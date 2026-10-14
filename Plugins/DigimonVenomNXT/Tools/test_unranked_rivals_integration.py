#!/usr/bin/env python3
"""Execute actual bot-pair selection and recording with an observable combat seam.

The shared combat resolver has separate real-core tests. This harness checks the
production caller's habitat, busy, level, snapshot and paired-result boundaries.
"""
from pathlib import Path
import os
import shlex
import subprocess
import tempfile
import unittest
from test_world_chat_integration import method

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTAIRivalSubsystem.cpp"
STUBS = r'''
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
using int32=int;using int64=long long;
constexpr int MAX_int32=INT_MAX;
#define TEXT(Value) Value
struct FString : std::string {
    using std::string::string;using std::string::operator=;
    FString()=default;FString(const std::string& V):std::string(V){}
    const char* operator*()const{return c_str();}
    template<class... A>static FString Printf(const char* Format,A... Args){char Buffer[1024];std::snprintf(Buffer,sizeof(Buffer),Format,Args...);return Buffer;}
};
template<class T>struct TArray : std::vector<T> {using std::vector<T>::vector;bool IsEmpty()const{return this->empty();}};
template<class T>struct TSet : std::set<T> {bool Contains(const T& V)const{return this->count(V)>0;}};
struct FDigimonOwnedPartner {int CurrentHP=8,CurrentSP=4;};
struct FDigimonAIRivalRecord {
    FString RivalId,DisplayName,CurrentActivity;int MapId=1,TrainingLevel=10;
    int64 NextActionUnix=0,LastSimulatedUnix=0;TArray<FDigimonOwnedPartner> Partners={{8,4}};
};
struct FRandomStream {int RandHelper(int){return 0;}int RandRange(int A,int){return A;}};
struct FDateTime {static FDateTime UtcNow(){return {};}int64 ToUnixTimestamp()const{return 1000;}};
namespace FMath {template<class T>T Max(T A,T B){return std::max(A,B);}int Abs(int V){return std::abs(V);}}
struct UDigimonVenomNXTSettings {int ActiveBattleSize=3,AIRivalActionIntervalSeconds=20;};
template<class T>T* GetDefault(){static T S;return &S;}
namespace DigimonVenomNXTAutoBattle {
    struct Result {TArray<FDigimonOwnedPartner> TeamA,TeamB;bool bTeamAWon=false,bDraw=false;};
    inline int Calls=0;inline bool AWins=true,Draw=false,Valid=true,Restored=false;
    Result Resolve(TArray<FDigimonOwnedPartner>& A,TArray<FDigimonOwnedPartner>& B,int*,int,int){
        ++Calls;Restored=A[0].CurrentHP==MAX_int32&&A[0].CurrentSP==MAX_int32&&B[0].CurrentHP==MAX_int32&&B[0].CurrentSP==MAX_int32;
        A[0].CurrentHP=0;B[0].CurrentSP=0;
        if(!Valid)return {};
        return {A,B,AWins,Draw};
    }
}
struct UDigimonVenomNXTAIRivalSubsystem {
    struct {TArray<FDigimonAIRivalRecord> Rivals;} SaveData;
    TSet<FString> LiveBattleRivals;bool Data=true;
    struct Recorded {FString Id;bool Won,Draw,Persist;};std::vector<Recorded> Results;
    int GetActiveRivalCount()const{return static_cast<int>(SaveData.Rivals.size());}
    int* GetData(){static int D;return Data?&D:nullptr;}
    int PartyTrainingLevel(const FDigimonAIRivalRecord& R)const{return R.TrainingLevel;}
    void RecordUnrankedResult(const FString& Id,bool Won,bool Draw,bool Persist){Results.push_back({Id,Won,Draw,Persist});}
    bool TrySimulateUnranked(FDigimonAIRivalRecord& Rival,FRandomStream& Random);
};
'''
CASES = r'''
int Checks=0;
void Check(bool OK,const char* Message){++Checks;if(!OK)throw std::runtime_error(Message);}
struct Fixture {
    UDigimonVenomNXTAIRivalSubsystem Bots;FRandomStream Random;
    Fixture(){DigimonVenomNXTAutoBattle::Calls=0;DigimonVenomNXTAutoBattle::AWins=true;DigimonVenomNXTAutoBattle::Draw=false;DigimonVenomNXTAutoBattle::Valid=true;
        FDigimonAIRivalRecord A,B;A.RivalId="a";A.DisplayName="Alpha";B.RivalId="b";B.DisplayName="Beta";
        Bots.SaveData.Rivals={A,B};}
    bool Run(){return Bots.TrySimulateUnranked(Bots.SaveData.Rivals[0],Random);}
    void Unchanged(){Check(Bots.SaveData.Rivals[0].Partners[0].CurrentHP==8&&Bots.SaveData.Rivals[0].Partners[0].CurrentSP==4&&
        Bots.SaveData.Rivals[1].Partners[0].CurrentHP==8&&Bots.SaveData.Rivals[1].Partners[0].CurrentSP==4,"simulation damaged real expedition party");}
};
int main(){try{
    {Fixture F;Check(F.Run(),"eligible same-map rivals never battled");Check(DigimonVenomNXTAutoBattle::Calls==1&&DigimonVenomNXTAutoBattle::Restored,"simulation did not resolve restored snapshots");
     Check(F.Bots.Results.size()==2&&F.Bots.Results[0].Id=="a"&&F.Bots.Results[1].Id=="b"&&F.Bots.Results[0].Won&&!F.Bots.Results[1].Won,"bot winner and loser not recorded complementarily");
     Check(!F.Bots.Results[0].Persist&&!F.Bots.Results[1].Persist,"bot pair bypassed batched checkpoint");
     Check(F.Bots.SaveData.Rivals[0].NextActionUnix==1045&&F.Bots.SaveData.Rivals[1].NextActionUnix==1045,"both rivals did not receive minimum cooldown");
     Check(F.Bots.SaveData.Rivals[0].LastSimulatedUnix==1000&&F.Bots.SaveData.Rivals[1].LastSimulatedUnix==1000,"paired simulation timestamps differ");
     Check(!F.Run()&&DigimonVenomNXTAutoBattle::Calls==1,"same defender battled twice in same simulation batch");F.Unchanged();}
    {Fixture F;DigimonVenomNXTAutoBattle::AWins=false;Check(F.Run()&&!F.Bots.Results[0].Won&&F.Bots.Results[1].Won,"team B winner was reversed");}
    {Fixture F;DigimonVenomNXTAutoBattle::Draw=true;Check(F.Run()&&F.Bots.Results[0].Draw&&F.Bots.Results[1].Draw,"draw was not recorded for both bots");}
    {Fixture F;F.Bots.SaveData.Rivals[1].MapId=2;Check(!F.Run()&&DigimonVenomNXTAutoBattle::Calls==0,"rivals battled across habitats");}
    {Fixture F;F.Bots.SaveData.Rivals[1].RivalId="a";Check(!F.Run(),"bot battled itself");}
    {Fixture F;F.Bots.LiveBattleRivals.insert("a");Check(!F.Run(),"live engaged attacker entered bot simulation");}
    {Fixture F;F.Bots.LiveBattleRivals.insert("b");Check(!F.Run(),"live engaged defender entered bot simulation");}
    {Fixture F;F.Bots.SaveData.Rivals[1].NextActionUnix=1001;Check(!F.Run(),"future scheduled defender entered simulation");}
    {Fixture F;F.Bots.SaveData.Rivals[1].TrainingLevel=16;Check(!F.Run(),"unfair large level mismatch entered simulation");}
    {Fixture F;F.Bots.SaveData.Rivals[1].TrainingLevel=15;Check(F.Run(),"level tolerance boundary wrongly blocked");}
    {Fixture F;F.Bots.SaveData.Rivals[0].Partners.clear();Check(!F.Run(),"empty attacker entered simulation");}
    {Fixture F;F.Bots.SaveData.Rivals[1].Partners.clear();Check(!F.Run(),"empty defender entered simulation");}
    {Fixture F;F.Bots.Data=false;Check(!F.Run(),"missing combat data entered simulation");}
    {Fixture F;DigimonVenomNXTAutoBattle::Valid=false;Check(!F.Run()&&F.Bots.Results.empty(),"invalid combat result updated bot statistics");F.Unchanged();}
    {Fixture F;F.Bots.SaveData.Rivals.pop_back();Check(!F.Run(),"single bot population attempted battle");}
    std::cout<<"Actual same-map rival simulation: "<<Checks<<" eligibility, paired-result, snapshot and cooldown checks passed.\n";
    return 0;
}catch(const std::exception& Error){std::cerr<<Error.what()<<'\n';return 1;}}
'''


class UnrankedRivalsIntegrationTests(unittest.TestCase):
    def test_actual_local_pair_selection_and_isolated_combat_snapshots(self):
        source_text = SOURCE.read_text(encoding="utf-8")
        program = STUBS + method(source_text, "UDigimonVenomNXTAIRivalSubsystem::TrySimulateUnranked(") + CASES
        authority = method(source_text, "UDigimonVenomNXTAIRivalSubsystem::ForceSimulationStep(")
        self.assertIn("!HasServerAuthority()", authority)
        self.assertIn("!LiveBattleRivals.Contains(Rival.RivalId)", authority)
        with tempfile.TemporaryDirectory(prefix="digimon-unranked-rivals-") as directory:
            source = Path(directory) / "rivals.cpp"
            binary = Path(directory) / "rivals"
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
