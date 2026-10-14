#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTCampaignAuthored.h"
namespace DigimonVenomNXTRelay
{
namespace Authored = DigimonVenomNXTCampaignAuthored;
const TArray<FDigimonRelayMap>& Maps() { return Authored::Content(0).Maps; }
const TArray<FDigimonRelayNPC>& NPCs() { return Authored::Content(0).NPCs; }
const FDigimonRelayMap* GetMap(int32 Id) { return Authored::Map(0, Id); }
const FDigimonRelayNPC* GetNPC(FName Id) { return Authored::NPC(0, Id); }
TArray<FDigimonRelayNPC> NPCsForMap(int32 Id) { return NPCs().FilterByPredicate([Id](const auto& N) { return N.MapId == Id; }); }
bool CanEnterMap(const FDigimonRelayProgress& P, int32 Id) { return Authored::CanEnter(0, P, Id); }
bool CanChallenge(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Error) { return Authored::CanChallenge(0, P, N, Error); }
bool Interact(FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Dialogue, FString& Error) { return Authored::Interact(0, P, N, Dialogue, Error); }
FString Objective(const FDigimonRelayProgress& P) { return Authored::Objective(0, P); }
bool Reconcile(FDigimonRelayProgress& P) { return Authored::Reconcile(0, P); }
bool Settle(FDigimonRelayProgress& P, FGuid Id, FName NPCId, bool Win, bool& FirstClear) { return Authored::Settle(0, P, Id, NPCId, Win, FirstClear); }
const FDigimonRelayNPC* CurrentChallenger(const FDigimonRelayProgress& P) { return Authored::Challenger(0, P); }
bool IsBattleRole(EDigimonRelayRole Role) { return Authored::IsBattle(Role); }
}
