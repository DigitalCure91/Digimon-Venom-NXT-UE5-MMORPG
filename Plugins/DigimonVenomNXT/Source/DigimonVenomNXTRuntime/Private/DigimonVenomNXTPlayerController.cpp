#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTTradeComponent.h"
#include "DigimonVenomNXTUnrankedComponent.h"
#include "DigimonVenomNXTWorldChatCore.h"
#include "DigimonVenomNXTServerActivity.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTBattleWidget.h"
#include "DigimonVenomNXTGameHUDWidget.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTFarmScene.h"
#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTRelayScene.h"
#include "DigimonVenomNXTRelaySessionCore.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTFarmSessionCore.h"
#include "DigimonVenomNXTAIRivalAvatar.h"
#include "DigimonVenomNXTPartnerFollower.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTGameInstance.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "InputCoreTypes.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "HAL/PlatformTime.h"

ADigimonVenomNXTPlayerController::ADigimonVenomNXTPlayerController()
{
    bReplicates = true;
    PrimaryActorTick.bCanEverTick = true;
    SocialComponent = CreateDefaultSubobject<UDigimonVenomNXTSocialComponent>(TEXT("SocialComponent"));
    TradeComponent = CreateDefaultSubobject<UDigimonVenomNXTTradeComponent>(TEXT("TradeComponent"));
    UnrankedComponent = CreateDefaultSubobject<UDigimonVenomNXTUnrankedComponent>(TEXT("UnrankedComponent"));
}

void ADigimonVenomNXTPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (IsLocalController())
    {
        bFieldMenuOpen = false;
        ApplyFieldInputMode();
        SubmitPendingAccountAuthentication();
    }
}

void ADigimonVenomNXTPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    TickProfileSynchronization();
    if (!IsLocalController() || !IsOwnerProfileReady()) return;
    RefreshDigiFarmPresentation();
    RefreshRelayPresentation();
    RefreshLocalActorPrivacy();
    if (IsInDigiFarm() && IsValid(DigiFarmScene))
    {
        FarmResidentRefreshElapsed += DeltaSeconds;
        if (FarmResidentRefreshElapsed >= 0.25f)
        {
            FarmResidentRefreshElapsed = 0.0f;
            DigiFarmScene->RefreshResidents();
        }
    }
    if (CurrentBattle || IsLogoutPending()) return;
    if (GameHUDWidget && GameHUDWidget->IsWorldChatTyping())
    {
        if (WasInputKeyJustPressed(EKeys::Escape)) GameHUDWidget->ReleaseWorldChatFocus();
        return;
    }
    if (!IsFieldPresentationBlocked() && !IsInDigiFarm() && !IsInRelay() &&
        WasInputKeyJustPressed(EKeys::Enter) && GameHUDWidget)
    {
        GameHUDWidget->FocusWorldChat();
        return;
    }
    if (bRelayDialogueOpen)
    {
        if (WasInputKeyJustPressed(EKeys::Escape) && GameHUDWidget) GameHUDWidget->CloseRelayDialogue();
        return;
    }
    if (IsInRelay() && !IsFieldInputBlocked() && WasInputKeyJustPressed(EKeys::E))
    {
        const FName Nearby = GetNearestRelayNPC();
        if (!Nearby.IsNone()) ServerInteractRelayNPC(Nearby);
        else if (CanUseRelayPortal(true)) ServerTravelRelayMap(GetRelayPortalTarget(true));
        else if (CanUseRelayPortal(false)) ServerTravelRelayMap(GetRelayPortalTarget(false));
    }

    // Text entry, console commands and modal controls own keyboard navigation while open.
    const bool bMenuOwnsShortcuts = GameHUDWidget && (GameHUDWidget->IsTamerStudioOpen() || GameHUDWidget->IsVideoSettingsOpen() || GameHUDWidget->IsServerConsoleOpen() || GameHUDWidget->IsLogoutConfirmationOpen() || GameHUDWidget->IsCommunityOpen());
    if (!bMenuOwnsShortcuts && (WasInputKeyJustPressed(EKeys::M) || WasInputKeyJustPressed(EKeys::Tab)))
    {
        ToggleFieldMenu();
    }
    else if (!bMenuOwnsShortcuts && !IsFieldInputBlocked() && !IsInDigiFarm() && WasInputKeyJustPressed(EKeys::L) && GameHUDWidget)
    {
        if (UDigimonVenomNXTAudioSubsystem* Audio=GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr) Audio->PlayCue(EDigimonAudioCue::UINavigate);
        GameHUDWidget->OpenDigiLab();
    }
    else if (bFieldMenuOpen && (WasInputKeyJustPressed(EKeys::Escape) ||
        (GameHUDWidget && (GameHUDWidget->IsVideoSettingsOpen() || GameHUDWidget->IsServerConsoleOpen() || GameHUDWidget->IsLogoutConfirmationOpen() || GameHUDWidget->IsCommunityOpen()) && WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Right))))
    {
        if (GameHUDWidget && GameHUDWidget->HandleLogoutConfirmationBack()) return;
        if (GameHUDWidget && GameHUDWidget->HandleServerConsoleBack()) return;
        if (GameHUDWidget && GameHUDWidget->HandleVideoSettingsBack()) return;
        if (GameHUDWidget && GameHUDWidget->HandleCommunityBack()) return;
        if (UDigimonVenomNXTAudioSubsystem* Audio=GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr) Audio->PlayCue(EDigimonAudioCue::UIBack);
        SetFieldMenuOpen(false);
    }
    else if (!bFieldMenuOpen && WasInputKeyJustPressed(EKeys::H) && GameHUDWidget)
    {
        GameHUDWidget->SetCompactHUDVisible(!GameHUDWidget->IsCompactHUDVisible());
    }
}

void ADigimonVenomNXTPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (IsLocalController())
    {
        if (UDigimonVenomNXTAudioSubsystem* Audio = GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        {
            Audio->ClearBattleMusicState(MusicBattle.Get());
            Audio->SetDigiFarmActive(false);
        }
        MusicBattle.Reset();
        if (IsValid(DigiFarmScene)) { DigiFarmScene->Destroy(); DigiFarmScene = nullptr; }
        if (IsValid(RelayScene)) { RelayScene->Destroy(); RelayScene = nullptr; }
        if (IsValid(LocalMapRenderer)) { LocalMapRenderer->Destroy(); LocalMapRenderer = nullptr; }
        if (BattleWidget) { BattleWidget->RemoveFromParent(); BattleWidget = nullptr; }
        if (GameHUDWidget) { GameHUDWidget->RemoveFromParent(); GameHUDWidget = nullptr; }
    }
    ClearProfileSynchronization();
    Super::EndPlay(EndPlayReason);
}

void ADigimonVenomNXTPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerController, CurrentBattle, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerController, bAccountAuthenticated, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerController, FarmSession, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerController, RelaySession, COND_OwnerOnly);
}


void ADigimonVenomNXTPlayerController::SubmitPendingAccountAuthentication()
{
    UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr;
    bool bCreateAccount = false;
    FString Username, Password;
    if (!Auth || !Auth->GetPendingCredentials(bCreateAccount, Username, Password))
    {
        FString RestoredUsername, RestoredAccountId;
        if (UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = DigimonVenomNXTServerActivity::Console(this))
            if (ServerConsole->TryRestoreLocalHostIdentity(this, RestoredUsername, RestoredAccountId))
            {
                // Revalidate locally on the server; do not send a trusted account ID.
                ServerAuthenticateAccount(false, FString(), FString());
                return;
            }
        if (Auth) Auth->ApplyServerAuthResult(false, TEXT("No Digimon Venom NXT account credentials were supplied. Return to MainMenu and choose Create Account or Log In."), FString(), FString());
        UDigimonVenomNXTGameInstance::ReturnToMainMenuForGameInstance(GetGameInstance());
        return;
    }
    ServerAuthenticateAccount(bCreateAccount, Username, Password);
}

void ADigimonVenomNXTPlayerController::ServerAuthenticateAccount_Implementation(bool bCreateAccount, const FString& Username, const FString& Password)
{
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    FString AuthenticatedUsername, AccountId, Error;
    if (!GM || !GM->AuthenticatePlayer(this, bCreateAccount, Username, Password, AuthenticatedUsername, AccountId, Error))
    {
        ClientAccountAuthenticationResult(false, Error.IsEmpty() ? TEXT("Account authentication failed.") : Error, FString(), FString());
        return;
    }
    ClientAccountAuthenticationResult(true, bCreateAccount ? TEXT("Account created and logged in.") : TEXT("Login successful."), AuthenticatedUsername, AccountId);
}

void ADigimonVenomNXTPlayerController::ClientAccountAuthenticationResult_Implementation(bool bSuccess, const FString& Message, const FString& Username, const FString& AccountId)
{
    bAccountAuthenticated = bSuccess;
    if (UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr)
    {
        Auth->ApplyServerAuthResult(bSuccess, Message, Username, AccountId);
    }

    if (!bSuccess)
    {
        UDigimonVenomNXTGameInstance::ReturnToMainMenuForGameInstance(GetGameInstance());
        return;
    }

    ExpectedProfileAccountId = AccountId;
    LastProfileClientProgress = FPlatformTime::Seconds();
    if (HasAuthority())
    {
        const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
        bOwnerProfileReady = PS && PS->HasInitializedServerProfile() && PS->Profile.AccountId == AccountId;
        if (bOwnerProfileReady) { ActivateSynchronizedAccount(); FinishOwnerProfilePresentation(); }
    }
    else ShowProfileSynchronizationStatus(TEXT("Restoring your team, Season career and ranked progress..."), false);
}

void ADigimonVenomNXTPlayerController::SetAccountAuthenticatedServer(bool bAuthenticated)
{
    if (!HasAuthority()) return;
    if (!bAuthenticated)
        if (ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr)
            Mode->LeaveWorldChat(this);
    bAccountAuthenticated = bAuthenticated;
    ForceNetUpdate();
}

void ADigimonVenomNXTPlayerController::CreateNativeHUD()
{
    if (GameHUDWidget || !IsLocalController() || !IsOwnerProfileReady()) return;
    GameHUDWidget = CreateWidget<UDigimonVenomNXTGameHUDWidget>(this, UDigimonVenomNXTGameHUDWidget::StaticClass());
    if (GameHUDWidget)
    {
        GameHUDWidget->AddToViewport(10);
        const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
        SetFieldMenuOpen(PS ? !PS->HasStarter() : false);
        if (PS && !PS->HasStarter()) GameHUDWidget->ShowPage(TEXT("Overview"));
        if (!PendingFarmMessage.IsEmpty())
        {
            GameHUDWidget->ShowToast(TEXT("DigiFarm"), PendingFarmMessage);
            PendingFarmMessage.Reset();
        }
    }
}

bool ADigimonVenomNXTPlayerController::IsFieldInputBlocked() const
{
    return IsFieldPresentationBlocked() || (GameHUDWidget && GameHUDWidget->IsWorldChatTyping());
}

void ADigimonVenomNXTPlayerController::SetFieldMenuOpen(bool bOpen)
{
    if (!IsLocalController()) return;
    bFieldMenuOpen = bOpen || bFarmPresentationFailurePending || bRelayPresentationFailurePending;
    if (GameHUDWidget) GameHUDWidget->SetMenuOpen(bFieldMenuOpen);
    ApplyFieldInputMode();
}

