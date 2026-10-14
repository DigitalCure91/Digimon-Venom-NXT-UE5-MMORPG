#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTChroniclesWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UVerticalBox;
class UTextBlock;
class UProgressBar;
class UDigimonVenomNXTActionButton;

/** Account-owned campaign journal. Battles and quest hand-ins take place beside world NPCs. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTChroniclesWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Chronicles") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> BoundPlayer;
    int32 ActiveTab = 0;
    int32 InspectedMap = 0;
    int32 LastProfileMap = 0;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Content;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> StatusText;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> CrestMeter;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    void BuildLayout();
    void RefreshContent();
    void BuildJournal();
    void BuildAtlas();
    void BuildCrests();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, int32 Payload = 0, bool bHighlight = false);
};
