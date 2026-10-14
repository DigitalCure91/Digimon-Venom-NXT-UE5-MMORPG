#include "DigimonVenomNXTDigiLabWidget.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTPresentationAssets.h"
#include "DigimonVenomNXTScanCore.h"
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
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/LocalPlayer.h"
#include "HAL/PlatformTime.h"

namespace DigimonDigiLabUI
{
const FLinearColor Ink(0.010f, 0.025f, 0.043f, 1.0f);
const FLinearColor Panel(0.020f, 0.062f, 0.085f, 1.0f);
const FLinearColor White(0.95f, 0.99f, 1.0f, 1.0f);
const FLinearColor Muted(0.65f, 0.79f, 0.83f, 1.0f);
const FLinearColor Green(0.30f, 1.0f, 0.61f, 1.0f);
const FLinearColor Cyan(0.22f, 0.87f, 1.0f, 1.0f);
const FLinearColor Gold(1.0f, 0.80f, 0.35f, 1.0f);
const FLinearColor Red(1.0f, 0.47f, 0.43f, 1.0f);

UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 13, FLinearColor Color = White, bool bBold = false)
{
    UTextBlock* Result = Tree->ConstructWidget<UTextBlock>();
    Result->SetText(FText::FromString(Value)); Result->SetColorAndOpacity(Color); Result->SetAutoWrapText(true);
    FSlateFontInfo Font = Result->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Result->SetFont(Font);
    return Result;
}
void Set(UTextBlock* Widget, const FString& Value) { if (Widget) Widget->SetText(FText::FromString(Value)); }
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
UBorder* Card(UWidgetTree* Tree, FLinearColor Accent = Cyan)
{
    UBorder* Result = Tree->ConstructWidget<UBorder>();
    Result->SetBrush(FSlateRoundedBoxBrush(Panel, 10.0f, Accent.CopyWithNewOpacity(0.35f), 1.0f));
    Result->SetPadding(FMargin(14)); return Result;
}
UProgressBar* Meter(UWidgetTree* Tree, UVerticalBox* Box, FLinearColor Color)
{
    UProgressBar* Bar = Tree->ConstructWidget<UProgressBar>(); Bar->SetFillColorAndOpacity(Color);
    FProgressBarStyle Style = Bar->GetWidgetStyle();
    Style.SetBackgroundImage(FSlateRoundedBoxBrush(Ink, 3.0f));
    Style.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White, 3.0f)); Bar->SetWidgetStyle(Style);
    USizeBox* Bounds = Tree->ConstructWidget<USizeBox>(); Bounds->SetHeightOverride(7.0f); Bounds->AddChild(Bar); Add(Box, Bounds, 2);
    return Bar;
}
}

TSharedRef<SWidget> UDigimonVenomNXTDigiLabWidget::RebuildWidget()
{
    BuildLayout();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTDigiLabWidget::NativeConstruct()
{
    Super::NativeConstruct();
    RefreshFromProfile();
}

void UDigimonVenomNXTDigiLabWidget::NativeDestruct()
{
    if (BoundPlayerState.IsValid())
    {
        BoundPlayerState->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTDigiLabWidget::RefreshFromProfile);
        BoundPlayerState->OnDigiLabHealResult.RemoveDynamic(this, &UDigimonVenomNXTDigiLabWidget::HandleHealResult);
    }
    BoundPlayerState.Reset(); HealingTracks.Empty(); PendingRequest.Invalidate(); LastReceipt.Invalidate(); bPendingHeal = false;
    Super::NativeDestruct();
}

ADigimonVenomNXTPlayerState* UDigimonVenomNXTDigiLabWidget::PlayerState() const
{
    const APlayerController* PC = GetOwningPlayer();
    return PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
}

