#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTTamerCharacter.generated.h"

class UDigimonVenomNXTTamerAnimationSet;
class ADigimonVenomNXTPartnerFollower;
class USpringArmComponent;
class UCameraComponent;
class UDigimonVenomNXTNameplateComponent;
class ADigimonVenomNXTPlayerController;

/** Top-down replicated tamer pawn with handheld-RPG field camera and walking-driven encounters. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTTamerCharacter : public APaperCharacter
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTTamerCharacter();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
    bool IsVisibleToViewer(const ADigimonVenomNXTPlayerController* Viewer) const;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Tamer")
    TObjectPtr<UDigimonVenomNXTTamerAnimationSet> AnimationSet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Tamer")
    TObjectPtr<UDigimonVenomNXTNameplateComponent> Nameplate;

    UPROPERTY(ReplicatedUsing=OnRep_Facing, BlueprintReadOnly, Category="Digimon Venom NXT|Tamer")
    EDigimonFacing Facing = EDigimonFacing::Down;

    UPROPERTY(ReplicatedUsing=OnRep_TamerStyle, BlueprintReadOnly, Category="Digimon Venom NXT|Tamer")
    FName TamerStyleId = TEXT("tamer_002");

    UPROPERTY(ReplicatedUsing=OnRep_Follower, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    TObjectPtr<ADigimonVenomNXTPartnerFollower> Follower;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Digimon Venom NXT|Follower")
    TSubclassOf<ADigimonVenomNXTPartnerFollower> FollowerClass;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Follower")
    void RefreshFollowerFromProfile();

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Follower")
    void SnapFollowerToTamer();

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Tamer")
    void RefreshTamerStyleFromProfile();

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Camera")
    void AdjustCameraZoom(float Direction);

    /** Called after spawn/travel/battle so the next encounter cannot immediately retrigger. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Wild")
    void ResetEncounterTracker();

protected:
    UFUNCTION(Server, Unreliable) void ServerSetFacing(EDigimonFacing NewFacing);
    UFUNCTION() void OnRep_Facing();
    UFUNCTION() void OnRep_TamerStyle();
    UFUNCTION() void OnRep_Follower();
    UFUNCTION(BlueprintImplementableEvent, Category="Digimon Venom NXT|Tamer") void BP_OnFacingChanged(EDigimonFacing NewFacing);
    UFUNCTION(BlueprintImplementableEvent, Category="Digimon Venom NXT|Follower") void BP_OnFollowerChanged(ADigimonVenomNXTPartnerFollower* NewFollower);

private:
    float DesiredOrthoWidth = 10000.0f;
    float FieldCameraZoom = 1.0f;
    int32 PresentedCameraMapId = INDEX_NONE;
    int32 PresentedCameraContext = INDEX_NONE;
    FVector PresentedCameraOrigin = FVector::ZeroVector;
    FVector FieldCameraCenter = FVector::ZeroVector;
    bool bCameraFrameReady = false;
    FVector LastEncounterLocation = FVector::ZeroVector;
    float EncounterDistanceAccumulator = 0.0f;
    float EncounterSafeDistanceRemaining = 0.0f;
    bool bEncounterTrackerReady = false;
    FVector LastValidWalkableLocation = FVector::ZeroVector;
    bool bHasValidWalkableLocation = false;

    void ApplyFacingVisual();
    void UpdateWalkAnimationState();
    void StopFieldMovement();
    void HandleLocalMovement(float DeltaSeconds);
    void HandleLocalCameraZoom(float DeltaSeconds);
    void HandleServerWalkingEncounter();
    void EnforceServerMapCollision();
};
