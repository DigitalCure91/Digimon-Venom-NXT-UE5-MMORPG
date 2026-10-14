// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTTradeTypes.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTTradeTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonDirectTrade(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonOwnedPartner(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeListing(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeMarket(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeOffer(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeView(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonTradeListing **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonTradeListing_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonTradeListing>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonTradeListing); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The complete partner snapshot is the item in escrow, not a client-provided description. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The complete partner snapshot is the item in escrow, not a client-provided description." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ListingId_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SellerAccountId_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SellerName_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Partner_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Credits_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiRubies_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreatedUnix_MetaData[] = {
		{ "Category", "DigimonTradeListing" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonTradeListing constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ListingId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SellerAccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SellerName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Partner;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Credits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiRubies;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_CreatedUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonTradeListing constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonTradeListing>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonTradeListing Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ListingId = { "ListingId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, ListingId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ListingId_MetaData), NewProp_ListingId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SellerAccountId = { "SellerAccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, SellerAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SellerAccountId_MetaData), NewProp_SellerAccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SellerName = { "SellerName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, SellerName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SellerName_MetaData), NewProp_SellerName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Partner = { "Partner", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, Partner), Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Partner_MetaData), NewProp_Partner_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Credits = { "Credits", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, Credits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Credits_MetaData), NewProp_Credits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiRubies = { "DigiRubies", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, DigiRubies), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiRubies_MetaData), NewProp_DigiRubies_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_CreatedUnix = { "CreatedUnix", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeListing, CreatedUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreatedUnix_MetaData), NewProp_CreatedUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ListingId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SellerAccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SellerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Credits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiRubies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CreatedUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonTradeListing Property Definitions ***************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonTradeListing",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonTradeListing>(),
	alignof(FDigimonTradeListing),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonTradeListing;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeListing(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonTradeListing.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonTradeListing.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonTradeListing, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonTradeListing"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonTradeListing.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonTradeListing.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonTradeListing.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonTradeListing.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonTradeListing ************************************************

// ********** Begin ScriptStruct FDigimonTradeOffer ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonTradeOffer_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonTradeOffer>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonTradeOffer); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Partners_MetaData[] = {
		{ "Category", "DigimonTradeOffer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Credits_MetaData[] = {
		{ "Category", "DigimonTradeOffer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiRubies_MetaData[] = {
		{ "Category", "DigimonTradeOffer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bConfirmed_MetaData[] = {
		{ "Category", "DigimonTradeOffer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonTradeOffer constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Partners_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Partners;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Credits;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DigiRubies;
	static void NewProp_bConfirmed_SetBit(void* Obj)
	{
		((FDigimonTradeOffer*)Obj)->bConfirmed = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bConfirmed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonTradeOffer constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonTradeOffer>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonTradeOffer Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Partners_Inner = { "Partners", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonOwnedPartner, METADATA_PARAMS(0, nullptr) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Partners = { "Partners", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeOffer, Partners), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Partners_MetaData), NewProp_Partners_MetaData) }; // a7bbefd88ce1b01e88394b75ed04e83bd121c51c
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Credits = { "Credits", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeOffer, Credits), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Credits_MetaData), NewProp_Credits_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DigiRubies = { "DigiRubies", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeOffer, DigiRubies), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiRubies_MetaData), NewProp_DigiRubies_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bConfirmed = { "bConfirmed", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonTradeOffer), &UHT_STATICS::NewProp_bConfirmed_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bConfirmed_MetaData), NewProp_bConfirmed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partners_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Partners,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Credits,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiRubies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bConfirmed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonTradeOffer Property Definitions *****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonTradeOffer",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonTradeOffer>(),
	alignof(FDigimonTradeOffer),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonTradeOffer;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeOffer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonTradeOffer, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonTradeOffer"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonTradeOffer.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonTradeOffer **************************************************

// ********** Begin ScriptStruct FDigimonDirectTrade ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonDirectTrade_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonDirectTrade>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonDirectTrade); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SessionId_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstAccountId_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstName_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondAccountId_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondName_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_First_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Second_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpiresUnix_MetaData[] = {
		{ "Category", "DigimonDirectTrade" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonDirectTrade constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SessionId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Revision;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FirstAccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FirstName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SecondAccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SecondName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_First;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Second;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_ExpiresUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonDirectTrade constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonDirectTrade>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonDirectTrade Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SessionId = { "SessionId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, SessionId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SessionId_MetaData), NewProp_SessionId_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_FirstAccountId = { "FirstAccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, FirstAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstAccountId_MetaData), NewProp_FirstAccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_FirstName = { "FirstName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, FirstName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstName_MetaData), NewProp_FirstName_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SecondAccountId = { "SecondAccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, SecondAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondAccountId_MetaData), NewProp_SecondAccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SecondName = { "SecondName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, SecondName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondName_MetaData), NewProp_SecondName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_First = { "First", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, First), Z_Construct_UScriptStruct_FDigimonTradeOffer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_First_MetaData), NewProp_First_MetaData) }; // 33d3504db13bf7c108090e3ec92b5162c7d4de11
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Second = { "Second", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, Second), Z_Construct_UScriptStruct_FDigimonTradeOffer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Second_MetaData), NewProp_Second_MetaData) }; // 33d3504db13bf7c108090e3ec92b5162c7d4de11
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_ExpiresUnix = { "ExpiresUnix", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonDirectTrade, ExpiresUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpiresUnix_MetaData), NewProp_ExpiresUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FirstAccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FirstName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SecondAccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SecondName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_First,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Second,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExpiresUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonDirectTrade Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonDirectTrade",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonDirectTrade>(),
	alignof(FDigimonDirectTrade),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonDirectTrade;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonDirectTrade(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonDirectTrade, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonDirectTrade"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonDirectTrade.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonDirectTrade *************************************************

// ********** Begin ScriptStruct FDigimonTradeView *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonTradeView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonTradeView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonTradeView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Listings_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Page_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalListings_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Search_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMineOnly_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Session_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PurchaseReview_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PurchaseToken_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "DigimonTradeView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonTradeView constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Listings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Listings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Page;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TotalListings;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Search;
	static void NewProp_bMineOnly_SetBit(void* Obj)
	{
		((FDigimonTradeView*)Obj)->bMineOnly = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMineOnly;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Session;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PurchaseReview;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PurchaseToken;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Status;
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((FDigimonTradeView*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonTradeView constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonTradeView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonTradeView Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Listings_Inner = { "Listings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonTradeListing, METADATA_PARAMS(0, nullptr) }; // 8385e6da4226f0af5d025d3b5d5c4a2503b2bca7
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Listings = { "Listings", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, Listings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Listings_MetaData), NewProp_Listings_MetaData) }; // 8385e6da4226f0af5d025d3b5d5c4a2503b2bca7
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, Page), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Page_MetaData), NewProp_Page_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TotalListings = { "TotalListings", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, TotalListings), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalListings_MetaData), NewProp_TotalListings_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Search = { "Search", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, Search), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Search_MetaData), NewProp_Search_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bMineOnly = { "bMineOnly", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonTradeView), &UHT_STATICS::NewProp_bMineOnly_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMineOnly_MetaData), NewProp_bMineOnly_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Session = { "Session", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, Session), Z_Construct_UScriptStruct_FDigimonDirectTrade, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Session_MetaData), NewProp_Session_MetaData) }; // cbfbc68c0aeac316cc3675e5d4a812ed720dc17f
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PurchaseReview = { "PurchaseReview", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, PurchaseReview), Z_Construct_UScriptStruct_FDigimonTradeListing, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PurchaseReview_MetaData), NewProp_PurchaseReview_MetaData) }; // 8385e6da4226f0af5d025d3b5d5c4a2503b2bca7
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PurchaseToken = { "PurchaseToken", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, PurchaseToken), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PurchaseToken_MetaData), NewProp_PurchaseToken_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeView, Status), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Status_MetaData), NewProp_Status_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonTradeView), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Listings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Listings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TotalListings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Search,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bMineOnly,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Session,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PurchaseReview,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PurchaseToken,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Status,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonTradeView Property Definitions ******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonTradeView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonTradeView>(),
	alignof(FDigimonTradeView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonTradeView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonTradeView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonTradeView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonTradeView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonTradeView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonTradeView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonTradeView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonTradeView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonTradeView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonTradeView ***************************************************

// ********** Begin ScriptStruct FDigimonTradeMarket ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonTradeMarket_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonTradeMarket>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonTradeMarket); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Private server storage. Escrow is removed from its seller before a listing is published. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Private server storage. Escrow is removed from its seller before a listing is published." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Listings_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTradeTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonTradeMarket constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Listings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Listings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonTradeMarket constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonTradeMarket>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonTradeMarket Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeMarket, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Listings_Inner = { "Listings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonTradeListing, METADATA_PARAMS(0, nullptr) }; // 8385e6da4226f0af5d025d3b5d5c4a2503b2bca7
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Listings = { "Listings", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonTradeMarket, Listings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Listings_MetaData), NewProp_Listings_MetaData) }; // 8385e6da4226f0af5d025d3b5d5c4a2503b2bca7
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Listings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Listings,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonTradeMarket Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonTradeMarket",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonTradeMarket>(),
	alignof(FDigimonTradeMarket),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonTradeMarket;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonTradeMarket(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonTradeMarket, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonTradeMarket"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonTradeMarket.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonTradeMarket *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeTypes_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonTradeListing, Z_Construct_UScriptStruct_FDigimonTradeListing_Statics::NewStructOps, TEXT("DigimonTradeListing"),&Z_Registration_Info_UScriptStruct_FDigimonTradeListing, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonTradeListing), 2206590682U) },
		{ Z_Construct_UScriptStruct_FDigimonTradeOffer, Z_Construct_UScriptStruct_FDigimonTradeOffer_Statics::NewStructOps, TEXT("DigimonTradeOffer"),&Z_Registration_Info_UScriptStruct_FDigimonTradeOffer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonTradeOffer), 869486669U) },
		{ Z_Construct_UScriptStruct_FDigimonDirectTrade, Z_Construct_UScriptStruct_FDigimonDirectTrade_Statics::NewStructOps, TEXT("DigimonDirectTrade"),&Z_Registration_Info_UScriptStruct_FDigimonDirectTrade, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonDirectTrade), 3422275212U) },
		{ Z_Construct_UScriptStruct_FDigimonTradeView, Z_Construct_UScriptStruct_FDigimonTradeView_Statics::NewStructOps, TEXT("DigimonTradeView"),&Z_Registration_Info_UScriptStruct_FDigimonTradeView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonTradeView), 3796457059U) },
		{ Z_Construct_UScriptStruct_FDigimonTradeMarket, Z_Construct_UScriptStruct_FDigimonTradeMarket_Statics::NewStructOps, TEXT("DigimonTradeMarket"),&Z_Registration_Info_UScriptStruct_FDigimonTradeMarket, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonTradeMarket), 2082445181U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeTypes_h__Script_DigimonVenomNXTRuntime_68e8444e727e8d84c57fd9ef130cbfce9966f750{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
