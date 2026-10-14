#include "DigimonVenomNXTMainMenuWidget.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTGameInstance.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTPresentationAssets.h"
#include "DigimonVenomNXTVideoSettingsWidget.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "InputCoreTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/ScaleBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"

namespace DigimonMenuUI
{
    static const FLinearColor BG(0.012f, 0.022f, 0.052f, 1.0f);
    static const FLinearColor Panel(0.025f, 0.055f, 0.11f, 0.97f);
    static const FLinearColor Accent(0.06f, 0.85f, 0.95f, 1.0f);
    static const FLinearColor Accent2(1.0f, 0.76f, 0.30f, 1.0f);
    static const FLinearColor Text(0.92f, 0.97f, 1.0f, 1.0f);
    static const FLinearColor Muted(0.70f, 0.79f, 0.86f, 1.0f);
    static const FLinearColor Error(1.0f, 0.34f, 0.36f, 1.0f);

    UTextBlock* TextBlock(UWidgetTree* Tree, const FString& Value, int32 Size, FLinearColor Color, bool bBold=false)
    {
        UTextBlock* T = Tree->ConstructWidget<UTextBlock>();
        T->SetText(FText::FromString(Value));
        T->SetAutoWrapText(true);
        T->SetColorAndOpacity(FSlateColor(Color));
        FSlateFontInfo Font = T->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular"));
        T->SetFont(Font);
        return T;
    }

    UButton* Button(UWidgetTree* Tree, const FString& Label)
    {
        UButton* B = Tree->ConstructWidget<UButton>();
        DigimonVenomNXTUI::StyleButton(B, Accent);
        UTextBlock* T = TextBlock(Tree, Label, 16, Text, true);
        T->SetJustification(ETextJustify::Center);
        B->SetToolTipText(FText::FromString(Label));
        B->AddChild(T);
        return B;
    }

    UEditableTextBox* Input(UWidgetTree* Tree, const FString& Hint, bool bPassword)
    {
        UEditableTextBox* E = Tree->ConstructWidget<UEditableTextBox>();
        E->SetHintText(FText::FromString(Hint));
        E->SetIsPassword(bPassword);
        DigimonVenomNXTUI::StyleInput(E);
        return E;
    }

    void Add(UVerticalBox* Box, UWidget* Widget, float Pad=7.0f, bool bFill=false)
    {
        if (UVerticalBoxSlot* Slot = Box->AddChildToVerticalBox(Widget))
        {
            Slot->SetPadding(FMargin(0, Pad));
            Slot->SetHorizontalAlignment(HAlign_Fill);
            if (bFill) Slot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        }
    }
}

void UDigimonVenomNXTMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    BuildNativeUI();
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UDigimonVenomNXTAuthSubsystem* Auth = GI->GetSubsystem<UDigimonVenomNXTAuthSubsystem>())
        {
            Auth->OnAuthResult.RemoveDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleAuthResult);
            Auth->OnAuthResult.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleAuthResult);
        }
    }
}

void UDigimonVenomNXTMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildNativeUI();
    UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr;
    if (Auth && Auth->HasPendingCredentials())
    {
        ShowServerPage();
    }
    else
    {
        ShowAuthentication();
        if (Auth && !Auth->GetLastAuthMessage().IsEmpty()) SetAuthStatus(Auth->GetLastAuthMessage(), !Auth->WasLastAuthSuccessful());
    }
}

