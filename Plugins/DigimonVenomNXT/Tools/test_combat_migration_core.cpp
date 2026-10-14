#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCombatMigrationCore.h"
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
struct Partner { int Version = 0; int HP = 25; int SP = 0; int Level = 50; int ABI = 120; std::string Id = "owned-guid"; };
struct Tamer { std::vector<Partner> Team; };
struct Profile
{
    std::vector<Partner> Collection;
    std::vector<Tamer> Roster;
    std::string Checkpoint = "exact-unresolved-decision";
    int Credits = 935;
    int Proofs = 28;
};
}
int main()
{
    Profile Saved;
    Saved.Collection.resize(12);
    Saved.Roster.resize(15);
    for (auto& T : Saved.Roster) T.Team.resize(3);
    int Calls = 0;
    auto Apply = [&](Partner& P)
    {
        ++Calls;
        if (P.Version != 0) return false;
        P.Version = 1;
        P.HP *= 2; // Test traversal delegates fraction conversion rather than overwriting health itself.
        return true;
    };
    Require(!DigimonVenomNXTCombatMigrationCore::Reconcile(Saved.Collection, Saved.Roster, true, Apply), "live or checkpoint battle defers the entire migration");
    Require(Calls == 0, "no partner or season rival touched under battle lock");
    Require(Saved.Collection[0].Version == 0 && Saved.Collection[0].HP == 25, "locked collection remains exact");
    Require(Saved.Roster[14].Team[2].Version == 0, "locked season reserve remains exact");
    Require(Saved.Checkpoint == "exact-unresolved-decision" && Saved.Proofs == 28, "lock preserves checkpoint and campaign proofs");
    Profile Candidate = Saved;
    Require(DigimonVenomNXTCombatMigrationCore::Reconcile(Candidate.Collection, Candidate.Roster, false, Apply), "unlocked candidate migrates");
    Require(Calls == 57, "all collection partners and all fifteen season teams are traversed");
    Require(Candidate.Collection[11].Version == 1 && Candidate.Roster[14].Team[2].Version == 1, "boxed and distant season partners migrate");
    Require(Saved.Collection[0].Version == 0, "candidate creation leaves live profile unpublished until save succeeds");
    Require(Candidate.Credits == 935 && Candidate.Proofs == 28 && Candidate.Checkpoint == Saved.Checkpoint, "migration traversal cannot invent rewards or clear story progress");
    Require(Candidate.Collection[0].SP == 0 && Candidate.Collection[0].Level == 50 && Candidate.Collection[0].ABI == 120 && Candidate.Collection[0].Id == "owned-guid", "earned progression and exhausted SP retained");
    Saved = Candidate; // The production caller does this only after successful atomic SaveProfile.
    Calls = 0;
    Require(!DigimonVenomNXTCombatMigrationCore::Reconcile(Saved.Collection, Saved.Roster, false, Apply), "repeat login is idempotent");
    Require(Calls == 57 && Saved.Collection[0].HP == 50, "versioned vitals never scale twice");
    Saved.Collection[0] = Partner{};
    Saved.Collection[1].HP = 11; // Already-normalized checkpoint result persisted during settlement.
    Require(DigimonVenomNXTCombatMigrationCore::Reconcile(Saved.Collection, Saved.Roster, false, Apply), "deferred unengaged collection migrates after settlement");
    Require(Saved.Collection[0].HP == 50 && Saved.Collection[1].HP == 11, "settled canonical vitals are not rescaled with deferred collection");
    std::vector<Partner> EmptyCollection;
    std::vector<Tamer> EmptyRoster;
    Require(!DigimonVenomNXTCombatMigrationCore::Reconcile(EmptyCollection, EmptyRoster, false, Apply), "empty account needs no migration save");
    std::cout << "Combat migration traversal: " << Checks << " checks passed\n";
}
