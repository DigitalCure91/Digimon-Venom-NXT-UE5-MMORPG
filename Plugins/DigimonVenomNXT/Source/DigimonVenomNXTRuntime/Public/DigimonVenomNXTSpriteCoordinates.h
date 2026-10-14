#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"

/** Coordinates in the sprite's own image rectangle: (0,0) is its top-left
 * corner, independent of where the frame is packed in its texture. The baked
 * vertices retain the authored pivot and pixel scale in cooked games; Paper2D's
 * source/pivot editing functions and properties do not.
 */
namespace DigimonVenomNXTSpriteCoordinates
{
    inline bool IsFinitePoint(const FVector& Point)
    {
        return FMath::IsFinite(Point.X) && FMath::IsFinite(Point.Y) && FMath::IsFinite(Point.Z);
    }

    struct FMapping
    {
        FVector2D ImageSize = FVector2D::ZeroVector;
        FVector ImageOrigin = FVector::ZeroVector;
        FVector ImageAxisX = FVector::ZeroVector;
        FVector ImageAxisY = FVector::ZeroVector;

        FVector ImageToLocal(const FVector2D& ImagePoint) const
        {
            return ImageOrigin + ImageAxisX * ImagePoint.X + ImageAxisY * ImagePoint.Y;
        }

        FVector2D LocalToImage(const FVector& LocalPoint) const
        {
            const double Determinant = ImageAxisX.X * ImageAxisY.Z - ImageAxisY.X * ImageAxisX.Z;
            if (!FMath::IsFinite(Determinant) || Determinant == 0.0 || !IsFinitePoint(LocalPoint))
                return FVector2D::ZeroVector;
            const FVector Delta = LocalPoint - ImageOrigin;
            return FVector2D((Delta.X * ImageAxisY.Z - ImageAxisY.X * Delta.Z) / Determinant,
                (ImageAxisX.X * Delta.Z - Delta.X * ImageAxisX.Z) / Determinant);
        }
    };

