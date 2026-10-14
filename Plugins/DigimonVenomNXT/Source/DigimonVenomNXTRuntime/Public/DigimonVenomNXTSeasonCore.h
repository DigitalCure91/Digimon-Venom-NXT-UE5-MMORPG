#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string_view>

/** Pure rules used by the authoritative private career, not the shared Ranked ladder. */
namespace DigimonVenomNXTSeasonCore
{
    constexpr int RosterSize = 16;
    constexpr int FixturesPerWeek = 8;
    constexpr int MaximumWeek = std::numeric_limits<int>::max() - 1;
    inline int Clamp(int V, int Low, int High) { return std::max(Low, std::min(V, High)); }
    struct Date { std::int64_t Year = 1; int Month = 1; int Day = 1; int Weekday = 1; };
    inline bool IsLeapYear(std::int64_t Y) { return Y > 0 && Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0); }
    inline int DaysInMonth(std::int64_t Y, int M)
    {
        constexpr int Lengths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        return M >= 1 && M <= 12 ? Lengths[M - 1] + (M == 2 && IsLeapYear(Y) ? 1 : 0) : 0;
    }
    inline std::int64_t DaysBeforeYear(std::int64_t Y)
    {
        const std::int64_t P = std::max<std::int64_t>(1, std::min<std::int64_t>(Y, 100000000)) - 1;
        return P * 365 + P / 4 - P / 100 + P / 400;
    }
    inline std::int64_t WeekStartDays(int Week) { return static_cast<std::int64_t>(Clamp(Week, 1, MaximumWeek) - 1) * 7; }
    inline Date CalendarFromDays(std::int64_t Elapsed)
    {
        Elapsed = std::max<std::int64_t>(0, std::min(Elapsed, WeekStartDays(MaximumWeek) + 6));
        const std::int64_t Cycles = Elapsed / 146097;
        std::int64_t Remaining = Elapsed % 146097;
        const auto Centuries = std::min<std::int64_t>(3, Remaining / 36524);
        Remaining -= Centuries * 36524;
        const auto Quads = Remaining / 1461;
        Remaining %= 1461;
        const auto Singles = std::min<std::int64_t>(3, Remaining / 365);
        Remaining -= Singles * 365;
        Date D; D.Year = 1 + Cycles * 400 + Centuries * 100 + Quads * 4 + Singles;
        while (D.Month < 12 && Remaining >= DaysInMonth(D.Year, D.Month)) Remaining -= DaysInMonth(D.Year, D.Month++);
        D.Day = static_cast<int>(Remaining) + 1; D.Weekday = static_cast<int>(Elapsed % 7) + 1;
        return D;
    }
    inline std::int64_t MonthKey(const Date& D) { return (D.Year - 1) * 12 + D.Month; }
    inline bool IsAnnualWeek(int Week)
    {
        const auto Start = WeekStartDays(Week); const auto D = CalendarFromDays(Start);
        const auto LastDay = DaysBeforeYear(D.Year + 1) - 1;
        return LastDay >= Start && LastDay <= Start + 6;
    }
    inline bool IsChampionshipWeek(int Week, int Interval = 4)
    {
        const auto Start = WeekStartDays(Week);
        return Clamp(Week, 1, MaximumWeek) % Clamp(Interval, 1, 52) == 0 ||
            MonthKey(CalendarFromDays(Start)) != MonthKey(CalendarFromDays(Start + 6)) || IsAnnualWeek(Week);
    }
    inline int OpponentLevel(int Week, int StartingLevel = 5, int WeeksPerLevel = 3, int MaxLevel = 100)
    {
        const int Cap = Clamp(MaxLevel, 1, 200);
        const auto Growth = static_cast<std::int64_t>(Clamp(Week, 1, MaximumWeek) - 1) / Clamp(WeeksPerLevel, 1, 52);
        return static_cast<int>(std::min<std::int64_t>(Cap, Clamp(StartingLevel, 1, Cap) + Growth));
    }
    inline int EloGain(int WinnerRating, int LoserRating)
    {
        const double Gap = static_cast<double>(Clamp(LoserRating, 600, 2400) - Clamp(WinnerRating, 600, 2400));
        return std::max(4, static_cast<int>(std::lround(32.0 * (1.0 - 1.0 / (1.0 + std::pow(10.0, Gap / 400.0))))));
    }
    inline int DrawRatingChange(int RatingA, int RatingB)
    {
        const double ExpectedA = 1.0 / (1.0 + std::pow(10.0, static_cast<double>(Clamp(RatingB,600,2400) - Clamp(RatingA,600,2400)) / 400.0));
        return static_cast<int>(std::lround(32.0 * (0.5 - ExpectedA)));
    }
    inline bool BetterStanding(int ARating, int AWins, int ALosses, std::string_view AId,
                               int BRating, int BWins, int BLosses, std::string_view BId)
    {
        if (ARating != BRating) return ARating > BRating;
        if (AWins != BWins) return AWins > BWins;
        if (ALosses != BLosses) return ALosses < BLosses;
        return AId < BId;
    }
    inline int RivalryHeat(int Heat, bool Title) { return std::min(100, Clamp(Heat,0,100) + (Title ? 24 : 12)); }
    inline int DecayRivalry(int Heat) { return std::max(0, Clamp(Heat,0,100) - 2); }
    inline bool CanSettle(std::string_view Current, std::string_view Pending, std::string_view Requested,
                          std::string_view LastSettled, bool Resolved)
    {
        return !Current.empty() && !Resolved && Current == Pending && Current == Requested && Current != LastSettled;
    }
    inline bool ShouldPayPeriod(std::int64_t Period, std::int64_t LastPaid) { return Period > 0 && Period > LastPaid; }
    inline bool IsDefenseMilestone(int Defenses, int Interval) { return Defenses > 0 && Defenses % Clamp(Interval,1,100) == 0; }
    struct RewardRules
    {
        int MatchBase = 25;
        int MatchPerLevel = 7;
        int MonthBase = 0;
        int MonthPerWin = 0;
        int MonthRankBonus = 0;
        int MonthChampionBonus = 0;
        int YearBase = 0;
        int YearPerWin = 0;
        int YearRankBonus = 0;
        int YearChampionBonus = 0;
    };
    inline int MatchUnitXP(int Level, int StageTier) { return 24 + Clamp(Level,1,200) * 12 + Clamp(StageTier,0,6) * 8; }
    inline int ReserveXP(int XP) { return std::max(0, XP) / 2; }
    inline std::int64_t MatchCredits(int Level, const RewardRules& R = {})
    {
        return Clamp(R.MatchBase,0,1000000) + static_cast<std::int64_t>(Clamp(Level,1,200)) * Clamp(R.MatchPerLevel,0,1000000);
    }
    inline std::int64_t PeriodCredits(int Wins, int Rank, bool Champion, bool Annual, const RewardRules& R = {})
    {
        const int Base = Annual ? R.YearBase : R.MonthBase;
        const int PerWin = Annual ? R.YearPerWin : R.MonthPerWin;
        const int RankBonus = Annual ? R.YearRankBonus : R.MonthRankBonus;
        const int ChampionBonus = Annual ? R.YearChampionBonus : R.MonthChampionBonus;
        return Clamp(Base,0,1000000) + static_cast<std::int64_t>(Clamp(Wins,0,Annual ? 53 : 5)) * Clamp(PerWin,0,1000000) +
            static_cast<std::int64_t>(16 - Clamp(Rank,1,16)) * Clamp(RankBonus,0,1000000) / 15 + (Champion ? Clamp(ChampionBonus,0,1000000) : 0);
    }
    inline std::int64_t AddCreditsSaturated(std::int64_t Current, std::int64_t Gain)
    {
        Current = std::max<std::int64_t>(0, Current); Gain = std::max<std::int64_t>(0, Gain);
        return Gain > std::numeric_limits<std::int64_t>::max() - Current ? std::numeric_limits<std::int64_t>::max() : Current + Gain;
    }
}
