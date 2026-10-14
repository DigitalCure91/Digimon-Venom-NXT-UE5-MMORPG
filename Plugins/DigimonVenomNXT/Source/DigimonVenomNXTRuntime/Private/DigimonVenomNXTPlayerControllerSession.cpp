#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTGameInstance.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "HAL/PlatformTime.h"
#include "JsonObjectConverter.h"
#include "TimerManager.h"

namespace DigimonVenomNXTSessionPrivate
{
bool CanPreserveBattle(const ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    const ADigimonVenomNXTBattleActor* Battle = Controller ? Controller->CurrentBattle.Get() : nullptr;
    const ADigimonVenomNXTPlayerState* Player = Controller ? Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    if (!Battle || Battle->State.bFinished) return true;
    // Ranked playback is presentation of an already committed ledger result.
    if (Battle->State.Kind == EDigimonBattleKind::Ranked && Battle->State.bAutomatic) return true;
    const FString* CheckpointJson = nullptr;
    EDigimonPrivateCampaign Campaign;
    FName NPCId;
    if (Player && DigimonVenomNXTCampaign::TryParseContext(Battle->BattleContextId, Campaign, NPCId))
        CheckpointJson = &DigimonVenomNXTCampaign::Progress(Player->Profile, Campaign).BattleCheckpointJson;
    else if (Player && Battle->State.Kind == EDigimonBattleKind::Season)
        CheckpointJson = &Player->Profile.Season.BattleCheckpointJson;
    else if (Player && Battle->State.Kind == EDigimonBattleKind::Wild && Battle->BattleContextId.StartsWith(TEXT("world:")))
        CheckpointJson = &Player->Profile.WorldBattleCheckpointJson;
    if (CheckpointJson && !CheckpointJson->IsEmpty() && CheckpointJson->Len() <= 1024 * 1024)
    {
        FDigimonSeasonBattleCheckpoint Checkpoint;
        if (FJsonObjectConverter::JsonObjectStringToUStruct(*CheckpointJson, &Checkpoint, 0, 0) &&
            (Checkpoint.Version == 1 || Checkpoint.Version == 2) &&
            Checkpoint.ContextId == Battle->BattleContextId && Checkpoint.State.BattleId == Battle->State.BattleId &&
            !Checkpoint.State.bFinished)
            return true;
        OutError = TEXT("The active battle has no valid saved checkpoint. Finish the battle or retry after the next saved decision.");
        return false;
    }
    OutError = TEXT("Finish the active battle before logging out, or wait for a saved decision. Wild, story and Season battles with valid checkpoints can be resumed after login.");
    return false;
}

void SuspendDurableBattle(ADigimonVenomNXTPlayerController* Controller)
{
    ADigimonVenomNXTBattleActor* Battle = Controller ? Controller->CurrentBattle.Get() : nullptr;
    if (!Battle) return;
    EDigimonPrivateCampaign Campaign;
    FName NPCId;
    if (DigimonVenomNXTCampaign::TryParseContext(Battle->BattleContextId, Campaign, NPCId)) Battle->SuspendRelayMatch();
    else if (Battle->State.Kind == EDigimonBattleKind::Season) Battle->SuspendSeasonMatch();
    else if (Battle->State.Kind == EDigimonBattleKind::Wild && Battle->BattleContextId.StartsWith(TEXT("world:"))) Battle->SuspendWorldWildMatch();
    Controller->SetCurrentBattleServer(nullptr);
    Battle->TryDestroyWhenUnused();
}
}

bool ADigimonVenomNXTPlayerController::RequestLogout(FString& OutError)
{
    OutError.Reset();
    if (!IsLocalController() || (!IsAccountAuthenticated() && !PendingLogoutRequestId.IsValid()))
    {
        OutError = TEXT("Only the signed-in local player can request logout.");
        return false;
    }
    if (bLogoutPending || bLogoutServerCommitted)
    {
        OutError = TEXT("Logout is already waiting for the server to confirm your session handoff.");
        return false;
    }
    if (!UDigimonVenomNXTGameInstance::ValidateMainMenuForGameInstance(GetGameInstance(), OutError)) return false;
    bLogoutPending = true;
    PendingLogoutRequestId = FGuid::NewGuid();
    GetWorldTimerManager().SetTimer(LogoutTimeoutTimer, this, &ADigimonVenomNXTPlayerController::LogoutAcknowledgementTimedOut, 15.0f, false);
    ServerRequestLogout(PendingLogoutRequestId);
    return true;
}

