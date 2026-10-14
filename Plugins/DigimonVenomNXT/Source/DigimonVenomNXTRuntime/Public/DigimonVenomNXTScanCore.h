#pragma once

// Engine-independent rules shared by the authoritative player/bot paths and DigiDex previews.
#include <algorithm>
#include <cstdint>
#include <utility>

namespace DigimonVenomNXTScanCore
{
inline int Cap(int ConfiguredCap) { return std::clamp(ConfiguredCap, 100, 999); }
inline int Requirement(int ConfiguredRequirement, int ConfiguredCap)
{
    return std::clamp(ConfiguredRequirement, 1, Cap(ConfiguredCap));
}
inline int Percent(int Current, int ConfiguredCap) { return std::clamp(Current, 0, Cap(ConfiguredCap)); }
inline int Gain(int Current, std::int64_t Amount, int ConfiguredCap)
{
    const int Existing = Percent(Current, ConfiguredCap);
    const int Available = Cap(ConfiguredCap) - Existing;
    return Existing + static_cast<int>(std::clamp<std::int64_t>(Amount, 0, Available));
}
inline bool IsVariantAvailable(int Variant, bool Normal, bool Paradox, bool Shiny, bool Firewall = false)
{
    return Variant == 0 ? Normal : Variant == 1 ? Paradox : Variant == 2 ? Shiny : Variant == 3 ? Firewall : false;
}
inline int BonusABI(int ScanPercent)
{
    // Original Digidex rule: each complete 20% above 100% gives 1 permanent ABI, capped at 5.
    return (std::clamp(ScanPercent, 100, 200) - 100) / 20;
}
struct Materialization
{
    bool Ready = false;
    int ScanPercent = 0, Requirement = 100, Cap = 200, BonusABI = 0, RemainingPercent = 0;
};
inline Materialization Materialize(int Current, int ConfiguredRequirement, int ConfiguredCap, bool ConsumeScan)
{
    Materialization Result;
    Result.Cap = Cap(ConfiguredCap);
    Result.Requirement = Requirement(ConfiguredRequirement, ConfiguredCap);
    Result.ScanPercent = Percent(Current, ConfiguredCap);
    Result.Ready = Result.ScanPercent >= Result.Requirement;
    Result.BonusABI = Result.Ready ? BonusABI(Result.ScanPercent) : 0;
    // One conversion spends the entire accumulated scan, including the portion that earned ABI.
    // Explicit non-consuming administrator mode retains scan and allows repeated conversions.
    Result.RemainingPercent = Result.Ready && ConsumeScan ? 0 : Result.ScanPercent;
    return Result;
}
template <typename Record>
bool Observe(Record& Scan, int ConfiguredCap, bool Owned = false)
{
    const int Current = Percent(Scan.Percent, ConfiguredCap);
    const int Fraction = Current >= Cap(ConfiguredCap) || Scan.Percent < 0 ? 0 : std::clamp(Scan.FractionalHundredths, 0, 99);
    const int Peak = std::max(Current, std::max(0, Scan.PeakPercent));
    const int Count = std::max(0, Scan.Materializations);
    const bool EverOwned = Scan.bEverOwned || Owned || Count > 0;
    const bool Changed = Current != Scan.Percent || Fraction != Scan.FractionalHundredths || Peak != Scan.PeakPercent ||
        Count != Scan.Materializations || EverOwned != Scan.bEverOwned;
    Scan.Percent = Current;
    Scan.FractionalHundredths = Fraction;
    Scan.PeakPercent = Peak;
    Scan.Materializations = Count;
    Scan.bEverOwned = EverOwned;
    return Changed;
}
template <typename Profile, typename Mutate, typename Save>
bool Commit(Profile& State, Mutate&& Mutation, Save&& Persist)
{
    Profile Before = State;
    Mutation(State);
    if (Persist(State)) return true;
    State = std::move(Before);
    return false;
}
}
