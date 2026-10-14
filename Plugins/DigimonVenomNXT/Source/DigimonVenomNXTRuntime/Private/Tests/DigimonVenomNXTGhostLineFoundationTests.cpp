#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTRelaySessionCore.h"
#include "Misc/AutomationTest.h"
#include "JsonObjectConverter.h"

static_assert(static_cast<uint8>(EDigimonPrivateCampaign::Relay) == 0, "Relay save identity must remain stable");
static_assert(static_cast<uint8>(EDigimonPrivateCampaign::ParadoxChronicles) == 1, "Chronicles save identity must remain stable");
static_assert(static_cast<uint8>(EDigimonPrivateCampaign::GhostLine) == 2, "GhostLine is appended, never inserted");

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTGhostLineFoundationTest,
    "DigimonVenomNXT.GhostLine.Persistence.ContextIdentityIndependentMasteryAndCheckpointIsolation",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTGhostLineFoundationTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    for (EDigimonPrivateCampaign Campaign : {EDigimonPrivateCampaign::Relay, EDigimonPrivateCampaign::ParadoxChronicles, EDigimonPrivateCampaign::GhostLine})
    {
        EDigimonPrivateCampaign Parsed = EDigimonPrivateCampaign::Relay;
        FName NPCId;
        TestTrue(TEXT("Exact campaign context parses"), DigimonVenomNXTCampaign::TryParseContext(DigimonVenomNXTCampaign::ContextPrefix(Campaign) + TEXT("wild:2"), Parsed, NPCId));
        TestTrue(TEXT("Context retains its own campaign"), Parsed == Campaign);
        TestEqual(TEXT("Context retains complete encounter payload"), NPCId, FName(TEXT("wild:2")));
    }
    EDigimonPrivateCampaign UntouchedCampaign = EDigimonPrivateCampaign::GhostLine;
    FName UntouchedNPC(TEXT("original"));
    for (const FString& Invalid : {FString(TEXT("GhostLine:boss")), FString(TEXT("ghostline:")), FString(TEXT("ghostline:None")), FString(TEXT("unknown:boss"))})
    {
        TestFalse(TEXT("Unknown or empty context fails closed"), DigimonVenomNXTCampaign::TryParseContext(Invalid, UntouchedCampaign, UntouchedNPC));
        TestTrue(TEXT("Parse failure does not redirect another campaign"), UntouchedCampaign == EDigimonPrivateCampaign::GhostLine);
        TestEqual(TEXT("Parse failure does not replace encounter identity"), UntouchedNPC, FName(TEXT("original")));
    }
    const auto InvalidCampaign = static_cast<EDigimonPrivateCampaign>(99);
    TestFalse(TEXT("Unknown campaign identity rejected"), DigimonVenomNXTCampaign::IsValid(InvalidCampaign));
    TestTrue(TEXT("Unknown campaign cannot inherit Relay maps"), DigimonVenomNXTCampaign::Maps(InvalidCampaign).IsEmpty());
    TestTrue(TEXT("Unknown campaign cannot inherit Relay opponents"), DigimonVenomNXTCampaign::NPCs(InvalidCampaign).IsEmpty());

    FDigimonPlayerProfile Independent;
    Independent.AccountId = TEXT("GhostLineFoundationFixture");
    Independent.Username = TEXT("Independent journeys");
    Independent.Relay.bEverChampion = true;
    Independent.Relay.ChampionshipWins = 1;
    Independent.Chronicles.DefeatedTamers.Add(TEXT("ds_final_triad"));
    DigimonVenomNXTCampaign::Reconcile(Independent);
    TestTrue(TEXT("Dawn champion retains Firewall mastery"), Independent.Relay.bFirewallScanMastery);
    TestTrue(TEXT("Native World DS final victory grants Paradox mastery"), Independent.Chronicles.bParadoxScanMastery);
    TestFalse(TEXT("Other campaigns cannot complete Super Xros Wars"), Independent.GhostLine.bComplete);
    TestFalse(TEXT("Other campaigns cannot grant Shiny mastery"), Independent.GhostLine.bShinyScanMastery);
    TestEqual(TEXT("Dawn Firewall mastery preserves configured base plus20 percent"), DigimonVenomNXTCampaign::ScanGain(Independent, EDigimonVariant::Firewall, 25, true), 30);

    FDigimonPlayerProfile Candidate = Independent;
    Candidate.GhostLine.DefeatedTamers.Add(TEXT("ghost_final_regent"));
    DigimonVenomNXTCampaign::Reconcile(Candidate);
    TestTrue(TEXT("Native Super Xros Wars final victory grants Shiny mastery"), Candidate.GhostLine.bShinyScanMastery);
    TestEqual(TEXT("Shiny victory grants base plus20 percent"), DigimonVenomNXTCampaign::ScanGain(Candidate, EDigimonVariant::Shiny, 25, true), 30);
    TestEqual(TEXT("Normal scanning retains configured amount"), DigimonVenomNXTCampaign::ScanGain(Candidate, EDigimonVariant::Normal, 6, true), 6);
    TestEqual(TEXT("Non-wild zero scan remains zero"), DigimonVenomNXTCampaign::ScanGain(Candidate, EDigimonVariant::Firewall, 0, false), 0);
    TestEqual(TEXT("Dawn completion remains independent"), DigimonVenomNXTCampaign::ScanGain(Candidate, EDigimonVariant::Firewall, 5, true), 6);
    TestEqual(TEXT("Paradox completion remains independent"), DigimonVenomNXTCampaign::ScanGain(Candidate, EDigimonVariant::Paradox, 5, true), 6);

    // A damaged host save containing competing decisions must remain recoverable.
    // Reconciliation may normalize content, but it must not choose and erase a battle.
    Candidate.ActiveStoryCampaign = EDigimonPrivateCampaign::GhostLine;
    Candidate.Relay.bInside = true;
    Candidate.GhostLine.bInside = true;
    Candidate.Relay.PendingBattleId = FGuid::NewGuid();
    Candidate.GhostLine.PendingBattleId = FGuid::NewGuid();
    Candidate.Relay.PendingNPCId = TEXT("wild:1");
    Candidate.GhostLine.PendingNPCId = TEXT("wild:31");
    Candidate.Relay.BattleCheckpointJson = TEXT("{\"retained\":\"relay\"}");
    Candidate.GhostLine.BattleCheckpointJson = TEXT("{\"retained\":\"ghostline\"}");
    const FGuid RelayId = Candidate.Relay.PendingBattleId, GhostId = Candidate.GhostLine.PendingBattleId;
    DigimonVenomNXTCampaign::Reconcile(Candidate);
    TestTrue(TEXT("Conflicting inside states are not silently discarded"), Candidate.Relay.bInside && Candidate.GhostLine.bInside);
    TestTrue(TEXT("All pending campaign decisions lock party operations"), DigimonVenomNXTCampaign::HasPendingBattle(Candidate));
    TestTrue(TEXT("Other campaign checkpoint blocks GhostLine battle launch"), DigimonVenomNXTCampaign::HasOtherPendingBattle(Candidate, EDigimonPrivateCampaign::GhostLine));
    TestTrue(TEXT("Other campaign checkpoint blocks Relay battle launch"), DigimonVenomNXTCampaign::HasOtherPendingBattle(Candidate, EDigimonPrivateCampaign::Relay));
    TestEqual(TEXT("Conflicting campaign decisions refuse restoration"), DigimonVenomNXTRelaySessionCore::SavedCampaign(2,true,false,true,false,true,true), -2);
    FString Json;
    if (!TestTrue(TEXT("Three campaigns serialize in one account profile"), FJsonObjectConverter::UStructToJsonObjectString(Candidate, Json))) return false;
    FDigimonPlayerProfile Reloaded;
    if (!TestTrue(TEXT("Three campaigns deserialize independently"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Reloaded, 0, 0))) return false;
    DigimonVenomNXTCampaign::Reconcile(Reloaded);
    TestTrue(TEXT("Relay pending GUID survives reconciliation and reload"), Reloaded.Relay.PendingBattleId == RelayId);
    TestTrue(TEXT("GhostLine pending GUID survives reconciliation and reload"), Reloaded.GhostLine.PendingBattleId == GhostId);
    TestEqual(TEXT("Relay exact saved decision remains intact"), Reloaded.Relay.BattleCheckpointJson, Candidate.Relay.BattleCheckpointJson);
    TestEqual(TEXT("GhostLine exact saved decision remains intact"), Reloaded.GhostLine.BattleCheckpointJson, Candidate.GhostLine.BattleCheckpointJson);
    TestTrue(TEXT("Shiny reward survives profile round trip"), Reloaded.GhostLine.bShinyScanMastery);
    TestTrue(TEXT("Each native campaign remains its own reward authority"), Reloaded.Relay.bFirewallScanMastery && Reloaded.Chronicles.bParadoxScanMastery && Reloaded.GhostLine.bShinyScanMastery);
    return true;
}
#endif
