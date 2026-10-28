// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTProfileSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonPlayerProfile(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonArchive(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonArchivePage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTProfileSubsystem Function DeleteProfile ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_DeleteProfile_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms
	{
		FString AccountId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeleteProfile constinit property declarations *************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeleteProfile constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeleteProfile Property Definitions ************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeleteProfile Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem, nullptr, "DeleteProfile", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventDeleteProfile_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_DeleteProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTProfileSubsystem::execDeleteProfile)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_AccountId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeleteProfile(Z_Param_AccountId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTProfileSubsystem Function DeleteProfile ********************

// ********** Begin Class UDigimonVenomNXTProfileSubsystem Function LoadProfile ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadProfile_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms
	{
		FString AccountId;
		FString Username;
		FDigimonPlayerProfile OutProfile;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadProfile constinit property declarations ***************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutProfile;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function LoadProfile constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function LoadProfile Property Definitions **************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutProfile = { "OutProfile", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms, OutProfile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(0, nullptr) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutProfile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function LoadProfile Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem, nullptr, "LoadProfile", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventLoadProfile_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTProfileSubsystem::execLoadProfile)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_AccountId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Username);
	P_GET_STRUCT_REF(FDigimonPlayerProfile,Z_Param_Out_OutProfile);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadProfile(Z_Param_AccountId,Z_Param_Username,Z_Param_Out_OutProfile);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTProfileSubsystem Function LoadProfile **********************

// ********** Begin Class UDigimonVenomNXTProfileSubsystem Function LoadSeasonArchive **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadSeasonArchive_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms
	{
		FDigimonPlayerProfile Profile;
		int32 Page;
		int32 PageSize;
		FDigimonSeasonArchivePage OutPage;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reads private history through the last accepted profile week, including pending server-memory records. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reads private history through the last accepted profile week, including pending server-memory records." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Profile_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadSeasonArchive constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Profile;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Page;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageSize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutPage;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function LoadSeasonArchive constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function LoadSeasonArchive Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Profile = { "Profile", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms, Profile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Profile_MetaData), NewProp_Profile_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms, Page), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageSize = { "PageSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms, PageSize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutPage = { "OutPage", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms, OutPage), Z_Construct_UScriptStruct_FDigimonSeasonArchivePage, METADATA_PARAMS(0, nullptr) }; // 80c6bd44f1ff8717382adef8167abbcfb94ffd23
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Profile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutPage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function LoadSeasonArchive Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem, nullptr, "LoadSeasonArchive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventLoadSeasonArchive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadSeasonArchive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTProfileSubsystem::execLoadSeasonArchive)
{
	P_GET_STRUCT_REF(FDigimonPlayerProfile,Z_Param_Out_Profile);
	P_GET_PROPERTY(FIntProperty,Z_Param_Page);
	P_GET_PROPERTY(FIntProperty,Z_Param_PageSize);
	P_GET_STRUCT_REF(FDigimonSeasonArchivePage,Z_Param_Out_OutPage);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadSeasonArchive(Z_Param_Out_Profile,Z_Param_Page,Z_Param_PageSize,Z_Param_Out_OutPage);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTProfileSubsystem Function LoadSeasonArchive ****************

// ********** Begin Class UDigimonVenomNXTProfileSubsystem Function SaveProfile ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_SaveProfile_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms
	{
		FDigimonPlayerProfile Profile;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Accepts authoritative progress. With autosaves OFF this retains a value snapshot in server memory only. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Accepts authoritative progress. With autosaves OFF this retains a value snapshot in server memory only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Profile_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveProfile constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Profile;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SaveProfile constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SaveProfile Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Profile = { "Profile", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms, Profile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Profile_MetaData), NewProp_Profile_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Profile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SaveProfile Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem, nullptr, "SaveProfile", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTProfileSubsystem_eventSaveProfile_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_SaveProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTProfileSubsystem::execSaveProfile)
{
	P_GET_STRUCT_REF(FDigimonPlayerProfile,Z_Param_Out_Profile);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SaveProfile(Z_Param_Out_Profile);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTProfileSubsystem Function SaveProfile **********************

// ********** Begin Class UDigimonVenomNXTProfileSubsystem *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTProfileSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SessionProfiles_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Value snapshots outlive PlayerController/PlayerState destruction, but not the server process.\n" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Value snapshots outlive PlayerController/PlayerState destruction, but not the server process." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeferredSeasonRecords_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTProfileSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTProfileSubsystem constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_SessionProfiles_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SessionProfiles_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_SessionProfiles;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DeferredSeasonRecords_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DeferredSeasonRecords_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_DeferredSeasonRecords;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTProfileSubsystem constinit property declarations ***********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DeleteProfile"), .Pointer = &UDigimonVenomNXTProfileSubsystem::execDeleteProfile },
		{ .NameUTF8 = UTF8TEXT("LoadProfile"), .Pointer = &UDigimonVenomNXTProfileSubsystem::execLoadProfile },
		{ .NameUTF8 = UTF8TEXT("LoadSeasonArchive"), .Pointer = &UDigimonVenomNXTProfileSubsystem::execLoadSeasonArchive },
		{ .NameUTF8 = UTF8TEXT("SaveProfile"), .Pointer = &UDigimonVenomNXTProfileSubsystem::execSaveProfile },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_DeleteProfile, "DeleteProfile" }, // 8ec34449531cb199eb18fa88b842499723edbb06
		{ &Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadProfile, "LoadProfile" }, // a0d25ec70ee87eed96e152c75191e10000a20202
		{ &Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_LoadSeasonArchive, "LoadSeasonArchive" }, // 67b8aa05453deedbb17e129c39aad0c47b4575b3
		{ &Z_Construct_UFunction_UDigimonVenomNXTProfileSubsystem_SaveProfile, "SaveProfile" }, // 478bd86e9b9ae9ac5030341449f6608b12b9caaa
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTProfileSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTProfileSubsystem Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SessionProfiles_ValueProp = { "SessionProfiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(0, nullptr) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SessionProfiles_Key_KeyProp = { "SessionProfiles_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_SessionProfiles = { "SessionProfiles", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTProfileSubsystem, SessionProfiles), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SessionProfiles_MetaData), NewProp_SessionProfiles_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DeferredSeasonRecords_ValueProp = { "DeferredSeasonRecords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FDigimonSeasonArchive, METADATA_PARAMS(0, nullptr) }; // a4a0519d8c251fbce9ddd1eecaca3935dd95e4ed
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DeferredSeasonRecords_Key_KeyProp = { "DeferredSeasonRecords_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_DeferredSeasonRecords = { "DeferredSeasonRecords", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTProfileSubsystem, DeferredSeasonRecords), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeferredSeasonRecords_MetaData), NewProp_DeferredSeasonRecords_MetaData) }; // a4a0519d8c251fbce9ddd1eecaca3935dd95e4ed
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionProfiles_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionProfiles_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SessionProfiles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeferredSeasonRecords_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeferredSeasonRecords_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeferredSeasonRecords,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTProfileSubsystem Property Definitions **********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem,
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
static void UDigimonVenomNXTProfileSubsystem_StaticRegisterNativesUDigimonVenomNXTProfileSubsystem()
{
	UClass* Class = UDigimonVenomNXTProfileSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTProfileSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTProfileSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.InnerSingleton,
				UDigimonVenomNXTProfileSubsystem_StaticRegisterNativesUDigimonVenomNXTProfileSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTProfileSubsystem::UDigimonVenomNXTProfileSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTProfileSubsystem);
UDigimonVenomNXTProfileSubsystem::~UDigimonVenomNXTProfileSubsystem() {}
// ********** End Class UDigimonVenomNXTProfileSubsystem *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTProfileSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTProfileSubsystem, TEXT("UDigimonVenomNXTProfileSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTProfileSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTProfileSubsystem), 1570672388U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTProfileSubsystem_h__Script_DigimonVenomNXTRuntime_c950a8ac6b791e69dad254eea2303e2bf2ade57c{
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
