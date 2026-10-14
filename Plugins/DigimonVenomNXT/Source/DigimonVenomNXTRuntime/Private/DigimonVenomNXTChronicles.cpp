#include "DigimonVenomNXTChronicles.h"
#include "DigimonVenomNXTCampaignAuthored.h"
namespace DigimonVenomNXTChronicles
{
namespace Authored = DigimonVenomNXTCampaignAuthored;
const TArray<FDigimonRelayMap>& Maps() { return Authored::Content(1).Maps; }
const TArray<FDigimonRelayNPC>& NPCs() { return Authored::Content(1).NPCs; }
const FDigimonRelayMap* GetMap(int32 Id) { return Authored::Map(1, Id); }
const FDigimonRelayNPC* GetNPC(FName Id) { return Authored::NPC(1, Id); }
TArray<FDigimonRelayNPC> NPCsForMap(int32 Id) { return NPCs().FilterByPredicate([Id](const auto& N) { return N.MapId == Id; }); }
bool CanEnterMap(const FDigimonRelayProgress& P, int32 Id) { return Authored::CanEnter(1, P, Id); }
bool CanChallenge(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Error) { return Authored::CanChallenge(1, P, N, Error); }
bool Interact(FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Dialogue, FString& Error) { return Authored::Interact(1, P, N, Dialogue, Error); }
FString Objective(const FDigimonRelayProgress& P) { return Authored::Objective(1, P); }
bool Reconcile(FDigimonRelayProgress& P) { return Authored::Reconcile(1, P); }
bool Settle(FDigimonRelayProgress& P, FGuid Id, FName NPCId, bool Win, bool& FirstClear) { return Authored::Settle(1, P, Id, NPCId, Win, FirstClear); }
int32 QuestObjectiveCount(const FDigimonRelayProgress& P, FName Id) { return Authored::QuestCount(1, P, Id); }
bool AdvanceQuest(FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Dialogue, FString& Error) { return Authored::AdvanceQuest(1, P, N, Dialogue, Error); }
}
