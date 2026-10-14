#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"

/** Fixed first-campaign content; no player-authored opponents or progression. */
enum class EDigimonRelayRole : uint8 { Guide, Healer, Shop, Tamer, Gym, Champion, Challenger, Quest, ParadoxBoss, FinalBoss, Lab, Farm };

struct DIGIMONVENOMNXTRUNTIME_API FDigimonRelayMap
{
    int32 MapId = 1;
    int32 SourceMapId = 1;
    int32 RegionIndex = 0;
    FString Name, Subtitle, Intro, Objective;
    int32 MinLevel = 1, MaxLevel = 10;
    FVector2D EntryPosition = FVector2D(.45, .48);
    FVector2D ExitPosition = FVector2D(.7, .5);
    FVector2D ArrivalPosition = FVector2D(.5, .5);
    TArray<FName> RequiredBadges;
    FName BadgeId = NAME_None;
    bool bPeaceful = false;
};
struct FDigimonCampaignDialogueVariant
{
    TArray<FName> Branches, RequiresCompleted, RequiresHacked;
    int32 RequiresReveal = -1, RequiresComplete = -1;
    FString Text;
};
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRelayNPC
{
    FName Id = NAME_None;
    int32 MapId = 1;
    FString Name;
    FName TamerStyleId = TEXT("tamer_002");
    EDigimonRelayRole Role = EDigimonRelayRole::Guide;
    FString Dialogue, AfterDialogue, LostDialogue;
    FName Prerequisite = NAME_None;
    FName BadgeId = NAME_None;
    FString BadgeName;
    int32 Level = 1, TeamSize = 1;
    /** Desired UV; private scene projects this to a reachable collision cell. */
    FVector2D Position = FVector2D(.5, .5);
    TArray<FName> TeamSpecies;
    TArray<int32> TeamLevels;
    /** Empty means Normal; Paradox bosses explicitly use Paradox for every slot. */
    TArray<EDigimonVariant> TeamVariants;
    /** Quest giver, required quest, or battle objective according to role. */
    FName QuestId = NAME_None;
    int32 QuestTarget = 0;
    int64 Credits = 0;
    FName RewardPartner = NAME_None;
    int32 RewardPartnerLevel = 1;
    /** First-clear earned XP milestone; never lowers an existing partner. */
    int32 TrainingLevel = 1;
    TArray<FName> RequiresCompleted, RequiresAccepted, RequiresBadges, RequiresHacked, QuestRequires;
    TMap<FName, FString> DialogueBranches;
    TArray<FDigimonCampaignDialogueVariant> DialogueVariants;
    TMap<FName, int32> RewardItems;
    FString QuestTitle, RoleLabel, CharacterId;
    bool bRepeatable = false, bHideOnReveal = false, bShowRequiresReveal = false;
    bool bHideOnComplete = false, bRevealOnComplete = false, bHackedAfterVictory = false;
    bool bMentor = false;
    int32 RequiresReveal = -1;
    EDigimonVariant RewardPartnerVariant = EDigimonVariant::Normal;
};
namespace DigimonVenomNXTRelay
{
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayMap>& Maps();
    DIGIMONVENOMNXTRUNTIME_API const TArray<FDigimonRelayNPC>& NPCs();
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayMap* GetMap(int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayNPC* GetNPC(FName Id);
    DIGIMONVENOMNXTRUNTIME_API TArray<FDigimonRelayNPC> NPCsForMap(int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonRelayNPC* CurrentChallenger(const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool IsBattleRole(EDigimonRelayRole Role);
    DIGIMONVENOMNXTRUNTIME_API bool CanEnterMap(const FDigimonRelayProgress& Progress, int32 MapId);
    DIGIMONVENOMNXTRUNTIME_API bool CanChallenge(const FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API bool Interact(FDigimonRelayProgress& Progress, const FDigimonRelayNPC& NPC, FString& Dialogue, FString& Error);
    DIGIMONVENOMNXTRUNTIME_API FString Objective(const FDigimonRelayProgress& Progress);
    DIGIMONVENOMNXTRUNTIME_API bool Reconcile(FDigimonRelayProgress& Progress);
    /** Server settlement in a copied profile; callers persist before publishing. */
    DIGIMONVENOMNXTRUNTIME_API bool Settle(FDigimonRelayProgress& Progress, FGuid BattleId, FName NPCId, bool bVictory, bool& bFirstClear);
}
