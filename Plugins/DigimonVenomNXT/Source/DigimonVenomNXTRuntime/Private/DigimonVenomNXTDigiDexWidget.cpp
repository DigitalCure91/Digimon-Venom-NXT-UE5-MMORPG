#include "DigimonVenomNXTDigiDexWidget.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTScanCore.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "HAL/PlatformTime.h"

namespace DigimonDigiDexUI
{
    constexpr int32 PageSize = 12;
    const FLinearColor Ink(0.009f, 0.021f, 0.040f, 1.0f);
    const FLinearColor Panel(0.023f, 0.052f, 0.079f, 1.0f);
    const FLinearColor Cyan(0.28f, 0.82f, 1.0f, 1.0f);
    const FLinearColor Gold(1.0f, 0.74f, 0.25f, 1.0f);
    const FLinearColor Violet(0.76f, 0.57f, 1.0f, 1.0f);
    const FLinearColor White(0.92f, 0.97f, 1.0f, 1.0f);
    const FLinearColor Muted(0.61f, 0.74f, 0.83f, 1.0f);
    const FLinearColor Ready(0.43f, 0.95f, 0.73f, 1.0f);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 12, FLinearColor Color = White, bool bBold = false)
    {
        UTextBlock* Widget = Tree->ConstructWidget<UTextBlock>();
        Widget->SetText(FText::FromString(Value)); Widget->SetColorAndOpacity(Color); Widget->SetAutoWrapText(true);
        FSlateFontInfo Font = Widget->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Widget->SetFont(Font);
        return Widget;
    }
    void Set(UTextBlock* Widget, const FString& Value)
    {
        if (Widget && Widget->GetText().ToString() != Value) Widget->SetText(FText::FromString(Value));
    }
    void Add(UVerticalBox* Box, UWidget* Widget, float Padding = 3.0f)
    {
        if (UVerticalBoxSlot* ChildSlot = Box->AddChildToVerticalBox(Widget))
        {
            ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        }
    }
    void Row(UHorizontalBox* Box, UWidget* Widget, bool bFill = true, float Padding = 4.0f)
    {
        if (UHorizontalBoxSlot* ChildSlot = Box->AddChildToHorizontalBox(Widget))
        {
            ChildSlot->SetPadding(FMargin(Padding, 0)); ChildSlot->SetVerticalAlignment(VAlign_Center);
            if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
    void Weight(UWidget* Widget, float Value)
    {
        if (UHorizontalBoxSlot* ChildSlot = Cast<UHorizontalBoxSlot>(Widget ? Widget->Slot : nullptr))
        {
            FSlateChildSize Size(ESlateSizeRule::Fill); Size.Value = FMath::Max(0.0001f, Value); ChildSlot->SetSize(Size);
        }
    }
    UBorder* PanelBox(UWidgetTree* Tree, FLinearColor Accent = Cyan, float Padding = 12)
    {
        UBorder* Border = Tree->ConstructWidget<UBorder>();
        Border->SetBrush(FSlateRoundedBoxBrush(Panel, 5.0f, Accent.CopyWithNewOpacity(0.36f), 1.0f));
        Border->SetPadding(FMargin(Padding)); return Border;
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
    FLinearColor Accent(EDigimonVariant Value)
    {
        return DigimonVenomNXTUI::VarietyAccent(Value);
    }
    FString FormName(const FDigimonSpeciesDefinition& Species, EDigimonVariant Value)
    {
        const FString Name = Species.DisplayName.IsEmpty() ? Species.SpeciesId.ToString() : Species.DisplayName.ToString();
        return Value == EDigimonVariant::Paradox ? TEXT("Paradox ") + Name : Value == EDigimonVariant::Shiny ? TEXT("Shiny ") + Name : Value == EDigimonVariant::Firewall ? TEXT("Firewall ") + Name : Name;
    }
    FString Key(FName SpeciesId, EDigimonVariant Value)
    {
        return FString::Printf(TEXT("%s:%d"), *SpeciesId.ToString(), static_cast<int32>(Value)).ToLower();
    }

    struct FHabitatResearch
    {
        FString Summary;
        FString Details;
    };

    FHabitatResearch FirewallHabitats(UDigimonVenomNXTDataSubsystem* Data, FName SpeciesId)
    {
        // Registries are loaded once per game instance. Cache the small display
        // strings, not the full map rows (which also contain collision grids).
        // Repeated profile, selection and battle-lock refreshes never rescan maps.
        static TWeakObjectPtr<UDigimonVenomNXTDataSubsystem> HabitatData;
        static TMap<FName, FHabitatResearch> HabitatRecords;
        if (!Data) return { TEXT("PUBLIC HABITATS  /  Waiting for the world catalogue."), FString() };
        if (HabitatData.Get() != Data)
        {
            HabitatData = Data;
            HabitatRecords.Reset();
            TMap<FName, TArray<FString>> LocationsBySpecies;
            // GetAllMaps returns the actual public registry in ascending map order.
            for (const FDigimonMapRow& Habitat : Data->GetAllMaps())
            {
                const FString MapName = Habitat.DisplayName.IsEmpty() ? FString::Printf(TEXT("Habitat %03d"), Habitat.MapId) : Habitat.DisplayName.ToString();
                const int32 LowestLevel = FMath::Max(1, Habitat.RecommendedMinLevel);
                const int32 HighestLevel = FMath::Max(LowestLevel, Habitat.RecommendedMaxLevel);
                const FString Location = FString::Printf(TEXT("%03d  ·  %s  ·  Lv.%d–%d"), Habitat.MapId, *MapName, LowestLevel, HighestLevel);
                for (FName WildSpeciesId : Habitat.WildSpecies) LocationsBySpecies.FindOrAdd(WildSpeciesId).AddUnique(Location);
            }
            for (const auto& Pair : LocationsBySpecies)
            {
                FHabitatResearch Research;
                Research.Summary = TEXT("PUBLIC HABITATS  /  Find these maps in Level Select");
                const int32 VisibleLocations = FMath::Min(3, Pair.Value.Num());
                for (int32 LocationIndex = 0; LocationIndex < VisibleLocations; ++LocationIndex) Research.Summary += TEXT("\n") + Pair.Value[LocationIndex];
                if (Pair.Value.Num() > VisibleLocations) Research.Summary += FString::Printf(TEXT("\n+%d more habitats — hover here for the full list."), Pair.Value.Num() - VisibleLocations);
                Research.Details = TEXT("PUBLIC WILD HABITATS\n") + FString::Join(Pair.Value, TEXT("\n")) + TEXT("\nLevel ranges follow the world catalogue. Firewall encounters use this world's configured variety chance.");
                HabitatRecords.Add(Pair.Key, MoveTemp(Research));
            }
        }
        if (const FHabitatResearch* Research = HabitatRecords.Find(SpeciesId)) return *Research;
        return { TEXT("PUBLIC HABITATS  /  This form is not listed in this world's wild pools. Check its evolution and de-evolution routes for another way to obtain it."), FString() };
    }
}

TSharedRef<SWidget> UDigimonVenomNXTDigiDexWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTDigiDexWidget::Button(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload)
{
    UDigimonVenomNXTActionButton* Widget = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(Widget, Accent); Widget->InitializeAction(Action, Payload);
    FButtonStyle Style = Widget->GetStyle(); Style.SetNormalPadding(FMargin(9, 8)); Style.SetPressedPadding(FMargin(9, 9, 9, 7)); Widget->SetStyle(Style);
    Widget->OnAction.AddDynamic(this, &UDigimonVenomNXTDigiDexWidget::HandleAction);
    UTextBlock* Caption = DigimonDigiDexUI::Text(WidgetTree, Label, 11, DigimonDigiDexUI::White, true);
    Caption->SetJustification(ETextJustify::Center); Widget->SetContent(Caption); return Widget;
}

void UDigimonVenomNXTDigiDexWidget::BuildLayout()
{
    if (Root) return;
    using namespace DigimonDigiDexUI;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("DigiDexWidgetTree"));
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;

    UBorder* Hero = PanelBox(WidgetTree, Cyan, 18);
    Hero->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.019f, 0.049f, 0.095f, 1), 7, Cyan.CopyWithNewOpacity(0.75f), 1)); Add(Root, Hero, 3);
    UVerticalBox* HeroBody = WidgetTree->ConstructWidget<UVerticalBox>(); Hero->SetContent(HeroBody);
    Add(HeroBody, Text(WidgetTree, TEXT("DIGIDEX  /  SPECIES LIBRARY"), 10, Cyan, true), 1);
    Add(HeroBody, Text(WidgetTree, TEXT("Every form. A new possibility."), 27, White, true), 5);
    Subtitle = Text(WidgetTree, TEXT("Your account's field research, collection and next partner — together in one place."), 12, Muted); Add(HeroBody, Subtitle, 2);
    Rules = Text(WidgetTree, TEXT("100% unlocks materialization. 200% awards 5 permanent ABI. Each variety has its own scan data."), 12, Gold, true); Add(HeroBody, Rules, 3);
    Add(HeroBody, Text(WidgetTree, TEXT("CAMPAIGN RESEARCH  /  Complete Dawn Story for Firewall, World DS for Paradox, and Super Xros Wars for Shiny scan bonuses. Each reward adds 20 percentage points to matching wild victories at default settings."), 12, Accent(EDigimonVariant::Firewall)), 3);
    UHorizontalBox* TotalRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody, TotalRow, 7);
    const TCHAR* TotalNames[] = {TEXT("CATALOGUE"), TEXT("DISCOVERED"), TEXT("EVER OWNED"), TEXT("READY")};
    for (int32 Index = 0; Index < 4; ++Index)
    {
        UBorder* TotalPanel = PanelBox(WidgetTree, Index == 3 ? Ready : Cyan, 9); Row(TotalRow, TotalPanel);
        TotalPanel->SetBrush(FSlateRoundedBoxBrush(Ink, 4));
        UVerticalBox* TotalBody = WidgetTree->ConstructWidget<UVerticalBox>(); TotalPanel->SetContent(TotalBody);
        UTextBlock* Number = Text(WidgetTree, TEXT("—"), 21, Index == 3 ? Ready : White, true); Add(TotalBody, Number, 0); Totals.Add(Number);
        Add(TotalBody, Text(WidgetTree, TotalNames[Index], 9, Muted, true), 1);
    }

    UHorizontalBox* Tabs = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Tabs, 6);
    const TCHAR* TabNames[] = {TEXT("ALL FORMS"), TEXT("DISCOVERED"), TEXT("OWNED"), TEXT("READY")};
    for (int32 Index = 0; Index < 4; ++Index)
    {
        UDigimonVenomNXTActionButton* Tab = Button(TabNames[Index], TEXT("dexview"), Cyan, Index); Row(Tabs, Tab); ViewTabs.Add(Tab);
    }
    UBorder* SearchPanel = PanelBox(WidgetTree, Cyan, 8); Add(Root, SearchPanel, 3);
    UVerticalBox* SearchBody = WidgetTree->ConstructWidget<UVerticalBox>(); SearchPanel->SetContent(SearchBody);
    SearchBox = WidgetTree->ConstructWidget<UEditableTextBox>();
    DigimonVenomNXTUI::StyleInput(SearchBox); SearchBox->SetHintText(FText::FromString(TEXT("Search name, type, element, role, stage or variety...")));
    SearchBox->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTDigiDexWidget::HandleSearchChanged); Add(SearchBody, SearchBox, 2);
    UHorizontalBox* Filters = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(SearchBody, Filters, 4);
    StageButton = Button(TEXT("ALL STAGES  >"), TEXT("dexstage"), Cyan); Row(Filters, StageButton);
    StageButton->SetToolTipText(FText::FromString(TEXT("Click to cycle the evolution stages present in this catalogue.")));
    VariantButton = Button(TEXT("ALL VARIETIES  >"), TEXT("dexvariant"), Violet); Row(Filters, VariantButton);
    VariantButton->SetToolTipText(FText::FromString(TEXT("Click to cycle All Varieties, Normal, Paradox, Shiny and Firewall. Each form keeps its own research progress.")));
    SortButton = Button(TEXT("SCAN FIRST  >"), TEXT("dexsort"), Cyan); Row(Filters, SortButton);
    SortButton->SetToolTipText(FText::FromString(TEXT("Click to sort by scan data, name or evolution stage.")));
    Row(Filters, Button(TEXT("RESET FILTERS"), TEXT("dexreset"), Muted));
    ResultLabel = Text(WidgetTree, TEXT("Loading your species library..."), 11, Muted); Add(Root, ResultLabel, 4);
    Status = Text(WidgetTree, TEXT(""), 12, Gold, true); Status->SetVisibility(ESlateVisibility::Collapsed); Add(Root, Status, 2);

    RecordPanel = PanelBox(WidgetTree, Gold, 14); RecordPanel->SetVisibility(ESlateVisibility::Collapsed); Add(Root, RecordPanel, 5);
    UVerticalBox* RecordBody = WidgetTree->ConstructWidget<UVerticalBox>(); RecordPanel->SetContent(RecordBody);
    UHorizontalBox* RecordHeading = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(RecordBody, RecordHeading, 0);
    RecordTitle = Text(WidgetTree, TEXT(""), 21, White, true); Row(RecordHeading, RecordTitle);
    Row(RecordHeading, Button(TEXT("CLOSE RECORD"), TEXT("dexclose"), Muted), false);
    UTextBlock* RecordTypeText = nullptr; UTextBlock* RecordElementText = nullptr;
    Add(RecordBody, DigimonVenomNXTCombatUI::TypeChips(WidgetTree, RecordTypeText, RecordElementText, 11), 4);
    RecordAffinity = RecordTypeText; RecordElement = RecordElementText;
    RecordStats = Text(WidgetTree, TEXT(""), 12, Muted); Add(RecordBody, RecordStats, 4);
    RecordRoutes = Text(WidgetTree, TEXT(""), 12, Cyan); Add(RecordBody, RecordRoutes, 3);
    RecordProgress = Text(WidgetTree, TEXT(""), 12, Muted); Add(RecordBody, RecordProgress, 3);
    RecordPreview = Text(WidgetTree, TEXT(""), 13, Gold, true); Add(RecordBody, RecordPreview, 5);
    ConfirmButton = Button(TEXT("MATERIALIZE THIS FORM"), TEXT("dexconfirm"), Ready); Add(RecordBody, ConfirmButton, 3);
    Add(RecordBody, Text(WidgetTree, TEXT("Materialization adds a new level 1 partner. Your existing partners are unchanged. Evolution is managed in Partners / Evolution."), 11, Muted), 1);

    EmptyLabel = Text(WidgetTree, TEXT("No forms match these filters. Clear the search or reset filters to see the full catalogue."), 15, Muted); Add(Root, EmptyLabel, 12);
    Grid = WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Root, Grid, 0);
    for (int32 Index = 0; Index < PageSize; ++Index)
    {
        FDigimonDigiDexCardView View;
        View.Bounds = WidgetTree->ConstructWidget<USizeBox>(); View.Bounds->SetWidthOverride(235);
        View.Card = PanelBox(WidgetTree, Cyan, 11); View.Bounds->AddChild(View.Card);
        UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); View.Card->SetContent(Body);
        View.AccentLine = WidgetTree->ConstructWidget<UBorder>(); View.AccentLine->SetPadding(FMargin(0)); View.AccentLine->SetBrushColor(Cyan);
        USizeBox* AccentHeight = WidgetTree->ConstructWidget<USizeBox>(); AccentHeight->SetHeightOverride(2); AccentHeight->AddChild(View.AccentLine); Add(Body, AccentHeight, 0);
        UHorizontalBox* Tags = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, Tags, 6);
        View.Stage = Text(WidgetTree, TEXT(""), 9, Muted, true); Row(Tags, View.Stage, true, 0);
        View.Variant = Text(WidgetTree, TEXT(""), 9, Cyan, true); View.Variant->SetJustification(ETextJustify::Right); Row(Tags, View.Variant, true, 0);

        // A fixed square canvas and the shared ScaleToFit portrait preserve every sprite's proportions.
        USizeBox* PortraitBounds = WidgetTree->ConstructWidget<USizeBox>(); PortraitBounds->SetWidthOverride(124); PortraitBounds->SetHeightOverride(124);
        View.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitBounds->AddChild(View.Portrait);
        if (UVerticalBoxSlot* PortraitSlot = Body->AddChildToVerticalBox(PortraitBounds)) PortraitSlot->SetHorizontalAlignment(HAlign_Center);
        USizeBox* PlinthBounds = WidgetTree->ConstructWidget<USizeBox>(); PlinthBounds->SetHeightOverride(4);
        UBorder* Plinth = WidgetTree->ConstructWidget<UBorder>(); Plinth->SetBrush(FSlateRoundedBoxBrush(Ink, 4, Cyan.CopyWithNewOpacity(0.30f), 1)); Plinth->SetPadding(FMargin(0)); PlinthBounds->AddChild(Plinth); Add(Body, PlinthBounds, 1);
        USizeBox* NameBounds = WidgetTree->ConstructWidget<USizeBox>(); NameBounds->SetHeightOverride(41); NameBounds->SetClipping(EWidgetClipping::ClipToBounds);
        View.Name = Text(WidgetTree, TEXT(""), 14, White, true); View.Name->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); NameBounds->AddChild(View.Name); Add(Body, NameBounds, 4);
        UTextBlock* TypeText = nullptr; UTextBlock* ElementText = nullptr;
        Add(Body, DigimonVenomNXTCombatUI::TypeChips(WidgetTree, TypeText, ElementText, 9), 3);
        View.Affinity = TypeText; View.Element = ElementText;
        View.Scan = Text(WidgetTree, TEXT(""), 11, White, true); Add(Body, View.Scan, 2);

        USizeBox* MeterBounds = WidgetTree->ConstructWidget<USizeBox>(); MeterBounds->SetHeightOverride(12); Add(Body, MeterBounds, 2);
        UOverlay* MeterOverlay = WidgetTree->ConstructWidget<UOverlay>(); MeterBounds->AddChild(MeterOverlay);
        View.Meter = WidgetTree->ConstructWidget<UProgressBar>();
        FProgressBarStyle MeterStyle = View.Meter->GetWidgetStyle(); MeterStyle.SetBackgroundImage(FSlateRoundedBoxBrush(Ink, 3)); MeterStyle.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White, 3)); View.Meter->SetWidgetStyle(MeterStyle);
        if (UOverlaySlot* MeterSlot = MeterOverlay->AddChildToOverlay(View.Meter)) { MeterSlot->SetHorizontalAlignment(HAlign_Fill); MeterSlot->SetVerticalAlignment(VAlign_Fill); MeterSlot->SetPadding(FMargin(0, 3)); }
        View.ThresholdRow = WidgetTree->ConstructWidget<UHorizontalBox>(); View.ThresholdRow->SetVisibility(ESlateVisibility::HitTestInvisible);
        View.ThresholdBefore = WidgetTree->ConstructWidget<USizeBox>(); Row(View.ThresholdRow, View.ThresholdBefore, true, 0);
        USizeBox* MarkerBounds = WidgetTree->ConstructWidget<USizeBox>(); MarkerBounds->SetWidthOverride(2); MarkerBounds->SetHeightOverride(12);
        UBorder* Marker = WidgetTree->ConstructWidget<UBorder>(); Marker->SetPadding(FMargin(0)); Marker->SetBrushColor(White); MarkerBounds->AddChild(Marker); Row(View.ThresholdRow, MarkerBounds, false, 0);
        View.ThresholdAfter = WidgetTree->ConstructWidget<USizeBox>(); Row(View.ThresholdRow, View.ThresholdAfter, true, 0);
        if (UOverlaySlot* MarkerSlot = MeterOverlay->AddChildToOverlay(View.ThresholdRow)) { MarkerSlot->SetHorizontalAlignment(HAlign_Fill); MarkerSlot->SetVerticalAlignment(VAlign_Fill); }

        View.History = Text(WidgetTree, TEXT(""), 10, Muted); Add(Body, View.History, 2);
        View.Bonus = Text(WidgetTree, TEXT(""), 10, Gold); Add(Body, View.Bonus, 2);
        UHorizontalBox* Actions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, Actions, 4);
        View.Inspect = Button(TEXT("DETAILS"), TEXT("dexinspect"), Cyan); Row(Actions, View.Inspect, true, 1); Weight(View.Inspect, 0.36f);
        View.Materialize = Button(TEXT(""), TEXT("dexpreview"), Ready); Row(Actions, View.Materialize, true, 1); Weight(View.Materialize, 0.64f);
        if (UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(View.Bounds, Index / Columns, Index % Columns)) { GridSlot->SetHorizontalAlignment(HAlign_Fill); GridSlot->SetVerticalAlignment(VAlign_Fill); }
        Cards.Add(View);
    }

    UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, Pager, 8);
    Previous = Button(TEXT("<  PREVIOUS"), TEXT("dexpage"), Cyan, -1); Row(Pager, Previous, false);
    PageLabel = Text(WidgetTree, TEXT(""), 12, Muted, true); PageLabel->SetJustification(ETextJustify::Center); Row(Pager, PageLabel);
    Next = Button(TEXT("NEXT  >"), TEXT("dexpage"), Cyan, 1); Row(Pager, Next, false);
    Add(Root, Text(WidgetTree, TEXT("Discovery and ownership history stay in your account after materializing, evolving or moving partners. Scan data belongs to each species and variety separately."), 11, Muted), 4);
}

