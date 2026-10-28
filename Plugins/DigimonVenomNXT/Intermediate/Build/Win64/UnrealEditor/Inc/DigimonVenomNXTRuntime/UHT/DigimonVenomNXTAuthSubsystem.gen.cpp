// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAuthSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USaveGame(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAccountRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAuthResult(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonAuthResultEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonAuthResultEvent ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonAuthResultEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonAuthResultEvent_Parms
	{
		FDigimonAuthResult Result;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonAuthResultEvent constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Result;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonAuthResultEvent constinit property declarations *****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonAuthResultEvent Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonAuthResultEvent_Parms, Result), Z_Construct_UScriptStruct_FDigimonAuthResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Result_MetaData), NewProp_Result_MetaData) }; // f3e13be835c9c5fbfe44ef4e4e4b443b7b7ec2b6
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Result,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonAuthResultEvent Property Definitions ****************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonAuthResultEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonAuthResultEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonAuthResultEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonAuthResultEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonAuthResultEvent *************************************************

// ********** Begin ScriptStruct FDigimonAccountRecord *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonAccountRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonAccountRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonAccountRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "Category", "DigimonAccountRecord" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "Category", "DigimonAccountRecord" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Salt_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PasswordHash_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HashIterations_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreatedUnix_MetaData[] = {
		{ "Category", "DigimonAccountRecord" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonAccountRecord constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Salt;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PasswordHash;
	static const UECodeGen_Private::FIntPropertyParams NewProp_HashIterations;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_CreatedUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonAccountRecord constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonAccountRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonAccountRecord Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000001000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000001000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Salt = { "Salt", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, Salt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Salt_MetaData), NewProp_Salt_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_PasswordHash = { "PasswordHash", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, PasswordHash), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PasswordHash_MetaData), NewProp_PasswordHash_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_HashIterations = { "HashIterations", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, HashIterations), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HashIterations_MetaData), NewProp_HashIterations_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_CreatedUnix = { "CreatedUnix", nullptr, (EPropertyFlags)0x0010000001000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonAccountRecord, CreatedUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreatedUnix_MetaData), NewProp_CreatedUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Salt,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PasswordHash,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HashIterations,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CreatedUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonAccountRecord Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonAccountRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonAccountRecord>(),
	alignof(FDigimonAccountRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonAccountRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonAccountRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonAccountRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonAccountRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonAccountRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonAccountRecord ***********************************************

// ********** Begin Class UDigimonVenomNXTAccountSaveGame ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Host-owned Unreal SaveGame database for Digimon Venom NXT accounts. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAuthSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Host-owned Unreal SaveGame database for Digimon Venom NXT accounts." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Accounts_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAccountSaveGame constinit property declarations **********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Accounts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Accounts;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTAccountSaveGame constinit property declarations ************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAccountSaveGame>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTAccountSaveGame Property Definitions *********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Accounts_Inner = { "Accounts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonAccountRecord, METADATA_PARAMS(0, nullptr) }; // b80537f19423538b949a3b2249f085d35ced4477
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Accounts = { "Accounts", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAccountSaveGame, Accounts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Accounts_MetaData), NewProp_Accounts_MetaData) }; // b80537f19423538b949a3b2249f085d35ced4477
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTAccountSaveGame Property Definitions ***********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_USaveGame,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame;
UClass* Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAccountSaveGame;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAccountSaveGame"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAccountSaveGame::UDigimonVenomNXTAccountSaveGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAccountSaveGame);
UDigimonVenomNXTAccountSaveGame::~UDigimonVenomNXTAccountSaveGame() {}
// ********** End Class UDigimonVenomNXTAccountSaveGame ********************************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function CreateAccount *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_CreateAccount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventCreateAccount_Parms
	{
		FString Username;
		FString Password;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stages credentials for creating an account on the host when Host/Join is selected. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stages credentials for creating an account on the host when Host/Join is selected." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateAccount constinit property declarations *************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateAccount constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateAccount Property Definitions ************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventCreateAccount_Parms, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventCreateAccount_Parms, Password), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Password_MetaData), NewProp_Password_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Password,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CreateAccount Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "CreateAccount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventCreateAccount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventCreateAccount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_CreateAccount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execCreateAccount)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Username);
	P_GET_PROPERTY(FStrProperty,Z_Param_Password);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CreateAccount(Z_Param_Username,Z_Param_Password);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function CreateAccount ***********************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function GetAccountId **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountId_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventGetAccountId_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAccountId constinit property declarations **************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAccountId constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAccountId Property Definitions *************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventGetAccountId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAccountId Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "GetAccountId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetAccountId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetAccountId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execGetAccountId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetAccountId();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function GetAccountId ************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function GetAccountSaveSlotName ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountSaveSlotName_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventGetAccountSaveSlotName_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** SaveGame slot name containing the host's account database. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SaveGame slot name containing the host's account database." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetAccountSaveSlotName constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAccountSaveSlotName constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAccountSaveSlotName Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventGetAccountSaveSlotName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAccountSaveSlotName Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "GetAccountSaveSlotName", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetAccountSaveSlotName_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetAccountSaveSlotName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountSaveSlotName(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execGetAccountSaveSlotName)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UDigimonVenomNXTAuthSubsystem::GetAccountSaveSlotName();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function GetAccountSaveSlotName **************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function GetLastAuthMessage ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetLastAuthMessage_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventGetLastAuthMessage_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetLastAuthMessage constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLastAuthMessage constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLastAuthMessage Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventGetLastAuthMessage_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetLastAuthMessage Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "GetLastAuthMessage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetLastAuthMessage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetLastAuthMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetLastAuthMessage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execGetLastAuthMessage)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetLastAuthMessage();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function GetLastAuthMessage ******************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function GetUsername ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetUsername_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventGetUsername_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetUsername constinit property declarations ***************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetUsername constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetUsername Property Definitions **************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventGetUsername_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetUsername Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "GetUsername", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetUsername_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventGetUsername_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetUsername(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execGetUsername)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetUsername();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function GetUsername *************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function HasPendingCredentials *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_HasPendingCredentials_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventHasPendingCredentials_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HasPendingCredentials constinit property declarations *****************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAuthSubsystem_eventHasPendingCredentials_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasPendingCredentials constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasPendingCredentials Property Definitions ****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAuthSubsystem_eventHasPendingCredentials_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasPendingCredentials Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "HasPendingCredentials", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventHasPendingCredentials_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventHasPendingCredentials_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_HasPendingCredentials(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execHasPendingCredentials)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasPendingCredentials();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function HasPendingCredentials ***************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function IsLoggedIn ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsLoggedIn_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventIsLoggedIn_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsLoggedIn constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAuthSubsystem_eventIsLoggedIn_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsLoggedIn constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsLoggedIn Property Definitions ***************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAuthSubsystem_eventIsLoggedIn_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsLoggedIn Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "IsLoggedIn", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventIsLoggedIn_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventIsLoggedIn_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsLoggedIn(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execIsLoggedIn)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsLoggedIn();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function IsLoggedIn **************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function IsPendingCreateAccount ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsPendingCreateAccount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventIsPendingCreateAccount_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsPendingCreateAccount constinit property declarations ****************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAuthSubsystem_eventIsPendingCreateAccount_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsPendingCreateAccount constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsPendingCreateAccount Property Definitions ***************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAuthSubsystem_eventIsPendingCreateAccount_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsPendingCreateAccount Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "IsPendingCreateAccount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventIsPendingCreateAccount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventIsPendingCreateAccount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsPendingCreateAccount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execIsPendingCreateAccount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsPendingCreateAccount();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function IsPendingCreateAccount **************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function Login *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Login_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventLogin_Parms
	{
		FString Username;
		FString Password;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stages credentials for logging into the host when Host/Join is selected. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stages credentials for logging into the host when Host/Join is selected." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function Login constinit property declarations *********************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Login constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Login Property Definitions ********************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventLogin_Parms, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAuthSubsystem_eventLogin_Parms, Password), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Password_MetaData), NewProp_Password_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Password,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function Login Property Definitions **********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "Login", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventLogin_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventLogin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Login(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execLogin)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Username);
	P_GET_PROPERTY(FStrProperty,Z_Param_Password);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Login(Z_Param_Username,Z_Param_Password);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function Login *******************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function Logout ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Logout_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Logout constinit property declarations ********************************
// ********** End Function Logout constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "Logout", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Logout(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execLogout)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Logout();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function Logout ******************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Function WasLastAuthSuccessful *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_WasLastAuthSuccessful_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAuthSubsystem_eventWasLastAuthSuccessful_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function WasLastAuthSuccessful constinit property declarations *****************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTAuthSubsystem_eventWasLastAuthSuccessful_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function WasLastAuthSuccessful constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function WasLastAuthSuccessful Property Definitions ****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAuthSubsystem_eventWasLastAuthSuccessful_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function WasLastAuthSuccessful Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, nullptr, "WasLastAuthSuccessful", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventWasLastAuthSuccessful_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAuthSubsystem_eventWasLastAuthSuccessful_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_WasLastAuthSuccessful(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAuthSubsystem::execWasLastAuthSuccessful)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->WasLastAuthSuccessful();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAuthSubsystem Function WasLastAuthSuccessful ***************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Pure Unreal Engine account subsystem.\n *\n * There is deliberately no HTTP account service, auth URL, auth TCP port,\n * signed session token, signing secret, web endpoint or external backend.\n * The authoritative host stores accounts in an Unreal SaveGame slot and\n * validates Create/Login requests received over the normal UE gameplay connection.\n */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAuthSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pure Unreal Engine account subsystem.\n\nThere is deliberately no HTTP account service, auth URL, auth TCP port,\nsigned session token, signing secret, web endpoint or external backend.\nThe authoritative host stores accounts in an Unreal SaveGame slot and\nvalidates Create/Login requests received over the normal UE gameplay connection." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAuthResult_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAuthSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAuthSubsystem constinit property declarations ************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAuthResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTAuthSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CreateAccount"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execCreateAccount },
		{ .NameUTF8 = UTF8TEXT("GetAccountId"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execGetAccountId },
		{ .NameUTF8 = UTF8TEXT("GetAccountSaveSlotName"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execGetAccountSaveSlotName },
		{ .NameUTF8 = UTF8TEXT("GetLastAuthMessage"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execGetLastAuthMessage },
		{ .NameUTF8 = UTF8TEXT("GetUsername"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execGetUsername },
		{ .NameUTF8 = UTF8TEXT("HasPendingCredentials"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execHasPendingCredentials },
		{ .NameUTF8 = UTF8TEXT("IsLoggedIn"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execIsLoggedIn },
		{ .NameUTF8 = UTF8TEXT("IsPendingCreateAccount"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execIsPendingCreateAccount },
		{ .NameUTF8 = UTF8TEXT("Login"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execLogin },
		{ .NameUTF8 = UTF8TEXT("Logout"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execLogout },
		{ .NameUTF8 = UTF8TEXT("WasLastAuthSuccessful"), .Pointer = &UDigimonVenomNXTAuthSubsystem::execWasLastAuthSuccessful },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_CreateAccount, "CreateAccount" }, // 19e378dcd7961e9b30119834650434ce8f376bdc
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountId, "GetAccountId" }, // 249e3e348c279b91d53479bcf67e2337019b7e8f
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetAccountSaveSlotName, "GetAccountSaveSlotName" }, // 8837da2332fe3f5dc521d84445818893e5389ad5
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetLastAuthMessage, "GetLastAuthMessage" }, // 94fa084d4eec7afbe9856dfa14396a0cc62fcd43
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_GetUsername, "GetUsername" }, // d1ff9bfb4c2d9a58bfe7830eca580c4b8f713627
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_HasPendingCredentials, "HasPendingCredentials" }, // 2f43ac3243ed6724670b08ba1e8390e6596bf238
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsLoggedIn, "IsLoggedIn" }, // 93e5f36c6ddc5aa9dbeb02b3644edce1a26e8cb9
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_IsPendingCreateAccount, "IsPendingCreateAccount" }, // 099c57878f2a17ce0ddab63ff76c232a28fb0d1d
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Login, "Login" }, // 04ef0ef9128c44424bc43495a67b4e6342d45e1e
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_Logout, "Logout" }, // 2c7766efde316f4f73eb56a4dc453c5931957b43
		{ &Z_Construct_UFunction_UDigimonVenomNXTAuthSubsystem_WasLastAuthSuccessful, "WasLastAuthSuccessful" }, // a33d3fc31740cfb53d9378291f37c8568e75a838
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAuthSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTAuthSubsystem Property Definitions ***********************
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnAuthResult = { "OnAuthResult", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAuthSubsystem, OnAuthResult), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonAuthResultEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAuthResult_MetaData), NewProp_OnAuthResult_MetaData) }; // af722057047cca16e9d7ba8c1ffcbbf8c040fd58
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnAuthResult,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTAuthSubsystem Property Definitions *************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem,
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
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTAuthSubsystem_StaticRegisterNativesUDigimonVenomNXTAuthSubsystem()
{
	UClass* Class = UDigimonVenomNXTAuthSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAuthSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAuthSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.InnerSingleton,
				UDigimonVenomNXTAuthSubsystem_StaticRegisterNativesUDigimonVenomNXTAuthSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAuthSubsystem::UDigimonVenomNXTAuthSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAuthSubsystem);
UDigimonVenomNXTAuthSubsystem::~UDigimonVenomNXTAuthSubsystem() {}
// ********** End Class UDigimonVenomNXTAuthSubsystem **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonAccountRecord, Z_Construct_UScriptStruct_FDigimonAccountRecord_Statics::NewStructOps, TEXT("DigimonAccountRecord"),&Z_Registration_Info_UScriptStruct_FDigimonAccountRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonAccountRecord), 3087349745U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame, TEXT("UDigimonVenomNXTAccountSaveGame"), &Z_Registration_Info_UClass_UDigimonVenomNXTAccountSaveGame, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAccountSaveGame), 513205894U) },
		{ Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem, TEXT("UDigimonVenomNXTAuthSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTAuthSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAuthSubsystem), 4293433534U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h__Script_DigimonVenomNXTRuntime_4ffa33cc6b421fc72e39252bd44a2a57e0cfbf14{
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
