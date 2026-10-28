// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTBattleActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AController(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleCommand(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonBattleStateChangedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleTeam(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleUnit(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonMoveSlot(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonPlayerProfile(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonWildEncounterEntry(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonBattleKind(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FDigimonWildEncounterEntry ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonWildEncounterEntry_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonWildEncounterEntry>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonWildEncounterEntry); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server-authored wild opponent; combat stats and identity are built by the battle actor. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server-authored wild opponent; combat stats and identity are built by the battle actor." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpeciesId_MetaData[] = {
		{ "Category", "DigimonWildEncounterEntry" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Variant_MetaData[] = {
		{ "Category", "DigimonWildEncounterEntry" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Level_MetaData[] = {
		{ "Category", "DigimonWildEncounterEntry" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonWildEncounterEntry constinit property declarations ********
	static const UECodeGen_Private::FNamePropertyParams NewProp_SpeciesId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Variant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Variant;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Level;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonWildEncounterEntry constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonWildEncounterEntry>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonWildEncounterEntry Property Definitions *******************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SpeciesId = { "SpeciesId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonWildEncounterEntry, SpeciesId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpeciesId_MetaData), NewProp_SpeciesId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Variant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Variant = { "Variant", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonWildEncounterEntry, Variant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Variant_MetaData), NewProp_Variant_MetaData) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Level = { "Level", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonWildEncounterEntry, Level), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Level_MetaData), NewProp_Level_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpeciesId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Level,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonWildEncounterEntry Property Definitions *********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonWildEncounterEntry",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonWildEncounterEntry>(),
	alignof(FDigimonWildEncounterEntry),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonWildEncounterEntry(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonWildEncounterEntry, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonWildEncounterEntry"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonWildEncounterEntry ******************************************

// ********** Begin ScriptStruct FDigimonSeasonBattleCheckpoint ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSeasonBattleCheckpoint>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSeasonBattleCheckpoint); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Host-only persisted manual battle decision (Season and all private campaigns); never client-authored. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Host-only persisted manual battle decision (Season and all private campaigns); never client-authored." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContextId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommandsA_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommandsB_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSeasonBattleCheckpoint constinit property declarations ****
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContextId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_State;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CommandsA_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CommandsA;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CommandsB_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CommandsB;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSeasonBattleCheckpoint constinit property declarations ******
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSeasonBattleCheckpoint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSeasonBattleCheckpoint Property Definitions ***************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonBattleCheckpoint, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ContextId = { "ContextId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonBattleCheckpoint, ContextId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContextId_MetaData), NewProp_ContextId_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonBattleCheckpoint, State), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_CommandsA_Inner = { "CommandsA", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattleCommand, METADATA_PARAMS(0, nullptr) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_CommandsA = { "CommandsA", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonBattleCheckpoint, CommandsA), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommandsA_MetaData), NewProp_CommandsA_MetaData) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_CommandsB_Inner = { "CommandsB", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonBattleCommand, METADATA_PARAMS(0, nullptr) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_CommandsB = { "CommandsB", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSeasonBattleCheckpoint, CommandsB), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommandsB_MetaData), NewProp_CommandsB_MetaData) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContextId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandsA_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandsA,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandsB_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommandsB,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSeasonBattleCheckpoint Property Definitions *****************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSeasonBattleCheckpoint",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSeasonBattleCheckpoint>(),
	alignof(FDigimonSeasonBattleCheckpoint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSeasonBattleCheckpoint"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSeasonBattleCheckpoint **************************************

// ********** Begin Delegate FDigimonBattleStateChangedEvent ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonBattleStateChangedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonBattleStateChangedEvent_Parms
	{
		FDigimonBattleState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonBattleStateChangedEvent constinit property declarations *******
	static const UECodeGen_Private::FStructPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonBattleStateChangedEvent constinit property declarations *********
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonBattleStateChangedEvent Property Definitions ******************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonBattleStateChangedEvent_Parms, State), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonBattleStateChangedEvent Property Definitions ********************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonBattleStateChangedEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonBattleStateChangedEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonBattleStateChangedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonBattleStateChangedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonBattleStateChangedEvent *****************************************

// ********** Begin Class ADigimonVenomNXTBattleActor Function ComputeDamage ***********************
struct DigimonVenomNXTBattleActor_eventComputeDamage_Parms
{
	FDigimonBattleUnit Attacker;
	FDigimonBattleUnit Defender;
	int32 Power;
	int32 ReturnValue;

	/** Constructor, initializes return property only **/
	DigimonVenomNXTBattleActor_eventComputeDamage_Parms()
		: ReturnValue(0)
	{
	}
};
static FName NAME_ADigimonVenomNXTBattleActor_ComputeDamage = FName(TEXT("ComputeDamage"));
int32 ADigimonVenomNXTBattleActor::ComputeDamage(FDigimonBattleUnit const& Attacker, FDigimonBattleUnit const& Defender, int32 Power) const
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTBattleActor_ComputeDamage);
	if (!Func->GetOwnerClass()->HasAnyClassFlags(CLASS_Native))
	{
		DigimonVenomNXTBattleActor_eventComputeDamage_Parms Parms;
		Parms.Attacker=Attacker;
		Parms.Defender=Defender;
		Parms.Power=Power;
		const_cast<ADigimonVenomNXTBattleActor*>(this)->ProcessEvent(Func,&Parms);
		return Parms.ReturnValue;
	}
	else
	{
		return const_cast<ADigimonVenomNXTBattleActor*>(this)->ComputeDamage_Implementation(Attacker, Defender, Power);
	}
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeDamage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Legacy physical/neutral hook. New skills use ComputeMoveDamage with their canonical metadata. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Legacy physical/neutral hook. New skills use ComputeMoveDamage with their canonical metadata." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attacker_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Defender_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ComputeDamage constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attacker;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Defender;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Power;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ComputeDamage constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ComputeDamage Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Attacker = { "Attacker", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeDamage_Parms, Attacker), Z_Construct_UScriptStruct_FDigimonBattleUnit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attacker_MetaData), NewProp_Attacker_MetaData) }; // a6ced0e3e983e5f5b7b64446b10259a0816ee358
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Defender = { "Defender", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeDamage_Parms, Defender), Z_Construct_UScriptStruct_FDigimonBattleUnit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Defender_MetaData), NewProp_Defender_MetaData) }; // a6ced0e3e983e5f5b7b64446b10259a0816ee358
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Power = { "Power", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeDamage_Parms, Power), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeDamage_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Attacker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Defender,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Power,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ComputeDamage Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "ComputeDamage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTBattleActor_eventComputeDamage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x48420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTBattleActor_eventComputeDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeDamage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execComputeDamage)
{
	P_GET_STRUCT_REF(FDigimonBattleUnit,Z_Param_Out_Attacker);
	P_GET_STRUCT_REF(FDigimonBattleUnit,Z_Param_Out_Defender);
	P_GET_PROPERTY(FIntProperty,Z_Param_Power);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->ComputeDamage_Implementation(Z_Param_Out_Attacker,Z_Param_Out_Defender,Z_Param_Power);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function ComputeDamage *************************

// ********** Begin Class ADigimonVenomNXTBattleActor Function ComputeMoveDamage *******************
struct DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms
{
	FDigimonBattleUnit Attacker;
	FDigimonBattleUnit Defender;
	FDigimonMoveSlot Move;
	int32 ReturnValue;

	/** Constructor, initializes return property only **/
	DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms()
		: ReturnValue(0)
	{
	}
};
static FName NAME_ADigimonVenomNXTBattleActor_ComputeMoveDamage = FName(TEXT("ComputeMoveDamage"));
int32 ADigimonVenomNXTBattleActor::ComputeMoveDamage(FDigimonBattleUnit const& Attacker, FDigimonBattleUnit const& Defender, FDigimonMoveSlot const& Move) const
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTBattleActor_ComputeMoveDamage);
	if (!Func->GetOwnerClass()->HasAnyClassFlags(CLASS_Native))
	{
		DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms Parms;
		Parms.Attacker=Attacker;
		Parms.Defender=Defender;
		Parms.Move=Move;
		const_cast<ADigimonVenomNXTBattleActor*>(this)->ProcessEvent(Func,&Parms);
		return Parms.ReturnValue;
	}
	else
	{
		return const_cast<ADigimonVenomNXTBattleActor*>(this)->ComputeMoveDamage_Implementation(Attacker, Defender, Move);
	}
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeMoveDamage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attacker_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Defender_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Move_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ComputeMoveDamage constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attacker;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Defender;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Move;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ComputeMoveDamage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ComputeMoveDamage Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Attacker = { "Attacker", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms, Attacker), Z_Construct_UScriptStruct_FDigimonBattleUnit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attacker_MetaData), NewProp_Attacker_MetaData) }; // a6ced0e3e983e5f5b7b64446b10259a0816ee358
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Defender = { "Defender", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms, Defender), Z_Construct_UScriptStruct_FDigimonBattleUnit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Defender_MetaData), NewProp_Defender_MetaData) }; // a6ced0e3e983e5f5b7b64446b10259a0816ee358
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Move = { "Move", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms, Move), Z_Construct_UScriptStruct_FDigimonMoveSlot, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Move_MetaData), NewProp_Move_MetaData) }; // a52864aab2f9dfa537fec2d0c5991c2c7dfd4635
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Attacker,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Defender,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Move,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ComputeMoveDamage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "ComputeMoveDamage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x48420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTBattleActor_eventComputeMoveDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeMoveDamage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execComputeMoveDamage)
{
	P_GET_STRUCT_REF(FDigimonBattleUnit,Z_Param_Out_Attacker);
	P_GET_STRUCT_REF(FDigimonBattleUnit,Z_Param_Out_Defender);
	P_GET_STRUCT_REF(FDigimonMoveSlot,Z_Param_Out_Move);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->ComputeMoveDamage_Implementation(Z_Param_Out_Attacker,Z_Param_Out_Defender,Z_Param_Out_Move);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function ComputeMoveDamage *********************

// ********** Begin Class ADigimonVenomNXTBattleActor Function InitializeAITrainerBattle ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeAITrainerBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms
	{
		ADigimonVenomNXTPlayerState* Player;
		FDigimonBattleTeam OpponentTeam;
		EDigimonBattleKind Kind;
		FString ContextId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpponentTeam_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContextId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeAITrainerBattle constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Player;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OpponentTeam;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Kind_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Kind;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContextId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeAITrainerBattle constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeAITrainerBattle Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms, Player), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OpponentTeam = { "OpponentTeam", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms, OpponentTeam), Z_Construct_UScriptStruct_FDigimonBattleTeam, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpponentTeam_MetaData), NewProp_OpponentTeam_MetaData) }; // 9743f9b4f2467ec0110a0a2d86885ac78b99a3e0
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Kind_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Kind = { "Kind", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms, Kind), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonBattleKind, METADATA_PARAMS(0, nullptr) }; // 01055dd94064d1ee00f77910bb99d3b5df9d4027
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ContextId = { "ContextId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms, ContextId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContextId_MetaData), NewProp_ContextId_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OpponentTeam,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Kind_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Kind,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContextId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeAITrainerBattle Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "InitializeAITrainerBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeAITrainerBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeAITrainerBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execInitializeAITrainerBattle)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_Player);
	P_GET_STRUCT_REF(FDigimonBattleTeam,Z_Param_Out_OpponentTeam);
	P_GET_ENUM(EDigimonBattleKind,Z_Param_Kind);
	P_GET_PROPERTY(FStrProperty,Z_Param_ContextId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->InitializeAITrainerBattle(Z_Param_Player,Z_Param_Out_OpponentTeam,EDigimonBattleKind(Z_Param_Kind),Z_Param_ContextId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function InitializeAITrainerBattle *************

// ********** Begin Class ADigimonVenomNXTBattleActor Function InitializeTamerBattle ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeTamerBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms
	{
		ADigimonVenomNXTPlayerState* InPlayerA;
		ADigimonVenomNXTPlayerState* InPlayerB;
		EDigimonBattleKind Kind;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeTamerBattle constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InPlayerA;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InPlayerB;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Kind_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Kind;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeTamerBattle constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeTamerBattle Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InPlayerA = { "InPlayerA", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms, InPlayerA), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InPlayerB = { "InPlayerB", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms, InPlayerB), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Kind_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Kind = { "Kind", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms, Kind), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonBattleKind, METADATA_PARAMS(0, nullptr) }; // 01055dd94064d1ee00f77910bb99d3b5df9d4027
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InPlayerA,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InPlayerB,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Kind_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Kind,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeTamerBattle Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "InitializeTamerBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeTamerBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeTamerBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execInitializeTamerBattle)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_InPlayerA);
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_InPlayerB);
	P_GET_ENUM(EDigimonBattleKind,Z_Param_Kind);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->InitializeTamerBattle(Z_Param_InPlayerA,Z_Param_InPlayerB,EDigimonBattleKind(Z_Param_Kind));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function InitializeTamerBattle *****************

// ********** Begin Class ADigimonVenomNXTBattleActor Function InitializeWildBattle ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms
	{
		ADigimonVenomNXTPlayerState* Player;
		FName WildSpecies;
		EDigimonVariant Variant;
		int32 WildLevel;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeWildBattle constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Player;
	static const UECodeGen_Private::FNamePropertyParams NewProp_WildSpecies;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Variant_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Variant;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WildLevel;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeWildBattle constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeWildBattle Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms, Player), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_WildSpecies = { "WildSpecies", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms, WildSpecies), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Variant_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Variant = { "Variant", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms, Variant), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonVariant, METADATA_PARAMS(0, nullptr) }; // 83dd2583d6da5ba799b4693e6fe9884be4c8551d
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_WildLevel = { "WildLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms, WildLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WildSpecies,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Variant,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WildLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeWildBattle Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "InitializeWildBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeWildBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execInitializeWildBattle)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_Player);
	P_GET_PROPERTY(FNameProperty,Z_Param_WildSpecies);
	P_GET_ENUM(EDigimonVariant,Z_Param_Variant);
	P_GET_PROPERTY(FIntProperty,Z_Param_WildLevel);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->InitializeWildBattle(Z_Param_Player,Z_Param_WildSpecies,EDigimonVariant(Z_Param_Variant),Z_Param_WildLevel);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function InitializeWildBattle ******************