void UDigimonVenomNXTDigiDexWidget::BuildCatalogue()
{
    using namespace DigimonDigiDexUI;
    Entries.Reset(); FilteredEntries.Reset(); AvailableStages.Reset(); SpeciesCount = 0;
    if (!CachedData.IsValid()) return;
    TArray<FDigimonSpeciesDefinition> SpeciesList = CachedData->GetAllSpecies();
    SpeciesList.Sort([](const FDigimonSpeciesDefinition& A, const FDigimonSpeciesDefinition& B)
    {
        const int32 NameOrder = A.DisplayName.ToString().Compare(B.DisplayName.ToString(), ESearchCase::IgnoreCase);
        return NameOrder == 0 ? A.SpeciesId.LexicalLess(B.SpeciesId) : NameOrder < 0;
    });
    for (const auto& Species : SpeciesList)
    {
        if (Species.bPlaceholder || Species.SpeciesId.IsNone()) continue;
        bool bIncluded = false;
        for (int32 Variety = 0; Variety <= static_cast<int32>(EDigimonVariant::Firewall); ++Variety)
        {
            if (!DigimonVenomNXTScanCore::IsVariantAvailable(Variety, Species.bHasNormalArtwork, Species.bHasParadoxArtwork, Species.bHasShinyArtwork, Species.bHasFirewallArtwork)) continue;
            FEntry Entry; Entry.Species = Species; Entry.Variant = static_cast<EDigimonVariant>(Variety); Entry.Key = Key(Species.SpeciesId, Entry.Variant);
            Entry.Search = (Species.DisplayName.ToString() + TEXT(" ") + Species.SpeciesId.ToString() + TEXT(" ") + Stage(Species.Stage) + TEXT(" ") + Variant(Entry.Variant) + TEXT(" ") + DigimonVenomNXTCombatUI::Affinity(Species.Affinity) + TEXT(" ") + DigimonVenomNXTCombatUI::Element(Species.Element) + TEXT(" ") + Species.CombatRole).ToLower();
            Entries.Add(MoveTemp(Entry)); bIncluded = true;
        }
        if (bIncluded) { ++SpeciesCount; AvailableStages.AddUnique(static_cast<int32>(Species.Stage)); }
    }
    AvailableStages.Sort();
}

void UDigimonVenomNXTDigiDexWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data)
{
    BuildLayout();
    const bool bNewAccount = CachedPlayerState.Get() != PlayerState;
    const bool bNewCatalogue = CachedData.Get() != Data || Entries.IsEmpty();
    CachedPlayerState = PlayerState; CachedData = Data;
    if (!CachedPlayerState.IsValid() || !CachedData.IsValid()) return;
    if (bNewAccount) { SelectedEntry = INDEX_NONE; bConfirming = false; bRequestPending = false; Page = 0; }
    if (bNewCatalogue) { BuildCatalogue(); SelectedEntry = INDEX_NONE; }
    UpdateAccountProgress();
    if (bRequestPending && (CachedPlayerState->Profile.Collection.Num() != PendingCollectionCount || (Entries.IsValidIndex(PendingEntry) && Entries[PendingEntry].Scan != PendingScan)))
    {
        bRequestPending = false; bConfirming = false; DigimonDigiDexUI::Set(Status, TEXT("Account data refreshed. Your scan and collection totals are up to date."));
    }
    RefreshResults();
}

void UDigimonVenomNXTDigiDexWidget::UpdateAccountProgress()
{
    using namespace DigimonDigiDexUI;
    if (!CachedPlayerState.IsValid()) return;
    const auto& Policy = CachedPlayerState->ScanPolicy;
    TMap<FString, const FDigimonScanRecord*> Records;
    for (const auto& Scan : CachedPlayerState->Profile.Scans) Records.Add(Key(Scan.SpeciesId, Scan.Variant), &Scan);
    TMap<FString, int32> Owned;
    for (const auto& Partner : CachedPlayerState->Profile.Collection) ++Owned.FindOrAdd(Key(Partner.SpeciesId, Partner.Variant));
    int32 Discovered = 0, EverOwned = 0, ReadyCount = 0;
    for (auto& Entry : Entries)
    {
        const FDigimonScanRecord* const* Found = Records.Find(Entry.Key);
        const FDigimonScanRecord* Record = Found ? *Found : nullptr;
        const auto Preview = DigimonVenomNXTScanCore::Materialize(Record ? Record->Percent : 0, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
        Entry.Scan = Preview.ScanPercent;
        Entry.FractionalHundredths = Record && Entry.Scan < Preview.Cap ? FMath::Clamp(Record->FractionalHundredths, 0, 99) : 0;
        Entry.Peak = Record ? FMath::Max(Entry.Scan, Record->PeakPercent) : 0;
        Entry.Owned = Owned.FindRef(Entry.Key);
        Entry.bEverOwned = Entry.Owned > 0 || (Record && Record->bEverOwned);
        Entry.bDiscovered = Record != nullptr || Entry.bEverOwned;
        Entry.Materializations = Record ? Record->Materializations : 0;
        if (Entry.bDiscovered) ++Discovered;
        if (Entry.bEverOwned) ++EverOwned;
        if (Preview.Ready) ++ReadyCount;
    }
    const int32 Counts[] = {Entries.Num(), Discovered, EverOwned, ReadyCount};
    for (int32 Index = 0; Index < Totals.Num(); ++Index) Set(Totals[Index], FText::AsNumber(Counts[Index]).ToString());
    Set(Subtitle, FString::Printf(TEXT("%d species. %s forms. Your account's permanent research archive."), SpeciesCount, *FText::AsNumber(Entries.Num()).ToString()));
    const auto Limits = DigimonVenomNXTScanCore::Materialize(0, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
    Set(Rules, Limits.Cap >= 200
        ? FString::Printf(TEXT("%d%% unlocks materialization  /  200%% awards 5 permanent ABI  /  %d%% scan capacity"), Limits.Requirement, Limits.Cap)
        : FString::Printf(TEXT("%d%% unlocks materialization  /  server scan cap %d%%  /  up to +%d permanent ABI"), Limits.Requirement, Limits.Cap, DigimonVenomNXTScanCore::BonusABI(Limits.Cap)));
}

void UDigimonVenomNXTDigiDexWidget::RefreshResults()
{
    using namespace DigimonDigiDexUI;
    if (!CachedPlayerState.IsValid()) return;
    const auto& Policy = CachedPlayerState->ScanPolicy;
    TArray<FString> Terms; SearchTerm.ToLower().ParseIntoArrayWS(Terms);
    FilteredEntries.Reset();
    for (int32 Index = 0; Index < Entries.Num(); ++Index)
    {
        const auto& Entry = Entries[Index];
        if (StageFilter != INDEX_NONE && static_cast<int32>(Entry.Species.Stage) != StageFilter) continue;
        if (VariantFilter != INDEX_NONE && static_cast<int32>(Entry.Variant) != VariantFilter) continue;
        if (ViewFilter == 1 && !Entry.bDiscovered) continue;
        if (ViewFilter == 2 && Entry.Owned == 0) continue;
        if (ViewFilter == 3 && !DigimonVenomNXTScanCore::Materialize(Entry.Scan, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize).Ready) continue;
        bool bMatches = true;
        for (const auto& Term : Terms) if (!Entry.Search.Contains(Term)) { bMatches = false; break; }
        if (bMatches) FilteredEntries.Add(Index);
    }
    FilteredEntries.Sort([this](int32 Left, int32 Right)
    {
        const auto& A = Entries[Left]; const auto& B = Entries[Right];
        if (SortMode == 0 && A.Scan != B.Scan) return A.Scan > B.Scan;
        if (SortMode == 0 && A.FractionalHundredths != B.FractionalHundredths) return A.FractionalHundredths > B.FractionalHundredths;
        if (SortMode == 2 && A.Species.Stage != B.Species.Stage) return static_cast<int32>(A.Species.Stage) < static_cast<int32>(B.Species.Stage);
        const int32 NameOrder = A.Species.DisplayName.ToString().Compare(B.Species.DisplayName.ToString(), ESearchCase::IgnoreCase);
        if (NameOrder != 0) return NameOrder < 0;
        if (A.Species.SpeciesId != B.Species.SpeciesId) return A.Species.SpeciesId.LexicalLess(B.Species.SpeciesId);
        return static_cast<int32>(A.Variant) < static_cast<int32>(B.Variant);
    });
    const int32 PageCount = FMath::Max(1, FMath::DivideAndRoundUp(FilteredEntries.Num(), PageSize));
    Page = FMath::Clamp(Page, 0, PageCount - 1);
    Set(ResultLabel, FString::Printf(TEXT("%s matching forms  /  %d species in the full catalogue  /  separate scan data for every variety"), *FText::AsNumber(FilteredEntries.Num()).ToString(), SpeciesCount));
    Set(PageLabel, FString::Printf(TEXT("PAGE %d / %d"), Page + 1, PageCount));
    Previous->SetIsEnabled(Page > 0); Next->SetIsEnabled(Page + 1 < PageCount);
    EmptyLabel->SetVisibility(FilteredEntries.IsEmpty() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    for (int32 Index = 0; Index < ViewTabs.Num(); ++Index) DigimonVenomNXTUI::StyleButton(ViewTabs[Index], Cyan, ViewFilter == Index);
    Set(Cast<UTextBlock>(StageButton->GetContent()), StageFilter == INDEX_NONE ? TEXT("ALL STAGES  >") : Stage(static_cast<EDigimonStage>(StageFilter)) + TEXT("  >"));
    Set(Cast<UTextBlock>(VariantButton->GetContent()), VariantFilter == INDEX_NONE ? TEXT("ALL VARIETIES  >") : Variant(static_cast<EDigimonVariant>(VariantFilter)) + TEXT("  >"));
    DigimonVenomNXTUI::StyleButton(VariantButton, VariantFilter == INDEX_NONE ? Violet : Accent(static_cast<EDigimonVariant>(VariantFilter)), VariantFilter != INDEX_NONE);
    Set(Cast<UTextBlock>(SortButton->GetContent()), SortMode == 0 ? TEXT("SCAN FIRST  >") : SortMode == 1 ? TEXT("NAME A–Z  >") : TEXT("STAGE ORDER  >"));
    RefreshCards(); RefreshRecord();
}

void UDigimonVenomNXTDigiDexWidget::RefreshCards()
{
    using namespace DigimonDigiDexUI;
    if (!CachedPlayerState.IsValid()) return;
    const auto& Policy = CachedPlayerState->ScanPolicy;
    bWasBattleLocked = CachedPlayerState->HasActiveBattle();
    for (int32 CardIndex = 0; CardIndex < Cards.Num(); ++CardIndex)
    {
        auto& Card = Cards[CardIndex]; const int32 ResultIndex = Page * PageSize + CardIndex;
        const bool bVisible = FilteredEntries.IsValidIndex(ResultIndex);
        Card.Bounds->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        if (!bVisible) { Card.Portrait->SetDigimon(NAME_None, EDigimonVariant::Normal); continue; }
        const int32 EntryIndex = FilteredEntries[ResultIndex]; const auto& Entry = Entries[EntryIndex];
        const auto Preview = DigimonVenomNXTScanCore::Materialize(Entry.Scan, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
        const FLinearColor Color = Accent(Entry.Variant);
        Card.Card->SetBrush(FSlateRoundedBoxBrush(Panel, 5, EntryIndex == SelectedEntry ? Color : Color.CopyWithNewOpacity(0.35f), EntryIndex == SelectedEntry ? 2 : 1));
        Card.AccentLine->SetBrushColor(Color); Card.Portrait->SetDigimon(Entry.Species.SpeciesId, Entry.Variant);
        DigimonVenomNXTCombatUI::UpdateChips(Card.Affinity, Card.Element, Entry.Species.Affinity, Entry.Species.Element);
        Set(Card.Stage, Stage(Entry.Species.Stage)); Set(Card.Variant, Variant(Entry.Variant)); Card.Variant->SetColorAndOpacity(Color);
        Set(Card.Name, FormName(Entry.Species, Entry.Variant)); Card.Name->SetColorAndOpacity(Entry.Variant == EDigimonVariant::Shiny ? Gold : White);
        Card.Name->SetToolTipText(FText::FromString(FormName(Entry.Species, Entry.Variant) + TEXT("\n") + Entry.Species.SpeciesId.ToString()));
        Set(Card.Scan, FString::Printf(TEXT("%s / %d%% DATA   ·   %d OWNED"), *DigimonVenomNXTUI::ScanValue(Entry.Scan, Entry.FractionalHundredths), Preview.Cap, Entry.Owned));
        Card.Meter->SetPercent(Entry.Scan / static_cast<float>(FMath::Max(1, Preview.Cap))); Card.Meter->SetFillColorAndOpacity(Preview.Ready ? Ready : Color);
        Card.Meter->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s%% current scan. White marker: %d%% materialization threshold. Peak scan: %d%%."), *DigimonVenomNXTUI::ScanValue(Entry.Scan, Entry.FractionalHundredths), Preview.Requirement, Entry.Peak)));
        const float Threshold = Preview.Requirement / static_cast<float>(FMath::Max(1, Preview.Cap)); Weight(Card.ThresholdBefore, Threshold); Weight(Card.ThresholdAfter, 1.0f - Threshold);
        Set(Card.History, Entry.bEverOwned ? FString::Printf(TEXT("ARCHIVED   ·   PEAK %d%%"), Entry.Peak) : Entry.bDiscovered ? FString::Printf(TEXT("DISCOVERED   ·   PEAK %d%%"), Entry.Peak) : TEXT("UNDISCOVERED   ·   FIELD RESEARCH"));
        Set(Card.Bonus, Preview.Cap < 200 ? FString::Printf(TEXT("SERVER CAP %d%%   /   MAX +%d ABI"), Preview.Cap, DigimonVenomNXTScanCore::BonusABI(Preview.Cap)) : Entry.Scan >= 200 ? TEXT("MAXIMUM BONUS: +5 PERMANENT ABI") : Preview.Ready ? FString::Printf(TEXT("MATERIALIZE NOW: +%d ABI   /   200%%: +5"), Preview.BonusABI) : TEXT("200% SCAN  =  +5 PERMANENT ABI"));
        Card.Inspect->InitializeAction(TEXT("dexinspect"), EntryIndex); Card.Materialize->InitializeAction(TEXT("dexpreview"), EntryIndex);
        Set(Cast<UTextBlock>(Card.Materialize->GetContent()), bRequestPending ? TEXT("PENDING...") : bWasBattleLocked ? TEXT("IN BATTLE") : Preview.Ready ? TEXT("MATERIALIZE") : FString::Printf(TEXT("NEED %d%%"), FMath::Max(0, Preview.Requirement - Entry.Scan)));
        Card.Materialize->SetIsEnabled(Preview.Ready && !bRequestPending && !bWasBattleLocked);
        Card.Materialize->SetToolTipText(FText::FromString(bWasBattleLocked ? TEXT("Finish your current battle before materializing.") : Preview.Ready ? TEXT("Review this partner and the exact scan cost before confirming.") : TEXT("Win wild battles against this species and variety to gain more scan data.")));
    }
}

void UDigimonVenomNXTDigiDexWidget::RefreshRecord()
{
    using namespace DigimonDigiDexUI;
    const bool bHasRecord = Entries.IsValidIndex(SelectedEntry) && CachedPlayerState.IsValid();
    RecordPanel->SetVisibility(bHasRecord ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (!bHasRecord) return;
    const auto& Entry = Entries[SelectedEntry]; const auto& Stats = Entry.Species.BaseStats;
    const auto& Policy = CachedPlayerState->ScanPolicy;
    const auto Preview = DigimonVenomNXTScanCore::Materialize(Entry.Scan, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
    Set(RecordTitle, FormName(Entry.Species, Entry.Variant));
    RecordTitle->SetColorAndOpacity(Accent(Entry.Variant));
    DigimonVenomNXTCombatUI::UpdateChips(RecordAffinity, RecordElement, Entry.Species.Affinity, Entry.Species.Element);
    Set(RecordStats, FString::Printf(TEXT("%s  /  %s  /  %s\nLEVEL 1 BASE STATS   HP %d   SP %d   ATK %d   DEF %d   INT %d   SPD %d\nINT = special attack & special defense. SP = skill energy."), *Stage(Entry.Species.Stage), *Variant(Entry.Variant), *Entry.Species.CombatRole, Stats.MaxHP, Stats.MaxSP, Stats.Attack, Stats.Defense, Stats.Spirit, Stats.Speed));
    RecordStats->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::StatHelp() + TEXT("\n") + DigimonVenomNXTCombatUI::MatchupHelp()));
    RecordPreview->SetToolTipText(FText::GetEmpty());
    TArray<FString> EvolveNames, DevolveNames;
    for (const auto& Route : Entry.Species.Evolutions)
    {
        FDigimonSpeciesDefinition Target;
        if (CachedData.IsValid() && CachedData->GetSpecies(Route.TargetSpeciesId, Target) && !Target.bPlaceholder) EvolveNames.Add(Target.DisplayName.ToString());
    }
    if (CachedData.IsValid()) for (const auto& Source : CachedData->GetDeEvolutionSources(Entry.Species.SpeciesId)) DevolveNames.Add(Source.DisplayName.ToString());
    Set(RecordRoutes, FString::Printf(TEXT("EVOLVES TO  %s\nDE-EVOLVES TO  %s"), EvolveNames.IsEmpty() ? TEXT("No next form") : *FString::Join(EvolveNames, TEXT("  /  ")), DevolveNames.IsEmpty() ? TEXT("No previous form") : *FString::Join(DevolveNames, TEXT("  /  "))));
    Set(RecordProgress, FString::Printf(TEXT("%d owned now  /  %s%% current scan  /  %d%% peak scan  /  %d materializations recorded\n%s"), Entry.Owned, *DigimonVenomNXTUI::ScanValue(Entry.Scan, Entry.FractionalHundredths), Entry.Peak, Entry.Materializations, Entry.bEverOwned ? TEXT("OWNERSHIP ARCHIVED — this form stays recorded after evolution.") : TEXT("Not yet owned. Collect scan data to create this form.")));
    const FString Destination = CachedPlayerState->Profile.Party.Num() < FMath::Max(1, Policy.MaxPartySize) ? TEXT("party") : CachedPlayerState->Profile.DigiFarmResidents.Num() < FMath::Max(0, Policy.MaxFarmResidents) ? TEXT("DigiFarm") : TEXT("collection (party and farm are full)");
    const auto ScanNeeded = [&Entry](int32 Target)
    {
        const int32 Missing = FMath::Max(0, (Target - Entry.Scan) * 100 - Entry.FractionalHundredths);
        return DigimonVenomNXTUI::ScanValue(Missing / 100, Missing % 100);
    };
    FString PreviewText;
    if (Preview.Ready)
    {
        PreviewText = FString::Printf(TEXT("%sLEVEL 1  ·  %s  ·  +%d PERMANENT ABI\nScan: %s%% → %s%% (%s%% consumed). New partner goes to your %s."), bConfirming ? TEXT("CONFIRM MATERIALIZATION\n") : TEXT("MATERIALIZATION PREVIEW\n"), *Variant(Entry.Variant), Preview.BonusABI,
            *DigimonVenomNXTUI::ScanValue(Entry.Scan, Entry.FractionalHundredths),
            *DigimonVenomNXTUI::ScanValue(Preview.RemainingPercent, Policy.bConsumeScanOnMaterialize ? 0 : Entry.FractionalHundredths),
            *DigimonVenomNXTUI::ScanValue(Entry.Scan - Preview.RemainingPercent, Policy.bConsumeScanOnMaterialize ? Entry.FractionalHundredths : 0), *Destination);
        if (Entry.Scan < 200 && Preview.Cap >= 200) PreviewText += FString::Printf(TEXT("\nKeep scanning to 200%% for the full +5 ABI bonus (%s%% more needed)."), *ScanNeeded(200));
        else if (Preview.Cap < 200) PreviewText += FString::Printf(TEXT("\nThis server's %d%% scan cap allows a maximum of +%d ABI."), Preview.Cap, DigimonVenomNXTScanCore::BonusABI(Preview.Cap));
    }
    else
    {
        PreviewText = FString::Printf(TEXT("%s%% more scan data needed before materialization. Win wild battles against this exact species and variety."), *ScanNeeded(Preview.Requirement));
        PreviewText += Preview.Cap >= 200
            ? TEXT("\nAt 100%: no bonus ABI. Every extra 20% adds 1 ABI, up to +5 at 200%.")
            : FString::Printf(TEXT("\nThis server's %d%% scan cap allows a maximum of +%d permanent ABI."), Preview.Cap, DigimonVenomNXTScanCore::BonusABI(Preview.Cap));
    }
    if (Entry.Variant == EDigimonVariant::Firewall)
    {
        const FHabitatResearch Habitats = FirewallHabitats(CachedData.Get(), Entry.Species.SpeciesId);
        PreviewText += TEXT("\n\n") + Habitats.Summary;
        RecordPreview->SetToolTipText(FText::FromString(Habitats.Details));
    }
    if (Entry.Variant != EDigimonVariant::Normal)
    {
        const auto& Profile = CachedPlayerState->Profile;
        const bool bMastery = Entry.Variant == EDigimonVariant::Firewall ? Profile.Relay.bFirewallScanMastery
            : Entry.Variant == EDigimonVariant::Paradox ? Profile.Chronicles.bParadoxScanMastery : Profile.GhostLine.bShinyScanMastery;
        const TCHAR* Campaign = Entry.Variant == EDigimonVariant::Firewall ? TEXT("Dawn Story")
            : Entry.Variant == EDigimonVariant::Paradox ? TEXT("World DS") : TEXT("Super Xros Wars");
        PreviewText += bMastery
            ? FString::Printf(TEXT("\n%s MASTERY ACTIVE: Wild victories against this form award 20%% more scan data, up to your scan cap."), *FString(Campaign).ToUpper())
            : FString::Printf(TEXT("\nComplete %s to permanently gain 20%% more scan data from wild victories against %s Digimon."), Campaign, *Variant(Entry.Variant));
    }
    Set(RecordPreview, PreviewText);
    Set(Cast<UTextBlock>(ConfirmButton->GetContent()), bRequestPending ? TEXT("WAITING FOR SERVER...") : bWasBattleLocked ? TEXT("FINISH YOUR BATTLE FIRST") : !Preview.Ready ? TEXT("MORE SCAN DATA REQUIRED") : bConfirming ? TEXT("CONFIRM — MATERIALIZE LEVEL 1 PARTNER") : TEXT("REVIEW MATERIALIZATION"));
    ConfirmButton->SetIsEnabled(Preview.Ready && !bRequestPending && !bWasBattleLocked);
}

void UDigimonVenomNXTDigiDexWidget::ShowReadyForms()
{
    ViewFilter = 3; Page = 0; SearchTerm.Reset(); StageFilter = VariantFilter = INDEX_NONE;
    if (SearchBox) { bSearchReset = true; SearchBox->SetText(FText::GetEmpty()); bSearchReset = false; }
    if (Root) RefreshResults();
}

void UDigimonVenomNXTDigiDexWidget::HandleSearchChanged(const FText& Text)
{
    if (bSearchReset) return;
    SearchTerm = Text.ToString().TrimStartAndEnd(); Page = 0;
    RefreshResults();
}

void UDigimonVenomNXTDigiDexWidget::HandleAction(const FString& Action, int32 Payload)
{
    using namespace DigimonDigiDexUI;
    if (Action == TEXT("dexview")) { ViewFilter = FMath::Clamp(Payload, 0, 3); Page = 0; }
    else if (Action == TEXT("dexstage"))
    {
        const int32 NextStage = AvailableStages.IndexOfByKey(StageFilter) + 1;
        StageFilter = AvailableStages.IsValidIndex(NextStage) ? AvailableStages[NextStage] : INDEX_NONE; Page = 0;
    }
    else if (Action == TEXT("dexvariant")) { VariantFilter = VariantFilter >= static_cast<int32>(EDigimonVariant::Firewall) ? INDEX_NONE : VariantFilter + 1; Page = 0; }
    else if (Action == TEXT("dexsort")) { SortMode = (SortMode + 1) % 3; Page = 0; }
    else if (Action == TEXT("dexpage")) Page = FMath::Max(0, Page + Payload);
    else if (Action == TEXT("dexreset"))
    {
        SearchTerm.Reset(); ViewFilter = 0; StageFilter = VariantFilter = INDEX_NONE; SortMode = 0; Page = 0;
        bSearchReset = true; SearchBox->SetText(FText::GetEmpty()); bSearchReset = false;
    }
    else if (Action == TEXT("dexclose")) { SelectedEntry = INDEX_NONE; bConfirming = false; }
    else if (Action == TEXT("dexinspect") || Action == TEXT("dexpreview"))
    {
        if (!Entries.IsValidIndex(Payload)) return;
        SelectedEntry = Payload; bConfirming = Action == TEXT("dexpreview");
    }
    else if (Action == TEXT("dexconfirm"))
    {
        if (!CachedPlayerState.IsValid() || !Entries.IsValidIndex(SelectedEntry) || bRequestPending || CachedPlayerState->HasActiveBattle()) return;
        const auto& Policy = CachedPlayerState->ScanPolicy;
        const auto& Entry = Entries[SelectedEntry];
        const auto Preview = DigimonVenomNXTScanCore::Materialize(Entry.Scan, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
        if (!Preview.Ready) return;
        if (!bConfirming) { bConfirming = true; RefreshRecord(); return; }
        bRequestPending = true; PendingEntry = SelectedEntry; PendingScan = Entry.Scan;
        PendingCollectionCount = CachedPlayerState->Profile.Collection.Num(); RequestSentAt = FPlatformTime::Seconds();
        Set(Status, TEXT("Materialization requested. Waiting for your server-confirmed collection update...")); Status->SetVisibility(ESlateVisibility::Visible);
        RefreshCards(); RefreshRecord();
        OnAction.Broadcast(FString::Printf(TEXT("materialize:%s:%d"), *Entry.Species.SpeciesId.ToString(), static_cast<int32>(Entry.Variant)), 0);
        return;
    }
    else { OnAction.Broadcast(Action, Payload); return; }
    RefreshResults();
    if (Action == TEXT("dexinspect") || Action == TEXT("dexpreview")) RevealInScroll(RecordPanel);
    else if (Action == TEXT("dexpage")) RevealInScroll(Grid);
}

void UDigimonVenomNXTDigiDexWidget::RevealInScroll(UWidget* Widget)
{
    for (UWidget* Ancestor = GetParent(); Ancestor; Ancestor = Ancestor->GetParent())
        if (UScrollBox* Scroll = Cast<UScrollBox>(Ancestor))
        {
            Scroll->ScrollWidgetIntoView(Widget, true, EDescendantScrollDestination::TopOrLeft, 12.0f);
            break;
        }
}

void UDigimonVenomNXTDigiDexWidget::UpdateGridLayout(float Width)
{
    if (!Grid || Width < 100 || FMath::IsNearlyEqual(LastGridWidth, Width, 1.0f)) return;
    LastGridWidth = Width;
    // Six cards on wide displays, four on desktop, three on compact desktop; small windows remain usable.
    Columns = Width >= 1450 ? 6 : Width >= 960 ? 4 : Width >= 700 ? 3 : Width >= 450 ? 2 : 1;
    const float CardWidth = FMath::Max(190.0f, (Width - Columns * 8.0f) / Columns);
    for (int32 Index = 0; Index < Cards.Num(); ++Index)
    {
        Cards[Index].Bounds->SetWidthOverride(CardWidth);
        if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(Cards[Index].Bounds->Slot)) { GridSlot->SetRow(Index / Columns); GridSlot->SetColumn(Index % Columns); }
    }
}

void UDigimonVenomNXTDigiDexWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    UpdateGridLayout(MyGeometry.GetLocalSize().X);
    if (CachedPlayerState.IsValid() && CachedPlayerState->HasActiveBattle() != bWasBattleLocked) { RefreshCards(); RefreshRecord(); }
    // Failure notifications are owned by the HUD. A timeout permits retry without inventing success.
    if (bRequestPending && FPlatformTime::Seconds() - RequestSentAt >= 12.0)
    {
        bRequestPending = false; bConfirming = false;
        DigimonDigiDexUI::Set(Status, TEXT("No collection update received yet. Check the server notification before trying again."));
        RefreshCards(); RefreshRecord();
    }
}
