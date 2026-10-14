#include "DigimonVenomNXTWorldChatWidget.h"
#include "DigimonVenomNXTWorldChatCore.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTFieldPartyWidget.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTUIComponents.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "CoreGlobals.h"
#include "HAL/PlatformTime.h"
#include "InputCoreTypes.h"

namespace DigimonWorldChatUI
{
    constexpr int32 HistoryLimit = DigimonVenomNXTWorldChatCore::HistoryLimit;
    const FLinearColor Accent(0.08f, 0.88f, 0.94f, 1.0f);
    const FLinearColor Ink(0.92f, 0.96f, 1.0f, 1.0f);
    const FLinearColor Muted(0.57f, 0.70f, 0.79f, 1.0f);
    const FLinearColor Joined(0.42f, 0.91f, 0.64f, 1.0f);
    const FLinearColor Left(1.0f, 0.72f, 0.36f, 1.0f);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size, FLinearColor Color, bool bBold = false)
    {
        UTextBlock* Out = Tree->ConstructWidget<UTextBlock>();
        Out->SetText(FText::FromString(Value));
        Out->SetColorAndOpacity(FSlateColor(Color));
        Out->SetAutoWrapText(true);
        Out->SetVisibility(ESlateVisibility::HitTestInvisible);
        FSlateFontInfo Font = Out->GetFont();
        Font.Size = Size;
        Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular"));
        Out->SetFont(Font);
        return Out;
    }

    void SmallButton(UButton* Button)
    {
        DigimonVenomNXTUI::StyleButton(Button, Accent);
        FButtonStyle Style = Button->GetStyle();
        Style.SetNormalPadding(FMargin(10, 6));
        Style.SetPressedPadding(FMargin(10, 7, 10, 5));
        Button->SetStyle(Style);
    }
}

void UDigimonVenomNXTWorldChatWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    BuildNativeUI();
}

void UDigimonVenomNXTWorldChatWidget::NativeDestruct()
{
    ReleaseComposer();
    Super::NativeDestruct();
}

