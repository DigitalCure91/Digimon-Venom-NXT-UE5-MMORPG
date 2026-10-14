#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTTradeTypes.h"
#include "Engine/GameInstance.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTTradeJournalRecovery,
    "DigimonVenomNXT.Trading.Persistence.PartialCommitRecoveryAndStaleSaveFence",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTTradeJournalRecovery::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Root = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Automation"),
        TEXT("Trade_") + FGuid::NewGuid().ToString(EGuidFormats::Digits));
    struct FCleanup { FString Root; ~FCleanup() { IFileManager::Get().DeleteDirectory(*Root, false, true); } } Cleanup{ Root };
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    Store->SetStorageRootForTests(Root);
    FDigimonPlayerProfile A, B;
    A.AccountId = TEXT("trade_a"); A.Username = TEXT("Trade A"); A.Credits = 1000; A.DigiRubies = 20;
    B.AccountId = TEXT("trade_b"); B.Username = TEXT("Trade B"); B.Credits = 100; B.DigiRubies = 10;
    if (!TestTrue(TEXT("Create profile A"), Store->SaveProfile(A)) || !TestTrue(TEXT("Create profile B"), Store->SaveProfile(B))) return false;
    Store->LoadExistingCommerceProfile(A.AccountId, A); Store->LoadExistingCommerceProfile(B.AccountId, B);
    const FDigimonPlayerProfile StaleA = A;
    FString Error;
    TArray<FDigimonPlayerProfile> Next { A, B };
    Next[0].Credits -= 250; Next[1].Credits += 250;
    Next[0].DigiRubies += 3; Next[1].DigiRubies -= 3;
    const FString Pending = FPaths::Combine(Root, TEXT("Commerce"), TEXT("pending.json"));
    const FString Blocked = FPaths::Combine(Root, TEXT("Profiles"), TEXT("trade_b.json.tmp"));
    if (!TestTrue(TEXT("Inject failure after first profile can publish"), IFileManager::Get().MakeDirectory(*Blocked, true))) return false;
    TestTrue(TEXT("Complete journal intent is accepted even when one target write fails"), Store->CommitProfileGroup(Next, Error));
    TestEqual(TEXT("Accepted intent advances exactly one generation"), Next[0].CommerceRevision, int64(1));
    FString SavedIntent;
    TestTrue(TEXT("Intent remains available for recovery"), FFileHelper::LoadFileToString(SavedIntent, *Pending));
    FDigimonPlayerProfile Loaded;
    TestFalse(TEXT("Cannot expose half-committed profiles"), Store->LoadExistingCommerceProfile(B.AccountId, Loaded));
    TestFalse(TEXT("Cannot overwrite while recovery is blocked"), Store->SaveProfile(Next[0]));
    TestFalse(TEXT("Old login cannot load while recovery is blocked"), Store->LoadProfile(A.AccountId, A.Username, Loaded));
    FString Market; bool bExists = false;
    TestFalse(TEXT("Cannot expose stale market while recovery is blocked"), Store->LoadCommerceMarket(Market, bExists, Error));
    IFileManager::Get().DeleteDirectory(*Blocked, false, true);
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Restarted(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Restarted->SetAutomaticSavingForTests(true);
    Restarted->SetStorageRootForTests(Root);
    if (!TestTrue(TEXT("Fresh subsystem recovers before exposing a profile"), Restarted->LoadExistingCommerceProfile(B.AccountId, Loaded))) return false;
    TestEqual(TEXT("Seller gets full committed credits once"), Loaded.Credits, int64(350));
    TestEqual(TEXT("Seller pays rubies once"), Loaded.DigiRubies, 7);
    Restarted->LoadExistingCommerceProfile(A.AccountId, Loaded);
    TestEqual(TEXT("Buyer debit recovered once"), Loaded.Credits, int64(750));
    TestEqual(TEXT("Buyer receives rubies once"), Loaded.DigiRubies, 23);
    TestFalse(TEXT("Older snapshot cannot undo a trade"), Restarted->SaveProfile(StaleA));
    TestTrue(TEXT("Both targets and market completed before journal removal"), !IFileManager::Get().FileExists(*Pending));
    // Simulate unlink resurrection after successful recovery and a newer same-generation autosave.
    Loaded.Credits += 77;
    TestTrue(TEXT("Ordinary post-trade gameplay saves normally"), Restarted->SaveProfile(Loaded));
    TestTrue(TEXT("Simulate old intent reappearing after interrupted unlink"), FFileHelper::SaveStringToFile(SavedIntent, *Pending));
    FDigimonPlayerProfile Later;
    TestTrue(TEXT("Durable completion marker suppresses old replay"), Restarted->LoadExistingCommerceProfile(A.AccountId, Later));
    TestEqual(TEXT("Later gameplay survives old journal resurrection"), Later.Credits, int64(827));
    // A failure before the durable intent must leave both profiles and caller revisions untouched.
    const FString BlockedIntent = Pending + TEXT(".tmp");
    IFileManager::Get().MakeDirectory(*BlockedIntent, true);
    TArray<FDigimonPlayerProfile> Rejected { Later };
    Rejected[0].Credits -= 1;
    TestFalse(TEXT("Blocked journal creation rejects transaction"), Restarted->CommitProfileGroup(Rejected, Error));
    TestEqual(TEXT("Rejected transaction does not advance caller revision"), Rejected[0].CommerceRevision, int64(1));
    Restarted->LoadExistingCommerceProfile(A.AccountId, Later);
    TestEqual(TEXT("Rejected transaction preserves previous durable money"), Later.Credits, int64(827));
    IFileManager::Get().DeleteDirectory(*BlockedIntent, false, true);
    const FString BlockedMarker = FPaths::Combine(Root, TEXT("Commerce"), TEXT("completed.txt.tmp"));
    IFileManager::Get().MakeDirectory(*BlockedMarker, true);
    TArray<FDigimonPlayerProfile> MarkerFailure { Later };
    MarkerFailure[0].Credits -= 7;
    TestTrue(TEXT("Intent remains committed if completion-marker write fails"), Restarted->CommitProfileGroup(MarkerFailure, Error));
    TestFalse(TEXT("A missing completion marker keeps newer profile writes fenced"), Restarted->SaveProfile(MarkerFailure[0]));
    IFileManager::Get().DeleteDirectory(*BlockedMarker, false, true);
    TestTrue(TEXT("Retry finishes marker and exposes committed result"), Restarted->LoadExistingCommerceProfile(A.AccountId, Later));
    TestEqual(TEXT("Repeated marker-stage replay does not repeat debit"), Later.Credits, int64(820));
    TestEqual(TEXT("Marker-stage recovery preserves generation"), Later.CommerceRevision, int64(2));
    return true;
}
#endif
