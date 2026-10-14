#include "DigimonVenomNXTCommunityWidget.h"
#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTTradeComponent.h"
#include "DigimonVenomNXTUnrankedComponent.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTPresentationAssets.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "InputCoreTypes.h"

namespace DigimonCommunityUI
{
    const FLinearColor Cyan(0.12f, 0.88f, 0.95f, 1);
    const FLinearColor Gold(1.0f, 0.78f, 0.31f, 1);
    const FLinearColor Muted(0.63f, 0.76f, 0.84f, 1);
    const FLinearColor Ink(0.011f, 0.032f, 0.060f, 0.98f);
    const FLinearColor White(0.94f, 0.98f, 1, 1);
    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 14, FLinearColor Color = White)
    {
        UTextBlock* W = Tree->ConstructWidget<UTextBlock>();
        W->SetText(FText::FromString(Value)); W->SetAutoWrapText(true); W->SetColorAndOpacity(Color);
        FSlateFontInfo Font = W->GetFont(); Font.Size = Size; if (Size >= 18) Font.TypefaceFontName = TEXT("Bold"); W->SetFont(Font);
        W->SetVisibility(ESlateVisibility::HitTestInvisible);
        return W;
    }
    void Add(UVerticalBox* Parent, UWidget* Child, float Pad = 4)
    {
        if (UVerticalBoxSlot* Slot = Parent->AddChildToVerticalBox(Child)) { Slot->SetPadding(FMargin(0, Pad)); Slot->SetHorizontalAlignment(HAlign_Fill); }
    }
    FString Role(EDigimonClanRole R)
    {
        return R == EDigimonClanRole::Leader ? TEXT("Leader") : R == EDigimonClanRole::Officer ? TEXT("Officer") : R == EDigimonClanRole::Member ? TEXT("Member") : TEXT("No clan");
    }
    FString PartnerName(const FDigimonOwnedPartner& P)
    {
        return FString::Printf(TEXT("%s  •  Lv.%d  •  %s"), P.Nickname.IsEmpty() ? *P.SpeciesId.ToString() : *P.Nickname, P.Level, *DigimonVenomNXTUI::VarietyLabel(P.Variant));
    }
    FString Price(int64 Credits, int32 Rubies)
    {
        return FString::Printf(TEXT("%s money  +  %s digirubies"), *FText::AsNumber(Credits).ToString(), *FText::AsNumber(Rubies).ToString());
    }
    FString Presence(const FDigimonSocialContact& P)
    {
        return P.bOnline ? FString::Printf(TEXT("ONLINE  •  %s  •  Lead Lv.%d"), *P.Location, P.LeadLevel) : TEXT("OFFLINE");
    }
}

UDigimonVenomNXTCommunityWidget::FAction UDigimonVenomNXTCommunityWidget::Make(const FString& Kind, const FString& Target) const
{
    FAction A; A.Kind = Kind; A.Target = Target; return A;
}

void UDigimonVenomNXTCommunityWidget::Configure(FName InSection)
{
    if (bBuilt) return;
    Section = InSection;
    Mode = Section == TEXT("Clans") ? TEXT("Live") : Section == TEXT("Trading Center") ? TEXT("Market") : Section == TEXT("Unranked") ? TEXT("Players") : TEXT("Friends");
    Build();
}

void UDigimonVenomNXTCommunityWidget::NativeConstruct()
{
    Super::NativeConstruct(); Build(); Bind(); Refresh();
}

void UDigimonVenomNXTCommunityWidget::NativeDestruct()
{
    if (Social.IsValid()) { Social->OnSocialChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); Social->OnSocialResult.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleSocialResult); }
    if (Trade.IsValid()) Trade->OnTradeChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged);
    if (Unranked.IsValid()) Unranked->OnUnrankedChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged);
    if (Player.IsValid()) Player->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleProfileChanged);
    Social.Reset(); Trade.Reset(); Unranked.Reset(); Player.Reset();
    Super::NativeDestruct();
}

void UDigimonVenomNXTCommunityWidget::Bind()
{
    APlayerController* PC = GetOwningPlayer(); if (!PC) return;
    UDigimonVenomNXTSocialComponent* S = PC->FindComponentByClass<UDigimonVenomNXTSocialComponent>();
    UDigimonVenomNXTTradeComponent* T = PC->FindComponentByClass<UDigimonVenomNXTTradeComponent>();
    UDigimonVenomNXTUnrankedComponent* U = PC->FindComponentByClass<UDigimonVenomNXTUnrankedComponent>();
    ADigimonVenomNXTPlayerState* P = PC->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (Social.Get() != S) { if (Social.IsValid()) { Social->OnSocialChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); Social->OnSocialResult.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleSocialResult); } Social = S; if (S) { S->OnSocialChanged.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); S->OnSocialResult.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleSocialResult); } }
    if (Trade.Get() != T) { if (Trade.IsValid()) Trade->OnTradeChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); Trade = T; if (T) T->OnTradeChanged.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); }
    if (Unranked.Get() != U) { if (Unranked.IsValid()) Unranked->OnUnrankedChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); Unranked = U; if (U) U->OnUnrankedChanged.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleChanged); }
    if (Player.Get() != P) { if (Player.IsValid()) Player->OnProfileChanged.RemoveDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleProfileChanged); Player = P; if (P) { P->OnProfileChanged.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleProfileChanged); RefreshPartnerOptions(); } }
}

void UDigimonVenomNXTCommunityWidget::SetPageActive(bool bInActive)
{
    const bool bOpened = bInActive && !bActive; bActive = bInActive;
    if (!bActive) { HandleBack(); return; }
    Bind(); if (bOpened) { Refresh(); RequestRefresh(); } else if (bDirty) Refresh();
}

void UDigimonVenomNXTCommunityWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
    Super::NativeTick(Geometry, DeltaSeconds);
    if (!bActive) return;
    RefreshTime += DeltaSeconds;
    if (RefreshTime >= 5.0f) { RefreshTime = 0; Bind(); RequestRefresh(); }
    if (bDirty) Refresh();
}

FReply UDigimonVenomNXTCommunityWidget::NativeOnPreviewKeyDown(const FGeometry& Geometry, const FKeyEvent& Event)
{
    if ((Event.GetKey() == EKeys::Escape || Event.GetKey() == EKeys::Gamepad_FaceButton_Right) && HandleBack()) return FReply::Handled();
    return Super::NativeOnPreviewKeyDown(Geometry, Event);
}

