#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTFieldMovementCore.h"
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCollisionCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

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
    using namespace DigimonVenomNXTCollisionCore;
    using DigimonVenomNXTFieldMovementCore::StepDistance;
    constexpr int Width = 128, Height = 96;
    std::vector<std::uint8_t> Bits((Width * Height + 7) / 8, 0);
    // A deliberately asymmetric L-shaped walkway. The right-hand bend is valid
    // ground, while the short straight-ahead continuation ends at a real wall.
    for (int Y = 0; Y < Height; ++Y)
        for (int X = 0; X < Width; ++X)
            if ((X >= 10 && X <= 105 && Y >= 40 && Y <= 59) ||
                (X >= 86 && X <= 105 && Y >= 10 && Y <= 59))
            {
                const int Index = Y * Width + X;
                Bits[Index / 8] |= static_cast<std::uint8_t>(1u << (7 - Index % 8));
            }
    const Grid Surface{Width, Height, Bits.data(), Bits.size(), Width, Height};
    constexpr double Radius = 2.0;
    const Point Approach{80, 50};
    for (const double Rate : {30.0, 60.0, 120.0, 240.0})
    {
        const double Step = StepDistance(240.0, 1.0 / Rate);
        Require(IsSegmentWalkable(Surface, Approach, {Approach.X + Step, Approach.Y}, Radius),
            "actual next frame reaches walkable ground approaching the bend");
        Require(!IsSegmentWalkable(Surface, Approach, {Approach.X + 45.0, Approach.Y}, Radius),
            "regression fixture reproduces the old premature 45-unit stop");
    }

    Point Position = Approach;
    for (int Step = 0; Step < 4; ++Step)
    {
        const Point Next{Position.X + StepDistance(240.0, 1.0 / 60.0), Position.Y};
        Require(IsSegmentWalkable(Surface, Position, Next, Radius), "player can reach the real corner");
        Position = Next;
    }
    for (int Step = 0; Step < 8; ++Step)
    {
        const Point Next{Position.X, Position.Y - StepDistance(240.0, 1.0 / 60.0)};
        Require(IsSegmentWalkable(Surface, Position, Next, Radius), "player can turn and traverse the vertical walkway");
        Position = Next;
    }
    Require(Position.X == 96.0 && Position.Y == 18.0, "reachable destination is no longer blocked by a distant wall");

    const Point LastAccepted{70, 50}, AcrossCorner{96, 24};
    Require(IsWalkable(Surface, LastAccepted, Radius) && IsWalkable(Surface, AcrossCorner, Radius),
        "corner shortcut has two valid endpoints");
    Require(!IsSegmentWalkable(Surface, LastAccepted, AcrossCorner, Radius),
        "authority rejects diagonal wall cutting even when destination is valid");
    Point Authority = LastAccepted;
    if (IsSegmentWalkable(Surface, Authority, AcrossCorner, Radius)) Authority = AcrossCorner;
    Require(Authority.X == LastAccepted.X && Authority.Y == LastAccepted.Y,
        "rejected server movement preserves the last valid position");
    Require(IsSegmentWalkable(Surface, LastAccepted, {96, 50}, Radius) &&
        IsSegmentWalkable(Surface, {96, 50}, AcrossCorner, Radius),
        "legitimate route around the same corner remains valid");

    Require(StepDistance(240.0, 0.0) == 0.0 && StepDistance(-1.0, 0.1) == 0.0 &&
        StepDistance(240.0, -0.1) == 0.0, "zero and invalid time/speed do not invent movement");
    Require(StepDistance(std::numeric_limits<double>::infinity(), 0.1) == 0.0 &&
        StepDistance(240.0, std::numeric_limits<double>::quiet_NaN()) == 0.0,
        "nonfinite timing cannot bypass movement prediction");
    std::cout << "Field movement regression core: " << Checks << " checks passed\n";
}
