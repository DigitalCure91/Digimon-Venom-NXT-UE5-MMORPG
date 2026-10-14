#include "DigimonVenomNXTSeasonWidget.h"
#include "DigimonVenomNXTCombatUI.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTSeason.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Texture2D.h"

namespace DigimonSeasonUI
{
    constexpr int32 RosterPageSize = 8;
    constexpr int32 RivalryPageSize = 6;
    constexpr int32 ArchivePageSize = 8;
    const FLinearColor Ink(0.008f,0.020f,0.043f,1);
    const FLinearColor Panel(0.014f,0.040f,0.066f,0.98f);
    const FLinearColor Cyan(0.13f,0.86f,0.98f,1);
    const FLinearColor Gold(1.0f,0.74f,0.27f,1);
    const FLinearColor White(0.93f,0.98f,1,1);
    const FLinearColor Muted(0.58f,0.72f,0.84f,1);
    const FLinearColor Green(0.63f,0.96f,0.38f,1);
    const FLinearColor Red(1.0f,0.44f,0.49f,1);

    UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size=13, FLinearColor Color=White, bool bBold=false)
    {
        UTextBlock* W=Tree->ConstructWidget<UTextBlock>(); W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font=W->GetFont(); Font.Size=Size; Font.TypefaceFontName=bBold?FName(TEXT("Bold")):FName(TEXT("Regular")); W->SetFont(Font); return W;
    }
    void Set(UTextBlock* W,const FString& Value) { if(W) W->SetText(FText::FromString(Value)); }
    void Add(UVerticalBox* Box,UWidget* W,float Pad=3)
    {
        if(UVerticalBoxSlot* S=Box->AddChildToVerticalBox(W)) { S->SetPadding(FMargin(0,Pad)); S->SetHorizontalAlignment(HAlign_Fill); }
    }
    void Row(UHorizontalBox* Box,UWidget* W,float Weight=1,float Pad=4)
    {
        if(UHorizontalBoxSlot* S=Box->AddChildToHorizontalBox(W)) { S->SetPadding(FMargin(Pad,0)); S->SetVerticalAlignment(VAlign_Center); if(Weight>0) { FSlateChildSize Size(ESlateSizeRule::Fill); Size.Value=Weight; S->SetSize(Size); } }
    }
    USizeBox* Width(UWidgetTree* Tree,UWidget* W,float Value) { USizeBox* B=Tree->ConstructWidget<USizeBox>(); B->SetWidthOverride(Value); B->AddChild(W); return B; }
    UBorder* Card(UWidgetTree* Tree,FLinearColor Accent=Cyan,float Pad=12)
    {
        UBorder* B=Tree->ConstructWidget<UBorder>(); B->SetBrush(FSlateRoundedBoxBrush(Panel,7.0f,Accent.CopyWithNewOpacity(0.42f),1)); B->SetPadding(FMargin(Pad)); return B;
    }
    UVerticalBox* Section(UWidgetTree* Tree,UVerticalBox* Parent,const FString& Title,FLinearColor Accent=Cyan)
    {
        UBorder* Border=Card(Tree,Accent); Add(Parent,Border,5); UVerticalBox* Body=Tree->ConstructWidget<UVerticalBox>(); Border->SetContent(Body); Add(Body,Text(Tree,Title,12,Accent,true),3); return Body;
    }
    USizeBox* Portrait(UWidgetTree* Tree,UDigimonVenomNXTAnimatedPortrait*& Out,float Size)
    {
        USizeBox* B=Tree->ConstructWidget<USizeBox>(); B->SetWidthOverride(Size); B->SetHeightOverride(Size); Out=Tree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>(); B->AddChild(Out); return B;
    }
    USizeBox* Tamer(UWidgetTree* Tree,UImage*& Out,float Size)
    {
        USizeBox* B=Tree->ConstructWidget<USizeBox>(); B->SetWidthOverride(Size); B->SetHeightOverride(Size);
        UScaleBox* Fit=Tree->ConstructWidget<UScaleBox>(); Fit->SetStretch(EStretch::ScaleToFit); B->AddChild(Fit); Out=Tree->ConstructWidget<UImage>(); Fit->AddChild(Out); return B;
    }
    void SetTamer(UImage* Image,FName Style)
    {
        if(!Image)return;
        const FString Path=DigimonVenomNXTTamers::ThumbnailPath(Style);
        UTexture2D* Texture=Path.IsEmpty()?nullptr:LoadObject<UTexture2D>(nullptr,*Path,nullptr,LOAD_NoWarn | LOAD_Quiet);
        Image->SetBrushFromTexture(Texture,true); Image->SetVisibility(Texture?ESlateVisibility::HitTestInvisible:ESlateVisibility::Hidden);
    }
    UProgressBar* Meter(UWidgetTree* Tree,UVerticalBox* Parent,FLinearColor Color)
    {
        UProgressBar* Bar=Tree->ConstructWidget<UProgressBar>(); Bar->SetFillColorAndOpacity(Color); FProgressBarStyle Style=Bar->GetWidgetStyle(); Style.SetBackgroundImage(FSlateRoundedBoxBrush(Ink,3.0f)); Style.SetFillImage(FSlateRoundedBoxBrush(FLinearColor::White,3.0f)); Bar->SetWidgetStyle(Style);
        USizeBox* Bounds=Tree->ConstructWidget<USizeBox>(); Bounds->SetHeightOverride(7); Bounds->AddChild(Bar); Add(Parent,Bounds,5); return Bar;
    }
    void SingleLine(UTextBlock* Text) { Text->SetAutoWrapText(false); Text->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis); }
    void Caption(UDigimonVenomNXTActionButton* Button,const FString& Value) { if(Button) Set(Cast<UTextBlock>(Button->GetContent()),Value); }
}

TSharedRef<SWidget> UDigimonVenomNXTSeasonWidget::RebuildWidget() { BuildLayout(); return Super::RebuildWidget(); }

UDigimonVenomNXTActionButton* UDigimonVenomNXTSeasonWidget::Button(const FString& Label,const FString& Action,FLinearColor Accent)
{
    UDigimonVenomNXTActionButton* B=WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>(); DigimonVenomNXTUI::StyleButton(B,Accent); B->InitializeAction(Action);
    B->OnAction.AddDynamic(this,&UDigimonVenomNXTSeasonWidget::HandleAction); UTextBlock* T=DigimonSeasonUI::Text(WidgetTree,Label,12,DigimonSeasonUI::White,true); T->SetJustification(ETextJustify::Center); B->SetContent(T); return B;
}

UVerticalBox* UDigimonVenomNXTSeasonWidget::BuildTeam(UVerticalBox* Parent,TArray<FDigimonSeasonPartnerView>& Views,bool bDetailed)
{
    using namespace DigimonSeasonUI;
    UVerticalBox* Body=WidgetTree->ConstructWidget<UVerticalBox>(); Add(Parent,Body,0);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(3)); Add(Body,Grid,0);
    // Twelve bounded cells cover the full supported party limit; unused cells collapse.
    for(int32 Index=0;Index<12;++Index)
    {
        FDigimonSeasonPartnerView V; V.Card=Card(WidgetTree,Cyan,bDetailed?9:4); UVerticalBox* Cell=WidgetTree->ConstructWidget<UVerticalBox>(); V.Card->SetContent(Cell);
        UDigimonVenomNXTAnimatedPortrait* P=nullptr; USizeBox* PortraitBox=Portrait(WidgetTree,P,bDetailed?82:54); V.Portrait=P;
        if(UVerticalBoxSlot* S=Cell->AddChildToVerticalBox(PortraitBox)) S->SetHorizontalAlignment(HAlign_Center);
        V.Name=Text(WidgetTree,TEXT(""),bDetailed?13:11,White,true); SingleLine(V.Name); V.Name->SetJustification(ETextJustify::Center); Add(Cell,V.Name,1);
        V.Stats=Text(WidgetTree,TEXT(""),bDetailed?12:10,Muted); V.Stats->SetJustification(ETextJustify::Center); Add(Cell,V.Stats,2);
        V.Bounds=WidgetTree->ConstructWidget<USizeBox>(); V.Bounds->SetWidthOverride(bDetailed?250.0f:92.0f); V.Bounds->AddChild(V.Card);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(V.Bounds,Index/3,Index%3)) S->SetHorizontalAlignment(HAlign_Fill);
        Views.Add(V);
    }
    return Body;
}

