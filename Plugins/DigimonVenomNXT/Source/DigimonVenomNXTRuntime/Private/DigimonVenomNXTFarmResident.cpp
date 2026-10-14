#include "DigimonVenomNXTFarmResident.h"
#include "DigimonVenomNXTFarmScene.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTFieldSizing.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "PaperFlipbookComponent.h"

UDigimonVenomNXTFarmResidentSelectButton::UDigimonVenomNXTFarmResidentSelectButton(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InitIsFocusable(false);
}

void UDigimonVenomNXTFarmResidentNameplate::InitializeFor(ADigimonVenomNXTFarmResident* InResident)
{
    Resident = InResident;
}

TSharedRef<SWidget> UDigimonVenomNXTFarmResidentNameplate::RebuildWidget()
{
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("FarmResidentNameplateTree"));
    Plate = WidgetTree->ConstructWidget<UBorder>();
    Plate->SetPadding(FMargin(0.0f));
    WidgetTree->RootWidget = Plate;
    SelectButton = WidgetTree->ConstructWidget<UDigimonVenomNXTFarmResidentSelectButton>();
    SelectButton->SetBackgroundColor(FLinearColor::Transparent);
    SelectButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTFarmResidentNameplate::HandleClicked);
    Plate->AddChild(SelectButton);
    Label = WidgetTree->ConstructWidget<UTextBlock>();
    FSlateFontInfo Font = Label->GetFont();
    Font.Size = 11; Font.TypefaceFontName = TEXT("Bold");
    Label->SetFont(Font);
    Label->SetJustification(ETextJustify::Center);
    Label->SetAutoWrapText(false);
    Label->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    Label->SetVisibility(ESlateVisibility::HitTestInvisible);
    SelectButton->AddChild(Label);
    SetToolTipText(FText::FromString(TEXT("Select this resident for quick feeding")));
    ApplyIdentity();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTFarmResidentNameplate::SetIdentity(const FString& Name, int32 Level, bool bSelected)
{
    if (ResidentName == Name && ResidentLevel == Level && bResidentSelected == bSelected) return;
    ResidentName = Name; ResidentLevel = Level; bResidentSelected = bSelected;
    ApplyIdentity();
}

void UDigimonVenomNXTFarmResidentNameplate::ApplyIdentity()
{
    if (!Plate || !Label) return;
    const FLinearColor Accent = bResidentSelected ? FLinearColor(1.0f, 0.78f, 0.28f) : FLinearColor(0.2f, 0.9f, 0.84f);
    Plate->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.015f, 0.06f, 0.09f, 0.92f), 7.0f,
        Accent.CopyWithNewOpacity(bResidentSelected ? 1.0f : 0.6f), bResidentSelected ? 2.0f : 1.0f));
    Label->SetText(FText::FromString(FString::Printf(TEXT("%s  |  Lv %d"), *ResidentName, ResidentLevel)));
    Label->SetColorAndOpacity(bResidentSelected ? Accent : FLinearColor(0.94f, 1.0f, 1.0f));
}

void UDigimonVenomNXTFarmResidentNameplate::HandleClicked()
{
    if (Resident.IsValid()) Resident->RequestSelection();
}

ADigimonVenomNXTFarmResident::ADigimonVenomNXTFarmResident()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PostUpdateWork;
    bReplicates = false;
    SetActorEnableCollision(false);
    Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ResidentSprite"));
    SetRootComponent(Sprite);
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    Sprite->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
    Sprite->SetLooping(true);
    DigimonVenomNXTFieldSprite::ConfigureDefaults(Sprite);
}

void ADigimonVenomNXTFarmResident::BeginPlay()
{
    Super::BeginPlay();
    DigimonVenomNXTFieldSprite::Configure(Sprite);
}

