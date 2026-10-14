#include "DigimonVenomNXTTradeSubsystem.h"
#include "DigimonVenomNXTTradeComponent.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTTradeCore.h"
#include "DigimonVenomNXTTradeStorage.h"
#include "DigimonVenomNXTServerActivity.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "JsonObjectConverter.h"

namespace
{
ADigimonVenomNXTPlayerState* OwnerState(UDigimonVenomNXTTradeComponent* Client)
{
    return Client && Client->Controller() ? Client->Controller()->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
}
UDigimonVenomNXTTradeComponent* Component(ADigimonVenomNXTPlayerController* PC)
{
    return PC ? PC->FindComponentByClass<UDigimonVenomNXTTradeComponent>() : nullptr;
}
void RemovePartners(FDigimonPlayerProfile& Profile, const FDigimonTradeOffer& Offer)
{
    for (const FDigimonOwnedPartner& Partner : Offer.Partners)
    {
        Profile.Collection.RemoveAll([&](const FDigimonOwnedPartner& Existing) { return Existing.InstanceId == Partner.InstanceId; });
        Profile.Party.Remove(Partner.InstanceId);
        for (auto& Tamer : Profile.Season.Roster)
            if (Tamer.bPlayer)
                Tamer.Team.RemoveAll([&](const FDigimonOwnedPartner& Existing) { return Existing.InstanceId == Partner.InstanceId; });
    }
}
bool SameOffer(const FDigimonTradeOffer& A, const FDigimonTradeOffer& B)
{
    if (A.Credits != B.Credits || A.DigiRubies != B.DigiRubies || A.Partners.Num() != B.Partners.Num()) return false;
    for (int32 Index = 0; Index < A.Partners.Num(); ++Index)
        if (!FDigimonOwnedPartner::StaticStruct()->CompareScriptStruct(&A.Partners[Index], &B.Partners[Index], 0)) return false;
    return true;
}
TArray<FGuid> OfferIds(const FDigimonTradeOffer& Offer)
{
    TArray<FGuid> Ids;
    for (const auto& Partner : Offer.Partners) Ids.Add(Partner.InstanceId);
    return Ids;
}
bool HasGift(const FDigimonTradeOffer& Offer)
{
    return !Offer.Partners.IsEmpty() || Offer.Credits > 0 || Offer.DigiRubies > 0;
}
}

void UDigimonVenomNXTTradeSubsystem::Deinitialize()
{
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(SessionExpiryTimer);
    Sessions.Empty(); LastInvitation.Empty();
    Super::Deinitialize();
}

bool UDigimonVenomNXTTradeSubsystem::Ready(FString& Error)
{
    if (!GetGameInstance() || !GetWorld() || GetWorld()->GetNetMode() == NM_Client)
        { Error = TEXT("Trading is available after signing in to a server."); return false; }
    auto* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Profiles) { Error = TEXT("Profile storage is unavailable."); return false; }
    if (bLoaded)
    {
        if (Profiles->IsCommerceStorageReady()) return true;
        Error = TEXT("Trading storage recovery is pending. Please retry later."); return false;
    }
    FString Json; bool bExists = false;
    if (!Profiles->LoadCommerceMarket(Json, bExists, Error)) return false;
    FDigimonTradeMarket Loaded;
    if (bExists && !DigimonVenomNXTTradeStorage::ReadMarket(Json, Loaded))
        { Error = TEXT("Saved listings failed validation. Trading is paused to protect escrow."); return false; }
    Market = MoveTemp(Loaded); bLoaded = true; return true;
}

ADigimonVenomNXTPlayerController* UDigimonVenomNXTTradeSubsystem::Online(const FString& AccountId) const
{
    if (!GetWorld() || AccountId.IsEmpty()) return nullptr;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get()))
            if (PC->IsAccountAuthenticated())
                if (auto* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>())
                    if (PS->Profile.AccountId == AccountId) return PC;
    return nullptr;
}

