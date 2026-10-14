#include "DigimonVenomNXTBattleWidget.h"
#include "DigimonVenomNXTUnrankedComponent.h"
#include "GameFramework/GameStateBase.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTTimelineCore.h"
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTUIComponents.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/ScaleBox.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Texture2D.h"
#include "Engine/LocalPlayer.h"

namespace DigimonBattleUI
{
    // The original Venom NXT palette, expressed as sRGB colors rather than guessed tints.
    static const FLinearColor Navy(FColor(5,15,32));
    static const FLinearColor Panel(FColor(18,35,49));
    static const FLinearColor Line(FColor(35,82,116));
    static const FLinearColor Cyan(FColor(67,213,231));
    static const FLinearColor Gold(FColor(247,199,104));
    static const FLinearColor Text(FColor(231,241,249));
    static const FLinearColor Muted(FColor(141,164,185));
    static const FLinearColor HP(FColor(190,240,107));
    static const FLinearColor EnemyHP(FColor(255,117,138));
    static constexpr float ArenaWidth = 1044.0f;
    static constexpr float ArenaHeight = 500.0f;
    static constexpr float ActionDuration = 0.82f;
    static constexpr float ImpactTime = 0.30f;

    UTextBlock* MakeText(UWidgetTree* Tree, const FString& Value, int32 Size=13, FLinearColor Color=Text, bool bBold=false)
    {
        UTextBlock* T = Tree->ConstructWidget<UTextBlock>();
        T->SetText(FText::FromString(Value));
        T->SetColorAndOpacity(FSlateColor(Color));
        T->SetAutoWrapText(true);
        T->SetVisibility(ESlateVisibility::HitTestInvisible);
        FSlateFontInfo Font = T->GetFont();
        Font.Size = Size;
        Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular"));
        T->SetFont(Font);
        return T;
    }

    void Place(UCanvasPanel* Canvas, UWidget* Widget, float X, float Y, float Width, float Height, int32 Z=0)
    {
        if (UCanvasPanelSlot* S = Canvas->AddChildToCanvas(Widget))
        {
            S->SetPosition(FVector2D(X,Y));
            S->SetSize(FVector2D(Width,Height));
            S->SetZOrder(Z);
        }
    }

    void Add(UVerticalBox* Box, UWidget* Widget, float Padding=3.0f)
    {
        if (UVerticalBoxSlot* S = Box->AddChildToVerticalBox(Widget))
        {
            S->SetPadding(FMargin(0,Padding));
            S->SetHorizontalAlignment(HAlign_Fill);
        }
    }

    void AddAction(UHorizontalBox* Box, UWidget* Widget)
    {
        if (UHorizontalBoxSlot* S = Box->AddChildToHorizontalBox(Widget))
        {
            S->SetPadding(FMargin(3,0));
            S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
            S->SetHorizontalAlignment(HAlign_Fill);
            S->SetVerticalAlignment(VAlign_Fill);
        }
    }

    UBorder* MakePanel(UWidgetTree* Tree, FLinearColor Fill=Panel, float Radius=5.0f)
    {
        UBorder* B = Tree->ConstructWidget<UBorder>();
        B->SetBrush(FSlateRoundedBoxBrush(Fill, Radius, Line, 1.0f));
        B->SetBrushColor(FLinearColor::White);
        B->SetPadding(FMargin(0));
        return B;
    }

    void StyleSelection(UDigimonVenomNXTActionButton* B, bool Selected, FLinearColor Color)
    {
        const FLinearColor Clear(0,0,0,0);
        FButtonStyle S;
        S.SetNormal(FSlateRoundedBoxBrush(Clear,13.0f,Selected ? Color : Clear,Selected ? 2.0f : 0.0f));
        S.SetHovered(FSlateRoundedBoxBrush(Color.CopyWithNewOpacity(0.035f),13.0f,Color.CopyWithNewOpacity(0.65f),1.0f));
        S.SetPressed(FSlateRoundedBoxBrush(Color.CopyWithNewOpacity(0.075f),13.0f,Color,2.0f));
        S.SetDisabled(S.Normal);
        S.SetNormalPadding(FMargin(0));
        S.SetPressedPadding(FMargin(0));
        B->SetStyle(S);
        B->SetBackgroundColor(FLinearColor::White);
    }

    UDigimonVenomNXTActionButton* MakeAction(UWidgetTree* Tree, const FString& Label, const FString& Action, int32 Payload=0, bool bGold=false)
    {
        UDigimonVenomNXTActionButton* B = Tree->ConstructWidget<UDigimonVenomNXTActionButton>();
        B->InitializeAction(Action, Payload);
        FButtonStyle S;
        S.SetNormal(FSlateRoundedBoxBrush(bGold ? Gold : Panel,5.0f,bGold ? Gold : Line,1.0f));
        S.SetHovered(FSlateRoundedBoxBrush(bGold ? FLinearColor(FColor(255,218,150)) : FLinearColor(FColor(25,58,77)),5.0f,Cyan,1.0f));
        S.SetPressed(FSlateRoundedBoxBrush(bGold ? FLinearColor(FColor(215,164,75)) : Navy,5.0f,Gold,1.0f));
        S.SetDisabled(FSlateRoundedBoxBrush(FLinearColor(FColor(17,29,41)),5.0f,Line.CopyWithNewOpacity(0.5f),1.0f));
        S.SetNormalPadding(FMargin(10,8));
        S.SetPressedPadding(FMargin(10,9,10,7));
        B->SetStyle(S);
        UTextBlock* LabelWidget = MakeText(Tree,Label,13,bGold ? Navy : Text,bGold);
        LabelWidget->SetJustification(ETextJustify::Center);
        B->AddChild(LabelWidget);
        B->SetToolTipText(FText::FromString(Label));
        return B;
    }

    UProgressBar* MakeBar(UWidgetTree* Tree, FLinearColor Fill)
    {
        UProgressBar* B = Tree->ConstructWidget<UProgressBar>();
        FProgressBarStyle S;
        S.SetBackgroundImage(FSlateRoundedBoxBrush(FLinearColor(FColor(2,10,19)),3.0f));
        S.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White,3.0f));
        B->SetWidgetStyle(S);
        B->SetBarFillStyle(EProgressBarFillStyle::Scale);
        B->SetFillColorAndOpacity(Fill);
        B->SetVisibility(ESlateVisibility::HitTestInvisible);
        return B;
    }

    void FallbackGrid(UWidgetTree* Tree, UCanvasPanel* Canvas)
    {
        UBorder* Base = Tree->ConstructWidget<UBorder>();
        Base->SetBrushColor(Navy);
        Base->SetVisibility(ESlateVisibility::HitTestInvisible);
        Place(Canvas,Base,0,0,ArenaWidth,ArenaHeight);
        auto DrawLine = [&](FVector2D A, FVector2D B, FLinearColor Color)
        {
            UBorder* L = Tree->ConstructWidget<UBorder>();
            L->SetBrushColor(Color);
            L->SetVisibility(ESlateVisibility::HitTestInvisible);
            Place(Canvas,L,A.X,A.Y,(B-A).Size(),0.8f);
            L->SetRenderTransformPivot(FVector2D::ZeroVector);
            L->SetRenderTransformAngle(FMath::RadiansToDegrees(FMath::Atan2(B.Y-A.Y,B.X-A.X)));
        };
        for (int32 I=-12; I<=12; ++I)
            DrawLine(FVector2D(ArenaWidth*0.5f+I*15.0f,70),FVector2D(ArenaWidth*0.5f+I*130.0f,ArenaHeight),Line.CopyWithNewOpacity(0.55f));
        for (int32 I=0; I<24; ++I)
        {
            const float A = static_cast<float>(I)/23.0f;
            const float Y = 72.0f+A*A*(ArenaHeight-72.0f);
            DrawLine(FVector2D(0,Y),FVector2D(ArenaWidth,Y),Line.CopyWithNewOpacity(0.5f));
        }
    }
}

void UDigimonVenomNXTBattleWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    BuildNativeUI();
}

void UDigimonVenomNXTBattleWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildNativeUI();
    if (Battle.IsValid())
    {
        Battle->OnBattleStateChanged.AddUniqueDynamic(this,&UDigimonVenomNXTBattleWidget::HandleBattleStateChanged);
        for (const FDigimonBattleState& Packet : Battle->ConsumePresentationBacklog()) HandleBattleStateChanged(Packet);
        if (ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
            PC->ServerAcknowledgeBattlePresentation(Battle.Get());
    }
    Refresh();
}

void UDigimonVenomNXTBattleWidget::NativeDestruct()
{
    if (Battle.IsValid())
    {
        Battle->OnBattleStateChanged.RemoveDynamic(this,&UDigimonVenomNXTBattleWidget::HandleBattleStateChanged);
        Battle->ReleasePresentationConsumer();
    }
    Super::NativeDestruct();
}