void UDigimonVenomNXTSeasonWidget::BuildMatchCard(UVerticalBox* Parent,TArray<FDigimonSeasonMatchView>& Views)
{
    using namespace DigimonSeasonUI;
    for(int32 Index=0;Index<8;++Index)
    {
        FDigimonSeasonMatchView V; V.Card=Card(WidgetTree,Cyan,8); Add(Parent,V.Card,2); UHorizontalBox* R=WidgetTree->ConstructWidget<UHorizontalBox>(); V.Card->SetContent(R);
        V.Day=Text(WidgetTree,TEXT(""),10,Muted,true); Row(R,Width(WidgetTree,V.Day,30),0,1);
        V.Home=Text(WidgetTree,TEXT(""),12,White,true); SingleLine(V.Home); Row(R,V.Home);
        Row(R,Text(WidgetTree,TEXT("VS"),9,Muted),0,4);
        V.Away=Text(WidgetTree,TEXT(""),12,White,true); SingleLine(V.Away); Row(R,V.Away);
        V.Result=Text(WidgetTree,TEXT(""),9,Muted,true); V.Result->SetJustification(ETextJustify::Right); Row(R,Width(WidgetTree,V.Result,58),0,1); Views.Add(V);
    }
}

void UDigimonVenomNXTSeasonWidget::BuildLayout()
{
    if(Root)return;
    if(!WidgetTree)WidgetTree=NewObject<UWidgetTree>(this,TEXT("SeasonWidgetTree"));
    using namespace DigimonSeasonUI;
    Root=WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget=Root;
    UBorder* Header=Card(WidgetTree,Cyan,0); Add(Root,Header,0); UOverlay* HeaderOverlay=WidgetTree->ConstructWidget<UOverlay>(); Header->SetContent(HeaderOverlay);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree,HeaderOverlay,nullptr,FLinearColor(0.002f,0.01f,0.025f,0.28f));
    UHorizontalBox* HeaderRow=WidgetTree->ConstructWidget<UHorizontalBox>();
    if(UOverlaySlot* S=HeaderOverlay->AddChildToOverlay(HeaderRow)) S->SetPadding(FMargin(18,17));
    UVerticalBox* HeaderText=WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeaderRow,HeaderText,1,0);
    Add(HeaderText,Text(WidgetTree,TEXT("DIGIMON VENOM NXT  /  PRIVATE SOLO LEAGUE"),11,Cyan,true),2);
    Add(HeaderText,Text(WidgetTree,TEXT("YOUR TAMER CAREER"),27,White,true),2);
    Calendar=Text(WidgetTree,TEXT("Synchronizing your private league..."),12,Muted); Add(HeaderText,Calendar,3);
    UVerticalBox* HeaderRight=WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeaderRow,Width(WidgetTree,HeaderRight,200),0,5);
    Add(HeaderRight,Text(WidgetTree,TEXT("WORLD CIRCUIT"),15,Gold,true),5);
    Add(HeaderRight,Button(TEXT("SAVE & RETURN TO WORLD"),TEXT("seasonreturn"),Cyan),3);
    UHorizontalBox* TabRow=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root,TabRow,9);
    const TCHAR* Names[]={TEXT("THIS WEEK"),TEXT("ROSTER & RANKINGS"),TEXT("RIVALRIES"),TEXT("CHAMPIONSHIP"),TEXT("CAREER ARCHIVE")};
    for(int32 I=0;I<5;++I) { UDigimonVenomNXTActionButton* B=Button(Names[I],TEXT("seasontab"),I==3?Gold:Cyan); B->InitializeAction(TEXT("seasontab"),I); Row(TabRow,B,1,3); Tabs.Add(B); }
    Pages=WidgetTree->ConstructWidget<UWidgetSwitcher>(); Add(Root,Pages,0);

    UHorizontalBox* Week=WidgetTree->ConstructWidget<UHorizontalBox>(); Pages->AddChild(Week);
    UVerticalBox* Main=WidgetTree->ConstructWidget<UVerticalBox>(); Row(Week,Main,1,0);
    UVerticalBox* Side=WidgetTree->ConstructWidget<UVerticalBox>(); Row(Week,Width(WidgetTree,Side,220),0,6);
    if(UHorizontalBoxSlot* S=Cast<UHorizontalBoxSlot>(Main->Slot)) S->SetVerticalAlignment(VAlign_Top);
    if(UHorizontalBoxSlot* S=Cast<UHorizontalBoxSlot>(Side->GetParent()->Slot)) S->SetVerticalAlignment(VAlign_Top);
    UBorder* Hero=Card(WidgetTree,Cyan,14); Add(Main,Hero,3); UVerticalBox* HeroBody=WidgetTree->ConstructWidget<UVerticalBox>(); Hero->SetContent(HeroBody);
    MatchKicker=Text(WidgetTree,TEXT("THIS WEEK / YOUR MATCH"),10,Gold,true); Add(HeroBody,MatchKicker,2);
    MatchTitle=Text(WidgetTree,TEXT("World Circuit"),22,White,true); Add(HeroBody,MatchTitle,2);
    MatchDetail=Text(WidgetTree,TEXT(""),12,Muted); Add(HeroBody,MatchDetail,2);
    UHorizontalBox* MatchCommands=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody,MatchCommands,5);
    MatchOutcome=Text(WidgetTree,TEXT(""),12,Green,true); Row(MatchCommands,MatchOutcome);
    MatchAction=Button(TEXT("START THIS WEEK'S MATCH"),TEXT("seasonmatch"),Cyan); Row(MatchCommands,MatchAction,1,0);
    UHorizontalBox* Teams=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(HeroBody,Teams,5);
    auto AddTeamHeader=[&](UVerticalBox* Body,UImage*& TamerImage,UTextBlock*& Name,UTextBlock*& Summary)
    {
        UHorizontalBox* NameRow=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Body,NameRow,4);
        Row(NameRow,Tamer(WidgetTree,TamerImage,48),0,1); Name=Text(WidgetTree,TEXT(""),15,Cyan,true); SingleLine(Name); Row(NameRow,Name);
        Summary=Text(WidgetTree,TEXT(""),11,Muted); Add(Body,Summary,2);
    };
    UVerticalBox* Home=WidgetTree->ConstructWidget<UVerticalBox>(); Row(Teams,Home,1,0);
    UImage* HomeTamer=nullptr; UTextBlock* HomeName=nullptr; UTextBlock* HomeSummary=nullptr; AddTeamHeader(Home,HomeTamer,HomeName,HomeSummary); PlayerTamer=HomeTamer; PlayerName=HomeName; PlayerTeamSummary=HomeSummary;
    BuildTeam(Home,PlayerTeam,false);
    UTextBlock* VS=Text(WidgetTree,TEXT("VS"),13,Gold,true); Row(Teams,VS,0,5);
    UVerticalBox* Away=WidgetTree->ConstructWidget<UVerticalBox>(); Row(Teams,Away,1,0);
    UImage* AwayTamer=nullptr; UTextBlock* AwayName=nullptr; UTextBlock* AwaySummary=nullptr; AddTeamHeader(Away,AwayTamer,AwayName,AwaySummary); OpponentTamer=AwayTamer; OpponentName=AwayName; OpponentTeamSummary=AwaySummary;
    BuildTeam(Away,OpponentTeam,false);
    Add(HeroBody,Text(WidgetTree,TEXT("Your real party enters at its current levels and stats. Victories award partner EXP and credits."),11,Muted),3);
    UVerticalBox* Matches=Section(WidgetTree,Main,TEXT("MATCH CARD  /  ALL 16 TAMERS")); BuildMatchCard(Matches,WeekMatches);
    UVerticalBox* Champion=Section(WidgetTree,Side,TEXT("WORLD CHAMPION"),Gold); UDigimonVenomNXTAnimatedPortrait* CP=nullptr; USizeBox* CPBox=Portrait(WidgetTree,CP,76); ChampionPortrait=CP;
    if(UVerticalBoxSlot* S=Champion->AddChildToVerticalBox(CPBox)) S->SetHorizontalAlignment(HAlign_Center);
    ChampionName=Text(WidgetTree,TEXT(""),18,White,true); Add(Champion,ChampionName,3); ChampionDetails=Text(WidgetTree,TEXT(""),12,Muted); Add(Champion,ChampionDetails,3);
    UVerticalBox* Career=Section(WidgetTree,Side,TEXT("YOUR CAREER")); CareerRecord=Text(WidgetTree,TEXT(""),24,White,true); Add(Career,CareerRecord,3); Add(Career,Text(WidgetTree,TEXT("WINS / LOSSES"),10,Muted,true),1); CareerRank=Text(WidgetTree,TEXT(""),14,Cyan,true); Add(Career,CareerRank,2); CareerTitles=Text(WidgetTree,TEXT(""),13,Gold); Add(Career,CareerTitles,2); CareerIncome=Text(WidgetTree,TEXT(""),12,Muted); Add(Career,CareerIncome,3);
    UVerticalBox* News=Section(WidgetTree,Side,TEXT("LEAGUE FREQUENCY")); LeagueNews=Text(WidgetTree,TEXT(""),12,Muted); Add(News,LeagueNews,4);

    UVerticalBox* Roster=WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(Roster);
    Add(Roster,Text(WidgetTree,TEXT("THE COMPETING ROSTER"),19,Cyan,true),2); Add(Roster,Text(WidgetTree,TEXT("All records belong to your private league. Select a tamer to inspect every partner and its real combat stats."),12,Muted),3);
    auto Pager=[&](UVerticalBox* Parent,const FString& Command,UDigimonVenomNXTActionButton*& Previous,UTextBlock*& Label,UDigimonVenomNXTActionButton*& Next)
    {
        UHorizontalBox* R=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Parent,R,5); Previous=Button(TEXT("PREVIOUS"),Command,Cyan); Row(R,Previous,0);
        Label=Text(WidgetTree,TEXT(""),12,Muted,true); Label->SetJustification(ETextJustify::Center); Row(R,Label);
        Next=Button(TEXT("NEXT"),Command,Cyan); Row(R,Next,0);
    };
    UDigimonVenomNXTActionButton* Prev=nullptr; UDigimonVenomNXTActionButton* Next=nullptr; UTextBlock* PageLabel=nullptr;
    Pager(Roster,TEXT("seasonrosterpage"),Prev,PageLabel,Next); RosterPrevious=Prev; RosterPager=PageLabel; RosterNext=Next;
    for(int32 I=0;I<RosterPageSize;++I)
    {
        FDigimonSeasonRosterView V; V.Button=Button(TEXT(""),TEXT("seasontamer"),Cyan); Add(Roster,V.Button,2);
        UHorizontalBox* R=WidgetTree->ConstructWidget<UHorizontalBox>(); V.Button->SetContent(R);
        V.Rank=Text(WidgetTree,TEXT(""),19,Gold,true); Row(R,Width(WidgetTree,V.Rank,35),0);
        UImage* TI=nullptr; Row(R,Tamer(WidgetTree,TI,34),0,0); V.Tamer=TI;
        UDigimonVenomNXTAnimatedPortrait* P=nullptr; Row(R,Portrait(WidgetTree,P,42),0,2); V.Portrait=P;
        V.Name=Text(WidgetTree,TEXT(""),14,White,true); SingleLine(V.Name); Row(R,V.Name,1.0f);
        V.Record=Text(WidgetTree,TEXT(""),12,Muted); Row(R,V.Record,0.85f);
        V.Progress=Text(WidgetTree,TEXT(""),12,Muted); Row(R,V.Progress,0.8f); RosterRows.Add(V);
    }
    UVerticalBox* Inspector=Section(WidgetTree,Roster,TEXT("TAMER DOSSIER  /  COMPLETE PARTY"),Gold);
    SelectedTamerName=Text(WidgetTree,TEXT(""),22,White,true); Add(Inspector,SelectedTamerName,2); SelectedTamerRecord=Text(WidgetTree,TEXT(""),12,Muted); Add(Inspector,SelectedTamerRecord,4); BuildTeam(Inspector,SelectedTeam,true);

    UVerticalBox* Rivalries=WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(Rivalries);
    Add(Rivalries,Text(WidgetTree,TEXT("RIVALRY SIGNALS"),19,Cyan,true),2); Add(Rivalries,Text(WidgetTree,TEXT("Repeated clashes build shared history. Your rivalries continue across weeks, months and years."),12,Muted),3);
    Pager(Rivalries,TEXT("seasonrivalrypage"),Prev,PageLabel,Next); RivalryPrevious=Prev; RivalryPager=PageLabel; RivalryNext=Next;
    RivalryEmpty=Text(WidgetTree,TEXT("Your first rival is waiting on the match card."),17,White,true); Add(Rivalries,RivalryEmpty,12);
    UUniformGridPanel* RivalsGrid=WidgetTree->ConstructWidget<UUniformGridPanel>(); RivalsGrid->SetSlotPadding(FMargin(4)); Add(Rivalries,RivalsGrid,0);
    for(int32 I=0;I<RivalryPageSize;++I)
    {
        FDigimonSeasonRivalryView V; V.Card=Card(WidgetTree,Cyan,16); UVerticalBox* B=WidgetTree->ConstructWidget<UVerticalBox>(); V.Card->SetContent(B);
        V.Names=Text(WidgetTree,TEXT(""),16,White,true); Add(B,V.Names,3); V.Record=Text(WidgetTree,TEXT(""),12,Muted); Add(B,V.Record,6); V.Status=Text(WidgetTree,TEXT(""),12,Cyan,true); Add(B,V.Status,3); V.Heat=Meter(WidgetTree,B,Cyan);
        if(UUniformGridSlot* S=RivalsGrid->AddChildToUniformGrid(V.Card,I/2,I%2)) S->SetHorizontalAlignment(HAlign_Fill); RivalryCards.Add(V);
    }

    UVerticalBox* Titles=WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(Titles);
    UVerticalBox* TitleHero=Section(WidgetTree,Titles,TEXT("SOLO SEASON  /  WORLD CHAMPIONSHIP"),Gold);
    UHorizontalBox* TitleRow=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(TitleHero,TitleRow,3);
    UDigimonVenomNXTAnimatedPortrait* TP=nullptr; Row(TitleRow,Portrait(WidgetTree,TP,130),0,10); TitlePortrait=TP;
    UVerticalBox* TitleInfo=WidgetTree->ConstructWidget<UVerticalBox>(); Row(TitleRow,TitleInfo);
    TitleHolder=Text(WidgetTree,TEXT(""),28,White,true); Add(TitleInfo,TitleHolder,3); TitleDetails=Text(WidgetTree,TEXT(""),15,Gold); Add(TitleInfo,TitleDetails,5);
    TitleMilestone=Text(WidgetTree,TEXT(""),13,Muted); Add(TitleHero,TitleMilestone,4); DefenseProgress=Meter(WidgetTree,TitleHero,Gold);
    UVerticalBox* Reigns=Section(WidgetTree,Titles,TEXT("CHAMPIONSHIP CONTINUITY"),Gold); Add(Reigns,Text(WidgetTree,TEXT("Each title changes hands through a real scheduled match. Completed title bouts remain in the career archive."),12,Muted),4); ReignHistory=Text(WidgetTree,TEXT(""),14,White); Add(Reigns,ReignHistory,5);

    UVerticalBox* Archive=WidgetTree->ConstructWidget<UVerticalBox>(); Pages->AddChild(Archive);
    Add(Archive,Text(WidgetTree,TEXT("YOUR CAREER, RECORDED"),19,Cyan,true),2); Add(Archive,Text(WidgetTree,TEXT("Review completed bookings and credited payouts. Select a week to see the full eight-match card."),12,Muted),3);
    Pager(Archive,TEXT("seasonarchivepage"),Prev,PageLabel,Next); ArchivePrevious=Prev; ArchivePager=PageLabel; ArchiveNext=Next;
    Add(Archive,Button(TEXT("REFRESH ARCHIVE"),TEXT("seasonarchiverefresh"),Cyan),3);
    for(int32 I=0;I<ArchivePageSize;++I) { UDigimonVenomNXTActionButton* B=Button(TEXT(""),TEXT("seasonarchiveweek"),Cyan); Add(Archive,B,2); ArchiveRows.Add(B); }
    UVerticalBox* ArchivedCard=Section(WidgetTree,Archive,TEXT("BOOKING REPLAY  /  RECORDED RESULTS")); ArchiveSelection=Text(WidgetTree,TEXT(""),14,Gold,true); Add(ArchivedCard,ArchiveSelection,4); BuildMatchCard(ArchivedCard,ArchiveMatches);
    Add(ArchivedCard,Text(WidgetTree,TEXT("THIS BOOKING'S CREDIT LEDGER"),12,Gold,true),8);
    ArchivedPayouts=Text(WidgetTree,TEXT(""),12,Muted); Add(ArchivedCard,ArchivedPayouts,4);
    HistoricalToggle=Button(TEXT("SHOW SAVED LEAGUE TABLE"),TEXT("seasonhistoricaltoggle"),Cyan); Add(ArchivedCard,HistoricalToggle,5);
    HistoricalStandings=WidgetTree->ConstructWidget<UVerticalBox>(); Add(ArchivedCard,HistoricalStandings,0);
    Pager(HistoricalStandings,TEXT("seasonhistoricalpage"),Prev,PageLabel,Next); HistoricalPrevious=Prev; HistoricalPager=PageLabel; HistoricalNext=Next;
    for(int32 I=0;I<RosterPageSize;++I) { UTextBlock* T=Text(WidgetTree,TEXT(""),12,White); Add(HistoricalStandings,T,5); HistoricalRows.Add(T); }
    UVerticalBox* Rewards=Section(WidgetTree,Archive,TEXT("CAREER EARNINGS & UPCOMING PAYOUTS"),Gold); RewardSummary=Text(WidgetTree,TEXT(""),17,Gold,true); Add(Rewards,RewardSummary,4); RewardForecast=Text(WidgetTree,TEXT(""),12,Muted); Add(Rewards,RewardForecast,5);
    Pager(Rewards,TEXT("seasonpayoutpage"),Prev,PageLabel,Next); PayoutPrevious=Prev; PayoutPager=PageLabel; PayoutNext=Next;
    for(int32 I=0;I<ArchivePageSize;++I) { UTextBlock* T=Text(WidgetTree,TEXT(""),12,White); Add(Rewards,T,4); PayoutRows.Add(T); }
    SaveStatus=Text(WidgetTree,TEXT("AUTO-SAVED  /  Your private calendar advances only when you play. Your league pauses when you leave."),11,Muted); Add(Root,SaveStatus,10);
}

