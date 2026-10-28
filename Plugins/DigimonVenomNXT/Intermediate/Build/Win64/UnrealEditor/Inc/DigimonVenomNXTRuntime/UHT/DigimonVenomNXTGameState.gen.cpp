// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTGameState() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameStateBase(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRankedPublicEntry(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonServerStateChanged__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonShopItemDefinition(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTGameState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTGameState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonServerStateChanged ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonServerStateChanged__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonServerStateChanged constinit property declarations ************
// ********** End Delegate FDigimonServerStateChanged constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonServerStateChanged__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonServerStateChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonServerStateChanged **********************************************

// ********** Begin Class ADigimonVenomNXTGameState Function GetOnlinePlayerCount ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameState_GetOnlinePlayerCount_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameState_eventGetOnlinePlayerCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetOnlinePlayerCount constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetOnlinePlayerCount constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetOnlinePlayerCount Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameState_eventGetOnlinePlayerCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetOnlinePlayerCount Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameState, nullptr, "GetOnlinePlayerCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameState_eventGetOnlinePlayerCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameState_eventGetOnlinePlayerCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameState_GetOnlinePlayerCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameState::execGetOnlinePlayerCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetOnlinePlayerCount();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameState Function GetOnlinePlayerCount ********************

// ********** Begin Class ADigimonVenomNXTGameState Function OnRep_ServerState *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameState_OnRep_ServerState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_ServerState constinit property declarations *********************
// ********** End Function OnRep_ServerState constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameState, nullptr, "OnRep_ServerState", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameState_OnRep_ServerState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameState::execOnRep_ServerState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_ServerState();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameState Function OnRep_ServerState ***********************

