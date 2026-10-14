#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTGhostLineCore.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
using namespace DigimonVenomNXTGhostLineCore;
static int Checks=0;
static void Check(bool Condition,const char* Why) { ++Checks; if(!Condition){std::cerr<<"FAIL: "<<Why<<"\n";std::exit(1);} }
// Exercise save/reload of every independent durable fact between transitions.
static Progress RoundTrip(const Progress& S)
{
    std::ostringstream Out;
    Out<<S.Complete<<' '<<S.Mastery<<' ';
    for(int I=0;I<CaseCount;++I) Out<<S.Accepted[I]<<' '<<S.Reported[I]<<' '<<S.Won[I]<<' '<<S.Proof[I]<<' '<<S.Hacked[I]<<' ';
    Progress R;std::istringstream In(Out.str()); In>>R.Complete>>R.Mastery;
    for(int I=0;I<CaseCount;++I) In>>R.Accepted[I]>>R.Reported[I]>>R.Won[I]>>R.Proof[I]>>R.Hacked[I];
    Reconcile(R);return R;
}
int main()
{
    Progress P;
    Check(CanEnter(P,1)&&CanEnter(P,2),"hub and first field open");
    for(int M=-3;M<=36;++M) Check(CanEnter(P,M)==(M==1||M==2),"initial exact route gating");
    Check(!IsRevealed(P)&&!P.Mastery&&!P.Complete,"new account has no story inference");
    Progress BadgeOnly;BadgeOnly.Proof.fill(true);Reconcile(BadgeOnly);
    Check(!CanEnter(BadgeOnly,3)&&!CanChallenge(BadgeOnly,30)&&!BadgeOnly.Mastery,"proof count is not case evidence");
    Progress Future;Future.Accepted[25]=Future.Reported[25]=Future.Proof[25]=Future.Won[25]=true;Reconcile(Future);
    Check(!IsRevealed(Future)&&!Future.Reported[25],"unearned out-of-order reveal rejected");
    int Battles=0,Reports=0,Hacked=0;
    for(int F=1;F<=30;++F)
    {
        Check(CanEnter(P,F+1),"case field reachable through exact prior proofs");
        Check(!CanChallenge(P,F),"no battle before acceptance/final sealed archive");
        Check(AdvanceQuest(P,F)==QuestResult::Accepted,"case accepted once");
        P=RoundTrip(P);
        int ObjectiveField=0;
        Check(Stage(P,ObjectiveField)==(F==30?ObjectiveStage::ConfirmReport:ObjectiveStage::WitnessTrial),"accepted case objective distinguishes final audit");
        Check(ObjectiveField==F,"objective points to actual first incomplete case");
        if(F<30)
        {
            Check(AdvanceQuest(P,F)==QuestResult::Rejected,"cannot report before witness victory");
            for(int Attempt=0;Attempt<3;++Attempt)
            {
                bool First=true;Check(Settle(P,F,false,First)&&!First,"loss permits retry without reward");
                Check(!P.Hacked[F-1]&&!P.Proof[F-1]&&!P.Reported[F-1],"loss creates no hacked witness/proof/report");
                P=RoundTrip(P);Check(CanChallenge(P,F),"saved loss keeps authorized retry");
            }
            bool First=false;Check(Settle(P,F,true,First)&&First,"first authorized victory settled");++Battles;
            Check(P.Hacked[F-1]==(F<=23),"only first23 trials have hacked history");
            Check(!CanChallenge(P,F),"ordinary trial nonrepeatable after victory");
            Check(!Settle(P,F,true,First)&&!First,"duplicate victory cannot settle or reward");
            Check(!CanEnter(P,F+2),"victory alone does not open forward route");
            if(F==26) Check(!IsRevealed(P),"signature trial alone must not reveal culprit");
        }
        Check(CanReport(P,F),"report readiness requires exact case evidence");
        Check(AdvanceQuest(P,F)==QuestResult::Reported,"confirm report grants proof once");++Reports;
        Check(HasReport(P,F)&&P.Proof[F-1],"durable report and proof agree");
        Check(AdvanceQuest(P,F)==QuestResult::Rejected,"repeated report gives no new reward");
        P=RoundTrip(P);
        Check(IsRevealed(P)==(F>=26),"reveal earned exactly at field26 report");
        Check(CompanionVisible(P,true,false)==(F<26),"early friend actors retire on revelation");
        Check(CompanionVisible(P,false,true)==(F>=26),"confession/final actors gated by revelation");
        for(int Old=1;Old<=F;++Old) Check(CanEnter(P,Old+1),"all earlier fields remain available");
    }
    Check(Reports==30&&Battles==29,"thirty reports have exactly29 preceding trials");
    Check(CanChallenge(P,30)&&!P.Complete&&!P.Mastery,"final report unlocks battle, not mastery");
    for(bool Value:P.Hacked) if(Value)++Hacked;
    Check(Hacked==23,"clean recorder and subsequent trials create no hacked witnesses");
    bool First=true;Check(Settle(P,30,false,First)&&!First,"final loss preserves retry");
    P=RoundTrip(P);Check(Prefix(P,30)&&CanChallenge(P,30)&&!P.Mastery,"final loss preserves all evidence without mastery");
    Check(Settle(P,30,true,First)&&First,"final victory completes campaign");++Battles;
    P=RoundTrip(P);
    Check(P.Complete&&P.Mastery&&Battles==30,"exact30 authored battles and permanent mastery");
    Check(!CanChallenge(P,30)&&!Settle(P,30,true,First),"final confrontation cannot be replayed");
    Check(!CompanionVisible(P,true,false)&&!CompanionVisible(P,false,true),"every Marek actor absent after ending");
    for(int F=1;F<=30;++F) Check(P.Hacked[F-1]==(F<=23)&&HasReport(P,F),"ending preserves historical incidents and all proofs");
    Progress Durable;Durable.Complete=true;Reconcile(Durable);
    Check(Durable.Complete&&Durable.Mastery&&Prefix(Durable,30),"persisted completion reconstructs redundant proof/mastery facts");
    Progress Mastery;Mastery.Mastery=true;Reconcile(Mastery);
    Check(Mastery.Mastery&&!Mastery.Complete&&!CanEnter(Mastery,3),"permanent mastery cannot unlock or invent investigation");
    for(int Bits=0;Bits<16;++Bits)
    {
        bool V=(Bits&1)!=0,Pend=(Bits&2)!=0,NPC=(Bits&4)!=0,Settled=(Bits&8)!=0;
        Check(ReceiptMatches(V,Pend,NPC,Settled)==(Bits==7),"receipt fence rejects forged/stale/wrong NPC settlements");
    }
    std::cout<<"PASS GhostLine core: "<<Checks<<" checks; 31 maps, 30 reports/battles, earned reveal, clean recorder, save recovery, one-time mastery\n";
}
