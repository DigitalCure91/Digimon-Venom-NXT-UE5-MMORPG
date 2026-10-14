#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTSocialTypes.h"
#include "DigimonVenomNXTSocialSubsystem.generated.h"

class ADigimonVenomNXTPlayerController;

/** Host-owned, atomic social database. No other player's Profile is ever mutated. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTSocialSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    /** Fail closed when social data is unavailable. Call immediately before accepting a trade/battle too. */
    bool IsInteractionBlocked(const FString& FirstAccountId, const FString& SecondAccountId) const;
    /** Fail closed so admin deletion cannot orphan an unavailable clan database. */
    bool HasClanMembership(const FString& AccountId) const;
    bool IsIgnoring(const FString& ViewerAccountId, const FString& SenderAccountId) const;
    bool Execute(ADigimonVenomNXTPlayerController* Controller, EDigimonSocialAction Action,
        const FString& Target, const FString& Text, const FString& Extra, FString& OutMessage);
    bool SendClanChat(ADigimonVenomNXTPlayerController* Controller, const FString& Message, FString& OutError);
    bool BuildState(ADigimonVenomNXTPlayerController* Controller, FDigimonSocialState& Out) const;
    bool GetPlayerInfo(ADigimonVenomNXTPlayerController* Viewer, const FString& Query,
        FDigimonSocialPlayerInfo& Out, FString& OutError) const;
    void RefreshConnectedClients();
    bool IsReady() const { return bReady; }
    bool SaveForHostConsole();

private:
    friend class FDigimonVenomNXTSocialDatabaseIntegrityTest;
    UPROPERTY() FDigimonSocialDatabase Database;
    bool bReady = false;
    bool bLoaded = false;
    bool bDirty = false;
    TMap<FString, int32> AccountIndex;
    TMap<FString, int32> MembershipIndex;
    TMap<FString, TArray<int32>> InvitationIndex;
    TMap<FString, TArray<FDigimonChatMessage>> ClanChatHistory;
    TMap<FString, double> LastActionTimes;
    TMap<FString, double> LastChatTimes;
    mutable TMap<FString, FDigimonSocialContact> PresenceCache;
    mutable TWeakObjectPtr<UWorld> CachedPresenceWorld;
    mutable double LastPresenceRefresh = -100.0;
    bool EnsureLoaded();
    void RebuildIndexes();
    const FDigimonSocialAccountRecord* FindAccountById(const FString& Id) const;
    const FDigimonClanRecord* FindClanByMember(const FString& Id) const;
    bool Commit(FDigimonSocialDatabase&& Candidate, FString& OutError);
    bool WriteDatabase(const FDigimonSocialDatabase& Candidate, FString& OutError);
    static FString SavePath();
    static bool ValidateDatabase(const FDigimonSocialDatabase& Candidate);
    bool Authenticate(const ADigimonVenomNXTPlayerController* Controller, FString& OutId, FString& OutName) const;
    bool ResolveAccount(const FString& Query, FString& OutId, FString& OutName) const;
    void RefreshPresenceCache() const;
    void FillLivePlayerInfo(FDigimonSocialPlayerInfo& Out) const;
    FDigimonSocialContact MakeContact(const FString& AccountId) const;
};
