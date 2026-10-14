#pragma once
#include <algorithm>
#include <limits>

/** Shared pure rules used by live progression and portable regression tests. */
namespace DigimonVenomNXTChroniclesCore
{
constexpr int FirstField = 2;
constexpr int LastField = 18;
constexpr int CrestCount = 17;
template<typename HasCrest> bool CanEnter(int MapId, HasCrest Has)
{
    if (MapId < 1 || MapId > LastField) return false;
    for (int Field = FirstField; Field < MapId; ++Field) if (!Has(Field)) return false;
    return true;
}
template<typename ClearedGuardian, typename HasCrest> bool CanSummon(ClearedGuardian Cleared, HasCrest Has)
{
    for (int Field = FirstField; Field <= LastField; ++Field) if (!Cleared(Field) || !Has(Field)) return false;
    return true;
}
inline bool CanTurnIn(bool Accepted, int ObjectiveCount, int Target)
{
    return Accepted && Target > 0 && ObjectiveCount >= Target;
}
inline int ScanGain(int Base, bool Shiny, bool Paradox, bool RelayMastery, bool ChroniclesMastery, bool WildVictory)
{
    if (WildVictory && ((Shiny && RelayMastery) || (Paradox && ChroniclesMastery))) {
        const long long Nonnegative = std::max(0, Base);
        return static_cast<int>(std::min<long long>(std::numeric_limits<int>::max(), Nonnegative + (Nonnegative + 4) / 5));
    }
    return std::max(0, Base);
}
}
