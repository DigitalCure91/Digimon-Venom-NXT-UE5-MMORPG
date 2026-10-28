// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTSeasonWidget.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTSeasonWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UImage(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UProgressBar(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_USizeBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonArchivePage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonMatchView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonPartnerView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonRivalryView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonRosterView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSeasonWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSeasonWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonSeasonPartnerView *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSeasonPartnerView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSeasonPartnerView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSeasonPartnerView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stats_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSeasonPartnerView constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Bounds;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Card;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Stats;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSeasonPartnerView constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSeasonPartnerView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSeasonPartnerView Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonPartnerView, Bounds), Z_Construct_UClass_USizeBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonPartnerView, Card), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Card_MetaData), NewProp_Card_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonPartnerView, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonPartnerView, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Stats = { "Stats", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonPartnerView, Stats), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stats_MetaData), NewProp_Stats_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Card,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stats,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSeasonPartnerView Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSeasonPartnerView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSeasonPartnerView>(),
	alignof(FDigimonSeasonPartnerView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonPartnerView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSeasonPartnerView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSeasonPartnerView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSeasonPartnerView *******************************************

// ********** Begin ScriptStruct FDigimonSeasonMatchView *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSeasonMatchView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSeasonMatchView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSeasonMatchView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Day_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Home_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Away_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSeasonMatchView constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Card;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Day;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Home;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Away;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Result;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSeasonMatchView constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSeasonMatchView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSeasonMatchView Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonMatchView, Card), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Card_MetaData), NewProp_Card_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Day = { "Day", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonMatchView, Day), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Day_MetaData), NewProp_Day_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Home = { "Home", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonMatchView, Home), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Home_MetaData), NewProp_Home_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Away = { "Away", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonMatchView, Away), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Away_MetaData), NewProp_Away_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonMatchView, Result), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Result_MetaData), NewProp_Result_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Card,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Day,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Home,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Away,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Result,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSeasonMatchView Property Definitions ************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSeasonMatchView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSeasonMatchView>(),
	alignof(FDigimonSeasonMatchView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonMatchView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSeasonMatchView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSeasonMatchView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSeasonMatchView *********************************************

// ********** Begin ScriptStruct FDigimonSeasonRosterView ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSeasonRosterView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSeasonRosterView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSeasonRosterView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Button_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Portrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tamer_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rank_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Record_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Progress_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSeasonRosterView constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Button;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Portrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tamer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Rank;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Record;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Progress;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSeasonRosterView constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSeasonRosterView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSeasonRosterView Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Button = { "Button", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Button), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Button_MetaData), NewProp_Button_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Portrait = { "Portrait", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Portrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Portrait_MetaData), NewProp_Portrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Tamer = { "Tamer", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Tamer), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tamer_MetaData), NewProp_Tamer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Rank = { "Rank", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Rank), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rank_MetaData), NewProp_Rank_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Name), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Record = { "Record", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Record), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Record_MetaData), NewProp_Record_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Progress = { "Progress", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRosterView, Progress), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Progress_MetaData), NewProp_Progress_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Button,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Portrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Rank,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Record,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Progress,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSeasonRosterView Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSeasonRosterView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSeasonRosterView>(),
	alignof(FDigimonSeasonRosterView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonRosterView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSeasonRosterView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSeasonRosterView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSeasonRosterView ********************************************

// ********** Begin ScriptStruct FDigimonSeasonRivalryView *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSeasonRivalryView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSeasonRivalryView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSeasonRivalryView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Names_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Record_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Heat_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSeasonRivalryView constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Card;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Names;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Record;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Status;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Heat;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSeasonRivalryView constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSeasonRivalryView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSeasonRivalryView Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRivalryView, Card), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Card_MetaData), NewProp_Card_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Names = { "Names", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRivalryView, Names), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Names_MetaData), NewProp_Names_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Record = { "Record", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRivalryView, Record), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Record_MetaData), NewProp_Record_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRivalryView, Status), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Status_MetaData), NewProp_Status_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Heat = { "Heat", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonRivalryView, Heat), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Heat_MetaData), NewProp_Heat_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Card,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Names,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Record,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Status,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Heat,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSeasonRivalryView Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSeasonRivalryView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSeasonRivalryView>(),
	alignof(FDigimonSeasonRivalryView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonRivalryView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSeasonRivalryView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSeasonRivalryView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSeasonRivalryView *******************************************

// ********** Begin Class UDigimonVenomNXTSeasonWidget Function HandleAction ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSeasonWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTSeasonWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSeasonWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSeasonWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSeasonWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTSeasonWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTSeasonWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSeasonWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSeasonWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSeasonWidget Function HandleAction *************************

// ********** Begin Class UDigimonVenomNXTSeasonWidget *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTSeasonWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pure presentation of the owner's private, persisted season. Never resolves a booking or awards currency. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTSeasonWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pure presentation of the owner's private, persisted season. Never resolves a booking or awards currency." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchiveSnapshot_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pages_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Calendar_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SaveStatus_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tabs_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchKicker_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchTitle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchDetail_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchOutcome_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MatchAction_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpponentName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerTamer_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpponentTamer_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerTeamSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpponentTeamSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerTeam_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpponentTeam_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeekMatches_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChampionPortrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChampionName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChampionDetails_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CareerRecord_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CareerRank_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CareerTitles_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CareerIncome_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeagueNews_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterPager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RosterRows_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectedTamerName_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectedTamerRecord_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectedTeam_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalryPager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalryPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalryNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalryEmpty_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalryCards_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TitlePortrait_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TitleHolder_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TitleDetails_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TitleMilestone_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefenseProgress_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReignHistory_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchivePager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchivePrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchiveNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchiveRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchiveSelection_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchiveMatches_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchivedPayouts_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalStandings_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalToggle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalPager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoricalRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RewardSummary_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RewardForecast_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PayoutPager_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PayoutPrevious_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PayoutNext_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PayoutRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSeasonWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTSeasonWidget constinit property declarations *************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ArchiveSnapshot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Pages;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Calendar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SaveStatus;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tabs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Tabs;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchKicker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchTitle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchDetail;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchOutcome;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MatchAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OpponentName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerTamer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OpponentTamer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerTeamSummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OpponentTeamSummary;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlayerTeam_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PlayerTeam;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OpponentTeam_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OpponentTeam;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WeekMatches_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_WeekMatches;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChampionPortrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChampionName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChampionDetails;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CareerRecord;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CareerRank;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CareerTitles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CareerIncome;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeagueNews;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterPager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RosterNext;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RosterRows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RosterRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectedTamerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectedTamerRecord;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SelectedTeam_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SelectedTeam;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalryPager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalryPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalryNext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalryEmpty;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RivalryCards_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RivalryCards;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TitlePortrait;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TitleHolder;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TitleDetails;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TitleMilestone;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefenseProgress;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReignHistory;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchivePager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchivePrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchiveNext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchiveRows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ArchiveRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchiveSelection;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ArchiveMatches_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ArchiveMatches;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ArchivedPayouts;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalStandings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalToggle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalPager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalNext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HistoricalRows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_HistoricalRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RewardSummary;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RewardForecast;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PayoutPager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PayoutPrevious;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PayoutNext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PayoutRows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PayoutRows;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTSeasonWidget constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTSeasonWidget::execHandleAction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTSeasonWidget_HandleAction, "HandleAction" }, // 1bb948d38f32a1d5de5feaa7bc70f95bd4be2e20
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTSeasonWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTSeasonWidget Property Definitions ************************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ArchiveSnapshot = { "ArchiveSnapshot", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchiveSnapshot), Z_Construct_UScriptStruct_FDigimonSeasonArchivePage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchiveSnapshot_MetaData), NewProp_ArchiveSnapshot_MetaData) }; // 80c6bd44f1ff8717382adef8167abbcfb94ffd23
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, Root), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Pages = { "Pages", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, Pages), Z_Construct_UClass_UWidgetSwitcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pages_MetaData), NewProp_Pages_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Calendar = { "Calendar", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, Calendar), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Calendar_MetaData), NewProp_Calendar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SaveStatus = { "SaveStatus", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, SaveStatus), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SaveStatus_MetaData), NewProp_SaveStatus_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Tabs_Inner = { "Tabs", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Tabs = { "Tabs", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, Tabs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tabs_MetaData), NewProp_Tabs_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchKicker = { "MatchKicker", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, MatchKicker), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchKicker_MetaData), NewProp_MatchKicker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchTitle = { "MatchTitle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, MatchTitle), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchTitle_MetaData), NewProp_MatchTitle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchDetail = { "MatchDetail", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, MatchDetail), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchDetail_MetaData), NewProp_MatchDetail_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchOutcome = { "MatchOutcome", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, MatchOutcome), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchOutcome_MetaData), NewProp_MatchOutcome_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MatchAction = { "MatchAction", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, MatchAction), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MatchAction_MetaData), NewProp_MatchAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerName = { "PlayerName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PlayerName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerName_MetaData), NewProp_PlayerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OpponentName = { "OpponentName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, OpponentName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpponentName_MetaData), NewProp_OpponentName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerTamer = { "PlayerTamer", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PlayerTamer), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerTamer_MetaData), NewProp_PlayerTamer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OpponentTamer = { "OpponentTamer", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, OpponentTamer), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpponentTamer_MetaData), NewProp_OpponentTamer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerTeamSummary = { "PlayerTeamSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PlayerTeamSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerTeamSummary_MetaData), NewProp_PlayerTeamSummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OpponentTeamSummary = { "OpponentTeamSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, OpponentTeamSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpponentTeamSummary_MetaData), NewProp_OpponentTeamSummary_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PlayerTeam_Inner = { "PlayerTeam", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonPartnerView, METADATA_PARAMS(0, nullptr) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PlayerTeam = { "PlayerTeam", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PlayerTeam), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerTeam_MetaData), NewProp_PlayerTeam_MetaData) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OpponentTeam_Inner = { "OpponentTeam", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonPartnerView, METADATA_PARAMS(0, nullptr) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OpponentTeam = { "OpponentTeam", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, OpponentTeam), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpponentTeam_MetaData), NewProp_OpponentTeam_MetaData) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WeekMatches_Inner = { "WeekMatches", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonMatchView, METADATA_PARAMS(0, nullptr) }; // 78e2e184ba5e90d2da0fc5ab6eec906f012729e1
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_WeekMatches = { "WeekMatches", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, WeekMatches), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeekMatches_MetaData), NewProp_WeekMatches_MetaData) }; // 78e2e184ba5e90d2da0fc5ab6eec906f012729e1
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChampionPortrait = { "ChampionPortrait", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ChampionPortrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChampionPortrait_MetaData), NewProp_ChampionPortrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChampionName = { "ChampionName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ChampionName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChampionName_MetaData), NewProp_ChampionName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChampionDetails = { "ChampionDetails", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ChampionDetails), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChampionDetails_MetaData), NewProp_ChampionDetails_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CareerRecord = { "CareerRecord", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, CareerRecord), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CareerRecord_MetaData), NewProp_CareerRecord_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CareerRank = { "CareerRank", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, CareerRank), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CareerRank_MetaData), NewProp_CareerRank_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CareerTitles = { "CareerTitles", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, CareerTitles), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CareerTitles_MetaData), NewProp_CareerTitles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CareerIncome = { "CareerIncome", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, CareerIncome), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CareerIncome_MetaData), NewProp_CareerIncome_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LeagueNews = { "LeagueNews", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, LeagueNews), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeagueNews_MetaData), NewProp_LeagueNews_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterPager = { "RosterPager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RosterPager), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterPager_MetaData), NewProp_RosterPager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterPrevious = { "RosterPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RosterPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterPrevious_MetaData), NewProp_RosterPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RosterNext = { "RosterNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RosterNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterNext_MetaData), NewProp_RosterNext_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RosterRows_Inner = { "RosterRows", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonRosterView, METADATA_PARAMS(0, nullptr) }; // 888c9a7501725fc18d21026de608490f633da402
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RosterRows = { "RosterRows", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RosterRows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RosterRows_MetaData), NewProp_RosterRows_MetaData) }; // 888c9a7501725fc18d21026de608490f633da402
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SelectedTamerName = { "SelectedTamerName", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, SelectedTamerName), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectedTamerName_MetaData), NewProp_SelectedTamerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SelectedTamerRecord = { "SelectedTamerRecord", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, SelectedTamerRecord), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectedTamerRecord_MetaData), NewProp_SelectedTamerRecord_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SelectedTeam_Inner = { "SelectedTeam", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonPartnerView, METADATA_PARAMS(0, nullptr) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_SelectedTeam = { "SelectedTeam", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, SelectedTeam), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectedTeam_MetaData), NewProp_SelectedTeam_MetaData) }; // 2ede03be7c2c3a4cad2d53c4e3233633b672580b
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalryPager = { "RivalryPager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RivalryPager), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalryPager_MetaData), NewProp_RivalryPager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalryPrevious = { "RivalryPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RivalryPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalryPrevious_MetaData), NewProp_RivalryPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalryNext = { "RivalryNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RivalryNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalryNext_MetaData), NewProp_RivalryNext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalryEmpty = { "RivalryEmpty", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RivalryEmpty), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalryEmpty_MetaData), NewProp_RivalryEmpty_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RivalryCards_Inner = { "RivalryCards", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonRivalryView, METADATA_PARAMS(0, nullptr) }; // 8ea9058f43c32d18d8fa006b551355a11400956d
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RivalryCards = { "RivalryCards", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RivalryCards), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalryCards_MetaData), NewProp_RivalryCards_MetaData) }; // 8ea9058f43c32d18d8fa006b551355a11400956d
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TitlePortrait = { "TitlePortrait", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, TitlePortrait), Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TitlePortrait_MetaData), NewProp_TitlePortrait_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TitleHolder = { "TitleHolder", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, TitleHolder), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TitleHolder_MetaData), NewProp_TitleHolder_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TitleDetails = { "TitleDetails", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, TitleDetails), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TitleDetails_MetaData), NewProp_TitleDetails_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TitleMilestone = { "TitleMilestone", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, TitleMilestone), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TitleMilestone_MetaData), NewProp_TitleMilestone_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DefenseProgress = { "DefenseProgress", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, DefenseProgress), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefenseProgress_MetaData), NewProp_DefenseProgress_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReignHistory = { "ReignHistory", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ReignHistory), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReignHistory_MetaData), NewProp_ReignHistory_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchivePager = { "ArchivePager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchivePager), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchivePager_MetaData), NewProp_ArchivePager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchivePrevious = { "ArchivePrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchivePrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchivePrevious_MetaData), NewProp_ArchivePrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchiveNext = { "ArchiveNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchiveNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchiveNext_MetaData), NewProp_ArchiveNext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchiveRows_Inner = { "ArchiveRows", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ArchiveRows = { "ArchiveRows", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchiveRows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchiveRows_MetaData), NewProp_ArchiveRows_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchiveSelection = { "ArchiveSelection", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchiveSelection), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchiveSelection_MetaData), NewProp_ArchiveSelection_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ArchiveMatches_Inner = { "ArchiveMatches", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSeasonMatchView, METADATA_PARAMS(0, nullptr) }; // 78e2e184ba5e90d2da0fc5ab6eec906f012729e1
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ArchiveMatches = { "ArchiveMatches", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchiveMatches), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchiveMatches_MetaData), NewProp_ArchiveMatches_MetaData) }; // 78e2e184ba5e90d2da0fc5ab6eec906f012729e1
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ArchivedPayouts = { "ArchivedPayouts", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, ArchivedPayouts), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchivedPayouts_MetaData), NewProp_ArchivedPayouts_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalStandings = { "HistoricalStandings", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalStandings), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalStandings_MetaData), NewProp_HistoricalStandings_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalToggle = { "HistoricalToggle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalToggle), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalToggle_MetaData), NewProp_HistoricalToggle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalPager = { "HistoricalPager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalPager), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalPager_MetaData), NewProp_HistoricalPager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalPrevious = { "HistoricalPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalPrevious_MetaData), NewProp_HistoricalPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalNext = { "HistoricalNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalNext_MetaData), NewProp_HistoricalNext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HistoricalRows_Inner = { "HistoricalRows", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_HistoricalRows = { "HistoricalRows", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, HistoricalRows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoricalRows_MetaData), NewProp_HistoricalRows_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RewardSummary = { "RewardSummary", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RewardSummary), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RewardSummary_MetaData), NewProp_RewardSummary_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RewardForecast = { "RewardForecast", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, RewardForecast), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RewardForecast_MetaData), NewProp_RewardForecast_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PayoutPager = { "PayoutPager", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PayoutPager), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PayoutPager_MetaData), NewProp_PayoutPager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PayoutPrevious = { "PayoutPrevious", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PayoutPrevious), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PayoutPrevious_MetaData), NewProp_PayoutPrevious_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PayoutNext = { "PayoutNext", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PayoutNext), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PayoutNext_MetaData), NewProp_PayoutNext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PayoutRows_Inner = { "PayoutRows", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTextBlock, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PayoutRows = { "PayoutRows", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSeasonWidget, PayoutRows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PayoutRows_MetaData), NewProp_PayoutRows_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveSnapshot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pages,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Calendar,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SaveStatus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchKicker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchDetail,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchOutcome,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MatchAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerTamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentTamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerTeamSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentTeamSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerTeam_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerTeam,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentTeam_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentTeam,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WeekMatches_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WeekMatches,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChampionPortrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChampionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChampionDetails,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CareerRecord,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CareerRank,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CareerTitles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CareerIncome,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LeagueNews,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterPager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterRows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RosterRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectedTamerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectedTamerRecord,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectedTeam_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectedTeam,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryPager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryEmpty,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryCards_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalryCards,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TitlePortrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TitleHolder,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TitleDetails,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TitleMilestone,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefenseProgress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReignHistory,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchivePager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchivePrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveRows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveSelection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveMatches_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchiveMatches,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArchivedPayouts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalStandings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalToggle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalPager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalRows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HistoricalRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RewardSummary,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RewardForecast,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PayoutPager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PayoutPrevious,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PayoutNext,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PayoutRows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PayoutRows,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTSeasonWidget Property Definitions **************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTSeasonWidget,
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
static void UDigimonVenomNXTSeasonWidget_StaticRegisterNativesUDigimonVenomNXTSeasonWidget()
{
	UClass* Class = UDigimonVenomNXTSeasonWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTSeasonWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTSeasonWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTSeasonWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.InnerSingleton,
				UDigimonVenomNXTSeasonWidget_StaticRegisterNativesUDigimonVenomNXTSeasonWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTSeasonWidget::UDigimonVenomNXTSeasonWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTSeasonWidget);
UDigimonVenomNXTSeasonWidget::~UDigimonVenomNXTSeasonWidget() {}
// ********** End Class UDigimonVenomNXTSeasonWidget ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSeasonWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonSeasonPartnerView, Z_Construct_UScriptStruct_FDigimonSeasonPartnerView_Statics::NewStructOps, TEXT("DigimonSeasonPartnerView"),&Z_Registration_Info_UScriptStruct_FDigimonSeasonPartnerView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSeasonPartnerView), 786301886U) },
		{ Z_Construct_UScriptStruct_FDigimonSeasonMatchView, Z_Construct_UScriptStruct_FDigimonSeasonMatchView_Statics::NewStructOps, TEXT("DigimonSeasonMatchView"),&Z_Registration_Info_UScriptStruct_FDigimonSeasonMatchView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSeasonMatchView), 2028134788U) },
		{ Z_Construct_UScriptStruct_FDigimonSeasonRosterView, Z_Construct_UScriptStruct_FDigimonSeasonRosterView_Statics::NewStructOps, TEXT("DigimonSeasonRosterView"),&Z_Registration_Info_UScriptStruct_FDigimonSeasonRosterView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSeasonRosterView), 2290915957U) },
		{ Z_Construct_UScriptStruct_FDigimonSeasonRivalryView, Z_Construct_UScriptStruct_FDigimonSeasonRivalryView_Statics::NewStructOps, TEXT("DigimonSeasonRivalryView"),&Z_Registration_Info_UScriptStruct_FDigimonSeasonRivalryView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSeasonRivalryView), 2393441679U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTSeasonWidget, TEXT("UDigimonVenomNXTSeasonWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTSeasonWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTSeasonWidget), 2519947449U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSeasonWidget_h__Script_DigimonVenomNXTRuntime_875361e95678ebb0beeaa0182efa7cd4ad4b2223{
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
