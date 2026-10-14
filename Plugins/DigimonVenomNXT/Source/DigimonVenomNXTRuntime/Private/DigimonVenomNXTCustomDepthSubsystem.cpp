#include "DigimonVenomNXTCustomDepthSubsystem.h"
#include "DigimonVenomNXTCustomDepth.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Stats/Stats.h"

void UDigimonVenomNXTCustomDepthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    if (UWorld* World = GetWorld())
        ActorSpawnedHandle = World->AddOnActorSpawnedHandler(
            FOnActorSpawned::FDelegate::CreateUObject(this, &UDigimonVenomNXTCustomDepthSubsystem::OnActorSpawned));
    LevelAddedHandle = FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UDigimonVenomNXTCustomDepthSubsystem::OnLevelAdded);
    RenderStateDirtyHandle = UActorComponent::MarkRenderStateDirtyEvent.AddUObject(this,
        &UDigimonVenomNXTCustomDepthSubsystem::OnRenderStateDirty);
}

void UDigimonVenomNXTCustomDepthSubsystem::Deinitialize()
{
    if (UWorld* World = GetWorld()) World->RemoveOnActorSpawnedHandler(ActorSpawnedHandle);
    FWorldDelegates::LevelAddedToWorld.Remove(LevelAddedHandle);
    UActorComponent::MarkRenderStateDirtyEvent.Remove(RenderStateDirtyHandle);
    PendingConstruction.Reset();
    KnownActors.Reset();
    Actors.Reset();
    ActorCursor = 0;
    Super::Deinitialize();
}

bool UDigimonVenomNXTCustomDepthSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
    return WorldType == EWorldType::Game || WorldType == EWorldType::PIE ||
        WorldType == EWorldType::Editor || WorldType == EWorldType::GamePreview;
}

void UDigimonVenomNXTCustomDepthSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    RefreshWorld();
}

void UDigimonVenomNXTCustomDepthSubsystem::OnWorldComponentsUpdated(UWorld& InWorld)
{
    Super::OnWorldComponentsUpdated(InWorld);
    RefreshWorld();
}

void UDigimonVenomNXTCustomDepthSubsystem::TrackActor(AActor* Actor)
{
    if (!IsValid(Actor) || Actor->IsTemplate() || Actor->GetWorld() != GetWorld()) return;
    const TWeakObjectPtr<AActor> WeakActor(Actor);
    if (!KnownActors.Contains(WeakActor))
    {
        KnownActors.Add(WeakActor);
        Actors.Add(WeakActor);
    }
    DigimonVenomNXTCustomDepth::ConfigureActor(Actor);
}

void UDigimonVenomNXTCustomDepthSubsystem::RefreshWorld()
{
    UWorld* World = GetWorld();
    if (!World) return;
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    Actors.Reset();
    KnownActors.Reset();
    ActorCursor = 0;
    for (TActorIterator<AActor> It(World); It; ++It) TrackActor(*It);
}

void UDigimonVenomNXTCustomDepthSubsystem::OnActorSpawned(AActor* Actor)
{
    TrackActor(Actor);
    // Deferred spawning and Blueprint construction can append components after the
    // spawn notification. Revisit on the next world tick as well as the rotating sweep.
    if (IsValid(Actor)) PendingConstruction.AddUnique(TWeakObjectPtr<AActor>(Actor));
}

void UDigimonVenomNXTCustomDepthSubsystem::OnLevelAdded(ULevel* Level, UWorld* InWorld)
{
    if (InWorld != GetWorld() || !Level) return;
    for (AActor* Actor : Level->Actors) TrackActor(Actor);
}

void UDigimonVenomNXTCustomDepthSubsystem::OnRenderStateDirty(UActorComponent& Component)
{
    // Material, visibility and Custom Depth setters route here before their render
    // proxy is rebuilt. The guard prevents recursion from our own SetRenderCustomDepth.
    if (bHandlingRenderStateDirty || !IsInGameThread() || Component.GetWorld() != GetWorld()) return;
    TGuardValue<bool> Guard(bHandlingRenderStateDirty, true);
    DigimonVenomNXTCustomDepth::ConfigurePrimitive(Cast<UPrimitiveComponent>(&Component));
}

void UDigimonVenomNXTCustomDepthSubsystem::Tick(float DeltaTime)
{
    for (const TWeakObjectPtr<AActor>& Pending : PendingConstruction)
        if (AActor* Actor = Pending.Get()) DigimonVenomNXTCustomDepth::ConfigureActor(Actor);
    PendingConstruction.Reset();
    if (Actors.IsEmpty()) return;

    // Aim to revisit every actor within half a second. Bound the per-frame work for
    // unusually large streamed worlds; never iterate every UObject or actor each frame.
    const int32 Budget = FMath::Clamp(FMath::CeilToInt(
        Actors.Num() * FMath::Clamp(DeltaTime, 1.0f / 240.0f, 0.1f) * 2.0f), 1, 256);
    for (int32 Work = 0; Work < Budget && !Actors.IsEmpty(); ++Work)
    {
        if (ActorCursor >= Actors.Num()) ActorCursor = 0;
        const TWeakObjectPtr<AActor> Entry = Actors[ActorCursor];
        AActor* Actor = Entry.Get();
        if (!Actor || Actor->GetWorld() != GetWorld())
        {
            KnownActors.Remove(Entry);
            Actors.RemoveAtSwap(ActorCursor, 1, EAllowShrinking::No);
            continue;
        }
        DigimonVenomNXTCustomDepth::ConfigureActor(Actor);
        ++ActorCursor;
    }
}

TStatId UDigimonVenomNXTCustomDepthSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UDigimonVenomNXTCustomDepthSubsystem, STATGROUP_Tickables);
}
