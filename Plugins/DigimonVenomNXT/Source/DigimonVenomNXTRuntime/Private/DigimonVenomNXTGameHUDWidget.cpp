#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTCommunityWidget.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTStarterCore.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTTamerStudioWidget.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTEvolutionWidget.h"
#include "DigimonVenomNXTDigiDexWidget.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTPartyWidget.h"
#include "DigimonVenomNXTFieldPartyWidget.h"
#include "DigimonVenomNXTWorldChatWidget.h"
#include "DigimonVenomNXTDigiLabWidget.h"
#include "DigimonVenomNXTVideoSettingsWidget.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTServerConsoleWidget.h"
#include "DigimonVenomNXTPresentationAssets.h"
#include "DigimonVenomNXTFarmWidget.h"
#include "DigimonVenomNXTFarmScene.h"
#include "DigimonVenomNXTSeasonWidget.h"
#include "DigimonVenomNXTRelayWidget.h"
#include "DigimonVenomNXTChroniclesWidget.h"
#include "DigimonVenomNXTGhostLineWidget.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTChronicles.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/ScrollBox.h"
#include "Components/ScaleBox.h"
#include "Components/ScaleBoxSlot.h"
#include "Components/ProgressBar.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "Components/SizeBox.h"
#include "Components/Slider.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Texture2D.h"
#include "Engine/LocalPlayer.h"
#include "InputCoreTypes.h"

namespace DigimonHUDUI
{
    static const FLinearColor Panel(0.015f, 0.035f, 0.075f, 0.94f);
    static const FLinearColor Panel2(0.025f, 0.075f, 0.12f, 0.94f);
    static const FLinearColor Accent(0.02f, 0.87f, 0.92f, 1.0f);
    static const FLinearColor Purple(0.69f, 0.32f, 1.0f, 1.0f);
    static const FLinearColor Gold(1.0f, 0.72f, 0.14f, 1.0f);
    static const FLinearColor Text(0.94f, 0.98f, 1.0f, 1.0f);
    static const FLinearColor Muted(0.69f, 0.79f, 0.86f, 1.0f);

    UTextBlock* T(UWidgetTree* Tree, const FString& Value, int32 Size=15, FLinearColor Color=Text, bool Bold=false)
    {
        UTextBlock* Out = Tree->ConstructWidget<UTextBlock>();
        Out->SetText(FText::FromString(Value));
        Out->SetColorAndOpacity(FSlateColor(Color));
        Out->SetAutoWrapText(true);
        FSlateFontInfo Font = Out->GetFont(); Font.Size = Size; Font.TypefaceFontName = Bold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Out->SetFont(Font);
        return Out;
    }

    void Add(UVerticalBox* Box, UWidget* W, float P=4.0f)
    {
        if (UVerticalBoxSlot* Slot = Box->AddChildToVerticalBox(W)) { Slot->SetPadding(FMargin(0,P)); Slot->SetHorizontalAlignment(HAlign_Fill); }
    }

    UDigimonVenomNXTActionButton* Action(UWidgetTree* Tree, const FString& Label, const FString& Command, int32 Payload=0, FLinearColor Color=Accent)
    {
        UDigimonVenomNXTActionButton* B = Tree->ConstructWidget<UDigimonVenomNXTActionButton>();
        DigimonVenomNXTUI::StyleButton(B, Color);
        B->InitializeAction(Command, Payload);
        UTextBlock* LabelWidget = T(Tree, Label, 14, Text, true);
        LabelWidget->SetJustification(ETextJustify::Center);
        B->SetToolTipText(FText::FromString(Label));
        B->AddChild(LabelWidget);
        return B;
    }

    UBorder* Card(UWidgetTree* Tree, FLinearColor Color=Panel2)
    {
        UBorder* B = Tree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(B, Color); return B;
    }

    UDigimonVenomNXTActionButton* FindFocusedAction(UWidget* Widget, APlayerController* Owner)
    {
        if (UDigimonVenomNXTActionButton* Button = Cast<UDigimonVenomNXTActionButton>(Widget))
            if (Button->HasUserFocus(Owner)) return Button;
        if (UUserWidget* UserWidget = Cast<UUserWidget>(Widget))
            if (UDigimonVenomNXTActionButton* Found = FindFocusedAction(UserWidget->GetRootWidget(), Owner)) return Found;
        if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(Widget))
            for (int32 Index = 0; Index < PanelWidget->GetChildrenCount(); ++Index)
                if (UDigimonVenomNXTActionButton* Found = FindFocusedAction(PanelWidget->GetChildAt(Index), Owner)) return Found;
        return nullptr;
    }

    UDigimonVenomNXTActionButton* FindAction(UWidget* Widget, const FString& Command, int32 Payload)
    {
        if (UDigimonVenomNXTActionButton* Button = Cast<UDigimonVenomNXTActionButton>(Widget))
            if (Button->Action == Command && Button->Payload == Payload && Button->GetIsEnabled()) return Button;
        if (UUserWidget* UserWidget = Cast<UUserWidget>(Widget))
            if (UDigimonVenomNXTActionButton* Found = FindAction(UserWidget->GetRootWidget(), Command, Payload)) return Found;
        if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(Widget))
            for (int32 Index = 0; Index < PanelWidget->GetChildrenCount(); ++Index)
                if (UDigimonVenomNXTActionButton* Found = FindAction(PanelWidget->GetChildAt(Index), Command, Payload)) return Found;
        return nullptr;
    }

    UTexture2D* LoadMapTexture(int32 MapId)
    {
        return UDigimonVenomNXTMapAssetRevision::LoadMapTexture(MapId);
    }

    UTexture2D* LoadTamerThumbnail(const FString& Style)
    {
        const FString Path = DigimonVenomNXTTamers::ThumbnailPath(FName(*Style));
        return Path.IsEmpty() ? nullptr : LoadObject<UTexture2D>(nullptr, *Path, nullptr, LOAD_NoWarn | LOAD_Quiet);
    }

    UTexture2D* LoadPresentationTexture(const FString& Asset)
    {
        return LoadObject<UTexture2D>(nullptr, *FString::Printf(TEXT("/DigimonVenomNXT/Generated/UI/Presentation/%s.%s"), *Asset, *Asset));
    }

    USizeBox* TextureBox(UWidgetTree* Tree, UTexture2D* Texture, float Width, float Height)
    {
        return DigimonVenomNXTUI::Texture(Tree, Texture, Width, Height);
    }
}

void UDigimonVenomNXTGameHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    BuildNativeUI();
}

void UDigimonVenomNXTGameHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildNativeUI();
    if (const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
    {
        if (FieldWorldChat) FieldWorldChat->SetHistory(PC->WorldChatHistory);
        if (MenuWorldChat) MenuWorldChat->SetHistory(PC->WorldChatHistory);
    }
    BindPlayerState();
    RefreshAll();
    SyncMenuMusic();
}

void UDigimonVenomNXTGameHUDWidget::NativeDestruct()
{
    ReleaseWorldChatFocus();
    if (ServerConsole) ServerConsole->CloseConsole();
    SetLogoutConfirmation(false);
    if (VideoSettings) VideoSettings->CloseSettings();
    CommitAudioVolumes();
    // A removed HUD no longer owns a music layer, even if its menu was open.
    if (ULocalPlayer* Player = GetOwningLocalPlayer())
        if (UDigimonVenomNXTAudioSubsystem* Audio = Player->GetSubsystem<UDigimonVenomNXTAudioSubsystem>()) Audio->ClearUIScreenMusic(this);
    if (BoundPlayerState.IsValid()) BoundPlayerState->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleProfileChanged);
    if (BoundGameState.IsValid()) BoundGameState->OnServerStateChanged.RemoveDynamic(this, &UDigimonVenomNXTGameHUDWidget::RefreshLivePages);
    BoundPlayerState.Reset();
    BoundGameState.Reset();
    Super::NativeDestruct();
}

FReply UDigimonVenomNXTGameHUDWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if ((InKeyEvent.GetKey() == EKeys::Escape || InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right) && HandleCommunityBack()) return FReply::Handled();
    if (bLogoutConfirmationOpen && (InKeyEvent.GetKey() == EKeys::Escape || InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right))
    {
        HandleLogoutConfirmationBack();
        return FReply::Handled();
    }
    return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UDigimonVenomNXTGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    RefreshFarmPresentation();
    RefreshFieldPartyPresentation();
    RefreshWorldChatPresentation();
    RefreshAccumulator += InDeltaTime;
    if (ToastSecondsRemaining > 0.0f)
    {
        ToastSecondsRemaining -= InDeltaTime;
        if (ToastSecondsRemaining <= 0.0f && ToastText) ToastText->SetText(FText::GetEmpty());
    }
    if (bMenuOpen)
    {
        LiveRefreshAccumulator += InDeltaTime;
        if (LiveRefreshAccumulator >= 5.0f) { LiveRefreshAccumulator = 0.0f; RequestLivePage(); }
    }
    if (RefreshAccumulator >= 0.5f)
    {
        RefreshAccumulator = 0.0f;
        BindPlayerState();
        RefreshSessionControls();
        RefreshHeader();
        RefreshRelayFieldHUD();
        RefreshFarmPresentation(true);
        RefreshFieldPartyPresentation(true);
        if (bMenuOpen) RefreshLiveTimers();
    }
}

ADigimonVenomNXTPlayerState* UDigimonVenomNXTGameHUDWidget::GetDigimonPlayerState() const
{
    const APlayerController* PC = GetOwningPlayer();
    return PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
}

void UDigimonVenomNXTGameHUDWidget::BindPlayerState()
{
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    ADigimonVenomNXTGameState* GS = GetWorld() ? GetWorld()->GetGameState<ADigimonVenomNXTGameState>() : nullptr;
    if (BoundGameState.Get() != GS)
    {
        if (BoundGameState.IsValid()) BoundGameState->OnServerStateChanged.RemoveDynamic(this, &UDigimonVenomNXTGameHUDWidget::RefreshLivePages);
        BoundGameState = GS;
        if (GS)
        {
            GS->OnServerStateChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::RefreshLivePages);
            // The initial replicated catalog can arrive before this HUD binds.
            RefreshLivePages();
        }
    }
    if (BoundPlayerState.Get() == PS) return;
    if (BoundPlayerState.IsValid()) BoundPlayerState->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleProfileChanged);
    BoundPlayerState = PS;
    if (PS)
    {
        PS->OnProfileChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleProfileChanged);
        HandleProfileChanged();
    }
}