namespace DigimonSeasonUI
{
    FString NameOf(const FDigimonSeasonCareer& Career,const FString& Id)
    {
        const FDigimonSeasonTamer* T=DigimonVenomNXTSeason::FindTamer(Career,Id); return T?T->Name:Id.IsEmpty()?TEXT("Vacant"):Id==TEXT("player")?TEXT("You"):TEXT("Unknown tamer");
    }
    TArray<FDigimonOwnedPartner> CurrentParty(const FDigimonPlayerProfile& Profile)
    {
        TArray<FDigimonOwnedPartner> Out;
        for(const FGuid& Id:Profile.Party) if(const FDigimonOwnedPartner* P=Profile.Collection.FindByPredicate([&](const FDigimonOwnedPartner& Owned){return Owned.InstanceId==Id;})) Out.Add(*P);
        return Out;
    }
    TArray<FDigimonOwnedPartner> TeamOf(const FDigimonPlayerProfile& Profile,const FDigimonSeasonTamer* T)
    {
        return T?(T->bPlayer?CurrentParty(Profile):T->Team):TArray<FDigimonOwnedPartner>();
    }
    void Leader(UDigimonVenomNXTAnimatedPortrait* Portrait,const TArray<FDigimonOwnedPartner>& Team)
    {
        if(!Portrait)return; Portrait->SetVisibility(Team.IsEmpty()?ESlateVisibility::Hidden:ESlateVisibility::HitTestInvisible);
        if(!Team.IsEmpty())Portrait->SetDigimon(Team[0].SpeciesId,Team[0].Variant);
    }
    void UpdatePager(int32& Page,int32 Total,int32 Size,UTextBlock* Label,UDigimonVenomNXTActionButton* Previous,UDigimonVenomNXTActionButton* Next,const FString& Command,const FString& Noun)
    {
        const int32 Count=FMath::Max(1,FMath::DivideAndRoundUp(Total,Size)); Page=FMath::Clamp(Page,0,Count-1);
        Set(Label,FString::Printf(TEXT("%s  %d / %d   |   %d TOTAL"),*Noun,Page+1,Count,Total));
        Previous->InitializeAction(Command,Page-1); Previous->SetIsEnabled(Page>0); Next->InitializeAction(Command,Page+1); Next->SetIsEnabled(Page+1<Count);
    }
    FString TeamSummary(const TArray<FDigimonOwnedPartner>& Team)
    {
        if(Team.IsEmpty())return TEXT("No party selected. Add partners in the Evolution Lab.");
        int32 Low=MAX_int32,High=0; for(const auto& P:Team){Low=FMath::Min(Low,P.Level);High=FMath::Max(High,P.Level);}
        return Low==High?FString::Printf(TEXT("%d PARTNERS  /  LV.%d"),Team.Num(),Low):FString::Printf(TEXT("%d PARTNERS  /  LV.%d-%d"),Team.Num(),Low,High);
    }
}

