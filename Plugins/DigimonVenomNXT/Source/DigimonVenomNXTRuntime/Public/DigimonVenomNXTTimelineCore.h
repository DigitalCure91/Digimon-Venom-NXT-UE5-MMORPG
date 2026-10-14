#pragma once
// One continuous, speed-driven clock shared by interactive and automatic combat.
// Save NextAt and the battle clock as doubles; reconnect must not rebuild a round.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace DigimonVenomNXTTimelineCore
{
struct Entry
{
    int Team = 0, Actor = 0, Speed = 1;
    double NextAt = 0.0;
    uint32_t Priority = 0;
};
inline uint32_t MixPriority(uint32_t Value)
{
    Value ^= Value >> 16; Value *= 0x7feb352du;
    Value ^= Value >> 15; Value *= 0x846ca68bu;
    return Value ^ (Value >> 16);
}
inline uint32_t IdentityPriority(uint32_t Seed, int Team, int Actor)
{
    return MixPriority(Seed ^ (Team == 0 ? 0x243f6a88u : 0xb7e15162u) ^
        MixPriority(static_cast<uint32_t>(Actor)));
}
inline double InitialTime(int Speed) { return 500.0 / std::max(1, Speed); }
inline double NextTime(double Clock, int Speed)
{
    const double SafeClock = std::isfinite(Clock) ? std::max(0.0, Clock) : 0.0;
    return SafeClock + 1000.0 / std::max(1, Speed);
}
inline Entry MakeEntry(uint32_t Seed, int Team, int Actor, int Speed, double NextAt)
{
    return {Team, Actor, std::max(1, Speed), NextAt, IdentityPriority(Seed, Team, Actor)};
}
inline Entry MakeInitialEntry(uint32_t Seed, int Team, int Actor, int Speed)
{
    return MakeEntry(Seed, Team, Actor, Speed, InitialTime(Speed));
}
// An entering reserve waits a full action interval, including after a knockout.
inline Entry MakeDelayedEntry(uint32_t Seed, int Team, int Actor, int Speed, double Clock)
{
    return MakeEntry(Seed, Team, Actor, Speed, NextTime(Clock, Speed));
}
inline bool ValidEntry(const Entry& Value)
{
    return Value.Team >= 0 && Value.Team <= 1 && Value.Actor >= 0 && Value.Speed > 0 &&
        std::isfinite(Value.NextAt) && Value.NextAt >= 0.0;
}
inline bool EntryPrecedes(const Entry& A, const Entry& B)
{
    if (A.NextAt != B.NextAt) return A.NextAt < B.NextAt;
    if (A.Priority != B.Priority) return A.Priority > B.Priority;
    if (A.Actor != B.Actor) return A.Actor < B.Actor;
    return A.Team < B.Team;
}
inline int SelectNext(const std::vector<Entry>& Queue)
{
    int Best = -1;
    for (int Index = 0; Index < static_cast<int>(Queue.size()); ++Index)
        if (ValidEntry(Queue[Index]) && (Best < 0 || EntryPrecedes(Queue[Index], Queue[Best]))) Best = Index;
    return Best;
}
inline void Reschedule(Entry& Value, double Clock, int Speed)
{
    Value.Speed = std::max(1, Speed);
    Value.NextAt = NextTime(Clock, Value.Speed);
}
// Guard expires when this identity is selected for its next action opportunity,
// never when a different unit acts or a notional team round changes.
inline void BeginOpportunity(bool& Guarding) { Guarding = false; }
}
