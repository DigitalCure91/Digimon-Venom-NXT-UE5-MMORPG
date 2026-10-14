#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTCollisionCore.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

namespace
{
    int Checks = 0;
    void Require(bool Condition, const char* Message)
    {
        ++Checks;
        if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    }
    void Block(std::vector<std::uint8_t>& Bits, int Width, int X, int Y)
    {
        const int Index = Y * Width + X;
        Bits[Index / 8] &= static_cast<std::uint8_t>(~(1u << (7 - Index % 8)));
    }
    // Independent disk oracle; intentionally not implemented using core helpers.
    bool OracleDisk(const DigimonVenomNXTCollisionCore::Grid& G, DigimonVenomNXTCollisionCore::Point P, double Radius)
    {
        if (P.X - Radius < 0 || P.Y - Radius < 0 || P.X + Radius >= G.WorldWidth || P.Y + Radius >= G.WorldHeight) return false;
        const double CW = G.WorldWidth / G.Width, CH = G.WorldHeight / G.Height;
        for (int Y = 0; Y < G.Height; ++Y)
            for (int X = 0; X < G.Width; ++X)
            {
                const int I = Y * G.Width + X;
                if (G.Bits[I / 8] & (1u << (7 - I % 8))) continue;
                const double DX = std::max({X * CW - P.X, P.X - (X + 1) * CW, 0.0});
                const double DY = std::max({Y * CH - P.Y, P.Y - (Y + 1) * CH, 0.0});
                if (DX * DX + DY * DY <= Radius * Radius) return false;
            }
        return true;
    }
}

