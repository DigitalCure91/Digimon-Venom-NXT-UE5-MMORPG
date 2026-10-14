// Run from the plugin root:
// g++ -std=c++17 -Wall -Wextra -Werror -pedantic Tools/test_gameplay_core.cpp -o /tmp/digimon-core-tests && /tmp/digimon-core-tests
// These tests compile the production combat core directly. Unreal integration still requires an Unreal build and PIE testing.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRivalRules.h"
#include "../Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTRankedRulesCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
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
Unit Fighter(int HP, int Attack, int Defense, int Speed, int Level = 1)
{
    Unit U;
    U.HP = U.MaxHP = HP;
    U.Attack = Attack; U.Defense = Defense; U.Speed = Speed; U.Level = Level;
    return U;
}
bool SameEvents(const Result& A, const Result& B)
{
    if (A.Events.size() != B.Events.size()) return false;
    for (std::size_t I = 0; I < A.Events.size(); ++I)
    {
        const Event& X = A.Events[I]; const Event& Y = B.Events[I];
        if (X.Team != Y.Team || X.Actor != Y.Actor || X.Target != Y.Target || X.Damage != Y.Damage || X.MoveIndex != Y.MoveIndex || X.Round != Y.Round) return false;
    }
    return true;
}
void CheckBounds(const Result& R)
{
    for (const auto* Team : {&R.A, &R.B})
        for (const auto& U : *Team)
        {
            Require(U.HP >= 0 && U.HP <= U.MaxHP, "HP stays within its legal bounds");
            Require(U.SP >= 0 && U.SP <= U.MaxSP, "SP stays within its legal bounds");
        }
}
void TestRivalWindows()
{
    struct Counters { int Battles = 0; int Scans = 0; };
    struct Rival { Counters WindowStats; Counters LifetimeStats; std::vector<int> Collection; };
    std::vector<Rival> Rivals = {{{7, 35}, {300, 1500}, {11, 12, 13}}, {{9, 45}, {400, 2000}, {21}}};
    std::int64_t Start = 43200;
    Require(DigimonVenomNXTRivalRules::WindowStart(86399) == 43200 && DigimonVenomNXTRivalRules::WindowStart(86400) == 86400, "12-hour windows change exactly at the boundary");
    Require(!DigimonVenomNXTRivalRules::RefreshWindow<std::int64_t>(86399, Start, Rivals), "counters survive until the final second of the window");
    Require(Rivals[0].WindowStats.Battles == 7 && Rivals[1].WindowStats.Scans == 45, "reading current-window stats does not clear them");
    Require(DigimonVenomNXTRivalRules::RefreshWindow<std::int64_t>(86400, Start, Rivals), "exact boundary resets every rival once");
    Require(Start == 86400 && Rivals[0].WindowStats.Battles == 0 && Rivals[1].WindowStats.Scans == 0, "new window starts with zero activity");
    Require(Rivals[0].LifetimeStats.Battles == 300 && Rivals[1].LifetimeStats.Scans == 2000, "window reset preserves lifetime totals");
    Require(Rivals[0].Collection == std::vector<int>({11, 12, 13}) && Rivals[1].Collection == std::vector<int>({21}), "window reset preserves owned collections");
    Rivals[0].WindowStats.Battles = 1;
    Require(!DigimonVenomNXTRivalRules::RefreshWindow<std::int64_t>(86400, Start, Rivals) && Rivals[0].WindowStats.Battles == 1, "repeated boundary refresh cannot erase new activity");
    Require(!DigimonVenomNXTRivalRules::RefreshWindow<std::int64_t>(80000, Start, Rivals) && Start == 86400 && Rivals[0].WindowStats.Battles == 1, "clock rollback cannot rewind the window or erase activity");
    Require(DigimonVenomNXTRivalRules::RefreshWindow<std::int64_t>(604900, Start, Rivals) && Start == 604800, "offline leap moves directly to the current window");
    Require(Rivals[0].WindowStats.Battles == 0 && Rivals[0].LifetimeStats.Battles == 300, "offline leap resets current stats without inventing lifetime activity");
    Require(DigimonVenomNXTRivalRules::NextLevelXP(1) == 47 && DigimonVenomNXTRivalRules::NextLevelXP(2) == 114 && DigimonVenomNXTRivalRules::NextLevelXP(3) == 208, "XP thresholds are cumulative for early levels");
    Require(DigimonVenomNXTRivalRules::NextLevelXP(99) == 387719 && DigimonVenomNXTRivalRules::NextLevelXP(0) == 47, "high-level and invalid-low-level XP thresholds are safe");
}
void TestRankedRules()
{
    namespace Ranked = DigimonVenomNXTRankedRulesCore;
    const int Thresholds[] = {0,100,300,600,1000,1800};
    const int Repeated[] = {0,100,300,600,600,1800};
    const int Negative[] = {-1,100,300,600,1000,1800};
    const int Oversized[] = {0,100,300,600,1000,1000000};
    Require(Ranked::AreThresholdsValid(Thresholds,6), "source Bronze through Master thresholds validate");
    Require(!Ranked::AreThresholdsValid(nullptr,6) && !Ranked::AreThresholdsValid(Thresholds,5), "missing grade configuration fails safely");
    Require(!Ranked::AreThresholdsValid(Repeated,6) && !Ranked::AreThresholdsValid(Negative,6) && !Ranked::AreThresholdsValid(Oversized,6), "invalid thresholds fail safely");
    for(int I=0;I<6;++I) {
        Require(Ranked::GradeIndex(Thresholds[I],Thresholds)==I,"grade eligibility begins at exact threshold");
        if(I>0) Require(Ranked::GradeIndex(Thresholds[I]-1,Thresholds)==I-1,"one point below threshold is ineligible");
    }
    Require(Ranked::GradeIndex(-100,Thresholds)==0 && Ranked::GradeIndex(1000000,Thresholds)==5,"points remain within six grades");
    auto P=Ranked::ApplyPoints(80,0,true,false,true,Thresholds);
    Require(P.Points==100 && P.Grade==0 && !P.Promoted && P.PromotionPending,"threshold-reaching win opens a promotion match");
    P=Ranked::ApplyPoints(P.Points,P.Grade,true,false,true,Thresholds);
    Require(P.Points==120 && P.Grade==1 && P.Promoted,"next attacking win earns promotion");
    P=Ranked::ApplyPoints(100,0,true,false,false,Thresholds);
    Require(P.Points==120 && P.Grade==0 && P.PromotionPending,"defense victory gives points but cannot promote");
    P=Ranked::ApplyPoints(100,0,false,false,true,Thresholds);
    Require(P.Points==95 && P.Grade==0 && !P.PromotionPending,"lost promotion reduces points by five and clears eligibility");
    P=Ranked::ApplyPoints(2,1,false,false,true,Thresholds);
    Require(P.Points==0 && P.Grade==1,"points cannot go negative and earned grade persists after losses");
    P=Ranked::ApplyPoints(100,0,false,true,true,Thresholds);
    Require(P.Points==100 && P.Grade==0 && !P.Promoted,"draw cannot promote or change points");
    const int Placement[]={1,2,10,11,25,26,50,51,100,101,500,501};
    const int Bracket[]={0,1,1,2,2,3,3,4,4,5,5,6};
    for(int I=0;I<12;++I) Require(Ranked::PlacementBracket(Placement[I])==Bracket[I],"source placement reward boundaries");

    constexpr std::int64_t Monday = 1791158400; // 2026-10-05 00:00:00 UTC.
    constexpr std::int64_t Week = 7 * 86400;
    Require(Ranked::SeasonStart(Monday, 7) == Monday, "weekly season begins on the exact Monday UTC boundary");
    Require(Ranked::SeasonStart(Monday - 1, 7) == Monday - Week, "the final second of Sunday belongs to the previous season");
    Require(Ranked::SeasonStart(Monday + Week - 1, 7) == Monday && Ranked::SeasonStart(Monday + Week, 7) == Monday + Week, "seven-day season switches once at expiry");
    Require(Ranked::SeasonStart(Monday + 9 * Week + 73, 7) == Monday + 9 * Week, "offline weeks jump to the active season without intermediate seasons");
    constexpr std::int64_t Epoch = 345600;
    Require(Ranked::SeasonStart(Epoch + 5 * 86400 - 1, 5) == Epoch && Ranked::SeasonStart(Epoch + 5 * 86400, 5) == Epoch + 5 * 86400, "configured five-day seasons honor their exact boundary");

    Require(!Ranked::RewardEligible(0) && Ranked::RewardEligible(1), "passive defenses do not qualify; one ranked attack qualifies for weekly rewards");
    Require(!Ranked::RewardEligible(2,3) && Ranked::RewardEligible(3,3), "host minimum uses attacking matches only");
    const Ranked::EnergyState Before = {27, 1000};
    auto Energy = Ranked::Recharge(Before, 1299, 30, 300);
    Require(Energy.Energy == 27 && Energy.Anchor == 1000, "energy does not recharge one second early");
    Energy = Ranked::Recharge(Before, 1300, 30, 300);
    Require(Energy.Energy == 28 && Energy.Anchor == 1300, "energy gains exactly one at five minutes");
    Energy = Ranked::Recharge(Before, 1650, 30, 300);
    Require(Energy.Energy == 29 && Energy.Anchor == 1600, "partial refill retains progress toward the next unit");
    Energy = Ranked::Recharge(Before, 1900, 30, 300);
    Require(Energy.Energy == 30 && Energy.Anchor == 1900, "energy reaches its cap exactly");
    Energy = Ranked::Recharge({0, 1000}, 1000 + 6 * Week, 30, 300);
    Require(Energy.Energy == 30 && Energy.Anchor == 1000 + 6 * Week, "offline recovery caps at thirty without banked surplus");
    Energy = Ranked::Recharge({30, 1000}, 4000, 30, 300);
    Require(Energy.Energy == 30 && Energy.Anchor == 4000, "full energy discards prior recharge time");
    --Energy.Energy;
    Energy = Ranked::Recharge(Energy, 4299, 30, 300);
    Require(Energy.Energy == 29, "spending at cap starts a fresh full five-minute wait");
    Energy = Ranked::Recharge(Energy, 4300, 30, 300);
    Require(Energy.Energy == 30, "spent cap energy returns after five minutes");
    Energy = Ranked::Recharge({12, 1000}, 900, 30, 300);
    Require(Energy.Energy == 12 && Energy.Anchor == 900, "backward clock does not grant or remove energy");
    Energy = Ranked::Recharge({-50, 1000}, 1000, 20, 300);
    Require(Energy.Energy == 0, "negative saved energy normalizes to zero");
    Energy = Ranked::Recharge({50, 1000}, 1000, 20, 300);
    Require(Energy.Energy == 20, "lowered global energy cap takes effect safely");
    Energy = Ranked::Recharge({0, 1}, std::numeric_limits<std::int64_t>::max(), 30, 300);
    Require(Energy.Energy == 30, "extreme elapsed time cannot overflow energy");

    Require(Ranked::RatingDelta(1500, 1500, 1.0f, 40) == 20 && Ranked::RatingDelta(1500, 1500, 0.0f, 40) == -20, "equal-rating wins and losses have symmetric Elo movement");
    Require(Ranked::RatingDelta(1500, 1500, 0.5f, 40) == 0, "equal-rating draw preserves rating");
    Require(Ranked::RatingDelta(1000, 2000, 1.0f, 40) > Ranked::RatingDelta(2000, 1000, 1.0f, 40), "an upset win earns more rating than beating a weaker opponent");
    Require(Ranked::RatingDelta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 1.0f, 40) == 40, "extreme rating difference stays numerically bounded");
    Require(Ranked::RatingDelta(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), 0.0f, 40) == -40, "extreme reversed rating difference stays numerically bounded");
}
}