void UDigimonVenomNXTBattleWidget::BuildNativeUI()
{
    if (bBuilt || !WidgetTree) return;
    bBuilt = true;
    using namespace DigimonBattleUI;
    UOverlay* Viewport = WidgetTree->ConstructWidget<UOverlay>();
    WidgetTree->RootWidget = Viewport;
    UBorder* Back = WidgetTree->ConstructWidget<UBorder>();
    Back->SetBrushColor(Navy);
    Back->SetVisibility(ESlateVisibility::HitTestInvisible);
    Viewport->AddChildToOverlay(Back);
    UScaleBox* Responsive = WidgetTree->ConstructWidget<UScaleBox>();
    Responsive->SetStretch(EStretch::ScaleToFit);
    Responsive->SetStretchDirection(EStretchDirection::Both);
    if (UOverlaySlot* S = Viewport->AddChildToOverlay(Responsive))
    { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
    USizeBox* DesignSize = WidgetTree->ConstructWidget<USizeBox>();
    DesignSize->SetWidthOverride(1280); DesignSize->SetHeightOverride(720);
    Responsive->AddChild(DesignSize);
    UCanvasPanel* Layout = WidgetTree->ConstructWidget<UCanvasPanel>();
    Layout->SetClipping(EWidgetClipping::ClipToBounds);
    DesignSize->AddChild(Layout);

    UBorder* ArenaFrame = MakePanel(WidgetTree,Navy);
    Place(Layout,ArenaFrame,10,8,1048,602);
    BattleTitle = MakeText(WidgetTree,TEXT("DIGIMON BATTLE"),23,Text,true);
    Place(Layout,BattleTitle,24,17,810,29);
    BattleSubtitle = MakeText(WidgetTree,TEXT("YOUR LIVE MATCH  /  SELECT YOUR TARGET"),9,Cyan);
    Place(Layout,BattleSubtitle,25,46,800,14);
    TurnText = MakeText(WidgetTree,TEXT("TURN 1"),14,Gold,true);
    TurnText->SetJustification(ETextJustify::Right);
    Place(Layout,TurnText,867,24,172,24);

    PresentationOverlay = WidgetTree->ConstructWidget<UOverlay>();
    PresentationOverlay->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    Place(Layout,PresentationOverlay,12,62,ArenaWidth,ArenaHeight);
    UCanvasPanel* Backdrop = WidgetTree->ConstructWidget<UCanvasPanel>();
    Backdrop->SetVisibility(ESlateVisibility::HitTestInvisible);
    if (UOverlaySlot* S = PresentationOverlay->AddChildToOverlay(Backdrop))
    { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
    // The original Venom battle stage is native geometry: a calm perspective
    // floor with a clear horizon, never a stretched image from another game.
    FallbackGrid(WidgetTree,Backdrop);
    ArenaCanvas = WidgetTree->ConstructWidget<UCanvasPanel>();
    ArenaCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    if (UOverlaySlot* S = PresentationOverlay->AddChildToOverlay(ArenaCanvas))
    { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }

    CommandsBox = WidgetTree->ConstructWidget<UHorizontalBox>();
    Place(Layout,CommandsBox,20,568,1028,34);
    UBorder* LogPanel = MakePanel(WidgetTree);
    Place(Layout,LogPanel,10,621,1048,89);
    UTextBlock* LogHeading = MakeText(WidgetTree,TEXT("BATTLE LOG"),10,Cyan,true);
    Place(Layout,LogHeading,22,629,300,15);
    LogScroll = WidgetTree->ConstructWidget<UScrollBox>();
    LogScroll->SetScrollBarVisibility(ESlateVisibility::Visible);
    Place(Layout,LogScroll,22,648,1020,41);
    LogText = MakeText(WidgetTree,TEXT(""),10,Muted);
    LogText->SetWrapTextAt(980.0f);
    LogScroll->AddChild(LogText);
    EventText = MakeText(WidgetTree,TEXT("Choose an opponent, then command your active partner."),10,Text);
    EventText->SetClipping(EWidgetClipping::ClipToBoundsAlways);
    Place(Layout,EventText,22,691,1020,15);

    UBorder* PartyPanel = MakePanel(WidgetTree);
    Place(Layout,PartyPanel,1070,8,200,702);
    UTextBlock* PartyHeading = MakeText(WidgetTree,TEXT("PARTNER LINK"),11,HP,true);
    Place(Layout,PartyHeading,1081,24,142,18);
    PartyCount = MakeText(WidgetTree,TEXT("0 / 6"),10,Muted);
    PartyCount->SetJustification(ETextJustify::Right);
    Place(Layout,PartyCount,1220,24,38,18);
    UScrollBox* PartyScroll = WidgetTree->ConstructWidget<UScrollBox>();
    Place(Layout,PartyScroll,1079,49,182,582);
    PartyBox = WidgetTree->ConstructWidget<UVerticalBox>();
    PartyScroll->AddChild(PartyBox);
    MatchupPreview = MakeText(WidgetTree,TEXT("Select an opponent to preview your attack."),10,Muted);
    Place(Layout,MatchupPreview,1082,643,176,57);
    MatchupPreview->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::MatchupHelp()));

    ActionTray = MakePanel(WidgetTree,FLinearColor(FColor(9,27,44)));
    ActionTray->SetPadding(FMargin(12));
    ActionTrayContent = WidgetTree->ConstructWidget<UVerticalBox>();
    ActionTray->SetContent(ActionTrayContent);
    ActionTray->SetVisibility(ESlateVisibility::Collapsed);
    Place(Layout,ActionTray,24,372,1020,188,20);

    // Results have a separate bounded reading area. Long campaign dialogue,
    // rewards and level-up lists must never push the fixed return control away.
    ResultPanel = MakePanel(WidgetTree,FLinearColor(FColor(7,23,42)));
    ResultPanel->SetPadding(FMargin(22,18));
    ResultPanel->SetVisibility(ESlateVisibility::Collapsed);
    Place(Layout,ResultPanel,24,94,1020,454,25);
    UVerticalBox* ResultBody = WidgetTree->ConstructWidget<UVerticalBox>(); ResultPanel->SetContent(ResultBody);
    ResultHeading = MakeText(WidgetTree,TEXT("MATCH COMPLETE"),23,Gold,true); Add(ResultBody,ResultHeading,2);
    Add(ResultBody,MakeText(WidgetTree,TEXT("YOUR RESULT  /  REWARDS & NEXT STEPS"),10,Cyan,true),3);
    ResultScroll = WidgetTree->ConstructWidget<UScrollBox>();
    ResultScroll->SetScrollBarVisibility(ESlateVisibility::Visible);
    ResultScroll->SetClipping(EWidgetClipping::ClipToBoundsAlways);
    if (UVerticalBoxSlot* S = ResultBody->AddChildToVerticalBox(ResultScroll))
    { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0,10,0,8)); }
    ResultSummary = MakeText(WidgetTree,TEXT(""),15,Text);
    ResultSummary->SetWrapTextAt(936.0f); ResultScroll->AddChild(ResultSummary);
    Add(ResultBody,MakeText(WidgetTree,TEXT("Scroll to read the full result. The return button below stays available."),10,Muted),2);

    ImpactImage = WidgetTree->ConstructWidget<UImage>();
    ImpactImage->SetDesiredSizeOverride(FVector2D(176,160));
    ImpactImage->SetVisibility(ESlateVisibility::Collapsed);
    if (UOverlaySlot* S = PresentationOverlay->AddChildToOverlay(ImpactImage))
    { S->SetHorizontalAlignment(HAlign_Center); S->SetVerticalAlignment(VAlign_Center); }
    ImpactText = MakeText(WidgetTree,TEXT(""),32,Gold,true);
    ImpactText->SetJustification(ETextJustify::Center);
    ImpactText->SetRenderOpacity(0);
    if (UOverlaySlot* S = PresentationOverlay->AddChildToOverlay(ImpactText))
    { S->SetHorizontalAlignment(HAlign_Center); S->SetVerticalAlignment(VAlign_Center); }
    ImpactDetail = MakeText(WidgetTree,TEXT(""),12,Gold,true);
    ImpactDetail->SetJustification(ETextJustify::Center);
    ImpactDetail->SetRenderOpacity(0);
    if (UOverlaySlot* S = PresentationOverlay->AddChildToOverlay(ImpactDetail))
    { S->SetHorizontalAlignment(HAlign_Center); S->SetVerticalAlignment(VAlign_Center); }
    for (int32 Frame=0; Frame<=14; ++Frame)
    {
        const FString Asset = FString::Printf(TEXT("T_DVNXT_BattleImpact_%02d"),Frame);
        if (UTexture2D* Texture = LoadObject<UTexture2D>(nullptr,*FString::Printf(TEXT("/DigimonVenomNXT/Generated/UI/Presentation/%s.%s"),*Asset,*Asset),nullptr,LOAD_NoWarn))
            ImpactFrames.Add(Texture);
    }
}

