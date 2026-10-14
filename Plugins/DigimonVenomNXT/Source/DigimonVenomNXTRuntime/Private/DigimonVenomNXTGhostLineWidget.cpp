#include "DigimonVenomNXTGhostLineWidget.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "Engine/GameInstance.h"
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

namespace DigimonGhostLineUI
{
    constexpr EDigimonPrivateCampaign Campaign = EDigimonPrivateCampaign::GhostLine;
    const FLinearColor Cyan(.25f,.92f,.93f,1);
    const FLinearColor Amber(1,.72f,.32f,1);
    const FLinearColor White(.94f,.98f,1,1);
    const FLinearColor Muted(.65f,.75f,.8f,1);
    const FLinearColor Green(.48f,.94f,.70f,1);
    UTextBlock* Text(UWidgetTree* Tree,const FString& Value,int32 Size=13,FLinearColor Color=White,bool bBold=false)
    {
        UTextBlock* W=Tree->ConstructWidget<UTextBlock>(); W->SetText(FText::FromString(Value)); W->SetColorAndOpacity(Color); W->SetAutoWrapText(true);
        FSlateFontInfo Font=W->GetFont(); Font.Size=Size; Font.TypefaceFontName=bBold?FName(TEXT("Bold")):FName(TEXT("Regular")); W->SetFont(Font); return W;
    }
    void Add(UVerticalBox* Box,UWidget* W,float Pad=3)
    { if(UVerticalBoxSlot* S=Box->AddChildToVerticalBox(W)) { S->SetPadding(FMargin(0,Pad)); S->SetHorizontalAlignment(HAlign_Fill); } }
    void Row(UHorizontalBox* Box,UWidget* W)
    { if(UHorizontalBoxSlot* S=Box->AddChildToHorizontalBox(W)) { S->SetPadding(FMargin(4,0)); S->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); S->SetVerticalAlignment(VAlign_Center); } }
    UBorder* Card(UWidgetTree* Tree,FLinearColor Accent=Cyan,float Pad=13)
    { UBorder* B=Tree->ConstructWidget<UBorder>(); B->SetBrush(FSlateRoundedBoxBrush(FLinearColor(.011f,.030f,.046f,.98f),8,Accent.CopyWithNewOpacity(.42f),1)); B->SetPadding(FMargin(Pad)); return B; }
    UVerticalBox* Section(UWidgetTree* Tree,UVerticalBox* Parent,const FString& Heading,FLinearColor Accent=Cyan)
    { UBorder* B=Card(Tree,Accent); Add(Parent,B,5); UVerticalBox* V=Tree->ConstructWidget<UVerticalBox>(); B->SetContent(V); Add(V,Text(Tree,Heading,11,Accent,true),3); return V; }
    void Availability(UDigimonVenomNXTActionButton* B,bool bEnabled,const FString& Reason)
    { B->SetIsEnabled(bEnabled); if(!Reason.IsEmpty())B->SetToolTipText(FText::FromString(Reason)); }
    const FDigimonRelayNPC* QuestFor(int32 MapId)
    { for(const FDigimonRelayNPC& N:DigimonVenomNXTCampaign::NPCs(Campaign))if(N.MapId==MapId&&N.Role==EDigimonRelayRole::Quest)return &N; return nullptr; }
    bool ReportFiled(const FDigimonRelayProgress& P,const FDigimonRelayNPC& Quest)
    { return Quest.Role==EDigimonRelayRole::Quest && P.CompletedObjectives.Contains(Quest.QuestId) && P.Badges.Contains(Quest.BadgeId); }
    int32 Proofs(const FDigimonRelayProgress& P)
    {
        int32 Count=0;
        for(const FDigimonRelayNPC& Quest:DigimonVenomNXTCampaign::NPCs(Campaign))if(ReportFiled(P,Quest))++Count;
        return Count;
    }
    bool Suspended(const FDigimonRelayProgress& P)
    { return !P.BattleCheckpointJson.IsEmpty() || P.PendingBattleId.IsValid(); }
}

TSharedRef<SWidget> UDigimonVenomNXTGhostLineWidget::RebuildWidget() { BuildLayout(); return Super::RebuildWidget(); }

