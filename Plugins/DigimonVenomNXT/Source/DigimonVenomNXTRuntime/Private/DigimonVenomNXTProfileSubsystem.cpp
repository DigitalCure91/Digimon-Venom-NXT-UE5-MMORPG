#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTProfileValidation.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTTradeSubsystem.h"
#include "DigimonVenomNXTTradeStorage.h"
#include "Serialization/Archive.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTCombatMigrationCore.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "Engine/GameInstance.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTAtomicFile.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/CriticalSection.h"
#include "Misc/ScopeLock.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Class.h"

namespace
{
// Profiles and their immutable history are a single local-server persistence domain.
// Keep the existence check and rename together if a caller saves off the game thread.
FCriticalSection ProfilePersistenceMutex;

void ReportProfileStorageFailure(UDigimonVenomNXTProfileSubsystem* Source, const FString& Username, const TCHAR* Reason)
{
    // Persistence can be invoked under its file mutex from a worker. Deliver a
    // compact value-only event on the game thread, without traversing UObjects
    // on the worker for log delivery.
    const TWeakObjectPtr<UDigimonVenomNXTProfileSubsystem> WeakSource(Source);
    auto Deliver = [WeakSource, Username, Message = FString(Reason)]()
    {
        UDigimonVenomNXTProfileSubsystem* Live = WeakSource.Get();
        UGameInstance* Instance = Live ? Live->GetGameInstance() : nullptr;
        UWorld* World = Instance ? Instance->GetWorld() : nullptr;
        if (!World || World->GetNetMode() == NM_Client) return;
        if (UDigimonVenomNXTServerConsoleSubsystem* Console = Instance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>())
            Console->RecordActivity(TEXT("Persistence"), Username, TEXT("Profile storage failed"), Message, TEXT("Error"));
    };
    if (IsInGameThread()) Deliver();
    else AsyncTask(ENamedThreads::GameThread, MoveTemp(Deliver));
}

bool ReadSeasonRecord(const FString& Path, const FString& AccountId, const FString& CareerId,
    FDigimonSeasonArchive& OutRecord)
{
    FString Text, StoredAccount, StoredCareer;
    TSharedPtr<FJsonObject> Envelope;
    if (!FFileHelper::LoadFileToString(Text, *Path) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Envelope) || !Envelope.IsValid()) return false;
    double Version = 0;
    const TSharedPtr<FJsonObject>* RecordObject = nullptr;
    if (!Envelope->TryGetNumberField(TEXT("version"), Version) || Version != 1 ||
        !Envelope->TryGetStringField(TEXT("accountId"), StoredAccount) || StoredAccount != AccountId ||
        !Envelope->TryGetStringField(TEXT("careerId"), StoredCareer) || StoredCareer != CareerId ||
        !Envelope->TryGetObjectField(TEXT("record"), RecordObject) || !RecordObject || !RecordObject->IsValid()) return false;
    if (!FJsonObjectConverter::JsonObjectToUStruct(RecordObject->ToSharedRef(), &OutRecord, 0, 0) ||
        OutRecord.CareerId != CareerId || OutRecord.Week < 1 || OutRecord.Matches.Num() != 8) return false;
    for (const FDigimonSeasonMatch& Match : OutRecord.Matches)
        if (!Match.bResolved || Match.MatchId.IsEmpty()) return false;
    return true;
}

bool EquivalentSeasonRecord(const FDigimonSeasonArchive& A, const FDigimonSeasonArchive& B)
{
    // Reflected value comparison avoids depending on JSON property order or whitespace.
    return FDigimonSeasonArchive::StaticStruct()->CompareScriptStruct(&A, &B, 0);
}

FString SeasonRecordPath(const FString& Directory, int32 Week)
{
    return FPaths::Combine(Directory, FString::Printf(TEXT("week_%010d.json"), Week));
}
}

FString UDigimonVenomNXTProfileSubsystem::ProfilePath(const FString& AccountId) const
{
    FString Safe = AccountId;
    Safe.ReplaceInline(TEXT("/"), TEXT("_")); Safe.ReplaceInline(TEXT("\\"), TEXT("_")); Safe.ReplaceInline(TEXT(".."), TEXT("_"));
#if WITH_DEV_AUTOMATION_TESTS
    if (!TestStorageRoot.IsEmpty()) return FPaths::Combine(TestStorageRoot, TEXT("Profiles"), Safe + TEXT(".json"));
#endif
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Profiles"), Safe + TEXT(".json"));
}

FString UDigimonVenomNXTProfileSubsystem::SeasonArchiveDirectory(const FString& AccountId, const FString& CareerId) const
{
    FGuid CareerGuid;
    if (AccountId.IsEmpty() || !FGuid::Parse(CareerId, CareerGuid) || !CareerGuid.IsValid()) return FString();
    const FString Path = ProfilePath(AccountId);
    return FPaths::Combine(FPaths::GetPath(Path), TEXT("SeasonArchive"), FPaths::GetBaseFilename(Path),
        CareerGuid.ToString(EGuidFormats::Digits));
}

