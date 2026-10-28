// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTEditorLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTEditorLibrary() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTEditor(ETypeConstructPhase);
DIGIMONVENOMNXTEDITOR_API UClass* Z_Construct_UClass_UDigimonVenomNXTEditorLibrary(ETypeConstructPhase);
DIGIMONVENOMNXTEDITOR_API UClass* Z_Construct_UClass_UDigimonVenomNXTEditorLibrary(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function BuildCompleteGameContent **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildCompleteGameContent_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import all content, build worlds, configure the project and save a verified packaging receipt. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import all content, build worlds, configure the project and save a verified packaging receipt." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BuildCompleteGameContent constinit property declarations **************
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BuildCompleteGameContent constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BuildCompleteGameContent Property Definitions *************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BuildCompleteGameContent Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "BuildCompleteGameContent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventBuildCompleteGameContent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildCompleteGameContent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execBuildCompleteGameContent)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::BuildCompleteGameContent(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function BuildCompleteGameContent ************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function BuildStarterLevels ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildStarterLevels_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms
	{
		bool bOverwriteExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Create MainMenu and PublicWorld without switching the open editor level. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create MainMenu and PublicWorld without switching the open editor level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BuildStarterLevels constinit property declarations ********************
	static void NewProp_bOverwriteExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms*)Obj)->bOverwriteExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverwriteExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BuildStarterLevels constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BuildStarterLevels Property Definitions *******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOverwriteExisting = { "bOverwriteExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms), &UHT_STATICS::NewProp_bOverwriteExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOverwriteExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BuildStarterLevels Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "BuildStarterLevels", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventBuildStarterLevels_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildStarterLevels(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execBuildStarterLevels)
{
	P_GET_UBOOL(Z_Param_bOverwriteExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::BuildStarterLevels(Z_Param_bOverwriteExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function BuildStarterLevels ******************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ConfigureLevelCustomDepth *********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureLevelCustomDepth_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable Custom Depth with Stencil and configure rendered level components. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable Custom Depth with Stencil and configure rendered level components." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ConfigureLevelCustomDepth constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConfigureLevelCustomDepth constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConfigureLevelCustomDepth Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ConfigureLevelCustomDepth Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ConfigureLevelCustomDepth", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventConfigureLevelCustomDepth_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureLevelCustomDepth(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execConfigureLevelCustomDepth)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ConfigureLevelCustomDepth(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ConfigureLevelCustomDepth ***********

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ConfigureProjectForDigimonVenomNXT 
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureProjectForDigimonVenomNXT_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Save native project startup and render configuration. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Save native project startup and render configuration." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ConfigureProjectForDigimonVenomNXT constinit property declarations ****
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConfigureProjectForDigimonVenomNXT constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConfigureProjectForDigimonVenomNXT Property Definitions ***************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ConfigureProjectForDigimonVenomNXT Property Definitions *****************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ConfigureProjectForDigimonVenomNXT", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventConfigureProjectForDigimonVenomNXT_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureProjectForDigimonVenomNXT(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execConfigureProjectForDigimonVenomNXT)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ConfigureProjectForDigimonVenomNXT(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ConfigureProjectForDigimonVenomNXT **

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportAllBundledAssets ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportAllBundledAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Complete setup, including MainMenu/PublicWorld and startup configuration. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complete setup, including MainMenu/PublicWorld and startup configuration." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportAllBundledAssets constinit property declarations ****************
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportAllBundledAssets constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportAllBundledAssets Property Definitions ***************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportAllBundledAssets Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportAllBundledAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportAllBundledAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportAllBundledAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportAllBundledAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportAllBundledAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportAllBundledAssets **************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportCoreAssets ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportCoreAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Complete setup: create worlds, import content and configure startup. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complete setup: create worlds, import content and configure startup." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportCoreAssets constinit property declarations **********************
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportCoreAssets constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportCoreAssets Property Definitions *********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportCoreAssets Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportCoreAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportCoreAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportCoreAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportCoreAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportCoreAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportCoreAssets ********************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportFirewallRosterAssets ********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFirewallRosterAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import every Firewall variety with original frame dimensions and timing. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import every Firewall variety with original frame dimensions and timing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportFirewallRosterAssets constinit property declarations ************
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportFirewallRosterAssets constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportFirewallRosterAssets Property Definitions ***********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportFirewallRosterAssets Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportFirewallRosterAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportFirewallRosterAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFirewallRosterAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportFirewallRosterAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportFirewallRosterAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportFirewallRosterAssets **********

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportFullTamerRosterAssets *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFullTamerRosterAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import all supplied tamer appearances and eight-direction animations. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import all supplied tamer appearances and eight-direction animations." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportFullTamerRosterAssets constinit property declarations ***********
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportFullTamerRosterAssets constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportFullTamerRosterAssets Property Definitions **********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportFullTamerRosterAssets Property Definitions ************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportFullTamerRosterAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportFullTamerRosterAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFullTamerRosterAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportFullTamerRosterAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportFullTamerRosterAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportFullTamerRosterAssets *********

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportPlayableMapAssets ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPlayableMapAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import every registered map and save the matching collision completion marker. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import every registered map and save the matching collision completion marker." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportPlayableMapAssets constinit property declarations ***************
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportPlayableMapAssets constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportPlayableMapAssets Property Definitions **************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportPlayableMapAssets Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportPlayableMapAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportPlayableMapAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPlayableMapAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportPlayableMapAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportPlayableMapAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportPlayableMapAssets *************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ImportPresentationPolishAssets ****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPresentationPolishAssets_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms
	{
		bool bReplaceExisting;
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import all source Digimon interface imagery, effects and background music. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import all source Digimon interface imagery, effects and background music." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ImportPresentationPolishAssets constinit property declarations ********
	static void NewProp_bReplaceExisting_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms*)Obj)->bReplaceExisting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplaceExisting;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ImportPresentationPolishAssets constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ImportPresentationPolishAssets Property Definitions *******************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReplaceExisting = { "bReplaceExisting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms), &UHT_STATICS::NewProp_bReplaceExisting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReplaceExisting,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ImportPresentationPolishAssets Property Definitions *********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ImportPresentationPolishAssets", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventImportPresentationPolishAssets_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPresentationPolishAssets(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execImportPresentationPolishAssets)
{
	P_GET_UBOOL(Z_Param_bReplaceExisting);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ImportPresentationPolishAssets(Z_Param_bReplaceExisting,Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ImportPresentationPolishAssets ******

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function PrepareGameWorlds *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PrepareGameWorlds_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Create or repair both worlds and startup settings without waiting for artwork import. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create or repair both worlds and startup settings without waiting for artwork import." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function PrepareGameWorlds constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PrepareGameWorlds constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PrepareGameWorlds Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PrepareGameWorlds Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "PrepareGameWorlds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventPrepareGameWorlds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PrepareGameWorlds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execPrepareGameWorlds)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::PrepareGameWorlds(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function PrepareGameWorlds *******************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function PreparePrivateDigiFarm ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PreparePrivateDigiFarm_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Prepare the source private farm island and farm presentation. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Prepare the source private farm island and farm presentation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function PreparePrivateDigiFarm constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PreparePrivateDigiFarm constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PreparePrivateDigiFarm Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PreparePrivateDigiFarm Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "PreparePrivateDigiFarm", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventPreparePrivateDigiFarm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PreparePrivateDigiFarm(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execPreparePrivateDigiFarm)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::PreparePrivateDigiFarm(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function PreparePrivateDigiFarm **************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function RepairBackgroundMusic *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairBackgroundMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import missing source background music and repair looping playback. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import missing source background music and repair looping playback." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RepairBackgroundMusic constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RepairBackgroundMusic constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RepairBackgroundMusic Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RepairBackgroundMusic Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "RepairBackgroundMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairBackgroundMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairBackgroundMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execRepairBackgroundMusic)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::RepairBackgroundMusic(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function RepairBackgroundMusic ***************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function RepairFieldSpriteRendering ********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairFieldSpriteRendering_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Repair every Digimon sprite, flipbook and animation set in place. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Repair every Digimon sprite, flipbook and animation set in place." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RepairFieldSpriteRendering constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RepairFieldSpriteRendering constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RepairFieldSpriteRendering Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RepairFieldSpriteRendering Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "RepairFieldSpriteRendering", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairFieldSpriteRendering_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairFieldSpriteRendering(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execRepairFieldSpriteRendering)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::RepairFieldSpriteRendering(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function RepairFieldSpriteRendering **********

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function RepairPackagedStartup *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairPackagedStartup_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Repair missing worlds, zone metadata, startup, travel and cooking. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Repair missing worlds, zone metadata, startup, travel and cooking." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RepairPackagedStartup constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RepairPackagedStartup constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RepairPackagedStartup Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RepairPackagedStartup Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "RepairPackagedStartup", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairPackagedStartup_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairPackagedStartup(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execRepairPackagedStartup)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::RepairPackagedStartup(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function RepairPackagedStartup ***************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function RepairSoundEffects ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairSoundEffects_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Import missing source sound effects and repair non-looping playback. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Import missing source sound effects and repair non-looping playback." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RepairSoundEffects constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RepairSoundEffects constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RepairSoundEffects Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RepairSoundEffects Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "RepairSoundEffects", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventRepairSoundEffects_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairSoundEffects(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execRepairSoundEffects)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::RepairSoundEffects(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function RepairSoundEffects ******************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ValidateBundledContent ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateBundledContent_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Read-only verification of the complete source manifest and every dependency. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Read-only verification of the complete source manifest and every dependency." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ValidateBundledContent constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ValidateBundledContent constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ValidateBundledContent Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ValidateBundledContent Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ValidateBundledContent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventValidateBundledContent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateBundledContent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execValidateBundledContent)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ValidateBundledContent(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ValidateBundledContent **************

// ********** Begin Class UDigimonVenomNXTEditorLibrary Function ValidateGameWorlds ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateGameWorlds_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms
	{
		FString OutReport;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Editor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Read-only validation of saved worlds, native modes, map identities, start and imported map revision. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Read-only validation of saved worlds, native modes, map identities, start and imported map revision." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ValidateGameWorlds constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutReport;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ValidateGameWorlds constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ValidateGameWorlds Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutReport = { "OutReport", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms, OutReport), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutReport,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ValidateGameWorlds Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, nullptr, "ValidateGameWorlds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEditorLibrary_eventValidateGameWorlds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateGameWorlds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEditorLibrary::execValidateGameWorlds)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutReport);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UDigimonVenomNXTEditorLibrary::ValidateGameWorlds(Z_Param_Out_OutReport);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEditorLibrary Function ValidateGameWorlds ******************

// ********** Begin Class UDigimonVenomNXTEditorLibrary ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTEditorLibrary_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native Digimon setup. Worlds are prepared first; authored assets require verified source checksums. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTEditorLibrary.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEditorLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native Digimon setup. Worlds are prepared first; authored assets require verified source checksums." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTEditorLibrary constinit property declarations ************
// ********** End Class UDigimonVenomNXTEditorLibrary constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BuildCompleteGameContent"), .Pointer = &UDigimonVenomNXTEditorLibrary::execBuildCompleteGameContent },
		{ .NameUTF8 = UTF8TEXT("BuildStarterLevels"), .Pointer = &UDigimonVenomNXTEditorLibrary::execBuildStarterLevels },
		{ .NameUTF8 = UTF8TEXT("ConfigureLevelCustomDepth"), .Pointer = &UDigimonVenomNXTEditorLibrary::execConfigureLevelCustomDepth },
		{ .NameUTF8 = UTF8TEXT("ConfigureProjectForDigimonVenomNXT"), .Pointer = &UDigimonVenomNXTEditorLibrary::execConfigureProjectForDigimonVenomNXT },
		{ .NameUTF8 = UTF8TEXT("ImportAllBundledAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportAllBundledAssets },
		{ .NameUTF8 = UTF8TEXT("ImportCoreAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportCoreAssets },
		{ .NameUTF8 = UTF8TEXT("ImportFirewallRosterAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportFirewallRosterAssets },
		{ .NameUTF8 = UTF8TEXT("ImportFullTamerRosterAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportFullTamerRosterAssets },
		{ .NameUTF8 = UTF8TEXT("ImportPlayableMapAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportPlayableMapAssets },
		{ .NameUTF8 = UTF8TEXT("ImportPresentationPolishAssets"), .Pointer = &UDigimonVenomNXTEditorLibrary::execImportPresentationPolishAssets },
		{ .NameUTF8 = UTF8TEXT("PrepareGameWorlds"), .Pointer = &UDigimonVenomNXTEditorLibrary::execPrepareGameWorlds },
		{ .NameUTF8 = UTF8TEXT("PreparePrivateDigiFarm"), .Pointer = &UDigimonVenomNXTEditorLibrary::execPreparePrivateDigiFarm },
		{ .NameUTF8 = UTF8TEXT("RepairBackgroundMusic"), .Pointer = &UDigimonVenomNXTEditorLibrary::execRepairBackgroundMusic },
		{ .NameUTF8 = UTF8TEXT("RepairFieldSpriteRendering"), .Pointer = &UDigimonVenomNXTEditorLibrary::execRepairFieldSpriteRendering },
		{ .NameUTF8 = UTF8TEXT("RepairPackagedStartup"), .Pointer = &UDigimonVenomNXTEditorLibrary::execRepairPackagedStartup },
		{ .NameUTF8 = UTF8TEXT("RepairSoundEffects"), .Pointer = &UDigimonVenomNXTEditorLibrary::execRepairSoundEffects },
		{ .NameUTF8 = UTF8TEXT("ValidateBundledContent"), .Pointer = &UDigimonVenomNXTEditorLibrary::execValidateBundledContent },
		{ .NameUTF8 = UTF8TEXT("ValidateGameWorlds"), .Pointer = &UDigimonVenomNXTEditorLibrary::execValidateGameWorlds },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildCompleteGameContent, "BuildCompleteGameContent" }, // 3dce6451a99748de815e6918edee83bc6b5180f3
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_BuildStarterLevels, "BuildStarterLevels" }, // 3de3b7864f2bbeb937718cd73010ac89fdc3811c
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureLevelCustomDepth, "ConfigureLevelCustomDepth" }, // 795396c1b8c9e3d918cbe3789f1312f6f9cc67af
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ConfigureProjectForDigimonVenomNXT, "ConfigureProjectForDigimonVenomNXT" }, // aaacbf758cc62b3ac93587fd32024686808a8f51
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportAllBundledAssets, "ImportAllBundledAssets" }, // c52308556d2268b649bc9463f29dc22a5aeb6871
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportCoreAssets, "ImportCoreAssets" }, // a4d499b3e9d2c1eb53f18227e5e2b61ebb1158b1
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFirewallRosterAssets, "ImportFirewallRosterAssets" }, // cb60a029b22ce99c08ec199a57840f7c2674ba2d
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportFullTamerRosterAssets, "ImportFullTamerRosterAssets" }, // 08933bf49ad58727ecd22b4d2a23c46cf86bc5f9
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPlayableMapAssets, "ImportPlayableMapAssets" }, // db809ddb3a5ee4ce1aef40bb0e652fe322645575
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ImportPresentationPolishAssets, "ImportPresentationPolishAssets" }, // 9062c479ab3cb05e9009507f01c03ca2b4686fcf
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PrepareGameWorlds, "PrepareGameWorlds" }, // 775eca01a63adcb15a677773dea31c820a431692
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_PreparePrivateDigiFarm, "PreparePrivateDigiFarm" }, // f6c82f3015b9dc6b903aa5b54b5cb7998dcd26d5
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairBackgroundMusic, "RepairBackgroundMusic" }, // 41ba488ebbc22ed2f331a3e15db36c6dbd94b0cd
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairFieldSpriteRendering, "RepairFieldSpriteRendering" }, // cc9e14583dca706bb15d4c7b840f4ad6061f1e64
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairPackagedStartup, "RepairPackagedStartup" }, // bd289539c5d7ec150cba061b7a6ca88485e62b33
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_RepairSoundEffects, "RepairSoundEffects" }, // a11b1b910466dbb89ac88bd876ab4fff5c249059
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateBundledContent, "ValidateBundledContent" }, // 9cc11f6d9a6f13c9e9adc7cd1b99016834b1d350
		{ &Z_Construct_UFunction_UDigimonVenomNXTEditorLibrary_ValidateGameWorlds, "ValidateGameWorlds" }, // 5beacbe8d7784c60400d1021172fc65a08259d7d
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTEditorLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UBlueprintFunctionLibrary,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTEditor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTEditorLibrary,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTEditorLibrary_StaticRegisterNativesUDigimonVenomNXTEditorLibrary()
{
	UClass* Class = UDigimonVenomNXTEditorLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary;
UClass* Z_Construct_UClass_UDigimonVenomNXTEditorLibrary(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTEditorLibrary;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTEditorLibrary"),
				Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.InnerSingleton,
				UDigimonVenomNXTEditorLibrary_StaticRegisterNativesUDigimonVenomNXTEditorLibrary,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTEditorLibrary::UDigimonVenomNXTEditorLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTEditorLibrary);
UDigimonVenomNXTEditorLibrary::~UDigimonVenomNXTEditorLibrary() {}
// ********** End Class UDigimonVenomNXTEditorLibrary **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTEditor_Public_DigimonVenomNXTEditorLibrary_h__Script_DigimonVenomNXTEditor_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTEditorLibrary, TEXT("UDigimonVenomNXTEditorLibrary"), &Z_Registration_Info_UClass_UDigimonVenomNXTEditorLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTEditorLibrary), 1235814286U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTEditor_Public_DigimonVenomNXTEditorLibrary_h__Script_DigimonVenomNXTEditor_06e4a6d934304ac0eba48480a73f52799a2217c3{
	TEXT("/Script/DigimonVenomNXTEditor"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
