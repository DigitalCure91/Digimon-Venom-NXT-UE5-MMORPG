#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTAuthSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDigimonAuthResultEvent, const FDigimonAuthResult&, Result);

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAccountRecord
{
    GENERATED_BODY()

    UPROPERTY(SaveGame, BlueprintReadOnly)
    FString AccountId;

    UPROPERTY(SaveGame, BlueprintReadOnly)
    FString Username;

    UPROPERTY(SaveGame)
    FString Salt;

    UPROPERTY(SaveGame)
    FString PasswordHash;

    UPROPERTY(SaveGame)
    int32 HashIterations = 120000;

    UPROPERTY(SaveGame, BlueprintReadOnly)
    int64 CreatedUnix = 0;
};

/** Host-owned Unreal SaveGame database for Digimon Venom NXT accounts. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAccountSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(SaveGame)
    TArray<FDigimonAccountRecord> Accounts;
};

/**
 * Pure Unreal Engine account subsystem.
 *
 * There is deliberately no HTTP account service, auth URL, auth TCP port,
 * signed session token, signing secret, web endpoint or external backend.
 * The authoritative host stores accounts in an Unreal SaveGame slot and
 * validates Create/Login requests received over the normal UE gameplay connection.
 */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAuthSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Accounts")
    FDigimonAuthResultEvent OnAuthResult;

    /** Stages credentials for creating an account on the host when Host/Join is selected. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Accounts")
    void CreateAccount(const FString& Username, const FString& Password);

    /** Stages credentials for logging into the host when Host/Join is selected. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Accounts")
    void Login(const FString& Username, const FString& Password);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Accounts")
    void Logout();

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool IsLoggedIn() const { return bAuthenticated; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool HasPendingCredentials() const { return bHasPendingCredentials && !PendingUsername.IsEmpty() && !PendingPassword.IsEmpty(); }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool IsPendingCreateAccount() const { return bPendingCreateAccount; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    FString GetUsername() const { return !LoggedInUsername.IsEmpty() ? LoggedInUsername : PendingUsername; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    FString GetAccountId() const { return LoggedInAccountId; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    FString GetLastAuthMessage() const { return LastAuthMessage; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    bool WasLastAuthSuccessful() const { return bLastAuthSuccessful; }

    /** Returns the staged credentials to the local player controller. Password remains memory-only. */
    bool GetPendingCredentials(bool& bOutCreateAccount, FString& OutUsername, FString& OutPassword) const;

    /** Called by the client after the authoritative UE server accepts or rejects account authentication. */
    void ApplyServerAuthResult(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId);

    /**
     * Authoritative host-only account operation. Loads/saves the UE SaveGame account database.
     * This does not alter the subsystem's local-player login state when authenticating a remote client.
     */
    bool AuthenticateServerCredentials(bool bCreateAccount, const FString& Username, const FString& Password,
        FString& OutUsername, FString& OutAccountId, FString& OutError);

    /** Host-and-play path: validate/create the local host account before opening the listen world. */
    bool AuthenticateLocalHost(FString& OutError);

    /** Local listen-host console only. Never returns password hashes, salts or staged credentials. */
    bool AdminResolveAccount(const FString& Query, FString& OutUsername, FString& OutAccountId, FString& OutError) const;
    bool AdminCreateAccount(const FString& Username, const FString& Password, FString& OutError);
    bool AdminResetPassword(const FString& Query, const FString& NewPassword, FString& OutError);
    /** Removes an offline account record; profile storage is handled by the console transaction. */
    bool AdminDeleteAccount(const FString& Query, FString& OutError);
    /** Server-only public identity lookup; callers authenticate their requesting connection. */
    bool GetAccountIdentity(const FString& Query, FString& OutUsername, FString& OutAccountId) const;

    /** SaveGame slot name containing the host's account database. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Accounts")
    static FString GetAccountSaveSlotName() { return TEXT("DigimonVenomNXT_Accounts"); }

private:
    FString LoggedInUsername;
    FString LoggedInAccountId;
    FString PendingUsername;
    FString PendingPassword;
    FString LastAuthMessage;
    bool bAuthenticated = false;
    bool bHasPendingCredentials = false;
    bool bPendingCreateAccount = false;
    bool bLastAuthSuccessful = false;

    bool StageCredentials(bool bCreateAccount, const FString& Username, const FString& Password, FDigimonAuthResult& OutResult);
    UDigimonVenomNXTAccountSaveGame* LoadAccountSave() const;
    bool SaveAccountSave(UDigimonVenomNXTAccountSaveGame* SaveGame, FString& OutError) const;
    static FDigimonAccountRecord* FindAccount(UDigimonVenomNXTAccountSaveGame* SaveGame, const FString& Username);
    static const FDigimonAccountRecord* FindAccount(const UDigimonVenomNXTAccountSaveGame* SaveGame, const FString& Username);
    static bool IsValidUsername(const FString& Username);
    bool RequireLocalHostConsole(FString& OutError) const;
};
