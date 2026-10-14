// Exercises the same recovery and reserve-promotion templates used by PlayerState
// and BattleActor. Unreal replication, SaveGame and widgets need an engine smoke test.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRecoveryCore.h"
#include <cstdlib>
#include <iostream>
#include <vector>

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
struct Stats { int MaxHP = 100; int MaxSP = 40; };
struct Partner { int CurrentHP = 0; int CurrentSP = 0; Stats Maximums; };
struct Unit { int Id = 0; int HP = 0; int SP = 0; bool bDefeated = true; ::Stats Stats; };
struct Team { std::vector<Unit> Active, Bench; };
DigimonVenomNXTRecoveryCore::Vitals Maximums(const Partner& Value)
{
    return {Value.Maximums.MaxHP, Value.Maximums.MaxSP};
}
Unit MakeUnit(int Id, int HP, int SP = 0)
{
    Unit Value;
    Value.Id = Id; Value.HP = HP; Value.SP = SP; Value.bDefeated = HP <= 0;
    return Value;
}

void TestLegacyWipeout()
{
    Partner Lead{0, 0, {215, 83}}, Reserve{-10, 4, {137, 52}}, Boxed{0, 1, {310, 64}};
    std::vector<Partner*> Party{&Lead, nullptr, &Reserve};
    Require(DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums), "legacy zero/negative HP party is recovered");
    Require(Lead.CurrentHP == 215 && Lead.CurrentSP == 83, "lead uses its level/training-derived maxima");
    Require(Reserve.CurrentHP == 137 && Reserve.CurrentSP == 52, "reserve gets full HP and SP too");
    Require(Boxed.CurrentHP == 0 && Boxed.CurrentSP == 1, "boxed non-party partner is untouched");
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums), "repair is idempotent after first recovery");
    std::vector<Partner*> Missing{nullptr, nullptr};
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Missing, Maximums), "stale IDs alone cannot create a party");
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(std::vector<Partner*>{}, Maximums), "empty party cannot recover or enter a battle");
}

void TestPartialInjuries()
{
    Partner Lead{0, 0, {215, 83}}, Reserve{1, 2, {137, 52}};
    const std::vector<Partner*> Party{&Lead, &Reserve};
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums), "one surviving reserve prevents free healing");
    Require(Lead.CurrentHP == 0 && Lead.CurrentSP == 0 && Reserve.CurrentHP == 1 && Reserve.CurrentSP == 2,
        "partial KO and low-HP injuries remain exactly unchanged for DigiLab");
    Lead.CurrentHP = 20; Reserve.CurrentHP = 0;
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums), "one surviving active partner prevents healing");
    Lead.CurrentHP = 215; Lead.CurrentSP = 0;
    Require(!DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums) && Lead.CurrentSP == 0,
        "SP exhaustion alone never qualifies as defeat");
}

void TestReservePromotion()
{
    Team Value{{MakeUnit(1, 0), MakeUnit(2, 10), MakeUnit(3, 0)},
        {MakeUnit(4, 0), MakeUnit(5, 7, 3), MakeUnit(6, 2, 1)}};
    Require(!DigimonVenomNXTRecoveryCore::IsTeamDefeated(Value), "living reserves count toward survival before promotion");
    Require(DigimonVenomNXTRecoveryCore::PrepareTeam(Value), "down active slots are replaced before waiting for commands");
    Require(Value.Active[0].Id == 5 && Value.Active[1].Id == 2 && Value.Active[2].Id == 6,
        "living reserves promote in order without displacing living active partners");
    Require(Value.Active[0].HP == 7 && Value.Active[0].SP == 3 && Value.Active[2].HP == 2,
        "reserve promotion preserves damage and SP");
    Require(Value.Bench[0].Id == 4 && Value.Bench[1].Id == 1 && Value.Bench[2].Id == 3,
        "defeated units remain in the battle roster for outcome persistence");
    Require(!DigimonVenomNXTRecoveryCore::PrepareTeam(Value), "already prepared formation remains stable");
    for (auto& Member : Value.Active) Member.HP = 0;
    Require(DigimonVenomNXTRecoveryCore::IsTeamDefeated(Value), "zero HP overrides stale living presentation flags");
    DigimonVenomNXTRecoveryCore::PrepareTeam(Value);
    Require(Value.Active[0].bDefeated && Value.Active[1].bDefeated && Value.Active[2].bDefeated,
        "all zero-HP flags are normalized so UI can finish the battle");
    Require(DigimonVenomNXTRecoveryCore::IsTeamDefeated(Team{}), "empty battle is terminal rather than waiting forever");
}

