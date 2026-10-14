#include "DigimonVenomNXTChroniclesWidget.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTChronicles.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "Engine/GameInstance.h"
#include "DigimonVenomNXTPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
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

namespace DigimonChroniclesUI
{
    constexpr EDigimonPrivateCampaign Campaign = EDigimonPrivateCampaign::ParadoxChronicles;
    const FLinearColor Violet(0.72f,0.48f,1.0f,1);
    const FLinearColor Cyan(0.25f,0.9f,1.0f,1);
    const FLinearColor Gold(1.0f,0.77f,0.38f,1);
    const FLinearColor White(0.94f,0.97f,1,1);
    const FLinearColor Muted(0.65f,0.72f,0.85f,1);
    const FLinearColor Green(0.53f,0.95f,0.72f,1);
    UTextBlock* Text(UWidgetTree* Tree,const FString& Value,int32 Size=13,FLinearColor Color=White,bool bBold=false)
    {
        UTextBlock* W=Tree->ConstructWidget<UTextBlock>(); W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font=W->GetFont(); Font.Size=Size; Font.TypefaceFontName=bBold?FName(TEXT("Bold")):FName(TEXT("Regular")); W->SetFont(Font); return W;
    }
    void Add(UVerticalBox* Box,UWidget* W,float Pad=3)
    { if(UVerticalBoxSlot* S=Box->AddChildToVerticalBox(W)) { S->SetPadding(FMargin(0,Pad)); S->SetHorizontalAlignment(HAlign_Fill); } }
    void Row(UHorizontalBox* Box,UWidget* W)
    { if(UHorizontalBoxSlot* S=Box->AddChildToHorizontalBox(W)) { S->SetPadding(FMargin(4,0)); S->SetVerticalAlignment(VAlign_Center); S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); } }
    UBorder* Card(UWidgetTree* Tree,FLinearColor Accent=Violet,float Pad=12)
    { UBorder* B=Tree->ConstructWidget<UBorder>(); B->SetBrush(FSlateRoundedBoxBrush(FLinearColor(0.018f,0.018f,0.055f,0.97f),8.0f,Accent.CopyWithNewOpacity(0.4f),1)); B->SetPadding(FMargin(Pad)); return B; }
    UVerticalBox* Section(UWidgetTree* Tree,UVerticalBox* Parent,const FString& Heading,FLinearColor Accent=Violet)
    { UBorder* B=Card(Tree,Accent); Add(Parent,B,5); UVerticalBox* V=Tree->ConstructWidget<UVerticalBox>(); B->SetContent(V); Add(V,Text(Tree,Heading,11,Accent,true),3); return V; }
    void Emblem(UWidgetTree* Tree,UVerticalBox* Parent,const FString& Asset,float Size,bool bEarned=true)
    {
        UBorder* Seal=Card(Tree,bEarned?Violet:Muted,12);
        UTextBlock* Label=Text(Tree,Asset.Contains(TEXT("Mastery"))?TEXT("+20%"):TEXT("CREST"),18,bEarned?White:Muted,true);
        Label->SetJustification(ETextJustify::Center); Seal->SetContent(Label);
        if(UVerticalBoxSlot* S=Parent->AddChildToVerticalBox(Seal)) { S->SetHorizontalAlignment(HAlign_Center); S->SetPadding(FMargin(3)); }
    }
    FString ContactRole(EDigimonRelayRole Value)
    {
        switch(Value) {
        case EDigimonRelayRole::Quest:return TEXT("QUEST CONTACT");
        case EDigimonRelayRole::Healer:return TEXT("PARTY CARE");
        case EDigimonRelayRole::Shop:return TEXT("SUPPLIES");
        case EDigimonRelayRole::Tamer:return TEXT("FIELD TRIAL");
        case EDigimonRelayRole::ParadoxBoss:return TEXT("PARADOX GUARDIAN");
        case EDigimonRelayRole::FinalBoss:return TEXT("FINAL SUMMONER");
        default:return TEXT("STORY CONTACT"); }
    }
}

TSharedRef<SWidget> UDigimonVenomNXTChroniclesWidget::RebuildWidget() { BuildLayout(); return Super::RebuildWidget(); }

