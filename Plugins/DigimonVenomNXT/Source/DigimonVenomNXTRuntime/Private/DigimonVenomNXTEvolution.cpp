#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTScanCore.h"

namespace
{
    DigimonVenomNXTEvolutionCore::Rules Rules()
    {
        const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
        DigimonVenomNXTEvolutionCore::Rules R;
        R.MaxABI = S->MaxABI; R.MinimumDeEvolutionLevel = S->MinimumDeEvolutionLevel;
        R.EvolutionBaseABI = S->EvolutionBaseABI; R.EvolutionLevelsPerABI = S->EvolutionLevelsPerABI;
        R.DeEvolutionBaseABI = S->DeEvolutionBaseABI; R.DeEvolutionLevelsPerABI = S->DeEvolutionLevelsPerABI;
        return R;
    }

    int32 Tier(EDigimonStage Stage)
    {
        if (static_cast<int32>(Stage) == 9 || static_cast<int32>(Stage) == 10) return 3;
        switch (Stage)
        {
            case EDigimonStage::Fresh: return 0;
            case EDigimonStage::InTraining: return 1;
            case EDigimonStage::Rookie: return 2;
            case EDigimonStage::Champion: return 3;
            case EDigimonStage::Ultimate: return 4;
            case EDigimonStage::Mega: return 5;
            case EDigimonStage::Ultra: return 6;
            case EDigimonStage::ReservedStage: return 2;
            default: return 2;
        }
    }

    int64 UsedTenths(const FDigimonOwnedPartner& P)
    {
        const FDigimonStats& T = P.PermanentTraining;
        return DigimonVenomNXTEvolutionCore::TrainingUsedTenths(T.MaxHP, T.MaxSP, T.Attack, T.Defense, T.Spirit, T.Speed);
    }

    int32 TrainingValue(const FDigimonOwnedPartner& Partner, EDigimonTrainingStat Stat)
    {
        const FDigimonStats& Training = Partner.PermanentTraining;
        switch (Stat)
        {
            case EDigimonTrainingStat::MaxHP: return Training.MaxHP;
            case EDigimonTrainingStat::MaxSP: return Training.MaxSP;
            case EDigimonTrainingStat::Attack: return Training.Attack;
            case EDigimonTrainingStat::Defense: return Training.Defense;
            case EDigimonTrainingStat::Spirit: return Training.Spirit;
            case EDigimonTrainingStat::Speed: return Training.Speed;
            default: return -1;
        }
    }

    FDigimonEvolutionOption MakeOption(const FDigimonOwnedPartner& Partner, const FDigimonSpeciesDefinition& Source,
        const FDigimonSpeciesDefinition& Target, FDigimonEvolutionRequirement Requirement, bool bReverse,
        const FDigimonStats& EffectiveStats)
    {
        const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
        const auto R = Rules();
        FDigimonEvolutionOption Option;
        Option.TargetSpeciesId = Target.SpeciesId;
        Option.TargetStage = Target.Stage;
        Option.bDeEvolution = bReverse;
        if (bReverse)
        {
            Requirement = FDigimonEvolutionRequirement();
            Requirement.TargetSpeciesId = Target.SpeciesId;
            Requirement.RequiredLevel = DigimonVenomNXTEvolutionCore::MinimumChangeLevel(true, R);
        }
        else
        {
            Requirement.RequiredLevel = FMath::Max(2, Requirement.RequiredLevel);
            if (Target.Stage == EDigimonStage::InTraining)
                Requirement.RequiredCAM = FMath::Max(Requirement.RequiredCAM, FMath::Clamp(S->InTrainingEvolutionCAM, 0, 100));
            else if (Target.Stage == EDigimonStage::Rookie)
                Requirement.RequiredCAM = FMath::Max(Requirement.RequiredCAM, FMath::Clamp(S->RookieEvolutionCAM, 0, 100));
            else if (Target.Stage == EDigimonStage::Champion)
                Requirement.RequiredABI = FMath::Max(Requirement.RequiredABI, FMath::Clamp(S->ChampionEvolutionABI, 0, 200));
            else if (Target.Stage == EDigimonStage::Ultimate)
                Requirement.RequiredABI = FMath::Max(Requirement.RequiredABI, FMath::Clamp(S->UltimateEvolutionABI, 1, 200));
            else if (Target.Stage == EDigimonStage::Mega || Target.Stage == EDigimonStage::Ultra)
                Requirement.RequiredABI = FMath::Max(Requirement.RequiredABI, FMath::Clamp(S->MegaEvolutionABI, 1, 200));
        }
        Option.Requirement = Requirement;
        Option.RequiredLevel = Requirement.RequiredLevel;
        Option.RequiredCAM = Requirement.RequiredCAM;
        Option.RequiredABI = Requirement.RequiredABI;
        Option.ResultABI = DigimonVenomNXTEvolutionCore::ResultABI(Partner.ABI,
            DigimonVenomNXTEvolutionCore::ABIGain(Tier(Source.Stage), Partner.Level, bReverse, R), R.MaxABI);
        Option.ABIGain = FMath::Max(0, Option.ResultABI - Partner.ABI);
        TArray<FString> Missing;
        if (!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Partner.Variant), Target.bHasNormalArtwork,
            Target.bHasParadoxArtwork, Target.bHasShinyArtwork, Target.bHasFirewallArtwork))
            Missing.Add(TEXT("This variety is not installed for the target form"));
        auto Check = [&Missing](const TCHAR* Label, int32 Current, int32 Required)
        {
            if (Current < Required) Missing.Add(FString::Printf(TEXT("%s %d / %d"), Label, Current, Required));
        };
        Check(TEXT("Level"), Partner.Level, Requirement.RequiredLevel);
        Check(TEXT("CAM"), Partner.CAM, Requirement.RequiredCAM);
        Check(TEXT("ABI"), Partner.ABI, Requirement.RequiredABI);
        Check(TEXT("ATK"), EffectiveStats.Attack, Requirement.RequiredAttack);
        Check(TEXT("DEF"), EffectiveStats.Defense, Requirement.RequiredDefense);
        Check(TEXT("INT"), EffectiveStats.Spirit, Requirement.RequiredSpirit);
        Check(TEXT("SPD"), EffectiveStats.Speed, Requirement.RequiredSpeed);
        Option.bAvailable = DigimonVenomNXTEvolutionCore::MeetsRequirements(
            Partner.Level, Partner.CAM, Partner.ABI,
            Requirement.RequiredLevel, Requirement.RequiredCAM, Requirement.RequiredABI) && Missing.IsEmpty();
        Option.MissingReasons = FString::Join(Missing, TEXT("  |  "));
        return Option;
    }
}