UDigimonVenomNXTActionButton* UDigimonVenomNXTGhostLineWidget::Button(const FString& Label,const FString& Action,int32 Payload,bool bHighlight)
{
    using namespace DigimonGhostLineUI;
    UDigimonVenomNXTActionButton* B=WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    DigimonVenomNXTUI::StyleButton(B,bHighlight?Amber:Cyan); B->InitializeAction(Action,Payload); B->OnAction.AddDynamic(this,&UDigimonVenomNXTGhostLineWidget::HandleAction);
    UTextBlock* Caption=Text(WidgetTree,Label,12,White,true); Caption->SetJustification(ETextJustify::Center); B->SetContent(Caption); B->SetToolTipText(FText::FromString(Label)); return B;
}

void UDigimonVenomNXTGhostLineWidget::BuildLayout()
{
    if(Root)return;
    if(!WidgetTree)WidgetTree=NewObject<UWidgetTree>(this,TEXT("GhostLineWidgetTree"));
    using namespace DigimonGhostLineUI;
    Root=WidgetTree->ConstructWidget<UVerticalBox>(); WidgetTree->RootWidget=Root;
    UBorder* Hero=Card(WidgetTree,Cyan,0); Add(Root,Hero,0);
    UOverlay* Layers=WidgetTree->ConstructWidget<UOverlay>(); Hero->SetContent(Layers);
    UVerticalBox* Words=WidgetTree->ConstructWidget<UVerticalBox>();
    if(UOverlaySlot* S=Layers->AddChildToOverlay(Words))S->SetPadding(FMargin(22,20));
    Add(Words,Text(WidgetTree,TEXT("PRIVATE CAMPAIGN  /  CYBERSPACE CASE FILES"),10,Cyan,true),2);
    Add(Words,Text(WidgetTree,TEXT("SUPER XROS: GHOSTLINE"),32,White,true),2);
    Add(Words,Text(WidgetTree,TEXT("Every connection leaves a trace."),16,Amber,true),3);
    Add(Words,Text(WidgetTree,TEXT("Follow a trusted friend's leads through 30 investigations. Preserve the evidence. Find who is really writing the commands."),13,White),4);
    StatusText=Text(WidgetTree,TEXT("Synchronizing your case archive..."),12,White); Add(Words,StatusText,4);
    ProofMeter=WidgetTree->ConstructWidget<UProgressBar>(); ProofMeter->SetFillColorAndOpacity(Cyan);
    USizeBox* Bar=WidgetTree->ConstructWidget<USizeBox>(); Bar->SetHeightOverride(5); Bar->AddChild(ProofMeter); Add(Words,Bar,4);
    UHorizontalBox* Nav=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Root,Nav,9);
    const TCHAR* Labels[]={TEXT("CASE BOARD"),TEXT("31-MAP NETWORK"),TEXT("EVIDENCE & MASTERY")};
    for(int32 I=0;I<3;++I) { UDigimonVenomNXTActionButton* B=Button(Labels[I],TEXT("ghostlinetab"),I); Tabs.Add(B); Row(Nav,B); }
    Content=WidgetTree->ConstructWidget<UVerticalBox>(); Add(Root,Content,0);
}

void UDigimonVenomNXTGhostLineWidget::RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState)
{
    if(PlayerState&&LastProfileMap!=PlayerState->Profile.GhostLine.MapId) { LastProfileMap=PlayerState->Profile.GhostLine.MapId; InspectedMap=0; }
    BoundPlayer=PlayerState; BuildLayout(); RefreshContent();
}

void UDigimonVenomNXTGhostLineWidget::HandleAction(const FString& Action,int32 Payload)
{
    if(Action==TEXT("ghostlinetab")) { ActiveTab=FMath::Clamp(Payload,0,2); RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); return; }
    if(Action==TEXT("ghostlineinspect"))
    {
        const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get();
        if(PS&&DigimonVenomNXTCampaign::CanEnterMap(DigimonGhostLineUI::Campaign,PS->Profile.GhostLine,Payload)) { InspectedMap=Payload; ActiveTab=0; RefreshContent(); OnAction.Broadcast(TEXT("campaignscrolltop"),0); }
        return;
    }
    OnAction.Broadcast(Action,Payload);
}

