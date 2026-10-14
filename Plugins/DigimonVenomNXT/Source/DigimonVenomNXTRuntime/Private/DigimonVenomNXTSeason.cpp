#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTSeasonCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTRewardCore.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTTamers.h"
#include "Misc/Crc.h"

namespace
{
    using namespace DigimonVenomNXTSeasonCore;
    // Unity builds combine unrelated cpp files into one translation unit. Keep
    // anonymous-namespace data names specific to Season to avoid C4459 shadows.
    const TCHAR* SeasonPlayerId = TEXT("player");
    const TCHAR* SeasonTamerNames[] = {TEXT("Rei Voltage"), TEXT("Mika Cipher"), TEXT("Kai Nightfall"), TEXT("Sora Pulse"),
        TEXT("Ren Aegis"), TEXT("Yuna Arc"), TEXT("Kira Flux"), TEXT("Toma Zenith"), TEXT("Aoi Vortex"),
        TEXT("Riku Chrome"), TEXT("Nia Eclipse"), TEXT("Haru Nova"), TEXT("Akira Zero"), TEXT("Mei Prism"), TEXT("Jin Overdrive")};
    const TCHAR* SeasonMonthNames[] = {TEXT("January"),TEXT("February"),TEXT("March"),TEXT("April"),TEXT("May"),TEXT("June"),
        TEXT("July"),TEXT("August"),TEXT("September"),TEXT("October"),TEXT("November"),TEXT("December")};
    const TCHAR* SeasonWeekdayNames[] = {TEXT("Monday"),TEXT("Tuesday"),TEXT("Wednesday"),TEXT("Thursday"),TEXT("Friday"),TEXT("Saturday"),TEXT("Sunday")};
    int32 Increment(int32 Value) { return Value < MAX_int32 ? FMath::Max(0, Value) + 1 : MAX_int32; }
    int32 StreamSeed(const FDigimonSeasonCareer& S, const TCHAR* Purpose)
    {
        return static_cast<int32>(FCrc::StrCrc32(*FString::Printf(TEXT("%d:%d:%s"),S.Seed,S.Week,Purpose)));
    }
    RewardRules Rewards()
    {
        const auto* S = GetDefault<UDigimonVenomNXTSettings>(); RewardRules R;
        R.MatchBase=S->SeasonMatchBaseCredits; R.MatchPerLevel=S->SeasonMatchCreditsPerLevel;
        R.MonthBase=S->SeasonMonthlyBaseCredits; R.MonthPerWin=S->SeasonMonthlyCreditsPerWin;
        R.MonthRankBonus=S->SeasonMonthlyRankBonus; R.MonthChampionBonus=S->SeasonMonthlyChampionBonus;
        R.YearBase=S->SeasonYearlyBaseCredits; R.YearPerWin=S->SeasonYearlyCreditsPerWin;
        R.YearRankBonus=S->SeasonYearlyRankBonus; R.YearChampionBonus=S->SeasonYearlyChampionBonus;
        return R;
    }
    FDigimonSeasonTamer* MutableTamer(FDigimonSeasonCareer& S, const FString& Id)
    { return S.Roster.FindByPredicate([&](const FDigimonSeasonTamer& T){ return T.TamerId==Id; }); }
    void AddNews(FDigimonSeasonCareer& S, const FString& Text)
    { S.News.Insert(Text,0); if (S.News.Num()>12) S.News.SetNum(12); }
    void UpdateRankings(FDigimonSeasonCareer& S)
    {
        TArray<int32> Order; for(int32 I=0;I<S.Roster.Num();++I) Order.Add(I);
        Order.Sort([&](int32 A,int32 B)
        {
            const auto& X=S.Roster[A]; const auto& Y=S.Roster[B];
            return BetterStanding(X.Rating,X.Wins,X.Losses,TCHAR_TO_UTF8(*X.TamerId),
                Y.Rating,Y.Wins,Y.Losses,TCHAR_TO_UTF8(*Y.TamerId));
        });
        for(int32 I=0;I<Order.Num();++I) S.Roster[Order[I]].Rank=I+1;
        if(const auto* P=DigimonVenomNXTSeason::FindTamer(S,SeasonPlayerId))
        { S.Wins=P->Wins; S.Losses=P->Losses; S.Draws=P->Draws; S.Championships=P->Titles; }
    }
    void UpdateViews(FDigimonPlayerProfile& Profile)
    {
        auto& S=Profile.Season;
        if(auto* P=MutableTamer(S,SeasonPlayerId))
        {
            P->Name=Profile.Username; P->TamerStyleId=Profile.TamerStyleId; P->Team.Reset();
            for(const FGuid& Id:Profile.Party)
                if(const auto* Owned=Profile.Collection.FindByPredicate([&](const FDigimonOwnedPartner& N){return N.InstanceId==Id;}))
                    P->Team.Add(*Owned);
        }
        UpdateRankings(S);
        const auto* Settings=GetDefault<UDigimonVenomNXTSettings>();
        S.DefenseRewardInterval=Clamp(Settings->SeasonDefenseRewardInterval,1,100);
        S.DefenseRewardCredits=Clamp(Settings->SeasonDefenseRewardCredits,0,1000000);
        S.MonthRewardEstimate=DigimonVenomNXTSeason::MonthRewardPreview(S);
        S.YearRewardEstimate=DigimonVenomNXTSeason::YearRewardPreview(S);
    }
    int64 Award(FDigimonPlayerProfile& Profile,const FString& Id,const FString& Reason,int64 Requested)
    {
        auto& S=Profile.Season;
        if(Requested<=0 || S.Payouts.ContainsByPredicate([&](const FDigimonSeasonPayout& P){return P.PayoutId==Id;})) return 0;
        const int64 Before=FMath::Max<int64>(0,Profile.Credits);
        Profile.Credits=AddCreditsSaturated(Before,Requested);
        const int64 Actual=Profile.Credits-Before;
        FDigimonSeasonPayout P; P.PayoutId=Id; P.Reason=Reason; P.Week=S.Week; P.Credits=Actual;
        S.Payouts.Insert(P,0);
        const int32 Limit=Clamp(GetDefault<UDigimonVenomNXTSettings>()->SeasonPayoutHistoryCount,12,128);
        if(S.Payouts.Num()>Limit) S.Payouts.SetNum(Limit);
        S.TotalCreditsEarned=AddCreditsSaturated(S.TotalCreditsEarned,Actual);
        S.WeekCreditsEarned=AddCreditsSaturated(S.WeekCreditsEarned,Actual);
        return Actual;
    }
    /** Only explicit player actions move this clock; pays a crossed period once even after ledger eviction. */
    void MoveCalendar(FDigimonPlayerProfile& Profile,int64 NewElapsed)
    {
        auto& S=Profile.Season;
        const int64 OldElapsed=WeekStartDays(S.Week)+Clamp(S.DayOffset,0,6);
        if(NewElapsed<=OldElapsed) return;
        const Date Old=CalendarFromDays(OldElapsed); const Date Next=CalendarFromDays(NewElapsed);
        UpdateRankings(S);
        if(MonthKey(Next)>MonthKey(Old))
        {
            const int64 Period=MonthKey(Old);
            if(ShouldPayPeriod(Period,S.LastPaidMonth))
            {
                const FString Label=FString::Printf(TEXT("%s, Year %lld performance payroll"),SeasonMonthNames[Old.Month-1],static_cast<long long>(Old.Year));
                const int64 Amount=Award(Profile,FString::Printf(TEXT("month:%lld"),static_cast<long long>(Period)),Label,DigimonVenomNXTSeason::MonthRewardPreview(S));
                S.LastPaidMonth=Period;
                AddNews(S,FString::Printf(TEXT("%s: +%lld credits."),*Label,static_cast<long long>(Amount)));
            }
            S.MonthWins=S.MonthLosses=S.MonthDraws=0;
        }
        if(Next.Year>Old.Year)
        {
            if(ShouldPayPeriod(Old.Year,S.LastPaidYear))
            {
                const FString Label=FString::Printf(TEXT("Year %lld career performance bonus"),static_cast<long long>(Old.Year));
                const int64 Amount=Award(Profile,FString::Printf(TEXT("year:%lld"),static_cast<long long>(Old.Year)),Label,DigimonVenomNXTSeason::YearRewardPreview(S));
                S.LastPaidYear=Old.Year;
                AddNews(S,FString::Printf(TEXT("%s: +%lld credits. Your career continues."),*Label,static_cast<long long>(Amount)));
            }
            S.YearWins=S.YearLosses=S.YearDraws=0;
        }
        S.DayOffset=static_cast<int32>(NewElapsed-WeekStartDays(S.Week));
    }
    FDigimonOwnedPartner MakePartner(const FDigimonSpeciesDefinition& Def,int32 Level,FRandomStream& Random,const UDigimonVenomNXTDataSubsystem* Data)
    {
        FDigimonOwnedPartner P;
        P.InstanceId=FGuid(Random.GetUnsignedInt(),Random.GetUnsignedInt(),Random.GetUnsignedInt(),Random.GetUnsignedInt());
        if(!P.InstanceId.IsValid()) P.InstanceId=FGuid(1,0,0,0);
        P.SpeciesId=Def.SpeciesId; P.Level=Level;
        P.Experience=DigimonVenomNXTProgressionCore::ExperienceFloor(Level);
        P.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        P.Variant=EDigimonVariant::Normal; // Reference season roster begins with ordinary partners.
        const auto U=DigimonVenomNXTAutoBattle::BuildUnit(P,Data); P.CurrentHP=U.Stats.MaxHP; P.CurrentSP=U.Stats.MaxSP; P.Moves=U.Moves;
        return P;
    }
    void DevelopTeams(FDigimonSeasonCareer& S,const UDigimonVenomNXTDataSubsystem* Data)
    {
        if(!Data) return;
        FRandomStream Random(StreamSeed(S,TEXT("development")));
        const auto* Settings=GetDefault<UDigimonVenomNXTSettings>();
        const int32 Interval=Clamp(Settings->SeasonWeeksPerLevel,1,52);
        const int32 LevelCap=FMath::Min(99,Clamp(Settings->SeasonMaxOpponentLevel,1,200));
        for(auto& T:S.Roster)
        {
            if(T.bPlayer) continue;
            const int64 Development=static_cast<int64>(T.Wins)+T.Losses+T.Draws;
            for(int32 Index=0;Index<T.Team.Num();++Index)
            {
                auto& P=T.Team[Index];
                if(Development>0 && Development%Interval==0) P.Level=FMath::Min(LevelCap,P.Level+1);
                P.ABI=static_cast<int32>(FMath::Min<int64>(200,Development/6));
                P.CAM=static_cast<int32>(FMath::Min<int64>(100,10+Development/3));
                if(Development>0 && Development%12==0)
                {
                    FDigimonSpeciesDefinition Current;
                    TArray<FName> Routes;
                    if(Data->GetSpecies(P.SpeciesId,Current))
                        for(const auto& Route:Current.Evolutions)
                        {
                            FDigimonSpeciesDefinition Target;
                            if(Route.RequiredLevel<=P.Level && Data->GetSpecies(Route.TargetSpeciesId,Target) &&
                                !Target.bPlaceholder && Target.bHasNormalArtwork) Routes.Add(Target.SpeciesId);
                        }
                    // Source circuit NPC coaching advances a normal form at the
                    // route's level gate, retaining that opponent's earned level.
                    if(!Routes.IsEmpty())
                    {
                        P.SpeciesId=Routes[Random.RandRange(0,Routes.Num()-1)]; P.Moves.Reset();
                        FDigimonSpeciesDefinition Target;
                        if(Index==0 && Data->GetSpecies(P.SpeciesId,Target))
                            AddNews(S,FString::Printf(TEXT("%s's lead partner digivolved into %s."),*T.Name,*Target.DisplayName.ToString()));
                    }
                }
                P.Experience=DigimonVenomNXTProgressionCore::ExperienceFloor(P.Level);
                P.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
                const auto U=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);
                P.CurrentHP=U.Stats.MaxHP; P.CurrentSP=U.Stats.MaxSP; P.Moves=U.Moves;
            }
        }
        S.OpponentLevel=DigimonVenomNXTSeason::NextOpponentLevel(S);
    }
    void BookWeek(FDigimonPlayerProfile& Profile)
    {
        auto& S=Profile.Season; UpdateViews(Profile);
        S.bChampionshipWeek=IsChampionshipWeek(S.Week,GetDefault<UDigimonVenomNXTSettings>()->SeasonTitleIntervalWeeks);
        S.bAnnualEvent=IsAnnualWeek(S.Week);
        const auto Date=CalendarFromDays(WeekStartDays(S.Week));
        S.EventName=S.bAnnualEvent ? FString::Printf(TEXT("World Circuit Grand Championship | Year %lld"),static_cast<long long>(Date.Year)) :
            S.bChampionshipWeek ? TEXT("World Circuit Championship") : TEXT("Venom Circuit | Weekly Clash");
        TArray<FString> Remaining; for(const auto& T:S.Roster) Remaining.Add(T.TamerId);
        struct Pair { FString Home; FString Away; bool Title=false; };
        TArray<Pair> Pairs;
        if(S.bChampionshipWeek)
        {
            const FDigimonSeasonTamer* Challenger=nullptr;
            for(const auto& T:S.Roster) if(T.TamerId!=S.ChampionId && (!Challenger || T.Rank<Challenger->Rank)) Challenger=&T;
            if(Challenger && Remaining.Contains(S.ChampionId))
            { Pairs.Add({S.ChampionId,Challenger->TamerId,true}); Remaining.Remove(S.ChampionId); Remaining.Remove(Challenger->TamerId); }
        }
        FRandomStream Random(StreamSeed(S,TEXT("booking")));
        if(Remaining.Contains(SeasonPlayerId))
        {
            const auto* Human=DigimonVenomNXTSeason::FindTamer(S,SeasonPlayerId);
            TArray<FString> Candidates=Remaining; Candidates.Remove(SeasonPlayerId);
            if(Human && Candidates.Num()>1) Candidates.Remove(Human->LastOpponentId);
            FString Opponent; int32 HighestHeat=-1;
            if(S.Week%3==0)
                for(const auto& R:S.Rivalries)
                {
                    const FString Other=R.TamerAId==SeasonPlayerId ? R.TamerBId : R.TamerBId==SeasonPlayerId ? R.TamerAId : FString();
                    if(Candidates.Contains(Other) && R.Heat>=15 && R.Heat>HighestHeat) { Opponent=Other; HighestHeat=R.Heat; }
                }
            if(Opponent.IsEmpty() && !Candidates.IsEmpty())
            {
                Candidates.Sort([&](const FString& A,const FString& B)
                {
                    const auto* X=DigimonVenomNXTSeason::FindTamer(S,A); const auto* Y=DigimonVenomNXTSeason::FindTamer(S,B);
                    const int32 Rating=Human ? Human->Rating : 1200;
                    const int32 DX=X ? FMath::Abs(X->Rating-Rating) : MAX_int32, DY=Y ? FMath::Abs(Y->Rating-Rating) : MAX_int32;
                    return DX==DY ? A<B : DX<DY;
                });
                Opponent=Candidates[Random.RandRange(0,FMath::Min(4,Candidates.Num())-1)];
            }
            if(!Opponent.IsEmpty()) { Pairs.Add({SeasonPlayerId,Opponent,false}); Remaining.Remove(SeasonPlayerId); Remaining.Remove(Opponent); }
        }
        Remaining.Sort();
        for(int32 I=Remaining.Num()-1;I>0;--I) Remaining.Swap(I,Random.RandRange(0,I));
        for(int32 I=0;I+1<Remaining.Num();I+=2) Pairs.Add({Remaining[I],Remaining[I+1],false});
        Pairs.StableSort([](const Pair& A,const Pair& B)
        {
            const bool AP=A.Home==SeasonPlayerId || A.Away==SeasonPlayerId, BP=B.Home==SeasonPlayerId || B.Away==SeasonPlayerId;
            return AP!=BP ? AP : A.Title!=B.Title ? !A.Title : false;
        });
        S.CurrentCard.Reset();
        for(int32 I=0;I<Pairs.Num();++I)
        {
            const auto& P=Pairs[I]; FDigimonSeasonMatch M;
            M.MatchId=FString::Printf(TEXT("%s:%d:%d"),*S.CareerId,S.Week,I);
            M.HomeTamerId=P.Home; M.AwayTamerId=P.Away; M.bTitleMatch=P.Title; M.bPlayerMatch=P.Home==SeasonPlayerId || P.Away==SeasonPlayerId;
            M.DayOfWeek=M.bPlayerMatch ? 2 : FMath::Min(7,3+(I-1)*5/7);
            if(M.bTitleMatch && !M.bPlayerMatch) M.DayOfWeek=7;
            M.Result=TEXT("Awaiting match"); S.CurrentCard.Add(M);
            if(M.bPlayerMatch) S.CurrentRivalId=P.Home==SeasonPlayerId ? P.Away : P.Home;
        }
        S.DayOffset=0; S.bScheduledBattleComplete=false; S.PendingContextId.Empty(); S.BattleCheckpointJson.Empty();
        S.WeekCreditsEarned=0;
    }
    bool CardIsValid(const FDigimonSeasonCareer& S)
    {
        if(S.Roster.Num()!=RosterSize || S.CurrentCard.Num()!=FixturesPerWeek) return false;
        TSet<FString> Seen; int32 PlayerMatches=0,TitleMatches=0;
        int32 Index=0;
        for(const auto& M:S.CurrentCard)
        {
            const FString ExpectedId=FString::Printf(TEXT("%s:%d:%d"),*S.CareerId,S.Week,Index++);
            if(M.MatchId!=ExpectedId || M.DayOfWeek<2 || M.DayOfWeek>7 || M.HomeTamerId==M.AwayTamerId || Seen.Contains(M.HomeTamerId) || Seen.Contains(M.AwayTamerId) ||
                !DigimonVenomNXTSeason::FindTamer(S,M.HomeTamerId) || !DigimonVenomNXTSeason::FindTamer(S,M.AwayTamerId)) return false;
            Seen.Add(M.HomeTamerId); Seen.Add(M.AwayTamerId);
            if(M.bPlayerMatch) ++PlayerMatches;
            if(M.bTitleMatch) ++TitleMatches;
            if(M.bPlayerMatch!=(M.HomeTamerId==SeasonPlayerId || M.AwayTamerId==SeasonPlayerId)) return false;
        }
        return Seen.Num()==RosterSize && PlayerMatches==1 && TitleMatches==(S.bChampionshipWeek ? 1 : 0);
    }
    void RecordMatch(FDigimonPlayerProfile& Profile,FDigimonSeasonMatch& M,const FString& WinnerId,bool bDraw)
    {
        auto& S=Profile.Season; auto* Home=MutableTamer(S,M.HomeTamerId); auto* Away=MutableTamer(S,M.AwayTamerId);
        if(!Home || !Away || M.bResolved) return;
        M.bResolved=true; M.bDraw=bDraw; M.WinnerTamerId=bDraw ? FString() : WinnerId;
        Home->LastOpponentId=Away->TamerId; Away->LastOpponentId=Home->TamerId;
        FDigimonSeasonTamer* Winner=WinnerId==Home->TamerId ? Home : Away;
        FDigimonSeasonTamer* Loser=Winner==Home ? Away : Home;
        if(bDraw)
        {
            const int32 Change=DrawRatingChange(Home->Rating,Away->Rating);
            Home->Rating=Clamp(Home->Rating+Change,600,2400); Away->Rating=Clamp(Away->Rating-Change,600,2400);
            Home->Draws=Increment(Home->Draws); Away->Draws=Increment(Away->Draws); Home->Streak=Away->Streak=0;
            M.Result=FString::Printf(TEXT("%s drew with %s"),*Home->Name,*Away->Name);
        }
        else
        {
            const int32 Change=EloGain(Winner->Rating,Loser->Rating);
            Winner->Rating=Clamp(Winner->Rating+Change,600,2400); Loser->Rating=Clamp(Loser->Rating-Change,600,2400);
            Winner->Wins=Increment(Winner->Wins); Loser->Losses=Increment(Loser->Losses);
            Winner->Streak=Increment(FMath::Max(0,Winner->Streak));
            Loser->Streak=FMath::Min(0,Loser->Streak)>-MAX_int32 ? FMath::Min(0,Loser->Streak)-1 : -MAX_int32;
            Winner->BestStreak=FMath::Max(Winner->BestStreak,Winner->Streak);
            M.Result=FString::Printf(TEXT("%s defeated %s"),*Winner->Name,*Loser->Name);
        }
        const FString A=M.HomeTamerId<M.AwayTamerId ? M.HomeTamerId : M.AwayTamerId;
        const FString B=M.HomeTamerId<M.AwayTamerId ? M.AwayTamerId : M.HomeTamerId;
        auto* Rivalry=S.Rivalries.FindByPredicate([&](const FDigimonSeasonRivalry& R){return R.TamerAId==A && R.TamerBId==B;});
        if(!Rivalry) { FDigimonSeasonRivalry R; R.TamerAId=A; R.TamerBId=B; S.Rivalries.Add(R); Rivalry=&S.Rivalries.Last(); }
        Rivalry->Heat=RivalryHeat(Rivalry->Heat,M.bTitleMatch); Rivalry->Meetings=Increment(Rivalry->Meetings); Rivalry->LastWeek=S.Week;
        if(bDraw) Rivalry->Draws=Increment(Rivalry->Draws);
        else if(WinnerId==A) Rivalry->AWins=Increment(Rivalry->AWins);
        else Rivalry->BWins=Increment(Rivalry->BWins);
        if(M.bPlayerMatch)
        {
            AddNews(S,M.Result+(M.bTitleMatch ? TEXT(" in a World Championship match!") : TEXT(".")));
            if(bDraw) { S.MonthDraws=Increment(S.MonthDraws); S.YearDraws=Increment(S.YearDraws); }
            else if(WinnerId==SeasonPlayerId) { S.MonthWins=Increment(S.MonthWins); S.YearWins=Increment(S.YearWins); }
            else { S.MonthLosses=Increment(S.MonthLosses); S.YearLosses=Increment(S.YearLosses); }
        }
        if(M.bTitleMatch && !bDraw)
        {
            if(WinnerId==S.ChampionId)
            {
                S.ChampionDefenses=Increment(S.ChampionDefenses); Winner->Defenses=Increment(Winner->Defenses);
                if(!S.Reigns.IsEmpty()) S.Reigns.Last().Defenses=S.ChampionDefenses;
                AddNews(S,FString::Printf(TEXT("%s retained the World Championship. Defense %d."),*Winner->Name,S.ChampionDefenses));
                if(WinnerId==SeasonPlayerId && IsDefenseMilestone(S.ChampionDefenses,GetDefault<UDigimonVenomNXTSettings>()->SeasonDefenseRewardInterval))
                {
                    const int64 Paid=Award(Profile,FString::Printf(TEXT("defense:%d:%d"),S.ChampionReign,S.ChampionDefenses),
                        FString::Printf(TEXT("Champion retained: %d defenses"),S.ChampionDefenses),Clamp(GetDefault<UDigimonVenomNXTSettings>()->SeasonDefenseRewardCredits,0,1000000));
                    AddNews(S,FString::Printf(TEXT("Championship defense milestone: +%lld credits."),static_cast<long long>(Paid)));
                }
            }
            else
            {
                if(!S.Reigns.IsEmpty()) S.Reigns.Last().EndWeek=S.Week;
                S.ChampionId=WinnerId; S.ChampionSinceWeek=S.Week; S.ChampionReign=Increment(S.ChampionReign); S.ChampionDefenses=0;
                Winner->Titles=Increment(Winner->Titles);
                FDigimonSeasonReign R; R.HolderId=WinnerId; R.HolderName=Winner->Name; R.ReignNumber=S.ChampionReign; R.StartWeek=S.Week;
                S.Reigns.Add(R); if(S.Reigns.Num()>12) S.Reigns.RemoveAt(0,S.Reigns.Num()-12);
                AddNews(S,FString::Printf(TEXT("NEW WORLD CHAMPION: %s. Reign %d begins."),*Winner->Name,S.ChampionReign));
                if(WinnerId==SeasonPlayerId) Award(Profile,FString::Printf(TEXT("title:%d"),S.ChampionReign),TEXT("World Championship victory"),Clamp(GetDefault<UDigimonVenomNXTSettings>()->SeasonTitleWinCredits,0,1000000));
            }
        }
        else if(M.bTitleMatch && bDraw) AddNews(S,TEXT("Championship draw: the reigning champion retains the title; no defense milestone is awarded."));
        UpdateRankings(S);
    }
}

