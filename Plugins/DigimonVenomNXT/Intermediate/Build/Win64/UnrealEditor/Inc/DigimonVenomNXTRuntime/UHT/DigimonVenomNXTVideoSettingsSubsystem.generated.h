// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTVideoSettingsSubsystem.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTVideoSettingsSubsystem_generated_h
#error "DigimonVenomNXTVideoSettingsSubsystem.generated.h already included, missing '#pragma once' in DigimonVenomNXTVideoSettingsSubsystem.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTVideoSettingsSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FDigimonVideoSettings *********************************************
struct Z_Construct_UScriptStruct_FDigimonVideoSettings_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonVideoSettings(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_19_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonVideoSettings_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonVideoSettings(ETypeConstructPhase::Inner); }


struct FDigimonVideoSettings;
// ********** End ScriptStruct FDigimonVideoSettings ***********************************************

// ********** Begin Class UDigimonVenomNXTVideoSettingsSubsystem ***********************************
struct Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_75_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTVideoSettingsSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem) \
	DECLARE_SERIALIZER(UDigimonVenomNXTVideoSettingsSubsystem)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_75_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTVideoSettingsSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTVideoSettingsSubsystem(UDigimonVenomNXTVideoSettingsSubsystem&&) = delete; \
	UDigimonVenomNXTVideoSettingsSubsystem(const UDigimonVenomNXTVideoSettingsSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTVideoSettingsSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTVideoSettingsSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTVideoSettingsSubsystem) \
	NO_API virtual ~UDigimonVenomNXTVideoSettingsSubsystem();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_72_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_75_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_75_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h_75_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTVideoSettingsSubsystem;

// ********** End Class UDigimonVenomNXTVideoSettingsSubsystem *************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h

// ********** Begin Enum EDigimonDisplayMode *******************************************************
#define FOREACH_ENUM_EDIGIMONDISPLAYMODE(op) \
	op(EDigimonDisplayMode::Fullscreen) \
	op(EDigimonDisplayMode::Borderless) \
	op(EDigimonDisplayMode::Windowed) 

enum class EDigimonDisplayMode : uint8;
template<> struct TIsUEnumClass<EDigimonDisplayMode> { enum { Value = true }; };
template<> UE_NODEBUG DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonDisplayMode>();
// ********** End Enum EDigimonDisplayMode *********************************************************

// ********** Begin Enum EDigimonVideoPreset *******************************************************
#define FOREACH_ENUM_EDIGIMONVIDEOPRESET(op) \
	op(EDigimonVideoPreset::Optimized) \
	op(EDigimonVideoPreset::Low) \
	op(EDigimonVideoPreset::Balanced) \
	op(EDigimonVideoPreset::High) \
	op(EDigimonVideoPreset::Epic) 

enum class EDigimonVideoPreset : uint8;
template<> struct TIsUEnumClass<EDigimonVideoPreset> { enum { Value = true }; };
template<> UE_NODEBUG DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonVideoPreset>();
// ********** End Enum EDigimonVideoPreset *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