void ADigimonVenomNXTPlayerController::ToggleFieldMenu()
{
    if (UDigimonVenomNXTAudioSubsystem* Audio=GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        Audio->PlayCue(bFieldMenuOpen ? EDigimonAudioCue::UIBack : EDigimonAudioCue::UINavigate);
    SetFieldMenuOpen(!bFieldMenuOpen);
}

void ADigimonVenomNXTPlayerController::ApplyFieldInputMode()
{
    if (!IsLocalController()) return;
    if (!IsOwnerProfileReady())
    {
        bShowMouseCursor = true;
        FInputModeUIOnly SyncInputMode;
        SetInputMode(SyncInputMode);
        return;
    }
    if (CurrentBattle)
    {
        bShowMouseCursor = true;
        FInputModeUIOnly Mode;
        SetInputMode(Mode);
        return;
    }
    // The field party rail and DigiLab shortcut must be clickable in public maps
    // as well as private campaigns. Nonfocusable rail buttons leave movement to
    // the viewport; opening a modal still blocks movement through IsFieldInputBlocked.
    bShowMouseCursor = true;
    FInputModeGameAndUI Mode;
    Mode.SetHideCursorDuringCapture(false);
    Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(Mode);
    if (!bFieldMenuOpen && !bRelayDialogueOpen && !(GameHUDWidget && GameHUDWidget->IsWorldChatTyping())) UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void ADigimonVenomNXTPlayerController::RefreshBattleUI()
{
    if (!IsLocalController() || !IsOwnerProfileReady()) return;
    // Establish the battle layer before binding its widget. A resumed finished
    // widget can then select result music without this method overwriting it.
    if (UDigimonVenomNXTAudioSubsystem* Audio = GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
    {
        const int32 MapId = GetLocalMusicMapId();
        Audio->PlayExplorationForMap(MapId);
        if (MusicBattle.Get() != CurrentBattle.Get()) Audio->ClearBattleMusicState(MusicBattle.Get());
        MusicBattle = CurrentBattle;
        if (CurrentBattle)
            Audio->SetBattleMusicState(CurrentBattle.Get(), MapId, false, CurrentBattle->State.Kind == EDigimonBattleKind::Season);
        else
            Audio->ClearBattleMusicState(nullptr);
    }
    if (CurrentBattle)
    {
        if (GameHUDWidget) GameHUDWidget->ReleaseWorldChatFocus();
        if (!BattleWidget)
        {
            BattleWidget = CreateWidget<UDigimonVenomNXTBattleWidget>(this, UDigimonVenomNXTBattleWidget::StaticClass());
            if (BattleWidget) BattleWidget->AddToViewport(100);
        }
        if (BattleWidget) BattleWidget->SetBattle(CurrentBattle);
        bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        SetInputMode(InputMode);
    }
    else
    {
        if (BattleWidget)
        {
            BattleWidget->RemoveFromParent();
            BattleWidget = nullptr;
        }
        ApplyFieldInputMode();
    }
    OnCurrentBattleChanged.Broadcast(CurrentBattle);
}

void ADigimonVenomNXTPlayerController::OnRep_CurrentBattle()
{
    RefreshBattleUI();
}

void ADigimonVenomNXTPlayerController::SetCurrentBattleServer(ADigimonVenomNXTBattleActor* Battle)
{
    if (!HasAuthority()) return;
    CurrentBattle = Battle;
    if (Battle)
    {
        if (APawn* P = GetPawn())
        {
            if (UCharacterMovementComponent* Move = Cast<UCharacterMovementComponent>(P->GetMovementComponent())) Move->StopMovementImmediately();
        }
    }
    ForceNetUpdate();
    if (IsLocalController()) RefreshBattleUI();
}

void ADigimonVenomNXTPlayerController::ServerTravelToMap_Implementation(int32 MapId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (!bAccountAuthenticated) return;
    if (CurrentBattle) { ClientShowMessage(TEXT("Battle in progress"), TEXT("Finish your battle before travelling.")); return; }
    if (HasPendingStoryBattle()) { ClientShowMessage(TEXT("Saved campaign battle"), TEXT("Resume and finish your saved campaign battle before travelling.")); return; }
    if (IsInRelay())
    {
        ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), TEXT("Use the campaign portals to explore, or Leave Campaign to return to public habitats."));
        return;
    }
    if (IsInDigiFarm())
    {
        ClientShowMessage(TEXT("DigiFarm"), TEXT("Use Leave Farm to return to your saved location before travelling through Level Select."));
        return;
    }
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if ((CurrentBattle && CurrentBattle->State.Kind == EDigimonBattleKind::Season) ||
        (PS && (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty())))
    {
        ClientShowMessage(TEXT("Season Mode"), TEXT("Finish your saved Season match before travelling to another map."));
        return;
    }
    FString Error;
    UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!WorldSystem || !WorldSystem->TravelPlayerToMap(this, MapId, Error))
    {
        DigimonVenomNXTServerActivity::Record(this, TEXT("Travel"), TEXT("Map travel rejected"), Error, TEXT("Warning"));
        ClientShowMessage(TEXT("Travel"), Error.IsEmpty() ? TEXT("Could not travel to that map.") : Error);
    }
    else
    {
        DigimonVenomNXTServerActivity::Record(this, TEXT("Travel"), TEXT("Public map entered"), FString::Printf(TEXT("Map %d | applied; normal save policy"), MapId));
        ClientSetActiveMapPresentation(MapId);
        ClientPlayExplorationMusic(MapId);
    }
}







bool ADigimonVenomNXTPlayerController::TryStartWalkingWildEncounter()
{
    if (!HasAuthority() || !bAccountAuthenticated || CurrentBattle || IsInDigiFarm() || IsInRelay() || HasPendingStoryBattle() || HasPendingWorldBattle()) return false;
    const double Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0;
    const double Cooldown = GetDefault<UDigimonVenomNXTSettings>()->WildEncounterCooldownSeconds;
    if (Now - LastWildEncounterRequestTime < Cooldown) return false;

    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !GM->StartWildBattleFor(this, Error)) return false;
    LastWildEncounterRequestTime = Now;
    return true;
}

void ADigimonVenomNXTPlayerController::ServerRequestAIRivalActivity_Implementation(int32 PageIndex, int32 PageSize)
{
    if (!bAccountAuthenticated || !GetWorld()) return;
    const double Now = GetWorld()->GetTimeSeconds();
    if (Now - LastActivityRequestTime < 0.5) return;
    LastActivityRequestTime = Now;
    if (UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>())
        ClientReceiveAIRivalActivity(Rivals->GetActivityPage(FMath::Max(0, PageIndex), FMath::Clamp(PageSize, 1, 20)));
}

void ADigimonVenomNXTPlayerController::ClientReceiveAIRivalActivity_Implementation(const FDigimonAIRivalActivityPage& Page)
{
    if (GameHUDWidget) GameHUDWidget->ApplyRivalActivityPage(Page);
}

void ADigimonVenomNXTPlayerController::ServerRequestRankedStatus_Implementation()
{
    if (!bAccountAuthenticated || !GetWorld()) return;
    const double Now = GetWorld()->GetTimeSeconds();
    if (Now - LastRankedStatusRequestTime < 2.0) return;
    LastRankedStatusRequestTime = Now;
    if (UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr)
        Ranked->RefreshPlayerState(GetPlayerState<ADigimonVenomNXTPlayerState>());
}

void ADigimonVenomNXTPlayerController::ServerChallengeAIRival_Implementation(const FString& RivalId)
{
    if (!bAccountAuthenticated || RivalId.IsEmpty() || RivalId.Len() > 128) return;
    const double Now = FPlatformTime::Seconds();
    if (Now - LastRivalChallengeRequestTime < 3.0) return;
    LastRivalChallengeRequestTime = Now;
    if (!RequirePublicFieldForBattle()) return;
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !GM->StartAIRivalBattleFor(this, RivalId, Error)) ClientShowMessage(TEXT("AI Rival"), Error.IsEmpty()?TEXT("Could not start the rival battle."):Error);
}

void ADigimonVenomNXTPlayerController::ServerRequestSeasonStatus_Implementation()
{
    if (!bAccountAuthenticated || !GetWorld()) return;
    if (CurrentBattle && !CurrentBattle->State.bFinished) return;
    const double Now = GetWorld()->GetTimeSeconds();
    if (Now - LastSeasonStatusRequestTime < 2.0) return;
    LastSeasonStatusRequestTime = Now;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!PS || PS->Profile.AccountId.IsEmpty() || !GM || !Data) return;
    const FDigimonPlayerProfile Before = PS->Profile;
    if (!DigimonVenomNXTSeason::EnsureCareer(PS->Profile, Data)) return;
    if (!GM->SavePlayer(PS))
    {
        PS->Profile = Before;
        ClientShowMessage(TEXT("Season Mode"), TEXT("Could not save your Season roster. Please try reopening this screen."));
        return;
    }
    PS->MarkProfileChanged();
}

void ADigimonVenomNXTPlayerController::ServerRequestSeasonArchive_Implementation(int32 PageIndex)
{
    if (!bAccountAuthenticated || !GetWorld()) return;
    const double Now = GetWorld()->GetTimeSeconds();
    if (Now - LastSeasonArchiveRequestTime < 0.5) return;
    LastSeasonArchiveRequestTime = Now;
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!PS || PS->Profile.AccountId.IsEmpty() || !Profiles) return;
    FDigimonSeasonArchivePage Page;
    Profiles->LoadSeasonArchive(PS->Profile, FMath::Max(0, PageIndex), 8, Page);
    ClientReceiveSeasonArchive(Page);
}

void ADigimonVenomNXTPlayerController::ClientReceiveSeasonArchive_Implementation(const FDigimonSeasonArchivePage& Page)
{
    if (GameHUDWidget) GameHUDWidget->ApplySeasonArchivePage(Page);
}

void ADigimonVenomNXTPlayerController::ServerStartSeasonMatch_Implementation()
{
    if (!bAccountAuthenticated) return;
    if (!RequirePublicFieldForBattle()) return;
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !GM->StartSeasonBattleFor(this, Error)) ClientShowMessage(TEXT("Season Mode"), Error.IsEmpty()?TEXT("Could not start the Season match."):Error);
}

void ADigimonVenomNXTPlayerController::ServerAdvanceSeasonWeek_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (!bAccountAuthenticated || !GetWorld()) return;
    if (CurrentBattle)
    {
        ClientShowMessage(TEXT("Season Mode"), TEXT("Return from the current battle before advancing your career."));
        return;
    }
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!PS || PS->Profile.AccountId.IsEmpty() || !GM || !Data) return;
    const FDigimonPlayerProfile Before = PS->Profile;
    FString Message;
    DigimonVenomNXTSeason::EnsureCareer(PS->Profile, Data);
    if (!DigimonVenomNXTSeason::AdvanceWeek(PS->Profile, Data, Message))
    {
        PS->Profile = Before;
        ClientShowMessage(TEXT("Season Mode"), Message);
        return;
    }
    // Month/year rewards and their paid-period markers commit together with the
    // next card. A failed write rolls back all three and can safely be retried.
    if (!GM->SavePlayer(PS))
    {
        PS->Profile = Before;
        ClientShowMessage(TEXT("Season Mode"), TEXT("Could not save the next week. Your calendar and credits are unchanged; please try again."));
        return;
    }
    PS->MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Season"), TEXT("Week advanced and saved"), Message);
    ClientShowMessage(TEXT("Season Mode"), Message);
}