const FDigimonSeasonTamer* DigimonVenomNXTSeason::FindTamer(const FDigimonSeasonCareer& S,const FString& Id)
{ return S.Roster.FindByPredicate([&](const FDigimonSeasonTamer& T){return T.TamerId==Id;}); }
const FDigimonSeasonMatch* DigimonVenomNXTSeason::GetPlayerMatch(const FDigimonSeasonCareer& S)
{ return S.CurrentCard.FindByPredicate([](const FDigimonSeasonMatch& M){return M.bPlayerMatch;}); }
int32 DigimonVenomNXTSeason::GetRank(const FDigimonSeasonCareer& S)
{ const auto* T=FindTamer(S,SeasonPlayerId); return T ? T->Rank : 16; }
int32 DigimonVenomNXTSeason::NextOpponentLevel(const FDigimonSeasonCareer& S)
{
    const auto* Match=GetPlayerMatch(S);
    const auto* T=Match ? FindTamer(S,Match->HomeTamerId==SeasonPlayerId ? Match->AwayTamerId : Match->HomeTamerId) : nullptr;
    if(T && !T->Team.IsEmpty()) return T->Team[0].Level;
    return FMath::Max(1,S.OpponentLevel);
}
int64 DigimonVenomNXTSeason::MonthRewardPreview(const FDigimonSeasonCareer& S)
{ return PeriodCredits(S.MonthWins,GetRank(S),S.ChampionId==SeasonPlayerId,false,Rewards()); }
int64 DigimonVenomNXTSeason::YearRewardPreview(const FDigimonSeasonCareer& S)
{ return PeriodCredits(S.YearWins,GetRank(S),S.ChampionId==SeasonPlayerId,true,Rewards()); }
FString DigimonVenomNXTSeason::CalendarLabel(const FDigimonSeasonCareer& S,int32 DayOffset)
{
    const auto D=CalendarFromDays(WeekStartDays(S.Week)+Clamp(DayOffset==INDEX_NONE ? S.DayOffset : DayOffset,0,6));
    return FString::Printf(TEXT("%s, %d %s | Year %lld"),SeasonWeekdayNames[D.Weekday-1],D.Day,SeasonMonthNames[D.Month-1],static_cast<long long>(D.Year));
}
FString DigimonVenomNXTSeason::GetScheduledOpponentName(const FDigimonPlayerProfile& Profile)
{
    const auto* M=GetPlayerMatch(Profile.Season);
    const auto* T=M ? FindTamer(Profile.Season,M->HomeTamerId==SeasonPlayerId ? M->AwayTamerId : M->HomeTamerId) : nullptr;
    return T ? T->Name : TEXT("Unscheduled");
}

