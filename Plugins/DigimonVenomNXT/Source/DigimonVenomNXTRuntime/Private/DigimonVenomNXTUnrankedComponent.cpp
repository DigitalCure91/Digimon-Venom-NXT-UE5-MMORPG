#include "DigimonVenomNXTUnrankedComponent.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTServerActivity.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "HAL/PlatformTime.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

UDigimonVenomNXTUnrankedComponent::UDigimonVenomNXTUnrankedComponent()
{
    SetIsReplicatedByDefault(true);
}

void UDigimonVenomNXTUnrankedComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner()->HasAuthority())
        GetWorld()->GetTimerManager().SetTimer(InvitationTimer, this, &UDigimonVenomNXTUnrankedComponent::CheckInvitation, 1.0f, true);
}

void UDigimonVenomNXTUnrankedComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(InvitationTimer);
    if (GetOwner() && GetOwner()->HasAuthority()) ClearInvitation(TEXT("Challenge cancelled: the other tamer disconnected."));
    Super::EndPlay(EndPlayReason);
}

void UDigimonVenomNXTUnrankedComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTUnrankedComponent, IncomingChallenge, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTUnrankedComponent, OutgoingChallenge, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTUnrankedComponent, NearbyPlayers, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTUnrankedComponent, NearbyRivals, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTUnrankedComponent, StatusMessage, COND_OwnerOnly);
}

void UDigimonVenomNXTUnrankedComponent::OnRep_State() { OnUnrankedChanged.Broadcast(); }
ADigimonVenomNXTPlayerController* UDigimonVenomNXTUnrankedComponent::Controller() const { return Cast<ADigimonVenomNXTPlayerController>(GetOwner()); }
void UDigimonVenomNXTUnrankedComponent::Notify(const FString& Message)
{
    StatusMessage = Message;
    OnRep_State();
    if (GetOwner()) GetOwner()->ForceNetUpdate();
}

bool UDigimonVenomNXTUnrankedComponent::RateLimit(double& Previous, double Interval)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || !Controller() || !Controller()->IsAccountAuthenticated()) return false;
    const double Now = FPlatformTime::Seconds();
    if (Now - Previous < Interval) return false;
    Previous = Now;
    return true;
}

bool UDigimonVenomNXTUnrankedComponent::Ready(ADigimonVenomNXTPlayerController* Player, FString& Error) const
{
    if (!Player || !Player->IsAccountAuthenticated() || Player->IsLogoutPending() || !Player->GetPawn())
    { Error = TEXT("That tamer is not available for live battle."); return false; }
    if (!DigimonVenomNXTServerActivity::AllowGameplay(Player, &Error)) return false;
    const ADigimonVenomNXTPlayerState* PS = Player->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!PS || PS->Profile.AccountId.IsEmpty() || PS->Profile.Party.IsEmpty())
    { Error = TEXT("Both tamers need a party before starting a live battle."); return false; }
    if (Player->CurrentBattle || PS->HasActiveBattle())
    { Error = TEXT("Finish your battle and return to the world before challenging a tamer."); return false; }
    if (Player->IsInDigiFarm() || Player->IsInRelay() || PS->Profile.Farm.bInside || DigimonVenomNXTCampaign::IsActive(PS->Profile))
    { Error = TEXT("Return to a public habitat to play an unranked match."); return false; }
    return true;
}

bool UDigimonVenomNXTUnrankedComponent::Compatible(ADigimonVenomNXTPlayerController* First, ADigimonVenomNXTPlayerController* Second, FString& Error) const
{
    if (First == Second || !Ready(First, Error) || !Ready(Second, Error)) return false;
    const auto* A = First->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const auto* B = Second->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (A->Profile.CurrentMapId != B->Profile.CurrentMapId)
    { Error = TEXT("Meet in the same public habitat to battle live."); return false; }
    const UDigimonVenomNXTSocialSubsystem* Social = First->GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
    if (!Social || Social->IsInteractionBlocked(A->Profile.AccountId, B->Profile.AccountId))
    { Error = TEXT("That tamer cannot receive your challenge."); return false; }
    return true;
}

ADigimonVenomNXTPlayerController* UDigimonVenomNXTUnrankedComponent::FindOnline(const FString& AccountId) const
{
    if (AccountId.IsEmpty() || AccountId.Len() > 128 || !GetWorld()) return nullptr;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        auto* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        if (PC && PC->IsAccountAuthenticated() && PS && PS->Profile.AccountId == AccountId) return PC;
    }
    return nullptr;
}

