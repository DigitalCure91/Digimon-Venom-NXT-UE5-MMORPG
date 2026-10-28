// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTFarmScene.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTFarmScene() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USceneComponent(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSpriteComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmScene(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmResident(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmScene(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTFarmScene ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTFarmScene_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Private island presentation. Never replicated; residents come only from this owner's profile. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTFarmScene.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmScene.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Private island presentation. Never replicated; residents come only from this owner's profile." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SceneRoot_MetaData[] = {
		{ "Category", "DigimonVenomNXTFarmScene" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmScene.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IslandSprite_MetaData[] = {
		{ "Category", "DigimonVenomNXTFarmScene" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmScene.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OwningController_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmScene.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Residents_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTFarmScene.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTFarmScene constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IslandSprite;
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_OwningController;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Residents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Residents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTFarmScene constinit property declarations ******************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTFarmScene>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTFarmScene Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SceneRoot = { "SceneRoot", nullptr, (EPropertyFlags)0x01440000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmScene, SceneRoot), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SceneRoot_MetaData), NewProp_SceneRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_IslandSprite = { "IslandSprite", nullptr, (EPropertyFlags)0x01440000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmScene, IslandSprite), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IslandSprite_MetaData), NewProp_IslandSprite_MetaData) };
const UECodeGen_Private::FWeakObjectPropertyParams UHT_STATICS::NewProp_OwningController = { "OwningController", nullptr, (EPropertyFlags)0x0044000000002000, UECodeGen_Private::EPropertyGenFlags::WeakObject, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmScene, OwningController), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OwningController_MetaData), NewProp_OwningController_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Residents_Inner = { "Residents", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_ADigimonVenomNXTFarmResident, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Residents = { "Residents", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTFarmScene, Residents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Residents_MetaData), NewProp_Residents_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SceneRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IslandSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OwningController,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Residents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Residents,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTFarmScene Property Definitions *****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTFarmScene,
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
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene;
UClass* Z_Construct_UClass_ADigimonVenomNXTFarmScene(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTFarmScene;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTFarmScene"),
				Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.InnerSingleton,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTFarmScene);
ADigimonVenomNXTFarmScene::~ADigimonVenomNXTFarmScene() {}
// ********** End Class ADigimonVenomNXTFarmScene **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTFarmScene_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTFarmScene, TEXT("ADigimonVenomNXTFarmScene"), &Z_Registration_Info_UClass_ADigimonVenomNXTFarmScene, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTFarmScene), 3600980400U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTFarmScene_h__Script_DigimonVenomNXTRuntime_f00c7d9a39e0783e4f61ec51e6a5996e22eaaa34{
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