void UDigimonVenomNXTDigiLabWidget::BindPlayerState()
{
    ADigimonVenomNXTPlayerState* PS = PlayerState();
    if (BoundPlayerState.Get() == PS) return;
    if (BoundPlayerState.IsValid())
    {
        BoundPlayerState->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTDigiLabWidget::RefreshFromProfile);
        BoundPlayerState->OnDigiLabHealResult.RemoveDynamic(this, &UDigimonVenomNXTDigiLabWidget::HandleHealResult);
    }
    BoundPlayerState = PS; HealingTracks.Empty(); PendingRequest.Invalidate(); LastReceipt.Invalidate(); bPendingHeal = false;
    if (PS)
    {
        PS->OnProfileChanged.AddDynamic(this, &UDigimonVenomNXTDigiLabWidget::RefreshFromProfile);
        PS->OnDigiLabHealResult.AddDynamic(this, &UDigimonVenomNXTDigiLabWidget::HandleHealResult);
    }
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTDigiLabWidget::Button(const FString& Label, const FString& Action, FLinearColor Accent)
{
    UDigimonVenomNXTActionButton* Result = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(Result, Accent); Result->InitializeAction(Action);
    Result->OnAction.AddDynamic(this, &UDigimonVenomNXTDigiLabWidget::HandleAction);
    UTextBlock* Caption = DigimonDigiLabUI::Text(WidgetTree, Label, 12, DigimonDigiLabUI::White, true);
    Caption->SetJustification(ETextJustify::Center); Result->SetContent(Caption); return Result;
}

void UDigimonVenomNXTDigiLabWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("DigiLabWidgetTree"));
    using namespace DigimonDigiLabUI;
    Root = WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget = Root;

    // The illustration establishes the room; all labels remain real, accessible UMG text.
    UBorder* Hero = Card(WidgetTree, Green); Hero->SetPadding(FMargin(0)); Hero->SetClipping(EWidgetClipping::ClipToBounds); Add(Root, Hero, 2);
    USizeBox* HeroBounds = WidgetTree->ConstructWidget<USizeBox>(); HeroBounds->SetHeightOverride(224); Hero->SetContent(HeroBounds);
    UOverlay* HeroOverlay = WidgetTree->ConstructWidget<UOverlay>(); HeroBounds->AddChild(HeroOverlay);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, HeroOverlay, DigimonVenomNXTPresentationAssets::ObjectPath(TEXT("DigiLabHero")), FLinearColor(0.005f, 0.019f, 0.030f, 0.82f));
    UBorder* HeroCaption = Card(WidgetTree, Green);
    HeroCaption->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.009f, 0.030f, 0.045f, 0.91f), 0.0f)); HeroCaption->SetPadding(FMargin(18, 12));
    if (UOverlaySlot* ChildSlot = HeroOverlay->AddChildToOverlay(HeroCaption)) { ChildSlot->SetVerticalAlignment(VAlign_Bottom); ChildSlot->SetHorizontalAlignment(HAlign_Fill); }
    UHorizontalBox* HeroRow = WidgetTree->ConstructWidget<UHorizontalBox>(); HeroCaption->SetContent(HeroRow);
    UVerticalBox* HeroText = WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeroRow, HeroText, true, 0);
    Add(HeroText, Text(WidgetTree, TEXT("DIGILAB"), 29, White, true), 0);
    Add(HeroText, Text(WidgetTree, TEXT("PARTNER CARE  /  RESEARCH  /  DISCOVERY"), 10, Green, true), 2);
    Add(HeroText, Text(WidgetTree, TEXT("A moment to recover. A new possibility to discover."), 12, Muted), 1);
    Row(HeroRow, Button(TEXT("RETURN TO MAP"), TEXT("digilab:return"), Cyan), false, 6);

    UBorder* Recovery = Card(WidgetTree, Green); Add(Root, Recovery, 8);
    UVerticalBox* RecoveryBody = WidgetTree->ConstructWidget<UVerticalBox>(); Recovery->SetContent(RecoveryBody);
    UHorizontalBox* RecoveryRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(RecoveryBody, RecoveryRow, 1);
    UVerticalBox* RecoveryText = WidgetTree->ConstructWidget<UVerticalBox>(); Row(RecoveryRow, RecoveryText, true, 0);
    Add(RecoveryText, Text(WidgetTree, TEXT("PARTNER RECOVERY"), 18, White, true), 1);
    PartySummary = Text(WidgetTree, TEXT("Synchronizing your party..."), 13, Green, true); Add(RecoveryText, PartySummary, 1);
    CollectionSummary = Text(WidgetTree, TEXT("Full HP and SP for every owned partner. Always free."), 11, Muted); Add(RecoveryText, CollectionSummary, 1);
    HealButton = Button(TEXT("RESTORE ALL  /  FREE"), TEXT("digilab:heal"), Green);
    HealCaption = Cast<UTextBlock>(HealButton->GetContent());
    HealButton->SetToolTipText(FText::FromString(TEXT("Restore HP and SP for your entire collection, including defeated partners. Free outside battles.")));
    Row(RecoveryRow, HealButton, false, 8);
    RecoveryStatus = Text(WidgetTree, TEXT("Your map and position stay right where you left them."), 12, Muted); Add(RecoveryBody, RecoveryStatus, 4);

    UHorizontalBox* PartyHeader = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root, PartyHeader, 3);
    Row(PartyHeader, Text(WidgetTree, TEXT("YOUR CURRENT PARTY"), 14, White, true), true, 0);
    Row(PartyHeader, Button(TEXT("MANAGE PARTY"), TEXT("page:Party"), Cyan), false, 0);
    UUniformGridPanel* Grid = WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Root, Grid, 2);
    for (int32 Index = 0; Index < 6; ++Index)
    {
        FDigimonDigiLabCardView View;
        View.Card = Card(WidgetTree, Cyan); View.Card->SetPadding(FMargin(11)); View.Card->SetClipping(EWidgetClipping::ClipToBounds);
        if (UUniformGridSlot* ChildSlot = Grid->AddChildToUniformGrid(View.Card, Index / 2, Index % 2)) ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        UOverlay* Overlay = WidgetTree->ConstructWidget<UOverlay>(); View.Card->SetContent(Overlay);
        UVerticalBox* Content = WidgetTree->ConstructWidget<UVerticalBox>();
        if (UOverlaySlot* ChildSlot = Overlay->AddChildToOverlay(Content)) ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        View.Slot = Text(WidgetTree, FString::Printf(TEXT("PARTY SLOT %02d"), Index + 1), 9, Muted, true); Add(Content, View.Slot, 0);
        UHorizontalBox* Main = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Content, Main, 3);
        USizeBox* PortraitSize = WidgetTree->ConstructWidget<USizeBox>(); PortraitSize->SetWidthOverride(72); PortraitSize->SetHeightOverride(92);
        View.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); PortraitSize->AddChild(View.Portrait); Row(Main, PortraitSize, false, 0);
        UVerticalBox* Detail = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Main, Detail, true, 8);
        View.Name = Text(WidgetTree, TEXT("Empty slot"), 16, White, true);
        View.Name->SetAutoWrapText(false); View.Name->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); Add(Detail, View.Name, 0);
        View.Identity = Text(WidgetTree, TEXT("Add a partner from Collection"), 10, Muted); Add(Detail, View.Identity, 1);
        View.Health = Text(WidgetTree, TEXT("HP  —"), 11, Green, true); Add(Detail, View.Health, 1); View.HPBar = Meter(WidgetTree, Detail, Green);
        View.SkillPoints = Text(WidgetTree, TEXT("SP  —"), 11, Cyan, true); Add(Detail, View.SkillPoints, 1); View.SPBar = Meter(WidgetTree, Detail, Cyan);
        View.Status = Text(WidgetTree, TEXT("AWAITING A PARTNER"), 10, Muted, true); Add(Content, View.Status, 1);
        View.Restored = Text(WidgetTree, TEXT(""), 10, Green, true); Add(Content, View.Restored, 0);
        View.Restored->SetVisibility(ESlateVisibility::Collapsed);
        for (int32 EffectIndex = 0; EffectIndex < 3; ++EffectIndex)
        {
            UTextBlock* Plus = Text(WidgetTree, TEXT("+"), 30, Green, true);
            Plus->SetAutoWrapText(false); Plus->SetVisibility(ESlateVisibility::HitTestInvisible); Plus->SetRenderOpacity(0.0f);
            Plus->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.18f, 0.08f, 0.8f)); Plus->SetShadowOffset(FVector2D(1, 1));
            if (UOverlaySlot* ChildSlot = Overlay->AddChildToOverlay(Plus)) { ChildSlot->SetHorizontalAlignment(HAlign_Left); ChildSlot->SetVerticalAlignment(VAlign_Center); ChildSlot->SetPadding(FMargin(16, 0, 0, 0)); }
            View.Pluses.Add(Plus);
        }
        PartyCards.Add(View);
    }

    UBorder* Research = Card(WidgetTree, Cyan); Add(Root, Research, 8);
    UVerticalBox* ResearchBody = WidgetTree->ConstructWidget<UVerticalBox>(); Research->SetContent(ResearchBody);
    Add(ResearchBody, Text(WidgetTree, TEXT("SCAN RESEARCH & MATERIALIZATION"), 18, White, true), 1);
    ResearchSummary = Text(WidgetTree, TEXT("Reading your research..."), 14, Gold, true); Add(ResearchBody, ResearchSummary, 3);
    ResearchDetails = Text(WidgetTree, TEXT(""), 12, Muted); Add(ResearchBody, ResearchDetails, 3);
    UHorizontalBox* ResearchActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ResearchBody, ResearchActions, 7);
    Row(ResearchActions, Button(TEXT("OPEN DIGIDEX"), TEXT("page:DigiDex"), Cyan), true, 2);
    Row(ResearchActions, Button(TEXT("READY SCANS"), TEXT("dexready"), Gold), true, 2);
    Row(ResearchActions, Button(TEXT("COLLECTION & EVOLUTION"), TEXT("page:Collection"), Green), true, 2);
    Add(ResearchBody, Text(WidgetTree, TEXT("Compare forms, review evolution routes and bring your next partner to life. Your research belongs to your tamer."), 11, Muted), 1);
}

