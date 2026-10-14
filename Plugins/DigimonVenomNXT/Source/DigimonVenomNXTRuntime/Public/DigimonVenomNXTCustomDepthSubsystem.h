#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DigimonVenomNXTCustomDepthSubsystem.generated.h"

class UActorComponent;
class ULevel;

/**
 * Keeps every world visual in the cel-shading Custom Depth pass. Covers loaded maps,
 * streamed levels, spawned actors, construction-script components and later additions.
 * A bounded round-robin repairs late component changes without a full scan every frame.
 */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTCustomDepthSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;
    virtual void OnWorldComponentsUpdated(UWorld& InWorld) override;
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickableInEditor() const override { return true; }
    virtual bool IsTickableWhenPaused() const override { return true; }

    /** Also available to editor repair commands and automated acceptance tests. */
    void RefreshWorld();

protected:
    virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;

private:
    void TrackActor(AActor* Actor);
    void OnActorSpawned(AActor* Actor);
    void OnLevelAdded(ULevel* Level, UWorld* InWorld);
    void OnRenderStateDirty(UActorComponent& Component);

    TArray<TWeakObjectPtr<AActor>> Actors;
    TSet<TWeakObjectPtr<AActor>> KnownActors;
    TArray<TWeakObjectPtr<AActor>> PendingConstruction;
    int32 ActorCursor = 0;
    bool bHandlingRenderStateDirty = false;
    FDelegateHandle ActorSpawnedHandle;
    FDelegateHandle LevelAddedHandle;
    FDelegateHandle RenderStateDirtyHandle;
};