void UDigimonVenomNXTGameHUDWidget::BuildNativeUI()
{
    if (bBuilt || !WidgetTree) return;
    bBuilt = true;
    using namespace DigimonHUDUI;

    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>();
    Root->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    WidgetTree->RootWidget = Root;

    // Minimal exploration HUD: the map and character own the screen. Only compact status remains.
    USizeBox* CompactSize = WidgetTree->ConstructWidget<USizeBox>();
    CompactSize->SetWidthOverride(560.0f);
    CompactSize->SetHeightOverride(86.0f);
    if (UOverlaySlot* CompactOverlaySlot = Root->AddChildToOverlay(CompactSize))
    {
        CompactOverlaySlot->SetHorizontalAlignment(HAlign_Left);
        CompactOverlaySlot->SetVerticalAlignment(VAlign_Top);
        CompactOverlaySlot->SetPadding(FMargin(18.0f));
    }
    CompactHUDRoot = Card(WidgetTree, FLinearColor(0.006f,0.018f,0.035f,0.84f));
    CompactHUDRoot->SetPadding(FMargin(10.0f));
    CompactSize->AddChild(CompactHUDRoot);
    UHorizontalBox* CompactRow = WidgetTree->ConstructWidget<UHorizontalBox>();
    CompactHUDRoot->SetContent(CompactRow);
    USizeBox* LeadSize = WidgetTree->ConstructWidget<USizeBox>();
    LeadSize->SetWidthOverride(64.0f); LeadSize->SetHeightOverride(64.0f);
    CompactLeadImage = WidgetTree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>();
    UScaleBox* LeadScale = WidgetTree->ConstructWidget<UScaleBox>();
    LeadScale->SetStretch(EStretch::ScaleToFit);
    LeadScale->AddChild(CompactLeadImage);
    LeadSize->AddChild(LeadScale);
    if (UHorizontalBoxSlot* S = CompactRow->AddChildToHorizontalBox(LeadSize)) { S->SetPadding(FMargin(0,0,10,0)); S->SetVerticalAlignment(VAlign_Center); }
    UVerticalBox* CompactText = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UHorizontalBoxSlot* S = CompactRow->AddChildToHorizontalBox(CompactText)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
    HeaderIdentity = T(WidgetTree, TEXT("DIGIMON VENOM NXT"), 17, Accent, true);
    HeaderWorld = T(WidgetTree, TEXT("Map 1"), 13, Text, true);
    HeaderEconomy = T(WidgetTree, TEXT("0 Credits"), 12, Gold, false);
    HeaderRubies = T(WidgetTree, TEXT("0 DigiRubies"), 12, Purple, false);
    HeaderIdentity->SetAutoWrapText(false); HeaderIdentity->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    HeaderWorld->SetAutoWrapText(false); HeaderWorld->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    HeaderEconomy->SetAutoWrapText(false); HeaderEconomy->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    Add(CompactText, HeaderIdentity, 0); Add(CompactText, HeaderWorld, 0);
    UHorizontalBox* Wallet = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(CompactText, Wallet, 0);
    Wallet->AddChildToHorizontalBox(DigimonVenomNXTUI::CurrencyIcon(WidgetTree, false, 22, 22));
    if (UHorizontalBoxSlot* WalletCreditSlot = Wallet->AddChildToHorizontalBox(HeaderEconomy)) { WalletCreditSlot->SetPadding(FMargin(4, 0, 12, 0)); WalletCreditSlot->SetVerticalAlignment(VAlign_Center); }
    Wallet->AddChildToHorizontalBox(DigimonVenomNXTUI::CurrencyIcon(WidgetTree, true, 22, 22));
    if (UHorizontalBoxSlot* WalletRubySlot = Wallet->AddChildToHorizontalBox(HeaderRubies)) { WalletRubySlot->SetPadding(FMargin(4, 0)); WalletRubySlot->SetVerticalAlignment(VAlign_Center); }

    FieldHintText = T(WidgetTree, TEXT("WASD / ARROWS  Explore     L  DigiLab     M / TAB  Menu     Mouse Wheel  Zoom     H  Hide HUD"), 12, FLinearColor(0.80f,0.90f,0.96f,0.95f), true);
    FieldHintText->SetJustification(ETextJustify::Right);
    if (UOverlaySlot* HintOverlaySlot = Root->AddChildToOverlay(FieldHintText))
    {
        HintOverlaySlot->SetHorizontalAlignment(HAlign_Right);
        HintOverlaySlot->SetVerticalAlignment(VAlign_Bottom);
        HintOverlaySlot->SetPadding(FMargin(0,0,20,18));
    }

    // The six slots are retained; the outer fit scales the entire rail at short
    // viewport heights so reserves and the recovery shortcut never require scrolling.
    UScaleBox* FieldPartyFit = WidgetTree->ConstructWidget<UScaleBox>();
    FieldPartyFit->SetStretch(EStretch::ScaleToFit); FieldPartyFit->SetStretchDirection(EStretchDirection::DownOnly);
    FieldPartyFit->SetVisibility(ESlateVisibility::SelfHitTestInvisible); FieldPartyFrame = FieldPartyFit;
    if (UOverlaySlot* RailSlot = Root->AddChildToOverlay(FieldPartyFit))
    { RailSlot->SetHorizontalAlignment(HAlign_Right); RailSlot->SetVerticalAlignment(VAlign_Fill); RailSlot->SetPadding(FMargin(12, 18, 18, 62)); }
    USizeBox* RailBounds = WidgetTree->ConstructWidget<USizeBox>(); RailBounds->SetWidthOverride(304); RailBounds->SetHeightOverride(696); FieldPartyFit->AddChild(RailBounds);
    if (UScaleBoxSlot* RailFitSlot = Cast<UScaleBoxSlot>(RailBounds->Slot)) { RailFitSlot->SetHorizontalAlignment(HAlign_Right); RailFitSlot->SetVerticalAlignment(VAlign_Center); }
    FieldParty = CreateWidget<UDigimonVenomNXTFieldPartyWidget>(GetOwningPlayer(), UDigimonVenomNXTFieldPartyWidget::StaticClass());
    if (FieldParty) { FieldParty->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); RailBounds->AddChild(FieldParty); }
    FieldPartyFit->SetVisibility(ESlateVisibility::Collapsed);

    // WORLD remains anchored to the lower left, clear of the right-hand team rail.
    // Both chat views stay alive through menus, habitat travel and profile refreshes.
    FieldWorldChatFrame = WidgetTree->ConstructWidget<USizeBox>();
    FieldWorldChatFrame->SetWidthOverride(452.0f);
    if (UOverlaySlot* LayoutSlot = Root->AddChildToOverlay(FieldWorldChatFrame))
    {
        LayoutSlot->SetHorizontalAlignment(HAlign_Left);
        LayoutSlot->SetVerticalAlignment(VAlign_Bottom);
        LayoutSlot->SetPadding(FMargin(18, 12, 18, 52));
    }
    FieldWorldChat = CreateWidget<UDigimonVenomNXTWorldChatWidget>(GetOwningPlayer(), UDigimonVenomNXTWorldChatWidget::StaticClass());
    if (FieldWorldChat)
    {
        FieldWorldChat->SetFieldPresentation(true);
        FieldWorldChatFrame->AddChild(FieldWorldChat);
    }
    FieldWorldChatFrame->SetVisibility(ESlateVisibility::Collapsed);

    // The campaign tracker occupies the left below identity, clear of the team rail.
    USizeBox* RelayObjectiveSize = WidgetTree->ConstructWidget<USizeBox>();
    RelayObjectiveSize->SetWidthOverride(380.0f);
    if (UOverlaySlot* S = Root->AddChildToOverlay(RelayObjectiveSize))
    { S->SetHorizontalAlignment(HAlign_Left); S->SetVerticalAlignment(VAlign_Top); S->SetPadding(FMargin(18, 116, 18, 18)); }
    RelayObjectiveRoot = Card(WidgetTree, FLinearColor(0.006f,0.018f,0.035f,0.90f));
    RelayObjectiveRoot->SetVisibility(ESlateVisibility::Collapsed); RelayObjectiveRoot->SetPadding(FMargin(14));
    RelayObjectiveSize->AddChild(RelayObjectiveRoot);
    UVerticalBox* RelayTracker = WidgetTree->ConstructWidget<UVerticalBox>(); RelayObjectiveRoot->SetContent(RelayTracker);
    RelayCampaignLabel = T(WidgetTree, TEXT("DAWN STORY  /  PRIVATE JOURNEY"), 10, Gold, true); Add(RelayTracker, RelayCampaignLabel, 2);
    RelayObjectiveTitle = T(WidgetTree, TEXT(""), 16, Text, true); Add(RelayTracker, RelayObjectiveTitle, 3);
    RelayObjectiveText = T(WidgetTree, TEXT(""), 13, Muted); Add(RelayTracker, RelayObjectiveText, 3);
    RelayInteractionText = T(WidgetTree, TEXT(""), 12, Accent, true); Add(RelayTracker, RelayInteractionText, 4);

    // Farm care is a nonmodal overlay: only its controls receive clicks. The empty
    // screen still belongs to exploration, and every care button is nonfocusable.
    FarmWorldHUD = CreateWidget<UDigimonVenomNXTFarmWidget>(GetOwningPlayer(), UDigimonVenomNXTFarmWidget::StaticClass());
    if (FarmWorldHUD)
    {
        FarmWorldHUD->SetWorldOverlay(true);
        FarmWorldHUD->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        if (UOverlaySlot* FarmHUDSlot = Root->AddChildToOverlay(FarmWorldHUD)) { FarmHUDSlot->SetHorizontalAlignment(HAlign_Fill); FarmHUDSlot->SetVerticalAlignment(VAlign_Fill); }
        FarmWorldHUD->SetVisibility(ESlateVisibility::Collapsed);
    }

    // Full menu is intentionally collapsed during exploration.
    MenuRoot = Card(WidgetTree, FLinearColor(0.0f,0.0f,0.0f,0.58f));
    MenuRoot->SetPadding(FMargin(0));
    if (UOverlaySlot* MenuOverlaySlot = Root->AddChildToOverlay(MenuRoot))
    {
        MenuOverlaySlot->SetHorizontalAlignment(HAlign_Fill);
        MenuOverlaySlot->SetVerticalAlignment(VAlign_Fill);
    }
    UOverlay* MenuOverlay = WidgetTree->ConstructWidget<UOverlay>();
    MenuRoot->SetContent(MenuOverlay);

    DigimonVenomNXTUI::AddBackdrop(WidgetTree, MenuOverlay, nullptr, FLinearColor(0.003f,0.012f,0.027f,0.48f));
    UScaleBox* ResponsiveFrame = WidgetTree->ConstructWidget<UScaleBox>();
    MenuBodyFrame = ResponsiveFrame;
    ResponsiveFrame->SetStretch(EStretch::ScaleToFit);
    ResponsiveFrame->SetStretchDirection(EStretchDirection::DownOnly);
    if (UOverlaySlot* ResponsiveSlot = MenuOverlay->AddChildToOverlay(ResponsiveFrame))
    {
        ResponsiveSlot->SetHorizontalAlignment(HAlign_Fill);
        ResponsiveSlot->SetVerticalAlignment(VAlign_Fill);
        ResponsiveSlot->SetPadding(FMargin(20.0f));
    }
    USizeBox* FrameSize = WidgetTree->ConstructWidget<USizeBox>();
    FrameSize->SetWidthOverride(1280.0f);
    FrameSize->SetHeightOverride(900.0f);
    ResponsiveFrame->AddChild(FrameSize);
    UBorder* Frame = Card(WidgetTree, FLinearColor(0.009f,0.025f,0.050f,0.94f));
    Frame->SetPadding(FMargin(14.0f));
    FrameSize->AddChild(Frame);
    UVerticalBox* FrameV = WidgetTree->ConstructWidget<UVerticalBox>();
    Frame->SetContent(FrameV);

    UHorizontalBox* MainRow = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* S = FrameV->AddChildToVerticalBox(MainRow)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); }

    USizeBox* SidebarSize = WidgetTree->ConstructWidget<USizeBox>();
    SidebarSize->SetWidthOverride(210.0f);
    UBorder* Sidebar = Card(WidgetTree, FLinearColor(0.015f,0.055f,0.085f,0.96f));
    SidebarSize->AddChild(Sidebar);
    if (UHorizontalBoxSlot* S = MainRow->AddChildToHorizontalBox(SidebarSize)) { S->SetPadding(FMargin(0,0,12,0)); }
    UVerticalBox* SidebarBody = WidgetTree->ConstructWidget<UVerticalBox>(); Sidebar->SetContent(SidebarBody);
    UScrollBox* NavScroll = WidgetTree->ConstructWidget<UScrollBox>();
    if (UVerticalBoxSlot* S = SidebarBody->AddChildToVerticalBox(NavScroll)) S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    UVerticalBox* Nav = WidgetTree->ConstructWidget<UVerticalBox>(); NavScroll->AddChild(Nav);
    Add(Nav, T(WidgetTree, TEXT("DIGIMON VENOM NXT"), 24, Accent, true), 2);
    Add(Nav, T(WidgetTree, TEXT("TAMER COMMAND DECK"), 11, Muted, true), 0);
    Add(Nav, T(WidgetTree, TEXT("Explore. Collect. Ascend."), 11, Muted), 2);
    Add(Nav, T(WidgetTree, TEXT("ESC closes  •  M / TAB opens from field"), 10, Muted), 2);
    UDigimonVenomNXTActionButton* CloseMenu = Action(WidgetTree, TEXT("RETURN TO FIELD"), TEXT("closemenu"), 0, FLinearColor(0.20f,0.78f,0.65f,1.0f));
    CloseMenu->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(Nav, CloseMenu, 5);
    const TArray<FString> Pages = {TEXT("Overview"),TEXT("Tamer Studio"),TEXT("Atlas"),TEXT("Party"),TEXT("DigiDex"),TEXT("Collection"),TEXT("DigiLab"),TEXT("DigiFarm"),TEXT("Shop"),TEXT("Story"),TEXT("Season"),TEXT("Ranked"),TEXT("Unranked"),TEXT("Rivals"),TEXT("Social"),TEXT("Clans"),TEXT("Trading Center"),TEXT("Video")};
    for (const FString& Page : Pages)
    {
        const FLinearColor NavColor = Page == TEXT("Ranked") ? Purple : (Page == TEXT("Story")) ? Gold : Accent;
        const FString PageLabel = Page == TEXT("Atlas") ? TEXT("LEVEL SELECT") : Page.ToUpper();
        UDigimonVenomNXTActionButton* B = Action(WidgetTree, PageLabel, TEXT("page:") + Page, 0, NavColor);
        B->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        NavButtons.Add(Page, B);
        Add(Nav, B, 2);
    }

    // Pinned session actions stay reachable even when the page list scrolls.
    HostConsoleButton = Action(WidgetTree, TEXT("WORLD SERVER CONSOLE"), TEXT("console:open"), 0, Gold);
    HostConsoleButton->SetToolTipText(FText::FromString(TEXT("Host only: live server activity and administrative commands.")));
    HostConsoleButton->SetVisibility(ESlateVisibility::Collapsed);
    HostConsoleButton->SetIsEnabled(false);
    HostConsoleButton->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
    Add(SidebarBody, HostConsoleButton, 5);
    LogoutButton = Action(WidgetTree, TEXT("LOG OUT"), TEXT("session:logout"), 0, Muted);
    LogoutButton->SetToolTipText(FText::FromString(TEXT("Return to login. Player progress stays in server memory; only the admin saves to disk.")));
    LogoutButton->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
    Add(SidebarBody, LogoutButton, 2);

    UBorder* PageBorder = Card(WidgetTree, FLinearColor(0.012f,0.035f,0.066f,0.98f));
    if (UHorizontalBoxSlot* S = MainRow->AddChildToHorizontalBox(PageBorder)) S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    PageSwitcher = WidgetTree->ConstructWidget<UWidgetSwitcher>();
    PageBorder->SetContent(PageSwitcher);

    auto MakePage = [&](const FString& Name) -> UVerticalBox*
    {
        UVerticalBox* Outer = WidgetTree->ConstructWidget<UVerticalBox>();
        PageIndices.Add(Name, PageSwitcher->GetNumWidgets());
        PageSwitcher->AddChild(Outer);
        const FString DisplayName = Name == TEXT("Collection") ? TEXT("EVOLUTION LAB") : Name == TEXT("Rivals") ? TEXT("RIVAL ACTIVITY") : Name == TEXT("Ranked") ? TEXT("RANKED ARENA") : Name.ToUpper();
        if (Name != TEXT("Season") && Name != TEXT("Party") && Name != TEXT("DigiFarm") && Name != TEXT("DigiDex") && Name != TEXT("DigiLab") && Name != TEXT("Story") && Name != TEXT("Tamer Studio")) Add(Outer, T(WidgetTree, DisplayName, 28, Name == TEXT("Story") ? Gold : Name == TEXT("Ranked") ? Gold : Accent, true), 2);
        UScrollBox* Scroll = WidgetTree->ConstructWidget<UScrollBox>();
        if (UVerticalBoxSlot* S = Outer->AddChildToVerticalBox(Scroll)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0, Name == TEXT("Season") ? 0 : 8)); }
        UVerticalBox* DynamicContent = WidgetTree->ConstructWidget<UVerticalBox>();
        Scroll->AddChild(DynamicContent);
        PageScrolls.Add(Name, Scroll);
        return DynamicContent;
    };

    OverviewContent = MakePage(TEXT("Overview"));
    TamerContent = MakePage(TEXT("Tamer Studio"));

    UVerticalBox* AtlasOuter = WidgetTree->ConstructWidget<UVerticalBox>();
    PageIndices.Add(TEXT("Atlas"), PageSwitcher->GetNumWidgets());
    PageSwitcher->AddChild(AtlasOuter);
    Add(AtlasOuter, T(WidgetTree, TEXT("LEVEL SELECT"), 26, Accent, true), 2);
    Add(AtlasOuter, T(WidgetTree, TEXT("Choose a habitat, then the field menu closes automatically so you can walk the map. Wild battles occur from exploration steps."), 13, Muted), 2);
    UHorizontalBox* Regions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(AtlasOuter, Regions, 5);
    const TCHAR* RegionLabels[] = { TEXT("ALL REGIONS"), TEXT("DAWN"), TEXT("WORLD DS"), TEXT("SUPER XROS WARS") };
    for (int32 I = 0; I < 4; ++I)
    {
        UDigimonVenomNXTActionButton* Region = Action(WidgetTree, RegionLabels[I], TEXT("atlasregion"), I - 1, Accent);
        Region->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        if (UHorizontalBoxSlot* S = Regions->AddChildToHorizontalBox(Region)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(3)); }
    }
    UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(AtlasOuter, Pager, 4);
    AtlasPrevious = Action(WidgetTree, TEXT("PREVIOUS"), TEXT("atlaspage"), -1, Accent);
    AtlasPrevious->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Pager->AddChildToHorizontalBox(AtlasPrevious);
    AtlasPageLabel = T(WidgetTree, TEXT(""), 13, Muted, true); AtlasPageLabel->SetJustification(ETextJustify::Center);
    if (UHorizontalBoxSlot* S = Pager->AddChildToHorizontalBox(AtlasPageLabel)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
    AtlasNext = Action(WidgetTree, TEXT("NEXT"), TEXT("atlaspage"), 1, Accent);
    AtlasNext->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Pager->AddChildToHorizontalBox(AtlasNext);
    UScrollBox* AtlasScroll = WidgetTree->ConstructWidget<UScrollBox>();
    if (UVerticalBoxSlot* S = AtlasOuter->AddChildToVerticalBox(AtlasScroll)) S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    PageScrolls.Add(TEXT("Atlas"), AtlasScroll);
    AtlasGrid = WidgetTree->ConstructWidget<UUniformGridPanel>(); AtlasGrid->SetSlotPadding(FMargin(5)); AtlasScroll->AddChild(AtlasGrid);

    PartyContent = MakePage(TEXT("Party"));
    DigiDexContent = MakePage(TEXT("DigiDex"));
    CollectionContent = MakePage(TEXT("Collection"));
    LabContent = MakePage(TEXT("DigiLab"));
    FarmContent = MakePage(TEXT("DigiFarm"));
    ShopContent = MakePage(TEXT("Shop"));
    StoryContent = MakePage(TEXT("Story"));
    SeasonContent = MakePage(TEXT("Season"));
    RankedContent = MakePage(TEXT("Ranked"));
    RivalsContent = MakePage(TEXT("Rivals"));
    for (const FString& CommunityName : TArray<FString>{TEXT("Social"), TEXT("Unranked"), TEXT("Clans"), TEXT("Trading Center")})
    {
        UDigimonVenomNXTCommunityWidget* CommunityPage = CreateWidget<UDigimonVenomNXTCommunityWidget>(GetOwningPlayer(), UDigimonVenomNXTCommunityWidget::StaticClass());
        if (!CommunityPage) continue;
        CommunityPage->Configure(FName(*CommunityName));
        CommunityPages.Add(CommunityName, CommunityPage);
        PageIndices.Add(CommunityName, PageSwitcher->GetNumWidgets());
        PageSwitcher->AddChild(CommunityPage);
    }

    // Video owns its scroll area and confirmation overlay. A direct fill page
    // keeps Apply/Keep/Revert visible without nesting scroll containers.
    VideoSettings = CreateWidget<UDigimonVenomNXTVideoSettingsWidget>(GetOwningPlayer(), UDigimonVenomNXTVideoSettingsWidget::StaticClass());
    if (VideoSettings)
    {
        PageIndices.Add(TEXT("Video"), PageSwitcher->GetNumWidgets());
        PageSwitcher->AddChild(VideoSettings);
    }

    MenuWorldChat = CreateWidget<UDigimonVenomNXTWorldChatWidget>(GetOwningPlayer(), UDigimonVenomNXTWorldChatWidget::StaticClass());
    if (MenuWorldChat)
    {
        MenuWorldChat->SetFieldPresentation(false);
        if (UVerticalBoxSlot* LayoutSlot = FrameV->AddChildToVerticalBox(MenuWorldChat))
        {
            LayoutSlot->SetPadding(FMargin(0, 10, 0, 0));
            LayoutSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
        }
    }

    // NPC conversations sit above the menu but leave the campaign map visible.
    UScaleBox* DialogueFit = WidgetTree->ConstructWidget<UScaleBox>(); DialogueFit->SetStretch(EStretch::ScaleToFit); DialogueFit->SetStretchDirection(EStretchDirection::DownOnly);
    if (UOverlaySlot* S = Root->AddChildToOverlay(DialogueFit))
    { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Bottom); S->SetPadding(FMargin(24,12,24,68)); }
    USizeBox* DialogueSize = WidgetTree->ConstructWidget<USizeBox>(); DialogueSize->SetWidthOverride(840.0f); DialogueFit->AddChild(DialogueSize);
    RelayDialogueRoot = Card(WidgetTree, FLinearColor(0.009f,0.025f,0.052f,0.99f)); RelayDialogueRoot->SetPadding(FMargin(22)); DialogueSize->AddChild(RelayDialogueRoot);
    RelayDialogueContent = WidgetTree->ConstructWidget<UVerticalBox>(); RelayDialogueRoot->SetContent(RelayDialogueContent); RelayDialogueRoot->SetVisibility(ESlateVisibility::Collapsed);

    LogoutOverlay = Card(WidgetTree, FLinearColor(0.0f,0.0f,0.0f,0.85f));
    LogoutOverlay->SetPadding(FMargin(24));
    if (UOverlaySlot* S = Root->AddChildToOverlay(LogoutOverlay)) { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
    UScaleBox* LogoutFit = WidgetTree->ConstructWidget<UScaleBox>();
    LogoutFit->SetStretch(EStretch::ScaleToFit); LogoutFit->SetStretchDirection(EStretchDirection::DownOnly);
    LogoutOverlay->SetContent(LogoutFit);
    USizeBox* LogoutSize = WidgetTree->ConstructWidget<USizeBox>(); LogoutSize->SetWidthOverride(600); LogoutFit->AddChild(LogoutSize);
    UBorder* LogoutCard = Card(WidgetTree); LogoutCard->SetPadding(FMargin(28)); LogoutSize->AddChild(LogoutCard);
    UVerticalBox* LogoutBody = WidgetTree->ConstructWidget<UVerticalBox>(); LogoutCard->SetContent(LogoutBody);
    Add(LogoutBody, T(WidgetTree, TEXT("READY TO LOG OUT?"), 25, Gold, true), 4);
    LogoutMessage = T(WidgetTree, TEXT(""), 16); Add(LogoutBody, LogoutMessage, 12);
    Add(LogoutBody, T(WidgetTree, TEXT("If the server cannot retain your session, you stay in game. Finish any battle that cannot be resumed before leaving."), 13, Muted), 6);
    LogoutCancelButton = Action(WidgetTree, TEXT("STAY IN GAME"), TEXT("session:cancel"));
    LogoutCancelButton->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(LogoutBody, LogoutCancelButton, 6);
    UDigimonVenomNXTActionButton* ConfirmLogout = Action(WidgetTree, TEXT("CONFIRM LOG OUT"), TEXT("session:confirm"), 0, Gold);
    ConfirmLogout->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(LogoutBody, ConfirmLogout, 3);
    LogoutOverlay->SetVisibility(ESlateVisibility::Collapsed);

    ToastText = T(WidgetTree, TEXT(""), 14, Gold, true); ToastText->SetJustification(ETextJustify::Center); ToastText->SetWrapTextAt(760.0f);
    USizeBox* ToastWidth = WidgetTree->ConstructWidget<USizeBox>();
    ToastWidth->SetWidthOverride(800.0f);
    ToastWidth->AddChild(ToastText);
    ToastWidth->SetVisibility(ESlateVisibility::HitTestInvisible);
    if (UOverlaySlot* ToastOverlaySlot = Root->AddChildToOverlay(ToastWidth)) { ToastOverlaySlot->SetHorizontalAlignment(HAlign_Center); ToastOverlaySlot->SetVerticalAlignment(VAlign_Bottom); ToastOverlaySlot->SetPadding(FMargin(20,0,20,28)); }

    ShowPage(TEXT("Overview"));
    SetMenuOpen(false);
}