UDigimonVenomNXTActionButton* UDigimonVenomNXTChroniclesWidget::Button(const FString& Label,const FString& Action,int32 Payload,bool bHighlight)
{
    UDigimonVenomNXTActionButton* B=WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(B,bHighlight?DigimonChroniclesUI::Gold:DigimonChroniclesUI::Violet); B->InitializeAction(Action,Payload);
    B->OnAction.AddDynamic(this,&UDigimonVenomNXTChroniclesWidget::HandleAction);
    UTextBlock* T=DigimonChroniclesUI::Text(WidgetTree,Label,12,DigimonChroniclesUI::White,true); T->SetJustification(ETextJustify::Center); B->SetContent(T); B->SetToolTipText(FText::FromString(Label)); return B;
}

void UDigimonVenomNXTChroniclesWidget::BuildLayout()
{
    if(Root)return;
    if(!WidgetTree)WidgetTree=NewObject<UWidgetTree>(this,TEXT("ChroniclesWidgetTree"));
    using namespace DigimonChroniclesUI;
    Root=WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget=Root;
    UBorder* Hero=Card(WidgetTree,Violet,0); Add(Root,Hero,0);
    UOverlay* Layers=WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(Layers);
    UVerticalBox* Words=WidgetTree->ConstructWidget<UVerticalBox>();
    if(UOverlaySlot* S=Layers->AddChildToOverlay(Words))S->SetPadding(FMargin(22,20));
    Add(Words,Text(WidgetTree,TEXT("PRIVATE CAMPAIGN  /  ONE TAMER. SEVENTEEN FRACTURES."),10,Cyan,true),2);
    Add(Words,Text(WidgetTree,TEXT("WORLD DS: PARADOX CHRONICLE"),30,White,true),2);
    Add(Words,Text(WidgetTree,TEXT("Bring the lost moments home."),16,Gold,true),3);
    StatusText=Text(WidgetTree,TEXT("Synchronizing your chronicle..."),12,White); Add(Words,StatusText,5);
    CrestMeter=WidgetTree->ConstructWidget<UProgressBar>(); CrestMeter->SetFillColorAndOpacity(Violet);
    USizeBox* Bar=WidgetTree->ConstructWidget<USizeBox>(); Bar->SetHeightOverride(5); Bar->AddChild(CrestMeter); Add(Words,Bar,4);
    UHorizontalBox* Nav=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root,Nav,9);
    const TCHAR* Labels[]={TEXT("QUEST JOURNAL"),TEXT("18-MAP EXPEDITION"),TEXT("17 CRESTS & MASTERY")};
    for(int32 I=0;I<3;++I) { UDigimonVenomNXTActionButton* B=Button(Labels[I],TEXT("chroniclestab"),I,I==2); Tabs.Add(B); Row(Nav,B); }
    Content=WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root,Content,0);
}

void UDigimonVenomNXTChroniclesWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState)
{
    if(PlayerState&&PlayerState->Profile.Chronicles.MapId!=LastProfileMap)
    { LastProfileMap=PlayerState->Profile.Chronicles.MapId; InspectedMap=0; }
    BoundPlayer=PlayerState; BuildLayout(); RefreshContent();
}

void UDigimonVenomNXTChroniclesWidget::HandleAction(const FString& Action,int32 Payload)
{
    if(Action==TEXT("chroniclestab")) { ActiveTab=FMath::Clamp(Payload,0,2); RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); return; }
    if(Action==TEXT("chroniclesinspect")) { InspectedMap=Payload; ActiveTab=0; RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); return; }
    OnAction.Broadcast(Action,Payload);
}

void UDigimonVenomNXTChroniclesWidget::RefreshContent()
{
    using namespace DigimonChroniclesUI;
    if(!Content)return; Content->ClearChildren();
    for(int32 I=0;I<Tabs.Num();++I)DigimonVenomNXTUI::StyleButton(Tabs[I],I==2?Gold:Violet,I==ActiveTab);
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get();
    if(!PS) { Add(Content,Text(WidgetTree,TEXT("Your saved chronicle will appear once your account finishes synchronizing."),14,Muted)); return; }
    const auto& P=PS->Profile.Chronicles;
    StatusText->SetText(FText::FromString(FString::Printf(TEXT("%s  •  Map %02d / 18  •  %d / 17 Paradox Crests  •  %s"),*PS->Profile.Username,P.MapId,P.Badges.Num(),P.bComplete?TEXT("CHRONICLE RESTORED"):TEXT("EXPEDITION IN PROGRESS"))));
    CrestMeter->SetPercent(FMath::Clamp(P.Badges.Num()/17.0f,0.0f,1.0f));
    if(ActiveTab==1)BuildAtlas(); else if(ActiveTab==2)BuildCrests(); else BuildJournal();
}

