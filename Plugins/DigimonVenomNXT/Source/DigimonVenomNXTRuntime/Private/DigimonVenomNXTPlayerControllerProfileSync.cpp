#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProfileSnapshot.h"
#include "DigimonVenomNXTProfileSyncWidget.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTServerActivity.h"
#include "Engine/World.h"
#include "HAL/PlatformTime.h"
#include "UObject/Class.h"

void ADigimonVenomNXTPlayerController::QueueOwnerProfileSynchronization()
{
    if (HasAuthority()) bOwnerProfileDirty = true;
}

void ADigimonVenomNXTPlayerController::TickProfileSynchronization()
{
    const double Now = FPlatformTime::Seconds();
    if (HasAuthority())
    {
        if (!IsAccountAuthenticated() || bLogoutServerCommitted) return;
        ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!PS || !PS->HasInitializedServerProfile()) return;
        if (IsLocalController()) return; // The listen host already owns authoritative memory.
        if (Now - LastProfileComparison >= 2.0)
        {
            LastProfileComparison = Now;
            // Also catches Blueprint/admin mutations that forget MarkProfileChanged.
            if (!FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&PS->Profile, &LastQueuedOwnerProfile, 0))
                bOwnerProfileDirty = true;
        }
        if (OutgoingProfileTransferId.IsValid())
        {
            if (Now - LastProfileServerProgress > DigimonVenomNXTProfileSyncCore::IdleTimeoutSeconds)
                FailOutgoingProfileSnapshot(TEXT("Account synchronization stopped responding. Retry the connection; the saved account has not been replaced."));
            else PumpOwnerProfileSnapshot();
        }
        else if (bOwnerProfileDirty && ProfileSyncFailureCount < 3 &&
            Now - LastProfileSnapshotStarted >= DigimonVenomNXTProfileSyncCore::MinimumSnapshotIntervalSeconds)
            StartOwnerProfileSnapshot();
        return;
    }
    if (!IsLocalController() || ExpectedProfileAccountId.IsEmpty() || bLogoutPending) return;
    TryApplyOwnerProfileSnapshot();
    // A replaced/delayed PlayerState is not evidence of a fresh account. Re-request
    // its owner snapshot instead of presenting default data or assigning by username.
    if (bOwnerProfileReady && AppliedOwnerProfileState.Get() != GetPlayerState<ADigimonVenomNXTPlayerState>())
    {
        bOwnerProfileReady = false;
        if (GameHUDWidget) { GameHUDWidget->RemoveFromParent(); GameHUDWidget = nullptr; }
        ShowProfileSynchronizationStatus(TEXT("Restoring the account on the new player connection..."), false);
        RetryProfileSynchronization();
    }
    if ((!bOwnerProfileReady || IncomingProfileTransferId.IsValid()) &&
        Now - LastProfileClientProgress > DigimonVenomNXTProfileSyncCore::IdleTimeoutSeconds)
    {
        LastProfileClientProgress = Now;
        if (ProfileAutomaticRetries < 3)
        {
            ++ProfileAutomaticRetries;
            RetryProfileSynchronization();
        }
        else ShowProfileSynchronizationStatus(TEXT("The server has not completed account synchronization. Retry, or return to login. Your saved account has not been replaced."), true);
    }
}

void ADigimonVenomNXTPlayerController::StartOwnerProfileSnapshot()
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!HasAuthority() || !IsAccountAuthenticated() || IsLocalController() || !PS || !PS->HasInitializedServerProfile()) return;
    LastProfileSnapshotStarted = FPlatformTime::Seconds();
    int32 JsonByteCount = 0;
    uint32 Checksum = 0;
    FString Error;
    // Freeze one version. Later gameplay changes queue a newer snapshot, never
    // alter chunks already in flight and never restart/starve a slow transfer.
    LastQueuedOwnerProfile = PS->Profile;
    if (!DigimonVenomNXTProfileSnapshot::Encode(LastQueuedOwnerProfile, OutgoingProfileBytes, JsonByteCount, Checksum, Error))
    {
        FailOutgoingProfileSnapshot(Error);
        return;
    }
    if (!ProfileSendWindow.Begin(OutgoingProfileBytes.Num()))
    {
        FailOutgoingProfileSnapshot(TEXT("The profile snapshot has an invalid transfer size."));
        return;
    }
    bOwnerProfileDirty = false;
    OutgoingProfileTransferId = FGuid::NewGuid();
    ++OutgoingProfileRevision;
    LastProfileServerProgress = FPlatformTime::Seconds();
    ClientBeginProfileSnapshot(OutgoingProfileTransferId, DigimonVenomNXTProfileSyncCore::ProtocolVersion,
        OutgoingProfileRevision, PS->Profile.AccountId, OutgoingProfileBytes.Num(), JsonByteCount, static_cast<int64>(Checksum));
    if (!bOwnerProfileReady)
        DigimonVenomNXTServerActivity::Record(this, TEXT("Session"), TEXT("Profile synchronization started"),
            FString::Printf(TEXT("Party %d | Collection %d | Season week %d | Ranked rating %d | Snapshot %d bytes in %d chunks"),
                PS->Profile.Party.Num(), PS->Profile.Collection.Num(), PS->Profile.Season.Week, PS->Profile.Ranked.Rating,
                OutgoingProfileBytes.Num(), DigimonVenomNXTProfileSyncCore::ChunkCount(OutgoingProfileBytes.Num())));
    PumpOwnerProfileSnapshot();
}