void UDigimonVenomNXTGameHUDWidget::ShowPage(const FString& PageName)
{
    if (!PageSwitcher) return;
    if (bLogoutConfirmationOpen) return;
    if (PageName == TEXT("Server Console"))
    {
        UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
        if (!Console || !Console->CanAccess(GetOwningPlayer())) return;
        RefreshSessionControls();
    }
    const int32* Index = PageIndices.Find(PageName);
    if (!Index) return;
    if (ActivePage == TEXT("Overview") && PageName != ActivePage) CommitAudioVolumes();
    if (ActivePage == TEXT("Video") && PageName != ActivePage && VideoSettings) VideoSettings->CloseSettings();
    if (ActivePage == TEXT("Server Console") && PageName != ActivePage && ServerConsole) ServerConsole->CloseConsole();
    PageSwitcher->SetActiveWidgetIndex(*Index);
    ActivePage = PageName;
    for (const auto& Pair : CommunityPages) if (Pair.Value) Pair.Value->SetPageActive(bMenuOpen && Pair.Key == ActivePage);
    if (PageName == TEXT("Story")) if (const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) if (PC->IsInRelay()) SelectedCampaign = PC->GetStoryCampaign();
    for (const auto& Pair : NavButtons) DigimonVenomNXTUI::StyleButton(Pair.Value, Pair.Key == TEXT("Ranked") || Pair.Key == TEXT("Story") ? DigimonHUDUI::Gold : DigimonHUDUI::Accent, Pair.Key == PageName);
    RefreshAll();
    if (ActivePage == TEXT("Tamer Studio") && TamerStudio) TamerStudio->FocusRoster();
    if (ActivePage == TEXT("Video") && VideoSettings && bMenuOpen) VideoSettings->OpenSettings();
    if (ActivePage == TEXT("Server Console") && ServerConsole && bMenuOpen) ServerConsole->OpenConsole();
    if (HostConsoleButton) DigimonVenomNXTUI::StyleButton(HostConsoleButton, DigimonHUDUI::Gold, ActivePage == TEXT("Server Console"));
    LiveRefreshAccumulator = 5.0f;
    SyncMenuMusic();
}

