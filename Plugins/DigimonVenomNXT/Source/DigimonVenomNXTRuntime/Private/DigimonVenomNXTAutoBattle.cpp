#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTCombatCore.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTBattlePolicyCore.h"

namespace
{
FDigimonStats DigimonBalancedStats(const FDigimonSpeciesDefinition& Def, const FDigimonOwnedPartner& Partner)
{
    using namespace DigimonVenomNXTCombatCore;
    const int32 Rank = StageRank(static_cast<int32>(Def.Stage));
    FDigimonStats Out;
    Out.MaxHP = Stat(Def.BaseStats.MaxHP, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.MaxHP, 0);
    Out.MaxSP = Stat(Def.BaseStats.MaxSP, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.MaxSP, 1);
    Out.Attack = Stat(Def.BaseStats.Attack, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.Attack, 2);
    Out.Defense = Stat(Def.BaseStats.Defense, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.Defense, 3);
    Out.Spirit = Stat(Def.BaseStats.Spirit, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.Spirit, 4);
    Out.Speed = Stat(Def.BaseStats.Speed, Partner.Level, Rank, Partner.ABI, Partner.PermanentTraining.Speed, 5);
    return Out;
}
int32 DigimonLegacyMaximum(EDigimonStage Stage, int32 Level, int32 Training, int32 StatIndex)
{
    // Old builds scaled base + training together and did not apply ABI. Match that
    // exact denominator once, then use the new base/growth/ABI + raw-training model.
    const int64 Sum = static_cast<int64>(DigimonVenomNXTCombatCore::LegacyBase(static_cast<int32>(Stage), StatIndex)) + FMath::Max(0, Training);
    return DigimonVenomNXTCombatCore::ScaledStat(static_cast<int32>(FMath::Min<int64>(100000000, Sum)), Level);
}
bool DigimonSameMoves(const TArray<FDigimonMoveSlot>& A, const TArray<FDigimonMoveSlot>& B)
{
    if (A.Num() != B.Num()) return false;
    for (int32 I = 0; I < A.Num(); ++I)
        if (A[I].MoveId != B[I].MoveId || A[I].Power != B[I].Power || A[I].SPCost != B[I].SPCost ||
            A[I].DamageClass != B[I].DamageClass || A[I].Element != B[I].Element ||
            A[I].DisplayName.ToString() != B[I].DisplayName.ToString() || A[I].Description != B[I].Description ||
            A[I].SPCostPerRank != B[I].SPCostPerRank || A[I].bUsesSpeciesElement != B[I].bUsesSpeciesElement) return false;
    return true;
}
}

FDigimonMoveSlot DigimonVenomNXTAutoBattle::ResolveMove(FName MoveId, const FDigimonSpeciesDefinition& Species, const UDigimonVenomNXTDataSubsystem* Data)
{
    FDigimonMoveSlot Out;
    if (!Data || !Data->GetMove(MoveId, Out))
    {
        // Unknown legacy/custom IDs remain equipped, but never trust saved damage,
        // SP costs or elemental metadata. Their safe neutral action costs no SP.
        Out.MoveId = MoveId;
        Out.DisplayName = FText::FromString(TEXT("Basic Technique"));
        Out.Description = TEXT("An unregistered legacy technique. Uses regular neutral physical Attack strength at no SP cost.");
        return Out;
    }
    Out.SPCost += Out.SPCostPerRank * DigimonVenomNXTCombatCore::StageRank(static_cast<int32>(Species.Stage));
    if (Out.bUsesSpeciesElement) Out.Element = Species.Element;
    if (MoveId == TEXT("burst"))
    {
        static const TCHAR* Names[] = {TEXT("Data Burst"), TEXT("Flare Burst"), TEXT("Aqua Pulse"),
            TEXT("Thorn Surge"), TEXT("Volt Arc"), TEXT("Gale Cutter"), TEXT("Terra Impact"),
            TEXT("Radiant Lance"), TEXT("Void Pulse")};
        Out.DisplayName = FText::FromString(Names[FMath::Clamp(static_cast<int32>(Species.Element), 0, 8)]);
    }
    // A combat slot stores the already-resolved values. BuildUnit always re-reads
    // the immutable catalog so evolving or loading never compounds stage costs.
    return Out;
}

