#pragma once

// Native server instrumentation only. This header adds no replicated state or RPC.
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

namespace DigimonVenomNXTServerActivity
{
inline const TCHAR* VarietyName(EDigimonVariant Variant)
{
    switch (Variant)
    {
    case EDigimonVariant::Normal: return TEXT("Normal");
    case EDigimonVariant::Paradox: return TEXT("Paradox");
    case EDigimonVariant::Shiny: return TEXT("Shiny");
    case EDigimonVariant::Firewall: return TEXT("Firewall");
    default: return TEXT("Unknown");
    }
}

inline UDigimonVenomNXTServerConsoleSubsystem* Console(const AActor* Actor)
{
    if (!Actor || !Actor->HasAuthority() || !Actor->GetWorld() || Actor->GetNetMode() == NM_Client) return nullptr;
    UGameInstance* Instance = Actor->GetGameInstance();
    return Instance ? Instance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
}

inline const ADigimonVenomNXTPlayerState* PlayerState(const AActor* Actor)
{
    if (const ADigimonVenomNXTPlayerState* State = Cast<ADigimonVenomNXTPlayerState>(Actor)) return State;
    const AController* Controller = Cast<AController>(Actor);
    return Controller ? Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
}

inline FString PlayerName(const AActor* Actor)
{
    const ADigimonVenomNXTPlayerState* State = PlayerState(Actor);
    if (State && !State->Profile.Username.IsEmpty()) return State->Profile.Username;
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Actor);
    if (!Controller && State) Controller = Cast<ADigimonVenomNXTPlayerController>(State->GetOwner());
    if (Controller && Controller->IsAccountAuthenticated())
        return TEXT("Authenticated session: profile unavailable");
    return TEXT("Pending account authentication");
}

inline void RecordFor(const AActor* Actor, const FString& Player, const FString& Category,
    const FString& Action, const FString& Details, const FString& Severity = TEXT("Info"))
{
    if (UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = Console(Actor))
        ServerConsole->RecordActivity(Category, Player, Action, Details, Severity);
}

inline void Record(const AActor* Actor, const FString& Category, const FString& Action,
    const FString& Details, const FString& Severity = TEXT("Info"))
{
    RecordFor(Actor, PlayerName(Actor), Category, Action, Details, Severity);
}

// Gate player-initiated mutations, never settlement, saving, chat or logout. A jail
// cannot erase a saved battle or prevent the normal disconnect/save paths.
inline bool AllowGameplay(AActor* Actor, FString* OutError = nullptr)
{
    if (!Actor || !Actor->HasAuthority() || !Actor->GetWorld() || Actor->GetNetMode() == NM_Client) return false;
    const ADigimonVenomNXTPlayerState* State = PlayerState(Actor);
    if (!State || State->Profile.AccountId.IsEmpty()) return false;
    ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Actor);
    if (!Controller) Controller = Cast<ADigimonVenomNXTPlayerController>(State->GetOwner());
    // Logout disarms gameplay before its final travel. A retained profile is not
    // proof of a live authenticated session during that disconnect interval.
    if (!Controller || Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() != State ||
        !Controller->IsAccountAuthenticated() || Controller->IsLogoutPending())
    {
        if (OutError) *OutError = TEXT("Sign in again before changing your tamer's progress.");
        return false;
    }
    if (!Controller->IsOwnerProfileReady())
    {
        if (OutError) *OutError = TEXT("Your account is still synchronizing. Wait for the verified profile before changing progress.");
        return false;
    }
    UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = Console(Actor);
    FString Reason;
    if (!ServerConsole || !ServerConsole->IsAccountJailed(State->Profile.AccountId, Reason)) return true;
    const FString Message = TEXT("Gameplay is suspended by this host. ") + Reason;
    if (OutError) *OutError = Message;
    if (Controller) Controller->ClientShowMessage(TEXT("Host moderation"), Message);
    Record(Actor, TEXT("Moderation"), TEXT("Gameplay blocked"), TEXT("Account is jailed."), TEXT("Warning"));
    return false;
}
}
