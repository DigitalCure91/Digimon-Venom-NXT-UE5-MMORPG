// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTAudioSubsystem.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAudioSubsystem_generated_h
#error "DigimonVenomNXTAudioSubsystem.generated.h already included, missing '#pragma once' in DigimonVenomNXTAudioSubsystem.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAudioSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class USoundBase;
enum class EDigimonAudioCue : uint8;

// ********** Begin ScriptStruct FDigimonEffectVoice ***********************************************
struct Z_Construct_UScriptStruct_FDigimonEffectVoice_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonEffectVoice(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_24_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonEffectVoice_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonEffectVoice(ETypeConstructPhase::Inner); }


struct FDigimonEffectVoice;
// ********** End ScriptStruct FDigimonEffectVoice *************************************************

// ********** Begin ScriptStruct FDigimonMusicVoice ************************************************
struct Z_Construct_UScriptStruct_FDigimonMusicVoice_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonMusicVoice(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_34_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonMusicVoice_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonMusicVoice(ETypeConstructPhase::Inner); }


struct FDigimonMusicVoice;
// ********** End ScriptStruct FDigimonMusicVoice **************************************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem *******************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetCurrentMusic); \
	DECLARE_FUNCTION(execStopMusic); \
	DECLARE_FUNCTION(execPlayMusic); \
	DECLARE_FUNCTION(execClearBattleMusicState); \
	DECLARE_FUNCTION(execSetBattleMusicState); \
	DECLARE_FUNCTION(execClearUIScreenMusic); \
	DECLARE_FUNCTION(execSetUIScreenMusic); \
	DECLARE_FUNCTION(execPlayMainMenuMusic); \
	DECLARE_FUNCTION(execPlayBattleForMap); \
	DECLARE_FUNCTION(execSetDigiFarmActive); \
	DECLARE_FUNCTION(execPlayExplorationForMap); \
	DECLARE_FUNCTION(execGetUIVolume); \
	DECLARE_FUNCTION(execGetEffectsVolume); \
	DECLARE_FUNCTION(execGetMusicVolume); \
	DECLARE_FUNCTION(execGetMasterVolume); \
	DECLARE_FUNCTION(execSetAudioVolumes); \
	DECLARE_FUNCTION(execPlayCueOnce); \
	DECLARE_FUNCTION(execPlayCue);


struct Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTAudioSubsystem, ULocalPlayerSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem) \
	DECLARE_SERIALIZER(UDigimonVenomNXTAudioSubsystem)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTAudioSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTAudioSubsystem(UDigimonVenomNXTAudioSubsystem&&) = delete; \
	UDigimonVenomNXTAudioSubsystem(const UDigimonVenomNXTAudioSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTAudioSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTAudioSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTAudioSubsystem) \
	NO_API virtual ~UDigimonVenomNXTAudioSubsystem();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_49_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h_52_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTAudioSubsystem;

// ********** End Class UDigimonVenomNXTAudioSubsystem *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h

// ********** Begin Enum EDigimonAudioCue **********************************************************
#define FOREACH_ENUM_EDIGIMONAUDIOCUE(op) \
	op(EDigimonAudioCue::UIHover) \
	op(EDigimonAudioCue::UIClick) \
	op(EDigimonAudioCue::UIBack) \
	op(EDigimonAudioCue::UINavigate) \
	op(EDigimonAudioCue::Confirm) \
	op(EDigimonAudioCue::Error) \
	op(EDigimonAudioCue::Heal) \
	op(EDigimonAudioCue::Item) \
	op(EDigimonAudioCue::Purchase) \
	op(EDigimonAudioCue::PhysicalAttack) \
	op(EDigimonAudioCue::SpecialAttack) \
	op(EDigimonAudioCue::Hit) \
	op(EDigimonAudioCue::Guard) \
	op(EDigimonAudioCue::Knockout) \
	op(EDigimonAudioCue::Victory) \
	op(EDigimonAudioCue::Defeat) \
	op(EDigimonAudioCue::Flee) \
	op(EDigimonAudioCue::Travel) \
	op(EDigimonAudioCue::Interaction) \
	op(EDigimonAudioCue::Encounter) \
	op(EDigimonAudioCue::EffectiveHit) 

enum class EDigimonAudioCue : uint8;
template<> struct TIsUEnumClass<EDigimonAudioCue> { enum { Value = true }; };
template<> UE_NODEBUG DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonAudioCue>();
// ********** End Enum EDigimonAudioCue ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
