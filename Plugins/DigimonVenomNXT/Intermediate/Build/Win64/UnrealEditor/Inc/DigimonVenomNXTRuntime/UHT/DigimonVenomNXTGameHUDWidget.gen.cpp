// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTGameHUDWidget() {}

// ********** Begin Cross Module References ********************************************************
COMMONUI_API UClass* Z_Construct_UClass_UCommonActivatableWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UScrollBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_USizeBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUniformGridPanel(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonChatMessage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRelayProgress(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonArchivePage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTChroniclesWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTCommunityWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDigiDexWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFarmWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFieldPartyWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTGhostLineWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartyWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTRelayWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSeasonWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function AppendChat ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_AppendChat_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventAppendChat_Parms
	{
		FDigimonChatMessage Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AppendChat constinit property declarations ****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AppendChat constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AppendChat Property Definitions ***************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventAppendChat_Parms, Message), Z_Construct_UScriptStruct_FDigimonChatMessage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AppendChat Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "AppendChat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventAppendChat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventAppendChat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_AppendChat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execAppendChat)
{
	P_GET_STRUCT_REF(FDigimonChatMessage,Z_Param_Out_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AppendChat(Z_Param_Out_Message);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function AppendChat **************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ApplyRivalActivityPage ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplyRivalActivityPage_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventApplyRivalActivityPage_Parms
	{
		FDigimonAIRivalActivityPage Page;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Owner-only, bounded server response; clients never read the authority's rival save. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Owner-only, bounded server response; clients never read the authority's rival save." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Page_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyRivalActivityPage constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Page;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyRivalActivityPage constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyRivalActivityPage Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventApplyRivalActivityPage_Parms, Page), Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Page_MetaData), NewProp_Page_MetaData) }; // 8fb19c9299962509f91282c6ddf27a520cdb2f77
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ApplyRivalActivityPage Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ApplyRivalActivityPage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventApplyRivalActivityPage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventApplyRivalActivityPage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplyRivalActivityPage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execApplyRivalActivityPage)
{
	P_GET_STRUCT_REF(FDigimonAIRivalActivityPage,Z_Param_Out_Page);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyRivalActivityPage(Z_Param_Out_Page);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ApplyRivalActivityPage **************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ApplySeasonArchivePage ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplySeasonArchivePage_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventApplySeasonArchivePage_Parms
	{
		FDigimonSeasonArchivePage Page;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Page_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplySeasonArchivePage constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Page;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplySeasonArchivePage constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplySeasonArchivePage Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventApplySeasonArchivePage_Parms, Page), Z_Construct_UScriptStruct_FDigimonSeasonArchivePage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Page_MetaData), NewProp_Page_MetaData) }; // 80c6bd44f1ff8717382adef8167abbcfb94ffd23
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ApplySeasonArchivePage Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ApplySeasonArchivePage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventApplySeasonArchivePage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventApplySeasonArchivePage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplySeasonArchivePage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execApplySeasonArchivePage)
{
	P_GET_STRUCT_REF(FDigimonSeasonArchivePage,Z_Param_Out_Page);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplySeasonArchivePage(Z_Param_Out_Page);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ApplySeasonArchivePage **************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function CloseRelayDialogue ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CloseRelayDialogue_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CloseRelayDialogue constinit property declarations ********************
// ********** End Function CloseRelayDialogue constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "CloseRelayDialogue", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CloseRelayDialogue(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execCloseRelayDialogue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CloseRelayDialogue();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function CloseRelayDialogue ******************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function CommitAudioVolumes ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CommitAudioVolumes_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CommitAudioVolumes constinit property declarations ********************
// ********** End Function CommitAudioVolumes constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "CommitAudioVolumes", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CommitAudioVolumes(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execCommitAudioVolumes)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CommitAudioVolumes();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function CommitAudioVolumes ******************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleAction **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleAction ************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleEffectsVolume ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleEffectsVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventHandleEffectsVolume_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleEffectsVolume constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleEffectsVolume constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleEffectsVolume Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleEffectsVolume_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleEffectsVolume Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleEffectsVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleEffectsVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleEffectsVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleEffectsVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleEffectsVolume)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleEffectsVolume(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleEffectsVolume *****************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleMasterVolume ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMasterVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventHandleMasterVolume_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleMasterVolume constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleMasterVolume constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleMasterVolume Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleMasterVolume_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleMasterVolume Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleMasterVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleMasterVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleMasterVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMasterVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleMasterVolume)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMasterVolume(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleMasterVolume ******************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleMusicVolume *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMusicVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventHandleMusicVolume_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleMusicVolume constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleMusicVolume constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleMusicVolume Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleMusicVolume_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleMusicVolume Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleMusicVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleMusicVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleMusicVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMusicVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleMusicVolume)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMusicVolume(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleMusicVolume *******************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleProfileChanged **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleProfileChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleProfileChanged constinit property declarations ******************
// ********** End Function HandleProfileChanged constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleProfileChanged", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleProfileChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleProfileChanged)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleProfileChanged();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleProfileChanged ****************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function HandleUIVolume ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleUIVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventHandleUIVolume_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleUIVolume constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleUIVolume constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleUIVolume Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventHandleUIVolume_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleUIVolume Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "HandleUIVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleUIVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventHandleUIVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleUIVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execHandleUIVolume)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleUIVolume(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function HandleUIVolume **********************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function IsCompactHUDVisible ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsCompactHUDVisible_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventIsCompactHUDVisible_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsCompactHUDVisible constinit property declarations *******************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameHUDWidget_eventIsCompactHUDVisible_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsCompactHUDVisible constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsCompactHUDVisible Property Definitions ******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameHUDWidget_eventIsCompactHUDVisible_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsCompactHUDVisible Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "IsCompactHUDVisible", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsCompactHUDVisible_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsCompactHUDVisible_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsCompactHUDVisible(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execIsCompactHUDVisible)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsCompactHUDVisible();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function IsCompactHUDVisible *****************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function IsMenuOpen ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsMenuOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventIsMenuOpen_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsMenuOpen constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameHUDWidget_eventIsMenuOpen_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsMenuOpen constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsMenuOpen Property Definitions ***************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameHUDWidget_eventIsMenuOpen_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsMenuOpen Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "IsMenuOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsMenuOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsMenuOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsMenuOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execIsMenuOpen)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsMenuOpen();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function IsMenuOpen **************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function IsRelayDialogueOpen ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsRelayDialogueOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventIsRelayDialogueOpen_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsRelayDialogueOpen constinit property declarations *******************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameHUDWidget_eventIsRelayDialogueOpen_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRelayDialogueOpen constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRelayDialogueOpen Property Definitions ******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameHUDWidget_eventIsRelayDialogueOpen_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsRelayDialogueOpen Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "IsRelayDialogueOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsRelayDialogueOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventIsRelayDialogueOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsRelayDialogueOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execIsRelayDialogueOpen)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRelayDialogueOpen();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function IsRelayDialogueOpen *****************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function OpenDigiLab ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_OpenDigiLab_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** In-place recovery overlay; leaves the current map, pawn position and private instance intact. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "In-place recovery overlay; leaves the current map, pawn position and private instance intact." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OpenDigiLab constinit property declarations ***************************
// ********** End Function OpenDigiLab constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "OpenDigiLab", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_OpenDigiLab(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execOpenDigiLab)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenDigiLab();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function OpenDigiLab *************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function RefreshLivePages ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_RefreshLivePages_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshLivePages constinit property declarations **********************
// ********** End Function RefreshLivePages constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "RefreshLivePages", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_RefreshLivePages(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execRefreshLivePages)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshLivePages();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function RefreshLivePages ********************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function SetCompactHUDVisible **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetCompactHUDVisible_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventSetCompactHUDVisible_Parms
	{
		bool bVisible;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetCompactHUDVisible constinit property declarations ******************
	static void NewProp_bVisible_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameHUDWidget_eventSetCompactHUDVisible_Parms*)Obj)->bVisible = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVisible;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetCompactHUDVisible constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetCompactHUDVisible Property Definitions *****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bVisible = { "bVisible", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameHUDWidget_eventSetCompactHUDVisible_Parms), &UHT_STATICS::NewProp_bVisible_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bVisible,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetCompactHUDVisible Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "SetCompactHUDVisible", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventSetCompactHUDVisible_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventSetCompactHUDVisible_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetCompactHUDVisible(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execSetCompactHUDVisible)
{
	P_GET_UBOOL(Z_Param_bVisible);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetCompactHUDVisible(Z_Param_bVisible);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function SetCompactHUDVisible ****************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function SetMenuOpen ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetMenuOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventSetMenuOpen_Parms
	{
		bool bOpen;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Field exploration owns the screen by default. M/Tab opens this menu; Escape closes it. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Field exploration owns the screen by default. M/Tab opens this menu; Escape closes it." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetMenuOpen constinit property declarations ***************************
	static void NewProp_bOpen_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameHUDWidget_eventSetMenuOpen_Parms*)Obj)->bOpen = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpen;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetMenuOpen constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetMenuOpen Property Definitions **************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOpen = { "bOpen", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameHUDWidget_eventSetMenuOpen_Parms), &UHT_STATICS::NewProp_bOpen_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOpen,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetMenuOpen Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "SetMenuOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventSetMenuOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventSetMenuOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetMenuOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execSetMenuOpen)
{
	P_GET_UBOOL(Z_Param_bOpen);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMenuOpen(Z_Param_bOpen);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function SetMenuOpen *************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ShowPage **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowPage_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventShowPage_Parms
	{
		FString PageName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowPage constinit property declarations ******************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_PageName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ShowPage constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ShowPage Property Definitions *****************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_PageName = { "PageName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowPage_Parms, PageName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageName_MetaData), NewProp_PageName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageName,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ShowPage Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ShowPage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowPage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowPage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowPage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execShowPage)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PageName);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowPage(Z_Param_PageName);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ShowPage ****************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ShowRelayDialogue *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowRelayDialogue_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms
	{
		FName NPCId;
		FString Dialogue;
		FDigimonRelayProgress ConfirmedProgress;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Opened only by a proximity-checked server interaction with a campaign NPC. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Opened only by a proximity-checked server interaction with a campaign NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dialogue_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConfirmedProgress_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowRelayDialogue constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Dialogue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ConfirmedProgress;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ShowRelayDialogue constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ShowRelayDialogue Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Dialogue = { "Dialogue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms, Dialogue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dialogue_MetaData), NewProp_Dialogue_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ConfirmedProgress = { "ConfirmedProgress", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms, ConfirmedProgress), Z_Construct_UScriptStruct_FDigimonRelayProgress, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConfirmedProgress_MetaData), NewProp_ConfirmedProgress_MetaData) }; // 6c57e16f81b8e83a6df3b845191f9c7a82333f84
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Dialogue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ConfirmedProgress,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ShowRelayDialogue Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ShowRelayDialogue", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowRelayDialogue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowRelayDialogue(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execShowRelayDialogue)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Dialogue);
	P_GET_STRUCT_REF(FDigimonRelayProgress,Z_Param_Out_ConfirmedProgress);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowRelayDialogue(Z_Param_NPCId,Z_Param_Dialogue,Z_Param_Out_ConfirmedProgress);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ShowRelayDialogue *******************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ShowToast *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowToast_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameHUDWidget_eventShowToast_Parms
	{
		FString Title;
		FString Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Title_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowToast constinit property declarations *****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Title;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ShowToast constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ShowToast Property Definitions ****************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Title = { "Title", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowToast_Parms, Title), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Title_MetaData), NewProp_Title_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameHUDWidget_eventShowToast_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Title,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ShowToast Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ShowToast", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowToast_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameHUDWidget_eventShowToast_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowToast(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execShowToast)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Title);
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowToast(Z_Param_Title,Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ShowToast ***************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Function ToggleMenu ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ToggleMenu_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|HUD" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleMenu constinit property declarations ****************************
// ********** End Function ToggleMenu constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, nullptr, "ToggleMenu", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ToggleMenu(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTGameHUDWidget::execToggleMenu)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleMenu();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTGameHUDWidget Function ToggleMenu **************************

// ********** Begin Class UDigimonVenomNXTGameHUDWidget ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Native in-world UI shell. Provides usable pages for Atlas, party/collection, DigiLab,\n * DigiFarm, shop, Season, Ranked, AI rival stats and WORLD chat. Blueprint subclasses can restyle/extend it.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTGameHUDWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native in-world UI shell. Provides usable pages for Atlas, party/collection, DigiLab,\nDigiFarm, shop, Season, Ranked, AI rival stats and WORLD chat. Blueprint subclasses can restyle/extend it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalSnapshot_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageScrolls_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NavButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalSummaryText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalCountdownText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalTotalsText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalPageText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalPreviousButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalNextButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalRowsBox_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalMetricValues_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalRowTexts_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalChallengeButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedCountdownText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedEnergyText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CompactHUDRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CompactLeadImage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AudioVolumeLabels_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeaderIdentity_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeaderEconomy_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeaderRubies_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldParty_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldPartyFrame_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldWorldChat_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MenuWorldChat_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldWorldChatFrame_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeaderWorld_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldHintText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ToastText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayObjectiveRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayCampaignLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayObjectiveTitle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayObjectiveText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayInteractionText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayDialogueRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayDialogueContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayJournal_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChroniclesJournal_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GhostLineJournal_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MenuRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageSwitcher_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverviewContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerStudio_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyPanel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollectionContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EvolutionLab_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiDexContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiDex_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LabContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiLab_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VideoSettings_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerConsole_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HostConsoleButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogoutButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogoutCancelButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogoutOverlay_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogoutMessage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MenuBodyFrame_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarmContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarmManager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarmWorldHUD_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShopContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StoryContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeasonCareer_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalsContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommunityPages_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StarterSearchInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AtlasGrid_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AtlasPageLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AtlasPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AtlasNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameHUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTGameHUDWidget constinit property declarations ************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RivalSnapshot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PageScrolls_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PageScrolls_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_PageScrolls;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NavButtons_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NavButtons_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_NavButtons;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalSummaryText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalCountdownText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalTotalsText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalPageText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalPreviousButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalNextButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalRowsBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalMetricValues_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RivalMetricValues;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalRowTexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RivalRowTexts;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalChallengeButtons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RivalChallengeButtons;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RankedCountdownText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RankedEnergyText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CompactHUDRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CompactLeadImage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AudioVolumeLabels_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AudioVolumeLabels;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeaderIdentity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeaderEconomy;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeaderRubies;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FieldParty;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FieldPartyFrame;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FieldWorldChat;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MenuWorldChat;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FieldWorldChatFrame;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeaderWorld;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FieldHintText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ToastText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayObjectiveRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayCampaignLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayObjectiveTitle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayObjectiveText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayInteractionText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayDialogueRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayDialogueContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayJournal;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChroniclesJournal;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GhostLineJournal;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MenuRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PageSwitcher;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverviewContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TamerContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TamerStudio;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartyContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartyPanel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollectionContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EvolutionLab;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DigiDexContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DigiDex;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LabContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DigiLab;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VideoSettings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ServerConsole;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HostConsoleButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogoutButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogoutCancelButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogoutOverlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogoutMessage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MenuBodyFrame;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FarmContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FarmManager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FarmWorldHUD;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ShopContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StoryContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SeasonContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SeasonCareer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RankedContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalsContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CommunityPages_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CommunityPages_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_CommunityPages;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StarterSearchInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AtlasGrid;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AtlasPageLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AtlasPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AtlasNext;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTGameHUDWidget constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AppendChat"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execAppendChat },
		{ .NameUTF8 = UTF8TEXT("ApplyRivalActivityPage"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execApplyRivalActivityPage },
		{ .NameUTF8 = UTF8TEXT("ApplySeasonArchivePage"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execApplySeasonArchivePage },
		{ .NameUTF8 = UTF8TEXT("CloseRelayDialogue"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execCloseRelayDialogue },
		{ .NameUTF8 = UTF8TEXT("CommitAudioVolumes"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execCommitAudioVolumes },
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleEffectsVolume"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleEffectsVolume },
		{ .NameUTF8 = UTF8TEXT("HandleMasterVolume"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleMasterVolume },
		{ .NameUTF8 = UTF8TEXT("HandleMusicVolume"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleMusicVolume },
		{ .NameUTF8 = UTF8TEXT("HandleProfileChanged"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleProfileChanged },
		{ .NameUTF8 = UTF8TEXT("HandleUIVolume"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execHandleUIVolume },
		{ .NameUTF8 = UTF8TEXT("IsCompactHUDVisible"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execIsCompactHUDVisible },
		{ .NameUTF8 = UTF8TEXT("IsMenuOpen"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execIsMenuOpen },
		{ .NameUTF8 = UTF8TEXT("IsRelayDialogueOpen"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execIsRelayDialogueOpen },
		{ .NameUTF8 = UTF8TEXT("OpenDigiLab"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execOpenDigiLab },
		{ .NameUTF8 = UTF8TEXT("RefreshLivePages"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execRefreshLivePages },
		{ .NameUTF8 = UTF8TEXT("SetCompactHUDVisible"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execSetCompactHUDVisible },
		{ .NameUTF8 = UTF8TEXT("SetMenuOpen"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execSetMenuOpen },
		{ .NameUTF8 = UTF8TEXT("ShowPage"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execShowPage },
		{ .NameUTF8 = UTF8TEXT("ShowRelayDialogue"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execShowRelayDialogue },
		{ .NameUTF8 = UTF8TEXT("ShowToast"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execShowToast },
		{ .NameUTF8 = UTF8TEXT("ToggleMenu"), .Pointer = &UDigimonVenomNXTGameHUDWidget::execToggleMenu },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_AppendChat, "AppendChat" }, // a7bac6d6b37c7751caddef03ef8151c2a39e9745
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplyRivalActivityPage, "ApplyRivalActivityPage" }, // 7049cd699ea60805e4667e502c5b2c19482b310c
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ApplySeasonArchivePage, "ApplySeasonArchivePage" }, // 5779aaf3d5844dfefb69f00fd3333f2ca72b6926
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CloseRelayDialogue, "CloseRelayDialogue" }, // 1df2e4e0e2d384f547f486317ef0c246f2a3b43a
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_CommitAudioVolumes, "CommitAudioVolumes" }, // 72b07e11f25dc0282c5fde435b3f3275b2fe13cb
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleAction, "HandleAction" }, // e1d17f1b6b22ef39a997a88c23a2bb8d4008ef26
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleEffectsVolume, "HandleEffectsVolume" }, // fe60bd9f1603a55453e4a3ebda9c917eabb7ad33
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMasterVolume, "HandleMasterVolume" }, // a836f5d5901905dec715ed79601bae0bfca70cbe
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleMusicVolume, "HandleMusicVolume" }, // 9326324e9e310cf58292663d5e4de4983d93c087
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleProfileChanged, "HandleProfileChanged" }, // 6a5f627e5f1f2b33a6a8c8e057e6764f7cc978b7
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_HandleUIVolume, "HandleUIVolume" }, // bd710d56b5c80443be35f84b393afe38ce3bf8b5
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsCompactHUDVisible, "IsCompactHUDVisible" }, // 32f0a0cf003593767ad5acd5335a9d6c5e93486a
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsMenuOpen, "IsMenuOpen" }, // 8f3c3e7635c49715716e17f5dedcb9333542092c
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_IsRelayDialogueOpen, "IsRelayDialogueOpen" }, // e10a8bb2fd1c5add0505488b8d8fc5d978edd59a
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_OpenDigiLab, "OpenDigiLab" }, // 2e511a27ea0827693c738b213012ed85f30801c9
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_RefreshLivePages, "RefreshLivePages" }, // 33e5efb736db157bddf575bce12a9f59eb1e7f19
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetCompactHUDVisible, "SetCompactHUDVisible" }, // 7de482632ac202f99e899d1fd39063638fa0c819
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_SetMenuOpen, "SetMenuOpen" }, // 4ed0f758a1e83e21286f8c43e0c714fc6a0e9fa0
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowPage, "ShowPage" }, // 601a03726792f345aa7f18c21524f53d7a7fd10d
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowRelayDialogue, "ShowRelayDialogue" }, // a873a77ef175b57a8034e8557e3e0c6bb0728d86
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ShowToast, "ShowToast" }, // 8f1710950293dd64f8eebf6551037bf3d20e5703
		{ &Z_Construct_UFunction_UDigimonVenomNXTGameHUDWidget_ToggleMenu, "ToggleMenu" }, // 61520aa7b00e1b4f7183829b8942ef96a3cc7b9c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTGameHUDWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTGameHUDWidget Property Definitions ***********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RivalSnapshot = { "RivalSnapshot", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalSnapshot), Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalSnapshot_MetaData), NewProp_RivalSnapshot_MetaData) }; // 8fb19c9299962509f91282c6ddf27a520cdb2f77
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PageScrolls_ValueProp = { "PageScrolls", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 1, Z_Construct_UClass_UScrollBox, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_PageScrolls_Key_KeyProp = { "PageScrolls_Key", nullptr, (EPropertyFlags)0x0100000000080008, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_PageScrolls = { "PageScrolls", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, PageScrolls), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageScrolls_MetaData), NewProp_PageScrolls_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NavButtons_ValueProp = { "NavButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 1, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_NavButtons_Key_KeyProp = { "NavButtons_Key", nullptr, (EPropertyFlags)0x0100000000080008, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_NavButtons = { "NavButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, NavButtons), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NavButtons_MetaData), NewProp_NavButtons_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalSummaryText = { "RivalSummaryText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalSummaryText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalSummaryText_MetaData), NewProp_RivalSummaryText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalCountdownText = { "RivalCountdownText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalCountdownText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalCountdownText_MetaData), NewProp_RivalCountdownText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalTotalsText = { "RivalTotalsText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalTotalsText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalTotalsText_MetaData), NewProp_RivalTotalsText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalPageText = { "RivalPageText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalPageText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalPageText_MetaData), NewProp_RivalPageText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalPreviousButton = { "RivalPreviousButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalPreviousButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalPreviousButton_MetaData), NewProp_RivalPreviousButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalNextButton = { "RivalNextButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalNextButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalNextButton_MetaData), NewProp_RivalNextButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalRowsBox = { "RivalRowsBox", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalRowsBox), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalRowsBox_MetaData), NewProp_RivalRowsBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalMetricValues_Inner = { "RivalMetricValues", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RivalMetricValues = { "RivalMetricValues", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalMetricValues), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalMetricValues_MetaData), NewProp_RivalMetricValues_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalRowTexts_Inner = { "RivalRowTexts", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RivalRowTexts = { "RivalRowTexts", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalRowTexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalRowTexts_MetaData), NewProp_RivalRowTexts_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalChallengeButtons_Inner = { "RivalChallengeButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RivalChallengeButtons = { "RivalChallengeButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalChallengeButtons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalChallengeButtons_MetaData), NewProp_RivalChallengeButtons_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RankedCountdownText = { "RankedCountdownText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RankedCountdownText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedCountdownText_MetaData), NewProp_RankedCountdownText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RankedEnergyText = { "RankedEnergyText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RankedEnergyText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedEnergyText_MetaData), NewProp_RankedEnergyText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CompactHUDRoot = { "CompactHUDRoot", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, CompactHUDRoot), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CompactHUDRoot_MetaData), NewProp_CompactHUDRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CompactLeadImage = { "CompactLeadImage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, CompactLeadImage), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CompactLeadImage_MetaData), NewProp_CompactLeadImage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AudioVolumeLabels_Inner = { "AudioVolumeLabels", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_AudioVolumeLabels = { "AudioVolumeLabels", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, AudioVolumeLabels), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AudioVolumeLabels_MetaData), NewProp_AudioVolumeLabels_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeaderIdentity = { "HeaderIdentity", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, HeaderIdentity), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeaderIdentity_MetaData), NewProp_HeaderIdentity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeaderEconomy = { "HeaderEconomy", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, HeaderEconomy), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeaderEconomy_MetaData), NewProp_HeaderEconomy_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeaderRubies = { "HeaderRubies", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, HeaderRubies), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeaderRubies_MetaData), NewProp_HeaderRubies_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FieldParty = { "FieldParty", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FieldParty), Z_Construct_UClass_UDigimonVenomNXTFieldPartyWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldParty_MetaData), NewProp_FieldParty_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FieldPartyFrame = { "FieldPartyFrame", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FieldPartyFrame), Z_Construct_UClass_UWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldPartyFrame_MetaData), NewProp_FieldPartyFrame_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FieldWorldChat = { "FieldWorldChat", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FieldWorldChat), Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldWorldChat_MetaData), NewProp_FieldWorldChat_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MenuWorldChat = { "MenuWorldChat", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, MenuWorldChat), Z_Construct_UClass_UDigimonVenomNXTWorldChatWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MenuWorldChat_MetaData), NewProp_MenuWorldChat_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FieldWorldChatFrame = { "FieldWorldChatFrame", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FieldWorldChatFrame), Z_Construct_UClass_USizeBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldWorldChatFrame_MetaData), NewProp_FieldWorldChatFrame_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeaderWorld = { "HeaderWorld", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, HeaderWorld), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeaderWorld_MetaData), NewProp_HeaderWorld_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FieldHintText = { "FieldHintText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FieldHintText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldHintText_MetaData), NewProp_FieldHintText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ToastText = { "ToastText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, ToastText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ToastText_MetaData), NewProp_ToastText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayObjectiveRoot = { "RelayObjectiveRoot", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayObjectiveRoot), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayObjectiveRoot_MetaData), NewProp_RelayObjectiveRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayCampaignLabel = { "RelayCampaignLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayCampaignLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayCampaignLabel_MetaData), NewProp_RelayCampaignLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayObjectiveTitle = { "RelayObjectiveTitle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayObjectiveTitle), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayObjectiveTitle_MetaData), NewProp_RelayObjectiveTitle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayObjectiveText = { "RelayObjectiveText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayObjectiveText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayObjectiveText_MetaData), NewProp_RelayObjectiveText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayInteractionText = { "RelayInteractionText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayInteractionText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayInteractionText_MetaData), NewProp_RelayInteractionText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayDialogueRoot = { "RelayDialogueRoot", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayDialogueRoot), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayDialogueRoot_MetaData), NewProp_RelayDialogueRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayDialogueContent = { "RelayDialogueContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayDialogueContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayDialogueContent_MetaData), NewProp_RelayDialogueContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayJournal = { "RelayJournal", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RelayJournal), Z_Construct_UClass_UDigimonVenomNXTRelayWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayJournal_MetaData), NewProp_RelayJournal_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChroniclesJournal = { "ChroniclesJournal", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, ChroniclesJournal), Z_Construct_UClass_UDigimonVenomNXTChroniclesWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChroniclesJournal_MetaData), NewProp_ChroniclesJournal_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_GhostLineJournal = { "GhostLineJournal", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, GhostLineJournal), Z_Construct_UClass_UDigimonVenomNXTGhostLineWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GhostLineJournal_MetaData), NewProp_GhostLineJournal_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MenuRoot = { "MenuRoot", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, MenuRoot), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MenuRoot_MetaData), NewProp_MenuRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PageSwitcher = { "PageSwitcher", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, PageSwitcher), Z_Construct_UClass_UWidgetSwitcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageSwitcher_MetaData), NewProp_PageSwitcher_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OverviewContent = { "OverviewContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, OverviewContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverviewContent_MetaData), NewProp_OverviewContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TamerContent = { "TamerContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, TamerContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerContent_MetaData), NewProp_TamerContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TamerStudio = { "TamerStudio", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, TamerStudio), Z_Construct_UClass_UDigimonVenomNXTTamerStudioWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerStudio_MetaData), NewProp_TamerStudio_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartyContent = { "PartyContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, PartyContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyContent_MetaData), NewProp_PartyContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartyPanel = { "PartyPanel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, PartyPanel), Z_Construct_UClass_UDigimonVenomNXTPartyWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyPanel_MetaData), NewProp_PartyPanel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CollectionContent = { "CollectionContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, CollectionContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollectionContent_MetaData), NewProp_CollectionContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EvolutionLab = { "EvolutionLab", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, EvolutionLab), Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EvolutionLab_MetaData), NewProp_EvolutionLab_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DigiDexContent = { "DigiDexContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, DigiDexContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiDexContent_MetaData), NewProp_DigiDexContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DigiDex = { "DigiDex", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, DigiDex), Z_Construct_UClass_UDigimonVenomNXTDigiDexWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiDex_MetaData), NewProp_DigiDex_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LabContent = { "LabContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, LabContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LabContent_MetaData), NewProp_LabContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DigiLab = { "DigiLab", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, DigiLab), Z_Construct_UClass_UDigimonVenomNXTDigiLabWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiLab_MetaData), NewProp_DigiLab_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_VideoSettings = { "VideoSettings", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, VideoSettings), Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VideoSettings_MetaData), NewProp_VideoSettings_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ServerConsole = { "ServerConsole", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, ServerConsole), Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerConsole_MetaData), NewProp_ServerConsole_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HostConsoleButton = { "HostConsoleButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, HostConsoleButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HostConsoleButton_MetaData), NewProp_HostConsoleButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogoutButton = { "LogoutButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, LogoutButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogoutButton_MetaData), NewProp_LogoutButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogoutCancelButton = { "LogoutCancelButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, LogoutCancelButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogoutCancelButton_MetaData), NewProp_LogoutCancelButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogoutOverlay = { "LogoutOverlay", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, LogoutOverlay), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogoutOverlay_MetaData), NewProp_LogoutOverlay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogoutMessage = { "LogoutMessage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, LogoutMessage), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogoutMessage_MetaData), NewProp_LogoutMessage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MenuBodyFrame = { "MenuBodyFrame", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, MenuBodyFrame), Z_Construct_UClass_UWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MenuBodyFrame_MetaData), NewProp_MenuBodyFrame_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FarmContent = { "FarmContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FarmContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarmContent_MetaData), NewProp_FarmContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FarmManager = { "FarmManager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FarmManager), Z_Construct_UClass_UDigimonVenomNXTFarmWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarmManager_MetaData), NewProp_FarmManager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FarmWorldHUD = { "FarmWorldHUD", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, FarmWorldHUD), Z_Construct_UClass_UDigimonVenomNXTFarmWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarmWorldHUD_MetaData), NewProp_FarmWorldHUD_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ShopContent = { "ShopContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, ShopContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShopContent_MetaData), NewProp_ShopContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StoryContent = { "StoryContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, StoryContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StoryContent_MetaData), NewProp_StoryContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SeasonContent = { "SeasonContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, SeasonContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonContent_MetaData), NewProp_SeasonContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SeasonCareer = { "SeasonCareer", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, SeasonCareer), Z_Construct_UClass_UDigimonVenomNXTSeasonWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeasonCareer_MetaData), NewProp_SeasonCareer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RankedContent = { "RankedContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RankedContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedContent_MetaData), NewProp_RankedContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalsContent = { "RivalsContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, RivalsContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalsContent_MetaData), NewProp_RivalsContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CommunityPages_ValueProp = { "CommunityPages", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 1, Z_Construct_UClass_UDigimonVenomNXTCommunityWidget, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_CommunityPages_Key_KeyProp = { "CommunityPages_Key", nullptr, (EPropertyFlags)0x0100000000080008, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_CommunityPages = { "CommunityPages", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, CommunityPages), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommunityPages_MetaData), NewProp_CommunityPages_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StarterSearchInput = { "StarterSearchInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, StarterSearchInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StarterSearchInput_MetaData), NewProp_StarterSearchInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AtlasGrid = { "AtlasGrid", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, AtlasGrid), Z_Construct_UClass_UUniformGridPanel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AtlasGrid_MetaData), NewProp_AtlasGrid_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AtlasPageLabel = { "AtlasPageLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, AtlasPageLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AtlasPageLabel_MetaData), NewProp_AtlasPageLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AtlasPrevious = { "AtlasPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, AtlasPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AtlasPrevious_MetaData), NewProp_AtlasPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AtlasNext = { "AtlasNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTGameHUDWidget, AtlasNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AtlasNext_MetaData), NewProp_AtlasNext_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalSnapshot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageScrolls_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageScrolls_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageScrolls,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NavButtons_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NavButtons_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NavButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalSummaryText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalCountdownText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalTotalsText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalPageText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalPreviousButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalNextButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalRowsBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalMetricValues_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalMetricValues,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalRowTexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalRowTexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalChallengeButtons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalChallengeButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedCountdownText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedEnergyText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CompactHUDRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CompactLeadImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AudioVolumeLabels_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AudioVolumeLabels,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeaderIdentity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeaderEconomy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeaderRubies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldParty,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldPartyFrame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldWorldChat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MenuWorldChat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldWorldChatFrame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeaderWorld,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FieldHintText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ToastText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayObjectiveRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayCampaignLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayObjectiveTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayObjectiveText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayInteractionText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayDialogueRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayDialogueContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayJournal,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChroniclesJournal,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GhostLineJournal,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MenuRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageSwitcher,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OverviewContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerStudio,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyPanel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CollectionContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EvolutionLab,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiDexContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiDex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LabContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiLab,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VideoSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ServerConsole,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HostConsoleButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogoutButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogoutCancelButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogoutOverlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogoutMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MenuBodyFrame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FarmContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FarmManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FarmWorldHUD,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StoryContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeasonCareer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalsContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommunityPages_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommunityPages_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommunityPages,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StarterSearchInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AtlasGrid,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AtlasPageLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AtlasPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AtlasNext,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTGameHUDWidget Property Definitions *************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UCommonActivatableWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget,
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
static void UDigimonVenomNXTGameHUDWidget_StaticRegisterNativesUDigimonVenomNXTGameHUDWidget()
{
	UClass* Class = UDigimonVenomNXTGameHUDWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTGameHUDWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTGameHUDWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.InnerSingleton,
				UDigimonVenomNXTGameHUDWidget_StaticRegisterNativesUDigimonVenomNXTGameHUDWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTGameHUDWidget::UDigimonVenomNXTGameHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTGameHUDWidget);
UDigimonVenomNXTGameHUDWidget::~UDigimonVenomNXTGameHUDWidget() {}
// ********** End Class UDigimonVenomNXTGameHUDWidget **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, TEXT("UDigimonVenomNXTGameHUDWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTGameHUDWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTGameHUDWidget), 4243194589U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameHUDWidget_h__Script_DigimonVenomNXTRuntime_496409e528c7779070635ecf5ff4d2c5276b6600{
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