void UDigimonVenomNXTDigiLabWidget::RefreshFromProfile()
{
    BuildLayout(); BindPlayerState();
    using namespace DigimonDigiLabUI;
    ADigimonVenomNXTPlayerState* PS = BoundPlayerState.Get();
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!PS || !Data || PS->Profile.AccountId.IsEmpty()) { UpdateControls(); return; }
    int32 Present = 0, InNeed = 0; TSet<FGuid> VisibleIds;
    for (int32 Index = 0; Index < PartyCards.Num(); ++Index)
    {
        FDigimonDigiLabCardView& View = PartyCards[Index];
        FDigimonOwnedPartner Partner;
        const bool bPresent = PS->Profile.Party.IsValidIndex(Index) && PS->GetPartner(PS->Profile.Party[Index], Partner);
        View.Portrait->SetVisibility(bPresent ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
        if (!bPresent)
        {
            View.InstanceId.Invalidate(); Set(View.Name, TEXT("Empty slot")); View.Name->SetToolTipText(FText::GetEmpty());
            Set(View.Identity, TEXT("Add a partner from Collection")); View.Identity->SetColorAndOpacity(Muted);
            Set(View.Health, TEXT("HP  —")); Set(View.SkillPoints, TEXT("SP  —")); Set(View.Status, TEXT("AWAITING A PARTNER")); View.Status->SetColorAndOpacity(Muted);
            View.HPBar->SetPercent(0); View.SPBar->SetPercent(0); View.Restored->SetVisibility(ESlateVisibility::Collapsed);
            for (UTextBlock* Plus : View.Pluses) Plus->SetRenderOpacity(0);
            View.Card->SetBrush(FSlateRoundedBoxBrush(Ink, 10.0f, Muted.CopyWithNewOpacity(0.16f), 1.0f));
            continue;
        }
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        View.InstanceId = Partner.InstanceId; VisibleIds.Add(Partner.InstanceId); ++Present;
        auto& Track = HealingTracks.FindOrAdd(Partner.InstanceId);
        Track.Observe({Unit.HP, Unit.SP, Unit.Stats.MaxHP, Unit.Stats.MaxSP}, PS->Profile.DigiLabRecoveryRevision);
        Track.AdvanceClock(FPlatformTime::Seconds());
        const auto Target = Track.To;
        if (Target.HP < Target.MaxHP || Target.SP < Target.MaxSP) ++InNeed;
        View.Portrait->SetDigimon(Partner.SpeciesId, Partner.Variant);
        Set(View.Name, Unit.DisplayName); View.Name->SetToolTipText(FText::FromString(Unit.DisplayName));
        Set(View.Identity, FString::Printf(TEXT("LEVEL %d  /  %s"), Unit.Level, *DigimonVenomNXTUI::VarietyLabel(Partner.Variant)));
        View.Identity->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Partner.Variant));
        UpdatePresentation(View);
    }
    for (auto It = HealingTracks.CreateIterator(); It; ++It) if (!VisibleIds.Contains(It.Key())) It.RemoveCurrent();
    Set(PartySummary, Present == 0 ? TEXT("No partners assigned  /  Add your team from Collection") :
        InNeed > 0 ? FString::Printf(TEXT("%d / 6 party slots  •  %d %s need recovery"), Present, InNeed, InNeed == 1 ? TEXT("partner") : TEXT("partners")) :
        FString::Printf(TEXT("%d / 6 party slots  •  Team ready to explore"), Present));
    Set(CollectionSummary, FString::Printf(TEXT("%d owned  •  Full HP & SP recovery  •  Farm and collection included"), PS->Profile.Collection.Num()));
    int32 Ready = 0, FullResearch = 0;
    const FDigimonScanPolicy& Policy = PS->ScanPolicy;
    for (const FDigimonScanRecord& Scan : PS->Profile.Scans)
    {
        FDigimonSpeciesDefinition Definition;
        if (!Data->GetSpecies(Scan.SpeciesId, Definition) || Definition.bPlaceholder) continue;
        if (!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Scan.Variant), Definition.bHasNormalArtwork, Definition.bHasParadoxArtwork, Definition.bHasShinyArtwork, Definition.bHasFirewallArtwork)) continue;
        const auto Outcome = DigimonVenomNXTScanCore::Materialize(Scan.Percent, Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, Policy.bConsumeScanOnMaterialize);
        if (Outcome.Ready) { ++Ready; if (Outcome.BonusABI == 5) ++FullResearch; }
    }
    Set(ResearchSummary, FString::Printf(TEXT("%d forms ready to materialize  •  %d ready with +5 ABI"), Ready, FullResearch));
    Set(ResearchDetails, FString::Printf(TEXT("Materialize from %d%% scan. Research can reach %d%% for up to +%d permanent ABI. Preview your partner and its scan cost in DigiDex before confirming."), Policy.MaterializeRequirementPercent, Policy.ScanCapPercent, DigimonVenomNXTScanCore::BonusABI(Policy.ScanCapPercent)));
    UpdateControls();
}