void UDigimonVenomNXTGhostLineWidget::RefreshContent()
{
    using namespace DigimonGhostLineUI;
    if(!Content)return; Content->ClearChildren();
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get();
    if(!PS) { Add(Content,Text(WidgetTree,TEXT("Connecting to your private case archive..."),15,Muted)); return; }
    const auto& P=PS->Profile.GhostLine; const int32 Count=Proofs(P);
    StatusText->SetText(FText::FromString(FString::Printf(TEXT("%s  •  %02d / 30 ACCESS PROOFS  •  %s"),P.bComplete?TEXT("CASE CLOSED"):TEXT("INVESTIGATION IN PROGRESS"),Count,P.bShinyScanMastery?TEXT("SHINY MASTERY ACTIVE"):TEXT("YOUR ACCOUNT'S SAVED JOURNEY"))));
    ProofMeter->SetPercent(Count/30.0f);
    for(int32 I=0;I<Tabs.Num();++I)DigimonVenomNXTUI::StyleButton(Tabs[I],Cyan,I==ActiveTab);
    if(ActiveTab==1)BuildNetworkMap(); else if(ActiveTab==2)BuildEvidence(); else BuildCaseBoard();
}

void UDigimonVenomNXTGhostLineWidget::BuildCaseBoard()
{
    using namespace DigimonGhostLineUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return;
    const auto& P=PS->Profile.GhostLine; ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bInField=PC&&PC->IsInGhostLine(),bSaved=Suspended(P),bOtherBattle=DigimonVenomNXTCampaign::HasOtherPendingBattle(PS->Profile,Campaign);
    UVerticalBox* Next=Section(WidgetTree,Content,P.bComplete?TEXT("CASE CLOSED  /  THE NETWORK IS YOURS TO REVISIT"):TEXT("YOUR NEXT LEAD"),Amber);
    Add(Next,Text(WidgetTree,DigimonVenomNXTCampaign::Objective(Campaign,P),18,White,true),4);
    Add(Next,Text(WidgetTree,TEXT("Walk to your contact and press E. Open the case, win its named tamer trial, then return to confirm the report. Each ordinary case opens the next route; the final archive review unlocks the last confrontation."),13,Muted),4);
    if(bSaved) { Add(Next,Text(WidgetTree,TEXT("A battle is saved at its last confirmed turn. Resume it before changing your party, shopping or travelling."),13,Amber,true),3); Add(Next,Button(TEXT("RESUME SAVED GHOSTLINE BATTLE"),TEXT("ghostlineresume"),0,true),4); }
    if(bOtherBattle)Add(Next,Text(WidgetTree,TEXT("Another campaign has a saved battle. Resume that journey first; your Super Xros Wars progress is safe."),13,Amber,true),4);
    UHorizontalBox* Actions=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Next,Actions,5);
    UDigimonVenomNXTActionButton* Enter=Button(bInField?TEXT("RETURN TO YOUR PRIVATE FIELD"):TEXT("ENTER / RESUME GHOSTLINE"),TEXT("ghostlineenter"),0,true); Row(Actions,Enter);
    Availability(Enter,!bOtherBattle,bOtherBattle?TEXT("Finish the saved battle in your other campaign first."):TEXT("Explore with your existing party at its real strength."));
    if(bInField&&!bSaved)Row(Actions,Button(TEXT("SAVE & RETURN TO PUBLIC WORLD"),TEXT("relayleave")));
    UVerticalBox* Carry=Section(WidgetTree,Content,TEXT("YOUR TAMER. YOUR REAL TEAM."));
    Add(Carry,Text(WidgetTree,TEXT("Your levels, stats, HP and SP carry into every trial. DigiLab, DigiFarm, inventory, shops, Credits and DigiRubies remain yours. Each of the three campaigns keeps independent saved progress."),13,Muted),3);
    UHorizontalBox* Services=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Carry,Services,5);
    for(const auto& Service:TArray<TPair<FString,FString>>{{TEXT("PARTY"),TEXT("page:Party")},{TEXT("DIGILAB"),TEXT("page:DigiLab")},{TEXT("DIGIFARM"),TEXT("page:DigiFarm")},{TEXT("SHOP & SUPPLIES"),TEXT("page:Shop")}})
    { UDigimonVenomNXTActionButton* B=Button(Service.Key,Service.Value); Availability(B,!bSaved&&!bOtherBattle,bSaved||bOtherBattle?TEXT("Finish or resume your saved battle before using party services."):TEXT("Use your existing party and shared account services.")); Row(Services,B); }
    const int32 MapId=InspectedMap>0?InspectedMap:P.MapId;
    const FDigimonRelayMap* Map=DigimonVenomNXTCampaign::GetMap(Campaign,MapId);
    if(!Map||!DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,MapId))return;
    UVerticalBox* Chapter=Section(WidgetTree,Content,FString::Printf(TEXT("MAP %02d / 31  •  %s"),MapId,MapId==P.MapId?TEXT("CURRENT LOCATION"):TEXT("OPEN CASE FILE")));
    Add(Chapter,Text(WidgetTree,Map->Name,23,White,true),3); Add(Chapter,Text(WidgetTree,Map->Subtitle,14,Amber,true),3);
    Add(Chapter,Text(WidgetTree,Map->Intro,14,White),5);
    Add(Chapter,Text(WidgetTree,MapId==1?TEXT("SAFE BACKCHANNEL  •  CASE TEAM / PARTY CARE / SUPPLIES"):FString::Printf(TEXT("RECOMMENDED LV.%d  •  YOUR PARTY IS NEVER SCALED DOWN"),Map->MaxLevel),11,Muted,true),3);
    if(const FDigimonRelayNPC* Quest=QuestFor(MapId))
    {
        const bool bAccepted=P.AcceptedQuests.Contains(Quest->QuestId),bReported=ReportFiled(P,*Quest);
        const bool bInvestigated=DigimonVenomNXTCampaign::QuestObjectiveCount(Campaign,P,Quest->QuestId)>=FMath::Max(1,Quest->QuestTarget);
        auto Step=[&](int32 Number,const FString& Label,bool bDone,bool bNext) { Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("%s  %d. %s"),bDone?TEXT("COMPLETE"):bNext?TEXT("NEXT"):TEXT("PENDING"),Number,*Label),13,bDone?Green:bNext?Amber:Muted,bDone||bNext),4); };
        Step(1,FString::Printf(TEXT("Open the case with %s"),*Quest->Name),bAccepted||bReported,!bAccepted&&!bReported);
        if(MapId<31)
        {
            const FDigimonRelayNPC* Trial=DigimonVenomNXTCampaign::GetNPC(Campaign,Quest->Prerequisite);
            Step(2,Trial?FString::Printf(TEXT("Win %s's witnessed trial"),*Trial->Name):TEXT("Win the named quest tamer's trial"),bInvestigated||bReported,bAccepted&&!bInvestigated&&!bReported);
            Step(3,FString::Printf(TEXT("Return to %s and confirm the case report"),*Quest->Name),bReported,bInvestigated&&!bReported);
        }
        else
        {
            Step(2,TEXT("Confirm the full archive with Iona and seal Access Proof 30"),bReported,bAccepted&&!bReported);
            Step(3,TEXT("Confront the Regent's three level-99 Mega partners"),P.bComplete,bReported&&!P.bComplete);
        }
        if(bReported)Add(Chapter,Text(WidgetTree,TEXT("ACCESS PROOF SAVED  •  Your case report remains in Evidence & Mastery."),12,Green,true),5);
    }
    for(const FDigimonRelayNPC& NPC:DigimonVenomNXTCampaign::NPCsForMap(Campaign,MapId))
    {
        if(!DigimonVenomNXTCampaign::IsNPCVisible(Campaign,P,NPC))continue;
        const bool bDone=NPC.Role==EDigimonRelayRole::Quest?P.CompletedObjectives.Contains(NPC.QuestId):P.DefeatedTamers.Contains(NPC.Id);
        Add(Chapter,Text(WidgetTree,FString::Printf(TEXT("%s  •  %s%s%s"),*DigimonVenomNXTGhostLine::RoleLabel(NPC),*NPC.Name,DigimonVenomNXTCampaign::IsBattleRole(NPC.Role)?*FString::Printf(TEXT("  /  LV.%d"),NPC.Level):TEXT(""),bDone?TEXT("  /  FILED"):TEXT("")),12,bDone?Green:Muted),3);
    }
    if(bInField&&MapId==P.MapId&&!bSaved)
    {
        UHorizontalBox* Travel=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Chapter,Travel,7);
        const int32 Back=PC->GetRelayPortalTarget(false),Forward=PC->GetRelayPortalTarget(true);
        if(Back!=INDEX_NONE) { UDigimonVenomNXTActionButton* B=Button(TEXT("ENTRANCE — PREVIOUS MAP"),TEXT("ghostlineportal"),Back); Availability(B,PC->CanUseRelayPortal(false),TEXT("Walk to the map entrance, then press E or use this button.")); Row(Travel,B); }
        if(Forward!=INDEX_NONE) { UDigimonVenomNXTActionButton* B=Button(Forward==1?TEXT("RETURN UPLINK — BACKCHANNEL"):TEXT("EXIT — NEXT CASE"),TEXT("ghostlineportal"),Forward,true); Availability(B,PC->CanUseRelayPortal(true)&&DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,Forward),Forward==1?TEXT("Approach the return uplink to revisit the Backchannel."):TEXT("Confirm this case report, then walk to the exit.")); Row(Travel,B); }
        if(MapId==31&&!P.bComplete)Add(Chapter,Text(WidgetTree,TEXT("RETURN UPLINK LOCKED  •  Close the final case to restore this route. Your entrance and unlocked network routes remain available."),12,Muted),3);
        if(MapId>1) { Add(Chapter,Button(TEXT("OPTIONAL WILD FIELD TRAINING"),TEXT("ghostlinetrain")),5); Add(Chapter,Text(WidgetTree,TEXT("Repeatable practice with normal wild rewards. You may flee. Story trials cannot be repeated, and wild training never substitutes for case evidence."),12,Muted),3); }
    }
    if(P.bComplete)
    {
        UVerticalBox* Ending=Section(WidgetTree,Content,TEXT("IONA  /  AUTHENTICATED CLOSING TRANSMISSION"),Green);
        Add(Ending,Text(WidgetTree,DigimonVenomNXTGhostLine::Epilogue(P),14,White),5);
    }
    if(InspectedMap>0&&InspectedMap!=P.MapId)Add(Content,Button(TEXT("BACK TO YOUR CURRENT LOCATION"),TEXT("ghostlineinspect"),P.MapId),4);
}

