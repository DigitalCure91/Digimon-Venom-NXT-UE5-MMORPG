#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAIRivalSubsystem.generated.h"

class ADigimonVenomNXTAIRivalAvatar;
class ADigimonVenomNXTMapZone;
class UDigimonVenomNXTDataSubsystem;

/**
 * Persistent server simulation for up to 1,000 AI tamers. Their progression is record based;
 * replicated avatars are spawned only on maps currently occupied by real players.
 */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAIRivalSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickable() const override;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|AI Rivals")
    TArray<FDigimonAIRivalRecord> GetAllRivals() const;

    /** Server matchmaking view; excludes potentially large collections and scan histories. */
    TArray<FDigimonAIRivalRecord> GetRivalBattleSnapshots() const;

    /** UTC fixed 12-hour window; at most 25 rows per response. Server only. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|AI Rivals")
    FDigimonAIRivalActivityPage GetActivityPage(int32 PageIndex=0, int32 PageSize=20);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|AI Rivals")
    int32 GetActiveRivalCount() const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|AI Rivals")
    TArray<FDigimonAIRivalRecord> GetRivalsOnMap(int32 MapId, int32 MaxResults=24) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|AI Rivals")
    bool GetRival(const FString& RivalId, FDigimonAIRivalRecord& OutRival) const;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|AI Rivals")
    void ForceSimulationStep(int32 MaxRecords=100);

    /** Returns a battle-ready team snapshot from the persistent rival record. */
    bool BuildBattleTeam(const FString& RivalId, FDigimonBattleTeam& OutTeam) const;

    /** Updates the persistent record after a player-vs-rival battle. */
    void RecordBattleResult(const FString& RivalId, bool bRivalWon, int64 VictoryXP=50, int64 VictoryCredits=0);

    /** Live sparring and simulated same-habitat duels share the existing trainer/unranked counters. */
    void RecordUnrankedResult(const FString& RivalId, bool bRivalWon, bool bDraw = false, bool bPersist = true);
    bool IsRivalInLiveBattle(const FString& RivalId) const;

    /** Ranked defence/queue callbacks do not mutate expedition HP or ownership. */
    void RecordRankedResult(const FString& RivalId, bool bRivalWon, bool bDraw=false);

    /** Checkpoint rivals for an authenticated local host console; report disk failures. No RPC/Blueprint entry point. */
    bool SaveForHostConsole();

private:
    FDigimonAIRivalSaveData SaveData;
    TMap<FString, TWeakObjectPtr<ADigimonVenomNXTAIRivalAvatar>> Avatars;
    float SimulationAccumulator = 0.0f;
    float AvatarRefreshAccumulator = 0.0f;
    float SaveAccumulator = 0.0f;
    int32 SimulationCursor = 0;
    bool bLoaded = false;
    bool bDirty = false;
    bool bRecoveredFromBackup = false;
    TArray<FName> StarterSpecies;
    TArray<FDigimonMapRow> ExplorationMaps;
    // One population pass per simulation batch, updated immediately on travel.
    TMap<int32, int32> MapPopulation;
    TArray<int32> TrainingHabitatPopulation;
    // Live server presence only: never invent offline friendship gains after a restart.
    TMap<FString, int64> NextPartyCAMUnix;

    FString SavePath() const;
    bool Load();
    bool Save(bool bExplicitAdminSave = false);
    bool HasServerAuthority() const;
    const UDigimonVenomNXTDataSubsystem* GetData() const;
    void BuildSimulationCatalog();
    void RefreshActivityWindow(int64 Now);
    void RecordActivity(FDigimonAIRivalRecord& Rival, const FDigimonAIRivalActivityCounters& Delta);
    void NormalizeRival(FDigimonAIRivalRecord& Rival);
    void StoreParty(FDigimonAIRivalRecord& Rival);
    void SelectParty(FDigimonAIRivalRecord& Rival, bool bRotate=false, FGuid PreferredLeader=FGuid());
    int32 PartyTrainingLevel(const FDigimonAIRivalRecord& Rival) const;
    void RebuildMapPopulation();
    bool TravelToSuitableMap(FDigimonAIRivalRecord& Rival, FRandomStream& Random, bool bRetreat);
    bool TryMaterialize(FDigimonAIRivalRecord& Rival);
    bool TryEvolve(FDigimonAIRivalRecord& Rival);
    bool TryTrain(FDigimonAIRivalRecord& Rival, FRandomStream& Random);
    bool HealPartyIfNeeded(FDigimonAIRivalRecord& Rival);
    void AwardExperience(FDigimonAIRivalRecord& Rival, int64 Amount, FDigimonAIRivalActivityCounters& Delta);
    void AwardPartyPresenceCAM(FDigimonAIRivalRecord& Rival, int64 Now);
    void SimulateWildBattle(FDigimonAIRivalRecord& Rival, FRandomStream& Random);
    bool TrySimulateUnranked(FDigimonAIRivalRecord& Rival, FRandomStream& Random);
    TSet<FString> LiveBattleRivals;
    FDigimonOwnedPartner MakePartner(FName SpeciesId, EDigimonVariant Variant, int32 Level) const;
    void SetSpeciesMoves(FDigimonOwnedPartner& Partner) const;
    void EnsurePopulation();
    FDigimonAIRivalRecord MakeRival(int32 Index) const;
    void SimulateRival(FDigimonAIRivalRecord& Rival);
    void RefreshVisibleAvatars();
    ADigimonVenomNXTMapZone* FindZone(int32 MapId) const;
    FDigimonOwnedPartner MakePartnerForRival(int32 Level) const;
    FDigimonAIRivalRecord* FindRivalMutable(const FString& RivalId);
};
