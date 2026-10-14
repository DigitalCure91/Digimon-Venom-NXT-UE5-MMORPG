#!/usr/bin/env python3
"""Compile the actual runtime damage adapters against lightweight UE value stubs.

This catches a runtime adapter bypassing the tested core or dropping INT, elements,
Guard, or PvE context. It is deliberately not a substitute for an Unreal build.
"""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"


def definition(source, signature):
    start = source.index(signature)
    brace = source.index("{", start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == "{") - (source[end] == "}")
        end += 1
    return source[start:end]


class RuntimeDamageAdapterTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which("g++"), "g++ required for portable adapter check")
    def test_actual_runtime_adapter(self):
        battle = (PRIVATE / "DigimonVenomNXTBattleActor.cpp").read_text()
        auto = (PRIVATE / "DigimonVenomNXTAutoBattle.cpp").read_text()
        definitions = "\n".join([
            definition(auto, "DigimonVenomNXTCombatCore::Move DigimonVenomNXTAutoBattle::ToCoreMove("),
            definition(auto, "DigimonVenomNXTCombatCore::Unit DigimonVenomNXTAutoBattle::ToCoreUnit("),
            definition(battle, "int32 ADigimonVenomNXTBattleActor::LivingActiveCount("),
            definition(battle, "int32 ADigimonVenomNXTBattleActor::ComputeDamage_Implementation("),
            definition(battle, "int32 ADigimonVenomNXTBattleActor::ComputeMoveDamage_Implementation("),
        ])
        source = r'''
#include "DigimonVenomNXTCombatCore.h"
#include "DigimonVenomNXTBattlePolicyCore.h"
#include <cassert>
#include <iostream>
using int32 = int;
enum class EDigimonDamageClass { Physical, Special };
enum class EDigimonAffinity { Free, Vaccine, Virus, Data };
enum class EDigimonElement { Neutral, Fire, Water, Plant, Electric, Wind, Earth, Light, Dark };
enum class EDigimonBattleKind { Wild, AITamer, Season, Ranked, Story, Friendly };
struct FDigimonStats { int MaxHP=1500,MaxSP=120,Attack=200,Defense=175,Spirit=200,Speed=100; };
struct FDigimonMoveSlot { int Power=100,SPCost=0; EDigimonDamageClass DamageClass=EDigimonDamageClass::Physical; EDigimonElement Element=EDigimonElement::Neutral; };
struct FDigimonBattleUnit {
    int InstanceId=1,HP=1500,SP=120,Level=50,CAM=0;
    FDigimonStats Stats; std::vector<FDigimonMoveSlot> Moves; bool bDefeated=false,bGuarding=false;
    EDigimonAffinity Affinity=EDigimonAffinity::Free; EDigimonElement Element=EDigimonElement::Neutral;
};
template<typename T> struct Array:std::vector<T> {
    template<typename P> bool ContainsByPredicate(P predicate)const { for(const auto& value:*this)if(predicate(value))return true;return false; }
};
struct FDigimonBattleTeam { Array<FDigimonBattleUnit> Active,Bench; };
struct FDigimonBattleState { FDigimonBattleTeam TeamA,TeamB; EDigimonBattleKind Kind=EDigimonBattleKind::Wild; };
struct FMath { static int Max(int a,int b){return std::max(a,b);} static float FRand(){return 0.0f;} static float FRandRange(float,float){return 1.0f;} };
namespace DigimonVenomNXTAutoBattle {
DigimonVenomNXTCombatCore::Move ToCoreMove(const FDigimonMoveSlot&);
DigimonVenomNXTCombatCore::Unit ToCoreUnit(const FDigimonBattleUnit&);
}
struct ADigimonVenomNXTBattleActor {
    FDigimonBattleState State; void* PlayerB=nullptr; mutable float LastDamageCombo=1.0f;
    int32 LivingActiveCount(const FDigimonBattleTeam&)const;
    int32 ComputeDamage_Implementation(const FDigimonBattleUnit&,const FDigimonBattleUnit&,int32)const;
    int32 ComputeMoveDamage_Implementation(const FDigimonBattleUnit&,const FDigimonBattleUnit&,const FDigimonMoveSlot&)const;
    int32 ComputeMoveDamage(const FDigimonBattleUnit&a,const FDigimonBattleUnit&b,const FDigimonMoveSlot&m)const{return ComputeMoveDamage_Implementation(a,b,m);}
};
'''
        source += definitions
        source += r'''
int main(){
    ADigimonVenomNXTBattleActor battle;
    FDigimonBattleUnit a,b; b.InstanceId=2;
    battle.State.TeamA.Active.push_back(a); battle.State.TeamB.Active.push_back(b);
    FDigimonMoveSlot basic,special;
    special.Power=155; special.DamageClass=EDigimonDamageClass::Special; special.Element=EDigimonElement::Fire;
    auto expect=[&](const FDigimonBattleUnit&x,const FDigimonBattleUnit&y,const FDigimonMoveSlot&m,double multiplier){
        auto cx=DigimonVenomNXTAutoBattle::ToCoreUnit(x),cy=DigimonVenomNXTAutoBattle::ToCoreUnit(y);
        cx.DamageMultiplier=multiplier;
        return DigimonVenomNXTCombatCore::CalculateDamage(cx,cy,DigimonVenomNXTAutoBattle::ToCoreMove(m),1.0f);
    };
    assert(battle.ComputeMoveDamage_Implementation(a,b,basic)==expect(a,b,basic,1.0));
    assert(battle.ComputeMoveDamage_Implementation(a,b,basic)<b.HP/3);
    assert(battle.ComputeMoveDamage_Implementation(b,a,basic)==expect(b,a,basic,.72));
    for(auto kind:{EDigimonBattleKind::AITamer,EDigimonBattleKind::Season,EDigimonBattleKind::Story}){
        battle.State.Kind=kind;assert(battle.ComputeMoveDamage_Implementation(b,a,special)==expect(b,a,special,.72));
    }
    for(auto kind:{EDigimonBattleKind::Ranked,EDigimonBattleKind::Friendly}){
        battle.State.Kind=kind;assert(battle.ComputeMoveDamage_Implementation(b,a,special)==expect(b,a,special,1.0));
    }
    a.Affinity=EDigimonAffinity::Vaccine;b.Affinity=EDigimonAffinity::Virus;b.Element=EDigimonElement::Plant;
    a.Stats.Attack=20;a.Stats.Spirit=200;b.Stats.Defense=200;b.Stats.Spirit=20;
    assert(battle.ComputeMoveDamage_Implementation(a,b,basic)==1);
    assert(battle.ComputeMoveDamage_Implementation(a,b,special)==expect(a,b,special,1.0));
    b.bGuarding=true;
    assert(battle.ComputeMoveDamage_Implementation(a,b,special)==expect(a,b,special,1.0));
    assert(battle.ComputeDamage_Implementation(a,b,100)==expect(a,b,basic,1.0));
    a.CAM=100; battle.State.TeamA.Active.push_back(a);
    auto ca=DigimonVenomNXTAutoBattle::ToCoreUnit(a),cb=DigimonVenomNXTAutoBattle::ToCoreUnit(b);
    assert(battle.ComputeMoveDamage_Implementation(a,b,special)==DigimonVenomNXTCombatCore::CalculateDamage(ca,cb,DigimonVenomNXTAutoBattle::ToCoreMove(special),1.0f,1.25f));
    assert(battle.LastDamageCombo==1.25f);
    b.CAM=100; a.bGuarding=false; battle.State.TeamB.Active.push_back(b); battle.State.Kind=EDigimonBattleKind::Season;
    assert(battle.ComputeMoveDamage_Implementation(b,a,special)==expect(b,a,special,.72));
    assert(battle.LastDamageCombo==1.0f);
    battle.State.Kind=EDigimonBattleKind::Ranked;
    auto rankedB=DigimonVenomNXTAutoBattle::ToCoreUnit(b),rankedA=DigimonVenomNXTAutoBattle::ToCoreUnit(a);
    assert(battle.ComputeMoveDamage_Implementation(b,a,special)==DigimonVenomNXTCombatCore::CalculateDamage(rankedB,rankedA,DigimonVenomNXTAutoBattle::ToCoreMove(special),1.0f,1.25f));
    std::cout<<"Actual runtime adapter: physical/INT, affinities, Guard, CAM, PvE and mode parity passed\n";
}
'''
        with tempfile.TemporaryDirectory() as temp:
            cpp, executable = Path(temp) / "adapter.cpp", Path(temp) / "adapter"
            cpp.write_text(source)
            compile_result = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", "-I", str(PUBLIC), str(cpp), "-o", str(executable)], text=True, capture_output=True)
            self.assertEqual(compile_result.returncode, 0, compile_result.stdout + compile_result.stderr)
            run = subprocess.run([str(executable)], text=True, capture_output=True)
            self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
            print(run.stdout.strip())


if __name__ == "__main__":
    unittest.main()
