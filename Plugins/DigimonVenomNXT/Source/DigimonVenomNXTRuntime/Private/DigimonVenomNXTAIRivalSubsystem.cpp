#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTAIRivalAvatar.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTAtomicFile.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTRivalRules.h"
#include "DigimonVenomNXTRivalRetention.h"
#include "DigimonVenomNXTRivalPersistence.h"
#include "DigimonVenomNXTRivalTrainingCore.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTStarterCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTVariantCore.h"
#include "DigimonVenomNXTWorld.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformTime.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogDigimonRivals, Log, All);

namespace
{
    constexpr int64 ActivityWindowSeconds = DigimonVenomNXTRivalRules::ActivityWindowSeconds;
}

void UDigimonVenomNXTAIRivalSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // World subsystems also exist in the editor and menu. Data and authoritative game mode
    // are only guaranteed at world begin-play; never create/write rivals from the menu.
}

void UDigimonVenomNXTAIRivalSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    if (!HasServerAuthority() || !GetData()) return;
    BuildSimulationCatalog();
    if (StarterSpecies.IsEmpty())
    {
        UE_LOG(LogDigimonRivals, Error, TEXT("Rival simulation disabled: species registry is unavailable. Existing saves are preserved without cleanup."));
        return;
    }
    if (!Load()) return;
    RefreshActivityWindow(FDateTime::UtcNow().ToUnixTimestamp());
    EnsurePopulation();
    if (ADigimonVenomNXTGameState* GS = InWorld.GetGameState<ADigimonVenomNXTGameState>()) GS->SetPersistentAIRivalCount(GetActiveRivalCount());
}

bool UDigimonVenomNXTAIRivalSubsystem::HasServerAuthority() const
{
    return GetWorld() && GetWorld()->IsGameWorld() && GetWorld()->GetNetMode() != NM_Client &&
        GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() != nullptr;
}

const UDigimonVenomNXTDataSubsystem* UDigimonVenomNXTAIRivalSubsystem::GetData() const
{
    const UGameInstance* GI = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
    return GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
}

void UDigimonVenomNXTAIRivalSubsystem::BuildSimulationCatalog()
{
    StarterSpecies.Reset(); ExplorationMaps.Reset();
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    if (!Data) return;
    for (const FDigimonSpeciesDefinition& Def : Data->GetStarterCandidates(512)) StarterSpecies.Add(Def.SpeciesId);
    if (StarterSpecies.IsEmpty())
        for (const FDigimonSpeciesDefinition& Def : Data->GetAllSpecies())
            if (!Def.bPlaceholder) { StarterSpecies.Add(Def.SpeciesId); break; }
    // Copy lightweight encounter data once, never terrain textures or collision masks
    // into each bot's per-action work.
    for (const FDigimonMapRow& Source : Data->GetAllMaps())
    {
        FDigimonMapRow Map;
        Map.MapId = Source.MapId; Map.DisplayName = Source.DisplayName;
        Map.RecommendedMinLevel = Source.RecommendedMinLevel;
        Map.RecommendedMaxLevel = Source.RecommendedMaxLevel;
        for (FName SpeciesId : Source.WildSpecies)
        {
            FDigimonSpeciesDefinition Def;
            if (Data->GetSpecies(SpeciesId, Def) && !Def.bPlaceholder) Map.WildSpecies.Add(SpeciesId);
        }
        if (!Map.WildSpecies.IsEmpty()) ExplorationMaps.Add(MoveTemp(Map));
    }
}

void UDigimonVenomNXTAIRivalSubsystem::Deinitialize()
{
    if (bLoaded && bDirty && GetWorld() && GetWorld()->GetNetMode() != NM_Client) Save();
    for (const TPair<FString, TWeakObjectPtr<ADigimonVenomNXTAIRivalAvatar>>& Entry : Avatars)
        if (ADigimonVenomNXTAIRivalAvatar* Avatar = Entry.Value.Get()) Avatar->Destroy();
    Avatars.Reset();
    NextPartyCAMUnix.Reset();
    MapPopulation.Reset();
    TrainingHabitatPopulation.Reset();
    Super::Deinitialize();
}

bool UDigimonVenomNXTAIRivalSubsystem::IsTickable() const
{
    return bLoaded && HasServerAuthority();
}

TStatId UDigimonVenomNXTAIRivalSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UDigimonVenomNXTAIRivalSubsystem, STATGROUP_Tickables);
}

FString UDigimonVenomNXTAIRivalSubsystem::SavePath() const
{
    return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT"), TEXT("AIRivals.json"));
}

int32 UDigimonVenomNXTAIRivalSubsystem::RetentionPopulation() const
{
    // Paused rivals still occupy disk/memory. Include them and any configured new population.
    return FMath::Max(SaveData.Rivals.Num(), FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPersistentAIRivals, 1, 5000));
}

void UDigimonVenomNXTAIRivalSubsystem::CompactRival(FDigimonAIRivalRecord& Rival)
{
    if (DigimonVenomNXTRivalRetention::Prune(Rival, *GetDefault<UDigimonVenomNXTSettings>(), GetData(), RetentionPopulation()).bChanged)
        bDirty = true;
}

bool UDigimonVenomNXTAIRivalSubsystem::Load()
{
    const FString Path = SavePath();
    bool bUnsupportedSchema = false;
    FString Error;
    int64 ReleasedPartners = 0;
    auto Read = [this, &bUnsupportedSchema, &Error, &ReleasedPartners](const FString& Source)
    {
        ReleasedPartners = 0;
        return DigimonVenomNXTRivalPersistence::Read(Source, SaveData,
            [this, &ReleasedPartners](FDigimonAIRivalRecord& Rival, int32 TotalRivals)
            {
                const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
                const auto Result = DigimonVenomNXTRivalRetention::Prune(Rival, *Settings, GetData(),
                    FMath::Max(TotalRivals, FMath::Clamp(Settings->MaxPersistentAIRivals, 1, 5000)));
                ReleasedPartners += Result.ReleasedPartners;
            }, Error, bUnsupportedSchema);
    };
    IFileManager& Files = IFileManager::Get();
    if (!Files.FileExists(*Path))
    {
        if (Files.FileExists(*(Path + TEXT(".bak"))))
        {
            if (!Read(Path + TEXT(".bak")))
            {
                UE_LOG(LogDigimonRivals, Error, TEXT("Rival backup could not be loaded: %s. Simulation disabled; save files preserved."), *Error);
                return false;
            }
            bRecoveredFromBackup = true;
        }
    }
    else if (!Read(Path))
    {
        if (bUnsupportedSchema)
        {
            UE_LOG(LogDigimonRivals, Error, TEXT("Rival save belongs to a newer framework version; simulation disabled without modifying it."));
            return false;
        }
        UE_LOG(LogDigimonRivals, Warning, TEXT("Primary rival checkpoint rejected: %s"), *Error);
        if (!Read(Path + TEXT(".bak")))
        {
            UE_LOG(LogDigimonRivals, Error, TEXT("Rival save and backup could not be loaded: %s. Simulation disabled; save files preserved."), *Error);
            return false;
        }
        bRecoveredFromBackup = true;
        // A single bounded diagnostic copy is enough. Never create a new gigabyte archive.
        if (Files.FileSize(*Path) <= DigimonVenomNXTRivalPersistence::MaxCheckpointBytes)
        {
            if (Files.Copy(*(Path + TEXT(".corrupt")), *Path, true, true) != COPY_OK)
                UE_LOG(LogDigimonRivals, Warning, TEXT("Could not archive corrupt primary; retaining valid backup during recovery."));
        }
        UE_LOG(LogDigimonRivals, Warning, TEXT("Recovered persistent rivals from the last complete backup."));
    }
    SaveData.SchemaVersion = 3;
    RebuildMapPopulation();
    for (FDigimonAIRivalRecord& Rival : SaveData.Rivals) NormalizeRival(Rival);
    bLoaded = true;
    bDirty = true;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    UE_LOG(LogDigimonRivals, Display, TEXT("Rival retention: %d stored tamers, %d Digimon per bot, %d scan records per bot; released %lld surplus/invalid/duplicate records during load."),
        SaveData.Rivals.Num(), DigimonVenomNXTRivalRetention::CollectionLimit(Settings->AIRivalMaxCollectionSize, Settings->MaxPartySize, RetentionPopulation()),
        DigimonVenomNXTRivalRetention::ScanLimit(Settings->AIRivalMaxScanRecords, RetentionPopulation()), static_cast<long long>(ReleasedPartners));
    return true;
}

