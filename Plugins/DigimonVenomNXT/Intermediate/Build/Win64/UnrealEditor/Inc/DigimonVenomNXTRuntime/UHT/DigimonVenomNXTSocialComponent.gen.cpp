// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTSocialTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTSocialComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialChangedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialResultEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonSocialChangedEvent ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialChangedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonSocialChangedEvent constinit property declarations ************
// ********** End Delegate FDigimonSocialChangedEvent constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonSocialChangedEvent__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialChangedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonSocialChangedEvent **********************************************

// ********** Begin Delegate FDigimonSocialResultEvent *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialResultEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms
	{
		bool bSuccess;
		FString Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonSocialResultEvent constinit property declarations *************
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonSocialResultEvent constinit property declarations ***************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonSocialResultEvent Property Definitions ************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonSocialResultEvent Property Definitions **************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonSocialResultEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonSocialResultEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialResultEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonSocialResultEvent ***********************************************

// ********** Begin Class UDigimonVenomNXTSocialComponent Function ClientSocialResult **************
struct DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms
{
	bool bSuccess;
	FString Message;
};
static FName NAME_UDigimonVenomNXTSocialComponent_ClientSocialResult = FName(TEXT("ClientSocialResult"));
void UDigimonVenomNXTSocialComponent::ClientSocialResult(bool bSuccess, const FString& Message)
{
	DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms Parms;
	Parms.bSuccess=bSuccess ? true : false;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTSocialComponent_ClientSocialResult);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ClientSocialResult_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientSocialResult constinit property declarations ********************
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientSocialResult constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientSocialResult Property Definitions *******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientSocialResult Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "ClientSocialResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTSocialComponent_eventClientSocialResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ClientSocialResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execClientSocialResult)
{
	P_GET_UBOOL(Z_Param_bSuccess);
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientSocialResult_Implementation(Z_Param_bSuccess,Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function ClientSocialResult ****************

// ********** Begin Class UDigimonVenomNXTSocialComponent Function OnRep_State *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_OnRep_State_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_State constinit property declarations ***************************
// ********** End Function OnRep_State constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "OnRep_State", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_OnRep_State(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execOnRep_State)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_State();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function OnRep_State ***********************

// ********** Begin Class UDigimonVenomNXTSocialComponent Function ServerRefreshSocial *************
static FName NAME_UDigimonVenomNXTSocialComponent_ServerRefreshSocial = FName(TEXT("ServerRefreshSocial"));
void UDigimonVenomNXTSocialComponent::ServerRefreshSocial()
{
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTSocialComponent_ServerRefreshSocial);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRefreshSocial_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRefreshSocial constinit property declarations *******************
// ********** End Function ServerRefreshSocial constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "ServerRefreshSocial", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRefreshSocial(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execServerRefreshSocial)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRefreshSocial_Implementation();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function ServerRefreshSocial ***************

// ********** Begin Class UDigimonVenomNXTSocialComponent Function ServerRequestPlayerInfo *********
struct DigimonVenomNXTSocialComponent_eventServerRequestPlayerInfo_Parms
{
	FString UsernameOrId;
};
static FName NAME_UDigimonVenomNXTSocialComponent_ServerRequestPlayerInfo = FName(TEXT("ServerRequestPlayerInfo"));
void UDigimonVenomNXTSocialComponent::ServerRequestPlayerInfo(const FString& UsernameOrId)
{
	DigimonVenomNXTSocialComponent_eventServerRequestPlayerInfo_Parms Parms;
	Parms.UsernameOrId=UsernameOrId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTSocialComponent_ServerRequestPlayerInfo);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRequestPlayerInfo_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UsernameOrId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestPlayerInfo constinit property declarations ***************
	static const UECodeGen_Private::FStrPropertyParams NewProp_UsernameOrId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRequestPlayerInfo constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRequestPlayerInfo Property Definitions **************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_UsernameOrId = { "UsernameOrId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerRequestPlayerInfo_Parms, UsernameOrId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UsernameOrId_MetaData), NewProp_UsernameOrId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UsernameOrId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRequestPlayerInfo Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "ServerRequestPlayerInfo", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTSocialComponent_eventServerRequestPlayerInfo_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTSocialComponent_eventServerRequestPlayerInfo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRequestPlayerInfo(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execServerRequestPlayerInfo)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_UsernameOrId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestPlayerInfo_Implementation(Z_Param_UsernameOrId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function ServerRequestPlayerInfo ***********

// ********** Begin Class UDigimonVenomNXTSocialComponent Function ServerSendClanChat **************
struct DigimonVenomNXTSocialComponent_eventServerSendClanChat_Parms
{
	FString Message;
};
static FName NAME_UDigimonVenomNXTSocialComponent_ServerSendClanChat = FName(TEXT("ServerSendClanChat"));
void UDigimonVenomNXTSocialComponent::ServerSendClanChat(const FString& Message)
{
	DigimonVenomNXTSocialComponent_eventServerSendClanChat_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTSocialComponent_ServerSendClanChat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSendClanChat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSendClanChat constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSendClanChat constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSendClanChat Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerSendClanChat_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSendClanChat Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "ServerSendClanChat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTSocialComponent_eventServerSendClanChat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTSocialComponent_eventServerSendClanChat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSendClanChat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execServerSendClanChat)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSendClanChat_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function ServerSendClanChat ****************

// ********** Begin Class UDigimonVenomNXTSocialComponent Function ServerSocialAction **************
struct DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms
{
	EDigimonSocialAction Action;
	FString Target;
	FString Text;
	FString Extra;
};
static FName NAME_UDigimonVenomNXTSocialComponent_ServerSocialAction = FName(TEXT("ServerSocialAction"));
void UDigimonVenomNXTSocialComponent::ServerSocialAction(EDigimonSocialAction Action, const FString& Target, const FString& Text, const FString& Extra)
{
	DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms Parms;
	Parms.Action=Action;
	Parms.Target=Target;
	Parms.Text=Text;
	Parms.Extra=Extra;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTSocialComponent_ServerSocialAction);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSocialAction_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * Account actions: Target=username or immutable AccountId; Text/Extra unused.\n     * ClanCreate: Target=name (3-32), Text=tag (2-5), Extra=description (0-240).\n     * ClanDisband: Target=current ClanId, Text=exact clan name (explicit confirmation).\n     * ClanAccept/Decline: Target=ClanId. ClanLeave: no arguments required.\n     * ClanUpdate: Target=current ClanId, Text=message of the day (0-200), Extra=description (0-240).\n     * ClanTransfer: Target=new leader account, Text=exact clan name (confirmation).\n     */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Account actions: Target=username or immutable AccountId; Text/Extra unused.\nClanCreate: Target=name (3-32), Text=tag (2-5), Extra=description (0-240).\nClanDisband: Target=current ClanId, Text=exact clan name (explicit confirmation).\nClanAccept/Decline: Target=ClanId. ClanLeave: no arguments required.\nClanUpdate: Target=current ClanId, Text=message of the day (0-200), Extra=description (0-240).\nClanTransfer: Target=new leader account, Text=exact clan name (confirmation)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Extra_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSocialAction constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Action_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Action;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Target;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Text;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Extra;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSocialAction constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSocialAction Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Action_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms, Action), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction, METADATA_PARAMS(0, nullptr) }; // 60d3a2abefc9878ab509a98c4364c9dac7a440b6
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms, Target), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Target_MetaData), NewProp_Target_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Extra = { "Extra", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms, Extra), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Extra_MetaData), NewProp_Extra_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Extra,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSocialAction Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTSocialComponent, nullptr, "ServerSocialAction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTSocialComponent_eventServerSocialAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSocialAction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTSocialComponent::execServerSocialAction)
{
	P_GET_ENUM(EDigimonSocialAction,Z_Param_Action);
	P_GET_PROPERTY(FStrProperty,Z_Param_Target);
	P_GET_PROPERTY(FStrProperty,Z_Param_Text);
	P_GET_PROPERTY(FStrProperty,Z_Param_Extra);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSocialAction_Implementation(EDigimonSocialAction(Z_Param_Action),Z_Param_Target,Z_Param_Text,Z_Param_Extra);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTSocialComponent Function ServerSocialAction ****************

// ********** Begin Class UDigimonVenomNXTSocialComponent ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTSocialComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Digimon" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default replicated PlayerController subobject. Every RPC derives its account from the authenticated owner. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTSocialComponent.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default replicated PlayerController subobject. Every RPC derives its account from the authenticated owner." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Social" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastResult_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Social" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLastResultSucceeded_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Social" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSocialChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSocialResult_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTSocialComponent constinit property declarations **********
	static const UECodeGen_Private::FStructPropertyParams NewProp_State;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LastResult;
	static void NewProp_bLastResultSucceeded_SetBit(void* Obj)
	{
		((UDigimonVenomNXTSocialComponent*)Obj)->bLastResultSucceeded = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLastResultSucceeded;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSocialChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSocialResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTSocialComponent constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClientSocialResult"), .Pointer = &UDigimonVenomNXTSocialComponent::execClientSocialResult },
		{ .NameUTF8 = UTF8TEXT("OnRep_State"), .Pointer = &UDigimonVenomNXTSocialComponent::execOnRep_State },
		{ .NameUTF8 = UTF8TEXT("ServerRefreshSocial"), .Pointer = &UDigimonVenomNXTSocialComponent::execServerRefreshSocial },
		{ .NameUTF8 = UTF8TEXT("ServerRequestPlayerInfo"), .Pointer = &UDigimonVenomNXTSocialComponent::execServerRequestPlayerInfo },
		{ .NameUTF8 = UTF8TEXT("ServerSendClanChat"), .Pointer = &UDigimonVenomNXTSocialComponent::execServerSendClanChat },
		{ .NameUTF8 = UTF8TEXT("ServerSocialAction"), .Pointer = &UDigimonVenomNXTSocialComponent::execServerSocialAction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ClientSocialResult, "ClientSocialResult" }, // 9e2a53a0508e5f3111c214c5b29fb5c16a182da6
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_OnRep_State, "OnRep_State" }, // 57a9ce7ceaca6a81934dc3ed0261c20294e6a462
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRefreshSocial, "ServerRefreshSocial" }, // 271d5e01d3efefc32f62f42c5e80231934eda4a6
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerRequestPlayerInfo, "ServerRequestPlayerInfo" }, // 3069d71f33566eb40ca2f09465d54fbaaad7a178
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSendClanChat, "ServerSendClanChat" }, // 1871b7d1a5acb5000aea55bb2319c33d01a2100a
		{ &Z_Construct_UFunction_UDigimonVenomNXTSocialComponent_ServerSocialAction, "ServerSocialAction" }, // 2e7246c39bb36d735de79b3e54ce2c084407cf0c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTSocialComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTSocialComponent Property Definitions *********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_State = { "State", "OnRep_State", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSocialComponent, State), Z_Construct_UScriptStruct_FDigimonSocialState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 59f7f301e6c37154b355b049ee36056a202b3229
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_LastResult = { "LastResult", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSocialComponent, LastResult), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastResult_MetaData), NewProp_LastResult_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bLastResultSucceeded = { "bLastResultSucceeded", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDigimonVenomNXTSocialComponent), &UHT_STATICS::NewProp_bLastResultSucceeded_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLastResultSucceeded_MetaData), NewProp_bLastResultSucceeded_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnSocialChanged = { "OnSocialChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSocialComponent, OnSocialChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialChangedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSocialChanged_MetaData), NewProp_OnSocialChanged_MetaData) }; // db7d51e64e4417f57cbc2337f45b652be90feff5
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnSocialResult = { "OnSocialResult", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTSocialComponent, OnSocialResult), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonSocialResultEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSocialResult_MetaData), NewProp_OnSocialResult_MetaData) }; // 736f5b903bde663dfbf556b4f15a975b779d7f1e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bLastResultSucceeded,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnSocialChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnSocialResult,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTSocialComponent Property Definitions ***********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTSocialComponent,
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
static void UDigimonVenomNXTSocialComponent_StaticRegisterNativesUDigimonVenomNXTSocialComponent()
{
	UClass* Class = UDigimonVenomNXTSocialComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent;
UClass* Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTSocialComponent;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTSocialComponent"),
				Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.InnerSingleton,
				UDigimonVenomNXTSocialComponent_StaticRegisterNativesUDigimonVenomNXTSocialComponent,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void UDigimonVenomNXTSocialComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_State(TEXT("State"));
	const bool bIsValid = true
		&& Name_State == ClassReps[(int32)ENetFields_Private::State].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UDigimonVenomNXTSocialComponent"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTSocialComponent);
UDigimonVenomNXTSocialComponent::~UDigimonVenomNXTSocialComponent() {}
// ********** End Class UDigimonVenomNXTSocialComponent ********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTSocialComponent, TEXT("UDigimonVenomNXTSocialComponent"), &Z_Registration_Info_UClass_UDigimonVenomNXTSocialComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTSocialComponent), 2824583000U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h__Script_DigimonVenomNXTRuntime_f129351a97d29ade276fc28d03e95901547c23fd{
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