void UDigimonVenomNXTBattleWidget::SetBattle(ADigimonVenomNXTBattleActor* InBattle)
{
    if (Battle.Get() == InBattle)
    {
        // Reopening the same visible screen must not skip queued animation or reset its idle phases.
        if (Battle.IsValid())
        {
            Battle->OnBattleStateChanged.AddUniqueDynamic(this,&UDigimonVenomNXTBattleWidget::HandleBattleStateChanged);
            const TArray<FDigimonBattleState> Backlog=Battle->ConsumePresentationBacklog();
            for (const FDigimonBattleState& Packet : Backlog) HandleBattleStateChanged(Packet);
            if (Backlog.Num()==0) HandleBattleStateChanged(Battle->State);
            if (ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
                PC->ServerAcknowledgeBattlePresentation(Battle.Get());
        }
        return;
    }
    if (Battle.IsValid())
    {
        Battle->OnBattleStateChanged.RemoveDynamic(this,&UDigimonVenomNXTBattleWidget::HandleBattleStateChanged);
        Battle->ReleasePresentationConsumer();
    }
    Battle = InBattle;
    PendingPresentationEvents.Reset();
    bPresentationAnimating = false;
    bHasDisplayState = false;
    SeenPresentationSerial = 0;
    SelectedActor = SelectedTarget = CommandTab = 0;
    SubmittedSlots.Reset();
    BattleLog.Reset();
    if (LogText) LogText->SetText(FText::GetEmpty());
    if (LogScroll) LogScroll->ScrollToStart();
    if (Battle.IsValid())
    {
        Battle->OnBattleStateChanged.AddUniqueDynamic(this,&UDigimonVenomNXTBattleWidget::HandleBattleStateChanged);
        const ADigimonVenomNXTPlayerController* OwnerPC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
        bVisualOursAreOriginalB=OwnerPC && OwnerPC->PlayerState==Battle->PlayerB;
        const TArray<FDigimonBattleState> Backlog=Battle->ConsumePresentationBacklog();
        if (Backlog.Num()>0)
        {
            // Packet zero is the original full-health roster. Never seed from the newest
            // replicated post-action state when the widget took longer to construct.
            for (const FDigimonBattleState& Packet : Backlog) HandleBattleStateChanged(Packet);
        }
        else HandleBattleStateChanged(Battle->State);
        if (ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
            PC->ServerAcknowledgeBattlePresentation(Battle.Get());
    }
    else Refresh();
}

FString UDigimonVenomNXTBattleWidget::VariantLabel(EDigimonVariant Variant) const
{
    if (Variant == EDigimonVariant::Paradox) return TEXT("PARADOX");
    return DigimonVenomNXTUI::VarietyLabel(Variant);
}

int32 UDigimonVenomNXTBattleWidget::FindFirstLivingTarget(const FDigimonBattleTeam& Team) const
{
    for (int32 I=0; I<Team.Active.Num(); ++I)
        if (!Team.Active[I].bDefeated && Team.Active[I].HP > 0) return I;
    return INDEX_NONE;
}

bool UDigimonVenomNXTBattleWidget::IsAutomaticBattle() const
{
    return DisplayState.bAutomatic;
}

void UDigimonVenomNXTBattleWidget::RebuildTeam(const FDigimonBattleTeam& Team, bool bPlayerTeam, TArray<FDigimonBattleSlotVisual>& Visuals)
{
    using namespace DigimonBattleUI;
    for (FDigimonBattleSlotVisual& V : Visuals) if (V.Selection) V.Selection->RemoveFromParent();
    Visuals.Reset();
    const float Width = FMath::Min(202.0f,ArenaWidth/static_cast<float>(FMath::Max(3,Team.Active.Num())+1)-10.0f);
    const float SpriteSize = FMath::Min(142.0f,Width-24.0f);
    for (int32 I=0; I<Team.Active.Num(); ++I)
    {
        FDigimonBattleSlotVisual V;
        V.Selection = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
        V.Selection->InitializeAction(bPlayerTeam ? TEXT("actor") : TEXT("target"),I);
        V.Selection->OnAction.AddDynamic(this,&UDigimonVenomNXTBattleWidget::HandleAction);
        StyleSelection(V.Selection,false,bPlayerTeam ? Cyan : Gold);
        UCanvasPanel* UnitLayout = WidgetTree->ConstructWidget<UCanvasPanel>();
        UnitLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        V.Selection->SetContent(UnitLayout);
        const float X = ArenaWidth*static_cast<float>(I+1)/static_cast<float>(Team.Active.Num()+1)-Width*0.5f;
        Place(ArenaCanvas,V.Selection,X,bPlayerTeam ? 272.0f : 38.0f,Width,216.0f);
        V.Marker = MakeText(WidgetTree,TEXT(""),9,bPlayerTeam ? HP : Gold);
        V.Marker->SetJustification(ETextJustify::Center);
        Place(UnitLayout,V.Marker,4,bPlayerTeam ? 199.0f : 5.0f,Width-8,14);
        V.Name = MakeText(WidgetTree,TEXT(""),13,bPlayerTeam ? Text : EnemyHP,true);
        V.Name->SetJustification(ETextJustify::Center);
        V.Name->SetClipping(EWidgetClipping::ClipToBoundsAlways);
        V.Name->SetMinDesiredWidth(0);
        Place(UnitLayout,V.Name,5,20,Width-10,34);
        V.Detail = MakeText(WidgetTree,TEXT(""),9,Muted);
        V.Detail->SetJustification(ETextJustify::Center);
        Place(UnitLayout,V.Detail,4,53,Width-8,13);
        UTextBlock* TypeText = nullptr; UTextBlock* ElementText = nullptr;
        UHorizontalBox* Chips = DigimonVenomNXTCombatUI::TypeChips(WidgetTree, TypeText, ElementText, 8);
        V.Affinity = TypeText; V.Element = ElementText;
        Place(UnitLayout,Chips,3,68,Width-6,18);
        UBorder* Shadow = WidgetTree->ConstructWidget<UBorder>();
        Shadow->SetBrush(FSlateRoundedBoxBrush((bPlayerTeam ? Cyan : EnemyHP).CopyWithNewOpacity(0.16f),55.0f));
        Shadow->SetBrushColor(FLinearColor::White);
        Shadow->SetVisibility(ESlateVisibility::HitTestInvisible);
        Place(UnitLayout,Shadow,(Width-100)*0.5f,171,100,16);
        V.SpriteHost = WidgetTree->ConstructWidget<UBorder>();
        V.SpriteHost->SetBrushColor(FLinearColor::Transparent);
        V.SpriteHost->SetPadding(FMargin(0));
        V.SpriteHost->SetVisibility(ESlateVisibility::HitTestInvisible);
        V.Portrait = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>();
        V.Portrait->SetFacingLeft(!bPlayerTeam);
        V.Portrait->SetVisibility(ESlateVisibility::HitTestInvisible);
        V.SpriteHost->SetContent(V.Portrait);
        V.SpriteHost->SetRenderTransformPivot(FVector2D(0.5f,0.9f));
        Place(UnitLayout,V.SpriteHost,(Width-SpriteSize)*0.5f,87,SpriteSize,98);
        V.HP = MakeBar(WidgetTree,bPlayerTeam ? HP : EnemyHP);
        Place(UnitLayout,V.HP,Width*0.17f,188,Width*0.66f,5);
        V.SP = MakeBar(WidgetTree,Cyan);
        Place(UnitLayout,V.SP,Width*0.17f,196,Width*0.66f,3);
        V.SP->SetVisibility(bPlayerTeam ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
        Visuals.Add(V);
    }
}

void UDigimonVenomNXTBattleWidget::RefreshTeam(const FDigimonBattleTeam& Team, bool bPlayerTeam, TArray<FDigimonBattleSlotVisual>& Visuals)
{
    using namespace DigimonBattleUI;
    if (Visuals.Num() != Team.Active.Num()) RebuildTeam(Team,bPlayerTeam,Visuals);
    for (int32 I=0; I<Team.Active.Num(); ++I)
    {
        const FDigimonBattleUnit& Unit = Team.Active[I];
        FDigimonBattleSlotVisual& V = Visuals[I];
        const bool Alive = !Unit.bDefeated && Unit.HP>0;
        if (V.SpeciesId != Unit.SpeciesId || V.Variant != Unit.Variant)
        {
            V.SpeciesId=Unit.SpeciesId; V.Variant=Unit.Variant;
            V.Portrait->SetDigimon(Unit.SpeciesId,Unit.Variant);
        }
        V.Name->SetText(FText::FromString(Unit.DisplayName));
        DigimonVenomNXTCombatUI::UpdateChips(V.Affinity, V.Element, Unit.Affinity, Unit.Element);
        V.Detail->SetText(FText::FromString(FString::Printf(TEXT("Lv.%d  /  SPD %d  /  %s"),Unit.Level,Unit.Stats.Speed,*VariantLabel(Unit.Variant))));
        V.Detail->SetColorAndOpacity(DigimonVenomNXTUI::VarietyAccent(Unit.Variant));
        V.HP->SetPercent(static_cast<float>(Unit.HP)/FMath::Max(1,Unit.Stats.MaxHP));
        V.SP->SetPercent(static_cast<float>(Unit.SP)/FMath::Max(1,Unit.Stats.MaxSP));
        const bool Selected = Alive && (bPlayerTeam ? I==SelectedActor : I==SelectedTarget);
        StyleSelection(V.Selection,Selected && (!bPlayerTeam || !IsAutomaticBattle()),bPlayerTeam ? Cyan.CopyWithNewOpacity(0.38f) : Gold);
        FString Marker;
        if (!Alive) Marker=TEXT("DEFEATED");
        else if (!bPlayerTeam && Selected) Marker=TEXT("TARGET");
        else if (Unit.bGuarding) Marker=TEXT("GUARDING · HALF DAMAGE");
        else if (DisplayState.ActingTeam==(bPlayerTeam ? (bVisualOursAreOriginalB ? 1 : 0) : (bVisualOursAreOriginalB ? 0 : 1)) && DisplayState.ActingSlot==I) Marker=IsAutomaticBattle() ? TEXT("ACTING") : bPlayerTeam ? TEXT("YOUR ACTION") : TEXT("OPPONENT ACTION");
        V.Marker->SetText(FText::FromString(Marker));
        V.Selection->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::UnitDetails(Unit)));
        V.Portrait->SetRenderOpacity(Alive ? 1.0f : 0.28f);
        V.Name->SetRenderOpacity(Alive ? 1.0f : 0.45f);
    }
}

void UDigimonVenomNXTBattleWidget::RefreshParty(const FDigimonBattleTeam& Team)
{
    using namespace DigimonBattleUI;
    const int32 PartySize = Team.Active.Num()+Team.Bench.Num();
    const int32 Links = FMath::Max(6,PartySize);
    PartyCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),PartySize,Links)));
    if (PartyVisuals.Num() != Links)
    {
        PartyBox->ClearChildren();
        PartyVisuals.Reset();
        for (int32 I=0; I<Links; ++I)
        {
            FDigimonBattleSlotVisual V;
            V.Selection=WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
            V.Selection->InitializeAction(TEXT("link"),I);
            V.Selection->OnAction.AddDynamic(this,&UDigimonVenomNXTBattleWidget::HandleAction);
            USizeBox* Size=WidgetTree->ConstructWidget<USizeBox>();
            Size->SetHeightOverride(89.0f);
            UCanvasPanel* Content=WidgetTree->ConstructWidget<UCanvasPanel>();
            Size->AddChild(Content); V.Selection->SetContent(Size);
            V.Portrait=WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>();
            V.Portrait->SetVisibility(ESlateVisibility::HitTestInvisible);
            Place(Content,V.Portrait,5,10,47,62);
            V.Name=MakeText(WidgetTree,TEXT(""),10,Text,true);
            V.Name->SetClipping(EWidgetClipping::ClipToBoundsAlways);
            Place(Content,V.Name,58,8,118,29);
            V.Detail=MakeText(WidgetTree,TEXT(""),8,Muted);
            Place(Content,V.Detail,58,37,118,13);
            V.HP=MakeBar(WidgetTree,HP); Place(Content,V.HP,58,54,116,4);
            V.SP=MakeBar(WidgetTree,Cyan); Place(Content,V.SP,58,62,116,3);
            V.Marker=MakeText(WidgetTree,TEXT(""),8,Muted);
            Place(Content,V.Marker,58,69,118,12);
            Add(PartyBox,V.Selection,3);
            PartyVisuals.Add(V);
        }
    }
    for (int32 I=0; I<PartyVisuals.Num(); ++I)
    {
        FDigimonBattleSlotVisual& V=PartyVisuals[I];
        const FDigimonBattleUnit* Unit=Team.Active.IsValidIndex(I) ? &Team.Active[I] : (Team.Bench.IsValidIndex(I-Team.Active.Num()) ? &Team.Bench[I-Team.Active.Num()] : nullptr);
        const bool Active=I<Team.Active.Num();
        FButtonStyle Style;
        Style.SetNormal(FSlateRoundedBoxBrush(Panel,4.0f,Unit && Active && I==SelectedActor ? HP.CopyWithNewOpacity(0.8f) : Line,1.0f));
        Style.SetHovered(FSlateRoundedBoxBrush(FLinearColor(FColor(21,48,62)),4.0f,Cyan,1.0f));
        Style.SetPressed(Style.Hovered); Style.SetDisabled(Style.Normal);
        Style.SetNormalPadding(FMargin(0)); Style.SetPressedPadding(FMargin(0));
        V.Selection->SetStyle(Style);
        if (!Unit)
        {
            V.Name->SetText(FText::FromString(FString::Printf(TEXT("%02d / OPEN LINK"),I+1)));
            V.Name->SetColorAndOpacity(FSlateColor(Muted));
            V.Detail->SetText(FText::GetEmpty()); V.Marker->SetText(FText::GetEmpty());
            V.Portrait->SetVisibility(ESlateVisibility::Collapsed);
            V.HP->SetVisibility(ESlateVisibility::Collapsed); V.SP->SetVisibility(ESlateVisibility::Collapsed);
            V.Selection->SetIsEnabled(false);
            continue;
        }
        V.Selection->SetIsEnabled(true);
        V.Portrait->SetVisibility(ESlateVisibility::HitTestInvisible);
        V.HP->SetVisibility(ESlateVisibility::HitTestInvisible); V.SP->SetVisibility(ESlateVisibility::HitTestInvisible);
        if (V.SpeciesId!=Unit->SpeciesId || V.Variant!=Unit->Variant)
        { V.SpeciesId=Unit->SpeciesId; V.Variant=Unit->Variant; V.Portrait->SetDigimon(Unit->SpeciesId,Unit->Variant); }
        V.Name->SetText(FText::FromString(Unit->DisplayName));
        V.Name->SetColorAndOpacity(FSlateColor(Text));
        V.Detail->SetText(FText::FromString(FString::Printf(TEXT("Lv.%d / %s"),Unit->Level,Active ? TEXT("ACTIVE") : TEXT("RESERVE"))));
        V.Detail->SetColorAndOpacity(Unit->Variant == EDigimonVariant::Firewall ? DigimonVenomNXTUI::VarietyAccent(Unit->Variant) : Muted);
        V.Marker->SetText(FText::FromString(FString::Printf(TEXT("HP %d/%d  SP %d"),Unit->HP,Unit->Stats.MaxHP,Unit->SP)));
        V.HP->SetPercent(static_cast<float>(Unit->HP)/FMath::Max(1,Unit->Stats.MaxHP));
        V.SP->SetPercent(static_cast<float>(Unit->SP)/FMath::Max(1,Unit->Stats.MaxSP));
        V.Portrait->SetRenderOpacity(Unit->bDefeated ? 0.3f : 1.0f);
        V.Selection->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::UnitDetails(*Unit) + TEXT("\n") + (Active ? TEXT("Each partner acts when its speed timer is ready.") : TEXT("Switch the acting partner with this reserve; switching uses its action."))));
    }
}

