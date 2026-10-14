#pragma once

// Shared by the authoritative Unreal adapters and the native regression suite.
// HP is canonical; bDefeated is presentation data derived from it.
#include <algorithm>
#include <utility>

namespace DigimonVenomNXTRecoveryCore
{
// Shared by field recovery, battle commands and shop/item previews.
inline constexpr int SmallHPCapsule = 250;
inline constexpr int SmallSPCapsule = 25;
struct Vitals { int HP = 0; int SP = 0; };

template <typename Units>
bool HasLivingUnit(const Units& Roster)
{
    for (const auto& Unit : Roster) if (Unit.HP > 0) return true;
    return false;
}

template <typename Team>
bool IsTeamDefeated(const Team& Value)
{
    return !HasLivingUnit(Value.Active) && !HasLivingUnit(Value.Bench);
}

template <typename Unit>
Vitals ResultVitals(const Unit& Value, bool Restore)
{
    const int MaxHP = std::max(1, Value.Stats.MaxHP);
    const int MaxSP = std::max(0, Value.Stats.MaxSP);
    return {Restore ? MaxHP : std::clamp(Value.HP, 0, MaxHP),
        Restore ? MaxSP : std::clamp(Value.SP, 0, MaxSP)};
}

template <typename Team>
bool PrepareTeam(Team& Value, bool PromoteReserves = true)
{
    bool Changed = false;
    auto Normalize = [&Changed](auto& Roster)
    {
        for (auto& Unit : Roster)
        {
            const Vitals Safe = ResultVitals(Unit, false);
            const bool Defeated = Safe.HP <= 0;
            Changed = Changed || Unit.HP != Safe.HP || Unit.SP != Safe.SP || Unit.bDefeated != Defeated;
            Unit.HP = Safe.HP; Unit.SP = Safe.SP; Unit.bDefeated = Defeated;
        }
    };
    Normalize(Value.Active);
    Normalize(Value.Bench);
    if (!PromoteReserves) return Changed;
    for (auto& Active : Value.Active)
    {
        if (Active.HP > 0) continue;
        for (auto& Reserve : Value.Bench)
        {
            if (Reserve.HP <= 0) continue;
            std::swap(Active, Reserve);
            Changed = true;
            break;
        }
    }
    return Changed;
}

// The caller resolves owned party IDs; absent/stale IDs never count as defeated
// partners. One surviving reserve keeps ordinary injuries intact for the DigiLab.
template <typename PartnerPointers, typename GetMaximums>
bool RestoreExhaustedParty(const PartnerPointers& Party, GetMaximums Maximums)
{
    bool FoundPartner = false;
    for (const auto* Partner : Party)
    {
        if (!Partner) continue;
        FoundPartner = true;
        if (Partner->CurrentHP > 0) return false;
    }
    if (!FoundPartner) return false;
    for (auto* Partner : Party)
    {
        if (!Partner) continue;
        const Vitals Limits = Maximums(*Partner);
        Partner->CurrentHP = std::max(1, Limits.HP);
        Partner->CurrentSP = std::max(0, Limits.SP);
    }
    return true;
}
}
