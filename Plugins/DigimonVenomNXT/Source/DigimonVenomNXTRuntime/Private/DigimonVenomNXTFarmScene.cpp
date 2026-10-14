#include "DigimonVenomNXTFarmScene.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTSpriteCoordinates.h"
#include "DigimonVenomNXTFarmResident.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

ADigimonVenomNXTFarmScene::ADigimonVenomNXTFarmScene()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = false;
    SetActorEnableCollision(false);
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FarmRoot"));
    SetRootComponent(SceneRoot);
    IslandSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("IslandSprite"));
    IslandSprite->SetupAttachment(SceneRoot);
    IslandSprite->SetMobility(EComponentMobility::Movable);
    IslandSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    IslandSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    IslandSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -6.0f));
    IslandSprite->SetCastShadow(false);
    IslandSprite->SetRenderCustomDepth(true);
    IslandSprite->SetTranslucentSortPriority(-100);
    SetActorHiddenInGame(true);
}

bool ADigimonVenomNXTFarmScene::InitializeFor(ADigimonVenomNXTPlayerController* InOwner, FVector Origin)
{
    if (!InOwner || !InOwner->IsLocalController() || GetNetMode() == NM_DedicatedServer) return false;
    OwningController = InOwner;
    SetOwner(InOwner);
    SetActorLocation(Origin);
    UPaperSprite* Island = LoadObject<UPaperSprite>(nullptr,
        TEXT("/DigimonVenomNXT/Generated/Maps/SP_DigiFarmIsland.SP_DigiFarmIsland"));
    if (!Island)
    {
        UE_LOG(LogTemp, Error, TEXT("DigiFarm island sprite is missing. Run Tools > Digimon Venom NXT: Prepare Private DigiFarm, then save/cook the generated assets."));
        SetFarmVisible(false);
        return false;
    }
    IslandSprite->SetSprite(Island);
    IslandSprite->SetRenderCustomDepth(true);
    const FVector2D ImageSize = DigimonVenomNXTSpriteCoordinates::GetImageSize(Island);
    if (ImageSize.X <= 0.0 || ImageSize.Y <= 0.0)
    {
        UE_LOG(LogTemp, Error, TEXT("DigiFarm island has no valid cooked sprite mapping."));
        SetFarmVisible(false);
        return false;
    }
    const double NativeWidth = FMath::Max(1.0, static_cast<double>(ImageSize.X) * Island->GetUnrealUnitsPerPixel());
    const double Scale = DigimonVenomNXTFarmCore::WorldWidth / NativeWidth;
    IslandSprite->SetRelativeScale3D(FVector(-Scale, Scale, Scale));
    // Collision uses the source canvas centre. Paper2D can snap a centre pivot
    // on this odd-height (941px) image, and old imported assets may retain edits.
    // Align the rendered canvas itself so neither case offsets the shoreline.
    const FVector LocalCentre = DigimonVenomNXTSpriteCoordinates::ImageToLocal(Island, ImageSize * 0.5);
    const FVector CentreOffset = IslandSprite->GetRelativeTransform().TransformVector(LocalCentre);
    IslandSprite->SetRelativeLocation(FVector(-CentreOffset.X, -CentreOffset.Y, -6.0));
    bPresentationReady = true;
    SetFarmVisible(true);
    RefreshResidents();
    return true;
}

void ADigimonVenomNXTFarmScene::SetFarmVisible(bool bVisible)
{
    bFarmVisible = bVisible && bPresentationReady;
    SetActorHiddenInGame(!bFarmVisible);
    SetActorTickEnabled(bFarmVisible);
    for (ADigimonVenomNXTFarmResident* Resident : Residents)
        if (IsValid(Resident)) Resident->SetFarmVisible(bFarmVisible);
}

void ADigimonVenomNXTFarmScene::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!OwningController.IsValid()) { Destroy(); return; }
    RefreshRemaining -= DeltaSeconds;
    if (RefreshRemaining <= 0.0f)
    {
        RefreshRemaining = 0.5f;
        RefreshResidents();
    }
}

