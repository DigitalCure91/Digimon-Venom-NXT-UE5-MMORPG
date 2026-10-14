#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTNameplateCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>

namespace
{
    int Checks = 0;
    void Require(bool Condition, const char* Message)
    {
        ++Checks;
        if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    }
}

int main()
{
    using namespace DigimonVenomNXTNameplateCore;
    Require(ShouldShow(true, true), "active tamer in the same public habitat has a nameplate");
    Require(!ShouldShow(false, true), "hidden or despawned actors do not leave labels");
    Require(!ShouldShow(true, false), "remote labels cannot leak between habitats or private instances");
    Require(!ShouldShow(false, false), "inactive off-map rivals remain hidden");

    // Exercise the entire camera range including the former 55% visibility
    // boundary. Moving the actor's sprite head beyond the top of the screen must
    // not hide its plate while even the bottom of the sprite remains in view.
    for (int Percent = 0; Percent <= 100; ++Percent)
    {
        const double OrthoWidth = 4800.0 - 3700.0 * Percent / 100.0;
        const double PixelsPerUnit = 1920.0 / OrthoWidth;
        const double HalfWidth = 24.0 * PixelsPerUnit;
        const double HalfHeight = 48.0 * PixelsPerUnit;
        Require(ShouldShow(true, true) &&
            IntersectsViewport(960 - HalfWidth, 540 - HalfHeight, 960 + HalfWidth, 540 + HalfHeight, 1920, 1080),
            "in-view remote player or AI remains visible throughout camera zoom");
        const Anchor Center = FitAnchor(960, 540 - HalfHeight - 7, 1920, 1080);
        Require(Center.Visible && Center.X == 960 && Center.Y == 540 - HalfHeight - 7,
            "normal labels stay anchored to the sprite with a fixed screen-space gap");
        Require(IntersectsViewport(-HalfWidth, -HalfHeight, HalfWidth, HalfHeight, 1920, 1080),
            "partly visible sprite at a screen corner retains its nameplate at every zoom");
        const Anchor Corner = FitAnchor(0, -HalfHeight - 7, 1920, 1080, 46);
        Require(Corner.Visible && Corner.X == 109 && Corner.Y == 50,
            "corner label and equipped title remain readable with a fixed screen-space size");
        Require(!IntersectsViewport(1921, 540 - HalfHeight, 1921 + 2 * HalfWidth, 540 + HalfHeight, 1920, 1080),
            "fully offscreen sprite never leaves a label pinned to the viewport edge");
    }

    const Anchor Above = FitAnchor(960, -180, 1920, 1080);
    Require(Above.Visible && Above.X == 960 && Above.Y == 32, "visible sprite with its head above screen keeps its label inset");
    const Anchor BottomRight = FitAnchor(2100, 1300, 1920, 1080);
    Require(BottomRight.Visible && BottomRight.X == 1811 && BottomRight.Y == 1076, "complete label rectangle fits the bottom-right corner");
    const Anchor Left = FitAnchor(-100, 540, 1920, 1080);
    Require(Left.Visible && Left.X == 109 && Left.Y == 540, "label does not disappear past the left edge");
    const Anchor Narrow = FitAnchor(-200, -50, 160, 90);
    Require(Narrow.Visible && Narrow.X == 80 && Narrow.Y == 32, "narrow local viewport centers the label without inverted clamp bounds");
    const Anchor Tiny = FitAnchor(500, 500, 20, 10);
    Require(Tiny.Visible && Tiny.X == 10 && Tiny.Y == 19, "tiny viewport preserves the label center");

    Require(IntersectsViewport(-10, 500, 0, 550, 1920, 1080), "leftmost sprite edge touching the view remains visible");
    Require(IntersectsViewport(1920, 500, 1930, 550, 1920, 1080), "rightmost viewport boundary remains visible");
    Require(IntersectsViewport(900, -30, 940, 0, 1920, 1080), "sprite touching the top boundary remains visible");
    Require(IntersectsViewport(900, 1080, 940, 1120, 1920, 1080), "sprite touching the bottom boundary remains visible");
    Require(!IntersectsViewport(-10, 500, -0.01, 550, 1920, 1080), "sprite fully past the left boundary is hidden");
    Require(!IntersectsViewport(1920.01, 500, 1930, 550, 1920, 1080), "sprite fully past the right boundary is hidden");
    Require(!IntersectsViewport(900, -30, 940, -0.01, 1920, 1080), "sprite fully past the top boundary is hidden");
    Require(!IntersectsViewport(900, 1080.01, 940, 1120, 1920, 1080), "sprite fully past the bottom boundary is hidden");
    Require(!IntersectsViewport(100, 50, 90, 100, 1920, 1080), "inverted horizontal bounds cannot display a label");
    Require(!IntersectsViewport(100, 150, 110, 100, 1920, 1080), "inverted vertical bounds cannot display a label");
    Require(!IntersectsViewport(100, 50, 110, 100, 0, 1080), "uninitialized viewport does not show a remote label");
    const double NaN = std::numeric_limits<double>::quiet_NaN();
    const double Infinity = std::numeric_limits<double>::infinity();
    Require(!IntersectsViewport(NaN, 50, 110, 100, 1920, 1080), "invalid silhouette coordinates do not expose a label");
    Require(!IntersectsViewport(100, 50, Infinity, 100, 1920, 1080), "infinite silhouette bounds do not expose a label");
    Require(!FitAnchor(10, 10, 0, 100).Visible, "uninitialized viewport geometry cannot display misplaced labels");
    Require(!FitAnchor(NaN, 10, 1920, 1080).Visible, "invalid projection coordinates cannot display labels");
    Require(!FitAnchor(10, 10, Infinity, 100).Visible, "infinite viewport geometry cannot display labels");
    const Anchor Titled = FitAnchor(960, 45, 1920, 1080, 46);
    Require(Titled.Visible && Titled.Y == 50, "remote equipped title stays visible when its original top line would clip");
    Require(!FitAnchor(960, 400, 1920, 1080, NaN).Visible, "invalid title height cannot bypass viewport checks");
    Require(!FitAnchor(960, 400, 1920, 1080, 0).Visible, "empty label height does not display a label");
    std::cout << "Nameplate core: " << Checks << " checks passed\n";
}
