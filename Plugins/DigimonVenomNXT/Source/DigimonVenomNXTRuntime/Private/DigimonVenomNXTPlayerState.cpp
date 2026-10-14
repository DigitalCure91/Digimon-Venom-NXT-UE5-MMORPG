#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTProfileValidation.h"
#include "DigimonVenomNXTServerActivity.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTEvolutionCore.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTStarterCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTRewardCore.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTSeason.h"
#include "Net/UnrealNetwork.h"
#include "Engine/GameInstance.h"
#include "HAL/PlatformTime.h"

ADigimonVenomNXTPlayerState::ADigimonVenomNXTPlayerState()
{
    bReplicates = true;
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1.0f;
    SetNetUpdateFrequency(4.0f);
}

void ADigimonVenomNXTPlayerState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Only actual online presence counts. Travel, disconnects and boxed partners never earn catch-up CAM.
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || !GetPawn()) return;
    const ADigimonVenomNXTPlayerController* Session = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    if (!Session || !Session->IsAccountAuthenticated() || Session->IsLogoutPending()) return;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    const float Interval = FMath::Clamp(S->PartyCAMIntervalSeconds, 10.0f, 86400.0f);
    const float Elapsed = FMath::Clamp(DeltaSeconds, 0.0f, 5.0f);
    for (auto It = PartyCAMElapsed.CreateIterator(); It; ++It)
        if (!Profile.Party.Contains(It.Key())) It.RemoveCurrent();
    bool bChanged = false;
    TSet<FGuid> Seen;
    for (const FGuid& Id : Profile.Party)
    {
        if (Seen.Contains(Id)) continue;
        Seen.Add(Id);
        FDigimonOwnedPartner* Partner = FindPartnerMutable(Id);
        if (!Partner || Partner->CAM >= 100) { PartyCAMElapsed.Remove(Id); continue; }
        float& Time = PartyCAMElapsed.FindOrAdd(Id);
        Time += Elapsed;
        if (Time < Interval) continue;
        Time = FMath::Fmod(Time, Interval);
        Partner->CAM = FMath::Min(100, FMath::Max(0, Partner->CAM) + FMath::Clamp(S->PartyCAMGain, 1, 100));
        bChanged = true;
    }
    if (bChanged) MarkProfileChanged();
}

void ADigimonVenomNXTPlayerState::NotifyProgression(const FString& Title, const FString& Message) const
{
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner()))
        Controller->ClientShowMessage(Title, Message);
}

void ADigimonVenomNXTPlayerState::NotifyProgression(const FString& Title, const FString& Message, EDigimonAudioCue Cue) const
{
    NotifyProgression(Title, Message);
    DigimonVenomNXTServerActivity::Record(this, TEXT("Progression"), Title, Message,
        Cue == EDigimonAudioCue::Error ? TEXT("Warning") : TEXT("Info"));
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner()))
        Controller->ClientPlayAudioCue(Cue, FGuid::NewGuid());
}

void ADigimonVenomNXTPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerState, ScanPolicy, COND_OwnerOnly);
    DOREPLIFETIME(ADigimonVenomNXTPlayerState, PublicSnapshot);
}

void ADigimonVenomNXTPlayerState::OnRep_Profile()
{
    OnProfileChanged.Broadcast();
}

void ADigimonVenomNXTPlayerState::InitializeServerProfile(const FDigimonPlayerProfile& InProfile)
{
    if (!HasAuthority()) return;
    Profile = InProfile;
    InitializedServerAccountId = InProfile.AccountId;
    const bool bCampaignMigrated = DigimonVenomNXTCampaign::Reconcile(Profile);
    RefreshScanPolicy();
    // Old saves gain a private home automatically without changing their location.
    // Keep real resident identities; discard duplicates and missing collection IDs.
    TSet<FGuid> ResidentsSeen;
    Profile.DigiFarmResidents.RemoveAll([&](const FGuid& Id)
    {
        if (!Id.IsValid() || ResidentsSeen.Contains(Id) || !FindPartnerMutable(Id)) return true;
        ResidentsSeen.Add(Id);
        return false;
    });
    Profile.Farm.Version = 1;
    PartyCAMElapsed.Reset();
    SetPlayerName(Profile.Username);
    // Migrate vitals before any recovery or progression writes new-stat maxima.
    ReconcileCombatBalance();
    // Repair profiles saved by older builds after a wipeout before gameplay resumes.
    RecoverDefeatedParty();
    // Recover the entire exhausted party before the starter-only correction heals it.
    UpgradeLegacyStarter();
    ReconcileProgression();
    const bool bDexMigrated = ReconcileDigiDexHistory();
    if (bDexMigrated || bCampaignMigrated)
        if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr)
            if (!Profiles->SaveProfile(Profile))
                UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist profile migration for %s; autosave will retry."), *GetPlayerName());
    RefreshPublicSnapshot();
    ForceNetUpdate();
}

bool ADigimonVenomNXTPlayerState::ApplyOwnerProfileSnapshot(const FDigimonPlayerProfile& InProfile, const FString& ExpectedAccountId)
{
    FString Error;
    if (HasAuthority() || !DigimonVenomNXTProfileValidation::Validate(InProfile, ExpectedAccountId, Error)) return false;
    Profile = InProfile;
    OnRep_Profile();
    return true;
}

void ADigimonVenomNXTPlayerState::MarkProfileChanged()
{
    if (!HasAuthority()) return;
    DigimonVenomNXTCampaign::Reconcile(Profile);
    RefreshScanPolicy();
    // A saved battle defers collection migration until its normalized units settle.
    ReconcileCombatBalance();
    // A saved Season battle may have deferred the login correction until settlement.
    UpgradeLegacyStarter();
    ReconcileProgression();
    ReconcileDigiDexHistory();
    RefreshPublicSnapshot();
    ForceNetUpdate();
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetPawn()))
    {
        Tamer->RefreshFollowerFromProfile();
    }
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner()))
        Controller->QueueOwnerProfileSynchronization();
    OnProfileChanged.Broadcast();
}

bool ADigimonVenomNXTPlayerState::GetPartner(FGuid InstanceId, FDigimonOwnedPartner& OutPartner) const
{
    for (const FDigimonOwnedPartner& Partner : Profile.Collection)
    {
        if (Partner.InstanceId == InstanceId) { OutPartner = Partner; return true; }
    }
    return false;
}

FDigimonOwnedPartner* ADigimonVenomNXTPlayerState::FindPartnerMutable(const FGuid& InstanceId)
{
    for (FDigimonOwnedPartner& Partner : Profile.Collection) if (Partner.InstanceId == InstanceId) return &Partner;
    return nullptr;
}

bool ADigimonVenomNXTPlayerState::HasActiveBattle() const
{
    // A saved Season decision remains locked even before its actor has been restored.
    if (!Profile.WorldBattleCheckpointJson.IsEmpty() || !Profile.Season.BattleCheckpointJson.IsEmpty() || DigimonVenomNXTCampaign::HasPendingBattle(Profile)) return true;
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    return Controller && (IsValid(Controller->CurrentBattle.Get()) && !Controller->CurrentBattle->State.bFinished);
}

FDigimonScanRecord* ADigimonVenomNXTPlayerState::FindScanMutable(FName SpeciesId, EDigimonVariant Variant)
{
    for (FDigimonScanRecord& Scan : Profile.Scans)
    {
        if (Scan.SpeciesId == SpeciesId && Scan.Variant == Variant) return &Scan;
    }
    return nullptr;
}

