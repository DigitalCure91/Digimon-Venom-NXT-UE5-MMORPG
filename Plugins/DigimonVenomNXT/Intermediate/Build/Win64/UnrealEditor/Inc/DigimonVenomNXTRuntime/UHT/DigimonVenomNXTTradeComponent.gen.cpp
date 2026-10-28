// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTTradeComponent.h"
#include "DigimonVenomNXTTradeTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTTradeComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonTradeChangedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonTradeChangedEvent *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonTradeChangedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonTradeChangedEvent constinit property declarations *************
// ********** End Delegate FDigimonTradeChangedEvent constinit property declarations ***************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonTradeChangedEvent__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonTradeChangedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonTradeChangedEvent ***********************************************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function OnRep_View ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_OnRep_View_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_View constinit property declarations ****************************
// ********** End Function OnRep_View constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "OnRep_View", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_OnRep_View(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execOnRep_View)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_View();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function OnRep_View *************************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerBrowse *********************
struct DigimonVenomNXTTradeComponent_eventServerBrowse_Parms
{
	FString Search;
	int32 Page;
	bool bMineOnly;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerBrowse = FName(TEXT("ServerBrowse"));
void UDigimonVenomNXTTradeComponent::ServerBrowse(const FString& Search, int32 Page, bool bMineOnly)
{
	DigimonVenomNXTTradeComponent_eventServerBrowse_Parms Parms;
	Parms.Search=Search;
	Parms.Page=Page;
	Parms.bMineOnly=bMineOnly ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerBrowse);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerBrowse_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Search_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerBrowse constinit property declarations **************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Search;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Page;
	static void NewProp_bMineOnly_SetBit(void* Obj)
	{
		((DigimonVenomNXTTradeComponent_eventServerBrowse_Parms*)Obj)->bMineOnly = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMineOnly;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerBrowse constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerBrowse Property Definitions *************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Search = { "Search", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerBrowse_Parms, Search), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Search_MetaData), NewProp_Search_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerBrowse_Parms, Page), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bMineOnly = { "bMineOnly", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTTradeComponent_eventServerBrowse_Parms), &UHT_STATICS::NewProp_bMineOnly_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Search,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bMineOnly,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerBrowse Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerBrowse", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerBrowse_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerBrowse_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerBrowse(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerBrowse)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Search);
	P_GET_PROPERTY(FIntProperty,Z_Param_Page);
	P_GET_UBOOL(Z_Param_bMineOnly);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerBrowse_Implementation(Z_Param_Search,Z_Param_Page,Z_Param_bMineOnly);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerBrowse ***********************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerCancelListing **************
