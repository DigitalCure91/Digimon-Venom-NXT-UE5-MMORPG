#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTHealingPresentationCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
using namespace DigimonVenomNXTHealingPresentationCore;

void TestUnconfirmedProfiles()
{
    Track Value;
    Value.Observe({50, 20, 100, 40});
    Require(!Value.IsAnimating() && !Value.ShowingReceipt, "opening a damaged party never pretends to heal");
    Value.Observe({100, 40, 100, 40});
    Require(!Value.IsAnimating(), "unrelated profile restoration cannot invent a receipt animation");
    Require(Value.Display().HP == 100 && Value.Display().SP == 40, "ordinary profile changes are shown immediately");
    Require(!Value.Confirm({100, 40, 100, 40}, {100, 40, 100, 40}), "already healthy partners never emit green pluses");
    Require(!Value.Confirm({50, 20, 100, 40}, {40, 40, 100, 40}), "mixed damage and energy changes are not healing");
    Require(!Value.Confirm({50, 20, 100, 40}, {150, 40, 200, 40}), "level-up maximum changes are not recovery receipts");
}

void TestReceiptBeforeReplication()
{
    Track Value;
    const Vitals Before{0, 5, 1250, 160}, After{1250, 160, 1250, 160};
    Value.Observe(Before, 6);
    Require(Value.Confirm(Before, After, 7), "defeated partner accepts confirmed full restoration");
    Require(Value.Display().HP == 0 && Value.AwaitingProfile, "animation starts from the receipt's original vitals");
    int PreviousHP = 0, PreviousSP = 5;
    for (int Frame = 0; Frame < 180; ++Frame)
    {
        Value.Observe(Before, 6); // Simulate repeated unrelated old profile replication.
        Value.Advance(1.0 / 60.0);
        const Vitals Current = Value.Display();
        Require(Current.HP >= PreviousHP && Current.SP >= PreviousSP, "old profile cannot rewind recovery interpolation");
        Require(Current.HP <= After.HP && Current.SP <= After.SP, "interpolated bars and counts never overshoot");
        PreviousHP = Current.HP; PreviousSP = Current.SP;
    }
    Require(Value.Display().HP == 1250 && Value.Display().SP == 160, "confirmed vitals remain after animation ends");
    Require(!Value.IsAnimating() && Value.AwaitingProfile, "effects stop even if replication is delayed");
    Value.Observe(After, 7);
    Require(!Value.AwaitingProfile && !Value.IsAnimating(), "late matching snapshot reconciles without replay");
    Value.Observe({900, 130, 1250, 160}, 7);
    Require(Value.Display().HP == 900 && !Value.ShowingReceipt, "new battle or item vitals supersede completed healing");
}

void TestReplicationBeforeReceipt()
{
    Track Value;
    const Vitals Before{72, 0, 300, 90}, After{300, 90, 300, 90};
    Value.Observe(After);
    Require(Value.Confirm(Before, After), "receipt after profile still supplies trustworthy old/new endpoints");
    Value.Observe(After);
    Require(Value.Display().HP == 72 && Value.IsAnimating() && !Value.AwaitingProfile, "matching profile does not suppress recovery animation");
    Value.Advance(0.5);
    const int Intermediate = Value.Display().HP;
    Require(Intermediate > 72 && Intermediate < 300, "bar has a real intermediate fill state");
    Value.Observe(After);
    Require(Value.Display().HP == Intermediate, "repeated identical profile updates do not restart the animation");
    Value.Observe({210, 60, 300, 90});
    Require(!Value.IsAnimating() && Value.Display().HP == 210, "new contradictory authoritative vitals cancel stale animation");
}

void TestIdentitiesAndSPOnly()
{
    std::map<int, Track> Tracks;
    Tracks[73].Observe({100, 2, 100, 60});
    Tracks[19].Observe({100, 60, 100, 60});
    Require(Tracks[73].Confirm({100, 2, 100, 60}, {100, 60, 100, 60}), "SP-only exhaustion is visibly recoverable");
    Tracks[73].Advance(0.5);
    Require(Tracks[73].Display().HP == 100 && Tracks[73].Display().SP > 2, "SP-only receipt leaves HP untouched");
    Require(!Tracks[19].IsAnimating(), "healthy partner does not inherit another identity's animation");
    const int ReorderedParty[] = {19, 73};
    Require(!Tracks[ReorderedParty[0]].IsAnimating() && Tracks[ReorderedParty[1]].IsAnimating(), "party reorder follows identity, not visual slot");
    Tracks[73].Advance(-2.0); Tracks[73].Advance(std::numeric_limits<double>::quiet_NaN());
    Require(std::isfinite(Tracks[73].FillAlpha()), "invalid tick input cannot corrupt progress bars");
    Tracks[73].Advance(1000.0);
    Require(!Tracks[73].IsAnimating() && Tracks[73].Display().SP == 60, "a long frame settles precisely to confirmed final values");
    Track NoSP;
    Require(NoSP.Confirm({0, 0, 100, 0}, {100, 0, 100, 0}), "zero-SP custom profiles retain their real maximum while HP heals");
    NoSP.Advance(10);
    Require(NoSP.Display().SP == 0 && NoSP.Display().MaxSP == 0, "zero-SP partner never invents energy");
}

void TestRevisionFencingAndHiddenTime()
{
    Track Value;
    Value.Observe({900, 70, 1000, 90}, 12);
    Require(Value.Confirm({400, 4, 1000, 90}, {1000, 90, 1000, 90}, 13, 50.0), "receipt fences the profile state that preceded the latest damage");
    Value.Observe({900, 70, 1000, 90}, 12);
    Require(Value.Display().HP == 400 && Value.AwaitingProfile, "older pre-battle snapshot cannot replace authoritative receipt endpoints");
    Value.Observe({300, 2, 1000, 90}, 11);
    Require(Value.Display().HP == 400, "even different older snapshots remain fenced");
    Value.AdvanceClock(50.5);
    Require(Value.Display().HP > 400 && Value.Display().HP < 1000, "real monotonic time drives visual recovery");
    Value.AdvanceClock(110.0); // Widget hidden for a minute, with no intermediate ticks.
    Require(!Value.IsAnimating() && Value.Display().HP == 1000, "reopening a hidden page never replays an expired plus effect");
    Value.Observe({700, 30, 1000, 90}, 13);
    Require(!Value.AwaitingProfile && Value.Display().HP == 700, "coalesced newer damage after recovery supersedes receipt without a full-HP intermediate snapshot");
    Value.Confirm({700, 30, 1000, 90}, {1000, 90, 1000, 90}, 14, 120.0);
    Value.Observe({980, 88, 1000, 90}, 15);
    Require(!Value.AwaitingProfile && !Value.IsAnimating() && Value.Display().HP == 980, "a newer legacy or direct recovery revision subsumes the previous receipt");
}
}

int main()
{
    TestUnconfirmedProfiles(); TestReceiptBeforeReplication(); TestReplicationBeforeReceipt(); TestIdentitiesAndSPOnly(); TestRevisionFencingAndHiddenTime();
    std::cout << "Healing presentation core: " << Checks << " checks passed.\n";
}
