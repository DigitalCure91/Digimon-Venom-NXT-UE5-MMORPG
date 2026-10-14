#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTUIComponents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDigimonUIButtonAction, const FString&, Action, int32, Payload);

/** Native button carrying an action string and integer payload, useful for data-driven C++ widget trees. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTActionButton : public UButton
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|UI") FString Action;
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|UI") int32 Payload = 0;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|UI")
    void InitializeAction(const FString& InAction, int32 InPayload = 0);

private:
    UFUNCTION() void HandleClicked();
    UFUNCTION() void HandleHovered();
    bool bBound = false;
};

class UBorder;
class UEditableTextBox;
class UOverlay;
class USizeBox;
class UTexture2D;
class UWidgetTree;

/** Shared native presentation rules. All art is decorative; absence never blocks a screen. */
namespace DigimonVenomNXTUI
{
    DIGIMONVENOMNXTRUNTIME_API FString VarietyLabel(EDigimonVariant Variety);
    DIGIMONVENOMNXTRUNTIME_API FLinearColor VarietyAccent(EDigimonVariant Variety);
    DIGIMONVENOMNXTRUNTIME_API void StyleButton(UButton* Button, FLinearColor Accent, bool bSelected = false);
    DIGIMONVENOMNXTRUNTIME_API void StylePanel(UBorder* Border, FLinearColor Fill);
    DIGIMONVENOMNXTRUNTIME_API void StyleInput(UEditableTextBox* Input);
    DIGIMONVENOMNXTRUNTIME_API USizeBox* Texture(UWidgetTree* Tree, UTexture2D* Image, float Width, float Height);
    DIGIMONVENOMNXTRUNTIME_API USizeBox* CurrencyIcon(UWidgetTree* Tree, bool bDigiRubies, float Width, float Height);
    DIGIMONVENOMNXTRUNTIME_API USizeBox* AnimatedPortrait(UWidgetTree* Tree, FName SpeciesId, EDigimonVariant Variant, float Width, float Height);
    DIGIMONVENOMNXTRUNTIME_API void AddBackdrop(UWidgetTree* Tree, UOverlay* Overlay, const TCHAR* AssetPath, FLinearColor Shade);
    /** Whole scan values stay compact; custom rates retain exact hundredths. */
    DIGIMONVENOMNXTRUNTIME_API FString ScanValue(int32 Whole, int32 Hundredths = 0);
    DIGIMONVENOMNXTRUNTIME_API FString Countdown(int64 Seconds);
}
