#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAnimatedTamerPortrait.generated.h"

class UImage;
class UPaperFlipbook;
class UPaperSprite;
class UTexture2D;
class UDigimonVenomNXTTamerAnimationSet;

/** One retained, aspect-correct preview of the actual directional field sprites. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAnimatedTamerPortrait : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetTamerStyle(FName InStyle);
    void SetFacing(EDigimonFacing InFacing);
    void SetWalking(bool bInWalking);
    bool HasArtwork() const;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    void LoadDirection();
    void UpdateFrame();
    FName Style;
    EDigimonFacing Facing = EDigimonFacing::Down;
    bool bWalking = true;
    int32 LastTextureFrame = INDEX_NONE;
    UPROPERTY(Transient) TObjectPtr<UImage> FrameImage;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTTamerAnimationSet> AnimationSet;
    UPROPERTY(Transient) TObjectPtr<UPaperFlipbook> DirectionFlipbook;
    UPROPERTY(Transient) TObjectPtr<UPaperSprite> LastSprite;
    UPROPERTY(Transient) TArray<TObjectPtr<UTexture2D>> DirectionFrames;
};
