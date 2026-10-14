#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"

namespace DigimonVenomNXTProfileValidation
{
    // Validate identity and ownership, not balance tuning. Never "repair" a broken
    // party by silently deleting members or replacing the account with defaults.
    DIGIMONVENOMNXTRUNTIME_API bool Validate(const FDigimonPlayerProfile& Profile, const FString& ExpectedAccountId, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool HasRequiredJsonFields(const FString& Json);
}
