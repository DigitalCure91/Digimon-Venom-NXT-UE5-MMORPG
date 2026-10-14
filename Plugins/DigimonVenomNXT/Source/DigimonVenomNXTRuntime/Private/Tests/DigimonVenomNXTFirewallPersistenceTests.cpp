#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTTypes.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTFirewallPersistenceTest,
    "DigimonVenomNXT.Firewall.Persistence.LegacyAndFourVarieties",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTFirewallPersistenceTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    // Old numeric and named JSON remain readable after appending the new enum.
    const TCHAR* LegacyNames[] = {TEXT("Normal"), TEXT("Paradox"), TEXT("Shiny")};
    for (int32 VarietyIndex = 0; VarietyIndex < 3; ++VarietyIndex)
    {
        FDigimonScanRecord LegacyNumeric, LegacyNamed;
        const FString NumericJson = FString::Printf(TEXT("{\"speciesId\":\"rookie_001\",\"variant\":%d,\"percent\":75}"), VarietyIndex);
        const FString NamedJson = FString::Printf(TEXT("{\"speciesId\":\"rookie_001\",\"variant\":\"%s\",\"percent\":75}"), LegacyNames[VarietyIndex]);
        if (!TestTrue(TEXT("Read legacy numeric variety"), FJsonObjectConverter::JsonObjectStringToUStruct(NumericJson, &LegacyNumeric, 0, 0)) ||
            !TestTrue(TEXT("Read legacy named variety"), FJsonObjectConverter::JsonObjectStringToUStruct(NamedJson, &LegacyNamed, 0, 0))) return false;
        TestEqual(TEXT("Numeric variety retains identity"), static_cast<int32>(LegacyNumeric.Variant), VarietyIndex);
        TestEqual(TEXT("Named variety retains identity"), static_cast<int32>(LegacyNamed.Variant), VarietyIndex);
        TestEqual(TEXT("Legacy scan remains unchanged"), LegacyNamed.Percent, 75);
    }

    FDigimonPlayerProfile Before;
    Before.AccountId = TEXT("FirewallSerializationFixture");
    Before.Username = TEXT("Firewall tamer");
    Before.Relay.bShinyScanMastery = true;
    Before.Chronicles.bParadoxScanMastery = true;
    for (int32 VarietyIndex = 0; VarietyIndex < 4; ++VarietyIndex)
    {
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid::NewGuid();
        Partner.SpeciesId = TEXT("rookie_001");
        Partner.Variant = static_cast<EDigimonVariant>(VarietyIndex);
        Partner.Level = 27;
        Partner.Experience = 175000;
        Partner.ABI = 19;
        Partner.PermanentTraining.Attack = 6;
        Before.Collection.Add(Partner);
        Before.Party.Add(Partner.InstanceId);
        Before.DigiFarmResidents.Add(Partner.InstanceId);
        Before.Ranked.DefenderTeam.Add(Partner);
        FDigimonScanRecord Scan;
        Scan.SpeciesId = Partner.SpeciesId;
        Scan.Variant = Partner.Variant;
        Scan.Percent = 35 + VarietyIndex * 5;
        Scan.PeakPercent = 200;
        Scan.bEverOwned = true;
        Before.Scans.Add(Scan);
    }
    FDigimonBattleState Checkpoint;
    FDigimonBattleUnit FirewallUnit;
    FirewallUnit.SpeciesId = TEXT("rookie_001");
    FirewallUnit.Variant = EDigimonVariant::Firewall;
    FirewallUnit.Level = 27;
    Checkpoint.TeamB.Active.Add(FirewallUnit);
    if (!TestTrue(TEXT("Serialize Firewall battle decision"), FJsonObjectConverter::UStructToJsonObjectString(Checkpoint, Before.Chronicles.BattleCheckpointJson))) return false;
    Before.Relay.BattleCheckpointJson = Before.Chronicles.BattleCheckpointJson;
    Before.Season.BattleCheckpointJson = Before.Chronicles.BattleCheckpointJson;

    FString ProfileJson;
    FDigimonPlayerProfile After;
    if (!TestTrue(TEXT("Serialize all four forms through production JSON converter"), FJsonObjectConverter::UStructToJsonObjectString(Before, ProfileJson)) ||
        !TestTrue(TEXT("Deserialize complete account"), FJsonObjectConverter::JsonObjectStringToUStruct(ProfileJson, &After, 0, 0))) return false;
    TestTrue(TEXT("Collection, scan, party, farm, ranked and campaign fields round-trip without loss"),
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Before, &After, 0));
    FDigimonBattleState Restored;
    if (!TestTrue(TEXT("Restore nested Firewall battle decision"), FJsonObjectConverter::JsonObjectStringToUStruct(After.Chronicles.BattleCheckpointJson, &Restored, 0, 0))) return false;
    if (!TestEqual(TEXT("Saved opponent is retained"), Restored.TeamB.Active.Num(), 1)) return false;
    TestTrue(TEXT("Saved wild opponent keeps Firewall identity"), Restored.TeamB.Active[0].Variant == EDigimonVariant::Firewall);
    return true;
}

#endif
