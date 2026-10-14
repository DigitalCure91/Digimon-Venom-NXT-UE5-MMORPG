#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAnimatedPortrait.generated.h"

class UImage;
class UPaperFlipbook;
class UPaperSprite;
class UTexture2D;
class UDigimonVenomNXTPartnerAnimationSet;

/** Real idle flipbook frames inside UMG; drawing never changes gameplay state. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAnimatedPortrait : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void SetDigimon(FName InSpeciesId, EDigimonVariant InVariant);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void SetFacingLeft(bool bInFaceLeft);

    /** Play the source attack poses once; snapshots never alter the shared idle clock. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void PlayAttack();

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

private:
    UPROPERTY(Transient) TObjectPtr<UImage> FrameImage;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTPartnerAnimationSet> AnimationSet;
    UPROPERTY(Transient) TObjectPtr<UPaperFlipbook> IdleFlipbook;
    UPROPERTY(Transient) TObjectPtr<UPaperSprite> LastSprite;
    UPROPERTY(Transient) TObjectPtr<UPaperFlipbook> AttackFlipbook;
    UPROPERTY(Transient) TObjectPtr<UTexture2D> FallbackTexture;
    FName SpeciesId;
    EDigimonVariant Variant = EDigimonVariant::Normal;
    double AttackStartSeconds = -1.0;
    bool bConfigured = false;
    bool bFaceLeft = false;
    bool bUsingFallback = false;
    void UpdateFrame();
};
