#pragma once
#include <algorithm>
#include <limits>

/** Engine-independent championship invariants used by live settlement and migration. */
namespace DigimonVenomNXTRelayCore
{
inline int Increment(int Value) { return Value < std::numeric_limits<int>::max() ? std::max(0, Value) + 1 : Value; }
template<typename Progress> bool ReconcileMastery(Progress& P)
{
    const bool Earned = P.bEverChampion || P.bIsChampion || P.ChampionshipWins > 0;
    const bool Changed = Earned && (!P.bEverChampion || !P.bFirewallScanMastery);
    if (Earned) { P.bEverChampion = true; P.bFirewallScanMastery = true; }
    return Changed;
}
template<typename Progress> void TitleResult(Progress& P, bool Victory, bool FirstChampionship)
{
    // Source championship rotation advances its match counter for every result.
    // A lost title's exact holder is retained separately by campaign settlement.
    P.ChallengerIndex = Increment(P.ChallengerIndex);
    if (Victory)
    {
        if (!FirstChampionship && P.bIsChampion) P.Defenses = Increment(P.Defenses);
        else P.ChampionshipWins = Increment(P.ChampionshipWins);
        P.bIsChampion = true;
        P.bEverChampion = true;
        P.bFirewallScanMastery = true;
    }
    else if (!FirstChampionship && P.bIsChampion)
    {
        P.bIsChampion = false;
        P.TitleLosses = Increment(P.TitleLosses);
        // Mastery never changes after a championship loss.
    }
}
}
