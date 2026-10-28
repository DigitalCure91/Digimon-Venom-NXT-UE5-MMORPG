#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"

/** Bounded-memory adapter for both legacy and compact AIRivals.json checkpoints. */
namespace DigimonVenomNXTRivalPersistence
{
    constexpr int64 MaxCheckpointBytes = 256LL * 1024 * 1024;
    /** Validates/indexes the stream first, then decodes and compacts one rival at a time.
     * OutData is only replaced after the complete checkpoint passes validation. */
    DIGIMONVENOMNXTRUNTIME_API bool Read(const FString& Path, FDigimonAIRivalSaveData& OutData,
        TFunctionRef<void(FDigimonAIRivalRecord&, int32 TotalRivals)> CompactRecord, FString& OutError, bool& bUnsupportedSchema);

    /** Writes only Path (the caller's .tmp). Never touches the primary or backup.
     * One condensed UTF-8 record at a time; refuses to exceed 256 MiB. */
    DIGIMONVENOMNXTRUNTIME_API bool WriteTemporary(const FString& Path, const FDigimonAIRivalSaveData& Data,
        FString& OutError);
}
