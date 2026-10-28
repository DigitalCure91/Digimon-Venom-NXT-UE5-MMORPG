// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTAIRivalAvatar.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAIRivalAvatar_generated_h
#error "DigimonVenomNXTAIRivalAvatar.generated.h already included, missing '#pragma once' in DigimonVenomNXTAIRivalAvatar.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAIRivalAvatar_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDigimonOwnedPartner;

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar ********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_Identity); \
	DECLARE_FUNCTION(execIsForRival); \
	DECLARE_FUNCTION(execRefreshLeaderFollower); \
	DECLARE_FUNCTION(execInitializeAvatar);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTAIRivalAvatar, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar) \
	DECLARE_SERIALIZER(ADigimonVenomNXTAIRivalAvatar) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		RivalId=NETFIELD_REP_START, \
		DisplayName, \
		MapId, \
		TamerLevel, \
		LeaderFollower, \
		NETFIELD_REP_END=LeaderFollower	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTAIRivalAvatar(ADigimonVenomNXTAIRivalAvatar&&) = delete; \
	ADigimonVenomNXTAIRivalAvatar(const ADigimonVenomNXTAIRivalAvatar&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTAIRivalAvatar); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTAIRivalAvatar); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTAIRivalAvatar) \
	NO_API virtual ~ADigimonVenomNXTAIRivalAvatar();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_15_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTAIRivalAvatar;

// ********** End Class ADigimonVenomNXTAIRivalAvatar **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
