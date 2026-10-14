#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTPartnerFollower.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTFieldSizing.h"
#include "DigimonVenomNXTFieldMovementCore.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTFarmSessionCore.h"
#include "DigimonVenomNXTRelaySessionCore.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTNameplateComponent.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include "Net/UnrealNetwork.h"
#include "PaperFlipbookComponent.h"

ADigimonVenomNXTTamerCharacter::ADigimonVenomNXTTamerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);
    SetNetUpdateFrequency(20.0f);
    SetMinNetUpdateFrequency(6.0f);
    GetCharacterMovement()->MaxWalkSpeed = 240.0f;
    GetCharacterMovement()->MaxFlySpeed = 240.0f;
    GetCharacterMovement()->GravityScale = 0.0f;
    // Field avatars do not become invisible physical walls for other players.
    // Terrain is enforced by the shared, server-authoritative foot mask.
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->SetPlaneConstraintNormal(FVector::UpVector);
    GetCharacterMovement()->bSnapToPlaneAtStart = true;
    // Field movement should feel like a handheld RPG, not inertial flying.
    GetCharacterMovement()->MaxAcceleration = 1000000.0f;
    GetCharacterMovement()->BrakingDecelerationFlying = 1000000.0f;
    GetCharacterMovement()->bUseSeparateBrakingFriction = true;
    GetCharacterMovement()->BrakingFriction = 128.0f;
    GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
    GetCharacterMovement()->bForceMaxAccel = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 3200.0f;
    CameraBoom->SetRelativeRotation(FRotator(-90.0f, 90.0f, 0.0f));
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->bUsePawnControlRotation = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    FollowCamera->SetOrthoWidth(10000.0f);

    Nameplate = CreateDefaultSubobject<UDigimonVenomNXTNameplateComponent>(TEXT("Nameplate"));

    FollowerClass = ADigimonVenomNXTPartnerFollower::StaticClass();
    if (GetSprite())
    {
        GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        // True top-down Paper2D presentation. +90 roll lays the X/Z sprite plane
        // onto world X/Y with its FRONT face toward the overhead camera. The negative local-X
        // scale is compensated by +90 camera yaw so source orientation remains unchanged on screen.
        GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
        GetSprite()->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
        GetSprite()->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
        DigimonVenomNXTFieldSprite::ConfigureDefaults(GetSprite());
    }
}

void ADigimonVenomNXTTamerCharacter::BeginPlay()
{
    Super::BeginPlay();
    // Repair capsule responses serialized by older generated pawn Blueprints.
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    float EffectiveWalkSpeed = Settings->TamerWalkSpeed;
    // Migrate the old fast prototype default to the tighter handheld-RPG pace.
    if (FMath::IsNearlyEqual(EffectiveWalkSpeed, 450.0f, 0.1f) || FMath::IsNearlyEqual(EffectiveWalkSpeed, 320.0f, 0.1f)) EffectiveWalkSpeed = 240.0f;
    GetCharacterMovement()->MaxWalkSpeed = EffectiveWalkSpeed;
    GetCharacterMovement()->MaxFlySpeed = EffectiveWalkSpeed;
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    CameraBoom->TargetArmLength = Settings->FieldCameraBoomLength;
    const float CameraPitch = Settings->bUseTrueTopDownFieldCamera ? -90.0f : Settings->FieldCameraPitch;
    CameraBoom->SetRelativeRotation(FRotator(CameraPitch, 90.0f, 0.0f));
    FieldCameraZoom = FMath::Clamp(Settings->FieldCameraInitialZoom, 1.0f, 8.0f);
    DesiredOrthoWidth = Settings->MapWorldWidth;
    FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    FollowCamera->SetOrthoWidth(DesiredOrthoWidth);
    if (GetSprite())
    {
        if (Settings->bUseTrueTopDownFieldCamera)
        {
            GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
            GetSprite()->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
        }
        DigimonVenomNXTFieldSprite::Configure(GetSprite());
    }

    if (HasAuthority()) RefreshTamerStyleFromProfile();
    else OnRep_TamerStyle();
    ApplyFacingVisual();
    if (IsLocallyControlled()) HandleLocalCameraZoom(0.0f);
    if (HasAuthority()) RefreshFollowerFromProfile();
    ResetEncounterTracker();
}

void ADigimonVenomNXTTamerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    DigimonVenomNXTFieldSprite::UpdateDepth(GetSprite());
    if (IsLocallyControlled())
    {
        HandleLocalMovement(DeltaSeconds);
        HandleLocalCameraZoom(DeltaSeconds);
    }
    UpdateWalkAnimationState();
    DigimonVenomNXTFieldSizing::ApplyTamer(GetSprite(), AnimationSet, DigimonVenomNXTFieldSizing::PawnWorldPerPixel(this));
    if (HasAuthority())
    {
        EnforceServerMapCollision();
        HandleServerWalkingEncounter();
    }
}

void ADigimonVenomNXTTamerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADigimonVenomNXTTamerCharacter, Facing);
    DOREPLIFETIME(ADigimonVenomNXTTamerCharacter, TamerStyleId);
    DOREPLIFETIME(ADigimonVenomNXTTamerCharacter, Follower);
}

void ADigimonVenomNXTTamerCharacter::HandleLocalMovement(float DeltaSeconds)
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Controller);
    if (!PC || !PC->IsLocalController()) return;
    // Raw-key polling must never leave a previous frame's movement request queued.
    // Clear the pawn input accumulator first, then add only the keys held this frame.
    ConsumeMovementInputVector();
    if (PC->IsFieldInputBlocked())
    {
        StopFieldMovement();
        return;
    }

    FVector2D Axis = FVector2D::ZeroVector;
    if (PC->IsInputKeyDown(EKeys::W) || PC->IsInputKeyDown(EKeys::Up)) Axis.Y += 1.0f;
    if (PC->IsInputKeyDown(EKeys::S) || PC->IsInputKeyDown(EKeys::Down)) Axis.Y -= 1.0f;
    if (PC->IsInputKeyDown(EKeys::D) || PC->IsInputKeyDown(EKeys::Right)) Axis.X += 1.0f;
    if (PC->IsInputKeyDown(EKeys::A) || PC->IsInputKeyDown(EKeys::Left)) Axis.X -= 1.0f;
    Axis = Axis.GetSafeNormal();
    if (Axis.IsNearlyZero())
    {
        StopFieldMovement();
        return;
    }
    {
        // Movement is screen/camera-relative so WASD always feels like a handheld
        // top-down RPG regardless of the configured field-camera yaw/pitch.
        // Use camera screen-up/right rather than camera forward. A true overhead
        // camera has a vertical forward vector, so projecting Forward onto XY would
        // be zero and break W/S movement. Camera Up remains the correct screen-up
        // direction for both true top-down and legacy angled views.
        FVector ScreenUp = FollowCamera ? FollowCamera->GetUpVector() : FVector::ForwardVector;
        FVector ScreenRight = FollowCamera ? FollowCamera->GetRightVector() : FVector::RightVector;
        ScreenUp.Z = 0.0f;
        ScreenRight.Z = 0.0f;
        ScreenUp = ScreenUp.GetSafeNormal();
        ScreenRight = ScreenRight.GetSafeNormal();
        FVector MoveDirection = (ScreenUp * Axis.Y + ScreenRight * Axis.X).GetSafeNormal();
        if (!MoveDirection.IsNearlyZero())
        {
            const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
            const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
            // Sweep only the actual next movement step. The old fixed 45-unit
            // look-ahead made every wall larger and rejected turns on narrow paths.
            const float Probe = static_cast<float>(DigimonVenomNXTFieldMovementCore::StepDistance(GetCharacterMovement()->MaxFlySpeed, DeltaSeconds));
            auto CanStand = [&](const FVector& Direction)
            {
                const FVector Candidate = GetActorLocation() + Direction * Probe;
                if (PC->IsInDigiFarm())
                {
                    const FVector From = GetActorLocation() - PC->GetDigiFarmOrigin();
                    const FVector To = Candidate - PC->GetDigiFarmOrigin();
                    return DigimonVenomNXTFarmCore::IsSegmentWalkable(From.X, From.Y, To.X, To.Y, DigimonVenomNXTFarmCore::PlayerRadius);
                }
                if (PC->IsInRelay()) return PC->IsRelaySegmentWalkable(GetActorLocation(), Candidate);
                if (!PS || !WorldSystem) return false;
                return WorldSystem->IsWorldSegmentWalkable(PS->Profile.CurrentMapId, GetActorLocation(), Candidate);
            };

            if (!CanStand(MoveDirection))
            {
                const FVector Horizontal = (ScreenRight * Axis.X).GetSafeNormal();
                const FVector Vertical = (ScreenUp * Axis.Y).GetSafeNormal();
                if (!Horizontal.IsNearlyZero() && CanStand(Horizontal)) MoveDirection = Horizontal;
                else if (!Vertical.IsNearlyZero() && CanStand(Vertical)) MoveDirection = Vertical;
                else
                {
                    StopFieldMovement();
                    MoveDirection = FVector::ZeroVector;
                }
            }
            if (!MoveDirection.IsNearlyZero()) AddMovementInput(MoveDirection, 1.0f);
        }

        EDigimonFacing NewFacing = Facing;
        if (Axis.Y > 0.35f) NewFacing = Axis.X > 0.35f ? EDigimonFacing::UpRight : (Axis.X < -0.35f ? EDigimonFacing::UpLeft : EDigimonFacing::Up);
        else if (Axis.Y < -0.35f) NewFacing = Axis.X > 0.35f ? EDigimonFacing::DownRight : (Axis.X < -0.35f ? EDigimonFacing::DownLeft : EDigimonFacing::Down);
        else NewFacing = Axis.X > 0.0f ? EDigimonFacing::Right : EDigimonFacing::Left;
        if (NewFacing != Facing)
        {
            Facing = NewFacing;
            ApplyFacingVisual();
            if (!HasAuthority()) ServerSetFacing(NewFacing);
        }
    }
}