void UDigimonVenomNXTChroniclesWidget::BuildJournal()
{
    using namespace DigimonChroniclesUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Chronicles;
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bInField=PC&&PC->IsInChronicles();
    const bool bSuspended=!P.BattleCheckpointJson.IsEmpty();
    UVerticalBox* Next=Section(WidgetTree,Content,TEXT("YOUR NEXT STEP"),Gold);
    Add(Next,Text(WidgetTree,DigimonVenomNXTCampaign::Objective(Campaign,P),18,White,true),4);
    Add(Next,Text(WidgetTree,TEXT("Explore at your own pace. Walk to a named contact and press E. Accept their assignment, win the field trial, return to report, then face the map's Paradox guardian. Every crest opens the next map."),13,Muted),4);
    if(bSuspended)
    {
        Add(Next,Text(WidgetTree,TEXT("Your battle is saved at its last confirmed turn. Resume this chronicle before changing your party or travelling."),13,Gold,true),4);
        Add(Next,Button(TEXT("RESUME SAVED CHRONICLES BATTLE"),TEXT("chroniclesresume"),0,true),4);
    }
    UHorizontalBox* Actions=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Next,Actions,6);
    Row(Actions,Button(bInField?TEXT("RETURN TO YOUR PRIVATE FIELD"):TEXT("ENTER / RESUME YOUR CHRONICLE"),TEXT("chroniclesenter"),0,true));
    if(bInField&&!bSuspended)Row(Actions,Button(TEXT("SAVE & RETURN TO PUBLIC WORLD"),TEXT("relayleave")));
    UVerticalBox* Carry=Section(WidgetTree,Content,TEXT("YOUR PARTY. YOUR PROGRESS."),Cyan);
    Add(Carry,Text(WidgetTree,TEXT("Bring your existing partners at their real levels and stats. Keep using DigiLab, DigiFarm, shops, inventory, Credits and DigiRubies. Dawn Story, World DS and Super Xros Wars each keep separate saved progress."),13,Muted),3);
    UHorizontalBox* Services=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Carry,Services,5); Services->SetIsEnabled(!bSuspended);
    Row(Services,Button(TEXT("PARTY"),TEXT("page:Party"))); Row(Services,Button(TEXT("DIGILAB"),TEXT("page:DigiLab"))); Row(Services,Button(TEXT("DIGIFARM"),TEXT("page:DigiFarm"))); Row(Services,Button(TEXT("SHOP & SUPPLIES"),TEXT("page:Shop")));
    const int32 MapId=InspectedMap>0?InspectedMap:P.MapId;
    const FDigimonRelayMap* Map=DigimonVenomNXTCampaign::GetMap(Campaign,MapId); if(!Map)return;
    const bool bUnlocked=DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,MapId);
    UVerticalBox* Chapter=Section(WidgetTree,Content,FString::Printf(TEXT("MAP %02d  /  %s"),MapId,MapId==P.MapId?TEXT("CURRENT CHAPTER"):TEXT("CHAPTER PREVIEW")));
    Add(Chapter,Text(WidgetTree,Map->Name,23,White,true),3);
    Add(Chapter,Text(WidgetTree,Map->Subtitle,14,Gold,true),3);
    Add(Chapter,Text(WidgetTree,Map->Intro,14,White),5);
    Add(Chapter,Text(WidgetTree,MapId==1?TEXT("SAFE HUB  •  Story contacts, party care and supplies"):FString::Printf(TEXT("Recommended Lv.%d–%d  •  %s"),Map->MinLevel,Map->MaxLevel,bUnlocked?TEXT("Route unlocked"):TEXT("Earn the preceding guardian's crest to unlock")),12,Muted),4);
    if(MapId>1)
    {
        const auto Contacts=DigimonVenomNXTCampaign::NPCsForMap(Campaign,MapId);
        const FDigimonRelayNPC* Quest=Contacts.FindByPredicate([](const FDigimonRelayNPC& N){return N.Role==EDigimonRelayRole::Quest;});
        const FDigimonRelayNPC* Guardian=Contacts.FindByPredicate([](const FDigimonRelayNPC& N){return N.Role==EDigimonRelayRole::ParadoxBoss;});
        if(Quest)
        {
            const bool bAccepted=P.AcceptedQuests.Contains(Quest->QuestId);
            const bool bTrial=DigimonVenomNXTChronicles::QuestObjectiveCount(P,Quest->QuestId)>=FMath::Max(1,Quest->QuestTarget);
            const bool bReported=P.CompletedObjectives.Contains(Quest->QuestId);
            const bool bCrest=Guardian&&P.Badges.Contains(Guardian->BadgeId);
            auto Step=[&](int32 Number,const FString& Label,bool bDone,bool bNext)
            { Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("%s  %d. %s"),bDone?TEXT("COMPLETE"):bNext?TEXT("NEXT"):TEXT("PENDING"),Number,*Label),13,bDone?Green:bNext?Gold:Muted,bDone||bNext),4); };
            Step(1,FString::Printf(TEXT("Accept the assignment from %s"),*Quest->Name),bAccepted||bReported,!bAccepted&&!bReported);
            const FDigimonRelayNPC* Trial=DigimonVenomNXTCampaign::GetNPC(Campaign,Quest->Prerequisite);
            Step(2,Trial?FString::Printf(TEXT("Win %s's field trial"),*Trial->Name):TEXT("Win the field trial"),bTrial||bReported,bAccepted&&!bTrial&&!bReported);
            Step(3,FString::Printf(TEXT("Return to %s and report your findings"),*Quest->Name),bReported,bTrial&&!bReported);
            Step(4,Guardian?FString::Printf(TEXT("Defeat %s and earn %s"),*Guardian->Name,*Guardian->BadgeName):TEXT("Defeat the Paradox guardian"),bCrest,bReported&&!bCrest);
        }
    }
    for(const FDigimonRelayNPC& NPC:DigimonVenomNXTCampaign::NPCsForMap(Campaign,MapId))
    {
        if(NPC.Role==EDigimonRelayRole::FinalBoss)continue;
        const bool bDone=NPC.Role==EDigimonRelayRole::Quest?P.CompletedObjectives.Contains(NPC.QuestId):NPC.Role==EDigimonRelayRole::Guide?P.CompletedObjectives.Contains(NPC.Id):P.DefeatedTamers.Contains(NPC.Id);
        Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("%s  •  %s%s%s"),*ContactRole(NPC.Role),*NPC.Name,DigimonVenomNXTCampaign::IsBattleRole(NPC.Role)?*FString::Printf(TEXT("  /  Lv.%d"),NPC.Level):TEXT(""),bDone?TEXT("  /  COMPLETE"):TEXT("")),12,bDone?Green:Muted),3);
    }
    if(MapId==18)
    {
        Add(Chapter,Text(WidgetTree,TEXT("THE FINAL SUMMONING"),12,Gold,true),8);
        Add(Chapter,Text(WidgetTree,P.bComplete?TEXT("The Paradox Triad is defeated. Your restored chronicle and permanent Paradox Scan Mastery remain yours."):TEXT("Earn all 17 guardian crests, then meet the final summoner here. Your last fight is a team of three level-100 Paradox Mega Digimon. Winning restores the chronicle and unlocks permanent Paradox Scan Mastery."),14,White),4);
    }
    if(bInField&&MapId==P.MapId&&!bSuspended)
    {
        UHorizontalBox* Travel=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Chapter,Travel,7);
        if(MapId>1) { UDigimonVenomNXTActionButton* B=Button(TEXT("ENTRANCE — PREVIOUS MAP"),TEXT("relaytravel"),MapId-1); B->SetIsEnabled(PC->CanUseRelayPortal(false)); B->SetToolTipText(FText::FromString(TEXT("Walk to the entrance, then press E or use this button."))); Row(Travel,B); }
        if(MapId<18) { UDigimonVenomNXTActionButton* B=Button(TEXT("EXIT — NEXT MAP"),TEXT("relaytravel"),MapId+1,true); B->SetIsEnabled(DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,MapId+1)&&PC->CanUseRelayPortal(true)); B->SetToolTipText(FText::FromString(TEXT("Complete the chapter, then walk to the exit."))); Row(Travel,B); }
        if(MapId>1) { Add(Chapter,Button(TEXT("OPTIONAL WILD FIELD TRAINING"),TEXT("relaytraining")),5); Add(Chapter,Text(WidgetTree,TEXT("Normal wild rewards and scan data; fleeing is allowed. Wild training does not replace the named story trial or guardian battle."),12,Muted),3); }
    }
    if(InspectedMap>0&&InspectedMap!=P.MapId)Add(Content,Button(TEXT("BACK TO YOUR CURRENT CHAPTER"),TEXT("chroniclesinspect"),P.MapId),4);
}

