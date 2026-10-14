// Direct production-rule tests. Unreal profile/RPC/asset integration requires editor validation.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTVariantCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTScanCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCampaignCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTEvolutionCore.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

namespace
{
int Checks = 0;
void Require(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}

void TestWildDistribution()
{
    using namespace DigimonVenomNXTVariantCore;
    std::array<int, 4> Counts{};
    for (int Sample = 0; Sample < 100000; ++Sample)
        ++Counts[RollWildVariant((Sample + 0.5) / 100000.0, 0.01f, 0.025f, 0.01f)];
    Require(Counts[Firewall] == 1000, "Firewall covers exactly one percent of uniform default samples");
    Require(Counts[Shiny] == 1000 && Counts[Paradox] == 2500 && Counts[Normal] == 95500,
        "Firewall does not suppress existing Shiny or Paradox encounter odds");

    const WildRates Rates = EffectiveWildRates(0.01, 0.025, 0.01);
    const double Start = Rates.ShinyChance + Rates.ParadoxChance;
    const double End = Start + Rates.FirewallChance;
    Require(RollWildVariant(0.0,0.01,0.025,0.01) == Shiny, "first rare interval includes zero");
    Require(RollWildVariant(Rates.ShinyChance,0.01,0.025,0.01) == Paradox, "Shiny/Paradox boundary has no overlap");
    Require(RollWildVariant(std::nextafter(Start,0.0),0.01,0.025,0.01) == Paradox,
        "the last Paradox roll is not a Firewall encounter");
    Require(RollWildVariant(Start,0.01,0.025,0.01) == Firewall &&
        RollWildVariant(std::nextafter(End,0.0),0.01,0.025,0.01) == Firewall,
        "the Firewall interval includes its start and excludes its end");
    Require(RollWildVariant(End,0.01,0.025,0.01) == Normal, "normal distribution begins immediately after Firewall");
    for (int Sample = 0; Sample < 1000; ++Sample)
    {
        const double Roll = (Sample + 0.5) / 1000.0;
        Require(RollWildVariant(Roll,0.0,0.0,1.0) == Firewall, "100 percent Firewall with other rarities disabled");
        Require(RollWildVariant(Roll,0.01,0.025,0.0) != Firewall, "zero global chance disables Firewall completely");
        Require(RollWildVariant(Roll,0.0,0.0,0.0) == Normal, "all disabled rarities remain ordinary wild battles");
    }
    Counts.fill(0);
    for (int Sample = 0; Sample < 10000; ++Sample)
        ++Counts[RollWildVariant((Sample + 0.5) / 10000.0, 0.01, 0.025, 0.25)];
    Require(Counts[Firewall] == 2500 && Counts[Shiny] == 100 && Counts[Paradox] == 250,
        "changing the project Firewall setting changes only its category while total is valid");
}

void TestMalformedSettings()
{
    using namespace DigimonVenomNXTVariantCore;
    const double NaN = std::numeric_limits<double>::quiet_NaN();
    const double Infinity = std::numeric_limits<double>::infinity();
    Require(SafeProbability(NaN) == 0.0 && SafeProbability(Infinity) == 0.0 && SafeProbability(-Infinity) == 0.0,
        "nonfinite ini values cannot poison probabilities");
    Require(SafeProbability(-0.25) == 0.0 && SafeProbability(2.0) == 1.0,
        "out-of-range ini probabilities clamp safely");
    const WildRates Over = EffectiveWildRates(1.0,1.0,1.0);
    Require(std::abs(Over.ShinyChance - 1.0/3.0) < 1e-12 &&
        std::abs(Over.ParadoxChance - 1.0/3.0) < 1e-12 && std::abs(Over.FirewallChance - 1.0/3.0) < 1e-12,
        "oversubscribed settings scale all rare rates proportionally");
    Require(RollWildVariant(0.9,1.0,1.0,1.0) == Firewall, "the last variety cannot be starved by earlier settings");
    Require(RollWildVariant(0.5,NaN,Infinity,1.0) == Firewall, "invalid other settings do not hide a configured Firewall rate");
    for (double BadRoll : {-1.0,1.0,2.0,NaN,Infinity})
        Require(RollWildVariant(BadRoll,1.0,1.0,1.0) == Normal, "invalid RNG inputs never invent a rare encounter");
}

void TestVariantScanAndMasteries()
{
    using namespace DigimonVenomNXTVariantCore;
    using namespace DigimonVenomNXTScanCore;
    for (int Variant = -1; Variant < 256; ++Variant)
        Require(IsVariantAvailable(Variant,true,true,true,true) == (Variant >= Normal && Variant <= Firewall),
            "four known variants are accepted and unknown saved/RPC enum values rejected");
    Require(!IsVariantAvailable(Firewall,true,true,true), "legacy four-argument callers cannot unlock missing Firewall data");
    Require(IsVariantAvailable(Firewall,false,false,false,true), "Firewall availability uses its own artwork flag");
    Require(!IsVariantAvailable(Shiny,false,false,false,true) && !IsVariantAvailable(Paradox,false,false,false,true),
        "Firewall art never unlocks another variety");
    for (int Base : {-10,0,1,5,10,99,std::numeric_limits<int>::max()})
        for (int Masteries = 0; Masteries < 8; ++Masteries)
            for (int Variant = Normal; Variant <= Firewall; ++Variant)
            {
                const bool ShinyMastery = (Masteries & 1) != 0;
                const bool ParadoxMastery = (Masteries & 2) != 0;
                const bool FirewallMastery = (Masteries & 4) != 0;
                const bool Match = (Variant == Shiny && ShinyMastery) ||
                    (Variant == Paradox && ParadoxMastery) || (Variant == Firewall && FirewallMastery);
                const long long Nonnegative = std::max(0,Base);
                const int Expected = Match ? static_cast<int>(std::min<long long>(std::numeric_limits<int>::max(),
                    Nonnegative + (Nonnegative + 4) / 5)) : WildScanGain(Variant,Base);
                Require(DigimonVenomNXTCampaignCore::ScanGain(Base,Variant,ShinyMastery,ParadoxMastery,FirewallMastery,true) == Expected,
                    "Dawn Firewall, World DS Paradox and Super Xros Wars Shiny masteries increase only their variety by20 percent");
                Require(DigimonVenomNXTCampaignCore::ScanGain(Base,Variant,ShinyMastery,ParadoxMastery,FirewallMastery,false) == Nonnegative,
                    "trainer battles cannot apply a wild scan mastery");
            }
    int FirewallScan = 0;
    for (int Win = 1; Win <= 20; ++Win)
    {
        FirewallScan = Gain(FirewallScan,WildScanGain(Firewall,5),200);
        Require(Materialize(FirewallScan,100,200,true).Ready == (Win == 20),
            "twenty Firewall victories unlock default one hundred percent materialization");
    }
    Require(Materialize(FirewallScan,100,200,true).RemainingPercent == 0,
        "Firewall materialization consumes its scan under the existing account rule");
    Require(Gain(198,WildScanGain(Firewall,5),200) == 200 && Gain(200,5,200) == 200,
        "Firewall respects the shared scan cap without overflow");
}

void TestFirewallEvolutionIdentity()
{
    struct Partner
    {
        std::string SpeciesId = "rookie";
        int Variant = DigimonVenomNXTVariantCore::Firewall;
        int Level = 30, ABI = 20, CAM = 70, Training = 17;
        long long Experience = 999;
        std::string InstanceId = "stable-firewall-instance";
    } Value;
    DigimonVenomNXTEvolutionCore::ApplyIdentityPreservingTransform(Value,std::string("champion"),24);
    Require(Value.SpeciesId == "champion" && Value.Level == 1 && Value.Experience == 0 && Value.ABI == 24,
        "Firewall evolution uses real shared progression rules");
    Require(Value.Variant == DigimonVenomNXTVariantCore::Firewall && Value.CAM == 70 && Value.Training == 17 &&
        Value.InstanceId == "stable-firewall-instance", "evolution retains Firewall identity, friendship and training");
    Value.Level = 20;
    DigimonVenomNXTEvolutionCore::ApplyIdentityPreservingTransform(Value,std::string("rookie"),30);
    Require(Value.Variant == DigimonVenomNXTVariantCore::Firewall && Value.SpeciesId == "rookie" && Value.ABI == 30,
        "de-evolution preserves the same Firewall variety and permanent ABI");
}
}

int main()
{
    TestWildDistribution(); TestMalformedSettings(); TestVariantScanAndMasteries(); TestFirewallEvolutionIdentity();
    std::cout << "Firewall variety core: " << Checks << " checks passed\n";
}
