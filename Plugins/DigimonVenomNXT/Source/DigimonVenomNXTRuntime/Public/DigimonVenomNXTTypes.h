#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DigimonVenomNXTTypes.generated.h"

class UPaperFlipbook;
class UTexture2D;
class USoundBase;

UENUM(BlueprintType)
enum class EDigimonVariant : uint8
{
    // Append new varieties: these values are persisted in accounts, battles and rivals.
    Normal = 0 UMETA(DisplayName="Normal"),
    Paradox = 1 UMETA(DisplayName="Paradox"),
    Shiny = 2 UMETA(DisplayName="Shiny"),
    Firewall = 3 UMETA(DisplayName="Firewall")
};

/** Independently saved, owner-only campaign worlds. */
UENUM(BlueprintType)
enum class EDigimonPrivateCampaign : uint8
{
    // Append only: campaign IDs are persisted and sent in owner-only sessions.
    Relay = 0 UMETA(DisplayName="Dawn Relay Chronicle"),
    ParadoxChronicles = 1 UMETA(DisplayName="World DS: Paradox Chronicle"),
    GhostLine = 2 UMETA(DisplayName="Super Xros: Ghostline")
};

UENUM(BlueprintType)
enum class EDigimonStage : uint8
{
    Fresh,
    InTraining UMETA(DisplayName="In-Training"),
    Rookie,
    Champion,
    Ultimate,
    Mega,
    Ultra,
    ReservedStage,
    Unknown,
    Armor,
    Hybrid
};

/** Stable combat identities; variety is cosmetic and never changes a matchup. */
UENUM(BlueprintType)
enum class EDigimonAffinity : uint8
{
    Free = 0, Vaccine = 1, Virus = 2, Data = 3
};

UENUM(BlueprintType)
enum class EDigimonElement : uint8
{
    Neutral = 0, Fire = 1, Water = 2, Plant = 3, Electric = 4, Wind = 5, Earth = 6, Light = 7, Dark = 8
};

UENUM(BlueprintType)
enum class EDigimonDamageClass : uint8
{
    Physical = 0, Special = 1
};

UENUM(BlueprintType)
enum class EDigimonBattleKind : uint8
{
    Wild,
    AITamer,
    Season,
    Ranked,
    Story,
    Friendly,
};

UENUM(BlueprintType)
enum class EDigimonBattleAction : uint8
{
    Attack,
    Move1,
    Move2,
    Move3,
    Move4,
    Switch,
    Item,
    Retreat,
    Guard
};

UENUM(BlueprintType)
enum class EDigimonCurrency : uint8
{
    Credits,
    DigiRubies
};

UENUM(BlueprintType)
enum class EDigimonTrainingStat : uint8
{
    MaxHP,
    MaxSP,
    Attack,
    Defense,
    Spirit,
    Speed
};

UENUM(BlueprintType)
enum class EDigimonRankedGrade : uint8
{
    Bronze = 0, Silver = 1, Gold = 2, Platinum = 3, Diamond = 4, Master = 5
};

UENUM(BlueprintType)
enum class EDigimonRegion : uint8
{
    RegionOne,
    RegionTwo,
    RegionThree
};

