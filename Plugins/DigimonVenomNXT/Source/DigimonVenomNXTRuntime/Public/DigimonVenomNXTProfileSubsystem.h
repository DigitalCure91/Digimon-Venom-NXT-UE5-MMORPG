#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTProfileSubsystem.generated.h"

class UDigimonVenomNXTDataSubsystem;

UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTProfileSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    bool LoadProfile(const FString& AccountId, const FString& Username, FDigimonPlayerProfile& OutProfile);

    /** Accepts authoritative progress. With autosaves OFF this retains a value snapshot in server memory only. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    bool SaveProfile(const FDigimonPlayerProfile& Profile);

    /** Server-owned in-memory handoff. Never serializes or writes files; used for every ordinary logout. */
    bool RetainProfile(const FDigimonPlayerProfile& Profile);
    /** Authenticated local admin only. Includes profiles belonging to disconnected players. */
    bool SaveForHostConsole(int32& OutSavedProfiles, FString& Error);
    /** Timer hook; cannot bypass the global autosave policy. */
    bool FlushAutomaticSaves(FString& Error);

    /** Migrates a candidate without altering a live or saved battle. The caller saves before publishing. */
    static bool ReconcileCombatBalance(FDigimonPlayerProfile& Candidate,
        const UDigimonVenomNXTDataSubsystem* Data, bool bLiveBattle = false);

    /** Reads private history through the last accepted profile week, including pending server-memory records. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    bool LoadSeasonArchive(const FDigimonPlayerProfile& Profile, int32 Page, int32 PageSize, FDigimonSeasonArchivePage& OutPage);

    /** For paired battle results; preserves the market and advances both revisions only on acceptance. */
    bool CommitProfileGroup(TArray<FDigimonPlayerProfile>& Candidates, FString& Error);
    /** Atomic transaction acceptance. With autosaves OFF, true means all participants and the market
     * are retained together in server memory. With autosaves ON, true means journal intent is durable,
     * even if replay is temporarily required. Admin checkpoints persist the full pending set.
     * Candidates must contain current live profiles with CommerceRevision advanced exactly once.
     * Callers publish all candidates after true; no candidate is published after false. */
    bool CommitCommerce(const TArray<FDigimonPlayerProfile>& Candidates, const FString& MarketJson, FString& Error);
    /** Replays a durable pending intent before exposing a market or profile. Fails closed on I/O errors. */
    bool LoadCommerceMarket(FString& Json, bool& bExists, FString& Error);
    bool IsCommerceStorageReady();
    bool LoadExistingCommerceProfile(const FString& AccountId, FDigimonPlayerProfile& OutProfile);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    bool DeleteProfile(const FString& AccountId);

#if WITH_DEV_AUTOMATION_TESTS
    /** Isolates transaction fault injection from real host progress. Never compiled into shipping. */
    void SetStorageRootForTests(const FString& Root) { TestStorageRoot = Root; }
    void SetAutomaticSavingForTests(bool bEnabled) { TestAutomaticSaving = bEnabled; }
    bool FlushForTests(FString& Error);
#endif
private:
#if WITH_DEV_AUTOMATION_TESTS
    FString TestStorageRoot;
    TOptional<bool> TestAutomaticSaving;
#endif
    // Value snapshots outlive PlayerController/PlayerState destruction, but not the server process.
    UPROPERTY(Transient)
    TMap<FString, FDigimonPlayerProfile> SessionProfiles;
    UPROPERTY(Transient)
    TMap<FString, FDigimonSeasonArchive> DeferredSeasonRecords;
    TSet<FString> DirtySessionProfiles;
    FString SessionMarketJson;
    bool bHasSessionMarket = false;
    bool bMarketDirty = false;
    bool AutomaticSavingEnabled() const;
    void RetainProfileLocked(const FDigimonPlayerProfile& Profile);
    bool FlushDeferredLocked(FString& Error);
    bool RecoverCommerceLocked();
    bool ApplyCommerceJournalLocked(const FString& Journal);
    bool CheckCommerceFenceLocked(const FDigimonPlayerProfile& Profile, bool bAdvance) const;
    FString CommercePath(const TCHAR* Filename) const;
    FString ProfilePath(const FString& AccountId) const;
    FString SeasonArchiveDirectory(const FString& AccountId, const FString& CareerId) const;
    bool WriteSeasonArchive(const FDigimonPlayerProfile& Profile) const;
};
