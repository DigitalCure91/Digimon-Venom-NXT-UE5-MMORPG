#include "DigimonVenomNXTServerConsoleWidget.h"
#include "DigimonVenomNXTServerConsoleCore.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include "Styling/CoreStyle.h"

namespace DigimonServerUI
{
constexpr int32 MaxCachedEntries = 500;
constexpr int32 MaxRenderedRows = 350;
constexpr int32 MaxHistoryEntries = 64;
constexpr int32 MaxCommandLength = 1024;
constexpr float PollInterval = 0.25f;
const FLinearColor Ink(0.009f, 0.020f, 0.037f, 1.0f);
const FLinearColor Panel(0.018f, 0.048f, 0.071f, 1.0f);
const FLinearColor White(0.94f, 0.98f, 1.0f, 1.0f);
const FLinearColor Muted(0.60f, 0.75f, 0.82f, 1.0f);
const FLinearColor Cyan(0.22f, 0.85f, 1.0f, 1.0f);
const FLinearColor Green(0.34f, 0.95f, 0.64f, 1.0f);
const FLinearColor Gold(1.0f, 0.78f, 0.35f, 1.0f);
const FLinearColor Red(1.0f, 0.43f, 0.46f, 1.0f);

UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 11, FLinearColor Color = White, bool bBold = false)
{
    UTextBlock* Result = Tree->ConstructWidget<UTextBlock>();
    Result->SetText(FText::FromString(Value)); Result->SetColorAndOpacity(Color); Result->SetAutoWrapText(true);
    Result->SetFont(FCoreStyle::GetDefaultFontStyle(bBold ? TEXT("Bold") : TEXT("Regular"), Size));
    return Result;
}
void Set(UTextBlock* Widget, const FString& Value)
{
    if (Widget && Widget->GetText().ToString() != Value) Widget->SetText(FText::FromString(Value));
}
void Set(UMultiLineEditableText* Widget, const FString& Value)
{
    if (Widget && Widget->GetText().ToString() != Value) Widget->SetText(FText::FromString(Value));
}
void Add(UVerticalBox* Box, UWidget* Child, float Padding = 3.0f, bool bFill = false)
{
    if (UVerticalBoxSlot* ChildSlot = Box->AddChildToVerticalBox(Child))
    {
        ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
}
void Row(UHorizontalBox* Box, UWidget* Child, bool bFill = false, float Padding = 4.0f)
{
    if (UHorizontalBoxSlot* ChildSlot = Box->AddChildToHorizontalBox(Child))
    {
        ChildSlot->SetPadding(FMargin(Padding, 0)); ChildSlot->SetVerticalAlignment(VAlign_Center);
        if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
}
UBorder* Card(UWidgetTree* Tree, FLinearColor Accent = Cyan, float Padding = 10.0f)
{
    UBorder* Result = Tree->ConstructWidget<UBorder>();
    Result->SetBrush(FSlateRoundedBoxBrush(Panel, 7.0f, Accent.CopyWithNewOpacity(0.30f), 1.0f));
    Result->SetPadding(FMargin(Padding)); return Result;
}
USizeBox* Width(UWidgetTree* Tree, UWidget* Child, float Value)
{
    USizeBox* Result = Tree->ConstructWidget<USizeBox>(); Result->SetWidthOverride(Value); Result->AddChild(Child); return Result;
}
FLinearColor SeverityColor(const FString& Severity)
{
    if (Severity.Equals(TEXT("Error"), ESearchCase::IgnoreCase)) return Red;
    if (Severity.Equals(TEXT("Warning"), ESearchCase::IgnoreCase)) return Gold;
    if (Severity.Equals(TEXT("Success"), ESearchCase::IgnoreCase)) return Green;
    return Cyan;
}
FSlateFontInfo ConsoleFont(int32 Size)
{
    FSlateFontInfo Font = FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), Size);
    Font.bForceMonospaced = true; Font.MonospacedWidth = 0.65f; return Font;
}
FString CommandName(const FString& Command)
{
    TArray<FString> Words; Command.ParseIntoArrayWS(Words);
    FString Name = Words.Num() ? Words[0] : FString();
    Name.RemoveFromStart(TEXT("\"")); Name.RemoveFromEnd(TEXT("\""));
    Name.ToLowerInline(); return Name;
}
bool IsSensitiveCommand(const FString& Command)
{
    const FString Name = CommandName(Command);
    return Name == TEXT("/createaccount") || Name == TEXT("/resetpassword");
}
bool SearchMatches(const FString& Haystack, const FString& Search)
{
    TArray<FString> Terms; Search.ParseIntoArrayWS(Terms);
    for (const FString& Term : Terms) if (!Haystack.Contains(Term, ESearchCase::IgnoreCase)) return false;
    return true;
}
FString SlashName(const FString& Name) { return Name.StartsWith(TEXT("/")) ? Name : TEXT("/") + Name; }
}

UDigimonVenomNXTConsoleFilter::UDigimonVenomNXTConsoleFilter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    using namespace DigimonServerUI;
    InitFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 10));
    InitForegroundColor(FSlateColor(White)); InitIsFocusable(true);
    FComboBoxStyle Style = GetWidgetStyle();
    FButtonStyle ButtonStyle = Style.ComboButtonStyle.ButtonStyle;
    ButtonStyle.SetNormal(FSlateRoundedBoxBrush(Ink, 5.0f, Cyan.CopyWithNewOpacity(0.35f), 1.0f));
    ButtonStyle.SetHovered(FSlateRoundedBoxBrush(Panel, 5.0f, Cyan, 1.0f));
    ButtonStyle.SetPressed(FSlateRoundedBoxBrush(Panel, 5.0f, White, 1.0f));
    ButtonStyle.SetDisabled(FSlateRoundedBoxBrush(Ink, 5.0f));
    Style.ComboButtonStyle.SetButtonStyle(ButtonStyle);
    Style.ComboButtonStyle.SetMenuBorderBrush(FSlateRoundedBoxBrush(Ink, 5.0f, Cyan, 1.0f)); SetWidgetStyle(Style);
    FTableRowStyle Rows = GetItemStyle(); Rows.SetTextColor(FSlateColor(White)); Rows.SetSelectedTextColor(FSlateColor(White));
    Rows.SetEvenRowBackgroundBrush(FSlateRoundedBoxBrush(Ink, 0.0f)); Rows.SetOddRowBackgroundBrush(FSlateRoundedBoxBrush(Ink, 0.0f));
    Rows.SetEvenRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(Panel, 0.0f)); Rows.SetOddRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(Panel, 0.0f));
    Rows.SetActiveBrush(FSlateRoundedBoxBrush(FLinearColor(0.025f, 0.22f, 0.30f, 1.0f), 3.0f));
    Rows.SetActiveHoveredBrush(Rows.ActiveBrush); Rows.SetInactiveBrush(Rows.ActiveBrush); Rows.SetInactiveHoveredBrush(Rows.ActiveBrush); SetItemStyle(Rows);
    SetEnableGamepadNavigationMode(true);
}