void UDigimonVenomNXTUnrankedComponent::ServerRefresh_Implementation()
{
    if (!RateLimit(LastRefresh, 2.0)) return;
    NearbyPlayers.Reset(); NearbyRivals.Reset();
    FString Error;
    if (!Ready(Controller(), Error)) { Notify(Error); return; }
    const auto* Self = Controller()->GetPlayerState<ADigimonVenomNXTPlayerState>();
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It && NearbyPlayers.Num() < 100; ++It)
    {
        auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        auto* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        if (!PC || PC == Controller() || !PC->IsAccountAuthenticated() || !PS || PS->Profile.CurrentMapId != Self->Profile.CurrentMapId || PC->IsInDigiFarm() || PC->IsInRelay()) continue;
        const UDigimonVenomNXTSocialSubsystem* Social = Controller()->GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
        if (!Social || Social->IsInteractionBlocked(Self->Profile.AccountId, PS->Profile.AccountId)) continue;
        FDigimonUnrankedTarget Row;
        Row.AccountId = PS->Profile.AccountId; Row.DisplayName = PS->Profile.Username;
        for (const auto& Partner : PS->Profile.Collection) if (PS->Profile.Party.Contains(Partner.InstanceId)) Row.Level = FMath::Max(Row.Level, Partner.Level);
        auto* Component = PC->FindComponentByClass<UDigimonVenomNXTUnrankedComponent>();
        Row.bAvailable = Component && !Component->IncomingChallenge.ChallengeId.IsValid() && !Component->OutgoingChallenge.ChallengeId.IsValid() && Compatible(Controller(), PC, Error);
        NearbyPlayers.Add(Row);
    }
    if (auto* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>())
        for (const FDigimonAIRivalRecord& Rival : Rivals->GetRivalsOnMap(Self->Profile.CurrentMapId, 100))
        {
            FDigimonUnrankedTarget Row;
            Row.AccountId = Rival.RivalId; Row.DisplayName = Rival.DisplayName; Row.Level = Rival.TamerLevel;
            Row.bAvailable = !Rivals->IsRivalInLiveBattle(Rival.RivalId);
            NearbyRivals.Add(Row);
        }
    Notify(TEXT("Live unranked: original party levels, restored battle HP/SP, no items or rewards. Surrender, disconnection or a missed turn counts as a loss."));
}

void UDigimonVenomNXTUnrankedComponent::ServerChallengePlayer_Implementation(const FString& AccountId)
{
    if (!RateLimit(LastChallenge, 3.0)) return;
    FString Error;
    auto* Other = FindOnline(AccountId);
    if (!Compatible(Controller(), Other, Error)) { Notify(Error.IsEmpty() ? TEXT("That tamer is unavailable.") : Error); return; }
    auto* Component = Other->FindComponentByClass<UDigimonVenomNXTUnrankedComponent>();
    if (!Component || IncomingChallenge.ChallengeId.IsValid() || OutgoingChallenge.ChallengeId.IsValid() ||
        Component->IncomingChallenge.ChallengeId.IsValid() || Component->OutgoingChallenge.ChallengeId.IsValid())
    { Notify(TEXT("One of you already has a pending challenge. Resolve it first.")); return; }
    const auto* Self = Controller()->GetPlayerState<ADigimonVenomNXTPlayerState>();
    const auto* Target = Other->GetPlayerState<ADigimonVenomNXTPlayerState>();
    OutgoingChallenge.ChallengeId = FGuid::NewGuid();
    OutgoingChallenge.OtherAccountId = Target->Profile.AccountId;
    OutgoingChallenge.OtherName = Target->Profile.Username;
    OutgoingChallenge.ExpiresUnix = FDateTime::UtcNow().ToUnixTimestamp() + 45;
    Component->IncomingChallenge = OutgoingChallenge;
    Component->IncomingChallenge.OtherAccountId = Self->Profile.AccountId;
    Component->IncomingChallenge.OtherName = Self->Profile.Username;
    OtherComponent = Component; Component->OtherComponent = this;
    Notify(TEXT("Challenge sent. Waiting for the other tamer (45 seconds)."));
    Component->Notify(Self->Profile.Username + TEXT(" invites you to a live unranked match. Accept or decline within 45 seconds."));
    Other->ClientShowMessage(TEXT("Live battle invitation"), Component->StatusMessage + TEXT(" Open UNRANKED to respond."));
}

void UDigimonVenomNXTUnrankedComponent::ClearInvitation(const FString& Message)
{
    auto* Other = OtherComponent.Get();
    const FGuid Id = IncomingChallenge.ChallengeId.IsValid() ? IncomingChallenge.ChallengeId : OutgoingChallenge.ChallengeId;
    IncomingChallenge = FDigimonUnrankedChallenge(); OutgoingChallenge = FDigimonUnrankedChallenge(); OtherComponent.Reset();
    if (!Id.IsValid()) return;
    Notify(Message);
    if (Other && (Other->IncomingChallenge.ChallengeId == Id || Other->OutgoingChallenge.ChallengeId == Id))
    {
        Other->IncomingChallenge = FDigimonUnrankedChallenge(); Other->OutgoingChallenge = FDigimonUnrankedChallenge(); Other->OtherComponent.Reset();
        Other->Notify(Message);
    }
}

