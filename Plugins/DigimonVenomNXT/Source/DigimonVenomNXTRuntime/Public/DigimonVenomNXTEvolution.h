#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"

class UDigimonVenomNXTDataSubsystem;

/** Shared preview produced from the exact same gates used by the server and AI rivals. */
struct DIGIMONVENOMNXTRUNTIME_API FDigimonEvolutionOption
{
    FName TargetSpeciesId = NAME_None;
    EDigimonStage TargetStage = EDigimonStage::Unknown;
    bool bDeEvolution = false;
    bool bAvailable = false;
    int32 RequiredLevel = 2;
    int32 RequiredCAM = 0;
    int32 RequiredABI = 0;
    int32 ABIGain = 0;
    int32 ResultABI = 0;
    FDigimonEvolutionRequirement Requirement;
    FString MissingReasons;
};

namespace DigimonVenomNXTEvolution
{
    DIGIMONVENOMNXTRUNTIME_API TArray<FDigimonEvolutionOption> GetOptions(const FDigimonOwnedPartner& Partner, const UDigimonVenomNXTDataSubsystem* Data, bool bIncludeDeEvolution = true);
    DIGIMONVENOMNXTRUNTIME_API bool TryTransform(FDigimonOwnedPartner& Partner, FName TargetSpeciesId, bool bDeEvolution, const UDigimonVenomNXTDataSubsystem* Data, FString& OutMessage);
    DIGIMONVENOMNXTRUNTIME_API int32 TrainingCapacity(const FDigimonOwnedPartner& Partner);
    DIGIMONVENOMNXTRUNTIME_API float TrainingUsed(const FDigimonOwnedPartner& Partner);
    DIGIMONVENOMNXTRUNTIME_API bool CanTrain(const FDigimonOwnedPartner& Partner, EDigimonTrainingStat Stat, int32 Amount = 1);
    DIGIMONVENOMNXTRUNTIME_API bool TryTrain(FDigimonOwnedPartner& Partner, EDigimonTrainingStat Stat, int32 Amount = 1);
    /** Returns the actual applied gain; zero means already capped. No inventory is consumed here. */
    DIGIMONVENOMNXTRUNTIME_API int32 FeedCAM(FDigimonOwnedPartner& Partner);
    DIGIMONVENOMNXTRUNTIME_API int32 FeedABI(FDigimonOwnedPartner& Partner);
}
