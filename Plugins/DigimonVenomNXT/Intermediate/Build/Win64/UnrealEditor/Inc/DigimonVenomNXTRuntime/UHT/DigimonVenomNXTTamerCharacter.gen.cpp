// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTTamerCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTTamerCharacter() {}

// ********** Begin Cross Module References ********************************************************
PAPER2D_API UClass* Z_Construct_UClass_APaperCharacter(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTNameplateComponent(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPartnerFollower(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function AdjustCameraZoom *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_AdjustCameraZoom_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTTamerCharacter_eventAdjustCameraZoom_Parms
	{
		float Direction;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Camera" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AdjustCameraZoom constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AdjustCameraZoom constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AdjustCameraZoom Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerCharacter_eventAdjustCameraZoom_Parms, Direction), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Direction,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AdjustCameraZoom Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "AdjustCameraZoom", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTTamerCharacter_eventAdjustCameraZoom_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTTamerCharacter_eventAdjustCameraZoom_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_AdjustCameraZoom(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execAdjustCameraZoom)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Direction);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdjustCameraZoom(Z_Param_Direction);
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function AdjustCameraZoom *******************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function BP_OnFacingChanged ***************
struct DigimonVenomNXTTamerCharacter_eventBP_OnFacingChanged_Parms
{
	EDigimonFacing NewFacing;
};
static FName NAME_ADigimonVenomNXTTamerCharacter_BP_OnFacingChanged = FName(TEXT("BP_OnFacingChanged"));
void ADigimonVenomNXTTamerCharacter::BP_OnFacingChanged(EDigimonFacing NewFacing)
{
	DigimonVenomNXTTamerCharacter_eventBP_OnFacingChanged_Parms Parms;
	Parms.NewFacing=NewFacing;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTTamerCharacter_BP_OnFacingChanged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFacingChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnFacingChanged constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewFacing_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewFacing;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnFacingChanged constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnFacingChanged Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_NewFacing_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_NewFacing = { "NewFacing", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerCharacter_eventBP_OnFacingChanged_Parms, NewFacing), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing, METADATA_PARAMS(0, nullptr) }; // 3468c7b186f8660ca8fa082482b86445185fe59f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewFacing_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewFacing,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnFacingChanged Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "BP_OnFacingChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTamerCharacter_eventBP_OnFacingChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTamerCharacter_eventBP_OnFacingChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFacingChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ADigimonVenomNXTTamerCharacter Function BP_OnFacingChanged *****************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function BP_OnFollowerChanged *************
struct DigimonVenomNXTTamerCharacter_eventBP_OnFollowerChanged_Parms
{
	ADigimonVenomNXTPartnerFollower* NewFollower;
};
static FName NAME_ADigimonVenomNXTTamerCharacter_BP_OnFollowerChanged = FName(TEXT("BP_OnFollowerChanged"));
void ADigimonVenomNXTTamerCharacter::BP_OnFollowerChanged(ADigimonVenomNXTPartnerFollower* NewFollower)
{
	DigimonVenomNXTTamerCharacter_eventBP_OnFollowerChanged_Parms Parms;
	Parms.NewFollower=NewFollower;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTTamerCharacter_BP_OnFollowerChanged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFollowerChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnFollowerChanged constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewFollower;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnFollowerChanged constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnFollowerChanged Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NewFollower = { "NewFollower", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerCharacter_eventBP_OnFollowerChanged_Parms, NewFollower), Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewFollower,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnFollowerChanged Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "BP_OnFollowerChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTamerCharacter_eventBP_OnFollowerChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTamerCharacter_eventBP_OnFollowerChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFollowerChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ADigimonVenomNXTTamerCharacter Function BP_OnFollowerChanged ***************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function OnRep_Facing *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Facing_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_Facing constinit property declarations **************************
// ********** End Function OnRep_Facing constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "OnRep_Facing", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Facing(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execOnRep_Facing)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Facing();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function OnRep_Facing ***********************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function OnRep_Follower *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Follower_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_Follower constinit property declarations ************************
// ********** End Function OnRep_Follower constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "OnRep_Follower", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Follower(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execOnRep_Follower)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Follower();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function OnRep_Follower *********************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function OnRep_TamerStyle *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_TamerStyle_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_TamerStyle constinit property declarations **********************
// ********** End Function OnRep_TamerStyle constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "OnRep_TamerStyle", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_TamerStyle(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execOnRep_TamerStyle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_TamerStyle();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function OnRep_TamerStyle *******************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function RefreshFollowerFromProfile *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshFollowerFromProfile_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshFollowerFromProfile constinit property declarations ************
// ********** End Function RefreshFollowerFromProfile constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "RefreshFollowerFromProfile", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshFollowerFromProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execRefreshFollowerFromProfile)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshFollowerFromProfile();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function RefreshFollowerFromProfile *********

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function RefreshTamerStyleFromProfile *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshTamerStyleFromProfile_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshTamerStyleFromProfile constinit property declarations **********
// ********** End Function RefreshTamerStyleFromProfile constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "RefreshTamerStyleFromProfile", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshTamerStyleFromProfile(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execRefreshTamerStyleFromProfile)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshTamerStyleFromProfile();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function RefreshTamerStyleFromProfile *******

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function ResetEncounterTracker ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ResetEncounterTracker_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Wild" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called after spawn/travel/battle so the next encounter cannot immediately retrigger. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called after spawn/travel/battle so the next encounter cannot immediately retrigger." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetEncounterTracker constinit property declarations *****************
// ********** End Function ResetEncounterTracker constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "ResetEncounterTracker", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ResetEncounterTracker(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execResetEncounterTracker)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetEncounterTracker();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function ResetEncounterTracker **************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function ServerSetFacing ******************
struct DigimonVenomNXTTamerCharacter_eventServerSetFacing_Parms
{
	EDigimonFacing NewFacing;
};
static FName NAME_ADigimonVenomNXTTamerCharacter_ServerSetFacing = FName(TEXT("ServerSetFacing"));
void ADigimonVenomNXTTamerCharacter::ServerSetFacing(EDigimonFacing NewFacing)
{
	DigimonVenomNXTTamerCharacter_eventServerSetFacing_Parms Parms;
	Parms.NewFacing=NewFacing;
	UFunction* Func = FindFunctionChecked(NAME_ADigimonVenomNXTTamerCharacter_ServerSetFacing);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ServerSetFacing_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerSetFacing constinit property declarations ***********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewFacing_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewFacing;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerSetFacing constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerSetFacing Property Definitions **********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_NewFacing_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_NewFacing = { "NewFacing", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTTamerCharacter_eventServerSetFacing_Parms, NewFacing), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing, METADATA_PARAMS(0, nullptr) }; // 3468c7b186f8660ca8fa082482b86445185fe59f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewFacing_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewFacing,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ServerSetFacing Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "ServerSetFacing", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<DigimonVenomNXTTamerCharacter_eventServerSetFacing_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280C40, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(DigimonVenomNXTTamerCharacter_eventServerSetFacing_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ServerSetFacing(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execServerSetFacing)
{
	P_GET_ENUM(EDigimonFacing,Z_Param_NewFacing);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSetFacing_Implementation(EDigimonFacing(Z_Param_NewFacing));
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function ServerSetFacing ********************

// ********** Begin Class ADigimonVenomNXTTamerCharacter Function SnapFollowerToTamer **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_SnapFollowerToTamer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SnapFollowerToTamer constinit property declarations *******************
// ********** End Function SnapFollowerToTamer constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, nullptr, "SnapFollowerToTamer", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_SnapFollowerToTamer(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADigimonVenomNXTTamerCharacter::execSnapFollowerToTamer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SnapFollowerToTamer();
	P_NATIVE_END;
}
// ********** End Class ADigimonVenomNXTTamerCharacter Function SnapFollowerToTamer ****************

// ********** Begin Class ADigimonVenomNXTTamerCharacter *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADigimonVenomNXTTamerCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Top-down replicated tamer pawn with handheld-RPG field camera and walking-driven encounters. */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "DigimonVenomNXTTamerCharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Top-down replicated tamer pawn with handheld-RPG field camera and walking-driven encounters." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationSet_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nameplate_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Facing_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TamerStyleId_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Tamer" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Follower_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowerClass_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Follower" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTTamerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADigimonVenomNXTTamerCharacter constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimationSet;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Nameplate;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Facing_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Facing;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TamerStyleId;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Follower;
	static const UECodeGen_Private::FClassPropertyParams NewProp_FollowerClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADigimonVenomNXTTamerCharacter constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AdjustCameraZoom"), .Pointer = &ADigimonVenomNXTTamerCharacter::execAdjustCameraZoom },
		{ .NameUTF8 = UTF8TEXT("OnRep_Facing"), .Pointer = &ADigimonVenomNXTTamerCharacter::execOnRep_Facing },
		{ .NameUTF8 = UTF8TEXT("OnRep_Follower"), .Pointer = &ADigimonVenomNXTTamerCharacter::execOnRep_Follower },
		{ .NameUTF8 = UTF8TEXT("OnRep_TamerStyle"), .Pointer = &ADigimonVenomNXTTamerCharacter::execOnRep_TamerStyle },
		{ .NameUTF8 = UTF8TEXT("RefreshFollowerFromProfile"), .Pointer = &ADigimonVenomNXTTamerCharacter::execRefreshFollowerFromProfile },
		{ .NameUTF8 = UTF8TEXT("RefreshTamerStyleFromProfile"), .Pointer = &ADigimonVenomNXTTamerCharacter::execRefreshTamerStyleFromProfile },
		{ .NameUTF8 = UTF8TEXT("ResetEncounterTracker"), .Pointer = &ADigimonVenomNXTTamerCharacter::execResetEncounterTracker },
		{ .NameUTF8 = UTF8TEXT("ServerSetFacing"), .Pointer = &ADigimonVenomNXTTamerCharacter::execServerSetFacing },
		{ .NameUTF8 = UTF8TEXT("SnapFollowerToTamer"), .Pointer = &ADigimonVenomNXTTamerCharacter::execSnapFollowerToTamer },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_AdjustCameraZoom, "AdjustCameraZoom" }, // 40026d82ed5169f9e27b2c1074cdac83b0c716e6
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFacingChanged, "BP_OnFacingChanged" }, // 801deba073f0b57117b1a8dec5d6e9af74b4a022
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_BP_OnFollowerChanged, "BP_OnFollowerChanged" }, // 687046e9f3102b2a961aa637e038bfee5684f793
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Facing, "OnRep_Facing" }, // 54a3b916f4335bdbf7bc79c87874fae2b855c215
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_Follower, "OnRep_Follower" }, // 76f3ff0180990876196ed4d4dbf8f0551a2c7605
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_OnRep_TamerStyle, "OnRep_TamerStyle" }, // 83dd1fd4d05ff2125cd7f3803299ec149440677c
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshFollowerFromProfile, "RefreshFollowerFromProfile" }, // 6cc0d0988fab57a9d0dc756842032c491ff70e09
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_RefreshTamerStyleFromProfile, "RefreshTamerStyleFromProfile" }, // 2a97e66bc223b4c6be37063b1cd2da1f09bb4634
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ResetEncounterTracker, "ResetEncounterTracker" }, // 9f5e75f677ede0e695e3d59a19180e3dd4a8e42d
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_ServerSetFacing, "ServerSetFacing" }, // e0e2bdc791be6e923e92383618853b88ccda06d3
		{ &Z_Construct_UFunction_ADigimonVenomNXTTamerCharacter_SnapFollowerToTamer, "SnapFollowerToTamer" }, // 522369dd02d41a5af7c5da13e56ce48afd83d597
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADigimonVenomNXTTamerCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADigimonVenomNXTTamerCharacter Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AnimationSet = { "AnimationSet", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, AnimationSet), Z_Construct_UClass_UDigimonVenomNXTTamerAnimationSet, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationSet_MetaData), NewProp_AnimationSet_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Nameplate = { "Nameplate", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, Nameplate), Z_Construct_UClass_UDigimonVenomNXTNameplateComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nameplate_MetaData), NewProp_Nameplate_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Facing_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Facing = { "Facing", "OnRep_Facing", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, Facing), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonFacing, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Facing_MetaData), NewProp_Facing_MetaData) }; // 3468c7b186f8660ca8fa082482b86445185fe59f
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TamerStyleId = { "TamerStyleId", "OnRep_TamerStyle", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, TamerStyleId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TamerStyleId_MetaData), NewProp_TamerStyleId_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Follower = { "Follower", "OnRep_Follower", (EPropertyFlags)0x0114000100000034, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, Follower), Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Follower_MetaData), NewProp_Follower_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_FollowerClass = { "FollowerClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ADigimonVenomNXTTamerCharacter, FollowerClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ADigimonVenomNXTPartnerFollower, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowerClass_MetaData), NewProp_FollowerClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AnimationSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Nameplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Facing_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Facing,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TamerStyleId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Follower,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowerClass,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADigimonVenomNXTTamerCharacter Property Definitions ************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APaperCharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADigimonVenomNXTTamerCharacter,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADigimonVenomNXTTamerCharacter_StaticRegisterNativesADigimonVenomNXTTamerCharacter()
{
	UClass* Class = ADigimonVenomNXTTamerCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter;
UClass* Z_Construct_UClass_ADigimonVenomNXTTamerCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADigimonVenomNXTTamerCharacter;
		if (!Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTTamerCharacter"),
				Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.InnerSingleton,
				ADigimonVenomNXTTamerCharacter_StaticRegisterNativesADigimonVenomNXTTamerCharacter,
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
		return Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void ADigimonVenomNXTTamerCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_Facing(TEXT("Facing"));
	static FName Name_TamerStyleId(TEXT("TamerStyleId"));
	static FName Name_Follower(TEXT("Follower"));
	const bool bIsValid = true
		&& Name_Facing == ClassReps[(int32)ENetFields_Private::Facing].Property->GetFName()
		&& Name_TamerStyleId == ClassReps[(int32)ENetFields_Private::TamerStyleId].Property->GetFName()
		&& Name_Follower == ClassReps[(int32)ENetFields_Private::Follower].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ADigimonVenomNXTTamerCharacter"));
}
#endif
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADigimonVenomNXTTamerCharacter);
ADigimonVenomNXTTamerCharacter::~ADigimonVenomNXTTamerCharacter() {}
// ********** End Class ADigimonVenomNXTTamerCharacter *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADigimonVenomNXTTamerCharacter, TEXT("ADigimonVenomNXTTamerCharacter"), &Z_Registration_Info_UClass_ADigimonVenomNXTTamerCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADigimonVenomNXTTamerCharacter), 3797793403U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTamerCharacter_h__Script_DigimonVenomNXTRuntime_351a249678131846cf5fe8ac082458c8284fe0f5{
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