bool UDigimonVenomNXTAIRivalSubsystem::Save(bool bExplicitAdminSave)
{
    if (!bLoaded || !GetWorld() || GetWorld()->GetNetMode() == NM_Client) return false;
    if (!bExplicitAdminSave && !GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves) return true;
    // Include paused rivals and live-battle records; compaction preserves their active party.
    for (FDigimonAIRivalRecord& Rival : SaveData.Rivals) CompactRival(Rival);
    if (!bDirty) return true;
    const FString Path = SavePath();
    const FString Temporary = Path + TEXT(".tmp");
    const FString Backup = Path + TEXT(".bak");
    const FString BackupTemporary = Backup + TEXT(".tmp");
    IFileManager& Files = IFileManager::Get();
    Files.MakeDirectory(*FPaths::GetPath(Path), true);
    SaveData.LastSavedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    FString Error;
    if (!DigimonVenomNXTRivalPersistence::WriteTemporary(Temporary, SaveData, Error))
    {
        UE_LOG(LogDigimonRivals, Error, TEXT("Could not write rival checkpoint: %s. Previous save retained."), *Error);
        Files.Delete(*Temporary, false, true);
        return false;
    }
    // Rotate just one backup through its own temporary file. During first legacy
    // compaction/recovery seed it from the completed compact checkpoint, so a 1GB
    // previous database does not remain indefinitely as a second archive.
    const bool bSeedCompactBackup = bRecoveredFromBackup || !Files.FileExists(*Path) ||
        Files.FileSize(*Path) > DigimonVenomNXTRivalPersistence::MaxCheckpointBytes;
    const FString BackupSource = bSeedCompactBackup ? Temporary : Path;
    if (Files.Copy(*BackupTemporary, *BackupSource, true, true) != COPY_OK ||
        !DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Backup, BackupTemporary))
    {
        UE_LOG(LogDigimonRivals, Error, TEXT("Could not back up rival checkpoint; previous save retained."));
        Files.Delete(*BackupTemporary, false, true);
        Files.Delete(*Temporary, false, true);
        return false;
    }
    if (!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Path, Temporary))
    {
        UE_LOG(LogDigimonRivals, Error, TEXT("Could not publish rival checkpoint; backup retained."));
        Files.Delete(*Temporary, false, true);
        return false;
    }
    // Only discard an oversized diagnostic artifact after both valid checkpoints exist.
    const FString Corrupt = Path + TEXT(".corrupt");
    if (Files.FileSize(*Corrupt) > DigimonVenomNXTRivalPersistence::MaxCheckpointBytes && !Files.Delete(*Corrupt, false, true))
        UE_LOG(LogDigimonRivals, Warning, TEXT("Could not remove oversized obsolete rival diagnostic archive."));
    bDirty = false;
    bRecoveredFromBackup = false;
    UE_LOG(LogDigimonRivals, Display, TEXT("Saved %d persistent rivals in %.2f MiB (bounded, streamed checkpoint)."),
        SaveData.Rivals.Num(), static_cast<double>(Files.FileSize(*Path)) / (1024.0 * 1024.0));
    return true;
}

bool UDigimonVenomNXTAIRivalSubsystem::SaveForHostConsole()
{
    UWorld* World = GetWorld();
    if (!HasServerAuthority() || !World || World->GetNetMode() != NM_ListenServer) return false;
    UGameInstance* GI = World->GetGameInstance();
    UDigimonVenomNXTServerConsoleSubsystem* Console = GI ? GI->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>() : nullptr;
    if (!Console || !Console->CanAccess(GI->GetFirstLocalPlayerController())) return false;
    return Save(true);
}

bool UDigimonVenomNXTAIRivalSubsystem::ReleaseStoredPartner(const FString& RivalId, FGuid InstanceId)
{
    if (!bLoaded || !HasServerAuthority() || IsRivalInLiveBattle(RivalId)) return false;
    FDigimonAIRivalRecord* Rival = FindRivalMutable(RivalId);
    if (!Rival || !DigimonVenomNXTRivalRetention::Release(*Rival, InstanceId,
        *GetDefault<UDigimonVenomNXTSettings>(), GetData(), RetentionPopulation())) return false;
    Rival->CurrentActivity = TEXT("Released a stored Digimon; storage slot available");
    bDirty = true;
    return true;
}

void UDigimonVenomNXTAIRivalSubsystem::RefreshActivityWindow(int64 Now)
{
    if (DigimonVenomNXTRivalRules::RefreshWindow(Now, SaveData.ActivityWindowStartUnix, SaveData.Rivals)) bDirty = true;
}

void UDigimonVenomNXTAIRivalSubsystem::RecordActivity(FDigimonAIRivalRecord& Rival, const FDigimonAIRivalActivityCounters& Delta)
{
    RefreshActivityWindow(FDateTime::UtcNow().ToUnixTimestamp());
    Rival.WindowStats.Add(Delta);
    Rival.LifetimeStats.Add(Delta);
    bDirty = true;
}

void UDigimonVenomNXTAIRivalSubsystem::SetSpeciesMoves(FDigimonOwnedPartner& Partner) const
{
    Partner.Moves.Reset();
    Partner.Moves = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData()).Moves;
}

FDigimonOwnedPartner UDigimonVenomNXTAIRivalSubsystem::MakePartner(FName SpeciesId, EDigimonVariant Variant, int32 Level) const
{
    FDigimonOwnedPartner Partner;
    Partner.InstanceId = FGuid::NewGuid();
    Partner.SpeciesId = SpeciesId;
    Partner.Variant = Variant;
    Partner.Level = FMath::Clamp(Level, 1, FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel, 1, 200));
    Partner.Experience = DigimonVenomNXTProgressionCore::ExperienceFloor(Partner.Level);
    Partner.CAM = 0;
    Partner.ABI = 0;
    Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    Partner.PermanentTraining.MaxHP = 0; Partner.PermanentTraining.MaxSP = 0;
    Partner.PermanentTraining.Attack = 0; Partner.PermanentTraining.Defense = 0;
    Partner.PermanentTraining.Spirit = 0; Partner.PermanentTraining.Speed = 0;
    SetSpeciesMoves(Partner);
    const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData());
    Partner.CurrentHP = Unit.Stats.MaxHP;
    Partner.CurrentSP = Unit.Stats.MaxSP;
    return Partner;
}

FDigimonOwnedPartner UDigimonVenomNXTAIRivalSubsystem::MakePartnerForRival(int32 Level) const
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    Level = FMath::Max(Level, DigimonVenomNXTStarterCore::StartingLevel(Settings->StarterLevel, Settings->MaxPartnerLevel));
    if (!StarterSpecies.IsEmpty()) return MakePartner(StarterSpecies[FMath::RandHelper(StarterSpecies.Num())], EDigimonVariant::Normal, Level);
    return FDigimonOwnedPartner(); // No synthetic/unknown species is ever persisted.
}

FDigimonAIRivalRecord UDigimonVenomNXTAIRivalSubsystem::MakeRival(int32 Index) const
{
    FDigimonAIRivalRecord Rival;
    Rival.RivalId = FString::Printf(TEXT("AI-%04d"), Index + 1);
    static const TCHAR* Given[] = { TEXT("Aster"), TEXT("Kira"), TEXT("Ren"), TEXT("Nova"), TEXT("Kai"), TEXT("Mira"), TEXT("Sora"), TEXT("Axel"), TEXT("Nia"), TEXT("Rei"), TEXT("Orion"), TEXT("Yuna") };
    static const TCHAR* Guild[] = { TEXT("Pulse"), TEXT("Circuit"), TEXT("Prism"), TEXT("Vector"), TEXT("Echo"), TEXT("Helix"), TEXT("Flux"), TEXT("Beacon") };
    Rival.DisplayName = FString::Printf(TEXT("%s %s %03d"), Given[Index % UE_ARRAY_COUNT(Given)], Guild[(Index / UE_ARRAY_COUNT(Given)) % UE_ARRAY_COUNT(Guild)], Index + 1);
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 FirstLevel = DigimonVenomNXTStarterCore::StartingLevel(Settings->StarterLevel, Settings->MaxPartnerLevel);
    // Retain the established ladder population spread, with no under-level starters.
    Rival.TamerLevel = FMath::Max(FirstLevel, 1 + (Index % FMath::Clamp(Settings->MaxPartnerLevel, 1, 200)));
    Rival.StarterBalanceVersion = DigimonVenomNXTStarterCore::BalanceVersion;
    Rival.Credits = 1000;
    Rival.ExplorationTargetLevel = Rival.TamerLevel;
    const FDigimonOwnedPartner Partner = MakePartnerForRival(Rival.TamerLevel);
    if (Partner.IsValid()) { Rival.Partners.Add(Partner); Rival.Collection.Add(Partner); }
    Rival.LastSimulatedUnix = FDateTime::UtcNow().ToUnixTimestamp();
    Rival.NextActionUnix = Rival.LastSimulatedUnix + Index % FMath::Max(5, GetDefault<UDigimonVenomNXTSettings>()->AIRivalActionIntervalSeconds);
    // Initial placement uses the same eligibility and population rules as travel,
    // without recording a fabricated travel event or changing partner levels.
    std::vector<DigimonVenomNXTRivalTrainingCore::Habitat> Habitats;
    Habitats.reserve(ExplorationMaps.Num());
    for (const FDigimonMapRow& Map : ExplorationMaps)
        Habitats.push_back({Map.MapId, Map.RecommendedMinLevel, Map.RecommendedMaxLevel, MapPopulation.FindRef(Map.MapId)});
    Rival.MapId = DigimonVenomNXTRivalTrainingCore::ChooseHabitat(Habitats, Rival.TamerLevel, INDEX_NONE, GetTypeHash(Rival.RivalId));
    return Rival;
}