// ********** Begin Class ADigimonVenomNXTBattleActor Function InitializeWildGroupBattle ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildGroupBattle_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms
	{
		ADigimonVenomNXTPlayerState* Player;
		TArray<FDigimonWildEncounterEntry> Encounters;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Starts one encounter containing 1-3 independently authored wild opponents. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Starts one encounter containing 1-3 independently authored wild opponents." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Encounters_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeWildGroupBattle constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Player;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Encounters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Encounters;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function InitializeWildGroupBattle constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function InitializeWildGroupBattle Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms, Player), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Encounters_Inner = { "Encounters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonWildEncounterEntry, METADATA_PARAMS(0, nullptr) }; // 8cba1a79141d3bc9598a13a5456e16522b74aa73
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Encounters = { "Encounters", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms, Encounters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Encounters_MetaData), NewProp_Encounters_MetaData) }; // 8cba1a79141d3bc9598a13a5456e16522b74aa73
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Encounters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Encounters,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function InitializeWildGroupBattle Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "InitializeWildGroupBattle", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventInitializeWildGroupBattle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildGroupBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execInitializeWildGroupBattle)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_Player);
	P_GET_TARRAY_REF(FDigimonWildEncounterEntry,Z_Param_Out_Encounters);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->InitializeWildGroupBattle(Z_Param_Player,Z_Param_Out_Encounters);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function InitializeWildGroupBattle *************

