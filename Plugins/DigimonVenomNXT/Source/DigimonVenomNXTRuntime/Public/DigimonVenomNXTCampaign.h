#pragma once
#include "DigimonVenomNXTRelay.h"

/** Campaign routing keeps saves, pending battles and map identities separate. */
namespace DigimonVenomNXTCampaign
{
    DIGIMONVENOMNXTRUNTIME_API bool IsValid(EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API FString ContextPrefix(EDigimonPrivateCampaign Campaign);
    /** Reject unknown/empty contexts without falling back to another campaign. */
    DIGIMONVENOMNXTRUNTIME_API bool TryParseContext(const FString& Context, EDigimonPrivateCampaign& OutCampaign, FName& OutNPCId);
    DIGIMONVENOMNXTRUNTIME_API bool HasPendingBattle(const FDigimonPlayerProfile& Profile);
    DIGIMONVENOMNXTRUNTIME_API bool HasOtherPendingBattle(const FDigimonPlayerProfile& Profile, EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API FDigimonRelayProgress& Progress(FDigimonPlayerProfile& Profile, EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayProgress& Progress(const FDigimonPlayerProfile& Profile, EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API bool IsActive(const FDigimonPlayerProfile& Profile);
    DIGIMONVENOMNXTRUNTIME_API FString Name(EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayMap>& Maps(EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayNPC>& NPCs(EDigimonPrivateCampaign Campaign);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayMap* GetMap(EDigimonPrivateCampaign Campaign, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayNPC* GetNPC(EDigimonPrivateCampaign Campaign, FName Id);
    DIGIMONVENOMNXTRUNTIME_API TArray<FDigimonRelayNPC> NPCsForMap(EDigimonPrivateCampaign Campaign, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API bool IsNPCVisible(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC);
    DIGIMONVENOMNXTRUNTIME_API int32 QuestObjectiveCount(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress, FName QuestId);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayNPC* CurrentChallenger(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool IsBattleRole(EDigimonRelayRole Role);
    DIGIMONVENOMNXTRUNTIME_API bool CanEnterMap(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API bool CanChallenge(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool Interact(EDigimonPrivateCampaign Campaign, FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool AdvanceQuest(EDigimonPrivateCampaign Campaign, FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API FString Objective(EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& Progress);
    /** Reconcile each native campaign independently. Save before publishing. */
    DIGIMONVENOMNXTRUNTIME_API bool Reconcile(FDigimonPlayerProfile& Profile);
    DIGIMONVENOMNXTRUNTIME_API bool Settle(EDigimonPrivateCampaign Campaign, FDigimonRelayProgress& Progress, FGuid BattleId, FName NPCId, bool bVictory, bool& bFirstClear);
    /** Matching mastery grants +20% scan on wild victory; no stacking or cross-variety leakage. */
    DIGIMONVENOMNXTRUNTIME_API int32 ScanGain(const FDigimonPlayerProfile& Profile, EDigimonVariant Variant, int32 Base, bool bWildVictory);
}