void UDigimonVenomNXTAIRivalSubsystem::NormalizeRival(FDigimonAIRivalRecord& Rival)
{
    CompactRival(Rival); // Bound legacy ownership before migration/building combat stats.
    // Existing Partners are the authoritative legacy records. Merge by GUID rather than
    // recreating them: XP, moves, training, variants and scans survive this migration.
    for (FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        if (!Partner.InstanceId.IsValid()) Partner.InstanceId = FGuid::NewGuid();
        if (Partner.Moves.IsEmpty()) SetSpeciesMoves(Partner);
        FDigimonOwnedPartner* Existing = Rival.Collection.FindByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Partner.InstanceId; });
        if (Existing) *Existing = Partner;
        else Rival.Collection.Add(Partner);
    }
    if (Rival.Collection.IsEmpty())
    {
        const FDigimonOwnedPartner Partner = MakePartnerForRival(FMath::Max(1, Rival.TamerLevel));
        if (Partner.IsValid()) Rival.Collection.Add(Partner);
    }
    // Preserve each old HP/SP fraction before any starter or XP correction uses new maxima.
    for (FDigimonOwnedPartner& Partner : Rival.Collection)
        DigimonVenomNXTAutoBattle::MigratePartner(Partner, GetData());
    // Normalize legacy snapshots first, then upgrade only the original starter.
    // Selected party copies are rebuilt below so stale low-level copies cannot win.
    if (!Rival.Collection.IsEmpty() && Rival.StarterBalanceVersion < DigimonVenomNXTStarterCore::BalanceVersion)
    {
        const UDigimonVenomNXTDataSubsystem* Data = GetData();
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        FDigimonOwnedPartner& Starter = Rival.Collection[0];
        FDigimonSpeciesDefinition Def;
        if (Data && Data->GetSpecies(Starter.SpeciesId, Def))
            DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Rival.StarterBalanceVersion, Settings->StarterLevel,
                Settings->MaxPartnerLevel, Starter.IsValid() && !Def.bPlaceholder && Def.Stage == EDigimonStage::Rookie &&
                Starter.Variant == EDigimonVariant::Normal && Rival.LifetimeStats.Evolutions == 0 && Rival.LifetimeStats.DeEvolutions == 0,
                false, [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
    }
    // Repair XP/level mismatches for every owned creature before rebuilding party
    // snapshots. Corrections are not new battles, rewards or activity-window XP.
    const UDigimonVenomNXTDataSubsystem* ProgressionData = GetData();
    for (FDigimonOwnedPartner& Partner : Rival.Collection)
        if (Partner.IsValid()) DigimonVenomNXTProgressionCore::Apply(Partner, 0, GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel,
            [ProgressionData](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, ProgressionData).Stats; });
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    // No invented offline battles: resume work once, with no catch-up burst.
    Rival.NextActionUnix = FMath::Clamp<int64>(Rival.NextActionUnix, Now, Now + FMath::Max(5, GetDefault<UDigimonVenomNXTSettings>()->AIRivalActionIntervalSeconds));
    SelectParty(Rival);
    if (Rival.Partners.IsEmpty())
    {
        // Cleanup removes unusable early placeholder records. If none of the retained
        // creatures can form a party, provide one real starter to resume.
        const FDigimonOwnedPartner Recovered = MakePartnerForRival(FMath::Max(1, Rival.TamerLevel));
        if (Recovered.IsValid()) { Rival.Collection.Add(Recovered); SelectParty(Rival); }
    }
    if (Rival.ExplorationTargetLevel <= 0) Rival.ExplorationTargetLevel = Rival.TamerLevel;
    CompactRival(Rival);
}

void UDigimonVenomNXTAIRivalSubsystem::EnsurePopulation()
{
    if (!bLoaded || !HasServerAuthority()) return;
    RebuildMapPopulation();
    const int32 Target = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPersistentAIRivals, 0, 5000);
    while (SaveData.Rivals.Num() < Target)
    {
        FDigimonAIRivalRecord Rival = MakeRival(SaveData.Rivals.Num());
        if (Rival.Partners.IsEmpty())
        {
            UE_LOG(LogDigimonRivals, Error, TEXT("No valid species data; rival population creation paused."));
            break;
        }
        SelectParty(Rival);
        ++MapPopulation.FindOrAdd(Rival.MapId);
        SaveData.Rivals.Add(MoveTemp(Rival));
    }
    // Lowering the active limit pauses surplus tamers, preserving every owned creature.
    bDirty = true;
    Save();
}

int32 UDigimonVenomNXTAIRivalSubsystem::GetActiveRivalCount() const
{
    return FMath::Min(SaveData.Rivals.Num(), FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPersistentAIRivals, 0, 5000));
}

TArray<FDigimonAIRivalRecord> UDigimonVenomNXTAIRivalSubsystem::GetAllRivals() const
{
    TArray<FDigimonAIRivalRecord> Out;
    const int32 Count = GetActiveRivalCount();
    Out.Reserve(Count);
    for (int32 Index = 0; Index < Count; ++Index) Out.Add(SaveData.Rivals[Index]);
    return Out;
}

TArray<FDigimonAIRivalRecord> UDigimonVenomNXTAIRivalSubsystem::GetRivalBattleSnapshots() const
{
    TArray<FDigimonAIRivalRecord> Out;
    Out.Reserve(GetActiveRivalCount());
    for (int32 Index = 0; Index < GetActiveRivalCount(); ++Index)
    {
        const FDigimonAIRivalRecord& Source = SaveData.Rivals[Index];
        FDigimonAIRivalRecord Rival;
        Rival.RivalId = Source.RivalId; Rival.DisplayName = Source.DisplayName;
        Rival.MapId = Source.MapId; Rival.TamerLevel = Source.TamerLevel;
        Rival.Partners = Source.Partners;
        Out.Add(MoveTemp(Rival));
    }
    return Out;
}

FDigimonAIRivalRecord* UDigimonVenomNXTAIRivalSubsystem::FindRivalMutable(const FString& RivalId)
{
    const int32 Count = GetActiveRivalCount();
    for (int32 Index = 0; Index < Count; ++Index)
        if (SaveData.Rivals[Index].RivalId == RivalId) return &SaveData.Rivals[Index];
    return nullptr;
}

bool UDigimonVenomNXTAIRivalSubsystem::GetRival(const FString& RivalId, FDigimonAIRivalRecord& OutRival) const
{
    const int32 Count = GetActiveRivalCount();
    for (int32 Index = 0; Index < Count; ++Index)
        if (SaveData.Rivals[Index].RivalId == RivalId) { OutRival = SaveData.Rivals[Index]; return true; }
    return false;
}

TArray<FDigimonAIRivalRecord> UDigimonVenomNXTAIRivalSubsystem::GetRivalsOnMap(int32 MapId, int32 MaxResults) const
{
    TArray<FDigimonAIRivalRecord> Out;
    const int32 Limit = FMath::Clamp(MaxResults, 1, 200);
    for (int32 Index = 0; Index < GetActiveRivalCount(); ++Index)
    {
        const FDigimonAIRivalRecord& Rival = SaveData.Rivals[Index];
        if (Rival.MapId != MapId) continue;
        Out.Add(Rival);
        if (Out.Num() >= Limit) break;
    }
    return Out;
}

FDigimonAIRivalActivityPage UDigimonVenomNXTAIRivalSubsystem::GetActivityPage(int32 PageIndex, int32 PageSize)
{
    FDigimonAIRivalActivityPage Page;
    if (!bLoaded || !HasServerAuthority()) return Page;
    Page.ServerUnix = FDateTime::UtcNow().ToUnixTimestamp();
    RefreshActivityWindow(Page.ServerUnix);
    Page.WindowStartUnix = SaveData.ActivityWindowStartUnix;
    Page.WindowEndUnix = Page.WindowStartUnix + ActivityWindowSeconds;
    Page.TotalRivals = GetActiveRivalCount();
    Page.PageSize = FMath::Clamp(PageSize, 1, 25);
    Page.TotalPages = FMath::DivideAndRoundUp(Page.TotalRivals, Page.PageSize);
    Page.PageIndex = FMath::Clamp(PageIndex, 0, FMath::Max(0, Page.TotalPages - 1));
    const int32 Start = Page.PageIndex * Page.PageSize;
    for (int32 Index = 0; Index < Page.TotalRivals; ++Index)
    {
        const FDigimonAIRivalRecord& Rival = SaveData.Rivals[Index];
        Page.Totals.Add(Rival.WindowStats);
        if (Index < Start || Index >= Start + Page.PageSize) continue;
        FDigimonAIRivalActivityRow Row;
        Row.RivalId = Rival.RivalId; Row.DisplayName = Rival.DisplayName;
        Row.MapId = Rival.MapId; Row.TamerLevel = Rival.TamerLevel;
        Row.PartySize = Rival.Partners.Num(); Row.CollectionSize = Rival.Collection.Num();
        Row.CurrentActivity = Rival.CurrentActivity.Left(160);
        Row.LastSimulatedUnix = Rival.LastSimulatedUnix; Row.Stats = Rival.WindowStats;
        Page.Rows.Add(MoveTemp(Row));
    }
    return Page;
}

void UDigimonVenomNXTAIRivalSubsystem::StoreParty(FDigimonAIRivalRecord& Rival)
{
    for (const FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        FDigimonOwnedPartner* Owned = Rival.Collection.FindByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Partner.InstanceId; });
        if (Owned) *Owned = Partner;
        else if (Partner.IsValid()) Rival.Collection.Add(Partner);
    }
    CompactRival(Rival);
    if (ADigimonVenomNXTAIRivalAvatar* Avatar = Avatars.FindRef(Rival.RivalId).Get())
        Avatar->RefreshLeaderFollower(Rival.Partners.IsEmpty() ? FDigimonOwnedPartner() : Rival.Partners[0]);
}

