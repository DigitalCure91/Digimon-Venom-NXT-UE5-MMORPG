#pragma once
#include <cstdint>
#include <limits>

/** Shared by the actual authority settlement and the portable regression executable. */
namespace DigimonVenomNXTTradeCore
{
constexpr std::int64_t MaxCredits = 9007199254740991LL; // JSON's exact integer range.
constexpr std::int64_t MaxRubies = 2147483647LL;
constexpr int MaxPartners = 6;
constexpr int MaxCollection = 1000;
constexpr int MaxListingsPerAccount = 10;
constexpr int PageSize = 12;
inline bool Exchange(std::int64_t BalanceA, std::int64_t BalanceB,
    std::int64_t OfferA, std::int64_t OfferB, std::int64_t Cap,
    std::int64_t& ResultA, std::int64_t& ResultB)
{
    if (Cap < 0 || BalanceA < 0 || BalanceB < 0 || BalanceA > Cap || BalanceB > Cap ||
        OfferA < 0 || OfferB < 0 || OfferA > BalanceA || OfferB > BalanceB) return false;
    const std::int64_t LeftA = BalanceA - OfferA, LeftB = BalanceB - OfferB;
    if (OfferB > Cap - LeftA || OfferA > Cap - LeftB) return false;
    ResultA = LeftA + OfferB;
    ResultB = LeftB + OfferA;
    return true;
}
inline bool ValidPrice(std::int64_t Credits, std::int64_t Rubies)
{
    return Credits >= 0 && Credits <= MaxCredits && Rubies >= 0 && Rubies <= MaxRubies &&
        (Credits > 0 || Rubies > 0);
}
inline bool ReceiveFits(int Existing, int Sending, int Receiving)
{
    return Existing >= 0 && Sending >= 0 && Sending <= Existing && Receiving >= 0 &&
        Existing - Sending <= MaxCollection - Receiving;
}
}