void UDigimonVenomNXTBattleWidget::RefreshCommands(const FDigimonBattleTeam& Ours)
{
    using namespace DigimonBattleUI;
    CommandsBox->ClearChildren();
    ActionTrayContent->ClearChildren();
    ActionTray->SetVisibility(ESlateVisibility::Collapsed);
    const bool bWasShowingResult=ResultPanel&&ResultPanel->GetVisibility()!=ESlateVisibility::Collapsed;
    if(ResultPanel)ResultPanel->SetVisibility(ESlateVisibility::Collapsed);
    const bool Busy=IsPresentationBusy();
    auto Button = [&](const FString& Label,const FString& Action,int32 Payload=0,bool bGold=false)
    {
        UDigimonVenomNXTActionButton* B=MakeAction(WidgetTree,Label,Action,Payload,bGold);
        B->OnAction.AddDynamic(this,&UDigimonVenomNXTBattleWidget::HandleAction);
        return B;
    };
    if (DisplayState.bFinished && !Busy)
    {
        MatchupPreview->SetText(FText::FromString(DisplayState.bFled ? TEXT("ESCAPED\nNo battle rewards.\nHP and SP retained.") : TEXT("MATCH COMPLETE\nReview the result, then return when ready.")));
        const int32 OursIndex=bVisualOursAreOriginalB ? 1 : 0;
        UTextBlock* Result=MakeText(WidgetTree,DisplayState.bFled ? TEXT("ESCAPED") : DisplayState.WinningTeam==OursIndex ? TEXT("VICTORY") : (DisplayState.WinningTeam==INDEX_NONE ? TEXT("DRAW") : TEXT("DEFEAT")),20,Gold,true);
        Result->SetJustification(ETextJustify::Center);
        AddAction(CommandsBox,Result);
        const ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
        const FString ReturnLabel=DisplayState.Kind==EDigimonBattleKind::Season ? TEXT("RETURN TO YOUR CAREER") : PC&&PC->IsInGhostLine() ? TEXT("CONTINUE SUPER XROS WARS") : PC&&PC->IsInChronicles() ? TEXT("CONTINUE WORLD DS") : PC&&PC->IsInRelay() ? TEXT("CONTINUE DAWN STORY") : TEXT("RETURN TO THE WORLD");
        UDigimonVenomNXTActionButton* Return=Button(ReturnLabel,TEXT("leave"),0,true);
        AddAction(CommandsBox,Return);
        if(ResultPanel)
        {
            ResultPanel->SetVisibility(ESlateVisibility::Visible);
            ResultHeading->SetText(Result->GetText());
            if(ResultSummary->GetText().ToString()!=DisplayState.LastEvent)ResultSummary->SetText(FText::FromString(DisplayState.LastEvent));
            if(!bWasShowingResult)
            {
                ResultScroll->ScrollToStart();
                Return->SetUserFocus(GetOwningPlayer());
            }
        }
        return;
    }
    if (Battle.IsValid() && Battle->bUnrankedResultSaving)
    {
        MatchupPreview->SetText(FText::FromString(TEXT("SAVING RESULT\nBoth tamers' records are being committed. Please wait.")));
        AddAction(CommandsBox,MakeText(WidgetTree,TEXT("Saving match result…"),13,Gold,true));
        return;
    }
    if (IsAutomaticBattle())
    {
        MatchupPreview->SetText(FText::FromString(TEXT("AUTO BATTLE\nYour party chooses targets and skills using the same matchup rules.")));
        UTextBlock* Auto=MakeText(WidgetTree,TEXT("AUTO BATTLE  /  YOUR PARTY IS FIGHTING"),13,Gold,true);
        Auto->SetJustification(ETextJustify::Center);
        AddAction(CommandsBox,Auto);
        return;
    }
    const int32 OurTeam=bVisualOursAreOriginalB ? 1 : 0;
    const FDigimonBattleTeam& Theirs=bVisualOursAreOriginalB ? DisplayState.TeamA : DisplayState.TeamB;
    const FDigimonBattleUnit* Unit=Ours.Active.IsValidIndex(SelectedActor) ? &Ours.Active[SelectedActor] : nullptr;
    const FDigimonBattleUnit* Target=Theirs.Active.IsValidIndex(SelectedTarget) ? &Theirs.Active[SelectedTarget] : nullptr;
    const bool CanCommand=!Busy && Unit && Unit->HP>0 && !Unit->bDefeated && !SubmittedSlots.Contains(SelectedActor)
        && DisplayState.ActingTeam==OurTeam && DisplayState.ActingSlot==SelectedActor;
    UDigimonVenomNXTActionButton* Attack=Button(TEXT("Attack · 0 SP"),TEXT("attack"),0,true);
    Attack->SetToolTipText(FText::FromString(TEXT("Neutral physical attack. Always available at 0 SP. ATK attacks DEF.") +
        (Unit && Target ? TEXT("\n") + DigimonVenomNXTCombatUI::MatchupDetail(*Unit,*Target,EDigimonElement::Neutral) : FString())));
    Attack->SetIsEnabled(CanCommand && Target); AddAction(CommandsBox,Attack);
    UDigimonVenomNXTActionButton* Skills=Button(TEXT("Skills"),TEXT("skills"));
    Skills->SetIsEnabled(CanCommand); AddAction(CommandsBox,Skills);
    UDigimonVenomNXTActionButton* Guard=Button(TEXT("Guard"),TEXT("guard"));
    Guard->SetToolTipText(FText::FromString(TEXT("Use this action to halve incoming damage until this partner's next action. Costs 0 SP.")));
    Guard->SetIsEnabled(CanCommand); AddAction(CommandsBox,Guard);
    UDigimonVenomNXTActionButton* Items=Button((DisplayState.Kind==EDigimonBattleKind::Friendly) ? TEXT("Switch") : TEXT("Items / Switch"),TEXT("items"));
    Items->SetIsEnabled(CanCommand); AddAction(CommandsBox,Items);
    if (DisplayState.Kind==EDigimonBattleKind::Wild)
    {
        UDigimonVenomNXTActionButton* Flee=Button(TEXT("Flee"),TEXT("retreat"));
        Flee->SetToolTipText(FText::FromString(TEXT("Leave this wild encounter immediately. No XP, credits or scan data. Your remaining HP and SP are kept.")));
        Flee->SetIsEnabled(CanCommand); AddAction(CommandsBox,Flee);
    }
    if (DisplayState.Kind==EDigimonBattleKind::Friendly)
    {
        UDigimonVenomNXTActionButton* Surrender=Button(bConfirmUnrankedSurrender ? TEXT("Confirm surrender") : TEXT("Surrender"),TEXT("surrender"));
        Surrender->SetToolTipText(FText::FromString(TEXT("Surrender counts as a loss. Your expedition party, items and currency are unchanged. Click twice to confirm.")));
        AddAction(CommandsBox,Surrender);
        if (bConfirmUnrankedSurrender) AddAction(CommandsBox,Button(TEXT("Keep battling"),TEXT("keep_battling")));
    }
    UDigimonVenomNXTActionButton* Help=Button(TEXT("Matchups"),TEXT("matchup_help"));
    Help->SetIsEnabled(!Busy); AddAction(CommandsBox,Help);
    if (Unit && Target && MatchupPreview)
    {
        MatchupPreview->SetText(FText::FromString((DisplayState.ActingTeam==OurTeam ? TEXT("BASIC ATTACK\n") : TEXT("WAITING FOR OPPONENT\n")) + DigimonVenomNXTCombatUI::MatchupLabel(DigimonVenomNXTCombatUI::Effectiveness(*Unit,*Target,EDigimonElement::Neutral)) + TEXT("\nPhysical · Neutral · 0 SP")));
        MatchupPreview->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::MatchupDetail(*Unit,*Target,EDigimonElement::Neutral)));
    }
    if (CommandTab==0 || Busy || (CommandTab!=3 && !CanCommand)) return;
    ActionTray->SetVisibility(ESlateVisibility::Visible);
    UHorizontalBox* Heading=WidgetTree->ConstructWidget<UHorizontalBox>();
    Add(ActionTrayContent,Heading,0);
    const FString HeadingText=CommandTab==3 ? TEXT("BATTLE GUIDE  /  TYPE, ELEMENT & STATS") : FString::Printf(TEXT("%s  /  %s%s"),*Unit->DisplayName,
        CommandTab==1 ? TEXT("SKILLS") : TEXT("ITEMS & TEAM"),Target && CommandTab==1 ? *FString(TEXT("  →  ")+Target->DisplayName) : TEXT(""));
    UTextBlock* Title=MakeText(WidgetTree,HeadingText,12,Cyan,true);
    if (UHorizontalBoxSlot* S=Heading->AddChildToHorizontalBox(Title)) S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    Heading->AddChildToHorizontalBox(Button(TEXT("Close"),TEXT("close_tray")));
    if (CommandTab==3)
    {
        Add(ActionTrayContent,MakeText(WidgetTree,DigimonVenomNXTCombatUI::MatchupHelp(),11,Text),4);
        Add(ActionTrayContent,MakeText(WidgetTree,DigimonVenomNXTCombatUI::StatHelp(),10,Muted),2);
        return;
    }
    UHorizontalBox* Choices=WidgetTree->ConstructWidget<UHorizontalBox>();
    Add(ActionTrayContent,Choices,7);
    if (CommandTab==1)
    {
        for (int32 I=0; I<FMath::Min(4,Unit->Moves.Num()); ++I)
        {
            const FDigimonMoveSlot& Move=Unit->Moves[I];
            const FString Matchup=Target ? DigimonVenomNXTCombatUI::MatchupLabel(DigimonVenomNXTCombatUI::Effectiveness(*Unit,*Target,Move.Element)) : TEXT("Select a target");
            const FString Label=FString::Printf(TEXT("%s\n%s · %s\nPower %d%% · %d SP\n%s%s"),*DigimonVenomNXTCombatUI::MoveName(Move),
                *DigimonVenomNXTCombatUI::Class(Move.DamageClass),*DigimonVenomNXTCombatUI::Element(Move.Element),Move.Power,Move.SPCost,*Matchup,
                Unit->SP<Move.SPCost ? *FString::Printf(TEXT("\nNeed %d more SP"),Move.SPCost-Unit->SP) : TEXT(""));
            UDigimonVenomNXTActionButton* Skill=Button(Label,TEXT("move"),I);
            Skill->SetToolTipText(FText::FromString(Move.Description + TEXT("\n") + (Move.DamageClass==EDigimonDamageClass::Special ? TEXT("INT attacks the target's INT.") : TEXT("ATK attacks the target's DEF.")) +
                (Target ? TEXT("\n")+DigimonVenomNXTCombatUI::MatchupDetail(*Unit,*Target,Move.Element) : FString())));
            Skill->SetIsEnabled(Unit->SP>=Move.SPCost && Target);
            AddAction(Choices,Skill);
        }
        if (Unit->Moves.Num()==0) AddAction(Choices,MakeText(WidgetTree,TEXT("No skills learned yet. Attack uses no SP."),12,Muted));
    }
    else if (DisplayState.Kind==EDigimonBattleKind::Friendly)
    {
        Add(ActionTrayContent,MakeText(WidgetTree,TEXT("Select a healthy reserve in PARTNER LINK to switch. Switching spends this partner's action. Consumables are disabled in this rested-party challenge."),11,Muted),4);
    }
    else
    {
        const ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
        const ADigimonVenomNXTPlayerState* PS=PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        // HP/SP S, M and L all use their source catalog amount and inventory ID.
        for (const TCHAR* ItemId : { TEXT("hp_s"), TEXT("hp_m"), TEXT("hp_l"), TEXT("sp_s"), TEXT("sp_m"), TEXT("sp_l") })
        {
            FDigimonShopItemDefinition Item;
            if (!Data || !Data->GetShopItem(FName(ItemId), Item)) continue;
            const bool bHP = Item.Resource == FName(TEXT("hp"));
            const int32 Count = PS ? PS->GetInventoryQuantity(FName(ItemId)) : 0;
            UDigimonVenomNXTActionButton* Use = Button(FString::Printf(TEXT("%s\n×%d  ·  +%d %s"), *Item.DisplayName.ToString(), Count, Item.Amount, bHP ? TEXT("HP") : TEXT("SP")), FString(TEXT("item:")) + ItemId);
            Use->SetToolTipText(FText::FromString(FString::Printf(TEXT("Restore up to %d %s to the acting partner, capped at maximum. Uses one capsule and one action."), Item.Amount, bHP ? TEXT("HP") : TEXT("SP"))));
            Use->SetIsEnabled(Count > 0 && (bHP ? Unit->HP < Unit->Stats.MaxHP : Unit->SP < Unit->Stats.MaxSP));
            AddAction(Choices, Use);
        }
        Add(ActionTrayContent,MakeText(WidgetTree,TEXT("Select a reserve in PARTNER LINK to switch it into the acting partner's slot. Items and switching each use that partner's action."),11,Muted),4);
    }
}

