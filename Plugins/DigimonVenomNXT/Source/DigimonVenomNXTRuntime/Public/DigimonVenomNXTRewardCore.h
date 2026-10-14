#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>

// Source v1.5 reward amounts, shared by wild, authored story and private training.
namespace DigimonVenomNXTRewardCore
{
constexpr int64_t MaxCredits = 9007199254740991LL;
inline int WildXP(int Level, int StageRank) { return 24 + 12 * std::clamp(Level, 1, 200) + 8 * std::clamp(StageRank, 0, 6); }
inline int WildCredits(int Level) { return 25 + 7 * std::clamp(Level, 1, 200); }
inline int StoryXP(int Level) { return 24 + 16 * std::clamp(Level, 1, 200); }
inline int FieldCredits(int RegionIndex) { return 40 + 70 * std::max(0, RegionIndex); }
inline int64_t RematchCredits(int64_t Amount) { return std::max<int64_t>(25, std::max<int64_t>(0, Amount) / 5); }
inline int64_t Scale(int64_t Amount, double Rate)
{
    if (Amount <= 0 || !std::isfinite(Rate) || Rate <= 0) return 0;
    return static_cast<int64_t>(std::min<double>(MaxCredits, std::floor(Amount * Rate + 0.5)));
}
inline int64_t CreditTotal(int64_t Current, int64_t Gain)
{
    Current = std::clamp<int64_t>(Current, 0, MaxCredits);
    return Current + std::clamp<int64_t>(Gain, 0, MaxCredits - Current);
}
inline int InventoryTotal(int Current, int Gain) { return std::clamp(Current, 0, 999) + std::clamp(Gain, 0, 999 - std::clamp(Current, 0, 999)); }
inline int MasteryHundredths(int BaseScan) { return std::clamp(BaseScan, 0, 999) * 20; }
inline int ScanHundredthsAfter(int Percent, int Fraction, int Gain, int Cap)
{
    const int Limit = std::clamp(Cap, 100, 999) * 100;
    const int Before = std::min(Limit, std::clamp(Percent, 0, 999) * 100 + std::clamp(Fraction, 0, 99));
    return Before + std::clamp(Gain, 0, Limit - Before);
}
inline bool FriendshipMeatDrop(double Roll, int Quantity) { return Roll >= 0.0 && Roll < 0.18 && Quantity < 999; }
}
