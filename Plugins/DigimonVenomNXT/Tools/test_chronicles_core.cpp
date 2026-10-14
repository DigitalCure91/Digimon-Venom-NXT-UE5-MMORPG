#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTChroniclesCore.h"
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
int main()
{
    using namespace DigimonVenomNXTChroniclesCore;
    std::array<bool, 19> Crests{}, Bosses{};
    const auto Has = [&](int Map) { return Crests[Map]; };
    const auto Cleared = [&](int Map) { return Bosses[Map]; };
    assert(CanEnter(1,Has) && CanEnter(2,Has));
    assert(!CanEnter(0,Has) && !CanEnter(19,Has));
    for (int Map=2;Map<=18;++Map)
    {
        assert(CanEnter(Map,Has));
        if (Map<18) assert(!CanEnter(Map+1,Has));
        assert(!CanSummon(Cleared,Has));
        Crests[Map]=true;
        assert(!CanSummon(Cleared,Has));
        Bosses[Map]=true;
    }
    assert(CanSummon(Cleared,Has));
    for (int Map=2;Map<=18;++Map)
    {
        Crests[Map]=false; assert(!CanSummon(Cleared,Has)); Crests[Map]=true;
        Bosses[Map]=false; assert(!CanSummon(Cleared,Has)); Bosses[Map]=true;
    }
    Crests[2]=false; assert(!CanEnter(18,Has)); // cardinality cannot substitute for exact prefix
    assert(!CanTurnIn(false,1,1) && !CanTurnIn(true,0,1) && CanTurnIn(true,1,1));
    assert(!CanTurnIn(true,10,0));
    for (int Variant=0;Variant<3;++Variant)
        for (int Relay=0;Relay<2;++Relay)
            for (int Chronicles=0;Chronicles<2;++Chronicles)
                for (int Wild=0;Wild<2;++Wild)
                {
                    const bool Matching = Wild && ((Variant==1 && Relay) || (Variant==2 && Chronicles));
                    assert(ScanGain(5,Variant==1,Variant==2,Relay,Chronicles,Wild)==(Matching?6:5));
                }
    assert(ScanGain(-1,false,false,false,false,true)==0);
    assert(ScanGain(25,true,false,true,true,true)==30);
    assert(ScanGain(std::numeric_limits<int>::max(),false,false,true,true,true)==std::numeric_limits<int>::max());
    std::cout << "PASS Chronicles ordered routes, all17 unique crest+guardian gate, explicit quest turn-in, isolated20 percent mastery rules\n";
}