void UDigimonVenomNXTGameHUDWidget::SetMenuOpen(bool bOpen)
{
    if (bOpen != bMenuOpen)
    {
        ReleaseWorldChatFocus();
        if (FieldWorldChat && MenuWorldChat)
        {
            if (bOpen) MenuWorldChat->TakeComposerStateFrom(FieldWorldChat);
            else FieldWorldChat->TakeComposerStateFrom(MenuWorldChat);
        }
    }
    if (!bOpen) { SetLogoutConfirmation(false); if (ServerConsole) ServerConsole->CloseConsole(); }
    if (!bOpen) CommitAudioVolumes();
    if (!bOpen && VideoSettings) VideoSettings->CloseSettings();
    bMenuOpen = bOpen;
    for (const auto& Pair : CommunityPages) if (Pair.Value) Pair.Value->SetPageActive(bOpen && Pair.Key == ActivePage);
    if (bOpen) { CloseRelayDialogue(); RefreshSessionControls(); RefreshAll(); LiveRefreshAccumulator = 5.0f; }
    if (MenuRoot) MenuRoot->SetVisibility(bOpen ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (bOpen && ActivePage == TEXT("Video") && VideoSettings) VideoSettings->OpenSettings();
    if (bOpen && ActivePage == TEXT("Server Console") && ServerConsole) ServerConsole->OpenConsole();
    if (FieldHintText) FieldHintText->SetVisibility((bOpen || !bCompactHUDVisible) ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
    RefreshFarmPresentation(true);
    RefreshFieldPartyPresentation(true);
    RefreshWorldChatPresentation();
    RefreshRelayFieldHUD();
    SyncMenuMusic();
}

bool UDigimonVenomNXTGameHUDWidget::HandleVideoSettingsBack()
{
    return IsVideoSettingsOpen() && VideoSettings && VideoSettings->HandleBack();
}

void UDigimonVenomNXTGameHUDWidget::RefreshSessionControls()
{
    UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    const bool bAllowed = Console && Console->CanAccess(GetOwningPlayer());
    if (HostConsoleButton) { HostConsoleButton->SetVisibility(bAllowed ? ESlateVisibility::Visible : ESlateVisibility::Collapsed); HostConsoleButton->SetIsEnabled(bAllowed); }
    if (bAllowed && !ServerConsole && PageSwitcher)
    {
        ServerConsole = CreateWidget<UDigimonVenomNXTServerConsoleWidget>(GetOwningPlayer(), UDigimonVenomNXTServerConsoleWidget::StaticClass());
        if (ServerConsole)
        {
            ServerConsole->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
            PageIndices.Add(TEXT("Server Console"), PageSwitcher->GetNumWidgets());
            PageSwitcher->AddChild(ServerConsole);
        }
    }
    if (!bAllowed && ServerConsole)
    {
        ServerConsole->CloseConsole();
        if (ActivePage == TEXT("Server Console"))
        {
            SetLogoutConfirmation(false);
            ShowPage(TEXT("Overview"));
        }
        if (PageSwitcher) PageSwitcher->RemoveChild(ServerConsole);
        PageIndices.Remove(TEXT("Server Console"));
        ServerConsole = nullptr;
    }
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    if (LogoutButton) LogoutButton->SetIsEnabled(PC && !PC->IsLogoutPending());
}

bool UDigimonVenomNXTGameHUDWidget::HandleServerConsoleBack()
{
    if (!IsServerConsoleOpen() || !ServerConsole) return false;
    if (ServerConsole->HandleBack()) return true;
    ShowPage(TEXT("Overview"));
    return true;
}

void UDigimonVenomNXTGameHUDWidget::SetLogoutConfirmation(bool bShow)
{
    bLogoutConfirmationOpen = bShow && bMenuOpen && LogoutOverlay;
    if (LogoutOverlay) LogoutOverlay->SetVisibility(bLogoutConfirmationOpen ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (MenuBodyFrame) MenuBodyFrame->SetIsEnabled(!bLogoutConfirmationOpen);
    if (!bLogoutConfirmationOpen) return;
    const APlayerController* PC = GetOwningPlayer();
    const bool bHost = PC && PC->IsLocalController() && PC->HasAuthority() && PC->GetNetMode() == NM_ListenServer;
    if (LogoutMessage) LogoutMessage->SetText(FText::FromString(bHost
        ? TEXT("You are hosting this world. Logging out saves all online and disconnected players, ranked progress and AI rivals, then closes the server.")
        : TEXT("Your progress stays in server memory so you can rejoin while the server is running. Your logout does not save to disk. The admin must use /saveall or log out to checkpoint progress; a server crash can lose unflushed changes.")));
    if (LogoutCancelButton) LogoutCancelButton->SetKeyboardFocus();
}

bool UDigimonVenomNXTGameHUDWidget::HandleLogoutConfirmationBack()
{
    if (!bLogoutConfirmationOpen) return false;
    SetLogoutConfirmation(false);
    if (LogoutButton) LogoutButton->SetKeyboardFocus();
    return true;
}

void UDigimonVenomNXTGameHUDWidget::SyncMenuMusic()
{
    if (ULocalPlayer* Player = GetOwningLocalPlayer())
    {
        if (UDigimonVenomNXTAudioSubsystem* Audio = Player->GetSubsystem<UDigimonVenomNXTAudioSubsystem>())
        {
            if (bMenuOpen) Audio->SetUIScreenMusic(this, ActivePage);
            else Audio->ClearUIScreenMusic(this);
        }
    }
}

void UDigimonVenomNXTGameHUDWidget::ToggleMenu()
{
    if (ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) PC->SetFieldMenuOpen(!bMenuOpen);
    else SetMenuOpen(!bMenuOpen);
}

void UDigimonVenomNXTGameHUDWidget::OpenDigiLab()
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (!PC || !PS || !PS->HasStarter() || PC->CurrentBattle || PS->HasActiveBattle() || PC->IsInDigiFarm() || IsRelayDialogueOpen()) return;
    ShowPage(TEXT("DigiLab"));
    PC->SetFieldMenuOpen(true); // Recovery never travels, respawns or replaces a campaign instance.
}

void UDigimonVenomNXTGameHUDWidget::SetCompactHUDVisible(bool bVisible)
{
    bCompactHUDVisible = bVisible;
    if (CompactHUDRoot) CompactHUDRoot->SetVisibility(bVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
    if (FieldHintText && !bMenuOpen) FieldHintText->SetVisibility(bVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
    RefreshRelayFieldHUD();
    RefreshFieldPartyPresentation(true);
    RefreshWorldChatPresentation();
}

void UDigimonVenomNXTGameHUDWidget::ShowToast(const FString& Title, const FString& Message)
{
    ToastSecondsRemaining = 7.0f;
    if (ToastText) ToastText->SetText(FText::FromString(Title.IsEmpty() ? Message : FString::Printf(TEXT("%s — %s"), *Title, *Message)));
}

void UDigimonVenomNXTGameHUDWidget::AppendChat(const FDigimonChatMessage& Message)
{
    if (FieldWorldChat) FieldWorldChat->AppendMessage(Message);
    if (MenuWorldChat) MenuWorldChat->AppendMessage(Message);
}

bool UDigimonVenomNXTGameHUDWidget::IsWorldChatTyping() const
{
    return (FieldWorldChat && FieldWorldChat->IsComposing()) || (MenuWorldChat && MenuWorldChat->IsComposing());
}

bool UDigimonVenomNXTGameHUDWidget::IsWorldChatHovered() const
{
    return (FieldWorldChat && FieldWorldChatFrame && FieldWorldChatFrame->GetVisibility() != ESlateVisibility::Collapsed && FieldWorldChat->IsHovered())
        || (bMenuOpen && MenuWorldChat && MenuWorldChat->IsHovered());
}

void UDigimonVenomNXTGameHUDWidget::FocusWorldChat()
{
    if (bLogoutConfirmationOpen || IsRelayDialogueOpen()) return;
    RefreshWorldChatPresentation();
    if (bMenuOpen) { if (MenuWorldChat) MenuWorldChat->FocusComposer(); }
    else if (FieldWorldChat && FieldWorldChatFrame && FieldWorldChatFrame->GetVisibility() != ESlateVisibility::Collapsed) FieldWorldChat->FocusComposer();
}

void UDigimonVenomNXTGameHUDWidget::ReleaseWorldChatFocus()
{
    if (FieldWorldChat) FieldWorldChat->ReleaseComposer();
    if (MenuWorldChat) MenuWorldChat->ReleaseComposer();
}

void UDigimonVenomNXTGameHUDWidget::HandleProfileChanged()
{
    RefreshAll();
}

void UDigimonVenomNXTGameHUDWidget::HandleAction(const FString& Action, int32 Payload)
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (Action == TEXT("session:cancel")) { HandleLogoutConfirmationBack(); return; }
    if (Action == TEXT("session:confirm"))
    {
        if (!bLogoutConfirmationOpen || !PC) return;
        FString Error;
        if (PC->RequestLogout(Error)) SetLogoutConfirmation(false);
        else ShowToast(TEXT("LOGOUT"), Error);
        RefreshSessionControls();
        return;
    }
    if (bLogoutConfirmationOpen) return;
    if (Action == TEXT("session:logout")) { if (PC && !PC->IsLogoutPending()) SetLogoutConfirmation(true); return; }
    if (Action == TEXT("console:open")) { ShowPage(TEXT("Server Console")); return; }
    if (Action == TEXT("console:close")) { ShowPage(TEXT("Overview")); return; }
    if (Action == TEXT("digilab:open")) { OpenDigiLab(); return; }
    if (Action == TEXT("field:party"))
    {
        if (PC && PS && !PC->CurrentBattle && !PS->HasActiveBattle() && !IsRelayDialogueOpen())
        { ShowPage(TEXT("Party")); PC->SetFieldMenuOpen(true); }
        return;
    }
    if (Action == TEXT("digilab:return")) { if (PC) PC->SetFieldMenuOpen(false); else SetMenuOpen(false); return; }
    if (Action == TEXT("campaignselect") || Action == TEXT("campaignscrolltop"))
    {
        if (Action == TEXT("campaignselect")) { if (Payload >= 0 && Payload <= 2) SelectedCampaign = static_cast<EDigimonPrivateCampaign>(Payload); RefreshStory(); }
        if (const TObjectPtr<UScrollBox>* StoryScroll = PageScrolls.Find(TEXT("Story"))) if (*StoryScroll) (*StoryScroll)->ScrollToStart();
        return;
    }
    if (Action == TEXT("relayresume")) { if (PC) { if (PC->IsInRelayCampaign()) PC->ServerResumeRelayBattle(); else PC->ServerEnterRelay(); } return; }
    if (Action == TEXT("chroniclesresume")) { if (PC) { if (PC->IsInChronicles()) PC->ServerResumeRelayBattle(); else PC->ServerEnterChronicles(); } return; }
    if (Action == TEXT("chroniclesenter")) { SelectedCampaign = EDigimonPrivateCampaign::ParadoxChronicles; if (PC) { if (PC->IsInChronicles()) PC->SetFieldMenuOpen(false); else PC->ServerEnterChronicles(); } return; }
    if (Action == TEXT("chroniclesquest")) { const FName NPCId = RelayDialogueNPC; CloseRelayDialogue(); if (PC && !NPCId.IsNone()) PC->ServerAdvanceChroniclesQuest(NPCId); return; }
    if (Action == TEXT("relayenter")) { SelectedCampaign = EDigimonPrivateCampaign::Relay; if (PC) { if (PC->IsInRelayCampaign()) PC->SetFieldMenuOpen(false); else PC->ServerEnterRelay(); } return; }
    if (Action == TEXT("ghostlineresume")) { if (PC) { if (PC->IsInGhostLine()) PC->ServerResumeRelayBattle(); else PC->ServerEnterGhostLine(); } return; }
    if (Action == TEXT("ghostlineenter")) { SelectedCampaign = EDigimonPrivateCampaign::GhostLine; if (PC) { if (PC->IsInGhostLine()) PC->SetFieldMenuOpen(false); else PC->ServerEnterGhostLine(); } return; }
    if (Action == TEXT("ghostlinequest")) { const FName NPCId = RelayDialogueNPC; CloseRelayDialogue(); if (PC && !NPCId.IsNone()) PC->ServerAdvanceGhostLineQuest(NPCId); return; }
    if (Action == TEXT("ghostlinetravel")) { CloseRelayDialogue(); if (PC && PC->IsInGhostLine()) PC->ServerRelayFastTravel(Payload); return; }
    if (Action == TEXT("ghostlineportal")) { CloseRelayDialogue(); if (PC && PC->IsInGhostLine()) PC->ServerTravelRelayMap(Payload); return; }
    if (Action == TEXT("ghostlinetrain")) { if (PC && PC->IsInGhostLine()) { PC->SetFieldMenuOpen(false); PC->ServerStartRelayFieldTraining(); } return; }
    if (Action == TEXT("relayleave")) { CloseRelayDialogue(); if (PC) PC->ServerLeaveRelay(); return; }
    if (Action == TEXT("relayfasttravel")) { CloseRelayDialogue(); if (PC) PC->ServerRelayFastTravel(Payload); return; }
    if (Action == TEXT("relaytravel")) { CloseRelayDialogue(); if (PC) PC->ServerTravelRelayMap(Payload); return; }
    if (Action == TEXT("relaytraining")) { if (PC) { PC->SetFieldMenuOpen(false); PC->ServerStartRelayFieldTraining(); } return; }
    if (Action == TEXT("relaydialogueclose")) { CloseRelayDialogue(); return; }
    if (Action == TEXT("relaydialoguechallenge")) { const FName NPCId = RelayDialogueNPC; CloseRelayDialogue(); if (PC && !NPCId.IsNone()) PC->ServerChallengeRelayNPC(NPCId); return; }
    if (Action == TEXT("relaydialogueshop")) { CloseRelayDialogue(); ShowPage(TEXT("Shop")); if (PC) PC->SetFieldMenuOpen(true); return; }
    if (Action == TEXT("farmenter"))
    {
        if (PC)
        {
            if (PC->IsInDigiFarm())
            {
                if (PC->GetDigiFarmScene() && PC->GetDigiFarmScene()->IsPresentationReady()) PC->SetFieldMenuOpen(false);
                else ShowToast(TEXT("Island unavailable"), TEXT("Choose LEAVE FARM to return safely. Ask the host to check the island before entering again."));
            }
            else PC->ServerEnterDigiFarm();
        }
        return;
    }
    if (Action == TEXT("farmleave")) { if (PC) PC->ServerLeaveDigiFarm(); return; }
    if (Action == TEXT("farmmanage") || Action == TEXT("farmshop"))
    {
        ShowPage(Action == TEXT("farmmanage") ? TEXT("DigiFarm") : TEXT("Shop"));
        if (PC) PC->SetFieldMenuOpen(true);
        return;
    }
    if (Action.StartsWith(TEXT("page:"))) { ShowPage(Action.Mid(5)); return; }
    if (Action == TEXT("closemenu")) { if (PC) PC->SetFieldMenuOpen(false); else SetMenuOpen(false); return; }
    if (Action == TEXT("map")) { if (PC) { PC->ServerTravelToMap(Payload); PC->SetFieldMenuOpen(false); } return; }
    if (Action == TEXT("seasonmatch")) { if (PC) PC->ServerStartSeasonMatch(); return; }
    if (Action == TEXT("seasonadvance")) { if (PC) PC->ServerAdvanceSeasonWeek(); return; }
    if (Action == TEXT("seasonarchivepage")) { if (PC) PC->ServerRequestSeasonArchive(FMath::Max(0, Payload)); return; }
    if (Action == TEXT("seasonreturn")) { if (PC) PC->ServerSaveSeasonAndReturn(); return; }
    if (Action == TEXT("rivalspage"))
    {
        RivalPageIndex = FMath::Clamp(Payload, 0, FMath::Max(0, RivalSnapshot.TotalPages - 1));
        if (PC) PC->ServerRequestAIRivalActivity(RivalPageIndex, 12);
        return;
    }
    if (Action == TEXT("rivalsrefresh")) { RequestLivePage(); LiveRefreshAccumulator = 0.0f; return; }
    if (Action == TEXT("rankeddefender")) { if (PC) PC->ServerSaveRankedDefender(); return; }
    if (Action == TEXT("rankedquick")) { if (PC) PC->ServerRunRankedQuickMatch(); return; }
    if (Action.StartsWith(TEXT("rival:"))) { if (PC) PC->ServerChallengeAIRival(Action.Mid(6)); return; }
    if (Action == TEXT("heal")) { if (PS) PS->ServerHealAll(); return; }
    if (Action == TEXT("save")) { if (PC) PC->ServerRequestSave(); return; }
    if (Action == TEXT("relaydialoguelab") || Action == TEXT("relaydialoguefarm"))
    {
        CloseRelayDialogue(); ShowPage(Action == TEXT("relaydialoguelab") ? TEXT("DigiLab") : TEXT("DigiFarm"));
        if (PC) PC->SetFieldMenuOpen(true); return;
    }
    if (Action == TEXT("startersearch")) { StarterSearchTerm = StarterSearchInput ? StarterSearchInput->GetText().ToString().TrimStartAndEnd() : FString(); StarterPage = 0; RefreshOverview(); return; }
    if (Action == TEXT("starterclear")) { StarterSearchTerm.Reset(); StarterPage = 0; RefreshOverview(); return; }
    if (Action == TEXT("starterpage")) { StarterPage = FMath::Max(0, StarterPage + Payload); RefreshOverview(); return; }
    if (Action == TEXT("atlasregion")) { AtlasRegion = FMath::Clamp(Payload, -1, 2); AtlasPage = 0; RefreshAtlas(); return; }
    if (Action == TEXT("atlaspage")) { AtlasPage = FMath::Max(0, AtlasPage + Payload); RefreshAtlas(); if (auto* Scroll = PageScrolls.Find(TEXT("Atlas"))) if (*Scroll) (*Scroll)->ScrollToStart(); return; }
    if (Action == TEXT("shopfilter")) { ShopFilter = FMath::Clamp(Payload, 0, 4); RefreshShop(); return; }
    if (Action == TEXT("shopquantity")) { ShopQuantity = Payload == 5 || Payload == 10 ? Payload : 1; RefreshShop(); return; }
    if (Action == TEXT("rubies")) { if (PS) PS->ServerConvertDigiRubiesToCredits(FMath::Max(1,Payload)); return; }
    if (Action.StartsWith(TEXT("starter:"))) { if (PS) PS->ServerChooseStarter(FName(*Action.Mid(8))); return; }
    if (Action.StartsWith(TEXT("tamer:"))) { if (PS) PS->ServerSetTamerStyle(FName(*Action.Mid(6))); return; }
    if (Action.StartsWith(TEXT("buyc:"))) { if (PS) PS->ServerPurchaseItem(FName(*Action.Mid(5)), EDigimonCurrency::Credits, FMath::Max(1,Payload)); return; }
    if (Action.StartsWith(TEXT("buyr:"))) { if (PS) PS->ServerPurchaseItem(FName(*Action.Mid(5)), EDigimonCurrency::DigiRubies, FMath::Max(1,Payload)); return; }
    if (Action.StartsWith(TEXT("materialize:")) && PS)
    {
        TArray<FString> Parts; Action.ParseIntoArray(Parts, TEXT(":"), false);
        if (Parts.Num()==3) PS->ServerMaterialize(FName(*Parts[1]), static_cast<EDigimonVariant>(FCString::Atoi(*Parts[2])));
        return;
    }
    if (Action == TEXT("dexready"))
    {
        ShowPage(TEXT("DigiDex"));
        if (DigiDex) DigiDex->ShowReadyForms();
        return;
    }
    if (Action.StartsWith(TEXT("inspectpartner:")) && PS)
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(15), Id)) return;
        ShowPage(TEXT("Collection"));
        if (EvolutionLab) EvolutionLab->SelectPartner(Id);
        return;
    }
    if (Action.StartsWith(TEXT("partymove:")) && PS)
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(10), Id) || (Payload != -1 && Payload != 1)) return;
        TArray<FGuid> Party = PS->Profile.Party;
        const int32 CurrentIndex = Party.IndexOfByKey(Id);
        const int32 TargetIndex = CurrentIndex + Payload;
        if (CurrentIndex != INDEX_NONE && Party.IsValidIndex(TargetIndex))
        {
            Party.Swap(CurrentIndex, TargetIndex);
            PS->ServerSetParty(Party);
        }
        return;
    }
    if (Action.StartsWith(TEXT("partyadd:")) && PS)
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(9), Id)) return;
        TArray<FGuid> Party = PS->Profile.Party;
        if (!Party.Contains(Id) && Party.Num() < GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize) { Party.Add(Id); PS->ServerSetParty(Party); }
        return;
    }
    if (Action.StartsWith(TEXT("partyremove:")) && PS)
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(12), Id)) return;
        TArray<FGuid> Party = PS->Profile.Party;
        if (Party.Num() > 1 && Party.Remove(Id) > 0) PS->ServerSetParty(Party);
        return;
    }
    if (Action.StartsWith(TEXT("leader:")) && PS)
    {
        FGuid Id; if (!FGuid::Parse(Action.Mid(7), Id)) return;
        TArray<FGuid> Party = PS->Profile.Party;
        const int32 Found = Party.IndexOfByKey(Id);
        if (Found > 0) { Party.RemoveAt(Found); Party.Insert(Id, 0); PS->ServerSetParty(Party); }
        return;
    }
    if ((Action.StartsWith(TEXT("evolve:")) || Action.StartsWith(TEXT("deevolve:"))) && PS)
    {
        TArray<FString> Parts; Action.ParseIntoArray(Parts, TEXT(":"), false);
        FGuid Id;
        if (Parts.Num() == 3 && FGuid::Parse(Parts[1], Id))
        {
            if (Action.StartsWith(TEXT("deevolve:"))) PS->ServerDeEvolve(Id, FName(*Parts[2]));
            else PS->ServerEvolve(Id, FName(*Parts[2]));
        }
        return;
    }
    if (Action.StartsWith(TEXT("farmadd:")) && PS) { FGuid Id; if (FGuid::Parse(Action.Mid(8),Id)) PS->ServerSetFarmResident(Id,true); return; }
    if (Action.StartsWith(TEXT("farmremove:")) && PS) { FGuid Id; if (FGuid::Parse(Action.Mid(11),Id)) PS->ServerSetFarmResident(Id,false); return; }
    if (Action.StartsWith(TEXT("camtreat:")) && PS) { FGuid Id; if (FGuid::Parse(Action.Mid(9),Id)) PS->ServerUseCAMTreat(Id); return; }
    if (Action.StartsWith(TEXT("abimeat:")) && PS) { FGuid Id; if (FGuid::Parse(Action.Mid(8),Id)) PS->ServerUseABIMeat(Id); return; }
    if (Action.StartsWith(TEXT("digimeat:")) && PS)
    {
        TArray<FString> Parts; Action.ParseIntoArray(Parts, TEXT(":"), false); FGuid Id;
        const int32 Stat = Parts.Num() == 3 ? FCString::Atoi(*Parts[2]) : -1;
        if (Parts.Num() == 3 && FGuid::Parse(Parts[1], Id) && Stat >= 0 && Stat <= static_cast<int32>(EDigimonTrainingStat::Speed))
            PS->ServerUseDigiMeat(Id, static_cast<EDigimonTrainingStat>(Stat));
        return;
    }
    if (Action.StartsWith(TEXT("abi:")) && PS)
    {
        TArray<FString> Parts; Action.ParseIntoArray(Parts,TEXT(":"),false); FGuid Id;
        if (Parts.Num()==3 && FGuid::Parse(Parts[1],Id)) PS->ServerFeedABIMeat(Id, Parts[2]==TEXT("r")?EDigimonCurrency::DigiRubies:EDigimonCurrency::Credits);
        return;
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshAll()
{
    RefreshHeader();
    RefreshRelayFieldHUD();
    RefreshFarmPresentation(true);
    RefreshFieldPartyPresentation(true);
    if (!bMenuOpen) return; // Opening the menu refreshes its active page; hidden collections do no work.
    // Update only the visible page. Collection and farm can contain hundreds of partners.
    const TObjectPtr<UScrollBox>* Scroll = PageScrolls.Find(ActivePage);
    const float Offset = Scroll && *Scroll ? (*Scroll)->GetScrollOffset() : 0.0f;
    UDigimonVenomNXTActionButton* Focused = Scroll && *Scroll ? DigimonHUDUI::FindFocusedAction(*Scroll, GetOwningPlayer()) : nullptr;
    const FString FocusedAction = Focused ? Focused->Action : FString();
    const int32 FocusedPayload = Focused ? Focused->Payload : 0;
    if (ActivePage == TEXT("Overview")) RefreshOverview();
    else if (ActivePage == TEXT("Tamer Studio")) RefreshTamerStudio();
    else if (ActivePage == TEXT("Party")) RefreshParty();
    else if (ActivePage == TEXT("DigiDex")) RefreshDigiDex();
    else if (ActivePage == TEXT("Collection")) RefreshCollection();
    else if (ActivePage == TEXT("Atlas")) RefreshAtlas();
    else if (ActivePage == TEXT("DigiLab")) RefreshLab();
    else if (ActivePage == TEXT("DigiFarm")) RefreshFarm();
    else if (ActivePage == TEXT("Shop")) RefreshShop();
    else if (ActivePage == TEXT("Story")) RefreshStory();
    else if (ActivePage == TEXT("Season")) RefreshSeason();
    else if (ActivePage == TEXT("Ranked")) RefreshRanked();
    else if (ActivePage == TEXT("Rivals")) RefreshRivals();
    if (Scroll && *Scroll)
    {
        (*Scroll)->SetScrollOffset(Offset);
        if (!FocusedAction.IsEmpty())
            if (UDigimonVenomNXTActionButton* Restored = DigimonHUDUI::FindAction(*Scroll, FocusedAction, FocusedPayload)) Restored->SetUserFocus(GetOwningPlayer());
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshHeader()
{
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (!PS) return;
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonMapRow MapRow;
    const bool bHasMap = Data && Data->GetMap(PS->Profile.CurrentMapId, MapRow);
    const FString MapName = bHasMap && !MapRow.DisplayName.IsEmpty() ? MapRow.DisplayName.ToString() : FString::Printf(TEXT("Habitat %03d"), PS->Profile.CurrentMapId);

    if (HeaderIdentity) HeaderIdentity->SetText(FText::FromString(FString::Printf(TEXT("%s  •  %d collected"), *PS->Profile.Username, PS->Profile.Collection.Num())));
    if (HeaderEconomy) HeaderEconomy->SetText(FText::FromString(FText::AsNumber(PS->Profile.Credits).ToString() + TEXT(" Credits")));
    if (HeaderRubies) HeaderRubies->SetText(FText::FromString(FText::AsNumber(PS->Profile.DigiRubies).ToString() + TEXT(" DigiRubies")));
    if (HeaderWorld)
    {
        HeaderWorld->SetText(FText::FromString(FString::Printf(TEXT("Map %03d  •  %s  •  Party %d/%d"), PS->Profile.CurrentMapId, *MapName, PS->Profile.Party.Num(), GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize)));
        HeaderWorld->SetToolTipText(FText::FromString(MapName));
    }

    if (CompactLeadImage)
    {
        FDigimonOwnedPartner Lead;
        if (PS->Profile.Party.Num() > 0 && PS->GetPartner(PS->Profile.Party[0], Lead))
        {
            CompactLeadImage->SetDigimon(Lead.SpeciesId, Lead.Variant);
            CompactLeadImage->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
        else CompactLeadImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshOverview()
{
    if (!OverviewContent || !WidgetTree) return;
    OverviewContent->ClearChildren();
    AudioVolumeLabels.Reset();
    using namespace DigimonHUDUI;
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (!PS) { Add(OverviewContent, T(WidgetTree, TEXT("Synchronizing profile..."), 16, Muted), 3); return; }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;

    // The appearance studio is available before the first partner selection too.
    UBorder* IdentityCard = Card(WidgetTree);
    UHorizontalBox* IdentityRow = WidgetTree->ConstructWidget<UHorizontalBox>(); IdentityCard->SetContent(IdentityRow);
    if (UHorizontalBoxSlot* IdentityArtLayout = IdentityRow->AddChildToHorizontalBox(TextureBox(WidgetTree, LoadTamerThumbnail(PS->Profile.TamerStyleId.ToString()), 48, 96))) IdentityArtLayout->SetPadding(FMargin(4, 0, 16, 0));
    UVerticalBox* IdentityDetails = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UHorizontalBoxSlot* IdentityDetailsLayout = IdentityRow->AddChildToHorizontalBox(IdentityDetails)) { IdentityDetailsLayout->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); IdentityDetailsLayout->SetVerticalAlignment(VAlign_Center); }
    Add(IdentityDetails, T(WidgetTree, TEXT("YOUR TAMER  /  ") + DigimonVenomNXTTamers::DisplayName(PS->Profile.TamerStyleId), 17, Purple, true), 2);
    Add(IdentityDetails, T(WidgetTree, FString::Printf(TEXT("Choose from %d appearances. Preview every direction and make the adventure your own."), DigimonVenomNXTTamers::GetRoster().Num()), 13, Muted), 2);
    UDigimonVenomNXTActionButton* OpenStudio = Action(WidgetTree, FString::Printf(TEXT("OPEN TAMER STUDIO  •  %d FREE LOOKS"), DigimonVenomNXTTamers::GetRoster().Num()), TEXT("page:Tamer Studio"));
    OpenStudio->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(IdentityDetails, OpenStudio, 3);
    Add(OverviewContent, IdentityCard, 5);
    if (!PS->HasStarter())
    {
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        const int32 StarterLevel = DigimonVenomNXTStarterCore::StartingLevel(Settings->StarterLevel, Settings->MaxPartnerLevel);
        Add(OverviewContent, T(WidgetTree, TEXT("CHOOSE YOUR FIRST PARTNER"), 21, Gold, true), 5);
        Add(OverviewContent, T(WidgetTree, FString::Printf(TEXT("Start at Lv.%d with full HP and SP. Your partner joins party slot 1 and follows you in the world."), StarterLevel), 14, Muted), 3);
        if (Data)
        {
            UHorizontalBox* SearchRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(OverviewContent, SearchRow, 5);
            StarterSearchInput = WidgetTree->ConstructWidget<UEditableTextBox>();
            DigimonVenomNXTUI::StyleInput(StarterSearchInput); StarterSearchInput->SetHintText(FText::FromString(TEXT("Find a Rookie by name")));
            StarterSearchInput->SetText(FText::FromString(StarterSearchTerm));
            if (UHorizontalBoxSlot* S = SearchRow->AddChildToHorizontalBox(StarterSearchInput)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0, 0, 6, 0)); }
            UDigimonVenomNXTActionButton* Search = Action(WidgetTree, TEXT("SEARCH"), TEXT("startersearch")); Search->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); SearchRow->AddChildToHorizontalBox(Search);
            UDigimonVenomNXTActionButton* Clear = Action(WidgetTree, TEXT("CLEAR"), TEXT("starterclear")); Clear->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); SearchRow->AddChildToHorizontalBox(Clear);
            TArray<FDigimonSpeciesDefinition> Candidates;
            for (const FDigimonSpeciesDefinition& Def : Data->GetStarterCandidates(MAX_int32))
                if (StarterSearchTerm.IsEmpty() || Def.DisplayName.ToString().Contains(StarterSearchTerm, ESearchCase::IgnoreCase) || Def.SpeciesId.ToString().Contains(StarterSearchTerm, ESearchCase::IgnoreCase)) Candidates.Add(Def);
            constexpr int32 PerPage = 12;
            const int32 Pages = FMath::Max(1, FMath::DivideAndRoundUp(Candidates.Num(), PerPage)); StarterPage = FMath::Clamp(StarterPage, 0, Pages - 1);
            UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(OverviewContent, Pager, 4);
            for (const int32 Direction : { -1, 1 })
            {
                UDigimonVenomNXTActionButton* Page = Action(WidgetTree, Direction < 0 ? TEXT("PREVIOUS") : TEXT("NEXT"), TEXT("starterpage"), Direction);
                Page->SetIsEnabled(Direction < 0 ? StarterPage > 0 : StarterPage + 1 < Pages);
                Page->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Pager->AddChildToHorizontalBox(Page);
            }
            if (UHorizontalBoxSlot* S = Pager->AddChildToHorizontalBox(T(WidgetTree, FString::Printf(TEXT("%d ROOKIES  •  PAGE %d / %d"), Candidates.Num(), StarterPage + 1, Pages), 13, Muted, true))) { S->SetPadding(FMargin(12, 0)); S->SetVerticalAlignment(VAlign_Center); }
            if (Candidates.IsEmpty()) Add(OverviewContent, T(WidgetTree, TEXT("No Rookie matches that search. Clear the search to browse every starter."), 14, Gold), 5);
            for (int32 CandidateIndex = StarterPage * PerPage; CandidateIndex < FMath::Min(Candidates.Num(), (StarterPage + 1) * PerPage); ++CandidateIndex)
            {
                const FDigimonSpeciesDefinition& Def = Candidates[CandidateIndex];
                UBorder* C = Card(WidgetTree);
                UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>(); C->SetContent(Row);
                if (UHorizontalBoxSlot* PortraitRowSlot = Row->AddChildToHorizontalBox(DigimonVenomNXTUI::AnimatedPortrait(WidgetTree, Def.SpeciesId, EDigimonVariant::Normal, 112.0f, 112.0f))) PortraitRowSlot->SetPadding(FMargin(0,0,12,0));
                UVerticalBox* Info = WidgetTree->ConstructWidget<UVerticalBox>();
                if (UHorizontalBoxSlot* InfoRowSlot = Row->AddChildToHorizontalBox(Info)) { InfoRowSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); InfoRowSlot->SetVerticalAlignment(VAlign_Center); }
                Add(Info, T(WidgetTree, Def.DisplayName.ToString(), 18, Text, true), 1);
                UTextBlock* TypeText = nullptr; UTextBlock* ElementText = nullptr;
                Add(Info, DigimonVenomNXTCombatUI::TypeChips(WidgetTree, TypeText, ElementText, 10), 2);
                DigimonVenomNXTCombatUI::UpdateChips(TypeText, ElementText, Def.Affinity, Def.Element);
                FDigimonOwnedPartner Preview; Preview.SpeciesId = Def.SpeciesId; Preview.Level = StarterLevel;
                const FDigimonStats StarterStats = DigimonVenomNXTAutoBattle::BuildUnit(Preview, Data).Stats;
                Add(Info, T(WidgetTree, FString::Printf(TEXT("Lv.%d  •  HP %d  SP %d  ATK %d  DEF %d  INT %d  SPD %d"), StarterLevel, StarterStats.MaxHP, StarterStats.MaxSP, StarterStats.Attack, StarterStats.Defense, StarterStats.Spirit, StarterStats.Speed), 12, Muted), 1);
                UDigimonVenomNXTActionButton* B = Action(WidgetTree, TEXT("CHOOSE THIS PARTNER"), TEXT("starter:") + Def.SpeciesId.ToString(), 0, Gold);
                B->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(Info, B, 3);
                Add(OverviewContent, C, 4);
            }
        }
        return;
    }

    BuildAudioControls();
    Add(OverviewContent, T(WidgetTree, TEXT("YOUR ADVENTURE CONTINUES"), 20, Gold, true), 4);
    Add(OverviewContent, T(WidgetTree, TEXT("Your next partner is out there. Walk the habitats to discover wild Digimon, collect scan data and build a team that is yours. M / Tab returns to the field; the mouse wheel adjusts your view."), 15, Text), 3);
    Add(OverviewContent, T(WidgetTree, TEXT("After travelling through Level Select there is a short safe walking distance before random encounter rolls begin."), 13, Muted), 2);
    UDigimonVenomNXTActionButton* Save = Action(WidgetTree, TEXT("SAVE PROFILE NOW"), TEXT("save"));
    Save->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(OverviewContent, Save, 6);
    Add(OverviewContent, T(WidgetTree, FString::Printf(TEXT("Scan records %d   •   DigiFarm %d/100   •   Ranked career %d-%d"), PS->Profile.Scans.Num(), PS->Profile.DigiFarmResidents.Num(), PS->Profile.Ranked.CareerWins, PS->Profile.Ranked.CareerLosses), 13, Muted), 3);
}

