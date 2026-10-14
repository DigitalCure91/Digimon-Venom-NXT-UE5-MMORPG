#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTAudioCueCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <set>

namespace
{
int Checks = 0;
void Require(bool OK, const char* Reason)
{
    ++Checks;
    if (!OK) { std::cerr << "FAIL: " << Reason << '\n'; std::exit(1); }
}
}
int main()
{
    using namespace DigimonVenomNXTAudioCueCore;
    const std::set<std::string> Supplied = {"ui_se000", "ui_se001", "ui_se002", "ui_se003", "ui_se004", "ui_se009", "ui_se030", "se009", "se011", "se014"};
    std::set<std::string> Used;
    for (int I = 0; I < static_cast<int>(Cue::Count); ++I)
    {
        const auto* D = Describe(static_cast<Cue>(I));
        Require(D != nullptr && Supplied.count(D->Stem) == 1, "every cue uses an actual supplied SFX stem");
        Require(D->Gain > 0 && D->Gain <= .8f && D->Cooldown >= .065, "cue gains and rate limits have safe headroom");
        Require(D->Pitch >= .8f && D->Pitch <= 1.2f, "small deterministic UI pitch variation");
        Used.insert(D->Stem);
    }
    Require(Used == Supplied, "all assigned source interaction and combat cues have a gameplay or UI role");
    Require(Describe(static_cast<Cue>(255)) == nullptr, "untrusted enum values are rejected");
    Require(Volume(-1) == 0 && Volume(2) == 1, "volumes are clamped");
    Require(Volume(std::numeric_limits<float>::quiet_NaN()) == 0, "NaN preference mutes safely");
    Require(Volume(std::numeric_limits<float>::infinity()) == 0, "infinite preference mutes safely");
    Require(Mix(0, 1, 1) == 0 && Mix(1, 0, 1) == 0, "master and per-channel mute independently");
    Require(std::abs(Mix(.5f, .8f, .25f) - .1f) < .00001f, "master, channel and cue gains multiply exactly once");
    Gate G;
    Require(G.Accept(Cue::UIHover, 10), "first hover plays");
    Require(!G.Accept(Cue::UIHover, 10.02), "hover storm is bounded across all buttons");
    Require(G.Accept(Cue::Hit, 10.02), "hover cannot suppress independent combat impact");
    Require(G.Accept(Cue::UIHover, 10.13), "hover resumes after cooldown");
    Require(G.Accept(Cue::Heal, 11, "heal-receipt"), "confirmed heal plays once");
    Require(!G.Accept(Cue::Heal, 14, "heal-receipt"), "widget rebuild and delayed duplicate cannot replay heal");
    Require(G.Accept(Cue::Victory, 14, "battle-result"), "result feedback is independent of music routing");
    Require(!G.Accept(Cue::Defeat, 20, "battle-result"), "stale contradictory result shares the same receipt");
    Require(!G.Accept(Cue::UIClick, std::numeric_limits<double>::infinity()), "invalid clock does not corrupt gate");
    Require(!G.Accept(static_cast<Cue>(255), 20), "invalid cue cannot index past cooldown storage");
    Require(G.Accept(Cue::Item, 25, "item-a"), "first item effect");
    Require(!G.Accept(Cue::Item, 25.01, "item-b"), "rapid duplicate class is bounded");
    Require(!G.Accept(Cue::Item, 26, "item-b"), "rate-limited receipt cannot become a delayed duplicate");
    for (int I = 0; I < 6000; ++I)
        Require(G.Accept(Cue::Hit, 100.0 + I, "event-" + std::to_string(I)), "long battle histories keep playing new events");
    Require(G.ReceiptCount() == 4096, "event receipt memory remains bounded");
    Require(!G.Accept(Cue::Hit, 10000, "event-5999"), "most recent receipt survives pruning");
    std::cout << Checks << " audio cue policy checks passed\n";
}
