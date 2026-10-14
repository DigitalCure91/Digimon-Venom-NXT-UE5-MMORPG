#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DigimonVenomNXTSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Digimon Venom NXT"))
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTSettings : public UDeveloperSettings
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTSettings();

    /** Defaults for new local players. In-game mixer changes are saved on that device. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(ClampMin="0.0", ClampMax="1.0"))
    float DefaultMasterVolume = 1.0f;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(ClampMin="0.0", ClampMax="1.0"))
    float DefaultMusicVolume = 1.0f;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(ClampMin="0.0", ClampMax="1.0"))
    float DefaultEffectsVolume = 0.85f;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(ClampMin="0.0", ClampMax="1.0"))
    float DefaultUIVolume = 0.75f;
    /** Optional per-cue assets: Heal, UIClick, PhysicalAttack, etc. Leave empty to use supplied SFX. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(AllowedClasses="/Script/Engine.SoundBase"))
    TMap<FName, FSoftObjectPath> SoundEffectOverrides;

    virtual FName GetCategoryName() const override { return TEXT("Game"); }
    virtual FName GetSectionName() const override { return TEXT("DigimonVenomNXT"); }

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Startup")
    FSoftObjectPath MainMenuMap;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Startup")
    FSoftObjectPath PublicWorldMap;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Multiplayer|Public Server")
    FString ServerDisplayName = TEXT("Digimon Venom NXT Public World");

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Multiplayer|Public Server", meta=(ToolTip="IP, domain, or subdomain players use to reach the public game. There is intentionally no join password."))
    FString PublicGameAddress = TEXT("127.0.0.1");

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Multiplayer|Public Server", meta=(ClampMin="1", ClampMax="65535"))
    int32 GameplayPort = 7777;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Multiplayer|Public Server", meta=(ClampMin="1", ClampMax="5000"))
    int32 MaxPlayers = 100;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Multiplayer|Hosting", meta=(PasswordField="true", ToolTip="Local editor hosting credential. Leave blank in distributable config. Production hosting uses DIGIMONVENOMNXT_HOST_PASSWORD or Saved/DigimonVenomNXT/Host.ini. This is not a joining password."))
    FString AdminHostPassword;

    /** Server-local environment/file override, never replicated. Do not log the returned value. */
    FString ResolveAdminHostPassword() const;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Accounts", meta=(ToolTip="Password hashing work factor for the host-owned Unreal SaveGame account database.", ClampMin="10000", ClampMax="500000"))
    int32 PasswordHashIterations = 120000;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party", meta=(ClampMin="1", ClampMax="12"))
    int32 MaxPartySize = 6;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party", meta=(ClampMin="1", ClampMax="6"))
    int32 ActiveBattleSize = 3;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party", meta=(ClampMin="1", ClampMax="200"))
    int32 MaxPartnerLevel = 99;

    /** Initial level for a player's first partner and the minimum for newly seeded AI starters. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party", meta=(ClampMin="1", ClampMax="200"))
    int32 StarterLevel = 1;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Collection", meta=(ClampMin="1"))
    int32 NormalSpeciesCapacity = 502;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Collection", meta=(ClampMin="100", ClampMax="999"))
    int32 ScanCapPercent = 200;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Collection", meta=(ClampMin="1", ClampMax="200"))
    int32 MaterializeRequirementPercent = 100;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Collection")
    bool bConsumeScanOnMaterialize = true;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Wild Encounters", meta=(ClampMin="0.0", ClampMax="1.0"))
    float ParadoxChance = 0.025f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Wild Encounters", meta=(ClampMin="0.0", ClampMax="1.0"))
    float ShinyChance = 0.01f;

    /** The global Firewall rate for public fields, private campaign training and AI rivals. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Wild Encounters", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0", DisplayName="Firewall Encounter Chance", ToolTip="0.007 = 0.7% of wild encounters, 0 disables, 1 = 100% when other variety chances are zero. Each encounter uses one roll: Shiny, Paradox, Firewall, then Normal. If rare chances total more than 100%, they are reduced proportionally. Unavailable artwork falls back to Normal without increasing other rare rates. Wild Firewall defeats grant 5 scan points by default; completing Dawn Relay grants a 20% mastery bonus on a qualifying victory (6 total), up to the scan cap."))
    float FirewallChance = 0.007f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Wild Encounters", meta=(ClampMin="1", ClampMax="100", ToolTip="Base scan points per defeated normal wild Digimon. RareScanGain controls variants; campaign mastery applies after a qualifying victory."))
    int32 BaseScanGain = 20;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Wild Encounters", meta=(ClampMin="0", ClampMax="100", ToolTip="Base scan points per defeated Shiny, Paradox or Firewall wild Digimon before campaign mastery."))
    int32 RareScanGain = 5;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Progression", meta=(ClampMin="0.0", ClampMax="100.0", ToolTip="Global multiplier for newly awarded battle experience; 1 uses source game rates."))
    float ExperienceRate = 1.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(ClampMin="0.0", ClampMax="100.0", ToolTip="Global multiplier for newly awarded battle money; 1 uses source game rates."))
    float MoneyRewardRate = 1.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="1", ClampMax="1000"))
    int32 PublicAtlasMapCount = 500;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="1", ClampMax="16"))
    int32 RegionCount = 4;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="1", ClampMax="5000"))
    int32 MaxPersistentAIRivals = 1000;

    /** Server work budget. Existing records are retained if the active population is reduced. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="0.25", ClampMax="30.0"))
    float AIRivalSimulationIntervalSeconds = 1.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="1", ClampMax="100"))
    int32 AIRivalRecordsPerStep = 40;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="5", ClampMax="3600"))
    int32 AIRivalActionIntervalSeconds = 30;

    /** Wall-clock budget for each simulation batch; cursor resumes on the next tick. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="0.5", ClampMax="20.0"))
    float AIRivalSimulationBudgetMilliseconds = 4.0f;

    /** Unique species/variant materializations stop at this capacity; existing ownership is retained. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="6", ClampMax="5000"))
    int32 AIRivalMaxCollectionSize = 1536;

    /** Rotate the training leader and level-matched party after this many field battles. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="1", ClampMax="100"))
    int32 AIRivalTrainingBattlesPerParty = 8;

    /** Maximum level difference within a training cohort. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="0", ClampMax="30"))
    int32 AIRivalTrainingLevelSpan = 6;

    /** Review suitable habitat population after this many field battles; party changes always reassess immediately. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="1", ClampMax="100"))
    int32 AIRivalMapBalanceReviewActions = 4;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="AI Rivals", meta=(ClampMin="10.0", ClampMax="600.0"))
    float AIRivalSaveIntervalSeconds = 60.0f;


    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="1", ClampMax="200"))
    int32 MaxVisibleAIRivalsPerMap = 24;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World")
    float LocalChatRadius = 3000.0f; // Legacy config compatibility; WORLD has no distance limit.

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="1", ClampMax="512"))
    int32 MaxChatCharacters = 180;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="50.0", ClampMax="5000.0"))
    float TamerWalkSpeed = 240.0f;

    /** Tamer source-art scale multiplier, normalized to the original 5.4 presentation setting. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Character Presentation", meta=(ClampMin="0.5", ClampMax="8.0"))
    float TamerFieldSpriteScale = 5.4f;

    /** Partner follower source-art scale multiplier, normalized to the original 1.45 presentation setting. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Character Presentation", meta=(ClampMin="0.1", ClampMax="3.0"))
    float FollowerFieldSpriteScale = 1.45f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World", meta=(ClampMin="0.0", ClampMax="60.0"))
    float WildEncounterCooldownSeconds = 1.5f;

    /** Distance travelled on foot before the server performs another random encounter roll. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Field Exploration", meta=(ClampMin="50.0", ClampMax="2000.0"))
    float EncounterStepDistance = 180.0f;

    /** Probability of a wild encounter for each completed encounter step. Wild battles are field-walking driven, not button driven. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Field Exploration", meta=(ClampMin="0.0", ClampMax="1.0"))
    float EncounterChancePerStep = 0.08f;

    /** Safe walking distance after spawning or Atlas travel before encounters can roll. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Field Exploration", meta=(ClampMin="0.0", ClampMax="5000.0"))
    float EncounterSafeDistanceAfterTravel = 650.0f;

    /** Normalized width used for every real imported 2D habitat. Collision masks are never playable maps. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Map Presentation", meta=(ClampMin="2000.0", ClampMax="30000.0"))
    float MapWorldWidth = 10000.0f;

    /** Legacy configuration retained for compatibility. Source-mask edges now own collision; rectangular inset walls are disabled. */
    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy")
    float MapBoundaryThickness = 140.0f;

    /** Exact circular footprint at the tamer's feet, swept across every movement segment against source pixels. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Map Collision", meta=(DisplayName="Tamer Footprint Radius", ClampMin="8.0", ClampMax="200.0"))
    float TamerCollisionProbeRadius = 8.0f;

    /** Legacy key retained for config compatibility. World visuals now always render Custom Depth for cel shading. */
    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy")
    bool bRenderCustomDepthByDefault = true;

    /** Initial stencil value for unassigned map sprites. Existing authored stencil IDs are preserved. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Rendering", meta=(ClampMin="0", ClampMax="255"))
    int32 CustomDepthStencilValue = 1;

    /** Zoom relative to fitting the complete source map into the current viewport. One fits the whole map. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Camera", meta=(ClampMin="1.0", ClampMax="8.0"))
    float FieldCameraInitialZoom = 1.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Camera", meta=(ClampMin="0.05", ClampMax="2.0"))
    float FieldCameraZoomIncrement = 0.25f;

    /** Legacy fixed-world-unit zoom keys are retained for existing config; source-fit camera uses the settings above. */
    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy", meta=(ClampMin="500.0", ClampMax="10000.0"))
    float FieldCameraOrthoWidth = 2400.0f;

    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy", meta=(ClampMin="300.0", ClampMax="10000.0"))
    float FieldCameraMinOrthoWidth = 1100.0f;

    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy", meta=(ClampMin="500.0", ClampMax="20000.0"))
    float FieldCameraMaxOrthoWidth = 4800.0f;

    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy", meta=(ClampMin="25.0", ClampMax="2000.0"))
    float FieldCameraZoomStep = 260.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Camera", meta=(ClampMin="1000.0", ClampMax="10000.0"))
    float FieldCameraBoomLength = 3200.0f;

    /** Legacy angled-camera pitch used only when true top-down presentation is disabled. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Camera", meta=(ClampMin="-90.0", ClampMax="-25.0"))
    float FieldCameraPitch = -68.0f;

    /** Recommended field mode. Renders the imported map artwork face-on like a handheld 2D RPG, eliminating oblique Paper2D scanline aliasing. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Camera")
    bool bUseTrueTopDownFieldCamera = true;

    /** Legacy fixed orthographic width. The source-fit camera now derives width from source-map dimensions and viewport aspect ratio. */
    UPROPERTY(Config, BlueprintReadOnly, Category="World|Legacy", meta=(ClampMin="700.0", ClampMax="6000.0"))
    float TopDownFieldCameraOrthoWidth = 1250.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Follower", meta=(ClampMin="80.0", ClampMax="800.0"))
    float FollowerTrailDistance = 250.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Follower", meta=(ClampMin="1.0", ClampMax="30.0"))
    float FollowerFollowSpeed = 10.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="World|Follower", meta=(ClampMin="300.0", ClampMax="10000.0"))
    float FollowerSnapDistance = 1200.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="DigiFarm", meta=(ClampMin="1", ClampMax="500"))
    int32 MaxFarmResidents = 100;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="DigiFarm", meta=(ClampMin="1", ClampMax="1000000"))
    int32 ABIMeatCreditCost = 6000;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="DigiFarm", meta=(ClampMin="0", ClampMax="10000"))
    int32 ABIMeatRubyCost = 30;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution", meta=(ClampMin="1", ClampMax="200"))
    int32 MaxABI = 200;

    /** Form changes return to level 1; this gate prevents repeat level-1 ABI farming. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution", meta=(ClampMin="2", ClampMax="200"))
    int32 MinimumDeEvolutionLevel = 5;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|ABI Gains", meta=(ClampMin="1", ClampMax="200"))
    int32 EvolutionBaseABI = 2;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|ABI Gains", meta=(ClampMin="1", ClampMax="200"))
    int32 EvolutionLevelsPerABI = 10;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|ABI Gains", meta=(ClampMin="1", ClampMax="200"))
    int32 DeEvolutionBaseABI = 5;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|ABI Gains", meta=(ClampMin="1", ClampMax="200"))
    int32 DeEvolutionLevelsPerABI = 5;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Requirements", meta=(ClampMin="0", ClampMax="100"))
    int32 InTrainingEvolutionCAM = 0;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Requirements", meta=(ClampMin="0", ClampMax="100"))
    int32 RookieEvolutionCAM = 0;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Requirements", meta=(ClampMin="0", ClampMax="200"))
    int32 ChampionEvolutionABI = 0;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Requirements", meta=(ClampMin="1", ClampMax="200"))
    int32 UltimateEvolutionABI = 10;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Requirements", meta=(ClampMin="1", ClampMax="200"))
    int32 MegaEvolutionABI = 25;

    /** Flat total training budget shared by HP, SP and battle stats. Existing excess bonuses are preserved. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Evolution|Training", meta=(ClampMin="0", ClampMax="1000"))
    int32 TrainingBaseCapacity = 300;

    /** Online time in the active or reserve party awards CAM; boxed partners do not gain it. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party|Friendship", meta=(ClampMin="10.0", ClampMax="86400.0"))
    float PartyCAMIntervalSeconds = 300.0f;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Party|Friendship", meta=(ClampMin="1", ClampMax="100"))
    int32 PartyCAMGain = 1;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1", ClampMax="1000000"))
    int32 CAMMeatCreditCost = 150;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="0", ClampMax="10000"))
    int32 CAMMeatRubyCost = 1;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1", ClampMax="100"))
    int32 CAMMeatGain = 5;
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1", ClampMax="200"))
    int32 ABIMeatGain = 1;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(ClampMin="1", ClampMax="100000"))
    int32 CreditsPerDigiRuby = 100;

    /** Optional per-item money prices. Keys are canonical IDs from DigimonShop.json, such as hp_m or digimeat_atk_2. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    TMap<FName, int32> ShopCreditPriceOverrides;

    /** Optional per-item DigiRuby prices. Overrides take precedence over source and individual item settings. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="0"))
    TMap<FName, int32> ShopDigiRubyPriceOverrides;

    /** Private, action-driven season career. These settings never change shared Ranked Arena rewards. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Progression", meta=(ClampMin="0", ClampMax="200", ToolTip="Zero seeds the career from the first three active partners average level; a positive value overrides that starting level."))
    int32 SeasonStartingLevel = 0;

    /** Completed career matches per opponent level increase; includes title challenges. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Progression", meta=(DisplayName="Season Matches Per Level", ClampMin="1", ClampMax="52"))
    int32 SeasonWeeksPerLevel = 3;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Progression", meta=(ClampMin="1", ClampMax="200"))
    int32 SeasonMaxOpponentLevel = 99;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Championship", meta=(ClampMin="1", ClampMax="52"))
    int32 SeasonTitleIntervalWeeks = 4;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Championship", meta=(ClampMin="1", ClampMax="100"))
    int32 SeasonDefenseRewardInterval = 3;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonDefenseRewardCredits = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonTitleWinCredits = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMatchBaseCredits = 25;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMatchCreditsPerLevel = 7;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMonthlyBaseCredits = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMonthlyCreditsPerWin = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMonthlyRankBonus = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonMonthlyChampionBonus = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonYearlyBaseCredits = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonYearlyCreditsPerWin = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonYearlyRankBonus = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|Rewards", meta=(ClampMin="0", ClampMax="1000000"))
    int32 SeasonYearlyChampionBonus = 0;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|History", meta=(ClampMin="4", ClampMax="16"))
    int32 SeasonArchiveWeeks = 8;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Season Career|History", meta=(ClampMin="12", ClampMax="128"))
    int32 SeasonPayoutHistoryCount = 48;

    /** UTC ranked seasons begin on fixed boundaries anchored to Monday, 5 January 1970. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Seasons", meta=(ClampMin="1", ClampMax="30"))
    int32 RankedSeasonDays = 7;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Energy", meta=(ClampMin="1", ClampMax="999"))
    int32 RankedMaxEnergy = 30;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Energy", meta=(ClampMin="1", ClampMax="86400"))
    int32 RankedEnergyRechargeSeconds = 300;

    /** Bronze, Silver, Gold, Platinum, Diamond, Champion: six increasing source-game point thresholds. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Grades")
    TArray<int32> RankedGradeRatingThresholds = {0, 100, 300, 600, 1000, 1800};

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Points", meta=(ClampMin="0", ClampMax="1000"))
    int32 RankedWinPoints = 20;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Points", meta=(ClampMin="0", ClampMax="1000"))
    int32 RankedLossPoints = 5;

    /** Persisted actual bot parties fill the ladder when human defense snapshots are scarce. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Matchmaking")
    bool bRankedAllowAIRivals = true;

    /** Fraction of ranked points retained at season rollover; zero matches the source game. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Seasons", meta=(ClampMin="0.0", ClampMax="1.0"))
    float RankedSeasonRatingRetention = 0.0f;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Rewards", meta=(ClampMin="1", ClampMax="1000"))
    int32 RankedMinimumRewardMatches = 1;

    /** Human-only placement rewards for ranks 1, 2-10, 11-25, 26-50, 51-100, 101-500 and all other eligible players. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Rewards")
    TArray<int32> RankedPlacementDigiRubies = {300, 200, 150, 100, 75, 40, 20};

    /** Season participation reward by final grade, Bronze through Champion. Added to any placement bonus. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Ranked|Rewards")
    TArray<int32> RankedGradeDigiRubies = {10, 20, 40, 70, 100, 150};



    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 SmallHPCapsuleCreditCost = 60;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 SmallHPCapsuleRubyCost = 1;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 SmallSPCapsuleCreditCost = 90;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 SmallSPCapsuleRubyCost = 1;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 DigiMeatCreditCost = 2500;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Economy|Shop", meta=(ClampMin="1"))
    int32 DigiMeatRubyCost = 13;

    /** One server-wide policy for player, ranked, commerce and AI-rival automatic checkpoints.
     * Disabled: retain gameplay in server memory until admin /saveall or admin logout.
     * Ordinary player logout NEVER requests a disk checkpoint. A crash loses unflushed progress. */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Persistence", meta=(DisplayName="Enable Global Autosaves", ToolTip="OFF by default. Disables automatic player, ranked, commerce and AI-rival saves. Admin /saveall and admin logout still save all online and disconnected profiles. Ordinary player logout only retains progress in server memory. Unsaved progress is lost if the server crashes or is forcibly terminated."))
    bool bEnableGlobalAutosaves = false;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Persistence", meta=(EditCondition="bEnableGlobalAutosaves", ClampMin="10.0", ClampMax="1800.0"))
    float AutoSaveIntervalSeconds = 60.0f;
};
