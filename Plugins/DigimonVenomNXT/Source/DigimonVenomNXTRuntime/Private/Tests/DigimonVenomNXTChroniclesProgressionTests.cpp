#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTChronicles.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonChroniclesProgressionTest, "DigimonVenomNXT.Chronicles.FullCampaignProgression", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonChroniclesProgressionTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const auto Campaign = EDigimonPrivateCampaign::ParadoxChronicles;
    FDigimonPlayerProfile Profile;
    DigimonVenomNXTCampaign::Reconcile(Profile);
    FDigimonRelayProgress& P = Profile.Chronicles;
    FString Error, Dialogue;
    TestEqual(TEXT("18 maps"), DigimonVenomNXTChronicles::Maps().Num(), 18);
    TestEqual(TEXT("92 world NPCs"), DigimonVenomNXTChronicles::NPCs().Num(), 92);
    const FDigimonRelayNPC* Final = DigimonVenomNXTChronicles::GetNPC(TEXT("ds_final_triad"));
    if (!TestNotNull(TEXT("Final encounter exists"), Final)) return false;
    auto Win = [&](const FDigimonRelayNPC& NPC, bool ExpectedFirst)
    {
        const FGuid BattleId = FGuid::NewGuid();
        P.PendingBattleId = BattleId; P.PendingNPCId = NPC.Id;
        bool First = false;
        TestTrue(TEXT("Settle authenticated pending attempt"), DigimonVenomNXTCampaign::Settle(Campaign, P, BattleId, NPC.Id, true, First));
        TestEqual(TEXT("First clear fence"), First, ExpectedFirst);
        TestFalse(TEXT("Duplicate result rejected"), DigimonVenomNXTCampaign::Settle(Campaign, P, BattleId, NPC.Id, true, First));
    };
    for (int32 MapId=2; MapId<=18; ++MapId)
    {
        P.MapId = MapId;
        const auto FieldNPCs = DigimonVenomNXTChronicles::NPCsForMap(MapId);
        const auto* Quest = FieldNPCs.FindByPredicate([](const auto& N) { return N.Role == EDigimonRelayRole::Quest; });
        const auto* Tamer = FieldNPCs.FindByPredicate([](const auto& N) { return N.Role == EDigimonRelayRole::Tamer; });
        const auto* Guardian = FieldNPCs.FindByPredicate([](const auto& N) { return N.Role == EDigimonRelayRole::ParadoxBoss; });
        if (!Quest || !Tamer || !Guardian) { AddError(TEXT("Authored field chain is missing")); return false; }
        TestTrue(TEXT("Current field unlocked"), DigimonVenomNXTChronicles::CanEnterMap(P, MapId));
        if (MapId<18) TestFalse(TEXT("Next field locked"), DigimonVenomNXTChronicles::CanEnterMap(P, MapId+1));
        TestFalse(TEXT("Final locked before guardian17"), DigimonVenomNXTChronicles::CanChallenge(P, *Final, Error));
        TestFalse(TEXT("Tamer requires accepted assignment"), DigimonVenomNXTChronicles::CanChallenge(P,*Tamer,Error));
        TestEqual(TEXT("Unaccepted assignment has no objective progress"),DigimonVenomNXTChronicles::QuestObjectiveCount(P,Quest->QuestId),0);
        TestTrue(TEXT("Dialogue can open"), DigimonVenomNXTChronicles::Interact(P,*Quest,Dialogue,Error));
        TestFalse(TEXT("Merely opening dialogue does not accept"),P.AcceptedQuests.Contains(Quest->QuestId));
        TestTrue(TEXT("Explicit accept succeeds"), DigimonVenomNXTChronicles::AdvanceQuest(P,*Quest,Dialogue,Error));
        TestEqual(TEXT("Acceptance alone cannot complete trial"),DigimonVenomNXTChronicles::QuestObjectiveCount(P,Quest->QuestId),0);
        TestFalse(TEXT("Premature turn-in rejected"), DigimonVenomNXTChronicles::AdvanceQuest(P,*Quest,Dialogue,Error));
        TestTrue(TEXT("Accepted assignment opens trial"), DigimonVenomNXTChronicles::CanChallenge(P,*Tamer,Error));
        TestFalse(TEXT("Guardian requires trial"), DigimonVenomNXTChronicles::CanChallenge(P,*Guardian,Error));
        Win(*Tamer,true);
        TestEqual(TEXT("Battle objective derives from saved victory"),DigimonVenomNXTChronicles::QuestObjectiveCount(P,Quest->QuestId),1);
        const FDigimonRelayProgress ReplicatedProgress = P;
        TestEqual(TEXT("Dialogue snapshot derives identical objective progress"),DigimonVenomNXTChronicles::QuestObjectiveCount(ReplicatedProgress,Quest->QuestId),1);
        TestEqual(TEXT("Unknown assignment cannot have progress"),DigimonVenomNXTChronicles::QuestObjectiveCount(P,TEXT("unknown_quest")),0);
        TestEqual(TEXT("A tamer ID is not a quest ID"),DigimonVenomNXTChronicles::QuestObjectiveCount(P,Tamer->Id),0);
        TestFalse(TEXT("Trial does not auto turn-in quest"),P.CompletedObjectives.Contains(Quest->QuestId));
        TestFalse(TEXT("Guardian requires explicit return and turn-in"),DigimonVenomNXTChronicles::CanChallenge(P,*Guardian,Error));
        TestTrue(TEXT("Turn-in succeeds"),DigimonVenomNXTChronicles::AdvanceQuest(P,*Quest,Dialogue,Error));
        TestTrue(TEXT("Guardian opens after turn-in"),DigimonVenomNXTChronicles::CanChallenge(P,*Guardian,Error));
        Win(*Guardian,true);
        TestTrue(TEXT("Unique crest saved"),P.Badges.Contains(Guardian->BadgeId));
    }
    TestTrue(TEXT("All17 open final"),DigimonVenomNXTChronicles::CanChallenge(P,*Final,Error));
    for (FName Crest : Final->RequiresBadges)
    {
        P.Badges.Remove(Crest);
        TestFalse(TEXT("Every exact crest is required"),DigimonVenomNXTChronicles::CanChallenge(P,*Final,Error));
        P.Badges.Add(Crest);
    }
    for (FName Guardian : Final->RequiresCompleted)
    {
        P.DefeatedTamers.Remove(Guardian);
        TestFalse(TEXT("Every exact guardian is required"),DigimonVenomNXTChronicles::CanChallenge(P,*Final,Error));
        P.DefeatedTamers.Add(Guardian);
    }
    Win(*Final,true);
    TestTrue(TEXT("Completion persisted"),P.bComplete);
    TestTrue(TEXT("Paradox mastery earned"),P.bParadoxScanMastery);
    TestFalse(TEXT("Chronicles never grants Shiny mastery"),Profile.Relay.bShinyScanMastery);
    Win(*Final,false);
    const FGuid DefeatId=FGuid::NewGuid();P.PendingBattleId=DefeatId;P.PendingNPCId=Final->Id;
    bool First=false;
    TestTrue(TEXT("Final replay defeat settles"),DigimonVenomNXTChronicles::Settle(P,DefeatId,Final->Id,false,First));
    TestTrue(TEXT("Replay defeat retains completion and mastery"),P.bComplete && P.bParadoxScanMastery);
    TestFalse(TEXT("Stable reconcile is idempotent"),DigimonVenomNXTChronicles::Reconcile(P));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonChroniclesProfileAuthorityTest, "DigimonVenomNXT.Chronicles.NativeProfileAuthorityAndMasteryIsolation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonChroniclesProfileAuthorityTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FDigimonPlayerProfile CountOnly;
    CountOnly.Story.Chapter=18; CountOnly.Story.ParadoxBadges=17;
    CountOnly.Story.DefeatedBossChapters={2,3,4};
    CountOnly.Story.bFinalEncounterUnlocked=true; CountOnly.Story.bFinalEncounterComplete=true;
    DigimonVenomNXTCampaign::Reconcile(CountOnly);
    TestEqual(TEXT("Unrelated story counters cannot invent native crest ownership"),CountOnly.Chronicles.Badges.Num(),0);
    TestFalse(TEXT("Only native World DS achievements determine completion"),CountOnly.Chronicles.bComplete);
    TestFalse(TEXT("Unrelated story completion cannot invent Paradox mastery"),CountOnly.Chronicles.bParadoxScanMastery);

    FDigimonPlayerProfile Native;
    Native.Relay.bEverChampion=true;
    Native.Chronicles.DefeatedTamers.Add(TEXT("ds_final_triad"));
    DigimonVenomNXTCampaign::Reconcile(Native);
    TestTrue(TEXT("Native Dawn championship grants Firewall"),Native.Relay.bFirewallScanMastery);
    TestTrue(TEXT("Native World DS final receipt grants Paradox"),Native.Chronicles.bComplete && Native.Chronicles.bParadoxScanMastery);
    TestFalse(TEXT("Neither completed route can grant Super Xros Wars mastery"),Native.GhostLine.bShinyScanMastery);
    TestEqual(TEXT("Dawn Firewall victory adds20 percent"),DigimonVenomNXTCampaign::ScanGain(Native,EDigimonVariant::Firewall,5,true),6);
    TestEqual(TEXT("World DS Paradox victory adds20 percent"),DigimonVenomNXTCampaign::ScanGain(Native,EDigimonVariant::Paradox,5,true),6);
    TestEqual(TEXT("Shiny remains independent"),DigimonVenomNXTCampaign::ScanGain(Native,EDigimonVariant::Shiny,5,true),5);
    TestEqual(TEXT("Non-wild scanning receives no permanent bonus"),DigimonVenomNXTCampaign::ScanGain(Native,EDigimonVariant::Paradox,5,false),5);
    TestFalse(TEXT("Native profile reconciliation is idempotent"),DigimonVenomNXTCampaign::Reconcile(Native));

    // Unrecognized JSON counters must not manufacture an exact native victory.
    FDigimonPlayerProfile Counter;
    TestTrue(TEXT("Obsolete counter JSON can be ignored safely"),FJsonObjectConverter::JsonObjectStringToUStruct(
        TEXT("{\"chronicles\":{\"acceptedQuests\":[\"ds_green_quest\"],\"questCounters\":{\"ds_green_quest\":99}}}"), &Counter,0,0));
    TestEqual(TEXT("Fabricated counter cannot complete a witness trial"),DigimonVenomNXTChronicles::QuestObjectiveCount(Counter.Chronicles,TEXT("ds_green_quest")),0);
    Counter.Chronicles.DefeatedTamers.Add(TEXT("ds_green_trainer"));
    FString Saved;
    TestTrue(TEXT("Native profile serializes"),FJsonObjectConverter::UStructToJsonObjectString(Counter,Saved));
    TestFalse(TEXT("Unrecognized counter is not saved or replicated"),Saved.Contains(TEXT("questCounters")));
    FDigimonPlayerProfile Restored;
    TestTrue(TEXT("Native profile reloads"),FJsonObjectConverter::JsonObjectStringToUStruct(Saved,&Restored,0,0));
    TestEqual(TEXT("Exact native victory survives reload"),DigimonVenomNXTChronicles::QuestObjectiveCount(Restored.Chronicles,TEXT("ds_green_quest")),1);
    return true;
}
#endif
