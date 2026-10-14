#include "DigimonVenomNXTCampaignAuthored.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTCampaign.h"
#include <iostream>
namespace A=DigimonVenomNXTCampaignAuthored;
namespace G=DigimonVenomNXTGhostLine;
static void TestGhostInvestigation()
{
 FDigimonRelayProgress p;
 FString error, dialogue;
 bool first=false;
 assert(G::Maps().Num()==31 && G::NPCs().Num()==141);
 assert(G::IsFieldComplete(p,1) && !G::IsFieldComplete(p,2));
 assert(G::Epilogue(p).IsEmpty());
 const auto* final=G::GetNPC(TEXT("ghost_final_regent")); assert(final);
 for(int field=1;field<=30;++field)
 {
  const std::wstring number=(field<10?L"0":L"")+std::to_wstring(field);
  const auto* quest=G::GetNPC(FName(L"ghost_"+number+L"_quest")); assert(quest);
  assert(G::CanEnterMap(p,field+1));
  assert(!G::IsFieldComplete(p,field+1));
  if(field<30)assert(!G::CanEnterMap(p,field+2));
  // A changed copy cannot remove authoritative prerequisites.
  FDigimonRelayNPC spoof=*final;spoof.RequiresCompleted={};spoof.RequiresBadges={};spoof.RequiresReveal=-1;
  assert(!G::CanChallenge(p,spoof,error));
  const auto* trainer=G::GetNPC(FName(L"ghost_"+number+L"_trainer"));
  if(trainer)assert(!G::CanChallenge(p,*trainer,error));
  assert(G::AdvanceQuest(p,*quest,dialogue,error));
  assert(p.AcceptedQuests.Contains(quest->Id));
  assert(!G::IsFieldComplete(p,field+1));
  if(trainer)
  {
   assert(G::QuestObjectiveCount(p,quest->Id)==0);
   assert(!G::AdvanceQuest(p,*quest,dialogue,error));
   assert(G::CanChallenge(p,*trainer,error));
   const auto loss=FGuid::NewGuid();p.PendingBattleId=loss;p.PendingNPCId=trainer->Id;
   p.BattleCheckpointJson=TEXT("saved pending battle");
   G::Reconcile(p);assert(p.PendingBattleId==loss && !p.BattleCheckpointJson.IsEmpty());
   assert(G::Settle(p,loss,trainer->Id,false,first));assert(!first);
   assert(!p.PendingBattleId.IsValid()&&p.BattleCheckpointJson.IsEmpty());
   assert(!p.DefeatedTamers.Contains(trainer->Id)&&p.AcceptedQuests.Contains(quest->Id));
   assert(!G::IsFieldComplete(p,field+1));
   const auto win=FGuid::NewGuid();p.PendingBattleId=win;p.PendingNPCId=trainer->Id;
   assert(G::Settle(p,win,trainer->Id,true,first)&&first);
   assert(!G::Settle(p,win,trainer->Id,true,first));
   assert(G::QuestObjectiveCount(p,quest->Id)==1);
   if(field<=26)assert(!G::IsRevealed(p));
   assert(!G::IsFieldComplete(p,field+1));
   if(field<30)assert(!G::CanEnterMap(p,field+2));
   if(trainer->bHackedAfterVictory)assert(p.CompletedObjectives.Contains(FName(L"hacked:"+trainer->Id.S)));
  }
  assert(G::AdvanceQuest(p,*quest,dialogue,error));
  assert(!G::AdvanceQuest(p,*quest,dialogue,error));
  assert(G::IsFieldComplete(p,field+1));
  assert(p.Badges.Num()==field);
  assert(G::IsRevealed(p)==(field>=26));
  if(field<30)assert(G::CanEnterMap(p,field+2));
  for(const auto& n:G::NPCs())if(n.bHideOnReveal&&field>=26)assert(!G::IsNPCVisible(p,n));
 }
 // Final report unlocks a real battle, and never grants completion by itself.
 assert(!p.bComplete&&!p.bShinyScanMastery&&G::CanChallenge(p,*final,error));
 const auto finalLoss=FGuid::NewGuid();p.PendingBattleId=finalLoss;p.PendingNPCId=final->Id;
 assert(G::Settle(p,finalLoss,final->Id,false,first));
 assert(!p.bComplete&&G::CanChallenge(p,*final,error));
 const auto finalWin=FGuid::NewGuid();p.PendingBattleId=finalWin;p.PendingNPCId=final->Id;
 assert(G::Settle(p,finalWin,final->Id,true,first)&&first);
 assert(p.bComplete&&p.bShinyScanMastery&&!p.bParadoxScanMastery&&!p.bFirewallScanMastery);
 assert(!G::Epilogue(p).IsEmpty()&&!G::CanChallenge(p,*final,error));
 for(const auto& n:G::NPCs())
 {
  if(n.CharacterId==TEXT("mara_vale"))assert(!G::IsNPCVisible(p,n));
  if(n.Role==EDigimonRelayRole::Quest)assert(p.CompletedObjectives.Contains(n.Id));
  if(n.bHackedAfterVictory)assert(p.CompletedObjectives.Contains(FName(L"hacked:"+n.Id.S)));
 }
 const auto* witness=G::GetNPC(TEXT("ghost_01_trainer"));assert(witness);
 assert(G::Interact(p,*witness,dialogue,error));assert(!dialogue.IsEmpty());
 FDigimonRelayProgress inflated;inflated.UnlockedMapId=31;
 G::Reconcile(inflated);assert(!inflated.bComplete&&!inflated.bShinyScanMastery);
 std::cout<<"Super Xros Wars adapter: all30 reports, loss/retry, reveal26, persistent hacks, final receipt and return-visit checks passed\n";
}
static void TestLiveProfileRouting()
{
 namespace C=DigimonVenomNXTCampaign;
 FDigimonPlayerProfile unrelated;
 unrelated.Story.Chapter=18;unrelated.Story.ParadoxBadges=17;unrelated.Story.bFinalEncounterComplete=true;
 assert(C::Reconcile(unrelated));
 assert(!unrelated.Chronicles.bComplete&&!unrelated.Chronicles.bParadoxScanMastery&&unrelated.Chronicles.Badges.IsEmpty());
 assert(!C::Reconcile(unrelated));
 FDigimonPlayerProfile native;
 native.Relay.bEverChampion=true;
 native.Chronicles.DefeatedTamers.Add(TEXT("ds_final_triad"));
 native.GhostLine.DefeatedTamers.Add(TEXT("ghost_final_regent"));
 assert(C::Reconcile(native));
 assert(native.Relay.bFirewallScanMastery&&native.Chronicles.bParadoxScanMastery&&native.GhostLine.bShinyScanMastery);
 for(auto variant:{EDigimonVariant::Paradox,EDigimonVariant::Shiny,EDigimonVariant::Firewall})assert(C::ScanGain(native,variant,5,true)==6);
 assert(!C::Reconcile(native));
 for(int id=0;id<3;++id)
 {
  const auto campaign=static_cast<EDigimonPrivateCampaign>(id);
  auto parsed=EDigimonPrivateCampaign::Relay;FName npc;
  assert(C::TryParseContext(C::ContextPrefix(campaign)+TEXT("wild:2"),parsed,npc));
  assert(parsed==campaign&&npc==TEXT("wild:2"));
  assert(&C::Progress(native,campaign)==(id==0?&native.Relay:id==1?&native.Chronicles:&native.GhostLine));
 }
 auto untouched=EDigimonPrivateCampaign::GhostLine;FName npc(TEXT("original"));
 for(const auto* invalid:{TEXT("GhostLine:boss"),TEXT("ghostline:"),TEXT("ghostline:None"),TEXT("unknown:boss")})
 {assert(!C::TryParseContext(invalid,untouched,npc));assert(untouched==EDigimonPrivateCampaign::GhostLine&&npc==TEXT("original"));}
 native.Relay.BattleCheckpointJson=TEXT("relay saved decision");native.GhostLine.BattleCheckpointJson=TEXT("ghost saved decision");
 native.Relay.bInside=native.GhostLine.bInside=true;native.ActiveStoryCampaign=EDigimonPrivateCampaign::GhostLine;
 C::Reconcile(native);assert(native.Relay.bInside&&native.GhostLine.bInside);
 assert(C::HasPendingBattle(native)&&C::HasOtherPendingBattle(native,EDigimonPrivateCampaign::GhostLine));
 assert(native.Relay.BattleCheckpointJson==TEXT("relay saved decision")&&native.GhostLine.BattleCheckpointJson==TEXT("ghost saved decision"));
 std::cout<<"Live profile contract: native authority, independent masteries, full campaign routing and conflicting checkpoints passed\n";
}
int main(){
 TestLiveProfileRouting();
 TestGhostInvestigation();
 const int maps[]={18,18,31},npcs[]={60,92,141},badges[]={8,17,30};
 for(int c=0;c<3;++c){
  const auto& d=A::Content(c);assert(d.Maps.Num()==maps[c]);assert(d.NPCs.Num()==npcs[c]);
  FDigimonRelayProgress p;A::Reconcile(c,p);assert(A::CanEnter(c,p,1));assert(A::CanEnter(c,p,2));assert(!A::CanEnter(c,p,3));
  FString error,dialogue;bool first=false;const auto* final=A::NPC(c,d.FinalId);assert(final);assert(!A::CanChallenge(c,p,*final,error));
  int wins=0,quests=0;
  // Execute the authored state machine in source order until the finale wins.
  for(int pass=0;pass<1000&&!p.bComplete;++pass){
   bool advanced=false;
   for(const auto& n:d.NPCs){
    if(n.Role==EDigimonRelayRole::Challenger)continue;
    if(n.Role==EDigimonRelayRole::Quest&&!p.CompletedObjectives.Contains(n.Id)){
     bool accepted=p.AcceptedQuests.Contains(n.Id);
     if(A::AdvanceQuest(c,p,n,dialogue,error)){
      advanced=true;if(accepted){++quests;assert(!A::AdvanceQuest(c,p,n,dialogue,error));}
     }
    }else if(A::IsBattle(n.Role)&&!p.DefeatedTamers.Contains(n.Id)&&A::CanChallenge(c,p,n,error)){
     assert(!A::Settle(c,p,FGuid::NewGuid(),n.Id,true,first));
     const FGuid id=FGuid::NewGuid();p.PendingBattleId=id;p.PendingNPCId=n.Id;
     assert(A::Settle(c,p,id,n.Id,true,first));assert(first);++wins;advanced=true;
     assert(!A::Settle(c,p,id,n.Id,true,first));
    }
   }
   assert(advanced||p.bComplete);
  }
  assert(p.bComplete);assert(p.Badges.Num()==badges[c]);
  for(int i=1;i<=maps[c];++i)assert(A::CanEnter(c,p,i));
  assert(p.bFirewallScanMastery==(c==0));assert(p.bParadoxScanMastery==(c==1));assert(p.bShinyScanMastery==(c==2));
  if(c==0){
   const auto* challenge=A::Challenger(c,p);assert(challenge);auto id=FGuid::NewGuid();p.PendingBattleId=id;p.PendingNPCId=challenge->Id;
   assert(A::Settle(c,p,id,challenge->Id,false,first));assert(!p.bIsChampion&&p.bFirewallScanMastery);
   assert(A::Challenger(c,p)->Id==challenge->Id);id=FGuid::NewGuid();p.PendingBattleId=id;p.PendingNPCId=challenge->Id;
   assert(A::Settle(c,p,id,challenge->Id,true,first));assert(p.bIsChampion&&p.bFirewallScanMastery);
  }
  if(c==1){assert(final->TeamSpecies.Num()==3);for(int i=0;i<3;++i){assert(final->TeamLevels[i]==100);assert(final->TeamVariants[i]==EDigimonVariant::Paradox);}}
  if(c==2){assert(A::Revealed(p));assert(!A::Visible(c,p,*final));assert(!A::CanChallenge(c,p,*final,error));for(const auto& n:d.NPCs)if(n.CharacterId==TEXT("mara_vale"))assert(!A::Visible(c,p,n));for(auto v:final->TeamVariants)assert(v==EDigimonVariant::Normal);}
  std::cout<<"campaign "<<c<<": "<<wins<<" battles, "<<quests<<" reports, "<<p.Badges.Num()<<" badges; receipt, gating and mastery checks passed\n";
 }
}