// ********** Begin Class ADigimonVenomNXTBattleActor Function IsParticipant ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_IsParticipant_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventIsParticipant_Parms
	{
		const AController* Controller;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsParticipant constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventIsParticipant_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsParticipant constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsParticipant Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventIsParticipant_Parms, Controller), Z_Construct_UClass_AController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventIsParticipant_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsParticipant Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "IsParticipant", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventIsParticipant_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventIsParticipant_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_IsParticipant(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execIsParticipant)
{
	P_GET_OBJECT(AController,Z_Param_Controller);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsParticipant(Z_Param_Controller);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function IsParticipant *************************

// ********** Begin Class ADigimonVenomNXTBattleActor Function MulticastPresentState ***************
struct DigimonVenomNXTBattleActor_eventMulticastPresentState_Parms
{
	FDigimonBattleState Packet;
};
static FName NAME_ADigimonVenomNXTBattleActor_MulticastPresentState = FName(TEXT("MulticastPresentState"));
void ADigimonVenomNXTBattleActor::MulticastPresentState(FDigimonBattleState const& Packet)
{
	DigimonVenomNXTBattleActor_eventMulticastPresentState_Parms Parms;
	Parms.Packet=Packet;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTBattleActor_MulticastPresentState);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_MulticastPresentState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Packet_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function MulticastPresentState constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Packet;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function MulticastPresentState constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function MulticastPresentState Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Packet = { "Packet", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventMulticastPresentState_Parms, Packet), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Packet_MetaData), NewProp_Packet_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Packet,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function MulticastPresentState Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "MulticastPresentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTBattleActor_eventMulticastPresentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00084CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTBattleActor_eventMulticastPresentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_MulticastPresentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execMulticastPresentState)
{
	P_GET_STRUCT(FDigimonBattleState,Z_Param_Packet);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MulticastPresentState_Implementation(Z_Param_Packet);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function MulticastPresentState *****************

// ********** Begin Class ADigimonVenomNXTBattleActor Function OnRep_State *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_OnRep_State_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_State constinit property declarations ***************************
// ********** End Function OnRep_State constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "OnRep_State", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_OnRep_State(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execOnRep_State)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_State();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function OnRep_State ***************************

// ********** Begin Class ADigimonVenomNXTBattleActor Function SubmitCommand ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTBattleActor_SubmitCommand_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTBattleActor_eventSubmitCommand_Parms
	{
		AController* FromController;
		FDigimonBattleCommand Command;
		FString OutError;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Command_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SubmitCommand constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FromController;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Command;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTBattleActor_eventSubmitCommand_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SubmitCommand constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SubmitCommand Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FromController = { "FromController", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventSubmitCommand_Parms, FromController), Z_Construct_UClass_AController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Command = { "Command", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventSubmitCommand_Parms, Command), Z_Construct_UScriptStruct_FDigimonBattleCommand, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Command_MetaData), NewProp_Command_MetaData) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTBattleActor_eventSubmitCommand_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTBattleActor_eventSubmitCommand_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FromController,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Command,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SubmitCommand Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTBattleActor, nullptr, "SubmitCommand", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTBattleActor_eventSubmitCommand_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTBattleActor_eventSubmitCommand_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTBattleActor_SubmitCommand(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTBattleActor::execSubmitCommand)
{
	P_GET_OBJECT(AController,Z_Param_FromController);
	P_GET_STRUCT_REF(FDigimonBattleCommand,Z_Param_Out_Command);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SubmitCommand(Z_Param_FromController,Z_Param_Out_Command,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTBattleActor Function SubmitCommand *************************

// ********** Begin Class ADigimonVenomNXTBattleActor **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTBattleActor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DigimonVenomNXTBattleActor.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnrankedDecisionDeadlineServerTime_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Friendly battles share server time deadlines; independent of either client UI. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Friendly battles share server time deadlines; independent of either client UI." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUnrankedResultSaving_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current ordered presentation state; replication snapshots bootstrap late clients only. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current ordered presentation state; replication snapshots bootstrap late clients only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerA_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerB_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BattleContextId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional rival/season/story identifier used by server reward hooks. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional rival/season/story identifier used by server reward hooks." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnBattleStateChanged_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReplicatedSnapshot_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PendingUnrankedProfiles_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTBattleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTBattleActor constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UnrankedDecisionDeadlineServerTime;
	static void NewProp_bUnrankedResultSaving_SetBit(void* Obj)
	{
		((ADigimonVenomNXTBattleActor*)Obj)->bUnrankedResultSaving = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUnrankedResultSaving;
	static const UECodeGen_Private::FStructPropertyParams NewProp_State;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerA;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerB;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BattleContextId;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnBattleStateChanged;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReplicatedSnapshot;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PendingUnrankedProfiles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PendingUnrankedProfiles;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTBattleActor constinit property declarations ****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ComputeDamage"), .Pointer = &ADigimonVenomNXTBattleActor::execComputeDamage },
		{ .NameUTF8 = UTF8TEXT("ComputeMoveDamage"), .Pointer = &ADigimonVenomNXTBattleActor::execComputeMoveDamage },
		{ .NameUTF8 = UTF8TEXT("InitializeAITrainerBattle"), .Pointer = &ADigimonVenomNXTBattleActor::execInitializeAITrainerBattle },
		{ .NameUTF8 = UTF8TEXT("InitializeTamerBattle"), .Pointer = &ADigimonVenomNXTBattleActor::execInitializeTamerBattle },
		{ .NameUTF8 = UTF8TEXT("InitializeWildBattle"), .Pointer = &ADigimonVenomNXTBattleActor::execInitializeWildBattle },
		{ .NameUTF8 = UTF8TEXT("InitializeWildGroupBattle"), .Pointer = &ADigimonVenomNXTBattleActor::execInitializeWildGroupBattle },
		{ .NameUTF8 = UTF8TEXT("IsParticipant"), .Pointer = &ADigimonVenomNXTBattleActor::execIsParticipant },
		{ .NameUTF8 = UTF8TEXT("MulticastPresentState"), .Pointer = &ADigimonVenomNXTBattleActor::execMulticastPresentState },
		{ .NameUTF8 = UTF8TEXT("OnRep_State"), .Pointer = &ADigimonVenomNXTBattleActor::execOnRep_State },
		{ .NameUTF8 = UTF8TEXT("SubmitCommand"), .Pointer = &ADigimonVenomNXTBattleActor::execSubmitCommand },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeDamage, "ComputeDamage" }, // f8b8fc14e5c94a6bbb09d42fbd5628b32f39d5ba
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_ComputeMoveDamage, "ComputeMoveDamage" }, // 5d48f7790ebcf74147189fe14a035c48e7657920
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeAITrainerBattle, "InitializeAITrainerBattle" }, // 986fdae180089c1bde1cc66de241d7ee1b6cce29
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeTamerBattle, "InitializeTamerBattle" }, // a2d805da3e50080781c9542fea63b41e7e283ed5
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildBattle, "InitializeWildBattle" }, // 086b32b2fdf07a52cebeb95b620f8aa41ac70d70
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_InitializeWildGroupBattle, "InitializeWildGroupBattle" }, // f68a0405a5288d017d42a32db03dc4c0b5d8bc34
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_IsParticipant, "IsParticipant" }, // 3c8a66989067b1941a8040ad147265a3be2154ad
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_MulticastPresentState, "MulticastPresentState" }, // 930d137651eaad7ae0f4992f6afa9c35bcd21d2e
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_OnRep_State, "OnRep_State" }, // 55fb78e824822b2053b1a0217a58c9a0108aee77
		{ &Z_Construct_UFunction_ADigimonVenomNXTBattleActor_SubmitCommand, "SubmitCommand" }, // eacf384ce149829e01d2efea34af49f3bfc52c84
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTBattleActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTBattleActor Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_UnrankedDecisionDeadlineServerTime = { "UnrankedDecisionDeadlineServerTime", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, UnrankedDecisionDeadlineServerTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnrankedDecisionDeadlineServerTime_MetaData), NewProp_UnrankedDecisionDeadlineServerTime_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bUnrankedResultSaving = { "bUnrankedResultSaving", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ADigimonVenomNXTBattleActor), &UHT_STATICS::NewProp_bUnrankedResultSaving_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUnrankedResultSaving_MetaData), NewProp_bUnrankedResultSaving_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, State), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerA = { "PlayerA", nullptr, (EPropertyFlags)0x0114000000000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, PlayerA), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerA_MetaData), NewProp_PlayerA_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerB = { "PlayerB", nullptr, (EPropertyFlags)0x0114000000000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, PlayerB), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerB_MetaData), NewProp_PlayerB_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_BattleContextId = { "BattleContextId", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, BattleContextId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BattleContextId_MetaData), NewProp_BattleContextId_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnBattleStateChanged = { "OnBattleStateChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, OnBattleStateChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonBattleStateChangedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnBattleStateChanged_MetaData), NewProp_OnBattleStateChanged_MetaData) }; // 1ad7537031c5b24b85a0be4262009be0c25772a1
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReplicatedSnapshot = { "ReplicatedSnapshot", "OnRep_State", (EPropertyFlags)0x0040000100000020, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, ReplicatedSnapshot), Z_Construct_UScriptStruct_FDigimonBattleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReplicatedSnapshot_MetaData), NewProp_ReplicatedSnapshot_MetaData) }; // 87926de77b8dfe182f887419de2c31269a4a6f0a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PendingUnrankedProfiles_Inner = { "PendingUnrankedProfiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(0, nullptr) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_PendingUnrankedProfiles = { "PendingUnrankedProfiles", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTBattleActor, PendingUnrankedProfiles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PendingUnrankedProfiles_MetaData), NewProp_PendingUnrankedProfiles_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnrankedDecisionDeadlineServerTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bUnrankedResultSaving,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerA,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerB,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleContextId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnBattleStateChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReplicatedSnapshot,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PendingUnrankedProfiles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PendingUnrankedProfiles,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTBattleActor Property Definitions ***************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTBattleActor,
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
static void ADigimonVenomNXTBattleActor_StaticRegisterNativesADigimonVenomNXTBattleActor()
{
	UClass* Class = ADigimonVenomNXTBattleActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor;
UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTBattleActor;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTBattleActor"),
				Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.InnerSingleton,
				ADigimonVenomNXTBattleActor_StaticRegisterNativesADigimonVenomNXTBattleActor,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTBattleActor::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_UnrankedDecisionDeadlineServerTime(TEXT("UnrankedDecisionDeadlineServerTime"));
	static FName Name_bUnrankedResultSaving(TEXT("bUnrankedResultSaving"));
	static FName Name_PlayerA(TEXT("PlayerA"));
	static FName Name_PlayerB(TEXT("PlayerB"));
	static FName Name_BattleContextId(TEXT("BattleContextId"));
	static FName Name_ReplicatedSnapshot(TEXT("ReplicatedSnapshot"));
	const bool bIsValid = true
		&& Name_UnrankedDecisionDeadlineServerTime == ClassReps[(int32)ENetFields_Private::UnrankedDecisionDeadlineServerTime].Property->GetFName()
		&& Name_bUnrankedResultSaving == ClassReps[(int32)ENetFields_Private::bUnrankedResultSaving].Property->GetFName()
		&& Name_PlayerA == ClassReps[(int32)ENetFields_Private::PlayerA].Property->GetFName()
		&& Name_PlayerB == ClassReps[(int32)ENetFields_Private::PlayerB].Property->GetFName()
		&& Name_BattleContextId == ClassReps[(int32)ENetFields_Private::BattleContextId].Property->GetFName()
		&& Name_ReplicatedSnapshot == ClassReps[(int32)ENetFields_Private::ReplicatedSnapshot].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTBattleActor"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTBattleActor);
ADigimonVenomNXTBattleActor::~ADigimonVenomNXTBattleActor() {}
// ********** End Class ADigimonVenomNXTBattleActor ************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonWildEncounterEntry, Z_Construct_UScriptStruct_FDigimonWildEncounterEntry_Statics::NewStructOps, TEXT("DigimonWildEncounterEntry"),&Z_Registration_Info_UScriptStruct_FDigimonWildEncounterEntry, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonWildEncounterEntry), 2361006713U) },
		{ Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint, Z_Construct_UScriptStruct_FDigimonSeasonBattleCheckpoint_Statics::NewStructOps, TEXT("DigimonSeasonBattleCheckpoint"),&Z_Registration_Info_UScriptStruct_FDigimonSeasonBattleCheckpoint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSeasonBattleCheckpoint), 3279275481U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTBattleActor, TEXT("ADigimonVenomNXTBattleActor"), &Z_Registration_Info_UClass_ADigimonVenomNXTBattleActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTBattleActor), 1753136482U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTBattleActor_h__Script_DigimonVenomNXTRuntime_5385a8b4977ecc7dbf2814f213be97cc24d32fee{
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
