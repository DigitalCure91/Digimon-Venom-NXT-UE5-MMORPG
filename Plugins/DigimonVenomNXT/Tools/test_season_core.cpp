// Runs the actual production Season arithmetic and transaction fences without Unreal.
// Fixtures were independently generated using Python datetime's Gregorian calendar.
// Engine transactions, networking, UMG and disk-failure integration still require UE tests.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTSeasonCore.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
namespace S = DigimonVenomNXTSeasonCore;
int Checks = 0;
void Require(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
void DateIs(std::int64_t Days, std::int64_t Year, int Month, int Day, int Weekday)
{
    const auto D = S::CalendarFromDays(Days);
    Require(D.Year == Year && D.Month == Month && D.Day == Day && D.Weekday == Weekday,
        "private calendar agrees with independent Gregorian date and weekday fixture");
}
void Calendar()
{
    struct Fixture { std::int64_t Elapsed; int Year, Month, Day, Weekday; };
    const Fixture Dates[] = {
        {0LL, 1, 1, 1, 1},
        {364LL, 1, 12, 31, 1},
        {1154LL, 4, 2, 29, 7},
        {36218LL, 100, 3, 1, 1},
        {145790LL, 400, 2, 29, 2},
        {693654LL, 1900, 3, 1, 4},
        {730178LL, 2000, 2, 29, 2},
        {3652058LL, 9999, 12, 31, 5},
        {2591043LL, 7095, 1, 14, 1},
        {2236677LL, 6124, 10, 25, 3},
        {2977452LL, 8152, 12, 27, 3},
        {1534479LL, 4202, 4, 7, 3},
        {2394859LL, 6557, 11, 26, 6},
        {2456970LL, 6727, 12, 17, 6},
        {3069789LL, 8405, 10, 19, 3},
        {694942LL, 1903, 9, 10, 4},
        {3251422LL, 8903, 2, 4, 7},
        {3457674LL, 9467, 10, 17, 4},
        {1395819LL, 3822, 8, 17, 6},
        {1609374LL, 4407, 4, 27, 5},
        {2662854LL, 7291, 8, 25, 6},
        {3311876LL, 9068, 8, 11, 2},
        {1509300LL, 4133, 4, 29, 3},
        {1290307LL, 3533, 9, 29, 5},
        {1642285LL, 4497, 6, 4, 2},
        {2923932LL, 8006, 6, 16, 5},
        {859605LL, 2354, 7, 10, 6},
        {3194114LL, 8746, 3, 11, 1},
        {2752627LL, 7537, 6, 10, 4},
        {3623165LL, 9920, 11, 22, 1},
        {1530388LL, 4191, 1, 23, 7},
        {458388LL, 1256, 1, 10, 1},
        {1784624LL, 4887, 2, 19, 3},
        {3441164LL, 9422, 8, 4, 7},
        {2664211LL, 7295, 5, 13, 5},
        {1672432LL, 4579, 12, 19, 7},
        {274068LL, 751, 5, 18, 5},
        {2119772LL, 5804, 9, 28, 5},
        {2932692LL, 8030, 6, 10, 1},
        {2802307LL, 7673, 6, 16, 5},
        {1460045LL, 3998, 6, 21, 7},
        {1692768LL, 4635, 8, 24, 1},
        {1691854LL, 4633, 2, 21, 4},
        {3362206LL, 9206, 5, 30, 2},
        {3093485LL, 8470, 9, 4, 4},
        {3355716LL, 9188, 8, 22, 1},
        {1303799LL, 3570, 9, 7, 1},
        {2783964LL, 7623, 3, 28, 2},
        {74766LL, 205, 9, 15, 7},
        {3491785LL, 9561, 3, 9, 4},
        {1481300LL, 4056, 8, 30, 3},
        {2493332LL, 6827, 7, 7, 3},
        {497181LL, 1362, 3, 28, 7},
        {1933295LL, 5294, 3, 8, 1},
        {1033395LL, 2830, 5, 5, 7},
        {718137LL, 1967, 3, 13, 1},
    };
    for (const auto& D : Dates) DateIs(D.Elapsed,D.Year,D.Month,D.Day,D.Weekday);
    Require(!S::IsLeapYear(1) && S::IsLeapYear(4) && !S::IsLeapYear(100) && S::IsLeapYear(400),
        "Gregorian four-year, century and four-century boundaries are correct");
    Require(S::IsLeapYear(10000) && !S::IsLeapYear(10100) && S::IsLeapYear(10400),
        "fictional calendar supports years beyond platform date limits");
    Require(!S::IsLeapYear(0) && !S::IsLeapYear(-4), "invalid nonpositive years are not leap years");
    Require(S::DaysInMonth(1,2)==28 && S::DaysInMonth(4,2)==29 && S::DaysInMonth(100,2)==28,
        "February has its true Gregorian length");
    Require(S::DaysInMonth(1,4)==30 && S::DaysInMonth(1,1)==31 && S::DaysInMonth(1,12)==31,
        "thirty and thirty-one day months retain their lengths");
    Require(S::DaysInMonth(1,0)==0 && S::DaysInMonth(1,13)==0, "invalid month is rejected");
    DateIs(-1,1,1,1,1);
    const auto Leap = S::CalendarFromDays(S::DaysBeforeYear(10000)+59);
    Require(Leap.Year==10000 && Leap.Month==2 && Leap.Day==29, "year ten thousand includes February twenty-nine");
    const auto NonLeap = S::CalendarFromDays(S::DaysBeforeYear(10100)+59);
    Require(NonLeap.Year==10100 && NonLeap.Month==3 && NonLeap.Day==1, "non-leap century advances directly to March");
    Require(S::WeekStartDays(1)==0 && S::WeekStartDays(2)==7 && S::WeekStartDays(53)==364,
        "booking weeks are explicit seven-day steps from Year one");
    Require(S::WeekStartDays(0)==0 && S::WeekStartDays(INT_MIN)==0,
        "invalid legacy weeks safely map to the first booking");
    Require(S::WeekStartDays(INT_MAX)==S::WeekStartDays(S::MaximumWeek), "huge weeks saturate without integer multiplication overflow");
    const auto Maximum = S::CalendarFromDays(INT64_MAX);
    const auto Bound = S::CalendarFromDays(S::WeekStartDays(S::MaximumWeek)+6);
    Require(Maximum.Year==Bound.Year && Maximum.Month==Bound.Month && Maximum.Day==Bound.Day,
        "corrupt elapsed-day input is bounded by supported career range");
    Require(!S::IsAnnualWeek(52) && S::IsAnnualWeek(53) && !S::IsAnnualWeek(54),
        "the first year-end event occurs only in the booking containing December thirty-one");
    Require(!S::IsChampionshipWeek(1) && S::IsChampionshipWeek(4) && S::IsChampionshipWeek(5),
        "regular fourth-week and January-to-February boundary cards have title matches");
    Require(S::IsChampionshipWeek(53,52), "the annual card remains a championship even with a long regular interval");
    const auto Jan = S::CalendarFromDays(30), Feb = S::CalendarFromDays(31), NextJan = S::CalendarFromDays(365);
    Require(S::MonthKey(Feb)==S::MonthKey(Jan)+1 && S::MonthKey(NextJan)==13,
        "month fences are consecutive and continue across years");
}
void Difficulty()
{
    Require(S::OpponentLevel(1)==5 && S::OpponentLevel(2)==5 && S::OpponentLevel(3)==5,
        "all first three bookings start at level five with default settings");
    Require(S::OpponentLevel(4)==6 && S::OpponentLevel(7)==7 && S::OpponentLevel(52)==22,
        "opponents train one level every three booking weeks");
    Require(S::OpponentLevel(286)==100 && S::OpponentLevel(INT_MAX)==100,
        "late careers remain at the configured level ceiling");
    Require(S::OpponentLevel(1,5,3,4)==4 && S::OpponentLevel(1,0,0,0)==1,
        "custom starting level and malformed settings cannot exceed a safe positive cap");
    Require(S::OpponentLevel(200,5,1,200)==200 && S::OpponentLevel(1000,5,1,INT_MAX)==200,
        "custom fast progression respects the supported two-hundred level maximum");
    int Previous=0;
    bool Monotonic=true;
    for (int Week=1; Week<=500; ++Week)
    {
        const int Level=S::OpponentLevel(Week);
        Monotonic = Monotonic && Level>=Previous && Level<=100 && Level>=5;
        Previous=Level;
    }
    Require(Monotonic, "five-hundred-booking progression never reverses or exceeds its cap");
}
void StandingsAndRivalries()
{
    Require(S::EloGain(1200,1200)==16, "equal-rated victory awards the expected Elo change");
    Require(S::EloGain(600,2400)>S::EloGain(2400,600), "an underdog upset gains more rating than beating a weaker opponent");
    Require(S::EloGain(INT_MIN,INT_MAX)<=32 && S::EloGain(INT_MAX,INT_MIN)>=4,
        "extreme saved ratings still produce bounded positive win gains");
    Require(S::DrawRatingChange(1200,1200)==0, "equal-rated draw leaves rating unchanged");
    Require(S::DrawRatingChange(600,2400)>0 && S::DrawRatingChange(2400,600)<0,
        "draws reward the lower-rated entrant and reduce the favorite");
    Require(S::BetterStanding(1300,0,10,"z",1200,20,0,"a"), "rating is the first standings key");
    Require(S::BetterStanding(1200,3,10,"z",1200,2,0,"a"), "wins break equal-rating ties");
    Require(S::BetterStanding(1200,3,1,"z",1200,3,2,"a"), "fewer losses break equal-rating and win ties");
    Require(S::BetterStanding(1200,3,1,"a",1200,3,1,"z"), "stable tamer identity deterministically breaks a complete tie");
    Require(!S::BetterStanding(1200,3,1,"a",1200,3,1,"a"), "standings comparator is strict for identical records");
    Require(S::RivalryHeat(0,false)==12 && S::RivalryHeat(0,true)==24,
        "title meetings build twice the normal rivalry heat");
    Require(S::RivalryHeat(99,true)==100 && S::RivalryHeat(INT_MAX,true)==100,
        "rivalry intensity remains capped at one hundred");
    Require(S::DecayRivalry(100)==98 && S::DecayRivalry(1)==0 && S::DecayRivalry(INT_MIN)==0,
        "manual weekly rivalry decay cannot become negative");
    Require(!S::IsDefenseMilestone(0,3) && !S::IsDefenseMilestone(2,3) && S::IsDefenseMilestone(3,3) && S::IsDefenseMilestone(6,3),
        "championship retention milestones occur only after positive interval multiples");
    Require(!S::IsDefenseMilestone(-3,3) && S::IsDefenseMilestone(1,0),
        "bad defense settings cannot create a zero-modulus operation or negative milestone");
}
void ReceiptFences()
{
    Require(S::CanSettle("career:week1","career:week1","career:week1","",false),
        "the current pending unresolved battle can settle");
    Require(!S::CanSettle("career:week1","career:week1","career:week1","career:week1",false),
        "an already committed context cannot pay twice");
    Require(!S::CanSettle("career:week1","career:week1","career:week1","",true),
        "resolved fixtures reject duplicated terminal commands");
    Require(!S::CanSettle("career:week2","career:week2","career:week1","",false),
        "stale battle context from the prior booking cannot settle a new card");
    Require(!S::CanSettle("career:week1","other:week1","career:week1","",false),
        "a different pending career receipt cannot settle this account's match");
    Require(!S::CanSettle("","","","",false) && !S::CanSettle("career:week1","","career:week1","",false),
        "missing schedule and missing pending receipt reject settlement");
    Require(S::ShouldPayPeriod(1,0) && S::ShouldPayPeriod(13,12), "first and subsequent unclaimed periods can pay");
    Require(!S::ShouldPayPeriod(0,0) && !S::ShouldPayPeriod(12,12) && !S::ShouldPayPeriod(11,12),
        "zero, repeated and stale period payouts are rejected");
    Require(S::ShouldPayPeriod(INT64_MAX,INT64_MAX-1) && !S::ShouldPayPeriod(INT64_MAX,INT64_MAX),
        "period fences support long careers without overflow-based repeats");
}
void Rewards()
{
    Require(S::MatchUnitXP(5,2)==100 && S::MatchUnitXP(20,3)==288,
        "battle XP rewards use opponent level and evolution stage");
    Require(S::MatchUnitXP(100,5)>S::MatchUnitXP(5,2),
        "developing stronger league opponents awards more XP");
    Require(S::MatchUnitXP(INT_MIN,INT_MIN)==36 && S::MatchUnitXP(INT_MAX,INT_MAX)==2472,
        "invalid and oversized level or stage inputs cannot overflow XP rewards");
    Require(S::ReserveXP(100)==50 && S::ReserveXP(101)==50 && S::ReserveXP(-1)==0,
        "reserve experience is half the active award with safe downward rounding");
    Require(S::MatchCredits(5)==60 && S::MatchCredits(100)==725,
        "default victory credits scale with the actual scheduled enemy level");
    Require(S::PeriodCredits(0,16,false,false)==0 && S::PeriodCredits(5,1,true,false)==0,
        "source circuit has no monthly currency payout");
    Require(S::PeriodCredits(0,16,false,true)==0 && S::PeriodCredits(53,1,true,true)==0,
        "source circuit has no annual currency payout");
    bool Monotonic=true;
    for (int Rank=16; Rank>1; --Rank)
        Monotonic = Monotonic && S::PeriodCredits(3,Rank-1,false,false)>=S::PeriodCredits(3,Rank,false,false);
    for (int Wins=0; Wins<53; ++Wins)
        Monotonic = Monotonic && S::PeriodCredits(Wins+1,5,false,true)>=S::PeriodCredits(Wins,5,false,true);
    Require(Monotonic, "better placement and more period wins never reduce the payout");
    S::RewardRules R;
    R.MatchBase=R.MatchPerLevel=R.MonthBase=R.MonthPerWin=R.MonthRankBonus=R.MonthChampionBonus=
        R.YearBase=R.YearPerWin=R.YearRankBonus=R.YearChampionBonus=INT_MAX;
    Require(S::MatchCredits(INT_MAX,R)==201000000LL, "malformed match rewards remain bounded using widened arithmetic");
    Require(S::PeriodCredits(INT_MAX,1,true,true,R)==56000000LL,
        "malformed annual settings cannot overflow the payout calculation");
    R.MatchBase=R.MatchPerLevel=R.MonthBase=R.MonthPerWin=R.MonthRankBonus=R.MonthChampionBonus=
        R.YearBase=R.YearPerWin=R.YearRankBonus=R.YearChampionBonus=INT_MIN;
    Require(S::MatchCredits(5,R)==0 && S::PeriodCredits(3,1,true,false,R)==0,
        "negative configured rewards cannot deduct currency");
    Require(S::AddCreditsSaturated(10,20)==30 && S::AddCreditsSaturated(-10,20)==20,
        "currency accumulation repairs negative legacy balances while retaining a real award");
    Require(S::AddCreditsSaturated(INT64_MAX-10,11)==INT64_MAX && S::AddCreditsSaturated(INT64_MAX,INT64_MAX)==INT64_MAX,
        "credits saturate instead of wrapping at the integer limit");
    Require(S::AddCreditsSaturated(25,-10)==25, "negative gains cannot remove earned credits");
}
}
int main()
{
    Calendar(); Difficulty(); StandingsAndRivalries(); ReceiptFences(); Rewards();
    std::cout << "Season core: " << Checks << " checks passed.\n";
}