bool UDigimonVenomNXTCommunityWidget::HandleBack()
{
    if (!Confirmation || Confirmation->GetVisibility() == ESlateVisibility::Collapsed) return false;
    Confirmation->SetVisibility(ESlateVisibility::Collapsed); Body->SetIsEnabled(true); PendingAction = FAction(); return true;
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTCommunityWidget::Button(const FString& Label, const FAction& A, bool bDynamic, bool bEnabled)
{
    UDigimonVenomNXTActionButton* B = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    const int32 Key = NextAction++; Actions.Add(Key, A); if (bDynamic) DynamicActionIds.Add(Key);
    B->InitializeAction(TEXT("community"), Key); B->OnAction.AddDynamic(this, &UDigimonVenomNXTCommunityWidget::HandleAction);
    DigimonVenomNXTUI::StyleButton(B, A.Kind.Contains(TEXT("delete")) || A.Kind.Contains(TEXT("disband")) ? DigimonCommunityUI::Gold : DigimonCommunityUI::Cyan);
    UTextBlock* LabelText = DigimonCommunityUI::Text(WidgetTree, Label, 12); LabelText->SetJustification(ETextJustify::Center); B->AddChild(LabelText);
    B->SetToolTipText(FText::FromString(Label)); B->SetIsEnabled(bEnabled); return B;
}

void UDigimonVenomNXTCommunityWidget::AddAction(UVerticalBox* Parent, const FString& Label, const FAction& A, bool bEnabled)
{
    DigimonCommunityUI::Add(Parent, Button(Label, A, true, bEnabled), 3);
}

UVerticalBox* UDigimonVenomNXTCommunityWidget::Form(const FString& Key)
{
    UVerticalBox* V = WidgetTree->ConstructWidget<UVerticalBox>(); Forms.Add(Key, V); DigimonCommunityUI::Add(FormHost, V, 3); return V;
}

UEditableTextBox* UDigimonVenomNXTCommunityWidget::Input(UVerticalBox* Parent, const FString& Key, const FString& Label, const FString& Hint, int32 MaxLength)
{
    using namespace DigimonCommunityUI;
    Add(Parent, Text(WidgetTree, Label, 11, Muted), 1);
    UEditableTextBox* E = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(E); E->SetHintText(FText::FromString(Hint));
    E->SetToolTipText(FText::FromString(FString::Printf(TEXT("%s • maximum %d characters"), *Label, MaxLength)));
    E->SetSelectAllTextWhenFocused(false); Inputs.Add(Key, E); Add(Parent, E, 2); return E;
}

void UDigimonVenomNXTCommunityWidget::Build()
{
    if (bBuilt || !WidgetTree) return; bBuilt = true;
    using namespace DigimonCommunityUI;
    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>(); WidgetTree->RootWidget = Root;
    Body = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* S = Root->AddChildToOverlay(Body)) { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
    UBorder* Hero = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(Hero, Ink); Hero->SetPadding(FMargin(12)); Add(Body, Hero, 0);
    UHorizontalBox* Header = WidgetTree->ConstructWidget<UHorizontalBox>(); Hero->SetContent(Header);
    const FName Art = Section == TEXT("Clans") ? FName(TEXT("ClansHero")) : Section == TEXT("Trading Center") ? FName(TEXT("TradingHero")) : FName(TEXT("CommunityHero"));
    if (UTexture2D* Image = DigimonVenomNXTPresentationAssets::LoadTexture(Art))
    {
        if (UHorizontalBoxSlot* S = Header->AddChildToHorizontalBox(DigimonVenomNXTUI::Texture(WidgetTree, Image, 194, 96))) S->SetPadding(FMargin(0,0,16,0));
    }
    UVerticalBox* Heading = WidgetTree->ConstructWidget<UVerticalBox>(); if (UHorizontalBoxSlot* S = Header->AddChildToHorizontalBox(Heading)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); }
    Add(Heading, Text(WidgetTree, Section == TEXT("Social") ? TEXT("YOUR TAMER NETWORK") : Section == TEXT("Unranked") ? TEXT("LIVE UNRANKED BATTLES") : Section.ToString().ToUpper(), 24, Cyan), 2);
    const FString Tagline = Section == TEXT("Social") ? TEXT("Stay connected. Find your friends. Choose who can reach you.") : Section == TEXT("Clans") ? TEXT("Find your people. Build your clan. Explore together.") : Section == TEXT("Unranked") ? TEXT("Challenge a nearby tamer or AI rival. Your skill, without the rating stakes.") : TEXT("Discover a new partner. List, buy, or agree a direct exchange.");
    Add(Heading, Text(WidgetTree, Tagline, 13, Muted), 2);
    TabRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body, TabRow, 6);
    const TArray<FString> Modes = Section == TEXT("Social") ? TArray<FString>{TEXT("Friends"),TEXT("Requests"),TEXT("Ignored"),TEXT("Player info")} : Section == TEXT("Clans") ? TArray<FString>{TEXT("Live"),TEXT("Roster"),TEXT("Manage"),TEXT("Invitations")} : Section == TEXT("Unranked") ? TArray<FString>{TEXT("Players"),TEXT("AI rivals")} : TArray<FString>{TEXT("Market"),TEXT("My listings"),TEXT("Create listing"),TEXT("Direct trade")};
    for (const FString& M : Modes)
    {
        UDigimonVenomNXTActionButton* B = Button(M.ToUpper(), Make(TEXT("mode"), M)); Tabs.Add(M, B);
        if (UHorizontalBoxSlot* S = TabRow->AddChildToHorizontalBox(B)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0,0,4,0)); }
    }
    Summary = Text(WidgetTree, TEXT("Connecting to the world server..."), 12, Muted); Add(Body, Summary, 3);
    Status = Text(WidgetTree, TEXT(""), 13, Gold); Add(Body, Status, 2);
    Scroll = WidgetTree->ConstructWidget<UScrollBox>();
    if (UVerticalBoxSlot* S = Body->AddChildToVerticalBox(Scroll)) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0,6,0,0)); }
    FormHost = WidgetTree->ConstructWidget<UVerticalBox>(); Scroll->AddChild(FormHost);
    if (Section == TEXT("Social"))
    {
        UVerticalBox* V = Form(TEXT("social")); Input(V, TEXT("target"), TEXT("TAMER USERNAME"), TEXT("Enter an exact account username"), 32);
        UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(V, Row, 3);
        for (const auto& Pair : TArray<TPair<FString,FString>>{{TEXT("VIEW PLAYER"),TEXT("find")},{TEXT("ADD FRIEND"),TEXT("friend-request-input")},{TEXT("IGNORE USER"),TEXT("ignore-input")}})
        { if (UHorizontalBoxSlot* S = Row->AddChildToHorizontalBox(Button(Pair.Key, Make(Pair.Value)))) { S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetPadding(FMargin(0,0,4,0)); } }
    }
    else if (Section == TEXT("Clans"))
    {
        UVerticalBox* Create = Form(TEXT("clan-create"));
        Input(Create,TEXT("clan-name"),TEXT("CLAN NAME  •  3–32 CHARACTERS"),TEXT("Your clan's name"),32);
        Input(Create,TEXT("clan-tag"),TEXT("TAG  •  2–5 LETTERS / NUMBERS"),TEXT("NXT"),5);
        Input(Create,TEXT("clan-description"),TEXT("ABOUT YOUR CLAN"),TEXT("What brings your clan together?"),240);
        Add(Create,Button(TEXT("CREATE CLAN"),Make(TEXT("clan-create"))));
        UVerticalBox* Manage = Form(TEXT("clan-manage"));
        Input(Manage,TEXT("motd"),TEXT("MESSAGE OF THE DAY"),TEXT("A message for every clan member"),200);
        Input(Manage,TEXT("description"),TEXT("CLAN DESCRIPTION"),TEXT("What brings your clan together?"),240);
        Add(Manage,Button(TEXT("SAVE CLAN DETAILS"),Make(TEXT("clan-update"))));
        UVerticalBox* Invite = Form(TEXT("clan-invite")); Input(Invite,TEXT("invite"),TEXT("INVITE A TAMER"),TEXT("Exact account username"),32);
        Add(Invite,Button(TEXT("SEND CLAN INVITATION"),Make(TEXT("clan-invite"))));
        UVerticalBox* Chat = Form(TEXT("clan-chat")); Input(Chat,TEXT("chat"),TEXT("CLAN CHAT"),TEXT("Write to your clan, then press Enter"),256)->OnTextCommitted.AddDynamic(this,&UDigimonVenomNXTCommunityWidget::HandleChatCommitted);
        Add(Chat,Button(TEXT("SEND TO CLAN"),Make(TEXT("clan-chat"))));
    }
    else if (Section == TEXT("Trading Center"))
    {
        UVerticalBox* Search = Form(TEXT("market-search")); Input(Search,TEXT("search"),TEXT("SEARCH LISTINGS"),TEXT("Species, nickname or seller"),64);
        Add(Search,Button(TEXT("SEARCH / REFRESH"),Make(TEXT("search"))));
        UVerticalBox* List = Form(TEXT("listing")); Add(List,Text(WidgetTree,TEXT("CHOOSE A DIGIMON FROM YOUR COLLECTION"),11,Muted),1);
        ListingPartner = WidgetTree->ConstructWidget<UComboBoxString>(); ListingPartner->SetMaxListHeight(240); Add(List,ListingPartner,3);
        Input(List,TEXT("listing-money"),TEXT("ASKING PRICE — MONEY"),TEXT("0"),18);
        Input(List,TEXT("listing-rubies"),TEXT("ASKING PRICE — DIGIRUBIES"),TEXT("0"),10);
        Add(List,Text(WidgetTree,TEXT("Set money, digirubies, or both. The listed Digimon is held safely until purchased or cancelled. Remove the partner from your party, farm and ranked defense before listing."),12,Muted));
        Add(List,Button(TEXT("REVIEW LISTING"),Make(TEXT("listing-review"))));
        UVerticalBox* Invite = Form(TEXT("trade-invite")); Input(Invite,TEXT("trade-target"),TEXT("TRADE WITH A LIVE TAMER"),TEXT("Exact account username"),32);
        Add(Invite,Button(TEXT("INVITE TO DIRECT TRADE"),Make(TEXT("trade-invite"))));
        UVerticalBox* Offer = Form(TEXT("trade-offer"));
        Add(Offer,Text(WidgetTree,TEXT("YOUR OFFER  •  UP TO SIX DIGIMON"),11,Muted));
        for (int32 I=0; I<6; ++I) { UComboBoxString* C=WidgetTree->ConstructWidget<UComboBoxString>(); C->SetMaxListHeight(180); OfferPartners.Add(C); Add(Offer,C,1); }
        Input(Offer,TEXT("offer-money"),TEXT("MONEY YOU GIVE"),TEXT("0"),18);
        Input(Offer,TEXT("offer-rubies"),TEXT("DIGIRUBIES YOU GIVE"),TEXT("0"),10);
        Add(Offer,Button(TEXT("UPDATE MY OFFER"),Make(TEXT("offer-update"))));
        Add(Offer,Text(WidgetTree,TEXT("Updating either offer clears both confirmations. Review the full exchange below, then confirm its exact revision."),12,Muted));
    }
    Live = WidgetTree->ConstructWidget<UVerticalBox>(); DigimonCommunityUI::Add(FormHost, Live);
    Confirmation = WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(Confirmation,FLinearColor(0,0.005f,0.015f,0.98f)); Confirmation->SetPadding(FMargin(30));
    if (UOverlaySlot* S = Root->AddChildToOverlay(Confirmation)) { S->SetHorizontalAlignment(HAlign_Fill); S->SetVerticalAlignment(VAlign_Fill); }
    UVerticalBox* Confirm = WidgetTree->ConstructWidget<UVerticalBox>(); Confirmation->SetContent(Confirm);
    ConfirmationTitle=Text(WidgetTree,TEXT("REVIEW"),24,Gold); Add(Confirm,ConfirmationTitle,8);
    UScrollBox* ConfirmScroll=WidgetTree->ConstructWidget<UScrollBox>(); if(UVerticalBoxSlot* S=Confirm->AddChildToVerticalBox(ConfirmScroll)) S->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    ConfirmationText=Text(WidgetTree,TEXT(""),16); ConfirmScroll->AddChild(ConfirmationText);
    ConfirmationName=WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(ConfirmationName);
    ConfirmationName->SetHintText(FText::FromString(TEXT("Type the exact clan name to confirm"))); Add(Confirm,ConfirmationName,6);
    ConfirmationName->SetVisibility(ESlateVisibility::Collapsed);
    ConfirmationButton=Button(TEXT("CONFIRM"),Make(TEXT("confirm"))); Add(Confirm,ConfirmationButton,8);
    Add(Confirm,Button(TEXT("GO BACK"),Make(TEXT("cancel-confirm"))),3);
    Confirmation->SetVisibility(ESlateVisibility::Collapsed);
    SetMode(Mode);
}

