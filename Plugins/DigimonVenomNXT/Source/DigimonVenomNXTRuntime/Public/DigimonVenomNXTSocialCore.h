#pragma once

/** Engine-independent authorization rules shared by the server and executable regression probe. */
namespace DigimonVenomNXTSocialCore
{
    constexpr int MaxFriends = 200;
    constexpr int MaxIgnored = 200;
    constexpr int MaxFriendRequests = 50;
    constexpr int MaxClanMembers = 100;
    constexpr int MaxClanInvitations = 100;
    constexpr int MaxAccountClanInvitations = 16;
    constexpr int Member = 1;
    constexpr int Officer = 2;
    constexpr int Leader = 3;
    constexpr bool ValidRole(int Role) { return Role >= Member && Role <= Leader; }
    constexpr bool CanInvite(int Role) { return Role == Officer || Role == Leader; }
    constexpr bool CanEditDetails(int Role) { return CanInvite(Role); }
    constexpr bool CanKick(int ActorRole, int TargetRole, bool bSameAccount)
    {
        return !bSameAccount && ValidRole(TargetRole) &&
            ((ActorRole == Leader && TargetRole != Leader) || (ActorRole == Officer && TargetRole == Member));
    }
    constexpr bool CanChangeRole(int ActorRole, int TargetRole, int DesiredRole, bool bSameAccount)
    {
        return !bSameAccount && ActorRole == Leader &&
            ((TargetRole == Member && DesiredRole == Officer) || (TargetRole == Officer && DesiredRole == Member));
    }
    constexpr bool CanLeave(int Role) { return Role == Member || Role == Officer; }
}
