#pragma once

#include "CoreMinimal.h"

/** One authoritative catalogue shared by appearance requests, UI and importing. */
namespace DigimonVenomNXTTamers
{
struct FStyle
{
    FName Id;
    FString Name;
    FString Description;
};

DIGIMONVENOMNXTRUNTIME_API const TArray<FStyle>& GetRoster();
DIGIMONVENOMNXTRUNTIME_API bool IsValidStyle(FName StyleId);
DIGIMONVENOMNXTRUNTIME_API FName StyleForIndex(int32 Index);
/** Stable across machines, reconnects and simulation order. */
DIGIMONVENOMNXTRUNTIME_API FName StyleForStableId(const FString& StableId);
DIGIMONVENOMNXTRUNTIME_API FString DisplayName(FName StyleId);
DIGIMONVENOMNXTRUNTIME_API FString ThumbnailPath(FName StyleId);
DIGIMONVENOMNXTRUNTIME_API FString AnimationPath(FName StyleId);
}
