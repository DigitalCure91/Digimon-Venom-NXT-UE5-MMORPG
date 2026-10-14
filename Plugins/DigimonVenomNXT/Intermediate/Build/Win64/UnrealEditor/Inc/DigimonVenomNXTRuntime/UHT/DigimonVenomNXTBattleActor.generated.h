// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTBattleActor.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTBattleActor_generated_h
#error "DigimonVenomNXTBattleActor.generated.h already included, missing '#pragma once' in DigimonVenomNXTBattleActor.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTBattleActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AController;
class ADigimonVenomNXTPlayerState;
enum class EDigimonBattleKind : uint8;
enum class EDigimonVariant : uint8;
struct FDigimonBattleCommand;
struct FDigimonBattleState;
struct FDigimonBattleTeam;
struct FDigimonBattleUnit;
struct FDigimonMoveSlot;
struct FDigimonWildEncounterEntry;

// ********** Begin ScriptStruct FDigimonWildEncounterEntry ****************************************
struct Z_Construct_UScriptStruct_FDigimonWildEncounterEntry_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonWildEncounterEntry(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_16_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonWildEncounterEntry_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonWildEncounterEntry(ETypeConstructPhase::Inner); }


struct FDigimonWildEncounterEntry;
// ********** End ScriptStruct FDigimonWildEncounterEntry ******************************************

// ********** Begin ScriptStruct FDigimonSeasonBattleCheckpoint ************************************
struct Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_26_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint(ETypeConstructPhase::Inner); }


struct FDigimonSeasonBattleCheckpoint;
// ********** End ScriptStruct FDigimonSeasonBattleCheckpoint **************************************

// ********** Begin Class ADigimonVenomNXTBattleActor **********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void MulticastPresentState_Implementation(FDigimonBattleState const& Packet); \
	DECLARE_FUNCTION(execMulticastPresentState); \
	DECLARE_FUNCTION(execOnRep_State); \
	DECLARE_FUNCTION(execComputeMoveDamage); \
	DECLARE_FUNCTION(execComputeDamage); \
	DECLARE_FUNCTION(execIsParticipant); \
	DECLARE_FUNCTION(execSubmitCommand); \
	DECLARE_FUNCTION(execInitializeAITrainerBattle); \
	DECLARE_FUNCTION(execInitializeTamerBattle); \
	DECLARE_FUNCTION(execInitializeWildGroupBattle); \
	DECLARE_FUNCTION(execInitializeWildBattle);


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTBattleActor_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTBattleActor_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTBattleActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTBattleActor) \
	DECLARE_SERIALIZER(ADigimonVenomNXTBattleActor) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		UnrankedDecisionDeadlineServerTime=NETFIELD_REP_START, \
		bUnrankedResultSaving, \
		PlayerA, \
		PlayerB, \
		BattleContextId, \
		ReplicatedSnapshot, \
		NETFIELD_REP_END=ReplicatedSnapshot	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTBattleActor(ADigimonVenomNXTBattleActor&&) = delete; \
	ADigimonVenomNXTBattleActor(const ADigimonVenomNXTBattleActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTBattleActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTBattleActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTBattleActor) \
	NO_API virtual ~ADigimonVenomNXTBattleActor();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_36_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTBattleActor;

// ********** End Class ADigimonVenomNXTBattleActor ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
