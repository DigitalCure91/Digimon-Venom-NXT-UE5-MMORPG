#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTNameplateWidget.generated.h"

class UBorder;
class UTextBlock;
class UMenuAnchor;
class UDigimonVenomNXTActionButton;
class UDigimonVenomNXTNameplateWidget;

/** Concrete popup class for a viewport-safe native menu anchor. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTNameplateMenuWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void InitializeFor(UDigimonVenomNXTNameplateWidget* Plate);
};

/** Screen-space label with an anchored context menu for other tamers. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTNameplateWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetIdentity(const FString& Name, bool bOwnTamer, bool bAIRival, const FString& Title = FString(), const FString& AccountId = FString());
    void CloseContextMenu();

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

private:
    friend class UDigimonVenomNXTNameplateMenuWidget;
    UFUNCTION() void HandlePlateClicked(const FString& Action, int32 Payload);
    UFUNCTION() UUserWidget* BuildContextMenu();
    UFUNCTION() void HandleContextAction(const FString& Action, int32 Payload);
    UPROPERTY(Transient) TObjectPtr<UMenuAnchor> ContextAnchor;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PlateButton;
    FString TargetAccountId;
    UPROPERTY(Transient) TObjectPtr<UBorder> Plate;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> NameText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> KindText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TitleText;
    FString DisplayName;
    FString DisplayTitle;
    bool bIsOwnTamer = false;
    bool bIsAIRival = false;
    void ApplyIdentity();
};