FString UDigimonVenomNXTCommunityWidget::Value(const FString& Key) const
{
    const TObjectPtr<UEditableTextBox>* E=Inputs.Find(Key); return E && *E ? (*E)->GetText().ToString().TrimStartAndEnd() : FString();
}

bool UDigimonVenomNXTCommunityWidget::ReadPrice(const FString& Prefix, int64& Credits, int32& Rubies)
{
    // Parse with explicit bounds: integer conversion must never wrap a large typed price.
    auto Parse=[](const FString& S, int64 Cap, int64& Out)
    {
        Out=0; if(S.Len()>18) return false;
        for(TCHAR Ch:S)
        {
            if(Ch<TEXT('0')||Ch>TEXT('9')) return false;
            const int64 Digit=Ch-TEXT('0');
            if(Out>(Cap-Digit)/10) return false;
            Out=Out*10+Digit;
        }
        return true;
    };
    int64 ParsedRubies=0; Credits=0; Rubies=0;
    if(!Parse(Value(Prefix+TEXT("-money")),9007199254740991LL,Credits) || !Parse(Value(Prefix+TEXT("-rubies")),2147483647LL,ParsedRubies))
    { ShowStatus(TEXT("Enter whole, non-negative currency amounts within the supported limits."),false); return false; }
    Rubies=static_cast<int32>(ParsedRubies); return true;
}

void UDigimonVenomNXTCommunityWidget::ShowStatus(const FString& Message, bool bSuccess)
{
    if(Status) { Status->SetText(FText::FromString(Message)); Status->SetColorAndOpacity(bSuccess?DigimonCommunityUI::Cyan:DigimonCommunityUI::Gold); }
}

void UDigimonVenomNXTCommunityWidget::SetMode(const FString& NewMode)
{
    Mode=NewMode; HandleBack();
    for(const auto& P:Tabs) DigimonVenomNXTUI::StyleButton(P.Value,DigimonCommunityUI::Cyan,P.Key==Mode);
    bDirty=true; if(bBuilt) Refresh();
}

void UDigimonVenomNXTCommunityWidget::HandleChanged() { bDirty=true; }
void UDigimonVenomNXTCommunityWidget::HandleProfileChanged() { RefreshPartnerOptions(); bDirty=true; }
void UDigimonVenomNXTCommunityWidget::HandleSocialResult(bool bSuccess,const FString& Message) { if(bActive&&(Section==TEXT("Social")||Section==TEXT("Clans"))) ShowStatus(Message,bSuccess); bDirty=true; }
void UDigimonVenomNXTCommunityWidget::HandleChatCommitted(const FText& Text,ETextCommit::Type Commit) { if(Commit==ETextCommit::OnEnter) Execute(Make(TEXT("clan-chat"))); }

void UDigimonVenomNXTCommunityWidget::RequestRefresh()
{
    if (!bActive) return;
    if ((Section==TEXT("Social")||Section==TEXT("Clans"))&&Social.IsValid()) Social->ServerRefreshSocial();
    if (Section==TEXT("Unranked")&&Unranked.IsValid()) Unranked->ServerRefresh();
    if (Section==TEXT("Trading Center")&&Trade.IsValid() && (Mode==TEXT("Market")||Mode==TEXT("My listings"))) Trade->ServerBrowse(SubmittedSearch,BrowsePage,Mode==TEXT("My listings"));
}

void UDigimonVenomNXTCommunityWidget::OpenTarget(const FString& TargetId,const FString& Name,bool bRival)
{
    Bind(); TargetAccount=TargetId; bTargetRival=bRival;
    if(Inputs.Contains(TEXT("target"))) Inputs[TEXT("target")]->SetText(FText::FromString(Name));
    if(Inputs.Contains(TEXT("trade-target"))) Inputs[TEXT("trade-target")]->SetText(FText::FromString(Name));
    if(Section==TEXT("Social")) { SetMode(TEXT("Player info")); if(Social.IsValid()&&!bRival) Social->ServerRequestPlayerInfo(TargetId); }
    else if(Section==TEXT("Unranked")) { SetMode(bRival?TEXT("AI rivals"):TEXT("Players")); RequestRefresh(); }
    else if(Section==TEXT("Trading Center")) SetMode(TEXT("Direct trade"));
}

UVerticalBox* UDigimonVenomNXTCommunityWidget::Card(const FString& Title,const FString& Detail)
{
    using namespace DigimonCommunityUI;
    UBorder* B=WidgetTree->ConstructWidget<UBorder>(); DigimonVenomNXTUI::StylePanel(B,Ink); B->SetPadding(FMargin(12)); Add(Live,B,4);
    UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); B->SetContent(V); Add(V,Text(WidgetTree,Title,18,Cyan),1);
    if(!Detail.IsEmpty()) Add(V,Text(WidgetTree,Detail,13,Muted),3); return V;
}

