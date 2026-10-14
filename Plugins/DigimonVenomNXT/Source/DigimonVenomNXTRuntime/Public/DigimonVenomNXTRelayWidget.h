#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTRelayWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UVerticalBox;
class UTextBlock;
class UProgressBar;
class UDigimonVenomNXTActionButton;

/** Private campaign journal. Route cards navigate unlocked maps; encounters start beside world NPCs. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTRelayWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Relay") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> BoundPlayer;
    int32 ActiveTab = 0;
    int32 InspectedMap = 0;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Content;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> StatusText;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> BadgeMeter;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    void BuildLayout();
    void RefreshContent();
    void BuildJourney();
    void BuildAtlas();
    void BuildBadges();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, int32 Payload = 0, bool bGold = false);
};
