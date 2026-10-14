#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DigimonVenomNXTSocialTypes.h"
#include "DigimonVenomNXTSocialComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigimonSocialChangedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDigimonSocialResultEvent, bool, bSuccess, const FString&, Message);

/** Default replicated PlayerController subobject. Every RPC derives its account from the authenticated owner. */
UCLASS(ClassGroup=(Digimon), meta=(BlueprintSpawnableComponent))
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTSocialComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTSocialComponent();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly, Category="Digimon Venom NXT|Social") FDigimonSocialState State;
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|Social") FString LastResult;
    UPROPERTY(BlueprintReadOnly, Category="Digimon Venom NXT|Social") bool bLastResultSucceeded = false;
    UPROPERTY(BlueprintAssignable) FDigimonSocialChangedEvent OnSocialChanged;
    UPROPERTY(BlueprintAssignable) FDigimonSocialResultEvent OnSocialResult;

    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerRefreshSocial();
    /**
     * Account actions: Target=username or immutable AccountId; Text/Extra unused.
     * ClanCreate: Target=name (3-32), Text=tag (2-5), Extra=description (0-240).
     * ClanDisband: Target=current ClanId, Text=exact clan name (explicit confirmation).
     * ClanAccept/Decline: Target=ClanId. ClanLeave: no arguments required.
     * ClanUpdate: Target=current ClanId, Text=message of the day (0-200), Extra=description (0-240).
     * ClanTransfer: Target=new leader account, Text=exact clan name (confirmation).
     */
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSocialAction(EDigimonSocialAction Action, const FString& Target, const FString& Text, const FString& Extra);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerRequestPlayerInfo(const FString& UsernameOrId);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerSendClanChat(const FString& Message);
    UFUNCTION(Client, Reliable) void ClientSocialResult(bool bSuccess, const FString& Message);
    /** Server only; called after durable changes and periodically to refresh presence. */
    void RefreshServerState();

private:
    UFUNCTION() void OnRep_State();
    FTimerHandle PresenceTimer;
    double LastRefreshRequest = -100.0;
    double LastInfoRequest = -100.0;
    double LastActionRequest = -100.0;
    double LastChatRequest = -100.0;
};
