#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTRankedRulesCore.h"

namespace DigimonVenomNXTRankedRules
{
    inline TArray<int32> ValidThresholds(const TArray<int32>& Configured)
    {
        return DigimonVenomNXTRankedRulesCore::AreThresholdsValid(Configured.GetData(), Configured.Num())
            ? Configured : TArray<int32>{0, 100, 300, 600, 1000, 1800};
    }

    inline int32 GradeIndex(int32 Rating, const TArray<int32>& Thresholds)
    {
        return DigimonVenomNXTRankedRulesCore::GradeIndex(Rating, Thresholds.GetData());
    }

    inline int64 SeasonStart(int64 Now, int32 Days)
    {
        return DigimonVenomNXTRankedRulesCore::SeasonStart(Now, Days);
    }

    inline void Recharge(int32& Energy, int64& Anchor, int64 Now, int32 Maximum, int32 Interval)
    {
        const auto Result = DigimonVenomNXTRankedRulesCore::Recharge({Energy, Anchor}, Now, Maximum, Interval);
        Energy = Result.Energy; Anchor = Result.Anchor;
    }

    inline int32 RatingDelta(int32 Rating, int32 Opponent, float Score, int32 K)
    {
        return DigimonVenomNXTRankedRulesCore::RatingDelta(Rating, Opponent, Score, K);
    }
}