void UDigimonVenomNXTSeasonWidget::NativeTick(const FGeometry& MyGeometry,float InDeltaTime)
{
    Super::NativeTick(MyGeometry,InDeltaTime);
    const double Now=FPlatformTime::Seconds();
    if(bCommandPending&&Now-CommandSentAt>8.0)
    {
        bCommandPending=false;
        if(PlayerState.IsValid()&&Data.IsValid())RefreshFromProfile(PlayerState.Get(),Data.Get());
    }
    if(bArchivePending&&Now-ArchiveRequestTime>8.0)
    {
        bArchivePending=false;
        if(PlayerState.IsValid()&&Data.IsValid())RefreshArchive();
    }
}

void UDigimonVenomNXTSeasonWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* InPlayerState,UDigimonVenomNXTDataSubsystem* InData)
{
    BuildLayout(); PlayerState=InPlayerState; Data=InData;
    if(!PlayerState.IsValid()||!Data.IsValid())return;
    using namespace DigimonSeasonUI;
    const FDigimonSeasonCareer& C=PlayerState->Profile.Season;
    if(!C.CareerId.IsEmpty()&&BoundCareerId!=C.CareerId)
    {
        if(!BoundCareerId.IsEmpty()) { ActiveTab=0; RosterPage=RivalryPage=ArchivePage=PayoutPage=HistoricalRosterPage=0; bShowHistoricalStandings=false; SelectedTamerId.Empty(); SelectedArchiveWeek=0; }
        BoundCareerId=C.CareerId; ArchiveSnapshot=FDigimonSeasonArchivePage(); bHasArchivePage=bArchivePending=bCommandPending=false;
    }
    if(bCommandPending&&(C.Week!=PendingWeek||C.bScheduledBattleComplete!=bPendingComplete))bCommandPending=false;
    Set(Calendar,C.Version>0?FString::Printf(TEXT("%s   /   BOOKING WEEK %d"),*DigimonVenomNXTSeason::CalendarLabel(C),C.Week):TEXT("Synchronizing your private league..."));
    Set(SaveStatus,bCommandPending?TEXT("SYNCHRONIZING  /  Waiting for the server to confirm your booking."):TEXT("AUTO-SAVED  /  Your private calendar advances only when you play. Your league pauses when you leave."));
    for(int32 I=0;I<Tabs.Num();++I)DigimonVenomNXTUI::StyleButton(Tabs[I],I==3?Gold:Cyan,ActiveTab==I);
    Pages->SetActiveWidgetIndex(ActiveTab);
    if(ActiveTab==0)RefreshWeek(); else if(ActiveTab==1)RefreshRoster(); else if(ActiveTab==2)RefreshRivalries(); else if(ActiveTab==3)RefreshChampionship(); else RefreshArchive();
}

