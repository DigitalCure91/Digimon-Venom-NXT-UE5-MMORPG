// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTSocialComponent.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTSocialComponent_generated_h
#error "DigimonVenomNXTSocialComponent.generated.h already included, missing '#pragma once' in DigimonVenomNXTSocialComponent.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTSocialComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EDigimonSocialAction : uint8;

// ********** Begin Class UDigimonVenomNXTSocialComponent ******************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ClientSocialResult_Implementation(bool bSuccess, const FString& Message); \
	virtual void ServerSendClanChat_Implementation(const FString& Message); \
	virtual void ServerRequestPlayerInfo_Implementation(const FString& UsernameOrId); \
	virtual void ServerSocialAction_Implementation(EDigimonSocialAction Action, const FString& Target, const FString& Text, const FString& Extra); \
	virtual void ServerRefreshSocial_Implementation(); \
	DECLARE_FUNCTION(execOnRep_State); \
	DECLARE_FUNCTION(execClientSocialResult); \
	DECLARE_FUNCTION(execServerSendClanChat); \
	DECLARE_FUNCTION(execServerRequestPlayerInfo); \
	DECLARE_FUNCTION(execServerSocialAction); \
	DECLARE_FUNCTION(execServerRefreshSocial);


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UDigimonVenomNXTSocialComponent_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTSocialComponent_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTSocialComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTSocialComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTSocialComponent) \
	DECLARE_SERIALIZER(UDigimonVenomNXTSocialComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		State=NETFIELD_REP_START, \
		NETFIELD_REP_END=State	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTSocialComponent(UDigimonVenomNXTSocialComponent&&) = delete; \
	UDigimonVenomNXTSocialComponent(const UDigimonVenomNXTSocialComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTSocialComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTSocialComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDigimonVenomNXTSocialComponent) \
	NO_API virtual ~UDigimonVenomNXTSocialComponent();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_12_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTSocialComponent;

// ********** End Class UDigimonVenomNXTSocialComponent ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