bool UDigimonVenomNXTTradeSubsystem::Blocked(const FString& A, const FString& B) const
{
    const auto* Social = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>() : nullptr;
    return !Social || Social->IsInteractionBlocked(A, B);
}

bool UDigimonVenomNXTTradeSubsystem::Snapshot(const FString& AccountId, FDigimonPlayerProfile& Profile, FString& Error) const
{
    if (auto* PC = Online(AccountId))
    {
        Profile = PC->GetPlayerState<ADigimonVenomNXTPlayerState>()->Profile; return true;
    }
    auto* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (Profiles && Profiles->LoadExistingCommerceProfile(AccountId, Profile)) return true;
    Error = TEXT("The account's saved progress is unavailable. Nothing was traded."); return false;
}

bool UDigimonVenomNXTTradeSubsystem::CanTransact(ADigimonVenomNXTPlayerState* State, FString& Error) const
{
    if (!State || State->Profile.AccountId.IsEmpty())
        { Error = TEXT("Sign in before trading."); return false; }
    if (!DigimonVenomNXTServerActivity::AllowGameplay(State, &Error)) return false;
    if (State->Profile.Collection.IsEmpty() || State->Profile.Party.IsEmpty())
        { Error = TEXT("Choose your starter and active party before trading."); return false; }
    if (State->HasActiveBattle()) { Error = TEXT("Finish your live or saved battle before trading."); return false; }
    return true;
}

bool UDigimonVenomNXTTradeSubsystem::ValidateOffer(const FDigimonPlayerProfile& Profile, const TArray<FGuid>& Ids,
    int64 Credits, int32 Rubies, FDigimonTradeOffer& Offer, FString& Error) const
{
    if (Credits < 0 || Credits > DigimonVenomNXTTradeCore::MaxCredits || Rubies < 0 ||
        Credits > Profile.Credits || Rubies > Profile.DigiRubies || Ids.Num() > DigimonVenomNXTTradeCore::MaxPartners)
        { Error = TEXT("Choose up to 6 Digimon and amounts you currently own."); return false; }
    if (!Profile.Season.BattleCheckpointJson.IsEmpty() || DigimonVenomNXTCampaign::HasPendingBattle(Profile))
        { Error = TEXT("Finish your saved battle before trading."); return false; }
    Offer = FDigimonTradeOffer(); Offer.Credits = Credits; Offer.DigiRubies = Rubies;
    TSet<FGuid> Seen;
    for (const FGuid& Id : Ids)
    {
        const FDigimonOwnedPartner* Partner = Profile.Collection.FindByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; });
        if (!Id.IsValid() || Seen.Contains(Id) || !Partner || !Partner->IsValid())
            { Error = TEXT("One selected Digimon is no longer owned or was selected twice."); return false; }
        if (Profile.DigiFarmResidents.Contains(Id))
            { Error = TEXT("Remove the selected Digimon from DigiFarm before trading it."); return false; }
        if (Profile.Ranked.DefenderLineup.Contains(Id) || Profile.Ranked.DefenderTeam.ContainsByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; }))
            { Error = TEXT("Remove the selected Digimon from your ranked defender team before trading it."); return false; }
        Seen.Add(Id); Offer.Partners.Add(*Partner);
    }
    // A trade cannot leave the owner without a playable current party, even if receiving
    // partners. New arrivals are boxed until the player deliberately changes their party.
    if (!Ids.IsEmpty())
    {
        bool bRemainingPlayable = false;
        for (const auto& Partner : Profile.Collection)
            if (Profile.Party.Contains(Partner.InstanceId) && !Seen.Contains(Partner.InstanceId) && Partner.CurrentHP > 0)
                { bRemainingPlayable = true; break; }
        if (!bRemainingPlayable) { Error = TEXT("Keep at least one healthy Digimon in your active party."); return false; }
    }
    return true;
}

