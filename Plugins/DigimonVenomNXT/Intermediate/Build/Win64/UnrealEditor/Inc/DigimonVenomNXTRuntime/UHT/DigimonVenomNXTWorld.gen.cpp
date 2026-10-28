// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTWorld.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTWorld() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AController(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USceneComponent(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSprite(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSpriteComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTMapZone(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonRegion(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTMapZone(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTMapZone Function ApplyMapPresentation ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTMapZone_ApplyMapPresentation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyMapPresentation constinit property declarations ******************
// ********** End Function ApplyMapPresentation constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTMapZone, nullptr, "ApplyMapPresentation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTMapZone_ApplyMapPresentation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTMapZone::execApplyMapPresentation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyMapPresentation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTMapZone Function ApplyMapPresentation **********************

// ********** Begin Class ADigimonVenomNXTMapZone Function GetPlayableHalfExtents ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayableHalfExtents_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTMapZone_eventGetPlayableHalfExtents_Parms
	{
		FVector2D ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPlayableHalfExtents constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPlayableHalfExtents constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPlayableHalfExtents Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTMapZone_eventGetPlayableHalfExtents_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPlayableHalfExtents Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTMapZone, nullptr, "GetPlayableHalfExtents", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTMapZone_eventGetPlayableHalfExtents_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTMapZone_eventGetPlayableHalfExtents_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayableHalfExtents(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTMapZone::execGetPlayableHalfExtents)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector2D*)Z_Param__Result=P_THIS->GetPlayableHalfExtents();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTMapZone Function GetPlayableHalfExtents ********************

// ********** Begin Class ADigimonVenomNXTMapZone Function GetPlayerSpawnLocation ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayerSpawnLocation_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTMapZone_eventGetPlayerSpawnLocation_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPlayerSpawnLocation constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPlayerSpawnLocation constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPlayerSpawnLocation Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTMapZone_eventGetPlayerSpawnLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPlayerSpawnLocation Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTMapZone, nullptr, "GetPlayerSpawnLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTMapZone_eventGetPlayerSpawnLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTMapZone_eventGetPlayerSpawnLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayerSpawnLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTMapZone::execGetPlayerSpawnLocation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetPlayerSpawnLocation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTMapZone Function GetPlayerSpawnLocation ********************

// ********** Begin Class ADigimonVenomNXTMapZone Function GetRuntimeMapId *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetRuntimeMapId_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTMapZone_eventGetRuntimeMapId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Canonical map id recovered from the generated actor name/location when legacy serialized data is stale. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Canonical map id recovered from the generated actor name/location when legacy serialized data is stale." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetRuntimeMapId constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRuntimeMapId constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRuntimeMapId Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTMapZone_eventGetRuntimeMapId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRuntimeMapId Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTMapZone, nullptr, "GetRuntimeMapId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTMapZone_eventGetRuntimeMapId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTMapZone_eventGetRuntimeMapId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetRuntimeMapId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTMapZone::execGetRuntimeMapId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetRuntimeMapId();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTMapZone Function GetRuntimeMapId ***************************

