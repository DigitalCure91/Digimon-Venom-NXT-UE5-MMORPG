#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTProfileSyncCore.h"
#include "DigimonVenomNXTPlayerController.generated.h"

class ADigimonVenomNXTBattleActor;
class UDigimonVenomNXTGameHUDWidget;
class UDigimonVenomNXTBattleWidget;
class ADigimonVenomNXTLocalMapRenderer;
class ADigimonVenomNXTFarmScene;
class ADigimonVenomNXTRelayScene;
class UDigimonVenomNXTSocialComponent;
class UDigimonVenomNXTTradeComponent;
class UDigimonVenomNXTUnrankedComponent;
class UDigimonVenomNXTProfileSyncWidget;
class ADigimonVenomNXTPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDigimonClientMessageEvent, const FString&, Title, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDigimonChatReceivedEvent, const FDigimonChatMessage&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDigimonCurrentBattleChangedEvent, ADigimonVenomNXTBattleActor*, Battle);

/** One owner-only replication property keeps private location and active state atomic. */
USTRUCT()
struct FDigimonFarmSession
{
    GENERATED_BODY()
    UPROPERTY() bool bActive = false;
    UPROPERTY() FVector Origin = FVector::ZeroVector;
    UPROPERTY() uint64 Revision = 0;
};

/** An atomic owner-only campaign session. Public habitat identity remains untouched. */
USTRUCT()
struct FDigimonRelaySession
{
    GENERATED_BODY()
    UPROPERTY() bool bActive = false;
    UPROPERTY() EDigimonPrivateCampaign Campaign = EDigimonPrivateCampaign::Relay;
    UPROPERTY() int32 MapId = 1;
    UPROPERTY() FVector Origin = FVector::ZeroVector;
    UPROPERTY() uint64 Revision = 0;
};