void UDigimonVenomNXTCommunityWidget::Refresh()
{
    if(!bBuilt||!Live) return; bDirty=false;
    const float Offset=Scroll->GetScrollOffset();
    for(int32 Key:DynamicActionIds) Actions.Remove(Key); DynamicActionIds.Reset(); Live->ClearChildren();
    VisibleForms.Reset();
    if(Section==TEXT("Social")) RefreshSocial(); else if(Section==TEXT("Clans")) RefreshClans(); else if(Section==TEXT("Unranked")) RefreshUnranked(); else RefreshTrading();
    for(const auto& Pair:Forms) { const ESlateVisibility Wanted=VisibleForms.Contains(Pair.Key)?ESlateVisibility::Visible:ESlateVisibility::Collapsed; if(Pair.Value->GetVisibility()!=Wanted) Pair.Value->SetVisibility(Wanted); }
    Scroll->SetScrollOffset(Offset);
}

void UDigimonVenomNXTCommunityWidget::RefreshSocial()
{
    using namespace DigimonCommunityUI;
    VisibleForms.Add(TEXT("social"));
    if(!Social.IsValid()||!Social->State.bReady) { Card(TEXT("Connecting your account"),TEXT("Friends, requests and ignored users will appear when the world server responds.")); return; }
    const FDigimonSocialState& S=Social->State;
    Summary->SetText(FText::FromString(FString::Printf(TEXT("%d FRIENDS  •  %d INCOMING REQUESTS  •  %d IGNORED"),S.Friends.Num(),S.IncomingFriends.Num(),S.Ignored.Num())));
    auto Contact=[&](const FDigimonSocialContact& P,const FString& Kind)
    {
        UVerticalBox* V=Card(P.Username,Presence(P));
        AddAction(V,TEXT("VIEW PLAYER INFO"),Make(TEXT("profile"),P.AccountId));
        if(Kind==TEXT("friend"))
        {
            AddAction(V,TEXT("CHALLENGE TO UNRANKED"),Make(TEXT("challenge-player"),P.AccountId),P.bOnline);
            AddAction(V,TEXT("OPEN DIRECT TRADE"),Make(TEXT("open-trade"),P.AccountId),P.bOnline);
            AddAction(V,TEXT("REMOVE FRIEND"),Make(TEXT("friend-remove"),P.AccountId));
        }
        else if(Kind==TEXT("incoming")) { AddAction(V,TEXT("ACCEPT FRIEND REQUEST"),Make(TEXT("friend-accept"),P.AccountId)); AddAction(V,TEXT("DECLINE"),Make(TEXT("friend-decline"),P.AccountId)); }
        else if(Kind==TEXT("outgoing")) AddAction(V,TEXT("CANCEL REQUEST"),Make(TEXT("friend-cancel"),P.AccountId));
        else AddAction(V,TEXT("STOP IGNORING"),Make(TEXT("ignore-remove"),P.AccountId));
    };
    if(Mode==TEXT("Friends")) { for(const auto& P:S.Friends) Contact(P,TEXT("friend")); if(S.Friends.IsEmpty()) Card(TEXT("Your next adventure starts with a friend"),TEXT("Enter a tamer's username above, or click a player nameplate in the field to send a friend request. Both players must accept the friendship.")); }
    else if(Mode==TEXT("Requests"))
    {
        for(const auto& P:S.IncomingFriends) Contact(P,TEXT("incoming"));
        for(const auto& P:S.OutgoingFriends) Contact(P,TEXT("outgoing"));
        if(S.IncomingFriends.IsEmpty()&&S.OutgoingFriends.IsEmpty()) Card(TEXT("All caught up"),TEXT("New friend requests and requests awaiting a reply appear here."));
    }
    else if(Mode==TEXT("Ignored"))
    {
        Card(TEXT("You control your social space"),TEXT("Ignoring a player hides their chat and blocks new social invitations from them. You can stop ignoring them at any time."));
        for(const auto& P:S.Ignored) Contact(P,TEXT("ignored"));
        if(S.Ignored.IsEmpty()) Card(TEXT("No ignored users"));
    }
    else
    {
        const FDigimonSocialPlayerInfo& P=S.PlayerInfo;
        if(bTargetRival) { Card(TEXT("AI rival"),TEXT("AI rivals are simulated tamers. Open UNRANKED → AI RIVALS for nearby challenges and RIVALS for their persistent activity record.")); return; }
        if(!P.bValid || (!TargetAccount.IsEmpty() && P.Player.AccountId!=TargetAccount && !P.Player.Username.Equals(TargetAccount,ESearchCase::IgnoreCase))) { Card(TEXT("Find a tamer"),TEXT("Search an exact username above, or choose Player info from a nameplate.")); return; }
        UVerticalBox* V=Card(P.Player.Username,Presence(P.Player));
        Add(V,Text(WidgetTree,P.bUnrankedStatsAvailable ? FString::Printf(TEXT("UNRANKED  •  %d WINS / %d LOSSES / %d DRAWS"),P.UnrankedWins,P.UnrankedLosses,P.UnrankedDraws) : TEXT("Unranked record is available when this player is online."),13,Muted));
        if(!P.EquippedTitle.IsEmpty()) Add(V,Text(WidgetTree,P.EquippedTitle,16,Gold));
        Add(V,Text(WidgetTree,P.ClanName.IsEmpty()?TEXT("No clan"):FString::Printf(TEXT("[%s] %s  •  %s"),*P.ClanTag,*P.ClanName,*Role(P.ClanRole)),14,Muted));
        if(Player.IsValid()&&P.Player.AccountId==Player->Profile.AccountId) { Add(V,Text(WidgetTree,TEXT("This is your public player information."),13,Muted)); return; }
        if(P.bIncomingRequest) { AddAction(V,TEXT("ACCEPT FRIEND REQUEST"),Make(TEXT("friend-accept"),P.Player.AccountId)); AddAction(V,TEXT("DECLINE REQUEST"),Make(TEXT("friend-decline"),P.Player.AccountId)); }
        else if(P.bFriend) AddAction(V,TEXT("REMOVE FRIEND"),Make(TEXT("friend-remove"),P.Player.AccountId));
        else if(P.bOutgoingRequest) AddAction(V,TEXT("CANCEL PENDING FRIEND REQUEST"),Make(TEXT("friend-cancel"),P.Player.AccountId));
        else AddAction(V,TEXT("ADD FRIEND"),Make(TEXT("friend-request"),P.Player.AccountId),!P.bIgnored);
        AddAction(V,P.bIgnored?TEXT("STOP IGNORING"):TEXT("IGNORE USER"),Make(P.bIgnored?TEXT("ignore-remove"):TEXT("ignore-add"),P.Player.AccountId));
        AddAction(V,TEXT("CHALLENGE TO LIVE UNRANKED"),Make(TEXT("challenge-player"),P.Player.AccountId),P.Player.bOnline&&!P.bIgnored);
        AddAction(V,TEXT("OPEN DIRECT TRADE"),Make(TEXT("open-trade"),P.Player.AccountId),P.Player.bOnline&&!P.bIgnored);
        if(S.Clan.YourRole==EDigimonClanRole::Leader||S.Clan.YourRole==EDigimonClanRole::Officer) AddAction(V,TEXT("INVITE TO YOUR CLAN"),Make(TEXT("clan-invite-target"),P.Player.AccountId),!P.bIgnored);
    }
}

