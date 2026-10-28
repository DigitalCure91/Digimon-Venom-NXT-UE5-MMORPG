#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTRivalRetention.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "Engine/World.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTTypes.h"
#include "Misc/AutomationTest.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"

namespace
{
    FDigimonOwnedPartner RetentionPartner(uint32 Serial, int32 Level = 1)
    {
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid(0, 0, 1, Serial);
        Partner.SpeciesId = FName(*FString::Printf(TEXT("retention_species_%u"), Serial));
        Partner.Level = Level;
        Partner.Experience = static_cast<int64>(Level) * 100;
        return Partner;
    }

    FDigimonAIRivalTrainingHistory RetentionHistory(const FGuid& Id, int64 Session)
    {
        FDigimonAIRivalTrainingHistory History;
        History.InstanceId = Id;
        History.LastLedSession = Session;
        return History;
    }

    bool HasRetentionPartner(const FDigimonAIRivalRecord& Rival, const FGuid& Id)
    {
        return Rival.Collection.ContainsByPredicate([&Id](const FDigimonOwnedPartner& Partner)
        {
            return Partner.InstanceId == Id;
        });
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRivalRetentionOwnershipTest,
    "DigimonVenomNXT.Rivals.Retention.LegacyOwnershipAndHistory",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTRivalRetentionOwnershipTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UDigimonVenomNXTSettings* Settings = NewObject<UDigimonVenomNXTSettings>();
    Settings->AIRivalMaxCollectionSize = 6;
    Settings->MaxPartySize = 6;
    FDigimonAIRivalRecord Rival;
    Rival.TrainingSessionSerial = 20;
    for (uint32 Serial = 1; Serial <= 40; ++Serial)
    {
        Rival.Collection.Add(RetentionPartner(Serial, 40 - static_cast<int32>(Serial)));
        Rival.TrainingHistory.Add(RetentionHistory(Rival.Collection.Last().InstanceId, Serial % 20));
    }
    // A low-level active partner at the end must survive ahead of powerful reserves.
    FDigimonOwnedPartner Active = Rival.Collection.Last();
    Active.Level = 17;
    Active.Experience = 123456;
    Active.ABI = 21;
    Rival.Partners.Add(Active);
    Rival.TrainingLeaderId = Rival.Collection[38].InstanceId;
    const FGuid LeaderId = Rival.TrainingLeaderId;
    const FGuid StarterId = Rival.Collection[0].InstanceId;
    // Old party-only saves must not lose currently selected ownership.
    const FDigimonOwnedPartner PartyOnly = RetentionPartner(100, 2);
    Rival.Partners.Add(PartyOnly);
    Rival.Collection.Add(Rival.Collection[0]);
    Rival.TrainingHistory.Add(RetentionHistory(FGuid(9, 9, 9, 9), 2));
    Rival.LifetimeStats.Materializations = 420;
    Rival.LifetimeStats.ExperienceGained = 1000000;

    const auto Result = DigimonVenomNXTRivalRetention::Prune(Rival, *Settings);
    TestTrue(TEXT("Oversized legacy record reports cleanup"), Result.bChanged);
    TestEqual(TEXT("Collection obeys configured limit"), Rival.Collection.Num(), 6);
    TestTrue(TEXT("Active partner protected"), HasRetentionPartner(Rival, Active.InstanceId));
    TestTrue(TEXT("Training leader protected"), HasRetentionPartner(Rival, LeaderId));
    TestTrue(TEXT("Original starter protected"), HasRetentionPartner(Rival, StarterId));
    TestTrue(TEXT("Party-only legacy partner preserved"), HasRetentionPartner(Rival, PartyOnly.InstanceId));
    const FDigimonOwnedPartner* Owned = Rival.Collection.FindByPredicate([&Active](const FDigimonOwnedPartner& Partner)
    {
        return Partner.InstanceId == Active.InstanceId;
    });
    if (TestNotNull(TEXT("Active authoritative ownership exists"), Owned))
    {
        TestEqual(TEXT("Latest party XP preserved"), Owned->Experience, Active.Experience);
        TestEqual(TEXT("Latest party ABI preserved"), Owned->ABI, Active.ABI);
        TestEqual(TEXT("Latest party level preserved"), Owned->Level, Active.Level);
    }
    TSet<FGuid> CollectionIds;
    for (const FDigimonOwnedPartner& Partner : Rival.Collection)
    {
        TestFalse(TEXT("Ownership GUIDs are unique"), CollectionIds.Contains(Partner.InstanceId));
        CollectionIds.Add(Partner.InstanceId);
    }
    TSet<FGuid> HistoryIds;
    for (const FDigimonAIRivalTrainingHistory& History : Rival.TrainingHistory)
    {
        TestTrue(TEXT("History points only to retained ownership"), CollectionIds.Contains(History.InstanceId));
        TestFalse(TEXT("History GUIDs are unique"), HistoryIds.Contains(History.InstanceId));
        HistoryIds.Add(History.InstanceId);
    }
    TestTrue(TEXT("History bounded by ownership"), Rival.TrainingHistory.Num() <= Rival.Collection.Num());
    TestEqual(TEXT("Lifetime materialization total survives release"), Rival.LifetimeStats.Materializations, 420);
    TestEqual(TEXT("Lifetime XP total survives release"), Rival.LifetimeStats.ExperienceGained, int64(1000000));
    const FDigimonAIRivalRecord Once = Rival;
    const auto Again = DigimonVenomNXTRivalRetention::Prune(Rival, *Settings);
    TestFalse(TEXT("Second prune is a no-op"), Again.bChanged);
    TestTrue(TEXT("Retention is idempotent"), FDigimonAIRivalRecord::StaticStruct()->CompareScriptStruct(&Once, &Rival, 0));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRivalRetentionScansTest,
    "DigimonVenomNXT.Rivals.Retention.ScanDeduplicationAndBounds",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTRivalRetentionScansTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UDigimonVenomNXTSettings* Settings = NewObject<UDigimonVenomNXTSettings>();
    Settings->AIRivalMaxScanRecords = 128;
    Settings->ScanCapPercent = 200;
    FDigimonAIRivalRecord Rival;
    FDigimonScanRecord A;
    A.SpeciesId = TEXT("retention_scan");
    A.Percent = 40;
    A.PeakPercent = 80;
    A.Materializations = 2;
    Rival.Scans.Add(A);
    A.Percent = 75;
    A.PeakPercent = 200;
    A.Materializations = 3;
    A.bEverOwned = true;
    Rival.Scans.Add(A);
    A.Variant = EDigimonVariant::Shiny;
    A.Percent = 100;
    Rival.Scans.Add(A);
    A.Variant = static_cast<EDigimonVariant>(255);
    Rival.Scans.Add(A);
    A.SpeciesId = NAME_None;
    A.Variant = EDigimonVariant::Normal;
    Rival.Scans.Add(A);
    const auto Result = DigimonVenomNXTRivalRetention::Prune(Rival, *Settings);
    TestTrue(TEXT("Duplicate and invalid scan cleanup reported"), Result.bChanged);
    TestEqual(TEXT("One record per valid species/variant"), Rival.Scans.Num(), 2);
    const FDigimonScanRecord* Normal = Rival.Scans.FindByPredicate([](const FDigimonScanRecord& Scan)
    {
        return Scan.SpeciesId == FName(TEXT("retention_scan")) && Scan.Variant == EDigimonVariant::Normal;
    });
    if (TestNotNull(TEXT("Normal scan retained"), Normal))
    {
        TestEqual(TEXT("Duplicate progress takes maximum, not sum"), Normal->Percent, 75);
        TestEqual(TEXT("Peak discovery preserved"), Normal->PeakPercent, 200);
        TestEqual(TEXT("Duplicate counters are not multiplied"), Normal->Materializations, 3);
        TestTrue(TEXT("Owned discovery preserved"), Normal->bEverOwned);
    }
    Rival.Scans.Reset();
    Settings->AIRivalMaxScanRecords = 100000;
    for (int32 Index = 0; Index < 1000; ++Index)
    {
        FDigimonScanRecord Scan;
        Scan.SpeciesId = FName(*FString::Printf(TEXT("bounded_scan_%d"), Index));
        Scan.Percent = 100;
        Rival.Scans.Add(Scan);
    }
    DigimonVenomNXTRivalRetention::Prune(Rival, *Settings);
    TestEqual(TEXT("Unsafe legacy config respects population scan budget"), Rival.Scans.Num(), 128);
    const FDigimonAIRivalRecord Once = Rival;
    TestFalse(TEXT("Bounded scans stay stable"), DigimonVenomNXTRivalRetention::Prune(Rival, *Settings).bChanged);
    TestTrue(TEXT("Repeated scan cleanup is idempotent"), FDigimonAIRivalRecord::StaticStruct()->CompareScriptStruct(&Once, &Rival, 0));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRivalRetentionReleaseTest,
    "DigimonVenomNXT.Rivals.Retention.ReleaseRemovesOwnershipAndHistory",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTRivalRetentionReleaseTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UDigimonVenomNXTSettings* Settings = NewObject<UDigimonVenomNXTSettings>();
    FDigimonAIRivalRecord Rival;
    for (uint32 Serial = 1; Serial <= 3; ++Serial)
    {
        Rival.Collection.Add(RetentionPartner(Serial));
        Rival.TrainingHistory.Add(RetentionHistory(Rival.Collection.Last().InstanceId, 0));
    }
    Rival.Partners.Add(Rival.Collection[0]);
    Rival.TrainingLeaderId = Rival.Collection[1].InstanceId;
    const FGuid ActiveId = Rival.Collection[0].InstanceId;
    const FGuid LeaderId = Rival.Collection[1].InstanceId;
    const FGuid ReserveId = Rival.Collection[2].InstanceId;
    TestFalse(TEXT("Active party cannot be released"), DigimonVenomNXTRivalRetention::Release(Rival, ActiveId, *Settings));
    TestFalse(TEXT("Current training leader cannot be released"), DigimonVenomNXTRivalRetention::Release(Rival, LeaderId, *Settings));
    TestFalse(TEXT("Unknown ownership cannot be released"), DigimonVenomNXTRivalRetention::Release(Rival, FGuid(4, 4, 4, 4), *Settings));
    TestTrue(TEXT("Reserve can be released"), DigimonVenomNXTRivalRetention::Release(Rival, ReserveId, *Settings));
    TestEqual(TEXT("One ownership slot freed"), Rival.Collection.Num(), 2);
    TestFalse(TEXT("Released creature payload gone"), HasRetentionPartner(Rival, ReserveId));
    TestFalse(TEXT("Released creature history gone"), Rival.TrainingHistory.ContainsByPredicate([&ReserveId](const FDigimonAIRivalTrainingHistory& History)
    {
        return History.InstanceId == ReserveId;
    }));
    TestFalse(TEXT("Repeated release cannot remove another creature"), DigimonVenomNXTRivalRetention::Release(Rival, ReserveId, *Settings));
    TestTrue(TEXT("Active ownership still present"), HasRetentionPartner(Rival, ActiveId));
    TestTrue(TEXT("Leader ownership still present"), HasRetentionPartner(Rival, LeaderId));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRivalRetentionLimitsTest,
    "DigimonVenomNXT.Rivals.Retention.LegacyConfigurationHardLimits",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTRivalRetentionLimitsTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    TestEqual(TEXT("Legacy 1536 collection config is bounded"), DigimonVenomNXTRivalRetention::CollectionLimit(1536), 64);
    TestEqual(TEXT("Negative collection config permits a full six-member party"), DigimonVenomNXTRivalRetention::CollectionLimit(-100), 6);
    TestEqual(TEXT("Requested safe collection capacity preserved"), DigimonVenomNXTRivalRetention::CollectionLimit(24), 24);
    TestEqual(TEXT("Twelve-member party fits despite lower collection setting"), DigimonVenomNXTRivalRetention::CollectionLimit(6, 12), 12);
    TestEqual(TEXT("Arbitrary scan config respects default population budget"), DigimonVenomNXTRivalRetention::ScanLimit(MAX_int32), 128);
    TestEqual(TEXT("Small population still respects absolute scan bound"), DigimonVenomNXTRivalRetention::ScanLimit(MAX_int32, 1), 256);
    TestEqual(TEXT("Large population reduces ownership capacity"), DigimonVenomNXTRivalRetention::CollectionLimit(1536, 6, 5000), 12);
    TestEqual(TEXT("Large population reduces scan capacity"), DigimonVenomNXTRivalRetention::ScanLimit(MAX_int32, 5000), 25);
    UDigimonVenomNXTSettings* Settings = NewObject<UDigimonVenomNXTSettings>();
    Settings->AIRivalMaxCollectionSize = 1536;
    Settings->MaxPartySize = 12;
    Settings->AIRivalMaxScanRecords = MAX_int32;
    FDigimonAIRivalRecord Rival;
    for (uint32 Serial = 1; Serial <= 90; ++Serial)
    {
        Rival.Collection.Add(RetentionPartner(Serial));
        if (Serial > 78) Rival.Partners.Add(Rival.Collection.Last());
        FDigimonScanRecord Scan;
        Scan.SpeciesId = Rival.Collection.Last().SpeciesId;
        Scan.Percent = 100;
        Rival.Scans.Add(Scan);
    }
    Rival.TrainingLeaderId = Rival.Partners[0].InstanceId;
    DigimonVenomNXTRivalRetention::Prune(Rival, *Settings, nullptr, 5000);
    TestEqual(TEXT("Large population applies collection budget in production prune"), Rival.Collection.Num(), 12);
    TestEqual(TEXT("Large population applies scan budget in production prune"), Rival.Scans.Num(), 25);
    TestEqual(TEXT("Full configured party survives scaled budget"), Rival.Partners.Num(), 12);
    for (const FDigimonOwnedPartner& Partner : Rival.Partners)
        TestTrue(TEXT("Scaled cleanup preserves every active partner"), HasRetentionPartner(Rival, Partner.InstanceId));
    return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTRivalRetentionPayloadTest,
    "DigimonVenomNXT.Rivals.Retention.SpentScansMovesAndInventory",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTRivalRetentionPayloadTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UDigimonVenomNXTSettings* Settings = NewObject<UDigimonVenomNXTSettings>();
    Settings->AIRivalMaxScanRecords = 128;
    Settings->ScanCapPercent = 200;
    FDigimonAIRivalRecord Rival;
    FDigimonOwnedPartner Partner = RetentionPartner(1);
    FString LongText;
    for (int32 Index = 0; Index < 2000; ++Index) LongText += TEXT("x");
    Partner.Nickname = LongText;
    Rival.DisplayName = LongText;
    Rival.CurrentActivity = LongText;
    for (int32 Index = 0; Index < 12; ++Index)
    {
        FDigimonMoveSlot Move;
        Move.MoveId = FName(*FString::Printf(TEXT("retention_move_%d"), Index));
        Move.DisplayName = FText::FromString(LongText);
        Move.Description = LongText;
        Move.Power = 100 + Index;
        Move.SPCost = 3 + Index;
        Partner.Moves.Add(Move);
    }
    Rival.Collection.Add(Partner);
    Rival.Partners.Add(Partner);
    FDigimonScanRecord Spent;
    Spent.SpeciesId = TEXT("spent_scan");
    Spent.PeakPercent = 200;
    Spent.Materializations = 9000;
    Spent.bEverOwned = true;
    Rival.Scans.Add(Spent);
    FDigimonScanRecord Empty;
    Empty.SpeciesId = TEXT("empty_scan");
    Rival.Scans.Add(Empty);
    FDigimonScanRecord Fractional;
    Fractional.SpeciesId = TEXT("fractional_scan");
    Fractional.FractionalHundredths = 25;
    Rival.Scans.Add(Fractional);
    Rival.LifetimeStats.Materializations = 9000;
    auto AddItem = [&Rival](FName Id, int32 Quantity)
    {
        FDigimonInventoryEntry Entry;
        Entry.ItemId = Id;
        Entry.Quantity = Quantity;
        Rival.Inventory.Add(Entry);
    };
    AddItem(TEXT("healing_item"), 3);
    AddItem(TEXT("healing_item"), 8);
    AddItem(NAME_None, 99);
    AddItem(TEXT("empty_item"), 0);
    AddItem(TEXT("invalid_item"), -1);

    const auto Result = DigimonVenomNXTRivalRetention::Prune(Rival, *Settings);
    TestTrue(TEXT("Payload cleanup reported"), Result.bChanged);
    TestEqual(TEXT("Only useful fractional progress remains"), Rival.Scans.Num(), 1);
    if (Rival.Scans.Num() == 1)
    {
        TestTrue(TEXT("Fractional scan retains identity"), Rival.Scans[0].SpeciesId == FName(TEXT("fractional_scan")));
        TestEqual(TEXT("Fractional progress is not lost"), Rival.Scans[0].FractionalHundredths, 25);
    }
    TestEqual(TEXT("Spent discovery payload removed"), Result.RemovedScans, 2);
    TestEqual(TEXT("Historical activity uses fixed counters"), Rival.LifetimeStats.Materializations, 9000);
    if (TestEqual(TEXT("Companion remains owned"), Rival.Collection.Num(), 1))
    {
        const FDigimonOwnedPartner& Owned = Rival.Collection[0];
        TestEqual(TEXT("Only four combat move slots persist"), Owned.Moves.Num(), 4);
        TestEqual(TEXT("Nickname length bounded"), Owned.Nickname.Len(), 64);
        for (int32 Index = 0; Index < Owned.Moves.Num(); ++Index)
        {
            const FDigimonMoveSlot& Move = Owned.Moves[Index];
            TestTrue(TEXT("Move catalog display text removed"), Move.DisplayName.IsEmpty());
            TestTrue(TEXT("Move catalog description removed"), Move.Description.IsEmpty());
            TestTrue(TEXT("Equipped move IDs survive compaction"), Move.MoveId == FName(*FString::Printf(TEXT("retention_move_%d"), Index)));
            TestEqual(TEXT("Move power retained"), Move.Power, 100 + Index);
            TestEqual(TEXT("Move cost retained"), Move.SPCost, 3 + Index);
        }
        if (TestEqual(TEXT("Selected party remains intact"), Rival.Partners.Num(), 1))
            TestTrue(TEXT("Selected and owned payloads stay synchronized"), FDigimonOwnedPartner::StaticStruct()->CompareScriptStruct(&Owned, &Rival.Partners[0], 0));
    }
    TestEqual(TEXT("Display name bounded"), Rival.DisplayName.Len(), 96);
    TestEqual(TEXT("Activity text bounded"), Rival.CurrentActivity.Len(), 160);
    if (TestEqual(TEXT("Inventory deduplicated and empty entries removed"), Rival.Inventory.Num(), 1))
    {
        TestTrue(TEXT("Useful inventory retained"), Rival.Inventory[0].ItemId == FName(TEXT("healing_item")));
        TestEqual(TEXT("Duplicate quantities take maximum, not sum"), Rival.Inventory[0].Quantity, 8);
    }
    TestEqual(TEXT("Removed inventory payload counted"), Result.RemovedInventory, 4);
    const FDigimonAIRivalRecord Once = Rival;
    TestFalse(TEXT("Payload compaction is a no-op on second pass"), DigimonVenomNXTRivalRetention::Prune(Rival, *Settings).bChanged);
    TestTrue(TEXT("Payload compaction remains idempotent"), FDigimonAIRivalRecord::StaticStruct()->CompareScriptStruct(&Once, &Rival, 0));
    FDigimonAIRivalRecord DuplicateSlots;
    Partner.Moves[1].MoveId = Partner.Moves[0].MoveId;
    DuplicateSlots.Collection.Add(Partner);
    DigimonVenomNXTRivalRetention::Prune(DuplicateSlots, *Settings);
    if (TestEqual(TEXT("Duplicate-slot companion preserved"), DuplicateSlots.Collection.Num(), 1) &&
        TestEqual(TEXT("Legal duplicate techniques keep all four slots"), DuplicateSlots.Collection[0].Moves.Num(), 4))
        for (int32 Index = 0; Index < 4; ++Index)
            TestTrue(TEXT("Equipped technique order remains exact"), DuplicateSlots.Collection[0].Moves[Index].MoveId == Partner.Moves[Index].MoveId);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonRivalMaterializationCapacityTest,
    "DigimonVenomNXT.Rivals.Retention.MaterializationStopsBeforeAllocationOrScanSpend",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonRivalMaterializationCapacityTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    // No initialized registry/world is needed: a full collection must return before
    // querying the catalog, allocating a new GUID, or consuming any scan currency.
    UWorld* World = NewObject<UWorld>();
    UDigimonVenomNXTAIRivalSubsystem* Store = NewObject<UDigimonVenomNXTAIRivalSubsystem>(World);
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 Population = Store->RetentionPopulation();
    const int32 Capacity = DigimonVenomNXTRivalRetention::CollectionLimit(
        Settings->AIRivalMaxCollectionSize, Settings->MaxPartySize, Population);
    FDigimonAIRivalRecord Rival;
    for (int32 I = 0; I < Capacity; ++I) Rival.Collection.Add(RetentionPartner(I + 1));
    Rival.Partners.Add(Rival.Collection[0]);
    Rival.TrainingLeaderId = Rival.Partners[0].InstanceId;
    FDigimonScanRecord Scan;
    Scan.SpeciesId = TEXT("new_unowned_species");
    Scan.Percent = Settings->ScanCapPercent;
    Scan.Materializations = 7;
    Rival.Scans.Add(Scan);
    const FDigimonAIRivalRecord Before = Rival;
    // A week of attempted 30-second materializations with all automatic saves off.
    for (int32 Attempt = 0; Attempt < 20160; ++Attempt)
        if (Store->TryMaterialize(Rival)) { AddError(TEXT("Full bot materialized another Digimon")); return false; }
    TestTrue(TEXT("Full collection and scan balances remain unchanged across a week of attempts"),
        FDigimonAIRivalRecord::StaticStruct()->CompareScriptStruct(&Before, &Rival, 0));
    const FGuid Reserve = Rival.Collection.Last().InstanceId;
    TestTrue(TEXT("Releasing a reserve opens a real ownership slot"),
        DigimonVenomNXTRivalRetention::Release(Rival, Reserve, *Settings, nullptr, Population));
    TestEqual(TEXT("Capacity is freed only after release"), Rival.Collection.Num(), Capacity - 1);
    return true;
}

#endif
