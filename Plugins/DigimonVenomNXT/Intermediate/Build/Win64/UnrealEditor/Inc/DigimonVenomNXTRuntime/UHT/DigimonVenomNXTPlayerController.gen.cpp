// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTPlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_APlayerController(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonBattleCommand(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonChatMessage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonChatReceivedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonClientMessageEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonCurrentBattleChangedEvent__DelegateSignature(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonFarmSession(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonPlayerProfile(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRelayProgress(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRelaySession(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSeasonArchivePage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonPrivateCampaign(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTBattleActor(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTBattleWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTFarmScene(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTProfileSyncWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTRelayScene(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FDigimonClientMessageEvent ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonClientMessageEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonClientMessageEvent_Parms
	{
		FString Title;
		FString Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Title_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonClientMessageEvent constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Title;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonClientMessageEvent constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonClientMessageEvent Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Title = { "Title", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonClientMessageEvent_Parms, Title), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Title_MetaData), NewProp_Title_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonClientMessageEvent_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Title,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonClientMessageEvent Property Definitions *************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonClientMessageEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonClientMessageEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonClientMessageEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonClientMessageEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonClientMessageEvent **********************************************

// ********** Begin Delegate FDigimonChatReceivedEvent *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonChatReceivedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonChatReceivedEvent_Parms
	{
		FDigimonChatMessage Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonChatReceivedEvent constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonChatReceivedEvent constinit property declarations ***************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonChatReceivedEvent Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonChatReceivedEvent_Parms, Message), Z_Construct_UScriptStruct_FDigimonChatMessage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonChatReceivedEvent Property Definitions **************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonChatReceivedEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonChatReceivedEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonChatReceivedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonChatReceivedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonChatReceivedEvent ***********************************************

// ********** Begin Delegate FDigimonCurrentBattleChangedEvent *************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonCurrentBattleChangedEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_DigimonVenomNXTRuntime_eventDigimonCurrentBattleChangedEvent_Parms
	{
		ADigimonVenomNXTBattleActor* Battle;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDigimonCurrentBattleChangedEvent constinit property declarations *****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Battle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDigimonCurrentBattleChangedEvent constinit property declarations *******
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDigimonCurrentBattleChangedEvent Property Definitions ****************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Battle = { "Battle", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_DigimonVenomNXTRuntime_eventDigimonCurrentBattleChangedEvent_Parms, Battle), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Battle,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDigimonCurrentBattleChangedEvent Property Definitions ******************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime, nullptr, "DigimonCurrentBattleChangedEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonCurrentBattleChangedEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_DigimonVenomNXTRuntime_eventDigimonCurrentBattleChangedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonCurrentBattleChangedEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDigimonCurrentBattleChangedEvent ***************************************

// ********** Begin ScriptStruct FDigimonFarmSession ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonFarmSession_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonFarmSession>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonFarmSession); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** One owner-only replication property keeps private location and active state atomic. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "One owner-only replication property keeps private location and active state atomic." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bActive_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Origin_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonFarmSession constinit property declarations ***************
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((FDigimonFarmSession*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Origin;
	static const UECodeGen_Private::FUInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonFarmSession constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonFarmSession>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonFarmSession Property Definitions **************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonFarmSession), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bActive_MetaData), NewProp_bActive_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Origin = { "Origin", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonFarmSession, Origin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Origin_MetaData), NewProp_Origin_MetaData) };
