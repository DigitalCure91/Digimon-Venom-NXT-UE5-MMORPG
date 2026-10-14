#include "DigimonVenomNXTTamerStudioWidget.h"
#include "DigimonVenomNXTAnimatedTamerPortrait.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTTamers.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformTime.h"
#include "InputCoreTypes.h"

namespace DigimonTamerStudioUI
{
    static constexpr int32 CardsPerPage = 12;
    static const FLinearColor Cyan(0.08f, 0.86f, 0.91f);
    static const FLinearColor Violet(0.64f, 0.44f, 1.0f);
    static const FLinearColor Gold(1.0f, 0.76f, 0.25f);
    static const FLinearColor White(0.94f, 0.98f, 1.0f);
    static const FLinearColor Muted(0.66f, 0.77f, 0.86f);
    static const TCHAR* FacingNames[] = {TEXT("Front"), TEXT("Front left"), TEXT("Left"), TEXT("Back left"), TEXT("Back"), TEXT("Back right"), TEXT("Right"), TEXT("Front right")};

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 14, FLinearColor Tint = White, bool bBold = false)
    {
        UTextBlock* Out = Tree->ConstructWidget<UTextBlock>();
        Out->SetText(FText::FromString(Value)); Out->SetColorAndOpacity(Tint); Out->SetAutoWrapText(true);
        FSlateFontInfo Font = Out->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Out->SetFont(Font);
        return Out;
    }
    void Add(UVerticalBox* Box, UWidget* Child, float Padding = 3.0f)
    {
        if (UVerticalBoxSlot* ChildLayout = Box->AddChildToVerticalBox(Child)) ChildLayout->SetPadding(FMargin(0, Padding));
    }
    void Row(UHorizontalBox* Box, UWidget* Child, bool bFill = false, float Padding = 4.0f)
    {
        if (UHorizontalBoxSlot* ChildLayout = Box->AddChildToHorizontalBox(Child))
        {
            ChildLayout->SetPadding(FMargin(Padding, 0)); ChildLayout->SetVerticalAlignment(VAlign_Center);
            if (bFill) ChildLayout->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
    void SetLabel(UDigimonVenomNXTActionButton* Button, const FString& Value)
    {
        if (Button) if (UTextBlock* Label = Cast<UTextBlock>(Button->GetChildAt(0))) Label->SetText(FText::FromString(Value));
    }
}

TSharedRef<SWidget> UDigimonVenomNXTTamerStudioWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTTamerStudioWidget::MakeButton(const FString& Label, const FString& Command, int32 Payload)
{
    UDigimonVenomNXTActionButton* Button = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    Button->InitializeAction(Command, Payload);
    DigimonVenomNXTUI::StyleButton(Button, DigimonTamerStudioUI::Cyan);
    Button->OnAction.AddDynamic(this, &UDigimonVenomNXTTamerStudioWidget::HandleAction);
    UTextBlock* Caption = DigimonTamerStudioUI::Text(WidgetTree, Label, 12, DigimonTamerStudioUI::White, true);
    Caption->SetJustification(ETextJustify::Center); Button->AddChild(Caption);
    Button->SetToolTipText(FText::FromString(Label));
    return Button;
}

void UDigimonVenomNXTTamerStudioWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("TamerStudioTree"), RF_Transient);
    using namespace DigimonTamerStudioUI;
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;
    UHorizontalBox* Heading = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Heading, 2);
    Row(Heading, Text(WidgetTree, TEXT("TAMER STUDIO"), 27, Cyan, true), true, 0);
    Row(Heading, MakeButton(TEXT("BACK TO OVERVIEW"), TEXT("back")), false, 0);
    Add(Root, Text(WidgetTree, FString::Printf(TEXT("%d appearances. One adventure that is yours."), DigimonVenomNXTTamers::GetRoster().Num()), 15, White), 2);
    Add(Root, Text(WidgetTree, TEXT("Every look is available from the start. Change your appearance anytime for free; your party, stats and progress stay with you."), 12, Muted), 2);

    UBorder* Hero = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(Hero, FLinearColor(0.025f, 0.06f, 0.105f, 1)); Hero->SetPadding(FMargin(14)); Add(Root, Hero, 10);
    UHorizontalBox* HeroRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Hero->SetContent(HeroRow);
    UVerticalBox* PreviewColumn = WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeroRow, PreviewColumn, false, 8);
    USizeBox* PreviewBounds = WidgetTree->ConstructWidget<USizeBox>(); PreviewBounds->SetWidthOverride(104); PreviewBounds->SetHeightOverride(208);
    Preview = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedTamerPortrait>(); PreviewBounds->AddChild(Preview); Add(PreviewColumn, PreviewBounds, 0);
    PreviewArtHint = Text(WidgetTree, TEXT(""), 10, Gold); PreviewArtHint->SetWrapTextAt(112); Add(PreviewColumn, PreviewArtHint, 2);
    UVerticalBox* Details = WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeroRow, Details, true, 14);
    Add(Details, Text(WidgetTree, TEXT("APPEARANCE PREVIEW"), 11, Violet, true), 2);
    PreviewName = Text(WidgetTree, TEXT("Choose a tamer"), 22, White, true); Add(Details, PreviewName, 2);
    PreviewDescription = Text(WidgetTree, TEXT(""), 13, Muted); Add(Details, PreviewDescription, 5);
    CurrentLabel = Text(WidgetTree, TEXT("Synchronizing your appearance..."), 12, Gold, true); Add(Details, CurrentLabel, 4);
    ApplyButton = MakeButton(TEXT("APPLY APPEARANCE"), TEXT("apply")); Add(Details, ApplyButton, 4);
    StatusLabel = Text(WidgetTree, TEXT("Select a card to preview its outfit."), 12, Muted); Add(Details, StatusLabel, 3);

    USizeBox* DirectionBounds = WidgetTree->ConstructWidget<USizeBox>(); DirectionBounds->SetWidthOverride(232); Row(HeroRow, DirectionBounds, false, 0);
    UVerticalBox* Directions = WidgetTree->ConstructWidget<UVerticalBox>(); DirectionBounds->AddChild(Directions);
    Add(Directions, Text(WidgetTree, TEXT("VIEW EVERY ANGLE"), 11, Cyan, true), 3);
    UUniformGridPanel* DirectionGrid = WidgetTree->ConstructWidget<UUniformGridPanel>(); DirectionGrid->SetSlotPadding(FMargin(2)); Add(Directions, DirectionGrid, 2);
    // Clockwise ring, with an intentionally empty center: arrows describe the actual facing.
    const int32 Cells[] = {7, 6, 3, 0, 1, 2, 5, 8};
    const TCHAR* ArrowLabels[] = {TEXT("S"), TEXT("SW"), TEXT("W"), TEXT("NW"), TEXT("N"), TEXT("NE"), TEXT("E"), TEXT("SE")};
    for (int32 DirectionIndex = 0; DirectionIndex < 8; ++DirectionIndex)
    {
        UDigimonVenomNXTActionButton* DirectionButton = MakeButton(ArrowLabels[DirectionIndex], TEXT("facing"), DirectionIndex);
        DirectionButton->SetToolTipText(FText::FromString(FacingNames[DirectionIndex]));
        DirectionGrid->AddChildToUniformGrid(DirectionButton, Cells[DirectionIndex] / 3, Cells[DirectionIndex] % 3); DirectionButtons.Add(DirectionButton);
    }
    FacingLabel = Text(WidgetTree, TEXT(""), 12, Muted); FacingLabel->SetJustification(ETextJustify::Center); Add(Directions, FacingLabel, 4);
    WalkButton = MakeButton(TEXT("WALKING  /  PAUSE"), TEXT("walking")); Add(Directions, WalkButton, 3);
    Add(Directions, MakeButton(TEXT("SHOW MY CURRENT LOOK"), TEXT("current")), 3);

    UHorizontalBox* SearchRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, SearchRow, 3);
    SearchBox = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(SearchBox);
    SearchBox->SetHintText(FText::FromString(TEXT("Search a name, outfit or style number...")));
    SearchBox->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTTamerStudioWidget::HandleSearchChanged);
    Row(SearchRow, SearchBox, true, 0); Row(SearchRow, MakeButton(TEXT("CLEAR"), TEXT("clear")), false, 4);
    ResultLabel = Text(WidgetTree, TEXT(""), 12, Muted); Add(Root, ResultLabel, 4);
    EmptyLabel = Text(WidgetTree, TEXT("No appearances match this search. Clear your search to see all 64 tamers."), 14, Muted); Add(Root, EmptyLabel, 5);
    Grid = WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Root, Grid, 2);
    for (int32 CardIndex = 0; CardIndex < CardsPerPage; ++CardIndex)
    {
        FDigimonTamerStudioCard Card;
        Card.Bounds = WidgetTree->ConstructWidget<USizeBox>(); Card.Bounds->SetMinDesiredWidth(178); Card.Bounds->SetMinDesiredHeight(198);
        Card.Select = MakeButton(TEXT(""), TEXT("preview")); Card.Select->ClearChildren(); Card.Bounds->AddChild(Card.Select);
        UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); Card.Select->AddChild(Body);
        USizeBox* PortraitBounds = WidgetTree->ConstructWidget<USizeBox>(); PortraitBounds->SetWidthOverride(72); PortraitBounds->SetHeightOverride(144);
        UScaleBox* Fit = WidgetTree->ConstructWidget<UScaleBox>(); Fit->SetStretch(EStretch::ScaleToFit); PortraitBounds->AddChild(Fit);
        Card.Portrait = WidgetTree->ConstructWidget<UImage>(); Fit->AddChild(Card.Portrait);
        if (UVerticalBoxSlot* PortraitLayout = Body->AddChildToVerticalBox(PortraitBounds)) PortraitLayout->SetHorizontalAlignment(HAlign_Center);
        Card.NameText = Text(WidgetTree, TEXT(""), 12, White, true); Card.NameText->SetJustification(ETextJustify::Center); Add(Body, Card.NameText, 2);
        Card.StateText = Text(WidgetTree, TEXT(""), 10, Muted); Card.StateText->SetJustification(ETextJustify::Center); Add(Body, Card.StateText, 1);
        Grid->AddChildToUniformGrid(Card.Bounds, CardIndex / 4, CardIndex % 4); Cards.Add(Card);
    }
    UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Pager, 8);
    PreviousButton = MakeButton(TEXT("PREVIOUS"), TEXT("previous")); Row(Pager, PreviousButton, false, 0);
    PageLabel = Text(WidgetTree, TEXT(""), 13, White, true); PageLabel->SetJustification(ETextJustify::Center); Row(Pager, PageLabel, true, 8);
    NextButton = MakeButton(TEXT("NEXT"), TEXT("next")); Row(Pager, NextButton, false, 0);
    Add(Root, Text(WidgetTree, TEXT("Keyboard: Tab / arrows to focus, Enter to select, Page Up / Page Down to browse. Controller: D-pad to focus, A to select, bumpers to browse, B for Overview."), 10, Muted), 2);
    Refilter();
}

void UDigimonVenomNXTTamerStudioWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState)
{
    CachedPlayerState = PlayerState;
    BuildLayout();
    if (!PlayerState) return;
    CurrentStyle = PlayerState->Profile.TamerStyleId;
    if (bRequestPending && CurrentStyle == PendingStyle)
    {
        bRequestPending = false;
        Feedback = DigimonVenomNXTTamers::DisplayName(CurrentStyle) + TEXT(" is now your saved appearance.");
    }
    if (PreviewIndex == INDEX_NONE) ShowCurrentStyle();
    RefreshCards(); RefreshPreview();
}

void UDigimonVenomNXTTamerStudioWidget::Refilter()
{
    FilteredStyles.Reset();
    const auto& Roster = DigimonVenomNXTTamers::GetRoster();
    for (int32 StyleIndex = 0; StyleIndex < Roster.Num(); ++StyleIndex)
    {
        const auto& Style = Roster[StyleIndex];
        const FString Searchable = Style.Name + TEXT(" ") + Style.Description + TEXT(" ") + Style.Id.ToString();
        if (SearchTerm.IsEmpty() || Searchable.Contains(SearchTerm, ESearchCase::IgnoreCase)) FilteredStyles.Add(StyleIndex);
    }
    PageIndex = FMath::Clamp(PageIndex, 0, FMath::Max(0, (FilteredStyles.Num() - 1) / DigimonTamerStudioUI::CardsPerPage));
    RefreshCards(); RefreshPreview();
}

