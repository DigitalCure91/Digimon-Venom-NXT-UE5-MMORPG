#include "DigimonVenomNXTEvolutionWidget.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTSettings.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

namespace DigimonEvolutionUI
{
    constexpr int32 PageSize = 12;
    const FLinearColor Ink(0.009f, 0.022f, 0.045f, 1.0f);
    const FLinearColor Panel(0.018f, 0.052f, 0.090f, 1.0f);
    const FLinearColor Cyan(0.08f, 0.88f, 0.94f, 1.0f);
    const FLinearColor Gold(1.0f, 0.74f, 0.21f, 1.0f);
    const FLinearColor Violet(0.71f, 0.48f, 1.0f, 1.0f);
    const FLinearColor White(0.94f, 0.98f, 1.0f, 1.0f);
    const FLinearColor Muted(0.59f, 0.73f, 0.84f, 1.0f);
    const FLinearColor Ready(0.34f, 0.93f, 0.66f, 1.0f);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 13, FLinearColor Color = White, bool bBold = false)
    {
        UTextBlock* W = Tree->ConstructWidget<UTextBlock>();
        W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font = W->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); W->SetFont(Font);
        return W;
    }
    void Set(UTextBlock* Widget, const FString& Value) { if (Widget) Widget->SetText(FText::FromString(Value)); }
    void Add(UVerticalBox* Box, UWidget* Child, float Pad = 3.0f)
    {
        if (UVerticalBoxSlot* Slot = Box->AddChildToVerticalBox(Child)) { Slot->SetPadding(FMargin(0, Pad)); Slot->SetHorizontalAlignment(HAlign_Fill); }
    }
    void AddRow(UHorizontalBox* Box, UWidget* Child, bool bFill = true, float Pad = 4.0f)
    {
        if (UHorizontalBoxSlot* Slot = Box->AddChildToHorizontalBox(Child))
        {
            Slot->SetPadding(FMargin(Pad, 0)); Slot->SetVerticalAlignment(VAlign_Center);
            if (bFill) Slot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
    UBorder* Card(UWidgetTree* Tree, FLinearColor Accent = Cyan)
    {
        UBorder* W = Tree->ConstructWidget<UBorder>();
        W->SetBrush(FSlateRoundedBoxBrush(Panel, 9.0f, Accent.CopyWithNewOpacity(0.38f), 1.0f));
        W->SetPadding(FMargin(14)); return W;
    }
    USizeBox* Portrait(UWidgetTree* Tree, UDigimonVenomNXTAnimatedPortrait*& Out, float Size)
    {
        USizeBox* Box = Tree->ConstructWidget<USizeBox>(); Box->SetWidthOverride(Size); Box->SetHeightOverride(Size);
        Out = Tree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); Box->AddChild(Out); return Box;
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
    FString Variant(EDigimonVariant Value)
    {
        return DigimonVenomNXTUI::VarietyLabel(Value);
    }
    FString Name(const FDigimonOwnedPartner& Partner, const UDigimonVenomNXTDataSubsystem* Data)
    {
        if (!Partner.Nickname.IsEmpty()) return Partner.Nickname;
        FDigimonSpeciesDefinition Definition;
        return Data && Data->GetSpecies(Partner.SpeciesId, Definition) ? Definition.DisplayName.ToString() : Partner.SpeciesId.ToString();
    }
}

TSharedRef<SWidget> UDigimonVenomNXTEvolutionWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTEvolutionWidget::Button(const FString& Label, const FString& Action, FLinearColor Color)
{
    UDigimonVenomNXTActionButton* B = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(B, Color); B->InitializeAction(Action);
    B->OnAction.AddDynamic(this, &UDigimonVenomNXTEvolutionWidget::HandleAction);
    UTextBlock* Caption = DigimonEvolutionUI::Text(WidgetTree, Label, 12, DigimonEvolutionUI::White, true);
    Caption->SetJustification(ETextJustify::Center); B->SetContent(Caption);
    return B;
}

void UDigimonVenomNXTEvolutionWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("EvolutionWidgetTree"));
    using namespace DigimonEvolutionUI;
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;
    Summary = Text(WidgetTree, TEXT("Connecting to your collection..."), 12, Gold, true); Add(Root, Summary, 2);
    UHorizontalBox* TabRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, TabRow, 7);
    const TCHAR* TabNames[] = {TEXT("EVOLVE"), TEXT("DE-EVOLVE"), TEXT("SCAN DATABASE")};
    for (int32 Index = 0; Index < 3; ++Index)
    {
        UDigimonVenomNXTActionButton* Tab = Button(TabNames[Index], TEXT("evolutiontab"), Index == 1 ? Violet : Cyan);
        Tab->InitializeAction(TEXT("evolutiontab"), Index); Tabs.Add(Tab); AddRow(TabRow, Tab);
    }
    PartnerSection = WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root, PartnerSection, 0);
    UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(PartnerSection, Pager, 3);
    RosterPrevious = Button(TEXT("PREVIOUS"), TEXT("rosterpage"), Cyan); AddRow(Pager, RosterPrevious, false);
    RosterPageLabel = Text(WidgetTree, TEXT("YOUR PARTNERS"), 12, Muted, true); RosterPageLabel->SetJustification(ETextJustify::Center); AddRow(Pager, RosterPageLabel);
    RosterNext = Button(TEXT("NEXT"), TEXT("rosterpage"), Cyan); AddRow(Pager, RosterNext, false);
    UUniformGridPanel* RosterGrid = WidgetTree->ConstructWidget<UUniformGridPanel>(); RosterGrid->SetSlotPadding(FMargin(3));
    if (UVerticalBoxSlot* S = PartnerSection->AddChildToVerticalBox(RosterGrid)) { S->SetHorizontalAlignment(HAlign_Left); S->SetPadding(FMargin(0,2)); }
    for (int32 Index = 0; Index < PageSize; ++Index)
    {
        FDigimonEvolutionPartnerTile Tile;
        Tile.Button = Button(TEXT(""), TEXT("selectpartner"), Cyan);
        UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); Tile.Button->SetContent(Body);
        UDigimonVenomNXTAnimatedPortrait* PortraitWidget = nullptr;
        USizeBox* PortraitBox = Portrait(WidgetTree, PortraitWidget, 54); Tile.Portrait = PortraitWidget;
        if (UVerticalBoxSlot* S = Body->AddChildToVerticalBox(PortraitBox)) S->SetHorizontalAlignment(HAlign_Center);
        Tile.Name = Text(WidgetTree, TEXT(""), 11, White, true); Tile.Name->SetAutoWrapText(false); Tile.Name->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); Tile.Name->SetJustification(ETextJustify::Center); Add(Body, Tile.Name, 1);
        Tile.Detail = Text(WidgetTree, TEXT(""), 10, Muted); Tile.Detail->SetJustification(ETextJustify::Center); Add(Body, Tile.Detail, 0);
        USizeBox* TileBounds = WidgetTree->ConstructWidget<USizeBox>(); TileBounds->SetWidthOverride(138); TileBounds->AddChild(Tile.Button);
        if (UUniformGridSlot* S = RosterGrid->AddChildToUniformGrid(TileBounds, Index / 6, Index % 6)) S->SetHorizontalAlignment(HAlign_Fill);
        RosterTiles.Add(Tile);
    }

    Hero = Card(WidgetTree, Gold); Hero->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.017f,0.045f,0.078f,1), 12, Gold.CopyWithNewOpacity(0.60f), 1)); Add(PartnerSection, Hero, 8);
    UVerticalBox* HeroBody = WidgetTree->ConstructWidget<UVerticalBox>(); Hero->SetContent(HeroBody);
    UHorizontalBox* HeroRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody, HeroRow, 0);
    UDigimonVenomNXTAnimatedPortrait* PortraitWidget = nullptr;
    USizeBox* HeroBox = Portrait(WidgetTree, PortraitWidget, 158); HeroPortrait = PortraitWidget; AddRow(HeroRow, HeroBox, false, 8);
    UVerticalBox* Info = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(HeroRow, Info);
    Add(Info, Text(WidgetTree, TEXT("SELECTED PARTNER / EVOLUTION LINK"), 10, Gold, true), 1);
    HeroName = Text(WidgetTree, TEXT(""), 24, White, true); Add(Info, HeroName, 2);
    HeroStage = Text(WidgetTree, TEXT(""), 12, Cyan, true); Add(Info, HeroStage, 1);
    UTextBlock* TypeText = nullptr; UTextBlock* ElementText = nullptr;
    Add(Info, DigimonVenomNXTCombatUI::TypeChips(WidgetTree, TypeText, ElementText, 11), 3);
    HeroAffinity = TypeText; HeroElement = ElementText;
    HeroStats = Text(WidgetTree, TEXT(""), 12, Muted); Add(Info, HeroStats, 2);
    UBorder* XPPanel = Card(WidgetTree, Gold); XPPanel->SetPadding(FMargin(10,7)); XPPanel->SetBrush(FSlateRoundedBoxBrush(Ink, 6.0f)); Add(Info, XPPanel, 4);
    UVerticalBox* XPColumn = WidgetTree->ConstructWidget<UVerticalBox>(); XPPanel->SetContent(XPColumn);
    HeroExperience = Text(WidgetTree, TEXT(""), 12, Gold, true); Add(XPColumn, HeroExperience, 1);
    HeroXP = Meter(WidgetTree, XPColumn, Gold, 9.0f);
    HeroNextLevel = Text(WidgetTree, TEXT(""), 11, Muted); Add(XPColumn, HeroNextLevel, 1);
    UHorizontalBox* BondRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Info, BondRow, 3);
    UVerticalBox* CAMColumn = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(BondRow, CAMColumn);
    HeroCAMText = Text(WidgetTree, TEXT(""), 12, Cyan, true); Add(CAMColumn, HeroCAMText, 1); HeroCAM = Meter(WidgetTree, CAMColumn, Cyan);
    UVerticalBox* ABIColumn = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(BondRow, ABIColumn);
    HeroABIText = Text(WidgetTree, TEXT(""), 12, Violet, true); Add(ABIColumn, HeroABIText, 1); HeroABI = Meter(WidgetTree, ABIColumn, Violet);
    HeroTraining = Text(WidgetTree, TEXT(""), 11, Muted); Add(Info, HeroTraining, 2);
    UHorizontalBox* PartyActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Info, PartyActions, 3);
    PartyButton = Button(TEXT("ADD TO PARTY"), TEXT(""), Cyan); AddRow(PartyActions, PartyButton);
    LeaderButton = Button(TEXT("MAKE LEADER"), TEXT(""), Gold); AddRow(PartyActions, LeaderButton);

    UHorizontalBox* FeedActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody, FeedActions, 5);
    CAMButton = Button(TEXT(""), TEXT(""), Cyan); CAMButtonLabel = Cast<UTextBlock>(CAMButton->GetContent()); AddRow(FeedActions, CAMButton);
    ABIButton = Button(TEXT(""), TEXT(""), Violet); ABIButtonLabel = Cast<UTextBlock>(ABIButton->GetContent()); AddRow(FeedActions, ABIButton);
    AddRow(FeedActions, Button(TEXT("BUY DIGIMEAT"), TEXT("page:Shop"), Gold), false);
    Add(HeroBody, Text(WidgetTree, TEXT("CAM grows with time in your party and CAM DigiMeat. ABI is permanent: evolving, de-evolving and ABI DigiMeat increase it."), 11, Muted), 1);
    RouteIntro = Text(WidgetTree, TEXT(""), 14, Gold, true); Add(PartnerSection, RouteIntro, 5);
    RouteEmpty = Text(WidgetTree, TEXT(""), 13, Muted); Add(PartnerSection, RouteEmpty, 3);
    RouteGrid = WidgetTree->ConstructWidget<UUniformGridPanel>(); RouteGrid->SetSlotPadding(FMargin(4)); Add(PartnerSection, RouteGrid, 1);

    ScanSection = WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root, ScanSection, 2);
    Add(ScanSection, Text(WidgetTree, TEXT("Your field research, recorded in DigiDex."), 18, Gold, true), 3);
    Add(ScanSection, Text(WidgetTree, TEXT("Win wild encounters to collect scan data. Materialization creates a new partner; evolution transforms the partner you already own."), 13, Muted), 2);
    Add(ScanSection, Button(TEXT("OPEN DIGIDEX / MATERIALIZE"), TEXT("page:DigiDex"), Cyan), 5);
    UHorizontalBox* ScanPager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ScanSection, ScanPager, 4);
    ScanPrevious = Button(TEXT("PREVIOUS"), TEXT("scanpage"), Cyan); AddRow(ScanPager, ScanPrevious, false);
    ScanPageLabel = Text(WidgetTree, TEXT(""), 12, Muted, true); ScanPageLabel->SetJustification(ETextJustify::Center); AddRow(ScanPager, ScanPageLabel);
    ScanNext = Button(TEXT("NEXT"), TEXT("scanpage"), Cyan); AddRow(ScanPager, ScanNext, false);
    ScanGrid = WidgetTree->ConstructWidget<UUniformGridPanel>(); ScanGrid->SetSlotPadding(FMargin(4)); Add(ScanSection, ScanGrid, 2);
}

void UDigimonVenomNXTEvolutionWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* InPlayerState, UDigimonVenomNXTDataSubsystem* InData)
{
    BuildLayout(); PlayerState = InPlayerState; Data = InData;
    if (!PlayerState.IsValid() || !Data.IsValid()) return;
    const auto& Profile = PlayerState->Profile;
    FDigimonOwnedPartner Partner;
    if (!PlayerState->GetPartner(SelectedPartnerId, Partner))
    {
        SelectedPartnerId = Profile.Party.Num() > 0 ? Profile.Party[0] : Profile.Collection.Num() > 0 ? Profile.Collection[0].InstanceId : FGuid();
        const int32 Index = Profile.Collection.IndexOfByPredicate([this](const FDigimonOwnedPartner& Owned) { return Owned.InstanceId == SelectedPartnerId; });
        RosterPage = FMath::Max(0, Index) / DigimonEvolutionUI::PageSize;
    }
    int32 Normal = 0, Paradox = 0, Shiny = 0, Firewall = 0;
    for (const auto& Owned : Profile.Collection)
        if (Owned.Variant == EDigimonVariant::Firewall) ++Firewall; else if (Owned.Variant == EDigimonVariant::Shiny) ++Shiny; else if (Owned.Variant == EDigimonVariant::Paradox) ++Paradox; else if (Owned.Variant == EDigimonVariant::Normal) ++Normal;
    DigimonEvolutionUI::Set(Summary, FString::Printf(TEXT("%d PARTNERS   /   %d NORMAL   /   %d PARADOX   /   %d SHINY   /   %d FIREWALL"), Profile.Collection.Num(), Normal, Paradox, Shiny, Firewall));
    for (int32 Index = 0; Index < Tabs.Num(); ++Index) DigimonVenomNXTUI::StyleButton(Tabs[Index], Index == 1 ? DigimonEvolutionUI::Violet : DigimonEvolutionUI::Cyan, ActiveTab == Index);
    PartnerSection->SetVisibility(ActiveTab == 2 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    ScanSection->SetVisibility(ActiveTab == 2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (ActiveTab == 2) RefreshScans();
    else { RefreshRoster(); RefreshPartner(); RefreshRoutes(); }
}

void UDigimonVenomNXTEvolutionWidget::RefreshRoster()
{
    using namespace DigimonEvolutionUI;
    const auto& Collection = PlayerState->Profile.Collection;
    const int32 Pages = FMath::Max(1, FMath::DivideAndRoundUp(Collection.Num(), PageSize));
    RosterPage = FMath::Clamp(RosterPage, 0, Pages - 1);
    Set(RosterPageLabel, FString::Printf(TEXT("CHOOSE A PARTNER   /   PAGE %d OF %d"), RosterPage + 1, Pages));
    RosterPrevious->InitializeAction(TEXT("rosterpage"), RosterPage - 1); RosterPrevious->SetIsEnabled(RosterPage > 0);
    RosterNext->InitializeAction(TEXT("rosterpage"), RosterPage + 1); RosterNext->SetIsEnabled(RosterPage + 1 < Pages);
    for (int32 Index = 0; Index < RosterTiles.Num(); ++Index)
    {
        auto& Tile = RosterTiles[Index]; const int32 CollectionIndex = RosterPage * PageSize + Index;
        // Collapse the bounds too, so a short collection does not reserve an empty second row.
        if (UWidget* Bounds = Tile.Button->GetParent()) Bounds->SetVisibility(Collection.IsValidIndex(CollectionIndex) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        if (!Collection.IsValidIndex(CollectionIndex)) continue;
        const auto& Partner = Collection[CollectionIndex];
        Tile.Portrait->SetDigimon(Partner.SpeciesId, Partner.Variant);
        const FString DisplayName = Name(Partner, Data.Get()); Set(Tile.Name, DisplayName);
        const int32 PartySlot = PlayerState->Profile.Party.IndexOfByKey(Partner.InstanceId);
        Set(Tile.Detail, FString::Printf(TEXT("Lv.%d%s"), Partner.Level, PartySlot == 0 ? TEXT(" / LEADER") : PartySlot != INDEX_NONE ? TEXT(" / PARTY") : TEXT("")));
        Tile.Button->InitializeAction(TEXT("selectpartner:") + Partner.InstanceId.ToString());
        Tile.Button->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s / %s / CAM %d / ABI %d"), *DisplayName, *Variant(Partner.Variant), Partner.CAM, Partner.ABI)));
        DigimonVenomNXTUI::StyleButton(Tile.Button, DigimonVenomNXTUI::VarietyAccent(Partner.Variant), Partner.InstanceId == SelectedPartnerId);
        FButtonStyle Style = Tile.Button->GetStyle(); Style.SetNormalPadding(FMargin(5,3)); Style.SetPressedPadding(FMargin(5,4,5,2)); Tile.Button->SetStyle(Style);
    }
}

void UDigimonVenomNXTEvolutionWidget::SelectPartner(const FGuid& PartnerId)
{
    if (!PlayerState.IsValid() || !Data.IsValid()) return;
    FDigimonOwnedPartner Partner;
    if (!PlayerState->GetPartner(PartnerId, Partner)) return;
    SelectedPartnerId = PartnerId;
    const int32 CollectionIndex = PlayerState->Profile.Collection.IndexOfByPredicate([&PartnerId](const FDigimonOwnedPartner& Owned) { return Owned.InstanceId == PartnerId; });
    RosterPage = FMath::Max(0, CollectionIndex) / DigimonEvolutionUI::PageSize;
    ActiveTab = 0;
    RefreshFromProfile(PlayerState.Get(), Data.Get());
}

void UDigimonVenomNXTEvolutionWidget::RefreshPartner()
{
    using namespace DigimonEvolutionUI;
    FDigimonOwnedPartner Partner;
    const bool bHasPartner = PlayerState->GetPartner(SelectedPartnerId, Partner);
    Hero->SetVisibility(bHasPartner ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (!bHasPartner) return;
    FDigimonSpeciesDefinition Definition; Data->GetSpecies(Partner.SpeciesId, Definition);
    const auto* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 ABICap = DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI);
    HeroPortrait->SetDigimon(Partner.SpeciesId, Partner.Variant);
    Set(HeroName, Name(Partner, Data.Get()));
    Set(HeroStage, FString::Printf(TEXT("%s   /   %s   /   LEVEL %d"), *Stage(Definition.Stage), *Variant(Partner.Variant), Partner.Level));
    HeroStage->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
    const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data.Get());
    DigimonVenomNXTCombatUI::UpdateChips(HeroAffinity, HeroElement, Unit.Affinity, Unit.Element);
    HeroStats->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::StatHelp()));
    Set(HeroStats, FString::Printf(TEXT("HP %d / %d   /   SP %d / %d\nATK %d   DEF %d   INT %d   SPD %d\nINT = special attack & special defense"), Unit.HP, Unit.Stats.MaxHP, Unit.SP, Unit.Stats.MaxSP, Unit.Stats.Attack, Unit.Stats.Defense, Unit.Stats.Spirit, Unit.Stats.Speed));
    const auto Progress = DigimonVenomNXTProgressionCore::GetProgress(Partner.Level, Partner.Experience, Settings->MaxPartnerLevel);
    HeroXP->SetPercent(static_cast<float>(Progress.Fraction)); HeroXP->SetFillColorAndOpacity(Progress.AtCap ? Cyan : Gold);
    Set(HeroExperience, Progress.AtCap ? FString::Printf(TEXT("LEVEL %d  /  LEVEL CAP REACHED"), Progress.Level) : FString::Printf(TEXT("LEVEL %d  →  %d     %s / %s EXP"), Progress.Level, Progress.Level + 1, *FText::AsNumber(static_cast<int64>(Progress.IntoLevel)).ToString(), *FText::AsNumber(static_cast<int64>(Progress.LevelSpan)).ToString()));
    Set(HeroNextLevel, Progress.AtCap ? TEXT("Maximum level for this world. Plan your next evolution below.") : FString::Printf(TEXT("%s EXP to next level"), *FText::AsNumber(static_cast<int64>(Progress.Remaining)).ToString()));
    HeroXP->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s total EXP. The bar shows progress within this level, not lifetime EXP."), *FText::AsNumber(Partner.Experience).ToString())));
    Set(HeroCAMText, FString::Printf(TEXT("CAM  %d / 100"), Partner.CAM)); HeroCAM->SetPercent(FMath::Clamp(Partner.CAM / 100.0f, 0.0f, 1.0f));
    Set(HeroABIText, FString::Printf(TEXT("ABI  %d / %d"), Partner.ABI, ABICap)); HeroABI->SetPercent(FMath::Clamp(Partner.ABI / static_cast<float>(ABICap), 0.0f, 1.0f));
    Set(HeroTraining, FString::Printf(TEXT("PERMANENT TRAINING   %.0f / %d total   •   Maximum +100 per stat."), DigimonVenomNXTEvolution::TrainingUsed(Partner), DigimonVenomNXTEvolution::TrainingCapacity(Partner)));
    const int32 PartySlot = PlayerState->Profile.Party.IndexOfByKey(Partner.InstanceId);
    Set(Cast<UTextBlock>(PartyButton->GetContent()), PartySlot != INDEX_NONE ? TEXT("REMOVE FROM PARTY") : TEXT("ADD TO PARTY"));
    PartyButton->InitializeAction((PartySlot != INDEX_NONE ? TEXT("partyremove:") : TEXT("partyadd:")) + Partner.InstanceId.ToString());
    PartyButton->SetIsEnabled(PartySlot != INDEX_NONE ? PlayerState->Profile.Party.Num() > 1 : PlayerState->Profile.Party.Num() < Settings->MaxPartySize);
    Set(Cast<UTextBlock>(LeaderButton->GetContent()), PartySlot == 0 ? TEXT("CURRENT LEADER") : TEXT("MAKE LEADER"));
    LeaderButton->InitializeAction(TEXT("leader:") + Partner.InstanceId.ToString()); LeaderButton->SetIsEnabled(PartySlot > 0);
    const int32 CAMMeat = PlayerState->GetInventoryQuantity(TEXT("digimeat_cam"));
    const int32 ABIMeat = PlayerState->GetInventoryQuantity(TEXT("digimeat_abi"));
    FDigimonOwnedPartner CAMPreview = Partner, ABIPreview = Partner;
    const int32 CAMGain = DigimonVenomNXTEvolution::FeedCAM(CAMPreview), ABIGain = DigimonVenomNXTEvolution::FeedABI(ABIPreview);
    Set(CAMButtonLabel, FString::Printf(TEXT("FEED CAM +%d   /   %d OWNED"), CAMGain, CAMMeat));
    CAMButton->InitializeAction(TEXT("camtreat:") + Partner.InstanceId.ToString()); CAMButton->SetIsEnabled(CAMMeat > 0 && CAMGain > 0);
    CAMButton->SetToolTipText(FText::FromString(TEXT("Feed one CAM DigiMeat to this partner. Available from the Shop.")));
    Set(ABIButtonLabel, FString::Printf(TEXT("FEED ABI +%d   /   %d OWNED"), ABIGain, ABIMeat));
    ABIButton->InitializeAction(TEXT("abimeat:") + Partner.InstanceId.ToString()); ABIButton->SetIsEnabled(ABIMeat > 0 && ABIGain > 0);
    ABIButton->SetToolTipText(FText::FromString(TEXT("Feed one ABI DigiMeat for a permanent ABI increase. Available from the Shop.")));
}

