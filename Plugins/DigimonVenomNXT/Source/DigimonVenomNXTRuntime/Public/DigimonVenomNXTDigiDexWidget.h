#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTDigiDexWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UEditableTextBox;
class UHorizontalBox;
class UProgressBar;
class USizeBox;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;

/** Only these twelve retained cards load portrait assets, regardless of catalogue size. */
USTRUCT()
struct FDigimonDigiDexCardView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<USizeBox> Bounds;
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UBorder> AccentLine;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Stage;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Variant;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Affinity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Element;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Scan;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> History;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Bonus;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> Meter;
    UPROPERTY(Transient) TObjectPtr<UHorizontalBox> ThresholdRow;
    UPROPERTY(Transient) TObjectPtr<USizeBox> ThresholdBefore;
    UPROPERTY(Transient) TObjectPtr<USizeBox> ThresholdAfter;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Inspect;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Materialize;
};

/** Read-only view of the owning account. Server RPCs remain the only mutation path. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTDigiDexWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data);
    void ShowReadyForms();

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleSearchChanged(const FText& Text);

private:
    struct FEntry
    {
        FDigimonSpeciesDefinition Species;
        EDigimonVariant Variant = EDigimonVariant::Normal;
        FString Key;
        FString Search;
        int32 Scan = 0;
        int32 FractionalHundredths = 0;
        int32 Peak = 0;
        int32 Owned = 0;
        int32 Materializations = 0;
        bool bEverOwned = false;
        bool bDiscovered = false;
    };
    void BuildLayout();
    void BuildCatalogue();
    void UpdateAccountProgress();
    void RefreshResults();
    void RefreshCards();
    void RefreshRecord();
    void UpdateGridLayout(float Width);
    void RevealInScroll(UWidget* Widget);
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload = 0);

    TWeakObjectPtr<ADigimonVenomNXTPlayerState> CachedPlayerState;
    TWeakObjectPtr<UDigimonVenomNXTDataSubsystem> CachedData;
    TArray<FEntry> Entries;
    TArray<int32> FilteredEntries;
    TArray<int32> AvailableStages;
    FString SearchTerm;
    int32 SpeciesCount = 0;
    int32 Page = 0;
    int32 ViewFilter = 0; // All / discovered / currently owned / ready
    int32 StageFilter = INDEX_NONE;
    int32 VariantFilter = INDEX_NONE;
    int32 SortMode = 0; // Scan descending / name / stage
    int32 SelectedEntry = INDEX_NONE;
    int32 Columns = 4;
    float LastGridWidth = 0.0f;
    bool bSearchReset = false;
    bool bConfirming = false;
    bool bRequestPending = false;
    bool bWasBattleLocked = false;
    double RequestSentAt = 0.0;
    int32 PendingCollectionCount = 0;
    int32 PendingScan = 0;
    int32 PendingEntry = INDEX_NONE;

    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Subtitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Rules;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> Totals;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> ViewTabs;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> SearchBox;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> StageButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> VariantButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> SortButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResultLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UBorder> RecordPanel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordStats;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordAffinity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordElement;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordRoutes;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordProgress;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecordPreview;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ConfirmButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyLabel;
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> Grid;
    UPROPERTY(Transient) TArray<FDigimonDigiDexCardView> Cards;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Previous;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Next;
};