int32 UDigimonVenomNXTAIRivalSubsystem::PartyTrainingLevel(const FDigimonAIRivalRecord& Rival) const
{
    // Reserves can enter combat too: every party member must fit the habitat.
    // TamerLevel is a lifetime profile level, not permission to take a rookie
    // into level-100 fields.
    int32 Level = MAX_int32;
    for (const FDigimonOwnedPartner& Partner : Rival.Partners) Level = FMath::Min(Level, Partner.Level);
    return Level == MAX_int32 ? 1 : FMath::Max(1, Level);
}

void UDigimonVenomNXTAIRivalSubsystem::RebuildMapPopulation()
{
    MapPopulation.Reset();
    for (int32 Index = 0; Index < GetActiveRivalCount(); ++Index) ++MapPopulation.FindOrAdd(SaveData.Rivals[Index].MapId);
    TrainingHabitatPopulation.Init(0, 201);
    // Cache level demand once per bounded batch, not one population scan per
    // creature in every tamer's collection. Used only for equally old leaders.
    for (int32 Level = 1; Level < TrainingHabitatPopulation.Num(); ++Level)
    {
        int32 Best = MAX_int32;
        for (const FDigimonMapRow& Map : ExplorationMaps)
            if (DigimonVenomNXTRivalRules::IsSuitableMap(Map.RecommendedMinLevel, Map.RecommendedMaxLevel, Level))
                Best = FMath::Min(Best, MapPopulation.FindRef(Map.MapId));
        TrainingHabitatPopulation[Level] = Best == MAX_int32 ? 0 : Best;
    }
}

void UDigimonVenomNXTAIRivalSubsystem::SelectParty(FDigimonAIRivalRecord& Rival, bool bRotate, FGuid PreferredLeader)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    TMap<FGuid, int64> History;
    for (const FDigimonAIRivalTrainingHistory& Entry : Rival.TrainingHistory)
        if (Entry.InstanceId.IsValid()) History.Add(Entry.InstanceId, FMath::Clamp<int64>(Entry.LastLedSession, 0, FMath::Max<int64>(0, Rival.TrainingSessionSerial)));
    std::vector<DigimonVenomNXTRivalTrainingCore::Candidate> Candidates;
    Candidates.reserve(Rival.Collection.Num());
    TSet<FGuid> Seen;
    int32 Leader = INDEX_NONE;
    int32 Preferred = INDEX_NONE;
    for (int32 Index = 0; Index < Rival.Collection.Num(); ++Index)
    {
        const FDigimonOwnedPartner& Partner = Rival.Collection[Index];
        FDigimonSpeciesDefinition Def;
        if (!Partner.IsValid() || Seen.Contains(Partner.InstanceId) || !Data ||
            !Data->GetSpecies(Partner.SpeciesId, Def) || Def.bPlaceholder) continue;
        Seen.Add(Partner.InstanceId);
        const int32 Level = FMath::Clamp(Partner.Level, 1, 200);
        Candidates.push_back({Index, Level, History.FindRef(Partner.InstanceId),
            TrainingHabitatPopulation.IsValidIndex(Level) ? TrainingHabitatPopulation[Level] : 0});
        if (Partner.InstanceId == Rival.TrainingLeaderId) Leader = Index;
        if (Partner.InstanceId == PreferredLeader) Preferred = Index;
        Rival.TamerLevel = FMath::Max(Rival.TamerLevel, Partner.Level);
    }
    const uint32 Seed = GetTypeHash(Rival.RivalId);
    const bool bNewSession = bRotate || Leader == INDEX_NONE || Preferred != INDEX_NONE;
    if (bNewSession) Leader = Preferred != INDEX_NONE ? Preferred : DigimonVenomNXTRivalTrainingCore::ChooseLeader(Candidates, Seed);
    const std::vector<int> Selected = DigimonVenomNXTRivalTrainingCore::BuildParty(Candidates, Leader,
        Settings->MaxPartySize, Settings->AIRivalTrainingLevelSpan, Seed ^ static_cast<uint32>(Rival.TrainingSessionSerial));
    Rival.Partners.Reset();
    for (int32 Index : Selected) Rival.Partners.Add(Rival.Collection[Index]);
    if (bNewSession && !Rival.Partners.IsEmpty())
    {
        // Defensively renormalize a saturated imported counter without erasing
        // ownership or giving one partner a permanent maximum-priority age.
        if (Rival.TrainingSessionSerial >= MAX_int64 - 1)
        {
            for (TPair<FGuid, int64>& Entry : History) Entry.Value /= 2;
            Rival.TrainingSessionSerial /= 2;
        }
        Rival.TrainingSessionSerial = FMath::Max<int64>(0, Rival.TrainingSessionSerial) + 1;
        Rival.TrainingLeaderId = Rival.Partners[0].InstanceId;
        History.Add(Rival.TrainingLeaderId, Rival.TrainingSessionSerial);
        Rival.TrainingSessionBattles = 0;
        Rival.TrainingSessionStartLevel = Rival.Partners[0].Level;
        Rival.ConsecutiveWildLosses = 0;
        Rival.ConsecutiveWildWins = 0;
        Rival.ExplorationTargetLevel = PartyTrainingLevel(Rival);
        NextPartyCAMUnix.Remove(Rival.RivalId); // A new party earns its own live-presence interval.
    }
    else
    {
        Rival.TrainingSessionBattles = FMath::Max(0, Rival.TrainingSessionBattles);
        Rival.ExplorationTargetLevel = FMath::Clamp(Rival.ExplorationTargetLevel, 1, PartyTrainingLevel(Rival));
    }
    Rival.TrainingHistory.Reset();
    Rival.TrainingHistory.Reserve(static_cast<int32>(Candidates.size()));
    for (const auto& Candidate : Candidates)
    {
        FDigimonAIRivalTrainingHistory Entry;
        Entry.InstanceId = Rival.Collection[Candidate.Index].InstanceId;
        Entry.LastLedSession = History.FindRef(Entry.InstanceId);
        Rival.TrainingHistory.Add(Entry);
    }
    if (ADigimonVenomNXTAIRivalAvatar* Avatar = Avatars.FindRef(Rival.RivalId).Get())
        Avatar->RefreshLeaderFollower(Rival.Partners.IsEmpty() ? FDigimonOwnedPartner() : Rival.Partners[0]);
}

bool UDigimonVenomNXTAIRivalSubsystem::TravelToSuitableMap(FDigimonAIRivalRecord& Rival, FRandomStream& Random, bool bRetreat)
{
    if (ExplorationMaps.IsEmpty()) return false;
    int32 DesiredLevel = FMath::Clamp(Rival.ExplorationTargetLevel, 1, PartyTrainingLevel(Rival));
    if (bRetreat)
    {
        const FDigimonMapRow* Current = ExplorationMaps.FindByPredicate([&](const FDigimonMapRow& Map) { return Map.MapId == Rival.MapId; });
        DesiredLevel = FMath::Max(1, FMath::Min(DesiredLevel, Current ? Current->RecommendedMinLevel : DesiredLevel) - 8);
        Rival.ExplorationTargetLevel = DesiredLevel;
    }
    std::vector<DigimonVenomNXTRivalTrainingCore::Habitat> Habitats;
    Habitats.reserve(ExplorationMaps.Num());
    for (const FDigimonMapRow& Map : ExplorationMaps)
        Habitats.push_back({Map.MapId, Map.RecommendedMinLevel, Map.RecommendedMaxLevel, MapPopulation.FindRef(Map.MapId)});
    const int32 Destination = DigimonVenomNXTRivalTrainingCore::ChooseHabitat(Habitats, DesiredLevel, Rival.MapId, Random.GetUnsignedInt());
    if (Destination == Rival.MapId) return false;
    MapPopulation.FindOrAdd(Rival.MapId) = FMath::Max(0, MapPopulation.FindRef(Rival.MapId) - 1);
    ++MapPopulation.FindOrAdd(Destination);
    Rival.MapId = Destination;
    Rival.ConsecutiveWildLosses = 0;
    Rival.ConsecutiveWildWins = 0;
    // Release the old public-map proxy immediately. The visibility pass places a
    // fresh proxy at the destination only when players are actually present.
    if (ADigimonVenomNXTAIRivalAvatar* Avatar = Avatars.FindRef(Rival.RivalId).Get()) Avatar->Destroy();
    Avatars.Remove(Rival.RivalId);
    Rival.CurrentActivity = FString::Printf(TEXT("Travelled to map %d%s"), Rival.MapId, bRetreat ? TEXT(" to recover momentum") : TEXT(" with the current training party"));
    FDigimonAIRivalActivityCounters Delta; Delta.MapTravels = 1;
    RecordActivity(Rival, Delta);
    return true;
}

bool UDigimonVenomNXTAIRivalSubsystem::HealPartyIfNeeded(FDigimonAIRivalRecord& Rival)
{
    bool bNeedsHealing = false;
    for (const FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData());
        if (Partner.CurrentHP < FMath::Max(1, Unit.Stats.MaxHP * 35 / 100) || Partner.CurrentSP < Unit.Stats.MaxSP / 8) { bNeedsHealing = true; break; }
    }
    if (!bNeedsHealing) return false;
    for (FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData());
        Partner.CurrentHP = Unit.Stats.MaxHP; Partner.CurrentSP = Unit.Stats.MaxSP;
    }
    Rival.CurrentActivity = TEXT("Recovered party HP and SP at the healing service");
    FDigimonAIRivalActivityCounters Delta; Delta.Heals = 1;
    RecordActivity(Rival, Delta);
    StoreParty(Rival);
    return true;
}

