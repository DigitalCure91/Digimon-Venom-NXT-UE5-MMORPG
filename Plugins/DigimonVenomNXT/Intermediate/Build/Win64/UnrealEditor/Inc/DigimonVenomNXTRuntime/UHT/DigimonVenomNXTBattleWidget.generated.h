// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTBattleWidget.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTBattleWidget_generated_h
#error "DigimonVenomNXTBattleWidget.generated.h already included, missing '#pragma once' in DigimonVenomNXTBattleWidget.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTBattleWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ADigimonVenomNXTBattleActor;
struct FDigimonBattleState;

// ********** Begin ScriptStruct FDigimonBattleSlotVisual ******************************************
struct Z_Construct_UScriptStruct_FDigimonBattleSlotVisual_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleSlotVisual(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_26_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonBattleSlotVisual_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonBattleSlotVisual(ETypeConstructPhase::Inner); }


struct FDigimonBattleSlotVisual;
// ********** End ScriptStruct FDigimonBattleSlotVisual ********************************************

// ********** Begin Class UDigimonVenomNXTBattleWidget *********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleAction); \
	DECLARE_FUNCTION(execHandleBattleStateChanged); \
	DECLARE_FUNCTION(execIsPresentationBusy); \
	DECLARE_FUNCTION(execGetBattle); \
	DECLARE_FUNCTION(execSetBattle);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UDigimonVenomNXTBattleWidget_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTBattleWidget_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTBattleWidget, UCommonActivatableWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTBattleWidget) \
	DECLARE_SERIALIZER(UDigimonVenomNXTBattleWidget)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTBattleWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTBattleWidget(UDigimonVenomNXTBattleWidget&&) = delete; \
	UDigimonVenomNXTBattleWidget(const UDigimonVenomNXTBattleWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTBattleWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTBattleWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTBattleWidget) \
	NO_API virtual ~UDigimonVenomNXTBattleWidget();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_44_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h_47_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTBattleWidget;

// ********** End Class UDigimonVenomNXTBattleWidget ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