TSharedRef<SWidget> UDigimonVenomNXTServerConsoleWidget::RebuildWidget()
{
    BuildLayout(); return Super::RebuildWidget();
}

void UDigimonVenomNXTServerConsoleWidget::NativeConstruct()
{
    Super::NativeConstruct(); BuildLayout(); CheckAccess();
}

void UDigimonVenomNXTServerConsoleWidget::NativeDestruct()
{
    bPageOpen = false; ClearPrivateState(); Super::NativeDestruct();
}

UDigimonVenomNXTServerConsoleSubsystem* UDigimonVenomNXTServerConsoleWidget::Backend() const
{
    return GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
}

bool UDigimonVenomNXTServerConsoleWidget::CheckAccess()
{
    UDigimonVenomNXTServerConsoleSubsystem* Server = Backend();
    const bool bAllowed = Server && Server->CanAccess(GetOwningPlayer());
    if (Content) Content->SetIsEnabled(bAllowed && !bCredentialPromptOpen);
    if (!bAllowed)
    {
        bPageOpen = false; ClearPrivateState();
        if (Root) Root->SetVisibility(ESlateVisibility::Collapsed);
    }
    return bAllowed;
}

void UDigimonVenomNXTServerConsoleWidget::ClearPrivateState()
{
    CloseCredentialPrompt();
    Entries.Reset(); CommandHelp.Reset(); CommandHistory.Reset(); RenderedSequences.Reset(); RenderedRows.Reset();
    LastSequence = 0; PendingEntries = 0; OnlinePlayers = 0; RetainedEntries = 0;
    HistoryIndex = INDEX_NONE; DraftCommand.Reset(); StatusNotice.Reset();
    CategoryFilter.Reset(); SeverityFilter.Reset(); LogSearch.Reset(); HelpSearch.Reset();
    bPaused = false; bFollowLive = true; bLogFilterDirty = false; bHelpFilterDirty = false; bSensitiveDraft = false;
    if (LogRows) LogRows->ClearChildren();
    if (HelpRows) HelpRows->ClearChildren();
    if (CommandInput)
    {
        bUpdatingInput = true; CommandInput->SetText(FText::GetEmpty()); CommandInput->SetIsPassword(false); bUpdatingInput = false;
    }
    if (CategoryPicker) { CategoryPicker->ClearOptions(); CategoryPicker->AddOption(TEXT("All activity")); CategoryPicker->SetSelectedOption(TEXT("All activity")); }
    if (SeverityPicker) SeverityPicker->SetSelectedOption(TEXT("All levels"));
    if (LogSearchInput) LogSearchInput->SetText(FText::GetEmpty());
    if (HelpSearchInput) HelpSearchInput->SetText(FText::GetEmpty());
    DigimonServerUI::Set(SessionReadout, TEXT("Host access required"));
    DigimonServerUI::Set(ViewReadout, FString()); DigimonServerUI::Set(FeedbackText, FString());
    DigimonServerUI::Set(InputHint, FString()); DigimonServerUI::Set(HelpReadout, FString());
}