FDigimonInventoryEntry* ADigimonVenomNXTPlayerState::FindInventoryMutable(FName ItemId)
{
    if (ItemId.IsNone()) return nullptr;
    return Profile.Inventory.FindByPredicate([ItemId](const FDigimonInventoryEntry& Entry)
    {
        return Entry.ItemId == ItemId;
    });
}

int32 ADigimonVenomNXTPlayerState::GetScanPercent(FName SpeciesId, EDigimonVariant Variant) const
{
    for (const FDigimonScanRecord& Scan : Profile.Scans)
    {
        if (Scan.SpeciesId == SpeciesId && Scan.Variant == Variant) return Scan.Percent;
    }
    return 0;
}

bool ADigimonVenomNXTPlayerState::ReconcileCombatBalance()
{
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || HasActiveBattle()) return false;
    UGameInstance* GI = GetGameInstance();
    UDigimonVenomNXTProfileSubsystem* Profiles = GI ? GI->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Profiles || !Data) return false;
    FDigimonPlayerProfile Candidate = Profile;
    if (!UDigimonVenomNXTProfileSubsystem::ReconcileCombatBalance(Candidate, Data)) return false;
    if (!Profiles->SaveProfile(Candidate))
    {
        UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist combat migration for %s; retrying after the next profile update."), *GetPlayerName());
        return false;
    }
    Profile = MoveTemp(Candidate);
    return true;
}

bool ADigimonVenomNXTPlayerState::UpgradeLegacyStarter()
{
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || Profile.Collection.IsEmpty() ||
        Profile.StarterBalanceVersion >= DigimonVenomNXTStarterCore::BalanceVersion || HasActiveBattle()) return false;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data) return false;
    FDigimonOwnedPartner& Starter = Profile.Collection[0];
    FDigimonSpeciesDefinition Def;
    if (!Data->GetSpecies(Starter.SpeciesId, Def)) return false;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const bool bChanged = DigimonVenomNXTStarterCore::UpgradeLegacyStarter(Starter, Profile.StarterBalanceVersion,
        Settings->StarterLevel, Settings->MaxPartnerLevel,
        Starter.IsValid() && !Def.bPlaceholder && Def.Stage == EDigimonStage::Rookie && Starter.Variant == EDigimonVariant::Normal,
        false, [Data](const FDigimonOwnedPartner& Partner) { return DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats; });
    if (bChanged)
        if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>())
            if (!Profiles->SaveProfile(Profile))
                UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist starter correction for %s; autosave will retry."), *GetPlayerName());
    return bChanged;
}

bool ADigimonVenomNXTPlayerState::ReconcileProgression()
{
    // Never change stats underneath a live/saved battle. MarkProfileChanged retries
    // after settlement, and the Season award is reconciled inside its transaction.
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || HasActiveBattle()) return false;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data) return false;
    const int32 MaxLevel = GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel;
    bool bChanged = false;
    for (FDigimonOwnedPartner& Partner : Profile.Collection)
    {
        if (!Partner.IsValid()) continue;
        const auto Result = DigimonVenomNXTProgressionCore::Apply(Partner, 0, MaxLevel,
            [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        bChanged |= Result.Changed;
    }
    if (bChanged)
        if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>())
            if (!Profiles->SaveProfile(Profile))
                UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist XP/level correction for %s; autosave will retry."), *GetPlayerName());
    return bChanged;
}

FDigimonOwnedPartner ADigimonVenomNXTPlayerState::MakePartner(FName SpeciesId, EDigimonVariant Variant, int32 InitialLevel) const
{
    FDigimonOwnedPartner Partner;
    Partner.InstanceId = FGuid::NewGuid();
    Partner.SpeciesId = SpeciesId;
    Partner.Variant = Variant;
    Partner.CAM = 0;
    Partner.ABI = 0;
    Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    DigimonVenomNXTStarterCore::InitializeLevel(Partner, InitialLevel, Settings->MaxPartnerLevel,
        [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
    Partner.Moves = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Moves;
    return Partner;
}

bool ADigimonVenomNXTPlayerState::ReconcileDigiDexHistory()
{
    if (!HasAuthority() || Profile.AccountId.IsEmpty()) return false;
    const int32 Cap = GetDefault<UDigimonVenomNXTSettings>()->ScanCapPercent;
    bool bChanged = false;
    for (FDigimonScanRecord& Scan : Profile.Scans)
        bChanged |= DigimonVenomNXTScanCore::Observe(Scan, Cap);
    // Migration can only infer forms present in the old save. Never invent old conversions.
    for (const FDigimonOwnedPartner& Partner : Profile.Collection)
    {
        if (!Partner.IsValid()) continue;
        FDigimonScanRecord* Scan = FindScanMutable(Partner.SpeciesId, Partner.Variant);
        if (!Scan)
        {
            FDigimonScanRecord NewScan;
            NewScan.SpeciesId = Partner.SpeciesId;
            NewScan.Variant = Partner.Variant;
            Profile.Scans.Add(NewScan);
            Scan = &Profile.Scans.Last();
            bChanged = true;
        }
        bChanged |= DigimonVenomNXTScanCore::Observe(*Scan, Cap, true);
    }
    return bChanged;
}

void ADigimonVenomNXTPlayerState::RefreshScanPolicy()
{
    if (!HasAuthority()) return;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    ScanPolicy.ScanCapPercent = DigimonVenomNXTScanCore::Cap(Settings->ScanCapPercent);
    ScanPolicy.MaterializeRequirementPercent = DigimonVenomNXTScanCore::Requirement(Settings->MaterializeRequirementPercent, Settings->ScanCapPercent);
    ScanPolicy.bConsumeScanOnMaterialize = Settings->bConsumeScanOnMaterialize;
    ScanPolicy.MaxPartySize = FMath::Clamp(Settings->MaxPartySize, 1, 6);
    ScanPolicy.MaxFarmResidents = FMath::Clamp(Settings->MaxFarmResidents, 1, 500);
}

void ADigimonVenomNXTPlayerState::ServerChooseStarter_Implementation(FName SpeciesId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    if (Profile.Collection.Num() > 0 || SpeciesId.IsNone()) return;
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonSpeciesDefinition Def;
    if (!Data || !Data->GetSpecies(SpeciesId, Def) || Def.bPlaceholder || Def.Stage != EDigimonStage::Rookie) return;
    FDigimonOwnedPartner Starter = MakePartner(SpeciesId, EDigimonVariant::Normal, GetDefault<UDigimonVenomNXTSettings>()->StarterLevel);
    Profile.Collection.Add(Starter);
    Profile.Party.Add(Starter.InstanceId);
    Profile.StarterBalanceVersion = DigimonVenomNXTStarterCore::BalanceVersion;
    MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Party"), TEXT("Starter chosen"), FString::Printf(TEXT("%s | level %d | applied; normal save policy"), *SpeciesId.ToString(), Starter.Level));
}

void ADigimonVenomNXTPlayerState::ServerSetParty_Implementation(const TArray<FGuid>& NewParty)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty() || HasActiveBattle()) return;
    const int32 MaxParty = GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize;
    if (NewParty.Num() < 1 || NewParty.Num() > MaxParty) return;
    TSet<FGuid> Unique;
    for (const FGuid& Id : NewParty)
    {
        if (!FindPartnerMutable(Id) || Unique.Contains(Id)) return;
        Unique.Add(Id);
    }
    Profile.Party = NewParty;
    MarkProfileChanged();
    FString Lineup;
    for (const FGuid& Id : Profile.Party)
        if (const FDigimonOwnedPartner* Partner = FindPartnerMutable(Id))
            Lineup += FString::Printf(TEXT("%s%s Lv.%d"), Lineup.IsEmpty() ? TEXT("") : TEXT(", "), *Partner->SpeciesId.ToString(), Partner->Level);
    DigimonVenomNXTServerActivity::Record(this, TEXT("Party"), TEXT("Lineup changed"), Lineup + TEXT(" | applied; normal save policy"));
}