void ADigimonVenomNXTTamerCharacter::UpdateWalkAnimationState()
{
    if (!GetSprite() || !AnimationSet) return;

    const bool bHasInput = !GetPendingMovementInputVector().IsNearlyZero(0.01f);
    const bool bMoving = bHasInput || GetVelocity().SizeSquared2D() > FMath::Square(5.0f);
    // Source tamers use the shared clock while moving, the first pose at rest.
    DigimonVenomNXTFieldSizing::SetSourceClock(GetSprite(), bMoving);
}

void ADigimonVenomNXTTamerCharacter::StopFieldMovement()
{
    if (UCharacterMovementComponent* Movement = GetCharacterMovement())
    {
        Movement->StopMovementImmediately();
        Movement->Velocity = FVector::ZeroVector;
        Movement->UpdateComponentVelocity();
    }
    ConsumeMovementInputVector();
}

void ADigimonVenomNXTTamerCharacter::HandleLocalCameraZoom(float DeltaSeconds)
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Controller);
    if (!PC || !PC->IsLocalController() || !FollowCamera) return;

    // Discrete wheel keys are reliable in PIE/Standalone; MouseWheelAxis remains
    // as a fallback for devices that expose a continuous wheel axis.
    float Wheel = 0.0f;
    if (PC->WasInputKeyJustPressed(EKeys::MouseScrollUp)) Wheel += 1.0f;
    if (PC->WasInputKeyJustPressed(EKeys::MouseScrollDown)) Wheel -= 1.0f;
    if (FMath::IsNearlyZero(Wheel)) Wheel = PC->GetInputAnalogKeyState(EKeys::MouseWheelAxis);
    const UDigimonVenomNXTGameHUDWidget* HUD = PC->GetNativeHUDWidget();
    if (HUD && (HUD->IsWorldChatHovered() || HUD->IsWorldChatTyping())) Wheel = 0.0f;
    if (!FMath::IsNearlyZero(Wheel, 0.01f)) AdjustCameraZoom(Wheel);

    const bool bFarm = PC->IsInDigiFarm();
    const bool bCampaign = PC->IsInRelay();
    const int32 CameraContext = bFarm ? 2 : bCampaign ? 1 : 0;
    const bool bContextChanged = PresentedCameraContext != CameraContext;
    const int32 SourceMapId = bFarm ? -1 : PC->GetLocalMusicMapId();
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const FDigimonMapRow* Row = !bFarm && Data ? Data->FindMap(SourceMapId) : nullptr;
    if (!bFarm && (!Row || Row->SourceWidth <= 0 || Row->SourceHeight <= 0)) return;
    const double Width = bFarm ? DigimonVenomNXTFarmCore::WorldWidth : GetDefault<UDigimonVenomNXTSettings>()->MapWorldWidth;
    const double Height = bFarm ? DigimonVenomNXTFarmCore::WorldHeight : Width * Row->SourceHeight / Row->SourceWidth;
    FVector Origin = PresentedCameraOrigin;
    if (bFarm) Origin = PC->GetDigiFarmOrigin();
    else if (bCampaign) Origin = PC->GetRelayOrigin();
    else if (!bCameraFrameReady || PresentedCameraMapId != SourceMapId || bContextChanged)
    {
        const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>();
        const ADigimonVenomNXTMapZone* Zone = WorldSystem ? WorldSystem->FindMapZone(SourceMapId) : nullptr;
        if (!Zone) return;
        Origin = Zone->GetActorLocation();
    }
    const bool bMapChanged = !bCameraFrameReady || PresentedCameraMapId != SourceMapId || bContextChanged || !Origin.Equals(PresentedCameraOrigin, .01);
    int32 ViewportWidth = 0, ViewportHeight = 0;
    PC->GetViewportSize(ViewportWidth, ViewportHeight);
    const double Aspect = ViewportWidth > 0 && ViewportHeight > 0 ? static_cast<double>(ViewportWidth) / ViewportHeight : 16. / 9.;
    DesiredOrthoWidth = static_cast<float>(DigimonVenomNXTFieldSizingCore::CameraWidth(Width, Height, Aspect, FieldCameraZoom));
    const float Current = FollowCamera->OrthoWidth;
    const float Smoothed = bMapChanged ? DesiredOrthoWidth : FMath::FInterpTo(Current, DesiredOrthoWidth, DeltaSeconds, 12.0f);
    // Snap the final fraction instead of leaving the smoothed width just short
    // of its target (including an exact nameplate visibility threshold).
    FollowCamera->SetOrthoWidth(FMath::IsNearlyEqual(Smoothed, DesiredOrthoWidth, 0.1f) ? DesiredOrthoWidth : Smoothed);
    const FVector Location = GetActorLocation();
    const double ViewWidth = FollowCamera->OrthoWidth, ViewHeight = ViewWidth / Aspect;
    const FVector Target(
        DigimonVenomNXTFieldSizingCore::CameraCenter(Location.X, Origin.X, Width, ViewWidth),
        DigimonVenomNXTFieldSizingCore::CameraCenter(Location.Y, Origin.Y, Height, ViewHeight), 0.);
    FieldCameraCenter = bMapChanged ? Target : FMath::VInterpTo(FieldCameraCenter, Target, DeltaSeconds, 12.0f);
    // Clamp the smoothed center too: zooming out must not reveal space beyond
    // the authored map edge while the follow target catches up.
    FieldCameraCenter.X = DigimonVenomNXTFieldSizingCore::CameraCenter(FieldCameraCenter.X, Origin.X, Width, ViewWidth);
    FieldCameraCenter.Y = DigimonVenomNXTFieldSizingCore::CameraCenter(FieldCameraCenter.Y, Origin.Y, Height, ViewHeight);
    if (CameraBoom) CameraBoom->TargetOffset = FVector(FieldCameraCenter.X - Location.X, FieldCameraCenter.Y - Location.Y, 0.);
    PresentedCameraMapId = SourceMapId;
    PresentedCameraContext = CameraContext;
    PresentedCameraOrigin = Origin;
    bCameraFrameReady = true;
}