bool UDigimonVenomNXTAIRivalSubsystem::TryMaterialize(FDigimonAIRivalRecord& Rival)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    // Check BEFORE consuming scan, allocating a GUID, or constructing a new partner.
    if (Rival.Collection.Num() >= DigimonVenomNXTRivalRetention::CollectionLimit(
        Settings->AIRivalMaxCollectionSize, Settings->MaxPartySize, RetentionPopulation())) return false;
    for (FDigimonScanRecord& Scan : Rival.Scans)
    {
        const auto Result = DigimonVenomNXTScanCore::Materialize(Scan.Percent, Settings->MaterializeRequirementPercent,
            Settings->ScanCapPercent, Settings->bConsumeScanOnMaterialize);
        if (!Result.Ready || Rival.Collection.ContainsByPredicate([&](const FDigimonOwnedPartner& P) { return P.SpeciesId == Scan.SpeciesId && P.Variant == Scan.Variant; })) continue;
        FDigimonSpeciesDefinition Def;
        if (!GetData() || !GetData()->GetSpecies(Scan.SpeciesId, Def) || Def.bPlaceholder ||
            !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Scan.Variant), Def.bHasNormalArtwork, Def.bHasParadoxArtwork, Def.bHasShinyArtwork, Def.bHasFirewallArtwork)) continue;
        FDigimonOwnedPartner Partner = MakePartner(Scan.SpeciesId, Scan.Variant, 1);
        if (!Partner.IsValid()) continue;
        Partner.ABI = Result.BonusABI;
        const FDigimonStats MaterializedStats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData()).Stats;
        Partner.CurrentHP = MaterializedStats.MaxHP;
        Partner.CurrentSP = MaterializedStats.MaxSP;
        Rival.Collection.Add(MoveTemp(Partner));
        DigimonVenomNXTScanCore::Observe(Scan, Settings->ScanCapPercent, true);
        Scan.Percent = Result.RemainingPercent;
        if (Scan.Materializations < MAX_int32) ++Scan.Materializations;
        // A newcomer is immediately eligible to lead the next session. Do not
        // repeatedly interrupt an expedition before it has completed real battles.
        SelectParty(Rival, Rival.TrainingSessionBattles >= FMath::Clamp(Settings->AIRivalTrainingBattlesPerParty, 1, 4));
        const TCHAR* MaterializedVariety = Scan.Variant == EDigimonVariant::Firewall ? TEXT("Firewall ") :
            Scan.Variant == EDigimonVariant::Shiny ? TEXT("Shiny ") :
            Scan.Variant == EDigimonVariant::Paradox ? TEXT("Paradox ") : TEXT("");
        Rival.CurrentActivity = FString::Printf(TEXT("Materialized %s%s from scan data"), MaterializedVariety, *Def.DisplayName.ToString());
        FDigimonAIRivalActivityCounters Delta; Delta.Materializations = 1; Delta.ABIGained = Result.BonusABI;
        RecordActivity(Rival, Delta);
        return true;
    }
    return false;
}

bool UDigimonVenomNXTAIRivalSubsystem::TryEvolve(FDigimonAIRivalRecord& Rival)
{
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    if (!Data) return false;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int32 MaxLevel = FMath::Clamp(Settings->MaxPartnerLevel, 1, 200);
    const int32 MaxABI = FMath::Clamp(Settings->MaxABI, 1, 200);
    for (FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        const TArray<FDigimonEvolutionOption> Forward = DigimonVenomNXTEvolution::GetOptions(Partner, Data, false);
        const FDigimonEvolutionOption* NextRoute = nullptr;
        const FDigimonEvolutionOption* ReadyRoute = nullptr;
        for (const FDigimonEvolutionOption& Option : Forward)
        {
            if (Option.bDeEvolution || (Option.RequiredLevel > MaxLevel && Partner.Level < Option.RequiredLevel) ||
                (Option.RequiredABI > MaxABI && Partner.ABI < Option.RequiredABI) || Option.RequiredCAM > 100) continue;
            if (Option.bAvailable) { ReadyRoute = &Option; break; }
            // Prefer an achievable branch rather than farming ABI for the most expensive
            // alternative. Registry order is a deterministic tie breaker.
            if (!NextRoute || Option.RequiredABI < NextRoute->RequiredABI ||
                (Option.RequiredABI == NextRoute->RequiredABI && Option.RequiredLevel < NextRoute->RequiredLevel))
                NextRoute = &Option;
        }

        FName TargetId = ReadyRoute ? ReadyRoute->TargetSpeciesId : NAME_None;
        bool bDeEvolution = false;
        if (!ReadyRoute && NextRoute && Partner.Level >= NextRoute->RequiredLevel && Partner.ABI < NextRoute->RequiredABI)
        {
            // Recycle a mature form only when ABI blocks its next form. Both operations
            // reset to level 1, so a rival must train again before another cycle. Terminal
            // species and forms merely waiting for CAM/stat training are not downgraded.
            const TArray<FDigimonEvolutionOption> Options = DigimonVenomNXTEvolution::GetOptions(Partner, Data);
            const FDigimonEvolutionOption* Reverse = nullptr;
            for (const FDigimonEvolutionOption& Option : Options)
                if (Option.bDeEvolution && Option.bAvailable && Option.ABIGain > 0 &&
                    (!Reverse || Option.TargetStage > Reverse->TargetStage)) Reverse = &Option;
            if (Reverse) { TargetId = Reverse->TargetSpeciesId; bDeEvolution = true; }
        }
        if (TargetId.IsNone()) continue;
        const int32 BeforeABI = Partner.ABI;
        FString Message;
        if (!DigimonVenomNXTEvolution::TryTransform(Partner, TargetId, bDeEvolution, Data, Message)) continue;
        FDigimonAIRivalActivityCounters Delta;
        Delta.Evolutions = bDeEvolution ? 0 : 1;
        Delta.DeEvolutions = bDeEvolution ? 1 : 0;
        Delta.ABIGained = FMath::Max(0, Partner.ABI - BeforeABI);
        Rival.CurrentActivity = Message;
        RecordActivity(Rival, Delta);
        // Transformations reset level. Give that actual owned partner a coherent
        // retraining party and let the next action move it back to a suitable field.
        const FGuid TransformedId = Partner.InstanceId;
        StoreParty(Rival);
        SelectParty(Rival, true, TransformedId);
        return true;
    }
    return false;
}

bool UDigimonVenomNXTAIRivalSubsystem::TryTrain(FDigimonAIRivalRecord& Rival, FRandomStream& Random)
{
    if (Rival.Partners.IsEmpty()) return false;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    const int32 First = Random.RandHelper(Rival.Partners.Num());
    // If one partner is capped, another can still use a training action. No item or
    // credit is consumed until the shared progression helper reports a real gain.
    for (int32 Offset = 0; Offset < Rival.Partners.Num(); ++Offset)
    {
        FDigimonOwnedPartner& Partner = Rival.Partners[(First + Offset) % Rival.Partners.Num()];
        FDigimonSpeciesDefinition Def;
        if (!Data || !Data->GetSpecies(Partner.SpeciesId, Def)) continue;
        const TArray<FDigimonEvolutionOption> Options = DigimonVenomNXTEvolution::GetOptions(Partner, Data, false);
        const FDigimonEvolutionOption* Goal = nullptr;
        for (const FDigimonEvolutionOption& Option : Options)
        {
            if (Option.bDeEvolution || Option.RequiredCAM > 100 ||
                (Option.RequiredLevel > FMath::Clamp(Settings->MaxPartnerLevel, 1, 200) && Partner.Level < Option.RequiredLevel) ||
                (Option.RequiredABI > FMath::Clamp(Settings->MaxABI, 1, 200) && Partner.ABI < Option.RequiredABI)) continue;
            if (!Goal || Option.RequiredABI < Goal->RequiredABI ||
                (Option.RequiredABI == Goal->RequiredABI && Option.RequiredLevel < Goal->RequiredLevel)) Goal = &Option;
        }

        FDigimonOwnedPartner Trained = Partner;
        FName ItemId;
        int64 Cost = 0;
        int32 CAMGain = 0;
        int32 ABIGain = 0;
        if (Goal && Partner.CAM < Goal->RequiredCAM)
        {
            CAMGain = DigimonVenomNXTEvolution::FeedCAM(Trained);
            if (CAMGain > 0) { ItemId = TEXT("digimeat_cam"); Cost = FMath::Max(1, Settings->CAMMeatCreditCost); }
        }
        else if (Goal && Partner.ABI < Goal->RequiredABI)
        {
            ABIGain = DigimonVenomNXTEvolution::FeedABI(Trained);
            if (ABIGain > 0) { ItemId = TEXT("digimeat_abi"); Cost = FMath::Max(1, Settings->ABIMeatCreditCost); }
        }
        else
        {
            const FDigimonStats Stats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats;
            EDigimonTrainingStat Stat = static_cast<EDigimonTrainingStat>(Random.RandRange(0, 5));
            if (Goal)
            {
                const FDigimonEvolutionRequirement& Requirement = Goal->Requirement;
                if (Stats.Attack < Requirement.RequiredAttack) Stat = EDigimonTrainingStat::Attack;
                else if (Stats.Defense < Requirement.RequiredDefense) Stat = EDigimonTrainingStat::Defense;
                else if (Stats.Spirit < Requirement.RequiredSpirit) Stat = EDigimonTrainingStat::Spirit;
                else if (Stats.Speed < Requirement.RequiredSpeed) Stat = EDigimonTrainingStat::Speed;
            }
            if (DigimonVenomNXTEvolution::TryTrain(Trained, Stat))
            {
                ItemId = TEXT("DigiMeat"); Cost = FMath::Max(1, Settings->DigiMeatCreditCost);
            }
            else
            {
                // ABI meat also expands the permanent training budget, even for a fully
                // evolved partner. Existing over-cap legacy training is never removed.
                ABIGain = DigimonVenomNXTEvolution::FeedABI(Trained);
                if (ABIGain > 0) { ItemId = TEXT("digimeat_abi"); Cost = FMath::Max(1, Settings->ABIMeatCreditCost); }
            }
        }
        if (ItemId.IsNone()) continue;
        FDigimonInventoryEntry* Item = Rival.Inventory.FindByPredicate([&](const FDigimonInventoryEntry& Entry)
            { return Entry.ItemId == ItemId && Entry.Quantity > 0; });
        FDigimonAIRivalActivityCounters Delta;
        if (Item) --Item->Quantity;
        else
        {
            if (Rival.Credits < Cost) continue;
            Rival.Credits -= Cost;
            Delta.CreditsSpent = Cost;
            Delta.ItemsPurchased = 1;
        }
        Partner = MoveTemp(Trained);
        Delta.TrainingActions = 1;
        Delta.CAMGained = CAMGain;
        Delta.ABIGained = ABIGain;
        Rival.CurrentActivity = FString::Printf(TEXT("Trained %s using %s"), *Def.DisplayName.ToString(), *ItemId.ToString());
        RecordActivity(Rival, Delta);
        StoreParty(Rival);
        return true;
    }
    return false;
}