void ADigimonVenomNXTPlayerController::PumpOwnerProfileSnapshot()
{
    if (!HasAuthority() || !OutgoingProfileTransferId.IsValid() || bLogoutServerCommitted) return;
    for (int32 Offset = ProfileSendWindow.NextOffset(); Offset >= 0; Offset = ProfileSendWindow.NextOffset())
    {
        const int32 Count = DigimonVenomNXTProfileSyncCore::ExpectedChunkBytes(OutgoingProfileBytes.Num(), Offset);
        TArray<uint8> Chunk;
        Chunk.Append(OutgoingProfileBytes.GetData() + Offset, Count);
        ClientProfileSnapshotChunk(OutgoingProfileTransferId, Offset, Chunk);
    }
}

void ADigimonVenomNXTPlayerController::ServerAcknowledgeProfileChunk_Implementation(FGuid TransferId, int32 Offset)
{
    if (!HasAuthority() || !IsAccountAuthenticated() || bLogoutServerCommitted ||
        TransferId != OutgoingProfileTransferId || !TransferId.IsValid()) return;
    if (ProfileSendWindow.Acknowledge(Offset)) LastProfileServerProgress = FPlatformTime::Seconds();
}

void ADigimonVenomNXTPlayerController::ServerCompleteProfileSnapshot_Implementation(FGuid TransferId, int64 Revision, bool bAccepted)
{
    if (!HasAuthority() || !IsAccountAuthenticated() || bLogoutServerCommitted ||
        TransferId != OutgoingProfileTransferId || !TransferId.IsValid() || Revision != OutgoingProfileRevision) return;
    if (!bAccepted)
    {
        FailOutgoingProfileSnapshot(TEXT("The client rejected an incomplete or stale snapshot. The server retains the authoritative account and will retry."));
        return;
    }
    if (!ProfileSendWindow.Complete()) return;
    const bool bFirstReady = !bOwnerProfileReady;
    OutgoingProfileTransferId.Invalidate();
    OutgoingProfileBytes.Reset();
    ProfileSendWindow.Reset();
    ProfileSyncFailureCount = 0;
    bOwnerProfileReady = true;
    if (bFirstReady)
    {
        DigimonVenomNXTServerActivity::Record(this, TEXT("Session"), TEXT("Profile synchronization complete"),
            TEXT("The client verified its complete account snapshot. Gameplay is now enabled."));
        ActivateSynchronizedAccount();
    }
}

void ADigimonVenomNXTPlayerController::ClientBeginProfileSnapshot_Implementation(FGuid TransferId, int32 Protocol, int64 Revision,
    const FString& AccountId, int32 ByteCount, int32 JsonByteCount, int64 Checksum)
{
    if (HasAuthority() || !IsLocalController() || bLogoutPending) return;
    if (!TransferId.IsValid() || Protocol != DigimonVenomNXTProfileSyncCore::ProtocolVersion ||
        ExpectedProfileAccountId.IsEmpty() || AccountId != ExpectedProfileAccountId || Revision <= AppliedProfileRevision ||
        !DigimonVenomNXTProfileSyncCore::ValidSize(ByteCount) || !DigimonVenomNXTProfileSyncCore::ValidSize(JsonByteCount) ||
        Checksum < 0 || Checksum > 0xffffffffLL)
    {
        ServerCompleteProfileSnapshot(TransferId, Revision, false);
        ShowProfileSynchronizationStatus(TEXT("The server sent an incompatible account snapshot. Ensure host and client use the same Digimon Venom NXT build, then retry."), true);
        return;
    }
    if (IncomingProfileTransferId.IsValid() && Revision <= IncomingProfileRevision) return;
    if (!ProfileReceiver.Begin(ByteCount)) return;
    IncomingProfileTransferId = TransferId;
    IncomingProfileRevision = Revision;
    IncomingProfileJsonBytes = JsonByteCount;
    IncomingProfileChecksum = static_cast<uint32>(Checksum);
    bOwnerProfilePending = false;
    LastProfileClientProgress = FPlatformTime::Seconds();
    if (!bOwnerProfileReady) ShowProfileSynchronizationStatus(TEXT("Receiving your saved account..."), false);
}