void UDigimonVenomNXTGameHUDWidget::BuildAudioControls()
{
    ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
    UDigimonVenomNXTAudioSubsystem* Audio = LocalPlayer ? LocalPlayer->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr;
    if (!OverviewContent || !WidgetTree || !Audio) return;
    using namespace DigimonHUDUI;
    UBorder* MixCard = Card(WidgetTree); Add(OverviewContent, MixCard, 5);
    UVerticalBox* MixBody = WidgetTree->ConstructWidget<UVerticalBox>(); MixCard->SetContent(MixBody);
    Add(MixBody, T(WidgetTree, TEXT("YOUR SOUND MIX"), 17, Accent, true), 2);
    Add(MixBody, T(WidgetTree, TEXT("Music, battle effects and interface sounds have independent volume controls. Your choices are saved on this device."), 12, Muted), 3);
    const TCHAR* Labels[] = { TEXT("MASTER"), TEXT("MUSIC"), TEXT("BATTLE / WORLD EFFECTS"), TEXT("INTERFACE") };
    const float Values[] = { Audio->GetMasterVolume(), Audio->GetMusicVolume(), Audio->GetEffectsVolume(), Audio->GetUIVolume() };
    for (int32 Channel = 0; Channel < 4; ++Channel)
    {
        UHorizontalBox* MixRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(MixBody, MixRow, 4);
        USizeBox* NameBounds = WidgetTree->ConstructWidget<USizeBox>(); NameBounds->SetWidthOverride(178);
        NameBounds->AddChild(T(WidgetTree, Labels[Channel], 11, Text, true));
        if (UHorizontalBoxSlot* NameSlot = MixRow->AddChildToHorizontalBox(NameBounds)) NameSlot->SetVerticalAlignment(VAlign_Center);
        USlider* Slider = WidgetTree->ConstructWidget<USlider>(); Slider->SetMinValue(0); Slider->SetMaxValue(1); Slider->SetStepSize(0.01f); Slider->SetValue(Values[Channel]);
        Slider->SetSliderBarColor(FLinearColor(0.12f, 0.23f, 0.31f)); Slider->SetSliderHandleColor(Accent);
        Slider->SetToolTipText(FText::FromString(FString(Labels[Channel]) + TEXT(" volume. Zero mutes this channel. Use arrow keys for fine adjustment.")));
        if (UHorizontalBoxSlot* SliderSlot = MixRow->AddChildToHorizontalBox(Slider)) { SliderSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); SliderSlot->SetPadding(FMargin(12, 0)); SliderSlot->SetVerticalAlignment(VAlign_Center); }
        UTextBlock* ValueText = T(WidgetTree, FString::Printf(TEXT("%d%%"), FMath::RoundToInt(Values[Channel] * 100)), 12, Gold, true); ValueText->SetJustification(ETextJustify::Right);
        USizeBox* ValueBounds = WidgetTree->ConstructWidget<USizeBox>(); ValueBounds->SetWidthOverride(46); ValueBounds->AddChild(ValueText); MixRow->AddChildToHorizontalBox(ValueBounds); AudioVolumeLabels.Add(ValueText);
        if (Channel == 0) Slider->OnValueChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleMasterVolume);
        else if (Channel == 1) Slider->OnValueChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleMusicVolume);
        else if (Channel == 2) Slider->OnValueChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleEffectsVolume);
        else Slider->OnValueChanged.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleUIVolume);
        Slider->OnMouseCaptureEnd.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::CommitAudioVolumes);
        Slider->OnControllerCaptureEnd.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::CommitAudioVolumes);
    }
}

void UDigimonVenomNXTGameHUDWidget::SetAudioMixValue(int32 Channel, float Value)
{
    ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
    UDigimonVenomNXTAudioSubsystem* Audio = LocalPlayer ? LocalPlayer->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr;
    if (!Audio || Channel < 0 || Channel > 3) return;
    Value = FMath::Clamp(Value, 0.0f, 1.0f);
    Audio->SetAudioVolumes(Channel == 0 ? Value : Audio->GetMasterVolume(), Channel == 1 ? Value : Audio->GetMusicVolume(),
        Channel == 2 ? Value : Audio->GetEffectsVolume(), Channel == 3 ? Value : Audio->GetUIVolume(), false);
    if (AudioVolumeLabels.IsValidIndex(Channel) && AudioVolumeLabels[Channel]) AudioVolumeLabels[Channel]->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), FMath::RoundToInt(Value * 100))));
    bAudioMixDirty = true;
}

void UDigimonVenomNXTGameHUDWidget::HandleMasterVolume(float Value) { SetAudioMixValue(0, Value); }
void UDigimonVenomNXTGameHUDWidget::HandleMusicVolume(float Value) { SetAudioMixValue(1, Value); }
void UDigimonVenomNXTGameHUDWidget::HandleEffectsVolume(float Value) { SetAudioMixValue(2, Value); }
void UDigimonVenomNXTGameHUDWidget::HandleUIVolume(float Value) { SetAudioMixValue(3, Value); }

void UDigimonVenomNXTGameHUDWidget::CommitAudioVolumes()
{
    if (!bAudioMixDirty) return;
    if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
        if (UDigimonVenomNXTAudioSubsystem* Audio = LocalPlayer->GetSubsystem<UDigimonVenomNXTAudioSubsystem>())
        {
            Audio->SetAudioVolumes(Audio->GetMasterVolume(), Audio->GetMusicVolume(), Audio->GetEffectsVolume(), Audio->GetUIVolume(), true);
            bAudioMixDirty = false;
        }
}

void UDigimonVenomNXTGameHUDWidget::RefreshTamerStudio()
{
    if (!TamerContent || !WidgetTree) return;
    if (!TamerStudio)
    {
        TamerStudio = CreateWidget<UDigimonVenomNXTTamerStudioWidget>(GetOwningPlayer(), UDigimonVenomNXTTamerStudioWidget::StaticClass());
        if (!TamerStudio) return;
        TamerStudio->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(TamerContent, TamerStudio, 0);
    }
    TamerStudio->RefreshFromProfile(GetDigimonPlayerState());
}

