// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTSettings.h"
#include "UObject/SoftObjectPath.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTSettings() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftObjectPath(ETypeConstructPhase);
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSettings(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSettings(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTSettings *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTSettings_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "DisplayName", "Digimon Venom NXT" },
		{ "IncludePath", "DigimonVenomNXTSettings.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMasterVolume_MetaData[] = {
		{ "Category", "Audio" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Defaults for new local players. In-game mixer changes are saved on that device. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Defaults for new local players. In-game mixer changes are saved on that device." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMusicVolume_MetaData[] = {
		{ "Category", "Audio" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultEffectsVolume_MetaData[] = {
		{ "Category", "Audio" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultUIVolume_MetaData[] = {
		{ "Category", "Audio" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundEffectOverrides_MetaData[] = {
		{ "AllowedClasses", "/Script/Engine.SoundBase" },
		{ "Category", "Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional per-cue assets: Heal, UIClick, PhysicalAttack, etc. Leave empty to use supplied SFX. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional per-cue assets: Heal, UIClick, PhysicalAttack, etc. Leave empty to use supplied SFX." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainMenuMap_MetaData[] = {
		{ "Category", "Startup" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PublicWorldMap_MetaData[] = {
		{ "Category", "Startup" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerDisplayName_MetaData[] = {
		{ "Category", "Multiplayer|Public Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PublicGameAddress_MetaData[] = {
		{ "Category", "Multiplayer|Public Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "IP, domain, or subdomain players use to reach the public game. There is intentionally no join password." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GameplayPort_MetaData[] = {
		{ "Category", "Multiplayer|Public Server" },
		{ "ClampMax", "65535" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPlayers_MetaData[] = {
		{ "Category", "Multiplayer|Public Server" },
		{ "ClampMax", "5000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdminHostPassword_MetaData[] = {
		{ "Category", "Multiplayer|Hosting" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
		{ "PasswordField", "true" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local editor hosting credential. Leave blank in distributable config. Production hosting uses DIGIMONVENOMNXT_HOST_PASSWORD or Saved/DigimonVenomNXT/Host.ini. This is not a joining password." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PasswordHashIterations_MetaData[] = {
		{ "Category", "Accounts" },
		{ "ClampMax", "500000" },
		{ "ClampMin", "10000" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Password hashing work factor for the host-owned Unreal SaveGame account database." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPartySize_MetaData[] = {
		{ "Category", "Party" },
		{ "ClampMax", "12" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveBattleSize_MetaData[] = {
		{ "Category", "Party" },
		{ "ClampMax", "6" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPartnerLevel_MetaData[] = {
		{ "Category", "Party" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StarterLevel_MetaData[] = {
		{ "Category", "Party" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Initial level for a player's first partner and the minimum for newly seeded AI starters. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initial level for a player's first partner and the minimum for newly seeded AI starters." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NormalSpeciesCapacity_MetaData[] = {
		{ "Category", "Collection" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanCapPercent_MetaData[] = {
		{ "Category", "Collection" },
		{ "ClampMax", "999" },
		{ "ClampMin", "100" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterializeRequirementPercent_MetaData[] = {
		{ "Category", "Collection" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bConsumeScanOnMaterialize_MetaData[] = {
		{ "Category", "Collection" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParadoxChance_MetaData[] = {
		{ "Category", "Wild Encounters" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShinyChance_MetaData[] = {
		{ "Category", "Wild Encounters" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirewallChance_MetaData[] = {
		{ "Category", "Wild Encounters" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "DisplayName", "Firewall Encounter Chance" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0.007 = 0.7% of wild encounters, 0 disables, 1 = 100% when other variety chances are zero. Each encounter uses one roll: Shiny, Paradox, Firewall, then Normal. If rare chances total more than 100%, they are reduced proportionally. Unavailable artwork falls back to Normal without increasing other rare rates. Wild Firewall defeats grant 5 scan points by default; completing Dawn Relay grants a 20% mastery bonus on a qualifying victory (6 total), up to the scan cap." },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseScanGain_MetaData[] = {
		{ "Category", "Wild Encounters" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base scan points per defeated normal wild Digimon. RareScanGain controls variants; campaign mastery applies after a qualifying victory." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RareScanGain_MetaData[] = {
		{ "Category", "Wild Encounters" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base scan points per defeated Shiny, Paradox or Firewall wild Digimon before campaign mastery." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExperienceRate_MetaData[] = {
		{ "Category", "Progression" },
		{ "ClampMax", "100.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Global multiplier for newly awarded battle experience; 1 uses source game rates." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoneyRewardRate_MetaData[] = {
		{ "Category", "Economy" },
		{ "ClampMax", "100.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Global multiplier for newly awarded battle money; 1 uses source game rates." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PublicAtlasMapCount_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RegionCount_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPersistentAIRivals_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "5000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalSimulationIntervalSeconds_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "30.0" },
		{ "ClampMin", "0.25" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server work budget. Existing records are retained if the active population is reduced. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server work budget. Existing records are retained if the active population is reduced." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalRecordsPerStep_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalActionIntervalSeconds_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "3600" },
		{ "ClampMin", "5" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalSimulationBudgetMilliseconds_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "20.0" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Wall-clock budget for each simulation batch; cursor resumes on the next tick. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Wall-clock budget for each simulation batch; cursor resumes on the next tick." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalMaxCollectionSize_MetaData[] = {
		{ "Category", "AI Rivals|Retention" },
		{ "ClampMax", "64" },
		{ "ClampMin", "6" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Total owned Digimon per bot, including its active party. Full storage blocks materialization.\n     * Excess legacy reserves are released permanently; active parties are retained. Runtime safety\n     * also limits ownership to 64 per bot and shares a 64,000-companion budget across saved rivals.\n     * Existing INI values above these limits are clamped; configured party slots remain available.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total owned Digimon per bot, including its active party. Full storage blocks materialization.\nExcess legacy reserves are released permanently; active parties are retained. Runtime safety\nalso limits ownership to 64 per bot and shares a 64,000-companion budget across saved rivals.\nExisting INI values above these limits are clamped; configured party slots remain available." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalMaxScanRecords_MetaData[] = {
		{ "Category", "AI Rivals|Retention" },
		{ "ClampMax", "256" },
		{ "ClampMin", "16" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Retain useful scan progress, not a perpetual full discovery archive for every bot.\n     * Runtime limits: 256 per bot and a shared 128,000-record budget across saved rivals.\n     * Duplicate/empty scans are removed; excess scans prefer current spendable progress.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retain useful scan progress, not a perpetual full discovery archive for every bot.\nRuntime limits: 256 per bot and a shared 128,000-record budget across saved rivals.\nDuplicate/empty scans are removed; excess scans prefer current spendable progress." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalTrainingBattlesPerParty_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rotate the training leader and level-matched party after this many field battles. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rotate the training leader and level-matched party after this many field battles." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalTrainingLevelSpan_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "30" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum level difference within a training cohort. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum level difference within a training cohort." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalMapBalanceReviewActions_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Review suitable habitat population after this many field battles; party changes always reassess immediately. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Review suitable habitat population after this many field battles; party changes always reassess immediately." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIRivalSaveIntervalSeconds_MetaData[] = {
		{ "Category", "AI Rivals" },
		{ "ClampMax", "600.0" },
		{ "ClampMin", "10.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxVisibleAIRivalsPerMap_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalChatRadius_MetaData[] = {
		{ "Category", "World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxChatCharacters_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "512" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Legacy config compatibility; WORLD has no distance limit.\n" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy config compatibility; WORLD has no distance limit." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerWalkSpeed_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "5000.0" },
		{ "ClampMin", "50.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerFieldSpriteScale_MetaData[] = {
		{ "Category", "World|Character Presentation" },
		{ "ClampMax", "8.0" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Tamer source-art scale multiplier, normalized to the original 5.4 presentation setting. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tamer source-art scale multiplier, normalized to the original 5.4 presentation setting." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowerFieldSpriteScale_MetaData[] = {
		{ "Category", "World|Character Presentation" },
		{ "ClampMax", "3.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Partner follower source-art scale multiplier, normalized to the original 1.45 presentation setting. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Partner follower source-art scale multiplier, normalized to the original 1.45 presentation setting." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WildEncounterCooldownSeconds_MetaData[] = {
		{ "Category", "World" },
		{ "ClampMax", "60.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EncounterStepDistance_MetaData[] = {
		{ "Category", "World|Field Exploration" },
		{ "ClampMax", "2000.0" },
		{ "ClampMin", "50.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance travelled on foot before the server performs another random encounter roll. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance travelled on foot before the server performs another random encounter roll." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EncounterChancePerStep_MetaData[] = {
		{ "Category", "World|Field Exploration" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Probability of a wild encounter for each completed encounter step. Wild battles are field-walking driven, not button driven. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Probability of a wild encounter for each completed encounter step. Wild battles are field-walking driven, not button driven." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EncounterSafeDistanceAfterTravel_MetaData[] = {
		{ "Category", "World|Field Exploration" },
		{ "ClampMax", "5000.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Safe walking distance after spawning or Atlas travel before encounters can roll. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Safe walking distance after spawning or Atlas travel before encounters can roll." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapWorldWidth_MetaData[] = {
		{ "Category", "World|Map Presentation" },
		{ "ClampMax", "30000.0" },
		{ "ClampMin", "2000.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Normalized width used for every real imported 2D habitat. Collision masks are never playable maps. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Normalized width used for every real imported 2D habitat. Collision masks are never playable maps." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapBoundaryThickness_MetaData[] = {
		{ "Category", "World|Legacy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy configuration retained for compatibility. Source-mask edges now own collision; rectangular inset walls are disabled. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy configuration retained for compatibility. Source-mask edges now own collision; rectangular inset walls are disabled." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerCollisionProbeRadius_MetaData[] = {
		{ "Category", "World|Map Collision" },
		{ "ClampMax", "200.0" },
		{ "ClampMin", "8.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Exact circular footprint at the tamer's feet, swept across every movement segment against source pixels. */" },
#endif
		{ "DisplayName", "Tamer Footprint Radius" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exact circular footprint at the tamer's feet, swept across every movement segment against source pixels." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRenderCustomDepthByDefault_MetaData[] = {
		{ "Category", "World|Legacy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy key retained for config compatibility. World visuals now always render Custom Depth for cel shading. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy key retained for config compatibility. World visuals now always render Custom Depth for cel shading." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomDepthStencilValue_MetaData[] = {
		{ "Category", "World|Rendering" },
		{ "ClampMax", "255" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Initial stencil value for unassigned map sprites. Existing authored stencil IDs are preserved. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initial stencil value for unassigned map sprites. Existing authored stencil IDs are preserved." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraInitialZoom_MetaData[] = {
		{ "Category", "World|Camera" },
		{ "ClampMax", "8.0" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Zoom relative to fitting the complete source map into the current viewport. One fits the whole map. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zoom relative to fitting the complete source map into the current viewport. One fits the whole map." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraZoomIncrement_MetaData[] = {
		{ "Category", "World|Camera" },
		{ "ClampMax", "2.0" },
		{ "ClampMin", "0.05" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraOrthoWidth_MetaData[] = {
		{ "Category", "World|Legacy" },
		{ "ClampMax", "10000.0" },
		{ "ClampMin", "500.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy fixed-world-unit zoom keys are retained for existing config; source-fit camera uses the settings above. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy fixed-world-unit zoom keys are retained for existing config; source-fit camera uses the settings above." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraMinOrthoWidth_MetaData[] = {
		{ "Category", "World|Legacy" },
		{ "ClampMax", "10000.0" },
		{ "ClampMin", "300.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraMaxOrthoWidth_MetaData[] = {
		{ "Category", "World|Legacy" },
		{ "ClampMax", "20000.0" },
		{ "ClampMin", "500.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraZoomStep_MetaData[] = {
		{ "Category", "World|Legacy" },
		{ "ClampMax", "2000.0" },
		{ "ClampMin", "25.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraBoomLength_MetaData[] = {
		{ "Category", "World|Camera" },
		{ "ClampMax", "10000.0" },
		{ "ClampMin", "1000.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldCameraPitch_MetaData[] = {
		{ "Category", "World|Camera" },
		{ "ClampMax", "-25.0" },
		{ "ClampMin", "-90.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy angled-camera pitch used only when true top-down presentation is disabled. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy angled-camera pitch used only when true top-down presentation is disabled." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseTrueTopDownFieldCamera_MetaData[] = {
		{ "Category", "World|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Recommended field mode. Renders the imported map artwork face-on like a handheld 2D RPG, eliminating oblique Paper2D scanline aliasing. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Recommended field mode. Renders the imported map artwork face-on like a handheld 2D RPG, eliminating oblique Paper2D scanline aliasing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TopDownFieldCameraOrthoWidth_MetaData[] = {
		{ "Category", "World|Legacy" },
		{ "ClampMax", "6000.0" },
		{ "ClampMin", "700.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy fixed orthographic width. The source-fit camera now derives width from source-map dimensions and viewport aspect ratio. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy fixed orthographic width. The source-fit camera now derives width from source-map dimensions and viewport aspect ratio." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowerTrailDistance_MetaData[] = {
		{ "Category", "World|Follower" },
		{ "ClampMax", "800.0" },
		{ "ClampMin", "80.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowerFollowSpeed_MetaData[] = {
		{ "Category", "World|Follower" },
		{ "ClampMax", "30.0" },
		{ "ClampMin", "1.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowerSnapDistance_MetaData[] = {
		{ "Category", "World|Follower" },
		{ "ClampMax", "10000.0" },
		{ "ClampMin", "300.0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxFarmResidents_MetaData[] = {
		{ "Category", "DigiFarm" },
		{ "ClampMax", "500" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ABIMeatCreditCost_MetaData[] = {
		{ "Category", "DigiFarm" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ABIMeatRubyCost_MetaData[] = {
		{ "Category", "DigiFarm" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxABI_MetaData[] = {
		{ "Category", "Evolution" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinimumDeEvolutionLevel_MetaData[] = {
		{ "Category", "Evolution" },
		{ "ClampMax", "200" },
		{ "ClampMin", "2" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Form changes return to level 1; this gate prevents repeat level-1 ABI farming. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Form changes return to level 1; this gate prevents repeat level-1 ABI farming." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EvolutionBaseABI_MetaData[] = {
		{ "Category", "Evolution|ABI Gains" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EvolutionLevelsPerABI_MetaData[] = {
		{ "Category", "Evolution|ABI Gains" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeEvolutionBaseABI_MetaData[] = {
		{ "Category", "Evolution|ABI Gains" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeEvolutionLevelsPerABI_MetaData[] = {
		{ "Category", "Evolution|ABI Gains" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InTrainingEvolutionCAM_MetaData[] = {
		{ "Category", "Evolution|Requirements" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RookieEvolutionCAM_MetaData[] = {
		{ "Category", "Evolution|Requirements" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChampionEvolutionABI_MetaData[] = {
		{ "Category", "Evolution|Requirements" },
		{ "ClampMax", "200" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UltimateEvolutionABI_MetaData[] = {
		{ "Category", "Evolution|Requirements" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MegaEvolutionABI_MetaData[] = {
		{ "Category", "Evolution|Requirements" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TrainingBaseCapacity_MetaData[] = {
		{ "Category", "Evolution|Training" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Flat total training budget shared by HP, SP and battle stats. Existing excess bonuses are preserved. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Flat total training budget shared by HP, SP and battle stats. Existing excess bonuses are preserved." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyCAMIntervalSeconds_MetaData[] = {
		{ "Category", "Party|Friendship" },
		{ "ClampMax", "86400.0" },
		{ "ClampMin", "10.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Online time in the active or reserve party awards CAM; boxed partners do not gain it. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Online time in the active or reserve party awards CAM; boxed partners do not gain it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyCAMGain_MetaData[] = {
		{ "Category", "Party|Friendship" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CAMMeatCreditCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CAMMeatRubyCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CAMMeatGain_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ABIMeatGain_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreditsPerDigiRuby_MetaData[] = {
		{ "Category", "Economy" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShopCreditPriceOverrides_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional per-item money prices. Keys are canonical IDs from DigimonShop.json, such as hp_m or digimeat_atk_2. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional per-item money prices. Keys are canonical IDs from DigimonShop.json, such as hp_m or digimeat_atk_2." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShopDigiRubyPriceOverrides_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional per-item DigiRuby prices. Overrides take precedence over source and individual item settings. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional per-item DigiRuby prices. Overrides take precedence over source and individual item settings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonStartingLevel_MetaData[] = {
		{ "Category", "Season Career|Progression" },
		{ "ClampMax", "200" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zero seeds the career from the first three active partners average level; a positive value overrides that starting level." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonWeeksPerLevel_MetaData[] = {
		{ "Category", "Season Career|Progression" },
		{ "ClampMax", "52" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Completed career matches per opponent level increase; includes title challenges. */" },
#endif
		{ "DisplayName", "Season Matches Per Level" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Completed career matches per opponent level increase; includes title challenges." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMaxOpponentLevel_MetaData[] = {
		{ "Category", "Season Career|Progression" },
		{ "ClampMax", "200" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonTitleIntervalWeeks_MetaData[] = {
		{ "Category", "Season Career|Championship" },
		{ "ClampMax", "52" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonDefenseRewardInterval_MetaData[] = {
		{ "Category", "Season Career|Championship" },
		{ "ClampMax", "100" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonDefenseRewardCredits_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonTitleWinCredits_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMatchBaseCredits_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMatchCreditsPerLevel_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMonthlyBaseCredits_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMonthlyCreditsPerWin_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMonthlyRankBonus_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonMonthlyChampionBonus_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonYearlyBaseCredits_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonYearlyCreditsPerWin_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonYearlyRankBonus_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonYearlyChampionBonus_MetaData[] = {
		{ "Category", "Season Career|Rewards" },
		{ "ClampMax", "1000000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonArchiveWeeks_MetaData[] = {
		{ "Category", "Season Career|History" },
		{ "ClampMax", "16" },
		{ "ClampMin", "4" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonPayoutHistoryCount_MetaData[] = {
		{ "Category", "Season Career|History" },
		{ "ClampMax", "128" },
		{ "ClampMin", "12" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedSeasonDays_MetaData[] = {
		{ "Category", "Ranked|Seasons" },
		{ "ClampMax", "30" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** UTC ranked seasons begin on fixed boundaries anchored to Monday, 5 January 1970. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UTC ranked seasons begin on fixed boundaries anchored to Monday, 5 January 1970." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedMaxEnergy_MetaData[] = {
		{ "Category", "Ranked|Energy" },
		{ "ClampMax", "999" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedEnergyRechargeSeconds_MetaData[] = {
		{ "Category", "Ranked|Energy" },
		{ "ClampMax", "86400" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedGradeRatingThresholds_MetaData[] = {
		{ "Category", "Ranked|Grades" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Bronze, Silver, Gold, Platinum, Diamond, Champion: six increasing source-game point thresholds. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bronze, Silver, Gold, Platinum, Diamond, Champion: six increasing source-game point thresholds." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedWinPoints_MetaData[] = {
		{ "Category", "Ranked|Points" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedLossPoints_MetaData[] = {
		{ "Category", "Ranked|Points" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRankedAllowAIRivals_MetaData[] = {
		{ "Category", "Ranked|Matchmaking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Persisted actual bot parties fill the ladder when human defense snapshots are scarce. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Persisted actual bot parties fill the ladder when human defense snapshots are scarce." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedSeasonRatingRetention_MetaData[] = {
		{ "Category", "Ranked|Seasons" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fraction of ranked points retained at season rollover; zero matches the source game. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fraction of ranked points retained at season rollover; zero matches the source game." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedMinimumRewardMatches_MetaData[] = {
		{ "Category", "Ranked|Rewards" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedPlacementDigiRubies_MetaData[] = {
		{ "Category", "Ranked|Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Human-only placement rewards for ranks 1, 2-10, 11-25, 26-50, 51-100, 101-500 and all other eligible players. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Human-only placement rewards for ranks 1, 2-10, 11-25, 26-50, 51-100, 101-500 and all other eligible players." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedGradeDigiRubies_MetaData[] = {
		{ "Category", "Ranked|Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Season participation reward by final grade, Bronze through Champion. Added to any placement bonus. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Season participation reward by final grade, Bronze through Champion. Added to any placement bonus." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SmallHPCapsuleCreditCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SmallHPCapsuleRubyCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SmallSPCapsuleCreditCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SmallSPCapsuleRubyCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiMeatCreditCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiMeatRubyCost_MetaData[] = {
		{ "Category", "Economy|Shop" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableGlobalAutosaves_MetaData[] = {
		{ "Category", "Persistence" },
		{ "DisplayName", "Enable Global Autosaves" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "OFF by default. Disables automatic player, ranked, commerce and AI-rival saves. Admin /saveall and admin logout still save all online and disconnected profiles. Ordinary player logout only retains progress in server memory. Unsaved progress is lost if the server crashes or is forcibly terminated." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AutoSaveIntervalSeconds_MetaData[] = {
		{ "Category", "Persistence" },
		{ "ClampMax", "1800.0" },
		{ "ClampMin", "10.0" },
		{ "EditCondition", "bEnableGlobalAutosaves" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSettings.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTSettings constinit property declarations *****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultMasterVolume;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultMusicVolume;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultEffectsVolume;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultUIVolume;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SoundEffectOverrides_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_SoundEffectOverrides_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_SoundEffectOverrides;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MainMenuMap;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PublicWorldMap;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerDisplayName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PublicGameAddress;
	static const UECodeGen_Private::FIntPropertyParams NewProp_GameplayPort;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPlayers;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AdminHostPassword;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PasswordHashIterations;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPartySize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ActiveBattleSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPartnerLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_StarterLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NormalSpeciesCapacity;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ScanCapPercent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaterializeRequirementPercent;
	static void NewProp_bConsumeScanOnMaterialize_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSettings*)Obj)->bConsumeScanOnMaterialize = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bConsumeScanOnMaterialize;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ParadoxChance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ShinyChance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FirewallChance;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BaseScanGain;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RareScanGain;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExperienceRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoneyRewardRate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PublicAtlasMapCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RegionCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPersistentAIRivals;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AIRivalSimulationIntervalSeconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalRecordsPerStep;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalActionIntervalSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AIRivalSimulationBudgetMilliseconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalMaxCollectionSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalMaxScanRecords;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalTrainingBattlesPerParty;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalTrainingLevelSpan;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AIRivalMapBalanceReviewActions;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AIRivalSaveIntervalSeconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxVisibleAIRivalsPerMap;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LocalChatRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxChatCharacters;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TamerWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TamerFieldSpriteScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FollowerFieldSpriteScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WildEncounterCooldownSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EncounterStepDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EncounterChancePerStep;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EncounterSafeDistanceAfterTravel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MapWorldWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MapBoundaryThickness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TamerCollisionProbeRadius;
	static void NewProp_bRenderCustomDepthByDefault_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSettings*)Obj)->bRenderCustomDepthByDefault = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRenderCustomDepthByDefault;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CustomDepthStencilValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraInitialZoom;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraZoomIncrement;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraOrthoWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraMinOrthoWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraMaxOrthoWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraZoomStep;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraBoomLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FieldCameraPitch;
	static void NewProp_bUseTrueTopDownFieldCamera_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSettings*)Obj)->bUseTrueTopDownFieldCamera = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseTrueTopDownFieldCamera;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TopDownFieldCameraOrthoWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FollowerTrailDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FollowerFollowSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FollowerSnapDistance;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxFarmResidents;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ABIMeatCreditCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ABIMeatRubyCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MinimumDeEvolutionLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EvolutionBaseABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EvolutionLevelsPerABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DeEvolutionBaseABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DeEvolutionLevelsPerABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InTrainingEvolutionCAM;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RookieEvolutionCAM;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChampionEvolutionABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_UltimateEvolutionABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MegaEvolutionABI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TrainingBaseCapacity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PartyCAMIntervalSeconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PartyCAMGain;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CAMMeatCreditCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CAMMeatRubyCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CAMMeatGain;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ABIMeatGain;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CreditsPerDigiRuby;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ShopCreditPriceOverrides_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ShopCreditPriceOverrides_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ShopCreditPriceOverrides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ShopDigiRubyPriceOverrides_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ShopDigiRubyPriceOverrides_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ShopDigiRubyPriceOverrides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonStartingLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonWeeksPerLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMaxOpponentLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonTitleIntervalWeeks;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonDefenseRewardInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonDefenseRewardCredits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonTitleWinCredits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMatchBaseCredits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMatchCreditsPerLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMonthlyBaseCredits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMonthlyCreditsPerWin;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMonthlyRankBonus;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonMonthlyChampionBonus;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonYearlyBaseCredits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonYearlyCreditsPerWin;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonYearlyRankBonus;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonYearlyChampionBonus;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonArchiveWeeks;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SeasonPayoutHistoryCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedSeasonDays;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedMaxEnergy;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedEnergyRechargeSeconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedGradeRatingThresholds_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RankedGradeRatingThresholds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedWinPoints;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedLossPoints;
	static void NewProp_bRankedAllowAIRivals_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSettings*)Obj)->bRankedAllowAIRivals = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRankedAllowAIRivals;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RankedSeasonRatingRetention;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedMinimumRewardMatches;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedPlacementDigiRubies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RankedPlacementDigiRubies;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RankedGradeDigiRubies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RankedGradeDigiRubies;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SmallHPCapsuleCreditCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SmallHPCapsuleRubyCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SmallSPCapsuleCreditCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SmallSPCapsuleRubyCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiMeatCreditCost;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiMeatRubyCost;
	static void NewProp_bEnableGlobalAutosaves_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSettings*)Obj)->bEnableGlobalAutosaves = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableGlobalAutosaves;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AutoSaveIntervalSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTSettings constinit property declarations *******************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTSettings Property Definitions ****************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DefaultMasterVolume = { "DefaultMasterVolume", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DefaultMasterVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMasterVolume_MetaData), NewProp_DefaultMasterVolume_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DefaultMusicVolume = { "DefaultMusicVolume", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DefaultMusicVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMusicVolume_MetaData), NewProp_DefaultMusicVolume_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DefaultEffectsVolume = { "DefaultEffectsVolume", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DefaultEffectsVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultEffectsVolume_MetaData), NewProp_DefaultEffectsVolume_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DefaultUIVolume = { "DefaultUIVolume", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DefaultUIVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultUIVolume_MetaData), NewProp_DefaultUIVolume_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SoundEffectOverrides_ValueProp = { "SoundEffectOverrides", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(0, nullptr) }; // af11f93e8a98b61a8502d3dfb50f3175321d399c
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SoundEffectOverrides_Key_KeyProp = { "SoundEffectOverrides_Key", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_SoundEffectOverrides = { "SoundEffectOverrides", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SoundEffectOverrides), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundEffectOverrides_MetaData), NewProp_SoundEffectOverrides_MetaData) }; // af11f93e8a98b61a8502d3dfb50f3175321d399c
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_MainMenuMap = { "MainMenuMap", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MainMenuMap), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainMenuMap_MetaData), NewProp_MainMenuMap_MetaData) }; // af11f93e8a98b61a8502d3dfb50f3175321d399c
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PublicWorldMap = { "PublicWorldMap", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PublicWorldMap), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PublicWorldMap_MetaData), NewProp_PublicWorldMap_MetaData) }; // af11f93e8a98b61a8502d3dfb50f3175321d399c
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ServerDisplayName = { "ServerDisplayName", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ServerDisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerDisplayName_MetaData), NewProp_ServerDisplayName_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_PublicGameAddress = { "PublicGameAddress", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PublicGameAddress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PublicGameAddress_MetaData), NewProp_PublicGameAddress_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_GameplayPort = { "GameplayPort", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, GameplayPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GameplayPort_MetaData), NewProp_GameplayPort_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxPlayers = { "MaxPlayers", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxPlayers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPlayers_MetaData), NewProp_MaxPlayers_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AdminHostPassword = { "AdminHostPassword", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AdminHostPassword), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdminHostPassword_MetaData), NewProp_AdminHostPassword_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PasswordHashIterations = { "PasswordHashIterations", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PasswordHashIterations), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PasswordHashIterations_MetaData), NewProp_PasswordHashIterations_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxPartySize = { "MaxPartySize", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxPartySize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPartySize_MetaData), NewProp_MaxPartySize_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ActiveBattleSize = { "ActiveBattleSize", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ActiveBattleSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveBattleSize_MetaData), NewProp_ActiveBattleSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxPartnerLevel = { "MaxPartnerLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxPartnerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPartnerLevel_MetaData), NewProp_MaxPartnerLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_StarterLevel = { "StarterLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, StarterLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StarterLevel_MetaData), NewProp_StarterLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NormalSpeciesCapacity = { "NormalSpeciesCapacity", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, NormalSpeciesCapacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NormalSpeciesCapacity_MetaData), NewProp_NormalSpeciesCapacity_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ScanCapPercent = { "ScanCapPercent", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ScanCapPercent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanCapPercent_MetaData), NewProp_ScanCapPercent_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaterializeRequirementPercent = { "MaterializeRequirementPercent", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaterializeRequirementPercent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterializeRequirementPercent_MetaData), NewProp_MaterializeRequirementPercent_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bConsumeScanOnMaterialize = { "bConsumeScanOnMaterialize", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSettings), &UHT_STATICS::NewProp_bConsumeScanOnMaterialize_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bConsumeScanOnMaterialize_MetaData), NewProp_bConsumeScanOnMaterialize_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ParadoxChance = { "ParadoxChance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ParadoxChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParadoxChance_MetaData), NewProp_ParadoxChance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ShinyChance = { "ShinyChance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ShinyChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShinyChance_MetaData), NewProp_ShinyChance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FirewallChance = { "FirewallChance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FirewallChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirewallChance_MetaData), NewProp_FirewallChance_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_BaseScanGain = { "BaseScanGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, BaseScanGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseScanGain_MetaData), NewProp_BaseScanGain_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RareScanGain = { "RareScanGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RareScanGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RareScanGain_MetaData), NewProp_RareScanGain_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ExperienceRate = { "ExperienceRate", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ExperienceRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExperienceRate_MetaData), NewProp_ExperienceRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MoneyRewardRate = { "MoneyRewardRate", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MoneyRewardRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoneyRewardRate_MetaData), NewProp_MoneyRewardRate_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PublicAtlasMapCount = { "PublicAtlasMapCount", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PublicAtlasMapCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PublicAtlasMapCount_MetaData), NewProp_PublicAtlasMapCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RegionCount = { "RegionCount", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RegionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RegionCount_MetaData), NewProp_RegionCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxPersistentAIRivals = { "MaxPersistentAIRivals", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxPersistentAIRivals), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPersistentAIRivals_MetaData), NewProp_MaxPersistentAIRivals_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AIRivalSimulationIntervalSeconds = { "AIRivalSimulationIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalSimulationIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalSimulationIntervalSeconds_MetaData), NewProp_AIRivalSimulationIntervalSeconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalRecordsPerStep = { "AIRivalRecordsPerStep", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalRecordsPerStep), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalRecordsPerStep_MetaData), NewProp_AIRivalRecordsPerStep_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalActionIntervalSeconds = { "AIRivalActionIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalActionIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalActionIntervalSeconds_MetaData), NewProp_AIRivalActionIntervalSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AIRivalSimulationBudgetMilliseconds = { "AIRivalSimulationBudgetMilliseconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalSimulationBudgetMilliseconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalSimulationBudgetMilliseconds_MetaData), NewProp_AIRivalSimulationBudgetMilliseconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalMaxCollectionSize = { "AIRivalMaxCollectionSize", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalMaxCollectionSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalMaxCollectionSize_MetaData), NewProp_AIRivalMaxCollectionSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalMaxScanRecords = { "AIRivalMaxScanRecords", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalMaxScanRecords), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalMaxScanRecords_MetaData), NewProp_AIRivalMaxScanRecords_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalTrainingBattlesPerParty = { "AIRivalTrainingBattlesPerParty", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalTrainingBattlesPerParty), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalTrainingBattlesPerParty_MetaData), NewProp_AIRivalTrainingBattlesPerParty_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalTrainingLevelSpan = { "AIRivalTrainingLevelSpan", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalTrainingLevelSpan), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalTrainingLevelSpan_MetaData), NewProp_AIRivalTrainingLevelSpan_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AIRivalMapBalanceReviewActions = { "AIRivalMapBalanceReviewActions", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalMapBalanceReviewActions), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalMapBalanceReviewActions_MetaData), NewProp_AIRivalMapBalanceReviewActions_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AIRivalSaveIntervalSeconds = { "AIRivalSaveIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AIRivalSaveIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIRivalSaveIntervalSeconds_MetaData), NewProp_AIRivalSaveIntervalSeconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxVisibleAIRivalsPerMap = { "MaxVisibleAIRivalsPerMap", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxVisibleAIRivalsPerMap), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxVisibleAIRivalsPerMap_MetaData), NewProp_MaxVisibleAIRivalsPerMap_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LocalChatRadius = { "LocalChatRadius", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, LocalChatRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalChatRadius_MetaData), NewProp_LocalChatRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxChatCharacters = { "MaxChatCharacters", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxChatCharacters), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxChatCharacters_MetaData), NewProp_MaxChatCharacters_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TamerWalkSpeed = { "TamerWalkSpeed", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, TamerWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerWalkSpeed_MetaData), NewProp_TamerWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TamerFieldSpriteScale = { "TamerFieldSpriteScale", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, TamerFieldSpriteScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerFieldSpriteScale_MetaData), NewProp_TamerFieldSpriteScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FollowerFieldSpriteScale = { "FollowerFieldSpriteScale", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FollowerFieldSpriteScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowerFieldSpriteScale_MetaData), NewProp_FollowerFieldSpriteScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WildEncounterCooldownSeconds = { "WildEncounterCooldownSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, WildEncounterCooldownSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WildEncounterCooldownSeconds_MetaData), NewProp_WildEncounterCooldownSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_EncounterStepDistance = { "EncounterStepDistance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, EncounterStepDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EncounterStepDistance_MetaData), NewProp_EncounterStepDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_EncounterChancePerStep = { "EncounterChancePerStep", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, EncounterChancePerStep), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EncounterChancePerStep_MetaData), NewProp_EncounterChancePerStep_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_EncounterSafeDistanceAfterTravel = { "EncounterSafeDistanceAfterTravel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, EncounterSafeDistanceAfterTravel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EncounterSafeDistanceAfterTravel_MetaData), NewProp_EncounterSafeDistanceAfterTravel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MapWorldWidth = { "MapWorldWidth", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MapWorldWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapWorldWidth_MetaData), NewProp_MapWorldWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MapBoundaryThickness = { "MapBoundaryThickness", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MapBoundaryThickness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapBoundaryThickness_MetaData), NewProp_MapBoundaryThickness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TamerCollisionProbeRadius = { "TamerCollisionProbeRadius", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, TamerCollisionProbeRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerCollisionProbeRadius_MetaData), NewProp_TamerCollisionProbeRadius_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRenderCustomDepthByDefault = { "bRenderCustomDepthByDefault", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSettings), &UHT_STATICS::NewProp_bRenderCustomDepthByDefault_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRenderCustomDepthByDefault_MetaData), NewProp_bRenderCustomDepthByDefault_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CustomDepthStencilValue = { "CustomDepthStencilValue", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, CustomDepthStencilValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomDepthStencilValue_MetaData), NewProp_CustomDepthStencilValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraInitialZoom = { "FieldCameraInitialZoom", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraInitialZoom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraInitialZoom_MetaData), NewProp_FieldCameraInitialZoom_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraZoomIncrement = { "FieldCameraZoomIncrement", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraZoomIncrement), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraZoomIncrement_MetaData), NewProp_FieldCameraZoomIncrement_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraOrthoWidth = { "FieldCameraOrthoWidth", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraOrthoWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraOrthoWidth_MetaData), NewProp_FieldCameraOrthoWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraMinOrthoWidth = { "FieldCameraMinOrthoWidth", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraMinOrthoWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraMinOrthoWidth_MetaData), NewProp_FieldCameraMinOrthoWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraMaxOrthoWidth = { "FieldCameraMaxOrthoWidth", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraMaxOrthoWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraMaxOrthoWidth_MetaData), NewProp_FieldCameraMaxOrthoWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraZoomStep = { "FieldCameraZoomStep", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraZoomStep), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraZoomStep_MetaData), NewProp_FieldCameraZoomStep_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraBoomLength = { "FieldCameraBoomLength", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraBoomLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraBoomLength_MetaData), NewProp_FieldCameraBoomLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FieldCameraPitch = { "FieldCameraPitch", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FieldCameraPitch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldCameraPitch_MetaData), NewProp_FieldCameraPitch_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bUseTrueTopDownFieldCamera = { "bUseTrueTopDownFieldCamera", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSettings), &UHT_STATICS::NewProp_bUseTrueTopDownFieldCamera_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseTrueTopDownFieldCamera_MetaData), NewProp_bUseTrueTopDownFieldCamera_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TopDownFieldCameraOrthoWidth = { "TopDownFieldCameraOrthoWidth", nullptr, (EPropertyFlags)0x0010000000004014, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, TopDownFieldCameraOrthoWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TopDownFieldCameraOrthoWidth_MetaData), NewProp_TopDownFieldCameraOrthoWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FollowerTrailDistance = { "FollowerTrailDistance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FollowerTrailDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowerTrailDistance_MetaData), NewProp_FollowerTrailDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FollowerFollowSpeed = { "FollowerFollowSpeed", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FollowerFollowSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowerFollowSpeed_MetaData), NewProp_FollowerFollowSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FollowerSnapDistance = { "FollowerSnapDistance", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, FollowerSnapDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowerSnapDistance_MetaData), NewProp_FollowerSnapDistance_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxFarmResidents = { "MaxFarmResidents", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxFarmResidents), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxFarmResidents_MetaData), NewProp_MaxFarmResidents_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ABIMeatCreditCost = { "ABIMeatCreditCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ABIMeatCreditCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ABIMeatCreditCost_MetaData), NewProp_ABIMeatCreditCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ABIMeatRubyCost = { "ABIMeatRubyCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ABIMeatRubyCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ABIMeatRubyCost_MetaData), NewProp_ABIMeatRubyCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxABI = { "MaxABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MaxABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxABI_MetaData), NewProp_MaxABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MinimumDeEvolutionLevel = { "MinimumDeEvolutionLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MinimumDeEvolutionLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinimumDeEvolutionLevel_MetaData), NewProp_MinimumDeEvolutionLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_EvolutionBaseABI = { "EvolutionBaseABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, EvolutionBaseABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EvolutionBaseABI_MetaData), NewProp_EvolutionBaseABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_EvolutionLevelsPerABI = { "EvolutionLevelsPerABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, EvolutionLevelsPerABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EvolutionLevelsPerABI_MetaData), NewProp_EvolutionLevelsPerABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DeEvolutionBaseABI = { "DeEvolutionBaseABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DeEvolutionBaseABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeEvolutionBaseABI_MetaData), NewProp_DeEvolutionBaseABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DeEvolutionLevelsPerABI = { "DeEvolutionLevelsPerABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DeEvolutionLevelsPerABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeEvolutionLevelsPerABI_MetaData), NewProp_DeEvolutionLevelsPerABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_InTrainingEvolutionCAM = { "InTrainingEvolutionCAM", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, InTrainingEvolutionCAM), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InTrainingEvolutionCAM_MetaData), NewProp_InTrainingEvolutionCAM_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RookieEvolutionCAM = { "RookieEvolutionCAM", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RookieEvolutionCAM), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RookieEvolutionCAM_MetaData), NewProp_RookieEvolutionCAM_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ChampionEvolutionABI = { "ChampionEvolutionABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ChampionEvolutionABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChampionEvolutionABI_MetaData), NewProp_ChampionEvolutionABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_UltimateEvolutionABI = { "UltimateEvolutionABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, UltimateEvolutionABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UltimateEvolutionABI_MetaData), NewProp_UltimateEvolutionABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MegaEvolutionABI = { "MegaEvolutionABI", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, MegaEvolutionABI), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MegaEvolutionABI_MetaData), NewProp_MegaEvolutionABI_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TrainingBaseCapacity = { "TrainingBaseCapacity", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, TrainingBaseCapacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TrainingBaseCapacity_MetaData), NewProp_TrainingBaseCapacity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_PartyCAMIntervalSeconds = { "PartyCAMIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PartyCAMIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyCAMIntervalSeconds_MetaData), NewProp_PartyCAMIntervalSeconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PartyCAMGain = { "PartyCAMGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, PartyCAMGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyCAMGain_MetaData), NewProp_PartyCAMGain_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CAMMeatCreditCost = { "CAMMeatCreditCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, CAMMeatCreditCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CAMMeatCreditCost_MetaData), NewProp_CAMMeatCreditCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CAMMeatRubyCost = { "CAMMeatRubyCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, CAMMeatRubyCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CAMMeatRubyCost_MetaData), NewProp_CAMMeatRubyCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CAMMeatGain = { "CAMMeatGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, CAMMeatGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CAMMeatGain_MetaData), NewProp_CAMMeatGain_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ABIMeatGain = { "ABIMeatGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ABIMeatGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ABIMeatGain_MetaData), NewProp_ABIMeatGain_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CreditsPerDigiRuby = { "CreditsPerDigiRuby", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, CreditsPerDigiRuby), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreditsPerDigiRuby_MetaData), NewProp_CreditsPerDigiRuby_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ShopCreditPriceOverrides_ValueProp = { "ShopCreditPriceOverrides", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ShopCreditPriceOverrides_Key_KeyProp = { "ShopCreditPriceOverrides_Key", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_ShopCreditPriceOverrides = { "ShopCreditPriceOverrides", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ShopCreditPriceOverrides), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShopCreditPriceOverrides_MetaData), NewProp_ShopCreditPriceOverrides_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides_ValueProp = { "ShopDigiRubyPriceOverrides", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides_Key_KeyProp = { "ShopDigiRubyPriceOverrides_Key", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides = { "ShopDigiRubyPriceOverrides", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, ShopDigiRubyPriceOverrides), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShopDigiRubyPriceOverrides_MetaData), NewProp_ShopDigiRubyPriceOverrides_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonStartingLevel = { "SeasonStartingLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonStartingLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonStartingLevel_MetaData), NewProp_SeasonStartingLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonWeeksPerLevel = { "SeasonWeeksPerLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonWeeksPerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonWeeksPerLevel_MetaData), NewProp_SeasonWeeksPerLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMaxOpponentLevel = { "SeasonMaxOpponentLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMaxOpponentLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMaxOpponentLevel_MetaData), NewProp_SeasonMaxOpponentLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonTitleIntervalWeeks = { "SeasonTitleIntervalWeeks", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonTitleIntervalWeeks), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonTitleIntervalWeeks_MetaData), NewProp_SeasonTitleIntervalWeeks_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonDefenseRewardInterval = { "SeasonDefenseRewardInterval", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonDefenseRewardInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonDefenseRewardInterval_MetaData), NewProp_SeasonDefenseRewardInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonDefenseRewardCredits = { "SeasonDefenseRewardCredits", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonDefenseRewardCredits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonDefenseRewardCredits_MetaData), NewProp_SeasonDefenseRewardCredits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonTitleWinCredits = { "SeasonTitleWinCredits", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonTitleWinCredits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonTitleWinCredits_MetaData), NewProp_SeasonTitleWinCredits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMatchBaseCredits = { "SeasonMatchBaseCredits", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMatchBaseCredits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMatchBaseCredits_MetaData), NewProp_SeasonMatchBaseCredits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMatchCreditsPerLevel = { "SeasonMatchCreditsPerLevel", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMatchCreditsPerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMatchCreditsPerLevel_MetaData), NewProp_SeasonMatchCreditsPerLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMonthlyBaseCredits = { "SeasonMonthlyBaseCredits", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMonthlyBaseCredits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMonthlyBaseCredits_MetaData), NewProp_SeasonMonthlyBaseCredits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMonthlyCreditsPerWin = { "SeasonMonthlyCreditsPerWin", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMonthlyCreditsPerWin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMonthlyCreditsPerWin_MetaData), NewProp_SeasonMonthlyCreditsPerWin_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMonthlyRankBonus = { "SeasonMonthlyRankBonus", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMonthlyRankBonus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMonthlyRankBonus_MetaData), NewProp_SeasonMonthlyRankBonus_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonMonthlyChampionBonus = { "SeasonMonthlyChampionBonus", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonMonthlyChampionBonus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonMonthlyChampionBonus_MetaData), NewProp_SeasonMonthlyChampionBonus_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonYearlyBaseCredits = { "SeasonYearlyBaseCredits", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonYearlyBaseCredits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonYearlyBaseCredits_MetaData), NewProp_SeasonYearlyBaseCredits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonYearlyCreditsPerWin = { "SeasonYearlyCreditsPerWin", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonYearlyCreditsPerWin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonYearlyCreditsPerWin_MetaData), NewProp_SeasonYearlyCreditsPerWin_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonYearlyRankBonus = { "SeasonYearlyRankBonus", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonYearlyRankBonus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonYearlyRankBonus_MetaData), NewProp_SeasonYearlyRankBonus_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonYearlyChampionBonus = { "SeasonYearlyChampionBonus", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonYearlyChampionBonus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonYearlyChampionBonus_MetaData), NewProp_SeasonYearlyChampionBonus_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonArchiveWeeks = { "SeasonArchiveWeeks", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonArchiveWeeks), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonArchiveWeeks_MetaData), NewProp_SeasonArchiveWeeks_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SeasonPayoutHistoryCount = { "SeasonPayoutHistoryCount", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SeasonPayoutHistoryCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonPayoutHistoryCount_MetaData), NewProp_SeasonPayoutHistoryCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedSeasonDays = { "RankedSeasonDays", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedSeasonDays), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedSeasonDays_MetaData), NewProp_RankedSeasonDays_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedMaxEnergy = { "RankedMaxEnergy", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedMaxEnergy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedMaxEnergy_MetaData), NewProp_RankedMaxEnergy_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedEnergyRechargeSeconds = { "RankedEnergyRechargeSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedEnergyRechargeSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedEnergyRechargeSeconds_MetaData), NewProp_RankedEnergyRechargeSeconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedGradeRatingThresholds_Inner = { "RankedGradeRatingThresholds", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RankedGradeRatingThresholds = { "RankedGradeRatingThresholds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedGradeRatingThresholds), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedGradeRatingThresholds_MetaData), NewProp_RankedGradeRatingThresholds_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedWinPoints = { "RankedWinPoints", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedWinPoints), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedWinPoints_MetaData), NewProp_RankedWinPoints_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedLossPoints = { "RankedLossPoints", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedLossPoints), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedLossPoints_MetaData), NewProp_RankedLossPoints_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRankedAllowAIRivals = { "bRankedAllowAIRivals", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSettings), &UHT_STATICS::NewProp_bRankedAllowAIRivals_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRankedAllowAIRivals_MetaData), NewProp_bRankedAllowAIRivals_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RankedSeasonRatingRetention = { "RankedSeasonRatingRetention", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedSeasonRatingRetention), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedSeasonRatingRetention_MetaData), NewProp_RankedSeasonRatingRetention_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedMinimumRewardMatches = { "RankedMinimumRewardMatches", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedMinimumRewardMatches), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedMinimumRewardMatches_MetaData), NewProp_RankedMinimumRewardMatches_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedPlacementDigiRubies_Inner = { "RankedPlacementDigiRubies", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RankedPlacementDigiRubies = { "RankedPlacementDigiRubies", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedPlacementDigiRubies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedPlacementDigiRubies_MetaData), NewProp_RankedPlacementDigiRubies_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RankedGradeDigiRubies_Inner = { "RankedGradeDigiRubies", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RankedGradeDigiRubies = { "RankedGradeDigiRubies", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, RankedGradeDigiRubies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedGradeDigiRubies_MetaData), NewProp_RankedGradeDigiRubies_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SmallHPCapsuleCreditCost = { "SmallHPCapsuleCreditCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SmallHPCapsuleCreditCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SmallHPCapsuleCreditCost_MetaData), NewProp_SmallHPCapsuleCreditCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SmallHPCapsuleRubyCost = { "SmallHPCapsuleRubyCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SmallHPCapsuleRubyCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SmallHPCapsuleRubyCost_MetaData), NewProp_SmallHPCapsuleRubyCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SmallSPCapsuleCreditCost = { "SmallSPCapsuleCreditCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SmallSPCapsuleCreditCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SmallSPCapsuleCreditCost_MetaData), NewProp_SmallSPCapsuleCreditCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SmallSPCapsuleRubyCost = { "SmallSPCapsuleRubyCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, SmallSPCapsuleRubyCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SmallSPCapsuleRubyCost_MetaData), NewProp_SmallSPCapsuleRubyCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiMeatCreditCost = { "DigiMeatCreditCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DigiMeatCreditCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiMeatCreditCost_MetaData), NewProp_DigiMeatCreditCost_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiMeatRubyCost = { "DigiMeatRubyCost", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, DigiMeatRubyCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiMeatRubyCost_MetaData), NewProp_DigiMeatRubyCost_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnableGlobalAutosaves = { "bEnableGlobalAutosaves", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSettings), &UHT_STATICS::NewProp_bEnableGlobalAutosaves_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableGlobalAutosaves_MetaData), NewProp_bEnableGlobalAutosaves_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AutoSaveIntervalSeconds = { "AutoSaveIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSettings, AutoSaveIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AutoSaveIntervalSeconds_MetaData), NewProp_AutoSaveIntervalSeconds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultMasterVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultMusicVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultEffectsVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultUIVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundEffectOverrides_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundEffectOverrides_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundEffectOverrides,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MainMenuMap,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PublicWorldMap,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ServerDisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PublicGameAddress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GameplayPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdminHostPassword,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PasswordHashIterations,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPartySize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveBattleSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPartnerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StarterLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NormalSpeciesCapacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanCapPercent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaterializeRequirementPercent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bConsumeScanOnMaterialize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ParadoxChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShinyChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FirewallChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BaseScanGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RareScanGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExperienceRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoneyRewardRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PublicAtlasMapCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RegionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPersistentAIRivals,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalSimulationIntervalSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalRecordsPerStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalActionIntervalSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalSimulationBudgetMilliseconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalMaxCollectionSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalMaxScanRecords,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalTrainingBattlesPerParty,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalTrainingLevelSpan,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalMapBalanceReviewActions,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AIRivalSaveIntervalSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxVisibleAIRivalsPerMap,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocalChatRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxChatCharacters,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerFieldSpriteScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowerFieldSpriteScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WildEncounterCooldownSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EncounterStepDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EncounterChancePerStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EncounterSafeDistanceAfterTravel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapWorldWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapBoundaryThickness,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerCollisionProbeRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRenderCustomDepthByDefault,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CustomDepthStencilValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraInitialZoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraZoomIncrement,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraOrthoWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraMinOrthoWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraMaxOrthoWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraZoomStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraBoomLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldCameraPitch,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bUseTrueTopDownFieldCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TopDownFieldCameraOrthoWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowerTrailDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowerFollowSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowerSnapDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxFarmResidents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ABIMeatCreditCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ABIMeatRubyCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinimumDeEvolutionLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EvolutionBaseABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EvolutionLevelsPerABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeEvolutionBaseABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeEvolutionLevelsPerABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InTrainingEvolutionCAM,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RookieEvolutionCAM,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChampionEvolutionABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UltimateEvolutionABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MegaEvolutionABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TrainingBaseCapacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyCAMIntervalSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyCAMGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CAMMeatCreditCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CAMMeatRubyCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CAMMeatGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ABIMeatGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CreditsPerDigiRuby,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopCreditPriceOverrides_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopCreditPriceOverrides_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopCreditPriceOverrides,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopDigiRubyPriceOverrides,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonStartingLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonWeeksPerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMaxOpponentLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonTitleIntervalWeeks,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonDefenseRewardInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonDefenseRewardCredits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonTitleWinCredits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMatchBaseCredits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMatchCreditsPerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMonthlyBaseCredits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMonthlyCreditsPerWin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMonthlyRankBonus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonMonthlyChampionBonus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonYearlyBaseCredits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonYearlyCreditsPerWin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonYearlyRankBonus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonYearlyChampionBonus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonArchiveWeeks,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonPayoutHistoryCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedSeasonDays,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedMaxEnergy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedEnergyRechargeSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedGradeRatingThresholds_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedGradeRatingThresholds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedWinPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedLossPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRankedAllowAIRivals,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedSeasonRatingRetention,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedMinimumRewardMatches,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedPlacementDigiRubies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedPlacementDigiRubies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedGradeDigiRubies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedGradeDigiRubies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SmallHPCapsuleCreditCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SmallHPCapsuleRubyCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SmallSPCapsuleCreditCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SmallSPCapsuleRubyCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiMeatCreditCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiMeatRubyCost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnableGlobalAutosaves,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AutoSaveIntervalSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTSettings Property Definitions ******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDeveloperSettings,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTSettings,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTSettings;
UClass* Z_Construct_UClass_UDigimonVenomNXTSettings(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTSettings;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTSettings.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTSettings"),
				Z_Registration_Info_UClass_UDigimonVenomNXTSettings.InnerSingleton,
				nullptr,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_UDigimonVenomNXTSettings.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTSettings.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTSettings.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTSettings);
UDigimonVenomNXTSettings::~UDigimonVenomNXTSettings() {}
// ********** End Class UDigimonVenomNXTSettings ***************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSettings_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTSettings, TEXT("UDigimonVenomNXTSettings"), &Z_Registration_Info_UClass_UDigimonVenomNXTSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTSettings), 1027485103U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSettings_h__Script_DigimonVenomNXTRuntime_a5f03081c42b4b191fb92c3c982975ad287487f0{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