void ADigimonVenomNXTPlayerController::ServerSaveSeasonAndReturn_Implementation()
{
    if (!bAccountAuthenticated || !GetWorld()) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    if (!PS || PS->Profile.AccountId.IsEmpty() || !GM) return;
    if (CurrentBattle || (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()))
    {
        ClientShowMessage(TEXT("Season Mode"), TEXT("Finish your saved Season match before returning to the world."));
        return;
    }
    if (!GM->SavePlayer(PS))
    {
        ClientShowMessage(TEXT("Season Mode"), TEXT("Could not save your profile. Your career remains open; please try again."));
        return;
    }
    DigimonVenomNXTServerActivity::Record(this, TEXT("Season"), TEXT("Career saved"), TEXT("Player returned to the world menu."));
    ClientReturnFromSeason();
}

void ADigimonVenomNXTPlayerController::ClientReturnFromSeason_Implementation()
{
    SetFieldMenuOpen(false);
    ClientShowMessage_Implementation(TEXT("Season Mode"), TEXT("Season saved. Your calendar, champion and next match will wait for your return."));
}

void ADigimonVenomNXTPlayerController::ServerBeginSecondStory_Implementation()
{
    ServerEnterChronicles_Implementation();
}

void ADigimonVenomNXTPlayerController::ServerStartStoryBoss_Implementation(int32 Chapter)
{
    if (!bAccountAuthenticated) return;
    ClientShowMessage(TEXT("Paradox Chronicles"), TEXT("Enter your private Chronicles campaign, complete the local quest, then approach the Paradox guardian and press E."));
}

void ADigimonVenomNXTPlayerController::ServerStartFinalStoryBoss_Implementation()
{
    if (!bAccountAuthenticated) return;
    ClientShowMessage(TEXT("Paradox Chronicles"), TEXT("The final convergence awaits in Map 18. Complete its assignment and approach the three Paradox Mega guardians to begin."));
}

void ADigimonVenomNXTPlayerController::ServerSaveRankedDefender_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (!bAccountAuthenticated) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr;
    FString Message;
    if (!Ranked || !Ranked->SaveDefenderLineup(PS, Message)) ClientShowMessage(TEXT("Ranked Arena"), Message.IsEmpty()?TEXT("Could not save the defender lineup."):Message);
    else
    {
        Ranked->RefreshSeasonAndGameState(GetWorld()?GetWorld()->GetGameState<ADigimonVenomNXTGameState>():nullptr);
        DigimonVenomNXTServerActivity::Record(this, TEXT("Ranked"), TEXT("Defender lineup saved"), Message);
        ClientShowMessage(TEXT("Ranked Arena"), Message);
    }
}

void ADigimonVenomNXTPlayerController::ServerRunRankedQuickMatch_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (!bAccountAuthenticated) return;
    if (!RequirePublicFieldForBattle()) return;
    if (CurrentBattle)
    {
        ClientShowMessage(TEXT("Ranked Arena"), TEXT("Return from your current battle before entering the arena."));
        return;
    }
    const double Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0;
    if (Now - LastRankedMatchRequestTime < 2.0) return;
    LastRankedMatchRequestTime = Now;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr;
    if (PS && (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()))
    {
        ClientShowMessage(TEXT("Season Mode"), TEXT("Resume and finish your saved Season match before entering Ranked Arena."));
        return;
    }
    FString Message;
    ADigimonVenomNXTBattleActor* RankedBattle = nullptr;
    if (!Ranked || !Ranked->StartRankedMatch(PS, RankedBattle, Message))
    {
        ClientShowMessage(TEXT("Ranked Arena"), Message.IsEmpty() ? TEXT("Could not enter the ranked battle.") : Message);
        return;
    }
    // The same battle screen presents every automatic action before its result.
    // No result toast is sent here: entering ranked must never skip the fight.
    SetCurrentBattleServer(RankedBattle);
}

void ADigimonVenomNXTPlayerController::ServerAcknowledgeBattlePresentation_Implementation(ADigimonVenomNXTBattleActor* BattleActor)
{
    if (!bAccountAuthenticated) return;
    if (!IsValid(BattleActor) || CurrentBattle != BattleActor || !BattleActor->IsParticipant(this)) return;
    BattleActor->AcknowledgePresentationReady(this);
}

void ADigimonVenomNXTPlayerController::ServerSubmitBattleCommand_Implementation(const FDigimonBattleCommand& Command)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (!bAccountAuthenticated) return;
    FString Error;
    if (!CurrentBattle || !CurrentBattle->SubmitCommand(this, Command, Error))
    {
        DigimonVenomNXTServerActivity::Record(this, TEXT("Battle"), TEXT("Command rejected"), Error.IsEmpty() ? TEXT("No active battle or invalid command.") : Error, TEXT("Warning"));
        ClientShowMessage(TEXT("Battle"), Error.IsEmpty() ? TEXT("That battle command is not valid.") : Error);
    }
}

void ADigimonVenomNXTPlayerController::ServerLeaveFinishedBattle_Implementation()
{
    if (!bAccountAuthenticated) return;
    if (!CurrentBattle || !CurrentBattle->State.bFinished) return;
    ADigimonVenomNXTBattleActor* OldBattle = CurrentBattle;
    const bool bReturnToSeason = OldBattle->State.Kind == EDigimonBattleKind::Season;
    DigimonVenomNXTServerActivity::Record(this, TEXT("Battle"), TEXT("Result screen closed"), FString::Printf(TEXT("Battle %s"), *OldBattle->State.BattleId.ToString(EGuidFormats::Digits)));
    SetCurrentBattleServer(nullptr);
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetPawn()))
    {
        Tamer->ResetEncounterTracker();
        Tamer->SnapFollowerToTamer();
    }
    if (OldBattle && OldBattle->HasAuthority()) OldBattle->TryDestroyWhenUnused();
    if (bReturnToSeason) ClientReturnToSeason();
}

void ADigimonVenomNXTPlayerController::ClientReturnToSeason_Implementation()
{
    CreateNativeHUD();
    SetFieldMenuOpen(true);
    if (GameHUDWidget) GameHUDWidget->ShowPage(TEXT("Season"));
}

void ADigimonVenomNXTPlayerController::ServerSendWorldChat_Implementation(const FString& InMessage)
{
    ServerSendLocalChat_Implementation(InMessage);
}

void ADigimonVenomNXTPlayerController::ServerSendLocalChat_Implementation(const FString& InMessage)
{
    if (!bAccountAuthenticated || bLogoutServerCommitted || !GetWorld()) return;
    ADigimonVenomNXTPlayerState* SenderPS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* Mode = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    if (!SenderPS || SenderPS->Profile.AccountId.IsEmpty() || !Mode) return;
    const double Now = FPlatformTime::Seconds();
    // Bound work and reply frequency before processing untrusted text or moderation feedback.
    if (!DigimonVenomNXTWorldChatCore::CanSend(Now, LastWorldChatSendTime))
    {
        if (Now - LastWorldChatFeedbackTime >= 2.0)
        {
            LastWorldChatFeedbackTime = Now;
            ClientShowMessage(TEXT("WORLD chat"), TEXT("Please wait a moment before sending another message."));
        }
        return;
    }
    LastWorldChatSendTime = Now;
    const int32 Limit = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxChatCharacters, 1, 512);
    const auto Normalized = DigimonVenomNXTWorldChatCore::Normalize(*InMessage, InMessage.Len(), Limit);
    const FString Clean(Normalized.c_str());
    if (Clean.IsEmpty()) return;

    FString MuteReason;
    if (UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = DigimonVenomNXTServerActivity::Console(this))
        if (ServerConsole->IsAccountMuted(SenderPS->Profile.AccountId, MuteReason))
        {
            DigimonVenomNXTServerActivity::Record(this, TEXT("Moderation"), TEXT("Chat blocked"), TEXT("Account is muted; message body not recorded."), TEXT("Warning"));
            ClientShowMessage(TEXT("Chat muted"), MuteReason);
            return;
        }

    FDigimonChatMessage Chat;
    Chat.Kind = EDigimonChatMessageKind::Player;
    Chat.SenderAccountId = SenderPS->Profile.AccountId;
    Chat.Sender = SenderPS->Profile.Username;
    Chat.Message = Clean;
    Chat.UnixTime = FDateTime::UtcNow().ToUnixTimestamp();
    const int32 RecipientCount = Mode->BroadcastWorldChat(Chat);
    // Record routing, never arbitrary message bodies or credentials.
    DigimonVenomNXTServerActivity::Record(this, TEXT("Chat"), TEXT("WORLD message delivered"),
        FString::Printf(TEXT("%d characters | %d authenticated recipients | body omitted"), Clean.Len(), RecipientCount));
}

void ADigimonVenomNXTPlayerController::ServerRequestSave_Implementation()
{
    if (!bAccountAuthenticated || bLogoutServerCommitted) return;
    ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!Mode || !Mode->SavePlayer(GetPlayerState<ADigimonVenomNXTPlayerState>(), false))
        ClientShowMessage(TEXT("Progress"), TEXT("The server could not retain your profile. Your session remains open."));
    else ClientShowMessage(TEXT("Progress retained"), TEXT("Your profile is retained in server memory. Only the admin can request a disk checkpoint with /saveall or by logging out."));
}

void ADigimonVenomNXTPlayerController::ClientShowMessage_Implementation(const FString& Title, const FString& Message)
{
    // Authentication can restore a saved farm before its HUD is constructed.
    // Retain repair feedback instead of losing it between those owner RPCs.
    if (!GameHUDWidget && Title.StartsWith(TEXT("DigiFarm"))) PendingFarmMessage = Message;
    OnClientMessage.Broadcast(Title, Message);
    if (GameHUDWidget) GameHUDWidget->ShowToast(Title, Message);
}

void ADigimonVenomNXTPlayerController::ClientReceiveLocalChat_Implementation(const FDigimonChatMessage& Message)
{
    if (SocialComponent && !Message.SenderAccountId.IsEmpty() &&
        SocialComponent->State.Ignored.ContainsByPredicate([&Message](const FDigimonSocialContact& Contact)
        { return Contact.AccountId == Message.SenderAccountId; })) return;
    // Reliable join RPCs can arrive before the authentication response constructs the HUD.
    WorldChatHistory.Add(Message);
    if (WorldChatHistory.Num() > DigimonVenomNXTWorldChatCore::HistoryLimit)
        WorldChatHistory.RemoveAt(0, WorldChatHistory.Num() - DigimonVenomNXTWorldChatCore::HistoryLimit);
    OnChatReceived.Broadcast(Message);
    if (GameHUDWidget) GameHUDWidget->AppendChat(Message);
}

void ADigimonVenomNXTPlayerController::RefreshIgnoredChat()
{
    if (!IsLocalController() || !SocialComponent) return;
    const int32 Removed = WorldChatHistory.RemoveAll([this](const FDigimonChatMessage& Message)
    {
        return !Message.SenderAccountId.IsEmpty() && SocialComponent->State.Ignored.ContainsByPredicate(
            [&Message](const FDigimonSocialContact& Contact) { return Contact.AccountId == Message.SenderAccountId; });
    });
    if (Removed > 0 && GameHUDWidget) GameHUDWidget->RefreshChatHistory();
}

