#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTAtomicFile.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTRankedRules.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogDigimonRanked, Log, All);

namespace
{
    bool WriteRankedAtomically(const FString& Path, const FDigimonRankedSaveData& Data)
    {
        FString Json;
        if (!FJsonObjectConverter::UStructToJsonObjectString(Data, Json)) return false;
        IFileManager& Files = IFileManager::Get();
        if (!Files.MakeDirectory(*FPaths::GetPath(Path), true)) return false;
        const FString Temporary = Path + TEXT(".tmp");
        if (!FFileHelper::SaveStringToFile(Json, *Temporary, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)) return false;
        // Same-directory rename: a failed temporary write never truncates the previous save.
        if (!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary))
        {
            UE_LOG(LogDigimonRanked, Error, TEXT("Could not commit ranked data to %s; existing save retained."), *Path);
            return false;
        }
        return true;
    }

    bool LadderBefore(const FDigimonRankedLadderEntry& A, const FDigimonRankedLadderEntry& B)
    {
        if (A.Rating != B.Rating) return A.Rating > B.Rating;
        if (A.Wins != B.Wins) return A.Wins > B.Wins;
        if (A.Losses != B.Losses) return A.Losses < B.Losses;
        return A.AccountId < B.AccountId;
    }

    FString SeasonIdForStart(int64 Start, int32 Days)
    {
        return FString::Printf(TEXT("UTC-%s-D%d"), *FDateTime::FromUnixTimestamp(Start).ToString(TEXT("%Y-%m-%d")), Days);
    }

    TArray<FDigimonOwnedPartner> FullHealthCopy(const TArray<FDigimonOwnedPartner>& Team)
    {
        TArray<FDigimonOwnedPartner> Copy = Team;
        for (FDigimonOwnedPartner& Partner : Copy) { Partner.CurrentHP = MAX_int32; Partner.CurrentSP = MAX_int32; }
        return Copy;
    }
}

void UDigimonVenomNXTRankedSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // GameInstance subsystems also exist on clients and menus. Load lazily on a real server world.
}

void UDigimonVenomNXTRankedSubsystem::Deinitialize()
{
    if (bLoaded && !bLoadFailed && IsAuthoritativeWorld()) Save();
    Super::Deinitialize();
}

bool UDigimonVenomNXTRankedSubsystem::IsAuthoritativeWorld() const
{
    return GetWorld() && GetWorld()->IsGameWorld() && GetWorld()->GetNetMode() != NM_Client && GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() != nullptr;
}

FString UDigimonVenomNXTRankedSubsystem::SavePath() const
{
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Ranked.json"));
}

FString UDigimonVenomNXTRankedSubsystem::ArchivePath(const FString& SeasonId) const
{
    FString Safe = SeasonId;
    Safe.ReplaceInline(TEXT("/"), TEXT("_")); Safe.ReplaceInline(TEXT("\\"), TEXT("_")); Safe.ReplaceInline(TEXT(".."), TEXT("_"));
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("RankedArchive"), Safe + TEXT(".json"));
}

EDigimonRankedGrade UDigimonVenomNXTRankedSubsystem::GetGradeForRating(int32 Rating)
{
    return static_cast<EDigimonRankedGrade>(DigimonVenomNXTRankedRules::GradeIndex(Rating,
        DigimonVenomNXTRankedRules::ValidThresholds(GetDefault<UDigimonVenomNXTSettings>()->RankedGradeRatingThresholds)));
}

FString UDigimonVenomNXTRankedSubsystem::GetGradeLabel(EDigimonRankedGrade Grade)
{
    static const TCHAR* Labels[] = {TEXT("Bronze"), TEXT("Silver"), TEXT("Gold"), TEXT("Platinum"), TEXT("Diamond"), TEXT("Master")};
    return Labels[FMath::Clamp(static_cast<int32>(Grade), 0, 5)];
}

