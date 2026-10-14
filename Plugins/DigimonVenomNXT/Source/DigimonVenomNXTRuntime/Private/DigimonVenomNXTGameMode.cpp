#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTServerActivity.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTCampaignBattleCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTVariantCore.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTPartnerFollower.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTWorld.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

namespace
{
void ReplaceWildVariety(TArray<FDigimonWildEncounterEntry>& Encounters, const TArray<FName>& ParadoxSpecies,
    const TArray<FName>& ShinySpecies, const TArray<FName>& FirewallSpecies)
{
    if (Encounters.IsEmpty() || (ParadoxSpecies.IsEmpty() && ShinySpecies.IsEmpty() && FirewallSpecies.IsEmpty())) return;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const auto Rates = DigimonVenomNXTVariantCore::EffectiveWildRates(
        ShinySpecies.IsEmpty() ? 0. : Settings->ShinyChance,
        ParadoxSpecies.IsEmpty() ? 0. : Settings->ParadoxChance,
        FirewallSpecies.IsEmpty() ? 0. : Settings->FirewallChance);
    // Match the source's categorical order and its independent rare-species draw.
    // A habitat's rare pool may include species absent from its common pool.
    const double Roll = FMath::FRand();
    EDigimonVariant Variant = EDigimonVariant::Normal;
    const TArray<FName>* Pool = nullptr;
    if (Roll < Rates.ParadoxChance) { Variant = EDigimonVariant::Paradox; Pool = &ParadoxSpecies; }
    else if (Roll < Rates.ParadoxChance + Rates.ShinyChance) { Variant = EDigimonVariant::Shiny; Pool = &ShinySpecies; }
    else if (Roll < Rates.ParadoxChance + Rates.ShinyChance + Rates.FirewallChance) { Variant = EDigimonVariant::Firewall; Pool = &FirewallSpecies; }
    if (!Pool || Pool->IsEmpty()) return;
    FDigimonWildEncounterEntry& Replaced = Encounters[FMath::RandRange(0, Encounters.Num() - 1)];
    Replaced.SpeciesId = (*Pool)[FMath::RandRange(0, Pool->Num() - 1)];
    Replaced.Variant = Variant;
}

TArray<FDigimonWildEncounterEntry> BuildRandomWildGroup(const TArray<FName>& Candidates, int32 MinLevel, int32 MaxLevel,
    const ADigimonVenomNXTPlayerState* Player, bool bDawn = false,
    const TArray<FName>& ParadoxSpecies = TArray<FName>(), const TArray<FName>& ShinySpecies = TArray<FName>(), const TArray<FName>& FirewallSpecies = TArray<FName>())
{
    TArray<FDigimonWildEncounterEntry> Encounters;
    if (Candidates.IsEmpty()) return Encounters;
    int32 LivingActive = 0;
    if (Player)
        for (int32 I = 0; I < FMath::Min(3, Player->Profile.Party.Num()); ++I)
        {
            FDigimonOwnedPartner Partner;
            if (Player->GetPartner(Player->Profile.Party[I], Partner) && Partner.CurrentHP > 0) ++LivingActive;
        }
    const float Roll = FMath::FRand();
    const int32 GroupSize = LivingActive <= 1 ? (Roll < .70f ? 1 : Roll < .95f ? 2 : 3) : (Roll < .25f ? 1 : Roll < .65f ? 2 : 3);
    const int32 LowestLevel = FMath::Clamp(MinLevel, 1, 99);
    const int32 HighestLevel = FMath::Clamp(MaxLevel, LowestLevel, 99);
    Encounters.Reserve(GroupSize);
    for (int32 Index = 0; Index < GroupSize; ++Index)
    {
        FDigimonWildEncounterEntry Encounter;
        Encounter.SpeciesId = Candidates[FMath::RandRange(0, Candidates.Num() - 1)];
        Encounter.Level = bDawn ? FMath::Clamp((LowestLevel == 1 ? HighestLevel - 2 : LowestLevel + 2) + FMath::RandRange(-2, 2), 1, 99) : FMath::RandRange(LowestLevel, HighestLevel);
        Encounters.Add(Encounter);
    }
    ReplaceWildVariety(Encounters, ParadoxSpecies, ShinySpecies, FirewallSpecies);
    return Encounters;
}
}

ADigimonVenomNXTGameMode::ADigimonVenomNXTGameMode()
{
    PlayerControllerClass = ADigimonVenomNXTPlayerController::StaticClass();
    PlayerStateClass = ADigimonVenomNXTPlayerState::StaticClass();
    GameStateClass = ADigimonVenomNXTGameState::StaticClass();
    DefaultPawnClass = ADigimonVenomNXTTamerCharacter::StaticClass();
    BattleActorClass = ADigimonVenomNXTBattleActor::StaticClass();
    bUseSeamlessTravel = true;
}

UClass* ADigimonVenomNXTGameMode::GetBattleActorClass() const
{
    return BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass();
}

void ADigimonVenomNXTGameMode::BeginPlay()
{
    Super::BeginPlay();
    if (ADigimonVenomNXTGameState* NGS = GetGameState<ADigimonVenomNXTGameState>())
    {
        NGS->InitializeFromSettings();
        if (UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr)
        {
            Ranked->RefreshSeasonAndGameState(NGS);
        }
    }
    const float Interval = FMath::Max(10.0f, GetDefault<UDigimonVenomNXTSettings>()->AutoSaveIntervalSeconds);
    GetWorldTimerManager().SetTimer(AutosaveTimer, this, &ADigimonVenomNXTGameMode::SaveAllPlayers, Interval, true);
    GetWorldTimerManager().SetTimer(RankedRefreshTimer, this, &ADigimonVenomNXTGameMode::RefreshRankedSeason, 5.0f, true);
}

void ADigimonVenomNXTGameMode::RefreshRankedSeason()
{
    if (!HasAuthority()) return;
    if (UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr)
        Ranked->RefreshSeasonAndGameState(GetGameState<ADigimonVenomNXTGameState>());
}

void ADigimonVenomNXTGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    if (!ErrorMessage.IsEmpty()) return;

    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    if (GameState && GameState->PlayerArray.Num() >= S->MaxPlayers)
    {
        ErrorMessage = TEXT("Server Full");
        DigimonVenomNXTServerActivity::RecordFor(this, TEXT("Connection"), TEXT("Session"), TEXT("Connection rejected"), TEXT("Server player limit reached."), TEXT("Warning"));
    }
}

void ADigimonVenomNXTGameMode::PostLogin(APlayerController* NewPlayer)
{
    // Connection is intentionally allowed before account authentication.
    // HandleStartingNewPlayer is gated below, so unauthenticated clients have no gameplay pawn.
    Super::PostLogin(NewPlayer);
    DigimonVenomNXTServerActivity::Record(NewPlayer, TEXT("Session"), TEXT("Transport connected"),
        FString::Printf(TEXT("Connection %s: waiting for credentials. This is a connection-stage event, not an authentication rejection."), *GetNameSafe(NewPlayer)));
}

bool ADigimonVenomNXTGameMode::AuthenticatePlayer(ADigimonVenomNXTPlayerController* Controller, bool bCreateAccount, const FString& Username, const FString& Password,
    FString& OutUsername, FString& OutAccountId, FString& OutError)
{
    if (!Controller) { OutError = TEXT("Player controller is unavailable."); return false; }
    if (Controller->IsAccountAuthenticated()) { OutError = TEXT("This connection is already authenticated."); return false; }

    UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>() : nullptr;
    UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = DigimonVenomNXTServerActivity::Console(this);
    // A same-process host restart may restore only the already authenticated,
    // armed local host. Empty remote credentials never acquire this capability.
    const bool bRestoredLocalHost = !bCreateAccount && Username.IsEmpty() && Password.IsEmpty() && ServerConsole &&
        ServerConsole->TryRestoreLocalHostIdentity(Controller, OutUsername, OutAccountId);
    if (!bRestoredLocalHost && (!Auth || !Auth->AuthenticateServerCredentials(bCreateAccount, Username, Password, OutUsername, OutAccountId, OutError)))
    {
        // No submitted username, password, credential error or account identifier is logged.
        DigimonVenomNXTServerActivity::Record(Controller, TEXT("Session"), TEXT("Authentication rejected"), TEXT("Credentials were not accepted or the account service is unavailable."), TEXT("Warning"));
        return false;
    }
    DigimonVenomNXTServerActivity::RecordFor(Controller, OutUsername, TEXT("Session"), TEXT("Credentials accepted"),
        FString::Printf(TEXT("Connection %s: account identity verified; checking session ownership and loading saved progress."), *GetNameSafe(Controller)));
    if (ServerConsole && ServerConsole->IsAccountBanned(OutAccountId, OutError))
    {
        DigimonVenomNXTServerActivity::RecordFor(this, OutUsername, TEXT("Moderation"), TEXT("Login blocked"), TEXT("Authenticated account is banned."), TEXT("Warning"));
        return false;
    }

    if (GameState)
    {
        for (APlayerState* Existing : GameState->PlayerArray)
        {
            if (Existing == Controller->GetPlayerState<APlayerState>()) continue;
            const ADigimonVenomNXTPlayerState* ExistingNPS = Cast<ADigimonVenomNXTPlayerState>(Existing);
            const ADigimonVenomNXTPlayerController* ExistingController = ExistingNPS ? Cast<ADigimonVenomNXTPlayerController>(ExistingNPS->GetOwner()) : nullptr;
            if (ExistingNPS && ExistingNPS->Profile.AccountId == OutAccountId && ExistingController &&
                ExistingController->GetPlayerState<ADigimonVenomNXTPlayerState>() == ExistingNPS &&
                ExistingController->IsAccountAuthenticated() && !ExistingController->HasCommittedLogout())
            {
                OutError = TEXT("This Digimon Venom NXT account is already connected.");
                DigimonVenomNXTServerActivity::RecordFor(this, OutUsername, TEXT("Session"), TEXT("Login rejected"), TEXT("Account already has an active connection."), TEXT("Warning"));
                return false;
            }
        }
    }

    ADigimonVenomNXTPlayerState* NPS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!NPS || !Profiles)
    {
        OutError = TEXT("Digimon Venom NXT profile storage is unavailable.");
        DigimonVenomNXTServerActivity::RecordFor(this, OutUsername, TEXT("Persistence"), TEXT("Login profile unavailable"), TEXT("Player state or profile storage is unavailable."), TEXT("Error"));
        return false;
    }

    FDigimonPlayerProfile Profile;
    if (!Profiles->LoadProfile(OutAccountId, OutUsername, Profile))
    {
        OutError = TEXT("Your credentials were accepted, but the server could not load your saved profile. No replacement account was created. Check the host's Persistence events.");
        DigimonVenomNXTServerActivity::RecordFor(Controller, OutUsername, TEXT("Session"), TEXT("Login profile load failed"),
            TEXT("Authentication succeeded; persistent profile loading failed. See the corresponding Persistence event."), TEXT("Error"));
        return false;
    }
    Profile.AccountId = OutAccountId;
    Profile.Username = OutUsername;
    // The private career is part of this account save, not the public world-rival population.
    const UDigimonVenomNXTDataSubsystem* SeasonData = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (DigimonVenomNXTSeason::EnsureCareer(Profile, SeasonData) && !Profiles->SaveProfile(Profile))
    {
        OutError = TEXT("Could not save your Season career. Please try signing in again.");
        DigimonVenomNXTServerActivity::RecordFor(Controller, OutUsername, TEXT("Session"), TEXT("Login career initialization failed"),
            TEXT("Authentication and profile loading succeeded; the Season initialization write failed."), TEXT("Error"));
        return false;
    }
    NPS->InitializeServerProfile(Profile);
    Controller->SetAccountAuthenticatedServer(true);

    if (UDigimonVenomNXTRankedSubsystem* Ranked = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>() : nullptr)
    {
        Ranked->ClaimPendingReward(NPS);
        Ranked->RefreshSeasonAndGameState(GetGameState<ADigimonVenomNXTGameState>());
    }
    DigimonVenomNXTServerActivity::Record(Controller, TEXT("Session"), bRestoredLocalHost ? TEXT("Host identity restored") : bCreateAccount ? TEXT("Account created and authenticated") : TEXT("Account authenticated"),
        FString::Printf(TEXT("Connection %s: server profile loaded. Party %d | Collection %d | Season week %d | Ranked grade %s | Rating %d. Waiting for verified client synchronization."),
            *GetNameSafe(Controller), NPS->Profile.Party.Num(), NPS->Profile.Collection.Num(), NPS->Profile.Season.Week,
            *StaticEnum<EDigimonRankedGrade>()->GetNameStringByValue(static_cast<int64>(NPS->Profile.Ranked.Grade)), NPS->Profile.Ranked.Rating));
    Controller->QueueOwnerProfileSynchronization();
    return true;
}