void UDigimonVenomNXTServerConsoleWidget::OpenConsole()
{
    BuildLayout(); if (!CheckAccess()) return;
    if (bPageOpen) return;
    bPageOpen = true; PollElapsed = 0.0f;
    Root->SetVisibility(ESlateVisibility::Visible);
    UDigimonVenomNXTServerConsoleSubsystem* Server = Backend();
    if (!Server->GetCommandHelp(GetOwningPlayer(), CommandHelp)) { CheckAccess(); return; }
    CommandHelp.Sort([](const FDigimonServerCommandInfo& A, const FDigimonServerCommandInfo& B) { return A.Name < B.Name; });
    FDigimonServerConsoleStatus ServerStatus;
    if (Server->GetStatus(GetOwningPlayer(), ServerStatus))
    {
        LastSequence = FMath::Max<int64>(0, ServerStatus.LatestSequence - DigimonServerUI::MaxCachedEntries);
    }
    bPaused = false; bFollowLive = true; StatusNotice.Reset();
    RebuildHelp(); SelectPage(0); PollEntries();
    DigimonServerUI::Set(InputHint, TEXT("Enter to run  |  Up / Down: history  |  Tab: complete command  |  /help: command guide"));
    SetFeedback(TEXT("Host console ready. Commands affect this server and are recorded in its activity log."), true);
    if (CommandInput && GetOwningPlayer()) CommandInput->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTServerConsoleWidget::CloseConsole()
{
    bPageOpen = false;
    // No credentials, player logs or draft actions survive a closed host page or travel.
    ClearPrivateState();
    if (Root) Root->SetVisibility(ESlateVisibility::Collapsed);
}

bool UDigimonVenomNXTServerConsoleWidget::HandleBack()
{
    if (!bPageOpen || !CheckAccess()) return false;
    if (bCredentialPromptOpen) { CloseCredentialPrompt(); SetFeedback(TEXT("Account action cancelled. No changes were made."), true); return true; }
    if (CommandInput && !CommandInput->GetText().IsEmpty())
    {
        FillCommand(FString()); SetFeedback(TEXT("Command draft cleared. Press Back again to leave the console."), true); return true;
    }
    if (ActivePage != 0) { SelectPage(0); return true; }
    return false;
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTServerConsoleWidget::MakeButton(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload)
{
    UDigimonVenomNXTActionButton* Result = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    Result->InitializeAction(Action, Payload); DigimonVenomNXTUI::StyleButton(Result, Accent);
    Result->OnAction.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleAction);
    UTextBlock* Caption = DigimonServerUI::Text(WidgetTree, Label, 10, DigimonServerUI::White, true);
    Caption->SetJustification(ETextJustify::Center); Result->SetContent(Caption); return Result;
}

void UDigimonVenomNXTServerConsoleWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("ServerConsoleWidgetTree"));
    using namespace DigimonServerUI;
    Root = WidgetTree->ConstructWidget<UBorder>(); WidgetTree->RootWidget = Root;
    Root->SetBrush(FSlateRoundedBoxBrush(Ink, 10.0f, Cyan.CopyWithNewOpacity(0.28f), 1.0f)); Root->SetPadding(FMargin(14));
    UOverlay* RootLayers = WidgetTree->ConstructWidget<UOverlay>(); Root->SetContent(RootLayers);
    Content = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* ChildSlot = RootLayers->AddChildToOverlay(Content)) { ChildSlot->SetHorizontalAlignment(HAlign_Fill); ChildSlot->SetVerticalAlignment(VAlign_Fill); }

    UHorizontalBox* Header = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Content, Header, 1);
    UVerticalBox* Title = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Header, Title, true, 0);
    Add(Title, Text(WidgetTree, TEXT("WORLD SERVER"), 23, White, true), 0);
    Add(Title, Text(WidgetTree, TEXT("HOST CONSOLE  /  LIVE SERVER ACTIVITY"), 10, Cyan, true), 2);
    UVerticalBox* HostStatus = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Header, HostStatus, false, 0);
    UTextBlock* AccessBadge = Text(WidgetTree, TEXT("HOST ACCESS ONLY"), 10, Green, true); AccessBadge->SetJustification(ETextJustify::Right); Add(HostStatus, AccessBadge, 1);
    SessionReadout = Text(WidgetTree, TEXT("Connecting to local host..."), 10, Muted); SessionReadout->SetJustification(ETextJustify::Right); Add(HostStatus, SessionReadout, 1);
    Add(Content, Text(WidgetTree, TEXT("Watch player activity and manage your world. This console is visible only to the player hosting this session."), 10, Muted), 3);

    UHorizontalBox* Tabs = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Content, Tabs, 5);
    UDigimonVenomNXTActionButton* ConsoleTab = MakeButton(TEXT("LIVE CONSOLE"), TEXT("console:page"), Cyan, 0); Row(Tabs, ConsoleTab, true); PageButtons.Add(ConsoleTab);
    UDigimonVenomNXTActionButton* CommandsTab = MakeButton(TEXT("COMMAND GUIDE"), TEXT("console:page"), Cyan, 1); Row(Tabs, CommandsTab, true); PageButtons.Add(CommandsTab);
    UDigimonVenomNXTActionButton* Players = MakeButton(TEXT("ONLINE PLAYERS"), TEXT("console:players"), Green);
    Players->SetToolTipText(FText::FromString(TEXT("Run /players to inspect the server's online player roster."))); Row(Tabs, Players, false);
    Row(Tabs, MakeButton(TEXT("BACK"), TEXT("console:close"), Muted), false);

    Pages = WidgetTree->ConstructWidget<UWidgetSwitcher>(); Add(Content, Pages, 0, true);
    UVerticalBox* ConsolePage = WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(ConsolePage);
    UHorizontalBox* Filters = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ConsolePage, Filters, 3);
    CategoryPicker = WidgetTree->ConstructWidget<UDigimonVenomNXTConsoleFilter>();
    CategoryPicker->AddOption(TEXT("All activity")); CategoryPicker->SetSelectedOption(TEXT("All activity")); CategoryPicker->SetMaxListHeight(280); CategoryPicker->SetContentPadding(FMargin(8));
    CategoryPicker->SetToolTipText(FText::FromString(TEXT("Filter activity by category. Categories appear as the server records them.")));
    CategoryPicker->OnSelectionChanged.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleCategoryChanged); Row(Filters, Width(WidgetTree, CategoryPicker, 150));
    SeverityPicker = WidgetTree->ConstructWidget<UDigimonVenomNXTConsoleFilter>();
    for (const TCHAR* Level : { TEXT("All levels"), TEXT("Info"), TEXT("Success"), TEXT("Warning"), TEXT("Error") }) SeverityPicker->AddOption(Level);
    SeverityPicker->SetSelectedOption(TEXT("All levels")); SeverityPicker->SetMaxListHeight(220); SeverityPicker->SetContentPadding(FMargin(8));
    SeverityPicker->SetToolTipText(FText::FromString(TEXT("Filter messages by severity.")));
    SeverityPicker->OnSelectionChanged.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleSeverityChanged); Row(Filters, Width(WidgetTree, SeverityPicker, 120));
    LogSearchInput = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(LogSearchInput);
    LogSearchInput->SetHintText(FText::FromString(TEXT("Search player, action or message...")));
    LogSearchInput->SetToolTipText(FText::FromString(TEXT("Search the latest 500 buffered entries. Every typed word must match; matching ignores case.")));
    LogSearchInput->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleLogSearchChanged); Row(Filters, LogSearchInput, true);

    UBorder* LogFrame = Card(WidgetTree, Cyan, 4); Add(ConsolePage, LogFrame, 3, true);
    UOverlay* LogOverlay = WidgetTree->ConstructWidget<UOverlay>(); LogFrame->SetContent(LogOverlay);
    LogScroll = WidgetTree->ConstructWidget<UScrollBox>(); LogScroll->SetAnimateWheelScrolling(false); LogScroll->SetAlwaysShowScrollbar(true);
    LogScroll->SetClipping(EWidgetClipping::ClipToBounds); LogScroll->OnUserScrolled.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleUserScrolled);
    if (UOverlaySlot* ChildSlot = LogOverlay->AddChildToOverlay(LogScroll)) { ChildSlot->SetHorizontalAlignment(HAlign_Fill); ChildSlot->SetVerticalAlignment(VAlign_Fill); }
    LogRows = WidgetTree->ConstructWidget<UVerticalBox>(); LogScroll->AddChild(LogRows);
    EmptyMessage = Text(WidgetTree, TEXT("Waiting for server activity..."), 13, Muted); EmptyMessage->SetJustification(ETextJustify::Center);
    if (UOverlaySlot* ChildSlot = LogOverlay->AddChildToOverlay(EmptyMessage)) { ChildSlot->SetHorizontalAlignment(HAlign_Center); ChildSlot->SetVerticalAlignment(VAlign_Center); ChildSlot->SetPadding(FMargin(20)); }
    EmptyMessage->SetVisibility(ESlateVisibility::HitTestInvisible);

    UHorizontalBox* LogControls = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ConsolePage, LogControls, 3);
    PauseButton = MakeButton(TEXT("PAUSE VIEW"), TEXT("console:pause"), Gold); PauseCaption = Cast<UTextBlock>(PauseButton->GetContent()); Row(LogControls, PauseButton);
    PauseButton->SetToolTipText(FText::FromString(TEXT("Pause this view while the server continues recording. Resume catches up from the retained log.")));
    FollowButton = MakeButton(TEXT("FOLLOWING LIVE"), TEXT("console:latest"), Cyan); FollowCaption = Cast<UTextBlock>(FollowButton->GetContent()); Row(LogControls, FollowButton);
    FollowButton->SetToolTipText(FText::FromString(TEXT("Resume and scroll to the newest matching event. Scrolling upward suspends automatic following.")));
    UDigimonVenomNXTActionButton* Clear = MakeButton(TEXT("CLEAR VIEW"), TEXT("console:clear"), Muted); Row(LogControls, Clear);
    Clear->SetToolTipText(FText::FromString(TEXT("Hide currently buffered rows on this page. This does not delete the server activity log.")));
    ViewReadout = Text(WidgetTree, FString(), 9, Muted); ViewReadout->SetJustification(ETextJustify::Right); Row(LogControls, ViewReadout, true);

    UVerticalBox* GuidePage = WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(GuidePage);
    HelpSearchInput = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(HelpSearchInput);
    HelpSearchInput->SetHintText(FText::FromString(TEXT("Find a command: digimon, money, title, firewall...")));
    HelpSearchInput->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleHelpSearchChanged); Add(GuidePage, HelpSearchInput, 3);
    HelpReadout = Text(WidgetTree, FString(), 10, Muted); Add(GuidePage, HelpReadout, 4);
    UScrollBox* HelpScroll = WidgetTree->ConstructWidget<UScrollBox>(); HelpScroll->SetAlwaysShowScrollbar(true); HelpScroll->SetAnimateWheelScrolling(false); Add(GuidePage, HelpScroll, 1, true);
    HelpRows = WidgetTree->ConstructWidget<UVerticalBox>(); HelpScroll->AddChild(HelpRows);

    UBorder* EntryCard = Card(WidgetTree, Green, 9); Add(Content, EntryCard, 5);
    UVerticalBox* EntryBody = WidgetTree->ConstructWidget<UVerticalBox>(); EntryCard->SetContent(EntryBody);
    UHorizontalBox* CommandRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(EntryBody, CommandRow, 1);
    Row(CommandRow, Text(WidgetTree, TEXT("HOST >"), 11, Green, true));
    CommandInput = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(CommandInput);
    CommandInput->SetHintText(FText::FromString(TEXT("Type /help or enter a server command...")));
    CommandInput->SetClearKeyboardFocusOnCommit(false); CommandInput->SetSelectAllTextWhenFocused(false);
    CommandInput->SetToolTipText(FText::FromString(TEXT("Native host commands only. Quote player names that contain spaces. Account/password commands are masked and never enter history.")));
    CommandInput->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleCommandChanged);
    CommandInput->OnTextCommitted.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleCommandCommitted); Row(CommandRow, CommandInput, true);
    ExecuteButton = MakeButton(TEXT("RUN"), TEXT("console:run"), Green); ExecuteButton->SetIsEnabled(false); Row(CommandRow, ExecuteButton);
    InputHint = Text(WidgetTree, FString(), 9, Muted); Add(EntryBody, InputHint, 4);
    Add(EntryBody, Text(WidgetTree, TEXT("COMMAND RESULT  /  scroll to read · select text to copy"), 8, Muted), 1);
    USizeBox* FeedbackBounds = WidgetTree->ConstructWidget<USizeBox>(); FeedbackBounds->SetMaxDesiredHeight(96.0f); Add(EntryBody, FeedbackBounds, 2);
    UScrollBox* FeedbackScroll = WidgetTree->ConstructWidget<UScrollBox>(); FeedbackBounds->AddChild(FeedbackScroll);
    FeedbackText = WidgetTree->ConstructWidget<UMultiLineEditableText>(); FeedbackText->SetIsReadOnly(true); FeedbackText->SetAutoWrapText(true);
    FeedbackText->SetWidgetStyle(FTextBlockStyle().SetFont(ConsoleFont(10)).SetColorAndOpacity(Green)); FeedbackScroll->AddChild(FeedbackText);

    // Credentials use their own masked controls, never the generic command parser or history.
    CredentialOverlay = WidgetTree->ConstructWidget<UBorder>(); CredentialOverlay->SetBrushColor(FLinearColor(0.006f, 0.012f, 0.023f, 0.98f));
    CredentialOverlay->SetPadding(FMargin(22)); CredentialOverlay->SetHorizontalAlignment(HAlign_Center); CredentialOverlay->SetVerticalAlignment(VAlign_Center);
    if (UOverlaySlot* ChildSlot = RootLayers->AddChildToOverlay(CredentialOverlay)) { ChildSlot->SetHorizontalAlignment(HAlign_Fill); ChildSlot->SetVerticalAlignment(VAlign_Fill); }
    USizeBox* DialogBounds = WidgetTree->ConstructWidget<USizeBox>(); DialogBounds->SetWidthOverride(490.0f); CredentialOverlay->SetContent(DialogBounds);
    UBorder* DialogCard = Card(WidgetTree, Gold, 20); DialogBounds->AddChild(DialogCard);
    UVerticalBox* Dialog = WidgetTree->ConstructWidget<UVerticalBox>(); DialogCard->SetContent(Dialog);
    CredentialTitle = Text(WidgetTree, TEXT("ACCOUNT ACCESS"), 20, White, true); Add(Dialog, CredentialTitle, 0);
    CredentialAccount = Text(WidgetTree, FString(), 12, Cyan, true); Add(Dialog, CredentialAccount, 7);
    Add(Dialog, Text(WidgetTree, TEXT("Enter the new password below. It stays out of the command line, command history and activity log."), 11, Muted), 4);
    Add(Dialog, Text(WidgetTree, TEXT("NEW PASSWORD"), 10, White, true), 3);
    CredentialPassword = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(CredentialPassword);
    CredentialPassword->SetIsPassword(true); CredentialPassword->SetHintText(FText::FromString(TEXT("New password"))); CredentialPassword->SetClearKeyboardFocusOnCommit(false); Add(Dialog, CredentialPassword, 2);
    Add(Dialog, Text(WidgetTree, TEXT("CONFIRM PASSWORD"), 10, White, true), 5);
    CredentialConfirmation = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(CredentialConfirmation);
    CredentialConfirmation->SetIsPassword(true); CredentialConfirmation->SetHintText(FText::FromString(TEXT("Repeat new password"))); CredentialConfirmation->SetClearKeyboardFocusOnCommit(false);
    CredentialConfirmation->OnTextCommitted.AddDynamic(this, &UDigimonVenomNXTServerConsoleWidget::HandleCredentialCommitted); Add(Dialog, CredentialConfirmation, 2);
    CredentialFeedback = Text(WidgetTree, FString(), 11, Gold); Add(Dialog, CredentialFeedback, 6);
    UHorizontalBox* CredentialButtons = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Dialog, CredentialButtons, 6);
    Row(CredentialButtons, MakeButton(TEXT("CANCEL"), TEXT("console:credentialcancel"), Muted), true);
    Row(CredentialButtons, MakeButton(TEXT("SAVE ACCOUNT"), TEXT("console:credentialsave"), Green), true);
    CredentialOverlay->SetVisibility(ESlateVisibility::Collapsed);
    Root->SetVisibility(ESlateVisibility::Collapsed);
}

void UDigimonVenomNXTServerConsoleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!bPageOpen) return;
    PollElapsed += InDeltaTime;
    if (PollElapsed < DigimonServerUI::PollInterval) return;
    PollElapsed = 0.0f;
    if (!CheckAccess()) return;
    if (bLogFilterDirty) { bLogFilterDirty = false; RebuildLog(); }
    if (bHelpFilterDirty) { bHelpFilterDirty = false; RebuildHelp(); }
    PollEntries();
}

bool UDigimonVenomNXTServerConsoleWidget::EntryMatches(const FDigimonServerConsoleEntry& Entry) const
{
    if (!CategoryFilter.IsEmpty() && !Entry.Category.Equals(CategoryFilter, ESearchCase::IgnoreCase)) return false;
    if (!SeverityFilter.IsEmpty() && !Entry.Severity.Equals(SeverityFilter, ESearchCase::IgnoreCase)) return false;
    return DigimonServerUI::SearchMatches(Entry.Player + TEXT(" ") + Entry.Category + TEXT(" ") + Entry.Action + TEXT(" ") + Entry.Details + TEXT(" ") + Entry.Severity, LogSearch);
}

void UDigimonVenomNXTServerConsoleWidget::PollEntries()
{
    if (!bPageOpen || !CheckAccess()) return;
    UDigimonVenomNXTServerConsoleSubsystem* Server = Backend();
    FDigimonServerConsoleStatus ServerStatus;
    if (!Server->GetStatus(GetOwningPlayer(), ServerStatus)) { CheckAccess(); return; }
    OnlinePlayers = ServerStatus.OnlinePlayers; RetainedEntries = ServerStatus.RetainedEntries;
    PendingEntries = static_cast<int32>(FMath::Clamp<int64>(ServerStatus.LatestSequence - LastSequence, 0, MAX_int32));
    if (bPaused) { RefreshReadout(); return; }
    if (LastSequence > ServerStatus.LatestSequence)
    {
        Entries.Reset(); RenderedRows.Reset(); RenderedSequences.Reset(); LogRows->ClearChildren(); LastSequence = 0;
        StatusNotice = TEXT("New server session.");
    }
    if (LastSequence > 0 && ServerStatus.FirstSequence > LastSequence + 1)
    {
        StatusNotice = TEXT("Older activity rolled out of the server buffer while this view was paused.");
        LastSequence = ServerStatus.FirstSequence - 1;
    }
    TArray<FDigimonServerConsoleEntry> Added;
    if (!Server->ReadEntries(GetOwningPlayer(), LastSequence, DigimonServerUI::MaxCachedEntries, Added)) { CheckAccess(); return; }
    const int64 PreviousSequence = LastSequence;
    for (const FDigimonServerConsoleEntry& Entry : Added)
    {
        if (Entry.Sequence <= LastSequence) continue;
        LastSequence = Entry.Sequence; Entries.Add(Entry);
        if (!Entry.Category.IsEmpty() && CategoryPicker->FindOptionIndex(Entry.Category) == INDEX_NONE) CategoryPicker->AddOption(Entry.Category);
    }
    if (Entries.Num() > DigimonServerUI::MaxCachedEntries) Entries.RemoveAt(0, Entries.Num() - DigimonServerUI::MaxCachedEntries);
    // Rows may expire even when the newest entries do not match the current filter.
    float RemovedHeight = 0.0f;
    while (RenderedRows.Num() && Entries.Num() && RenderedSequences[0] < Entries[0].Sequence)
    {
        RemovedHeight += RenderedRows[0]->GetDesiredSize().Y + 2.0f; LogRows->RemoveChild(RenderedRows[0]);
        RenderedRows.RemoveAt(0); RenderedSequences.RemoveAt(0);
    }
    if (RemovedHeight > 0 && !bFollowLive)
    {
        bSynchronizingScroll = true; LogScroll->SetScrollOffset(FMath::Max(0.0f, LogScroll->GetScrollOffset() - RemovedHeight)); bSynchronizingScroll = false;
    }
    int32 FirstNew = Entries.Num(); int32 MatchingNew = 0;
    for (int32 Index = Entries.Num() - 1; Index >= 0 && Entries[Index].Sequence > PreviousSequence; --Index)
    {
        if (EntryMatches(Entries[Index])) { FirstNew = Index; if (++MatchingNew >= DigimonServerUI::MaxRenderedRows) break; }
    }
    for (int32 Index = FirstNew; Index < Entries.Num(); ++Index) if (EntryMatches(Entries[Index])) AppendLogRow(Entries[Index]);
    if (bFollowLive && Added.Num()) { bSynchronizingScroll = true; LogScroll->ScrollToEnd(); bSynchronizingScroll = false; }
    PendingEntries = static_cast<int32>(FMath::Clamp<int64>(ServerStatus.LatestSequence - LastSequence, 0, MAX_int32));
    RefreshReadout();
}

