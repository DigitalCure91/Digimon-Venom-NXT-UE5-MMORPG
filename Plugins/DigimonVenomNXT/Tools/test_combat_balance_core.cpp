// Production stat, matchup, migration and tactical-AI rules; no duplicate formula implementation.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatCore.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
using namespace DigimonVenomNXTCombatCore;
namespace {
int Checks=0;
void Check(bool OK,const char* Why) { ++Checks; if(!OK) {std::cerr<<"FAIL: "<<Why<<'\n';std::exit(1);} }
Unit Creature(int Rank,int Level)
{
    Unit U; const int Bases[]={190,40,36,32,36,34};
    U.MaxHP=U.HP=Stat(Bases[0],Level,Rank,0,0,0); U.MaxSP=U.SP=Stat(Bases[1],Level,Rank,0,0,1);
    U.Attack=Stat(Bases[2],Level,Rank,0,0,2); U.Defense=Stat(Bases[3],Level,Rank,0,0,3);
    U.Spirit=Stat(Bases[4],Level,Rank,0,0,4); U.Speed=Stat(Bases[5],Level,Rank,0,0,5); U.Level=Level;
    return U;
}
}
int main()
{
    for(int A=0;A<4;++A) for(int D=0;D<4;++D)
    {
        const float Expected=A==0||D==0||A==D?1.0f:(D==A%3+1?2.0f:.5f);
        Check(TypeMultiplier(A,D)==Expected,"all sixteen affinity pairings obey the Warden / Ravager / Cipher triangle");
    }
    const int Advantage[][2]={{1,3},{3,2},{2,1},{4,5},{5,6},{6,4},{7,8},{8,7}};
    for(int A=0;A<9;++A) for(int D=0;D<9;++D)
    {
        bool Good=false;for(const auto& P:Advantage) if(P[0]==A&&P[1]==D)Good=true;
        Check(ElementMultiplier(A,D)==(Good?1.5f:1.0f),"all eighty-one element pairings match the reference including neutral reverse matchups");
    }
    Check(Effectiveness(1,2,1,3)==3.0f,"affinity and element advantages combine to threefold damage");
    Check(Effectiveness(2,1,1,3)==.75f,"element advantage does not erase type disadvantage");
    Check(TypeMultiplier(-1,2)==1 && TypeMultiplier(100,3)==1,"invalid affinities cannot grant a multiplier");
    Unit A=Creature(2,50),D=Creature(2,50); Move Strike{145,6,0,0},Pulse{155,7,1,0};
    const int Basic=CalculateDamage(A,D,Move{},1);
    Check(Basic==109,"reference physical arithmetic uses power as a percentage and floors once");
    Check(D.MaxHP/Basic>=10,"neutral level-fifty peers survive several deliberate turns");
    Check(CalculateDamage(A,D,Strike,1)==158,"physical power strike uses reference percent power");
    Check(Damage(1,A.Attack,D.Defense,100,1)==Damage(200,A.Attack,D.Defense,100,1),"attacker level is not multiplied a second time in damage");
    Unit Mage=A; Mage.Spirit=500; Mage.Attack=1;
    Check(CalculateDamage(Mage,D,Pulse,1)>CalculateDamage(Mage,D,Strike,1),"special techniques use INT offense instead of physical attack");
    Unit Ward=D; Ward.Spirit=1000;
    Check(CalculateDamage(Mage,Ward,Pulse,1)<CalculateDamage(Mage,D,Pulse,1),"INT also defends against special attacks");
    Check(CalculateDamage(A,Ward,Strike,1)==CalculateDamage(A,D,Strike,1),"INT does not replace physical defense");
    D.Guarding=true;
    Check(CalculateDamage(A,D,Strike,1)==79,"Guard halves the integer base hit like the reference");
    D.Guarding=false; A.DamageMultiplier=.72;
    Check(CalculateDamage(A,D,Strike,1)==113,"PvE enemy handicap is applied inside the shared arithmetic");
    A.DamageMultiplier=1;
    Check(ComboMultiplier(19,true,0)==1 && ComboMultiplier(100,false,0)==1,"combos require CAM twenty and a living active ally");
    Check(ComboMultiplier(100,true,.1999f)==1.25f && ComboMultiplier(100,true,.2f)==1,"CAM combo threshold matches CAM / 500 exactly");
    Check(CalculateDamage(A,D,Strike,1,1.25f)==197,"CAM bonus multiplies the already-floored hit like the reference");
    Check(CalculateDamage(A,D,Strike,std::numeric_limits<float>::quiet_NaN())>=1,"invalid variance cannot overflow damage");
    const Unit Low=Creature(2,5),High=Creature(2,50);
    Unit LowAdv=Low,HighWeak=High;LowAdv.Affinity=1;HighWeak.Affinity=2;HighWeak.Element=3;
    Move BestLow{155,7,1,1};
    Check(CalculateDamage(LowAdv,HighWeak,BestLow,1.08f)==1,"large level gaps withstand even an advantageous low-level special");
    Check(CalculateDamage(High,Low,Strike,1)>CalculateDamage(Low,High,Strike,1),"leveled stats make stronger partners hit meaningfully harder");
    for(int R=0;R<=5;++R) for(int L:{1,5,20,50,100,200}) for(int S=0;S<6;++S)
    {
        const int Untrained=Stat(30,L,R,100,0,S);
        Check(Stat(30,L,R,100,25,S)==Untrained+25,"permanent training is added after ABI and growth, never amplified");
        Check(Stat(30,L,R,999,0,S)==Stat(30,L,R,200,0,S),"ABI stat scaling is capped at two hundred");
    }
    Check(Stat(100,2,2,0,0,0)==122 && Stat(40,2,2,0,0,1)==42,"HP and SP have distinct linear growth");
    Check(Stat(20,2,2,0,0,2)==23 && Stat(20,2,2,0,0,3)==23,"fractional growth floors like the reference");
    for(int Max:{1,10,100,1000})for(int NewMax:{1,25,200,3000})for(int V:{-5,0,1,Max/2,Max,Max+200})
    {
        const int M=MigrateVital(V,Max,NewMax,true);
        Check(M>=0&&M<=NewMax,"migrated health remains bounded");
        Check((V<=0&&M==0)||(V>0&&M>=1),"migration preserves fainted state and keeps a living partner alive");
    }
    Check(MigrateVital(230,692,2941,true)==978,"vitality migration rounds exact halves without floating point loss");
    Check(MigrateVital(50,100,1000,true)==500,"legacy half-health becomes half of the new maximum");
    Check(MigrateVital(0,40,100,false)==0,"empty SP stays empty on migration");
    Check(MigrateVital(std::numeric_limits<int>::max(),100,1000,true)==1000,"full-heal construction sentinels become full health");
    Check(LegacyBase(2,0)==100&&LegacyBase(5,0)==275&&LegacyBase(8,0)==100,"legacy denominators use original stage tables, never new authored stats");
    Check(ScaledStat(LegacyBase(2,0)+20,11)==162,"legacy training belonged inside the old scale when determining old max HP");
    A.Moves={Strike,Pulse};A.SP=100;A.Spirit=500;A.Attack=20;
    Check(ChooseMove(A,D)==1,"AI considers INT versus INT rather than comparing skill power alone");
    D.HP=1;Check(ChooseMove(A,D)==-1,"AI conserves SP when regular Attack already finishes the target");
    D.HP=D.MaxHP;A.SP=0;Check(ChooseMove(A,D)==-1,"zero-SP units always retain a free regular Attack");
    A.SP=100;A.Spirit=10;A.Attack=500;Check(ChooseMove(A,D)==0,"physical specialists favor their stronger actual damage channel");
    A.Moves={{100,0,0,0},{145,-1,0,0},{155,1000,1,0}};Check(ChooseMove(A,D)==-1,"invalid or unaffordable skills cannot bypass SP rules");
    Unit Tactician=Creature(2,50); Tactician.Affinity=1; Tactician.Element=1;
    Tactician.Moves={{145,6,0,1},{155,7,1,0}};
    Unit Resist=Creature(2,50),Weak=Resist;
    Resist.Affinity=3; Weak.Affinity=2; Weak.Element=3;
    const Decision AdvantagePick=ChooseAction(Tactician,{Resist,Weak},{0,1});
    Check(AdvantagePick.Target==1,"AI target choice values the actual affinity and element matchup");
    Resist.HP=1;
    const Decision FinishPick=ChooseAction(Tactician,{Resist,Weak},{0,1});
    Check(FinishPick.Target==0&&FinishPick.MoveIndex==-1,"securing a knockout takes priority and conserves SP");
    Check(ChooseAction(Tactician,{Weak,Weak},{0,1}).Target==0,"equal tactical scores retain stable target order");
    Check(ChooseAction(Tactician,{Weak},{-1,5}).Target==-1,"invalid target indices are ignored safely");
    Unit Fast=Creature(2,50),Slow=Fast;Fast.Speed=100;Slow.Speed=50;
    Fast.HP=Fast.MaxHP=Slow.HP=Slow.MaxHP=1000000;
    const Result Pace=Resolve({Fast},{Slow},1,3,30,true);
    int FastCount=0,SlowCount=0;
    double Clock=-1;
    for(const Event& E:Pace.Events)
    {
        if(E.Team==0)++FastCount;else++SlowCount;
        Check(E.Clock>=Clock,"automatic replay records monotonically advancing CTB time");Clock=E.Clock;
    }
    Check(FastCount==40&&SlowCount==20,"double-speed combatant earns two action opportunities per opponent action");
    Unit Finisher=Creature(5,100),LastHP=Creature(0,1);LastHP.HP=1;
    Finisher.Speed=1000;LastHP.Speed=1;
    const Result FinalHit=Resolve({Finisher},{LastHP},1,8,20,true);
    Check(FinalHit.Events.size()==1&&FinalHit.Events[0].Damage==1&&FinalHit.Events[0].TargetHPAfter==0,"replay reports actual damage removed rather than overkill");
    std::cout<<"PASS: "<<Checks<<" production combat balance, matchup, migration, ABI, training and AI checks.\n";
}