void UDigimonVenomNXTSeasonWidget::RefreshTeams(TArray<FDigimonSeasonPartnerView>& Views,const TArray<FDigimonOwnedPartner>& Team,bool bDetailed)
{
    using namespace DigimonSeasonUI;
    for(int32 I=0;I<Views.Num();++I)
    {
        auto& V=Views[I]; const bool bHasPartner=Team.IsValidIndex(I);
        V.Bounds->SetVisibility(bHasPartner?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
        // Collapsed reserve slots must not leave empty uniform-grid rows on smaller parties.
        if(UUniformGridSlot* PartnerGridSlot=Cast<UUniformGridSlot>(V.Bounds->Slot))PartnerGridSlot->SetRow(bHasPartner?I/3:0);
        if(!bHasPartner)continue;
        const auto& P=Team[I]; const FDigimonBattleUnit Unit=DigimonVenomNXTAutoBattle::BuildUnit(P,Data.Get());
        V.Portrait->SetDigimon(P.SpeciesId,P.Variant); Set(V.Name,Unit.DisplayName);
        FString Stats=FString::Printf(TEXT("LV.%d  /  %s\n%s\nHP %d   SP %d\nATK %d  DEF %d\nINT %d  SPD %d"),P.Level,I<FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize,1,3)?TEXT("ACTIVE"):TEXT("RESERVE"),*DigimonVenomNXTUI::VarietyLabel(P.Variant),Unit.Stats.MaxHP,Unit.Stats.MaxSP,Unit.Stats.Attack,Unit.Stats.Defense,Unit.Stats.Spirit,Unit.Stats.Speed);
        if(bDetailed)Stats+=FString::Printf(TEXT("\nCAM %d   ABI %d"),P.CAM,P.ABI);
        Set(V.Stats,Stats); V.Card->SetToolTipText(FText::FromString(DigimonVenomNXTCombatUI::UnitDetails(Unit)));
    }
}

void UDigimonVenomNXTSeasonWidget::RefreshMatches(TArray<FDigimonSeasonMatchView>& Views,const TArray<FDigimonSeasonMatch>& Fixtures,const TArray<FDigimonSeasonTamer>* SavedStandings)
{
    using namespace DigimonSeasonUI; const auto& C=PlayerState->Profile.Season; const TCHAR* Days[]={TEXT("MON"),TEXT("TUE"),TEXT("WED"),TEXT("THU"),TEXT("FRI"),TEXT("SAT"),TEXT("SUN")};
    auto DisplayName=[&](const FString& Id)->FString
    {
        if(SavedStandings)if(const auto* T=SavedStandings->FindByPredicate([&](const FDigimonSeasonTamer& Entry){return Entry.TamerId==Id;}))return T->Name;
        return NameOf(C,Id);
    };
    for(int32 I=0;I<Views.Num();++I)
    {
        auto& V=Views[I]; V.Card->SetVisibility(Fixtures.IsValidIndex(I)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!Fixtures.IsValidIndex(I))continue;
        const auto& M=Fixtures[I]; const bool bLegacyResult=M.bResolved&&!M.bDraw&&M.WinnerTamerId.IsEmpty(); const bool HomeWon=!bLegacyResult&&M.bResolved&&!M.bDraw&&M.WinnerTamerId==M.HomeTamerId; const bool AwayWon=!bLegacyResult&&M.bResolved&&!M.bDraw&&M.WinnerTamerId==M.AwayTamerId;
        Set(V.Day,bLegacyResult?TEXT("--"):Days[FMath::Clamp(M.DayOfWeek,1,7)-1]);
        Set(V.Home,bLegacyResult?TEXT("Previous-version fixture"):DisplayName(M.HomeTamerId)+(HomeWon?TEXT("  · WIN"):TEXT(""))); Set(V.Away,bLegacyResult?TEXT("Result unavailable"):DisplayName(M.AwayTamerId)+(AwayWon?TEXT("  · WIN"):TEXT("")));
        V.Home->SetColorAndOpacity(HomeWon?Green:M.HomeTamerId==TEXT("player")?Cyan:White); V.Away->SetColorAndOpacity(AwayWon?Green:M.AwayTamerId==TEXT("player")?Cyan:White);
        Set(V.Result,bLegacyResult?TEXT("LEGACY\nCOMPLETE"):M.bTitleMatch?(M.bResolved?TEXT("TITLE\nFINAL"):TEXT("TITLE")):M.bDraw?TEXT("DRAW"):M.bResolved?TEXT("FINAL"):TEXT("BOOKED")); V.Result->SetColorAndOpacity(bLegacyResult?Muted:M.bTitleMatch?Gold:M.bResolved?Green:Muted);
        V.Card->SetBrush(FSlateRoundedBoxBrush(M.bPlayerMatch?FLinearColor(0.02f,0.095f,0.13f,1):Panel,5.0f,(M.bPlayerMatch?Cyan:Muted).CopyWithNewOpacity(M.bPlayerMatch?0.6f:0.15f),1));
        V.Card->SetToolTipText(FText::FromString(bLegacyResult?M.Result:FString::Printf(TEXT("%s versus %s\n%s"),*DisplayName(M.HomeTamerId),*DisplayName(M.AwayTamerId),M.Result.IsEmpty()?TEXT("Results are confirmed after your match."):*M.Result)));
    }
}