void UDigimonVenomNXTTamerStudioWidget::RefreshCards()
{
    if (!Root) return;
    using namespace DigimonTamerStudioUI;
    const auto& Roster = DigimonVenomNXTTamers::GetRoster();
    for (int32 CardIndex = 0; CardIndex < Cards.Num(); ++CardIndex)
    {
        auto& Card = Cards[CardIndex];
        const int32 ResultIndex = PageIndex * CardsPerPage + CardIndex;
        const bool bVisible = FilteredStyles.IsValidIndex(ResultIndex);
        Card.Bounds->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        if (!bVisible) continue;
        const int32 StyleIndex = FilteredStyles[ResultIndex]; const auto& Style = Roster[StyleIndex];
        Card.Select->InitializeAction(TEXT("preview"), StyleIndex);
        Card.Select->SetToolTipText(FText::FromString(Style.Name + TEXT(" — ") + Style.Description + TEXT("\nSelect to preview. Apply to save this appearance.")));
        DigimonVenomNXTUI::StyleButton(Card.Select, Style.Id == CurrentStyle ? Gold : Cyan, StyleIndex == PreviewIndex);
        Card.NameText->SetText(FText::FromString(Style.Name));
        if (Card.DisplayedStyle != Style.Id)
        {
            Card.DisplayedStyle = Style.Id;
            UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *DigimonVenomNXTTamers::ThumbnailPath(Style.Id), nullptr, LOAD_NoWarn | LOAD_Quiet);
            Card.Portrait->SetBrushFromTexture(Texture, true); Card.Portrait->SetOpacity(Texture ? 1.0f : 0.0f); Card.bHasPortrait = Texture != nullptr;
        }
        Card.StateText->SetText(FText::FromString(Style.Id == CurrentStyle ? TEXT("CURRENT LOOK") : StyleIndex == PreviewIndex ? TEXT("PREVIEWING") : !Card.bHasPortrait ? TEXT("PREVIEW UNAVAILABLE") : TEXT("AVAILABLE  •  FREE")));
        Card.StateText->SetColorAndOpacity(Style.Id == CurrentStyle ? Gold : StyleIndex == PreviewIndex ? Cyan : Muted);
    }
    const int32 PageCount = FMath::Max(1, FMath::DivideAndRoundUp(FilteredStyles.Num(), CardsPerPage));
    PageLabel->SetText(FText::FromString(FString::Printf(TEXT("PAGE %d / %d"), PageIndex + 1, PageCount)));
    PreviousButton->SetIsEnabled(PageIndex > 0); NextButton->SetIsEnabled(PageIndex + 1 < PageCount);
    EmptyLabel->SetVisibility(FilteredStyles.IsEmpty() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    ResultLabel->SetText(FText::FromString(FilteredStyles.IsEmpty() ? TEXT("0 matches") : FString::Printf(TEXT("Showing %d–%d of %d appearances  •  %d in the full roster"), PageIndex * CardsPerPage + 1, FMath::Min((PageIndex + 1) * CardsPerPage, FilteredStyles.Num()), FilteredStyles.Num(), Roster.Num())));
}