UENUM(BlueprintType)
enum class EDigimonFacing : uint8
{
    Down,
    DownLeft,
    Left,
    UpLeft,
    Up,
    UpRight,
    Right,
    DownRight
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MaxHP = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MaxSP = 40;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Attack = 20;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defense = 20;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="INT / Sp. Atk & Sp. Def")) int32 Spirit = 20;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Speed = 20;

    FDigimonStats operator+(const FDigimonStats& Other) const
    {
        FDigimonStats Out;
        Out.MaxHP = MaxHP + Other.MaxHP;
        Out.MaxSP = MaxSP + Other.MaxSP;
        Out.Attack = Attack + Other.Attack;
        Out.Defense = Defense + Other.Defense;
        Out.Spirit = Spirit + Other.Spirit;
        Out.Speed = Speed + Other.Speed;
        return Out;
    }
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonEvolutionRequirement
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName TargetSpeciesId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredCAM = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredABI = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredAttack = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredDefense = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredSpirit = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredSpeed = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonMoveSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName MoveId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SPCost = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Power = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonDamageClass DamageClass = EDigimonDamageClass::Physical;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonElement Element = EDigimonElement::Neutral;
    /** Catalog metadata is resolved to the species when building a combat unit. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SPCostPerRank = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bUsesSpeciesElement = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAnimationRefs
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UPaperFlipbook> Idle;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UPaperFlipbook> WalkLeft;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UPaperFlipbook> WalkRight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UPaperFlipbook> Attack;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSpeciesDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SpeciesId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonStage Stage = EDigimonStage::Unknown;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonStats BaseStats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> LearnableMoves;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonEvolutionRequirement> Evolutions;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAnimationRefs NormalAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAnimationRefs ParadoxAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAnimationRefs ShinyAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAnimationRefs FirewallAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasNormalArtwork = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasParadoxArtwork = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasShinyArtwork = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasFirewallArtwork = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bPlaceholder = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonAffinity Affinity = EDigimonAffinity::Free;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonElement Element = EDigimonElement::Neutral;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CombatRole = TEXT("Balanced");
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonOwnedPartner
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGuid InstanceId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SpeciesId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonVariant Variant = EDigimonVariant::Normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Nickname;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Level = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 Experience = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CAM = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ABI = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonStats PermanentTraining;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CurrentHP = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CurrentSP = 40;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonMoveSlot> Moves;

    /** Zero identifies pre-rebalance saves and is migrated once, preserving vitality ratios. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CombatBalanceVersion = 0;

    FDigimonOwnedPartner()
    {
        // Training is an additive bonus, not another copy of the default base stats.
        PermanentTraining.MaxHP = PermanentTraining.MaxSP = 0;
        PermanentTraining.Attack = PermanentTraining.Defense = 0;
        PermanentTraining.Spirit = PermanentTraining.Speed = 0;
    }

    bool IsValid() const { return InstanceId.IsValid() && !SpeciesId.IsNone(); }
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonScanRecord
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SpeciesId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonVariant Variant = EDigimonVariant::Normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Percent = 0;
    /** Exact remainder for custom scan rates and the permanent 20% mastery bonus. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 FractionalHundredths = 0;
    /** Lifetime discovery survives spending scan and evolving away from this exact form. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 PeakPercent = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bEverOwned = false;
    /** Conversions recorded since DigiDex history was introduced; old saves start at zero. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Materializations = 0;
};

/** Live server rules; replicated to the owning client rather than saved in an account. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonScanPolicy
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) int32 MaterializeRequirementPercent = 100;
    UPROPERTY(BlueprintReadOnly) int32 ScanCapPercent = 200;
    UPROPERTY(BlueprintReadOnly) bool bConsumeScanOnMaterialize = true;
    UPROPERTY(BlueprintReadOnly) int32 MaxPartySize = 6;
    UPROPERTY(BlueprintReadOnly) int32 MaxFarmResidents = 100;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRankedCareer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rating = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonRankedGrade Grade = EDigimonRankedGrade::Bronze;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WeeklyWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WeeklyAttacks = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WeeklyLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WeeklyDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString WeeklySeasonId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FGuid> DefenderLineup;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> DefenderTeam;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Energy = 30;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 EnergyCap = 30;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 EnergyRechargeSeconds = 300;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 EnergyUpdatedUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 NextEnergyUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 SeasonEndsUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 ServerUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RewardPlacement = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<int32> GradeThresholds;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<int32> RewardGradeDigiRubies;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<int32> RewardPlacementDigiRubies;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MinimumRewardMatches = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LastOpponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LastResult;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LastRatingDelta = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LastBattleTurns = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastBattleUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> LastBattleLog;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> LastOpponentTeam;
    /** Applied on the same durable profile write as currency. Prevents duplicate claims after restart. */
    UPROPERTY() TArray<FString> ClaimedRewardIds;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonTamer
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString TamerId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName TamerStyleId = TEXT("tamer_002");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bPlayer = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> Team;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rating = 1200;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rank = 16;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Losses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Draws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Streak = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BestStreak = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Titles = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defenses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LastOpponentId;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonMatch
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString MatchId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString HomeTamerId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString AwayTamerId;
    /** Monday = 1, Sunday = 7. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DayOfWeek = 2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bPlayerMatch = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bTitleMatch = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bResolved = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bDraw = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString WinnerTamerId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Result;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonRivalry
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString TamerAId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString TamerBId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Heat = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Meetings = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 AWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Draws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LastWeek = 1;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonReign
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString HolderId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString HolderName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ReignNumber = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 StartWeek = 1;
    /** Zero means the reigning champion. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 EndWeek = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defenses = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonPayout
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString PayoutId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Reason;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Week = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 Credits = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonArchive
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CareerId;
    /** Archived standings omit live party data to keep history compact. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonTamer> Standings;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Week = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EventName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonMatch> Matches;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ChampionId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionReign = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionDefenses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionSinceWeek = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonPayout> Payouts;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 PlayerRank = 16;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 PlayerRating = 1200;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 CreditsEarned = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonArchivePage
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString CareerId;
    UPROPERTY(BlueprintReadOnly) int32 PageIndex = 0;
    UPROPERTY(BlueprintReadOnly) int32 PageSize = 8;
    UPROPERTY(BlueprintReadOnly) int32 TotalRecords = 0;
    UPROPERTY(BlueprintReadOnly) bool bHasMore = false;
    UPROPERTY(BlueprintReadOnly) bool bSuccess = false;
    UPROPERTY(BlueprintReadOnly) FString Error;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonSeasonArchive> Records;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonSeasonCareer
{
    GENERATED_BODY()
    // Legacy fields intentionally retained: existing saves migrate without losing their totals.
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Week = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Losses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Championships = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CurrentRivalId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bScheduledBattleComplete = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 FirstArchiveWeek = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 OpponentLevel = 5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 MonthRewardEstimate = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 YearRewardEstimate = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DefenseRewardInterval = 3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DefenseRewardCredits = 1500;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Version = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CareerId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Seed = 0;
    /** Calendar offset inside the booking week: Monday=0, Tuesday=1, results Sunday=6. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DayOffset = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EventName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bChampionshipWeek = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bAnnualEvent = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonTamer> Roster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonMatch> CurrentCard;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonRivalry> Rivalries;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ChampionId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionSinceWeek = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionReign = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionDefenses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonReign> Reigns;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> News;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonArchive> Archive;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonSeasonPayout> Payouts;
    /** Saved next decision, including queued commands and exact HP/SP; only the account owner receives this profile. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString BattleCheckpointJson;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString PendingContextId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LastSettledContextId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Draws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MonthWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MonthLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MonthDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 YearWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 YearLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 YearDraws = 0;
    /** Monotonic period fences protect exactly-once payouts independently of bounded history. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastPaidMonth = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastPaidYear = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 TotalCreditsEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 TotalExperienceEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 WeekCreditsEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastMatchCredits = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastMatchXP = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonStoryProgress
{
    GENERATED_BODY()

    /** 1 is the hub. Chapters 2-18 each contain a Paradox boss. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Chapter = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<int32> DefeatedBossChapters;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ParadoxBadges = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bFinalEncounterUnlocked = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bFinalEncounterComplete = false;
};

/** Independent journey save, used separately by each private campaign. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRelayProgress
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Version = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bInside = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 UnlockedMapId = 2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D Position = FVector2D::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasPosition = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ReturnMapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector ReturnLocation = FVector::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasReturnLocation = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> CompletedObjectives;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> DefeatedTamers;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> Badges;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bEverChampion = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsChampion = false;
    /** Permanent World DS: Paradox Chronicle reward. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bParadoxScanMastery = false;
    /** Permanent Super Xros: Ghostline reward. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bShinyScanMastery = false;
    /** Permanent Dawn Relay Chronicle reward. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bFirewallScanMastery = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bComplete = false;
    /** Accepted quests persist independently from completed turn-ins. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> AcceptedQuests;
    // Quest objective progress is derived from DefeatedTamers. Keep this shared
    // profile/RPC structure free of unsupported replicated TMap properties.
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChampionshipWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defenses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TitleLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChallengerIndex = 0;
    /** Receipt fence and persisted in-flight attempt retain disconnect decisions without free resets. */
    UPROPERTY() FGuid LastSettledBattleId;
    UPROPERTY() FGuid PendingBattleId;
    UPROPERTY() FName PendingNPCId = NAME_None;
    /** Host-authored exact next decision; owner-only through Profile replication. */
    UPROPERTY() FString BattleCheckpointJson;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonInventoryEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ItemId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Quantity = 0;
};

