// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTServerConsoleSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USaveGame(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonServerModerationRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonServerModerationRecord ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonServerModerationRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonServerModerationRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonServerModerationRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BannedUntil_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Zero means absent; -1 means permanent. Positive values are UTC Unix expiry. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zero means absent; -1 means permanent. Positive values are UTC Unix expiry." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MutedUntil_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JailedUntil_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BanReason_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MuteReason_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JailReason_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Warnings_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonServerModerationRecord constinit property declarations ****
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_BannedUntil;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_MutedUntil;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_JailedUntil;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BanReason;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MuteReason;
	static const UECodeGen_Private::FStrPropertyParams NewProp_JailReason;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Warnings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Warnings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonServerModerationRecord constinit property declarations ******
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonServerModerationRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonServerModerationRecord Property Definitions ***************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_BannedUntil = { "BannedUntil", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, BannedUntil), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BannedUntil_MetaData), NewProp_BannedUntil_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_MutedUntil = { "MutedUntil", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, MutedUntil), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MutedUntil_MetaData), NewProp_MutedUntil_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_JailedUntil = { "JailedUntil", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, JailedUntil), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JailedUntil_MetaData), NewProp_JailedUntil_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_BanReason = { "BanReason", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, BanReason), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BanReason_MetaData), NewProp_BanReason_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_MuteReason = { "MuteReason", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, MuteReason), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MuteReason_MetaData), NewProp_MuteReason_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_JailReason = { "JailReason", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, JailReason), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JailReason_MetaData), NewProp_JailReason_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Warnings_Inner = { "Warnings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Warnings = { "Warnings", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonServerModerationRecord, Warnings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Warnings_MetaData), NewProp_Warnings_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BannedUntil,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MutedUntil,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JailedUntil,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BanReason,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MuteReason,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JailReason,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Warnings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Warnings,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonServerModerationRecord Property Definitions *****************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonServerModerationRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonServerModerationRecord>(),
	alignof(FDigimonServerModerationRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonServerModerationRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonServerModerationRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonServerModerationRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonServerModerationRecord **************************************

// ********** Begin Class UDigimonVenomNXTServerModerationSaveGame *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "DigimonVenomNXTServerConsoleSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Accounts_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Titles_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTServerModerationSaveGame constinit property declarations *
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Accounts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Accounts;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Titles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Titles;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTServerModerationSaveGame constinit property declarations ***
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTServerModerationSaveGame>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTServerModerationSaveGame Property Definitions ************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerModerationSaveGame, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Accounts_Inner = { "Accounts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonServerModerationRecord, METADATA_PARAMS(0, nullptr) }; // 4370d1fa5122f83634565622410c25dc33446041
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Accounts = { "Accounts", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerModerationSaveGame, Accounts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Accounts_MetaData), NewProp_Accounts_MetaData) }; // 4370d1fa5122f83634565622410c25dc33446041
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Titles_Inner = { "Titles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Titles = { "Titles", nullptr, (EPropertyFlags)0x0010000001000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerModerationSaveGame, Titles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Titles_MetaData), NewProp_Titles_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Titles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Titles,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTServerModerationSaveGame Property Definitions **************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_USaveGame,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame;
UClass* Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTServerModerationSaveGame;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTServerModerationSaveGame"),
				Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTServerModerationSaveGame::UDigimonVenomNXTServerModerationSaveGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTServerModerationSaveGame);
UDigimonVenomNXTServerModerationSaveGame::~UDigimonVenomNXTServerModerationSaveGame() {}
// ********** End Class UDigimonVenomNXTServerModerationSaveGame ***********************************

// ********** Begin Class UDigimonVenomNXTServerConsoleSubsystem ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Host-and-play console. Intentionally no Blueprint execution, RPC, Exec or chat entry point. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTServerConsoleSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Host-and-play console. Intentionally no Blueprint execution, RPC, Exec or chat entry point." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Moderation_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTServerConsoleSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTServerConsoleSubsystem constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Moderation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTServerConsoleSubsystem constinit property declarations *****
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTServerConsoleSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTServerConsoleSubsystem Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Moderation = { "Moderation", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTServerConsoleSubsystem, Moderation), Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Moderation_MetaData), NewProp_Moderation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Moderation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTServerConsoleSubsystem Property Definitions ****************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UGameInstanceSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTServerConsoleSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTServerConsoleSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.InnerSingleton,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTServerConsoleSubsystem::UDigimonVenomNXTServerConsoleSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTServerConsoleSubsystem);
UDigimonVenomNXTServerConsoleSubsystem::~UDigimonVenomNXTServerConsoleSubsystem() {}
// ********** End Class UDigimonVenomNXTServerConsoleSubsystem *************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTServerConsoleSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonServerModerationRecord, Z_Construct_UScriptStruct_FDigimonServerModerationRecord_Statics::NewStructOps, TEXT("DigimonServerModerationRecord"),&Z_Registration_Info_UScriptStruct_FDigimonServerModerationRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonServerModerationRecord), 1131467258U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTServerModerationSaveGame, TEXT("UDigimonVenomNXTServerModerationSaveGame"), &Z_Registration_Info_UClass_UDigimonVenomNXTServerModerationSaveGame, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTServerModerationSaveGame), 3846304628U) },
		{ Z_Construct_UClass_UDigimonVenomNXTServerConsoleSubsystem, TEXT("UDigimonVenomNXTServerConsoleSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTServerConsoleSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTServerConsoleSubsystem), 4097603314U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTServerConsoleSubsystem_h__Script_DigimonVenomNXTRuntime_9cb3d2a5f7e8eb0df5e2de372bd6ec041bbf09cd{
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
