#pragma once
#include <cstdint>
#include <cmath>
#include "DigimonVenomNXTCampaignCore.h"
/** Shared native/testable bounds for private campaign sessions. Farm and public cells never overlap. */
namespace DigimonVenomNXTRelaySessionCore
{
    constexpr int MaximumPrivateSessions = 4096;
    constexpr double CellSpacing = 50000.0;
    constexpr double InteractionRadius = 260.0;
    struct Origin { double X; double Y; };
    inline Origin OriginForSlot(int Slot)
    { return {1000000.0 + (Slot % 64) * CellSpacing, 1000000.0 + (Slot / 64) * CellSpacing}; }
    inline bool AcceptRevision(std::uint64_t Applied, std::uint64_t Incoming) { return Incoming >= Applied; }
    inline bool MayObserve(bool Authenticated, bool OwnTamer, bool ViewerPrivate, bool SubjectPrivate, bool SamePublicMap)
    { return Authenticated && (OwnTamer || (!ViewerPrivate && !SubjectPrivate && SamePublicMap)); }
    /** Stable wire identities: Relay=0, ParadoxChronicles=1, GhostLine=2. */
    inline bool ValidCampaign(int Campaign) { return DigimonVenomNXTCampaignCore::ValidCampaign(Campaign); }
    inline bool MayEnterCampaign(int Requested, int Current, bool Inside, bool ActiveBattle,
        bool SeasonCheckpoint, bool RelayCheckpoint, bool ChroniclesCheckpoint, bool GhostLineCheckpoint = false)
    {
        if (!ValidCampaign(Requested) || ActiveBattle || SeasonCheckpoint) return false;
        const bool Checkpoints[] = {RelayCheckpoint, ChroniclesCheckpoint, GhostLineCheckpoint};
        for (int Campaign = 0; Campaign < DigimonVenomNXTCampaignCore::CampaignCount; ++Campaign)
            if (Campaign != Requested && Checkpoints[Campaign]) return false;
        return !(Inside && Current != Requested && (RelayCheckpoint || ChroniclesCheckpoint || GhostLineCheckpoint));
    }
    /** -1 means public; -2 means conflicting pending decisions, requiring a safe refusal. */
    inline int SavedCampaign(int Preferred, bool RelayInside, bool ChroniclesInside,
        bool RelayCheckpoint, bool ChroniclesCheckpoint, bool GhostLineInside = false, bool GhostLineCheckpoint = false)
    {
        const bool Checkpoints[] = {RelayCheckpoint, ChroniclesCheckpoint, GhostLineCheckpoint};
        int PendingCampaign = -1;
        for (int Campaign = 0; Campaign < DigimonVenomNXTCampaignCore::CampaignCount; ++Campaign)
            if (Checkpoints[Campaign])
            {
                if (PendingCampaign >= 0) return -2;
                PendingCampaign = Campaign;
            }
        if (PendingCampaign >= 0) return PendingCampaign;
        const bool Inside[] = {RelayInside, ChroniclesInside, GhostLineInside};
        if (ValidCampaign(Preferred) && Inside[Preferred]) return Preferred;
        if (GhostLineInside) return 2;
        if (ChroniclesInside) return 1;
        return RelayInside ? 0 : -1;
    }
    inline bool IsAdjacentPortal(int From, int To, int MaximumMapId = 18)
    { return MaximumMapId >= 1 && From >= 1 && From <= MaximumMapId && To >= 1 && To <= MaximumMapId && std::abs(From - To) == 1; }
    /** Authored linear routes may expose a completed-finale return portal to their hub. */
    inline int PortalTarget(int From, bool Forward, int MaximumMapId = 18, bool FinalReturnToHub = false)
    {
        if (MaximumMapId < 1 || From < 1 || From > MaximumMapId) return -1;
        if (Forward && From == MaximumMapId) return FinalReturnToHub && MaximumMapId > 1 ? 1 : -1;
        const int To = Forward ? From + 1 : From - 1;
        return IsAdjacentPortal(From, To, MaximumMapId) ? To : -1;
    }
    inline bool WithinInteraction(double DX, double DY)
    { return std::isfinite(DX) && std::isfinite(DY) && DX * DX + DY * DY <= InteractionRadius * InteractionRadius; }
}