FDigimonBattleUnit DigimonVenomNXTAutoBattle::BuildUnit(const FDigimonOwnedPartner& P, const UDigimonVenomNXTDataSubsystem* Data)
{
    FDigimonBattleUnit U;
    U.InstanceId=P.InstanceId; U.SpeciesId=P.SpeciesId; U.Variant=P.Variant;
    U.Level=FMath::Clamp(P.Level,1,200); U.CAM=FMath::Clamp(P.CAM,0,100); U.ABI=FMath::Clamp(P.ABI,0,200);
    U.DisplayName=P.Nickname.IsEmpty()?P.SpeciesId.ToString():P.Nickname;
    FDigimonSpeciesDefinition Def;
    if (Data && Data->GetSpecies(P.SpeciesId,Def))
        U.DisplayName=P.Nickname.IsEmpty()?Def.DisplayName.ToString():P.Nickname;
    U.Stats=DigimonBalancedStats(Def,P);
    U.Affinity=Def.Affinity; U.Element=Def.Element;
    if (P.Moves.IsEmpty())
    {
        for (int32 I=0; I<FMath::Min(4,Def.LearnableMoves.Num()); ++I)
            U.Moves.Add(ResolveMove(Def.LearnableMoves[I],Def,Data));
    }
    else
    {
        // Preserve slot order, equipped IDs and inherited techniques; replace only
        // their authored metadata so an old serialized Power cannot bypass balance.
        for (int32 I=0; I<FMath::Min(4,P.Moves.Num()); ++I)
            U.Moves.Add(ResolveMove(P.Moves[I].MoveId,Def,Data));
    }
    if (P.CombatBalanceVersion < CurrentBalanceVersion)
    {
        U.HP=DigimonVenomNXTCombatCore::MigrateVital(P.CurrentHP,DigimonLegacyMaximum(Def.Stage,U.Level,P.PermanentTraining.MaxHP,0),U.Stats.MaxHP,true);
        U.SP=DigimonVenomNXTCombatCore::MigrateVital(P.CurrentSP,DigimonLegacyMaximum(Def.Stage,U.Level,P.PermanentTraining.MaxSP,1),U.Stats.MaxSP,false);
    }
    else
    {
        U.HP=FMath::Clamp(P.CurrentHP,0,U.Stats.MaxHP); U.SP=FMath::Clamp(P.CurrentSP,0,U.Stats.MaxSP);
    }
    U.CombatBalanceVersion=CurrentBalanceVersion;
    U.bDefeated=U.HP<=0;
    return U;
}

bool DigimonVenomNXTAutoBattle::MigratePartner(FDigimonOwnedPartner& P, const UDigimonVenomNXTDataSubsystem* Data)
{
    FDigimonSpeciesDefinition Def;
    if (!Data || !Data->GetSpecies(P.SpeciesId,Def)) return false;
    const FDigimonBattleUnit U=BuildUnit(P,Data);
    const bool Changed=P.CombatBalanceVersion<CurrentBalanceVersion || P.CurrentHP!=U.HP || P.CurrentSP!=U.SP || !DigimonSameMoves(P.Moves,U.Moves);
    if (Changed)
    {
        P.CurrentHP=U.HP; P.CurrentSP=U.SP; P.Moves=U.Moves;
        P.CombatBalanceVersion=CurrentBalanceVersion;
    }
    return Changed;
}

bool DigimonVenomNXTAutoBattle::RebuildSavedUnit(FDigimonBattleUnit& U, const UDigimonVenomNXTDataSubsystem* Data, const FDigimonOwnedPartner* OwnedPartner, bool bWildEnemy, bool bPrivateTraining)
{
    FDigimonSpeciesDefinition Def;
    if (!Data || !Data->GetSpecies(U.SpeciesId,Def)) return false;
    FDigimonOwnedPartner P;
    if (OwnedPartner) P=*OwnedPartner;
    P.InstanceId=U.InstanceId; P.SpeciesId=U.SpeciesId; P.Variant=U.Variant; P.Level=U.Level;
    P.Nickname=U.DisplayName; P.Moves=U.Moves; P.CombatBalanceVersion=CurrentBalanceVersion;
    if (!OwnedPartner) { P.CAM=U.CAM; P.ABI=U.ABI; }
    FDigimonBattleUnit Fresh=BuildUnit(P,Data);
    if (bWildEnemy) Fresh.Stats.MaxHP=DigimonVenomNXTBattlePolicyCore::WildMaxHP(Fresh.Stats.MaxHP, bPrivateTraining);
    if (U.CombatBalanceVersion<CurrentBalanceVersion)
    {
        Fresh.HP=DigimonVenomNXTCombatCore::MigrateVital(U.HP,U.Stats.MaxHP,Fresh.Stats.MaxHP,true);
        Fresh.SP=DigimonVenomNXTCombatCore::MigrateVital(U.SP,U.Stats.MaxSP,Fresh.Stats.MaxSP,false);
    }
    else
    {
        Fresh.HP=FMath::Clamp(U.HP,0,Fresh.Stats.MaxHP); Fresh.SP=FMath::Clamp(U.SP,0,Fresh.Stats.MaxSP);
    }
    Fresh.bDefeated=Fresh.HP<=0;
    Fresh.NextActionTime=U.NextActionTime; Fresh.TimelineOrder=U.TimelineOrder; Fresh.bGuarding=U.bGuarding;
    U=MoveTemp(Fresh);
    return true;
}

