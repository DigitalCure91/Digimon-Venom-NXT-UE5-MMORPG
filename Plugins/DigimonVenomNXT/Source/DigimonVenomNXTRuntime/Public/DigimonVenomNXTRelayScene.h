#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTRelayScene.generated.h"
class ADigimonVenomNXTPlayerController;
class ADigimonVenomNXTLocalMapRenderer;
class UTextBlock;
class UPaperFlipbookComponent;
class UWidgetComponent;
class UDigimonVenomNXTPartnerAnimationSet;

/** Readable camera-independent in-world labels, owned only by the local campaign. */
UCLASS(NotBlueprintable, Transient)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTRelayWorldLabel : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetLabel(const FString& Label, const FLinearColor& Color);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
private:
    UPROPERTY(Transient) TObjectPtr<UTextBlock> LabelText;
    FString PendingLabel;
    FLinearColor PendingColor = FLinearColor::White;
};

/** Local presentation only. Gameplay positions are recomputed by the authoritative controller. */
UCLASS(NotBlueprintable, Transient)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTRelayScene : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTRelayScene();
    bool InitializeFor(ADigimonVenomNXTPlayerController* Controller, FString* OutError = nullptr);
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaSeconds) override;
private:
    struct FGuardianVisual
    {
        TWeakObjectPtr<UPaperFlipbookComponent> Sprite;
        TWeakObjectPtr<UDigimonVenomNXTPartnerAnimationSet> Animation;
        double WorldPerPixel = 1.;
        FName Species;
        FVector GroundContact = FVector::ZeroVector;
        float PlaybackTime = 0.0f;
    };
    TArray<FGuardianVisual> GuardianVisuals;
    UPROPERTY(Transient) TObjectPtr<ADigimonVenomNXTPlayerController> CampaignOwner;
    UPROPERTY(Transient) TObjectPtr<ADigimonVenomNXTLocalMapRenderer> Ground;
    UPROPERTY(Transient) TArray<TObjectPtr<UPaperFlipbookComponent>> Tamers;
    UPROPERTY(Transient) TArray<TObjectPtr<UWidgetComponent>> Labels;
    void AddLabel(const FVector& WorldLocation, const FString& Text, const FLinearColor& Color);
    bool RebuildCast(FString* OutError = nullptr);
    FString CastSignature() const;
    FString PresentedCastSignature;
    float CastRefreshAccumulator = 0.0f;
};