void ADigimonVenomNXTPlayerController::ClientPlayExplorationMusic_Implementation(int32 MapId)
{
    if (IsInRelay()) if (const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId())) MapId = Map->SourceMapId;
    LocalMusicMapId = FMath::Max(1, MapId);
    if (UDigimonVenomNXTAudioSubsystem* Audio = GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        Audio->PlayExplorationForMap(LocalMusicMapId);
}

void ADigimonVenomNXTPlayerController::ClientPlayAudioCue_Implementation(EDigimonAudioCue Cue, FGuid ReceiptId)
{
    if (!IsLocalController() || !ReceiptId.IsValid()) return;
    if (UDigimonVenomNXTAudioSubsystem* Audio=GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        Audio->PlayCueOnce(Cue,TEXT("server:")+ReceiptId.ToString());
}

int32 ADigimonVenomNXTPlayerController::GetLocalMusicMapId() const
{
    if (IsInRelay()) if (const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId())) return Map->SourceMapId;
    if (LocalMusicMapId != INDEX_NONE) return LocalMusicMapId;
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    return PS ? FMath::Max(1, PS->Profile.CurrentMapId) : 1;
}

void ADigimonVenomNXTPlayerController::ClientSetActiveMapPresentation_Implementation(int32 MapId)
{
    LocalMusicMapId = FMath::Max(1, MapId);
    if (!GetWorld()) return;

    // Never render the 500 serialized zone sprites directly at runtime. They remain
    // authoritative travel/bounds markers only. One local renderer is the sole map
    // surface for this player, eliminating z-fighting and stale visibility state.
    ADigimonVenomNXTMapZone* TargetZone = nullptr;
    int32 MatchedZones = 0;
    for (TActorIterator<ADigimonVenomNXTMapZone> It(GetWorld()); It; ++It)
    {
        It->SetLocalPresentationActive(false);
        if (It->GetRuntimeMapId() == MapId)
        {
            TargetZone = *It;
            ++MatchedZones;
        }
    }

    FVector ZoneCenter = FVector::ZeroVector;
    UPaperSprite* LegacyFallback = nullptr;
    if (TargetZone)
    {
        TargetZone->ApplyMapPresentation();
        ZoneCenter = TargetZone->GetActorLocation();
        LegacyFallback = TargetZone->MapSprite;
    }
    else
    {
        // Last-resort compatibility with the deterministic 10-column PublicWorld
        // grid used by every generated release. The server travel code will normally
        // have found the zone already; this path prevents a blank client surface if a
        // legacy actor name cannot be recovered locally.
        const int32 Index = FMath::Clamp(MapId, 1, 500) - 1;
        ZoneCenter = FVector((Index % 10) * 14000.0f, (Index / 10) * 11000.0f, 0.0f);
    }

    if (!IsValid(LocalMapRenderer))
    {
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        LocalMapRenderer = GetWorld()->SpawnActor<ADigimonVenomNXTLocalMapRenderer>(ADigimonVenomNXTLocalMapRenderer::StaticClass(), ZoneCenter, FRotator::ZeroRotator, Params);
    }

    const bool bRendered = IsValid(LocalMapRenderer) && LocalMapRenderer->ShowMap(MapId, ZoneCenter, LegacyFallback);
    if (IsValid(LocalMapRenderer)) LocalMapRenderer->SetActorHiddenInGame(IsInDigiFarm() || IsInRelay());
    if (!bRendered)
    {
        ClientShowMessage(TEXT("Map Presentation"), FString::Printf(TEXT("Map %03d artwork could not be loaded. Re-run only the Digimon Venom NXT core map import/repair tool."), MapId));
    }

    UE_LOG(LogTemp, Log, TEXT("Digimon Venom NXT local map render: Map=%d ZonesMatched=%d Renderer=%s Center=%s"),
        MapId, MatchedZones, bRendered ? TEXT("OK") : TEXT("FAILED"), *ZoneCenter.ToCompactString());
}

bool ADigimonVenomNXTPlayerController::AllocateDigiFarmOrigin()
{
    if (!HasAuthority() || !GetWorld()) return false;
    if (DigiFarmSlot != INDEX_NONE) return true;
    TSet<int32> UsedSlots;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* Other = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (Other && Other != this && Other->DigiFarmSlot != INDEX_NONE) UsedSlots.Add(Other->DigiFarmSlot);
    }
    // Private cells lie entirely outside the authored public-map grid. Allocation is
    // unique among live connections; account IDs and client coordinates cannot pick a cell.
    for (int32 SlotIndex = 0; SlotIndex < DigimonVenomNXTFarmSessionCore::MaximumPrivateSessions; ++SlotIndex)
    {
        if (UsedSlots.Contains(SlotIndex)) continue;
        DigiFarmSlot = SlotIndex;
        const auto Cell = DigimonVenomNXTFarmSessionCore::OriginForSlot(SlotIndex);
        FarmSession.Origin = FVector(Cell.X, Cell.Y, 0.0);
        return true;
    }
    return false;
}

void ADigimonVenomNXTPlayerController::CaptureDigiFarmPosition()
{
    if (!HasAuthority() || !IsInDigiFarm() || !GetPawn()) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || !PS->Profile.Farm.bInside) return;
    const FVector Local = GetPawn()->GetActorLocation() - FarmSession.Origin;
    if (!DigimonVenomNXTFarmCore::IsWalkable(Local.X, Local.Y, DigimonVenomNXTFarmCore::PlayerRadius)) return;
    PS->Profile.Farm.Position = FVector2D(Local.X, Local.Y);
    PS->Profile.Farm.bHasPosition = true;
}

bool ADigimonVenomNXTPlayerController::EnterDigiFarmServer(bool bRestoreSavedSession, FString& OutError)
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    APawn* FarmPawn = GetPawn();
    if (!HasAuthority() || !bAccountAuthenticated || !PS || PS->Profile.AccountId.IsEmpty() || !FarmPawn || !GM)
    { OutError = TEXT("Your tamer is not ready to enter DigiFarm yet."); return false; }
    if (IsInDigiFarm()) return true;
    if (CurrentBattle || (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()) || HasPendingStoryBattle())
    { OutError = TEXT("Finish and return from your current or saved battle before entering DigiFarm."); return false; }
    if (!LoadObject<UPaperSprite>(nullptr, TEXT("/DigimonVenomNXT/Generated/Maps/SP_DigiFarmIsland.SP_DigiFarmIsland")))
    {
        OutError = TEXT("DigiFarm island artwork has not been prepared on this host. Run Tools > Digimon Venom NXT: Prepare Private DigiFarm in the editor, save the generated assets, then restart the host.");
        return false;
    }
    if (!AllocateDigiFarmOrigin())
    { OutError = TEXT("No private farm session is available. Please try again shortly."); return false; }

    CaptureRelayPosition();
    const FDigimonFarmState Before = PS->Profile.Farm;
    const FVector BeforeLocation = FarmPawn->GetActorLocation();
    FDigimonFarmState& Farm = PS->Profile.Farm;
    if (!bRestoreSavedSession || !Farm.bHasReturnLocation)
    {
        Farm.ReturnMapId = FMath::Max(1, PS->Profile.CurrentMapId);
        Farm.ReturnLocation = DigimonVenomNXTCampaign::IsActive(PS->Profile) && DigimonVenomNXTCampaign::Progress(PS->Profile, PS->Profile.ActiveStoryCampaign).bHasReturnLocation
            ? DigimonVenomNXTCampaign::Progress(PS->Profile, PS->Profile.ActiveStoryCampaign).ReturnLocation : BeforeLocation;
        Farm.bHasReturnLocation = !Farm.ReturnLocation.ContainsNaN();
    }
    const auto Spawn = Farm.bHasPosition
        ? DigimonVenomNXTFarmCore::FindSafePoint(Farm.Position.X, Farm.Position.Y, DigimonVenomNXTFarmCore::PlayerRadius)
        : DigimonVenomNXTFarmCore::FindSafePoint(DigimonVenomNXTFarmCore::SpawnX, DigimonVenomNXTFarmCore::SpawnY, DigimonVenomNXTFarmCore::PlayerRadius);
    Farm.Position = FVector2D(Spawn.X, Spawn.Y);
    Farm.bHasPosition = true;
    Farm.bInside = true;
    FarmSession.bActive = true;
    if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(FarmPawn->GetMovementComponent())) Movement->StopMovementImmediately();
    FarmPawn->SetActorLocation(FarmSession.Origin + FVector(Spawn.X, Spawn.Y, 100.0), false, nullptr, ETeleportType::TeleportPhysics);
    if (!GM->SavePlayer(PS))
    {
        PS->Profile.Farm = Before;
        FarmSession.bActive = false;
        DigiFarmSlot = INDEX_NONE;
        FarmSession.Origin = FVector::ZeroVector;
        FarmPawn->SetActorLocation(BeforeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        OutError = TEXT("Could not save your farm entry. Your location is unchanged; please try again.");
        return false;
    }
    PS->MarkProfileChanged();
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(FarmPawn))
    {
        Tamer->ResetEncounterTracker();
        Tamer->SnapFollowerToTamer();
    }
    ++FarmSession.Revision;
    FarmPawn->ForceNetUpdate();
    ForceNetUpdate();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Travel"), bRestoreSavedSession ? TEXT("Private farm restored") : TEXT("Private farm entered"), TEXT("Location saved; private farm visible only to its owner."));
    ClientSetDigiFarmPresentation(true, FarmSession.Origin, PS->Profile.CurrentMapId, FarmSession.Revision);
    return true;
}

