// Compile the production initiative and combat rules; Unreal adapters still need PIE.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatCore.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <tuple>

using namespace DigimonVenomNXTCombatCore;

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
Unit Rookie()
{
    // Synthetic initiative fixture, deliberately independent of authored species balance.
    Unit U;
    U.HP = U.MaxHP = 100; U.SP = U.MaxSP = 40;
    U.Attack = 20; U.Defense = 18; U.Speed = 20; U.Level = 1;
    U.Moves = {{38,4}, {50,8}, {62,12}, {74,16}};
    return U;
}
void TestSyntheticTwoHitTies()
{
    int TeamAFirst = 0;
    bool EveryFirstActorKeepsPriority = true, EveryResultMatchesActions = true;
    Unit Even = Rookie();
    // Neutral basic hits deal 60-70 damage, guaranteeing exactly two hits despite
    // variance. This checks tie fairness without claiming real rookies are two-hit KOs.
    Even.Attack = 80; Even.Defense = 0; Even.Moves.clear();
    for (uint32_t Seed = 0; Seed < 4096; ++Seed)
    {
        const Result R = Resolve({Even}, {Even}, 1, Seed, 20, true);
        if (R.Events.empty()) { EveryFirstActorKeepsPriority = false; continue; }
        const int First = R.Events.front().Team;
        TeamAFirst += First == 0 ? 1 : 0;
        EveryFirstActorKeepsPriority &= R.Events.size() == 3 && R.Rounds == 3 &&
            R.Events[0].Round == 1 && R.Events[1].Round == 2 && R.Events[2].Round == 3 &&
            R.Events[0].Clock == R.Events[1].Clock && R.Events[2].Clock > R.Events[1].Clock &&
            R.Events[1].Team != First && R.Events[2].Team == First;
        EveryResultMatchesActions &= !R.Draw && R.TeamAWon == (First == 0) && R.Events.back().TargetHPAfter == 0;
    }
    Require(EveryFirstActorKeepsPriority, "equal-speed CTB actors retain seeded priority across consecutive opportunities");
    Require(EveryResultMatchesActions, "synthetic two-hit mirror wins follow the actual first actor and recorded knockout");
    Require(TeamAFirst >= 1945 && TeamAFirst <= 2151, "4096 independent tie seeds divide first action approximately equally between both teams");
}
void TestSpeedDominanceAndStableOrdering()
{
    bool SpeedAlwaysWins = true, SortIndependent = true, ExactActionBudget = true, ExtraSpeedActions = true;
    Unit Tank = Rookie();
    Tank.HP = Tank.MaxHP = 100000; Tank.Defense = 100000; Tank.Moves.clear();
    for (uint32_t Seed = 0; Seed < 128; ++Seed)
    {
        for (int FastTeam = 0; FastTeam < 2; ++FastTeam)
        {
            Unit A = Tank, B = Tank;
            (FastTeam == 0 ? A : B).Speed *= 2;
            const Result R = Resolve({A}, {B}, 1, Seed, 20, true);
            ExactActionBudget &= R.Events.size() == 40 && R.Rounds == 40;
            SpeedAlwaysWins &= !R.Events.empty() && R.Events.front().Team == FastTeam;
            int FastActions = 0, SlowActions = 0;
            double PreviousClock = -1.0;
            for (std::size_t I = 0; I < R.Events.size(); ++I)
            {
                const Event& E = R.Events[I];
                if (E.Team == FastTeam) ++FastActions; else ++SlowActions;
                ExactActionBudget &= E.Round == static_cast<int>(I) + 1 && E.Clock >= PreviousClock;
                PreviousClock = E.Clock;
            }
            ExtraSpeedActions &= FastActions == 27 && SlowActions == 13;
        }
        std::vector<Initiative> Queue;
        for (int Team = 0; Team < 2; ++Team)
            for (int Actor = 0; Actor < 6; ++Actor)
                Queue.push_back(MakeInitiative(Seed, Team, Actor, 20 + Actor % 3));
        auto Reversed = Queue;
        std::reverse(Reversed.begin(), Reversed.end());
        std::sort(Queue.begin(), Queue.end(), InitiativePrecedes);
        std::sort(Reversed.begin(), Reversed.end(), InitiativePrecedes);
        for (std::size_t I = 0; I < Queue.size(); ++I)
        {
            SortIndependent &= Queue[I].Team == Reversed[I].Team && Queue[I].Actor == Reversed[I].Actor;
            if (I > 0) SortIndependent &= Queue[I-1].Speed >= Queue[I].Speed;
        }
    }
    Require(SpeedAlwaysWins, "faster units earn the first CTB opportunity on either side");
    Require(ExactActionBudget, "each CTB event advances one action number and respects the bounded budget");
    Require(ExtraSpeedActions, "double SPD earns extra actions at the expected two-to-one pace");
    Require(SortIndependent, "reversed command arrival and container order cannot change initiative");
    const uint32_t SavedSeed = BattleSeed(1, 44, 7, 299);
    const auto Original = MakeInitiative(SavedSeed, 1, 2, 42);
    const auto Restored = MakeInitiative(BattleSeed(1, 44, 7, 299), 1, 2, 42);
    Require(Original.Priority == Restored.Priority, "saved battle identity restores the exact initiative priority without a new roll");
    Require(!InitiativePrecedes(Original, Original), "initiative comparison is irreflexive");
    const Initiative CollisionA = {0, 2, 20, 17}, CollisionB = {1, 2, 20, 17}, CollisionC = {0, 3, 20, 17};
    Require(InitiativePrecedes(CollisionA, CollisionB) && !InitiativePrecedes(CollisionB, CollisionA) &&
        InitiativePrecedes(CollisionB, CollisionC), "explicit collision fallback gives a strict total order");
}
void TestLivingActorsAndDecisionFence()
{
    Unit Fragile = Rookie(); Fragile.HP = Fragile.MaxHP = 1; Fragile.Speed = 1;
    Unit Reserve = Rookie(); Reserve.HP = Reserve.MaxHP = 3000; Reserve.Attack = 500; Reserve.Defense = 1000; Reserve.Speed = 1000;
    Unit Killer = Rookie(); Killer.HP = Killer.MaxHP = 300; Killer.Attack = 100; Killer.Speed = 100;
    const Result Promotion = Resolve({Fragile, Reserve}, {Killer}, 1, 93, 200, true);
    bool NoInheritedTurn = true, ReserveActsNextOpportunity = false, OneActionEach = true;
    std::set<std::tuple<int,int,int>> Actions;
    for (const auto& E : Promotion.Events)
    {
        NoInheritedTurn &= !(E.Team == 0 && E.Actor == 0);
        if (E.Team == 0 && E.Actor == 1)
        { NoInheritedTurn &= E.Round >= 2; ReserveActsNextOpportunity |= E.Round == 2; }
        OneActionEach &= Actions.emplace(E.Round, E.Team, E.Actor).second;
    }
    Require(NoInheritedTurn && ReserveActsNextOpportunity && Promotion.TeamAWon, "a reserve waits for its own CTB time instead of inheriting a defeated partner's action");
    Require(OneActionEach, "each CTB action token records exactly one original actor");

    const uint64_t Battle = 887766;
    int Turn = 1, ResolvedRounds = 0;
    for (int Duplicate = 0; Duplicate < 5; ++Duplicate)
        if (IsCurrentDecision(Battle, Turn, Battle, 1)) { ++ResolvedRounds; ++Turn; }
    Require(ResolvedRounds == 1 && Turn == 2, "five copies of the same CTB Attack token resolve only one opportunity");
    Require(!IsCurrentDecision(Battle, Turn, Battle - 1, Turn), "a delayed previous-battle command is rejected even at the same turn number");
    Require(!IsCurrentDecision(Battle, Turn, Battle, Turn + 1), "future-turn commands cannot prequeue unseen CTB opportunities");
    Require(!IsCurrentDecision(Battle, 0, Battle, 0), "uninitialized turn tokens cannot submit a decision");
    Require(IsCurrentDecision(Battle, Turn, Battle, Turn), "the next fresh player decision remains accepted after duplicate rejection");
}
}

int main()
{
    TestSyntheticTwoHitTies();
    TestSpeedDominanceAndStableOrdering();
    TestLivingActorsAndDecisionFence();
    std::cout << "PASS: " << Checks << " initiative checks; synthetic two-hit mirrors, stable ties, CTB extra turns, replay/arrival independence, reserves and command fencing.\n";
}
