#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTSocialCore.h"
#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTAtomicFile.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTWorldChatCore.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

namespace
{
    FDigimonSocialAccountRecord* Account(FDigimonSocialDatabase& DB, const FString& Id)
    { return DB.Accounts.FindByPredicate([&](const FDigimonSocialAccountRecord& A) { return A.AccountId == Id; }); }
    const FDigimonSocialAccountRecord* Account(const FDigimonSocialDatabase& DB, const FString& Id)
    { return DB.Accounts.FindByPredicate([&](const FDigimonSocialAccountRecord& A) { return A.AccountId == Id; }); }
    FDigimonClanRecord* ClanFor(FDigimonSocialDatabase& DB, const FString& Id)
    { return DB.Clans.FindByPredicate([&](const FDigimonClanRecord& C) { return C.Members.ContainsByPredicate([&](const FDigimonClanMemberRecord& M) { return M.AccountId == Id; }); }); }
    const FDigimonClanRecord* ClanFor(const FDigimonSocialDatabase& DB, const FString& Id)
    { return DB.Clans.FindByPredicate([&](const FDigimonClanRecord& C) { return C.Members.ContainsByPredicate([&](const FDigimonClanMemberRecord& M) { return M.AccountId == Id; }); }); }
    FDigimonClanMemberRecord* MemberOf(FDigimonClanRecord& C, const FString& Id)
    { return C.Members.FindByPredicate([&](const FDigimonClanMemberRecord& M) { return M.AccountId == Id; }); }
    EDigimonClanRole RoleOf(const FDigimonClanRecord& C, const FString& Id)
    {
        const FDigimonClanMemberRecord* Member = C.Members.FindByPredicate([&](const FDigimonClanMemberRecord& M) { return M.AccountId == Id; });
        return Member ? Member->Role : EDigimonClanRole::None;
    }
    void EnsureAccount(FDigimonSocialDatabase& DB, const FString& Id, const FString& Name)
    {
        if (FDigimonSocialAccountRecord* Existing = Account(DB, Id)) Existing->Username = Name;
        else { FDigimonSocialAccountRecord A; A.AccountId = Id; A.Username = Name; DB.Accounts.Add(MoveTemp(A)); }
    }
    bool CleanText(const FString& Input, int32 Max, FString& Out, bool bAllowEmpty = true)
    {
        if (Input.Len() > Max) return false;
        Out = Input.TrimStartAndEnd();
        if (!bAllowEmpty && Out.IsEmpty()) return false;
        for (TCHAR Ch : Out) if (Ch < 32 || Ch == 127 || Ch == 0x2028 || Ch == 0x2029) return false;
        return true;
    }
    bool ValidClanName(const FString& Name)
    {
        if (Name.Len() < 3 || Name.Len() > 32 || Name != Name.TrimStartAndEnd()) return false;
        bool bHasLetterOrNumber = false;
        for (TCHAR Ch : Name)
        {
            if (FChar::IsAlnum(Ch)) bHasLetterOrNumber = true;
            else if (Ch != TEXT(' ') && Ch != TEXT('_') && Ch != TEXT('-')) return false;
        }
        return bHasLetterOrNumber;
    }
    bool ValidTag(const FString& Tag)
    {
        if (Tag.Len() < 2 || Tag.Len() > 5) return false;
        for (TCHAR Ch : Tag) if (!((Ch >= TEXT('A') && Ch <= TEXT('Z')) || (Ch >= TEXT('0') && Ch <= TEXT('9')))) return false;
        return true;
    }
    bool Blocked(const FDigimonSocialDatabase& DB, const FString& A, const FString& B)
    {
        const FDigimonSocialAccountRecord* First = Account(DB, A);
        const FDigimonSocialAccountRecord* Second = Account(DB, B);
        return (First && First->Ignored.Contains(B)) || (Second && Second->Ignored.Contains(A));
    }
    void RemoveFriendship(FDigimonSocialAccountRecord& A, FDigimonSocialAccountRecord& B)
    {
        A.Friends.Remove(B.AccountId); B.Friends.Remove(A.AccountId);
        A.IncomingFriends.Remove(B.AccountId); B.OutgoingFriends.Remove(A.AccountId);
        A.OutgoingFriends.Remove(B.AccountId); B.IncomingFriends.Remove(A.AccountId);
    }
    int32 InvitationsFor(const FDigimonSocialDatabase& DB, const FString& Id, int64 Now)
    {
        int32 Count = 0;
        for (const FDigimonClanRecord& C : DB.Clans)
            for (const FDigimonClanInvitationRecord& I : C.Invitations) if (I.AccountId == Id && I.ExpiresUnix > Now) ++Count;
        return Count;
    }
    void SortContacts(TArray<FDigimonSocialContact>& Contacts)
    {
        Contacts.Sort([](const FDigimonSocialContact& A, const FDigimonSocialContact& B)
        { return A.bOnline != B.bOnline ? A.bOnline : A.Username.Compare(B.Username, ESearchCase::IgnoreCase) < 0; });
    }
}

void UDigimonVenomNXTSocialSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    Collection.InitializeDependency<UDigimonVenomNXTAuthSubsystem>();
    // Deferred until an authenticated authority calls us: joining clients never read the host database.
}

FString UDigimonVenomNXTSocialSubsystem::SavePath()
{
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("Social"), TEXT("Social.json"));
}

bool UDigimonVenomNXTSocialSubsystem::EnsureLoaded()
{
    if (bLoaded) return bReady;
    if (!GetWorld() || GetWorld()->GetNetMode() == NM_Client) return false;
    bLoaded = true;
    const FString Path = SavePath();
    if (!IFileManager::Get().FileExists(*Path)) { bReady = true; return true; }
    const int64 FileSize = IFileManager::Get().FileSize(*Path);
    if (FileSize <= 0 || FileSize > 64ll * 1024 * 1024) return false;
    FString Text;
    FDigimonSocialDatabase Loaded;
    TSharedPtr<FJsonObject> Root;
    if (!FFileHelper::LoadFileToString(Text, *Path) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root) || !Root.IsValid() ||
        !Root->HasTypedField<EJson::Number>(TEXT("schemaVersion")) ||
        !Root->HasTypedField<EJson::Number>(TEXT("revision")) ||
        !Root->HasTypedField<EJson::Array>(TEXT("accounts")) ||
        !Root->HasTypedField<EJson::Array>(TEXT("clans")) ||
        !FJsonObjectConverter::JsonObjectToUStruct(Root.ToSharedRef(), &Loaded, 0, 0) || !ValidateDatabase(Loaded))
    {
        UE_LOG(LogTemp, Error, TEXT("Digimon social database is unreadable or invalid; preserving it and blocking social mutations."));
        return false;
    }
    Database = MoveTemp(Loaded);
    RebuildIndexes();
    bReady = true;
    return true;
}