bool ADigimonVenomNXTPlayerController::LeaveDigiFarmServer(FString& OutError)
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    APawn* FarmPawn = GetPawn();
    if (!HasAuthority() || !bAccountAuthenticated || !PS || !FarmPawn || !GM || !WorldSystem)
    { OutError = TEXT("Your tamer is not ready to leave DigiFarm yet."); return false; }
    if (!IsInDigiFarm()) return true;
    if (CurrentBattle || HasPendingStoryBattle() || (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()))
    { OutError = TEXT("Resume and return from your saved battle first."); return false; }
    CaptureDigiFarmPosition();
    const FDigimonPlayerProfile BeforeProfile = PS->Profile;
    const FDigimonRelaySession BeforeRelaySession = RelaySession;
    const int32 BeforeRelaySlot = RelaySlot;
    const FVector BeforeLocation = FarmPawn->GetActorLocation();
    const int32 SavedCampaign = DigimonVenomNXTRelaySessionCore::SavedCampaign(static_cast<int32>(PS->Profile.ActiveStoryCampaign),
        PS->Profile.Relay.bInside, PS->Profile.Chronicles.bInside, false, false, PS->Profile.GhostLine.bInside, false);
    const bool bReturnToRelay = DigimonVenomNXTRelaySessionCore::ValidCampaign(SavedCampaign);
    int32 ReturnMapId = FMath::Max(1, PS->Profile.CurrentMapId);
    FVector Destination = FVector::ZeroVector;
    if (bReturnToRelay)
    {
        RelaySession.Campaign = static_cast<EDigimonPrivateCampaign>(SavedCampaign);
        FDigimonRelayProgress& Journey = DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign());
        RelaySession.MapId = Journey.MapId;
        if (!AllocateRelayOrigin())
        {
            RelaySession = BeforeRelaySession; RelaySlot = BeforeRelaySlot;
            OutError = TEXT("All private campaign spaces are in use. You remain safely in DigiFarm; please try again later [CAMPAIGN_CAPACITY]."); return false;
        }
        if (!PrepareRelayPlacements(&OutError))
        {
            RelaySession = BeforeRelaySession; RelaySlot = BeforeRelaySlot;
            return false;
        }
        Destination = GetRelayOrigin() + RelayArrivalLocal;
        if (Journey.bHasPosition)
        {
            const FVector Saved = GetRelayOrigin() + FVector(Journey.Position.X, Journey.Position.Y, 100);
            if (IsRelayLocationWalkable(Saved)) Destination = Saved;
        }
        PS->Profile.ActiveStoryCampaign = GetStoryCampaign();
        PS->Profile.Relay.bInside = GetStoryCampaign() == EDigimonPrivateCampaign::Relay;
        PS->Profile.Chronicles.bInside = GetStoryCampaign() == EDigimonPrivateCampaign::ParadoxChronicles;
        PS->Profile.GhostLine.bInside = GetStoryCampaign() == EDigimonPrivateCampaign::GhostLine;
        RelaySession.bActive = true;
    }
    else
    {
        ADigimonVenomNXTMapZone* Zone = WorldSystem->FindMapZone(ReturnMapId);
        if (!Zone) { ReturnMapId = 1; Zone = WorldSystem->FindMapZone(ReturnMapId); }
        if (!Zone) { OutError = TEXT("Your return habitat is unavailable. Your farm remains open."); return false; }
        Zone->ApplyMapPresentation();
        Destination = Zone->GetPlayerSpawnLocation();
        const FDigimonFarmState& Farm = PS->Profile.Farm;
        if (Farm.bHasReturnLocation && Farm.ReturnMapId == ReturnMapId &&
            !Farm.ReturnLocation.ContainsNaN() && WorldSystem->IsWorldLocationWalkable(ReturnMapId, Farm.ReturnLocation))
            Destination = Farm.ReturnLocation;
        if (!WorldSystem->IsWorldLocationWalkable(ReturnMapId, Destination))
        { OutError = TEXT("Your return habitat has no safe spawn. Please ask the host to repair its map collision data."); return false; }
        RelaySession.bActive = false;
    }
    PS->Profile.Farm.bInside = false;
    PS->Profile.CurrentMapId = ReturnMapId;
    FarmSession.bActive = false;
    if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(FarmPawn->GetMovementComponent())) Movement->StopMovementImmediately();
    FarmPawn->SetActorLocation(Destination, false, nullptr, ETeleportType::TeleportPhysics);
    if (!GM->SavePlayer(PS))
    {
        PS->Profile = BeforeProfile;
        RelaySession = BeforeRelaySession; RelaySlot = BeforeRelaySlot;
        FarmSession.bActive = true;
        FarmPawn->SetActorLocation(BeforeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        OutError = TEXT("Could not save your farm exit. You remain safely in your farm; please try again.");
        return false;
    }
    DigiFarmSlot = INDEX_NONE;
    PS->MarkProfileChanged();
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(FarmPawn))
    {
        Tamer->ResetEncounterTracker();
        Tamer->SnapFollowerToTamer();
    }
    ++FarmSession.Revision;
    FarmPawn->ForceNetUpdate();
    ForceNetUpdate();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Travel"), TEXT("Private farm left"), bReturnToRelay ? TEXT("Saved return to private campaign.") : FString::Printf(TEXT("Saved return to public map %d."), ReturnMapId));
    ClientSetDigiFarmPresentation(false, FarmSession.Origin, ReturnMapId, FarmSession.Revision);
    if (bReturnToRelay || BeforeRelaySession.bActive) PublishRelaySession();
    return true;
}

void ADigimonVenomNXTPlayerController::RestoreDigiFarmAfterLogin()
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!HasAuthority() || !PS || !PS->Profile.Farm.bInside) return;
    if ((!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()) || HasPendingStoryBattle())
    {
        // A legacy/inconsistent farm flag cannot prevent a suspended Season decision.
        PS->Profile.Farm.bInside = false;
        if (ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr) GM->SavePlayer(PS);
        PS->MarkProfileChanged();
        return;
    }
    FString Error;
    if (!EnterDigiFarmServer(true, Error))
    {
        PS->Profile.Farm.bInside = false;
        if (ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr) GM->SavePlayer(PS);
        PS->MarkProfileChanged();
        ClientShowMessage(TEXT("DigiFarm"), Error);
    }
}

void ADigimonVenomNXTPlayerController::ServerEnterDigiFarm_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!EnterDigiFarmServer(false, Error)) ClientShowMessage(TEXT("DigiFarm"), Error);
}

void ADigimonVenomNXTPlayerController::ServerLeaveDigiFarm_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!LeaveDigiFarmServer(Error)) ClientShowMessage(TEXT("DigiFarm"), Error);

}

bool ADigimonVenomNXTPlayerController::RequirePublicFieldForBattle()
{
    if (HasPendingStoryBattle()) { ClientShowMessage(TEXT("Saved campaign battle"), TEXT("Resume and finish your saved campaign battle first.")); return false; }
    if (!IsInDigiFarm() && !IsInRelay()) return true;
    if (IsInRelay()) { ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), TEXT("Leave Campaign before entering public battles.")); return false; }
    ClientShowMessage(TEXT("DigiFarm"), TEXT("Leave your private farm before starting a battle. Your residents will be waiting when you return."));
    return false;
}

void ADigimonVenomNXTPlayerController::ClientSetDigiFarmPresentation_Implementation(bool bInside, FVector Origin, int32 ReturnMapId, uint64 Revision)
{
    if (!DigimonVenomNXTFarmSessionCore::AcceptRevision(AppliedLocalFarmSession.Revision, Revision)) return;
    FarmSession.Revision = Revision;
    FarmSession.bActive = bInside;
    FarmSession.Origin = Origin;
    AppliedLocalFarmSession = FarmSession;
    LocalMusicMapId = FMath::Max(1, ReturnMapId);
    RefreshDigiFarmPresentation();
    RefreshRelayPresentation();
    RefreshLocalActorPrivacy();
    if (bInside)
    {
        const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
        SetFieldMenuOpen(bFarmPresentationFailurePending || (PS && !PS->HasStarter()));
    }
    else
    {
        ClientSetActiveMapPresentation_Implementation(ReturnMapId);
        ClientPlayExplorationMusic_Implementation(ReturnMapId);
        const bool bReportAssetFailure = bFarmPresentationFailurePending;
        bFarmPresentationFailurePending = false;
        SetFieldMenuOpen(bReportAssetFailure);
        if (bReportAssetFailure)
            ClientShowMessage_Implementation(TEXT("DigiFarm artwork missing"), TEXT("You were returned safely to your previous level. Run Tools > Digimon Venom NXT: Prepare Private DigiFarm and rebuild this client with the generated island assets."));
    }
    // Release previous menu/button focus while preserving clickable farm quick actions.
    ApplyFieldInputMode();
}

void ADigimonVenomNXTPlayerController::OnRep_DigiFarmSession()
{
    // A reliable presentation RPC and an older property bunch may meet in either
    // order. Never let an old entry resurrect the farm after a newer exit.
    if (!DigimonVenomNXTFarmSessionCore::AcceptRevision(AppliedLocalFarmSession.Revision, FarmSession.Revision))
    {
        FarmSession = AppliedLocalFarmSession;
        return;
    }
    AppliedLocalFarmSession = FarmSession;
    RefreshDigiFarmPresentation();
    RefreshRelayPresentation();
    RefreshLocalActorPrivacy();
}

