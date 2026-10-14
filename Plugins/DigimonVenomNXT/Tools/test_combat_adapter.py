#!/usr/bin/env python3
"""Compile/run the actual AutoBattle adapter using production structs and tiny UE stand-ins.

This checks C++ signatures, adapter/core integration and migration invariants. It
is not UHT, engine compilation, real UObject containers or an Unreal save test.
The JSON fixtures come from the shipped combat and species registries.
"""
import json
import os
import pathlib
import re
import shlex
import subprocess
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[1]
PUBLIC = ROOT / 'Source/DigimonVenomNXTRuntime/Public'
COMPAT = r'''
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>
using TCHAR=char; using int32=int; using int64=long long; using uint8=unsigned char; using uint32=unsigned;
#define TEXT(X) X
#define DIGIMONVENOMNXTRUNTIME_API
#define GENERATED_BODY()
#define UPROPERTY(...)
#define UMETA(...)
#define MoveTemp(X) std::move(X)
constexpr int32 INDEX_NONE=-1;
constexpr int32 MAX_int32=std::numeric_limits<int32>::max();
struct FString {
 std::string Value;
 FString()=default;FString(const char*S):Value(S){}FString(std::string S):Value(std::move(S)){}
 const char*operator*()const{return Value.c_str();}
 bool IsEmpty()const{return Value.empty();}
 friend bool operator==(const FString&A,const FString&B){return A.Value==B.Value;}
 friend bool operator!=(const FString&A,const FString&B){return !(A==B);}
 static FString Printf(const char*Format,...){char Out[8192];va_list Args;va_start(Args,Format);vsnprintf(Out,sizeof(Out),Format,Args);va_end(Args);return Out;}
};
struct FText {FString Value;static FText FromString(const FString&S){return {S};}FString ToString()const{return Value;}};
struct FName {
 std::string Value; FName()=default;FName(const char*S):Value(S){}
 bool IsNone()const{return Value.empty();}FString ToString()const{return Value;}
 friend bool operator==(const FName&A,const FName&B){return A.Value==B.Value;}
 friend bool operator!=(const FName&A,const FName&B){return !(A==B);}
};
inline const FName NAME_None;
struct FGuid {unsigned Value=0;static FGuid NewGuid(){static unsigned Next=0;return {++Next};}bool IsValid()const{return Value!=0;}friend bool operator==(FGuid A,FGuid B){return A.Value==B.Value;}friend bool operator!=(FGuid A,FGuid B){return !(A==B);}};
template<class T> struct TArray:std::vector<T>{
 using std::vector<T>::vector;using std::vector<T>::operator=;
 void Add(const T&V){this->push_back(V);}void Reserve(int32 N){this->reserve(N);}
 bool IsEmpty()const{return this->empty();}
 int32 Num()const{return static_cast<int32>(this->size());}
};
struct FMath {
 template<class T>static T Min(T A,T B){return std::min(A,B);}
 template<class T>static T Max(T A,T B){return std::max(A,B);}
 template<class T>static T Clamp(T V,T A,T B){return std::clamp(V,A,B);}
 static int32 FloorToInt(float V){return static_cast<int32>(std::floor(V));}
};
class UPaperFlipbook;
template<class T>struct TSoftObjectPtr {};
'''
DATA = r'''
#pragma once
#include "DigimonVenomNXTTypes.h"
class UDigimonVenomNXTDataSubsystem {
public:
 std::map<std::string,FDigimonSpeciesDefinition> Species;
 std::map<std::string,FDigimonMoveSlot> Moves;
 bool GetSpecies(FName Id,FDigimonSpeciesDefinition&Out)const{auto I=Species.find(Id.Value);if(I==Species.end())return false;Out=I->second;return true;}
 bool GetMove(FName Id,FDigimonMoveSlot&Out)const{auto I=Moves.find(Id.Value);if(I==Moves.end())return false;Out=I->second;return true;}
};
'''
HARNESS = r'''
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include <cstdlib>
#include <iostream>
static int Checks=0;
static void Check(bool Value,const char* Message){++Checks;if(!Value){std::cerr<<"FAIL actual combat adapter: "<<Message<<"\n";std::exit(1);}}
void LoadFixture(UDigimonVenomNXTDataSubsystem& Data);
static int PreviousMaximum(EDigimonStage Stage,int Level,int Training,bool SP){
 // Independently pinned to the pre-rebalance release, not production migration helpers.
 const int H[]={55,70,100,145,205,275},S[]={24,28,40,55,72,92};
 int Index=static_cast<int>(Stage);if(Index>5)Index=Index<=7?5:2;
 return static_cast<int>(std::round(((SP?S[Index]:H[Index])+Training)*(1.0+(Level-1)*0.035)));
}
static int Fraction(int Current,int OldMax,int NewMax,bool Living){
 if(Current<=0)return 0;
 return std::max(Living?1:0,static_cast<int>(std::llround(std::min(Current,OldMax)*static_cast<long double>(NewMax)/OldMax)));
}
int main(){
 using namespace DigimonVenomNXTAutoBattle;
 UDigimonVenomNXTDataSubsystem Data;LoadFixture(Data);
 int Provided=0;
 for(const auto& Pair:Data.Species){
  const auto& Def=Pair.second;if(Def.bPlaceholder)continue;++Provided;
  for(int Level:{1,5,50,99,100,200})for(int ABI:{0,80,200}){
   FDigimonOwnedPartner P;P.InstanceId=FGuid::NewGuid();P.SpeciesId=Def.SpeciesId;P.Level=Level;P.ABI=ABI;
   P.CAM=43;P.Experience=123456;P.Nickname="Kept nickname";P.Variant=EDigimonVariant::Firewall;
   P.PermanentTraining.MaxHP=55;P.PermanentTraining.MaxSP=9;P.PermanentTraining.Attack=13;P.PermanentTraining.Spirit=17;
   int OldHP=PreviousMaximum(Def.Stage,Level,55,false),OldSP=PreviousMaximum(Def.Stage,Level,9,true);
   P.CurrentHP=OldHP;P.CurrentSP=OldSP;
   const auto Full=BuildUnit(P,&Data);
   Check(Full.HP==Full.Stats.MaxHP&&Full.SP==Full.Stats.MaxSP,"legacy full vitals become canonical full vitals");
   Check(P.CombatBalanceVersion==0&&P.CurrentHP==OldHP,"BuildUnit does not mutate persisted source");
   int Rank=static_cast<int>(Def.Stage);if(Rank==7||Rank==8)Rank=2;if(Rank==9||Rank==10)Rank=3;
   int ExpectedHP=static_cast<int>(std::floor((Def.BaseStats.MaxHP+(Level-1)*(18.0+2.0*Rank))*(1.0+ABI/1000.0)))+55;
   int ExpectedINT=static_cast<int>(std::floor((Def.BaseStats.Spirit+(Level-1)*(3.0+.3*Rank))*(1.0+ABI/1000.0)))+17;
   Check(Full.Stats.MaxHP==ExpectedHP&&Full.Stats.Spirit==ExpectedINT,"additive growth, ABI then unscaled permanent training");
   P.CurrentHP=OldHP/3;P.CurrentSP=0;const auto Id=P.InstanceId;
   Check(MigratePartner(P,&Data),"legacy persisted partner migrates once");
   if(P.CurrentHP!=Fraction(OldHP/3,OldHP,ExpectedHP,true))std::cerr<<"Diagnostic "<<Def.SpeciesId.Value<<" level="<<Level<<" ABI="<<ABI<<" old="<<OldHP<<" new="<<ExpectedHP<<" got="<<P.CurrentHP<<" expected="<<Fraction(OldHP/3,OldHP,ExpectedHP,true)<<"\n";
   Check(P.CurrentHP==Fraction(OldHP/3,OldHP,ExpectedHP,true)&&P.CurrentSP==0,"partial HP fraction and exhausted SP survive");
   Check(P.CombatBalanceVersion==CurrentBalanceVersion&&P.InstanceId==Id&&P.Level==Level&&P.ABI==ABI&&P.Experience==123456&&P.CAM==43&&P.Nickname=="Kept nickname"&&P.Variant==EDigimonVariant::Firewall,"migration preserves earned identity and progression");
   int MigratedHP=P.CurrentHP;Check(!MigratePartner(P,&Data)&&P.CurrentHP==MigratedHP,"repeat migration cannot rescale or heal");
   P.CurrentHP=11;P.CurrentSP=3;auto Current=BuildUnit(P,&Data);
   Check(Current.HP==11&&Current.SP==3,"versioned current injury is never fraction-converted again");
   P.CombatBalanceVersion=0;P.CurrentHP=0;auto Dead=BuildUnit(P,&Data);Check(Dead.HP==0&&Dead.bDefeated,"legacy fainted remains fainted");
   P.CurrentHP=1;auto Alive=BuildUnit(P,&Data);Check(Alive.HP>=1&&!Alive.bDefeated,"legacy one-HP survives rounding");
   P.CurrentSP=OldSP/3;auto PartialSP=BuildUnit(P,&Data);Check(PartialSP.SP==Fraction(OldSP/3,OldSP,PartialSP.Stats.MaxSP,false),"legacy nonzero SP fraction uses the captured old scale");
   P.CurrentHP=MAX_int32;P.CurrentSP=MAX_int32;auto Healed=BuildUnit(P,&Data);
   Check(Healed.HP==Healed.Stats.MaxHP&&Healed.SP==Healed.Stats.MaxSP,"ranked MAX_int32 sentinel remains fully healed");
  }
 }
 Check(Provided==502,"entire supplied roster exercised");
 // Actual inherited legacy IDs keep their slots while stale arbitrary power/cost is discarded.
 FDigimonOwnedPartner P;P.InstanceId=FGuid::NewGuid();P.SpeciesId="agumon";P.Level=50;P.ABI=120;
 P.CombatBalanceVersion=CurrentBalanceVersion;P.CurrentHP=MAX_int32;P.CurrentSP=MAX_int32;
 FDigimonMoveSlot M;M.MoveId="burst";M.Power=999999;M.SPCost=-1;M.Element=EDigimonElement::Dark;M.DamageClass=EDigimonDamageClass::Physical;P.Moves.Add(M);
 M.MoveId="strike";P.Moves.Add(M);M.MoveId="UnknownInherited";P.Moves.Add(M);
 const auto Before=BuildUnit(P,&Data);const auto Def=Data.Species.at(P.SpeciesId.Value);const auto Catalog=Data.Moves.at("burst");
 Check(Before.Moves.Num()==3&&Before.Moves[0].MoveId=="burst"&&Before.Moves[1].MoveId=="strike"&&Before.Moves[2].MoveId=="UnknownInherited","equipped inherited IDs and order are retained");
 Check(Before.Moves[0].Power==Catalog.Power&&Before.Moves[0].SPCost==Catalog.SPCost+Catalog.SPCostPerRank*2&&Before.Moves[0].DamageClass==Catalog.DamageClass,"canonical metadata defeats tampered saved move power and cost");
 Check(Before.Moves[2].Power==100&&Before.Moves[2].SPCost==0&&Before.Moves[2].Element==EDigimonElement::Neutral&&Before.Moves[2].DamageClass==EDigimonDamageClass::Physical,"unknown equipped legacy ID receives safe neutral fallback");
 Check(MigratePartner(P,&Data)&&!MigratePartner(P,&Data),"canonical move repair on versioned partner is idempotent");
 auto Evolved=Def;Evolved.SpeciesId="test_water_mega";Evolved.Stage=EDigimonStage::Mega;Evolved.Element=EDigimonElement::Water;Data.Species[Evolved.SpeciesId.Value]=Evolved;P.SpeciesId=Evolved.SpeciesId;
 auto Mega=BuildUnit(P,&Data);Check(Mega.Moves[0].SPCost==Catalog.SPCost+Catalog.SPCostPerRank*5,"evolution resolves stage cost from immutable base exactly once");
 if(Catalog.bUsesSpeciesElement)Check(Mega.Moves[0].Element==EDigimonElement::Water,"evolved inherited species-element move follows actual new form");
 P.Moves=Mega.Moves;auto Again=BuildUnit(P,&Data);Check(Again.Moves[0].SPCost==Mega.Moves[0].SPCost,"loading already-resolved cost never compounds stage additions");
 P.PermanentTraining.MaxHP=55;P.PermanentTraining.Spirit=17;
 auto Checkpoint=BuildUnit(P,&Data);Checkpoint.CombatBalanceVersion=0;Checkpoint.Stats.MaxHP=500;Checkpoint.Stats.MaxSP=250;Checkpoint.HP=123;Checkpoint.SP=0;
 Checkpoint.NextActionTime=1234.5;Checkpoint.TimelineOrder=9;Checkpoint.bGuarding=true;
 const auto Fresh=BuildUnit(P,&Data);
 Check(RebuildSavedUnit(Checkpoint,&Data,&P),"legacy checkpoint adapter succeeds");
 Check(Checkpoint.HP==Fraction(123,500,Fresh.Stats.MaxHP,true)&&Checkpoint.SP==0,"checkpoint uses its captured maxima, not owner current health");
 Check(Checkpoint.Stats.Spirit==Fresh.Stats.Spirit&&Checkpoint.CAM==P.CAM&&Checkpoint.ABI==P.ABI,"checkpoint retains owned ABI, training and CAM");
 auto NoOwner=Fresh;Check(RebuildSavedUnit(NoOwner,&Data,nullptr)&&NoOwner.Stats.Spirit<Fresh.Stats.Spirit,"trained season opponents require their saved owner record on restoration");
 Check(Checkpoint.NextActionTime==1234.5&&Checkpoint.TimelineOrder==9&&Checkpoint.bGuarding,"saved CTB position and guard survive stat conversion");
 int CheckpointHP=Checkpoint.HP;Check(RebuildSavedUnit(Checkpoint,&Data,&P)&&Checkpoint.HP==CheckpointHP,"current-version checkpoint restoration never fraction-converts twice");
 auto Wild=BuildUnit(P,&Data);Wild.CombatBalanceVersion=0;Wild.Stats.MaxHP=1000;Wild.HP=250;
 Check(RebuildSavedUnit(Wild,&Data,&P,true),"wild checkpoint adapter succeeds");
 int WildMax=static_cast<int>(std::floor(Fresh.Stats.MaxHP*0.72f));int WildHP=Wild.HP;
 Check(Wild.Stats.MaxHP==WildMax&&Wild.HP==Fraction(250,1000,WildMax,true),"wild seventy-two-percent maximum applied before vitality conversion");
 Check(RebuildSavedUnit(Wild,&Data,&P,true)&&Wild.Stats.MaxHP==WildMax&&Wild.HP==WildHP,"wild reduction applies once across repeated checkpoint restores");
 auto PrivateWild=BuildUnit(P,&Data);Check(RebuildSavedUnit(PrivateWild,&Data,&P,true,true)&&PrivateWild.Stats.MaxHP==static_cast<int>(std::floor(Fresh.Stats.MaxHP*0.60)),"private field HP is sixty percent and ABI survives restore");
 auto Trainer=Fresh;Check(RebuildSavedUnit(Trainer,&Data,&P,false)&&Trainer.Stats.MaxHP==Fresh.Stats.MaxHP,"trainer checkpoint keeps normal maximum");
 auto Missing=Trainer;Missing.SpeciesId="missing_species";Check(!RebuildSavedUnit(Missing,&Data,&P)&&Missing.HP==Trainer.HP,"missing species fails closed without replacing saved vitals");
 FDigimonOwnedPartner Unknown=P;Unknown.SpeciesId="missing_species";Unknown.CombatBalanceVersion=0;Check(!MigratePartner(Unknown,&Data)&&Unknown.CombatBalanceVersion==0,"unknown owned record is not falsely marked migrated");
 P.CurrentHP=MAX_int32;P.CurrentSP=MAX_int32;TArray<FDigimonOwnedPartner>A{P},B{P};
 auto Duel=Resolve(A,B,&Data,1,987,true,false);auto Encounter=Resolve(A,B,&Data,1,987,true,true);
 Check(Duel.InitialTeamA[0].Stats.MaxHP==Duel.InitialTeamB[0].Stats.MaxHP,"ranked/season automatic duel stats stay symmetric");
 Check(Encounter.InitialTeamA[0].Stats.MaxHP==Duel.InitialTeamA[0].Stats.MaxHP&&Encounter.InitialTeamB[0].Stats.MaxHP==WildMax,"automatic wild reduction affects only wild enemy");
 Check(Encounter.InitialTeamB[0].HP==WildMax&&A[0].CurrentHP==MAX_int32&&B[0].CurrentHP==MAX_int32,"automatic resolver uses isolated healed snapshots");
 Check(!Duel.Actions.IsEmpty()&&!Encounter.Actions.IsEmpty(),"production automatic resolver emits playable action traces");
 std::cout<<"PASS actual combat adapter: "<<Checks<<" checks (portable UE stand-ins; not an Unreal build)\n";
}
'''

