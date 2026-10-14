#include "DigimonVenomNXTProfileSyncWidget.h"
#include "DigimonVenomNXTPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UDigimonVenomNXTProfileSyncWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    // Establish the widget tree before Slate is first built, not after Construct.
    BuildNativeUI();
}

void UDigimonVenomNXTProfileSyncWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BuildNativeUI();
}

void UDigimonVenomNXTProfileSyncWidget::BuildNativeUI()
{
    if (StatusText) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this);
    UBorder* Backdrop = WidgetTree->ConstructWidget<UBorder>();
    Backdrop->SetBrushColor(FLinearColor(0.008f, 0.02f, 0.04f, 0.98f));
    Backdrop->SetHorizontalAlignment(HAlign_Center);
    Backdrop->SetVerticalAlignment(VAlign_Center);
    Backdrop->SetPadding(FMargin(24.0f));
    WidgetTree->RootWidget = Backdrop;
    USizeBox* Frame = WidgetTree->ConstructWidget<USizeBox>();
    Frame->SetMaxDesiredWidth(640.0f);
    Backdrop->SetContent(Frame);
    UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>();
    Frame->AddChild(Body);
    UTextBlock* Heading = WidgetTree->ConstructWidget<UTextBlock>();
    Heading->SetText(FText::FromString(TEXT("LOADING YOUR ACCOUNT")));
    Heading->SetJustification(ETextJustify::Center);
    Heading->SetAutoWrapText(true);
    FSlateFontInfo HeadingFont = Heading->GetFont(); HeadingFont.Size = 26; Heading->SetFont(HeadingFont);
    Body->AddChildToVerticalBox(Heading)->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 20.0f));
    StatusText = WidgetTree->ConstructWidget<UTextBlock>();
    StatusText->SetAutoWrapText(true);
    StatusText->SetJustification(ETextJustify::Center);
    Body->AddChildToVerticalBox(StatusText)->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 16.0f));
    UTextBlock* Hint = WidgetTree->ConstructWidget<UTextBlock>();
    Hint->SetText(FText::FromString(TEXT("Your team and progress are not replaced while loading. Gameplay opens only after the complete account is verified.")));
    Hint->SetAutoWrapText(true);
    Hint->SetJustification(ETextJustify::Center);
    Body->AddChildToVerticalBox(Hint)->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 24.0f));
    RetryButton = WidgetTree->ConstructWidget<UButton>();
    UTextBlock* RetryLabel = WidgetTree->ConstructWidget<UTextBlock>();
    RetryLabel->SetText(FText::FromString(TEXT("RETRY ACCOUNT SYNC")));
    RetryButton->AddChild(RetryLabel);
    Body->AddChildToVerticalBox(RetryButton)->SetPadding(FMargin(0.0f, 6.0f));
    RetryButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTProfileSyncWidget::HandleRetry);
    LeaveButton = WidgetTree->ConstructWidget<UButton>();
    UTextBlock* LeaveLabel = WidgetTree->ConstructWidget<UTextBlock>();
    LeaveLabel->SetText(FText::FromString(TEXT("RETURN TO LOGIN")));
    LeaveButton->AddChild(LeaveLabel);
    Body->AddChildToVerticalBox(LeaveButton)->SetPadding(FMargin(0.0f, 6.0f));
    LeaveButton->OnClicked.AddDynamic(this, &UDigimonVenomNXTProfileSyncWidget::HandleLeave);
    SetStatus(TEXT("Waiting for the server's verified account snapshot..."), false);
}

void UDigimonVenomNXTProfileSyncWidget::SetStatus(const FString& Message, bool bCanRetry)
{
    if (StatusText) StatusText->SetText(FText::FromString(Message));
    if (RetryButton) RetryButton->SetIsEnabled(bCanRetry);
}
void UDigimonVenomNXTProfileSyncWidget::HandleRetry()
{
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
        Controller->RetryProfileSynchronization();
}
void UDigimonVenomNXTProfileSyncWidget::HandleLeave()
{
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer()))
    {
        FString Error;
        if (Controller->RequestLogout(Error)) SetStatus(TEXT("Waiting for the server to confirm your session handoff before returning to login..."), false);
        else SetStatus(Error, true);
    }
}
