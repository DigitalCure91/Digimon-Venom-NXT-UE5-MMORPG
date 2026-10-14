#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>

/** Exact collision against the registered image-space mask. Coordinates and
 * radius are world units measured from the image's top-left, X right, Y down.
 * This core has no rendering or Unreal dependency: authority, prediction and
 * placement all use the same disk / swept-disk intersection contract.
 */
namespace DigimonVenomNXTCollisionCore
{
    struct Point { double X = 0.0; double Y = 0.0; };
    struct Grid
    {
        int Width = 0;
        int Height = 0;
        const std::uint8_t* Bits = nullptr;
        std::size_t ByteCount = 0;
        double WorldWidth = 0.0;
        double WorldHeight = 0.0;
    };

    inline bool Valid(const Grid& G)
    {
        if (G.Width <= 0 || G.Height <= 0 || G.Width > 16384 || G.Height > 16384 || !G.Bits ||
            !std::isfinite(G.WorldWidth) || !std::isfinite(G.WorldHeight) || G.WorldWidth <= 0 || G.WorldHeight <= 0) return false;
        const std::uint64_t Cells = static_cast<std::uint64_t>(G.Width) * G.Height;
        return G.ByteCount == static_cast<std::size_t>((Cells + 7u) / 8u);
    }

    inline bool CellWalkable(const Grid& G, int X, int Y)
    {
        if (X < 0 || Y < 0 || X >= G.Width || Y >= G.Height || !G.Bits) return false;
        const std::size_t Index = static_cast<std::size_t>(Y) * G.Width + X;
        return Index / 8 < G.ByteCount && (G.Bits[Index / 8] & (1u << (7u - Index % 8u))) != 0;
    }

    inline double PointSegmentDistanceSquared(Point P, Point A, Point B)
    {
        const double DX = B.X - A.X, DY = B.Y - A.Y;
        const double LengthSquared = DX * DX + DY * DY;
        const double T = LengthSquared > 0 ? std::clamp(((P.X - A.X) * DX + (P.Y - A.Y) * DY) / LengthSquared, 0.0, 1.0) : 0.0;
        const double PX = P.X - (A.X + DX * T), PY = P.Y - (A.Y + DY * T);
        return PX * PX + PY * PY;
    }

    inline double PointRectangleDistanceSquared(Point P, double Left, double Top, double Right, double Bottom)
    {
        const double DX = P.X - std::clamp(P.X, Left, Right), DY = P.Y - std::clamp(P.Y, Top, Bottom);
        return DX * DX + DY * DY;
    }

    inline bool SegmentIntersectsRectangle(Point A, Point B, double Left, double Top, double Right, double Bottom)
    {
        double Enter = 0.0, Exit = 1.0;
        const auto Clip = [&](double Start, double Delta, double Low, double High) -> bool
        {
            if (std::abs(Delta) <= 1.e-14) return Start >= Low && Start <= High;
            double T0 = (Low - Start) / Delta, T1 = (High - Start) / Delta;
            if (T0 > T1) std::swap(T0, T1);
            Enter = std::max(Enter, T0); Exit = std::min(Exit, T1);
            return Enter <= Exit;
        };
        return Clip(A.X, B.X - A.X, Left, Right) && Clip(A.Y, B.Y - A.Y, Top, Bottom);
    }

    inline double SegmentRectangleDistanceSquared(Point A, Point B, double Left, double Top, double Right, double Bottom)
    {
        if (SegmentIntersectsRectangle(A, B, Left, Top, Right, Bottom)) return 0.0;
        double Best = std::min(PointRectangleDistanceSquared(A, Left, Top, Right, Bottom),
                               PointRectangleDistanceSquared(B, Left, Top, Right, Bottom));
        for (const Point Corner : {Point{Left, Top}, Point{Right, Top}, Point{Left, Bottom}, Point{Right, Bottom}})
            Best = std::min(Best, PointSegmentDistanceSquared(Corner, A, B));
        return Best;
    }

    inline bool IsSegmentWalkable(const Grid& G, Point A, Point B, double Radius)
    {
        if (!Valid(G) || !std::isfinite(A.X) || !std::isfinite(A.Y) || !std::isfinite(B.X) || !std::isfinite(B.Y) ||
            !std::isfinite(Radius) || Radius < 0.0) return false;
        const double Left = std::min(A.X, B.X) - Radius, Right = std::max(A.X, B.X) + Radius;
        const double Top = std::min(A.Y, B.Y) - Radius, Bottom = std::max(A.Y, B.Y) + Radius;
        // Outside the authored image is always blocked, even if the last pixel is white.
        if (Left < 0.0 || Top < 0.0 || Right >= G.WorldWidth || Bottom >= G.WorldHeight) return false;
        const double CellWidth = G.WorldWidth / G.Width, CellHeight = G.WorldHeight / G.Height;
        // Cells are closed rectangles for collision. At an exact lower grid
        // boundary the preceding cell can touch the disk/capsule too. Include
        // that candidate; the exact distance test discards it when separated.
        const int MinX = std::max(0, static_cast<int>(std::floor(Left / CellWidth)) - 1);
        const int MaxX = std::min(G.Width - 1, static_cast<int>(std::floor(Right / CellWidth)));
        const int MinY = std::max(0, static_cast<int>(std::floor(Top / CellHeight)) - 1);
        const int MaxY = std::min(G.Height - 1, static_cast<int>(std::floor(Bottom / CellHeight)));
        const double RadiusSquared = Radius * Radius;
        for (int Y = MinY; Y <= MaxY; ++Y)
            for (int X = MinX; X <= MaxX; ++X)
            {
                if (CellWalkable(G, X, Y)) continue;
                if (SegmentRectangleDistanceSquared(A, B, X * CellWidth, Y * CellHeight,
                    (X + 1) * CellWidth, (Y + 1) * CellHeight) <= RadiusSquared) return false;
            }
        return true;
    }

    inline bool IsWalkable(const Grid& G, Point P, double Radius)
    {
        return IsSegmentWalkable(G, P, P, Radius);
    }
}
