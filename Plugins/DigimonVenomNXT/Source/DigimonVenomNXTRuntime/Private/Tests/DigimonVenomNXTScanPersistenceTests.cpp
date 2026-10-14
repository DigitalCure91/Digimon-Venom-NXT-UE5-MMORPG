#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTScanCore.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTScanPersistenceTest,
    "DigimonVenomNXT.DigiDex.Persistence.AtomicMaterialization",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTScanPersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Account = TEXT("Automation_DigiDex_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString OtherAccount = Account + TEXT("_other");
    const FString Root = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Profiles"));
    const FString Path = FPaths::Combine(Root, Account + TEXT(".json"));
    const FString OtherPath = FPaths::Combine(Root, OtherAccount + TEXT(".json"));
    struct FCleanup
    {
        FString ProfilePath, OtherProfilePath;
        ~FCleanup()
        {
            for (const FString& File : {ProfilePath, OtherProfilePath})
            {
                IFileManager::Get().DeleteDirectory(*(File + TEXT(".tmp")), false, true);
                IFileManager::Get().Delete(*(File + TEXT(".tmp")), false, true, true);
                IFileManager::Get().Delete(*File, false, true, true);
            }
        }
    } Cleanup{Path, OtherPath};

    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    FDigimonPlayerProfile Profile;
    Profile.AccountId = Account;
    Profile.Username = TEXT("DigiDex fixture");
    FDigimonScanRecord Scan;
    Scan.SpeciesId = TEXT("agumon");
    Scan.Percent = Scan.PeakPercent = 200;
    Profile.Scans.Add(Scan);
    Scan.Variant = EDigimonVariant::Shiny;
    Scan.Percent = Scan.PeakPercent = 140;
    Profile.Scans.Add(Scan);
    if (!TestTrue(TEXT("Save the exact account and variant scan balances"), Store->SaveProfile(Profile))) return false;
    FDigimonPlayerProfile Other;
    if (!TestTrue(TEXT("Create an independent account"), Store->LoadProfile(OtherAccount, TEXT("Other fixture"), Other))) return false;
    const FDigimonPlayerProfile Before = Profile;
    FDigimonOwnedPartner Partner;
    Partner.InstanceId = FGuid::NewGuid();
    Partner.SpeciesId = TEXT("agumon");
    const auto Mutate = [&Partner](FDigimonPlayerProfile& Candidate)
    {
        FDigimonScanRecord& Data = Candidate.Scans[0];
        const auto Result = DigimonVenomNXTScanCore::Materialize(Data.Percent, 100, 200, true);
        DigimonVenomNXTScanCore::Observe(Data, 200, true);
        Data.Percent = Result.RemainingPercent;
        ++Data.Materializations;
        Partner.ABI = Result.BonusABI;
        Candidate.Collection.Add(Partner);
        Candidate.Party.Add(Partner.InstanceId);
    };
    const auto Save = [&Store](const FDigimonPlayerProfile& Candidate) { return Store->SaveProfile(Candidate); };
    if (!TestTrue(TEXT("Force failure only at the synthetic profile's temporary file"),
        IFileManager::Get().MakeDirectory(*(Path + TEXT(".tmp")), true))) return false;
    TestFalse(TEXT("Failed durable save refuses materialization"), DigimonVenomNXTScanCore::Commit(Profile, Mutate, Save));
    TestTrue(TEXT("Every reflected field is restored after save failure"),
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Profile, &Before, 0));
    FDigimonPlayerProfile Reloaded;
    if (!TestTrue(TEXT("Failed conversion leaves the old account readable"), Store->LoadProfile(Account, Profile.Username, Reloaded))) return false;
    TestEqual(TEXT("Failed conversion leaves scan on disk"), Reloaded.Scans[0].Percent, 200);
    TestEqual(TEXT("Failed conversion cannot create a saved partner"), Reloaded.Collection.Num(), 0);
    if (!TestTrue(TEXT("Release the temporary-file failure fixture"),
        IFileManager::Get().DeleteDirectory(*(Path + TEXT(".tmp")), false, true))) return false;
    if (!TestTrue(TEXT("Retry commits the complete materialization"), DigimonVenomNXTScanCore::Commit(Profile, Mutate, Save))) return false;
    if (!TestTrue(TEXT("Reconnect reloads the saved profile"), Store->LoadProfile(Account, Profile.Username, Reloaded))) return false;
    TestEqual(TEXT("Only the consumed form's scan resets"), Reloaded.Scans[0].Percent, 0);
    TestEqual(TEXT("Peak discovery survives consumption"), Reloaded.Scans[0].PeakPercent, 200);
    TestTrue(TEXT("Lifetime ownership survives serialization"), Reloaded.Scans[0].bEverOwned);
    TestEqual(TEXT("Lifetime conversion count survives serialization"), Reloaded.Scans[0].Materializations, 1);
    TestEqual(TEXT("Another variant retains its scan"), Reloaded.Scans[1].Percent, 140);
    TestFalse(TEXT("Another variant has not been owned"), Reloaded.Scans[1].bEverOwned);
    TestEqual(TEXT("Exactly one real partner was created"), Reloaded.Collection.Num(), 1);
    if (!Reloaded.Collection.IsEmpty())
    {
        TestTrue(TEXT("The same instance identity survives reconnect"), Reloaded.Collection[0].InstanceId == Partner.InstanceId);
        TestEqual(TEXT("Perfect scan grants permanent ABI"), Reloaded.Collection[0].ABI, 5);
        TestEqual(TEXT("Materialized partner begins at level one"), Reloaded.Collection[0].Level, 1);
        TestTrue(TEXT("The actual partner is in the real party"), Reloaded.Party.Contains(Partner.InstanceId));
    }
    TestFalse(TEXT("Consumed scan cannot create a second partner"), DigimonVenomNXTScanCore::Materialize(Reloaded.Scans[0].Percent, 100, 200, true).Ready);
    if (!TestTrue(TEXT("Read the other private account"), Store->LoadProfile(OtherAccount, Other.Username, Other))) return false;
    TestEqual(TEXT("Other account has no borrowed discovery"), Other.Scans.Num(), 0);
    TestEqual(TEXT("Other account has no borrowed partner"), Other.Collection.Num(), 0);
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
