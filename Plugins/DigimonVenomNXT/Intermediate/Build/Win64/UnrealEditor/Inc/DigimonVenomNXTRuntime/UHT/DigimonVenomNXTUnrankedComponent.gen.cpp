// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTUnrankedComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTUnrankedComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedChallenge(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUnrankedChanged__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedTarget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonUnrankedChallenge *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonUnrankedChallenge_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonUnrankedChallenge>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonUnrankedChallenge); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChallengeId_MetaData[] = {
		{ "Category", "DigimonUnrankedChallenge" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherAccountId_MetaData[] = {
		{ "Category", "DigimonUnrankedChallenge" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherName_MetaData[] = {
		{ "Category", "DigimonUnrankedChallenge" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpiresUnix_MetaData[] = {
		{ "Category", "DigimonUnrankedChallenge" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonUnrankedChallenge constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChallengeId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OtherAccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OtherName;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_ExpiresUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonUnrankedChallenge constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonUnrankedChallenge>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonUnrankedChallenge Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ChallengeId = { "ChallengeId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedChallenge, ChallengeId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChallengeId_MetaData), NewProp_ChallengeId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OtherAccountId = { "OtherAccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedChallenge, OtherAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherAccountId_MetaData), NewProp_OtherAccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OtherName = { "OtherName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedChallenge, OtherName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherName_MetaData), NewProp_OtherName_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_ExpiresUnix = { "ExpiresUnix", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedChallenge, ExpiresUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpiresUnix_MetaData), NewProp_ExpiresUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChallengeId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherAccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExpiresUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonUnrankedChallenge Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonUnrankedChallenge",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonUnrankedChallenge>(),
	alignof(FDigimonUnrankedChallenge),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedChallenge(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonUnrankedChallenge, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonUnrankedChallenge"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonUnrankedChallenge *******************************************

// ********** Begin ScriptStruct FDigimonUnrankedTarget ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonUnrankedTarget_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonUnrankedTarget>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonUnrankedTarget); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deliberately excludes inventory, collection, saved location and private account data. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deliberately excludes inventory, collection, saved location and private account data." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "Category", "DigimonUnrankedTarget" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "DigimonUnrankedTarget" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Level_MetaData[] = {
		{ "Category", "DigimonUnrankedTarget" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvailable_MetaData[] = {
		{ "Category", "DigimonUnrankedTarget" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonUnrankedTarget constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Level;
	static void NewProp_bAvailable_SetBit(void* Obj)
	{
		((FDigimonUnrankedTarget*)Obj)->bAvailable = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvailable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonUnrankedTarget constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonUnrankedTarget>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonUnrankedTarget Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedTarget, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedTarget, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Level = { "Level", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonUnrankedTarget, Level), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Level_MetaData), NewProp_Level_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAvailable = { "bAvailable", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonUnrankedTarget), &UHT_STATICS::NewProp_bAvailable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvailable_MetaData), NewProp_bAvailable_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Level,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAvailable,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonUnrankedTarget Property Definitions *************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonUnrankedTarget",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonUnrankedTarget>(),
	alignof(FDigimonUnrankedTarget),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonUnrankedTarget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonUnrankedTarget, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonUnrankedTarget"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonUnrankedTarget **********************************************

// ********** Begin Delegate FDigimonUnrankedChanged ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUnrankedChanged__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonUnrankedChanged constinit property declarations ***************
// ********** End Delegate FDigimonUnrankedChanged constinit property declarations *****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonUnrankedChanged__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUnrankedChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonUnrankedChanged *************************************************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function OnRep_State *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_OnRep_State_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_State constinit property declarations ***************************
// ********** End Function OnRep_State constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "OnRep_State", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_OnRep_State(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execOnRep_State)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_State();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function OnRep_State *********************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerCancel ******************
struct DigimonVenomNXTUnrankedComponent_eventServerCancel_Parms
{
	FGuid ChallengeId;
};
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerCancel = FName(TEXT("ServerCancel"));
void UDigimonVenomNXTUnrankedComponent::ServerCancel(FGuid ChallengeId)
{
	DigimonVenomNXTUnrankedComponent_eventServerCancel_Parms Parms;
	Parms.ChallengeId=ChallengeId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerCancel);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerCancel_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCancel constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChallengeId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerCancel constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerCancel Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ChallengeId = { "ChallengeId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTUnrankedComponent_eventServerCancel_Parms, ChallengeId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChallengeId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerCancel Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerCancel", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTUnrankedComponent_eventServerCancel_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTUnrankedComponent_eventServerCancel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerCancel(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerCancel)
{
	P_GET_STRUCT(FGuid,Z_Param_ChallengeId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCancel_Implementation(Z_Param_ChallengeId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerCancel ********************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerChallengePlayer *********
struct DigimonVenomNXTUnrankedComponent_eventServerChallengePlayer_Parms
{
	FString AccountId;
};
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerChallengePlayer = FName(TEXT("ServerChallengePlayer"));
void UDigimonVenomNXTUnrankedComponent::ServerChallengePlayer(const FString& AccountId)
{
	DigimonVenomNXTUnrankedComponent_eventServerChallengePlayer_Parms Parms;
	Parms.AccountId=AccountId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerChallengePlayer);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengePlayer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerChallengePlayer constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerChallengePlayer constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerChallengePlayer Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTUnrankedComponent_eventServerChallengePlayer_Parms, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerChallengePlayer Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerChallengePlayer", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTUnrankedComponent_eventServerChallengePlayer_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTUnrankedComponent_eventServerChallengePlayer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengePlayer(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerChallengePlayer)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_AccountId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerChallengePlayer_Implementation(Z_Param_AccountId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerChallengePlayer ***********

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerChallengeRival **********
struct DigimonVenomNXTUnrankedComponent_eventServerChallengeRival_Parms
{
	FString RivalId;
};
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerChallengeRival = FName(TEXT("ServerChallengeRival"));
void UDigimonVenomNXTUnrankedComponent::ServerChallengeRival(const FString& RivalId)
{
	DigimonVenomNXTUnrankedComponent_eventServerChallengeRival_Parms Parms;
	Parms.RivalId=RivalId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerChallengeRival);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengeRival_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerChallengeRival constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerChallengeRival constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerChallengeRival Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTUnrankedComponent_eventServerChallengeRival_Parms, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerChallengeRival Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerChallengeRival", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTUnrankedComponent_eventServerChallengeRival_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTUnrankedComponent_eventServerChallengeRival_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengeRival(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerChallengeRival)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_RivalId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerChallengeRival_Implementation(Z_Param_RivalId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerChallengeRival ************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerForfeit *****************
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerForfeit = FName(TEXT("ServerForfeit"));
void UDigimonVenomNXTUnrankedComponent::ServerForfeit()
{
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerForfeit);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerForfeit_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerForfeit constinit property declarations *************************
// ********** End Function ServerForfeit constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerForfeit", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerForfeit(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerForfeit)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerForfeit_Implementation();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerForfeit *******************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerRefresh *****************
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerRefresh = FName(TEXT("ServerRefresh"));
void UDigimonVenomNXTUnrankedComponent::ServerRefresh()
{
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerRefresh);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRefresh_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRefresh constinit property declarations *************************
// ********** End Function ServerRefresh constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerRefresh", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRefresh(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerRefresh)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRefresh_Implementation();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerRefresh *******************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Function ServerRespond *****************
struct DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms
{
	FGuid ChallengeId;
	bool bAccept;
};
static FName NAME_UDigimonVenomNXTUnrankedComponent_ServerRespond = FName(TEXT("ServerRespond"));
void UDigimonVenomNXTUnrankedComponent::ServerRespond(FGuid ChallengeId, bool bAccept)
{
	DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms Parms;
	Parms.ChallengeId=ChallengeId;
	Parms.bAccept=bAccept ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTUnrankedComponent_ServerRespond);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRespond_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRespond constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChallengeId;
	static void NewProp_bAccept_SetBit(void* Obj)
	{
		((DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms*)Obj)->bAccept = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAccept;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRespond constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRespond Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ChallengeId = { "ChallengeId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms, ChallengeId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAccept = { "bAccept", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms), &UHT_STATICS::NewProp_bAccept_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChallengeId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAccept,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRespond Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, nullptr, "ServerRespond", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTUnrankedComponent_eventServerRespond_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRespond(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTUnrankedComponent::execServerRespond)
{
	P_GET_STRUCT(FGuid,Z_Param_ChallengeId);
	P_GET_UBOOL(Z_Param_bAccept);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRespond_Implementation(Z_Param_ChallengeId,Z_Param_bAccept);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTUnrankedComponent Function ServerRespond *******************

// ********** Begin Class UDigimonVenomNXTUnrankedComponent ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Digimon" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Owner-only invitations. Only the server chooses participants, party snapshots and outcomes. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTUnrankedComponent.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Owner-only invitations. Only the server chooses participants, party snapshots and outcomes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingChallenge_MetaData[] = {
		{ "Category", "DigimonVenomNXTUnrankedComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutgoingChallenge_MetaData[] = {
		{ "Category", "DigimonVenomNXTUnrankedComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NearbyPlayers_MetaData[] = {
		{ "Category", "DigimonVenomNXTUnrankedComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NearbyRivals_MetaData[] = {
		{ "Category", "DigimonVenomNXTUnrankedComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusMessage_MetaData[] = {
		{ "Category", "DigimonVenomNXTUnrankedComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnUnrankedChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTUnrankedComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTUnrankedComponent constinit property declarations ********
	static const UECodeGen_Private::FStructPropertyParams NewProp_IncomingChallenge;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutgoingChallenge;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NearbyPlayers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_NearbyPlayers;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NearbyRivals_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_NearbyRivals;
	static const UECodeGen_Private::FStrPropertyParams NewProp_StatusMessage;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnUnrankedChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTUnrankedComponent constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnRep_State"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execOnRep_State },
		{ .NameUTF8 = UTF8TEXT("ServerCancel"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerCancel },
		{ .NameUTF8 = UTF8TEXT("ServerChallengePlayer"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerChallengePlayer },
		{ .NameUTF8 = UTF8TEXT("ServerChallengeRival"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerChallengeRival },
		{ .NameUTF8 = UTF8TEXT("ServerForfeit"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerForfeit },
		{ .NameUTF8 = UTF8TEXT("ServerRefresh"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerRefresh },
		{ .NameUTF8 = UTF8TEXT("ServerRespond"), .Pointer = &UDigimonVenomNXTUnrankedComponent::execServerRespond },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_OnRep_State, "OnRep_State" }, // 6e9c9fcc7b0c3c8fbde80bd6ae1896dc3e97060b
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerCancel, "ServerCancel" }, // a0b62051d6f81a0139a74168a2f4fe1afb636dea
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengePlayer, "ServerChallengePlayer" }, // f74d0c58b69721d0115062d0bf2f08d00fdb1f7b
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerChallengeRival, "ServerChallengeRival" }, // b028a39ee93987f56c907169a23f37848220b619
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerForfeit, "ServerForfeit" }, // 4339c3098aecf9b10908552ad0ebe9612476e907
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRefresh, "ServerRefresh" }, // 847f5f9abbd26f973f5cd9f1d62107f6f67baee2
		{ &Z_Construct_UFunction_UDigimonVenomNXTUnrankedComponent_ServerRespond, "ServerRespond" }, // 43bb007de0549596086ef04abc84467b4e37a24a
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTUnrankedComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTUnrankedComponent Property Definitions *******************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_IncomingChallenge = { "IncomingChallenge", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, IncomingChallenge), Z_Construct_UScriptStruct_FDigimonUnrankedChallenge, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingChallenge_MetaData), NewProp_IncomingChallenge_MetaData) }; // f4d04bcf99b86928ee4771dddc1f607036ae0fab
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutgoingChallenge = { "OutgoingChallenge", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, OutgoingChallenge), Z_Construct_UScriptStruct_FDigimonUnrankedChallenge, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutgoingChallenge_MetaData), NewProp_OutgoingChallenge_MetaData) }; // f4d04bcf99b86928ee4771dddc1f607036ae0fab
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NearbyPlayers_Inner = { "NearbyPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonUnrankedTarget, METADATA_PARAMS(0, nullptr) }; // 73b2a33383ba63cf3b193ea2496f826251bf0899
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_NearbyPlayers = { "NearbyPlayers", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, NearbyPlayers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NearbyPlayers_MetaData), NewProp_NearbyPlayers_MetaData) }; // 73b2a33383ba63cf3b193ea2496f826251bf0899
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NearbyRivals_Inner = { "NearbyRivals", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonUnrankedTarget, METADATA_PARAMS(0, nullptr) }; // 73b2a33383ba63cf3b193ea2496f826251bf0899
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_NearbyRivals = { "NearbyRivals", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, NearbyRivals), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NearbyRivals_MetaData), NewProp_NearbyRivals_MetaData) }; // 73b2a33383ba63cf3b193ea2496f826251bf0899
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_StatusMessage = { "StatusMessage", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, StatusMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusMessage_MetaData), NewProp_StatusMessage_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnUnrankedChanged = { "OnUnrankedChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTUnrankedComponent, OnUnrankedChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonUnrankedChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnUnrankedChanged_MetaData), NewProp_OnUnrankedChanged_MetaData) }; // ba5ade6ac630ddf2fbbc00f952b1ae93753b50dc
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IncomingChallenge,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutgoingChallenge,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NearbyPlayers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NearbyPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NearbyRivals_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NearbyRivals,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StatusMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnUnrankedChanged,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTUnrankedComponent Property Definitions *********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent,
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
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTUnrankedComponent_StaticRegisterNativesUDigimonVenomNXTUnrankedComponent()
{
	UClass* Class = UDigimonVenomNXTUnrankedComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent;
UClass* Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTUnrankedComponent;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTUnrankedComponent"),
				Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.InnerSingleton,
				UDigimonVenomNXTUnrankedComponent_StaticRegisterNativesUDigimonVenomNXTUnrankedComponent,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void UDigimonVenomNXTUnrankedComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_IncomingChallenge(TEXT("IncomingChallenge"));
	static FName Name_OutgoingChallenge(TEXT("OutgoingChallenge"));
	static FName Name_NearbyPlayers(TEXT("NearbyPlayers"));
	static FName Name_NearbyRivals(TEXT("NearbyRivals"));
	static FName Name_StatusMessage(TEXT("StatusMessage"));
	const bool bIsValid = true
		&& Name_IncomingChallenge == ClassReps[(int32)ENetFields_Private::IncomingChallenge].Property->GetFName()
		&& Name_OutgoingChallenge == ClassReps[(int32)ENetFields_Private::OutgoingChallenge].Property->GetFName()
		&& Name_NearbyPlayers == ClassReps[(int32)ENetFields_Private::NearbyPlayers].Property->GetFName()
		&& Name_NearbyRivals == ClassReps[(int32)ENetFields_Private::NearbyRivals].Property->GetFName()
		&& Name_StatusMessage == ClassReps[(int32)ENetFields_Private::StatusMessage].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UDigimonVenomNXTUnrankedComponent"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTUnrankedComponent);
UDigimonVenomNXTUnrankedComponent::~UDigimonVenomNXTUnrankedComponent() {}
// ********** End Class UDigimonVenomNXTUnrankedComponent ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonUnrankedChallenge, Z_Construct_UScriptStruct_FDigimonUnrankedChallenge_Statics::NewStructOps, TEXT("DigimonUnrankedChallenge"),&Z_Registration_Info_UScriptStruct_FDigimonUnrankedChallenge, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonUnrankedChallenge), 4107291599U) },
		{ Z_Construct_UScriptStruct_FDigimonUnrankedTarget, Z_Construct_UScriptStruct_FDigimonUnrankedTarget_Statics::NewStructOps, TEXT("DigimonUnrankedTarget"),&Z_Registration_Info_UScriptStruct_FDigimonUnrankedTarget, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonUnrankedTarget), 1941087027U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, TEXT("UDigimonVenomNXTUnrankedComponent"), &Z_Registration_Info_UClass_UDigimonVenomNXTUnrankedComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTUnrankedComponent), 3817846702U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTUnrankedComponent_h__Script_DigimonVenomNXTRuntime_b94b0cc6feeafd8a8afdaf31d280130b5e2accc6{
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