void UDigimonVenomNXTSocialSubsystem::RebuildIndexes()
{
    AccountIndex.Reset(); MembershipIndex.Reset(); InvitationIndex.Reset();
    for (int32 Index = 0; Index < Database.Accounts.Num(); ++Index) AccountIndex.Add(Database.Accounts[Index].AccountId, Index);
    for (int32 Index = 0; Index < Database.Clans.Num(); ++Index)
    {
        for (const FDigimonClanMemberRecord& Member : Database.Clans[Index].Members) MembershipIndex.Add(Member.AccountId, Index);
        for (const FDigimonClanInvitationRecord& Invite : Database.Clans[Index].Invitations) InvitationIndex.FindOrAdd(Invite.AccountId).Add(Index);
    }
}

const FDigimonSocialAccountRecord* UDigimonVenomNXTSocialSubsystem::FindAccountById(const FString& Id) const
{
    const int32* Index = AccountIndex.Find(Id);
    return Index && Database.Accounts.IsValidIndex(*Index) ? &Database.Accounts[*Index] : nullptr;
}

const FDigimonClanRecord* UDigimonVenomNXTSocialSubsystem::FindClanByMember(const FString& Id) const
{
    const int32* Index = MembershipIndex.Find(Id);
    return Index && Database.Clans.IsValidIndex(*Index) ? &Database.Clans[*Index] : nullptr;
}

bool UDigimonVenomNXTSocialSubsystem::ValidateDatabase(const FDigimonSocialDatabase& DB)
{
    if (DB.SchemaVersion != 1 || DB.Revision < 0 || DB.Accounts.Num() > 100000 || DB.Clans.Num() > 10000) return false;
    TSet<FString> Ids;
    TMap<FString, const FDigimonSocialAccountRecord*> ById;
    for (const FDigimonSocialAccountRecord& A : DB.Accounts)
    {
        if (A.AccountId.IsEmpty() || A.AccountId.Len() > 128 || A.Username.IsEmpty() || A.Username.Len() > 24 ||
            Ids.Contains(A.AccountId) || A.Friends.Num() > DigimonVenomNXTSocialCore::MaxFriends ||
            A.Ignored.Num() > DigimonVenomNXTSocialCore::MaxIgnored || A.IncomingFriends.Num() > DigimonVenomNXTSocialCore::MaxFriendRequests || A.OutgoingFriends.Num() > DigimonVenomNXTSocialCore::MaxFriendRequests) return false;
        Ids.Add(A.AccountId); ById.Add(A.AccountId, &A);
    }
    for (const FDigimonSocialAccountRecord& A : DB.Accounts)
    {
        const TArray<FString>* Lists[] = { &A.Friends, &A.Ignored, &A.IncomingFriends, &A.OutgoingFriends };
        for (const TArray<FString>* List : Lists)
        {
            TSet<FString> Seen;
            for (const FString& Id : *List)
            { if (Id == A.AccountId || !Ids.Contains(Id) || Seen.Contains(Id)) return false; Seen.Add(Id); }
        }
        for (const FString& Id : A.Friends)
        {
            const FDigimonSocialAccountRecord* const* FoundOther = ById.Find(Id);
            const FDigimonSocialAccountRecord* Other = FoundOther ? *FoundOther : nullptr;
            if (!Other || !Other->Friends.Contains(A.AccountId) || (A.Ignored.Contains(Id) || (Other && Other->Ignored.Contains(A.AccountId))) ||
                A.IncomingFriends.Contains(Id) || A.OutgoingFriends.Contains(Id)) return false;
        }
        for (const FString& Id : A.IncomingFriends)
        {
            const FDigimonSocialAccountRecord* const* FoundOther = ById.Find(Id);
            const FDigimonSocialAccountRecord* Other = FoundOther ? *FoundOther : nullptr;
            if (!Other || !Other->OutgoingFriends.Contains(A.AccountId) || A.OutgoingFriends.Contains(Id) || (A.Ignored.Contains(Id) || (Other && Other->Ignored.Contains(A.AccountId)))) return false;
        }
        for (const FString& Id : A.OutgoingFriends)
        {
            const FDigimonSocialAccountRecord* const* FoundOther = ById.Find(Id);
            const FDigimonSocialAccountRecord* Other = FoundOther ? *FoundOther : nullptr;
            if (!Other || !Other->IncomingFriends.Contains(A.AccountId) || (A.Ignored.Contains(Id) || (Other && Other->Ignored.Contains(A.AccountId)))) return false;
        }
    }
    TSet<FString> ClanIds, ClanNames, ClanTags, MemberIds, AllMemberIds;
    TMap<FString, int32> InvitationCounts;
    for (const FDigimonClanRecord& C : DB.Clans)
        for (const FDigimonClanMemberRecord& M : C.Members) AllMemberIds.Add(M.AccountId);
    for (const FDigimonClanRecord& C : DB.Clans)
    {
        FString Clean;
        if (C.ClanId.IsEmpty() || C.ClanId.Len() > 64 || ClanIds.Contains(C.ClanId) || !ValidClanName(C.Name) || !ValidTag(C.Tag) ||
            ClanNames.Contains(C.Name.ToLower()) || ClanTags.Contains(C.Tag) || !CleanText(C.Description, 240, Clean) ||
            !CleanText(C.MessageOfTheDay, 200, Clean) || C.Members.Num() < 1 || C.Members.Num() > DigimonVenomNXTSocialCore::MaxClanMembers || C.Invitations.Num() > DigimonVenomNXTSocialCore::MaxClanInvitations) return false;
        ClanIds.Add(C.ClanId); ClanNames.Add(C.Name.ToLower()); ClanTags.Add(C.Tag);
        int32 Leaders = 0;
        for (const FDigimonClanMemberRecord& M : C.Members)
        {
            if (!Ids.Contains(M.AccountId) || MemberIds.Contains(M.AccountId) || !DigimonVenomNXTSocialCore::ValidRole(static_cast<int>(M.Role)) || M.JoinedUnix <= 0) return false;
            MemberIds.Add(M.AccountId);
            if (M.Role == EDigimonClanRole::Leader) ++Leaders;
        }
        if (Leaders != 1) return false;
        TSet<FString> InviteIds;
        for (const FDigimonClanInvitationRecord& I : C.Invitations)
        {
            if (!Ids.Contains(I.AccountId) || !Ids.Contains(I.InviterAccountId) || InviteIds.Contains(I.AccountId) ||
                I.ExpiresUnix <= 0 || I.AccountId == I.InviterAccountId || AllMemberIds.Contains(I.AccountId) ||
                !DigimonVenomNXTSocialCore::CanInvite(static_cast<int>(RoleOf(C, I.InviterAccountId)))) return false;
            const FDigimonSocialAccountRecord* Recipient = ById.FindChecked(I.AccountId);
            const FDigimonSocialAccountRecord* Inviter = ById.FindChecked(I.InviterAccountId);
            if (Recipient->Ignored.Contains(I.InviterAccountId) || Inviter->Ignored.Contains(I.AccountId) ||
                ++InvitationCounts.FindOrAdd(I.AccountId) > DigimonVenomNXTSocialCore::MaxAccountClanInvitations) return false;
            InviteIds.Add(I.AccountId);
        }
    }
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::Commit(FDigimonSocialDatabase&& Candidate, FString& OutError)
{
    if (!bReady || Database.Revision == MAX_int64) { OutError = TEXT("Social storage is unavailable. Your previous data is safe."); return false; }
    Candidate.Revision = Database.Revision + 1;
    if (!ValidateDatabase(Candidate)) { OutError = TEXT("The social update could not be validated. No changes were made."); return false; }
    if (GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves && !WriteDatabase(Candidate, OutError)) return false;
    bDirty = !GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves;
    // Both sides publish together; manual mode retains the complete database in memory.
    Database = MoveTemp(Candidate);
    RebuildIndexes();
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::Authenticate(const ADigimonVenomNXTPlayerController* Controller, FString& OutId, FString& OutName) const
{
    if (!Controller || !Controller->HasAuthority() || !Controller->IsAccountAuthenticated()) return false;
    const ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || PS->Profile.AccountId.IsEmpty() || PS->Profile.Username.IsEmpty()) return false;
    OutId = PS->Profile.AccountId; OutName = PS->Profile.Username;
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::ResolveAccount(const FString& Query, FString& OutId, FString& OutName) const
{
    if (Query.IsEmpty() || Query.Len() > 128 || !GetGameInstance()) return false;
    const FString Clean = Query.TrimStartAndEnd();
    // The common nameplate/invitation path is resolved from admitted connections without a disk read.
    if (GetWorld()) for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!PC || !PC->IsAccountAuthenticated()) continue;
        const ADigimonVenomNXTPlayerState* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (PS && (PS->Profile.AccountId.Equals(Clean, ESearchCase::IgnoreCase) || PS->Profile.Username.Equals(Clean, ESearchCase::IgnoreCase)))
        { OutId = PS->Profile.AccountId; OutName = PS->Profile.Username; return true; }
    }
    if (const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>())
        return Auth->GetAccountIdentity(Clean, OutName, OutId);
    return false;
}

