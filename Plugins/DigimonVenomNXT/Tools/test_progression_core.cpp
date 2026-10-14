// Executes the production cumulative adapter against reference Venom v1.5 XP values.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTProgressionCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTStarterCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRivalRules.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
namespace {
using namespace DigimonVenomNXTProgressionCore;
int Checks=0;
void Require(bool V, const char* M) { ++Checks; if (!V) { std::cerr << "FAIL: " << M << '\n'; std::exit(1); } }
struct Partner { int Level=5, CurrentHP=35, CurrentSP=7, ABI=19, CAM=24; std::int64_t Experience=332; std::string Id="owned-guid", Species="agumon"; };
struct Stats { int MaxHP, MaxSP; };
Stats StatsFor(const Partner& P) { return {100+P.Level*4,40+P.Level}; }
void TestReferenceCurve() {
    const int Levels[]={1,2,3,4,5,6,10,20,50,99,100,200};
    const std::int64_t Spans[]={47,67,94,124,158,196,373,959,3523,9429,9566,26077};
    const std::int64_t Floors[]={0,47,114,208,332,490,1526,7742,71156,378290,387719,2119741};
    for (int I=0;I<12;++I) { Require(ExperienceToNextLevel(Levels[I])==Spans[I],"reference per-level XP"); Require(ExperienceFloor(Levels[I])==Floors[I],"reference cumulative XP floor"); }
    for (int L=1;L<200;++L) {
        const auto Start=GetProgress(L,ExperienceFloor(L),200);
        const auto End=GetProgress(L,NextLevelXP(L)-1,200);
        const auto Next=GetProgress(L,NextLevelXP(L),200);
        Require(Start.Level==L && Start.IntoLevel==0 && Start.LevelSpan==ExperienceToNextLevel(L),"each band begins empty");
        Require(End.Level==L && End.Remaining==1 && End.Fraction<1.0,"last XP remains below level boundary");
        Require(Next.Level==L+1 && (Next.AtCap || Next.IntoLevel==0),"inclusive threshold crosses one level");
    }
    const auto P=GetProgress(5,400,99);
    Require(P.Level==5 && P.IntoLevel==68 && P.LevelSpan==158 && P.Remaining==90,"UI uses within-level reference progress");
}
void TestAwardsAndRecovery() {
    Partner Human,Rival,Batched;
    Apply(Human,140,99,StatsFor); Apply(Rival,140,99,StatsFor);
    Require(Human.Level==5 && Human.Experience==472,"one award accumulates below source level-six floor");
    Apply(Human,140,99,StatsFor); Apply(Rival,140,99,StatsFor); Apply(Batched,280,99,StatsFor);
    Require(Human.Level==6 && Human.Experience==612 && Human.CurrentHP==39 && Human.CurrentSP==8,"only new HP/SP maxima are recovered on level up");
    Require(Rival.Level==Human.Level && Rival.Experience==Human.Experience && Batched.Level==Human.Level && Batched.Experience==Human.Experience,"humans rivals and batched rewards share source pacing");
    Require(Human.Id=="owned-guid" && Human.Species=="agumon" && Human.ABI==19 && Human.CAM==24,"growth retains identity and permanent progression");
    Partner Defeated; Defeated.CurrentHP=0; Apply(Defeated,5000,99,StatsFor);
    Require(Defeated.Level>5 && Defeated.CurrentHP==0,"XP never revives a defeated partner");
    const int HP=Human.CurrentHP,SP=Human.CurrentSP;
    const auto Again=Apply(Human,0,99,StatsFor);
    Require(!Again.Changed && Human.CurrentHP==HP && Human.CurrentSP==SP,"repeated refresh never heals");
    Partner Granted; Granted.Experience=0; Apply(Granted,0,99,StatsFor);
    Require(Granted.Level==5 && Granted.Experience==332 && Granted.CurrentHP==35,"granted levels reconcile their floor without healing");
    Partner Reset; Reset.Level=1; Reset.Experience=0; Apply(Reset,0,99,StatsFor);
    Require(Reset.Level==1 && Reset.Experience==0,"evolution reset never restores prior XP");
    Partner Stale; Stale.Experience=1526; Apply(Stale,0,99,StatsFor);
    Require(Stale.Level==10 && Stale.Experience==1526,"saved XP crosses all earned levels");
}
void TestCaps() {
    Partner P; const auto Award=Apply(P,2000,6,StatsFor);
    Require(P.Level==6 && P.Experience==490 && Award.GrantedExperience==158,"cap discards within-level excess as source does");
    P.CurrentHP=1; P.CurrentSP=0; const auto Capped=Apply(P,2000,6,StatsFor);
    Require(!Capped.Changed && Capped.GrantedExperience==0 && P.CurrentHP==1,"capped awards never accrue or heal");
    Apply(P,0,99,StatsFor); Require(P.Level==6 && P.Experience==490,"raising the cap cannot cash in discarded XP");
    Apply(P,std::numeric_limits<std::int64_t>::max(),200,StatsFor);
    Require(P.Level==200 && P.Experience==2119741,"large awards saturate safely at supported cap");
    Require(AddSaturated(std::numeric_limits<std::int64_t>::max()-1,5)==std::numeric_limits<std::int64_t>::max(),"accumulation cannot overflow");
    Require(GetProgress(0,-100,-1).Level==1 && GetProgress(500,0,500).Level==200,"malformed bounds normalize");
    Require(DigimonVenomNXTStarterCore::ExperienceFloor(5)==332 && DigimonVenomNXTRivalRules::NextLevelXP(5)==490,"starter and rivals use common source curve");
}
}
int main() { TestReferenceCurve(); TestAwardsAndRecovery(); TestCaps(); std::cout << "Progression core: " << Checks << " checks passed.\n"; }