bool DigimonVenomNXTSeason::ReconcileTamerStyles(FDigimonPlayerProfile& Profile)
{
    bool bChanged = false;
    if (!DigimonVenomNXTTamers::IsValidStyle(Profile.TamerStyleId))
    {
        Profile.TamerStyleId = DigimonVenomNXTTamers::StyleForIndex(0);
        bChanged = true;
    }
    for (FDigimonSeasonTamer& Tamer : Profile.Season.Roster)
    {
        const FName DesiredStyle = Tamer.bPlayer || Tamer.TamerId == SeasonPlayerId
            ? Profile.TamerStyleId : DigimonVenomNXTTamers::StyleForStableId(Tamer.TamerId);
        if (Tamer.TamerStyleId != DesiredStyle)
        {
            Tamer.TamerStyleId = DesiredStyle;
            bChanged = true;
        }
    }
    return bChanged;
}

bool DigimonVenomNXTSeason::EnsureCareer(FDigimonPlayerProfile& Profile,const UDigimonVenomNXTDataSubsystem* Data)
{
    auto& S=Profile.Season;
    if(S.Version>0)
    {
        // A read/refresh must never rebook a match, reseed parties, advance time or touch a saved battle.
        const bool bStylesMigrated = ReconcileTamerStyles(Profile);
        UpdateViews(Profile);
        return bStylesMigrated;
    }
    if(!Data || Profile.AccountId.IsEmpty()) return false;
    TArray<FDigimonSpeciesDefinition> Starters;
    for(const auto& Def:Data->GetAllSpecies())
        if(!Def.bPlaceholder && Def.bHasNormalArtwork && Def.Stage==EDigimonStage::Rookie) Starters.Add(Def);
    if(Starters.IsEmpty()) return false;
    Starters.Sort([](const auto& A,const auto& B){return A.SpeciesId.LexicalLess(B.SpeciesId);});
    const int32 OldWeek=Clamp(S.Week,1,MaximumWeek),OldWins=FMath::Max(0,S.Wins),OldLosses=FMath::Max(0,S.Losses),OldTitles=FMath::Max(0,S.Championships);
    const bool OldComplete=S.bScheduledBattleComplete;
    S=FDigimonSeasonCareer(); S.Version=1; S.Week=OldWeek; S.FirstArchiveWeek=OldWeek;
    S.CareerId=FGuid::NewGuid().ToString(EGuidFormats::Digits); S.Seed=static_cast<int32>(FCrc::StrCrc32(*S.CareerId));
    int32 InitialLevelSum=0,InitialPartyCount=0;
    for(const FGuid& Id:Profile.Party)
    {
        if(const auto* P=Profile.Collection.FindByPredicate([&](const FDigimonOwnedPartner& N){return N.InstanceId==Id;}))
        { InitialLevelSum+=P->Level; if(++InitialPartyCount>=3) break; }
    }
    const auto* Settings=GetDefault<UDigimonVenomNXTSettings>();
    const int32 InitialLevel=Settings->SeasonStartingLevel>0 ? Settings->SeasonStartingLevel :
        InitialLevelSum/FMath::Max(1,InitialPartyCount);
    S.OpponentLevel=Clamp(InitialLevel,1,99);
    FRandomStream Random(StreamSeed(S,TEXT("roster")));
    for(int32 I=0;I<RosterSize;++I)
    {
        FDigimonSeasonTamer T; T.bPlayer=I==0;
        T.TamerId=I==0 ? FString(SeasonPlayerId) : FString::Printf(TEXT("season_tamer_%02d"),I);
        T.Name=I==0 ? Profile.Username : FString(SeasonTamerNames[I-1]);
        T.TamerStyleId=I==0 ? Profile.TamerStyleId : DigimonVenomNXTTamers::StyleForStableId(T.TamerId);
        T.Rating=I==0 ? 1200 : 1110+I*15;
        if(I==0) { T.Wins=OldWins; T.Losses=OldLosses; T.Titles=OldTitles; }
        else
        {
            const int32 TamerLevel=Clamp(S.OpponentLevel+(I%5)-2,1,99);
            for(int32 J=0;J<3;++J)
            {
                auto Partner=MakePartner(Starters[Random.RandRange(0,Starters.Num()-1)],TamerLevel,Random,Data);
                Partner.CAM=10; T.Team.Add(Partner);
            }
        }
        S.Roster.Add(T);
    }
    S.ChampionId=S.Roster.Last().TamerId; S.Roster.Last().Titles=1;
    FDigimonSeasonReign FirstReign; FirstReign.HolderId=S.ChampionId; FirstReign.HolderName=S.Roster.Last().Name; FirstReign.StartWeek=S.Week;
    S.Reigns.Add(FirstReign); S.ChampionSinceWeek=S.Week;
    const auto CurrentDate=CalendarFromDays(WeekStartDays(S.Week));
    S.LastPaidMonth=MonthKey(CurrentDate)-1; S.LastPaidYear=CurrentDate.Year-1;
    AddNews(S,TEXT("Your private World Circuit begins. Sixteen tamers. One World Champion. Every match matters."));
    BookWeek(Profile);
    if(OldComplete)
    {
        // Old builds only retained a complete flag, not fixture results. Preserve the right to continue
        // without replaying the paid match or inventing historical opponents, wins or rewards.
        for(auto& M:S.CurrentCard) { M.bResolved=true; M.Result=TEXT("Completed in the previous version; detailed result unavailable."); }
        S.bScheduledBattleComplete=true; S.DayOffset=6;
        AddNews(S,TEXT("Previous season totals preserved. Continue to the next week for the new full match card."));
    }
    UpdateViews(Profile);
    return true;
}

