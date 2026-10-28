// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTRelayWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTRelayWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UProgressBar(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTRelayWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTRelayWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTRelayWidget Function HandleAction ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTRelayWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTRelayWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRelayWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTRelayWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTRelayWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTRelayWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTRelayWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTRelayWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTRelayWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTRelayWidget Function HandleAction **************************

// ********** Begin Class UDigimonVenomNXTRelayWidget **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTRelayWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Private campaign journal. Route cards navigate unlocked maps; encounters start beside world NPCs. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTRelayWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Private campaign journal. Route cards navigate unlocked maps; encounters start beside world NPCs." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BadgeMeter_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tabs_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTRelayWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTRelayWidget constinit property declarations **************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Content;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatusText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BadgeMeter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tabs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Tabs;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTRelayWidget constinit property declarations ****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTRelayWidget::execHandleAction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTRelayWidget_HandleAction, "HandleAction" }, // adf2e87d0ff449dde5c867fbae65814bfe5ecb7f
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTRelayWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTRelayWidget Property Definitions *************************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, Root), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, Content), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Content_MetaData), NewProp_Content_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StatusText = { "StatusText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, StatusText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusText_MetaData), NewProp_StatusText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BadgeMeter = { "BadgeMeter", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, BadgeMeter), Z_Construct_UClass_UProgressBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BadgeMeter_MetaData), NewProp_BadgeMeter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Tabs_Inner = { "Tabs", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Tabs = { "Tabs", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTRelayWidget, Tabs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tabs_MetaData), NewProp_Tabs_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Content,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StatusText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BadgeMeter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tabs,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTRelayWidget Property Definitions ***************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTRelayWidget,
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
static void UDigimonVenomNXTRelayWidget_StaticRegisterNativesUDigimonVenomNXTRelayWidget()
{
	UClass* Class = UDigimonVenomNXTRelayWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTRelayWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTRelayWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTRelayWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.InnerSingleton,
				UDigimonVenomNXTRelayWidget_StaticRegisterNativesUDigimonVenomNXTRelayWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTRelayWidget::UDigimonVenomNXTRelayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTRelayWidget);
UDigimonVenomNXTRelayWidget::~UDigimonVenomNXTRelayWidget() {}
// ********** End Class UDigimonVenomNXTRelayWidget ************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTRelayWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTRelayWidget, TEXT("UDigimonVenomNXTRelayWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTRelayWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTRelayWidget), 417413910U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTRelayWidget_h__Script_DigimonVenomNXTRuntime_f5e4a0c46ff8261ca919438d39d48befb0ce0739{
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
