#pragma once
#include "DigimonVenomNXTRelay.h"

/** Private cyber investigation: Backchannel plus thirty sequential field cases. */
namespace DigimonVenomNXTGhostLine
{
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayMap>& Maps();
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayNPC>& NPCs();
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayMap* GetMap(int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayNPC* GetNPC(FName Id);
    DIGIMONVENOMNXTRUNTIME_API TArray<FDigimonRelayNPC> NPCsForMap(int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API int32 QuestObjectiveCount(const FDigimonRelayProgress& Progress, FName QuestId);
    DIGIMONVENOMNXTRUNTIME_API bool CanEnterMap(const FDigimonRelayProgress& Progress, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API bool CanChallenge(const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool Interact(FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool AdvanceQuest(FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API FString Objective(const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool Reconcile(FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool Settle(FDigimonRelayProgress& Progress, FGuid BattleId, FName NPCId, bool bVictory, bool& bFirstClear);
    DIGIMONVENOMNXTRUNTIME_API bool IsRevealed(const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool IsNPCVisible(const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC);
    DIGIMONVENOMNXTRUNTIME_API bool IsFieldComplete(const FDigimonRelayProgress& Progress, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API FString Epilogue(const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API FString RoleLabel(const FDigimonRelayNPC& NPC);
}