void ADigimonVenomNXTPlayerState::ServerSetTamerStyle_Implementation(FName TamerStyleId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || !Controller || !Controller->IsAccountAuthenticated()) return;
    if (!DigimonVenomNXTTamers::IsValidStyle(TamerStyleId))
    { NotifyProgression(TEXT("Tamer style unavailable"), TEXT("Choose one of the 64 styles in the Tamer Studio."), EDigimonAudioCue::Error); return; }
    if (Profile.TamerStyleId == TamerStyleId)
    { NotifyProgression(TEXT("Tamer style saved"), TEXT("This is already your saved tamer style."), EDigimonAudioCue::Confirm); return; }
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    FDigimonPlayerProfile Candidate = Profile;
    Candidate.TamerStyleId = TamerStyleId;
    DigimonVenomNXTSeason::ReconcileTamerStyles(Candidate);
    // Commit before publishing either the owner profile or the public character.
    // Cosmetics stay independent of teams, currencies and saved battle decisions.
    if (!Profiles || !Profiles->SaveProfile(Candidate))
    { NotifyProgression(TEXT("Tamer style could not be saved"), TEXT("Your previous style is still equipped. Please try again."), EDigimonAudioCue::Error); return; }
    Profile = MoveTemp(Candidate);
    RefreshPublicSnapshot();
    ForceNetUpdate();
    OnProfileChanged.Broadcast();
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetPawn())) Tamer->RefreshTamerStyleFromProfile();
    NotifyProgression(TEXT("Tamer style saved"), FString::Printf(TEXT("%s is now your tamer style."), *DigimonVenomNXTTamers::DisplayName(TamerStyleId)), EDigimonAudioCue::Confirm);
}

void ADigimonVenomNXTPlayerState::ServerMaterialize_Implementation(FName SpeciesId, EDigimonVariant Variant)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    if (!HasAuthority() || Profile.AccountId.IsEmpty() || !Controller || !Controller->IsAccountAuthenticated()) return;
    RefreshScanPolicy();
    if (HasActiveBattle())
    { NotifyProgression(TEXT("DigiDex"), TEXT("Finish the current battle before materializing a Digimon."), EDigimonAudioCue::Error); return; }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonSpeciesDefinition Def;
    if (!Data || !Data->GetSpecies(SpeciesId, Def) || Def.bPlaceholder ||
        !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Variant), Def.bHasNormalArtwork, Def.bHasParadoxArtwork, Def.bHasShinyArtwork, Def.bHasFirewallArtwork))
    { NotifyProgression(TEXT("DigiDex"), TEXT("That Digimon form is not available for materialization."), EDigimonAudioCue::Error); return; }
    FDigimonScanRecord* Scan = FindScanMutable(SpeciesId, Variant);
    const auto Result = DigimonVenomNXTScanCore::Materialize(Scan ? Scan->Percent : 0,
        ScanPolicy.MaterializeRequirementPercent, ScanPolicy.ScanCapPercent, ScanPolicy.bConsumeScanOnMaterialize);
    if (!Scan || !Result.Ready)
    { NotifyProgression(TEXT("More scan data needed"), FString::Printf(TEXT("This form has %d%% scan. Materialization requires %d%%."), Result.ScanPercent, Result.Requirement), EDigimonAudioCue::Error); return; }
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Profiles)
    { NotifyProgression(TEXT("Materialization unavailable"), TEXT("The account save service is unavailable. Your scan data has not been spent."), EDigimonAudioCue::Error); return; }
    FDigimonOwnedPartner Partner = MakePartner(SpeciesId, Variant, 1);
    Partner.ABI = Result.BonusABI;
    const FDigimonStats MaterializedStats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats;
    Partner.CurrentHP = MaterializedStats.MaxHP;
    Partner.CurrentSP = MaterializedStats.MaxSP;
    // Collection is the permanent owner ledger. Full party AND farm still safely keep the partner there.
    const bool bJoinParty = Profile.Party.Num() < ScanPolicy.MaxPartySize;
    const bool bJoinFarm = !bJoinParty && Profile.DigiFarmResidents.Num() < ScanPolicy.MaxFarmResidents;
    const bool bSaved = DigimonVenomNXTScanCore::Commit(Profile, [&](FDigimonPlayerProfile& Candidate)
    {
        DigimonVenomNXTScanCore::Observe(*Scan, ScanPolicy.ScanCapPercent, true);
        Scan->Percent = Result.RemainingPercent;
        if (ScanPolicy.bConsumeScanOnMaterialize) Scan->FractionalHundredths = 0;
        if (Scan->Materializations < MAX_int32) ++Scan->Materializations;
        // A materialized partner is not an old starter eligible for the level-five repair.
        if (Candidate.Collection.IsEmpty()) Candidate.StarterBalanceVersion = DigimonVenomNXTStarterCore::BalanceVersion;
        Candidate.Collection.Add(Partner);
        if (bJoinParty) Candidate.Party.Add(Partner.InstanceId);
        else if (bJoinFarm) Candidate.DigiFarmResidents.Add(Partner.InstanceId);
        ReconcileDigiDexHistory();
    }, [Profiles](const FDigimonPlayerProfile& Candidate) { return Profiles->SaveProfile(Candidate); });
    if (!bSaved)
    { NotifyProgression(TEXT("Materialization save failed"), TEXT("Your scan data, party and collection are unchanged. Please try again."), EDigimonAudioCue::Error); return; }
    MarkProfileChanged();
    const TCHAR* Destination = bJoinParty ? TEXT("your party") : bJoinFarm ? TEXT("your DigiFarm") : TEXT("your collection (party and farm are full)");
    const TCHAR* Form = Variant == EDigimonVariant::Paradox ? TEXT("Paradox ") : Variant == EDigimonVariant::Shiny ? TEXT("Shiny ") : Variant == EDigimonVariant::Firewall ? TEXT("Firewall ") : TEXT("");
    NotifyProgression(TEXT("Digimon materialized"), FString::Printf(TEXT("%s%s joined %s at level 1 with %d permanent ABI. %d%% scan remains."),
        Form, *Def.DisplayName.ToString(), Destination, Partner.ABI, Result.RemainingPercent), EDigimonAudioCue::Confirm);
}

void ADigimonVenomNXTPlayerState::ServerHealAll_Implementation()
{
    ProcessDigiLabHeal(FGuid::NewGuid(), true);
}

void ADigimonVenomNXTPlayerState::ServerRequestDigiLabHeal_Implementation(FGuid RequestId)
{
    ProcessDigiLabHeal(RequestId, false);
}

void ADigimonVenomNXTPlayerState::ClientDigiLabHealResult_Implementation(const FDigimonHealReceipt& Receipt)
{
    OnDigiLabHealResult.Broadcast(Receipt);
}