void ADigimonVenomNXTPlayerController::RefreshDigiFarmPresentation()
{
    if (!IsLocalController() || !GetWorld()) return;
    const bool bPresentFarm = IsInDigiFarm() && !FarmSession.Origin.IsNearlyZero();
    if (bPresentFarm && bFarmPresentationFailurePending) return;
    if (bPresentFarm && (!IsValid(DigiFarmScene) || !PresentedFarmOrigin.Equals(FarmSession.Origin)))
    {
        if (IsValid(DigiFarmScene)) DigiFarmScene->Destroy();
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        DigiFarmScene = GetWorld()->SpawnActor<ADigimonVenomNXTFarmScene>(ADigimonVenomNXTFarmScene::StaticClass(), FarmSession.Origin, FRotator::ZeroRotator, Params);
        if (!IsValid(DigiFarmScene) || !DigiFarmScene->InitializeFor(this, FarmSession.Origin))
        {
            // An older/unprepared client must never be left walking an invisible farm.
            // The authenticated server restores the saved public location and profile.
            bFarmPresentationFailurePending = true;
            CreateNativeHUD();
            SetFieldMenuOpen(true);
            ClientShowMessage_Implementation(TEXT("DigiFarm artwork missing"), TEXT("The island asset is missing on this client. Returning to your previous level..."));
            ServerLeaveDigiFarm();
            return;
        }
        PresentedFarmOrigin = FarmSession.Origin;
    }
    if (bLocalFarmPresentationActive != bPresentFarm)
    {
        bLocalFarmPresentationActive = bPresentFarm;
        if (IsValid(DigiFarmScene)) DigiFarmScene->SetFarmVisible(bPresentFarm);
        if (IsValid(LocalMapRenderer)) LocalMapRenderer->SetActorHiddenInGame(bPresentFarm || IsInRelay());
        if (UDigimonVenomNXTAudioSubsystem* Audio = GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
            Audio->SetDigiFarmActive(bPresentFarm);
        ApplyFieldInputMode();
    }
}

void ADigimonVenomNXTPlayerController::RefreshLocalActorPrivacy()
{
    if (!IsLocalController() || !GetWorld()) return;
    // Actor channel closure can lag behind farm entry. Hide only local rendering,
    // never replicated Actor::bHidden (which would hide remote players for everyone).
    for (TActorIterator<ADigimonVenomNXTTamerCharacter> It(GetWorld()); It; ++It)
        if (UPaperFlipbookComponent* Sprite = It->GetSprite()) Sprite->SetVisibility(It->IsVisibleToViewer(this));
    for (TActorIterator<ADigimonVenomNXTAIRivalAvatar> It(GetWorld()); It; ++It)
        if (It->Sprite) It->Sprite->SetVisibility(!IsInDigiFarm() && !IsInRelay() && It->MapId == GetLocalMusicMapId());
    for (TActorIterator<ADigimonVenomNXTPartnerFollower> It(GetWorld()); It; ++It)
    {
        const bool bVisible =
            (It->Tamer && It->Tamer->IsVisibleToViewer(this)) ||
            (!IsInDigiFarm() && !IsInRelay() && It->RivalTamer && It->RivalTamer->MapId == GetLocalMusicMapId());
        if (UPaperFlipbookComponent* Sprite = It->GetSprite()) Sprite->SetVisibility(bVisible);
    }
}

bool ADigimonVenomNXTPlayerController::AllocateRelayOrigin()
{
    if (!HasAuthority() || !GetWorld()) return false;
    if (RelaySlot != INDEX_NONE)
    {
        const auto Origin = DigimonVenomNXTRelaySessionCore::OriginForSlot(RelaySlot);
        RelaySession.Origin = FVector(Origin.X, Origin.Y, 0);
        return true;
    }
    TSet<int32> Used;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (const ADigimonVenomNXTPlayerController* Other = Cast<ADigimonVenomNXTPlayerController>(It->Get()))
            if (Other != this && Other->RelaySlot != INDEX_NONE) Used.Add(Other->RelaySlot);
    for (int32 Slot = 0; Slot < DigimonVenomNXTRelaySessionCore::MaximumPrivateSessions; ++Slot)
    {
        if (Used.Contains(Slot)) continue;
        RelaySlot = Slot;
        const auto Origin = DigimonVenomNXTRelaySessionCore::OriginForSlot(Slot);
        RelaySession.Origin = FVector(Origin.X, Origin.Y, 0);
        return true;
    }
    return false;
}

bool ADigimonVenomNXTPlayerController::PrepareRelayPlacements(FString* OutError) const
{
    if (OutError) OutError->Reset();
    if (PlacementCampaign == GetStoryCampaign() && PlacementMapId == GetRelayMapId() && !RelayNPCLocalLocations.IsEmpty()) return true;
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId());
    UDigimonVenomNXTWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!Map || !World)
    {
        if (OutError) *OutError = TEXT("The campaign map definition or world is unavailable [CAMPAIGN_WORLD]. Your saved progress is safe.");
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT campaign placement: campaign=%d map=%d; definition=%s world subsystem=%s."),
            static_cast<int32>(GetStoryCampaign()), GetRelayMapId(), Map ? TEXT("present") : TEXT("missing"), World ? TEXT("present") : TEXT("missing"));
        return false;
    }
    FString MapError;
    if (!World->ValidatePrivateMapContent(Map->SourceMapId, MapError))
    {
        if (OutError) *OutError = MapError;
        return false;
    }
    // A failed switch must leave the previous map's complete placement cache
    // intact. Never publish a partial new NPC list under the old cache key.
    FVector CandidateEntry, CandidateExit, CandidateArrival;
    TMap<FName, FVector> CandidateLocations;
    TArray<FVector> Occupied;
    const auto Place = [&](const FVector2D& UV, FVector& Local, const FString& Label) -> bool
    {
        if (World->ResolvePrivateMapPoint(Map->SourceMapId, UV, Local, Occupied)) return true;
        if (OutError) *OutError = FString::Printf(TEXT("Campaign habitat %03d: a safe position could not be found for %s [MAP_PLACEMENT]. Your saved progress is safe."), Map->SourceMapId, *Label);
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT campaign placement [MAP_PLACEMENT]: campaign=%d map=%d source=%d target=%s UV=(%.9f, %.9f)."),
            static_cast<int32>(GetStoryCampaign()), Map->MapId, Map->SourceMapId, *Label, UV.X, UV.Y);
        return false;
    };
    if (!World->ResolvePrivateMapPoint(Map->SourceMapId, Map->ArrivalPosition, CandidateArrival))
    { if (OutError) *OutError = TEXT("This campaign arrival point is unavailable."); return false; }
    // Place portals first; NPCs are separated so an interaction can never target a portal by accident.
    if (!Place(Map->EntryPosition, CandidateEntry, TEXT("the entrance"))) return false;
    Occupied.Add(CandidateEntry);
    if (!Place(Map->ExitPosition, CandidateExit, TEXT("the exit"))) return false;
    Occupied.Add(CandidateExit);
    for (const FDigimonRelayNPC& NPC : DigimonVenomNXTCampaign::NPCsForMap(GetStoryCampaign(), Map->MapId))
    {
        FVector Local;
        if (NPC.Role == EDigimonRelayRole::Challenger)
        {
            for (const FDigimonRelayNPC& StageNPC : DigimonVenomNXTCampaign::NPCsForMap(GetStoryCampaign(), Map->MapId))
                if (StageNPC.Role == EDigimonRelayRole::Champion)
                    if (const FVector* Stage = CandidateLocations.Find(StageNPC.Id)) { const FVector SharedStage = *Stage; CandidateLocations.Add(NPC.Id, SharedStage); break; }
            if (CandidateLocations.Contains(NPC.Id)) continue;
        }
        if (!Place(NPC.Position, Local, NPC.Id.ToString())) return false;
        CandidateLocations.Add(NPC.Id, Local);
        Occupied.Add(Local);
    }
    RelayArrivalLocal = CandidateArrival;
    RelayEntryLocal = CandidateEntry;
    RelayExitLocal = CandidateExit;
    RelayNPCLocalLocations = MoveTemp(CandidateLocations);
    PlacementMapId = Map->MapId;
    PlacementCampaign = GetStoryCampaign();
    return true;
}

FVector ADigimonVenomNXTPlayerController::GetRelayNPCLocation(FName NPCId) const
{
    if (!PrepareRelayPlacements()) return FVector::ZeroVector;
    const FVector* Local = RelayNPCLocalLocations.Find(NPCId);
    return Local ? GetRelayOrigin() + *Local : FVector::ZeroVector;
}

FVector ADigimonVenomNXTPlayerController::GetRelayPortalLocation(bool bForward) const
{
    if (!PrepareRelayPlacements()) return FVector::ZeroVector;
    return GetRelayOrigin() + (bForward ? RelayExitLocal : RelayEntryLocal);
}

int32 ADigimonVenomNXTPlayerController::GetRelayPortalTarget(bool bForward) const
{
    if (!DigimonVenomNXTCampaign::IsValid(GetStoryCampaign())) return INDEX_NONE;
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    const bool bReturnToHeadquarters = IsInGhostLine() && PS && PS->Profile.GhostLine.bComplete;
    return DigimonVenomNXTRelaySessionCore::PortalTarget(GetRelayMapId(), bForward,
        DigimonVenomNXTCampaign::Maps(GetStoryCampaign()).Num(), bReturnToHeadquarters);
}

bool ADigimonVenomNXTPlayerController::CanUseRelayPortal(bool bForward) const
{
    if (!IsInRelay() || !GetPawn() || CurrentBattle || HasPendingStoryBattle() || HasPendingWorldBattle()) return false;
    if (GetRelayPortalTarget(bForward) == INDEX_NONE) return false;
    const FVector Delta = GetPawn()->GetActorLocation() - GetRelayPortalLocation(bForward);
    return DigimonVenomNXTRelaySessionCore::WithinInteraction(Delta.X, Delta.Y) && IsRelaySegmentWalkable(GetPawn()->GetActorLocation(), GetRelayPortalLocation(bForward));
}

FName ADigimonVenomNXTPlayerController::GetNearestRelayNPC() const
{
    if (!IsInRelay() || !GetPawn() || CurrentBattle || HasPendingStoryBattle() || HasPendingWorldBattle() || !PrepareRelayPlacements()) return NAME_None;
    FName Nearest = NAME_None;
    double Distance = FMath::Square(DigimonVenomNXTRelaySessionCore::InteractionRadius);
    for (const auto& Pair : RelayNPCLocalLocations)
    {
        if (!IsActiveRelayNPC(Pair.Key)) continue;
        const FVector Location = GetRelayOrigin() + Pair.Value;
        const double Candidate = FVector::DistSquared2D(GetPawn()->GetActorLocation(), Location);
        if (Candidate <= Distance && IsRelaySegmentWalkable(GetPawn()->GetActorLocation(), Location)) { Distance = Candidate; Nearest = Pair.Key; }
    }
    return Nearest;
}

bool ADigimonVenomNXTPlayerController::ValidateRelayNPCInteraction(FName NPCId, FString& OutError) const
{
    const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(GetStoryCampaign(), NPCId);
    if (!HasAuthority() || !bAccountAuthenticated || !IsInRelay() || !NPC || NPC->MapId != GetRelayMapId() || !GetPawn())
    { OutError = TEXT("Enter this NPC's campaign map before interacting."); return false; }
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (CurrentBattle || !PS || PS->Profile.ActiveStoryCampaign != GetStoryCampaign() || !DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).bInside || HasPendingStoryBattle() || HasPendingWorldBattle()) { OutError = TEXT("Resume or return from your battle first."); return false; }
    if (!IsActiveRelayNPC(NPCId)) { OutError = TEXT("That character is not present in your campaign."); return false; }
    const FVector Location = GetRelayNPCLocation(NPCId);
    const FVector Delta = GetPawn()->GetActorLocation() - Location;
    if (Location.IsNearlyZero() || FMath::Abs(Delta.Z) > 150.0 || !DigimonVenomNXTRelaySessionCore::WithinInteraction(Delta.X, Delta.Y) || !IsRelaySegmentWalkable(GetPawn()->GetActorLocation(), Location))
    { OutError = TEXT("Walk closer to this character, then press E to interact."); return false; }
    return true;
}

bool ADigimonVenomNXTPlayerController::IsRelayLocationWalkable(const FVector& Location) const
{
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId());
    const UDigimonVenomNXTWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    return Map && World && World->IsPrivateMapLocationWalkable(Map->SourceMapId, GetRelayOrigin(), Location);
}
bool ADigimonVenomNXTPlayerController::IsRelaySegmentWalkable(const FVector& From, const FVector& To) const
{
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId());
    const UDigimonVenomNXTWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    return Map && World && World->IsPrivateMapSegmentWalkable(Map->SourceMapId, GetRelayOrigin(), From, To);
}

void ADigimonVenomNXTPlayerController::CaptureRelayPosition()
{
    if (!HasAuthority() || !IsInRelay() || !GetPawn()) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || !DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).bInside || !IsRelayLocationWalkable(GetPawn()->GetActorLocation())) return;
    const FVector Local = GetPawn()->GetActorLocation() - GetRelayOrigin();
    DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).Position = FVector2D(Local.X, Local.Y);
    DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).bHasPosition = true;
}

void ADigimonVenomNXTPlayerController::PublishRelaySession()
{
    ++RelaySession.Revision;
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetPawn()))
    { Tamer->ResetEncounterTracker(); Tamer->SnapFollowerToTamer(); Tamer->ForceNetUpdate(); }
    ForceNetUpdate();
    ClientSetRelayPresentation(RelaySession.Campaign, RelaySession.bActive, RelaySession.MapId, RelaySession.Origin, RelaySession.Revision);
}

bool ADigimonVenomNXTPlayerController::HasPendingWorldBattle() const
{
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    return PS && !PS->Profile.WorldBattleCheckpointJson.IsEmpty();
}

bool ADigimonVenomNXTPlayerController::HasPendingStoryBattle() const
{
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    return PS && DigimonVenomNXTCampaign::HasPendingBattle(PS->Profile);
}

