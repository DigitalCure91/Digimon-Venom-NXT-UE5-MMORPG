#include "DigimonVenomNXTRelayWidget.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Texture2D.h"

namespace DigimonRelayUI
{
    const FLinearColor Cyan(0.13f,0.86f,0.98f,1);
    const FLinearColor Gold(1.0f,0.74f,0.27f,1);
    const FLinearColor White(0.93f,0.98f,1,1);
    const FLinearColor Muted(0.60f,0.74f,0.85f,1);
    const FLinearColor Green(0.52f,0.94f,0.66f,1);
    const FLinearColor Ink(0.010f,0.029f,0.055f,0.98f);
    UTextBlock* Text(UWidgetTree* Tree,const FString& Value,int32 Size=13,FLinearColor Color=White,bool bBold=false)
    {
        UTextBlock* W=Tree->ConstructWidget<UTextBlock>(); W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font=W->GetFont(); Font.Size=Size; Font.TypefaceFontName=bBold?FName(TEXT("Bold")):FName(TEXT("Regular")); W->SetFont(Font); return W;
    }
    void Add(UVerticalBox* Box,UWidget* W,float Pad=3)
    { if(UVerticalBoxSlot* S=Box->AddChildToVerticalBox(W)) { S->SetPadding(FMargin(0,Pad)); S->SetHorizontalAlignment(HAlign_Fill); } }
    void Row(UHorizontalBox* Box,UWidget* W,float Weight=1,float Pad=4)
    { if(UHorizontalBoxSlot* S=Box->AddChildToHorizontalBox(W)) { S->SetPadding(FMargin(Pad,0)); S->SetVerticalAlignment(VAlign_Center); if(Weight>0) { FSlateChildSize Size(ESlateSizeRule::Fill); Size.Value=Weight; S->SetSize(Size); } } }
    UBorder* Card(UWidgetTree* Tree,FLinearColor Accent=Cyan,float Pad=12)
    { UBorder* B=Tree->ConstructWidget<UBorder>(); B->SetBrush(FSlateRoundedBoxBrush(Ink,8.0f,Accent.CopyWithNewOpacity(0.35f),1)); B->SetPadding(FMargin(Pad)); return B; }
    UVerticalBox* Section(UWidgetTree* Tree,UVerticalBox* Parent,const FString& Heading,FLinearColor Accent=Cyan)
    { UBorder* B=Card(Tree,Accent); Add(Parent,B,5); UVerticalBox* V=Tree->ConstructWidget<UVerticalBox>(); B->SetContent(V); Add(V,Text(Tree,Heading,11,Accent,true),3); return V; }
    FString Role(EDigimonRelayRole Value)
    {
        switch(Value) {
        case EDigimonRelayRole::Guide: return TEXT("STORY CONTACT");
        case EDigimonRelayRole::Healer: return TEXT("PARTY CARE");
        case EDigimonRelayRole::Shop: return TEXT("SHOPKEEPER");
        case EDigimonRelayRole::Lab: return TEXT("DIGILAB SERVICES");
        case EDigimonRelayRole::Farm: return TEXT("DIGIFARM SERVICES");
        case EDigimonRelayRole::Gym: return TEXT("DIGIBADGE WARDEN LEADER");
        case EDigimonRelayRole::Champion: return TEXT("DIGIMON CHAMPION");
        case EDigimonRelayRole::Challenger: return TEXT("TITLE CHALLENGER");
        default: return TEXT("TAMER BATTLE"); }
    }
}

TSharedRef<SWidget> UDigimonVenomNXTRelayWidget::RebuildWidget() { BuildLayout(); return Super::RebuildWidget(); }

UDigimonVenomNXTActionButton* UDigimonVenomNXTRelayWidget::Button(const FString& Label,const FString& Action,int32 Payload,bool bGold)
{
    UDigimonVenomNXTActionButton* B=WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(B,bGold?DigimonRelayUI::Gold:DigimonRelayUI::Cyan); B->InitializeAction(Action,Payload);
    B->OnAction.AddDynamic(this,&UDigimonVenomNXTRelayWidget::HandleAction);
    UTextBlock* T=DigimonRelayUI::Text(WidgetTree,Label,12,DigimonRelayUI::White,true); T->SetJustification(ETextJustify::Center); B->SetContent(T); B->SetToolTipText(FText::FromString(Label)); return B;
}

