// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTGameMode(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTGameMode(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTGameMode Function SaveAllPlayers *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_SaveAllPlayers_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveAllPlayers constinit property declarations ************************
// ********** End Function SaveAllPlayers constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "SaveAllPlayers", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_SaveAllPlayers(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execSaveAllPlayers)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SaveAllPlayers();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function SaveAllPlayers ***************************

// ********** Begin Class ADigimonVenomNXTGameMode Function SavePlayer *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_SavePlayer_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventSavePlayer_Parms
	{
		ADigimonVenomNXTPlayerState* PlayerState;
		bool bAllowAutomaticWrite;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
		{ "CPP_Default_bAllowAutomaticWrite", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SavePlayer constinit property declarations ****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerState;
	static void NewProp_bAllowAutomaticWrite_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameMode_eventSavePlayer_Parms*)Obj)->bAllowAutomaticWrite = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAllowAutomaticWrite;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTGameMode_eventSavePlayer_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SavePlayer constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SavePlayer Property Definitions ***************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PlayerState = { "PlayerState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventSavePlayer_Parms, PlayerState), Z_Construct_UClass_ADigimonVenomNXTPlayerState, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAllowAutomaticWrite = { "bAllowAutomaticWrite", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameMode_eventSavePlayer_Parms), &UHT_STATICS::NewProp_bAllowAutomaticWrite_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTGameMode_eventSavePlayer_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAllowAutomaticWrite,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SavePlayer Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "SavePlayer", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventSavePlayer_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventSavePlayer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_SavePlayer(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execSavePlayer)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerState,Z_Param_PlayerState);
	P_GET_UBOOL(Z_Param_bAllowAutomaticWrite);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SavePlayer(Z_Param_PlayerState,Z_Param_bAllowAutomaticWrite);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function SavePlayer *******************************

// ********** Begin Class ADigimonVenomNXTGameMode Function StartAIRivalBattleFor ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartAIRivalBattleFor_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms
	{
		ADigimonVenomNXTPlayerController* Controller;
		FString RivalId;
		FString OutError;
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartAIRivalBattleFor constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartAIRivalBattleFor constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartAIRivalBattleFor Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms, Controller), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartAIRivalBattleFor Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "StartAIRivalBattleFor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventStartAIRivalBattleFor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartAIRivalBattleFor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execStartAIRivalBattleFor)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerController,Z_Param_Controller);
	P_GET_PROPERTY(FStrProperty,Z_Param_RivalId);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->StartAIRivalBattleFor(Z_Param_Controller,Z_Param_RivalId,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function StartAIRivalBattleFor ********************

// ********** Begin Class ADigimonVenomNXTGameMode Function StartFinalStoryBattleFor ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartFinalStoryBattleFor_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms
	{
		ADigimonVenomNXTPlayerController* Controller;
		FString OutError;
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartFinalStoryBattleFor constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartFinalStoryBattleFor constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartFinalStoryBattleFor Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms, Controller), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartFinalStoryBattleFor Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "StartFinalStoryBattleFor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventStartFinalStoryBattleFor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartFinalStoryBattleFor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execStartFinalStoryBattleFor)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerController,Z_Param_Controller);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->StartFinalStoryBattleFor(Z_Param_Controller,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function StartFinalStoryBattleFor *****************

// ********** Begin Class ADigimonVenomNXTGameMode Function StartSeasonBattleFor *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartSeasonBattleFor_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms
	{
		ADigimonVenomNXTPlayerController* Controller;
		FString OutError;
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartSeasonBattleFor constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartSeasonBattleFor constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartSeasonBattleFor Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms, Controller), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartSeasonBattleFor Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "StartSeasonBattleFor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventStartSeasonBattleFor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartSeasonBattleFor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execStartSeasonBattleFor)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerController,Z_Param_Controller);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->StartSeasonBattleFor(Z_Param_Controller,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function StartSeasonBattleFor *********************

// ********** Begin Class ADigimonVenomNXTGameMode Function StartStoryBossBattleFor ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartStoryBossBattleFor_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms
	{
		ADigimonVenomNXTPlayerController* Controller;
		int32 Chapter;
		FString OutError;
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartStoryBossBattleFor constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Chapter;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartStoryBossBattleFor constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartStoryBossBattleFor Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms, Controller), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Chapter = { "Chapter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms, Chapter), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Chapter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartStoryBossBattleFor Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "StartStoryBossBattleFor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventStartStoryBossBattleFor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartStoryBossBattleFor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execStartStoryBossBattleFor)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerController,Z_Param_Controller);
	P_GET_PROPERTY(FIntProperty,Z_Param_Chapter);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->StartStoryBossBattleFor(Z_Param_Controller,Z_Param_Chapter,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function StartStoryBossBattleFor ******************

// ********** Begin Class ADigimonVenomNXTGameMode Function StartWildBattleFor *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartWildBattleFor_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms
	{
		ADigimonVenomNXTPlayerController* Controller;
		FString OutError;
		ADigimonVenomNXTBattleActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartWildBattleFor constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartWildBattleFor constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartWildBattleFor Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms, Controller), Z_Construct_UClass_ADigimonVenomNXTPlayerController, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartWildBattleFor Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTGameMode, nullptr, "StartWildBattleFor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTGameMode_eventStartWildBattleFor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartWildBattleFor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTGameMode::execStartWildBattleFor)
{
	P_GET_OBJECT(ADigimonVenomNXTPlayerController,Z_Param_Controller);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTBattleActor**)Z_Param__Result=P_THIS->StartWildBattleFor(Z_Param_Controller,Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTGameMode Function StartWildBattleFor ***********************

// ********** Begin Class ADigimonVenomNXTGameMode *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTGameMode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Authoritative public-world rules, authentication gate, autosave and battle factory. */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DigimonVenomNXTGameMode.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Authoritative public-world rules, authentication gate, autosave and battle factory." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BattleActorClass_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTGameMode.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTGameMode constinit property declarations *****************
	static const UECodeGen_Private::FClassPropertyParams NewProp_BattleActorClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTGameMode constinit property declarations *******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SaveAllPlayers"), .Pointer = &ADigimonVenomNXTGameMode::execSaveAllPlayers },
		{ .NameUTF8 = UTF8TEXT("SavePlayer"), .Pointer = &ADigimonVenomNXTGameMode::execSavePlayer },
		{ .NameUTF8 = UTF8TEXT("StartAIRivalBattleFor"), .Pointer = &ADigimonVenomNXTGameMode::execStartAIRivalBattleFor },
		{ .NameUTF8 = UTF8TEXT("StartFinalStoryBattleFor"), .Pointer = &ADigimonVenomNXTGameMode::execStartFinalStoryBattleFor },
		{ .NameUTF8 = UTF8TEXT("StartSeasonBattleFor"), .Pointer = &ADigimonVenomNXTGameMode::execStartSeasonBattleFor },
		{ .NameUTF8 = UTF8TEXT("StartStoryBossBattleFor"), .Pointer = &ADigimonVenomNXTGameMode::execStartStoryBossBattleFor },
		{ .NameUTF8 = UTF8TEXT("StartWildBattleFor"), .Pointer = &ADigimonVenomNXTGameMode::execStartWildBattleFor },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_SaveAllPlayers, "SaveAllPlayers" }, // 397fd58e92fdbbc995ecd0ff51e96548dbbc4f3a
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_SavePlayer, "SavePlayer" }, // 6edc3d8b2f30072c5abd7351d460e8be784a0c93
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartAIRivalBattleFor, "StartAIRivalBattleFor" }, // e15c1a70b42bc5ded0da90a589ed21992f350410
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartFinalStoryBattleFor, "StartFinalStoryBattleFor" }, // 24164ebe99104f96f0595bbd46c0931c6b6d73b1
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartSeasonBattleFor, "StartSeasonBattleFor" }, // c6196155ddfa991cda6be5ab3e1c0922db92960c
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartStoryBossBattleFor, "StartStoryBossBattleFor" }, // 8ba49c51ee062f9bf55f468434b933fe5a791ec8
		{ &Z_Construct_UFunction_ADigimonVenomNXTGameMode_StartWildBattleFor, "StartWildBattleFor" }, // bd5c8a80be57a96348e28c481f6faf774232166e
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTGameMode Property Definitions ****************************
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_BattleActorClass = { "BattleActorClass", nullptr, (EPropertyFlags)0x0024080000010015, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTGameMode, BattleActorClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BattleActorClass_MetaData), NewProp_BattleActorClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleActorClass,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTGameMode Property Definitions ******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AGameModeBase,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTGameMode,
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
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADigimonVenomNXTGameMode_StaticRegisterNativesADigimonVenomNXTGameMode()
{
	UClass* Class = ADigimonVenomNXTGameMode::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTGameMode;
UClass* Z_Construct_UClass_ADigimonVenomNXTGameMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTGameMode;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTGameMode"),
				Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.InnerSingleton,
				ADigimonVenomNXTGameMode_StaticRegisterNativesADigimonVenomNXTGameMode,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTGameMode.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTGameMode);
ADigimonVenomNXTGameMode::~ADigimonVenomNXTGameMode() {}
// ********** End Class ADigimonVenomNXTGameMode ***************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameMode_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTGameMode, TEXT("ADigimonVenomNXTGameMode"), &Z_Registration_Info_UClass_ADigimonVenomNXTGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTGameMode), 2627844691U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTGameMode_h__Script_DigimonVenomNXTRuntime_e8333413706047675abdb271ad072fac28fd3ed5{
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
