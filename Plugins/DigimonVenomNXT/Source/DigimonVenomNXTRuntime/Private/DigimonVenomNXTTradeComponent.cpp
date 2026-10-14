#include "DigimonVenomNXTTradeComponent.h"
#include "DigimonVenomNXTTradeSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTServerActivity.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

UDigimonVenomNXTTradeComponent::UDigimonVenomNXTTradeComponent()
{
    SetIsReplicatedByDefault(true);
}
void UDigimonVenomNXTTradeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(UDigimonVenomNXTTradeComponent, View, COND_OwnerOnly);
}
ADigimonVenomNXTPlayerController* UDigimonVenomNXTTradeComponent::Controller() const
{
    return Cast<ADigimonVenomNXTPlayerController>(GetOwner());
}
void UDigimonVenomNXTTradeComponent::OnRep_View() { OnTradeChanged.Broadcast(); }
void UDigimonVenomNXTTradeComponent::Publish()
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return;
    GetOwner()->ForceNetUpdate(); OnTradeChanged.Broadcast();
}
void UDigimonVenomNXTTradeComponent::Result(bool bSuccess, const FString& Message)
{
    View.bSuccess = bSuccess; View.Status = Message; Publish();
}
UDigimonVenomNXTTradeSubsystem* UDigimonVenomNXTTradeComponent::Authorized(bool bMutation)
{
    ADigimonVenomNXTPlayerController* PC = Controller();
    ADigimonVenomNXTPlayerState* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    if (!PC || !PC->HasAuthority() || !PC->IsAccountAuthenticated() || PC->IsLogoutPending() || !PS || PS->Profile.AccountId.IsEmpty()) return nullptr;
    if (bMutation && !DigimonVenomNXTServerActivity::AllowGameplay(PC)) return nullptr;
    double& Last = bMutation ? LastRequest : LastBrowse;
    const double Now = FPlatformTime::Seconds();
    if (Now - Last < (bMutation ? 0.25 : 0.5)) return nullptr;
    Last = Now;
    return PC->GetGameInstance() ? PC->GetGameInstance()->GetSubsystem<UDigimonVenomNXTTradeSubsystem>() : nullptr;
}
void UDigimonVenomNXTTradeComponent::ServerBrowse_Implementation(const FString& Search, int32 Page, bool bMineOnly)
{
    if (Search.Len() > 64 || Page < 0 || Page > 10000) return;
    if (auto* Trade = Authorized(false)) { bHasBrowsed = true; Trade->Browse(this, Search, Page, bMineOnly); }
}
void UDigimonVenomNXTTradeComponent::ServerCreateListing_Implementation(FGuid PartnerId, int64 Credits, int32 DigiRubies)
{
    if (auto* Trade = Authorized()) Trade->CreateListing(this, PartnerId, Credits, DigiRubies);
}
void UDigimonVenomNXTTradeComponent::ServerCancelListing_Implementation(FGuid ListingId)
{
    if (auto* Trade = Authorized()) Trade->CancelListing(this, ListingId);
}
void UDigimonVenomNXTTradeComponent::ServerReviewPurchase_Implementation(FGuid ListingId)
{
    if (auto* Trade = Authorized())
    {
        View.PurchaseToken.Invalidate(); View.PurchaseReview = FDigimonTradeListing();
        Trade->ReviewPurchase(this, ListingId);
        ReviewExpiry = FPlatformTime::Seconds() + 60.0;
    }
}
void UDigimonVenomNXTTradeComponent::ServerConfirmPurchase_Implementation(FGuid PurchaseToken)
{
    if (auto* Trade = Authorized())
    {
        if (!PurchaseToken.IsValid() || PurchaseToken != View.PurchaseToken || FPlatformTime::Seconds() > ReviewExpiry)
            { Result(false, TEXT("Purchase review expired. Review the listing again.")); return; }
        const FDigimonTradeListing Reviewed = View.PurchaseReview;
        View.PurchaseToken.Invalidate(); View.PurchaseReview = FDigimonTradeListing();
        Trade->Buy(this, Reviewed);
    }
}
void UDigimonVenomNXTTradeComponent::ServerInviteTrade_Implementation(const FString& TargetAccountId)
{
    if (TargetAccountId.IsEmpty() || TargetAccountId.Len() > 128) return;
    if (auto* Trade = Authorized()) Trade->Invite(this, TargetAccountId);
}
void UDigimonVenomNXTTradeComponent::ServerUpdateOffer_Implementation(FGuid SessionId, int32 Revision,
    const TArray<FGuid>& PartnerIds, int64 Credits, int32 DigiRubies)
{
    if (PartnerIds.Num() > 6) return;
    if (auto* Trade = Authorized()) Trade->UpdateOffer(this, SessionId, Revision, PartnerIds, Credits, DigiRubies);
}
void UDigimonVenomNXTTradeComponent::ServerConfirmTrade_Implementation(FGuid SessionId, int32 Revision)
{
    if (auto* Trade = Authorized()) Trade->Confirm(this, SessionId, Revision);
}
void UDigimonVenomNXTTradeComponent::ServerCancelTrade_Implementation(FGuid SessionId)
{
    if (auto* Trade = Authorized()) Trade->Cancel(this, SessionId);
}
void UDigimonVenomNXTTradeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (ADigimonVenomNXTPlayerController* PC = Controller())
        if (PC->HasAuthority() && PC->GetGameInstance())
            if (auto* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>())
                if (auto* Trade = PC->GetGameInstance()->GetSubsystem<UDigimonVenomNXTTradeSubsystem>())
                    Trade->Disconnect(PS->Profile.AccountId);
    Super::EndPlay(EndPlayReason);
}