void UDigimonVenomNXTUnrankedComponent::CheckInvitation()
{
    const int64 Expiry = IncomingChallenge.ChallengeId.IsValid() ? IncomingChallenge.ExpiresUnix : OutgoingChallenge.ExpiresUnix;
    if (Expiry == 0) return;
    FString Error;
    if (FDateTime::UtcNow().ToUnixTimestamp() >= Expiry) ClearInvitation(TEXT("Challenge expired. You can send another invitation."));
    else if (!OtherComponent.IsValid() || !Compatible(Controller(), OtherComponent->Controller(), Error))
        ClearInvitation(TEXT("Challenge cancelled: a tamer is no longer available in this habitat."));
}

void UDigimonVenomNXTUnrankedComponent::ServerRespond_Implementation(FGuid ChallengeId, bool bAccept)
{
    if (!RateLimit(LastAction, 0.25) || !ChallengeId.IsValid() || IncomingChallenge.ChallengeId != ChallengeId) return;
    if (!bAccept) { ClearInvitation(TEXT("Challenge declined.")); return; }
    auto* Other = OtherComponent.Get();
    FString Error;
    if (!Other || Other->OutgoingChallenge.ChallengeId != ChallengeId || FDateTime::UtcNow().ToUnixTimestamp() >= IncomingChallenge.ExpiresUnix || !Compatible(Controller(), Other->Controller(), Error))
    { ClearInvitation(TEXT("This challenge is no longer available. Meet in the same habitat and try again.")); return; }
    auto* Opponent = Other->Controller();
    auto* Self = Controller();
    // Consume both invitations before spawning: retransmitted acceptance cannot create a second battle.
    ClearInvitation(TEXT("Challenge accepted. Preparing your parties…"));
    auto* Mode = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    auto* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(Mode ? Mode->GetBattleActorClass() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeTamerBattle(Opponent->GetPlayerState<ADigimonVenomNXTPlayerState>(), Self->GetPlayerState<ADigimonVenomNXTPlayerState>(), EDigimonBattleKind::Friendly))
    {
        if (Battle) Battle->Destroy();
        Notify(TEXT("Your parties could not enter battle. Check your party and try again.")); Other->Notify(StatusMessage); return;
    }
    Opponent->SetCurrentBattleServer(Battle); Self->SetCurrentBattleServer(Battle);
    Notify(TEXT("Live unranked match started.")); Other->Notify(StatusMessage);
}

void UDigimonVenomNXTUnrankedComponent::ServerCancel_Implementation(FGuid ChallengeId)
{
    if (RateLimit(LastAction, 0.25) && ChallengeId.IsValid() && OutgoingChallenge.ChallengeId == ChallengeId) ClearInvitation(TEXT("Challenge cancelled."));
}

void UDigimonVenomNXTUnrankedComponent::ServerChallengeRival_Implementation(const FString& RivalId)
{
    if (!RateLimit(LastChallenge, 3.0) || RivalId.IsEmpty() || RivalId.Len() > 128) return;
    FString Error;
    if (!Ready(Controller(), Error)) { Notify(Error); return; }
    if (IncomingChallenge.ChallengeId.IsValid() || OutgoingChallenge.ChallengeId.IsValid()) { Notify(TEXT("Resolve your pending live challenge first.")); return; }
    auto* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>();
    auto* PS = Controller()->GetPlayerState<ADigimonVenomNXTPlayerState>();
    FDigimonAIRivalRecord Rival; FDigimonBattleTeam Team;
    if (!Rivals || !Rivals->GetRival(RivalId, Rival) || Rival.MapId != PS->Profile.CurrentMapId || Rivals->IsRivalInLiveBattle(RivalId) || !Rivals->BuildBattleTeam(RivalId, Team))
    { Notify(TEXT("That rival is busy or has travelled to another habitat. Refresh the list.")); return; }
    auto* Mode = GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();
    auto* Battle = GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>(Mode ? Mode->GetBattleActorClass() : ADigimonVenomNXTBattleActor::StaticClass());
    if (!Battle || !Battle->InitializeAITrainerBattle(PS, Team, EDigimonBattleKind::Friendly, RivalId))
    { if (Battle) Battle->Destroy(); Notify(TEXT("The rival battle could not start. Check your party and retry.")); return; }
    Controller()->SetCurrentBattleServer(Battle);
    Notify(TEXT("Unranked rival match started."));
}

void UDigimonVenomNXTUnrankedComponent::ServerForfeit_Implementation()
{
    if (!RateLimit(LastAction, 0.25)) return;
    if (auto* Battle = Controller()->CurrentBattle.Get())
    {
        const FString Name = Controller()->PlayerState == Battle->PlayerA ? Battle->State.TeamA.TrainerName : Battle->State.TeamB.TrainerName;
        Battle->ForfeitUnranked(Controller(), Name + TEXT(" surrendered the match."));
    }
}