void UDigimonVenomNXTCommunityWidget::RefreshClans()
{
    using namespace DigimonCommunityUI;
    if(!Social.IsValid()||!Social->State.bReady) { Card(TEXT("Connecting to clans"),TEXT("Your clan membership, invitations and live roster are loading.")); return; }
    const FDigimonSocialState& S=Social->State; const FDigimonClanView& C=S.Clan;
    const bool bMember=!C.ClanId.IsEmpty(); const bool bLeader=C.YourRole==EDigimonClanRole::Leader;
    const bool bOfficer=bLeader||C.YourRole==EDigimonClanRole::Officer;
    Summary->SetText(FText::FromString(bMember?FString::Printf(TEXT("[%s] %s  •  %s  •  %d MEMBERS"),*C.Tag,*C.Name,*Role(C.YourRole),C.Members.Num()):FString::Printf(TEXT("NO CLAN YET  •  %d INVITATIONS"),S.ClanInvites.Num())));
    if(LoadedClanId!=C.ClanId)
    {
        LoadedClanId=C.ClanId;
        Inputs[TEXT("motd")]->SetText(FText::FromString(C.MessageOfTheDay)); Inputs[TEXT("description")]->SetText(FText::FromString(C.Description));
    }
    if(Mode==TEXT("Invitations"))
    {
        for(const FDigimonClanInviteView& I:S.ClanInvites)
        {
            UVerticalBox* V=Card(I.ClanName,FString::Printf(TEXT("Invited by %s"),*I.InviterName));
            AddAction(V,TEXT("JOIN CLAN"),Make(TEXT("clan-accept"),I.ClanId),!bMember); AddAction(V,TEXT("DECLINE"),Make(TEXT("clan-decline"),I.ClanId));
        }
        if(S.ClanInvites.IsEmpty()) Card(TEXT("No pending clan invitations"),TEXT("A clan leader or officer can invite you by account username.")); return;
    }
    if(!bMember)
    {
        VisibleForms.Add(TEXT("clan-create"));
        Card(TEXT("Start something together"),TEXT("Create your own clan here, or open Invitations to join a clan. Clan members share a live roster, message of the day and private clan chat.")); return;
    }
    if(Mode==TEXT("Live"))
    {
        UVerticalBox* V=Card(C.Name,C.Description);
        Add(V,Text(WidgetTree,TEXT("MESSAGE OF THE DAY"),11,Gold)); Add(V,Text(WidgetTree,C.MessageOfTheDay.IsEmpty()?TEXT("Your clan has not posted a message yet."):C.MessageOfTheDay,16));
        int32 Online=0; for(const auto& M:C.Members) if(M.Player.bOnline) ++Online;
        Add(V,Text(WidgetTree,FString::Printf(TEXT("%d / %d MEMBERS ONLINE"),Online,C.Members.Num()),12,Cyan));
        VisibleForms.Add(TEXT("clan-chat"));
        UVerticalBox* Chat=Card(TEXT("CLAN CHAT"),TEXT("Only members of your clan can read this conversation."));
        if(S.ClanChat.IsEmpty()) Add(Chat,Text(WidgetTree,TEXT("No messages yet. Say hello to your clan."),13,Muted));
        for(const FDigimonChatMessage& M:S.ClanChat) Add(Chat,Text(WidgetTree,FString::Printf(TEXT("%s: %s"),*M.Sender,*M.Message),13),2);
    }
    else if(Mode==TEXT("Roster"))
    {
        if(bOfficer) VisibleForms.Add(TEXT("clan-invite"));
        for(const FDigimonClanMemberView& M:C.Members)
        {
            UVerticalBox* V=Card(FString::Printf(TEXT("%s  •  %s"),*M.Player.Username,*Role(M.Role)),Presence(M.Player));
            AddAction(V,TEXT("VIEW PLAYER INFO"),Make(TEXT("open-profile"),M.Player.AccountId));
            const bool bSelf=Player.IsValid()&&M.Player.AccountId==Player->Profile.AccountId;
            if(!bSelf&&bOfficer&&static_cast<uint8>(C.YourRole)>static_cast<uint8>(M.Role)) AddAction(V,TEXT("REMOVE FROM CLAN"),Make(TEXT("clan-kick"),M.Player.AccountId));
            if(!bSelf&&bLeader)
            {
                AddAction(V,M.Role==EDigimonClanRole::Officer?TEXT("DEMOTE TO MEMBER"):TEXT("PROMOTE TO OFFICER"),Make(M.Role==EDigimonClanRole::Officer?TEXT("clan-demote"):TEXT("clan-promote"),M.Player.AccountId));
                AddAction(V,TEXT("TRANSFER LEADERSHIP"),Make(TEXT("clan-transfer"),M.Player.AccountId));
            }
        }
    }
    else
    {
        if(bOfficer) { VisibleForms.Add(TEXT("clan-manage")); VisibleForms.Add(TEXT("clan-invite")); }
        UVerticalBox* V=Card(TEXT("MEMBERSHIP"),bLeader?TEXT("As leader, you can promote officers, transfer leadership from the roster, or permanently disband this clan."):TEXT("Leaving removes your access to the clan roster and chat. You can join another clan after leaving."));
        if(bLeader) AddAction(V,TEXT("DISBAND CLAN…"),Make(TEXT("clan-disband"),C.ClanId));
        else AddAction(V,TEXT("LEAVE CLAN…"),Make(TEXT("clan-leave")));
    }
}

void UDigimonVenomNXTCommunityWidget::RefreshUnranked()
{
    using namespace DigimonCommunityUI;
    if(!Unranked.IsValid()) { Card(TEXT("Connecting to the battle service")); return; }
    if(Player.IsValid()) Summary->SetText(FText::FromString(FString::Printf(TEXT("YOUR RECORD  •  %d WINS  /  %d LOSSES  /  %d DRAWS"),Player->Profile.UnrankedWins,Player->Profile.UnrankedLosses,Player->Profile.UnrankedDraws)));
    if(!Unranked->StatusMessage.IsEmpty()) ShowStatus(Unranked->StatusMessage);
    Card(TEXT("FRIENDLY MATCH RULES"),TEXT("Same-map challenges. Original team levels, fully restored battle HP and SP. No ranked rating, energy, consumables or item rewards. Both players choose their own actions; a decision has a 90-second deadline plus animation time. Surrender counts as a loss."));
    const FDigimonUnrankedChallenge& Incoming=Unranked->IncomingChallenge;
    if(Incoming.ChallengeId.IsValid())
    {
        UVerticalBox* V=Card(TEXT("A TAMER HAS CHALLENGED YOU"),FString::Printf(TEXT("%s wants a live unranked match. Challenge expires at %s UTC."),*Incoming.OtherName,*FDateTime::FromUnixTimestamp(Incoming.ExpiresUnix).ToString(TEXT("%H:%M:%S"))));
        FAction A=Make(TEXT("challenge-accept")); A.Id=Incoming.ChallengeId; AddAction(V,TEXT("ACCEPT AND ENTER BATTLE"),A); A.Kind=TEXT("challenge-decline"); AddAction(V,TEXT("DECLINE"),A);
    }
    const FDigimonUnrankedChallenge& Outgoing=Unranked->OutgoingChallenge;
    if(Outgoing.ChallengeId.IsValid())
    {
        UVerticalBox* V=Card(TEXT("WAITING FOR A REPLY"),FString::Printf(TEXT("Challenge sent to %s."),*Outgoing.OtherName)); FAction A=Make(TEXT("challenge-cancel")); A.Id=Outgoing.ChallengeId; AddAction(V,TEXT("CANCEL CHALLENGE"),A);
    }
    const bool bRivals=Mode==TEXT("AI rivals"); const auto& Targets=bRivals?Unranked->NearbyRivals:Unranked->NearbyPlayers;
    if(Targets.IsEmpty()) Card(bRivals?TEXT("No available rivals on this map"):TEXT("No other tamers on this map"),TEXT("Explore a public level map, then refresh. Private story maps and DigiFarm do not accept challenges."));
    for(const FDigimonUnrankedTarget& P:Targets)
    {
        UVerticalBox* V=Card(P.DisplayName,FString::Printf(TEXT("%s  •  Lv.%d  •  %s"),bRivals?TEXT("AI RIVAL"):TEXT("LIVE PLAYER"),P.Level,P.bAvailable?TEXT("READY"):TEXT("BUSY")));
        if(!TargetAccount.IsEmpty()&&P.AccountId==TargetAccount) Add(V,Text(WidgetTree,TEXT("SELECTED TAMER"),11,Gold));
        AddAction(V,bRivals?TEXT("BATTLE AI RIVAL"):TEXT("SEND LIVE CHALLENGE"),Make(bRivals?TEXT("challenge-rival"):TEXT("challenge-player"),P.AccountId),P.bAvailable&&!Incoming.ChallengeId.IsValid()&&!Outgoing.ChallengeId.IsValid());
        if(!bRivals) AddAction(V,TEXT("VIEW PLAYER INFO"),Make(TEXT("open-profile"),P.AccountId));
    }
    AddAction(Live,TEXT("REFRESH NEARBY TAMERS"),Make(TEXT("refresh")));
}

