// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTServerConsoleWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTServerConsoleWidget() {}

// ********** Begin Cross Module References ********************************************************
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ESelectInfo(ETypeConstructPhase);
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ETextCommit(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UComboBoxString(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UMultiLineEditableText(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UScrollBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTConsoleFilter(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTConsoleFilter(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTConsoleFilter ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTConsoleFilter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Uses the engine's initializer API rather than deprecated direct UMG fields. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTServerConsoleWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Uses the engine's initializer API rather than deprecated direct UMG fields." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTConsoleFilter constinit property declarations ************
// ********** End Class UDigimonVenomNXTConsoleFilter constinit property declarations **************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTConsoleFilter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UComboBoxString,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTConsoleFilter,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter;
UClass* Z_Construct_UClass_UDigimonVenomNXTConsoleFilter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTConsoleFilter;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTConsoleFilter"),
				Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.InnerSingleton,
				nullptr,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTConsoleFilter);
UDigimonVenomNXTConsoleFilter::~UDigimonVenomNXTConsoleFilter() {}
// ********** End Class UDigimonVenomNXTConsoleFilter **********************************************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function CloseConsole ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_CloseConsole_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CloseConsole constinit property declarations **************************
// ********** End Function CloseConsole constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "CloseConsole", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_CloseConsole(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execCloseConsole)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CloseConsole();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function CloseConsole ******************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleAction ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleAction ******************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleBack ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleBack_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleBack_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleBack constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTServerConsoleWidget_eventHandleBack_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleBack constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleBack Property Definitions ***************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTServerConsoleWidget_eventHandleBack_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleBack Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleBack", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleBack_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleBack_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleBack(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleBack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HandleBack();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleBack ********************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleCategoryChanged *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCategoryChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleCategoryChanged_Parms
	{
		FString Selection;
		TEnumAsByte<ESelectInfo::Type> SelectionType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCategoryChanged constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Selection;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleCategoryChanged constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleCategoryChanged Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Selection = { "Selection", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCategoryChanged_Parms, Selection), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SelectionType = { "SelectionType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCategoryChanged_Parms, SelectionType), Z_Construct_UEnum_SlateCore_ESelectInfo, METADATA_PARAMS(0, nullptr) }; // e4997621e7e05d1e476ff2d932386b6873716306
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Selection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleCategoryChanged Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleCategoryChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCategoryChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCategoryChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCategoryChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleCategoryChanged)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Selection);
	P_GET_PROPERTY(FByteProperty,Z_Param_SelectionType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCategoryChanged(Z_Param_Selection,ESelectInfo::Type(Z_Param_SelectionType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleCategoryChanged *********

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleCommandChanged ********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleCommandChanged_Parms
	{
		FText Text;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCommandChanged constinit property declarations ******************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleCommandChanged constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleCommandChanged Property Definitions *****************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCommandChanged_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleCommandChanged Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleCommandChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCommandChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCommandChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleCommandChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCommandChanged(Z_Param_Out_Text);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleCommandChanged **********

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleCommandCommitted ******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandCommitted_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleCommandCommitted_Parms
	{
		FText Text;
		TEnumAsByte<ETextCommit::Type> CommitType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCommandCommitted constinit property declarations ****************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleCommandCommitted constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleCommandCommitted Property Definitions ***************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCommandCommitted_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_CommitType = { "CommitType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCommandCommitted_Parms, CommitType), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 8323d5849e62ec5be16727bbd18b698ac3ecdec4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommitType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleCommandCommitted Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleCommandCommitted", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCommandCommitted_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCommandCommitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandCommitted(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleCommandCommitted)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCommandCommitted(Z_Param_Out_Text,ETextCommit::Type(Z_Param_CommitType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleCommandCommitted ********

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleCredentialCommitted ***
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCredentialCommitted_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleCredentialCommitted_Parms
	{
		FText Text;
		TEnumAsByte<ETextCommit::Type> CommitType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCredentialCommitted constinit property declarations *************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleCredentialCommitted constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleCredentialCommitted Property Definitions ************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCredentialCommitted_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_CommitType = { "CommitType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleCredentialCommitted_Parms, CommitType), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 8323d5849e62ec5be16727bbd18b698ac3ecdec4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommitType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleCredentialCommitted Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleCredentialCommitted", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCredentialCommitted_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleCredentialCommitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCredentialCommitted(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleCredentialCommitted)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCredentialCommitted(Z_Param_Out_Text,ETextCommit::Type(Z_Param_CommitType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleCredentialCommitted *****

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleHelpSearchChanged *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleHelpSearchChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleHelpSearchChanged_Parms
	{
		FText Text;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleHelpSearchChanged constinit property declarations ***************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleHelpSearchChanged constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleHelpSearchChanged Property Definitions **************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleHelpSearchChanged_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleHelpSearchChanged Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleHelpSearchChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleHelpSearchChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleHelpSearchChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleHelpSearchChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleHelpSearchChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleHelpSearchChanged(Z_Param_Out_Text);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleHelpSearchChanged *******

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleLogSearchChanged ******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleLogSearchChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleLogSearchChanged_Parms
	{
		FText Text;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleLogSearchChanged constinit property declarations ****************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleLogSearchChanged constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleLogSearchChanged Property Definitions ***************************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleLogSearchChanged_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleLogSearchChanged Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleLogSearchChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleLogSearchChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleLogSearchChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleLogSearchChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleLogSearchChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleLogSearchChanged(Z_Param_Out_Text);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleLogSearchChanged ********

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleSeverityChanged *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleSeverityChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleSeverityChanged_Parms
	{
		FString Selection;
		TEnumAsByte<ESelectInfo::Type> SelectionType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleSeverityChanged constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Selection;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleSeverityChanged constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleSeverityChanged Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Selection = { "Selection", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleSeverityChanged_Parms, Selection), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SelectionType = { "SelectionType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleSeverityChanged_Parms, SelectionType), Z_Construct_UEnum_SlateCore_ESelectInfo, METADATA_PARAMS(0, nullptr) }; // e4997621e7e05d1e476ff2d932386b6873716306
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Selection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleSeverityChanged Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleSeverityChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleSeverityChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleSeverityChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleSeverityChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleSeverityChanged)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Selection);
	P_GET_PROPERTY(FByteProperty,Z_Param_SelectionType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleSeverityChanged(Z_Param_Selection,ESelectInfo::Type(Z_Param_SelectionType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleSeverityChanged *********

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function HandleUserScrolled **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleUserScrolled_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventHandleUserScrolled_Parms
	{
		float Offset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleUserScrolled constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Offset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleUserScrolled constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleUserScrolled Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTServerConsoleWidget_eventHandleUserScrolled_Parms, Offset), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Offset,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleUserScrolled Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "HandleUserScrolled", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleUserScrolled_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventHandleUserScrolled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleUserScrolled(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execHandleUserScrolled)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Offset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleUserScrolled(Z_Param_Offset);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function HandleUserScrolled ************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function IsOpen **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_IsOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTServerConsoleWidget_eventIsOpen_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsOpen constinit property declarations ********************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTServerConsoleWidget_eventIsOpen_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsOpen constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsOpen Property Definitions *******************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTServerConsoleWidget_eventIsOpen_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsOpen Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "IsOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventIsOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTServerConsoleWidget_eventIsOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_IsOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execIsOpen)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsOpen();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function IsOpen ************************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Function OpenConsole *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_OpenConsole_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OpenConsole constinit property declarations ***************************
// ********** End Function OpenConsole constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, nullptr, "OpenConsole", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_OpenConsole(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTServerConsoleWidget::execOpenConsole)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenConsole();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTServerConsoleWidget Function OpenConsole *******************

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Local listen-host console. It neither replicates output nor forwards commands through chat/RPCs. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTServerConsoleWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local listen-host console. It neither replicates output nor forwards commands through chat/RPCs." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pages_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogScroll_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HelpRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SessionReadout_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ViewReadout_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmptyMessage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FeedbackText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputHint_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HelpReadout_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PauseCaption_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCaption_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CategoryPicker_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SeverityPicker_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogSearchInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HelpSearchInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommandInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExecuteButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PauseButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialOverlay_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialTitle_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialAccount_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialFeedback_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialPassword_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CredentialConfirmation_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderedRows_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget constinit property declarations ******
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Content;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Pages;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogScroll;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HelpRows;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SessionReadout;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ViewReadout;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EmptyMessage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FeedbackText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputHint;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HelpReadout;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PauseCaption;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCaption;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CategoryPicker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SeverityPicker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LogSearchInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HelpSearchInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CommandInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ExecuteButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PauseButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialOverlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialTitle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialAccount;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialFeedback;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialPassword;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CredentialConfirmation;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PageButtons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PageButtons;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RenderedRows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RenderedRows;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTServerConsoleWidget constinit property declarations ********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CloseConsole"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execCloseConsole },
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleBack"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleBack },
		{ .NameUTF8 = UTF8TEXT("HandleCategoryChanged"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleCategoryChanged },
		{ .NameUTF8 = UTF8TEXT("HandleCommandChanged"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleCommandChanged },
		{ .NameUTF8 = UTF8TEXT("HandleCommandCommitted"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleCommandCommitted },
		{ .NameUTF8 = UTF8TEXT("HandleCredentialCommitted"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleCredentialCommitted },
		{ .NameUTF8 = UTF8TEXT("HandleHelpSearchChanged"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleHelpSearchChanged },
		{ .NameUTF8 = UTF8TEXT("HandleLogSearchChanged"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleLogSearchChanged },
		{ .NameUTF8 = UTF8TEXT("HandleSeverityChanged"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleSeverityChanged },
		{ .NameUTF8 = UTF8TEXT("HandleUserScrolled"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execHandleUserScrolled },
		{ .NameUTF8 = UTF8TEXT("IsOpen"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execIsOpen },
		{ .NameUTF8 = UTF8TEXT("OpenConsole"), .Pointer = &UDigimonVenomNXTServerConsoleWidget::execOpenConsole },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_CloseConsole, "CloseConsole" }, // 0af20a9a3f7b81bf2dd862277ec8ba623674b49b
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleAction, "HandleAction" }, // 6ca40c6c2c3364b7bc96e1c22d63108ef01206d4
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleBack, "HandleBack" }, // 10995f26fed780c996b599a711de7a3cab4d9f4a
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCategoryChanged, "HandleCategoryChanged" }, // 01cfc44e17a5a9901c0243068b46641e4e47e15e
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandChanged, "HandleCommandChanged" }, // f8d9c284d8d6827722bcc928b7eebcc10b12ee11
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCommandCommitted, "HandleCommandCommitted" }, // 5a4af004a825e9a76e420e7024494c0e9846f5f2
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleCredentialCommitted, "HandleCredentialCommitted" }, // 671bdf53e06661527ea1d0e8be02a679f9473103
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleHelpSearchChanged, "HandleHelpSearchChanged" }, // 2aee5dec9207a6d8bb251e2395199d69935c48f2
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleLogSearchChanged, "HandleLogSearchChanged" }, // 3a19fb1e368b454c85398636b71789179e1775a3
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleSeverityChanged, "HandleSeverityChanged" }, // 884f9e6cb4bf8650fec1dee7732b491c393da375
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_HandleUserScrolled, "HandleUserScrolled" }, // acbdd1666fae2d94bf93ce90bb9e0ebcba73dd3a
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_IsOpen, "IsOpen" }, // fd347eed7ecf6718385aad1cfe7fa29da65772de
		{ &Z_Construct_UFunction_UDigimonVenomNXTServerConsoleWidget_OpenConsole, "OpenConsole" }, // 514f1bebffd7c9875d6224babdff0a5f6f314979
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTServerConsoleWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTServerConsoleWidget Property Definitions *****************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, Root), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, Content), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Content_MetaData), NewProp_Content_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Pages = { "Pages", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, Pages), Z_Construct_UClass_UWidgetSwitcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pages_MetaData), NewProp_Pages_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogScroll = { "LogScroll", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, LogScroll), Z_Construct_UClass_UScrollBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogScroll_MetaData), NewProp_LogScroll_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogRows = { "LogRows", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, LogRows), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogRows_MetaData), NewProp_LogRows_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HelpRows = { "HelpRows", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, HelpRows), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HelpRows_MetaData), NewProp_HelpRows_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SessionReadout = { "SessionReadout", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, SessionReadout), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SessionReadout_MetaData), NewProp_SessionReadout_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ViewReadout = { "ViewReadout", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, ViewReadout), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ViewReadout_MetaData), NewProp_ViewReadout_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EmptyMessage = { "EmptyMessage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, EmptyMessage), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmptyMessage_MetaData), NewProp_EmptyMessage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FeedbackText = { "FeedbackText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, FeedbackText), Z_Construct_UClass_UMultiLineEditableText, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FeedbackText_MetaData), NewProp_FeedbackText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InputHint = { "InputHint", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, InputHint), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputHint_MetaData), NewProp_InputHint_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HelpReadout = { "HelpReadout", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, HelpReadout), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HelpReadout_MetaData), NewProp_HelpReadout_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PauseCaption = { "PauseCaption", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, PauseCaption), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PauseCaption_MetaData), NewProp_PauseCaption_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowCaption = { "FollowCaption", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, FollowCaption), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCaption_MetaData), NewProp_FollowCaption_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CategoryPicker = { "CategoryPicker", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CategoryPicker), Z_Construct_UClass_UDigimonVenomNXTConsoleFilter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CategoryPicker_MetaData), NewProp_CategoryPicker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SeverityPicker = { "SeverityPicker", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, SeverityPicker), Z_Construct_UClass_UDigimonVenomNXTConsoleFilter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SeverityPicker_MetaData), NewProp_SeverityPicker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LogSearchInput = { "LogSearchInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, LogSearchInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogSearchInput_MetaData), NewProp_LogSearchInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HelpSearchInput = { "HelpSearchInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, HelpSearchInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HelpSearchInput_MetaData), NewProp_HelpSearchInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CommandInput = { "CommandInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CommandInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommandInput_MetaData), NewProp_CommandInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ExecuteButton = { "ExecuteButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, ExecuteButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExecuteButton_MetaData), NewProp_ExecuteButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PauseButton = { "PauseButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, PauseButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PauseButton_MetaData), NewProp_PauseButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowButton = { "FollowButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, FollowButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowButton_MetaData), NewProp_FollowButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialOverlay = { "CredentialOverlay", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialOverlay), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialOverlay_MetaData), NewProp_CredentialOverlay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialTitle = { "CredentialTitle", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialTitle), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialTitle_MetaData), NewProp_CredentialTitle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialAccount = { "CredentialAccount", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialAccount), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialAccount_MetaData), NewProp_CredentialAccount_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialFeedback = { "CredentialFeedback", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialFeedback), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialFeedback_MetaData), NewProp_CredentialFeedback_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialPassword = { "CredentialPassword", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialPassword), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialPassword_MetaData), NewProp_CredentialPassword_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CredentialConfirmation = { "CredentialConfirmation", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, CredentialConfirmation), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CredentialConfirmation_MetaData), NewProp_CredentialConfirmation_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PageButtons_Inner = { "PageButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PageButtons = { "PageButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, PageButtons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageButtons_MetaData), NewProp_PageButtons_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RenderedRows_Inner = { "RenderedRows", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UBorder, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RenderedRows = { "RenderedRows", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleWidget, RenderedRows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderedRows_MetaData), NewProp_RenderedRows_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Content,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pages,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogScroll,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HelpRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionReadout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ViewReadout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmptyMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FeedbackText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InputHint,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HelpReadout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PauseCaption,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowCaption,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CategoryPicker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SeverityPicker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LogSearchInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HelpSearchInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExecuteButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PauseButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialOverlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialAccount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialFeedback,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialPassword,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CredentialConfirmation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageButtons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RenderedRows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RenderedRows,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTServerConsoleWidget Property Definitions *******************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget,
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
static void UDigimonVenomNXTServerConsoleWidget_StaticRegisterNativesUDigimonVenomNXTServerConsoleWidget()
{
	UClass* Class = UDigimonVenomNXTServerConsoleWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTServerConsoleWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTServerConsoleWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.InnerSingleton,
				UDigimonVenomNXTServerConsoleWidget_StaticRegisterNativesUDigimonVenomNXTServerConsoleWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTServerConsoleWidget::UDigimonVenomNXTServerConsoleWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTServerConsoleWidget);
UDigimonVenomNXTServerConsoleWidget::~UDigimonVenomNXTServerConsoleWidget() {}
// ********** End Class UDigimonVenomNXTServerConsoleWidget ****************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTServerConsoleWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTConsoleFilter, TEXT("UDigimonVenomNXTConsoleFilter"), &Z_Registration_Info_UClass_UDigimonVenomNXTConsoleFilter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTConsoleFilter), 850820315U) },
		{ Z_Construct_UClass_UDigimonVenomNXTServerConsoleWidget, TEXT("UDigimonVenomNXTServerConsoleWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTServerConsoleWidget), 4100667569U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTServerConsoleWidget_h__Script_DigimonVenomNXTRuntime_e669ea12144ffb91e9c9c65ace8d9d556d6242a1{
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