// ********** Begin Class ADigimonVenomNXTGameState ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTGameState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Small, public server summary. Private player profiles live on PlayerState with owner-only replication. */" },
#endif
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DigimonVenomNXTGameState.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Small, public server summary. Private player profiles live on PlayerState with owner-only replication." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerDisplayName_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPlayers_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AtlasMapCount_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PersistentAIRivalCount_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShopCatalog_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Economy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Public effective economy; hosting secrets never enter replicated state. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Public effective economy; hosting secrets never enter replicated state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreditsPerDigiRuby_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Economy" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedSeasonId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RankedTop100_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnServerStateChanged_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Server" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTGameState constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerDisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPlayers;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasMapCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PersistentAIRivalCount;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShopCatalog_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ShopCatalog;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CreditsPerDigiRuby;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RankedSeasonId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RankedTop100_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RankedTop100;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnServerStateChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTGameState constinit property declarations ******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetOnlinePlayerCount"), .Pointer = &ADigimonVenomNXTGameState::execGetOnlinePlayerCount },
		{ .NameUTF8 = UTF8TEXT("OnRep_ServerState"), .Pointer = &ADigimonVenomNXTGameState::execOnRep_ServerState },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameState_GetOnlinePlayerCount, "GetOnlinePlayerCount" }, // cf3c8f403a2fdec7eec6faacca956ebcc898c0cb
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameState_OnRep_ServerState, "OnRep_ServerState" }, // ff227bc4163028dec18d289c2aaaf1d45790899e
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTGameState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTGameState Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ServerDisplayName = { "ServerDisplayName", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, ServerDisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerDisplayName_MetaData), NewProp_ServerDisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxPlayers = { "MaxPlayers", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, MaxPlayers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPlayers_MetaData), NewProp_MaxPlayers_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AtlasMapCount = { "AtlasMapCount", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, AtlasMapCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AtlasMapCount_MetaData), NewProp_AtlasMapCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PersistentAIRivalCount = { "PersistentAIRivalCount", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, PersistentAIRivalCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PersistentAIRivalCount_MetaData), NewProp_PersistentAIRivalCount_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ShopCatalog_Inner = { "ShopCatalog", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonShopItemDefinition, METADATA_PARAMS(0, nullptr) }; // 23d25ed9dae8b66d2d3cb91d4f43349b1af7fe88
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ShopCatalog = { "ShopCatalog", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, ShopCatalog), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShopCatalog_MetaData), NewProp_ShopCatalog_MetaData) }; // 23d25ed9dae8b66d2d3cb91d4f43349b1af7fe88
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CreditsPerDigiRuby = { "CreditsPerDigiRuby", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, CreditsPerDigiRuby), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreditsPerDigiRuby_MetaData), NewProp_CreditsPerDigiRuby_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RankedSeasonId = { "RankedSeasonId", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, RankedSeasonId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedSeasonId_MetaData), NewProp_RankedSeasonId_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RankedTop100_Inner = { "RankedTop100", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonRankedPublicEntry, METADATA_PARAMS(0, nullptr) }; // ea5c967d263cd6cb304ebfcda1ed3ac8c9f713da
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RankedTop100 = { "RankedTop100", "OnRep_ServerState", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, RankedTop100), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RankedTop100_MetaData), NewProp_RankedTop100_MetaData) }; // ea5c967d263cd6cb304ebfcda1ed3ac8c9f713da
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnServerStateChanged = { "OnServerStateChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameState, OnServerStateChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonServerStateChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnServerStateChanged_MetaData), NewProp_OnServerStateChanged_MetaData) }; // f327a1ae2c61b20ca9842b3424848abda11a9f70
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ServerDisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AtlasMapCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PersistentAIRivalCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopCatalog_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ShopCatalog,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CreditsPerDigiRuby,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedSeasonId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedTop100_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RankedTop100,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnServerStateChanged,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTGameState Property Definitions *****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AGameStateBase,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTGameState,
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
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADigimonVenomNXTGameState_StaticRegisterNativesADigimonVenomNXTGameState()
{
	UClass* Class = ADigimonVenomNXTGameState::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTGameState;
UClass* Z_Construct_UClass_ADigimonVenomNXTGameState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTGameState;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTGameState.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTGameState"),
				Z_Registration_Info_UClass_ADigimonVenomNXTGameState.InnerSingleton,
				ADigimonVenomNXTGameState_StaticRegisterNativesADigimonVenomNXTGameState,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTGameState.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTGameState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTGameState.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTGameState.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTGameState::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_ServerDisplayName(TEXT("ServerDisplayName"));
	static FName Name_MaxPlayers(TEXT("MaxPlayers"));
	static FName Name_AtlasMapCount(TEXT("AtlasMapCount"));
	static FName Name_PersistentAIRivalCount(TEXT("PersistentAIRivalCount"));
	static FName Name_ShopCatalog(TEXT("ShopCatalog"));
	static FName Name_CreditsPerDigiRuby(TEXT("CreditsPerDigiRuby"));
	static FName Name_RankedSeasonId(TEXT("RankedSeasonId"));
	static FName Name_RankedTop100(TEXT("RankedTop100"));
	const bool bIsValid = true
		&& Name_ServerDisplayName == ClassReps[(int32)ENetFields_Private::ServerDisplayName].Property->GetFName()
		&& Name_MaxPlayers == ClassReps[(int32)ENetFields_Private::MaxPlayers].Property->GetFName()
		&& Name_AtlasMapCount == ClassReps[(int32)ENetFields_Private::AtlasMapCount].Property->GetFName()
		&& Name_PersistentAIRivalCount == ClassReps[(int32)ENetFields_Private::PersistentAIRivalCount].Property->GetFName()
		&& Name_ShopCatalog == ClassReps[(int32)ENetFields_Private::ShopCatalog].Property->GetFName()
		&& Name_CreditsPerDigiRuby == ClassReps[(int32)ENetFields_Private::CreditsPerDigiRuby].Property->GetFName()
		&& Name_RankedSeasonId == ClassReps[(int32)ENetFields_Private::RankedSeasonId].Property->GetFName()
		&& Name_RankedTop100 == ClassReps[(int32)ENetFields_Private::RankedTop100].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTGameState"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTGameState);
ADigimonVenomNXTGameState::~ADigimonVenomNXTGameState() {}
// ********** End Class ADigimonVenomNXTGameState **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTGameState, TEXT("ADigimonVenomNXTGameState"), &Z_Registration_Info_UClass_ADigimonVenomNXTGameState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTGameState), 3589289134U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameState_h__Script_DigimonVenomNXTRuntime_9d203858ea87af2b82edef347fe5b7839ebfdd28{
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
