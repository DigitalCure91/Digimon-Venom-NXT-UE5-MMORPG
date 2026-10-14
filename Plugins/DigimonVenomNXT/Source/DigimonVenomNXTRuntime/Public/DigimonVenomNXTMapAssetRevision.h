#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonVenomNXTMapAssetRevision.generated.h"

class UTexture2D;

/** Saved only after the complete canonical map import succeeds. The cooked
 * receipt prevents old or partially imported artwork from being paired with
 * this release's collision registry, even when the image sizes are unchanged.
 */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTMapAssetRevision : public UDataAsset
{
    GENERATED_BODY()
public:
    static constexpr const TCHAR* ExpectedRevision = TEXT("DVNXT-1e216b48ea86541b");
    static constexpr int32 ExpectedMapCount = 500;
    static constexpr const TCHAR* ExpectedContentFingerprint = TEXT("1e216b48ea86541b3476268cd10f4be712f43f06a99b10710a0e80040cfadaa1");

    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Maps") FString Revision;
    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Maps") int32 MapCount = 0;
    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Maps") FString ContentFingerprint;

    /** Validates a cached cooked receipt without reading or hashing loose files. */
    static bool IsInstalledCurrent();
    /** Atlas thumbnails share the same content gate as the field renderer. */
    static UTexture2D* LoadMapTexture(int32 MapId);
};