bool UDigimonVenomNXTRankedSubsystem::Load()
{
    if (!IsAuthoritativeWorld() || bLoadFailed) return false;
    if (bLoaded) return true;
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    const int32 Days = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->RankedSeasonDays, 1, 30);
    if (!IFileManager::Get().FileExists(*SavePath()))
    {
        RankedData = FDigimonRankedSaveData();
        RankedData.SeasonStartsUnix = DigimonVenomNXTRankedRules::SeasonStart(Now, Days);
        RankedData.SeasonEndsUnix = RankedData.SeasonStartsUnix + static_cast<int64>(Days) * 86400;
        RankedData.SeasonId = SeasonIdForStart(RankedData.SeasonStartsUnix, Days);
        bLoaded = true;
        if (Save()) return true;
        bLoaded = false;
        return false;
    }
    FString Json;
    FDigimonRankedSaveData Loaded;
    if (!FFileHelper::LoadFileToString(Json, *SavePath()) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Loaded, 0, 0) || Loaded.SeasonId.IsEmpty())
    {
        bLoadFailed = true;
        UE_LOG(LogDigimonRanked, Error, TEXT("Ranked.json could not be read. Ranked is unavailable; the original file has NOT been overwritten."));
        return false;
    }
    TSet<FString> AccountIds;
    for (FDigimonRankedLadderEntry& Entry : Loaded.Entries)
    {
        if (Entry.AccountId.IsEmpty() || AccountIds.Contains(Entry.AccountId))
        {
            bLoadFailed = true;
            UE_LOG(LogDigimonRanked, Error, TEXT("Ranked save has an empty/duplicate account ID. Original file preserved."));
            return false;
        }
        AccountIds.Add(Entry.AccountId);
        Entry.Rating = FMath::Clamp(Entry.Rating, 0, 1000000);
        Entry.AchievedGrade = FMath::Clamp(Entry.AchievedGrade, 0, 5);
        Entry.SeasonAttacks = FMath::Max(0, Entry.SeasonAttacks);
        Entry.RivalRatingOffset = FMath::Clamp(Entry.RivalRatingOffset, -150, 150);
        Entry.Wins = FMath::Max(0, Entry.Wins); Entry.Losses = FMath::Max(0, Entry.Losses); Entry.Draws = FMath::Max(0, Entry.Draws);
    }
    // Upgrade the old Monday-based save without resetting anyone's wins from a stale profile.
    if (Loaded.SeasonEndsUnix <= 0)
    {
        FDateTime LegacyStart;
        if (Loaded.SeasonId.StartsWith(TEXT("UTC-")) &&
            FDateTime::ParseIso8601(*(Loaded.SeasonId.Mid(4, 10) + TEXT("T00:00:00Z")), LegacyStart))
            Loaded.SeasonStartsUnix = LegacyStart.ToUnixTimestamp();
        else Loaded.SeasonStartsUnix = DigimonVenomNXTRankedRules::SeasonStart(Now, Days);
        Loaded.SeasonEndsUnix = Loaded.SeasonStartsUnix + static_cast<int64>(Days) * 86400;
    }
    for (const TPair<FString, int32>& Legacy : Loaded.PendingRubyRewards)
    {
        if (Legacy.Value <= 0 || Legacy.Key.StartsWith(TEXT("AI:"))) continue;
        FDigimonRankedReward Reward;
        Reward.AccountId = Legacy.Key; Reward.SeasonId = Loaded.SeasonId;
        Reward.RewardId = TEXT("legacy:") + Loaded.SeasonId + TEXT(":") + Legacy.Key;
        Reward.DigiRubies = Legacy.Value;
        if (!Loaded.PendingRewards.ContainsByPredicate([&](const FDigimonRankedReward& R) { return R.RewardId == Reward.RewardId; }))
            Loaded.PendingRewards.Add(Reward);
    }
    Loaded.PendingRubyRewards.Reset();
    Loaded.SchemaVersion = 2;
    RankedData = MoveTemp(Loaded);
    bLoaded = true;
    return true;
}

bool UDigimonVenomNXTRankedSubsystem::Save(bool bExplicitAdminSave)
{
    if (!bLoaded || bLoadFailed || !IsAuthoritativeWorld()) return false;
    if (!bExplicitAdminSave && !GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves)
    { bDirty = true; return true; }
    for (const auto& Archive : DeferredArchives)
        if (!WriteRankedAtomically(ArchivePath(Archive.Key), Archive.Value)) return false;
    // Rival parties are already durable in AIRivals.json; rebuild their live snapshots after load.
    // Excluding them keeps high-frequency human result commits small even with 1,000 AI rivals.
    FDigimonRankedSaveData Persisted = RankedData;
    for (FDigimonRankedLadderEntry& Entry : Persisted.Entries)
        if (Entry.bAIRival) { Entry.DefenderTeam.Reset(); Entry.LastBattleLog.Reset(); Entry.LastOpponentTeam.Reset(); }
    if (!WriteRankedAtomically(SavePath(), Persisted)) return false;
    LastSavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    bDirty = false;
    DeferredArchives.Reset();
    return true;
}

bool UDigimonVenomNXTRankedSubsystem::SaveForHostConsole()
{
    UGameInstance* Instance = GetGameInstance();
    UDigimonVenomNXTServerConsoleSubsystem* Console = Instance ? Instance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    if (!Console || !Console->CanAccess(Instance->GetFirstLocalPlayerController())) return false;
    if (!Load()) return false;
    return Save(true);
}

int32 UDigimonVenomNXTRankedSubsystem::CalculateRubyReward(const FDigimonRankedLadderEntry& Entry, int32 Placement) const
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    if (Entry.bAIRival || !DigimonVenomNXTRankedRulesCore::RewardEligible(Entry.SeasonAttacks, Settings->RankedMinimumRewardMatches)) return 0;
    const int32 Grade = FMath::Clamp(Entry.AchievedGrade, 0, 5);
    int32 Reward = Settings->RankedGradeDigiRubies.IsValidIndex(Grade) ? FMath::Clamp(Settings->RankedGradeDigiRubies[Grade], 0, 1000000) : 0;
    const int32 Bracket = DigimonVenomNXTRankedRulesCore::PlacementBracket(Placement);
    if (Settings->RankedPlacementDigiRubies.IsValidIndex(Bracket)) Reward += FMath::Clamp(Settings->RankedPlacementDigiRubies[Bracket], 0, 1000000);
    return Reward;
}

void UDigimonVenomNXTRankedSubsystem::AwardSeasonRewards()
{
    TArray<FDigimonRankedLadderEntry> Standings;
    for (const FDigimonRankedLadderEntry& Entry : RankedData.Entries)
        if (static_cast<int64>(Entry.Wins) + Entry.Losses + Entry.Draws > 0) Standings.Add(Entry);
    Standings.Sort(LadderBefore);
    for (int32 I = 0; I < Standings.Num(); ++I)
    {
        const int32 Amount = CalculateRubyReward(Standings[I], I + 1);
        if (Amount <= 0) continue;
        FDigimonRankedReward Reward;
        Reward.AccountId = Standings[I].AccountId; Reward.SeasonId = RankedData.SeasonId; Reward.Placement = I + 1;
        Reward.RewardId = RankedData.SeasonId + TEXT(":") + Reward.AccountId;
        Reward.DigiRubies = Amount;
        if (!RankedData.PendingRewards.ContainsByPredicate([&](const FDigimonRankedReward& R) { return R.RewardId == Reward.RewardId; }))
            RankedData.PendingRewards.Add(Reward);
    }
}

