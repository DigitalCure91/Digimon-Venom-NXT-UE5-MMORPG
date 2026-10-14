#pragma once
#include "DigimonVenomNXTRelay.h"

/** The original game's authored campaigns, translated without substituting content. */
namespace DigimonVenomNXTCampaignAuthored
{
    struct FContent
    {
        FString Name, Introduction, Epilogue;
        FName FinalId;
        TArray<FDigimonRelayMap> Maps;
        TArray<FDigimonRelayNPC> NPCs;
        TArray<FName> Challengers;
    };
    const FContent& Content(int32 Campaign);
    const FDigimonRelayMap* Map(int32 Campaign, int32 MapId);
    const FDigimonRelayNPC* NPC(int32 Campaign, FName Id);
    bool IsBattle(EDigimonRelayRole Role);
    bool Revealed(const FDigimonRelayProgress& Progress);
    bool Visible(int32 Campaign, const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC);
    bool CanEnter(int32 Campaign, const FDigimonRelayProgress& Progress, int32 MapId);
    const FDigimonRelayNPC* Challenger(int32 Campaign, const FDigimonRelayProgress& Progress);
    int32 QuestCount(int32 Campaign, const FDigimonRelayProgress& Progress, FName QuestId);
    bool CanChallenge(int32 Campaign, const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Error);
    bool Interact(int32 Campaign, FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    bool AdvanceQuest(int32 Campaign, FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    FString Objective(int32 Campaign, const FDigimonRelayProgress& Progress);
    bool Reconcile(int32 Campaign, FDigimonRelayProgress& Progress);
    bool Settle(int32 Campaign, FDigimonRelayProgress& Progress, FGuid BattleId, FName NPCId, bool Victory, bool& FirstClear);
}
