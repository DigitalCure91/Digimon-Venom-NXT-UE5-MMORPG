#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <string_view>

/** Authoritative encounter policy, shared by battle creation, checkpoint validation and native tests. */
namespace DigimonVenomNXTCampaignBattleCore
{
    constexpr int FinaleActiveSlots = 3;
    inline int ActiveSlots(int Configured, bool Season, bool Finale)
    {
        return Finale ? FinaleActiveSlots : std::clamp(Configured, 1, Season ? 3 : 6);
    }
    struct FinalUnit
    {
        std::string Species;
        int Level = 0;
        int Variant = 0;
        bool Mega = false;
    };
    inline bool ValidFinalRoster(int Campaign, int MapId, std::string_view NPCId,
        const std::array<FinalUnit, FinaleActiveSlots>& Units, int ActiveCount, int BenchCount)
    {
        if (ActiveCount != FinaleActiveSlots || BenchCount != 0) return false;
        if (Campaign != 1 && Campaign != 2) return false;
        const bool GhostLine = Campaign == 2;
        if (MapId != (GhostLine ? 31 : 18) ||
            NPCId != (GhostLine ? "ghost_final_regent" : "ds_final_triad")) return false;
        const std::array<std::string_view, FinaleActiveSlots> GhostSpecies = {
            "diaboromon", "chaosdramon", "machinedramon"};
        const std::array<std::string_view, FinaleActiveSlots> ParadoxSpecies = {
            "alphamon", "omnimon", "imperialdramonpaladinmode"};
        for (std::size_t I = 0; I < Units.size(); ++I)
        {
            const auto& Unit = Units[I];
            if (Unit.Species.empty() || !Unit.Mega || Unit.Level != (GhostLine ? 99 : 100) ||
                Unit.Variant != (GhostLine ? 0 : 1)) return false;
            for (std::size_t J = 0; J < I; ++J)
                if (Unit.Species == Units[J].Species) return false;
            const auto& Expected = GhostLine ? GhostSpecies : ParadoxSpecies;
            if (std::find(Expected.begin(), Expected.end(), Unit.Species) == Expected.end()) return false;
        }
        return true;
    }
}