bool UDigimonVenomNXTTradeSubsystem::Commit(TArray<FDigimonPlayerProfile>& Profiles, const FDigimonTradeMarket& Next, FString& Error)
{
    FString MarketJson;
    if (!FJsonObjectConverter::UStructToJsonObjectString(Next, MarketJson))
        { Error = TEXT("Could not prepare the listing. Nothing was traded."); return false; }
    for (auto& Profile : Profiles)
    {
        if (Profile.CommerceRevision >= DigimonVenomNXTTradeCore::MaxCredits)
            { Error = TEXT("The account's transaction counter requires maintenance."); return false; }
        ++Profile.CommerceRevision;
    }
    auto* Persistence = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Persistence || !Persistence->CommitCommerce(Profiles, MarketJson, Error)) return false;
    Market = Next;
    // Publish only after the complete intent has committed; callbacks never see half a swap.
    TArray<ADigimonVenomNXTPlayerState*> Changed;
    for (const auto& Profile : Profiles)
        if (auto* PC = Online(Profile.AccountId))
        {
            auto* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>();
            PS->Profile = Profile; Changed.Add(PS);
        }
    for (auto* PS : Changed) PS->MarkProfileChanged();
    return true;
}

void UDigimonVenomNXTTradeSubsystem::Browse(UDigimonVenomNXTTradeComponent* Client, const FString& Search, int32 Page, bool bMineOnly)
{
    FString Error;
    auto* PS = OwnerState(Client);
    if (!PS || !Ready(Error)) { if (Client) Client->Result(false, Error); return; }
    ExpireSessions();
    TArray<FDigimonTradeListing> Results;
    const FString Query = Search.Left(64).TrimStartAndEnd();
    for (const auto& Listing : Market.Listings)
    {
        const bool bOwn = Listing.SellerAccountId == PS->Profile.AccountId;
        if ((bMineOnly && !bOwn) || (!bOwn && Blocked(PS->Profile.AccountId, Listing.SellerAccountId))) continue;
        if (!Query.IsEmpty() && !Listing.SellerName.Contains(Query) && !Listing.Partner.Nickname.Contains(Query) &&
            !Listing.Partner.SpeciesId.ToString().Contains(Query)) continue;
        Results.Add(Listing);
    }
    Results.Sort([](const auto& A, const auto& B) { return A.CreatedUnix == B.CreatedUnix ? A.ListingId.ToString() < B.ListingId.ToString() : A.CreatedUnix > B.CreatedUnix; });
    Client->View.TotalListings = Results.Num();
    Client->View.Page = FMath::Clamp(Page, 0, FMath::Max(0, (Results.Num() - 1) / DigimonVenomNXTTradeCore::PageSize));
    Client->View.Search = Query; Client->View.bMineOnly = bMineOnly; Client->View.Listings.Reset();
    const int32 Start = Client->View.Page * DigimonVenomNXTTradeCore::PageSize;
    for (int32 I = Start; I < FMath::Min(Start + DigimonVenomNXTTradeCore::PageSize, Results.Num()); ++I) Client->View.Listings.Add(Results[I]);
    Client->Publish();
}

void UDigimonVenomNXTTradeSubsystem::RefreshBrowsers()
{
    if (!GetWorld()) return;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get()))
            if (PC->IsAccountAuthenticated())
                if (auto* Client = Component(PC))
                    if (Client->HasBrowsedMarket()) Browse(Client, Client->View.Search, Client->View.Page, Client->View.bMineOnly);
}