void UDigimonVenomNXTChroniclesWidget::BuildAtlas()
{
    using namespace DigimonChroniclesUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Chronicles;
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bCanTravel=PC&&PC->IsInChronicles()&&P.BattleCheckpointJson.IsEmpty();
    Add(Content,Text(WidgetTree,TEXT("ONE SAFE HAVEN. SEVENTEEN FRACTURED WORLDS."),19,Gold,true),4);
    Add(Content,Text(WidgetTree,TEXT("Choose a chapter to read its story and quest steps. Travel to any unlocked map within your own expedition, or explore through its entrances and exits. Other players cannot enter your campaign."),13,Muted),4);
    if(!PC||!PC->IsInChronicles())Add(Content,Button(TEXT("ENTER / RESUME CHRONICLES TO TRAVEL"),TEXT("chroniclesenter"),0,true),4);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Content,Grid,5);
    int32 Index=0;
    for(const FDigimonRelayMap& Map:DigimonVenomNXTCampaign::Maps(Campaign))
    {
        const bool bUnlocked=DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,Map.MapId),bCurrent=Map.MapId==P.MapId;
        UBorder* C=Card(WidgetTree,bCurrent?Gold:bUnlocked?Violet:Muted,9); UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); C->SetContent(V);
        if(UTexture2D* Texture=UDigimonVenomNXTMapAssetRevision::LoadMapTexture(Map.SourceMapId))
        { USizeBox* Image=DigimonVenomNXTUI::Texture(WidgetTree,Texture,226,90); Image->SetRenderOpacity(bUnlocked?0.9f:0.24f); Add(V,Image,2); }
        Add(V,Text(WidgetTree,FString::Printf(TEXT("%02d  /  %s"),Map.MapId,bCurrent?TEXT("CURRENT CHAPTER"):bUnlocked?TEXT("OPEN"):TEXT("LOCKED")),10,bCurrent?Gold:bUnlocked?Cyan:Muted,true),2);
        Add(V,Text(WidgetTree,Map.Name,15,bUnlocked?White:Muted,true),3);
        Add(V,Text(WidgetTree,Map.MapId==1?TEXT("SAFE HUB  •  NO BATTLES"):FString::Printf(TEXT("Lv.%d–%d  •  Quest / trial / guardian%s"),Map.MinLevel,Map.MaxLevel,Map.MapId==18?TEXT(" / final"):TEXT("")),11,Muted),3);
        Add(V,Button(TEXT("VIEW CHAPTER & QUEST"),TEXT("chroniclesinspect"),Map.MapId,bCurrent),4);
        UDigimonVenomNXTActionButton* Travel=Button(bCurrent?TEXT("RETURN TO THIS MAP"):bUnlocked?TEXT("TRAVEL TO MAP"):TEXT("LOCKED — PREVIOUS CREST REQUIRED"),TEXT("relayfasttravel"),Map.MapId,bCurrent);
        Travel->SetIsEnabled(bUnlocked&&bCanTravel); Add(V,Travel,3);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(C,Index/3,Index%3))S->SetHorizontalAlignment(HAlign_Fill); ++Index;
    }
}

