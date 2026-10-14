#include "DigimonVenomNXTFarmWidget.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTFarmScene.h"
#include "DigimonVenomNXTPlayerController.h"
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
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

namespace DigimonFarmUI
{
    const FLinearColor Ink(0.007f, 0.023f, 0.041f, 0.96f);
    const FLinearColor Panel(0.014f, 0.052f, 0.075f, 0.95f);
    const FLinearColor Cyan(0.12f, 0.88f, 0.95f, 1.0f);
    const FLinearColor Mint(0.38f, 0.96f, 0.72f, 1.0f);
    const FLinearColor Gold(1.0f, 0.77f, 0.30f, 1.0f);
    const FLinearColor Violet(0.77f, 0.59f, 1.0f, 1.0f);
    const FLinearColor White(0.94f, 0.98f, 1.0f, 1.0f);
    const FLinearColor Muted(0.65f, 0.79f, 0.84f, 1.0f);
    constexpr int32 PageSize = 6;

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 12, FLinearColor Color = White, bool bBold = false)
    {
        UTextBlock* W = Tree->ConstructWidget<UTextBlock>();
        W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        W->SetVisibility(ESlateVisibility::HitTestInvisible);
        FSlateFontInfo Font = W->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); W->SetFont(Font); return W;
    }
    void Set(UTextBlock* W, const FString& Value) { if (W) W->SetText(FText::FromString(Value)); }
    void Add(UVerticalBox* Box, UWidget* Child, float Padding = 3.0f)
    {
        if (UVerticalBoxSlot* ChildSlot = Box->AddChildToVerticalBox(Child)) { ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill); }
    }
    void Row(UHorizontalBox* Box, UWidget* Child, bool bFill = true, float Padding = 4.0f)
    {
        if (UHorizontalBoxSlot* ChildSlot = Box->AddChildToHorizontalBox(Child))
        {
            ChildSlot->SetPadding(FMargin(Padding, 0)); ChildSlot->SetVerticalAlignment(VAlign_Center);
            if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
    UBorder* Card(UWidgetTree* Tree, FLinearColor Accent = Mint)
    {
        UBorder* W = Tree->ConstructWidget<UBorder>(); W->SetBrush(FSlateRoundedBoxBrush(Panel, 10.0f, Accent.CopyWithNewOpacity(0.45f), 1.0f)); W->SetPadding(FMargin(14)); return W;
    }
    UProgressBar* Meter(UWidgetTree* Tree, UVerticalBox* Box, FLinearColor Color)
    {
        UProgressBar* W = Tree->ConstructWidget<UProgressBar>(); W->SetFillColorAndOpacity(Color);
        FProgressBarStyle Style = W->GetWidgetStyle(); Style.SetBackgroundImage(FSlateRoundedBoxBrush(Ink, 3.0f)); Style.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White, 3.0f)); W->SetWidgetStyle(Style);
        USizeBox* Bounds = Tree->ConstructWidget<USizeBox>(); Bounds->SetHeightOverride(7); Bounds->AddChild(W); Add(Box, Bounds, 3); return W;
    }
    FString Number(int64 Value) { return FText::AsNumber(Value).ToString(); }
    FString XPText(const FDigimonOwnedPartner& Partner)
    {
        const auto Progress = DigimonVenomNXTProgressionCore::GetProgress(Partner.Level, Partner.Experience, GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel);
        return Progress.AtCap ? FString::Printf(TEXT("LV. %d  /  MAX LEVEL"), Progress.Level) : FString::Printf(TEXT("LV. %d → %d   %s / %s EXP   ·   %s to go"), Progress.Level, Progress.Level + 1, *Number(Progress.IntoLevel), *Number(Progress.LevelSpan), *Number(Progress.Remaining));
    }
}

UDigimonVenomNXTFarmActionButton::UDigimonVenomNXTFarmActionButton(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InitIsFocusable(false);
}

