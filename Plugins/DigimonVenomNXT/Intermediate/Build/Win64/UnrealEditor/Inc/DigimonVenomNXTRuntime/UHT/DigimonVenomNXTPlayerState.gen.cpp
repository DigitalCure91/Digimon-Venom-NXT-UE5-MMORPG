// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTHealingTypes.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTPlayerState() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_APlayerState(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealReceipt(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonHealResultEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonOwnedPartner(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonPlayerProfile(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonProfileChangedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonPublicPlayerSnapshot(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonScanPolicy(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonCurrency(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonTrainingStat(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonProfileChangedEvent *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonProfileChangedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonProfileChangedEvent constinit property declarations ***********
// ********** End Delegate FDigimonProfileChangedEvent constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonProfileChangedEvent__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonProfileChangedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonProfileChangedEvent *********************************************

// ********** Begin Delegate FDigimonHealResultEvent ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonHealResultEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonHealResultEvent_Parms
	{
		FDigimonHealReceipt Receipt;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Receipt_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonHealResultEvent constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Receipt;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonHealResultEvent constinit property declarations *****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonHealResultEvent Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Receipt = { "Receipt", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonHealResultEvent_Parms, Receipt), Z_Construct_UScriptStruct_FDigimonHealReceipt, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Receipt_MetaData), NewProp_Receipt_MetaData) }; // b6eaf5c755bc10846075d3fcb92018e8f9108282
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Receipt,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonHealResultEvent Property Definitions ****************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonHealResultEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonHealResultEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonHealResultEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonHealResultEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonHealResultEvent *************************************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ClientDigiLabHealResult *************
struct DigimonVenomNXTPlayerState_eventClientDigiLabHealResult_Parms
{
	FDigimonHealReceipt Receipt;
};
static FName NAME_ADigimonVenomNXTPlayerState_ClientDigiLabHealResult = FName(TEXT("ClientDigiLabHealResult"));
void ADigimonVenomNXTPlayerState::ClientDigiLabHealResult(FDigimonHealReceipt const& Receipt)
{
	DigimonVenomNXTPlayerState_eventClientDigiLabHealResult_Parms Parms;
	Parms.Receipt=Receipt;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ClientDigiLabHealResult);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ClientDigiLabHealResult_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Receipt_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientDigiLabHealResult constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Receipt;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientDigiLabHealResult constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientDigiLabHealResult Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Receipt = { "Receipt", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventClientDigiLabHealResult_Parms, Receipt), Z_Construct_UScriptStruct_FDigimonHealReceipt, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Receipt_MetaData), NewProp_Receipt_MetaData) }; // b6eaf5c755bc10846075d3fcb92018e8f9108282
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Receipt,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientDigiLabHealResult Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ClientDigiLabHealResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventClientDigiLabHealResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventClientDigiLabHealResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ClientDigiLabHealResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execClientDigiLabHealResult)
{
	P_GET_STRUCT(FDigimonHealReceipt,Z_Param_Receipt);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientDigiLabHealResult_Implementation(Z_Param_Receipt);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ClientDigiLabHealResult ***************

// ********** Begin Class ADigimonVenomNXTPlayerState Function GetInventoryQuantity ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetInventoryQuantity_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerState_eventGetInventoryQuantity_Parms
	{
		FName ItemId;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Inventory" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetInventoryQuantity constinit property declarations ******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetInventoryQuantity constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetInventoryQuantity Property Definitions *****************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ItemId = { "ItemId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetInventoryQuantity_Parms, ItemId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetInventoryQuantity_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ItemId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetInventoryQuantity Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "GetInventoryQuantity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerState_eventGetInventoryQuantity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerState_eventGetInventoryQuantity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetInventoryQuantity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execGetInventoryQuantity)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetInventoryQuantity(Z_Param_ItemId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function GetInventoryQuantity ******************

// ********** Begin Class ADigimonVenomNXTPlayerState Function GetPartner **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetPartner_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerState_eventGetPartner_Parms
	{
		FGuid InstanceId;
		FDigimonOwnedPartner OutPartner;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Party" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPartner constinit property declarations ****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutPartner;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerState_eventGetPartner_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPartner constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPartner Property Definitions ***************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetPartner_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutPartner = { "OutPartner", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetPartner_Parms, OutPartner), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(0, nullptr) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerState_eventGetPartner_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutPartner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPartner Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "GetPartner", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerState_eventGetPartner_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerState_eventGetPartner_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetPartner(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execGetPartner)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_STRUCT_REF(FDigimonOwnedPartner,Z_Param_Out_OutPartner);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetPartner(Z_Param_InstanceId,Z_Param_Out_OutPartner);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function GetPartner ****************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function GetScanPercent **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetScanPercent_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerState_eventGetScanPercent_Parms
	{
		FName SpeciesId;
		EDigimonVariant Variant;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Scan" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetScanPercent constinit property declarations ************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Variant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Variant;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetScanPercent constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetScanPercent Property Definitions ***********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetScanPercent_Parms, SpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Variant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Variant = { "Variant", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetScanPercent_Parms, Variant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventGetScanPercent_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetScanPercent Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "GetScanPercent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerState_eventGetScanPercent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerState_eventGetScanPercent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetScanPercent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execGetScanPercent)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SpeciesId);
	P_GET_ENUM(EDigimonVariant,Z_Param_Variant);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetScanPercent(Z_Param_SpeciesId,EDigimonVariant(Z_Param_Variant));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function GetScanPercent ************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function HasStarter **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_HasStarter_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerState_eventHasStarter_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Profile" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HasStarter constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerState_eventHasStarter_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasStarter constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasStarter Property Definitions ***************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerState_eventHasStarter_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasStarter Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "HasStarter", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerState_eventHasStarter_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerState_eventHasStarter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_HasStarter(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execHasStarter)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasStarter();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function HasStarter ****************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function OnRep_Profile ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_OnRep_Profile_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_Profile constinit property declarations *************************
// ********** End Function OnRep_Profile constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "OnRep_Profile", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_OnRep_Profile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execOnRep_Profile)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Profile();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function OnRep_Profile *************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerChooseStarter *****************
struct DigimonVenomNXTPlayerState_eventServerChooseStarter_Parms
{
	FName SpeciesId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerChooseStarter = FName(TEXT("ServerChooseStarter"));
void ADigimonVenomNXTPlayerState::ServerChooseStarter(FName SpeciesId)
{
	DigimonVenomNXTPlayerState_eventServerChooseStarter_Parms Parms;
	Parms.SpeciesId=SpeciesId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerChooseStarter);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerChooseStarter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Starter" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerChooseStarter constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerChooseStarter constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerChooseStarter Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerChooseStarter_Parms, SpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerChooseStarter Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerChooseStarter", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerChooseStarter_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerChooseStarter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerChooseStarter(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerChooseStarter)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SpeciesId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerChooseStarter_Implementation(Z_Param_SpeciesId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerChooseStarter *******************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerConvertDigiRubiesToCredits ****
struct DigimonVenomNXTPlayerState_eventServerConvertDigiRubiesToCredits_Parms
{
	int32 RubyAmount;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerConvertDigiRubiesToCredits = FName(TEXT("ServerConvertDigiRubiesToCredits"));
void ADigimonVenomNXTPlayerState::ServerConvertDigiRubiesToCredits(int32 RubyAmount)
{
	DigimonVenomNXTPlayerState_eventServerConvertDigiRubiesToCredits_Parms Parms;
	Parms.RubyAmount=RubyAmount;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerConvertDigiRubiesToCredits);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerConvertDigiRubiesToCredits_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Economy" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerConvertDigiRubiesToCredits constinit property declarations ******
	static const UECodeGen_Private::FIntPropertyParams NewProp_RubyAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerConvertDigiRubiesToCredits constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerConvertDigiRubiesToCredits Property Definitions *****************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RubyAmount = { "RubyAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerConvertDigiRubiesToCredits_Parms, RubyAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RubyAmount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerConvertDigiRubiesToCredits Property Definitions *******************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerConvertDigiRubiesToCredits", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerConvertDigiRubiesToCredits_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerConvertDigiRubiesToCredits_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerConvertDigiRubiesToCredits(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerConvertDigiRubiesToCredits)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_RubyAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerConvertDigiRubiesToCredits_Implementation(Z_Param_RubyAmount);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerConvertDigiRubiesToCredits ******

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerDeEvolve **********************
struct DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms
{
	FGuid InstanceId;
	FName TargetSpeciesId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerDeEvolve = FName(TEXT("ServerDeEvolve"));
void ADigimonVenomNXTPlayerState::ServerDeEvolve(FGuid InstanceId, FName TargetSpeciesId)
{
	DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.TargetSpeciesId=TargetSpeciesId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerDeEvolve);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerDeEvolve_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Evolution" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerDeEvolve constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TargetSpeciesId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerDeEvolve constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerDeEvolve Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TargetSpeciesId = { "TargetSpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms, TargetSpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetSpeciesId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerDeEvolve Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerDeEvolve", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerDeEvolve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerDeEvolve(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerDeEvolve)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_PROPERTY(FNameProperty,Z_Param_TargetSpeciesId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerDeEvolve_Implementation(Z_Param_InstanceId,Z_Param_TargetSpeciesId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerDeEvolve ************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerEvolve ************************
struct DigimonVenomNXTPlayerState_eventServerEvolve_Parms
{
	FGuid InstanceId;
	FName TargetSpeciesId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerEvolve = FName(TEXT("ServerEvolve"));
void ADigimonVenomNXTPlayerState::ServerEvolve(FGuid InstanceId, FName TargetSpeciesId)
{
	DigimonVenomNXTPlayerState_eventServerEvolve_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.TargetSpeciesId=TargetSpeciesId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerEvolve);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerEvolve_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Evolution" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerEvolve constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TargetSpeciesId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerEvolve constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerEvolve Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerEvolve_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TargetSpeciesId = { "TargetSpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerEvolve_Parms, TargetSpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetSpeciesId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerEvolve Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerEvolve", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerEvolve_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerEvolve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerEvolve(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerEvolve)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_PROPERTY(FNameProperty,Z_Param_TargetSpeciesId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerEvolve_Implementation(Z_Param_InstanceId,Z_Param_TargetSpeciesId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerEvolve **************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerFeedABIMeat *******************
struct DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms
{
	FGuid InstanceId;
	EDigimonCurrency Currency;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerFeedABIMeat = FName(TEXT("ServerFeedABIMeat"));
void ADigimonVenomNXTPlayerState::ServerFeedABIMeat(FGuid InstanceId, EDigimonCurrency Currency)
{
	DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.Currency=Currency;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerFeedABIMeat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedABIMeat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerFeedABIMeat constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Currency_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Currency;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerFeedABIMeat constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerFeedABIMeat Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Currency_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Currency = { "Currency", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms, Currency), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonCurrency, METADATA_PARAMS(0, nullptr) }; // 443a0cd325d496d4235ea910ac9a8d57d5ea4f00
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Currency_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Currency,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerFeedABIMeat Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerFeedABIMeat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerFeedABIMeat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedABIMeat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerFeedABIMeat)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_ENUM(EDigimonCurrency,Z_Param_Currency);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerFeedABIMeat_Implementation(Z_Param_InstanceId,EDigimonCurrency(Z_Param_Currency));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerFeedABIMeat *********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerFeedFarmResident **************
struct DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms
{
	FGuid InstanceId;
	FName ItemId;
	EDigimonTrainingStat Stat;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerFeedFarmResident = FName(TEXT("ServerFeedFarmResident"));
void ADigimonVenomNXTPlayerState::ServerFeedFarmResident(FGuid InstanceId, FName ItemId, EDigimonTrainingStat Stat)
{
	DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.ItemId=ItemId;
	Parms.Stat=Stat;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerFeedFarmResident);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedFarmResident_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** In-world care: only the authenticated owner's currently placed residents. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "In-world care: only the authenticated owner's currently placed residents." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ServerFeedFarmResident constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Stat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Stat;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerFeedFarmResident constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerFeedFarmResident Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ItemId = { "ItemId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms, ItemId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Stat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Stat = { "Stat", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms, Stat), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonTrainingStat, METADATA_PARAMS(0, nullptr) }; // c6ffa463b25ff175f41887d10c821b528f35d30d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ItemId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stat,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerFeedFarmResident Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerFeedFarmResident", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerFeedFarmResident_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedFarmResident(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerFeedFarmResident)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemId);
	P_GET_ENUM(EDigimonTrainingStat,Z_Param_Stat);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerFeedFarmResident_Implementation(Z_Param_InstanceId,Z_Param_ItemId,EDigimonTrainingStat(Z_Param_Stat));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerFeedFarmResident ****************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerHealAll ***********************
static FName NAME_ADigimonVenomNXTPlayerState_ServerHealAll = FName(TEXT("ServerHealAll"));
void ADigimonVenomNXTPlayerState::ServerHealAll()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerHealAll);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerHealAll_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiLab" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerHealAll constinit property declarations *************************
// ********** End Function ServerHealAll constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerHealAll", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerHealAll(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerHealAll)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerHealAll_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerHealAll *************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerMaterialize *******************
struct DigimonVenomNXTPlayerState_eventServerMaterialize_Parms
{
	FName SpeciesId;
	EDigimonVariant Variant;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerMaterialize = FName(TEXT("ServerMaterialize"));
void ADigimonVenomNXTPlayerState::ServerMaterialize(FName SpeciesId, EDigimonVariant Variant)
{
	DigimonVenomNXTPlayerState_eventServerMaterialize_Parms Parms;
	Parms.SpeciesId=SpeciesId;
	Parms.Variant=Variant;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerMaterialize);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerMaterialize_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiLab" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerMaterialize constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Variant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Variant;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerMaterialize constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerMaterialize Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerMaterialize_Parms, SpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Variant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Variant = { "Variant", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerMaterialize_Parms, Variant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerMaterialize Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerMaterialize", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerMaterialize_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerMaterialize_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerMaterialize(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerMaterialize)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SpeciesId);
	P_GET_ENUM(EDigimonVariant,Z_Param_Variant);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerMaterialize_Implementation(Z_Param_SpeciesId,EDigimonVariant(Z_Param_Variant));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerMaterialize *********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerPurchaseItem ******************
struct DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms
{
	FName ItemId;
	EDigimonCurrency Currency;
	int32 Quantity;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerPurchaseItem = FName(TEXT("ServerPurchaseItem"));
void ADigimonVenomNXTPlayerState::ServerPurchaseItem(FName ItemId, EDigimonCurrency Currency, int32 Quantity)
{
	DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms Parms;
	Parms.ItemId=ItemId;
	Parms.Currency=Currency;
	Parms.Quantity=Quantity;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerPurchaseItem);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerPurchaseItem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Shop" },
		{ "CPP_Default_Quantity", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerPurchaseItem constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Currency_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Currency;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Quantity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerPurchaseItem constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerPurchaseItem Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ItemId = { "ItemId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms, ItemId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Currency_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Currency = { "Currency", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms, Currency), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonCurrency, METADATA_PARAMS(0, nullptr) }; // 443a0cd325d496d4235ea910ac9a8d57d5ea4f00
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Quantity = { "Quantity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms, Quantity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ItemId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Currency_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Currency,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Quantity,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerPurchaseItem Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerPurchaseItem", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerPurchaseItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerPurchaseItem(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerPurchaseItem)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemId);
	P_GET_ENUM(EDigimonCurrency,Z_Param_Currency);
	P_GET_PROPERTY(FIntProperty,Z_Param_Quantity);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerPurchaseItem_Implementation(Z_Param_ItemId,EDigimonCurrency(Z_Param_Currency),Z_Param_Quantity);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerPurchaseItem ********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerRequestDigiLabHeal ************
struct DigimonVenomNXTPlayerState_eventServerRequestDigiLabHeal_Parms
{
	FGuid RequestId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerRequestDigiLabHeal = FName(TEXT("ServerRequestDigiLabHeal"));
void ADigimonVenomNXTPlayerState::ServerRequestDigiLabHeal(FGuid RequestId)
{
	DigimonVenomNXTPlayerState_eventServerRequestDigiLabHeal_Parms Parms;
	Parms.RequestId=RequestId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerRequestDigiLabHeal);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerRequestDigiLabHeal_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiLab" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** UI request identity prevents duplicate recovery on a retried reliable action. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UI request identity prevents duplicate recovery on a retried reliable action." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestDigiLabHeal constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RequestId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRequestDigiLabHeal constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRequestDigiLabHeal Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RequestId = { "RequestId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerRequestDigiLabHeal_Parms, RequestId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequestId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRequestDigiLabHeal Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerRequestDigiLabHeal", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerRequestDigiLabHeal_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerRequestDigiLabHeal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerRequestDigiLabHeal(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerRequestDigiLabHeal)
{
	P_GET_STRUCT(FGuid,Z_Param_RequestId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestDigiLabHeal_Implementation(Z_Param_RequestId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerRequestDigiLabHeal **************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerSetFarmResident ***************
struct DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms
{
	FGuid InstanceId;
	bool bResident;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerSetFarmResident = FName(TEXT("ServerSetFarmResident"));
void ADigimonVenomNXTPlayerState::ServerSetFarmResident(FGuid InstanceId, bool bResident)
{
	DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.bResident=bResident ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerSetFarmResident);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetFarmResident_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSetFarmResident constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static void NewProp_bResident_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms*)Obj)->bResident = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bResident;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSetFarmResident constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSetFarmResident Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bResident = { "bResident", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms), &UHT_STATICS::NewProp_bResident_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bResident,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSetFarmResident Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerSetFarmResident", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerSetFarmResident_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetFarmResident(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerSetFarmResident)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_UBOOL(Z_Param_bResident);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSetFarmResident_Implementation(Z_Param_InstanceId,Z_Param_bResident);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerSetFarmResident *****************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerSetParty **********************
struct DigimonVenomNXTPlayerState_eventServerSetParty_Parms
{
	TArray<FGuid> NewParty;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerSetParty = FName(TEXT("ServerSetParty"));
void ADigimonVenomNXTPlayerState::ServerSetParty(TArray<FGuid> const& NewParty)
{
	DigimonVenomNXTPlayerState_eventServerSetParty_Parms Parms;
	Parms.NewParty=NewParty;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerSetParty);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetParty_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Party" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewParty_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSetParty constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewParty_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_NewParty;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSetParty constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSetParty Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NewParty_Inner = { "NewParty", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_NewParty = { "NewParty", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerSetParty_Parms, NewParty), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewParty_MetaData), NewProp_NewParty_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewParty_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewParty,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSetParty Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerSetParty", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerSetParty_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerSetParty_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetParty(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerSetParty)
{
	P_GET_TARRAY(FGuid,Z_Param_NewParty);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSetParty_Implementation(Z_Param_NewParty);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerSetParty ************************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerSetTamerStyle *****************
struct DigimonVenomNXTPlayerState_eventServerSetTamerStyle_Parms
{
	FName TamerStyleId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerSetTamerStyle = FName(TEXT("ServerSetTamerStyle"));
void ADigimonVenomNXTPlayerState::ServerSetTamerStyle(FName TamerStyleId)
{
	DigimonVenomNXTPlayerState_eventServerSetTamerStyle_Parms Parms;
	Parms.TamerStyleId=TamerStyleId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerSetTamerStyle);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetTamerStyle_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSetTamerStyle constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_TamerStyleId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSetTamerStyle constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSetTamerStyle Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TamerStyleId = { "TamerStyleId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerSetTamerStyle_Parms, TamerStyleId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerStyleId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSetTamerStyle Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerSetTamerStyle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerSetTamerStyle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerSetTamerStyle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetTamerStyle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerSetTamerStyle)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_TamerStyleId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSetTamerStyle_Implementation(Z_Param_TamerStyleId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerSetTamerStyle *******************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerUseABIMeat ********************
struct DigimonVenomNXTPlayerState_eventServerUseABIMeat_Parms
{
	FGuid InstanceId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerUseABIMeat = FName(TEXT("ServerUseABIMeat"));
void ADigimonVenomNXTPlayerState::ServerUseABIMeat(FGuid InstanceId)
{
	DigimonVenomNXTPlayerState_eventServerUseABIMeat_Parms Parms;
	Parms.InstanceId=InstanceId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerUseABIMeat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseABIMeat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Items" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerUseABIMeat constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerUseABIMeat constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerUseABIMeat Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseABIMeat_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerUseABIMeat Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerUseABIMeat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerUseABIMeat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerUseABIMeat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseABIMeat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerUseABIMeat)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerUseABIMeat_Implementation(Z_Param_InstanceId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerUseABIMeat **********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerUseCAMTreat *******************
struct DigimonVenomNXTPlayerState_eventServerUseCAMTreat_Parms
{
	FGuid InstanceId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerUseCAMTreat = FName(TEXT("ServerUseCAMTreat"));
void ADigimonVenomNXTPlayerState::ServerUseCAMTreat(FGuid InstanceId)
{
	DigimonVenomNXTPlayerState_eventServerUseCAMTreat_Parms Parms;
	Parms.InstanceId=InstanceId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerUseCAMTreat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseCAMTreat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerUseCAMTreat constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerUseCAMTreat constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerUseCAMTreat Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseCAMTreat_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerUseCAMTreat Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerUseCAMTreat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerUseCAMTreat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerUseCAMTreat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseCAMTreat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerUseCAMTreat)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerUseCAMTreat_Implementation(Z_Param_InstanceId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerUseCAMTreat *********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerUseDigiMeat *******************
struct DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms
{
	FGuid InstanceId;
	EDigimonTrainingStat Stat;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerUseDigiMeat = FName(TEXT("ServerUseDigiMeat"));
void ADigimonVenomNXTPlayerState::ServerUseDigiMeat(FGuid InstanceId, EDigimonTrainingStat Stat)
{
	DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.Stat=Stat;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerUseDigiMeat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseDigiMeat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerUseDigiMeat constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Stat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Stat;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerUseDigiMeat constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerUseDigiMeat Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Stat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Stat = { "Stat", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms, Stat), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonTrainingStat, METADATA_PARAMS(0, nullptr) }; // c6ffa463b25ff175f41887d10c821b528f35d30d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stat,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerUseDigiMeat Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerUseDigiMeat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerUseDigiMeat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseDigiMeat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerUseDigiMeat)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_ENUM(EDigimonTrainingStat,Z_Param_Stat);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerUseDigiMeat_Implementation(Z_Param_InstanceId,EDigimonTrainingStat(Z_Param_Stat));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerUseDigiMeat *********************

// ********** Begin Class ADigimonVenomNXTPlayerState Function ServerUseHealingItem ****************
struct DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms
{
	FGuid InstanceId;
	FName ItemId;
};
static FName NAME_ADigimonVenomNXTPlayerState_ServerUseHealingItem = FName(TEXT("ServerUseHealingItem"));
void ADigimonVenomNXTPlayerState::ServerUseHealingItem(FGuid InstanceId, FName ItemId)
{
	DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms Parms;
	Parms.InstanceId=InstanceId;
	Parms.ItemId=ItemId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerState_ServerUseHealingItem);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseHealingItem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Items" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerUseHealingItem constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerUseHealingItem constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerUseHealingItem Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ItemId = { "ItemId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms, ItemId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ItemId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerUseHealingItem Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerState, nullptr, "ServerUseHealingItem", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerState_eventServerUseHealingItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseHealingItem(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerState::execServerUseHealingItem)
{
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerUseHealingItem_Implementation(Z_Param_InstanceId,Z_Param_ItemId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerState Function ServerUseHealingItem ******************

// ********** Begin Class ADigimonVenomNXTPlayerState **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTPlayerState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DigimonVenomNXTPlayerState.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Profile_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Profile" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Disk state is not one unbounded actor-channel property. The owner receives\n// complete checked snapshots through its controller; public presence stays replicated.\n" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Disk state is not one unbounded actor-channel property. The owner receives\ncomplete checked snapshots through its controller; public presence stays replicated." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanPolicy_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiDex" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PublicSnapshot_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Profile" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnProfileChanged_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Profile" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDigiLabHealResult_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiLab" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RecentDigiLabHealReceipts_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTPlayerState constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Profile;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ScanPolicy;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PublicSnapshot;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnProfileChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDigiLabHealResult;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RecentDigiLabHealReceipts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RecentDigiLabHealReceipts;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTPlayerState constinit property declarations ****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClientDigiLabHealResult"), .Pointer = &ADigimonVenomNXTPlayerState::execClientDigiLabHealResult },
		{ .NameUTF8 = UTF8TEXT("GetInventoryQuantity"), .Pointer = &ADigimonVenomNXTPlayerState::execGetInventoryQuantity },
		{ .NameUTF8 = UTF8TEXT("GetPartner"), .Pointer = &ADigimonVenomNXTPlayerState::execGetPartner },
		{ .NameUTF8 = UTF8TEXT("GetScanPercent"), .Pointer = &ADigimonVenomNXTPlayerState::execGetScanPercent },
		{ .NameUTF8 = UTF8TEXT("HasStarter"), .Pointer = &ADigimonVenomNXTPlayerState::execHasStarter },
		{ .NameUTF8 = UTF8TEXT("OnRep_Profile"), .Pointer = &ADigimonVenomNXTPlayerState::execOnRep_Profile },
		{ .NameUTF8 = UTF8TEXT("ServerChooseStarter"), .Pointer = &ADigimonVenomNXTPlayerState::execServerChooseStarter },
		{ .NameUTF8 = UTF8TEXT("ServerConvertDigiRubiesToCredits"), .Pointer = &ADigimonVenomNXTPlayerState::execServerConvertDigiRubiesToCredits },
		{ .NameUTF8 = UTF8TEXT("ServerDeEvolve"), .Pointer = &ADigimonVenomNXTPlayerState::execServerDeEvolve },
		{ .NameUTF8 = UTF8TEXT("ServerEvolve"), .Pointer = &ADigimonVenomNXTPlayerState::execServerEvolve },
		{ .NameUTF8 = UTF8TEXT("ServerFeedABIMeat"), .Pointer = &ADigimonVenomNXTPlayerState::execServerFeedABIMeat },
		{ .NameUTF8 = UTF8TEXT("ServerFeedFarmResident"), .Pointer = &ADigimonVenomNXTPlayerState::execServerFeedFarmResident },
		{ .NameUTF8 = UTF8TEXT("ServerHealAll"), .Pointer = &ADigimonVenomNXTPlayerState::execServerHealAll },
		{ .NameUTF8 = UTF8TEXT("ServerMaterialize"), .Pointer = &ADigimonVenomNXTPlayerState::execServerMaterialize },
		{ .NameUTF8 = UTF8TEXT("ServerPurchaseItem"), .Pointer = &ADigimonVenomNXTPlayerState::execServerPurchaseItem },
		{ .NameUTF8 = UTF8TEXT("ServerRequestDigiLabHeal"), .Pointer = &ADigimonVenomNXTPlayerState::execServerRequestDigiLabHeal },
		{ .NameUTF8 = UTF8TEXT("ServerSetFarmResident"), .Pointer = &ADigimonVenomNXTPlayerState::execServerSetFarmResident },
		{ .NameUTF8 = UTF8TEXT("ServerSetParty"), .Pointer = &ADigimonVenomNXTPlayerState::execServerSetParty },
		{ .NameUTF8 = UTF8TEXT("ServerSetTamerStyle"), .Pointer = &ADigimonVenomNXTPlayerState::execServerSetTamerStyle },
		{ .NameUTF8 = UTF8TEXT("ServerUseABIMeat"), .Pointer = &ADigimonVenomNXTPlayerState::execServerUseABIMeat },
		{ .NameUTF8 = UTF8TEXT("ServerUseCAMTreat"), .Pointer = &ADigimonVenomNXTPlayerState::execServerUseCAMTreat },
		{ .NameUTF8 = UTF8TEXT("ServerUseDigiMeat"), .Pointer = &ADigimonVenomNXTPlayerState::execServerUseDigiMeat },
		{ .NameUTF8 = UTF8TEXT("ServerUseHealingItem"), .Pointer = &ADigimonVenomNXTPlayerState::execServerUseHealingItem },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ClientDigiLabHealResult, "ClientDigiLabHealResult" }, // 6a981f433a307b0689b7d21ff20d8ce6c6922093
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetInventoryQuantity, "GetInventoryQuantity" }, // 01b5a19be54860730683347a2c030200be03054b
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetPartner, "GetPartner" }, // f3d974d1ab24e296f3d8852756ecb620b96a9e3a
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_GetScanPercent, "GetScanPercent" }, // 894847532880b31da8448e290dbdc3ae040a3633
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_HasStarter, "HasStarter" }, // 083af924cba3c08aef8f8f0c2cef9ddddf79af4f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_OnRep_Profile, "OnRep_Profile" }, // 4c3cc7184c197c0df95b4bb0ed5ba94df537d464
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerChooseStarter, "ServerChooseStarter" }, // 96f5ca7bafcfd65a30ba8fb0c07d68608bb4521f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerConvertDigiRubiesToCredits, "ServerConvertDigiRubiesToCredits" }, // 321037c87071e632d65cf9141a08b1929c20cbb3
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerDeEvolve, "ServerDeEvolve" }, // 1f1269b91a69fae408830dc8c383e7656d60fd9d
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerEvolve, "ServerEvolve" }, // 9d9fd5ba2689a979cdd0e11eec76cf10169b942f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedABIMeat, "ServerFeedABIMeat" }, // c97fe39b9bdd731a1e34c69742b6b970de2b72ad
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerFeedFarmResident, "ServerFeedFarmResident" }, // a8bdd4f0a8a5f4367a41abf7bb331500e6efc779
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerHealAll, "ServerHealAll" }, // 6b7032507516877c9b229bc6770a82be0dd8ebf4
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerMaterialize, "ServerMaterialize" }, // cf4f416121e1bd8c444ebac6c5ba502a58f3fc0e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerPurchaseItem, "ServerPurchaseItem" }, // db2bea466abb066343e27d21dc20448af11315b0
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerRequestDigiLabHeal, "ServerRequestDigiLabHeal" }, // 9a6b69508751508e7b3c05556c6d2450d6b5336e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetFarmResident, "ServerSetFarmResident" }, // db24a21013e6aab6686f50a6c5543b636eafe02b
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetParty, "ServerSetParty" }, // 8b88558a3b74b602034a33ea25434a4397d0fd3b
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerSetTamerStyle, "ServerSetTamerStyle" }, // 14b45ec16ba91a01e959154834b2e124bbb73e1f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseABIMeat, "ServerUseABIMeat" }, // da86fc99d9c13cee5911cd2d6417cbcd5363144d
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseCAMTreat, "ServerUseCAMTreat" }, // 87d65b7817fe412a36f6a0b575456b79e5176b08
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseDigiMeat, "ServerUseDigiMeat" }, // 0c428c6ed06d2b9c32f7f49dce36d8142ef6c60f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerState_ServerUseHealingItem, "ServerUseHealingItem" }, // d9f337426c90ed61181ef26bbfe364e20dd3563b
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTPlayerState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTPlayerState Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Profile = { "Profile", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, Profile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Profile_MetaData), NewProp_Profile_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ScanPolicy = { "ScanPolicy", "OnRep_Profile", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, ScanPolicy), Z_Construct_UScriptStruct_FDigimonScanPolicy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanPolicy_MetaData), NewProp_ScanPolicy_MetaData) }; // b3563c17e26dac4837fa79f919c3cd96a16a2b81
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PublicSnapshot = { "PublicSnapshot", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, PublicSnapshot), Z_Construct_UScriptStruct_FDigimonPublicPlayerSnapshot, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PublicSnapshot_MetaData), NewProp_PublicSnapshot_MetaData) }; // d2d72debbcab18588f3fd379208a1eedf6b08e8d
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnProfileChanged = { "OnProfileChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, OnProfileChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonProfileChangedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnProfileChanged_MetaData), NewProp_OnProfileChanged_MetaData) }; // 2018fd758c0c9d17fa9bc52759be46fa1335c675
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnDigiLabHealResult = { "OnDigiLabHealResult", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, OnDigiLabHealResult), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonHealResultEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDigiLabHealResult_MetaData), NewProp_OnDigiLabHealResult_MetaData) }; // d50867a3b3da509c10c4b595aaf615a5d07e9109
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RecentDigiLabHealReceipts_Inner = { "RecentDigiLabHealReceipts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonHealReceipt, METADATA_PARAMS(0, nullptr) }; // b6eaf5c755bc10846075d3fcb92018e8f9108282
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RecentDigiLabHealReceipts = { "RecentDigiLabHealReceipts", nullptr, (EPropertyFlags)0x0020080000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerState, RecentDigiLabHealReceipts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RecentDigiLabHealReceipts_MetaData), NewProp_RecentDigiLabHealReceipts_MetaData) }; // b6eaf5c755bc10846075d3fcb92018e8f9108282
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Profile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanPolicy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PublicSnapshot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnProfileChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnDigiLabHealResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecentDigiLabHealReceipts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecentDigiLabHealReceipts,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTPlayerState Property Definitions ***************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APlayerState,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTPlayerState,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADigimonVenomNXTPlayerState_StaticRegisterNativesADigimonVenomNXTPlayerState()
{
	UClass* Class = ADigimonVenomNXTPlayerState::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState;
UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTPlayerState;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTPlayerState"),
				Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.InnerSingleton,
				ADigimonVenomNXTPlayerState_StaticRegisterNativesADigimonVenomNXTPlayerState,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTPlayerState::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_ScanPolicy(TEXT("ScanPolicy"));
	static FName Name_PublicSnapshot(TEXT("PublicSnapshot"));
	const bool bIsValid = true
		&& Name_ScanPolicy == ClassReps[(int32)ENetFields_Private::ScanPolicy].Property->GetFName()
		&& Name_PublicSnapshot == ClassReps[(int32)ENetFields_Private::PublicSnapshot].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTPlayerState"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTPlayerState);
ADigimonVenomNXTPlayerState::~ADigimonVenomNXTPlayerState() {}
// ********** End Class ADigimonVenomNXTPlayerState ************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTPlayerState, TEXT("ADigimonVenomNXTPlayerState"), &Z_Registration_Info_UClass_ADigimonVenomNXTPlayerState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTPlayerState), 3025804813U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h__Script_DigimonVenomNXTRuntime_716c5a1188f2d8e8457df3def57b1f0516e1e4de{
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