void ADigimonVenomNXTPlayerController::ServerRequestLogout_Implementation(FGuid RequestId)
{
    if (!RequestId.IsValid() || !HasAuthority()) return;
    if (bLogoutServerCommitted)
    {
        // A retry never writes or settles again. A previous success is still a valid session-handoff acknowledgement.
        ClientLogoutResult(RequestId, true, TEXT("Your session was safely released. Returning to the login screen."));
        return;
    }
    const double Now = FPlatformTime::Seconds();
    if (Now - LastLogoutServerRequestTime < 0.5)
    {
        ClientLogoutResult(RequestId, false, TEXT("Please wait a moment before trying Logout again."));
        return;
    }
    LastLogoutServerRequestTime = Now;
    if (!IsAccountAuthenticated())
    {
        ClientLogoutResult(RequestId, false, TEXT("This connection is not authenticated. Logout was not started."));
        return;
    }
    ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    ADigimonVenomNXTPlayerState* Self = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!Mode || !Self || Self->Profile.AccountId.IsEmpty())
    {
        ClientLogoutResult(RequestId, false, TEXT("The authoritative profile or session-retention service is unavailable. Your session remains open."));
        return;
    }
    UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>();
    const bool bHost = Console && Console->CanAccess(this);
    if (IsLocalController() && GetNetMode() == NM_ListenServer && !bHost)
    {
        ClientLogoutResult(RequestId, false, TEXT("The authenticated host session could not be verified. The server remains open."));
        return;
    }
    FString Error;
    if (bHost && !UDigimonVenomNXTGameInstance::ValidateMainMenuForGameInstance(GetGameInstance(), Error))
    {
        ClientLogoutResult(RequestId, false, Error);
        return;
    }
    TArray<ADigimonVenomNXTPlayerController*> Players;
    Players.Add(this);
    if (bHost)
    {
        // Inspect each result instead of using SaveAllPlayers(), which discards failures.
        const AGameStateBase* State = GetWorld()->GetGameState();
        if (!State)
        {
            ClientLogoutResult(RequestId, false, TEXT("The server player list is unavailable. The world remains open."));
            return;
        }
        for (APlayerState* Entry : State->PlayerArray)
        {
            ADigimonVenomNXTPlayerController* Other = Entry ? Cast<ADigimonVenomNXTPlayerController>(Entry->GetOwner()) : nullptr;
            if (Other && Other != this && Other->IsAccountAuthenticated()) Players.AddUnique(Other);
        }
    }
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        if (!DigimonVenomNXTSessionPrivate::CanPreserveBattle(SessionController, Error))
        {
            const ADigimonVenomNXTPlayerState* Profile = SessionController->GetPlayerState<ADigimonVenomNXTPlayerState>();
            const FString Name = Profile ? Profile->Profile.Username : TEXT("A connected player");
            ClientLogoutResult(RequestId, false, bHost ? Name + TEXT(": ") + Error + TEXT(" The server remains open.") : Error);
            return;
        }
    }
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        ADigimonVenomNXTPlayerState* Profile = SessionController->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!Mode->SavePlayer(Profile, false))
        {
            const FString Name = Profile ? Profile->Profile.Username : TEXT("A connected player");
            ClientLogoutResult(RequestId, false, FString::Printf(TEXT("Could not retain %s in server memory. No players were disconnected. Check the server log for the profile-validation or revision error."), *Name));
            return;
        }
    }
    if (bHost)
    {
        if (!Console->SaveAll(Error))
        {
            ClientLogoutResult(RequestId, false, Error + TEXT(" The world remains open; no players were disconnected."));
            return;
        }
    }
    // Queue every leave while all recipients are still authenticated, before any close RPC.
    for (ADigimonVenomNXTPlayerController* SessionController : Players) Mode->LeaveWorldChat(SessionController);
    // Ordinary logout only handed authoritative values to server memory. Admin logout
    // additionally completed the full disk checkpoint. Now release the old connection.
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        DigimonVenomNXTSessionPrivate::SuspendDurableBattle(SessionController);
        SessionController->bLogoutServerCommitted = true;
        SessionController->SetAccountAuthenticatedServer(false);
        if (SessionController != this) SessionController->ClientHostSessionClosed(TEXT("The host closed the world. Your progress was saved."));
    }
    CommittedLogoutRequestId = RequestId;
    if (bHost)
    {
        // Let reliable close notices leave the listen server before its NetDriver is torn down.
        // The notice is convenience; profile durability does not depend on client delivery.
        GetWorldTimerManager().SetTimer(HostLogoutTravelTimer, FTimerDelegate::CreateWeakLambda(this, [this, RequestId]()
        {
            ClientLogoutResult(RequestId, true, TEXT("All online and disconnected profiles and server progression were saved. The world is now closing."));
        }), 0.5f, false);
    }
    else ClientLogoutResult(RequestId, true, TEXT("Your session was safely released. Returning to the login screen."));
}