void UDigimonVenomNXTRelayWidget::BuildLayout()
{
    if(Root)return;
    if(!WidgetTree)WidgetTree=NewObject<UWidgetTree>(this,TEXT("RelayWidgetTree"));
    using namespace DigimonRelayUI;
    Root=WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget=Root;
    UBorder* Hero=Card(WidgetTree,Gold,0); Add(Root,Hero,0);
    UOverlay* HeroOverlay=WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(HeroOverlay);
    UVerticalBox* HeroText=WidgetTree->ConstructWidget<UVerticalBox>();
    if(UOverlaySlot* S=HeroOverlay->AddChildToOverlay(HeroText))S->SetPadding(FMargin(22,20));
    Add(HeroText,Text(WidgetTree,TEXT("PRIVATE CAMPAIGN  /  YOUR TAMER. YOUR STORY."),10,Cyan,true),2);
    Add(HeroText,Text(WidgetTree,TEXT("DAWN RELAY"),32,White,true),2);
    Add(HeroText,Text(WidgetTree,TEXT("Restore the relay. Earn your championship."),16,Gold,true),3);
    StatusText=Text(WidgetTree,TEXT("Synchronizing your journey..."),12,White); Add(HeroText,StatusText,5);
    BadgeMeter=WidgetTree->ConstructWidget<UProgressBar>(); BadgeMeter->SetFillColorAndOpacity(Gold);
    USizeBox* MeterSize=WidgetTree->ConstructWidget<USizeBox>(); MeterSize->SetHeightOverride(5); MeterSize->AddChild(BadgeMeter); Add(HeroText,MeterSize,4);
    UHorizontalBox* TabRow=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root,TabRow,9);
    const TCHAR* Labels[]={TEXT("JOURNEY & OBJECTIVE"),TEXT("18-MAP ROUTE"),TEXT("BADGES & CHAMPIONSHIP")};
    for(int32 I=0;I<3;++I) { UDigimonVenomNXTActionButton* B=Button(Labels[I],TEXT("relaytab"),I,I==2); Tabs.Add(B); Row(TabRow,B); }
    Content=WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root,Content,0);
}

void UDigimonVenomNXTRelayWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState)
{
    BoundPlayer=PlayerState; BuildLayout(); RefreshContent();
}

void UDigimonVenomNXTRelayWidget::HandleAction(const FString& Action,int32 Payload)
{
    if(Action==TEXT("relaytab")) { ActiveTab=FMath::Clamp(Payload,0,2); RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); return; }
    if(Action==TEXT("relayinspect")) { InspectedMap=Payload; ActiveTab=0; RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); return; }
    OnAction.Broadcast(Action,Payload);
}

void UDigimonVenomNXTRelayWidget::RefreshContent()
{
    using namespace DigimonRelayUI;
    if(!Content)return;
    Content->ClearChildren();
    for(int32 I=0;I<Tabs.Num();++I)DigimonVenomNXTUI::StyleButton(Tabs[I],I==2?Gold:Cyan,I==ActiveTab);
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get();
    if(!PS) { Add(Content,Text(WidgetTree,TEXT("Your saved journey will appear when your account finishes synchronizing."),14,Muted)); return; }
    const auto& P=PS->Profile.Relay;
    StatusText->SetText(FText::FromString(FString::Printf(TEXT("%s  •  Map %02d / 18  •  %d / 8 DigiBadges  •  %s"),*PS->Profile.Username,P.MapId,P.Badges.Num(),P.bIsChampion?TEXT("REIGNING CHAMPION"):P.bEverChampion?TEXT("CHAMPION — TITLE AVAILABLE TO RECLAIM"):TEXT("CHALLENGER"))));
    BadgeMeter->SetPercent(FMath::Clamp(P.Badges.Num()/8.0f,0.0f,1.0f));
    if(ActiveTab==1)BuildAtlas(); else if(ActiveTab==2)BuildBadges(); else BuildJourney();
}

