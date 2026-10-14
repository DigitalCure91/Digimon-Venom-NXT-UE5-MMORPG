#pragma once
#include "DigimonVenomNXTVariantCore.h"
#include <algorithm>
#include <limits>
#include <string_view>

/** Stable campaign context identities and mutually exclusive wild-scan rewards. */
namespace DigimonVenomNXTCampaignCore
{
    constexpr int CampaignCount = 3;
    constexpr bool ValidCampaign(int Campaign) { return Campaign >= 0 && Campaign < CampaignCount; }
    constexpr std::string_view ContextPrefix(int Campaign)
    {
        return Campaign == 0 ? "relay:" : Campaign == 1 ? "chronicles:" : Campaign == 2 ? "ghostline:" : "";
    }
    /** Only an exact, lower-case campaign prefix followed by a nonempty payload is valid. */
    inline int ContextCampaign(std::string_view Context)
    {
        for (int Campaign = 0; Campaign < CampaignCount; ++Campaign)
        {
            const auto Prefix = ContextPrefix(Campaign);
            if (Context.size() > Prefix.size() && Context.substr(0, Prefix.size()) == Prefix) return Campaign;
        }
        return -1;
    }
    inline int ScanGain(int Base, int Variant, bool ShinyMastery, bool ParadoxMastery,
        bool FirewallMastery, bool WildVictory)
    {
        if (!WildVictory) return std::max(0, Base);
        if ((Variant == 2 && ShinyMastery) || (Variant == 1 && ParadoxMastery) ||
            (Variant == 3 && FirewallMastery)) {
        const long long Nonnegative = std::max(0, Base);
        return static_cast<int>(std::min<long long>(std::numeric_limits<int>::max(), Nonnegative + (Nonnegative + 4) / 5));
    }
        return DigimonVenomNXTVariantCore::WildScanGain(Variant, Base);
    }
}
