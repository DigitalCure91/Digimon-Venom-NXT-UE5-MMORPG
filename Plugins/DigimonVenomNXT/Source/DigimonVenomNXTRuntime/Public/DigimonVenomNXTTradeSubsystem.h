#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTTradeTypes.h"
#include "TimerManager.h"
#include "DigimonVenomNXTTradeSubsystem.generated.h"
class UDigimonVenomNXTTradeComponent;
class ADigimonVenomNXTPlayerState;
class ADigimonVenomNXTPlayerController;

UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTTradeSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Deinitialize() override;
    void Browse(UDigimonVenomNXTTradeComponent* Client, const FString& Search, int32 Page, bool bMineOnly);
    void CreateListing(UDigimonVenomNXTTradeComponent* Client, FGuid PartnerId, int64 Credits, int32 Rubies);
    void CancelListing(UDigimonVenomNXTTradeComponent* Client, FGuid ListingId);
    void ReviewPurchase(UDigimonVenomNXTTradeComponent* Client, FGuid ListingId);
    void Buy(UDigimonVenomNXTTradeComponent* Client, const FDigimonTradeListing& Reviewed);
    void Invite(UDigimonVenomNXTTradeComponent* Client, const FString& TargetAccountId);
    void UpdateOffer(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId, int32 Revision, const TArray<FGuid>& Partners, int64 Credits, int32 Rubies);
    void Confirm(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId, int32 Revision);
    void Cancel(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId);
    void Disconnect(const FString& AccountId);
    /** A failed store read returns true: deleting an account must never discard escrow. */
    bool HasAccountAssets(const FString& AccountId);
private:
    FDigimonTradeMarket Market;
    bool bLoaded = false;
    FTimerHandle SessionExpiryTimer;
    TMap<FGuid, FDigimonDirectTrade> Sessions;
    TMap<FString, double> LastInvitation;
    bool Ready(FString& Error);
    bool Commit(TArray<FDigimonPlayerProfile>& Profiles, const FDigimonTradeMarket& Next, FString& Error);
    ADigimonVenomNXTPlayerController* Online(const FString& AccountId) const;
    bool Blocked(const FString& A, const FString& B) const;
    bool Snapshot(const FString& AccountId, FDigimonPlayerProfile& Profile, FString& Error) const;
    bool ValidateOffer(const FDigimonPlayerProfile& Profile, const TArray<FGuid>& Ids, int64 Credits, int32 Rubies, FDigimonTradeOffer& Offer, FString& Error) const;
    bool CanTransact(ADigimonVenomNXTPlayerState* State, FString& Error) const;
    void PublishSession(const FDigimonDirectTrade& Session, const FString& Message);
    void FinishSession(FGuid Id, const FString& Message, bool bSuccess);
    void ExpireSessions();
    void RefreshBrowsers();
};
