#include "DigimonVenomNXTPartnerFollower.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTAIRivalAvatar.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTFieldSizing.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "PaperFlipbookComponent.h"
#include "Misc/Crc.h"

ADigimonVenomNXTPartnerFollower::ADigimonVenomNXTPartnerFollower()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bNetUseOwnerRelevancy = true;
    SetReplicateMovement(true);
    SetNetUpdateFrequency(15.0f);
    SetMinNetUpdateFrequency(4.0f);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    GetCharacterMovement()->GravityScale = 0.0f;
    if (GetSprite())
    {
        GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
        GetSprite()->SetRelativeLocation(FVector(0.0f, 0.0f, -84.0f));
        GetSprite()->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
        DigimonVenomNXTFieldSprite::ConfigureDefaults(GetSprite());
    }
}

void ADigimonVenomNXTPartnerFollower::BeginPlay()
{
    Super::BeginPlay();
    if (GetSprite())
    {
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        if (Settings && Settings->bUseTrueTopDownFieldCamera)
        {
            GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
            GetSprite()->SetRelativeLocation(FVector(0.0f, 0.0f, -84.0f));
        }
        DigimonVenomNXTFieldSprite::Configure(GetSprite());
    }
    PreviousVisualLocation = GetActorLocation();
    OnRep_Identity();
}

void ADigimonVenomNXTPartnerFollower::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, InstanceId);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, SpeciesId);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, Variant);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, PartnerLevel);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, Tamer);
    DOREPLIFETIME(ADigimonVenomNXTPartnerFollower, RivalTamer);
}

bool ADigimonVenomNXTPartnerFollower::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
    // The rival's map and distance gates also apply to its companion, including late joins.
    if (RivalTamer) return RivalTamer->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
    if (Tamer) return Tamer->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
    return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

AActor* ADigimonVenomNXTPartnerFollower::GetFollowTarget() const
{
    if (IsValid(RivalTamer)) return RivalTamer.Get();
    return IsValid(Tamer) ? Tamer.Get() : nullptr;
}

void ADigimonVenomNXTPartnerFollower::InitializeFromPartner(ADigimonVenomNXTTamerCharacter* InTamer, const FDigimonOwnedPartner& Partner)
{
    if (!HasAuthority() || !IsValid(InTamer) || !Partner.IsValid()) return;
    const bool bOwnerChanged = GetFollowTarget() != InTamer;
    Tamer = InTamer;
    RivalTamer = nullptr;
    SetOwner(InTamer);
    ApplyPartnerIdentity(Partner, bOwnerChanged);
}

void ADigimonVenomNXTPartnerFollower::InitializeFromRival(ADigimonVenomNXTAIRivalAvatar* InRival, const FDigimonOwnedPartner& Partner)
{
    if (!HasAuthority() || !IsValid(InRival) || !Partner.IsValid()) return;
    const bool bOwnerChanged = GetFollowTarget() != InRival;
    Tamer = nullptr;
    RivalTamer = InRival;
    SetOwner(InRival);
    ApplyPartnerIdentity(Partner, bOwnerChanged);
}

void ADigimonVenomNXTPartnerFollower::ApplyPartnerIdentity(const FDigimonOwnedPartner& Partner, bool bOwnerChanged)
{
    const bool bIdentityChanged = InstanceId != Partner.InstanceId || SpeciesId != Partner.SpeciesId ||
        Variant != Partner.Variant || PartnerLevel != Partner.Level;
    InstanceId = Partner.InstanceId;
    SpeciesId = Partner.SpeciesId;
    Variant = Partner.Variant;
    PartnerLevel = Partner.Level;
    if (bIdentityChanged || !AnimationSet) OnRep_Identity();
    if (bOwnerChanged || !bTrailInitialized) SnapToTamer();
    if (bIdentityChanged || bOwnerChanged) ForceNetUpdate();
}

bool ADigimonVenomNXTPartnerFollower::IsSafeTrailSegment(const FVector& From, const FVector& To) const
{
    const ADigimonVenomNXTPlayerController* PC = Tamer ? Cast<ADigimonVenomNXTPlayerController>(Tamer->GetController()) : nullptr;
    if (PC && PC->IsInDigiFarm())
    {
        const FVector LocalFrom = From - PC->GetDigiFarmOrigin();
        const FVector LocalTo = To - PC->GetDigiFarmOrigin();
        return DigimonVenomNXTFarmCore::IsSegmentWalkable(LocalFrom.X, LocalFrom.Y, LocalTo.X, LocalTo.Y, DigimonVenomNXTFarmCore::ResidentRadius);
    }
    if (PC && PC->IsInRelay()) return PC->IsRelaySegmentWalkable(From, To);
    const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!WorldSystem) return false;
    const ADigimonVenomNXTPlayerState* PS = Tamer ? Tamer->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    const int32 MapId = RivalTamer ? RivalTamer->MapId : (PS ? PS->Profile.CurrentMapId : INDEX_NONE);
    // Human followers use the same terrain sweep as rivals. A following offset or
    // interpolation step must not cut through a wall or a shoreline corner.
    return MapId != INDEX_NONE && WorldSystem->IsWorldSegmentWalkable(MapId, From, To);
}

