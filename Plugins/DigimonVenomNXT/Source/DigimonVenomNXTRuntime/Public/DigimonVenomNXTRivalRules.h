#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include "DigimonVenomNXTProgressionCore.h"

/** Engine-independent rival progression/window rules, executed by the native test harness. */
namespace DigimonVenomNXTRivalRules
{
    constexpr std::int64_t ActivityWindowSeconds = 43200;

    inline std::int64_t WindowStart(std::int64_t Now)
    {
        return (Now < 0 ? 0 : Now / ActivityWindowSeconds) * ActivityWindowSeconds;
    }

    inline std::int64_t NextLevelXP(int Level)
    {
        return DigimonVenomNXTProgressionCore::NextLevelXP(Level);
    }

    /** Judge a habitat by its strongest possible encounter, not its weakest one.
        Invalid/inverted ranges must never hide a higher minimum encounter level. */
    inline int MapEncounterCeiling(int MinLevel, int MaxLevel)
    {
        return std::max(1, std::max(MinLevel, MaxLevel));
    }

    /** Lower is better. Every safe ceiling ranks before every unsafe ceiling, even
        when the safe habitat is much easier. If none is safe, choose the lowest
        encounter ceiling available. Include the current map when finding this
        fallback; exclude it only from the random alternative destination list. */
    inline std::int64_t MapDistance(int MinLevel, int MaxLevel, int DesiredLevel)
    {
        const std::int64_t Target = std::max(1, DesiredLevel);
        const std::int64_t Ceiling = MapEncounterCeiling(MinLevel, MaxLevel);
        if (Ceiling <= Target) return Target - Ceiling;
        constexpr std::int64_t UnsafePenalty = static_cast<std::int64_t>(std::numeric_limits<int>::max()) + 1;
        return UnsafePenalty + Ceiling - Target;
    }

    /** Random exploration stays within six levels of the training target and may
        never expose a rival to a wild encounter above that target. Easier habitats
        remain available through MapDistance when no suitable alternative exists. */
    inline bool IsSuitableMap(int MinLevel, int MaxLevel, int DesiredLevel)
    {
        const std::int64_t Target = std::max(1, DesiredLevel);
        const std::int64_t Ceiling = MapEncounterCeiling(MinLevel, MaxLevel);
        return Ceiling <= Target && Ceiling >= Target - 6;
    }

    /** Offline gaps produce one clear, never invented event totals. Clock rollback cannot
        clear a live interval. Only WindowStats changes; ownership and lifetime data survive. */
    template<class TTimestamp, class TRivals>
    bool RefreshWindow(TTimestamp Now, TTimestamp& Start, TRivals& Rivals)
    {
        const TTimestamp Next = static_cast<TTimestamp>(WindowStart(Now));
        if (Start > 0 && Next <= Start) return false;
        if (Start == 0 && Next == 0) return false;
        Start = Next;
        for (auto& Rival : Rivals) Rival.WindowStats = {};
        return true;
    }
}
