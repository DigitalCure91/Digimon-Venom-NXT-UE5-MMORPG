#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTBattlePolicyCore.h"
#include <cassert>
#include <iostream>
int main()
{
    using namespace DigimonVenomNXTBattlePolicyCore;
    int Checks = 0;
    for (int Kind = -2; Kind < 10; ++Kind)
        for (int Team = -1; Team < 3; ++Team)
            for (bool Done : {false, true})
                for (bool Auto : {false, true})
                    for (bool OtherPlayer : {false, true})
                    {
                        assert(MayFlee(Kind, Team, Done, Auto, OtherPlayer) ==
                            (Kind == 0 && Team == 0 && !Done && !Auto && !OtherPlayer));
                        ++Checks;
                    }
    for (int Kind = 0; Kind <= 5; ++Kind)
    {
        assert(UsesSourcePlayerFormation(Kind, false) == (Kind == 0 || Kind == 2 || Kind == 4)); ++Checks;
        assert(!UsesSourcePlayerFormation(Kind, true)); ++Checks;
        assert(EnemyDamageMultiplier(Kind, 0, false) == 1.0); ++Checks;
        assert(EnemyDamageMultiplier(Kind, 1, true) == 1.0); ++Checks;
        assert(EnemyDamageMultiplier(Kind, 1, false) == (Kind == 3 || Kind == 5 ? 1.0 : 0.72)); ++Checks;
    }
    assert(WildMaxHP(1000) == 720); ++Checks;
    assert(WildMaxHP(1) == 20); ++Checks;
    assert(WildMaxHP(0) == 20); ++Checks;
    assert(TrainerVictoryCredits(6, 6) == 160); ++Checks;
    assert(TrainerVictoryCredits(7, 6) == 170); ++Checks;
    assert(TrainerVictoryCredits(60, 6) == 250); ++Checks;
    assert(TrainerVictoryCredits(120, 6) == 350); ++Checks;
    assert(TrainerVictoryCredits(2147483647, 1) == 350); ++Checks;
    assert(TrainerVictoryCredits(0, 0) == 160); ++Checks;
    std::cout << "Battle policy: " << Checks << " checks passed\n";
}
