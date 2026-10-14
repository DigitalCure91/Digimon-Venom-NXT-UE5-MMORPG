#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTGhostLineWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UVerticalBox;
class UTextBlock;
class UProgressBar;
class UDigimonVenomNXTActionButton;

/** Private, spoiler-aware case board. Mutations remain authoritative field interactions. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTGhostLineWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|GhostLine") FDigimonUIButtonAction OnAction;
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
    UPROPERTY(Transient) TObjectPtr<UProgressBar> ProofMeter;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    void BuildLayout();
    void RefreshContent();
    void BuildCaseBoard();
    void BuildNetworkMap();
    void BuildEvidence();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, int32 Payload = 0, bool bHighlight = false);
};
