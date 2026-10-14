#pragma once

// Engine-independent, shared by server wild encounters and the persistent AI simulation.
// IDs mirror EDigimonVariant and must remain stable for existing account/battle saves.
#include <algorithm>
#include <cmath>

namespace DigimonVenomNXTVariantCore
{
constexpr int Normal = 0;
constexpr int Paradox = 1;
constexpr int Shiny = 2;
constexpr int Firewall = 3;
constexpr int FirewallVictoryScan = 5;

struct WildRates
{
    double ShinyChance = 0.0;
    double ParadoxChance = 0.0;
    double FirewallChance = 0.0;
};

inline double SafeProbability(double Value)
{
    return std::isfinite(Value) ? std::clamp(Value, 0.0, 1.0) : 0.0;
}

inline WildRates EffectiveWildRates(double ShinyChance, double ParadoxChance, double FirewallChance)
{
    WildRates Rates{SafeProbability(ShinyChance), SafeProbability(ParadoxChance), SafeProbability(FirewallChance)};
    const double Total = Rates.ShinyChance + Rates.ParadoxChance + Rates.FirewallChance;
    // One categorical roll avoids a later variety being suppressed by an earlier roll.
    // Malformed settings cannot create NaNs or silently give one rare variety priority.
    if (Total > 1.0)
    {
        Rates.ShinyChance /= Total;
        Rates.ParadoxChance /= Total;
        Rates.FirewallChance /= Total;
    }
    return Rates;
}

inline int RollWildVariant(double UnitRoll, double ShinyChance, double ParadoxChance, double FirewallChance)
{
    // FMath::FRand / FRandomStream::FRand supply [0, 1). Reject invalid custom inputs.
    if (!std::isfinite(UnitRoll) || UnitRoll < 0.0 || UnitRoll >= 1.0) return Normal;
    const WildRates Rates = EffectiveWildRates(ShinyChance, ParadoxChance, FirewallChance);
    if (UnitRoll < Rates.ShinyChance) return Shiny;
    if (UnitRoll < Rates.ShinyChance + Rates.ParadoxChance) return Paradox;
    if (UnitRoll < Rates.ShinyChance + Rates.ParadoxChance + Rates.FirewallChance) return Firewall;
    return Normal;
}

inline int WildScanGain(int Variant, int ConfiguredBase)
{
    // Callers choose the normal or rare configured base before permanent mastery.
    (void)Variant;
    return std::max(0, ConfiguredBase);
}
}
