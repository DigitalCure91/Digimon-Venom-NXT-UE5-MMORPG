#pragma once

// Engine-independent traversal shared by load and deferred settlement migration.
// Call with a candidate profile; publish it only after its atomic save succeeds.
namespace DigimonVenomNXTCombatMigrationCore
{
    template <typename Collection, typename Roster, typename Migrate>
    bool Reconcile(Collection& Partners, Roster& SeasonRoster, bool bBattleLocked, Migrate&& MigratePartner)
    {
        if (bBattleLocked) return false;
        bool bChanged = false;
        for (auto& Partner : Partners) bChanged = MigratePartner(Partner) || bChanged;
        for (auto& Tamer : SeasonRoster)
            for (auto& Partner : Tamer.Team) bChanged = MigratePartner(Partner) || bChanged;
        return bChanged;
    }
}
