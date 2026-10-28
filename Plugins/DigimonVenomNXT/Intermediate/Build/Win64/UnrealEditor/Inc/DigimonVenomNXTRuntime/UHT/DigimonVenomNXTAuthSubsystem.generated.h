// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTAuthSubsystem.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAuthSubsystem_generated_h
#error "DigimonVenomNXTAuthSubsystem.generated.h already included, missing '#pragma once' in DigimonVenomNXTAuthSubsystem.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTAuthSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDigimonAuthResult;

// ********** Begin ScriptStruct FDigimonAccountRecord *********************************************
struct Z_Construct_UScriptStruct_FDigimonAccountRecord_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAccountRecord(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_14_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonAccountRecord_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonAccountRecord(ETypeConstructPhase::Inner); }


struct FDigimonAccountRecord;
// ********** End ScriptStruct FDigimonAccountRecord ***********************************************

// ********** Begin Class UDigimonVenomNXTAccountSaveGame ******************************************
struct Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_39_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTAccountSaveGame, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTAccountSaveGame) \
	DECLARE_SERIALIZER(UDigimonVenomNXTAccountSaveGame)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_39_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTAccountSaveGame(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTAccountSaveGame(UDigimonVenomNXTAccountSaveGame&&) = delete; \
	UDigimonVenomNXTAccountSaveGame(const UDigimonVenomNXTAccountSaveGame&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTAccountSaveGame); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTAccountSaveGame); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTAccountSaveGame) \
	NO_API virtual ~UDigimonVenomNXTAccountSaveGame();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_36_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_39_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTAccountSaveGame;

// ********** End Class UDigimonVenomNXTAccountSaveGame ********************************************

// ********** Begin Class UDigimonVenomNXTAuthSubsystem ********************************************
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetAccountSaveSlotName); \
	DECLARE_FUNCTION(execWasLastAuthSuccessful); \
	DECLARE_FUNCTION(execGetLastAuthMessage); \
	DECLARE_FUNCTION(execGetAccountId); \
	DECLARE_FUNCTION(execGetUsername); \
	DECLARE_FUNCTION(execIsPendingCreateAccount); \
	DECLARE_FUNCTION(execHasPendingCredentials); \
	DECLARE_FUNCTION(execIsLoggedIn); \
	DECLARE_FUNCTION(execLogout); \
	DECLARE_FUNCTION(execLogin); \
	DECLARE_FUNCTION(execCreateAccount);


struct Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDigimonVenomNXTAuthSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_UDigimonVenomNXTAuthSubsystem) \
	DECLARE_SERIALIZER(UDigimonVenomNXTAuthSubsystem)


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDigimonVenomNXTAuthSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDigimonVenomNXTAuthSubsystem(UDigimonVenomNXTAuthSubsystem&&) = delete; \
	UDigimonVenomNXTAuthSubsystem(const UDigimonVenomNXTAuthSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDigimonVenomNXTAuthSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDigimonVenomNXTAuthSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDigimonVenomNXTAuthSubsystem) \
	NO_API virtual ~UDigimonVenomNXTAuthSubsystem();


#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_53_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h_56_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDigimonVenomNXTAuthSubsystem;

// ********** End Class UDigimonVenomNXTAuthSubsystem **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_Digimon_Venom_NXT_UE5_MMORPG_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTAuthSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