DigimonVenomNXTCombatCore::Move DigimonVenomNXTAutoBattle::ToCoreMove(const FDigimonMoveSlot& M)
{
    return {M.Power,M.SPCost,static_cast<int32>(M.DamageClass),static_cast<int32>(M.Element)};
}
DigimonVenomNXTCombatCore::Unit DigimonVenomNXTAutoBattle::ToCoreUnit(const FDigimonBattleUnit& U)
{
    DigimonVenomNXTCombatCore::Unit C;
    C.HP=U.HP; C.SP=U.SP; C.MaxHP=U.Stats.MaxHP; C.MaxSP=U.Stats.MaxSP;
    C.Attack=U.Stats.Attack; C.Defense=U.Stats.Defense; C.Speed=U.Stats.Speed; C.Level=U.Level;
    C.Spirit=U.Stats.Spirit; C.Affinity=static_cast<int32>(U.Affinity); C.Element=static_cast<int32>(U.Element);
    C.CAM=U.CAM; C.Guarding=U.bGuarding;
    for (const FDigimonMoveSlot& M:U.Moves) C.Moves.push_back(ToCoreMove(M));
    return C;
}

FDigimonAutoBattleResult DigimonVenomNXTAutoBattle::Resolve(const TArray<FDigimonOwnedPartner>& A, const TArray<FDigimonOwnedPartner>& B,
    const UDigimonVenomNXTDataSubsystem* Data, int32 ActiveSize, int32 Seed, bool bCapturePresentation, bool bWildEncounter)
{
    FDigimonAutoBattleResult Out;
    std::vector<DigimonVenomNXTCombatCore::Unit> CoreA, CoreB;
    auto Build=[Data](const TArray<FDigimonOwnedPartner>& Input,TArray<FDigimonBattleUnit>& Units,std::vector<DigimonVenomNXTCombatCore::Unit>& Core)
    {
        // No actors, timers, global random state or profile mutation in the combat resolver.
        for (int32 I=0; I<FMath::Min(12,Input.Num()); ++I)
        {
            const FDigimonBattleUnit U=BuildUnit(Input[I],Data); Units.Add(U);
            DigimonVenomNXTCombatCore::Unit C=ToCoreUnit(U);
            Core.push_back(C);
        }
    };
    Build(A,Out.TeamA,CoreA); Build(B,Out.TeamB,CoreB);
    if (bWildEncounter)
    {
        for (int32 I=0; I<Out.TeamB.Num(); ++I)
        {
            FDigimonBattleUnit& U=Out.TeamB[I];
            const int32 PreviousMax=U.Stats.MaxHP;
            U.Stats.MaxHP=DigimonVenomNXTBattlePolicyCore::WildMaxHP(PreviousMax);
            U.HP=DigimonVenomNXTCombatCore::MigrateVital(U.HP,PreviousMax,U.Stats.MaxHP,true);
            CoreB[I]=ToCoreUnit(U); CoreB[I].DamageMultiplier=DigimonVenomNXTBattlePolicyCore::EnemyDamageMultiplier(0,1,false);
        }
    }
    if (bCapturePresentation) { Out.InitialTeamA=Out.TeamA; Out.InitialTeamB=Out.TeamB; }
    auto R=DigimonVenomNXTCombatCore::Resolve(MoveTemp(CoreA),MoveTemp(CoreB),ActiveSize,static_cast<uint32>(Seed),200,bCapturePresentation);
    Out.bTeamAWon=R.TeamAWon; Out.bDraw=R.Draw; Out.Turns=R.Rounds;
    auto CopyVitals=[](TArray<FDigimonBattleUnit>& Units,const std::vector<DigimonVenomNXTCombatCore::Unit>& Core)
    {
        for (int32 I=0; I<Units.Num(); ++I) { Units[I].HP=Core[I].HP; Units[I].SP=Core[I].SP; Units[I].bDefeated=Core[I].HP<=0; }
    };
    CopyVitals(Out.TeamA,R.A); CopyVitals(Out.TeamB,R.B);
    int32 Logged = 0;
    for (const auto& E:R.Events)
    {
        if (++Logged > 80) break; // Text history is bounded independently from the full visible replay.
        const auto& Attackers=E.Team==0?Out.TeamA:Out.TeamB;
        const auto& Defenders=E.Team==0?Out.TeamB:Out.TeamA;
        const FString MoveName=E.MoveIndex>=0?Attackers[E.Actor].Moves[E.MoveIndex].DisplayName.ToString():TEXT("Attack");
        Out.Log.Add(FString::Printf(TEXT("Turn %d | %s: %s > %s | %d damage"),E.Round,*Attackers[E.Actor].DisplayName,*MoveName,*Defenders[E.Target].DisplayName,E.Damage));
    }
    Out.Log.Add(Out.bDraw?TEXT("Draw: battle limit reached or neither team can continue."):Out.bTeamAWon?TEXT("Challenger victory."):TEXT("Defender victory."));
    if (bCapturePresentation)
    {
        Out.Actions.Reserve(static_cast<int32>(R.Events.size()));
        for (const auto& Event:R.Events) Out.Actions.Add(Event);
    }
    return Out;
}