void UDigimonVenomNXTTradeSubsystem::CreateListing(UDigimonVenomNXTTradeComponent* Client, FGuid PartnerId, int64 Credits, int32 Rubies)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    if (!DigimonVenomNXTTradeCore::ValidPrice(Credits, Rubies))
        { Client->Result(false, TEXT("Set a positive price in money, DigiRubies, or both.")); return; }
    int32 OwnCount = 0;
    for (const auto& Listing : Market.Listings) if (Listing.SellerAccountId == PS->Profile.AccountId) ++OwnCount;
    if (OwnCount >= DigimonVenomNXTTradeCore::MaxListingsPerAccount || Market.Listings.Num() >= 10000)
        { Client->Result(false, TEXT("Listing limit reached. Cancel or sell an existing listing first.")); return; }
    FDigimonTradeOffer Escrow;
    if (!ValidateOffer(PS->Profile, { PartnerId }, 0, 0, Escrow, Error)) { Client->Result(false, Error); return; }
    FDigimonTradeMarket Next = Market;
    FDigimonTradeListing Listing;
    Listing.ListingId = FGuid::NewGuid(); Listing.SellerAccountId = PS->Profile.AccountId; Listing.SellerName = PS->Profile.Username;
    Listing.Partner = Escrow.Partners[0]; Listing.Credits = Credits; Listing.DigiRubies = Rubies;
    Listing.CreatedUnix = FDateTime::UtcNow().ToUnixTimestamp(); Next.Listings.Add(Listing);
    TArray<FDigimonPlayerProfile> Profiles { PS->Profile }; RemovePartners(Profiles[0], Escrow);
    if (!Commit(Profiles, Next, Error)) { Client->Result(false, Error); return; }
    Client->Result(true, TEXT("Listing published. Your Digimon is held safely until sold or cancelled.")); RefreshBrowsers();
}

void UDigimonVenomNXTTradeSubsystem::CancelListing(UDigimonVenomNXTTradeComponent* Client, FGuid ListingId)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    const int32 Index = Market.Listings.IndexOfByPredicate([&](const auto& L) { return L.ListingId == ListingId && L.SellerAccountId == PS->Profile.AccountId; });
    if (Index == INDEX_NONE) { Client->Result(false, TEXT("That listing has already ended or belongs to another player.")); return; }
    if (PS->Profile.Collection.ContainsByPredicate([&](const auto& P) { return P.InstanceId == Market.Listings[Index].Partner.InstanceId; }))
        { Client->Result(false, TEXT("Ownership conflict. Please contact the server administrator.")); return; }
    FDigimonTradeMarket Next = Market;
    TArray<FDigimonPlayerProfile> Profiles { PS->Profile };
    // Returning escrow must never be blocked by collection capacity: it is already owned property.
    Profiles[0].Collection.Add(Next.Listings[Index].Partner); Next.Listings.RemoveAt(Index);
    if (!Commit(Profiles, Next, Error)) { Client->Result(false, Error); return; }
    Client->Result(true, TEXT("Listing cancelled. Your Digimon is back in your collection.")); RefreshBrowsers();
}

void UDigimonVenomNXTTradeSubsystem::ReviewPurchase(UDigimonVenomNXTTradeComponent* Client, FGuid ListingId)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    const auto* Listing = Market.Listings.FindByPredicate([&](const auto& L) { return L.ListingId == ListingId; });
    if (!Listing || Listing->SellerAccountId == PS->Profile.AccountId || Blocked(PS->Profile.AccountId, Listing->SellerAccountId))
        { Client->Result(false, TEXT("That listing is unavailable.")); return; }
    Client->View.PurchaseReview = *Listing; Client->View.PurchaseToken = FGuid::NewGuid();
    Client->Result(true, TEXT("Review this Digimon and both currency amounts. Confirm purchase within 60 seconds."));
}