int main()
{
    TestRivalWindows();
    TestRankedRules();
    // A seed captures the complete replay, including speed ties and damage variance.
    Unit Even = Fighter(1200, 70, 50, 40, 10);
    Even.Moves = {{70, 6}, {110, 15}};
    const Result RepeatA = Resolve({Even, Even, Even}, {Even, Even, Even}, 3, 8128);
    const Result RepeatB = Resolve({Even, Even, Even}, {Even, Even, Even}, 3, 8128);
    Require(SameEvents(RepeatA, RepeatB), "identical teams and seed reproduce every logged event");
    Require(RepeatA.TeamAWon == RepeatB.TeamAWon && RepeatA.Draw == RepeatB.Draw && RepeatA.Rounds == RepeatB.Rounds, "seeded result reproduces");
    for (std::size_t I = 0; I < RepeatA.A.size(); ++I)
        Require(RepeatA.A[I].HP == RepeatB.A[I].HP && RepeatA.A[I].SP == RepeatB.A[I].SP && RepeatA.B[I].HP == RepeatB.B[I].HP && RepeatA.B[I].SP == RepeatB.B[I].SP, "seeded final vitals reproduce");

    // Strength comes from battle actions, rather than a probability coin flip.
    const Unit Strong = Fighter(1200, 200, 100, 100, 50);
    const Unit Weak = Fighter(150, 15, 10, 10, 2);
    for (uint32_t Seed = 0; Seed < 64; ++Seed)
    {
        const Result R = Resolve({Strong, Strong, Strong}, {Weak, Weak, Weak}, 3, Seed);
        Require(R.TeamAWon && !R.Draw, "clearly stronger team wins across seeds");
        CheckBounds(R);
    }

    const Result Speed = Resolve({Fighter(1000, 1, 500, 2)}, {Fighter(1000, 1, 500, 99)}, 1, 7, 1);
    Require(!Speed.Events.empty() && Speed.Events.front().Team == 1, "faster living unit acts first");

    Unit Fainted = Fighter(100, 999, 1, 1000); Fainted.HP = 0;
    const Result AlreadyFainted = Resolve({Fainted, Strong}, {Weak}, 1, 99);
    for (const Event& E : AlreadyFainted.Events)
        Require(!(E.Team == 0 && E.Actor == 0), "initially fainted unit never acts");
    Require(AlreadyFainted.TeamAWon, "living reserve replaces an initially fainted lead");

    Unit Fragile = Fighter(1, 1, 1, 1);
    Unit Reserve = Fighter(3000, 500, 1000, 1000);
    Unit Killer = Fighter(300, 100, 1, 100);
    const Result Promotion = Resolve({Fragile, Reserve}, {Killer}, 1, 123);
    bool ReserveActed = false;
    for (const Event& E : Promotion.Events)
    {
        Require(!(E.Team == 0 && E.Actor == 0), "unit defeated before its queued action never acts");
        if (E.Team == 0 && E.Actor == 1)
        {
            ReserveActed = true;
            Require(E.Round >= 2, "promoted reserve cannot inherit the fainted unit's queued turn");
        }
    }
    Require(Promotion.TeamAWon && ReserveActed, "reserve promotes and can win the battle");

    // Six SP supports a four-SP skill, then a two-SP skill, then regular Attack.
    Unit Caster = Fighter(100000, 30, 1, 100);
    Caster.SP = 6; Caster.Moves = {{145, 4}, {125, 2}, {155, 7}, {155, -1}};
    const Unit Tank = Fighter(100000, 1, 1, 100);
    const Result Mana = Resolve({Caster}, {Tank}, 1, 17, 3);
    std::vector<int> Used;
    for (const Event& E : Mana.Events) if (E.Team == 0) Used.push_back(E.MoveIndex);
    Require(Used == std::vector<int>({0, 1, -1}), "AI uses the strongest affordable skill and falls back to Attack");
    Require(Mana.A.front().SP == 0, "skill costs are charged exactly once");
    Require(Mana.Draw && !Mana.TeamAWon && Mana.Rounds == 6, "bounded CTB action limit produces a draw while both teams survive");
    CheckBounds(Mana);

    Unit Over = Tank; Over.HP += 1000; Over.SP += 1000;
    Unit Under = Tank; Under.HP = -8; Under.SP = -6;
    const Result Bounds = Resolve({Over, Under}, {Tank}, 1, 3, 1);
    CheckBounds(Bounds);
    Require(Bounds.A[1].HP == 0 && Bounds.A[1].SP == 0, "invalid negative initial vitals are clamped");

    const Result Empty = Resolve({}, {}, 3, 1);
    const Result Forfeit = Resolve({}, {Tank}, 3, 1);
    Require(Empty.Draw && !Empty.TeamAWon && Empty.Events.empty(), "empty teams produce a safe draw");
    Require(!Forfeit.Draw && !Forfeit.TeamAWon && Forfeit.Events.empty(), "empty challenger loses without fabricating actions");
    Require(ScaledStat(100, 1) == 100 && ScaledStat(100, 20) > 100, "level progression increases combat stats");

    std::cout << "PASS: " << Checks << " checks; combat, reserves/SP, activity rollover, XP, ranked energy/calendar/grades/Elo.\n";
    return 0;
}