bool UDigimonVenomNXTProfileSubsystem::WriteSeasonArchive(const FDigimonPlayerProfile& Profile) const
{
    const FDigimonSeasonCareer& Career = Profile.Season;
    if (Career.Archive.IsEmpty())
        return Career.CareerId.IsEmpty() || Career.Week <= FMath::Max(1, Career.FirstArchiveWeek);
    const FString Directory = SeasonArchiveDirectory(Profile.AccountId, Career.CareerId);
    if (Directory.IsEmpty() || Career.FirstArchiveWeek < 1 || Career.Week <= Career.FirstArchiveWeek) return false;
    if (!IFileManager::Get().MakeDirectory(*Directory, true)) return false;
    // A previous archive-first attempt may have failed to publish the profile. Only the
    // durable profile can prove that such a record remains provisional, never live memory.
    FString CommittedJson;
    FDigimonPlayerProfile Committed;
    const bool bHasCommittedFence =
        FFileHelper::LoadFileToString(CommittedJson, *ProfilePath(Profile.AccountId)) &&
        FJsonObjectConverter::JsonObjectStringToUStruct(CommittedJson, &Committed, 0, 0) &&
        Committed.AccountId == Profile.AccountId && Committed.Season.CareerId == Career.CareerId &&
        Committed.Season.FirstArchiveWeek >= 1 && Committed.Season.Week >= Committed.Season.FirstArchiveWeek;
    TSet<int32> SeenWeeks;
    for (const FDigimonSeasonArchive& Record : Career.Archive)
    {
        if (Record.CareerId != Career.CareerId || Record.Week < Career.FirstArchiveWeek ||
            Record.Week >= Career.Week || SeenWeeks.Contains(Record.Week) || Record.Matches.Num() != 8) return false;
        SeenWeeks.Add(Record.Week);
        for (const FDigimonSeasonMatch& Match : Record.Matches)
            if (!Match.bResolved || Match.MatchId.IsEmpty()) return false;
        const FString Path = SeasonRecordPath(Directory, Record.Week);
        if (IFileManager::Get().FileExists(*Path))
        {
            FDigimonSeasonArchive Existing;
            if (!ReadSeasonRecord(Path, Profile.AccountId, Career.CareerId, Existing) || Existing.Week != Record.Week) return false;
            if (EquivalentSeasonRecord(Existing, Record)) continue;
            // Committed cards are immutable. A hidden orphan can legitimately differ on
            // retry after payroll settings or the player's name change before Next Week.
            if (!bHasCommittedFence || Record.Week < Committed.Season.Week) return false;
        }
        TSharedRef<FJsonObject> RecordObject = MakeShared<FJsonObject>();
        if (!FJsonObjectConverter::UStructToJsonObject(FDigimonSeasonArchive::StaticStruct(), &Record, RecordObject, 0, 0)) return false;
        TSharedRef<FJsonObject> Envelope = MakeShared<FJsonObject>();
        Envelope->SetNumberField(TEXT("version"), 1);
        Envelope->SetStringField(TEXT("accountId"), Profile.AccountId);
        Envelope->SetStringField(TEXT("careerId"), Career.CareerId);
        Envelope->SetObjectField(TEXT("record"), RecordObject);
        FString Json;
        if (!FJsonSerializer::Serialize(Envelope, TJsonWriterFactory<>::Create(&Json))) return false;
        const FString Temporary = Path + TEXT(".tmp");
        if (!FFileHelper::SaveStringToFile(Json, *Temporary, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM) ||
            !DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary)) return false;
    }
    // A future profile may not publish a new week while its newest completed card is absent.
    return SeenWeeks.Contains(Career.Week - 1);
}

bool UDigimonVenomNXTProfileSubsystem::ReconcileCombatBalance(FDigimonPlayerProfile& Candidate,
    const UDigimonVenomNXTDataSubsystem* Data, bool bLiveBattle)
{
    if (!Data) return false;
    const bool bBattleLocked = bLiveBattle || !Candidate.WorldBattleCheckpointJson.IsEmpty() || !Candidate.Season.BattleCheckpointJson.IsEmpty() ||
        DigimonVenomNXTCampaign::HasPendingBattle(Candidate);
    return DigimonVenomNXTCombatMigrationCore::Reconcile(Candidate.Collection, Candidate.Season.Roster,
        bBattleLocked, [Data](FDigimonOwnedPartner& Partner)
        {
            return DigimonVenomNXTAutoBattle::MigratePartner(Partner, Data);
        });
}

