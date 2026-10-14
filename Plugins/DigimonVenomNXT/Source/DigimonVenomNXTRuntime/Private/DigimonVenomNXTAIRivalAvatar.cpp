#include "DigimonVenomNXTAIRivalAvatar.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"
#include "PaperFlipbookComponent.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTPartnerFollower.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Misc/Crc.h"
#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTFieldSizing.h"
#include "DigimonVenomNXTNameplateComponent.h"

ADigimonVenomNXTAIRivalAvatar::ADigimonVenomNXTAIRivalAvatar()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);
    SetNetUpdateFrequency(5.0f);
    SetMinNetUpdateFrequency(1.0f);
    SetNetCullDistanceSquared(FMath::Square(6000.0f));

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);
    Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
    Sprite->SetupAttachment(Root);
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    Sprite->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
    DigimonVenomNXTFieldSprite::ConfigureDefaults(Sprite);
    Nameplate = CreateDefaultSubobject<UDigimonVenomNXTNameplateComponent>(TEXT("Nameplate"));
}

void ADigimonVenomNXTAIRivalAvatar::BeginPlay()
{
    Super::BeginPlay();
    if (Sprite)
    {
        DigimonVenomNXTFieldSprite::Configure(Sprite);
    }
    PreviousVisualLocation = GetActorLocation();
    OnRep_Identity();
}

void ADigimonVenomNXTAIRivalAvatar::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADigimonVenomNXTAIRivalAvatar, RivalId);
    DOREPLIFETIME(ADigimonVenomNXTAIRivalAvatar, DisplayName);
    DOREPLIFETIME(ADigimonVenomNXTAIRivalAvatar, MapId);
    DOREPLIFETIME(ADigimonVenomNXTAIRivalAvatar, TamerLevel);
    DOREPLIFETIME(ADigimonVenomNXTAIRivalAvatar, LeaderFollower);
}

