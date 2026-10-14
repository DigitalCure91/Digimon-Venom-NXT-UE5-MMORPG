#!/usr/bin/env python3
"""Exercise production wild encounter adapters with portable UE value stand-ins.

Compiles the actual group builder, battle initialization and private settlement
functions, plus the wild checkpoint-validation branch. Uses a minimal species
fixture and real combat/progression/scan/recovery/pacing cores. This catches
behavioral regressions without claiming an Unreal/UHT, networking or render test.
"""
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile

import test_combat_adapter as combat
from test_battle_damage_adapter import definition

ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"

COMPAT = r'''
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>
using TCHAR=char;using int32=int;using int64=long long;using uint8=unsigned char;using uint32=unsigned;
#define TEXT(X) X
#define DIGIMONVENOMNXTRUNTIME_API
#define GENERATED_BODY()
#define UPROPERTY(...)
#define UMETA(...)
#define MoveTemp(X) std::move(X)
constexpr int32 INDEX_NONE=-1,MAX_int32=std::numeric_limits<int32>::max();
struct FString {
 std::string Value;
 FString()=default;FString(const char*S):Value(S){}FString(std::string S):Value(std::move(S)){}
 const char*operator*()const{return Value.c_str();}bool IsEmpty()const{return Value.empty();}
 void Reset(){Value.clear();}int32 Len()const{return static_cast<int32>(Value.size());}
 FString&operator+=(const FString&S){Value+=S.Value;return *this;}
 friend FString operator+(const FString&A,const FString&B){return A.Value+B.Value;}
 friend bool operator==(const FString&A,const FString&B){return A.Value==B.Value;}
 friend bool operator!=(const FString&A,const FString&B){return !(A==B);}
 static FString Printf(const char*Format,...){char Out[8192];va_list Args;va_start(Args,Format);vsnprintf(Out,sizeof(Out),Format,Args);va_end(Args);return Out;}
};
struct FText {FString Value;static FText FromString(const FString&S){return {S};}FString ToString()const{return Value;}};
struct FName {
 std::string Value;FName()=default;FName(const char*S):Value(S){}
 bool IsNone()const{return Value.empty();}FString ToString()const{return Value;}
 friend bool operator==(const FName&A,const FName&B){return A.Value==B.Value;}
 friend bool operator!=(const FName&A,const FName&B){return !(A==B);}
};
inline const FName NAME_None;
struct FGuid {
 unsigned Value=0;static FGuid NewGuid(){static unsigned Next=0;return {++Next};}
 bool IsValid()const{return Value!=0;}void Invalidate(){Value=0;}
 friend bool operator==(FGuid A,FGuid B){return A.Value==B.Value;}friend bool operator!=(FGuid A,FGuid B){return !(A==B);}friend bool operator<(FGuid A,FGuid B){return A.Value<B.Value;}
};
template<class T>struct TArray:std::vector<T>{
 using std::vector<T>::vector;using std::vector<T>::operator=;
 void Add(const T&V){this->push_back(V);}void AddUnique(const T&V){if(!Contains(V))Add(V);}void Reserve(int32 N){this->reserve(N);}void Reset(){this->clear();}
 bool IsEmpty()const{return this->empty();}int32 Num()const{return static_cast<int32>(this->size());}
 bool IsValidIndex(int32 N)const{return N>=0&&N<Num();}T&Last(){return this->back();}
 bool Contains(const T&V)const{return std::find(this->begin(),this->end(),V)!=this->end();}
 template<class P>T*FindByPredicate(P Predicate){for(auto&V:*this)if(Predicate(V))return &V;return nullptr;}
 template<class P>const T*FindByPredicate(P Predicate)const{for(const auto&V:*this)if(Predicate(V))return &V;return nullptr;}
};
template<class T>struct TSet:TArray<T>{};
template<class K,class V>struct TMap:std::map<K,V>{void Add(const K&K_,const V&V_){(*this)[K_]=V_;}V FindRef(const K&K_)const{auto I=this->find(K_);return I==this->end()?V():I->second;}void Reset(){this->clear();}};
struct FMath {
 inline static float UnitRoll=.1f;static float FRand(){return UnitRoll;}
 inline static std::vector<int> Rolls;inline static std::vector<std::pair<int,int>> Ranges;inline static unsigned Cursor=0;
 static void Script(std::initializer_list<int> Values){Rolls=Values;Ranges.clear();Cursor=0;}
 static int RandRange(int A,int B){Ranges.emplace_back(A,B);if(Cursor>=Rolls.size()){std::cerr<<"Unexpected random roll\n";std::exit(1);}int V=Rolls[Cursor++];if(V<A||V>B){std::cerr<<"Out-of-range scripted roll "<<V<<" in "<<A<<".."<<B<<"\n";std::exit(1);}return V;}
 template<class T>static T Min(T A,T B){return std::min(A,B);}template<class T>static T Max(T A,T B){return std::max(A,B);}
 static bool IsFinite(double V){return std::isfinite(V);}
 template<class T>static T Clamp(T V,T A,T B){return std::clamp(V,A,B);}static int32 FloorToInt(float V){return static_cast<int32>(std::floor(V));}
};
class UPaperFlipbook;template<class T>struct TSoftObjectPtr{};
'''