struct DigimonVenomNXTTradeComponent_eventServerCancelListing_Parms
{
	FGuid ListingId;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerCancelListing = FName(TEXT("ServerCancelListing"));
void UDigimonVenomNXTTradeComponent::ServerCancelListing(FGuid ListingId)
{
	DigimonVenomNXTTradeComponent_eventServerCancelListing_Parms Parms;
	Parms.ListingId=ListingId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerCancelListing);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelListing_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCancelListing constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ListingId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerCancelListing constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerCancelListing Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ListingId = { "ListingId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerCancelListing_Parms, ListingId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ListingId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerCancelListing Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerCancelListing", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerCancelListing_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerCancelListing_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelListing(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerCancelListing)
{
	P_GET_STRUCT(FGuid,Z_Param_ListingId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCancelListing_Implementation(Z_Param_ListingId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerCancelListing ****************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerCancelTrade ****************
struct DigimonVenomNXTTradeComponent_eventServerCancelTrade_Parms
{
	FGuid SessionId;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerCancelTrade = FName(TEXT("ServerCancelTrade"));
void UDigimonVenomNXTTradeComponent::ServerCancelTrade(FGuid SessionId)
{
	DigimonVenomNXTTradeComponent_eventServerCancelTrade_Parms Parms;
	Parms.SessionId=SessionId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerCancelTrade);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelTrade_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCancelTrade constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SessionId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerCancelTrade constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerCancelTrade Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SessionId = { "SessionId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerCancelTrade_Parms, SessionId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerCancelTrade Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerCancelTrade", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerCancelTrade_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerCancelTrade_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelTrade(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerCancelTrade)
{
	P_GET_STRUCT(FGuid,Z_Param_SessionId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCancelTrade_Implementation(Z_Param_SessionId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerCancelTrade ******************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerConfirmPurchase ************
struct DigimonVenomNXTTradeComponent_eventServerConfirmPurchase_Parms
{
	FGuid PurchaseToken;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerConfirmPurchase = FName(TEXT("ServerConfirmPurchase"));
void UDigimonVenomNXTTradeComponent::ServerConfirmPurchase(FGuid PurchaseToken)
{
	DigimonVenomNXTTradeComponent_eventServerConfirmPurchase_Parms Parms;
	Parms.PurchaseToken=PurchaseToken;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerConfirmPurchase);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmPurchase_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerConfirmPurchase constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_PurchaseToken;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerConfirmPurchase constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerConfirmPurchase Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PurchaseToken = { "PurchaseToken", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerConfirmPurchase_Parms, PurchaseToken), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PurchaseToken,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerConfirmPurchase Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerConfirmPurchase", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerConfirmPurchase_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerConfirmPurchase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmPurchase(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerConfirmPurchase)
{
	P_GET_STRUCT(FGuid,Z_Param_PurchaseToken);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerConfirmPurchase_Implementation(Z_Param_PurchaseToken);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerConfirmPurchase **************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerConfirmTrade ***************
struct DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms
{
	FGuid SessionId;
	int32 Revision;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerConfirmTrade = FName(TEXT("ServerConfirmTrade"));
void UDigimonVenomNXTTradeComponent::ServerConfirmTrade(FGuid SessionId, int32 Revision)
{
	DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms Parms;
	Parms.SessionId=SessionId;
	Parms.Revision=Revision;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerConfirmTrade);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmTrade_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerConfirmTrade constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SessionId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Revision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerConfirmTrade constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerConfirmTrade Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SessionId = { "SessionId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms, SessionId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerConfirmTrade Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerConfirmTrade", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerConfirmTrade_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmTrade(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerConfirmTrade)
{
	P_GET_STRUCT(FGuid,Z_Param_SessionId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Revision);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerConfirmTrade_Implementation(Z_Param_SessionId,Z_Param_Revision);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerConfirmTrade *****************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerCreateListing **************
struct DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms
{
	FGuid PartnerId;
	int64 Credits;
	int32 DigiRubies;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerCreateListing = FName(TEXT("ServerCreateListing"));
void UDigimonVenomNXTTradeComponent::ServerCreateListing(FGuid PartnerId, int64 Credits, int32 DigiRubies)
{
	DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms Parms;
	Parms.PartnerId=PartnerId;
	Parms.Credits=Credits;
	Parms.DigiRubies=DigiRubies;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerCreateListing);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCreateListing_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCreateListing constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_PartnerId;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Credits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiRubies;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerCreateListing constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerCreateListing Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PartnerId = { "PartnerId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms, PartnerId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Credits = { "Credits", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms, Credits), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiRubies = { "DigiRubies", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms, DigiRubies), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartnerId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Credits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiRubies,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerCreateListing Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerCreateListing", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerCreateListing_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCreateListing(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerCreateListing)
{
	P_GET_STRUCT(FGuid,Z_Param_PartnerId);
	P_GET_PROPERTY(FInt64Property,Z_Param_Credits);
	P_GET_PROPERTY(FIntProperty,Z_Param_DigiRubies);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCreateListing_Implementation(Z_Param_PartnerId,Z_Param_Credits,Z_Param_DigiRubies);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerCreateListing ****************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerInviteTrade ****************
struct DigimonVenomNXTTradeComponent_eventServerInviteTrade_Parms
{
	FString TargetAccountId;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerInviteTrade = FName(TEXT("ServerInviteTrade"));
void UDigimonVenomNXTTradeComponent::ServerInviteTrade(const FString& TargetAccountId)
{
	DigimonVenomNXTTradeComponent_eventServerInviteTrade_Parms Parms;
	Parms.TargetAccountId=TargetAccountId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerInviteTrade);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerInviteTrade_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetAccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerInviteTrade constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetAccountId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerInviteTrade constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerInviteTrade Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_TargetAccountId = { "TargetAccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerInviteTrade_Parms, TargetAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetAccountId_MetaData), NewProp_TargetAccountId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetAccountId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerInviteTrade Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerInviteTrade", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerInviteTrade_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerInviteTrade_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerInviteTrade(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerInviteTrade)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_TargetAccountId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerInviteTrade_Implementation(Z_Param_TargetAccountId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerInviteTrade ******************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerReviewPurchase *************
struct DigimonVenomNXTTradeComponent_eventServerReviewPurchase_Parms
{
	FGuid ListingId;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerReviewPurchase = FName(TEXT("ServerReviewPurchase"));
void UDigimonVenomNXTTradeComponent::ServerReviewPurchase(FGuid ListingId)
{
	DigimonVenomNXTTradeComponent_eventServerReviewPurchase_Parms Parms;
	Parms.ListingId=ListingId;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerReviewPurchase);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerReviewPurchase_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerReviewPurchase constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ListingId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerReviewPurchase constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerReviewPurchase Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ListingId = { "ListingId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerReviewPurchase_Parms, ListingId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ListingId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerReviewPurchase Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerReviewPurchase", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerReviewPurchase_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerReviewPurchase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerReviewPurchase(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerReviewPurchase)
{
	P_GET_STRUCT(FGuid,Z_Param_ListingId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerReviewPurchase_Implementation(Z_Param_ListingId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerReviewPurchase ***************

// ********** Begin Class UDigimonVenomNXTTradeComponent Function ServerUpdateOffer ****************
struct DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms
{
	FGuid SessionId;
	int32 Revision;
	TArray<FGuid> PartnerIds;
	int64 Credits;
	int32 DigiRubies;
};
static FName NAME_UDigimonVenomNXTTradeComponent_ServerUpdateOffer = FName(TEXT("ServerUpdateOffer"));
void UDigimonVenomNXTTradeComponent::ServerUpdateOffer(FGuid SessionId, int32 Revision, TArray<FGuid> const& PartnerIds, int64 Credits, int32 DigiRubies)
{
	DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms Parms;
	Parms.SessionId=SessionId;
	Parms.Revision=Revision;
	Parms.PartnerIds=PartnerIds;
	Parms.Credits=Credits;
	Parms.DigiRubies=DigiRubies;
	UFunction* Func = FindFunctionChecked(NAME_UDigimonVenomNXTTradeComponent_ServerUpdateOffer);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerUpdateOffer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartnerIds_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerUpdateOffer constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SessionId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Revision;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PartnerIds_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PartnerIds;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Credits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiRubies;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerUpdateOffer constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerUpdateOffer Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SessionId = { "SessionId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms, SessionId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PartnerIds_Inner = { "PartnerIds", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PartnerIds = { "PartnerIds", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms, PartnerIds), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartnerIds_MetaData), NewProp_PartnerIds_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Credits = { "Credits", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms, Credits), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiRubies = { "DigiRubies", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms, DigiRubies), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartnerIds_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartnerIds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Credits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiRubies,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerUpdateOffer Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTTradeComponent, nullptr, "ServerUpdateOffer", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTradeComponent_eventServerUpdateOffer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerUpdateOffer(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTTradeComponent::execServerUpdateOffer)
{
	P_GET_STRUCT(FGuid,Z_Param_SessionId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Revision);
	P_GET_TARRAY(FGuid,Z_Param_PartnerIds);
	P_GET_PROPERTY(FInt64Property,Z_Param_Credits);
	P_GET_PROPERTY(FIntProperty,Z_Param_DigiRubies);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerUpdateOffer_Implementation(Z_Param_SessionId,Z_Param_Revision,Z_Param_PartnerIds,Z_Param_Credits,Z_Param_DigiRubies);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTTradeComponent Function ServerUpdateOffer ******************

// ********** Begin Class UDigimonVenomNXTTradeComponent *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTTradeComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "DigimonVenomNXT" },
		{ "IncludePath", "DigimonVenomNXTTradeComponent.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_View_MetaData[] = {
		{ "Category", "DigimonVenomNXTTradeComponent" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTradeChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTTradeComponent constinit property declarations ***********
	static const UECodeGen_Private::FStructPropertyParams NewProp_View;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTradeChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTTradeComponent constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnRep_View"), .Pointer = &UDigimonVenomNXTTradeComponent::execOnRep_View },
		{ .NameUTF8 = UTF8TEXT("ServerBrowse"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerBrowse },
		{ .NameUTF8 = UTF8TEXT("ServerCancelListing"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerCancelListing },
		{ .NameUTF8 = UTF8TEXT("ServerCancelTrade"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerCancelTrade },
		{ .NameUTF8 = UTF8TEXT("ServerConfirmPurchase"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerConfirmPurchase },
		{ .NameUTF8 = UTF8TEXT("ServerConfirmTrade"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerConfirmTrade },
		{ .NameUTF8 = UTF8TEXT("ServerCreateListing"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerCreateListing },
		{ .NameUTF8 = UTF8TEXT("ServerInviteTrade"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerInviteTrade },
		{ .NameUTF8 = UTF8TEXT("ServerReviewPurchase"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerReviewPurchase },
		{ .NameUTF8 = UTF8TEXT("ServerUpdateOffer"), .Pointer = &UDigimonVenomNXTTradeComponent::execServerUpdateOffer },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_OnRep_View, "OnRep_View" }, // 311a4aaa7502cf2f60a52f01634e76d6b9a0d7bb
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerBrowse, "ServerBrowse" }, // 0fd63217412e0b87f6117b62fbdf4ed6e804b07f
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelListing, "ServerCancelListing" }, // 055a98335193b2d0680961da259c1697476f6886
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCancelTrade, "ServerCancelTrade" }, // b7c43a07d11d796991dd67bf76137f8b5aa26468
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmPurchase, "ServerConfirmPurchase" }, // ceef04bf0439e2b2b091bfed816ae06b9a8b7b5c
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerConfirmTrade, "ServerConfirmTrade" }, // 3bb9b06c510a4b28ee7bfe4f83ef72050f98fc6f
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerCreateListing, "ServerCreateListing" }, // 910cff3e2d492d649d70ef9083691f1f533c4104
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerInviteTrade, "ServerInviteTrade" }, // 53300e0894d9fc6d8d4618618b1c0cd3ad97a5bc
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerReviewPurchase, "ServerReviewPurchase" }, // 397045b268d3e7cef728bece0a7830d25f40fac9
		{ &Z_Construct_UFunction_UDigimonVenomNXTTradeComponent_ServerUpdateOffer, "ServerUpdateOffer" }, // b72f2327d9a41bc791aef495e4818a6b02fd2d27
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTTradeComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTTradeComponent Property Definitions **********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_View = { "View", "OnRep_View", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTradeComponent, View), Z_Construct_UScriptStruct_FDigimonTradeView, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_View_MetaData), NewProp_View_MetaData) }; // e2495663709283cd8c346c6bbb4ef6d8deaae4af
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnTradeChanged = { "OnTradeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTTradeComponent, OnTradeChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonTradeChangedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTradeChanged_MetaData), NewProp_OnTradeChanged_MetaData) }; // c524178773430bd67503671c0a7cd51a136bc69b
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_View,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnTradeChanged,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTTradeComponent Property Definitions ************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTTradeComponent,
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
static void UDigimonVenomNXTTradeComponent_StaticRegisterNativesUDigimonVenomNXTTradeComponent()
{
	UClass* Class = UDigimonVenomNXTTradeComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent;
UClass* Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTTradeComponent;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTTradeComponent"),
				Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.InnerSingleton,
				UDigimonVenomNXTTradeComponent_StaticRegisterNativesUDigimonVenomNXTTradeComponent,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void UDigimonVenomNXTTradeComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_View(TEXT("View"));
	const bool bIsValid = true
		&& Name_View == ClassReps[(int32)ENetFields_Private::View].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UDigimonVenomNXTTradeComponent"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTTradeComponent);
UDigimonVenomNXTTradeComponent::~UDigimonVenomNXTTradeComponent() {}
// ********** End Class UDigimonVenomNXTTradeComponent *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTTradeComponent, TEXT("UDigimonVenomNXTTradeComponent"), &Z_Registration_Info_UClass_UDigimonVenomNXTTradeComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTTradeComponent), 3827237921U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h__Script_DigimonVenomNXTRuntime_37247ae7306631977a5533029d363aa765c3add1{
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
