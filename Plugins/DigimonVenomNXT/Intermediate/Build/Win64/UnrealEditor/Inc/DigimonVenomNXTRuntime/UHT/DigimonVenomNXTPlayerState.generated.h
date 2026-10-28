// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTPlayerState.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPlayerState_generated_h
#error "DigimonVenomNXTPlayerState.generated.h already included, missing '#pragma once' in DigimonVenomNXTPlayerState.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPlayerState_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EDigimonCurrency : uint8;
enum class EDigimonTrainingStat : uint8;
enum class EDigimonVariant : uint8;
struct FDigimonHealReceipt;
struct FDigimonOwnedPartner;
struct FGuid;

// ********** Begin Class ADigimonVenomNXTPlayerState **********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerDeEvolve_Implementation(FGuid InstanceId, FName TargetSpeciesId); \
	virtual void ServerEvolve_Implementation(FGuid InstanceId, FName TargetSpeciesId); \
	virtual void ServerUseDigiMeat_Implementation(FGuid InstanceId, EDigimonTrainingStat Stat); \
	virtual void ServerUseABIMeat_Implementation(FGuid InstanceId); \
	virtual void ServerUseCAMTreat_Implementation(FGuid InstanceId); \
	virtual void ServerFeedFarmResident_Implementation(FGuid InstanceId, FName ItemId, EDigimonTrainingStat Stat); \
	virtual void ServerSetFarmResident_Implementation(FGuid InstanceId, bool bResident); \
	virtual void ServerUseHealingItem_Implementation(FGuid InstanceId, FName ItemId); \
	virtual void ServerPurchaseItem_Implementation(FName ItemId, EDigimonCurrency Currency, int32 Quantity); \
	virtual void ServerConvertDigiRubiesToCredits_Implementation(int32 RubyAmount); \
	virtual void ServerFeedABIMeat_Implementation(FGuid InstanceId, EDigimonCurrency Currency); \
	virtual void ClientDigiLabHealResult_Implementation(FDigimonHealReceipt const& Receipt); \
	virtual void ServerRequestDigiLabHeal_Implementation(FGuid RequestId); \
	virtual void ServerHealAll_Implementation(); \
	virtual void ServerMaterialize_Implementation(FName SpeciesId, EDigimonVariant Variant); \
	virtual void ServerSetTamerStyle_Implementation(FName TamerStyleId); \
	virtual void ServerSetParty_Implementation(TArray<FGuid> const& NewParty); \
	virtual void ServerChooseStarter_Implementation(FName SpeciesId); \
	DECLARE_FUNCTION(execOnRep_Profile); \
	DECLARE_FUNCTION(execGetInventoryQuantity); \
	DECLARE_FUNCTION(execServerDeEvolve); \
	DECLARE_FUNCTION(execServerEvolve); \
	DECLARE_FUNCTION(execServerUseDigiMeat); \
	DECLARE_FUNCTION(execServerUseABIMeat); \
	DECLARE_FUNCTION(execServerUseCAMTreat); \
	DECLARE_FUNCTION(execServerFeedFarmResident); \
	DECLARE_FUNCTION(execServerSetFarmResident); \
	DECLARE_FUNCTION(execServerUseHealingItem); \
	DECLARE_FUNCTION(execServerPurchaseItem); \
	DECLARE_FUNCTION(execServerConvertDigiRubiesToCredits); \
	DECLARE_FUNCTION(execServerFeedABIMeat); \
	DECLARE_FUNCTION(execClientDigiLabHealResult); \
	DECLARE_FUNCTION(execServerRequestDigiLabHeal); \
	DECLARE_FUNCTION(execServerHealAll); \
	DECLARE_FUNCTION(execServerMaterialize); \
	DECLARE_FUNCTION(execServerSetTamerStyle); \
	DECLARE_FUNCTION(execServerSetParty); \
	DECLARE_FUNCTION(execServerChooseStarter); \
	DECLARE_FUNCTION(execGetScanPercent); \
	DECLARE_FUNCTION(execGetPartner); \
	DECLARE_FUNCTION(execHasStarter);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTPlayerState_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTPlayerState_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTPlayerState(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTPlayerState, APlayerState, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTPlayerState) \
	DECLARE_SERIALIZER(ADigimonVenomNXTPlayerState) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ScanPolicy=NETFIELD_REP_START, \
		PublicSnapshot, \
		NETFIELD_REP_END=PublicSnapshot	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTPlayerState(ADigimonVenomNXTPlayerState&&) = delete; \
	ADigimonVenomNXTPlayerState(const ADigimonVenomNXTPlayerState&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTPlayerState); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTPlayerState); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTPlayerState) \
	NO_API virtual ~ADigimonVenomNXTPlayerState();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_13_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTPlayerState;

// ********** End Class ADigimonVenomNXTPlayerState ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerState_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