void ADigimonVenomNXTPlayerState::ProcessDigiLabHeal(const FGuid& RequestId, bool bLegacyRequest)
{
    if (!HasAuthority()) return;
    // Replaying a request returns its original result, never another heal after a later battle.
    if (const FDigimonHealReceipt* Previous = RecentDigiLabHealReceipts.FindByPredicate(
        [&](const FDigimonHealReceipt& Entry) { return Entry.RequestId == RequestId; }))
    {
        ClientDigiLabHealResult(*Previous);
        return;
    }
    FDigimonHealReceipt Receipt;
    Receipt.RequestId = RequestId;
    const auto Respond = [&]()
    {
        if (RequestId.IsValid())
        {
            if (RecentDigiLabHealReceipts.Num() >= 16) RecentDigiLabHealReceipts.RemoveAt(0);
            RecentDigiLabHealReceipts.Add(Receipt);
        }
        DigimonVenomNXTServerActivity::Record(this, TEXT("DigiLab"), Receipt.bSuccess ? TEXT("Recovery saved") : TEXT("Recovery rejected"),
            Receipt.Message, Receipt.bSuccess ? TEXT("Info") : TEXT("Warning"));
        ClientDigiLabHealResult(Receipt);
        if (bLegacyRequest) NotifyProgression(TEXT("DigiLab recovery"), Receipt.Message, !Receipt.bSuccess ? EDigimonAudioCue::Error : Receipt.RestoredPartners > 0 ? EDigimonAudioCue::Heal : EDigimonAudioCue::Confirm);
    };
    ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    if (!RequestId.IsValid() || Profile.AccountId.IsEmpty() || !Controller || !Controller->IsAccountAuthenticated())
    {
        Receipt.Message = TEXT("Sign in to your tamer account before using DigiLab recovery.");
        Respond(); return;
    }
    FString ModerationError;
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this, &ModerationError))
    {
        Receipt.Message = ModerationError.IsEmpty() ? TEXT("Recovery is unavailable for this account.") : ModerationError;
        Respond(); return;
    }
    if (HasActiveBattle())
    {
        Receipt.Message = TEXT("Finish or resume your current battle before healing. No partner was changed.");
        Respond(); return;
    }
    const double Now = FPlatformTime::Seconds();
    if (Now - LastDigiLabHealRequestTime < 0.5)
    {
        Receipt.Message = TEXT("Recovery is processing. Please wait a moment before trying again.");
        Respond(); return;
    }
    LastDigiLabHealRequestTime = Now;
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Data || !Profiles)
    {
        Receipt.Message = TEXT("The recovery service is unavailable. Your partners are unchanged; please try again.");
        Respond(); return;
    }
    // Capture the existing private location without travelling or changing campaign selection.
    Controller->CaptureDigiFarmPosition();
    Controller->CaptureRelayPosition();
    FDigimonPlayerProfile Candidate = Profile;
    TArray<FDigimonHealedPartner> ChangedParty;
    int32 Restored = 0;
    for (FDigimonOwnedPartner& Partner : Candidate.Collection)
    {
        FDigimonSpeciesDefinition Definition;
        if (!Data->GetSpecies(Partner.SpeciesId, Definition))
        {
            Receipt.Message = TEXT("A partner's species data is unavailable. No healing was applied; please try again.");
            Respond(); return;
        }
        DigimonVenomNXTAutoBattle::MigratePartner(Partner, Data);
        const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
        const int32 MaxHP = FMath::Max(1, Unit.Stats.MaxHP);
        const int32 MaxSP = FMath::Max(0, Unit.Stats.MaxSP);
        const int32 BeforeHP = FMath::Clamp(Partner.CurrentHP, 0, MaxHP);
        const int32 BeforeSP = FMath::Clamp(Partner.CurrentSP, 0, MaxSP);
        if (BeforeHP < MaxHP || BeforeSP < MaxSP)
        {
            ++Restored;
            const int32 PartyIndex = Candidate.Party.IndexOfByKey(Partner.InstanceId);
            if (PartyIndex >= 0 && PartyIndex < 6 && ChangedParty.Num() < 6)
            {
                FDigimonHealedPartner Change;
                Change.InstanceId = Partner.InstanceId;
                Change.BeforeHP = BeforeHP; Change.BeforeSP = BeforeSP;
                Change.AfterHP = MaxHP; Change.AfterSP = MaxSP;
                Change.MaxHP = MaxHP; Change.MaxSP = MaxSP;
                ChangedParty.Add(Change);
            }
        }
        Partner.CurrentHP = MaxHP;
        Partner.CurrentSP = MaxSP;
        Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    }
    // Never advertise recovered vitals, or emit recovery effects, before durable acceptance.
    Candidate.DigiLabRecoveryRevision = FMath::Clamp<int64>(Candidate.DigiLabRecoveryRevision, 0, MAX_int64 - 1) + 1;
    if (!Profiles->SaveProfile(Candidate))
    {
        Receipt.Message = TEXT("Recovery could not be saved. Your partners are unchanged. Please try again.");
        Respond(); return;
    }
    Profile = MoveTemp(Candidate);
    RefreshPublicSnapshot();
    ForceNetUpdate();
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(GetPawn())) Tamer->RefreshFollowerFromProfile();
    OnProfileChanged.Broadcast();
    Receipt.bSuccess = true;
    Receipt.RecoveryRevision = Profile.DigiLabRecoveryRevision;
    Receipt.RestoredPartners = Restored;
    Receipt.PartyChanges = MoveTemp(ChangedParty);
    Receipt.Message = Restored > 0
        ? FString::Printf(TEXT("Recovery complete. %d partner%s restored to full HP and SP — free of charge."), Restored, Restored == 1 ? TEXT("") : TEXT("s"))
        : TEXT("All partners are already fully restored.");
    Respond();
}

void ADigimonVenomNXTPlayerState::ServerFeedABIMeat_Implementation(FGuid InstanceId, EDigimonCurrency Currency)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    if (HasActiveBattle()) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Finish the current battle before feeding your Digimon."), EDigimonAudioCue::Error); return; }
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonShopItemDefinition Item;
    if (!Data || !Data->GetShopItem(TEXT("digimeat_abi"), Item)) return;
    FDigimonPlayerProfile Candidate = Profile;
    FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&](const FDigimonOwnedPartner& P) { return P.InstanceId == InstanceId; });
    if (!Partner) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Select a Digimon from your collection."), EDigimonAudioCue::Error); return; }
    if (Partner->ABI >= DigimonVenomNXTEvolutionCore::MaximumABI(GetDefault<UDigimonVenomNXTSettings>()->MaxABI))
    { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("This Digimon has reached the ABI limit. Nothing was spent."), EDigimonAudioCue::Error); return; }
    if (Currency == EDigimonCurrency::Credits)
    {
        if (Candidate.Credits < Item.CreditCost) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Not enough credits."), EDigimonAudioCue::Error); return; }
        Candidate.Credits -= Item.CreditCost;
    }
    else if (Currency == EDigimonCurrency::DigiRubies)
    {
        if (Candidate.DigiRubies < Item.DigiRubyCost) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Not enough DigiRubies."), EDigimonAudioCue::Error); return; }
        Candidate.DigiRubies -= Item.DigiRubyCost;
    }
    else return;
    const int32 Gain = DigimonVenomNXTEvolution::FeedABI(*Partner);
    const int32 ABI = Partner->ABI;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Candidate))
    { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Feeding could not be saved. Nothing was spent; please try again."), EDigimonAudioCue::Error); return; }
    Profile = MoveTemp(Candidate);
    MarkProfileChanged();
    NotifyProgression(TEXT("Permanent ABI increased"), FString::Printf(TEXT("+%d ABI. Total ABI: %d."), Gain, ABI), EDigimonAudioCue::Item);
}

