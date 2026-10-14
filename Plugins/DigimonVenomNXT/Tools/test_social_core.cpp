#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTSocialCore.h"
#include <cassert>
#include <iostream>

int main()
{
    // Expected authorization matrix: member/officer/leader; outsiders have no privileges.
    const bool invite[] = {false, false, true, true, false};
    const bool leave[] = {false, true, true, false, false};
    const bool kick[5][5] = {
        {false, false, false, false, false},
        {false, false, false, false, false},
        {false, true,  false, false, false},
        {false, true,  true,  false, false},
        {false, false, false, false, false}
    };
    int cases = 0;
    for (int actor = 0; actor < 5; ++actor)
    {
        assert(DigimonVenomNXTSocialCore::CanInvite(actor) == invite[actor]);
        assert(DigimonVenomNXTSocialCore::CanEditDetails(actor) == invite[actor]);
        assert(DigimonVenomNXTSocialCore::CanLeave(actor) == leave[actor]);
        cases += 3;
        for (int target = 0; target < 5; ++target)
        {
            assert(DigimonVenomNXTSocialCore::CanKick(actor, target, false) == kick[actor][target]);
            assert(!DigimonVenomNXTSocialCore::CanKick(actor, target, true)); // Never self-kick, including leader.
            cases += 2;
            for (int desired = 0; desired < 5; ++desired)
            {
                const bool allowed = actor == 3 && ((target == 1 && desired == 2) || (target == 2 && desired == 1));
                assert(DigimonVenomNXTSocialCore::CanChangeRole(actor, target, desired, false) == allowed);
                assert(!DigimonVenomNXTSocialCore::CanChangeRole(actor, target, desired, true));
                cases += 2;
            }
        }
    }
    assert(!DigimonVenomNXTSocialCore::CanInvite(-1)); assert(!DigimonVenomNXTSocialCore::CanInvite(255));
    assert(!DigimonVenomNXTSocialCore::CanKick(DigimonVenomNXTSocialCore::Leader, -1, false)); assert(!DigimonVenomNXTSocialCore::CanKick(DigimonVenomNXTSocialCore::Leader, 255, false));
    assert(!DigimonVenomNXTSocialCore::CanChangeRole(DigimonVenomNXTSocialCore::Leader, DigimonVenomNXTSocialCore::Member, DigimonVenomNXTSocialCore::Leader, false)); // Leadership uses confirmed transfer.
    assert(DigimonVenomNXTSocialCore::MaxFriends == 200 && DigimonVenomNXTSocialCore::MaxIgnored == 200 && DigimonVenomNXTSocialCore::MaxFriendRequests == 50);
    assert(DigimonVenomNXTSocialCore::MaxClanMembers == 100 && DigimonVenomNXTSocialCore::MaxAccountClanInvitations == 16);
    std::cout << "PASS: " << cases + 7 << " social/clan authorization and limit checks\n";
}
