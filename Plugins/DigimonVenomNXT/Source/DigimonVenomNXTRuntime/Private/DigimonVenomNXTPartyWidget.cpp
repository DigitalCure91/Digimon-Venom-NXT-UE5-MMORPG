#include "DigimonVenomNXTPartyWidget.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTSettings.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

namespace DigimonPartyUI
{
    const FLinearColor Ink(0.009f, 0.022f, 0.045f, 1.0f);
    const FLinearColor Panel(0.018f, 0.052f, 0.090f, 1.0f);
    const FLinearColor Cyan(0.08f, 0.88f, 0.94f, 1.0f);
    const FLinearColor Gold(1.0f, 0.74f, 0.21f, 1.0f);
    const FLinearColor Violet(0.71f, 0.48f, 1.0f, 1.0f);
    const FLinearColor White(0.94f, 0.98f, 1.0f, 1.0f);
    const FLinearColor Muted(0.59f, 0.73f, 0.84f, 1.0f);
    const FLinearColor Green(0.34f, 0.93f, 0.66f, 1.0f);
    const FLinearColor Red(1.0f, 0.40f, 0.40f, 1.0f);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 13, FLinearColor Color = White, bool bBold = false)
    {
        UTextBlock* W = Tree->ConstructWidget<UTextBlock>();
        W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font = W->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); W->SetFont(Font);
        return W;
    }
    void Set(UTextBlock* W, const FString& Value) { if (W) W->SetText(FText::FromString(Value)); }
    void Add(UVerticalBox* Box, UWidget* Child, float Padding = 3.0f)
    {
        if (UVerticalBoxSlot* ChildSlot = Box->AddChildToVerticalBox(Child)) { ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill); }
    }
    void AddRow(UHorizontalBox* Box, UWidget* Child, bool bFill = true, float Padding = 5.0f)
    {
        if (UHorizontalBoxSlot* ChildSlot = Box->AddChildToHorizontalBox(Child))
        {
            ChildSlot->SetPadding(FMargin(Padding, 0)); ChildSlot->SetVerticalAlignment(VAlign_Center);
            if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
    UBorder* PanelBox(UWidgetTree* Tree, FLinearColor Accent)
    {
        UBorder* W = Tree->ConstructWidget<UBorder>();
        W->SetBrush(FSlateRoundedBoxBrush(Panel, 10.0f, Accent.CopyWithNewOpacity(0.45f), 1.0f));
        W->SetPadding(FMargin(16)); return W;
    }
    UProgressBar* Meter(UWidgetTree* Tree, UVerticalBox* Box, FLinearColor Color, float Height = 6.0f)
    {
        UProgressBar* Bar = Tree->ConstructWidget<UProgressBar>(); Bar->SetFillColorAndOpacity(Color);
        FProgressBarStyle Style = Bar->GetWidgetStyle();
        Style.SetBackgroundImage(FSlateRoundedBoxBrush(Ink, 3.0f));
        Style.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White, 3.0f)); Bar->SetWidgetStyle(Style);
        USizeBox* Bounds = Tree->ConstructWidget<USizeBox>(); Bounds->SetHeightOverride(Height); Bounds->AddChild(Bar); Add(Box, Bounds, 2);
        return Bar;
    }
    FString Stage(EDigimonStage Value)
    {
        switch (Value)
        {
        case EDigimonStage::Fresh: return TEXT("FRESH");
        case EDigimonStage::InTraining: return TEXT("IN-TRAINING");
        case EDigimonStage::Rookie: return TEXT("ROOKIE");
        case EDigimonStage::Champion: return TEXT("CHAMPION");
        case EDigimonStage::Ultimate: return TEXT("ULTIMATE");
        case EDigimonStage::Mega: return TEXT("MEGA");
        case EDigimonStage::Ultra: return TEXT("ULTRA");
        case EDigimonStage::Armor: return TEXT("ARMOR");
        case EDigimonStage::Hybrid: return TEXT("HYBRID");
        default: return TEXT("UNKNOWN");
        }
    }
    FString Number(int64 Value) { return FText::AsNumber(Value).ToString(); }
}

TSharedRef<SWidget> UDigimonVenomNXTPartyWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTPartyWidget::Button(const FString& Label, const FString& Action, FLinearColor Color)
{
    UDigimonVenomNXTActionButton* B = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(B, Color); B->InitializeAction(Action);
    B->OnAction.AddDynamic(this, &UDigimonVenomNXTPartyWidget::HandleAction);
    FButtonStyle Style = B->GetStyle(); Style.SetNormalPadding(FMargin(8, 8)); Style.SetPressedPadding(FMargin(8, 9, 8, 7)); B->SetStyle(Style);
    UTextBlock* Caption = DigimonPartyUI::Text(WidgetTree, Label, 11, DigimonPartyUI::White, true);
    Caption->SetJustification(ETextJustify::Center); B->SetContent(Caption); return B;
}

void UDigimonVenomNXTPartyWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("PartyWidgetTree"));
    using namespace DigimonPartyUI;
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;
    UBorder* Hero = PanelBox(WidgetTree, Cyan); Hero->SetPadding(FMargin(0)); Hero->SetClipping(EWidgetClipping::ClipToBounds); Add(Root, Hero, 3);
    UOverlay* HeroOverlay = WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(HeroOverlay);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, HeroOverlay, nullptr, FLinearColor(0.005f, 0.018f, 0.038f, 0.80f));
    UVerticalBox* HeroBody = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* HeroContentSlot = HeroOverlay->AddChildToOverlay(HeroBody)) { HeroContentSlot->SetPadding(FMargin(20, 16)); HeroContentSlot->SetHorizontalAlignment(HAlign_Fill); }
    Add(HeroBody, Text(WidgetTree, TEXT("PARTNER COMMAND"), 25, White, true), 1);
    Add(HeroBody, Text(WidgetTree, TEXT("Your team. Your journey. Every level earned."), 12, Cyan), 1);
    Summary = Text(WidgetTree, TEXT("Synchronizing your party..."), 14, Gold, true); Add(HeroBody, Summary, 5);
    Formation = Text(WidgetTree, TEXT(""), 12, Muted); Add(HeroBody, Formation, 2);
    Add(HeroBody, Text(WidgetTree, TEXT("Earn partner EXP from wild, story, rival and Season victories. Ranked and friendly battles do not award partner EXP."), 11, Muted), 2);
    UHorizontalBox* HeaderActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody, HeaderActions, 6);
    AddRow(HeaderActions, Button(TEXT("COLLECTION / EVOLUTION"), TEXT("page:Collection"), Cyan));
    AddRow(HeaderActions, Button(TEXT("DIGILAB / RESTORE PARTY"), TEXT("page:DigiLab"), Green));
    EmptyMessage = Text(WidgetTree, TEXT("Your party is empty. Choose your starter in Overview, or add a partner from your Collection."), 14, Gold); Add(Root, EmptyMessage, 8);
    Cards = WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root, Cards, 3);
}

void UDigimonVenomNXTPartyWidget::AddPartnerCard()
{
    using namespace DigimonPartyUI;
    FDigimonPartyCardView View;
    View.Card = PanelBox(WidgetTree, Cyan); Add(Cards, View.Card, 5);
    UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); View.Card->SetContent(Body);
    View.Role = Text(WidgetTree, TEXT(""), 11, Gold, true); Add(Body, View.Role, 1);
    UHorizontalBox* MainRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, MainRow, 7);
    UBorder* PortraitPanel = PanelBox(WidgetTree, Cyan); PortraitPanel->SetPadding(FMargin(6));
    PortraitPanel->SetBrush(FSlateRoundedBoxBrush(Ink, 8.0f, Cyan.CopyWithNewOpacity(0.2f), 1.0f));
    USizeBox* PortraitBounds = WidgetTree->ConstructWidget<USizeBox>(); PortraitBounds->SetWidthOverride(132); PortraitBounds->SetHeightOverride(148);
    View.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitBounds->AddChild(View.Portrait); PortraitPanel->SetContent(PortraitBounds); AddRow(MainRow, PortraitPanel, false, 0);
    UVerticalBox* Detail = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(MainRow, Detail, true, 14);
    View.Name = Text(WidgetTree, TEXT(""), 22, White, true); View.Name->SetAutoWrapText(false); View.Name->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); Add(Detail, View.Name, 1);
    View.Identity = Text(WidgetTree, TEXT(""), 11, Cyan, true); Add(Detail, View.Identity, 2);
    UTextBlock* TypeText = nullptr; UTextBlock* ElementText = nullptr;
    Add(Detail, DigimonVenomNXTCombatUI::TypeChips(WidgetTree, TypeText, ElementText, 10), 2);
    View.Affinity = TypeText; View.Element = ElementText;
    UHorizontalBox* VitalsRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Detail, VitalsRow, 4);
    UVerticalBox* HPColumn = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(VitalsRow, HPColumn, true, 0);
    View.Health = Text(WidgetTree, TEXT(""), 12, Green, true); Add(HPColumn, View.Health, 1); View.HPBar = Meter(WidgetTree, HPColumn, Green);
    UVerticalBox* SPColumn = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(VitalsRow, SPColumn, true, 6);
    View.SkillPoints = Text(WidgetTree, TEXT(""), 12, Cyan, true); Add(SPColumn, View.SkillPoints, 1); View.SPBar = Meter(WidgetTree, SPColumn, Cyan);
    View.Stats = Text(WidgetTree, TEXT(""), 12, White, true); Add(Detail, View.Stats, 3);
    View.Growth = Text(WidgetTree, TEXT(""), 11, Muted); Add(Detail, View.Growth, 2);
    USizeBox* ActionBounds = WidgetTree->ConstructWidget<USizeBox>(); ActionBounds->SetWidthOverride(156); AddRow(MainRow, ActionBounds, false, 0);
    UVerticalBox* Actions = WidgetTree->ConstructWidget<UVerticalBox>(); ActionBounds->AddChild(Actions);
    View.Leader = Button(TEXT("MAKE LEADER"), TEXT(""), Gold); Add(Actions, View.Leader, 2);
    View.Inspect = Button(TEXT("EVOLUTION / DETAILS"), TEXT(""), Cyan); Add(Actions, View.Inspect, 2);
    UHorizontalBox* OrderRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Actions, OrderRow, 2);
    View.MoveEarlier = Button(TEXT("UP"), TEXT(""), Cyan); AddRow(OrderRow, View.MoveEarlier, true, 1);
    View.MoveLater = Button(TEXT("DOWN"), TEXT(""), Cyan); AddRow(OrderRow, View.MoveLater, true, 1);
    View.Remove = Button(TEXT("TO COLLECTION"), TEXT(""), Muted); Add(Actions, View.Remove, 2);
    UBorder* XPPanel = PanelBox(WidgetTree, Violet); XPPanel->SetPadding(FMargin(12, 8)); XPPanel->SetBrush(FSlateRoundedBoxBrush(Ink, 6.0f)); Add(Body, XPPanel, 0);
    UVerticalBox* XPColumn = WidgetTree->ConstructWidget<UVerticalBox>(); XPPanel->SetContent(XPColumn);
    View.Experience = Text(WidgetTree, TEXT(""), 12, Gold, true); Add(XPColumn, View.Experience, 1);
    View.XPBar = Meter(WidgetTree, XPColumn, Gold, 9.0f);
    View.NextLevel = Text(WidgetTree, TEXT(""), 11, Muted); Add(XPColumn, View.NextLevel, 1);
    PartnerCards.Add(View);
}

void UDigimonVenomNXTPartyWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data)
{
    BuildLayout();
    if (!PlayerState || !Data) return;
    using namespace DigimonPartyUI;
    const auto& Profile = PlayerState->Profile;
    const auto* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 ActiveCount = FMath::Clamp(Settings->ActiveBattleSize, 1, 6);
    const bool bLocked = PlayerState->HasActiveBattle();
    while (PartnerCards.Num() < Profile.Party.Num()) AddPartnerCard();
    int32 Healthy = 0, TotalLevels = 0;
    for (int32 Index = 0; Index < PartnerCards.Num(); ++Index)
    {
        auto& View = PartnerCards[Index];
        FDigimonOwnedPartner Partner;
        const bool bPresent = Profile.Party.IsValidIndex(Index) && PlayerState->GetPartner(Profile.Party[Index], Partner);
        View.Card->SetVisibility(bPresent ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        if (!bPresent) continue;
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        FDigimonSpeciesDefinition Definition; const bool bHasDefinition = Data->GetSpecies(Partner.SpeciesId, Definition);
        const auto Progress = DigimonVenomNXTProgressionCore::GetProgress(Partner.Level, Partner.Experience, Settings->MaxPartnerLevel);
        const FString Variant = DigimonVenomNXTUI::VarietyLabel(Partner.Variant);
        const FLinearColor Accent = Index == 0 ? Gold : Index < ActiveCount ? Cyan : Violet;
        View.Card->SetBrush(FSlateRoundedBoxBrush(Panel, 10.0f, Accent.CopyWithNewOpacity(Index == 0 ? 0.85f : 0.42f), Index == 0 ? 2.0f : 1.0f));
        View.Role->SetColorAndOpacity(Accent);
        Set(View.Role, FString::Printf(TEXT("SLOT %02d  /  %s%s"), Index + 1, Index < ActiveCount ? TEXT("ACTIVE TEAM") : TEXT("RESERVE"), Index == 0 ? TEXT("  /  LEADER + FIELD FOLLOWER") : TEXT("")));
        View.Portrait->SetDigimon(Partner.SpeciesId, Partner.Variant); Set(View.Name, Unit.DisplayName); View.Name->SetToolTipText(FText::FromString(Unit.DisplayName));
        Set(View.Identity, FString::Printf(TEXT("LEVEL %d   /   %s   /   %s"), Progress.Level, bHasDefinition ? *Stage(Definition.Stage) : TEXT("PARTNER"), *Variant));
        View.Identity->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
        DigimonVenomNXTCombatUI::UpdateChips(View.Affinity, View.Element, Unit.Affinity, Unit.Element);
        View.Stats->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::StatHelp()));
        Set(View.Health, FString::Printf(TEXT("HP  %d / %d"), Unit.HP, Unit.Stats.MaxHP));
        Set(View.SkillPoints, FString::Printf(TEXT("SP  %d / %d"), Unit.SP, Unit.Stats.MaxSP));
        const float HPFraction = Unit.Stats.MaxHP > 0 ? static_cast<float>(Unit.HP) / Unit.Stats.MaxHP : 0.0f;
        View.HPBar->SetPercent(FMath::Clamp(HPFraction, 0.0f, 1.0f)); View.HPBar->SetFillColorAndOpacity(HPFraction <= 0.25f ? Red : Green);
        View.Health->SetColorAndOpacity(HPFraction <= 0.25f ? Red : Green);
        View.SPBar->SetPercent(Unit.Stats.MaxSP > 0 ? FMath::Clamp(static_cast<float>(Unit.SP) / Unit.Stats.MaxSP, 0.0f, 1.0f) : 0.0f);
        Set(View.Stats, FString::Printf(TEXT("ATK %d   DEF %d   INT %d   SPD %d\nINT: special attack & special defense"), Unit.Stats.Attack, Unit.Stats.Defense, Unit.Stats.Spirit, Unit.Stats.Speed));
        Set(View.Growth, FString::Printf(TEXT("CAM %d / 100   /   ABI %d / %d%s"), Partner.CAM, Partner.ABI, DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI), Unit.HP <= 0 ? TEXT("   /   NEEDS RESTORING") : TEXT("")));
        View.XPBar->SetPercent(static_cast<float>(Progress.Fraction)); View.XPBar->SetFillColorAndOpacity(Progress.AtCap ? Cyan : Gold);
        Set(View.Experience, Progress.AtCap ? FString::Printf(TEXT("LEVEL %d  /  LEVEL CAP REACHED"), Progress.Level) : FString::Printf(TEXT("LEVEL %d  →  %d     %s / %s EXP"), Progress.Level, Progress.Level + 1, *Number(Progress.IntoLevel), *Number(Progress.LevelSpan)));
        Set(View.NextLevel, Progress.AtCap ? TEXT("Maximum level for this world. Visit Evolution to plan your next form.") : FString::Printf(TEXT("%s EXP to next level"), *Number(Progress.Remaining)));
        View.XPBar->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s total EXP. The bar shows EXP earned within this level and begins again after each level up."), *Number(Partner.Experience))));
        const FString Id = Partner.InstanceId.ToString();
        Set(Cast<UTextBlock>(View.Leader->GetContent()), Index == 0 ? TEXT("CURRENT LEADER") : TEXT("MAKE LEADER"));
        View.Leader->InitializeAction(TEXT("leader:") + Id); View.Leader->SetIsEnabled(!bLocked && Index > 0);
        View.Inspect->InitializeAction(TEXT("inspectpartner:") + Id);
        View.MoveEarlier->InitializeAction(TEXT("partymove:") + Id, -1); View.MoveEarlier->SetIsEnabled(!bLocked && Index > 0);
        View.MoveLater->InitializeAction(TEXT("partymove:") + Id, 1); View.MoveLater->SetIsEnabled(!bLocked && Index + 1 < Profile.Party.Num());
        View.MoveEarlier->SetToolTipText(FText::FromString(TEXT("Move one slot earlier. Slot 1 is your leader and field follower.")));
        View.MoveLater->SetToolTipText(FText::FromString(TEXT("Move one slot later. The first active slots enter battle.")));
        View.Remove->InitializeAction(TEXT("partyremove:") + Id); View.Remove->SetIsEnabled(!bLocked && Profile.Party.Num() > 1);
        View.Remove->SetToolTipText(FText::FromString(TEXT("Keep this partner in your collection. At least one partner must remain in your party.")));
        Healthy += Unit.HP > 0 ? 1 : 0; TotalLevels += Partner.Level;
    }
    const int32 Count = Profile.Party.Num();
    Set(Summary, FString::Printf(TEXT("%d / %d PARTNERS   /   %d READY   /   AVERAGE LV. %.1f"), Count, Settings->MaxPartySize, Healthy, Count > 0 ? static_cast<float>(TotalLevels) / Count : 0.0f));
    Set(Formation, bLocked ? TEXT("Party changes are locked while a battle is active. Finish or resume your battle to change the formation.") : FString::Printf(TEXT("First %d slots: active battle team. Slot 1: your leader and field follower. Move partners up or down to set your formation."), ActiveCount));
    EmptyMessage->SetVisibility(Count == 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UDigimonVenomNXTPartyWidget::HandleAction(const FString& Action, int32 Payload)
{
    OnAction.Broadcast(Action, Payload);
}