void ADigimonVenomNXTGameMode::FinishAuthenticatedPlayerLogin(ADigimonVenomNXTPlayerController* Controller)
{
    if (!HasAuthority() || !Controller || !Controller->IsAccountAuthenticated() || !Controller->IsOwnerProfileReady()) return;
    ADigimonVenomNXTPlayerState* NPS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!NPS || !NPS->HasInitializedServerProfile()) return;
    HandleStartingNewPlayer(Controller);
    if (UDigimonVenomNXTServerConsoleSubsystem* ServerConsole = DigimonVenomNXTServerActivity::Console(this))
        ServerConsole->ApplyModerationToPlayer(Controller);
    if (!NPS->Profile.Season.BattleCheckpointJson.IsEmpty())
    {
        FString ResumeError;
        if (!StartSeasonBattleFor(Controller, ResumeError)) Controller->ClientShowMessage(TEXT("Season resume"), ResumeError);
    }
    if (!NPS->Profile.WorldBattleCheckpointJson.IsEmpty())
    {
        FString ResumeError;
        if (!StartWildBattleFor(Controller, ResumeError)) Controller->ClientShowMessage(TEXT("Wild battle resume"), ResumeError);
    }
    JoinWorldChat(Controller);
}

void ADigimonVenomNXTGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    ADigimonVenomNXTPlayerController* DigimonController = Cast<ADigimonVenomNXTPlayerController>(NewPlayer);
    if (!DigimonController || !DigimonController->IsAccountAuthenticated() || !DigimonController->IsOwnerProfileReady()) return;
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
    if (!NewPlayer || !NewPlayer->GetPawn()) return;

    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(NewPlayer->GetPawn()))
    {
        Tamer->RefreshTamerStyleFromProfile();
        Tamer->RefreshFollowerFromProfile();
    }

    if (const ADigimonVenomNXTPlayerState* NPS = NewPlayer->GetPlayerState<ADigimonVenomNXTPlayerState>())
    {
        if (UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>() : nullptr)
        {
            FString TravelError;
            const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
            const int32 RealMapCount = Data ? FMath::Max(1, Data->GetPublicMapCount()) : 1;
            int32 SavedMapId = FMath::Clamp(NPS->Profile.CurrentMapId, 1, RealMapCount);
            FDigimonMapRow SavedRow;
            if (!Data || !Data->GetMap(SavedMapId, SavedRow)) SavedMapId = 1;
            if (!WorldSystem->TravelPlayerToMap(NewPlayer, SavedMapId, TravelError))
            {
                UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not restore map %d for %s: %s"), SavedMapId, *NPS->GetPlayerName(), *TravelError);
                DigimonVenomNXTServerActivity::Record(NewPlayer, TEXT("Travel"), TEXT("Saved map restore failed"), TravelError, TEXT("Warning"));
                DigimonController->ClientShowMessage(TEXT("Habitat unavailable"), TravelError);
            }
            else if (ADigimonVenomNXTPlayerController* DigimonPC = Cast<ADigimonVenomNXTPlayerController>(NewPlayer))
            {
                if (!NPS->Profile.Farm.bInside && !DigimonVenomNXTCampaign::IsActive(NPS->Profile))
                    DigimonVenomNXTServerActivity::Record(NewPlayer, TEXT("Travel"), TEXT("Public map restored"), FString::Printf(TEXT("Map %d"), SavedMapId));
                DigimonPC->ClientSetActiveMapPresentation(SavedMapId);
                DigimonPC->ClientPlayExplorationMusic(SavedMapId);
            }
        }
    }
    DigimonController->RestoreDigiFarmAfterLogin();
    DigimonController->RestoreRelayAfterLogin();
}

