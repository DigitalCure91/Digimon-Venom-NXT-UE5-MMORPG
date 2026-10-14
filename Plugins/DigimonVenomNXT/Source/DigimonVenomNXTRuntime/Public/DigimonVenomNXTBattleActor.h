#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTCombatCore.h"
#include "DigimonVenomNXTBattleActor.generated.h"

class ADigimonVenomNXTPlayerState;
class AController;
struct FDigimonAutoBattleResult;

/** Server-authored wild opponent; combat stats and identity are built by the battle actor. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonWildEncounterEntry
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SpeciesId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonVariant Variant = EDigimonVariant::Normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Level = 1;
};

/** Host-only persisted manual battle decision (Season and all private campaigns); never client-authored. */
USTRUCT()
struct FDigimonSeasonBattleCheckpoint
{
    GENERATED_BODY()
    UPROPERTY() int32 Version = 2;
    UPROPERTY() FString ContextId;
    UPROPERTY() FDigimonBattleState State;
    UPROPERTY() TArray<FDigimonBattleCommand> CommandsA;
    UPROPERTY() TArray<FDigimonBattleCommand> CommandsB;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDigimonBattleStateChangedEvent, const FDigimonBattleState&, State);

UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTBattleActor : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTBattleActor();
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

    /** Friendly battles share server time deadlines; independent of either client UI. */
    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    float UnrankedDecisionDeadlineServerTime = 0.0f;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    bool bUnrankedResultSaving = false;


    /** Server-only participant surrender/disconnection. No command-turn requirement. */
    bool ForfeitUnranked(AController* Controller, const FString& Reason);

    /** Current ordered presentation state; replication snapshots bootstrap late clients only. */
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    FDigimonBattleState State;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    TObjectPtr<ADigimonVenomNXTPlayerState> PlayerA;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    TObjectPtr<ADigimonVenomNXTPlayerState> PlayerB;

    /** Optional rival/season/story identifier used by server reward hooks. */
    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    FString BattleContextId;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Battle")
    FDigimonBattleStateChangedEvent OnBattleStateChanged;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    bool InitializeWildBattle(ADigimonVenomNXTPlayerState* Player, FName WildSpecies, EDigimonVariant Variant, int32 WildLevel);

    /** Starts one encounter containing 1-3 independently authored wild opponents. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    bool InitializeWildGroupBattle(ADigimonVenomNXTPlayerState* Player, const TArray<FDigimonWildEncounterEntry>& Encounters);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    bool InitializeTamerBattle(ADigimonVenomNXTPlayerState* InPlayerA, ADigimonVenomNXTPlayerState* InPlayerB, EDigimonBattleKind Kind);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    bool InitializeAITrainerBattle(ADigimonVenomNXTPlayerState* Player, const FDigimonBattleTeam& OpponentTeam, EDigimonBattleKind Kind, const FString& ContextId);


    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    bool SubmitCommand(AController* FromController, const FDigimonBattleCommand& Command, FString& OutError);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Battle")
    bool IsParticipant(const AController* Controller) const;


    /** Restores the exact saved Season decision, including already queued commands. */
    bool RestoreSeasonMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError);
    /** Disconnect cleanup: the persisted checkpoint remains ready for the next connection. */
    void SuspendSeasonMatch();
    bool RestoreRelayMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError);
    void SuspendRelayMatch();
    bool RestoreWorldWildMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError);
    void SuspendWorldWildMatch();

    /** The ranked ledger is committed once before starting this server-paced visible replay. */
    bool InitializeRankedPlayback(ADigimonVenomNXTPlayerState* Player, const FDigimonAutoBattleResult& Result,
        const FString& TrainerName, const FString& OpponentName, const FString& ContextId);
    void StartRankedPlayback(const FString& ResultSummary);
    void RebindRankedPlayer(ADigimonVenomNXTPlayerState* Player);
    void AcknowledgePresentationReady(AController* Controller);

    /** Drains packets received before the local widget attached (slow loads must not skip attacks). */
    TArray<FDigimonBattleState> ConsumePresentationBacklog();
    void ReleasePresentationConsumer();

    /** Destroys a finished battle once no connected Digimon controller still references it. */
    void TryDestroyWhenUnused();

    /** Legacy physical/neutral hook. New skills use ComputeMoveDamage with their canonical metadata. */
    UFUNCTION(BlueprintNativeEvent, Category="Digimon Venom NXT|Battle")
    int32 ComputeDamage(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, int32 Power) const;
    virtual int32 ComputeDamage_Implementation(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, int32 Power) const;

    UFUNCTION(BlueprintNativeEvent, Category="Digimon Venom NXT|Battle")
    int32 ComputeMoveDamage(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, const FDigimonMoveSlot& Move) const;
    virtual int32 ComputeMoveDamage_Implementation(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, const FDigimonMoveSlot& Move) const;