def extract_types():
    source = (PUBLIC / 'DigimonVenomNXTTypes.h').read_text()
    chunks = ['#pragma once\n#include "CoreMinimal.h"\n']
    for name in ('EDigimonVariant','EDigimonStage','EDigimonAffinity','EDigimonElement','EDigimonDamageClass'):
        chunks.append(re.search(r'enum class '+name+r'\s*:\s*uint8\s*\{.*?\n\};', source, re.S).group())
    for name in ('FDigimonStats','FDigimonEvolutionRequirement','FDigimonMoveSlot','FDigimonAnimationRefs','FDigimonSpeciesDefinition','FDigimonOwnedPartner','FDigimonBattleUnit'):
        chunks.append(re.search(r'struct DIGIMONVENOMNXTRUNTIME_API '+name+r'\s*\{.*?\n\};', source, re.S).group())
    return '\n'.join(chunks)


def fixtures():
    q = lambda value: json.dumps(value, ensure_ascii=True)
    species = json.loads((ROOT / 'Resources/DigimonSpecies.json').read_text())['species']
    moves = json.loads((ROOT / 'Resources/DigimonCombat.json').read_text())['moves']
    lines = ['#include "DigimonVenomNXTDataSubsystem.h"\nvoid LoadFixture(UDigimonVenomNXTDataSubsystem& D){']
    for row in species:
        lines.append('{ FDigimonSpeciesDefinition S;')
        for key, field in (('speciesId','SpeciesId'),('combatRole','CombatRole')):
            lines.append(f'S.{field}={q(row[key])};')
        lines.append(f'S.DisplayName=FText::FromString({q(row["displayName"])});')
        lines.append(f'S.Stage=EDigimonStage::{row["stage"].replace("-","")};S.Affinity=EDigimonAffinity::{row["affinity"]};S.Element=EDigimonElement::{row["element"]};')
        lines.append(f'S.bPlaceholder={str(row["placeholder"]).lower()};')
        for key, field in (('maxHP','MaxHP'),('maxSP','MaxSP'),('attack','Attack'),('defense','Defense'),('spirit','Spirit'),('speed','Speed')):
            lines.append(f'S.BaseStats.{field}={row["baseStats"][key]};')
        for move in row['learnableMoves']:
            lines.append(f'S.LearnableMoves.Add({q(move)});')
        lines.append('D.Species[S.SpeciesId.Value]=S;}')
    for row in moves:
        lines.append('{ FDigimonMoveSlot M;')
        lines.append(f'M.MoveId={q(row["moveId"])};M.DisplayName=FText::FromString({q(row["displayName"])});M.Description={q(row["description"])};')
        lines.append(f'M.Power={row["power"]};M.SPCost={row["spCost"]};M.SPCostPerRank={row["spCostPerRank"]};')
        lines.append(f'M.DamageClass=EDigimonDamageClass::{row["damageClass"]};M.Element=EDigimonElement::{row["element"]};M.bUsesSpeciesElement={str(row["usesSpeciesElement"]).lower()};')
        lines.append('D.Moves[M.MoveId.Value]=M;}')
    lines.append('}')
    return '\n'.join(lines)


def main():
    with tempfile.TemporaryDirectory(prefix='digimon-combat-adapter-') as directory:
        d=pathlib.Path(directory)
        (d/'CoreMinimal.h').write_text(COMPAT)
        (d/'DigimonVenomNXTTypes.h').write_text(extract_types())
        (d/'DigimonVenomNXTAutoBattle.h').write_bytes((PUBLIC/'DigimonVenomNXTAutoBattle.h').read_bytes())
        (d/'DigimonVenomNXTDataSubsystem.h').write_text(DATA)
        (d/'main.cpp').write_text(HARNESS)
        (d/'fixture.cpp').write_text(fixtures())
        cmd=shlex.split(os.environ.get('CXX','g++'))+['-std=c++17','-Wall','-Wextra','-Werror','-pedantic','-I'+str(d),'-I'+str(PUBLIC),str(ROOT/'Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTAutoBattle.cpp'),str(d/'fixture.cpp'),str(d/'main.cpp'),'-o',str(d/'test')]
        subprocess.run(cmd,check=True,timeout=90)
        subprocess.run([str(d/'test')],check=True,timeout=30)

if __name__=='__main__':
    main()