/** One private home belongs to this profile's account; no client-provided owner or visit target. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonFarmState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Version = 1;
    /** False in legacy profiles; newly created accounts are explicitly placed at home. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bInside = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D Position = FVector2D::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasPosition = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ReturnMapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector ReturnLocation = FVector::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasReturnLocation = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonPlayerProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString AccountId;
    /** Authoritative recovery generation fences older owner-profile snapshots in DigiLab. */
    UPROPERTY(BlueprintReadOnly) int64 DigiLabRecoveryRevision = 0;
    /** Durable commerce generation rejects stale profile writes after a transfer. */
    UPROPERTY(BlueprintReadOnly) int64 CommerceRevision = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Username;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> OwnedTitles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EquippedTitle;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName TamerStyleId = TEXT("tamer_002");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 Credits = 2500;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DigiRubies = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedWins = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedLosses = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CurrentMapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> Collection;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FGuid> Party;
    /** One-time original-starter correction; prevents later evolution resets being raised. */
    UPROPERTY() int32 StarterBalanceVersion = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FGuid> DigiFarmResidents;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonFarmState Farm;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonScanRecord> Scans;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonInventoryEntry> Inventory;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonRankedCareer Ranked;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonSeasonCareer Season;
    /** Host-owned suspended public wild encounter, committed with earned defeat scans. */
    UPROPERTY() FString WorldBattleCheckpointJson;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonStoryProgress Story;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonRelayProgress Relay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonRelayProgress Chronicles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonRelayProgress GhostLine;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonPrivateCampaign ActiveStoryCampaign = EDigimonPrivateCampaign::Relay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastSavedUnix = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonPublicPlayerSnapshot
{
    GENERATED_BODY()

    /** Public identifier only; authentication secrets remain server-only. */
    UPROPERTY(BlueprintReadOnly) FString AccountId;
    UPROPERTY(BlueprintReadOnly) FString Username;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedWins = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedLosses = 0;
    UPROPERTY(BlueprintReadOnly) int32 UnrankedDraws = 0;
    UPROPERTY(BlueprintReadOnly) FString EquippedTitle;
    UPROPERTY(BlueprintReadOnly) FName TamerStyleId = TEXT("tamer_002");
    UPROPERTY(BlueprintReadOnly) int32 MapId = 1;
    /** Only presence is public. Farm positions, resident IDs and owner data remain owner-only. */
    UPROPERTY(BlueprintReadOnly) bool bInDigiFarm = false;
    UPROPERTY(BlueprintReadOnly) bool bInRelay = false;
    UPROPERTY(BlueprintReadOnly) FName LeadSpeciesId = NAME_None;
    UPROPERTY(BlueprintReadOnly) EDigimonVariant LeadVariant = EDigimonVariant::Normal;
    UPROPERTY(BlueprintReadOnly) int32 LeadLevel = 1;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonBattleUnit
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FGuid InstanceId;
    UPROPERTY(BlueprintReadWrite) FName SpeciesId = NAME_None;
    UPROPERTY(BlueprintReadWrite) FString DisplayName;
    UPROPERTY(BlueprintReadWrite) EDigimonVariant Variant = EDigimonVariant::Normal;
    UPROPERTY(BlueprintReadWrite) int32 Level = 1;
    UPROPERTY(BlueprintReadWrite) FDigimonStats Stats;
    UPROPERTY(BlueprintReadWrite) int32 HP = 100;
    UPROPERTY(BlueprintReadWrite) int32 SP = 40;
    UPROPERTY(BlueprintReadWrite) TArray<FDigimonMoveSlot> Moves;
    UPROPERTY(BlueprintReadWrite) bool bDefeated = false;
    UPROPERTY(BlueprintReadWrite) EDigimonAffinity Affinity = EDigimonAffinity::Free;
    UPROPERTY(BlueprintReadWrite) EDigimonElement Element = EDigimonElement::Neutral;
    UPROPERTY(BlueprintReadWrite) int32 CombatBalanceVersion = 0;
    UPROPERTY(BlueprintReadWrite) int32 CAM = 0;
    UPROPERTY(BlueprintReadWrite) int32 ABI = 0;
    UPROPERTY(BlueprintReadWrite) bool bGuarding = false;
    UPROPERTY(BlueprintReadWrite) double NextActionTime = 0.0;
    UPROPERTY(BlueprintReadWrite) int32 TimelineOrder = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonBattleTeam
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FString TrainerName;
    UPROPERTY(BlueprintReadWrite) TArray<FDigimonBattleUnit> Active;
    UPROPERTY(BlueprintReadWrite) TArray<FDigimonBattleUnit> Bench;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonBattlePresentationEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) int32 TurnNumber = 0;
    UPROPERTY(BlueprintReadOnly) int32 ActingTeam = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) int32 ActingSlot = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) int32 TargetTeam = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) int32 TargetSlot = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) EDigimonBattleAction Action = EDigimonBattleAction::Attack;
    UPROPERTY(BlueprintReadOnly) int32 Damage = 0;
    UPROPERTY(BlueprintReadOnly) FString Text;
    /** Exact post-action state, applied by presentation only when the attack lands. */
    UPROPERTY(BlueprintReadOnly) bool bHasPostState = false;
    UPROPERTY(BlueprintReadOnly) FDigimonBattleTeam PostTeamA;
    UPROPERTY(BlueprintReadOnly) FDigimonBattleTeam PostTeamB;
    UPROPERTY(BlueprintReadOnly) FGuid ActingInstanceId;
    UPROPERTY(BlueprintReadOnly) FGuid TargetInstanceId;
    UPROPERTY(BlueprintReadOnly) float Effectiveness = 1.0f;
    UPROPERTY(BlueprintReadOnly) float ComboMultiplier = 1.0f;
    UPROPERTY(BlueprintReadOnly) bool bGuarded = false;
    UPROPERTY(BlueprintReadOnly) float TypeMultiplier = 1.0f;
    UPROPERTY(BlueprintReadOnly) float ElementMultiplier = 1.0f;
    UPROPERTY(BlueprintReadOnly) EDigimonDamageClass DamageClass = EDigimonDamageClass::Physical;
    UPROPERTY(BlueprintReadOnly) EDigimonElement Element = EDigimonElement::Neutral;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonWildScanMasteryPending
{
    GENERATED_BODY()
    UPROPERTY() FGuid InstanceId;
    UPROPERTY() int32 Hundredths = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonBattleState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) FGuid BattleId;
    UPROPERTY(BlueprintReadOnly) EDigimonBattleKind Kind = EDigimonBattleKind::Wild;
    UPROPERTY(BlueprintReadOnly) bool bAutomatic = false;
    UPROPERTY(BlueprintReadOnly) FDigimonBattleTeam TeamA;
    UPROPERTY(BlueprintReadOnly) FDigimonBattleTeam TeamB;
    UPROPERTY(BlueprintReadOnly) int32 TurnNumber = 1;
    UPROPERTY(BlueprintReadOnly) int32 ActingTeam = 0;
    UPROPERTY(BlueprintReadOnly) bool bFinished = false;
    UPROPERTY(BlueprintReadOnly) int32 WinningTeam = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) FString LastEvent;
    /** All visual actions resolved in the last server round, replayed client-side for polished movement/hit feedback. */
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonBattlePresentationEvent> PresentationEvents;
    /** Authoritative queued slots for every manual mode; saved Season decisions also restore these after reconnect. */
    UPROPERTY(BlueprintReadOnly) TArray<int32> ReadySlotsA;
    UPROPERTY(BlueprintReadOnly) TArray<int32> ReadySlotsB;
    UPROPERTY(BlueprintReadOnly) int32 PresentationSerial = 0;
    /** A successful wild withdrawal has no winning team and grants no battle rewards. */
    UPROPERTY(BlueprintReadOnly) bool bFled = false;
    UPROPERTY(BlueprintReadOnly) double BattleClock = 0.0;
    UPROPERTY(BlueprintReadOnly) int32 ActingSlot = INDEX_NONE;
    UPROPERTY(BlueprintReadOnly) int32 CombatBalanceVersion = 0;
    /** Opening formation size keeps reward pacing independent of reserves and CTB extra turns. */
    UPROPERTY(BlueprintReadOnly) int32 InitialActiveCount = 0;
    /** Defeat scans and their encounter identity persist together, preventing duplicate awards on resume. */
    UPROPERTY() TArray<FGuid> ScannedWildInstances;
    UPROPERTY() TArray<FDigimonWildScanMasteryPending> WildMasteryHundredths;
    UPROPERTY() bool bWildMasteryPaid = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonBattleCommand
{
    GENERATED_BODY()

    /** Every manual mode rejects commands generated for another battle or an earlier turn. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGuid ExpectedBattleId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ExpectedTurnNumber = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonBattleAction Action = EDigimonBattleAction::Attack;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ActingSlot = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TargetSlot = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SwitchBenchIndex = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ItemId = NAME_None;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonMapRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonRegion Region = EDigimonRegion::RegionOne;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RecommendedMinLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RecommendedMaxLevel = 3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UTexture2D> GroundTexture;
    /** Real playable level art. Collision-mask sources are never exposed through this field. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SourceImageRelativePath;
    /** Hidden source mask used only to build/query walkability. Never rendered or shown in Atlas. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CollisionSourceImageRelativePath;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bCollisionDerivedFromGround = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SourceWidth = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SourceHeight = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WalkGridWidth = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WalkGridHeight = 0;
    /** Packed row-major walkability bits. One means the tamer may stand in this cell. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> WalkGridBits;
    /** Normalized source-image coordinate chosen from the collision data as a safe spawn point. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D SafeSpawnUV = FVector2D(0.5f, 0.5f);
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<USoundBase> ExplorationMusic;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<USoundBase> BattleMusic;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> WildSpecies;
    /** Independent source habitat pools; a rare encounter can replace the normal species. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ParadoxSpecies;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ShinySpecies;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> FirewallSpecies;
};

/** Event counters, reset only at the UTC 00:00 / 12:00 window boundary. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalActivityCounters
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WildBattles = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WildWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WildLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 WildDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainerBattles = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainerWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainerLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainerDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RankedBattles = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RankedWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RankedLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RankedDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ScanGained = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Materializations = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LevelUps = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Evolutions = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DeEvolutions = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ABIGained = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CAMGained = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MapTravels = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Heals = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainingActions = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ItemsPurchased = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 CreditsEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 CreditsSpent = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 ExperienceGained = 0;

    void Add(const FDigimonAIRivalActivityCounters& Other)
    {
        WildBattles += Other.WildBattles;
        WildWins += Other.WildWins;
        WildLosses += Other.WildLosses;
        WildDraws += Other.WildDraws;
        TrainerBattles += Other.TrainerBattles;
        TrainerWins += Other.TrainerWins;
        TrainerLosses += Other.TrainerLosses;
        TrainerDraws += Other.TrainerDraws;
        RankedBattles += Other.RankedBattles;
        RankedWins += Other.RankedWins;
        RankedLosses += Other.RankedLosses;
        RankedDraws += Other.RankedDraws;
        ScanGained += Other.ScanGained;
        Materializations += Other.Materializations;
        LevelUps += Other.LevelUps;
        Evolutions += Other.Evolutions;
        DeEvolutions += Other.DeEvolutions;
        ABIGained += Other.ABIGained;
        CAMGained += Other.CAMGained;
        MapTravels += Other.MapTravels;
        Heals += Other.Heals;
        TrainingActions += Other.TrainingActions;
        ItemsPurchased += Other.ItemsPurchased;
        CreditsEarned += Other.CreditsEarned;
        CreditsSpent += Other.CreditsSpent;
        ExperienceGained += Other.ExperienceGained;
    }
};

USTRUCT()
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalTrainingHistory
{
    GENERATED_BODY()
    UPROPERTY() FGuid InstanceId;
    UPROPERTY() int64 LastLedSession = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalRecord
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString RivalId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TamerLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Losses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 Credits = 1000;
    /** Selected party snapshot; kept for compatibility with battles and existing saves. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> Partners;
    /** Persistent ownership. Party snapshots are synchronized after every activity. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> Collection;
    UPROPERTY() int32 StarterBalanceVersion = 0;
    UPROPERTY() TArray<FDigimonAIRivalTrainingHistory> TrainingHistory;
    UPROPERTY() FGuid TrainingLeaderId;
    UPROPERTY() int64 TrainingSessionSerial = 0;
    UPROPERTY() int32 TrainingSessionBattles = 0;
    UPROPERTY() int32 TrainingSessionStartLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonScanRecord> Scans;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonInventoryEntry> Inventory;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastSimulatedUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 NextActionUnix = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ConsecutiveWildLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ConsecutiveWildWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ExplorationTargetLevel = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CurrentActivity = TEXT("Preparing expedition");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAIRivalActivityCounters WindowStats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDigimonAIRivalActivityCounters LifetimeStats;
};

/** Bounded, public projection: never replicates collections or inventories. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalActivityRow
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) FString RivalId;
    UPROPERTY(BlueprintReadOnly) FString DisplayName;
    UPROPERTY(BlueprintReadOnly) int32 MapId = 1;
    UPROPERTY(BlueprintReadOnly) int32 TamerLevel = 1;
    UPROPERTY(BlueprintReadOnly) int32 PartySize = 0;
    UPROPERTY(BlueprintReadOnly) int32 CollectionSize = 0;
    UPROPERTY(BlueprintReadOnly) FString CurrentActivity;
    UPROPERTY(BlueprintReadOnly) int64 LastSimulatedUnix = 0;
    UPROPERTY(BlueprintReadOnly) FDigimonAIRivalActivityCounters Stats;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalActivityPage
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) int64 WindowStartUnix = 0;
    UPROPERTY(BlueprintReadOnly) int64 WindowEndUnix = 0;
    UPROPERTY(BlueprintReadOnly) int64 ServerUnix = 0;
    UPROPERTY(BlueprintReadOnly) int32 PageIndex = 0;
    UPROPERTY(BlueprintReadOnly) int32 PageSize = 20;
    UPROPERTY(BlueprintReadOnly) int32 TotalRivals = 0;
    UPROPERTY(BlueprintReadOnly) int32 TotalPages = 0;
    UPROPERTY(BlueprintReadOnly) FDigimonAIRivalActivityCounters Totals;
    UPROPERTY(BlueprintReadOnly) TArray<FDigimonAIRivalActivityRow> Rows;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonShopItemDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ItemId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 CreditCost = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DigiRubyCost = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Resource = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Amount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Category = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HPHeal = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SPHeal = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CAMGain = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TrainingGain = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bABIMeat = false;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRankedLadderEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rank = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString AccountId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Username;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rating = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 AchievedGrade = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SeasonAttacks = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Losses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Draws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerWins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerLosses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CareerDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDigimonOwnedPartner> DefenderTeam;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bAIRival = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString RivalId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TeamPower = 0;
    UPROPERTY() int32 RivalRatingOffset = 0;
    /** Canonical energy lives with the result ledger, so reconnecting cannot restore spent energy. */
    UPROPERTY() bool bEnergyInitialized = false;
    UPROPERTY() int32 Energy = 30;
    UPROPERTY() int64 EnergyUpdatedUnix = 0;
    UPROPERTY() FString LastOpponent;
    UPROPERTY() FString LastResult;
    UPROPERTY() int32 LastRatingDelta = 0;
    UPROPERTY() int32 LastBattleTurns = 0;
    UPROPERTY() int64 LastBattleUnix = 0;
    UPROPERTY() TArray<FString> LastBattleLog;
    UPROPERTY() TArray<FDigimonOwnedPartner> LastOpponentTeam;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAuthResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) bool bSuccess = false;
    UPROPERTY(BlueprintReadOnly) FString Message;
    UPROPERTY(BlueprintReadOnly) FString Username;
    UPROPERTY(BlueprintReadOnly) FString AccountId;
};