bool ADigimonVenomNXTPlayerController::PrepareHostWorldRestart(FString& OutError)
{
    OutError.Reset();
    UDigimonVenomNXTServerConsoleSubsystem* Console = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!Console || !Console->CanAccess(this) || !Mode || bLogoutPending || bLogoutServerCommitted)
    {
        OutError = TEXT("Only the authenticated local host can restart an active world. Finish any pending logout first.");
        return false;
    }
    if (!UDigimonVenomNXTGameInstance::ValidateMainMenuForGameInstance(GetGameInstance(), OutError)) return false;
    TArray<ADigimonVenomNXTPlayerController*> Players;
    const AGameStateBase* State = GetWorld()->GetGameState();
    if (!State) { OutError = TEXT("The connected-player list is unavailable. The world was not restarted."); return false; }
    for (APlayerState* Entry : State->PlayerArray)
    {
        ADigimonVenomNXTPlayerController* SessionController = Entry ? Cast<ADigimonVenomNXTPlayerController>(Entry->GetOwner()) : nullptr;
        if (SessionController && SessionController->IsAccountAuthenticated()) Players.AddUnique(SessionController);
    }
    if (!Players.Contains(this)) { OutError = TEXT("The host was not found in the authenticated player list."); return false; }
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        FString BattleError;
        if (!DigimonVenomNXTSessionPrivate::CanPreserveBattle(SessionController, BattleError))
        {
            const ADigimonVenomNXTPlayerState* Profile = SessionController->GetPlayerState<ADigimonVenomNXTPlayerState>();
            OutError = (Profile ? Profile->Profile.Username : TEXT("A connected player")) + TEXT(": ") + BattleError;
            return false;
        }
    }
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        ADigimonVenomNXTPlayerState* Profile = SessionController->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!Mode->SavePlayer(Profile, false))
        {
            OutError = FString::Printf(TEXT("Could not retain %s in server memory. The world remains open and no players were disconnected."), Profile ? *Profile->Profile.Username : TEXT("a connected player"));
            return false;
        }
    }
    if (!Console->SaveAll(OutError))
    {
        OutError += TEXT(" The world remains open; no players were disconnected.");
        return false;
    }
    // All durable saves have succeeded; announce the entire closing session before deauthentication.
    for (ADigimonVenomNXTPlayerController* SessionController : Players) Mode->LeaveWorldChat(SessionController);
    for (ADigimonVenomNXTPlayerController* SessionController : Players)
    {
        DigimonVenomNXTSessionPrivate::SuspendDurableBattle(SessionController);
        if (SessionController != this)
        {
            SessionController->bLogoutServerCommitted = true;
            SessionController->SetAccountAuthenticatedServer(false);
            SessionController->ClientHostSessionClosed(TEXT("The host is restarting the world. Your progress was saved; log in and join again shortly."));
        }
    }
    // Keep only the previously authenticated local host identity and capability.
    // The next listen controller must revalidate that local provenance before loading its profile.
    bLogoutPending = true;
    SetAccountAuthenticatedServer(false);
    return true;
}

void ADigimonVenomNXTPlayerController::ClientLogoutResult_Implementation(FGuid RequestId, bool bSuccess, const FString& Message)
{
    if (!IsLocalController() || RequestId != PendingLogoutRequestId) return;
    GetWorldTimerManager().ClearTimer(LogoutTimeoutTimer);
    if (!bSuccess)
    {
        bLogoutPending = false;
        PendingLogoutRequestId.Invalidate();
        ClientShowMessage(TEXT("Logout"), Message);
        return;
    }
    CompleteAcknowledgedLogout();
}

void ADigimonVenomNXTPlayerController::LogoutAcknowledgementTimedOut()
{
    if (!bLogoutPending) return;
    bLogoutPending = false;
    // Keep the request ID so a late success can still complete safely. A retry replaces it.
    ClientShowMessage(TEXT("Logout is taking longer"), TEXT("The server has not confirmed your session handoff yet. Retry Logout; your credentials are retained until it acknowledges. Ordinary logout does not write saves."));
}

void ADigimonVenomNXTPlayerController::CompleteAcknowledgedLogout()
{
    FString Error;
    if (!UDigimonVenomNXTGameInstance::ValidateMainMenuForGameInstance(GetGameInstance(), Error))
    {
        bLogoutPending = false;
        ClientShowMessage(TEXT("Session released"), Error);
        return;
    }
    bLogoutPending = true;
    if (UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>()) Auth->Logout();
    UDigimonVenomNXTGameInstance::TryReturnToMainMenuForGameInstance(GetGameInstance(), Error);
}

void ADigimonVenomNXTPlayerController::ClientHostSessionClosed_Implementation(const FString& Message)
{
    if (!IsLocalController()) return;
    GetWorldTimerManager().ClearTimer(LogoutTimeoutTimer);
    ClientShowMessage(TEXT("World closed"), Message);
    CompleteAcknowledgedLogout();
}
