#pragma once
// Engine-independent battle rules, compiled directly by Tools/test_gameplay_core.cpp.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include "DigimonVenomNXTTimelineCore.h"

namespace DigimonVenomNXTCombatCore
{
// Enum ordinals mirror the append-only Unreal enums without depending on the engine.
struct Move { int Power = 100; int SPCost = 0; int DamageClass = 0; int Element = 0; };
struct Unit
{
    int HP = 100, SP = 40, MaxHP = 100, MaxSP = 40;
    int Attack = 20, Defense = 20, Speed = 20, Level = 1;
    std::vector<Move> Moves;
    int Spirit = 20, Affinity = 0, Element = 0, CAM = 0;
    bool Guarding = false;
    double DamageMultiplier = 1.0;
};
// Stable roster indices identify the original unit, never a replacement in the same visual slot.
// Post-action vitals make replay exact without repeating random choices or damage calculations.
struct Event
{
    int Team = 0, Actor = 0, Target = 0, Damage = 0, MoveIndex = -1, Round = 0;
    int ActorSPAfter = 0, TargetHPAfter = 0;
    float Effectiveness = 1.0f, TypeMultiplier = 1.0f, ElementMultiplier = 1.0f;
    int DamageClass = 0, Element = 0;
    double Clock = 0.0;
    float ComboMultiplier = 1.0f;
    bool Guarded = false;
};
struct Result
{
    bool TeamAWon = false, Draw = false;
    int Rounds = 0;
    std::vector<Unit> A, B;
    std::vector<Event> Events;
};
// Initiative is independent of command arrival, container order and damage RNG.
// Exact speed ties retain their seeded order for the whole battle: re-rolling on
// each round can grant back-to-back attacks at the round boundary in a two-hit KO.
struct Initiative
{
    int Team = 0, Actor = 0, Speed = 1;
    uint32_t Priority = 0;
};
inline uint32_t MixSeed(uint32_t Value)
{
    Value ^= Value >> 16; Value *= 0x7feb352du;
    Value ^= Value >> 15; Value *= 0x846ca68bu;
    return Value ^ (Value >> 16);
}
inline uint32_t BattleSeed(uint32_t A, uint32_t B, uint32_t C, uint32_t D)
{
    return MixSeed(A ^ MixSeed(B) ^ MixSeed(C + 0x9e3779b9u) ^ MixSeed(D + 0x85ebca6bu));
}
inline Initiative MakeInitiative(uint32_t Seed, int Team, int Actor, int Speed)
{
    return {Team, Actor, std::max(1, Speed),
        MixSeed(Seed ^ (Team == 0 ? 0x243f6a88u : 0xb7e15162u) ^ MixSeed(static_cast<uint32_t>(Actor)))};
}
inline bool InitiativePrecedes(const Initiative& A, const Initiative& B)
{
    if (A.Speed != B.Speed) return A.Speed > B.Speed;
    if (A.Priority != B.Priority) return A.Priority > B.Priority;
    // Total ordering even in the extremely rare hash collision; never rely on sort stability.
    if (A.Actor != B.Actor) return A.Actor < B.Actor;
    return A.Team < B.Team;
}
template <typename BattleId>
bool IsCurrentDecision(const BattleId& CurrentBattle, int CurrentTurn, const BattleId& ExpectedBattle, int ExpectedTurn)
{
    return CurrentTurn > 0 && ExpectedTurn == CurrentTurn && ExpectedBattle == CurrentBattle;
}
inline float TypeMultiplier(int AttackAffinity, int DefendAffinity)
{
    if (AttackAffinity < 1 || AttackAffinity > 3 || DefendAffinity < 1 || DefendAffinity > 3 || AttackAffinity == DefendAffinity) return 1.0f;
    return DefendAffinity == AttackAffinity % 3 + 1 ? 2.0f : 0.5f;
}
inline float ElementMultiplier(int MoveElement, int DefendElement)
{
    const bool Advantage = (MoveElement == 1 && DefendElement == 3) ||
        (MoveElement == 3 && DefendElement == 2) || (MoveElement == 2 && DefendElement == 1) ||
        (MoveElement == 4 && DefendElement == 5) || (MoveElement == 5 && DefendElement == 6) ||
        (MoveElement == 6 && DefendElement == 4) || (MoveElement == 7 && DefendElement == 8) ||
        (MoveElement == 8 && DefendElement == 7);
    return Advantage ? 1.5f : 1.0f;
}
inline float Effectiveness(int AttackAffinity, int DefendAffinity, int MoveElement, int DefendElement)
{
    return TypeMultiplier(AttackAffinity, DefendAffinity) * ElementMultiplier(MoveElement, DefendElement);
}
inline int SafeFloor(double Value)
{
    if (!std::isfinite(Value)) return 1;
    return static_cast<int>(std::floor(std::max(1.0, std::min(100000000.0, Value))));
}
inline float ComboMultiplier(int CAM, bool LivingAlly, float Roll)
{
    return LivingAlly && CAM >= 20 && Roll < static_cast<float>(std::clamp(CAM, 0, 100)) / 500.0f ? 1.25f : 1.0f;
}
inline int CalculateDamage(const Unit& Attacker, const Unit& Defender, const Move& Skill, float Variance, float Combo = 1.0f)
{
    const double Offense = std::max(0, Skill.DamageClass == 1 ? Attacker.Spirit : Attacker.Attack);
    const double Defense = std::max(0, Skill.DamageClass == 1 ? Defender.Spirit : Defender.Defense);
    const double Raw = 8.0 + 0.72 * Offense - 0.28 * Defense;
    const float Roll = std::isfinite(Variance) ? std::clamp(Variance, 0.92f, 1.08f) : 1.0f;
    const double PvE = std::isfinite(Attacker.DamageMultiplier) ? std::clamp(Attacker.DamageMultiplier, 0.0, 1.0) : 1.0;
    // Preserve the reference's ordering of integer truncations. Combining these
    // multipliers before one floor would add occasional points to guards/combos.
    int Hit = SafeFloor(Raw * (std::clamp(Skill.Power, 1, 300) / 100.0) *
        Effectiveness(Attacker.Affinity, Defender.Affinity, Skill.Element, Defender.Element) * Roll);
    Hit = SafeFloor(Hit * static_cast<double>(PvE));
    Hit = SafeFloor(Hit * static_cast<double>(std::clamp(Combo, 1.0f, 1.25f)));
    if (Defender.Guarding) Hit = std::max(1, Hit / 2);
    return Hit;
}
// Public Blueprint signature retained. Level no longer multiplies damage twice;
// level progression is already represented in the supplied ATK / DEF values.
inline int Damage(int Level, int Attack, int Defense, int Power, float Variance)
{
    (void)Level;
    Unit A, B; A.Attack = Attack; B.Defense = Defense;
    Move Skill; Skill.Power = Power;
    return CalculateDamage(A, B, Skill, Variance);
}
inline int ChooseMove(const Unit& Attacker, const Unit& Defender)
{
    const int BasicDamage = CalculateDamage(Attacker, Defender, Move{}, 1.0f);
    if (BasicDamage >= Defender.HP) return -1;
    int Best = -1, BestDamage = BasicDamage, BestCost = 0;
    for (int I = 0; I < std::min(4, static_cast<int>(Attacker.Moves.size())); ++I)
    {
        const Move& M = Attacker.Moves[I];
        if (M.SPCost < 0 || M.SPCost > Attacker.SP) continue;
        const int Hit = CalculateDamage(Attacker, Defender, M, 1.0f);
        if (Hit > BestDamage || (Hit == BestDamage && M.SPCost < BestCost))
        { Best = I; BestDamage = Hit; BestCost = M.SPCost; }
    }
    return Best;
}
inline double TargetScore(int Damage, int HP, int MaxHP)
{
    if (HP <= 0) return -1.0;
    return (Damage >= HP ? 2.0 : 0.0) + std::min(Damage, HP) / static_cast<double>(std::max(1, MaxHP));
}
struct Decision { int Target = -1, MoveIndex = -1, ExpectedDamage = 0; };
inline Decision ChooseAction(const Unit& Attacker, const std::vector<Unit>& Enemies, const std::vector<int>& Targets)
{
    Decision Best;
    double BestScore = -1.0;
    for (int I : Targets)
    {
        if (I < 0 || I >= static_cast<int>(Enemies.size()) || Enemies[I].HP <= 0) continue;
        const int MoveIndex = ChooseMove(Attacker, Enemies[I]);
        const Move Skill = MoveIndex >= 0 ? Attacker.Moves[MoveIndex] : Move{};
        const int Hit = CalculateDamage(Attacker, Enemies[I], Skill, 1.0f);
        const double Score = TargetScore(Hit, Enemies[I].HP, Enemies[I].MaxHP);
        if (Score > BestScore) { BestScore = Score; Best = {I, MoveIndex, Hit}; }
    }
    return Best;
}
inline int StageRank(int Stage)
{
    if (Stage >= 0 && Stage <= 6) return Stage;
    // Append-only UE enum: Armor and Hybrid retain Champion growth.
    return Stage == 9 || Stage == 10 ? 3 : 2;
}
// Legacy scale is used only when translating old saved vitals, never for combat.
inline int ScaledStat(int Value, int Level)
{
    return std::max(1, static_cast<int>(std::round(std::min(100000000.0,
        std::max(1, Value) * (1.0 + (std::clamp(Level, 1, 200) - 1) * 0.035)))));
}
inline int Stat(int Base, int Level, int Rank, int ABI, int Training, int StatIndex)
{
    Rank = std::clamp(Rank, 0, 6);
    const double Growth[] = {18.0 + 2.0 * Rank, 2.0, 3.0 + 0.3 * Rank, 2.5 + 0.3 * Rank, 3.0 + 0.3 * Rank, 2.0 + 0.2 * Rank};
    const double Natural = (std::max(1, Base) + (std::clamp(Level, 1, 200) - 1) * Growth[std::clamp(StatIndex, 0, 5)]) * (1.0 + std::clamp(ABI, 0, 200) / 1000.0);
    return SafeFloor(std::floor(std::max(1.0, Natural)) + static_cast<double>(std::max(0, Training)));
}
inline int LegacyBase(int Stage, int StatIndex)
{
    constexpr int Bases[6][6] = {{55,24,8,8,8,10}, {70,28,11,11,11,13}, {100,40,20,18,18,20},
        {145,55,30,28,27,28}, {205,72,43,40,39,38}, {275,92,58,54,53,50}};
    const int Rank = Stage >= 0 && Stage < 6 ? Stage : (Stage == 6 || Stage == 7 ? 5 : 2);
    return Bases[Rank][std::clamp(StatIndex, 0, 5)];
}
inline int MigrateVital(int Current, int PreviousMaximum, int NewMaximum, bool PreserveLiving)
{
    if (Current <= 0 || NewMaximum <= 0) return 0;
    const int64_t OldMax = std::max(1, PreviousMaximum);
    const int64_t Clamped = std::clamp(Current, 0, static_cast<int>(OldMax));
    // Integer half-up avoids ratio-first floating point turning an exact .5 into
    // .4999999999. Products of two positive int32 maxima fit safely in int64.
    const int64_t Rounded = (Clamped * static_cast<int64_t>(NewMaximum) + OldMax / 2) / OldMax;
    return std::clamp(static_cast<int>(Rounded), PreserveLiving ? 1 : 0, NewMaximum);
}
inline std::vector<int> Active(const std::vector<Unit>& Team, int Count)
{
    std::vector<int> Out;
    for (int i=0; i<static_cast<int>(Team.size()) && static_cast<int>(Out.size())<Count; ++i)
        if (Team[i].HP > 0) Out.push_back(i);
    return Out;
}
inline Result Resolve(std::vector<Unit> A, std::vector<Unit> B, int ActiveSize, uint32_t Seed, int MaxRounds = 200, bool CaptureCompleteEvents = false)
{
    Result R; R.A=std::move(A); R.B=std::move(B);
    ActiveSize = std::clamp(ActiveSize, 1, 6);
    const int MaxActions = std::clamp(MaxRounds, 1, 1000) * ActiveSize * 2;
    const uint32_t InitiativeSeed = Seed;
    auto Random = [&Seed]() -> uint32_t { Seed = Seed * 1664525u + 1013904223u; return Seed; };
    for (auto* Team : {&R.A, &R.B})
        for (auto& U : *Team) { U.HP=std::clamp(U.HP,0,std::max(1,U.MaxHP)); U.SP=std::clamp(U.SP,0,std::max(0,U.MaxSP)); }
    namespace Timeline = DigimonVenomNXTTimelineCore;
    std::vector<Timeline::Entry> Queue;
    std::vector<bool> EnteredA(R.A.size(), false), EnteredB(R.B.size(), false);
    auto Admit = [&](int Team, double Clock, bool Initial)
    {
        auto& Units = Team == 0 ? R.A : R.B;
        auto& Entered = Team == 0 ? EnteredA : EnteredB;
        for (int I : Active(Units, ActiveSize)) if (!Entered[I])
        {
            Entered[I] = true;
            Queue.push_back(Initial ? Timeline::MakeInitialEntry(InitiativeSeed, Team, I, Units[I].Speed) :
                Timeline::MakeDelayedEntry(InitiativeSeed, Team, I, Units[I].Speed, Clock));
        }
    };
    Admit(0, 0.0, true); Admit(1, 0.0, true);
    for (int Action = 1; Action <= MaxActions; ++Action)
    {
        if (Active(R.A,1).empty() || Active(R.B,1).empty()) break;
        Queue.erase(std::remove_if(Queue.begin(), Queue.end(), [&](const Timeline::Entry& E)
            { return (E.Team == 0 ? R.A : R.B)[E.Actor].HP <= 0; }), Queue.end());
        const int Next = Timeline::SelectNext(Queue);
        if (Next < 0) break;
        Timeline::Entry Turn = Queue[Next];
        Queue.erase(Queue.begin() + Next);
        auto& Allies = Turn.Team == 0 ? R.A : R.B;
        auto& Enemies = Turn.Team == 0 ? R.B : R.A;
        auto& Attacker = Allies[Turn.Actor];
        Attacker.Guarding = false;
        const auto Targets = Active(Enemies, ActiveSize);
        if (Targets.empty()) break;
        const Decision Choice = ChooseAction(Attacker, Enemies, Targets);
        const int Target = Choice.Target;
        if (Target < 0) break;
        auto& Defender = Enemies[Target];
        const int MoveIndex = Choice.MoveIndex;
        const Move Skill = MoveIndex >= 0 ? Attacker.Moves[MoveIndex] : Move{};
        Attacker.SP -= Skill.SPCost;
        const float Variance = 0.92f + static_cast<float>(Random() % 1601u) / 10000.0f;
        // Common-engine PvE enemies do not earn player CAM combos. Ranked and
        // friendly snapshots use the unmodified multiplier and remain symmetric.
        const float Combo = Attacker.DamageMultiplier < 1.0 ? 1.0f :
            ComboMultiplier(Attacker.CAM, Active(Allies, ActiveSize).size() > 1, static_cast<float>(Random() % 10000u) / 10000.0f);
        const int Hit = std::min(Defender.HP, CalculateDamage(Attacker, Defender, Skill, Variance, Combo));
        Defender.HP = std::max(0, Defender.HP - Hit);
        R.Rounds = Action; // A CTB turn is one action opportunity, including extra turns earned by SPD.
        if (CaptureCompleteEvents || R.Events.size() < 80)
            R.Events.push_back({Turn.Team,Turn.Actor,Target,Hit,MoveIndex,Action,Attacker.SP,Defender.HP,
                Effectiveness(Attacker.Affinity, Defender.Affinity, Skill.Element, Defender.Element),
                TypeMultiplier(Attacker.Affinity, Defender.Affinity), ElementMultiplier(Skill.Element, Defender.Element),
                Skill.DamageClass, Skill.Element, Turn.NextAt, Combo, Defender.Guarding});
        const double Clock = Turn.NextAt;
        Timeline::Reschedule(Turn, Clock, Attacker.Speed);
        Queue.push_back(Turn);
        Admit(0, Clock, false); Admit(1, Clock, false);
    }
    const bool ADead=Active(R.A,1).empty(), BDead=Active(R.B,1).empty();
    R.Draw=ADead==BDead;
    R.TeamAWon=!ADead && BDead;
    return R;
}
}