void UDigimonVenomNXTAIRivalSubsystem::AwardPartyPresenceCAM(FDigimonAIRivalRecord& Rival, int64 Now)
{
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const int64 Interval = FMath::CeilToInt(FMath::Clamp(Settings->PartyCAMIntervalSeconds, 10.0f, 86400.0f));
    int64* Next = NextPartyCAMUnix.Find(Rival.RivalId);
    if (!Next) { NextPartyCAMUnix.Add(Rival.RivalId, Now + Interval); return; }
    if (Now < *Next) return;
    *Next = Now + Interval; // No burst catch-up for paused rivals or a restarted server.
    const int32 Gain = FMath::Clamp(Settings->PartyCAMGain, 1, 100);
    if (Gain <= 0) return;
    FDigimonAIRivalActivityCounters Delta;
    for (FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        const int32 Before = Partner.CAM;
        Partner.CAM = FMath::Clamp(Partner.CAM + Gain, 0, 100);
        Delta.CAMGained += FMath::Max(0, Partner.CAM - Before);
    }
    if (Delta.CAMGained > 0) { RecordActivity(Rival, Delta); StoreParty(Rival); }
}

void UDigimonVenomNXTAIRivalSubsystem::AwardExperience(FDigimonAIRivalRecord& Rival, int64 Amount, FDigimonAIRivalActivityCounters& Delta)
{
    if (Amount <= 0) return;
    const int32 MaxLevel = GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel;
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    TMap<FGuid, FDigimonOwnedPartner> Awarded;
    for (FDigimonOwnedPartner& Partner : Rival.Partners)
    {
        if (!Partner.IsValid()) continue;
        if (const FDigimonOwnedPartner* AlreadyAwarded = Awarded.Find(Partner.InstanceId))
        {
            // Keep duplicate legacy snapshots synchronized: StoreParty must not
            // overwrite the first rewarded copy with an old second copy.
            Partner = *AlreadyAwarded;
            continue;
        }
        const auto Award = DigimonVenomNXTProgressionCore::Apply(Partner, Amount, MaxLevel,
            [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        Delta.ExperienceGained = DigimonVenomNXTProgressionCore::AddSaturated(Delta.ExperienceGained, Award.GrantedExperience);
        Delta.LevelUps += Award.LevelsGained;
        Rival.TamerLevel = FMath::Max(Rival.TamerLevel, Partner.Level);
        Awarded.Add(Partner.InstanceId, Partner);
    }
}

void UDigimonVenomNXTAIRivalSubsystem::SimulateWildBattle(FDigimonAIRivalRecord& Rival, FRandomStream& Random)
{
    const UDigimonVenomNXTDataSubsystem* Data = GetData();
    const FDigimonMapRow* Map = ExplorationMaps.FindByPredicate([&](const FDigimonMapRow& M) { return M.MapId == Rival.MapId; });
    if (!Data || !Map || Map->WildSpecies.IsEmpty()) { Rival.CurrentActivity = TEXT("Seeking a populated exploration map"); return; }
    const TArray<FName>& Pool = Map->WildSpecies;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const FName SpeciesId = Pool[Random.RandHelper(Pool.Num())];
    FDigimonSpeciesDefinition WildDef;
    if (!Data->GetSpecies(SpeciesId, WildDef) || WildDef.bPlaceholder || !WildDef.bHasNormalArtwork)
    { Rival.CurrentActivity = TEXT("Seeking an available wild encounter"); return; }
    EDigimonVariant Variant = static_cast<EDigimonVariant>(DigimonVenomNXTVariantCore::RollWildVariant(
        Random.FRand(), Settings->ShinyChance, Settings->ParadoxChance, Settings->FirewallChance));
    if (!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Variant), WildDef.bHasNormalArtwork,
        WildDef.bHasParadoxArtwork, WildDef.bHasShinyArtwork, WildDef.bHasFirewallArtwork)) Variant = EDigimonVariant::Normal;
    const int32 MinLevel = FMath::Clamp(Map->RecommendedMinLevel, 1, FMath::Max(1, Settings->MaxPartnerLevel));
    const int32 MaxLevel = FMath::Clamp(Map->RecommendedMaxLevel, MinLevel, FMath::Max(MinLevel, Settings->MaxPartnerLevel));
    FDigimonOwnedPartner Wild = MakePartner(SpeciesId, Variant, Random.RandRange(MinLevel, MaxLevel));
    const TCHAR* WildVariety = Variant == EDigimonVariant::Firewall ? TEXT("Firewall ") :
        Variant == EDigimonVariant::Shiny ? TEXT("Shiny ") :
        Variant == EDigimonVariant::Paradox ? TEXT("Paradox ") : TEXT("");
    const FString WildDisplayName = FString(WildVariety) + WildDef.DisplayName.ToString();
    const TArray<FDigimonOwnedPartner> WildParty = { Wild };
    const FDigimonAutoBattleResult Result = DigimonVenomNXTAutoBattle::Resolve(Rival.Partners, WildParty, Data, Settings->ActiveBattleSize, Random.RandRange(1, MAX_int32), false, true);
    for (const FDigimonBattleUnit& Unit : Result.TeamA)
    {
        FDigimonOwnedPartner* Partner = Rival.Partners.FindByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
        if (Partner) { Partner->CurrentHP = FMath::Max(0, Unit.HP); Partner->CurrentSP = FMath::Max(0, Unit.SP); }
    }
    FDigimonAIRivalActivityCounters Delta;
    Delta.WildBattles = 1;
    Rival.TrainingSessionBattles = FMath::Min(1000, Rival.TrainingSessionBattles + 1);
    if (Result.bDraw)
    {
        Delta.WildDraws = 1;
        ++Rival.ConsecutiveWildLosses;
        Rival.ConsecutiveWildWins = 0;
        Rival.CurrentActivity = FString::Printf(TEXT("Drew against wild %s (Lv.%d)"), *WildDisplayName, Wild.Level);
    }
    else if (Result.bTeamAWon)
    {
        ++Rival.Wins; Delta.WildWins = 1;
        Rival.ConsecutiveWildLosses = 0;
        ++Rival.ConsecutiveWildWins;
        if (Rival.ConsecutiveWildWins >= 5)
        {
            Rival.ExplorationTargetLevel = FMath::Min(PartyTrainingLevel(Rival), FMath::Max(1, Rival.ExplorationTargetLevel) + 2);
            Rival.ConsecutiveWildWins = 0;
        }
        Delta.CreditsEarned = FMath::Max<int64>(10, Wild.Level * 20LL);
        Rival.Credits += Delta.CreditsEarned;
        AwardExperience(Rival, FMath::Max<int64>(50, Wild.Level * 28LL), Delta);
        FDigimonScanRecord* Scan = Rival.Scans.FindByPredicate([&](const FDigimonScanRecord& S) { return S.SpeciesId == SpeciesId && S.Variant == Variant; });
        if (!Scan)
        {
            FDigimonScanRecord NewScan; NewScan.SpeciesId = SpeciesId; NewScan.Variant = Variant;
            Rival.Scans.Add(NewScan); Scan = &Rival.Scans.Last();
        }
        const int32 Before = Scan->Percent;
        Scan->Percent = DigimonVenomNXTScanCore::Gain(Scan->Percent,
            DigimonVenomNXTVariantCore::WildScanGain(static_cast<int32>(Variant), Variant == EDigimonVariant::Normal ? Settings->BaseScanGain : Settings->RareScanGain), Settings->ScanCapPercent);
        DigimonVenomNXTScanCore::Observe(*Scan, Settings->ScanCapPercent);
        Delta.ScanGained = FMath::Max(0, Scan->Percent - Before);
        Rival.CurrentActivity = FString::Printf(TEXT("Won vs wild %s (Lv.%d), +%d%% scan"), *WildDisplayName, Wild.Level, Delta.ScanGained);
    }
    else
    {
        ++Rival.Losses; Delta.WildLosses = 1;
        ++Rival.ConsecutiveWildLosses;
        Rival.ConsecutiveWildWins = 0;
        Rival.CurrentActivity = FString::Printf(TEXT("Lost to wild %s (Lv.%d); regrouping"), *WildDisplayName, Wild.Level);
    }
    RecordActivity(Rival, Delta);
    StoreParty(Rival);
    if (Delta.LevelUps > 0) SelectParty(Rival);
}

