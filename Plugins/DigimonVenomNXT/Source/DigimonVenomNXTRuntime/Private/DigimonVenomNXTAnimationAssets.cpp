#include "DigimonVenomNXTAnimationAssets.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"

const TCHAR* DigimonVenomNXTPartnerArt::VariantFolder(EDigimonVariant Variant)
{
    switch (Variant)
    {
        case EDigimonVariant::Paradox: return TEXT("Paradox");
        case EDigimonVariant::Shiny: return TEXT("Shiny");
        case EDigimonVariant::Firewall: return TEXT("Firewall");
        default: return TEXT("Normal");
    }
}

UPaperFlipbook* UDigimonVenomNXTTamerAnimationSet::GetForFacing(EDigimonFacing Facing) const
{
    // Source directional folders were verified against the uploaded frames:
    // left faces screen-left and right faces screen-right. Keep the mapping direct.
    switch (Facing)
    {
        case EDigimonFacing::DownLeft: return DownLeft;
        case EDigimonFacing::Left: return Left;
        case EDigimonFacing::UpLeft: return UpLeft;
        case EDigimonFacing::Up: return Up;
        case EDigimonFacing::UpRight: return UpRight;
        case EDigimonFacing::Right: return Right;
        case EDigimonFacing::DownRight: return DownRight;
        default: return Down;
    }
}

bool UDigimonVenomNXTPartnerAnimationSet::ShouldMirrorLeftFrame(UPaperSprite* Frame) const
{
    return !Frame || !AuthoredLeftSprites.ContainsByPredicate([Frame](const TObjectPtr<UPaperSprite>& Authored) { return Authored.Get() == Frame; });
}

FVector2D UDigimonVenomNXTPartnerAnimationSet::GetBodySizeForFrame(UPaperSprite* Frame) const
{
    if (const FVector2D* Size = NativeFrameBodies.Find(Frame))
        if (Size->X > 0. && Size->Y > 0.) return *Size;
    return NativeBodySize;
}