bool UDigimonVenomNXTRankedSubsystem::RollSeasonIfNeeded()
{
    if (!IsAuthoritativeWorld() || (!bLoaded && !Load()) || bLoadFailed) return false;
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    if (Now < RankedData.SeasonEndsUnix) return true;
    const FDigimonRankedSaveData Before = RankedData;
    AwardSeasonRewards();
    // Archive before mutation. Retrying after a crash uses identical season-scoped reward IDs.
    if (!GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves)
        DeferredArchives.Add(RankedData.SeasonId, RankedData);
    else if (!WriteRankedAtomically(ArchivePath(RankedData.SeasonId), RankedData))
    {
        RankedData = Before;
        return false;
    }
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 Floor = DigimonVenomNXTRankedRules::ValidThresholds(Settings->RankedGradeRatingThresholds)[0];
    for (FDigimonRankedLadderEntry& Entry : RankedData.Entries)
    {
        Entry.Wins = 0; Entry.Losses = 0; Entry.Draws = 0; Entry.AchievedGrade = 0; Entry.SeasonAttacks = 0;
        if (!Entry.bAIRival) Entry.Rating = Floor + FMath::RoundToInt(FMath::Max(0, Entry.Rating - Floor) * FMath::Clamp(Settings->RankedSeasonRatingRetention, 0.0f, 1.0f));
    }
    const int32 Days = FMath::Clamp(Settings->RankedSeasonDays, 1, 30);
    // No rewards for skipped empty seasons while the server was offline.
    RankedData.SeasonStartsUnix = DigimonVenomNXTRankedRules::SeasonStart(Now, Days);
    RankedData.SeasonEndsUnix = RankedData.SeasonStartsUnix + static_cast<int64>(Days) * 86400;
    RankedData.SeasonId = SeasonIdForStart(RankedData.SeasonStartsUnix, Days);
    if (!Save()) { RankedData = Before; return false; }
    return true;
}

FDigimonRankedLadderEntry* UDigimonVenomNXTRankedSubsystem::FindEntry(const FString& AccountId)
{
    return RankedData.Entries.FindByPredicate([&](const FDigimonRankedLadderEntry& E) { return E.AccountId == AccountId; });
}

FDigimonRankedLadderEntry& UDigimonVenomNXTRankedSubsystem::FindOrAddEntry(ADigimonVenomNXTPlayerState* PlayerState)
{
    if (FDigimonRankedLadderEntry* Existing = FindEntry(PlayerState->Profile.AccountId))
    {
        Existing->Username = PlayerState->Profile.Username;
        Existing->CareerWins = FMath::Max(Existing->CareerWins, PlayerState->Profile.Ranked.CareerWins);
        Existing->CareerLosses = FMath::Max(Existing->CareerLosses, PlayerState->Profile.Ranked.CareerLosses);
        Existing->CareerDraws = FMath::Max(Existing->CareerDraws, PlayerState->Profile.Ranked.CareerDraws);
        // The ledger is authoritative. Never import stale weekly wins/rating from the profile.
        return *Existing;
    }
    FDigimonRankedLadderEntry Entry;
    Entry.AccountId = PlayerState->Profile.AccountId;
    Entry.Username = PlayerState->Profile.Username;
    Entry.Rating = DigimonVenomNXTRankedRules::ValidThresholds(GetDefault<UDigimonVenomNXTSettings>()->RankedGradeRatingThresholds)[0];
    Entry.CareerWins = FMath::Max(0, PlayerState->Profile.Ranked.CareerWins);
    Entry.CareerLosses = FMath::Max(0, PlayerState->Profile.Ranked.CareerLosses);
    Entry.CareerDraws = FMath::Max(0, PlayerState->Profile.Ranked.CareerDraws);
    RefreshEnergy(Entry, FDateTime::UtcNow().ToUnixTimestamp());
    return RankedData.Entries.Add_GetRef(Entry);
}

int32 UDigimonVenomNXTRankedSubsystem::TeamPower(const TArray<FDigimonOwnedPartner>& Team) const
{
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    int64 Total = 0;
    for (const FDigimonOwnedPartner& Partner : Team)
    {
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        Total += static_cast<int64>(Unit.Stats.MaxHP) + Unit.Stats.MaxSP +
            6LL * (static_cast<int64>(Unit.Stats.Attack) + Unit.Stats.Defense + Unit.Stats.Spirit + Unit.Stats.Speed);
    }
    return static_cast<int32>(FMath::Clamp<int64>(Total, 1, MAX_int32));
}

void UDigimonVenomNXTRankedSubsystem::RefreshEnergy(FDigimonRankedLadderEntry& Entry, int64 Now) const
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 Maximum = FMath::Clamp(Settings->RankedMaxEnergy, 1, 999);
    if (!Entry.bEnergyInitialized)
    {
        Entry.bEnergyInitialized = true; Entry.Energy = Maximum; Entry.EnergyUpdatedUnix = Now;
    }
    DigimonVenomNXTRankedRules::Recharge(Entry.Energy, Entry.EnergyUpdatedUnix, Now, Maximum, Settings->RankedEnergyRechargeSeconds);
}

