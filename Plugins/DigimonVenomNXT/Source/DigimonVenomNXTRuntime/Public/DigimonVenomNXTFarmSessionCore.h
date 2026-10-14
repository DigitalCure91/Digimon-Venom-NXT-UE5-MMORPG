#pragma once

#include <cstdint>

/** Engine-independent privacy/ordering rules shared by replication and local rendering. */
namespace DigimonVenomNXTFarmSessionCore
{
    inline constexpr int MaximumPrivateSessions = 4096;
    struct Origin { double X; double Y; };
    inline Origin OriginForSlot(int Slot)
    {
        return { static_cast<double>(Slot % 64) * 10000.0, -50000.0 - static_cast<double>(Slot / 64) * 10000.0 };
    }

    inline bool MayObserve(bool Authenticated, bool OwnTamer, bool ViewerInFarm, bool SubjectInFarm, bool SamePublicMap)
    {
        return Authenticated && (OwnTamer || (!ViewerInFarm && !SubjectInFarm && SamePublicMap));
    }

    inline bool AcceptRevision(std::uint64_t Applied, std::uint64_t Incoming)
    {
        return Incoming >= Applied;
    }
}
