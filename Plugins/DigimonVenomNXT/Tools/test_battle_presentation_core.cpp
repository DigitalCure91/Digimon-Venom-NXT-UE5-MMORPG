// This compiles the actual production resolver. It does not emulate Unreal UI/networking.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatCore.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace DigimonVenomNXTCombatCore;

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
Unit Fighter(int HP, int Attack, int Defense, int Speed, int SP = 40)
{
    Unit U;
    U.HP = U.MaxHP = HP; U.SP = U.MaxSP = SP;
    U.Attack = Attack; U.Defense = Defense; U.Speed = Speed;
    return U;
}
bool SameVitals(const std::vector<Unit>& A, const std::vector<Unit>& B)
{
    if (A.size() != B.size()) return false;
    for (std::size_t I = 0; I < A.size(); ++I)
        if (A[I].HP != B[I].HP || A[I].SP != B[I].SP) return false;
    return true;
}
bool SameEvent(const Event& A, const Event& B)
{
    return A.Team == B.Team && A.Actor == B.Actor && A.Target == B.Target &&
        A.Damage == B.Damage && A.MoveIndex == B.MoveIndex && A.Round == B.Round &&
        A.ActorSPAfter == B.ActorSPAfter && A.TargetHPAfter == B.TargetHPAfter;
}
// Project only recorded after-state, as presentation must; independently check it against
// before-state and move costs so bad event capture cannot silently pass the final check.
bool ReplayIsExact(std::vector<Unit> A, std::vector<Unit> B, int ActiveSize, const Result& R)
{
    int LastRound = 0;
    for (const Event& E : R.Events)
    {
        if (E.Team != 0 && E.Team != 1) return false;
        auto& Actors = E.Team == 0 ? A : B;
        auto& Targets = E.Team == 0 ? B : A;
        if (E.Actor < 0 || E.Actor >= static_cast<int>(Actors.size()) ||
            E.Target < 0 || E.Target >= static_cast<int>(Targets.size())) return false;
        const auto AA = Active(Actors, ActiveSize), BB = Active(Targets, ActiveSize);
        if (std::find(AA.begin(), AA.end(), E.Actor) == AA.end() ||
            std::find(BB.begin(), BB.end(), E.Target) == BB.end()) return false;
        const Unit& Actor = Actors[E.Actor];
        const Unit& Target = Targets[E.Target];
        if (E.Round < LastRound || E.Round < 1 || E.Round > R.Rounds || E.Damage < 1) return false;
        LastRound = E.Round;
        if (E.MoveIndex >= static_cast<int>(Actor.Moves.size()) || E.MoveIndex < -1) return false;
        const int Cost = E.MoveIndex >= 0 ? Actor.Moves[E.MoveIndex].SPCost : 0;
        if (E.ActorSPAfter != Actor.SP - Cost || E.ActorSPAfter < 0 ||
            E.TargetHPAfter != std::max(0, Target.HP - E.Damage)) return false;
        Actors[E.Actor].SP = E.ActorSPAfter;
        Targets[E.Target].HP = E.TargetHPAfter;
    }
    return SameVitals(A, R.A) && SameVitals(B, R.B);
}