void UDigimonVenomNXTTradeSubsystem::Buy(UDigimonVenomNXTTradeComponent* Client, const FDigimonTradeListing& Reviewed)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    const int32 Index = Market.Listings.IndexOfByPredicate([&](const auto& L) { return L.ListingId == Reviewed.ListingId; });
    if (Index == INDEX_NONE) { Client->Result(false, TEXT("Another player bought this Digimon or the seller cancelled.")); return; }
    const auto& Listing = Market.Listings[Index];
    if (!FDigimonTradeListing::StaticStruct()->CompareScriptStruct(&Listing, &Reviewed, 0) ||
        Listing.SellerAccountId == PS->Profile.AccountId || Blocked(PS->Profile.AccountId, Listing.SellerAccountId))
        { Client->Result(false, TEXT("This listing changed or is unavailable. Review it again.")); return; }
    if (!DigimonVenomNXTTradeCore::ReceiveFits(PS->Profile.Collection.Num(), 0, 1) ||
        PS->Profile.Collection.ContainsByPredicate([&](const auto& P) { return P.InstanceId == Listing.Partner.InstanceId; }))
        { Client->Result(false, TEXT("Your collection cannot receive this Digimon. Free a collection slot first.")); return; }
    FDigimonPlayerProfile Seller;
    if (!Snapshot(Listing.SellerAccountId, Seller, Error)) { Client->Result(false, Error); return; }
    if (Seller.Collection.ContainsByPredicate([&](const auto& P) { return P.InstanceId == Listing.Partner.InstanceId; }))
        { Client->Result(false, TEXT("Escrow ownership conflict. Please contact the server administrator.")); return; }
    std::int64_t BuyerCredits, SellerCredits, BuyerRubies, SellerRubies;
    if (!DigimonVenomNXTTradeCore::Exchange(PS->Profile.Credits, Seller.Credits, Listing.Credits, 0,
            DigimonVenomNXTTradeCore::MaxCredits, BuyerCredits, SellerCredits) ||
        !DigimonVenomNXTTradeCore::Exchange(PS->Profile.DigiRubies, Seller.DigiRubies, Listing.DigiRubies, 0,
            DigimonVenomNXTTradeCore::MaxRubies, BuyerRubies, SellerRubies))
        { Client->Result(false, TEXT("Insufficient funds or the seller has reached a currency limit. Nothing was spent.")); return; }
    TArray<FDigimonPlayerProfile> Profiles { PS->Profile, Seller };
    Profiles[0].Credits = BuyerCredits; Profiles[0].DigiRubies = static_cast<int32>(BuyerRubies); Profiles[0].Collection.Add(Listing.Partner);
    Profiles[1].Credits = SellerCredits; Profiles[1].DigiRubies = static_cast<int32>(SellerRubies);
    FDigimonTradeMarket Next = Market; Next.Listings.RemoveAt(Index);
    if (!Commit(Profiles, Next, Error)) { Client->Result(false, Error); return; }
    Client->Result(true, TEXT("Purchase complete. Your Digimon is in your collection."));
    if (auto* SellerClient = Component(Online(Seller.AccountId))) SellerClient->Result(true, TEXT("Your listing sold. Payment has been added to your account."));
    RefreshBrowsers();
}

bool UDigimonVenomNXTTradeSubsystem::HasAccountAssets(const FString& AccountId)
{
    FString Error;
    if (!Ready(Error)) return true;
    if (Market.Listings.ContainsByPredicate([&](const auto& L) { return L.SellerAccountId == AccountId; })) return true;
    for (const auto& Pair : Sessions)
        if (Pair.Value.FirstAccountId == AccountId || Pair.Value.SecondAccountId == AccountId) return true;
    return false;
}

void UDigimonVenomNXTTradeSubsystem::ExpireSessions()
{
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    TArray<FGuid> Expired;
    for (const auto& Pair : Sessions)
    {
        const auto* First = Online(Pair.Value.FirstAccountId);
        const auto* Second = Online(Pair.Value.SecondAccountId);
        if (Pair.Value.ExpiresUnix < Now || !First || !Second || First->IsLogoutPending() || Second->IsLogoutPending() ||
            Blocked(Pair.Value.FirstAccountId, Pair.Value.SecondAccountId)) Expired.Add(Pair.Key);
    }
    for (const FGuid& Id : Expired) FinishSession(Id, TEXT("Trade closed because it expired or a player became unavailable. Nothing was exchanged."), false);
}

void UDigimonVenomNXTTradeSubsystem::PublishSession(const FDigimonDirectTrade& Session, const FString& Message)
{
    for (const FString& Account : { Session.FirstAccountId, Session.SecondAccountId })
        if (auto* Client = Component(Online(Account))) { Client->View.Session = Session; Client->Result(true, Message); }
}