/**
 * Owner RPC surface for Digimon Venom NXT. UI and Blueprint code send intent through this controller;
 * authoritative gameplay mutations are performed on the server.
 */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTPlayerController();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Community")
    TObjectPtr<UDigimonVenomNXTSocialComponent> SocialComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Community")
    TObjectPtr<UDigimonVenomNXTTradeComponent> TradeComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Community")
    TObjectPtr<UDigimonVenomNXTUnrankedComponent> UnrankedComponent;



    UPROPERTY(ReplicatedUsing=OnRep_CurrentBattle, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    TObjectPtr<ADigimonVenomNXTBattleActor> CurrentBattle;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Accounts")
    bool bAccountAuthenticated = false;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool IsAccountAuthenticated() const { return bAccountAuthenticated; }

    /** True only after this connection has a complete, identity-checked owner profile. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool IsOwnerProfileReady() const { return bOwnerProfileReady; }

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Accounts")
    void RetryProfileSynchronization();

    void QueueOwnerProfileSynchronization();
    bool HasCommittedLogout() const { return bLogoutServerCommitted; }

    UFUNCTION(Client, Reliable)
    void ClientBeginProfileSnapshot(FGuid TransferId, int32 Protocol, int64 Revision, const FString& AccountId,
        int32 ByteCount, int32 JsonByteCount, int64 Checksum);
    UFUNCTION(Client, Reliable)
    void ClientProfileSnapshotChunk(FGuid TransferId, int32 Offset, const TArray<uint8>& Bytes);
    UFUNCTION(Server, Reliable)
    void ServerAcknowledgeProfileChunk(FGuid TransferId, int32 Offset);
    UFUNCTION(Server, Reliable)
    void ServerCompleteProfileSnapshot(FGuid TransferId, int64 Revision, bool bAccepted);
    UFUNCTION(Server, Reliable)
    void ServerRequestProfileSynchronization();
    UFUNCTION(Client, Reliable)
    void ClientProfileSynchronizationFailed(const FString& Message);

    /** Local UI entry point. Ordinary logout acknowledges memory retention; admin logout also flushes every pending disk checkpoint. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Accounts")
    bool RequestLogout(FString& OutError);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool IsLogoutPending() const { return bLogoutPending; }

    /** Local host console only; checkpoints online/disconnected profiles and server ledgers before restarting. */
    bool PrepareHostWorldRestart(FString& OutError);

    UFUNCTION(Server, Reliable)
    void ServerRequestLogout(FGuid RequestId);

    UFUNCTION(Client, Reliable)
    void ClientLogoutResult(FGuid RequestId, bool bSuccess, const FString& Message);

    /** Sent only after the host has checkpointed online/disconnected profiles and server ledgers. */
    UFUNCTION(Client, Reliable)
    void ClientHostSessionClosed(const FString& Message);

    /** First RPC sent after connecting. Account data is validated entirely by the UE host SaveGame database. */
    UFUNCTION(Server, Reliable, Category="Digimon Venom NXT|Accounts")
    void ServerAuthenticateAccount(bool bCreateAccount, const FString& Username, const FString& Password);

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Accounts")
    void ClientAccountAuthenticationResult(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId);

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI")
    FDigimonClientMessageEvent OnClientMessage;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Chat")
    FDigimonChatReceivedEvent OnChatReceived;

    /** Session-local history survives menu changes and messages arriving before HUD creation. */
    UPROPERTY(Transient, BlueprintReadOnly, Category="Digimon Venom NXT|Chat")
    TArray<FDigimonChatMessage> WorldChatHistory;

    /** Removes previously received messages when the owner changes their ignore list. */
    void RefreshIgnoredChat();

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Battle")
    FDigimonCurrentBattleChangedEvent OnCurrentBattleChanged;

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|World")
    void ServerTravelToMap(int32 MapId);



    /** Owner-only private farm session. The public map remains the saved return habitat. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|DigiFarm")
    bool IsInDigiFarm() const { return FarmSession.bActive; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|DigiFarm")
    FVector GetDigiFarmOrigin() const { return FarmSession.Origin; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|DigiFarm")
    ADigimonVenomNXTFarmScene* GetDigiFarmScene() const { return DigiFarmScene; }

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerEnterDigiFarm();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerLeaveDigiFarm();

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ClientSetDigiFarmPresentation(bool bInside, FVector Origin, int32 ReturnMapId, uint64 Revision);

    /** Called after authentication/spawn and immediately before durable profile writes. */
    void RestoreDigiFarmAfterLogin();
    void CaptureDigiFarmPosition();

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") bool IsInRelay() const { return RelaySession.bActive && !FarmSession.bActive; }
    /** Compatibility name: true inside any private story world; privacy guards intentionally share it. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Story") EDigimonPrivateCampaign GetStoryCampaign() const { return RelaySession.Campaign; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Story") bool IsInChronicles() const { return IsInRelay() && GetStoryCampaign() == EDigimonPrivateCampaign::ParadoxChronicles; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Story") bool IsInGhostLine() const { return IsInRelay() && GetStoryCampaign() == EDigimonPrivateCampaign::GhostLine; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Story") bool IsInRelayCampaign() const { return IsInRelay() && GetStoryCampaign() == EDigimonPrivateCampaign::Relay; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") int32 GetRelayMapId() const { return RelaySession.MapId; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") FVector GetRelayOrigin() const { return RelaySession.Origin; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") FVector GetRelayNPCLocation(FName NPCId) const;
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") FName GetNearestRelayNPC() const;
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") FVector GetRelayPortalLocation(bool bForward) const;
    /** Destination of the visible portal, or INDEX_NONE. Includes the completed GhostLine return to HQ. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") int32 GetRelayPortalTarget(bool bForward) const;
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") bool CanUseRelayPortal(bool bForward) const;
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerEnterRelay();
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story") void ServerEnterChronicles();
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story") void ServerAdvanceChroniclesQuest(FName NPCId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story") void ServerEnterGhostLine();
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story") void ServerAdvanceGhostLineQuest(FName NPCId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerLeaveRelay();
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerTravelRelayMap(int32 MapId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerRelayFastTravel(int32 MapId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerInteractRelayNPC(FName NPCId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerChallengeRelayNPC(FName NPCId);
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerStartRelayFieldTraining();
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Relay") void ServerResumeRelayBattle();
    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Relay") void ClientShowRelayDialogue(FName NPCId, const FString& Dialogue, EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& ConfirmedProgress);
    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Relay") void ClientSetRelayPresentation(EDigimonPrivateCampaign Campaign, bool bInside, int32 MapId, FVector Origin, uint64 Revision);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Relay") void SetRelayDialogueOpen(bool bOpen);
    bool ValidateRelayNPCInteraction(FName NPCId, FString& OutError) const;
    bool IsRelayLocationWalkable(const FVector& Location) const;
    bool IsRelaySegmentWalkable(const FVector& From, const FVector& To) const;
    void CaptureRelayPosition();
    void RestoreRelayAfterLogin();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|AI Rivals")
    void ServerChallengeAIRival(const FString& RivalId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|AI Rivals")
    void ServerRequestAIRivalActivity(int32 PageIndex, int32 PageSize);

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|AI Rivals")
    void ClientReceiveAIRivalActivity(const FDigimonAIRivalActivityPage& Page);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Ranked")
    void ServerRequestRankedStatus();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Season")
    void ServerRequestSeasonStatus();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Season")
    void ServerRequestSeasonArchive(int32 PageIndex);

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Season")
    void ClientReceiveSeasonArchive(const FDigimonSeasonArchivePage& Page);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Season")
    void ServerStartSeasonMatch();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Season")
    void ServerAdvanceSeasonWeek();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Season")
    void ServerSaveSeasonAndReturn();

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Season")
    void ClientReturnFromSeason();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story")
    void ServerBeginSecondStory();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story")
    void ServerStartStoryBoss(int32 Chapter);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Story")
    void ServerStartFinalStoryBoss();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Ranked")
    void ServerSaveRankedDefender();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Ranked")
    void ServerRunRankedQuickMatch();

    /** Sent only after the local battle widget has bound its presentation stream. */
    UFUNCTION(Server, Reliable, Category="Digimon Venom NXT|Battle")
    void ServerAcknowledgeBattlePresentation(ADigimonVenomNXTBattleActor* BattleActor);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Battle")
    void ServerSubmitBattleCommand(const FDigimonBattleCommand& Command);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Battle")
    void ServerLeaveFinishedBattle();

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Chat")
    void ServerSendLocalChat(const FString& Message);

    /** Canonical WORLD entry point. The legacy LocalChat RPC forwards to the same server path. */
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Chat")
    void ServerSendWorldChat(const FString& Message);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Persistence")
    void ServerRequestSave();

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|UI")
    void ClientShowMessage(const FString& Title, const FString& Message);

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Season")
    void ClientReturnToSeason();

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Chat")
    void ClientReceiveLocalChat(const FDigimonChatMessage& Message);

    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|Audio")
    void ClientPlayExplorationMusic(int32 MapId);

    /** Server confirms the operation; playback is local and receipt-deduplicated. */
    UFUNCTION(Client, Reliable)
    void ClientPlayAudioCue(EDigimonAudioCue Cue, FGuid ReceiptId);

    /** Makes only this client's current habitat ground visible, preventing cross-map overlap/z-fighting. */
    UFUNCTION(Client, Reliable, Category="Digimon Venom NXT|World")
    void ClientSetActiveMapPresentation(int32 MapId);

    /** Server-only. Marks whether this connection has passed host account authentication. */
    void SetAccountAuthenticatedServer(bool bAuthenticated);

    /** Server-only. Sets the replicated owner battle pointer. */
    void SetCurrentBattleServer(ADigimonVenomNXTBattleActor* Battle);


    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|UI")
    UDigimonVenomNXTGameHUDWidget* GetNativeHUDWidget() const { return GameHUDWidget; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|UI")
    UDigimonVenomNXTBattleWidget* GetNativeBattleWidget() const { return BattleWidget; }

    /** Local field menu state. Closed means the world owns the screen and movement is active. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void SetFieldMenuOpen(bool bOpen);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void ToggleFieldMenu();

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|UI")
    bool IsFieldMenuOpen() const { return bFieldMenuOpen; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|World")
    bool IsFieldInputBlocked() const;

    /** Field visibility follows gameplay/menu state; chat focus alone does not hide the map. */
    bool IsFieldPresentationBlocked() const { return !IsOwnerProfileReady() || bLogoutPending || bFieldMenuOpen || bRelayDialogueOpen || CurrentBattle != nullptr || HasPendingStoryBattle() || HasPendingWorldBattle() || bFarmPresentationFailurePending || bRelayPresentationFailurePending || bRelayPresentationWaiting; }


    /** Last authoritative map RPC takes precedence over a late replicated profile. */
    int32 GetLocalMusicMapId() const;

    /** Authority-side walking encounter trigger used by the tamer distance tracker. */
    bool TryStartWalkingWildEncounter();

protected:
    UFUNCTION() void OnRep_CurrentBattle();
    UFUNCTION() void OnRep_DigiFarmSession();
    UFUNCTION() void OnRep_RelaySession();

private:
    void ActivateSynchronizedAccount();
    bool bAuthenticatedWorldEntered = false;
    void TickProfileSynchronization();
    void StartOwnerProfileSnapshot();
    void PumpOwnerProfileSnapshot();
    void TryApplyOwnerProfileSnapshot();
    void FinishOwnerProfilePresentation();
    void ShowProfileSynchronizationStatus(const FString& Message, bool bCanRetry);
    void ClearProfileSynchronization();
    void RejectIncomingProfileSnapshot(const FString& Message);
    void FailOutgoingProfileSnapshot(const FString& Message);
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTProfileSyncWidget> ProfileSyncWidget;
    UPROPERTY(Transient) FDigimonPlayerProfile LastQueuedOwnerProfile;
    UPROPERTY(Transient) FDigimonPlayerProfile PendingOwnerProfile;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> AppliedOwnerProfileState;
    DigimonVenomNXTProfileSyncCore::SendWindow ProfileSendWindow;
    DigimonVenomNXTProfileSyncCore::Receiver ProfileReceiver;
    TArray<uint8> OutgoingProfileBytes;
    FGuid OutgoingProfileTransferId;
    FGuid IncomingProfileTransferId;
    FString ExpectedProfileAccountId;
    int64 OutgoingProfileRevision = 0;
    int64 IncomingProfileRevision = 0;
    int64 AppliedProfileRevision = 0;
    int32 IncomingProfileJsonBytes = 0;
    uint32 IncomingProfileChecksum = 0;
    int32 ProfileSyncFailureCount = 0;
    int32 ProfileAutomaticRetries = 0;
    bool bOwnerProfileReady = false;
    bool bOwnerProfileDirty = true;
    bool bOwnerProfilePending = false;
    double LastProfileSnapshotStarted = -1000.0;
    double LastProfileServerProgress = 0.0;
    double LastProfileComparison = -1000.0;
    double LastProfileClientProgress = 0.0;
    double LastProfileResyncRequest = -1000.0;
    double LastProfileServerResyncRequest = -1000.0;

    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTGameHUDWidget> GameHUDWidget;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTBattleWidget> BattleWidget;
    UPROPERTY(Transient) TObjectPtr<ADigimonVenomNXTLocalMapRenderer> LocalMapRenderer;
    UPROPERTY(Transient) TObjectPtr<ADigimonVenomNXTFarmScene> DigiFarmScene;
    UPROPERTY(Transient) TObjectPtr<ADigimonVenomNXTRelayScene> RelayScene;
    UPROPERTY(ReplicatedUsing=OnRep_RelaySession) FDigimonRelaySession RelaySession;
    FDigimonRelaySession AppliedLocalRelaySession;
    int32 RelaySlot = INDEX_NONE;
    bool bRelayDialogueOpen = false;
    bool bRelayPresentationFailurePending = false;
    bool bRelayPresentationWaiting = false;
    int32 PresentedRelayMapId = INDEX_NONE;
    FVector PresentedRelayOrigin = FVector::ZeroVector;
    mutable int32 PlacementMapId = INDEX_NONE;
    mutable EDigimonPrivateCampaign PlacementCampaign = EDigimonPrivateCampaign::Relay;
    EDigimonPrivateCampaign PresentedCampaign = EDigimonPrivateCampaign::Relay;
    mutable TMap<FName, FVector> RelayNPCLocalLocations;
    mutable FVector RelayArrivalLocal = FVector::ZeroVector;
    mutable FVector RelayEntryLocal = FVector::ZeroVector;
    mutable FVector RelayExitLocal = FVector::ZeroVector;
    double LastRelayInteractionTime = -1000.0;
    bool AllocateRelayOrigin();
    bool EnterCampaignServer(EDigimonPrivateCampaign Campaign, bool bRestoreSavedSession, FString& OutError);
    bool HasPendingStoryBattle() const;
    bool HasPendingWorldBattle() const;
    bool LeaveRelayServer(FString& OutError);
    bool PrepareRelayPlacements(FString* OutError = nullptr) const;
    void RefreshRelayPresentation();
    void PublishRelaySession();
    void TravelRelayMapServer(int32 MapId, bool bRequirePortal);
    bool IsActiveRelayNPC(FName NPCId) const;
    FString PresentedRelayCast;
    UPROPERTY(ReplicatedUsing=OnRep_DigiFarmSession) FDigimonFarmSession FarmSession;
    FDigimonFarmSession AppliedLocalFarmSession;
    int32 DigiFarmSlot = INDEX_NONE;
    bool bLocalFarmPresentationActive = false;
    bool bFarmPresentationFailurePending = false;
    FString PendingFarmMessage;
    FVector PresentedFarmOrigin = FVector::ZeroVector;
    float FarmResidentRefreshElapsed = 0.0f;
    TWeakObjectPtr<ADigimonVenomNXTBattleActor> MusicBattle;
    int32 LocalMusicMapId = INDEX_NONE;
    double LastWorldChatSendTime = -1000.0;
    double LastWorldChatFeedbackTime = -1000.0;
    double LastWildEncounterRequestTime = -1000.0;
    double LastActivityRequestTime = -1000.0;
    double LastRivalChallengeRequestTime = -1000.0;
    double LastRankedStatusRequestTime = -1000.0;
    double LastSeasonStatusRequestTime = -1000.0;
    double LastSeasonArchiveRequestTime = -1000.0;
    double LastRankedMatchRequestTime = -1000.0;
    bool bFieldMenuOpen = false;
    bool bLogoutPending = false;
    bool bLogoutServerCommitted = false;
    double LastLogoutServerRequestTime = -1000.0;
    FGuid PendingLogoutRequestId;
    FGuid CommittedLogoutRequestId;
    FTimerHandle LogoutTimeoutTimer;
    FTimerHandle HostLogoutTravelTimer;
    void LogoutAcknowledgementTimedOut();
    void CompleteAcknowledgedLogout();

    void SubmitPendingAccountAuthentication();
    void CreateNativeHUD();
    void RefreshBattleUI();
    void ApplyFieldInputMode();
    bool EnterDigiFarmServer(bool bRestoreSavedSession, FString& OutError);
    bool LeaveDigiFarmServer(FString& OutError);
    bool AllocateDigiFarmOrigin();
    void RefreshDigiFarmPresentation();
    void RefreshLocalActorPrivacy();
    bool RequirePublicFieldForBattle();
};