void UDigimonVenomNXTCommunityWidget::RefreshPartnerOptions()
{
    if(!Player.IsValid()||Section!=TEXT("Trading Center")) return;
    TArray<UComboBoxString*> Controls; if(ListingPartner) Controls.Add(ListingPartner); for(UComboBoxString* C:OfferPartners) if(C) Controls.Add(C);
    TArray<FGuid> Previous;
    for(UComboBoxString* C:Controls) { const FGuid* Id=PartnerOptions.Find(C->GetSelectedOption()); Previous.Add(Id?*Id:FGuid()); }
    PartnerOptions.Reset(); PartnerOptions.Add(TEXT("— No Digimon selected —"),FGuid());
    TArray<FString> Labels;
    for(const FDigimonOwnedPartner& P:Player->Profile.Collection)
    {
        if(Player->Profile.Party.Contains(P.InstanceId)||Player->Profile.DigiFarmResidents.Contains(P.InstanceId)||Player->Profile.Ranked.DefenderLineup.Contains(P.InstanceId)||
            Player->Profile.Ranked.DefenderTeam.ContainsByPredicate([&](const FDigimonOwnedPartner& Defender){ return Defender.InstanceId==P.InstanceId; })) continue;
        const FString Label=DigimonCommunityUI::PartnerName(P)+TEXT("  [")+P.InstanceId.ToString(EGuidFormats::Digits).Left(8)+TEXT("]");
        PartnerOptions.Add(Label,P.InstanceId); Labels.Add(Label);
    }
    Labels.Sort();
    for(int32 I=0; I<Controls.Num(); ++I)
    {
        UComboBoxString* C=Controls[I]; C->ClearOptions(); C->AddOption(TEXT("— No Digimon selected —"));
        FString Selection=TEXT("— No Digimon selected —");
        for(const FString& Label:Labels) { C->AddOption(Label); if(Previous[I].IsValid()&&PartnerOptions[Label]==Previous[I]) Selection=Label; }
        C->SetSelectedOption(Selection);
    }
}

void UDigimonVenomNXTCommunityWidget::RefreshTrading()
{
    using namespace DigimonCommunityUI;
    if(!Trade.IsValid()||!Player.IsValid()) { Card(TEXT("Connecting to the trading center")); return; }
    const FDigimonTradeView& V=Trade->View;
    Summary->SetText(FText::FromString(TEXT("YOUR BALANCE  •  ")+Price(Player->Profile.Credits,Player->Profile.DigiRubies)));
    if(!V.Status.IsEmpty()) ShowStatus(V.Status,V.bSuccess);
    if(V.PurchaseToken.IsValid()&&V.PurchaseToken!=SeenPurchaseToken)
    {
        SeenPurchaseToken=V.PurchaseToken;
        FAction A=Make(TEXT("purchase-confirm")); A.Id=V.PurchaseToken;
        const FDigimonTradeListing& L=V.PurchaseReview;
        Ask(A,TEXT("BUY THIS DIGIMON?"),FString::Printf(TEXT("You receive\n%s\nSpecies: %s\nCAM %d  •  ABI %d\n\nSeller: %s\n\nYou pay\n%s\n\nThe exact Digimon and the full price above are exchanged immediately when you confirm. The server checks availability and your balance again."),*PartnerName(L.Partner),*L.Partner.SpeciesId.ToString(),L.Partner.CAM,L.Partner.ABI,*L.SellerName,*Price(L.Credits,L.DigiRubies)));
    }
    if(Mode==TEXT("Market")||Mode==TEXT("My listings"))
    {
        VisibleForms.Add(TEXT("market-search"));
        if(V.bMineOnly!=(Mode==TEXT("My listings")) || V.Search!=SubmittedSearch)
        { Card(TEXT("UPDATING LISTINGS"),TEXT("Waiting for the world server to return your selected view.")); return; }
        Card(Mode==TEXT("My listings")?TEXT("YOUR ACTIVE LISTINGS"):TEXT("BUY NOW"),FString::Printf(TEXT("%d listings  •  Page %d  •  Prices may require money, digirubies, or both. Select a listing to review before buying."),V.TotalListings,V.Page+1));
        for(const FDigimonTradeListing& L:V.Listings)
        {
            UVerticalBox* C=Card(PartnerName(L.Partner),FString::Printf(TEXT("Seller: %s  •  Species: %s  •  CAM %d  •  ABI %d"),*L.SellerName,*L.Partner.SpeciesId.ToString(),L.Partner.CAM,L.Partner.ABI));
            Add(C,DigimonVenomNXTUI::AnimatedPortrait(WidgetTree,L.Partner.SpeciesId,L.Partner.Variant,90,90),2);
            Add(C,Text(WidgetTree,Price(L.Credits,L.DigiRubies),16,Gold));
            const bool bMine=L.SellerAccountId==Player->Profile.AccountId;
            FAction A=Make(bMine?TEXT("listing-cancel"):TEXT("purchase-review")); A.Id=L.ListingId; A.Text=PartnerName(L.Partner);
            const bool bAffordable=Player->Profile.Credits>=L.Credits&&Player->Profile.DigiRubies>=L.DigiRubies;
            AddAction(C,bMine?TEXT("CANCEL LISTING / RETURN DIGIMON"):bAffordable?TEXT("REVIEW & BUY NOW"):TEXT("INSUFFICIENT FUNDS"),A,bMine||bAffordable);
        }
        if(V.Listings.IsEmpty()) Card(TEXT("No listings found"),Mode==TEXT("My listings")?TEXT("Open Create listing to offer a Digimon from your collection."):TEXT("Try a different search, or be the first to create a listing."));
        FAction Prev=Make(TEXT("market-page")); Prev.Number=FMath::Max(0,V.Page-1); AddAction(Live,TEXT("PREVIOUS PAGE"),Prev,V.Page>0);
        FAction Next=Make(TEXT("market-page")); Next.Number=V.Page+1; AddAction(Live,TEXT("NEXT PAGE"),Next,(V.Page+1)*12<V.TotalListings);
    }
    else if(Mode==TEXT("Create listing"))
    {
        VisibleForms.Add(TEXT("listing"));
        if(PartnerOptions.Num()<=1) Card(TEXT("No trade-ready Digimon"),TEXT("Move a Digimon out of your active party, DigiFarm residents and ranked defense first. Keep at least one healthy partner in your active party."));
        Card(TEXT("YOUR LISTING, YOUR PRICE"),TEXT("The buyer pays every currency amount shown. Use zero for a currency you do not want. An active listing holds its Digimon safely, even if you log out; cancel it from My listings to return the partner."));
    }
    else
    {
        const FDigimonDirectTrade& S=V.Session;
        if(!S.SessionId.IsValid())
        {
            VisibleForms.Add(TEXT("trade-invite"));
            DisplayedSession.Invalidate(); DisplayedRevision=0;
            Card(TEXT("TRADE BY AGREEMENT"),TEXT("Invite a live tamer, then each of you chooses Digimon, money and/or digirubies to give. Both players must confirm the same offer revision. Either player can cancel before completion.")); return;
        }
        const bool bFirst=S.FirstAccountId==Player->Profile.AccountId;
        const FDigimonTradeOffer& Mine=bFirst?S.First:S.Second; const FDigimonTradeOffer& Theirs=bFirst?S.Second:S.First;
        const FString OtherName=bFirst?S.SecondName:S.FirstName;
        if(DisplayedSession!=S.SessionId)
        {
            DisplayedSession=S.SessionId; RefreshPartnerOptions();
            for(UComboBoxString* C:OfferPartners) C->SetSelectedIndex(0);
            Inputs[TEXT("offer-money")]->SetText(FText::FromString(TEXT("0"))); Inputs[TEXT("offer-rubies")]->SetText(FText::FromString(TEXT("0")));
        }
        DisplayedRevision=S.Revision;
        VisibleForms.Add(TEXT("trade-offer"));
        Card(FString::Printf(TEXT("TRADING WITH %s  •  REVISION %d"),*OtherName,S.Revision),TEXT("Only the submitted offers shown below are part of this exchange. Editing the form alone does not update your offer; press Update my offer to submit it."));
        auto Offer=[&](const FString& Title,const FDigimonTradeOffer& O)
        {
            UVerticalBox* C=Card(Title,Price(O.Credits,O.DigiRubies));
            for(const FDigimonOwnedPartner& P:O.Partners) Add(C,Text(WidgetTree,PartnerName(P)+FString::Printf(TEXT("  •  CAM %d / ABI %d"),P.CAM,P.ABI),14));
            if(O.Partners.IsEmpty()) Add(C,Text(WidgetTree,TEXT("No Digimon in this offer"),13,Muted));
            Add(C,Text(WidgetTree,O.bConfirmed?TEXT("CONFIRMED THIS REVISION"):TEXT("AWAITING CONFIRMATION"),12,O.bConfirmed?Cyan:Gold));
        };
        Offer(TEXT("YOU GIVE"),Mine); Offer(TEXT("YOU RECEIVE"),Theirs);
        FAction Confirm=Make(TEXT("trade-review")); Confirm.Id=S.SessionId; Confirm.Revision=S.Revision;
        AddAction(Live,Mine.bConfirmed?TEXT("WAITING FOR THEIR CONFIRMATION"):TEXT("REVIEW FULL EXCHANGE & CONFIRM"),Confirm,!Mine.bConfirmed);
        FAction Cancel=Make(TEXT("trade-cancel")); Cancel.Id=S.SessionId; AddAction(Live,TEXT("CANCEL THIS TRADE"),Cancel);
    }
}

