#pragma once
// The single cumulative experience curve used by humans, rivals and progression UI.
// No engine dependencies: the native regression suite executes these exact rules.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>

namespace DigimonVenomNXTProgressionCore
{
inline int MaximumLevel(int ConfiguredMaximum) { return std::max(1, std::min(200, ConfiguredMaximum)); }
inline int ClampLevel(int Level, int MaxLevel) { return std::max(1, std::min(Level, MaximumLevel(MaxLevel))); }

inline std::int64_t ExperienceToNextLevel(int Level)
{
    // Venom v1.5: xp_required(level) = 35 + int(12 * level ** 1.45).
    return 35 + static_cast<std::int64_t>(12.0 * std::pow(ClampLevel(Level, 200), 1.45));
}

inline const std::array<std::int64_t, 201>& ExperienceThresholds()
{
    // The UE save representation is cumulative; summing the source's per-level
    // curve keeps its exact pacing without rewriting every XP consumer.
    static const std::array<std::int64_t, 201> Values = []
    {
        std::array<std::int64_t, 201> Result{};
        for (int Level = 1; Level <= 200; ++Level)
            Result[Level] = Result[Level - 1] + ExperienceToNextLevel(Level);
        return Result;
    }();
    return Values;
}

inline std::int64_t ExperienceFloor(int Level) { return ExperienceThresholds()[ClampLevel(Level, 200) - 1]; }
inline std::int64_t NextLevelXP(int Level) { return ExperienceThresholds()[ClampLevel(Level, 200)]; }

inline std::int64_t AddSaturated(std::int64_t Value, std::int64_t Amount)
{
    Value = std::max<std::int64_t>(0, Value);
    Amount = std::max<std::int64_t>(0, Amount);
    return Value + std::min(Amount, std::numeric_limits<std::int64_t>::max() - Value);
}

struct Progress
{
    int Level = 1;
    std::int64_t IntoLevel = 0;
    std::int64_t LevelSpan = 47;
    std::int64_t Remaining = 47;
    std::int64_t NextLevelFloor = 47;
    double Fraction = 0.0;
    bool AtCap = false;
};

inline Progress GetProgress(int Level, std::int64_t Experience, int MaxLevel)
{
    Progress Result;
    Result.Level = ClampLevel(Level, MaxLevel);
    // Older saves sometimes contain a granted level with no matching starting XP.
    // Preserve that earned level instead of making the next award pay for it twice.
    Experience = std::max(Experience, ExperienceFloor(Result.Level));
    while (Result.Level < MaximumLevel(MaxLevel) && Experience >= NextLevelXP(Result.Level)) ++Result.Level;
    Result.AtCap = Result.Level >= MaximumLevel(MaxLevel);
    if (Result.AtCap)
    {
        Result.IntoLevel = Result.LevelSpan = Result.Remaining = 0;
        Result.NextLevelFloor = ExperienceFloor(Result.Level);
        Result.Fraction = 1.0;
        return Result;
    }
    Result.NextLevelFloor = NextLevelXP(Result.Level);
    Result.LevelSpan = Result.NextLevelFloor - ExperienceFloor(Result.Level);
    Result.IntoLevel = Experience - ExperienceFloor(Result.Level);
    Result.Remaining = Result.NextLevelFloor - Experience;
    Result.Fraction = static_cast<double>(Result.IntoLevel) / static_cast<double>(Result.LevelSpan);
    return Result;
}

struct Award
{
    int PreviousLevel = 1;
    int Level = 1;
    int LevelsGained = 0;
    std::int64_t Experience = 0;
    std::int64_t GrantedExperience = 0;
    bool Changed = false;
};

inline Award CalculateAward(int Level, std::int64_t Experience, std::int64_t Amount, int MaxLevel)
{
    Award Result;
    Result.PreviousLevel = ClampLevel(Level, MaxLevel);
    const std::int64_t CorrectedXP = std::max(Experience, ExperienceFloor(Result.PreviousLevel));
    const int ReconciledLevel = GetProgress(Result.PreviousLevel, CorrectedXP, MaxLevel).Level;
    // Source saves clear within-level XP at the cap. Keep only the cumulative
    // floor there, so a later cap change cannot cash in banked excess awards.
    const std::int64_t CapFloor = ExperienceFloor(MaximumLevel(MaxLevel));
    Result.Experience = ReconciledLevel < MaximumLevel(MaxLevel) ?
        std::min(CapFloor, AddSaturated(CorrectedXP, Amount)) : CapFloor;
    Result.GrantedExperience = std::max<std::int64_t>(0, Result.Experience - CorrectedXP);
    Result.Level = GetProgress(Result.PreviousLevel, Result.Experience, MaxLevel).Level;
    Result.LevelsGained = Result.Level - Result.PreviousLevel;
    Result.Changed = Result.Level != Level || Result.Experience != Experience;
    return Result;
}

// A zero grant repairs stale persisted level/XP safely. Recovery runs only for
// genuinely crossed levels, so repeated login and UI refresh cannot heal a party.
template <typename Partner, typename GetStats>
Award Apply(Partner& Value, std::int64_t Amount, int MaxLevel, GetStats StatsFor)
{
    const Award Result = CalculateAward(Value.Level, Value.Experience, Amount, MaxLevel);
    Value.Experience = Result.Experience;
    Value.Level = Result.PreviousLevel;
    if (Value.Level < Result.Level)
    {
        const auto PreviousStats = StatsFor(Value);
        Value.Level = Result.Level;
        const auto Stats = StatsFor(Value);
        // Levelling restores only the increase in maxima. It never revives a
        // defeated partner or turns repeated XP grants into free recovery.
        if (Value.CurrentHP > 0)
            Value.CurrentHP = static_cast<int>(std::min<std::int64_t>(Stats.MaxHP,
                AddSaturated(Value.CurrentHP, std::max(0, Stats.MaxHP - PreviousStats.MaxHP))));
        Value.CurrentSP = static_cast<int>(std::min<std::int64_t>(Stats.MaxSP,
            AddSaturated(Value.CurrentSP, std::max(0, Stats.MaxSP - PreviousStats.MaxSP))));
    }
    if (Result.Changed)
    {
        const auto Stats = StatsFor(Value);
        Value.CurrentHP = std::max(0, std::min(Value.CurrentHP, Stats.MaxHP));
        Value.CurrentSP = std::max(0, std::min(Value.CurrentSP, Stats.MaxSP));
    }
    return Result;
}
}