TArray<FDigimonOwnedPartner> DigimonVenomNXTSeason::BuildScheduledOpponent(const FDigimonPlayerProfile& Profile,const UDigimonVenomNXTDataSubsystem* Data)
{
    TArray<FDigimonOwnedPartner> Result;
    const auto& S=Profile.Season; const auto* Match=GetPlayerMatch(S);
    if(!Data || !Match || !CardIsValid(S) || Match->bResolved) return Result;
    const auto* T=FindTamer(S,Match->HomeTamerId==SeasonPlayerId ? Match->AwayTamerId : Match->HomeTamerId);
    if(!T || T->bPlayer) return Result;
    TSet<FGuid> ValidParty;
    for(const FGuid& Id:Profile.Party)
        if(Profile.Collection.ContainsByPredicate([&](const FDigimonOwnedPartner& P){return P.InstanceId==Id && P.IsValid();})) ValidParty.Add(Id);
    const int32 Count=FMath::Min3(T->Team.Num(),ValidParty.Num(),Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize,1,3));
    for(int32 Index=0;Index<Count;++Index)
    {
        const auto& P=T->Team[Index];
        FDigimonSpeciesDefinition Def;
        if(!P.IsValid() || !Data->GetSpecies(P.SpeciesId,Def) || Def.bPlaceholder) { Result.Reset(); return Result; }
        auto Copy=P;
        DigimonVenomNXTAutoBattle::MigratePartner(Copy,Data);
        const auto U=DigimonVenomNXTAutoBattle::BuildUnit(Copy,Data);
        Copy.CurrentHP=U.Stats.MaxHP; Copy.CurrentSP=U.Stats.MaxSP; Result.Add(Copy);
    }
    return Result;
}

