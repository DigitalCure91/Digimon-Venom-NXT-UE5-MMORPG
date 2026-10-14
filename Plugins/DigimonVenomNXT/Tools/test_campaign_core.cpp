#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCampaignCore.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <string>
static int Checks = 0;
static void Check(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::fprintf(stderr, "FAIL campaign core: %s\n", Message); std::exit(1); }
}
int main()
{
    using namespace DigimonVenomNXTCampaignCore;
    for (int Campaign = -2; Campaign <= 5; ++Campaign)
    {
        Check(ValidCampaign(Campaign) == (Campaign >= 0 && Campaign <= 2), "saved campaign IDs remain 0, 1 and appended 2");
        const auto Prefix = ContextPrefix(Campaign);
        if (!ValidCampaign(Campaign)) { Check(Prefix.empty(), "invalid campaign has no context"); continue; }
        Check(ContextCampaign(std::string(Prefix) + "npc") == Campaign, "authored opponent prefix round trip");
        Check(ContextCampaign(std::string(Prefix) + "wild:31") == Campaign, "private wild context belongs to exact campaign");
        Check(ContextCampaign(Prefix) == -1, "empty opponent rejected");
    }
    for (const auto Bad : {"", "GhostLine:npc", "ghostline", "ghostlines:npc", "ghostline:npc", "evil:ghostline:npc", " relay:npc", "chronicle:npc", "relay", "story:ghostline:npc"})
    {
        // The one valid control ensures this is not merely rejecting every context.
        Check(ContextCampaign(Bad) == (std::string_view(Bad) == "ghostline:npc" ? 2 : -1), "context parser rejects unknown or shifted prefixes");
    }
    for (int Variant = 0; Variant <= 3; ++Variant)
        for (int Masteries = 0; Masteries < 8; ++Masteries)
            for (bool Wild : {false, true})
                for (int Base : {-4, 0, 1, 5, 10, 25})
                {
                    const bool Shiny = (Masteries & 1) != 0;
                    const bool Paradox = (Masteries & 2) != 0;
                    const bool Firewall = (Masteries & 4) != 0;
                    const bool Match = (Variant == 2 && Shiny) || (Variant == 1 && Paradox) || (Variant == 3 && Firewall);
                    const int Ordinary = Base < 0 ? 0 : Base;
                    const int Expected = !Wild ? Ordinary : Match ? Ordinary + (Ordinary + 4) / 5 : Ordinary;
                    Check(ScanGain(Base, Variant, Shiny, Paradox, Firewall, Wild) == Expected,
                        "matching wild mastery adds20 percent once to configured base; no bonus stacking");
                }
    Check(ScanGain(5, 3, true, true, false, true) == 5, "old campaign completions cannot grant Firewall mastery");
    Check(ScanGain(5, 3, false, false, true, true) == 6, "Dawn completion increases Firewall wild gain by20 percent");
    Check(ScanGain(0, 3, true, true, true, false) == 0, "no scan award from trainer, final boss or non-victory");
    std::printf("campaign core: %d checks passed\n", Checks);
}
