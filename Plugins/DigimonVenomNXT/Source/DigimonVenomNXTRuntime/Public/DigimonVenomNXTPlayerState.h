#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTHealingTypes.h"
#include "DigimonVenomNXTPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigimonProfileChangedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDigimonHealResultEvent, const FDigimonHealReceipt&, Receipt);

enum class EDigimonAudioCue : uint8;

UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTPlayerState : public APlayerState
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTPlayerState();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaSeconds) override;

    // Disk state is not one unbounded actor-channel property. The owner receives
    // complete checked snapshots through its controller; public presence stays replicated.
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|Profile")
    FDigimonPlayerProfile Profile;

    UPROPERTY(ReplicatedUsing=OnRep_Profile, BlueprintReadOnly, Category="Digimon Venom NXT|DigiDex")
    FDigimonScanPolicy ScanPolicy;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Profile")
    FDigimonPublicPlayerSnapshot PublicSnapshot;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Profile")
    FDigimonProfileChangedEvent OnProfileChanged;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|DigiLab")
    FDigimonHealResultEvent OnDigiLabHealResult;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Profile")
    bool HasStarter() const { return Profile.Collection.Num() > 0; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Party")
    bool GetPartner(FGuid InstanceId, FDigimonOwnedPartner& OutPartner) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Scan")
    int32 GetScanPercent(FName SpeciesId, EDigimonVariant Variant) const;

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Starter")
    void ServerChooseStarter(FName SpeciesId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Party")
    void ServerSetParty(const TArray<FGuid>& NewParty);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Tamer")
    void ServerSetTamerStyle(FName TamerStyleId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiLab")
    void ServerMaterialize(FName SpeciesId, EDigimonVariant Variant);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiLab")
    void ServerHealAll();

    /** UI request identity prevents duplicate recovery on a retried reliable action. */
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiLab")
    void ServerRequestDigiLabHeal(FGuid RequestId);

    UFUNCTION(Client, Reliable)
    void ClientDigiLabHealResult(const FDigimonHealReceipt& Receipt);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerFeedABIMeat(FGuid InstanceId, EDigimonCurrency Currency);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Economy")
    void ServerConvertDigiRubiesToCredits(int32 RubyAmount);


    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Shop")
    void ServerPurchaseItem(FName ItemId, EDigimonCurrency Currency, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Items")
    void ServerUseHealingItem(FGuid InstanceId, FName ItemId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerSetFarmResident(FGuid InstanceId, bool bResident);

    /** In-world care: only the authenticated owner's currently placed residents. */
    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerFeedFarmResident(FGuid InstanceId, FName ItemId, EDigimonTrainingStat Stat);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerUseCAMTreat(FGuid InstanceId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Items")
    void ServerUseABIMeat(FGuid InstanceId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|DigiFarm")
    void ServerUseDigiMeat(FGuid InstanceId, EDigimonTrainingStat Stat);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Evolution")
    void ServerEvolve(FGuid InstanceId, FName TargetSpeciesId);

    UFUNCTION(BlueprintCallable, Server, Reliable, Category="Digimon Venom NXT|Evolution")
    void ServerDeEvolve(FGuid InstanceId, FName TargetSpeciesId);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Inventory")
    int32 GetInventoryQuantity(FName ItemId) const;

    /** True while a live battle or a saved Season battle decision locks this profile. */
    bool HasActiveBattle() const;

    /** Server-only campaign mutation helpers used by GameMode/Battle/Ranked systems. */
    void BeginSecondStory();
    void RecordStoryBossVictory(int32 Chapter);
    void RecordFinalStoryVictory();
    void MarkProfileChanged();

    void InitializeServerProfile(const FDigimonPlayerProfile& InProfile);
    bool HasInitializedServerProfile() const { return HasAuthority() && !InitializedServerAccountId.IsEmpty() && Profile.AccountId == InitializedServerAccountId; }
    bool ApplyOwnerProfileSnapshot(const FDigimonPlayerProfile& InProfile, const FString& ExpectedAccountId);
    void AwardScan(FName SpeciesId, EDigimonVariant Variant, int32 BaseAmount, bool bAllowMasteryBonus = true);
    void AwardCredits(int64 Amount);
    void AwardDigiRubies(int32 Amount);
    void SetCurrentMap(int32 MapId);
    void RefreshPublicSnapshot();
    /** Repairs only a complete party wipeout; partial damage and boxed partners are untouched. */
    bool RecoverDefeatedParty();
    void ApplyBattleTeamResult(const FDigimonBattleTeam& Team, bool bRestoreDefeatedParty = false);
    bool ConsumeBattleItem(FName ItemId, int32 Amount = 1);
    /** Applies the shared XP rules once per owned partner and returns a battle-result summary. */
    FString AwardExperienceToParty(int64 ExperiencePerPartner);

protected:
    FString InitializedServerAccountId;
    UFUNCTION() void OnRep_Profile();
    FDigimonOwnedPartner* FindPartnerMutable(const FGuid& InstanceId);
    FDigimonScanRecord* FindScanMutable(FName SpeciesId, EDigimonVariant Variant);
    FDigimonInventoryEntry* FindInventoryMutable(FName ItemId);
    FDigimonOwnedPartner MakePartner(FName SpeciesId, EDigimonVariant Variant, int32 InitialLevel = 1) const;
    bool ReconcileCombatBalance();
    bool UpgradeLegacyStarter();
    bool ReconcileProgression();
    bool ReconcileDigiDexHistory();
    void RefreshScanPolicy();
    void NotifyProgression(const FString& Title, const FString& Message) const;
    void NotifyProgression(const FString& Title, const FString& Message, EDigimonAudioCue Cue) const;
    void TransformPartner(FGuid InstanceId, FName TargetSpeciesId, bool bDeEvolution);
    void ProcessDigiLabHeal(const FGuid& RequestId, bool bLegacyRequest);
    UPROPERTY(Transient) TArray<FDigimonHealReceipt> RecentDigiLabHealReceipts;
    double LastDigiLabHealRequestTime = -100.0;
    TMap<FGuid, float> PartyCAMElapsed;
    void AddInventory(FName ItemId, int32 Amount);
    bool ConsumeInventory(FName ItemId, int32 Amount = 1);
};
