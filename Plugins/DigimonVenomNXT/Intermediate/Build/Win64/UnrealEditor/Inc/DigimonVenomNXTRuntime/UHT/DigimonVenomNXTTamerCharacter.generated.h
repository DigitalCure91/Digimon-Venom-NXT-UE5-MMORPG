// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTTamerCharacter.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTTamerCharacter_generated_h
#error "DigimonVenomNXTTamerCharacter.generated.h already included, missing '#pragma once' in DigimonVenomNXTTamerCharacter.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTTamerCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ADigimonVenomNXTPartnerFollower;
enum class EDigimonFacing : uint8;

// ********** Begin Class ADigimonVenomNXTTamerCharacter *******************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerSetFacing_Implementation(EDigimonFacing NewFacing); \
	DECLARE_FUNCTION(execOnRep_Follower); \
	DECLARE_FUNCTION(execOnRep_TamerStyle); \
	DECLARE_FUNCTION(execOnRep_Facing); \
	DECLARE_FUNCTION(execServerSetFacing); \
	DECLARE_FUNCTION(execResetEncounterTracker); \
	DECLARE_FUNCTION(execAdjustCameraZoom); \
	DECLARE_FUNCTION(execRefreshTamerStyleFromProfile); \
	DECLARE_FUNCTION(execSnapFollowerToTamer); \
	DECLARE_FUNCTION(execRefreshFollowerFromProfile);


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTTamerCharacter_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTTamerCharacter_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTTamerCharacter, APaperCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTTamerCharacter) \
	DECLARE_SERIALIZER(ADigimonVenomNXTTamerCharacter) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		Facing=NETFIELD_REP_START, \
		TamerStyleId, \
		Follower, \
		NETFIELD_REP_END=Follower	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTTamerCharacter(ADigimonVenomNXTTamerCharacter&&) = delete; \
	ADigimonVenomNXTTamerCharacter(const ADigimonVenomNXTTamerCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTTamerCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTTamerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTTamerCharacter) \
	NO_API virtual ~ADigimonVenomNXTTamerCharacter();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_16_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTTamerCharacter;

// ********** End Class ADigimonVenomNXTTamerCharacter *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
