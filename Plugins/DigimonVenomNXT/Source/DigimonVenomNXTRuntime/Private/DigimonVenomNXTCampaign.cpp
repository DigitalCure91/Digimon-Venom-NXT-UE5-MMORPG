#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTCampaignCore.h"
#include "DigimonVenomNXTCampaignAuthored.h"
#include "DigimonVenomNXTChronicles.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTRelaySessionCore.h"

namespace DigimonVenomNXTCampaign
{
bool IsValid(EDigimonPrivateCampaign C) { return DigimonVenomNXTCampaignCore::ValidCampaign(static_cast<int32>(C)); }
FString ContextPrefix(EDigimonPrivateCampaign C)
{
    const auto Prefix = DigimonVenomNXTCampaignCore::ContextPrefix(static_cast<int32>(C));
    return Prefix.empty() ? FString() : FString(UTF8_TO_TCHAR(Prefix.data()));
}
bool TryParseContext(const FString& Context, EDigimonPrivateCampaign& OutCampaign, FName& OutNPCId)
{
    FTCHARToUTF8 Encoded(*Context);
    const int32 Id = DigimonVenomNXTCampaignCore::ContextCampaign(std::string_view(Encoded.Get(), Encoded.Length()));
    if (!DigimonVenomNXTCampaignCore::ValidCampaign(Id)) return false;
    const EDigimonPrivateCampaign Campaign = static_cast<EDigimonPrivateCampaign>(Id);
    const FName NPCId(*Context.Mid(ContextPrefix(Campaign).Len()));
    if (NPCId.IsNone()) return false;
    OutCampaign = Campaign;
    OutNPCId = NPCId;
    return true;
}
FDigimonRelayProgress& Progress(FDigimonPlayerProfile& P, EDigimonPrivateCampaign C)
{
    checkf(IsValid(C), TEXT("Invalid private campaign identity"));
    return C == EDigimonPrivateCampaign::GhostLine ? P.GhostLine : C == EDigimonPrivateCampaign::ParadoxChronicles ? P.Chronicles : P.Relay;
}
const FDigimonRelayProgress& Progress(const FDigimonPlayerProfile& P, EDigimonPrivateCampaign C)
{
    checkf(IsValid(C), TEXT("Invalid private campaign identity"));
    return C == EDigimonPrivateCampaign::GhostLine ? P.GhostLine : C == EDigimonPrivateCampaign::ParadoxChronicles ? P.Chronicles : P.Relay;
}
bool HasPendingBattle(const FDigimonPlayerProfile& P)
{
    return !P.Relay.BattleCheckpointJson.IsEmpty() || !P.Chronicles.BattleCheckpointJson.IsEmpty() || !P.GhostLine.BattleCheckpointJson.IsEmpty();
}
bool HasOtherPendingBattle(const FDigimonPlayerProfile& P, EDigimonPrivateCampaign C)
{
    if (!IsValid(C)) return true;
    for (int32 Id = 0; Id < DigimonVenomNXTCampaignCore::CampaignCount; ++Id)
    {
        const EDigimonPrivateCampaign Other = static_cast<EDigimonPrivateCampaign>(Id);
        if (Other != C && !Progress(P, Other).BattleCheckpointJson.IsEmpty()) return true;
    }
    return false;
}
bool IsActive(const FDigimonPlayerProfile& P) { return P.Relay.bInside || P.Chronicles.bInside || P.GhostLine.bInside; }
FString Name(EDigimonPrivateCampaign C)
{
    return IsValid(C) ? DigimonVenomNXTCampaignAuthored::Content(static_cast<int32>(C)).Name : TEXT("Unknown campaign");
}
const TArray<FDigimonRelayMap>& Maps(EDigimonPrivateCampaign C)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::Maps();
    if (C == EDigimonPrivateCampaign::ParadoxChronicles) return DigimonVenomNXTChronicles::Maps();
    if (C == EDigimonPrivateCampaign::Relay) return DigimonVenomNXTRelay::Maps();
    static const TArray<FDigimonRelayMap> Empty;
    return Empty;
}
const TArray<FDigimonRelayNPC>& NPCs(EDigimonPrivateCampaign C)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::NPCs();
    if (C == EDigimonPrivateCampaign::ParadoxChronicles) return DigimonVenomNXTChronicles::NPCs();
    if (C == EDigimonPrivateCampaign::Relay) return DigimonVenomNXTRelay::NPCs();
    static const TArray<FDigimonRelayNPC> Empty;
    return Empty;
}
const FDigimonRelayMap* GetMap(EDigimonPrivateCampaign C, int32 Id)
{
    return Maps(C).FindByPredicate([Id](const FDigimonRelayMap& Map) { return Map.MapId == Id; });
}
const FDigimonRelayNPC* GetNPC(EDigimonPrivateCampaign C, FName Id)
{
    return NPCs(C).FindByPredicate([Id](const FDigimonRelayNPC& NPC) { return NPC.Id == Id; });
}
TArray<FDigimonRelayNPC> NPCsForMap(EDigimonPrivateCampaign C, int32 Id)
{
    return NPCs(C).FilterByPredicate([Id](const FDigimonRelayNPC& NPC) { return NPC.MapId == Id; });
}
bool IsNPCVisible(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P, const FDigimonRelayNPC& NPC)
{
    return IsValid(C) && GetNPC(C, NPC.Id) && DigimonVenomNXTCampaignAuthored::Visible(static_cast<int32>(C), P, NPC);
}
int32 QuestObjectiveCount(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P, FName QuestId)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::QuestObjectiveCount(P, QuestId);
    return C == EDigimonPrivateCampaign::ParadoxChronicles ? DigimonVenomNXTChronicles::QuestObjectiveCount(P, QuestId) : 0;
}
const FDigimonRelayNPC* CurrentChallenger(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P) { return C == EDigimonPrivateCampaign::Relay ? DigimonVenomNXTRelay::CurrentChallenger(P) : nullptr; }
bool IsBattleRole(EDigimonRelayRole Role) { return DigimonVenomNXTRelay::IsBattleRole(Role) || Role == EDigimonRelayRole::ParadoxBoss || Role == EDigimonRelayRole::FinalBoss; }
bool CanEnterMap(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P, int32 Id)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::CanEnterMap(P, Id);
    if (C == EDigimonPrivateCampaign::ParadoxChronicles) return DigimonVenomNXTChronicles::CanEnterMap(P, Id);
    return C == EDigimonPrivateCampaign::Relay && DigimonVenomNXTRelay::CanEnterMap(P, Id);
}
bool CanChallenge(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P, const FDigimonRelayNPC& NPC, FString& Error)
{
    if (!IsValid(C)) { Error = TEXT("This campaign is unavailable."); return false; }
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::CanChallenge(P, NPC, Error);
    return C == EDigimonPrivateCampaign::ParadoxChronicles ? DigimonVenomNXTChronicles::CanChallenge(P, NPC, Error) : DigimonVenomNXTRelay::CanChallenge(P, NPC, Error);
}
bool Interact(EDigimonPrivateCampaign C, FDigimonRelayProgress& P, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error)
{
    if (!IsValid(C)) { Error = TEXT("This campaign is unavailable."); return false; }
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::Interact(P, NPC, Dialogue, Error);
    return C == EDigimonPrivateCampaign::ParadoxChronicles ? DigimonVenomNXTChronicles::Interact(P, NPC, Dialogue, Error) : DigimonVenomNXTRelay::Interact(P, NPC, Dialogue, Error);
}
bool AdvanceQuest(EDigimonPrivateCampaign C, FDigimonRelayProgress& P, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::AdvanceQuest(P, NPC, Dialogue, Error);
    if (C == EDigimonPrivateCampaign::ParadoxChronicles) return DigimonVenomNXTChronicles::AdvanceQuest(P, NPC, Dialogue, Error);
    Error = TEXT("This campaign has no assignment to turn in here."); return false;
}
FString Objective(EDigimonPrivateCampaign C, const FDigimonRelayProgress& P)
{
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::Objective(P);
    if (C == EDigimonPrivateCampaign::ParadoxChronicles) return DigimonVenomNXTChronicles::Objective(P);
    return C == EDigimonPrivateCampaign::Relay ? DigimonVenomNXTRelay::Objective(P) : TEXT("Select an available story campaign.");
}
bool Reconcile(FDigimonPlayerProfile& P)
{
    bool Changed = false;
    Changed |= DigimonVenomNXTRelay::Reconcile(P.Relay);
    Changed |= DigimonVenomNXTChronicles::Reconcile(P.Chronicles);
    Changed |= DigimonVenomNXTGhostLine::Reconcile(P.GhostLine);
    if (!IsValid(P.ActiveStoryCampaign)) { P.ActiveStoryCampaign = EDigimonPrivateCampaign::Relay; Changed = true; }
    const int32 Saved = DigimonVenomNXTRelaySessionCore::SavedCampaign(static_cast<int32>(P.ActiveStoryCampaign),
        P.Relay.bInside, P.Chronicles.bInside, !P.Relay.BattleCheckpointJson.IsEmpty(), !P.Chronicles.BattleCheckpointJson.IsEmpty(),
        P.GhostLine.bInside, !P.GhostLine.BattleCheckpointJson.IsEmpty());
    // Prefer the one durable pending decision, then the explicit active journey.
    // Conflicting decisions are deliberately retained for a safe restore refusal.
    if (DigimonVenomNXTRelaySessionCore::ValidCampaign(Saved))
    {
        const EDigimonPrivateCampaign Active = static_cast<EDigimonPrivateCampaign>(Saved);
        if (P.ActiveStoryCampaign != Active) { P.ActiveStoryCampaign = Active; Changed = true; }
        for (int32 Id = 0; Id < DigimonVenomNXTCampaignCore::CampaignCount; ++Id)
        {
            const EDigimonPrivateCampaign Other = static_cast<EDigimonPrivateCampaign>(Id);
            if (Other != Active && Progress(P, Other).bInside) { Progress(P, Other).bInside = false; Changed = true; }
        }
    }
    return Changed;
}
bool Settle(EDigimonPrivateCampaign C, FDigimonRelayProgress& P, FGuid BattleId, FName NPCId, bool Victory, bool& FirstClear)
{
    if (!IsValid(C)) { FirstClear = false; return false; }
    if (C == EDigimonPrivateCampaign::GhostLine) return DigimonVenomNXTGhostLine::Settle(P, BattleId, NPCId, Victory, FirstClear);
    return C == EDigimonPrivateCampaign::ParadoxChronicles ? DigimonVenomNXTChronicles::Settle(P, BattleId, NPCId, Victory, FirstClear) : DigimonVenomNXTRelay::Settle(P, BattleId, NPCId, Victory, FirstClear);
}
int32 ScanGain(const FDigimonPlayerProfile& P, EDigimonVariant Variant, int32 Base, bool WildVictory)
{
    return DigimonVenomNXTCampaignCore::ScanGain(Base, static_cast<int32>(Variant), P.GhostLine.bShinyScanMastery,
        P.Chronicles.bParadoxScanMastery, P.Relay.bFirewallScanMastery, WildVictory);
}
}