void ADigimonVenomNXTPlayerController::ClientProfileSnapshotChunk_Implementation(FGuid TransferId, int32 Offset, const TArray<uint8>& Bytes)
{
    if (HasAuthority() || !IsLocalController() || bLogoutPending ||
        !TransferId.IsValid() || TransferId != IncomingProfileTransferId) return;
    const DigimonVenomNXTProfileSyncCore::AddResult Result = ProfileReceiver.Add(Offset, Bytes.GetData(), Bytes.Num());
    if (Result == DigimonVenomNXTProfileSyncCore::AddResult::Rejected)
    {
        RejectIncomingProfileSnapshot(TEXT("An account snapshot chunk was invalid. The previous profile remains unchanged."));
        return;
    }
    LastProfileClientProgress = FPlatformTime::Seconds();
    ServerAcknowledgeProfileChunk(TransferId, Offset);
    if (!bOwnerProfileReady)
        ShowProfileSynchronizationStatus(FString::Printf(TEXT("Restoring account: %d%%\nTeam, Season career, ranked progress and inventory are being verified together."),
            static_cast<int32>(100LL * ProfileReceiver.ReceivedBytes() / ProfileReceiver.TotalBytes())), false);
    if (Result != DigimonVenomNXTProfileSyncCore::AddResult::Complete) return;
    FString Error;
    if (!DigimonVenomNXTProfileSnapshot::Decode(ProfileReceiver.Bytes(), ProfileReceiver.TotalBytes(), IncomingProfileJsonBytes,
        IncomingProfileChecksum, ExpectedProfileAccountId, PendingOwnerProfile, Error))
    {
        RejectIncomingProfileSnapshot(Error);
        return;
    }
    bOwnerProfilePending = true;
    TryApplyOwnerProfileSnapshot();
}

void ADigimonVenomNXTPlayerController::TryApplyOwnerProfileSnapshot()
{
    if (HasAuthority() || !bOwnerProfilePending || !IncomingProfileTransferId.IsValid() || bLogoutPending) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS) return; // The controller's reliable RPC and PlayerState can arrive in either order.
    if ((!PS->Profile.AccountId.IsEmpty() && PS->Profile.AccountId != ExpectedProfileAccountId) ||
        !DigimonVenomNXTProfileSyncCore::CanApplyRevision(IncomingProfileRevision, AppliedProfileRevision,
            PendingOwnerProfile.CommerceRevision, PS->Profile.CommerceRevision,
            PendingOwnerProfile.DigiLabRecoveryRevision, PS->Profile.DigiLabRecoveryRevision))
    {
        RejectIncomingProfileSnapshot(TEXT("A newer transaction is already present. Requesting a fresh account snapshot without rolling it back."));
        return;
    }
    if (!PS->ApplyOwnerProfileSnapshot(PendingOwnerProfile, ExpectedProfileAccountId))
    {
        RejectIncomingProfileSnapshot(TEXT("The account snapshot could not be applied safely. The previous profile remains unchanged."));
        return;
    }
    AppliedProfileRevision = IncomingProfileRevision;
    AppliedOwnerProfileState = PS;
    const bool bFirstReady = !bOwnerProfileReady;
    bOwnerProfileReady = true;
    bOwnerProfilePending = false;
    ProfileAutomaticRetries = 0;
    // ACK first; later gameplay RPCs on this same controller are ordered after it.
    ServerCompleteProfileSnapshot(IncomingProfileTransferId, IncomingProfileRevision, true);
    IncomingProfileTransferId.Invalidate();
    ProfileReceiver.Reset();
    PendingOwnerProfile = FDigimonPlayerProfile();
    if (bFirstReady) FinishOwnerProfilePresentation();
}

void ADigimonVenomNXTPlayerController::ActivateSynchronizedAccount()
{
    if (!HasAuthority() || !bOwnerProfileReady || bAuthenticatedWorldEntered) return;
    if (ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr)
    {
        bAuthenticatedWorldEntered = true;
        Mode->FinishAuthenticatedPlayerLogin(this);
    }
}

void ADigimonVenomNXTPlayerController::FinishOwnerProfilePresentation()
{
    if (!IsLocalController() || !bOwnerProfileReady) return;
    if (ProfileSyncWidget) { ProfileSyncWidget->RemoveFromParent(); ProfileSyncWidget = nullptr; }
    CreateNativeHUD();
    RefreshBattleUI();
    ApplyFieldInputMode();
}