TSharedRef<SWidget> UDigimonVenomNXTFarmWidget::RebuildWidget()
{
    BuildLayout(); return Super::RebuildWidget();
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTFarmWidget::Button(const FString& Label, const FString& Action, FLinearColor Color, int32 Payload)
{
    UDigimonVenomNXTActionButton* B = WidgetTree->ConstructWidget<UDigimonVenomNXTFarmActionButton>();
    DigimonVenomNXTUI::StyleButton(B, Color); B->InitializeAction(Action, Payload);
    B->OnAction.AddDynamic(this, &UDigimonVenomNXTFarmWidget::HandleAction);
    FButtonStyle Style = B->GetStyle(); Style.SetNormalPadding(FMargin(8, 7)); Style.SetPressedPadding(FMargin(8, 8, 8, 6)); B->SetStyle(Style);
    UTextBlock* Caption = DigimonFarmUI::Text(WidgetTree, Label, 11, DigimonFarmUI::White, true); Caption->SetJustification(ETextJustify::Center); B->SetContent(Caption); return B;
}

void UDigimonVenomNXTFarmWidget::BuildLayout()
{
    if (bBuilt) return;
    bBuilt = true;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("FarmWidgetTree"));
    SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    if (bWorldOverlay) BuildWorldOverlay(); else BuildManagement();
}

void UDigimonVenomNXTFarmWidget::BuildManagement()
{
    using namespace DigimonFarmUI;
    UVerticalBox* Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;
    UBorder* Hero = Card(WidgetTree, Mint); Hero->SetPadding(FMargin(0)); Hero->SetClipping(EWidgetClipping::ClipToBounds); Add(Root, Hero, 3);
    UOverlay* HeroOverlay = WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(HeroOverlay);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, HeroOverlay, TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_DigiFarmLevel.T_DVN_DigiFarmLevel"), FLinearColor(0.005f, 0.021f, 0.036f, 0.78f));
    UVerticalBox* HeroBody = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* HeroBodySlot = HeroOverlay->AddChildToOverlay(HeroBody)) { HeroBodySlot->SetPadding(FMargin(22, 18)); HeroBodySlot->SetHorizontalAlignment(HAlign_Fill); }
    Add(HeroBody, Text(WidgetTree, TEXT("YOUR PRIVATE DIGIFARM"), 26, White, true), 1);
    Add(HeroBody, Text(WidgetTree, TEXT("A little island. A home for your Digimon."), 13, Mint), 3);
    Summary = Text(WidgetTree, TEXT("Preparing your island..."), 14, Gold, true); Add(HeroBody, Summary, 5);
    Add(HeroBody, Text(WidgetTree, TEXT("Walk beside your residents, select their nameplates and feed them while exploring. Your farm belongs only to your account."), 12, White), 3);
    Supplies = Text(WidgetTree, TEXT(""), 12, Muted); Add(HeroBody, Supplies, 3);
    UHorizontalBox* HeroActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody, HeroActions, 6);
    Enter = Button(TEXT("ENTER YOUR ISLAND"), TEXT("farmenter"), Mint); Row(HeroActions, Enter);
    Row(HeroActions, Button(TEXT("BUY FARM SUPPLIES"), TEXT("page:Shop"), Gold));
    Leave = Button(TEXT("LEAVE FARM"), TEXT("farmleave"), Muted); Row(HeroActions, Leave);
    Add(Root, Text(WidgetTree, TEXT("RESIDENT MANAGEMENT"), 17, Cyan, true), 9);
    Add(Root, Text(WidgetTree, TEXT("Place any partner from your collection. Farm residence does not remove a partner from your battle party. Changes save to your account."), 12, Muted), 1);
    UHorizontalBox* Tabs = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Tabs, 6);
    ResidentsTab = Button(TEXT("ON YOUR ISLAND"), TEXT("farmfilter"), Mint, 0); Row(Tabs, ResidentsTab);
    CollectionTab = Button(TEXT("AVAILABLE COLLECTION"), TEXT("farmfilter"), Cyan, 1); Row(Tabs, CollectionTab);
    EmptyMessage = Text(WidgetTree, TEXT(""), 14, Muted); Add(Root, EmptyMessage, 10);
    Cards = WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root, Cards, 3);
    for (int32 Index = 0; Index < PageSize; ++Index) AddResidentCard();
    UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Pager, 8);
    Previous = Button(TEXT("PREVIOUS"), TEXT("farmpage"), Cyan, -1); Row(Pager, Previous);
    PageLabel = Text(WidgetTree, TEXT("1 / 1"), 12, White, true); PageLabel->SetJustification(ETextJustify::Center); Row(Pager, PageLabel);
    Next = Button(TEXT("NEXT"), TEXT("farmpage"), Cyan, 1); Row(Pager, Next);
}

