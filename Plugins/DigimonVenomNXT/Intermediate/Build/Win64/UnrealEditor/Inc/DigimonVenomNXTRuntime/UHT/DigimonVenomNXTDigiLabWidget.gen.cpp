// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTDigiLabWidget.h"
#include "DigimonVenomNXTHealingTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTDigiLabWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UProgressBar(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonDigiLabCardView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealReceipt(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonDigiLabCardView *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonDigiLabCardView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonDigiLabCardView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonDigiLabCardView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Slot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Identity_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkillPoints_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Restored_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HPBar_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SPBar_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pluses_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonDigiLabCardView constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Card;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Slot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Identity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Health;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkillPoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Status;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Restored;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HPBar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SPBar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Pluses_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Pluses;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonDigiLabCardView constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonDigiLabCardView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonDigiLabCardView Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Card), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Card_MetaData), NewProp_Card_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Slot = { "Slot", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Slot), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Slot_MetaData), NewProp_Slot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Identity = { "Identity", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Identity), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Identity_MetaData), NewProp_Identity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Health), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Health_MetaData), NewProp_Health_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SkillPoints = { "SkillPoints", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, SkillPoints), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkillPoints_MetaData), NewProp_SkillPoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Status), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Status_MetaData), NewProp_Status_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Restored = { "Restored", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Restored), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Restored_MetaData), NewProp_Restored_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HPBar = { "HPBar", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, HPBar), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HPBar_MetaData), NewProp_HPBar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SPBar = { "SPBar", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, SPBar), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SPBar_MetaData), NewProp_SPBar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Pluses_Inner = { "Pluses", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Pluses = { "Pluses", nullptr, (EPropertyFlags)0x0114008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDigiLabCardView, Pluses), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pluses_MetaData), NewProp_Pluses_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Card,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Slot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Identity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Health,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkillPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Status,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Restored,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HPBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SPBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pluses_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pluses,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonDigiLabCardView Property Definitions ************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonDigiLabCardView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonDigiLabCardView>(),
	alignof(FDigimonDigiLabCardView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonDigiLabCardView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonDigiLabCardView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonDigiLabCardView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonDigiLabCardView *********************************************

// ********** Begin Class UDigimonVenomNXTDigiLabWidget Function HandleAction **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDigiLabWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Action_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleAction constinit property declarations **************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Action;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Payload;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleAction constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleAction Property Definitions *************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDigiLabWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDigiLabWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDigiLabWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDigiLabWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDigiLabWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDigiLabWidget Function HandleAction ************************

// ********** Begin Class UDigimonVenomNXTDigiLabWidget Function HandleHealResult ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleHealResult_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTDigiLabWidget_eventHandleHealResult_Parms
	{
		FDigimonHealReceipt Receipt;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Receipt_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleHealResult constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Receipt;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleHealResult constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleHealResult Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Receipt = { "Receipt", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTDigiLabWidget_eventHandleHealResult_Parms, Receipt), Z_Construct_UScriptStruct_FDigimonHealReceipt, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Receipt_MetaData), NewProp_Receipt_MetaData) }; // b6eaf5c755bc10846075d3fcb92018e8f9108282
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Receipt,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleHealResult Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget, nullptr, "HandleHealResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTDigiLabWidget_eventHandleHealResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTDigiLabWidget_eventHandleHealResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleHealResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDigiLabWidget::execHandleHealResult)
{
	P_GET_STRUCT_REF(FDigimonHealReceipt,Z_Param_Out_Receipt);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleHealResult(Z_Param_Out_Receipt);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDigiLabWidget Function HandleHealResult ********************

// ********** Begin Class UDigimonVenomNXTDigiLabWidget Function RefreshFromProfile ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_RefreshFromProfile_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiLab" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshFromProfile constinit property declarations ********************
// ********** End Function RefreshFromProfile constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget, nullptr, "RefreshFromProfile", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_RefreshFromProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTDigiLabWidget::execRefreshFromProfile)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshFromProfile();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTDigiLabWidget Function RefreshFromProfile ******************

// ********** Begin Class UDigimonVenomNXTDigiLabWidget ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Retained recovery dashboard. Animation follows confirmed receipts, never predicted healing. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTDigiLabWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retained recovery dashboard. Animation follows confirmed receipts, never predicted healing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartySummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollectionSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RecoveryStatus_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HealCaption_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResearchSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResearchDetails_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HealButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyCards_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTDigiLabWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTDigiLabWidget constinit property declarations ************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartySummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollectionSummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RecoveryStatus;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HealCaption;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResearchSummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResearchDetails;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HealButton;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PartyCards_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PartyCards;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTDigiLabWidget constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTDigiLabWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleHealResult"), .Pointer = &UDigimonVenomNXTDigiLabWidget::execHandleHealResult },
		{ .NameUTF8 = UTF8TEXT("RefreshFromProfile"), .Pointer = &UDigimonVenomNXTDigiLabWidget::execRefreshFromProfile },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleAction, "HandleAction" }, // 9e84c5f974cd52fbe54fec23e02922f3344f4d4b
		{ &Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_HandleHealResult, "HandleHealResult" }, // 9ae27de89d8fbc006bbc9334e22ce6f74eacee21
		{ &Z_Construct_UFunction_UDigimonVenomNXTDigiLabWidget_RefreshFromProfile, "RefreshFromProfile" }, // fdef018f99d35c02055115535169d607e6c37416
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTDigiLabWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTDigiLabWidget Property Definitions ***********************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, Root), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartySummary = { "PartySummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, PartySummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartySummary_MetaData), NewProp_PartySummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CollectionSummary = { "CollectionSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, CollectionSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollectionSummary_MetaData), NewProp_CollectionSummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RecoveryStatus = { "RecoveryStatus", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, RecoveryStatus), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RecoveryStatus_MetaData), NewProp_RecoveryStatus_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HealCaption = { "HealCaption", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, HealCaption), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HealCaption_MetaData), NewProp_HealCaption_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResearchSummary = { "ResearchSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, ResearchSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResearchSummary_MetaData), NewProp_ResearchSummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResearchDetails = { "ResearchDetails", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, ResearchDetails), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResearchDetails_MetaData), NewProp_ResearchDetails_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HealButton = { "HealButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, HealButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HealButton_MetaData), NewProp_HealButton_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PartyCards_Inner = { "PartyCards", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonDigiLabCardView, METADATA_PARAMS(0, nullptr) }; // 0a6120d5402cdca240c81ea0c97c60276eeb8ca1
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PartyCards = { "PartyCards", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTDigiLabWidget, PartyCards), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyCards_MetaData), NewProp_PartyCards_MetaData) }; // 0a6120d5402cdca240c81ea0c97c60276eeb8ca1
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartySummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CollectionSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecoveryStatus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HealCaption,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResearchSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResearchDetails,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HealButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyCards_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyCards,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTDigiLabWidget Property Definitions *************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTDigiLabWidget_StaticRegisterNativesUDigimonVenomNXTDigiLabWidget()
{
	UClass* Class = UDigimonVenomNXTDigiLabWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTDigiLabWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTDigiLabWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.InnerSingleton,
				UDigimonVenomNXTDigiLabWidget_StaticRegisterNativesUDigimonVenomNXTDigiLabWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTDigiLabWidget::UDigimonVenomNXTDigiLabWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTDigiLabWidget);
UDigimonVenomNXTDigiLabWidget::~UDigimonVenomNXTDigiLabWidget() {}
// ********** End Class UDigimonVenomNXTDigiLabWidget **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDigiLabWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonDigiLabCardView, Z_Construct_UScriptStruct_FDigimonDigiLabCardView_Statics::NewStructOps, TEXT("DigimonDigiLabCardView"),&Z_Registration_Info_UScriptStruct_FDigimonDigiLabCardView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonDigiLabCardView), 174137557U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget, TEXT("UDigimonVenomNXTDigiLabWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTDigiLabWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTDigiLabWidget), 1187363420U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTDigiLabWidget_h__Script_DigimonVenomNXTRuntime_f40b8a6956ba7c8243b9b5aed75b568ea10daf0f{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
