#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "Engine/GameInstance.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "UObject/StrongObjectPtr.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTTamerStyleMigrationTest,
    "DigimonVenomNXT.Tamers.Persistence.AllStylesAndCosmeticOnlyMigration",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTTamerStyleMigrationTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    TestEqual(TEXT("Exactly 64 selectable supplied characters"), DigimonVenomNXTTamers::GetRoster().Num(), 64);
    for (const DigimonVenomNXTTamers::FStyle& Style : DigimonVenomNXTTamers::GetRoster())
    {
        FDigimonPlayerProfile Source, Restored;
        Source.TamerStyleId = Style.Id;
        FString Json;
        if (!TestTrue(TEXT("Serialize a selected tamer"), FJsonObjectConverter::UStructToJsonObjectString(Source, Json)) ||
            !TestTrue(TEXT("Read the selected tamer"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Restored, 0, 0))) return false;
        TestTrue(TEXT("Every supplied selection survives JSON storage"), Restored.TamerStyleId == Style.Id);
        TestFalse(TEXT("Valid player choices never change on migration"), DigimonVenomNXTSeason::ReconcileTamerStyles(Restored));
    }

    FDigimonPlayerProfile Legacy;
    Legacy.TamerStyleId = TEXT("tamer_004");
    Legacy.Credits = 78910;
    Legacy.DigiRubies = 31;
    Legacy.Season.Version = 1;
    Legacy.Season.Week = 47;
    Legacy.Season.Wins = 29;
    Legacy.Season.PendingContextId = TEXT("saved-match");
    Legacy.Season.BattleCheckpointJson = TEXT("{\"savedDecision\":\"preserve-exactly\"}");
    Legacy.Relay.BattleCheckpointJson = TEXT("relay decision remains byte-for-byte");
    Legacy.Chronicles.BattleCheckpointJson = TEXT("chronicles decision remains byte-for-byte");
    FDigimonOwnedPartner Partner;
    Partner.InstanceId = FGuid::NewGuid();
    Partner.SpeciesId = TEXT("rookie_001");
    Partner.Variant = EDigimonVariant::Firewall;
    Partner.Level = 37;
    Partner.CurrentHP = 123;
    Legacy.Collection.Add(Partner);
    Legacy.Party.Add(Partner.InstanceId);
    FDigimonSeasonMatch Match;
    Match.MatchId = Legacy.Season.PendingContextId;
    Match.HomeTamerId = TEXT("player");
    Match.AwayTamerId = TEXT("season_tamer_09");
    Legacy.Season.CurrentCard.Add(Match);
    for (int32 Index = 0; Index < 16; ++Index)
    {
        FDigimonSeasonTamer Tamer;
        Tamer.bPlayer = Index == 0;
        Tamer.TamerId = Tamer.bPlayer ? TEXT("player") : FString::Printf(TEXT("season_tamer_%02d"), Index);
        Tamer.TamerStyleId = TEXT("tamer_002");
        Tamer.Wins = Index * 3;
        Tamer.Team.Add(Partner);
        Legacy.Season.Roster.Add(Tamer);
    }
    const FDigimonPlayerProfile Before = Legacy;
    TestTrue(TEXT("The four-style career upgrades its appearances"), DigimonVenomNXTSeason::ReconcileTamerStyles(Legacy));
    TestTrue(TEXT("The player's legacy selection remains equipped"), Legacy.TamerStyleId == Before.TamerStyleId);
    for (int32 Index = 0; Index < Legacy.Season.Roster.Num(); ++Index)
    {
        const FDigimonSeasonTamer& Tamer = Legacy.Season.Roster[Index];
        const FName Expected = Tamer.bPlayer ? Legacy.TamerStyleId : DigimonVenomNXTTamers::StyleForStableId(Tamer.TamerId);
        TestTrue(TEXT("Career bots use the same stable catalogue mapping as field rivals"), Tamer.TamerStyleId == Expected);
    }
    TestFalse(TEXT("Reconnect never rerolls the migrated appearances"), DigimonVenomNXTSeason::ReconcileTamerStyles(Legacy));
    FDigimonPlayerProfile RestoredCosmetics = Legacy;
    for (int32 Index = 0; Index < RestoredCosmetics.Season.Roster.Num(); ++Index)
        RestoredCosmetics.Season.Roster[Index].TamerStyleId = Before.Season.Roster[Index].TamerStyleId;
    TestTrue(TEXT("Only cosmetic fields change: teams, HP, money, fixtures and all checkpoints remain exact"),
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Before, &RestoredCosmetics, 0));
    Legacy.TamerStyleId = TEXT("tamer_unavailable");
    TestTrue(TEXT("An invalid legacy selection is repaired"), DigimonVenomNXTSeason::ReconcileTamerStyles(Legacy));
    TestTrue(TEXT("The repaired selection is a supplied character"), DigimonVenomNXTTamers::IsValidStyle(Legacy.TamerStyleId));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTTamerAtomicMigrationTest,
    "DigimonVenomNXT.Tamers.Persistence.AtomicLegacyMigrationAndReconnect",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTTamerAtomicMigrationTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    const FString Account = TEXT("Automation_Tamers_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString Path = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Profiles"), Account + TEXT(".json"));
    struct FTamerFixtureCleanup
    {
        FString Path;
        ~FTamerFixtureCleanup()
        {
            IFileManager::Get().DeleteDirectory(*(Path + TEXT(".tmp")), false, true);
            IFileManager::Get().Delete(*(Path + TEXT(".tmp")), false, true, true);
            IFileManager::Get().Delete(*Path, false, true, true);
        }
    } Cleanup{Path};
    TStrongObjectPtr<UGameInstance> Instance(NewObject<UGameInstance>());
    TStrongObjectPtr<UDigimonVenomNXTProfileSubsystem> Store(NewObject<UDigimonVenomNXTProfileSubsystem>(Instance.Get()));
    Store->SetAutomaticSavingForTests(true);
    FDigimonPlayerProfile Legacy;
    Legacy.AccountId = Account;
    Legacy.Username = TEXT("Tamer migration fixture");
    Legacy.TamerStyleId = TEXT("invalid_old_style");
    Legacy.Credits = 4001;
    Legacy.DigiRubies = 23;
    DigimonVenomNXTCampaign::Reconcile(Legacy);
    FString LegacyJson;
    if (!TestTrue(TEXT("Serialize an old account fixture"), FJsonObjectConverter::UStructToJsonObjectString(Legacy, LegacyJson))) return false;
    IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true);
    if (!TestTrue(TEXT("Write old save without applying migration"), FFileHelper::SaveStringToFile(LegacyJson, *Path))) return false;
    if (!TestTrue(TEXT("Block the temporary write to simulate save failure"), IFileManager::Get().MakeDirectory(*(Path + TEXT(".tmp")), true))) return false;
    FDigimonPlayerProfile Loaded;
    TestFalse(TEXT("Uncommitted style migration is never returned as a successful load"), Store->LoadProfile(Account, Legacy.Username, Loaded));
    FString AfterFailure;
    FFileHelper::LoadFileToString(AfterFailure, *Path);
    TestEqual(TEXT("Failed migration retains the exact previous durable save"), AfterFailure, LegacyJson);
    IFileManager::Get().DeleteDirectory(*(Path + TEXT(".tmp")), false, true);
    if (!TestTrue(TEXT("Retry atomically commits migration"), Store->LoadProfile(Account, Legacy.Username, Loaded))) return false;
    TestTrue(TEXT("Migration equips a valid character"), DigimonVenomNXTTamers::IsValidStyle(Loaded.TamerStyleId));
    TestEqual(TEXT("Credits survive appearance repair"), Loaded.Credits, Legacy.Credits);
    TestEqual(TEXT("DigiRubies survive appearance repair"), Loaded.DigiRubies, Legacy.DigiRubies);
    Loaded.TamerStyleId = DigimonVenomNXTTamers::StyleForIndex(63);
    if (!TestTrue(TEXT("The final roster character saves"), Store->SaveProfile(Loaded))) return false;
    FDigimonPlayerProfile Reconnected;
    if (!TestTrue(TEXT("Reconnect reads the selected character"), Store->LoadProfile(Account, Legacy.Username, Reconnected))) return false;
    TestTrue(TEXT("Character 64 remains selected after reconnect"), Reconnected.TamerStyleId == Loaded.TamerStyleId);
    return true;
}

#endif
