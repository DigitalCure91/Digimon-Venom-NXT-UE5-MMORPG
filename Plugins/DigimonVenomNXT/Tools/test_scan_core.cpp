#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTScanCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace
{
int Checks = 0;
void Require(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
struct Record
{
    int Percent = 0, FractionalHundredths = 0, PeakPercent = 0, Materializations = 0;
    bool bEverOwned = false;
};
void TestThresholds()
{
    using namespace DigimonVenomNXTScanCore;
    for (int Scan = 0; Scan <= 250; ++Scan)
    {
        const auto Result = Materialize(Scan, 100, 200, true);
        Require(Result.Ready == (Scan >= 100), "default conversion unlocks at 100 percent");
        Require(Result.ScanPercent == std::min(Scan, 200), "preview uses capped authoritative scan");
        Require(Result.BonusABI == (Scan < 100 ? 0 : (std::min(Scan, 200) - 100) / 20), "each full twenty extra percent gives ABI");
        Require(Result.RemainingPercent == (Scan < 100 ? Scan : 0), "all scan is spent in one conversion");
    }
    for (const auto& Pair : std::vector<std::pair<int, int>>{{100,0},{119,0},{120,1},{139,1},{140,2},{159,2},{160,3},{179,3},{180,4},{199,4},{200,5}})
        Require(Materialize(Pair.first, 100, 200, true).BonusABI == Pair.second, "reference ABI boundary");
    const auto First = Materialize(200, 100, 200, true);
    Require(!Materialize(First.RemainingPercent, 100, 200, true).Ready, "200 percent cannot fund a second partner");
    const auto Admin = Materialize(200, 100, 200, false);
    Require(Admin.RemainingPercent == 200 && Admin.BonusABI == 5, "explicit administrator non-consuming mode is respected");
    Require(Materialize(-100, 100, 200, true).ScanPercent == 0, "invalid negative scan cannot convert");
    Require(Materialize(999, 100, 999, true).BonusABI == 5, "raised scan cap never raises ABI reward past five");
    Require(!Materialize(150, 175, 200, true).Ready, "configured conversion threshold is enforced");
    Require(Materialize(175, 175, 200, true).BonusABI == 3, "ABI uses the reference 100 percent base with custom requirements");
    Require(Materialize(100, 300, 100, true).Requirement == 100, "unreachable configured requirement clamps to cap");
    Require(Cap(-100) == 100 && Cap(10000) == 999 && Requirement(-1,200) == 1, "invalid settings have bounded usable defaults");
}
void TestGainAndVariants()
{
    using namespace DigimonVenomNXTScanCore;
    Require(Gain(195, 10, 200) == 200, "battle gain caps at two hundred");
    Require(Gain(1, std::numeric_limits<std::int64_t>::max(), 200) == 200, "large gain cannot overflow");
    Require(Gain(120, -20, 200) == 120, "negative rewards cannot remove scan");
    Require(Gain(-50, 10, 200) == 10, "corrupt negative scan recovers safely");
    Require(Gain(999, 10, 200) == 200, "lower configured cap normalizes old scan");
    for (int Variant = -2; Variant <= 255; ++Variant)
    {
        Require(IsVariantAvailable(Variant, true, true, true) == (Variant >= 0 && Variant <= 2), "unknown enum values are rejected");
        Require(!IsVariantAvailable(Variant, false, false, false), "forms with no artwork cannot materialize");
    }
    Require(IsVariantAvailable(0,true,false,false) && !IsVariantAvailable(1,true,false,false) && !IsVariantAvailable(2,true,false,false), "normal artwork does not unlock alternate forms");
    Require(IsVariantAvailable(1,false,true,false) && IsVariantAvailable(2,false,false,true), "each variant validates its own artwork");
}
void TestHistory()
{
    using namespace DigimonVenomNXTScanCore;
    Record Legacy; Legacy.Percent = 140;
    Require(Observe(Legacy, 200) && Legacy.PeakPercent == 140 && !Legacy.bEverOwned && Legacy.Materializations == 0,
        "old scans migrate without inventing ownership or conversion counts");
    Require(!Observe(Legacy,200), "history migration is idempotent");
    Require(Observe(Legacy,200,true) && Legacy.bEverOwned, "owned/evolved form is recorded independently of its current scan");
    Legacy.Percent = 200; Observe(Legacy,200); Legacy.Percent = 0;
    Require(!Observe(Legacy,200) && Legacy.PeakPercent == 200 && Legacy.bEverOwned, "consumption does not erase discovery");
    Require(!Observe(Legacy,100) && Legacy.PeakPercent == 200, "reduced scan cap does not erase lifetime peak");
    Record Corrupt; Corrupt.Percent = -10; Corrupt.PeakPercent = -5; Corrupt.Materializations = -2;
    Require(Observe(Corrupt,200) && Corrupt.Percent == 0 && Corrupt.PeakPercent == 0 && Corrupt.Materializations == 0,
        "negative legacy metadata is repaired");
    Record Fractional; Fractional.Percent = 5; Fractional.FractionalHundredths = 20;
    Observe(Fractional,200);
    Require(Fractional.FractionalHundredths == 20, "legitimate custom-rate mastery fractions survive normalization");
    Fractional.FractionalHundredths = 140; Observe(Fractional,200);
    Require(Fractional.FractionalHundredths == 99, "invalid fractional residue is clamped");
    Fractional.Percent = 200; Observe(Fractional,200);
    Require(Fractional.FractionalHundredths == 0, "at scan cap no fractional overflow is retained");
    Fractional.Percent = -1; Fractional.FractionalHundredths = 20; Observe(Fractional,200);
    Require(Fractional.Percent == 0 && Fractional.FractionalHundredths == 0, "negative scan values cannot retain positive fractions");
    Record Converted; Converted.Materializations = 1;
    Require(Observe(Converted,200) && Converted.bEverOwned, "known conversion implies historical ownership");
    Record Shiny;
    Require(!Observe(Shiny,200) && !Shiny.bEverOwned && Shiny.PeakPercent == 0, "history for one variant never unlocks another");
}
struct Profile
{
    std::string Account = "account-a";
    Record Scan;
    std::vector<std::string> Collection, Party, Farm;
    int ABI = 0;
};
void TestPersistence()
{
    using namespace DigimonVenomNXTScanCore;
    Profile State; State.Scan.Percent = 200; State.Collection = {"starter"}; State.Party = {"starter"};
    Profile OtherAccount;
    int SaveCalls = 0;
    const auto Mutate = [](Profile& P)
    {
        const auto Result = Materialize(P.Scan.Percent,100,200,true);
        Observe(P.Scan,200,true);
        P.Scan.Percent = Result.RemainingPercent;
        ++P.Scan.Materializations;
        P.ABI = Result.BonusABI;
        P.Collection.push_back("new-guid"); P.Party.push_back("new-guid"); P.Farm.push_back("resident-guid");
    };
    Require(!Commit(State, Mutate, [&](const Profile& Candidate)
    {
        ++SaveCalls;
        Require(Candidate.Scan.Percent == 0 && Candidate.ABI == 5 && Candidate.Collection.size() == 2,
            "save receives the complete candidate transaction");
        return false;
    }), "save failure refuses conversion");
    Require(SaveCalls == 1 && State.Scan.Percent == 200 && State.Scan.PeakPercent == 0 && !State.Scan.bEverOwned &&
        State.Scan.Materializations == 0 && State.Collection.size() == 1 && State.Party.size() == 1 && State.Farm.empty() && State.ABI == 0,
        "save failure restores all scan, history, identity placement and ABI fields");
    Profile Persisted;
    Require(Commit(State, Mutate, [&](const Profile& Candidate) { ++SaveCalls; Persisted = Candidate; return true; }), "successful save commits conversion");
    Require(State.Scan.Percent == 0 && Persisted.Scan.Percent == 0 && Persisted.Scan.PeakPercent == 200 &&
        Persisted.Scan.bEverOwned && Persisted.Scan.Materializations == 1 && Persisted.ABI == 5 && Persisted.Collection.back() == "new-guid",
        "reloaded account retains history and the actual created partner");
    Require(OtherAccount.Scan.Percent == 0 && !OtherAccount.Scan.bEverOwned && OtherAccount.Collection.empty(), "another account remains isolated");
    Require(SaveCalls == 2 && !Materialize(Persisted.Scan.Percent,100,200,true).Ready, "retry/reload cannot repeat a committed conversion");
}
}
int main()
{
    TestThresholds(); TestGainAndVariants(); TestHistory(); TestPersistence();
    std::cout << "Scan/DigiDex core: " << Checks << " checks passed\n";
}
