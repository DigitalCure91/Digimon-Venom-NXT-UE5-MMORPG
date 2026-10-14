#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

/** Bounded editor artwork residency. Selection wins over viewport proximity. */
namespace DigimonVenomNXTEditorMapPreviewCore
{
    struct Candidate { int Index = 0; double DistanceSquared = 0.; bool Selected = false; };

    inline double DistanceToMap(double ViewX, double ViewY, double CenterX, double CenterY, double HalfWidth, double HalfHeight)
    {
        const double X = std::max(0., std::abs(ViewX - CenterX) - std::max(0., HalfWidth));
        const double Y = std::max(0., std::abs(ViewY - CenterY) - std::max(0., HalfHeight));
        return X * X + Y * Y;
    }

    inline std::vector<int> Choose(std::vector<Candidate> Maps, std::size_t Limit = 4)
    {
        Maps.erase(std::remove_if(Maps.begin(), Maps.end(), [](const Candidate& Map)
            { return !std::isfinite(Map.DistanceSquared) || Map.DistanceSquared < 0.; }), Maps.end());
        std::sort(Maps.begin(), Maps.end(), [](const Candidate& A, const Candidate& B)
        {
            if (A.Selected != B.Selected) return A.Selected;
            if (A.DistanceSquared != B.DistanceSquared) return A.DistanceSquared < B.DistanceSquared;
            return A.Index < B.Index;
        });
        std::vector<int> Result;
        // Selection can be far away from the camera. Only its nearest additional
        // habitats are useful; never decode the complete 500-map world overview.
        for (const Candidate& Map : Maps)
        {
            if (Result.size() >= Limit) break;
            Result.push_back(Map.Index);
        }
        return Result;
    }
}
