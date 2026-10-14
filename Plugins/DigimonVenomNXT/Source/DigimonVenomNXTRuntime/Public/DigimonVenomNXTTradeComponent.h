#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DigimonVenomNXTTradeTypes.h"
#include "DigimonVenomNXTTradeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigimonTradeChangedEvent);
class ADigimonVenomNXTPlayerController;
class UDigimonVenomNXTTradeSubsystem;

UCLASS(ClassGroup=(DigimonVenomNXT), meta=(BlueprintSpawnableComponent))
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTTradeComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTTradeComponent();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    UPROPERTY(ReplicatedUsing=OnRep_View, BlueprintReadOnly) FDigimonTradeView View;
    UPROPERTY(BlueprintAssignable) FDigimonTradeChangedEvent OnTradeChanged;
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerBrowse(const FString& Search, int32 Page, bool bMineOnly);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerCreateListing(FGuid PartnerId, int64 Credits, int32 DigiRubies);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerCancelListing(FGuid ListingId);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerReviewPurchase(FGuid ListingId);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerConfirmPurchase(FGuid PurchaseToken);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerInviteTrade(const FString& TargetAccountId);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerUpdateOffer(FGuid SessionId, int32 Revision, const TArray<FGuid>& PartnerIds, int64 Credits, int32 DigiRubies);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerConfirmTrade(FGuid SessionId, int32 Revision);
    UFUNCTION(Server, Reliable, BlueprintCallable) void ServerCancelTrade(FGuid SessionId);
    /** Called by authority only. Owner-only replication prevents leaking private negotiations. */
    void Publish();
    void Result(bool bSuccess, const FString& Message);
    ADigimonVenomNXTPlayerController* Controller() const;
    bool HasBrowsedMarket() const { return bHasBrowsed; }
private:
    UFUNCTION() void OnRep_View();
    UDigimonVenomNXTTradeSubsystem* Authorized(bool bMutation = true);
    bool bHasBrowsed = false;
    double LastRequest = -1000.0;
    double LastBrowse = -1000.0;
    double ReviewExpiry = 0;
};