void UDigimonVenomNXTGhostLineWidget::BuildNetworkMap()
{
    using namespace DigimonGhostLineUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.GhostLine;
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(GetOwningPlayer());
    const bool bInField=PC&&PC->IsInGhostLine(),bSaved=Suspended(P),bCanTravel=bInField&&!bSaved;
    Add(Content,Text(WidgetTree,TEXT("ONE BACKCHANNEL. THIRTY CASES."),20,Amber,true),4);
    Add(Content,Text(WidgetTree,TEXT("Each Access Proof opens the next route. Revisit any open map from your private field. Sealed files reveal no future testimony or suspects. Other players cannot enter your investigation."),13,Muted),4);
    if(!bInField)
    {
        UDigimonVenomNXTActionButton* Enter=Button(TEXT("ENTER GHOSTLINE TO USE NETWORK TRAVEL"),TEXT("ghostlineenter"),0,true);
        const bool bOtherBattle=DigimonVenomNXTCampaign::HasOtherPendingBattle(PS->Profile,Campaign);
        Availability(Enter,!bOtherBattle,bOtherBattle?TEXT("Resume the saved battle in your other campaign first."):TEXT("Enter your private investigation with your real party.")); Add(Content,Enter,4);
        if(bOtherBattle)Add(Content,Text(WidgetTree,TEXT("Another campaign has a saved battle. Resume that journey first."),12,Amber,true),3);
    }
    if(bSaved)Add(Content,Text(WidgetTree,TEXT("NETWORK TRAVEL PAUSED  •  Resume your saved battle first."),13,Amber,true),4);
    UUniformGridPanel* Grid=WidgetTree->ConstructWidget<UUniformGridPanel>(); Grid->SetSlotPadding(FMargin(4)); Add(Content,Grid,5); int32 Index=0;
    for(const FDigimonRelayMap& Map:DigimonVenomNXTCampaign::Maps(Campaign))
    {
        const FDigimonRelayNPC* Quest=QuestFor(Map.MapId);
        const bool bOpen=DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,Map.MapId),bCurrent=Map.MapId==P.MapId,bFiled=Quest&&ReportFiled(P,*Quest);
        UBorder* C=Card(WidgetTree,bCurrent?Amber:bOpen?Cyan:Muted,10); UVerticalBox* V=WidgetTree->ConstructWidget<UVerticalBox>(); C->SetContent(V);
        if(bOpen)
        {
            if(UTexture2D* Texture=UDigimonVenomNXTMapAssetRevision::LoadMapTexture(Map.SourceMapId))Add(V,DigimonVenomNXTUI::Texture(WidgetTree,Texture,226,90),2);
        }
        else { USizeBox* Sealed=WidgetTree->ConstructWidget<USizeBox>(); Sealed->SetHeightOverride(90); UTextBlock* Lock=Text(WidgetTree,TEXT("ENCRYPTED CASE FILE"),12,Muted,true); Lock->SetJustification(ETextJustify::Center); Sealed->AddChild(Lock); Add(V,Sealed,2); }
        Add(V,Text(WidgetTree,FString::Printf(TEXT("%02d / 31  •  %s"),Map.MapId,bCurrent?TEXT("CURRENT"):bFiled?TEXT("REPORT FILED"):bOpen?TEXT("OPEN"):TEXT("SEALED")),10,bCurrent?Amber:bFiled?Green:Muted,true),2);
        Add(V,Text(WidgetTree,bOpen?Map.Name:TEXT("Unopened investigation"),15,bOpen?White:Muted,true),3);
        Add(V,Text(WidgetTree,!bOpen?TEXT("File the previous case to decrypt this route."):Map.MapId==1?TEXT("SAFE HUB  •  NO BATTLES"):FString::Printf(TEXT("LV.%d  •  %s"),Map.MaxLevel,bFiled?TEXT("ACCESS PROOF SAVED"):TEXT("CASE REPORT REQUIRED")),11,Muted),3);
        UDigimonVenomNXTActionButton* Inspect=Button(bOpen?TEXT("READ CASE FILE"):TEXT("SEALED CASE FILE"),TEXT("ghostlineinspect"),Map.MapId,bCurrent); Availability(Inspect,bOpen,bOpen?TEXT("Review this open case and its investigation steps."):TEXT("File the preceding case report to reveal this investigation.")); Add(V,Inspect,3);
        UDigimonVenomNXTActionButton* Travel=Button(bCurrent?TEXT("RETURN TO THIS MAP"):bOpen?TEXT("TRAVEL TO MAP"):TEXT("ACCESS PROOF REQUIRED"),TEXT("ghostlinetravel"),Map.MapId,bCurrent);
        Availability(Travel,bOpen&&bCanTravel,!bOpen?TEXT("Confirm the previous case report first."):bSaved?TEXT("Resume your saved battle before travelling."):!bInField?TEXT("Enter Super Xros Wars to travel within your own investigation."):TEXT("Travel with your existing party to this open private map.")); Add(V,Travel,3);
        if(UUniformGridSlot* S=Grid->AddChildToUniformGrid(C,Index/3,Index%3))S->SetHorizontalAlignment(HAlign_Fill); ++Index;
    }
}