void ADigimonVenomNXTPlayerState::ServerConvertDigiRubiesToCredits_Implementation(int32 RubyAmount)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty() || HasActiveBattle()) return;
    if (RubyAmount <= 0 || Profile.DigiRubies < RubyAmount) return;
    const int64 Rate = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby, 1, 100000);
    const int64 CreditsToAdd = static_cast<int64>(RubyAmount) * Rate;
    if (Profile.Credits < 0 || Profile.Credits > DigimonVenomNXTRewardCore::MaxCredits - CreditsToAdd)
    { NotifyProgression(TEXT("Currency exchange"), TEXT("Your credit balance cannot hold this exchange. Nothing was spent."), EDigimonAudioCue::Error); return; }
    FDigimonPlayerProfile Candidate = Profile;
    Candidate.DigiRubies -= RubyAmount;
    Candidate.Credits += CreditsToAdd;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Candidate))
    { NotifyProgression(TEXT("Currency exchange"), TEXT("The exchange could not be saved. Nothing was spent; please try again."), EDigimonAudioCue::Error); return; }
    Profile = MoveTemp(Candidate);
    MarkProfileChanged();
    NotifyProgression(TEXT("Currency exchanged"), FString::Printf(TEXT("%d DigiRubies exchanged for %lld credits."), RubyAmount, static_cast<long long>(CreditsToAdd)), EDigimonAudioCue::Purchase);
    DigimonVenomNXTServerActivity::Record(this, TEXT("Economy"), TEXT("Currency converted"), FString::Printf(TEXT("%d DigiRubies -> %lld credits | saved"), RubyAmount, static_cast<long long>(CreditsToAdd)));
}

void ADigimonVenomNXTPlayerState::AwardScan(FName SpeciesId, EDigimonVariant Variant, int32 BaseAmount, bool bAllowMasteryBonus)
{
    if (!HasAuthority() || SpeciesId.IsNone()) return;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    const int32 Base = FMath::Clamp(BaseAmount, 0, 999);
    const bool bMastery = bAllowMasteryBonus &&
        ((Variant == EDigimonVariant::Firewall && Profile.Relay.bFirewallScanMastery) ||
         (Variant == EDigimonVariant::Paradox && Profile.Chronicles.bParadoxScanMastery) ||
         (Variant == EDigimonVariant::Shiny && Profile.GhostLine.bShinyScanMastery));
    const int32 GainHundredths = Base * 100 + (bMastery ? DigimonVenomNXTRewardCore::MasteryHundredths(Base) : 0);
    if (GainHundredths <= 0) return;
    FDigimonScanRecord* Scan = FindScanMutable(SpeciesId, Variant);
    if (!Scan)
    {
        FDigimonScanRecord NewScan; NewScan.SpeciesId = SpeciesId; NewScan.Variant = Variant; NewScan.Percent = 0;
        Profile.Scans.Add(NewScan);
        Scan = &Profile.Scans.Last();
    }
    const int32 PreviousPercent = Scan->Percent;
    const int32 Total = DigimonVenomNXTRewardCore::ScanHundredthsAfter(Scan->Percent, Scan->FractionalHundredths, GainHundredths, S->ScanCapPercent);
    Scan->Percent = Total / 100;
    Scan->FractionalHundredths = Total % 100;
    DigimonVenomNXTScanCore::Observe(*Scan, S->ScanCapPercent);
    const int32 CurrentPercent = Scan->Percent;
    MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Rewards"), TEXT("Scan applied"), FString::Printf(TEXT("%s | %s | +%d%% -> %d%% | settlement save follows"), *SpeciesId.ToString(), DigimonVenomNXTServerActivity::VarietyName(Variant), CurrentPercent - PreviousPercent, CurrentPercent));
}

void ADigimonVenomNXTPlayerState::AwardCredits(int64 Amount)
{
    if (!HasAuthority() || Amount <= 0) return;
    Profile.Credits = DigimonVenomNXTRewardCore::CreditTotal(Profile.Credits, Amount);
    MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Economy"), TEXT("Credits applied"), FString::Printf(TEXT("+%lld | balance %lld | settlement save follows"), static_cast<long long>(Amount), static_cast<long long>(Profile.Credits)));
}

void ADigimonVenomNXTPlayerState::AwardDigiRubies(int32 Amount)
{
    if (!HasAuthority() || Amount <= 0) return;
    Profile.DigiRubies = FMath::Max(0, Profile.DigiRubies) + FMath::Min(Amount, MAX_int32 - FMath::Max(0, Profile.DigiRubies));
    MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("Economy"), TEXT("DigiRubies applied"), FString::Printf(TEXT("+%d | balance %d | settlement save follows"), Amount, Profile.DigiRubies));
}

void ADigimonVenomNXTPlayerState::SetCurrentMap(int32 MapId)
{
    if (!HasAuthority()) return;
    Profile.CurrentMapId = FMath::Max(1, MapId);
    MarkProfileChanged();
}

void ADigimonVenomNXTPlayerState::RefreshPublicSnapshot()
{
    PublicSnapshot.AccountId = Profile.AccountId;
    PublicSnapshot.UnrankedWins = Profile.UnrankedWins;
    PublicSnapshot.UnrankedLosses = Profile.UnrankedLosses;
    PublicSnapshot.UnrankedDraws = Profile.UnrankedDraws;
    PublicSnapshot.Username = Profile.Username;
    PublicSnapshot.EquippedTitle = Profile.EquippedTitle;
    PublicSnapshot.TamerStyleId = Profile.TamerStyleId;
    PublicSnapshot.bInDigiFarm = Profile.Farm.bInside;
    PublicSnapshot.bInRelay = DigimonVenomNXTCampaign::IsActive(Profile);
    PublicSnapshot.MapId = (Profile.Farm.bInside || DigimonVenomNXTCampaign::IsActive(Profile)) ? INDEX_NONE : Profile.CurrentMapId;
    PublicSnapshot.LeadSpeciesId = NAME_None;
    PublicSnapshot.LeadVariant = EDigimonVariant::Normal;
    PublicSnapshot.LeadLevel = 1;
    if (Profile.Party.Num() > 0)
    {
        if (const FDigimonOwnedPartner* Lead = FindPartnerMutable(Profile.Party[0]))
        {
            PublicSnapshot.LeadSpeciesId = Lead->SpeciesId;
            PublicSnapshot.LeadVariant = Lead->Variant;
            PublicSnapshot.LeadLevel = Lead->Level;
        }
    }
}

void ADigimonVenomNXTPlayerState::BeginSecondStory()
{
    // Compatibility only. Entry and saved progression are owned by the private
    // campaign controller; opening an obsolete battle list cannot unlock maps.
}

void ADigimonVenomNXTPlayerState::RecordStoryBossVictory(int32 Chapter)
{
    // Legacy list-based battles are retired. Chronicle receipts are settled by
    // the authenticated private battle actor, with its exact NPC and checkpoint.
    (void)Chapter;
}

void ADigimonVenomNXTPlayerState::RecordFinalStoryVictory()
{
    // Do not let an old Blueprint award mastery from a chapter/badge count.
    // Existing completion proof is migrated on profile load, never invented here.
}

int32 ADigimonVenomNXTPlayerState::GetInventoryQuantity(FName ItemId) const
{
    if (ItemId.IsNone()) return 0;
    const FDigimonInventoryEntry* Found = Profile.Inventory.FindByPredicate([ItemId](const FDigimonInventoryEntry& Entry)
    {
        return Entry.ItemId == ItemId;
    });
    return Found ? FMath::Max(0, Found->Quantity) : 0;
}