void UDigimonVenomNXTRelayWidget::BuildJourney()
{
    using namespace DigimonRelayUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Relay;
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bInField=PC&&PC->IsInRelayCampaign();
    UVerticalBox* Next=Section(WidgetTree,Content,TEXT("YOUR NEXT STEP"),Gold);
    Add(Next,Text(WidgetTree,DigimonVenomNXTRelay::Objective(P),18,White,true),4);
    Add(Next,Text(WidgetTree,TEXT("Walk to the named contact and press E to talk. Explore both maps in each region, defeat its tamers and earn its DigiBadge to open the next region. Your campaign space is private."),13,Muted),3);
    const bool bSuspendedBattle=!P.BattleCheckpointJson.IsEmpty();
    if(bSuspendedBattle)
    {
        Add(Next,Text(WidgetTree,TEXT("A Relay battle is saved at its last confirmed turn. Resume it before changing your party, shopping or travelling."),13,Gold,true),5);
        Add(Next,Button(TEXT("RESUME YOUR SAVED RELAY BATTLE"),TEXT("relayresume"),0,true),5);
    }
    UHorizontalBox* Actions=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Next,Actions,6);
    Row(Actions,Button(bInField?TEXT("RETURN TO CAMPAIGN FIELD"):TEXT("ENTER / RESUME YOUR JOURNEY"),TEXT("relayenter"),0,true));
    if(bInField&&!bSuspendedBattle)Row(Actions,Button(TEXT("SAVE & RETURN TO PUBLIC WORLD"),TEXT("relayleave")));
    UVerticalBox* Carry=Section(WidgetTree,Content,TEXT("YOUR EXISTING PARTY TRAVELS WITH YOU"));
    Add(Carry,Text(WidgetTree,TEXT("Real levels. Real stats. The same partners, inventory, Credits and DigiRubies. Open your services whenever you need them; each campaign keeps its own saved progress."),13,Muted),2);
    UHorizontalBox* Services=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Carry,Services,4);
    Services->SetIsEnabled(!bSuspendedBattle);
    Row(Services,Button(TEXT("PARTY"),TEXT("page:Party"))); Row(Services,Button(TEXT("DIGILAB"),TEXT("page:DigiLab"))); Row(Services,Button(TEXT("DIGIFARM"),TEXT("page:DigiFarm"))); Row(Services,Button(TEXT("SHOP & SUPPLIES"),TEXT("page:Shop")));
    Add(Carry,Text(WidgetTree,FString::Printf(TEXT("%lld Credits  •  %d DigiRubies  •  HP Capsules %d  •  SP Capsules %d"),PS->Profile.Credits,PS->Profile.DigiRubies,PS->GetInventoryQuantity(TEXT("hp_s")),PS->GetInventoryQuantity(TEXT("sp_s"))),12,Gold),4);
    const int32 MapId=InspectedMap>0?InspectedMap:P.MapId;
    const FDigimonRelayMap* Map=DigimonVenomNXTRelay::GetMap(MapId); if(!Map)return;
    UVerticalBox* Chapter=Section(WidgetTree,Content,FString::Printf(TEXT("MAP %02d  /  %s"),MapId,MapId==P.MapId?TEXT("CURRENT CHAPTER"):TEXT("ROUTE PREVIEW")));
    Add(Chapter,Text(WidgetTree,Map->Name,24,White,true),3); Add(Chapter,Text(WidgetTree,Map->Subtitle,14,Gold,true),3);
    Add(Chapter,Text(WidgetTree,Map->Intro,14,White),4);
    Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("Recommended Lv.%d–%d  •  %s"),Map->MinLevel,Map->MaxLevel,DigimonVenomNXTRelay::CanEnterMap(P,MapId)?TEXT("Route unlocked"):TEXT("Earn the preceding region's DigiBadge to unlock")),12,Muted),4);
    if(DigimonVenomNXTRelay::CanEnterMap(P,MapId))
    {
        for(const FDigimonRelayNPC& NPC:DigimonVenomNXTRelay::NPCsForMap(MapId))
        {
            if(NPC.Role==EDigimonRelayRole::Champion&&P.bEverChampion)continue;
            const FDigimonRelayNPC* Challenger=DigimonVenomNXTRelay::CurrentChallenger(P);
            if(NPC.Role==EDigimonRelayRole::Challenger&&(!P.bEverChampion||!Challenger||NPC.Id!=Challenger->Id))continue;
            const bool bService=NPC.Role==EDigimonRelayRole::Healer||NPC.Role==EDigimonRelayRole::Shop||NPC.Role==EDigimonRelayRole::Lab||NPC.Role==EDigimonRelayRole::Farm;
            const bool bComplete=NPC.Role==EDigimonRelayRole::Guide?P.CompletedObjectives.Contains(NPC.Id):NPC.Role==EDigimonRelayRole::Champion?P.bEverChampion:P.DefeatedTamers.Contains(NPC.Id);
            const FString State=bService?TEXT("AVAILABLE SERVICE"):bComplete?TEXT("COMPLETE"):TEXT("MEET IN THE FIELD");
            Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("%s  •  %s  •  %s%s"),*State,*NPC.Name,*Role(NPC.Role),DigimonVenomNXTRelay::IsBattleRole(NPC.Role)?*FString::Printf(TEXT("  /  Lv.%d"),NPC.Level):TEXT("")),12,bComplete?Green:Muted,true),4);
        }
    }
    if(bInField&&MapId==P.MapId&&!bSuspendedBattle)
    {
        UHorizontalBox* Travel=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Chapter,Travel,7);
        if(MapId>1) { UDigimonVenomNXTActionButton* B=Button(TEXT("USE ENTRANCE — PREVIOUS MAP"),TEXT("relaytravel"),MapId-1); B->SetIsEnabled(PC->CanUseRelayPortal(false)); B->SetToolTipText(FText::FromString(TEXT("Walk to this map's entrance, then press E or use this button."))); Row(Travel,B); }
        if(MapId<18) { UDigimonVenomNXTActionButton* B=Button(TEXT("USE EXIT — NEXT MAP"),TEXT("relaytravel"),MapId+1,true); B->SetIsEnabled(DigimonVenomNXTRelay::CanEnterMap(P,MapId+1)&&PC->CanUseRelayPortal(true)); B->SetToolTipText(FText::FromString(TEXT("Walk to the exit. Entering the next region requires this region's DigiBadge."))); Row(Travel,B); }
        { Add(Chapter,Button(TEXT("FIELD TRAINING — OPTIONAL WILD ENCOUNTER"),TEXT("relaytraining")),5); Add(Chapter,Text(WidgetTree,TEXT("Train at your own pace. Field training gives normal wild rewards and scan data; you may flee. Story battles begin only by speaking to their tamers."),12,Muted),2); }
    }
    if(InspectedMap>0&&InspectedMap!=P.MapId)Add(Content,Button(TEXT("BACK TO YOUR CURRENT CHAPTER"),TEXT("relayinspect"),P.MapId),4);
}

