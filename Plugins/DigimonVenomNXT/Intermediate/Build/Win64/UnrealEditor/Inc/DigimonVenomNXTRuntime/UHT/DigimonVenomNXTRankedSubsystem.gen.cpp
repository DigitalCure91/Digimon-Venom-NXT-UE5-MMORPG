// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTRankedSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRankedPublicEntry(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonRankedGrade(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function GetCurrentSeasonId **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetCurrentSeasonId_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventGetCurrentSeasonId_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentSeasonId constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentSeasonId constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentSeasonId Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetCurrentSeasonId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentSeasonId Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "GetCurrentSeasonId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetCurrentSeasonId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetCurrentSeasonId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetCurrentSeasonId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execGetCurrentSeasonId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetCurrentSeasonId();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function GetCurrentSeasonId ****************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function GetGradeForRating ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeForRating_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventGetGradeForRating_Parms
	{
		int32 Rating;
		EDigimonRankedGrade ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetGradeForRating constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Rating;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetGradeForRating constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetGradeForRating Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Rating = { "Rating", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetGradeForRating_Parms, Rating), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetGradeForRating_Parms, ReturnValue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonRankedGrade, METADATA_PARAMS(0, nullptr) }; // e9a262c615e6baead609b2d36f7999f891ed58fb
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Rating,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetGradeForRating Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "GetGradeForRating", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetGradeForRating_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetGradeForRating_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeForRating(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execGetGradeForRating)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Rating);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EDigimonRankedGrade*)Z_Param__Result=UDigimonVenomNXTRankedSubsystem::GetGradeForRating(Z_Param_Rating);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function GetGradeForRating *****************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function GetGradeLabel *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeLabel_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventGetGradeLabel_Parms
	{
		EDigimonRankedGrade Grade;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetGradeLabel constinit property declarations *************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Grade_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Grade;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetGradeLabel constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetGradeLabel Property Definitions ************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Grade_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Grade = { "Grade", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetGradeLabel_Parms, Grade), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonRankedGrade, METADATA_PARAMS(0, nullptr) }; // e9a262c615e6baead609b2d36f7999f891ed58fb
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetGradeLabel_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Grade_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Grade,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetGradeLabel Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "GetGradeLabel", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetGradeLabel_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetGradeLabel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeLabel(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execGetGradeLabel)
{
	P_GET_ENUM(EDigimonRankedGrade,Z_Param_Grade);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UDigimonVenomNXTRankedSubsystem::GetGradeLabel(EDigimonRankedGrade(Z_Param_Grade));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function GetGradeLabel *********************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function GetTop100 ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetTop100_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventGetTop100_Parms
	{
		TArray<FDigimonRankedPublicEntry> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTop100 constinit property declarations *****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTop100 constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTop100 Property Definitions ****************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonRankedPublicEntry, METADATA_PARAMS(0, nullptr) }; // ea5c967d263cd6cb304ebfcda1ed3ac8c9f713da
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventGetTop100_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // ea5c967d263cd6cb304ebfcda1ed3ac8c9f713da
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTop100 Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "GetTop100", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetTop100_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventGetTop100_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetTop100(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execGetTop100)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FDigimonRankedPublicEntry>*)Z_Param__Result=P_THIS->GetTop100();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function GetTop100 *************************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function RunQuickMatch *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_RunQuickMatch_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms
	{
		ADigimonVenomNXTPlayerState* Challenger;
		FString OutMessage;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RunQuickMatch constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Challenger;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutMessage;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RunQuickMatch constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RunQuickMatch Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Challenger = { "Challenger", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms, Challenger), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutMessage = { "OutMessage", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms, OutMessage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Challenger,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RunQuickMatch Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "RunQuickMatch", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventRunQuickMatch_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_RunQuickMatch(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execRunQuickMatch)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_Challenger);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutMessage);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->RunQuickMatch(Z_Param_Challenger,Z_Param_Out_OutMessage);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function RunQuickMatch *********************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem Function SaveDefenderLineup **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_SaveDefenderLineup_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms
	{
		ADigimonVenomNXTPlayerState* PlayerState;
		FString OutMessage;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveDefenderLineup constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerState;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutMessage;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SaveDefenderLineup constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SaveDefenderLineup Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerState = { "PlayerState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms, PlayerState), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutMessage = { "OutMessage", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms, OutMessage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SaveDefenderLineup Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, nullptr, "SaveDefenderLineup", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRankedSubsystem_eventSaveDefenderLineup_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_SaveDefenderLineup(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRankedSubsystem::execSaveDefenderLineup)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_PlayerState);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutMessage);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SaveDefenderLineup(Z_Param_PlayerState,Z_Param_Out_OutMessage);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRankedSubsystem Function SaveDefenderLineup ****************

// ********** Begin Class UDigimonVenomNXTRankedSubsystem ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Authoritative seasonal ladder: real auto combat, durable energy and idempotent payouts. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTRankedSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRankedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Authoritative seasonal ladder: real auto combat, durable energy and idempotent payouts." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTRankedSubsystem constinit property declarations **********
// ********** End Class UDigimonVenomNXTRankedSubsystem constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentSeasonId"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execGetCurrentSeasonId },
		{ .NameUTF8 = UTF8TEXT("GetGradeForRating"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execGetGradeForRating },
		{ .NameUTF8 = UTF8TEXT("GetGradeLabel"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execGetGradeLabel },
		{ .NameUTF8 = UTF8TEXT("GetTop100"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execGetTop100 },
		{ .NameUTF8 = UTF8TEXT("RunQuickMatch"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execRunQuickMatch },
		{ .NameUTF8 = UTF8TEXT("SaveDefenderLineup"), .Pointer = &UDigimonVenomNXTRankedSubsystem::execSaveDefenderLineup },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetCurrentSeasonId, "GetCurrentSeasonId" }, // e0b1e470d2b4bd6563a774a62cce9b0e04923333
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeForRating, "GetGradeForRating" }, // e7d5b830edc6cc4ef4d51f136a5477f3e4b84ed7
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetGradeLabel, "GetGradeLabel" }, // 9d5e61240072fc046d9a180eceaa6e7a3ae52095
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_GetTop100, "GetTop100" }, // 8e868fb3fa8bc3be2eb5bd732d6d3775681df139
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_RunQuickMatch, "RunQuickMatch" }, // 8cf1556a4ffcf472001c03ecce83d21cb5e02271
		{ &Z_Construct_UFunction_UDigimonVenomNXTRankedSubsystem_SaveDefenderLineup, "SaveDefenderLineup" }, // 1ba20bcfbe49f009a62d452a00f9ddbac48befde
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTRankedSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem,
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
static void UDigimonVenomNXTRankedSubsystem_StaticRegisterNativesUDigimonVenomNXTRankedSubsystem()
{
	UClass* Class = UDigimonVenomNXTRankedSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTRankedSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTRankedSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.InnerSingleton,
				UDigimonVenomNXTRankedSubsystem_StaticRegisterNativesUDigimonVenomNXTRankedSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTRankedSubsystem::UDigimonVenomNXTRankedSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTRankedSubsystem);
UDigimonVenomNXTRankedSubsystem::~UDigimonVenomNXTRankedSubsystem() {}
// ********** End Class UDigimonVenomNXTRankedSubsystem ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTRankedSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTRankedSubsystem, TEXT("UDigimonVenomNXTRankedSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTRankedSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTRankedSubsystem), 1078413544U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTRankedSubsystem_h__Script_DigimonVenomNXTRuntime_cf98a805e1dac65001a09ea8a345a4721eb90572{
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