void UDigimonVenomNXTGameHUDWidget::RefreshParty()
{
    if (!PartyContent || !WidgetTree) return;
    // Update cards in place so portraits, pointer targets and keyboard focus remain stable.
    if (!PartyPanel)
    {
        PartyPanel = WidgetTree->ConstructWidget<UDigimonVenomNXTPartyWidget>();
        PartyPanel->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(PartyContent, PartyPanel, 0);
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    PartyPanel->RefreshFromProfile(GetDigimonPlayerState(), Data);
}

void UDigimonVenomNXTGameHUDWidget::RefreshCollection()
{
    if (!CollectionContent || !WidgetTree) return;
    // Retain the entire lab across profile replication. Selection, pages and animations stay live.
    if (!EvolutionLab)
    {
        EvolutionLab = WidgetTree->ConstructWidget<UDigimonVenomNXTEvolutionWidget>();
        EvolutionLab->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(CollectionContent, EvolutionLab, 0);
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    EvolutionLab->RefreshFromProfile(GetDigimonPlayerState(), Data);
}

void UDigimonVenomNXTGameHUDWidget::RefreshDigiDex()
{
    if (!DigiDexContent || !WidgetTree) return;
    if (!DigiDex)
    {
        DigiDex = WidgetTree->ConstructWidget<UDigimonVenomNXTDigiDexWidget>();
        DigiDex->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(DigiDexContent, DigiDex, 0);
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    DigiDex->RefreshFromProfile(GetDigimonPlayerState(), Data);
}

void UDigimonVenomNXTGameHUDWidget::RefreshLab()
{
    if (!LabContent || !WidgetTree) return;
    if (!DigiLab)
    {
        DigiLab = CreateWidget<UDigimonVenomNXTDigiLabWidget>(GetOwningPlayer(), UDigimonVenomNXTDigiLabWidget::StaticClass());
        if (!DigiLab) return;
        DigiLab->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(LabContent, DigiLab, 0);
    }
    DigiLab->RefreshFromProfile();
}

void UDigimonVenomNXTGameHUDWidget::RefreshFarm()
{
    if (!FarmContent || !WidgetTree) return;
    if (!FarmManager)
    {
        FarmManager = CreateWidget<UDigimonVenomNXTFarmWidget>(GetOwningPlayer(), UDigimonVenomNXTFarmWidget::StaticClass());
        if (!FarmManager) return;
        FarmManager->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(FarmContent, FarmManager, 0);
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FarmManager->RefreshFromProfile(GetDigimonPlayerState(), Data);
}

void UDigimonVenomNXTGameHUDWidget::RefreshFarmPresentation(bool bRefreshData)
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bFarm = PC && PC->IsInDigiFarm();
    const bool bCareVisible = bFarm && !bMenuOpen && !PC->CurrentBattle;
    if (FarmWorldHUD)
    {
        const bool bWasVisible = FarmWorldHUD->GetVisibility() != ESlateVisibility::Collapsed;
        FarmWorldHUD->SetVisibility(bCareVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
        if (bCareVisible && (bRefreshData || !bWasVisible))
        {
            UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
            FarmWorldHUD->RefreshFromProfile(GetDigimonPlayerState(), Data);
        }
    }
    // The island has its own compact identity and care UI; avoid duplicating the field card.
    if (CompactHUDRoot) CompactHUDRoot->SetVisibility(!bFarm && bCompactHUDVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
    if (FieldHintText) FieldHintText->SetVisibility(!bFarm && !bMenuOpen && bCompactHUDVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

void UDigimonVenomNXTGameHUDWidget::RefreshFieldPartyPresentation(bool bRefreshData)
{
    if (!FieldParty || !FieldPartyFrame) return;
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    const bool bVisible = PC && PS && PS->HasStarter() && !PC->IsInDigiFarm() && !PC->CurrentBattle && !PS->HasActiveBattle()
        && !bMenuOpen && !IsRelayDialogueOpen() && bCompactHUDVisible;
    const bool bWasVisible = FieldPartyFrame->GetVisibility() != ESlateVisibility::Collapsed;
    FieldPartyFrame->SetVisibility(bVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
    if (bVisible && (bRefreshData || !bWasVisible))
    {
        UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        FieldParty->RefreshFromProfile(PS, Data);
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshWorldChatPresentation()
{
    if (!FieldWorldChat || !FieldWorldChatFrame) return;
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    const bool bPublicField = PC && PS && PS->HasStarter() && !PC->IsInDigiFarm() && !PC->IsInRelay()
        && !PC->IsFieldPresentationBlocked() && !PS->HasActiveBattle()
        && !bMenuOpen && !IsRelayDialogueOpen() && bCompactHUDVisible;
    if (!bPublicField && FieldWorldChatFrame->GetVisibility() != ESlateVisibility::Collapsed)
        FieldWorldChat->ReleaseComposer();
    FieldWorldChatFrame->SetVisibility(bPublicField ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
    // Logical viewport sizing keeps the lower-left card clear of the team rail on smaller windows.
    const float ViewWidth = GetCachedGeometry().GetLocalSize().X;
    if (ViewWidth > 0.0f)
        FieldWorldChatFrame->SetWidthOverride(FMath::Clamp(ViewWidth * 0.40f, 300.0f, 452.0f));
}

void UDigimonVenomNXTGameHUDWidget::RefreshAtlas()
{
    if (!AtlasGrid || !WidgetTree) return;
    using namespace DigimonHUDUI;
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const TArray<FDigimonMapRow> AllMaps = Data ? Data->GetAllMaps() : TArray<FDigimonMapRow>();
    TArray<FDigimonMapRow> Maps;
    for (const FDigimonMapRow& Map : AllMaps) if (AtlasRegion < 0 || static_cast<int32>(Map.Region) == AtlasRegion) Maps.Add(Map);
    constexpr int32 PageSize = 18;
    const int32 Pages = FMath::Max(1, FMath::DivideAndRoundUp(Maps.Num(), PageSize));
    AtlasPage = FMath::Clamp(AtlasPage, 0, Pages - 1);
    AtlasGrid->ClearChildren();
    AtlasPageLabel->SetText(FText::FromString(FString::Printf(TEXT("%d HABITATS  •  PAGE %d / %d"), Maps.Num(), AtlasPage + 1, Pages)));
    AtlasPrevious->SetIsEnabled(AtlasPage > 0); AtlasNext->SetIsEnabled(AtlasPage + 1 < Pages);
    const ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    const TCHAR* RegionNames[] = { TEXT("Dawn"), TEXT("World DS"), TEXT("Super Xros Wars") };
    // At most eighteen map textures are requested per page. Opening the menu
    // never synchronously loads the entire multi-region map catalogue.
    for (int32 Index = 0; Index < PageSize && Maps.IsValidIndex(AtlasPage * PageSize + Index); ++Index)
    {
        const FDigimonMapRow& Map = Maps[AtlasPage * PageSize + Index];
        UDigimonVenomNXTActionButton* B = Action(WidgetTree, TEXT(""), TEXT("map"), Map.MapId, Accent);
        B->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        const bool bHere = PS && PS->Profile.CurrentMapId == Map.MapId;
        DigimonVenomNXTUI::StyleButton(B, bHere ? Gold : Accent, bHere);
        UVerticalBox* Tile = WidgetTree->ConstructWidget<UVerticalBox>(); B->SetContent(Tile);
        Add(Tile, TextureBox(WidgetTree, LoadMapTexture(Map.MapId), 230, 120), 1);
        const FString Name = Map.DisplayName.IsEmpty() ? FString::Printf(TEXT("Habitat %03d"), Map.MapId) : Map.DisplayName.ToString();
        Add(Tile, T(WidgetTree, FString::Printf(TEXT("%03d  •  %s%s"), Map.MapId, *Name, bHere ? TEXT("  /  HERE") : TEXT("")), 12, Text, true), 2);
        Add(Tile, T(WidgetTree, FString::Printf(TEXT("Lv.%d–%d  •  %s"), Map.RecommendedMinLevel, Map.RecommendedMaxLevel, RegionNames[FMath::Clamp(static_cast<int32>(Map.Region), 0, 2)]), 11, Muted), 1);
        if (UUniformGridSlot* S = AtlasGrid->AddChildToUniformGrid(B, Index / 3, Index % 3)) S->SetHorizontalAlignment(HAlign_Fill);
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshShop()
{
    if (!ShopContent || !WidgetTree) return;
    ShopContent->ClearChildren();
    using namespace DigimonHUDUI;
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (!PS) return;
    UHorizontalBox* ShopHero = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ShopContent, ShopHero, 3);
    if (UTexture2D* Shopkeeper = LoadPresentationTexture(TEXT("T_DVN_Shopkeeper")))
        if (UHorizontalBoxSlot* HeroImageSlot = ShopHero->AddChildToHorizontalBox(TextureBox(WidgetTree, Shopkeeper, 146, 146))) HeroImageSlot->SetPadding(FMargin(0, 0, 16, 0));
    UVerticalBox* Intro = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UHorizontalBoxSlot* IntroSlot = ShopHero->AddChildToHorizontalBox(Intro)) { IntroSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); IntroSlot->SetVerticalAlignment(VAlign_Center); }
    Add(Intro, T(WidgetTree, TEXT("VENOM NXT SUPPLY TERMINAL"), 22, Gold, true), 2);
    Add(Intro, T(WidgetTree, TEXT("Ready for your next adventure."), 16, Text, true), 3);
    Add(Intro, T(WidgetTree, TEXT("Choose supplies and a quantity, then pay with Credits or DigiRubies. Prices below show the full cost of your purchase."), 13, Muted), 3);

    UHorizontalBox* WalletRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ShopContent, WalletRow, 6);
    for (int32 CurrencyIndex = 0; CurrencyIndex < 2; ++CurrencyIndex)
    {
        const bool bRubies = CurrencyIndex == 1;
        UBorder* WalletCard = Card(WidgetTree); WalletCard->SetPadding(FMargin(12, 8));
        if (UHorizontalBoxSlot* WalletSlot = WalletRow->AddChildToHorizontalBox(WalletCard)) { WalletSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); WalletSlot->SetPadding(FMargin(CurrencyIndex == 0 ? 0 : 6, 0, CurrencyIndex == 0 ? 6 : 0, 0)); }
        UHorizontalBox* CurrencyRow = WidgetTree->ConstructWidget<UHorizontalBox>(); WalletCard->SetContent(CurrencyRow);
        CurrencyRow->AddChildToHorizontalBox(DigimonVenomNXTUI::CurrencyIcon(WidgetTree, bRubies, 52, 52));
        UVerticalBox* CurrencyInfo = WidgetTree->ConstructWidget<UVerticalBox>();
        if (UHorizontalBoxSlot* CurrencySlot = CurrencyRow->AddChildToHorizontalBox(CurrencyInfo)) { CurrencySlot->SetPadding(FMargin(12, 0)); CurrencySlot->SetVerticalAlignment(VAlign_Center); CurrencySlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); }
        Add(CurrencyInfo, T(WidgetTree, bRubies ? TEXT("DIGIRUBIES") : TEXT("CREDITS"), 10, Muted, true), 1);
        Add(CurrencyInfo, T(WidgetTree, FText::AsNumber(bRubies ? static_cast<int64>(PS->Profile.DigiRubies) : PS->Profile.Credits).ToString(), 22, bRubies ? Purple : Gold, true), 1);
    }
    const bool bCanBuy = !PS->HasActiveBattle();
    if (!bCanBuy) Add(ShopContent, T(WidgetTree, TEXT("Purchases are unavailable while a battle is active."), 12, Gold), 3);
    UHorizontalBox* Filters = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ShopContent, Filters, 5);
    const TCHAR* Categories[] = { TEXT("ALL SUPPLIES"), TEXT("HP RECOVERY"), TEXT("SP RECOVERY"), TEXT("DIGIMEAT"), TEXT("ABI GROWTH") };
    for (int32 I = 0; I < 5; ++I)
    {
        UDigimonVenomNXTActionButton* Filter = Action(WidgetTree, Categories[I], TEXT("shopfilter"), I, Accent);
        DigimonVenomNXTUI::StyleButton(Filter, Accent, ShopFilter == I);
        Filter->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        if (UHorizontalBoxSlot* S = Filters->AddChildToHorizontalBox(Filter)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(2)); }
    }
    UHorizontalBox* Quantities = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ShopContent, Quantities, 4);
    Quantities->AddChildToHorizontalBox(T(WidgetTree, TEXT("QUANTITY PER PURCHASE"), 12, Muted, true));
    for (const int32 Quantity : { 1, 5, 10 })
    {
        UDigimonVenomNXTActionButton* Q = Action(WidgetTree, FString::Printf(TEXT("×%d"), Quantity), TEXT("shopquantity"), Quantity, Gold);
        DigimonVenomNXTUI::StyleButton(Q, Gold, ShopQuantity == Quantity);
        Q->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        if (UHorizontalBoxSlot* S = Quantities->AddChildToHorizontalBox(Q)) S->SetPadding(FMargin(6, 0));
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const TArray<FDigimonShopItemDefinition> Items = Data ? Data->GetShopItems() : TArray<FDigimonShopItemDefinition>();
    if (Items.IsEmpty()) Add(ShopContent, T(WidgetTree, TEXT("The supply catalog is unavailable. Please contact the world host."), 14, Gold), 8);
    for (const FDigimonShopItemDefinition& Item : Items)
    {
        const bool bMeat = Item.Category == FName(TEXT("digimeat"));
        if ((ShopFilter == 1 && (bMeat || Item.Resource != FName(TEXT("hp")))) ||
            (ShopFilter == 2 && (bMeat || Item.Resource != FName(TEXT("sp")))) ||
            (ShopFilter == 3 && !bMeat) || (ShopFilter == 4 && Item.Resource != FName(TEXT("abi")))) continue;
        const FString Name = Item.DisplayName.ToString();
        const int32 Owned = PS->GetInventoryQuantity(Item.ItemId);
        const FLinearColor Color = Item.Resource == FName(TEXT("hp")) ? FLinearColor(0.34f, 0.93f, 0.66f) : bMeat ? Gold : Accent;
        UBorder* ItemCard = Card(WidgetTree); ItemCard->SetPadding(FMargin(14)); Add(ShopContent, ItemCard, 5);
        UHorizontalBox* ItemRow = WidgetTree->ConstructWidget<UHorizontalBox>(); ItemCard->SetContent(ItemRow);
        if (UHorizontalBoxSlot* IconSlot = ItemRow->AddChildToHorizontalBox(TextureBox(WidgetTree, DigimonVenomNXTPresentationAssets::ItemTexture(Item.ItemId), 84, 84))) { IconSlot->SetPadding(FMargin(0, 4, 18, 4)); IconSlot->SetVerticalAlignment(VAlign_Center); }
        UVerticalBox* Details = WidgetTree->ConstructWidget<UVerticalBox>();
        if (UHorizontalBoxSlot* DetailSlot = ItemRow->AddChildToHorizontalBox(Details)) DetailSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        Add(Details, T(WidgetTree, FString::Printf(TEXT("%s   /   %d OWNED"), *Name, Owned), 17, Color, true), 1);
        Add(Details, T(WidgetTree, Item.Description.ToString(), 13, Muted), 4);
        UHorizontalBox* BuyRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Details, BuyRow, 4);
        for (int32 CurrencyIndex = 0; CurrencyIndex < 2; ++CurrencyIndex)
        {
            const bool bRubies = CurrencyIndex == 1;
            const int64 UnitPrice = bRubies ? static_cast<int64>(Item.DigiRubyCost) : Item.CreditCost;
            const int64 Price = UnitPrice * ShopQuantity;
            const bool bAffordable = bRubies ? static_cast<int64>(PS->Profile.DigiRubies) >= Price : PS->Profile.Credits >= Price;
            const bool bHasRoom = Owned <= 999 - ShopQuantity;
            UDigimonVenomNXTActionButton* Buy = Action(WidgetTree, TEXT(""), FString(bRubies ? TEXT("buyr:") : TEXT("buyc:")) + Item.ItemId.ToString(), ShopQuantity, bRubies ? Purple : Gold);
            Buy->SetIsEnabled(bCanBuy && bAffordable && bHasRoom && UnitPrice > 0); Buy->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
            UHorizontalBox* BuyLabel = WidgetTree->ConstructWidget<UHorizontalBox>(); Buy->SetContent(BuyLabel);
            BuyLabel->AddChildToHorizontalBox(DigimonVenomNXTUI::CurrencyIcon(WidgetTree, bRubies, 26, 26));
            UTextBlock* PriceText = T(WidgetTree, FString::Printf(TEXT("BUY ×%d  •  %s %s"), ShopQuantity, *FText::AsNumber(Price).ToString(), bRubies ? TEXT("DIGIRUBIES") : TEXT("CREDITS")), 11, Text, true);
            if (UHorizontalBoxSlot* LabelSlot = BuyLabel->AddChildToHorizontalBox(PriceText)) { LabelSlot->SetPadding(FMargin(7, 0, 0, 0)); LabelSlot->SetVerticalAlignment(VAlign_Center); }
            Buy->SetToolTipText(FText::FromString(FString::Printf(TEXT("Buy %d %s for %s %s.%s"), ShopQuantity, *Name, *FText::AsNumber(Price).ToString(), bRubies ? TEXT("DigiRubies") : TEXT("Credits"), !bCanBuy ? TEXT(" Finish the active battle first.") : !bHasRoom ? TEXT(" Inventory holds 999 of each item.") : !bAffordable ? TEXT(" You need more currency.") : TEXT(""))));
            if (UHorizontalBoxSlot* BuySlot = BuyRow->AddChildToHorizontalBox(Buy)) { BuySlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); BuySlot->SetPadding(FMargin(CurrencyIndex == 0 ? 0 : 4, 0, CurrencyIndex == 0 ? 4 : 0, 0)); }
        }
    }
    Add(ShopContent, T(WidgetTree, TEXT("DIGIRUBY EXCHANGE"), 17, Purple, true), 10);
    Add(ShopContent, T(WidgetTree, TEXT("Exchange a DigiRuby for Credits. This exchange is one-way."), 12, Muted), 2);
    UDigimonVenomNXTActionButton* Convert = Action(WidgetTree, FString::Printf(TEXT("EXCHANGE 1 DIGIRUBY → %s CREDITS"), *FText::AsNumber(Data ? Data->GetCreditsPerDigiRuby() : 100).ToString()), TEXT("rubies"), 1, Purple);
    Convert->SetIsEnabled(bCanBuy && PS->Profile.DigiRubies > 0); Convert->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(ShopContent, Convert, 3);
}

void UDigimonVenomNXTGameHUDWidget::RefreshStory()
{
    if (!StoryContent || !WidgetTree) return;
    StoryContent->ClearChildren();
    using namespace DigimonHUDUI;
    UHorizontalBox* Campaigns = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(StoryContent, Campaigns, 4);
    const TCHAR* Labels[] = { TEXT("DAWN STORY\nCHAMPIONSHIP"), TEXT("WORLD DS\nPARADOX JOURNEY"), TEXT("SUPER XROS WARS\nACCESS QUEST") };
    const FLinearColor CampaignColors[] = { Gold, Purple, Accent };
    for (int32 I=0; I<3; ++I)
    {
        UDigimonVenomNXTActionButton* B = Action(WidgetTree, Labels[I], TEXT("campaignselect"), I, CampaignColors[I]);
        DigimonVenomNXTUI::StyleButton(B, CampaignColors[I], static_cast<int32>(SelectedCampaign) == I);
        B->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        if (UHorizontalBoxSlot* S = Campaigns->AddChildToHorizontalBox(B)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(3)); }
    }
    Add(StoryContent, T(WidgetTree, TEXT("Three saved journeys with your own party: Dawn Story, World DS and Super Xros Wars. Earn permanent variety scan rewards by completing each campaign."), 12, Muted), 5);
    if (SelectedCampaign == EDigimonPrivateCampaign::ParadoxChronicles) { RefreshParadoxStory(); return; }
    if (SelectedCampaign == EDigimonPrivateCampaign::GhostLine) { RefreshGhostLineStory(); return; }
    if (!RelayJournal)
    {
        RelayJournal = CreateWidget<UDigimonVenomNXTRelayWidget>(GetOwningPlayer(), UDigimonVenomNXTRelayWidget::StaticClass());
        if (RelayJournal) RelayJournal->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
    }
    if (RelayJournal) { Add(StoryContent, RelayJournal, 4); RelayJournal->RefreshFromProfile(GetDigimonPlayerState()); }
}

void UDigimonVenomNXTGameHUDWidget::RefreshParadoxStory()
{
    if (!StoryContent || !WidgetTree) return;
    if (!ChroniclesJournal)
    {
        ChroniclesJournal = CreateWidget<UDigimonVenomNXTChroniclesWidget>(GetOwningPlayer(), UDigimonVenomNXTChroniclesWidget::StaticClass());
        if (ChroniclesJournal) ChroniclesJournal->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
    }
    if (ChroniclesJournal) { DigimonHUDUI::Add(StoryContent, ChroniclesJournal, 4); ChroniclesJournal->RefreshFromProfile(GetDigimonPlayerState()); }
}

void UDigimonVenomNXTGameHUDWidget::RefreshGhostLineStory()
{
    if (!StoryContent || !WidgetTree) return;
    if (!GhostLineJournal)
    {
        GhostLineJournal = CreateWidget<UDigimonVenomNXTGhostLineWidget>(GetOwningPlayer(), UDigimonVenomNXTGhostLineWidget::StaticClass());
        if (GhostLineJournal) GhostLineJournal->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
    }
    if (GhostLineJournal) { DigimonHUDUI::Add(StoryContent, GhostLineJournal, 4); GhostLineJournal->RefreshFromProfile(GetDigimonPlayerState()); }
}

void UDigimonVenomNXTGameHUDWidget::RefreshSeason()
{
    if (!SeasonContent || !WidgetTree) return;
    if (!SeasonCareer)
    {
        SeasonCareer = WidgetTree->ConstructWidget<UDigimonVenomNXTSeasonWidget>();
        SeasonCareer->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction);
        DigimonHUDUI::Add(SeasonContent, SeasonCareer, 0);
    }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    SeasonCareer->RefreshFromProfile(GetDigimonPlayerState(), Data);
}

void UDigimonVenomNXTGameHUDWidget::ApplySeasonArchivePage(const FDigimonSeasonArchivePage& Page)
{
    if (SeasonCareer) SeasonCareer->ApplyArchivePage(Page);
}

void UDigimonVenomNXTGameHUDWidget::RefreshRanked()
{
    if (!RankedContent || !WidgetTree) return;
    RankedContent->ClearChildren();
    RankedCountdownText = nullptr;
    RankedEnergyText = nullptr;
    using namespace DigimonHUDUI;
    ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    if (!PS) { Add(RankedContent, T(WidgetTree, TEXT("Connecting to the arena..."), 16, Muted)); return; }
    const auto& R = PS->Profile.Ranked;
    const ADigimonVenomNXTGameState* GS = GetWorld() ? GetWorld()->GetGameState<ADigimonVenomNXTGameState>() : nullptr;
    if (RankedSnapshotUnix != R.ServerUnix || RankedSnapshotReceivedAt <= 0.0)
    {
        RankedSnapshotUnix = R.ServerUnix;
        RankedSnapshotReceivedAt = FPlatformTime::Seconds();
    }

    UBorder* Hero = Card(WidgetTree, FLinearColor(0.016f,0.035f,0.070f,0.88f));
    UOverlay* HeroOverlay = WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(HeroOverlay);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, HeroOverlay, nullptr, FLinearColor(0.006f,0.014f,0.035f,0.73f));
    UVerticalBox* HeroText = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* HeroSlot = HeroOverlay->AddChildToOverlay(HeroText)) HeroSlot->SetPadding(FMargin(18.0f));
    Add(HeroText, T(WidgetTree, TEXT("THE ASCENT"), 12, Gold, true), 1);
    Add(HeroText, T(WidgetTree, FString::Printf(TEXT("GRADE %s   /   %d POINTS"), *UDigimonVenomNXTRankedSubsystem::GetGradeLabel(R.Grade), R.Rating), 30, Text, true), 3);
    Add(HeroText, T(WidgetTree, FString::Printf(TEXT("%d WINS   •   %d LOSSES   •   %d DRAWS"), R.WeeklyWins, R.WeeklyLosses, R.WeeklyDraws), 15, Accent, true), 2);
    RankedCountdownText = T(WidgetTree, TEXT("Synchronizing season..."), 14, Gold, true); Add(HeroText, RankedCountdownText, 2);
    Add(RankedContent, Hero, 5);

    const int32 GradeIndex = static_cast<int32>(R.Grade);
    if (R.GradeThresholds.IsValidIndex(GradeIndex + 1))
    {
        const int32 Minimum = R.GradeThresholds.IsValidIndex(GradeIndex) ? R.GradeThresholds[GradeIndex] : 0;
        const int32 Next = R.GradeThresholds[GradeIndex + 1];
        Add(RankedContent, T(WidgetTree, R.Rating >= Next
            ? FString::Printf(TEXT("PROMOTION READY  •  Win your next attacking match to earn %s."), *UDigimonVenomNXTRankedSubsystem::GetGradeLabel(static_cast<EDigimonRankedGrade>(GradeIndex + 1)))
            : FString::Printf(TEXT("NEXT GRADE %s  •  Earn %d more points, then win a promotion match."), *UDigimonVenomNXTRankedSubsystem::GetGradeLabel(static_cast<EDigimonRankedGrade>(GradeIndex + 1)), Next - R.Rating), 13, R.Rating >= Next ? Gold : Muted, true), 3);
        UProgressBar* Progress = WidgetTree->ConstructWidget<UProgressBar>();
        Progress->SetPercent(FMath::Clamp(static_cast<float>(R.Rating - Minimum) / FMath::Max(1, Next - Minimum), 0.0f, 1.0f));
        Progress->SetFillColorAndOpacity(Gold); Add(RankedContent, Progress, 3);
    }
    else Add(RankedContent, T(WidgetTree, TEXT("MASTER GRADE   •   Keep climbing the season standings."), 13, Gold, true), 3);
    Add(RankedContent, T(WidgetTree, TEXT("BRONZE  →  SILVER  →  GOLD  →  PLATINUM  →  DIAMOND  →  MASTER"), 14, Muted, true), 3);

    UBorder* EnergyCard = Card(WidgetTree);
    UVerticalBox* Energy = WidgetTree->ConstructWidget<UVerticalBox>(); EnergyCard->SetContent(Energy);
    RankedEnergyText = T(WidgetTree, TEXT(""), 18, Accent, true); Add(Energy, RankedEnergyText, 2);
    Add(Energy, T(WidgetTree, FString::Printf(TEXT("One energy per match. One energy returns every %s, including while you are away."), *DigimonVenomNXTUI::Countdown(R.EnergyRechargeSeconds)), 13, Muted), 2);
    UDigimonVenomNXTActionButton* Quick = Action(WidgetTree, R.Energy > 0 ? TEXT("ENTER AUTO BATTLE   /   1 ENERGY") : TEXT("RECHARGING ENERGY"), TEXT("rankedquick"), 0, Gold);
    Quick->SetIsEnabled(R.Energy > 0 && PS->Profile.Party.Num() > 0);
    Quick->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(Energy, Quick, 5);
    Add(Energy, T(WidgetTree, TEXT("Your real party fights automatically against a saved player defense or an active rival team. Opponents strengthen as you climb. Review the match report below after each battle."), 14, Text), 3);
    Add(RankedContent, EnergyCard, 5);

    UBorder* DefenseCard = Card(WidgetTree);
    UVerticalBox* Defense = WidgetTree->ConstructWidget<UVerticalBox>(); DefenseCard->SetContent(Defense);
    Add(Defense, T(WidgetTree, TEXT("YOUR DEFENSE TEAM"), 16, Accent, true), 2);
    Add(Defense, T(WidgetTree, TEXT("Save your current party whenever your team changes. This is the exact team opponents will face, including your reserve partners."), 13, Muted), 2);
    UUniformGridPanel* DefenseRow = WidgetTree->ConstructWidget<UUniformGridPanel>(); DefenseRow->SetSlotPadding(FMargin(6)); Add(Defense, DefenseRow, 3);
    for (int32 PartnerIndex = 0; PartnerIndex < R.DefenderTeam.Num(); ++PartnerIndex)
    {
        const FDigimonOwnedPartner& Partner = R.DefenderTeam[PartnerIndex];
        UVerticalBox* TeamColumn = WidgetTree->ConstructWidget<UVerticalBox>();
        Add(TeamColumn, DigimonVenomNXTUI::AnimatedPortrait(WidgetTree, Partner.SpeciesId, Partner.Variant, 96.0f, 96.0f), 1);
        Add(TeamColumn, T(WidgetTree, FString::Printf(TEXT("%s  Lv.%d"), *Partner.SpeciesId.ToString(), Partner.Level), 12, Text, true), 1);
        DefenseRow->AddChildToUniformGrid(TeamColumn, PartnerIndex / 3, PartnerIndex % 3);
    }
    if (R.DefenderTeam.IsEmpty()) Add(Defense, T(WidgetTree, TEXT("No defense saved yet. Set your lineup to enter the ladder."), 14, Gold), 2);
    UDigimonVenomNXTActionButton* SaveDef = Action(WidgetTree, TEXT("SAVE CURRENT DEFENSE"), TEXT("rankeddefender"), 0, Accent);
    SaveDef->SetIsEnabled(PS->Profile.Party.Num() > 0); SaveDef->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(Defense, SaveDef, 3);
    Add(RankedContent, DefenseCard, 5);

    if (R.LastBattleUnix > 0)
    {
        UBorder* Result = Card(WidgetTree); UVerticalBox* Details = WidgetTree->ConstructWidget<UVerticalBox>(); Result->SetContent(Details);
        Add(Details, T(WidgetTree, TEXT("LATEST MATCH REPORT"), 12, Muted, true), 1);
        Add(Details, T(WidgetTree, FString::Printf(TEXT("%s   /   %s   /   %+d POINTS"), *R.LastResult, *R.LastOpponent, R.LastRatingDelta), 21, R.LastResult == TEXT("WIN") ? Gold : Text, true), 3);
        Add(Details, T(WidgetTree, FString::Printf(TEXT("%d combat turns"), R.LastBattleTurns), 13, Muted), 2);
        UUniformGridPanel* Opponents = WidgetTree->ConstructWidget<UUniformGridPanel>(); Opponents->SetSlotPadding(FMargin(6)); Add(Details, Opponents, 3);
        for (int32 OpponentIndex = 0; OpponentIndex < R.LastOpponentTeam.Num(); ++OpponentIndex)
        {
            const FDigimonOwnedPartner& Opponent = R.LastOpponentTeam[OpponentIndex];
            UVerticalBox* Partner = WidgetTree->ConstructWidget<UVerticalBox>();
            Add(Partner, DigimonVenomNXTUI::AnimatedPortrait(WidgetTree, Opponent.SpeciesId, Opponent.Variant, 76.0f, 76.0f), 1);
            Add(Partner, T(WidgetTree, FString::Printf(TEXT("%s  Lv.%d"), *Opponent.SpeciesId.ToString(), Opponent.Level), 12, Text), 1);
            Opponents->AddChildToUniformGrid(Partner, OpponentIndex / 3, OpponentIndex % 3);
        }
        for (const FString& Line : R.LastBattleLog) Add(Details, T(WidgetTree, Line, 13, Muted), 1);
        Add(RankedContent, Result, 5);
    }

    Add(RankedContent, T(WidgetTree, TEXT("SEASON REWARDS  /  DIGIRUBIES"), 19, Gold, true), 6);
    Add(RankedContent, T(WidgetTree, R.RewardPlacement > 0 ? FString::Printf(TEXT("YOUR GLOBAL REWARD RANK   #%d"), R.RewardPlacement) : TEXT("PLAY AN ATTACKING MATCH TO QUALIFY FOR REWARDS"), 16, Gold, true), 3);
    Add(RankedContent, T(WidgetTree, TEXT("Placement bonuses use your global standing among players and AI rivals. An attacking match is required to qualify; passive defense alone does not count."), 13, Muted), 2);
    Add(RankedContent, T(WidgetTree, FString::Printf(TEXT("ATTACKING MATCHES  %d / %d REQUIRED. Grade rewards and eligible placement bonuses are delivered automatically when the season closes."), R.WeeklyAttacks, R.MinimumRewardMatches), 14, Muted), 3);
    FString GradeRewards;
    for (int32 Index = 0; Index < R.RewardGradeDigiRubies.Num() && Index < 6; ++Index)
    {
        if (!GradeRewards.IsEmpty()) GradeRewards += TEXT("   •   ");
        GradeRewards += FString::Printf(TEXT("%s: %d"), *UDigimonVenomNXTRankedSubsystem::GetGradeLabel(static_cast<EDigimonRankedGrade>(Index)), R.RewardGradeDigiRubies[Index]);
    }
    Add(RankedContent, T(WidgetTree, GradeRewards, 14, Gold, true), 3);
    const TCHAR* PlacementLabels[] = {TEXT("1st"), TEXT("Top 10"), TEXT("Top 25"), TEXT("Top 50"), TEXT("Top 100"), TEXT("Top 500"), TEXT("Eligible")};
    FString PlacementRewards;
    for (int32 Index = 0; Index < R.RewardPlacementDigiRubies.Num() && Index < 7; ++Index)
    {
        if (!PlacementRewards.IsEmpty()) PlacementRewards += TEXT("   •   ");
        PlacementRewards += FString::Printf(TEXT("%s: +%d"), PlacementLabels[Index], R.RewardPlacementDigiRubies[Index]);
    }
    Add(RankedContent, T(WidgetTree, PlacementRewards, 14, Text), 3);
    Add(RankedContent, T(WidgetTree, TEXT("SEASON STANDINGS"), 19, Accent, true), 6);
    if (GS && !GS->RankedTop100.IsEmpty())
    {
        for (const FDigimonRankedPublicEntry& Entry : GS->RankedTop100)
        {
            UBorder* Row = Card(WidgetTree); UVerticalBox* Info = WidgetTree->ConstructWidget<UVerticalBox>(); Row->SetContent(Info);
            Add(Info, T(WidgetTree, FString::Printf(TEXT("#%d   %s   %s"), Entry.Rank, *Entry.Username, Entry.bAIRival ? TEXT("[AI RIVAL]") : TEXT("[TAMER]")), 15, Entry.Rank <= 3 ? Gold : Text, true), 1);
            Add(Info, T(WidgetTree, FString::Printf(TEXT("GRADE %s   •   %d POINTS   •   %d W / %d L / %d D"), *UDigimonVenomNXTRankedSubsystem::GetGradeLabel(Entry.Grade), Entry.Rating, Entry.Wins, Entry.Losses, Entry.Draws), 13, Muted), 1);
            Add(RankedContent, Row, 2);
        }
    }
    else Add(RankedContent, T(WidgetTree, TEXT("The new season is open. Complete a match to begin your climb."), 14, Muted), 3);
    Add(RankedContent, T(WidgetTree, FString::Printf(TEXT("CAREER   %d WINS / %d LOSSES"), R.CareerWins, R.CareerLosses), 13, Muted), 6);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    UDigimonVenomNXTActionButton* Convert = Action(WidgetTree, FString::Printf(TEXT("EXCHANGE 1 DIGIRUBY → %d CREDITS"), Data ? Data->GetCreditsPerDigiRuby() : 100), TEXT("rubies"), 1, Gold);
    Convert->SetIsEnabled(PS->Profile.DigiRubies > 0); Convert->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(RankedContent, Convert, 4);
    RefreshLiveTimers();
}

