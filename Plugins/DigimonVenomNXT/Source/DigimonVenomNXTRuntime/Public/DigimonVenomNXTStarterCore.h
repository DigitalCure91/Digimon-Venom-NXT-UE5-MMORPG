#pragma once
// Shared starter rules. Materialization and evolution retain their level-one rules.
#include <algorithm>
#include <cstdint>
#include "DigimonVenomNXTProgressionCore.h"

namespace DigimonVenomNXTStarterCore
{
constexpr int BalanceVersion = 1;

inline int StartingLevel(int ConfiguredLevel, int MaximumLevel)
{
    return std::max(1, std::min(ConfiguredLevel, std::max(1, std::min(200, MaximumLevel))));
}

inline int64_t ExperienceFloor(int Level)
{
    return DigimonVenomNXTProgressionCore::ExperienceFloor(Level);
}

template <typename Partner, typename GetStats>
void InitializeLevel(Partner& Value, int Level, int MaximumLevel, GetStats StatsFor)
{
    Value.Level = StartingLevel(Level, MaximumLevel);
    Value.Experience = ExperienceFloor(Value.Level);
    const auto Stats = StatsFor(Value);
    Value.CurrentHP = Stats.MaxHP;
    Value.CurrentSP = Stats.MaxSP;
}

// The caller supplies only Collection[0], the append-only original starter.
// Positive ABI can indicate an evolved/devolved partner; never raise that reset.
// Returning true means the marker changed and must be persisted, even if no boost
// was appropriate. An in-progress battle defers both evaluation and mutation.
template <typename Partner, typename GetStats>
bool UpgradeLegacyStarter(Partner& Value, int& Version, int ConfiguredLevel,
    int MaximumLevel, bool EligibleOriginalSpecies, bool BattleActive, GetStats StatsFor)
{
    if (Version >= BalanceVersion || BattleActive) return false;
    Version = BalanceVersion;
    const int TargetLevel = StartingLevel(ConfiguredLevel, MaximumLevel);
    if (!EligibleOriginalSpecies || Value.ABI != 0 || Value.Level < 1 || Value.Level >= TargetLevel) return true;
    Value.Level = TargetLevel;
    Value.Experience = std::max<int64_t>(Value.Experience, ExperienceFloor(TargetLevel));
    const auto Stats = StatsFor(Value);
    Value.CurrentHP = Stats.MaxHP;
    Value.CurrentSP = Stats.MaxSP;
    return true;
}
}
