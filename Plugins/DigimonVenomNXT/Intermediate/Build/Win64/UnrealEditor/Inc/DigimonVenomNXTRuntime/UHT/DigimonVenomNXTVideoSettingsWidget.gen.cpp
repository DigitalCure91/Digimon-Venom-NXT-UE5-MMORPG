// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTVideoSettingsWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTVideoSettingsWidget() {}

// ********** Begin Cross Module References ********************************************************
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ESelectInfo(ETypeConstructPhase);
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ETextCommit(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UComboBoxString(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UOverlay(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UVerticalBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonVideoControlView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonVideoOptionChanged__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTActionButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonVideoOptionChanged ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonVideoOptionChanged__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonVideoOptionChanged_Parms
	{
		FName SettingKey;
		int32 OptionIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonVideoOptionChanged constinit property declarations ************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SettingKey;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OptionIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonVideoOptionChanged constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonVideoOptionChanged Property Definitions ***********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SettingKey = { "SettingKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonVideoOptionChanged_Parms, SettingKey), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_OptionIndex = { "OptionIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonVideoOptionChanged_Parms, OptionIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SettingKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OptionIndex,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonVideoOptionChanged Property Definitions *************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonVideoOptionChanged__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonVideoOptionChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonVideoOptionChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonVideoOptionChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonVideoOptionChanged **********************************************

// ********** Begin Class UDigimonVenomNXTVideoOptionPicker Function HandleOptionOpened ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionOpened_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleOptionOpened constinit property declarations ********************
// ********** End Function HandleOptionOpened constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker, nullptr, "HandleOptionOpened", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionOpened(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoOptionPicker::execHandleOptionOpened)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleOptionOpened();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoOptionPicker Function HandleOptionOpened **************

// ********** Begin Class UDigimonVenomNXTVideoOptionPicker Function HandleOptionSelected **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionSelected_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTVideoOptionPicker_eventHandleOptionSelected_Parms
	{
		FString SelectedItem;
		TEnumAsByte<ESelectInfo::Type> SelectionType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleOptionSelected constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SelectedItem;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleOptionSelected constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleOptionSelected Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SelectedItem = { "SelectedItem", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoOptionPicker_eventHandleOptionSelected_Parms, SelectedItem), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SelectionType = { "SelectionType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoOptionPicker_eventHandleOptionSelected_Parms, SelectionType), Z_Construct_UEnum_SlateCore_ESelectInfo, METADATA_PARAMS(0, nullptr) }; // e4997621e7e05d1e476ff2d932386b6873716306
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectedItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectionType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleOptionSelected Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker, nullptr, "HandleOptionSelected", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTVideoOptionPicker_eventHandleOptionSelected_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTVideoOptionPicker_eventHandleOptionSelected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionSelected(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoOptionPicker::execHandleOptionSelected)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SelectedItem);
	P_GET_PROPERTY(FByteProperty,Z_Param_SelectionType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleOptionSelected(Z_Param_SelectedItem,ESelectInfo::Type(Z_Param_SelectionType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoOptionPicker Function HandleOptionSelected ************

// ********** Begin Class UDigimonVenomNXTVideoOptionPicker ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native, keyboard/gamepad accessible dropdown with a stable setting identity. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTVideoSettingsWidget.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native, keyboard/gamepad accessible dropdown with a stable setting identity." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnOptionChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTVideoOptionPicker constinit property declarations ********
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnOptionChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTVideoOptionPicker constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleOptionOpened"), .Pointer = &UDigimonVenomNXTVideoOptionPicker::execHandleOptionOpened },
		{ .NameUTF8 = UTF8TEXT("HandleOptionSelected"), .Pointer = &UDigimonVenomNXTVideoOptionPicker::execHandleOptionSelected },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionOpened, "HandleOptionOpened" }, // 414d1c44bdf938614c9400dab0945e829c50aa5c
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoOptionPicker_HandleOptionSelected, "HandleOptionSelected" }, // a0663c3b9b878056f90d8c109a1faf5d1e81f414
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTVideoOptionPicker>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTVideoOptionPicker Property Definitions *******************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnOptionChanged = { "OnOptionChanged", nullptr, (EPropertyFlags)0x0010000000082000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoOptionPicker, OnOptionChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonVideoOptionChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnOptionChanged_MetaData), NewProp_OnOptionChanged_MetaData) }; // d2fa7db7bb6366c9805f58fd800a764399376088
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnOptionChanged,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTVideoOptionPicker Property Definitions *********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UComboBoxString,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker,
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
	0x00B000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTVideoOptionPicker_StaticRegisterNativesUDigimonVenomNXTVideoOptionPicker()
{
	UClass* Class = UDigimonVenomNXTVideoOptionPicker::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker;
UClass* Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTVideoOptionPicker;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTVideoOptionPicker"),
				Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.InnerSingleton,
				UDigimonVenomNXTVideoOptionPicker_StaticRegisterNativesUDigimonVenomNXTVideoOptionPicker,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTVideoOptionPicker);
UDigimonVenomNXTVideoOptionPicker::~UDigimonVenomNXTVideoOptionPicker() {}
// ********** End Class UDigimonVenomNXTVideoOptionPicker ******************************************

// ********** Begin ScriptStruct FDigimonVideoControlView ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonVideoControlView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonVideoControlView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonVideoControlView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Picker_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Help_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonVideoControlView constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Picker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Help;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonVideoControlView constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonVideoControlView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonVideoControlView Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Picker = { "Picker", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoControlView, Picker), Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Picker_MetaData), NewProp_Picker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Help = { "Help", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonVideoControlView, Help), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Help_MetaData), NewProp_Help_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Picker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Help,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonVideoControlView Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonVideoControlView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonVideoControlView>(),
	alignof(FDigimonVideoControlView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonVideoControlView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonVideoControlView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonVideoControlView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonVideoControlView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonVideoControlView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonVideoControlView ********************************************

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function CloseSettings ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_CloseSettings_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Video" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Keep staged edits, but immediately undo an unconfirmed display preview. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Keep staged edits, but immediately undo an unconfirmed display preview." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CloseSettings constinit property declarations *************************
// ********** End Function CloseSettings constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "CloseSettings", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_CloseSettings(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execCloseSettings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CloseSettings();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function CloseSettings *****************

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function HandleAction ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleAction_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTVideoSettingsWidget_eventHandleAction_Parms
	{
		FString Action;
		int32 Payload;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
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
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleAction_Parms, Action), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Action_MetaData), NewProp_Action_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Payload = { "Payload", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleAction_Parms, Payload), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Payload,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAction Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "HandleAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execHandleAction)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Action);
	P_GET_PROPERTY(FIntProperty,Z_Param_Payload);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAction(Z_Param_Action,Z_Param_Payload);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function HandleAction ******************

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function HandleBack ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleBack_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTVideoSettingsWidget_eventHandleBack_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Video" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Consume Back only when it reverts an active display preview. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Consume Back only when it reverts an active display preview." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HandleBack constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTVideoSettingsWidget_eventHandleBack_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleBack constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleBack Property Definitions ***************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTVideoSettingsWidget_eventHandleBack_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleBack Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "HandleBack", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleBack_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleBack_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleBack(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execHandleBack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HandleBack();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function HandleBack ********************

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function HandleCustomFrameRateCommitted 
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleCustomFrameRateCommitted_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTVideoSettingsWidget_eventHandleCustomFrameRateCommitted_Parms
	{
		FText Text;
		TEnumAsByte<ETextCommit::Type> CommitType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCustomFrameRateCommitted constinit property declarations ********
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleCustomFrameRateCommitted constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleCustomFrameRateCommitted Property Definitions *******************
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleCustomFrameRateCommitted_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_CommitType = { "CommitType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleCustomFrameRateCommitted_Parms, CommitType), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 8323d5849e62ec5be16727bbd18b698ac3ecdec4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommitType,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleCustomFrameRateCommitted Property Definitions *********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "HandleCustomFrameRateCommitted", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleCustomFrameRateCommitted_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleCustomFrameRateCommitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleCustomFrameRateCommitted(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execHandleCustomFrameRateCommitted)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCustomFrameRateCommitted(Z_Param_Out_Text,ETextCommit::Type(Z_Param_CommitType));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function HandleCustomFrameRateCommitted 

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function HandleOptionChanged *********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleOptionChanged_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTVideoSettingsWidget_eventHandleOptionChanged_Parms
	{
		FName SettingKey;
		int32 OptionIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleOptionChanged constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SettingKey;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OptionIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleOptionChanged constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleOptionChanged Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SettingKey = { "SettingKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleOptionChanged_Parms, SettingKey), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_OptionIndex = { "OptionIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTVideoSettingsWidget_eventHandleOptionChanged_Parms, OptionIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SettingKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OptionIndex,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleOptionChanged Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "HandleOptionChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleOptionChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTVideoSettingsWidget_eventHandleOptionChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleOptionChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execHandleOptionChanged)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_SettingKey);
	P_GET_PROPERTY(FIntProperty,Z_Param_OptionIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleOptionChanged(Z_Param_SettingKey,Z_Param_OptionIndex);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function HandleOptionChanged ***********

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Function OpenSettings ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_OpenSettings_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Video" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Idempotent: call when the parent menu shows this page. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Idempotent: call when the parent menu shows this page." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OpenSettings constinit property declarations **************************
// ********** End Function OpenSettings constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, nullptr, "OpenSettings", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_OpenSettings(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTVideoSettingsWidget::execOpenSettings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenSettings();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Function OpenSettings ******************

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Retained local video controls. Gameplay/profile refreshes never reset an edit. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTVideoSettingsWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retained local video controls. Gameplay/profile refreshes never reset an edit." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAction_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditableContent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Categories_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RuntimeNotice_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PresetDescription_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerformanceReadout_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomFrameRateStatus_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomFrameRateInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomFrameRateButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConfirmationText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConfirmationOverlay_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApplyButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RevertButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResetButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KeepDisplayButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UndoDisplayButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CategoryButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PresetButtons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controls_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTVideoSettingsWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget constinit property declarations ******
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditableContent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Categories;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Status;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RuntimeNotice;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PresetDescription;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PerformanceReadout;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomFrameRateStatus;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomFrameRateInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomFrameRateButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ConfirmationText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ConfirmationOverlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ApplyButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RevertButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResetButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_KeepDisplayButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UndoDisplayButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CategoryButtons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CategoryButtons;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PresetButtons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PresetButtons;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Controls_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Controls;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTVideoSettingsWidget constinit property declarations ********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CloseSettings"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execCloseSettings },
		{ .NameUTF8 = UTF8TEXT("HandleAction"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execHandleAction },
		{ .NameUTF8 = UTF8TEXT("HandleBack"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execHandleBack },
		{ .NameUTF8 = UTF8TEXT("HandleCustomFrameRateCommitted"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execHandleCustomFrameRateCommitted },
		{ .NameUTF8 = UTF8TEXT("HandleOptionChanged"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execHandleOptionChanged },
		{ .NameUTF8 = UTF8TEXT("OpenSettings"), .Pointer = &UDigimonVenomNXTVideoSettingsWidget::execOpenSettings },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_CloseSettings, "CloseSettings" }, // 8b0a97c686daa5cb9d9186545c03f73d9b741ddf
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleAction, "HandleAction" }, // bcf993ea6463e957260f9600fdde07fcb6902fa1
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleBack, "HandleBack" }, // cb7cf7282f06459149621a8c0f5b2f895b5f1193
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleCustomFrameRateCommitted, "HandleCustomFrameRateCommitted" }, // 1ec12d163ddefe6fe55e096692b6f3d8ee63bfd1
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_HandleOptionChanged, "HandleOptionChanged" }, // 3fb9583c15e33b2a673c0005b218085dcab2124f
		{ &Z_Construct_UFunction_UDigimonVenomNXTVideoSettingsWidget_OpenSettings, "OpenSettings" }, // 5aa3a17ba18c58352daa14f9a5da8fa8411e39d1
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTVideoSettingsWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTVideoSettingsWidget Property Definitions *****************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAction = { "OnAction", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, OnAction), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUIButtonAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAction_MetaData), NewProp_OnAction_MetaData) }; // fb2000634df561fb2f3babb68202161b73a31637
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, Root), Z_Construct_UClass_UOverlay, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EditableContent = { "EditableContent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, EditableContent), Z_Construct_UClass_UVerticalBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditableContent_MetaData), NewProp_EditableContent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Categories = { "Categories", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, Categories), Z_Construct_UClass_UWidgetSwitcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Categories_MetaData), NewProp_Categories_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, Status), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Status_MetaData), NewProp_Status_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RuntimeNotice = { "RuntimeNotice", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, RuntimeNotice), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RuntimeNotice_MetaData), NewProp_RuntimeNotice_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PresetDescription = { "PresetDescription", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, PresetDescription), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PresetDescription_MetaData), NewProp_PresetDescription_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PerformanceReadout = { "PerformanceReadout", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, PerformanceReadout), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerformanceReadout_MetaData), NewProp_PerformanceReadout_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CustomFrameRateStatus = { "CustomFrameRateStatus", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, CustomFrameRateStatus), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomFrameRateStatus_MetaData), NewProp_CustomFrameRateStatus_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CustomFrameRateInput = { "CustomFrameRateInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, CustomFrameRateInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomFrameRateInput_MetaData), NewProp_CustomFrameRateInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CustomFrameRateButton = { "CustomFrameRateButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, CustomFrameRateButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomFrameRateButton_MetaData), NewProp_CustomFrameRateButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ConfirmationText = { "ConfirmationText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, ConfirmationText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConfirmationText_MetaData), NewProp_ConfirmationText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ConfirmationOverlay = { "ConfirmationOverlay", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, ConfirmationOverlay), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConfirmationOverlay_MetaData), NewProp_ConfirmationOverlay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ApplyButton = { "ApplyButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, ApplyButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApplyButton_MetaData), NewProp_ApplyButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RevertButton = { "RevertButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, RevertButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RevertButton_MetaData), NewProp_RevertButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResetButton = { "ResetButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, ResetButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResetButton_MetaData), NewProp_ResetButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_KeepDisplayButton = { "KeepDisplayButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, KeepDisplayButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KeepDisplayButton_MetaData), NewProp_KeepDisplayButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UndoDisplayButton = { "UndoDisplayButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, UndoDisplayButton), Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UndoDisplayButton_MetaData), NewProp_UndoDisplayButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CategoryButtons_Inner = { "CategoryButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_CategoryButtons = { "CategoryButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, CategoryButtons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CategoryButtons_MetaData), NewProp_CategoryButtons_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PresetButtons_Inner = { "PresetButtons", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDigimonVenomNXTActionButton, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PresetButtons = { "PresetButtons", nullptr, (EPropertyFlags)0x0144008000002008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, PresetButtons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PresetButtons_MetaData), NewProp_PresetButtons_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Controls_Inner = { "Controls", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonVideoControlView, METADATA_PARAMS(0, nullptr) }; // 624ae6c36e6534516e542ce90949554ec6ed0ae6
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Controls = { "Controls", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTVideoSettingsWidget, Controls), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controls_MetaData), NewProp_Controls_MetaData) }; // 624ae6c36e6534516e542ce90949554ec6ed0ae6
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EditableContent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Categories,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Status,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RuntimeNotice,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PresetDescription,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PerformanceReadout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CustomFrameRateStatus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CustomFrameRateInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CustomFrameRateButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ConfirmationText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ConfirmationOverlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ApplyButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RevertButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResetButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_KeepDisplayButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UndoDisplayButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CategoryButtons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CategoryButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PresetButtons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PresetButtons,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controls_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controls,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTVideoSettingsWidget Property Definitions *******************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget,
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
static void UDigimonVenomNXTVideoSettingsWidget_StaticRegisterNativesUDigimonVenomNXTVideoSettingsWidget()
{
	UClass* Class = UDigimonVenomNXTVideoSettingsWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTVideoSettingsWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTVideoSettingsWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.InnerSingleton,
				UDigimonVenomNXTVideoSettingsWidget_StaticRegisterNativesUDigimonVenomNXTVideoSettingsWidget,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTVideoSettingsWidget::UDigimonVenomNXTVideoSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTVideoSettingsWidget);
UDigimonVenomNXTVideoSettingsWidget::~UDigimonVenomNXTVideoSettingsWidget() {}
// ********** End Class UDigimonVenomNXTVideoSettingsWidget ****************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonVideoControlView, Z_Construct_UScriptStruct_FDigimonVideoControlView_Statics::NewStructOps, TEXT("DigimonVideoControlView"),&Z_Registration_Info_UScriptStruct_FDigimonVideoControlView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonVideoControlView), 1649075907U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTVideoOptionPicker, TEXT("UDigimonVenomNXTVideoOptionPicker"), &Z_Registration_Info_UClass_UDigimonVenomNXTVideoOptionPicker, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTVideoOptionPicker), 2522166501U) },
		{ Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, TEXT("UDigimonVenomNXTVideoSettingsWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTVideoSettingsWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTVideoSettingsWidget), 177255692U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTVideoSettingsWidget_h__Script_DigimonVenomNXTRuntime_216c027b28d18c3868e5cb56b14254b5b21776a9{
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