void UDigimonVenomNXTMainMenuWidget::BuildNativeUI()
{
    if (bBuilt || !WidgetTree) return;
    bBuilt = true;
    using namespace DigimonMenuUI;

    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>();
    WidgetTree->RootWidget = Root;
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, Root, nullptr, FLinearColor(0.003f,0.013f,0.030f,0.24f));
    UScaleBox* Responsive = WidgetTree->ConstructWidget<UScaleBox>();
    Responsive->SetStretch(EStretch::ScaleToFit);
    Responsive->SetStretchDirection(EStretchDirection::DownOnly);
    LoginSurface = Responsive;
    if (UOverlaySlot* ResponsiveSlot = Root->AddChildToOverlay(Responsive))
    {
        ResponsiveSlot->SetHorizontalAlignment(HAlign_Fill);
        ResponsiveSlot->SetVerticalAlignment(VAlign_Fill);
        ResponsiveSlot->SetPadding(FMargin(24.0f));
    }
    USizeBox* Size = WidgetTree->ConstructWidget<USizeBox>();
    Size->SetWidthOverride(820.0f);
    Size->SetHeightOverride(920.0f);
    Responsive->AddChild(Size);

    UBorder* PanelBorder = WidgetTree->ConstructWidget<UBorder>();
    DigimonVenomNXTUI::StylePanel(PanelBorder, FLinearColor(0.010f,0.027f,0.055f,0.94f));
    PanelBorder->SetPadding(FMargin(40));
    Size->AddChild(PanelBorder);

    UVerticalBox* Main = WidgetTree->ConstructWidget<UVerticalBox>();
    UScrollBox* MainScroll = WidgetTree->ConstructWidget<UScrollBox>();
    PanelBorder->SetContent(MainScroll);
    MainScroll->AddChild(Main);

    UHorizontalBox* TitleRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Main, TitleRow, 2);
    TitleRow->AddChildToHorizontalBox(DigimonVenomNXTUI::Texture(WidgetTree, DigimonVenomNXTPresentationAssets::LoadTexture(TEXT("TitleCoronamon")), 74, 104));
    UTextBlock* Title = TextBlock(WidgetTree, TEXT("DIGIMON\nVENOM NXT"), 34, Accent, true);
    Title->SetJustification(ETextJustify::Center);
    if (UHorizontalBoxSlot* S = TitleRow->AddChildToHorizontalBox(Title)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
    TitleRow->AddChildToHorizontalBox(DigimonVenomNXTUI::Texture(WidgetTree, DigimonVenomNXTPresentationAssets::LoadTexture(TEXT("TitleLunamon")), 74, 104));
    UTextBlock* Subtitle = TextBlock(WidgetTree, TEXT("EXPLORE • SCAN • DIGIVOLVE • COMPETE"), 14, Muted, true);
    Subtitle->SetJustification(ETextJustify::Center);
    Add(Main, Subtitle, 3);

    USpacer* Divider = WidgetTree->ConstructWidget<USpacer>(); Divider->SetSize(FVector2D(1, 16)); Add(Main, Divider, 2);
    PageSwitcher = WidgetTree->ConstructWidget<UWidgetSwitcher>();
    Add(Main, PageSwitcher, 0, true);

    // Authentication page
    UVerticalBox* AuthPage = WidgetTree->ConstructWidget<UVerticalBox>();
    PageSwitcher->AddChild(AuthPage);
    UTextBlock* AuthHead = TextBlock(WidgetTree, TEXT("BEGIN YOUR NEXT CHAPTER"), 24, Text, true); Add(AuthPage, AuthHead, 8);
    UTextBlock* AuthBlurb = TextBlock(WidgetTree, TEXT("Create a tamer account or sign in to continue your adventure. Your collection, partners and progress travel with your account on this world."), 15, Muted);
    AuthBlurb->SetAutoWrapText(true); Add(AuthPage, AuthBlurb, 5);
    UsernameInput = Input(WidgetTree, TEXT("Username (3–24 letters, numbers or underscore)"), false); Add(AuthPage, UsernameInput, 6);
    PasswordInput = Input(WidgetTree, TEXT("Password (8–128 characters)"), true); Add(AuthPage, PasswordInput, 6);
    UHorizontalBox* AuthButtons = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(AuthPage, AuthButtons, 10);
    UButton* Create = Button(WidgetTree, TEXT("CREATE ACCOUNT"));
    UButton* Login = Button(WidgetTree, TEXT("LOG IN"));
    if (UHorizontalBoxSlot* S = AuthButtons->AddChildToHorizontalBox(Create)) { S->SetPadding(FMargin(0,0,6,0)); S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); }
    if (UHorizontalBoxSlot* S = AuthButtons->AddChildToHorizontalBox(Login)) { S->SetPadding(FMargin(6,0,0,0)); S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); }
    Create->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleCreateAccount);
    Login->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleLogin);
    AuthStatusText = TextBlock(WidgetTree, TEXT(""), 14, Muted); AuthStatusText->SetAutoWrapText(true); Add(AuthPage, AuthStatusText, 5);

    // Server page
    UVerticalBox* ServerPage = WidgetTree->ConstructWidget<UVerticalBox>();
    PageSwitcher->AddChild(ServerPage);
    WelcomeText = TextBlock(WidgetTree, TEXT("WELCOME, TAMER"), 26, Text, true); Add(ServerPage, WelcomeText, 5);
    ConnectionText = TextBlock(WidgetTree, TEXT(""), 14, Muted); ConnectionText->SetAutoWrapText(true); Add(ServerPage, ConnectionText, 4);

    UBorder* JoinBox = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(JoinBox, FLinearColor(0.015f,0.070f,0.10f,0.95f)); JoinBox->SetPadding(FMargin(20)); Add(ServerPage, JoinBox, 8);
    UVerticalBox* JoinContent = WidgetTree->ConstructWidget<UVerticalBox>(); JoinBox->SetContent(JoinContent);
    Add(JoinContent, TextBlock(WidgetTree, TEXT("PUBLIC WORLD"), 20, Accent, true), 3);
    UTextBlock* JoinInfo = TextBlock(WidgetTree, TEXT("Step into a living world of wild Digimon and rival tamers. Join with your tamer account whenever a player slot is available."), 15, Text); JoinInfo->SetAutoWrapText(true); Add(JoinContent, JoinInfo, 4);
    JoinWorldButton = Button(WidgetTree, TEXT("JOIN PUBLIC WORLD")); Add(JoinContent, JoinWorldButton, 7); JoinWorldButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleJoin);

    UBorder* HostBox = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(HostBox, FLinearColor(0.047f,0.034f,0.083f,0.95f)); HostBox->SetPadding(FMargin(20)); Add(ServerPage, HostBox, 8);
    UVerticalBox* HostContent = WidgetTree->ConstructWidget<UVerticalBox>(); HostBox->SetContent(HostContent);
    Add(HostContent, TextBlock(WidgetTree, TEXT("ADMIN HOST & PLAY"), 20, Accent2, true), 3);
    HostInfoText = TextBlock(WidgetTree, TEXT("World owners can start a public world on this machine with their hosting password. Players join through the public world button above."), 15, Text); HostInfoText->SetAutoWrapText(true); Add(HostContent, HostInfoText, 4);
    AdminPasswordInput = Input(WidgetTree, TEXT("Admin hosting password"), true); Add(HostContent, AdminPasswordInput, 6);
    UButton* Host = Button(WidgetTree, TEXT("HOST PUBLIC WORLD")); DigimonVenomNXTUI::StyleButton(Host, Accent2); Add(HostContent, Host, 7); Host->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleHost);

    ServerStatusText = TextBlock(WidgetTree, TEXT(""), 14, Muted); ServerStatusText->SetAutoWrapText(true); Add(ServerPage, ServerStatusText, 4);
    UButton* Logout = Button(WidgetTree, TEXT("LOG OUT")); DigimonVenomNXTUI::StyleButton(Logout, Muted); Add(ServerPage, Logout, 6); Logout->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleLogout);

    // Device video settings are available before authentication or joining a
    // world. The same native screen is used by the in-game Video tab.
    VideoMenuButton = Button(WidgetTree, TEXT("VIDEO SETTINGS"));
    Add(Main, VideoMenuButton, 10);
    VideoMenuButton->SetToolTipText(FText::FromString(TEXT("Display, frame rate, VSync and graphics quality for this device.")));
    VideoMenuButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleOpenVideo);
    UButton* ExitGameButton = Button(WidgetTree, TEXT("EXIT GAME"));
    DigimonVenomNXTUI::StyleButton(ExitGameButton, Muted);
    ExitGameButton->SetToolTipText(FText::FromString(TEXT("Close Digimon Venom NXT and return to your desktop.")));
    Add(Main, ExitGameButton, 4);
    ExitGameButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleExitGame);

    UScaleBox* VideoFit = WidgetTree->ConstructWidget<UScaleBox>();
    VideoFit->SetStretch(EStretch::ScaleToFit);
    VideoFit->SetStretchDirection(EStretchDirection::DownOnly);
    if (UOverlaySlot* ChildSlot = Root->AddChildToOverlay(VideoFit))
    {
        ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        ChildSlot->SetVerticalAlignment(VAlign_Fill);
        ChildSlot->SetPadding(FMargin(20));
    }
    VideoSurface = VideoFit;
    USizeBox* VideoBounds = WidgetTree->ConstructWidget<USizeBox>();
    VideoBounds->SetWidthOverride(1100); VideoBounds->SetHeightOverride(820); VideoFit->AddChild(VideoBounds);
    UBorder* VideoPanel = WidgetTree->ConstructWidget<UBorder>();
    DigimonVenomNXTUI::StylePanel(VideoPanel, FLinearColor(0.010f, 0.027f, 0.055f, 0.99f));
    VideoPanel->SetPadding(FMargin(16)); VideoBounds->AddChild(VideoPanel);
    UVerticalBox* VideoBody = WidgetTree->ConstructWidget<UVerticalBox>(); VideoPanel->SetContent(VideoBody);
    UButton* BackButton = Button(WidgetTree, TEXT("BACK TO MAIN MENU"));
    BackButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTMainMenuWidget::HandleCloseVideo);
    Add(VideoBody, BackButton, 4);
    VideoSettings = CreateWidget<UDigimonVenomNXTVideoSettingsWidget>(GetOwningPlayer(), UDigimonVenomNXTVideoSettingsWidget::StaticClass());
    if (VideoSettings) Add(VideoBody, VideoSettings, 4, true);
    VideoSurface->SetVisibility(ESlateVisibility::Collapsed);
}