void UDigimonVenomNXTWorldChatWidget::BuildNativeUI()
{
    if (bBuilt || !WidgetTree) return;
    bBuilt = true;
    using namespace DigimonWorldChatUI;
    SetVisibility(ESlateVisibility::SelfHitTestInvisible);

    UBorder* Panel = WidgetTree->ConstructWidget<UBorder>();
    DigimonVenomNXTUI::StylePanel(Panel, FLinearColor(0.006f, 0.019f, 0.035f, 0.94f));
    Panel->SetPadding(FMargin(12, 9));
    WidgetTree->RootWidget = Panel;
    UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>();
    Panel->SetContent(Body);

    UHorizontalBox* Header = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* LayoutSlot = Body->AddChildToVerticalBox(Header)) LayoutSlot->SetPadding(FMargin(0, 0, 0, 6));
    Header->AddChildToHorizontalBox(Text(WidgetTree, TEXT("WORLD"), 13, Accent, true));
    UTextBlock* Scope = Text(WidgetTree, TEXT("ALL HABITATS"), 10, Muted, true);
    Scope->SetVisibility(ESlateVisibility::Visible);
    Scope->SetToolTipText(FText::FromString(TEXT("One shared channel for everyone connected to this game server, across every habitat.")));
    if (UHorizontalBoxSlot* LayoutSlot = Header->AddChildToHorizontalBox(Scope))
    {
        LayoutSlot->SetPadding(FMargin(10, 0, 8, 0));
        LayoutSlot->SetVerticalAlignment(VAlign_Center);
        LayoutSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
    UnreadButton = WidgetTree->ConstructWidget<UDigimonVenomNXTFieldActionButton>();
    SmallButton(UnreadButton);
    UnreadLabel = Text(WidgetTree, TEXT(""), 10, Accent, true);
    UnreadButton->AddChild(UnreadLabel);
    UnreadButton->SetToolTipText(FText::FromString(TEXT("Jump to the newest world messages.")));
    UnreadButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTWorldChatWidget::HandleUnread);
    Header->AddChildToHorizontalBox(UnreadButton);

    HistorySize = WidgetTree->ConstructWidget<USizeBox>();
    Body->AddChildToVerticalBox(HistorySize);
    HistoryScroll = WidgetTree->ConstructWidget<UScrollBox>();
    HistoryScroll->SetScrollbarThickness(FVector2D(4, 4));
    HistoryScroll->SetConsumeMouseWheel(EConsumeMouseWheel::Always);
    HistoryScroll->SetAnimateWheelScrolling(false);
    HistoryScroll->SetAllowOverscroll(false);
    HistoryScroll->SetClipping(EWidgetClipping::ClipToBounds);
    HistoryScroll->OnUserScrolled.AddDynamic(this, &UDigimonVenomNXTWorldChatWidget::HandleScrolled);
    HistorySize->AddChild(HistoryScroll);
    MessageRows = WidgetTree->ConstructWidget<UVerticalBox>();
    HistoryScroll->AddChild(MessageRows);
    EmptyLabel = Text(WidgetTree, TEXT("Welcome to WORLD. Say hello to tamers across every habitat."), 13, Muted);
    MessageRows->AddChildToVerticalBox(EmptyLabel);

    UHorizontalBox* Composer = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* LayoutSlot = Body->AddChildToVerticalBox(Composer)) LayoutSlot->SetPadding(FMargin(0, 7, 0, 0));
    MessageInput = WidgetTree->ConstructWidget<UEditableTextBox>();
    DigimonVenomNXTUI::StyleInput(MessageInput);
    FEditableTextBoxStyle InputStyle = MessageInput->GetWidgetStyle();
    InputStyle.SetPadding(FMargin(9, 7));
    InputStyle.TextStyle.Font.Size = 13;
    MessageInput->SetWidgetStyle(InputStyle);
    MessageInput->SetHintText(FText::FromString(TEXT("Message all tamers...")));
    MessageInput->SetClearKeyboardFocusOnCommit(false);
    MessageInput->SetSelectAllTextWhenFocused(false);
    MessageInput->SetSelectAllTextOnCommit(false);
    MessageInput->OnTextChanged.AddDynamic(this, &UDigimonVenomNXTWorldChatWidget::HandleTextChanged);
    MessageInput->OnTextCommitted.AddDynamic(this, &UDigimonVenomNXTWorldChatWidget::HandleTextCommitted);
    if (UHorizontalBoxSlot* LayoutSlot = Composer->AddChildToHorizontalBox(MessageInput))
    {
        LayoutSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        LayoutSlot->SetPadding(FMargin(0, 0, 6, 0));
    }
    SendButton = WidgetTree->ConstructWidget<UDigimonVenomNXTFieldActionButton>();
    SmallButton(SendButton);
    SendLabel = Text(WidgetTree, TEXT("SEND"), 11, Ink, true);
    SendButton->AddChild(SendLabel);
    SendButton->SetToolTipText(FText::FromString(TEXT("Send to WORLD. You can send one message each second.")));
    SendButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTWorldChatWidget::HandleSend);
    Composer->AddChildToHorizontalBox(SendButton);

    UHorizontalBox* Footer = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* LayoutSlot = Body->AddChildToVerticalBox(Footer)) LayoutSlot->SetPadding(FMargin(0, 5, 0, 0));
    Help = Text(WidgetTree, TEXT(""), 10, Muted);
    if (UHorizontalBoxSlot* LayoutSlot = Footer->AddChildToHorizontalBox(Help)) LayoutSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    Counter = Text(WidgetTree, TEXT(""), 10, Muted);
    Footer->AddChildToHorizontalBox(Counter);
    SetFieldPresentation(bFieldPresentation);
    RefreshComposer();
    RefreshUnread();
}

void UDigimonVenomNXTWorldChatWidget::SetFieldPresentation(bool bField)
{
    bFieldPresentation = bField;
    if (HistorySize) HistorySize->SetHeightOverride(bField ? 138.0f : 74.0f);
    if (Help) Help->SetText(FText::FromString(bField ? TEXT("Enter  Chat / Send     Esc  Return to game") : TEXT("Enter  Send     Esc  Leave chat")));
}

void UDigimonVenomNXTWorldChatWidget::SetHistory(const TArray<FDigimonChatMessage>& History)
{
    BuildNativeUI();
    if (!MessageRows) return;
    MessageRows->ClearChildren();
    if (History.IsEmpty()) MessageRows->AddChildToVerticalBox(EmptyLabel);
    bFollowTail = true;
    UnreadCount = 0;
    for (int32 Index = FMath::Max(0, History.Num() - DigimonWorldChatUI::HistoryLimit); Index < History.Num(); ++Index)
        AppendMessage(History[Index]);
    RefreshUnread();
}