bool UDigimonVenomNXTProfileSubsystem::LoadProfile(const FString& AccountId, const FString& Username, FDigimonPlayerProfile& OutProfile)
{
    if (AccountId.IsEmpty()) return false;
    FString Json;
    bool bRead = false;
    {
        FScopeLock Lock(&ProfilePersistenceMutex);
        if (!RecoverCommerceLocked())
        {
            ReportProfileStorageFailure(this, Username, TEXT("Pending commerce recovery must complete before a profile can be loaded."));
            return false;
        }
        if (const FDigimonPlayerProfile* Session = SessionProfiles.Find(AccountId))
        {
            OutProfile = *Session;
            return true;
        }
        bRead = FFileHelper::LoadFileToString(Json, *ProfilePath(AccountId));
    }
    if (bRead)
    {
        FDigimonPlayerProfile Loaded;
        FString ValidationError;
        if (!DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
            !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Loaded, 0, 0) ||
            !DigimonVenomNXTProfileValidation::Validate(Loaded, AccountId, ValidationError))
        {
            ReportProfileStorageFailure(this, Username, TEXT("Load rejected: saved profile is damaged or belongs to a different account. Existing file retained."));
            return false; // Never replace damaged or mismatched existing progress with a new profile.
        }
        // Upgrade only recorded campaign evidence and retain both exact saved
        // decisions. Publish migration only after the atomic save succeeds.
        const bool bCampaignMigrated = DigimonVenomNXTCampaign::Reconcile(Loaded);
        const bool bTamerStylesMigrated = DigimonVenomNXTSeason::ReconcileTamerStyles(Loaded);
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        const bool bCombatMigrated = ReconcileCombatBalance(Loaded, Data);
        bool bScansMigrated = false;
        for (FDigimonScanRecord& Scan : Loaded.Scans) bScansMigrated |= DigimonVenomNXTScanCore::Observe(Scan, GetDefault<UDigimonVenomNXTSettings>()->ScanCapPercent);
        if ((bCampaignMigrated || bTamerStylesMigrated || bCombatMigrated || bScansMigrated) && !SaveProfile(Loaded)) return false;
        {
            FScopeLock Lock(&ProfilePersistenceMutex);
            SessionProfiles.Add(AccountId, Loaded);
        }
        OutProfile = MoveTemp(Loaded);
        return true;
    }
    if (IFileManager::Get().FileExists(*ProfilePath(AccountId)))
    {
        ReportProfileStorageFailure(this, Username, TEXT("Existing profile could not be read. File retained; no replacement profile created."));
        return false;
    }
    OutProfile = FDigimonPlayerProfile();
    OutProfile.AccountId = AccountId;
    OutProfile.Username = Username;
    // Match the reference's private-home introduction. This branch runs only
    // when no profile exists; reconnecting never awards these supplies again.
    OutProfile.Farm.bInside = true;
    FDigimonInventoryEntry WelcomeTreats;
    WelcomeTreats.ItemId = TEXT("digimeat_cam");
    WelcomeTreats.Quantity = 3;
    OutProfile.Inventory.Add(WelcomeTreats);
    OutProfile.LastSavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    return SaveProfile(OutProfile);
}

