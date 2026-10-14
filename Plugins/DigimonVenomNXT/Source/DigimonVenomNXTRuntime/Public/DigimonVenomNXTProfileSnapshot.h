#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"

namespace DigimonVenomNXTProfileSnapshot
{
    DIGIMONVENOMNXTRUNTIME_API bool Encode(const FDigimonPlayerProfile& Profile, TArray<uint8>& Bytes,
        int32& JsonBytes, uint32& Checksum, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool Decode(const uint8* Bytes, int32 ByteCount, int32 JsonBytes, uint32 Checksum,
        const FString& ExpectedAccountId, FDigimonPlayerProfile& OutProfile, FString& Error);
}
