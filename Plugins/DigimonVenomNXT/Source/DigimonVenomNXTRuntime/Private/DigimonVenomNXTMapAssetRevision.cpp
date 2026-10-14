#include "DigimonVenomNXTMapAssetRevision.h"
#include "Engine/Texture2D.h"

bool UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent()
{
    static TWeakObjectPtr<UDigimonVenomNXTMapAssetRevision> CachedReceipt;
    if (!CachedReceipt.IsValid())
    {
        CachedReceipt = LoadObject<UDigimonVenomNXTMapAssetRevision>(nullptr,
            TEXT("/DigimonVenomNXT/Generated/Maps/DA_PlayableMapRevision.DA_PlayableMapRevision"),
            nullptr, LOAD_NoWarn | LOAD_Quiet);
    }
    const UDigimonVenomNXTMapAssetRevision* Receipt = CachedReceipt.Get();
    // Read the fields on each check: the editor invalidates this object before
    // reimporting, so an already-loaded receipt cannot authorize a partial set.
    return Receipt && Receipt->Revision == ExpectedRevision &&
        Receipt->MapCount == ExpectedMapCount && Receipt->ContentFingerprint == ExpectedContentFingerprint;
}

UTexture2D* UDigimonVenomNXTMapAssetRevision::LoadMapTexture(int32 MapId)
{
    if (MapId < 1 || MapId > ExpectedMapCount || !IsInstalledCurrent()) return nullptr;
    const FString Asset = FString::Printf(TEXT("T_PlayMap_%03d"), MapId);
    return LoadObject<UTexture2D>(nullptr,
        *FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/%s.%s"), *Asset, *Asset), nullptr, LOAD_NoWarn | LOAD_Quiet);
}