void ADigimonVenomNXTPartnerFollower::SnapToTamer()
{
    AActor* FollowTarget = GetFollowTarget();
    if (!HasAuthority() || !FollowTarget) return;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const float FollowDistance = FMath::Max(0.0f, Settings ? Settings->FollowerTrailDistance : 250.0f);
    const FVector OwnerLocation = FollowTarget->GetActorLocation();
    FVector Back = -FollowTarget->GetVelocity().GetSafeNormal2D();
    if (Back.IsNearlyZero() && Tamer && Tamer->FollowCamera)
    {
        Back = -Tamer->FollowCamera->GetForwardVector();
        Back.Z = 0.0f;
        Back = Back.GetSafeNormal();
    }
    if (Back.IsNearlyZero()) Back = FVector(0.0f, 1.0f, 0.0f);
    FVector Target = OwnerLocation + Back * FollowDistance;
    if (!IsSafeTrailSegment(OwnerLocation, Target))
    {
        // Spawn on the same connected walkable surface. A trailing offset must never
        // put the partner outside its habitat or beyond a wall beside the spawn.
        Target = OwnerLocation;
        bool bFound = false;
        const int32 StartDirection = static_cast<int32>((RivalTamer ? FCrc::StrCrc32(*RivalTamer->RivalId) : GetTypeHash(InstanceId)) % 12);
        for (const float Fraction : { 1.0f, 0.5f, 0.25f })
        {
            for (int32 Index = 0; Index < 12; ++Index)
            {
                const float Angle = static_cast<float>(Index + StartDirection) * 2.0f * PI / 12.0f;
                const FVector Candidate = OwnerLocation + FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f) * FollowDistance * Fraction;
                if (!IsSafeTrailSegment(OwnerLocation, Candidate)) continue;
                Target = Candidate;
                bFound = true;
                break;
            }
            if (bFound) break;
        }
    }
    Target.Z = OwnerLocation.Z + 4.0f;
    SetActorLocation(Target, false, nullptr, ETeleportType::TeleportPhysics);
    PreviousVisualLocation = Target;
    WalkVisualRemaining = 0.0f;
    TrailPoints.Reset();
    // Seed the actual safe trailing segment; otherwise the first idle tick would pull
    // the follower back onto its owner before that owner has walked anywhere.
    TrailPoints.Add(Target);
    TrailPoints.Add(OwnerLocation);
    LastRecordedTamerLocation = OwnerLocation;
    bTrailInitialized = true;
    ForceNetUpdate();
}

void ADigimonVenomNXTPartnerFollower::UpdateTrail()
{
    AActor* FollowTarget = GetFollowTarget();
    if (!FollowTarget) return;
    const FVector Current = FollowTarget->GetActorLocation();
    if (!bTrailInitialized)
    {
        SnapToTamer();
        return;
    }
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const float SnapDistance = FMath::Max(100.0f, Settings ? Settings->FollowerSnapDistance : 1200.0f);
    if (FVector::DistSquared2D(Current, LastRecordedTamerLocation) > FMath::Square(SnapDistance))
    {
        // Teleports/map changes cannot retain samples from the previous habitat.
        SnapToTamer();
        return;
    }
    if (FVector::DistSquared2D(Current, LastRecordedTamerLocation) >= FMath::Square(28.0f))
    {
        TrailPoints.Add(Current);
        LastRecordedTamerLocation = Current;
    }
    while (TrailPoints.Num() > 96) TrailPoints.RemoveAt(0, TrailPoints.Num() - 96, EAllowShrinking::No);
}

FVector ADigimonVenomNXTPartnerFollower::ResolveTrailTarget(float FollowDistance) const
{
    const AActor* FollowTarget = GetFollowTarget();
    if (!FollowTarget || TrailPoints.IsEmpty()) return GetActorLocation();
    float Remaining = FollowDistance;
    FVector Previous = FollowTarget->GetActorLocation();
    for (int32 Index = TrailPoints.Num() - 1; Index >= 0; --Index)
    {
        const FVector Candidate = TrailPoints[Index];
        const float SegmentLength = FVector::Dist2D(Previous, Candidate);
        if (SegmentLength > UE_SMALL_NUMBER && SegmentLength >= Remaining)
        {
            FVector Target = FMath::Lerp(Previous, Candidate, Remaining / SegmentLength);
            Target.Z = FollowTarget->GetActorLocation().Z + 4.0f;
            return Target;
        }
        Remaining -= SegmentLength;
        Previous = Candidate;
    }
    FVector Target = TrailPoints[0];
    Target.Z = FollowTarget->GetActorLocation().Z + 4.0f;
    return Target;
}

