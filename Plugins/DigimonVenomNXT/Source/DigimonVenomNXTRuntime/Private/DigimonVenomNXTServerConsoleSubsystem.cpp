#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTServerConsoleCore.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTCampaign.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "JsonObjectConverter.h"
#include "Misc/SecureHash.h"
#include "TimerManager.h"

namespace DigimonServerConsolePrivate
{
FString Clean(const FString& Input, int32 Maximum)
{
    FString Result; Result.Reserve(FMath::Min(Input.Len(), Maximum));
    for (const TCHAR Ch : Input)
    {
        if (Result.Len() >= Maximum) break;
        if (Ch >= 32 && Ch != 127 && Ch != 0x2028 && Ch != 0x2029 && !(Ch >= 0x202A && Ch <= 0x202E) && !(Ch >= 0x2066 && Ch <= 0x2069)) Result.AppendChar(Ch);
        else Result.AppendChar(TEXT(' '));
    }
    return Result.TrimStartAndEnd();
}
}

void UDigimonVenomNXTServerConsoleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    BuildRegistry();
    if (GEngine)
    {
        TravelFailureHandle = GEngine->OnTravelFailure().AddUObject(this, &UDigimonVenomNXTServerConsoleSubsystem::OnTravelFailure);
        NetworkFailureHandle = GEngine->OnNetworkFailure().AddUObject(this, &UDigimonVenomNXTServerConsoleSubsystem::OnNetworkFailure);
    }
}
void UDigimonVenomNXTServerConsoleSubsystem::Deinitialize()
{
    DisarmHostSession();
    if (GEngine)
    {
        GEngine->OnTravelFailure().Remove(TravelFailureHandle);
        GEngine->OnNetworkFailure().Remove(NetworkFailureHandle);
    }
    Super::Deinitialize();
}
void UDigimonVenomNXTServerConsoleSubsystem::ArmHostSession(const FString& AuthenticatedAccountId)
{
    DisarmHostSession();
    const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    if (AuthenticatedAccountId.IsEmpty() || !Auth || !Auth->IsLoggedIn() || Auth->GetAccountId() != AuthenticatedAccountId || !GetGameInstance()->GetFirstGamePlayer()) return;
    HostAccountId = AuthenticatedAccountId;
    HostLocalPlayer = GetGameInstance()->GetFirstGamePlayer();
    Moderation = Cast<UDigimonVenomNXTServerModerationSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("DigimonVenomNXT_ServerModeration"), 0));
    if (!Moderation)
    {
        bModerationLoadFailed = UGameplayStatics::DoesSaveGameExist(TEXT("DigimonVenomNXT_ServerModeration"), 0);
        if (!bModerationLoadFailed) Moderation = NewObject<UDigimonVenomNXTServerModerationSaveGame>(this);
    }
}
void UDigimonVenomNXTServerConsoleSubsystem::DisarmHostSession()
{
    HostAccountId.Reset(); HostLocalPlayer.Reset(); PendingCommand.Reset(); PendingToken.Reset(); PendingFingerprint.Reset(); PendingUntil = 0;
    Entries.Reset(); RecentActivityTimes.Reset(); DetainedMovementModes.Reset(); NextSequence = 1; Moderation = nullptr; bModerationLoadFailed = false;
    if (GetWorld()) { GetWorld()->GetTimerManager().ClearTimer(ModerationTimer); GetWorld()->GetTimerManager().ClearTimer(LifecycleTimer); }
}
void UDigimonVenomNXTServerConsoleSubsystem::OnTravelFailure(UWorld* World, ETravelFailure::Type Failure, const FString& Error)
{
    if (World && World->GetGameInstance() == GetGameInstance()) DisarmHostSession();
}
void UDigimonVenomNXTServerConsoleSubsystem::OnNetworkFailure(UWorld* World, UNetDriver* Driver, ENetworkFailure::Type Failure, const FString& Error)
{
    // A remote connection loss is normal and must not revoke the host. Driver failure is terminal.
    if (World && World->GetGameInstance() == GetGameInstance() && (World->GetNetMode() != NM_ListenServer || Failure == ENetworkFailure::NetDriverCreateFailure || Failure == ENetworkFailure::NetDriverListenFailure)) DisarmHostSession();
}
bool UDigimonVenomNXTServerConsoleSubsystem::IsHostWorld() const
{
    return !HostAccountId.IsEmpty() && HostLocalPlayer.IsValid() && GetWorld() && GetWorld()->GetNetMode() == NM_ListenServer;
}
bool UDigimonVenomNXTServerConsoleSubsystem::CanAccess(const APlayerController* Requester) const
{
    if (!Requester || !GetGameInstance()) return false;
    const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Requester);
    const ADigimonVenomNXTPlayerState* PS = Requester->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    return DigimonVenomNXTServerConsoleCore::Authorized(!HostAccountId.IsEmpty(), IsHostWorld(), Requester->GetWorld() == GetWorld(),
        Requester->GetGameInstance() == GetGameInstance(), Requester->HasAuthority(), Requester->IsLocalController(),
        Requester->GetLocalPlayer() == HostLocalPlayer.Get() && Requester->GetLocalPlayer() == GetGameInstance()->GetFirstGamePlayer(),
        PC && PC->IsAccountAuthenticated() && Auth && Auth->IsLoggedIn(),
        PS && PS->Profile.AccountId == HostAccountId && Auth && Auth->GetAccountId() == HostAccountId);
}
void UDigimonVenomNXTServerConsoleSubsystem::RecordActivity(const FString& Category, const FString& Player, const FString& Action, const FString& Details, const FString& Severity)
{
    if (!IsInGameThread() || !IsHostWorld()) return;
    const FString Key = DigimonServerConsolePrivate::Clean(Category, 32) + TEXT("|") + DigimonServerConsolePrivate::Clean(Player, 64)
        + TEXT("|") + DigimonServerConsolePrivate::Clean(Action, 96) + TEXT("|") + DigimonServerConsolePrivate::Clean(Details, 768);
    const double Now = FPlatformTime::Seconds();
    if (const double* Previous = RecentActivityTimes.Find(Key)) if (Now - *Previous < 0.25) return;
    if (RecentActivityTimes.Num() > 512) RecentActivityTimes.Reset();
    RecentActivityTimes.Add(Key, Now);
    FDigimonServerConsoleEntry Entry;
    Entry.Sequence = NextSequence++; Entry.Timestamp = FDateTime::UtcNow();
    Entry.Category = DigimonServerConsolePrivate::Clean(Category, 32);
    Entry.Player = DigimonServerConsolePrivate::Clean(Player, 64);
    Entry.Action = DigimonServerConsolePrivate::Clean(Action, 96);
    Entry.Details = DigimonServerConsolePrivate::Clean(Details, 768);
    Entry.Severity = Severity == TEXT("Error") || Severity == TEXT("Warning") ? Severity : TEXT("Info");
    Entries.Add(MoveTemp(Entry));
    if (Entries.Num() > 2000) Entries.RemoveAt(0, Entries.Num() - 2000, EAllowShrinking::No);
}
bool UDigimonVenomNXTServerConsoleSubsystem::ReadEntries(const APlayerController* Requester, int64 AfterSequence, int32 Limit, TArray<FDigimonServerConsoleEntry>& OutEntries) const
{
    OutEntries.Reset(); if (!CanAccess(Requester)) return false;
    const int32 BoundedLimit = FMath::Clamp(Limit, 1, 500);
    for (const FDigimonServerConsoleEntry& Entry : Entries)
        if (Entry.Sequence > AfterSequence) { OutEntries.Add(Entry); if (OutEntries.Num() >= BoundedLimit) break; }
    return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::GetStatus(const APlayerController* Requester, FDigimonServerConsoleStatus& OutStatus) const
{
    OutStatus = FDigimonServerConsoleStatus(); if (!CanAccess(Requester)) return false;
    OutStatus.Capacity = GetDefault<UDigimonVenomNXTSettings>()->MaxPlayers;
    OutStatus.RetainedEntries = Entries.Num(); OutStatus.FirstSequence = Entries.IsEmpty() ? NextSequence : Entries[0].Sequence; OutStatus.LatestSequence = NextSequence - 1;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get())) if (PC->IsAccountAuthenticated()) ++OutStatus.OnlinePlayers;
    return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::GetCommandHelp(const APlayerController* Requester, TArray<FDigimonServerCommandInfo>& OutCommands) const
{
    OutCommands.Reset(); if (!CanAccess(Requester)) return false; OutCommands = Registry; return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::ResolveTarget(const FString& Query, FDigimonPlayerProfile& OutProfile, ADigimonVenomNXTPlayerState*& OutLive, FString& OutError) const
{
    OutLive = nullptr;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        ADigimonVenomNXTPlayerState* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        if (PC && PS && !PS->Profile.AccountId.IsEmpty() && (PS->Profile.Username.Equals(Query, ESearchCase::IgnoreCase) || PS->Profile.AccountId == Query))
        {
            if (!PC->IsAccountAuthenticated() || PC->IsLogoutPending())
            { OutError = TEXT("That account is disconnecting or changing session. Wait for it to leave before issuing account commands."); return false; }
            if (OutLive) { OutError = TEXT("That account selector is ambiguous. Use its exact account ID."); return false; }
            OutLive = PS; OutProfile = PS->Profile;
        }
    }
    if (OutLive) return true;
    FString Username, AccountId;
    UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Auth || !Auth->AdminResolveAccount(Query, Username, AccountId, OutError)) return false;
    if (!Profiles || !Profiles->LoadProfile(AccountId, Username, OutProfile)) { OutError = TEXT("That account profile could not be loaded."); return false; }
    return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::RequireMutable(const FDigimonPlayerProfile& Profile, const ADigimonVenomNXTPlayerState* Live, FString& OutError) const
{
    const ADigimonVenomNXTPlayerController* PC = Live ? Cast<ADigimonVenomNXTPlayerController>(Live->GetOwner()) : nullptr;
    if (PC && (!PC->IsAccountAuthenticated() || PC->IsLogoutPending()))
    { OutError = TEXT("That account is changing session. Its profile cannot be modified until sign-out finishes."); return false; }
    if ((Live && Live->HasActiveBattle()) || (PC && PC->CurrentBattle) ||
        !Profile.WorldBattleCheckpointJson.IsEmpty() || !Profile.Season.BattleCheckpointJson.IsEmpty() || DigimonVenomNXTCampaign::HasPendingBattle(Profile))
    { OutError = TEXT("Finish and close the live or saved battle before changing this profile."); return false; }
    return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::CommitProfile(FDigimonPlayerProfile& Candidate, ADigimonVenomNXTPlayerState* Live, FString& OutError)
{
    if (!RequireMutable(Candidate, Live, OutError)) return false;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    const bool Committed = DigimonVenomNXTServerConsoleCore::Commit(Candidate,
        [Profiles](FDigimonPlayerProfile& Value) { return Profiles && Profiles->SaveProfile(Value); },
        [Live](FDigimonPlayerProfile& Value) { if (Live) { Live->Profile = MoveTemp(Value); Live->MarkProfileChanged(); } });
    if (!Committed) OutError = TEXT("Save failed. The live profile was not changed. Check available disk space and save permissions.");
    return Committed;
}
bool UDigimonVenomNXTServerConsoleSubsystem::SaveModeration(UDigimonVenomNXTServerModerationSaveGame* Candidate, FString& OutError)
{
    if (bModerationLoadFailed) { OutError = TEXT("Existing moderation data could not be read. Restore its save backup before changing restrictions or titles."); return false; }
    if (!Candidate || !UGameplayStatics::SaveGameToSlot(Candidate, TEXT("DigimonVenomNXT_ServerModeration"), 0)) { OutError = TEXT("The moderation database could not be saved. Nothing changed."); return false; }
    Moderation = Candidate; return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::IsAccountBanned(const FString& AccountId, FString& OutReason) const
{
    if (bModerationLoadFailed && IsHostWorld() && AccountId != HostAccountId)
    { OutReason = TEXT("The host moderation database needs repair. New remote logins are temporarily unavailable."); return true; }
    OutReason.Reset(); if (!Moderation || !IsHostWorld()) return false;
    const FDigimonServerModerationRecord* Record = Moderation->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& Item) { return Item.AccountId == AccountId; });
    if (!Record || !DigimonVenomNXTServerConsoleCore::ActiveUntil(Record->BannedUntil, FDateTime::UtcNow().ToUnixTimestamp())) return false;
    OutReason = Record->BanReason; return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::IsAccountMuted(const FString& AccountId, FString& OutReason) const
{
    OutReason.Reset(); if (!Moderation || !IsHostWorld()) return false;
    const FDigimonServerModerationRecord* Record = Moderation->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& Item) { return Item.AccountId == AccountId; });
    if (!Record || !DigimonVenomNXTServerConsoleCore::ActiveUntil(Record->MutedUntil, FDateTime::UtcNow().ToUnixTimestamp())) return false;
    OutReason = Record->MuteReason; return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::IsAccountJailed(const FString& AccountId, FString& OutReason) const
{
    OutReason.Reset(); if (!Moderation || !IsHostWorld()) return false;
    const FDigimonServerModerationRecord* Record = Moderation->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& Item) { return Item.AccountId == AccountId; });
    if (!Record || !DigimonVenomNXTServerConsoleCore::ActiveUntil(Record->JailedUntil, FDateTime::UtcNow().ToUnixTimestamp())) return false;
    OutReason = Record->JailReason; return true;
}
void UDigimonVenomNXTServerConsoleSubsystem::ApplyModerationToPlayer(ADigimonVenomNXTPlayerController* Player)
{
    if (!IsHostWorld() || !Player || !Player->HasAuthority()) return;
    if (bModerationLoadFailed && Player->IsLocalController())
    {
        RecordActivity(TEXT("Server"), TEXT("Host"), TEXT("Moderation save unreadable"), TEXT("Remote logins are blocked until the existing moderation save is repaired. It has not been overwritten."), TEXT("Error"));
        Player->ClientShowMessage(TEXT("Moderation save needs repair"), TEXT("The existing moderation database could not be loaded. Remote sign-ins and moderation changes are blocked; restore a known good backup."));
    }
    if (GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(ModerationTimer)) GetWorld()->GetTimerManager().SetTimer(ModerationTimer, this, &UDigimonVenomNXTServerConsoleSubsystem::RefreshModeration, 1.0f, true);
    ADigimonVenomNXTPlayerState* PS = Player->GetPlayerState<ADigimonVenomNXTPlayerState>();
    ACharacter* Character = Cast<ACharacter>(Player->GetPawn());
    if (!PS || !Character || !Character->GetCharacterMovement()) return;
    FString Reason;
    if (IsAccountJailed(PS->Profile.AccountId, Reason))
    {
        const TWeakObjectPtr<ACharacter> Key(Character);
        if (!DetainedMovementModes.Contains(Key)) DetainedMovementModes.Add(Key,
            TPair<uint8, uint8>(static_cast<uint8>(Character->GetCharacterMovement()->MovementMode), Character->GetCharacterMovement()->CustomMovementMode));
        Character->GetCharacterMovement()->StopMovementImmediately(); Character->GetCharacterMovement()->DisableMovement();
        Player->ClientShowMessage(TEXT("Account detained"), TEXT("Gameplay is suspended by the host. Your location and progress are preserved. Reason: ") + Reason);
    }
    else
    {
        const TWeakObjectPtr<ACharacter> Key(Character);
        if (const TPair<uint8, uint8>* Previous = DetainedMovementModes.Find(Key))
        {
            Character->GetCharacterMovement()->SetMovementMode(static_cast<EMovementMode>(Previous->Key), Previous->Value);
            DetainedMovementModes.Remove(Key);
        }
    }
}
void UDigimonVenomNXTServerConsoleSubsystem::RefreshModeration()
{
    if (!IsHostWorld()) return;
    for (auto It = DetainedMovementModes.CreateIterator(); It; ++It) if (!It.Key().IsValid()) It.RemoveCurrent();
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        ADigimonVenomNXTPlayerState* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        if (!PS || !Moderation) continue;
        FDigimonServerModerationRecord* Record = Moderation->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& Value) { return Value.AccountId == PS->Profile.AccountId; });
        if (Record && Record->JailedUntil > 0 && Record->JailedUntil <= FDateTime::UtcNow().ToUnixTimestamp())
        {
            Record->JailedUntil = 0; ApplyModerationToPlayer(PC);
            PC->ClientShowMessage(TEXT("Detention ended"), TEXT("You may continue playing."));
            RecordActivity(TEXT("Moderation"), PS->Profile.Username, TEXT("Detention expired"), TEXT("Gameplay restored."));
        }
    }
}

bool UDigimonVenomNXTServerConsoleSubsystem::TryRestoreLocalHostIdentity(ADigimonVenomNXTPlayerController* Requester, FString& OutUsername, FString& OutAccountId) const
{
    OutUsername.Reset(); OutAccountId.Reset();
    const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr;
    if (!Requester || !IsHostWorld() || Requester->GetWorld() != GetWorld() || Requester->GetGameInstance() != GetGameInstance()
        || !Requester->HasAuthority() || !Requester->IsLocalController() || Requester->GetLocalPlayer() != HostLocalPlayer.Get()
        || Requester->GetLocalPlayer() != GetGameInstance()->GetFirstGamePlayer() || !Auth || !Auth->IsLoggedIn() || Auth->GetAccountId() != HostAccountId) return false;
    OutUsername = Auth->GetUsername(); OutAccountId = HostAccountId; return true;
}
