// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTEvolutionWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTEvolutionWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UProgressBar(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUniformGridPanel(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonEvolutionRouteView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonEvolutionPartnerTile **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonEvolutionPartnerTile>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonEvolutionPartnerTile); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Retained widgets are updated in place: a profile replication never restarts a portrait. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retained widgets are updated in place: a profile replication never restarts a portrait." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Button_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Detail_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonEvolutionPartnerTile constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Button;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Detail;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonEvolutionPartnerTile constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonEvolutionPartnerTile>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonEvolutionPartnerTile Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Button = { "Button", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionPartnerTile, Button), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Button_MetaData), NewProp_Button_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionPartnerTile, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionPartnerTile, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Detail = { "Detail", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionPartnerTile, Detail), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Detail_MetaData), NewProp_Detail_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Button,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Detail,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonEvolutionPartnerTile Property Definitions *******************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonEvolutionPartnerTile",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonEvolutionPartnerTile>(),
	alignof(FDigimonEvolutionPartnerTile),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonEvolutionPartnerTile"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonEvolutionPartnerTile ****************************************

// ********** Begin ScriptStruct FDigimonEvolutionRouteView ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonEvolutionRouteView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonEvolutionRouteView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonEvolutionRouteView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequirementLabels_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequirementBars_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdditionalRequirements_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Outcome_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transform_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransformLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonEvolutionRouteView constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Card;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Stage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Status;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RequirementLabels_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequirementLabels;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RequirementBars_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequirementBars;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AdditionalRequirements;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Outcome;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Transform;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TransformLabel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonEvolutionRouteView constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonEvolutionRouteView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonEvolutionRouteView Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Card), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Card_MetaData), NewProp_Card_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Stage = { "Stage", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Stage), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stage_MetaData), NewProp_Stage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Status), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Status_MetaData), NewProp_Status_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RequirementLabels_Inner = { "RequirementLabels", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RequirementLabels = { "RequirementLabels", nullptr, (EPropertyFlags)0x0114008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, RequirementLabels), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequirementLabels_MetaData), NewProp_RequirementLabels_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RequirementBars_Inner = { "RequirementBars", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UProgressBar, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RequirementBars = { "RequirementBars", nullptr, (EPropertyFlags)0x0114008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, RequirementBars), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequirementBars_MetaData), NewProp_RequirementBars_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AdditionalRequirements = { "AdditionalRequirements", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, AdditionalRequirements), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdditionalRequirements_MetaData), NewProp_AdditionalRequirements_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Outcome = { "Outcome", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Outcome), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Outcome_MetaData), NewProp_Outcome_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Transform = { "Transform", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, Transform), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transform_MetaData), NewProp_Transform_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TransformLabel = { "TransformLabel", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEvolutionRouteView, TransformLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransformLabel_MetaData), NewProp_TransformLabel_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Card,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Status,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequirementLabels_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequirementLabels,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequirementBars_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequirementBars,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdditionalRequirements,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Outcome,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Transform,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TransformLabel,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonEvolutionRouteView Property Definitions *********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonEvolutionRouteView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonEvolutionRouteView>(),
	alignof(FDigimonEvolutionRouteView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonEvolutionRouteView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonEvolutionRouteView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonEvolutionRouteView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonEvolutionRouteView ******************************************

// ********** Begin Class UDigimonVenomNXTEvolutionWidget Function HandleAction ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTEvolutionWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTEvolutionWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEvolutionWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTEvolutionWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTEvolutionWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTEvolutionWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTEvolutionWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTEvolutionWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTEvolutionWidget Function HandleAction **********************

// ********** Begin Class UDigimonVenomNXTEvolutionWidget ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Collection, evolution planning and scan browsing, all keyed by stable partner GUIDs. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTEvolutionWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Collection, evolution planning and scan browsing, all keyed by stable partner GUIDs." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartnerSection_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanSection_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Summary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterPageLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterTiles_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tabs_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hero_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroPortrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroStage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroAffinity_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroElement_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroStats_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroExperience_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroNextLevel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroXP_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroTraining_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroCAM_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroABI_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroCAMText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeroABIText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeaderButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CAMButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ABIButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CAMButtonLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ABIButtonLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RouteIntro_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RouteEmpty_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RouteGrid_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RouteViews_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanGrid_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanPageLabel_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScanNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTEvolutionWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTEvolutionWidget constinit property declarations **********
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartnerSection;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScanSection;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Summary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterPageLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterNext;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RosterTiles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RosterTiles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tabs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Tabs;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Hero;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroPortrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroStage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroAffinity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroElement;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroStats;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroExperience;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroNextLevel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroXP;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroTraining;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroCAM;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroABI;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroCAMText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeroABIText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PartyButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeaderButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CAMButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ABIButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CAMButtonLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ABIButtonLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RouteIntro;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RouteEmpty;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RouteGrid;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RouteViews_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RouteViews;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScanGrid;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScanPageLabel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScanPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScanNext;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTEvolutionWidget constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTEvolutionWidget::execHandleAction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTEvolutionWidget_HandleAction, "HandleAction" }, // ca8f682db8401f78c1f1577af7b60b9f2e034f77
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTEvolutionWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTEvolutionWidget Property Definitions *********************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, Root), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartnerSection = { "PartnerSection", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, PartnerSection), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartnerSection_MetaData), NewProp_PartnerSection_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ScanSection = { "ScanSection", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ScanSection), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanSection_MetaData), NewProp_ScanSection_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Summary = { "Summary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, Summary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Summary_MetaData), NewProp_Summary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterPageLabel = { "RosterPageLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RosterPageLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterPageLabel_MetaData), NewProp_RosterPageLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterPrevious = { "RosterPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RosterPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterPrevious_MetaData), NewProp_RosterPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterNext = { "RosterNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RosterNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterNext_MetaData), NewProp_RosterNext_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RosterTiles_Inner = { "RosterTiles", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile, METADATA_PARAMS(0, nullptr) }; // 4570c601cf5ca170aca770d718a9e052d4085525
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RosterTiles = { "RosterTiles", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RosterTiles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterTiles_MetaData), NewProp_RosterTiles_MetaData) }; // 4570c601cf5ca170aca770d718a9e052d4085525
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Tabs_Inner = { "Tabs", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Tabs = { "Tabs", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, Tabs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tabs_MetaData), NewProp_Tabs_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Hero = { "Hero", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, Hero), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hero_MetaData), NewProp_Hero_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroPortrait = { "HeroPortrait", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroPortrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroPortrait_MetaData), NewProp_HeroPortrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroName = { "HeroName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroName_MetaData), NewProp_HeroName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroStage = { "HeroStage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroStage), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroStage_MetaData), NewProp_HeroStage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroAffinity = { "HeroAffinity", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroAffinity), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroAffinity_MetaData), NewProp_HeroAffinity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroElement = { "HeroElement", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroElement), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroElement_MetaData), NewProp_HeroElement_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroStats = { "HeroStats", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroStats), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroStats_MetaData), NewProp_HeroStats_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroExperience = { "HeroExperience", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroExperience), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroExperience_MetaData), NewProp_HeroExperience_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroNextLevel = { "HeroNextLevel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroNextLevel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroNextLevel_MetaData), NewProp_HeroNextLevel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroXP = { "HeroXP", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroXP), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroXP_MetaData), NewProp_HeroXP_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroTraining = { "HeroTraining", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroTraining), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroTraining_MetaData), NewProp_HeroTraining_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroCAM = { "HeroCAM", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroCAM), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroCAM_MetaData), NewProp_HeroCAM_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroABI = { "HeroABI", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroABI), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroABI_MetaData), NewProp_HeroABI_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroCAMText = { "HeroCAMText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroCAMText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroCAMText_MetaData), NewProp_HeroCAMText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeroABIText = { "HeroABIText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, HeroABIText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeroABIText_MetaData), NewProp_HeroABIText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PartyButton = { "PartyButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, PartyButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyButton_MetaData), NewProp_PartyButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LeaderButton = { "LeaderButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, LeaderButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeaderButton_MetaData), NewProp_LeaderButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CAMButton = { "CAMButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, CAMButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CAMButton_MetaData), NewProp_CAMButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ABIButton = { "ABIButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ABIButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ABIButton_MetaData), NewProp_ABIButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CAMButtonLabel = { "CAMButtonLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, CAMButtonLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CAMButtonLabel_MetaData), NewProp_CAMButtonLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ABIButtonLabel = { "ABIButtonLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ABIButtonLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ABIButtonLabel_MetaData), NewProp_ABIButtonLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RouteIntro = { "RouteIntro", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RouteIntro), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RouteIntro_MetaData), NewProp_RouteIntro_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RouteEmpty = { "RouteEmpty", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RouteEmpty), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RouteEmpty_MetaData), NewProp_RouteEmpty_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RouteGrid = { "RouteGrid", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RouteGrid), Z_Construct_UClass_UUniformGridPanel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RouteGrid_MetaData), NewProp_RouteGrid_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RouteViews_Inner = { "RouteViews", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonEvolutionRouteView, METADATA_PARAMS(0, nullptr) }; // 5cedb7446e5141ed2e71007ebe51845b9f6ab985
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RouteViews = { "RouteViews", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, RouteViews), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RouteViews_MetaData), NewProp_RouteViews_MetaData) }; // 5cedb7446e5141ed2e71007ebe51845b9f6ab985
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ScanGrid = { "ScanGrid", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ScanGrid), Z_Construct_UClass_UUniformGridPanel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanGrid_MetaData), NewProp_ScanGrid_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ScanPageLabel = { "ScanPageLabel", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ScanPageLabel), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanPageLabel_MetaData), NewProp_ScanPageLabel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ScanPrevious = { "ScanPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ScanPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanPrevious_MetaData), NewProp_ScanPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ScanNext = { "ScanNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTEvolutionWidget, ScanNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScanNext_MetaData), NewProp_ScanNext_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartnerSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Summary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterPageLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterTiles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterTiles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Hero,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroPortrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroStage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroAffinity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroElement,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroStats,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroExperience,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroNextLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroXP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroTraining,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroCAM,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroABI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroCAMText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeroABIText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LeaderButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CAMButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ABIButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CAMButtonLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ABIButtonLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RouteIntro,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RouteEmpty,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RouteGrid,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RouteViews_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RouteViews,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanGrid,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanPageLabel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScanNext,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTEvolutionWidget Property Definitions ***********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget,
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
static void UDigimonVenomNXTEvolutionWidget_StaticRegisterNativesUDigimonVenomNXTEvolutionWidget()
{
	UClass* Class = UDigimonVenomNXTEvolutionWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTEvolutionWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTEvolutionWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.InnerSingleton,
				UDigimonVenomNXTEvolutionWidget_StaticRegisterNativesUDigimonVenomNXTEvolutionWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTEvolutionWidget::UDigimonVenomNXTEvolutionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTEvolutionWidget);
UDigimonVenomNXTEvolutionWidget::~UDigimonVenomNXTEvolutionWidget() {}
// ********** End Class UDigimonVenomNXTEvolutionWidget ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTEvolutionWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile, Z_Construct_UScriptStruct_FDigimonEvolutionPartnerTile_Statics::NewStructOps, TEXT("DigimonEvolutionPartnerTile"),&Z_Registration_Info_UScriptStruct_FDigimonEvolutionPartnerTile, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonEvolutionPartnerTile), 1165018625U) },
		{ Z_Construct_UScriptStruct_FDigimonEvolutionRouteView, Z_Construct_UScriptStruct_FDigimonEvolutionRouteView_Statics::NewStructOps, TEXT("DigimonEvolutionRouteView"),&Z_Registration_Info_UScriptStruct_FDigimonEvolutionRouteView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonEvolutionRouteView), 1559082820U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTEvolutionWidget, TEXT("UDigimonVenomNXTEvolutionWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTEvolutionWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTEvolutionWidget), 358445763U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTEvolutionWidget_h__Script_DigimonVenomNXTRuntime_bf3b4fe940611873a26f66cfb78bb9ad3b5591af{
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