TArray<FDigimonEvolutionOption> DigimonVenomNXTEvolution::GetOptions(const FDigimonOwnedPartner& Partner,
    const UDigimonVenomNXTDataSubsystem* Data, bool bIncludeDeEvolution)
{
    TArray<FDigimonEvolutionOption> Options;
    FDigimonSpeciesDefinition Source;
    if (!Data || !Partner.IsValid() || !Data->GetSpecies(Partner.SpeciesId, Source) || Source.bPlaceholder) return Options;
    const FDigimonStats EffectiveStats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats;
    TSet<FName> ForwardTargets;
    for (const FDigimonEvolutionRequirement& Route : Source.Evolutions)
    {
        FDigimonSpeciesDefinition Target;
        if (Route.TargetSpeciesId == Source.SpeciesId || ForwardTargets.Contains(Route.TargetSpeciesId) ||
            !Data->GetSpecies(Route.TargetSpeciesId, Target) || Target.bPlaceholder || Tier(Target.Stage) <= Tier(Source.Stage)) continue;
        ForwardTargets.Add(Target.SpeciesId);
        Options.Add(MakeOption(Partner, Source, Target, Route, false, EffectiveStats));
    }
    if (bIncludeDeEvolution)
    {
        for (const FDigimonSpeciesDefinition& Target : Data->GetDeEvolutionSources(Source.SpeciesId))
        {
            if (Target.bPlaceholder || Target.SpeciesId == Source.SpeciesId || Tier(Target.Stage) >= Tier(Source.Stage)) continue;
            Options.Add(MakeOption(Partner, Source, Target, FDigimonEvolutionRequirement(), true, EffectiveStats));
        }
    }
    Options.Sort([](const FDigimonEvolutionOption& A, const FDigimonEvolutionOption& B)
    {
        if (A.bDeEvolution != B.bDeEvolution) return !A.bDeEvolution;
        return A.TargetSpeciesId.LexicalLess(B.TargetSpeciesId);
    });
    return Options;
}