void ADigimonVenomNXTPlayerState::AddInventory(FName ItemId, int32 Amount)
{
    if (ItemId.IsNone() || Amount <= 0) return;
    if (FDigimonInventoryEntry* Existing = FindInventoryMutable(ItemId))
    {
        Existing->Quantity = FMath::Min(999, FMath::Max(0, Existing->Quantity) + FMath::Min(999, Amount));
        return;
    }
    FDigimonInventoryEntry Entry;
    Entry.ItemId = ItemId;
    Entry.Quantity = FMath::Min(999, Amount);
    Profile.Inventory.Add(Entry);
}

bool ADigimonVenomNXTPlayerState::ConsumeInventory(FName ItemId, int32 Amount)
{
    if (ItemId.IsNone() || Amount <= 0) return false;
    for (int32 Index = 0; Index < Profile.Inventory.Num(); ++Index)
    {
        FDigimonInventoryEntry& Entry = Profile.Inventory[Index];
        if (Entry.ItemId != ItemId) continue;
        if (Entry.Quantity < Amount) return false;
        Entry.Quantity -= Amount;
        if (Entry.Quantity <= 0) Profile.Inventory.RemoveAt(Index);
        return true;
    }
    return false;
}

void ADigimonVenomNXTPlayerState::ServerPurchaseItem_Implementation(FName ItemId, EDigimonCurrency Currency, int32 Quantity)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    const auto Reject = [&](const FString& Message) { NotifyProgression(TEXT("Shop"), Message, EDigimonAudioCue::Error); };
    if (HasActiveBattle()) { Reject(TEXT("Finish your current battle before purchasing supplies.")); return; }
    if (Currency != EDigimonCurrency::Credits && Currency != EDigimonCurrency::DigiRubies) return;
    if (Quantity < 1 || Quantity > 99) { Reject(TEXT("Choose a quantity from 1 to 99.")); return; }
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonShopItemDefinition Item;
    if (!Data || !Data->GetShopItem(ItemId, Item)) { Reject(TEXT("This item is not available from the shop.")); return; }
    const int64 CreditCost = Item.CreditCost;
    const int32 RubyCost = Item.DigiRubyCost;
    const FString ItemName = Item.DisplayName.ToString();

    const int64 TotalCredits = FMath::Clamp<int64>(CreditCost, 1, MAX_int64 / 99) * Quantity;
    const int64 TotalRubies = static_cast<int64>(FMath::Max(0, RubyCost)) * Quantity;
    FDigimonPlayerProfile Candidate = Profile;
    if (Currency == EDigimonCurrency::Credits)
    {
        if (Candidate.Credits < TotalCredits) { Reject(TEXT("Not enough credits. Nothing was purchased.")); return; }
        Candidate.Credits -= TotalCredits;
    }
    else
    {
        if (Candidate.DigiRubies < TotalRubies) { Reject(TEXT("Not enough DigiRubies. Nothing was purchased.")); return; }
        Candidate.DigiRubies -= static_cast<int32>(TotalRubies);
    }
    FDigimonInventoryEntry* Existing = Candidate.Inventory.FindByPredicate([&](const FDigimonInventoryEntry& Entry) { return Entry.ItemId == ItemId; });
    if (Existing)
    {
        if (Existing->Quantity > 999 - Quantity) { Reject(TEXT("You can carry up to 999 of each item. Nothing was spent.")); return; }
        Existing->Quantity = FMath::Max(0, Existing->Quantity) + Quantity;
    }
    else
    {
        FDigimonInventoryEntry Entry; Entry.ItemId = ItemId; Entry.Quantity = Quantity; Candidate.Inventory.Add(Entry);
    }
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Candidate))
    { Reject(TEXT("Your purchase could not be saved. No currency was spent; please try again.")); return; }
    Profile = MoveTemp(Candidate);
    MarkProfileChanged();
    NotifyProgression(TEXT("Purchase complete"), FString::Printf(TEXT("%d x %s added to your inventory."), Quantity, *ItemName), EDigimonAudioCue::Purchase);
}

void ADigimonVenomNXTPlayerState::ServerUseHealingItem_Implementation(FGuid InstanceId, FName ItemId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    const auto Reject = [&](const FString& Message) { NotifyProgression(TEXT("Recovery item"), Message, EDigimonAudioCue::Error); };
    if (HasActiveBattle()) { Reject(TEXT("Use the battle item command during your current battle.")); return; }
    const UDigimonVenomNXTDataSubsystem* Shop = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonShopItemDefinition Item;
    if (!Shop || !Shop->GetShopItem(ItemId, Item) || (Item.HPHeal <= 0 && Item.SPHeal <= 0)) return;
    FDigimonPlayerProfile Candidate = Profile;
    FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&](const FDigimonOwnedPartner& Entry) { return Entry.InstanceId == InstanceId; });
    const int32 InventoryIndex = Candidate.Inventory.IndexOfByPredicate([&](const FDigimonInventoryEntry& Entry) { return Entry.ItemId == ItemId && Entry.Quantity > 0; });
    if (!Partner || InventoryIndex == INDEX_NONE) { Reject(TEXT("Select a partner and a capsule you own. Nothing was used.")); return; }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonSpeciesDefinition Definition;
    if (!Data || !Data->GetSpecies(Partner->SpeciesId, Definition)) { Reject(TEXT("Partner data is unavailable. No capsule was used.")); return; }
    DigimonVenomNXTAutoBattle::MigratePartner(*Partner, Data);
    const FDigimonStats Total = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data).Stats;
    const bool bHP = Item.HPHeal > 0;
    const int32 Maximum = bHP ? FMath::Max(1, Total.MaxHP) : FMath::Max(0, Total.MaxSP);
    const int32 Before = FMath::Clamp(bHP ? Partner->CurrentHP : Partner->CurrentSP, 0, Maximum);
    const int32 Gain = FMath::Min(Maximum - Before, bHP ? Item.HPHeal : Item.SPHeal);
    if (Gain <= 0) { Reject(bHP ? TEXT("This partner already has full HP. No capsule was used.") : TEXT("This partner already has full SP. No capsule was used.")); return; }
    if (bHP) Partner->CurrentHP = Before + Gain; else Partner->CurrentSP = Before + Gain;
    Partner->CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    if (--Candidate.Inventory[InventoryIndex].Quantity <= 0) Candidate.Inventory.RemoveAt(InventoryIndex);
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Candidate))
    { Reject(TEXT("Recovery could not be saved. Your capsule and partner are unchanged; please try again.")); return; }
    Profile = MoveTemp(Candidate);
    MarkProfileChanged();
    NotifyProgression(TEXT("Capsule applied"), FString::Printf(TEXT("Restored %d %s."), Gain, bHP ? TEXT("HP") : TEXT("SP")), EDigimonAudioCue::Item);
}

