#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCampaignBattleCore.h"
#include <cstdlib>
#include <iostream>
#include <utility>

using namespace DigimonVenomNXTCampaignBattleCore;
int main()
{
    int Checks = 0;
    auto Require = [&Checks](bool Value, const char* Message)
    {
        ++Checks;
        if (!Value) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    };
    const std::array<FinalUnit, 3> Ghost = {{{"diaboromon",99,0,true},
        {"chaosdramon",99,0,true},{"machinedramon",99,0,true}}};
    auto Valid = [](const std::array<FinalUnit, 3>& Team)
    { return ValidFinalRoster(2,31,"ghost_final_regent",Team,3,0); };
    Require(Valid(Ghost), "Authored Super Xros Wars normal Mega finale accepted");
    // Promotion / resume ordering must not alter identity or award eligibility.
    for (int I = 0; I < 3; ++I)
        for (int J = 0; J < 3; ++J)
        {
            auto Restored = Ghost;
            std::swap(Restored[I],Restored[J]);
            Require(Valid(Restored), "Reordered saved roster accepted");
        }
    for (int Slot = 0; Slot < 3; ++Slot)
    {
        auto Edited = Ghost;
        Edited[Slot].Species = Ghost[(Slot+1)%3].Species;
        Require(!Valid(Edited), "Duplicated final partner rejected");
        Edited = Ghost; Edited[Slot].Species = "wargreymon";
        Require(!Valid(Edited), "Different installed Mega cannot replace authored member");
        Edited = Ghost; Edited[Slot].Species.clear();
        Require(!Valid(Edited), "Missing roster identity rejected");
        Edited = Ghost; Edited[Slot].Mega = false;
        Require(!Valid(Edited), "Non-Mega rejected");
        for (int Level : {1,98,100,200})
        {
            Edited = Ghost; Edited[Slot].Level = Level;
            Require(!Valid(Edited), "Checkpoint level cannot change");
        }
        for (int Variant : {-1,1,2,3,4,255})
        {
            Edited = Ghost; Edited[Slot].Variant = Variant;
            Require(!Valid(Edited), "Checkpoint variety must match source Normal roster");
        }
    }
    for (int Active = 0; Active <= 6; ++Active)
        for (int Bench = 0; Bench <= 3; ++Bench)
            Require(ValidFinalRoster(2,31,"ghost_final_regent",Ghost,Active,Bench) == (Active == 3 && Bench == 0),
                "Opponent finale is exactly three active and no extra reserves");
    for (int Campaign : {-1,0,1,3,255})
        Require(!ValidFinalRoster(Campaign,31,"ghost_final_regent",Ghost,3,0), "Wrong campaign cannot adopt GhostLine checkpoint");
    for (int Map : {0,1,18,30,32})
        Require(!ValidFinalRoster(2,Map,"ghost_final_regent",Ghost,3,0), "Final cannot be started on another map");
    for (const char* NPC : {"", "ghost_30_tamer", "ds_final_triad", "relay_champion"})
        Require(!ValidFinalRoster(2,31,NPC,Ghost,3,0), "Wrong NPC cannot adopt final roster");
    for (int Configured = -2; Configured <= 9; ++Configured)
    {
        Require(ActiveSlots(Configured,false,true)==3, "Finale remains 3 active for every project setting");
        Require(ActiveSlots(Configured,true,false)==std::clamp(Configured,1,3), "Season active policy preserved");
        Require(ActiveSlots(Configured,false,false)==std::clamp(Configured,1,6), "Ordinary party active policy preserved");
    }
    const std::array<FinalUnit, 3> Chronicles = {{{"alphamon",100,1,true},
        {"omnimon",100,1,true},{"imperialdramonpaladinmode",100,1,true}}};
    Require(ValidFinalRoster(1,18,"ds_final_triad",Chronicles,3,0), "Chronicles retains its level100 Paradox finale");
    Require(!ValidFinalRoster(2,31,"ghost_final_regent",Chronicles,3,0), "World DS roster cannot settle Super Xros Wars");
    Require(!ValidFinalRoster(1,18,"ds_final_triad",Ghost,3,0), "GhostLine roster cannot settle Chronicles");
    std::cout << "Campaign battle policy: " << Checks << " checks passed\n";
}