void UDigimonVenomNXTWorldChatWidget::AppendMessage(const FDigimonChatMessage& Message)
{
    BuildNativeUI();
    if (!MessageRows || !HistoryScroll) return;
    using namespace DigimonWorldChatUI;
    if (EmptyLabel && EmptyLabel->GetParent() == MessageRows) MessageRows->RemoveChild(EmptyLabel);

    // Plain text deliberately prevents user-supplied markup from changing identity/system styling.
    const bool bSystem = Message.Kind != EDigimonChatMessageKind::Player;
    const FLinearColor Color = Message.Kind == EDigimonChatMessageKind::PlayerJoined ? Joined
        : Message.Kind == EDigimonChatMessageKind::PlayerLeft ? Left : Ink;
    const FString Body = bSystem ? Message.Message : FString::Printf(TEXT("%s: %s"), *Message.Sender, *Message.Message);
    UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>();
    UTextBlock* Stamp = Text(WidgetTree, Message.UnixTime > 0 ? FDateTime::FromUnixTimestamp(Message.UnixTime).ToString(TEXT("%H:%M")) : TEXT(""), 10, Muted);
    Stamp->SetAutoWrapText(false);
    Stamp->SetVisibility(ESlateVisibility::Visible);
    Stamp->SetToolTipText(FText::FromString(TEXT("Server time (UTC).")));
    if (UHorizontalBoxSlot* LayoutSlot = Row->AddChildToHorizontalBox(Stamp))
    {
        LayoutSlot->SetVerticalAlignment(VAlign_Top);
        LayoutSlot->SetPadding(FMargin(0, 2, 7, 0));
    }
    UTextBlock* Line = Text(WidgetTree, Body, 13, Color);
    Line->SetWrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping);
    if (UHorizontalBoxSlot* LayoutSlot = Row->AddChildToHorizontalBox(Line)) LayoutSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    if (UVerticalBoxSlot* LayoutSlot = MessageRows->AddChildToVerticalBox(Row)) LayoutSlot->SetPadding(FMargin(0, 2));

    // Retain the reader's position when old rows expire instead of jumping to the newest line.
    float RemovedHeight = 0.0f;
    while (MessageRows->GetChildrenCount() > HistoryLimit)
    {
        RemovedHeight += MessageRows->GetChildAt(0)->GetDesiredSize().Y + 4.0f;
        MessageRows->RemoveChildAt(0);
    }
    if (bFollowTail) { bPendingTail = true; HistoryScroll->ScrollToEnd(); }
    else
    {
        if (RemovedHeight > 0.0f) HistoryScroll->SetScrollOffset(FMath::Max(0.0f, HistoryScroll->GetScrollOffset() - RemovedHeight));
        ++UnreadCount;
    }
    RefreshUnread();
}

void UDigimonVenomNXTWorldChatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (bPendingTail && HistoryScroll)
    {
        // ScrollToEnd executes after layout; repeating on the next visible tick also handles a
        // hidden menu receiving wrapped messages before being opened.
        HistoryScroll->ScrollToEnd();
        bPendingTail = false;
    }
    const bool bFocused = MessageInput && (MessageInput->HasKeyboardFocus() || MessageInput->HasUserFocus(GetOwningPlayer()));
    if (bWasFocused && !bFocused) LastFocusReleaseFrame = GFrameCounter;
    bWasFocused = bFocused;
    if (CanSend() != bLastCanSend) RefreshComposer();
}

bool UDigimonVenomNXTWorldChatWidget::IsComposing() const
{
    return (MessageInput && (MessageInput->HasKeyboardFocus() || MessageInput->HasUserFocus(GetOwningPlayer())))
        || LastFocusReleaseFrame == GFrameCounter;
}

void UDigimonVenomNXTWorldChatWidget::FocusComposer()
{
    if (!MessageInput || !GetIsEnabled()) return;
    MessageInput->SetKeyboardFocus();
    MessageInput->SetUserFocus(GetOwningPlayer());
    bWasFocused = true;
}

void UDigimonVenomNXTWorldChatWidget::ReleaseComposer()
{
    if (!MessageInput || !(MessageInput->HasKeyboardFocus() || MessageInput->HasUserFocus(GetOwningPlayer()))) return;
    LastFocusReleaseFrame = GFrameCounter;
    bWasFocused = false;
    UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void UDigimonVenomNXTWorldChatWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
    LastFocusReleaseFrame = GFrameCounter;
    bWasFocused = false;
    Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

FReply UDigimonVenomNXTWorldChatWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Escape && IsComposing())
    {
        ReleaseComposer(); // Preserve an unfinished message when the player returns to exploration.
        return FReply::Handled();
    }
    return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

int32 UDigimonVenomNXTWorldChatWidget::GetCharacterLimit() const
{
    return FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxChatCharacters, 1, 512);
}