void UDigimonVenomNXTRankedSubsystem::SyncProfile(ADigimonVenomNXTPlayerState* PlayerState, FDigimonRankedLadderEntry& Entry) const
{
    RefreshEnergy(Entry, FDateTime::UtcNow().ToUnixTimestamp());
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    FDigimonRankedCareer& Career = PlayerState->Profile.Ranked;
    Career.Rating = Entry.Rating; Career.Grade = static_cast<EDigimonRankedGrade>(FMath::Clamp(Entry.AchievedGrade, 0, 5));
    Career.WeeklyWins = Entry.Wins; Career.WeeklyLosses = Entry.Losses; Career.WeeklyDraws = Entry.Draws; Career.WeeklyAttacks = Entry.SeasonAttacks;
    Career.CareerWins = Entry.CareerWins; Career.CareerLosses = Entry.CareerLosses; Career.CareerDraws = Entry.CareerDraws;
    Career.WeeklySeasonId = RankedData.SeasonId; Career.SeasonEndsUnix = RankedData.SeasonEndsUnix;
    Career.ServerUnix = FDateTime::UtcNow().ToUnixTimestamp();
    Career.RewardPlacement = 0;
    const int32 RequiredMatches = FMath::Max(1, Settings->RankedMinimumRewardMatches);
    if (DigimonVenomNXTRankedRulesCore::RewardEligible(Entry.SeasonAttacks, RequiredMatches))
    {
        Career.RewardPlacement = 1;
        for (const FDigimonRankedLadderEntry& Other : RankedData.Entries)
            if (Other.AccountId != Entry.AccountId &&
                static_cast<int64>(Other.Wins) + Other.Losses + Other.Draws > 0 && LadderBefore(Other, Entry)) ++Career.RewardPlacement;
    }
    Career.Energy = Entry.Energy; Career.EnergyCap = FMath::Clamp(Settings->RankedMaxEnergy, 1, 999);
    Career.EnergyRechargeSeconds = FMath::Clamp(Settings->RankedEnergyRechargeSeconds, 1, 86400);
    Career.EnergyUpdatedUnix = Entry.EnergyUpdatedUnix;
    Career.NextEnergyUnix = Entry.Energy < Career.EnergyCap ? Entry.EnergyUpdatedUnix + Career.EnergyRechargeSeconds : 0;
    Career.GradeThresholds = DigimonVenomNXTRankedRules::ValidThresholds(Settings->RankedGradeRatingThresholds);
    Career.RewardGradeDigiRubies.SetNum(6);
    for (int32 I = 0; I < 6; ++I) Career.RewardGradeDigiRubies[I] = Settings->RankedGradeDigiRubies.IsValidIndex(I) ? FMath::Clamp(Settings->RankedGradeDigiRubies[I], 0, 1000000) : 0;
    Career.RewardPlacementDigiRubies.SetNum(7);
    for (int32 I = 0; I < 7; ++I) Career.RewardPlacementDigiRubies[I] = Settings->RankedPlacementDigiRubies.IsValidIndex(I) ? FMath::Clamp(Settings->RankedPlacementDigiRubies[I], 0, 1000000) : 0;
    Career.MinimumRewardMatches = FMath::Max(1, Settings->RankedMinimumRewardMatches);
    Career.LastOpponent = Entry.LastOpponent; Career.LastResult = Entry.LastResult;
    Career.LastRatingDelta = Entry.LastRatingDelta; Career.LastBattleTurns = Entry.LastBattleTurns;
    Career.LastBattleUnix = Entry.LastBattleUnix; Career.LastBattleLog = Entry.LastBattleLog;
    Career.LastOpponentTeam = Entry.LastOpponentTeam;
    Career.DefenderTeam = Entry.DefenderTeam;
    Career.DefenderLineup.Reset();
    for (const FDigimonOwnedPartner& Partner : Entry.DefenderTeam) Career.DefenderLineup.Add(Partner.InstanceId);
    const TWeakObjectPtr<ADigimonVenomNXTBattleActor>* Presentation=ActivePresentations.Find(Entry.AccountId);
    const FDigimonRankedCareer* Before=VisibleCareersBeforePresentation.Find(Entry.AccountId);
    if (Presentation && Presentation->IsValid() && !Presentation->Get()->State.bFinished && Before)
    {
        Career.Rating=Before->Rating; Career.Grade=Before->Grade;
        Career.WeeklyWins=Before->WeeklyWins; Career.WeeklyLosses=Before->WeeklyLosses; Career.WeeklyDraws=Before->WeeklyDraws; Career.WeeklyAttacks=Before->WeeklyAttacks;
        Career.CareerWins=Before->CareerWins; Career.CareerLosses=Before->CareerLosses; Career.CareerDraws=Before->CareerDraws;
        Career.RewardPlacement=Before->RewardPlacement;
        Career.LastOpponent=Before->LastOpponent; Career.LastResult=Before->LastResult;
        Career.LastRatingDelta=Before->LastRatingDelta; Career.LastBattleTurns=Before->LastBattleTurns;
        Career.LastBattleUnix=Before->LastBattleUnix; Career.LastBattleLog=Before->LastBattleLog;
        Career.LastOpponentTeam=Before->LastOpponentTeam;
    }
    PlayerState->MarkProfileChanged();
}