void UDigimonVenomNXTTamerStudioWidget::RefreshPreview()
{
    if (!Root) return;
    using namespace DigimonTamerStudioUI;
    const auto& Roster = DigimonVenomNXTTamers::GetRoster();
    const bool bHasSelection = Roster.IsValidIndex(PreviewIndex);
    if (bHasSelection)
    {
        const auto& Style = Roster[PreviewIndex];
        PreviewName->SetText(FText::FromString(Style.Name)); PreviewDescription->SetText(FText::FromString(Style.Description));
        Preview->SetTamerStyle(Style.Id); Preview->SetFacing(static_cast<EDigimonFacing>(FacingIndex)); Preview->SetWalking(bWalking);
        PreviewArtHint->SetText(FText::FromString(Preview->HasArtwork() ? TEXT("") : TEXT("Appearance preview unavailable.")));
    }
    const bool bCurrent = bHasSelection && Roster[PreviewIndex].Id == CurrentStyle;
    const bool bHasPreviewArt = bHasSelection && Preview->HasArtwork();
    ApplyButton->SetIsEnabled(CachedPlayerState.IsValid() && bHasPreviewArt && !bCurrent && !bRequestPending);
    SetLabel(ApplyButton, bRequestPending ? TEXT("SAVING APPEARANCE...") : bCurrent ? TEXT("CURRENT APPEARANCE") : !bHasPreviewArt ? TEXT("APPEARANCE UNAVAILABLE") : TEXT("APPLY APPEARANCE  •  FREE"));
    DigimonVenomNXTUI::StyleButton(ApplyButton, bCurrent ? Gold : Cyan, bCurrent);
    CurrentLabel->SetText(FText::FromString(CurrentStyle.IsNone() ? TEXT("Synchronizing your appearance...") : TEXT("CURRENT  /  ") + DigimonVenomNXTTamers::DisplayName(CurrentStyle)));
    StatusLabel->SetText(FText::FromString(bRequestPending ? TEXT("Waiting for your saved profile to confirm the change...") : !Feedback.IsEmpty() ? Feedback : bCurrent ? TEXT("This appearance is already equipped.") : !bHasPreviewArt ? TEXT("This appearance cannot be applied while its preview is unavailable.") : TEXT("Preview only. Apply when you are ready to use this appearance.")));
    FacingLabel->SetText(FText::FromString(FString(FacingNames[FacingIndex]) + (bWalking ? TEXT("  •  Walking") : TEXT("  •  Standing"))));
    SetLabel(WalkButton, bWalking ? TEXT("WALKING  /  PAUSE") : TEXT("STANDING  /  PLAY"));
    for (int32 DirectionIndex = 0; DirectionIndex < DirectionButtons.Num(); ++DirectionIndex)
        DigimonVenomNXTUI::StyleButton(DirectionButtons[DirectionIndex], Violet, DirectionIndex == FacingIndex);
}