UENUM(BlueprintType)
enum class EDigimonChatMessageKind : uint8
{
    Player,
    PlayerJoined,
    PlayerLeft
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonChatMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) EDigimonChatMessageKind Kind = EDigimonChatMessageKind::Player;
    UPROPERTY(BlueprintReadOnly) FString SenderAccountId;
    UPROPERTY(BlueprintReadOnly) FString Sender;
    UPROPERTY(BlueprintReadOnly) FString Message;
    UPROPERTY(BlueprintReadOnly) int64 UnixTime = 0;
};

USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAssetInventoryEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SourcePath;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString AssetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SpeciesId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Variant;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Stage;
};


USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRankedPublicEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rank = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Username;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rating = 1000;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDigimonRankedGrade Grade = EDigimonRankedGrade::Bronze;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Losses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Draws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bAIRival = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TeamPower = 0;
};

USTRUCT()
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRankedReward
{
    GENERATED_BODY()
    UPROPERTY() FString RewardId;
    UPROPERTY() FString AccountId;
    UPROPERTY() FString SeasonId;
    UPROPERTY() int32 Placement = 0;
    UPROPERTY() int32 DigiRubies = 0;
};

USTRUCT()
struct DIGIMONVENOMNXTRUNTIME_API FDigimonRankedSaveData
{
    GENERATED_BODY()

    UPROPERTY() int32 SchemaVersion = 2;
    UPROPERTY() FString SeasonId;
    UPROPERTY() int64 SeasonStartsUnix = 0;
    UPROPERTY() int64 SeasonEndsUnix = 0;
    UPROPERTY() TArray<FDigimonRankedLadderEntry> Entries;
    /** Legacy v1 balance map, converted to tokenized rewards exactly once on load. */
    UPROPERTY() TMap<FString, int32> PendingRubyRewards;
    UPROPERTY() TArray<FDigimonRankedReward> PendingRewards;
};

USTRUCT()
struct DIGIMONVENOMNXTRUNTIME_API FDigimonAIRivalSaveData
{
    GENERATED_BODY()

    UPROPERTY() int32 SchemaVersion = 3;
    UPROPERTY() TArray<FDigimonAIRivalRecord> Rivals;
    UPROPERTY() int64 ActivityWindowStartUnix = 0;
    UPROPERTY() int64 LastSavedUnix = 0;
};