const UECodeGen_Private::FUInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonFarmSession, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Origin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonFarmSession Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonFarmSession",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonFarmSession>(),
	alignof(FDigimonFarmSession),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonFarmSession;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonFarmSession(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonFarmSession.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonFarmSession.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonFarmSession, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonFarmSession"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonFarmSession.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonFarmSession.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonFarmSession.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonFarmSession.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonFarmSession *************************************************

// ********** Begin ScriptStruct FDigimonRelaySession **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonRelaySession_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonRelaySession>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonRelaySession); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** An atomic owner-only campaign session. Public habitat identity remains untouched. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An atomic owner-only campaign session. Public habitat identity remains untouched." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bActive_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Campaign_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Origin_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonRelaySession constinit property declarations **************
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((FDigimonRelaySession*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Campaign_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Campaign;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Origin;
	static const UECodeGen_Private::FUInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonRelaySession constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonRelaySession>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonRelaySession Property Definitions *************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonRelaySession), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bActive_MetaData), NewProp_bActive_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Campaign_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Campaign = { "Campaign", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonRelaySession, Campaign), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonPrivateCampaign, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Campaign_MetaData), NewProp_Campaign_MetaData) }; // 13bd3e9de9f6f2f40b1ef878b84716e0b7a25bab
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonRelaySession, MapId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapId_MetaData), NewProp_MapId_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Origin = { "Origin", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonRelaySession, Origin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Origin_MetaData), NewProp_Origin_MetaData) };
const UECodeGen_Private::FUInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::UInt64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonRelaySession, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Origin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonRelaySession Property Definitions ***************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonRelaySession",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonRelaySession>(),
	alignof(FDigimonRelaySession),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonRelaySession;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonRelaySession(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonRelaySession.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonRelaySession.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonRelaySession, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonRelaySession"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonRelaySession.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonRelaySession.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonRelaySession.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonRelaySession.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonRelaySession ************************************************

// ********** Begin Class ADigimonVenomNXTPlayerController Function CanUseRelayPortal **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_CanUseRelayPortal_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms
	{
		bool bForward;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CanUseRelayPortal constinit property declarations *********************
	static void NewProp_bForward_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms*)Obj)->bForward = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bForward;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CanUseRelayPortal constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CanUseRelayPortal Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bForward = { "bForward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms), &UHT_STATICS::NewProp_bForward_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bForward,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CanUseRelayPortal Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "CanUseRelayPortal", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventCanUseRelayPortal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_CanUseRelayPortal(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execCanUseRelayPortal)
{
	P_GET_UBOOL(Z_Param_bForward);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->CanUseRelayPortal(Z_Param_bForward);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function CanUseRelayPortal ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientAccountAuthenticationResult 
struct DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms
{
	bool bSuccess;
	FString Message;
	FString Username;
	FString AccountId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientAccountAuthenticationResult = FName(TEXT("ClientAccountAuthenticationResult"));
void ADigimonVenomNXTPlayerController::ClientAccountAuthenticationResult(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId)
{
	DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms Parms;
	Parms.bSuccess=bSuccess ? true : false;
	Parms.Message=Message;
	Parms.Username=Username;
	Parms.AccountId=AccountId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientAccountAuthenticationResult);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientAccountAuthenticationResult_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientAccountAuthenticationResult constinit property declarations *****
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientAccountAuthenticationResult constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientAccountAuthenticationResult Property Definitions ****************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientAccountAuthenticationResult Property Definitions ******************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientAccountAuthenticationResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientAccountAuthenticationResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientAccountAuthenticationResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientAccountAuthenticationResult)
{
	P_GET_UBOOL(Z_Param_bSuccess);
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_GET_PROPERTY(FStrProperty,Z_Param_Username);
	P_GET_PROPERTY(FStrProperty,Z_Param_AccountId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientAccountAuthenticationResult_Implementation(Z_Param_bSuccess,Z_Param_Message,Z_Param_Username,Z_Param_AccountId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientAccountAuthenticationResult 

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientBeginProfileSnapshot *****
struct DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms
{
	FGuid TransferId;
	int32 Protocol;
	int64 Revision;
	FString AccountId;
	int32 ByteCount;
	int32 JsonByteCount;
	int64 Checksum;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientBeginProfileSnapshot = FName(TEXT("ClientBeginProfileSnapshot"));
void ADigimonVenomNXTPlayerController::ClientBeginProfileSnapshot(FGuid TransferId, int32 Protocol, int64 Revision, const FString& AccountId, int32 ByteCount, int32 JsonByteCount, int64 Checksum)
{
	DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms Parms;
	Parms.TransferId=TransferId;
	Parms.Protocol=Protocol;
	Parms.Revision=Revision;
	Parms.AccountId=AccountId;
	Parms.ByteCount=ByteCount;
	Parms.JsonByteCount=JsonByteCount;
	Parms.Checksum=Checksum;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientBeginProfileSnapshot);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientBeginProfileSnapshot_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientBeginProfileSnapshot constinit property declarations ************
	static const UECodeGen_Private::FStructPropertyParams NewProp_TransferId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Protocol;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ByteCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_JsonByteCount;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Checksum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientBeginProfileSnapshot constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientBeginProfileSnapshot Property Definitions ***********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TransferId = { "TransferId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, TransferId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Protocol = { "Protocol", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, Protocol), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ByteCount = { "ByteCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, ByteCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_JsonByteCount = { "JsonByteCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, JsonByteCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Checksum = { "Checksum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms, Checksum), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TransferId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Protocol,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ByteCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JsonByteCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Checksum,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientBeginProfileSnapshot Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientBeginProfileSnapshot", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientBeginProfileSnapshot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientBeginProfileSnapshot(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientBeginProfileSnapshot)
{
	P_GET_STRUCT(FGuid,Z_Param_TransferId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Protocol);
	P_GET_PROPERTY(FInt64Property,Z_Param_Revision);
	P_GET_PROPERTY(FStrProperty,Z_Param_AccountId);
	P_GET_PROPERTY(FIntProperty,Z_Param_ByteCount);
	P_GET_PROPERTY(FIntProperty,Z_Param_JsonByteCount);
	P_GET_PROPERTY(FInt64Property,Z_Param_Checksum);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientBeginProfileSnapshot_Implementation(Z_Param_TransferId,Z_Param_Protocol,Z_Param_Revision,Z_Param_AccountId,Z_Param_ByteCount,Z_Param_JsonByteCount,Z_Param_Checksum);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientBeginProfileSnapshot *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientHostSessionClosed ********
struct DigimonVenomNXTPlayerController_eventClientHostSessionClosed_Parms
{
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientHostSessionClosed = FName(TEXT("ClientHostSessionClosed"));
void ADigimonVenomNXTPlayerController::ClientHostSessionClosed(const FString& Message)
{
	DigimonVenomNXTPlayerController_eventClientHostSessionClosed_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientHostSessionClosed);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientHostSessionClosed_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sent only after the host has checkpointed online/disconnected profiles and server ledgers. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sent only after the host has checkpointed online/disconnected profiles and server ledgers." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientHostSessionClosed constinit property declarations ***************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientHostSessionClosed constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientHostSessionClosed Property Definitions **************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientHostSessionClosed_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientHostSessionClosed Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientHostSessionClosed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientHostSessionClosed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientHostSessionClosed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientHostSessionClosed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientHostSessionClosed)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientHostSessionClosed_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientHostSessionClosed **********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientLogoutResult *************
struct DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms
{
	FGuid RequestId;
	bool bSuccess;
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientLogoutResult = FName(TEXT("ClientLogoutResult"));
void ADigimonVenomNXTPlayerController::ClientLogoutResult(FGuid RequestId, bool bSuccess, const FString& Message)
{
	DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms Parms;
	Parms.RequestId=RequestId;
	Parms.bSuccess=bSuccess ? true : false;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientLogoutResult);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientLogoutResult_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientLogoutResult constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RequestId;
	static void NewProp_bSuccess_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms*)Obj)->bSuccess = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientLogoutResult constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientLogoutResult Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RequestId = { "RequestId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms, RequestId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms), &UHT_STATICS::NewProp_bSuccess_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequestId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientLogoutResult Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientLogoutResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientLogoutResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientLogoutResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientLogoutResult)
{
	P_GET_STRUCT(FGuid,Z_Param_RequestId);
	P_GET_UBOOL(Z_Param_bSuccess);
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientLogoutResult_Implementation(Z_Param_RequestId,Z_Param_bSuccess,Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientLogoutResult ***************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientPlayAudioCue *************
struct DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms
{
	EDigimonAudioCue Cue;
	FGuid ReceiptId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientPlayAudioCue = FName(TEXT("ClientPlayAudioCue"));
void ADigimonVenomNXTPlayerController::ClientPlayAudioCue(EDigimonAudioCue Cue, FGuid ReceiptId)
{
	DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms Parms;
	Parms.Cue=Cue;
	Parms.ReceiptId=ReceiptId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientPlayAudioCue);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayAudioCue_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server confirms the operation; playback is local and receipt-deduplicated. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server confirms the operation; playback is local and receipt-deduplicated." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClientPlayAudioCue constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Cue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Cue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReceiptId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientPlayAudioCue constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientPlayAudioCue Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Cue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Cue = { "Cue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms, Cue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonAudioCue, METADATA_PARAMS(0, nullptr) }; // 69e30e3df0ae325d7904c551340b5e7b1ff8c271
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReceiptId = { "ReceiptId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms, ReceiptId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReceiptId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientPlayAudioCue Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientPlayAudioCue", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientPlayAudioCue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayAudioCue(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientPlayAudioCue)
{
	P_GET_ENUM(EDigimonAudioCue,Z_Param_Cue);
	P_GET_STRUCT(FGuid,Z_Param_ReceiptId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientPlayAudioCue_Implementation(EDigimonAudioCue(Z_Param_Cue),Z_Param_ReceiptId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientPlayAudioCue ***************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientPlayExplorationMusic *****
struct DigimonVenomNXTPlayerController_eventClientPlayExplorationMusic_Parms
{
	int32 MapId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientPlayExplorationMusic = FName(TEXT("ClientPlayExplorationMusic"));
void ADigimonVenomNXTPlayerController::ClientPlayExplorationMusic(int32 MapId)
{
	DigimonVenomNXTPlayerController_eventClientPlayExplorationMusic_Parms Parms;
	Parms.MapId=MapId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientPlayExplorationMusic);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayExplorationMusic_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Audio" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientPlayExplorationMusic constinit property declarations ************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientPlayExplorationMusic constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientPlayExplorationMusic Property Definitions ***********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientPlayExplorationMusic_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientPlayExplorationMusic Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientPlayExplorationMusic", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientPlayExplorationMusic_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientPlayExplorationMusic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayExplorationMusic(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientPlayExplorationMusic)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientPlayExplorationMusic_Implementation(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientPlayExplorationMusic *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientProfileSnapshotChunk *****
struct DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms
{
	FGuid TransferId;
	int32 Offset;
	TArray<uint8> Bytes;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientProfileSnapshotChunk = FName(TEXT("ClientProfileSnapshotChunk"));
void ADigimonVenomNXTPlayerController::ClientProfileSnapshotChunk(FGuid TransferId, int32 Offset, TArray<uint8> const& Bytes)
{
	DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms Parms;
	Parms.TransferId=TransferId;
	Parms.Offset=Offset;
	Parms.Bytes=Bytes;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientProfileSnapshotChunk);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSnapshotChunk_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bytes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientProfileSnapshotChunk constinit property declarations ************
	static const UECodeGen_Private::FStructPropertyParams NewProp_TransferId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Offset;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Bytes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Bytes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientProfileSnapshotChunk constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientProfileSnapshotChunk Property Definitions ***********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TransferId = { "TransferId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms, TransferId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms, Offset), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Bytes_Inner = { "Bytes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Bytes = { "Bytes", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms, Bytes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bytes_MetaData), NewProp_Bytes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TransferId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Offset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bytes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bytes,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientProfileSnapshotChunk Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientProfileSnapshotChunk", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientProfileSnapshotChunk_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSnapshotChunk(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientProfileSnapshotChunk)
{
	P_GET_STRUCT(FGuid,Z_Param_TransferId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Offset);
	P_GET_TARRAY(uint8,Z_Param_Bytes);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientProfileSnapshotChunk_Implementation(Z_Param_TransferId,Z_Param_Offset,Z_Param_Bytes);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientProfileSnapshotChunk *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientProfileSynchronizationFailed 
struct DigimonVenomNXTPlayerController_eventClientProfileSynchronizationFailed_Parms
{
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientProfileSynchronizationFailed = FName(TEXT("ClientProfileSynchronizationFailed"));
void ADigimonVenomNXTPlayerController::ClientProfileSynchronizationFailed(const FString& Message)
{
	DigimonVenomNXTPlayerController_eventClientProfileSynchronizationFailed_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientProfileSynchronizationFailed);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSynchronizationFailed_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientProfileSynchronizationFailed constinit property declarations ****
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientProfileSynchronizationFailed constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientProfileSynchronizationFailed Property Definitions ***************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientProfileSynchronizationFailed_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientProfileSynchronizationFailed Property Definitions *****************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientProfileSynchronizationFailed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientProfileSynchronizationFailed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientProfileSynchronizationFailed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSynchronizationFailed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientProfileSynchronizationFailed)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientProfileSynchronizationFailed_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientProfileSynchronizationFailed 

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientReceiveAIRivalActivity ***
struct DigimonVenomNXTPlayerController_eventClientReceiveAIRivalActivity_Parms
{
	FDigimonAIRivalActivityPage Page;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientReceiveAIRivalActivity = FName(TEXT("ClientReceiveAIRivalActivity"));
void ADigimonVenomNXTPlayerController::ClientReceiveAIRivalActivity(FDigimonAIRivalActivityPage const& Page)
{
	DigimonVenomNXTPlayerController_eventClientReceiveAIRivalActivity_Parms Parms;
	Parms.Page=Page;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientReceiveAIRivalActivity);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveAIRivalActivity_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Page_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientReceiveAIRivalActivity constinit property declarations **********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Page;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientReceiveAIRivalActivity constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientReceiveAIRivalActivity Property Definitions *********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientReceiveAIRivalActivity_Parms, Page), Z_Construct_UScriptStruct_FDigimonAIRivalActivityPage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Page_MetaData), NewProp_Page_MetaData) }; // 8fb19c9299962509f91282c6ddf27a520cdb2f77
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientReceiveAIRivalActivity Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientReceiveAIRivalActivity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientReceiveAIRivalActivity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientReceiveAIRivalActivity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveAIRivalActivity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientReceiveAIRivalActivity)
{
	P_GET_STRUCT(FDigimonAIRivalActivityPage,Z_Param_Page);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientReceiveAIRivalActivity_Implementation(Z_Param_Page);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientReceiveAIRivalActivity *****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientReceiveLocalChat *********
struct DigimonVenomNXTPlayerController_eventClientReceiveLocalChat_Parms
{
	FDigimonChatMessage Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientReceiveLocalChat = FName(TEXT("ClientReceiveLocalChat"));
void ADigimonVenomNXTPlayerController::ClientReceiveLocalChat(FDigimonChatMessage const& Message)
{
	DigimonVenomNXTPlayerController_eventClientReceiveLocalChat_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientReceiveLocalChat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveLocalChat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientReceiveLocalChat constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientReceiveLocalChat constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientReceiveLocalChat Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientReceiveLocalChat_Parms, Message), Z_Construct_UScriptStruct_FDigimonChatMessage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientReceiveLocalChat Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientReceiveLocalChat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientReceiveLocalChat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientReceiveLocalChat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveLocalChat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientReceiveLocalChat)
{
	P_GET_STRUCT(FDigimonChatMessage,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientReceiveLocalChat_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientReceiveLocalChat ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientReceiveSeasonArchive *****
struct DigimonVenomNXTPlayerController_eventClientReceiveSeasonArchive_Parms
{
	FDigimonSeasonArchivePage Page;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientReceiveSeasonArchive = FName(TEXT("ClientReceiveSeasonArchive"));
void ADigimonVenomNXTPlayerController::ClientReceiveSeasonArchive(FDigimonSeasonArchivePage const& Page)
{
	DigimonVenomNXTPlayerController_eventClientReceiveSeasonArchive_Parms Parms;
	Parms.Page=Page;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientReceiveSeasonArchive);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveSeasonArchive_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Page_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientReceiveSeasonArchive constinit property declarations ************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Page;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientReceiveSeasonArchive constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientReceiveSeasonArchive Property Definitions ***********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Page = { "Page", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientReceiveSeasonArchive_Parms, Page), Z_Construct_UScriptStruct_FDigimonSeasonArchivePage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Page_MetaData), NewProp_Page_MetaData) }; // 80c6bd44f1ff8717382adef8167abbcfb94ffd23
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Page,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientReceiveSeasonArchive Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientReceiveSeasonArchive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientReceiveSeasonArchive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientReceiveSeasonArchive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveSeasonArchive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientReceiveSeasonArchive)
{
	P_GET_STRUCT(FDigimonSeasonArchivePage,Z_Param_Page);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientReceiveSeasonArchive_Implementation(Z_Param_Page);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientReceiveSeasonArchive *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientReturnFromSeason *********
static FName NAME_ADigimonVenomNXTPlayerController_ClientReturnFromSeason = FName(TEXT("ClientReturnFromSeason"));
void ADigimonVenomNXTPlayerController::ClientReturnFromSeason()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientReturnFromSeason);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnFromSeason_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientReturnFromSeason constinit property declarations ****************
// ********** End Function ClientReturnFromSeason constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientReturnFromSeason", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnFromSeason(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientReturnFromSeason)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientReturnFromSeason_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientReturnFromSeason ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientReturnToSeason ***********
static FName NAME_ADigimonVenomNXTPlayerController_ClientReturnToSeason = FName(TEXT("ClientReturnToSeason"));
void ADigimonVenomNXTPlayerController::ClientReturnToSeason()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientReturnToSeason);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnToSeason_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientReturnToSeason constinit property declarations ******************
// ********** End Function ClientReturnToSeason constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientReturnToSeason", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnToSeason(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientReturnToSeason)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientReturnToSeason_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientReturnToSeason *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientSetActiveMapPresentation *
struct DigimonVenomNXTPlayerController_eventClientSetActiveMapPresentation_Parms
{
	int32 MapId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientSetActiveMapPresentation = FName(TEXT("ClientSetActiveMapPresentation"));
void ADigimonVenomNXTPlayerController::ClientSetActiveMapPresentation(int32 MapId)
{
	DigimonVenomNXTPlayerController_eventClientSetActiveMapPresentation_Parms Parms;
	Parms.MapId=MapId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientSetActiveMapPresentation);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetActiveMapPresentation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Makes only this client's current habitat ground visible, preventing cross-map overlap/z-fighting. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Makes only this client's current habitat ground visible, preventing cross-map overlap/z-fighting." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClientSetActiveMapPresentation constinit property declarations ********
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientSetActiveMapPresentation constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientSetActiveMapPresentation Property Definitions *******************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetActiveMapPresentation_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientSetActiveMapPresentation Property Definitions *********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientSetActiveMapPresentation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientSetActiveMapPresentation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientSetActiveMapPresentation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetActiveMapPresentation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientSetActiveMapPresentation)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientSetActiveMapPresentation_Implementation(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientSetActiveMapPresentation ***

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientSetDigiFarmPresentation **
struct DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms
{
	bool bInside;
	FVector Origin;
	int32 ReturnMapId;
	uint64 Revision;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientSetDigiFarmPresentation = FName(TEXT("ClientSetDigiFarmPresentation"));
void ADigimonVenomNXTPlayerController::ClientSetDigiFarmPresentation(bool bInside, FVector Origin, int32 ReturnMapId, uint64 Revision)
{
	DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms Parms;
	Parms.bInside=bInside ? true : false;
	Parms.Origin=Origin;
	Parms.ReturnMapId=ReturnMapId;
	Parms.Revision=Revision;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientSetDigiFarmPresentation);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetDigiFarmPresentation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientSetDigiFarmPresentation constinit property declarations *********
	static void NewProp_bInside_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms*)Obj)->bInside = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInside;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Origin;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnMapId;
	static const UECodeGen_Private::FUInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientSetDigiFarmPresentation constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientSetDigiFarmPresentation Property Definitions ********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bInside = { "bInside", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms), &UHT_STATICS::NewProp_bInside_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Origin = { "Origin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms, Origin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnMapId = { "ReturnMapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms, ReturnMapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FUInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::UInt64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bInside,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Origin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnMapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientSetDigiFarmPresentation Property Definitions **********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientSetDigiFarmPresentation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientSetDigiFarmPresentation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetDigiFarmPresentation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientSetDigiFarmPresentation)
{
	P_GET_UBOOL(Z_Param_bInside);
	P_GET_STRUCT(FVector,Z_Param_Origin);
	P_GET_PROPERTY(FIntProperty,Z_Param_ReturnMapId);
	P_GET_PROPERTY(FUInt64Property,Z_Param_Revision);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientSetDigiFarmPresentation_Implementation(Z_Param_bInside,Z_Param_Origin,Z_Param_ReturnMapId,Z_Param_Revision);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientSetDigiFarmPresentation ****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientSetRelayPresentation *****
struct DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms
{
	EDigimonPrivateCampaign Campaign;
	bool bInside;
	int32 MapId;
	FVector Origin;
	uint64 Revision;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientSetRelayPresentation = FName(TEXT("ClientSetRelayPresentation"));
void ADigimonVenomNXTPlayerController::ClientSetRelayPresentation(EDigimonPrivateCampaign Campaign, bool bInside, int32 MapId, FVector Origin, uint64 Revision)
{
	DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms Parms;
	Parms.Campaign=Campaign;
	Parms.bInside=bInside ? true : false;
	Parms.MapId=MapId;
	Parms.Origin=Origin;
	Parms.Revision=Revision;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientSetRelayPresentation);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetRelayPresentation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientSetRelayPresentation constinit property declarations ************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Campaign_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Campaign;
	static void NewProp_bInside_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms*)Obj)->bInside = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInside;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Origin;
	static const UECodeGen_Private::FUInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientSetRelayPresentation constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientSetRelayPresentation Property Definitions ***********************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Campaign_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Campaign = { "Campaign", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms, Campaign), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonPrivateCampaign, METADATA_PARAMS(0, nullptr) }; // 13bd3e9de9f6f2f40b1ef878b84716e0b7a25bab
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bInside = { "bInside", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms), &UHT_STATICS::NewProp_bInside_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Origin = { "Origin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms, Origin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FUInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::UInt64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bInside,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Origin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientSetRelayPresentation Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientSetRelayPresentation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01820CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientSetRelayPresentation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetRelayPresentation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientSetRelayPresentation)
{
	P_GET_ENUM(EDigimonPrivateCampaign,Z_Param_Campaign);
	P_GET_UBOOL(Z_Param_bInside);
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_GET_STRUCT(FVector,Z_Param_Origin);
	P_GET_PROPERTY(FUInt64Property,Z_Param_Revision);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientSetRelayPresentation_Implementation(EDigimonPrivateCampaign(Z_Param_Campaign),Z_Param_bInside,Z_Param_MapId,Z_Param_Origin,Z_Param_Revision);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientSetRelayPresentation *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientShowMessage **************
struct DigimonVenomNXTPlayerController_eventClientShowMessage_Parms
{
	FString Title;
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientShowMessage = FName(TEXT("ClientShowMessage"));
void ADigimonVenomNXTPlayerController::ClientShowMessage(const FString& Title, const FString& Message)
{
	DigimonVenomNXTPlayerController_eventClientShowMessage_Parms Parms;
	Parms.Title=Title;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientShowMessage);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowMessage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Title_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientShowMessage constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Title;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientShowMessage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientShowMessage Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Title = { "Title", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowMessage_Parms, Title), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Title_MetaData), NewProp_Title_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowMessage_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Title,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientShowMessage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientShowMessage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientShowMessage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientShowMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowMessage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientShowMessage)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Title);
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientShowMessage_Implementation(Z_Param_Title,Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientShowMessage ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ClientShowRelayDialogue ********
struct DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms
{
	FName NPCId;
	FString Dialogue;
	EDigimonPrivateCampaign Campaign;
	FDigimonRelayProgress ConfirmedProgress;
};
static FName NAME_ADigimonVenomNXTPlayerController_ClientShowRelayDialogue = FName(TEXT("ClientShowRelayDialogue"));
void ADigimonVenomNXTPlayerController::ClientShowRelayDialogue(FName NPCId, const FString& Dialogue, EDigimonPrivateCampaign Campaign, FDigimonRelayProgress const& ConfirmedProgress)
{
	DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms Parms;
	Parms.NPCId=NPCId;
	Parms.Dialogue=Dialogue;
	Parms.Campaign=Campaign;
	Parms.ConfirmedProgress=ConfirmedProgress;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ClientShowRelayDialogue);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowRelayDialogue_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dialogue_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConfirmedProgress_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClientShowRelayDialogue constinit property declarations ***************
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Dialogue;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Campaign_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Campaign;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ConfirmedProgress;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClientShowRelayDialogue constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClientShowRelayDialogue Property Definitions **************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Dialogue = { "Dialogue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms, Dialogue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dialogue_MetaData), NewProp_Dialogue_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Campaign_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Campaign = { "Campaign", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms, Campaign), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonPrivateCampaign, METADATA_PARAMS(0, nullptr) }; // 13bd3e9de9f6f2f40b1ef878b84716e0b7a25bab
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ConfirmedProgress = { "ConfirmedProgress", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms, ConfirmedProgress), Z_Construct_UScriptStruct_FDigimonRelayProgress, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConfirmedProgress_MetaData), NewProp_ConfirmedProgress_MetaData) }; // 6c57e16f81b8e83a6df3b845191f9c7a82333f84
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Dialogue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Campaign,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ConfirmedProgress,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ClientShowRelayDialogue Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ClientShowRelayDialogue", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventClientShowRelayDialogue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowRelayDialogue(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execClientShowRelayDialogue)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Dialogue);
	P_GET_ENUM(EDigimonPrivateCampaign,Z_Param_Campaign);
	P_GET_STRUCT(FDigimonRelayProgress,Z_Param_ConfirmedProgress);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClientShowRelayDialogue_Implementation(Z_Param_NPCId,Z_Param_Dialogue,EDigimonPrivateCampaign(Z_Param_Campaign),Z_Param_ConfirmedProgress);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ClientShowRelayDialogue **********

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetDigiFarmOrigin **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmOrigin_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetDigiFarmOrigin_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetDigiFarmOrigin constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDigiFarmOrigin constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDigiFarmOrigin Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetDigiFarmOrigin_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDigiFarmOrigin Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetDigiFarmOrigin", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetDigiFarmOrigin_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetDigiFarmOrigin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmOrigin(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetDigiFarmOrigin)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetDigiFarmOrigin();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetDigiFarmOrigin ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetDigiFarmScene ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmScene_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetDigiFarmScene_Parms
	{
		ADigimonVenomNXTFarmScene* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetDigiFarmScene constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDigiFarmScene constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDigiFarmScene Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetDigiFarmScene_Parms, ReturnValue), Z_Construct_UClass_ADigimonVenomNXTFarmScene, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDigiFarmScene Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetDigiFarmScene", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetDigiFarmScene_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetDigiFarmScene_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmScene(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetDigiFarmScene)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ADigimonVenomNXTFarmScene**)Z_Param__Result=P_THIS->GetDigiFarmScene();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetDigiFarmScene *****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetNativeBattleWidget **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeBattleWidget_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetNativeBattleWidget_Parms
	{
		UDigimonVenomNXTBattleWidget* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNativeBattleWidget constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNativeBattleWidget constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNativeBattleWidget Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetNativeBattleWidget_Parms, ReturnValue), Z_Construct_UClass_UDigimonVenomNXTBattleWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetNativeBattleWidget Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetNativeBattleWidget", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNativeBattleWidget_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNativeBattleWidget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeBattleWidget(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetNativeBattleWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UDigimonVenomNXTBattleWidget**)Z_Param__Result=P_THIS->GetNativeBattleWidget();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetNativeBattleWidget ************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetNativeHUDWidget *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeHUDWidget_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetNativeHUDWidget_Parms
	{
		UDigimonVenomNXTGameHUDWidget* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNativeHUDWidget constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNativeHUDWidget constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNativeHUDWidget Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetNativeHUDWidget_Parms, ReturnValue), Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetNativeHUDWidget Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetNativeHUDWidget", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNativeHUDWidget_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNativeHUDWidget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeHUDWidget(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetNativeHUDWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UDigimonVenomNXTGameHUDWidget**)Z_Param__Result=P_THIS->GetNativeHUDWidget();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetNativeHUDWidget ***************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetNearestRelayNPC *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNearestRelayNPC_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetNearestRelayNPC_Parms
	{
		FName ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNearestRelayNPC constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNearestRelayNPC constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNearestRelayNPC Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetNearestRelayNPC_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetNearestRelayNPC Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetNearestRelayNPC", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNearestRelayNPC_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetNearestRelayNPC_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNearestRelayNPC(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetNearestRelayNPC)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FName*)Z_Param__Result=P_THIS->GetNearestRelayNPC();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetNearestRelayNPC ***************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetRelayMapId ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayMapId_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetRelayMapId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRelayMapId constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRelayMapId constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRelayMapId Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayMapId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRelayMapId Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetRelayMapId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayMapId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayMapId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayMapId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetRelayMapId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetRelayMapId();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetRelayMapId ********************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetRelayNPCLocation ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayNPCLocation_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetRelayNPCLocation_Parms
	{
		FName NPCId;
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRelayNPCLocation constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRelayNPCLocation constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRelayNPCLocation Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayNPCLocation_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayNPCLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRelayNPCLocation Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetRelayNPCLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayNPCLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayNPCLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayNPCLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetRelayNPCLocation)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetRelayNPCLocation(Z_Param_NPCId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetRelayNPCLocation **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetRelayOrigin *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayOrigin_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetRelayOrigin_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRelayOrigin constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRelayOrigin constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRelayOrigin Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayOrigin_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRelayOrigin Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetRelayOrigin", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayOrigin_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayOrigin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayOrigin(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetRelayOrigin)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetRelayOrigin();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetRelayOrigin *******************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetRelayPortalLocation *********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalLocation_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms
	{
		bool bForward;
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRelayPortalLocation constinit property declarations ****************
	static void NewProp_bForward_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms*)Obj)->bForward = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bForward;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRelayPortalLocation constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRelayPortalLocation Property Definitions ***************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bForward = { "bForward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms), &UHT_STATICS::NewProp_bForward_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bForward,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRelayPortalLocation Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetRelayPortalLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayPortalLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetRelayPortalLocation)
{
	P_GET_UBOOL(Z_Param_bForward);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetRelayPortalLocation(Z_Param_bForward);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetRelayPortalLocation ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetRelayPortalTarget ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalTarget_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms
	{
		bool bForward;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Destination of the visible portal, or INDEX_NONE. Includes the completed GhostLine return to HQ. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Destination of the visible portal, or INDEX_NONE. Includes the completed GhostLine return to HQ." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetRelayPortalTarget constinit property declarations ******************
	static void NewProp_bForward_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms*)Obj)->bForward = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bForward;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRelayPortalTarget constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRelayPortalTarget Property Definitions *****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bForward = { "bForward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms), &UHT_STATICS::NewProp_bForward_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bForward,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRelayPortalTarget Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetRelayPortalTarget", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetRelayPortalTarget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalTarget(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetRelayPortalTarget)
{
	P_GET_UBOOL(Z_Param_bForward);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetRelayPortalTarget(Z_Param_bForward);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetRelayPortalTarget *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function GetStoryCampaign ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetStoryCampaign_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventGetStoryCampaign_Parms
	{
		EDigimonPrivateCampaign ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Compatibility name: true inside any private story world; privacy guards intentionally share it. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Compatibility name: true inside any private story world; privacy guards intentionally share it." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetStoryCampaign constinit property declarations **********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStoryCampaign constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStoryCampaign Property Definitions *********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventGetStoryCampaign_Parms, ReturnValue), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonPrivateCampaign, METADATA_PARAMS(0, nullptr) }; // 13bd3e9de9f6f2f40b1ef878b84716e0b7a25bab
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetStoryCampaign Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "GetStoryCampaign", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventGetStoryCampaign_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventGetStoryCampaign_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetStoryCampaign(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execGetStoryCampaign)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EDigimonPrivateCampaign*)Z_Param__Result=P_THIS->GetStoryCampaign();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function GetStoryCampaign *****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsAccountAuthenticated *********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsAccountAuthenticated_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsAccountAuthenticated_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsAccountAuthenticated constinit property declarations ****************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsAccountAuthenticated_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsAccountAuthenticated constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsAccountAuthenticated Property Definitions ***************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsAccountAuthenticated_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsAccountAuthenticated Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsAccountAuthenticated", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsAccountAuthenticated_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsAccountAuthenticated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsAccountAuthenticated(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsAccountAuthenticated)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsAccountAuthenticated();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsAccountAuthenticated ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsFieldInputBlocked ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldInputBlocked_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsFieldInputBlocked_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsFieldInputBlocked constinit property declarations *******************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsFieldInputBlocked_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsFieldInputBlocked constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsFieldInputBlocked Property Definitions ******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsFieldInputBlocked_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsFieldInputBlocked Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsFieldInputBlocked", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsFieldInputBlocked_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsFieldInputBlocked_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldInputBlocked(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsFieldInputBlocked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsFieldInputBlocked();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsFieldInputBlocked **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsFieldMenuOpen ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldMenuOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsFieldMenuOpen_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsFieldMenuOpen constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsFieldMenuOpen_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsFieldMenuOpen constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsFieldMenuOpen Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsFieldMenuOpen_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsFieldMenuOpen Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsFieldMenuOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsFieldMenuOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsFieldMenuOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldMenuOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsFieldMenuOpen)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsFieldMenuOpen();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsFieldMenuOpen ******************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsInChronicles *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInChronicles_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsInChronicles_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsInChronicles constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsInChronicles_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsInChronicles constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsInChronicles Property Definitions ***********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsInChronicles_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsInChronicles Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsInChronicles", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInChronicles_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInChronicles_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInChronicles(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsInChronicles)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsInChronicles();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsInChronicles *******************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsInDigiFarm *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInDigiFarm_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsInDigiFarm_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Owner-only private farm session. The public map remains the saved return habitat. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Owner-only private farm session. The public map remains the saved return habitat." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsInDigiFarm constinit property declarations **************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsInDigiFarm_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsInDigiFarm constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsInDigiFarm Property Definitions *************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsInDigiFarm_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsInDigiFarm Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsInDigiFarm", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInDigiFarm_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInDigiFarm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInDigiFarm(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsInDigiFarm)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsInDigiFarm();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsInDigiFarm *********************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsInGhostLine ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInGhostLine_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsInGhostLine_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsInGhostLine constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsInGhostLine_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsInGhostLine constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsInGhostLine Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsInGhostLine_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsInGhostLine Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsInGhostLine", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInGhostLine_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInGhostLine_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInGhostLine(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsInGhostLine)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsInGhostLine();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsInGhostLine ********************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsInRelay **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelay_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsInRelay_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsInRelay constinit property declarations *****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsInRelay_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsInRelay constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsInRelay Property Definitions ****************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsInRelay_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsInRelay Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsInRelay", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInRelay_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInRelay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsInRelay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsInRelay();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsInRelay ************************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsInRelayCampaign **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelayCampaign_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsInRelayCampaign_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsInRelayCampaign constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsInRelayCampaign_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsInRelayCampaign constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsInRelayCampaign Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsInRelayCampaign_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsInRelayCampaign Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsInRelayCampaign", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInRelayCampaign_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsInRelayCampaign_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelayCampaign(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsInRelayCampaign)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsInRelayCampaign();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsInRelayCampaign ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsLogoutPending ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsLogoutPending_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsLogoutPending_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsLogoutPending constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsLogoutPending_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsLogoutPending constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsLogoutPending Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsLogoutPending_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsLogoutPending Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsLogoutPending", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsLogoutPending_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsLogoutPending_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsLogoutPending(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsLogoutPending)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsLogoutPending();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsLogoutPending ******************

// ********** Begin Class ADigimonVenomNXTPlayerController Function IsOwnerProfileReady ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsOwnerProfileReady_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventIsOwnerProfileReady_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True only after this connection has a complete, identity-checked owner profile. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True only after this connection has a complete, identity-checked owner profile." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsOwnerProfileReady constinit property declarations *******************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventIsOwnerProfileReady_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsOwnerProfileReady constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsOwnerProfileReady Property Definitions ******************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventIsOwnerProfileReady_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsOwnerProfileReady Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "IsOwnerProfileReady", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventIsOwnerProfileReady_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventIsOwnerProfileReady_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsOwnerProfileReady(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execIsOwnerProfileReady)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsOwnerProfileReady();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function IsOwnerProfileReady **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function OnRep_CurrentBattle ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_CurrentBattle_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_CurrentBattle constinit property declarations *******************
// ********** End Function OnRep_CurrentBattle constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "OnRep_CurrentBattle", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_CurrentBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execOnRep_CurrentBattle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentBattle();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function OnRep_CurrentBattle **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function OnRep_DigiFarmSession **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_DigiFarmSession_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_DigiFarmSession constinit property declarations *****************
// ********** End Function OnRep_DigiFarmSession constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "OnRep_DigiFarmSession", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_DigiFarmSession(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execOnRep_DigiFarmSession)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_DigiFarmSession();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function OnRep_DigiFarmSession ************

// ********** Begin Class ADigimonVenomNXTPlayerController Function OnRep_RelaySession *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_RelaySession_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_RelaySession constinit property declarations ********************
// ********** End Function OnRep_RelaySession constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "OnRep_RelaySession", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_RelaySession(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execOnRep_RelaySession)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_RelaySession();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function OnRep_RelaySession ***************

// ********** Begin Class ADigimonVenomNXTPlayerController Function RequestLogout ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RequestLogout_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventRequestLogout_Parms
	{
		FString OutError;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Local UI entry point. Ordinary logout acknowledges memory retention; admin logout also flushes every pending disk checkpoint. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local UI entry point. Ordinary logout acknowledges memory retention; admin logout also flushes every pending disk checkpoint." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RequestLogout constinit property declarations *************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutError;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventRequestLogout_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RequestLogout constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RequestLogout Property Definitions ************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutError = { "OutError", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventRequestLogout_Parms, OutError), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventRequestLogout_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutError,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RequestLogout Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "RequestLogout", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventRequestLogout_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventRequestLogout_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RequestLogout(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execRequestLogout)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutError);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->RequestLogout(Z_Param_Out_OutError);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function RequestLogout ********************

// ********** Begin Class ADigimonVenomNXTPlayerController Function RetryProfileSynchronization ****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RetryProfileSynchronization_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RetryProfileSynchronization constinit property declarations ***********
// ********** End Function RetryProfileSynchronization constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "RetryProfileSynchronization", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RetryProfileSynchronization(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execRetryProfileSynchronization)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RetryProfileSynchronization();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function RetryProfileSynchronization ******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAcknowledgeBattlePresentation 
struct DigimonVenomNXTPlayerController_eventServerAcknowledgeBattlePresentation_Parms
{
	ADigimonVenomNXTBattleActor* BattleActor;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerAcknowledgeBattlePresentation = FName(TEXT("ServerAcknowledgeBattlePresentation"));
void ADigimonVenomNXTPlayerController::ServerAcknowledgeBattlePresentation(ADigimonVenomNXTBattleActor* BattleActor)
{
	DigimonVenomNXTPlayerController_eventServerAcknowledgeBattlePresentation_Parms Parms;
	Parms.BattleActor=BattleActor;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAcknowledgeBattlePresentation);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeBattlePresentation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sent only after the local battle widget has bound its presentation stream. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sent only after the local battle widget has bound its presentation stream." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAcknowledgeBattlePresentation constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerAcknowledgeBattlePresentation constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerAcknowledgeBattlePresentation Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleActor = { "BattleActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAcknowledgeBattlePresentation_Parms, BattleActor), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleActor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerAcknowledgeBattlePresentation Property Definitions ****************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAcknowledgeBattlePresentation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerAcknowledgeBattlePresentation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerAcknowledgeBattlePresentation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeBattlePresentation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAcknowledgeBattlePresentation)
{
	P_GET_OBJECT(ADigimonVenomNXTBattleActor,Z_Param_BattleActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAcknowledgeBattlePresentation_Implementation(Z_Param_BattleActor);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAcknowledgeBattlePresentation 

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAcknowledgeProfileChunk **
struct DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms
{
	FGuid TransferId;
	int32 Offset;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerAcknowledgeProfileChunk = FName(TEXT("ServerAcknowledgeProfileChunk"));
void ADigimonVenomNXTPlayerController::ServerAcknowledgeProfileChunk(FGuid TransferId, int32 Offset)
{
	DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms Parms;
	Parms.TransferId=TransferId;
	Parms.Offset=Offset;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAcknowledgeProfileChunk);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeProfileChunk_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAcknowledgeProfileChunk constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_TransferId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Offset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerAcknowledgeProfileChunk constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerAcknowledgeProfileChunk Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TransferId = { "TransferId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms, TransferId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms, Offset), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TransferId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Offset,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerAcknowledgeProfileChunk Property Definitions **********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAcknowledgeProfileChunk", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerAcknowledgeProfileChunk_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeProfileChunk(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAcknowledgeProfileChunk)
{
	P_GET_STRUCT(FGuid,Z_Param_TransferId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Offset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAcknowledgeProfileChunk_Implementation(Z_Param_TransferId,Z_Param_Offset);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAcknowledgeProfileChunk ****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAdvanceChroniclesQuest ***
struct DigimonVenomNXTPlayerController_eventServerAdvanceChroniclesQuest_Parms
{
	FName NPCId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerAdvanceChroniclesQuest = FName(TEXT("ServerAdvanceChroniclesQuest"));
void ADigimonVenomNXTPlayerController::ServerAdvanceChroniclesQuest(FName NPCId)
{
	DigimonVenomNXTPlayerController_eventServerAdvanceChroniclesQuest_Parms Parms;
	Parms.NPCId=NPCId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAdvanceChroniclesQuest);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceChroniclesQuest_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAdvanceChroniclesQuest constinit property declarations **********
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerAdvanceChroniclesQuest constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerAdvanceChroniclesQuest Property Definitions *********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAdvanceChroniclesQuest_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerAdvanceChroniclesQuest Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAdvanceChroniclesQuest", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerAdvanceChroniclesQuest_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerAdvanceChroniclesQuest_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceChroniclesQuest(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAdvanceChroniclesQuest)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAdvanceChroniclesQuest_Implementation(Z_Param_NPCId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAdvanceChroniclesQuest *****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAdvanceGhostLineQuest ****
struct DigimonVenomNXTPlayerController_eventServerAdvanceGhostLineQuest_Parms
{
	FName NPCId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerAdvanceGhostLineQuest = FName(TEXT("ServerAdvanceGhostLineQuest"));
void ADigimonVenomNXTPlayerController::ServerAdvanceGhostLineQuest(FName NPCId)
{
	DigimonVenomNXTPlayerController_eventServerAdvanceGhostLineQuest_Parms Parms;
	Parms.NPCId=NPCId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAdvanceGhostLineQuest);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceGhostLineQuest_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAdvanceGhostLineQuest constinit property declarations ***********
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerAdvanceGhostLineQuest constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerAdvanceGhostLineQuest Property Definitions **********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAdvanceGhostLineQuest_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerAdvanceGhostLineQuest Property Definitions ************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAdvanceGhostLineQuest", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerAdvanceGhostLineQuest_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerAdvanceGhostLineQuest_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceGhostLineQuest(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAdvanceGhostLineQuest)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAdvanceGhostLineQuest_Implementation(Z_Param_NPCId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAdvanceGhostLineQuest ******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAdvanceSeasonWeek ********
static FName NAME_ADigimonVenomNXTPlayerController_ServerAdvanceSeasonWeek = FName(TEXT("ServerAdvanceSeasonWeek"));
void ADigimonVenomNXTPlayerController::ServerAdvanceSeasonWeek()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAdvanceSeasonWeek);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceSeasonWeek_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAdvanceSeasonWeek constinit property declarations ***************
// ********** End Function ServerAdvanceSeasonWeek constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAdvanceSeasonWeek", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceSeasonWeek(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAdvanceSeasonWeek)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAdvanceSeasonWeek_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAdvanceSeasonWeek **********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerAuthenticateAccount ******
struct DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms
{
	bool bCreateAccount;
	FString Username;
	FString Password;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerAuthenticateAccount = FName(TEXT("ServerAuthenticateAccount"));
void ADigimonVenomNXTPlayerController::ServerAuthenticateAccount(bool bCreateAccount, const FString& Username, const FString& Password)
{
	DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms Parms;
	Parms.bCreateAccount=bCreateAccount ? true : false;
	Parms.Username=Username;
	Parms.Password=Password;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerAuthenticateAccount);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAuthenticateAccount_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** First RPC sent after connecting. Account data is validated entirely by the UE host SaveGame database. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "First RPC sent after connecting. Account data is validated entirely by the UE host SaveGame database." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerAuthenticateAccount constinit property declarations *************
	static void NewProp_bCreateAccount_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms*)Obj)->bCreateAccount = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCreateAccount;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerAuthenticateAccount constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerAuthenticateAccount Property Definitions ************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bCreateAccount = { "bCreateAccount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms), &UHT_STATICS::NewProp_bCreateAccount_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms, Password), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Password_MetaData), NewProp_Password_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bCreateAccount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Password,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerAuthenticateAccount Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerAuthenticateAccount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerAuthenticateAccount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAuthenticateAccount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerAuthenticateAccount)
{
	P_GET_UBOOL(Z_Param_bCreateAccount);
	P_GET_PROPERTY(FStrProperty,Z_Param_Username);
	P_GET_PROPERTY(FStrProperty,Z_Param_Password);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerAuthenticateAccount_Implementation(Z_Param_bCreateAccount,Z_Param_Username,Z_Param_Password);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerAuthenticateAccount ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerBeginSecondStory *********
static FName NAME_ADigimonVenomNXTPlayerController_ServerBeginSecondStory = FName(TEXT("ServerBeginSecondStory"));
void ADigimonVenomNXTPlayerController::ServerBeginSecondStory()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerBeginSecondStory);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerBeginSecondStory_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerBeginSecondStory constinit property declarations ****************
// ********** End Function ServerBeginSecondStory constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerBeginSecondStory", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerBeginSecondStory(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerBeginSecondStory)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerBeginSecondStory_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerBeginSecondStory ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerChallengeAIRival *********
struct DigimonVenomNXTPlayerController_eventServerChallengeAIRival_Parms
{
	FString RivalId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerChallengeAIRival = FName(TEXT("ServerChallengeAIRival"));
void ADigimonVenomNXTPlayerController::ServerChallengeAIRival(const FString& RivalId)
{
	DigimonVenomNXTPlayerController_eventServerChallengeAIRival_Parms Parms;
	Parms.RivalId=RivalId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerChallengeAIRival);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeAIRival_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RivalId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerChallengeAIRival constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RivalId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerChallengeAIRival constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerChallengeAIRival Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_RivalId = { "RivalId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerChallengeAIRival_Parms, RivalId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RivalId_MetaData), NewProp_RivalId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RivalId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerChallengeAIRival Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerChallengeAIRival", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerChallengeAIRival_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerChallengeAIRival_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeAIRival(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerChallengeAIRival)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_RivalId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerChallengeAIRival_Implementation(Z_Param_RivalId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerChallengeAIRival ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerChallengeRelayNPC ********
struct DigimonVenomNXTPlayerController_eventServerChallengeRelayNPC_Parms
{
	FName NPCId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerChallengeRelayNPC = FName(TEXT("ServerChallengeRelayNPC"));
void ADigimonVenomNXTPlayerController::ServerChallengeRelayNPC(FName NPCId)
{
	DigimonVenomNXTPlayerController_eventServerChallengeRelayNPC_Parms Parms;
	Parms.NPCId=NPCId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerChallengeRelayNPC);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeRelayNPC_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerChallengeRelayNPC constinit property declarations ***************
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerChallengeRelayNPC constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerChallengeRelayNPC Property Definitions **************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerChallengeRelayNPC_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerChallengeRelayNPC Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerChallengeRelayNPC", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerChallengeRelayNPC_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerChallengeRelayNPC_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeRelayNPC(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerChallengeRelayNPC)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerChallengeRelayNPC_Implementation(Z_Param_NPCId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerChallengeRelayNPC **********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerCompleteProfileSnapshot **
struct DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms
{
	FGuid TransferId;
	int64 Revision;
	bool bAccepted;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerCompleteProfileSnapshot = FName(TEXT("ServerCompleteProfileSnapshot"));
void ADigimonVenomNXTPlayerController::ServerCompleteProfileSnapshot(FGuid TransferId, int64 Revision, bool bAccepted)
{
	DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms Parms;
	Parms.TransferId=TransferId;
	Parms.Revision=Revision;
	Parms.bAccepted=bAccepted ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerCompleteProfileSnapshot);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerCompleteProfileSnapshot_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCompleteProfileSnapshot constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_TransferId;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Revision;
	static void NewProp_bAccepted_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms*)Obj)->bAccepted = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAccepted;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerCompleteProfileSnapshot constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerCompleteProfileSnapshot Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TransferId = { "TransferId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms, TransferId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms, Revision), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAccepted = { "bAccepted", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms), &UHT_STATICS::NewProp_bAccepted_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TransferId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAccepted,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerCompleteProfileSnapshot Property Definitions **********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerCompleteProfileSnapshot", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerCompleteProfileSnapshot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerCompleteProfileSnapshot(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerCompleteProfileSnapshot)
{
	P_GET_STRUCT(FGuid,Z_Param_TransferId);
	P_GET_PROPERTY(FInt64Property,Z_Param_Revision);
	P_GET_UBOOL(Z_Param_bAccepted);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCompleteProfileSnapshot_Implementation(Z_Param_TransferId,Z_Param_Revision,Z_Param_bAccepted);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerCompleteProfileSnapshot ****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerEnterChronicles **********
static FName NAME_ADigimonVenomNXTPlayerController_ServerEnterChronicles = FName(TEXT("ServerEnterChronicles"));
void ADigimonVenomNXTPlayerController::ServerEnterChronicles()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerEnterChronicles);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterChronicles_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerEnterChronicles constinit property declarations *****************
// ********** End Function ServerEnterChronicles constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerEnterChronicles", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterChronicles(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerEnterChronicles)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerEnterChronicles_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerEnterChronicles ************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerEnterDigiFarm ************
static FName NAME_ADigimonVenomNXTPlayerController_ServerEnterDigiFarm = FName(TEXT("ServerEnterDigiFarm"));
void ADigimonVenomNXTPlayerController::ServerEnterDigiFarm()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerEnterDigiFarm);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterDigiFarm_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerEnterDigiFarm constinit property declarations *******************
// ********** End Function ServerEnterDigiFarm constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerEnterDigiFarm", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterDigiFarm(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerEnterDigiFarm)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerEnterDigiFarm_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerEnterDigiFarm **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerEnterGhostLine ***********
static FName NAME_ADigimonVenomNXTPlayerController_ServerEnterGhostLine = FName(TEXT("ServerEnterGhostLine"));
void ADigimonVenomNXTPlayerController::ServerEnterGhostLine()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerEnterGhostLine);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterGhostLine_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerEnterGhostLine constinit property declarations ******************
// ********** End Function ServerEnterGhostLine constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerEnterGhostLine", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterGhostLine(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerEnterGhostLine)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerEnterGhostLine_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerEnterGhostLine *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerEnterRelay ***************
static FName NAME_ADigimonVenomNXTPlayerController_ServerEnterRelay = FName(TEXT("ServerEnterRelay"));
void ADigimonVenomNXTPlayerController::ServerEnterRelay()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerEnterRelay);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterRelay_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerEnterRelay constinit property declarations **********************
// ********** End Function ServerEnterRelay constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerEnterRelay", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterRelay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerEnterRelay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerEnterRelay_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerEnterRelay *****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerInteractRelayNPC *********
struct DigimonVenomNXTPlayerController_eventServerInteractRelayNPC_Parms
{
	FName NPCId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerInteractRelayNPC = FName(TEXT("ServerInteractRelayNPC"));
void ADigimonVenomNXTPlayerController::ServerInteractRelayNPC(FName NPCId)
{
	DigimonVenomNXTPlayerController_eventServerInteractRelayNPC_Parms Parms;
	Parms.NPCId=NPCId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerInteractRelayNPC);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerInteractRelayNPC_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerInteractRelayNPC constinit property declarations ****************
	static const UECodeGen_Private::FNamePropertyParams NewProp_NPCId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerInteractRelayNPC constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerInteractRelayNPC Property Definitions ***************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NPCId = { "NPCId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerInteractRelayNPC_Parms, NPCId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerInteractRelayNPC Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerInteractRelayNPC", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerInteractRelayNPC_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerInteractRelayNPC_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerInteractRelayNPC(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerInteractRelayNPC)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_NPCId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerInteractRelayNPC_Implementation(Z_Param_NPCId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerInteractRelayNPC ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerLeaveDigiFarm ************
static FName NAME_ADigimonVenomNXTPlayerController_ServerLeaveDigiFarm = FName(TEXT("ServerLeaveDigiFarm"));
void ADigimonVenomNXTPlayerController::ServerLeaveDigiFarm()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerLeaveDigiFarm);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveDigiFarm_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|DigiFarm" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerLeaveDigiFarm constinit property declarations *******************
// ********** End Function ServerLeaveDigiFarm constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerLeaveDigiFarm", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveDigiFarm(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerLeaveDigiFarm)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerLeaveDigiFarm_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerLeaveDigiFarm **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerLeaveFinishedBattle ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerLeaveFinishedBattle = FName(TEXT("ServerLeaveFinishedBattle"));
void ADigimonVenomNXTPlayerController::ServerLeaveFinishedBattle()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerLeaveFinishedBattle);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveFinishedBattle_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerLeaveFinishedBattle constinit property declarations *************
// ********** End Function ServerLeaveFinishedBattle constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerLeaveFinishedBattle", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveFinishedBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerLeaveFinishedBattle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerLeaveFinishedBattle_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerLeaveFinishedBattle ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerLeaveRelay ***************
static FName NAME_ADigimonVenomNXTPlayerController_ServerLeaveRelay = FName(TEXT("ServerLeaveRelay"));
void ADigimonVenomNXTPlayerController::ServerLeaveRelay()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerLeaveRelay);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveRelay_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerLeaveRelay constinit property declarations **********************
// ********** End Function ServerLeaveRelay constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerLeaveRelay", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveRelay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerLeaveRelay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerLeaveRelay_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerLeaveRelay *****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRelayFastTravel **********
struct DigimonVenomNXTPlayerController_eventServerRelayFastTravel_Parms
{
	int32 MapId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerRelayFastTravel = FName(TEXT("ServerRelayFastTravel"));
void ADigimonVenomNXTPlayerController::ServerRelayFastTravel(int32 MapId)
{
	DigimonVenomNXTPlayerController_eventServerRelayFastTravel_Parms Parms;
	Parms.MapId=MapId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRelayFastTravel);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRelayFastTravel_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRelayFastTravel constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRelayFastTravel constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRelayFastTravel Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerRelayFastTravel_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRelayFastTravel Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRelayFastTravel", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerRelayFastTravel_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerRelayFastTravel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRelayFastTravel(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRelayFastTravel)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRelayFastTravel_Implementation(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRelayFastTravel ************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestAIRivalActivity ***
struct DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms
{
	int32 PageIndex;
	int32 PageSize;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestAIRivalActivity = FName(TEXT("ServerRequestAIRivalActivity"));
void ADigimonVenomNXTPlayerController::ServerRequestAIRivalActivity(int32 PageIndex, int32 PageSize)
{
	DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms Parms;
	Parms.PageIndex=PageIndex;
	Parms.PageSize=PageSize;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestAIRivalActivity);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestAIRivalActivity_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|AI Rivals" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestAIRivalActivity constinit property declarations **********
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageSize;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRequestAIRivalActivity constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRequestAIRivalActivity Property Definitions *********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageIndex = { "PageIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms, PageIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageSize = { "PageSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms, PageSize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageSize,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRequestAIRivalActivity Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestAIRivalActivity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerRequestAIRivalActivity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestAIRivalActivity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestAIRivalActivity)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_PageIndex);
	P_GET_PROPERTY(FIntProperty,Z_Param_PageSize);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestAIRivalActivity_Implementation(Z_Param_PageIndex,Z_Param_PageSize);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestAIRivalActivity *****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestLogout ************
struct DigimonVenomNXTPlayerController_eventServerRequestLogout_Parms
{
	FGuid RequestId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestLogout = FName(TEXT("ServerRequestLogout"));
void ADigimonVenomNXTPlayerController::ServerRequestLogout(FGuid RequestId)
{
	DigimonVenomNXTPlayerController_eventServerRequestLogout_Parms Parms;
	Parms.RequestId=RequestId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestLogout);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestLogout_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestLogout constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RequestId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRequestLogout constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRequestLogout Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RequestId = { "RequestId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerRequestLogout_Parms, RequestId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RequestId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRequestLogout Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestLogout", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerRequestLogout_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00A20CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerRequestLogout_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestLogout(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestLogout)
{
	P_GET_STRUCT(FGuid,Z_Param_RequestId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestLogout_Implementation(Z_Param_RequestId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestLogout **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestProfileSynchronization 
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestProfileSynchronization = FName(TEXT("ServerRequestProfileSynchronization"));
void ADigimonVenomNXTPlayerController::ServerRequestProfileSynchronization()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestProfileSynchronization);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestProfileSynchronization_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestProfileSynchronization constinit property declarations ***
// ********** End Function ServerRequestProfileSynchronization constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestProfileSynchronization", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestProfileSynchronization(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestProfileSynchronization)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestProfileSynchronization_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestProfileSynchronization 

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestRankedStatus ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestRankedStatus = FName(TEXT("ServerRequestRankedStatus"));
void ADigimonVenomNXTPlayerController::ServerRequestRankedStatus()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestRankedStatus);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestRankedStatus_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestRankedStatus constinit property declarations *************
// ********** End Function ServerRequestRankedStatus constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestRankedStatus", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestRankedStatus(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestRankedStatus)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestRankedStatus_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestRankedStatus ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestSave **************
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestSave = FName(TEXT("ServerRequestSave"));
void ADigimonVenomNXTPlayerController::ServerRequestSave()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestSave);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSave_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Persistence" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestSave constinit property declarations *********************
// ********** End Function ServerRequestSave constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestSave", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSave(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestSave)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestSave_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestSave ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestSeasonArchive *****
struct DigimonVenomNXTPlayerController_eventServerRequestSeasonArchive_Parms
{
	int32 PageIndex;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestSeasonArchive = FName(TEXT("ServerRequestSeasonArchive"));
void ADigimonVenomNXTPlayerController::ServerRequestSeasonArchive(int32 PageIndex)
{
	DigimonVenomNXTPlayerController_eventServerRequestSeasonArchive_Parms Parms;
	Parms.PageIndex=PageIndex;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestSeasonArchive);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonArchive_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestSeasonArchive constinit property declarations ************
	static const UECodeGen_Private::FIntPropertyParams NewProp_PageIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerRequestSeasonArchive constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerRequestSeasonArchive Property Definitions ***********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PageIndex = { "PageIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerRequestSeasonArchive_Parms, PageIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageIndex,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerRequestSeasonArchive Property Definitions *************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestSeasonArchive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerRequestSeasonArchive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerRequestSeasonArchive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonArchive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestSeasonArchive)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_PageIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestSeasonArchive_Implementation(Z_Param_PageIndex);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestSeasonArchive *******

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRequestSeasonStatus ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerRequestSeasonStatus = FName(TEXT("ServerRequestSeasonStatus"));
void ADigimonVenomNXTPlayerController::ServerRequestSeasonStatus()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRequestSeasonStatus);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonStatus_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRequestSeasonStatus constinit property declarations *************
// ********** End Function ServerRequestSeasonStatus constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRequestSeasonStatus", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonStatus(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRequestSeasonStatus)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRequestSeasonStatus_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRequestSeasonStatus ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerResumeRelayBattle ********
static FName NAME_ADigimonVenomNXTPlayerController_ServerResumeRelayBattle = FName(TEXT("ServerResumeRelayBattle"));
void ADigimonVenomNXTPlayerController::ServerResumeRelayBattle()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerResumeRelayBattle);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerResumeRelayBattle_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerResumeRelayBattle constinit property declarations ***************
// ********** End Function ServerResumeRelayBattle constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerResumeRelayBattle", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerResumeRelayBattle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerResumeRelayBattle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerResumeRelayBattle_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerResumeRelayBattle **********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerRunRankedQuickMatch ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerRunRankedQuickMatch = FName(TEXT("ServerRunRankedQuickMatch"));
void ADigimonVenomNXTPlayerController::ServerRunRankedQuickMatch()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerRunRankedQuickMatch);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRunRankedQuickMatch_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerRunRankedQuickMatch constinit property declarations *************
// ********** End Function ServerRunRankedQuickMatch constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerRunRankedQuickMatch", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRunRankedQuickMatch(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerRunRankedQuickMatch)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerRunRankedQuickMatch_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerRunRankedQuickMatch ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerSaveRankedDefender *******
static FName NAME_ADigimonVenomNXTPlayerController_ServerSaveRankedDefender = FName(TEXT("ServerSaveRankedDefender"));
void ADigimonVenomNXTPlayerController::ServerSaveRankedDefender()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerSaveRankedDefender);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveRankedDefender_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Ranked" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSaveRankedDefender constinit property declarations **************
// ********** End Function ServerSaveRankedDefender constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerSaveRankedDefender", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveRankedDefender(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerSaveRankedDefender)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSaveRankedDefender_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerSaveRankedDefender *********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerSaveSeasonAndReturn ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerSaveSeasonAndReturn = FName(TEXT("ServerSaveSeasonAndReturn"));
void ADigimonVenomNXTPlayerController::ServerSaveSeasonAndReturn()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerSaveSeasonAndReturn);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveSeasonAndReturn_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSaveSeasonAndReturn constinit property declarations *************
// ********** End Function ServerSaveSeasonAndReturn constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerSaveSeasonAndReturn", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveSeasonAndReturn(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerSaveSeasonAndReturn)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSaveSeasonAndReturn_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerSaveSeasonAndReturn ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerSendLocalChat ************
struct DigimonVenomNXTPlayerController_eventServerSendLocalChat_Parms
{
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerSendLocalChat = FName(TEXT("ServerSendLocalChat"));
void ADigimonVenomNXTPlayerController::ServerSendLocalChat(const FString& Message)
{
	DigimonVenomNXTPlayerController_eventServerSendLocalChat_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerSendLocalChat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendLocalChat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSendLocalChat constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSendLocalChat constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSendLocalChat Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerSendLocalChat_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSendLocalChat Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerSendLocalChat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerSendLocalChat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerSendLocalChat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendLocalChat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerSendLocalChat)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSendLocalChat_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerSendLocalChat **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerSendWorldChat ************
struct DigimonVenomNXTPlayerController_eventServerSendWorldChat_Parms
{
	FString Message;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerSendWorldChat = FName(TEXT("ServerSendWorldChat"));
void ADigimonVenomNXTPlayerController::ServerSendWorldChat(const FString& Message)
{
	DigimonVenomNXTPlayerController_eventServerSendWorldChat_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerSendWorldChat);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendWorldChat_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Canonical WORLD entry point. The legacy LocalChat RPC forwards to the same server path. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Canonical WORLD entry point. The legacy LocalChat RPC forwards to the same server path." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSendWorldChat constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSendWorldChat constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSendWorldChat Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerSendWorldChat_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSendWorldChat Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerSendWorldChat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerSendWorldChat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerSendWorldChat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendWorldChat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerSendWorldChat)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSendWorldChat_Implementation(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerSendWorldChat **************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerStartFinalStoryBoss ******
static FName NAME_ADigimonVenomNXTPlayerController_ServerStartFinalStoryBoss = FName(TEXT("ServerStartFinalStoryBoss"));
void ADigimonVenomNXTPlayerController::ServerStartFinalStoryBoss()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerStartFinalStoryBoss);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartFinalStoryBoss_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerStartFinalStoryBoss constinit property declarations *************
// ********** End Function ServerStartFinalStoryBoss constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerStartFinalStoryBoss", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartFinalStoryBoss(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerStartFinalStoryBoss)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerStartFinalStoryBoss_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerStartFinalStoryBoss ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerStartRelayFieldTraining **
static FName NAME_ADigimonVenomNXTPlayerController_ServerStartRelayFieldTraining = FName(TEXT("ServerStartRelayFieldTraining"));
void ADigimonVenomNXTPlayerController::ServerStartRelayFieldTraining()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerStartRelayFieldTraining);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartRelayFieldTraining_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerStartRelayFieldTraining constinit property declarations *********
// ********** End Function ServerStartRelayFieldTraining constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerStartRelayFieldTraining", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartRelayFieldTraining(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerStartRelayFieldTraining)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerStartRelayFieldTraining_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerStartRelayFieldTraining ****

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerStartSeasonMatch *********
static FName NAME_ADigimonVenomNXTPlayerController_ServerStartSeasonMatch = FName(TEXT("ServerStartSeasonMatch"));
void ADigimonVenomNXTPlayerController::ServerStartSeasonMatch()
{
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerStartSeasonMatch);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartSeasonMatch_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Season" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerStartSeasonMatch constinit property declarations ****************
// ********** End Function ServerStartSeasonMatch constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerStartSeasonMatch", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartSeasonMatch(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerStartSeasonMatch)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerStartSeasonMatch_Implementation();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerStartSeasonMatch ***********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerStartStoryBoss ***********
struct DigimonVenomNXTPlayerController_eventServerStartStoryBoss_Parms
{
	int32 Chapter;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerStartStoryBoss = FName(TEXT("ServerStartStoryBoss"));
void ADigimonVenomNXTPlayerController::ServerStartStoryBoss(int32 Chapter)
{
	DigimonVenomNXTPlayerController_eventServerStartStoryBoss_Parms Parms;
	Parms.Chapter=Chapter;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerStartStoryBoss);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartStoryBoss_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Story" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerStartStoryBoss constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Chapter;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerStartStoryBoss constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerStartStoryBoss Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Chapter = { "Chapter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerStartStoryBoss_Parms, Chapter), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Chapter,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerStartStoryBoss Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerStartStoryBoss", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerStartStoryBoss_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerStartStoryBoss_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartStoryBoss(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerStartStoryBoss)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Chapter);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerStartStoryBoss_Implementation(Z_Param_Chapter);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerStartStoryBoss *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerSubmitBattleCommand ******
struct DigimonVenomNXTPlayerController_eventServerSubmitBattleCommand_Parms
{
	FDigimonBattleCommand Command;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerSubmitBattleCommand = FName(TEXT("ServerSubmitBattleCommand"));
void ADigimonVenomNXTPlayerController::ServerSubmitBattleCommand(FDigimonBattleCommand const& Command)
{
	DigimonVenomNXTPlayerController_eventServerSubmitBattleCommand_Parms Parms;
	Parms.Command=Command;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerSubmitBattleCommand);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSubmitBattleCommand_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Command_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSubmitBattleCommand constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Command;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSubmitBattleCommand constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSubmitBattleCommand Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Command = { "Command", nullptr, (EPropertyFlags)0x0010000008000082, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerSubmitBattleCommand_Parms, Command), Z_Construct_UScriptStruct_FDigimonBattleCommand, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Command_MetaData), NewProp_Command_MetaData) }; // 4660d03fbac20661821fdbde3b0565b1ae9a2d3b
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Command,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSubmitBattleCommand Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerSubmitBattleCommand", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerSubmitBattleCommand_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerSubmitBattleCommand_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSubmitBattleCommand(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerSubmitBattleCommand)
{
	P_GET_STRUCT(FDigimonBattleCommand,Z_Param_Command);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSubmitBattleCommand_Implementation(Z_Param_Command);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerSubmitBattleCommand ********

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerTravelRelayMap ***********
struct DigimonVenomNXTPlayerController_eventServerTravelRelayMap_Parms
{
	int32 MapId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerTravelRelayMap = FName(TEXT("ServerTravelRelayMap"));
void ADigimonVenomNXTPlayerController::ServerTravelRelayMap(int32 MapId)
{
	DigimonVenomNXTPlayerController_eventServerTravelRelayMap_Parms Parms;
	Parms.MapId=MapId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerTravelRelayMap);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelRelayMap_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerTravelRelayMap constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerTravelRelayMap constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerTravelRelayMap Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerTravelRelayMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerTravelRelayMap Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerTravelRelayMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerTravelRelayMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerTravelRelayMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelRelayMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerTravelRelayMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerTravelRelayMap_Implementation(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerTravelRelayMap *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ServerTravelToMap **************
struct DigimonVenomNXTPlayerController_eventServerTravelToMap_Parms
{
	int32 MapId;
};
static FName NAME_ADigimonVenomNXTPlayerController_ServerTravelToMap = FName(TEXT("ServerTravelToMap"));
void ADigimonVenomNXTPlayerController::ServerTravelToMap(int32 MapId)
{
	DigimonVenomNXTPlayerController_eventServerTravelToMap_Parms Parms;
	Parms.MapId=MapId;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTPlayerController_ServerTravelToMap);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelToMap_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|World" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerTravelToMap constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MapId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerTravelToMap constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerTravelToMap Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MapId = { "MapId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTPlayerController_eventServerTravelToMap_Parms, MapId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MapId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerTravelToMap Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ServerTravelToMap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTPlayerController_eventServerTravelToMap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTPlayerController_eventServerTravelToMap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelToMap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execServerTravelToMap)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_MapId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerTravelToMap_Implementation(Z_Param_MapId);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ServerTravelToMap ****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function SetFieldMenuOpen ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetFieldMenuOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventSetFieldMenuOpen_Parms
	{
		bool bOpen;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Local field menu state. Closed means the world owns the screen and movement is active. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local field menu state. Closed means the world owns the screen and movement is active." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetFieldMenuOpen constinit property declarations **********************
	static void NewProp_bOpen_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventSetFieldMenuOpen_Parms*)Obj)->bOpen = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpen;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetFieldMenuOpen constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetFieldMenuOpen Property Definitions *********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOpen = { "bOpen", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventSetFieldMenuOpen_Parms), &UHT_STATICS::NewProp_bOpen_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOpen,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetFieldMenuOpen Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "SetFieldMenuOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventSetFieldMenuOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventSetFieldMenuOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetFieldMenuOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execSetFieldMenuOpen)
{
	P_GET_UBOOL(Z_Param_bOpen);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetFieldMenuOpen(Z_Param_bOpen);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function SetFieldMenuOpen *****************

// ********** Begin Class ADigimonVenomNXTPlayerController Function SetRelayDialogueOpen ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetRelayDialogueOpen_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTPlayerController_eventSetRelayDialogueOpen_Parms
	{
		bool bOpen;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Relay" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetRelayDialogueOpen constinit property declarations ******************
	static void NewProp_bOpen_SetBit(void* Obj)
	{
		((DigimonVenomNXTPlayerController_eventSetRelayDialogueOpen_Parms*)Obj)->bOpen = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpen;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRelayDialogueOpen constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRelayDialogueOpen Property Definitions *****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOpen = { "bOpen", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DigimonVenomNXTPlayerController_eventSetRelayDialogueOpen_Parms), &UHT_STATICS::NewProp_bOpen_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOpen,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRelayDialogueOpen Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "SetRelayDialogueOpen", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTPlayerController_eventSetRelayDialogueOpen_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTPlayerController_eventSetRelayDialogueOpen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetRelayDialogueOpen(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execSetRelayDialogueOpen)
{
	P_GET_UBOOL(Z_Param_bOpen);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRelayDialogueOpen(Z_Param_bOpen);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function SetRelayDialogueOpen *************

// ********** Begin Class ADigimonVenomNXTPlayerController Function ToggleFieldMenu ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ToggleFieldMenu_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleFieldMenu constinit property declarations ***********************
// ********** End Function ToggleFieldMenu constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTPlayerController, nullptr, "ToggleFieldMenu", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ToggleFieldMenu(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTPlayerController::execToggleFieldMenu)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleFieldMenu();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTPlayerController Function ToggleFieldMenu ******************

// ********** Begin Class ADigimonVenomNXTPlayerController *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTPlayerController_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Owner RPC surface for Digimon Venom NXT. UI and Blueprint code send intent through this controller;\n * authoritative gameplay mutations are performed on the server.\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "DigimonVenomNXTPlayerController.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Owner RPC surface for Digimon Venom NXT. UI and Blueprint code send intent through this controller;\nauthoritative gameplay mutations are performed on the server." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SocialComponent_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Community" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TradeComponent_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Community" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnrankedComponent_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Community" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentBattle_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAccountAuthenticated_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Accounts" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnClientMessage_MetaData[] = {
		{ "Category", "Digimon Venom NXT|UI" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnChatReceived_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldChatHistory_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Chat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Session-local history survives menu changes and messages arriving before HUD creation. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Session-local history survives menu changes and messages arriving before HUD creation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnCurrentBattleChanged_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Battle" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProfileSyncWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastQueuedOwnerProfile_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PendingOwnerProfile_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GameHUDWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BattleWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalMapRenderer_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DigiFarmScene_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelayScene_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RelaySession_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarmSession_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTPlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTPlayerController constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SocialComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TradeComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UnrankedComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentBattle;
	static void NewProp_bAccountAuthenticated_SetBit(void* Obj)
	{
		((ADigimonVenomNXTPlayerController*)Obj)->bAccountAuthenticated = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAccountAuthenticated;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnClientMessage;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnChatReceived;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldChatHistory_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_WorldChatHistory;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCurrentBattleChanged;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProfileSyncWidget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LastQueuedOwnerProfile;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PendingOwnerProfile;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GameHUDWidget;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BattleWidget;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LocalMapRenderer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DigiFarmScene;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RelayScene;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RelaySession;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FarmSession;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTPlayerController constinit property declarations ***********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CanUseRelayPortal"), .Pointer = &ADigimonVenomNXTPlayerController::execCanUseRelayPortal },
		{ .NameUTF8 = UTF8TEXT("ClientAccountAuthenticationResult"), .Pointer = &ADigimonVenomNXTPlayerController::execClientAccountAuthenticationResult },
		{ .NameUTF8 = UTF8TEXT("ClientBeginProfileSnapshot"), .Pointer = &ADigimonVenomNXTPlayerController::execClientBeginProfileSnapshot },
		{ .NameUTF8 = UTF8TEXT("ClientHostSessionClosed"), .Pointer = &ADigimonVenomNXTPlayerController::execClientHostSessionClosed },
		{ .NameUTF8 = UTF8TEXT("ClientLogoutResult"), .Pointer = &ADigimonVenomNXTPlayerController::execClientLogoutResult },
		{ .NameUTF8 = UTF8TEXT("ClientPlayAudioCue"), .Pointer = &ADigimonVenomNXTPlayerController::execClientPlayAudioCue },
		{ .NameUTF8 = UTF8TEXT("ClientPlayExplorationMusic"), .Pointer = &ADigimonVenomNXTPlayerController::execClientPlayExplorationMusic },
		{ .NameUTF8 = UTF8TEXT("ClientProfileSnapshotChunk"), .Pointer = &ADigimonVenomNXTPlayerController::execClientProfileSnapshotChunk },
		{ .NameUTF8 = UTF8TEXT("ClientProfileSynchronizationFailed"), .Pointer = &ADigimonVenomNXTPlayerController::execClientProfileSynchronizationFailed },
		{ .NameUTF8 = UTF8TEXT("ClientReceiveAIRivalActivity"), .Pointer = &ADigimonVenomNXTPlayerController::execClientReceiveAIRivalActivity },
		{ .NameUTF8 = UTF8TEXT("ClientReceiveLocalChat"), .Pointer = &ADigimonVenomNXTPlayerController::execClientReceiveLocalChat },
		{ .NameUTF8 = UTF8TEXT("ClientReceiveSeasonArchive"), .Pointer = &ADigimonVenomNXTPlayerController::execClientReceiveSeasonArchive },
		{ .NameUTF8 = UTF8TEXT("ClientReturnFromSeason"), .Pointer = &ADigimonVenomNXTPlayerController::execClientReturnFromSeason },
		{ .NameUTF8 = UTF8TEXT("ClientReturnToSeason"), .Pointer = &ADigimonVenomNXTPlayerController::execClientReturnToSeason },
		{ .NameUTF8 = UTF8TEXT("ClientSetActiveMapPresentation"), .Pointer = &ADigimonVenomNXTPlayerController::execClientSetActiveMapPresentation },
		{ .NameUTF8 = UTF8TEXT("ClientSetDigiFarmPresentation"), .Pointer = &ADigimonVenomNXTPlayerController::execClientSetDigiFarmPresentation },
		{ .NameUTF8 = UTF8TEXT("ClientSetRelayPresentation"), .Pointer = &ADigimonVenomNXTPlayerController::execClientSetRelayPresentation },
		{ .NameUTF8 = UTF8TEXT("ClientShowMessage"), .Pointer = &ADigimonVenomNXTPlayerController::execClientShowMessage },
		{ .NameUTF8 = UTF8TEXT("ClientShowRelayDialogue"), .Pointer = &ADigimonVenomNXTPlayerController::execClientShowRelayDialogue },
		{ .NameUTF8 = UTF8TEXT("GetDigiFarmOrigin"), .Pointer = &ADigimonVenomNXTPlayerController::execGetDigiFarmOrigin },
		{ .NameUTF8 = UTF8TEXT("GetDigiFarmScene"), .Pointer = &ADigimonVenomNXTPlayerController::execGetDigiFarmScene },
		{ .NameUTF8 = UTF8TEXT("GetNativeBattleWidget"), .Pointer = &ADigimonVenomNXTPlayerController::execGetNativeBattleWidget },
		{ .NameUTF8 = UTF8TEXT("GetNativeHUDWidget"), .Pointer = &ADigimonVenomNXTPlayerController::execGetNativeHUDWidget },
		{ .NameUTF8 = UTF8TEXT("GetNearestRelayNPC"), .Pointer = &ADigimonVenomNXTPlayerController::execGetNearestRelayNPC },
		{ .NameUTF8 = UTF8TEXT("GetRelayMapId"), .Pointer = &ADigimonVenomNXTPlayerController::execGetRelayMapId },
		{ .NameUTF8 = UTF8TEXT("GetRelayNPCLocation"), .Pointer = &ADigimonVenomNXTPlayerController::execGetRelayNPCLocation },
		{ .NameUTF8 = UTF8TEXT("GetRelayOrigin"), .Pointer = &ADigimonVenomNXTPlayerController::execGetRelayOrigin },
		{ .NameUTF8 = UTF8TEXT("GetRelayPortalLocation"), .Pointer = &ADigimonVenomNXTPlayerController::execGetRelayPortalLocation },
		{ .NameUTF8 = UTF8TEXT("GetRelayPortalTarget"), .Pointer = &ADigimonVenomNXTPlayerController::execGetRelayPortalTarget },
		{ .NameUTF8 = UTF8TEXT("GetStoryCampaign"), .Pointer = &ADigimonVenomNXTPlayerController::execGetStoryCampaign },
		{ .NameUTF8 = UTF8TEXT("IsAccountAuthenticated"), .Pointer = &ADigimonVenomNXTPlayerController::execIsAccountAuthenticated },
		{ .NameUTF8 = UTF8TEXT("IsFieldInputBlocked"), .Pointer = &ADigimonVenomNXTPlayerController::execIsFieldInputBlocked },
		{ .NameUTF8 = UTF8TEXT("IsFieldMenuOpen"), .Pointer = &ADigimonVenomNXTPlayerController::execIsFieldMenuOpen },
		{ .NameUTF8 = UTF8TEXT("IsInChronicles"), .Pointer = &ADigimonVenomNXTPlayerController::execIsInChronicles },
		{ .NameUTF8 = UTF8TEXT("IsInDigiFarm"), .Pointer = &ADigimonVenomNXTPlayerController::execIsInDigiFarm },
		{ .NameUTF8 = UTF8TEXT("IsInGhostLine"), .Pointer = &ADigimonVenomNXTPlayerController::execIsInGhostLine },
		{ .NameUTF8 = UTF8TEXT("IsInRelay"), .Pointer = &ADigimonVenomNXTPlayerController::execIsInRelay },
		{ .NameUTF8 = UTF8TEXT("IsInRelayCampaign"), .Pointer = &ADigimonVenomNXTPlayerController::execIsInRelayCampaign },
		{ .NameUTF8 = UTF8TEXT("IsLogoutPending"), .Pointer = &ADigimonVenomNXTPlayerController::execIsLogoutPending },
		{ .NameUTF8 = UTF8TEXT("IsOwnerProfileReady"), .Pointer = &ADigimonVenomNXTPlayerController::execIsOwnerProfileReady },
		{ .NameUTF8 = UTF8TEXT("OnRep_CurrentBattle"), .Pointer = &ADigimonVenomNXTPlayerController::execOnRep_CurrentBattle },
		{ .NameUTF8 = UTF8TEXT("OnRep_DigiFarmSession"), .Pointer = &ADigimonVenomNXTPlayerController::execOnRep_DigiFarmSession },
		{ .NameUTF8 = UTF8TEXT("OnRep_RelaySession"), .Pointer = &ADigimonVenomNXTPlayerController::execOnRep_RelaySession },
		{ .NameUTF8 = UTF8TEXT("RequestLogout"), .Pointer = &ADigimonVenomNXTPlayerController::execRequestLogout },
		{ .NameUTF8 = UTF8TEXT("RetryProfileSynchronization"), .Pointer = &ADigimonVenomNXTPlayerController::execRetryProfileSynchronization },
		{ .NameUTF8 = UTF8TEXT("ServerAcknowledgeBattlePresentation"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAcknowledgeBattlePresentation },
		{ .NameUTF8 = UTF8TEXT("ServerAcknowledgeProfileChunk"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAcknowledgeProfileChunk },
		{ .NameUTF8 = UTF8TEXT("ServerAdvanceChroniclesQuest"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAdvanceChroniclesQuest },
		{ .NameUTF8 = UTF8TEXT("ServerAdvanceGhostLineQuest"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAdvanceGhostLineQuest },
		{ .NameUTF8 = UTF8TEXT("ServerAdvanceSeasonWeek"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAdvanceSeasonWeek },
		{ .NameUTF8 = UTF8TEXT("ServerAuthenticateAccount"), .Pointer = &ADigimonVenomNXTPlayerController::execServerAuthenticateAccount },
		{ .NameUTF8 = UTF8TEXT("ServerBeginSecondStory"), .Pointer = &ADigimonVenomNXTPlayerController::execServerBeginSecondStory },
		{ .NameUTF8 = UTF8TEXT("ServerChallengeAIRival"), .Pointer = &ADigimonVenomNXTPlayerController::execServerChallengeAIRival },
		{ .NameUTF8 = UTF8TEXT("ServerChallengeRelayNPC"), .Pointer = &ADigimonVenomNXTPlayerController::execServerChallengeRelayNPC },
		{ .NameUTF8 = UTF8TEXT("ServerCompleteProfileSnapshot"), .Pointer = &ADigimonVenomNXTPlayerController::execServerCompleteProfileSnapshot },
		{ .NameUTF8 = UTF8TEXT("ServerEnterChronicles"), .Pointer = &ADigimonVenomNXTPlayerController::execServerEnterChronicles },
		{ .NameUTF8 = UTF8TEXT("ServerEnterDigiFarm"), .Pointer = &ADigimonVenomNXTPlayerController::execServerEnterDigiFarm },
		{ .NameUTF8 = UTF8TEXT("ServerEnterGhostLine"), .Pointer = &ADigimonVenomNXTPlayerController::execServerEnterGhostLine },
		{ .NameUTF8 = UTF8TEXT("ServerEnterRelay"), .Pointer = &ADigimonVenomNXTPlayerController::execServerEnterRelay },
		{ .NameUTF8 = UTF8TEXT("ServerInteractRelayNPC"), .Pointer = &ADigimonVenomNXTPlayerController::execServerInteractRelayNPC },
		{ .NameUTF8 = UTF8TEXT("ServerLeaveDigiFarm"), .Pointer = &ADigimonVenomNXTPlayerController::execServerLeaveDigiFarm },
		{ .NameUTF8 = UTF8TEXT("ServerLeaveFinishedBattle"), .Pointer = &ADigimonVenomNXTPlayerController::execServerLeaveFinishedBattle },
		{ .NameUTF8 = UTF8TEXT("ServerLeaveRelay"), .Pointer = &ADigimonVenomNXTPlayerController::execServerLeaveRelay },
		{ .NameUTF8 = UTF8TEXT("ServerRelayFastTravel"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRelayFastTravel },
		{ .NameUTF8 = UTF8TEXT("ServerRequestAIRivalActivity"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestAIRivalActivity },
		{ .NameUTF8 = UTF8TEXT("ServerRequestLogout"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestLogout },
		{ .NameUTF8 = UTF8TEXT("ServerRequestProfileSynchronization"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestProfileSynchronization },
		{ .NameUTF8 = UTF8TEXT("ServerRequestRankedStatus"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestRankedStatus },
		{ .NameUTF8 = UTF8TEXT("ServerRequestSave"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestSave },
		{ .NameUTF8 = UTF8TEXT("ServerRequestSeasonArchive"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestSeasonArchive },
		{ .NameUTF8 = UTF8TEXT("ServerRequestSeasonStatus"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRequestSeasonStatus },
		{ .NameUTF8 = UTF8TEXT("ServerResumeRelayBattle"), .Pointer = &ADigimonVenomNXTPlayerController::execServerResumeRelayBattle },
		{ .NameUTF8 = UTF8TEXT("ServerRunRankedQuickMatch"), .Pointer = &ADigimonVenomNXTPlayerController::execServerRunRankedQuickMatch },
		{ .NameUTF8 = UTF8TEXT("ServerSaveRankedDefender"), .Pointer = &ADigimonVenomNXTPlayerController::execServerSaveRankedDefender },
		{ .NameUTF8 = UTF8TEXT("ServerSaveSeasonAndReturn"), .Pointer = &ADigimonVenomNXTPlayerController::execServerSaveSeasonAndReturn },
		{ .NameUTF8 = UTF8TEXT("ServerSendLocalChat"), .Pointer = &ADigimonVenomNXTPlayerController::execServerSendLocalChat },
		{ .NameUTF8 = UTF8TEXT("ServerSendWorldChat"), .Pointer = &ADigimonVenomNXTPlayerController::execServerSendWorldChat },
		{ .NameUTF8 = UTF8TEXT("ServerStartFinalStoryBoss"), .Pointer = &ADigimonVenomNXTPlayerController::execServerStartFinalStoryBoss },
		{ .NameUTF8 = UTF8TEXT("ServerStartRelayFieldTraining"), .Pointer = &ADigimonVenomNXTPlayerController::execServerStartRelayFieldTraining },
		{ .NameUTF8 = UTF8TEXT("ServerStartSeasonMatch"), .Pointer = &ADigimonVenomNXTPlayerController::execServerStartSeasonMatch },
		{ .NameUTF8 = UTF8TEXT("ServerStartStoryBoss"), .Pointer = &ADigimonVenomNXTPlayerController::execServerStartStoryBoss },
		{ .NameUTF8 = UTF8TEXT("ServerSubmitBattleCommand"), .Pointer = &ADigimonVenomNXTPlayerController::execServerSubmitBattleCommand },
		{ .NameUTF8 = UTF8TEXT("ServerTravelRelayMap"), .Pointer = &ADigimonVenomNXTPlayerController::execServerTravelRelayMap },
		{ .NameUTF8 = UTF8TEXT("ServerTravelToMap"), .Pointer = &ADigimonVenomNXTPlayerController::execServerTravelToMap },
		{ .NameUTF8 = UTF8TEXT("SetFieldMenuOpen"), .Pointer = &ADigimonVenomNXTPlayerController::execSetFieldMenuOpen },
		{ .NameUTF8 = UTF8TEXT("SetRelayDialogueOpen"), .Pointer = &ADigimonVenomNXTPlayerController::execSetRelayDialogueOpen },
		{ .NameUTF8 = UTF8TEXT("ToggleFieldMenu"), .Pointer = &ADigimonVenomNXTPlayerController::execToggleFieldMenu },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_CanUseRelayPortal, "CanUseRelayPortal" }, // c405c46d3730fea442f069e33889e905bbd24e9c
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientAccountAuthenticationResult, "ClientAccountAuthenticationResult" }, // c7b44f4e749f2833c404f461ac51f0115642965e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientBeginProfileSnapshot, "ClientBeginProfileSnapshot" }, // 3d8632c2e1886513a518dfe7c1753775232a2194
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientHostSessionClosed, "ClientHostSessionClosed" }, // 9de4a3dd0faf5e18e6ca6abac2a9f16f977313f2
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientLogoutResult, "ClientLogoutResult" }, // 008ffe018c3671be2ecef0af47b3f413ca364ef8
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayAudioCue, "ClientPlayAudioCue" }, // ecb82ebbe69ce7e092e268f90dabaf881b81e96c
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientPlayExplorationMusic, "ClientPlayExplorationMusic" }, // 4112b7b47d9807d1d2fbd60244918b647a115009
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSnapshotChunk, "ClientProfileSnapshotChunk" }, // e26f01bbc4a6cdf8dc8d05715ae0b56652d845e6
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientProfileSynchronizationFailed, "ClientProfileSynchronizationFailed" }, // 0505b057de9ea129faa5fca9a49722307052ca44
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveAIRivalActivity, "ClientReceiveAIRivalActivity" }, // b6e4e18973cf48d9618e27860330bcd046c321b5
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveLocalChat, "ClientReceiveLocalChat" }, // 71d5714ad47f19a715ff04578725587526db1cd1
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReceiveSeasonArchive, "ClientReceiveSeasonArchive" }, // 0c5e9ff15baf73216a5ca0c63d0d7823784f9233
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnFromSeason, "ClientReturnFromSeason" }, // 64960e69bc805065a5e9bfabdb041d8d78f9c5da
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientReturnToSeason, "ClientReturnToSeason" }, // f09072a9d4376b0de0b47c1d8de3481d0da860a6
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetActiveMapPresentation, "ClientSetActiveMapPresentation" }, // 9aa3a8c044ab49bf433f50668233023dc6bc0d66
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetDigiFarmPresentation, "ClientSetDigiFarmPresentation" }, // 246ab25918eaa806619ca8ad77c506e150e9ff40
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientSetRelayPresentation, "ClientSetRelayPresentation" }, // d4b47cda2affddc9a1c000c4c3d27922227966bd
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowMessage, "ClientShowMessage" }, // c3785fd65fc7876fd405952d4cfd77aaddc6fca0
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ClientShowRelayDialogue, "ClientShowRelayDialogue" }, // 326f0ce0e30ecd4a9aaf6728a582c04b8485708b
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmOrigin, "GetDigiFarmOrigin" }, // 5c32e3fd24793286da2b14a7adb77119195cbf5d
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetDigiFarmScene, "GetDigiFarmScene" }, // 580edb4cf874cb00bd682ca4c3c1ac1b62e8ace2
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeBattleWidget, "GetNativeBattleWidget" }, // 7e1c29c91b676601c1059cd9b8f6f79ee557d841
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNativeHUDWidget, "GetNativeHUDWidget" }, // 4fbb49a74aa282a888f9281086606eb81a9d9890
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetNearestRelayNPC, "GetNearestRelayNPC" }, // b0552c936a5a10a66ffbbc9064f542ee1c944ecf
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayMapId, "GetRelayMapId" }, // 949373abd9b1025c17dad509c7993bc730bd0e9c
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayNPCLocation, "GetRelayNPCLocation" }, // 0798b2edef9919f65ecbfc203ca1528d1055efc8
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayOrigin, "GetRelayOrigin" }, // 6a082d62be8b2404d04f035c8bfd65f33a0bcec5
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalLocation, "GetRelayPortalLocation" }, // a745dbfb7d3d9fa0acd8690be163e7d2bcb87474
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetRelayPortalTarget, "GetRelayPortalTarget" }, // 2e63c3dc74ec44f02d68728ec71bd8530ffd0794
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_GetStoryCampaign, "GetStoryCampaign" }, // b666b1e84d9266ed8b2cd8dfb64edf5b1e548538
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsAccountAuthenticated, "IsAccountAuthenticated" }, // 3d1cc46fa8f36a2cb60106646416b3abe2d3675c
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldInputBlocked, "IsFieldInputBlocked" }, // ed7f99405fb5f7d00c5b73f3d2f86b37e1a1f380
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsFieldMenuOpen, "IsFieldMenuOpen" }, // 8baa629d59b3781758b6ffe011195b29c603b6e4
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInChronicles, "IsInChronicles" }, // 158985ea1c42b41a8e6302b8fd0791aa280c8033
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInDigiFarm, "IsInDigiFarm" }, // a3c67087c74bbc116f7c01fe863ccc5a087a49aa
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInGhostLine, "IsInGhostLine" }, // a6ff8b8d4940c09287104c8df436392d295349e7
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelay, "IsInRelay" }, // 0e7bd7ab8b93aad3e46a0f6af739c2646e385bd0
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsInRelayCampaign, "IsInRelayCampaign" }, // 3bef0e45d6e317fc7ae9306f30a87d7220fe2613
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsLogoutPending, "IsLogoutPending" }, // 77e95d10b9a787c14096e54b434c0de9c3f0feaa
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_IsOwnerProfileReady, "IsOwnerProfileReady" }, // cc0ad67b618207657167d6500486878270974dca
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_CurrentBattle, "OnRep_CurrentBattle" }, // 8936b7a53ba3bab2e18bff1693fef79fa5fdbd49
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_DigiFarmSession, "OnRep_DigiFarmSession" }, // 66545074eafce824ee09adb9af8208fab45a6c2e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_OnRep_RelaySession, "OnRep_RelaySession" }, // 9bc14d20549234b4ca738764577add58499ac64f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RequestLogout, "RequestLogout" }, // dccfaf0bb50b6a92c5912451e20b5f48166a0e38
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_RetryProfileSynchronization, "RetryProfileSynchronization" }, // ff18558dba5988a04039872ac99ccfde96299c9a
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeBattlePresentation, "ServerAcknowledgeBattlePresentation" }, // 2370cfa18fb9c65d7f2f5c5643d35ab667eba208
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAcknowledgeProfileChunk, "ServerAcknowledgeProfileChunk" }, // a21588ba6ec91e5c9c28553620af9213aa539e21
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceChroniclesQuest, "ServerAdvanceChroniclesQuest" }, // a33ddd53c70635a5f69ff2f335dd893b8b95848f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceGhostLineQuest, "ServerAdvanceGhostLineQuest" }, // 3d283aba4ba3e3e3f1a260a572216ae911aa7f24
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAdvanceSeasonWeek, "ServerAdvanceSeasonWeek" }, // fe92fb3f2626368cd31c8da47c65ea28efa9a422
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerAuthenticateAccount, "ServerAuthenticateAccount" }, // 166b71dd867d9b46b52eb05744cb567b058bbc63
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerBeginSecondStory, "ServerBeginSecondStory" }, // 4b48e8f5a717bb855581a3088b20b24f8ca5d933
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeAIRival, "ServerChallengeAIRival" }, // ab47207c9e6f8e1f4fe1aca50c3e064d3460617f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerChallengeRelayNPC, "ServerChallengeRelayNPC" }, // 9048288303805e5bff30d04262a21f9cbd0fb732
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerCompleteProfileSnapshot, "ServerCompleteProfileSnapshot" }, // 9320dc18217f0d1ec7ea0c0706544c6d5e476801
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterChronicles, "ServerEnterChronicles" }, // cb397bc6b56963c41d2fe568a20fd72926dcbad1
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterDigiFarm, "ServerEnterDigiFarm" }, // 3961bc741a0282b6e0082342a1027dff19ff8546
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterGhostLine, "ServerEnterGhostLine" }, // 9b3f33dfd5db778abc0c894f76488de523fc9971
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerEnterRelay, "ServerEnterRelay" }, // ad585fbea8d95aaaa40b78a2acbdce810b058544
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerInteractRelayNPC, "ServerInteractRelayNPC" }, // b5a523e4145393f839749463fc7fc3a1d684eef8
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveDigiFarm, "ServerLeaveDigiFarm" }, // 5ed87a9d06464fd7a22de9036379e69fd03a9e6e
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveFinishedBattle, "ServerLeaveFinishedBattle" }, // 6b1d1ed81434fc3e726e5fb6f0242d372c62bcfb
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerLeaveRelay, "ServerLeaveRelay" }, // b40257ea36dab49defde5714d3e048ce7b352d6d
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRelayFastTravel, "ServerRelayFastTravel" }, // 75ed3602becea306eadcc37e7fc29d205a21fddd
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestAIRivalActivity, "ServerRequestAIRivalActivity" }, // c80e7e10ec9ec959e9cfc9b1706b3daaa847cbd7
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestLogout, "ServerRequestLogout" }, // 8793bb393d78604510ad9321c6124cc00d208553
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestProfileSynchronization, "ServerRequestProfileSynchronization" }, // f2d31bd2b43ee1bac121bfddd5b643be241d97e9
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestRankedStatus, "ServerRequestRankedStatus" }, // 81f4fa86a666e67fab13eac94a2a750233c8cc5f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSave, "ServerRequestSave" }, // 01d5cc7e6f141d6d57b152158faaade443afc14a
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonArchive, "ServerRequestSeasonArchive" }, // 14db59cb5d5296072f0e7e5f38484b28182aa7c3
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRequestSeasonStatus, "ServerRequestSeasonStatus" }, // 3ccda1f32ac0851fc146ef27c5bc458c60587d3a
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerResumeRelayBattle, "ServerResumeRelayBattle" }, // 5b70349cb7a68f10ca39f827afd1b596be24b2db
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerRunRankedQuickMatch, "ServerRunRankedQuickMatch" }, // ecaaed2350988be81996b6853ab2141d538b6eac
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveRankedDefender, "ServerSaveRankedDefender" }, // 2ef65abf49e52036b18ceeeffa14d4d013fcbfcb
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSaveSeasonAndReturn, "ServerSaveSeasonAndReturn" }, // 4f51e7407436f9558f2b64ec8d5e96d21ae6d66b
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendLocalChat, "ServerSendLocalChat" }, // 9315ba26d535b9280b60d9ccd365ba17fc76f71c
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSendWorldChat, "ServerSendWorldChat" }, // 298ca171f35cd7f608439b6f56d1fa50f536e72f
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartFinalStoryBoss, "ServerStartFinalStoryBoss" }, // e167a7e163649540245b81ae52840460e170ab7d
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartRelayFieldTraining, "ServerStartRelayFieldTraining" }, // d9669c3960a0461e15a343d868e3287bbf533e39
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartSeasonMatch, "ServerStartSeasonMatch" }, // f3e60bbc7bd8a51d718d5766e4f16190870a6651
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerStartStoryBoss, "ServerStartStoryBoss" }, // b4ea1d89e45b5a5071c0a8877ea9c6dc54034dcf
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerSubmitBattleCommand, "ServerSubmitBattleCommand" }, // 7c4b5d4252af7eb76fe40ee054027cd65abf9e22
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelRelayMap, "ServerTravelRelayMap" }, // fd4814925e9fac27a4b11daa1f8825249ce37bb8
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ServerTravelToMap, "ServerTravelToMap" }, // 187e1c914a03b13456af8a5e3bfc6a479818eebd
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetFieldMenuOpen, "SetFieldMenuOpen" }, // 63606d31a68e9016edeb1802b440716ea0e16bef
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_SetRelayDialogueOpen, "SetRelayDialogueOpen" }, // 26695b5f044df26d8d52644cd07e74f0da289285
		{ &Z_Construct_UFunction_ADigimonVenomNXTPlayerController_ToggleFieldMenu, "ToggleFieldMenu" }, // 19ada2ee793ead29c47952e1d4fd35dadf6ad204
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTPlayerController Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SocialComponent = { "SocialComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, SocialComponent), Z_Construct_UClass_UDigimonVenomNXTSocialComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SocialComponent_MetaData), NewProp_SocialComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TradeComponent = { "TradeComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, TradeComponent), Z_Construct_UClass_UDigimonVenomNXTTradeComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TradeComponent_MetaData), NewProp_TradeComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UnrankedComponent = { "UnrankedComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, UnrankedComponent), Z_Construct_UClass_UDigimonVenomNXTUnrankedComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnrankedComponent_MetaData), NewProp_UnrankedComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CurrentBattle = { "CurrentBattle", "OnRep_CurrentBattle", (EPropertyFlags)0x0114000100000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, CurrentBattle), Z_Construct_UClass_ADigimonVenomNXTBattleActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentBattle_MetaData), NewProp_CurrentBattle_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAccountAuthenticated = { "bAccountAuthenticated", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ADigimonVenomNXTPlayerController), &UHT_STATICS::NewProp_bAccountAuthenticated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAccountAuthenticated_MetaData), NewProp_bAccountAuthenticated_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnClientMessage = { "OnClientMessage", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, OnClientMessage), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonClientMessageEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnClientMessage_MetaData), NewProp_OnClientMessage_MetaData) }; // 9fb2d1a4ef5f4748c13bd78f3380e7966bfd83a5
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnChatReceived = { "OnChatReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, OnChatReceived), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonChatReceivedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnChatReceived_MetaData), NewProp_OnChatReceived_MetaData) }; // 9daef46376218006f9709a661329327850e0b84d
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldChatHistory_Inner = { "WorldChatHistory", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonChatMessage, METADATA_PARAMS(0, nullptr) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_WorldChatHistory = { "WorldChatHistory", nullptr, (EPropertyFlags)0x0010000000002014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, WorldChatHistory), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldChatHistory_MetaData), NewProp_WorldChatHistory_MetaData) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnCurrentBattleChanged = { "OnCurrentBattleChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, OnCurrentBattleChanged), Z_Construct_UDelegateFunction_DigimonVenomNXTRuntime_DigimonCurrentBattleChangedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnCurrentBattleChanged_MetaData), NewProp_OnCurrentBattleChanged_MetaData) }; // 52824cf4e128f26b7bce661cfaf51793800219fc
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ProfileSyncWidget = { "ProfileSyncWidget", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, ProfileSyncWidget), Z_Construct_UClass_UDigimonVenomNXTProfileSyncWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProfileSyncWidget_MetaData), NewProp_ProfileSyncWidget_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LastQueuedOwnerProfile = { "LastQueuedOwnerProfile", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, LastQueuedOwnerProfile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastQueuedOwnerProfile_MetaData), NewProp_LastQueuedOwnerProfile_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PendingOwnerProfile = { "PendingOwnerProfile", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, PendingOwnerProfile), Z_Construct_UScriptStruct_FDigimonPlayerProfile, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PendingOwnerProfile_MetaData), NewProp_PendingOwnerProfile_MetaData) }; // f32a377a42f0dcc6e2cd7c85b1df28c388f385a6
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_GameHUDWidget = { "GameHUDWidget", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, GameHUDWidget), Z_Construct_UClass_UDigimonVenomNXTGameHUDWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GameHUDWidget_MetaData), NewProp_GameHUDWidget_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BattleWidget = { "BattleWidget", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, BattleWidget), Z_Construct_UClass_UDigimonVenomNXTBattleWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BattleWidget_MetaData), NewProp_BattleWidget_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LocalMapRenderer = { "LocalMapRenderer", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, LocalMapRenderer), Z_Construct_UClass_ADigimonVenomNXTLocalMapRenderer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalMapRenderer_MetaData), NewProp_LocalMapRenderer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DigiFarmScene = { "DigiFarmScene", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, DigiFarmScene), Z_Construct_UClass_ADigimonVenomNXTFarmScene, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DigiFarmScene_MetaData), NewProp_DigiFarmScene_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RelayScene = { "RelayScene", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, RelayScene), Z_Construct_UClass_ADigimonVenomNXTRelayScene, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelayScene_MetaData), NewProp_RelayScene_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RelaySession = { "RelaySession", "OnRep_RelaySession", (EPropertyFlags)0x0040000100000020, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, RelaySession), Z_Construct_UScriptStruct_FDigimonRelaySession, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RelaySession_MetaData), NewProp_RelaySession_MetaData) }; // 41ee24ba0927a82eb7fcfd8eb0f277b54508ae91
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FarmSession = { "FarmSession", "OnRep_DigiFarmSession", (EPropertyFlags)0x0040000100000020, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTPlayerController, FarmSession), Z_Construct_UScriptStruct_FDigimonFarmSession, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarmSession_MetaData), NewProp_FarmSession_MetaData) }; // 3d77b2a2cc417214930a36f09ffbef4a12eec6f7
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SocialComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TradeComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnrankedComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentBattle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAccountAuthenticated,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnClientMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnChatReceived,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldChatHistory_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldChatHistory,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnCurrentBattleChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ProfileSyncWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastQueuedOwnerProfile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PendingOwnerProfile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GameHUDWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BattleWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocalMapRenderer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DigiFarmScene,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelayScene,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RelaySession,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FarmSession,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTPlayerController Property Definitions **********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APlayerController,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTPlayerController,
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
static void ADigimonVenomNXTPlayerController_StaticRegisterNativesADigimonVenomNXTPlayerController()
{
	UClass* Class = ADigimonVenomNXTPlayerController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController;
UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTPlayerController;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTPlayerController"),
				Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.InnerSingleton,
				ADigimonVenomNXTPlayerController_StaticRegisterNativesADigimonVenomNXTPlayerController,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTPlayerController::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_CurrentBattle(TEXT("CurrentBattle"));
	static FName Name_bAccountAuthenticated(TEXT("bAccountAuthenticated"));
	static FName Name_RelaySession(TEXT("RelaySession"));
	static FName Name_FarmSession(TEXT("FarmSession"));
	const bool bIsValid = true
		&& Name_CurrentBattle == ClassReps[(int32)ENetFields_Private::CurrentBattle].Property->GetFName()
		&& Name_bAccountAuthenticated == ClassReps[(int32)ENetFields_Private::bAccountAuthenticated].Property->GetFName()
		&& Name_RelaySession == ClassReps[(int32)ENetFields_Private::RelaySession].Property->GetFName()
		&& Name_FarmSession == ClassReps[(int32)ENetFields_Private::FarmSession].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTPlayerController"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTPlayerController);
ADigimonVenomNXTPlayerController::~ADigimonVenomNXTPlayerController() {}
// ********** End Class ADigimonVenomNXTPlayerController *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonFarmSession, Z_Construct_UScriptStruct_FDigimonFarmSession_Statics::NewStructOps, TEXT("DigimonFarmSession"),&Z_Registration_Info_UScriptStruct_FDigimonFarmSession, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonFarmSession), 1031254690U) },
		{ Z_Construct_UScriptStruct_FDigimonRelaySession, Z_Construct_UScriptStruct_FDigimonRelaySession_Statics::NewStructOps, TEXT("DigimonRelaySession"),&Z_Registration_Info_UScriptStruct_FDigimonRelaySession, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonRelaySession), 1106126010U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTPlayerController, TEXT("ADigimonVenomNXTPlayerController"), &Z_Registration_Info_UClass_ADigimonVenomNXTPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTPlayerController), 1336991534U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h__Script_DigimonVenomNXTRuntime_449ca56fb9e9a8aba2e1a778db223d0ce7c566e9{
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