void ADigimonVenomNXTPlayerState::ServerSetFarmResident_Implementation(FGuid InstanceId, bool bResident)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    if (HasActiveBattle()) { NotifyProgression(TEXT("DigiFarm"), TEXT("Finish the current battle before changing farm residents."), EDigimonAudioCue::Error); return; }
    if (!FindPartnerMutable(InstanceId)) return;
    const int32 Index = Profile.DigiFarmResidents.IndexOfByKey(InstanceId);
    const FDigimonPlayerProfile Before = Profile;
    if (bResident)
    {
        if (Index != INDEX_NONE) return;
        if (Profile.DigiFarmResidents.Num() >= FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxFarmResidents, 1, 500))
        { NotifyProgression(TEXT("DigiFarm full"), TEXT("Return a resident to your collection before placing another Digimon."), EDigimonAudioCue::Error); return; }
        Profile.DigiFarmResidents.Add(InstanceId);
    }
    else if (Index != INDEX_NONE) Profile.DigiFarmResidents.RemoveAt(Index);
    else return;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Profile))
    {
        Profile = Before;
        NotifyProgression(TEXT("DigiFarm save failed"), TEXT("Your resident assignment was not changed. Please try again."), EDigimonAudioCue::Error);
        return;
    }
    MarkProfileChanged();
    DigimonVenomNXTServerActivity::Record(this, TEXT("DigiFarm"), TEXT("Resident assignment saved"), FString::Printf(TEXT("Partner %s | %s | %d farm residents"), *InstanceId.ToString(EGuidFormats::Digits), bResident ? TEXT("placed on farm") : TEXT("returned to collection"), Profile.DigiFarmResidents.Num()));
}

void ADigimonVenomNXTPlayerState::ServerFeedFarmResident_Implementation(FGuid InstanceId, FName ItemId, EDigimonTrainingStat Stat)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(GetOwner());
    if (Profile.AccountId.IsEmpty() || !PC || !PC->IsAccountAuthenticated()) return;
    if (!PC->IsInDigiFarm() || !Profile.DigiFarmResidents.Contains(InstanceId) || HasActiveBattle())
    { NotifyProgression(TEXT("DigiFarm care"), TEXT("Enter your private farm and select one of its residents before feeding."), EDigimonAudioCue::Error); return; }
    FDigimonOwnedPartner* Partner = FindPartnerMutable(InstanceId);
    if (!Partner || !Partner->IsValid()) return;
    // Item identity determines the trained stat; clients cannot redirect a meat bonus.
    const UDigimonVenomNXTDataSubsystem* Shop = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonShopItemDefinition Item;
    if (!Shop || !Shop->GetShopItem(ItemId, Item) || Item.Category != TEXT("digimeat")) return;
    const bool bCAM = Item.CAMGain > 0, bABI = Item.bABIMeat, bTraining = Item.TrainingGain > 0;
    const FName StatNames[] = {TEXT("hp"), TEXT("sp"), TEXT("atk"), TEXT("def"), TEXT("int"), TEXT("spd")};
    if (bTraining)
    {
        int32 StatIndex = INDEX_NONE;
        for (int32 I = 0; I < 6; ++I) if (StatNames[I] == Item.Resource) StatIndex = I;
        if (StatIndex == INDEX_NONE) return;
        Stat = static_cast<EDigimonTrainingStat>(StatIndex);
        if (!DigimonVenomNXTEvolution::CanTrain(*Partner, Stat, Item.TrainingGain))
        { NotifyProgression(TEXT("Training limit"), TEXT("This meat would exceed +100 in one stat or +300 total. Nothing was spent."), EDigimonAudioCue::Error); return; }
    }
    if (bCAM && Partner->CAM >= 100)
    { NotifyProgression(TEXT("Friendship complete"), TEXT("This resident already has 100 CAM. No meat was used."), EDigimonAudioCue::Error); return; }
    if (bABI && Partner->ABI >= DigimonVenomNXTEvolutionCore::MaximumABI(GetDefault<UDigimonVenomNXTSettings>()->MaxABI))
    { NotifyProgression(TEXT("ABI limit reached"), TEXT("This resident has reached its ABI limit. No meat was used."), EDigimonAudioCue::Error); return; }
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonSpeciesDefinition Species;
    if (!Data || !Data->GetSpecies(Partner->SpeciesId, Species) || Species.bPlaceholder) return;
    const FDigimonPlayerProfile Before = Profile;
    if (!ConsumeInventory(ItemId))
    { NotifyProgression(TEXT("DigiMeat needed"), TEXT("Buy the selected DigiMeat from the shop first."), EDigimonAudioCue::Error); return; }
    FString Result;
    if (bCAM)
    {
        const int32 Gain = DigimonVenomNXTEvolution::FeedCAM(*Partner);
        Result = FString::Printf(TEXT("+%d CAM. Friendship: %d / 100."), Gain, Partner->CAM);
    }
    else if (bABI)
    {
        const int32 Gain = DigimonVenomNXTEvolution::FeedABI(*Partner);
        Result = FString::Printf(TEXT("+%d permanent ABI. ABI: %d. Training capacity: %d points."), Gain, Partner->ABI, DigimonVenomNXTEvolution::TrainingCapacity(*Partner));
    }
    else
    {
        const FDigimonStats OldStats = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data).Stats;
        if (!DigimonVenomNXTEvolution::TryTrain(*Partner, Stat, Item.TrainingGain)) { Profile = Before; return; }
        const FDigimonStats NewStats = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data).Stats;
        Partner->CurrentHP = FMath::Min(NewStats.MaxHP, Partner->CurrentHP + FMath::Max(0, NewStats.MaxHP - OldStats.MaxHP));
        Partner->CurrentSP = FMath::Min(NewStats.MaxSP, Partner->CurrentSP + FMath::Max(0, NewStats.MaxSP - OldStats.MaxSP));
        Result = FString::Printf(TEXT("Permanent training increased: %.1f / %d points."), DigimonVenomNXTEvolution::TrainingUsed(*Partner), DigimonVenomNXTEvolution::TrainingCapacity(*Partner));
    }
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles || !Profiles->SaveProfile(Profile))
    {
        Profile = Before;
        NotifyProgression(TEXT("DigiFarm save failed"), TEXT("No meat was spent and no stats were changed. Please try again."), EDigimonAudioCue::Error);
        return;
    }
    MarkProfileChanged();
    NotifyProgression(TEXT("Resident fed"), Result, EDigimonAudioCue::Item);
}

void ADigimonVenomNXTPlayerState::ServerUseCAMTreat_Implementation(FGuid InstanceId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    if (HasActiveBattle()) { NotifyProgression(TEXT("CAM DigiMeat"), TEXT("Finish the current battle before feeding your Digimon."), EDigimonAudioCue::Error); return; }
    FDigimonOwnedPartner* Partner = FindPartnerMutable(InstanceId);
    if (!Partner) { NotifyProgression(TEXT("CAM DigiMeat"), TEXT("Select a Digimon from your collection."), EDigimonAudioCue::Error); return; }
    if (Partner->CAM >= 100) { NotifyProgression(TEXT("CAM DigiMeat"), TEXT("Friendship is already at 100 CAM. No meat was used."), EDigimonAudioCue::Error); return; }
    if (!ConsumeInventory(TEXT("digimeat_cam"))) { NotifyProgression(TEXT("CAM DigiMeat"), TEXT("Buy CAM DigiMeat from the shop first."), EDigimonAudioCue::Error); return; }
    const int32 Gain = DigimonVenomNXTEvolution::FeedCAM(*Partner);
    NotifyProgression(TEXT("Friendship increased"), FString::Printf(TEXT("+%d CAM. Friendship: %d / 100."), Gain, Partner->CAM), EDigimonAudioCue::Item);
    MarkProfileChanged();
}