void UDigimonVenomNXTGhostLineWidget::BuildEvidence()
{
    using namespace DigimonGhostLineUI;
    const ADigimonVenomNXTPlayerState* PS=BoundPlayer.Get(); if(!PS)return; const auto& P=PS->Profile.GhostLine;
    UVerticalBox* Mastery=Section(WidgetTree,Content,P.bShinyScanMastery?TEXT("SHINY SCAN MASTERY  /  PERMANENTLY UNLOCKED"):TEXT("SUPER XROS WARS COMPLETION REWARD"),P.bShinyScanMastery?Green:Amber);
    Add(Mastery,Text(WidgetTree,TEXT("+20% SHINY SCAN GAIN  /  5% → 6%"),22,White,true),4);
    Add(Mastery,Text(WidgetTree,TEXT("Complete Super Xros Wars to permanently gain 20% more scan data when you win a wild battle against a Shiny Digimon. The reward applies to that exact species and variety, up to your scan cap. It does not change encounter odds or award wild scan data from story tamer battles."),13,Muted),4);
    Add(Mastery,Text(WidgetTree,TEXT("Independent rewards: Dawn / FireWall mastery  •  World DS / Paradox mastery  •  Super Xros / Shiny mastery"),12,Cyan,true),4);
    if(DigimonVenomNXTGhostLine::IsRevealed(P))
    {
        UVerticalBox* Verdict=Section(WidgetTree,Content,P.bComplete?TEXT("THE ROOT SESSION IS CLOSED"):TEXT("LIVE SIGNATURE VERIFIED"),Amber);
        Add(Verdict,Text(WidgetTree,P.bComplete?TEXT("Your evidence and every witness's exit route remain preserved. The final confrontation cannot be repeated. Explore open maps, hear recovery testimony and train in wild encounters."):TEXT("The live-key challenge identified Mara Vale as the Null Regent. Preserve independent revocation and every witness's exit route before closing her root session."),14,White),4);
        // Team details appear only when the final location has legitimately opened.
        if(DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,31))
        {
            const FDigimonRelayNPC* Final=DigimonVenomNXTCampaign::GetNPC(Campaign,TEXT("ghost_final_regent"));
            if(Final)
            {
                Add(Verdict,Text(WidgetTree,TEXT("FINAL LINEUP  /  THREE MEGA DIGIMON  /  LV.99"),12,Amber,true),5);
                UDigimonVenomNXTDataSubsystem* Data=GetGameInstance()?GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>():nullptr;
                UHorizontalBox* Team=WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Verdict,Team,5);
                for(int32 I=0;I<Final->TeamSpecies.Num();++I)
                {
                    UVerticalBox* Partner=WidgetTree->ConstructWidget<UVerticalBox>();
                    USizeBox* Portrait=DigimonVenomNXTUI::AnimatedPortrait(WidgetTree,Final->TeamSpecies[I],Final->TeamVariants.IsValidIndex(I)?Final->TeamVariants[I]:EDigimonVariant::Normal,104,104);
                    if(UVerticalBoxSlot* S=Partner->AddChildToVerticalBox(Portrait))S->SetHorizontalAlignment(HAlign_Center);
                    FDigimonSpeciesDefinition Definition; const FString Name=Data&&Data->GetSpecies(Final->TeamSpecies[I],Definition)?Definition.DisplayName.ToString():TEXT("Mega Digimon");
                    Add(Partner,Text(WidgetTree,Name,13,White,true),3); Add(Partner,Text(WidgetTree,TEXT("MEGA  /  LV.99"),10,Amber,true),2); Row(Team,Partner);
                }
            }
        }
    }
    UVerticalBox* Archive=Section(WidgetTree,Content,FString::Printf(TEXT("EVIDENCE ARCHIVE  /  %02d OF 30 ACCESS PROOFS"),Proofs(P)));
    Add(Archive,Text(WidgetTree,TEXT("Only confirmed reports enter this archive. New leads stay sealed until you investigate them; revisiting a map never rewrites the historical record."),13,Muted),4);
    for(const FDigimonRelayMap& Map:DigimonVenomNXTCampaign::Maps(Campaign))
    {
        if(Map.MapId==1)continue; const FDigimonRelayNPC* Quest=QuestFor(Map.MapId); if(!Quest)continue;
        const bool bReported=ReportFiled(P,*Quest),bOpen=DigimonVenomNXTCampaign::CanEnterMap(Campaign,P,Map.MapId);
        UVerticalBox* File=Section(WidgetTree,Archive,FString::Printf(TEXT("ACCESS PROOF %02d  /  %s"),Map.MapId-1,bReported?TEXT("PRESERVED"):bOpen?TEXT("INVESTIGATION OPEN"):TEXT("SEALED")),bReported?Green:Muted);
        if(bReported)
        {
            Add(File,Text(WidgetTree,Map.Name,16,White,true),3); Add(File,Text(WidgetTree,Quest->AfterDialogue,13,White),4);
        }
        else Add(File,Text(WidgetTree,bOpen?TEXT("Complete the named trial and confirm your report with the case contact to preserve this evidence."):TEXT("This evidence has not been discovered."),12,Muted),3);
    }
}
