#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTCampaignAuthored.h"
namespace DigimonVenomNXTGhostLine
{
namespace Authored = DigimonVenomNXTCampaignAuthored;
const TArray<FDigimonRelayMap>& Maps() { return Authored::Content(2).Maps; }
const TArray<FDigimonRelayNPC>& NPCs() { return Authored::Content(2).NPCs; }
const FDigimonRelayMap* GetMap(int32 Id) { return Authored::Map(2, Id); }
const FDigimonRelayNPC* GetNPC(FName Id) { return Authored::NPC(2, Id); }
TArray<FDigimonRelayNPC> NPCsForMap(int32 Id) { return NPCs().FilterByPredicate([Id](const auto& N) { return N.MapId == Id; }); }
bool CanEnterMap(const FDigimonRelayProgress& P, int32 Id) { return Authored::CanEnter(2, P, Id); }
bool CanChallenge(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Error) { return Authored::CanChallenge(2, P, N, Error); }
bool Interact(FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Dialogue, FString& Error) { return Authored::Interact(2, P, N, Dialogue, Error); }
FString Objective(const FDigimonRelayProgress& P) { return Authored::Objective(2, P); }
bool Reconcile(FDigimonRelayProgress& P) { return Authored::Reconcile(2, P); }
bool Settle(FDigimonRelayProgress& P, FGuid Id, FName NPCId, bool Win, bool& FirstClear) { return Authored::Settle(2, P, Id, NPCId, Win, FirstClear); }
int32 QuestObjectiveCount(const FDigimonRelayProgress& P, FName Id) { return Authored::QuestCount(2, P, Id); }
bool AdvanceQuest(FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FString& Dialogue, FString& Error) { return Authored::AdvanceQuest(2, P, N, Dialogue, Error); }
bool IsRevealed(const FDigimonRelayProgress& P) { return Authored::Revealed(P); }
bool IsNPCVisible(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N) { return Authored::Visible(2, P, N); }
bool IsFieldComplete(const FDigimonRelayProgress& P, int32 Id)
{
    const auto* M = GetMap(Id);
    return M && (M->bPeaceful || (!M->BadgeId.IsNone() && P.Badges.Contains(M->BadgeId)));
}
FString Epilogue(const FDigimonRelayProgress& P) { return P.bComplete ? Authored::Content(2).Epilogue : FString(); }
FString RoleLabel(const FDigimonRelayNPC& N) { return N.RoleLabel; }
}