void ADigimonVenomNXTGameMode::Logout(AController* Exiting)
{
    LeaveWorldChat(Cast<ADigimonVenomNXTPlayerController>(Exiting));
    if (Exiting)
    {
        // The accepted decision, exact HP/SP and queued commands are already saved.
        // Remove only the disconnected actor; never settle a suspended match as a win.
        if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Exiting))
        {
            ADigimonVenomNXTBattleActor* Battle = Controller->CurrentBattle;
            if (Battle && Battle->State.Kind == EDigimonBattleKind::Friendly)
            {
                Battle->ForfeitUnranked(Controller, TEXT("Unranked match ended: your opponent disconnected."));
                Controller->SetCurrentBattleServer(nullptr);
                Battle->TryDestroyWhenUnused();
                Battle = nullptr;
            }

            EDigimonPrivateCampaign SavedCampaign;
            FName SavedNPC;
            if (Battle && DigimonVenomNXTCampaign::TryParseContext(Battle->BattleContextId, SavedCampaign, SavedNPC))
            {
                Battle->SuspendRelayMatch();
                Controller->SetCurrentBattleServer(nullptr);
                Battle->TryDestroyWhenUnused();
            }
            else if (Battle && Battle->State.Kind == EDigimonBattleKind::Season)
            {
                Battle->SuspendSeasonMatch();
                Controller->SetCurrentBattleServer(nullptr);
                Battle->TryDestroyWhenUnused();
            }
            else if (Battle && Battle->State.Kind == EDigimonBattleKind::Wild)
            {
                Battle->SuspendWorldWildMatch();
                Controller->SetCurrentBattleServer(nullptr);
                Battle->TryDestroyWhenUnused();
            }
        }
        if (ADigimonVenomNXTPlayerState* NPS = Exiting->GetPlayerState<ADigimonVenomNXTPlayerState>())
        {
            const ADigimonVenomNXTPlayerController* SessionController = Cast<ADigimonVenomNXTPlayerController>(Exiting);
            const bool bAlreadySaved = SessionController && SessionController->HasCommittedLogout();
            const bool bShouldSave = NPS->HasInitializedServerProfile() && !bAlreadySaved;
            const bool bSaved = bShouldSave && SavePlayer(NPS, false);
            DigimonVenomNXTServerActivity::Record(Exiting, TEXT("Session"), TEXT("Disconnected"),
                !NPS->HasInitializedServerProfile() ? TEXT("Connection closed before a profile was initialized; no save attempted.") :
                bAlreadySaved ? TEXT("Explicit logout handoff was already acknowledged; no duplicate capture or write.") :
                bSaved ? TEXT("Authoritative profile retained in server memory. No disconnect disk save; pending admin /saveall or admin logout.") : TEXT("Profile handoff failed on disconnect; check Persistence events."),
                bShouldSave && !bSaved ? TEXT("Error") : TEXT("Info"));
        }
    }
    Super::Logout(Exiting);
}

bool ADigimonVenomNXTGameMode::SavePlayer(ADigimonVenomNXTPlayerState* PlayerState, bool bAllowAutomaticWrite)
{
    if (!HasAuthority() || !PlayerState || !PlayerState->HasInitializedServerProfile()) return false;
    ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(PlayerState->GetOwner());
    if (!Controller || Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() != PlayerState ||
        !Controller->IsAccountAuthenticated() || Controller->HasCommittedLogout())
    {
        DigimonVenomNXTServerActivity::Record(PlayerState, TEXT("Persistence"), TEXT("Save rejected"),
            TEXT("Only the initialized profile owned by this live authenticated controller may be saved."), TEXT("Warning"));
        return false;
    }
    Controller->CaptureDigiFarmPosition();
    Controller->CaptureRelayPosition();
    if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr)
    {
        return bAllowAutomaticWrite ? Profiles->SaveProfile(PlayerState->Profile) : Profiles->RetainProfile(PlayerState->Profile);
    }
    DigimonVenomNXTServerActivity::Record(PlayerState, TEXT("Persistence"), TEXT("Save failed"), TEXT("Profile storage subsystem is unavailable."), TEXT("Error"));
    return false;
}