void UDigimonVenomNXTRankedSubsystem::RefreshRivalEntries(bool bForce)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    if (!Settings->bRankedAllowAIRivals)
    {
        RankedData.Entries.RemoveAll([](const FDigimonRankedLadderEntry& E) { return E.bAIRival; });
        return;
    }
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    if (!bForce && LastRivalRefreshUnix > 0 && Now - LastRivalRefreshUnix < 30) return;
    UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>();
    if (!Rivals) return;
    TArray<FDigimonAIRivalRecord> Records = Rivals->GetRivalBattleSnapshots();
    if (Records.Num() == 0) return;
    LastRivalRefreshUnix = Now;
    bDirty = true;
    const int32 PartyLimit = FMath::Clamp(Settings->MaxPartySize, 1, 12);
    TSet<FString> ActiveIds;
    for (const FDigimonAIRivalRecord& Rival : Records)
    {
        if (Rival.Partners.Num() == 0 || Rival.RivalId.IsEmpty()) continue;
        const FString Id = TEXT("AI:") + Rival.RivalId;
        ActiveIds.Add(Id);
        FDigimonRankedLadderEntry* Entry = FindEntry(Id);
        if (!Entry)
        {
            FDigimonRankedLadderEntry NewEntry;
            NewEntry.AccountId = Id; NewEntry.bAIRival = true; NewEntry.RivalId = Rival.RivalId;
            RankedData.Entries.Add(NewEntry); Entry = &RankedData.Entries.Last();
        }
        Entry->Username = Rival.DisplayName;
        Entry->DefenderTeam = Rival.Partners;
        if (Entry->DefenderTeam.Num() > PartyLimit) Entry->DefenderTeam.SetNum(PartyLimit);
        Entry->TeamPower = TeamPower(Entry->DefenderTeam);
        RefreshEnergy(*Entry, Now);
    }
    RankedData.Entries.RemoveAll([&](const FDigimonRankedLadderEntry& E) { return E.bAIRival && !ActiveIds.Contains(E.AccountId); });
    TArray<FDigimonRankedLadderEntry*> ByStrength;
    for (FDigimonRankedLadderEntry& Entry : RankedData.Entries) if (Entry.bAIRival) ByStrength.Add(&Entry);
    ByStrength.Sort([](const FDigimonRankedLadderEntry& A, const FDigimonRankedLadderEntry& B)
    {
        if (A.TeamPower != B.TeamPower) return A.TeamPower < B.TeamPower;
        return A.AccountId < B.AccountId;
    });
    const TArray<int32> Thresholds = DigimonVenomNXTRankedRules::ValidThresholds(Settings->RankedGradeRatingThresholds);
    for (int32 I = 0; I < ByStrength.Num(); ++I)
    {
        // Difficulty follows the actual persistent roster: strongest rivals occupy Master.
        const double BandPosition = ByStrength.Num() > 1 ? 5.999 * I / (ByStrength.Num() - 1) : 0.0;
        const int32 Grade = FMath::Clamp(FMath::FloorToInt(BandPosition), 0, 5);
        const int32 Width = Grade < 5 ? Thresholds[Grade + 1] - Thresholds[Grade] : 250;
        const int32 Anchor = Thresholds[Grade] + FMath::FloorToInt((BandPosition - Grade) * Width);
        ByStrength[I]->Rating = FMath::Clamp(Anchor + ByStrength[I]->RivalRatingOffset, Thresholds[Grade], Thresholds[Grade] + Width - 1);
        ByStrength[I]->AchievedGrade = Grade;
    }
}

bool UDigimonVenomNXTRankedSubsystem::SaveDefenderLineup(ADigimonVenomNXTPlayerState* PlayerState, FString& OutMessage)
{
    if (!PlayerState || !PlayerState->HasAuthority() || PlayerState->Profile.AccountId.IsEmpty() || !RollSeasonIfNeeded())
    { OutMessage = TEXT("Ranked service is unavailable. Please try again after the host checks its saved data."); return false; }
    TArray<FDigimonOwnedPartner> Team;
    const int32 Limit = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize, 1, 12);
    for (const FGuid& Id : PlayerState->Profile.Party)
    {
        FDigimonOwnedPartner Partner;
        if (PlayerState->GetPartner(Id, Partner) && !Team.ContainsByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; })) Team.Add(Partner);
        if (Team.Num() >= Limit) break;
    }
    if (Team.Num() == 0) { OutMessage = TEXT("Put at least one Digimon in your party before saving a defense team."); return false; }
    const FDigimonRankedSaveData Before = RankedData;
    FDigimonRankedLadderEntry& Entry = FindOrAddEntry(PlayerState);
    Entry.DefenderTeam = Team; Entry.TeamPower = TeamPower(Team);
    if (!Save()) { RankedData = Before; OutMessage = TEXT("Defense could not be saved. Your previous lineup is unchanged."); return false; }
    SyncProfile(PlayerState, Entry);
    OutMessage = FString::Printf(TEXT("Defense saved: %d Digimon. Challengers fight this full-health snapshot while you are away."), Team.Num());
    return true;
}

bool UDigimonVenomNXTRankedSubsystem::RunQuickMatch(ADigimonVenomNXTPlayerState* Challenger, FString& OutMessage)
{
    ADigimonVenomNXTBattleActor* Battle=nullptr;
    if (!StartRankedMatch(Challenger,Battle,OutMessage)) return false;
    if (ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(Challenger->GetOwner())) PC->SetCurrentBattleServer(Battle);
    return true;
}