protected:
    UFUNCTION() void OnRep_State();
    UFUNCTION(NetMulticast, Reliable) void MulticastPresentState(const FDigimonBattleState& Packet);

private:
    friend class FDigimonBattleAdapterTest;
    friend class FDigimonUnrankedBattleTest;
    mutable float LastDamageCombo = 1.0f;
    UPROPERTY(ReplicatedUsing=OnRep_State) FDigimonBattleState ReplicatedSnapshot;
    int32 LastDeliveredSerial = INDEX_NONE;
    FGuid LastDeliveredBattleId;
    // Native host audit cursor; never replicated or included in a checkpoint.
    FGuid ConsoleBattleId;
    int32 LastConsolePresentationSerial = INDEX_NONE;
    bool bConsoleResultLogged = false;
    bool bPresentationConsumerAttached = false;
    TArray<FDigimonBattleState> PresentationBacklog;
    void PublishState();
    bool ShouldBufferPresentation() const;
    void CapturePostState(int32 FirstEvent);
    void AdvanceRankedPlayback();
    FTimerHandle RankedPlaybackTimer;
    FTimerHandle BattleSafetyTimer;
    double UnrankedDecisionDeadline = 0.0;
    double UnrankedStartedAt = 0.0;
    void ResetUnrankedDeadline();
    bool bUnrankedSettlementPending = false;
    int32 PendingUnrankedWinner = INDEX_NONE;
    FString PendingUnrankedReason;
    UPROPERTY() TArray<FDigimonPlayerProfile> PendingUnrankedProfiles;
    double NextUnrankedSettlementAttempt = 0.0;
    bool FinishUnrankedMatch(int32 WinningTeam, const FString& Reason, bool bRecordResult);
    void StartBattleSafetyChecks();
    void CheckBattleSafety();
    bool EnsureBattleCanContinue();
    TArray<DigimonVenomNXTCombatCore::Event> RankedActions;
    TArray<FDigimonBattleUnit> RankedRosterA;
    TArray<FDigimonBattleUnit> RankedRosterB;
    int32 NextRankedAction = 0;
    bool bAwaitingRankedPresentationReady = false;
    int32 RankedWinningTeam = INDEX_NONE;
    int32 RankedFinalTurns = 0;
    FString RankedResultSummary;

    bool bSeasonCommandTransaction = false;
    bool bSeasonSettlementFailed = false;
    bool SaveSeasonCheckpoint(); // Shared durable decision commit for Season and all private campaigns.
    // Legacy public method naming is retained; campaign identity is parsed by the
    // shared facade so an unknown prefix can never fall back to Relay.
    bool IsRelayBattle() const;
    EDigimonPrivateCampaign BattleCampaign() const;
    FName BattleNPCId() const;
    bool FinishWorldWildMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards);
    bool FinishPrivateWildMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards);
    bool FinishRelayMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards);
    bool FinishSeasonMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards);

    TMap<int32, FDigimonBattleCommand> PendingA;
    TMap<int32, FDigimonBattleCommand> PendingB;

    FDigimonBattleTeam BuildTeamFromProfile(const FDigimonPlayerProfile& Profile, bool bFullRestore = false, bool bCampaignFinale = false) const;
    FDigimonBattleUnit BuildUnit(const FDigimonOwnedPartner& Partner) const;
    bool ValidateCommand(int32 TeamIndex, const FDigimonBattleCommand& Command, FString& OutError) const;
    int32 LivingActiveCount(const FDigimonBattleTeam& Team) const;
    void AutoFillAICommands();
    void InitializeTimeline();
    bool SelectNextActor();
    bool RebuildRestoredBattle(bool& bUpgraded, FString& OutError);
    void AdvanceOpeningAI();
    void TryResolveRound();
    void ResolveRound();
    void ResolveOne(int32 TeamIndex, const FDigimonBattleCommand& Command);
    void PromoteBench(FDigimonBattleTeam& Team);
    bool IsTeamDefeated(const FDigimonBattleTeam& Team) const;
    void FinishBattle(int32 WinningTeam, const FString& Reason, bool bGrantRewards = true);
    void SaveParticipantProfiles();
    void RewardWildVictory();
    void RecordWildDefeat(const FDigimonBattleUnit& Unit);
    FString AwardWildMastery(FDigimonPlayerProfile& Profile);
};
