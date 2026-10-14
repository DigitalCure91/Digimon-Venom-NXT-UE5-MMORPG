// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAnimatedPortrait.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAnimatedPortrait() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UTexture2D(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbook(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSprite(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UImage(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait Function PlayAttack *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_PlayAttack_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Play the source attack poses once; snapshots never alter the shared idle clock. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Play the source attack poses once; snapshots never alter the shared idle clock." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function PlayAttack constinit property declarations ****************************
// ********** End Function PlayAttack constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, nullptr, "PlayAttack", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_PlayAttack(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAnimatedPortrait::execPlayAttack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayAttack();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAnimatedPortrait Function PlayAttack ***********************

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait Function SetDigimon *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetDigimon_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAnimatedPortrait_eventSetDigimon_Parms
	{
		FName InSpeciesId;
		EDigimonVariant InVariant;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetDigimon constinit property declarations ****************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_InSpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InVariant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_InVariant;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDigimon constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDigimon Property Definitions ***************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_InSpeciesId = { "InSpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAnimatedPortrait_eventSetDigimon_Parms, InSpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_InVariant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_InVariant = { "InVariant", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAnimatedPortrait_eventSetDigimon_Parms, InVariant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InSpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InVariant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InVariant,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetDigimon Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, nullptr, "SetDigimon", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAnimatedPortrait_eventSetDigimon_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAnimatedPortrait_eventSetDigimon_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetDigimon(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAnimatedPortrait::execSetDigimon)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_InSpeciesId);
	P_GET_ENUM(EDigimonVariant,Z_Param_InVariant);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDigimon(Z_Param_InSpeciesId,EDigimonVariant(Z_Param_InVariant));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAnimatedPortrait Function SetDigimon ***********************

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait Function SetFacingLeft ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetFacingLeft_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAnimatedPortrait_eventSetFacingLeft_Parms
	{
		bool bInFaceLeft;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetFacingLeft constinit property declarations *************************
	static void NewProp_bInFaceLeft_SetBit(void* Obj)
	{
		((DigimonVenomNXTAnimatedPortrait_eventSetFacingLeft_Parms*)Obj)->bInFaceLeft = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInFaceLeft;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetFacingLeft constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetFacingLeft Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bInFaceLeft = { "bInFaceLeft", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAnimatedPortrait_eventSetFacingLeft_Parms), &UHT_STATICS::NewProp_bInFaceLeft_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bInFaceLeft,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetFacingLeft Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, nullptr, "SetFacingLeft", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAnimatedPortrait_eventSetFacingLeft_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAnimatedPortrait_eventSetFacingLeft_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetFacingLeft(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAnimatedPortrait::execSetFacingLeft)
{
	P_GET_UBOOL(Z_Param_bInFaceLeft);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetFacingLeft(Z_Param_bInFaceLeft);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAnimatedPortrait Function SetFacingLeft ********************

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Real idle flipbook frames inside UMG; drawing never changes gameplay state. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAnimatedPortrait.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Real idle flipbook frames inside UMG; drawing never changes gameplay state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameImage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IdleFlipbook_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastSprite_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackFlipbook_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FallbackTexture_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedPortrait.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FrameImage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IdleFlipbook;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LastSprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackFlipbook;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FallbackTexture;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTAnimatedPortrait constinit property declarations ***********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("PlayAttack"), .Pointer = &UDigimonVenomNXTAnimatedPortrait::execPlayAttack },
		{ .NameUTF8 = UTF8TEXT("SetDigimon"), .Pointer = &UDigimonVenomNXTAnimatedPortrait::execSetDigimon },
		{ .NameUTF8 = UTF8TEXT("SetFacingLeft"), .Pointer = &UDigimonVenomNXTAnimatedPortrait::execSetFacingLeft },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_PlayAttack, "PlayAttack" }, // 9478811f33b903568acb02254dd7ba70ca6e8371
		{ &Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetDigimon, "SetDigimon" }, // f09c4ce46300648fd4709808e73d061ceb383517
		{ &Z_Construct_UFunction_UDigimonVenomNXTAnimatedPortrait_SetFacingLeft, "SetFacingLeft" }, // bd6401abb986d3560fab292bb07b9f60b0816976
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAnimatedPortrait>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTAnimatedPortrait Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FrameImage = { "FrameImage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, FrameImage), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameImage_MetaData), NewProp_FrameImage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_IdleFlipbook = { "IdleFlipbook", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, IdleFlipbook), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IdleFlipbook_MetaData), NewProp_IdleFlipbook_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LastSprite = { "LastSprite", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, LastSprite), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastSprite_MetaData), NewProp_LastSprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AttackFlipbook = { "AttackFlipbook", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, AttackFlipbook), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackFlipbook_MetaData), NewProp_AttackFlipbook_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FallbackTexture = { "FallbackTexture", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedPortrait, FallbackTexture), Z_Construct_UClass_UTexture2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FallbackTexture_MetaData), NewProp_FallbackTexture_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FrameImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IdleFlipbook,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AttackFlipbook,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FallbackTexture,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTAnimatedPortrait Property Definitions **********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait,
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
static void UDigimonVenomNXTAnimatedPortrait_StaticRegisterNativesUDigimonVenomNXTAnimatedPortrait()
{
	UClass* Class = UDigimonVenomNXTAnimatedPortrait::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait;
UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAnimatedPortrait;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAnimatedPortrait"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.InnerSingleton,
				UDigimonVenomNXTAnimatedPortrait_StaticRegisterNativesUDigimonVenomNXTAnimatedPortrait,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAnimatedPortrait::UDigimonVenomNXTAnimatedPortrait(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAnimatedPortrait);
UDigimonVenomNXTAnimatedPortrait::~UDigimonVenomNXTAnimatedPortrait() {}
// ********** End Class UDigimonVenomNXTAnimatedPortrait *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimatedPortrait_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTAnimatedPortrait, TEXT("UDigimonVenomNXTAnimatedPortrait"), &Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedPortrait, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAnimatedPortrait), 1435640457U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimatedPortrait_h__Script_DigimonVenomNXTRuntime_b111ac11bcb34e952ffdff17d4be071e7aed4e95{
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