void UDigimonVenomNXTMainMenuWidget::NativeDestruct()
{
    if (VideoSettings) VideoSettings->CloseSettings();
    Super::NativeDestruct();
}

void UDigimonVenomNXTMainMenuWidget::HandleExitGame()
{
    if (VideoSettings) VideoSettings->CloseSettings();
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UDigimonVenomNXTMainMenuWidget::HandleOpenVideo()
{
    if (!VideoSurface || !VideoSettings) return;
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UINavigate);
    if (LoginSurface) LoginSurface->SetVisibility(ESlateVisibility::Collapsed);
    VideoSurface->SetVisibility(ESlateVisibility::Visible);
    VideoSettings->OpenSettings();
}

void UDigimonVenomNXTMainMenuWidget::HandleCloseVideo()
{
    if (VideoSettings) VideoSettings->CloseSettings();
    if (VideoSurface) VideoSurface->SetVisibility(ESlateVisibility::Collapsed);
    if (LoginSurface) LoginSurface->SetVisibility(ESlateVisibility::Visible);
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UIBack);
    if (VideoMenuButton) VideoMenuButton->SetKeyboardFocus();
}

FReply UDigimonVenomNXTMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (VideoSurface && VideoSurface->GetVisibility() == ESlateVisibility::Visible &&
        (InKeyEvent.GetKey() == EKeys::Escape || InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right))
    {
        if (!VideoSettings || !VideoSettings->HandleBack()) HandleCloseVideo();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UDigimonVenomNXTMainMenuWidget::ShowAuthentication()
{
    if (PageSwitcher) PageSwitcher->SetActiveWidgetIndex(0);
    SetAuthStatus(TEXT(""));
    if (UsernameInput && GetOwningPlayer()) UsernameInput->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTMainMenuWidget::ShowServerPage()
{
    if (PageSwitcher) PageSwitcher->SetActiveWidgetIndex(1);
    RefreshServerPage();
    if (JoinWorldButton && GetOwningPlayer()) JoinWorldButton->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTMainMenuWidget::RefreshServerPage()
{
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr;
    if (WelcomeText) WelcomeText->SetText(FText::FromString(FString::Printf(TEXT("WELCOME, %s"), Auth ? *Auth->GetUsername().ToUpper() : TEXT("TAMER"))));
    if (ConnectionText)
    {
        const FString Address = UDigimonVenomNXTGameInstance::GetPublicConnectionAddressForSettings();
        ConnectionText->SetText(FText::FromString(FString::Printf(TEXT("WORLD %s   •   UP TO %d TAMERS"), *Address, S->MaxPlayers)));
    }
    if (HostInfoText)
    {
        // Read readiness only. Never display or log the resolved credential.
        const FString HostPassword = S->ResolveAdminHostPassword();
        const bool bHostingConfigured = !HostPassword.IsEmpty() && HostPassword != TEXT("CHANGE_ME");
        const FString HostHelp = bHostingConfigured
            ? TEXT("Start a public world on this machine with your hosting password. Other players join through the public world button above.")
            : TEXT("Hosting setup is required on this machine. Set Admin Host Password in Project Settings > Game > Digimon Venom NXT > Multiplayer > Hosting. Packaged hosts can use DIGIMONVENOMNXT_HOST_PASSWORD or Saved/DigimonVenomNXT/Host.ini. Joining another host does not require this setup.");
        HostInfoText->SetText(FText::FromString(HostHelp));
        HostInfoText->SetColorAndOpacity(FSlateColor(bHostingConfigured ? DigimonMenuUI::Text : DigimonMenuUI::Accent2));
    }
}

void UDigimonVenomNXTMainMenuWidget::SetAuthStatus(const FString& Value, bool bError)
{
    if (!AuthStatusText) return;
    AuthStatusText->SetText(FText::FromString(Value));
    AuthStatusText->SetColorAndOpacity(FSlateColor(bError ? DigimonMenuUI::Error : DigimonMenuUI::Accent));
}

void UDigimonVenomNXTMainMenuWidget::SetServerStatus(const FString& Value, bool bError)
{
    if (!ServerStatusText) return;
    ServerStatusText->SetText(FText::FromString(Value));
    ServerStatusText->SetColorAndOpacity(FSlateColor(bError ? DigimonMenuUI::Error : DigimonMenuUI::Accent));
}

void UDigimonVenomNXTMainMenuWidget::HandleCreateAccount()
{
    if (!UsernameInput || !PasswordInput) return;
    SetAuthStatus(TEXT("Preparing your new tamer account..."));
    if (UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>()) Auth->CreateAccount(UsernameInput->GetText().ToString(), PasswordInput->GetText().ToString());
}

void UDigimonVenomNXTMainMenuWidget::HandleLogin()
{
    if (!UsernameInput || !PasswordInput) return;
    SetAuthStatus(TEXT("Preparing your sign-in..."));
    if (UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>()) Auth->Login(UsernameInput->GetText().ToString(), PasswordInput->GetText().ToString());
}

void UDigimonVenomNXTMainMenuWidget::HandleLogout()
{
    if (UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>()) Auth->Logout();
    if (PasswordInput) PasswordInput->SetText(FText::GetEmpty());
    if (AdminPasswordInput) AdminPasswordInput->SetText(FText::GetEmpty());
    ShowAuthentication();
}

void UDigimonVenomNXTMainMenuWidget::HandleJoin()
{
    FString Error;
    UGameInstance* GI = GetGameInstance();
    if (!UDigimonVenomNXTGameInstance::JoinPublicWorldForGameInstance(GI, Error))
    {
        SetServerStatus(Error.IsEmpty() ? TEXT("Could not join the public world. Check the Output Log for Digimon Venom NXT details.") : Error, true);
    }
    else
    {
        SetServerStatus(TEXT("Connecting..."));
    }
}

void UDigimonVenomNXTMainMenuWidget::HandleHost()
{
    FString Error;
    UGameInstance* GI = GetGameInstance();
    const FString Admin = AdminPasswordInput ? AdminPasswordInput->GetText().ToString() : FString();
    if (!UDigimonVenomNXTGameInstance::HostPublicWorldForGameInstance(GI, Admin, Error))
    {
        SetServerStatus(Error.IsEmpty() ? TEXT("Could not host the public world. Check the Output Log for Digimon Venom NXT details.") : Error, true);
    }
    else
    {
        SetServerStatus(TEXT("Starting the public listen server..."));
    }
}

void UDigimonVenomNXTMainMenuWidget::HandleAuthResult(const FDigimonAuthResult& Result)
{
    if (!Result.bSuccess) { SetAuthStatus(Result.Message, true); return; }
    SetAuthStatus(Result.Message, false);
    if (PasswordInput) PasswordInput->SetText(FText::GetEmpty());
    ShowServerPage();
}
