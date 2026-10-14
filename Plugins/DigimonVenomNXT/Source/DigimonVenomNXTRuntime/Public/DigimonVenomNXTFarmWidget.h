#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTFarmWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UProgressBar;
class UTextBlock;
class UVerticalBox;

/** Farm controls preserve the field's WASD input after mouse clicks. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFarmActionButton : public UDigimonVenomNXTActionButton
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTFarmActionButton(const FObjectInitializer& ObjectInitializer);
};

USTRUCT()
struct FDigimonFarmCardView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Growth;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Experience;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> XPBar;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Residence;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Inspect;
};

/** Retained resident manager and nonmodal farm care controls. Never takes keyboard focus. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFarmWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    /** Set before adding the widget to its parent. */
    void SetWorldOverlay(bool bEnabled) { bWorldOverlay = bEnabled; }
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    void BuildLayout();
    void BuildManagement();
    void BuildWorldOverlay();
    void AddResidentCard();
    void RefreshSelection();
    void RefreshCurrent();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Color, int32 Payload = 0);
    bool bWorldOverlay = false;
    bool bBuilt = false;
    int32 PageIndex = 0;
    int32 Filter = 0; // 0 residents; 1 collection available to place
    int32 PageCount = 1;
    float SelectionAccumulator = 0.0f;
    FGuid SelectedResident;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> CachedPlayerState;
    TWeakObjectPtr<UDigimonVenomNXTDataSubsystem> CachedData;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Cards;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Summary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Supplies;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyMessage;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Previous;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Next;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Enter;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Leave;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ResidentsTab;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> CollectionTab;
    UPROPERTY(Transient) TArray<FDigimonFarmCardView> ResidentCards;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> CareBody;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> SelectedPortrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedStats;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedGrowth;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedXP;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> SelectedXPBar;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> TrainingBar;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TrainingText;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> FeedCAM;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> FeedABI;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> TrainingButtons;
};
