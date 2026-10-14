#pragma once
// Server battle-context policy. Numeric kinds mirror the explicitly asserted UE enum below.
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace DigimonVenomNXTBattlePolicyCore
{
inline bool UsesSourcePlayerFormation(int Kind, bool Automatic)
{
    // Human-controlled wild, Season and authored story use manual reserve swaps.
    // Rival simulations, ranked playback and live friendly matches retain their own formation rules.
    return !Automatic && (Kind == 0 || Kind == 2 || Kind == 4);
}
inline bool MayFlee(int Kind, int Team, bool Finished, bool Automatic, bool HasSecondPlayer)
{
    return Kind == 0 && Team == 0 && !Finished && !Automatic && !HasSecondPlayer;
}
inline double EnemyDamageMultiplier(int Kind, int Team, bool HasSecondPlayer)
{
    return Team == 1 && !HasSecondPlayer && (Kind == 0 || Kind == 1 || Kind == 2 || Kind == 4) ? 0.72 : 1.0;
}
inline int WildMaxHP(int FullMaxHP, bool PrivateTraining = false)
{
    return std::max(20, static_cast<int>(std::floor(std::max(1, FullMaxHP) * (PrivateTraining ? 0.60 : 0.72))));
}
inline int TrainerVictoryCredits(int ActionCount, int InitialActiveCount)
{
    const int64_t Actions = std::max(1, ActionCount);
    const int64_t Slots = std::max(1, InitialActiveCount);
    const int64_t RoundEquivalent = (Actions + Slots - 1) / Slots;
    return 150 + 10 * static_cast<int>(std::clamp<int64_t>(RoundEquivalent, 1, 20));
}
}
