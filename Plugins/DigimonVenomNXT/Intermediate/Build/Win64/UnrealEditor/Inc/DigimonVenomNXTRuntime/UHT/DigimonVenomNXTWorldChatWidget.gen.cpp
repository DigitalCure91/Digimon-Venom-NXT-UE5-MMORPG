// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTWorldChatWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTWorldChatWidget() {}

// ********** Begin Cross Module References ********************************************************
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ETextCommit(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UButton(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UScrollBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_USizeBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Function HandleScrolled ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleScrolled_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldChatWidget_eventHandleScrolled_Parms
	{
		float Offset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleScrolled constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Offset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleScrolled constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleScrolled Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldChatWidget_eventHandleScrolled_Parms, Offset), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Offset,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleScrolled Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, nullptr, "HandleScrolled", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleScrolled_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleScrolled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleScrolled(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldChatWidget::execHandleScrolled)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Offset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleScrolled(Z_Param_Offset);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldChatWidget Function HandleScrolled ********************

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Function HandleSend **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleSend_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleSend constinit property declarations ****************************
// ********** End Function HandleSend constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, nullptr, "HandleSend", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleSend(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldChatWidget::execHandleSend)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleSend();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldChatWidget Function HandleSend ************************

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Function HandleTextChanged ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldChatWidget_eventHandleTextChanged_Parms
	{
		FText Text;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleTextChanged constinit property declarations *********************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleTextChanged constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleTextChanged Property Definitions ********************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldChatWidget_eventHandleTextChanged_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleTextChanged Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, nullptr, "HandleTextChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleTextChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleTextChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldChatWidget::execHandleTextChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleTextChanged(Z_Param_Out_Text);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldChatWidget Function HandleTextChanged *****************

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Function HandleTextCommitted *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextCommitted_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldChatWidget_eventHandleTextCommitted_Parms
	{
		FText Text;
		TEnumAsByte<ETextCommit::Type> CommitMethod;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleTextCommitted constinit property declarations *******************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitMethod;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleTextCommitted constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleTextCommitted Property Definitions ******************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldChatWidget_eventHandleTextCommitted_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_CommitMethod = { "CommitMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldChatWidget_eventHandleTextCommitted_Parms, CommitMethod), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 8323d5849e62ec5be16727bbd18b698ac3ecdec4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommitMethod,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleTextCommitted Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, nullptr, "HandleTextCommitted", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleTextCommitted_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldChatWidget_eventHandleTextCommitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextCommitted(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldChatWidget::execHandleTextCommitted)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitMethod);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleTextCommitted(Z_Param_Out_Text,ETextCommit::Type(Z_Param_CommitMethod));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldChatWidget Function HandleTextCommitted ***************

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Function HandleUnread ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleUnread_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleUnread constinit property declarations **************************
// ********** End Function HandleUnread constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, nullptr, "HandleUnread", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleUnread(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldChatWidget::execHandleUnread)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleUnread();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldChatWidget Function HandleUnread **********************

// ********** Begin Class UDigimonVenomNXTWorldChatWidget ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Retained native WORLD channel, shared by the habitat HUD and the field menu. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTWorldChatWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retained native WORLD channel, shared by the habitat HUD and the field menu." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoryScroll_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistorySize_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SendButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SendLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnreadButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnreadLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Counter_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Help_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmptyLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorldChatWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTWorldChatWidget constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoryScroll;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MessageRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistorySize;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MessageInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SendButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SendLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UnreadButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UnreadLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Counter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Help;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EmptyLabel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTWorldChatWidget constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleScrolled"), .Pointer = &UDigimonVenomNXTWorldChatWidget::execHandleScrolled },
		{ .NameUTF8 = UTF8TEXT("HandleSend"), .Pointer = &UDigimonVenomNXTWorldChatWidget::execHandleSend },
		{ .NameUTF8 = UTF8TEXT("HandleTextChanged"), .Pointer = &UDigimonVenomNXTWorldChatWidget::execHandleTextChanged },
		{ .NameUTF8 = UTF8TEXT("HandleTextCommitted"), .Pointer = &UDigimonVenomNXTWorldChatWidget::execHandleTextCommitted },
		{ .NameUTF8 = UTF8TEXT("HandleUnread"), .Pointer = &UDigimonVenomNXTWorldChatWidget::execHandleUnread },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleScrolled, "HandleScrolled" }, // 895e4797b38352310e5f76dfae5020ef351b1657
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleSend, "HandleSend" }, // 0128fc21ec36d4a252599ff0724cd5e2a68f7a63
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextChanged, "HandleTextChanged" }, // 53ec0767b714825931cf9aa6c3d5008736d0d816
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleTextCommitted, "HandleTextCommitted" }, // 3a3abed4257e0374dbd0deb40e92d29089ea1c67
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldChatWidget_HandleUnread, "HandleUnread" }, // 53ef2fef46956c3f436436f894d3b7d86272a4bf
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTWorldChatWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTWorldChatWidget Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoryScroll = { "HistoryScroll", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, HistoryScroll), Z_Construct_UClass_UScrollBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoryScroll_MetaData), NewProp_HistoryScroll_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MessageRows = { "MessageRows", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, MessageRows), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageRows_MetaData), NewProp_MessageRows_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistorySize = { "HistorySize", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, HistorySize), Z_Construct_UClass_USizeBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistorySize_MetaData), NewProp_HistorySize_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MessageInput = { "MessageInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, MessageInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageInput_MetaData), NewProp_MessageInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SendButton = { "SendButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, SendButton), Z_Construct_UClass_UButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SendButton_MetaData), NewProp_SendButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SendLabel = { "SendLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, SendLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SendLabel_MetaData), NewProp_SendLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UnreadButton = { "UnreadButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, UnreadButton), Z_Construct_UClass_UButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnreadButton_MetaData), NewProp_UnreadButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UnreadLabel = { "UnreadLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, UnreadLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnreadLabel_MetaData), NewProp_UnreadLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Counter = { "Counter", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, Counter), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Counter_MetaData), NewProp_Counter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Help = { "Help", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, Help), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Help_MetaData), NewProp_Help_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EmptyLabel = { "EmptyLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTWorldChatWidget, EmptyLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmptyLabel_MetaData), NewProp_EmptyLabel_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoryScroll,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MessageRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistorySize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MessageInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SendButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SendLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnreadButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnreadLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Counter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Help,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmptyLabel,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTWorldChatWidget Property Definitions ***********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget,
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
static void UDigimonVenomNXTWorldChatWidget_StaticRegisterNativesUDigimonVenomNXTWorldChatWidget()
{
	UClass* Class = UDigimonVenomNXTWorldChatWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTWorldChatWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTWorldChatWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.InnerSingleton,
				UDigimonVenomNXTWorldChatWidget_StaticRegisterNativesUDigimonVenomNXTWorldChatWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTWorldChatWidget::UDigimonVenomNXTWorldChatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTWorldChatWidget);
UDigimonVenomNXTWorldChatWidget::~UDigimonVenomNXTWorldChatWidget() {}
// ********** End Class UDigimonVenomNXTWorldChatWidget ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTWorldChatWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, TEXT("UDigimonVenomNXTWorldChatWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTWorldChatWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTWorldChatWidget), 1356313377U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTWorldChatWidget_h__Script_DigimonVenomNXTRuntime_9a681e4b0698d093548973ef6d85a60b6c49ffbc{
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