void UDigimonVenomNXTRelayWidget::BuildAtlas()
{
    using namespace DigimonRelayUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Relay;
    Add(Content,Text(WidgetTree,TEXT("THE ROAD TO THE RELAY SUMMIT"),19,Gold,true),4);
    Add(Content,Text(WidgetTree,TEXT("Travel between unlocked maps from this atlas, or walk through entrances and exits in your private campaign field. Story contacts lead the way; eight DigiBadge warden victories restore the relay."),13,Muted),4);
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bTravelAvailable=PC&&PC->IsInRelayCampaign()&&P.BattleCheckpointJson.IsEmpty();
    if(!PC||!PC->IsInRelayCampaign())Add(Content,Button(TEXT("ENTER / RESUME CAMPAIGN TO TRAVEL"),TEXT("relayenter"),0,true),4);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Content,Grid,5);
    int32 Index=0;
    for(const FDigimonRelayMap& Map:DigimonVenomNXTRelay::Maps())
    {
        const bool bUnlocked=DigimonVenomNXTRelay::CanEnterMap(P,Map.MapId); const bool bCurrent=Map.MapId==P.MapId;
        UBorder* C=Card(WidgetTree,bCurrent?Gold:bUnlocked?Cyan:Muted,9); UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); C->SetContent(V);
        UTexture2D* Art=UDigimonVenomNXTMapAssetRevision::LoadMapTexture(Map.SourceMapId);
        if(Art) { USizeBox* Image=DigimonVenomNXTUI::Texture(WidgetTree,Art,230,96); Image->SetRenderOpacity(bUnlocked?0.90f:0.25f); Add(V,Image,2); }
        Add(V,Text(WidgetTree,FString::Printf(TEXT("%02d  /  %s"),Map.MapId,bCurrent?TEXT("YOU ARE HERE"):bUnlocked?TEXT("OPEN"):TEXT("LOCKED")),10,bCurrent?Gold:bUnlocked?Cyan:Muted,true),2);
        Add(V,Text(WidgetTree,Map.Name,16,bUnlocked?White:Muted,true),3);
        Add(V,Text(WidgetTree,FString::Printf(TEXT("Lv.%d–%d  •  %s"),Map.MinLevel,Map.MaxLevel,Map.MapId==18?TEXT("Champion"):Map.MapId%2==0?TEXT("DigiBadge warden + story"):TEXT("Services + story + tamer")),11,Muted),3);
        Add(V,Button(TEXT("INSPECT CHAPTER"),TEXT("relayinspect"),Map.MapId,bCurrent),4);
        UDigimonVenomNXTActionButton* Travel=Button(bCurrent?TEXT("RETURN TO THIS MAP"):bUnlocked?TEXT("TRAVEL TO MAP"):TEXT("LOCKED — EARN THE PRECEDING BADGE"),TEXT("relayfasttravel"),Map.MapId,bCurrent);
        Travel->SetIsEnabled(bUnlocked&&bTravelAvailable);
        Travel->SetToolTipText(FText::FromString(!bUnlocked?TEXT("Earn the preceding region's DigiBadge to open this route."):!P.BattleCheckpointJson.IsEmpty()?TEXT("Resume your saved Relay battle before travelling."):TEXT("Travel within your own private campaign using your existing party.")));
        Add(V,Travel,3);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(C,Index/3,Index%3))S->SetHorizontalAlignment(HAlign_Fill);
        ++Index;
    }
}