void UDigimonVenomNXTTradeSubsystem::FinishSession(FGuid Id, const FString& Message, bool bSuccess)
{
    FDigimonDirectTrade Finished;
    if (!Sessions.RemoveAndCopyValue(Id, Finished)) return;
    if (Sessions.IsEmpty() && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(SessionExpiryTimer);
    for (const FString& Account : { Finished.FirstAccountId, Finished.SecondAccountId })
        if (auto* Client = Component(Online(Account))) { Client->View.Session = FDigimonDirectTrade(); Client->Result(bSuccess, Message); }
}

void UDigimonVenomNXTTradeSubsystem::Invite(UDigimonVenomNXTTradeComponent* Client, const FString& TargetAccountId)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    ExpireSessions();
    const double Now = FPlatformTime::Seconds();
    if (const double* Last = LastInvitation.Find(PS->Profile.AccountId))
        if (Now - *Last < 10.0) { Client->Result(false, TEXT("Wait a moment before sending another trade invitation.")); return; }
    LastInvitation.Add(PS->Profile.AccountId, Now);
    auto* Target = Online(TargetAccountId);
    // The menu accepts an exact username; nameplates supply the opaque account ID.
    if (!Target && GetWorld())
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
            if (auto* Candidate = Cast<ADigimonVenomNXTPlayerController>(It->Get()))
                if (Candidate->IsAccountAuthenticated())
                    if (auto* CandidateState = Candidate->GetPlayerState<ADigimonVenomNXTPlayerState>())
                        if (CandidateState->Profile.Username.Equals(TargetAccountId.TrimStartAndEnd(), ESearchCase::IgnoreCase))
                            { Target = Candidate; break; }
    auto* TargetPS = Target ? Target->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    const FString ResolvedAccount = TargetPS ? TargetPS->Profile.AccountId : FString();
    if (ResolvedAccount == PS->Profile.AccountId || !Target || !Component(Target) || Blocked(PS->Profile.AccountId, ResolvedAccount) || !CanTransact(TargetPS, Error))
        { Client->Result(false, TEXT("That player is unavailable for a direct trade.")); return; }
    for (const auto& Pair : Sessions)
        if (Pair.Value.FirstAccountId == PS->Profile.AccountId || Pair.Value.SecondAccountId == PS->Profile.AccountId ||
            Pair.Value.FirstAccountId == ResolvedAccount || Pair.Value.SecondAccountId == ResolvedAccount)
            { Client->Result(false, TEXT("One player already has a trade open. Close it before starting another.")); return; }
    FDigimonDirectTrade Session;
    Session.SessionId = FGuid::NewGuid(); Session.FirstAccountId = PS->Profile.AccountId; Session.FirstName = PS->Profile.Username;
    Session.SecondAccountId = ResolvedAccount; Session.SecondName = TargetPS->Profile.Username;
    Session.ExpiresUnix = FDateTime::UtcNow().ToUnixTimestamp() + 300;
    Sessions.Add(Session.SessionId, Session);
    if (GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(SessionExpiryTimer))
        GetWorld()->GetTimerManager().SetTimer(SessionExpiryTimer, this, &UDigimonVenomNXTTradeSubsystem::ExpireSessions, 5.0f, true);
    PublishSession(Session, TEXT("Trade invitation opened. Add your offer, review both sides, then each player confirms. Cancel to decline."));
    Target->ClientShowMessage(TEXT("Trade invitation"), Session.FirstName + TEXT(" invited you to trade. Open TRADING CENTER, then DIRECT TRADE to review or decline. Nothing is exchanged until both players confirm."));
}