bool UDigimonVenomNXTProfileSubsystem::SaveProfile(const FDigimonPlayerProfile& Profile)
{
    if (Profile.AccountId.IsEmpty()) return false;
    const auto Fail = [&](const TCHAR* Reason)
    {
        ReportProfileStorageFailure(this, Profile.Username, Reason);
        return false;
    };
    if (GetWorld() && GetWorld()->GetNetMode() == NM_Client) return false;
    FString ValidationError;
    if (!DigimonVenomNXTProfileValidation::Validate(Profile, Profile.AccountId, ValidationError)) return Fail(*ValidationError);
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (AutomaticSavingEnabled() && !FlushDeferredLocked(ValidationError)) return Fail(*ValidationError);
    if (!CheckCommerceFenceLocked(Profile, false)) return Fail(TEXT("Stale commerce revision rejected; the newer traded profile was retained."));
    FDigimonPlayerProfile Copy = Profile;
    DigimonVenomNXTCampaign::Reconcile(Copy);
    DigimonVenomNXTSeason::ReconcileTamerStyles(Copy);
    if (!AutomaticSavingEnabled())
    {
        RetainProfileLocked(Copy);
        return true; // Accepted in server memory, not a claim of disk durability.
    }
    Copy.LastSavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    FString Json;
    if (!FJsonObjectConverter::UStructToJsonObjectString(Copy, Json)) return Fail(TEXT("Profile serialization failed; previous saved profile retained."));
    FDigimonPlayerProfile Verified;
    if (!DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Verified, 0, 0) ||
        !DigimonVenomNXTProfileValidation::Validate(Verified, Copy.AccountId, ValidationError) ||
        !FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Copy, &Verified, 0))
        return Fail(TEXT("Profile round-trip verification failed; previous saved profile retained."));
    const FString Path = ProfilePath(Copy.AccountId);
    if (!IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true)) return Fail(TEXT("Profile storage directory is unavailable; previous saved profile retained."));
    // Archive first, then publish the profile's new committed week. A failed profile rename
    // may leave an orphan record; LoadSeasonArchive hides it and the same transaction can retry.
    if (!WriteSeasonArchive(Copy)) return Fail(TEXT("Season archive commit failed; profile transaction was not published."));
    const FString Temporary = Path + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(Json, *Temporary, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)) return Fail(TEXT("Temporary profile write failed; previous saved profile retained."));
    // Same-directory rename keeps a partially written JSON file out of the live save path.
    if (!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary)) return Fail(TEXT("Atomic profile replacement failed; previous saved profile retained."));
    SessionProfiles.Add(Copy.AccountId, Copy);
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::LoadSeasonArchive(const FDigimonPlayerProfile& Profile, int32 Page,
    int32 PageSize, FDigimonSeasonArchivePage& OutPage)
{
    OutPage = FDigimonSeasonArchivePage();
    OutPage.CareerId = Profile.Season.CareerId;
    OutPage.PageSize = FMath::Clamp(PageSize, 1, 12);
    OutPage.PageIndex = FMath::Max(0, Page);
    const auto Fail = [&OutPage](const TCHAR* Message)
    {
        OutPage.Records.Reset();
        OutPage.bSuccess = false;
        OutPage.Error = Message;
        return false;
    };
    if (Profile.AccountId.IsEmpty()) return Fail(TEXT("Sign in before loading your career archive."));
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (!RecoverCommerceLocked()) return Fail(TEXT("Commerce storage recovery is pending. Please retry."));
    FString Json;
    FDigimonPlayerProfile Committed;
    if (const FDigimonPlayerProfile* Session = SessionProfiles.Find(Profile.AccountId)) Committed = *Session;
    else if (!FFileHelper::LoadFileToString(Json, *ProfilePath(Profile.AccountId)) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Committed, 0, 0) ||
        Committed.AccountId != Profile.AccountId)
        return Fail(TEXT("Your saved career could not be read. Please retry."));
    const FDigimonSeasonCareer& Career = Committed.Season;
    if (Career.CareerId != Profile.Season.CareerId)
        return Fail(TEXT("Your career has changed. Reopen Season Mode and retry."));
    if (Career.CareerId.IsEmpty())
    {
        OutPage.PageIndex = 0;
        OutPage.bSuccess = true;
        return true;
    }
    const FString Directory = SeasonArchiveDirectory(Committed.AccountId, Career.CareerId);
    if (Directory.IsEmpty() || Career.FirstArchiveWeek < 1 || Career.Week < Career.FirstArchiveWeek)
        return Fail(TEXT("The saved archive index is invalid. Your progress has not been changed."));
    OutPage.TotalRecords = Career.Week - Career.FirstArchiveWeek;
    const int32 LastPage = OutPage.TotalRecords > 0 ? (OutPage.TotalRecords - 1) / OutPage.PageSize : 0;
    OutPage.PageIndex = FMath::Min(OutPage.PageIndex, LastPage);
    const int64 Skip = static_cast<int64>(OutPage.PageIndex) * OutPage.PageSize;
    const int64 NewestWeek = static_cast<int64>(Career.Week) - 1 - Skip;
    const int64 OldestWeek = FMath::Max<int64>(Career.FirstArchiveWeek, NewestWeek - OutPage.PageSize + 1);
    for (int64 Week = NewestWeek; Week >= OldestWeek; --Week)
    {
        FDigimonSeasonArchive Record;
        const FString Key = Committed.AccountId + TEXT(":") + Career.CareerId + TEXT(":") + FString::FromInt(static_cast<int32>(Week));
        if (const FDigimonSeasonArchive* Deferred = DeferredSeasonRecords.Find(Key)) Record = *Deferred;
        else if (!ReadSeasonRecord(SeasonRecordPath(Directory, static_cast<int32>(Week)), Committed.AccountId,
                Career.CareerId, Record) || Record.Week != Week)
            return Fail(TEXT("A saved week could not be read. No archive data was replaced; please retry."));
        OutPage.Records.Add(MoveTemp(Record));
    }
    OutPage.bHasMore = Skip + OutPage.Records.Num() < OutPage.TotalRecords;
    OutPage.bSuccess = true;
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::DeleteProfile(const FString& AccountId)
{
    if (AccountId.IsEmpty()) return false;
    if (UGameInstance* Instance = GetGameInstance())
        if (UDigimonVenomNXTTradeSubsystem* Trade = Instance->GetSubsystem<UDigimonVenomNXTTradeSubsystem>())
            if (Trade->HasAccountAssets(AccountId)) return false;
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (!RecoverCommerceLocked()) return false;
    // Preserve archive folders as recovery history. A new career receives a distinct GUID;
    // only a matching, committed profile can read a career's records through this subsystem.
    if (!IFileManager::Get().Delete(*ProfilePath(AccountId), false, true, true)) return false;
    SessionProfiles.Remove(AccountId);
    DirtySessionProfiles.Remove(AccountId);
    for (auto It = DeferredSeasonRecords.CreateIterator(); It; ++It)
        if (It.Key().StartsWith(AccountId + TEXT(":"))) It.RemoveCurrent();
    return true;
}