void UDigimonVenomNXTDigiLabWidget::UpdatePresentation(FDigimonDigiLabCardView& Card)
{
    using namespace DigimonDigiLabUI;
    auto* Track = HealingTracks.Find(Card.InstanceId); if (!Track) return;
    const auto Vitals = Track->Display();
    Set(Card.Health, FString::Printf(TEXT("HP  %d / %d"), Vitals.HP, Vitals.MaxHP));
    Set(Card.SkillPoints, FString::Printf(TEXT("SP  %d / %d"), Vitals.SP, Vitals.MaxSP));
    Card.HPBar->SetPercent(static_cast<float>(Vitals.HP) / Vitals.MaxHP);
    Card.SPBar->SetPercent(static_cast<float>(Vitals.SP) / FMath::Max(1, Vitals.MaxSP));
    const bool bAnimating = Track->IsAnimating();
    const bool bHealthy = Track->To.HP == Track->To.MaxHP && Track->To.SP == Track->To.MaxSP;
    const FLinearColor Accent = bAnimating || bHealthy ? Green : Track->To.HP == 0 ? Red : Gold;
    Card.Status->SetColorAndOpacity(Accent);
    Set(Card.Status, bAnimating ? TEXT("RESTORING  /  RECOVERY CONFIRMED") : bHealthy ? TEXT("READY  /  FULL HP & SP") : Track->To.HP == 0 ? TEXT("DEFEATED  /  RECOVERY NEEDED") : TEXT("RECOVERY AVAILABLE"));
    Card.Card->SetBrush(FSlateRoundedBoxBrush(Panel, 10.0f, Accent.CopyWithNewOpacity(bAnimating ? 0.60f + 0.25f * FMath::Sin(static_cast<float>(Track->Elapsed) * 7.0f) : 0.3f), bAnimating ? 2.0f : 1.0f));
    Card.Restored->SetVisibility(Track->ShowingReceipt ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
    if (Track->ShowingReceipt)
        Set(Card.Restored, FString::Printf(TEXT("RECOVERED  +%d HP  /  +%d SP"), Track->To.HP - Track->From.HP, Track->To.SP - Track->From.SP));
    for (int32 Index = 0; Index < Card.Pluses.Num(); ++Index)
    {
        UTextBlock* Plus = Card.Pluses[Index];
        const float Phase = (static_cast<float>(Track->Elapsed) - Index * 0.28f) / 1.30f;
        const bool bVisible = bAnimating && Phase >= 0.0f && Phase <= 1.0f;
        Plus->SetRenderOpacity(bVisible ? FMath::Sin(Phase * PI) * 0.95f : 0.0f);
        Plus->SetRenderTranslation(FVector2D(12.0f + Index * 16.0f, 26.0f - FMath::Clamp(Phase, 0.0f, 1.0f) * 68.0f));
        const float Scale = 0.7f + FMath::Clamp(Phase, 0.0f, 1.0f) * 0.35f;
        Plus->SetRenderScale(FVector2D(Scale, Scale));
    }
}

void UDigimonVenomNXTDigiLabWidget::UpdateControls()
{
    if (!HealButton) return;
    ADigimonVenomNXTPlayerState* PS = BoundPlayerState.Get();
    const bool bReady = PS && !PS->Profile.AccountId.IsEmpty() && PS->Profile.Collection.Num() > 0;
    const bool bBattleLocked = PS && PS->HasActiveBattle();
    HealButton->SetIsEnabled(bReady && !bBattleLocked && !bPendingHeal);
    DigimonDigiLabUI::Set(HealCaption, bPendingHeal ? TEXT("CONFIRMING RECOVERY...") : bBattleLocked ? TEXT("AVAILABLE AFTER BATTLE") : TEXT("RESTORE ALL  /  FREE"));
    if (bBattleLocked && !bPendingHeal)
    {
        DigimonDigiLabUI::Set(RecoveryStatus, TEXT("Finish your current battle before using DigiLab recovery. Saved Season battles must also be completed."));
        RecoveryStatus->SetColorAndOpacity(DigimonDigiLabUI::Gold);
    }
}

void UDigimonVenomNXTDigiLabWidget::HandleAction(const FString& Action, int32 Payload)
{
    if (Action == TEXT("digilab:return"))
    {
        if (ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) PC->SetFieldMenuOpen(false);
        return;
    }
    if (Action != TEXT("digilab:heal")) { OnAction.Broadcast(Action, Payload); return; }
    ADigimonVenomNXTPlayerState* PS = PlayerState();
    if (!PS || PS->Profile.AccountId.IsEmpty() || PS->HasActiveBattle() || bPendingHeal) { UpdateControls(); return; }
    BindPlayerState(); PendingRequest = FGuid::NewGuid(); bPendingHeal = true; PendingStartedAt = FPlatformTime::Seconds();
    DigimonDigiLabUI::Set(RecoveryStatus, TEXT("Requesting free recovery. Your partner vitals will update after confirmation."));
    RecoveryStatus->SetColorAndOpacity(DigimonDigiLabUI::Cyan); UpdateControls();
    PS->ServerRequestDigiLabHeal(PendingRequest);
}

void UDigimonVenomNXTDigiLabWidget::HandleHealResult(const FDigimonHealReceipt& Receipt)
{
    if (!Receipt.RequestId.IsValid() || Receipt.RequestId != PendingRequest || Receipt.RequestId == LastReceipt) return;
    LastReceipt = Receipt.RequestId; bPendingHeal = false; PendingStartedAt = 0.0;
    if (Receipt.bSuccess)
    {
        for (const FDigimonHealedPartner& Partner : Receipt.PartyChanges)
        {
            if (!PartyCards.ContainsByPredicate([&](const FDigimonDigiLabCardView& Card) { return Card.InstanceId == Partner.InstanceId; })) continue;
            auto& Track = HealingTracks.FindOrAdd(Partner.InstanceId);
            Track.Confirm({Partner.BeforeHP, Partner.BeforeSP, Partner.MaxHP, Partner.MaxSP}, {Partner.AfterHP, Partner.AfterSP, Partner.MaxHP, Partner.MaxSP}, Receipt.RecoveryRevision, FPlatformTime::Seconds());
        }
    }
    if (UDigimonVenomNXTAudioSubsystem* Audio = GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
    {
        const EDigimonAudioCue Cue = !Receipt.bSuccess ? EDigimonAudioCue::Error : Receipt.RestoredPartners > 0 ? EDigimonAudioCue::Heal : EDigimonAudioCue::Confirm;
        Audio->PlayCueOnce(Cue, TEXT("DigiLab:") + Receipt.RequestId.ToString(EGuidFormats::Digits));
    }
    RefreshFromProfile();
    DigimonDigiLabUI::Set(RecoveryStatus, Receipt.Message);
    RecoveryStatus->SetColorAndOpacity(Receipt.bSuccess ? DigimonDigiLabUI::Green : DigimonDigiLabUI::Red);
}

void UDigimonVenomNXTDigiLabWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    for (auto& Entry : HealingTracks)
    {
        if (!Entry.Value.IsAnimating()) continue;
        Entry.Value.AdvanceClock(FPlatformTime::Seconds());
        for (FDigimonDigiLabCardView& Card : PartyCards) if (Card.InstanceId == Entry.Key) UpdatePresentation(Card);
    }
    if (bPendingHeal)
    {
        if (FPlatformTime::Seconds() - PendingStartedAt >= 12.0)
        {
            bPendingHeal = false;
            DigimonDigiLabUI::Set(RecoveryStatus, TEXT("Still waiting for recovery confirmation. Check your connection, or try again."));
            if (RecoveryStatus) RecoveryStatus->SetColorAndOpacity(DigimonDigiLabUI::Gold);
            UpdateControls();
        }
    }
    ProfilePollSeconds += InDeltaTime;
    if (ProfilePollSeconds >= 1.0f)
    {
        ProfilePollSeconds = 0.0f;
        // No widget reconstruction or collection scan per tick. Poll only identity / lock state.
        if (PlayerState() != BoundPlayerState.Get()) RefreshFromProfile(); else UpdateControls();
    }
}
