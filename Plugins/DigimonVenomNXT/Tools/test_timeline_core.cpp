#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTTimelineCore.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace DigimonVenomNXTTimelineCore;
int main()
{
    int Checks = 0;
    auto Require = [&Checks](bool Value, const char* Message)
    {
        ++Checks;
        if (!Value) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    };
    Require(InitialTime(100) == 5.0 && NextTime(5.0,100) == 15.0, "Reference initial and recurring time");
    Require(InitialTime(0) == 500.0 && InitialTime(-100) == 500.0, "Invalid speeds cannot divide by zero");
    Require(SelectNext({}) == -1, "Empty timeline has no actor");
    for (int SlowSpeed : {1,17,100,999})
    {
        std::vector<Entry> Queue{MakeInitialEntry(7,0,0,SlowSpeed*2),MakeInitialEntry(7,1,0,SlowSpeed)};
        int Counts[2] = {0,0};
        double Clock = 0.0;
        for (int Turn = 0; Turn < 60; ++Turn)
        {
            const int Selected = SelectNext(Queue);
            auto& Actor = Queue[Selected];
            Require(Actor.NextAt >= Clock, "Continuous clock never moves backwards");
            Clock = Actor.NextAt;
            ++Counts[Actor.Team];
            Reschedule(Actor,Clock,Actor.Speed);
        }
        Require(Counts[0] == 40 && Counts[1] == 20, "Twice the speed yields twice as many opportunities");
    }
    int First[2] = {0,0};
    for (uint32_t Seed = 0; Seed < 4096; ++Seed)
    {
        const auto A = MakeInitialEntry(Seed,0,0,100);
        const auto B = MakeInitialEntry(Seed,1,0,100);
        ++First[EntryPrecedes(A,B) ? 0 : 1];
        std::vector<Entry> Forward{A,B}, Reverse{B,A};
        Require(Forward[SelectNext(Forward)].Team == Reverse[SelectNext(Reverse)].Team,
            "Ties depend on battle seed and identity, never container or command order");
        auto LaterA = A, LaterB = B;
        Reschedule(LaterA,5.0,100); Reschedule(LaterB,5.0,100);
        Require(EntryPrecedes(A,B) == EntryPrecedes(LaterA,LaterB), "Equal-speed ties retain identity priority");
    }
    Require(First[0] > 1800 && First[0] < 2300 && First[1] > 1800 && First[1] < 2300,
        "Equal-speed seeded openings do not permanently favor either side");
    std::vector<Entry> Live{MakeInitialEntry(381,0,0,37),MakeInitialEntry(381,1,0,53),MakeInitialEntry(381,0,2,81)};
    double Clock = 0.0;
    for (int Turn = 0; Turn < 19; ++Turn)
    {
        auto& Actor = Live[SelectNext(Live)]; Clock = Actor.NextAt; Reschedule(Actor,Clock,Actor.Speed);
    }
    std::stringstream Saved;
    Saved << std::setprecision(std::numeric_limits<double>::max_digits10) << Clock << '\n';
    for (const auto& Actor : Live)
        Saved << Actor.Team << ' ' << Actor.Actor << ' ' << Actor.Speed << ' ' << Actor.NextAt << ' ' << Actor.Priority << '\n';
    std::vector<Entry> Restored(Live.size());
    double SavedClock = 0.0; Saved >> SavedClock;
    for (auto& Actor : Restored) Saved >> Actor.Team >> Actor.Actor >> Actor.Speed >> Actor.NextAt >> Actor.Priority;
    Require(Clock == SavedClock, "Clock round trips without resetting accumulated time");
    for (int Turn = 0; Turn < 100; ++Turn)
    {
        auto& Expected = Live[SelectNext(Live)]; auto& Actual = Restored[SelectNext(Restored)];
        Require(Expected.Team == Actual.Team && Expected.Actor == Actual.Actor && Expected.NextAt == Actual.NextAt,
            "Reconnect resumes the exact next hundred identities and times");
        Reschedule(Expected,Expected.NextAt,Expected.Speed); Reschedule(Actual,Actual.NextAt,Actual.Speed);
    }
    const auto Reserve = MakeDelayedEntry(9,1,5,100,123.5);
    Require(Reserve.Actor == 5 && Reserve.NextAt == 133.5, "Reserve keeps original roster identity and waits a full interval");
    Require(Reserve.NextAt > MakeEntry(9,0,1,100,125.0).NextAt, "Reserve cannot steal an existing queued action");
    bool Guarding = true;
    auto GuardQueue = std::vector<Entry>{MakeInitialEntry(9,0,0,100),MakeInitialEntry(9,1,0,300)};
    Reschedule(GuardQueue[0],5.0,100);
    for (int Turn = 0; Turn < 4; ++Turn)
    {
        auto& Actor = GuardQueue[SelectNext(GuardQueue)];
        Require(Actor.Team == 1 && Guarding, "Guard survives every enemy action before the owner is ready");
        Reschedule(Actor,Actor.NextAt,Actor.Speed);
    }
    BeginOpportunity(Guarding);
    Require(!Guarding, "Guard expires at its owner's next opportunity");
    auto Invalid = MakeInitialEntry(1,0,0,100); Invalid.NextAt = std::numeric_limits<double>::quiet_NaN();
    Require(!ValidEntry(Invalid) && SelectNext({Invalid}) == -1, "Non-finite restored entries are rejected");
    Invalid.NextAt = -1.0; Require(!ValidEntry(Invalid), "Negative timeline time is rejected");
    std::cout << "Continuous speed timeline: " << Checks << " checks passed\n";
}
