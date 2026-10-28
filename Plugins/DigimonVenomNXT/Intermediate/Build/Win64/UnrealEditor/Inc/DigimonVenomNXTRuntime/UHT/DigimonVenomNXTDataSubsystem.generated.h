// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTDataSubsystem.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTDataSubsystem_generated_h
#error "DigimonVenomNXTDataSubsystem.generated.h already included, missing '#pragma once' in DigimonVenomNXTDataSubsystem.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTDataSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDigimonMapRow;
struct FDigimonMoveSlot;
struct FDigimonShopItemDefinition;
struct FDigimonSpeciesDefinition;

// ********** Begin Class UDigimonVenomNXTDataSubsystem ********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetCreditsPerDigiRuby); \
	DECLARE_FUNCTION(execGetShopItem); \
	DECLARE_FUNCTION(execGetShopItems); \
	DECLARE_FUNCTION(execGetConfiguredSpeciesCapacity); \
	DECLARE_FUNCTION(execGetPublicMapCount); \
	DECLARE_FUNCTION(execGetAllMaps); \
	DECLARE_FUNCTION(execGetMap); \
	DECLARE_FUNCTION(execGetProvidedSpeciesCount); \
	DECLARE_FUNCTION(execGetStarterCandidates); \
	DECLARE_FUNCTION(execGetDeEvolutionSources); \
	DECLARE_FUNCTION(execGetMove); \
	DECLARE_FUNCTION(execGetAllSpecies); \
	DECLARE_FUNCTION(execGetSpecies);


struct Z_Construct_UClass_UDigimonVenomNXTDataSubsystem_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDataSubsystem(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTDataSubsystem_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTDataSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTDataSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTDataSubsystem) \
	DECLARE_SERIALIZER(UDigimonVenomNXTDataSubsystem)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTDataSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTDataSubsystem(UDigimonVenomNXTDataSubsystem&&) = delete; \
	UDigimonVenomNXTDataSubsystem(const UDigimonVenomNXTDataSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTDataSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTDataSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTDataSubsystem) \
	NO_API virtual ~UDigimonVenomNXTDataSubsystem();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_8_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTDataSubsystem;

// ********** End Class UDigimonVenomNXTDataSubsystem **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
