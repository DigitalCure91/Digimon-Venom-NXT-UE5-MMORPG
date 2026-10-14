#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DigimonVenomNXTUnrankedComponent.generated.h"

class ADigimonVenomNXTPlayerController;

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonUnrankedChallenge
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FGuid ChallengeId;
    UPROPERTY(BlueprintReadOnly) FString OtherAccountId;
    UPROPERTY(BlueprintReadOnly) FString OtherName;
    UPROPERTY(BlueprintReadOnly) int64 ExpiresUnix = 0;
};

/** Deliberately excludes inventory, collection, saved location and private account data. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonUnrankedTarget
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString AccountId;
    UPROPERTY(BlueprintReadOnly) FString DisplayName;
    UPROPERTY(BlueprintReadOnly) int32 Level = 1;
    UPROPERTY(BlueprintReadOnly) bool bAvailable = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigimonUnrankedChanged);

/** Owner-only invitations. Only the server chooses participants, party snapshots and outcomes. */
UCLASS(ClassGroup=(Digimon), meta=(BlueprintSpawnableComponent))
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTUnrankedComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTUnrankedComponent();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly) FDigimonUnrankedChallenge IncomingChallenge;
    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly) FDigimonUnrankedChallenge OutgoingChallenge;
    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly) TArray<FDigimonUnrankedTarget> NearbyPlayers;
    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly) TArray<FDigimonUnrankedTarget> NearbyRivals;
    UPROPERTY(ReplicatedUsing=OnRep_State, BlueprintReadOnly) FString StatusMessage;
    UPROPERTY(BlueprintAssignable) FDigimonUnrankedChanged OnUnrankedChanged;

    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerRefresh();
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerChallengePlayer(const FString& AccountId);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerRespond(FGuid ChallengeId, bool bAccept);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerCancel(FGuid ChallengeId);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerChallengeRival(const FString& RivalId);
    UFUNCTION(BlueprintCallable, Server, Reliable) void ServerForfeit();

private:
    UFUNCTION() void OnRep_State();
    void CheckInvitation();
    void ClearInvitation(const FString& Message);
    void Notify(const FString& Message);
    bool RateLimit(double& Previous, double Interval);
    ADigimonVenomNXTPlayerController* Controller() const;
    bool Ready(ADigimonVenomNXTPlayerController* Player, FString& Error) const;
    bool Compatible(ADigimonVenomNXTPlayerController* First, ADigimonVenomNXTPlayerController* Second, FString& Error) const;
    ADigimonVenomNXTPlayerController* FindOnline(const FString& AccountId) const;
    TWeakObjectPtr<UDigimonVenomNXTUnrankedComponent> OtherComponent;
    double LastRefresh = -1000.0;
    double LastChallenge = -1000.0;
    double LastAction = -1000.0;
    FTimerHandle InvitationTimer;
};
