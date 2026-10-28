// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "Engine/LocalPlayer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTAudioSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ULocalPlayerSubsystem(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UObject(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USoundBase(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonEffectVoice(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonMusicVoice(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EDigimonAudioCue **********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue_Statics
template<> DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonAudioCue>()
{
	return Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Confirm.Name", "EDigimonAudioCue::Confirm" },
		{ "Defeat.Name", "EDigimonAudioCue::Defeat" },
		{ "EffectiveHit.Name", "EDigimonAudioCue::EffectiveHit" },
		{ "Encounter.Name", "EDigimonAudioCue::Encounter" },
		{ "Error.Name", "EDigimonAudioCue::Error" },
		{ "Flee.Name", "EDigimonAudioCue::Flee" },
		{ "Guard.Name", "EDigimonAudioCue::Guard" },
		{ "Heal.Name", "EDigimonAudioCue::Heal" },
		{ "Hit.Name", "EDigimonAudioCue::Hit" },
		{ "Interaction.Name", "EDigimonAudioCue::Interaction" },
		{ "Item.Name", "EDigimonAudioCue::Item" },
		{ "Knockout.Name", "EDigimonAudioCue::Knockout" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
		{ "PhysicalAttack.Name", "EDigimonAudioCue::PhysicalAttack" },
		{ "Purchase.Name", "EDigimonAudioCue::Purchase" },
		{ "SpecialAttack.Name", "EDigimonAudioCue::SpecialAttack" },
		{ "Travel.Name", "EDigimonAudioCue::Travel" },
		{ "UIBack.Name", "EDigimonAudioCue::UIBack" },
		{ "UIClick.Name", "EDigimonAudioCue::UIClick" },
		{ "UIHover.Name", "EDigimonAudioCue::UIHover" },
		{ "UINavigate.Name", "EDigimonAudioCue::UINavigate" },
		{ "Victory.Name", "EDigimonAudioCue::Victory" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDigimonAudioCue::UIHover", (int64)EDigimonAudioCue::UIHover },
		{ "EDigimonAudioCue::UIClick", (int64)EDigimonAudioCue::UIClick },
		{ "EDigimonAudioCue::UIBack", (int64)EDigimonAudioCue::UIBack },
		{ "EDigimonAudioCue::UINavigate", (int64)EDigimonAudioCue::UINavigate },
		{ "EDigimonAudioCue::Confirm", (int64)EDigimonAudioCue::Confirm },
		{ "EDigimonAudioCue::Error", (int64)EDigimonAudioCue::Error },
		{ "EDigimonAudioCue::Heal", (int64)EDigimonAudioCue::Heal },
		{ "EDigimonAudioCue::Item", (int64)EDigimonAudioCue::Item },
		{ "EDigimonAudioCue::Purchase", (int64)EDigimonAudioCue::Purchase },
		{ "EDigimonAudioCue::PhysicalAttack", (int64)EDigimonAudioCue::PhysicalAttack },
		{ "EDigimonAudioCue::SpecialAttack", (int64)EDigimonAudioCue::SpecialAttack },
		{ "EDigimonAudioCue::Hit", (int64)EDigimonAudioCue::Hit },
		{ "EDigimonAudioCue::Guard", (int64)EDigimonAudioCue::Guard },
		{ "EDigimonAudioCue::Knockout", (int64)EDigimonAudioCue::Knockout },
		{ "EDigimonAudioCue::Victory", (int64)EDigimonAudioCue::Victory },
		{ "EDigimonAudioCue::Defeat", (int64)EDigimonAudioCue::Defeat },
		{ "EDigimonAudioCue::Flee", (int64)EDigimonAudioCue::Flee },
		{ "EDigimonAudioCue::Travel", (int64)EDigimonAudioCue::Travel },
		{ "EDigimonAudioCue::Interaction", (int64)EDigimonAudioCue::Interaction },
		{ "EDigimonAudioCue::Encounter", (int64)EDigimonAudioCue::Encounter },
		{ "EDigimonAudioCue::EffectiveHit", (int64)EDigimonAudioCue::EffectiveHit },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	"EDigimonAudioCue",
	"EDigimonAudioCue",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EDigimonAudioCue;
UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EDigimonAudioCue.OuterSingleton)
		{
			ZRIE_EDigimonAudioCue.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("EDigimonAudioCue"));
		}
		return ZRIE_EDigimonAudioCue.OuterSingleton;
	}
	if (!ZRIE_EDigimonAudioCue.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EDigimonAudioCue.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EDigimonAudioCue.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EDigimonAudioCue ************************************************************

// ********** Begin ScriptStruct FDigimonEffectVoice ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonEffectVoice_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonEffectVoice>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonEffectVoice); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Component_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonEffectVoice constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Component;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonEffectVoice constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonEffectVoice>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonEffectVoice Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Component = { "Component", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonEffectVoice, Component), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Component_MetaData), NewProp_Component_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Component,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonEffectVoice Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonEffectVoice",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonEffectVoice>(),
	alignof(FDigimonEffectVoice),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonEffectVoice;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonEffectVoice(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonEffectVoice, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonEffectVoice"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonEffectVoice.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonEffectVoice *************************************************

// ********** Begin ScriptStruct FDigimonMusicVoice ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonMusicVoice_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonMusicVoice>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonMusicVoice); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A retained logical track can start on a different, non-looping intro wave. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A retained logical track can start on a different, non-looping intro wave." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Component_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Track_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Continuation_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonMusicVoice constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Component;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Track;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Continuation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonMusicVoice constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonMusicVoice>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonMusicVoice Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Component = { "Component", nullptr, (EPropertyFlags)0x0114000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonMusicVoice, Component), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Component_MetaData), NewProp_Component_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Track = { "Track", nullptr, (EPropertyFlags)0x0114000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonMusicVoice, Track), Z_Construct_UClass_USoundBase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Track_MetaData), NewProp_Track_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Continuation = { "Continuation", nullptr, (EPropertyFlags)0x0114000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonMusicVoice, Continuation), Z_Construct_UClass_USoundBase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Continuation_MetaData), NewProp_Continuation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Component,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Track,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Continuation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonMusicVoice Property Definitions *****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonMusicVoice",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonMusicVoice>(),
	alignof(FDigimonMusicVoice),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonMusicVoice;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonMusicVoice(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonMusicVoice, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonMusicVoice"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonMusicVoice.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonMusicVoice **************************************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function ClearBattleMusicState ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearBattleMusicState_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventClearBattleMusicState_Parms
	{
		UObject* BattleOwner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearBattleMusicState constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleOwner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClearBattleMusicState constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClearBattleMusicState Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleOwner = { "BattleOwner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventClearBattleMusicState_Parms, BattleOwner), Z_Construct_UClass_UObject, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleOwner,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClearBattleMusicState Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "ClearBattleMusicState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventClearBattleMusicState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventClearBattleMusicState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearBattleMusicState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execClearBattleMusicState)
{
	P_GET_OBJECT(UObject,Z_Param_BattleOwner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearBattleMusicState(Z_Param_BattleOwner);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function ClearBattleMusicState **************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function ClearUIScreenMusic ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearUIScreenMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventClearUIScreenMusic_Parms
	{
		UObject* Owner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearUIScreenMusic constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Owner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClearUIScreenMusic constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClearUIScreenMusic Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventClearUIScreenMusic_Parms, Owner), Z_Construct_UClass_UObject, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Owner,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClearUIScreenMusic Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "ClearUIScreenMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventClearUIScreenMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventClearUIScreenMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearUIScreenMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execClearUIScreenMusic)
{
	P_GET_OBJECT(UObject,Z_Param_Owner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearUIScreenMusic(Z_Param_Owner);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function ClearUIScreenMusic *****************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function GetCurrentMusic ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetCurrentMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventGetCurrentMusic_Parms
	{
		USoundBase* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentMusic constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentMusic constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentMusic Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventGetCurrentMusic_Parms, ReturnValue), Z_Construct_UClass_USoundBase, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentMusic Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "GetCurrentMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetCurrentMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetCurrentMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetCurrentMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execGetCurrentMusic)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USoundBase**)Z_Param__Result=P_THIS->GetCurrentMusic();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function GetCurrentMusic ********************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function GetEffectsVolume *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetEffectsVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventGetEffectsVolume_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEffectsVolume constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEffectsVolume constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEffectsVolume Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventGetEffectsVolume_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetEffectsVolume Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "GetEffectsVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetEffectsVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetEffectsVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetEffectsVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execGetEffectsVolume)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetEffectsVolume();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function GetEffectsVolume *******************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function GetMasterVolume ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMasterVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventGetMasterVolume_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMasterVolume constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMasterVolume constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMasterVolume Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventGetMasterVolume_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMasterVolume Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "GetMasterVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetMasterVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetMasterVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMasterVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execGetMasterVolume)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetMasterVolume();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function GetMasterVolume ********************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function GetMusicVolume *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMusicVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventGetMusicVolume_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMusicVolume constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMusicVolume constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMusicVolume Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventGetMusicVolume_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMusicVolume Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "GetMusicVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetMusicVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetMusicVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMusicVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execGetMusicVolume)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetMusicVolume();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function GetMusicVolume *********************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function GetUIVolume **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetUIVolume_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventGetUIVolume_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetUIVolume constinit property declarations ***************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetUIVolume constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetUIVolume Property Definitions **************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventGetUIVolume_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetUIVolume Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "GetUIVolume", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetUIVolume_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventGetUIVolume_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetUIVolume(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execGetUIVolume)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetUIVolume();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function GetUIVolume ************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayBattleForMap *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayBattleForMap_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventPlayBattleForMap_Parms
	{
		int32 MapId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PlayBattleForMap constinit property declarations **********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PlayBattleForMap constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PlayBattleForMap Property Definitions *********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayBattleForMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PlayBattleForMap Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayBattleForMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayBattleForMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayBattleForMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayBattleForMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayBattleForMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayBattleForMap(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayBattleForMap *******************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayCue **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCue_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventPlayCue_Parms
	{
		EDigimonAudioCue Cue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Local sound feedback. Never sends network traffic or changes BGM routing. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local sound feedback. Never sends network traffic or changes BGM routing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function PlayCue constinit property declarations *******************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Cue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Cue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PlayCue constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PlayCue Property Definitions ******************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Cue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Cue = { "Cue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayCue_Parms, Cue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue, METADATA_PARAMS(0, nullptr) }; // 69e30e3df0ae325d7904c551340b5e7b1ff8c271
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PlayCue Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayCue", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayCue_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayCue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCue(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayCue)
{
	P_GET_ENUM(EDigimonAudioCue,Z_Param_Cue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayCue(EDigimonAudioCue(Z_Param_Cue));
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayCue ****************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayCueOnce **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCueOnce_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventPlayCueOnce_Parms
	{
		EDigimonAudioCue Cue;
		FString EventKey;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stable receipt key suppresses repeated replicated events, including widget recreation. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stable receipt key suppresses repeated replicated events, including widget recreation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function PlayCueOnce constinit property declarations ***************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Cue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Cue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventKey;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PlayCueOnce constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PlayCueOnce Property Definitions **************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Cue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Cue = { "Cue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayCueOnce_Parms, Cue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue, METADATA_PARAMS(0, nullptr) }; // 69e30e3df0ae325d7904c551340b5e7b1ff8c271
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_EventKey = { "EventKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayCueOnce_Parms, EventKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventKey_MetaData), NewProp_EventKey_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventKey,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PlayCueOnce Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayCueOnce", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayCueOnce_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayCueOnce_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCueOnce(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayCueOnce)
{
	P_GET_ENUM(EDigimonAudioCue,Z_Param_Cue);
	P_GET_PROPERTY(FStrProperty,Z_Param_EventKey);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayCueOnce(EDigimonAudioCue(Z_Param_Cue),Z_Param_EventKey);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayCueOnce ************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayExplorationForMap ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayExplorationForMap_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventPlayExplorationForMap_Parms
	{
		int32 MapId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PlayExplorationForMap constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PlayExplorationForMap constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PlayExplorationForMap Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayExplorationForMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PlayExplorationForMap Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayExplorationForMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayExplorationForMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayExplorationForMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayExplorationForMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayExplorationForMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayExplorationForMap(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayExplorationForMap **************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayMainMenuMusic ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMainMenuMusic_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PlayMainMenuMusic constinit property declarations *********************
// ********** End Function PlayMainMenuMusic constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayMainMenuMusic", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMainMenuMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayMainMenuMusic)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayMainMenuMusic();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayMainMenuMusic ******************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function PlayMusic ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventPlayMusic_Parms
	{
		USoundBase* Sound;
		float FadeSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "CPP_Default_FadeSeconds", "0.350000" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PlayMusic constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sound;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PlayMusic constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PlayMusic Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Sound = { "Sound", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayMusic_Parms, Sound), Z_Construct_UClass_USoundBase, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FadeSeconds = { "FadeSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventPlayMusic_Parms, FadeSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Sound,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FadeSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function PlayMusic Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "PlayMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventPlayMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execPlayMusic)
{
	P_GET_OBJECT(USoundBase,Z_Param_Sound);
	P_GET_PROPERTY(FFloatProperty,Z_Param_FadeSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayMusic(Z_Param_Sound,Z_Param_FadeSeconds);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function PlayMusic **************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function SetAudioVolumes ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetAudioVolumes_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms
	{
		float Master;
		float Music;
		float Effects;
		float UI;
		bool bSave;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "CPP_Default_bSave", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetAudioVolumes constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Master;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Music;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Effects;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UI;
	static void NewProp_bSave_SetBit(void* Obj)
	{
		((DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms*)Obj)->bSave = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSave;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetAudioVolumes constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetAudioVolumes Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Master = { "Master", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms, Master), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Music = { "Music", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms, Music), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Effects = { "Effects", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms, Effects), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_UI = { "UI", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms, UI), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSave = { "bSave", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms), &UHT_STATICS::NewProp_bSave_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Master,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Music,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Effects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UI,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSave,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetAudioVolumes Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "SetAudioVolumes", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetAudioVolumes_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetAudioVolumes(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execSetAudioVolumes)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Master);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Music);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Effects);
	P_GET_PROPERTY(FFloatProperty,Z_Param_UI);
	P_GET_UBOOL(Z_Param_bSave);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAudioVolumes(Z_Param_Master,Z_Param_Music,Z_Param_Effects,Z_Param_UI,Z_Param_bSave);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function SetAudioVolumes ********************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function SetBattleMusicState **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetBattleMusicState_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms
	{
		UObject* BattleOwner;
		int32 MapId;
		bool bVictory;
		bool bSeasonMatch;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Battle/result presentation overrides UI until that battle is dismissed. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Battle/result presentation overrides UI until that battle is dismissed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetBattleMusicState constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleOwner;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static void NewProp_bVictory_SetBit(void* Obj)
	{
		((DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms*)Obj)->bVictory = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVictory;
	static void NewProp_bSeasonMatch_SetBit(void* Obj)
	{
		((DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms*)Obj)->bSeasonMatch = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSeasonMatch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetBattleMusicState constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetBattleMusicState Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleOwner = { "BattleOwner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms, BattleOwner), Z_Construct_UClass_UObject, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bVictory = { "bVictory", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms), &UHT_STATICS::NewProp_bVictory_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSeasonMatch = { "bSeasonMatch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms), &UHT_STATICS::NewProp_bSeasonMatch_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleOwner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bVictory,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSeasonMatch,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetBattleMusicState Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "SetBattleMusicState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetBattleMusicState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetBattleMusicState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execSetBattleMusicState)
{
	P_GET_OBJECT(UObject,Z_Param_BattleOwner);
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_UBOOL(Z_Param_bVictory);
	P_GET_UBOOL(Z_Param_bSeasonMatch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetBattleMusicState(Z_Param_BattleOwner,Z_Param_MapId,Z_Param_bVictory,Z_Param_bSeasonMatch);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function SetBattleMusicState ****************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function SetDigiFarmActive ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetDigiFarmActive_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventSetDigiFarmActive_Parms
	{
		bool bActive;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The private farm is a field context, so nonmodal care cannot stop its music. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The private farm is a field context, so nonmodal care cannot stop its music." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetDigiFarmActive constinit property declarations *********************
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((DigimonVenomNXTAudioSubsystem_eventSetDigiFarmActive_Parms*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDigiFarmActive constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDigiFarmActive Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTAudioSubsystem_eventSetDigiFarmActive_Parms), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetDigiFarmActive Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "SetDigiFarmActive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetDigiFarmActive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetDigiFarmActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetDigiFarmActive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execSetDigiFarmActive)
{
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDigiFarmActive(Z_Param_bActive);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function SetDigiFarmActive ******************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function SetUIScreenMusic *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetUIScreenMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventSetUIScreenMusic_Parms
	{
		UObject* Owner;
		FString PageName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Visible UI owners update in place; nested owners restore when closed. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visible UI owners update in place; nested owners restore when closed." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetUIScreenMusic constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Owner;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PageName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetUIScreenMusic constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetUIScreenMusic Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetUIScreenMusic_Parms, Owner), Z_Construct_UClass_UObject, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_PageName = { "PageName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventSetUIScreenMusic_Parms, PageName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageName_MetaData), NewProp_PageName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Owner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageName,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetUIScreenMusic Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "SetUIScreenMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetUIScreenMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventSetUIScreenMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetUIScreenMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execSetUIScreenMusic)
{
	P_GET_OBJECT(UObject,Z_Param_Owner);
	P_GET_PROPERTY(FStrProperty,Z_Param_PageName);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetUIScreenMusic(Z_Param_Owner,Z_Param_PageName);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function SetUIScreenMusic *******************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Function StopMusic ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_StopMusic_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTAudioSubsystem_eventStopMusic_Parms
	{
		float FadeSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "CPP_Default_FadeSeconds", "0.350000" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StopMusic constinit property declarations *****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StopMusic constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StopMusic Property Definitions ****************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FadeSeconds = { "FadeSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTAudioSubsystem_eventStopMusic_Parms, FadeSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FadeSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StopMusic Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, nullptr, "StopMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventStopMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTAudioSubsystem_eventStopMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_StopMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTAudioSubsystem::execStopMusic)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_FadeSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopMusic(Z_Param_FadeSeconds);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTAudioSubsystem Function StopMusic **************************

// ********** Begin Class UDigimonVenomNXTAudioSubsystem *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Client-local music controller. Keeps replicated gameplay free of audio state while exposing Blueprint hooks. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTAudioSubsystem.h" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Client-local music controller. Keeps replicated gameplay free of audio state while exposing Blueprint hooks." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EffectVoices_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadedEffects_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MusicComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentSound_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MusicLayers_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadedTracks_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTAudioSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTAudioSubsystem constinit property declarations ***********
	static const UECodeGen_Private::FStructPropertyParams NewProp_EffectVoices_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_EffectVoices;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoadedEffects_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_LoadedEffects_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_LoadedEffects;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MusicComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentSound;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MusicLayers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MusicLayers;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoadedTracks_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_LoadedTracks_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_LoadedTracks;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTAudioSubsystem constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClearBattleMusicState"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execClearBattleMusicState },
		{ .NameUTF8 = UTF8TEXT("ClearUIScreenMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execClearUIScreenMusic },
		{ .NameUTF8 = UTF8TEXT("GetCurrentMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execGetCurrentMusic },
		{ .NameUTF8 = UTF8TEXT("GetEffectsVolume"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execGetEffectsVolume },
		{ .NameUTF8 = UTF8TEXT("GetMasterVolume"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execGetMasterVolume },
		{ .NameUTF8 = UTF8TEXT("GetMusicVolume"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execGetMusicVolume },
		{ .NameUTF8 = UTF8TEXT("GetUIVolume"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execGetUIVolume },
		{ .NameUTF8 = UTF8TEXT("PlayBattleForMap"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayBattleForMap },
		{ .NameUTF8 = UTF8TEXT("PlayCue"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayCue },
		{ .NameUTF8 = UTF8TEXT("PlayCueOnce"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayCueOnce },
		{ .NameUTF8 = UTF8TEXT("PlayExplorationForMap"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayExplorationForMap },
		{ .NameUTF8 = UTF8TEXT("PlayMainMenuMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayMainMenuMusic },
		{ .NameUTF8 = UTF8TEXT("PlayMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execPlayMusic },
		{ .NameUTF8 = UTF8TEXT("SetAudioVolumes"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execSetAudioVolumes },
		{ .NameUTF8 = UTF8TEXT("SetBattleMusicState"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execSetBattleMusicState },
		{ .NameUTF8 = UTF8TEXT("SetDigiFarmActive"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execSetDigiFarmActive },
		{ .NameUTF8 = UTF8TEXT("SetUIScreenMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execSetUIScreenMusic },
		{ .NameUTF8 = UTF8TEXT("StopMusic"), .Pointer = &UDigimonVenomNXTAudioSubsystem::execStopMusic },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearBattleMusicState, "ClearBattleMusicState" }, // db964030eaac3af62a0b3ddacecf0d34c86c7328
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_ClearUIScreenMusic, "ClearUIScreenMusic" }, // a4880d5c662d798c8e266a684e479e8bac515174
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetCurrentMusic, "GetCurrentMusic" }, // 5828688b0c9a5ed2a3d0485280adeb7f396be2d8
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetEffectsVolume, "GetEffectsVolume" }, // bdad22fbdad3ddd673d80649ec984964190affe4
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMasterVolume, "GetMasterVolume" }, // 3fac582a921298875cc9752edff2769223d9bdfd
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetMusicVolume, "GetMusicVolume" }, // ba5a498e259c878f7641135a17457e867888018d
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_GetUIVolume, "GetUIVolume" }, // 8a29014709adfa7c6c09b160777c659afdf9f116
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayBattleForMap, "PlayBattleForMap" }, // 8c5faf33efe8f594802686defc6f25f291d537d4
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCue, "PlayCue" }, // 39ec31686a78aec78043cca9b425a4d5fd9c4d83
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayCueOnce, "PlayCueOnce" }, // 6ef1cf889dbeb297f62b9585294bfca380a1721f
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayExplorationForMap, "PlayExplorationForMap" }, // 6f6ee74662272e09077a7fa5057af8957e01875f
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMainMenuMusic, "PlayMainMenuMusic" }, // 53834f03d1f7d0ede1c9e0e88616398c0ffdc1ac
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_PlayMusic, "PlayMusic" }, // cbab2e736645710b8bd6fd9e3d7e2bf898ce4e2e
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetAudioVolumes, "SetAudioVolumes" }, // 4525e030ec0a4f49922ff74bc42da9e77f28499b
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetBattleMusicState, "SetBattleMusicState" }, // 14c10b7d5366346c8a024adb1a4b63b8096b91f1
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetDigiFarmActive, "SetDigiFarmActive" }, // 44c19d48e9f2239ad931c5f22567d85a2127eda0
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_SetUIScreenMusic, "SetUIScreenMusic" }, // 15a8a83574c07aa95efd5151c1883780daed0a7c
		{ &Z_Construct_UFunction_UDigimonVenomNXTAudioSubsystem_StopMusic, "StopMusic" }, // 4f26436a07a964499538014079aedb77a039797c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTAudioSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTAudioSubsystem Property Definitions **********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_EffectVoices_Inner = { "EffectVoices", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonEffectVoice, METADATA_PARAMS(0, nullptr) }; // 93ddc3d07caa9acffb3f850de417bb8408b3f27d
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_EffectVoices = { "EffectVoices", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, EffectVoices), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EffectVoices_MetaData), NewProp_EffectVoices_MetaData) }; // 93ddc3d07caa9acffb3f850de417bb8408b3f27d
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LoadedEffects_ValueProp = { "LoadedEffects", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 1, Z_Construct_UClass_USoundBase, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LoadedEffects_Key_KeyProp = { "LoadedEffects_Key", nullptr, (EPropertyFlags)0x0100000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_LoadedEffects = { "LoadedEffects", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, LoadedEffects), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadedEffects_MetaData), NewProp_LoadedEffects_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MusicComponent = { "MusicComponent", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, MusicComponent), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MusicComponent_MetaData), NewProp_MusicComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CurrentSound = { "CurrentSound", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, CurrentSound), Z_Construct_UClass_USoundBase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentSound_MetaData), NewProp_CurrentSound_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_MusicLayers_Inner = { "MusicLayers", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonMusicVoice, METADATA_PARAMS(0, nullptr) }; // f4fa47c1ba3711dd23650f2b97b24a9dfdef6a42
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_MusicLayers = { "MusicLayers", nullptr, (EPropertyFlags)0x0040008000002000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, MusicLayers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MusicLayers_MetaData), NewProp_MusicLayers_MetaData) }; // f4fa47c1ba3711dd23650f2b97b24a9dfdef6a42
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LoadedTracks_ValueProp = { "LoadedTracks", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 1, Z_Construct_UClass_USoundBase, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LoadedTracks_Key_KeyProp = { "LoadedTracks_Key", nullptr, (EPropertyFlags)0x0100000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_LoadedTracks = { "LoadedTracks", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTAudioSubsystem, LoadedTracks), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadedTracks_MetaData), NewProp_LoadedTracks_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EffectVoices_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EffectVoices,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedEffects_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedEffects_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedEffects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MusicComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentSound,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MusicLayers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MusicLayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedTracks_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedTracks_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoadedTracks,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTAudioSubsystem Property Definitions ************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ULocalPlayerSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem,
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
static void UDigimonVenomNXTAudioSubsystem_StaticRegisterNativesUDigimonVenomNXTAudioSubsystem()
{
	UClass* Class = UDigimonVenomNXTAudioSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem;
UClass* Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTAudioSubsystem;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTAudioSubsystem"),
				Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.InnerSingleton,
				UDigimonVenomNXTAudioSubsystem_StaticRegisterNativesUDigimonVenomNXTAudioSubsystem,
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
		return Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTAudioSubsystem::UDigimonVenomNXTAudioSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTAudioSubsystem);
UDigimonVenomNXTAudioSubsystem::~UDigimonVenomNXTAudioSubsystem() {}
// ********** End Class UDigimonVenomNXTAudioSubsystem *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue, TEXT("EDigimonAudioCue"), &ZRIE_EDigimonAudioCue, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1776487997U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonEffectVoice, Z_Construct_UScriptStruct_FDigimonEffectVoice_Statics::NewStructOps, TEXT("DigimonEffectVoice"),&Z_Registration_Info_UScriptStruct_FDigimonEffectVoice, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonEffectVoice), 2480784336U) },
		{ Z_Construct_UScriptStruct_FDigimonMusicVoice, Z_Construct_UScriptStruct_FDigimonMusicVoice_Statics::NewStructOps, TEXT("DigimonMusicVoice"),&Z_Registration_Info_UScriptStruct_FDigimonMusicVoice, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonMusicVoice), 4110043073U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTAudioSubsystem, TEXT("UDigimonVenomNXTAudioSubsystem"), &Z_Registration_Info_UClass_UDigimonVenomNXTAudioSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTAudioSubsystem), 4080275197U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAudioSubsystem_h__Script_DigimonVenomNXTRuntime_5d3a14bb71ed04481f655d55c239d06d70814a16{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