void UDigimonVenomNXTGameHUDWidget::ApplyRivalActivityPage(const FDigimonAIRivalActivityPage& Page)
{
    if (Page.PageIndex != RivalPageIndex && RivalPageIndex < Page.TotalPages) return; // Ignore older navigation responses.
    if (bHasRivalSnapshot && Page.ServerUnix < RivalSnapshot.ServerUnix) return;
    RivalPageIndex = Page.PageIndex;
    RivalSnapshot = Page;
    bHasRivalSnapshot = true;
    bRivalWindowExpired = false;
    RivalSnapshotReceivedAt = FPlatformTime::Seconds();
    if (ActivePage == TEXT("Rivals")) RefreshRivals();
}

void UDigimonVenomNXTGameHUDWidget::RequestLivePage()
{
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    if (!PC || !bMenuOpen) return;
    if (ActivePage == TEXT("Rivals")) PC->ServerRequestAIRivalActivity(RivalPageIndex, 12);
    else if (ActivePage == TEXT("Ranked")) PC->ServerRequestRankedStatus();
    else if (ActivePage == TEXT("Season")) PC->ServerRequestSeasonStatus();
}

void UDigimonVenomNXTGameHUDWidget::RefreshLivePages()
{
    if (bMenuOpen && (ActivePage == TEXT("Ranked") || ActivePage == TEXT("Shop"))) RefreshAll();
}

void UDigimonVenomNXTGameHUDWidget::RefreshLiveTimers()
{
    if (ActivePage == TEXT("Rivals") && RivalCountdownText)
    {
        if (!bHasRivalSnapshot) RivalCountdownText->SetText(FText::FromString(TEXT("Connecting to the activity feed...")));
        else
        {
            const int64 Now = RivalSnapshot.ServerUnix + static_cast<int64>(FPlatformTime::Seconds() - RivalSnapshotReceivedAt);
            const int64 Remaining = FMath::Max<int64>(0, RivalSnapshot.WindowEndUnix - Now);
            RivalCountdownText->SetText(FText::FromString(Remaining > 0
                ? FString::Printf(TEXT("12-HOUR WINDOW   /   RESETS IN %s   /   LIVE EVERY 5 SECONDS"), *DigimonVenomNXTUI::Countdown(Remaining))
                : TEXT("NEW 12-HOUR WINDOW   /   REFRESHING ACTIVITY...")));
            if (Remaining == 0 && !bRivalWindowExpired)
            {
                bRivalWindowExpired = true;
                RefreshRivals(); // Show zero counters immediately; persistent parties are unchanged.
                LiveRefreshAccumulator = 5.0f;
            }
        }
    }
    if (ActivePage == TEXT("Ranked"))
    {
        const ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
        if (!PS) return;
        const auto& R = PS->Profile.Ranked;
        const int64 Now = RankedSnapshotUnix + static_cast<int64>(FPlatformTime::Seconds() - RankedSnapshotReceivedAt);
        if (RankedCountdownText) RankedCountdownText->SetText(FText::FromString(R.ServerUnix > 0 && R.SeasonEndsUnix > 0 ? FString::Printf(TEXT("SEASON %s   •   CLOSES IN %s"), *R.WeeklySeasonId, *DigimonVenomNXTUI::Countdown(R.SeasonEndsUnix - Now)) : TEXT("Synchronizing season...")));
        if (RankedEnergyText)
        {
            const FString Recharge = R.NextEnergyUnix > 0 ? FString::Printf(TEXT("NEXT +1 IN %s"), *DigimonVenomNXTUI::Countdown(R.NextEnergyUnix - Now)) : TEXT("FULLY CHARGED");
            RankedEnergyText->SetText(FText::FromString(FString::Printf(TEXT("ENERGY   %d / %d   •   %s"), R.Energy, R.EnergyCap, *Recharge)));
        }
    }
}

void UDigimonVenomNXTGameHUDWidget::RefreshRivals()
{
    if (!RivalsContent || !WidgetTree) return;
    using namespace DigimonHUDUI;
    if (!bRivalsLayoutBuilt)
    {
        bRivalsLayoutBuilt = true;
        RivalsContent->ClearChildren();
        Add(RivalsContent, T(WidgetTree, TEXT("A WORLD THAT KEEPS MOVING"), 20, Gold, true), 2);
        RivalSummaryText = T(WidgetTree, TEXT("Connecting..."), 15, Text, true); Add(RivalsContent, RivalSummaryText, 3);
        Add(RivalsContent, T(WidgetTree, TEXT("Watch every rival explore, battle, gather scan data and build their team. These are the current 12-hour totals for every bot on this server. Counters reset together; their partners, levels and collections persist."), 14, Muted), 3);
        RivalCountdownText = T(WidgetTree, TEXT(""), 13, Accent, true); Add(RivalsContent, RivalCountdownText, 5);
        UUniformGridPanel* Metrics = WidgetTree->ConstructWidget<UUniformGridPanel>(); Metrics->SetSlotPadding(FMargin(4)); Add(RivalsContent, Metrics, 4);
        const TCHAR* Labels[] = {TEXT("WILD BATTLES"),TEXT("VICTORIES"),TEXT("DEFEATS"),TEXT("MATERIALIZED"),TEXT("LEVEL UPS"),TEXT("MAP TRAVELS")};
        for (int32 Index = 0; Index < 6; ++Index)
        {
            UBorder* Metric = Card(WidgetTree); UVerticalBox* Info = WidgetTree->ConstructWidget<UVerticalBox>(); Metric->SetContent(Info);
            Add(Info, T(WidgetTree, Labels[Index], 11, Muted, true), 1);
            UTextBlock* Value = T(WidgetTree, TEXT("—"), 27, Index == 3 ? Gold : Accent, true); Add(Info, Value, 2); RivalMetricValues.Add(Value);
            Metrics->AddChildToUniformGrid(Metric, Index / 3, Index % 3);
        }
        UBorder* Totals = Card(WidgetTree); RivalTotalsText = T(WidgetTree, TEXT("Waiting for server activity..."), 14, Text); Totals->SetContent(RivalTotalsText); Add(RivalsContent, Totals, 4);
        UHorizontalBox* Pager = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(RivalsContent, Pager, 6);
        RivalPreviousButton = Action(WidgetTree, TEXT("← PREVIOUS"), TEXT("rivalspage"));
        RivalPreviousButton->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Pager->AddChildToHorizontalBox(RivalPreviousButton);
        RivalPageText = T(WidgetTree, TEXT("PAGE 1"), 14, Gold, true); RivalPageText->SetJustification(ETextJustify::Center);
        if (UHorizontalBoxSlot* S = Pager->AddChildToHorizontalBox(RivalPageText)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
        RivalNextButton = Action(WidgetTree, TEXT("NEXT →"), TEXT("rivalspage"));
        RivalNextButton->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Pager->AddChildToHorizontalBox(RivalNextButton);
        RivalRowsBox = WidgetTree->ConstructWidget<UVerticalBox>(); Add(RivalsContent, RivalRowsBox, 4);
    }
    RivalSummaryText->SetText(FText::FromString(bHasRivalSnapshot ? FString::Printf(TEXT("%d ACTIVE RIVAL RECORDS   /   SERVER-WIDE ACTIVITY"), RivalSnapshot.TotalRivals) : TEXT("Loading server-wide activity...")));
    RivalPreviousButton->SetIsEnabled(bHasRivalSnapshot && RivalPageIndex > 0);
    RivalPreviousButton->InitializeAction(TEXT("rivalspage"), RivalPageIndex - 1);
    RivalNextButton->SetIsEnabled(bHasRivalSnapshot && RivalPageIndex + 1 < RivalSnapshot.TotalPages);
    RivalNextButton->InitializeAction(TEXT("rivalspage"), RivalPageIndex + 1);
    RivalPageText->SetText(FText::FromString(FString::Printf(TEXT("PAGE %d / %d"), RivalPageIndex + 1, FMath::Max(1, RivalSnapshot.TotalPages))));
    if (!bHasRivalSnapshot) { RefreshLiveTimers(); return; }
    const FDigimonAIRivalActivityCounters Empty;
    const FDigimonAIRivalActivityCounters& Totals = bRivalWindowExpired ? Empty : RivalSnapshot.Totals;
    const int32 Values[] = {Totals.WildBattles, Totals.WildWins, Totals.WildLosses, Totals.Materializations, Totals.LevelUps, Totals.MapTravels};
    for (int32 Index = 0; Index < RivalMetricValues.Num(); ++Index) RivalMetricValues[Index]->SetText(FText::AsNumber(Values[Index]));
    auto FormatCounters = [](const FDigimonAIRivalActivityCounters& C)
    {
        return FString::Printf(TEXT("Wild: %d battles  /  %d W  /  %d L  /  %d D\nTamer: %d battles  /  %d W  /  %d L  /  %d D\nRanked: %d battles  /  %d W  /  %d L  /  %d D\nScan gained: %d%%   •   Materialized: %d   •   XP gained: %lld\nLevel ups: %d   •   Evolutions: %d   •   De-evolutions: %d   •   Map travels: %d\nABI gained: %d   •   CAM gained: %d\nHeals: %d   •   Training: %d   •   Items bought: %d\nCredits earned: %lld   •   Credits spent: %lld"), C.WildBattles, C.WildWins, C.WildLosses, C.WildDraws, C.TrainerBattles, C.TrainerWins, C.TrainerLosses, C.TrainerDraws, C.RankedBattles, C.RankedWins, C.RankedLosses, C.RankedDraws, C.ScanGained, C.Materializations, C.ExperienceGained, C.LevelUps, C.Evolutions, C.DeEvolutions, C.MapTravels, C.ABIGained, C.CAMGained, C.Heals, C.TrainingActions, C.ItemsPurchased, C.CreditsEarned, C.CreditsSpent);
    };
    RivalTotalsText->SetText(FText::FromString(TEXT("ALL RIVALS / WINDOW TOTALS\n\n") + FormatCounters(Totals)));
    TArray<FString> NewIds;
    for (const auto& Row : RivalSnapshot.Rows) NewIds.Add(Row.RivalId);
    if (NewIds != RivalVisibleIds || (NewIds.IsEmpty() && RivalRowsBox->GetChildrenCount() == 0))
    {
        RivalVisibleIds = NewIds;
        RivalRowsBox->ClearChildren(); RivalRowTexts.Reset(); RivalChallengeButtons.Reset();
        for (const auto& Row : RivalSnapshot.Rows)
        {
            UBorder* CardWidget = Card(WidgetTree); UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); CardWidget->SetContent(Body);
            UTextBlock* Header = T(WidgetTree, TEXT(""), 17, Gold, true); Add(Body, Header, 2); RivalRowTexts.Add(Header);
            UTextBlock* Activity = T(WidgetTree, TEXT(""), 13, Accent, true); Add(Body, Activity, 2); RivalRowTexts.Add(Activity);
            UTextBlock* Stats = T(WidgetTree, TEXT(""), 13, Text); Add(Body, Stats, 3); RivalRowTexts.Add(Stats);
            UDigimonVenomNXTActionButton* Challenge = Action(WidgetTree, TEXT("CHALLENGE ON YOUR MAP"), TEXT("rival:") + Row.RivalId, 0, Purple);
            Challenge->OnAction.AddDynamic(this, &UDigimonVenomNXTGameHUDWidget::HandleAction); Add(Body, Challenge, 3); RivalChallengeButtons.Add(Challenge);
            Add(RivalRowsBox, CardWidget, 5);
        }
        if (NewIds.IsEmpty()) Add(RivalRowsBox, T(WidgetTree, TEXT("No AI rivals are currently enabled on this server."), 15, Muted), 5);
    }
    const ADigimonVenomNXTPlayerState* PS = GetDigimonPlayerState();
    for (int32 Index = 0; Index < RivalSnapshot.Rows.Num(); ++Index)
    {
        const FDigimonAIRivalActivityRow& Row = RivalSnapshot.Rows[Index];
        RivalRowTexts[Index * 3]->SetText(FText::FromString(FString::Printf(TEXT("%s   /   LV.%d   /   MAP %03d"), *Row.DisplayName, Row.TamerLevel, Row.MapId)));
        RivalRowTexts[Index * 3 + 1]->SetText(FText::FromString(FString::Printf(TEXT("%s   •   PARTY %d   •   COLLECTION %d"), *Row.CurrentActivity, Row.PartySize, Row.CollectionSize)));
        RivalRowTexts[Index * 3 + 2]->SetText(FText::FromString(FormatCounters(bRivalWindowExpired ? Empty : Row.Stats)));
        RivalChallengeButtons[Index]->SetIsEnabled(PS && PS->Profile.CurrentMapId == Row.MapId && PS->Profile.Party.Num() > 0);
    }
    RefreshLiveTimers();
}