bool ADigimonVenomNXTPlayerController::EnterCampaignServer(EDigimonPrivateCampaign Campaign, bool bRestoreSavedSession, FString& OutError)
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!HasAuthority() || !bAccountAuthenticated || !PS || !PS->HasStarter() || !GetPawn() || !GM)
    { OutError = TEXT("Choose your starter and finish signing in before entering a campaign."); return false; }
    if (!DigimonVenomNXTCampaign::IsValid(Campaign))
    { OutError = TEXT("This campaign is unavailable."); return false; }
    if (IsInDigiFarm()) { OutError = TEXT("Leave DigiFarm to return to your campaign first."); return false; }
    if (!DigimonVenomNXTRelaySessionCore::MayEnterCampaign(static_cast<int32>(Campaign), static_cast<int32>(GetStoryCampaign()), IsInRelay(),
        CurrentBattle != nullptr, (!PS->Profile.Season.BattleCheckpointJson.IsEmpty() || !PS->Profile.WorldBattleCheckpointJson.IsEmpty()),
        !PS->Profile.Relay.BattleCheckpointJson.IsEmpty(), !PS->Profile.Chronicles.BattleCheckpointJson.IsEmpty(),
        !PS->Profile.GhostLine.BattleCheckpointJson.IsEmpty()))
    { OutError = TEXT("Finish or resume your saved battle before changing campaigns."); return false; }
    if (IsInRelay() && GetStoryCampaign() == Campaign && !bRestoreSavedSession) return true;

    // Capture the journey being left, but never copy the party, inventory or currencies.
    CaptureRelayPosition();
    const FDigimonPlayerProfile BeforeProfile = PS->Profile;
    const FDigimonRelaySession BeforeSession = RelaySession;
    const int32 BeforeSlot = RelaySlot;
    const FVector BeforeLocation = GetPawn()->GetActorLocation();
    const bool bSwitchingCampaign = IsInRelay();
    const FDigimonRelayProgress PreviousJourney = DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign());
    DigimonVenomNXTCampaign::Reconcile(PS->Profile);
    FDigimonRelayProgress& Journey = DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign);
    if (!DigimonVenomNXTCampaign::CanEnterMap(Campaign, Journey, Journey.MapId))
    { Journey.MapId = 1; Journey.bHasPosition = false; }
    RelaySession.Campaign = Campaign;
    RelaySession.MapId = Journey.MapId;
    if (!AllocateRelayOrigin())
    {
        PS->Profile = BeforeProfile; RelaySession = BeforeSession; RelaySlot = BeforeSlot;
        OutError = TEXT("All private campaign spaces are currently in use. Please try again after a player leaves [CAMPAIGN_CAPACITY]."); return false;
    }
    if (!PrepareRelayPlacements(&OutError))
    {
        PS->Profile = BeforeProfile; RelaySession = BeforeSession; RelaySlot = BeforeSlot;
        return false;
    }
    if (bSwitchingCampaign)
    {
        // Carry the original PUBLIC return address across an atomic campaign switch.
        Journey.ReturnMapId = PreviousJourney.ReturnMapId;
        Journey.ReturnLocation = PreviousJourney.ReturnLocation;
        Journey.bHasReturnLocation = PreviousJourney.bHasReturnLocation;
    }
    else if (!bRestoreSavedSession || !Journey.bHasReturnLocation)
    {
        Journey.ReturnMapId = PS->Profile.CurrentMapId;
        Journey.ReturnLocation = BeforeLocation;
        Journey.bHasReturnLocation = !BeforeLocation.ContainsNaN();
    }
    FVector Destination = GetRelayOrigin() + RelayArrivalLocal;
    if (Journey.bHasPosition)
    {
        const FVector Saved = GetRelayOrigin() + FVector(Journey.Position.X, Journey.Position.Y, 100);
        if (IsRelayLocationWalkable(Saved)) Destination = Saved;
    }
    PS->Profile.ActiveStoryCampaign = Campaign;
    PS->Profile.Relay.bInside = Campaign == EDigimonPrivateCampaign::Relay;
    PS->Profile.Chronicles.bInside = Campaign == EDigimonPrivateCampaign::ParadoxChronicles;
    PS->Profile.GhostLine.bInside = Campaign == EDigimonPrivateCampaign::GhostLine;
    RelaySession.bActive = true;
    if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent())) Movement->StopMovementImmediately();
    GetPawn()->SetActorLocation(Destination, false, nullptr, ETeleportType::TeleportPhysics);
    CaptureRelayPosition();
    if (!GM->SavePlayer(PS))
    {
        PS->Profile = BeforeProfile; RelaySession = BeforeSession; RelaySlot = BeforeSlot;
        GetPawn()->SetActorLocation(BeforeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        OutError = TEXT("Could not save campaign entry. Your previous location is restored; try again."); return false;
    }
    PS->MarkProfileChanged();
    PublishRelaySession();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Campaign"), bRestoreSavedSession ? TEXT("Private campaign restored") : TEXT("Private campaign entered"), FString::Printf(TEXT("%s | map %d | saved"), *DigimonVenomNXTCampaign::Name(Campaign), GetRelayMapId()));
    return true;
}

bool ADigimonVenomNXTPlayerController::LeaveRelayServer(FString& OutError)
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    UDigimonVenomNXTWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr;
    if (!HasAuthority() || !bAccountAuthenticated || !PS || !GetPawn() || !GM || !World) return false;
    if (!IsInRelay()) { OutError = TEXT("Leave DigiFarm before leaving the campaign."); return false; }
    if (CurrentBattle || HasPendingStoryBattle() || HasPendingWorldBattle())
    { OutError = TEXT("Finish and return from your campaign battle before leaving."); return false; }
    CaptureRelayPosition();
    const FDigimonRelayProgress Before = DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign());
    const FVector BeforeLocation = GetPawn()->GetActorLocation();
    int32 ReturnMap = FMath::Max(1, Before.ReturnMapId);
    ADigimonVenomNXTMapZone* Zone = World->FindMapZone(ReturnMap);
    if (!Zone) { ReturnMap = 1; Zone = World->FindMapZone(1); }
    if (!Zone) { OutError = TEXT("Your public return habitat is unavailable."); return false; }
    Zone->ApplyMapPresentation();
    FVector Destination = Zone->GetPlayerSpawnLocation();
    if (Before.bHasReturnLocation && Before.ReturnMapId == ReturnMap && World->IsWorldLocationWalkable(ReturnMap, Before.ReturnLocation)) Destination = Before.ReturnLocation;
    if (!World->IsWorldLocationWalkable(ReturnMap, Destination)) { OutError = TEXT("Your public return habitat has no safe spawn. Ask the host to repair its map collision."); return false; }
    const int32 BeforeMap = PS->Profile.CurrentMapId;
    RelaySession.bActive = false;
    DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).bInside = false;
    PS->Profile.CurrentMapId = ReturnMap;
    if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent())) Movement->StopMovementImmediately();
    GetPawn()->SetActorLocation(Destination, false, nullptr, ETeleportType::TeleportPhysics);
    if (!GM->SavePlayer(PS))
    {
        RelaySession.bActive = true; DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()) = Before; PS->Profile.CurrentMapId = BeforeMap;
        GetPawn()->SetActorLocation(BeforeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        OutError = TEXT("Could not save campaign exit. You remain in your private campaign."); return false;
    }
    RelaySlot = INDEX_NONE;
    PS->MarkProfileChanged();
    PublishRelaySession();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Campaign"), TEXT("Private campaign left"), FString::Printf(TEXT("%s | saved return to public map %d"), *DigimonVenomNXTCampaign::Name(GetStoryCampaign()), ReturnMap));
    ClientSetActiveMapPresentation(ReturnMap);
    ClientPlayExplorationMusic(ReturnMap);
    return true;
}

void ADigimonVenomNXTPlayerController::RestoreRelayAfterLogin()
{
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!HasAuthority() || !PS || IsInDigiFarm()) return;
    // Restore the suspended decision before any stale world/farm flag can redirect the account.
    const int32 SavedCampaign = DigimonVenomNXTRelaySessionCore::SavedCampaign(static_cast<int32>(PS->Profile.ActiveStoryCampaign),
        PS->Profile.Relay.bInside, PS->Profile.Chronicles.bInside,
        !PS->Profile.Relay.BattleCheckpointJson.IsEmpty(), !PS->Profile.Chronicles.BattleCheckpointJson.IsEmpty(),
        PS->Profile.GhostLine.bInside, !PS->Profile.GhostLine.BattleCheckpointJson.IsEmpty());
    if (SavedCampaign == -1) return;
    if (SavedCampaign == -2) { ClientShowMessage(TEXT("Campaign recovery"), TEXT("Multiple saved campaign battles need host recovery. Your decisions remain saved; no progress was overwritten.")); return; }
    const EDigimonPrivateCampaign Campaign = static_cast<EDigimonPrivateCampaign>(SavedCampaign);
    FString Error;
    if (!EnterCampaignServer(Campaign, true, Error))
    {
        ClientShowMessage(DigimonVenomNXTCampaign::Name(Campaign), Error);
        return;
    }
    if (HasPendingStoryBattle()) ServerResumeRelayBattle_Implementation();
}

void ADigimonVenomNXTPlayerController::ServerEnterRelay_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!EnterCampaignServer(EDigimonPrivateCampaign::Relay, false, Error)) ClientShowMessage(TEXT("Digimon Relay"), Error);
    else if (HasPendingStoryBattle()) ServerResumeRelayBattle_Implementation();
}
void ADigimonVenomNXTPlayerController::ServerEnterChronicles_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!EnterCampaignServer(EDigimonPrivateCampaign::ParadoxChronicles, false, Error)) ClientShowMessage(TEXT("Paradox Chronicles"), Error);
    else if (HasPendingStoryBattle()) ServerResumeRelayBattle_Implementation();
}
void ADigimonVenomNXTPlayerController::ServerEnterGhostLine_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!EnterCampaignServer(EDigimonPrivateCampaign::GhostLine, false, Error)) ClientShowMessage(TEXT("GhostLine"), Error);
    else if (HasPendingStoryBattle()) ServerResumeRelayBattle_Implementation();
}
void ADigimonVenomNXTPlayerController::ServerAdvanceGhostLineQuest_Implementation(FName NPCId)
{
    if (!IsInGhostLine() || !GetWorld()) return;
    if (GetWorld()->GetTimeSeconds() - LastRelayInteractionTime < .25) return;
    LastRelayInteractionTime = GetWorld()->GetTimeSeconds();
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    if (!GM || !ValidateRelayNPCInteraction(NPCId, Error) || !GM->InteractRelayNPCFor(this, NPCId, Error, true))
        ClientShowMessage(TEXT("GhostLine"), Error);
}
void ADigimonVenomNXTPlayerController::ServerAdvanceChroniclesQuest_Implementation(FName NPCId)
{
    if (!IsInChronicles() || !GetWorld()) return;
    if (GetWorld()->GetTimeSeconds() - LastRelayInteractionTime < .25) return;
    LastRelayInteractionTime = GetWorld()->GetTimeSeconds();
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    if (!GM || !ValidateRelayNPCInteraction(NPCId, Error) || !GM->InteractRelayNPCFor(this, NPCId, Error, true))
        ClientShowMessage(TEXT("Paradox Chronicles"), Error);
}
void ADigimonVenomNXTPlayerController::ServerLeaveRelay_Implementation()
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    FString Error;
    if (!LeaveRelayServer(Error)) ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), Error);
}
void ADigimonVenomNXTPlayerController::ServerTravelRelayMap_Implementation(int32 MapId)
{ TravelRelayMapServer(MapId, true); }
void ADigimonVenomNXTPlayerController::ServerRelayFastTravel_Implementation(int32 MapId)
{ TravelRelayMapServer(MapId, false); }
void ADigimonVenomNXTPlayerController::TravelRelayMapServer(int32 MapId, bool bRequirePortal)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!bAccountAuthenticated || !IsInRelay() || !GetPawn() || !PS || !GM || CurrentBattle || HasPendingStoryBattle() || HasPendingWorldBattle()) return;
    // The GhostLine finale exits forwards to HQ; numerical map order does not determine portal direction.
    const bool bForwardPortal = MapId == GetRelayPortalTarget(true);
    const bool bBackwardPortal = MapId == GetRelayPortalTarget(false);
    if (bRequirePortal && ((!bForwardPortal && !bBackwardPortal) || !CanUseRelayPortal(bForwardPortal)))
    { ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), TEXT("Walk to the marked entrance or exit and press E to travel.")); return; }
    if (!DigimonVenomNXTCampaign::CanEnterMap(GetStoryCampaign(), DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()), MapId))
    { ClientShowMessage(TEXT("Campaign gate"), DigimonVenomNXTCampaign::Objective(GetStoryCampaign(), DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()))); return; }
    CaptureRelayPosition();
    const FDigimonRelayProgress Before = DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign());
    const int32 BeforeMap = RelaySession.MapId;
    const FVector BeforeLocation = GetPawn()->GetActorLocation();
    RelaySession.MapId = MapId;
    FString PlacementError;
    if (!PrepareRelayPlacements(&PlacementError))
    { RelaySession.MapId = BeforeMap; ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), PlacementError); return; }
    DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()).MapId = MapId;
    const FVector Destination = GetRelayOrigin() + (!bRequirePortal ? RelayArrivalLocal : bForwardPortal ? RelayEntryLocal : RelayExitLocal);
    if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent())) Movement->StopMovementImmediately();
    GetPawn()->SetActorLocation(Destination, false, nullptr, ETeleportType::TeleportPhysics);
    CaptureRelayPosition();
    if (!GM->SavePlayer(PS))
    {
        DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()) = Before; RelaySession.MapId = BeforeMap;
        GetPawn()->SetActorLocation(BeforeLocation, false, nullptr, ETeleportType::TeleportPhysics);
        ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), TEXT("Could not save map travel. You remain on your previous map.")); return;
    }
    PS->MarkProfileChanged();
    PublishRelaySession();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Campaign"), TEXT("Private map travel saved"), FString::Printf(TEXT("%s | map %d -> %d | %s"), *DigimonVenomNXTCampaign::Name(GetStoryCampaign()), BeforeMap, MapId, bRequirePortal ? TEXT("portal") : TEXT("fast travel")));
}