void TestLongMatch()
{
    // More than the former 80-entry text log: final UI vitals would be wrong if the
    // replay accidentally reused that log instead of the complete action trace.
    Unit A = Fighter(150, 1, 10000, 100, 19);
    Unit B = Fighter(150, 1, 10000, 20, 19);
    A.Moves = B.Moves = {{80, 7}, {50, 3}};
    const Result Full = Resolve({A}, {B}, 1, 91281, 200, true);
    const Result Short = Resolve({A}, {B}, 1, 91281, 200, false);
    Require(Full.Events.size() > 80 && Short.Events.size() == 80, "human trace continues beyond the bounded headless text history");
    Require(Full.TeamAWon && !Full.Draw && Full.B[0].HP == 0, "long test reaches a real terminal win");
    Require(ReplayIsExact({A}, {B}, 1, Full), "every long-match action replays to exact final HP and SP");
    Require(!ReplayIsExact({A}, {B}, 1, Short), "truncated trace cannot falsely pass final-vitals verification");
    Require(Full.TeamAWon == Short.TeamAWon && Full.Draw == Short.Draw && Full.Rounds == Short.Rounds &&
        SameVitals(Full.A, Short.A) && SameVitals(Full.B, Short.B), "recording full presentation never changes combat outcome");
    bool PrefixMatches = true;
    for (std::size_t I = 0; I < Short.Events.size(); ++I) PrefixMatches &= SameEvent(Full.Events[I], Short.Events[I]);
    Require(PrefixMatches, "complete and bounded traces describe identical first eighty actions");
}
void TestPromotionAndRandomizedParties()
{
    const Unit Fragile = Fighter(1, 1, 1, 1);
    const Unit Reserve = Fighter(3000, 500, 1000, 1000);
    const Unit Killer = Fighter(300, 100, 1, 100);
    const Result Promotion = Resolve({Fragile, Reserve}, {Killer}, 1, 123, 200, true);
    Require(ReplayIsExact({Fragile, Reserve}, {Killer}, 1, Promotion), "promotion trace preserves original roster identities and exact vitals");
    Require(Promotion.Events.size() >= 2 && Promotion.Events[0].Team == 1 &&
        Promotion.Events[0].Target == 0 && Promotion.Events[0].TargetHPAfter == 0 &&
        Promotion.Events[1].Team == 0 && Promotion.Events[1].Actor == 1 &&
        Promotion.Events[1].Round == 2, "a promoted reserve earns its own CTB opportunity, never the defeated actor's queued turn");

    for (uint32_t Seed = 0; Seed < 32; ++Seed)
    {
        std::vector<Unit> A, B;
        for (int I = 0; I < 9; ++I)
        {
            Unit Ally = Fighter(150 + I * 23, 10 + I * 7, 20 + I * 3, 10 + ((I * 13) % 40), 20 + I);
            Unit Enemy = Fighter(180 + I * 17, 12 + I * 6, 15 + I * 4, 10 + ((I * 17) % 40), 15 + I);
            Ally.Moves = {{60, 3}, {100, 12}}; Enemy.Moves = {{55, 4}, {90, 9}};
            A.push_back(Ally); B.push_back(Enemy);
        }
        const int ActiveSize = 1 + static_cast<int>(Seed % 6);
        const Result R = Resolve(A, B, ActiveSize, Seed, 200, true);
        Require(!R.Events.empty() && ReplayIsExact(A, B, ActiveSize, R), "mixed parties replay exactly across seeds, active sizes and reserve promotions");
    }
}
void TestBoundedDrawAndFinalStrike()
{
    const Unit Tank = Fighter(100000, 1, 100000, 1);
    const std::vector<Unit> Six(6, Tank);
    const Result Maximum = Resolve(Six, Six, 6, 73, 1000, true);
    // The compatibility budget is still 1000 * six actives * two teams.
    // Rounds now counts CTB action opportunities, matching Event.Round and the
    // interactive TurnNumber, rather than groups of twelve simultaneous commands.
    Require(Maximum.Draw && Maximum.Rounds == 12000 && Maximum.Events.size() == 12000,
        "complete CTB trace obeys the twelve-thousand-action upper bound without truncation");
    Require(Maximum.Events.back().Round == Maximum.Rounds,
        "the terminal CTB action number matches the complete recorded trace");
    Require(ReplayIsExact(Six, Six, 6, Maximum), "action-limit draw has exact replay vitals after all CTB opportunities");
    const Unit Fast = Fighter(10, 1000, 1, 100);
    const Unit Slow = Fighter(10, 1000, 1, 1);
    const Result OneHit = Resolve({Fast}, {Slow}, 1, 82, 200, true);
    Require(OneHit.Events.size() == 1 && OneHit.Events.front().TargetHPAfter == 0 && OneHit.TeamAWon,
        "terminal strike is retained and defeated final opponent produces no extra action");
    Require(ReplayIsExact({Fast}, {Slow}, 1, OneHit), "one-action battle still includes exact final presentation state");
}
}

int main()
{
    TestLongMatch();
    TestPromotionAndRandomizedParties();
    TestBoundedDrawAndFinalStrike();
    std::cout << "PASS: " << Checks << " battle-presentation checks; complete traces, terminal strikes, SP/HP replay, reserves and bounded draws.\n";
}