bool DigimonVenomNXTEvolution::TryTransform(FDigimonOwnedPartner& Partner, FName TargetSpeciesId, bool bDeEvolution,
    const UDigimonVenomNXTDataSubsystem* Data, FString& OutMessage)
{
    const TArray<FDigimonEvolutionOption> Options = GetOptions(Partner, Data, bDeEvolution);
    const FDigimonEvolutionOption* Option = Options.FindByPredicate([TargetSpeciesId, bDeEvolution](const FDigimonEvolutionOption& Candidate)
    {
        return Candidate.TargetSpeciesId == TargetSpeciesId && Candidate.bDeEvolution == bDeEvolution;
    });
    if (!Option)
    {
        OutMessage = TEXT("That form is not linked to this Digimon. Select an available route and try again.");
        return false;
    }
    if (!Option->bAvailable)
    {
        OutMessage = TEXT("Requirements not met: ") + Option->MissingReasons;
        return false;
    }
    FDigimonSpeciesDefinition Target;
    if (!Data || !Data->GetSpecies(TargetSpeciesId, Target) || Target.bPlaceholder)
    {
        OutMessage = TEXT("This Digimon's form is unavailable. No progress was changed.");
        return false;
    }
    const int32 ABIGain = Option->ABIGain;
    DigimonVenomNXTEvolutionCore::ApplyIdentityPreservingTransform(Partner, TargetSpeciesId, Option->ResultABI);
    Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    // The source regenerates the two techniques for the new form; their element
    // and stage SP costs must not retain stale metadata from the previous species.
    Partner.Moves.Reset();
    for (int32 Index = 0; Index < Target.LearnableMoves.Num() && Partner.Moves.Num() < 4; ++Index)
    {
        if (Partner.Moves.ContainsByPredicate([&Target, Index](const FDigimonMoveSlot& Existing)
            { return Existing.MoveId == Target.LearnableMoves[Index]; })) continue;
        FDigimonMoveSlot Move;
        Move.MoveId = Target.LearnableMoves[Index];
        Partner.Moves.Add(Move);
    }
    const FDigimonBattleUnit Rebuilt = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
    Partner.Moves = Rebuilt.Moves; // Resolve inherited IDs through the shared canonical move catalog.
    const FDigimonStats& Total = Rebuilt.Stats;
    Partner.CurrentHP = Total.MaxHP;
    Partner.CurrentSP = Total.MaxSP;
    OutMessage = FString::Printf(TEXT("%s into %s! Level reset to 1. +%d permanent ABI (%d total). CAM and training retained."),
        bDeEvolution ? TEXT("De-evolved") : TEXT("Evolved"), *Target.DisplayName.ToString(), ABIGain, Partner.ABI);
    return true;
}

int32 DigimonVenomNXTEvolution::TrainingCapacity(const FDigimonOwnedPartner& Partner)
{
    return DigimonVenomNXTEvolutionCore::TrainingCapacity(Partner.ABI, GetDefault<UDigimonVenomNXTSettings>()->TrainingBaseCapacity);
}

float DigimonVenomNXTEvolution::TrainingUsed(const FDigimonOwnedPartner& Partner)
{
    return static_cast<float>(UsedTenths(Partner)) / 10.0f;
}

bool DigimonVenomNXTEvolution::CanTrain(const FDigimonOwnedPartner& Partner, EDigimonTrainingStat Stat, int32 Amount)
{
    return DigimonVenomNXTEvolutionCore::CanTrainStat(TrainingValue(Partner, Stat), Amount) &&
        DigimonVenomNXTEvolutionCore::CanTrain(Partner.ABI, UsedTenths(Partner), Amount * 10,
            GetDefault<UDigimonVenomNXTSettings>()->TrainingBaseCapacity);
}

bool DigimonVenomNXTEvolution::TryTrain(FDigimonOwnedPartner& Partner, EDigimonTrainingStat Stat, int32 Amount)
{
    if (!CanTrain(Partner, Stat, Amount)) return false;
    switch (Stat)
    {
        case EDigimonTrainingStat::MaxHP: Partner.PermanentTraining.MaxHP += Amount; break;
        case EDigimonTrainingStat::MaxSP: Partner.PermanentTraining.MaxSP += Amount; break;
        case EDigimonTrainingStat::Attack: Partner.PermanentTraining.Attack += Amount; break;
        case EDigimonTrainingStat::Defense: Partner.PermanentTraining.Defense += Amount; break;
        case EDigimonTrainingStat::Spirit: Partner.PermanentTraining.Spirit += Amount; break;
        case EDigimonTrainingStat::Speed: Partner.PermanentTraining.Speed += Amount; break;
        default: return false;
    }
    return true;
}

int32 DigimonVenomNXTEvolution::FeedCAM(FDigimonOwnedPartner& Partner)
{
    if (Partner.CAM >= 100) return 0;
    const int32 Before = FMath::Max(0, Partner.CAM);
    Partner.CAM = FMath::Min(100, Before + FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->CAMMeatGain, 1, 100));
    return Partner.CAM - Before;
}

int32 DigimonVenomNXTEvolution::FeedABI(FDigimonOwnedPartner& Partner)
{
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    if (Partner.ABI >= DigimonVenomNXTEvolutionCore::MaximumABI(S->MaxABI)) return 0;
    const int32 Before = FMath::Max(0, Partner.ABI);
    Partner.ABI = DigimonVenomNXTEvolutionCore::ResultABI(Before, FMath::Clamp(S->ABIMeatGain, 1, 200), S->MaxABI);
    return Partner.ABI - Before;
}