void UDigimonVenomNXTServerConsoleWidget::AppendLogRow(const FDigimonServerConsoleEntry& Entry)
{
    using namespace DigimonServerUI;
    UBorder* Line = WidgetTree->ConstructWidget<UBorder>();
    const FLinearColor Accent = SeverityColor(Entry.Severity);
    Line->SetBrush(FSlateRoundedBoxBrush(Entry.Sequence % 2 ? Panel : Ink, 3.0f)); Line->SetPadding(FMargin(7, 5));
    UHorizontalBox* Columns = WidgetTree->ConstructWidget<UHorizontalBox>(); Line->SetContent(Columns);
    UVerticalBox* Stamp = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Columns, Width(WidgetTree, Stamp, 64), false, 0);
    UTextBlock* Time = Text(WidgetTree, Entry.Timestamp.ToString(TEXT("%H:%M:%S")), 9, Muted);
    Time->SetToolTipText(FText::FromString(TEXT("Server event time in UTC.")));
    Time->SetFont(ConsoleFont(9)); Add(Stamp, Time, 0);
    Add(Stamp, Text(WidgetTree, FString::Printf(TEXT("#%lld"), static_cast<long long>(Entry.Sequence)), 8, Muted), 1);
    UVerticalBox* Message = WidgetTree->ConstructWidget<UVerticalBox>(); Row(Columns, Message, true, 4);
    const FString Actor = Entry.Player.IsEmpty() ? TEXT("Server") : Entry.Player;
    UTextBlock* Heading = Text(WidgetTree, FString::Printf(TEXT("[%s]  %s  |  %s  /  %s"), *Entry.Severity.ToUpper(), *Entry.Category, *Actor, *Entry.Action), 10, Accent, true);
    Add(Message, Heading, 0);
    if (!Entry.Details.IsEmpty())
    {
        UTextBlock* Details = Text(WidgetTree, Entry.Details, 10, White);
        Details->SetFont(ConsoleFont(10)); Add(Message, Details, 2);
    }
    Add(LogRows, Line, 1); RenderedRows.Add(Line); RenderedSequences.Add(Entry.Sequence);
    if (RenderedRows.Num() > MaxRenderedRows)
    {
        const float RemovedHeight = RenderedRows[0]->GetDesiredSize().Y + 2.0f;
        LogRows->RemoveChild(RenderedRows[0]); RenderedRows.RemoveAt(0); RenderedSequences.RemoveAt(0);
        if (!bFollowLive)
        {
            bSynchronizingScroll = true; LogScroll->SetScrollOffset(FMath::Max(0.0f, LogScroll->GetScrollOffset() - RemovedHeight)); bSynchronizingScroll = false;
        }
    }
}

void UDigimonVenomNXTServerConsoleWidget::RebuildLog()
{
    if (!LogRows || !CheckAccess()) return;
    const float OldOffset = LogScroll->GetScrollOffset();
    LogRows->ClearChildren(); RenderedRows.Reset(); RenderedSequences.Reset();
    int32 First = Entries.Num(); int32 Matching = 0;
    for (int32 Index = Entries.Num() - 1; Index >= 0; --Index)
    {
        if (EntryMatches(Entries[Index])) { First = Index; if (++Matching >= DigimonServerUI::MaxRenderedRows) break; }
    }
    for (int32 Index = First; Index < Entries.Num(); ++Index) if (EntryMatches(Entries[Index])) AppendLogRow(Entries[Index]);
    bSynchronizingScroll = true;
    if (bFollowLive) LogScroll->ScrollToEnd(); else LogScroll->SetScrollOffset(OldOffset);
    bSynchronizingScroll = false; RefreshReadout();
}

