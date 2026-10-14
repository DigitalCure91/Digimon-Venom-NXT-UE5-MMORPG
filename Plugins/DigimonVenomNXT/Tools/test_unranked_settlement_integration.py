#!/usr/bin/env python3
"""Execute actual friendly settlement with observable persistence/world doubles.

Tests atomic publication and retry control. Journal disk behavior belongs to the
separate persistence suite; this does not execute Unreal networking or UHT.
"""
from pathlib import Path
import os
import shlex
import subprocess
import tempfile
import unittest
from test_world_chat_integration import method

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTBattleActor.cpp"
STUBS = r'''
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using int32=int;
constexpr int INDEX_NONE=-1,MAX_int32=INT_MAX;
#define TEXT(Value) Value
#define MoveTemp(Value) std::move(Value)
struct FString : std::string {
    using std::string::string;using std::string::operator=;
    FString()=default;FString(const std::string& V):std::string(V){}
    bool IsEmpty()const{return empty();}
};
template<class T>struct TArray : std::vector<T> {
    using std::vector<T>::vector;
    void Reset(){this->clear();}void Add(const T& V){this->push_back(V);}
    bool IsEmpty()const{return this->empty();}int Num()const{return static_cast<int>(this->size());}
};
template<class T>struct TObjectPtr {
    T* Value=nullptr;TObjectPtr& operator=(T* V){Value=V;return *this;}
    explicit operator bool()const{return Value!=nullptr;}T* Get()const{return Value;}T* operator->()const{return Value;}
};
template<class T>bool IsValid(T* V){return V!=nullptr;}
template<class T,class U>T* Cast(U* V){return dynamic_cast<T*>(V);}
struct FPlatformTime {static double Seconds(){return 100;}};
namespace FMath {template<class T>T Max(T A,T B){return std::max(A,B);}}
struct FDigimonPlayerProfile {
    FString AccountId;
    int UnrankedWins=0,UnrankedLosses=0,UnrankedDraws=0;
    long long CommerceRevision=0,Credits=300;
    int DigiRubies=17,PartyHP=3,PartySP=2,XP=14,RankedRating=1000;
};
struct ADigimonVenomNXTPlayerState {
    FDigimonPlayerProfile Profile;int Notifications=0;
    void MarkProfileChanged(){++Notifications;}
};
struct AController {virtual ~AController()=default;};
struct ADigimonVenomNXTPlayerController : AController {
    bool Authenticated=true;ADigimonVenomNXTPlayerState* State=nullptr;
    bool IsAccountAuthenticated()const{return Authenticated;}
    template<class T>T* GetPlayerState(){return State;}
};
struct Entry {AController* Value;AController* Get()const{return Value;}};
struct FConstPlayerControllerIterator {
    const std::vector<Entry>* Values;std::size_t Index=0;
    explicit operator bool()const{return Index<Values->size();}
    void operator++(){++Index;}const Entry* operator->()const{return &(*Values)[Index];}
};
struct UDigimonVenomNXTProfileSubsystem {
    bool Available=true;int Attempts=0;std::map<FString,FDigimonPlayerProfile> Disk;
    bool LoadExistingCommerceProfile(const FString& Id,FDigimonPlayerProfile& Out){
        auto It=Disk.find(Id);if(It==Disk.end())return false;Out=It->second;return true;
    }
    bool CommitProfileGroup(TArray<FDigimonPlayerProfile>& Candidates,FString&){
        ++Attempts;if(!Available)return false;
        for(auto& C:Candidates)++C.CommerceRevision;
        for(const auto& C:Candidates)Disk[C.AccountId]=C;
        return true;
    }
};
struct UDigimonVenomNXTAIRivalSubsystem {
    int Results=0;bool Won=false,Draw=false;
    void RecordUnrankedResult(const FString&,bool W,bool D){++Results;Won=W;Draw=D;}
};
struct MockGameInstance {
    UDigimonVenomNXTProfileSubsystem* Profiles=nullptr;
    template<class T>T* GetSubsystem(){return Profiles;}
};
struct MockTimer {int Clears=0;void ClearTimer(int){++Clears;}};
struct MockWorld {
    std::vector<Entry> Players;MockTimer Timer;UDigimonVenomNXTAIRivalSubsystem Rivals;
    FConstPlayerControllerIterator GetPlayerControllerIterator(){return {&Players};}
    template<class T>T* GetSubsystem(){return &Rivals;}
    MockTimer& GetTimerManager(){return Timer;}
};
enum class EDigimonBattleKind {Friendly,Wild};
struct ADigimonVenomNXTBattleActor {
    bool Authority=true,bUnrankedSettlementPending=false,bUnrankedResultSaving=false;int PendingUnrankedWinner=INDEX_NONE;
    FString PendingUnrankedReason,BattleContextId;TArray<FDigimonPlayerProfile> PendingUnrankedProfiles;
    TObjectPtr<ADigimonVenomNXTPlayerState> PlayerA,PlayerB;
    struct {EDigimonBattleKind Kind=EDigimonBattleKind::Friendly;bool bFinished=false;int WinningTeam=INDEX_NONE;FString LastEvent;} State;
    double UnrankedDecisionDeadlineServerTime=200,NextUnrankedSettlementAttempt=0;
    int BattleSafetyTimer=1,RetrySchedules=0;
    MockGameInstance* Game=nullptr;MockWorld* World=nullptr;
    bool HasAuthority()const{return Authority;}
    MockGameInstance* GetGameInstance(){return Game;}MockWorld* GetWorld(){return World;}
    void StartBattleSafetyChecks(){++RetrySchedules;}
    bool FinishUnrankedMatch(int32 WinningTeam,const FString& Reason,bool bRecordResult);
};
'''
CASES = r'''
int Checks=0;
void Check(bool OK,const char* Message){++Checks;if(!OK)throw std::runtime_error(Message);}
void Unchanged(const FDigimonPlayerProfile& P){
    Check(P.Credits==300&&P.DigiRubies==17&&P.PartyHP==3&&P.PartySP==2&&P.XP==14&&P.RankedRating==1000,
          "sparring settlement changed expedition HP/SP, XP, money, rubies or rating");
}
struct Fixture {
    UDigimonVenomNXTProfileSubsystem Profiles;MockGameInstance Game;MockWorld World;
    ADigimonVenomNXTPlayerState A,B;ADigimonVenomNXTPlayerController First,Second;ADigimonVenomNXTBattleActor Battle;
    Fixture(){Game.Profiles=&Profiles;A.Profile.AccountId="first";B.Profile.AccountId="second";
        First.State=&A;Second.State=&B;World.Players={{&First},{&Second}};
        Battle.Game=&Game;Battle.World=&World;Battle.PlayerA=&A;Battle.PlayerB=&B;
        Profiles.Disk["first"]=A.Profile;Profiles.Disk["second"]=B.Profile;}
};
int main(){try{
    {Fixture F;Check(F.Battle.FinishUnrankedMatch(0,"won",true),"successful paired settlement failed");
     Check(F.A.Profile.UnrankedWins==1&&F.B.Profile.UnrankedLosses==1,"paired win/loss not published together");
     Check(F.Profiles.Disk["first"].UnrankedWins==1&&F.Profiles.Disk["second"].UnrankedLosses==1,"paired profiles not persisted");
     Check(F.Battle.State.bFinished&&!F.Battle.bUnrankedSettlementPending&&F.Battle.State.WinningTeam==0,"committed match not finished");
     Check(!F.Battle.FinishUnrankedMatch(1,"replay",true)&&F.Profiles.Attempts==1,"finished result applied twice");
     Unchanged(F.A.Profile);Unchanged(F.B.Profile);}
    {Fixture F;F.Profiles.Available=false;
     Check(!F.Battle.FinishUnrankedMatch(0,"original win",true),"failed storage reported success");
     Check(F.A.Profile.UnrankedWins==0&&F.B.Profile.UnrankedLosses==0&&F.A.Notifications==0&&F.B.Notifications==0,"failed storage published half/all results");
     Check(!F.Battle.State.bFinished&&F.Battle.bUnrankedSettlementPending&&F.Battle.RetrySchedules==1,"failed storage did not retain retryable outcome");
     F.A.Profile.Credits=777;F.B.Profile.DigiRubies=99;F.Profiles.Available=true;
     Check(F.Battle.FinishUnrankedMatch(1,"later timeout",true),"retry settlement failed");
     Check(F.A.Profile.UnrankedWins==1&&F.A.Profile.UnrankedLosses==0&&F.B.Profile.UnrankedLosses==1,"retry changed frozen winner or counted twice");
     Check(F.A.Profile.Credits==777&&F.B.Profile.DigiRubies==99,"retry clobbered newer live progress");
     Check(F.Battle.State.LastEvent.find("original win")!=std::string::npos,"retry replaced frozen result reason");}
    {Fixture F;F.Profiles.Available=false;F.Battle.FinishUnrankedMatch(1,"win",true);
     ADigimonVenomNXTPlayerState Reconnected;Reconnected.Profile=F.A.Profile;Reconnected.Profile.CommerceRevision=5;Reconnected.Profile.XP=90;
     F.First.State=&Reconnected;F.Profiles.Available=true;
     Check(F.Battle.FinishUnrankedMatch(1,"retry",true),"reconnected settlement failed");
     Check(Reconnected.Profile.UnrankedLosses==1&&Reconnected.Profile.CommerceRevision==6&&Reconnected.Profile.XP==90,"reconnect snapshot was overwritten with stale profile");
     Check(F.A.Profile.CommerceRevision==6&&F.A.Profile.XP==90,"departing PlayerState retained stale revision for Logout save");}
    {Fixture F;F.Profiles.Available=false;F.Battle.FinishUnrankedMatch(0,"win",true);F.World.Players={{&F.Second}};
     F.Profiles.Disk["first"].XP=71;F.Profiles.Disk["first"].CommerceRevision=8;F.Profiles.Available=true;
     Check(F.Battle.FinishUnrankedMatch(0,"retry",true),"offline participant could not settle");
     Check(F.Profiles.Disk["first"].UnrankedWins==1&&F.Profiles.Disk["first"].XP==71&&F.Profiles.Disk["first"].CommerceRevision==9,"offline settlement used stale captured profile");}
    {Fixture F;F.Profiles.Available=false;F.Battle.FinishUnrankedMatch(0,"win",true);
     F.World.Players={{&F.Second}};F.Profiles.Disk.erase("first");F.Profiles.Available=true;
     Check(!F.Battle.FinishUnrankedMatch(0,"win",true)&&F.Profiles.Attempts==1,"missing offline profile permitted partial commit");
     Check(F.B.Profile.UnrankedLosses==0,"missing offline profile published other participant loss");}
    {Fixture F;F.Game.Profiles=nullptr;Check(!F.Battle.FinishUnrankedMatch(0,"win",true)&&!F.Battle.State.bFinished,"missing persistence failed open");}
    {Fixture F;F.A.Profile.UnrankedDraws=MAX_int32;Check(F.Battle.FinishUnrankedMatch(INDEX_NONE,"draw",true),"draw settlement failed");
     Check(F.A.Profile.UnrankedDraws==MAX_int32&&F.B.Profile.UnrankedDraws==1,"draw counter did not saturate or both increment");}
    {Fixture F;F.Battle.PlayerB=nullptr;F.World.Players={{&F.First}};F.Battle.BattleContextId="rival";
     F.Profiles.Available=false;F.Battle.FinishUnrankedMatch(0,"rival win",true);
     Check(F.World.Rivals.Results==0,"rival stats published before player journal commit");F.Profiles.Available=true;
     Check(F.Battle.FinishUnrankedMatch(0,"retry",true)&&F.World.Rivals.Results==1&&!F.World.Rivals.Won,"rival result did not settle once after player save");}
    {Fixture F;Check(F.Battle.FinishUnrankedMatch(INDEX_NONE,"cancel",false)&&F.Profiles.Attempts==0&&F.A.Profile.UnrankedDraws==0,
        "unrecorded cancellation altered statistics");}
    {Fixture F;F.Battle.Authority=false;Check(!F.Battle.FinishUnrankedMatch(0,"win",true)&&F.Profiles.Attempts==0,"client authored settlement");}
    std::cout<<"Actual friendly settlement: "<<Checks<<" paired publication, retry, reconnect and state-preservation checks passed.\n";
    return 0;
}catch(const std::exception& Error){std::cerr<<Error.what()<<'\n';return 1;}}
'''


class UnrankedSettlementIntegrationTests(unittest.TestCase):
    def test_actual_paired_settlement_retry_and_latest_account_snapshots(self):
        program = STUBS + method(SOURCE.read_text(encoding="utf-8"),
                                "ADigimonVenomNXTBattleActor::FinishUnrankedMatch(") + CASES
        with tempfile.TemporaryDirectory(prefix="digimon-unranked-settlement-") as directory:
            source = Path(directory) / "settlement.cpp"
            binary = Path(directory) / "settlement"
            source.write_text(program, encoding="utf-8")
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", str(source), "-o", str(binary)]
            compiled = subprocess.run(command, capture_output=True, text=True, timeout=45)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout.strip())


if __name__ == "__main__":
    unittest.main()
