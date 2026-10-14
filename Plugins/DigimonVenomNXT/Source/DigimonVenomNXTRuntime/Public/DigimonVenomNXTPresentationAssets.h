#pragma once

#include "CoreMinimal.h"

class UTexture2D;

/** Shared runtime/editor registration for the original DigiLab and shop artwork. */
namespace DigimonVenomNXTPresentationAssets
{
    struct FRegistration
    {
        const TCHAR* Key;
        /** Source path relative to Resources/RawAssets. */
        const TCHAR* RelativePNG;
        /** Stable cooked Texture2D object path. */
        const TCHAR* TexturePath;
    };

    DIGIMONVENOMNXTRUNTIME_API TConstArrayView<FRegistration> AllAssets();
    DIGIMONVENOMNXTRUNTIME_API TConstArrayView<FRegistration> CommunityAssets();
    /** Unknown keys return nullptr; no arbitrary asset paths are accepted. */
    DIGIMONVENOMNXTRUNTIME_API const TCHAR* ObjectPath(FName Key);
    /** Weakly cached; missing assets are retried after an editor import. Dedicated servers do not load UI art. */
    DIGIMONVENOMNXTRUNTIME_API UTexture2D* LoadTexture(FName Key);
    DIGIMONVENOMNXTRUNTIME_API UTexture2D* ItemTexture(FName ItemId);
}