void UDigimonVenomNXTServerConsoleWidget::RefreshReadout()
{
    using namespace DigimonServerUI;
    Set(SessionReadout, FString::Printf(TEXT("%d online  |  %d server events retained  |  UTC"), OnlinePlayers, RetainedEntries));
    FString State = bPaused ? TEXT("PAUSED") : bFollowLive ? TEXT("LIVE") : TEXT("READING HISTORY");
    State += FString::Printf(TEXT("  |  %d shown / %d buffered"), RenderedRows.Num(), Entries.Num());
    if (PendingEntries > 0) State += FString::Printf(TEXT("  |  %d new"), PendingEntries);
    if (!StatusNotice.IsEmpty()) State += TEXT("\n") + StatusNotice;
    Set(ViewReadout, State); Set(PauseCaption, bPaused ? TEXT("RESUME VIEW") : TEXT("PAUSE VIEW"));
    Set(FollowCaption, bFollowLive && !bPaused ? TEXT("FOLLOWING LIVE") : TEXT("JUMP TO LATEST"));
    DigimonVenomNXTUI::StyleButton(PauseButton, Gold, bPaused); DigimonVenomNXTUI::StyleButton(FollowButton, Cyan, bFollowLive && !bPaused);
    if (EmptyMessage)
    {
        EmptyMessage->SetVisibility(RenderedRows.Num() ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
        Set(EmptyMessage, Entries.Num() ? TEXT("No activity matches these filters.\nTry a different category or clear your search.") : TEXT("Waiting for server activity...\nConnections, battles, rewards and host actions appear here."));
    }
}

void UDigimonVenomNXTServerConsoleWidget::RebuildHelp()
{
    if (!HelpRows || !CheckAccess()) return;
    using namespace DigimonServerUI;
    HelpRows->ClearChildren(); int32 Matched = 0;
    for (int32 Index = 0; Index < CommandHelp.Num(); ++Index)
    {
        const FDigimonServerCommandInfo& Command = CommandHelp[Index];
        if (!SearchMatches(Command.Name + TEXT(" ") + Command.Usage + TEXT(" ") + Command.Description, HelpSearch)) continue;
        ++Matched; UBorder* Entry = Card(WidgetTree, Command.bRequiresConfirmation ? Gold : Cyan, 10); Add(HelpRows, Entry, 4);
        UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); Entry->SetContent(Body);
        UHorizontalBox* Title = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, Title, 0);
        Row(Title, Text(WidgetTree, SlashName(Command.Name), 13, Cyan, true), true, 0);
        if (Command.bRequiresConfirmation) Row(Title, Text(WidgetTree, TEXT("CONFIRMATION REQUIRED"), 9, Gold, true), false, 6);
        UDigimonVenomNXTActionButton* Use = MakeButton(TEXT("FILL COMMAND"), TEXT("console:fill"), Cyan, Index);
        Use->SetToolTipText(FText::FromString(TEXT("Copy the command name into the input. Add its arguments and review before running."))); Row(Title, Use);
        Add(Body, Text(WidgetTree, Command.Usage, 11, White), 3);
        Add(Body, Text(WidgetTree, Command.Description, 10, Muted), 2);
        if (IsSensitiveCommand(SlashName(Command.Name))) Add(Body, Text(WidgetTree, TEXT("Credential command: input is hidden and excluded from history."), 9, Gold), 1);
    }
    Set(HelpReadout, FString::Printf(TEXT("%d of %d commands  |  <required>  [optional]  |  Quote names with spaces. Commands act only after you press Run."), Matched, CommandHelp.Num()));
    if (Matched == 0) Add(HelpRows, Text(WidgetTree, TEXT("No commands match your search. Try money, party, title or help."), 12, Muted), 14);
}

void UDigimonVenomNXTServerConsoleWidget::SelectPage(int32 PageIndex)
{
    ActivePage = FMath::Clamp(PageIndex, 0, 1); if (Pages) Pages->SetActiveWidgetIndex(ActivePage);
    for (int32 Index = 0; Index < PageButtons.Num(); ++Index) DigimonVenomNXTUI::StyleButton(PageButtons[Index], DigimonServerUI::Cyan, Index == ActivePage);
}

void UDigimonVenomNXTServerConsoleWidget::SetFeedback(const FString& Message, bool bSuccess)
{
    DigimonServerUI::Set(FeedbackText, Message);
    if (FeedbackText) FeedbackText->SetWidgetStyle(FTextBlockStyle().SetFont(DigimonServerUI::ConsoleFont(10)).SetColorAndOpacity(bSuccess ? DigimonServerUI::Green : DigimonServerUI::Gold));
}

