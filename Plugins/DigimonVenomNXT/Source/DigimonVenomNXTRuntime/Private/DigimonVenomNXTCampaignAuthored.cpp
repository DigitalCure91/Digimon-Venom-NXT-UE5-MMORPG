#include "DigimonVenomNXTCampaignAuthored.h"
#include "DigimonVenomNXTRelayCore.h"

namespace DigimonVenomNXTCampaignAuthored
{
#include "DigimonVenomNXTCampaignContent.inl"

namespace
{
const FName RevealMarker(TEXT("campaign_revealed"));
FName HackMarker(FName Id) { return FName(*(TEXT("hacked:") + Id.ToString())); }
FName HolderMarker(FName Id) { return FName(*(TEXT("title_holder:") + Id.ToString())); }
bool Completed(const FDigimonRelayProgress& P, FName Id)
{
    return P.CompletedObjectives.Contains(Id) || P.DefeatedTamers.Contains(Id);
}
bool AllCompleted(const FDigimonRelayProgress& P, const TArray<FName>& IDs)
{
    for (FName Id : IDs) if (!Completed(P, Id)) return false;
    return true;
}
bool ContainsAll(const TArray<FName>& Existing, const TArray<FName>& Required)
{
    for (FName Id : Required) if (!Existing.Contains(Id)) return false;
    return true;
}
bool AllHacked(const FDigimonRelayProgress& P, const TArray<FName>& IDs)
{
    for (FName Id : IDs) if (!P.CompletedObjectives.Contains(HackMarker(Id))) return false;
    return true;
}
bool Ready(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N)
{
    return AllCompleted(P, N.RequiresCompleted) && ContainsAll(P.AcceptedQuests, N.RequiresAccepted) &&
        ContainsAll(P.Badges, N.RequiresBadges) && AllHacked(P, N.RequiresHacked) &&
        (N.RequiresReveal < 0 || Revealed(P) == (N.RequiresReveal != 0));
}
FString Branch(const FDigimonRelayProgress& P, const FDigimonRelayNPC& N, FName Key)
{
    for (const auto& Variant : N.DialogueVariants)
    {
        if ((!Variant.Branches.IsEmpty() && !Variant.Branches.Contains(Key)) ||
            (Variant.RequiresReveal >= 0 && Revealed(P) != (Variant.RequiresReveal != 0)) ||
            (Variant.RequiresComplete >= 0 && P.bComplete != (Variant.RequiresComplete != 0)) ||
            !AllCompleted(P, Variant.RequiresCompleted) || !AllHacked(P, Variant.RequiresHacked)) continue;
        if (!Variant.Text.IsEmpty()) return Variant.Text;
    }
    const auto Text = [&](FName Id) -> const FString* { return N.DialogueBranches.Find(Id); };
    if (P.bComplete) if (const FString* T = Text(TEXT("campaign_complete"))) return *T;
    if (Key == TEXT("repeat") && Revealed(P)) if (const FString* T = Text(TEXT("after_reveal"))) return *T;
    if (Key == TEXT("repeat") && P.CompletedObjectives.Contains(HackMarker(N.Id)))
        if (const FString* T = Text(TEXT("hacked_repeat"))) return *T;
    if (const FString* T = Text(Key)) return *T;
    return N.Dialogue;
}
}

const FDigimonRelayMap* Map(int32 C, int32 Id)
{
    return Content(C).Maps.FindByPredicate([Id](const auto& M) { return M.MapId == Id; });
}
const FDigimonRelayNPC* NPC(int32 C, FName Id)
{
    return Content(C).NPCs.FindByPredicate([Id](const auto& N) { return N.Id == Id; });
}
bool IsBattle(EDigimonRelayRole R)
{
    return R == EDigimonRelayRole::Tamer || R == EDigimonRelayRole::Gym || R == EDigimonRelayRole::Champion ||
        R == EDigimonRelayRole::Challenger || R == EDigimonRelayRole::ParadoxBoss || R == EDigimonRelayRole::FinalBoss;
}
bool Revealed(const FDigimonRelayProgress& P) { return P.CompletedObjectives.Contains(RevealMarker); }
const FDigimonRelayNPC* Challenger(int32 C, const FDigimonRelayProgress& P)
{
    const auto& IDs = Content(C).Challengers;
    if (P.bEverChampion && !P.bIsChampion)
        for (FName Id : IDs) if (P.CompletedObjectives.Contains(HolderMarker(Id))) return NPC(C, Id);
    return P.bEverChampion && !IDs.IsEmpty() ? NPC(C, IDs[FMath::Max(0, P.ChallengerIndex) % IDs.Num()]) : nullptr;
}
bool Visible(int32 C, const FDigimonRelayProgress& P, const FDigimonRelayNPC& N)
{
    if ((N.bHideOnComplete || N.CharacterId == TEXT("mara_vale")) && P.bComplete) return false;
    if (N.bHideOnReveal && Revealed(P)) return false;
    if (N.bShowRequiresReveal && !Revealed(P)) return false;
    if (N.Role == EDigimonRelayRole::Champion) return !P.bEverChampion;
    if (N.Role == EDigimonRelayRole::Challenger)
    {
        const auto* Current = Challenger(C, P);
        return Current && Current->Id == N.Id;
    }
    return true;
}
bool CanEnter(int32 C, const FDigimonRelayProgress& P, int32 Id)
{
    const auto* M = Map(C, Id);
    return M && ContainsAll(P.Badges, M->RequiredBadges);
}
int32 QuestCount(int32 C, const FDigimonRelayProgress& P, FName Id)
{
    const auto* Q = NPC(C, Id);
    if (!Q || Q->Role != EDigimonRelayRole::Quest || !P.AcceptedQuests.Contains(Id)) return 0;
    if (Q->QuestRequires.IsEmpty()) return Ready(P, *Q) ? 1 : 0;
    int32 Count = 0;
    for (FName Required : Q->QuestRequires) if (Completed(P, Required)) ++Count;
    return Count;
}
bool CanChallenge(int32 C, const FDigimonRelayProgress& P, const FDigimonRelayNPC& Input, FString& Error)
{
    const auto* N = NPC(C, Input.Id);
    if (!N || !IsBattle(N->Role)) { Error = TEXT("This contact offers support or an assignment."); return false; }
    if (!CanEnter(C, P, N->MapId)) { Error = TEXT("Complete the preceding chapter and earn its badge before entering this route."); return false; }
    if (!Visible(C, P, *N)) { Error = TEXT("This encounter is no longer on your current story route."); return false; }
    if (!Ready(P, *N))
    {
        Error = N->DialogueBranches.FindRef(TEXT("locked"));
        if (Error.IsEmpty()) Error = TEXT("Complete the journal's required assignments before beginning this encounter.");
        return false;
    }
    if (!N->bRepeatable && Completed(P, N->Id)) { Error = TEXT("This story encounter is complete. Your rewards and progress remain saved."); return false; }
    Error.Reset(); return true;
}
bool Interact(int32 C, FDigimonRelayProgress& P, const FDigimonRelayNPC& Input, FString& Dialogue, FString& Error)
{
    const auto* N = NPC(C, Input.Id);
    if (!N || !CanEnter(C, P, N->MapId) || !Visible(C, P, *N)) { Error = TEXT("This contact is unavailable on your current story route."); return false; }
    FName Key(TEXT("ready"));
    if (!Ready(P, *N)) Key = TEXT("locked");
    else if (Completed(P, N->Id)) Key = TEXT("repeat");
    else if (N->Role == EDigimonRelayRole::Quest)
        Key = !P.AcceptedQuests.Contains(N->Id) ? TEXT("quest_start") : QuestCount(C, P, N->Id) >= N->QuestTarget ? TEXT("quest_complete") : TEXT("quest_progress");
    else if (IsBattle(N->Role)) Key = TEXT("ready");
    const auto* M = Map(C, N->MapId);
    if (N->bMentor && M && ((!M->BadgeId.IsNone() && P.Badges.Contains(M->BadgeId)) || (C == 0 && M->MapId >= 17 && P.bEverChampion))) Key = TEXT("won");
    Dialogue = Branch(P, *N, Key);
    Error.Reset(); return true;
}
bool AdvanceQuest(int32 C, FDigimonRelayProgress& P, const FDigimonRelayNPC& Input, FString& Dialogue, FString& Error)
{
    const auto* Q = NPC(C, Input.Id);
    if (!Q || Q->Role != EDigimonRelayRole::Quest || !CanEnter(C, P, Q->MapId) || !Visible(C, P, *Q) || !Ready(P, *Q))
    { Error = TEXT("This assignment is not available yet. Follow the prerequisites in your journal."); return false; }
    if (Completed(P, Q->Id)) { Error = TEXT("This assignment and its first-clear rewards are already recorded."); return false; }
    if (!P.AcceptedQuests.Contains(Q->Id))
    {
        P.AcceptedQuests.AddUnique(Q->Id);
        Dialogue = TEXT("Assignment accepted.\n\n") + Branch(P, *Q, TEXT("quest_progress"));
    }
    else
    {
        if (QuestCount(C, P, Q->Id) < Q->QuestTarget) { Error = TEXT("Complete the required witness battle, then return to report your findings."); return false; }
        P.CompletedObjectives.AddUnique(Q->Id);
        if (!Q->BadgeId.IsNone()) P.Badges.AddUnique(Q->BadgeId);
        if (Q->bRevealOnComplete) P.CompletedObjectives.AddUnique(RevealMarker);
        Dialogue = Branch(P, *Q, TEXT("won"));
    }
    Reconcile(C, P);
    Error.Reset(); return true;
}
FString Objective(int32 C, const FDigimonRelayProgress& P)
{
    if (!P.BattleCheckpointJson.IsEmpty()) return TEXT("Resume your saved story battle. Your exact turn, HP, SP and queued commands are waiting.");
    if (C == 0 && P.bEverChampion)
    {
        const auto* Next = Challenger(C, P);
        return FString::Printf(TEXT("%s your Dawn championship against %s at Crown Terminal. Permanent +20%% FireWall scan gain remains active."),
            P.bIsChampion ? TEXT("Defend") : TEXT("Reclaim"), Next ? *Next->Name : TEXT("the next challenger"));
    }
    if (P.bComplete) return C == 1 ? TEXT("Paradox Chronicle complete. Permanent +20% Paradox scan gain is active on wild victories. All seventeen crests and eighteen regions remain yours.") :
        TEXT("Ghostline closed. Permanent +20% Shiny scan gain is active on wild victories. Mara's access is revoked; all thirty Access Proofs remain yours.");
    for (const auto& N : Content(C).NPCs)
    {
        if (!CanEnter(C, P, N.MapId) || !Visible(C, P, N) || Completed(P, N.Id) || !Ready(P, N)) continue;
        const auto* M = Map(C, N.MapId);
        if (N.Role == EDigimonRelayRole::Quest)
        {
            if (!P.AcceptedQuests.Contains(N.Id)) return FString::Printf(TEXT("Speak to %s in %s to accept %s."), *N.Name, *M->Name, *N.QuestTitle);
            if (QuestCount(C, P, N.Id) >= N.QuestTarget) return FString::Printf(TEXT("Return to %s in %s and submit your completed report."), *N.Name, *M->Name);
        }
        else if (IsBattle(N.Role)) return FString::Printf(TEXT("Challenge %s (Lv. %d) in %s. Review your partners, techniques and supplies before beginning."), *N.Name, N.Level, *M->Name);
    }
    const auto* M = Map(C, P.MapId);
    return M ? M->Objective : Content(C).Introduction;
}
bool Reconcile(int32 C, FDigimonRelayProgress& P)
{
    bool Changed = false;
    // Preserve only achievements belonging to this campaign; completion is
    // derived from a recorded final victory, never an unlocked map or badge count.
    TSet<FName> Seen;
    const int32 Before = P.DefeatedTamers.Num();
    P.DefeatedTamers.RemoveAll([&](FName Id) { const auto* N = NPC(C, Id); if (!N || !IsBattle(N->Role) || Seen.Contains(Id)) return true; Seen.Add(Id); return false; });
    Changed |= Before != P.DefeatedTamers.Num();
    for (const auto& N : Content(C).NPCs)
    {
        if (Completed(P, N.Id) && !N.BadgeId.IsNone() && !P.Badges.Contains(N.BadgeId)) { P.Badges.Add(N.BadgeId); Changed = true; }
        if (N.bRevealOnComplete && Completed(P, N.Id) && !Revealed(P)) { P.CompletedObjectives.Add(RevealMarker); Changed = true; }
    }
    if (P.DefeatedTamers.Contains(Content(C).FinalId))
    {
        if (!P.bComplete) { P.bComplete = true; Changed = true; }
        if (!P.bEverChampion) { P.bEverChampion = true; Changed = true; }
    }
    if (C == 0 && P.bEverChampion && !P.bFirewallScanMastery) { P.bFirewallScanMastery = true; Changed = true; }
    if (C == 1 && P.bComplete && !P.bParadoxScanMastery) { P.bParadoxScanMastery = true; Changed = true; }
    if (C == 2 && P.bComplete && !P.bShinyScanMastery) { P.bShinyScanMastery = true; Changed = true; }
    int32 Unlocked = 1;
    for (const auto& M : Content(C).Maps) if (CanEnter(C, P, M.MapId)) Unlocked = FMath::Max(Unlocked, M.MapId);
    if (P.UnlockedMapId != Unlocked) { P.UnlockedMapId = Unlocked; Changed = true; }
    if (!CanEnter(C, P, P.MapId)) { P.MapId = 1; P.bHasPosition = false; Changed = true; }
    if (P.ReturnMapId < 1) { P.ReturnMapId = 1; P.bHasReturnLocation = false; Changed = true; }
    if (P.ChallengerIndex < 0) { P.ChallengerIndex = 0; Changed = true; }
    if (P.Version != 3) { P.Version = 3; Changed = true; }
    return Changed;
}
bool Settle(int32 C, FDigimonRelayProgress& P, FGuid BattleId, FName Id, bool Victory, bool& FirstClear)
{
    FirstClear = false;
    const auto* N = NPC(C, Id);
    FString Error;
    if (!BattleId.IsValid() || P.PendingBattleId != BattleId || P.PendingNPCId != Id || P.LastSettledBattleId == BattleId || !N || !CanChallenge(C, P, *N, Error)) return false;
    if (Victory)
    {
        FirstClear = !Completed(P, Id);
        P.DefeatedTamers.AddUnique(Id);
        if (!N->BadgeId.IsNone()) P.Badges.AddUnique(N->BadgeId);
        if (N->bHackedAfterVictory) P.CompletedObjectives.AddUnique(HackMarker(Id));
        if (N->Role == EDigimonRelayRole::FinalBoss) P.bComplete = true;
    }
    if (N->Role == EDigimonRelayRole::Champion || N->Role == EDigimonRelayRole::Challenger)
    {
        for (FName HolderId : Content(C).Challengers)
            P.CompletedObjectives.RemoveAll([&](FName Saved) { return Saved == HolderMarker(HolderId); });
        if (!Victory && N->Role == EDigimonRelayRole::Challenger) P.CompletedObjectives.AddUnique(HolderMarker(Id));
        DigimonVenomNXTRelayCore::TitleResult(P, Victory, N->Role == EDigimonRelayRole::Champion);
    }
    P.LastSettledBattleId = BattleId; P.PendingBattleId.Invalidate(); P.PendingNPCId = NAME_None; P.BattleCheckpointJson.Reset();
    Reconcile(C, P);
    return true;
}
}
