#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTCombatVersionPersistenceTest,
    "DigimonVenomNXT.Combat.Persistence.LegacyAndVersionedVitals",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTCombatVersionPersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FDigimonOwnedPartner Legacy;
    if (!TestTrue(TEXT("Legacy partner JSON remains readable"), FJsonObjectConverter::JsonObjectStringToUStruct(
        TEXT("{\"speciesId\":\"rookie_001\",\"level\":50,\"currentHP\":41,\"currentSP\":0,\"aBI\":120}"), &Legacy, 0, 0))) return false;
    TestEqual(TEXT("Missing version requests one-time proportional migration"), Legacy.CombatBalanceVersion, 0);
    TestEqual(TEXT("Deserialization itself never heals"), Legacy.CurrentHP, 41);
    TestEqual(TEXT("Exhausted SP remains exhausted before migration"), Legacy.CurrentSP, 0);
    Legacy.InstanceId = FGuid::NewGuid();
    Legacy.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    FDigimonPlayerProfile Before;
    Before.AccountId = TEXT("CombatVersionFixture");
    Before.Collection.Add(Legacy);
    Before.Party.Add(Legacy.InstanceId);
    Before.DigiFarmResidents.Add(Legacy.InstanceId);
    Before.Ranked.DefenderTeam.Add(Legacy);
    FDigimonSeasonTamer Tamer;
    Tamer.Team.Add(Legacy);
    Before.Season.Roster.Add(Tamer);
    Before.GhostLine.BattleCheckpointJson = TEXT("unresolved-private-decision");
    Before.GhostLine.bFirewallScanMastery = true;
    FString Json;
    FDigimonPlayerProfile After;
    if (!TestTrue(TEXT("Serialize combat version in each persisted roster"), FJsonObjectConverter::UStructToJsonObjectString(Before, Json)) ||
        !TestTrue(TEXT("Restore profile combat markers"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &After, 0, 0))) return false;
    TestTrue(TEXT("Identity, injury, checkpoint, mastery and nested version fields survive"),
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Before, &After, 0));
    TestEqual(TEXT("Season NPC marker survives"), After.Season.Roster[0].Team[0].CombatBalanceVersion, DigimonVenomNXTAutoBattle::CurrentBalanceVersion);
    return true;
}

#endif
