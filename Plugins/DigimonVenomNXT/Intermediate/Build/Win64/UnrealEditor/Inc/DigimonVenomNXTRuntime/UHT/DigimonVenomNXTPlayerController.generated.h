// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DigimonVenomNXTPlayerController.h"

#ifdef DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPlayerController_generated_h
#error "DigimonVenomNXTPlayerController.generated.h already included, missing '#pragma once' in DigimonVenomNXTPlayerController.h"
#endif
#define DIGIMONVENOMNXTRUNTIME_DigimonVenomNXTPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ADigimonVenomNXTBattleActor;
class ADigimonVenomNXTFarmScene;
class UDigimonVenomNXTBattleWidget;
class UDigimonVenomNXTGameHUDWidget;
enum class EDigimonAudioCue : uint8;
enum class EDigimonPrivateCampaign : uint8;
struct FDigimonAIRivalActivityPage;
struct FDigimonBattleCommand;
struct FDigimonChatMessage;
struct FDigimonRelayProgress;
struct FDigimonSeasonArchivePage;
struct FGuid;

// ********** Begin ScriptStruct FDigimonFarmSession ***********************************************
struct Z_Construct_UScriptStruct_FDigimonFarmSession_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonFarmSession(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_30_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonFarmSession_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonFarmSession(ETypeConstructPhase::Inner); }


struct FDigimonFarmSession;
// ********** End ScriptStruct FDigimonFarmSession *************************************************

// ********** Begin ScriptStruct FDigimonRelaySession **********************************************
struct Z_Construct_UScriptStruct_FDigimonRelaySession_Statics;
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonRelaySession(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_40_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDigimonRelaySession_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FDigimonRelaySession(ETypeConstructPhase::Inner); }


struct FDigimonRelaySession;
// ********** End ScriptStruct FDigimonRelaySession ************************************************

