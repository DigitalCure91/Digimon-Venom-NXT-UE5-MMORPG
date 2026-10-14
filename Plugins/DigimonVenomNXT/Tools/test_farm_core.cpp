#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTFarmCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>

namespace
{
    int Checks = 0;
    void Require(bool Condition, const char* Message)
    {
        ++Checks;
        if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
    }
    DigimonVenomNXTFarmCore::Point Pixel(double X, double Y)
    {
        using namespace DigimonVenomNXTFarmCore;
        return {WorldWidth * (0.5 - X / 1672.0), WorldHeight * (0.5 - Y / 941.0)};
    }
    bool SafePixel(double X, double Y, double Radius = 0)
    {
        const auto P = Pixel(X,Y);
        return DigimonVenomNXTFarmCore::IsWalkable(P.X, P.Y, Radius);
    }
}

int main()
{
    using namespace DigimonVenomNXTFarmCore;
    using namespace DigimonVenomNXTFarmCollisionData;
    Require(IsWalkable(SpawnX, SpawnY, PlayerRadius), "tamer entry has complete walkable footprint");
    Require(IsWalkable(SpawnX, SpawnY, ResidentRadius), "resident fallback has complete walkable footprint");
    // Independent visible landmark: the north grass at source (836,180) is
    // world +Y, whereas its mirrored source row 761 lies beyond the south cliff.
    // The old sign mistake passed pixel-roundtrip tests but fails these world probes.
    Require(IsWalkable(0.0, WorldHeight * (0.5 - 180.0 / 941.0), PlayerRadius), "north grass is on positive world Y");
    Require(!IsWalkable(0.0, -WorldHeight * (0.5 - 180.0 / 941.0), PlayerRadius), "north grass must not be mirrored onto south water");
    Require(SafePixel(836,470,PlayerRadius), "reference MMO center spawn matches same island");
    Require(SafePixel(350,350,PlayerRadius) && SafePixel(1320,530,PlayerRadius), "both island lobes support tamers");
    Require(SafePixel(325,170), "interior dirt patch stays walkable; no color classification holes");
    Require(!SafePixel(0,0) && !SafePixel(1671,0) && !SafePixel(0,940) && !SafePixel(1671,940), "all four art corners are water");
    Require(!SafePixel(836,60) && !SafePixel(836,850), "water above and below island blocked");
    Require(!SafePixel(150,380), "left shoreline inlet water blocked inside image rectangle");
    Require(!SafePixel(1550,350), "right shoreline inlet water blocked inside image rectangle");
    Require(!SafePixel(410,795) && !SafePixel(1125,815), "cliff faces are not mistaken for grass");
    Require(!IsWalkable(WorldWidth,0) && !IsWalkable(0,WorldHeight), "out-of-art positions fail closed");
    Require(!IsWalkable(0,0,-1), "invalid footprint radius fails closed");
    const double NaN = std::numeric_limits<double>::quiet_NaN();
    const double Infinity = std::numeric_limits<double>::infinity();
    Require(!IsWalkable(NaN,0) && !IsWalkable(0,Infinity) && !IsWalkable(0,0,NaN), "nonfinite movement cannot pass mask");
    Require(!IsSegmentWalkable(0,0,Infinity,0,PlayerRadius), "nonfinite destination cannot tunnel");
    Require(IsSegmentWalkable(SpawnX,SpawnY,SpawnX,SpawnY,PlayerRadius), "zero-distance valid movement succeeds");
    const auto CorruptSave = FindSafePoint(NaN,Infinity,PlayerRadius);
    Require(IsWalkable(CorruptSave.X,CorruptSave.Y,PlayerRadius), "corrupt saved farm coordinates recover on grass");
    const auto WaterSave = FindSafePoint(WorldWidth,WorldHeight,PlayerRadius);
    Require(IsWalkable(WaterSave.X,WaterSave.Y,PlayerRadius), "saved water position snaps to complete safe footprint");
    const auto KeptSave = FindSafePoint(SpawnX,SpawnY,PlayerRadius);
    Require(KeptSave.X==SpawnX && KeptSave.Y==SpawnY, "valid saved coordinates remain unchanged");

    // Dense independent world/pixel orientation check: every eighth cell in both
    // axes must agree with its source mask byte; catches wrong mirror/y direction.
    for (int Y=0;Y<GridHeight;Y+=8)
        for (int X=0;X<GridWidth;X+=8)
        {
            const double WX=WorldWidth*(0.5-(X+0.5)/GridWidth);
            const double WY=WorldHeight*(0.5-(Y+0.5)/GridHeight);
            Require(IsWalkable(WX,WY)==CellWalkable(X,Y), "source mask remains aligned to field-space artwork");
        }
    int Walkable=0;
    for (int Y=0;Y<GridHeight;++Y)
        for (int X=0;X<GridWidth;++X)
            if (CellWalkable(X,Y)) ++Walkable;
    Require(GridWidth == 1672 && GridHeight == 941, "farm collision retains every source pixel without downsampling");
    Require(Walkable==738796, "committed authoritative shoreline cell count is intact");
    Require(Walkable>GridWidth*GridHeight*0.4 && Walkable<GridWidth*GridHeight*0.6, "collision is actual island area, not enclosing rectangle");

    bool FoundFootprintEdge=false;
    for (int Y=0;Y<GridHeight && !FoundFootprintEdge;++Y)
        for (int X=0;X<GridWidth;++X)
        {
            const double WX=WorldWidth*0.5-(X+0.5)*CellWidth;
            const double WY=WorldHeight*0.5-(Y+0.5)*CellHeight;
            if (!IsWalkable(WX,WY) || IsWalkable(WX,WY,PlayerRadius)) continue;
            FoundFootprintEdge=true;
            Require(!IsWalkable(WX,WY,PlayerRadius), "feet center on grass cannot let body radius hang over cliff");
            break;
        }
    Require(FoundFootprintEdge, "shoreline footprint edge case is exercised");
    const auto InletTop=Pixel(170,280), InletBottom=Pixel(125,540);
    Require(IsWalkable(InletTop.X,InletTop.Y,ResidentRadius) && IsWalkable(InletBottom.X,InletBottom.Y,ResidentRadius), "concave-inlet test endpoints are valid grass");
    Require(!IsSegmentWalkable(InletTop.X,InletTop.Y,InletBottom.X,InletBottom.Y,ResidentRadius), "long steps cannot shortcut through water between valid endpoints");

    // Exercise the actual resident route policy over repeatable candidate walks.
    std::mt19937 Random(1378);
    std::uniform_real_distribution<double> Offset(-650.0,650.0);
    Point Current{SpawnX,SpawnY};
    int Accepted=0, Rejected=0;
    for (int Attempt=0;Attempt<500;++Attempt)
    {
        const Point Candidate{Current.X+Offset(Random),Current.Y+Offset(Random)};
        if (!IsSegmentWalkable(Current.X,Current.Y,Candidate.X,Candidate.Y,ResidentRadius)) { ++Rejected; continue; }
        ++Accepted;
        for (int Step=0;Step<=20;++Step)
        {
            const double T=Step/20.0;
            Require(IsWalkable(Current.X+(Candidate.X-Current.X)*T,Current.Y+(Candidate.Y-Current.Y)*T,ResidentRadius), "accepted resident route keeps entire footprint on grass");
        }
        Current=Candidate;
    }
    Require(Accepted>100 && Rejected>10, "roaming tests exercise both valid paths and rejected shoreline paths");
    std::cout << "Farm collision core: " << Checks << " checks passed\n";
}