void UDigimonVenomNXTTamerStudioWidget::ShowCurrentStyle()
{
    const auto& Roster = DigimonVenomNXTTamers::GetRoster();
    PreviewIndex = Roster.IndexOfByPredicate([&](const DigimonVenomNXTTamers::FStyle& Style) { return Style.Id == CurrentStyle; });
    if (PreviewIndex == INDEX_NONE && Roster.Num() > 0) PreviewIndex = 0;
    bResettingSearch = true; SearchTerm.Empty(); SearchBox->SetText(FText::GetEmpty()); bResettingSearch = false;
    PageIndex = FMath::Max(0, PreviewIndex) / DigimonTamerStudioUI::CardsPerPage;
    Refilter();
}

void UDigimonVenomNXTTamerStudioWidget::ChangePage(int32 NewPage)
{
    const int32 LastPage = FMath::Max(0, (FilteredStyles.Num() - 1) / DigimonTamerStudioUI::CardsPerPage);
    PageIndex = FMath::Clamp(NewPage, 0, LastPage);
    RefreshCards();
    // Keep a usable focus target even when the previous page's final card disappears.
    if (Cards.Num() > 0 && !FilteredStyles.IsEmpty()) Cards[0].Select->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTTamerStudioWidget::HandleSearchChanged(const FText& InText)
{
    if (bResettingSearch) return;
    SearchTerm = InText.ToString().TrimStartAndEnd(); PageIndex = 0; Refilter();
}

void UDigimonVenomNXTTamerStudioWidget::HandleAction(const FString& Action, int32 Payload)
{
    const auto& Roster = DigimonVenomNXTTamers::GetRoster();
    if (Action == TEXT("back")) { OnAction.Broadcast(TEXT("page:Overview"), 0); return; }
    if (Action == TEXT("preview") && Roster.IsValidIndex(Payload)) { PreviewIndex = Payload; Feedback.Empty(); RefreshCards(); RefreshPreview(); return; }
    if (Action == TEXT("previous")) { ChangePage(PageIndex - 1); return; }
    if (Action == TEXT("next")) { ChangePage(PageIndex + 1); return; }
    if (Action == TEXT("clear")) { SearchBox->SetText(FText::GetEmpty()); return; }
    if (Action == TEXT("current")) { Feedback.Empty(); ShowCurrentStyle(); return; }
    if (Action == TEXT("facing")) { FacingIndex = FMath::Clamp(Payload, 0, 7); RefreshPreview(); return; }
    if (Action == TEXT("walking")) { bWalking = !bWalking; RefreshPreview(); return; }
    if (Action == TEXT("apply") && CachedPlayerState.IsValid() && Roster.IsValidIndex(PreviewIndex) && Preview && Preview->HasArtwork() && !bRequestPending && Roster[PreviewIndex].Id != CurrentStyle)
    {
        PendingStyle = Roster[PreviewIndex].Id; bRequestPending = true; RequestSentAt = FPlatformTime::Seconds(); Feedback.Empty();
        RefreshPreview();
        OnAction.Broadcast(TEXT("tamer:") + PendingStyle.ToString(), 0);
    }
}

void UDigimonVenomNXTTamerStudioWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (bFocusRosterPending && Cards.Num() > 0 && !FilteredStyles.IsEmpty())
    {
        const int32 SelectedResult = FilteredStyles.Find(PreviewIndex);
        const int32 CardIndex = SelectedResult >= PageIndex * DigimonTamerStudioUI::CardsPerPage && SelectedResult < (PageIndex + 1) * DigimonTamerStudioUI::CardsPerPage
            ? SelectedResult % DigimonTamerStudioUI::CardsPerPage : 0;
        if (Cards[CardIndex].Select->GetCachedWidget().IsValid())
        {
            Cards[CardIndex].Select->SetUserFocus(GetOwningPlayer()); bFocusRosterPending = false;
        }
    }
    if (CachedPlayerState.IsValid() && CurrentStyle != CachedPlayerState->Profile.TamerStyleId) RefreshFromProfile(CachedPlayerState.Get());
    if (bRequestPending && FPlatformTime::Seconds() - RequestSentAt >= 10.0)
    {
        bRequestPending = false;
        Feedback = TEXT("The change has not been confirmed. Check the server message, then try Apply again.");
        RefreshPreview();
    }
}

FReply UDigimonVenomNXTTamerStudioWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    const FKey Key = InKeyEvent.GetKey();
    if (Key == EKeys::Gamepad_FaceButton_Right) { OnAction.Broadcast(TEXT("page:Overview"), 0); return FReply::Handled(); }
    if (Key == EKeys::PageUp || Key == EKeys::Gamepad_LeftShoulder) { ChangePage(PageIndex - 1); return FReply::Handled(); }
    if (Key == EKeys::PageDown || Key == EKeys::Gamepad_RightShoulder) { ChangePage(PageIndex + 1); return FReply::Handled(); }
    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
