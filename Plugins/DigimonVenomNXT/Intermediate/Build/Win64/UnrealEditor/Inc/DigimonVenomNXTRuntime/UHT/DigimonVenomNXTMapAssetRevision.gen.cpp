// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTMapAssetRevision.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTMapAssetRevision() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UDataAsset(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTMapAssetRevision *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Saved only after the complete canonical map import succeeds. The cooked\n * receipt prevents old or partially imported artwork from being paired with\n * this release's collision registry, even when the image sizes are unchanged.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTMapAssetRevision.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMapAssetRevision.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Saved only after the complete canonical map import succeeds. The cooked\nreceipt prevents old or partially imported artwork from being paired with\nthis release's collision registry, even when the image sizes are unchanged." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Maps" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMapAssetRevision.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapCount_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Maps" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMapAssetRevision.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContentFingerprint_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Maps" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMapAssetRevision.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTMapAssetRevision constinit property declarations *********
	static const UECodeGen_Private::FStrPropertyParams NewProp_Revision;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapCount;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContentFingerprint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTMapAssetRevision constinit property declarations ***********
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTMapAssetRevision>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTMapAssetRevision Property Definitions ********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMapAssetRevision, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapCount = { "MapCount", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMapAssetRevision, MapCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapCount_MetaData), NewProp_MapCount_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ContentFingerprint = { "ContentFingerprint", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMapAssetRevision, ContentFingerprint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContentFingerprint_MetaData), NewProp_ContentFingerprint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContentFingerprint,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTMapAssetRevision Property Definitions **********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDataAsset,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision;
UClass* Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTMapAssetRevision;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTMapAssetRevision"),
				Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTMapAssetRevision::UDigimonVenomNXTMapAssetRevision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTMapAssetRevision);
UDigimonVenomNXTMapAssetRevision::~UDigimonVenomNXTMapAssetRevision() {}
// ********** End Class UDigimonVenomNXTMapAssetRevision *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTMapAssetRevision_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTMapAssetRevision, TEXT("UDigimonVenomNXTMapAssetRevision"), &Z_Registration_Info_UClass_UDigimonVenomNXTMapAssetRevision, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTMapAssetRevision), 3357316499U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTMapAssetRevision_h__Script_DigimonVenomNXTRuntime_95a9761f04a01252ecc781c52c8ae34dd0356cec{
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