void ADigimonVenomNXTGameMode::SaveAllPlayers()
{
    if (!HasAuthority() || !GetWorld() || !GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves) return;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (Controller && Controller->IsAccountAuthenticated() && !Controller->HasCommittedLogout())
            SavePlayer(Controller->GetPlayerState<ADigimonVenomNXTPlayerState>(), false);
    }
    if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>())
    {
        FString Error;
        if (!Profiles->FlushAutomaticSaves(Error))
            DigimonVenomNXTServerActivity::Record(this, TEXT("Persistence"), TEXT("Autosave failed"), Error, TEXT("Error"));
    }
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartWildBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (!HasAuthority() || !Controller || !Controller->IsAccountAuthenticated()) { OutError = TEXT("Sign in before starting a wild battle."); return nullptr; }
    if (Controller && Controller->IsInRelay()) return StartRelayFieldTrainingFor(Controller, OutError);
    if (Controller && Controller->IsInDigiFarm()) { OutError = TEXT("Leave your private DigiFarm before starting a battle."); return nullptr; }
    if (!Controller || !Controller->GetPawn()) { OutError = TEXT("Player is not ready."); return nullptr; }
    if (Controller->CurrentBattle && !Controller->CurrentBattle->State.bFinished) { OutError = TEXT("You are already in a battle."); return nullptr; }
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (PS && !PS->Profile.Season.BattleCheckpointJson.IsEmpty()) { OutError = TEXT("Resume and finish your saved Season match first."); return nullptr; }
    if (!PS || PS->Profile.Party.Num() == 0) { OutError = TEXT("Choose a starter and build a party before battling."); return nullptr; }

    if (!PS->Profile.WorldBattleCheckpointJson.IsEmpty())
    {
        ADigimonVenomNXTBattleActor* Resumed = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(GetBattleActorClass());
        if (!Resumed || !Resumed->RestoreWorldWildMatch(PS, OutError))
        { if (Resumed) Resumed->Destroy(); if (OutError.IsEmpty()) OutError = TEXT("Your saved wild battle could not be restored."); return nullptr; }
        Controller->SetCurrentBattleServer(Resumed);
        return Resumed;
    }

    bool bLivingActive = false;
    for (int32 Index = 0; Index < FMath::Min(3, PS->Profile.Party.Num()); ++Index)
    {
        FDigimonOwnedPartner Partner;
        if (PS->GetPartner(PS->Profile.Party[Index], Partner) && Partner.CurrentHP > 0) bLivingActive = true;
    }
    if (!bLivingActive)
    { OutError = TEXT("Your first three party slots have no healthy Digimon. Heal at DigiLab or move a healthy partner into those slots before searching."); return nullptr; }

    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    const FDigimonMapRow* Row = Data ? Data->FindMap(PS->Profile.CurrentMapId) : nullptr;
    if (!Row || Row->WildSpecies.IsEmpty()) { OutError = TEXT("This map has no wild encounters."); return nullptr; }
    const TArray<FDigimonWildEncounterEntry> Encounters = BuildRandomWildGroup(Row->WildSpecies,
        Row->RecommendedMinLevel, Row->RecommendedMaxLevel, PS, Row->Region == EDigimonRegion::RegionOne,
        Row->ParadoxSpecies, Row->ShinySpecies, Row->FirewallSpecies);
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeWildGroupBattle(PS, Encounters))
    {
        if (Battle) Battle->Destroy();
        OutError = TEXT("Could not initialize the wild battle.");
        return nullptr;
    }
    Controller->SetCurrentBattleServer(Battle);
    return Battle;
}




ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartAIRivalBattleFor(ADigimonVenomNXTPlayerController* Controller, const FString& RivalId, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (Controller && (Controller->IsInDigiFarm() || Controller->IsInRelay())) { OutError = TEXT("Return to a public habitat before challenging a rival."); return nullptr; }
    if (!Controller || !Controller->IsAccountAuthenticated() || !Controller->GetPawn()) { OutError = TEXT("Player is not ready."); return nullptr; }
    if (Controller->CurrentBattle) { OutError = TEXT("You are already in a battle."); return nullptr; }
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (PS && !PS->Profile.Season.BattleCheckpointJson.IsEmpty()) { OutError = TEXT("Resume and finish your saved Season match first."); return nullptr; }
    if (PS && !PS->Profile.WorldBattleCheckpointJson.IsEmpty()) { OutError = TEXT("Resume and finish your saved wild encounter first."); return nullptr; }
    if (!PS || PS->Profile.Party.Num() == 0) { OutError = TEXT("Build a party before challenging a rival."); return nullptr; }
    UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>() : nullptr;
    FDigimonAIRivalRecord Rival;
    FDigimonBattleTeam Team;
    if (!Rivals || !Rivals->GetRival(RivalId, Rival) || !Rivals->BuildBattleTeam(RivalId, Team)) { OutError = TEXT("That AI rival is unavailable."); return nullptr; }
    if (Rival.MapId != PS->Profile.CurrentMapId) { OutError = TEXT("That rival has travelled to another map."); return nullptr; }
    if (Rivals->IsRivalInLiveBattle(RivalId)) { OutError = TEXT("That rival is already battling another tamer."); return nullptr; }
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeAITrainerBattle(PS, Team, EDigimonBattleKind::Friendly, RivalId))
    {
        if (Battle) Battle->Destroy();
        OutError = TEXT("Could not initialize the AI tamer battle.");
        return nullptr;
    }
    Controller->SetCurrentBattleServer(Battle);
    return Battle;
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartSeasonBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (Controller && Controller->IsInDigiFarm()) { OutError = TEXT("Leave your private DigiFarm before starting a battle."); return nullptr; }
    if (!HasAuthority() || !Controller || !Controller->IsAccountAuthenticated() || !Controller->GetPawn())
    { OutError = TEXT("Player is not ready."); return nullptr; }
    if (Controller->CurrentBattle) { OutError = TEXT("Return from the current battle before starting your Season match."); return nullptr; }
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || PS->Profile.AccountId.IsEmpty() || PS->Profile.Party.IsEmpty())
    { OutError = TEXT("Build a party before playing a Season match."); return nullptr; }

    if (!PS->Profile.WorldBattleCheckpointJson.IsEmpty())
    { OutError = TEXT("Resume and finish your saved wild encounter before starting a Season match."); return nullptr; }

    if (DigimonVenomNXTCampaign::HasPendingBattle(PS->Profile))
    { OutError = TEXT("Resume and finish your saved private campaign battle before starting a Season match."); return nullptr; }

    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data) { OutError = TEXT("Season roster data is unavailable."); return nullptr; }
    if (!PS->Profile.Season.BattleCheckpointJson.IsEmpty())
    {
        ADigimonVenomNXTBattleActor* Resumed = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
        if (!Resumed || !Resumed->RestoreSeasonMatch(PS, OutError))
        {
            if (Resumed) Resumed->Destroy();
            if (OutError.IsEmpty()) OutError = TEXT("Could not restore your saved Season decision. Your progress has been preserved.");
            return nullptr;
        }
        Controller->SetCurrentBattleServer(Resumed);
        return Resumed;
    }
    const FDigimonPlayerProfile Before = PS->Profile;
    DigimonVenomNXTSeason::EnsureCareer(PS->Profile, Data);
    const TArray<FDigimonOwnedPartner> Opponents = DigimonVenomNXTSeason::BuildScheduledOpponent(PS->Profile, Data);
    if (Opponents.IsEmpty())
    {
        PS->Profile = Before;
        OutError = TEXT("The scheduled Season party is unavailable. Please reopen Season Mode.");
        return nullptr;
    }
    FDigimonBattleTeam Team;
    Team.TrainerName = DigimonVenomNXTSeason::GetScheduledOpponentName(PS->Profile);
    const int32 ActiveLimit = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, 1, 6);
    TSet<FGuid> ValidParty;
    for (const FGuid& Id : PS->Profile.Party)
        if (PS->Profile.Collection.ContainsByPredicate([&Id](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; })) ValidParty.Add(Id);
    const int32 OpponentCount = FMath::Min3(Opponents.Num(), ActiveLimit, ValidParty.Num());
    if (OpponentCount <= 0) { PS->Profile = Before; OutError = TEXT("Your party has no valid partners for this match."); return nullptr; }
    for (int32 Index = 0; Index < OpponentCount; ++Index)
        Team.Active.Add(DigimonVenomNXTAutoBattle::BuildUnit(Opponents[Index], Data));
    FString ContextId;
    if (!DigimonVenomNXTSeason::BeginMatch(PS->Profile, ContextId, OutError))
    {
        PS->Profile = Before;
        return nullptr;
    }
    // Save the scheduled context BEFORE preparing the opening decision checkpoint.
    // Every subsequent command saves that exact decision before it is published.
    if (!SavePlayer(PS))
    {
        PS->Profile = Before;
        OutError = TEXT("Could not save the scheduled match. No Season match was started; please try again.");
        return nullptr;
    }
    PS->MarkProfileChanged();
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeAITrainerBattle(PS, Team, EDigimonBattleKind::Season, ContextId))
    {
        if (Battle) Battle->Destroy();
        OutError = TEXT("Could not initialize the Season match. Your same scheduled opponent is saved for retry.");
        return nullptr;
    }
    Controller->SetCurrentBattleServer(Battle);
    return Battle;
}


ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartStoryBossBattleFor(ADigimonVenomNXTPlayerController* Controller, int32 Chapter, FString& OutError)
{
    (void)Controller; (void)Chapter;
    OutError = TEXT("Paradox Chronicles is an explorable private campaign. Enter it from Story Mode, complete the local quest, then approach that map's Paradox boss.");
    return nullptr;
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartFinalStoryBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    (void)Controller;
    OutError = TEXT("Enter Paradox Chronicles and approach the final rift after earning all 17 crests. The old battle list cannot launch this encounter.");
    return nullptr;
}