void UDigimonVenomNXTFarmWidget::AddResidentCard()
{
    using namespace DigimonFarmUI;
    FDigimonFarmCardView View;
    View.Card = Card(WidgetTree, Mint); Add(Cards, View.Card, 4);
    UHorizontalBox* Main = WidgetTree->ConstructWidget<UHorizontalBox>(); View.Card->SetContent(Main);
    USizeBox* PortraitSize = WidgetTree->ConstructWidget<USizeBox>(); PortraitSize->SetWidthOverride(96); PortraitSize->SetHeightOverride(108);
    View.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitSize->AddChild(View.Portrait); Row(Main, PortraitSize, false, 0);
    UVerticalBox* Detail = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Main, Detail, true, 12);
    View.Name = Text(WidgetTree, TEXT(""), 19, White, true); View.Name->SetAutoWrapText(false); View.Name->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); Add(Detail, View.Name, 1);
    View.Status = Text(WidgetTree, TEXT(""), 10, Mint, true); Add(Detail, View.Status, 1);
    View.Growth = Text(WidgetTree, TEXT(""), 12, Muted); Add(Detail, View.Growth, 3);
    View.Experience = Text(WidgetTree, TEXT(""), 11, Gold); Add(Detail, View.Experience, 1); View.XPBar = Meter(WidgetTree, Detail, Gold);
    USizeBox* ActionSize = WidgetTree->ConstructWidget<USizeBox>(); ActionSize->SetWidthOverride(156); Row(Main, ActionSize, false, 0);
    UVerticalBox* Actions = WidgetTree->ConstructWidget<UVerticalBox>(); ActionSize->AddChild(Actions);
    View.Residence = Button(TEXT(""), TEXT(""), Mint); Add(Actions, View.Residence, 3);
    View.Inspect = Button(TEXT("EVOLUTION / DETAILS"), TEXT(""), Cyan); Add(Actions, View.Inspect, 3);
    ResidentCards.Add(View);
}

