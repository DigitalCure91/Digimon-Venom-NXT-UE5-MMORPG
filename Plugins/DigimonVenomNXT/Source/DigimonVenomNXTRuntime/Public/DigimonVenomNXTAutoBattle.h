#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTCombatCore.h"
class UDigimonVenomNXTDataSubsystem;

struct DIGIMONVENOMNXTRUNTIME_API FDigimonAutoBattleResult
{
    bool bTeamAWon = false;
    bool bDraw = false;
    int32 Turns = 0;
    TArray<FDigimonBattleUnit> TeamA;
    TArray<FDigimonBattleUnit> TeamB;
    TArray<FString> Log;
    // Captured only for human ranked presentation. No huge trace is replicated or saved.
    TArray<FDigimonBattleUnit> InitialTeamA;
    TArray<FDigimonBattleUnit> InitialTeamB;
    TArray<DigimonVenomNXTCombatCore::Event> Actions;
};
namespace DigimonVenomNXTAutoBattle
{
    inline constexpr int32 CurrentBalanceVersion = 1;
    DIGIMONVENOMNXTRUNTIME_API DigimonVenomNXTCombatCore::Unit ToCoreUnit(const FDigimonBattleUnit& Unit);
    DIGIMONVENOMNXTRUNTIME_API DigimonVenomNXTCombatCore::Move ToCoreMove(const FDigimonMoveSlot& Move);
    DIGIMONVENOMNXTRUNTIME_API FDigimonMoveSlot ResolveMove(FName MoveId, const FDigimonSpeciesDefinition& Species, const UDigimonVenomNXTDataSubsystem* Data);
    /** Returns whether an owned save changed. Existing HP/SP ratios, fainted state and equipped IDs survive. */
    DIGIMONVENOMNXTRUNTIME_API bool MigratePartner(FDigimonOwnedPartner& Partner, const UDigimonVenomNXTDataSubsystem* Data);
    /** Returns success; rebuilds a checkpoint's canonical data while preserving vitality and CTB state. */
    DIGIMONVENOMNXTRUNTIME_API bool RebuildSavedUnit(FDigimonBattleUnit& Unit, const UDigimonVenomNXTDataSubsystem* Data,
        const FDigimonOwnedPartner* OwnedPartner = nullptr, bool bWildEnemy = false, bool bPrivateTraining = false);
    DIGIMONVENOMNXTRUNTIME_API FDigimonBattleUnit BuildUnit(const FDigimonOwnedPartner& Partner, const UDigimonVenomNXTDataSubsystem* Data);
    DIGIMONVENOMNXTRUNTIME_API FDigimonAutoBattleResult Resolve(const TArray<FDigimonOwnedPartner>& A, const TArray<FDigimonOwnedPartner>& B,
        const UDigimonVenomNXTDataSubsystem* Data, int32 ActiveSize, int32 Seed, bool bCapturePresentation = false, bool bWildEncounter = false);
}
