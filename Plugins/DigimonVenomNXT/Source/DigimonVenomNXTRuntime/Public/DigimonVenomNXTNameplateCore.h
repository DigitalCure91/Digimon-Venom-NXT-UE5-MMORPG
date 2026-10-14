#pragma once

#include <algorithm>
#include <cmath>

/** Viewer-local, screen-space rules. Camera zoom never hides an in-view identity. */
namespace DigimonVenomNXTNameplateCore
{
    inline bool ShouldShow(bool Active, bool SameMap)
    {
        return Active && SameMap;
    }

    /** Test the sprite, not the label rectangle: a visible tamer keeps its name at screen edges. */
    inline bool IntersectsViewport(double Left, double Top, double Right, double Bottom,
        double ViewWidth, double ViewHeight)
    {
        return std::isfinite(Left) && std::isfinite(Top) && std::isfinite(Right) &&
            std::isfinite(Bottom) && std::isfinite(ViewWidth) && std::isfinite(ViewHeight) &&
            ViewWidth > 0.0 && ViewHeight > 0.0 && Left <= Right && Top <= Bottom &&
            Right >= 0.0 && Left <= ViewWidth && Bottom >= 0.0 && Top <= ViewHeight;
    }

    struct Anchor
    {
        double X = 0.0;
        double Y = 0.0;
        bool Visible = false;
    };

    /** Coordinates address the plate's bottom-center; every visible label stays inside the view. */
    inline Anchor FitAnchor(double X, double Y, double ViewWidth, double ViewHeight, double PlateHeight = 28.0)
    {
        if (!std::isfinite(X) || !std::isfinite(Y) || !std::isfinite(ViewWidth) ||
            !std::isfinite(ViewHeight) || !std::isfinite(PlateHeight) || PlateHeight <= 0.0 ||
            ViewWidth <= 0.0 || ViewHeight <= 0.0) return {};
        constexpr double HalfWidth = 105.0;
        const double Height = PlateHeight;
        constexpr double Margin = 4.0;
        // Even an unusually small viewport must not hide a visible tamer. If the
        // plate cannot fit entirely, keep its center in view instead of clamping
        // against inverted bounds; normal viewports retain a four-pixel inset.
        const double FitX = ViewWidth >= 2.0 * (HalfWidth + Margin)
            ? std::clamp(X, HalfWidth + Margin, ViewWidth - HalfWidth - Margin) : ViewWidth * 0.5;
        const double FitY = ViewHeight >= Height + 2.0 * Margin
            ? std::clamp(Y, Height + Margin, ViewHeight - Margin) : (ViewHeight + Height) * 0.5;
        return {FitX, FitY, true};
    }
}
