// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAnimationAssets.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAnimationAssets() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UDataAsset(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbook(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperSprite(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTPartnerAnimationSet Function GetBodySizeForFrame *********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_GetBodySizeForFrame_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPartnerAnimationSet_eventGetBodySizeForFrame_Parms
	{
		UPaperSprite* Frame;
		FVector2D ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetBodySizeForFrame constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Frame;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetBodySizeForFrame constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetBodySizeForFrame Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Frame = { "Frame", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerAnimationSet_eventGetBodySizeForFrame_Parms, Frame), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerAnimationSet_eventGetBodySizeForFrame_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Frame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetBodySizeForFrame Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, nullptr, "GetBodySizeForFrame", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPartnerAnimationSet_eventGetBodySizeForFrame_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPartnerAnimationSet_eventGetBodySizeForFrame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_GetBodySizeForFrame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTPartnerAnimationSet::execGetBodySizeForFrame)
{
	P_GET_OBJECT(UPaperSprite,Z_Param_Frame);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector2D*)Z_Param__Result=P_THIS->GetBodySizeForFrame(Z_Param_Frame);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTPartnerAnimationSet Function GetBodySizeForFrame ***********

// ********** Begin Class UDigimonVenomNXTPartnerAnimationSet Function ShouldMirrorLeftFrame *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_ShouldMirrorLeftFrame_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms
	{
		UPaperSprite* Frame;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShouldMirrorLeftFrame constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Frame;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ShouldMirrorLeftFrame constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ShouldMirrorLeftFrame Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Frame = { "Frame", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms, Frame), Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Frame,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ShouldMirrorLeftFrame Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, nullptr, "ShouldMirrorLeftFrame", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPartnerAnimationSet_eventShouldMirrorLeftFrame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_ShouldMirrorLeftFrame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTPartnerAnimationSet::execShouldMirrorLeftFrame)
{
	P_GET_OBJECT(UPaperSprite,Z_Param_Frame);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ShouldMirrorLeftFrame(Z_Param_Frame);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTPartnerAnimationSet Function ShouldMirrorLeftFrame *********

// ********** Begin Class UDigimonVenomNXTPartnerAnimationSet **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTAnimationAssets.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Idle_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkLeft_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkRight_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attack_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IdleLeft_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Opposite-facing poses supplied by the Digimon source catalog. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Opposite-facing poses supplied by the Digimon source catalog." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackLeft_MetaData[] = {
		{ "Category", "DigimonVenomNXTPartnerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasAuthoredLeftFrames_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AuthoredLeftSprites_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Only these individual source frames already face left. Partial mappings\n     * retain standard mirroring for the remaining frames in the same sequence. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Only these individual source frames already face left. Partial mappings\nretain standard mirroring for the remaining frames in the same sequence." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NativeFrameBodies_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unpadded source body dimensions for each frame, used for native sizing. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unpadded source body dimensions for each frame, used for native sizing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NativeBodySize_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native idle body dimensions before aura padding or runtime presentation scale. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native idle body dimensions before aura padding or runtime presentation scale." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FootOrigins_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Authored contact point in normalized frame coordinates, in this order:\n     * IdleA, IdleB, WalkRight, WalkLeft, AttackA, AttackB. Supplied by the native content manifest.\n     * Cooked presentation metadata; does not alter shared Paper2D sprite pivots.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Authored contact point in normalized frame coordinates, in this order:\nIdleA, IdleB, WalkRight, WalkLeft, AttackA, AttackB. Supplied by the native content manifest.\nCooked presentation metadata; does not alter shared Paper2D sprite pivots." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTPartnerAnimationSet constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Idle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WalkLeft;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WalkRight;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Attack;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IdleLeft;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackLeft;
	static void NewProp_bHasAuthoredLeftFrames_SetBit(void* Obj)
	{
		((UDigimonVenomNXTPartnerAnimationSet*)Obj)->bHasAuthoredLeftFrames = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasAuthoredLeftFrames;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AuthoredLeftSprites_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AuthoredLeftSprites;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NativeFrameBodies_ValueProp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NativeFrameBodies_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_NativeFrameBodies;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NativeBodySize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FootOrigins_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FootOrigins;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTPartnerAnimationSet constinit property declarations ********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetBodySizeForFrame"), .Pointer = &UDigimonVenomNXTPartnerAnimationSet::execGetBodySizeForFrame },
		{ .NameUTF8 = UTF8TEXT("ShouldMirrorLeftFrame"), .Pointer = &UDigimonVenomNXTPartnerAnimationSet::execShouldMirrorLeftFrame },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_GetBodySizeForFrame, "GetBodySizeForFrame" }, // 5c35bfa02fba207d88140343be8d38bf2cb9bc88
		{ &Z_Construct_UFunction_UDigimonVenomNXTPartnerAnimationSet_ShouldMirrorLeftFrame, "ShouldMirrorLeftFrame" }, // cca0f94c894e9e6a2241bfbdd5fe856106d47731
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTPartnerAnimationSet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTPartnerAnimationSet Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Idle = { "Idle", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, Idle), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Idle_MetaData), NewProp_Idle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_WalkLeft = { "WalkLeft", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, WalkLeft), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkLeft_MetaData), NewProp_WalkLeft_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_WalkRight = { "WalkRight", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, WalkRight), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkRight_MetaData), NewProp_WalkRight_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Attack = { "Attack", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, Attack), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attack_MetaData), NewProp_Attack_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_IdleLeft = { "IdleLeft", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, IdleLeft), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IdleLeft_MetaData), NewProp_IdleLeft_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AttackLeft = { "AttackLeft", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, AttackLeft), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackLeft_MetaData), NewProp_AttackLeft_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bHasAuthoredLeftFrames = { "bHasAuthoredLeftFrames", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTPartnerAnimationSet), &UHT_STATICS::NewProp_bHasAuthoredLeftFrames_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasAuthoredLeftFrames_MetaData), NewProp_bHasAuthoredLeftFrames_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AuthoredLeftSprites_Inner = { "AuthoredLeftSprites", nullptr, (EPropertyFlags)0x0104000000020000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_AuthoredLeftSprites = { "AuthoredLeftSprites", nullptr, (EPropertyFlags)0x0114000000020015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, AuthoredLeftSprites), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AuthoredLeftSprites_MetaData), NewProp_AuthoredLeftSprites_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NativeFrameBodies_ValueProp = { "NativeFrameBodies", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NativeFrameBodies_Key_KeyProp = { "NativeFrameBodies_Key", nullptr, (EPropertyFlags)0x0004000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPaperSprite, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_NativeFrameBodies = { "NativeFrameBodies", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, NativeFrameBodies), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NativeFrameBodies_MetaData), NewProp_NativeFrameBodies_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NativeBodySize = { "NativeBodySize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, NativeBodySize), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NativeBodySize_MetaData), NewProp_NativeBodySize_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FootOrigins_Inner = { "FootOrigins", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_FootOrigins = { "FootOrigins", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTPartnerAnimationSet, FootOrigins), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FootOrigins_MetaData), NewProp_FootOrigins_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Idle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WalkLeft,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WalkRight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Attack,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IdleLeft,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AttackLeft,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bHasAuthoredLeftFrames,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AuthoredLeftSprites_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AuthoredLeftSprites,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NativeFrameBodies_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NativeFrameBodies_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NativeFrameBodies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NativeBodySize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FootOrigins_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FootOrigins,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTPartnerAnimationSet Property Definitions *******************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDataAsset,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTPartnerAnimationSet_StaticRegisterNativesUDigimonVenomNXTPartnerAnimationSet()
{
	UClass* Class = UDigimonVenomNXTPartnerAnimationSet::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet;
UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTPartnerAnimationSet;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTPartnerAnimationSet"),
				Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.InnerSingleton,
				UDigimonVenomNXTPartnerAnimationSet_StaticRegisterNativesUDigimonVenomNXTPartnerAnimationSet,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTPartnerAnimationSet::UDigimonVenomNXTPartnerAnimationSet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTPartnerAnimationSet);
UDigimonVenomNXTPartnerAnimationSet::~UDigimonVenomNXTPartnerAnimationSet() {}
// ********** End Class UDigimonVenomNXTPartnerAnimationSet ****************************************

// ********** Begin Class UDigimonVenomNXTTamerAnimationSet Function GetForFacing ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTamerAnimationSet_GetForFacing_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTTamerAnimationSet_eventGetForFacing_Parms
	{
		EDigimonFacing Facing;
		UPaperFlipbook* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetForFacing constinit property declarations **************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Facing_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Facing;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetForFacing constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetForFacing Property Definitions *************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Facing_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Facing = { "Facing", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerAnimationSet_eventGetForFacing_Parms, Facing), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing, METADATA_PARAMS(0, nullptr) }; // 3468c7b186f8660ca8fa082482b86445185fe59f
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerAnimationSet_eventGetForFacing_Parms, ReturnValue), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Facing_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Facing,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetForFacing Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet, nullptr, "GetForFacing", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTTamerAnimationSet_eventGetForFacing_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTTamerAnimationSet_eventGetForFacing_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTamerAnimationSet_GetForFacing(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTamerAnimationSet::execGetForFacing)
{
	P_GET_ENUM(EDigimonFacing,Z_Param_Facing);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UPaperFlipbook**)Z_Param__Result=P_THIS->GetForFacing(EDigimonFacing(Z_Param_Facing));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTamerAnimationSet Function GetForFacing ********************

// ********** Begin Class UDigimonVenomNXTTamerAnimationSet ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTAnimationAssets.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Down_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DownLeft_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Left_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpLeft_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Up_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpRight_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Right_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DownRight_MetaData[] = {
		{ "Category", "DigimonVenomNXTTamerAnimationSet" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayScale_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Browser-source display multiplier; applied by tamer presentation. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Browser-source display multiplier; applied by tamer presentation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NativeBodySize_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Animation" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAnimationAssets.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTTamerAnimationSet constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Down;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DownLeft;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Left;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UpLeft;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Up;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UpRight;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Right;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DownRight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DisplayScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NativeBodySize;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTTamerAnimationSet constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetForFacing"), .Pointer = &UDigimonVenomNXTTamerAnimationSet::execGetForFacing },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTTamerAnimationSet_GetForFacing, "GetForFacing" }, // c4c49619f0e68f06bb5d6373ab72308108781dd3
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTTamerAnimationSet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTTamerAnimationSet Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Down = { "Down", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, Down), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Down_MetaData), NewProp_Down_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DownLeft = { "DownLeft", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, DownLeft), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DownLeft_MetaData), NewProp_DownLeft_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Left = { "Left", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, Left), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Left_MetaData), NewProp_Left_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UpLeft = { "UpLeft", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, UpLeft), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpLeft_MetaData), NewProp_UpLeft_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Up = { "Up", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, Up), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Up_MetaData), NewProp_Up_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UpRight = { "UpRight", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, UpRight), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpRight_MetaData), NewProp_UpRight_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, Right), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Right_MetaData), NewProp_Right_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DownRight = { "DownRight", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, DownRight), Z_Construct_UClass_UPaperFlipbook, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DownRight_MetaData), NewProp_DownRight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DisplayScale = { "DisplayScale", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, DisplayScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayScale_MetaData), NewProp_DisplayScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NativeBodySize = { "NativeBodySize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTamerAnimationSet, NativeBodySize), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NativeBodySize_MetaData), NewProp_NativeBodySize_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Down,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DownLeft,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Left,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UpLeft,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Up,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UpRight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DownRight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NativeBodySize,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTTamerAnimationSet Property Definitions *********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UDataAsset,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTTamerAnimationSet_StaticRegisterNativesUDigimonVenomNXTTamerAnimationSet()
{
	UClass* Class = UDigimonVenomNXTTamerAnimationSet::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet;
UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTTamerAnimationSet;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTTamerAnimationSet"),
				Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.InnerSingleton,
				UDigimonVenomNXTTamerAnimationSet_StaticRegisterNativesUDigimonVenomNXTTamerAnimationSet,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTTamerAnimationSet::UDigimonVenomNXTTamerAnimationSet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTTamerAnimationSet);
UDigimonVenomNXTTamerAnimationSet::~UDigimonVenomNXTTamerAnimationSet() {}
// ********** End Class UDigimonVenomNXTTamerAnimationSet ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimationAssets_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, TEXT("UDigimonVenomNXTPartnerAnimationSet"), &Z_Registration_Info_UClass_UDigimonVenomNXTPartnerAnimationSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTPartnerAnimationSet), 1938889477U) },
		{ Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet, TEXT("UDigimonVenomNXTTamerAnimationSet"), &Z_Registration_Info_UClass_UDigimonVenomNXTTamerAnimationSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTTamerAnimationSet), 1658104201U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAnimationAssets_h__Script_DigimonVenomNXTRuntime_8ccffa4a4b3ae00b8f2119cbf123157db25ec057{
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