bool UDigimonVenomNXTSocialSubsystem::HasClanMembership(const FString& Id) const
{
    if (!const_cast<UDigimonVenomNXTSocialSubsystem*>(this)->EnsureLoaded()) return true;
    return FindClanByMember(Id) != nullptr;
}

bool UDigimonVenomNXTSocialSubsystem::IsIgnoring(const FString& ViewerId, const FString& SenderId) const
{
    if (ViewerId.IsEmpty() || SenderId.IsEmpty() || ViewerId == SenderId) return false;
    if (!const_cast<UDigimonVenomNXTSocialSubsystem*>(this)->EnsureLoaded()) return true;
    const FDigimonSocialAccountRecord* A = FindAccountById(ViewerId);
    return A && A->Ignored.Contains(SenderId);
}

bool UDigimonVenomNXTSocialSubsystem::IsInteractionBlocked(const FString& A, const FString& B) const
{
    if (A.IsEmpty() || B.IsEmpty() || A == B) return true;
    if (!const_cast<UDigimonVenomNXTSocialSubsystem*>(this)->EnsureLoaded()) return true;
    const FDigimonSocialAccountRecord* First = FindAccountById(A);
    const FDigimonSocialAccountRecord* Second = FindAccountById(B);
    return (First && First->Ignored.Contains(B)) || (Second && Second->Ignored.Contains(A));
}

void UDigimonVenomNXTSocialSubsystem::RefreshPresenceCache() const
{
    const double Now = FPlatformTime::Seconds();
    if (CachedPresenceWorld.Get() == GetWorld() && Now - LastPresenceRefresh < 1.0) return;
    CachedPresenceWorld = GetWorld(); LastPresenceRefresh = Now; PresenceCache.Reset();
    if (!GetWorld()) return;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!PC || !PC->IsAccountAuthenticated()) continue;
        const ADigimonVenomNXTPlayerState* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!PS || PS->Profile.AccountId.IsEmpty()) continue;
        FDigimonSocialContact Out;
        Out.AccountId = PS->Profile.AccountId; Out.Username = PS->Profile.Username; Out.bOnline = true;
        Out.LeadLevel = PS->PublicSnapshot.LeadLevel; Out.LeadSpeciesId = PS->PublicSnapshot.LeadSpeciesId;
        if (PC->IsInDigiFarm()) Out.Location = TEXT("DigiFarm");
        else if (PC->IsInRelay()) Out.Location = TEXT("Story adventure");
        else if (Data)
        {
            if (const FDigimonMapRow* Map = Data->FindMap(PS->PublicSnapshot.MapId)) Out.Location = Map->DisplayName.ToString();
            else Out.Location = TEXT("Exploring");
        }
        else Out.Location = TEXT("Online");
        const FString OnlineId = Out.AccountId;
        PresenceCache.Add(OnlineId, MoveTemp(Out));
    }
}

