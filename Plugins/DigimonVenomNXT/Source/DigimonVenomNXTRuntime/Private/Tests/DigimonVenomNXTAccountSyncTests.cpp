#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTProfileSnapshot.h"
#include "DigimonVenomNXTProfileSyncCore.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTProfileValidation.h"
#include "DigimonVenomNXTBattleActor.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/Class.h"

// These tests use the real reflected profile, JSON codec, compression and disk
// store. They do not simulate actor channels or claim to be live network tests.
namespace DigimonVenomNXTAccountSyncTestPrivate
{
FDigimonOwnedPartner MakePartner(int32 Index)
{
    FDigimonOwnedPartner Partner;
    Partner.InstanceId = FGuid::NewGuid();
    Partner.SpeciesId = FName(*FString::Printf(TEXT("fixture_%03d"), Index));
    Partner.Nickname = FString::Printf(TEXT("Saved partner %d"), Index);
    Partner.Level = 75;
    Partner.Experience = 123456;
    Partner.CurrentHP = 321 + Index;
    Partner.CurrentSP = 47;
    Partner.CAM = 80;
    Partner.ABI = 90;
    Partner.CombatBalanceVersion = 1;
    return Partner;
}

FDigimonPlayerProfile MakeProfile(EDigimonRankedGrade Grade)
{
    FDigimonPlayerProfile Profile;
    Profile.AccountId = TEXT("AccountSync_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    Profile.Username = TEXT("AccountSyncFixture");
    Profile.Credits = 123456789;
    Profile.DigiRubies = 731;
    Profile.DigiLabRecoveryRevision = 5;
    for (int32 Index = 0; Index < 6; ++Index)
    {
        const FDigimonOwnedPartner Partner = MakePartner(Index);
        Profile.Collection.Add(Partner);
        Profile.Party.Add(Partner.InstanceId);
    }
    Profile.Ranked.Grade = Grade;
    Profile.Ranked.Rating = Grade == EDigimonRankedGrade::Gold ? 2100 : 1800;
    Profile.Ranked.CareerWins = 87;
    Profile.Ranked.Energy = 7;
    Profile.Ranked.DefenderLineup = Profile.Party;
    Profile.Ranked.DefenderTeam = Profile.Collection;
    Profile.Ranked.LastOpponentTeam = Profile.Collection;
    Profile.Ranked.LastOpponent = TEXT("Persisted full-team opponent");
    Profile.Ranked.LastResult = TEXT("Victory");
    // Large, mostly unique text tests multiple windows, not just a tiny zlib blob.
    for (int32 LineIndex = 0; LineIndex < 160; ++LineIndex)
    {
        FString Line = FString::Printf(TEXT("Turn %03d: "), LineIndex);
        for (int32 PartIndex = 0; PartIndex < 16; ++PartIndex)
            Line += FGuid::NewGuid().ToString(EGuidFormats::Digits);
        Profile.Ranked.LastBattleLog.Add(Line);
    }
    Profile.Season.Version = 1;
    Profile.Season.CareerId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
    Profile.Season.Week = 9;
    Profile.Season.FirstArchiveWeek = 9;
    Profile.Season.Wins = 12;
    Profile.Season.Championships = 2;
    for (int32 TamerIndex = 0; TamerIndex < 16; ++TamerIndex)
    {
        FDigimonSeasonTamer Tamer;
        Tamer.TamerId = FString::Printf(TEXT("career_tamer_%02d"), TamerIndex);
        Tamer.Name = FString::Printf(TEXT("Career tamer %d"), TamerIndex);
        Tamer.Rating = 1600 + TamerIndex;
        Tamer.Rank = TamerIndex + 1;
        for (int32 SlotIndex = 0; SlotIndex < 6; ++SlotIndex)
            Tamer.Team.Add(MakePartner(100 + TamerIndex * 6 + SlotIndex));
        Profile.Season.Roster.Add(Tamer);
    }
    FDigimonSeasonBattleCheckpoint Checkpoint;
    Checkpoint.Version = 2;
    Checkpoint.ContextId = TEXT("fixture_saved_season_decision");
    Checkpoint.State.BattleId = FGuid::NewGuid();
    Checkpoint.State.Kind = EDigimonBattleKind::Season;
    Checkpoint.State.TurnNumber = 32;
    for (const FDigimonOwnedPartner& Partner : Profile.Collection)
    {
        FDigimonBattleUnit Unit;
        Unit.InstanceId = Partner.InstanceId;
        Unit.SpeciesId = Partner.SpeciesId;
        Unit.HP = Partner.CurrentHP;
        Unit.SP = Partner.CurrentSP;
        Unit.Level = Partner.Level;
        Checkpoint.State.TeamA.Active.Add(Unit);
        Checkpoint.State.TeamB.Active.Add(Unit);
    }
    FJsonObjectConverter::UStructToJsonObjectString(Checkpoint, Profile.Season.BattleCheckpointJson);
    Profile.Season.PendingContextId = Checkpoint.ContextId;
    FDigimonInventoryEntry Inventory;
    Inventory.ItemId = TEXT("digimeat_cam");
    Inventory.Quantity = 12;
    Profile.Inventory.Add(Inventory);
    return Profile;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTAccountSnapshotCodecTest,
    "DigimonVenomNXT.Accounts.ProfileSync.LargeProfileCodecAndIntegrity",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTAccountSnapshotCodecTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    for (const EDigimonRankedGrade Grade : { EDigimonRankedGrade::Gold, EDigimonRankedGrade::Silver })
    {
        const FDigimonPlayerProfile Original = DigimonVenomNXTAccountSyncTestPrivate::MakeProfile(Grade);
        TArray<uint8> Bytes;
        int32 JsonBytes = 0;
        uint32 Checksum = 0;
        FString Error;
        if (!TestTrue(TEXT("Encode the real reflected progressed account"),
            DigimonVenomNXTProfileSnapshot::Encode(Original, Bytes, JsonBytes, Checksum, Error)))
        { AddError(Error); return false; }
        TestTrue(TEXT("Fixture exceeds 64 KiB before compression"), JsonBytes > 65536);
        TestTrue(TEXT("Fixture needs multiple acknowledged windows"),
            Bytes.Num() > DigimonVenomNXTProfileSyncCore::ChunkBytes * DigimonVenomNXTProfileSyncCore::WindowChunks);
        FDigimonPlayerProfile Received;
        if (!TestTrue(TEXT("Decode exact same-account snapshot"), DigimonVenomNXTProfileSnapshot::Decode(
            Bytes.GetData(), Bytes.Num(), JsonBytes, Checksum, Original.AccountId, Received, Error))) return false;
        TestTrue(TEXT("Every reflected field, including Season checkpoint and both ranked teams, survives"),
            FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Original, &Received, 0));
        TestEqual(TEXT("All six menu party identities survive"), Received.Party.Num(), 6);
        const FDigimonPlayerProfile Previous = Received;
        TestFalse(TEXT("Another account cannot replace the current client profile"), DigimonVenomNXTProfileSnapshot::Decode(
            Bytes.GetData(), Bytes.Num(), JsonBytes, Checksum, TEXT("different_account"), Received, Error));
        TestTrue(TEXT("Rejected identity leaves the previous profile untouched"),
            FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Previous, &Received, 0));
        TestFalse(TEXT("A changed checksum rejects the payload"), DigimonVenomNXTProfileSnapshot::Decode(
            Bytes.GetData(), Bytes.Num(), JsonBytes, Checksum ^ 1u, Original.AccountId, Received, Error));
        TestTrue(TEXT("Rejected checksum leaves the previous profile untouched"),
            FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Previous, &Received, 0));
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTAccountReconnectPersistenceTest,
    "DigimonVenomNXT.Accounts.ProfileSync.SixPartySeasonRankedRepeatedDiskReload",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTAccountReconnectPersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Root = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Automation"),
        TEXT("AccountSync_") + FGuid::NewGuid().ToString(EGuidFormats::Digits));
    struct FCleanup
    {
        FString Root;
        ~FCleanup() { IFileManager::Get().DeleteDirectory(*Root, false, true); }
    } Cleanup{Root};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    Store->SetStorageRootForTests(Root);
    for (const EDigimonRankedGrade Grade : { EDigimonRankedGrade::Gold, EDigimonRankedGrade::Silver })
    {
        FDigimonPlayerProfile Progress = DigimonVenomNXTAccountSyncTestPrivate::MakeProfile(Grade);
        if (!TestTrue(TEXT("Save complete authoritative progression"), Store->SaveProfile(Progress))) return false;
        FDigimonPlayerProfile Committed;
        if (!TestTrue(TEXT("Read committed baseline, including existing migrations"),
            Store->LoadProfile(Progress.AccountId, Progress.Username, Committed))) return false;
        for (int32 Reconnect = 0; Reconnect < 3; ++Reconnect)
        {
            // Fresh subsystem instance prevents an in-memory fixture from concealing
            // a broken durable reload. Its root is isolated from all real accounts.
            TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Reopened(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Reopened->SetAutomaticSavingForTests(true);
            Reopened->SetStorageRootForTests(Root);
            FDigimonPlayerProfile Loaded;
            if (!TestTrue(TEXT("Fresh store loads existing account, not a default profile"),
                Reopened->LoadProfile(Committed.AccountId, Committed.Username, Loaded))) return false;
            TestTrue(TEXT("Disk re-entry preserves every reflected field"),
                FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Committed, &Loaded, 0));
            TArray<uint8> Bytes;
            int32 JsonBytes = 0;
            uint32 Checksum = 0;
            FString Error;
            FDigimonPlayerProfile ClientCopy;
            if (!TestTrue(TEXT("Prepare owner transfer from reloaded server profile"),
                DigimonVenomNXTProfileSnapshot::Encode(Loaded, Bytes, JsonBytes, Checksum, Error)) ||
                !TestTrue(TEXT("Decode reloaded profile for owner menus"), DigimonVenomNXTProfileSnapshot::Decode(
                    Bytes.GetData(), Bytes.Num(), JsonBytes, Checksum, Loaded.AccountId, ClientCopy, Error))) return false;
            TestTrue(TEXT("Menu account equals server battle source in every field"),
                FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Loaded, &ClientCopy, 0));
            TestEqual(TEXT("Party remains six"), ClientCopy.Party.Num(), 6);
            TestEqual(TEXT("Season week remains nine"), ClientCopy.Season.Week, 9);
            TestTrue(TEXT("Gold or Silver grade is retained"), ClientCopy.Ranked.Grade == Grade);
            if (!TestTrue(TEXT("Normal save after re-entry remains enabled"), Reopened->SaveProfile(Loaded))) return false;
            if (!TestTrue(TEXT("Refresh expected durable save timestamp"),
                Reopened->LoadProfile(Loaded.AccountId, Loaded.Username, Committed))) return false;
        }
    }
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