bool UDigimonVenomNXTRankedSubsystem::StartRankedMatch(ADigimonVenomNXTPlayerState* Challenger, ADigimonVenomNXTBattleActor*& OutBattle, FString& OutMessage)
{
    OutBattle=nullptr;
    if (!Challenger || !Challenger->HasAuthority() || Challenger->Profile.AccountId.IsEmpty() || !RollSeasonIfNeeded())
    { OutMessage = TEXT("Ranked service is unavailable. Please try again after the host checks its saved data."); return false; }
    ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(Challenger->GetOwner());
    if (!PC || PC->GetPlayerState<ADigimonVenomNXTPlayerState>()!=Challenger)
    { OutMessage=TEXT("A connected tamer is required to enter ranked battles."); return false; }
    const FString AccountId=Challenger->Profile.AccountId;
    if (const TWeakObjectPtr<ADigimonVenomNXTBattleActor>* Existing=ActivePresentations.Find(AccountId))
    {
        if (ADigimonVenomNXTBattleActor* Battle=Existing->Get(); Battle && !Battle->State.bFinished)
        {
            Battle->RebindRankedPlayer(Challenger);
            OutBattle=Battle;
            OutMessage=TEXT("Resuming your current ranked battle.");
            return true; // Idempotent re-entry never spends energy twice.
        }
    }
    if (PC->CurrentBattle || Challenger->HasActiveBattle())
    { OutMessage=TEXT("Return from your current battle before entering the arena."); return false; }
    ActivePresentations.Remove(AccountId);
    VisibleCareersBeforePresentation.Remove(AccountId);
    RefreshRivalEntries();
    TArray<FDigimonOwnedPartner> Attackers;
    const int32 Limit = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize, 1, 12);
    for (const FGuid& Id : Challenger->Profile.Party)
    {
        FDigimonOwnedPartner Partner;
        if (Challenger->GetPartner(Id, Partner) && !Attackers.ContainsByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; })) Attackers.Add(Partner);
        if (Attackers.Num() >= Limit) break;
    }
    if (Attackers.Num() == 0) { OutMessage = TEXT("Your current party is empty. Add a Digimon before entering the arena."); return false; }
    FDigimonRankedLadderEntry& BeforeEntry=FindOrAddEntry(Challenger);
    SyncProfile(Challenger,BeforeEntry);
    const FDigimonRankedCareer VisibleCareer=Challenger->Profile.Ranked;
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner=PC;
    ADigimonVenomNXTBattleActor* Battle=GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(FVector::ZeroVector,FRotator::ZeroRotator,SpawnParameters);
    if (!Battle) { OutMessage=TEXT("The arena could not create its battle. No energy was spent."); return false; }
    if (!ResolveMatch(AccountId,Attackers,OutMessage,Challenger,Battle))
    {
        Battle->Destroy();
        if (FDigimonRankedLadderEntry* Entry=FindEntry(AccountId)) SyncProfile(Challenger,*Entry);
        return false;
    }
    const FString ResultSummary=OutMessage;
    ActivePresentations.Add(AccountId,Battle);
    VisibleCareersBeforePresentation.Add(AccountId,VisibleCareer);
    OutBattle=Battle;
    if (FDigimonRankedLadderEntry* Entry=FindEntry(AccountId)) SyncProfile(Challenger,*Entry);
    Battle->StartRankedPlayback(ResultSummary);
    OutMessage=TEXT("Opponent found. Entering the automatic ranked battle.");
    return true;
}

bool UDigimonVenomNXTRankedSubsystem::RunRivalQuickMatch(const FString& RivalId)
{
    if (!GetDefault<UDigimonVenomNXTSettings>()->bRankedAllowAIRivals || !RollSeasonIfNeeded()) return false;
    RefreshRivalEntries();
    const FString Id = TEXT("AI:") + RivalId;
    FDigimonRankedLadderEntry* Entry = FindEntry(Id);
    if (!Entry || !Entry->bAIRival) return false;
    UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>();
    FDigimonAIRivalRecord Current;
    if (!Rivals || !Rivals->GetRival(RivalId, Current) || Current.Partners.Num() == 0) return false;
    FString Ignored;
    return ResolveMatch(Id, Current.Partners, Ignored);
}