void ADigimonVenomNXTTamerCharacter::AdjustCameraZoom(float Direction)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const float Step = FMath::Clamp(Settings->FieldCameraZoomIncrement, .05f, 2.0f);
    FieldCameraZoom = FMath::Clamp(FieldCameraZoom + FMath::Sign(Direction) * Step, 1.0f, 8.0f);
}

void ADigimonVenomNXTTamerCharacter::ResetEncounterTracker()
{
    LastEncounterLocation = GetActorLocation();
    EncounterDistanceAccumulator = 0.0f;
    EncounterSafeDistanceRemaining = GetDefault<UDigimonVenomNXTSettings>()->EncounterSafeDistanceAfterTravel;
    bEncounterTrackerReady = true;
    if (HasAuthority())
    {
        const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
        const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Controller);
        const FVector Local = PC ? GetActorLocation() - PC->GetDigiFarmOrigin() : FVector::ZeroVector;
        const bool bWalkable = PC && PC->IsInDigiFarm()
            ? DigimonVenomNXTFarmCore::IsWalkable(Local.X, Local.Y, DigimonVenomNXTFarmCore::PlayerRadius)
            : PC && PC->IsInRelay() ? PC->IsRelayLocationWalkable(GetActorLocation())
            : PS && WorldSystem && WorldSystem->IsWorldLocationWalkable(PS->Profile.CurrentMapId, GetActorLocation());
        bHasValidWalkableLocation = bWalkable;
        if (bWalkable) LastValidWalkableLocation = GetActorLocation();
    }
}

