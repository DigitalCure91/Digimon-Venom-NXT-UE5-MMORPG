#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTSettings.h"
#include "PaperFlipbookComponent.h"
#include "Materials/MaterialInterface.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Crc.h"

void DigimonVenomNXTFieldSprite::ConfigureDefaults(UPaperFlipbookComponent* Sprite)
{
    if (!Sprite) return;
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sprite->SetCastShadow(false);
    Sprite->SetReceivesDecals(false);
    // The masked material clips transparent texels in the depth pass as well, so
    // cel shading follows the illustration instead of its rectangular sprite quad.
    // Preserve authored stencil IDs for project-specific post-process categories.
    Sprite->SetRenderCustomDepth(true);
    Sprite->SetTranslucentSortPriority(0);
}

void DigimonVenomNXTFieldSprite::Configure(UPaperFlipbookComponent* Sprite)
{
    // Native actor constructors also execute while class defaults and serialized
    // actors are being created. Loading a material package from that path can
    // re-enter the cooked async loader before the class is ready. Constructors
    // use ConfigureDefaults; BeginPlay/identity refresh resolve instance assets.
    if (!Sprite || !IsInGameThread() || Sprite->IsTemplate() || !Sprite->IsRegistered()) return;
    const AActor* Owner = Sprite->GetOwner();
    if (Owner && Owner->IsTemplate()) return;

    ConfigureDefaults(Sprite);
    UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr,
        TEXT("/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite.MI_DVNXT_FieldSprite"), nullptr, LOAD_NoWarn | LOAD_Quiet);
    if (!Material || Material->GetBlendMode() != BLEND_Masked)
        Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Paper2D/MaskedUnlitSpriteMaterial.MaskedUnlitSpriteMaterial"));
    if (!Material)
    {
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT: Paper2D masked sprite material is unavailable; refusing an opaque sprite fallback."));
        Sprite->SetVisibility(false);
        return;
    }
    {
        // Override both slots: old sprites can retain an opaque alternate geometry section.
        Sprite->SetMaterial(0, Material);
        Sprite->SetMaterial(1, Material);
    }
}

void DigimonVenomNXTFieldSprite::UpdateDepth(UPaperFlipbookComponent* Sprite)
{
    if (!Sprite || !Sprite->GetOwner()) return;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    if (!Settings->bUseTrueTopDownFieldCamera) return;
    APlayerController* Viewer = UGameplayStatics::GetPlayerController(Sprite, 0);
    if (!Viewer || !Viewer->IsLocalController() || !Viewer->PlayerCameraManager) return;

    const APlayerCameraManager* Camera = Viewer->PlayerCameraManager;
    FVector ScreenUp = Camera->GetCameraRotation().RotateVector(FVector::UpVector);
    ScreenUp.Z = 0.0f;
    ScreenUp = ScreenUp.GetSafeNormal();
    if (ScreenUp.IsNearlyZero()) return;
    const FVector ActorLocation = Sprite->GetOwner()->GetActorLocation();
    const double ScreenHeight = FVector::DotProduct(ActorLocation - Camera->GetCameraLocation(), ScreenUp);
    // Masked sprites write depth, so translucent sort priority cannot fix coplanar overlap.
    // Move only the visual plane; server movement, follower trails and collision stay unchanged.
    // Lower-on-screen actors sit closer to the overhead camera, with all planes above the ground.
    // Deterministic sub-row bias prevents coplanar depth fighting when feet share a row.
    // At most 0.051 world units: ordinary vertical ordering remains authoritative.
    const float TieBreak = static_cast<float>(FCrc::StrCrc32(*Sprite->GetOwner()->GetName()) & 255u) * 0.0002f;
    const float PlaneZ = 70.0f - FMath::Clamp(static_cast<float>(ScreenHeight), -12500.0f, 12500.0f) * 0.004f + TieBreak;
    FVector Relative = Sprite->GetRelativeLocation();
    Relative.Z += PlaneZ - Sprite->GetComponentLocation().Z;
    if (!FMath::IsNearlyEqual(Sprite->GetRelativeLocation().Z, Relative.Z, 0.001f))
        Sprite->SetRelativeLocation(Relative);
}