bool DigimonVenomNXTSeason::BeginMatch(FDigimonPlayerProfile& Profile,FString& OutContextId,FString& OutError)
{
    auto& S=Profile.Season; OutContextId.Empty(); OutError.Empty();
    const auto* Match=GetPlayerMatch(S);
    if(S.Version<=0 || !CardIsValid(S) || !Match) { OutError=TEXT("The private season card is unavailable. Reopen Season Mode."); return false; }
    if(S.bScheduledBattleComplete || Match->bResolved) { OutError=TEXT("This week's match is complete. Review the results and continue to next week."); return false; }
    if(!S.PendingContextId.IsEmpty())
    {
        if(S.PendingContextId!=Match->MatchId) { OutError=TEXT("A different saved season match requires recovery."); return false; }
        OutContextId=S.PendingContextId; return true;
    }
    if(!S.BattleCheckpointJson.IsEmpty()) { OutError=TEXT("The saved battle checkpoint requires recovery before a new match."); return false; }
    S.PendingContextId=Match->MatchId; OutContextId=S.PendingContextId;
    MoveCalendar(Profile,WeekStartDays(S.Week)+Match->DayOfWeek-1);
    S.LastMatchCredits=0; S.LastMatchXP=0; UpdateViews(Profile);
    return true;
}