FDigimonSocialContact UDigimonVenomNXTSocialSubsystem::MakeContact(const FString& Id) const
{
    RefreshPresenceCache();
    if (const FDigimonSocialContact* Online = PresenceCache.Find(Id)) return *Online;
    FDigimonSocialContact Out; Out.AccountId = Id;
    if (const FDigimonSocialAccountRecord* A = FindAccountById(Id)) Out.Username = A->Username;
    return Out;
}

bool UDigimonVenomNXTSocialSubsystem::Execute(ADigimonVenomNXTPlayerController* Controller, EDigimonSocialAction Action,
    const FString& Target, const FString& Text, const FString& Extra, FString& OutMessage)
{
    FString ActorId, ActorName;
    if (!Authenticate(Controller, ActorId, ActorName)) { OutMessage = TEXT("Please sign in before using social features."); return false; }
    const double NowTime = FPlatformTime::Seconds();
    if (const double* Last = LastActionTimes.Find(ActorId))
        if (NowTime - *Last < 0.35) { OutMessage = TEXT("Please wait a moment before trying again."); return false; }
    LastActionTimes.Add(ActorId, NowTime);
    if (Target.Len() > 128 || Text.Len() > 240 || Extra.Len() > 240) { OutMessage = TEXT("That request is too long."); return false; }
    if (!EnsureLoaded()) { OutMessage = TEXT("Social storage is unavailable. Please ask the host to check the server log."); return false; }
    if (static_cast<uint8>(Action) > static_cast<uint8>(EDigimonSocialAction::ClanUpdate)) { OutMessage = TEXT("Unknown social action."); return false; }

    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    FDigimonSocialDatabase Candidate = Database;
    EnsureAccount(Candidate, ActorId, ActorName);
    for (FDigimonClanRecord& Clan : Candidate.Clans)
        Clan.Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I)
        { return I.ExpiresUnix <= Now || !DigimonVenomNXTSocialCore::CanInvite(static_cast<int>(RoleOf(Clan, I.InviterAccountId))); });

    const bool bAccountTarget = Action <= EDigimonSocialAction::IgnoreRemove || Action == EDigimonSocialAction::ClanInvite ||
        Action == EDigimonSocialAction::ClanKick || Action == EDigimonSocialAction::ClanPromote ||
        Action == EDigimonSocialAction::ClanDemote || Action == EDigimonSocialAction::ClanTransfer;
    FString TargetId, TargetName;
    if (bAccountTarget)
    {
        if (!ResolveAccount(Target, TargetId, TargetName))
        {
            // Deleted accounts remain removable from existing lists by immutable ID.
            const bool bCleanup = Action == EDigimonSocialAction::FriendDecline || Action == EDigimonSocialAction::FriendCancel ||
                Action == EDigimonSocialAction::FriendRemove || Action == EDigimonSocialAction::IgnoreRemove;
            const FDigimonSocialAccountRecord* Retired = bCleanup ? Account(Candidate, Target) : nullptr;
            if (!Retired) { OutMessage = TEXT("No account was found with that name."); return false; }
            TargetId = Retired->AccountId; TargetName = Retired->Username;
        }
        if (TargetId == ActorId) { OutMessage = TEXT("Choose another player for that action."); return false; }
        EnsureAccount(Candidate, TargetId, TargetName);
    }
    FDigimonSocialAccountRecord* Actor = Account(Candidate, ActorId);
    FDigimonSocialAccountRecord* Other = bAccountTarget ? Account(Candidate, TargetId) : nullptr;
    FDigimonClanRecord* Clan = ClanFor(Candidate, ActorId);
    const EDigimonClanRole Role = Clan ? RoleOf(*Clan, ActorId) : EDigimonClanRole::None;
    FString DisbandedClan;
    auto Reject = [&](const TCHAR* Message) { OutMessage = Message; return false; };

    switch (Action)
    {
    case EDigimonSocialAction::FriendRequest:
        if (Blocked(Candidate, ActorId, TargetId)) return Reject(TEXT("This player is not available for social invitations."));
        if (Actor->Friends.Contains(TargetId)) return Reject(TEXT("This player is already on your friends list."));
        if (Actor->IncomingFriends.Contains(TargetId)) return Reject(TEXT("This player has already invited you. Accept their friend request."));
        if (Actor->OutgoingFriends.Contains(TargetId)) return Reject(TEXT("Your friend request is already pending."));
        if (Actor->Friends.Num() >= DigimonVenomNXTSocialCore::MaxFriends || Other->Friends.Num() >= DigimonVenomNXTSocialCore::MaxFriends) return Reject(TEXT("A friends list is full (200 maximum)."));
        if (Actor->OutgoingFriends.Num() >= DigimonVenomNXTSocialCore::MaxFriendRequests || Other->IncomingFriends.Num() >= DigimonVenomNXTSocialCore::MaxFriendRequests)
            return Reject(TEXT("Too many pending friend requests. Clear some requests and try again."));
        Actor->OutgoingFriends.Add(TargetId); Other->IncomingFriends.Add(ActorId);
        OutMessage = FString::Printf(TEXT("Friend request sent to %s."), *TargetName);
        break;
    case EDigimonSocialAction::FriendAccept:
        if (!Actor->IncomingFriends.Contains(TargetId) || !Other->OutgoingFriends.Contains(ActorId)) return Reject(TEXT("That friend request is no longer available."));
        if (Blocked(Candidate, ActorId, TargetId)) return Reject(TEXT("This player is not available for social invitations."));
        if (Actor->Friends.Num() >= DigimonVenomNXTSocialCore::MaxFriends || Other->Friends.Num() >= DigimonVenomNXTSocialCore::MaxFriends) return Reject(TEXT("A friends list is full (200 maximum)."));
        RemoveFriendship(*Actor, *Other);
        Actor->Friends.Add(TargetId); Other->Friends.Add(ActorId);
        OutMessage = FString::Printf(TEXT("You and %s are now friends."), *TargetName);
        break;
    case EDigimonSocialAction::FriendDecline:
        if (!Actor->IncomingFriends.Contains(TargetId)) return Reject(TEXT("That friend request is no longer available."));
        Actor->IncomingFriends.Remove(TargetId); Other->OutgoingFriends.Remove(ActorId);
        OutMessage = TEXT("Friend request declined.");
        break;
    case EDigimonSocialAction::FriendCancel:
        if (!Actor->OutgoingFriends.Contains(TargetId)) return Reject(TEXT("That friend request is no longer pending."));
        Actor->OutgoingFriends.Remove(TargetId); Other->IncomingFriends.Remove(ActorId);
        OutMessage = TEXT("Friend request cancelled.");
        break;
    case EDigimonSocialAction::FriendRemove:
        if (!Actor->Friends.Contains(TargetId)) return Reject(TEXT("This player is not on your friends list."));
        RemoveFriendship(*Actor, *Other);
        OutMessage = TEXT("Player removed from your friends list.");
        break;
    case EDigimonSocialAction::IgnoreAdd:
        if (Actor->Ignored.Contains(TargetId)) return Reject(TEXT("This player is already ignored."));
        if (Actor->Ignored.Num() >= DigimonVenomNXTSocialCore::MaxIgnored) return Reject(TEXT("Your ignore list is full (200 maximum)."));
        Actor->Ignored.Add(TargetId);
        RemoveFriendship(*Actor, *Other);
        for (FDigimonClanRecord& C : Candidate.Clans)
            C.Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I)
            { return (I.AccountId == ActorId && I.InviterAccountId == TargetId) || (I.AccountId == TargetId && I.InviterAccountId == ActorId); });
        OutMessage = FString::Printf(TEXT("%s is ignored. Their chat is hidden and direct invitations and trades are blocked."), *TargetName);
        break;
    case EDigimonSocialAction::IgnoreRemove:
        if (!Actor->Ignored.Contains(TargetId)) return Reject(TEXT("This player is not on your ignore list."));
        Actor->Ignored.Remove(TargetId);
        OutMessage = TEXT("Player removed from your ignore list. Friendship is not restored automatically.");
        break;
    case EDigimonSocialAction::ClanCreate:
    {
        if (Clan) return Reject(TEXT("Leave your current clan before creating another."));
        FString Name, Tag, Description;
        if (!CleanText(Target, 32, Name, false) || !ValidClanName(Name)) return Reject(TEXT("Clan names need 3-32 letters, numbers, spaces, underscores or hyphens."));
        Tag = Text.TrimStartAndEnd().ToUpper();
        if (!ValidTag(Tag)) return Reject(TEXT("Clan tags need 2-5 letters (A-Z) or numbers."));
        if (!CleanText(Extra, 240, Description)) return Reject(TEXT("The description must be at most 240 characters on one line."));
        if (Candidate.Clans.ContainsByPredicate([&](const FDigimonClanRecord& C) { return C.Name.Equals(Name, ESearchCase::IgnoreCase) || C.Tag == Tag; }))
            return Reject(TEXT("That clan name or tag is already in use."));
        if (Candidate.Clans.Num() >= 10000) return Reject(TEXT("The server has reached its clan limit."));
        FDigimonClanRecord New;
        New.ClanId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
        New.Name = Name; New.Tag = Tag; New.Description = Description;
        New.MessageOfTheDay = TEXT("Welcome to the clan!");
        FDigimonClanMemberRecord Leader; Leader.AccountId = ActorId; Leader.Role = EDigimonClanRole::Leader; Leader.JoinedUnix = Now;
        New.Members.Add(Leader);
        Candidate.Clans.Add(MoveTemp(New));
        for (FDigimonClanRecord& C : Candidate.Clans) C.Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.AccountId == ActorId; });
        OutMessage = FString::Printf(TEXT("%s has been created. Welcome, clan leader!"), *Name);
        break;
    }
    case EDigimonSocialAction::ClanDisband:
        if (!Clan || Role != EDigimonClanRole::Leader) return Reject(TEXT("Only the clan leader can disband the clan."));
        if (Target != Clan->ClanId || Text != Clan->Name) return Reject(TEXT("Confirm the exact current clan name to disband it."));
        DisbandedClan = Clan->ClanId;
        Candidate.Clans.RemoveAll([&](const FDigimonClanRecord& C) { return C.ClanId == DisbandedClan; });
        OutMessage = TEXT("The clan has been disbanded. All members are now free to join another clan.");
        break;
    case EDigimonSocialAction::ClanInvite:
    {
        if (!Clan || !DigimonVenomNXTSocialCore::CanInvite(static_cast<int>(Role))) return Reject(TEXT("Only clan leaders and officers can invite players."));
        if (ClanFor(Candidate, TargetId)) return Reject(TEXT("This player already belongs to a clan."));
        if (Blocked(Candidate, ActorId, TargetId)) return Reject(TEXT("This player is not available for clan invitations."));
        if (Clan->Members.Num() >= DigimonVenomNXTSocialCore::MaxClanMembers) return Reject(TEXT("Your clan is full (100 members maximum)."));
        if (Clan->Invitations.ContainsByPredicate([&](const FDigimonClanInvitationRecord& I) { return I.AccountId == TargetId; })) return Reject(TEXT("This player already has an invitation to your clan."));
        if (Clan->Invitations.Num() >= DigimonVenomNXTSocialCore::MaxClanInvitations || InvitationsFor(Candidate, TargetId, Now) >= DigimonVenomNXTSocialCore::MaxAccountClanInvitations)
            return Reject(TEXT("Too many clan invitations are pending."));
        FDigimonClanInvitationRecord Invite; Invite.AccountId = TargetId; Invite.InviterAccountId = ActorId; Invite.ExpiresUnix = Now + 7 * 24 * 60 * 60;
        Clan->Invitations.Add(Invite);
        OutMessage = FString::Printf(TEXT("%s has been invited to your clan. Invitations last seven days."), *TargetName);
        break;
    }
    case EDigimonSocialAction::ClanAccept:
    case EDigimonSocialAction::ClanDecline:
    {
        FDigimonClanRecord* Inviting = Candidate.Clans.FindByPredicate([&](const FDigimonClanRecord& C) { return C.ClanId == Target; });
        if (!Inviting) return Reject(TEXT("That clan invitation is no longer available."));
        const FDigimonClanInvitationRecord* Invite = Inviting->Invitations.FindByPredicate([&](const FDigimonClanInvitationRecord& I) { return I.AccountId == ActorId && I.ExpiresUnix > Now; });
        if (!Invite) return Reject(TEXT("That clan invitation has expired or been withdrawn."));
        if (Action == EDigimonSocialAction::ClanDecline)
        {
            Inviting->Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.AccountId == ActorId; });
            OutMessage = TEXT("Clan invitation declined.");
            break;
        }
        if (Clan) return Reject(TEXT("Leave your current clan before joining another."));
        if (!DigimonVenomNXTSocialCore::CanInvite(static_cast<int>(RoleOf(*Inviting, Invite->InviterAccountId))) || Blocked(Candidate, ActorId, Invite->InviterAccountId))
            return Reject(TEXT("That invitation is no longer available."));
        if (Inviting->Members.Num() >= DigimonVenomNXTSocialCore::MaxClanMembers) return Reject(TEXT("This clan is now full (100 members maximum)."));
        FDigimonClanMemberRecord Member; Member.AccountId = ActorId; Member.Role = EDigimonClanRole::Member; Member.JoinedUnix = Now;
        Inviting->Members.Add(Member);
        OutMessage = FString::Printf(TEXT("Welcome to %s!"), *Inviting->Name);
        for (FDigimonClanRecord& C : Candidate.Clans) C.Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.AccountId == ActorId; });
        break;
    }
    case EDigimonSocialAction::ClanLeave:
        if (!Clan) return Reject(TEXT("You are not currently in a clan."));
        if (!DigimonVenomNXTSocialCore::CanLeave(static_cast<int>(Role))) return Reject(TEXT("Transfer leadership to another member or disband the clan before leaving."));
        Clan->Members.RemoveAll([&](const FDigimonClanMemberRecord& M) { return M.AccountId == ActorId; });
        Clan->Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.InviterAccountId == ActorId; });
        OutMessage = TEXT("You have left the clan.");
        break;
    case EDigimonSocialAction::ClanKick:
    {
        if (!Clan) return Reject(TEXT("You are not currently in a clan."));
        const EDigimonClanRole TargetRole = RoleOf(*Clan, TargetId);
        if (!DigimonVenomNXTSocialCore::CanKick(static_cast<int>(Role), static_cast<int>(TargetRole), ActorId == TargetId)) return Reject(TEXT("You do not have permission to remove that clan member."));
        Clan->Members.RemoveAll([&](const FDigimonClanMemberRecord& M) { return M.AccountId == TargetId; });
        Clan->Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.InviterAccountId == TargetId; });
        OutMessage = FString::Printf(TEXT("%s has been removed from the clan."), *TargetName);
        break;
    }
    case EDigimonSocialAction::ClanPromote:
    case EDigimonSocialAction::ClanDemote:
    {
        if (!Clan) return Reject(TEXT("You are not currently in a clan."));
        const EDigimonClanRole Desired = Action == EDigimonSocialAction::ClanPromote ? EDigimonClanRole::Officer : EDigimonClanRole::Member;
        FDigimonClanMemberRecord* Member = MemberOf(*Clan, TargetId);
        if (!Member || !DigimonVenomNXTSocialCore::CanChangeRole(static_cast<int>(Role), static_cast<int>(Member->Role), static_cast<int>(Desired), ActorId == TargetId))
            return Reject(TEXT("Only the leader can promote members or demote officers."));
        Member->Role = Desired;
        if (Desired == EDigimonClanRole::Member) Clan->Invitations.RemoveAll([&](const FDigimonClanInvitationRecord& I) { return I.InviterAccountId == TargetId; });
        OutMessage = FString::Printf(TEXT("%s is now a clan %s."), *TargetName, Desired == EDigimonClanRole::Officer ? TEXT("officer") : TEXT("member"));
        break;
    }
    case EDigimonSocialAction::ClanTransfer:
    {
        if (!Clan || Role != EDigimonClanRole::Leader) return Reject(TEXT("Only the current leader can transfer clan leadership."));
        if (Text != Clan->Name) return Reject(TEXT("Confirm the exact clan name before transferring leadership."));
        FDigimonClanMemberRecord* Member = MemberOf(*Clan, TargetId);
        if (!Member) return Reject(TEXT("The new leader must already be in your clan."));
        MemberOf(*Clan, ActorId)->Role = EDigimonClanRole::Officer;
        Member->Role = EDigimonClanRole::Leader;
        OutMessage = FString::Printf(TEXT("%s is now the clan leader. You are now an officer."), *TargetName);
        break;
    }
    case EDigimonSocialAction::ClanUpdate:
    {
        if (!Clan || Target != Clan->ClanId || !DigimonVenomNXTSocialCore::CanEditDetails(static_cast<int>(Role))) return Reject(TEXT("Only clan leaders and officers can edit clan details."));
        FString Motd, Description;
        if (!CleanText(Text, 200, Motd) || !CleanText(Extra, 240, Description)) return Reject(TEXT("Use one line: up to 200 characters for the message and 240 for the description."));
        Clan->MessageOfTheDay = Motd; Clan->Description = Description;
        OutMessage = TEXT("Clan details updated.");
        break;
    }
    default: return Reject(TEXT("Unknown social action."));
    }
    if (!Commit(MoveTemp(Candidate), OutMessage)) return false;
    if (!DisbandedClan.IsEmpty()) ClanChatHistory.Remove(DisbandedClan);
    FString TargetNotification;
    if (Action == EDigimonSocialAction::FriendRequest) TargetNotification = ActorName + TEXT(" sent you a friend request. Open SOCIAL to accept or decline.");
    else if (Action == EDigimonSocialAction::FriendAccept) TargetNotification = ActorName + TEXT(" accepted your friend request.");
    else if (Action == EDigimonSocialAction::ClanInvite) TargetNotification = ActorName + TEXT(" invited you to a clan. Open CLANS to accept or decline.");
    else if (Action == EDigimonSocialAction::ClanKick) TargetNotification = TEXT("You have been removed from your clan.");
    else if (Action == EDigimonSocialAction::ClanPromote) TargetNotification = TEXT("You have been promoted to clan officer.");
    else if (Action == EDigimonSocialAction::ClanDemote) TargetNotification = TEXT("Your clan rank has changed to member.");
    else if (Action == EDigimonSocialAction::ClanTransfer) TargetNotification = TEXT("Clan leadership has been transferred to you.");
    if (!TargetNotification.IsEmpty() && GetWorld())
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            ADigimonVenomNXTPlayerController* Recipient = Cast<ADigimonVenomNXTPlayerController>(It->Get());
            if (!Recipient || !Recipient->IsAccountAuthenticated()) continue;
            const ADigimonVenomNXTPlayerState* PS = Recipient->GetPlayerState<ADigimonVenomNXTPlayerState>();
            if (PS && PS->Profile.AccountId == TargetId) Recipient->ClientShowMessage(TEXT("Community"), TargetNotification);
        }
    RefreshConnectedClients();
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::BuildState(ADigimonVenomNXTPlayerController* Controller, FDigimonSocialState& Out) const
{
    FString ActorId, ActorName;
    if (!Authenticate(Controller, ActorId, ActorName) || !const_cast<UDigimonVenomNXTSocialSubsystem*>(this)->EnsureLoaded()) { Out = FDigimonSocialState(); return false; }
    const FDigimonSocialPlayerInfo PreviousInfo = Out.PlayerInfo;
    Out = FDigimonSocialState();
    Out.bReady = true;
    Out.Revision = Database.Revision;
    const FDigimonSocialAccountRecord* Actor = FindAccountById(ActorId);
    if (Actor)
    {
        for (const FString& Id : Actor->Friends) Out.Friends.Add(MakeContact(Id));
        for (const FString& Id : Actor->Ignored) Out.Ignored.Add(MakeContact(Id));
        for (const FString& Id : Actor->IncomingFriends) Out.IncomingFriends.Add(MakeContact(Id));
        for (const FString& Id : Actor->OutgoingFriends) Out.OutgoingFriends.Add(MakeContact(Id));
        SortContacts(Out.Friends); SortContacts(Out.Ignored); SortContacts(Out.IncomingFriends); SortContacts(Out.OutgoingFriends);
    }
    const FDigimonClanRecord* Clan = FindClanByMember(ActorId);
    if (Clan)
    {
        Out.Clan.ClanId = Clan->ClanId; Out.Clan.Name = Clan->Name; Out.Clan.Tag = Clan->Tag;
        Out.Clan.Description = Clan->Description; Out.Clan.MessageOfTheDay = Clan->MessageOfTheDay;
        Out.Clan.YourRole = RoleOf(*Clan, ActorId);
        for (const FDigimonClanMemberRecord& Member : Clan->Members)
        {
            FDigimonClanMemberView View; View.Player = MakeContact(Member.AccountId); View.Role = Member.Role; View.JoinedUnix = Member.JoinedUnix;
            Out.Clan.Members.Add(MoveTemp(View));
        }
        Out.Clan.Members.Sort([](const FDigimonClanMemberView& A, const FDigimonClanMemberView& B)
        {
            if (A.Role != B.Role) return static_cast<int>(A.Role) > static_cast<int>(B.Role);
            if (A.Player.bOnline != B.Player.bOnline) return A.Player.bOnline;
            return A.Player.Username.Compare(B.Player.Username, ESearchCase::IgnoreCase) < 0;
        });
        if (const TArray<FDigimonChatMessage>* Messages = ClanChatHistory.Find(Clan->ClanId))
            for (const FDigimonChatMessage& Message : *Messages)
                if (!IsIgnoring(ActorId, Message.SenderAccountId)) Out.ClanChat.Add(Message);
    }
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    if (const TArray<int32>* InvitingClans = InvitationIndex.Find(ActorId))
        for (int32 ClanIndex : *InvitingClans)
        {
            if (!Database.Clans.IsValidIndex(ClanIndex)) continue;
            const FDigimonClanRecord& C = Database.Clans[ClanIndex];
            for (const FDigimonClanInvitationRecord& I : C.Invitations)
                if (I.AccountId == ActorId && I.ExpiresUnix > Now && DigimonVenomNXTSocialCore::CanInvite(static_cast<int>(RoleOf(C, I.InviterAccountId))) && !IsInteractionBlocked(ActorId, I.InviterAccountId))
                {
                    FDigimonClanInviteView View; View.ClanId = C.ClanId; View.ClanName = C.Name;
                    View.InviterName = MakeContact(I.InviterAccountId).Username; View.ExpiresUnix = I.ExpiresUnix;
                    Out.ClanInvites.Add(MoveTemp(View));
                }
        }
    if (PreviousInfo.bValid)
    {
        Out.PlayerInfo = PreviousInfo;
        FillLivePlayerInfo(Out.PlayerInfo);
        FDigimonSocialContact Current = MakeContact(PreviousInfo.Player.AccountId);
        if (Current.Username.IsEmpty()) Current.Username = PreviousInfo.Player.Username;
        Out.PlayerInfo.Player = MoveTemp(Current);
        Out.PlayerInfo.bFriend = Actor && Actor->Friends.Contains(PreviousInfo.Player.AccountId);
        Out.PlayerInfo.bIgnored = Actor && Actor->Ignored.Contains(PreviousInfo.Player.AccountId);
        Out.PlayerInfo.bIncomingRequest = Actor && Actor->IncomingFriends.Contains(PreviousInfo.Player.AccountId);
        Out.PlayerInfo.bOutgoingRequest = Actor && Actor->OutgoingFriends.Contains(PreviousInfo.Player.AccountId);
        Out.PlayerInfo.ClanName.Reset(); Out.PlayerInfo.ClanTag.Reset(); Out.PlayerInfo.ClanRole = EDigimonClanRole::None;
        if (const FDigimonClanRecord* SelectedClan = FindClanByMember(PreviousInfo.Player.AccountId))
        {
            Out.PlayerInfo.ClanName = SelectedClan->Name; Out.PlayerInfo.ClanTag = SelectedClan->Tag;
            Out.PlayerInfo.ClanRole = RoleOf(*SelectedClan, PreviousInfo.Player.AccountId);
        }
    }
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::GetPlayerInfo(ADigimonVenomNXTPlayerController* Viewer, const FString& Query,
    FDigimonSocialPlayerInfo& Out, FString& OutError) const
{
    Out = FDigimonSocialPlayerInfo();
    FString ActorId, ActorName, Id, Name;
    if (!Authenticate(Viewer, ActorId, ActorName)) { OutError = TEXT("Please sign in first."); return false; }
    if (!const_cast<UDigimonVenomNXTSocialSubsystem*>(this)->EnsureLoaded()) { OutError = TEXT("Social storage is unavailable."); return false; }
    if (!ResolveAccount(Query, Id, Name)) { OutError = TEXT("No account was found with that name."); return false; }
    Out.bValid = true; Out.Player = MakeContact(Id); Out.Player.Username = Name;
    if (const FDigimonSocialAccountRecord* A = FindAccountById(ActorId))
    {
        Out.bFriend = A->Friends.Contains(Id); Out.bIgnored = A->Ignored.Contains(Id);
        Out.bIncomingRequest = A->IncomingFriends.Contains(Id); Out.bOutgoingRequest = A->OutgoingFriends.Contains(Id);
    }
    if (const FDigimonClanRecord* Clan = FindClanByMember(Id))
    {
        Out.ClanName = Clan->Name; Out.ClanTag = Clan->Tag; Out.ClanRole = RoleOf(*Clan, Id);
    }
    FillLivePlayerInfo(Out);
    return true;
}

void UDigimonVenomNXTSocialSubsystem::FillLivePlayerInfo(FDigimonSocialPlayerInfo& Out) const
{
    Out.bUnrankedStatsAvailable = false;
    Out.UnrankedWins = 0; Out.UnrankedLosses = 0; Out.UnrankedDraws = 0;
    Out.EquippedTitle.Reset();
    if (GetWorld()) for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!PC || !PC->IsAccountAuthenticated()) continue;
        const ADigimonVenomNXTPlayerState* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (PS && PS->Profile.AccountId == Out.Player.AccountId)
        {
            Out.EquippedTitle = PS->PublicSnapshot.EquippedTitle;
            Out.bUnrankedStatsAvailable = true;
            Out.UnrankedWins = PS->PublicSnapshot.UnrankedWins;
            Out.UnrankedLosses = PS->PublicSnapshot.UnrankedLosses;
            Out.UnrankedDraws = PS->PublicSnapshot.UnrankedDraws;
            return;
        }
    }
}