void UDigimonVenomNXTGameHUDWidget::RefreshRelayFieldHUD()
{
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS=GetDigimonPlayerState();
    const bool bInRelay=PC&&PC->IsInRelay()&&PS;
    const bool bVisible=bInRelay&&!bMenuOpen&&bCompactHUDVisible&&!PC->CurrentBattle;
    if(RelayObjectiveRoot)RelayObjectiveRoot->SetVisibility(bVisible?ESlateVisibility::HitTestInvisible:ESlateVisibility::Collapsed);
    if(!bInRelay)
    {
        if(IsRelayDialogueOpen())CloseRelayDialogue();
        if(FieldHintText)FieldHintText->SetText(FText::FromString(TEXT("WASD / ARROWS  Explore     L  DigiLab     M / TAB  Menu     Mouse Wheel  Zoom     H  Hide HUD")));
        return;
    }
    const EDigimonPrivateCampaign Campaign=PC->GetStoryCampaign();
    const bool bChronicles=PC->IsInChronicles();
    const auto& P=DigimonVenomNXTCampaign::Progress(PS->Profile,Campaign);
    const FDigimonRelayMap* Map=DigimonVenomNXTCampaign::GetMap(Campaign,PC->GetRelayMapId());
    const bool bGhostLine=PC->IsInGhostLine();
    if(RelayCampaignLabel)RelayCampaignLabel->SetText(FText::FromString(DigimonVenomNXTCampaign::Name(Campaign).ToUpper() + (bGhostLine?TEXT("  /  PRIVATE CASE FILE"):TEXT("  /  PRIVATE JOURNEY"))));
    if(HeaderWorld&&Map)HeaderWorld->SetText(FText::FromString(FString::Printf(TEXT("PRIVATE %s  •  %s  •  %d/%d %s"),bGhostLine?TEXT("SUPER XROS WARS"):bChronicles?TEXT("WORLD DS"):TEXT("DAWN"),*Map->Name,P.Badges.Num(),bGhostLine?30:bChronicles?17:8,bGhostLine?TEXT("proofs"):bChronicles?TEXT("crests"):TEXT("badges"))));
    if(RelayObjectiveTitle&&Map)RelayObjectiveTitle->SetText(FText::FromString(FString::Printf(TEXT("%02d / %02d  •  %s"),Map->MapId,DigimonVenomNXTCampaign::Maps(Campaign).Num(),*Map->Name)));
    if(RelayObjectiveText)RelayObjectiveText->SetText(FText::FromString(DigimonVenomNXTCampaign::Objective(Campaign,P)));
    FString Hint=TEXT("M / TAB  Journal & services  •  Follow the map's paths");
    if(const FDigimonRelayNPC* NPC=DigimonVenomNXTCampaign::GetNPC(Campaign,PC->GetNearestRelayNPC()))Hint=FString::Printf(TEXT("E  Talk to %s"),*NPC->Name);
    else if(PC->CanUseRelayPortal(true))Hint=PC->GetRelayPortalTarget(true)==1?TEXT("E  Return uplink to the Backchannel"):TEXT("E  Use exit to next map");
    else if(PC->CanUseRelayPortal(false))Hint=TEXT("E  Return to previous map");
    if(RelayInteractionText)RelayInteractionText->SetText(FText::FromString(Hint));
    if(FieldHintText)FieldHintText->SetText(FText::FromString(TEXT("WASD / ARROWS  Explore    E  Interact    L  DigiLab    M / TAB  Journal & services    H  Hide HUD")));
    if(PC->CurrentBattle&&IsRelayDialogueOpen())CloseRelayDialogue();
}

void UDigimonVenomNXTGameHUDWidget::ShowRelayDialogue(FName NPCId,const FString& Dialogue,const FDigimonRelayProgress& ConfirmedProgress)
{
    using namespace DigimonHUDUI;
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    ADigimonVenomNXTPlayerState* PS=GetDigimonPlayerState();
    const EDigimonPrivateCampaign Campaign=PC?PC->GetStoryCampaign():EDigimonPrivateCampaign::Relay;
    const FDigimonRelayNPC* NPC=DigimonVenomNXTCampaign::GetNPC(Campaign,NPCId);
    if(!RelayDialogueRoot||!RelayDialogueContent||!NPC||!PC||!PS||!PC->IsInRelay())return;
    const FDigimonRelayProgress& Progress=ConfirmedProgress;
    if(!DigimonVenomNXTCampaign::IsNPCVisible(Campaign,Progress,*NPC)) { CloseRelayDialogue(); return; }
    PC->SetFieldMenuOpen(false);
    RelayDialogueNPC=NPCId;
    RelayDialogueContent->ClearChildren();
    const bool bChronicles=PC->IsInChronicles();
    const bool bGhostLine=PC->IsInGhostLine();
    const bool bBattle=DigimonVenomNXTCampaign::IsBattleRole(NPC->Role);
    Add(RelayDialogueContent,T(WidgetTree,bGhostLine?(NPC->Role==EDigimonRelayRole::Quest?TEXT("SUPER XROS WARS  /  ACCESS QUEST"):NPC->Role==EDigimonRelayRole::FinalBoss?TEXT("SUPER XROS WARS  /  FINAL CONFRONTATION"):bBattle?TEXT("SUPER XROS WARS  /  QUEST TAMER"):TEXT("SUPER XROS WARS  /  CONVERSATION")):NPC->Role==EDigimonRelayRole::Quest?TEXT("WORLD DS  /  FIELD ASSIGNMENT"):NPC->Role==EDigimonRelayRole::ParadoxBoss?TEXT("WORLD DS  /  PARADOX GUARDIAN"):NPC->Role==EDigimonRelayRole::FinalBoss?TEXT("WORLD DS  /  THE FINAL SUMMONING"):NPC->Role==EDigimonRelayRole::Gym?TEXT("DAWN WARDEN  /  EARN YOUR DIGIBADGE"):NPC->Role==EDigimonRelayRole::Champion?TEXT("DAWN SUMMIT  /  CHAMPIONSHIP"):NPC->Role==EDigimonRelayRole::Challenger?TEXT("DAWN SUMMIT  /  THE TITLE CONTINUES"):bChronicles?TEXT("WORLD DS  /  CONVERSATION"):TEXT("DAWN STORY  /  CONVERSATION"),10,Gold,true),2);
    UHorizontalBox* Identity=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(RelayDialogueContent,Identity,4);
    USizeBox* Portrait=NPC->Role==EDigimonRelayRole::ParadoxBoss&&!NPC->TeamSpecies.IsEmpty()
        ?DigimonVenomNXTUI::AnimatedPortrait(WidgetTree,NPC->TeamSpecies[0],EDigimonVariant::Paradox,88,88)
        :TextureBox(WidgetTree,LoadTamerThumbnail(NPC->TamerStyleId.ToString()),58,76);
    if(UHorizontalBoxSlot* S=Identity->AddChildToHorizontalBox(Portrait))S->SetPadding(FMargin(0,0,14,0));
    UVerticalBox* Name=WidgetTree->ConstructWidget<UVerticalBox>();
    if(UHorizontalBoxSlot* S=Identity->AddChildToHorizontalBox(Name)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
    Add(Name,T(WidgetTree,NPC->Name,24,Text,true),2);
    if(bBattle)Add(Name,T(WidgetTree,FString::Printf(TEXT("Lv.%d  •  %d partners  •  Your party keeps its real strength"),NPC->Level,NPC->TeamSize),12,Muted),2);
    else Add(Name,T(WidgetTree,bGhostLine?DigimonVenomNXTGhostLine::RoleLabel(*NPC):NPC->Role==EDigimonRelayRole::Healer?TEXT("PARTY CARE"):NPC->Role==EDigimonRelayRole::Shop?TEXT("SHOPKEEPER"):NPC->Role==EDigimonRelayRole::Lab?TEXT("DIGILAB SERVICE"):NPC->Role==EDigimonRelayRole::Farm?TEXT("DIGIFARM SERVICE"):TEXT("STORY CONTACT"),11,Accent,true),2);
    // Bound long conversations independently of the fixed challenge/continue controls.
    // The outer scale box keeps this whole panel within narrower game viewports.
    USizeBox* SpeechBounds=WidgetTree->ConstructWidget<USizeBox>(); SpeechBounds->SetHeightOverride(Dialogue.Len()>500?190.0f:130.0f);
    UScrollBox* SpeechScroll=WidgetTree->ConstructWidget<UScrollBox>(); SpeechScroll->SetScrollBarVisibility(ESlateVisibility::Visible); SpeechBounds->AddChild(SpeechScroll);
    UTextBlock* Speech=T(WidgetTree,Dialogue,16,Text); Speech->SetWrapTextAt(750.0f); SpeechScroll->AddChild(Speech); Add(RelayDialogueContent,SpeechBounds,8);
    if(Dialogue.Len()>500)Add(RelayDialogueContent,T(WidgetTree,TEXT("Scroll to read the full conversation"),10,Muted),1);
    UHorizontalBox* Choices=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(RelayDialogueContent,Choices,6);
    auto AddChoice=[&](const FString& Label,const FString& Command,FLinearColor Color)
    {
        UDigimonVenomNXTActionButton* B=Action(WidgetTree,Label,Command,0,Color); B->OnAction.AddDynamic(this,&UDigimonVenomNXTGameHUDWidget::HandleAction);
        if(UHorizontalBoxSlot* S=Choices->AddChildToHorizontalBox(B)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(4)); } return B;
    };
    if(bBattle)
    {
        FString Error;
        if(DigimonVenomNXTCampaign::CanChallenge(Campaign,Progress,*NPC,Error))
        {
            const FString Label=bGhostLine?(NPC->Role==EDigimonRelayRole::FinalBoss?TEXT("CHALLENGE THE FINAL TEAM  /  3 x LV.99"):TEXT("CHALLENGE QUEST TAMER")):NPC->Role==EDigimonRelayRole::ParadoxBoss?TEXT("CHALLENGE PARADOX GUARDIAN"):NPC->Role==EDigimonRelayRole::FinalBoss?TEXT("SUMMON THE LEVEL-100 TRIAD"):NPC->Role==EDigimonRelayRole::Gym?TEXT("CHALLENGE DAWN WARDEN"):NPC->Role==EDigimonRelayRole::Champion?TEXT("CHALLENGE THE CHAMPION"):NPC->Role==EDigimonRelayRole::Challenger?(Progress.bIsChampion?TEXT("DEFEND YOUR TITLE"):TEXT("RECLAIM YOUR TITLE")):Progress.DefeatedTamers.Contains(NPC->Id)?TEXT("TRAINING REMATCH"):TEXT("CHALLENGE TAMER");
            AddChoice(Label,TEXT("relaydialoguechallenge"),Gold);
        }
        else if(!Error.IsEmpty())Add(RelayDialogueContent,T(WidgetTree,Error,12,Muted),3);
    }
    else if((bChronicles||bGhostLine)&&NPC->Role==EDigimonRelayRole::Quest)
    {
        const bool bAccepted=Progress.AcceptedQuests.Contains(NPC->QuestId);
        const bool bComplete=Progress.CompletedObjectives.Contains(NPC->QuestId);
        const bool bReady=DigimonVenomNXTCampaign::QuestObjectiveCount(Campaign,Progress,NPC->QuestId)>=FMath::Max(1,NPC->QuestTarget);
        const FString QuestAction=bGhostLine?TEXT("ghostlinequest"):TEXT("chroniclesquest");
        if(!bComplete&&!bAccepted)AddChoice(bGhostLine?TEXT("OPEN THIS CASE"):TEXT("ACCEPT ASSIGNMENT"),QuestAction,Gold);
        else if(!bComplete&&bReady)AddChoice(bGhostLine?TEXT("CONFIRM CASE REPORT"):TEXT("REPORT FINDINGS & COMPLETE QUEST"),QuestAction,Gold);
        else Add(RelayDialogueContent,T(WidgetTree,bGhostLine?(bComplete?TEXT("CASE FILED  •  Your permanent Access Proof is saved."):TEXT("CASE OPEN  •  Win the named tamer's witnessed trial, then return to report.")):bComplete?TEXT("ASSIGNMENT COMPLETE  •  Your guardian challenge is unlocked."):TEXT("ASSIGNMENT ACTIVE  •  Win the named tamer's field trial, then return here to report."),12,bComplete?Accent:Muted,true),3);
    }
    else if(NPC->Role==EDigimonRelayRole::Shop)AddChoice(TEXT("OPEN SHOP"),TEXT("relaydialogueshop"),Gold);
    else if(NPC->Role==EDigimonRelayRole::Lab)AddChoice(TEXT("OPEN DIGILAB"),TEXT("relaydialoguelab"),Accent);
    else if(NPC->Role==EDigimonRelayRole::Farm)AddChoice(TEXT("OPEN DIGIFARM"),TEXT("relaydialoguefarm"),Accent);
    AddChoice(TEXT("CONTINUE EXPLORING  /  ESC"),TEXT("relaydialogueclose"),Accent);
    RelayDialogueRoot->SetVisibility(ESlateVisibility::Visible);
    PC->SetRelayDialogueOpen(true);
    RefreshFieldPartyPresentation();
}

void UDigimonVenomNXTGameHUDWidget::CloseRelayDialogue()
{
    RelayDialogueNPC=NAME_None;
    if(RelayDialogueRoot)RelayDialogueRoot->SetVisibility(ESlateVisibility::Collapsed);
    if(ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))PC->SetRelayDialogueOpen(false);
    RefreshFieldPartyPresentation(true);
}

void UDigimonVenomNXTGameHUDWidget::OpenCommunityTarget(const FString& TargetId, const FString& Name, bool bRival, const FString& PageName)
{
    const FString Destination = PageName == TEXT("Ignore") ? TEXT("Social") : PageName;
    ShowPage(Destination);
    if (ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) PC->SetFieldMenuOpen(true);
    else SetMenuOpen(true);
    if (const TObjectPtr<UDigimonVenomNXTCommunityWidget>* CommunityPage = CommunityPages.Find(Destination))
        if (*CommunityPage) { (*CommunityPage)->OpenTarget(TargetId, Name, bRival); if(PageName == TEXT("Ignore")) (*CommunityPage)->ReviewIgnoreTarget(TargetId, Name); }
}

bool UDigimonVenomNXTGameHUDWidget::HandleCommunityBack()
{
    if (!bMenuOpen) return false;
    if (const TObjectPtr<UDigimonVenomNXTCommunityWidget>* CommunityPage = CommunityPages.Find(ActivePage))
        if (*CommunityPage) return (*CommunityPage)->HandleBack();
    return false;
}

void UDigimonVenomNXTGameHUDWidget::RefreshChatHistory()
{
    if (const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
    {
        if (FieldWorldChat) FieldWorldChat->SetHistory(PC->WorldChatHistory);
        if (MenuWorldChat) MenuWorldChat->SetHistory(PC->WorldChatHistory);
    }
}
