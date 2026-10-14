#pragma once

#include "DigimonVenomNXTFarmCollisionData.h"
#include "DigimonVenomNXTCollisionCore.h"
#include <algorithm>
#include <cmath>
#include <limits>

/** The same immutable collision on server, local movement prediction and residents.
 * Pixel X/Y run opposite world X/Y: mirrored X and +90-roll Paper2D sprite.
 * Source-image up becomes world +Y, exactly as in the rendered island.
 * Every occupied grid cell is fully inside the source artwork's reference shore.
 */
namespace DigimonVenomNXTFarmCore
{
    inline constexpr double WorldWidth = 6400.0;
    inline constexpr double WorldHeight = WorldWidth * 941.0 / 1672.0;
    inline constexpr double PlayerRadius = 48.0;
    inline constexpr double ResidentRadius = 38.0;
    inline constexpr double SpawnX = 0.0;
    inline constexpr double SpawnY = 250.0;
    inline constexpr double CellWidth = WorldWidth / DigimonVenomNXTFarmCollisionData::GridWidth;
    inline constexpr double CellHeight = WorldHeight / DigimonVenomNXTFarmCollisionData::GridHeight;
    struct Point { double X = SpawnX; double Y = SpawnY; };

    inline bool CellWalkable(int X, int Y)
    {
        using namespace DigimonVenomNXTFarmCollisionData;
        if (X < 0 || Y < 0 || X >= GridWidth || Y >= GridHeight) return false;
        const int Index = Y * GridWidth + X;
        return (Bits[Index / 8] & (1u << (7 - Index % 8))) != 0;
    }

    inline DigimonVenomNXTCollisionCore::Grid CollisionGrid()
    {
        return {DigimonVenomNXTFarmCollisionData::GridWidth, DigimonVenomNXTFarmCollisionData::GridHeight,
            DigimonVenomNXTFarmCollisionData::Bits, sizeof(DigimonVenomNXTFarmCollisionData::Bits), WorldWidth, WorldHeight};
    }

    inline DigimonVenomNXTCollisionCore::Point ImagePoint(double LocalX, double LocalY)
    {
        return {WorldWidth * 0.5 - LocalX, WorldHeight * 0.5 - LocalY};
    }

    inline bool IsWalkable(double LocalX, double LocalY, double Radius = 0.0)
    {
        return DigimonVenomNXTCollisionCore::IsWalkable(CollisionGrid(), ImagePoint(LocalX, LocalY), Radius);
    }

    inline bool IsSegmentWalkable(double AX, double AY, double BX, double BY, double Radius = 0.0)
    {
        // Exact swept disk, shared with public maps and both private campaigns.
        // No sparse travel samples can miss a shoreline corner between frames.
        return DigimonVenomNXTCollisionCore::IsSegmentWalkable(CollisionGrid(), ImagePoint(AX, AY), ImagePoint(BX, BY), Radius);
    }

    inline Point FindSafePoint(double X, double Y, double Radius = 0.0)
    {
        if (IsWalkable(X, Y, Radius)) return {X, Y};
        // Invalid saved positions always recover to a known grass spawn. This
        // keeps shoreline migration independent of any distant field map origin.
        if (!std::isfinite(X) || !std::isfinite(Y) || !std::isfinite(Radius) || Radius < 0 ||
            !IsWalkable(SpawnX, SpawnY, Radius)) return {SpawnX, SpawnY};
        Point Best{SpawnX, SpawnY};
        double BestDistance = std::hypot(X - Best.X, Y - Best.Y);
        for (int GridY = 0; GridY < DigimonVenomNXTFarmCollisionData::GridHeight; GridY += 2)
        {
            for (int GridX = 0; GridX < DigimonVenomNXTFarmCollisionData::GridWidth; GridX += 2)
            {
                if (!CellWalkable(GridX, GridY)) continue;
                const Point Candidate{WorldWidth * 0.5 - (GridX + 0.5) * CellWidth,
                    WorldHeight * 0.5 - (GridY + 0.5) * CellHeight};
                const double Distance = std::hypot(X - Candidate.X, Y - Candidate.Y);
                if (Distance >= BestDistance || !IsWalkable(Candidate.X, Candidate.Y, Radius)) continue;
                Best = Candidate; BestDistance = Distance;
            }
        }
        return Best;
    }
}