void TestBadVitals()
{
    Unit WrongFlag = MakeUnit(1, 10, 999); WrongFlag.bDefeated = true;
    Unit Negative = MakeUnit(2, -8, -4); Negative.bDefeated = false;
    Team Value{{WrongFlag}, {Negative}};
    Require(DigimonVenomNXTRecoveryCore::PrepareTeam(Value), "invalid vitals are repaired before input");
    Require(Value.Active[0].HP == 10 && !Value.Active[0].bDefeated && Value.Active[0].SP == 40,
        "stale defeat flag clears on living unit without healing HP");
    Require(Value.Bench[0].HP == 0 && Value.Bench[0].SP == 0 && Value.Bench[0].bDefeated,
        "negative vitals clamp to legal values");
    const auto Full = DigimonVenomNXTRecoveryCore::ResultVitals(Negative, true);
    const auto Hurt = DigimonVenomNXTRecoveryCore::ResultVitals(MakeUnit(3, 9, 2), false);
    Require(Full.HP == 100 && Full.SP == 40, "confirmed wipeout result fully restores its participant");
    Require(Hurt.HP == 9 && Hurt.SP == 2, "victory or retreat result persists injuries");
}

void TestManualFormation()
{
    Team Value;
    Value.Active = {MakeUnit(1, 0), MakeUnit(2, 12), MakeUnit(3, 0)};
    Value.Bench = {MakeUnit(4, 100), MakeUnit(5, 0)};
    Require(!DigimonVenomNXTRecoveryCore::PrepareTeam(Value, false), "source manual formation keeps healthy reserves on the bench");
    Require(Value.Active[0].Id == 1 && Value.Active[1].Id == 2 && Value.Active[2].Id == 3 && Value.Bench[0].Id == 4,
        "fainted lead slots do not automatically summon a reserve");
    Value.Active[1].HP = 0;
    Require(DigimonVenomNXTRecoveryCore::PrepareTeam(Value, false) && Value.Active[1].bDefeated,
        "manual formation still normalizes defeated presentation state");
    Require(!DigimonVenomNXTRecoveryCore::HasLivingUnit(Value.Active) && DigimonVenomNXTRecoveryCore::HasLivingUnit(Value.Bench),
        "source human encounter ends when active team falls even with a healthy reserve");
    Require(DigimonVenomNXTRecoveryCore::PrepareTeam(Value) && Value.Active[0].Id == 4,
        "default rival and automatic battle reserve behavior remains unchanged");
}

void TestFullPartySizes()
{
    for (int Count = 1; Count <= 12; ++Count)
    {
        std::vector<Partner> Owned;
        for (int Index = 0; Index < Count; ++Index) Owned.push_back({0, Index, {100 + Index * 17, 40 + Index * 3}});
        std::vector<Partner*> Party;
        for (auto& Member : Owned) Party.push_back(&Member);
        Require(DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party, Maximums), "every supported party size recovers on a wipeout");
        bool AllRestored = true;
        for (const auto& Member : Owned)
            AllRestored = AllRestored && Member.CurrentHP == Member.Maximums.MaxHP && Member.CurrentSP == Member.Maximums.MaxSP;
        Require(AllRestored, "full party recovery covers every active and reserve slot");
    }
}
}

int main()
{
    TestLegacyWipeout(); TestPartialInjuries(); TestReservePromotion(); TestBadVitals(); TestManualFormation(); TestFullPartySizes();
    std::cout << "Recovery core: " << Checks << " checks passed.\n";
}
