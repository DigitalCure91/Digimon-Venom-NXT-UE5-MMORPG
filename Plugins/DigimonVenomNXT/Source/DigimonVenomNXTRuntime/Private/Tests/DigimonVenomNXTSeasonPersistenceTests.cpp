#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTProfileSubsystem.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTSeasonArchivePersistenceTest,
    "DigimonVenomNXT.Season.Archive.AtomicProfileFence",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTSeasonArchivePersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    // Only this randomly named synthetic account is touched by the test.
    const FString AccountId = TEXT("Automation_SeasonArchive_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString ProfilePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Profiles"), AccountId + TEXT(".json"));
    const FString ArchiveRoot = FPaths::Combine(FPaths::GetPath(ProfilePath), TEXT("SeasonArchive"), AccountId);
    struct FCleanup
    {
        FString Profile;
        FString Archive;
        ~FCleanup()
        {
            IFileManager::Get().DeleteDirectory(*(Profile + TEXT(".tmp")), false, true);
            IFileManager::Get().Delete(*(Profile + TEXT(".tmp")), false, true, true);
            IFileManager::Get().Delete(*Profile, false, true, true);
            IFileManager::Get().DeleteDirectory(*Archive, false, true);
        }
    } Cleanup{ProfilePath, ArchiveRoot};

    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    FDigimonPlayerProfile Profile;
    Profile.AccountId = AccountId;
    Profile.Username = TEXT("Archive transaction fixture");
    Profile.Season.Version = 1;
    Profile.Season.CareerId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
    Profile.Season.FirstArchiveWeek = 1;
    Profile.Season.Week = 1;
    if (!TestTrue(TEXT("Create an empty private career"), Store->SaveProfile(Profile))) return false;

    FDigimonSeasonArchive Record;
    Record.CareerId = Profile.Season.CareerId;
    Record.Week = 1;
    Record.EventName = TEXT("Completed week one");
    for (int32 Index = 0; Index < 8; ++Index)
    {
        FDigimonSeasonMatch Match;
        Match.MatchId = FString::Printf(TEXT("fixture_%d"), Index);
        Match.HomeTamerId = FString::Printf(TEXT("tamer_%d"), Index * 2);
        Match.AwayTamerId = FString::Printf(TEXT("tamer_%d"), Index * 2 + 1);
        Match.bResolved = true;
        Match.WinnerTamerId = Match.HomeTamerId;
        Record.Matches.Add(Match);
    }
    FDigimonPlayerProfile Candidate = Profile;
    Candidate.Season.Week = 2;
    Candidate.Season.Archive.Add(Record);
    // A directory at the temporary profile path makes only the final profile write fail;
    // immutable archive writes have already succeeded by this point.
    if (!TestTrue(TEXT("Create a profile-write failure fixture"),
        IFileManager::Get().MakeDirectory(*(ProfilePath + TEXT(".tmp")), true))) return false;
    TestFalse(TEXT("Archive does not mask a failed profile commit"), Store->SaveProfile(Candidate));
    const FString RecordPath = FPaths::Combine(ArchiveRoot, Profile.Season.CareerId, TEXT("week_0000000001.json"));
    TestTrue(TEXT("Failure left a provisional archive record"), IFileManager::Get().FileExists(*RecordPath));
    FDigimonSeasonArchivePage Page;
    TestTrue(TEXT("Read archive using the committed profile"), Store->LoadSeasonArchive(Candidate, 0, 8, Page));
    TestEqual(TEXT("Uncommitted week remains invisible"), Page.TotalRecords, 0);
    TestEqual(TEXT("Uncommitted record is not returned"), Page.Records.Num(), 0);
    IFileManager::Get().DeleteDirectory(*(ProfilePath + TEXT(".tmp")), false, true);

    // A host may change payroll settings between attempts. The unpublished record must
    // be replaceable while the previously committed history remains strictly immutable.
    Candidate.Season.Archive[0].CreditsEarned = 333;
    if (!TestTrue(TEXT("Changed provisional transaction retries successfully"), Store->SaveProfile(Candidate))) return false;
    TestTrue(TEXT("Repeated committed save is idempotent"), Store->SaveProfile(Candidate));
    TestTrue(TEXT("Committed record is readable"), Store->LoadSeasonArchive(Candidate, 0, 8, Page));
    TestEqual(TEXT("Exactly one completed week is archived"), Page.TotalRecords, 1);
    TestEqual(TEXT("One complete card is returned"), Page.Records.Num(), 1);
    if (!Page.Records.IsEmpty())
    {
        TestEqual(TEXT("Card content retained"), Page.Records[0].EventName, Record.EventName);
        TestEqual(TEXT("Committed payout uses the successful retry's amount"), Page.Records[0].CreditsEarned, static_cast<int64>(333));
    }

    FString Before, After;
    FFileHelper::LoadFileToString(Before, *RecordPath);
    FDigimonPlayerProfile Conflict = Candidate;
    Conflict.Season.Archive[0].EventName = TEXT("Conflicting rewritten history");
    TestFalse(TEXT("Conflicting immutable history rejects the complete save"), Store->SaveProfile(Conflict));
    FFileHelper::LoadFileToString(After, *RecordPath);
    TestEqual(TEXT("Conflicting retry never overwrites the old bytes"), After, Before);
    TestTrue(TEXT("History remains readable after rejected conflict"), Store->LoadSeasonArchive(Candidate, 999999, 100000, Page));
    TestEqual(TEXT("Requested page is bounded"), Page.PageIndex, 0);
    TestEqual(TEXT("Page size is bounded"), Page.PageSize, 12);

    // A missing/corrupt historical record must not be replaced with fabricated results.
    FFileHelper::SaveStringToFile(TEXT("invalid JSON"), *RecordPath);
    TestFalse(TEXT("Corrupt archived cards report a load failure"), Store->LoadSeasonArchive(Candidate, 0, 8, Page));
    TestFalse(TEXT("Corrupt archive is not silently overwritten by autosave"), Store->SaveProfile(Candidate));
    TestFalse(TEXT("Failure page is explicitly unsuccessful"), Page.bSuccess);
    TestTrue(TEXT("Failure supplies player-readable retry text"), !Page.Error.IsEmpty());

    // Repair only the synthetic corruption fixture, then let the live cache evict old cards.
    if (!TestTrue(TEXT("Restore the test's intentionally corrupted record"),
        FFileHelper::SaveStringToFile(Before, *RecordPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))) return false;
    for (int32 Week = 2; Week <= 11; ++Week)
    {
        FDigimonSeasonArchive NextRecord = Record;
        NextRecord.Week = Week;
        NextRecord.EventName = FString::Printf(TEXT("Completed week %d"), Week);
        for (int32 MatchIndex = 0; MatchIndex < NextRecord.Matches.Num(); ++MatchIndex)
            NextRecord.Matches[MatchIndex].MatchId = FString::Printf(TEXT("week_%d_fixture_%d"), Week, MatchIndex);
        Candidate.Season.Archive.Add(NextRecord);
        if (Candidate.Season.Archive.Num() > 2) Candidate.Season.Archive.RemoveAt(0);
        Candidate.Season.Week = Week + 1;
        if (!TestTrue(TEXT("Archive a new week while keeping a two-card live cache"), Store->SaveProfile(Candidate))) return false;
    }
    TestTrue(TEXT("Read newest archive page beyond the bounded live cache"), Store->LoadSeasonArchive(Candidate, 0, 8, Page));
    TestEqual(TEXT("All eleven weeks survive live cache eviction"), Page.TotalRecords, 11);
    TestEqual(TEXT("First history page is full"), Page.Records.Num(), 8);
    TestTrue(TEXT("Older page is advertised"), Page.bHasMore);
    if (!Page.Records.IsEmpty()) TestEqual(TEXT("Newest archived week comes first"), Page.Records[0].Week, 11);
    TestTrue(TEXT("Read history page containing the first career week"), Store->LoadSeasonArchive(Candidate, 1, 8, Page));
    TestEqual(TEXT("Remaining three weeks are available"), Page.Records.Num(), 3);
    TestFalse(TEXT("Final history page has no older page"), Page.bHasMore);
    if (!Page.Records.IsEmpty()) TestEqual(TEXT("Oldest original card remains available"), Page.Records.Last().Week, 1);

    FDigimonPlayerProfile Migrated = Profile;
    Migrated.Season.CareerId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
    Migrated.Season.FirstArchiveWeek = 137;
    Migrated.Season.Week = 137;
    TestTrue(TEXT("Migrate a legacy career without inventing missing history"), Store->SaveProfile(Migrated));
    TestTrue(TEXT("Migrated career history reads successfully"), Store->LoadSeasonArchive(Migrated, 0, 8, Page));
    TestEqual(TEXT("Legacy weeks are not fabricated or borrowed from another career"), Page.TotalRecords, 0);
    TestFalse(TEXT("Stale career identity cannot read another committed career"), Store->LoadSeasonArchive(Candidate, 0, 8, Page));
    TestTrue(TEXT("Original career's immutable records remain on disk"), IFileManager::Get().FileExists(*RecordPath));
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
