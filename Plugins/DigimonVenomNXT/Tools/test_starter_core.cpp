#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTStarterCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRecoveryCore.h"
#include <cstdlib>
#include <iostream>
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
struct Partner
{
    int Level = 1, ABI = 0, CAM = 32, TrainingHP = 7, CurrentHP = 1, CurrentSP = 2;
    int64_t Experience = 0;
    std::string Id = "original-guid", Species = "agumon", Move = "SpiritPulse";
};
struct Stats { int MaxHP, MaxSP; };
Stats StatsFor(const Partner& P)
{
    return {DigimonVenomNXTCombatCore::ScaledStat(100 + P.TrainingHP, P.Level), DigimonVenomNXTCombatCore::ScaledStat(40, P.Level)};
}
void TestNewPartners()
{
    Partner P; P.TrainingHP = 0;
    DigimonVenomNXTStarterCore::InitializeLevel(P, 5, 100, StatsFor);
    Require(P.Level == 5 && P.Experience == 332, "starter level and cumulative XP agree");
    Require(P.CurrentHP == 114 && P.CurrentSP == 46, "starter begins with full scaled HP/SP");
    Require(490 - P.Experience == 158, "starter needs normal level-five XP to reach six");
    DigimonVenomNXTStarterCore::InitializeLevel(P, 1, 100, StatsFor);
    Require(P.Level == 1 && P.Experience == 0 && P.CurrentHP == 100 && P.CurrentSP == 40,
        "materialization retains level one and full vitals");
    DigimonVenomNXTStarterCore::InitializeLevel(P, 5, 3, StatsFor);
    Require(P.Level == 3 && P.Experience == 114, "low configured maximum caps starter correctly");
    Require(DigimonVenomNXTStarterCore::StartingLevel(-10, 100) == 1, "invalid starter level clamps to one");
    Require(DigimonVenomNXTStarterCore::StartingLevel(250, 500) == 200, "starter obeys engine partner cap");
    Require(DigimonVenomNXTStarterCore::ExperienceFloor(200) == 2119741, "high level XP uses wide arithmetic");
}
void TestOldSaves()
{
    Partner Starter; Starter.Experience = 80;
    Partner Materialized;
    int Version = 0;
    Require(DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, false, StatsFor),
        "legacy original starter upgrade is persisted");
    Require(Starter.Level == 5 && Starter.Experience == 332 && Version == 1, "old starter receives one-time level correction");
    Require(Starter.CurrentHP == 122 && Starter.CurrentSP == 46, "migration heals from trained scaled maxima");
    Require(Starter.Id == "original-guid" && Starter.Species == "agumon" && Starter.Move == "SpiritPulse" &&
        Starter.CAM == 32 && Starter.ABI == 0 && Starter.TrainingHP == 7, "identity and earned progression survive migration");
    Require(Materialized.Level == 1 && Materialized.Experience == 0, "other owned partners are not raised");
    Starter.CurrentHP = 17; Starter.CurrentSP = 3;
    Require(!DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, false, StatsFor), "repeated login is idempotent");
    Require(Starter.CurrentHP == 17 && Starter.CurrentSP == 3, "repeated login cannot become a healing exploit");
    Starter.Level = 1; Starter.Experience = 0; Starter.ABI = 3;
    Require(!DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, false, StatsFor) && Starter.Level == 1,
        "later evolution/de-evolution reset stays level one");

    Partner PreviouslyEvolved; PreviouslyEvolved.ABI = 2; Version = 0;
    Require(DigimonVenomNXTStarterCore::UpgradeLegacyStarter(PreviouslyEvolved, Version, 5, 100, true, false, StatsFor) &&
        Version == 1 && PreviouslyEvolved.Level == 1 && PreviouslyEvolved.CurrentHP == 1,
        "pre-update transformed partners are marked but not boosted/healed");
    Partner OtherForm; Version = 0;
    Require(DigimonVenomNXTStarterCore::UpgradeLegacyStarter(OtherForm, Version, 5, 100, false, false, StatsFor) && OtherForm.Level == 1,
        "non-starter form or variant is untouched");
    Partner Experienced; Experienced.Level = 8; Experienced.Experience = 4930; Version = 0;
    Require(DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Experienced, Version, 5, 100, true, false, StatsFor) &&
        Experienced.Level == 8 && Experienced.Experience == 4930 && Experienced.CurrentHP == 1,
        "progressed starter never loses levels or gains unsolicited healing");
    Partner ExtraXP; ExtraXP.Experience = 1700; Version = 0;
    DigimonVenomNXTStarterCore::UpgradeLegacyStarter(ExtraXP, Version, 5, 100, true, false, StatsFor);
    Require(ExtraXP.Experience == 1700, "migration never subtracts earned experience");
}
void TestBattleDeferral()
{
    Partner Starter; int Version = 0;
    Require(!DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, true, StatsFor),
        "saved/live battle defers migration");
    Require(Starter.Level == 1 && Starter.CurrentHP == 1 && Starter.Experience == 0 && Version == 0,
        "deferral preserves checkpoint stats and pending migration marker");
    Require(DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, false, StatsFor) && Starter.Level == 5,
        "migration applies once saved battle has settled");
}
void TestRecoveryAndOpeningBattles()
{
    Partner Starter, Reserve; Starter.CurrentHP = Reserve.CurrentHP = 0;
    std::vector<Partner*> Party{&Starter, &Reserve};
    Require(DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, [](const Partner& Value)
        { const Stats S = StatsFor(Value); return DigimonVenomNXTRecoveryCore::Vitals{S.MaxHP, S.MaxSP}; }),
        "complete-party defeat recovery precedes starter migration");
    int Version = 0;
    DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Version, 5, 100, true, false, StatsFor);
    Require(Starter.Level == 5 && Starter.CurrentHP == 122 && Reserve.Level == 1 && Reserve.CurrentHP == 107,
        "starter upgrade cannot strand the other previously defeated partners");

    // The screenshot's two Rookie species and map-one Rookie pool share these
    // authored stats/moves. Use the live combat resolver, with full HP/SP on entry.
    const auto Rookie = [](int Level)
    {
        DigimonVenomNXTCombatCore::Unit U; U.Level = Level;
        U.HP = U.MaxHP = DigimonVenomNXTCombatCore::ScaledStat(100, Level);
        U.SP = U.MaxSP = DigimonVenomNXTCombatCore::ScaledStat(40, Level);
        U.Attack = DigimonVenomNXTCombatCore::ScaledStat(20, Level);
        U.Defense = DigimonVenomNXTCombatCore::ScaledStat(18, Level);
        U.Speed = DigimonVenomNXTCombatCore::ScaledStat(20, Level);
        U.Moves = {{38, 4}, {50, 8}, {62, 12}, {74, 16}};
        return U;
    };
    for (int WildLevel = 1; WildLevel <= 4; ++WildLevel)
    {
        bool AllWon = true;
        for (uint32_t Seed = 1; Seed <= 128; ++Seed)
        {
            const auto Result = DigimonVenomNXTCombatCore::Resolve({Rookie(5)}, {Rookie(WildLevel)}, 1, Seed);
            AllWon = AllWon && Result.TeamAWon && !Result.Draw;
        }
        Require(AllWon, "full-health level-five starter can win map-one level-one-through-four skill battles");
    }
}
}
int main()
{
    TestNewPartners(); TestOldSaves(); TestBattleDeferral(); TestRecoveryAndOpeningBattles();
    std::cout << "Starter core: " << Checks << " checks passed.\n";
}