bool UDigimonVenomNXTRankedSubsystem::ResolveMatch(const FString& AccountId, const TArray<FDigimonOwnedPartner>& AttackingTeam, FString& OutMessage,
    ADigimonVenomNXTPlayerState* Challenger, ADigimonVenomNXTBattleActor* Playback)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    FDigimonRankedLadderEntry* Self = FindEntry(AccountId);
    if (!Self) return false;
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    RefreshEnergy(*Self, Now);
    if (Self->Energy <= 0)
    {
        const int64 Wait = FMath::Max<int64>(1, Self->EnergyUpdatedUnix + FMath::Clamp(Settings->RankedEnergyRechargeSeconds, 1, 86400) - Now);
        OutMessage = FString::Printf(TEXT("No arena energy. Your next energy recharges in %lld seconds."), Wait); return false;
    }
    // Reliable-RPC floods cannot resolve multiple matches on the same server frame.
    if (Self->LastBattleUnix > 0 && Now - Self->LastBattleUnix < 2)
    { OutMessage = TEXT("The arena is preparing your next opponent. Try again in a moment."); return false; }
    const int32 SelfGrade = Self->AchievedGrade;
    TArray<FDigimonRankedLadderEntry*> Candidates;
    for (FDigimonRankedLadderEntry& Entry : RankedData.Entries)
    {
        if (Entry.AccountId == AccountId || Entry.DefenderTeam.IsEmpty()) continue;
        if (Entry.bAIRival && !Settings->bRankedAllowAIRivals) continue;
        Candidates.Add(&Entry);
    }
    Candidates.Sort([&](const FDigimonRankedLadderEntry& A, const FDigimonRankedLadderEntry& B)
    {
        const int32 GradeA = FMath::Abs(A.AchievedGrade - SelfGrade);
        const int32 GradeB = FMath::Abs(B.AchievedGrade - SelfGrade);
        if (GradeA != GradeB) return GradeA < GradeB;
        const int32 DistanceA = FMath::Abs(A.Rating - Self->Rating), DistanceB = FMath::Abs(B.Rating - Self->Rating);
        if (DistanceA != DistanceB) return DistanceA < DistanceB;
        return A.AccountId < B.AccountId;
    });
    if (Candidates.Num() == 0)
    { OutMessage = TEXT("No opponents are ready yet. The host needs active rival tamers or another player's saved defense team."); return false; }
    const int32 BestGradeDistance = FMath::Abs(Candidates[0]->AchievedGrade - SelfGrade);
    int32 Pool = 0;
    while (Pool < FMath::Min(8, Candidates.Num()) &&
        FMath::Abs(Candidates[Pool]->AchievedGrade - SelfGrade) == BestGradeDistance) ++Pool;
    FRandomStream Random(static_cast<int32>(GetTypeHash(FGuid::NewGuid())));
    FDigimonRankedLadderEntry* Opponent = Candidates[Random.RandRange(0, Pool - 1)];
    // Refresh selected bot from its actual live persistent party immediately before combat.
    UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>();
    TArray<FDigimonOwnedPartner> Defenders = Opponent->DefenderTeam;
    if (Opponent->bAIRival)
    {
        FDigimonAIRivalRecord Current;
        if (!Rivals || !Rivals->GetRival(Opponent->RivalId, Current) || Current.Partners.Num() == 0)
        { OutMessage = TEXT("That rival is moving between activities. Please search again."); return false; }
        Defenders = Current.Partners;
    }
    const int32 PartyLimit = FMath::Clamp(Settings->MaxPartySize, 1, 12);
    if (Defenders.Num() > PartyLimit) Defenders.SetNum(PartyLimit);
    TArray<FDigimonOwnedPartner> Attackers = AttackingTeam;
    if (Attackers.Num() > PartyLimit) Attackers.SetNum(PartyLimit);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    if (!Data || Attackers.IsEmpty()) { OutMessage = TEXT("Arena combat data is not ready."); return false; }
    const auto Result = DigimonVenomNXTAutoBattle::Resolve(FullHealthCopy(Attackers), FullHealthCopy(Defenders), Data,
        FMath::Clamp(Settings->ActiveBattleSize, 1, 6), Random.RandRange(1, MAX_int32), Playback!=nullptr);
    if (Playback && !Playback->InitializeRankedPlayback(Challenger,Result,Self->Username,Opponent->Username,RankedData.SeasonId))
    { OutMessage=TEXT("The arena could not prepare its battle. No energy was spent."); return false; }
    const FDigimonRankedLadderEntry Before = *Self;
    const FDigimonRankedLadderEntry DefenderBefore = *Opponent;
    const int32 OldRating = Self->Rating;
    const TArray<int32> Thresholds = DigimonVenomNXTRankedRules::ValidThresholds(Settings->RankedGradeRatingThresholds);
    const auto AttackerProgress = DigimonVenomNXTRankedRulesCore::ApplyPoints(Self->Rating, Self->AchievedGrade,
        Result.bTeamAWon, Result.bDraw, true, Thresholds.GetData(), Settings->RankedWinPoints, Settings->RankedLossPoints);
    const auto DefenderProgress = DigimonVenomNXTRankedRulesCore::ApplyPoints(Opponent->Rating, Opponent->AchievedGrade,
        !Result.bTeamAWon, Result.bDraw, false, Thresholds.GetData(), Settings->RankedWinPoints, Settings->RankedLossPoints);
    Self->Rating = AttackerProgress.Points; Self->AchievedGrade = AttackerProgress.Grade;
    Opponent->Rating = DefenderProgress.Points; Opponent->AchievedGrade = DefenderProgress.Grade;
    const int32 Delta = Self->Rating - OldRating;
    if (Self->bAIRival) Self->RivalRatingOffset = FMath::Clamp(Self->RivalRatingOffset + Delta, -150, 150);
    --Self->Energy;
    Self->SeasonAttacks = static_cast<int32>(FMath::Min<int64>(MAX_int32, static_cast<int64>(Self->SeasonAttacks) + 1));
    if (Result.bDraw) { ++Self->Draws; ++Self->CareerDraws; }
    else if (Result.bTeamAWon) { ++Self->Wins; ++Self->CareerWins; }
    else { ++Self->Losses; ++Self->CareerLosses; }
    if (Result.bDraw) { ++Opponent->Draws; ++Opponent->CareerDraws; }
    else if (Result.bTeamAWon) { ++Opponent->Losses; ++Opponent->CareerLosses; }
    else { ++Opponent->Wins; ++Opponent->CareerWins; }
    Self->LastOpponent = Opponent->Username;
    Self->LastResult = Result.bDraw ? TEXT("DRAW") : Result.bTeamAWon ? TEXT("WIN") : TEXT("LOSS");
    Self->LastRatingDelta = Self->Rating - OldRating;
    Self->LastBattleTurns = Result.Turns; Self->LastBattleUnix = Now;
    Self->LastBattleLog = Self->bAIRival ? TArray<FString>() : Result.Log;
    // Keep replication bounded even if a custom combat resolver produces extremely long logs.
    if (Self->LastBattleLog.Num() > 160) Self->LastBattleLog.RemoveAt(0, Self->LastBattleLog.Num() - 160);
    Self->LastOpponentTeam = Self->bAIRival ? TArray<FDigimonOwnedPartner>() : Defenders;
    if (Self->DefenderTeam.IsEmpty()) Self->DefenderTeam = Attackers;
    Self->TeamPower = TeamPower(Self->DefenderTeam);
    const FString SelfRivalId = Self->bAIRival ? Self->RivalId : FString();
    const FString OpponentRivalId = Opponent->bAIRival ? Opponent->RivalId : FString();
    // Source Battle Park records both competitors' points, but only an attacking
    // win can promote and only the attacker spends energy. Publish both records
    // together when either participant is human.
    if ((!Self->bAIRival || !Opponent->bAIRival) && !Save())
    {
        *Self = Before;
        *Opponent = DefenderBefore;
        OutMessage = TEXT("The match could not be committed. No energy or rating was spent. Please retry.");
        return false;
    }
    // Autonomous bot matches are checkpointed at most once per minute, never a large disk write per bot action.
    // Human result/energy and payout commits remain synchronous; bot-only progress may lose up to 60s on a crash.
    if (Self->bAIRival) bDirty = true;
    if (Rivals)
    {
        if (!SelfRivalId.IsEmpty()) Rivals->RecordRankedResult(SelfRivalId, Result.bTeamAWon && !Result.bDraw, Result.bDraw);
        if (!OpponentRivalId.IsEmpty()) Rivals->RecordRankedResult(OpponentRivalId, !Result.bTeamAWon && !Result.bDraw, Result.bDraw);
    }
    OutMessage = FString::Printf(TEXT("%s vs %s | %d turns | Rating %+d → %d (%s) | Energy %d/%d"),
        *Self->LastResult, *Self->LastOpponent, Result.Turns, Self->LastRatingDelta, Self->Rating,
        *GetGradeLabel(static_cast<EDigimonRankedGrade>(Self->AchievedGrade)), Self->Energy, FMath::Clamp(Settings->RankedMaxEnergy, 1, 999));
    if (AttackerProgress.Promoted) OutMessage += TEXT(" | Promotion earned!");
    else if (AttackerProgress.PromotionPending) OutMessage += TEXT(" | Win your next attacking match to promote.");
    return true;
}

