#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTRankedSubsystem.generated.h"

class ADigimonVenomNXTPlayerState;
class ADigimonVenomNXTGameState;
class ADigimonVenomNXTBattleActor;

/** Authoritative seasonal ladder: real auto combat, durable energy and idempotent payouts. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTRankedSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Ranked")
    FString GetCurrentSeasonId() const { return RankedData.SeasonId; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Ranked")
    TArray<FDigimonRankedPublicEntry> GetTop100() const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Ranked")
    static EDigimonRankedGrade GetGradeForRating(int32 Rating);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Ranked")
    static FString GetGradeLabel(EDigimonRankedGrade Grade);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Ranked")
    bool SaveDefenderLineup(ADigimonVenomNXTPlayerState* PlayerState, FString& OutMessage);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Ranked")
    bool RunQuickMatch(ADigimonVenomNXTPlayerState* Challenger, FString& OutMessage);

    /** Returns a visible automatic battle; success never means an instant result screen. */
    bool StartRankedMatch(ADigimonVenomNXTPlayerState* Challenger, ADigimonVenomNXTBattleActor*& OutBattle, FString& OutMessage);

    /** Bots may queue against actual human/bot defense snapshots; never receive currency. */
    bool RunRivalQuickMatch(const FString& RivalId);

    /** Claims only after writing both currency and the unique claim receipt to the profile. */
    void ClaimPendingReward(ADigimonVenomNXTPlayerState* PlayerState);
    void RefreshPlayerState(ADigimonVenomNXTPlayerState* PlayerState);

    /** Periodic server hook: season rollover, online rewards, energy and replicated standings. */
    void RefreshSeasonAndGameState(ADigimonVenomNXTGameState* GameState);

    /** Authenticated local admin checkpoint; no automatic save-policy bypass elsewhere. */
    bool SaveForHostConsole();

private:
    FDigimonRankedSaveData RankedData;
    bool bLoaded = false;
    bool bLoadFailed = false;
    int64 LastRivalRefreshUnix = 0;
    int64 LastSavedUnix = 0;
    bool bDirty = false;
    TMap<FString, FDigimonRankedSaveData> DeferredArchives;
    // The durable ledger owns the outcome; these transient actors own presentation only.
    TMap<FString, TWeakObjectPtr<ADigimonVenomNXTBattleActor>> ActivePresentations;
    TMap<FString, FDigimonRankedCareer> VisibleCareersBeforePresentation;

    bool IsAuthoritativeWorld() const;
    FString SavePath() const;
    FString ArchivePath(const FString& SeasonId) const;
    bool Load();
    bool Save(bool bExplicitAdminSave = false);
    bool RollSeasonIfNeeded();
    void AwardSeasonRewards();
    void RefreshRivalEntries(bool bForce = false);
    FDigimonRankedLadderEntry* FindEntry(const FString& AccountId);
    FDigimonRankedLadderEntry& FindOrAddEntry(ADigimonVenomNXTPlayerState* PlayerState);
    int32 TeamPower(const TArray<FDigimonOwnedPartner>& Team) const;
    int32 CalculateRubyReward(const FDigimonRankedLadderEntry& Entry, int32 Placement) const;
    void RefreshEnergy(FDigimonRankedLadderEntry& Entry, int64 Now) const;
    void SyncProfile(ADigimonVenomNXTPlayerState* PlayerState, FDigimonRankedLadderEntry& Entry) const;
    bool ResolveMatch(const FString& AccountId, const TArray<FDigimonOwnedPartner>& AttackingTeam, FString& OutMessage,
        ADigimonVenomNXTPlayerState* Challenger = nullptr, ADigimonVenomNXTBattleActor* Playback = nullptr);
    void PushToGameState(ADigimonVenomNXTGameState* GameState) const;
};