void ADigimonVenomNXTTamerCharacter::EnforceServerMapCollision()
{
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!PS) return;
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Controller);
    const FVector Current = GetActorLocation();
    if (PC && (PC->CurrentBattle || DigimonVenomNXTCampaign::HasPendingBattle(PS->Profile)))
    {
        // Pending campaign decisions freeze the field on the host as well as the owning client.
        if (bHasValidWalkableLocation && !Current.Equals(LastValidWalkableLocation, 1.0f))
            TeleportTo(LastValidWalkableLocation, GetActorRotation(), false, true);
        GetCharacterMovement()->StopMovementImmediately();
        return;
    }
    if (PC && PC->IsInDigiFarm())
    {
        const FVector Local = Current - PC->GetDigiFarmOrigin();
        const FVector PreviousLocal = LastValidWalkableLocation - PC->GetDigiFarmOrigin();
        const bool bValid = FMath::IsNearlyEqual(Local.Z, 100.0, 150.0) &&
            DigimonVenomNXTFarmCore::IsWalkable(Local.X, Local.Y, DigimonVenomNXTFarmCore::PlayerRadius) &&
            (!bHasValidWalkableLocation || DigimonVenomNXTFarmCore::IsSegmentWalkable(
                PreviousLocal.X, PreviousLocal.Y, Local.X, Local.Y, DigimonVenomNXTFarmCore::PlayerRadius));
        if (bValid)
        {
            LastValidWalkableLocation = Current;
            bHasValidWalkableLocation = true;
            return;
        }
        if (!bHasValidWalkableLocation)
        {
            const auto Spawn = DigimonVenomNXTFarmCore::FindSafePoint(DigimonVenomNXTFarmCore::SpawnX, DigimonVenomNXTFarmCore::SpawnY, DigimonVenomNXTFarmCore::PlayerRadius);
            LastValidWalkableLocation = PC->GetDigiFarmOrigin() + FVector(Spawn.X, Spawn.Y, 100.0);
            bHasValidWalkableLocation = true;
        }
        // The server rejects the entire crossed segment, preventing a large movement
        // update from jumping over water and landing on the opposite shore.
        TeleportTo(LastValidWalkableLocation, GetActorRotation(), false, true);
        GetCharacterMovement()->StopMovementImmediately();
        return;
    }
    if (PC && PC->IsInRelay())
    {
        const FVector Local = Current - PC->GetRelayOrigin();
        const bool bValid = FMath::IsNearlyEqual(Local.Z, 100.0, 150.0) && PC->IsRelayLocationWalkable(Current) &&
            (!bHasValidWalkableLocation || PC->IsRelaySegmentWalkable(LastValidWalkableLocation, Current));
        if (bValid) { LastValidWalkableLocation = Current; bHasValidWalkableLocation = true; return; }
        if (!bHasValidWalkableLocation)
        {
            LastValidWalkableLocation = PC->GetRelayPortalLocation(false);
            bHasValidWalkableLocation = !LastValidWalkableLocation.IsNearlyZero();
        }
        if (bHasValidWalkableLocation) TeleportTo(LastValidWalkableLocation, GetActorRotation(), false, true);
        GetCharacterMovement()->StopMovementImmediately();
        return;
    }
    if (!WorldSystem) return;
    if (WorldSystem->IsWorldLocationWalkable(PS->Profile.CurrentMapId, Current) &&
        (!bHasValidWalkableLocation || WorldSystem->IsWorldSegmentWalkable(
            PS->Profile.CurrentMapId, LastValidWalkableLocation, Current)))
    {
        LastValidWalkableLocation = Current;
        bHasValidWalkableLocation = true;
        return;
    }

    if (!bHasValidWalkableLocation)
    {
        // A stale/corrupt location must recover to a verified map spawn instead
        // of leaving a newly joined tamer permanently outside the collision mask.
        const ADigimonVenomNXTMapZone* Zone = WorldSystem->FindMapZone(PS->Profile.CurrentMapId);
        if (Zone && WorldSystem->IsWorldLocationWalkable(PS->Profile.CurrentMapId, Zone->GetPlayerSpawnLocation()))
        {
            LastValidWalkableLocation = Zone->GetPlayerSpawnLocation();
            bHasValidWalkableLocation = true;
        }
    }
    if (bHasValidWalkableLocation) TeleportTo(LastValidWalkableLocation, GetActorRotation(), false, true);
    GetCharacterMovement()->StopMovementImmediately();
}