void UDigimonVenomNXTRankedSubsystem::ClaimPendingReward(ADigimonVenomNXTPlayerState* PlayerState)
{
    if (!PlayerState || !PlayerState->HasAuthority() || PlayerState->Profile.AccountId.IsEmpty() || !RollSeasonIfNeeded()) return;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Profiles) return;
    for (int32 I = RankedData.PendingRewards.Num() - 1; I >= 0; --I)
    {
        const FDigimonRankedReward Reward = RankedData.PendingRewards[I];
        if (Reward.AccountId != PlayerState->Profile.AccountId || Reward.DigiRubies <= 0 || Reward.RewardId.IsEmpty()) continue;
        if (!PlayerState->Profile.Ranked.ClaimedRewardIds.Contains(Reward.RewardId))
        {
            if (PlayerState->Profile.DigiRubies > MAX_int32 - Reward.DigiRubies)
            {
                UE_LOG(LogDigimonRanked, Warning, TEXT("Reward retained: account currency capacity reached."));
                continue;
            }
            const FDigimonPlayerProfile Before = PlayerState->Profile;
            PlayerState->Profile.DigiRubies += Reward.DigiRubies;
            PlayerState->Profile.Ranked.ClaimedRewardIds.Add(Reward.RewardId);
            // Currency and receipt are the SAME atomic profile commit. Never remove the queue first.
            if (!Profiles->SaveProfile(PlayerState->Profile))
            {
                PlayerState->Profile = Before;
                UE_LOG(LogDigimonRanked, Error, TEXT("Ranked reward remains queued because profile save failed."));
                continue;
            }
            PlayerState->MarkProfileChanged();
        }
        RankedData.PendingRewards.RemoveAt(I);
        if (!Save())
        {
            // The profile receipt already blocks a duplicate, so retrying removal is safe.
            RankedData.PendingRewards.Insert(Reward, I);
            return;
        }
    }
}

void UDigimonVenomNXTRankedSubsystem::RefreshPlayerState(ADigimonVenomNXTPlayerState* PlayerState)
{
    if (!PlayerState || !PlayerState->HasAuthority() || PlayerState->Profile.AccountId.IsEmpty() || !RollSeasonIfNeeded()) return;
    // Reconnect to the still-running server battle. After a server restart there is
    // no transient actor, but its previously committed result/energy remain authoritative.
    if (const TWeakObjectPtr<ADigimonVenomNXTBattleActor>* Existing=ActivePresentations.Find(PlayerState->Profile.AccountId))
    {
        ADigimonVenomNXTBattleActor* Battle=Existing->Get();
        if (Battle && !Battle->State.bFinished)
        {
            Battle->RebindRankedPlayer(PlayerState);
            if (ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(PlayerState->GetOwner()))
                if (!PC->CurrentBattle) PC->SetCurrentBattleServer(Battle);
        }
        else
        {
            ActivePresentations.Remove(PlayerState->Profile.AccountId);
            VisibleCareersBeforePresentation.Remove(PlayerState->Profile.AccountId);
        }
    }
    FDigimonRankedLadderEntry& Entry = FindOrAddEntry(PlayerState);
    SyncProfile(PlayerState, Entry);
    ClaimPendingReward(PlayerState);
}

TArray<FDigimonRankedPublicEntry> UDigimonVenomNXTRankedSubsystem::GetTop100() const
{
    TArray<FDigimonRankedLadderEntry> Sorted;
    for (const FDigimonRankedLadderEntry& Entry : RankedData.Entries)
        if (!Entry.DefenderTeam.IsEmpty() || Entry.Wins + Entry.Losses + Entry.Draws > 0) Sorted.Add(Entry);
    Sorted.Sort(LadderBefore);
    TArray<FDigimonRankedPublicEntry> Out;
    for (int32 I = 0; I < FMath::Min(100, Sorted.Num()); ++I)
    {
        FDigimonRankedPublicEntry Entry;
        Entry.Rank = I + 1; Entry.Username = Sorted[I].Username; Entry.Rating = Sorted[I].Rating;
        Entry.Grade = static_cast<EDigimonRankedGrade>(FMath::Clamp(Sorted[I].AchievedGrade, 0, 5)); Entry.Wins = Sorted[I].Wins;
        Entry.Losses = Sorted[I].Losses; Entry.Draws = Sorted[I].Draws;
        Entry.bAIRival = Sorted[I].bAIRival; Entry.TeamPower = Sorted[I].TeamPower;
        Out.Add(Entry);
    }
    return Out;
}

void UDigimonVenomNXTRankedSubsystem::PushToGameState(ADigimonVenomNXTGameState* GameState) const
{
    if (!GameState || !GameState->HasAuthority()) return;
    GameState->SetRankedSeasonId(RankedData.SeasonId);
    GameState->SetRankedTop100(GetTop100());
}

void UDigimonVenomNXTRankedSubsystem::RefreshSeasonAndGameState(ADigimonVenomNXTGameState* GameState)
{
    if (!GameState || !GameState->HasAuthority() || !RollSeasonIfNeeded()) return;
    RefreshRivalEntries();
    for (APlayerState* State : GameState->PlayerArray)
        if (ADigimonVenomNXTPlayerState* PlayerState = Cast<ADigimonVenomNXTPlayerState>(State)) RefreshPlayerState(PlayerState);
    if (GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves && bDirty && FDateTime::UtcNow().ToUnixTimestamp() - LastSavedUnix >= 60) Save();
    PushToGameState(GameState);
}