bool DigimonVenomNXTSeason::SettleMatch(FDigimonPlayerProfile& Profile,const FString& ContextId,bool bWon,bool bDraw,
    const UDigimonVenomNXTDataSubsystem* Data,FString& OutMessage)
{
    auto& S=Profile.Season; auto* Match=S.CurrentCard.FindByPredicate([](const auto& M){return M.bPlayerMatch;});
    if(!Data || !CardIsValid(S) || !Match || !CanSettle(TCHAR_TO_UTF8(*Match->MatchId),TCHAR_TO_UTF8(*S.PendingContextId),
        TCHAR_TO_UTF8(*ContextId),TCHAR_TO_UTF8(*S.LastSettledContextId),Match->bResolved) || S.bScheduledBattleComplete)
    { OutMessage=TEXT("This season result is stale or already settled. No rewards were granted."); return false; }
    // Validate every AI team before changing any state on the candidate transaction.
    for(const auto& T:S.Roster) if(!T.bPlayer)
    {
        if(T.Team.Num()!=3) { OutMessage=TEXT("The private roster has an invalid team; no result was committed."); return false; }
        for(const auto& P:T.Team) { FDigimonSpeciesDefinition Def; if(!P.IsValid() || !Data->GetSpecies(P.SpeciesId,Def) || Def.bPlaceholder)
            { OutMessage=TEXT("A season partner is unavailable; no result was committed."); return false; } }
    }
    const FString Opponent=Match->HomeTamerId==SeasonPlayerId ? Match->AwayTamerId : Match->HomeTamerId;
    const auto OpponentTeam=BuildScheduledOpponent(Profile,Data);
    RecordMatch(Profile,*Match,bWon && !bDraw ? FString(SeasonPlayerId) : Opponent,bDraw);
    S.LastMatchCredits=0;
    if(bWon && !bDraw)
    {
        int64 Credits=0;
        for(const auto& P:OpponentTeam) Credits+=MatchCredits(P.Level,Rewards());
        const double Rate=FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MoneyRewardRate,0.0f,100.0f);
        S.LastMatchCredits=Award(Profile,TEXT("match:")+ContextId,TEXT("Season match victory"),DigimonVenomNXTRewardCore::Scale(Credits,Rate));
    }
    FRandomStream Random(StreamSeed(S,TEXT("results")));
    for(auto& Other:S.CurrentCard)
    {
        if(Other.bPlayerMatch || Other.bResolved) continue;
        MoveCalendar(Profile,WeekStartDays(S.Week)+Other.DayOfWeek-1);
        const auto* A=FindTamer(S,Other.HomeTamerId); const auto* B=FindTamer(S,Other.AwayTamerId);
        const int32 ALevel=A->Team.IsEmpty()?1:A->Team[0].Level, BLevel=B->Team.IsEmpty()?1:B->Team[0].Level;
        const double Gap=FMath::Clamp(A->Rating-B->Rating+(ALevel-BLevel)*4,-1200,1200);
        const double Chance=1.0/(1.0+FMath::Pow(10.0,-Gap/400.0));
        const FString Winner=Random.FRand()<Chance?A->TamerId:B->TamerId;
        RecordMatch(Profile,Other,Winner,false);
    }
    DevelopTeams(S,Data);
    MoveCalendar(Profile,WeekStartDays(S.Week)+6);
    S.bScheduledBattleComplete=true; S.LastSettledContextId=ContextId; S.PendingContextId.Empty(); S.BattleCheckpointJson.Empty();
    if(S.bAnnualEvent) AddNews(S,TEXT("The Grand Championship card is complete. All records, rivalries and the World Champion continue into the new year."));
    UpdateViews(Profile);
    OutMessage=FString::Printf(TEXT("%s Season week %d complete. +%lld match credits. Review the full card before advancing."),
        bDraw ? TEXT("Draw.") : bWon ? TEXT("Victory!") : TEXT("Defeat."),S.Week,static_cast<long long>(S.LastMatchCredits));
    return true;
}

