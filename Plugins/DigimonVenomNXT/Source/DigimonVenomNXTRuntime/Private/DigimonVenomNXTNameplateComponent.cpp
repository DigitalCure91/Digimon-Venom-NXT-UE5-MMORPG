#include "DigimonVenomNXTNameplateComponent.h"
#include "DigimonVenomNXTNameplateCore.h"
#include "DigimonVenomNXTNameplateWidget.h"
#include "DigimonVenomNXTAIRivalAvatar.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/World.h"
#include "PaperFlipbookComponent.h"

UDigimonVenomNXTNameplateComponent::UDigimonVenomNXTNameplateComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
    SetIsReplicatedByDefault(false);
}

void UDigimonVenomNXTNameplateComponent::BeginPlay()
{
    Super::BeginPlay();
    // Dedicated servers never create UMG objects or spend time projecting labels.
    if (GetNetMode() == NM_DedicatedServer) SetComponentTickEnabled(false);
}

void UDigimonVenomNXTNameplateComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (UDigimonVenomNXTNameplateWidget* Label : LocalNameplates)
        if (IsValid(Label)) { Label->CloseContextMenu(); Label->RemoveFromParent(); }
    LocalNameplates.Reset();
    Super::EndPlay(EndPlayReason);
}

void UDigimonVenomNXTNameplateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!GetWorld() || !IsValid(GetOwner()) || GetNetMode() == NM_DedicatedServer) return;

    const ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetOwner());
    const ADigimonVenomNXTAIRivalAvatar* Rival = Cast<ADigimonVenomNXTAIRivalAvatar>(GetOwner());
    const ADigimonVenomNXTPlayerState* SubjectPlayer = Tamer ? Tamer->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    const FString Name = Rival ? Rival->DisplayName : SubjectPlayer ? SubjectPlayer->PublicSnapshot.Username : FString();
    const FString Title = SubjectPlayer ? SubjectPlayer->PublicSnapshot.EquippedTitle.Left(32) : FString();
    const float PlateHeight = Title.IsEmpty() ? 28.0f : 46.0f;
    const int32 SubjectMapId = Rival ? Rival->MapId : SubjectPlayer ? SubjectPlayer->PublicSnapshot.MapId : INDEX_NONE;
    const UPaperFlipbookComponent* SubjectSprite = Rival ? Rival->Sprite.Get() : Tamer ? Tamer->GetSprite() : nullptr;
    const bool bActive = !GetOwner()->IsHidden() && SubjectSprite && SubjectSprite->IsVisible() && !Name.IsEmpty();

    // Removed local players, travel and actor teardown must never leave a frozen label behind.
    for (int32 Index = LocalNameplates.Num() - 1; Index >= 0; --Index)
    {
        UDigimonVenomNXTNameplateWidget* Label = LocalNameplates[Index];
        const APlayerController* Viewer = IsValid(Label) ? Label->GetOwningPlayer() : nullptr;
        if (!IsValid(Viewer) || !Viewer->IsLocalController() || Viewer->GetWorld() != GetWorld())
        {
            if (IsValid(Label)) { Label->CloseContextMenu(); Label->RemoveFromParent(); }
            LocalNameplates.RemoveAt(Index);
        }
    }

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        ADigimonVenomNXTPlayerController* Viewer = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!Viewer || !Viewer->IsLocalController() || !Viewer->GetLocalPlayer()) continue;
        UDigimonVenomNXTNameplateWidget* Label = nullptr;
        for (UDigimonVenomNXTNameplateWidget* Existing : LocalNameplates)
            if (Existing && Existing->GetOwningPlayer() == Viewer) { Label = Existing; break; }

        const ADigimonVenomNXTTamerCharacter* ViewerTamer = Cast<ADigimonVenomNXTTamerCharacter>(Viewer->GetPawn());
        const ADigimonVenomNXTPlayerState* ViewerPlayer = Viewer->GetPlayerState<ADigimonVenomNXTPlayerState>();
        const bool bOwnTamer = ViewerTamer && ViewerTamer == Tamer;
        // A farm's private presence must never match another farm just because
        // both public snapshots deliberately hide their map with INDEX_NONE.
        const bool bSameSpace = bOwnTamer || (!Viewer->IsInDigiFarm() && !Viewer->IsInRelay() &&
            (!SubjectPlayer || (!SubjectPlayer->PublicSnapshot.bInDigiFarm && !SubjectPlayer->PublicSnapshot.bInRelay)) &&
            ViewerPlayer && SubjectMapId != INDEX_NONE && ViewerPlayer->PublicSnapshot.MapId == SubjectMapId);
        bool bShow = DigimonVenomNXTNameplateCore::ShouldShow(
            bActive && Viewer->IsAccountAuthenticated() && !Viewer->IsFieldPresentationBlocked(),
            bSameSpace);

        FVector2D Position = FVector2D::ZeroVector;
        if (bShow)
        {
            // A world-Z offset is ineffective with a true top-down camera. Project the
            // sprite's actual upper silhouette along this viewer's camera-up vector.
            FVector ViewLocation; FRotator ViewRotation;
            Viewer->GetPlayerViewPoint(ViewLocation, ViewRotation);
            const FVector Up = FRotationMatrix(ViewRotation).GetUnitAxis(EAxis::Z);
            const FVector Right = FRotationMatrix(ViewRotation).GetUnitAxis(EAxis::Y);
            const FVector Extent = SubjectSprite->Bounds.BoxExtent;
            const double HalfHeight = FMath::Abs(Up.X) * Extent.X + FMath::Abs(Up.Y) * Extent.Y + FMath::Abs(Up.Z) * Extent.Z;
            const double HalfWidth = FMath::Abs(Right.X) * Extent.X + FMath::Abs(Right.Y) * Extent.Y + FMath::Abs(Right.Z) * Extent.Z;
            const FVector Anchor = SubjectSprite->Bounds.Origin + Up * HalfHeight;
            bShow = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Viewer, Anchor, Position, true);
            Position.Y -= 7.0f;
            const FVector2D ViewSize = UWidgetLayoutLibrary::GetPlayerScreenWidgetGeometry(Viewer).GetLocalSize();
            // In the orthographic field view these two corners bound the sprite's
            // projected silhouette. Test it before clamping the label, so names
            // do not disappear at screen edges or stick there after actors leave.
            if (bShow && !bOwnTamer)
            {
                FVector2D TopLeft, BottomRight;
                const FVector Center = SubjectSprite->Bounds.Origin;
                bShow = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
                    Viewer, Center + Up * HalfHeight - Right * HalfWidth, TopLeft, true) &&
                    UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
                    Viewer, Center - Up * HalfHeight + Right * HalfWidth, BottomRight, true) &&
                    DigimonVenomNXTNameplateCore::IntersectsViewport(TopLeft.X, TopLeft.Y, BottomRight.X,
                        BottomRight.Y, ViewSize.X, ViewSize.Y);
            }
            // Labels remain a fixed, readable screen size at every scroll distance.
            const DigimonVenomNXTNameplateCore::Anchor Fitted = DigimonVenomNXTNameplateCore::FitAnchor(
                Position.X, Position.Y, ViewSize.X, ViewSize.Y, PlateHeight);
            bShow = bShow && Fitted.Visible;
            Position = FVector2D(Fitted.X, Fitted.Y);
        }
        if (!Label && bShow)
        {
            Label = CreateWidget<UDigimonVenomNXTNameplateWidget>(Viewer, UDigimonVenomNXTNameplateWidget::StaticClass());
            if (Label)
            {
                Label->SetDesiredSizeInViewport(FVector2D(210.0f, PlateHeight));
                Label->SetAlignmentInViewport(FVector2D(0.5f, 1.0f));
                Label->AddToPlayerScreen(0);
                LocalNameplates.Add(Label);
            }
        }
        if (!Label) continue;
        // A viewport reset may remove widgets while a seamless-travel actor survives.
        if (bShow && !Label->IsInViewport()) Label->AddToPlayerScreen(0);
        Label->SetDesiredSizeInViewport(FVector2D(210.0f, PlateHeight));
        Label->SetIdentity(Name, bOwnTamer, Rival != nullptr, Title, Rival ? Rival->RivalId : SubjectPlayer ? SubjectPlayer->PublicSnapshot.AccountId : FString());
        if (!bShow) Label->CloseContextMenu();
        Label->SetVisibility(bShow ? (bOwnTamer ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible) : ESlateVisibility::Collapsed);
        // Projection already returns DPI-correct widget coordinates; do not divide twice.
        if (bShow) Label->SetPositionInViewport(Position, false);
    }
}
