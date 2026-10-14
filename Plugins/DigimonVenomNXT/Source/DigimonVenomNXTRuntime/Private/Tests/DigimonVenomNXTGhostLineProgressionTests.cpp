#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTGhostLine.h"
#include "Misc/AutomationTest.h"
#include "JsonObjectConverter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTGhostLineProgressionTest,
    "DigimonVenomNXT.GhostLine.Progression.AllThirtyCasesReceiptsRevealAndEnding",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTGhostLineProgressionTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FDigimonRelayProgress P;
    FString Dialogue, Error;
    int32 Trials = 0;
    for (int32 Field = 1; Field <= 30; ++Field)
    {
        const FName QuestId(*FString::Printf(TEXT("ghost_%02d_quest"), Field));
        const FName TrialId = Field == 30 ? FName(TEXT("ghost_final_regent")) : FName(*FString::Printf(TEXT("ghost_%02d_trainer"), Field));
        const auto* Quest = DigimonVenomNXTGhostLine::GetNPC(QuestId);
        const auto* Trial = DigimonVenomNXTGhostLine::GetNPC(TrialId);
        if (!TestNotNull(TEXT("Every field has its exact case"), Quest) || !TestNotNull(TEXT("Every field has its exact encounter"), Trial)) return false;
        TestTrue(TEXT("Preceding evidence opens exact next map"), DigimonVenomNXTGhostLine::CanEnterMap(P, Field + 1));
        TestFalse(TEXT("Encounter cannot start before case acceptance"), DigimonVenomNXTGhostLine::CanChallenge(P, *Trial, Error));
        TestTrue(TEXT("Case acceptance succeeds"), DigimonVenomNXTGhostLine::AdvanceQuest(P, *Quest, Dialogue, Error));
        TestTrue(TEXT("Acceptance is recorded under exact quest ID"), P.AcceptedQuests.Contains(QuestId));
        TestFalse(TEXT("Acceptance alone grants no report or proof"), P.CompletedObjectives.Contains(QuestId));
        if (Field < 30)
        {
            TestFalse(TEXT("Cannot confirm case before its exact witness victory"), DigimonVenomNXTGhostLine::AdvanceQuest(P, *Quest, Dialogue, Error));
            TestTrue(TEXT("Accepted encounter now available"), DigimonVenomNXTGhostLine::CanChallenge(P, *Trial, Error));
            const FGuid Battle = FGuid::NewGuid();
            P.PendingBattleId = Battle; P.PendingNPCId = TrialId;
            P.BattleCheckpointJson = TEXT("{\"exactTurn\":7}");
            bool First = true;
            TestFalse(TEXT("Wrong battle receipt rejected"), DigimonVenomNXTGhostLine::Settle(P, FGuid::NewGuid(), TrialId, true, First));
            TestFalse(TEXT("Forged receipt cannot receive first-clear payout"), First);
            TestEqual(TEXT("Rejected receipt preserves saved decision"), P.BattleCheckpointJson, FString(TEXT("{\"exactTurn\":7}")));
            TestTrue(TEXT("Legitimate loss settles"), DigimonVenomNXTGhostLine::Settle(P, Battle, TrialId, false, First));
            TestFalse(TEXT("Loss has no first-clear reward"), First);
            TestFalse(TEXT("Loss creates no hacked witness marker"), P.CompletedObjectives.Contains(FName(*(TEXT("hacked:") + TrialId.ToString()))));
            P.PendingBattleId = FGuid::NewGuid(); P.PendingNPCId = TrialId;
            const FGuid VictoryReceipt = P.PendingBattleId;
            TestTrue(TEXT("Exact first victory settles"), DigimonVenomNXTGhostLine::Settle(P, VictoryReceipt, TrialId, true, First));
            TestTrue(TEXT("First victory qualifies once"), First); ++Trials;
            TestFalse(TEXT("Receipt replay rejected"), DigimonVenomNXTGhostLine::Settle(P, VictoryReceipt, TrialId, true, First));
            TestFalse(TEXT("Witness cannot be rematched after first victory"), DigimonVenomNXTGhostLine::CanChallenge(P, *Trial, Error));
            TestFalse(TEXT("Victory cannot open forward route before report"), DigimonVenomNXTGhostLine::CanEnterMap(P, Field + 2));
            if (Field == 26)
            {
                TestFalse(TEXT("Trial victory does not reveal culprit"), DigimonVenomNXTGhostLine::IsRevealed(P));
                const auto* Confession = DigimonVenomNXTGhostLine::GetNPC(TEXT("ghost_26_mara"));
                if (TestNotNull(TEXT("Earned confession actor exists"), Confession)) TestFalse(TEXT("Confession hidden until report"), DigimonVenomNXTGhostLine::IsNPCVisible(P, *Confession));
                TestTrue(TEXT("Repeat witness dialogue is readable before reveal"), DigimonVenomNXTGhostLine::Interact(P, *Trial, Dialogue, Error));
                TestFalse(TEXT("Unreported witness cannot announce earned verdict"), Dialogue.Contains(TEXT("Mara Vale is the Null Regent")));
            }
        }
        TestEqual(TEXT("Exact objective permits report"), DigimonVenomNXTGhostLine::QuestObjectiveCount(P, QuestId), 1);
        TestTrue(TEXT("Explicit turn-in completes case"), DigimonVenomNXTGhostLine::AdvanceQuest(P, *Quest, Dialogue, Error));
        TestTrue(TEXT("Turn-in stores report and permanent numbered proof"), P.CompletedObjectives.Contains(QuestId) && P.Badges.Contains(Quest->BadgeId));
        TestFalse(TEXT("Repeat report cannot award again"), DigimonVenomNXTGhostLine::AdvanceQuest(P, *Quest, Dialogue, Error));
        TestTrue(TEXT("Reveal exists exactly after field26 report"), DigimonVenomNXTGhostLine::IsRevealed(P) == (Field >= 26));
        const auto* HubFriend = DigimonVenomNXTGhostLine::GetNPC(TEXT("ghost_hub_mara"));
        if (TestNotNull(TEXT("Stable hub friend actor exists"), HubFriend)) TestTrue(TEXT("Old friendly contact retires on reveal"), DigimonVenomNXTGhostLine::IsNPCVisible(P, *HubFriend) == (Field < 26));
        // Real reflected JSON serialization of every intermediate case, including
        // historical hacking markers, reports, proofs and accepted assignments.
        FString Saved;
        if (!TestTrue(TEXT("Progress serializes after each report"), FJsonObjectConverter::UStructToJsonObjectString(P, Saved))) return false;
        FDigimonRelayProgress Reloaded;
        if (!TestTrue(TEXT("Progress reloads after each report"), FJsonObjectConverter::JsonObjectStringToUStruct(Saved, &Reloaded, 0, 0))) return false;
        DigimonVenomNXTGhostLine::Reconcile(Reloaded);
        TestTrue(TEXT("Reports survive actual profile JSON round trip"), Reloaded.CompletedObjectives == P.CompletedObjectives);
        TestTrue(TEXT("Proofs survive actual profile JSON round trip"), Reloaded.Badges == P.Badges);
        P = MoveTemp(Reloaded);
    }
    TestEqual(TEXT("Final audit does not invent a thirtieth trial"), Trials, 29);
    TestEqual(TEXT("Final case yields all thirty proofs before final battle"), P.Badges.Num(), 30);
    TestFalse(TEXT("Proofs alone do not complete campaign or grant reward"), P.bComplete || P.bShinyScanMastery);
    const auto* Final = DigimonVenomNXTGhostLine::GetNPC(TEXT("ghost_final_regent"));
    if (!TestNotNull(TEXT("Final encounter exists"), Final)) return false;
    TestTrue(TEXT("Sealed archive permits final battle"), DigimonVenomNXTGhostLine::CanChallenge(P, *Final, Error));
    P.PendingBattleId = FGuid::NewGuid(); P.PendingNPCId = Final->Id;
    bool First = false;
    TestTrue(TEXT("Final loss settles without losing case"), DigimonVenomNXTGhostLine::Settle(P, P.PendingBattleId, Final->Id, false, First));
    TestFalse(TEXT("Final loss cannot grant mastery"), P.bShinyScanMastery);
    TestTrue(TEXT("Final loss permits same authored rematch"), DigimonVenomNXTGhostLine::CanChallenge(P, *Final, Error));
    P.PendingBattleId = FGuid::NewGuid(); P.PendingNPCId = Final->Id;
    TestTrue(TEXT("Final victory closes campaign"), DigimonVenomNXTGhostLine::Settle(P, P.PendingBattleId, Final->Id, true, First));
    TestTrue(TEXT("Completion and Shiny mastery durable"), First && P.bComplete && P.bShinyScanMastery);
    TestFalse(TEXT("Final cannot be replayed after completion"), DigimonVenomNXTGhostLine::CanChallenge(P, *Final, Error));
    TestTrue(TEXT("Ending is surviving Iona transmission"), DigimonVenomNXTGhostLine::Epilogue(P).StartsWith(TEXT("Iona:")));
    int32 HiddenMaraActors = 0;
    for (const auto& N : DigimonVenomNXTGhostLine::NPCs())
    {
        if (N.CharacterId == TEXT("mara_vale")) { ++HiddenMaraActors; TestFalse(TEXT("All Mara contacts disappear permanently"), DigimonVenomNXTGhostLine::IsNPCVisible(P, N)); }
        else TestTrue(TEXT("Surviving witnesses and services remain visible"), DigimonVenomNXTGhostLine::IsNPCVisible(P, N));
    }
    TestEqual(TEXT("All seventeen Mara appearances checked"), HiddenMaraActors, 17);
    for (const auto& N : DigimonVenomNXTGhostLine::NPCs())
        if (N.bHackedAfterVictory) TestTrue(TEXT("Every authored hacking incident survives completion"), P.CompletedObjectives.Contains(FName(*(TEXT("hacked:") + N.Id.ToString()))));
    return true;
}
#endif