void UDigimonVenomNXTRelayWidget::BuildBadges()
{
    using namespace DigimonRelayUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Relay;
    UVerticalBox* Collection=Section(WidgetTree,Content,TEXT("EIGHT DIGIBADGES  /  EIGHT RESTORED RELAY LINKS"),Gold);
    Add(Collection,Text(WidgetTree,TEXT("Every badge records a DigiBadge warden victory in your own story. Earn all eight and finish the route to face the level-96 Digimon Champion."),13,Muted),4);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(5)); Add(Collection,Grid,5);
    int32 Index=0;
    for(const FDigimonRelayMap& Map:DigimonVenomNXTRelay::Maps())for(const FDigimonRelayNPC& NPC:DigimonVenomNXTRelay::NPCsForMap(Map.MapId))
    {
        if(NPC.Role!=EDigimonRelayRole::Gym)continue;
        const bool bEarned=P.Badges.Contains(NPC.BadgeId); UBorder* C=Card(WidgetTree,bEarned?Gold:Muted,10); UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); C->SetContent(V);
        Add(V,Text(WidgetTree,NPC.BadgeName,13,bEarned?Gold:Muted,true),3);
        Add(V,Text(WidgetTree,bEarned?TEXT("EARNED"):TEXT("AWAITING YOUR VICTORY"),10,bEarned?Green:Muted,true),3);
        Add(V,Text(WidgetTree,Map.Name,12,White),2); Add(V,Text(WidgetTree,FString::Printf(TEXT("%s  •  Lv.%d"),*NPC.Name,NPC.Level),11,Muted),2);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(C,Index/4,Index%4))S->SetHorizontalAlignment(HAlign_Fill); ++Index;
    }
    UVerticalBox* Crown=Section(WidgetTree,Content,TEXT("THE CHAMPIONSHIP CONTINUES"),Gold);
    Add(Crown,Text(WidgetTree,P.bIsChampion?TEXT("YOUR TITLE. YOUR NEXT DEFENSE."):P.bEverChampion?TEXT("YOUR COMEBACK BEGINS HERE."):TEXT("EARN YOUR PLACE AT THE SUMMIT."),21,White,true),4);
    Add(Crown,Text(WidgetTree,P.bIsChampion?TEXT("You restored the relay and claimed the championship. Return to the summit and meet the challenger in person to defend your title. Your first championship completed the campaign; your reign can keep growing."):P.bEverChampion?TEXT("A lost title is a new chapter. Return to the summit and challenge for the crown again. Your completed story, badges and permanent FireWall Scan Mastery stay yours."):TEXT("A level-96 champion awaits at the end of the 18-map route. Bring your own party at its real strength, earn eight DigiBadges, and make the title yours."),14,Muted),4);
    Add(Crown,Text(WidgetTree,FString::Printf(TEXT("Championships %d   •   Successful defenses %d   •   Titles lost %d"),P.ChampionshipWins,P.Defenses,P.TitleLosses),13,Gold,true),5);
    UVerticalBox* Mastery=Section(WidgetTree,Content,P.bFirewallScanMastery?TEXT("FIREWALL SCAN MASTERY — PERMANENTLY UNLOCKED"):TEXT("FIRST-CHAMPIONSHIP REWARD"),P.bFirewallScanMastery?Green:Cyan);
    Add(Mastery,Text(WidgetTree,TEXT("+20% FIREWALL SCAN GAIN ON WILD VICTORY"),19,White,true),4);
    Add(Mastery,Text(WidgetTree,TEXT("Win your first Dawn Relay championship to permanently gain 20% more scan data when you win a wild battle against a FireWall Digimon (normally 5% to 6%). Losing your title never removes it."),13,Muted),3);
}