int main()
{
    using namespace DigimonVenomNXTCollisionCore;
    std::vector<std::uint8_t> Bits(100 * 100 / 8, 255);
    Grid G{100,100,Bits.data(),Bits.size(),100.0,100.0};
    Require(Valid(G), "valid source-resolution mask accepted");
    Require(IsWalkable(G,{50.0,50.0},34.0), "full footprint on open ground accepted");
    Require(!IsWalkable(G,{5.0,50.0},6.0), "full footprint may not leave artwork");
    Require(IsSegmentWalkable(G,{10,10},{90,90},1), "clear diagonal accepted");
    Block(Bits,100,50,50);
    Require(IsWalkable(G,{20,20},1) && IsWalkable(G,{80,80},1), "thin-wall endpoints separately valid");
    Require(!IsSegmentWalkable(G,{20,20},{80,80},1), "exact sweep catches one-pixel wall between endpoints");
    Require(!IsSegmentWalkable(G,{0.5,49.999},{99.5,49.999},0.01), "sub-pixel tangent collision is not missed between movement samples");
    Require(IsSegmentWalkable(G,{1,48},{98,48},1), "safe path parallel to a wall remains traversable");
    Require(!IsWalkable(G,{50.5,50.5},0), "blocked pixel rejects zero-radius point");
    // Blocked cells are closed rectangles: touching any of their four sides
    // must agree even when the broad-phase lower bound is exactly a cell edge.
    // Radius zero also exercises point/segment contact on the shared boundary.
    for (const double Radius : {0.0, 1.0})
    {
        const Point Tangencies[] = {{50.0 - Radius,50.5}, {51.0 + Radius,50.5},
                                    {50.5,50.0 - Radius}, {50.5,51.0 + Radius}};
        const Point Outward[] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        for (int Side = 0; Side < 4; ++Side)
        {
            const Point P = Tangencies[Side];
            const Point Along = Side < 2 ? Point{0,4} : Point{4,0};
            const Point A{P.X - Along.X,P.Y - Along.Y}, B{P.X + Along.X,P.Y + Along.Y};
            Require(!IsWalkable(G,P,Radius), "disk tangent to each blocked-cell side is rejected symmetrically");
            Require(!IsSegmentWalkable(G,A,B,Radius), "sweep tangent to each blocked-cell side is rejected");
            Require(!IsSegmentWalkable(G,B,A,Radius), "reverse tangent sweep is also rejected");
            Require(!OracleDisk(G,P,Radius), "independent closed-cell oracle confirms exact tangent rejection");
            const Point Gap{Outward[Side].X * .001,Outward[Side].Y * .001};
            Require(IsWalkable(G,{P.X+Gap.X,P.Y+Gap.Y},Radius), "positive gap beyond each tangent permits the disk");
            Require(IsSegmentWalkable(G,{A.X+Gap.X,A.Y+Gap.Y},{B.X+Gap.X,B.Y+Gap.Y},Radius), "positive gap permits parallel sweep");
            Require(IsSegmentWalkable(G,{B.X+Gap.X,B.Y+Gap.Y},{A.X+Gap.X,A.Y+Gap.Y},Radius), "positive gap permits reverse parallel sweep");
        }
        Require(IsWalkable(G,{Radius,20},Radius), "canvas left edge retains inclusive footprint policy");
        Require(IsWalkable(G,{20,Radius},Radius), "canvas top edge retains inclusive footprint policy");
        Require(!IsWalkable(G,{100-Radius,20},Radius), "canvas right edge retains exclusive footprint policy");
        Require(!IsWalkable(G,{20,100-Radius},Radius), "canvas bottom edge retains exclusive footprint policy");
    }
    Require(IsWalkable(G,{30.5,30.5},10), "rim-gap regression begins on clear ground");
    Block(Bits,100,34,39);
    Require(!IsWalkable(G,{30.5,30.5},10), "obstacle between the old nine probes is still inside the disk");
    const double NaN = std::numeric_limits<double>::quiet_NaN();
    const double Inf = std::numeric_limits<double>::infinity();
    Require(!IsWalkable(G,{NaN,30},1) && !IsWalkable(G,{30,Inf},1), "nonfinite coordinates fail closed");
    Require(!IsWalkable(G,{30,30},-1) && !IsWalkable(G,{30,30},NaN), "invalid footprint fails closed");
    Require(!IsSegmentWalkable(G,{30,30},{Inf,30},1), "nonfinite segment rejected before integer conversion");
    Grid Bad = G; Bad.ByteCount--;
    Require(!Valid(Bad) && !IsWalkable(Bad,{30,30},1), "truncated grid rejected");
    Bad = G; Bad.ByteCount++;
    Require(!Valid(Bad), "mismatched grid stride or byte count rejected");
    Bad = G; Bad.WorldWidth = Inf;
    Require(!Valid(Bad), "invalid image scale rejected");
    Bad = G; Bad.Width = 0;
    Require(!Valid(Bad), "empty grid fails closed");
    Bad = G; Bad.Bits = nullptr;
    Require(!Valid(Bad), "missing bit storage fails closed");

    // Non-square source pixels must be tested in physical world units.
    std::vector<std::uint8_t> Sparse(32 * 24 / 8, 255);
    for (const auto P : {Point{12,10},Point{13,10},Point{20,15},Point{6,18}})
        Block(Sparse,32,static_cast<int>(P.X),static_cast<int>(P.Y));
    const Grid Anisotropic{32,24,Sparse.data(),Sparse.size(),96.0,48.0};
    std::mt19937 Random(0x1982);
    std::uniform_real_distribution<double> X(2,94), Y(2,46), R(0,1.8);
    int Accepted = 0, Rejected = 0;
    for (int Trial = 0; Trial < 600; ++Trial)
    {
        const Point A{X(Random),Y(Random)}, B{X(Random),Y(Random)};
        const double Radius = R(Random);
        Require(IsWalkable(Anisotropic,A,Radius) == OracleDisk(Anisotropic,A,Radius), "disk oracle matches unequal cell aspect");
        const bool Clear = IsSegmentWalkable(Anisotropic,A,B,Radius);
        Require(Clear == IsSegmentWalkable(Anisotropic,B,A,Radius), "collision is direction symmetric");
        if (!Clear) { ++Rejected; continue; }
        ++Accepted;
        for (int Sample = 0; Sample <= 30; ++Sample)
        {
            const double T = Sample / 30.0;
            Require(OracleDisk(Anisotropic,{A.X+(B.X-A.X)*T,A.Y+(B.Y-A.Y)*T},Radius), "accepted sweep passes independent dense footprint samples");
        }
    }
    Require(Accepted > 150 && Rejected > 100, "fuzz coverage includes open and blocked movement");
    std::cout << "Exact image collision: " << Checks << " checks passed\n";
}
