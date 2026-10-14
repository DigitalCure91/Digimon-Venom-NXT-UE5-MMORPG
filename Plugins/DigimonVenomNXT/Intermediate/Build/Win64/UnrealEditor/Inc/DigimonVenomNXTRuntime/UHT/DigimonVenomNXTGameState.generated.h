// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTGameState.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTGameState_generated_h
#error "DigimonVenomNXTGameState.generated.h already included, missing '#pragma once' in DigimonVenomNXTGameState.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTGameState_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ADigimonVenomNXTGameState ************************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_ServerState); \
	DECLARE_FUNCTION(execGetOnlinePlayerCount);


struct Z_Construct_UClass_ADigimonVenomNXTGameState_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTGameState(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTGameState_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTGameState(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTGameState, AGameStateBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTGameState) \
	DECLARE_SERIALIZER(ADigimonVenomNXTGameState) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ServerDisplayName=NETFIELD_REP_START, \
		MaxPlayers, \
		AtlasMapCount, \
		PersistentAIRivalCount, \
		ShopCatalog, \
		CreditsPerDigiRuby, \
		RankedSeasonId, \
		RankedTop100, \
		NETFIELD_REP_END=RankedTop100	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTGameState(ADigimonVenomNXTGameState&&) = delete; \
	ADigimonVenomNXTGameState(const ADigimonVenomNXTGameState&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTGameState); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTGameState); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTGameState) \
	NO_API virtual ~ADigimonVenomNXTGameState();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_11_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTGameState;

// ********** End Class ADigimonVenomNXTGameState **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
