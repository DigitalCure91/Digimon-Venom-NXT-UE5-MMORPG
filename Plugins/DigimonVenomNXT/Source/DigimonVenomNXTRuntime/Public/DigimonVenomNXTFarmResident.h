#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameFramework/Actor.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTFarmResident.generated.h"

class ADigimonVenomNXTFarmScene;
class ADigimonVenomNXTPlayerController;
class ADigimonVenomNXTFarmResident;
class UPaperFlipbookComponent;
class UDigimonVenomNXTPartnerAnimationSet;
class UButton;
class UTextBlock;
class UBorder;

/** Mouse selection must not steal keyboard focus from farm movement. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFarmResidentSelectButton : public UButton
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTFarmResidentSelectButton(const FObjectInitializer& ObjectInitializer);
};

/** Clickable resident identity, rendered only in its owner's player viewport. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFarmResidentNameplate : public UUserWidget
{
    GENERATED_BODY()
public:
    void InitializeFor(ADigimonVenomNXTFarmResident* InResident);
    void SetIdentity(const FString& Name, int32 Level, bool bSelected);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
private:
    UPROPERTY(Transient) TWeakObjectPtr<ADigimonVenomNXTFarmResident> Resident;
    UPROPERTY(Transient) TObjectPtr<UBorder> Plate;
    UPROPERTY(Transient) TObjectPtr<UButton> SelectButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Label;
    FString ResidentName;
    int32 ResidentLevel = 1;
    bool bResidentSelected = false;
    UFUNCTION() void HandleClicked();
    void ApplyIdentity();
};

/** A cosmetic local view of one real, owned farm partner, with collision-safe roaming. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTFarmResident : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTFarmResident();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    void InitializeFor(ADigimonVenomNXTFarmScene* Scene, ADigimonVenomNXTPlayerController* Viewer,
        const FDigimonOwnedPartner& Partner, const FVector& Origin, const FVector2D& LocalPosition);
    void RefreshPartner(const FDigimonOwnedPartner& Partner);
    void SetFarmVisible(bool bVisible);
    void SetSelected(bool bSelected);
    void RequestSelection();
    FGuid GetPartnerId() const { return Snapshot.InstanceId; }
    const FDigimonOwnedPartner& GetPartnerSnapshot() const { return Snapshot; }
    FVector GetNameplateAnchor() const;

private:
    UPROPERTY(VisibleAnywhere) TObjectPtr<UPaperFlipbookComponent> Sprite;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTPartnerAnimationSet> AnimationSet;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTFarmResidentNameplate> Nameplate;
    UPROPERTY(Transient) TWeakObjectPtr<ADigimonVenomNXTFarmScene> FarmScene;
    UPROPERTY(Transient) TWeakObjectPtr<ADigimonVenomNXTPlayerController> OwningViewer;
    UPROPERTY(Transient) FDigimonOwnedPartner Snapshot;
    FVector FarmOrigin = FVector::ZeroVector;
    FVector2D RoamTarget = FVector2D::ZeroVector;
    FRandomStream RoamRandom;
    FString DisplayName;
    float WaitRemaining = 0.0f;
    bool bFarmVisible = false;
    bool bIsSelected = false;
    bool bHasTarget = false;
    bool bFacingLeft = false;
    void ChooseRoamTarget();
    void RefreshNameplate();
};
