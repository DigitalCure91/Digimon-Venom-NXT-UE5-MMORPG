#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAnimationAssets.generated.h"

class UPaperFlipbook;
class UPaperSprite;

namespace DigimonVenomNXTPartnerArt
{
    /** Canonical cooked artwork folder. Variants never borrow Normal artwork. */
    DIGIMONVENOMNXTRUNTIME_API const TCHAR* VariantFolder(EDigimonVariant Variant);
}

UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTPartnerAnimationSet : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Idle;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> WalkLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> WalkRight;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Attack;

    /** Opposite-facing poses supplied by the Digimon source catalog. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> IdleLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> AttackLeft;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    bool bHasAuthoredLeftFrames = false;

    /** Only these individual source frames already face left. Partial mappings
     * retain standard mirroring for the remaining frames in the same sequence. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    TArray<TObjectPtr<UPaperSprite>> AuthoredLeftSprites;

    /** Unpadded source body dimensions for each frame, used for native sizing. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    TMap<TObjectPtr<UPaperSprite>, FVector2D> NativeFrameBodies;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Animation")
    bool ShouldMirrorLeftFrame(UPaperSprite* Frame) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Animation")
    FVector2D GetBodySizeForFrame(UPaperSprite* Frame) const;

    /** Native idle body dimensions before aura padding or runtime presentation scale. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    FVector2D NativeBodySize = FVector2D::ZeroVector;

    /** Authored contact point in normalized frame coordinates, in this order:
     * IdleA, IdleB, WalkRight, WalkLeft, AttackA, AttackB. Supplied by the native content manifest.
     * Cooked presentation metadata; does not alter shared Paper2D sprite pivots.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    TArray<FVector2D> FootOrigins;
};

UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTTamerAnimationSet : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Down;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> DownLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Left;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> UpLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Up;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> UpRight;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> Right;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UPaperFlipbook> DownRight;

    /** Browser-source display multiplier; applied by tamer presentation. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    float DisplayScale = 2.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Animation")
    FVector2D NativeBodySize = FVector2D(16.0, 32.0);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Animation")
    UPaperFlipbook* GetForFacing(EDigimonFacing Facing) const;
};