namespace
{
bool RelayPlayerReady(ADigimonVenomNXTPlayerController* Controller, FString& Error, bool bAllowCheckpoint = false)
{
    if (!Controller || !Controller->HasAuthority() || !Controller->IsAccountAuthenticated() || !Controller->GetPawn())
    { Error = TEXT("Sign in and enter the world before entering a private campaign."); return false; }
    const ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || PS->Profile.AccountId.IsEmpty() || PS->Profile.Party.IsEmpty())
    { Error = TEXT("Choose your starter and bring a party to your campaign."); return false; }
    const EDigimonPrivateCampaign Campaign = Controller->GetStoryCampaign();
    if (!DigimonVenomNXTCampaign::IsValid(Campaign))
    { Error = TEXT("This private campaign is unavailable."); return false; }
    const FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign);
    if (!Controller->IsInRelay() || Controller->IsInDigiFarm() || !Progress.bInside || PS->Profile.ActiveStoryCampaign != Campaign)
    { Error = TEXT("Enter your private story campaign first."); return false; }
    if (DigimonVenomNXTCampaign::HasOtherPendingBattle(PS->Profile, Campaign))
    { Error = TEXT("Resume the saved battle in your other campaign before continuing here."); return false; }
    if (Controller->CurrentBattle || !PS->Profile.WorldBattleCheckpointJson.IsEmpty() || !PS->Profile.Season.BattleCheckpointJson.IsEmpty() ||
        (!bAllowCheckpoint && !Progress.BattleCheckpointJson.IsEmpty()))
    { Error = TEXT("Return from the current battle or resume your saved decision first."); return false; }
    if (!DigimonVenomNXTCampaign::CanEnterMap(Campaign, Progress, Progress.MapId))
    { Error = TEXT("This campaign region is not unlocked for your tamer."); return false; }
    return true;
}
}

