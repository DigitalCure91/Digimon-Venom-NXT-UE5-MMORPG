#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTScanCore.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRelayProgressionTest,
    "DigimonVenomNXT.Relay.Progression.BadgesChampionshipAndIndependentSave",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTRelayProgressionTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FDigimonPlayerProfile Profile;
    Profile.Story.ParadoxBadges=17; Profile.Story.bFinalEncounterComplete=true;
    Profile.Chronicles.bComplete=true; Profile.Chronicles.bParadoxScanMastery=true;
    DigimonVenomNXTRelay::Reconcile(Profile.Relay);
    TestFalse(TEXT("Second story completion is not a Relay championship"), Profile.Relay.bEverChampion);
    TestFalse(TEXT("Second story completion does not unlock Relay mastery"), Profile.Relay.bFirewallScanMastery);
    TestTrue(TEXT("Both maps of the first region are open"), DigimonVenomNXTRelay::CanEnterMap(Profile.Relay,2));
    TestFalse(TEXT("The next region needs its actual preceding badge"), DigimonVenomNXTRelay::CanEnterMap(Profile.Relay,3));
    FString Error;
    const auto* FirstGym=DigimonVenomNXTRelay::GetNPC(TEXT("lumen_warden"));
    if (!TestNotNull(TEXT("Authored first gym exists"),FirstGym)) return false;
    TestFalse(TEXT("Gym cannot skip its two tamer trials"),DigimonVenomNXTRelay::CanChallenge(Profile.Relay,*FirstGym,Error));
    int32 Battles=0;
    for(const FDigimonRelayNPC& NPC:DigimonVenomNXTRelay::NPCs())
    {
        if(!DigimonVenomNXTRelay::IsBattleRole(NPC.Role) || NPC.Role==EDigimonRelayRole::Challenger) continue;
        TestTrue(TEXT("Authored campaign progresses without a circular prerequisite"),DigimonVenomNXTRelay::CanChallenge(Profile.Relay,NPC,Error));
        const FGuid Battle=FGuid::NewGuid();
        Profile.Relay.PendingBattleId=Battle; Profile.Relay.PendingNPCId=NPC.Id;
        bool First=false;
        TestFalse(TEXT("Wrong battle receipt cannot settle"),DigimonVenomNXTRelay::Settle(Profile.Relay,FGuid::NewGuid(),NPC.Id,true,First));
        TestTrue(TEXT("Matching server-authored victory settles"),DigimonVenomNXTRelay::Settle(Profile.Relay,Battle,NPC.Id,true,First));
        TestTrue(TEXT("Every first authored victory is a first clear"),First);
        TestFalse(TEXT("Replayed settlement cannot grant twice"),DigimonVenomNXTRelay::Settle(Profile.Relay,Battle,NPC.Id,true,First));
        ++Battles;
    }
    TestEqual(TEXT("Exactly 27 campaign battles"),Battles,27);
    TestEqual(TEXT("Exactly eight distinct campaign badges"),Profile.Relay.Badges.Num(),8);
    TestTrue(TEXT("First championship unlocks permanent mastery"),Profile.Relay.bFirewallScanMastery);
    TestTrue(TEXT("All 18 maps open at completion"),DigimonVenomNXTRelay::CanEnterMap(Profile.Relay,18));
    TestEqual(TEXT("Second-story badges remain independent"),Profile.Story.ParadoxBadges,17);
    const auto* Challenger=DigimonVenomNXTRelay::CurrentChallenger(Profile.Relay);
    if(!TestNotNull(TEXT("First title defense exists"),Challenger)) return false;
    const FName Holder=Challenger->Id;
    Profile.Relay.PendingBattleId=FGuid::NewGuid(); Profile.Relay.PendingNPCId=Holder;
    bool First=false;
    TestTrue(TEXT("Title defeat settles"),DigimonVenomNXTRelay::Settle(Profile.Relay,Profile.Relay.PendingBattleId,Holder,false,First));
    TestFalse(TEXT("Loss removes only current title"),Profile.Relay.bIsChampion);
    TestTrue(TEXT("Loss retains mastery and completion"),Profile.Relay.bEverChampion && Profile.Relay.bFirewallScanMastery);
    TestTrue(TEXT("The same holder waits for reclaim"),DigimonVenomNXTRelay::CurrentChallenger(Profile.Relay)->Id==Holder);
    Profile.Relay.PendingBattleId=FGuid::NewGuid(); Profile.Relay.PendingNPCId=Holder;
    TestTrue(TEXT("Reclaim settles"),DigimonVenomNXTRelay::Settle(Profile.Relay,Profile.Relay.PendingBattleId,Holder,true,First));
    TestEqual(TEXT("Reclaim adds a championship, not a defense"),Profile.Relay.ChampionshipWins,2);
    TestEqual(TEXT("Reclaim does not count as successful defense"),Profile.Relay.Defenses,0);
    TestTrue(TEXT("Next challenger follows successful reclaim"),DigimonVenomNXTRelay::CurrentChallenger(Profile.Relay)->Id!=Holder);
    FDigimonRelayProgress PreviousChampion;
    PreviousChampion.bEverChampion=true; PreviousChampion.ChampionshipWins=1;
    DigimonVenomNXTRelay::Reconcile(PreviousChampion);
    TestTrue(TEXT("Previous Relay champions receive mastery automatically"),PreviousChampion.bFirewallScanMastery);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRelayPersistenceTest,
    "DigimonVenomNXT.Relay.Persistence.CheckpointSaveFailureAndReconnect",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTRelayPersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Account=TEXT("Automation_Relay_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString Path=FPaths::Combine(FPaths::ProjectSavedDir(),TEXT("DigimonVenomNXT"),TEXT("Profiles"),Account+TEXT(".json"));
    struct FCleanup { FString Path; ~FCleanup() { IFileManager::Get().DeleteDirectory(*(Path+TEXT(".tmp")),false,true); IFileManager::Get().Delete(*(Path+TEXT(".tmp")),false,true,true); IFileManager::Get().Delete(*Path,false,true,true); } } Cleanup{Path};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    FDigimonPlayerProfile Profile; Profile.AccountId=Account; Profile.Username=TEXT("Relay checkpoint fixture");
    Profile.Relay.bInside=true;
    Profile.Relay.PendingNPCId=TEXT("lumen_trial_1");
    Profile.Relay.PendingBattleId=FGuid::NewGuid();
    FDigimonSeasonBattleCheckpoint Decision;
    Decision.ContextId=TEXT("relay:lumen_trial_1"); Decision.State.Kind=EDigimonBattleKind::Story;
    Decision.State.BattleId=Profile.Relay.PendingBattleId; Decision.State.TurnNumber=7;
    FDigimonBattleUnit Unit; Unit.InstanceId=FGuid::NewGuid(); Unit.SpeciesId=TEXT("agumon"); Unit.HP=17; Unit.SP=9; Unit.Level=20;
    Decision.State.TeamA.Active.Add(Unit); Unit.HP=4; Decision.State.TeamB.Active.Add(Unit);
    FDigimonBattleCommand Command; Command.ExpectedBattleId=Decision.State.BattleId; Command.ExpectedTurnNumber=7; Command.ActingSlot=0;
    Decision.CommandsA.Add(Command);
    if(!TestTrue(TEXT("Serialize exact decision"),FJsonObjectConverter::UStructToJsonObjectString(Decision,Profile.Relay.BattleCheckpointJson)))return false;
    if(!TestTrue(TEXT("Save decision"),Store->SaveProfile(Profile)))return false;
    FDigimonPlayerProfile Reloaded;
    if(!TestTrue(TEXT("Reconnect reads decision"),Store->LoadProfile(Account,Profile.Username,Reloaded)))return false;
    FDigimonSeasonBattleCheckpoint Restored;
    TestTrue(TEXT("Restore checkpoint JSON"),FJsonObjectConverter::JsonObjectStringToUStruct(Reloaded.Relay.BattleCheckpointJson,&Restored,0,0));
    TestEqual(TEXT("Exact turn survives reconnect"),Restored.State.TurnNumber,7);
    TestEqual(TEXT("Exact HP survives reconnect"),Restored.State.TeamA.Active[0].HP,17);
    TestEqual(TEXT("Queued commands survive reconnect"),Restored.CommandsA.Num(),1);
    const FDigimonPlayerProfile Before=Profile;
    bool Settled=false;
    auto Mutate=[&Settled](FDigimonPlayerProfile& P){ bool First=false; Settled=DigimonVenomNXTRelay::Settle(P.Relay,P.Relay.PendingBattleId,P.Relay.PendingNPCId,true,First); P.Credits+=350; };
    auto Save=[&Store](const FDigimonPlayerProfile& P){return Store->SaveProfile(P);};
    if(!TestTrue(TEXT("Create save-failure fixture"),IFileManager::Get().MakeDirectory(*(Path+TEXT(".tmp")),true)))return false;
    TestFalse(TEXT("Failed save refuses whole settlement"),DigimonVenomNXTScanCore::Commit(Profile,Mutate,Save));
    TestTrue(TEXT("Victory was valid before simulated save failure"),Settled);
    TestTrue(TEXT("Failed save restores exact in-memory checkpoint, currency and receipt"),FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Profile,&Before,0));
    Store->LoadProfile(Account,Profile.Username,Reloaded);
    TestFalse(TEXT("Failed save cannot publish a durable clear"),Reloaded.Relay.DefeatedTamers.Contains(TEXT("lumen_trial_1")));
    TestTrue(TEXT("Release save-failure fixture"),IFileManager::Get().DeleteDirectory(*(Path+TEXT(".tmp")),false,true));
    TestTrue(TEXT("Retry commits once"),DigimonVenomNXTScanCore::Commit(Profile,Mutate,Save));
    Store->LoadProfile(Account,Profile.Username,Reloaded);
    TestTrue(TEXT("Successful settlement clears saved battle"),Reloaded.Relay.BattleCheckpointJson.IsEmpty());
    TestTrue(TEXT("Successful receipt survives reconnect"),Reloaded.Relay.LastSettledBattleId==Before.Relay.PendingBattleId);
    bool First=false;
    TestFalse(TEXT("Reconnect cannot replay old victory receipt"),DigimonVenomNXTRelay::Settle(Reloaded.Relay,Before.Relay.PendingBattleId,Before.Relay.PendingNPCId,true,First));
    return true;
}
#endif
