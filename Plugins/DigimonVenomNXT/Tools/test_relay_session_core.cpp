#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTRelaySessionCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTFarmSessionCore.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <set>
#include <utility>
static int Checks = 0;
static void Check(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::fprintf(stderr, "FAIL relay session: %s\n", Message); std::exit(1); }
}
int main()
{
    using namespace DigimonVenomNXTRelaySessionCore;
    for (bool Auth : {false,true}) for (bool Own : {false,true})
        for (bool ViewerPrivate : {false,true}) for (bool SubjectPrivate : {false,true})
            for (bool SameMap : {false,true})
            {
                const bool Visible = MayObserve(Auth, Own, ViewerPrivate, SubjectPrivate, SameMap);
                Check(Visible == (Auth && (Own || (!ViewerPrivate && !SubjectPrivate && SameMap))), "private accounts and public observers cannot observe each other");
                if (ViewerPrivate && SubjectPrivate && !Own) Check(!Visible, "matching private campaign map never implies shared instance");
            }
    std::set<std::pair<double,double>> Cells;
    for (int Slot = 0; Slot < MaximumPrivateSessions; ++Slot)
    {
        const auto Cell = OriginForSlot(Slot);
        Check(Cells.emplace(Cell.X, Cell.Y).second, "each live account owns a unique cell");
        Check(Cell.Y - 20000.0 > 200000.0, "private campaign bounds cannot overlap public world");
        const auto Farm = DigimonVenomNXTFarmSessionCore::OriginForSlot(Slot);
        Check(std::abs(Cell.Y - Farm.Y) > 40000.0, "farm and relay allocations cannot overlap");
        if (Slot % 64 != 0) Check(std::abs(Cell.X - OriginForSlot(Slot - 1).X) >= 40000.0, "neighbouring private maps do not collide");
    }
    Check(AcceptRevision(3,3) && AcceptRevision(3,4), "duplicate and newer session states accepted");
    Check(!AcceptRevision(4,3), "late map entry cannot undo later travel or exit");
    Check(AcceptRevision(0xffffffffULL, 0x100000000ULL), "session revision survives uint32 boundary");
    for (int From = 0; From <= 19; ++From) for (int To = 0; To <= 19; ++To)
        Check(IsAdjacentPortal(From, To) == (From >= 1 && From <= 18 && To >= 1 && To <= 18 && std::abs(From-To)==1), "portal intent requires a real adjacent map");
    Check(WithinInteraction(260,0) && WithinInteraction(0,-260), "boundary proximity permits interaction");
    Check(!WithinInteraction(261,0) && !WithinInteraction(260,260), "distant/diagonal spoofed interaction rejected");
    Check(!WithinInteraction(std::numeric_limits<double>::infinity(),0), "infinite client coordinates rejected");
    Check(!WithinInteraction(std::numeric_limits<double>::quiet_NaN(),0), "NaN client coordinates rejected");
    for (int Requested = -1; Requested <= 2; ++Requested)
        for (int Current = 0; Current <= 1; ++Current)
            for (bool Inside : {false,true}) for (bool Battle : {false,true})
                for (bool Season : {false,true}) for (bool RelaySaved : {false,true}) for (bool ChroniclesSaved : {false,true})
                {
                    const bool Allowed = MayEnterCampaign(Requested, Current, Inside, Battle, Season, RelaySaved, ChroniclesSaved);
                    if (Battle || Season || !ValidCampaign(Requested)) Check(!Allowed, "battle and malformed campaign switches are rejected");
                    if ((Requested == 0 && ChroniclesSaved) || (Requested == 1 && RelaySaved)) Check(!Allowed, "the other journey's pending decision cannot be bypassed");
                    if (Inside && Requested != Current && (RelaySaved || ChroniclesSaved)) Check(!Allowed, "switching campaigns cannot abandon either pending decision");
                }
    Check(MayEnterCampaign(1,0,true,false,false,false,false), "Relay can switch atomically to Chronicles when no battle is pending");
    Check(MayEnterCampaign(0,1,true,false,false,false,false), "Chronicles can switch atomically back to Relay");
    Check(MayEnterCampaign(1,0,false,false,false,false,true), "reconnected Chronicles checkpoint can enter its exact private campaign");
    Check(SavedCampaign(1,false,true,false,false)==1, "farm exit and login restore Chronicles instead of default Relay");
    Check(SavedCampaign(0,false,true,false,false)==1, "legacy stale selector recovers the only inside campaign");
    Check(SavedCampaign(1,true,true,false,false)==1, "active selector disambiguates old nested campaign flags");
    Check(SavedCampaign(0,true,false,false,true)==1, "Chronicles pending decision takes priority over an older Relay location flag");
    Check(SavedCampaign(1,false,true,true,false)==0, "Relay pending decision takes priority over an older Chronicles location flag");
    Check(SavedCampaign(1,false,false,false,false)==-1, "remembering a selected campaign does not force public players back inside");
    Check(SavedCampaign(0,true,true,true,true)==-2, "conflicting saved decisions fail closed without deleting either");
    // Exhaustive three-way entry and reconnect decisions, with all combinations
    // of inside flags, pending checkpoints and stale/invalid preferred identities.
    for (int Requested = -1; Requested <= 3; ++Requested)
        for (int Current = 0; Current <= 2; ++Current)
            for (bool Inside : {false,true}) for (bool Battle : {false,true}) for (bool Season : {false,true})
                for (int Pending = 0; Pending < 8; ++Pending)
                {
                    const bool R = (Pending & 1) != 0, C = (Pending & 2) != 0, G = (Pending & 4) != 0;
                    bool Expected = Requested >= 0 && Requested <= 2 && !Battle && !Season;
                    if (Requested != 0 && R) Expected = false;
                    if (Requested != 1 && C) Expected = false;
                    if (Requested != 2 && G) Expected = false;
                    if (Inside && Current != Requested && Pending != 0) Expected = false;
                    Check(MayEnterCampaign(Requested,Current,Inside,Battle,Season,R,C,G) == Expected,
                        "every campaign blocks another pending decision and permits only its exact restore");
                }
    for (int Preferred = -1; Preferred <= 3; ++Preferred)
        for (int Inside = 0; Inside < 8; ++Inside)
            for (int Pending = 0; Pending < 8; ++Pending)
            {
                const bool R = (Pending & 1) != 0, C = (Pending & 2) != 0, G = (Pending & 4) != 0;
                const int Count = static_cast<int>(R) + static_cast<int>(C) + static_cast<int>(G);
                const int Restored = SavedCampaign(Preferred,Inside & 1,Inside & 2,R,C,Inside & 4,G);
                if (Count > 1) Check(Restored == -2, "every conflicting pair or triple fails safely without choosing a journey");
                else if (Count == 1) Check(Restored == (R ? 0 : C ? 1 : 2), "a single durable decision outranks stale presence");
                else if (Preferred >= 0 && Preferred <= 2 && (Inside & (1 << Preferred))) Check(Restored == Preferred, "valid selected presence wins over duplicate flags");
                else if (Inside == 0) Check(Restored == -1, "no forced campaign return without presence or checkpoint");
                else Check(Restored >= 0 && Restored <= 2 && (Inside & (1 << Restored)), "stale preference recovers an actually saved presence");
            }
    Check(SavedCampaign(0,false,false,false,false,true,false) == 2, "farm return restores GhostLine");
    Check(SavedCampaign(0,true,false,false,false,false,true) == 2, "GhostLine checkpoint outranks stale Relay presence");
    Check(IsAdjacentPortal(30,31,31) && IsAdjacentPortal(31,30,31), "31-map GhostLine final approach and return remain traversable");
    Check(!IsAdjacentPortal(31,1,31), "final hub shortcut is explicit, not ordinary adjacency");
    for (const int MapCount : {18,31})
        for (int From = -1; From <= MapCount + 1; ++From)
            for (bool Forward : {false,true}) for (bool Complete : {false,true})
            {
                const int Target = PortalTarget(From,Forward,MapCount,Complete);
                if (From < 1 || From > MapCount || (!Forward && From == 1))
                    Check(Target == -1, "no out-of-map portal destination");
                else if (Forward && From == MapCount)
                    Check(Target == (Complete ? 1 : -1), "final return to hub requires explicit completion permission");
                else Check(Target == (Forward ? From + 1 : From - 1), "ordinary forward/backward portals retain linear route");
            }
    Check(PortalTarget(1,true,0,true) == -1 && PortalTarget(1,true,1,true) == -1, "invalid/single-map campaign cannot produce a self-loop");
    std::printf("relay session core: %d checks passed\n", Checks);
}
