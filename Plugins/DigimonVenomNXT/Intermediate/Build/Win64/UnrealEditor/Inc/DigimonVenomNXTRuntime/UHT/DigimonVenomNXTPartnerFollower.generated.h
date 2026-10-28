// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTPartnerFollower.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPartnerFollower_generated_h
#error "DigimonVenomNXTPartnerFollower.generated.h already included, missing '#pragma once' in DigimonVenomNXTPartnerFollower.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPartnerFollower_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ADigimonVenomNXTAIRivalAvatar;
class ADigimonVenomNXTTamerCharacter;
enum class EDigimonVariant : uint8;
struct FDigimonOwnedPartner;

// ********** Begin Class ADigimonVenomNXTPartnerFollower ******************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_Identity); \
	DECLARE_FUNCTION(execSnapToTamer); \
	DECLARE_FUNCTION(execInitializeFromRival); \
	DECLARE_FUNCTION(execInitializeFromPartner);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTPartnerFollower_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTPartnerFollower_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTPartnerFollower, APaperCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTPartnerFollower) \
	DECLARE_SERIALIZER(ADigimonVenomNXTPartnerFollower) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		InstanceId=NETFIELD_REP_START, \
		SpeciesId, \
		Variant, \
		PartnerLevel, \
		Tamer, \
		RivalTamer, \
		NETFIELD_REP_END=RivalTamer	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTPartnerFollower(ADigimonVenomNXTPartnerFollower&&) = delete; \
	ADigimonVenomNXTPartnerFollower(const ADigimonVenomNXTPartnerFollower&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTPartnerFollower); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTPartnerFollower); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTPartnerFollower) \
	NO_API virtual ~ADigimonVenomNXTPartnerFollower();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_13_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTPartnerFollower;

// ********** End Class ADigimonVenomNXTPartnerFollower ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
