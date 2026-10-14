// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTTradeComponent.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTTradeComponent_generated_h
#error "DigimonVenomNXTTradeComponent.generated.h already included, missing '#pragma once' in DigimonVenomNXTTradeComponent.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTTradeComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGuid;

// ********** Begin Class UDigimonVenomNXTTradeComponent *******************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerCancelTrade_Implementation(FGuid SessionId); \
	virtual void ServerConfirmTrade_Implementation(FGuid SessionId, int32 Revision); \
	virtual void ServerUpdateOffer_Implementation(FGuid SessionId, int32 Revision, TArray<FGuid> const& PartnerIds, int64 Credits, int32 DigiRubies); \
	virtual void ServerInviteTrade_Implementation(const FString& TargetAccountId); \
	virtual void ServerConfirmPurchase_Implementation(FGuid PurchaseToken); \
	virtual void ServerReviewPurchase_Implementation(FGuid ListingId); \
	virtual void ServerCancelListing_Implementation(FGuid ListingId); \
	virtual void ServerCreateListing_Implementation(FGuid PartnerId, int64 Credits, int32 DigiRubies); \
	virtual void ServerBrowse_Implementation(const FString& Search, int32 Page, bool bMineOnly); \
	DECLARE_FUNCTION(execOnRep_View); \
	DECLARE_FUNCTION(execServerCancelTrade); \
	DECLARE_FUNCTION(execServerConfirmTrade); \
	DECLARE_FUNCTION(execServerUpdateOffer); \
	DECLARE_FUNCTION(execServerInviteTrade); \
	DECLARE_FUNCTION(execServerConfirmPurchase); \
	DECLARE_FUNCTION(execServerReviewPurchase); \
	DECLARE_FUNCTION(execServerCancelListing); \
	DECLARE_FUNCTION(execServerCreateListing); \
	DECLARE_FUNCTION(execServerBrowse);


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UDigimonVenomNXTTradeComponent_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTTradeComponent_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTTradeComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTTradeComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTTradeComponent) \
	DECLARE_SERIALIZER(UDigimonVenomNXTTradeComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		View=NETFIELD_REP_START, \
		NETFIELD_REP_END=View	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTTradeComponent(UDigimonVenomNXTTradeComponent&&) = delete; \
	UDigimonVenomNXTTradeComponent(const UDigimonVenomNXTTradeComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTTradeComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTTradeComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDigimonVenomNXTTradeComponent) \
	NO_API virtual ~UDigimonVenomNXTTradeComponent();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_11_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTTradeComponent;

// ********** End Class UDigimonVenomNXTTradeComponent *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTTradeComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