void UDigimonVenomNXTSeasonWidget::RefreshWeek()
{
    using namespace DigimonSeasonUI; const auto& Profile=PlayerState->Profile; const auto& C=Profile.Season;
    const FDigimonSeasonMatch* Match=DigimonVenomNXTSeason::GetPlayerMatch(C);
    const bool bLegacyResult=Match&&Match->bResolved&&!Match->bDraw&&Match->WinnerTamerId.IsEmpty();
    const FDigimonSeasonTamer* Opponent=DigimonVenomNXTSeason::FindTamer(C,C.CurrentRivalId);
    const FDigimonSeasonTamer* Player=DigimonVenomNXTSeason::FindTamer(C,TEXT("player"));
    Set(MatchKicker,FString(C.bScheduledBattleComplete?TEXT("WEEK COMPLETE"):TEXT("THIS WEEK"))+(Match&&Match->bTitleMatch?TEXT("  /  WORLD CHAMPIONSHIP"):TEXT("  /  LEAGUE MATCH")));
    Set(MatchTitle,C.EventName.IsEmpty()?TEXT("Your opening booking"):C.EventName);
    Set(MatchDetail,FString::Printf(TEXT("%s  /  Opponent progression LV.%d"),*DigimonVenomNXTSeason::CalendarLabel(C,Match?Match->DayOfWeek-1:1),FMath::Max(1,C.OpponentLevel)));
    FString Outcome=TEXT("MATCH READY"); FLinearColor OutcomeColor=Cyan;
    if(C.bScheduledBattleComplete&&Match)
    {
        Outcome=bLegacyResult?TEXT("COMPLETED / LEGACY RESULT UNAVAILABLE"):Match->bDraw?TEXT("DRAW"):Match->WinnerTamerId==TEXT("player")?TEXT("VICTORY"):TEXT("DEFEAT"); OutcomeColor=bLegacyResult?Muted:Match->bDraw?Gold:Match->WinnerTamerId==TEXT("player")?Green:Red;
        if(!bLegacyResult)Outcome+=FString::Printf(TEXT("\n+%lld CREDITS  /  +%lld EXP"),C.LastMatchCredits,C.LastMatchXP);
    }
    if(bLegacyResult)
    {
        Set(MatchKicker,TEXT("PREVIOUS VERSION  /  COMPLETED")); Set(MatchTitle,TEXT("Previous season booking"));
        Set(MatchDetail,TEXT("Your saved totals are preserved. Detailed opponents, outcomes and rewards were not stored by the previous version."));
    }
    Set(MatchOutcome,Outcome); MatchOutcome->SetColorAndOpacity(OutcomeColor);
    Caption(MatchAction,bCommandPending?TEXT("CONNECTING..."):C.bScheduledBattleComplete?TEXT("NEXT WEEK  →"):C.PendingContextId.IsEmpty()?TEXT("START THIS WEEK'S MATCH"):TEXT("RESUME THIS WEEK'S MATCH"));
    MatchAction->InitializeAction(C.bScheduledBattleComplete?TEXT("seasonadvance"):TEXT("seasonmatch")); MatchAction->SetIsEnabled(C.Version>0&&Match&&!bCommandPending&&(C.bScheduledBattleComplete||!Profile.Party.IsEmpty()));
    Set(PlayerName,Profile.Username+TEXT("  / YOU")); Set(OpponentName,bLegacyResult?TEXT("Historical opponent unavailable"):Opponent?Opponent->Name:TEXT("Preparing opponent...")); SetTamer(PlayerTamer,Profile.TamerStyleId); if(Opponent)SetTamer(OpponentTamer,Opponent->TamerStyleId); if(bLegacyResult)OpponentTamer->SetVisibility(ESlateVisibility::Hidden);
    const auto HomeTeam=CurrentParty(Profile); const auto AwayTeam=bLegacyResult?TArray<FDigimonOwnedPartner>():C.bScheduledBattleComplete?TeamOf(Profile,Opponent):DigimonVenomNXTSeason::BuildScheduledOpponent(Profile,Data.Get());
    Set(PlayerTeamSummary,TeamSummary(HomeTeam)); Set(OpponentTeamSummary,bLegacyResult?TEXT("RESULT RECORD UNAVAILABLE"):(C.bScheduledBattleComplete?TEXT("ROSTER: "):TEXT(""))+TeamSummary(AwayTeam)); RefreshTeams(PlayerTeam,HomeTeam,false); RefreshTeams(OpponentTeam,AwayTeam,false);
    RefreshMatches(WeekMatches,C.CurrentCard);
    const FDigimonSeasonTamer* Champion=DigimonVenomNXTSeason::FindTamer(C,C.ChampionId); Leader(ChampionPortrait,TeamOf(Profile,Champion)); Set(ChampionName,NameOf(C,C.ChampionId));
    Set(ChampionDetails,FString::Printf(TEXT("Reign %d  /  %d defenses\nSince booking week %d"),C.ChampionReign,C.ChampionDefenses,C.ChampionSinceWeek));
    Set(CareerRecord,FString::Printf(TEXT("%d - %d"),C.Wins,C.Losses)); Set(CareerRank,FString::Printf(TEXT("#%d IN THE LEAGUE  /  %d RP"),Player?Player->Rank:16,Player?Player->Rating:1200));
    Set(CareerTitles, FString::Printf(TEXT("%d draws  /  %d titles\n%d career defenses"),
        C.Draws, C.Championships, Player ? Player->Defenses : 0));
    Set(CareerIncome, FString::Printf(TEXT("CAREER PAYOUTS\n%lld credits\n%lld partner EXP"),
        C.TotalCreditsEarned, C.TotalExperienceEarned));
    FString News; for(int32 I=0;I<FMath::Min(4,C.News.Num());++I) { if(!News.IsEmpty())News+=TEXT("\n\n"); News+=TEXT("• ")+C.News[I]; }
    Set(LeagueNews,News.IsEmpty()?TEXT("Your own roster. Your own calendar. The opening week is ready when you are."):News);
}

void UDigimonVenomNXTSeasonWidget::RefreshRoster()
{
    using namespace DigimonSeasonUI; const auto& Profile=PlayerState->Profile; const auto& C=Profile.Season;
    TArray<const FDigimonSeasonTamer*> Sorted; for(const auto& T:C.Roster)Sorted.Add(&T);
    Sorted.Sort([](const FDigimonSeasonTamer& A,const FDigimonSeasonTamer& B){return A.Rank!=B.Rank?A.Rank<B.Rank:A.TamerId<B.TamerId;});
    UpdatePager(RosterPage,Sorted.Num(),RosterPageSize,RosterPager,RosterPrevious,RosterNext,TEXT("seasonrosterpage"),TEXT("ROSTER"));
    if(!DigimonVenomNXTSeason::FindTamer(C,SelectedTamerId))SelectedTamerId=TEXT("player");
    for(int32 I=0;I<RosterRows.Num();++I)
    {
        auto& V=RosterRows[I]; const int32 Index=RosterPage*RosterPageSize+I; V.Button->SetVisibility(Sorted.IsValidIndex(Index)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!Sorted.IsValidIndex(Index))continue;
        const auto& T=*Sorted[Index]; V.Button->InitializeAction(TEXT("seasontamer:")+T.TamerId); DigimonVenomNXTUI::StyleButton(V.Button,T.TamerId==C.ChampionId?Gold:Cyan,SelectedTamerId==T.TamerId);
        Set(V.Rank,FString::Printf(TEXT("%02d"),T.Rank)); Set(V.Name,T.Name+(T.bPlayer?TEXT("  / YOU"):TEXT(""))); V.Name->SetColorAndOpacity(T.bPlayer?Cyan:White);
        Leader(V.Portrait,TeamOf(Profile,&T)); SetTamer(V.Tamer,T.TamerStyleId);
        Set(V.Record,FString::Printf(TEXT("%d RP  /  %d W · %d L · %d D"),T.Rating,T.Wins,T.Losses,T.Draws));
        Set(V.Progress,FString::Printf(TEXT("%d titles · %d defenses\n%+d streak  /  best %d"),T.Titles,T.Defenses,T.Streak,T.BestStreak));
    }
    const FDigimonSeasonTamer* Selected=DigimonVenomNXTSeason::FindTamer(C,SelectedTamerId); Set(SelectedTamerName,Selected?Selected->Name:TEXT("Synchronizing roster..."));
    if(Selected)Set(SelectedTamerRecord,FString::Printf(TEXT("RANK #%d  /  %d RP  /  %d W - %d L - %d D  /  %d TITLES  /  %d DEFENSES\n%s"),Selected->Rank,Selected->Rating,Selected->Wins,Selected->Losses,Selected->Draws,Selected->Titles,Selected->Defenses,*TeamSummary(TeamOf(Profile,Selected))));
    RefreshTeams(SelectedTeam,TeamOf(Profile,Selected),true);
}

