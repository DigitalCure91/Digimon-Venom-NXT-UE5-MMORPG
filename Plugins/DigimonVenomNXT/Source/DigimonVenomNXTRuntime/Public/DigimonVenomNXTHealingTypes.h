#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTHealingTypes.generated.h"

/** Authoritative recovery delta; sent only to the requesting account owner. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonHealedPartner
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FGuid InstanceId;
    UPROPERTY(BlueprintReadOnly) int32 BeforeHP = 0;
    UPROPERTY(BlueprintReadOnly) int32 BeforeSP = 0;
    UPROPERTY(BlueprintReadOnly) int32 AfterHP = 0;
    UPROPERTY(BlueprintReadOnly) int32 AfterSP = 0;
    UPROPERTY(BlueprintReadOnly) int32 MaxHP = 1;
    UPROPERTY(BlueprintReadOnly) int32 MaxSP = 0;
};

/** Success is published only after the full recovery transaction is saved. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonHealReceipt
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FGuid RequestId;
    /** Matches the saved profile generation, even when replication coalesces later changes. */
    UPROPERTY(BlueprintReadOnly) int64 RecoveryRevision = 0;
    UPROPERTY(BlueprintReadOnly) bool bSuccess = false;
    UPROPERTY(BlueprintReadOnly) FString Message;
    UPROPERTY(BlueprintReadOnly) int32 RestoredPartners = 0;
    /** Actual healed partners in the current six-member party; collection totals are above. */
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonHealedPartner> PartyChanges;
};