void ADigimonVenomNXTFarmScene::RefreshResidents()
{
    if (!OwningController.IsValid() || !GetWorld()) return;
    const ADigimonVenomNXTPlayerState* PS = OwningController->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS) return;
    // Owner-only Profile replication is the sole resident source. Public snapshots,
    // AI rosters and other controllers' collections are never consulted.
    TSet<FGuid> Desired;
    for (const FGuid& Id : PS->Profile.DigiFarmResidents)
    {
        FDigimonOwnedPartner Partner;
        if (!Id.IsValid() || Desired.Contains(Id) || !PS->GetPartner(Id, Partner) || !Partner.IsValid()) continue;
        Desired.Add(Id);
        ADigimonVenomNXTFarmResident* Existing = nullptr;
        for (ADigimonVenomNXTFarmResident* Resident : Residents)
            if (IsValid(Resident) && Resident->GetPartnerId() == Id) { Existing = Resident; break; }
        if (Existing) { Existing->RefreshPartner(Partner); continue; }
        FRandomStream Placement(static_cast<int32>(GetTypeHash(Id)));
        DigimonVenomNXTFarmCore::Point Point;
        for (int32 Attempt = 0; Attempt < 64; ++Attempt)
        {
            const double X = Placement.FRandRange(-2400.0f, 2400.0f);
            const double Y = Placement.FRandRange(-1100.0f, 850.0f);
            if (!DigimonVenomNXTFarmCore::IsWalkable(X, Y, DigimonVenomNXTFarmCore::ResidentRadius)) continue;
            bool bSeparated = true;
            for (const ADigimonVenomNXTFarmResident* Other : Residents)
                if (IsValid(Other) && FVector::DistSquared2D(GetActorLocation() + FVector(X, Y, 0.0), Other->GetActorLocation()) < FMath::Square(220.0)) { bSeparated = false; break; }
            if (!bSeparated) continue;
            Point = {X, Y}; break;
        }
        FActorSpawnParameters Params;
        Params.Owner = OwningController.Get();
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        ADigimonVenomNXTFarmResident* NewResident = GetWorld()->SpawnActor<ADigimonVenomNXTFarmResident>(
            ADigimonVenomNXTFarmResident::StaticClass(), GetActorLocation(), FRotator::ZeroRotator, Params);
        if (!NewResident) continue;
        NewResident->InitializeFor(this, OwningController.Get(), Partner, GetActorLocation(), FVector2D(Point.X, Point.Y));
        NewResident->SetFarmVisible(bFarmVisible);
        Residents.Add(NewResident);
    }
    for (int32 Index = Residents.Num() - 1; Index >= 0; --Index)
    {
        ADigimonVenomNXTFarmResident* Resident = Residents[Index];
        if (IsValid(Resident) && Desired.Contains(Resident->GetPartnerId())) continue;
        if (IsValid(Resident)) Resident->Destroy();
        Residents.RemoveAt(Index);
    }
    if (!Desired.Contains(SelectedResident))
        SelectedResident = Residents.IsEmpty() ? FGuid() : Residents[0]->GetPartnerId();
    for (ADigimonVenomNXTFarmResident* Resident : Residents)
        if (IsValid(Resident)) Resident->SetSelected(Resident->GetPartnerId() == SelectedResident);
}

void ADigimonVenomNXTFarmScene::SelectResident(FGuid InstanceId)
{
    for (ADigimonVenomNXTFarmResident* Resident : Residents)
    {
        if (!IsValid(Resident) || Resident->GetPartnerId() != InstanceId) continue;
        SelectedResident = InstanceId;
        for (ADigimonVenomNXTFarmResident* Other : Residents)
            if (IsValid(Other)) Other->SetSelected(Other == Resident);
        return;
    }
}

TArray<ADigimonVenomNXTFarmResident*> ADigimonVenomNXTFarmScene::GetResidentActors() const
{
    TArray<ADigimonVenomNXTFarmResident*> Result;
    for (ADigimonVenomNXTFarmResident* Resident : Residents)
        if (IsValid(Resident)) Result.Add(Resident);
    return Result;
}

void ADigimonVenomNXTFarmScene::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (ADigimonVenomNXTFarmResident* Resident : Residents)
        if (IsValid(Resident)) Resident->Destroy();
    Residents.Reset();
    Super::EndPlay(EndPlayReason);
}