void ADigimonVenomNXTPlayerController::ServerInteractRelayNPC_Implementation(FName NPCId)
{
    if (!GetWorld() || GetWorld()->GetTimeSeconds() - LastRelayInteractionTime < .25) return;
    LastRelayInteractionTime = GetWorld()->GetTimeSeconds();
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    if (!GM || !ValidateRelayNPCInteraction(NPCId, Error) || !GM->InteractRelayNPCFor(this, NPCId, Error)) ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), Error);
}
void ADigimonVenomNXTPlayerController::ServerChallengeRelayNPC_Implementation(FName NPCId)
{
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !ValidateRelayNPCInteraction(NPCId, Error) || !GM->StartRelayBattleFor(this, NPCId, Error)) ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), Error);
}
void ADigimonVenomNXTPlayerController::ServerStartRelayFieldTraining_Implementation()
{
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !GM->StartRelayFieldTrainingFor(this, Error)) ClientShowMessage(TEXT("Field Training"), Error);
}
void ADigimonVenomNXTPlayerController::ServerResumeRelayBattle_Implementation()
{
    FString Error;
    ADigimonVenomNXTGameMode* GM = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    if (!GM || !IsInRelay() || !GM->ResumeRelayBattleFor(this, Error)) ClientShowMessage(DigimonVenomNXTCampaign::Name(GetStoryCampaign()), Error);
}
void ADigimonVenomNXTPlayerController::SetRelayDialogueOpen(bool bOpen)
{
    if (!IsLocalController()) return;
    bRelayDialogueOpen = bOpen;
    ApplyFieldInputMode();
}
void ADigimonVenomNXTPlayerController::ClientShowRelayDialogue_Implementation(FName NPCId, const FString& Dialogue, EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& ConfirmedProgress)
{
    if (!IsInRelay() || Campaign != GetStoryCampaign() || ConfirmedProgress.MapId != GetRelayMapId()) return;
    CreateNativeHUD();
    if (GameHUDWidget)
    {
        SetFieldMenuOpen(false);
        GameHUDWidget->ShowRelayDialogue(NPCId, Dialogue, ConfirmedProgress);
        SetRelayDialogueOpen(true);
        if (UDigimonVenomNXTAudioSubsystem* Audio=GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
            Audio->PlayCue(EDigimonAudioCue::Interaction);
    }
}
void ADigimonVenomNXTPlayerController::ClientSetRelayPresentation_Implementation(EDigimonPrivateCampaign Campaign, bool bInside, int32 MapId, FVector Origin, uint64 Revision)
{
    if (!DigimonVenomNXTRelaySessionCore::AcceptRevision(AppliedLocalRelaySession.Revision, Revision)) return;
    if (!DigimonVenomNXTCampaign::IsValid(Campaign) || !DigimonVenomNXTCampaign::GetMap(Campaign, MapId) || Origin.ContainsNaN()) return;
    RelaySession.Campaign = Campaign;
    RelaySession.bActive = bInside;
    RelaySession.MapId = MapId;
    RelaySession.Origin = Origin;
    RelaySession.Revision = Revision;
    AppliedLocalRelaySession = RelaySession;
    if (GameHUDWidget) GameHUDWidget->CloseRelayDialogue();
    bRelayPresentationFailurePending = false;
    bRelayPresentationWaiting = bInside;
    RefreshRelayPresentation();
    RefreshLocalActorPrivacy();
    if (bInside) SetFieldMenuOpen(bRelayPresentationFailurePending);
    ApplyFieldInputMode();
}
void ADigimonVenomNXTPlayerController::OnRep_RelaySession()
{
    if (!DigimonVenomNXTCampaign::IsValid(RelaySession.Campaign) ||
        !DigimonVenomNXTCampaign::GetMap(RelaySession.Campaign, RelaySession.MapId) ||
        RelaySession.Origin.ContainsNaN() ||
        !DigimonVenomNXTRelaySessionCore::AcceptRevision(AppliedLocalRelaySession.Revision, RelaySession.Revision))
    { RelaySession = AppliedLocalRelaySession; return; }
    AppliedLocalRelaySession = RelaySession;
    RefreshRelayPresentation();
    RefreshLocalActorPrivacy();
}
void ADigimonVenomNXTPlayerController::RefreshRelayPresentation()
{
    if (!IsLocalController() || !GetWorld()) return;
    const bool bPresent = IsInRelay();
    if (!bPresent)
    {
        bRelayPresentationWaiting = false;
        bRelayPresentationFailurePending = false;
        if (IsValid(RelayScene)) { RelayScene->Destroy(); RelayScene = nullptr; }
        PresentedRelayMapId = INDEX_NONE;
        if (IsValid(LocalMapRenderer)) LocalMapRenderer->SetActorHiddenInGame(IsInDigiFarm());
        return;
    }
    // The campaign RPC and the owning PlayerState/profile/pawn arrive on
    // different replication paths. Waiting for them is not an artwork failure.
    // Tick retries this gate as those objects arrive, without latching an error.
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    bRelayPresentationWaiting = !PS || PS->Profile.AccountId.IsEmpty() || !GetPawn() || !GetLocalPlayer();
    if (bRelayPresentationWaiting) return;

    // Campaign content is validated only after the owning client's state is ready.
    if (IsValid(LocalMapRenderer)) LocalMapRenderer->SetActorHiddenInGame(true);
    if (bRelayPresentationFailurePending) return;
    FString CastKey;
    if (PS)
    {
        const FDigimonRelayProgress& Journey = DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign());
        CastKey = FString::Printf(TEXT("%d_%d_%d_%d_%d_%d_%d"), Journey.bEverChampion, Journey.bIsChampion,
            Journey.ChallengerIndex, Journey.DefeatedTamers.Num(), Journey.bComplete,
            Journey.CompletedObjectives.Num(), Journey.AcceptedQuests.Num());
        // The trusted companion disappears when exposed, and the defeated mastermind never respawns.
        // Derive this from actual visibility, not only a count that could miss a cast replacement.
        for (const FDigimonRelayNPC& NPC : DigimonVenomNXTCampaign::NPCsForMap(GetStoryCampaign(), GetRelayMapId()))
            if (DigimonVenomNXTCampaign::IsNPCVisible(GetStoryCampaign(), Journey, NPC)) CastKey += TEXT("|") + NPC.Id.ToString();
    }
    if (!IsValid(RelayScene) || PresentedCampaign != GetStoryCampaign() || PresentedRelayMapId != GetRelayMapId() || !PresentedRelayOrigin.Equals(GetRelayOrigin()) || PresentedRelayCast != CastKey)
    {
        if (IsValid(RelayScene)) RelayScene->Destroy();
        RelayScene = nullptr;
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FString PresentationError;
        const bool bPlacementsReady = PrepareRelayPlacements(&PresentationError);
        if (bPlacementsReady)
        {
            RelayScene = GetWorld()->SpawnActor<ADigimonVenomNXTRelayScene>(ADigimonVenomNXTRelayScene::StaticClass(), GetRelayOrigin(), FRotator::ZeroRotator, Params);
            if (!RelayScene)
                PresentationError = TEXT("The campaign scene could not be created on this client [CAMPAIGN_SCENE_SPAWN]. Your saved progress is safe.");
            else if (!RelayScene->InitializeFor(this, &PresentationError) && PresentationError.IsEmpty())
                PresentationError = TEXT("This client could not initialize the campaign scene [CAMPAIGN_SCENE_CONTENT]. Your saved progress is safe.");
        }
        if (!PresentationError.IsEmpty())
        {
            bRelayPresentationFailurePending = true;
            if (IsValid(RelayScene)) { RelayScene->Destroy(); RelayScene = nullptr; }
            SetFieldMenuOpen(true);
            UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT campaign client presentation: campaign=%d map=%d: %s"),
                static_cast<int32>(GetStoryCampaign()), GetRelayMapId(), *PresentationError);
            ClientShowMessage_Implementation(TEXT("Campaign unavailable"), PresentationError);
            return;
        }
        PresentedRelayCast = CastKey;
        PresentedRelayMapId = GetRelayMapId();
        PresentedCampaign = GetStoryCampaign();
        PresentedRelayOrigin = GetRelayOrigin();
        if (const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(GetStoryCampaign(), GetRelayMapId())) ClientPlayExplorationMusic_Implementation(Map->SourceMapId);
    }
}


bool ADigimonVenomNXTPlayerController::IsActiveRelayNPC(FName NPCId) const
{
    const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(GetStoryCampaign(), NPCId);
    const ADigimonVenomNXTPlayerState* PS = GetPlayerState<ADigimonVenomNXTPlayerState>();
    return NPC && PS && DigimonVenomNXTCampaign::IsNPCVisible(GetStoryCampaign(),
        DigimonVenomNXTCampaign::Progress(PS->Profile, GetStoryCampaign()), *NPC);
}
