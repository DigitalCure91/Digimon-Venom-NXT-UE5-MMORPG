#include "DigimonVenomNXTFieldPartyWidget.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ProgressBar.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

namespace DigimonFieldPartyUI
{
    constexpr int32 SlotCount = 6;
    const FLinearColor Ink(0.008f, 0.021f, 0.040f, 0.96f);
    const FLinearColor Panel(0.020f, 0.052f, 0.080f, 0.96f);
    const FLinearColor Cyan(0.12f, 0.86f, 0.96f, 1.0f);
    const FLinearColor Green(0.34f, 0.93f, 0.66f, 1.0f);
    const FLinearColor Gold(1.0f, 0.76f, 0.28f, 1.0f);
    const FLinearColor Red(1.0f, 0.40f, 0.38f, 1.0f);
    const FLinearColor White(0.94f, 0.98f, 1.0f, 1.0f);
    const FLinearColor Muted(0.59f, 0.73f, 0.82f, 1.0f);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 FontSize, FLinearColor Color, bool bBold = false)
    {
        UTextBlock* Out = Tree->ConstructWidget<UTextBlock>();
        Out->SetText(FText::FromString(Value)); Out->SetColorAndOpacity(Color);
        Out->SetAutoWrapText(false); Out->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
        FSlateFontInfo Font = Out->GetFont(); Font.Size = FontSize; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Out->SetFont(Font);
        return Out;
    }
    void Set(UTextBlock* Label, const FString& Value)
    {
        // Avoid invalidating layout when the profile's values have not changed.
        if (Label && Label->GetText().ToString() != Value) Label->SetText(FText::FromString(Value));
    }
    void Add(UVerticalBox* Parent, UWidget* Child, float Padding = 0.0f)
    {
        if (UVerticalBoxSlot* ChildSlot = Parent->AddChildToVerticalBox(Child))
        { ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill); }
    }
    UProgressBar* Meter(UWidgetTree* Tree, UVerticalBox* Parent, FLinearColor Color)
    {
        UProgressBar* Bar = Tree->ConstructWidget<UProgressBar>(); Bar->SetFillColorAndOpacity(Color);
        FProgressBarStyle Style = Bar->GetWidgetStyle();
        Style.SetBackgroundImage(FSlateRoundedBoxBrush(Ink, 2.0f));
        Style.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White, 2.0f)); Bar->SetWidgetStyle(Style);
        USizeBox* Bounds = Tree->ConstructWidget<USizeBox>(); Bounds->SetHeightOverride(4.0f); Bounds->AddChild(Bar); Add(Parent, Bounds, 1.0f);
        return Bar;
    }
}

UDigimonVenomNXTFieldActionButton::UDigimonVenomNXTFieldActionButton(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InitIsFocusable(false);
}

