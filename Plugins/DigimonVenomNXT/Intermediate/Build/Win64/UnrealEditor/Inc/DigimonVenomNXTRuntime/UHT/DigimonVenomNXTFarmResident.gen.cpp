// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTFarmResident.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTFarmResident() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UButton(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbookComponent(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UBorder(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UButton(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonOwnedPartner(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmResident(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmResident(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmScene(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTFarmResidentSelectButton *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse selection must not steal keyboard focus from farm movement. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTFarmResident.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse selection must not steal keyboard focus from farm movement." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTFarmResidentSelectButton constinit property declarations *
// ********** End Class UDigimonVenomNXTFarmResidentSelectButton constinit property declarations ***
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTFarmResidentSelectButton>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UButton,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton;
UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTFarmResidentSelectButton;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTFarmResidentSelectButton"),
				Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTFarmResidentSelectButton);
UDigimonVenomNXTFarmResidentSelectButton::~UDigimonVenomNXTFarmResidentSelectButton() {}
// ********** End Class UDigimonVenomNXTFarmResidentSelectButton ***********************************

// ********** Begin Class UDigimonVenomNXTFarmResidentNameplate Function HandleClicked *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTFarmResidentNameplate_HandleClicked_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleClicked constinit property declarations *************************
// ********** End Function HandleClicked constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate, nullptr, "HandleClicked", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTFarmResidentNameplate_HandleClicked(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTFarmResidentNameplate::execHandleClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleClicked();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTFarmResidentNameplate Function HandleClicked ***************

// ********** Begin Class UDigimonVenomNXTFarmResidentNameplate ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Clickable resident identity, rendered only in its owner's player viewport. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTFarmResident.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clickable resident identity, rendered only in its owner's player viewport." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Resident_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Plate_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Label_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTFarmResidentNameplate constinit property declarations ****
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_Resident;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Plate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Label;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTFarmResidentNameplate constinit property declarations ******
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleClicked"), .Pointer = &UDigimonVenomNXTFarmResidentNameplate::execHandleClicked },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTFarmResidentNameplate_HandleClicked, "HandleClicked" }, // dec69d10ca3afedbcf911adab181e40ae41d9aa0
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTFarmResidentNameplate>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTFarmResidentNameplate Property Definitions ***************
const UECodeGen_Private::FWeakObjectPropertyParams UHT_STATICS::NewProp_Resident = { "Resident", nullptr, (EPropertyFlags)0x0044000000002000, UECodeGen_Private::EPropertyGenFlags::WeakObject, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTFarmResidentNameplate, Resident), Z_Construct_UClass_ADigimonVenomNXTFarmResident, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Resident_MetaData), NewProp_Resident_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Plate = { "Plate", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTFarmResidentNameplate, Plate), Z_Construct_UClass_UBorder, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Plate_MetaData), NewProp_Plate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SelectButton = { "SelectButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTFarmResidentNameplate, SelectButton), Z_Construct_UClass_UButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectButton_MetaData), NewProp_SelectButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Label = { "Label", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTFarmResidentNameplate, Label), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Label_MetaData), NewProp_Label_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Resident,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Plate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SelectButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Label,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTFarmResidentNameplate Property Definitions *****************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate,
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
static void UDigimonVenomNXTFarmResidentNameplate_StaticRegisterNativesUDigimonVenomNXTFarmResidentNameplate()
{
	UClass* Class = UDigimonVenomNXTFarmResidentNameplate::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate;
UClass* Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTFarmResidentNameplate;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTFarmResidentNameplate"),
				Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.InnerSingleton,
				UDigimonVenomNXTFarmResidentNameplate_StaticRegisterNativesUDigimonVenomNXTFarmResidentNameplate,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTFarmResidentNameplate::UDigimonVenomNXTFarmResidentNameplate(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTFarmResidentNameplate);
UDigimonVenomNXTFarmResidentNameplate::~UDigimonVenomNXTFarmResidentNameplate() {}
// ********** End Class UDigimonVenomNXTFarmResidentNameplate **************************************

// ********** Begin Class ADigimonVenomNXTFarmResident *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTFarmResident_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A cosmetic local view of one real, owned farm partner, with collision-safe roaming. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTFarmResident.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A cosmetic local view of one real, owned farm partner, with collision-safe roaming." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sprite_MetaData[] = {
		{ "Category", "DigimonVenomNXTFarmResident" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nameplate_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarmScene_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OwningViewer_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Snapshot_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmResident.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTFarmResident constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Nameplate;
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_FarmScene;
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_OwningViewer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Snapshot;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTFarmResident constinit property declarations ***************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTFarmResident>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTFarmResident Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Sprite = { "Sprite", nullptr, (EPropertyFlags)0x01440000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, Sprite), Z_Construct_UClass_UPaperFlipbookComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sprite_MetaData), NewProp_Sprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Nameplate = { "Nameplate", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, Nameplate), Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nameplate_MetaData), NewProp_Nameplate_MetaData) };
const UECodeGen_Private::FWeakObjectPropertyParams UHT_STATICS::NewProp_FarmScene = { "FarmScene", nullptr, (EPropertyFlags)0x0044000000002000, UECodeGen_Private::EPropertyGenFlags::WeakObject, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, FarmScene), Z_Construct_UClass_ADigimonVenomNXTFarmScene, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarmScene_MetaData), NewProp_FarmScene_MetaData) };
const UECodeGen_Private::FWeakObjectPropertyParams UHT_STATICS::NewProp_OwningViewer = { "OwningViewer", nullptr, (EPropertyFlags)0x0044000000002000, UECodeGen_Private::EPropertyGenFlags::WeakObject, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, OwningViewer), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OwningViewer_MetaData), NewProp_OwningViewer_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Snapshot = { "Snapshot", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmResident, Snapshot), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Snapshot_MetaData), NewProp_Snapshot_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Sprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Nameplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FarmScene,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OwningViewer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Snapshot,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTFarmResident Property Definitions **************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTFarmResident,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident;
UClass* Z_Construct_UClass_ADigimonVenomNXTFarmResident(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTFarmResident;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTFarmResident"),
				Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.InnerSingleton,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTFarmResident);
ADigimonVenomNXTFarmResident::~ADigimonVenomNXTFarmResident() {}
// ********** End Class ADigimonVenomNXTFarmResident ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTFarmResident_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTFarmResidentSelectButton, TEXT("UDigimonVenomNXTFarmResidentSelectButton"), &Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentSelectButton, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTFarmResidentSelectButton), 923633710U) },
		{ Z_Construct_UClass_UDigimonVenomNXTFarmResidentNameplate, TEXT("UDigimonVenomNXTFarmResidentNameplate"), &Z_Registration_Info_UClass_UDigimonVenomNXTFarmResidentNameplate, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTFarmResidentNameplate), 2067115772U) },
		{ Z_Construct_UClass_ADigimonVenomNXTFarmResident, TEXT("ADigimonVenomNXTFarmResident"), &Z_Registration_Info_UClass_ADigimonVenomNXTFarmResident, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTFarmResident), 747549280U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTFarmResident_h__Script_DigimonVenomNXTRuntime_37c53aec6d5a192742456d4a14bb30160f900549{
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