void UDigimonVenomNXTTradeSubsystem::UpdateOffer(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId, int32 Revision,
    const TArray<FGuid>& Partners, int64 Credits, int32 Rubies)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    ExpireSessions(); auto* Session = Sessions.Find(SessionId);
    if (!Session || (Session->FirstAccountId != PS->Profile.AccountId && Session->SecondAccountId != PS->Profile.AccountId))
        { Client->Result(false, TEXT("This trade has closed.")); return; }
    if (Session->Revision != Revision) { Client->Result(false, TEXT("The offer changed. Review the latest details before editing.")); return; }
    if (Blocked(Session->FirstAccountId, Session->SecondAccountId)) { FinishSession(SessionId, TEXT("Trade is no longer available."), false); return; }
    FDigimonTradeOffer Offer;
    if (!ValidateOffer(PS->Profile, Partners, Credits, Rubies, Offer, Error)) { Client->Result(false, Error); return; }
    if (Session->Revision >= MAX_int32 - 1) { FinishSession(SessionId, TEXT("Please open a new trade."), false); return; }
    (Session->FirstAccountId == PS->Profile.AccountId ? Session->First : Session->Second) = Offer;
    Session->First.bConfirmed = Session->Second.bConfirmed = false; ++Session->Revision;
    Session->ExpiresUnix = FDateTime::UtcNow().ToUnixTimestamp() + 300;
    PublishSession(*Session, TEXT("Offer updated. Both confirmations were cleared; review the new offer."));
}