void UDigimonVenomNXTFarmWidget::BuildWorldOverlay()
{
    using namespace DigimonFarmUI;
    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>(); Root->SetVisibility(ESlateVisibility::SelfHitTestInvisible); WidgetTree->RootWidget = Root;
    // Scale the complete care panel down on smaller viewports; never stretch portraits or text.
    UScaleBox* Responsive = WidgetTree->ConstructWidget<UScaleBox>(); Responsive->SetStretch(EStretch::ScaleToFit); Responsive->SetStretchDirection(EStretchDirection::DownOnly);
    Responsive->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    if (UOverlaySlot* PanelSlot = Root->AddChildToOverlay(Responsive)) { PanelSlot->SetHorizontalAlignment(HAlign_Right); PanelSlot->SetVerticalAlignment(VAlign_Fill); PanelSlot->SetPadding(FMargin(12, 16, 18, 64)); }
    USizeBox* PanelSize = WidgetTree->ConstructWidget<USizeBox>(); PanelSize->SetWidthOverride(360); PanelSize->SetHeightOverride(810); Responsive->AddChild(PanelSize);
    UBorder* CarePanel = Card(WidgetTree, Mint); CarePanel->SetPadding(FMargin(14)); PanelSize->AddChild(CarePanel);
    UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); CarePanel->SetContent(Body);
    Add(Body, Text(WidgetTree, TEXT("PRIVATE DIGIFARM"), 20, Mint, true), 0);
    Summary = Text(WidgetTree, TEXT(""), 11, White, true); Add(Body, Summary, 2);
    Add(Body, Text(WidgetTree, TEXT("WASD / arrows · move    Wheel · zoom\nClick a resident nameplate to care for them."), 10, Muted), 4);
    UHorizontalBox* TopActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, TopActions, 4);
    Row(TopActions, Button(TEXT("RESIDENTS"), TEXT("farmmanage"), Cyan));
    Row(TopActions, Button(TEXT("SHOP"), TEXT("farmshop"), Gold));
    Row(TopActions, Button(TEXT("LEAVE"), TEXT("farmleave"), Muted));
    Supplies = Text(WidgetTree, TEXT(""), 11, Gold); Add(Body, Supplies, 3);
    UHorizontalBox* Selector = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, Selector, 4);
    Previous = Button(TEXT("‹"), TEXT("farmselectstep"), Cyan, -1); Row(Selector, Previous, false, 0);
    PageLabel = Text(WidgetTree, TEXT("SELECT A RESIDENT"), 11, White, true); PageLabel->SetJustification(ETextJustify::Center); Row(Selector, PageLabel);
    Next = Button(TEXT("›"), TEXT("farmselectstep"), Cyan, 1); Row(Selector, Next, false, 0);
    EmptyMessage = Text(WidgetTree, TEXT("Your island is ready for its first resident. Open RESIDENTS, choose AVAILABLE COLLECTION and place a Digimon here."), 13, Muted); Add(Body, EmptyMessage, 10);
    CareBody = WidgetTree->ConstructWidget<UVerticalBox>(); Add(Body, CareBody, 1);
    UHorizontalBox* Identity = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(CareBody, Identity, 4);
    USizeBox* PortraitSize = WidgetTree->ConstructWidget<USizeBox>(); PortraitSize->SetWidthOverride(82); PortraitSize->SetHeightOverride(92);
    SelectedPortrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitSize->AddChild(SelectedPortrait); Row(Identity, PortraitSize, false, 0);
    UVerticalBox* IdentityText = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Identity, IdentityText, true, 8);
    SelectedName = Text(WidgetTree, TEXT(""), 17, White, true); SelectedName->SetAutoWrapText(false); SelectedName->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); Add(IdentityText, SelectedName, 1);
    SelectedGrowth = Text(WidgetTree, TEXT(""), 12, Mint, true); Add(IdentityText, SelectedGrowth, 3);
    SelectedStats = Text(WidgetTree, TEXT(""), 10, Muted); Add(IdentityText, SelectedStats, 2);
    SelectedXP = Text(WidgetTree, TEXT(""), 10, Gold); Add(CareBody, SelectedXP, 1); SelectedXPBar = Meter(WidgetTree, CareBody, Gold);
    UHorizontalBox* FeedRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(CareBody, FeedRow, 5);
    FeedCAM = Button(TEXT("CAM DIGIMEAT"), TEXT("farmfeed"), Mint, 0); Row(FeedRow, FeedCAM);
    FeedABI = Button(TEXT("ABI DIGIMEAT"), TEXT("farmfeed"), Violet, 1); Row(FeedRow, FeedABI);
    Add(CareBody, Text(WidgetTree, TEXT("PERMANENT STAT TRAINING"), 11, Cyan, true), 5);
    TrainingText = Text(WidgetTree, TEXT(""), 11, Muted); Add(CareBody, TrainingText, 1); TrainingBar = Meter(WidgetTree, CareBody, Violet);
    const TCHAR* Labels[] = { TEXT("HP"), TEXT("SP"), TEXT("ATK"), TEXT("DEF"), TEXT("INT"), TEXT("SPD") };
    // Six rows keep the stat and the exact +1/+5 food adjacent. Every button
    // names its actual inventory item; there is no interchangeable training food.
    for (int32 Stat = 0; Stat < 6; ++Stat)
    {
        UHorizontalBox* TrainingRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(CareBody, TrainingRow, 2);
        Row(TrainingRow, Text(WidgetTree, Labels[Stat], 11, White, true), false, 4);
        for (int32 Tier = 0; Tier < 2; ++Tier)
        {
            UDigimonVenomNXTActionButton* Train = Button(Tier == 0 ? TEXT("+1") : TEXT("+5"), TEXT("farmtrain"), Violet, Stat * 2 + Tier);
            Row(TrainingRow, Train, true, 2); TrainingButtons.Add(Train);
        }
    }
    Add(CareBody, Text(WidgetTree, TEXT("One matching DigiMeat per feed. Permanent training is capped at +100 per stat and +300 total. No credits are spent when feeding."), 11, Muted), 4);
}

void UDigimonVenomNXTFarmWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data)
{
    BuildLayout(); CachedPlayerState = PlayerState; CachedData = Data;
    if (!PlayerState || !Data) return;
    using namespace DigimonFarmUI;
    const auto& Profile = PlayerState->Profile;
    const auto* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 Residents = Profile.DigiFarmResidents.Num();
    const int32 Capacity = FMath::Max(0, Settings->MaxFarmResidents);
    Set(Summary, FString::Printf(TEXT("%s's island  ·  %d / %d residents"), *Profile.Username, Residents, Capacity));
    Set(Supplies, FString::Printf(TEXT("CAM DigiMeat %d   ·   ABI DigiMeat %d"), PlayerState->GetInventoryQuantity(TEXT("digimeat_cam")), PlayerState->GetInventoryQuantity(TEXT("digimeat_abi"))));
    if (bWorldOverlay) { RefreshSelection(); return; }
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bInside = PC && PC->IsInDigiFarm();
    const bool bLocked = PlayerState->HasActiveBattle();
    Set(Cast<UTextBlock>(Enter->GetContent()), bInside ? TEXT("RETURN TO YOUR ISLAND") : TEXT("ENTER YOUR ISLAND"));
    const bool bIslandReady = !bInside || (PC->GetDigiFarmScene() && PC->GetDigiFarmScene()->IsPresentationReady());
    Enter->SetIsEnabled(!bLocked && bIslandReady);
    Enter->SetToolTipText(FText::FromString(!bIslandReady ? TEXT("The island could not be loaded. Use LEAVE FARM to return safely and let the host know.") : TEXT("Explore your private island and care for its residents.")));
    Leave->SetVisibility(bInside ? ESlateVisibility::Visible : ESlateVisibility::Collapsed); Leave->SetIsEnabled(!bLocked);
    Leave->SetToolTipText(FText::FromString(TEXT("Save your farm position and return to your previous habitat. If a save fails, this button lets you retry safely.")));
    DigimonVenomNXTUI::StyleButton(ResidentsTab, Mint, Filter == 0); DigimonVenomNXTUI::StyleButton(CollectionTab, Cyan, Filter == 1);
    TArray<FGuid> VisibleIds;
    if (Filter == 0)
    {
        for (const FGuid& Id : Profile.DigiFarmResidents) { FDigimonOwnedPartner P; if (PlayerState->GetPartner(Id, P)) VisibleIds.AddUnique(Id); }
    }
    else
    {
        for (const FDigimonOwnedPartner& P : Profile.Collection) if (!Profile.DigiFarmResidents.Contains(P.InstanceId)) VisibleIds.AddUnique(P.InstanceId);
    }
    PageCount = FMath::Max(1, FMath::DivideAndRoundUp(VisibleIds.Num(), PageSize)); PageIndex = FMath::Clamp(PageIndex, 0, PageCount - 1);
    Set(PageLabel, FString::Printf(TEXT("PAGE %d / %d  ·  %d PARTNERS"), PageIndex + 1, PageCount, VisibleIds.Num()));
    Previous->SetIsEnabled(PageIndex > 0); Next->SetIsEnabled(PageIndex + 1 < PageCount);
    EmptyMessage->SetVisibility(VisibleIds.IsEmpty() ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
    Set(EmptyMessage, Filter == 0 ? TEXT("Your island has room to grow. Open AVAILABLE COLLECTION to place your first resident, then enter your farm to meet and feed them.") : TEXT("All of your collected partners already live on this island. Materialize more Digimon to expand your resident collection."));
    for (int32 Index = 0; Index < ResidentCards.Num(); ++Index)
    {
        auto& View = ResidentCards[Index]; const int32 CollectionIndex = PageIndex * PageSize + Index;
        FDigimonOwnedPartner Partner; const bool bPresent = VisibleIds.IsValidIndex(CollectionIndex) && PlayerState->GetPartner(VisibleIds[CollectionIndex], Partner);
        View.Card->SetVisibility(bPresent ? ESlateVisibility::Visible : ESlateVisibility::Collapsed); if (!bPresent) continue;
        const bool bResident = Profile.DigiFarmResidents.Contains(Partner.InstanceId);
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        View.Portrait->SetDigimon(Partner.SpeciesId, Partner.Variant); Set(View.Name, Unit.DisplayName); View.Name->SetToolTipText(FText::FromString(Unit.DisplayName));
        Set(View.Status, FString::Printf(TEXT("%s  ·  %s%s"), *DigimonVenomNXTUI::VarietyLabel(Partner.Variant), bResident ? TEXT("ISLAND RESIDENT") : TEXT("READY TO PLACE"), Profile.Party.Contains(Partner.InstanceId) ? TEXT("  ·  IN YOUR PARTY") : TEXT("  ·  COLLECTION")));
        View.Status->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
        Set(View.Growth, FString::Printf(TEXT("CAM %d / 100  ·  ABI %d / %d  ·  Training %.1f / %d"), Partner.CAM, Partner.ABI, DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI), DigimonVenomNXTEvolution::TrainingUsed(Partner), DigimonVenomNXTEvolution::TrainingCapacity(Partner)));
        Set(View.Experience, XPText(Partner)); const auto Progress = DigimonVenomNXTProgressionCore::GetProgress(Partner.Level, Partner.Experience, Settings->MaxPartnerLevel); View.XPBar->SetPercent(static_cast<float>(Progress.Fraction));
        Set(Cast<UTextBlock>(View.Residence->GetContent()), bResident ? TEXT("REMOVE RESIDENT") : TEXT("PLACE ON ISLAND"));
        View.Residence->InitializeAction((bResident ? TEXT("farmremove:") : TEXT("farmadd:")) + Partner.InstanceId.ToString()); View.Residence->SetIsEnabled(!bLocked && (bResident || Residents < Capacity));
        View.Residence->SetToolTipText(FText::FromString(bLocked ? TEXT("Finish the active battle before changing residents.") : bResident ? TEXT("Return this resident to your collection. Your partner and its stats are kept.") : Residents >= Capacity ? TEXT("Your island is full. Remove a resident to free a space.") : TEXT("Place this partner on your private island. Its party slot is kept.")));
        View.Inspect->InitializeAction(TEXT("inspectpartner:") + Partner.InstanceId.ToString());
    }
}

