#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/SaveGame.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTServerConsoleSubsystem.generated.h"

class APlayerController;
class ACharacter;
class ADigimonVenomNXTPlayerController;
class ADigimonVenomNXTPlayerState;
class ULocalPlayer;
class UNetDriver;

/** Native-only local view. No console record, command or capability is replicated. */
struct DIGIMONVENOMNXTRUNTIME_API FDigimonServerConsoleEntry
{
    int64 Sequence = 0;
    FDateTime Timestamp;
    FString Severity, Category, Player, Action, Details;
};
struct DIGIMONVENOMNXTRUNTIME_API FDigimonServerCommandInfo
{
    FString Name, Usage, Description;
    bool bRequiresConfirmation = false;
};
struct DIGIMONVENOMNXTRUNTIME_API FDigimonServerConsoleStatus
{
    int32 OnlinePlayers = 0;
    int32 Capacity = 0;
    int32 RetainedEntries = 0;
    int64 FirstSequence = 0;
    int64 LatestSequence = 0;
};
USTRUCT()
struct FDigimonServerModerationRecord
{
    GENERATED_BODY()
    UPROPERTY(SaveGame) FString AccountId;
    UPROPERTY(SaveGame) FString Username;
    /** Zero means absent; -1 means permanent. Positive values are UTC Unix expiry. */
    UPROPERTY(SaveGame) int64 BannedUntil = 0;
    UPROPERTY(SaveGame) int64 MutedUntil = 0;
    UPROPERTY(SaveGame) int64 JailedUntil = 0;
    UPROPERTY(SaveGame) FString BanReason;
    UPROPERTY(SaveGame) FString MuteReason;
    UPROPERTY(SaveGame) FString JailReason;
    UPROPERTY(SaveGame) TArray<FString> Warnings;
};
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTServerModerationSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(SaveGame) int32 Version = 1;
    UPROPERTY(SaveGame) TArray<FDigimonServerModerationRecord> Accounts;
    UPROPERTY(SaveGame) TArray<FString> Titles;
};

/** Host-and-play console. Intentionally no Blueprint execution, RPC, Exec or chat entry point. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTServerConsoleSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    bool CanAccess(const APlayerController* Requester) const;
    bool ExecuteSensitiveCommand(APlayerController* Requester, const FString& Verb, const FString& Username, const FString& Password, FString& OutResponse);
    bool TryRestoreLocalHostIdentity(ADigimonVenomNXTPlayerController* Requester, FString& OutUsername, FString& OutAccountId) const;
    bool ExecuteCommand(APlayerController* Requester, const FString& Command, FString& OutResponse);
    bool ReadEntries(const APlayerController* Requester, int64 AfterSequence, int32 Limit, TArray<FDigimonServerConsoleEntry>& OutEntries) const;
    bool GetCommandHelp(const APlayerController* Requester, TArray<FDigimonServerCommandInfo>& OutCommands) const;
    bool GetStatus(const APlayerController* Requester, FDigimonServerConsoleStatus& OutStatus) const;
    void RecordActivity(const FString& Category, const FString& Player, const FString& Action, const FString& Details, const FString& Severity = TEXT("Info"));
    bool IsAccountBanned(const FString& AccountId, FString& OutReason) const;
    bool IsAccountMuted(const FString& AccountId, FString& OutReason) const;
    bool IsAccountJailed(const FString& AccountId, FString& OutReason) const;
    void ApplyModerationToPlayer(ADigimonVenomNXTPlayerController* Player);
    /** Authenticated local admin only; includes disconnected profiles and pending server ledgers. */
    bool SaveAll(FString& OutResponse);

private:
    friend class UDigimonVenomNXTGameInstance;
    friend class UDigimonVenomNXTAuthSubsystem;
    void ArmHostSession(const FString& AuthenticatedAccountId);
    void DisarmHostSession();
    bool IsHostWorld() const;
    bool bModerationLoadFailed = false;
    FString HostAccountId;
    TWeakObjectPtr<ULocalPlayer> HostLocalPlayer;
    TArray<FDigimonServerConsoleEntry> Entries;
    int64 NextSequence = 1;
    TArray<FDigimonServerCommandInfo> Registry;
    TMap<FString, double> RecentActivityTimes;
    TMap<TWeakObjectPtr<ACharacter>, TPair<uint8, uint8>> DetainedMovementModes;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTServerModerationSaveGame> Moderation;
    FString PendingCommand;
    FString PendingToken;
    FString PendingFingerprint;
    double PendingUntil = 0;
    FDelegateHandle NetworkFailureHandle, TravelFailureHandle;
    FTimerHandle ModerationTimer;
    FTimerHandle LifecycleTimer;
    bool bRestartScheduled = false;
    void RefreshModeration();
    void OnTravelFailure(UWorld* World, ETravelFailure::Type Failure, const FString& Error);
    void OnNetworkFailure(UWorld* World, UNetDriver* Driver, ENetworkFailure::Type Failure, const FString& Error);
    void BuildRegistry();
    bool RunCommand(APlayerController* Requester, const TArray<FString>& Args, FString& OutResponse, bool bConfirmed);
    bool ResolveTarget(const FString& Query, FDigimonPlayerProfile& OutProfile, ADigimonVenomNXTPlayerState*& OutLive, FString& OutError) const;
    bool CommitProfile(FDigimonPlayerProfile& Candidate, ADigimonVenomNXTPlayerState* Live, FString& OutError);
    bool RequireMutable(const FDigimonPlayerProfile& Profile, const ADigimonVenomNXTPlayerState* Live, FString& OutError) const;
    bool SaveModeration(UDigimonVenomNXTServerModerationSaveGame* Candidate, FString& OutError);

    bool PrepareConfirmation(const TArray<FString>& Args, const FString& Fingerprint, FString& OutResponse);
    FString ConfirmationFingerprint(const TArray<FString>& Args) const;
    void FinishLifecycle();
};
