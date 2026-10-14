#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRelayCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTProgressionCore.h"
#include <cassert>
#include <iostream>
#include <limits>
struct Progress
{
    bool bEverChampion=false, bIsChampion=false, bShinyScanMastery=false, bParadoxScanMastery=false, bFirewallScanMastery=false;
    int ChampionshipWins=0, Defenses=0, TitleLosses=0, ChallengerIndex=0;
};
int main()
{
    using namespace DigimonVenomNXTRelayCore;
    Progress P;
    assert(!ReconcileMastery(P));
    TitleResult(P,false,true);
    assert(!P.bEverChampion && !P.bIsChampion && !P.bFirewallScanMastery && P.ChampionshipWins==0);
    TitleResult(P,true,true);
    assert(P.bEverChampion && P.bIsChampion && P.bFirewallScanMastery && P.ChampionshipWins==1 && P.Defenses==0 && P.ChallengerIndex==2);
    for(int I=0;I<18;++I) TitleResult(P,true,false);
    assert(P.Defenses==18 && P.ChallengerIndex==20 && P.ChampionshipWins==1);
    TitleResult(P,false,false);
    assert(!P.bIsChampion && P.bEverChampion && P.bFirewallScanMastery && P.TitleLosses==1 && P.ChallengerIndex==21);
    TitleResult(P,false,false);
    assert(P.TitleLosses==1 && P.ChallengerIndex==22); // same holder, no duplicate title loss
    TitleResult(P,true,false);
    assert(P.bIsChampion && P.ChampionshipWins==2 && P.Defenses==18 && P.ChallengerIndex==23);
    for(int Signal=0;Signal<3;++Signal)
    {
        Progress Old;
        if(Signal==0) Old.bEverChampion=true;
        if(Signal==1) Old.bIsChampion=true;
        if(Signal==2) Old.ChampionshipWins=1;
        assert(ReconcileMastery(Old) && Old.bEverChampion && Old.bFirewallScanMastery);
        assert(!ReconcileMastery(Old));
    }
    Progress Legacy;
    Legacy.bEverChampion = true; Legacy.bParadoxScanMastery = true;
    assert(ReconcileMastery(Legacy) && Legacy.bFirewallScanMastery && Legacy.bParadoxScanMastery && !Legacy.bShinyScanMastery);
    Progress Unproven; Unproven.bParadoxScanMastery=true;
    assert(!ReconcileMastery(Unproven) && !Unproven.bFirewallScanMastery && Unproven.bParadoxScanMastery);
    P.ChallengerIndex=P.Defenses=std::numeric_limits<int>::max();
    TitleResult(P,true,false);
    assert(P.ChallengerIndex==std::numeric_limits<int>::max() && P.Defenses==std::numeric_limits<int>::max());
    // First-clear training is XP earned by the persistent party, not a battle stat replacement.
    for(int Existing : {1,5,20,90,100})
    {
        const auto XP=DigimonVenomNXTProgressionCore::ExperienceFloor(Existing);
        const auto Milestone=DigimonVenomNXTProgressionCore::ExperienceFloor(35);
        const auto Award=DigimonVenomNXTProgressionCore::CalculateAward(Existing,XP,std::max<std::int64_t>(500,std::max<std::int64_t>(0,Milestone-XP)),100);
        assert(Award.Level>=Existing);
        if(Existing<35) assert(Award.Level>=35);
    }
    std::cout << "PASS Relay championship, defeat/reclaim, proven-title backfill, independent Firewall mastery, saturation and real-party XP milestone invariants\n";
}