bool UDigimonVenomNXTSocialSubsystem::SendClanChat(ADigimonVenomNXTPlayerController* Controller, const FString& Message, FString& OutError)
{
    FString ActorId, ActorName;
    if (!Authenticate(Controller, ActorId, ActorName)) { OutError = TEXT("Please sign in first."); return false; }
    if (!EnsureLoaded()) { OutError = TEXT("Social storage is unavailable."); return false; }
    const FDigimonClanRecord* Clan = FindClanByMember(ActorId);
    if (!Clan) { OutError = TEXT("Join a clan to use clan chat."); return false; }
    const double Now = FPlatformTime::Seconds();
    if (const double* Last = LastChatTimes.Find(ActorId))
        if (Now - *Last < 1.0) { OutError = TEXT("Please wait a moment before sending another clan message."); return false; }
    LastChatTimes.Add(ActorId, Now);
    if (Message.Len() > 2048) { OutError = TEXT("Your message is too long (280 characters maximum)."); return false; }
    const auto Normalized = DigimonVenomNXTWorldChatCore::Normalize(*Message, Message.Len(), 280);
    const FString Clean(Normalized.c_str());
    if (Clean.IsEmpty()) { OutError = TEXT("Type a message first."); return false; }
    FString MuteReason;
    if (UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>())
        if (Console->IsAccountMuted(ActorId, MuteReason)) { OutError = MuteReason; return false; }
    FDigimonChatMessage Chat; Chat.Kind = EDigimonChatMessageKind::Player; Chat.Sender = ActorName;
    Chat.SenderAccountId = ActorId; Chat.Message = Clean; Chat.UnixTime = FDateTime::UtcNow().ToUnixTimestamp();
    TArray<FDigimonChatMessage>& History = ClanChatHistory.FindOrAdd(Clan->ClanId);
    History.Add(MoveTemp(Chat));
    if (History.Num() > 50) History.RemoveAt(0, History.Num() - 50);
    RefreshConnectedClients();
    return true;
}

