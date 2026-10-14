#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTTamerStudioWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTAnimatedTamerPortrait;
class UEditableTextBox;
class UImage;
class USizeBox;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;

USTRUCT()
struct FDigimonTamerStudioCard
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Select;
    UPROPERTY(Transient) TObjectPtr<USizeBox> Bounds;
    UPROPERTY(Transient) TObjectPtr<UImage> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> NameText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> StateText;
    FName DisplayedStyle;
    bool bHasPortrait = false;
};

/** Account cosmetics: twelve retained roster cards and one real directional preview. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTTamerStudioWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState);
    void FocusRoster() { bFocusRosterPending = true; }

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleSearchChanged(const FText& InText);

private:
    void BuildLayout();
    void Refilter();
    void RefreshCards();
    void RefreshPreview();
    void ChangePage(int32 NewPage);
    void ShowCurrentStyle();
    UDigimonVenomNXTActionButton* MakeButton(const FString& Label, const FString& Command, int32 Payload = 0);

    TWeakObjectPtr<ADigimonVenomNXTPlayerState> CachedPlayerState;
    TArray<int32> FilteredStyles;
    int32 PageIndex = 0;
    int32 PreviewIndex = INDEX_NONE;
    int32 FacingIndex = 0;
    bool bWalking = true;
    bool bRequestPending = false;
    bool bResettingSearch = false;
    bool bFocusRosterPending = false;
    double RequestSentAt = 0.0;
    FName PendingStyle;
    FName CurrentStyle;
    FString SearchTerm;
    FString Feedback;

    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> SearchBox;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedTamerPortrait> Preview;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PreviewName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PreviewDescription;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CurrentLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> FacingLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PreviewArtHint;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> StatusLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResultLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ApplyButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> WalkButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PreviousButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> NextButton;
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> Grid;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> DirectionButtons;
    UPROPERTY(Transient) TArray<FDigimonTamerStudioCard> Cards;
};