STUBS = r'''
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTBattlePolicyCore.h"
#include "DigimonVenomNXTCampaignBattleCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTRewardCore.h"
#include "DigimonVenomNXTVariantCore.h"
#include "DigimonVenomNXTTimelineCore.h"
enum class EDigimonPrivateCampaign{Relay,ParadoxChronicles,GhostLine};
enum class EDigimonBattleKind{Wild,AITamer,Season,Ranked,Story,Friendly};
struct FDigimonBattleState {TArray<FGuid>ScannedWildInstances;TArray<FDigimonWildScanMasteryPending>WildMasteryHundredths;bool bWildMasteryPaid=false,bAutomatic=false;FGuid BattleId;EDigimonBattleKind Kind=EDigimonBattleKind::Wild;FDigimonBattleTeam TeamA,TeamB;FString LastEvent;bool bFinished=false,bFled=false;int WinningTeam=-1,CombatBalanceVersion=0,InitialActiveCount=0,ActingTeam=0,ActingSlot=0;double BattleClock=0;};
struct FDigimonRelayProgress {bool bShinyScanMastery=false,bParadoxScanMastery=false,bFirewallScanMastery=false;bool bInside=true;int MapId=2;FGuid PendingBattleId,LastSettledBattleId;FName PendingNPCId;FString BattleCheckpointJson;};
struct FDigimonRelayMap {int MapId=2,MinLevel=1,MaxLevel=99,RegionIndex=1;TArray<FName> WildSpecies;};
struct FDigimonRelayNPC {int MapId=2;TArray<FName>TeamSpecies;TArray<EDigimonVariant>TeamVariants;};
struct FDigimonPlayerProfile {int CurrentMapId=1;TArray<FDigimonInventoryEntry>Inventory;FDigimonRelayProgress Relay,Chronicles,GhostLine;FString Username="Tester";EDigimonPrivateCampaign ActiveStoryCampaign=EDigimonPrivateCampaign::Relay;TArray<FGuid>Party;TArray<FDigimonOwnedPartner>Collection;TArray<FDigimonScanRecord>Scans;FDigimonRelayProgress Progress;int64 Credits=0;int Season=0;};
struct FDigimonSeasonBattleCheckpoint {FDigimonBattleState State;FString ContextId;};
struct FDigimonSeasonTamer {bool bPlayer=false;TArray<FDigimonOwnedPartner>Team;};
struct FDigimonSeasonMatch {FString HomeTamerId,AwayTamerId;};
namespace DigimonVenomNXTSeason {
 const FDigimonSeasonMatch*GetPlayerMatch(int){return nullptr;}
 const FDigimonSeasonTamer*FindTamer(int,const FString&){return nullptr;}
}
struct UDigimonVenomNXTSettings {int ActiveBattleSize=3,BaseScanGain=10,RareScanGain=5,MaxPartnerLevel=100,ScanCapPercent=200;double ExperienceRate=1.,MoneyRewardRate=1.,ShinyChance=.01,ParadoxChance=.025,FirewallChance=.007;};
template<class T>T*GetDefault(){static T Value;return &Value;}
struct ADigimonVenomNXTBattleActor;
struct ADigimonVenomNXTPlayerController {
 bool bRelay=false,bAuthenticated=true;EDigimonPrivateCampaign Campaign=EDigimonPrivateCampaign::Relay;ADigimonVenomNXTBattleActor*CurrentBattle=nullptr;
 bool IsInRelay()const{return bRelay;}bool IsAccountAuthenticated()const{return bAuthenticated;}
 EDigimonPrivateCampaign GetStoryCampaign()const{return Campaign;}
};
template<class T>T*Cast(ADigimonVenomNXTPlayerController*Pointer){return static_cast<T*>(Pointer);}
struct ADigimonVenomNXTPlayerState {
 FDigimonPlayerProfile Profile;ADigimonVenomNXTPlayerController Controller;bool bActive=false;int Recoveries=0,Changes=0;
 bool GetPartner(FGuid Id,FDigimonOwnedPartner&Out)const{const auto*P=Profile.Collection.FindByPredicate([Id](const auto&V){return V.InstanceId==Id;});if(!P)return false;Out=*P;return true;}
 bool HasActiveBattle()const{return bActive;}ADigimonVenomNXTPlayerController*GetOwner(){return &Controller;}
 void RecoverDefeatedParty(){++Recoveries;}void MarkProfileChanged(){++Changes;}
};
struct FakeGameInstance {UDigimonVenomNXTDataSubsystem*Data=nullptr;template<class T>T*GetSubsystem(){return static_cast<T*>(Data);}};
struct FakeTimer {void ClearTimer(int){}};struct FakeWorld {FakeTimer Timer;FakeTimer&GetTimerManager(){return Timer;}};
namespace DigimonVenomNXTCampaign {
 bool IsValid(EDigimonPrivateCampaign C){return static_cast<int>(C)>=0&&static_cast<int>(C)<3;}
 FDigimonRelayProgress&Progress(FDigimonPlayerProfile&P,EDigimonPrivateCampaign){return P.Progress;}
 const FDigimonRelayProgress&Progress(const FDigimonPlayerProfile&P,EDigimonPrivateCampaign){return P.Progress;}
 bool CanEnterMap(EDigimonPrivateCampaign,const FDigimonRelayProgress&,int MapId){return MapId>=1&&MapId<=31;}
 inline FDigimonRelayMap Map;inline TArray<FDigimonRelayNPC>NPCData;const TArray<FDigimonRelayNPC>&NPCs(EDigimonPrivateCampaign){return NPCData;}const FDigimonRelayMap*GetMap(EDigimonPrivateCampaign,int){return &Map;}
 FString ContextPrefix(EDigimonPrivateCampaign){return "campaign:";}
 int ScanGain(const FDigimonPlayerProfile&,EDigimonVariant V,int Base,bool){return Base+(V==EDigimonVariant::Firewall?10:0);}
}
struct UDigimonVenomNXTWorldSubsystem {
 TArray<EDigimonVariant>Variants;int Calls=0;
 EDigimonVariant RollWildVariant(){if(Calls>=Variants.Num()){std::cerr<<"Unexpected variant roll\n";std::exit(1);}return Variants[Calls++];}
};
struct ADigimonVenomNXTBattleActor {
 FakeGameInstance Instance;FakeWorld World;ADigimonVenomNXTPlayerState*PlayerA=nullptr,*PlayerB=nullptr;
 FDigimonBattleState State;FString BattleContextId;bool bAuthority=true,bSaveOK=true,bSeasonCommandTransaction=false;
 int Published=0,Saved=0,Safety=0,Timelines=0,BattleSafetyTimer=0;
 bool HasAuthority()const{return bAuthority;}FakeGameInstance*GetGameInstance()const{return const_cast<FakeGameInstance*>(&Instance);}
 FakeWorld*GetWorld(){return &World;}bool IsRelayBattle()const{return BattleContextId.Value.rfind("campaign:",0)==0;}
 EDigimonPrivateCampaign BattleCampaign()const{return PlayerA->Profile.ActiveStoryCampaign;}
 FName BattleNPCId()const{auto Pos=BattleContextId.Value.find("wild:");return Pos==std::string::npos?NAME_None:FName(BattleContextId.Value.substr(Pos).c_str());}
 bool SaveSeasonCheckpoint(){++Saved;return bSaveOK;}void PublishState(){++Published;}void StartBattleSafetyChecks(){++Safety;}
 void InitializeTimeline(){++Timelines;State.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;int Order=0;for(auto*Roster:{&State.TeamA.Active,&State.TeamA.Bench,&State.TeamB.Active,&State.TeamB.Bench})for(auto&Unit:*Roster){Unit.TimelineOrder=Order++;Unit.NextActionTime=10.0;}}
 bool SelectNextActor(){return true;}
 bool IsTeamDefeated(const FDigimonBattleTeam&T)const;
 void PromoteBench(FDigimonBattleTeam&);
 FDigimonBattleUnit BuildUnit(const FDigimonOwnedPartner&)const;
 FDigimonBattleTeam BuildTeamFromProfile(const FDigimonPlayerProfile&,bool bFullRestore=false,bool bCampaignFinale=false)const;
 bool InitializeWildBattle(ADigimonVenomNXTPlayerState*,FName,EDigimonVariant,int32);
 bool InitializeWildGroupBattle(ADigimonVenomNXTPlayerState*,const TArray<FDigimonWildEncounterEntry>&);
 void RecordWildDefeat(const FDigimonBattleUnit&);FString AwardWildMastery(FDigimonPlayerProfile&);
 bool FinishPrivateWildMatch(int32,const FString&,bool);
 bool RebuildRestoredBattle(bool&,FString&);
 bool ValidateSavedWildGroup(const FDigimonSeasonBattleCheckpoint&,const FDigimonRelayMap*,EDigimonPrivateCampaign,FString&);
};
void LoadFixture(UDigimonVenomNXTDataSubsystem&);
static int Checks=0;
static void Check(bool Value,const char*Message){++Checks;if(!Value){std::cerr<<"FAIL wild group adapter: "<<Message<<"\n";std::exit(1);}}
'''

