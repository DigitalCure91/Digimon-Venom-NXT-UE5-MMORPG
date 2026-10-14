#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTTamerCore.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

namespace
{
int TamerChecks = 0;
void RequireTamer(bool Condition, const char* Message)
{
    ++TamerChecks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
}

int main()
{
    using namespace DigimonVenomNXTTamerCore;
    RequireTamer(StyleCount == 64, "Exactly 64 styles, not the numeric range through 89");
    std::set<int> Unique;
    for (int Index = 0; Index < StyleCount; ++Index)
    {
        const int Number = StyleNumberAt(Index);
        Unique.insert(Number);
        RequireTamer(IsStyleNumber(Number), "Every selectable index resolves to an available style");
    }
    RequireTamer(Unique.size() == 64, "No duplicate character entries");
    for (int Number = -20; Number < 120; ++Number)
    {
        const bool Supplied = (Number >= 2 && Number <= 5) || (Number >= 14 && Number <= 39) ||
            (Number >= 44 && Number <= 69) || (Number >= 82 && Number <= 89);
        RequireTamer(IsStyleNumber(Number) == Supplied, "Reject reserved holes and arbitrary client numbers");
    }
    RequireTamer(StyleNumberAt(0) == 2 && StyleNumberAt(1) == 3 && StyleNumberAt(2) == 4 && StyleNumberAt(3) == 5,
        "Four historical player IDs preserve their catalogue identity");
    RequireTamer(StyleNumberAt(-1) == 2 && StyleNumberAt(64) == 2 && StyleNumberAt(1000000) == 2,
        "Invalid catalogue indices safely resolve to the default");
    RequireTamer(StyleIndexForKey("") == 0, "Empty identity has a deterministic fallback");
    std::array<int, 64> Counts{};
    std::array<int, 1000> SavedAssignments{};
    for (int BotIndex = 0; BotIndex < 1000; ++BotIndex)
    {
        char BotId[32];
        std::snprintf(BotId, sizeof(BotId), "AI-%04d", BotIndex);
        const int Index = StyleIndexForKey(BotId);
        RequireTamer(Index >= 0 && Index < StyleCount, "Every persistent rival gets one supplied style");
        SavedAssignments[BotIndex] = Index;
        ++Counts[Index];
    }
    for (int Count : Counts) RequireTamer(Count > 0, "Default 1000-bot population uses every one of the 64 styles");
    // Reverse order emulates a different respawn/simulation order after loading.
    for (int BotIndex = 999; BotIndex >= 0; --BotIndex)
    {
        char BotId[32];
        std::snprintf(BotId, sizeof(BotId), "ai-%04d", BotIndex);
        RequireTamer(StyleIndexForKey(BotId) == SavedAssignments[BotIndex],
            "Respawn order and ASCII case do not change a persistent rival's appearance");
    }
    RequireTamer(StableStyleHash("rival:alpha") == StableStyleHash("RIVAL:ALPHA"), "Stable ASCII identity hashing");
    RequireTamer(StyleIndexForKey("season:mentor") == StyleIndexForKey(std::string("season:") + "mentor"),
        "Saved identity content controls appearance, not string storage addresses");
    std::cout << "Tamer catalogue core: " << TamerChecks << " checks passed\n";
}