void ADigimonVenomNXTAIRivalAvatar::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (HasAuthority() && IsValid(LeaderFollower))
    {
        LeaderFollower->Destroy();
        LeaderFollower = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

bool ADigimonVenomNXTAIRivalAvatar::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
    if (!bHasWalkablePlacement || IsHidden()) return false;
    const APlayerController* Viewer = Cast<APlayerController>(RealViewer);
    if (!Viewer)
    {
        const APawn* ViewerPawn = Cast<APawn>(ViewTarget);
        Viewer = ViewerPawn ? Cast<APlayerController>(ViewerPawn->GetController()) : nullptr;
    }
    const ADigimonVenomNXTPlayerController* DigimonViewer = Cast<ADigimonVenomNXTPlayerController>(Viewer);
    if (!DigimonViewer || !DigimonViewer->IsAccountAuthenticated() || DigimonViewer->IsInDigiFarm() || DigimonViewer->IsInRelay()) return false;
    const ADigimonVenomNXTPlayerState* Player = Viewer ? Viewer->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    if (Player && Player->Profile.CurrentMapId != MapId) return false;
    return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

void ADigimonVenomNXTAIRivalAvatar::RefreshLeaderFollower(const FDigimonOwnedPartner& Partner)
{
    if (!HasAuthority() || !GetWorld()) return;
    if (!Partner.IsValid() || !bHasWalkablePlacement)
    {
        if (IsValid(LeaderFollower)) LeaderFollower->Destroy();
        LeaderFollower = nullptr;
        ForceNetUpdate();
        return;
    }
    if (!IsValid(LeaderFollower))
    {
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        LeaderFollower = GetWorld()->SpawnActor<ADigimonVenomNXTPartnerFollower>(ADigimonVenomNXTPartnerFollower::StaticClass(),
            GetActorLocation(), FRotator::ZeroRotator, Params);
        ForceNetUpdate();
    }
    if (LeaderFollower)
    {
        LeaderFollower->InitializeFromRival(this, Partner);
        LeaderFollower->SetActorHiddenInGame(IsHidden());
    }
}

void ADigimonVenomNXTAIRivalAvatar::InitializeAvatar(const FString& InRivalId, const FString& InDisplayName, int32 InMapId, int32 InTamerLevel, const FBox& InPatrolBounds)
{
    if (!HasAuthority()) return;
    const int32 NewLevel = FMath::Max(1, InTamerLevel);
    const bool bIdentityChanged = RivalId != InRivalId || DisplayName != InDisplayName || TamerLevel != NewLevel;
    const bool bMapChanged = MapId != InMapId;
    const bool bBoundsChanged = PatrolBounds.IsValid != InPatrolBounds.IsValid ||
        (InPatrolBounds.IsValid && (!PatrolBounds.Min.Equals(InPatrolBounds.Min, 0.1f) || !PatrolBounds.Max.Equals(InPatrolBounds.Max, 0.1f)));
    RivalId = InRivalId;
    DisplayName = InDisplayName;
    MapId = InMapId;
    TamerLevel = NewLevel;
    PatrolBounds = InPatrolBounds;

    UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    // A random spawn can be walkable but isolated from the player's entrance.
    // Prove connectivity on first placement/map changes; subsequent exact sweeps
    // preserve it without rebuilding or scanning the reachable graph every refresh.
    const bool bNeedsPlacement = !bHasWalkablePlacement || bMapChanged || bBoundsChanged ||
        !IsInsidePatrolBounds(GetActorLocation()) || !WorldSystem ||
        !WorldSystem->IsWorldLocationWalkable(MapId, GetActorLocation());
    bool bRelocated = false;
    if (bNeedsPlacement)
    {
        FVector SafeLocation;
        if (!FindWalkablePlacement(SafeLocation))
        {
            // Do not leave a proxy trapped in the previous map or walking through invalid data.
            // The next visibility refresh retries after map/collision assets become available.
            bHasWalkablePlacement = false;
            SetActorHiddenInGame(true);
            if (IsValid(LeaderFollower)) LeaderFollower->SetActorHiddenInGame(true);
            PatrolTarget = GetActorLocation();
            WalkVisualRemaining = 0.0f;
            if (Sprite) Sprite->Stop();
            ForceNetUpdate();
            return;
        }
        SetActorLocation(SafeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        PreviousVisualLocation = SafeLocation;
        WalkVisualRemaining = 0.0f;
        bRelocated = true;
    }
    const bool bFirstPlacement = !bHasWalkablePlacement;
    bHasWalkablePlacement = true;
    SetActorHiddenInGame(false);
    if (IsValid(LeaderFollower))
    {
        LeaderFollower->SetActorHiddenInGame(false);
        if (bRelocated || bMapChanged) LeaderFollower->SnapToTamer();
    }
    if (bRelocated || bBoundsChanged || bFirstPlacement) ChoosePatrolTarget();
    if (bIdentityChanged || !AnimationSet) OnRep_Identity();
    if (bIdentityChanged || bMapChanged || bRelocated || bFirstPlacement) ForceNetUpdate();
}

bool ADigimonVenomNXTAIRivalAvatar::IsInsidePatrolBounds(const FVector& Location) const
{
    return PatrolBounds.IsValid && Location.X >= PatrolBounds.Min.X && Location.X <= PatrolBounds.Max.X &&
        Location.Y >= PatrolBounds.Min.Y && Location.Y <= PatrolBounds.Max.Y;
}

bool ADigimonVenomNXTAIRivalAvatar::FindWalkablePlacement(FVector& OutLocation) const
{
    const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    const ADigimonVenomNXTMapZone* Zone = WorldSystem ? WorldSystem->FindMapZone(MapId) : nullptr;
    if (!WorldSystem || !Zone || !PatrolBounds.IsValid) return false;
    // Resolve onto the same cached connected component used by campaign NPCs.
    // The per-rival seed spreads rivals out and retains their location preference
    // after a map reload. No candidate may be accepted merely for having dry feet.
    FRandomStream PlacementRandom(static_cast<int32>(FCrc::StrCrc32(*RivalId)));
    const float DesiredU = PlacementRandom.FRandRange(0.08f, 0.92f);
    const float DesiredV = PlacementRandom.FRandRange(0.08f, 0.92f);
    const FVector2D DesiredUV(DesiredU, DesiredV);
    FVector ReachableLocal;
    if (WorldSystem->ResolvePrivateMapPoint(MapId, DesiredUV, ReachableLocal))
    {
        const FVector Candidate = Zone->GetActorLocation() + ReachableLocal;
        if (IsInsidePatrolBounds(Candidate) && WorldSystem->IsWorldLocationWalkable(MapId, Candidate))
        {
            OutLocation = Candidate;
            return true;
        }
    }
    // Custom patrol bounds may exclude the selected graph point. A verified
    // public entrance is the only fallback, never a disconnected random island.
    const FVector Anchor = Zone->GetPlayerSpawnLocation();
    if (!IsInsidePatrolBounds(Anchor) || !WorldSystem->IsWorldLocationWalkable(MapId, Anchor)) return false;
    OutLocation = Anchor;
    return true;
}

void ADigimonVenomNXTAIRivalAvatar::ChoosePatrolTarget()
{
    PatrolTarget = GetActorLocation();
    RetargetTimer = FMath::FRandRange(2.0f, 7.0f);
    const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!WorldSystem || !PatrolBounds.IsValid || !bHasWalkablePlacement) return;
    // Local connected wander segments keep a valid endpoint across walls from becoming an
    // unreachable patrol goal. Every step uses the same footprint collision query as players.
    for (int32 Attempt = 0; Attempt < 12; ++Attempt)
    {
        const float Angle = FMath::FRandRange(0.0f, 2.0f * PI);
        const FVector Direction(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);
        const float DesiredDistance = FMath::FRandRange(180.0f, 700.0f);
        FVector Furthest = GetActorLocation();
        for (float Distance = 24.0f; Distance <= DesiredDistance; Distance += 24.0f)
        {
            const FVector Candidate = GetActorLocation() + Direction * Distance;
            if (!IsInsidePatrolBounds(Candidate) || !WorldSystem->IsWorldSegmentWalkable(MapId, Furthest, Candidate)) break;
            Furthest = Candidate;
        }
        if (FVector::DistSquared2D(Furthest, GetActorLocation()) >= FMath::Square(48.0f))
        {
            PatrolTarget = Furthest;
            return;
        }
    }
}

void ADigimonVenomNXTAIRivalAvatar::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    DigimonVenomNXTFieldSprite::UpdateDepth(Sprite);
    UpdateWalkVisual(DeltaSeconds);
    if (!HasAuthority() || !bHasWalkablePlacement) return;
    RetargetTimer -= DeltaSeconds;
    if (RetargetTimer <= 0.0f || FVector::DistSquared2D(GetActorLocation(), PatrolTarget) < FMath::Square(20.0f)) ChoosePatrolTarget();
    const FVector Next = FMath::VInterpConstantTo(GetActorLocation(), PatrolTarget, FMath::Min(DeltaSeconds, 0.1f), PatrolSpeed);
    const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!WorldSystem) return;
    if (!IsInsidePatrolBounds(Next) || !WorldSystem->IsWorldSegmentWalkable(MapId, GetActorLocation(), Next))
    {
        ChoosePatrolTarget();
        return;
    }
    SetActorLocation(Next, false, nullptr, ETeleportType::None);
}