void UDigimonVenomNXTFarmWidget::RefreshSelection()
{
    ADigimonVenomNXTPlayerState* PS = CachedPlayerState.Get(); UDigimonVenomNXTDataSubsystem* Data = CachedData.Get();
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    if (!PS || !Data || !PC || !bWorldOverlay) return;
    using namespace DigimonFarmUI;
    ADigimonVenomNXTFarmScene* Scene = PC->GetDigiFarmScene();
    if (Scene) SelectedResident = Scene->GetSelectedResident();
    if (!PS->Profile.DigiFarmResidents.Contains(SelectedResident))
    {
        SelectedResident = PS->Profile.DigiFarmResidents.IsEmpty() ? FGuid() : PS->Profile.DigiFarmResidents[0];
        if (Scene) Scene->SelectResident(SelectedResident);
    }
    FDigimonOwnedPartner Partner;
    const bool bSelected = SelectedResident.IsValid() && PS->GetPartner(SelectedResident, Partner);
    CareBody->SetVisibility(bSelected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
    EmptyMessage->SetVisibility(bSelected ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
    Previous->SetIsEnabled(PS->Profile.DigiFarmResidents.Num() > 1); Next->SetIsEnabled(PS->Profile.DigiFarmResidents.Num() > 1);
    Set(PageLabel, bSelected ? FString::Printf(TEXT("RESIDENT %d / %d"), PS->Profile.DigiFarmResidents.IndexOfByKey(SelectedResident) + 1, PS->Profile.DigiFarmResidents.Num()) : TEXT("NO RESIDENTS YET"));
    if (!bSelected) return;
    const auto* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
    SelectedPortrait->SetDigimon(Partner.SpeciesId, Partner.Variant); Set(SelectedName, Unit.DisplayName); SelectedName->SetToolTipText(FText::FromString(Unit.DisplayName));
    Set(SelectedGrowth, FString::Printf(TEXT("%s  ·  LV. %d\nCAM %d  ·  ABI %d / %d"), *DigimonVenomNXTUI::VarietyLabel(Partner.Variant), Partner.Level, Partner.CAM, Partner.ABI, DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI)));
    SelectedGrowth->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
    SelectedStats->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::StatHelp()));
    Set(SelectedStats, FString::Printf(TEXT("HP %d/%d  ·  SP %d/%d\nATK %d  DEF %d  INT %d  SPD %d"), Unit.HP, Unit.Stats.MaxHP, Unit.SP, Unit.Stats.MaxSP, Unit.Stats.Attack, Unit.Stats.Defense, Unit.Stats.Spirit, Unit.Stats.Speed));
    Set(SelectedXP, XPText(Partner)); const auto Progress = DigimonVenomNXTProgressionCore::GetProgress(Partner.Level, Partner.Experience, Settings->MaxPartnerLevel); SelectedXPBar->SetPercent(static_cast<float>(Progress.Fraction));
    const bool bCanFeed = PC->IsInDigiFarm() && !PS->HasActiveBattle();
    const int32 CAMCount = PS->GetInventoryQuantity(TEXT("digimeat_cam")); const int32 ABICount = PS->GetInventoryQuantity(TEXT("digimeat_abi"));
    Set(Cast<UTextBlock>(FeedCAM->GetContent()), FString::Printf(TEXT("CAM +%d  ·  %d meat"), Settings->CAMMeatGain, CAMCount));
    Set(Cast<UTextBlock>(FeedABI->GetContent()), FString::Printf(TEXT("ABI +%d  ·  %d meat"), Settings->ABIMeatGain, ABICount));
    FeedCAM->SetIsEnabled(bCanFeed && CAMCount > 0 && Partner.CAM < 100); FeedABI->SetIsEnabled(bCanFeed && ABICount > 0 && Partner.ABI < DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI));
    FeedCAM->SetToolTipText(FText::FromString(Partner.CAM >= 100 ? TEXT("Friendship is already at maximum.") : CAMCount == 0 ? TEXT("Buy CAM DigiMeat from the shop first.") : TEXT("Feed one CAM DigiMeat to increase this resident's friendship.")));
    FeedABI->SetToolTipText(FText::FromString(Partner.ABI >= DigimonVenomNXTEvolutionCore::MaximumABI(Settings->MaxABI) ? TEXT("Permanent ABI is already at maximum.") : ABICount == 0 ? TEXT("Buy ABI DigiMeat from the shop first.") : TEXT("Feed one ABI DigiMeat for permanent ABI and advanced evolution requirements.")));
    const float Used = DigimonVenomNXTEvolution::TrainingUsed(Partner); const int32 Capacity = DigimonVenomNXTEvolution::TrainingCapacity(Partner);
    TrainingBar->SetPercent(Capacity > 0 ? FMath::Clamp(Used / Capacity, 0.0f, 1.0f) : 1.0f);
    Set(TrainingText, FString::Printf(TEXT("%.0f / %d total points  ·  +100 maximum per stat"), Used, Capacity));
    const TCHAR* StatKeys[] = { TEXT("hp"), TEXT("sp"), TEXT("atk"), TEXT("def"), TEXT("int"), TEXT("spd") };
    for (int32 Index = 0; Index < TrainingButtons.Num(); ++Index)
    {
        const int32 Stat = Index / 2;
        const int32 Amount = Index % 2 == 0 ? 1 : 5;
        const FName ItemId(*FString::Printf(TEXT("digimeat_%s_%d"), StatKeys[Stat], Amount));
        const int32 Count = PS->GetInventoryQuantity(ItemId);
        const bool bRoom = DigimonVenomNXTEvolution::CanTrain(Partner, static_cast<EDigimonTrainingStat>(Stat), Amount);
        Set(Cast<UTextBlock>(TrainingButtons[Index]->GetContent()), FString::Printf(TEXT("+%d  ·  %d owned"), Amount, Count));
        TrainingButtons[Index]->SetIsEnabled(bCanFeed && Count > 0 && bRoom);
        TrainingButtons[Index]->SetToolTipText(FText::FromString(!bRoom ? TEXT("This feed would exceed the +100 stat or +300 total training limit.") : Count == 0 ? TEXT("Buy this stat's matching DigiMeat from the shop first.") : FString::Printf(TEXT("Use one %s for +%d permanent training."), *ItemId.ToString(), Amount)));
    }
}