void UDigimonVenomNXTEvolutionWidget::RefreshRoutes()
{
    using namespace DigimonEvolutionUI;
    FDigimonOwnedPartner Partner;
    const bool bHasPartner = PlayerState->GetPartner(SelectedPartnerId, Partner);
    TArray<FDigimonEvolutionOption> Options;
    if (bHasPartner)
        for (const auto& Option : DigimonVenomNXTEvolution::GetOptions(Partner, Data.Get()))
            if (Option.bDeEvolution == (ActiveTab == 1)) Options.Add(Option);
    TArray<FName> Keys;
    for (const auto& Option : Options) Keys.Add(Option.TargetSpeciesId);
    if (Keys != VisibleRouteIds)
    {
        VisibleRouteIds = Keys; RouteGrid->ClearChildren(); RouteViews.Reset();
        for (int32 Index = 0; Index < Options.Num(); ++Index)
        {
            FDigimonEvolutionRouteView View;
            View.Card = Card(WidgetTree, ActiveTab == 1 ? Violet : Cyan);
            UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); View.Card->SetContent(Body);
            View.Status = Text(WidgetTree, TEXT(""), 10, Gold, true); Add(Body, View.Status, 1);
            UHorizontalBox* RouteRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, RouteRow, 4);
            UDigimonVenomNXTAnimatedPortrait* PortraitWidget = nullptr;
            USizeBox* PortraitBox = Portrait(WidgetTree, PortraitWidget, 116); View.Portrait = PortraitWidget; AddRow(RouteRow, PortraitBox, false, 2);
            UVerticalBox* Detail = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(RouteRow, Detail);
            View.Name = Text(WidgetTree, TEXT(""), 17, White, true); View.Name->SetWrapTextAt(210); Add(Detail, View.Name, 2);
            View.Stage = Text(WidgetTree, TEXT(""), 10, Cyan, true); Add(Detail, View.Stage, 2);
            for (int32 Metric = 0; Metric < 3; ++Metric)
            {
                UTextBlock* Label = Text(WidgetTree, TEXT(""), 11, Muted); Add(Detail, Label, 1); View.RequirementLabels.Add(Label);
                View.RequirementBars.Add(Meter(WidgetTree, Detail, Cyan));
            }
            View.AdditionalRequirements = Text(WidgetTree, TEXT(""), 11, Gold); Add(Body, View.AdditionalRequirements, 2);
            UBorder* GainPanel = Card(WidgetTree, Gold); GainPanel->SetPadding(FMargin(10,7)); GainPanel->SetBrush(FSlateRoundedBoxBrush(Ink, 5));
            View.Outcome = Text(WidgetTree, TEXT(""), 12, Gold, true); GainPanel->SetContent(View.Outcome); Add(Body, GainPanel, 3);
            Add(Body, Text(WidgetTree, TEXT("Resets to Lv.1 / 0 XP. CAM and permanent training stay."), 10, Muted), 3);
            View.Transform = Button(TEXT(""), TEXT(""), ActiveTab == 1 ? Violet : Gold); View.TransformLabel = Cast<UTextBlock>(View.Transform->GetContent()); Add(Body, View.Transform, 3);
            if (UUniformGridSlot* S = RouteGrid->AddChildToUniformGrid(View.Card, Index / 2, Index % 2)) { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
            RouteViews.Add(View);
        }
    }
    Set(RouteIntro, ActiveTab == 1 ? TEXT("DE-EVOLVE / REBUILD YOUR POTENTIAL") : TEXT("EVOLVE / YOUR NEXT FORM"));
    Set(RouteEmpty, !bHasPartner ? TEXT("Choose a starter or materialize a partner in the DigiLab to begin.") : Options.IsEmpty() ? (ActiveTab == 1 ? TEXT("This is a first-stage partner. Evolve it to unlock a return route and earn ABI through de-evolution.") : TEXT("This partner has reached its final evolution stage. De-evolve to build ABI, then raise it again.")) : TEXT(""));
    RouteEmpty->SetVisibility(Options.IsEmpty() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    const TCHAR* Labels[] = {TEXT("LEVEL"), TEXT("CAM"), TEXT("ABI")};
    for (int32 Index = 0; Index < Options.Num(); ++Index)
    {
        const auto& Option = Options[Index]; auto& View = RouteViews[Index];
        FDigimonSpeciesDefinition Target; Data->GetSpecies(Option.TargetSpeciesId, Target);
        View.Portrait->SetDigimon(Option.TargetSpeciesId, Partner.Variant); Set(View.Name, Target.DisplayName.ToString());
        Set(View.Stage, Stage(Option.TargetStage) + TEXT(" / ") + Variant(Partner.Variant));
        View.Stage->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
        Set(View.Status, Option.bAvailable ? TEXT("READY TO TRANSFORM") : TEXT("TRAINING REQUIRED")); View.Status->SetColorAndOpacity(Option.bAvailable ? Ready : Gold);
        const int32 Current[] = {Partner.Level, Partner.CAM, Partner.ABI};
        const int32 Required[] = {Option.RequiredLevel, Option.RequiredCAM, Option.RequiredABI};
        for (int32 Metric = 0; Metric < 3; ++Metric)
        {
            const bool bMet = Current[Metric] >= Required[Metric];
            Set(View.RequirementLabels[Metric], Required[Metric] > 0 ? FString::Printf(TEXT("%s  %d / %d  %s"), Labels[Metric], Current[Metric], Required[Metric], bMet ? TEXT("MET") : TEXT("NEEDED")) : FString::Printf(TEXT("%s  %d  /  NO MINIMUM"), Labels[Metric], Current[Metric]));
            View.RequirementLabels[Metric]->SetColorAndOpacity(bMet ? Ready : Gold);
            View.RequirementBars[Metric]->SetPercent(Required[Metric] > 0 ? FMath::Clamp(Current[Metric] / static_cast<float>(Required[Metric]), 0.0f, 1.0f) : 1.0f);
            View.RequirementBars[Metric]->SetFillColorAndOpacity(bMet ? Cyan : Gold);
        }
        Set(View.AdditionalRequirements, Option.MissingReasons); View.AdditionalRequirements->SetVisibility(Option.MissingReasons.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
        Set(View.Outcome, FString::Printf(TEXT("PERMANENT ABI  +%d     %d → %d"), Option.ABIGain, Partner.ABI, Option.ResultABI));
        View.Transform->InitializeAction((Option.bDeEvolution ? TEXT("deevolve:") : TEXT("evolve:")) + Partner.InstanceId.ToString() + TEXT(":") + Option.TargetSpeciesId.ToString());
        View.Transform->SetIsEnabled(Option.bAvailable);
        Set(View.TransformLabel, Option.bAvailable ? (Option.bDeEvolution ? TEXT("DE-EVOLVE TO THIS FORM") : TEXT("EVOLVE TO THIS FORM")) : TEXT("REQUIREMENTS NOT MET"));
        View.Transform->SetToolTipText(FText::FromString(Option.bAvailable ? TEXT("Transform this partner. Level and XP reset; permanent progression stays.") : Option.MissingReasons));
    }
}

void UDigimonVenomNXTEvolutionWidget::RefreshScans()
{
    using namespace DigimonEvolutionUI;
    TArray<FDigimonScanRecord> Scans = PlayerState->Profile.Scans;
    Scans.Sort([](const FDigimonScanRecord& A, const FDigimonScanRecord& B) { return A.SpeciesId == B.SpeciesId ? static_cast<uint8>(A.Variant) < static_cast<uint8>(B.Variant) : A.SpeciesId.LexicalLess(B.SpeciesId); });
    const int32 Pages = FMath::Max(1, FMath::DivideAndRoundUp(Scans.Num(), PageSize)); ScanPage = FMath::Clamp(ScanPage, 0, Pages - 1);
    Set(ScanPageLabel, FString::Printf(TEXT("%d SCAN RECORDS   /   PAGE %d OF %d"), Scans.Num(), ScanPage + 1, Pages));
    ScanPrevious->InitializeAction(TEXT("scanpage"), ScanPage - 1); ScanPrevious->SetIsEnabled(ScanPage > 0);
    ScanNext->InitializeAction(TEXT("scanpage"), ScanPage + 1); ScanNext->SetIsEnabled(ScanPage + 1 < Pages);
    uint32 Signature = GetTypeHash(ScanPage);
    Signature = HashCombine(Signature, GetTypeHash(PlayerState->ScanPolicy.MaterializeRequirementPercent));
    Signature = HashCombine(Signature, GetTypeHash(PlayerState->ScanPolicy.ScanCapPercent));
    for (int32 Index = ScanPage * PageSize; Index < FMath::Min(Scans.Num(), (ScanPage + 1) * PageSize); ++Index)
    {
        Signature = HashCombine(Signature, GetTypeHash(Scans[Index].SpeciesId)); Signature = HashCombine(Signature, GetTypeHash(static_cast<uint8>(Scans[Index].Variant))); Signature = HashCombine(Signature, GetTypeHash(Scans[Index].Percent)); Signature = HashCombine(Signature, GetTypeHash(Scans[Index].FractionalHundredths));
    }
    if (bHasScanSignature && ScanSignature == Signature) return;
    bHasScanSignature = true; ScanSignature = Signature; ScanGrid->ClearChildren();
    const int32 Required = FMath::Max(1, PlayerState->ScanPolicy.MaterializeRequirementPercent);
    const int32 ScanCap = FMath::Max(Required, PlayerState->ScanPolicy.ScanCapPercent);
    for (int32 Index = ScanPage * PageSize; Index < FMath::Min(Scans.Num(), (ScanPage + 1) * PageSize); ++Index)
    {
        const auto& Scan = Scans[Index]; FDigimonSpeciesDefinition Definition; Data->GetSpecies(Scan.SpeciesId, Definition);
        UBorder* ScanCard = Card(WidgetTree, Scan.Percent >= Required ? Gold : Cyan);
        UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>(); ScanCard->SetContent(Row);
        AddRow(Row, DigimonVenomNXTUI::AnimatedPortrait(WidgetTree, Scan.SpeciesId, Scan.Variant, 74, 74), false);
        UVerticalBox* Info = WidgetTree->ConstructWidget<UVerticalBox>(); AddRow(Row, Info);
        Add(Info, Text(WidgetTree, Definition.DisplayName.IsEmpty() ? Scan.SpeciesId.ToString() : Definition.DisplayName.ToString(), 14, White, true), 1);
        Add(Info, Text(WidgetTree, Variant(Scan.Variant), 10, DigimonVenomNXTUI::VarietyAccent(Scan.Variant), true), 1);
        Add(Info, Text(WidgetTree, FString::Printf(TEXT("SCAN %s%%   /   %s"), *DigimonVenomNXTUI::ScanValue(Scan.Percent, Scan.FractionalHundredths), Scan.Percent >= Required ? TEXT("READY IN DIGIDEX") : *FString::Printf(TEXT("%d%% REQUIRED"), Required)), 11, Scan.Percent >= Required ? Gold : Muted), 1);
        Meter(WidgetTree, Info, Scan.Percent >= Required ? Gold : Cyan)->SetPercent(FMath::Clamp(Scan.Percent / static_cast<float>(ScanCap), 0.0f, 1.0f));
        const int32 SlotIndex = Index - ScanPage * PageSize;
        if (UUniformGridSlot* S = ScanGrid->AddChildToUniformGrid(ScanCard, SlotIndex / 2, SlotIndex % 2)) S->SetHorizontalAlignment(HAlign_Fill);
    }
    if (Scans.IsEmpty()) ScanGrid->AddChildToUniformGrid(Text(WidgetTree, TEXT("No scan data yet. Explore a habitat and win a wild battle."), 14, Muted), 0, 0);
}

void UDigimonVenomNXTEvolutionWidget::HandleAction(const FString& Action, int32 Payload)
{
    if (Action == TEXT("evolutiontab")) ActiveTab = FMath::Clamp(Payload, 0, 2);
    else if (Action == TEXT("rosterpage")) RosterPage = FMath::Max(0, Payload);
    else if (Action == TEXT("scanpage")) ScanPage = FMath::Max(0, Payload);
    else if (Action.StartsWith(TEXT("selectpartner:")))
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(14), Id)) return;
        SelectedPartnerId = Id;
    }
    else { OnAction.Broadcast(Action, Payload); return; }
    RefreshFromProfile(PlayerState.Get(), Data.Get());
}