void UDigimonVenomNXTServerConsoleWidget::FillCommand(const FString& Command)
{
    if (!CommandInput || !CheckAccess()) return;
    bUpdatingInput = true; CommandInput->SetText(FText::FromString(Command)); bUpdatingInput = false;
    bSensitiveDraft = DigimonServerUI::IsSensitiveCommand(Command); CommandInput->SetIsPassword(bSensitiveDraft);
    HistoryIndex = INDEX_NONE; DraftCommand.Reset(); ExecuteButton->SetIsEnabled(!Command.TrimStartAndEnd().IsEmpty());
    SelectPage(0); if (GetOwningPlayer()) CommandInput->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTServerConsoleWidget::SubmitCommand()
{
    if (!bPageOpen || bCredentialPromptOpen || !CommandInput || !CheckAccess()) return;
    FString Command = CommandInput->GetText().ToString().TrimStartAndEnd();
    if (Command.IsEmpty()) return;
    const bool bSensitive = bSensitiveDraft || DigimonServerUI::IsSensitiveCommand(Command);
    // Clear before executing, so sensitive arguments never remain visible after a rejected command.
    bUpdatingInput = true; CommandInput->SetText(FText::GetEmpty()); CommandInput->SetIsPassword(false); bUpdatingInput = false;
    ExecuteButton->SetIsEnabled(false); HistoryIndex = INDEX_NONE; DraftCommand.Reset(); bSensitiveDraft = false;
    if (Command.Len() > DigimonServerUI::MaxCommandLength)
    {
        SetFeedback(TEXT("That command is too long. Use at most 1,024 characters."), false); return;
    }
    if (!Command.StartsWith(TEXT("/")))
    {
        SetFeedback(TEXT("Server commands start with /. Type /help or open Command Guide."), false); return;
    }
    std::vector<std::string> Arguments; std::string ParseError;
    if (!DigimonVenomNXTServerConsoleCore::Tokenize(TCHAR_TO_UTF8(*Command), Arguments, ParseError))
    {
        SetFeedback(UTF8_TO_TCHAR(ParseError.c_str()), false); return;
    }
    const FString Verb = FString(UTF8_TO_TCHAR(Arguments[0].c_str())).ToLower();
    if (DigimonServerUI::IsSensitiveCommand(Verb))
    {
        if (Arguments.size() != 2 || Arguments[1].empty())
        {
            SetFeedback(TEXT("For account actions, enter only /createaccount <username> or /resetpassword <username>. Enter the password in the separate masked dialog."), false); return;
        }
        OpenCredentialPrompt(Verb, UTF8_TO_TCHAR(Arguments[1].c_str())); return;
    }
    const bool bKnownCommand = CommandHelp.ContainsByPredicate([&Verb](const FDigimonServerCommandInfo& Item) { return DigimonServerUI::SlashName(Item.Name).Equals(Verb, ESearchCase::IgnoreCase); });
    if (!bSensitive && bKnownCommand && Verb != TEXT("/confirm"))
    {
        if (!CommandHistory.Num() || CommandHistory.Last() != Command) CommandHistory.Add(Command);
        if (CommandHistory.Num() > DigimonServerUI::MaxHistoryEntries) CommandHistory.RemoveAt(0);
    }
    FString Response;
    const bool bSuccess = Backend()->ExecuteCommand(GetOwningPlayer(), Command, Response);
    if (!CheckAccess()) return;
    SetFeedback(Response.IsEmpty() ? (bSuccess ? TEXT("Command completed.") : TEXT("Command could not be completed. Type /help for usage.")) : Response, bSuccess);
    DigimonServerUI::Set(InputHint, TEXT("Enter to run  |  Up / Down: history  |  Tab: complete command  |  /help: command guide"));
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, bSuccess ? EDigimonAudioCue::Confirm : EDigimonAudioCue::Error);
    SelectPage(0); PollEntries();
    if (GetOwningPlayer()) CommandInput->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTServerConsoleWidget::OpenCredentialPrompt(const FString& Verb, const FString& Username)
{
    if (!bPageOpen || !CheckAccess() || !CredentialOverlay) return;
    CredentialVerb = Verb; CredentialUsername = Username; bCredentialPromptOpen = true;
    CredentialPassword->SetText(FText::GetEmpty()); CredentialConfirmation->SetText(FText::GetEmpty());
    DigimonServerUI::Set(CredentialTitle, Verb == TEXT("/createaccount") ? TEXT("CREATE PLAYER ACCOUNT") : TEXT("RESET ACCOUNT PASSWORD"));
    DigimonServerUI::Set(CredentialAccount, TEXT("ACCOUNT: ") + Username);
    DigimonServerUI::Set(CredentialFeedback, TEXT("Use 8–128 characters. Both password fields must match."));
    Content->SetIsEnabled(false); CredentialOverlay->SetVisibility(ESlateVisibility::Visible);
    if (GetOwningPlayer()) CredentialPassword->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTServerConsoleWidget::CloseCredentialPrompt()
{
    bCredentialPromptOpen = false; CredentialVerb.Reset(); CredentialUsername.Reset();
    if (CredentialPassword) CredentialPassword->SetText(FText::GetEmpty());
    if (CredentialConfirmation) CredentialConfirmation->SetText(FText::GetEmpty());
    if (CredentialOverlay) CredentialOverlay->SetVisibility(ESlateVisibility::Collapsed);
    DigimonServerUI::Set(CredentialAccount, FString()); DigimonServerUI::Set(CredentialFeedback, FString());
    UDigimonVenomNXTServerConsoleSubsystem* Server = Backend();
    const bool bAllowed = bPageOpen && Server && Server->CanAccess(GetOwningPlayer());
    if (Content) Content->SetIsEnabled(bAllowed);
    if (bAllowed && CommandInput && GetOwningPlayer()) CommandInput->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTServerConsoleWidget::SubmitCredentialPrompt()
{
    if (!bPageOpen || !bCredentialPromptOpen || !CheckAccess()) return;
    FString Password = CredentialPassword->GetText().ToString();
    if (Password.Len() < 8 || Password.Len() > 128)
    {
        DigimonServerUI::Set(CredentialFeedback, TEXT("Choose a password between 8 and 128 characters.")); return;
    }
    if (Password != CredentialConfirmation->GetText().ToString())
    {
        CredentialConfirmation->SetText(FText::GetEmpty());
        DigimonServerUI::Set(CredentialFeedback, TEXT("Passwords did not match. Re-enter the confirmation."));
        if (GetOwningPlayer()) CredentialConfirmation->SetUserFocus(GetOwningPlayer()); return;
    }
    CredentialPassword->SetText(FText::GetEmpty()); CredentialConfirmation->SetText(FText::GetEmpty());
    FString Response;
    const bool bSuccess = Backend()->ExecuteSensitiveCommand(GetOwningPlayer(), CredentialVerb, CredentialUsername, Password, Response);
    Password.Reset();
    if (!CheckAccess()) return;
    if (bSuccess)
    {
        CloseCredentialPrompt(); SetFeedback(Response, true); PollEntries();
        UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Confirm);
    }
    else
    {
        DigimonServerUI::Set(CredentialFeedback, Response);
        UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Error);
        if (GetOwningPlayer()) CredentialPassword->SetUserFocus(GetOwningPlayer());
    }
}

void UDigimonVenomNXTServerConsoleWidget::HandleCredentialCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    if (CommitType == ETextCommit::OnEnter) SubmitCredentialPrompt();
}

void UDigimonVenomNXTServerConsoleWidget::HandleAction(const FString& Action, int32 Payload)
{
    if (!bPageOpen || !CheckAccess()) return;
    if (Action == TEXT("console:credentialcancel")) { CloseCredentialPrompt(); SetFeedback(TEXT("Account action cancelled. No changes were made."), true); return; }
    if (Action == TEXT("console:credentialsave")) { SubmitCredentialPrompt(); return; }
    if (bCredentialPromptOpen) return;
    if (Action == TEXT("console:close")) { if (!HandleBack()) OnAction.Broadcast(Action, Payload); }
    else if (Action == TEXT("console:page")) SelectPage(Payload);
    else if (Action == TEXT("console:run")) SubmitCommand();
    else if (Action == TEXT("console:players")) { FillCommand(TEXT("/players")); SubmitCommand(); }
    else if (Action == TEXT("console:fill") && CommandHelp.IsValidIndex(Payload))
    {
        const FDigimonServerCommandInfo& Command = CommandHelp[Payload];
        FillCommand(DigimonServerUI::SlashName(Command.Name) + TEXT(" "));
        SetFeedback(Command.Usage + TEXT("\n") + Command.Description, true);
    }
    else if (Action == TEXT("console:pause")) { bPaused = !bPaused; PollEntries(); }
    else if (Action == TEXT("console:latest"))
    {
        bPaused = false; bFollowLive = true; PollEntries(); bSynchronizingScroll = true; LogScroll->ScrollToEnd(); bSynchronizingScroll = false; RefreshReadout();
    }
    else if (Action == TEXT("console:clear"))
    {
        Entries.Reset(); RenderedRows.Reset(); RenderedSequences.Reset(); LogRows->ClearChildren(); StatusNotice = TEXT("View cleared; the server log is preserved."); RefreshReadout();
    }
}

