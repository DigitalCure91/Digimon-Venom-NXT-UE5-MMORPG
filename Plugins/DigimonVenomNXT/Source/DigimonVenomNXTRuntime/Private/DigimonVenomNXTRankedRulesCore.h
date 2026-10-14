#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

/** Engine-independent ranked rules. Runtime adapters and native tests call these exact functions. */
namespace DigimonVenomNXTRankedRulesCore
{
    inline bool AreThresholdsValid(const int* Values, int Count)
    {
        if (!Values || Count != 6) return false;
        for (int I = 0; I < Count; ++I)
            if (Values[I] < 0 || Values[I] > 999000 || (I > 0 && Values[I] <= Values[I - 1])) return false;
        return true;
    }

    inline int GradeIndex(int Rating, const int* Thresholds)
    {
        for (int I = 5; I > 0; --I) if (Rating >= Thresholds[I]) return I;
        return 0;
    }

    struct MatchProgress { int Points = 0, Grade = 0; bool Promoted = false, PromotionPending = false; };
    inline MatchProgress ApplyPoints(int Points, int EarnedGrade, bool Won, bool Draw, bool Attacking,
        const int* Thresholds, int WinPoints = 20, int LossPoints = 5)
    {
        MatchProgress Result;
        Result.Grade = std::clamp(EarnedGrade, 0, 5);
        const bool WasPending = Result.Grade < 5 && Points >= Thresholds[Result.Grade + 1];
        const std::int64_t Delta = Draw ? 0 : Won ? std::clamp(WinPoints, 1, 100000) : -std::clamp(LossPoints, 0, 100000);
        Result.Points = static_cast<int>(std::clamp<std::int64_t>(static_cast<std::int64_t>(Points) + Delta, 0, 1000000));
        Result.Promoted = Attacking && Won && !Draw && WasPending && Result.Grade < 5 && Result.Points >= Thresholds[Result.Grade + 1];
        if (Result.Promoted) ++Result.Grade;
        Result.PromotionPending = Result.Grade < 5 && Result.Points >= Thresholds[Result.Grade + 1];
        return Result;
    }

    inline bool RewardEligible(int AttackingMatches, int Minimum = 1)
    { return AttackingMatches >= std::max(1, Minimum); }

    inline int PlacementBracket(int Placement)
    {
        return Placement <= 1 ? 0 : Placement <= 10 ? 1 : Placement <= 25 ? 2 : Placement <= 50 ? 3 :
            Placement <= 100 ? 4 : Placement <= 500 ? 5 : 6;
    }

    inline std::int64_t SeasonStart(std::int64_t Now, int Days)
    {
        // 1970-01-05 00:00:00 UTC, a Monday. No locale, daylight saving, or weekday-enum assumptions.
        constexpr std::int64_t Epoch = 345600;
        const std::int64_t Length = static_cast<std::int64_t>(std::clamp(Days, 1, 30)) * 86400;
        return Epoch + ((std::max(Now, Epoch) - Epoch) / Length) * Length;
    }

    struct EnergyState { int Energy; std::int64_t Anchor; };

    inline EnergyState Recharge(EnergyState State, std::int64_t Now, int Maximum, int Interval)
    {
        Maximum = std::clamp(Maximum, 1, 999);
        Interval = std::clamp(Interval, 1, 86400);
        State.Energy = std::clamp(State.Energy, 0, Maximum);
        if (State.Anchor <= 0 || State.Anchor > Now) { State.Anchor = Now; return State; }
        // At the cap all surplus time is discarded. A later spend begins a new recharge period.
        if (State.Energy >= Maximum) { State.Anchor = Now; return State; }
        const std::int64_t Units = (Now - State.Anchor) / Interval;
        if (Units <= 0) return State;
        const std::int64_t Missing = Maximum - State.Energy;
        if (Units >= Missing) { State.Energy = Maximum; State.Anchor = Now; }
        else { State.Energy += static_cast<int>(Units); State.Anchor += Units * Interval; }
        return State;
    }

    inline int RatingDelta(int Rating, int Opponent, float Score, int K)
    {
        const double Exponent = std::clamp((static_cast<double>(Opponent) - Rating) / 400.0, -10.0, 10.0);
        const double Expected = 1.0 / (1.0 + std::pow(10.0, Exponent));
        int Delta = static_cast<int>(std::round(std::clamp(K, 8, 100) * (std::clamp(Score, 0.0f, 1.0f) - Expected)));
        if (Score >= 1.0f) Delta = std::max(1, Delta);
        if (Score <= 0.0f) Delta = std::min(-1, Delta);
        return Delta;
    }
}
