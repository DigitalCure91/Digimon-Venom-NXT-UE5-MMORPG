#pragma once

#include "DigimonVenomNXTRivalRules.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <vector>

/** Deterministic, engine-independent expedition planning. The live subsystem and
 * native regression tests execute these same decisions. No ownership/XP is created. */
namespace DigimonVenomNXTRivalTrainingCore
{
    struct Candidate
    {
        int Index = -1;
        int Level = 1;
        std::int64_t LastLedSession = 0;
        int HabitatPopulation = 0;
    };

    struct Habitat
    {
        int Id = 0;
        int MinLevel = 1;
        int MaxLevel = 1;
        int Population = 0;
    };

    inline std::uint32_t TieBreak(int Index, std::uint32_t Seed)
    {
        std::uint32_t Value = static_cast<std::uint32_t>(Index) ^ Seed;
        Value ^= Value >> 16; Value *= 0x7feb352dU;
        Value ^= Value >> 15; Value *= 0x846ca68bU;
        return Value ^ (Value >> 16);
    }

    /** Least-recently-led first: no permanent strongest leader. New ownership has
     * age zero; old save migrations distribute equal-age leaders by habitat demand
     * and a stable per-tamer tie, rather than moving every bot to one cohort. */
    inline int ChooseLeader(const std::vector<Candidate>& Candidates, std::uint32_t Seed)
    {
        const Candidate* Best = nullptr;
        for (const Candidate& Value : Candidates)
        {
            if (!Best || Value.LastLedSession < Best->LastLedSession ||
                (Value.LastLedSession == Best->LastLedSession &&
                    (Value.HabitatPopulation < Best->HabitatPopulation ||
                    (Value.HabitatPopulation == Best->HabitatPopulation &&
                        TieBreak(Value.Index, Seed) < TieBreak(Best->Index, Seed))))) Best = &Value;
        }
        return Best ? Best->Index : -1;
    }

    /** The training leader remains first. Only partners in the same level cohort
     * are selected; an incomplete party is preferable to a level-100 carry that
     * makes newly materialized partners permanently irrelevant in the field. */
    inline std::vector<int> BuildParty(const std::vector<Candidate>& Candidates, int LeaderIndex,
        int PartyLimit, int LevelSpan, std::uint32_t Seed)
    {
        std::vector<int> Result;
        const auto Leader = std::find_if(Candidates.begin(), Candidates.end(),
            [LeaderIndex](const Candidate& Value) { return Value.Index == LeaderIndex; });
        if (Leader == Candidates.end()) return Result;
        const std::int64_t Anchor = std::max(1, Leader->Level);
        const int Span = std::max(0, std::min(30, LevelSpan));
        std::vector<Candidate> Cohort;
        for (const Candidate& Value : Candidates)
            if (Value.Index != LeaderIndex && std::abs(static_cast<std::int64_t>(Value.Level) - Anchor) <= Span)
                Cohort.push_back(Value);
        std::sort(Cohort.begin(), Cohort.end(), [Anchor, Seed](const Candidate& A, const Candidate& B)
        {
            const auto ADistance = std::abs(static_cast<std::int64_t>(A.Level) - Anchor);
            const auto BDistance = std::abs(static_cast<std::int64_t>(B.Level) - Anchor);
            if (ADistance != BDistance) return ADistance < BDistance;
            if (A.LastLedSession != B.LastLedSession) return A.LastLedSession < B.LastLedSession;
            return TieBreak(A.Index, Seed) < TieBreak(B.Index, Seed);
        });
        Result.push_back(LeaderIndex);
        for (const Candidate& Value : Cohort)
        {
            if (static_cast<int>(Result.size()) >= std::max(1, std::min(12, PartyLimit))) break;
            Result.push_back(Value.Index);
        }
        return Result;
    }

    /** Compare population after removing the traveller from its current habitat.
     * A tie keeps the current map: moving only improves imbalance by at least two
     * and cannot oscillate two equally populated maps on every simulation action. */
    inline int ChooseHabitat(const std::vector<Habitat>& Habitats, int DesiredLevel,
        int CurrentMap, std::uint32_t Seed)
    {
        bool HasSuitable = false;
        std::int64_t BestDistance = std::numeric_limits<std::int64_t>::max();
        for (const Habitat& Map : Habitats)
        {
            HasSuitable |= DigimonVenomNXTRivalRules::IsSuitableMap(Map.MinLevel, Map.MaxLevel, DesiredLevel);
            BestDistance = std::min(BestDistance, DigimonVenomNXTRivalRules::MapDistance(Map.MinLevel, Map.MaxLevel, DesiredLevel));
        }
        const Habitat* Best = nullptr;
        int BestPopulation = std::numeric_limits<int>::max();
        for (const Habitat& Map : Habitats)
        {
            if (HasSuitable ? !DigimonVenomNXTRivalRules::IsSuitableMap(Map.MinLevel, Map.MaxLevel, DesiredLevel) :
                DigimonVenomNXTRivalRules::MapDistance(Map.MinLevel, Map.MaxLevel, DesiredLevel) != BestDistance) continue;
            const int Population = std::max(0, Map.Population - (Map.Id == CurrentMap ? 1 : 0));
            if (!Best || Population < BestPopulation || (Population == BestPopulation &&
                (Map.Id == CurrentMap || (Best->Id != CurrentMap && TieBreak(Map.Id, Seed) < TieBreak(Best->Id, Seed)))))
            { Best = &Map; BestPopulation = Population; }
        }
        return Best ? Best->Id : CurrentMap;
    }

    inline bool SessionFinished(int Battles, int BattlesPerParty, int StartLevel, int LeaderLevel)
    {
        return Battles >= std::max(1, std::min(100, BattlesPerParty)) ||
            (Battles > 0 && static_cast<std::int64_t>(LeaderLevel) >= static_cast<std::int64_t>(StartLevel) + 6);
    }
}
