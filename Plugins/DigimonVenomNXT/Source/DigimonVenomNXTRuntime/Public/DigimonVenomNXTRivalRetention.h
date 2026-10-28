#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTRivalRetentionCore.h"

class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTSettings;

/** Bounds live bot data independently of checkpoint frequency. Never applies to human profiles. */
namespace DigimonVenomNXTRivalRetention
{
    constexpr int32 MaxOwnedPerRival = DigimonVenomNXTRivalRetentionCore::MaxOwnedPerRival;
    constexpr int32 MaxScansPerRival = DigimonVenomNXTRivalRetentionCore::MaxScansPerRival;
    constexpr int32 GlobalOwnedBudget = DigimonVenomNXTRivalRetentionCore::GlobalOwnedBudget;
    constexpr int32 GlobalScanBudget = DigimonVenomNXTRivalRetentionCore::GlobalScanBudget;

    struct FResult
    {
        bool bChanged = false;
        int32 ReleasedPartners = 0;
        int32 RemovedScans = 0;
        int32 RemovedHistory = 0;
        int32 RemovedInventory = 0;
    };

    /** Includes active party slots. Legacy INI values cannot disable these runtime ceilings. */
    DIGIMONVENOMNXTRUNTIME_API int32 CollectionLimit(int32 Configured, int32 ConfiguredPartySize = 6, int32 Population = 1000);
    DIGIMONVENOMNXTRUNTIME_API int32 ScanLimit(int32 Configured, int32 Population = 1000);

    /** Merge current party, release excess reserves and erase stale associated payloads.
     * Active party wins; next retain training leader, original first companion and highest-progress reserves.
     * Data=nullptr is structural validation only, for tools/tests without an initialized species registry.
     */
    DIGIMONVENOMNXTRUNTIME_API FResult Prune(FDigimonAIRivalRecord& Rival, const UDigimonVenomNXTSettings& Settings,
        const UDigimonVenomNXTDataSubsystem* Data = nullptr, int32 Population = 1000);

    /** Explicit reserve release. Active party and current training leader cannot be released. */
    DIGIMONVENOMNXTRUNTIME_API bool Release(FDigimonAIRivalRecord& Rival, const FGuid& InstanceId,
        const UDigimonVenomNXTSettings& Settings, const UDigimonVenomNXTDataSubsystem* Data = nullptr, int32 Population = 1000);
}
