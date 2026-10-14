// Compile and execute the production expedition planner without Unreal:
// c++ -std=c++17 -Wall -Wextra -Werror -pedantic Tools/test_rival_training_core.cpp -o /tmp/digimon-training-tests
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRivalTrainingCore.h"
#include <iostream>
#include <fstream>
#include <set>

namespace
{
    int Checks = 0;
    void Require(bool Condition, const char* Message)
    {
        ++Checks;
        if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    }
}

int main(int Argc, char** Argv)
{
    using namespace DigimonVenomNXTRivalTrainingCore;
    std::vector<Candidate> Collection = {{0,100,4,0},{1,2,0,0},{2,3,0,0},{3,94,2,0},{4,65,1,0},{5,5,0,0}};
    const int Rookie = ChooseLeader(Collection, 17);
    Require(Rookie == 1 || Rookie == 2 || Rookie == 5, "new materializations lead before the veteran");
    const auto LowParty = BuildParty(Collection, Rookie, 6, 6, 17);
    Require(LowParty.front() == Rookie, "the selected trainee actually occupies leader slot zero");
    Require(LowParty.size() == 3, "training party contains the complete eligible rookie cohort");
    for (int Index : LowParty) Require(Collection[Index].Level <= 5, "unrelated high-level carries stay in collection");
    const auto VeteranParty = BuildParty(Collection, 0, 6, 6, 17);
    Require(VeteranParty == std::vector<int>({0,3}), "high-level partners retain their own training cohort");
    Require(BuildParty(Collection, 0, 1, 6, 17) == std::vector<int>({0}), "single-slot party setting is respected");
    Require(BuildParty(Collection, 0, 6, 0, 17) == std::vector<int>({0}), "zero span keeps exact-level cohorts");
    Require(BuildParty(Collection, -1, 6, 6, 17).empty(), "invalid leaders cannot manufacture a party");

    // Every real owned partner leads during each complete fair cycle. Recreating
    // the transient candidates from persisted ages produces identical decisions.
    std::int64_t Serial = 4;
    std::set<int> Led;
    for (std::size_t Session = 0; Session < Collection.size(); ++Session)
    {
        const auto AfterRestart = Collection;
        const int Leader = ChooseLeader(Collection, 42);
        Require(Leader == ChooseLeader(AfterRestart, 42), "persisted ages resume the same fair cycle after restart");
        Led.insert(Leader);
        Collection[Leader].LastLedSession = ++Serial;
    }
    Require(Led.size() == Collection.size(), "every cohort including the veteran eventually leads");
    const auto BeforeMaterialization = Collection;
    Collection.push_back({6,1,0,0});
    Require(ChooseLeader(Collection, 42) == 6, "newly acquired partner receives the next fair training opportunity");
    for (std::size_t Index = 0; Index < BeforeMaterialization.size(); ++Index)
        Require(Collection[Index].Level == BeforeMaterialization[Index].Level &&
            Collection[Index].LastLedSession == BeforeMaterialization[Index].LastLedSession,
            "selection never resets existing levels or history");

    Require(!SessionFinished(0,8,1,100), "zero-battle sessions cannot churn without doing work");
    Require(!SessionFinished(7,8,20,25), "a party trains for its configured session");
    Require(SessionFinished(8,8,20,20), "losses also complete a session so one cohort cannot stall forever");
    Require(SessionFinished(1,8,1,7), "six actual level gains allow an early fair handoff");
    Require(!SessionFinished(0,0,1,1) && SessionFinished(1,0,1,1), "invalid battle limits normalize safely");

    // Registry starter maps: cap four, five, five; a cap-six field stays ineligible.
    std::vector<Habitat> Maps = {{1,1,4,0},{2,1,5,0},{3,1,5,0},{4,1,6,0}};
    for (int Bot = 0; Bot < 1000; ++Bot)
    {
        const int Destination = ChooseHabitat(Maps, 5, -1, static_cast<unsigned>(Bot));
        Require(Destination >= 1 && Destination <= 3, "population balance never sends a rookie above its safe ceiling");
        ++Maps[Destination-1].Population;
    }
    const int Lowest = std::min({Maps[0].Population, Maps[1].Population, Maps[2].Population});
    const int Highest = std::max({Maps[0].Population, Maps[1].Population, Maps[2].Population});
    Require(Highest-Lowest <= 1, "1000 eligible bots populate the three starter habitats almost evenly");
    Require(Maps[3].Population == 0, "empty unsafe maps do not pull in unsuitable bots");
    for (int Seed = 0; Seed < 100; ++Seed)
        Require(ChooseHabitat(Maps, 5, 1, static_cast<unsigned>(Seed)) == 1, "balanced occupancy does not cause endless map hopping");

    Maps = {{1,1,4,20},{2,1,5,0},{3,1,5,0},{4,1,6,0}};
    for (int Bot = 0; Bot < 20; ++Bot)
    {
        const int Destination = ChooseHabitat(Maps, 5, 1, static_cast<unsigned>(Bot));
        if (Destination != 1) { --Maps[0].Population; ++Maps[Destination-1].Population; }
    }
    Require(std::max({Maps[0].Population,Maps[1].Population,Maps[2].Population})-
        std::min({Maps[0].Population,Maps[1].Population,Maps[2].Population}) <= 1,
        "existing overloaded saves rebalance instead of only balancing new tamers");
    Require(ChooseHabitat(Maps,1,4,0) == 1, "level-reset partners return to the lowest real encounter ceiling");
    Maps = {{1,1,4,0},{2,45,50,4},{3,90,94,1},{4,95,100,9},{5,96,101,0}};
    Require(ChooseHabitat(Maps,100,4,0) == 3, "veteran parties balance only within their eligible high-level band");
    Require(ChooseHabitat(Maps,50,4,0) == 2, "midlevel rotation travels down to the matching training field");
    Require(ChooseHabitat(Maps,1,4,0) == 1, "new materialization switches high field to starter habitat");
    Require(ChooseHabitat({},50,12,0) == 12, "missing map content cannot produce an invented map ID");

    // Initial equal-age migration avoids giving every tamer the exact same lead.
    std::vector<Candidate> Migration = {{0,5,0,0},{1,50,0,0},{2,100,0,0}};
    std::set<int> MigratedLeaders;
    for (unsigned Seed = 0; Seed < 1000; ++Seed) MigratedLeaders.insert(ChooseLeader(Migration,Seed));
    Require(MigratedLeaders.size() == 3, "stable per-tamer migration distributes initial cohorts");
    Migration[0].HabitatPopulation = 10; Migration[1].HabitatPopulation = 8;
    Require(ChooseLeader(Migration,1) == 2, "equally old leaders prefer eligible underpopulated fields");
    Migration[2].LastLedSession = 1;
    Require(ChooseLeader(Migration,1) == 1, "map crowding cannot starve older training cohorts");

    // Optional real-registry fixture generated by test_rival_training_registry.py.
    if (Argc == 2)
    {
        std::ifstream Input(Argv[1]);
        Require(static_cast<bool>(Input), "real habitat registry fixture opens");
        std::vector<Habitat> Registry;
        Habitat Map;
        while (Input >> Map.Id >> Map.MinLevel >> Map.MaxLevel) Registry.push_back(Map);
        Require(!Registry.empty(), "real habitat registry contains maps");
        std::vector<int> Locations(1000, -1);
        auto Count = [&Registry](int Id, int Delta)
        {
            for (auto& Value : Registry) if (Value.Id == Id) { Value.Population += Delta; break; }
        };
        for (int Sweep = 0; Sweep < 12; ++Sweep)
            for (int Bot = 0; Bot < 1000; ++Bot)
            {
                const int Level = std::max(5, 1 + Bot % 100);
                const int Destination = ChooseHabitat(Registry, Level, Locations[Bot], static_cast<unsigned>(Bot));
                const auto Found = std::find_if(Registry.begin(), Registry.end(), [Destination](const Habitat& Value) { return Value.Id == Destination; });
                Require(Found != Registry.end() && DigimonVenomNXTRivalRules::IsSuitableMap(Found->MinLevel,Found->MaxLevel,Level),
                    "real-registry population remains eligible throughout initial placement and every rebalance");
                if (Locations[Bot] != Destination) { Count(Locations[Bot],-1); Count(Destination,1); Locations[Bot] = Destination; }
            }
        int Occupied = 0;
        int Minimum = 1000;
        int Maximum = 0;
        for (const auto& Value : Registry)
        {
            Occupied += Value.Population > 0;
            Minimum = std::min(Minimum, Value.Population); Maximum = std::max(Maximum, Value.Population);
        }
        Require(Occupied == static_cast<int>(Registry.size()), "diverse eligible training cohorts populate every real public habitat");
        // Level-five starters are deliberately overrepresented (50 of 1000) and
        // only three actual habitats support them. Absolute global equality is
        // impossible without violating eligibility. Verify the stronger useful
        // invariant: no tamer can improve a population gap by moving safely.
        for (int Bot = 0; Bot < 1000; ++Bot)
            Require(ChooseHabitat(Registry,std::max(5,1+Bot%100),Locations[Bot],static_cast<unsigned>(Bot)) == Locations[Bot],
                "real registry reaches stable near-even occupancy within each tamer's eligible habitats");
        const auto LowestCeiling = std::min_element(Registry.begin(),Registry.end(),[](const Habitat& A,const Habitat& B)
            { return DigimonVenomNXTRivalRules::MapEncounterCeiling(A.MinLevel,A.MaxLevel) < DigimonVenomNXTRivalRules::MapEncounterCeiling(B.MinLevel,B.MaxLevel); });
        const int RookieMap = ChooseHabitat(Registry,1,Locations.back(),42);
        const auto FoundRookieMap = std::find_if(Registry.begin(),Registry.end(),[RookieMap](const Habitat& Value) { return Value.Id == RookieMap; });
        Require(FoundRookieMap != Registry.end() && DigimonVenomNXTRivalRules::MapEncounterCeiling(FoundRookieMap->MinLevel,FoundRookieMap->MaxLevel) ==
            DigimonVenomNXTRivalRules::MapEncounterCeiling(LowestCeiling->MinLevel,LowestCeiling->MaxLevel),
            "new level-one ownership returns from a veteran field to the safest real starter field");
        std::cout << "Real registry: " << Occupied << '/' << Registry.size() << " habitats populated; " << Minimum << '-' << Maximum << " tamers per habitat.\n";
    }
    std::cout << "Rival training core: " << Checks << " checks passed.\n";
}