void UDigimonVenomNXTBattleWidget::Refresh()
{
    if (!bBuilt || !bHasDisplayState || !Battle.IsValid() || !WidgetTree) return;
    const ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    bVisualOursAreOriginalB=PC && PC->PlayerState==Battle->PlayerB;
    const FDigimonBattleTeam& Ours=bVisualOursAreOriginalB ? DisplayState.TeamB : DisplayState.TeamA;
    const FDigimonBattleTeam& Theirs=bVisualOursAreOriginalB ? DisplayState.TeamA : DisplayState.TeamB;
    if (PC && PC->CurrentBattle.Get() == Battle.Get())
    {
        if (UDigimonVenomNXTAudioSubsystem* Audio = PC->GetLocalPlayer() ? PC->GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        {
            const bool bLocalVictory = DisplayState.bFinished && !IsPresentationBusy() &&
                DisplayState.WinningTeam == (bVisualOursAreOriginalB ? 1 : 0);
            // Result BGM follows the visible final impact, not early replicated HP.
            Audio->SetBattleMusicState(Battle.Get(), PC->GetLocalMusicMapId(),
                bLocalVictory, DisplayState.Kind == EDigimonBattleKind::Season);
            if (DisplayState.bFinished && !IsPresentationBusy())
                Audio->PlayCueOnce(DisplayState.bFled ? EDigimonAudioCue::Flee : bLocalVictory ? EDigimonAudioCue::Victory : EDigimonAudioCue::Defeat,
                    TEXT("battle-result:") + DisplayState.BattleId.ToString());
        }
    }
    if (!Theirs.Active.IsValidIndex(SelectedTarget) || Theirs.Active[SelectedTarget].HP<=0 || Theirs.Active[SelectedTarget].bDefeated)
        SelectedTarget=FindFirstLivingTarget(Theirs);
    const int32 OurTeam = bVisualOursAreOriginalB ? 1 : 0;
    if (!IsPresentationBusy() && DisplayState.ActingTeam==OurTeam && Ours.Active.IsValidIndex(DisplayState.ActingSlot))
        SelectedActor=DisplayState.ActingSlot;
    else if (!Ours.Active.IsValidIndex(SelectedActor) || Ours.Active[SelectedActor].HP<=0 || Ours.Active[SelectedActor].bDefeated)
        SelectedActor=FindFirstLivingTarget(Ours);
    FString Kind;
    switch (DisplayState.Kind)
    {
        case EDigimonBattleKind::Wild: Kind=TEXT("WILD ENCOUNTER"); break;
        case EDigimonBattleKind::AITamer: Kind=TEXT("RIVAL MATCH"); break;
        case EDigimonBattleKind::Season: Kind=TEXT("SEASON MATCH"); break;
        case EDigimonBattleKind::Ranked: Kind=TEXT("RANKED ARENA"); break;
        case EDigimonBattleKind::Story: Kind=TEXT("STORY BATTLE"); break;
        case EDigimonBattleKind::Friendly: Kind=TEXT("LIVE UNRANKED"); break;
        default: Kind=TEXT("TAMER BATTLE"); break;
    }
    BattleTitle->SetText(FText::FromString(Kind));
    const FDigimonBattleTeam& ActingTeam=DisplayState.ActingTeam==0 ? DisplayState.TeamA : DisplayState.TeamB;
    const FDigimonBattleUnit* Acting=ActingTeam.Active.IsValidIndex(DisplayState.ActingSlot) ? &ActingTeam.Active[DisplayState.ActingSlot] : nullptr;
    struct FUpcomingAction { const FDigimonBattleUnit* Unit = nullptr; DigimonVenomNXTTimelineCore::Entry Timer; };
    TArray<FUpcomingAction> Upcoming;
    const uint32 TimelineSeed=DigimonVenomNXTCombatCore::BattleSeed(DisplayState.BattleId.A,DisplayState.BattleId.B,DisplayState.BattleId.C,DisplayState.BattleId.D);
    for (int32 TeamIndex=0; TeamIndex<2; ++TeamIndex)
    {
        const FDigimonBattleTeam& Team=TeamIndex==0 ? DisplayState.TeamA : DisplayState.TeamB;
        for (const FDigimonBattleUnit& Candidate : Team.Active)
        {
            if (Candidate.HP<=0 || Candidate.bDefeated) continue;
            const double NextAt=&Candidate==Acting ? DigimonVenomNXTTimelineCore::NextTime(DisplayState.BattleClock,Candidate.Stats.Speed) : Candidate.NextActionTime;
            Upcoming.Add({&Candidate,DigimonVenomNXTTimelineCore::MakeEntry(TimelineSeed,TeamIndex,Candidate.TimelineOrder,Candidate.Stats.Speed,NextAt)});
        }
    }
    FString Timeline=Acting ? TEXT("NOW: ")+Acting->DisplayName : TEXT("RESOLVING");
    for (int32 I=0; I<2 && Upcoming.Num()>0; ++I)
    {
        Upcoming.Sort([](const FUpcomingAction& A,const FUpcomingAction& B){ return DigimonVenomNXTTimelineCore::EntryPrecedes(A.Timer,B.Timer); });
        Timeline+=(I==0 ? TEXT("  /  UP NEXT: ") : TEXT(" → "))+Upcoming[0].Unit->DisplayName;
        DigimonVenomNXTTimelineCore::Reschedule(Upcoming[0].Timer,Upcoming[0].Timer.NextAt,Upcoming[0].Unit->Stats.Speed);
    }
    BattleSubtitle->SetText(FText::FromString(DisplayState.bFinished && !IsPresentationBusy() ? TEXT("RESULT SAVED  /  RETURN WHEN READY") : Timeline));
    BattleSubtitle->SetToolTipText(FText::FromString(TEXT("Action order uses each living partner's speed timer. Faster partners act more often. Switching, defeats and reserve promotions can change who acts next.")));
    TurnText->SetText(FText::FromString(DisplayState.bFinished && !IsPresentationBusy() ? TEXT("MATCH COMPLETE") : FString::Printf(TEXT("ACTION %d"),DisplayState.TurnNumber)));
    TurnText->SetToolTipText(FText::FromString(TEXT("Command the highlighted partner when its speed timer is ready. SPD determines action frequency, including extra turns. Guard lasts until that partner's next action.")));
    RefreshTeam(Ours,true,TeamAVisuals);
    RefreshTeam(Theirs,false,TeamBVisuals);
    RefreshParty(Ours);
    RefreshCommands(Ours);
    if (!IsPresentationBusy() && !DisplayState.LastEvent.IsEmpty())
        EventText->SetText(FText::FromString(DisplayState.bFinished ? TEXT("Read your full result above, then return when you are ready.") : DisplayState.LastEvent));
    BP_OnBattleRefreshed(DisplayState);
}

void UDigimonVenomNXTBattleWidget::AppendBattleLog(const FString& Text)
{
    if (Text.IsEmpty()) return;
    BattleLog.Add(Text);
    while (BattleLog.Num()>50) BattleLog.RemoveAt(0);
    if (LogText) LogText->SetText(FText::FromString(FString::Join(BattleLog,TEXT("\n"))));
    if (LogScroll) LogScroll->ScrollToEnd();
}

void UDigimonVenomNXTBattleWidget::HandleBattleStateChanged(const FDigimonBattleState& NewState)
{
    if (!bHasDisplayState)
    {
        DisplayState=NewState;
        bHasDisplayState=true;
        if (!NewState.bFinished && NewState.BattleId.IsValid())
            if (UDigimonVenomNXTAudioSubsystem* Audio=GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
                Audio->PlayCueOnce(EDigimonAudioCue::Encounter,TEXT("battle-enter:")+NewState.BattleId.ToString());
    }
    // Reliable presentation packets and property replication can deliver the same serial.
    // A late duplicate must not roll the screen or its terminal state backwards.
    if (NewState.PresentationSerial<SeenPresentationSerial) return;
    LatestState=NewState;
    QueuePresentationEvents(NewState);
    if (!IsPresentationBusy())
    {
        DisplayState=LatestState;
        SyncSubmittedSlots();
    }
    Refresh();
}

void UDigimonVenomNXTBattleWidget::QueuePresentationEvents(const FDigimonBattleState& NewState)
{
    if (NewState.PresentationSerial<=SeenPresentationSerial) return;
    SeenPresentationSerial=NewState.PresentationSerial;
    for (const FDigimonBattlePresentationEvent& Event : NewState.PresentationEvents) PendingPresentationEvents.Add(Event);
    if (!bPresentationAnimating) StartNextPresentationEvent();
}

void UDigimonVenomNXTBattleWidget::StartNextPresentationEvent()
{
    ResetPresentationTransforms();
    if (PendingPresentationEvents.Num()==0)
    {
        bPresentationAnimating=false;
        DisplayState=LatestState;
        SyncSubmittedSlots();
        CommandTab=0;
        Refresh();
        return;
    }
    ActivePresentationEvent=PendingPresentationEvents[0];
    PendingPresentationEvents.RemoveAt(0);
    ActiveHPRecovery=ActiveSPRecovery=0;
    if (ActivePresentationEvent.Action==EDigimonBattleAction::Item && ActivePresentationEvent.bHasPostState)
    {
        const FDigimonBattleTeam& Before=ActivePresentationEvent.ActingTeam==0 ? DisplayState.TeamA : DisplayState.TeamB;
        const FDigimonBattleTeam& After=ActivePresentationEvent.ActingTeam==0 ? ActivePresentationEvent.PostTeamA : ActivePresentationEvent.PostTeamB;
        const int32 EventActorSlot=ActivePresentationEvent.ActingSlot;
        if (Before.Active.IsValidIndex(EventActorSlot) && After.Active.IsValidIndex(EventActorSlot) && Before.Active[EventActorSlot].InstanceId==After.Active[EventActorSlot].InstanceId)
        {
            ActiveHPRecovery=FMath::Max(0,After.Active[EventActorSlot].HP-Before.Active[EventActorSlot].HP);
            ActiveSPRecovery=FMath::Max(0,After.Active[EventActorSlot].SP-Before.Active[EventActorSlot].SP);
        }
    }
    PresentationAnimTime=0;
    bImpactApplied=false;
    bActionPositionsCached=false;
    bPresentationAnimating=true;
    DisplayState.bFinished=false;
    DisplayState.TurnNumber=ActivePresentationEvent.TurnNumber>0 ? ActivePresentationEvent.TurnNumber : LatestState.TurnNumber;
    CommandTab=0;
    const int32 OurTeam=bVisualOursAreOriginalB ? 1 : 0;
    if (ActivePresentationEvent.ActingTeam==OurTeam) SelectedActor=ActivePresentationEvent.ActingSlot;
    if (ActivePresentationEvent.TargetTeam!=OurTeam && ActivePresentationEvent.TargetSlot!=INDEX_NONE)
        SelectedTarget=ActivePresentationEvent.TargetSlot;
    if (EventText && !ActivePresentationEvent.Text.IsEmpty()) EventText->SetText(FText::FromString(ActivePresentationEvent.Text));
    PlayPresentationCue(false);
    Refresh();
    const bool bAttack = ActivePresentationEvent.Action == EDigimonBattleAction::Attack ||
        (ActivePresentationEvent.Action >= EDigimonBattleAction::Move1 && ActivePresentationEvent.Action <= EDigimonBattleAction::Move4);
    TArray<FDigimonBattleSlotVisual>& ActingVisuals = ActivePresentationEvent.ActingTeam == OurTeam ? TeamAVisuals : TeamBVisuals;
    if (bAttack && ActingVisuals.IsValidIndex(ActivePresentationEvent.ActingSlot))
        if (UDigimonVenomNXTAnimatedPortrait* Portrait = ActingVisuals[ActivePresentationEvent.ActingSlot].Portrait)
            Portrait->PlayAttack();
}

void UDigimonVenomNXTBattleWidget::PlayPresentationCue(bool bImpact)
{
    ULocalPlayer* Local=GetOwningLocalPlayer();
    UDigimonVenomNXTAudioSubsystem* Audio=Local ? Local->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr;
    if (!Audio) return;
    const FDigimonBattlePresentationEvent& E=ActivePresentationEvent;
    const bool bOffensive=E.Action==EDigimonBattleAction::Attack || (E.Action>=EDigimonBattleAction::Move1 && E.Action<=EDigimonBattleAction::Move4);
    EDigimonAudioCue Cue=EDigimonAudioCue::Hit;
    if (!bImpact)
    {
        if (!bOffensive) return;
        Cue=E.DamageClass==EDigimonDamageClass::Special ? EDigimonAudioCue::SpecialAttack : EDigimonAudioCue::PhysicalAttack;
    }
    else if (bOffensive && E.Damage>0)
    {
        const FDigimonBattleTeam& After=E.TargetTeam==0 ? E.PostTeamA : E.PostTeamB;
        bool bKnockout=false;
        if (E.bHasPostState)
        {
            for (const FDigimonBattleUnit& Unit : After.Active) if (Unit.InstanceId==E.TargetInstanceId) bKnockout=Unit.HP<=0 || Unit.bDefeated;
            for (const FDigimonBattleUnit& Unit : After.Bench) if (Unit.InstanceId==E.TargetInstanceId) bKnockout=Unit.HP<=0 || Unit.bDefeated;
        }
        Cue=bKnockout ? EDigimonAudioCue::Knockout : E.bGuarded ? EDigimonAudioCue::Guard : E.Effectiveness>1.001f ? EDigimonAudioCue::EffectiveHit : EDigimonAudioCue::Hit;
    }
    else if (E.Action==EDigimonBattleAction::Guard) Cue=EDigimonAudioCue::Guard;
    else if (E.Action==EDigimonBattleAction::Item && (ActiveHPRecovery>0 || ActiveSPRecovery>0)) Cue=EDigimonAudioCue::Item;
    else if (E.Action==EDigimonBattleAction::Switch) Cue=EDigimonAudioCue::UINavigate;
    else return; // Flee is heard once when the confirmed terminal result becomes visible.
    const FString Receipt=FString::Printf(TEXT("battle:%s:%d:%d:%d:%s:%s:%s"), *LatestState.BattleId.ToString(), E.TurnNumber,
        E.ActingTeam, static_cast<int32>(E.Action), *E.ActingInstanceId.ToString(), *E.TargetInstanceId.ToString(), bImpact ? TEXT("impact") : TEXT("start"));
    Audio->PlayCueOnce(Cue,Receipt);
}

void UDigimonVenomNXTBattleWidget::ApplyPresentationImpact()
{
    if (bImpactApplied) return;
    bImpactApplied=true;
    PlayPresentationCue(true);
    if (ActivePresentationEvent.bHasPostState)
    {
        const FDigimonBattleTeam BeforeA=DisplayState.TeamA;
        const FDigimonBattleTeam BeforeB=DisplayState.TeamB;
        DisplayState.TeamA=ActivePresentationEvent.PostTeamA;
        DisplayState.TeamB=ActivePresentationEvent.PostTeamB;
        if (ActivePresentationEvent.Damage>0)
        {
            // A knockout can promote a reserve on the server in this same action.
            // Keep the defeated instance in its old slot through its hit animation;
            // show the promoted partner only when this action has fully returned home.
            auto HoldPromotions=[](FDigimonBattleTeam& After,const FDigimonBattleTeam& Before)
            {
                for (int32 I=0; I<Before.Active.Num() && I<After.Active.Num(); ++I)
                {
                    const FGuid Id=Before.Active[I].InstanceId;
                    if (After.Active[I].InstanceId==Id) continue;
                    const int32 PreviousBench=After.Bench.IndexOfByPredicate([&](const FDigimonBattleUnit& Unit){ return Unit.InstanceId==Id; });
                    if (PreviousBench!=INDEX_NONE) Swap(After.Active[I],After.Bench[PreviousBench]);
                }
            };
            HoldPromotions(DisplayState.TeamA,BeforeA);
            HoldPromotions(DisplayState.TeamB,BeforeB);
        }
    }
    else if (ActivePresentationEvent.TargetTeam!=INDEX_NONE)
    {
        // Compatibility for Blueprint-created events that predate the snapshot protocol.
        FDigimonBattleTeam& Target=ActivePresentationEvent.TargetTeam==0 ? DisplayState.TeamA : DisplayState.TeamB;
        if (Target.Active.IsValidIndex(ActivePresentationEvent.TargetSlot))
        {
            FDigimonBattleUnit& Unit=Target.Active[ActivePresentationEvent.TargetSlot];
            Unit.HP=FMath::Max(0,Unit.HP-ActivePresentationEvent.Damage);
            Unit.bDefeated=Unit.HP<=0;
        }
    }
    DisplayState.bFinished=false;
    DisplayState.LastEvent=ActivePresentationEvent.Text;
    AppendBattleLog(ActivePresentationEvent.Text);
    Refresh();
}

UBorder* UDigimonVenomNXTBattleWidget::ResolveVisualCard(int32 OriginalTeamIndex,int32 SlotIndex) const
{
    if (OriginalTeamIndex==INDEX_NONE || SlotIndex==INDEX_NONE) return nullptr;
    const int32 Ours=bVisualOursAreOriginalB ? 1 : 0;
    const TArray<FDigimonBattleSlotVisual>& Visuals=OriginalTeamIndex==Ours ? TeamAVisuals : TeamBVisuals;
    return Visuals.IsValidIndex(SlotIndex) ? Visuals[SlotIndex].SpriteHost.Get() : nullptr;
}

void UDigimonVenomNXTBattleWidget::NativeTick(const FGeometry& MyGeometry,float InDeltaTime)
{
    Super::NativeTick(MyGeometry,InDeltaTime);
    if (TurnText && Battle.IsValid() && DisplayState.Kind==EDigimonBattleKind::Friendly && !DisplayState.bFinished)
    {
        const AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
        const float Now = GS ? GS->GetServerWorldTimeSeconds() : GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
        const int32 Remaining = FMath::Max(0, FMath::CeilToInt(Battle->UnrankedDecisionDeadlineServerTime - Now));
        TurnText->SetText(FText::FromString(Battle->bUnrankedResultSaving ? TEXT("SAVING RESULT") : FString::Printf(TEXT("ACTION %d  /  %ds"),DisplayState.TurnNumber,Remaining)));
        TurnText->SetToolTipText(FText::FromString(TEXT("Choose an action before the server deadline. Expiry counts as a loss. Each decision gets 90 seconds plus time for queued battle animations.")));
    }
    if (!bPresentationAnimating) return;
    using namespace DigimonBattleUI;
    PresentationAnimTime+=InDeltaTime;
    UBorder* Attacker=ResolveVisualCard(ActivePresentationEvent.ActingTeam,ActivePresentationEvent.ActingSlot);
    UBorder* Target=ResolveVisualCard(ActivePresentationEvent.TargetTeam,ActivePresentationEvent.TargetSlot);
    const bool Offensive=ActivePresentationEvent.Action==EDigimonBattleAction::Attack ||
        (ActivePresentationEvent.Action>=EDigimonBattleAction::Move1 && ActivePresentationEvent.Action<=EDigimonBattleAction::Move4);
    // The displacement is calculated in arena coordinates, so attacks remain vertical
    // (with a diagonal component for another column) at every viewport scale.
    if (!bActionPositionsCached && PresentationOverlay)
    {
        ActionStartCenter=FVector2D(ArenaWidth*0.5f,ArenaHeight*0.75f);
        ActionTargetCenter=FVector2D(ArenaWidth*0.5f,ArenaHeight*0.25f);
        if (Attacker)
        {
            const FGeometry& G=Attacker->GetCachedGeometry();
            ActionStartCenter=PresentationOverlay->GetCachedGeometry().AbsoluteToLocal(G.LocalToAbsolute(G.GetLocalSize()*0.5f));
        }
        if (Target)
        {
            const FGeometry& G=Target->GetCachedGeometry();
            ActionTargetCenter=PresentationOverlay->GetCachedGeometry().AbsoluteToLocal(G.LocalToAbsolute(G.GetLocalSize()*0.5f));
        }
        bActionPositionsCached=true;
    }
    const FVector2D TargetCenter=ActionTargetCenter;
    if (Attacker && Target && Offensive)
    {
        const float Phase=FMath::Clamp(PresentationAnimTime/0.60f,0.0f,1.0f);
        const float Curve=FMath::Sin(Phase*PI);
        Attacker->SetRenderTranslation((ActionTargetCenter-ActionStartCenter)*0.56f*Curve);
        const float Scale=1.0f+0.07f*Curve;
        Attacker->SetRenderScale(FVector2D(Scale,Scale));
    }
    if (PresentationAnimTime>=ImpactTime)
    {
        ApplyPresentationImpact();
        const float HitTime=PresentationAnimTime-ImpactTime;
        if (Target && ActivePresentationEvent.Damage>0)
        {
            const float Fade=FMath::Max(0.0f,1.0f-HitTime/0.36f);
            Target->SetRenderTranslation(FVector2D(FMath::Sin(HitTime*85.0f)*5.0f*Fade,0));
            Target->SetRenderOpacity(1.0f-0.35f*Fade);
            const FVector2D Offset=TargetCenter-FVector2D(ArenaWidth,ArenaHeight)*0.5f;
            ImpactText->SetText(FText::FromString(FString::Printf(TEXT("−%d"),ActivePresentationEvent.Damage)));
            ImpactText->SetColorAndOpacity(ActivePresentationEvent.Effectiveness>1.001f ? Gold : ActivePresentationEvent.Effectiveness<0.999f ? Muted : Text);
            ImpactText->SetRenderTranslation(Offset+FVector2D(0,-50.0f-HitTime*45.0f));
            ImpactText->SetRenderOpacity(FMath::Max(0.0f,1.0f-HitTime/0.49f));
            // These annotations use the recorded authoritative result. No random
            // rolls or damage calculation occur while replaying an impact.
            FString Details;
            if (!FMath::IsNearlyEqual(ActivePresentationEvent.Effectiveness,1.0f))
                Details=DigimonVenomNXTCombatUI::MatchupLabel(ActivePresentationEvent.Effectiveness);
            if (ActivePresentationEvent.ComboMultiplier>1.0f)
                Details+=(Details.IsEmpty() ? TEXT("") : TEXT("\n"))+FString::Printf(TEXT("TEAM COMBO ×%s"),*FString::SanitizeFloat(ActivePresentationEvent.ComboMultiplier,0));
            if (ActivePresentationEvent.bGuarded)
                Details+=(Details.IsEmpty() ? TEXT("") : TEXT("\n"))+FString(TEXT("GUARDED · HALF DAMAGE"));
            ImpactDetail->SetText(FText::FromString(Details));
            ImpactDetail->SetColorAndOpacity(Muted);
            ImpactDetail->SetRenderTranslation(Offset+FVector2D(0,-15.0f-HitTime*45.0f));
            ImpactDetail->SetRenderOpacity(FMath::Max(0.0f,1.0f-HitTime/0.49f));
            if (ImpactFrames.Num()>0)
            {
                const int32 Frame=FMath::Clamp(FMath::FloorToInt(HitTime*12.5f),0,ImpactFrames.Num()-1);
                ImpactImage->SetBrushFromTexture(ImpactFrames[Frame]);
                ImpactImage->SetDesiredSizeOverride(FVector2D(176,160));
                ImpactImage->SetVisibility(ESlateVisibility::HitTestInvisible);
                ImpactImage->SetRenderTranslation(Offset);
                ImpactImage->SetRenderOpacity(FMath::Max(0.0f,1.0f-HitTime/0.42f));
            }
        }
        else if (Target && !Offensive)
        {
            const float Scale=1.0f+FMath::Sin(FMath::Clamp(HitTime/0.3f,0.0f,1.0f)*PI)*0.06f;
            Target->SetRenderScale(FVector2D(Scale,Scale));
            if (ActiveHPRecovery>0 || ActiveSPRecovery>0)
            {
                const FVector2D Offset=TargetCenter-FVector2D(ArenaWidth,ArenaHeight)*0.5f;
                ImpactText->SetText(FText::FromString(FString::Printf(TEXT("+%d %s"),ActiveHPRecovery>0 ? ActiveHPRecovery : ActiveSPRecovery,ActiveHPRecovery>0 ? TEXT("HP") : TEXT("SP"))));
                ImpactText->SetColorAndOpacity(ActiveHPRecovery>0 ? HP : Cyan);
                ImpactText->SetRenderTranslation(Offset+FVector2D(0,-48.0f-HitTime*52.0f));
                ImpactText->SetRenderOpacity(FMath::Max(0.0f,1.0f-HitTime/0.49f));
                ImpactDetail->SetText(FText::FromString(TEXT("+   +   +")));
                ImpactDetail->SetColorAndOpacity(HP);
                ImpactDetail->SetRenderTranslation(Offset+FVector2D(0,-10.0f-HitTime*76.0f));
                ImpactDetail->SetRenderOpacity(FMath::Max(0.0f,1.0f-HitTime/0.49f));
            }
        }
    }
    if (PresentationAnimTime>=ActionDuration)
    {
        ApplyPresentationImpact();
        if (ActivePresentationEvent.bHasPostState)
        {
            DisplayState.TeamA=ActivePresentationEvent.PostTeamA;
            DisplayState.TeamB=ActivePresentationEvent.PostTeamB;
        }
        bPresentationAnimating=false;
        StartNextPresentationEvent();
    }
}

void UDigimonVenomNXTBattleWidget::ResetPresentationTransforms()
{
    for (TArray<FDigimonBattleSlotVisual>* Team : {&TeamAVisuals,&TeamBVisuals})
        for (FDigimonBattleSlotVisual& V : *Team)
            if (V.SpriteHost)
            {
                V.SpriteHost->SetRenderTranslation(FVector2D::ZeroVector);
                V.SpriteHost->SetRenderScale(FVector2D(1,1));
                V.SpriteHost->SetRenderOpacity(1);
            }
    if (ImpactText) { ImpactText->SetRenderOpacity(0); ImpactText->SetRenderTranslation(FVector2D::ZeroVector); }
    if (ImpactDetail) { ImpactDetail->SetRenderOpacity(0); ImpactDetail->SetRenderTranslation(FVector2D::ZeroVector); }
    if (ImpactImage) { ImpactImage->SetVisibility(ESlateVisibility::Collapsed); ImpactImage->SetRenderTranslation(FVector2D::ZeroVector); }
}

void UDigimonVenomNXTBattleWidget::SyncSubmittedSlots()
{
    SubmittedSlots.Reset();
    if (DisplayState.bAutomatic) return;
    const int32 OurTeam=bVisualOursAreOriginalB ? 1 : 0;
    const FDigimonBattleTeam& Team=bVisualOursAreOriginalB ? DisplayState.TeamB : DisplayState.TeamA;
    if (DisplayState.ActingTeam==OurTeam && Team.Active.IsValidIndex(DisplayState.ActingSlot))
        SelectedActor=DisplayState.ActingSlot;
}

void UDigimonVenomNXTBattleWidget::AdvanceSelectedActor()
{
    // The server's speed timeline chooses the next actor. A local round-robin
    // selection would command the wrong partner when speed grants an extra turn.
    if (DisplayState.ActingTeam==(bVisualOursAreOriginalB ? 1 : 0))
        SelectedActor=DisplayState.ActingSlot;
}

void UDigimonVenomNXTBattleWidget::HandleAction(const FString& Action,int32 Payload)
{
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    if (!PC || !Battle.IsValid()) return;
    if (Action==TEXT("leave"))
    {
        if (DisplayState.bFinished && !IsPresentationBusy()) PC->ServerLeaveFinishedBattle();
        return;
    }
    if (Action==TEXT("keep_battling")) { bConfirmUnrankedSurrender=false; Refresh(); return; }
    if (Action==TEXT("surrender") && DisplayState.Kind==EDigimonBattleKind::Friendly && !DisplayState.bFinished && !Battle->bUnrankedResultSaving)
    {
        if (!bConfirmUnrankedSurrender) { bConfirmUnrankedSurrender=true; Refresh(); return; }
        bConfirmUnrankedSurrender=false;
        if (auto* Component=PC->FindComponentByClass<UDigimonVenomNXTUnrankedComponent>()) Component->ServerForfeit();
        return;
    }
    if (IsPresentationBusy() || DisplayState.bFinished || IsAutomaticBattle()) return;
    const FDigimonBattleTeam& Ours=bVisualOursAreOriginalB ? DisplayState.TeamB : DisplayState.TeamA;
    const FDigimonBattleTeam& Theirs=bVisualOursAreOriginalB ? DisplayState.TeamA : DisplayState.TeamB;
    if (Action==TEXT("target"))
    {
        if (Theirs.Active.IsValidIndex(Payload) && !Theirs.Active[Payload].bDefeated && Theirs.Active[Payload].HP>0)
            SelectedTarget=Payload;
        Refresh(); return;
    }
    if (Action==TEXT("actor") || (Action==TEXT("link") && Payload<Ours.Active.Num()))
    {
        if (DisplayState.ActingTeam==(bVisualOursAreOriginalB ? 1 : 0) && Payload==DisplayState.ActingSlot && Ours.Active.IsValidIndex(Payload) && !Ours.Active[Payload].bDefeated && Ours.Active[Payload].HP>0)
            SelectedActor=Payload;
        Refresh(); return;
    }
    if (Action==TEXT("matchup_help")) { CommandTab=CommandTab==3 ? 0 : 3; Refresh(); return; }
    if (Action==TEXT("skills")) { CommandTab=CommandTab==1 ? 0 : 1; Refresh(); return; }
    if (Action==TEXT("items")) { CommandTab=CommandTab==2 ? 0 : 2; Refresh(); return; }
    if (Action==TEXT("close_tray")) { CommandTab=0; Refresh(); return; }
    if (DisplayState.ActingTeam!=(bVisualOursAreOriginalB ? 1 : 0) || SelectedActor!=DisplayState.ActingSlot ||
        !Ours.Active.IsValidIndex(SelectedActor) || Ours.Active[SelectedActor].bDefeated || SubmittedSlots.Contains(SelectedActor)) return;
    FDigimonBattleCommand Command;
    Command.ExpectedBattleId=DisplayState.BattleId;
    Command.ExpectedTurnNumber=DisplayState.TurnNumber;
    Command.ActingSlot=SelectedActor;
    Command.TargetSlot=SelectedTarget;
    if (Action==TEXT("attack")) Command.Action=EDigimonBattleAction::Attack;
    else if (Action==TEXT("move"))
    {
        const FDigimonBattleUnit& Unit=Ours.Active[SelectedActor];
        if (!Unit.Moves.IsValidIndex(Payload) || Payload>=4 || Unit.SP<Unit.Moves[Payload].SPCost) return;
        Command.Action=static_cast<EDigimonBattleAction>(static_cast<int32>(EDigimonBattleAction::Move1)+Payload);
    }
    else if (Action.StartsWith(TEXT("item:")))
    { Command.Action=EDigimonBattleAction::Item; Command.ItemId=FName(*Action.Mid(5)); }
    else if (Action==TEXT("link"))
    {
        Command.Action=EDigimonBattleAction::Switch;
        Command.SwitchBenchIndex=Payload-Ours.Active.Num();
        if (!Ours.Bench.IsValidIndex(Command.SwitchBenchIndex) || Ours.Bench[Command.SwitchBenchIndex].bDefeated || Ours.Bench[Command.SwitchBenchIndex].HP<=0) return;
    }
    else if (Action==TEXT("guard")) Command.Action=EDigimonBattleAction::Guard;
    else if (Action==TEXT("retreat"))
    {
        if (DisplayState.Kind!=EDigimonBattleKind::Wild) return;
        Command.Action=EDigimonBattleAction::Retreat;
    }
    else return;
    if ((Command.Action==EDigimonBattleAction::Attack || (Command.Action>=EDigimonBattleAction::Move1 && Command.Action<=EDigimonBattleAction::Move4)) && SelectedTarget==INDEX_NONE) return;
    // This is only a local readiness marker. Validation, items and all combat math stay on the server.
    SubmittedSlots.Add(SelectedActor);
    CommandTab=0;
    PC->ServerSubmitBattleCommand(Command);
    // A listen-server acknowledgement may already have selected the next partner
    // synchronously inside the RPC; do not skip that partner a second time.
    if (!IsPresentationBusy() && SelectedActor == Command.ActingSlot) AdvanceSelectedActor();
    Refresh();
}
