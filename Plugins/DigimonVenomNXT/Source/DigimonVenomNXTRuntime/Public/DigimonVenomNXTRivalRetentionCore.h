#pragma once

// Engine-independent storage policy used by runtime retention and executable regression checks.
#include <algorithm>

namespace DigimonVenomNXTRivalRetentionCore
{
    constexpr int MaxOwnedPerRival = 64;
    constexpr int MaxScansPerRival = 256;
    constexpr int GlobalOwnedBudget = 64000;
    constexpr int GlobalScanBudget = 128000;

    inline int CollectionLimit(int Configured, int ConfiguredPartySize = 6, int Population = 1000)
    {
        const int PartySlots = std::clamp(ConfiguredPartySize, 1, 12);
        const int SharedLimit = std::max(6, GlobalOwnedBudget / std::max(1, Population));
        return std::max(PartySlots, std::min(std::clamp(Configured, 6, MaxOwnedPerRival), SharedLimit));
    }

    inline int ScanLimit(int Configured, int Population = 1000)
    {
        const int SharedLimit = std::max(16, GlobalScanBudget / std::max(1, Population));
        return std::min(std::clamp(Configured, 16, MaxScansPerRival), SharedLimit);
    }
}