TSharedRef<SWidget> UDigimonVenomNXTFieldPartyWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTFieldPartyWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("FieldPartyWidgetTree"));
    using namespace DigimonFieldPartyUI;
    UBorder* PanelFrame = WidgetTree->ConstructWidget<UBorder>();
    PanelFrame->SetBrush(FSlateRoundedBoxBrush(Ink, 10.0f, Cyan.CopyWithNewOpacity(0.35f), 1.0f));
    PanelFrame->SetPadding(FMargin(10)); PanelFrame->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    WidgetTree->RootWidget = PanelFrame;
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); Root->SetVisibility(ESlateVisibility::SelfHitTestInvisible); PanelFrame->SetContent(Root);
    Add(Root, Text(WidgetTree, TEXT("YOUR FIELD TEAM"), 13, White, true), 1);
    Summary = Text(WidgetTree, TEXT("Synchronizing your partners..."), 10, Muted); Add(Root, Summary, 3);

    for (int32 Index = 0; Index < SlotCount; ++Index)
    {
        FDigimonFieldPartyCard Card;
        USizeBox* CardBounds = WidgetTree->ConstructWidget<USizeBox>(); CardBounds->SetHeightOverride(85.0f); Add(Root, CardBounds, 3);
        Card.Frame = WidgetTree->ConstructWidget<UBorder>(); Card.Frame->SetPadding(FMargin(7, 5)); CardBounds->AddChild(Card.Frame);
        Card.Frame->SetVisibility(ESlateVisibility::Visible);
        UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>(); Card.Frame->SetContent(Row);
        USizeBox* PortraitBounds = WidgetTree->ConstructWidget<USizeBox>(); PortraitBounds->SetWidthOverride(66); PortraitBounds->SetHeightOverride(68);
        UScaleBox* PortraitScale = WidgetTree->ConstructWidget<UScaleBox>(); PortraitScale->SetStretch(EStretch::ScaleToFit); PortraitBounds->AddChild(PortraitScale);
        Card.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitScale->AddChild(Card.Portrait);
        if (UHorizontalBoxSlot* PortraitSlot = Row->AddChildToHorizontalBox(PortraitBounds)) { PortraitSlot->SetPadding(FMargin(0, 0, 8, 0)); PortraitSlot->SetVerticalAlignment(VAlign_Center); }
        UVerticalBox* Details = WidgetTree->ConstructWidget<UVerticalBox>();
        if (UHorizontalBoxSlot* DetailSlot = Row->AddChildToHorizontalBox(Details)) { DetailSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); DetailSlot->SetVerticalAlignment(VAlign_Center); }
        Card.Name = Text(WidgetTree, TEXT("Empty slot"), 12, White, true); Add(Details, Card.Name);
        Card.Status = Text(WidgetTree, FString::Printf(TEXT("SLOT %02d"), Index + 1), 9, Muted, true); Add(Details, Card.Status, 1);
        Card.HP = Text(WidgetTree, TEXT("HP  —"), 9, Green, true); Add(Details, Card.HP); Card.HPBar = Meter(WidgetTree, Details, Green);
        Card.SP = Text(WidgetTree, TEXT("SP  —"), 9, Cyan, true); Add(Details, Card.SP); Card.SPBar = Meter(WidgetTree, Details, Cyan);
        Cards.Add(Card);
    }
    LabShortcut = WidgetTree->ConstructWidget<UDigimonVenomNXTFieldActionButton>();
    DigimonVenomNXTUI::StyleButton(LabShortcut, Green); LabShortcut->InitializeAction(TEXT("digilab:open"));
    LabShortcut->OnAction.AddDynamic(this, &UDigimonVenomNXTFieldPartyWidget::HandleAction);
    UTextBlock* LabText = Text(WidgetTree, TEXT("+  DIGILAB  /  HEAL     [L]"), 12, Green, true); LabText->SetJustification(ETextJustify::Center); LabShortcut->SetContent(LabText);
    LabShortcut->SetToolTipText(FText::FromString(TEXT("Open partner recovery. Return to this exact map and position when you close DigiLab."))); Add(Root, LabShortcut, 4);
    UDigimonVenomNXTActionButton* Manage = WidgetTree->ConstructWidget<UDigimonVenomNXTFieldActionButton>();
    DigimonVenomNXTUI::StyleButton(Manage, Cyan); Manage->InitializeAction(TEXT("field:party"));
    FButtonStyle ManageStyle = Manage->GetStyle(); ManageStyle.SetNormalPadding(FMargin(6, 5)); ManageStyle.SetPressedPadding(FMargin(6, 6, 6, 4)); Manage->SetStyle(ManageStyle);
    Manage->OnAction.AddDynamic(this, &UDigimonVenomNXTFieldPartyWidget::HandleAction);
    UTextBlock* ManageText = Text(WidgetTree, TEXT("MANAGE TEAM"), 10, Muted, true); ManageText->SetJustification(ETextJustify::Center); Manage->SetContent(ManageText); Add(Root, Manage, 1);
}

void UDigimonVenomNXTFieldPartyWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data)
{
    BuildLayout();
    if (!PlayerState || !Data) return;
    using namespace DigimonFieldPartyUI;
    const int32 ActiveCount = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, 1, SlotCount);
    int32 Occupied = 0, NeedsRecovery = 0;
    for (int32 Index = 0; Index < Cards.Num(); ++Index)
    {
        FDigimonFieldPartyCard& Card = Cards[Index];
        FDigimonOwnedPartner Partner;
        const bool bPresent = PlayerState->Profile.Party.IsValidIndex(Index) && PlayerState->GetPartner(PlayerState->Profile.Party[Index], Partner);
        Card.Portrait->SetVisibility(bPresent ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
        if (!bPresent)
        {
            Card.Frame->SetBrush(FSlateRoundedBoxBrush(Panel.CopyWithNewOpacity(0.40f), 7.0f, Muted.CopyWithNewOpacity(0.15f), 1.0f));
            Set(Card.Name, TEXT("Empty slot")); Card.Name->SetColorAndOpacity(Muted);
            Set(Card.Status, FString::Printf(TEXT("SLOT %02d  /  ADD IN PARTY"), Index + 1)); Card.Status->SetColorAndOpacity(Muted);
            Set(Card.HP, TEXT("HP  —")); Card.HP->SetColorAndOpacity(Muted); Set(Card.SP, TEXT("SP  —")); Card.HPBar->SetPercent(0); Card.SPBar->SetPercent(0);
            Card.Frame->SetToolTipText(FText::FromString(TEXT("Add an owned partner using Manage Team.")));
            continue;
        }
        ++Occupied;
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        const bool bDefeated = Unit.HP <= 0;
        const bool bNeedsCare = Unit.HP < Unit.Stats.MaxHP || Unit.SP < Unit.Stats.MaxSP;
        if (bNeedsCare) ++NeedsRecovery;
        const float HPFraction = Unit.Stats.MaxHP > 0 ? FMath::Clamp(static_cast<float>(Unit.HP) / Unit.Stats.MaxHP, 0.0f, 1.0f) : 0.0f;
        const float SPFraction = Unit.Stats.MaxSP > 0 ? FMath::Clamp(static_cast<float>(Unit.SP) / Unit.Stats.MaxSP, 0.0f, 1.0f) : 0.0f;
        const FLinearColor HealthColor = HPFraction <= 0.25f ? Red : Green;
        const FLinearColor Edge = bDefeated ? Red : Index == 0 ? Gold : Cyan;
        Card.Frame->SetBrush(FSlateRoundedBoxBrush(bDefeated ? FLinearColor(0.095f, 0.032f, 0.045f, 0.97f) : Panel, 7.0f, Edge.CopyWithNewOpacity(0.55f), 1.0f));
        if (Card.DisplayedSpecies != Partner.SpeciesId || Card.DisplayedVariant != Partner.Variant)
        {
            Card.Portrait->SetDigimon(Partner.SpeciesId, Partner.Variant);
            Card.DisplayedSpecies = Partner.SpeciesId; Card.DisplayedVariant = Partner.Variant;
        }
        Card.Portrait->SetRenderOpacity(bDefeated ? 0.45f : 1.0f);
        Set(Card.Name, Unit.DisplayName); Card.Name->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
        Set(Card.Status, FString::Printf(TEXT("%02d  /  LV.%d  /  %s"), Index + 1, Partner.Level, bDefeated ? TEXT("DEFEATED") : Index == 0 ? TEXT("LEADER") : Index < ActiveCount ? TEXT("ACTIVE") : TEXT("RESERVE")));
        Card.Status->SetColorAndOpacity(bDefeated ? Red : Index == 0 ? Gold : Muted);
        Set(Card.HP, FString::Printf(TEXT("HP  %d / %d"), Unit.HP, Unit.Stats.MaxHP)); Card.HP->SetColorAndOpacity(HealthColor); Card.HPBar->SetFillColorAndOpacity(HealthColor); Card.HPBar->SetPercent(HPFraction);
        Set(Card.SP, FString::Printf(TEXT("SP  %d / %d"), Unit.SP, Unit.Stats.MaxSP)); Card.SPBar->SetPercent(SPFraction);
        Card.Frame->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s  •  %s\nATK %d  DEF %d  INT %d  SPD %d\n%s"), *Unit.DisplayName, *DigimonVenomNXTUI::VarietyLabel(Partner.Variant), Unit.Stats.Attack, Unit.Stats.Defense, Unit.Stats.Spirit, Unit.Stats.Speed, bDefeated ? TEXT("Defeated — visit DigiLab to restore this partner.") : bNeedsCare ? TEXT("DigiLab restores all HP and SP for free.") : TEXT("Ready to explore."))));
    }
    Set(Summary, FString::Printf(TEXT("%d / 6 PARTNERS  •  %s"), Occupied, NeedsRecovery > 0 ? *FString::Printf(TEXT("%d NEED CARE"), NeedsRecovery) : TEXT("TEAM READY")));
    Summary->SetColorAndOpacity(NeedsRecovery > 0 ? Gold : Green);
    LabShortcut->SetIsEnabled(!PlayerState->HasActiveBattle());
}

void UDigimonVenomNXTFieldPartyWidget::HandleAction(const FString& Action, int32 Payload)
{
    OnAction.Broadcast(Action, Payload);
}
