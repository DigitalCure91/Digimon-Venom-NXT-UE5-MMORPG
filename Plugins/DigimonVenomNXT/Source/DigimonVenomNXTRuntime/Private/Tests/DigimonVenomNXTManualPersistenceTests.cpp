#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTProfileSnapshot.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/Class.h"

namespace DigimonVenomNXTManualPersistenceTestPrivate
{
struct FStorageCleanup
{
    FString Root;
    ~FStorageCleanup() { IFileManager::Get().DeleteDirectory(*Root, false, true); }
};
FString MakeRoot()
{
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Automation"),
        TEXT("ManualPersistence_") + FGuid::NewGuid().ToString(EGuidFormats::Digits));
}
FDigimonPlayerProfile MakeProfile(const TCHAR* Id)
{
    FDigimonPlayerProfile Profile;
    Profile.AccountId = Id;
    Profile.Username = FString(TEXT("Manual fixture ")) + Id;
    Profile.Credits = 120000;
    Profile.DigiRubies = 70;
    Profile.Ranked.Grade = EDigimonRankedGrade::Gold;
    Profile.Ranked.Rating = 1600;
    Profile.Season.CareerId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
    Profile.Season.FirstArchiveWeek = 1;
    Profile.Season.Week = 1;
    for (int32 Index = 0; Index < 6; ++Index)
    {
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid::NewGuid();
        Partner.SpeciesId = FName(*FString::Printf(TEXT("manual_fixture_%d"), Index));
        Partner.Level = 45;
        Partner.CurrentHP = 400;
        Partner.CurrentSP = 90;
        Profile.Collection.Add(Partner);
        Profile.Party.Add(Partner.InstanceId);
    }
    return Profile;
}
FDigimonSeasonArchive MakeWeek(const FString& CareerId, int32 Week)
{
    FDigimonSeasonArchive Record;
    Record.CareerId = CareerId;
    Record.Week = Week;
    Record.EventName = FString::Printf(TEXT("Manual-save week %d"), Week);
    for (int32 Index = 0; Index < 8; ++Index)
    {
        FDigimonSeasonMatch Match;
        Match.MatchId = FString::Printf(TEXT("manual_%d_%d"), Week, Index);
        Match.HomeTamerId = FString::Printf(TEXT("home_%d"), Index);
        Match.AwayTamerId = FString::Printf(TEXT("away_%d"), Index);
        Match.WinnerTamerId = Match.HomeTamerId;
        Match.bResolved = true;
        Record.Matches.Add(Match);
    }
    return Record;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTManualLogoutRetentionTest,
    "DigimonVenomNXT.Accounts.ManualPersistence.NoPlayerLogoutWriteAndOfflineAdminFlush",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTManualLogoutRetentionTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    using namespace DigimonVenomNXTManualPersistenceTestPrivate;
    FStorageCleanup Cleanup{MakeRoot()};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetStorageRootForTests(Cleanup.Root);
    Store->SetAutomaticSavingForTests(false);
    FDigimonPlayerProfile A = MakeProfile(TEXT("manual_a")), B = MakeProfile(TEXT("manual_b"));
    if (!TestTrue(TEXT("Stage first six-party account"), Store->SaveProfile(A)) ||
        !TestTrue(TEXT("Stage second six-party account"), Store->SaveProfile(B))) return false;
    // Read the normalized accepted values before evolving the synthetic session.
    Store->LoadProfile(A.AccountId, A.Username, A);
    Store->LoadProfile(B.AccountId, B.Username, B);
    A.Ranked.Grade = EDigimonRankedGrade::Silver;
    A.Ranked.Rating = 1450;
    A.Collection[2].Experience += 12345;
    A.Credits += 5000;
    if (!TestTrue(TEXT("Ordinary logout hands off to memory"), Store->RetainProfile(A))) return false;
    const FString APath = FPaths::Combine(Cleanup.Root, TEXT("Profiles"), TEXT("manual_a.json"));
    const FString BPath = FPaths::Combine(Cleanup.Root, TEXT("Profiles"), TEXT("manual_b.json"));
    TestFalse(TEXT("Logout did not create a profile file"), IFileManager::Get().FileExists(*APath));
    TestFalse(TEXT("Gameplay did not create a temporary profile file"), IFileManager::Get().FileExists(*(APath + TEXT(".tmp"))));
    FDigimonPlayerProfile Rejoined;
    if (!TestTrue(TEXT("Reconnect uses authoritative memory, not absent/older disk"), Store->LoadProfile(A.AccountId, A.Username, Rejoined))) return false;
    TestTrue(TEXT("Every reflected value survives session handoff"), FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&A, &Rejoined, 0));
    FString Error;
    TArray<FDigimonPlayerProfile> Pair { A, B };
    Pair[0].Credits -= 321;
    Pair[1].Credits += 321;
    if (!TestTrue(TEXT("Paired transaction is accepted atomically in memory"), Store->CommitProfileGroup(Pair, Error))) return false;
    TestEqual(TEXT("Both revisions advance together"), Pair[0].CommerceRevision, Pair[1].CommerceRevision);
    TestFalse(TEXT("Stale disconnected session cannot undo a trade"), Store->RetainProfile(A));
    TestFalse(TEXT("Paired manual transaction did not write profile A"), IFileManager::Get().FileExists(*APath));
    TestFalse(TEXT("Paired manual transaction did not write profile B"), IFileManager::Get().FileExists(*BPath));
    int32 UnauthorizedCount = 0;
    TestFalse(TEXT("A non-admin cannot force a disk checkpoint"), Store->SaveForHostConsole(UnauthorizedCount, Error));
    if (!TestTrue(TEXT("Test-isolated admin checkpoint includes disconnected profiles"), Store->FlushForTests(Error))) return false;
    TestTrue(TEXT("Admin checkpoint wrote offline A"), IFileManager::Get().FileExists(*APath));
    TestTrue(TEXT("Admin checkpoint wrote offline B"), IFileManager::Get().FileExists(*BPath));
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Reopened(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Reopened->SetStorageRootForTests(Cleanup.Root);
    Reopened->SetAutomaticSavingForTests(false);
    FDigimonPlayerProfile DiskA, DiskB;
    if (!TestTrue(TEXT("Fresh server loads checkpointed A"), Reopened->LoadProfile(A.AccountId, A.Username, DiskA)) ||
        !TestTrue(TEXT("Fresh server loads checkpointed B"), Reopened->LoadProfile(B.AccountId, B.Username, DiskB))) return false;
    TestEqual(TEXT("Offline A retains trade and progression"), DiskA.Credits, Pair[0].Credits);
    TestEqual(TEXT("Offline B retains trade and progression"), DiskB.Credits, Pair[1].Credits);
    TestEqual(TEXT("All party members survived disk checkpoint"), DiskA.Party.Num(), 6);
    TestTrue(TEXT("Ranked Silver grade is retained"), DiskA.Ranked.Grade == EDigimonRankedGrade::Silver);
    // Subsequent ordinary logout must leave an existing disk checkpoint byte-for-byte unchanged.
    FString Before, After;
    FFileHelper::LoadFileToString(Before, *APath);
    DiskA.Credits += 999;
    if (!TestTrue(TEXT("Later logout is also memory-only"), Reopened->RetainProfile(DiskA))) return false;
    FFileHelper::LoadFileToString(After, *APath);
    TestEqual(TEXT("Ordinary logout never rewrites existing profile"), After, Before);
    FDigimonPlayerProfile Latest;
    Reopened->LoadProfile(DiskA.AccountId, DiskA.Username, Latest);
    TestEqual(TEXT("Another rejoin still sees the newer unsaved balance"), Latest.Credits, DiskA.Credits);
    TArray<uint8> Bytes;
    int32 JsonBytes = 0;
    uint32 Checksum = 0;
    FDigimonPlayerProfile ClientCopy;
    if (!TestTrue(TEXT("Retained profile prepares owner snapshot"), DigimonVenomNXTProfileSnapshot::Encode(Latest, Bytes, JsonBytes, Checksum, Error)) ||
        !TestTrue(TEXT("Client decodes complete retained profile"), DigimonVenomNXTProfileSnapshot::Decode(Bytes.GetData(), Bytes.Num(), JsonBytes, Checksum, Latest.AccountId, ClientCopy, Error))) return false;
    TestTrue(TEXT("Menu snapshot equals authoritative battle source"), FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Latest, &ClientCopy, 0));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTManualArchiveRetentionTest,
    "DigimonVenomNXT.Accounts.ManualPersistence.HistoryBeyondLiveWindow",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTManualArchiveRetentionTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    using namespace DigimonVenomNXTManualPersistenceTestPrivate;
    FStorageCleanup Cleanup{MakeRoot()};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetStorageRootForTests(Cleanup.Root);
    Store->SetAutomaticSavingForTests(false);
    FDigimonPlayerProfile Profile = MakeProfile(TEXT("manual_history"));
    for (int32 Week = 1; Week <= 24; ++Week)
    {
        Profile.Season.Archive.Insert(MakeWeek(Profile.Season.CareerId, Week), 0);
        if (Profile.Season.Archive.Num() > 4) Profile.Season.Archive.SetNum(4);
        Profile.Season.Week = Week + 1;
        if (!TestTrue(TEXT("Accept next week without writing disk"), Store->SaveProfile(Profile))) return false;
    }
    FDigimonSeasonArchivePage Page;
    if (!TestTrue(TEXT("Oldest unsaved page remains readable"), Store->LoadSeasonArchive(Profile, 1, 12, Page))) return false;
    TestEqual(TEXT("All 24 accepted weeks are indexed"), Page.TotalRecords, 24);
    TestEqual(TEXT("Oldest week survived live-window pruning"), Page.Records.Last().Week, 1);
    FString Error;
    if (!TestTrue(TEXT("Admin saves full retained history"), Store->FlushForTests(Error))) return false;
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Reopened(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Reopened->SetStorageRootForTests(Cleanup.Root);
    Reopened->SetAutomaticSavingForTests(false);
    FDigimonPlayerProfile Loaded;
    if (!TestTrue(TEXT("Read bounded profile from disk"), Reopened->LoadProfile(Profile.AccountId, Profile.Username, Loaded))) return false;
    TestEqual(TEXT("Profile does not grow to contain every historical week"), Loaded.Season.Archive.Num(), 4);
    if (!TestTrue(TEXT("Read separately persisted oldest archive page"), Reopened->LoadSeasonArchive(Loaded, 1, 12, Page))) return false;
    TestEqual(TEXT("Disk history still reaches week one"), Page.Records.Last().Week, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTManualFlushRecoveryTest,
    "DigimonVenomNXT.Accounts.ManualPersistence.InterruptedAdminCheckpoint",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTManualFlushRecoveryTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    using namespace DigimonVenomNXTManualPersistenceTestPrivate;
    FStorageCleanup Cleanup{MakeRoot()};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetStorageRootForTests(Cleanup.Root);
    Store->SetAutomaticSavingForTests(false);
    const FDigimonPlayerProfile A = MakeProfile(TEXT("manual_a")), B = MakeProfile(TEXT("manual_b"));
    Store->SaveProfile(A); Store->SaveProfile(B);
    const FString Blocked = FPaths::Combine(Cleanup.Root, TEXT("Profiles"), TEXT("manual_b.json.tmp"));
    if (!TestTrue(TEXT("Inject target-file failure"), IFileManager::Get().MakeDirectory(*Blocked, true))) return false;
    FString Error;
    TestFalse(TEXT("Admin is not told that an incomplete flush succeeded"), Store->FlushForTests(Error));
    const FString Pending = FPaths::Combine(Cleanup.Root, TEXT("Commerce"), TEXT("pending.json"));
    TestTrue(TEXT("Complete all-profile intent remains replayable"), IFileManager::Get().FileExists(*Pending));
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Reopened(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Reopened->SetStorageRootForTests(Cleanup.Root);
    Reopened->SetAutomaticSavingForTests(false);
    FDigimonPlayerProfile Loaded;
    TestFalse(TEXT("Incomplete checkpoint is not replaced by a new empty profile"), Reopened->LoadProfile(B.AccountId, B.Username, Loaded));
    IFileManager::Get().DeleteDirectory(*Blocked, false, true);
    if (!TestTrue(TEXT("Retry replays the complete intended account"), Reopened->LoadProfile(B.AccountId, B.Username, Loaded))) return false;
    TestEqual(TEXT("Replay preserves all six members"), Loaded.Party.Num(), 6);
    TestEqual(TEXT("Replay preserves full balance"), Loaded.Credits, B.Credits);
    TestFalse(TEXT("Intent is removed only after all targets complete"), IFileManager::Get().FileExists(*Pending));
    return true;
}
#endif