TESTS = r'''
static FDigimonWildEncounterEntry Entry(const char*Species="agumon",int Level=1,EDigimonVariant Variant=EDigimonVariant::Normal){FDigimonWildEncounterEntry E;E.SpeciesId=Species;E.Level=Level;E.Variant=Variant;return E;}
static ADigimonVenomNXTPlayerState Player(){
 ADigimonVenomNXTPlayerState P;
 for(int I=0;I<4;++I){FDigimonOwnedPartner Unit;Unit.InstanceId=FGuid::NewGuid();Unit.SpeciesId="agumon";Unit.Level=50;Unit.Experience=240100;Unit.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;Unit.CurrentHP=MAX_int32;Unit.CurrentSP=MAX_int32;P.Profile.Collection.Add(Unit);P.Profile.Party.Add(Unit.InstanceId);}
 return P;
}
static ADigimonVenomNXTBattleActor Battle(UDigimonVenomNXTDataSubsystem&Data){ADigimonVenomNXTBattleActor B;B.Instance.Data=&Data;return B;}
static void PrepareSettlement(ADigimonVenomNXTBattleActor&B,ADigimonVenomNXTPlayerState&P){
 P.Controller.bRelay=true;P.Controller.CurrentBattle=&B;B.BattleContextId="campaign:wild:2";P.Profile.Progress.PendingBattleId=B.State.BattleId;P.Profile.Progress.PendingNPCId="wild:2";P.Profile.Progress.BattleCheckpointJson="saved";
 for(auto&Unit:B.State.TeamB.Active){Unit.HP=0;Unit.bDefeated=true;B.RecordWildDefeat(Unit);}
}
int main(){
 UDigimonVenomNXTDataSubsystem Data;LoadFixture(Data);
 for(auto&Pair:Data.Species){auto&S=Pair.second;S.bHasNormalArtwork=true;S.bHasParadoxArtwork=true;S.bHasShinyArtwork=true;S.bHasFirewallArtwork=true;}
 const auto Normal=EDigimonVariant::Normal,Shiny=EDigimonVariant::Shiny,Firewall=EDigimonVariant::Firewall;
 for(int Count:{1,2,3}){
  auto P=Player();auto B=Battle(Data);TArray<FDigimonWildEncounterEntry>Group;
  for(int I=0;I<Count;++I)Group.Add(Entry("agumon",5+I,I==1?Shiny:Normal));
  Check(B.InitializeWildGroupBattle(&P,Group),"each supported group size starts");
  Check(B.State.TeamB.Active.Num()==Count&&B.State.TeamB.Bench.IsEmpty(),"all rolled opponents are active with no hidden reserves");
  Check(B.State.TeamA.Active.Num()==3&&B.State.TeamA.Bench.Num()==1,"player formation and reserve remain unchanged");
  Check(B.Published==1&&B.Timelines==1&&B.Safety==1,"complete group publishes and starts one battle");
  for(int I=0;I<Count;++I){const auto&U=B.State.TeamB.Active[I];FDigimonOwnedPartner Owner;Owner.SpeciesId=U.SpeciesId;Owner.Level=U.Level;Owner.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;Owner.CurrentHP=MAX_int32;Owner.CurrentSP=MAX_int32;auto Full=DigimonVenomNXTAutoBattle::BuildUnit(Owner,&Data);
   Check(U.InstanceId.IsValid()&&U.Level==5+I&&U.Variant==Group[I].Variant,"opponent identity, independent level and variant are preserved");
   Check(U.Stats.MaxHP==static_cast<int>(std::floor(Full.Stats.MaxHP*.72f))&&U.HP==U.Stats.MaxHP&&U.SP==Full.Stats.MaxSP,"every wild member has existing 72-percent HP and full SP");
   Check(U.Stats.Attack==Full.Stats.Attack&&U.Stats.Spirit==Full.Stats.Spirit,"group size never changes per-opponent offense");
   for(int J=0;J<I;++J)Check(U.InstanceId!=B.State.TeamB.Active[J].InstanceId,"duplicate species receive distinct instance IDs");
  }
 }
 {
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildBattle(&P,"agumon",Firewall,7),"legacy single-opponent wrapper remains callable");
  Check(B.State.TeamB.Active.Num()==1&&B.State.TeamB.Active[0].Level==7&&B.State.TeamB.Active[0].Variant==Firewall,"legacy API retains explicit single selection");
 }
 // Human source modes use living members from the first three party positions.
 // A healthy reserve never revives the field party or joins without a manual swap.
 {
  auto P=Player();auto B=Battle(Data);
  for(int I=0;I<3;++I)P.Profile.Collection[I].CurrentHP=0;
  Check(!B.InitializeWildGroupBattle(&P,{Entry()}),"three fainted active partners cannot search using a healthy fourth reserve");
  Check(P.Recoveries==0&&P.Profile.Collection[0].CurrentHP==0&&B.Published==0&&!B.State.BattleId.IsValid(),"failed encounter does not heal or publish a battle");
 }
 {
  auto P=Player();auto B=Battle(Data);P.Profile.Collection[0].CurrentHP=P.Profile.Collection[2].CurrentHP=0;
  Check(B.InitializeWildGroupBattle(&P,{Entry()}),"one living partner among first three can start a wild battle");
  Check(B.State.TeamA.Active.Num()==1&&B.State.TeamA.Active[0].InstanceId==P.Profile.Party[1]&&B.State.TeamA.Bench.Num()==3,"living first-three compacts without pulling fourth party member into active slots");
  Check(P.Recoveries==0&&P.Profile.Collection[0].CurrentHP==0&&P.Profile.Collection[2].CurrentHP==0,"valid encounter preserves fainted owned partners");
 }
 for(auto Kind:{EDigimonBattleKind::Wild,EDigimonBattleKind::Story,EDigimonBattleKind::Season}){
  auto P=Player();auto B=Battle(Data);B.State.Kind=Kind;
  P.Profile.Collection[0].CurrentHP=0;
  B.State.TeamA=B.BuildTeamFromProfile(P.Profile);
  Check(B.State.TeamA.Active.Num()==2&&B.State.TeamA.Active[0].InstanceId==P.Profile.Party[1]&&B.State.TeamA.Active[1].InstanceId==P.Profile.Party[2],"all human source modes preserve living first-three order");
  for(auto&Unit:B.State.TeamA.Active)Unit.HP=0;
  B.PromoteBench(B.State.TeamA);
  Check(B.IsTeamDefeated(B.State.TeamA)&&B.State.TeamA.Active[0].HP==0,"human source defeat is resolved without automatic reserve promotion");
  const auto*Reserve=B.State.TeamA.Bench.FindByPredicate([&](const auto&Unit){return Unit.InstanceId==P.Profile.Party[3];});
  Check(Reserve&&Reserve->HP>0,"healthy reserve remains available for deliberate manual formation changes");
 }
 {
  auto P=Player();auto B=Battle(Data);B.State.bAutomatic=true;
  P.Profile.Collection[0].CurrentHP=0;B.State.TeamA=B.BuildTeamFromProfile(P.Profile);
  Check(B.State.TeamA.Active.Num()==3&&B.State.TeamA.Active[0].InstanceId==P.Profile.Party[3],"automatic rival battle keeps its existing reserve promotion policy");
 }
 for(int Mode=0;Mode<7;++Mode){
  auto P=Player();auto B=Battle(Data);TArray<FDigimonWildEncounterEntry>Group{Entry(),Entry(),Entry()};
  if(Mode==0)Group.Reset();
  if(Mode==1)Group.Add(Entry());
  if(Mode==2)Group[2].SpeciesId=NAME_None;
  if(Mode==3)Group[2].SpeciesId="missing";
  if(Mode==4)Group[2].Variant=static_cast<EDigimonVariant>(255);
  if(Mode==5)P.bActive=true;
  if(Mode==6)B.bAuthority=false;
  Check(!B.InitializeWildGroupBattle(&P,Group),"invalid group rejects even a bad final member");
  Check(B.Published==0&&B.Timelines==0&&P.Recoveries==0&&!B.State.BattleId.IsValid(),"invalid group has no battle or player side effects");
 }
 {
  auto P=Player();auto B=Battle(Data);auto&Species=Data.Species.at("agumon");Species.bHasShinyArtwork=false;
  Check(B.InitializeWildGroupBattle(&P,{Entry(),Entry("agumon",0,Shiny),Entry("agumon",999,Firewall)}),"missing optional artwork falls back independently");
  Check(B.State.TeamB.Active[1].Variant==Normal&&B.State.TeamB.Active[2].Variant==Firewall&&B.State.TeamB.Active[1].Level==1&&B.State.TeamB.Active[2].Level==99,"fallback and level clamps apply per member");
  Species.bHasNormalArtwork=false;auto Invalid=Battle(Data);Check(!Invalid.InitializeWildGroupBattle(&P,{Entry("agumon",1,Shiny)}),"missing normal fallback fails closed");
  Species.bHasNormalArtwork=true;Species.bHasShinyArtwork=true;Species.bPlaceholder=true;Invalid=Battle(Data);Check(!Invalid.InitializeWildGroupBattle(&P,{Entry()}),"placeholder species cannot encounter");Species.bPlaceholder=false;
 }
 // Source roll depends on living active count; rare species is drawn from
 // its independent habitat pool after choosing all ordinary enemies.
 const TArray<FName>Candidates{"agumon","gabumon"};
 GetDefault<UDigimonVenomNXTSettings>()->FirewallChance=1.;
 GetDefault<UDigimonVenomNXTSettings>()->ShinyChance=0.;
 GetDefault<UDigimonVenomNXTSettings>()->ParadoxChance=0.;
 for(bool Solo:{false,true})for(int Count:{1,2,3}){
  auto P=Player();if(Solo)for(int I=1;I<3;++I)P.Profile.Collection[I].CurrentHP=0;
  FMath::UnitRoll=Count==1?.1f:Count==2?(Solo?.8f:.4f):.99f;
  FMath::Rolls={};FMath::Ranges.clear();FMath::Cursor=0;
  for(int I=0;I<Count;++I){FMath::Rolls.push_back(I%2);FMath::Rolls.push_back(7+I);}
  FMath::Rolls.push_back(Count-1);FMath::Rolls.push_back(0);
  auto Group=BuildRandomWildGroup(Candidates,7,9,&P,false,{}, {}, {"rare_only"});
  Check(Group.Num()==Count&&FMath::Cursor==static_cast<unsigned>(2+2*Count),"group and level rolls followed by independent rare slot/species draws");
  Check(FMath::Ranges[2*Count]==std::make_pair(0,Count-1),"rare selection covers exactly one rolled group slot");
  for(int I=0;I<Count;++I)Check(Group[I].SpeciesId==(I==Count-1?FName("rare_only"):Candidates[I%2])&&Group[I].Level==7+I&&Group[I].Variant==(I==Count-1?Firewall:Normal),"rare habitat can replace normal species while preserving selected slot level");
 }
 GetDefault<UDigimonVenomNXTSettings>()->FirewallChance=.007;
 GetDefault<UDigimonVenomNXTSettings>()->ShinyChance=.01;
 GetDefault<UDigimonVenomNXTSettings>()->ParadoxChance=.025;
 {
  FMath::Script({});Check(BuildRandomWildGroup({},1,4,nullptr).IsEmpty()&&FMath::Cursor==0,"empty pool makes no random calls");
  FMath::UnitRoll=.99f;FMath::Script({0,99,0,99,0,99});auto Group=BuildRandomWildGroup({"agumon"},200,-20,nullptr);
  Check(Group.Num()==3&&Group[2].Variant==Normal&&Group[2].Level==99,"duplicates permitted and source wild level cap99");
 }
 // Exact source rare intervals are Paradox, Shiny, then Firewall, with
 // unavailable pools disabling only their category. Each event replaces once.
 for(int Case=0;Case<4;++Case){
  const float Rolls[]={.01f,.03f,.04f,.50f};const EDigimonVariant Expected[]={EDigimonVariant::Paradox,Shiny,Firewall,Normal};
  TArray<FDigimonWildEncounterEntry> Group{Entry("agumon",9),Entry("agumon",23)};
  FMath::UnitRoll=Rolls[Case];FMath::Script({1,0});
  ReplaceWildVariety(Group,{"paradox_only"},{"shiny_only"},{"firewall_only"});
  Check(Group[0].SpeciesId==FName("agumon")&&Group[0].Variant==Normal,"rare event never alters other group members");
  Check(Group[1].Variant==Expected[Case]&&Group[1].Level==23,"rare replacement retains that slot's exact level");
  Check(FMath::Cursor==(Case<3?2u:0u),"ordinary outcome does not consume replacement draws");
 }
 {
  TArray<FDigimonWildEncounterEntry> Group{Entry("agumon",7)};
  FMath::UnitRoll=.005f;FMath::Script({0,0});ReplaceWildVariety(Group,{}, {}, {"firewall_only"});
  Check(Group[0].SpeciesId==FName("firewall_only")&&Group[0].Variant==Firewall,"missing earlier pools cannot absorb an available rarity interval");
 }
 // The weighted public group distribution is pinned to the original source,
 // sampled at every percent midpoint with both living-active policies.
 for(bool Solo:{false,true}){
  int Counts[4]={};auto P=Player();if(Solo)for(int I=1;I<3;++I)P.Profile.Collection[I].CurrentHP=0;
  for(int Sample=0;Sample<100;++Sample){
   FMath::UnitRoll=(Sample+.5f)/100.f;FMath::Script({0,7,0,7,0,7});
   auto Group=BuildRandomWildGroup({"agumon"},7,7,&P);++Counts[Group.Num()];
  }
  Check(Counts[1]==(Solo?70:25)&&Counts[2]==(Solo?25:40)&&Counts[3]==(Solo?5:35),"living-first-three source group odds70/25/5 or25/40/35");
 }
 // Dawn legacy +/-2 clamping duplicates edge outcomes; explicit expansion ranges remain uniform.
 for(int Center:{1,2,3,98,99})for(int Delta=-2;Delta<=2;++Delta){
  FMath::UnitRoll=.1f;FMath::Script({0,Delta});
  auto Group=BuildRandomWildGroup({"agumon"},std::max(1,Center-2),std::min(99,Center+2),nullptr,true);
  Check(Group.Num()==1&&Group[0].Level==std::clamp(Center+Delta,1,99),"Dawn edge distribution retains original center and clamp");
 }
 {
  auto P=Player();P.Profile.Party.resize(3);P.Profile.Collection.resize(3);
  for(int I=0;I<3;++I){P.Profile.Collection[I].Level=9;P.Profile.Collection[I].Variant=I==0?Firewall:I==1?Shiny:EDigimonVariant::Paradox;}
  FDigimonRelayMap Map;Map.MinLevel=30;FString Error;
  DigimonVenomNXTCampaign::NPCData={{2,{"agumon"},{Normal}}};
  FMath::UnitRoll=.5f;FMath::Script({});
  const auto Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
  Check(Group.Num()==3&&Group[0].Level==9,"training mirrors the living firstthree at weakest capped regional level");
  Check(Group[0].Variant==Normal&&Group[1].Variant==Normal&&Group[2].Variant==EDigimonVariant::Paradox,"owned Shiny and Firewall normalize in practice; source Paradox remains");
  P.Profile.Collection[0].CurrentHP=P.Profile.Collection[1].CurrentHP=P.Profile.Collection[2].CurrentHP=0;
  Check(BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error).IsEmpty()&&!Error.IsEmpty(),"no living active practice team is rejected");
 }
 {
  auto P=Player();P.Profile.Party.resize(1);P.Profile.Collection.resize(1);P.Profile.Collection[0].SpeciesId="agumon";
  Data.Species.at("agumon").Affinity=EDigimonAffinity::Vaccine;
  Data.Species.at("gabumon").Affinity=EDigimonAffinity::Virus;
  DigimonVenomNXTCampaign::NPCData={{2,{"gabumon"},{Normal}}};
  FDigimonRelayMap Map;Map.MinLevel=60;FString Error;FMath::UnitRoll=.5f;FMath::Script({});
  auto Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
  Check(Group.Num()==1&&Group[0].SpeciesId==FName("agumon")&&Group[0].Level==50,"unsafe affinity pool falls back to the owned species");
  Data.Species.at("gabumon").Affinity=EDigimonAffinity::Free;
  FMath::Script({0});Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
  Check(Group[0].SpeciesId==FName("gabumon"),"Free practice types remain compatible with all partner affinities");
  Data.Species.at("gabumon").Affinity=EDigimonAffinity::Vaccine;
  const EDigimonStage Stage[]={EDigimonStage::Rookie,EDigimonStage::Champion,EDigimonStage::Ultimate,EDigimonStage::Mega,EDigimonStage::Ultra};
  const int Levels[]={14,15,30,45,60};
  for(int I=0;I<5;++I){
   P.Profile.Collection[0].Level=Levels[I];Data.Species.at("gabumon").Stage=Stage[I];
   FMath::Script({0});Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
   Check(Group[0].SpeciesId==FName("gabumon")&&Group[0].Level==Levels[I],"source practice stage threshold permits matching rank");
   if(I){P.Profile.Collection[0].Level=Levels[I]-1;FMath::Script({0});Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
    Check(Group[0].SpeciesId==FName("agumon"),"one level below stage threshold falls back to Rookie starter pool");}
  }
  Data.Species.at("gabumon").Stage=EDigimonStage::Rookie;
 }
 {
  auto P=Player();P.Profile.Party.resize(3);P.Profile.Collection.resize(3);
  for(auto&Partner:P.Profile.Collection)Partner.Level=9;
  P.Profile.Collection[1].SpeciesId="gabumon";
  FDigimonRelayMap Map;Map.MinLevel=30;FString Error;
  FMath::UnitRoll=.001f;FMath::Script({0,1});
  const auto Group=BuildTrainingFixture(&P,&Map,&Data,EDigimonPrivateCampaign::Relay,Error);
  Check(Group[0].SpeciesId==FName("gabumon")&&Group[0].Variant==Shiny&&Group[0].Level==9,"private rare pool can replace another practice partner species at the original slot's level");
  Check(Group[1].Variant==Normal&&Group[2].Variant==Normal&&FMath::Ranges[1]==std::make_pair(0,1),"practice rare pools deduplicate repeated base species and replace only one slot");
 }
 {
  auto P=Player();P.Controller.bRelay=true;auto B=Battle(Data);
  Check(B.InitializeWildGroupBattle(&P,{Entry("agumon",20)}),"private training initializes through actual battle adapter");
  const auto&U=B.State.TeamB.Active[0];FDigimonOwnedPartner FullPartner;FullPartner.SpeciesId=U.SpeciesId;FullPartner.Level=20;FullPartner.ABI=10;FullPartner.CAM=20;
  const auto Full=DigimonVenomNXTAutoBattle::BuildUnit(FullPartner,&Data);
  Check(U.ABI==10&&U.CAM==20&&U.Stats.MaxHP==std::max(20,int(Full.Stats.MaxHP*.60))&&U.HP==U.Stats.MaxHP,"source training ABI/CAM and60 percent enemy health");
 }
 {
  auto P=Player();P.Profile.Relay.bFirewallScanMastery=true;auto B=Battle(Data);
  GetDefault<UDigimonVenomNXTSettings>()->RareScanGain=1;
  Check(B.InitializeWildGroupBattle(&P,{Entry("agumon",5,Firewall)}),"fractional mastery fixture starts");PrepareSettlement(B,P);
  B.RecordWildDefeat(B.State.TeamB.Active[0]);
  Check(P.Profile.Scans[0].Percent==1&&P.Profile.Scans[0].FractionalHundredths==0&&B.State.ScannedWildInstances.Num()==1,"defeat scan is secured once; permanent bonus waits for whole battle victory");
  Check(B.FinishPrivateWildMatch(0,"Victory",true),"fractional configured mastery settles");
  Check(P.Profile.Scans[0].Percent==1&&P.Profile.Scans[0].FractionalHundredths==20&&B.State.bWildMasteryPaid,"source20 percent bonus retains fractional configured scan value");
  Check(B.AwardWildMastery(P.Profile).IsEmpty()&&P.Profile.Scans[0].FractionalHundredths==20,"repeat mastery settlement cannot duplicate a fractional bonus");
  GetDefault<UDigimonVenomNXTSettings>()->RareScanGain=5;
 }
 for(int Count:{1,2,3}){
  auto P=Player();auto B=Battle(Data);TArray<FDigimonWildEncounterEntry>Group;int64 XP=0,Credits=0;
  for(int I=0;I<Count;++I){Group.Add(Entry("agumon",1+I));XP+=24+(1+I)*16;Credits=110;}
  Check(B.InitializeWildGroupBattle(&P,Group),"reward fixture starts");PrepareSettlement(B,P);
  Check(B.FinishPrivateWildMatch(0,"Victory",true),"all supported sizes settle");
  for(const auto&Partner:P.Profile.Collection)Check(Partner.Experience==240100+XP,"all party members receive sum-of-opponent XP once");
  Check(P.Profile.Credits==Credits&&P.Profile.Scans.Num()==1&&P.Profile.Scans[0].Percent==Count*10,"source field credits paid once; scans stack per defeated individual");
  Check(!P.Profile.Progress.PendingBattleId.IsValid()&&P.Profile.Progress.BattleCheckpointJson.IsEmpty()&&P.Profile.Progress.LastSettledBattleId==B.State.BattleId,"successful settlement clears pending state and records one result");
  Check(!B.FinishPrivateWildMatch(0,"Again",true)&&P.Profile.Credits==Credits,"repeated settlement cannot grant rewards twice");
 }
 {
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildGroupBattle(&P,{Entry("agumon",8),Entry("agumon",9,Firewall),Entry("gabumon",10,Shiny)}),"mixed reward fixture starts");PrepareSettlement(B,P);
  Check(B.FinishPrivateWildMatch(0,"Victory",true)&&P.Profile.Scans.Num()==3,"mixed species and variants maintain separate scan records");
  Check(P.Profile.Scans[0].Percent==10&&P.Profile.Scans[1].Percent==5&&P.Profile.Scans[2].Percent==5,"each rare member uses configured rare base");
 }
 for(int Mode=0;Mode<3;++Mode){
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildGroupBattle(&P,{Entry(),Entry(),Entry()}),"non-victory fixture starts");PrepareSettlement(B,P);
  if(Mode==0)B.State.bFled=true;
  if(Mode==2)for(auto&U:B.State.TeamA.Active)U.HP=0;
  Check(B.FinishPrivateWildMatch(Mode==0?-1:1,Mode==0?"Fled":"Defeat",Mode!=0),"flee or loss settles without group rewards");
  Check(P.Profile.Credits==0&&P.Profile.Scans.Num()==1&&P.Profile.Scans[0].Percent==30,"loss and flee retain scan already secured from defeated enemies without credits");
  for(const auto&U:P.Profile.Collection)Check(U.Experience==240100,"loss and flee grant no XP");
 }
 {
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildGroupBattle(&P,{Entry(),Entry(),Entry()}),"unresolved fixture starts");PrepareSettlement(B,P);B.State.TeamB.Active[2].HP=1;
  Check(!B.FinishPrivateWildMatch(0,"Premature",true)&&P.Profile.Credits==0,"living final opponent prevents premature group victory");
  B.State.TeamB.Active[2].HP=0;B.bSaveOK=false;Check(!B.FinishPrivateWildMatch(0,"Save failure",true),"persistence failure reports unsuccessful settlement");
  Check(P.Profile.Credits==0&&P.Profile.Scans.Num()==1&&P.Profile.Scans[0].Percent==30&&P.Profile.Collection[0].Experience==240100&&!B.State.bFinished&&P.Profile.Progress.PendingBattleId.IsValid(),"failed save rolls back every group reward and pending battle");
 }
 CHECKPOINT_TESTS
 std::cout<<"PASS actual wild group adapters: "<<Checks<<" checks (portable UE stand-ins; not an Unreal build)\n";
}
'''


