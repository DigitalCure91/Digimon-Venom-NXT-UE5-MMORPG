#include "DigimonVenomNXTAnimatedTamerPortrait.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTTamers.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformTime.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Slate/SlateTextureAtlasInterface.h"

TSharedRef<SWidget> UDigimonVenomNXTAnimatedTamerPortrait::RebuildWidget()
{
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("TamerPortraitTree"), RF_Transient);
    if (!FrameImage)
    {
        UScaleBox* Fit = WidgetTree->ConstructWidget<UScaleBox>();
        Fit->SetStretch(EStretch::ScaleToFit);
        Fit->SetStretchDirection(EStretchDirection::Both);
        FrameImage = WidgetTree->ConstructWidget<UImage>();
        Fit->AddChild(FrameImage);
        WidgetTree->RootWidget = Fit;
    }
    SetVisibility(ESlateVisibility::HitTestInvisible);
    UpdateFrame();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTAnimatedTamerPortrait::SetTamerStyle(FName InStyle)
{
    if (Style == InStyle) return;
    Style = InStyle;
    AnimationSet = DigimonVenomNXTTamers::IsValidStyle(Style)
        ? LoadObject<UDigimonVenomNXTTamerAnimationSet>(nullptr, *DigimonVenomNXTTamers::AnimationPath(Style), nullptr, LOAD_NoWarn | LOAD_Quiet) : nullptr;
    LoadDirection();
}

void UDigimonVenomNXTAnimatedTamerPortrait::SetFacing(EDigimonFacing InFacing)
{
    if (Facing == InFacing) return;
    Facing = InFacing;
    LoadDirection();
}

void UDigimonVenomNXTAnimatedTamerPortrait::SetWalking(bool bInWalking)
{
    bWalking = bInWalking;
    UpdateFrame();
}

bool UDigimonVenomNXTAnimatedTamerPortrait::HasArtwork() const
{
    if (DirectionFlipbook && DirectionFlipbook->GetTotalDuration() > 0.0f) return true;
    return DirectionFrames.Num() > 0 && DirectionFrames[0] != nullptr;
}

void UDigimonVenomNXTAnimatedTamerPortrait::LoadDirection()
{
    DirectionFlipbook = AnimationSet ? AnimationSet->GetForFacing(Facing) : nullptr;
    DirectionFrames.Reset();
    LastSprite = nullptr;
    LastTextureFrame = INDEX_NONE;
    if (DigimonVenomNXTTamers::IsValidStyle(Style))
    {
        const TCHAR* Folder = TEXT("down");
        switch (Facing)
        {
            case EDigimonFacing::DownLeft: Folder = TEXT("down_left"); break;
            case EDigimonFacing::Left: Folder = TEXT("left"); break;
            case EDigimonFacing::UpLeft: Folder = TEXT("up_left"); break;
            case EDigimonFacing::Up: Folder = TEXT("up"); break;
            case EDigimonFacing::UpRight: Folder = TEXT("up_right"); break;
            case EDigimonFacing::Right: Folder = TEXT("right"); break;
            case EDigimonFacing::DownRight: Folder = TEXT("down_right"); break;
            default: break;
        }
        for (int32 FrameIndex = 0; FrameIndex < 4; ++FrameIndex)
        {
            const FString Asset = FString::Printf(TEXT("T_%s_%s_%02d"), *Style.ToString(), Folder, FrameIndex);
            const FString Path = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Tamers/%s/%s/%s.%s"), *Style.ToString(), Folder, *Asset, *Asset);
            DirectionFrames.Add(LoadObject<UTexture2D>(nullptr, *Path, nullptr, LOAD_NoWarn | LOAD_Quiet));
        }
    }
    UpdateFrame();
}

void UDigimonVenomNXTAnimatedTamerPortrait::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (bWalking) UpdateFrame();
}

void UDigimonVenomNXTAnimatedTamerPortrait::UpdateFrame()
{
    if (!FrameImage) return;
    const double Clock = bWalking ? FPlatformTime::Seconds() : 0.0;
    if (DirectionFlipbook && DirectionFlipbook->GetTotalDuration() > 0.0f)
    {
        const float Time = static_cast<float>(FMath::Fmod(Clock, static_cast<double>(DirectionFlipbook->GetTotalDuration())));
        UPaperSprite* Sprite = DirectionFlipbook->GetSpriteAtTime(Time, true);
        if (Sprite && Sprite->GetBakedTexture())
        {
            if (LastSprite != Sprite)
            {
                TScriptInterface<ISlateTextureAtlasInterface> Atlas;
                Atlas.SetObject(Sprite);
                Atlas.SetInterface(Cast<ISlateTextureAtlasInterface>(Sprite));
                FrameImage->SetBrushFromAtlasInterface(Atlas, true);
                FrameImage->SetOpacity(1.0f);
                LastSprite = Sprite;
                LastTextureFrame = INDEX_NONE;
            }
            return;
        }
    }
    // Each supplied direction contains four 150 ms frames. Preserve that timing
    // if an older cooked Paper2D sprite lacks its baked atlas data.
    const int32 FrameIndex = bWalking ? static_cast<int32>(FMath::Fmod(Clock, 0.6) / 0.15) : 0;
    if (LastTextureFrame != FrameIndex)
    {
        UTexture2D* Texture = DirectionFrames.IsValidIndex(FrameIndex) ? DirectionFrames[FrameIndex].Get() : nullptr;
        FrameImage->SetBrushFromTexture(Texture, true);
        FrameImage->SetOpacity(Texture ? 1.0f : 0.0f);
        LastTextureFrame = FrameIndex;
        LastSprite = nullptr;
    }
}