bool ADigimonVenomNXTGameMode::InteractRelayNPCFor(ADigimonVenomNXTPlayerController* Controller, FName NPCId, FString& OutError, bool bAdvanceQuest)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return false;
    if (!HasAuthority() || !RelayPlayerReady(Controller, OutError) || !Controller->ValidateRelayNPCInteraction(NPCId, OutError)) return false;
    const EDigimonPrivateCampaign Campaign = Controller->GetStoryCampaign();
    const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(Campaign, NPCId);
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!NPC || !PS || NPC->MapId != DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign).MapId ||
        !DigimonVenomNXTCampaign::IsNPCVisible(Campaign, DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign), *NPC))
    { OutError = TEXT("That person is not available in your current private map."); return false; }
    FDigimonPlayerProfile Candidate = PS->Profile;
    FString Dialogue;
    FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Candidate, Campaign);
    const bool bWasComplete = !NPC->QuestId.IsNone() && Progress.CompletedObjectives.Contains(NPC->QuestId);
    if (bAdvanceQuest)
    {
        if (!DigimonVenomNXTCampaign::AdvanceQuest(Campaign, Progress, *NPC, Dialogue, OutError)) return false;
        // Case rewards are committed with the explicit turn-in, never on opening
        // dialogue, accepting, retrying a click, or failing to save the profile.
        if (!bWasComplete &&
            !NPC->QuestId.IsNone() && Progress.CompletedObjectives.Contains(NPC->QuestId))
        {
            const int64 Credits = FMath::Max<int64>(0, NPC->Credits);
            Candidate.Credits = DigimonVenomNXTProgressionCore::AddSaturated(Candidate.Credits, Credits);
            auto AddCaseSupply = [&Candidate](FName Id, int32 Quantity)
            {
                FDigimonInventoryEntry* Entry = Candidate.Inventory.FindByPredicate([Id](const FDigimonInventoryEntry& E) { return E.ItemId == Id; });
                if (!Entry) { FDigimonInventoryEntry New; New.ItemId = Id; Candidate.Inventory.Add(New); Entry = &Candidate.Inventory.Last(); }
                Entry->Quantity = static_cast<int32>(FMath::Min<int64>(MAX_int32,
                    FMath::Max(0, Entry->Quantity) + static_cast<int64>(Quantity)));
            };
            for (const TPair<FName, int32>& Supply : NPC->RewardItems)
                if (Supply.Value > 0) AddCaseSupply(Supply.Key, Supply.Value);
            Dialogue += FString::Printf(TEXT("\n\nAssignment complete: +%lld credits. Supplies are in your bag."), Credits);
        }
    }
    else if (!DigimonVenomNXTCampaign::Interact(Campaign, Progress, *NPC, Dialogue, OutError)) return false;
    if (NPC->Role == EDigimonRelayRole::Healer)
    {
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
        if (!Data) { OutError = TEXT("Your team data is not ready. Please try again."); return false; }
        for (FDigimonOwnedPartner& Partner : Candidate.Collection)
        {
            const FDigimonStats Stats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats;
            Partner.CurrentHP = Stats.MaxHP; Partner.CurrentSP = Stats.MaxSP;
        }
        Dialogue += TEXT("\n\nYour collection has been fully restored to full HP and SP, free of charge.");
    }
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Profiles || !Profiles->SaveProfile(Candidate)) { OutError = TEXT("Your campaign progress could not be saved. Please speak with this person again."); return false; }
    const int64 CreditChange = Candidate.Credits - PS->Profile.Credits;
    PS->Profile = MoveTemp(Candidate);
    DigimonVenomNXTServerActivity::Record(Controller, TEXT("Campaign"), bAdvanceQuest ? TEXT("Quest progress saved") : TEXT("NPC interaction saved"),
        FString::Printf(TEXT("%s | map %d | NPC %s | credits %+lld%s"), *DigimonVenomNXTCampaign::Name(Campaign),
            DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign).MapId, *NPCId.ToString(), static_cast<long long>(CreditChange),
            NPC->Role == EDigimonRelayRole::Healer ? TEXT(" | collection healed") : TEXT("")));
    PS->MarkProfileChanged();
    Controller->ClientShowRelayDialogue(NPCId, Dialogue, Campaign, DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign));
    return true;
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartRelayBattleFor(ADigimonVenomNXTPlayerController* Controller, FName NPCId, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (!HasAuthority() || !RelayPlayerReady(Controller, OutError) || !Controller->ValidateRelayNPCInteraction(NPCId, OutError)) return nullptr;
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const EDigimonPrivateCampaign Campaign = Controller->GetStoryCampaign();
    const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(Campaign, NPCId);
    if (!NPC || NPC->MapId != DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign).MapId ||
        !DigimonVenomNXTCampaign::IsNPCVisible(Campaign, DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign), *NPC) ||
        !DigimonVenomNXTCampaign::CanChallenge(Campaign, DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign), *NPC, OutError)) return nullptr;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    if (!Data || NPC->TeamSpecies.IsEmpty() || NPC->TeamSpecies.Num() != NPC->TeamLevels.Num())
    { OutError = TEXT("This tamer's team data is unavailable. Your progress has not changed."); return nullptr; }
    bool bLivingStoryActive = false;
    for (int32 Index = 0; Index < FMath::Min(3, PS->Profile.Party.Num()); ++Index)
    {
        FDigimonOwnedPartner Partner;
        if (PS->GetPartner(PS->Profile.Party[Index], Partner) && Partner.CurrentHP > 0) bLivingStoryActive = true;
    }
    if (!bLivingStoryActive)
    { OutError = TEXT("Recover a Digimon in your first three party slots before challenging this tamer. DigiLab can heal your party."); return nullptr; }
    FDigimonBattleTeam Team;
    Team.TrainerName = NPC->Name;
    if (NPC->Role == EDigimonRelayRole::FinalBoss)
    {
        TSet<FName> FinalSpecies;
        for (const FName SpeciesId : NPC->TeamSpecies) FinalSpecies.Add(SpeciesId);
        if (NPC->TeamSpecies.Num() != 3 || FinalSpecies.Num() != 3)
        { OutError = TEXT("The campaign finale requires all three distinct authored Mega Digimon."); return nullptr; }
        if (Campaign == EDigimonPrivateCampaign::GhostLine &&
            (NPC->Id != FName(TEXT("ghost_final_regent")) || NPC->MapId != 31 ||
             !FinalSpecies.Contains(TEXT("diaboromon")) || !FinalSpecies.Contains(TEXT("chaosdramon")) ||
             !FinalSpecies.Contains(TEXT("machinedramon"))))
        { OutError = TEXT("The Ghostline finale is missing its authored Digimon team."); return nullptr; }
    }
    const int32 ActiveSize = DigimonVenomNXTCampaignBattleCore::ActiveSlots(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, false, NPC->Role == EDigimonRelayRole::FinalBoss);
    for (int32 Index = 0; Index < NPC->TeamSpecies.Num(); ++Index)
    {
        FDigimonSpeciesDefinition Species;
        if (!Data->GetSpecies(NPC->TeamSpecies[Index], Species) || Species.bPlaceholder)
        { OutError = TEXT("A campaign Digimon is missing from the installed species registry."); return nullptr; }
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid::NewGuid(); Partner.SpeciesId = Species.SpeciesId;
        Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        Partner.Level = NPC->TeamLevels[Index]; Partner.ABI = FMath::Min(100, Partner.Level / 2); Partner.CAM = FMath::Min(100, Partner.Level);
        Partner.CurrentHP = MAX_int32; Partner.CurrentSP = MAX_int32;
        Partner.Variant = NPC->TeamVariants.IsValidIndex(Index) ? NPC->TeamVariants[Index] : EDigimonVariant::Normal;
        const bool bGhostLine = Campaign == EDigimonPrivateCampaign::GhostLine;
        if (!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Partner.Variant), Species.bHasNormalArtwork,
                Species.bHasParadoxArtwork, Species.bHasShinyArtwork, Species.bHasFirewallArtwork) ||
            (NPC->Role == EDigimonRelayRole::FinalBoss &&
             (Partner.Level != (bGhostLine ? 99 : 100) ||
              Partner.Variant != (bGhostLine ? EDigimonVariant::Normal : EDigimonVariant::Paradox) || Species.Stage != EDigimonStage::Mega)))
        { OutError = TEXT("This campaign encounter needs its authored variety artwork and Mega team. Verify the installed campaign content."); return nullptr; }
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        if (Team.Active.Num() < ActiveSize) Team.Active.Add(Unit); else Team.Bench.Add(Unit);
    }
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeAITrainerBattle(PS, Team, EDigimonBattleKind::Story, DigimonVenomNXTCampaign::ContextPrefix(Campaign) + NPCId.ToString()))
    {
        if (Battle) Battle->Destroy();
        OutError = TEXT("The campaign battle could not be saved and started. No crest, badge or reward has changed; please retry.");
        return nullptr;
    }
    Controller->SetCurrentBattleServer(Battle);
    PS->MarkProfileChanged();
    return Battle;
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::ResumeRelayBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (!HasAuthority() || !RelayPlayerReady(Controller, OutError, true)) return nullptr;
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (DigimonVenomNXTCampaign::Progress(PS->Profile, Controller->GetStoryCampaign()).BattleCheckpointJson.IsEmpty()) { OutError = TEXT("There is no saved campaign battle to resume."); return nullptr; }
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->RestoreRelayMatch(PS, OutError))
    { if (Battle) Battle->Destroy(); return nullptr; }
    Controller->SetCurrentBattleServer(Battle);
    return Battle;
}