void UDigimonVenomNXTAIRivalSubsystem::SimulateRival(FDigimonAIRivalRecord& Rival)
{
    // Memory stays bounded even when global autosaving is disabled for days.
    CompactRival(Rival);
    if (Rival.Partners.IsEmpty()) { NormalizeRival(Rival); if (Rival.Partners.IsEmpty()) return; }
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    FRandomStream Random(static_cast<int32>(GetTypeHash(Rival.RivalId) ^ static_cast<uint32>(Now) ^ (static_cast<uint32>(Rival.LifetimeStats.WildBattles) * 31U)));
    AwardPartyPresenceCAM(Rival, Now);
    Rival.LastSimulatedUnix = Now;
    Rival.NextActionUnix = Now + FMath::Max(5, Settings->AIRivalActionIntervalSeconds);
    bDirty = true;
    if (DigimonVenomNXTRivalTrainingCore::SessionFinished(Rival.TrainingSessionBattles,
        Settings->AIRivalTrainingBattlesPerParty, Rival.TrainingSessionStartLevel, Rival.Partners[0].Level))
    {
        StoreParty(Rival);
        SelectParty(Rival, true);
        if (Rival.Partners.IsEmpty()) return;
        Rival.CurrentActivity = FString::Printf(TEXT("Rotated training party; leader Lv.%d"), Rival.Partners[0].Level);
    }
    Rival.ExplorationTargetLevel = FMath::Clamp(Rival.ExplorationTargetLevel, 1, PartyTrainingLevel(Rival));
    // Move before other work after a party change; a weak new team never fights
    // even one stale encounter in the previous high-level habitat.
    const FDigimonMapRow* CurrentMap = ExplorationMaps.FindByPredicate([&](const FDigimonMapRow& M) { return M.MapId == Rival.MapId; });
    const bool bNeedsMap = !CurrentMap || Rival.ConsecutiveWildLosses >= 3 ||
        !DigimonVenomNXTRivalRules::IsSuitableMap(CurrentMap->RecommendedMinLevel, CurrentMap->RecommendedMaxLevel, Rival.ExplorationTargetLevel);
    const bool bReviewPopulation = Rival.LifetimeStats.WildBattles % FMath::Clamp(Settings->AIRivalMapBalanceReviewActions, 1, 100) == 0;
    if ((bNeedsMap || bReviewPopulation) && TravelToSuitableMap(Rival, Random, Rival.ConsecutiveWildLosses >= 3)) return;
    if (HealPartyIfNeeded(Rival)) return;
    if (TryMaterialize(Rival) || TryEvolve(Rival)) return;
    const int32 Choice = Random.RandRange(0, 99);
    if (Choice < 5)
    {
        if (UGameInstance* GI = GetWorld()->GetGameInstance())
            if (UDigimonVenomNXTRankedSubsystem* Ranked = GI->GetSubsystem<UDigimonVenomNXTRankedSubsystem>())
                if (Ranked->RunRivalQuickMatch(Rival.RivalId)) return;
    }
    if (Choice >= 5 && Choice < 18 && TrySimulateUnranked(Rival, Random)) return;
    if (Choice >= 18 && Choice < 30 && TryTrain(Rival, Random)) return;
    SimulateWildBattle(Rival, Random);
}

void UDigimonVenomNXTAIRivalSubsystem::ForceSimulationStep(int32 MaxRecords)
{
    if (!bLoaded || !HasServerAuthority()) return;
    RefreshActivityWindow(FDateTime::UtcNow().ToUnixTimestamp());
    const int32 Population = GetActiveRivalCount();
    if (Population == 0) return;
    const double Started = FPlatformTime::Seconds();
    RebuildMapPopulation();
    const int32 Count = FMath::Clamp(MaxRecords, 1, FMath::Min(100, Population));
    LiveBattleRivals.Reset();
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        const ADigimonVenomNXTBattleActor* Battle = PC ? PC->CurrentBattle.Get() : nullptr;
        if (Battle && !Battle->State.bFinished && !Battle->PlayerB && (Battle->State.Kind == EDigimonBattleKind::AITamer || Battle->State.Kind == EDigimonBattleKind::Friendly))
            LiveBattleRivals.Add(Battle->BattleContextId);
    }
    const double Budget = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->AIRivalSimulationBudgetMilliseconds, 0.5f, 20.0f) / 1000.0;
    for (int32 Index = 0; Index < Count; ++Index)
    {
        SimulationCursor %= Population;
        FDigimonAIRivalRecord& Rival = SaveData.Rivals[SimulationCursor++];
        if (!LiveBattleRivals.Contains(Rival.RivalId) && Rival.NextActionUnix <= FDateTime::UtcNow().ToUnixTimestamp()) SimulateRival(Rival);
        if (FPlatformTime::Seconds() - Started >= Budget) break;
    }
}
ADigimonVenomNXTMapZone* UDigimonVenomNXTAIRivalSubsystem::FindZone(int32 MapId) const
{
    if (!GetWorld()) return nullptr;
    if (UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>()) return WorldSystem->FindMapZone(MapId);
    return nullptr;
}

void UDigimonVenomNXTAIRivalSubsystem::RefreshVisibleAvatars()
{
    if (!GetWorld()) return;
    TSet<int32> ActiveMaps;
    TSet<FString> Desired;
    for (FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!PC || !PC->IsAccountAuthenticated()) continue;
        const ADigimonVenomNXTBattleActor* Battle = PC->CurrentBattle.Get();
        if (Battle && !Battle->State.bFinished && !Battle->PlayerB && (Battle->State.Kind == EDigimonBattleKind::AITamer || Battle->State.Kind == EDigimonBattleKind::Friendly))
            Desired.Add(Battle->BattleContextId);
        if (PC->IsInDigiFarm() || PC->IsInRelay()) continue;
        if (const ADigimonVenomNXTPlayerState* PS = PC->GetPlayerState<ADigimonVenomNXTPlayerState>()) ActiveMaps.Add(PS->Profile.CurrentMapId);
    }

    const int32 PerMap = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxVisibleAIRivalsPerMap, 1, 200);
    for (const int32 MapId : ActiveMaps)
    {
        ADigimonVenomNXTMapZone* Zone = FindZone(MapId);
        if (!Zone) continue;
        TArray<const FDigimonAIRivalRecord*> Local;
        for (int32 Index = 0; Index < GetActiveRivalCount(); ++Index)
        {
            const FDigimonAIRivalRecord& Rival = SaveData.Rivals[Index];
            if (Rival.MapId == MapId) Local.Add(&Rival);
            if (Local.Num() >= PerMap) break;
        }
        const FVector Center = Zone->PlayBounds ? Zone->PlayBounds->Bounds.Origin : Zone->GetActorLocation();
        const FVector Extent = Zone->PlayBounds ? Zone->PlayBounds->Bounds.BoxExtent : FVector(600,600,50);
        FBox Bounds(Center-Extent, Center+Extent);
        for (int32 i=0; i<Local.Num(); ++i)
        {
            const FDigimonAIRivalRecord& R = *Local[i];
            Desired.Add(R.RivalId);
            ADigimonVenomNXTAIRivalAvatar* Avatar = Avatars.FindRef(R.RivalId).Get();
            if (!Avatar)
            {
                FVector Spawn = Zone->GetPlayerSpawnLocation();
                if (const UDigimonVenomNXTWorldSubsystem* WorldSystem = GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>())
                {
                    for (int32 Attempt = 0; Attempt < 8; ++Attempt)
                    {
                        const FVector Candidate = Center + FVector(FMath::FRandRange(-Extent.X * 0.7f, Extent.X * 0.7f), FMath::FRandRange(-Extent.Y * 0.7f, Extent.Y * 0.7f), 20.0f);
                        if (WorldSystem->IsWorldLocationWalkable(MapId, Candidate)) { Spawn = Candidate; break; }
                    }
                }
                Avatar = GetWorld()->SpawnActor<ADigimonVenomNXTAIRivalAvatar>(ADigimonVenomNXTAIRivalAvatar::StaticClass(), Spawn, FRotator::ZeroRotator);
                if (Avatar) Avatars.Add(R.RivalId, Avatar);
            }
            if (Avatar)
            {
                Avatar->InitializeAvatar(R.RivalId, R.DisplayName, R.MapId, R.TamerLevel, Bounds);
                Avatar->RefreshLeaderFollower(R.Partners.IsEmpty() ? FDigimonOwnedPartner() : R.Partners[0]);
            }
        }
    }

    TArray<FString> Existing;
    Avatars.GetKeys(Existing);
    for (const FString& Id : Existing)
    {
        if (Desired.Contains(Id)) continue;
        if (ADigimonVenomNXTAIRivalAvatar* Avatar = Avatars.FindRef(Id).Get()) Avatar->Destroy();
        Avatars.Remove(Id);
    }
}