// ********** Begin Class ADigimonVenomNXTMapZone Function SetLocalPresentationActive **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTMapZone_SetLocalPresentationActive_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTMapZone_eventSetLocalPresentationActive_Parms
	{
		bool bActive;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Client-local visual isolation: only the local player's current habitat should render. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Client-local visual isolation: only the local player's current habitat should render." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetLocalPresentationActive constinit property declarations ************
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((DigimonVenomNXTMapZone_eventSetLocalPresentationActive_Parms*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetLocalPresentationActive constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetLocalPresentationActive Property Definitions ***********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTMapZone_eventSetLocalPresentationActive_Parms), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetLocalPresentationActive Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTMapZone, nullptr, "SetLocalPresentationActive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTMapZone_eventSetLocalPresentationActive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTMapZone_eventSetLocalPresentationActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTMapZone_SetLocalPresentationActive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTMapZone::execSetLocalPresentationActive)
{
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetLocalPresentationActive(Z_Param_bActive);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTMapZone Function SetLocalPresentationActive ****************

// ********** Begin Class ADigimonVenomNXTMapZone **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTMapZone_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * One walkable handheld-RPG-style habitat inside the shared PublicWorld.\n * The imported 2D map artwork is laid flat on XY, normalized to a consistent\n * world size. The registered source-resolution mask is the sole movement\n * boundary; old rectangular wall components are retained with collision disabled.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTWorld.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "One walkable handheld-RPG-style habitat inside the shared PublicWorld.\nThe imported 2D map artwork is laid flat on XY, normalized to a consistent\nworld size. The registered source-resolution mask is the sole movement\nboundary; old rectangular wall components are retained with collision disabled." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundSprite_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayBounds_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerSpawn_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NorthWall_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map|Collision" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SouthWall_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map|Collision" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EastWall_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map|Collision" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WestWall_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map|Collision" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ClampMax", "500" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinLevel_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ClampMax", "99" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxLevel_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ClampMax", "99" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapSprite_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Compatibility-only transient reference; public zones never retain map textures. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Compatibility-only transient reference; public zones never retain map textures." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceImageSize_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native image geometry retained for editor bounds without loading artwork. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native image geometry retained for editor bounds without loading artwork." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SafeSpawnUV_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WildSpecies_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditorGroundPreview_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditorForegroundPreview_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTMapZone constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GroundSprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayBounds;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerSpawn;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NorthWall;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SouthWall;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EastWall;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WestWall;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Region_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Region;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MinLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxLevel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MapSprite;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceImageSize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SafeSpawnUV;
	static const UECodeGen_Private::FNamePropertyParams NewProp_WildSpecies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_WildSpecies;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditorGroundPreview;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditorForegroundPreview;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTMapZone constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyMapPresentation"), .Pointer = &ADigimonVenomNXTMapZone::execApplyMapPresentation },
		{ .NameUTF8 = UTF8TEXT("GetPlayableHalfExtents"), .Pointer = &ADigimonVenomNXTMapZone::execGetPlayableHalfExtents },
		{ .NameUTF8 = UTF8TEXT("GetPlayerSpawnLocation"), .Pointer = &ADigimonVenomNXTMapZone::execGetPlayerSpawnLocation },
		{ .NameUTF8 = UTF8TEXT("GetRuntimeMapId"), .Pointer = &ADigimonVenomNXTMapZone::execGetRuntimeMapId },
		{ .NameUTF8 = UTF8TEXT("SetLocalPresentationActive"), .Pointer = &ADigimonVenomNXTMapZone::execSetLocalPresentationActive },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTMapZone_ApplyMapPresentation, "ApplyMapPresentation" }, // fc99696863790dff8a9e2f940e9e5326f050683a
		{ &Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayableHalfExtents, "GetPlayableHalfExtents" }, // bfa818c176801f4ad744345846cda5da91b171e9
		{ &Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetPlayerSpawnLocation, "GetPlayerSpawnLocation" }, // d4899de8bc3ce2f283b6a7952e58219826109abb
		{ &Z_Construct_UFunction_ADigimonVenomNXTMapZone_GetRuntimeMapId, "GetRuntimeMapId" }, // 0bd47772ecde13e4b08eb73ba5ecb1c44ffaa728
		{ &Z_Construct_UFunction_ADigimonVenomNXTMapZone_SetLocalPresentationActive, "SetLocalPresentationActive" }, // c7940ce1a8148dd0f84268dd5ffb7e863e5701ae
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTMapZone>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTMapZone Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, Root), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_GroundSprite = { "GroundSprite", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, GroundSprite), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundSprite_MetaData), NewProp_GroundSprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayBounds = { "PlayBounds", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, PlayBounds), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayBounds_MetaData), NewProp_PlayBounds_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerSpawn = { "PlayerSpawn", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, PlayerSpawn), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerSpawn_MetaData), NewProp_PlayerSpawn_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NorthWall = { "NorthWall", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, NorthWall), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NorthWall_MetaData), NewProp_NorthWall_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SouthWall = { "SouthWall", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, SouthWall), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SouthWall_MetaData), NewProp_SouthWall_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EastWall = { "EastWall", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, EastWall), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EastWall_MetaData), NewProp_EastWall_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_WestWall = { "WestWall", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, WestWall), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WestWall_MetaData), NewProp_WestWall_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, MapId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapId_MetaData), NewProp_MapId_MetaData) };
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Region_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, Region), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonRegion, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Region_MetaData), NewProp_Region_MetaData) }; // 3b3ed7ae22ef1d0a55f79b9795a7ce30e2777488
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MinLevel = { "MinLevel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, MinLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinLevel_MetaData), NewProp_MinLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxLevel = { "MaxLevel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, MaxLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxLevel_MetaData), NewProp_MaxLevel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MapSprite = { "MapSprite", nullptr, (EPropertyFlags)0x0114000000002014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, MapSprite), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapSprite_MetaData), NewProp_MapSprite_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SourceImageSize = { "SourceImageSize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, SourceImageSize), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceImageSize_MetaData), NewProp_SourceImageSize_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SafeSpawnUV = { "SafeSpawnUV", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, SafeSpawnUV), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SafeSpawnUV_MetaData), NewProp_SafeSpawnUV_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_WildSpecies_Inner = { "WildSpecies", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_WildSpecies = { "WildSpecies", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, WildSpecies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WildSpecies_MetaData), NewProp_WildSpecies_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EditorGroundPreview = { "EditorGroundPreview", nullptr, (EPropertyFlags)0x0144000800282008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, EditorGroundPreview), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditorGroundPreview_MetaData), NewProp_EditorGroundPreview_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EditorForegroundPreview = { "EditorForegroundPreview", nullptr, (EPropertyFlags)0x0144000800282008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTMapZone, EditorForegroundPreview), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditorForegroundPreview_MetaData), NewProp_EditorForegroundPreview_MetaData) };
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GroundSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerSpawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NorthWall,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SouthWall,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EastWall,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WestWall,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Region_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Region,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SourceImageSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SafeSpawnUV,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WildSpecies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WildSpecies,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EditorGroundPreview,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EditorForegroundPreview,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTMapZone Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTMapZone,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADigimonVenomNXTMapZone_StaticRegisterNativesADigimonVenomNXTMapZone()
{
	UClass* Class = ADigimonVenomNXTMapZone::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTMapZone;
UClass* Z_Construct_UClass_ADigimonVenomNXTMapZone(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTMapZone;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTMapZone"),
				Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.InnerSingleton,
				ADigimonVenomNXTMapZone_StaticRegisterNativesADigimonVenomNXTMapZone,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTMapZone.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTMapZone);
ADigimonVenomNXTMapZone::~ADigimonVenomNXTMapZone() {}
// ********** End Class ADigimonVenomNXTMapZone ****************************************************

// ********** Begin Class ADigimonVenomNXTLocalMapRenderer *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Client-local map renderer. PublicWorld keeps its server-side zone actors for\n * travel/bounds only; each local player renders exactly one selected habitat here.\n * This deliberately avoids relying on serialized per-zone GroundSprite state.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTWorld.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Client-local map renderer. PublicWorld keeps its server-side zone actors for\ntravel/bounds only; each local player renders exactly one selected habitat here.\nThis deliberately avoids relying on serialized per-zone GroundSprite state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundSprite_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ForegroundSprite_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Map" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RuntimeFallbackSprite_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTLocalMapRenderer constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GroundSprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ForegroundSprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RuntimeFallbackSprite;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTLocalMapRenderer constinit property declarations ***********
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTLocalMapRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTLocalMapRenderer Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTLocalMapRenderer, Root), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_GroundSprite = { "GroundSprite", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTLocalMapRenderer, GroundSprite), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundSprite_MetaData), NewProp_GroundSprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ForegroundSprite = { "ForegroundSprite", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTLocalMapRenderer, ForegroundSprite), Z_Construct_UClass_UPaperSpriteComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ForegroundSprite_MetaData), NewProp_ForegroundSprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RuntimeFallbackSprite = { "RuntimeFallbackSprite", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTLocalMapRenderer, RuntimeFallbackSprite), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RuntimeFallbackSprite_MetaData), NewProp_RuntimeFallbackSprite_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GroundSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ForegroundSprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RuntimeFallbackSprite,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTLocalMapRenderer Property Definitions **********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer,
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
	0x009000ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer;
