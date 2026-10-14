#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTTradeTypes.generated.h"

/** The complete partner snapshot is the item in escrow, not a client-provided description. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonTradeListing
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FGuid ListingId;
    UPROPERTY(BlueprintReadOnly) FString SellerAccountId;
    UPROPERTY(BlueprintReadOnly) FString SellerName;
    UPROPERTY(BlueprintReadOnly) FDigimonOwnedPartner Partner;
    UPROPERTY(BlueprintReadOnly) int64 Credits = 0;
    UPROPERTY(BlueprintReadOnly) int32 DigiRubies = 0;
    UPROPERTY(BlueprintReadOnly) int64 CreatedUnix = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonTradeOffer
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonOwnedPartner> Partners;
    UPROPERTY(BlueprintReadOnly) int64 Credits = 0;
    UPROPERTY(BlueprintReadOnly) int32 DigiRubies = 0;
    UPROPERTY(BlueprintReadOnly) bool bConfirmed = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonDirectTrade
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FGuid SessionId;
    UPROPERTY(BlueprintReadOnly) int32 Revision = 1;
    UPROPERTY(BlueprintReadOnly) FString FirstAccountId;
    UPROPERTY(BlueprintReadOnly) FString FirstName;
    UPROPERTY(BlueprintReadOnly) FString SecondAccountId;
    UPROPERTY(BlueprintReadOnly) FString SecondName;
    UPROPERTY(BlueprintReadOnly) FDigimonTradeOffer First;
    UPROPERTY(BlueprintReadOnly) FDigimonTradeOffer Second;
    UPROPERTY(BlueprintReadOnly) int64 ExpiresUnix = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonTradeView
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonTradeListing> Listings;
    UPROPERTY(BlueprintReadOnly) int32 Page = 0;
    UPROPERTY(BlueprintReadOnly) int32 TotalListings = 0;
    UPROPERTY(BlueprintReadOnly) FString Search;
    UPROPERTY(BlueprintReadOnly) bool bMineOnly = false;
    UPROPERTY(BlueprintReadOnly) FDigimonDirectTrade Session;
    UPROPERTY(BlueprintReadOnly) FDigimonTradeListing PurchaseReview;
    UPROPERTY(BlueprintReadOnly) FGuid PurchaseToken;
    UPROPERTY(BlueprintReadOnly) FString Status;
    UPROPERTY(BlueprintReadOnly) bool bSuccess = true;
};

/** Private server storage. Escrow is removed from its seller before a listing is published. */
USTRUCT()
struct FDigimonTradeMarket
{
    GENERATED_BODY()
    UPROPERTY() int32 Version = 1;
    UPROPERTY() TArray<FDigimonTradeListing> Listings;
};