namespace
{
bool WriteCommerceAtomic(const FString& Path, const FString& Json)
{
    if (!IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true)) return false;
    const FString Temporary = Path + TEXT(".tmp");
    // Flush the complete UTF-8 stream before the atomic rename. On Windows the shared
    // rename also requests MOVEFILE_WRITE_THROUGH. A failed intent is never published.
    TUniquePtr<FArchive> Writer(IFileManager::Get().CreateFileWriter(*Temporary));
    if (!Writer) return false;
    const FTCHARToUTF8 Utf8(*Json);
    Writer->Serialize(const_cast<ANSICHAR*>(Utf8.Get()), Utf8.Length());
    Writer->Flush();
    const bool bGood = !Writer->IsError() && Writer->Close();
    Writer.Reset();
    return bGood && DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary);
}
}

FString UDigimonVenomNXTProfileSubsystem::CommercePath(const TCHAR* Filename) const
{
#if WITH_DEV_AUTOMATION_TESTS
    if (!TestStorageRoot.IsEmpty()) return FPaths::Combine(TestStorageRoot, TEXT("Commerce"), Filename);
#endif
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Commerce"), Filename);
}

bool UDigimonVenomNXTProfileSubsystem::CheckCommerceFenceLocked(const FDigimonPlayerProfile& Profile, bool bAdvance) const
{
    if (Profile.AccountId.IsEmpty() || Profile.CommerceRevision < 0 || Profile.CommerceRevision > 9007199254740991LL) return false;
    if (const FDigimonPlayerProfile* Session = SessionProfiles.Find(Profile.AccountId))
        return bAdvance ? Session->CommerceRevision < 9007199254740991LL &&
            Profile.CommerceRevision == Session->CommerceRevision + 1 : Profile.CommerceRevision == Session->CommerceRevision;
    const FString Path = ProfilePath(Profile.AccountId);
    if (!IFileManager::Get().FileExists(*Path)) return !bAdvance && Profile.CommerceRevision == 0;
    FString ExistingJson, ValidationError;
    FDigimonPlayerProfile Existing;
    if (!FFileHelper::LoadFileToString(ExistingJson, *Path) ||
        !DigimonVenomNXTProfileValidation::HasRequiredJsonFields(ExistingJson) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(ExistingJson, &Existing, 0, 0) ||
        !DigimonVenomNXTProfileValidation::Validate(Existing, Profile.AccountId, ValidationError)) return false;
    return bAdvance ? Existing.CommerceRevision < 9007199254740991LL &&
        Profile.CommerceRevision == Existing.CommerceRevision + 1 : Profile.CommerceRevision == Existing.CommerceRevision;
}

bool UDigimonVenomNXTProfileSubsystem::ApplyCommerceJournalLocked(const FString& Journal)
{
    TSharedPtr<FJsonObject> Envelope;
    const TArray<TSharedPtr<FJsonValue>>* Records = nullptr;
    FString MarketJson, TransactionId;
    double Version = 0;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Journal), Envelope) || !Envelope.IsValid() ||
        !Envelope->TryGetNumberField(TEXT("version"), Version) || (Version != 1 && Version != 2) ||
        !Envelope->TryGetStringField(TEXT("transaction"), TransactionId) || TransactionId.IsEmpty() ||
        !Envelope->TryGetStringField(TEXT("market"), MarketJson) ||
        !Envelope->TryGetArrayField(TEXT("profiles"), Records) || !Records ||
        (Version == 1 && (Records->Num() < 1 || Records->Num() > 2))) return false;
    // A completed marker is itself atomically replaced and flushed before journal unlink.
    // If a power loss resurrects an unlinked intent, never replay it over later autosaves.
    FString CompletedTransaction;
    if (FFileHelper::LoadFileToString(CompletedTransaction, *CommercePath(TEXT("completed.txt"))) && CompletedTransaction == TransactionId)
        return IFileManager::Get().Delete(*CommercePath(TEXT("pending.json")), false, true, true);
    TArray<FDigimonPlayerProfile> Profiles;
    TArray<FString> JsonProfiles;
    TSet<FString> Accounts;
    // Validate the entire intent before making its first write. The market is parsed too.
    FDigimonTradeMarket ParsedMarket;
    if (!DigimonVenomNXTTradeStorage::ReadMarket(MarketJson, ParsedMarket)) return false;
    for (const TSharedPtr<FJsonValue>& Record : *Records)
    {
        FString Json;
        FDigimonPlayerProfile Profile;
        FString ValidationError;
        if (!Record.IsValid() || !Record->TryGetString(Json) ||
            !DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
            !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Profile, 0, 0) ||
            !DigimonVenomNXTProfileValidation::Validate(Profile, Profile.AccountId, ValidationError) ||
            Profile.CommerceRevision < (Version == 1 ? 1 : 0) || Accounts.Contains(Profile.AccountId)) return false;
        Accounts.Add(Profile.AccountId);
        Profiles.Add(MoveTemp(Profile)); JsonProfiles.Add(MoveTemp(Json));
    }
    for (int32 Index = 0; Index < Profiles.Num(); ++Index)
        if (!WriteCommerceAtomic(ProfilePath(Profiles[Index].AccountId), JsonProfiles[Index])) return false;
    if (!WriteCommerceAtomic(CommercePath(TEXT("market.json")), MarketJson)) return false;
    if (!WriteCommerceAtomic(CommercePath(TEXT("completed.txt")), TransactionId)) return false;
    // Retain the journal unless every target and journal removal succeed. No later writes
    // are allowed while this exists, so retrying replay cannot roll back newer progress.
    return IFileManager::Get().Delete(*CommercePath(TEXT("pending.json")), false, true, true);
}