UClass* Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTLocalMapRenderer;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTLocalMapRenderer"),
				Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.InnerSingleton,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTLocalMapRenderer);
ADigimonVenomNXTLocalMapRenderer::~ADigimonVenomNXTLocalMapRenderer() {}
// ********** End Class ADigimonVenomNXTLocalMapRenderer *******************************************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem Function FindMapZone **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_FindMapZone_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldSubsystem_eventFindMapZone_Parms
	{
		int32 MapId;
		ADigimonVenomNXTMapZone* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindMapZone constinit property declarations ***************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindMapZone constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindMapZone Property Definitions **************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventFindMapZone_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventFindMapZone_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTMapZone, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function FindMapZone Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, nullptr, "FindMapZone", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventFindMapZone_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventFindMapZone_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_FindMapZone(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldSubsystem::execFindMapZone)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTMapZone**)Z_Param__Result=P_THIS->FindMapZone(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldSubsystem Function FindMapZone ************************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem Function GetAllMapZones *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_GetAllMapZones_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldSubsystem_eventGetAllMapZones_Parms
	{
		TArray<ADigimonVenomNXTMapZone*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllMapZones constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllMapZones constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllMapZones Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_ADigimonVenomNXTMapZone, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventGetAllMapZones_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllMapZones Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, nullptr, "GetAllMapZones", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventGetAllMapZones_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventGetAllMapZones_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_GetAllMapZones(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldSubsystem::execGetAllMapZones)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<ADigimonVenomNXTMapZone*>*)Z_Param__Result=P_THIS->GetAllMapZones();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldSubsystem Function GetAllMapZones *********************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem Function IsWorldLocationWalkable **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_IsWorldLocationWalkable_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms
	{
		int32 MapId;
		FVector WorldLocation;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World|Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Collision-mask driven walkability query. Hidden collision data only; masks are never rendered. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Collision-mask driven walkability query. Hidden collision data only; masks are never rendered." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsWorldLocationWalkable constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldLocation;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsWorldLocationWalkable constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsWorldLocationWalkable Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldLocation = { "WorldLocation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms, WorldLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldLocation_MetaData), NewProp_WorldLocation_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsWorldLocationWalkable Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, nullptr, "IsWorldLocationWalkable", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventIsWorldLocationWalkable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_IsWorldLocationWalkable(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldSubsystem::execIsWorldLocationWalkable)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_WorldLocation);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsWorldLocationWalkable(Z_Param_MapId,Z_Param_Out_WorldLocation);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldSubsystem Function IsWorldLocationWalkable ************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem Function RollWildVariant ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_RollWildVariant_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldSubsystem_eventRollWildVariant_Parms
	{
		EDigimonVariant ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Wild" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RollWildVariant constinit property declarations ***********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RollWildVariant constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RollWildVariant Property Definitions **********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventRollWildVariant_Parms, ReturnValue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RollWildVariant Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, nullptr, "RollWildVariant", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventRollWildVariant_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventRollWildVariant_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_RollWildVariant(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldSubsystem::execRollWildVariant)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EDigimonVariant*)Z_Param__Result=P_THIS->RollWildVariant();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldSubsystem Function RollWildVariant ********************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem Function TravelPlayerToMap ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_TravelPlayerToMap_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms
	{
		AController* Controller;
		int32 MapId;
		FString OutError;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function TravelPlayerToMap constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function TravelPlayerToMap constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function TravelPlayerToMap Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms, Controller), Z_Construct_UClass_AController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function TravelPlayerToMap Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, nullptr, "TravelPlayerToMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTWorldSubsystem_eventTravelPlayerToMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_TravelPlayerToMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTWorldSubsystem::execTravelPlayerToMap)
{
	P_GET_OBJECT(AController,Z_Param_Controller);
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->TravelPlayerToMap(Z_Param_Controller,Z_Param_MapId,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTWorldSubsystem Function TravelPlayerToMap ******************

// ********** Begin Class UDigimonVenomNXTWorldSubsystem *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTWorld.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTWorld.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTWorldSubsystem constinit property declarations ***********
// ********** End Class UDigimonVenomNXTWorldSubsystem constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("FindMapZone"), .Pointer = &UDigimonVenomNXTWorldSubsystem::execFindMapZone },
		{ .NameUTF8 = UTF8TEXT("GetAllMapZones"), .Pointer = &UDigimonVenomNXTWorldSubsystem::execGetAllMapZones },
		{ .NameUTF8 = UTF8TEXT("IsWorldLocationWalkable"), .Pointer = &UDigimonVenomNXTWorldSubsystem::execIsWorldLocationWalkable },
		{ .NameUTF8 = UTF8TEXT("RollWildVariant"), .Pointer = &UDigimonVenomNXTWorldSubsystem::execRollWildVariant },
		{ .NameUTF8 = UTF8TEXT("TravelPlayerToMap"), .Pointer = &UDigimonVenomNXTWorldSubsystem::execTravelPlayerToMap },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_FindMapZone, "FindMapZone" }, // 47bb79a215cff81733186e5f6113648d37996202
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_GetAllMapZones, "GetAllMapZones" }, // 5c1dc53839e053afcfca567d3ea9c7629aecde3c
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_IsWorldLocationWalkable, "IsWorldLocationWalkable" }, // 3c1f210f7996adffb54d3098ed79c164721cd2db
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_RollWildVariant, "RollWildVariant" }, // 7797b91de0b6b5689afb86dba22adc0928cc27fa
		{ &Z_Construct_UFunction_UDigimonVenomNXTWorldSubsystem_TravelPlayerToMap, "TravelPlayerToMap" }, // a82570a049341175b25d64639e6db0db5061448e
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTWorldSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTWorldSubsystem_StaticRegisterNativesUDigimonVenomNXTWorldSubsystem()
{
	UClass* Class = UDigimonVenomNXTWorldSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTWorldSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTWorldSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.InnerSingleton,
				UDigimonVenomNXTWorldSubsystem_StaticRegisterNativesUDigimonVenomNXTWorldSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTWorldSubsystem::UDigimonVenomNXTWorldSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTWorldSubsystem);
UDigimonVenomNXTWorldSubsystem::~UDigimonVenomNXTWorldSubsystem() {}
// ********** End Class UDigimonVenomNXTWorldSubsystem *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTWorld_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTMapZone, TEXT("ADigimonVenomNXTMapZone"), &Z_Registration_Info_UClass_ADigimonVenomNXTMapZone, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTMapZone), 3393387206U) },
		{ Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer, TEXT("ADigimonVenomNXTLocalMapRenderer"), &Z_Registration_Info_UClass_ADigimonVenomNXTLocalMapRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTLocalMapRenderer), 1579058007U) },
		{ Z_Construct_UClass_UDigimonVenomNXTWorldSubsystem, TEXT("UDigimonVenomNXTWorldSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTWorldSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTWorldSubsystem), 1729452255U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTWorld_h__Script_DigimonVenomNXTRuntime_a7bf437136603ed3b98a089bcdd2d247afa2a089{
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