void UDigimonVenomNXTTradeSubsystem::Confirm(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId, int32 Revision)
{
    FString Error; auto* PS = OwnerState(Client);
    if (!CanTransact(PS, Error) || !Ready(Error)) { Client->Result(false, Error); return; }
    ExpireSessions(); auto* Session = Sessions.Find(SessionId);
    if (!Session || (Session->FirstAccountId != PS->Profile.AccountId && Session->SecondAccountId != PS->Profile.AccountId))
        { Client->Result(false, TEXT("This trade has closed.")); return; }
    if (Session->Revision != Revision) { Client->Result(false, TEXT("The other offer changed. Review the latest revision before confirming.")); return; }
    if (Blocked(Session->FirstAccountId, Session->SecondAccountId)) { FinishSession(SessionId, TEXT("Trade is no longer available."), false); return; }
    auto* FirstPC = Online(Session->FirstAccountId); auto* SecondPC = Online(Session->SecondAccountId);
    auto* FirstPS = FirstPC ? FirstPC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    auto* SecondPS = SecondPC ? SecondPC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    if (!CanTransact(FirstPS, Error) || !CanTransact(SecondPS, Error)) { FinishSession(SessionId, Error, false); return; }
    if (!HasGift(Session->First) && !HasGift(Session->Second))
        { Client->Result(false, TEXT("Add at least one Digimon or a currency amount before confirming.")); return; }
    FDigimonTradeOffer FreshFirst, FreshSecond;
    if (!ValidateOffer(FirstPS->Profile, OfferIds(Session->First), Session->First.Credits, Session->First.DigiRubies, FreshFirst, Error) ||
        !ValidateOffer(SecondPS->Profile, OfferIds(Session->Second), Session->Second.Credits, Session->Second.DigiRubies, FreshSecond, Error) ||
        !SameOffer(Session->First, FreshFirst) || !SameOffer(Session->Second, FreshSecond))
    {
        Session->First.bConfirmed = Session->Second.bConfirmed = false;
        if (Session->Revision >= MAX_int32 - 1) { FinishSession(SessionId, TEXT("Please open a new trade."), false); return; }
        ++Session->Revision;
        PublishSession(*Session, TEXT("A Digimon or account balance changed. Update your offers before confirming again.")); return;
    }
    if (!DigimonVenomNXTTradeCore::ReceiveFits(FirstPS->Profile.Collection.Num(), Session->First.Partners.Num(), Session->Second.Partners.Num()) ||
        !DigimonVenomNXTTradeCore::ReceiveFits(SecondPS->Profile.Collection.Num(), Session->Second.Partners.Num(), Session->First.Partners.Num()))
        { Client->Result(false, TEXT("One collection is full. Free a collection slot before trading.")); return; }
    for (const auto& P : Session->First.Partners)
        if (SecondPS->Profile.Collection.ContainsByPredicate([&](const auto& Existing) { return Existing.InstanceId == P.InstanceId; }))
            { FinishSession(SessionId, TEXT("Ownership conflict. Nothing was exchanged."), false); return; }
    for (const auto& P : Session->Second.Partners)
        if (FirstPS->Profile.Collection.ContainsByPredicate([&](const auto& Existing) { return Existing.InstanceId == P.InstanceId; }))
            { FinishSession(SessionId, TEXT("Ownership conflict. Nothing was exchanged."), false); return; }
    std::int64_t FirstCredits, SecondCredits, FirstRubies, SecondRubies;
    if (!DigimonVenomNXTTradeCore::Exchange(FirstPS->Profile.Credits, SecondPS->Profile.Credits, Session->First.Credits, Session->Second.Credits,
        DigimonVenomNXTTradeCore::MaxCredits, FirstCredits, SecondCredits) ||
        !DigimonVenomNXTTradeCore::Exchange(FirstPS->Profile.DigiRubies, SecondPS->Profile.DigiRubies, Session->First.DigiRubies, Session->Second.DigiRubies,
        DigimonVenomNXTTradeCore::MaxRubies, FirstRubies, SecondRubies))
        { Client->Result(false, TEXT("Insufficient funds or a currency limit would be exceeded. Nothing was exchanged.")); return; }
    (Session->FirstAccountId == PS->Profile.AccountId ? Session->First : Session->Second).bConfirmed = true;
    if (!Session->First.bConfirmed || !Session->Second.bConfirmed)
        { PublishSession(*Session, TEXT("Confirmation recorded. Waiting for the other player to confirm this revision.")); return; }
    TArray<FDigimonPlayerProfile> Profiles { FirstPS->Profile, SecondPS->Profile };
    RemovePartners(Profiles[0], Session->First); RemovePartners(Profiles[1], Session->Second);
    Profiles[0].Collection.Append(Session->Second.Partners); Profiles[1].Collection.Append(Session->First.Partners);
    Profiles[0].Credits = FirstCredits; Profiles[1].Credits = SecondCredits;
    Profiles[0].DigiRubies = static_cast<int32>(FirstRubies); Profiles[1].DigiRubies = static_cast<int32>(SecondRubies);
    if (!Commit(Profiles, Market, Error))
    {
        if (Session->Revision >= MAX_int32 - 1) { FinishSession(SessionId, TEXT("Please open a new trade."), false); return; }
        Session->First.bConfirmed = Session->Second.bConfirmed = false; ++Session->Revision;
        PublishSession(*Session, Error + TEXT(" Both players must confirm again.")); return;
    }
    FinishSession(SessionId, TEXT("Trade complete. Digimon and both currencies have been exchanged and saved."), true);
}

void UDigimonVenomNXTTradeSubsystem::Cancel(UDigimonVenomNXTTradeComponent* Client, FGuid SessionId)
{
    auto* PS = OwnerState(Client); const auto* Session = Sessions.Find(SessionId);
    if (PS && Session && (Session->FirstAccountId == PS->Profile.AccountId || Session->SecondAccountId == PS->Profile.AccountId))
        FinishSession(SessionId, TEXT("Trade cancelled. Nothing was exchanged."), true);
}
void UDigimonVenomNXTTradeSubsystem::Disconnect(const FString& AccountId)
{
    LastInvitation.Remove(AccountId);
    TArray<FGuid> Closing;
    for (const auto& Pair : Sessions)
        if (Pair.Value.FirstAccountId == AccountId || Pair.Value.SecondAccountId == AccountId) Closing.Add(Pair.Key);
    for (const FGuid& Id : Closing) FinishSession(Id, TEXT("Trade closed because a player disconnected. Nothing was exchanged."), false);
}
