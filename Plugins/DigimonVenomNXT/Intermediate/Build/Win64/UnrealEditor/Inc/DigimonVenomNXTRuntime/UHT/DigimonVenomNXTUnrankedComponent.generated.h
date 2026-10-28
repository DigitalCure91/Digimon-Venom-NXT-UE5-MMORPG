// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTUnrankedComponent.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTUnrankedComponent_generated_h
#error "DigimonVenomNXTUnrankedComponent.generated.h already included, missing '#pragma once' in DigimonVenomNXTUnrankedComponent.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTUnrankedComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGuid;

// ********** Begin ScriptStruct FDigimonUnrankedChallenge *****************************************
struct Z_Construct_UScriptStruct_FDigimonUnrankedChallenge_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedChallenge(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_12_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonUnrankedChallenge_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonUnrankedChallenge(ETypeConstructPhase::Inner); }


struct FDigimonUnrankedChallenge;
// ********** End ScriptStruct FDigimonUnrankedChallenge *******************************************

// ********** Begin ScriptStruct FDigimonUnrankedTarget ********************************************
struct Z_Construct_UScriptStruct_FDigimonUnrankedTarget_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedTarget(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_23_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonUnrankedTarget_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonUnrankedTarget(ETypeConstructPhase::Inner); }


struct FDigimonUnrankedTarget;
// ********** End ScriptStruct FDigimonUnrankedTarget **********************************************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent ****************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerForfeit_Implementation(); \
	virtual void ServerChallengeRival_Implementation(const FString& RivalId); \
	virtual void ServerCancel_Implementation(FGuid ChallengeId); \
	virtual void ServerRespond_Implementation(FGuid ChallengeId, bool bAccept); \
	virtual void ServerChallengePlayer_Implementation(const FString& AccountId); \
	virtual void ServerRefresh_Implementation(); \
	DECLARE_FUNCTION(execOnRep_State); \
	DECLARE_FUNCTION(execServerForfeit); \
	DECLARE_FUNCTION(execServerChallengeRival); \
	DECLARE_FUNCTION(execServerCancel); \
	DECLARE_FUNCTION(execServerRespond); \
	DECLARE_FUNCTION(execServerChallengePlayer); \
	DECLARE_FUNCTION(execServerRefresh);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTUnrankedComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent) \
	DECLARE_SERIALIZER(UDigimonVenomNXTUnrankedComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		IncomingChallenge=NETFIELD_REP_START, \
		OutgoingChallenge, \
		NearbyPlayers, \
		NearbyRivals, \
		StatusMessage, \
		NETFIELD_REP_END=StatusMessage	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTUnrankedComponent(UDigimonVenomNXTUnrankedComponent&&) = delete; \
	UDigimonVenomNXTUnrankedComponent(const UDigimonVenomNXTUnrankedComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTUnrankedComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTUnrankedComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDigimonVenomNXTUnrankedComponent) \
	NO_API virtual ~UDigimonVenomNXTUnrankedComponent();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_33_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h_36_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTUnrankedComponent;

// ********** End Class UDigimonVenomNXTUnrankedComponent ******************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