ADigimonVenomNXTBattleActor* ADigimonVenomNXTGameMode::StartRelayFieldTrainingFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Controller, &OutError)) return nullptr;
    if (!HasAuthority() || !RelayPlayerReady(Controller, OutError)) return nullptr;
    ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const EDigimonPrivateCampaign Campaign = Controller->GetStoryCampaign();
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(Campaign, DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign).MapId);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    if (!Map || !Data) { OutError = TEXT("This training area's data is unavailable."); return nullptr; }
    if (Map->bPeaceful)
    { OutError = FString::Printf(TEXT("%s is a peaceful hub. Visit a field map to train."), *Map->Name); return nullptr; }
    TArray<FDigimonOwnedPartner> Living;
    int32 WeakestLevel = 99;
    for (int32 I = 0; I < FMath::Min(3, PS->Profile.Party.Num()); ++I)
    {
        FDigimonOwnedPartner Partner;
        if (PS->GetPartner(PS->Profile.Party[I], Partner) && Partner.CurrentHP > 0)
        { Living.Add(Partner); WeakestLevel = FMath::Min(WeakestLevel, Partner.Level); }
    }
    if (Living.IsEmpty()) { OutError = TEXT("Recover your partners before training."); return nullptr; }
    const int32 Level = FMath::Min(FMath::Max(1, WeakestLevel), FMath::Max(1, Map->MinLevel));
    const int32 RankLimit = Level < 15 ? 2 : Level < 30 ? 3 : Level < 45 ? 4 : Level < 60 ? 5 : 6;
    const auto StageRank = [](EDigimonStage Stage)
    {
        return Stage == EDigimonStage::Armor || Stage == EDigimonStage::Hybrid ? 3 :
            Stage <= EDigimonStage::Ultra ? static_cast<int32>(Stage) : 2;
    };
    TArray<FDigimonWildEncounterEntry> Candidates;
    // Preserve the source region's authored team pool, including repeat weights.
    for (const FDigimonRelayNPC& NPC : DigimonVenomNXTCampaign::NPCs(Campaign))
    {
        const FDigimonRelayMap* NPCMap = DigimonVenomNXTCampaign::GetMap(Campaign, NPC.MapId);
        if (!NPCMap || NPCMap->RegionIndex != Map->RegionIndex) continue;
        for (int32 I = 0; I < NPC.TeamSpecies.Num(); ++I)
        {
            FDigimonSpeciesDefinition Species;
            if (Data->GetSpecies(NPC.TeamSpecies[I], Species) && !Species.bPlaceholder && StageRank(Species.Stage) <= RankLimit)
            {
                FDigimonWildEncounterEntry Entry; Entry.SpeciesId = Species.SpeciesId;
                Entry.Variant = NPC.TeamVariants.IsValidIndex(I) && NPC.TeamVariants[I] == EDigimonVariant::Paradox ? EDigimonVariant::Paradox : EDigimonVariant::Normal;
                Candidates.Add(Entry);
            }
        }
    }
    if (Candidates.IsEmpty())
        for (const FDigimonSpeciesDefinition& Species : Data->GetStarterCandidates(MAX_int32))
        { FDigimonWildEncounterEntry Entry; Entry.SpeciesId = Species.SpeciesId; Candidates.Add(Entry); }
    if (Candidates.IsEmpty()) { OutError = TEXT("No suitable training Digimon are installed for this region."); return nullptr; }
    TArray<FDigimonWildEncounterEntry> Encounters;
    for (const FDigimonOwnedPartner& Partner : Living)
    {
        FDigimonSpeciesDefinition OwnSpecies;
        if (!Data->GetSpecies(Partner.SpeciesId, OwnSpecies)) { OutError = TEXT("Your partner's species data is unavailable."); return nullptr; }
        TArray<FDigimonWildEncounterEntry> SafePool;
        for (const FDigimonWildEncounterEntry& Candidate : Candidates)
        {
            FDigimonSpeciesDefinition Species;
            if (Data->GetSpecies(Candidate.SpeciesId, Species) && (Species.Affinity == OwnSpecies.Affinity || Species.Affinity == EDigimonAffinity::Free)) SafePool.Add(Candidate);
        }
        FDigimonWildEncounterEntry Entry;
        if (Level < 10 || SafePool.IsEmpty())
        {
            Entry.SpeciesId = Partner.SpeciesId;
            Entry.Variant = Partner.Variant == EDigimonVariant::Paradox ? EDigimonVariant::Paradox : EDigimonVariant::Normal;
        }
        else Entry = SafePool[FMath::RandRange(0, SafePool.Num() - 1)];
        Entry.Level = Level;
        Encounters.Add(Entry);
    }
    TArray<FName> ShinyPool, FirewallPool;
    for (const FDigimonWildEncounterEntry& Encounter : Encounters)
    {
        FDigimonSpeciesDefinition Species;
        if (!Data->GetSpecies(Encounter.SpeciesId, Species)) continue;
        if (Species.bHasShinyArtwork) ShinyPool.AddUnique(Species.SpeciesId);
        if (Species.bHasFirewallArtwork) FirewallPool.AddUnique(Species.SpeciesId);
    }
    ReplaceWildVariety(Encounters, {}, ShinyPool, FirewallPool);
    ADigimonVenomNXTBattleActor* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(BattleActorClass ? BattleActorClass.Get() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeWildGroupBattle(PS, Encounters))
    { if (Battle) Battle->Destroy(); OutError = TEXT("The private training battle could not start. Please retry."); return nullptr; }
    Controller->SetCurrentBattleServer(Battle);
    PS->MarkProfileChanged();
    return Battle;
}
