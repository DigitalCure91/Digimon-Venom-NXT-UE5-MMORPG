#include "DigimonVenomNXTNameplateWidget.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTUIComponents.h"
#include "Components/MenuAnchor.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

TSharedRef<SWidget> UDigimonVenomNXTNameplateWidget::RebuildWidget()
{
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("NameplateTree"));
    Plate = WidgetTree->ConstructWidget<UBorder>();
    Plate->SetPadding(FMargin(9.0f, 4.0f));
    Plate->SetVerticalAlignment(VAlign_Center);
    ContextAnchor = WidgetTree->ConstructWidget<UMenuAnchor>();
    ContextAnchor->SetPlacement(MenuPlacement_BelowAnchor);
    ContextAnchor->FitInWindow(true);
    ContextAnchor->OnGetUserMenuContentEvent.BindDynamic(this, &UDigimonVenomNXTNameplateWidget::BuildContextMenu);
    WidgetTree->RootWidget = ContextAnchor;
    PlateButton = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    PlateButton->InitializeAction(TEXT("open"));
    PlateButton->OnAction.AddDynamic(this, &UDigimonVenomNXTNameplateWidget::HandlePlateClicked);
    DigimonVenomNXTUI::StyleButton(PlateButton, FLinearColor(0.12f,0.86f,0.95f,1));
    FButtonStyle PlateStyle = PlateButton->GetStyle(); PlateStyle.SetNormalPadding(FMargin(0)); PlateStyle.SetPressedPadding(FMargin(0)); PlateButton->SetStyle(PlateStyle);
    PlateButton->SetToolTipText(FText::FromString(TEXT("Click for player info, friends, ignore, battle and trade")));
    ContextAnchor->AddChild(PlateButton);
    PlateButton->AddChild(Plate);

    UVerticalBox* Content = WidgetTree->ConstructWidget<UVerticalBox>();
    Plate->AddChild(Content);
    TitleText = WidgetTree->ConstructWidget<UTextBlock>();
    FSlateFontInfo TitleFont = TitleText->GetFont();
    TitleFont.Size = 9; TitleText->SetFont(TitleFont);
    TitleText->SetAutoWrapText(false);
    TitleText->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    TitleText->SetJustification(ETextJustify::Center);
    TitleText->SetColorAndOpacity(FLinearColor(1.0f, 0.82f, 0.38f, 1.0f));
    if (UVerticalBoxSlot* TitleSlot = Content->AddChildToVerticalBox(TitleText))
        TitleSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 2.0f));
    UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>();
    Content->AddChildToVerticalBox(Row);
    KindText = WidgetTree->ConstructWidget<UTextBlock>();
    FSlateFontInfo KindFont = KindText->GetFont();
    KindFont.Size = 9; KindFont.TypefaceFontName = TEXT("Bold"); KindText->SetFont(KindFont);
    if (UHorizontalBoxSlot* KindSlot = Row->AddChildToHorizontalBox(KindText))
    {
        KindSlot->SetVerticalAlignment(VAlign_Center);
        KindSlot->SetPadding(FMargin(0.0f, 0.0f, 7.0f, 0.0f));
    }
    NameText = WidgetTree->ConstructWidget<UTextBlock>();
    NameText->SetAutoWrapText(false);
    NameText->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
    FSlateFontInfo NameFont = NameText->GetFont();
    NameFont.Size = 12; NameFont.TypefaceFontName = TEXT("Bold"); NameText->SetFont(NameFont);
    NameText->SetShadowOffset(FVector2D(0.0f, 1.0f));
    NameText->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.65f));
    if (UHorizontalBoxSlot* NameSlot = Row->AddChildToHorizontalBox(NameText))
    {
        NameSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        NameSlot->SetVerticalAlignment(VAlign_Center);
    }
    SetVisibility(bIsOwnTamer ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);
    ApplyIdentity();
    return Super::RebuildWidget();
}

void UDigimonVenomNXTNameplateWidget::SetIdentity(const FString& Name, bool bOwnTamer, bool bAIRival, const FString& Title, const FString& AccountId)
{
    FString CleanTitle;
    if (!bAIRival)
        for (TCHAR Character : Title.Left(32))
            if (Character >= 32 && !(Character >= 127 && Character <= 159)) CleanTitle.AppendChar(Character);
    CleanTitle.TrimStartAndEndInline();
    if (DisplayName == Name && DisplayTitle == CleanTitle && bIsOwnTamer == bOwnTamer && bIsAIRival == bAIRival && TargetAccountId == AccountId) return;
    if (DisplayName != Name || TargetAccountId != AccountId) CloseContextMenu();
    TargetAccountId = AccountId;
    DisplayName = Name; bIsOwnTamer = bOwnTamer; bIsAIRival = bAIRival;
    DisplayTitle = MoveTemp(CleanTitle);
    ApplyIdentity();
}

void UDigimonVenomNXTNameplateWidget::ApplyIdentity()
{
    if (!Plate || !NameText || !KindText || !TitleText) return;
    if (PlateButton) PlateButton->SetIsEnabled(!bIsOwnTamer && !TargetAccountId.IsEmpty());
    const FLinearColor Cyan(0.12f, 0.86f, 0.95f, 1.0f);
    const FLinearColor Accent = bIsOwnTamer ? Cyan :
        (bIsAIRival ? FLinearColor(0.61f, 0.72f, 0.98f, 1.0f) : FLinearColor(0.57f, 0.82f, 0.94f, 1.0f));
    Plate->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.009f, 0.025f, 0.052f, 0.93f), 7.0f,
        Accent.CopyWithNewOpacity(bIsOwnTamer ? 0.85f : 0.50f), 1.0f));
    NameText->SetText(FText::FromString(DisplayName));
    NameText->SetColorAndOpacity(FLinearColor(0.94f, 0.98f, 1.0f, 1.0f));
    TitleText->SetText(FText::FromString(DisplayTitle));
    TitleText->SetVisibility(DisplayTitle.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
    KindText->SetText(FText::FromString(bIsOwnTamer ? TEXT("YOU") : bIsAIRival ? TEXT("AI") : TEXT("P")));
    KindText->SetColorAndOpacity(Accent);
}

