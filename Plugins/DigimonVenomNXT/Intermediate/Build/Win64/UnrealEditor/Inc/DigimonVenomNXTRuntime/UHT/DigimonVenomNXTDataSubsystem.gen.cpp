// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTDataSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonMapRow(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonMoveSlot(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonShopItemDefinition(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSpeciesDefinition(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDataSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDataSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetAllMaps ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllMaps_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetAllMaps_Parms
	{
		TArray<FDigimonMapRow> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllMaps constinit property declarations ****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllMaps constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllMaps Property Definitions ***************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonMapRow, METADATA_PARAMS(0, nullptr) }; // d3b9faab2e26607d93728ab7bbb0de16fe897b99
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetAllMaps_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // d3b9faab2e26607d93728ab7bbb0de16fe897b99
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllMaps Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetAllMaps", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetAllMaps_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetAllMaps_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllMaps(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetAllMaps)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonMapRow>*)Z_Param__Result=P_THIS->GetAllMaps();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetAllMaps **************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetAllSpecies *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllSpecies_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetAllSpecies_Parms
	{
		TArray<FDigimonSpeciesDefinition> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllSpecies constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllSpecies constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllSpecies Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSpeciesDefinition, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetAllSpecies_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllSpecies Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetAllSpecies", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetAllSpecies_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetAllSpecies_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllSpecies(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetAllSpecies)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonSpeciesDefinition>*)Z_Param__Result=P_THIS->GetAllSpecies();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetAllSpecies ***********************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetConfiguredSpeciesCapacity ******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetConfiguredSpeciesCapacity_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetConfiguredSpeciesCapacity_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetConfiguredSpeciesCapacity constinit property declarations **********
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetConfiguredSpeciesCapacity constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetConfiguredSpeciesCapacity Property Definitions *********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetConfiguredSpeciesCapacity_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetConfiguredSpeciesCapacity Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetConfiguredSpeciesCapacity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetConfiguredSpeciesCapacity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetConfiguredSpeciesCapacity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetConfiguredSpeciesCapacity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetConfiguredSpeciesCapacity)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetConfiguredSpeciesCapacity();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetConfiguredSpeciesCapacity ********

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetCreditsPerDigiRuby *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetCreditsPerDigiRuby_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetCreditsPerDigiRuby_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCreditsPerDigiRuby constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCreditsPerDigiRuby constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCreditsPerDigiRuby Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetCreditsPerDigiRuby_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCreditsPerDigiRuby Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetCreditsPerDigiRuby", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetCreditsPerDigiRuby_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetCreditsPerDigiRuby_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetCreditsPerDigiRuby(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetCreditsPerDigiRuby)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCreditsPerDigiRuby();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetCreditsPerDigiRuby ***************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetDeEvolutionSources *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetDeEvolutionSources_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetDeEvolutionSources_Parms
	{
		FName SpeciesId;
		TArray<FDigimonSpeciesDefinition> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Indexed reverse routes: only linked, supplied species are returned. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Indexed reverse routes: only linked, supplied species are returned." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeEvolutionSources constinit property declarations *****************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeEvolutionSources constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeEvolutionSources Property Definitions ****************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetDeEvolutionSources_Parms, SpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSpeciesDefinition, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetDeEvolutionSources_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeEvolutionSources Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetDeEvolutionSources", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetDeEvolutionSources_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetDeEvolutionSources_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetDeEvolutionSources(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetDeEvolutionSources)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SpeciesId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonSpeciesDefinition>*)Z_Param__Result=P_THIS->GetDeEvolutionSources(Z_Param_SpeciesId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetDeEvolutionSources ***************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetMap ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMap_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetMap_Parms
	{
		int32 MapId;
		FDigimonMapRow OutMap;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMap constinit property declarations ********************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutMap;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTDataSubsystem_eventGetMap_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMap constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMap Property Definitions *******************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutMap = { "OutMap", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetMap_Parms, OutMap), Z_Construct_UScriptStruct_FDigimonMapRow, METADATA_PARAMS(0, nullptr) }; // d3b9faab2e26607d93728ab7bbb0de16fe897b99
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTDataSubsystem_eventGetMap_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutMap,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMap Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_STRUCT_REF(FDigimonMapRow,Z_Param_Out_OutMap);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetMap(Z_Param_MapId,Z_Param_Out_OutMap);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetMap ******************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetMove ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMove_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetMove_Parms
	{
		FName MoveId;
		FDigimonMoveSlot OutMove;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Canonical moves override old serialized power/cost values without changing equipped IDs. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Canonical moves override old serialized power/cost values without changing equipped IDs." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetMove constinit property declarations *******************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_MoveId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutMove;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTDataSubsystem_eventGetMove_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMove constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMove Property Definitions ******************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_MoveId = { "MoveId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetMove_Parms, MoveId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutMove = { "OutMove", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetMove_Parms, OutMove), Z_Construct_UScriptStruct_FDigimonMoveSlot, METADATA_PARAMS(0, nullptr) }; // a52864aab2f9dfa537fec2d0c5991c2c7dfd4635
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTDataSubsystem_eventGetMove_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutMove,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMove Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetMove", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetMove_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMove(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetMove)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_MoveId);
	P_GET_STRUCT_REF(FDigimonMoveSlot,Z_Param_Out_OutMove);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetMove(Z_Param_MoveId,Z_Param_Out_OutMove);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetMove *****************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetProvidedSpeciesCount ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetProvidedSpeciesCount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetProvidedSpeciesCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetProvidedSpeciesCount constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetProvidedSpeciesCount constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetProvidedSpeciesCount Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetProvidedSpeciesCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetProvidedSpeciesCount Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetProvidedSpeciesCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetProvidedSpeciesCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetProvidedSpeciesCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetProvidedSpeciesCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetProvidedSpeciesCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetProvidedSpeciesCount();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetProvidedSpeciesCount *************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetPublicMapCount *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetPublicMapCount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetPublicMapCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPublicMapCount constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPublicMapCount constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPublicMapCount Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetPublicMapCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPublicMapCount Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetPublicMapCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetPublicMapCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetPublicMapCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetPublicMapCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetPublicMapCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetPublicMapCount();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetPublicMapCount *******************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetShopItem ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItem_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms
	{
		FName ItemId;
		FDigimonShopItemDefinition OutItem;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetShopItem constinit property declarations ***************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutItem;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetShopItem constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetShopItem Property Definitions **************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ItemId = { "ItemId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms, ItemId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutItem = { "OutItem", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms, OutItem), Z_Construct_UScriptStruct_FDigimonShopItemDefinition, METADATA_PARAMS(0, nullptr) }; // 23d25ed9dae8b66d2d3cb91d4f43349b1af7fe88
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ItemId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetShopItem Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetShopItem", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetShopItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItem(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetShopItem)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemId);
	P_GET_STRUCT_REF(FDigimonShopItemDefinition,Z_Param_Out_OutItem);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetShopItem(Z_Param_ItemId,Z_Param_Out_OutItem);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetShopItem *************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetShopItems **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItems_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetShopItems_Parms
	{
		TArray<FDigimonShopItemDefinition> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetShopItems constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetShopItems constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetShopItems Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonShopItemDefinition, METADATA_PARAMS(0, nullptr) }; // 23d25ed9dae8b66d2d3cb91d4f43349b1af7fe88
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetShopItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 23d25ed9dae8b66d2d3cb91d4f43349b1af7fe88
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetShopItems Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetShopItems", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetShopItems_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetShopItems_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItems(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetShopItems)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonShopItemDefinition>*)Z_Param__Result=P_THIS->GetShopItems();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetShopItems ************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetSpecies ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetSpecies_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms
	{
		FName SpeciesId;
		FDigimonSpeciesDefinition OutSpecies;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetSpecies constinit property declarations ****************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutSpecies;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSpecies constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSpecies Property Definitions ***************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms, SpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutSpecies = { "OutSpecies", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms, OutSpecies), Z_Construct_UScriptStruct_FDigimonSpeciesDefinition, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutSpecies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSpecies Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetSpecies", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetSpecies_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetSpecies(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetSpecies)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SpeciesId);
	P_GET_STRUCT_REF(FDigimonSpeciesDefinition,Z_Param_Out_OutSpecies);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetSpecies(Z_Param_SpeciesId,Z_Param_Out_OutSpecies);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetSpecies **************************

// ********** Begin Class UDigimonVenomNXTDataSubsystem Function GetStarterCandidates **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetStarterCandidates_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDataSubsystem_eventGetStarterCandidates_Parms
	{
		int32 MaxResults;
		TArray<FDigimonSpeciesDefinition> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Data" },
		{ "CPP_Default_MaxResults", "12" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStarterCandidates constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxResults;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStarterCandidates constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStarterCandidates Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxResults = { "MaxResults", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetStarterCandidates_Parms, MaxResults), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSpeciesDefinition, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDataSubsystem_eventGetStarterCandidates_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3ac769a5ee7789d69a4da8b706da31e9342eb94c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxResults,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetStarterCandidates Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, nullptr, "GetStarterCandidates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetStarterCandidates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDataSubsystem_eventGetStarterCandidates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetStarterCandidates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDataSubsystem::execGetStarterCandidates)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MaxResults);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonSpeciesDefinition>*)Z_Param__Result=P_THIS->GetStarterCandidates(Z_Param_MaxResults);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDataSubsystem Function GetStarterCandidates ****************

// ********** Begin Class UDigimonVenomNXTDataSubsystem ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTDataSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTDataSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTDataSubsystem constinit property declarations ************
// ********** End Class UDigimonVenomNXTDataSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetAllMaps"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetAllMaps },
		{ .NameUTF8 = UTF8TEXT("GetAllSpecies"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetAllSpecies },
		{ .NameUTF8 = UTF8TEXT("GetConfiguredSpeciesCapacity"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetConfiguredSpeciesCapacity },
		{ .NameUTF8 = UTF8TEXT("GetCreditsPerDigiRuby"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetCreditsPerDigiRuby },
		{ .NameUTF8 = UTF8TEXT("GetDeEvolutionSources"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetDeEvolutionSources },
		{ .NameUTF8 = UTF8TEXT("GetMap"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetMap },
		{ .NameUTF8 = UTF8TEXT("GetMove"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetMove },
		{ .NameUTF8 = UTF8TEXT("GetProvidedSpeciesCount"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetProvidedSpeciesCount },
		{ .NameUTF8 = UTF8TEXT("GetPublicMapCount"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetPublicMapCount },
		{ .NameUTF8 = UTF8TEXT("GetShopItem"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetShopItem },
		{ .NameUTF8 = UTF8TEXT("GetShopItems"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetShopItems },
		{ .NameUTF8 = UTF8TEXT("GetSpecies"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetSpecies },
		{ .NameUTF8 = UTF8TEXT("GetStarterCandidates"), .Pointer = &UDigimonVenomNXTDataSubsystem::execGetStarterCandidates },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllMaps, "GetAllMaps" }, // e0d626270a2d80fcf3cb03c0a7a98bcc2a40b571
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetAllSpecies, "GetAllSpecies" }, // d9040d8d3671001cf0afb62fa0ea75ebf67a9469
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetConfiguredSpeciesCapacity, "GetConfiguredSpeciesCapacity" }, // 6c1ff8350d960264429d076a949ec4c7a2c22903
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetCreditsPerDigiRuby, "GetCreditsPerDigiRuby" }, // f08dc957999ee68a828539936171d1cbf16daccd
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetDeEvolutionSources, "GetDeEvolutionSources" }, // 79a3c3f9bca285adb9f6b1b10380709982cd609b
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMap, "GetMap" }, // 4ae506a1a85e2fa75a69ed0391ff6925f348f522
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetMove, "GetMove" }, // 7a00d681854f78f31a273a57671d5e299e2b7eea
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetProvidedSpeciesCount, "GetProvidedSpeciesCount" }, // 70256ffd6bbe5b426f6784557c82963f8eda9a5b
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetPublicMapCount, "GetPublicMapCount" }, // 9424fc3a2335ff5290698cbefc5721051d0a05fe
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItem, "GetShopItem" }, // 2b2d0d036985e46cc4f04f2fde3e08379c63c128
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetShopItems, "GetShopItems" }, // 8f6bd5b8330bfbbeea681e6ff4ffbb40633c8567
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetSpecies, "GetSpecies" }, // 889273bc3062b784b7690e3f0089ec0b7ae55982
		{ &Z_Construct_UFunction_UDigimonVenomNXTDataSubsystem_GetStarterCandidates, "GetStarterCandidates" }, // 7edc01a3fe930f4b8b2b2e3bed31a6c2eec8cf51
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTDataSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTDataSubsystem,
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
static void UDigimonVenomNXTDataSubsystem_StaticRegisterNativesUDigimonVenomNXTDataSubsystem()
{
	UClass* Class = UDigimonVenomNXTDataSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTDataSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTDataSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTDataSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.InnerSingleton,
				UDigimonVenomNXTDataSubsystem_StaticRegisterNativesUDigimonVenomNXTDataSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTDataSubsystem::UDigimonVenomNXTDataSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTDataSubsystem);
UDigimonVenomNXTDataSubsystem::~UDigimonVenomNXTDataSubsystem() {}
// ********** End Class UDigimonVenomNXTDataSubsystem **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTDataSubsystem, TEXT("UDigimonVenomNXTDataSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTDataSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTDataSubsystem), 2404716589U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDataSubsystem_h__Script_DigimonVenomNXTRuntime_22051efdb49e4c6f51f2a43e761643d4d219c415{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