void ADigimonVenomNXTTamerCharacter::HandleServerWalkingEncounter()
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Controller);
    if (!PC || !PC->IsAccountAuthenticated() || PC->CurrentBattle || PC->IsInDigiFarm() || PC->IsInRelay()) { LastEncounterLocation = GetActorLocation(); return; }
    if (!bEncounterTrackerReady) { ResetEncounterTracker(); return; }

    const FVector Current = GetActorLocation();
    const float DeltaDistance = FVector::Dist2D(Current, LastEncounterLocation);
    LastEncounterLocation = Current;

    // Teleports/large corrections should never count as encounter walking.
    if (DeltaDistance <= 0.5f || DeltaDistance > 500.0f) return;
    if (GetVelocity().SizeSquared2D() < FMath::Square(20.0f)) return;

    if (EncounterSafeDistanceRemaining > 0.0f)
    {
        EncounterSafeDistanceRemaining = FMath::Max(0.0f, EncounterSafeDistanceRemaining - DeltaDistance);
        return;
    }

    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    EncounterDistanceAccumulator += DeltaDistance;
    const float StepDistance = FMath::Max(50.0f, Settings->EncounterStepDistance);
    while (EncounterDistanceAccumulator >= StepDistance && !PC->CurrentBattle)
    {
        EncounterDistanceAccumulator -= StepDistance;
        if (FMath::FRand() <= Settings->EncounterChancePerStep)
        {
            if (PC->TryStartWalkingWildEncounter())
            {
                ResetEncounterTracker();
                break;
            }
        }
    }
}

void ADigimonVenomNXTTamerCharacter::ServerSetFacing_Implementation(EDigimonFacing NewFacing)
{
    Facing = NewFacing;
    ApplyFacingVisual();
}

void ADigimonVenomNXTTamerCharacter::OnRep_Facing()
{
    ApplyFacingVisual();
}

void ADigimonVenomNXTTamerCharacter::RefreshTamerStyleFromProfile()
{
    if (!HasAuthority()) return;
    if (const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>())
    {
        TamerStyleId = DigimonVenomNXTTamers::IsValidStyle(PS->Profile.TamerStyleId)
            ? PS->Profile.TamerStyleId : DigimonVenomNXTTamers::StyleForIndex(0);
        OnRep_TamerStyle();
        ForceNetUpdate();
    }
}

void ADigimonVenomNXTTamerCharacter::OnRep_TamerStyle()
{
    if (GetNetMode() == NM_DedicatedServer) return;
    const FName StyleId = DigimonVenomNXTTamers::IsValidStyle(TamerStyleId) ? TamerStyleId : DigimonVenomNXTTamers::StyleForIndex(0);
    AnimationSet = LoadObject<UDigimonVenomNXTTamerAnimationSet>(nullptr, *DigimonVenomNXTTamers::AnimationPath(StyleId));
    // A missing import must not leave the previously selected character on screen.
    // The importer and cook validator report the specific missing roster asset.
    if (!AnimationSet)
        UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT tamer style %s is not imported; run Import Tamer Roster before packaging."), *StyleId.ToString());
    ApplyFacingVisual();
}

