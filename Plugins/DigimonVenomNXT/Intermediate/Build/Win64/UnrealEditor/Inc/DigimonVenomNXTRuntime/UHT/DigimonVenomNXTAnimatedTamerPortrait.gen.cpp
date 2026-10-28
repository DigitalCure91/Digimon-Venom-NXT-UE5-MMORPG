// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAnimatedTamerPortrait.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAnimatedTamerPortrait() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UTexture2D(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbook(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSprite(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UImage(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTAnimatedTamerPortrait ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** One retained, aspect-correct preview of the actual directional field sprites. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAnimatedTamerPortrait.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "One retained, aspect-correct preview of the actual directional field sprites." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameImage_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionFlipbook_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastSprite_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionFrames_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimatedTamerPortrait.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAnimatedTamerPortrait constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FrameImage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DirectionFlipbook;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LastSprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DirectionFrames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DirectionFrames;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTAnimatedTamerPortrait constinit property declarations ******
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAnimatedTamerPortrait>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTAnimatedTamerPortrait Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FrameImage = { "FrameImage", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedTamerPortrait, FrameImage), Z_Construct_UClass_UImage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameImage_MetaData), NewProp_FrameImage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedTamerPortrait, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DirectionFlipbook = { "DirectionFlipbook", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedTamerPortrait, DirectionFlipbook), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionFlipbook_MetaData), NewProp_DirectionFlipbook_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LastSprite = { "LastSprite", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedTamerPortrait, LastSprite), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastSprite_MetaData), NewProp_LastSprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DirectionFrames_Inner = { "DirectionFrames", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_DirectionFrames = { "DirectionFrames", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAnimatedTamerPortrait, DirectionFrames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionFrames_MetaData), NewProp_DirectionFrames_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FrameImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectionFlipbook,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectionFrames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectionFrames,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTAnimatedTamerPortrait Property Definitions *****************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait;
UClass* Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAnimatedTamerPortrait;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAnimatedTamerPortrait"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAnimatedTamerPortrait::UDigimonVenomNXTAnimatedTamerPortrait(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAnimatedTamerPortrait);
UDigimonVenomNXTAnimatedTamerPortrait::~UDigimonVenomNXTAnimatedTamerPortrait() {}
// ********** End Class UDigimonVenomNXTAnimatedTamerPortrait **************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimatedTamerPortrait_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTAnimatedTamerPortrait, TEXT("UDigimonVenomNXTAnimatedTamerPortrait"), &Z_Registration_Info_UClass_UDigimonVenomNXTAnimatedTamerPortrait, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAnimatedTamerPortrait), 4237804033U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimatedTamerPortrait_h__Script_DigimonVenomNXTRuntime_db1545bc5665027604f2c9a6c4bb23bec9591344{
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