void UDigimonVenomNXTCommunityWidget::Ask(const FAction& A,const FString& Title,const FString& Message)
{
    PendingAction=A; ExpectedConfirmationName.Reset();
    const bool bTyped=A.Kind==TEXT("clan-disband")||A.Kind==TEXT("clan-transfer");
    if(bTyped&&Social.IsValid()) ExpectedConfirmationName=Social->State.Clan.Name;
    ConfirmationName->SetText(FText::GetEmpty()); ConfirmationName->SetError(FText::GetEmpty());
    ConfirmationName->SetVisibility(bTyped?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
    ConfirmationName->SetHintText(FText::FromString(TEXT("Type exactly: ")+ExpectedConfirmationName));
    ConfirmationTitle->SetText(FText::FromString(Title)); ConfirmationText->SetText(FText::FromString(Message));
    Confirmation->SetVisibility(ESlateVisibility::Visible); Body->SetIsEnabled(false); ConfirmationButton->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTCommunityWidget::HandleAction(const FString& Action,int32 Payload)
{
    const FAction* Found=Actions.Find(Payload); if(!Found) return;
    const FAction A=*Found;
    if(A.Kind==TEXT("cancel-confirm")) { HandleBack(); return; }
    if(A.Kind==TEXT("confirm"))
    {
        FAction Confirmed=PendingAction;
        if(!ExpectedConfirmationName.IsEmpty())
        {
            Confirmed.Text=ConfirmationName->GetText().ToString();
            if(Confirmed.Text!=ExpectedConfirmationName) { ConfirmationName->SetError(FText::FromString(TEXT("Enter the exact clan name to continue."))); ConfirmationName->SetUserFocus(GetOwningPlayer()); return; }
        }
        HandleBack(); Execute(Confirmed); return;
    }
    if(A.Kind==TEXT("mode")) { BrowsePage=0; SetMode(A.Target); RequestRefresh(); return; }
    if(A.Kind==TEXT("refresh")) { RequestRefresh(); return; }
    const bool bDestructive=A.Kind==TEXT("friend-remove")||A.Kind==TEXT("ignore-add")||A.Kind==TEXT("clan-kick")||A.Kind==TEXT("clan-transfer")||A.Kind==TEXT("clan-disband")||A.Kind==TEXT("clan-leave")||A.Kind==TEXT("listing-cancel");
    if(bDestructive)
    {
        FAction Confirmed=A; Confirmed.Extra=TEXT("confirmed");
        FString Message=TEXT("Please confirm this account action.");
        if(A.Kind==TEXT("friend-remove")) Message=TEXT("Remove this tamer from your friends? They will also lose this friendship. You can send a new request later.");
        if(A.Kind==TEXT("ignore-add")) Message=TEXT("Ignore this tamer? Their chat will be hidden and new social invitations from them will be blocked. You can stop ignoring them from the Ignored tab.");
        if(A.Kind==TEXT("clan-kick")) Message=TEXT("Remove this member from your clan? They will lose access to clan chat and the live roster.");
        if(A.Kind==TEXT("clan-transfer")) Message=TEXT("Transfer your clan leadership to this member? They will control the clan and its membership.");
        if(A.Kind==TEXT("clan-disband")) Message=TEXT("Permanently disband your clan? Every member will be removed and the clan will be deleted. This cannot be undone.");
        if(A.Kind==TEXT("clan-leave")) Message=TEXT("Leave your clan? You will lose access to its chat and live roster.");
        if(A.Kind==TEXT("listing-cancel")) Message=TEXT("Cancel the listing for ")+A.Text+TEXT("? The Digimon will return to your collection if this listing has not already sold.");
        Ask(Confirmed,TEXT("CONFIRM YOUR CHOICE"),Message); return;
    }
    Execute(A);
}

void UDigimonVenomNXTCommunityWidget::Execute(const FAction& A)
{
    using namespace DigimonCommunityUI;
    Bind();
    if(A.Kind==TEXT("open-profile")||A.Kind==TEXT("open-trade"))
    {
        FString Display=A.Target;
        if(Social.IsValid())
        {
            for(const FDigimonSocialContact& P:Social->State.Friends) if(P.AccountId==A.Target) Display=P.Username;
            for(const FDigimonClanMemberView& M:Social->State.Clan.Members) if(M.Player.AccountId==A.Target) Display=M.Player.Username;
            if(Social->State.PlayerInfo.bValid&&Social->State.PlayerInfo.Player.AccountId==A.Target) Display=Social->State.PlayerInfo.Player.Username;
        }
        if(ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) if(UDigimonVenomNXTGameHUDWidget* HUD=PC->GetNativeHUDWidget()) { HUD->OpenCommunityTarget(A.Target,Display,false,A.Kind==TEXT("open-profile")?TEXT("Social"):TEXT("Trading Center")); }
        return;
    }
    if(A.Kind==TEXT("find")||A.Kind==TEXT("profile"))
    {
        const FString Target=A.Kind==TEXT("find")?Value(TEXT("target")):A.Target;
        if(Target.IsEmpty()) { ShowStatus(TEXT("Enter an exact tamer username first."),false); return; }
        bTargetRival=false; TargetAccount=Target; SetMode(TEXT("Player info")); if(Social.IsValid()) Social->ServerRequestPlayerInfo(Target); return;
    }
    if(A.Kind==TEXT("friend-request-input")||A.Kind==TEXT("ignore-input"))
    {
        const FString Target=Value(TEXT("target")); if(Target.IsEmpty()) { ShowStatus(TEXT("Enter a tamer username first."),false); return; }
        FAction New=Make(A.Kind==TEXT("ignore-input")?TEXT("ignore-add"):TEXT("friend-request"),Target);
        if(A.Kind==TEXT("ignore-input")) Ask(New,TEXT("IGNORE THIS USER?"),TEXT("Ignore ")+Target+TEXT("? Their chat will be hidden and new invitations blocked. You can reverse this in the Ignored tab.")); else Execute(New); return;
    }
    static const TMap<FString,EDigimonSocialAction> SocialActions={
        {TEXT("friend-request"),EDigimonSocialAction::FriendRequest},{TEXT("friend-accept"),EDigimonSocialAction::FriendAccept},{TEXT("friend-decline"),EDigimonSocialAction::FriendDecline},{TEXT("friend-remove"),EDigimonSocialAction::FriendRemove},{TEXT("friend-cancel"),EDigimonSocialAction::FriendCancel},
        {TEXT("ignore-add"),EDigimonSocialAction::IgnoreAdd},{TEXT("ignore-remove"),EDigimonSocialAction::IgnoreRemove},
        {TEXT("clan-accept"),EDigimonSocialAction::ClanAccept},{TEXT("clan-decline"),EDigimonSocialAction::ClanDecline},{TEXT("clan-leave"),EDigimonSocialAction::ClanLeave},{TEXT("clan-kick"),EDigimonSocialAction::ClanKick},{TEXT("clan-promote"),EDigimonSocialAction::ClanPromote},{TEXT("clan-demote"),EDigimonSocialAction::ClanDemote},{TEXT("clan-transfer"),EDigimonSocialAction::ClanTransfer},{TEXT("clan-disband"),EDigimonSocialAction::ClanDisband},{TEXT("clan-invite-target"),EDigimonSocialAction::ClanInvite}};
    if(const EDigimonSocialAction* Kind=SocialActions.Find(A.Kind))
    {
        if(Social.IsValid()) { const FString ConfirmName=(*Kind==EDigimonSocialAction::ClanDisband||*Kind==EDigimonSocialAction::ClanTransfer)?A.Text:FString(); Social->ServerSocialAction(*Kind,A.Target,ConfirmName,TEXT("")); ShowStatus(TEXT("Request sent to the world server…")); } return;
    }
    if(A.Kind.StartsWith(TEXT("clan-"))&&Social.IsValid())
    {
        if(A.Kind==TEXT("clan-create")) Social->ServerSocialAction(EDigimonSocialAction::ClanCreate,Value(TEXT("clan-name")),Value(TEXT("clan-tag")),Value(TEXT("clan-description")));
        else if(A.Kind==TEXT("clan-update")) Social->ServerSocialAction(EDigimonSocialAction::ClanUpdate,Social->State.Clan.ClanId,Value(TEXT("motd")),Value(TEXT("description")));
        else if(A.Kind==TEXT("clan-invite")) Social->ServerSocialAction(EDigimonSocialAction::ClanInvite,Value(TEXT("invite")),TEXT(""),TEXT(""));
        else if(A.Kind==TEXT("clan-chat")) { const FString Message=Value(TEXT("chat")); if(!Message.IsEmpty()) { Social->ServerSendClanChat(Message); Inputs[TEXT("chat")]->SetText(FText::GetEmpty()); } }
        return;
    }
    if(A.Kind.StartsWith(TEXT("challenge-"))&&Unranked.IsValid())
    {
        if(A.Kind==TEXT("challenge-player")) Unranked->ServerChallengePlayer(A.Target);
        else if(A.Kind==TEXT("challenge-rival")) Unranked->ServerChallengeRival(A.Target);
        else if(A.Kind==TEXT("challenge-cancel")) Unranked->ServerCancel(A.Id);
        else Unranked->ServerRespond(A.Id,A.Kind==TEXT("challenge-accept"));
        if(Section!=TEXT("Unranked")) if(ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer())) if(UDigimonVenomNXTGameHUDWidget* HUD=PC->GetNativeHUDWidget()) HUD->OpenCommunityTarget(A.Target,A.Target,A.Kind==TEXT("challenge-rival"),TEXT("Unranked"));
        return;
    }
    if(!Trade.IsValid()) return;
    if(A.Kind==TEXT("search")||A.Kind==TEXT("market-page")) { if(A.Kind==TEXT("search")) SubmittedSearch=Value(TEXT("search")).Left(64).TrimStartAndEnd(); BrowsePage=A.Kind==TEXT("search")?0:A.Number; RequestRefresh(); return; }
    if(A.Kind==TEXT("purchase-review")) { Trade->ServerReviewPurchase(A.Id); ShowStatus(TEXT("Requesting the current listing and price…")); return; }
    if(A.Kind==TEXT("purchase-confirm")) { Trade->ServerConfirmPurchase(A.Id); return; }
    if(A.Kind==TEXT("listing-cancel")) { Trade->ServerCancelListing(A.Id); return; }
    if(A.Kind==TEXT("listing-review"))
    {
        FAction Listing=Make(TEXT("listing-create")); if(!ReadPrice(TEXT("listing"),Listing.Credits,Listing.Rubies)) return;
        const FGuid* Id=ListingPartner?PartnerOptions.Find(ListingPartner->GetSelectedOption()):nullptr;
        if(!Id||!Id->IsValid()) { ShowStatus(TEXT("Choose a Digimon before creating a listing."),false); return; }
        if(Listing.Credits==0&&Listing.Rubies==0) { ShowStatus(TEXT("A listing needs a price in money, digirubies, or both."),false); return; }
        Listing.Id=*Id; Ask(Listing,TEXT("PUBLISH THIS LISTING?"),ListingPartner->GetSelectedOption()+TEXT("\n\nBuyer pays: ")+Price(Listing.Credits,Listing.Rubies)+TEXT("\n\nThis Digimon leaves your collection while listed. You can cancel an unsold listing from My listings.")); return;
    }
    if(A.Kind==TEXT("listing-create")) { Trade->ServerCreateListing(A.Id,A.Credits,A.Rubies); SetMode(TEXT("My listings")); return; }
    if(A.Kind==TEXT("trade-invite")) { const FString Name=Value(TEXT("trade-target")); if(Name.IsEmpty()) { ShowStatus(TEXT("Enter the live tamer's username first."),false); return; } Trade->ServerInviteTrade(Name); return; }
    if(A.Kind==TEXT("offer-update"))
    {
        if(!Trade->View.Session.SessionId.IsValid()) return;
        int64 Credits; int32 Rubies; if(!ReadPrice(TEXT("offer"),Credits,Rubies)) return;
        TArray<FGuid> Ids;
        for(UComboBoxString* C:OfferPartners) if(const FGuid* Id=PartnerOptions.Find(C->GetSelectedOption())) if(Id->IsValid()) { if(Ids.Contains(*Id)) { ShowStatus(TEXT("A Digimon can only appear once in your offer."),false); return; } Ids.Add(*Id); }
        if(Player.IsValid()&&(Credits>Player->Profile.Credits||Rubies>Player->Profile.DigiRubies)) { ShowStatus(TEXT("Your offer exceeds your available balance."),false); return; }
        Trade->ServerUpdateOffer(DisplayedSession,DisplayedRevision,Ids,Credits,Rubies); return;
    }
    if(A.Kind==TEXT("trade-review"))
    {
        const FDigimonDirectTrade& S=Trade->View.Session;
        if(S.SessionId!=A.Id||S.Revision!=A.Revision) { ShowStatus(TEXT("The trade changed. Review the latest offer before confirming."),false); return; }
        const bool bFirst=Player.IsValid()&&Player->Profile.AccountId==S.FirstAccountId;
        auto Describe=[](const FDigimonTradeOffer& O) { FString T=Price(O.Credits,O.DigiRubies); for(const FDigimonOwnedPartner& P:O.Partners) T+=TEXT("\n")+PartnerName(P); return T; };
        FAction Confirm=A; Confirm.Kind=TEXT("trade-confirm");
        Ask(Confirm,FString::Printf(TEXT("CONFIRM TRADE — REVISION %d"),S.Revision),TEXT("YOU GIVE\n")+Describe(bFirst?S.First:S.Second)+TEXT("\n\nYOU RECEIVE\n")+Describe(bFirst?S.Second:S.First)+TEXT("\n\nBoth players must confirm this exact exchange. Once both confirm, the exchange is final. If either offer changes, you must review and confirm again.")); return;
    }
    if(A.Kind==TEXT("trade-confirm")) { Trade->ServerConfirmTrade(A.Id,A.Revision); return; }
    if(A.Kind==TEXT("trade-cancel")) { Trade->ServerCancelTrade(A.Id); return; }
}

void UDigimonVenomNXTCommunityWidget::ReviewIgnoreTarget(const FString& TargetId, const FString& Name)
{
    bool bIgnored=false;
    if(Social.IsValid()) for(const FDigimonSocialContact& P:Social->State.Ignored) if(P.AccountId==TargetId) bIgnored=true;
    Ask(Make(bIgnored?TEXT("ignore-remove"):TEXT("ignore-add"),TargetId),bIgnored?TEXT("STOP IGNORING THIS USER?"):TEXT("IGNORE THIS USER?"),
        bIgnored ? TEXT("Stop ignoring ")+Name+TEXT("? Their future chat and social invitations will become available again.") : TEXT("Ignore ")+Name+TEXT("? Their chat will be hidden and new invitations blocked. You can reverse this in the Ignored tab."));
}