void ADigimonVenomNXTPartnerFollower::UpdateWalkVisual(float DeltaSeconds)
{
    const FVector Delta = GetActorLocation() - PreviousVisualLocation;
    PreviousVisualLocation = GetActorLocation();
    if (!AnimationSet || !GetSprite()) return;
    // Actors patrolled with SetActorLocation report zero GetVelocity; actual position
    // changes also work for their followers and for remotely replicated movement.
    if (Delta.SizeSquared2D() > FMath::Square(0.25f) && Delta.SizeSquared2D() < FMath::Square(1000.0f))
    {
        if (FMath::Abs(Delta.X) > 0.1f) bWalkFacingLeft = Delta.X > 0.0f;
        WalkVisualRemaining = 0.22f;
    }
    WalkVisualRemaining = FMath::Max(0.0f, WalkVisualRemaining - DeltaSeconds);
    UPaperFlipbook* Desired = bWalkFacingLeft && AnimationSet->bHasAuthoredLeftFrames && AnimationSet->IdleLeft
        ? AnimationSet->IdleLeft.Get() : AnimationSet->Idle.Get();
    if (WalkVisualRemaining > 0.0f)
        Desired = bWalkFacingLeft ? AnimationSet->WalkLeft : AnimationSet->WalkRight;
    if (!Desired) Desired = AnimationSet->Idle;
    if (Desired && GetSprite()->GetFlipbook() != Desired) GetSprite()->SetFlipbook(Desired);
    DigimonVenomNXTFieldSizing::SetSourceClock(GetSprite());
    const double WorldPerPixel = RivalTamer ? DigimonVenomNXTFieldSizing::MapWorldPerPixel(this, RivalTamer->MapId)
        : DigimonVenomNXTFieldSizing::PawnWorldPerPixel(Tamer);
    DigimonVenomNXTFieldSizing::ApplyPartner(GetSprite(), AnimationSet, WorldPerPixel, bWalkFacingLeft);
}

void ADigimonVenomNXTPartnerFollower::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    DigimonVenomNXTFieldSprite::UpdateDepth(GetSprite());
    UpdateWalkVisual(DeltaSeconds);
    AActor* FollowTarget = GetFollowTarget();
    if (!FollowTarget) return;
    if (!HasAuthority()) return;
    if (IsHidden() != FollowTarget->IsHidden()) SetActorHiddenInGame(FollowTarget->IsHidden());
    if (FollowTarget->IsHidden()) return;
    UpdateTrail();

    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const float FollowDistance = FMath::Max(0.0f, Settings ? Settings->FollowerTrailDistance : 250.0f);
    const float FollowSpeed = FMath::Max(0.1f, Settings ? Settings->FollowerFollowSpeed : 10.0f);
    const float SnapDistance = FMath::Max(100.0f, Settings ? Settings->FollowerSnapDistance : 1200.0f);
    const FVector Target = ResolveTrailTarget(FollowDistance);
    if (FVector::DistSquared2D(GetActorLocation(), Target) > FMath::Square(SnapDistance))
    {
        SnapToTamer();
        return;
    }
    const FVector Next = FMath::VInterpTo(GetActorLocation(), Target, DeltaSeconds, FollowSpeed);
    if (!IsSafeTrailSegment(GetActorLocation(), Next))
    {
        // Rejoin a safe trailing segment if interpolation would cut through a corner.
        SnapToTamer();
        return;
    }
    SetActorLocation(Next, false, nullptr, ETeleportType::None);
}

void ADigimonVenomNXTPartnerFollower::OnRep_Identity()
{
    // Level/instance refreshes preserve the current two-frame animation phase.
    if (!AnimationSet || LoadedSpeciesId != SpeciesId || LoadedVariant != Variant)
    {
        AnimationSet = nullptr;
        LoadedSpeciesId = SpeciesId;
        LoadedVariant = Variant;
        if (!SpeciesId.IsNone())
        {
            const FString VariantFolder = DigimonVenomNXTPartnerArt::VariantFolder(Variant);
            const FString Species = SpeciesId.ToString();
            const FString AssetName = FString::Printf(TEXT("DA_%s_%s_Animation"), *Species, *VariantFolder);
            const FString ObjectPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Digimon/%s/%s/%s.%s"), *VariantFolder, *Species, *AssetName, *AssetName);
            AnimationSet = LoadObject<UDigimonVenomNXTPartnerAnimationSet>(nullptr, *ObjectPath);
        }
        if (GetSprite())
        {
            GetSprite()->SetFlipbook(AnimationSet ? AnimationSet->Idle.Get() : nullptr);
            if (AnimationSet) GetSprite()->Play();
            DigimonVenomNXTFieldSprite::Configure(GetSprite());
        }
    }
    BP_OnFollowerIdentityChanged(SpeciesId, Variant, PartnerLevel);
}
