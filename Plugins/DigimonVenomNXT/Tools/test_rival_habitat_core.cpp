// Compile the production habitat rules without Unreal. The game uses the same
// helpers for initial bot placement and subsequent exploration/retreats.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRivalRules.h"
#include <cstdlib>
#include <iostream>
#include <limits>

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
}

int main()
{
    using namespace DigimonVenomNXTRivalRules;
    // Actual starter registry ranges. A map's low end alone cannot make it safe.
    Require(IsSuitableMap(1, 4, 5), "level-five starter can train in habitat one");
    Require(IsSuitableMap(1, 5, 5), "level-five starter can train in habitats two and three");
    Require(!IsSuitableMap(1, 6, 5), "habitat four is unsafe despite its level-one floor");
    Require(!IsSuitableMap(5, 10, 5), "habitat ten cannot match a level-five starter by its minimum");
    Require(!IsSuitableMap(7, 12, 5), "random exploration cannot send a level-five starter to habitat thirteen");
    Require(MapDistance(1, 5, 5) < MapDistance(1, 4, 5), "initial placement prefers the challenging safe ceiling");
    Require(MapDistance(1, 4, 5) < MapDistance(5, 10, 5), "safe habitat wins over a matching unsafe floor");

    // The initial/de-evolved level-one partner has no fully safe map in this
    // registry. Fallback chooses the lowest ceiling, not an arbitrary equal floor.
    Require(!IsSuitableMap(1, 4, 1) && !IsSuitableMap(1, 5, 1), "level-one partners have no invented safe destination");
    Require(MapDistance(1, 4, 1) < MapDistance(1, 5, 1), "lowest unsafe ceiling is the safest available fallback");
    Require(MapDistance(1, 5, 1) < MapDistance(5, 10, 1), "fallback does not favor harder low-floor habitats");

    Require(IsSuitableMap(90, 94, 100), "six-level training band includes its lower boundary");
    Require(!IsSuitableMap(90, 93, 100), "random travel excludes stale training habitats");
    Require(IsSuitableMap(95, 100, 100), "progressed rivals can explore their current level ceiling");
    Require(!IsSuitableMap(95, 101, 100), "progressed rivals still respect the safe ceiling");
    Require(MapDistance(1, 4, 100) < MapDistance(95, 101, 100), "a distant safe fallback outranks a nearby unsafe map");

    // Retreating lowers the target: no suitable alternative can force departure
    // from the current lowest habitat. Root integration retains that fallback.
    Require(IsSuitableMap(1, 4, 4) && !IsSuitableMap(1, 5, 4), "only the current lowest habitat remains suitable at target four");
    Require(MapDistance(1, 4, 4) < MapDistance(1, 5, 4), "current safe habitat remains the fallback when alternatives are unsafe");
    Require(!IsSuitableMap(5, 10, 7) && IsSuitableMap(2, 7, 7), "lower retreat target rejects the former hard habitat");
    Require(IsSuitableMap(5, 10, 10), "earned progression eventually unlocks the harder habitat");

    Require(MapEncounterCeiling(10, 2) == 10, "inverted level range keeps its true highest level");
    Require(!IsSuitableMap(10, 2, 5), "inverted range cannot disguise an unsafe habitat");
    Require(MapEncounterCeiling(-10, -3) == 1 && IsSuitableMap(-10, -3, -1), "nonpositive legacy levels normalize safely");
    const int High = std::numeric_limits<int>::max();
    const int Low = std::numeric_limits<int>::min();
    Require(MapDistance(Low, High, 1) > MapDistance(1, 1, High), "unsafe penalty outranks every safe distance without overflow");
    Require(MapDistance(Low, High, 1) > 0 && !IsSuitableMap(Low, High, 1), "extreme registry values remain ordered and unsafe");
    Require(MapDistance(High, High, High) == 0 && IsSuitableMap(High, High, High), "extreme equal levels remain valid");

    std::cout << "Rival habitat core: " << Checks << " checks passed.\n";
    return 0;
}