void ADigimonVenomNXTPlayerState::ServerUseABIMeat_Implementation(FGuid InstanceId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    if (Profile.AccountId.IsEmpty()) return;
    if (HasActiveBattle()) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Finish the current battle before feeding your Digimon."), EDigimonAudioCue::Error); return; }
    FDigimonOwnedPartner* Partner = FindPartnerMutable(InstanceId);
    if (!Partner) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Select a Digimon from your collection."), EDigimonAudioCue::Error); return; }
    if (Partner->ABI >= DigimonVenomNXTEvolutionCore::MaximumABI(GetDefault<UDigimonVenomNXTSettings>()->MaxABI))
    { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("This Digimon has reached the ABI limit. No meat was used."), EDigimonAudioCue::Error); return; }
    if (!ConsumeInventory(TEXT("digimeat_abi"))) { NotifyProgression(TEXT("ABI DigiMeat"), TEXT("Buy ABI DigiMeat from the shop first."), EDigimonAudioCue::Error); return; }
    const int32 Gain = DigimonVenomNXTEvolution::FeedABI(*Partner);
    NotifyProgression(TEXT("Permanent ABI increased"), FString::Printf(TEXT("+%d ABI. Total ABI: %d. Training capacity: %d points."), Gain, Partner->ABI, DigimonVenomNXTEvolution::TrainingCapacity(*Partner)), EDigimonAudioCue::Item);
    MarkProfileChanged();
}

void ADigimonVenomNXTPlayerState::ServerUseDigiMeat_Implementation(FGuid InstanceId, EDigimonTrainingStat Stat)
{
    const TCHAR* ItemIds[] = {TEXT("digimeat_hp_1"), TEXT("digimeat_sp_1"), TEXT("digimeat_atk_1"), TEXT("digimeat_def_1"), TEXT("digimeat_int_1"), TEXT("digimeat_spd_1")};
    const int32 Index = static_cast<int32>(Stat);
    if (Index < 0 || Index >= 6) return;
    ServerFeedFarmResident_Implementation(InstanceId, FName(ItemIds[Index]), Stat);
}

void ADigimonVenomNXTPlayerState::TransformPartner(FGuid InstanceId, FName TargetSpeciesId, bool bDeEvolution)
{
    if (!HasAuthority() || Profile.AccountId.IsEmpty()) return;
    const FString Title = bDeEvolution ? TEXT("De-evolution") : TEXT("Evolution");
    if (HasActiveBattle()) { NotifyProgression(Title, TEXT("Finish the current battle before changing a Digimon's form."), EDigimonAudioCue::Error); return; }
    FDigimonOwnedPartner* Partner = FindPartnerMutable(InstanceId);
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Partner || !Data) { NotifyProgression(Title, TEXT("This Digimon is unavailable. Select it again from your collection."), EDigimonAudioCue::Error); return; }
    FString Message;
    const bool bTransformed = DigimonVenomNXTEvolution::TryTransform(*Partner, TargetSpeciesId, bDeEvolution, Data, Message);
    if (bTransformed) MarkProfileChanged();
    NotifyProgression(Title, Message, bTransformed ? EDigimonAudioCue::Confirm : EDigimonAudioCue::Error);
}

void ADigimonVenomNXTPlayerState::ServerEvolve_Implementation(FGuid InstanceId, FName TargetSpeciesId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    TransformPartner(InstanceId, TargetSpeciesId, false);
}

void ADigimonVenomNXTPlayerState::ServerDeEvolve_Implementation(FGuid InstanceId, FName TargetSpeciesId)
{
    if (!DigimonVenomNXTServerActivity::AllowGameplay(this)) return;
    TransformPartner(InstanceId, TargetSpeciesId, true);
}

bool ADigimonVenomNXTPlayerState::RecoverDefeatedParty()
{
    if (!HasAuthority() || !Profile.Season.BattleCheckpointJson.IsEmpty() ||
        DigimonVenomNXTCampaign::HasPendingBattle(Profile)) return false;
    TArray<FDigimonOwnedPartner*> Party;
    for (const FGuid& Id : Profile.Party)
        if (FDigimonOwnedPartner* Partner = FindPartnerMutable(Id)) Party.AddUnique(Partner);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const bool bRecovered = DigimonVenomNXTRecoveryCore::RestoreExhaustedParty(Party,
        [Data](const FDigimonOwnedPartner& Partner)
        {
            const FDigimonStats Stats = DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data).Stats;
            return DigimonVenomNXTRecoveryCore::Vitals{Stats.MaxHP, Stats.MaxSP};
        });
    if (!bRecovered) return false;
    MarkProfileChanged();
    if (ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(GetOwner()))
        if (Controller->IsAccountAuthenticated())
            Controller->ClientShowMessage(TEXT("Party recovered"), TEXT("Your defeated party has been fully restored to full HP and SP."));
    if (!Profile.AccountId.IsEmpty())
        if (UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr)
            if (!Profiles->SaveProfile(Profile)) UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist recovered party for %s; autosave will retry."), *GetPlayerName());
    return true;
}

void ADigimonVenomNXTPlayerState::ApplyBattleTeamResult(const FDigimonBattleTeam& Team, bool bRestoreDefeatedParty)
{
    if (!HasAuthority()) return;
    // Victory, retreat and partial defeats retain their damage. Recovery is only
    // applied once every active AND reserve member of this battle party is down.
    const bool bRestore = bRestoreDefeatedParty && DigimonVenomNXTRecoveryCore::IsTeamDefeated(Team);
    auto ApplyUnit = [this, bRestore](const FDigimonBattleUnit& Unit)
    {
        if (FDigimonOwnedPartner* Partner = FindPartnerMutable(Unit.InstanceId))
        {
            const DigimonVenomNXTRecoveryCore::Vitals Vitals = DigimonVenomNXTRecoveryCore::ResultVitals(Unit, bRestore);
            Partner->CurrentHP = Vitals.HP;
            Partner->CurrentSP = Vitals.SP;
            Partner->CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        }
    };
    for (const FDigimonBattleUnit& Unit : Team.Active) ApplyUnit(Unit);
    for (const FDigimonBattleUnit& Unit : Team.Bench) ApplyUnit(Unit);
    MarkProfileChanged();
}


bool ADigimonVenomNXTPlayerState::ConsumeBattleItem(FName ItemId, int32 Amount)
{
    if (!HasAuthority() || Amount <= 0) return false;
    if (!ConsumeInventory(ItemId, Amount)) return false;
    MarkProfileChanged();
    return true;
}

FString ADigimonVenomNXTPlayerState::AwardExperienceToParty(int64 ExperiencePerPartner)
{
    if (!HasAuthority() || ExperiencePerPartner <= 0) return FString();
    const int32 MaxLevel = GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel;
    UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    TSet<FGuid> Awarded;
    FString Summary;
    for (const FGuid& Id : Profile.Party)
    {
        if (Awarded.Contains(Id)) continue;
        Awarded.Add(Id);
        FDigimonOwnedPartner* Partner = FindPartnerMutable(Id);
        if (!Partner || !Partner->IsValid()) continue;
        const auto Result = DigimonVenomNXTProgressionCore::Apply(*Partner, ExperiencePerPartner, MaxLevel,
            [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        if (Result.GrantedExperience > 0 || Result.LevelsGained > 0)
        {
            const FString Name = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data).DisplayName;
            Summary += FString::Printf(TEXT(" %s +%lld XP%s"), *Name, static_cast<long long>(Result.GrantedExperience),
                Result.LevelsGained > 0 ? *FString::Printf(TEXT(" — LEVEL UP! Lv. %d → %d."), Result.PreviousLevel, Result.Level) : TEXT("."));
        }
    }
    MarkProfileChanged();
    if (!Summary.IsEmpty()) DigimonVenomNXTServerActivity::Record(this, TEXT("Rewards"), TEXT("Party XP applied"), Summary + TEXT(" | settlement save follows"));
    return Summary;
}