CHECKPOINT_TESTS = r'''
 for(int Count:{1,2,3}){
  auto P=Player();auto B=Battle(Data);TArray<FDigimonWildEncounterEntry>Group;
  for(int I=0;I<Count;++I)Group.Add(Entry("agumon",3+I,I==1?Shiny:Normal));
  Check(B.InitializeWildGroupBattle(&P,Group),"restore fixture starts");
  FDigimonSeasonBattleCheckpoint Saved;Saved.State=B.State;Saved.ContextId="campaign:wild:2";FDigimonRelayMap Map;Map.MinLevel=5;Map.MaxLevel=5;FString Error;
  Check(B.ValidateSavedWildGroup(Saved,&Map,EDigimonPrivateCampaign::Relay,Error),"one, two and three opponents pass actual wild checkpoint branch");
  for(int I=0;I<Count;++I){B.State.TeamB.Active[I].HP=I==0?0:17;B.State.TeamB.Active[I].SP=I;B.State.TeamB.Active[I].NextActionTime=42.0+I;}
  const auto Before=B.State;bool Upgraded=false;
  Check(B.RebuildRestoredBattle(Upgraded,Error)&&!Upgraded,"current group checkpoint rebuilds from combat catalog");
  for(int I=0;I<Count;++I){const auto&U=B.State.TeamB.Active[I];const auto&Old=Before.TeamB.Active[I];
   Check(U.InstanceId==Old.InstanceId&&U.SpeciesId==Old.SpeciesId&&U.Variant==Old.Variant&&U.Level==Old.Level,"restoration retains every individual identity and form");
   Check(U.HP==Old.HP&&U.SP==Old.SP&&U.Stats.MaxHP==Old.Stats.MaxHP&&U.NextActionTime==Old.NextActionTime,"restoration preserves per-member injuries, resources and timeline without repeated HP reduction");
  }
 }
 for(int Mode=0;Mode<9;++Mode){
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildGroupBattle(&P,{Entry(),Entry(),Entry()}),"invalid checkpoint fixture starts");
  FDigimonSeasonBattleCheckpoint Saved;Saved.State=B.State;Saved.ContextId="campaign:wild:2";FDigimonRelayMap Map;Map.MinLevel=5;Map.MaxLevel=5;FString Error;
  if(Mode==0)Saved.State.TeamB.Active.Reset();
  if(Mode==1)Saved.State.TeamB.Active.Add(Saved.State.TeamB.Active[0]);
  if(Mode==2)Saved.State.TeamB.Bench.Add(Saved.State.TeamB.Active[0]);
  if(Mode==3)Saved.State.TeamB.Active[2].Level=0;
  if(Mode==4)Saved.State.TeamB.Active[2].Level=6;
  if(Mode==5)Saved.State.TeamB.Active[2].SpeciesId="missing";
  if(Mode==6)Saved.State.TeamB.Active[2].Variant=static_cast<EDigimonVariant>(255);
  if(Mode==7)Saved.ContextId="campaign:wild:3";
  if(Mode==8)Map.MapId=1;
  Check(!B.ValidateSavedWildGroup(Saved,&Map,EDigimonPrivateCampaign::ParadoxChronicles,Error)&&!Error.IsEmpty(),"invalid saved cardinality, reserve, final-member data, context or hub is rejected");
 }
 for(int Mode=0;Mode<4;++Mode){
  auto P=Player();auto B=Battle(Data);Check(B.InitializeWildGroupBattle(&P,{Entry(),Entry(),Entry()}),"saved identity fixture starts");
  if(Mode==0)B.State.TeamB.Active[2].InstanceId=B.State.TeamB.Active[0].InstanceId;
  if(Mode==1)B.State.TeamB.Active[2].InstanceId.Invalidate();
  if(Mode==2)B.State.TeamB.Active[2].TimelineOrder=B.State.TeamB.Active[0].TimelineOrder;
  if(Mode==3)B.State.TeamB.Active[2].NextActionTime=-1;
  bool Upgraded=false;FString Error;Check(!B.RebuildRestoredBattle(Upgraded,Error)&&!Error.IsEmpty(),"restored final opponent cannot use duplicate/missing ID or invalid timeline");
 }
'''