void ADigimonVenomNXTFarmResident::InitializeFor(ADigimonVenomNXTFarmScene* Scene, ADigimonVenomNXTPlayerController* Viewer,
    const FDigimonOwnedPartner& Partner, const FVector& Origin, const FVector2D& LocalPosition)
{
    if (!Scene || !Viewer || !Viewer->IsLocalController()) return;
    FarmScene = Scene; OwningViewer = Viewer; FarmOrigin = Origin;
    SetOwner(Viewer);
    RoamRandom.Initialize(static_cast<int32>(GetTypeHash(Partner.InstanceId)));
    const DigimonVenomNXTFarmCore::Point Safe = DigimonVenomNXTFarmCore::FindSafePoint(LocalPosition.X, LocalPosition.Y, DigimonVenomNXTFarmCore::ResidentRadius);
    SetActorLocation(Origin + FVector(Safe.X, Safe.Y, 70.0));
    RefreshPartner(Partner);
    Nameplate = CreateWidget<UDigimonVenomNXTFarmResidentNameplate>(Viewer);
    if (Nameplate)
    {
        Nameplate->InitializeFor(this);
        Nameplate->SetIdentity(DisplayName, Snapshot.Level, bIsSelected);
        Nameplate->SetDesiredSizeInViewport(FVector2D(214.0f, 29.0f));
        Nameplate->SetAlignmentInViewport(FVector2D(0.5f, 1.0f));
        Nameplate->AddToPlayerScreen(4);
    }
    WaitRemaining = RoamRandom.FRandRange(0.5f, 3.5f);
}

void ADigimonVenomNXTFarmResident::RefreshPartner(const FDigimonOwnedPartner& Partner)
{
    if (!Partner.IsValid()) return;
    const bool bAnimationChanged = Snapshot.SpeciesId != Partner.SpeciesId || Snapshot.Variant != Partner.Variant || !AnimationSet;
    Snapshot = Partner;
    DisplayName = Partner.Nickname;
    if (DisplayName.IsEmpty())
    {
        FDigimonSpeciesDefinition Definition;
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        DisplayName = Data && Data->GetSpecies(Partner.SpeciesId, Definition) ? Definition.DisplayName.ToString() : Partner.SpeciesId.ToString();
    }
    if (bAnimationChanged)
    {
        const FString VariantFolder = DigimonVenomNXTPartnerArt::VariantFolder(Partner.Variant);
        const FString Species = Partner.SpeciesId.ToString();
        const FString AssetName = FString::Printf(TEXT("DA_%s_%s_Animation"), *Species, *VariantFolder);
        const FString AssetPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Digimon/%s/%s/%s.%s"), *VariantFolder, *Species, *AssetName, *AssetName);
        AnimationSet = LoadObject<UDigimonVenomNXTPartnerAnimationSet>(nullptr, *AssetPath);
        Sprite->SetFlipbook(AnimationSet ? AnimationSet->Idle.Get() : nullptr);
        if (AnimationSet)
        {
            Sprite->Play();
            Sprite->SetPlaybackPosition(RoamRandom.FRandRange(0.0f, FMath::Max(0.01f, Sprite->GetFlipbookLength())), false);
        }
        DigimonVenomNXTFieldSprite::Configure(Sprite);
    }
    if (Nameplate) Nameplate->SetIdentity(DisplayName, Snapshot.Level, bIsSelected);
}

