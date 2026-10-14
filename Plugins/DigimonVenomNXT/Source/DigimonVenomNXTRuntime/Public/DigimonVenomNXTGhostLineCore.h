#pragma once
#include <array>

/** Authoritative GhostLine rules shared by the Unreal adapter and portable tests.
 * Field numbers are 1..30; campaign map numbers are field+1 (hub is map1).
 * A proof alone is never evidence of a case report or a permitted battle.
 */
namespace DigimonVenomNXTGhostLineCore
{
constexpr int CaseCount = 30;
constexpr int MapCount = 31;
constexpr int RevealField = 26;
constexpr int LastCompromisedField = 23;
struct Progress
{
    std::array<bool, CaseCount> Accepted{};
    std::array<bool, CaseCount> Reported{};
    std::array<bool, CaseCount> Won{};
    std::array<bool, CaseCount> Proof{};
    std::array<bool, CaseCount> Hacked{};
    bool Complete = false;
    bool Mastery = false;
};
inline bool ValidField(int Field) { return Field >= 1 && Field <= CaseCount; }
inline bool HasReport(const Progress& P, int Field)
{
    if (!ValidField(Field)) return false;
    const int I = Field - 1;
    return P.Accepted[I] && P.Reported[I] && P.Proof[I] && (Field == CaseCount || P.Won[I]);
}
inline bool Prefix(const Progress& P, int Count)
{
    if (Count < 0 || Count > CaseCount) return false;
    for (int F = 1; F <= Count; ++F) if (!HasReport(P, F)) return false;
    return true;
}
inline bool CanEnter(const Progress& P, int MapId)
{
    return MapId >= 1 && MapId <= MapCount && Prefix(P, MapId > 1 ? MapId - 2 : 0);
}
inline bool IsRevealed(const Progress& P) { return Prefix(P, RevealField); }
inline bool CanChallenge(const Progress& P, int Field)
{
    if (!ValidField(Field) || P.Complete || !CanEnter(P, Field + 1) || P.Won[Field - 1]) return false;
    return Field == CaseCount ? IsRevealed(P) && Prefix(P, CaseCount) : P.Accepted[Field - 1];
}
inline bool CanReport(const Progress& P, int Field)
{
    if (!ValidField(Field) || !CanEnter(P, Field + 1)) return false;
    const int I = Field - 1;
    return P.Accepted[I] && !P.Reported[I] && (Field == CaseCount ? Prefix(P, CaseCount - 1) : P.Won[I]);
}
enum class QuestResult { Rejected, Accepted, Reported };
inline QuestResult AdvanceQuest(Progress& P, int Field)
{
    if (!ValidField(Field) || P.Complete || !CanEnter(P, Field + 1) || P.Reported[Field - 1]) return QuestResult::Rejected;
    const int I = Field - 1;
    if (!P.Accepted[I]) { P.Accepted[I] = true; return QuestResult::Accepted; }
    if (!CanReport(P, Field)) return QuestResult::Rejected;
    P.Reported[I] = true;
    P.Proof[I] = true;
    return QuestResult::Reported;
}
/** Caller checks the durable server-authored receipt before invoking this. */
inline bool Settle(Progress& P, int Field, bool Victory, bool& FirstClear)
{
    FirstClear = false;
    if (!CanChallenge(P, Field)) return false;
    if (!Victory) return true;
    FirstClear = true;
    P.Won[Field - 1] = true;
    if (Field <= LastCompromisedField) P.Hacked[Field - 1] = true;
    if (Field == CaseCount) { P.Complete = true; P.Mastery = true; }
    return true;
}
inline bool ReceiptMatches(bool Valid, bool PendingMatches, bool NPCMatches, bool AlreadySettled)
{
    return Valid && PendingMatches && NPCMatches && !AlreadySettled;
}
inline bool CompanionVisible(const Progress& P, bool HideOnReveal, bool RequiresReveal)
{
    if (P.Complete) return false;
    const bool Revealed = IsRevealed(P);
    return !(HideOnReveal && Revealed) && !(RequiresReveal && !Revealed);
}
/** Rebuild redundant facts, never from travel, badge counts or another campaign.
 * Completion/mastery are durable. Pending server decisions live in the adapter
 * and must never be cleared or modified by this reconciliation.
 */
inline void Reconcile(Progress& P)
{
    if (P.Complete || P.Won[CaseCount - 1])
    {
        P.Complete = true; P.Mastery = true;
        for (int I = 0; I < CaseCount; ++I)
        {
            P.Accepted[I] = P.Reported[I] = P.Won[I] = P.Proof[I] = true;
            P.Hacked[I] = I < LastCompromisedField;
        }
        return;
    }
    bool PreviousComplete = true;
    for (int I = 0; I < CaseCount; ++I)
    {
        if (!PreviousComplete)
        {
            P.Accepted[I] = P.Reported[I] = P.Won[I] = P.Proof[I] = P.Hacked[I] = false;
            continue;
        }
        // A recorded first victory is stronger evidence than a missing acceptance.
        if (P.Won[I]) P.Accepted[I] = true;
        P.Reported[I] = P.Reported[I] && P.Accepted[I] && (I == CaseCount - 1 || P.Won[I]);
        P.Proof[I] = P.Reported[I];
        P.Hacked[I] = I < LastCompromisedField && P.Won[I];
        PreviousComplete = P.Reported[I];
    }
}
enum class ObjectiveStage { AcceptCase, WitnessTrial, ConfirmReport, FinalBattle, Complete };
inline ObjectiveStage Stage(const Progress& P, int& Field)
{
    if (P.Complete) { Field = CaseCount; return ObjectiveStage::Complete; }
    for (Field = 1; Field <= CaseCount; ++Field)
    {
        const int I = Field - 1;
        if (HasReport(P, Field)) continue;
        if (!P.Accepted[I]) return ObjectiveStage::AcceptCase;
        if (Field < CaseCount && !P.Won[I]) return ObjectiveStage::WitnessTrial;
        return ObjectiveStage::ConfirmReport;
    }
    Field = CaseCount;
    return ObjectiveStage::FinalBattle;
}
}
