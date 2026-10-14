#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAIRivalAvatar.generated.h"

class UPaperFlipbookComponent;
class USceneComponent;
class UDigimonVenomNXTTamerAnimationSet;
class ADigimonVenomNXTPartnerFollower;
class UDigimonVenomNXTNameplateComponent;

/** Lightweight replicated visual proxy for a persistent simulated AI tamer record. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTAIRivalAvatar : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTAIRivalAvatar();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    TObjectPtr<USceneComponent> Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    TObjectPtr<UPaperFlipbookComponent> Sprite;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    TObjectPtr<UDigimonVenomNXTNameplateComponent> Nameplate;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    FString RivalId;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    FString DisplayName;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    int32 MapId = 1;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    int32 TamerLevel = 1;

    /** One companion, bound to the persistent record's real first party instance. */
    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|AI Rival")
    TObjectPtr<ADigimonVenomNXTPartnerFollower> LeaderFollower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|AI Rival")
    float PatrolSpeed = 115.0f;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|AI Rival")
    void InitializeAvatar(const FString& InRivalId, const FString& InDisplayName, int32 InMapId, int32 InTamerLevel, const FBox& InPatrolBounds);

    /** Pass an invalid partner to remove the companion when the party is empty. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|AI Rival")
    void RefreshLeaderFollower(const FDigimonOwnedPartner& Partner);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|AI Rival")
    bool IsForRival(const FString& InRivalId) const { return RivalId == InRivalId; }

protected:
    UFUNCTION() void OnRep_Identity();
    UFUNCTION(BlueprintImplementableEvent, Category="Digimon Venom NXT|AI Rival")
    void BP_OnRivalIdentityChanged(const FString& NewRivalId, const FString& NewDisplayName, int32 NewLevel);

private:
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTTamerAnimationSet> AnimationSet;
    FString LoadedAnimationStyle;
    bool bHasWalkablePlacement = false;
    FVector PreviousVisualLocation = FVector::ZeroVector;
    float WalkVisualRemaining = 0.0f;
    void UpdateWalkVisual(float DeltaSeconds);
    FBox PatrolBounds = FBox(ForceInit);
    bool IsInsidePatrolBounds(const FVector& Location) const;
    bool FindWalkablePlacement(FVector& OutLocation) const;
    FVector PatrolTarget = FVector::ZeroVector;
    float RetargetTimer = 0.0f;
    void ChoosePatrolTarget();
};
