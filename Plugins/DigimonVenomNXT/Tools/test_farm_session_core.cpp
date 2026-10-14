#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTFarmSessionCore.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <utility>

static int Checks = 0;
static void Check(bool Condition, const char* Description)
{
    ++Checks;
    if (!Condition) { std::fprintf(stderr, "FAIL farm sessions: %s\n", Description); std::exit(1); }
}

int main()
{
    using namespace DigimonVenomNXTFarmSessionCore;
    // Two distinct accounts never share a private view, regardless of matching
    // return map, farm entry ordering, or whether both farms are occupied.
    for (bool Authenticated : { false, true })
        for (bool OwnTamer : { false, true })
            for (bool ViewerInFarm : { false, true })
                for (bool SubjectInFarm : { false, true })
                    for (bool SameMap : { false, true })
                    {
                        const bool Visible = MayObserve(Authenticated, OwnTamer, ViewerInFarm, SubjectInFarm, SameMap);
                        if (!Authenticated) Check(!Visible, "unauthenticated connections see no tamers");
                        else if (OwnTamer) Check(Visible, "owner keeps own tamer throughout transition");
                        else if (ViewerInFarm || SubjectInFarm) Check(!Visible, "private farm cannot leak to another account");
                        else Check(Visible == SameMap, "public tamer stays scoped to current map");
                    }
    Check(AcceptRevision(0, 0), "initial replication accepted");
    Check(AcceptRevision(0, 1), "first entry accepted");
    Check(AcceptRevision(1, 2), "exit accepted");
    Check(!AcceptRevision(2, 1), "late entry cannot resurrect exited farm");
    Check(AcceptRevision(2, 2), "duplicate exit is idempotent");
    Check(!AcceptRevision(3, 2), "late exit cannot dismiss a new entry");
    Check(AcceptRevision(3, 4), "later session takes over");
    Check(AcceptRevision(0xffffffffULL, 0x100000000ULL), "long running host does not wrap at uint32");

    std::set<std::pair<double, double>> Cells;
    for (int Slot = 0; Slot < MaximumPrivateSessions; ++Slot)
    {
        const auto Cell = OriginForSlot(Slot);
        Check(Cells.emplace(Cell.X, Cell.Y).second, "each active session has a distinct physical cell");
        Check(Cell.Y + 5000.0 < 0.0, "farm cell cannot overlap public grid including artwork bounds");
        Check(std::abs(Cell.X) < 1000000.0 && std::abs(Cell.Y) < 1000000.0, "cells remain within conservative world coordinates");
    }
    Check(OriginForSlot(63).X == 630000.0 && OriginForSlot(64).X == 0.0, "row wrap keeps slot allocation unique");
    Check(OriginForSlot(64).Y == -60000.0, "next row is fully separated from the first");
    std::printf("farm session core: %d checks passed\n", Checks);
    return 0;
}