bool UDigimonVenomNXTAIRivalSubsystem::BuildBattleTeam(const FString& RivalId, FDigimonBattleTeam& OutTeam) const
{
    FDigimonAIRivalRecord Rival;
    if (!bLoaded || !HasServerAuthority() || !GetRival(RivalId, Rival)) return false;
    OutTeam = FDigimonBattleTeam();
    OutTeam.TrainerName = Rival.DisplayName;
    const int32 ActiveLimit = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, 1, 6);
    for (FDigimonOwnedPartner Partner : Rival.Partners)
    {
        // Challenges/arena use a rested snapshot without healing the expedition party.
        Partner.CurrentHP = MAX_int32; Partner.CurrentSP = MAX_int32;
        FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, GetData());
        if (OutTeam.Active.Num() < ActiveLimit) OutTeam.Active.Add(Unit);
        else OutTeam.Bench.Add(Unit);
    }
    return !OutTeam.Active.IsEmpty();
}

void UDigimonVenomNXTAIRivalSubsystem::RecordBattleResult(const FString& RivalId, bool bRivalWon, int64 VictoryXP, int64 VictoryCredits)
{
    if (!bLoaded || !HasServerAuthority()) return;
    if (FDigimonAIRivalRecord* Rival = FindRivalMutable(RivalId))
    {
        FDigimonAIRivalActivityCounters Delta;
        Delta.TrainerBattles = 1;
        if (bRivalWon)
        {
            ++Rival->Wins; Delta.TrainerWins = 1;
            AwardExperience(*Rival, FMath::Max<int64>(0, VictoryXP), Delta);
            Delta.CreditsEarned = FMath::Max<int64>(0, VictoryCredits);
            Rival->Credits += Delta.CreditsEarned;
            StoreParty(*Rival);
        }
        else { ++Rival->Losses; Delta.TrainerLosses = 1; }
        Rival->CurrentActivity = bRivalWon ? TEXT("Won a tamer challenge") : TEXT("Lost a tamer challenge");
        RecordActivity(*Rival, Delta);
        Save();
    }
}

bool UDigimonVenomNXTAIRivalSubsystem::IsRivalInLiveBattle(const FString& RivalId) const
{
    if (!HasServerAuthority() || !GetWorld()) return true;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        const auto* Battle = PC ? PC->CurrentBattle.Get() : nullptr;
        if (Battle && !Battle->State.bFinished && !Battle->PlayerB && Battle->BattleContextId == RivalId &&
            (Battle->State.Kind == EDigimonBattleKind::Friendly || Battle->State.Kind == EDigimonBattleKind::AITamer)) return true;
    }
    return false;
}

void UDigimonVenomNXTAIRivalSubsystem::RecordUnrankedResult(const FString& RivalId, bool bRivalWon, bool bDraw, bool bPersist)
{
    if (!bLoaded || !HasServerAuthority()) return;
    if (FDigimonAIRivalRecord* Rival = FindRivalMutable(RivalId))
    {
        FDigimonAIRivalActivityCounters Delta;
        Delta.TrainerBattles = 1;
        if (bDraw) Delta.TrainerDraws = 1;
        else if (bRivalWon) { Rival->Wins = Rival->Wins < MAX_int32 ? Rival->Wins + 1 : MAX_int32; Delta.TrainerWins = 1; }
        else { Rival->Losses = Rival->Losses < MAX_int32 ? Rival->Losses + 1 : MAX_int32; Delta.TrainerLosses = 1; }
        Rival->CurrentActivity = bDraw ? TEXT("Drew a live unranked battle") : bRivalWon ? TEXT("Won a live unranked battle") : TEXT("Lost a live unranked battle");
        RecordActivity(*Rival, Delta);
        // No money, items, scans, experience or expedition-party damage from sparring.
        if (bPersist && !Save()) UE_LOG(LogDigimonRivals, Error, TEXT("Unranked rival result awaits the next checkpoint retry."));
    }
}

bool UDigimonVenomNXTAIRivalSubsystem::TrySimulateUnranked(FDigimonAIRivalRecord& Rival, FRandomStream& Random)
{
    const int32 Population = GetActiveRivalCount();
    if (Population < 2 || Rival.Partners.IsEmpty() || !GetData() || LiveBattleRivals.Contains(Rival.RivalId)) return false;
    const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
    const int32 Begin = Random.RandHelper(Population);
    FDigimonAIRivalRecord* Opponent = nullptr;
    for (int32 Offset = 0; Offset < Population; ++Offset)
    {
        FDigimonAIRivalRecord& Candidate = SaveData.Rivals[(Begin + Offset) % Population];
        if (Candidate.RivalId == Rival.RivalId || Candidate.MapId != Rival.MapId || Candidate.Partners.IsEmpty() ||
            Candidate.NextActionUnix > Now || LiveBattleRivals.Contains(Candidate.RivalId)) continue;
        // Habitat and similar party strength produce believable local rival encounters.
        if (FMath::Abs(PartyTrainingLevel(Rival) - PartyTrainingLevel(Candidate)) > FMath::Max(5, PartyTrainingLevel(Rival) / 3)) continue;
        Opponent = &Candidate; break;
    }
    if (!Opponent) return false;
    TArray<FDigimonOwnedPartner> A = Rival.Partners, B = Opponent->Partners;
    for (TArray<FDigimonOwnedPartner>* Team : {&A, &B})
        for (FDigimonOwnedPartner& Partner : *Team) { Partner.CurrentHP = MAX_int32; Partner.CurrentSP = MAX_int32; }
    const auto Result = DigimonVenomNXTAutoBattle::Resolve(A, B, GetData(), GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, Random.RandRange(1, MAX_int32));
    if (Result.TeamA.IsEmpty() || Result.TeamB.IsEmpty()) return false;
    RecordUnrankedResult(Rival.RivalId, Result.bTeamAWon, Result.bDraw, false);
    RecordUnrankedResult(Opponent->RivalId, !Result.bTeamAWon, Result.bDraw, false);
    Rival.CurrentActivity = FString::Printf(TEXT("%s unranked vs %s in habitat %d"), Result.bDraw ? TEXT("Drew") : Result.bTeamAWon ? TEXT("Won") : TEXT("Lost"), *Opponent->DisplayName, Rival.MapId);
    Opponent->CurrentActivity = FString::Printf(TEXT("%s unranked vs %s in habitat %d"), Result.bDraw ? TEXT("Drew") : Result.bTeamAWon ? TEXT("Lost") : TEXT("Won"), *Rival.DisplayName, Rival.MapId);
    // Reserve both simulated participants until their next action; a batch can never
    // repeatedly farm the same defender or race a live human challenge.
    Rival.NextActionUnix = Opponent->NextActionUnix = Now + FMath::Max(45, GetDefault<UDigimonVenomNXTSettings>()->AIRivalActionIntervalSeconds);
    Rival.LastSimulatedUnix = Opponent->LastSimulatedUnix = Now;
    return true;
}

void UDigimonVenomNXTAIRivalSubsystem::RecordRankedResult(const FString& RivalId, bool bRivalWon, bool bDraw)
{
    if (!bLoaded || !HasServerAuthority()) return;
    if (FDigimonAIRivalRecord* Rival = FindRivalMutable(RivalId))
    {
        FDigimonAIRivalActivityCounters Delta;
        Delta.RankedBattles = 1;
        if (bDraw) Delta.RankedDraws = 1;
        else if (bRivalWon) { ++Rival->Wins; Delta.RankedWins = 1; }
        else { ++Rival->Losses; Delta.RankedLosses = 1; }
        Rival->CurrentActivity = bDraw ? TEXT("Drew a ranked arena battle") : bRivalWon ? TEXT("Won a ranked arena battle") : TEXT("Lost a ranked arena battle");
        RecordActivity(*Rival, Delta);
        // Periodic atomic checkpoints batch AI arena activity; no whole-population JSON
        // serialization for every quick-match callback inside a simulation batch.
    }
}

void UDigimonVenomNXTAIRivalSubsystem::Tick(float DeltaTime)
{
    if (!bLoaded || !HasServerAuthority()) return;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    RefreshActivityWindow(FDateTime::UtcNow().ToUnixTimestamp());
    SimulationAccumulator += DeltaTime;
    AvatarRefreshAccumulator += DeltaTime;
    SaveAccumulator = Settings->bEnableGlobalAutosaves ? SaveAccumulator + DeltaTime : 0.0f;
    if (SimulationAccumulator >= FMath::Max(0.25f, Settings->AIRivalSimulationIntervalSeconds))
    {
        SimulationAccumulator = 0.0f;
        ForceSimulationStep(Settings->AIRivalRecordsPerStep);
    }
    if (AvatarRefreshAccumulator >= 3.0f)
    {
        AvatarRefreshAccumulator = 0.0f;
        RefreshVisibleAvatars();
        if (ADigimonVenomNXTGameState* GS = GetWorld()->GetGameState<ADigimonVenomNXTGameState>()) GS->SetPersistentAIRivalCount(GetActiveRivalCount());
    }
    if (Settings->bEnableGlobalAutosaves && SaveAccumulator >= FMath::Max(10.0f, Settings->AIRivalSaveIntervalSeconds))
    {
        SaveAccumulator = 0.0f;
        if (bDirty) Save();
    }
}
