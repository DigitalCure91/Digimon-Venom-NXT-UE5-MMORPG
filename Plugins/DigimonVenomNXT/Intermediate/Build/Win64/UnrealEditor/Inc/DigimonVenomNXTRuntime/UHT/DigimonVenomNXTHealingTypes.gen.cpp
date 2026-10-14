// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTHealingTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTHealingTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealReceipt(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealedPartner(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonHealedPartner *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonHealedPartner_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonHealedPartner>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonHealedPartner); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Authoritative recovery delta; sent only to the requesting account owner. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Authoritative recovery delta; sent only to the requesting account owner." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstanceId_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BeforeHP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BeforeSP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AfterHP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AfterSP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSP_MetaData[] = {
		{ "Category", "DigimonHealedPartner" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonHealedPartner constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BeforeHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BeforeSP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AfterHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AfterSP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxSP;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonHealedPartner constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonHealedPartner>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonHealedPartner Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstanceId_MetaData), NewProp_InstanceId_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_BeforeHP = { "BeforeHP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, BeforeHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BeforeHP_MetaData), NewProp_BeforeHP_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_BeforeSP = { "BeforeSP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, BeforeSP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BeforeSP_MetaData), NewProp_BeforeSP_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AfterHP = { "AfterHP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, AfterHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AfterHP_MetaData), NewProp_AfterHP_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AfterSP = { "AfterSP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, AfterSP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AfterSP_MetaData), NewProp_AfterSP_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxSP = { "MaxSP", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealedPartner, MaxSP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSP_MetaData), NewProp_MaxSP_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BeforeHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BeforeSP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AfterHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AfterSP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxSP,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonHealedPartner Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonHealedPartner",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonHealedPartner>(),
	alignof(FDigimonHealedPartner),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonHealedPartner;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealedPartner(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonHealedPartner, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonHealedPartner"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonHealedPartner.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonHealedPartner ***********************************************

// ********** Begin ScriptStruct FDigimonHealReceipt ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonHealReceipt_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonHealReceipt>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonHealReceipt); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Success is published only after the full recovery transaction is saved. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Success is published only after the full recovery transaction is saved." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequestId_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RecoveryRevision_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Matches the saved profile generation, even when replication coalesces later changes. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Matches the saved profile generation, even when replication coalesces later changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RestoredPartners_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartyChanges_MetaData[] = {
		{ "Category", "DigimonHealReceipt" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actual healed partners in the current six-member party; collection totals are above. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTHealingTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actual healed partners in the current six-member party; collection totals are above." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonHealReceipt constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RequestId;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_RecoveryRevision;
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((FDigimonHealReceipt*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RestoredPartners;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PartyChanges_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PartyChanges;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonHealReceipt constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonHealReceipt>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonHealReceipt Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RequestId = { "RequestId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealReceipt, RequestId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequestId_MetaData), NewProp_RequestId_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_RecoveryRevision = { "RecoveryRevision", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealReceipt, RecoveryRevision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RecoveryRevision_MetaData), NewProp_RecoveryRevision_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonHealReceipt), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealReceipt, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RestoredPartners = { "RestoredPartners", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealReceipt, RestoredPartners), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RestoredPartners_MetaData), NewProp_RestoredPartners_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PartyChanges_Inner = { "PartyChanges", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonHealedPartner, METADATA_PARAMS(0, nullptr) }; // 71a4252f7bb7b7797692aced8dce09cc6f8f78c2
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PartyChanges = { "PartyChanges", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonHealReceipt, PartyChanges), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartyChanges_MetaData), NewProp_PartyChanges_MetaData) }; // 71a4252f7bb7b7797692aced8dce09cc6f8f78c2
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequestId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecoveryRevision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RestoredPartners,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyChanges_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PartyChanges,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonHealReceipt Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonHealReceipt",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonHealReceipt>(),
	alignof(FDigimonHealReceipt),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonHealReceipt;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonHealReceipt(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonHealReceipt, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonHealReceipt"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonHealReceipt.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonHealReceipt *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTHealingTypes_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonHealedPartner, Z_Construct_UScriptStruct_FDigimonHealedPartner_Statics::NewStructOps, TEXT("DigimonHealedPartner"),&Z_Registration_Info_UScriptStruct_FDigimonHealedPartner, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonHealedPartner), 1906582831U) },
		{ Z_Construct_UScriptStruct_FDigimonHealReceipt, Z_Construct_UScriptStruct_FDigimonHealReceipt_Statics::NewStructOps, TEXT("DigimonHealReceipt"),&Z_Registration_Info_UScriptStruct_FDigimonHealReceipt, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonHealReceipt), 3068851655U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTHealingTypes_h__Script_DigimonVenomNXTRuntime_3722f3ae88f82cc47ecda69dc19d592dab8705be{
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
