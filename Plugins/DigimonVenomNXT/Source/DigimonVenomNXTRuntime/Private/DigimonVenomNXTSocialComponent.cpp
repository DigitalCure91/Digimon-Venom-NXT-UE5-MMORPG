#include "DigimonVenomNXTSocialComponent.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

namespace
{
    UDigimonVenomNXTSocialSubsystem* SocialFor(UActorComponent* Component, ADigimonVenomNXTPlayerController*& OutOwner)
    {
        OutOwner = Component ? Cast<ADigimonVenomNXTPlayerController>(Component->GetOwner()) : nullptr;
        if (!OutOwner || !OutOwner->HasAuthority() || !OutOwner->IsAccountAuthenticated() || !OutOwner->GetGameInstance()) return nullptr;
        return OutOwner->GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
    }
}

UDigimonVenomNXTSocialComponent::UDigimonVenomNXTSocialComponent()
{
    SetIsReplicatedByDefault(true);
    PrimaryComponentTick.bCanEverTick = false;
}

void UDigimonVenomNXTSocialComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner() && GetOwner()->HasAuthority() && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(PresenceTimer, this, &UDigimonVenomNXTSocialComponent::RefreshServerState, 2.0f, true, 0.25f);
    }
}

void UDigimonVenomNXTSocialComponent::EndPlay(const EEndPlayReason::Type Reason)
{
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(PresenceTimer);
    Super::EndPlay(Reason);
}

void UDigimonVenomNXTSocialComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTSocialComponent, State, COND_OwnerOnly);
}

void UDigimonVenomNXTSocialComponent::RefreshServerState()
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return;
    ADigimonVenomNXTPlayerController* PC = nullptr;
    if (UDigimonVenomNXTSocialSubsystem* Social = SocialFor(this, PC)) Social->BuildState(PC, State);
    else State = FDigimonSocialState();
    if (PC && PC->IsLocalController()) OnRep_State();
}

void UDigimonVenomNXTSocialComponent::ServerRefreshSocial_Implementation()
{
    const double Now = FPlatformTime::Seconds();
    if (Now - LastRefreshRequest < 1.0) return;
    LastRefreshRequest = Now;
    RefreshServerState();
}

void UDigimonVenomNXTSocialComponent::ServerSocialAction_Implementation(EDigimonSocialAction Action, const FString& Target, const FString& Text, const FString& Extra)
{
    const double Now = FPlatformTime::Seconds();
    if (Now - LastActionRequest < 0.35) return;
    LastActionRequest = Now;
    ADigimonVenomNXTPlayerController* PC = nullptr;
    UDigimonVenomNXTSocialSubsystem* Social = SocialFor(this, PC);
    if (!Social) return;
    FString Message;
    const bool bSuccess = Social->Execute(PC, Action, Target, Text, Extra, Message);
    RefreshServerState();
    ClientSocialResult(bSuccess, Message);
}

void UDigimonVenomNXTSocialComponent::ServerRequestPlayerInfo_Implementation(const FString& UsernameOrId)
{
    const double Now = FPlatformTime::Seconds();
    if (Now - LastInfoRequest < 0.5) return;
    LastInfoRequest = Now;
    ADigimonVenomNXTPlayerController* PC = nullptr;
    UDigimonVenomNXTSocialSubsystem* Social = SocialFor(this, PC);
    if (!Social) return;
    FString Message;
    const bool bSuccess = Social->GetPlayerInfo(PC, UsernameOrId, State.PlayerInfo, Message);
    RefreshServerState();
    if (!bSuccess) ClientSocialResult(false, Message);
}

void UDigimonVenomNXTSocialComponent::ServerSendClanChat_Implementation(const FString& Message)
{
    const double Now = FPlatformTime::Seconds();
    if (Now - LastChatRequest < 1.0) return;
    LastChatRequest = Now;
    ADigimonVenomNXTPlayerController* PC = nullptr;
    UDigimonVenomNXTSocialSubsystem* Social = SocialFor(this, PC);
    if (!Social) return;
    FString Error;
    if (!Social->SendClanChat(PC, Message, Error)) ClientSocialResult(false, Error);
}

void UDigimonVenomNXTSocialComponent::ClientSocialResult_Implementation(bool bSuccess, const FString& Message)
{
    LastResult = Message;
    bLastResultSucceeded = bSuccess;
    OnSocialResult.Broadcast(bSuccess, Message);
    OnSocialChanged.Broadcast();
}

void UDigimonVenomNXTSocialComponent::OnRep_State()
{
    if (ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwner()))
        if (PC->IsLocalController()) PC->RefreshIgnoredChat();
    OnSocialChanged.Broadcast();
}
