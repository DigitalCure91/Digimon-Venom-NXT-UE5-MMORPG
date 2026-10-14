#pragma once
#include "DigimonVenomNXTTradeTypes.h"
#include "DigimonVenomNXTTradeCore.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace DigimonVenomNXTTradeStorage
{
inline bool ReadMarket(const FString& Json, FDigimonTradeMarket& Out)
{
    TSharedPtr<FJsonObject> Object;
    const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
    double Version = 0;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json), Object) || !Object.IsValid() ||
        !Object->TryGetNumberField(TEXT("version"), Version) || Version != 1 ||
        !Object->TryGetArrayField(TEXT("listings"), Rows) || !Rows || Rows->Num() > 10000 ||
        !FJsonObjectConverter::JsonObjectToUStruct(Object.ToSharedRef(), &Out, 0, 0) || Out.Version != 1) return false;
    TSet<FGuid> Listings, Partners;
    for (const auto& Listing : Out.Listings)
    {
        if (!Listing.ListingId.IsValid() || !Listing.Partner.IsValid() || Listing.SellerAccountId.IsEmpty() ||
            Listings.Contains(Listing.ListingId) || Partners.Contains(Listing.Partner.InstanceId) ||
            !DigimonVenomNXTTradeCore::ValidPrice(Listing.Credits, Listing.DigiRubies)) return false;
        Listings.Add(Listing.ListingId); Partners.Add(Listing.Partner.InstanceId);
    }
    return true;
}
}