void ADigimonVenomNXTPlayerController::ShowProfileSynchronizationStatus(const FString& Message, bool bCanRetry)
{
    if (!IsLocalController()) return;
    if (bOwnerProfileReady)
    {
        if (bCanRetry) ClientShowMessage(TEXT("Account synchronization"), Message);
        return; // Keep the last verified profile visible during subsequent updates.
    }
    if (!ProfileSyncWidget)
    {
        ProfileSyncWidget = CreateWidget<UDigimonVenomNXTProfileSyncWidget>(this, UDigimonVenomNXTProfileSyncWidget::StaticClass());
        if (ProfileSyncWidget) ProfileSyncWidget->AddToViewport(1000);
    }
    if (ProfileSyncWidget) ProfileSyncWidget->SetStatus(Message, bCanRetry);
    ApplyFieldInputMode();
}

void ADigimonVenomNXTPlayerController::RetryProfileSynchronization()
{
    if (!IsLocalController() || HasAuthority() || ExpectedProfileAccountId.IsEmpty() || bLogoutPending) return;
    const double Now = FPlatformTime::Seconds();
    if (Now - LastProfileResyncRequest < 2.0) return;
    LastProfileResyncRequest = Now;
    LastProfileClientProgress = Now;
    ShowProfileSynchronizationStatus(TEXT("Requesting a fresh verified account snapshot..."), false);
    ServerRequestProfileSynchronization();
}

void ADigimonVenomNXTPlayerController::ServerRequestProfileSynchronization_Implementation()
{
    if (!HasAuthority() || !IsAccountAuthenticated() || bLogoutServerCommitted || IsLocalController()) return;
    const double Now = FPlatformTime::Seconds();
    if (Now - LastProfileServerResyncRequest < 2.0) return;
    LastProfileServerResyncRequest = Now;
    // Do not replace an active, progressing snapshot. This prevents retry spam
    // from queuing repeated full payloads or starving the first snapshot forever.
    if (OutgoingProfileTransferId.IsValid() && Now - LastProfileServerProgress < DigimonVenomNXTProfileSyncCore::IdleTimeoutSeconds) return;
    OutgoingProfileTransferId.Invalidate();
    OutgoingProfileBytes.Reset();
    ProfileSendWindow.Reset();
    ProfileSyncFailureCount = 0;
    bOwnerProfileDirty = true;
}

void ADigimonVenomNXTPlayerController::RejectIncomingProfileSnapshot(const FString& Message)
{
    if (IncomingProfileTransferId.IsValid()) ServerCompleteProfileSnapshot(IncomingProfileTransferId, IncomingProfileRevision, false);
    IncomingProfileTransferId.Invalidate();
    ProfileReceiver.Reset();
    bOwnerProfilePending = false;
    PendingOwnerProfile = FDigimonPlayerProfile();
    ShowProfileSynchronizationStatus(Message, true);
}

void ADigimonVenomNXTPlayerController::FailOutgoingProfileSnapshot(const FString& Message)
{
    OutgoingProfileTransferId.Invalidate();
    OutgoingProfileBytes.Reset();
    ProfileSendWindow.Reset();
    ++ProfileSyncFailureCount;
    bOwnerProfileDirty = true;
    DigimonVenomNXTServerActivity::Record(this, TEXT("Session"), TEXT("Profile synchronization failed"), Message, TEXT("Error"));
    ClientProfileSynchronizationFailed(Message);
}

void ADigimonVenomNXTPlayerController::ClientProfileSynchronizationFailed_Implementation(const FString& Message)
{
    if (HasAuthority() || bLogoutPending) return;
    IncomingProfileTransferId.Invalidate();
    ProfileReceiver.Reset();
    bOwnerProfilePending = false;
    PendingOwnerProfile = FDigimonPlayerProfile();
    ShowProfileSynchronizationStatus(Message, true);
}

void ADigimonVenomNXTPlayerController::ClearProfileSynchronization()
{
    if (ProfileSyncWidget) { ProfileSyncWidget->RemoveFromParent(); ProfileSyncWidget = nullptr; }
    OutgoingProfileTransferId.Invalidate(); IncomingProfileTransferId.Invalidate();
    OutgoingProfileBytes.Reset(); ProfileSendWindow.Reset(); ProfileReceiver.Reset();
    ExpectedProfileAccountId.Reset(); AppliedOwnerProfileState.Reset();
    PendingOwnerProfile = FDigimonPlayerProfile(); LastQueuedOwnerProfile = FDigimonPlayerProfile();
    bOwnerProfilePending = false; bOwnerProfileReady = false;
}
