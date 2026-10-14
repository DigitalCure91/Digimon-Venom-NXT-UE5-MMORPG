#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTSocialTypes.generated.h"

UENUM(BlueprintType)
enum class EDigimonClanRole : uint8 { None, Member, Officer, Leader };

/** Target is an account username/ID unless documented otherwise in SocialComponent. */
UENUM(BlueprintType)
enum class EDigimonSocialAction : uint8
{
    FriendRequest, FriendAccept, FriendDecline, FriendRemove, FriendCancel,
    IgnoreAdd, IgnoreRemove,
    ClanCreate, ClanDisband, ClanInvite, ClanAccept, ClanDecline, ClanLeave,
    ClanKick, ClanPromote, ClanDemote, ClanTransfer, ClanUpdate
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSocialContact
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString AccountId;
    UPROPERTY(BlueprintReadOnly) FString Username;
    UPROPERTY(BlueprintReadOnly) bool bOnline = false;
    UPROPERTY(BlueprintReadOnly) FString Location = TEXT("Offline");
    UPROPERTY(BlueprintReadOnly) int32 LeadLevel = 0;
    UPROPERTY(BlueprintReadOnly) FName LeadSpeciesId;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonClanMemberView
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FDigimonSocialContact Player;
    UPROPERTY(BlueprintReadOnly) EDigimonClanRole Role = EDigimonClanRole::Member;
    UPROPERTY(BlueprintReadOnly) int64 JoinedUnix = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonClanInviteView
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString ClanId;
    UPROPERTY(BlueprintReadOnly) FString ClanName;
    UPROPERTY(BlueprintReadOnly) FString InviterName;
    UPROPERTY(BlueprintReadOnly) int64 ExpiresUnix = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonClanView
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString ClanId;
    UPROPERTY(BlueprintReadOnly) FString Name;
    UPROPERTY(BlueprintReadOnly) FString Tag;
    UPROPERTY(BlueprintReadOnly) FString Description;
    UPROPERTY(BlueprintReadOnly) FString MessageOfTheDay;
    UPROPERTY(BlueprintReadOnly) EDigimonClanRole YourRole = EDigimonClanRole::None;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonClanMemberView> Members;
};

/** Explicitly public information; never a copy of another account's private profile. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSocialPlayerInfo
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) bool bValid = false;
    UPROPERTY(BlueprintReadOnly) FDigimonSocialContact Player;
    UPROPERTY(BlueprintReadOnly) FString EquippedTitle;
    UPROPERTY(BlueprintReadOnly) bool bUnrankedStatsAvailable = false;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedWins = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedLosses = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedDraws = 0;
    UPROPERTY(BlueprintReadOnly) FString ClanName;
    UPROPERTY(BlueprintReadOnly) FString ClanTag;
    UPROPERTY(BlueprintReadOnly) EDigimonClanRole ClanRole = EDigimonClanRole::None;
    UPROPERTY(BlueprintReadOnly) bool bFriend = false;
    UPROPERTY(BlueprintReadOnly) bool bIgnored = false;
    UPROPERTY(BlueprintReadOnly) bool bIncomingRequest = false;
    UPROPERTY(BlueprintReadOnly) bool bOutgoingRequest = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSocialState
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) bool bReady = false;
    UPROPERTY(BlueprintReadOnly) int64 Revision = 0;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonSocialContact> Friends;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonSocialContact> Ignored;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonSocialContact> IncomingFriends;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonSocialContact> OutgoingFriends;
    UPROPERTY(BlueprintReadOnly) FDigimonClanView Clan;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonClanInviteView> ClanInvites;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonChatMessage> ClanChat;
    UPROPERTY(BlueprintReadOnly) FDigimonSocialPlayerInfo PlayerInfo;
};

// Durable server records. These are never replicated directly to clients.
USTRUCT()
struct FDigimonSocialAccountRecord
{
    GENERATED_BODY()
    UPROPERTY() FString AccountId;
    UPROPERTY() FString Username;
    UPROPERTY() TArray<FString> Friends;
    UPROPERTY() TArray<FString> Ignored;
    UPROPERTY() TArray<FString> IncomingFriends;
    UPROPERTY() TArray<FString> OutgoingFriends;
};

USTRUCT()
struct FDigimonClanMemberRecord
{
    GENERATED_BODY()
    UPROPERTY() FString AccountId;
    UPROPERTY() EDigimonClanRole Role = EDigimonClanRole::Member;
    UPROPERTY() int64 JoinedUnix = 0;
};

USTRUCT()
struct FDigimonClanInvitationRecord
{
    GENERATED_BODY()
    UPROPERTY() FString AccountId;
    UPROPERTY() FString InviterAccountId;
    UPROPERTY() int64 ExpiresUnix = 0;
};

USTRUCT()
struct FDigimonClanRecord
{
    GENERATED_BODY()
    UPROPERTY() FString ClanId;
    UPROPERTY() FString Name;
    UPROPERTY() FString Tag;
    UPROPERTY() FString Description;
    UPROPERTY() FString MessageOfTheDay;
    UPROPERTY() TArray<FDigimonClanMemberRecord> Members;
    UPROPERTY() TArray<FDigimonClanInvitationRecord> Invitations;
};

USTRUCT()
struct FDigimonSocialDatabase
{
    GENERATED_BODY()
    UPROPERTY() int32 SchemaVersion = 1;
    UPROPERTY() int64 Revision = 0;
    UPROPERTY() TArray<FDigimonSocialAccountRecord> Accounts;
    UPROPERTY() TArray<FDigimonClanRecord> Clans;
};