void UDigimonVenomNXTFarmWidget::RefreshCurrent()
{
    RefreshFromProfile(CachedPlayerState.Get(), CachedData.Get());
}

void UDigimonVenomNXTFarmWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!bWorldOverlay) return;
    SelectionAccumulator += InDeltaTime;
    if (SelectionAccumulator < 0.1f) return;
    SelectionAccumulator = 0.0f;
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    if (PC && PC->GetDigiFarmScene() && PC->GetDigiFarmScene()->GetSelectedResident() != SelectedResident) RefreshSelection();
}

void UDigimonVenomNXTFarmWidget::HandleAction(const FString& Action, int32 Payload)
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS = CachedPlayerState.Get();
    if (Action == TEXT("farmfilter")) { Filter = FMath::Clamp(Payload, 0, 1); PageIndex = 0; RefreshCurrent(); return; }
    if (Action == TEXT("farmpage")) { PageIndex = FMath::Clamp(PageIndex + Payload, 0, PageCount - 1); RefreshCurrent(); return; }
    if (Action == TEXT("farmselectstep"))
    {
        if (!PS || !PC || !PC->IsInDigiFarm() || PS->Profile.DigiFarmResidents.IsEmpty()) return;
        const int32 Count = PS->Profile.DigiFarmResidents.Num(); const int32 Current = PS->Profile.DigiFarmResidents.IndexOfByKey(SelectedResident);
        SelectedResident = PS->Profile.DigiFarmResidents[(FMath::Max(Current, 0) + (Payload < 0 ? Count - 1 : 1)) % Count];
        if (ADigimonVenomNXTFarmScene* Scene = PC->GetDigiFarmScene()) Scene->SelectResident(SelectedResident);
        RefreshSelection(); return;
    }
    if (Action == TEXT("farmfeed") || Action == TEXT("farmtrain"))
    {
        // Read the selected GUID at the click, not from a stale card index. Authority validates
        // island presence, collection ownership, residence, inventory and training capacity.
        if (!PS || !PC || !PC->IsInDigiFarm() || PS->HasActiveBattle()) return;
        if (ADigimonVenomNXTFarmScene* Scene = PC->GetDigiFarmScene()) SelectedResident = Scene->GetSelectedResident();
        if (!PS->Profile.DigiFarmResidents.Contains(SelectedResident)) return;
        if (Action == TEXT("farmtrain") && Payload >= 0 && Payload < 12)
        {
            const TCHAR* StatKeys[] = { TEXT("hp"), TEXT("sp"), TEXT("atk"), TEXT("def"), TEXT("int"), TEXT("spd") };
            const int32 Stat = Payload / 2;
            const int32 Amount = Payload % 2 == 0 ? 1 : 5;
            PS->ServerFeedFarmResident(SelectedResident, FName(*FString::Printf(TEXT("digimeat_%s_%d"), StatKeys[Stat], Amount)), static_cast<EDigimonTrainingStat>(Stat));
        }
        else if (Action == TEXT("farmfeed")) PS->ServerFeedFarmResident(SelectedResident, Payload == 0 ? FName(TEXT("digimeat_cam")) : FName(TEXT("digimeat_abi")), EDigimonTrainingStat::MaxHP);
        return;
    }
    OnAction.Broadcast(Action, Payload);
}
