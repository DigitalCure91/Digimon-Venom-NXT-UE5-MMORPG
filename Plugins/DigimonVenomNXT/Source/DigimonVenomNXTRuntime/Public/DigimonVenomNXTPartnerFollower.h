#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTPartnerFollower.generated.h"

class ADigimonVenomNXTTamerCharacter;
class ADigimonVenomNXTAIRivalAvatar;
class UDigimonVenomNXTPartnerAnimationSet;

/** Replicated companion representing the actual first party member of a player or AI rival. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTPartnerFollower : public APaperCharacter
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTPartnerFollower();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    FGuid InstanceId;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    FName SpeciesId = NAME_None;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    EDigimonVariant Variant = EDigimonVariant::Normal;

    UPROPERTY(ReplicatedUsing=OnRep_Identity, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    int32 PartnerLevel = 1;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    TObjectPtr<ADigimonVenomNXTTamerCharacter> Tamer;

    /** Set only for rivals; Tamer remains the player-compatible owner reference. */
    UPROPERTY(Replicated, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    TObjectPtr<ADigimonVenomNXTAIRivalAvatar> RivalTamer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Follower")
    TObjectPtr<UDigimonVenomNXTPartnerAnimationSet> AnimationSet;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Follower")
    void InitializeFromPartner(ADigimonVenomNXTTamerCharacter* InTamer, const FDigimonOwnedPartner& Partner);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Follower")
    void InitializeFromRival(ADigimonVenomNXTAIRivalAvatar* InRival, const FDigimonOwnedPartner& Partner);

    /** Immediately places the follower at a safe trailing position and clears stale path history. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Follower")
    void SnapToTamer();

protected:
    UFUNCTION() void OnRep_Identity();
    UFUNCTION(BlueprintImplementableEvent, Category="Digimon Venom NXT|Follower")
    void BP_OnFollowerIdentityChanged(FName NewSpeciesId, EDigimonVariant NewVariant, int32 NewLevel);

private:
    TArray<FVector> TrailPoints;
    FVector LastRecordedTamerLocation = FVector::ZeroVector;
    bool bTrailInitialized = false;
    FVector PreviousVisualLocation = FVector::ZeroVector;
    float WalkVisualRemaining = 0.0f;
    bool bWalkFacingLeft = false;
    FName LoadedSpeciesId = NAME_None;
    EDigimonVariant LoadedVariant = EDigimonVariant::Normal;

    AActor* GetFollowTarget() const;
    void ApplyPartnerIdentity(const FDigimonOwnedPartner& Partner, bool bOwnerChanged);
    void UpdateWalkVisual(float DeltaSeconds);
    bool IsSafeTrailSegment(const FVector& From, const FVector& To) const;

    void UpdateTrail();
    FVector ResolveTrailTarget(float FollowDistance) const;
};
