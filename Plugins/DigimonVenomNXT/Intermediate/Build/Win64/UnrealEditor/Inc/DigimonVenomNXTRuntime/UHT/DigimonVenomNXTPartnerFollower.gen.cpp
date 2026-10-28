// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTPartnerFollower.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTPartnerFollower() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_APaperCharacter(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonOwnedPartner(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTPartnerFollower Function BP_OnFollowerIdentityChanged ****
struct DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms
{
	FName NewSpeciesId;
	EDigimonVariant NewVariant;
	int32 NewLevel;
};
static FName NAME_ADigimonVenomNXTPartnerFollower_BP_OnFollowerIdentityChanged = FName(TEXT("BP_OnFollowerIdentityChanged"));
void ADigimonVenomNXTPartnerFollower::BP_OnFollowerIdentityChanged(FName NewSpeciesId, EDigimonVariant NewVariant, int32 NewLevel)
{
	DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms Parms;
	Parms.NewSpeciesId=NewSpeciesId;
	Parms.NewVariant=NewVariant;
	Parms.NewLevel=NewLevel;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPartnerFollower_BP_OnFollowerIdentityChanged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_BP_OnFollowerIdentityChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnFollowerIdentityChanged constinit property declarations **********
	static const UECodeGen_Private::FNamePropertyParams NewProp_NewSpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewVariant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewVariant;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnFollowerIdentityChanged constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnFollowerIdentityChanged Property Definitions *********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NewSpeciesId = { "NewSpeciesId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms, NewSpeciesId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_NewVariant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_NewVariant = { "NewVariant", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms, NewVariant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NewLevel = { "NewLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms, NewLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewSpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewVariant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewVariant,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewLevel,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnFollowerIdentityChanged Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, nullptr, "BP_OnFollowerIdentityChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPartnerFollower_eventBP_OnFollowerIdentityChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_BP_OnFollowerIdentityChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ADigimonVenomNXTPartnerFollower Function BP_OnFollowerIdentityChanged ******

// ********** Begin Class ADigimonVenomNXTPartnerFollower Function InitializeFromPartner ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromPartner_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPartnerFollower_eventInitializeFromPartner_Parms
	{
		ADigimonVenomNXTTamerCharacter* InTamer;
		FDigimonOwnedPartner Partner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Partner_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeFromPartner constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InTamer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Partner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeFromPartner constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeFromPartner Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InTamer = { "InTamer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventInitializeFromPartner_Parms, InTamer), Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Partner = { "Partner", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventInitializeFromPartner_Parms, Partner), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Partner_MetaData), NewProp_Partner_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InTamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partner,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeFromPartner Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, nullptr, "InitializeFromPartner", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPartnerFollower_eventInitializeFromPartner_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPartnerFollower_eventInitializeFromPartner_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromPartner(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPartnerFollower::execInitializeFromPartner)
{
	P_GET_OBJECT(ADigimonVenomNXTTamerCharacter,Z_Param_InTamer);
	P_GET_STRUCT_REF(FDigimonOwnedPartner,Z_Param_Out_Partner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeFromPartner(Z_Param_InTamer,Z_Param_Out_Partner);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPartnerFollower Function InitializeFromPartner *************

// ********** Begin Class ADigimonVenomNXTPartnerFollower Function InitializeFromRival *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromRival_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPartnerFollower_eventInitializeFromRival_Parms
	{
		ADigimonVenomNXTAIRivalAvatar* InRival;
		FDigimonOwnedPartner Partner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Partner_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeFromRival constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InRival;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Partner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeFromRival constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeFromRival Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InRival = { "InRival", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventInitializeFromRival_Parms, InRival), Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Partner = { "Partner", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPartnerFollower_eventInitializeFromRival_Parms, Partner), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Partner_MetaData), NewProp_Partner_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InRival,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partner,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeFromRival Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, nullptr, "InitializeFromRival", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPartnerFollower_eventInitializeFromRival_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPartnerFollower_eventInitializeFromRival_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromRival(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPartnerFollower::execInitializeFromRival)
{
	P_GET_OBJECT(ADigimonVenomNXTAIRivalAvatar,Z_Param_InRival);
	P_GET_STRUCT_REF(FDigimonOwnedPartner,Z_Param_Out_Partner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeFromRival(Z_Param_InRival,Z_Param_Out_Partner);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPartnerFollower Function InitializeFromRival ***************

// ********** Begin Class ADigimonVenomNXTPartnerFollower Function OnRep_Identity ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_OnRep_Identity_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_Identity constinit property declarations ************************
// ********** End Function OnRep_Identity constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, nullptr, "OnRep_Identity", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_OnRep_Identity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPartnerFollower::execOnRep_Identity)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Identity();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPartnerFollower Function OnRep_Identity ********************

// ********** Begin Class ADigimonVenomNXTPartnerFollower Function SnapToTamer *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_SnapToTamer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Immediately places the follower at a safe trailing position and clears stale path history. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Immediately places the follower at a safe trailing position and clears stale path history." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SnapToTamer constinit property declarations ***************************
// ********** End Function SnapToTamer constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, nullptr, "SnapToTamer", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_SnapToTamer(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPartnerFollower::execSnapToTamer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SnapToTamer();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPartnerFollower Function SnapToTamer ***********************

// ********** Begin Class ADigimonVenomNXTPartnerFollower ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTPartnerFollower_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Replicated companion representing the actual first party member of a player or AI rival. */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "DigimonVenomNXTPartnerFollower.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Replicated companion representing the actual first party member of a player or AI rival." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstanceId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpeciesId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Variant_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartnerLevel_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tamer_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalTamer_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set only for rivals; Tamer remains the player-compatible owner reference. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set only for rivals; Tamer remains the player-compatible owner reference." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPartnerFollower.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTPartnerFollower constinit property declarations **********
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Variant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Variant;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PartnerLevel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tamer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RivalTamer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTPartnerFollower constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("InitializeFromPartner"), .Pointer = &ADigimonVenomNXTPartnerFollower::execInitializeFromPartner },
		{ .NameUTF8 = UTF8TEXT("InitializeFromRival"), .Pointer = &ADigimonVenomNXTPartnerFollower::execInitializeFromRival },
		{ .NameUTF8 = UTF8TEXT("OnRep_Identity"), .Pointer = &ADigimonVenomNXTPartnerFollower::execOnRep_Identity },
		{ .NameUTF8 = UTF8TEXT("SnapToTamer"), .Pointer = &ADigimonVenomNXTPartnerFollower::execSnapToTamer },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_BP_OnFollowerIdentityChanged, "BP_OnFollowerIdentityChanged" }, // 239d97abafc8e6f0b464a1372dbc52495b4cfc2f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromPartner, "InitializeFromPartner" }, // d4903a4f452e438110e31e57cff8fb1b3550cc6e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_InitializeFromRival, "InitializeFromRival" }, // 912bf97b871ce9c3c0f9f3f9fa774f530292478a
		{ &Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_OnRep_Identity, "OnRep_Identity" }, // bc18394d449292ccdea54fe26e821cc465597732
		{ &Z_Construct_UFunction_ADigimonVenomNXTPartnerFollower_SnapToTamer, "SnapToTamer" }, // 158abd0e582b66bf91e542b9341579dbfd05e44b
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTPartnerFollower>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTPartnerFollower Property Definitions *********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstanceId_MetaData), NewProp_InstanceId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, SpeciesId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpeciesId_MetaData), NewProp_SpeciesId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Variant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Variant = { "Variant", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, Variant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Variant_MetaData), NewProp_Variant_MetaData) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PartnerLevel = { "PartnerLevel", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, PartnerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartnerLevel_MetaData), NewProp_PartnerLevel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Tamer = { "Tamer", nullptr, (EPropertyFlags)0x0114000000000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, Tamer), Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tamer_MetaData), NewProp_Tamer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RivalTamer = { "RivalTamer", nullptr, (EPropertyFlags)0x0114000000000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, RivalTamer), Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalTamer_MetaData), NewProp_RivalTamer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPartnerFollower, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTPartnerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartnerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalTamer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTPartnerFollower Property Definitions ***********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APaperCharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTPartnerFollower,
	"Game",
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
static void ADigimonVenomNXTPartnerFollower_StaticRegisterNativesADigimonVenomNXTPartnerFollower()
{
	UClass* Class = ADigimonVenomNXTPartnerFollower::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower;
UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTPartnerFollower;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTPartnerFollower"),
				Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.InnerSingleton,
				ADigimonVenomNXTPartnerFollower_StaticRegisterNativesADigimonVenomNXTPartnerFollower,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTPartnerFollower::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_InstanceId(TEXT("InstanceId"));
	static FName Name_SpeciesId(TEXT("SpeciesId"));
	static FName Name_Variant(TEXT("Variant"));
	static FName Name_PartnerLevel(TEXT("PartnerLevel"));
	static FName Name_Tamer(TEXT("Tamer"));
	static FName Name_RivalTamer(TEXT("RivalTamer"));
	const bool bIsValid = true
		&& Name_InstanceId == ClassReps[(int32)ENetFields_Private::InstanceId].Property->GetFName()
		&& Name_SpeciesId == ClassReps[(int32)ENetFields_Private::SpeciesId].Property->GetFName()
		&& Name_Variant == ClassReps[(int32)ENetFields_Private::Variant].Property->GetFName()
		&& Name_PartnerLevel == ClassReps[(int32)ENetFields_Private::PartnerLevel].Property->GetFName()
		&& Name_Tamer == ClassReps[(int32)ENetFields_Private::Tamer].Property->GetFName()
		&& Name_RivalTamer == ClassReps[(int32)ENetFields_Private::RivalTamer].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTPartnerFollower"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTPartnerFollower);
ADigimonVenomNXTPartnerFollower::~ADigimonVenomNXTPartnerFollower() {}
// ********** End Class ADigimonVenomNXTPartnerFollower ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, TEXT("ADigimonVenomNXTPartnerFollower"), &Z_Registration_Info_UClass_ADigimonVenomNXTPartnerFollower, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTPartnerFollower), 2861087618U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPartnerFollower_h__Script_DigimonVenomNXTRuntime_ba67babb466c1646886340ab658b168079dad8a0{
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
