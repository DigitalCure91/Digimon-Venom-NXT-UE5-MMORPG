// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTBattleWidget.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTBattleWidget() {}

// ********** Begin Cross Module References ********************************************************
COMMONUI_API UClass* Z_Construct_UClass_UCommonActivatableWidget(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UTexture2D(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UCanvasPanel(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UHorizontalBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UImage(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UOverlay(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UProgressBar(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UScrollBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattlePresentationEvent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleSlotVisual(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonBattleSlotVisual ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonBattleSlotVisual_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonBattleSlotVisual>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonBattleSlotVisual); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stable widget references: changing HP must never restart the partner's idle animation. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stable widget references: changing HP must never restart the partner's idle animation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Selection_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpriteHost_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Detail_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Affinity_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Element_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Marker_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HP_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SP_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonBattleSlotVisual constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Selection;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpriteHost;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Detail;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Affinity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Element;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Marker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HP;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SP;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonBattleSlotVisual constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonBattleSlotVisual>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonBattleSlotVisual Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Selection = { "Selection", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Selection), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Selection_MetaData), NewProp_Selection_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpriteHost = { "SpriteHost", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, SpriteHost), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpriteHost_MetaData), NewProp_SpriteHost_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Detail = { "Detail", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Detail), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Detail_MetaData), NewProp_Detail_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Affinity = { "Affinity", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Affinity), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Affinity_MetaData), NewProp_Affinity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Element = { "Element", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Element), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Element_MetaData), NewProp_Element_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Marker = { "Marker", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, Marker), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Marker_MetaData), NewProp_Marker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HP = { "HP", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, HP), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HP_MetaData), NewProp_HP_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SP = { "SP", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonBattleSlotVisual, SP), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SP_MetaData), NewProp_SP_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Selection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpriteHost,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Detail,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Affinity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Element,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Marker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SP,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonBattleSlotVisual Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonBattleSlotVisual",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonBattleSlotVisual>(),
	alignof(FDigimonBattleSlotVisual),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleSlotVisual(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonBattleSlotVisual, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonBattleSlotVisual"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonBattleSlotVisual ********************************************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function BP_OnBattleRefreshed ***************
struct DigimonVenomNXTBattleWidget_eventBP_OnBattleRefreshed_Parms
{
	FDigimonBattleState NewState;
};
static FName NAME_UDigimonVenomNXTBattleWidget_BP_OnBattleRefreshed = FName(TEXT("BP_OnBattleRefreshed"));
void UDigimonVenomNXTBattleWidget::BP_OnBattleRefreshed(FDigimonBattleState const& NewState)
{
	DigimonVenomNXTBattleWidget_eventBP_OnBattleRefreshed_Parms Parms;
	Parms.NewState=NewState;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTBattleWidget_BP_OnBattleRefreshed);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_BP_OnBattleRefreshed_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnBattleRefreshed constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnBattleRefreshed constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnBattleRefreshed Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventBP_OnBattleRefreshed_Parms, NewState), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewState_MetaData), NewProp_NewState_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnBattleRefreshed Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "BP_OnBattleRefreshed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTBattleWidget_eventBP_OnBattleRefreshed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08480800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTBattleWidget_eventBP_OnBattleRefreshed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_BP_OnBattleRefreshed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UDigimonVenomNXTBattleWidget Function BP_OnBattleRefreshed *****************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function GetBattle **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_GetBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleWidget_eventGetBattle_Parms
	{
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetBattle constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetBattle constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetBattle Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventGetBattle_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetBattle Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "GetBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleWidget_eventGetBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleWidget_eventGetBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_GetBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTBattleWidget::execGetBattle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->GetBattle();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTBattleWidget Function GetBattle ****************************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function HandleAction ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTBattleWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTBattleWidget Function HandleAction *************************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function HandleBattleStateChanged ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleBattleStateChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleWidget_eventHandleBattleStateChanged_Parms
	{
		FDigimonBattleState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleBattleStateChanged constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleBattleStateChanged constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleBattleStateChanged Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventHandleBattleStateChanged_Parms, NewState), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewState_MetaData), NewProp_NewState_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleBattleStateChanged Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "HandleBattleStateChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleWidget_eventHandleBattleStateChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleWidget_eventHandleBattleStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleBattleStateChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTBattleWidget::execHandleBattleStateChanged)
{
	P_GET_STRUCT_REF(FDigimonBattleState,Z_Param_Out_NewState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleBattleStateChanged(Z_Param_Out_NewState);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTBattleWidget Function HandleBattleStateChanged *************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function IsPresentationBusy *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_IsPresentationBusy_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleWidget_eventIsPresentationBusy_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsPresentationBusy constinit property declarations ********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleWidget_eventIsPresentationBusy_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsPresentationBusy constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsPresentationBusy Property Definitions *******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleWidget_eventIsPresentationBusy_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsPresentationBusy Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "IsPresentationBusy", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleWidget_eventIsPresentationBusy_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleWidget_eventIsPresentationBusy_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_IsPresentationBusy(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTBattleWidget::execIsPresentationBusy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsPresentationBusy();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTBattleWidget Function IsPresentationBusy *******************

// ********** Begin Class UDigimonVenomNXTBattleWidget Function SetBattle **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_SetBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleWidget_eventSetBattle_Parms
	{
		ADigimonVenomNXTBattleActor* InBattle;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetBattle constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InBattle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetBattle constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetBattle Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InBattle = { "InBattle", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleWidget_eventSetBattle_Parms, InBattle), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InBattle,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetBattle Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTBattleWidget, nullptr, "SetBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleWidget_eventSetBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleWidget_eventSetBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_SetBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTBattleWidget::execSetBattle)
{
	P_GET_OBJECT(ADigimonVenomNXTBattleActor,Z_Param_InBattle);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetBattle(Z_Param_InBattle);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTBattleWidget Function SetBattle ****************************

// ********** Begin Class UDigimonVenomNXTBattleWidget *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTBattleWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Shared battlefield for wild, story, tamer and automatic ranked matches.\n * Replicated combat remains authoritative; local snapshots only pace its presentation.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTBattleWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Shared battlefield for wild, story, tamer and automatic ranked matches.\nReplicated combat remains authoritative; local snapshots only pace its presentation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayState_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LatestState_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PendingPresentationEvents_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActivePresentationEvent_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PresentationOverlay_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArenaCanvas_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BattleTitle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BattleSubtitle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogScroll_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyCount_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchupPreview_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommandsBox_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResultPanel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResultHeading_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResultSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResultScroll_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActionTray_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActionTrayContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyBox_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactDetail_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactImage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactFrames_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeamAVisuals_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeamBVisuals_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyVisuals_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTBattleWidget constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DisplayState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LatestState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PendingPresentationEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PendingPresentationEvents;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ActivePresentationEvent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PresentationOverlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArenaCanvas;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleTitle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleSubtitle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TurnText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EventText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogScroll;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartyCount;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchupPreview;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CommandsBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResultPanel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResultHeading;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResultSummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResultScroll;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActionTray;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActionTrayContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartyBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ImpactText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ImpactDetail;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ImpactImage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ImpactFrames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ImpactFrames;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TeamAVisuals_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TeamAVisuals;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TeamBVisuals_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TeamBVisuals;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PartyVisuals_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PartyVisuals;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTBattleWidget constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetBattle"), .Pointer = &UDigimonVenomNXTBattleWidget::execGetBattle },
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTBattleWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleBattleStateChanged"), .Pointer = &UDigimonVenomNXTBattleWidget::execHandleBattleStateChanged },
		{ .NameUTF8 = UTF8TEXT("IsPresentationBusy"), .Pointer = &UDigimonVenomNXTBattleWidget::execIsPresentationBusy },
		{ .NameUTF8 = UTF8TEXT("SetBattle"), .Pointer = &UDigimonVenomNXTBattleWidget::execSetBattle },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_BP_OnBattleRefreshed, "BP_OnBattleRefreshed" }, // 71970adbad3350fed51d3f9f24c9223506dfdc5d
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_GetBattle, "GetBattle" }, // c5b8e47e2fd915457541e5f4c6f40d8bd3d08a59
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleAction, "HandleAction" }, // fd7526f8e71c413f1ec0a65b16f746ed5c00fed7
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_HandleBattleStateChanged, "HandleBattleStateChanged" }, // fcbef3c9617f7d420e1c4f92c211b648e0cf8258
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_IsPresentationBusy, "IsPresentationBusy" }, // a25f07ef00ca5f317dfac679522b98868c427064
		{ &Z_Construct_UFunction_UDigimonVenomNXTBattleWidget_SetBattle, "SetBattle" }, // 1b8365b11b9f7e89174a50cbe7b6154402c32f80
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTBattleWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTBattleWidget Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DisplayState = { "DisplayState", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, DisplayState), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayState_MetaData), NewProp_DisplayState_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LatestState = { "LatestState", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, LatestState), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LatestState_MetaData), NewProp_LatestState_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PendingPresentationEvents_Inner = { "PendingPresentationEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattlePresentationEvent, METADATA_PARAMS(0, nullptr) }; // 1c7abd1d42b15fa5679e85e8af53b609b2d8ff90
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PendingPresentationEvents = { "PendingPresentationEvents", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, PendingPresentationEvents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PendingPresentationEvents_MetaData), NewProp_PendingPresentationEvents_MetaData) }; // 1c7abd1d42b15fa5679e85e8af53b609b2d8ff90
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ActivePresentationEvent = { "ActivePresentationEvent", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ActivePresentationEvent), Z_Construct_UScriptStruct_FDigimonBattlePresentationEvent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActivePresentationEvent_MetaData), NewProp_ActivePresentationEvent_MetaData) }; // 1c7abd1d42b15fa5679e85e8af53b609b2d8ff90
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PresentationOverlay = { "PresentationOverlay", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, PresentationOverlay), Z_Construct_UClass_UOverlay, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PresentationOverlay_MetaData), NewProp_PresentationOverlay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArenaCanvas = { "ArenaCanvas", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ArenaCanvas), Z_Construct_UClass_UCanvasPanel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArenaCanvas_MetaData), NewProp_ArenaCanvas_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleTitle = { "BattleTitle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, BattleTitle), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BattleTitle_MetaData), NewProp_BattleTitle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleSubtitle = { "BattleSubtitle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, BattleSubtitle), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BattleSubtitle_MetaData), NewProp_BattleSubtitle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TurnText = { "TurnText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, TurnText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnText_MetaData), NewProp_TurnText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EventText = { "EventText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, EventText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventText_MetaData), NewProp_EventText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogText = { "LogText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, LogText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogText_MetaData), NewProp_LogText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogScroll = { "LogScroll", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, LogScroll), Z_Construct_UClass_UScrollBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogScroll_MetaData), NewProp_LogScroll_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartyCount = { "PartyCount", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, PartyCount), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyCount_MetaData), NewProp_PartyCount_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchupPreview = { "MatchupPreview", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, MatchupPreview), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchupPreview_MetaData), NewProp_MatchupPreview_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CommandsBox = { "CommandsBox", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, CommandsBox), Z_Construct_UClass_UHorizontalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommandsBox_MetaData), NewProp_CommandsBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResultPanel = { "ResultPanel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ResultPanel), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResultPanel_MetaData), NewProp_ResultPanel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResultHeading = { "ResultHeading", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ResultHeading), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResultHeading_MetaData), NewProp_ResultHeading_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResultSummary = { "ResultSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ResultSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResultSummary_MetaData), NewProp_ResultSummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResultScroll = { "ResultScroll", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ResultScroll), Z_Construct_UClass_UScrollBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResultScroll_MetaData), NewProp_ResultScroll_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActionTray = { "ActionTray", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ActionTray), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActionTray_MetaData), NewProp_ActionTray_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActionTrayContent = { "ActionTrayContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ActionTrayContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActionTrayContent_MetaData), NewProp_ActionTrayContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartyBox = { "PartyBox", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, PartyBox), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyBox_MetaData), NewProp_PartyBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ImpactText = { "ImpactText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ImpactText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactText_MetaData), NewProp_ImpactText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ImpactDetail = { "ImpactDetail", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ImpactDetail), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactDetail_MetaData), NewProp_ImpactDetail_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ImpactImage = { "ImpactImage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ImpactImage), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactImage_MetaData), NewProp_ImpactImage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ImpactFrames_Inner = { "ImpactFrames", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ImpactFrames = { "ImpactFrames", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, ImpactFrames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactFrames_MetaData), NewProp_ImpactFrames_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TeamAVisuals_Inner = { "TeamAVisuals", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattleSlotVisual, METADATA_PARAMS(0, nullptr) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_TeamAVisuals = { "TeamAVisuals", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, TeamAVisuals), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeamAVisuals_MetaData), NewProp_TeamAVisuals_MetaData) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TeamBVisuals_Inner = { "TeamBVisuals", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattleSlotVisual, METADATA_PARAMS(0, nullptr) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_TeamBVisuals = { "TeamBVisuals", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, TeamBVisuals), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeamBVisuals_MetaData), NewProp_TeamBVisuals_MetaData) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PartyVisuals_Inner = { "PartyVisuals", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattleSlotVisual, METADATA_PARAMS(0, nullptr) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PartyVisuals = { "PartyVisuals", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTBattleWidget, PartyVisuals), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyVisuals_MetaData), NewProp_PartyVisuals_MetaData) }; // f2ded77d6050c5b4fe38da23d1ca182e58c634c8
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LatestState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PendingPresentationEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PendingPresentationEvents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivePresentationEvent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PresentationOverlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArenaCanvas,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleSubtitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TurnText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogScroll,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchupPreview,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandsBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResultPanel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResultHeading,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResultSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResultScroll,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActionTray,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActionTrayContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactDetail,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactFrames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactFrames,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamAVisuals_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamAVisuals,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamBVisuals_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamBVisuals,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyVisuals_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyVisuals,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTBattleWidget Property Definitions **************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UCommonActivatableWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTBattleWidget,
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
static void UDigimonVenomNXTBattleWidget_StaticRegisterNativesUDigimonVenomNXTBattleWidget()
{
	UClass* Class = UDigimonVenomNXTBattleWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTBattleWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTBattleWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.InnerSingleton,
				UDigimonVenomNXTBattleWidget_StaticRegisterNativesUDigimonVenomNXTBattleWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTBattleWidget::UDigimonVenomNXTBattleWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTBattleWidget);
UDigimonVenomNXTBattleWidget::~UDigimonVenomNXTBattleWidget() {}
// ********** End Class UDigimonVenomNXTBattleWidget ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonBattleSlotVisual, Z_Construct_UScriptStruct_FDigimonBattleSlotVisual_Statics::NewStructOps, TEXT("DigimonBattleSlotVisual"),&Z_Registration_Info_UScriptStruct_FDigimonBattleSlotVisual, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonBattleSlotVisual), 4074690429U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTBattleWidget, TEXT("UDigimonVenomNXTBattleWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTBattleWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTBattleWidget), 3412264073U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleWidget_h__Script_DigimonVenomNXTRuntime_91116325af2a952b470876024055179689721a5b{
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
