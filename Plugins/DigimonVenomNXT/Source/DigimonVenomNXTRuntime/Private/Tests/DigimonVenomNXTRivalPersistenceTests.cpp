#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTRivalPersistence.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

namespace
{
    struct FRivalPersistenceTestDirectory
    {
        FString Path = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("Automation"), TEXT("RivalPersistence"), FGuid::NewGuid().ToString(EGuidFormats::Digits));
        FRivalPersistenceTestDirectory() { IFileManager::Get().MakeDirectory(*Path, true); }
        ~FRivalPersistenceTestDirectory() { IFileManager::Get().DeleteDirectory(*Path, false, true); }
    };
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonRivalStreamingRoundTripTest,
    "DigimonVenomNXT.Rivals.Persistence.StreamingRoundTrip",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonRivalStreamingRoundTripTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FRivalPersistenceTestDirectory Directory;
    const FString Path = FPaths::Combine(Directory.Path, TEXT("AIRivals.json.tmp"));
    FDigimonAIRivalSaveData Before;
    Before.ActivityWindowStartUnix = 1793059200;
    Before.LastSavedUnix = 1793060000;
    for (int32 I = 0; I < 2; ++I)
    {
        FDigimonAIRivalRecord Rival;
        Rival.RivalId = FString::Printf(TEXT("AI-%04d"), I + 1);
        Rival.DisplayName = TEXT("Aster \"quoted\" \\ escaped");
        Rival.Credits = 987654321;
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid::NewGuid();
        Partner.SpeciesId = TEXT("fixture_species");
        Partner.Level = 42; Partner.Experience = 123456789; Partner.ABI = 55;
        Partner.PermanentTraining.Attack = 19;
        for (const FName MoveId : {FName(TEXT("inherited_move")), FName(TEXT("current_move"))})
        {
            FDigimonMoveSlot Move; Move.MoveId = MoveId;
            Move.Description = TEXT("Catalog metadata sentinel must not be persisted");
            Move.DisplayName = FText::FromString(TEXT("Catalog display sentinel"));
            Move.Power = 777;
            Partner.Moves.Add(Move);
        }
        Rival.Collection.Add(Partner);
        Rival.Partners.Add(Partner);
        Before.Rivals.Add(Rival);
    }
    FString Error;
    if (!TestTrue(TEXT("Stream compact checkpoint"), DigimonVenomNXTRivalPersistence::WriteTemporary(Path, Before, Error)))
    {
        AddError(Error); return false;
    }
    FString Encoded;
    if (!TestTrue(TEXT("Read encoded fixture"), FFileHelper::LoadFileToString(Encoded, *Path))) return false;
    TestFalse(TEXT("Move descriptions are catalog data, not persistent copies"), Encoded.Contains(TEXT("Catalog metadata sentinel")));
    TestFalse(TEXT("Move display names are not duplicated"), Encoded.Contains(TEXT("Catalog display sentinel")));
    TestFalse(TEXT("Checkpoint uses condensed JSON"), Encoded.Contains(TEXT("\n")));
    FDigimonAIRivalSaveData After;
    bool bUnsupported = false;
    int32 CallbackCount = 0;
    if (!TestTrue(TEXT("Read compact checkpoint"), DigimonVenomNXTRivalPersistence::Read(Path, After,
        [this, &CallbackCount](FDigimonAIRivalRecord&, int32 Total)
        {
            ++CallbackCount;
            TestEqual(TEXT("Compaction knows the full population"), Total, 2);
        }, Error, bUnsupported)))
    {
        AddError(Error); return false;
    }
    TestFalse(TEXT("Current schema supported"), bUnsupported);
    TestEqual(TEXT("Each rival compacted exactly once"), CallbackCount, 2);
    TestEqual(TEXT("Population retained"), After.Rivals.Num(), 2);
    TestEqual(TEXT("Window timestamp retained"), After.ActivityWindowStartUnix, Before.ActivityWindowStartUnix);
    TestEqual(TEXT("Save timestamp retained"), After.LastSavedUnix, Before.LastSavedUnix);
    for (int32 I = 0; I < After.Rivals.Num(); ++I)
    {
        const FDigimonAIRivalRecord& Rival = After.Rivals[I];
        TestEqual(TEXT("Stable identity"), Rival.RivalId, Before.Rivals[I].RivalId);
        TestEqual(TEXT("Escaped display text round-trips"), Rival.DisplayName, Before.Rivals[I].DisplayName);
        if (!TestEqual(TEXT("Owned partner kept"), Rival.Collection.Num(), 1) || !TestEqual(TEXT("Party snapshot kept"), Rival.Partners.Num(), 1)) return false;
        TestEqual(TEXT("Ownership GUID retained"), Rival.Collection[0].InstanceId, Before.Rivals[I].Collection[0].InstanceId);
        TestEqual(TEXT("XP retained"), Rival.Collection[0].Experience, Before.Rivals[I].Collection[0].Experience);
        TestEqual(TEXT("Training retained"), Rival.Collection[0].PermanentTraining.Attack, 19);
        if (!TestEqual(TEXT("Both equipped moves retained"), Rival.Collection[0].Moves.Num(), 2)) return false;
        TestEqual(TEXT("Inherited move remains first"), Rival.Collection[0].Moves[0].MoveId, FName(TEXT("inherited_move")));
        TestEqual(TEXT("Second equipped move retained"), Rival.Collection[0].Moves[1].MoveId, FName(TEXT("current_move")));
        TestEqual(TEXT("Party move order retained"), Rival.Partners[0].Moves[0].MoveId, FName(TEXT("inherited_move")));
    }
    // The adapter also accepts the previous whole-struct, pretty JSON writer.
    FString Legacy;
    if (!TestTrue(TEXT("Build legacy JSON fixture"), FJsonObjectConverter::UStructToJsonObjectString(Before, Legacy)) ||
        !TestTrue(TEXT("Write legacy fixture"), FFileHelper::SaveStringToFile(Legacy, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))) return false;
    TestTrue(TEXT("Read previous-format checkpoint"), DigimonVenomNXTRivalPersistence::Read(Path, After,
        [](FDigimonAIRivalRecord&, int32) {}, Error, bUnsupported));
    // Exercise the real FArchive adapter across its 64 KiB refill boundary.
    // Place each byte of a Unicode escape near that boundary; the scanner must
    // retain quote/escape state rather than splitting on the braces in the text.
    for (int32 Split = 0; Split < 12; ++Split)
    {
        const FString Prefix = TEXT("{\"ignored\":\"");
        const FString Padding = FString::ChrN(65536 - Prefix.Len() - Split, TEXT('x'));
        const FString BoundaryJson = Prefix + Padding + TEXT("\\ud83d\\ude00 } [ \\\"\",\"rivals\":[{\"rivalId\":\"AI-boundary\"}]}");
        if (!TestTrue(TEXT("Write buffer-boundary fixture"), FFileHelper::SaveStringToFile(BoundaryJson, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))) return false;
        if (!TestTrue(TEXT("Read escaped text across archive refill"), DigimonVenomNXTRivalPersistence::Read(Path, After,
            [](FDigimonAIRivalRecord&, int32) {}, Error, bUnsupported))) { AddError(Error); return false; }
        TestEqual(TEXT("Record after boundary retained"), After.Rivals[0].RivalId, FString(TEXT("AI-boundary")));
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonRivalStreamingFailureTest,
    "DigimonVenomNXT.Rivals.Persistence.RejectIncompleteWithoutPublishing",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonRivalStreamingFailureTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FRivalPersistenceTestDirectory Directory;
    const FString Path = FPaths::Combine(Directory.Path, TEXT("AIRivals.json"));
    FDigimonAIRivalSaveData Existing;
    Existing.LastSavedUnix = 123;
    FDigimonAIRivalRecord Old; Old.RivalId = TEXT("AI-existing"); Existing.Rivals.Add(Old);
    FString Error;
    bool bUnsupported = false;
    int32 Callbacks = 0;
    const auto Callback = [&Callbacks](FDigimonAIRivalRecord&, int32) { ++Callbacks; };
    const FString Truncated = TEXT("{\"rivals\":[{\"rivalId\":\"AI-0001\"}],\"lastSavedUnix\":");
    FFileHelper::SaveStringToFile(Truncated, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    TestFalse(TEXT("Incomplete tail rejected"), DigimonVenomNXTRivalPersistence::Read(Path, Existing, Callback, Error, bUnsupported));
    TestEqual(TEXT("No partially validated records processed"), Callbacks, 0);
    TestEqual(TEXT("Prior in-memory checkpoint retained"), Existing.LastSavedUnix, static_cast<int64>(123));
    TestEqual(TEXT("Prior record retained"), Existing.Rivals[0].RivalId, FString(TEXT("AI-existing")));
    const FString Newer = TEXT("{\"rivals\":[{\"rivalId\":\"AI-0001\"}],\"schemaVersion\":4}");
    FFileHelper::SaveStringToFile(Newer, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    TestFalse(TEXT("Newer schema rejected even when last field"), DigimonVenomNXTRivalPersistence::Read(Path, Existing, Callback, Error, bUnsupported));
    TestTrue(TEXT("Caller is told not to roll back newer schema"), bUnsupported);
    TestEqual(TEXT("Newer schema never reaches migration callback"), Callbacks, 0);
    const FString Duplicate = TEXT("{\"rivals\":[{\"rivalId\":\"AI-0001\"},{\"rivalId\":\"AI-0001\"}]}");
    FFileHelper::SaveStringToFile(Duplicate, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    TestFalse(TEXT("Duplicate identity rejected"), DigimonVenomNXTRivalPersistence::Read(Path, Existing, Callback, Error, bUnsupported));
    TestEqual(TEXT("Duplicate rejection does not publish partial database"), Existing.Rivals[0].RivalId, FString(TEXT("AI-existing")));
    FDigimonAIRivalSaveData DuplicateData;
    DuplicateData.Rivals.Add(Old); DuplicateData.Rivals.Add(Old);
    const FString Temporary = Path + TEXT(".tmp");
    TestFalse(TEXT("Writer refuses duplicate identity"), DigimonVenomNXTRivalPersistence::WriteTemporary(Temporary, DuplicateData, Error));
    TestFalse(TEXT("Failed writer deletes its incomplete temporary file"), IFileManager::Get().FileExists(*Temporary));
    FString Unchanged;
    FFileHelper::LoadFileToString(Unchanged, *Path);
    TestEqual(TEXT("Failed writer never modifies primary"), Unchanged, Duplicate);
    return true;
}

#endif
