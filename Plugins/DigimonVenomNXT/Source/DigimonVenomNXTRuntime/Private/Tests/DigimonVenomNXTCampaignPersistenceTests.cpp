#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTScanCore.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTCampaignCheckpointTest,
    "DigimonVenomNXT.Chronicles.Persistence.CampaignIdentityWildCheckpointAndAtomicRetry",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTCampaignCheckpointTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Account = TEXT("Automation_Chronicles_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString Path = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Profiles"), Account + TEXT(".json"));
    struct FCleanup
    {
        FString Path;
        ~FCleanup()
        {
            IFileManager::Get().DeleteDirectory(*(Path + TEXT(".tmp")), false, true);
            IFileManager::Get().Delete(*(Path + TEXT(".tmp")), false, true, true);
            IFileManager::Get().Delete(*Path, false, true, true);
        }
    } Cleanup{Path};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    FDigimonPlayerProfile Profile;
    Profile.AccountId = Account; Profile.Username = TEXT("Independent campaign fixture");
    Profile.Relay.ChampionshipWins = 1; Profile.Relay.bEverChampion = true;
    Profile.ActiveStoryCampaign = EDigimonPrivateCampaign::ParadoxChronicles;
    Profile.Chronicles.bInside = true; Profile.Chronicles.MapId = 2;
    Profile.Chronicles.PendingNPCId = TEXT("wild:2"); Profile.Chronicles.PendingBattleId = FGuid::NewGuid();
    DigimonVenomNXTCampaign::Reconcile(Profile);
    const FDigimonRelayProgress RelayBefore = Profile.Relay;
    FDigimonSeasonBattleCheckpoint Decision;
    Decision.ContextId = TEXT("chronicles:wild:2"); Decision.State.Kind = EDigimonBattleKind::Wild;
    Decision.State.BattleId = Profile.Chronicles.PendingBattleId; Decision.State.TurnNumber = 9;
    FDigimonBattleUnit Unit;
    Unit.InstanceId = FGuid::NewGuid(); Unit.SpeciesId = TEXT("agumon"); Unit.Level = 17; Unit.HP = 23; Unit.SP = 7;
    Decision.State.TeamA.Active.Add(Unit); Unit.InstanceId = FGuid::NewGuid(); Unit.HP = 4; Decision.State.TeamB.Active.Add(Unit);
    FDigimonBattleCommand Command;
    Command.ExpectedBattleId = Decision.State.BattleId; Command.ExpectedTurnNumber = 9; Command.ActingSlot = 0;
    Decision.CommandsA.Add(Command);
    if (!TestTrue(TEXT("Serialize private wild decision"), FJsonObjectConverter::UStructToJsonObjectString(Decision, Profile.Chronicles.BattleCheckpointJson))) return false;
    if (!TestTrue(TEXT("Persist private wild decision"), Store->SaveProfile(Profile))) return false;
    FDigimonPlayerProfile Reloaded;
    if (!TestTrue(TEXT("Reconnect restores campaign checkpoint"), Store->LoadProfile(Account, Profile.Username, Reloaded))) return false;
    FDigimonSeasonBattleCheckpoint Restored;
    if (!TestTrue(TEXT("Saved decision parses"), FJsonObjectConverter::JsonObjectStringToUStruct(Reloaded.Chronicles.BattleCheckpointJson, &Restored, 0, 0))) return false;
    TestEqual(TEXT("Checkpoint retains campaign and field map binding"), Restored.ContextId, FString(TEXT("chronicles:wild:2")));
    TestEqual(TEXT("No turn reroll on reconnect"), Restored.State.TurnNumber, 9);
    TestEqual(TEXT("Exact real-party HP survives reconnect"), Restored.State.TeamA.Active[0].HP, 23);
    TestEqual(TEXT("Exact real-party SP survives reconnect"), Restored.State.TeamA.Active[0].SP, 7);
    TestEqual(TEXT("Already queued decision survives reconnect"), Restored.CommandsA.Num(), 1);
    TestTrue(TEXT("Relay history remains separate"), FDigimonRelayProgress::StaticStruct()->CompareScriptStruct(&Reloaded.Relay, &RelayBefore, 0));
    TestTrue(TEXT("Native Dawn champion retains permanent Firewall mastery"), Reloaded.Relay.bFirewallScanMastery);
    TestFalse(TEXT("Relay evidence cannot unlock Chronicles mastery"), Reloaded.Chronicles.bParadoxScanMastery);
    TestEqual(TEXT("Dawn mastery applies to Firewall wild wins"), DigimonVenomNXTCampaign::ScanGain(Reloaded, EDigimonVariant::Firewall, 5, true), 6);
    TestEqual(TEXT("Relay mastery does not leak into Paradox wild wins"), DigimonVenomNXTCampaign::ScanGain(Reloaded, EDigimonVariant::Paradox, 5, true), 5);
    const FDigimonPlayerProfile Before = Profile;
    auto Mutate = [](FDigimonPlayerProfile& Candidate)
    {
        Candidate.Chronicles.LastSettledBattleId = Candidate.Chronicles.PendingBattleId;
        Candidate.Chronicles.PendingBattleId.Invalidate(); Candidate.Chronicles.PendingNPCId = NAME_None;
        Candidate.Chronicles.BattleCheckpointJson.Reset(); Candidate.Credits += 340;
    };
    auto Save = [&Store](const FDigimonPlayerProfile& Candidate) { return Store->SaveProfile(Candidate); };
    if (!TestTrue(TEXT("Simulate unavailable commit destination"), IFileManager::Get().MakeDirectory(*(Path + TEXT(".tmp")), true))) return false;
    TestFalse(TEXT("Failed save rejects complete settlement"), DigimonVenomNXTScanCore::Commit(Profile, Mutate, Save));
    TestTrue(TEXT("Failure preserves receipt, checkpoint and currency together"), FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Profile, &Before, 0));
    Store->LoadProfile(Account, Profile.Username, Reloaded);
    TestEqual(TEXT("Failure cannot erase saved decision"), Reloaded.Chronicles.BattleCheckpointJson, Before.Chronicles.BattleCheckpointJson);
    if (!TestTrue(TEXT("Restore commit destination"), IFileManager::Get().DeleteDirectory(*(Path + TEXT(".tmp")), false, true))) return false;
    TestTrue(TEXT("One retry commits complete settlement"), DigimonVenomNXTScanCore::Commit(Profile, Mutate, Save));
    Store->LoadProfile(Account, Profile.Username, Reloaded);
    TestTrue(TEXT("Settled checkpoint stays cleared after reconnect"), Reloaded.Chronicles.BattleCheckpointJson.IsEmpty());
    TestTrue(TEXT("Settled battle receipt survives reconnect"), Reloaded.Chronicles.LastSettledBattleId == Before.Chronicles.PendingBattleId);
    TestEqual(TEXT("Retry awards once"), Reloaded.Credits, Before.Credits + 340);
    TestTrue(TEXT("Chronicles settlement cannot alter Relay history"), FDigimonRelayProgress::StaticStruct()->CompareScriptStruct(&Reloaded.Relay, &RelayBefore, 0));
    return true;
}
#endif