void ADigimonVenomNXTTamerCharacter::ApplyFacingVisual()
{
    if (GetSprite())
    {
        GetSprite()->SetFlipbook(AnimationSet ? AnimationSet->GetForFacing(Facing) : nullptr);
        // The field camera uses +90 yaw while the front-facing +90 Paper2D roll maps
        // source-up to world +Y. A negative local-X scale compensates the camera
        // handedness, so the source left/right frames appear on their authored side.
        DigimonVenomNXTFieldSizing::ApplyTamer(GetSprite(), AnimationSet, DigimonVenomNXTFieldSizing::PawnWorldPerPixel(this));
        UpdateWalkAnimationState();
    }
    BP_OnFacingChanged(Facing);
}

void ADigimonVenomNXTTamerCharacter::RefreshFollowerFromProfile()
{
    if (!HasAuthority() || !GetWorld()) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || PS->Profile.Party.Num() == 0 ||
        (PS->Profile.Farm.bInside && PS->Profile.DigiFarmResidents.Contains(PS->Profile.Party[0])))
    {
        if (Follower) { Follower->Destroy(); Follower = nullptr; }
        return;
    }
    FDigimonOwnedPartner Lead;
    if (!PS->GetPartner(PS->Profile.Party[0], Lead)) return;
    if (!Follower)
    {
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;
        UClass* SpawnClass = FollowerClass ? FollowerClass.Get() : ADigimonVenomNXTPartnerFollower::StaticClass();
        Follower = GetWorld()->SpawnActor<ADigimonVenomNXTPartnerFollower>(SpawnClass, GetActorLocation() - FVector(250.0f, 0.0f, 0.0f), GetActorRotation(), Params);
    }
    if (Follower) Follower->InitializeFromPartner(this, Lead);
}

void ADigimonVenomNXTTamerCharacter::SnapFollowerToTamer()
{
    if (Follower) Follower->SnapToTamer();
}

void ADigimonVenomNXTTamerCharacter::OnRep_Follower()
{
    BP_OnFollowerChanged(Follower);
}

bool ADigimonVenomNXTTamerCharacter::IsVisibleToViewer(const ADigimonVenomNXTPlayerController* Viewer) const
{
    if (!Viewer) return false;
    const ADigimonVenomNXTPlayerState* Subject = GetPlayerState<ADigimonVenomNXTPlayerState>();
    return DigimonVenomNXTRelaySessionCore::MayObserve(Viewer->IsAccountAuthenticated(), Viewer->GetPawn() == this,
        Viewer->IsInDigiFarm() || Viewer->IsInRelay(), !Subject || Subject->PublicSnapshot.bInDigiFarm || Subject->PublicSnapshot.bInRelay,
        Subject && Subject->PublicSnapshot.MapId == Viewer->GetLocalMusicMapId());
}

bool ADigimonVenomNXTTamerCharacter::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
    const ADigimonVenomNXTPlayerController* Viewer = Cast<ADigimonVenomNXTPlayerController>(RealViewer);
    if (!Viewer)
    {
        const APawn* ViewerPawn = Cast<APawn>(ViewTarget);
        Viewer = ViewerPawn ? Cast<ADigimonVenomNXTPlayerController>(ViewerPawn->GetController()) : nullptr;
    }
    if (!Viewer) return false;
    const ADigimonVenomNXTPlayerState* Subject = GetPlayerState<ADigimonVenomNXTPlayerState>();
    const ADigimonVenomNXTPlayerState* Observer = Viewer->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const bool bOwnTamer = Viewer->GetPawn() == this;
    if (!DigimonVenomNXTRelaySessionCore::MayObserve(Viewer->IsAccountAuthenticated(), bOwnTamer,
        Viewer->IsInDigiFarm() || Viewer->IsInRelay(), !Subject || Subject->Profile.Farm.bInside || DigimonVenomNXTCampaign::IsActive(Subject->Profile),
        Subject && Observer && Subject->Profile.CurrentMapId == Observer->Profile.CurrentMapId)) return false;
    if (bOwnTamer) return true;
    return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}