// ********** Begin Class ADigimonVenomNXTPlayerController *****************************************
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ClientSetActiveMapPresentation_Implementation(int32 MapId); \
	virtual void ClientPlayAudioCue_Implementation(EDigimonAudioCue Cue, FGuid ReceiptId); \
	virtual void ClientPlayExplorationMusic_Implementation(int32 MapId); \
	virtual void ClientReceiveLocalChat_Implementation(FDigimonChatMessage const& Message); \
	virtual void ClientReturnToSeason_Implementation(); \
	virtual void ClientShowMessage_Implementation(const FString& Title, const FString& Message); \
	virtual void ServerRequestSave_Implementation(); \
	virtual void ServerSendWorldChat_Implementation(const FString& Message); \
	virtual void ServerSendLocalChat_Implementation(const FString& Message); \
	virtual void ServerLeaveFinishedBattle_Implementation(); \
	virtual void ServerSubmitBattleCommand_Implementation(FDigimonBattleCommand const& Command); \
	virtual void ServerAcknowledgeBattlePresentation_Implementation(ADigimonVenomNXTBattleActor* BattleActor); \
	virtual void ServerRunRankedQuickMatch_Implementation(); \
	virtual void ServerSaveRankedDefender_Implementation(); \
	virtual void ServerStartFinalStoryBoss_Implementation(); \
	virtual void ServerStartStoryBoss_Implementation(int32 Chapter); \
	virtual void ServerBeginSecondStory_Implementation(); \
	virtual void ClientReturnFromSeason_Implementation(); \
	virtual void ServerSaveSeasonAndReturn_Implementation(); \
	virtual void ServerAdvanceSeasonWeek_Implementation(); \
	virtual void ServerStartSeasonMatch_Implementation(); \
	virtual void ClientReceiveSeasonArchive_Implementation(FDigimonSeasonArchivePage const& Page); \
	virtual void ServerRequestSeasonArchive_Implementation(int32 PageIndex); \
	virtual void ServerRequestSeasonStatus_Implementation(); \
	virtual void ServerRequestRankedStatus_Implementation(); \
	virtual void ClientReceiveAIRivalActivity_Implementation(FDigimonAIRivalActivityPage const& Page); \
	virtual void ServerRequestAIRivalActivity_Implementation(int32 PageIndex, int32 PageSize); \
	virtual void ServerChallengeAIRival_Implementation(const FString& RivalId); \
	virtual void ClientSetRelayPresentation_Implementation(EDigimonPrivateCampaign Campaign, bool bInside, int32 MapId, FVector Origin, uint64 Revision); \
	virtual void ClientShowRelayDialogue_Implementation(FName NPCId, const FString& Dialogue, EDigimonPrivateCampaign Campaign, FDigimonRelayProgress const& ConfirmedProgress); \
	virtual void ServerResumeRelayBattle_Implementation(); \
	virtual void ServerStartRelayFieldTraining_Implementation(); \
	virtual void ServerChallengeRelayNPC_Implementation(FName NPCId); \
	virtual void ServerInteractRelayNPC_Implementation(FName NPCId); \
	virtual void ServerRelayFastTravel_Implementation(int32 MapId); \
	virtual void ServerTravelRelayMap_Implementation(int32 MapId); \
	virtual void ServerLeaveRelay_Implementation(); \
	virtual void ServerAdvanceGhostLineQuest_Implementation(FName NPCId); \
	virtual void ServerEnterGhostLine_Implementation(); \
	virtual void ServerAdvanceChroniclesQuest_Implementation(FName NPCId); \
	virtual void ServerEnterChronicles_Implementation(); \
	virtual void ServerEnterRelay_Implementation(); \
	virtual void ClientSetDigiFarmPresentation_Implementation(bool bInside, FVector Origin, int32 ReturnMapId, uint64 Revision); \
	virtual void ServerLeaveDigiFarm_Implementation(); \
	virtual void ServerEnterDigiFarm_Implementation(); \
	virtual void ServerTravelToMap_Implementation(int32 MapId); \
	virtual void ClientAccountAuthenticationResult_Implementation(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId); \
	virtual void ServerAuthenticateAccount_Implementation(bool bCreateAccount, const FString& Username, const FString& Password); \
	virtual void ClientHostSessionClosed_Implementation(const FString& Message); \
	virtual void ClientLogoutResult_Implementation(FGuid RequestId, bool bSuccess, const FString& Message); \
	virtual void ServerRequestLogout_Implementation(FGuid RequestId); \
	virtual void ClientProfileSynchronizationFailed_Implementation(const FString& Message); \
	virtual void ServerRequestProfileSynchronization_Implementation(); \
	virtual void ServerCompleteProfileSnapshot_Implementation(FGuid TransferId, int64 Revision, bool bAccepted); \
	virtual void ServerAcknowledgeProfileChunk_Implementation(FGuid TransferId, int32 Offset); \
	virtual void ClientProfileSnapshotChunk_Implementation(FGuid TransferId, int32 Offset, TArray<uint8> const& Bytes); \
	virtual void ClientBeginProfileSnapshot_Implementation(FGuid TransferId, int32 Protocol, int64 Revision, const FString& AccountId, int32 ByteCount, int32 JsonByteCount, int64 Checksum); \
	DECLARE_FUNCTION(execOnRep_RelaySession); \
	DECLARE_FUNCTION(execOnRep_DigiFarmSession); \
	DECLARE_FUNCTION(execOnRep_CurrentBattle); \
	DECLARE_FUNCTION(execIsFieldInputBlocked); \
	DECLARE_FUNCTION(execIsFieldMenuOpen); \
	DECLARE_FUNCTION(execToggleFieldMenu); \
	DECLARE_FUNCTION(execSetFieldMenuOpen); \
	DECLARE_FUNCTION(execGetNativeBattleWidget); \
	DECLARE_FUNCTION(execGetNativeHUDWidget); \
	DECLARE_FUNCTION(execClientSetActiveMapPresentation); \
	DECLARE_FUNCTION(execClientPlayAudioCue); \
	DECLARE_FUNCTION(execClientPlayExplorationMusic); \
	DECLARE_FUNCTION(execClientReceiveLocalChat); \
	DECLARE_FUNCTION(execClientReturnToSeason); \
	DECLARE_FUNCTION(execClientShowMessage); \
	DECLARE_FUNCTION(execServerRequestSave); \
	DECLARE_FUNCTION(execServerSendWorldChat); \
	DECLARE_FUNCTION(execServerSendLocalChat); \
	DECLARE_FUNCTION(execServerLeaveFinishedBattle); \
	DECLARE_FUNCTION(execServerSubmitBattleCommand); \
	DECLARE_FUNCTION(execServerAcknowledgeBattlePresentation); \
	DECLARE_FUNCTION(execServerRunRankedQuickMatch); \
	DECLARE_FUNCTION(execServerSaveRankedDefender); \
	DECLARE_FUNCTION(execServerStartFinalStoryBoss); \
	DECLARE_FUNCTION(execServerStartStoryBoss); \
	DECLARE_FUNCTION(execServerBeginSecondStory); \
	DECLARE_FUNCTION(execClientReturnFromSeason); \
	DECLARE_FUNCTION(execServerSaveSeasonAndReturn); \
	DECLARE_FUNCTION(execServerAdvanceSeasonWeek); \
	DECLARE_FUNCTION(execServerStartSeasonMatch); \
	DECLARE_FUNCTION(execClientReceiveSeasonArchive); \
	DECLARE_FUNCTION(execServerRequestSeasonArchive); \
	DECLARE_FUNCTION(execServerRequestSeasonStatus); \
	DECLARE_FUNCTION(execServerRequestRankedStatus); \
	DECLARE_FUNCTION(execClientReceiveAIRivalActivity); \
	DECLARE_FUNCTION(execServerRequestAIRivalActivity); \
	DECLARE_FUNCTION(execServerChallengeAIRival); \
	DECLARE_FUNCTION(execSetRelayDialogueOpen); \
	DECLARE_FUNCTION(execClientSetRelayPresentation); \
	DECLARE_FUNCTION(execClientShowRelayDialogue); \
	DECLARE_FUNCTION(execServerResumeRelayBattle); \
	DECLARE_FUNCTION(execServerStartRelayFieldTraining); \
	DECLARE_FUNCTION(execServerChallengeRelayNPC); \
	DECLARE_FUNCTION(execServerInteractRelayNPC); \
	DECLARE_FUNCTION(execServerRelayFastTravel); \
	DECLARE_FUNCTION(execServerTravelRelayMap); \
	DECLARE_FUNCTION(execServerLeaveRelay); \
	DECLARE_FUNCTION(execServerAdvanceGhostLineQuest); \
	DECLARE_FUNCTION(execServerEnterGhostLine); \
	DECLARE_FUNCTION(execServerAdvanceChroniclesQuest); \
	DECLARE_FUNCTION(execServerEnterChronicles); \
	DECLARE_FUNCTION(execServerEnterRelay); \
	DECLARE_FUNCTION(execCanUseRelayPortal); \
	DECLARE_FUNCTION(execGetRelayPortalTarget); \
	DECLARE_FUNCTION(execGetRelayPortalLocation); \
	DECLARE_FUNCTION(execGetNearestRelayNPC); \
	DECLARE_FUNCTION(execGetRelayNPCLocation); \
	DECLARE_FUNCTION(execGetRelayOrigin); \
	DECLARE_FUNCTION(execGetRelayMapId); \
	DECLARE_FUNCTION(execIsInRelayCampaign); \
	DECLARE_FUNCTION(execIsInGhostLine); \
	DECLARE_FUNCTION(execIsInChronicles); \
	DECLARE_FUNCTION(execGetStoryCampaign); \
	DECLARE_FUNCTION(execIsInRelay); \
	DECLARE_FUNCTION(execClientSetDigiFarmPresentation); \
	DECLARE_FUNCTION(execServerLeaveDigiFarm); \
	DECLARE_FUNCTION(execServerEnterDigiFarm); \
	DECLARE_FUNCTION(execGetDigiFarmScene); \
	DECLARE_FUNCTION(execGetDigiFarmOrigin); \
	DECLARE_FUNCTION(execIsInDigiFarm); \
	DECLARE_FUNCTION(execServerTravelToMap); \
	DECLARE_FUNCTION(execClientAccountAuthenticationResult); \
	DECLARE_FUNCTION(execServerAuthenticateAccount); \
	DECLARE_FUNCTION(execClientHostSessionClosed); \
	DECLARE_FUNCTION(execClientLogoutResult); \
	DECLARE_FUNCTION(execServerRequestLogout); \
	DECLARE_FUNCTION(execIsLogoutPending); \
	DECLARE_FUNCTION(execRequestLogout); \
	DECLARE_FUNCTION(execClientProfileSynchronizationFailed); \
	DECLARE_FUNCTION(execServerRequestProfileSynchronization); \
	DECLARE_FUNCTION(execServerCompleteProfileSnapshot); \
	DECLARE_FUNCTION(execServerAcknowledgeProfileChunk); \
	DECLARE_FUNCTION(execClientProfileSnapshotChunk); \
	DECLARE_FUNCTION(execClientBeginProfileSnapshot); \
	DECLARE_FUNCTION(execRetryProfileSynchronization); \
	DECLARE_FUNCTION(execIsOwnerProfileReady); \
	DECLARE_FUNCTION(execIsAccountAuthenticated);


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ADigimonVenomNXTPlayerController_Statics;
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase);

#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADigimonVenomNXTPlayerController_Statics; \
	friend DIGIMONVENOMNXTRUNTIME_API UClass* ::Z_Construct_UClass_ADigimonVenomNXTPlayerController(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADigimonVenomNXTPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DigimonVenomNXTRuntime"), Z_Construct_UClass_ADigimonVenomNXTPlayerController) \
	DECLARE_SERIALIZER(ADigimonVenomNXTPlayerController) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentBattle=NETFIELD_REP_START, \
		bAccountAuthenticated, \
		RelaySession, \
		FarmSession, \
		NETFIELD_REP_END=FarmSession	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADigimonVenomNXTPlayerController(ADigimonVenomNXTPlayerController&&) = delete; \
	ADigimonVenomNXTPlayerController(const ADigimonVenomNXTPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADigimonVenomNXTPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADigimonVenomNXTPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADigimonVenomNXTPlayerController) \
	NO_API virtual ~ADigimonVenomNXTPlayerController();


#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_52_PROLOG
#define FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_CALLBACK_WRAPPERS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_INCLASS_NO_PURE_DECLS \
	FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h_55_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADigimonVenomNXTPlayerController;

// ********** End Class ADigimonVenomNXTPlayerController *******************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