void ADigimonVenomNXTFarmResident::SetFarmVisible(bool bVisible)
{
    bFarmVisible = bVisible;
    SetActorHiddenInGame(!bVisible);
    SetActorTickEnabled(bVisible);
    if (Nameplate) Nameplate->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void ADigimonVenomNXTFarmResident::SetSelected(bool bSelected)
{
    if (bIsSelected == bSelected) return;
    bIsSelected = bSelected;
    if (Nameplate) Nameplate->SetIdentity(DisplayName, Snapshot.Level, bIsSelected);
    // Pause briefly on selection for easy feeding; every resident resumes roaming.
    if (bSelected) { bHasTarget = false; WaitRemaining = 2.0f; }
}

void ADigimonVenomNXTFarmResident::RequestSelection()
{
    if (FarmScene.IsValid()) FarmScene->SelectResident(Snapshot.InstanceId);
}

void ADigimonVenomNXTFarmResident::ChooseRoamTarget()
{
    const FVector Current = GetActorLocation() - FarmOrigin;
    for (int32 Attempt = 0; Attempt < 24; ++Attempt)
    {
        const float Angle = RoamRandom.FRandRange(0.0f, 2.0f * PI);
        const float Distance = RoamRandom.FRandRange(150.0f, 650.0f);
        const FVector2D Candidate(Current.X + FMath::Cos(Angle) * Distance, Current.Y + FMath::Sin(Angle) * Distance);
        if (!DigimonVenomNXTFarmCore::IsSegmentWalkable(Current.X, Current.Y, Candidate.X, Candidate.Y, DigimonVenomNXTFarmCore::ResidentRadius)) continue;
        RoamTarget = Candidate; bHasTarget = true; return;
    }
    WaitRemaining = RoamRandom.FRandRange(1.0f, 3.0f);
}

FVector ADigimonVenomNXTFarmResident::GetNameplateAnchor() const
{
    if (!Sprite || !OwningViewer.IsValid() || !OwningViewer->PlayerCameraManager) return GetActorLocation();
    const FVector Up = OwningViewer->PlayerCameraManager->GetCameraRotation().RotateVector(FVector::UpVector);
    const FVector Extent = Sprite->Bounds.BoxExtent;
    const float ProjectedHalfHeight = FMath::Abs(Up.X) * Extent.X + FMath::Abs(Up.Y) * Extent.Y + FMath::Abs(Up.Z) * Extent.Z;
    return Sprite->Bounds.Origin + Up * ProjectedHalfHeight;
}

void ADigimonVenomNXTFarmResident::RefreshNameplate()
{
    if (!Nameplate || !OwningViewer.IsValid()) return;
    FVector2D Position = FVector2D::ZeroVector;
    const bool bProjected = bFarmVisible && UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(OwningViewer.Get(), GetNameplateAnchor(), Position, true);
    const FVector2D Size = UWidgetLayoutLibrary::GetPlayerScreenWidgetGeometry(OwningViewer.Get()).GetLocalSize();
    Position.Y -= 5.0f;
    const bool bOnScreen = bProjected && Size.X > 0.0 && Size.Y > 0.0 &&
        Position.X >= 107.0 && Position.X <= Size.X - 107.0 && Position.Y >= 29.0 && Position.Y <= Size.Y;
    Nameplate->SetVisibility(bOnScreen ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (bOnScreen) Nameplate->SetPositionInViewport(Position, false);
}

void ADigimonVenomNXTFarmResident::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!FarmScene.IsValid() || !OwningViewer.IsValid()) { Destroy(); return; }
    if (!bFarmVisible) return;
    const float FrameTime = FMath::Clamp(DeltaSeconds, 0.0f, 0.1f);
    bool bWalking = false;
    {
        WaitRemaining = FMath::Max(0.0f, WaitRemaining - FrameTime);
        if (!bHasTarget && WaitRemaining <= 0.0f) ChooseRoamTarget();
        if (bHasTarget)
        {
            const FVector Current = GetActorLocation() - FarmOrigin;
            const FVector2D Delta = RoamTarget - FVector2D(Current.X, Current.Y);
            const double Distance = Delta.Size();
            if (Distance < 4.0)
            {
                bHasTarget = false; WaitRemaining = RoamRandom.FRandRange(2.0f, 6.0f);
            }
            else
            {
                const FVector2D Step = Delta.GetSafeNormal() * FMath::Min(Distance, 115.0 * FrameTime);
                const FVector2D Next(Current.X + Step.X, Current.Y + Step.Y);
                if (DigimonVenomNXTFarmCore::IsSegmentWalkable(Current.X, Current.Y, Next.X, Next.Y, DigimonVenomNXTFarmCore::ResidentRadius))
                {
                    SetActorLocation(FarmOrigin + FVector(Next.X, Next.Y, Current.Z));
                    if (FMath::Abs(Step.X) > 0.05) bFacingLeft = Step.X > 0.0;
                    bWalking = true;
                }
                else { bHasTarget = false; WaitRemaining = 0.5f; }
            }
        }
    }
    if (AnimationSet)
    {
        UPaperFlipbook* Idle = bFacingLeft && AnimationSet->bHasAuthoredLeftFrames && AnimationSet->IdleLeft
            ? AnimationSet->IdleLeft.Get() : AnimationSet->Idle.Get();
        UPaperFlipbook* Desired = bWalking ? (bFacingLeft ? AnimationSet->WalkLeft.Get() : AnimationSet->WalkRight.Get()) : Idle;
        if (!Desired) Desired = AnimationSet->Idle.Get();
        if (Desired && Sprite->GetFlipbook() != Desired) Sprite->SetFlipbook(Desired);
        DigimonVenomNXTFieldSizing::SetSourceClock(Sprite);
        DigimonVenomNXTFieldSizing::ApplyPartner(Sprite, AnimationSet,
            DigimonVenomNXTFieldSizing::FarmWorldPerPixel(), bFacingLeft);
    }
    DigimonVenomNXTFieldSprite::UpdateDepth(Sprite);
    RefreshNameplate();
}

void ADigimonVenomNXTFarmResident::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Nameplate) Nameplate->RemoveFromParent();
    Nameplate = nullptr;
    Super::EndPlay(EndPlayReason);
}
