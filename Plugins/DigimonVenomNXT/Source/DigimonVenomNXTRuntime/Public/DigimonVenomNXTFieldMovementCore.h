#pragma once

#include <cmath>

namespace DigimonVenomNXTFieldMovementCore
{
    /** Distance the movement component can request this frame. Terrain clearance
     * already includes the complete foot radius; adding a fixed lookahead here
     * would enlarge every wall and prevent valid turns in a narrow corridor.
     */
    inline double StepDistance(double Speed, double DeltaSeconds)
    {
        if (!std::isfinite(Speed) || !std::isfinite(DeltaSeconds) || Speed <= 0.0 || DeltaSeconds <= 0.0) return 0.0;
        const double Distance = Speed * DeltaSeconds;
        return std::isfinite(Distance) ? Distance : 0.0;
    }
}