bool UDigimonVenomNXTProfileSubsystem::RecoverCommerceLocked()
{
    const FString Path = CommercePath(TEXT("pending.json"));
    if (!IFileManager::Get().FileExists(*Path)) return true;
    FString Journal;
    return FFileHelper::LoadFileToString(Journal, *Path) && ApplyCommerceJournalLocked(Journal);
}

bool UDigimonVenomNXTProfileSubsystem::CommitCommerce(const TArray<FDigimonPlayerProfile>& Candidates,
    const FString& MarketJson, FString& Error)
{
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (GetWorld() && GetWorld()->GetNetMode() == NM_Client) { Error = TEXT("Only the server may commit account progress."); return false; }
    if (AutomaticSavingEnabled() && !FlushDeferredLocked(Error)) return false;
    FDigimonTradeMarket ValidatedMarket;
    if (Candidates.Num() < 1 || Candidates.Num() > 2 || !DigimonVenomNXTTradeStorage::ReadMarket(MarketJson, ValidatedMarket))
        { Error = TEXT("Invalid transaction or damaged trading storage. Nothing was changed."); return false; }
    TSet<FString> Accounts;
    for (const FDigimonPlayerProfile& Candidate : Candidates)
    {
        if (!DigimonVenomNXTProfileValidation::Validate(Candidate, Candidate.AccountId, Error) ||
            Accounts.Contains(Candidate.AccountId) || !CheckCommerceFenceLocked(Candidate, true))
        { Error = TEXT("Account transaction validation failed. Nothing was changed."); return false; }
        Accounts.Add(Candidate.AccountId);
    }
    if (!AutomaticSavingEnabled())
    {
        for (const FDigimonPlayerProfile& Candidate : Candidates) RetainProfileLocked(Candidate);
        SessionMarketJson = MarketJson;
        bHasSessionMarket = true;
        bMarketDirty = true;
        return true;
    }
    Accounts.Reset();
    TArray<TSharedPtr<FJsonValue>> Records;
    for (FDigimonPlayerProfile Candidate : Candidates)
    {
        if (!DigimonVenomNXTProfileValidation::Validate(Candidate, Candidate.AccountId, Error)) return false;
        if (Accounts.Contains(Candidate.AccountId) || !CheckCommerceFenceLocked(Candidate, true))
            { Error = TEXT("Account progress changed. Reconnect before trading again."); return false; }
        Accounts.Add(Candidate.AccountId);
        Candidate.LastSavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
        FString Json;
        if (!WriteSeasonArchive(Candidate) || !FJsonObjectConverter::UStructToJsonObjectString(Candidate, Json))
            { Error = TEXT("Could not prepare saved progress. Nothing was traded."); return false; }
        Records.Add(MakeShared<FJsonValueString>(Json));
    }
    TSharedRef<FJsonObject> Envelope = MakeShared<FJsonObject>();
    Envelope->SetNumberField(TEXT("version"), 1);
    Envelope->SetStringField(TEXT("transaction"), FGuid::NewGuid().ToString(EGuidFormats::Digits));
    Envelope->SetStringField(TEXT("market"), MarketJson);
    Envelope->SetArrayField(TEXT("profiles"), Records);
    FString Journal;
    if (!FJsonSerializer::Serialize(Envelope, TJsonWriterFactory<>::Create(&Journal)) ||
        !WriteCommerceAtomic(CommercePath(TEXT("pending.json")), Journal))
        { Error = TEXT("Could not save the transaction. Nothing was traded."); return false; }
    // The complete intent is durable. From this point rollback/retry as a new sale would
    // duplicate assets. Publish its candidates even if disk replay temporarily cannot finish.
    if (!ApplyCommerceJournalLocked(Journal))
        ReportProfileStorageFailure(this, Candidates[0].Username,
            TEXT("Commerce intent committed. Recovery will complete before further profile writes or trades."));
    for (const FDigimonPlayerProfile& Candidate : Candidates) SessionProfiles.Add(Candidate.AccountId, Candidate);
    SessionMarketJson = MarketJson;
    bHasSessionMarket = true;
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::LoadCommerceMarket(FString& Json, bool& bExists, FString& Error)
{
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (!RecoverCommerceLocked()) { Error = TEXT("Trading storage recovery is pending. Please retry later."); return false; }
    if (bHasSessionMarket) { Json = SessionMarketJson; bExists = true; return true; }
    const FString Path = CommercePath(TEXT("market.json"));
    bExists = IFileManager::Get().FileExists(*Path);
    if (!bExists) { Json.Reset(); return true; }
    if (!FFileHelper::LoadFileToString(Json, *Path))
        { Error = TEXT("The trading center could not read its saved listings. No assets were changed."); return false; }
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::IsCommerceStorageReady()
{
    FScopeLock Lock(&ProfilePersistenceMutex);
    return RecoverCommerceLocked();
}

bool UDigimonVenomNXTProfileSubsystem::LoadExistingCommerceProfile(const FString& AccountId, FDigimonPlayerProfile& OutProfile)
{
    if (AccountId.IsEmpty()) return false;
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (!RecoverCommerceLocked()) return false;
    if (const FDigimonPlayerProfile* Session = SessionProfiles.Find(AccountId)) { OutProfile = *Session; return true; }
    FString Json, ValidationError;
    FDigimonPlayerProfile Candidate;
    if (!FFileHelper::LoadFileToString(Json, *ProfilePath(AccountId)) ||
        !DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Candidate, 0, 0) ||
        !DigimonVenomNXTProfileValidation::Validate(Candidate, AccountId, ValidationError)) return false;
    OutProfile = MoveTemp(Candidate);
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::CommitProfileGroup(TArray<FDigimonPlayerProfile>& Candidates, FString& Error)
{
    if (!IsInGameThread()) { Error = TEXT("Grouped profile settlement requires the game thread."); return false; }
    FString MarketJson; bool bExists = false;
    if (!LoadCommerceMarket(MarketJson, bExists, Error)) return false;
    if (!bExists)
    {
        const FDigimonTradeMarket Empty;
        if (!FJsonObjectConverter::UStructToJsonObjectString(Empty, MarketJson)) return false;
    }
    TArray<FDigimonPlayerProfile> Next = Candidates;
    for (auto& Candidate : Next)
    {
        if (Candidate.CommerceRevision < 0 || Candidate.CommerceRevision >= 9007199254740991LL)
            { Error = TEXT("Transaction revision exhausted."); return false; }
        ++Candidate.CommerceRevision;
    }
    if (!CommitCommerce(Next, MarketJson, Error)) return false;
    Candidates = MoveTemp(Next);
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::AutomaticSavingEnabled() const
{
#if WITH_DEV_AUTOMATION_TESTS
    if (TestAutomaticSaving.IsSet()) return TestAutomaticSaving.GetValue();
#endif
    return GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves;
}

void UDigimonVenomNXTProfileSubsystem::RetainProfileLocked(const FDigimonPlayerProfile& Profile)
{
    SessionProfiles.Add(Profile.AccountId, Profile);
    DirtySessionProfiles.Add(Profile.AccountId);
    // The replicated career keeps only a bounded recent-history window. Preserve
    // older, not-yet-flushed weeks separately so long manual-save sessions lose none.
    for (const FDigimonSeasonArchive& Record : Profile.Season.Archive)
    {
        const FString Key = Profile.AccountId + TEXT(":") + Record.CareerId + TEXT(":") + FString::FromInt(Record.Week);
        DeferredSeasonRecords.Add(Key, Record);
    }
}

bool UDigimonVenomNXTProfileSubsystem::RetainProfile(const FDigimonPlayerProfile& Profile)
{
    if (GetWorld() && GetWorld()->GetNetMode() == NM_Client) return false;
    FString Error;
    if (!DigimonVenomNXTProfileValidation::Validate(Profile, Profile.AccountId, Error))
    {
        ReportProfileStorageFailure(this, Profile.Username, *Error);
        return false;
    }
    FScopeLock Lock(&ProfilePersistenceMutex);
    if (!CheckCommerceFenceLocked(Profile, false)) return false;
    // No recovery replay, serialization, archive writer or file writer on logout.
    RetainProfileLocked(Profile);
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::FlushDeferredLocked(FString& Error)
{
    Error.Reset();
    if (!RecoverCommerceLocked())
    { Error = TEXT("An earlier durable transaction must finish replaying before the next checkpoint. Check the save folder."); return false; }
    if (DirtySessionProfiles.IsEmpty() && !bMarketDirty) return true;
    FString MarketJson = SessionMarketJson;
    if (!bHasSessionMarket)
    {
        const FString MarketPath = CommercePath(TEXT("market.json"));
        if (IFileManager::Get().FileExists(*MarketPath))
        {
            if (!FFileHelper::LoadFileToString(MarketJson, *MarketPath))
            { Error = TEXT("Could not read the market for the full checkpoint. In-memory progress is retained."); return false; }
        }
        else
        {
            const FDigimonTradeMarket Empty;
            if (!FJsonObjectConverter::UStructToJsonObjectString(Empty, MarketJson)) return false;
        }
    }
    FDigimonTradeMarket ValidMarket;
    if (!DigimonVenomNXTTradeStorage::ReadMarket(MarketJson, ValidMarket))
    { Error = TEXT("Market validation failed. In-memory progress is retained."); return false; }
    TArray<TSharedPtr<FJsonValue>> Records;
    const int64 SavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    for (const FString& AccountId : DirtySessionProfiles)
    {
        const FDigimonPlayerProfile* Session = SessionProfiles.Find(AccountId);
        if (!Session || !DigimonVenomNXTProfileValidation::Validate(*Session, AccountId, Error)) return false;
        FDigimonPlayerProfile Candidate = *Session;
        Candidate.LastSavedUnix = SavedUnix;
        FString Json;
        FDigimonPlayerProfile Verified;
        if (!FJsonObjectConverter::UStructToJsonObjectString(Candidate, Json) ||
            !DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
            !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Verified, 0, 0) ||
            !DigimonVenomNXTProfileValidation::Validate(Verified, AccountId, Error) ||
            !FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&Candidate, &Verified, 0))
        { Error = TEXT("Checkpoint round-trip validation failed for ") + Candidate.Username; return false; }
        // Flush all accepted weeks, but keep the on-disk/live profile's archive
        // window bounded. Immutable history remains in its separate record files.
        FDigimonPlayerProfile WithHistory = Candidate;
        TSet<int32> Weeks;
        for (const FDigimonSeasonArchive& Record : WithHistory.Season.Archive) Weeks.Add(Record.Week);
        const FString Prefix = AccountId + TEXT(":") + Candidate.Season.CareerId + TEXT(":");
        for (const auto& Entry : DeferredSeasonRecords)
            if (Entry.Key.StartsWith(Prefix) && !Weeks.Contains(Entry.Value.Week))
            { WithHistory.Season.Archive.Add(Entry.Value); Weeks.Add(Entry.Value.Week); }
        if (!WriteSeasonArchive(WithHistory))
        { Error = TEXT("Could not checkpoint Season history for ") + Candidate.Username; return false; }
        Records.Add(MakeShared<FJsonValueString>(Json));
    }
    // One replayable intent covers ALL pending profiles plus their current market.
    // Saving offline trade participants separately would permit duplicated assets
    // after interruption, so manual checkpoints reuse the transaction journal.
    TSharedRef<FJsonObject> Envelope = MakeShared<FJsonObject>();
    Envelope->SetNumberField(TEXT("version"), 2);
    Envelope->SetStringField(TEXT("transaction"), FGuid::NewGuid().ToString(EGuidFormats::Digits));
    Envelope->SetStringField(TEXT("market"), MarketJson);
    Envelope->SetArrayField(TEXT("profiles"), Records);
    FString Journal;
    if (!FJsonSerializer::Serialize(Envelope, TJsonWriterFactory<>::Create(&Journal)) ||
        !WriteCommerceAtomic(CommercePath(TEXT("pending.json")), Journal))
    { Error = TEXT("Could not publish the full checkpoint intent. Server-memory progress is retained; retry /saveall."); return false; }
    if (!ApplyCommerceJournalLocked(Journal))
    { Error = TEXT("The full checkpoint intent is durable, but file replay is incomplete. Keep the server open and retry /saveall."); return false; }
    for (const FString& AccountId : DirtySessionProfiles)
        if (FDigimonPlayerProfile* Session = SessionProfiles.Find(AccountId)) Session->LastSavedUnix = SavedUnix;
    DirtySessionProfiles.Reset();
    DeferredSeasonRecords.Reset();
    bMarketDirty = false;
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::SaveForHostConsole(int32& OutSavedProfiles, FString& Error)
{
    OutSavedProfiles = 0;
    UGameInstance* Instance = GetGameInstance();
    UDigimonVenomNXTServerConsoleSubsystem* Console = Instance ? Instance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    if (!IsInGameThread() || !Console || !Console->CanAccess(Instance->GetFirstLocalPlayerController()))
    { Error = TEXT("Only the authenticated local admin may force a profile checkpoint."); return false; }
    FScopeLock Lock(&ProfilePersistenceMutex);
    const int32 Count = DirtySessionProfiles.Num();
    if (!FlushDeferredLocked(Error)) return false;
    OutSavedProfiles = Count;
    return true;
}

bool UDigimonVenomNXTProfileSubsystem::FlushAutomaticSaves(FString& Error)
{
    if (!AutomaticSavingEnabled()) return true;
    if (GetWorld() && GetWorld()->GetNetMode() == NM_Client) return false;
    FScopeLock Lock(&ProfilePersistenceMutex);
    return FlushDeferredLocked(Error);
}

#if WITH_DEV_AUTOMATION_TESTS
bool UDigimonVenomNXTProfileSubsystem::FlushForTests(FString& Error)
{
    // Test-only override cannot be used to write an actual host save directory.
    if (TestStorageRoot.IsEmpty()) return false;
    FScopeLock Lock(&ProfilePersistenceMutex);
    return FlushDeferredLocked(Error);
}
#endif
