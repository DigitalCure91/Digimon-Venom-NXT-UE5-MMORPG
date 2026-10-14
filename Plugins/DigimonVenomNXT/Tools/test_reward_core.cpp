#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRewardCore.h"
#include <cassert>
#include <iostream>
#include <limits>
int main()
{
    namespace R = DigimonVenomNXTRewardCore;
    int Checks=0;
    // Golden source formulas: wild active/reserve differs from the full-party story award.
    for(int L=1;L<=100;++L) for(int Rank=0;Rank<=6;++Rank)
    {
        assert(R::WildXP(L,Rank)==24+12*L+8*Rank);++Checks;
        assert(R::WildCredits(L)==25+7*L);++Checks;
        assert(R::StoryXP(L)==24+16*L);++Checks;
    }
    assert(R::WildXP(5,2)==100 && R::StoryXP(5)==104);++Checks;
    assert(R::FieldCredits(0)==40 && R::FieldCredits(30)==2140);++Checks;
    assert(R::RematchCredits(0)==25 && R::RematchCredits(850)==170);++Checks;
    assert(R::CreditTotal(R::MaxCredits-2,3)==R::MaxCredits);++Checks;
    assert(R::CreditTotal(-20,30)==30);++Checks;
    assert(R::InventoryTotal(998,10)==999 && R::InventoryTotal(999,1)==999);++Checks;
    assert(R::FriendshipMeatDrop(0.179999,998) && !R::FriendshipMeatDrop(0.18,998) && !R::FriendshipMeatDrop(0.0,999));++Checks;
    assert(R::Scale(100,1.5)==150 && R::Scale(100,0)==0 && R::Scale(100,std::numeric_limits<double>::infinity())==0);++Checks;
    assert(R::MasteryHundredths(5)==100 && R::MasteryHundredths(1)==20);++Checks;
    int Scan=0;
    for(int Battle=0;Battle<5;++Battle) Scan=R::ScanHundredthsAfter(Scan/100,Scan%100,120,200);
    assert(Scan==600);++Checks; // Five custom one-percent scans plus 20% mastery = six percent exactly.
    assert(R::ScanHundredthsAfter(199,90,100,200)==20000);++Checks;
    assert(R::ScanHundredthsAfter(200,99,100,200)==20000);++Checks;
    std::cout << "PASS source reward core: " << Checks << " checks\n";
}
