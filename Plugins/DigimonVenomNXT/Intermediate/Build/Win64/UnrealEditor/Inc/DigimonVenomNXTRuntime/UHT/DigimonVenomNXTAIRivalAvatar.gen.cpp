// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAIRivalAvatar.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAIRivalAvatar() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FBox(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USceneComponent(ETypeConstructPhase);
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbookComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonOwnedPartner(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTNameplateComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Function BP_OnRivalIdentityChanged *********
struct DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms
{
	FString NewRivalId;
	FString NewDisplayName;
	int32 NewLevel;
};
static FName NAME_ADigimonVenomNXTAIRivalAvatar_BP_OnRivalIdentityChanged = FName(TEXT("BP_OnRivalIdentityChanged"));
void ADigimonVenomNXTAIRivalAvatar::BP_OnRivalIdentityChanged(const FString& NewRivalId, const FString& NewDisplayName, int32 NewLevel)
{
	DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms Parms;
	Parms.NewRivalId=NewRivalId;
	Parms.NewDisplayName=NewDisplayName;
	Parms.NewLevel=NewLevel;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTAIRivalAvatar_BP_OnRivalIdentityChanged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_BP_OnRivalIdentityChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewDisplayName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnRivalIdentityChanged constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_NewRivalId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NewDisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnRivalIdentityChanged constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnRivalIdentityChanged Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_NewRivalId = { "NewRivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms, NewRivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRivalId_MetaData), NewProp_NewRivalId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_NewDisplayName = { "NewDisplayName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms, NewDisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewDisplayName_MetaData), NewProp_NewDisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NewLevel = { "NewLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms, NewLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewRivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewDisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewLevel,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnRivalIdentityChanged Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, nullptr, "BP_OnRivalIdentityChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTAIRivalAvatar_eventBP_OnRivalIdentityChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_BP_OnRivalIdentityChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ADigimonVenomNXTAIRivalAvatar Function BP_OnRivalIdentityChanged ***********

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Function InitializeAvatar ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_InitializeAvatar_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms
	{
		FString InRivalId;
		FString InDisplayName;
		int32 InMapId;
		int32 InTamerLevel;
		FBox InPatrolBounds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InRivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InDisplayName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InPatrolBounds_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeAvatar constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_InRivalId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InDisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InMapId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InTamerLevel;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InPatrolBounds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeAvatar constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeAvatar Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_InRivalId = { "InRivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms, InRivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InRivalId_MetaData), NewProp_InRivalId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_InDisplayName = { "InDisplayName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms, InDisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InDisplayName_MetaData), NewProp_InDisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_InMapId = { "InMapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms, InMapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_InTamerLevel = { "InTamerLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms, InTamerLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InPatrolBounds = { "InPatrolBounds", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms, InPatrolBounds), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InPatrolBounds_MetaData), NewProp_InPatrolBounds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InRivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InDisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InMapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InTamerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InPatrolBounds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeAvatar Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, nullptr, "InitializeAvatar", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventInitializeAvatar_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_InitializeAvatar(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTAIRivalAvatar::execInitializeAvatar)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_InRivalId);
	P_GET_PROPERTY(FStrProperty,Z_Param_InDisplayName);
	P_GET_PROPERTY(FIntProperty,Z_Param_InMapId);
	P_GET_PROPERTY(FIntProperty,Z_Param_InTamerLevel);
	P_GET_STRUCT_REF(FBox,Z_Param_Out_InPatrolBounds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeAvatar(Z_Param_InRivalId,Z_Param_InDisplayName,Z_Param_InMapId,Z_Param_InTamerLevel,Z_Param_Out_InPatrolBounds);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTAIRivalAvatar Function InitializeAvatar ********************

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Function IsForRival ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_IsForRival_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms
	{
		FString InRivalId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InRivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsForRival constinit property declarations ****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_InRivalId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsForRival constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsForRival Property Definitions ***************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_InRivalId = { "InRivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms, InRivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InRivalId_MetaData), NewProp_InRivalId_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InRivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsForRival Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, nullptr, "IsForRival", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventIsForRival_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_IsForRival(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTAIRivalAvatar::execIsForRival)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_InRivalId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsForRival(Z_Param_InRivalId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTAIRivalAvatar Function IsForRival **************************

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Function OnRep_Identity ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_OnRep_Identity_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_Identity constinit property declarations ************************
// ********** End Function OnRep_Identity constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, nullptr, "OnRep_Identity", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_OnRep_Identity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTAIRivalAvatar::execOnRep_Identity)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Identity();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTAIRivalAvatar Function OnRep_Identity **********************

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Function RefreshLeaderFollower *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_RefreshLeaderFollower_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAIRivalAvatar_eventRefreshLeaderFollower_Parms
	{
		FDigimonOwnedPartner Partner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pass an invalid partner to remove the companion when the party is empty. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pass an invalid partner to remove the companion when the party is empty." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Partner_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshLeaderFollower constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Partner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RefreshLeaderFollower constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RefreshLeaderFollower Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Partner = { "Partner", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAIRivalAvatar_eventRefreshLeaderFollower_Parms, Partner), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Partner_MetaData), NewProp_Partner_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partner,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RefreshLeaderFollower Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, nullptr, "RefreshLeaderFollower", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventRefreshLeaderFollower_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAIRivalAvatar_eventRefreshLeaderFollower_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_RefreshLeaderFollower(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTAIRivalAvatar::execRefreshLeaderFollower)
{
	P_GET_STRUCT_REF(FDigimonOwnedPartner,Z_Param_Out_Partner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshLeaderFollower(Z_Param_Out_Partner);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTAIRivalAvatar Function RefreshLeaderFollower ***************

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Lightweight replicated visual proxy for a persistent simulated AI tamer record. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAIRivalAvatar.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Lightweight replicated visual proxy for a persistent simulated AI tamer record." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sprite_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nameplate_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerLevel_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeaderFollower_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** One companion, bound to the persistent record's real first party instance. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "One companion, bound to the persistent record's real first party instance." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolSpeed_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rival" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAIRivalAvatar.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sprite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Nameplate;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TamerLevel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeaderFollower;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTAIRivalAvatar constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("InitializeAvatar"), .Pointer = &ADigimonVenomNXTAIRivalAvatar::execInitializeAvatar },
		{ .NameUTF8 = UTF8TEXT("IsForRival"), .Pointer = &ADigimonVenomNXTAIRivalAvatar::execIsForRival },
		{ .NameUTF8 = UTF8TEXT("OnRep_Identity"), .Pointer = &ADigimonVenomNXTAIRivalAvatar::execOnRep_Identity },
		{ .NameUTF8 = UTF8TEXT("RefreshLeaderFollower"), .Pointer = &ADigimonVenomNXTAIRivalAvatar::execRefreshLeaderFollower },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_BP_OnRivalIdentityChanged, "BP_OnRivalIdentityChanged" }, // b72b5de670476a9b0d5753d85534d5dbd3331219
		{ &Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_InitializeAvatar, "InitializeAvatar" }, // f183600842eef21b94a88f7cc75da032c073a44b
		{ &Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_IsForRival, "IsForRival" }, // 2c9d2c092c809838afce405c7c686350b72e13c4
		{ &Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_OnRep_Identity, "OnRep_Identity" }, // a48be198522987e0720ffc312ef5d81e23ee0c82
		{ &Z_Construct_UFunction_ADigimonVenomNXTAIRivalAvatar_RefreshLeaderFollower, "RefreshLeaderFollower" }, // fe7672ecdce94c62aea89398cc7dcf3ebf64cf67
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTAIRivalAvatar>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTAIRivalAvatar Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, Root), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Sprite = { "Sprite", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, Sprite), Z_Construct_UClass_UPaperFlipbookComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sprite_MetaData), NewProp_Sprite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Nameplate = { "Nameplate", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, Nameplate), Z_Construct_UClass_UDigimonVenomNXTNameplateComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nameplate_MetaData), NewProp_Nameplate_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, MapId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapId_MetaData), NewProp_MapId_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TamerLevel = { "TamerLevel", "OnRep_Identity", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, TamerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerLevel_MetaData), NewProp_TamerLevel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LeaderFollower = { "LeaderFollower", nullptr, (EPropertyFlags)0x0114000000000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, LeaderFollower), Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeaderFollower_MetaData), NewProp_LeaderFollower_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_PatrolSpeed = { "PatrolSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, PatrolSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolSpeed_MetaData), NewProp_PatrolSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTAIRivalAvatar, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Sprite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Nameplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LeaderFollower,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PatrolSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTAIRivalAvatar Property Definitions *************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar,
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
static void ADigimonVenomNXTAIRivalAvatar_StaticRegisterNativesADigimonVenomNXTAIRivalAvatar()
{
	UClass* Class = ADigimonVenomNXTAIRivalAvatar::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar;
UClass* Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTAIRivalAvatar;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAIRivalAvatar"),
				Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.InnerSingleton,
				ADigimonVenomNXTAIRivalAvatar_StaticRegisterNativesADigimonVenomNXTAIRivalAvatar,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTAIRivalAvatar::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_RivalId(TEXT("RivalId"));
	static FName Name_DisplayName(TEXT("DisplayName"));
	static FName Name_MapId(TEXT("MapId"));
	static FName Name_TamerLevel(TEXT("TamerLevel"));
	static FName Name_LeaderFollower(TEXT("LeaderFollower"));
	const bool bIsValid = true
		&& Name_RivalId == ClassReps[(int32)ENetFields_Private::RivalId].Property->GetFName()
		&& Name_DisplayName == ClassReps[(int32)ENetFields_Private::DisplayName].Property->GetFName()
		&& Name_MapId == ClassReps[(int32)ENetFields_Private::MapId].Property->GetFName()
		&& Name_TamerLevel == ClassReps[(int32)ENetFields_Private::TamerLevel].Property->GetFName()
		&& Name_LeaderFollower == ClassReps[(int32)ENetFields_Private::LeaderFollower].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTAIRivalAvatar"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTAIRivalAvatar);
ADigimonVenomNXTAIRivalAvatar::~ADigimonVenomNXTAIRivalAvatar() {}
// ********** End Class ADigimonVenomNXTAIRivalAvatar **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTAIRivalAvatar, TEXT("ADigimonVenomNXTAIRivalAvatar"), &Z_Registration_Info_UClass_ADigimonVenomNXTAIRivalAvatar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTAIRivalAvatar), 4260666707U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAIRivalAvatar_h__Script_DigimonVenomNXTRuntime_fd6ad32077d2793cd75e3e7098942cc2758d395c{
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
