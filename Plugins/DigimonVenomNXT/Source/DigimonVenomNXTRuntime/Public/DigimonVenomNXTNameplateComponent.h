#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DigimonVenomNXTNameplateComponent.generated.h"

class UDigimonVenomNXTNameplateWidget;

/** Non-replicated presentation; identity comes from the actor's existing replicated state. */
UCLASS(ClassGroup=(DigimonVenomNXT), meta=(BlueprintSpawnableComponent))
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTNameplateComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTNameplateComponent();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // Each local player has independent identity styling, projection and visibility.
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTNameplateWidget>> LocalNameplates;
};
