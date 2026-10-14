// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTVideoSettingsSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTVideoSettingsSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonVideoSettings(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EDigimonDisplayMode *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode_Statics
template<> DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonDisplayMode>()
{
	return Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Borderless.Name", "EDigimonDisplayMode::Borderless" },
		{ "Fullscreen.Name", "EDigimonDisplayMode::Fullscreen" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
		{ "Windowed.Name", "EDigimonDisplayMode::Windowed" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDigimonDisplayMode::Fullscreen", (int64)EDigimonDisplayMode::Fullscreen },
		{ "EDigimonDisplayMode::Borderless", (int64)EDigimonDisplayMode::Borderless },
		{ "EDigimonDisplayMode::Windowed", (int64)EDigimonDisplayMode::Windowed },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	"EDigimonDisplayMode",
	"EDigimonDisplayMode",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EDigimonDisplayMode;
UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EDigimonDisplayMode.OuterSingleton)
		{
			ZRIE_EDigimonDisplayMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("EDigimonDisplayMode"));
		}
		return ZRIE_EDigimonDisplayMode.OuterSingleton;
	}
	if (!ZRIE_EDigimonDisplayMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EDigimonDisplayMode.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EDigimonDisplayMode.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EDigimonDisplayMode *********************************************************

// ********** Begin Enum EDigimonVideoPreset *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset_Statics
template<> DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonVideoPreset>()
{
	return Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Balanced.Name", "EDigimonVideoPreset::Balanced" },
		{ "BlueprintType", "true" },
		{ "Epic.Name", "EDigimonVideoPreset::Epic" },
		{ "High.Name", "EDigimonVideoPreset::High" },
		{ "Low.Name", "EDigimonVideoPreset::Low" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
		{ "Optimized.Name", "EDigimonVideoPreset::Optimized" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDigimonVideoPreset::Optimized", (int64)EDigimonVideoPreset::Optimized },
		{ "EDigimonVideoPreset::Low", (int64)EDigimonVideoPreset::Low },
		{ "EDigimonVideoPreset::Balanced", (int64)EDigimonVideoPreset::Balanced },
		{ "EDigimonVideoPreset::High", (int64)EDigimonVideoPreset::High },
		{ "EDigimonVideoPreset::Epic", (int64)EDigimonVideoPreset::Epic },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	"EDigimonVideoPreset",
	"EDigimonVideoPreset",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EDigimonVideoPreset;
UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EDigimonVideoPreset.OuterSingleton)
		{
			ZRIE_EDigimonVideoPreset.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("EDigimonVideoPreset"));
		}
		return ZRIE_EDigimonVideoPreset.OuterSingleton;
	}
	if (!ZRIE_EDigimonVideoPreset.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EDigimonVideoPreset.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EDigimonVideoPreset.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EDigimonVideoPreset *********************************************************

// ********** Begin ScriptStruct FDigimonVideoSettings *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonVideoSettings_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonVideoSettings>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonVideoSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Device-local settings. Not part of a tamer profile, replicated state or account save. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Device-local settings. Not part of a tamer profile, replicated state or account save." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Resolution_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayMode_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResolutionScale_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameRateLimit_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gamma_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bVSync_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDynamicResolution_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHDR_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HDRNits_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ViewDistanceQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AntiAliasingQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShadowQuality_MetaData[] = {
		{ "Category", "Video" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Zero explicitly disables dynamic/contact shadows; 1..4 are medium..cinematic. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zero explicitly disables dynamic/contact shadows; 1..4 are medium..cinematic." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GlobalIlluminationQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReflectionQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PostProcessQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextureQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EffectsQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FoliageQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShadingQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LandscapeQuality_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AntiAliasingMethod_MetaData[] = {
		{ "Category", "Video" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Engine enum values: 0 off, 1 FXAA, 2 TAA, 3 MSAA (forward only), 4 TSR. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Engine enum values: 0 off, 1 FXAA, 2 TAA, 3 MSAA (forward only), 4 TSR." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMotionBlur_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDepthOfField_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBloom_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLensFlare_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bChromaticAberration_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAmbientOcclusion_MetaData[] = {
		{ "Category", "Video" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonVideoSettings constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Resolution;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DisplayMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DisplayMode;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ResolutionScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FrameRateLimit;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Gamma;
	static void NewProp_bVSync_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bVSync = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVSync;
	static void NewProp_bDynamicResolution_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bDynamicResolution = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDynamicResolution;
	static void NewProp_bHDR_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bHDR = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHDR;
	static const UECodeGen_Private::FIntPropertyParams NewProp_HDRNits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ViewDistanceQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AntiAliasingQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ShadowQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_GlobalIlluminationQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReflectionQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PostProcessQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TextureQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EffectsQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FoliageQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ShadingQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LandscapeQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AntiAliasingMethod;
	static void NewProp_bMotionBlur_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bMotionBlur = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMotionBlur;
	static void NewProp_bDepthOfField_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bDepthOfField = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDepthOfField;
	static void NewProp_bBloom_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bBloom = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBloom;
	static void NewProp_bLensFlare_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bLensFlare = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLensFlare;
	static void NewProp_bChromaticAberration_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bChromaticAberration = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bChromaticAberration;
	static void NewProp_bAmbientOcclusion_SetBit(void* Obj)
	{
		((FDigimonVideoSettings*)Obj)->bAmbientOcclusion = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAmbientOcclusion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonVideoSettings constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonVideoSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonVideoSettings Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Resolution = { "Resolution", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, Resolution), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Resolution_MetaData), NewProp_Resolution_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_DisplayMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_DisplayMode = { "DisplayMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, DisplayMode), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayMode_MetaData), NewProp_DisplayMode_MetaData) }; // 75507ad127a13cf77594f90c3cba778a057083a9
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ResolutionScale = { "ResolutionScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, ResolutionScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResolutionScale_MetaData), NewProp_ResolutionScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FrameRateLimit = { "FrameRateLimit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, FrameRateLimit), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameRateLimit_MetaData), NewProp_FrameRateLimit_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Gamma = { "Gamma", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, Gamma), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gamma_MetaData), NewProp_Gamma_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bVSync = { "bVSync", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bVSync_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bVSync_MetaData), NewProp_bVSync_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bDynamicResolution = { "bDynamicResolution", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bDynamicResolution_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDynamicResolution_MetaData), NewProp_bDynamicResolution_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bHDR = { "bHDR", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bHDR_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHDR_MetaData), NewProp_bHDR_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_HDRNits = { "HDRNits", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, HDRNits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HDRNits_MetaData), NewProp_HDRNits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ViewDistanceQuality = { "ViewDistanceQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, ViewDistanceQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ViewDistanceQuality_MetaData), NewProp_ViewDistanceQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AntiAliasingQuality = { "AntiAliasingQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, AntiAliasingQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AntiAliasingQuality_MetaData), NewProp_AntiAliasingQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ShadowQuality = { "ShadowQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, ShadowQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShadowQuality_MetaData), NewProp_ShadowQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_GlobalIlluminationQuality = { "GlobalIlluminationQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, GlobalIlluminationQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalIlluminationQuality_MetaData), NewProp_GlobalIlluminationQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReflectionQuality = { "ReflectionQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, ReflectionQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReflectionQuality_MetaData), NewProp_ReflectionQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PostProcessQuality = { "PostProcessQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, PostProcessQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PostProcessQuality_MetaData), NewProp_PostProcessQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TextureQuality = { "TextureQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, TextureQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureQuality_MetaData), NewProp_TextureQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_EffectsQuality = { "EffectsQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, EffectsQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EffectsQuality_MetaData), NewProp_EffectsQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_FoliageQuality = { "FoliageQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, FoliageQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FoliageQuality_MetaData), NewProp_FoliageQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ShadingQuality = { "ShadingQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, ShadingQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShadingQuality_MetaData), NewProp_ShadingQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_LandscapeQuality = { "LandscapeQuality", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, LandscapeQuality), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LandscapeQuality_MetaData), NewProp_LandscapeQuality_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AntiAliasingMethod = { "AntiAliasingMethod", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoSettings, AntiAliasingMethod), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AntiAliasingMethod_MetaData), NewProp_AntiAliasingMethod_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bMotionBlur = { "bMotionBlur", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bMotionBlur_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMotionBlur_MetaData), NewProp_bMotionBlur_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bDepthOfField = { "bDepthOfField", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bDepthOfField_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDepthOfField_MetaData), NewProp_bDepthOfField_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bBloom = { "bBloom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bBloom_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBloom_MetaData), NewProp_bBloom_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bLensFlare = { "bLensFlare", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bLensFlare_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLensFlare_MetaData), NewProp_bLensFlare_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bChromaticAberration = { "bChromaticAberration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bChromaticAberration_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bChromaticAberration_MetaData), NewProp_bChromaticAberration_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAmbientOcclusion = { "bAmbientOcclusion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonVideoSettings), &UHT_STATICS::NewProp_bAmbientOcclusion_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAmbientOcclusion_MetaData), NewProp_bAmbientOcclusion_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Resolution,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResolutionScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FrameRateLimit,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Gamma,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bVSync,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bDynamicResolution,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bHDR,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HDRNits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ViewDistanceQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AntiAliasingQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShadowQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GlobalIlluminationQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReflectionQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PostProcessQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TextureQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EffectsQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FoliageQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShadingQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LandscapeQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AntiAliasingMethod,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bMotionBlur,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bDepthOfField,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bBloom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bLensFlare,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bChromaticAberration,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAmbientOcclusion,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonVideoSettings Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonVideoSettings",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonVideoSettings>(),
	alignof(FDigimonVideoSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonVideoSettings;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonVideoSettings(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonVideoSettings, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonVideoSettings"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonVideoSettings.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonVideoSettings ***********************************************

// ********** Begin Class UDigimonVenomNXTVideoSettingsSubsystem ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A game-instance lifetime owns the confirmation countdown, including hidden/destroyed menus. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTVideoSettingsSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A game-instance lifetime owns the confirmation countdown, including hidden/destroyed menus." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pending_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Applied_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Confirmed_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTVideoSettingsSubsystem constinit property declarations ***
	static const UECodeGen_Private::FStructPropertyParams NewProp_Pending;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Applied;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Confirmed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTVideoSettingsSubsystem constinit property declarations *****
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTVideoSettingsSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTVideoSettingsSubsystem Property Definitions **************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Pending = { "Pending", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsSubsystem, Pending), Z_Construct_UScriptStruct_FDigimonVideoSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pending_MetaData), NewProp_Pending_MetaData) }; // 27ad4edd301be502b2f13d91de2b656ff46dde4b
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Applied = { "Applied", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsSubsystem, Applied), Z_Construct_UScriptStruct_FDigimonVideoSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Applied_MetaData), NewProp_Applied_MetaData) }; // 27ad4edd301be502b2f13d91de2b656ff46dde4b
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Confirmed = { "Confirmed", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsSubsystem, Confirmed), Z_Construct_UScriptStruct_FDigimonVideoSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Confirmed_MetaData), NewProp_Confirmed_MetaData) }; // 27ad4edd301be502b2f13d91de2b656ff46dde4b
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pending,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Applied,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Confirmed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTVideoSettingsSubsystem Property Definitions ****************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTVideoSettingsSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTVideoSettingsSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.InnerSingleton,
				nullptr,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTVideoSettingsSubsystem::UDigimonVenomNXTVideoSettingsSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTVideoSettingsSubsystem);
UDigimonVenomNXTVideoSettingsSubsystem::~UDigimonVenomNXTVideoSettingsSubsystem() {}
// ********** End Class UDigimonVenomNXTVideoSettingsSubsystem *************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonDisplayMode, TEXT("EDigimonDisplayMode"), &ZRIE_EDigimonDisplayMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1968208593U) },
		{ Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVideoPreset, TEXT("EDigimonVideoPreset"), &ZRIE_EDigimonVideoPreset, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2281703752U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonVideoSettings, Z_Construct_UScriptStruct_FDigimonVideoSettings_Statics::NewStructOps, TEXT("DigimonVideoSettings"),&Z_Registration_Info_UScriptStruct_FDigimonVideoSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonVideoSettings), 665669341U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTVideoSettingsSubsystem, TEXT("UDigimonVenomNXTVideoSettingsSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTVideoSettingsSubsystem), 996347097U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsSubsystem_h__Script_DigimonVenomNXTRuntime_810e6732a9211533a66e8d77a3b4b1996d6bffa5{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