void UDigimonVenomNXTNameplateWidget::CloseContextMenu()
{
    if (ContextAnchor) ContextAnchor->Close();
}

void UDigimonVenomNXTNameplateWidget::HandlePlateClicked(const FString& Action, int32 Payload)
{
    if (ContextAnchor && !bIsOwnTamer && !TargetAccountId.IsEmpty()) ContextAnchor->ToggleOpen(true);
}

UUserWidget* UDigimonVenomNXTNameplateWidget::BuildContextMenu()
{
    UDigimonVenomNXTNameplateMenuWidget* Menu = CreateWidget<UDigimonVenomNXTNameplateMenuWidget>(GetOwningPlayer(), UDigimonVenomNXTNameplateMenuWidget::StaticClass());
    if (Menu) Menu->InitializeFor(this);
    return Menu;
}

void UDigimonVenomNXTNameplateMenuWidget::InitializeFor(UDigimonVenomNXTNameplateWidget* Source)
{
    if (!Source) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("ContextTree"));
    UBorder* Frame = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(Frame,FLinearColor(0.008f,0.022f,0.050f,1)); Frame->SetPadding(FMargin(10)); WidgetTree->RootWidget = Frame;
    UVerticalBox* Items = WidgetTree->ConstructWidget<UVerticalBox>(); Frame->SetContent(Items);
    UTextBlock* Title = WidgetTree->ConstructWidget<UTextBlock>(); Title->SetText(FText::FromString(Source->DisplayName)); Title->SetColorAndOpacity(FLinearColor(0.12f,0.88f,0.95f,1));
    FSlateFontInfo Font = Title->GetFont(); Font.Size = 14; Font.TypefaceFontName = TEXT("Bold"); Title->SetFont(Font); Items->AddChildToVerticalBox(Title);
    auto Add = [&](const FString& Label, const FString& Action)
    {
        UDigimonVenomNXTActionButton* B = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>(); DigimonVenomNXTUI::StyleButton(B,FLinearColor(0.12f,0.86f,0.95f,1));
        B->InitializeAction(Action); B->OnAction.AddDynamic(Source,&UDigimonVenomNXTNameplateWidget::HandleContextAction);
        UTextBlock* T = WidgetTree->ConstructWidget<UTextBlock>(); T->SetText(FText::FromString(Label)); FSlateFontInfo F=T->GetFont(); F.Size=12; T->SetFont(F); B->AddChild(T);
        if (UVerticalBoxSlot* S=Items->AddChildToVerticalBox(B)) S->SetPadding(FMargin(0,3));
    };
    Add(Source->bIsAIRival ? TEXT("RIVAL INFO") : TEXT("PLAYER INFO"),TEXT("info"));
    if (!Source->bIsAIRival)
    {
        const UDigimonVenomNXTSocialComponent* Social = GetOwningPlayer() ? GetOwningPlayer()->FindComponentByClass<UDigimonVenomNXTSocialComponent>() : nullptr;
        bool bFriend = false, bIgnored = false;
        if (Social) { for (const auto& P:Social->State.Friends) if(P.AccountId==Source->TargetAccountId) bFriend=true; for(const auto& P:Social->State.Ignored) if(P.AccountId==Source->TargetAccountId) bIgnored=true; }
        Add(bFriend?TEXT("VIEW FRIEND"):TEXT("ADD FRIEND"),bFriend?TEXT("info"):TEXT("friend"));
        Add(bIgnored?TEXT("MANAGE IGNORE"):TEXT("IGNORE USER"),TEXT("ignore"));
        Add(TEXT("DIRECT TRADE"),TEXT("trade"));
    }
    Add(Source->bIsAIRival ? TEXT("CHALLENGE AI RIVAL") : TEXT("LIVE UNRANKED BATTLE"),TEXT("battle"));
    Add(TEXT("CLOSE"),TEXT("close"));
}

void UDigimonVenomNXTNameplateWidget::HandleContextAction(const FString& Action, int32 Payload)
{
    CloseContextMenu();
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    UDigimonVenomNXTGameHUDWidget* HUD = PC ? PC->GetNativeHUDWidget() : nullptr;
    if (!HUD || Action==TEXT("close") || TargetAccountId.IsEmpty()) return;
    if (Action==TEXT("friend"))
    {
        HUD->OpenCommunityTarget(TargetAccountId,DisplayName,false,TEXT("Social"));
        if (UDigimonVenomNXTSocialComponent* S = PC->FindComponentByClass<UDigimonVenomNXTSocialComponent>()) S->ServerSocialAction(EDigimonSocialAction::FriendRequest,TargetAccountId,TEXT(""),TEXT(""));
    }
    else if (Action==TEXT("battle") || (Action==TEXT("info") && bIsAIRival)) HUD->OpenCommunityTarget(TargetAccountId,DisplayName,bIsAIRival,TEXT("Unranked"));
    else if (Action==TEXT("ignore")) HUD->OpenCommunityTarget(TargetAccountId,DisplayName,false,TEXT("Ignore"));
    else if (Action==TEXT("trade")) HUD->OpenCommunityTarget(TargetAccountId,DisplayName,false,TEXT("Trading Center"));
    else HUD->OpenCommunityTarget(TargetAccountId,DisplayName,false,TEXT("Social"));
}