FString UDigimonVenomNXTWorldChatWidget::GetDraft() const
{
    return MessageInput ? MessageInput->GetText().ToString() : FString();
}

void UDigimonVenomNXTWorldChatWidget::SetDraft(const FString& Draft)
{
    if (MessageInput) MessageInput->SetText(FText::FromString(Draft.Left(GetCharacterLimit())));
}

void UDigimonVenomNXTWorldChatWidget::TakeComposerStateFrom(const UDigimonVenomNXTWorldChatWidget* Other)
{
    if (!Other || Other == this) return;
    LastSendTime = FMath::Max(LastSendTime, Other->LastSendTime);
    SetDraft(Other->GetDraft());
}

bool UDigimonVenomNXTWorldChatWidget::CanSend() const
{
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const ADigimonVenomNXTPlayerState* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    return PC && PS && PC->IsAccountAuthenticated() && !PC->IsLogoutPending() && !PC->CurrentBattle && !PS->Profile.Username.IsEmpty()
        && !GetDraft().TrimStartAndEnd().IsEmpty() && DigimonVenomNXTWorldChatCore::CanSend(FPlatformTime::Seconds(), LastSendTime);
}

void UDigimonVenomNXTWorldChatWidget::RefreshComposer()
{
    if (!MessageInput || !SendButton || !Counter) return;
    const int32 Length = GetDraft().Len();
    Counter->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Length, GetCharacterLimit())));
    Counter->SetColorAndOpacity(FSlateColor(Length >= GetCharacterLimit() ? DigimonWorldChatUI::Left : DigimonWorldChatUI::Muted));
    bLastCanSend = CanSend();
    SendButton->SetIsEnabled(bLastCanSend);
    if (SendLabel) SendLabel->SetColorAndOpacity(FSlateColor(bLastCanSend ? DigimonWorldChatUI::Ink : DigimonWorldChatUI::Muted));
}

void UDigimonVenomNXTWorldChatWidget::HandleTextChanged(const FText& Text)
{
    if (bChangingText || !MessageInput) return;
    FString Clean = Text.ToString();
    Clean.ReplaceInline(TEXT("\r"), TEXT(" "));
    Clean.ReplaceInline(TEXT("\n"), TEXT(" "));
    Clean.ReplaceInline(TEXT("\t"), TEXT(" "));
    Clean = Clean.Left(GetCharacterLimit());
    // Windows TCHAR is UTF-16: a length limit must not leave half of an emoji in the editor.
    if (!Clean.IsEmpty() && static_cast<uint32>(Clean[Clean.Len() - 1]) >= 0xd800 && static_cast<uint32>(Clean[Clean.Len() - 1]) <= 0xdbff)
        Clean.LeftChopInline(1);
    if (Clean != Text.ToString())
    {
        bChangingText = true;
        MessageInput->SetText(FText::FromString(Clean));
        bChangingText = false;
    }
    RefreshComposer();
}

void UDigimonVenomNXTWorldChatWidget::HandleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    if (CommitMethod != ETextCommit::OnEnter) return;
    if (GetDraft().TrimStartAndEnd().IsEmpty()) { ReleaseComposer(); return; }
    HandleSend();
}

void UDigimonVenomNXTWorldChatWidget::HandleSend()
{
    if (!CanSend()) return;
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const FString Message = GetDraft().TrimStartAndEnd();
    LastSendTime = FPlatformTime::Seconds();
    PC->ServerSendLocalChat(Message);
    MessageInput->SetText(FText::GetEmpty());
    HandleUnread();
    if (bFieldPresentation) ReleaseComposer();
    else FocusComposer();
    RefreshComposer();
}

void UDigimonVenomNXTWorldChatWidget::HandleScrolled(float Offset)
{
    if (!HistoryScroll) return;
    bFollowTail = Offset >= HistoryScroll->GetScrollOffsetOfEnd() - 8.0f;
    if (!bFollowTail) bPendingTail = false;
    else UnreadCount = 0;
    RefreshUnread();
}

void UDigimonVenomNXTWorldChatWidget::HandleUnread()
{
    bFollowTail = true;
    bPendingTail = true;
    UnreadCount = 0;
    if (HistoryScroll) HistoryScroll->ScrollToEnd();
    RefreshUnread();
}

void UDigimonVenomNXTWorldChatWidget::RefreshUnread()
{
    if (!UnreadButton || !UnreadLabel) return;
    UnreadLabel->SetText(FText::FromString(FString::Printf(TEXT("%d NEW  ↓"), UnreadCount)));
    UnreadButton->SetVisibility(UnreadCount > 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