    inline bool TryGetMapping(const UPaperSprite* Sprite, FMapping& OutMapping)
    {
        OutMapping = FMapping();
        if (!Sprite || Sprite->BakedRenderData.Num() < 3) return false;

        const double PixelsPerUnit = Sprite->GetPixelsPerUnrealUnit();
        const FSlateAtlasData Atlas = Sprite->GetSlateAtlasData();
        if (!FMath::IsFinite(PixelsPerUnit) || PixelsPerUnit <= 0.0 || !Atlas.AtlasTexture ||
            !FMath::IsFinite(Atlas.StartUV.X) || !FMath::IsFinite(Atlas.StartUV.Y) ||
            !FMath::IsFinite(Atlas.SizeUV.X) || !FMath::IsFinite(Atlas.SizeUV.Y) ||
            Atlas.SizeUV.X <= 0.0 || Atlas.SizeUV.Y <= 0.0) return false;

        // Find a well-conditioned triangle. Tight/diced geometry need not have
        // vertices at the image corners, so render bounds cannot recover the
        // source canvas or its pivot. Its affine UV mapping can recover both.
        int32 BestTriangle = INDEX_NONE;
        double BestArea = 0.0;
        for (int32 Index = 0; Index + 2 < Sprite->BakedRenderData.Num(); Index += 3)
        {
            const auto& A = Sprite->BakedRenderData[Index];
            const auto& B = Sprite->BakedRenderData[Index + 1];
            const auto& C = Sprite->BakedRenderData[Index + 2];
            if (!FMath::IsFinite(A.X) || !FMath::IsFinite(A.Y) || !FMath::IsFinite(A.Z) || !FMath::IsFinite(A.W) ||
                !FMath::IsFinite(B.X) || !FMath::IsFinite(B.Y) || !FMath::IsFinite(B.Z) || !FMath::IsFinite(B.W) ||
                !FMath::IsFinite(C.X) || !FMath::IsFinite(C.Y) || !FMath::IsFinite(C.Z) || !FMath::IsFinite(C.W)) continue;
            const double U1 = static_cast<double>(B.Z) - A.Z;
            const double V1 = static_cast<double>(B.W) - A.W;
            const double U2 = static_cast<double>(C.Z) - A.Z;
            const double V2 = static_cast<double>(C.W) - A.W;
            const double Area = FMath::Abs(U1 * V2 - U2 * V1);
            const double EdgeSquared = FMath::Max(U1 * U1 + V1 * V1, U2 * U2 + V2 * V2);
            if (FMath::IsFinite(Area) && FMath::IsFinite(EdgeSquared) &&
                Area > EdgeSquared * 1.0e-10 && Area > BestArea)
            {
                BestArea = Area;
                BestTriangle = Index;
            }
        }
        if (BestTriangle == INDEX_NONE) return false;

        const auto& A = Sprite->BakedRenderData[BestTriangle];
        const auto& B = Sprite->BakedRenderData[BestTriangle + 1];
        const auto& C = Sprite->BakedRenderData[BestTriangle + 2];
        const double U1 = static_cast<double>(B.Z) - A.Z;
        const double V1 = static_cast<double>(B.W) - A.W;
        const double U2 = static_cast<double>(C.Z) - A.Z;
        const double V2 = static_cast<double>(C.W) - A.W;
        const double Determinant = U1 * V2 - U2 * V1;
        const FVector Edge1(static_cast<double>(B.X) - A.X, 0.0, static_cast<double>(B.Y) - A.Y);
        const FVector Edge2(static_cast<double>(C.X) - A.X, 0.0, static_cast<double>(C.Y) - A.Y);
        const FVector LocalPerU = (Edge1 * V2 - Edge2 * V1) / Determinant;
        const FVector LocalPerV = (Edge2 * U1 - Edge1 * U2) / Determinant;
        const FVector ImageEdgeX = LocalPerU * Atlas.SizeUV.X;
        const FVector ImageEdgeY = LocalPerV * Atlas.SizeUV.Y;

        FMapping Result;
        // Reconstruct authored pixel dimensions from geometry, not the current
        // texture surface size: cooked LOD/mip limits can reduce that surface.
        Result.ImageSize = FVector2D(ImageEdgeX.Size() * PixelsPerUnit, ImageEdgeY.Size() * PixelsPerUnit);
        if (!FMath::IsFinite(Result.ImageSize.X) || !FMath::IsFinite(Result.ImageSize.Y) ||
            Result.ImageSize.X <= 0.0 || Result.ImageSize.Y <= 0.0) return false;
        Result.ImageOrigin = FVector(A.X, 0.0, A.Y) + LocalPerU * (Atlas.StartUV.X - A.Z) +
            LocalPerV * (Atlas.StartUV.Y - A.W);
        Result.ImageAxisX = ImageEdgeX / Result.ImageSize.X;
        Result.ImageAxisY = ImageEdgeY / Result.ImageSize.Y;
        const double LocalDeterminant = Result.ImageAxisX.X * Result.ImageAxisY.Z -
            Result.ImageAxisY.X * Result.ImageAxisX.Z;
        const double AxisProduct = Result.ImageAxisX.Size() * Result.ImageAxisY.Size();
        if (!IsFinitePoint(Result.ImageOrigin) || !IsFinitePoint(Result.ImageAxisX) || !IsFinitePoint(Result.ImageAxisY) ||
            !FMath::IsFinite(LocalDeterminant) || !FMath::IsFinite(AxisProduct) ||
            FMath::Abs(LocalDeterminant) <= AxisProduct * 1.0e-10) return false;
        OutMapping = Result;
        return true;
    }

    inline FVector2D GetImageSize(const UPaperSprite* Sprite)
    {
        FMapping Mapping;
        return TryGetMapping(Sprite, Mapping) ? Mapping.ImageSize : FVector2D::ZeroVector;
    }

    inline FVector ImageToLocal(const UPaperSprite* Sprite, const FVector2D& ImagePoint)
    {
        FMapping Mapping;
        if (!FMath::IsFinite(ImagePoint.X) || !FMath::IsFinite(ImagePoint.Y) || !TryGetMapping(Sprite, Mapping))
            return FVector::ZeroVector;
        return Mapping.ImageToLocal(ImagePoint);
    }

    inline FVector2D LocalToImage(const UPaperSprite* Sprite, const FVector& LocalPoint)
    {
        FMapping Mapping;
        return TryGetMapping(Sprite, Mapping) ? Mapping.LocalToImage(LocalPoint) : FVector2D::ZeroVector;
    }

    inline bool IsFullTexture(const UPaperSprite* Sprite)
    {
        if (!Sprite) return false;
        const FSlateAtlasData Atlas = Sprite->GetSlateAtlasData();
        return Atlas.AtlasTexture && FMath::IsNearlyEqual(Atlas.StartUV.X, 0.0, 1.0e-6) &&
            FMath::IsNearlyEqual(Atlas.StartUV.Y, 0.0, 1.0e-6) &&
            FMath::IsNearlyEqual(Atlas.SizeUV.X, 1.0, 1.0e-6) && FMath::IsNearlyEqual(Atlas.SizeUV.Y, 1.0, 1.0e-6);
    }
}