void UDigimonVenomNXTServerConsoleWidget::HandleCategoryChanged(FString Selection, ESelectInfo::Type SelectionType)
{
    if (SelectionType == ESelectInfo::Direct || !bPageOpen || !CheckAccess()) return;
    CategoryFilter = Selection == TEXT("All activity") ? FString() : Selection; bLogFilterDirty = true;
}

void UDigimonVenomNXTServerConsoleWidget::HandleSeverityChanged(FString Selection, ESelectInfo::Type SelectionType)
{
    if (SelectionType == ESelectInfo::Direct || !bPageOpen || !CheckAccess()) return;
    SeverityFilter = Selection == TEXT("All levels") ? FString() : Selection; bLogFilterDirty = true;
}

void UDigimonVenomNXTServerConsoleWidget::HandleLogSearchChanged(const FText& Text)
{
    if (!bPageOpen) return; LogSearch = Text.ToString().Left(256); bLogFilterDirty = true;
}

void UDigimonVenomNXTServerConsoleWidget::HandleHelpSearchChanged(const FText& Text)
{
    if (!bPageOpen) return; HelpSearch = Text.ToString().Left(256); bHelpFilterDirty = true;
}

void UDigimonVenomNXTServerConsoleWidget::HandleCommandChanged(const FText& Text)
{
    if (bUpdatingInput || !bPageOpen || !CheckAccess()) return;
    FString Command = Text.ToString();
    if (Command.Len() > DigimonServerUI::MaxCommandLength)
    {
        Command.LeftInline(DigimonServerUI::MaxCommandLength); bUpdatingInput = true; CommandInput->SetText(FText::FromString(Command)); bUpdatingInput = false;
        SetFeedback(TEXT("Command input is limited to 1,024 characters."), false);
    }
    bSensitiveDraft = !Command.IsEmpty() && (bSensitiveDraft || DigimonServerUI::IsSensitiveCommand(Command));
    CommandInput->SetIsPassword(bSensitiveDraft); ExecuteButton->SetIsEnabled(!Command.TrimStartAndEnd().IsEmpty());
    DigimonServerUI::Set(InputHint, bSensitiveDraft ? TEXT("ACCOUNT ACTION: enter the username only. Run opens a separate masked password dialog.") : TEXT("Enter to run  |  Up / Down: history  |  Tab: complete command  |  /help: command guide"));
    HistoryIndex = INDEX_NONE; DraftCommand.Reset();
}

void UDigimonVenomNXTServerConsoleWidget::HandleCommandCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    if (CommitType == ETextCommit::OnEnter) SubmitCommand();
}

void UDigimonVenomNXTServerConsoleWidget::HandleUserScrolled(float Offset)
{
    if (!bPageOpen || bSynchronizingScroll || !LogScroll) return;
    bFollowLive = Offset >= LogScroll->GetScrollOffsetOfEnd() - 20.0f; RefreshReadout();
}

bool UDigimonVenomNXTServerConsoleWidget::CommandHasFocus() const
{
    return CommandInput && (CommandInput->HasKeyboardFocus() || CommandInput->HasFocusedDescendants());
}

void UDigimonVenomNXTServerConsoleWidget::NavigateHistory(int32 Direction)
{
    if (!CheckAccess() || !CommandInput || !CommandHistory.Num()) return;
    if (bSensitiveDraft || DigimonServerUI::IsSensitiveCommand(CommandInput->GetText().ToString()))
    {
        SetFeedback(TEXT("Clear the credential command before using history."), false); return;
    }
    if (HistoryIndex == INDEX_NONE)
    {
        if (Direction > 0) return;
        DraftCommand = CommandInput->GetText().ToString(); HistoryIndex = CommandHistory.Num();
    }
    HistoryIndex = FMath::Clamp(HistoryIndex + Direction, 0, CommandHistory.Num());
    const FString Value = HistoryIndex == CommandHistory.Num() ? DraftCommand : CommandHistory[HistoryIndex];
    bUpdatingInput = true; CommandInput->SetText(FText::FromString(Value)); bUpdatingInput = false;
    ExecuteButton->SetIsEnabled(!Value.TrimStartAndEnd().IsEmpty());
}

void UDigimonVenomNXTServerConsoleWidget::CompleteCommand()
{
    if (!CheckAccess() || !CommandInput) return;
    FString Prefix = CommandInput->GetText().ToString().TrimStart();
    if (Prefix.Contains(TEXT(" ")) || Prefix.Contains(TEXT("\t")))
    {
        SetFeedback(TEXT("Tab completes the command name. Open Command Guide for argument syntax."), true); return;
    }
    if (Prefix.IsEmpty()) Prefix = TEXT("/");
    TArray<FString> Matches;
    for (const FDigimonServerCommandInfo& Command : CommandHelp)
    {
        const FString Name = DigimonServerUI::SlashName(Command.Name);
        if (Name.StartsWith(Prefix, ESearchCase::IgnoreCase)) Matches.AddUnique(Name);
    }
    if (Matches.Num() == 1) { FillCommand(Matches[0] + TEXT(" ")); return; }
    if (Matches.IsEmpty()) { SetFeedback(TEXT("No command matches that name. Type /help or open Command Guide."), false); return; }
    FString Common = Matches[0];
    for (int32 Index = 1; Index < Matches.Num(); ++Index)
        while (!Common.IsEmpty() && !Matches[Index].StartsWith(Common, ESearchCase::IgnoreCase)) Common.LeftChopInline(1);
    if (Common.Len() > Prefix.Len()) FillCommand(Common);
    FString Suggestions;
    for (int32 Index = 0; Index < FMath::Min(Matches.Num(), 8); ++Index) Suggestions += (Index ? TEXT("  ") : TEXT("")) + Matches[Index];
    if (Matches.Num() > 8) Suggestions += FString::Printf(TEXT("  (+%d more in Command Guide)"), Matches.Num() - 8);
    SetFeedback(TEXT("Matching commands: ") + Suggestions, true);
}

FReply UDigimonVenomNXTServerConsoleWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (bPageOpen && CheckAccess() && bCredentialPromptOpen && InKeyEvent.GetKey() == EKeys::Escape)
    {
        HandleBack(); return FReply::Handled();
    }
    if (bPageOpen && CheckAccess() && CommandHasFocus())
    {
        if (InKeyEvent.GetKey() == EKeys::Up) { NavigateHistory(-1); return FReply::Handled(); }
        if (InKeyEvent.GetKey() == EKeys::Down) { NavigateHistory(1); return FReply::Handled(); }
        if (InKeyEvent.GetKey() == EKeys::Tab && !InKeyEvent.IsShiftDown() && !InKeyEvent.IsControlDown() && !InKeyEvent.IsAltDown()) { CompleteCommand(); return FReply::Handled(); }
    }
    return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

FReply UDigimonVenomNXTServerConsoleWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (bPageOpen && CheckAccess() && InKeyEvent.GetKey() == EKeys::Escape)
    {
        if (!HandleBack()) OnAction.Broadcast(TEXT("console:close"), 0); return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