def actual_type(source, name):
    return re.search(r"struct DIGIMONVENOMNXTRUNTIME_API " + name + r"\s*\{.*?\n\};", source, re.S).group()


def main():
    battle = (PRIVATE / "DigimonVenomNXTBattleActor.cpp").read_text()
    game = (PRIVATE / "DigimonVenomNXTGameMode.cpp").read_text()
    types = (PUBLIC / "DigimonVenomNXTTypes.h").read_text()
    header = (PUBLIC / "DigimonVenomNXTBattleActor.h").read_text()
    definitions = "\n".join([
        definition(game, "void ReplaceWildVariety("),
        definition(game, "TArray<FDigimonWildEncounterEntry> BuildRandomWildGroup("),
        definition(battle, "void AddBattleSupply("),
        definition(battle, "int32 AddBattleScan("),
        definition(battle, "void ADigimonVenomNXTBattleActor::RecordWildDefeat("),
        definition(battle, "FString ADigimonVenomNXTBattleActor::AwardWildMastery("),
        definition(battle, "FDigimonBattleUnit ADigimonVenomNXTBattleActor::BuildUnit("),
        definition(battle, "bool ADigimonVenomNXTBattleActor::IsTeamDefeated("),
        definition(battle, "void ADigimonVenomNXTBattleActor::PromoteBench("),
        definition(battle, "FDigimonBattleTeam ADigimonVenomNXTBattleActor::BuildTeamFromProfile("),
        definition(battle, "bool ADigimonVenomNXTBattleActor::InitializeWildBattle("),
        definition(battle, "bool ADigimonVenomNXTBattleActor::InitializeWildGroupBattle("),
        definition(battle, "bool ADigimonVenomNXTBattleActor::FinishPrivateWildMatch("),
        definition(battle, "bool ADigimonVenomNXTBattleActor::RebuildRestoredBattle("),
    ])
    training = definition(game, "ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartRelayFieldTrainingFor(")
    selection = training[training.index("    TArray<FDigimonOwnedPartner> Living;"):training.index("    ADigimonVenomNXTBattleActor* Battle =")]
    # Extract the production selection block unchanged except its early-return
    # value, adapting the UObject factory's nullptr to an empty value array.
    definitions += "\nTArray<FDigimonWildEncounterEntry> BuildTrainingFixture(ADigimonVenomNXTPlayerState* PS, const FDigimonRelayMap* Map, const UDigimonVenomNXTDataSubsystem* Data, EDigimonPrivateCampaign Campaign, FString& OutError) {\n" + selection.replace("return nullptr;", "return {};") + "\nreturn Encounters;\n}\n"
    restore = definition(battle, "bool ADigimonVenomNXTBattleActor::RestoreRelayMatch(")
    wild_branch = definition(restore, "if (Checkpoint.State.Kind == EDigimonBattleKind::Wild)")
    definitions += "\nbool ADigimonVenomNXTBattleActor::ValidateSavedWildGroup(const FDigimonSeasonBattleCheckpoint& Checkpoint, const FDigimonRelayMap* Map, EDigimonPrivateCampaign Campaign, FString& OutError) {\n"
    definitions += "const FString Prefix = DigimonVenomNXTCampaign::ContextPrefix(Campaign);\n" + wild_branch + "\nreturn true;\n}\n"
    with tempfile.TemporaryDirectory(prefix="digimon-wild-groups-") as directory:
        d = Path(directory)
        (d / "CoreMinimal.h").write_text(COMPAT)
        more_types = "\n".join(actual_type(types, name) for name in ("FDigimonScanRecord", "FDigimonBattleTeam", "FDigimonInventoryEntry", "FDigimonWildScanMasteryPending"))
        (d / "DigimonVenomNXTTypes.h").write_text(combat.extract_types() + "\n" + more_types + "\n" + actual_type(header, "FDigimonWildEncounterEntry"))
        (d / "DigimonVenomNXTAutoBattle.h").write_bytes((PUBLIC / "DigimonVenomNXTAutoBattle.h").read_bytes())
        (d / "DigimonVenomNXTDataSubsystem.h").write_text(combat.DATA.replace("public:", "public:\n TArray<FDigimonSpeciesDefinition>GetStarterCandidates(int32)const{TArray<FDigimonSpeciesDefinition>Out;for(const auto&Pair:Species)if(Pair.second.Stage==EDigimonStage::Rookie&&!Pair.second.bPlaceholder)Out.Add(Pair.second);return Out;}"))
        (d / "fixture.cpp").write_text(r'''
#include "DigimonVenomNXTDataSubsystem.h"
void LoadFixture(UDigimonVenomNXTDataSubsystem& Data){
 for(const char*Id:{"agumon","gabumon"}){
  FDigimonSpeciesDefinition S;S.SpeciesId=Id;S.DisplayName=FText::FromString(Id);
  S.Stage=EDigimonStage::Rookie;S.BaseStats.MaxHP=300;S.BaseStats.MaxSP=50;
  S.BaseStats.Attack=30;S.BaseStats.Defense=20;S.BaseStats.Spirit=30;S.BaseStats.Speed=15;
  Data.Species[Id]=S;
 }
}
''')
        (d / "main.cpp").write_text(STUBS + definitions + TESTS.replace("CHECKPOINT_TESTS", CHECKPOINT_TESTS))
        command = shlex.split(os.environ.get("CXX", "g++")) + ["-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", "-I" + str(d), "-I" + str(PUBLIC), str(PRIVATE / "DigimonVenomNXTAutoBattle.cpp"), str(d / "fixture.cpp"), str(d / "main.cpp"), "-o", str(d / "test")]
        subprocess.run(command, check=True, timeout=90)
        subprocess.run([str(d / "test")], check=True, timeout=30)


if __name__ == "__main__":
    main()