void UDigimonVenomNXTSocialSubsystem::RefreshConnectedClients()
{
    if (!GetWorld() || GetWorld()->GetNetMode() == NM_Client) return;
    LastPresenceRefresh = -100.0;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get()))
            if (UDigimonVenomNXTSocialComponent* Component = PC->FindComponentByClass<UDigimonVenomNXTSocialComponent>()) Component->RefreshServerState();
}

bool UDigimonVenomNXTSocialSubsystem::WriteDatabase(const FDigimonSocialDatabase& Candidate, FString& OutError)
{
    FString Text;
    const FString Path = SavePath();
    const FString Temporary = Path + TEXT(".tmp");
    if (!FJsonObjectConverter::UStructToJsonObjectString(Candidate, Text))
    { OutError = TEXT("Could not prepare the social update. No changes were made."); return false; }
    // Never commit a file the bounded loader would reject on the next server start.
    const FTCHARToUTF8 Encoded(*Text);
    if (Encoded.Length() > 64ll * 1024 * 1024)
    { OutError = TEXT("The server social database has reached its storage limit. No changes were made."); return false; }
    if (!IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true) ||
        !FFileHelper::SaveStringToFile(Text, *Temporary, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM) ||
        !DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary))
    { OutError = TEXT("Could not save the social update. No changes were made; please try again."); return false; }
    return true;
}

bool UDigimonVenomNXTSocialSubsystem::SaveForHostConsole()
{
    UGameInstance* Instance = GetGameInstance();
    UDigimonVenomNXTServerConsoleSubsystem* Console = Instance ? Instance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    if (!Console || !Console->CanAccess(Instance->GetFirstLocalPlayerController())) return false;
    if (!EnsureLoaded()) return false;
    if (!bDirty) return true;
    FString Error;
    if (!ValidateDatabase(Database) || !WriteDatabase(Database, Error)) return false;
    bDirty = false;
    return true;
}
