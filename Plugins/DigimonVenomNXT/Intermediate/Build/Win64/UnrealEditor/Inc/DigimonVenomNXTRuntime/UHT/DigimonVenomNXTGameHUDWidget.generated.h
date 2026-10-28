// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTGameHUDWidget.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTGameHUDWidget_generated_h
#error "DigimonVenomNXTGameHUDWidget.generated.h already included, missing '#pragma once' in DigimonVenomNXTGameHUDWidget.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTGameHUDWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDigimonAIRivalActivityPage;
struct FDigimonChatMessage;
struct FDigimonRelayProgress;
struct FDigimonSeasonArchivePage;

// ********** Begin Class UDigimonVenomNXTGameHUDWidget ********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCommitAudioVolumes); \
	DECLARE_FUNCTION(execHandleUIVolume); \
	DECLARE_FUNCTION(execHandleEffectsVolume); \
	DECLARE_FUNCTION(execHandleMusicVolume); \
	DECLARE_FUNCTION(execHandleMasterVolume); \
	DECLARE_FUNCTION(execHandleProfileChanged); \
	DECLARE_FUNCTION(execHandleAction); \
	DECLARE_FUNCTION(execIsCompactHUDVisible); \
	DECLARE_FUNCTION(execSetCompactHUDVisible); \
	DECLARE_FUNCTION(execIsMenuOpen); \
	DECLARE_FUNCTION(execOpenDigiLab); \
	DECLARE_FUNCTION(execToggleMenu); \
	DECLARE_FUNCTION(execSetMenuOpen); \
	DECLARE_FUNCTION(execIsRelayDialogueOpen); \
	DECLARE_FUNCTION(execCloseRelayDialogue); \
	DECLARE_FUNCTION(execShowRelayDialogue); \
	DECLARE_FUNCTION(execApplySeasonArchivePage); \
	DECLARE_FUNCTION(execRefreshLivePages); \
	DECLARE_FUNCTION(execApplyRivalActivityPage); \
	DECLARE_FUNCTION(execAppendChat); \
	DECLARE_FUNCTION(execShowToast); \
	DECLARE_FUNCTION(execShowPage);


struct Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTGameHUDWidget, UCommonActivatableWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget) \
	DECLARE_SERIALIZER(UDigimonVenomNXTGameHUDWidget)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTGameHUDWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTGameHUDWidget(UDigimonVenomNXTGameHUDWidget&&) = delete; \
	UDigimonVenomNXTGameHUDWidget(const UDigimonVenomNXTGameHUDWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTGameHUDWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTGameHUDWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTGameHUDWidget) \
	NO_API virtual ~UDigimonVenomNXTGameHUDWidget();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_41_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h_44_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTGameHUDWidget;

// ********** End Class UDigimonVenomNXTGameHUDWidget **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