void UDigimonVenomNXTChroniclesWidget::BuildCrests()
{
    using namespace DigimonChroniclesUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.Chronicles;
    UVerticalBox* Collection=Section(WidgetTree,Content,TEXT("SEVENTEEN PARADOX CRESTS"),Gold);
    Add(Collection,Text(WidgetTree,TEXT("One crest for each guardian you free. Your collection is saved with this chronicle. All seventeen are required before the final summoner can open the last battle."),13,Muted),4);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Collection,Grid,5);
    int32 Index=0;
    for(const FDigimonRelayMap& Map:DigimonVenomNXTCampaign::Maps(Campaign))for(const FDigimonRelayNPC& NPC:DigimonVenomNXTCampaign::NPCsForMap(Campaign,Map.MapId))
    {
        if(NPC.Role!=EDigimonRelayRole::ParadoxBoss)continue;
        const bool bEarned=P.Badges.Contains(NPC.BadgeId); UBorder* C=Card(WidgetTree,bEarned?Violet:Muted,9); UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); C->SetContent(V);
        Emblem(WidgetTree,V,TEXT("T_ParadoxCrest"),75,bEarned);
        Add(V,Text(WidgetTree,FString::Printf(TEXT("CREST %02d  /  %s"),Index+1,bEarned?TEXT("RESTORED"):TEXT("UNCLAIMED")),10,bEarned?Green:Muted,true),3);
        Add(V,Text(WidgetTree,NPC.BadgeName,13,bEarned?White:Muted,true),3);
        Add(V,Text(WidgetTree,Map.Name,11,Muted),2);
        Add(V,Text(WidgetTree,FString::Printf(TEXT("%s  •  Lv.%d"),*NPC.Name,NPC.Level),11,Muted),2);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(C,Index/4,Index%4))S->SetHorizontalAlignment(HAlign_Fill); ++Index;
    }
    UVerticalBox* Finale=Section(WidgetTree,Content,P.bComplete?TEXT("THE CHRONICLE IS RESTORED"):TEXT("THE PARADOX TRIAD"),Gold);
    Add(Finale,Text(WidgetTree,P.bComplete?TEXT("YOU BROUGHT THE LOST MOMENTS HOME."):TEXT("THREE PARADOX MEGAS. LEVEL 100."),21,White,true),4);
    Add(Finale,Text(WidgetTree,P.bComplete?TEXT("Your tamer's story is complete, and the worlds you restored remain open to explore. Your mastery is permanent."):P.Badges.Num()>=17?TEXT("Your crest collection is complete. Return to map 18 and speak to the final summoner in person. Prepare your real party, restore its HP and SP, and face the three-member Paradox Mega team."):TEXT("Complete every local assignment and defeat all seventeen guardians. With the full crest collection, meet the final summoner on map 18 to challenge the three-member level-100 Paradox Mega team."),14,Muted),4);
    const auto FinalContacts=DigimonVenomNXTCampaign::NPCsForMap(Campaign,18);
    const FDigimonRelayNPC* Final=FinalContacts.FindByPredicate([](const FDigimonRelayNPC& N){return N.Role==EDigimonRelayRole::FinalBoss;});
    if(Final)
    {
        UDigimonVenomNXTDataSubsystem* Data=GetGameInstance()?GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>():nullptr;
        UHorizontalBox* Team=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Finale,Team,6);
        for(int32 PartnerIndex=0;PartnerIndex<Final->TeamSpecies.Num();++PartnerIndex)
        {
            UVerticalBox* Partner=WidgetTree->ConstructWidget<UVerticalBox>();
            USizeBox* Portrait=DigimonVenomNXTUI::AnimatedPortrait(WidgetTree,Final->TeamSpecies[PartnerIndex],EDigimonVariant::Paradox,104,104);
            if(UVerticalBoxSlot* S=Partner->AddChildToVerticalBox(Portrait))S->SetHorizontalAlignment(HAlign_Center);
            FDigimonSpeciesDefinition Definition;
            const FString Display=Data&&Data->GetSpecies(Final->TeamSpecies[PartnerIndex],Definition)?Definition.DisplayName.ToString():FString::Printf(TEXT("Paradox Mega %d"),PartnerIndex+1);
            Add(Partner,Text(WidgetTree,Display,13,White,true),3);
            Add(Partner,Text(WidgetTree,TEXT("PARADOX  /  MEGA  /  LV.100"),10,Violet,true),2);
            Row(Team,Partner);
        }
    }
    UVerticalBox* Mastery=Section(WidgetTree,Content,P.bParadoxScanMastery?TEXT("PARADOX SCAN MASTERY — PERMANENTLY UNLOCKED"):TEXT("CAMPAIGN COMPLETION REWARD"),P.bParadoxScanMastery?Green:Violet);
    Emblem(WidgetTree,Mastery,TEXT("T_ParadoxMastery"),96);
    Add(Mastery,Text(WidgetTree,TEXT("+20% PARADOX SCAN GAIN ON WILD VICTORY"),19,White,true),4);
    Add(Mastery,Text(WidgetTree,TEXT("Win the final Paradox Triad battle to permanently gain 20% more Paradox scan data from eligible wild victories (normally 5% to 6%). It stays unlocked across the world and all campaigns."),13,Muted),4);
    Add(Mastery,Text(WidgetTree,PS->Profile.Relay.bFirewallScanMastery?TEXT("RELAY REWARD ALSO UNLOCKED  •  FireWall Scan Mastery grants +20% scan gain per eligible FireWall wild victory."):TEXT("A SEPARATE REWARD  •  Win your first Relay championship to unlock permanent +20% FireWall scan gain per eligible wild victory."),12,Gold,true),5);
}
