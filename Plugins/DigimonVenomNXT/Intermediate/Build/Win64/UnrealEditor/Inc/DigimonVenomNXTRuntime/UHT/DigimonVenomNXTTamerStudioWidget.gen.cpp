// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTTamerStudioWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTTamerStudioWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UImage(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_USizeBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUniformGridPanel(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTamerStudioCard(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonTamerStudioCard *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonTamerStudioCard_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonTamerStudioCard>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonTamerStudioCard); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Select_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NameText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonTamerStudioCard constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Select;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Bounds;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NameText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StateText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonTamerStudioCard constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonTamerStudioCard>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonTamerStudioCard Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Select = { "Select", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTamerStudioCard, Select), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Select_MetaData), NewProp_Select_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTamerStudioCard, Bounds), Z_Construct_UClass_USizeBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTamerStudioCard, Portrait), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NameText = { "NameText", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTamerStudioCard, NameText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NameText_MetaData), NewProp_NameText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StateText = { "StateText", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTamerStudioCard, StateText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateText_MetaData), NewProp_StateText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Select,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NameText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StateText,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonTamerStudioCard Property Definitions ************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonTamerStudioCard",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonTamerStudioCard>(),
	alignof(FDigimonTamerStudioCard),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonTamerStudioCard(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonTamerStudioCard, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonTamerStudioCard"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonTamerStudioCard *********************************************

// ********** Begin Class UDigimonVenomNXTTamerStudioWidget Function HandleAction ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTTamerStudioWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerStudioWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerStudioWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTTamerStudioWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTTamerStudioWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTamerStudioWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTamerStudioWidget Function HandleAction ********************

// ********** Begin Class UDigimonVenomNXTTamerStudioWidget Function HandleSearchChanged ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleSearchChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTTamerStudioWidget_eventHandleSearchChanged_Parms
	{
		FText InText;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleSearchChanged constinit property declarations *******************
	static const UECodeGen_Private::FTextPropertyParams NewProp_InText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleSearchChanged constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleSearchChanged Property Definitions ******************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_InText = { "InText", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerStudioWidget_eventHandleSearchChanged_Parms, InText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InText_MetaData), NewProp_InText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InText,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleSearchChanged Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget, nullptr, "HandleSearchChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTTamerStudioWidget_eventHandleSearchChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTTamerStudioWidget_eventHandleSearchChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleSearchChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTamerStudioWidget::execHandleSearchChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_InText);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleSearchChanged(Z_Param_Out_InText);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTamerStudioWidget Function HandleSearchChanged *************

// ********** Begin Class UDigimonVenomNXTTamerStudioWidget ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Account cosmetics: twelve retained roster cards and one real directional preview. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTTamerStudioWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Account cosmetics: twelve retained roster cards and one real directional preview." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SearchBox_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Preview_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreviewName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreviewDescription_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FacingLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreviewArtHint_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResultLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmptyLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApplyButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreviousButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NextButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Grid_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cards_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerStudioWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTTamerStudioWidget constinit property declarations ********
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SearchBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Preview;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PreviewName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PreviewDescription;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FacingLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PreviewArtHint;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatusLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResultLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EmptyLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PageLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ApplyButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WalkButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PreviousButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NextButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Grid;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DirectionButtons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DirectionButtons;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Cards_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Cards;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTTamerStudioWidget constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTTamerStudioWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleSearchChanged"), .Pointer = &UDigimonVenomNXTTamerStudioWidget::execHandleSearchChanged },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleAction, "HandleAction" }, // 1b5f74e97869992f8396f77937f690654ecb0a15
		{ &Z_Construct_UFunction_UDigimonVenomNXTTamerStudioWidget_HandleSearchChanged, "HandleSearchChanged" }, // d89eb9e99791039e8cc3ae6213784a1c36986c25
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTTamerStudioWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTTamerStudioWidget Property Definitions *******************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, Root), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SearchBox = { "SearchBox", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, SearchBox), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SearchBox_MetaData), NewProp_SearchBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Preview = { "Preview", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, Preview), Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Preview_MetaData), NewProp_Preview_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PreviewName = { "PreviewName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, PreviewName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreviewName_MetaData), NewProp_PreviewName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PreviewDescription = { "PreviewDescription", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, PreviewDescription), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreviewDescription_MetaData), NewProp_PreviewDescription_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CurrentLabel = { "CurrentLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, CurrentLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentLabel_MetaData), NewProp_CurrentLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FacingLabel = { "FacingLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, FacingLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FacingLabel_MetaData), NewProp_FacingLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PreviewArtHint = { "PreviewArtHint", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, PreviewArtHint), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreviewArtHint_MetaData), NewProp_PreviewArtHint_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StatusLabel = { "StatusLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, StatusLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusLabel_MetaData), NewProp_StatusLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResultLabel = { "ResultLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, ResultLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResultLabel_MetaData), NewProp_ResultLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EmptyLabel = { "EmptyLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, EmptyLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmptyLabel_MetaData), NewProp_EmptyLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PageLabel = { "PageLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, PageLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageLabel_MetaData), NewProp_PageLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ApplyButton = { "ApplyButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, ApplyButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApplyButton_MetaData), NewProp_ApplyButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_WalkButton = { "WalkButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, WalkButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkButton_MetaData), NewProp_WalkButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PreviousButton = { "PreviousButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, PreviousButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreviousButton_MetaData), NewProp_PreviousButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NextButton = { "NextButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, NextButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NextButton_MetaData), NewProp_NextButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Grid = { "Grid", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, Grid), Z_Construct_UClass_UUniformGridPanel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Grid_MetaData), NewProp_Grid_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DirectionButtons_Inner = { "DirectionButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_DirectionButtons = { "DirectionButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, DirectionButtons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionButtons_MetaData), NewProp_DirectionButtons_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Cards_Inner = { "Cards", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonTamerStudioCard, METADATA_PARAMS(0, nullptr) }; // df0baa03aa778d95e11b3beaa92e13dfd9da7d92
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Cards = { "Cards", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerStudioWidget, Cards), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cards_MetaData), NewProp_Cards_MetaData) }; // df0baa03aa778d95e11b3beaa92e13dfd9da7d92
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SearchBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Preview,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PreviewName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PreviewDescription,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FacingLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PreviewArtHint,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StatusLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResultLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmptyLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ApplyButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WalkButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PreviousButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NextButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Grid,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectionButtons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectionButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cards_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cards,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTTamerStudioWidget Property Definitions *********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget,
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
static void UDigimonVenomNXTTamerStudioWidget_StaticRegisterNativesUDigimonVenomNXTTamerStudioWidget()
{
	UClass* Class = UDigimonVenomNXTTamerStudioWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTTamerStudioWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTTamerStudioWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.InnerSingleton,
				UDigimonVenomNXTTamerStudioWidget_StaticRegisterNativesUDigimonVenomNXTTamerStudioWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTTamerStudioWidget::UDigimonVenomNXTTamerStudioWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTTamerStudioWidget);
UDigimonVenomNXTTamerStudioWidget::~UDigimonVenomNXTTamerStudioWidget() {}
// ********** End Class UDigimonVenomNXTTamerStudioWidget ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerStudioWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonTamerStudioCard, Z_Construct_UScriptStruct_FDigimonTamerStudioCard_Statics::NewStructOps, TEXT("DigimonTamerStudioCard"),&Z_Registration_Info_UScriptStruct_FDigimonTamerStudioCard, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonTamerStudioCard), 3742083587U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget, TEXT("UDigimonVenomNXTTamerStudioWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTTamerStudioWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTTamerStudioWidget), 4254806105U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerStudioWidget_h__Script_DigimonVenomNXTRuntime_ac359bbab9dc8c53e851fc707cefeaf6217e65bf{
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