void UDigimonVenomNXTSeasonWidget::RefreshRivalries()
{
    using namespace DigimonSeasonUI; const auto& C=PlayerState->Profile.Season;
    TArray<const FDigimonSeasonRivalry*> Sorted; for(const auto& R:C.Rivalries)Sorted.Add(&R);
    Sorted.Sort([](const FDigimonSeasonRivalry& A,const FDigimonSeasonRivalry& B){return A.Heat!=B.Heat?A.Heat>B.Heat:A.LastWeek>B.LastWeek;});
    UpdatePager(RivalryPage,Sorted.Num(),RivalryPageSize,RivalryPager,RivalryPrevious,RivalryNext,TEXT("seasonrivalrypage"),TEXT("RIVALRIES"));
    RivalryEmpty->SetVisibility(Sorted.IsEmpty()?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
    for(int32 I=0;I<RivalryCards.Num();++I)
    {
        auto& V=RivalryCards[I]; const int32 Index=RivalryPage*RivalryPageSize+I; V.Card->SetVisibility(Sorted.IsValidIndex(Index)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!Sorted.IsValidIndex(Index))continue;
        const auto& R=*Sorted[Index]; Set(V.Names,NameOf(C,R.TamerAId)+TEXT("  vs  ")+NameOf(C,R.TamerBId));
        Set(V.Record,FString::Printf(TEXT("%d meetings  /  Last clash: week %d\n%s: %d wins\n%s: %d wins  /  %d draws"),R.Meetings,R.LastWeek,*NameOf(C,R.TamerAId),R.AWins,*NameOf(C,R.TamerBId),R.BWins,R.Draws));
        const FLinearColor Accent=R.Heat>=65?Gold:Cyan; Set(V.Status,FString::Printf(TEXT("%s  /  HEAT %d%%"),R.Heat>=65?TEXT("INTENSE"):R.Heat>=25?TEXT("BUILDING"):TEXT("NEW RIVALRY"),R.Heat)); V.Status->SetColorAndOpacity(Accent); V.Heat->SetFillColorAndOpacity(Accent); V.Heat->SetPercent(FMath::Clamp(R.Heat/100.0f,0.0f,1.0f));
    }
}

void UDigimonVenomNXTSeasonWidget::RefreshChampionship()
{
    using namespace DigimonSeasonUI; const auto& Profile=PlayerState->Profile; const auto& C=Profile.Season;
    const FDigimonSeasonTamer* Champion=DigimonVenomNXTSeason::FindTamer(C,C.ChampionId); Leader(TitlePortrait,TeamOf(Profile,Champion)); Set(TitleHolder,NameOf(C,C.ChampionId));
    Set(TitleDetails,FString::Printf(TEXT("REIGN %d  /  %d SUCCESSFUL DEFENSES\nChampion since booking week %d"),C.ChampionReign,C.ChampionDefenses,C.ChampionSinceWeek));
    const int32 Interval=FMath::Max(1,C.DefenseRewardInterval); const int64 Next=(static_cast<int64>(C.ChampionDefenses)/Interval+1)*Interval;
    Set(TitleMilestone,FString::Printf(TEXT("DEFENSE MILESTONE  /  %d of %lld retained\nA player champion earns %lld credits every %d successful defenses in a reign. Next checkpoint: defense %lld. Draws do not count as successful defenses."),C.ChampionDefenses,Next,static_cast<int64>(C.DefenseRewardCredits),Interval,Next));
    DefenseProgress->SetPercent(static_cast<float>(C.ChampionDefenses%Interval)/Interval);
    TArray<const FDigimonSeasonReign*> Sorted; for(const auto& R:C.Reigns)Sorted.Add(&R); Sorted.Sort([](const FDigimonSeasonReign& A,const FDigimonSeasonReign& B){return A.ReignNumber>B.ReignNumber;});
    FString History; for(int32 I=0;I<FMath::Min(16,Sorted.Num());++I)
    {
        const auto& R=*Sorted[I]; if(!History.IsEmpty())History+=TEXT("\n\n"); History+=FString::Printf(TEXT("REIGN %d   /   %s\nWeek %d - %s   /   %d defenses"),R.ReignNumber,*R.HolderName,R.StartWeek,R.EndWeek==0?TEXT("PRESENT"):*FString::FromInt(R.EndWeek),R.Defenses);
    }
    Set(ReignHistory,History.IsEmpty()?TEXT("The opening champion begins your league's history. Each completed title bout is recorded in the career archive."):History);
}

void UDigimonVenomNXTSeasonWidget::ApplyArchivePage(const FDigimonSeasonArchivePage& Page)
{
    if(!PlayerState.IsValid())return;
    // A slow response from an older page or another signed-in career cannot replace this view.
    if(Page.PageIndex!=ArchivePage||(!Page.CareerId.IsEmpty()&&Page.CareerId!=PlayerState->Profile.Season.CareerId))return;
    if(Page.bSuccess&&Page.CareerId!=PlayerState->Profile.Season.CareerId)return;
    ArchiveSnapshot=Page;
    // Error responses may have no disk career ID; bind them to this authenticated request for retry feedback.
    if(ArchiveSnapshot.CareerId.IsEmpty())ArchiveSnapshot.CareerId=PlayerState->Profile.Season.CareerId;
    bHasArchivePage=true; bArchivePending=false;
    if(ActiveTab==4)RefreshArchive();
}

void UDigimonVenomNXTSeasonWidget::RefreshArchive()
{
    using namespace DigimonSeasonUI; const auto& C=PlayerState->Profile.Season;
    TArray<const FDigimonSeasonArchive*> Records;
    const bool bSnapshotValid=bHasArchivePage&&ArchiveSnapshot.CareerId==C.CareerId;
    const bool bPageReady=bSnapshotValid&&ArchiveSnapshot.PageIndex==ArchivePage&&ArchiveSnapshot.bSuccess;
    if(bPageReady)for(const auto& A:ArchiveSnapshot.Records)Records.Add(&A);
    else if(!bHasArchivePage&&ArchivePage==0)for(const auto& A:C.Archive)Records.Add(&A);
    Records.Sort([](const FDigimonSeasonArchive& A,const FDigimonSeasonArchive& B){return A.Week>B.Week;});
    const int32 Total=bSnapshotValid?ArchiveSnapshot.TotalRecords:C.Archive.Num();
    const int32 PageCount=FMath::Max(1,FMath::DivideAndRoundUp(Total,ArchivePageSize));
    Set(ArchivePager,FString::Printf(TEXT("%s  /  PAGE %d OF %d  /  %d BOOKINGS"),bArchivePending?TEXT("LOADING ARCHIVE"):TEXT("CAREER ARCHIVE"),ArchivePage+1,PageCount,Total));
    ArchivePrevious->InitializeAction(TEXT("seasonarchivepage"),FMath::Max(0,ArchivePage-1)); ArchivePrevious->SetIsEnabled(!bArchivePending&&ArchivePage>0);
    ArchiveNext->InitializeAction(TEXT("seasonarchivepage"),ArchivePage+1); ArchiveNext->SetIsEnabled(!bArchivePending&&((bPageReady&&ArchiveSnapshot.bHasMore)||ArchivePage+1<PageCount));
    if(!Records.ContainsByPredicate([&](const FDigimonSeasonArchive* A){return A->Week==SelectedArchiveWeek;}))SelectedArchiveWeek=Records.IsEmpty()?0:Records[0]->Week;
    const FDigimonSeasonArchive* Selected=nullptr;
    for(int32 I=0;I<ArchiveRows.Num();++I)
    {
        auto* B=ArchiveRows[I].Get(); B->SetVisibility(Records.IsValidIndex(I)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!Records.IsValidIndex(I))continue;
        const auto& A=*Records[I]; const FDigimonSeasonMatch* PM=A.Matches.FindByPredicate([](const FDigimonSeasonMatch& M){return M.bPlayerMatch;});
        const FString Result=PM?(PM->bDraw?TEXT("DRAW"):PM->WinnerTamerId.IsEmpty()?TEXT("LEGACY COMPLETE / RESULT UNAVAILABLE"):PM->WinnerTamerId==TEXT("player")?TEXT("VICTORY"):TEXT("DEFEAT")):TEXT("COMPLETE");
        const bool bLegacyRecord=PM&&PM->bResolved&&!PM->bDraw&&PM->WinnerTamerId.IsEmpty();
        Caption(B,bLegacyRecord?FString::Printf(TEXT("WEEK %d   /   LEGACY COMPLETE   /   DETAILED RESULT UNAVAILABLE"),A.Week):FString::Printf(TEXT("WEEK %d   /   %s   /   %s   /   RANK #%d   /   +%lld CREDITS"),A.Week,*A.EventName,*Result,A.PlayerRank,A.CreditsEarned));
        B->InitializeAction(TEXT("seasonarchiveweek"),A.Week); DigimonVenomNXTUI::StyleButton(B,Cyan,A.Week==SelectedArchiveWeek); if(A.Week==SelectedArchiveWeek)Selected=&A;
    }
    FString Description=TEXT("Complete your first match to begin your career archive.");
    if(bArchivePending&&Records.IsEmpty())Description=TEXT("Loading saved bookings from your career archive...");
    else if(bSnapshotValid&&!ArchiveSnapshot.bSuccess)Description=ArchiveSnapshot.Error.IsEmpty()?TEXT("The archive could not be loaded. Choose Refresh Archive to retry."):ArchiveSnapshot.Error;
    else if(Selected)
    {
        const FDigimonSeasonTamer* SavedChampion=Selected->Standings.FindByPredicate([&](const FDigimonSeasonTamer& T){return T.TamerId==Selected->ChampionId;});
        Description=FString::Printf(TEXT("WEEK %d  /  %s\nCHAMPION AFTER THE CARD: %s  /  REIGN %d  /  %d DEFENSES\nSINCE WEEK %d  /  YOUR RANK #%d  /  %d RP"),Selected->Week,*Selected->EventName,SavedChampion?*SavedChampion->Name:*NameOf(C,Selected->ChampionId),Selected->ChampionReign,Selected->ChampionDefenses,Selected->ChampionSinceWeek,Selected->PlayerRank,Selected->PlayerRating);
    }
    Set(ArchiveSelection,Description); RefreshMatches(ArchiveMatches,Selected?Selected->Matches:TArray<FDigimonSeasonMatch>(),Selected?&Selected->Standings:nullptr);
    FString Ledger;
    if(Selected)for(const auto& P:Selected->Payouts) { if(!Ledger.IsEmpty())Ledger+=TEXT("\n"); Ledger+=FString::Printf(TEXT("+%lld credits  /  %s"),P.Credits,*P.Reason); }
    Set(ArchivedPayouts,Ledger.IsEmpty()?TEXT("No credit payouts were recorded for this booking."):Ledger);
    HistoricalStandings->SetVisibility(bShowHistoricalStandings?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
    Caption(HistoricalToggle,bShowHistoricalStandings?TEXT("HIDE SAVED LEAGUE TABLE"):TEXT("SHOW SAVED LEAGUE TABLE")); HistoricalToggle->SetIsEnabled(Selected&&!Selected->Standings.IsEmpty());
    TArray<const FDigimonSeasonTamer*> Standings; if(Selected)for(const auto& T:Selected->Standings)Standings.Add(&T);
    Standings.Sort([](const FDigimonSeasonTamer& A,const FDigimonSeasonTamer& B){return A.Rank<B.Rank;});
    UpdatePager(HistoricalRosterPage,Standings.Num(),RosterPageSize,HistoricalPager,HistoricalPrevious,HistoricalNext,TEXT("seasonhistoricalpage"),TEXT("SAVED STANDINGS"));
    for(int32 I=0;I<HistoricalRows.Num();++I)
    {
        const int32 Index=HistoricalRosterPage*RosterPageSize+I; UTextBlock* Text=HistoricalRows[I]; Text->SetVisibility(Standings.IsValidIndex(Index)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!Standings.IsValidIndex(Index))continue;
        const auto& T=*Standings[Index]; Set(Text,FString::Printf(TEXT("#%02d  %s   /   %d RP\n%d W - %d L - %d D  /  %d TITLES  /  %d DEFENSES  /  %+d STREAK"),T.Rank,*T.Name,T.Rating,T.Wins,T.Losses,T.Draws,T.Titles,T.Defenses,T.Streak)); Text->SetColorAndOpacity(T.bPlayer?Cyan:White);
    }
    Set(RewardSummary,FString::Printf(TEXT("%lld CAREER CREDITS  /  %lld PARTNER EXP"),C.TotalCreditsEarned,C.TotalExperienceEarned));
    Set(RewardForecast,FString::Printf(TEXT("NEXT IN-GAME MONTH: %lld credits at your current performance\nNEXT IN-GAME YEAR: %lld credits at your current performance\n\nThis month: %d W / %d L / %d D   |   This year: %d W / %d L / %d D\nServer estimates include your results, current league rank and champion status. Payouts are credited automatically when you advance into a new month or year; calendar time does not pass while you are away. These forecasts change with your results. Each payout is recorded once."),C.MonthRewardEstimate,C.YearRewardEstimate,C.MonthWins,C.MonthLosses,C.MonthDraws,C.YearWins,C.YearLosses,C.YearDraws));
    UpdatePager(PayoutPage,C.Payouts.Num(),ArchivePageSize,PayoutPager,PayoutPrevious,PayoutNext,TEXT("seasonpayoutpage"),TEXT("RECENT PAYOUTS"));
    for(int32 I=0;I<PayoutRows.Num();++I)
    {
        const int32 Index=PayoutPage*ArchivePageSize+I; UTextBlock* T=PayoutRows[I];
        T->SetVisibility(C.Payouts.IsValidIndex(Index)?ESlateVisibility::Visible:ESlateVisibility::Collapsed); if(!C.Payouts.IsValidIndex(Index))continue;
        const auto& P=C.Payouts[Index]; Set(T,FString::Printf(TEXT("WEEK %d   /   +%lld CREDITS   /   %s"),P.Week,P.Credits,*P.Reason)); T->SetToolTipText(FText::FromString(P.PayoutId));
    }
}

void UDigimonVenomNXTSeasonWidget::HandleAction(const FString& Action,int32 Payload)
{
    if(!PlayerState.IsValid()||!Data.IsValid())return;
    if(Action==TEXT("seasontab"))
    {
        ActiveTab=FMath::Clamp(Payload,0,4);
        if(ActiveTab==4)
        {
            bArchivePending=true; ArchiveRequestTime=FPlatformTime::Seconds(); OnAction.Broadcast(TEXT("seasonarchivepage"),ArchivePage);
        }
    }
    else if(Action==TEXT("seasonrosterpage"))RosterPage=FMath::Max(0,Payload);
    else if(Action.StartsWith(TEXT("seasontamer:")))SelectedTamerId=Action.Mid(12);
    else if(Action==TEXT("seasonrivalrypage"))RivalryPage=FMath::Max(0,Payload);
    else if(Action==TEXT("seasonarchiveweek")) { SelectedArchiveWeek=Payload; HistoricalRosterPage=0; }
    else if(Action==TEXT("seasonhistoricaltoggle"))bShowHistoricalStandings=!bShowHistoricalStandings;
    else if(Action==TEXT("seasonhistoricalpage"))HistoricalRosterPage=FMath::Max(0,Payload);
    else if(Action==TEXT("seasonpayoutpage"))PayoutPage=FMath::Max(0,Payload);
    else if(Action==TEXT("seasonarchivepage")||Action==TEXT("seasonarchiverefresh"))
    {
        if(bArchivePending)return;
        if(Action==TEXT("seasonarchivepage"))ArchivePage=FMath::Max(0,Payload);
        bArchivePending=true; ArchiveRequestTime=FPlatformTime::Seconds(); OnAction.Broadcast(TEXT("seasonarchivepage"),ArchivePage);
    }
    else
    {
        if((Action==TEXT("seasonmatch")||Action==TEXT("seasonadvance"))&&!bCommandPending)
        {
            bCommandPending=true; CommandSentAt=FPlatformTime::Seconds(); PendingWeek=PlayerState->Profile.Season.Week; bPendingComplete=PlayerState->Profile.Season.bScheduledBattleComplete;
        }
        else if(bCommandPending&&Action!=TEXT("seasonreturn"))return;
        OnAction.Broadcast(Action,Payload);
    }
    RefreshFromProfile(PlayerState.Get(),Data.Get());
}
