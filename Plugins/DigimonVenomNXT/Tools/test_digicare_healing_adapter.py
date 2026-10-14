#!/usr/bin/env python3
"""Exercise actual recovery and economy transactions with portable UE boundary doubles.

The production method and reflected receipt structures are extracted verbatim.
Only UObject, persistence, replication, moderation, audit, and canonical-stat service boundaries are
doubled. This checks transaction ordering; it is not an Unreal compile or a new
implementation of healing or economy rules. Direct ABI feeding also extracts the
real FeedABI method and uses its production progression core. Undefined-behavior
sanitization makes extreme-value arithmetic checks fail on signed overflow.
"""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"


def definition(source, signature):
    start = source.index(signature)
    brace = source.index("{", start)
    depth, end = 1, brace + 1
    while depth:
        depth += (source[end] == "{") - (source[end] == "}")
        end += 1
    return source[start:end]


class RecoveryTransactionAdapterTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which("g++"), "g++ required for portable transaction check")
    def test_actual_recovery_transaction(self):
        player = (PRIVATE / "DigimonVenomNXTPlayerState.cpp").read_text()
        healing_types = (PUBLIC / "DigimonVenomNXTHealingTypes.h").read_text()
        structures = re.sub(r"^#.*$", "", healing_types, flags=re.MULTILINE)
        method = "\n".join(definition(player, name) for name in (
            "void ADigimonVenomNXTPlayerState::ProcessDigiLabHeal(",
            "void ADigimonVenomNXTPlayerState::ServerPurchaseItem_Implementation(",
            "void ADigimonVenomNXTPlayerState::ServerUseHealingItem_Implementation(",
            "void ADigimonVenomNXTPlayerState::ServerFeedABIMeat_Implementation(",
            "void ADigimonVenomNXTPlayerState::ServerConvertDigiRubiesToCredits_Implementation(",
        ))
        feed_abi = definition((PRIVATE / "DigimonVenomNXTEvolution.cpp").read_text(),
                              "int32 DigimonVenomNXTEvolution::FeedABI(")
        settings_source = (PUBLIC / "DigimonVenomNXTSettings.h").read_text()
        settings = re.findall(r"int32\s+(?:SmallHPCapsule|SmallSPCapsule|DigiMeat|CAMMeat|ABIMeat)(?:Credit|Ruby)Cost\s*=\s*\d+\s*;", settings_source)
        self.assertEqual(len(settings), 10, "All shop prices must be extracted from actual settings")
        economy_settings = re.findall(r"int32\s+(?:MaxABI|ABIMeatGain|CreditsPerDigiRuby)\s*=\s*\d+\s*;", settings_source)
        self.assertEqual(len(economy_settings), 3, "ABI and currency defaults must come from actual settings")
        settings += economy_settings
        source = r'''
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTRewardCore.h"
#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
using int32 = int;
using int64 = long long;
constexpr int INDEX_NONE=-1;
constexpr int MAX_int32=std::numeric_limits<int>::max();
constexpr int64 MAX_int64=std::numeric_limits<int64>::max();
#define USTRUCT(...)
#define UPROPERTY(...)
#define GENERATED_BODY(...)
#define DIGIMONVENOMNXTRUNTIME_API
#define TEXT(value) value
#define MoveTemp(value) std::move(value)
struct FString:std::string {
    using std::string::string;
    FString(const std::string& value):std::string(value){}
    bool IsEmpty()const{return empty();}
    bool IsNone()const{return empty();}
    FString ToString()const{return *this;}
    const char* operator*()const{return c_str();}
    static FString Printf(const char* format,...){char buffer[1024];va_list args;va_start(args,format);vsnprintf(buffer,sizeof(buffer),format,args);va_end(args);return buffer;}
};
using FName=FString;
enum class EDigimonCurrency { Credits, DigiRubies };
enum class EDigimonAudioCue { Error, Heal, Confirm, Purchase, Item };
struct FGuid {
    int Value=0;
    bool IsValid()const{return Value>0;}
    bool operator==(const FGuid& other)const{return Value==other.Value;}
    bool operator!=(const FGuid& other)const{return !(*this==other);}
};
template<typename T> struct TArray:std::vector<T> {
    using std::vector<T>::vector;
    int Num()const{return static_cast<int>(this->size());}
    void Add(const T& value){this->push_back(value);}
    void RemoveAt(int index){this->erase(this->begin()+index);}
    template<typename P>const T* FindByPredicate(P predicate)const{for(const auto& value:*this)if(predicate(value))return &value;return nullptr;}
    template<typename P>T* FindByPredicate(P predicate){for(auto& value:*this)if(predicate(value))return &value;return nullptr;}
    template<typename P>int IndexOfByPredicate(P predicate)const{for(int i=0;i<Num();++i)if(predicate((*this)[i]))return i;return INDEX_NONE;}
    int IndexOfByKey(const T& key)const{for(int i=0;i<Num();++i)if((*this)[i]==key)return i;return -1;}
};
struct FMath {
    static int Max(int a,int b){return std::max(a,b);}
    static int Min(int a,int b){return std::min(a,b);}
    template<typename T>static T Clamp(T value,T minimum,T maximum){return std::clamp(value,minimum,maximum);}
};
struct FPlatformTime {inline static double Clock=10.0;static double Seconds(){return Clock;}};
struct FDigimonStats {int MaxHP=100,MaxSP=20;};
struct FDigimonOwnedPartner {
    FGuid InstanceId; int SpeciesId=1,CurrentHP=1,CurrentSP=0,CombatBalanceVersion=1;
    int Level=12,ABI=33,CAM=44,Training=55;FDigimonStats Stats;
};
struct FDigimonBattleUnit {FDigimonStats Stats;};
struct FDigimonSpeciesDefinition {};
struct FDigimonInventoryEntry {FName ItemId;int Quantity=0;};
struct FDigimonPlayerProfile {
    FString AccountId="owner";
    TArray<FDigimonOwnedPartner> Collection;TArray<FGuid> Party;
    TArray<FDigimonInventoryEntry> Inventory;
    int64 Credits=100,DigiLabRecoveryRevision=0;int DigiRubies=20,MapId=17,Position=303,Campaign=2,CampaignProgress=9;
};
// Deliberately small fixture prices isolate transaction/rollback behavior from balance tuning.
struct FDigimonShopItemDefinition { int64 CreditCost=250; int DigiRubyCost=2; FName DisplayName="Fixture item"; int HPHeal=0,SPHeal=0; };
struct UDigimonVenomNXTDataSubsystem {
    int MissingSpecies=-1;
    std::map<FName,FDigimonShopItemDefinition> Items = {
        {"hp_s",{250,2,"HP",DigimonVenomNXTRecoveryCore::SmallHPCapsule,0}},
        {"sp_s",{300,2,"SP",0,DigimonVenomNXTRecoveryCore::SmallSPCapsule}},
        {"digimeat_hp",{750,5,"Training",0,0}},
        {"digimeat_cam",{500,3,"CAM",0,0}},
        {"digimeat_abi",{5000,30,"ABI",0,0}}
    };
    bool GetShopItem(const FName& Id,FDigimonShopItemDefinition& Out)const { auto It=Items.find(Id); if(It==Items.end())return false;Out=It->second;return true; }
    bool GetSpecies(int species,FDigimonSpeciesDefinition&)const{return species!=MissingSpecies;}
};
struct UDigimonVenomNXTProfileSubsystem {
    bool bSucceed=true;int Calls=0;FDigimonPlayerProfile Saved;
    std::function<void(const FDigimonPlayerProfile&)> BeforeSave;
    bool SaveProfile(const FDigimonPlayerProfile& profile){++Calls;if(BeforeSave)BeforeSave(profile);if(!bSucceed)return false;Saved=profile;return true;}
};
struct UGameInstance {
    UDigimonVenomNXTDataSubsystem* Data=nullptr;UDigimonVenomNXTProfileSubsystem* Profiles=nullptr;
    template<typename T>T* GetSubsystem()const{if constexpr(std::is_same_v<T,UDigimonVenomNXTDataSubsystem>)return Data;else return Profiles;}
};
namespace DigimonVenomNXTAutoBattle {
    inline constexpr int CurrentBalanceVersion=1;
    bool MigratePartner(FDigimonOwnedPartner& partner,const UDigimonVenomNXTDataSubsystem*){
        if(partner.CombatBalanceVersion==1)return false;
        partner.CurrentHP*=2;partner.CurrentSP*=2;partner.CombatBalanceVersion=1;return true;
    }
    FDigimonBattleUnit BuildUnit(const FDigimonOwnedPartner& partner,const UDigimonVenomNXTDataSubsystem*){return {partner.Stats};}
}
struct ADigimonVenomNXTPlayerController {
    bool bAuthenticated=true,bLogoutPending=false,bJailed=false;int FarmCaptures=0,CampaignCaptures=0;
    bool IsAccountAuthenticated()const{return bAuthenticated;}
    void CaptureDigiFarmPosition(){++FarmCaptures;}
    void CaptureRelayPosition(){++CampaignCaptures;}
};
struct ADigimonVenomNXTTamerCharacter {int Refreshes=0;void RefreshFollowerFromProfile(){++Refreshes;}};
template<typename T> T* Cast(T* value){return value;}
struct Delegate {int Calls=0;std::function<void()> OnBroadcast;void Broadcast(){++Calls;if(OnBroadcast)OnBroadcast();}};
'''
        source += "struct UDigimonVenomNXTSettings {\n" + "\n".join(settings) + "\n};\n"
        source += "template<typename T>T* GetDefault(){static T Value;return &Value;}\n"
        source += "namespace DigimonVenomNXTEvolution { int32 FeedABI(FDigimonOwnedPartner& Partner); }\n"
        source += feed_abi + "\n"
        source += structures
        source += r'''
struct ADigimonVenomNXTPlayerState {
    bool bAuthority=true,bBattle=false;FDigimonPlayerProfile Profile;
    ADigimonVenomNXTPlayerController* Controller=nullptr;ADigimonVenomNXTTamerCharacter* Pawn=nullptr;UGameInstance* GameInstance=nullptr;
    TArray<FDigimonHealReceipt> RecentDigiLabHealReceipts,Sent;
    double LastDigiLabHealRequestTime=-100.0;int Snapshots=0,NetUpdates=0,Notices=0;
    Delegate OnProfileChanged;std::vector<EDigimonAudioCue> Cues;
    std::vector<FString> ActivityActions;
    bool HasAuthority()const{return bAuthority;}bool HasActiveBattle()const{return bBattle;}
    ADigimonVenomNXTPlayerController* GetOwner(){return Controller;}ADigimonVenomNXTTamerCharacter* GetPawn(){return Pawn;}UGameInstance* GetGameInstance(){return GameInstance;}
    void ClientDigiLabHealResult(const FDigimonHealReceipt& value){Sent.Add(value);}
    void NotifyProgression(const char*,const FString&,EDigimonAudioCue cue){++Notices;Cues.push_back(cue);}
    void RefreshPublicSnapshot(){++Snapshots;}void ForceNetUpdate(){++NetUpdates;}
    void MarkProfileChanged(){RefreshPublicSnapshot();ForceNetUpdate();OnProfileChanged.Broadcast();}
    void ProcessDigiLabHeal(const FGuid&,bool);
    void ServerPurchaseItem_Implementation(FName,EDigimonCurrency,int32);
    void ServerUseHealingItem_Implementation(FGuid,FName);
    void ServerFeedABIMeat_Implementation(FGuid,EDigimonCurrency);
    void ServerConvertDigiRubiesToCredits_Implementation(int32);
};
namespace DigimonVenomNXTServerActivity {
    // Moderation and audit are service boundaries; production transaction methods
    // below remain extracted verbatim. Server helper authorization has its own tests.
    bool AllowGameplay(ADigimonVenomNXTPlayerState* state,FString* error=nullptr){
        const bool allowed=state && state->HasAuthority() && !state->Profile.AccountId.IsEmpty() &&
            state->Controller && state->Controller->bAuthenticated && !state->Controller->bLogoutPending && !state->Controller->bJailed;
        if(!allowed && error)*error="Gameplay unavailable.";
        return allowed;
    }
    void Record(ADigimonVenomNXTPlayerState* state,const FString&,const FString& action,const FString&,const FString& = "Info"){
        if(!state || !state->HasAuthority())return;
        if(action=="Recovery saved" || action=="Currency converted")assert(state->GameInstance && state->GameInstance->Profiles && state->GameInstance->Profiles->Calls>0 && state->GameInstance->Profiles->bSucceed);
        state->ActivityActions.push_back(action);
    }
}
struct Fixture {
    UDigimonVenomNXTDataSubsystem Data;UDigimonVenomNXTProfileSubsystem Saves;UGameInstance GameInstance;
    ADigimonVenomNXTPlayerController Controller;ADigimonVenomNXTTamerCharacter Pawn;ADigimonVenomNXTPlayerState State;
    Fixture(){*GetDefault<UDigimonVenomNXTSettings>()=UDigimonVenomNXTSettings{};GameInstance.Data=&Data;GameInstance.Profiles=&Saves;State.GameInstance=&GameInstance;State.Controller=&Controller;State.Pawn=&Pawn;}
    void Partner(int id,int hp,int sp,bool party=true){FDigimonOwnedPartner partner;partner.InstanceId={id};partner.CurrentHP=hp;partner.CurrentSP=sp;State.Profile.Collection.Add(partner);if(party)State.Profile.Party.Add({id});}
    void Inventory(FName item,int quantity){State.Profile.Inventory.Add({item,quantity});}
    int Quantity(FName item)const{const auto*e=State.Profile.Inventory.FindByPredicate([&](const auto&entry){return entry.ItemId==item;});return e?e->Quantity:0;}
    const FDigimonHealReceipt& Run(int request=1,bool legacy=false){FPlatformTime::Clock+=1.0;State.ProcessDigiLabHeal({request},legacy);assert(!State.Sent.empty());return State.Sent.back();}
};
'''
        source += method
        source += r'''
int main(){
    int checks=0;
    auto check=[&](bool condition){++checks;if(!condition){std::cerr<<"Recovery adapter assertion "<<checks<<" failed\n";std::abort();}};
    {
        Fixture f;f.Partner(1,12,3);f.Partner(2,100,20);f.Partner(3,0,0,false);
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(f.State.Profile.Collection[0].CurrentHP==12);check(f.State.Sent.empty());check(f.State.OnProfileChanged.Calls==0);check(candidate.Collection[0].CurrentHP==100);};
        f.State.OnProfileChanged.OnBroadcast=[&](){check(f.Saves.Calls==1);check(f.Saves.Saved.Collection[0].CurrentHP==100);check(f.State.Sent.empty());};
        const auto& r=f.Run();check(r.bSuccess);check(r.RestoredPartners==2);check(r.PartyChanges.Num()==1);check(r.PartyChanges[0].InstanceId==FGuid{1});check(r.PartyChanges[0].BeforeHP==12);check(r.PartyChanges[0].BeforeSP==3);check(r.PartyChanges[0].AfterHP==100);check(r.PartyChanges[0].AfterSP==20);
        for(const auto& p:f.State.Profile.Collection){check(p.CurrentHP==100);check(p.CurrentSP==20);check(p.Level==12&&p.ABI==33&&p.CAM==44&&p.Training==55);}
        check(f.State.Profile.Credits==100&&f.State.Profile.DigiRubies==20);check(f.State.Profile.MapId==17&&f.State.Profile.Position==303&&f.State.Profile.Campaign==2&&f.State.Profile.CampaignProgress==9);check(f.Controller.FarmCaptures==1&&f.Controller.CampaignCaptures==1);check(f.State.NetUpdates==1&&f.State.Snapshots==1&&f.Pawn.Refreshes==1);
    }
    {
        Fixture f;f.Partner(1,8,2);f.Partner(2,0,0,false);f.Saves.bSucceed=false;
        const auto&r=f.Run();check(!r.bSuccess);check(r.RestoredPartners==0&&r.PartyChanges.empty());check(f.State.Profile.Collection[0].CurrentHP==8&&f.State.Profile.Collection[1].CurrentHP==0);check(f.State.Profile.Collection[0].CurrentSP==2);check(f.State.OnProfileChanged.Calls==0&&f.State.NetUpdates==0&&f.Pawn.Refreshes==0);check(f.Saves.Calls==1);
    }
    {
        Fixture f;f.Partner(1,100,20);const auto&r=f.Run();check(r.bSuccess);check(r.RestoredPartners==0&&r.PartyChanges.empty());check(f.Saves.Calls==1);
        Fixture empty;const auto&e=empty.Run();check(e.bSuccess&&e.RestoredPartners==0&&e.PartyChanges.empty());
    }
    {
        Fixture f;f.Partner(1,1,0);f.State.bBattle=true;const auto&r=f.Run();check(!r.bSuccess&&r.PartyChanges.empty());check(f.Saves.Calls==0&&f.State.Profile.Collection[0].CurrentHP==1);check(f.Controller.CampaignCaptures==0);
        Fixture unauth;unauth.Partner(1,1,0);unauth.Controller.bAuthenticated=false;check(!unauth.Run().bSuccess);check(unauth.Saves.Calls==0);
        Fixture invalid;invalid.Partner(1,1,0);check(!invalid.Run(0).bSuccess);check(invalid.State.RecentDigiLabHealReceipts.empty()&&invalid.Saves.Calls==0);
        Fixture owner;owner.State.Controller=nullptr;check(!owner.Run().bSuccess);
        Fixture account;account.State.Profile.AccountId="";check(!account.Run().bSuccess);
        Fixture client;client.State.bAuthority=false;client.State.ProcessDigiLabHeal({1},false);check(client.State.Sent.empty()&&client.Saves.Calls==0);
    }
    {
        Fixture f;f.Partner(1,1,0);check(f.Run(42).bSuccess);f.State.Profile.Collection[0].CurrentHP=7;f.State.bBattle=true;
        const auto&r=f.Run(42);check(r.bSuccess&&r.PartyChanges[0].BeforeHP==1);check(f.State.Profile.Collection[0].CurrentHP==7&&f.Saves.Calls==1);check(f.State.OnProfileChanged.Calls==1);
        Fixture failed;failed.Partner(1,2,0);failed.Saves.bSucceed=false;check(!failed.Run(5).bSuccess);failed.Saves.bSucceed=true;check(!failed.Run(5).bSuccess);check(failed.State.Profile.Collection[0].CurrentHP==2&&failed.Saves.Calls==1);check(failed.Run(6).bSuccess);
    }
    {
        Fixture f;for(int i=1;i<=32;++i)f.Partner(i,i,0);const auto&r=f.Run();check(r.bSuccess&&r.RestoredPartners==32);check(r.PartyChanges.Num()==6);
        for(int i=0;i<6;++i)check(r.PartyChanges[i].InstanceId==FGuid{i+1});
        for(const auto&p:f.State.Profile.Collection)check(p.CurrentHP==100&&p.CurrentSP==20);
        for(int i=2;i<=40;++i){check(f.Run(i).bSuccess);check(f.State.RecentDigiLabHealReceipts.Num()<=16);}check(f.State.RecentDigiLabHealReceipts.Num()==16);check(f.State.RecentDigiLabHealReceipts[0].RequestId==FGuid{25});
    }
    {
        Fixture f;f.Partner(1,-50,-10);f.State.Profile.Collection[0].Stats.MaxHP=0;f.State.Profile.Collection[0].Stats.MaxSP=0;
        const auto&r=f.Run();check(r.bSuccess&&r.PartyChanges.Num()==1);check(r.PartyChanges[0].BeforeHP==0&&r.PartyChanges[0].BeforeSP==0);check(r.PartyChanges[0].AfterHP==1&&r.PartyChanges[0].AfterSP==0);check(r.PartyChanges[0].MaxHP==1&&r.PartyChanges[0].MaxSP==0);
        Fixture excess;excess.Partner(1,10000,10000);const auto&e=excess.Run();check(e.bSuccess&&e.RestoredPartners==0&&e.PartyChanges.empty());check(excess.State.Profile.Collection[0].CurrentHP==100&&excess.State.Profile.Collection[0].CurrentSP==20);
    }
    {
        Fixture f;f.Partner(1,10,1);f.Partner(2,5,2);f.State.Profile.Collection[1].SpeciesId=99;f.Data.MissingSpecies=99;
        const auto&r=f.Run();check(!r.bSuccess&&r.PartyChanges.empty());check(f.Saves.Calls==0&&f.State.Profile.Collection[0].CurrentHP==10&&f.State.Profile.Collection[1].CurrentHP==5);
        Fixture service;service.GameInstance.Data=nullptr;check(!service.Run().bSuccess);check(service.Saves.Calls==0);
        Fixture persist;persist.GameInstance.Profiles=nullptr;check(!persist.Run().bSuccess);
        Fixture game;game.State.GameInstance=nullptr;check(!game.Run().bSuccess);
    }
    {
        Fixture f;f.Partner(1,10,2);f.State.Profile.Collection[0].CombatBalanceVersion=0;const auto&r=f.Run();check(r.bSuccess);check(r.PartyChanges[0].BeforeHP==20&&r.PartyChanges[0].BeforeSP==4);check(f.State.Profile.Collection[0].CombatBalanceVersion==1);
        Fixture failed;failed.Partner(1,10,2);failed.State.Profile.Collection[0].CombatBalanceVersion=0;failed.Saves.bSucceed=false;check(!failed.Run().bSuccess);check(failed.State.Profile.Collection[0].CurrentHP==10&&failed.State.Profile.Collection[0].CombatBalanceVersion==0);
    }
    {
        Fixture f;f.Partner(1,10,0);check(f.Run(1,true).bSuccess);check(f.State.Notices==1);f.State.ProcessDigiLabHeal({2},false);check(!f.State.Sent.back().bSuccess);check(f.Saves.Calls==1);
        FPlatformTime::Clock+=0.51;f.State.ProcessDigiLabHeal({3},false);check(f.State.Sent.back().bSuccess);check(f.Saves.Calls==2);
    }
    {
        Fixture f;f.Partner(1,10,0);f.State.Profile.DigiLabRecoveryRevision=27;
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(f.State.Profile.DigiLabRecoveryRevision==27);check(candidate.DigiLabRecoveryRevision==28);check(f.State.Sent.empty());};
        const auto&r=f.Run(7);check(r.bSuccess&&r.RecoveryRevision==28);check(f.State.Profile.DigiLabRecoveryRevision==28&&f.Saves.Saved.DigiLabRecoveryRevision==28);
        f.Saves.BeforeSave=nullptr;const auto&noop=f.Run(8);check(noop.bSuccess&&noop.RestoredPartners==0&&noop.RecoveryRevision==29);check(f.State.Profile.DigiLabRecoveryRevision==29&&f.Saves.Saved.DigiLabRecoveryRevision==29);
        const auto&old=f.Run(7);check(old.RecoveryRevision==28);check(f.State.Profile.DigiLabRecoveryRevision==29&&f.Saves.Calls==2);
        Fixture failed;failed.Partner(1,10,0);failed.State.Profile.DigiLabRecoveryRevision=13;failed.Saves.bSucceed=false;const auto&failure=failed.Run();check(!failure.bSuccess&&failure.RecoveryRevision==0);check(failed.State.Profile.DigiLabRecoveryRevision==13);
        Fixture negative;negative.State.Profile.DigiLabRecoveryRevision=-10;check(negative.Run().RecoveryRevision==1);
        Fixture overflow;overflow.State.Profile.DigiLabRecoveryRevision=MAX_int64;check(overflow.Run().RecoveryRevision==MAX_int64);
    }
    {
        Fixture f;f.State.Profile.Credits=10000;f.Inventory("hp_s",4);
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(f.State.Profile.Credits==10000&&f.Quantity("hp_s")==4);check(f.State.Cues.empty());check(candidate.Credits==9250);};
        f.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,3);
        check(f.State.Profile.Credits==9250&&f.Quantity("hp_s")==7);check(f.Saves.Calls==1);check(f.State.Cues.size()==1&&f.State.Cues.back()==EDigimonAudioCue::Purchase);check(f.State.OnProfileChanged.Calls==1);
        Fixture failed;failed.State.Profile.Credits=10000;failed.Inventory("hp_s",4);failed.Saves.bSucceed=false;
        failed.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,3);
        check(failed.State.Profile.Credits==10000&&failed.Quantity("hp_s")==4);check(failed.State.OnProfileChanged.Calls==0);check(failed.State.Cues.back()==EDigimonAudioCue::Error);
    }
    {
        Fixture f;f.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,1);
        check(f.State.Profile.Credits==100&&f.Quantity("hp_s")==0&&f.Saves.Calls==0);check(f.State.Cues.back()==EDigimonAudioCue::Error);
        f.State.ServerPurchaseItem_Implementation("digimeat_abi",EDigimonCurrency::DigiRubies,1);check(f.State.Profile.DigiRubies==20&&f.Saves.Calls==0);
        f.State.ServerPurchaseItem_Implementation("digimeat_cam",EDigimonCurrency::DigiRubies,2);check(f.Quantity("digimeat_cam")==2&&f.Quantity("CAMDigiMeat")==0);check(f.State.Profile.DigiRubies==14);
        for(const char* item:{"hp_s","sp_s","digimeat_hp","digimeat_cam","digimeat_abi"}){
            Fixture each;each.State.Profile.Credits=100000;each.State.ServerPurchaseItem_Implementation(item,EDigimonCurrency::Credits,2);check(each.Quantity(item)==2&&each.Saves.Calls==1&&each.State.Cues.back()==EDigimonAudioCue::Purchase);
        }
    }
    {
        Fixture f;f.State.Profile.Credits=MAX_int64;f.Inventory("hp_s",MAX_int32);
        f.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,99);check(f.State.Profile.Credits==MAX_int64&&f.Quantity("hp_s")==MAX_int32&&f.Saves.Calls==0);
        Fixture exact;exact.State.Profile.Credits=100000;exact.Inventory("hp_s",MAX_int32-99);exact.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,9999);check(exact.Quantity("hp_s")==MAX_int32-99&&exact.State.Profile.Credits==100000&&exact.Saves.Calls==0);
        Fixture negative;negative.State.Profile.Credits=1000;negative.Inventory("hp_s",-4);negative.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,-2);check(negative.Quantity("hp_s")==-4&&negative.State.Profile.Credits==1000&&negative.Saves.Calls==0);
        Fixture bigRuby;bigRuby.State.Profile.DigiRubies=MAX_int32;bigRuby.Data.Items["hp_s"].DigiRubyCost=MAX_int32;bigRuby.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::DigiRubies,99);check(bigRuby.State.Profile.DigiRubies==MAX_int32&&bigRuby.Saves.Calls==0);
        Fixture zeroRuby;zeroRuby.Data.Items["hp_s"].DigiRubyCost=-1;zeroRuby.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::DigiRubies,2);check(zeroRuby.State.Profile.DigiRubies==20&&zeroRuby.Quantity("hp_s")==2);
    }
    {
        Fixture f;f.State.Profile.Credits=100000;f.State.bBattle=true;f.State.ServerPurchaseItem_Implementation("digimeat_hp",EDigimonCurrency::Credits,1);check(f.Saves.Calls==0&&f.Quantity("digimeat_hp")==0);
        f.State.bBattle=false;f.State.ServerPurchaseItem_Implementation("Unknown",EDigimonCurrency::Credits,1);check(f.Saves.Calls==0&&f.State.Profile.Credits==100000);
        f.State.ServerPurchaseItem_Implementation("digimeat_hp",static_cast<EDigimonCurrency>(99),1);check(f.Saves.Calls==0);
        f.GameInstance.Profiles=nullptr;f.State.ServerPurchaseItem_Implementation("digimeat_hp",EDigimonCurrency::Credits,1);check(f.Quantity("digimeat_hp")==0&&f.State.Profile.Credits==100000);
        Fixture account;account.State.Profile.AccountId="";account.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::DigiRubies,1);check(account.Saves.Calls==0&&account.State.Cues.empty());
    }
    {
        Fixture f;f.Partner(1,900,20);f.State.Profile.Collection[0].Stats.MaxHP=1000;f.Inventory("hp_s",2);
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(f.State.Profile.Collection[0].CurrentHP==900&&f.Quantity("hp_s")==2);check(f.State.Cues.empty());check(candidate.Collection[0].CurrentHP==1000);};
        f.State.ServerUseHealingItem_Implementation({1},"hp_s");check(f.State.Profile.Collection[0].CurrentHP==1000&&f.Quantity("hp_s")==1);check(f.State.Profile.Collection[0].CurrentSP==20);check(f.State.Cues.back()==EDigimonAudioCue::Item&&f.State.OnProfileChanged.Calls==1);
        Fixture failed;failed.Partner(1,10,0);failed.Inventory("hp_s",1);failed.Saves.bSucceed=false;failed.State.ServerUseHealingItem_Implementation({1},"hp_s");check(failed.State.Profile.Collection[0].CurrentHP==10&&failed.Quantity("hp_s")==1);check(failed.State.Cues.back()==EDigimonAudioCue::Error&&failed.State.OnProfileChanged.Calls==0);
    }
    {
        Fixture full;full.Partner(1,100,20);full.Inventory("hp_s",1);full.Inventory("sp_s",1);
        full.State.ServerUseHealingItem_Implementation({1},"hp_s");full.State.ServerUseHealingItem_Implementation({1},"sp_s");check(full.Quantity("hp_s")==1&&full.Quantity("sp_s")==1&&full.Saves.Calls==0);
        Fixture empty;empty.Partner(1,0,0);empty.State.Profile.Collection[0].Stats={1000,200};empty.Inventory("hp_s",1);empty.Inventory("sp_s",1);
        empty.State.ServerUseHealingItem_Implementation({1},"hp_s");check(empty.State.Profile.Collection[0].CurrentHP==DigimonVenomNXTRecoveryCore::SmallHPCapsule&&empty.Quantity("hp_s")==0);check(empty.State.Profile.Collection[0].CurrentSP==0);
        empty.State.ServerUseHealingItem_Implementation({1},"sp_s");check(empty.State.Profile.Collection[0].CurrentSP==DigimonVenomNXTRecoveryCore::SmallSPCapsule&&empty.Quantity("sp_s")==0);check(empty.State.Profile.Inventory.empty());
        Fixture cap;cap.Partner(1,100,18);cap.Inventory("sp_s",1);cap.State.ServerUseHealingItem_Implementation({1},"sp_s");check(cap.State.Profile.Collection[0].CurrentSP==20&&cap.Quantity("sp_s")==0);
        Fixture zero;zero.Partner(1,100,0);zero.State.Profile.Collection[0].Stats.MaxSP=0;zero.Inventory("sp_s",1);zero.State.ServerUseHealingItem_Implementation({1},"sp_s");check(zero.Quantity("sp_s")==1&&zero.Saves.Calls==0);
    }
    {
        Fixture f;f.Partner(1,10,1);f.Inventory("hp_s",1);f.State.bBattle=true;f.State.ServerUseHealingItem_Implementation({1},"hp_s");check(f.Saves.Calls==0&&f.Quantity("hp_s")==1&&f.State.Profile.Collection[0].CurrentHP==10);
        f.State.bBattle=false;f.State.ServerUseHealingItem_Implementation({999},"hp_s");check(f.Saves.Calls==0&&f.Quantity("hp_s")==1);
        f.State.ServerUseHealingItem_Implementation({1},"sp_s");check(f.Saves.Calls==0&&f.State.Profile.Collection[0].CurrentSP==1);
        f.State.ServerUseHealingItem_Implementation({1},"digimeat_hp");check(f.Saves.Calls==0);
        f.Data.MissingSpecies=1;f.State.ServerUseHealingItem_Implementation({1},"hp_s");check(f.Saves.Calls==0&&f.Quantity("hp_s")==1);
        f.Data.MissingSpecies=-1;f.GameInstance.Profiles=nullptr;f.State.ServerUseHealingItem_Implementation({1},"hp_s");check(f.Quantity("hp_s")==1&&f.State.Profile.Collection[0].CurrentHP==10);
        Fixture migration;migration.Partner(1,10,1);migration.State.Profile.Collection[0].CombatBalanceVersion=0;migration.Inventory("hp_s",1);migration.Saves.bSucceed=false;migration.State.ServerUseHealingItem_Implementation({1},"hp_s");check(migration.State.Profile.Collection[0].CombatBalanceVersion==0&&migration.State.Profile.Collection[0].CurrentHP==10&&migration.Quantity("hp_s")==1);
    }
    {
        Fixture jailed;jailed.Partner(1,9,0);jailed.Controller.bJailed=true;
        const auto&r=jailed.Run();check(!r.bSuccess&&jailed.Saves.Calls==0&&jailed.State.Profile.Collection[0].CurrentHP==9);
        check(jailed.State.ActivityActions.size()==1&&jailed.State.ActivityActions[0]=="Recovery rejected");
        jailed.State.Profile.Credits=10000;jailed.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,2);
        check(jailed.State.Profile.Credits==10000&&jailed.Quantity("hp_s")==0&&jailed.Saves.Calls==0);
        jailed.Inventory("hp_s",1);jailed.State.ServerUseHealingItem_Implementation({1},"hp_s");
        check(jailed.Quantity("hp_s")==1&&jailed.State.Profile.Collection[0].CurrentHP==9&&jailed.Saves.Calls==0);
        Fixture logout;logout.Partner(1,7,0);logout.Controller.bLogoutPending=true;logout.Inventory("hp_s",1);
        check(!logout.Run().bSuccess&&logout.Saves.Calls==0);logout.State.ServerUseHealingItem_Implementation({1},"hp_s");
        check(logout.Quantity("hp_s")==1&&logout.State.Profile.Collection[0].CurrentHP==7);
        Fixture failed;failed.Partner(1,5,0);failed.Saves.bSucceed=false;check(!failed.Run().bSuccess);
        check(failed.State.ActivityActions.size()==1&&failed.State.ActivityActions[0]=="Recovery rejected");
        Fixture committed;committed.Partner(1,4,0);check(committed.Run().bSuccess);
        check(committed.State.ActivityActions.size()==1&&committed.State.ActivityActions[0]=="Recovery saved");
        committed.Run();check(committed.State.ActivityActions.size()==1); // Replay sends receipt without duplicate audit.
    }
    // The source inventory cap is 999, with atomic rejection instead of charging
    // for a partial purchase. Test both currency paths at the exact boundary.
    for(const auto currency:{EDigimonCurrency::Credits,EDigimonCurrency::DigiRubies}){
        Fixture exact;exact.State.Profile.Credits=100000;exact.State.Profile.DigiRubies=1000;exact.Inventory("hp_s",900);
        exact.State.ServerPurchaseItem_Implementation("hp_s",currency,99);
        check(exact.Quantity("hp_s")==999&&exact.Saves.Calls==1);
        check(exact.State.Profile.Credits==(currency==EDigimonCurrency::Credits?75250:100000));
        check(exact.State.Profile.DigiRubies==(currency==EDigimonCurrency::DigiRubies?802:1000));
        const auto credits=exact.State.Profile.Credits;const auto rubies=exact.State.Profile.DigiRubies;
        exact.State.ServerPurchaseItem_Implementation("hp_s",currency,1);
        check(exact.Quantity("hp_s")==999&&exact.Saves.Calls==1);
        check(exact.State.Profile.Credits==credits&&exact.State.Profile.DigiRubies==rubies);
        check(exact.State.Cues.back()==EDigimonAudioCue::Error);
        Fixture overflow;overflow.State.Profile.Credits=100000;overflow.State.Profile.DigiRubies=1000;overflow.Inventory("hp_s",901);
        overflow.State.ServerPurchaseItem_Implementation("hp_s",currency,99);
        check(overflow.Quantity("hp_s")==901&&overflow.Saves.Calls==0);
        check(overflow.State.Profile.Credits==100000&&overflow.State.Profile.DigiRubies==1000);
        Fixture failed;failed.State.Profile.Credits=100000;failed.State.Profile.DigiRubies=1000;failed.Inventory("hp_s",998);failed.Saves.bSucceed=false;
        failed.State.ServerPurchaseItem_Implementation("hp_s",currency,1);
        check(failed.Quantity("hp_s")==998&&failed.Saves.Calls==1);
        check(failed.State.Profile.Credits==100000&&failed.State.Profile.DigiRubies==1000&&failed.State.OnProfileChanged.Calls==0);
    }
    for(const int quantity:{0,-1,100,MAX_int32,std::numeric_limits<int>::min()}){
        Fixture f;f.State.Profile.Credits=100000;f.State.Profile.DigiRubies=1000;
        f.State.ServerPurchaseItem_Implementation("hp_s",EDigimonCurrency::Credits,quantity);
        check(f.Saves.Calls==0&&f.Quantity("hp_s")==0&&f.State.Profile.Credits==100000&&f.State.Profile.DigiRubies==1000);
    }
    // Exchange never publishes either balance or a success event before the
    // persistence boundary has accepted the same complete candidate profile.
    {
        Fixture f;f.Partner(1,7,2);f.Inventory("hp_s",3);
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){
            check(f.State.Profile.Credits==100&&f.State.Profile.DigiRubies==20);
            check(candidate.Credits==800&&candidate.DigiRubies==13);
            check(f.State.OnProfileChanged.Calls==0&&f.State.Cues.empty()&&f.State.ActivityActions.empty());
        };
        f.State.OnProfileChanged.OnBroadcast=[&](){
            check(f.Saves.Calls==1&&f.Saves.Saved.Credits==800&&f.Saves.Saved.DigiRubies==13);
            check(f.State.Profile.Credits==800&&f.State.Profile.DigiRubies==13&&f.State.Cues.empty());
        };
        f.State.ServerConvertDigiRubiesToCredits_Implementation(7);
        check(f.State.Profile.Credits==800&&f.State.Profile.DigiRubies==13);
        check(f.State.Cues.size()==1&&f.State.Cues.back()==EDigimonAudioCue::Purchase);
        check(f.State.ActivityActions.size()==1&&f.State.ActivityActions[0]=="Currency converted");
        check(f.State.OnProfileChanged.Calls==1&&f.State.Snapshots==1&&f.State.NetUpdates==1);
        check(f.State.Profile.Collection[0].CurrentHP==7&&f.State.Profile.Collection[0].CurrentSP==2&&f.Quantity("hp_s")==3);
        check(f.State.Profile.MapId==17&&f.State.Profile.Position==303&&f.State.Profile.CampaignProgress==9);
        Fixture failed;failed.Saves.bSucceed=false;
        failed.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(candidate.Credits==800&&candidate.DigiRubies==13);check(failed.State.Profile.Credits==100&&failed.State.Profile.DigiRubies==20);};
        failed.State.ServerConvertDigiRubiesToCredits_Implementation(7);
        check(failed.State.Profile.Credits==100&&failed.State.Profile.DigiRubies==20&&failed.Saves.Calls==1);
        check(failed.State.OnProfileChanged.Calls==0&&failed.State.ActivityActions.empty()&&failed.State.Cues.back()==EDigimonAudioCue::Error);
        Fixture missing;missing.GameInstance.Profiles=nullptr;missing.State.ServerConvertDigiRubiesToCredits_Implementation(7);
        check(missing.State.Profile.Credits==100&&missing.State.Profile.DigiRubies==20&&missing.State.OnProfileChanged.Calls==0);
        Fixture game;game.State.GameInstance=nullptr;game.State.ServerConvertDigiRubiesToCredits_Implementation(7);
        check(game.State.Profile.Credits==100&&game.State.Profile.DigiRubies==20&&game.State.OnProfileChanged.Calls==0);
    }
    for(const int amount:{0,-1,std::numeric_limits<int>::min(),21,MAX_int32}){
        Fixture f;f.State.ServerConvertDigiRubiesToCredits_Implementation(amount);
        check(f.Saves.Calls==0&&f.State.Profile.Credits==100&&f.State.Profile.DigiRubies==20&&f.State.OnProfileChanged.Calls==0);
    }
    {
        Fixture negative;negative.State.Profile.DigiRubies=-1;negative.State.ServerConvertDigiRubiesToCredits_Implementation(1);
        check(negative.Saves.Calls==0&&negative.State.Profile.DigiRubies==-1&&negative.State.Profile.Credits==100);
        constexpr int64 cap=DigimonVenomNXTRewardCore::MaxCredits;
        Fixture exact;exact.State.Profile.Credits=cap-100;exact.State.ServerConvertDigiRubiesToCredits_Implementation(1);
        check(exact.Saves.Calls==1&&exact.State.Profile.Credits==cap&&exact.State.Profile.DigiRubies==19);
        exact.State.ServerConvertDigiRubiesToCredits_Implementation(1);
        check(exact.Saves.Calls==1&&exact.State.Profile.Credits==cap&&exact.State.Profile.DigiRubies==19);
        for(const int64 invalid:{int64{-1},std::numeric_limits<int64>::min(),cap-99,cap,cap+1,MAX_int64}){
            Fixture f;f.State.Profile.Credits=invalid;f.State.ServerConvertDigiRubiesToCredits_Implementation(1);
            check(f.State.Profile.Credits==invalid&&f.State.Profile.DigiRubies==20&&f.Saves.Calls==0&&f.State.OnProfileChanged.Calls==0);
        }
        Fixture huge;huge.State.Profile.Credits=0;huge.State.Profile.DigiRubies=MAX_int32;GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby=MAX_int32;
        huge.State.ServerConvertDigiRubiesToCredits_Implementation(MAX_int32);
        check(huge.Saves.Calls==1&&huge.State.Profile.Credits==int64{MAX_int32}*100000&&huge.State.Profile.DigiRubies==0);
        check(huge.State.Profile.Credits<=cap);
        for(const int rate:{std::numeric_limits<int>::min(),-1,0,1,100000,MAX_int32}){
            Fixture f;GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby=rate;
            f.State.ServerConvertDigiRubiesToCredits_Implementation(20);
            const int expectedRate=std::clamp(rate,1,100000);
            check(f.State.Profile.Credits==100+int64{20}*expectedRate&&f.State.Profile.DigiRubies==0&&f.Saves.Calls==1);
        }
        Fixture edge;GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby=100000;
        edge.State.Profile.DigiRubies=MAX_int32;edge.State.Profile.Credits=cap-int64{MAX_int32}*100000;
        edge.State.ServerConvertDigiRubiesToCredits_Implementation(MAX_int32);
        check(edge.State.Profile.Credits==cap&&edge.State.Profile.DigiRubies==0&&edge.Saves.Calls==1);
        Fixture over;GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby=100000;
        over.State.Profile.DigiRubies=MAX_int32;const int64 before=cap-int64{MAX_int32}*100000+1;over.State.Profile.Credits=before;
        over.State.ServerConvertDigiRubiesToCredits_Implementation(MAX_int32);
        check(over.State.Profile.Credits==before&&over.State.Profile.DigiRubies==MAX_int32&&over.Saves.Calls==0);
    }
    // Direct ABI food purchases use the extracted FeedABI implementation, retain
    // other permanent state, and commit the currency/stat mutation together.
    for(const auto currency:{EDigimonCurrency::Credits,EDigimonCurrency::DigiRubies}){
        Fixture f;f.Partner(1,7,2);f.Partner(2,8,3,false);f.Inventory("digimeat_abi",4);
        f.State.Profile.Credits=10000;f.State.Profile.DigiRubies=100;
        const int64 afterCredits=currency==EDigimonCurrency::Credits?5000:10000;
        const int afterRubies=currency==EDigimonCurrency::DigiRubies?70:100;
        f.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){
            check(f.State.Profile.Credits==10000&&f.State.Profile.DigiRubies==100&&f.State.Profile.Collection[0].ABI==33);
            check(candidate.Credits==afterCredits&&candidate.DigiRubies==afterRubies&&candidate.Collection[0].ABI==34);
            check(f.State.OnProfileChanged.Calls==0&&f.State.Cues.empty());
        };
        f.State.OnProfileChanged.OnBroadcast=[&](){check(f.Saves.Calls==1&&f.Saves.Saved.Collection[0].ABI==34&&f.Saves.Saved.Credits==afterCredits&&f.Saves.Saved.DigiRubies==afterRubies);};
        f.State.ServerFeedABIMeat_Implementation({1},currency);
        check(f.State.Profile.Credits==afterCredits&&f.State.Profile.DigiRubies==afterRubies&&f.State.Profile.Collection[0].ABI==34);
        check(f.State.Profile.Collection[0].CurrentHP==7&&f.State.Profile.Collection[0].CurrentSP==2&&f.State.Profile.Collection[0].CAM==44&&f.State.Profile.Collection[0].Training==55);
        check(f.State.Profile.Collection[1].ABI==33&&f.Quantity("digimeat_abi")==4);
        check(f.State.OnProfileChanged.Calls==1&&f.State.Cues.back()==EDigimonAudioCue::Item);
        Fixture failed;failed.Partner(1,7,2);failed.State.Profile.Credits=10000;failed.State.Profile.DigiRubies=100;failed.Saves.bSucceed=false;
        failed.Saves.BeforeSave=[&](const FDigimonPlayerProfile& candidate){check(candidate.Collection[0].ABI==34);check(failed.State.Profile.Collection[0].ABI==33);};
        failed.State.ServerFeedABIMeat_Implementation({1},currency);
        check(failed.State.Profile.Credits==10000&&failed.State.Profile.DigiRubies==100&&failed.State.Profile.Collection[0].ABI==33&&failed.Saves.Calls==1);
        check(failed.State.OnProfileChanged.Calls==0&&failed.State.Cues.back()==EDigimonAudioCue::Error);
        Fixture insufficient;insufficient.Partner(1,7,2);
        insufficient.State.ServerFeedABIMeat_Implementation({1},currency);
        check(insufficient.Saves.Calls==0&&insufficient.State.Profile.Credits==100&&insufficient.State.Profile.DigiRubies==20&&insufficient.State.Profile.Collection[0].ABI==33);
    }
    {
        Fixture invalid;invalid.Partner(1,7,2);invalid.State.Profile.Credits=10000;
        invalid.State.ServerFeedABIMeat_Implementation({1},static_cast<EDigimonCurrency>(99));
        check(invalid.Saves.Calls==0&&invalid.State.Profile.Credits==10000&&invalid.State.Profile.DigiRubies==20&&invalid.State.Profile.Collection[0].ABI==33);
        invalid.State.ServerFeedABIMeat_Implementation({999},EDigimonCurrency::Credits);
        check(invalid.Saves.Calls==0&&invalid.State.Profile.Credits==10000&&invalid.State.Profile.Collection[0].ABI==33);
        Fixture cap;cap.Partner(1,7,2);cap.State.Profile.Credits=10000;cap.State.Profile.Collection[0].ABI=200;
        cap.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(cap.Saves.Calls==0&&cap.State.Profile.Credits==10000&&cap.State.Profile.Collection[0].ABI==200);
        Fixture lowered;lowered.Partner(1,7,2);lowered.State.Profile.Credits=10000;lowered.State.Profile.Collection[0].ABI=100;GetDefault<UDigimonVenomNXTSettings>()->MaxABI=40;
        lowered.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(lowered.Saves.Calls==0&&lowered.State.Profile.Credits==10000&&lowered.State.Profile.Collection[0].ABI==100);
        Fixture near;near.Partner(1,7,2);near.State.Profile.Credits=10000;near.State.Profile.Collection[0].ABI=199;GetDefault<UDigimonVenomNXTSettings>()->ABIMeatGain=MAX_int32;
        near.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(near.Saves.Calls==1&&near.State.Profile.Collection[0].ABI==200&&near.State.Profile.Credits==5000);
        Fixture negative;negative.Partner(1,7,2);negative.State.Profile.Credits=10000;negative.State.Profile.Collection[0].ABI=std::numeric_limits<int>::min();GetDefault<UDigimonVenomNXTSettings>()->ABIMeatGain=std::numeric_limits<int>::min();
        negative.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(negative.Saves.Calls==1&&negative.State.Profile.Collection[0].ABI==1&&negative.State.Profile.Credits==5000);
        Fixture free;free.Partner(1,7,2);free.State.Profile.DigiRubies=0;free.Data.Items["digimeat_abi"].DigiRubyCost=0;
        free.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::DigiRubies);
        check(free.Saves.Calls==1&&free.State.Profile.DigiRubies==0&&free.State.Profile.Collection[0].ABI==34);
    }
    for(int missing=0;missing<4;++missing){
        Fixture f;f.Partner(1,7,2);f.State.Profile.Credits=10000;
        if(missing==0)f.GameInstance.Data=nullptr;
        if(missing==1)f.GameInstance.Profiles=nullptr;
        if(missing==2)f.State.GameInstance=nullptr;
        if(missing==3)f.Data.Items.erase("digimeat_abi");
        f.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(f.Saves.Calls==0&&f.State.Profile.Credits==10000&&f.State.Profile.DigiRubies==20&&f.State.Profile.Collection[0].ABI==33&&f.State.OnProfileChanged.Calls==0);
    }
    // Both RPCs share the same authority/authentication/moderation/battle gates.
    for(int gate=0;gate<7;++gate){
        Fixture f;f.Partner(1,7,2);f.State.Profile.Credits=10000;
        if(gate==0)f.State.bBattle=true;
        if(gate==1)f.State.bAuthority=false;
        if(gate==2)f.Controller.bAuthenticated=false;
        if(gate==3)f.Controller.bJailed=true;
        if(gate==4)f.Controller.bLogoutPending=true;
        if(gate==5)f.State.Profile.AccountId="";
        if(gate==6)f.State.Controller=nullptr;
        f.State.ServerConvertDigiRubiesToCredits_Implementation(1);
        f.State.ServerFeedABIMeat_Implementation({1},EDigimonCurrency::Credits);
        check(f.Saves.Calls==0&&f.State.Profile.Credits==10000&&f.State.Profile.DigiRubies==20&&f.State.Profile.Collection[0].ABI==33);
        check(f.State.OnProfileChanged.Calls==0&&f.State.ActivityActions.empty());
    }
    std::cout<<"Actual DigiLab, shop, capsule, ABI and exchange adapters: "<<checks<<" transaction, authority, receipt, persistence, economy and replay checks passed\n";
}
'''
        with tempfile.TemporaryDirectory(prefix="digimon-recovery-adapter-") as temporary:
            cpp = Path(temporary) / "recovery_adapter.cpp"
            executable = Path(temporary) / "recovery_adapter"
            cpp.write_text(source)
            build = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", "-fsanitize=undefined", "-fno-sanitize-recover=undefined", "-I", str(PUBLIC), str(cpp), "-o", str(executable)], capture_output=True, text=True, timeout=60)
            self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
            result = subprocess.run([str(executable)], capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout.strip())


if __name__ == "__main__":
    unittest.main()
