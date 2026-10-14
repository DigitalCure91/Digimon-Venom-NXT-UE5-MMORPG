#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigimonVenomNXTFarmScene.generated.h"

class ADigimonVenomNXTPlayerController;
class ADigimonVenomNXTFarmResident;
class UPaperSpriteComponent;
class USceneComponent;

/** Private island presentation. Never replicated; residents come only from this owner's profile. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTFarmScene : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTFarmScene();
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    bool InitializeFor(ADigimonVenomNXTPlayerController* InOwner, FVector Origin);
    void RefreshResidents();
    void SetFarmVisible(bool bVisible);
    bool IsPresentationReady() const { return bPresentationReady; }
    bool IsFarmVisible() const { return bFarmVisible && bPresentationReady; }
    FGuid GetSelectedResident() const { return SelectedResident; }
    FGuid GetSelectedResidentId() const { return SelectedResident; }
    void SelectResident(FGuid InstanceId);
    TArray<ADigimonVenomNXTFarmResident*> GetResidentActors() const;

private:
    UPROPERTY(VisibleAnywhere) TObjectPtr<USceneComponent> SceneRoot;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UPaperSpriteComponent> IslandSprite;
    UPROPERTY(Transient) TWeakObjectPtr<ADigimonVenomNXTPlayerController> OwningController;
    UPROPERTY(Transient) TArray<TObjectPtr<ADigimonVenomNXTFarmResident>> Residents;
    FGuid SelectedResident;
    float RefreshRemaining = 0.0f;
    bool bFarmVisible = false;
    bool bPresentationReady = false;
};