void ADigimonVenomNXTAIRivalAvatar::OnRep_Identity()
{
    if (RivalId.IsEmpty()) return;
    const FName StyleId = DigimonVenomNXTTamers::StyleForStableId(RivalId);
    const FString Style = StyleId.ToString();
    // Name/level refreshes must not restart the walk cycle or turn a moving rival downward.
    if (GetNetMode() != NM_DedicatedServer && LoadedAnimationStyle != Style)
    {
        AnimationSet = LoadObject<UDigimonVenomNXTTamerAnimationSet>(nullptr, *DigimonVenomNXTTamers::AnimationPath(StyleId));
        LoadedAnimationStyle = Style;
        if (Sprite)
        {
            Sprite->SetFlipbook(AnimationSet ? AnimationSet->Down : nullptr);
            Sprite->Stop();
            Sprite->SetPlaybackPositionInFrames(0, false);
            DigimonVenomNXTFieldSprite::Configure(Sprite);
        }
        if (!AnimationSet)
            UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT rival %s needs imported tamer style %s."), *RivalId, *Style);
    }
    BP_OnRivalIdentityChanged(RivalId, DisplayName, TamerLevel);
}

void ADigimonVenomNXTAIRivalAvatar::UpdateWalkVisual(float DeltaSeconds)
{
    const FVector Delta = GetActorLocation() - PreviousVisualLocation;
    PreviousVisualLocation = GetActorLocation();
    if (!Sprite || !AnimationSet) return;
    DigimonVenomNXTFieldSizing::ApplyTamer(Sprite, AnimationSet, DigimonVenomNXTFieldSizing::MapWorldPerPixel(this, MapId));
    if (Delta.SizeSquared2D() > FMath::Square(0.25f) && Delta.SizeSquared2D() < FMath::Square(1000.0f))
    {
        // Field camera yaw is +90: screen right is world -X, screen up is world +Y.
        const FVector2D Direction(-Delta.X, Delta.Y);
        const FVector2D Axis = Direction.GetSafeNormal();
        EDigimonFacing Facing = EDigimonFacing::Down;
        if (Axis.Y > 0.35f) Facing = Axis.X > 0.35f ? EDigimonFacing::UpRight : (Axis.X < -0.35f ? EDigimonFacing::UpLeft : EDigimonFacing::Up);
        else if (Axis.Y < -0.35f) Facing = Axis.X > 0.35f ? EDigimonFacing::DownRight : (Axis.X < -0.35f ? EDigimonFacing::DownLeft : EDigimonFacing::Down);
        else Facing = Axis.X > 0.0f ? EDigimonFacing::Right : EDigimonFacing::Left;
        UPaperFlipbook* Desired = AnimationSet->GetForFacing(Facing);
        if (Desired && Sprite->GetFlipbook() != Desired) Sprite->SetFlipbook(Desired);
        // Bridge the replicated movement packet interval on clients.
        WalkVisualRemaining = 0.3f;
    }
    WalkVisualRemaining = FMath::Max(0.0f, WalkVisualRemaining - DeltaSeconds);
    DigimonVenomNXTFieldSizing::SetSourceClock(Sprite, WalkVisualRemaining > 0.0f);
}
