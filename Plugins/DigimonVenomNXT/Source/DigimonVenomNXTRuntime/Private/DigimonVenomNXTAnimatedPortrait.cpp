#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformTime.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Slate/SlateTextureAtlasInterface.h"

TSharedRef<SWidget> UDigimonVenomNXTAnimatedPortrait::RebuildWidget()
{
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("PortraitWidgetTree"), RF_Transient);
    if (!FrameImage)
    {
        UScaleBox* Scale = WidgetTree->ConstructWidget<UScaleBox>();
        Scale->SetStretch(EStretch::ScaleToFit);
        Scale->SetStretchDirection(EStretchDirection::Both);
        Scale->SetVisibility(ESlateVisibility::HitTestInvisible);
        FrameImage = WidgetTree->ConstructWidget<UImage>();
        FrameImage->SetVisibility(ESlateVisibility::HitTestInvisible);
        Scale->AddChild(FrameImage);
        WidgetTree->RootWidget = Scale;
    }
    UpdateFrame();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTAnimatedPortrait::SetDigimon(FName InSpeciesId, EDigimonVariant InVariant)
{
    if (bConfigured && SpeciesId == InSpeciesId && Variant == InVariant) return;
    bConfigured = true;
    SpeciesId = InSpeciesId; Variant = InVariant;
    AnimationSet = nullptr; IdleFlipbook = nullptr; AttackFlipbook = nullptr; FallbackTexture = nullptr; LastSprite = nullptr;
    AttackStartSeconds = -1.0; bUsingFallback = false;
    if (!SpeciesId.IsNone())
    {
        const FString Family = DigimonVenomNXTPartnerArt::VariantFolder(Variant);
        const FString Species = SpeciesId.ToString();
        const FString Folder = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Digimon/%s/%s/"), *Family, *Species);
        const FString Stem = Species + TEXT("_") + Family;
        const FString FlipbookName = TEXT("FB_") + Stem + TEXT("_Idle");
        const FString AttackName = TEXT("FB_") + Stem + TEXT("_Attack");
        const FString PortraitName = TEXT("T_") + Stem + TEXT("_Portrait");
        const FString SetName = TEXT("DA_") + Stem + TEXT("_Animation");
        AnimationSet = LoadObject<UDigimonVenomNXTPartnerAnimationSet>(nullptr, *(Folder + SetName + TEXT(".") + SetName), nullptr, LOAD_NoWarn | LOAD_Quiet);
        IdleFlipbook = LoadObject<UPaperFlipbook>(nullptr, *(Folder + FlipbookName + TEXT(".") + FlipbookName), nullptr, LOAD_NoWarn | LOAD_Quiet);
        AttackFlipbook = LoadObject<UPaperFlipbook>(nullptr, *(Folder + AttackName + TEXT(".") + AttackName), nullptr, LOAD_NoWarn | LOAD_Quiet);
        FallbackTexture = LoadObject<UTexture2D>(nullptr, *(Folder + PortraitName + TEXT(".") + PortraitName), nullptr, LOAD_NoWarn | LOAD_Quiet);
    }
    SetVisibility(ESlateVisibility::HitTestInvisible);
    UpdateFrame();
}

void UDigimonVenomNXTAnimatedPortrait::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    UpdateFrame();
}

void UDigimonVenomNXTAnimatedPortrait::SetFacingLeft(bool bInFaceLeft)
{
    if (bFaceLeft == bInFaceLeft) return;
    bFaceLeft = bInFaceLeft; LastSprite = nullptr; bUsingFallback = false; UpdateFrame();
}

void UDigimonVenomNXTAnimatedPortrait::PlayAttack()
{
    if (!AttackFlipbook) return;
    AttackStartSeconds = FPlatformTime::Seconds();
    LastSprite = nullptr;
    UpdateFrame();
}

void UDigimonVenomNXTAnimatedPortrait::UpdateFrame()
{
    if (!FrameImage) return;
    // Each source pose is a standalone PNG with its actual width and height.
    // PaperSprite provides correct atlas UVs for small, large and padded varieties.
    const double Clock = FPlatformTime::Seconds();
    const double AttackAge = AttackStartSeconds >= 0.0 ? Clock - AttackStartSeconds : 1.0;
    const bool bAttacking = AttackFlipbook && AttackAge >= 0.0 && AttackAge < 0.65;
    UPaperFlipbook* Book = bAttacking ? AttackFlipbook.Get() : IdleFlipbook.Get();
    UPaperFlipbook* AuthoredLeft = AnimationSet && AnimationSet->bHasAuthoredLeftFrames
        ? (bAttacking ? AnimationSet->AttackLeft.Get() : AnimationSet->IdleLeft.Get()) : nullptr;
    const bool bUseAuthoredLeft = bFaceLeft && AuthoredLeft;
    if (bUseAuthoredLeft) Book = AuthoredLeft;

    if (Book && Book->GetTotalDuration() > 0.0f)
    {
        const double Duration = static_cast<double>(Book->GetTotalDuration());
        const float Time = static_cast<float>(bAttacking ? FMath::Min(AttackAge, FMath::Max(0.0, Duration - 0.001)) : FMath::Fmod(Clock, Duration));
        UPaperSprite* Sprite = Book->GetSpriteAtTime(Time, !bAttacking);
        if (Sprite && Sprite->GetBakedTexture())
        {
            // A source may replace only one pose. Check the selected sprite,
            // so partially supplied opposite-facing sequences remain correct.
            const bool bMirror = bFaceLeft && (!AnimationSet || AnimationSet->ShouldMirrorLeftFrame(Sprite));
            FrameImage->SetRenderScale(FVector2D(bMirror ? -1.0f : 1.0f, 1.0f));
            if (LastSprite != Sprite)
            {
                TScriptInterface<ISlateTextureAtlasInterface> Atlas;
                Atlas.SetObject(Sprite); Atlas.SetInterface(Cast<ISlateTextureAtlasInterface>(Sprite));
                FrameImage->SetBrushFromAtlasInterface(Atlas, true);
                FrameImage->SetOpacity(1.0f); LastSprite = Sprite; bUsingFallback = false;
            }
            return;
        }
    }
    if (!bUsingFallback)
    {
        FrameImage->SetRenderScale(FVector2D(bFaceLeft ? -1.0f : 1.0f, 1.0f));
        FrameImage->SetBrushFromTexture(FallbackTexture, true);
        FrameImage->SetOpacity(FallbackTexture ? 1.0f : 0.0f);
        bUsingFallback = true; LastSprite = nullptr;
    }
}
