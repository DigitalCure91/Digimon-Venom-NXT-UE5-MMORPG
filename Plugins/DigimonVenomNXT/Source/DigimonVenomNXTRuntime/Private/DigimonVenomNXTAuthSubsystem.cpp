#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTCrypto.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTTradeSubsystem.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DigimonVenomNXTRuntime.h"
#include "Kismet/GameplayStatics.h"

void UDigimonVenomNXTAuthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UDigimonVenomNXTAuthSubsystem::Deinitialize()
{
    PendingPassword.Reset();
    Super::Deinitialize();
}

bool UDigimonVenomNXTAuthSubsystem::IsValidUsername(const FString& Username)
{
    if (Username.Len() < 3 || Username.Len() > 24) return false;
    for (const TCHAR C : Username)
    {
        if (!(FChar::IsAlnum(C) || C == TEXT('_'))) return false;
    }
    return true;
}

bool UDigimonVenomNXTAuthSubsystem::StageCredentials(bool bCreateAccount, const FString& Username, const FString& Password, FDigimonAuthResult& OutResult)
{
    if (UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
    bHasPendingCredentials = false;
    PendingPassword.Reset();
    FString CleanUsername = Username;
    CleanUsername.TrimStartAndEndInline();

    if (!IsValidUsername(CleanUsername))
    {
        OutResult.Message = TEXT("Username must be 3-24 characters using letters, numbers, or underscore.");
        return false;
    }
    if (Password.Len() < 8 || Password.Len() > 128)
    {
        OutResult.Message = TEXT("Password must be 8-128 characters.");
        return false;
    }

    PendingUsername = CleanUsername;
    PendingPassword = Password;
    bPendingCreateAccount = bCreateAccount;
    bHasPendingCredentials = true;
    bAuthenticated = false;
    LoggedInUsername.Reset();
    LoggedInAccountId.Reset();

    OutResult.bSuccess = true;
    OutResult.Username = CleanUsername;
    OutResult.Message = bCreateAccount
        ? TEXT("Account details ready. Choose Host or Join; the UE host will create the account in its SaveGame database.")
        : TEXT("Login details ready. Choose Host or Join; the UE host will validate the account in its SaveGame database.");
    LastAuthMessage = OutResult.Message;
    bLastAuthSuccessful = true;
    return true;
}

void UDigimonVenomNXTAuthSubsystem::CreateAccount(const FString& Username, const FString& Password)
{
    FDigimonAuthResult Result;
    StageCredentials(true, Username, Password, Result);
    LastAuthMessage = Result.Message;
    bLastAuthSuccessful = Result.bSuccess;
    OnAuthResult.Broadcast(Result);
}

void UDigimonVenomNXTAuthSubsystem::Login(const FString& Username, const FString& Password)
{
    FDigimonAuthResult Result;
    StageCredentials(false, Username, Password, Result);
    LastAuthMessage = Result.Message;
    bLastAuthSuccessful = Result.bSuccess;
    OnAuthResult.Broadcast(Result);
}

void UDigimonVenomNXTAuthSubsystem::Logout()
{
    if (UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
    LoggedInUsername.Reset();
    LoggedInAccountId.Reset();
    PendingUsername.Reset();
    PendingPassword.Reset();
    LastAuthMessage.Reset();
    bAuthenticated = false;
    bHasPendingCredentials = false;
    bPendingCreateAccount = false;
    bLastAuthSuccessful = false;
}

bool UDigimonVenomNXTAuthSubsystem::GetPendingCredentials(bool& bOutCreateAccount, FString& OutUsername, FString& OutPassword) const
{
    if (!HasPendingCredentials()) return false;
    bOutCreateAccount = bPendingCreateAccount;
    OutUsername = PendingUsername;
    OutPassword = PendingPassword;
    return true;
}

void UDigimonVenomNXTAuthSubsystem::ApplyServerAuthResult(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId)
{
    FDigimonAuthResult Result;
    Result.bSuccess = bSuccess;
    Result.Message = Message;
    Result.Username = Username;
    Result.AccountId = AccountId;
    LastAuthMessage = Message;
    bLastAuthSuccessful = bSuccess;

    if (bSuccess)
    {
        bAuthenticated = true;
        LoggedInUsername = Username;
        LoggedInAccountId = AccountId;
        PendingPassword.Reset();
        bHasPendingCredentials = false;
    }
    else
    {
        if (UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
        bAuthenticated = false;
        LoggedInAccountId.Reset();
        PendingPassword.Reset();
        bHasPendingCredentials = false;
    }

    OnAuthResult.Broadcast(Result);
}

UDigimonVenomNXTAccountSaveGame* UDigimonVenomNXTAuthSubsystem::LoadAccountSave() const
{
    const FString Slot = GetAccountSaveSlotName();
    if (UGameplayStatics::DoesSaveGameExist(Slot, 0))
    {
        if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(Slot, 0))
        {
            if (UDigimonVenomNXTAccountSaveGame* Accounts = Cast<UDigimonVenomNXTAccountSaveGame>(Loaded)) return Accounts;
        }
        // An unreadable existing account database must never become a blank database.
        return nullptr;
    }
    return Cast<UDigimonVenomNXTAccountSaveGame>(UGameplayStatics::CreateSaveGameObject(UDigimonVenomNXTAccountSaveGame::StaticClass()));
}

bool UDigimonVenomNXTAuthSubsystem::SaveAccountSave(UDigimonVenomNXTAccountSaveGame* SaveGame, FString& OutError) const
{
    if (!SaveGame)
    {
        OutError = TEXT("Could not create the Digimon Venom NXT account SaveGame.");
        return false;
    }
    if (!UGameplayStatics::SaveGameToSlot(SaveGame, GetAccountSaveSlotName(), 0))
    {
        OutError = TEXT("Could not save the Digimon Venom NXT account database.");
        return false;
    }
    return true;
}

FDigimonAccountRecord* UDigimonVenomNXTAuthSubsystem::FindAccount(UDigimonVenomNXTAccountSaveGame* SaveGame, const FString& Username)
{
    if (!SaveGame) return nullptr;
    for (FDigimonAccountRecord& Record : SaveGame->Accounts)
    {
        if (Record.Username.Equals(Username, ESearchCase::IgnoreCase)) return &Record;
    }
    return nullptr;
}

const FDigimonAccountRecord* UDigimonVenomNXTAuthSubsystem::FindAccount(const UDigimonVenomNXTAccountSaveGame* SaveGame, const FString& Username)
{
    if (!SaveGame) return nullptr;
    for (const FDigimonAccountRecord& Record : SaveGame->Accounts)
    {
        if (Record.Username.Equals(Username, ESearchCase::IgnoreCase)) return &Record;
    }
    return nullptr;
}

bool UDigimonVenomNXTAuthSubsystem::AuthenticateServerCredentials(bool bCreateAccount, const FString& Username, const FString& Password,
    FString& OutUsername, FString& OutAccountId, FString& OutError)
{
    FString CleanUsername = Username;
    CleanUsername.TrimStartAndEndInline();
    if (!IsValidUsername(CleanUsername))
    {
        OutError = TEXT("Username must be 3-24 characters using letters, numbers, or underscore.");
        return false;
    }
    if (Password.Len() < 8 || Password.Len() > 128)
    {
        OutError = TEXT("Password must be 8-128 characters.");
        return false;
    }

    UDigimonVenomNXTAccountSaveGame* Save = LoadAccountSave();
    if (!Save)
    {
        OutError = TEXT("Could not load the Digimon Venom NXT account SaveGame.");
        return false;
    }

    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    FDigimonAccountRecord* Existing = FindAccount(Save, CleanUsername);

    if (bCreateAccount)
    {
        if (Existing)
        {
            OutError = TEXT("That username already exists on this Digimon Venom NXT host.");
            return false;
        }

        FDigimonAccountRecord NewRecord;
        NewRecord.AccountId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
        NewRecord.Username = CleanUsername;
        NewRecord.Salt = FDigimonVenomNXTCrypto::NewSalt();
        NewRecord.HashIterations = Settings->PasswordHashIterations;
        NewRecord.PasswordHash = FDigimonVenomNXTCrypto::PBKDF2(Password, NewRecord.Salt, NewRecord.HashIterations);
        NewRecord.CreatedUnix = FDateTime::UtcNow().ToUnixTimestamp();
        Save->Accounts.Add(NewRecord);
        if (!SaveAccountSave(Save, OutError)) return false;

        OutUsername = NewRecord.Username;
        OutAccountId = NewRecord.AccountId;
        return true;
    }

    if (!Existing)
    {
        OutError = TEXT("Invalid username or password.");
        return false;
    }

    const int32 Iterations = Existing->HashIterations > 0 ? Existing->HashIterations : Settings->PasswordHashIterations;
    const FString Candidate = FDigimonVenomNXTCrypto::PBKDF2(Password, Existing->Salt, Iterations);
    if (!FDigimonVenomNXTCrypto::ConstantTimeEquals(Candidate, Existing->PasswordHash))
    {
        OutError = TEXT("Invalid username or password.");
        return false;
    }

    OutUsername = Existing->Username;
    OutAccountId = Existing->AccountId;
    return true;
}

bool UDigimonVenomNXTAuthSubsystem::AuthenticateLocalHost(FString& OutError)
{
    bool bCreate = false;
    FString Username, Password;
    if (!GetPendingCredentials(bCreate, Username, Password))
    {
        OutError = TEXT("Enter a username/password and choose Create Account or Log In first.");
        return false;
    }

    FString AuthenticatedUsername, AccountId;
    if (!AuthenticateServerCredentials(bCreate, Username, Password, AuthenticatedUsername, AccountId, OutError)) return false;

    bAuthenticated = true;
    LoggedInUsername = AuthenticatedUsername;
    LoggedInAccountId = AccountId;
    LastAuthMessage = bCreate ? TEXT("Host account created in the UE SaveGame database.") : TEXT("Host account login successful.");
    bLastAuthSuccessful = true;
    // The account now exists, so the PublicWorld authentication pass must log in rather than try to create it again.
    bPendingCreateAccount = false;
    // Keep the pending password only until the local listen-server PlayerController authenticates itself.
    return true;
}

bool UDigimonVenomNXTAuthSubsystem::RequireLocalHostConsole(FString& OutError) const
{
    OutError.Reset();
    UGameInstance* GI = GetGameInstance();
    const UDigimonVenomNXTServerConsoleSubsystem* Console = GI ? GI->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    if (!Console || !Console->CanAccess(GI->GetFirstLocalPlayerController()))
    {
        OutError = TEXT("Account management is available only in the authenticated local host console.");
        return false;
    }
    return true;
}

bool UDigimonVenomNXTAuthSubsystem::AdminResolveAccount(const FString& Query, FString& OutUsername, FString& OutAccountId, FString& OutError) const
{
    OutUsername.Reset(); OutAccountId.Reset();
    if (!RequireLocalHostConsole(OutError)) return false;
    FString Clean = Query; Clean.TrimStartAndEndInline();
    if (Clean.IsEmpty() || Clean.Len() > 128) { OutError = TEXT("Enter an account username or account ID."); return false; }
    const UDigimonVenomNXTAccountSaveGame* Save = LoadAccountSave();
    if (!Save) { OutError = TEXT("The account database could not be read. No records were changed."); return false; }
    int32 Matches = 0;
    for (const FDigimonAccountRecord& Record : Save->Accounts)
    {
        if (Record.Username.Equals(Clean, ESearchCase::IgnoreCase) || Record.AccountId.Equals(Clean, ESearchCase::IgnoreCase))
        {
            OutUsername = Record.Username; OutAccountId = Record.AccountId;
            ++Matches;
        }
    }
    if (Matches == 1) return true;
    OutUsername.Reset(); OutAccountId.Reset();
    if (Matches > 1) { OutError = TEXT("The account identifier is ambiguous. No account was selected or changed."); return false; }
    OutError = TEXT("No account matches that username or account ID on this host.");
    return false;
}

bool UDigimonVenomNXTAuthSubsystem::GetAccountIdentity(const FString& Query, FString& OutUsername, FString& OutAccountId) const
{
    OutUsername.Reset(); OutAccountId.Reset();
    // Read-only authority lookup used by authenticated social/trade requests.
    // No local administrator session is required and no credentials are returned.
    if (!GetWorld() || GetWorld()->GetNetMode() == NM_Client || Query.Len() > 128) return false;
    const FString Clean = Query.TrimStartAndEnd();
    if (Clean.IsEmpty()) return false;
    const UDigimonVenomNXTAccountSaveGame* Save = LoadAccountSave();
    if (!Save) return false;
    int32 Matches = 0;
    for (const FDigimonAccountRecord& Record : Save->Accounts)
        if (Record.Username.Equals(Clean, ESearchCase::IgnoreCase) || Record.AccountId.Equals(Clean, ESearchCase::IgnoreCase))
        {
            OutUsername = Record.Username; OutAccountId = Record.AccountId; ++Matches;
        }
    if (Matches == 1) return true;
    OutUsername.Reset(); OutAccountId.Reset();
    return false;
}

bool UDigimonVenomNXTAuthSubsystem::AdminCreateAccount(const FString& Username, const FString& Password, FString& OutError)
{
    if (!RequireLocalHostConsole(OutError)) return false;
    FString CreatedUsername, CreatedAccountId;
    // This method changes only the host database, never the local host's login state.
    return AuthenticateServerCredentials(true, Username, Password, CreatedUsername, CreatedAccountId, OutError);
}

bool UDigimonVenomNXTAuthSubsystem::AdminResetPassword(const FString& Query, const FString& NewPassword, FString& OutError)
{
    FString Username, AccountId;
    if (!AdminResolveAccount(Query, Username, AccountId, OutError)) return false;
    if (AccountId == LoggedInAccountId) { OutError = TEXT("The active host account password cannot be reset from this session."); return false; }
    const AGameStateBase* State = GetWorld() ? GetWorld()->GetGameState() : nullptr;
    if (!State) { OutError = TEXT("The connected-player list is unavailable. No password was changed."); return false; }
    for (const APlayerState* Player : State->PlayerArray)
    {
        const ADigimonVenomNXTPlayerState* DigimonPlayer = Cast<ADigimonVenomNXTPlayerState>(Player);
        if (DigimonPlayer && DigimonPlayer->Profile.AccountId == AccountId)
        {
            OutError = TEXT("That account is connected. Ask the player to log out before resetting its password.");
            return false;
        }
    }
    if (NewPassword.Len() < 8 || NewPassword.Len() > 128) { OutError = TEXT("Password must be 8-128 characters."); return false; }
    UDigimonVenomNXTAccountSaveGame* Save = LoadAccountSave();
    FDigimonAccountRecord* Record = FindAccount(Save, Username);
    if (!Record || Record->AccountId != AccountId) { OutError = TEXT("The account database changed or could not be read. Try again."); return false; }
    Record->Salt = FDigimonVenomNXTCrypto::NewSalt();
    Record->HashIterations = GetDefault<UDigimonVenomNXTSettings>()->PasswordHashIterations;
    Record->PasswordHash = FDigimonVenomNXTCrypto::PBKDF2(NewPassword, Record->Salt, Record->HashIterations);
    return SaveAccountSave(Save, OutError);
}

bool UDigimonVenomNXTAuthSubsystem::AdminDeleteAccount(const FString& Query, FString& OutError)
{
    FString Username, AccountId;
    if (!AdminResolveAccount(Query, Username, AccountId, OutError)) return false;
    if (AccountId == LoggedInAccountId) { OutError = TEXT("The active host account cannot be deleted."); return false; }
    UDigimonVenomNXTTradeSubsystem* Trade = GetGameInstance()->GetSubsystem<UDigimonVenomNXTTradeSubsystem>();
    UDigimonVenomNXTSocialSubsystem* Social = GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
    if (!Trade || Trade->HasAccountAssets(AccountId))
        { OutError = TEXT("Cancel this account's marketplace listings and resolve pending transfers before deletion."); return false; }
    if (!Social || Social->HasClanMembership(AccountId))
        { OutError = TEXT("This account must leave or disband its clan before deletion."); return false; }
    const AGameStateBase* State = GetWorld() ? GetWorld()->GetGameState() : nullptr;
    if (!State) { OutError = TEXT("The connected-player list is unavailable. No account was deleted."); return false; }
    for (const APlayerState* Player : State->PlayerArray)
    {
        const ADigimonVenomNXTPlayerState* DigimonPlayer = Cast<ADigimonVenomNXTPlayerState>(Player);
        if (DigimonPlayer && DigimonPlayer->Profile.AccountId == AccountId)
        {
            OutError = TEXT("That account is connected. Ask the player to log out before deleting it.");
            return false;
        }
    }
    UDigimonVenomNXTAccountSaveGame* Save = LoadAccountSave();
    if (!Save) { OutError = TEXT("The account database could not be read. No records were changed."); return false; }
    const int32 Removed = Save->Accounts.RemoveAll([&AccountId](const FDigimonAccountRecord& Record) { return Record.AccountId == AccountId; });
    if (Removed != 1) { OutError = TEXT("The account record was not unique. No records were saved."); return false; }
    return SaveAccountSave(Save, OutError);
}
