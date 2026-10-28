// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAIRivalSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UTickableWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAIRivalRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function ForceSimulationStep ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ForceSimulationStep_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventForceSimulationStep_Parms
	{
		int32 MaxRecords;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "CPP_Default_MaxRecords", "100" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ForceSimulationStep constinit property declarations *******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxRecords;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ForceSimulationStep constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ForceSimulationStep Property Definitions ******************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxRecords = { "MaxRecords", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventForceSimulationStep_Parms, MaxRecords), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxRecords,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ForceSimulationStep Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "ForceSimulationStep", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventForceSimulationStep_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventForceSimulationStep_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ForceSimulationStep(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execForceSimulationStep)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MaxRecords);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ForceSimulationStep(Z_Param_MaxRecords);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function ForceSimulationStep **************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function GetActiveRivalCount ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActiveRivalCount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventGetActiveRivalCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveRivalCount constinit property declarations *******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveRivalCount constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveRivalCount Property Definitions ******************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetActiveRivalCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetActiveRivalCount Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "GetActiveRivalCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetActiveRivalCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetActiveRivalCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActiveRivalCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execGetActiveRivalCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetActiveRivalCount();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function GetActiveRivalCount **************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function GetActivityPage ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActivityPage_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms
	{
		int32 PageIndex;
		int32 PageSize;
		FDigimonAIRivalActivityPage ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** UTC fixed 12-hour window; at most 25 rows per response. Server only. */" },
#endif
		{ "CPP_Default_PageIndex", "0" },
		{ "CPP_Default_PageSize", "20" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UTC fixed 12-hour window; at most 25 rows per response. Server only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetActivityPage constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageSize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActivityPage constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActivityPage Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageIndex = { "PageIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms, PageIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageSize = { "PageSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms, PageSize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms, ReturnValue), Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage, METADATA_PARAMS(0, nullptr) }; // 8fb19c9299962509f91282c6ddf27a520cdb2f77
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetActivityPage Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "GetActivityPage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetActivityPage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActivityPage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execGetActivityPage)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_PageIndex);
	P_GET_PROPERTY(FIntProperty,Z_Param_PageSize);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FDigimonAIRivalActivityPage*)Z_Param__Result=P_THIS->GetActivityPage(Z_Param_PageIndex,Z_Param_PageSize);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function GetActivityPage ******************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function GetAllRivals *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetAllRivals_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventGetAllRivals_Parms
	{
		TArray<FDigimonAIRivalRecord> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllRivals constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllRivals constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllRivals Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonAIRivalRecord, METADATA_PARAMS(0, nullptr) }; // 28a9f212f02b03ecde62fffc8704caaf3a606a02
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetAllRivals_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 28a9f212f02b03ecde62fffc8704caaf3a606a02
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllRivals Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "GetAllRivals", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetAllRivals_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetAllRivals_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetAllRivals(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execGetAllRivals)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonAIRivalRecord>*)Z_Param__Result=P_THIS->GetAllRivals();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function GetAllRivals *********************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function GetRival ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRival_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms
	{
		FString RivalId;
		FDigimonAIRivalRecord OutRival;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRival constinit property declarations ******************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutRival;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRival constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRival Property Definitions *****************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutRival = { "OutRival", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms, OutRival), Z_Construct_UScriptStruct_FDigimonAIRivalRecord, METADATA_PARAMS(0, nullptr) }; // 28a9f212f02b03ecde62fffc8704caaf3a606a02
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutRival,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRival Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "GetRival", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetRival_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRival(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execGetRival)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_RivalId);
	P_GET_STRUCT_REF(FDigimonAIRivalRecord,Z_Param_Out_OutRival);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetRival(Z_Param_RivalId,Z_Param_Out_OutRival);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function GetRival *************************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function GetRivalsOnMap *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRivalsOnMap_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms
	{
		int32 MapId;
		int32 MaxResults;
		TArray<FDigimonAIRivalRecord> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "CPP_Default_MaxResults", "24" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRivalsOnMap constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxResults;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRivalsOnMap constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRivalsOnMap Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxResults = { "MaxResults", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms, MaxResults), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonAIRivalRecord, METADATA_PARAMS(0, nullptr) }; // 28a9f212f02b03ecde62fffc8704caaf3a606a02
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 28a9f212f02b03ecde62fffc8704caaf3a606a02
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxResults,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRivalsOnMap Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "GetRivalsOnMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventGetRivalsOnMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRivalsOnMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execGetRivalsOnMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_PROPERTY(FIntProperty,Z_Param_MaxResults);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonAIRivalRecord>*)Z_Param__Result=P_THIS->GetRivalsOnMap(Z_Param_MapId,Z_Param_MaxResults);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function GetRivalsOnMap *******************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem Function ReleaseStoredPartner ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ReleaseStoredPartner_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms
	{
		FString RivalId;
		FGuid InstanceId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server-only release of a reserve; active party/leader and live battles are protected.\n     * Removes the owned record and its training history; scan progress is not a creature copy. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server-only release of a reserve; active party/leader and live battles are protected.\nRemoves the owned record and its training history; scan progress is not a creature copy." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ReleaseStoredPartner constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ReleaseStoredPartner constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ReleaseStoredPartner Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ReleaseStoredPartner Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, nullptr, "ReleaseStoredPartner", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820405, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalSubsystem_eventReleaseStoredPartner_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ReleaseStoredPartner(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAIRivalSubsystem::execReleaseStoredPartner)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_RivalId);
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ReleaseStoredPartner(Z_Param_RivalId,Z_Param_InstanceId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem Function ReleaseStoredPartner *************

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Persistent server simulation for up to 1,000 AI tamers. Their progression is record based;\n * replicated avatars are spawned only on maps currently occupied by real players.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAIRivalSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Persistent server simulation for up to 1,000 AI tamers. Their progression is record based;\nreplicated avatars are spawned only on maps currently occupied by real players." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAIRivalSubsystem constinit property declarations *********
// ********** End Class UDigimonVenomNXTAIRivalSubsystem constinit property declarations ***********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ForceSimulationStep"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execForceSimulationStep },
		{ .NameUTF8 = UTF8TEXT("GetActiveRivalCount"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execGetActiveRivalCount },
		{ .NameUTF8 = UTF8TEXT("GetActivityPage"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execGetActivityPage },
		{ .NameUTF8 = UTF8TEXT("GetAllRivals"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execGetAllRivals },
		{ .NameUTF8 = UTF8TEXT("GetRival"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execGetRival },
		{ .NameUTF8 = UTF8TEXT("GetRivalsOnMap"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execGetRivalsOnMap },
		{ .NameUTF8 = UTF8TEXT("ReleaseStoredPartner"), .Pointer = &UDigimonVenomNXTAIRivalSubsystem::execReleaseStoredPartner },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ForceSimulationStep, "ForceSimulationStep" }, // 76b21644ee08ebb127342b144292f2e2abba7fb5
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActiveRivalCount, "GetActiveRivalCount" }, // 725c07a5ef2e803bbe7d0a775e2da5899be7a8c2
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetActivityPage, "GetActivityPage" }, // 17a10bd931b4df4aa5b1f950bd36f8535ee189c7
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetAllRivals, "GetAllRivals" }, // efe45c2dd9946471925b6709300edf3c0ad9b057
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRival, "GetRival" }, // b8003111bfc507ae5c0d9db468fab45928313a03
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_GetRivalsOnMap, "GetRivalsOnMap" }, // 94b31c45e3fc0bd8821d66d3022e00798ffa5825
		{ &Z_Construct_UFunction_UDigimonVenomNXTAIRivalSubsystem_ReleaseStoredPartner, "ReleaseStoredPartner" }, // 9e52fb0520a1a96282947df2fe37328083612d29
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAIRivalSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UTickableWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem,
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
static void UDigimonVenomNXTAIRivalSubsystem_StaticRegisterNativesUDigimonVenomNXTAIRivalSubsystem()
{
	UClass* Class = UDigimonVenomNXTAIRivalSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAIRivalSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAIRivalSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.InnerSingleton,
				UDigimonVenomNXTAIRivalSubsystem_StaticRegisterNativesUDigimonVenomNXTAIRivalSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAIRivalSubsystem::UDigimonVenomNXTAIRivalSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAIRivalSubsystem);
UDigimonVenomNXTAIRivalSubsystem::~UDigimonVenomNXTAIRivalSubsystem() {}
// ********** End Class UDigimonVenomNXTAIRivalSubsystem *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTAIRivalSubsystem, TEXT("UDigimonVenomNXTAIRivalSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTAIRivalSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAIRivalSubsystem), 139856014U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalSubsystem_h__Script_DigimonVenomNXTRuntime_a274c444a537228112ee3fd57edcac7a41188509{
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