bool DigimonVenomNXTSeason::AdvanceWeek(FDigimonPlayerProfile& Profile,const UDigimonVenomNXTDataSubsystem* Data,FString& OutMessage)
{
    auto& S=Profile.Season;
    if(!Data || !CardIsValid(S) || !S.bScheduledBattleComplete || !S.PendingContextId.IsEmpty() || !S.BattleCheckpointJson.IsEmpty() ||
        S.CurrentCard.ContainsByPredicate([](const auto& M){return !M.bResolved;}))
    { OutMessage=TEXT("Finish your scheduled season battle before advancing to next week."); return false; }
    if(S.Week>=MaximumWeek) { OutMessage=TEXT("This career has reached the supported booking-week limit."); return false; }
    MoveCalendar(Profile,WeekStartDays(S.Week+1));
    UpdateViews(Profile);
    FDigimonSeasonArchive Record; Record.CareerId=S.CareerId; Record.Week=S.Week; Record.EventName=S.EventName; Record.Matches=S.CurrentCard;
    Record.ChampionId=S.ChampionId; Record.PlayerRank=GetRank(S); Record.CreditsEarned=S.WeekCreditsEarned;
    Record.ChampionReign=S.ChampionReign; Record.ChampionDefenses=S.ChampionDefenses; Record.ChampionSinceWeek=S.ChampionSinceWeek;
    for(const auto& Payout:S.Payouts) if(Payout.Week==S.Week) Record.Payouts.Add(Payout);
    if(const auto* P=FindTamer(S,SeasonPlayerId)) Record.PlayerRating=P->Rating;
    Record.Standings=S.Roster; for(auto& T:Record.Standings) T.Team.Reset();
    Record.Standings.Sort([](const auto& A,const auto& B){return A.Rank<B.Rank;});
    S.Archive.Insert(Record,0);
    const int32 Limit=Clamp(GetDefault<UDigimonVenomNXTSettings>()->SeasonArchiveWeeks,4,16);
    if(S.Archive.Num()>Limit) S.Archive.SetNum(Limit);
    ++S.Week;
    for(auto& Rivalry:S.Rivalries) Rivalry.Heat=DecayRivalry(Rivalry.Heat);
    BookWeek(Profile); S.OpponentLevel=NextOpponentLevel(S); UpdateViews(Profile);
    OutMessage=FString::Printf(TEXT("Week %d booked. Opponent parties are level %d. Your private career is saved."),S.Week,S.OpponentLevel);
    return true;
}
