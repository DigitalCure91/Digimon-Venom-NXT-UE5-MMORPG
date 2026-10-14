#include "DigimonVenomNXTBattleActor.h"
#include "HAL/PlatformTime.h"
#include "DigimonVenomNXTServerActivity.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTCombatCore.h"
#include "DigimonVenomNXTBattlePolicyCore.h"
#include "DigimonVenomNXTTimelineCore.h"
#include "DigimonVenomNXTRecoveryCore.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "DigimonVenomNXTSeason.h"
#include "DigimonVenomNXTSeasonCore.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTCampaignBattleCore.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTRewardCore.h"
#include "DigimonVenomNXTWorld.h"
#include "JsonObjectConverter.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "DigimonVenomNXTPlayerController.h"
#include "Engine/GameInstance.h"
#include "UObject/Class.h"

namespace
{
void AddBattleSupply(FDigimonPlayerProfile& Profile, FName Id, int32 Quantity)
{
    if (Quantity <= 0) return;
    FDigimonInventoryEntry* Entry = Profile.Inventory.FindByPredicate([Id](const FDigimonInventoryEntry& E) { return E.ItemId == Id; });
    if (!Entry) { FDigimonInventoryEntry New; New.ItemId = Id; Profile.Inventory.Add(New); Entry = &Profile.Inventory.Last(); }
    Entry->Quantity = DigimonVenomNXTRewardCore::InventoryTotal(Entry->Quantity, Quantity);
}
int32 AddBattleScan(FDigimonPlayerProfile& Profile, const FDigimonBattleUnit& Unit, int32 Gain, int32 Cap)
{
    FDigimonScanRecord* Scan = Profile.Scans.FindByPredicate([&Unit](const FDigimonScanRecord& E) { return E.SpeciesId == Unit.SpeciesId && E.Variant == Unit.Variant; });
    if (!Scan) { FDigimonScanRecord New; New.SpeciesId = Unit.SpeciesId; New.Variant = Unit.Variant; Profile.Scans.Add(New); Scan = &Profile.Scans.Last(); }
    const int32 Before = DigimonVenomNXTScanCore::Percent(Scan->Percent, Cap);
    Scan->Percent = DigimonVenomNXTScanCore::Gain(Before, Gain, Cap);
    if (Scan->Percent >= DigimonVenomNXTScanCore::Cap(Cap)) Scan->FractionalHundredths = 0;
    DigimonVenomNXTScanCore::Observe(*Scan, Cap);
    return Scan->Percent - Before;
}
static_assert(static_cast<int32>(EDigimonBattleKind::Wild) == 0 && static_cast<int32>(EDigimonBattleKind::AITamer) == 1 &&
    static_cast<int32>(EDigimonBattleKind::Season) == 2 && static_cast<int32>(EDigimonBattleKind::Ranked) == 3 &&
    static_cast<int32>(EDigimonBattleKind::Story) == 4 && static_cast<int32>(EDigimonBattleKind::Friendly) == 5,
    "Keep portable battle-context policy aligned with the persisted battle kinds.");
// This validates both a fresh factory request and a suspended decision. Active
// slots may be swapped with reserves during combat, so match the whole roster.
bool MatchesAuthoredCampaignTeam(EDigimonPrivateCampaign Campaign, const FDigimonRelayNPC& NPC,
    const FDigimonBattleTeam& Team, const UDigimonVenomNXTDataSubsystem* Data)
{
    if (!Data || NPC.TeamSpecies.IsEmpty() || NPC.TeamSpecies.Num() != NPC.TeamLevels.Num() ||
        Team.Active.IsEmpty() || Team.Active.Num() + Team.Bench.Num() != NPC.TeamSpecies.Num()) return false;
    const bool bFinale = NPC.Role == EDigimonRelayRole::FinalBoss;
    if (bFinale && (Team.Active.Num() != DigimonVenomNXTCampaignBattleCore::FinaleActiveSlots ||
        !Team.Bench.IsEmpty() || NPC.TeamSpecies.Num() != DigimonVenomNXTCampaignBattleCore::FinaleActiveSlots)) return false;
    std::array<DigimonVenomNXTCampaignBattleCore::FinalUnit, DigimonVenomNXTCampaignBattleCore::FinaleActiveSlots> FinalUnits;
    int32 FinalIndex = 0;
    TSet<int32> MatchedSlots;
    for (const TArray<FDigimonBattleUnit>* Units : {&Team.Active, &Team.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            FDigimonSpeciesDefinition Species;
            if (!Data->GetSpecies(Unit.SpeciesId, Species) || Species.bPlaceholder ||
                !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Unit.Variant), Species.bHasNormalArtwork,
                    Species.bHasParadoxArtwork, Species.bHasShinyArtwork, Species.bHasFirewallArtwork)) return false;
            if (bFinale)
            {
                auto& Final = FinalUnits[FinalIndex++];
                Final.Species = TCHAR_TO_UTF8(*Unit.SpeciesId.ToString());
                Final.Level = Unit.Level;
                Final.Variant = static_cast<int32>(Unit.Variant);
                Final.Mega = Species.Stage == EDigimonStage::Mega;
            }
            int32 MatchedSlot = INDEX_NONE;
            for (int32 Slot = 0; Slot < NPC.TeamSpecies.Num(); ++Slot)
                if (!MatchedSlots.Contains(Slot) && Unit.SpeciesId == NPC.TeamSpecies[Slot] &&
                    Unit.Level == NPC.TeamLevels[Slot] &&
                    Unit.Variant == (NPC.TeamVariants.IsValidIndex(Slot) ? NPC.TeamVariants[Slot] : EDigimonVariant::Normal))
                { MatchedSlot = Slot; break; }
            if (MatchedSlot == INDEX_NONE) return false;
            MatchedSlots.Add(MatchedSlot);
        }
    return !bFinale || DigimonVenomNXTCampaignBattleCore::ValidFinalRoster(static_cast<int32>(Campaign), NPC.MapId,
        TCHAR_TO_UTF8(*NPC.Id.ToString()), FinalUnits, Team.Active.Num(), Team.Bench.Num());
}
}

bool ADigimonVenomNXTBattleActor::IsRelayBattle() const
{
    EDigimonPrivateCampaign Campaign;
    FName NPCId;
    return (State.Kind == EDigimonBattleKind::Story || State.Kind == EDigimonBattleKind::Wild) &&
        DigimonVenomNXTCampaign::TryParseContext(BattleContextId, Campaign, NPCId);
}

EDigimonPrivateCampaign ADigimonVenomNXTBattleActor::BattleCampaign() const
{
    EDigimonPrivateCampaign Campaign;
    FName NPCId;
    return DigimonVenomNXTCampaign::TryParseContext(BattleContextId, Campaign, NPCId) ? Campaign :
        static_cast<EDigimonPrivateCampaign>(MAX_uint8);
}

FName ADigimonVenomNXTBattleActor::BattleNPCId() const
{
    EDigimonPrivateCampaign Campaign;
    FName NPCId;
    return DigimonVenomNXTCampaign::TryParseContext(BattleContextId, Campaign, NPCId) ? NPCId : NAME_None;
}

ADigimonVenomNXTBattleActor::ADigimonVenomNXTBattleActor()
{
    bReplicates = true;
    bAlwaysRelevant = false;
    SetReplicateMovement(false);
    SetNetUpdateFrequency(8.0f);
}

void ADigimonVenomNXTBattleActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, ReplicatedSnapshot);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, PlayerA);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, PlayerB);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, BattleContextId);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, UnrankedDecisionDeadlineServerTime);
    DOREPLIFETIME(ADigimonVenomNXTBattleActor, bUnrankedResultSaving);
}

void ADigimonVenomNXTBattleActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(RankedPlaybackTimer);
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    Super::EndPlay(EndPlayReason);
}

void ADigimonVenomNXTBattleActor::OnRep_State()
{
    // Properties may coalesce across network frames. Bootstrap once, then only the
    // reliable ordered stream may advance UI state, so no attacks disappear on lag.
    if (LastDeliveredBattleId == ReplicatedSnapshot.BattleId && LastDeliveredSerial != INDEX_NONE) return;
    State = ReplicatedSnapshot;
    LastDeliveredBattleId = State.BattleId;
    LastDeliveredSerial = State.PresentationSerial;
    if (!bPresentationConsumerAttached) PresentationBacklog.Add(State);
    OnBattleStateChanged.Broadcast(State);
}

void ADigimonVenomNXTBattleActor::MulticastPresentState_Implementation(const FDigimonBattleState& Packet)
{
    if (LastDeliveredBattleId == Packet.BattleId && Packet.PresentationSerial <= LastDeliveredSerial) return;
    LastDeliveredBattleId = Packet.BattleId;
    LastDeliveredSerial = Packet.PresentationSerial;
    if (!HasAuthority()) State = Packet;
    if (!bPresentationConsumerAttached && ShouldBufferPresentation()) PresentationBacklog.Add(Packet);
    OnBattleStateChanged.Broadcast(Packet);
}

bool ADigimonVenomNXTBattleActor::ShouldBufferPresentation() const
{
    if (!HasAuthority()) return true;
    if (!GetWorld() || GetNetMode()==NM_DedicatedServer) return false;
    for (FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator(); It; ++It)
        if (const APlayerController* PC=It->Get(); PC && PC->IsLocalController() && IsParticipant(PC)) return true;
    return false;
}

TArray<FDigimonBattleState> ADigimonVenomNXTBattleActor::ConsumePresentationBacklog()
{
    bPresentationConsumerAttached=true;
    TArray<FDigimonBattleState> Pending=MoveTemp(PresentationBacklog);
    PresentationBacklog.Reset();
    return Pending;
}

void ADigimonVenomNXTBattleActor::ReleasePresentationConsumer()
{
    bPresentationConsumerAttached=false;
    PresentationBacklog.Reset();
}

void ADigimonVenomNXTBattleActor::PublishState()
{
    if (!HasAuthority() || bSeasonCommandTransaction) return;
    // Only a published authoritative state is observable. Private/Season command
    // transactions return above until their durable commit has succeeded.
    if (ConsoleBattleId != State.BattleId)
    {
        ConsoleBattleId = State.BattleId;
        LastConsolePresentationSerial = INDEX_NONE;
        bConsoleResultLogged = false;
        DigimonVenomNXTServerActivity::RecordFor(this, State.TeamA.TrainerName, TEXT("Battle"), TEXT("Battle active"),
            FString::Printf(TEXT("%s | %s | opponent %s | turn %d | context %s"), *State.BattleId.ToString(EGuidFormats::Digits),
                *UEnum::GetValueAsString(State.Kind), *State.TeamB.TrainerName, State.TurnNumber,
                BattleContextId.IsEmpty() ? TEXT("public") : *BattleContextId));
    }
    PendingA.GenerateKeyArray(State.ReadySlotsA);
    PendingB.GenerateKeyArray(State.ReadySlotsB);
    const int32 PacketCount=FMath::Max(1,State.PresentationEvents.Num());
    const int32 FirstSerial=State.PresentationSerial;
    State.PresentationSerial=FirstSerial+PacketCount-1;
    ReplicatedSnapshot=State;
    // Snapshots bootstrap late join/reconnect at the current authoritative point.
    // The reliable stream supplies individual actions; replicating a whole round's
    // full snapshots would needlessly inflate bunches and may exceed network limits.
    ReplicatedSnapshot.PresentationEvents.Reset();
    ForceNetUpdate();
    for (int32 I=0; I<PacketCount; ++I)
    {
        FDigimonBattleState Packet=State;
        Packet.PresentationSerial=FirstSerial+I;
        if (State.PresentationEvents.IsValidIndex(I))
        {
            const FDigimonBattlePresentationEvent& Event=State.PresentationEvents[I];
            Packet.PresentationEvents.Reset();
            Packet.PresentationEvents.Add(Event);
            if (Event.bHasPostState) { Packet.TeamA=Event.PostTeamA; Packet.TeamB=Event.PostTeamB; }
            Packet.bFinished=State.bFinished && I==PacketCount-1;
            Packet.WinningTeam=Packet.bFinished ? State.WinningTeam : INDEX_NONE;
            if (!Packet.bFinished) Packet.LastEvent=Event.Text;
        }
        if (Packet.PresentationSerial > LastConsolePresentationSerial)
        {
            if (Packet.PresentationEvents.Num() > 0)
            {
                const FDigimonBattlePresentationEvent& Event = Packet.PresentationEvents[0];
                DigimonVenomNXTServerActivity::RecordFor(this, State.TeamA.TrainerName, TEXT("Battle"), TEXT("Action resolved"),
                    FString::Printf(TEXT("%s | turn %d | %s | team %d slot %d -> team %d slot %d | damage %d | %s"),
                        *State.BattleId.ToString(EGuidFormats::Digits), Event.TurnNumber, *UEnum::GetValueAsString(Event.Action),
                        Event.ActingTeam + 1, Event.ActingSlot + 1, Event.TargetTeam + 1, Event.TargetSlot + 1, Event.Damage, *Event.Text));
            }
            LastConsolePresentationSerial = Packet.PresentationSerial;
        }
        if (Packet.bFinished && !bConsoleResultLogged)
        {
            bConsoleResultLogged = true;
            // Public combat may remain applied in memory after a save failure; do
            // not label this event "saved". Persistence events report that outcome.
            DigimonVenomNXTServerActivity::RecordFor(this, State.TeamA.TrainerName, TEXT("Battle"), TEXT("Result published"),
                FString::Printf(TEXT("%s | %s | winning team %d | %s"), *State.BattleId.ToString(EGuidFormats::Digits),
                    State.bFled ? TEXT("fled") : TEXT("finished"), State.WinningTeam + 1, *State.LastEvent));
        }
        MulticastPresentState(Packet);
    }
}

void ADigimonVenomNXTBattleActor::CapturePostState(int32 FirstEvent)
{
    for (int32 I=FirstEvent; I<State.PresentationEvents.Num(); ++I)
    {
        auto& Event=State.PresentationEvents[I];
        Event.TurnNumber=State.TurnNumber;
        Event.bHasPostState=true;
        Event.PostTeamA=State.TeamA;
        Event.PostTeamB=State.TeamB;
    }
}

bool ADigimonVenomNXTBattleActor::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
    const AController* ViewerController = Cast<AController>(RealViewer);
    if (!ViewerController && ViewTarget) ViewerController = Cast<AController>(ViewTarget->GetInstigatorController());
    if (ViewerController && (ViewerController->PlayerState == PlayerA || ViewerController->PlayerState == PlayerB)) return true;
    return false;
}

void ADigimonVenomNXTBattleActor::TryDestroyWhenUnused()
{
    if (!HasAuthority() || !State.bFinished || !GetWorld()) return;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (PC && PC->CurrentBattle == this) return;
    }
    Destroy();
}

FDigimonBattleUnit ADigimonVenomNXTBattleActor::BuildUnit(const FDigimonOwnedPartner& Partner) const
{
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    return DigimonVenomNXTAutoBattle::BuildUnit(Partner, Data);
}

FDigimonBattleTeam ADigimonVenomNXTBattleActor::BuildTeamFromProfile(const FDigimonPlayerProfile& Profile, bool bFullRestore, bool bCampaignFinale) const
{
    FDigimonBattleTeam Team;
    Team.TrainerName = Profile.Username;
    const bool bSourceFormation = DigimonVenomNXTBattlePolicyCore::UsesSourcePlayerFormation(static_cast<int32>(State.Kind), State.bAutomatic);
    const int32 ActiveLimit = bSourceFormation ? 3 : DigimonVenomNXTCampaignBattleCore::ActiveSlots(
        GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize, bFullRestore && State.Kind != EDigimonBattleKind::Friendly, bCampaignFinale);
    TSet<FGuid> Seen;
    for (int32 PartyIndex = 0; PartyIndex < Profile.Party.Num(); ++PartyIndex)
    {
        const FGuid& Id = Profile.Party[PartyIndex];
        if (!Id.IsValid() || Seen.Contains(Id)) continue;
        Seen.Add(Id);
        const FDigimonOwnedPartner* Found = Profile.Collection.FindByPredicate([&](const FDigimonOwnedPartner& P){ return P.InstanceId == Id; });
        if (!Found) continue;
        FDigimonBattleUnit Unit = BuildUnit(*Found);
        if (bFullRestore) { Unit.HP = Unit.Stats.MaxHP; Unit.SP = Unit.Stats.MaxSP; Unit.bDefeated = false; }
        if (bSourceFormation ? PartyIndex < ActiveLimit && Unit.HP > 0 : Team.Active.Num() < ActiveLimit) Team.Active.Add(Unit);
        else Team.Bench.Add(Unit);
    }
    DigimonVenomNXTRecoveryCore::PrepareTeam(Team, !bSourceFormation);
    return Team;
}

bool ADigimonVenomNXTBattleActor::InitializeWildBattle(ADigimonVenomNXTPlayerState* Player, FName WildSpecies, EDigimonVariant Variant, int32 WildLevel)
{
    // Preserve the existing Blueprint/admin hook for an explicitly selected single opponent.
    FDigimonWildEncounterEntry Encounter;
    Encounter.SpeciesId = WildSpecies;
    Encounter.Variant = Variant;
    Encounter.Level = WildLevel;
    return InitializeWildGroupBattle(Player, TArray<FDigimonWildEncounterEntry>{Encounter});
}

bool ADigimonVenomNXTBattleActor::InitializeWildGroupBattle(ADigimonVenomNXTPlayerState* Player, const TArray<FDigimonWildEncounterEntry>& Encounters)
{

    if (!HasAuthority() || !Player || Player->HasActiveBattle() || Encounters.Num() < 1 || Encounters.Num() > 3) return false;
    bool bHasLivingActive = false;
    for (int32 Index = 0; Index < FMath::Min(3, Player->Profile.Party.Num()); ++Index)
    {
        const FGuid& Id = Player->Profile.Party[Index];
        const FDigimonOwnedPartner* Partner = Player->Profile.Collection.FindByPredicate([&Id](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; });
        if (Partner && Partner->CurrentHP > 0) bHasLivingActive = true;
    }
    if (!bHasLivingActive) return false; // Heal in DigiLab or rearrange the party before searching.
    const UDigimonVenomNXTDataSubsystem* WildData = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!WildData) return false;

    const ADigimonVenomNXTPlayerController* WildController = Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner());
    const bool bPrivateTraining = WildController && WildController->IsInRelay();
    // Validate and build the entire group before changing the player or publishing a battle.
    // Repeated species are allowed, but each opponent receives its own identity and timeline slot.
    FDigimonBattleTeam WildTeam;
    WildTeam.TrainerName = TEXT("Wild");
    for (const FDigimonWildEncounterEntry& Encounter : Encounters)
    {
        FDigimonSpeciesDefinition WildDefinition;
        EDigimonVariant Variant = Encounter.Variant;
        if (Encounter.SpeciesId.IsNone() || !WildData->GetSpecies(Encounter.SpeciesId, WildDefinition) || WildDefinition.bPlaceholder ||
            static_cast<uint8>(Variant) > static_cast<uint8>(EDigimonVariant::Firewall)) return false;
        if (!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Variant), WildDefinition.bHasNormalArtwork,
            WildDefinition.bHasParadoxArtwork, WildDefinition.bHasShinyArtwork, WildDefinition.bHasFirewallArtwork))
        {
            // A missing optional variety cannot reroll into another rare form or an invisible encounter.
            if (!WildDefinition.bHasNormalArtwork) return false;
            Variant = EDigimonVariant::Normal;
        }
        FDigimonOwnedPartner Wild;
        Wild.InstanceId = FGuid::NewGuid();
        Wild.SpeciesId = Encounter.SpeciesId;
        Wild.Variant = Variant;
        Wild.Level = FMath::Clamp(Encounter.Level, 1, 99);
        if (bPrivateTraining) { Wild.ABI = FMath::Min(100, Wild.Level / 2); Wild.CAM = Wild.Level; }
        Wild.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        Wild.CurrentHP = MAX_int32;
        Wild.CurrentSP = MAX_int32;
        FDigimonBattleUnit WildUnit = BuildUnit(Wild);
        // Keep the existing per-opponent wild battle balance for every group member.
        WildUnit.Stats.MaxHP = DigimonVenomNXTBattlePolicyCore::WildMaxHP(WildUnit.Stats.MaxHP, bPrivateTraining);
        WildUnit.HP = WildUnit.Stats.MaxHP;
        WildTeam.Active.Add(MoveTemp(WildUnit));
    }

    FString ContextId = FString::Printf(TEXT("world:%d"), Player->Profile.CurrentMapId);
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner());
    if (Controller && Controller->IsInRelay())
    {
        const EDigimonPrivateCampaign Campaign = Controller->GetStoryCampaign();
        if (!DigimonVenomNXTCampaign::IsValid(Campaign)) return false;
        const FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Player->Profile, Campaign);
        if (!Controller->IsAccountAuthenticated() || Campaign != Player->Profile.ActiveStoryCampaign || !Progress.bInside ||
            !DigimonVenomNXTCampaign::CanEnterMap(Campaign, Progress, Progress.MapId)) return false;
        if ((Campaign == EDigimonPrivateCampaign::ParadoxChronicles || Campaign == EDigimonPrivateCampaign::GhostLine) && Progress.MapId == 1) return false;
        ContextId = DigimonVenomNXTCampaign::ContextPrefix(Campaign) + FString::Printf(TEXT("wild:%d"), Progress.MapId);
    }
    PlayerA = Player;
    PlayerB = nullptr;
    BattleContextId = MoveTemp(ContextId);
    State = FDigimonBattleState();
    State.BattleId = FGuid::NewGuid();
    State.Kind = EDigimonBattleKind::Wild;
    State.TeamA = BuildTeamFromProfile(Player->Profile);
    if (State.TeamA.Active.Num() == 0 || IsTeamDefeated(State.TeamA)) return false;
    State.TeamB = MoveTemp(WildTeam);
    if (State.TeamB.Active.Num() == 1)
    {
        const FDigimonBattleUnit& WildUnit = State.TeamB.Active[0];
        const TCHAR* VarietyName = WildUnit.Variant == EDigimonVariant::Firewall ? TEXT("FireWall ") :
            WildUnit.Variant == EDigimonVariant::Shiny ? TEXT("Shiny ") : WildUnit.Variant == EDigimonVariant::Paradox ? TEXT("Paradox ") : TEXT("");
        State.LastEvent = FString::Printf(TEXT("A wild %s%s appeared! Defeating it secures scan data; winning the encounter awards any permanent mastery bonus."), VarietyName, *WildUnit.DisplayName);
    }
    else
    {
        State.LastEvent = FString::Printf(TEXT("%d wild Digimon appeared!"), State.TeamB.Active.Num());
        for (const FDigimonBattleUnit& WildUnit : State.TeamB.Active)
        {
            const TCHAR* VarietyName = WildUnit.Variant == EDigimonVariant::Firewall ? TEXT("Firewall ") :
                WildUnit.Variant == EDigimonVariant::Shiny ? TEXT("Shiny ") :
                WildUnit.Variant == EDigimonVariant::Paradox ? TEXT("Paradox ") : TEXT("");
            State.LastEvent += FString::Printf(TEXT("\n%s%s — Lv. %d"), VarietyName, *WildUnit.DisplayName, WildUnit.Level);
        }
    }
    InitializeTimeline();
    if (!SaveSeasonCheckpoint()) return false;
    PublishState();
    StartBattleSafetyChecks();
    return true;
}

bool ADigimonVenomNXTBattleActor::InitializeTamerBattle(ADigimonVenomNXTPlayerState* InPlayerA, ADigimonVenomNXTPlayerState* InPlayerB, EDigimonBattleKind Kind)
{
    if (!HasAuthority() || Kind != EDigimonBattleKind::Friendly || !InPlayerA || !InPlayerB || InPlayerA == InPlayerB || InPlayerA->HasActiveBattle() || InPlayerB->HasActiveBattle()) return false;
    // Sparring starts from restored snapshots; never heal or damage the expedition save.
    PlayerA = InPlayerA; PlayerB = InPlayerB;
    BattleContextId.Reset();
    State = FDigimonBattleState();
    State.BattleId = FGuid::NewGuid();
    State.Kind = Kind;
    State.TeamA = BuildTeamFromProfile(InPlayerA->Profile, true);
    State.TeamB = BuildTeamFromProfile(InPlayerB->Profile, true);
    if (State.TeamA.Active.IsEmpty() || State.TeamB.Active.IsEmpty() || IsTeamDefeated(State.TeamA) || IsTeamDefeated(State.TeamB)) return false;
    InitializeTimeline();
    State.LastEvent = TEXT("Live unranked battle started. Speed determines each action. Your party starts rested; no items, XP or currency rewards. Surrender or a missed turn counts as a loss.");
    PublishState();
    StartBattleSafetyChecks();
    return true;
}

bool ADigimonVenomNXTBattleActor::InitializeAITrainerBattle(ADigimonVenomNXTPlayerState* Player, const FDigimonBattleTeam& OpponentTeam, EDigimonBattleKind Kind, const FString& ContextId)
{

    if (!HasAuthority() || !Player || OpponentTeam.Active.Num() == 0 ||
        (Kind != EDigimonBattleKind::AITamer && Kind != EDigimonBattleKind::Season && Kind != EDigimonBattleKind::Story && Kind != EDigimonBattleKind::Friendly) ||
        (Kind != EDigimonBattleKind::Season && Player->HasActiveBattle())) return false;
    if (Kind == EDigimonBattleKind::Season && DigimonVenomNXTCampaign::HasPendingBattle(Player->Profile)) return false;
    bool bCampaignFinale = false;
    if (Kind == EDigimonBattleKind::Story)
    {
        EDigimonPrivateCampaign Campaign;
        FName NPCId;
        if (!DigimonVenomNXTCampaign::TryParseContext(ContextId, Campaign, NPCId)) return false;
        const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(Campaign, NPCId);
        const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner());
        const FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Player->Profile, Campaign);
        FString GateError;
        if (!Controller || !Controller->IsAccountAuthenticated() || !Controller->IsInRelay() ||
            Controller->GetStoryCampaign() != Campaign || Player->Profile.ActiveStoryCampaign != Campaign ||
            !Progress.bInside || !NPC || NPC->MapId != Progress.MapId ||
            DigimonVenomNXTCampaign::HasOtherPendingBattle(Player->Profile, Campaign) ||
            !DigimonVenomNXTCampaign::IsNPCVisible(Campaign, Progress, *NPC) ||
            !DigimonVenomNXTCampaign::CanChallenge(Campaign, Progress, *NPC, GateError)) return false;
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        if (!MatchesAuthoredCampaignTeam(Campaign, *NPC, OpponentTeam, Data)) return false;
        bCampaignFinale = NPC->Role == EDigimonRelayRole::FinalBoss;
    }
    if (Kind == EDigimonBattleKind::AITamer) Player->RecoverDefeatedParty();
    PlayerA = Player;
    PlayerB = nullptr;
    BattleContextId = ContextId;
    State = FDigimonBattleState();
    State.BattleId = FGuid::NewGuid();
    State.Kind = Kind;
    State.TeamA = BuildTeamFromProfile(Player->Profile, Kind == EDigimonBattleKind::Season || Kind == EDigimonBattleKind::Friendly, bCampaignFinale);
    State.TeamB = OpponentTeam;
    DigimonVenomNXTRecoveryCore::PrepareTeam(State.TeamB);
    if (State.TeamA.Active.IsEmpty() || IsTeamDefeated(State.TeamA) || IsTeamDefeated(State.TeamB)) return false;
    State.LastEvent = FString::Printf(TEXT("%s challenges you!"), *OpponentTeam.TrainerName);
    InitializeTimeline();
    if ((Kind == EDigimonBattleKind::Season || IsRelayBattle()) && !SaveSeasonCheckpoint()) return false;
    PublishState();
    StartBattleSafetyChecks();
    return true;
}



bool ADigimonVenomNXTBattleActor::SaveSeasonCheckpoint()
{
    if (!HasAuthority() || !PlayerA || (State.Kind != EDigimonBattleKind::Season && State.Kind != EDigimonBattleKind::Wild && !IsRelayBattle()) || PlayerA->Profile.AccountId.IsEmpty()) return false;
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles) return false;
    FDigimonPlayerProfile Candidate = PlayerA->Profile;
    FString& CheckpointJson = IsRelayBattle() ? DigimonVenomNXTCampaign::Progress(Candidate, BattleCampaign()).BattleCheckpointJson : State.Kind == EDigimonBattleKind::Wild ? Candidate.WorldBattleCheckpointJson : Candidate.Season.BattleCheckpointJson;
    if (State.bFinished) CheckpointJson.Reset();
    else
    {
        FDigimonSeasonBattleCheckpoint Checkpoint;
        Checkpoint.ContextId = BattleContextId;
        PendingA.GenerateKeyArray(State.ReadySlotsA);
        PendingB.GenerateKeyArray(State.ReadySlotsB);
        Checkpoint.State = State;
        // Animations already committed by the server are not replayed after reconnect.
        // The exact next decision and all pending player/AI commands are retained.
        Checkpoint.State.PresentationEvents.Reset();
        PendingA.GenerateValueArray(Checkpoint.CommandsA);
        PendingB.GenerateValueArray(Checkpoint.CommandsB);
        if (!FJsonObjectConverter::UStructToJsonObjectString(Checkpoint, CheckpointJson)) return false;
        if (IsRelayBattle())
        {
            FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Candidate, BattleCampaign());
            Progress.PendingBattleId = State.BattleId;
            Progress.PendingNPCId = BattleNPCId();
        }
    }
    if (State.bFinished)
    {
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
        UDigimonVenomNXTProfileSubsystem::ReconcileCombatBalance(Candidate, Data);
    }
    if (!Profiles->SaveProfile(Candidate)) return false;
    PlayerA->Profile = MoveTemp(Candidate);
    if (State.bFinished) DigimonVenomNXTServerActivity::Record(PlayerA, TEXT("Persistence"), TEXT("Battle settlement saved"), FString::Printf(TEXT("%s | context %s | progress, vitals and rewards committed"), *State.BattleId.ToString(EGuidFormats::Digits), *BattleContextId));
    return true;
}

bool ADigimonVenomNXTBattleActor::RestoreSeasonMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError)
{

    if (!HasAuthority() || !Player || Player->Profile.AccountId.IsEmpty()) return false;
    if (DigimonVenomNXTCampaign::HasPendingBattle(Player->Profile))
    { OutError = TEXT("Resume your saved private campaign battle before a Season match. Both saved decisions have been preserved."); return false; }
    const FDigimonSeasonCareer& Career = Player->Profile.Season;
    FDigimonSeasonBattleCheckpoint Checkpoint;
    const FDigimonSeasonMatch* Match = DigimonVenomNXTSeason::GetPlayerMatch(Career);
    if (Career.BattleCheckpointJson.IsEmpty() || Career.BattleCheckpointJson.Len() > 1024 * 1024 ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Career.BattleCheckpointJson, &Checkpoint, 0, 0) ||
        (Checkpoint.Version != 1 && Checkpoint.Version != 2) || !Match || Match->bResolved || Career.bScheduledBattleComplete ||
        Checkpoint.ContextId.IsEmpty() || Checkpoint.ContextId != Career.PendingContextId ||
        Checkpoint.ContextId != Match->MatchId || !Checkpoint.State.BattleId.IsValid() ||
        Checkpoint.State.Kind != EDigimonBattleKind::Season || Checkpoint.State.bAutomatic || Checkpoint.State.bFinished ||
        Checkpoint.State.TeamA.Active.IsEmpty() || Checkpoint.State.TeamB.Active.IsEmpty())
    {
        OutError = TEXT("Your saved Season decision could not be validated. Your saved progress has been preserved.");
        return false;
    }
    TSet<FGuid> Seen;
    for (const TArray<FDigimonBattleUnit>* Units : {&Checkpoint.State.TeamA.Active, &Checkpoint.State.TeamA.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            const FDigimonOwnedPartner* Partner = Player->Profile.Collection.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
            if (!Partner || !Player->Profile.Party.Contains(Unit.InstanceId) || Partner->SpeciesId != Unit.SpeciesId || Seen.Contains(Unit.InstanceId))
            {
                OutError = TEXT("The saved Season party no longer matches your collection. Saved progress has been preserved.");
                return false;
            }
            Seen.Add(Unit.InstanceId);
        }
    PlayerA = Player;
    PlayerB = nullptr;
    SetOwner(Player->GetOwner());
    BattleContextId = Checkpoint.ContextId;
    State = MoveTemp(Checkpoint.State);
    State.PresentationEvents.Reset();
    PendingA.Reset(); PendingB.Reset();
    bool bUpgraded = false;
    if (!RebuildRestoredBattle(bUpgraded, OutError)) return false;
    if (bUpgraded)
    {
        // Old whole-team rounds have no equivalent position in a continuous clock.
        // Keep the encounter, injuries and resources; ask for fresh unspent choices.
        Checkpoint.CommandsA.Reset(); Checkpoint.CommandsB.Reset();
    }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsA)
    {
        FString Error;
        if (!ValidateCommand(0, Command, Error)) { OutError = TEXT("A saved Season command is invalid. Saved progress has been preserved."); return false; }
        PendingA.Add(Command.ActingSlot, Command);
    }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsB)
    {
        FString Error;
        if (!ValidateCommand(1, Command, Error)) { OutError = TEXT("A saved opponent command is invalid. Saved progress has been preserved."); return false; }
        PendingB.Add(Command.ActingSlot, Command);
    }
    State.LastEvent = bUpgraded
        ? TEXT("Season battle updated to the speed timeline. Your saved HP/SP percentages, opponent and progress are preserved. Choose new commands for the new action order.")
        : FString::Printf(TEXT("Season resumed at action %d. Your HP, SP and speed timeline are restored."), State.TurnNumber);
    if (!SaveSeasonCheckpoint()) { OutError = TEXT("The updated Season decision could not be saved. Your previous saved battle remains intact."); return false; }
    ++State.PresentationSerial;
    PublishState();
    StartBattleSafetyChecks();
    return true;
}

void ADigimonVenomNXTBattleActor::SuspendSeasonMatch()
{
    if (!HasAuthority() || State.Kind != EDigimonBattleKind::Season || State.bFinished) return;
    // Every accepted decision was already saved atomically. Do not settle, heal,
    // or alter the checkpoint while disposing the disconnected world's actor.
    State.bFinished = true;
    State.WinningTeam = INDEX_NONE;
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
}

bool ADigimonVenomNXTBattleActor::FinishSeasonMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards)
{
    const ADigimonVenomNXTPlayerController* Controller = PlayerA ? Cast<ADigimonVenomNXTPlayerController>(PlayerA->GetOwner()) : nullptr;
    if (!HasAuthority() || !PlayerA || !Controller || !Controller->IsAccountAuthenticated() || Controller->CurrentBattle != this) return false;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data) return false;
    const FDigimonPlayerProfile Before = PlayerA->Profile;
    const FDigimonBattleState BeforeState = State;
    FDigimonPlayerProfile Candidate = Before;
    FString Summary = Reason;
    if (bGrantRewards && !DigimonVenomNXTSeason::SettleMatch(Candidate, BattleContextId, WinningTeam == 0, WinningTeam == INDEX_NONE, Data, Summary)) return false;

    int32 VictoryXP = 0;
    if (bGrantRewards && WinningTeam == 0)
    {
        for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamB.Active, &State.TeamB.Bench})
            for (const FDigimonBattleUnit& Unit : *Units)
            {
                FDigimonSpeciesDefinition Species;
                const int32 Tier = Data->GetSpecies(Unit.SpeciesId, Species) && Species.Stage != EDigimonStage::ReservedStage && Species.Stage != EDigimonStage::Unknown
                    ? DigimonVenomNXTCombatCore::StageRank(static_cast<int32>(Species.Stage)) : 2;
                VictoryXP += DigimonVenomNXTSeasonCore::MatchUnitXP(Unit.Level, Tier);
            }
    }
    VictoryXP = static_cast<int32>(FMath::Min<int64>(MAX_int32, DigimonVenomNXTRewardCore::Scale(VictoryXP, GetDefault<UDigimonVenomNXTSettings>()->ExperienceRate)));
    const int32 MaxLevel = FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel, 1, 200);
    int64 GrantedXP = 0;
    FString LevelUpSummary;
    TSet<FGuid> Updated;
    for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamA.Active, &State.TeamA.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            if (Updated.Contains(Unit.InstanceId)) continue;
            Updated.Add(Unit.InstanceId);
            FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
            if (!Partner) continue;
            int64 XP = 0;
            if (VictoryXP > 0)
            {
                const bool bActive = Units == &State.TeamA.Active;
                Partner->CAM = FMath::Min(100, FMath::Clamp(Partner->CAM, 0, 100) + (bActive ? 2 : 1));
                XP = bActive ? VictoryXP : DigimonVenomNXTSeasonCore::ReserveXP(VictoryXP);
            }
            const auto Award = DigimonVenomNXTProgressionCore::Apply(*Partner, XP, MaxLevel,
                [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
            GrantedXP = DigimonVenomNXTProgressionCore::AddSaturated(GrantedXP, Award.GrantedExperience);
            if (Award.LevelsGained > 0)
                LevelUpSummary += FString::Printf(TEXT(" %s LEVEL UP! Lv. %d → %d."), *Unit.DisplayName, Award.PreviousLevel, Award.Level);
            const FDigimonStats Stats = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data).Stats;
            Partner->CurrentHP = Stats.MaxHP;
            Partner->CurrentSP = Stats.MaxSP;
            Partner->CombatBalanceVersion = 1;
        }
    // Also repair banked partners and a deferred login correction in this same
    // durable Season transaction. An unsuccessful commit restores all old levels.
    for (FDigimonOwnedPartner& Partner : Candidate.Collection)
        if (Partner.IsValid()) DigimonVenomNXTProgressionCore::Apply(Partner, 0, MaxLevel,
            [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
    if (bGrantRewards)
    {
        Candidate.Season.LastMatchXP = VictoryXP;
        Candidate.Season.TotalExperienceEarned = FMath::Min<int64>(MAX_int64 - GrantedXP, FMath::Max<int64>(0, Candidate.Season.TotalExperienceEarned)) + GrantedXP;
    }
    else Summary += TEXT(" No result or rewards were recorded. Replay your saved scheduled opponent.");
    Candidate.Season.BattleCheckpointJson.Reset();
    DigimonVenomNXTSeason::EnsureCareer(Candidate, Data); // Refresh the real player roster after XP/CAM and recovery.
    PlayerA->Profile = MoveTemp(Candidate);
    State.bFinished = true;
    State.WinningTeam = WinningTeam;
    State.LastEvent = Summary + (VictoryXP > 0 ? FString::Printf(TEXT(" +%d XP per uncapped active partner; reserves receive half."), VictoryXP) : FString()) + LevelUpSummary;
    State.LastEvent += TEXT(" Season recovery restored your party to full HP and SP.");
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    // Normal commands persist the whole resolved round exactly once in SubmitCommand.
    // A safety closure outside that path still needs the same durable transaction.
    if (!bSeasonCommandTransaction)
    {
        if (!SaveSeasonCheckpoint())
        {
            PlayerA->Profile = Before;
            State = BeforeState;
            StartBattleSafetyChecks();
            return false;
        }
        PlayerA->MarkProfileChanged();
    }
    return true;
}

bool ADigimonVenomNXTBattleActor::IsParticipant(const AController* Controller) const
{
    if (!Controller) return false;
    return Controller->PlayerState == PlayerA || Controller->PlayerState == PlayerB;
}

int32 ADigimonVenomNXTBattleActor::LivingActiveCount(const FDigimonBattleTeam& Team) const
{
    int32 Count = 0;
    for (const FDigimonBattleUnit& U : Team.Active) if (!U.bDefeated && U.HP > 0) ++Count;
    return Count;
}

bool ADigimonVenomNXTBattleActor::ValidateCommand(int32 TeamIndex, const FDigimonBattleCommand& Command, FString& OutError) const
{
    if (State.bFinished) { OutError = TEXT("Battle has already ended."); return false; }
    if (bUnrankedSettlementPending) { OutError = TEXT("Your match result is being saved. Please wait; no further actions are needed."); return false; }
    if (State.bAutomatic) { OutError = TEXT("Ranked matches play automatically."); return false; }
    if (TeamIndex != 0 && TeamIndex != 1) { OutError = TEXT("Invalid battle team."); return false; }
    if (static_cast<uint8>(Command.Action) > static_cast<uint8>(EDigimonBattleAction::Guard))
    { OutError = TEXT("That battle action is unavailable."); return false; }
    const FDigimonBattleTeam& Team = TeamIndex == 0 ? State.TeamA : State.TeamB;
    const FDigimonBattleTeam& Enemy = TeamIndex == 0 ? State.TeamB : State.TeamA;
    if (!Team.Active.IsValidIndex(Command.ActingSlot) || Team.Active[Command.ActingSlot].bDefeated || Team.Active[Command.ActingSlot].HP <= 0) { OutError = TEXT("Invalid acting partner."); return false; }
    if (Command.Action == EDigimonBattleAction::Retreat)
    {
        if (!DigimonVenomNXTBattlePolicyCore::MayFlee(static_cast<int32>(State.Kind), TeamIndex, State.bFinished, State.bAutomatic, PlayerB != nullptr))
        { OutError = TEXT("You can flee only from a wild Digimon encounter."); return false; }
        return true;
    }
    if (TeamIndex != State.ActingTeam || Command.ActingSlot != State.ActingSlot)
    { OutError = TEXT("Wait for this partner's next action. Speed determines the turn order."); return false; }
    if (Command.Action == EDigimonBattleAction::Guard) return true;
    if (Command.Action == EDigimonBattleAction::Switch)
    {
        if (!Team.Bench.IsValidIndex(Command.SwitchBenchIndex) || Team.Bench[Command.SwitchBenchIndex].bDefeated || Team.Bench[Command.SwitchBenchIndex].HP <= 0)
        { OutError = TEXT("Invalid switch target."); return false; }
        return true;
    }
    if (Command.Action == EDigimonBattleAction::Item)
    {
        if (State.Kind == EDigimonBattleKind::Friendly) { OutError = TEXT("Items are disabled in unranked sparring. Use a skill, Guard, Attack or switch your partner."); return false; }
        const ADigimonVenomNXTPlayerState* UsingPlayer = TeamIndex == 0 ? PlayerA.Get() : PlayerB.Get();
        if (!UsingPlayer) { OutError = TEXT("AI teams cannot use player inventory."); return false; }
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
        FDigimonShopItemDefinition Item;
        if (!Data || !Data->GetShopItem(Command.ItemId, Item) || (Item.HPHeal <= 0 && Item.SPHeal <= 0))
        { OutError = TEXT("That item cannot be used in battle."); return false; }
        const FDigimonBattleUnit& Target = Team.Active[Command.ActingSlot];
        if ((Item.HPHeal > 0 && Target.HP >= Target.Stats.MaxHP) || (Item.SPHeal > 0 && Target.SP >= Target.Stats.MaxSP))
        { OutError = TEXT("This partner's resource is already full. No item was used."); return false; }
        if (UsingPlayer->GetInventoryQuantity(Command.ItemId) <= 0)
        {
            OutError = TEXT("You do not have that battle item."); return false;
        }
    }
    if (Command.Action != EDigimonBattleAction::Item && Command.Action != EDigimonBattleAction::Retreat)
    {
        if (!Enemy.Active.IsValidIndex(Command.TargetSlot) || Enemy.Active[Command.TargetSlot].bDefeated || Enemy.Active[Command.TargetSlot].HP <= 0) { OutError = TEXT("Invalid target."); return false; }
    }
    const int32 MoveIndex = static_cast<int32>(Command.Action) - static_cast<int32>(EDigimonBattleAction::Move1);
    if (MoveIndex >= 0 && MoveIndex <= 3)
    {
        const FDigimonBattleUnit& Unit = Team.Active[Command.ActingSlot];
        if (!Unit.Moves.IsValidIndex(MoveIndex)) { OutError = TEXT("That move slot is empty."); return false; }
        if (Unit.Moves[MoveIndex].SPCost < 0 || Unit.SP < Unit.Moves[MoveIndex].SPCost) { OutError = TEXT("Not enough SP."); return false; }
    }
    return true;
}

bool ADigimonVenomNXTBattleActor::SubmitCommand(AController* FromController, const FDigimonBattleCommand& Command, FString& OutError)
{
    if (!HasAuthority() || !FromController) { OutError = TEXT("Only the server may submit battle commands."); return false; }
    int32 TeamIndex = INDEX_NONE;
    if (FromController->PlayerState == PlayerA) TeamIndex = 0;
    else if (FromController->PlayerState == PlayerB) TeamIndex = 1;
    if (TeamIndex == INDEX_NONE) { OutError = TEXT("You are not a participant in this battle."); return false; }
    auto PublishReadiness = [this]()
    {
        if (State.bAutomatic) return;
        State.PresentationEvents.Reset();
        ++State.PresentationSerial;
        PublishState();
    };
    if (!DigimonVenomNXTCombatCore::IsCurrentDecision(State.BattleId, State.TurnNumber,
        Command.ExpectedBattleId, Command.ExpectedTurnNumber))
    {
        PublishReadiness();
        OutError = TEXT("That command belongs to an earlier battle or turn. Choose a command for the current turn.");
        return false;
    }
    if (State.Kind == EDigimonBattleKind::Friendly && !State.bFinished && !bUnrankedSettlementPending &&
        (State.ActingTeam == 0 || PlayerB) && FPlatformTime::Seconds() >= UnrankedDecisionDeadline)
    {
        CheckBattleSafety();
        OutError = TEXT("The unranked turn deadline has passed.");
        return false;
    }
    if (!State.bAutomatic && !EnsureBattleCanContinue()) { OutError = TEXT("Battle state updated. Please choose your command again or return from the result screen."); return false; }
    if (!ValidateCommand(TeamIndex, Command, OutError)) { PublishReadiness(); return false; }

    // Retried/rapid commands can never replace a committed slot or spill into the
    // next round. The next-round guard above applies to every manual battle kind.
    if (Command.Action != EDigimonBattleAction::Retreat && (TeamIndex == 0 ? PendingA : PendingB).Contains(Command.ActingSlot))
    {
        PublishReadiness();
        return true;
    }

    const auto RecordAccepted = [&](bool bDurable)
    {
        DigimonVenomNXTServerActivity::Record(FromController, TEXT("Battle"), TEXT("Command accepted"),
            FString::Printf(TEXT("%s | decision %d | %s | slot %d | %s"), *Command.ExpectedBattleId.ToString(EGuidFormats::Digits),
                Command.ExpectedTurnNumber, *UEnum::GetValueAsString(Command.Action), Command.ActingSlot + 1,
                bDurable ? TEXT("decision saved") : TEXT("server accepted; standard battle settlement")));
    };

    // Retreat is a team-level decision. Resolve it immediately instead of waiting
    // for commands from every other active partner in a 3-v-3 formation.
    if (Command.Action == EDigimonBattleAction::Retreat && State.Kind != EDigimonBattleKind::Wild && !IsRelayBattle())
    {
        State.PresentationEvents.Reset();
        ResolveOne(TeamIndex, Command);
        CapturePostState(0);
        ++State.PresentationSerial;
        PendingA.Reset();
        PendingB.Reset();
        PublishState();
        RecordAccepted(false);
        return true;
    }

    if (State.Kind == EDigimonBattleKind::Season || State.Kind == EDigimonBattleKind::Wild || IsRelayBattle())
    {
        // Persist one complete decision transaction before its animation or rewards
        // become visible. A failed save restores items, commands, HP/SP and progression.
        const FDigimonPlayerProfile BeforeProfile = PlayerA->Profile;
        const FDigimonBattleState BeforeState = State;
        const TMap<int32, FDigimonBattleCommand> BeforeA = PendingA;
        const TMap<int32, FDigimonBattleCommand> BeforeB = PendingB;
        bSeasonCommandTransaction = true;
        bSeasonSettlementFailed = false;
        // Prior-round events must never be replayed by a partial command acknowledgement.
        State.PresentationEvents.Reset();
        if (Command.Action == EDigimonBattleAction::Retreat)
        {
            ResolveOne(TeamIndex, Command);
            CapturePostState(0);
            ++State.PresentationSerial;
            PendingA.Reset(); PendingB.Reset();
        }
        else
        {
            PendingA.Add(Command.ActingSlot, Command);
            AutoFillAICommands();
            TryResolveRound();
        }
        if (State.PresentationEvents.IsEmpty() && !State.bFinished) ++State.PresentationSerial;
        const bool bSaved = !bSeasonSettlementFailed && SaveSeasonCheckpoint();
        bSeasonCommandTransaction = false;
        if (!bSaved)
        {
            PlayerA->Profile = BeforeProfile;
            State = BeforeState;
            PendingA = BeforeA;
            PendingB = BeforeB;
            State.PresentationEvents.Reset();
            State.LastEvent = TEXT("Your last decision could not be saved. No action or reward was committed; please retry your command.");
            ++State.PresentationSerial;
            PlayerA->MarkProfileChanged();
            StartBattleSafetyChecks();
            PublishState();
            OutError = State.LastEvent;
            return false;
        }
        PlayerA->MarkProfileChanged();
        PublishState();
        RecordAccepted(true);
        return true;
    }
    const int32 BeforeTurn = State.TurnNumber;
    State.PresentationEvents.Reset();
    (TeamIndex == 0 ? PendingA : PendingB).Add(Command.ActingSlot, Command);
    AutoFillAICommands();
    TryResolveRound();
    if (!State.bFinished && State.TurnNumber == BeforeTurn) PublishReadiness();
    RecordAccepted(false);
    return true;
}

void ADigimonVenomNXTBattleActor::AutoFillAICommands()
{
    if (PlayerB != nullptr || State.ActingTeam != 1) return;
    const int32 i = State.ActingSlot;
    if (State.TeamB.Active.IsValidIndex(i))
    {
        const FDigimonBattleUnit& Unit = State.TeamB.Active[i];
        if (Unit.bDefeated || Unit.HP <= 0 || PendingB.Contains(i)) return;
        auto Attacker = DigimonVenomNXTAutoBattle::ToCoreUnit(Unit);
        Attacker.DamageMultiplier = DigimonVenomNXTBattlePolicyCore::EnemyDamageMultiplier(static_cast<int32>(State.Kind), 1, false);
        int32 BestTarget = INDEX_NONE, BestMove = INDEX_NONE;
        double BestScore = -1.0;
        for (int32 Target = 0; Target < State.TeamA.Active.Num(); ++Target)
        {
            const FDigimonBattleUnit& Opponent = State.TeamA.Active[Target];
            if (Opponent.bDefeated || Opponent.HP <= 0) continue;
            const auto Defender = DigimonVenomNXTAutoBattle::ToCoreUnit(Opponent);
            const int32 MoveIndex = DigimonVenomNXTCombatCore::ChooseMove(Attacker, Defender);
            const auto Move = MoveIndex >= 0 ? Attacker.Moves[MoveIndex] : DigimonVenomNXTCombatCore::Move{};
            const int32 ExpectedDamage = DigimonVenomNXTCombatCore::CalculateDamage(Attacker, Defender, Move, 1.0f);
            const double Score = DigimonVenomNXTCombatCore::TargetScore(ExpectedDamage, Opponent.HP, Opponent.Stats.MaxHP);
            if (Score > BestScore)
            { BestScore = Score; BestTarget = Target; BestMove = MoveIndex; }
        }
        if (BestTarget == INDEX_NONE) return;
        FDigimonBattleCommand Cmd;
        Cmd.Action = BestMove < 0 ? EDigimonBattleAction::Attack :
            static_cast<EDigimonBattleAction>(static_cast<int32>(EDigimonBattleAction::Move1) + BestMove);
        Cmd.ActingSlot = i;
        Cmd.TargetSlot = BestTarget;
        PendingB.Add(i, Cmd);
    }
}

void ADigimonVenomNXTBattleActor::TryResolveRound()
{
    if (!EnsureBattleCanContinue()) return;
    // A CTB decision belongs to one identity, not to every slot in a team round.
    if (!(State.ActingTeam == 0 ? PendingA : PendingB).Contains(State.ActingSlot)) return;
    ResolveRound();
}

int32 ADigimonVenomNXTBattleActor::ComputeDamage_Implementation(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, int32 Power) const
{
    FDigimonMoveSlot Move;
    Move.Power = FMath::Max(1, Power);
    return ComputeMoveDamage(Attacker, Defender, Move);
}

int32 ADigimonVenomNXTBattleActor::ComputeMoveDamage_Implementation(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, const FDigimonMoveSlot& Move) const
{
    auto CoreAttacker = DigimonVenomNXTAutoBattle::ToCoreUnit(Attacker);
    const bool bEnemy = State.TeamB.Active.ContainsByPredicate([&Attacker](const FDigimonBattleUnit& Unit) { return Unit.InstanceId == Attacker.InstanceId; });
    CoreAttacker.DamageMultiplier = DigimonVenomNXTBattlePolicyCore::EnemyDamageMultiplier(static_cast<int32>(State.Kind), bEnemy ? 1 : 0, PlayerB != nullptr);
    const FDigimonBattleTeam& Allies = bEnemy ? State.TeamB : State.TeamA;
    const bool bCanCombo = !bEnemy || PlayerB != nullptr || State.Kind == EDigimonBattleKind::Ranked || State.Kind == EDigimonBattleKind::Friendly;
    const float Combo = bCanCombo ? DigimonVenomNXTCombatCore::ComboMultiplier(Attacker.CAM, LivingActiveCount(Allies) > 1, FMath::FRand()) : 1.0f;
    LastDamageCombo = Combo;
    return DigimonVenomNXTCombatCore::CalculateDamage(CoreAttacker,
        DigimonVenomNXTAutoBattle::ToCoreUnit(Defender), DigimonVenomNXTAutoBattle::ToCoreMove(Move), FMath::FRandRange(0.92f, 1.08f), Combo);
}

void ADigimonVenomNXTBattleActor::ResolveOne(int32 TeamIndex, const FDigimonBattleCommand& Command)
{
    FDigimonBattleTeam& Team = TeamIndex == 0 ? State.TeamA : State.TeamB;
    FDigimonBattleTeam& Enemy = TeamIndex == 0 ? State.TeamB : State.TeamA;
    if (!Team.Active.IsValidIndex(Command.ActingSlot)) return;
    FDigimonBattleUnit& Attacker = Team.Active[Command.ActingSlot];
    if (Attacker.bDefeated || Attacker.HP <= 0) return;

    FDigimonBattlePresentationEvent VisualEvent;
    VisualEvent.ActingTeam = TeamIndex;
    VisualEvent.ActingSlot = Command.ActingSlot;
    VisualEvent.ActingInstanceId = Attacker.InstanceId;
    VisualEvent.Action = Command.Action;

    if (Command.Action == EDigimonBattleAction::Retreat)
    {
        // Recheck at execution as well: forged, restored or Blueprint-created commands
        // cannot turn a trainer, story, Friendly, Season or Ranked battle into an escape.
        if (!DigimonVenomNXTBattlePolicyCore::MayFlee(static_cast<int32>(State.Kind), TeamIndex, State.bFinished, State.bAutomatic, PlayerB != nullptr)) return;
        State.bFled = true;
        VisualEvent.Text = TEXT("Escaped safely. Your party keeps its current HP and SP. No battle rewards were earned.");
        State.PresentationEvents.Add(VisualEvent);
        FinishBattle(INDEX_NONE, VisualEvent.Text, false);
        return;
    }
    if (Command.Action == EDigimonBattleAction::Guard)
    {
        Attacker.bGuarding = true;
        State.LastEvent = Attacker.DisplayName + TEXT(" is guarding. Incoming damage is halved until its next action.");
        VisualEvent.TargetTeam = TeamIndex;
        VisualEvent.TargetSlot = Command.ActingSlot;
        VisualEvent.Text = State.LastEvent;
        State.PresentationEvents.Add(VisualEvent);
        return;
    }
    if (Command.Action == EDigimonBattleAction::Switch)
    {
        if (Team.Bench.IsValidIndex(Command.SwitchBenchIndex))
        {
            Swap(Team.Active[Command.ActingSlot], Team.Bench[Command.SwitchBenchIndex]);
            Team.Active[Command.ActingSlot].NextActionTime = DigimonVenomNXTTimelineCore::NextTime(State.BattleClock, Team.Active[Command.ActingSlot].Stats.Speed);
            Team.Active[Command.ActingSlot].bGuarding = false;
            Team.Bench[Command.SwitchBenchIndex].NextActionTime = -1.0;
            Team.Bench[Command.SwitchBenchIndex].bGuarding = false;
            State.LastEvent = Team.TrainerName + TEXT(" switched partners.");
            VisualEvent.TargetTeam = TeamIndex;
            VisualEvent.TargetSlot = Command.ActingSlot;
            VisualEvent.Text = State.LastEvent;
            State.PresentationEvents.Add(VisualEvent);
        }
        return;
    }
    if (Command.Action == EDigimonBattleAction::Item)
    {
        ADigimonVenomNXTPlayerState* UsingPlayer = TeamIndex == 0 ? PlayerA.Get() : PlayerB.Get();
        if (!UsingPlayer || Command.ItemId.IsNone()) return;
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
        FDigimonShopItemDefinition Item;
        if (!Data || !Data->GetShopItem(Command.ItemId, Item) || (Item.HPHeal <= 0 && Item.SPHeal <= 0)) return;
        if (!UsingPlayer->ConsumeBattleItem(Command.ItemId, 1))
        {
            State.LastEvent = Team.TrainerName + TEXT(" has none of that item left.");
            VisualEvent.Text = State.LastEvent;
            State.PresentationEvents.Add(VisualEvent);
            return;
        }
        if (Item.HPHeal > 0)
        {
            Attacker.HP = FMath::Min(Attacker.Stats.MaxHP, Attacker.HP + Item.HPHeal);
            Attacker.bDefeated = false;
            State.LastEvent = FString::Printf(TEXT("%s restored HP to %s."), *Team.TrainerName, *Attacker.DisplayName);
        }
        else
        {
            Attacker.SP = FMath::Min(Attacker.Stats.MaxSP, Attacker.SP + Item.SPHeal);
            State.LastEvent = FString::Printf(TEXT("%s restored SP to %s."), *Team.TrainerName, *Attacker.DisplayName);
        }
        VisualEvent.TargetTeam = TeamIndex;
        VisualEvent.TargetSlot = Command.ActingSlot;
        VisualEvent.Text = State.LastEvent;
        State.PresentationEvents.Add(VisualEvent);
        return;
    }

    int32 TargetSlot = Command.TargetSlot;
    if (!Enemy.Active.IsValidIndex(TargetSlot) || Enemy.Active[TargetSlot].bDefeated || Enemy.Active[TargetSlot].HP <= 0)
    {
        // Another faster ally may already have defeated the selected opponent.
        // Retarget a living active opponent instead of silently losing this turn.
        TargetSlot = Enemy.Active.IndexOfByPredicate([](const FDigimonBattleUnit& Unit) { return !Unit.bDefeated && Unit.HP > 0; });
    }
    if (TargetSlot == INDEX_NONE) return;
    FDigimonBattleUnit& Defender = Enemy.Active[TargetSlot];
    FDigimonMoveSlot Move; // Neutral physical Attack: 100% power, always 0 SP.
    FString MoveName = TEXT("Attack");
    const int32 MoveIndex = static_cast<int32>(Command.Action) - static_cast<int32>(EDigimonBattleAction::Move1);
    if (MoveIndex >= 0 && MoveIndex <= 3)
    {
        if (!Attacker.Moves.IsValidIndex(MoveIndex)) return;
        Move = Attacker.Moves[MoveIndex];
        if (Move.SPCost < 0 || Attacker.SP < Move.SPCost) return;
        Attacker.SP -= Move.SPCost;
        MoveName = Move.DisplayName.IsEmpty() ? Move.MoveId.ToString() : Move.DisplayName.ToString();
    }
    LastDamageCombo = 1.0f;
    const int32 Damage = FMath::Clamp(ComputeMoveDamage(Attacker, Defender, Move), 1, Defender.HP);
    VisualEvent.ComboMultiplier = LastDamageCombo;
    VisualEvent.bGuarded = Defender.bGuarding;
    Defender.HP = FMath::Max(0, Defender.HP - Damage);
    VisualEvent.Effectiveness = DigimonVenomNXTCombatCore::Effectiveness(static_cast<int32>(Attacker.Affinity),
        static_cast<int32>(Defender.Affinity), static_cast<int32>(Move.Element), static_cast<int32>(Defender.Element));
    VisualEvent.TypeMultiplier = DigimonVenomNXTCombatCore::Effectiveness(static_cast<int32>(Attacker.Affinity),
        static_cast<int32>(Defender.Affinity), 0, 0);
    VisualEvent.ElementMultiplier = DigimonVenomNXTCombatCore::Effectiveness(0, 0,
        static_cast<int32>(Move.Element), static_cast<int32>(Defender.Element));
    VisualEvent.DamageClass = Move.DamageClass;
    VisualEvent.Element = Move.Element;
    State.LastEvent = FString::Printf(TEXT("%s used %s on %s: %d damage.%s"), *Attacker.DisplayName, *MoveName,
        *Defender.DisplayName, Damage, VisualEvent.Effectiveness > 1.001f ? TEXT(" Super effective!") :
        VisualEvent.Effectiveness < 0.999f ? TEXT(" Not very effective.") : TEXT(""));
    if (VisualEvent.ComboMultiplier > 1.0f) State.LastEvent += TEXT(" Team combo!");
    if (VisualEvent.bGuarded) State.LastEvent += TEXT(" Guard reduced the damage.");
    VisualEvent.TargetTeam = TeamIndex == 0 ? 1 : 0;
    VisualEvent.TargetSlot = TargetSlot;
    VisualEvent.TargetInstanceId = Defender.InstanceId;
    VisualEvent.Damage = Damage;
    VisualEvent.Text = State.LastEvent;
    State.PresentationEvents.Add(VisualEvent);
    if (Defender.HP <= 0)
    {
        Defender.bDefeated = true;
        State.LastEvent += TEXT(" It was defeated!");
        if (TeamIndex == 0 && State.Kind == EDigimonBattleKind::Wild) RecordWildDefeat(Defender);
        State.PresentationEvents.Last().Text = State.LastEvent;
        PromoteBench(Enemy);
    }
}

void ADigimonVenomNXTBattleActor::PromoteBench(FDigimonBattleTeam& Team)
{
    const bool bManualFormation = &Team == &State.TeamA && DigimonVenomNXTBattlePolicyCore::UsesSourcePlayerFormation(static_cast<int32>(State.Kind), State.bAutomatic);
    DigimonVenomNXTRecoveryCore::PrepareTeam(Team, !bManualFormation);
    if (State.CombatBalanceVersion > 0)
        for (FDigimonBattleUnit& Unit : Team.Active)
            if (!Unit.bDefeated && Unit.HP > 0 && Unit.NextActionTime < 0.0)
            {
                Unit.NextActionTime = DigimonVenomNXTTimelineCore::NextTime(State.BattleClock, Unit.Stats.Speed);
                Unit.bGuarding = false;
            }
}

bool ADigimonVenomNXTBattleActor::IsTeamDefeated(const FDigimonBattleTeam& Team) const
{
    if (&Team == &State.TeamA && DigimonVenomNXTBattlePolicyCore::UsesSourcePlayerFormation(static_cast<int32>(State.Kind), State.bAutomatic))
        return !DigimonVenomNXTRecoveryCore::HasLivingUnit(Team.Active);
    return DigimonVenomNXTRecoveryCore::IsTeamDefeated(Team);
}

void ADigimonVenomNXTBattleActor::StartBattleSafetyChecks()
{
    if (HasAuthority() && GetWorld() && !State.bAutomatic && !State.bFinished)
        GetWorld()->GetTimerManager().SetTimer(BattleSafetyTimer, this, &ADigimonVenomNXTBattleActor::CheckBattleSafety, 1.0f, true);
}

void ADigimonVenomNXTBattleActor::ResetUnrankedDeadline()
{
    if (State.Kind != EDigimonBattleKind::Friendly || !HasAuthority()) return;
    const double Now = FPlatformTime::Seconds();
    if (UnrankedStartedAt == 0.0) UnrankedStartedAt = Now;
    // Presentation actions can precede input. Give both peers a bounded playback allowance.
    const int32 Seconds = 90 + FMath::Clamp(State.PresentationEvents.Num() * 3, 0, 120);
    UnrankedDecisionDeadline = Now + Seconds;
    UnrankedDecisionDeadlineServerTime = GetWorld()->GetTimeSeconds() + Seconds;
}

bool ADigimonVenomNXTBattleActor::ForfeitUnranked(AController* Controller, const FString& Reason)
{
    if (!HasAuthority() || State.Kind != EDigimonBattleKind::Friendly || State.bFinished || bUnrankedSettlementPending || !IsParticipant(Controller)) return false;
    const int32 Winner = Controller->PlayerState == PlayerA ? 1 : 0;
    State.PresentationEvents.Reset();
    FinishBattle(Winner, Reason);
    PendingA.Reset(); PendingB.Reset();
    ++State.PresentationSerial;
    PublishState();
    return true;
}

void ADigimonVenomNXTBattleActor::CheckBattleSafety()
{

    if (bUnrankedSettlementPending)
    {
        if (FPlatformTime::Seconds() >= NextUnrankedSettlementAttempt)
        {
            NextUnrankedSettlementAttempt = FPlatformTime::Seconds() + 3.0;
            if (FinishUnrankedMatch(PendingUnrankedWinner, PendingUnrankedReason, true))
            {
                ++State.PresentationSerial;
                PublishState();
                TryDestroyWhenUnused();
            }
        }
        return;
    }
    if (State.Kind == EDigimonBattleKind::Friendly && !State.bFinished)
    {
        auto Connected = [this](ADigimonVenomNXTPlayerState* Player)
        {
            const auto* PC = Player ? Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner()) : nullptr;
            return PC && PC->IsAccountAuthenticated() && PC->CurrentBattle == this;
        };
        const bool HasA = Connected(PlayerA);
        const bool HasB = PlayerB ? Connected(PlayerB) : true;
        int32 Winner = INDEX_NONE;
        FString Reason;
        if (!HasA || !HasB)
        {
            Winner = HasA == HasB ? INDEX_NONE : HasA ? 0 : 1;
            Reason = TEXT("Unranked match ended after a participant disconnected.");
        }
        else if (FPlatformTime::Seconds() - UnrankedStartedAt >= 1800.0 || State.TurnNumber >= 1000)
            Reason = TEXT("Unranked match drawn: the match duration limit was reached.");
        else if (State.ActingTeam == 0 || PlayerB)
        {
            if (FPlatformTime::Seconds() >= UnrankedDecisionDeadline)
            {
                Winner = State.ActingTeam == 0 ? 1 : 0;
                Reason = TEXT("Unranked match ended: a tamer did not choose an action before the turn deadline.");
            }
        }
        if (!Reason.IsEmpty())
        {
            State.PresentationEvents.Reset();
            FinishBattle(Winner, Reason);
            PendingA.Reset(); PendingB.Reset();
            ++State.PresentationSerial;
            PublishState();
            return;
        }
    }
    if (EnsureBattleCanContinue()) AdvanceOpeningAI();
}

bool ADigimonVenomNXTBattleActor::EnsureBattleCanContinue()
{
    if (!HasAuthority() || State.bFinished || State.bAutomatic || bUnrankedSettlementPending) return false;
    const bool bSourceFormation = DigimonVenomNXTBattlePolicyCore::UsesSourcePlayerFormation(static_cast<int32>(State.Kind), State.bAutomatic);
    const bool bChangedA = DigimonVenomNXTRecoveryCore::PrepareTeam(State.TeamA, !bSourceFormation);
    const bool bChangedB = DigimonVenomNXTRecoveryCore::PrepareTeam(State.TeamB);
    const bool bNoInputA = LivingActiveCount(State.TeamA) == 0;
    const bool bNoInputB = LivingActiveCount(State.TeamB) == 0;
    if (bNoInputA || bNoInputB)
    {
        State.PresentationEvents.Reset();
        // This is a safety repair, not a played victory. Invalid/empty formations
        // must never grant scans, currency, XP, story badges or a season result.
        const int32 Winner = bNoInputA == bNoInputB ? INDEX_NONE : bNoInputA ? 1 : 0;
        FinishBattle(Winner, TEXT("The battle ended because a team could no longer act."), false);
        PendingA.Reset(); PendingB.Reset();
        ++State.PresentationSerial;
        PublishState();
        return false;
    }
    if (bChangedA || bChangedB)
    {
        PendingA.Reset(); PendingB.Reset();
        State.PresentationEvents.Reset();
        PromoteBench(State.TeamA);
        PromoteBench(State.TeamB);
        SelectNextActor();
        State.LastEvent = TEXT("Ready partners moved into the active formation. The speed timeline has been updated.");
        ++State.PresentationSerial;
        PublishState();
        return false;
    }
    return true;
}

bool ADigimonVenomNXTBattleActor::RebuildRestoredBattle(bool& bUpgraded, FString& OutError)
{
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data || !PlayerA) { OutError = TEXT("Battle data is not ready. Your saved decision is unchanged."); return false; }
    if (State.CombatBalanceVersion < 0 || State.CombatBalanceVersion > DigimonVenomNXTAutoBattle::CurrentBalanceVersion)
    { OutError = TEXT("This saved battle uses an unsupported combat version. Your saved decision is preserved."); return false; }
    bUpgraded = State.CombatBalanceVersion < DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    if (State.Kind == EDigimonBattleKind::Wild)
    {
        if (State.bWildMasteryPaid || State.ScannedWildInstances.Num() > 3 || State.WildMasteryHundredths.Num() > 3)
        { OutError = TEXT("The saved scan settlement is invalid. Your checkpoint is preserved."); return false; }
        TSet<FGuid> ScanIds, PendingIds;
        for (const FGuid& Id : State.ScannedWildInstances)
        {
            const FDigimonBattleUnit* Unit = State.TeamB.Active.FindByPredicate([&Id](const FDigimonBattleUnit& U) { return U.InstanceId == Id; });
            if (!Unit || Unit->HP > 0 || ScanIds.Contains(Id))
            { OutError = TEXT("The saved defeat scan receipt is invalid. Your checkpoint is preserved."); return false; }
            ScanIds.Add(Id);
        }
        for (const FDigimonWildScanMasteryPending& Pending : State.WildMasteryHundredths)
        {
            const FDigimonBattleUnit* Unit = State.TeamB.Active.FindByPredicate([&Pending](const FDigimonBattleUnit& U) { return U.InstanceId == Pending.InstanceId; });
            if (!Unit || Unit->Variant == EDigimonVariant::Normal || !ScanIds.Contains(Pending.InstanceId) ||
                PendingIds.Contains(Pending.InstanceId) || Pending.Hundredths < 0 || Pending.Hundredths > DigimonVenomNXTRewardCore::MasteryHundredths(999))
            { OutError = TEXT("The saved mastery receipt is invalid. Your checkpoint is preserved."); return false; }
            PendingIds.Add(Pending.InstanceId);
        }
    }
    const FDigimonSeasonTamer* ScheduledOpponent = nullptr;
    if (State.Kind == EDigimonBattleKind::Season)
    {
        const FDigimonSeasonMatch* Match = DigimonVenomNXTSeason::GetPlayerMatch(PlayerA->Profile.Season);
        if (Match) ScheduledOpponent = DigimonVenomNXTSeason::FindTamer(PlayerA->Profile.Season,
            Match->HomeTamerId == TEXT("player") ? Match->AwayTamerId : Match->HomeTamerId);
        if (!ScheduledOpponent || ScheduledOpponent->bPlayer)
        { OutError = TEXT("The scheduled opponent is unavailable. Your saved Season decision is preserved."); return false; }
    }
    if (!bUpgraded && (!FMath::IsFinite(State.BattleClock) || State.BattleClock < 0.0 || State.bFled))
    { OutError = TEXT("The saved speed timeline is invalid. Your saved decision is preserved."); return false; }
    for (int32 TeamIndex = 0; TeamIndex < 2; ++TeamIndex)
    {
        FDigimonBattleTeam& Team = TeamIndex == 0 ? State.TeamA : State.TeamB;
        TSet<int32> Identities;
        TSet<FGuid> SeenUnits;
        for (TArray<FDigimonBattleUnit>* Units : {&Team.Active, &Team.Bench})
            for (FDigimonBattleUnit& Unit : *Units)
            {
                const FDigimonOwnedPartner* Partner = TeamIndex == 0 ? PlayerA->Profile.Collection.FindByPredicate(
                    [&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; }) : nullptr;
                if (TeamIndex == 1 && ScheduledOpponent)
                    Partner = ScheduledOpponent->Team.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
                const bool bNeedsPersistedPartner = TeamIndex == 0 || ScheduledOpponent != nullptr;
                if (!Unit.InstanceId.IsValid() || SeenUnits.Contains(Unit.InstanceId) ||
                    (bNeedsPersistedPartner && (!Partner || Partner->SpeciesId != Unit.SpeciesId || Partner->Level != Unit.Level || Partner->Variant != Unit.Variant)))
                { OutError = TEXT("A saved combatant no longer matches its owned or scheduled roster. Your saved decision is preserved."); return false; }
                SeenUnits.Add(Unit.InstanceId);
                if (Unit.CombatBalanceVersion < 0 || Unit.CombatBalanceVersion > DigimonVenomNXTAutoBattle::CurrentBalanceVersion ||
                    !DigimonVenomNXTAutoBattle::RebuildSavedUnit(Unit, Data, Partner,
                    TeamIndex == 1 && State.Kind == EDigimonBattleKind::Wild, TeamIndex == 1 && IsRelayBattle() && State.Kind == EDigimonBattleKind::Wild))
                { OutError = TEXT("A saved combatant could not be rebuilt from the species catalog. Your saved decision is unchanged."); return false; }
                if (!bUpgraded)
                {
                    if (Unit.TimelineOrder < 0 || Identities.Contains(Unit.TimelineOrder) ||
                        !FMath::IsFinite(Unit.NextActionTime) ||
                        (Units == &Team.Active && Unit.HP > 0 && Unit.NextActionTime < State.BattleClock))
                    { OutError = TEXT("The saved action order is invalid. Your saved decision is preserved."); return false; }
                    Identities.Add(Unit.TimelineOrder);
                }
            }
    }
    if (bUpgraded) InitializeTimeline();
    else
    {
        if (State.InitialActiveCount <= 0) State.InitialActiveCount = State.TeamA.Active.Num() + State.TeamB.Active.Num();
        const int32 SavedTeam = State.ActingTeam, SavedSlot = State.ActingSlot;
        if (!SelectNextActor() || SavedTeam != State.ActingTeam || SavedSlot != State.ActingSlot)
        { OutError = TEXT("The saved next actor does not match its speed timeline. Your saved decision is preserved."); return false; }
    }
    return true;
}

void ADigimonVenomNXTBattleActor::InitializeTimeline()
{
    State.BattleClock = 0.0;
    State.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    State.InitialActiveCount = State.TeamA.Active.Num() + State.TeamB.Active.Num();
    for (FDigimonBattleTeam* Team : {&State.TeamA, &State.TeamB})
    {
        int32 Identity = 0;
        for (FDigimonBattleUnit& Unit : Team->Active)
        {
            Unit.TimelineOrder = Identity++;
            Unit.NextActionTime = DigimonVenomNXTTimelineCore::InitialTime(Unit.Stats.Speed);
            Unit.bGuarding = false;
        }
        for (FDigimonBattleUnit& Unit : Team->Bench)
        {
            Unit.TimelineOrder = Identity++;
            Unit.NextActionTime = -1.0;
            Unit.bGuarding = false;
        }
    }
    PendingA.Reset(); PendingB.Reset();
    SelectNextActor();
}

bool ADigimonVenomNXTBattleActor::SelectNextActor()
{
    const uint32 Seed = DigimonVenomNXTCombatCore::BattleSeed(State.BattleId.A, State.BattleId.B, State.BattleId.C, State.BattleId.D);
    std::vector<DigimonVenomNXTTimelineCore::Entry> Queue;
    TArray<TPair<int32, int32>> Slots;
    for (int32 TeamIndex = 0; TeamIndex < 2; ++TeamIndex)
    {
        FDigimonBattleTeam& Team = TeamIndex == 0 ? State.TeamA : State.TeamB;
        for (int32 Slot = 0; Slot < Team.Active.Num(); ++Slot)
        {
            FDigimonBattleUnit& Unit = Team.Active[Slot];
            if (Unit.HP <= 0 || Unit.bDefeated) continue;
            if (Unit.NextActionTime < 0.0)
                Unit.NextActionTime = DigimonVenomNXTTimelineCore::NextTime(State.BattleClock, Unit.Stats.Speed);
            Queue.push_back(DigimonVenomNXTTimelineCore::MakeEntry(Seed, TeamIndex, Unit.TimelineOrder, Unit.Stats.Speed, Unit.NextActionTime));
            Slots.Emplace(TeamIndex, Slot);
        }
    }
    const int32 Next = DigimonVenomNXTTimelineCore::SelectNext(Queue);
    if (!Slots.IsValidIndex(Next)) return false;
    State.ActingTeam = Slots[Next].Key;
    State.ActingSlot = Slots[Next].Value;
    State.BattleClock = FMath::Max(State.BattleClock, Queue[Next].NextAt);
    FDigimonBattleUnit& Acting = (State.ActingTeam == 0 ? State.TeamA : State.TeamB).Active[State.ActingSlot];
    DigimonVenomNXTTimelineCore::BeginOpportunity(Acting.bGuarding);
    ResetUnrankedDeadline();
    return true;
}

void ADigimonVenomNXTBattleActor::AdvanceOpeningAI()
{
    const bool bQueuedDecision = (State.ActingTeam == 0 ? PendingA : PendingB).Contains(State.ActingSlot);
    if (!HasAuthority() || State.bFinished || State.bAutomatic || !PlayerA ||
        (!bQueuedDecision && (PlayerB || State.ActingTeam != 1))) return;
    // Initial enemy turns can occur before the first human input. The timer runs
    // after the controller owns this battle, preserving private settlement checks.
    const bool bDurable = State.Kind == EDigimonBattleKind::Season || State.Kind == EDigimonBattleKind::Wild || IsRelayBattle();
    const FDigimonPlayerProfile BeforeProfile = PlayerA->Profile;
    const FDigimonBattleState BeforeState = State;
    const TMap<int32, FDigimonBattleCommand> BeforeA = PendingA, BeforeB = PendingB;
    bSeasonCommandTransaction = bDurable;
    bSeasonSettlementFailed = false;
    AutoFillAICommands();
    ResolveRound();
    const bool bSaved = !bDurable || (!bSeasonSettlementFailed && SaveSeasonCheckpoint());
    bSeasonCommandTransaction = false;
    if (!bSaved)
    {
        PlayerA->Profile = BeforeProfile;
        State = BeforeState;
        PendingA = BeforeA; PendingB = BeforeB;
        State.PresentationEvents.Reset();
        State.LastEvent = TEXT("The next battle action could not be saved. Your last saved decision is unchanged; retrying safely.");
        ++State.PresentationSerial;
        StartBattleSafetyChecks();
    }
    if (bDurable) PlayerA->MarkProfileChanged();
    if (bDurable || !bSaved) PublishState();
}

void ADigimonVenomNXTBattleActor::ResolveRound()
{
    if (!EnsureBattleCanContinue()) return;
    State.PresentationEvents.Reset();
    // Bounded batches keep pathological speed gaps responsive. The safety timer
    // continues a remaining AI streak; no extra player command is required.
    for (int32 ActionCount = 0; ActionCount < 64 && !State.bFinished; ++ActionCount)
    {
        if (State.ActingTeam == 1 && !PlayerB) AutoFillAICommands();
        TMap<int32, FDigimonBattleCommand>& Pending = State.ActingTeam == 0 ? PendingA : PendingB;
        const FDigimonBattleCommand* Found = Pending.Find(State.ActingSlot);
        if (!Found) break;
        const FDigimonBattleCommand Command = *Found;
        const int32 TeamIndex = State.ActingTeam;
        FDigimonBattleTeam& Team = TeamIndex == 0 ? State.TeamA : State.TeamB;
        if (!Team.Active.IsValidIndex(Command.ActingSlot)) break;
        const FGuid ActingId = Team.Active[Command.ActingSlot].InstanceId;
        Pending.Remove(Command.ActingSlot);
        const int32 FirstEvent = State.PresentationEvents.Num();
        ResolveOne(TeamIndex, Command);
        // A switched or promoted identity never inherits the former unit's clock.
        if (Team.Active.IsValidIndex(Command.ActingSlot) && Team.Active[Command.ActingSlot].InstanceId == ActingId)
            Team.Active[Command.ActingSlot].NextActionTime = DigimonVenomNXTTimelineCore::NextTime(State.BattleClock, Team.Active[Command.ActingSlot].Stats.Speed);
        if (State.bFinished) { CapturePostState(FirstEvent); break; }
        if (IsTeamDefeated(State.TeamA)) { CapturePostState(FirstEvent); FinishBattle(1, TEXT("Team B won the battle.")); break; }
        if (IsTeamDefeated(State.TeamB)) { CapturePostState(FirstEvent); FinishBattle(0, TEXT("Team A won the battle.")); break; }
        const bool bSelected = SelectNextActor();
        // Include the next opportunity's Guard expiry in the final visible snapshot.
        CapturePostState(FirstEvent);
        ++State.TurnNumber;
        if (!bSelected || State.ActingTeam == 0 || PlayerB) break;
    }
    PendingA.Reset(); PendingB.Reset();
    if (State.PresentationEvents.Num() > 0) ++State.PresentationSerial;
    PublishState();
}

void ADigimonVenomNXTBattleActor::RecordWildDefeat(const FDigimonBattleUnit& Unit)
{
    if (!PlayerA || State.Kind != EDigimonBattleKind::Wild || State.ScannedWildInstances.Contains(Unit.InstanceId)) return;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    State.ScannedWildInstances.Add(Unit.InstanceId);
    const int32 Gain = Unit.Variant == EDigimonVariant::Normal ? S->BaseScanGain : S->RareScanGain;
    const bool bMastery = (Unit.Variant == EDigimonVariant::Paradox && PlayerA->Profile.Chronicles.bParadoxScanMastery) ||
        (Unit.Variant == EDigimonVariant::Shiny && PlayerA->Profile.GhostLine.bShinyScanMastery) ||
        (Unit.Variant == EDigimonVariant::Firewall && PlayerA->Profile.Relay.bFirewallScanMastery);
    if (bMastery)
    {
        FDigimonWildScanMasteryPending Pending; Pending.InstanceId = Unit.InstanceId;
        Pending.Hundredths = DigimonVenomNXTRewardCore::MasteryHundredths(Gain);
        State.WildMasteryHundredths.Add(Pending);
    }
    const int32 Granted = AddBattleScan(PlayerA->Profile, Unit, Gain, S->ScanCapPercent);
    State.LastEvent += FString::Printf(TEXT(" +%d%% scan data secured."), Granted);
}

FString ADigimonVenomNXTBattleActor::AwardWildMastery(FDigimonPlayerProfile& Profile)
{
    if (State.bWildMasteryPaid || State.Kind != EDigimonBattleKind::Wild) return FString();
    State.bWildMasteryPaid = true;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    FString Summary;
    for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamB.Active, &State.TeamB.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            if (!State.ScannedWildInstances.Contains(Unit.InstanceId)) continue;
            const FDigimonWildScanMasteryPending* Pending = State.WildMasteryHundredths.FindByPredicate([&Unit](const FDigimonWildScanMasteryPending& P) { return P.InstanceId == Unit.InstanceId; });
            const int32 Bonus = Pending ? Pending->Hundredths : 0;
            if (Bonus <= 0) continue;
            FDigimonScanRecord* Scan = Profile.Scans.FindByPredicate([&Unit](const FDigimonScanRecord& E) { return E.SpeciesId == Unit.SpeciesId && E.Variant == Unit.Variant; });
            if (!Scan) continue;
            const int32 CapHundredths = DigimonVenomNXTScanCore::Cap(S->ScanCapPercent) * 100;
            const int32 Before = FMath::Clamp(Scan->Percent, 0, CapHundredths / 100) * 100 + FMath::Clamp(Scan->FractionalHundredths, 0, 99);
            const int32 After = DigimonVenomNXTRewardCore::ScanHundredthsAfter(Scan->Percent, Scan->FractionalHundredths, Bonus, S->ScanCapPercent);
            Scan->Percent = After / 100; Scan->FractionalHundredths = After % 100;
            DigimonVenomNXTScanCore::Observe(*Scan, S->ScanCapPercent);
            if (After > Before) Summary += FString::Printf(TEXT("\n%s: +%.2f%% permanent scan mastery bonus."), *Unit.DisplayName, (After - Before) / 100.0);
        }
    State.WildMasteryHundredths.Reset();
    return Summary;
}

void ADigimonVenomNXTBattleActor::RewardWildVictory()
{
    if (!PlayerA) return;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    State.LastEvent += AwardWildMastery(PlayerA->Profile);
    int64 Credits = 0;
    for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamB.Active, &State.TeamB.Bench})
        for (const FDigimonBattleUnit& Unit : *Units) Credits += DigimonVenomNXTRewardCore::WildCredits(Unit.Level);
    Credits = DigimonVenomNXTRewardCore::Scale(Credits, S->MoneyRewardRate);
    PlayerA->Profile.Credits = DigimonVenomNXTRewardCore::CreditTotal(PlayerA->Profile.Credits, Credits);
    State.LastEvent += FString::Printf(TEXT(" +%lld credits."), Credits);
    const FDigimonInventoryEntry* Meat = PlayerA->Profile.Inventory.FindByPredicate([](const FDigimonInventoryEntry& E) { return E.ItemId == TEXT("digimeat_cam"); });
    if (DigimonVenomNXTRewardCore::FriendshipMeatDrop(FMath::FRand(), Meat ? Meat->Quantity : 0))
    {
        AddBattleSupply(PlayerA->Profile, TEXT("digimeat_cam"), 1);
        State.LastEvent += TEXT(" Friendship DigiMeat ×1 found!");
    }
}

void ADigimonVenomNXTBattleActor::SaveParticipantProfiles()
{
    if (bSeasonCommandTransaction) return; // The complete decision is saved atomically by SubmitCommand.
    UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
    if (!Profiles)
    {
        DigimonVenomNXTServerActivity::RecordFor(this, State.TeamA.TrainerName, TEXT("Persistence"), TEXT("Battle result save failed"), TEXT("Profile storage subsystem is unavailable."), TEXT("Error"));
        return;
    }
    for (ADigimonVenomNXTPlayerState* Player : {PlayerA.Get(), PlayerB.Get()})
    {
        if (!Player || Player->Profile.AccountId.IsEmpty()) continue;
        const bool bSaved = Profiles->SaveProfile(Player->Profile);
        DigimonVenomNXTServerActivity::Record(Player, TEXT("Persistence"), bSaved ? TEXT("Battle result saved") : TEXT("Battle result save failed"),
            FString::Printf(TEXT("Battle %s%s"), *State.BattleId.ToString(EGuidFormats::Digits), bSaved ? TEXT("") : TEXT(" | applied in memory; autosave will retry")), bSaved ? TEXT("Info") : TEXT("Error"));
        if (!bSaved) UE_LOG(LogTemp, Warning, TEXT("Digimon Venom NXT could not persist battle result for %s; autosave will retry."), *Player->GetPlayerName());
    }
}





bool ADigimonVenomNXTBattleActor::FinishUnrankedMatch(int32 WinningTeam, const FString& Reason, bool bRecordResult)
{
    if (!HasAuthority() || State.Kind != EDigimonBattleKind::Friendly || State.bFinished) return false;
    const bool bNewOutcome = !bUnrankedSettlementPending;
    // Freeze the outcome once. A later timeout/disconnect cannot change a won match
    // while its paired profile transaction waits for storage recovery.
    if (!bUnrankedSettlementPending && bRecordResult)
    {
        PendingUnrankedWinner = WinningTeam;
        PendingUnrankedReason = Reason;
        PendingUnrankedProfiles.Reset();
        if (PlayerA) PendingUnrankedProfiles.Add(PlayerA->Profile);
        if (PlayerB) PendingUnrankedProfiles.Add(PlayerB->Profile);
        bUnrankedSettlementPending = true;
        bUnrankedResultSaving = true;
    }
    if (bUnrankedSettlementPending)
    {
        WinningTeam = PendingUnrankedWinner;
        UDigimonVenomNXTProfileSubsystem* Profiles = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>() : nullptr;
        TArray<FDigimonPlayerProfile> Candidates;
        TArray<ADigimonVenomNXTPlayerState*> Connected;
        bool bReady = Profiles && !PendingUnrankedProfiles.IsEmpty();
        for (int32 Team = 0; bReady && Team < PendingUnrankedProfiles.Num(); ++Team)
        {
            const FString& AccountId = PendingUnrankedProfiles[Team].AccountId;
            ADigimonVenomNXTPlayerState* LivePlayer = nullptr;
            for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
            {
                auto* PC = Cast<ADigimonVenomNXTPlayerController>(It->Get());
                auto* PS = PC ? PC->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
                if (PC && PC->IsAccountAuthenticated() && PS && PS->Profile.AccountId == AccountId) { LivePlayer = PS; break; }
            }
            FDigimonPlayerProfile Candidate;
            if (AccountId.IsEmpty()) { bReady = false; break; }
            if (LivePlayer) Candidate = LivePlayer->Profile;
            else if (bNewOutcome && IsValid(Team == 0 ? PlayerA.Get() : PlayerB.Get())) Candidate = PendingUnrankedProfiles[Team];
            else if (!Profiles->LoadExistingCommerceProfile(AccountId, Candidate)) { bReady = false; break; }
            int32& Counter = WinningTeam == INDEX_NONE ? Candidate.UnrankedDraws : WinningTeam == Team ? Candidate.UnrankedWins : Candidate.UnrankedLosses;
            Counter = Counter < MAX_int32 ? FMath::Max(0, Counter) + 1 : MAX_int32;
            Candidates.Add(MoveTemp(Candidate)); Connected.Add(LivePlayer);
        }
        FString SaveError;
        if (!bReady || !Profiles->CommitProfileGroup(Candidates, SaveError))
        {
            State.LastEvent = TEXT("Match complete — saving both tamers' results. Storage is temporarily unavailable; retrying automatically. Your party and currencies are unchanged.");
            UnrankedDecisionDeadlineServerTime = 0;
            NextUnrankedSettlementAttempt = FPlatformTime::Seconds() + 3.0;
            StartBattleSafetyChecks();
            return false;
        }
        for (int32 Index = 0; Index < Candidates.Num(); ++Index)
        {
            PendingUnrankedProfiles[Index] = Candidates[Index];
            // The server game thread serializes the journal and this publication.
            // Connected recipients adopt exactly the committed revision; reconnects
            // load the same result through normal journal recovery.
            if (Connected[Index]) { Connected[Index]->Profile = Candidates[Index]; Connected[Index]->MarkProfileChanged(); }
            // During Logout the controller may already have left the iterator but
            // GameMode still saves its PlayerState immediately after this function.
            ADigimonVenomNXTPlayerState* Original = Index == 0 ? PlayerA.Get() : PlayerB.Get();
            if (IsValid(Original) && Original != Connected[Index] && Original->Profile.AccountId == Candidates[Index].AccountId &&
                Original->Profile.CommerceRevision <= Candidates[Index].CommerceRevision)
            { Original->Profile = Candidates[Index]; Original->MarkProfileChanged(); }
        }
        bUnrankedSettlementPending = false;
        bUnrankedResultSaving = false;
        if (PendingUnrankedProfiles.Num() == 1 && !BattleContextId.IsEmpty())
            if (auto* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>())
                Rivals->RecordUnrankedResult(BattleContextId, WinningTeam == 1, WinningTeam == INDEX_NONE);
    }
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    State.bFinished = true;
    State.WinningTeam = WinningTeam;
    State.LastEvent = bRecordResult ? PendingUnrankedReason : Reason;
    State.LastEvent += TEXT(" Your expedition party is unchanged. No XP, money or ranked points were awarded.");
    UnrankedDecisionDeadlineServerTime = 0;
    PendingUnrankedProfiles.Reset();
    return true;
}

bool ADigimonVenomNXTBattleActor::FinishWorldWildMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards)
{
    if (!PlayerA || State.Kind != EDigimonBattleKind::Wild || IsRelayBattle()) return false;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data) return false;
    const FDigimonPlayerProfile Before = PlayerA->Profile;
    const FDigimonBattleState BeforeState = State;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    const bool bVictory = bGrantRewards && WinningTeam == 0 && !State.bFled;
    if (bVictory && !IsTeamDefeated(State.TeamB)) return false;
    int64 XP = 0;
    if (bVictory)
        for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamB.Active, &State.TeamB.Bench})
            for (const FDigimonBattleUnit& Unit : *Units)
            {
                FDigimonSpeciesDefinition Species;
                const int32 Rank = Data->GetSpecies(Unit.SpeciesId, Species) ? DigimonVenomNXTCombatCore::StageRank(static_cast<int32>(Species.Stage)) : 2;
                XP += DigimonVenomNXTRewardCore::WildXP(Unit.Level, Rank);
            }
    XP = DigimonVenomNXTRewardCore::Scale(XP, S->ExperienceRate);
    const bool bRecovery = IsTeamDefeated(State.TeamA);
    FString Summary = Reason;
    for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamA.Active, &State.TeamA.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            FDigimonOwnedPartner* Partner = PlayerA->Profile.Collection.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
            if (!Partner) { PlayerA->Profile = Before; return false; }
            const auto Vitals = DigimonVenomNXTRecoveryCore::ResultVitals(Unit, bRecovery);
            Partner->CurrentHP = Vitals.HP; Partner->CurrentSP = Vitals.SP;
            const bool bActive = Units == &State.TeamA.Active;
            if (bVictory) Partner->CAM = FMath::Clamp(Partner->CAM + (bActive ? 2 : 1), 0, 100);
            const int64 AwardXP = !bVictory ? 0 : bActive ? XP : FMath::Max<int64>(XP > 0 ? 1 : 0, XP / 2);
            const auto Award = DigimonVenomNXTProgressionCore::Apply(*Partner, AwardXP, S->MaxPartnerLevel,
                [Data](const FDigimonOwnedPartner& P) { return DigimonVenomNXTAutoBattle::BuildUnit(P, Data).Stats; });
            Partner->CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
            if (Award.LevelsGained > 0) Summary += FString::Printf(TEXT(" %s: Lv. %d → %d."), *Unit.DisplayName, Award.PreviousLevel, Award.Level);
        }
    State.LastEvent = Summary;
    if (bVictory)
    {
        RewardWildVictory();
        State.LastEvent += FString::Printf(TEXT(" +%lld XP per uncapped active partner; reserves receive half."), XP);
    }
    if (bRecovery) State.LastEvent += TEXT(" Your party has been fully restored. All earned scan data is safe.");
    State.bFinished = true; State.WinningTeam = WinningTeam;
    PlayerA->Profile.WorldBattleCheckpointJson.Reset();
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    if (!bSeasonCommandTransaction)
    {
        if (!SaveSeasonCheckpoint())
        { PlayerA->Profile = Before; State = BeforeState; StartBattleSafetyChecks(); return false; }
        PlayerA->MarkProfileChanged();
    }
    return true;
}

void ADigimonVenomNXTBattleActor::FinishBattle(int32 WinningTeam, const FString& Reason, bool bGrantRewards)
{
    if (!HasAuthority() || State.bFinished) return;

    if (IsRelayBattle())
    {
        bSeasonSettlementFailed = !(State.Kind == EDigimonBattleKind::Wild ? FinishPrivateWildMatch(WinningTeam, Reason, bGrantRewards) : FinishRelayMatch(WinningTeam, Reason, bGrantRewards));
        return;
    }
    if (State.Kind == EDigimonBattleKind::Season)
    {
        bSeasonSettlementFailed = !FinishSeasonMatch(WinningTeam, Reason, bGrantRewards);
        return;
    }
    if (State.Kind == EDigimonBattleKind::Friendly)
    {
        FinishUnrankedMatch(WinningTeam, Reason, bGrantRewards);
        return;
    }
    if (State.Kind == EDigimonBattleKind::Wild)
    {
        bSeasonSettlementFailed = !FinishWorldWildMatch(WinningTeam, Reason, bGrantRewards);
        return;
    }
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    State.bFinished = true;
    State.WinningTeam = WinningTeam;
    State.LastEvent = Reason;
    if (PlayerA) PlayerA->ApplyBattleTeamResult(State.TeamA, true);
    if (PlayerB) PlayerB->ApplyBattleTeamResult(State.TeamB, true);
    if ((PlayerA && !State.TeamA.Active.IsEmpty() && IsTeamDefeated(State.TeamA)) ||
        (PlayerB && !State.TeamB.Active.IsEmpty() && IsTeamDefeated(State.TeamB)))
        State.LastEvent += TEXT(" Defeated parties have been fully restored to full HP and SP.");
    if (State.bFled || !bGrantRewards) { SaveParticipantProfiles(); return; }

    // Progression is server-authored. Friendly sparring does not award XP to prevent trivial farming.
    auto CalculateVictoryXP = [](const FDigimonBattleTeam& DefeatedTeam) -> int64
    {
        int64 Total = 0;
        int32 Count = 0;
        for (const FDigimonBattleUnit& Unit : DefeatedTeam.Active)
        {
            Total += FMath::Max(1, Unit.Level) * 28LL;
            ++Count;
        }
        for (const FDigimonBattleUnit& Unit : DefeatedTeam.Bench)
        {
            Total += FMath::Max(1, Unit.Level) * 14LL;
            ++Count;
        }
        return FMath::Max<int64>(50LL, Count > 0 ? Total : 50LL);
    };
    if (State.Kind != EDigimonBattleKind::Friendly)
    {
        if (WinningTeam == 0 && PlayerA) State.LastEvent += PlayerA->AwardExperienceToParty(CalculateVictoryXP(State.TeamB));
        if (WinningTeam == 1 && PlayerB) State.LastEvent += PlayerB->AwardExperienceToParty(CalculateVictoryXP(State.TeamA));
    }
    if (State.Kind == EDigimonBattleKind::Wild && WinningTeam == 0) RewardWildVictory();
    if (PlayerA && State.Kind == EDigimonBattleKind::AITamer)
    {
        // CTB counts individual opportunities; normalize to formation rounds and
        // cap the duration bonus so Guard stalling cannot grow money indefinitely.
        const int32 VictoryCredits = DigimonVenomNXTBattlePolicyCore::TrainerVictoryCredits(State.TurnNumber, State.InitialActiveCount);
        if (UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld() ? GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>() : nullptr)
        {
            Rivals->RecordBattleResult(BattleContextId, WinningTeam == 1, CalculateVictoryXP(State.TeamA), VictoryCredits);
        }
        if (WinningTeam == 0) PlayerA->AwardCredits(VictoryCredits);
    }
    // Private story rewards are handled only by FinishRelayMatch's atomic,
    // NPC-bound receipt settlement. Retired "story:" contexts grant no campaign rewards.
    SaveParticipantProfiles();
}

bool ADigimonVenomNXTBattleActor::InitializeRankedPlayback(ADigimonVenomNXTPlayerState* Player,
    const FDigimonAutoBattleResult& Result, const FString& TrainerName, const FString& OpponentName, const FString& ContextId)
{

    if (!HasAuthority() || !Player || Player->HasActiveBattle() || Result.InitialTeamA.IsEmpty() || Result.InitialTeamB.IsEmpty()) return false;
    PlayerA=Player;
    PlayerB=nullptr; // Ranked defense is a snapshot, never a live second controller.
    SetOwner(Player->GetOwner());
    BattleContextId=ContextId;
    State=FDigimonBattleState();
    State.BattleId=FGuid::NewGuid();
    State.Kind=EDigimonBattleKind::Ranked;
    State.bAutomatic=true;
    State.TeamA.TrainerName=TrainerName;
    State.TeamB.TrainerName=OpponentName;
    RankedRosterA=Result.InitialTeamA;
    RankedRosterB=Result.InitialTeamB;
    RankedActions=Result.Actions;
    RankedWinningTeam=Result.bDraw ? INDEX_NONE : Result.bTeamAWon ? 0 : 1;
    RankedFinalTurns=Result.Turns;
    NextRankedAction=0;
    const int32 ActiveLimit=FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->ActiveBattleSize,1,6);
    auto Fill=[ActiveLimit](FDigimonBattleTeam& Team,const TArray<FDigimonBattleUnit>& Roster)
    {
        for (const FDigimonBattleUnit& Unit : Roster)
        {
            if (Team.Active.Num()<ActiveLimit) Team.Active.Add(Unit);
            else Team.Bench.Add(Unit);
        }
    };
    Fill(State.TeamA,RankedRosterA);
    Fill(State.TeamB,RankedRosterB);
    InitializeTimeline();
    State.LastEvent=FString::Printf(TEXT("Ranked arena: %s vs %s. Automatic battle starting..."),*TrainerName,*OpponentName);
    // Do not expose or advance a prepared match until its energy/result commit succeeds.
    return true;
}

void ADigimonVenomNXTBattleActor::StartRankedPlayback(const FString& ResultSummary)
{
    if (!HasAuthority() || !GetWorld() || !State.bAutomatic || State.bFinished || GetWorld()->GetTimerManager().IsTimerActive(RankedPlaybackTimer)) return;
    RankedResultSummary=ResultSummary;
    bAwaitingRankedPresentationReady=true;
    PublishState();
    // Wait for the owning widget's READY acknowledgement before the first action;
    // asset loads and opening the actor channel need not finish in a fixed timeout.
    // Subsequent packets allow the full 0.82-second movement/impact animation.
    GetWorld()->GetTimerManager().SetTimer(RankedPlaybackTimer,this,&ADigimonVenomNXTBattleActor::AdvanceRankedPlayback,0.95f,true,1.30f);
}

void ADigimonVenomNXTBattleActor::RebindRankedPlayer(ADigimonVenomNXTPlayerState* Player)
{
    if (!HasAuthority() || !Player || !State.bAutomatic || State.bFinished) return;
    PlayerA=Player;
    SetOwner(Player->GetOwner());
    ForceNetUpdate();
}

void ADigimonVenomNXTBattleActor::AcknowledgePresentationReady(AController* Controller)
{
    if (!HasAuthority() || !IsParticipant(Controller) || !State.bAutomatic || State.bFinished) return;
    bAwaitingRankedPresentationReady=false;
}

void ADigimonVenomNXTBattleActor::AdvanceRankedPlayback()
{
    if (!HasAuthority() || State.bFinished || !State.bAutomatic) return;
    if (bAwaitingRankedPresentationReady)
    {
        AActor* Controller=IsValid(PlayerA.Get()) ? PlayerA->GetOwner() : nullptr;
        if (IsValid(Controller) && !Controller->IsActorBeingDestroyed()) return;
        // A disconnect before READY does not strand the actor or undo its committed loss.
        bAwaitingRankedPresentationReady=false;
    }
    State.PresentationEvents.Reset();
    if (NextRankedAction>=RankedActions.Num())
    {
        GetWorld()->GetTimerManager().ClearTimer(RankedPlaybackTimer);
        State.bFinished=true;
        State.WinningTeam=RankedWinningTeam;
        State.TurnNumber=FMath::Max(1,RankedFinalTurns);
        State.LastEvent=RankedResultSummary;
        ++State.PresentationSerial;
        // Never call FinishBattle here: rating/energy already have one atomic receipt;
        // ranked snapshots do not injure the overworld party or award farmable wild XP.
        PublishState();
        if (UDigimonVenomNXTRankedSubsystem* Ranked=GetGameInstance()->GetSubsystem<UDigimonVenomNXTRankedSubsystem>())
            if (PlayerA) Ranked->RefreshPlayerState(PlayerA);
        RankedActions.Reset();
        RankedRosterA.Reset();
        RankedRosterB.Reset();
        TryDestroyWhenUnused();
        return;
    }

    const auto& Action=RankedActions[NextRankedAction++];
    FDigimonBattleTeam& Allies=Action.Team==0 ? State.TeamA : State.TeamB;
    FDigimonBattleTeam& Enemies=Action.Team==0 ? State.TeamB : State.TeamA;
    const auto& SourceAllies=Action.Team==0 ? RankedRosterA : RankedRosterB;
    const auto& SourceEnemies=Action.Team==0 ? RankedRosterB : RankedRosterA;
    if (!SourceAllies.IsValidIndex(Action.Actor) || !SourceEnemies.IsValidIndex(Action.Target)) return;
    const FGuid ActorId=SourceAllies[Action.Actor].InstanceId;
    const FGuid TargetId=SourceEnemies[Action.Target].InstanceId;
    const int32 ActingSlot=Allies.Active.IndexOfByPredicate([&](const FDigimonBattleUnit& Unit){return Unit.InstanceId==ActorId;});
    const int32 TargetSlot=Enemies.Active.IndexOfByPredicate([&](const FDigimonBattleUnit& Unit){return Unit.InstanceId==TargetId;});
    if (!Allies.Active.IsValidIndex(ActingSlot) || !Enemies.Active.IsValidIndex(TargetSlot)) return;
    FDigimonBattleUnit& Attacker=Allies.Active[ActingSlot];
    FDigimonBattleUnit& Defender=Enemies.Active[TargetSlot];
    FDigimonBattlePresentationEvent Event;
    Event.ActingTeam=Action.Team;
    Event.ActingSlot=ActingSlot;
    Event.ActingInstanceId=ActorId;
    Event.TargetTeam=1-Action.Team;
    Event.TargetSlot=TargetSlot;
    Event.TargetInstanceId=TargetId;
    Event.Action=Action.MoveIndex<0 ? EDigimonBattleAction::Attack : static_cast<EDigimonBattleAction>(static_cast<int32>(EDigimonBattleAction::Move1)+Action.MoveIndex);
    Event.Damage=Action.Damage;
    Event.Effectiveness=Action.Effectiveness;
    Event.TypeMultiplier=Action.TypeMultiplier;
    Event.ElementMultiplier=Action.ElementMultiplier;
    Event.DamageClass=static_cast<EDigimonDamageClass>(Action.DamageClass);
    Event.Element=static_cast<EDigimonElement>(Action.Element);
    Event.ComboMultiplier=Action.ComboMultiplier;
    Event.bGuarded=Action.Guarded;
    State.BattleClock=Action.Clock;
    Attacker.NextActionTime=DigimonVenomNXTTimelineCore::NextTime(Action.Clock,Attacker.Stats.Speed);
    Attacker.SP=Action.ActorSPAfter;
    Defender.HP=Action.TargetHPAfter;
    Defender.bDefeated=Defender.HP<=0;
    const FString MoveName=Attacker.Moves.IsValidIndex(Action.MoveIndex)
        ? (Attacker.Moves[Action.MoveIndex].DisplayName.IsEmpty() ? Attacker.Moves[Action.MoveIndex].MoveId.ToString() : Attacker.Moves[Action.MoveIndex].DisplayName.ToString())
        : TEXT("Attack");
    Event.Text=FString::Printf(TEXT("%s used %s on %s: %d damage%s"),*Attacker.DisplayName,*MoveName,*Defender.DisplayName,Action.Damage,Defender.bDefeated ? TEXT(" — defeated!") : TEXT("."));
    if (Event.Effectiveness > 1.001f) Event.Text += TEXT(" Super effective!");
    else if (Event.Effectiveness < 0.999f) Event.Text += TEXT(" Not very effective.");
    if (Event.ComboMultiplier > 1.0f) Event.Text += TEXT(" Team combo!");
    State.TurnNumber=Action.Round;
    State.ActingTeam=Action.Team;
    State.ActingSlot=ActingSlot;
    State.LastEvent=Event.Text;
    State.PresentationEvents.Add(Event);
    // Stable instance IDs make promoted partners occupy their real slot, without
    // inheriting the defeated original's queued turn or shifting the whole formation.
    PromoteBench(Enemies);
    CapturePostState(0);
    ++State.PresentationSerial;
    PublishState();
}

bool ADigimonVenomNXTBattleActor::RestoreWorldWildMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError)
{
    if (!HasAuthority() || !Player || Player->Profile.AccountId.IsEmpty()) return false;
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner());
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const FDigimonMapRow* Map = Data ? Data->FindMap(Player->Profile.CurrentMapId) : nullptr;
    const FString& Json = Player->Profile.WorldBattleCheckpointJson;
    FDigimonSeasonBattleCheckpoint Checkpoint;
    if (!Controller || !Controller->IsAccountAuthenticated() || Controller->IsInRelay() || !Map ||
        !Player->Profile.Season.BattleCheckpointJson.IsEmpty() || DigimonVenomNXTCampaign::HasPendingBattle(Player->Profile) ||
        Json.IsEmpty() || Json.Len() > 1024 * 1024 || !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Checkpoint, 0, 0) ||
        (Checkpoint.Version != 1 && Checkpoint.Version != 2) ||
        Checkpoint.ContextId != FString::Printf(TEXT("world:%d"), Player->Profile.CurrentMapId) ||
        !Checkpoint.State.BattleId.IsValid() || Checkpoint.State.Kind != EDigimonBattleKind::Wild ||
        Checkpoint.State.bFinished || Checkpoint.State.bAutomatic || Checkpoint.State.bWildMasteryPaid ||
        Checkpoint.State.TeamA.Active.IsEmpty() || Checkpoint.State.TeamA.Active.Num() + Checkpoint.State.TeamA.Bench.Num() > 12 ||
        Checkpoint.State.TeamB.Active.Num() < 1 || Checkpoint.State.TeamB.Active.Num() > 3 || !Checkpoint.State.TeamB.Bench.IsEmpty())
    { OutError = TEXT("Your saved wild encounter could not be validated. Your saved decision and scan data are preserved."); return false; }
    TSet<FGuid> Seen;
    for (const TArray<FDigimonBattleUnit>* Units : {&Checkpoint.State.TeamA.Active, &Checkpoint.State.TeamA.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            const FDigimonOwnedPartner* Partner = Player->Profile.Collection.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
            if (!Partner || !Player->Profile.Party.Contains(Unit.InstanceId) || Partner->SpeciesId != Unit.SpeciesId ||
                Partner->Level != Unit.Level || Partner->Variant != Unit.Variant || Seen.Contains(Unit.InstanceId))
            { OutError = TEXT("The saved wild party no longer matches your collection. Your saved decision is preserved."); return false; }
            Seen.Add(Unit.InstanceId);
        }
    Seen.Reset();
    for (const FDigimonBattleUnit& Unit : Checkpoint.State.TeamB.Active)
    {
        FDigimonSpeciesDefinition Species;
        if (Seen.Contains(Unit.InstanceId) || Unit.Level < 1 || Unit.Level > 99 ||
            !Data->GetSpecies(Unit.SpeciesId, Species) || Species.bPlaceholder ||
            !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Unit.Variant), Species.bHasNormalArtwork,
                Species.bHasParadoxArtwork, Species.bHasShinyArtwork, Species.bHasFirewallArtwork))
        { OutError = TEXT("A saved wild opponent is unavailable. Your saved decision is preserved."); return false; }
        Seen.Add(Unit.InstanceId);
    }
    TSet<FGuid> Scanned;
    for (const FGuid& Id : Checkpoint.State.ScannedWildInstances)
    {
        const FDigimonBattleUnit* Unit = Checkpoint.State.TeamB.Active.FindByPredicate([&Id](const FDigimonBattleUnit& U) { return U.InstanceId == Id; });
        if (!Unit || Unit->HP > 0 || Scanned.Contains(Id))
        { OutError = TEXT("The saved scan receipts are invalid. Your saved decision is preserved."); return false; }
        Scanned.Add(Id);
    }
    PlayerA = Player; PlayerB = nullptr; SetOwner(Player->GetOwner());
    BattleContextId = Checkpoint.ContextId; State = MoveTemp(Checkpoint.State);
    State.PresentationEvents.Reset(); PendingA.Reset(); PendingB.Reset();
    bool bUpgraded = false;
    if (!RebuildRestoredBattle(bUpgraded, OutError)) return false;
    if (bUpgraded) { Checkpoint.CommandsA.Reset(); Checkpoint.CommandsB.Reset(); }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsA)
    {
        FString Error;
        if (!ValidateCommand(0, Command, Error) || PendingA.Contains(Command.ActingSlot))
        { OutError = TEXT("A saved wild command is invalid. Your saved decision is preserved."); return false; }
        PendingA.Add(Command.ActingSlot, Command);
    }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsB)
    {
        FString Error;
        if (!ValidateCommand(1, Command, Error) || PendingB.Contains(Command.ActingSlot))
        { OutError = TEXT("A saved wild opponent command is invalid. Your saved decision is preserved."); return false; }
        PendingB.Add(Command.ActingSlot, Command);
    }
    State.LastEvent = FString::Printf(TEXT("Wild encounter resumed at action %d. Your HP, SP, scan receipts and action order are restored."), State.TurnNumber);
    if (!SaveSeasonCheckpoint()) { OutError = TEXT("The resumed wild decision could not be saved. Your previous checkpoint is preserved."); return false; }
    ++State.PresentationSerial; PublishState(); StartBattleSafetyChecks();
    return true;
}

void ADigimonVenomNXTBattleActor::SuspendWorldWildMatch()
{
    if (!HasAuthority() || State.Kind != EDigimonBattleKind::Wild || IsRelayBattle() || State.bFinished) return;
    // Accepted decisions and defeat scans are already durable; suspension is not a result.
    State.bFinished = true; State.WinningTeam = INDEX_NONE;
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
}

bool ADigimonVenomNXTBattleActor::RestoreRelayMatch(ADigimonVenomNXTPlayerState* Player, FString& OutError)
{

    if (!HasAuthority() || !Player || Player->Profile.AccountId.IsEmpty()) return false;
    const EDigimonPrivateCampaign Campaign = Player->Profile.ActiveStoryCampaign;
    if (!DigimonVenomNXTCampaign::IsValid(Campaign))
    { OutError = TEXT("The saved campaign identity is invalid. Your saved decision has been preserved."); return false; }
    const FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Player->Profile, Campaign);
    const ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(Player->GetOwner());
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(Campaign, Progress.MapId);
    const FString Prefix = DigimonVenomNXTCampaign::ContextPrefix(Campaign);
    FDigimonSeasonBattleCheckpoint Checkpoint;
    if (!Controller || !Controller->IsAccountAuthenticated() || !Controller->IsInRelay() || Controller->GetStoryCampaign() != Campaign ||
        !Map || !Progress.bInside || !DigimonVenomNXTCampaign::CanEnterMap(Campaign, Progress, Progress.MapId) ||
        !Player->Profile.Season.BattleCheckpointJson.IsEmpty() || DigimonVenomNXTCampaign::HasOtherPendingBattle(Player->Profile, Campaign) ||
        Progress.BattleCheckpointJson.IsEmpty() || Progress.BattleCheckpointJson.Len() > 1024 * 1024 ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Progress.BattleCheckpointJson, &Checkpoint, 0, 0) || (Checkpoint.Version != 1 && Checkpoint.Version != 2) ||
        Checkpoint.ContextId != Prefix + Progress.PendingNPCId.ToString() || !Checkpoint.State.BattleId.IsValid() ||
        Checkpoint.State.BattleId != Progress.PendingBattleId || Checkpoint.State.BattleId == Progress.LastSettledBattleId ||
        Checkpoint.State.bAutomatic || Checkpoint.State.bFinished || Checkpoint.State.TeamA.Active.IsEmpty() || Checkpoint.State.TeamB.Active.IsEmpty() ||
        Checkpoint.State.TeamA.Active.Num() + Checkpoint.State.TeamA.Bench.Num() > 12)
    { OutError = TEXT("Your saved campaign decision could not be validated. It has been preserved; restore a valid server backup rather than resetting your campaign."); return false; }
    if (Checkpoint.State.Kind == EDigimonBattleKind::Wild)
    {
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        if (((Campaign == EDigimonPrivateCampaign::ParadoxChronicles || Campaign == EDigimonPrivateCampaign::GhostLine) && Map->MapId == 1) ||
            Checkpoint.ContextId != Prefix + FString::Printf(TEXT("wild:%d"), Map->MapId) || !Data ||
            Checkpoint.State.TeamB.Active.Num() < 1 || Checkpoint.State.TeamB.Active.Num() > 3 || !Checkpoint.State.TeamB.Bench.IsEmpty())
        { OutError = TEXT("The saved field encounter does not belong to this campaign map. Your saved decision has been preserved."); return false; }
        for (const FDigimonBattleUnit& Wild : Checkpoint.State.TeamB.Active)
        {
            FDigimonSpeciesDefinition Species;
            if (Wild.Level < 1 || Wild.Level > FMath::Min(99, Map->MinLevel) ||
                !Data->GetSpecies(Wild.SpeciesId, Species) || Species.bPlaceholder ||
                !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Wild.Variant), Species.bHasNormalArtwork,
                    Species.bHasParadoxArtwork, Species.bHasShinyArtwork, Species.bHasFirewallArtwork))
            { OutError = TEXT("A saved wild Digimon does not match this campaign map's encounter data. Your saved decision has been preserved."); return false; }
        }
    }
    else
    {
        const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(Campaign, Progress.PendingNPCId);
        FString GateError;
        if (Checkpoint.State.Kind != EDigimonBattleKind::Story || !NPC || NPC->MapId != Progress.MapId ||
            !DigimonVenomNXTCampaign::CanChallenge(Campaign, Progress, *NPC, GateError) ||
            Checkpoint.State.TeamB.Active.Num() + Checkpoint.State.TeamB.Bench.Num() != NPC->TeamSpecies.Num())
        { OutError = TEXT("The saved story encounter does not match your current quest. Your saved decision has been preserved."); return false; }
        const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        if (!DigimonVenomNXTCampaign::IsNPCVisible(Campaign, Progress, *NPC) ||
            !MatchesAuthoredCampaignTeam(Campaign, *NPC, Checkpoint.State.TeamB, Data))
        { OutError = TEXT("The saved opponent or party does not match this campaign encounter. Your saved decision has been preserved."); return false; }

    }
    TSet<FGuid> Seen;
    for (const TArray<FDigimonBattleUnit>* Units : {&Checkpoint.State.TeamA.Active, &Checkpoint.State.TeamA.Bench})
        for (const FDigimonBattleUnit& Unit : *Units)
        {
            const FDigimonOwnedPartner* Partner = Player->Profile.Collection.FindByPredicate([&Unit](const FDigimonOwnedPartner& P) { return P.InstanceId == Unit.InstanceId; });
            if (!Partner || !Player->Profile.Party.Contains(Unit.InstanceId) || Partner->SpeciesId != Unit.SpeciesId ||
                Partner->Level != Unit.Level || Partner->Variant != Unit.Variant || Seen.Contains(Unit.InstanceId))
            { OutError = TEXT("The saved campaign party no longer matches your collection. Your saved decision has been preserved."); return false; }
            Seen.Add(Unit.InstanceId);
        }
    PlayerA = Player; PlayerB = nullptr;
    SetOwner(Player->GetOwner());
    BattleContextId = Checkpoint.ContextId;
    State = MoveTemp(Checkpoint.State);
    State.PresentationEvents.Reset();
    PendingA.Reset(); PendingB.Reset();
    bool bUpgraded = false;
    if (!RebuildRestoredBattle(bUpgraded, OutError)) return false;
    if (bUpgraded)
    {
        // Old whole-team rounds have no equivalent position in a continuous clock.
        // Keep the encounter, injuries and resources; ask for fresh unspent choices.
        Checkpoint.CommandsA.Reset(); Checkpoint.CommandsB.Reset();
    }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsA)
    {
        FString Error;
        if (!ValidateCommand(0, Command, Error) || PendingA.Contains(Command.ActingSlot))
        { OutError = TEXT("A saved campaign command is invalid. Your saved decision has been preserved."); return false; }
        PendingA.Add(Command.ActingSlot, Command);
    }
    for (const FDigimonBattleCommand& Command : Checkpoint.CommandsB)
    {
        FString Error;
        if (!ValidateCommand(1, Command, Error) || PendingB.Contains(Command.ActingSlot))
        { OutError = TEXT("A saved campaign opponent command is invalid. Your saved decision has been preserved."); return false; }
        PendingB.Add(Command.ActingSlot, Command);
    }
    State.LastEvent = bUpgraded
        ? TEXT("Campaign battle updated to the speed timeline. Your real party, saved HP/SP percentages, opponent and progress are preserved. Choose new commands for the new action order.")
        : FString::Printf(TEXT("Campaign resumed at action %d. Your real party, HP, SP and speed timeline are restored."), State.TurnNumber);
    if (!SaveSeasonCheckpoint()) { OutError = TEXT("The updated campaign decision could not be saved. Your previous saved battle remains intact."); return false; }
    ++State.PresentationSerial;
    PublishState();
    StartBattleSafetyChecks();
    return true;
}

void ADigimonVenomNXTBattleActor::SuspendRelayMatch()
{
    if (!HasAuthority() || !IsRelayBattle() || State.bFinished) return;
    // Every accepted command has a durable checkpoint. Disconnect does not
    // reroll this opponent, heal this team, award a badge, or evade a defense.
    State.bFinished = true;
    State.WinningTeam = INDEX_NONE;
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
}

bool ADigimonVenomNXTBattleActor::FinishRelayMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards)
{
    const ADigimonVenomNXTPlayerController* Controller = PlayerA ? Cast<ADigimonVenomNXTPlayerController>(PlayerA->GetOwner()) : nullptr;
    if (!HasAuthority() || !IsRelayBattle() || !PlayerA || !Controller || !Controller->IsAccountAuthenticated() ||
        Controller->CurrentBattle != this || !Controller->IsInRelay()) return false;
    const EDigimonPrivateCampaign Campaign = BattleCampaign();
    if (Controller->GetStoryCampaign() != Campaign || PlayerA->Profile.ActiveStoryCampaign != Campaign) return false;
    const FName NPCId = BattleNPCId();
    const FDigimonRelayNPC* NPC = DigimonVenomNXTCampaign::GetNPC(Campaign, NPCId);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    if (!NPC || !Data || NPC->MapId != DigimonVenomNXTCampaign::Progress(PlayerA->Profile, Campaign).MapId) return false;
    // Only a combat-resolved victory may settle an unbeaten tamer or championship.
    if (bGrantRewards && WinningTeam == 0 && !IsTeamDefeated(State.TeamB)) return false;
    const FDigimonPlayerProfile Before = PlayerA->Profile;
    const FDigimonBattleState BeforeState = State;
    FDigimonPlayerProfile Candidate = Before;
    FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Candidate, Campaign);
    bool bFirstClear = false;
    if (bGrantRewards)
    {
        if (!DigimonVenomNXTCampaign::Settle(Campaign, Progress, State.BattleId, NPCId, WinningTeam == 0, bFirstClear)) return false;
    }
    else
    {
        if (Progress.PendingBattleId != State.BattleId || Progress.PendingNPCId != NPCId) return false;
        Progress.LastSettledBattleId = State.BattleId;
        Progress.PendingBattleId.Invalidate(); Progress.PendingNPCId = NAME_None;
        Progress.BattleCheckpointJson.Reset();
    }
    const bool bVictory = bGrantRewards && WinningTeam == 0;
    const bool bPaidVictory = bVictory && !(NPC->Role == EDigimonRelayRole::FinalBoss && !bFirstClear);
    const bool bTitleBattle = Campaign == EDigimonPrivateCampaign::Relay &&
        (NPC->Role == EDigimonRelayRole::Champion || NPC->Role == EDigimonRelayRole::Challenger);
    const bool bFullReward = bPaidVictory && (bFirstClear || bTitleBattle);
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    int64 VictoryXP = 0;
    if (bPaidVictory)
        for (const TArray<FDigimonBattleUnit>* Units : {&State.TeamB.Active, &State.TeamB.Bench})
            for (const FDigimonBattleUnit& Unit : *Units) VictoryXP += DigimonVenomNXTRewardCore::StoryXP(Unit.Level);
    VictoryXP = DigimonVenomNXTRewardCore::Scale(VictoryXP, Settings->ExperienceRate);
    const int32 MaxLevel = FMath::Clamp(Settings->MaxPartnerLevel, 1, 200);
    FString LevelUps;
    // Every party member earns full story XP, including reserves. First-clear ABI
    // applies before recalculating stats; all campaign outcomes end fully rested.
    for (const FGuid& Id : Candidate.Party)
    {
        FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&Id](const FDigimonOwnedPartner& P){ return P.InstanceId == Id; });
        if (!Partner) return false;
        if (bPaidVictory)
        {
            Partner->CAM = FMath::Clamp(Partner->CAM + (bFirstClear ? 5 : 2), 0, 100);
            if (bFirstClear) Partner->ABI = FMath::Clamp(Partner->ABI + 3, 0, 200);
        }
        const int32 PreviousLevel = Partner->Level;
        DigimonVenomNXTProgressionCore::Apply(*Partner, VictoryXP, MaxLevel,
            [Data](const FDigimonOwnedPartner& Value){ return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        if (bFullReward && Campaign != EDigimonPrivateCampaign::GhostLine)
        {
            const int64 MilestoneXP = FMath::Max<int64>(0, DigimonVenomNXTProgressionCore::ExperienceFloor(FMath::Clamp(NPC->TrainingLevel, 1, MaxLevel)) - Partner->Experience);
            DigimonVenomNXTProgressionCore::Apply(*Partner, MilestoneXP, MaxLevel,
                [Data](const FDigimonOwnedPartner& Value){ return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        }
        const FDigimonBattleUnit Rested = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data);
        Partner->CurrentHP = Rested.Stats.MaxHP; Partner->CurrentSP = Rested.Stats.MaxSP;
        Partner->CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        if (Partner->Level > PreviousLevel) LevelUps += FString::Printf(TEXT(" %s: Lv. %d → %d."), *Rested.DisplayName, PreviousLevel, Partner->Level);
    }
    FString Summary = Reason;
    if (bGrantRewards)
    {
        const FString Dialogue = bVictory && Campaign == EDigimonPrivateCampaign::GhostLine && NPC->Role == EDigimonRelayRole::FinalBoss
            ? DigimonVenomNXTGhostLine::Epilogue(Progress) : bVictory ? NPC->AfterDialogue : NPC->LostDialogue;
        Summary += TEXT("\n\n") + Dialogue;
    }
    else Summary += TEXT(" No result or rewards were recorded. Your earlier campaign progress is unchanged.");
    if (bPaidVictory)
    {
        const int64 Credits = DigimonVenomNXTRewardCore::Scale(bFullReward ? NPC->Credits : DigimonVenomNXTRewardCore::RematchCredits(NPC->Credits), Settings->MoneyRewardRate);
        Candidate.Credits = DigimonVenomNXTRewardCore::CreditTotal(Candidate.Credits, Credits);
        Summary += FString::Printf(TEXT("\n+%lld credits; +%lld battle XP per uncapped party member."), Credits, VictoryXP);
        if (bFullReward)
        {
            for (const TPair<FName, int32>& Supply : NPC->RewardItems) AddBattleSupply(Candidate, Supply.Key, Supply.Value);
            if (!NPC->RewardPartner.IsNone())
            {
                FDigimonSpeciesDefinition Definition;
                if (!Data->GetSpecies(NPC->RewardPartner, Definition) || Definition.bPlaceholder) return false;
                FDigimonOwnedPartner Gift;
                Gift.InstanceId = FGuid::NewGuid(); Gift.SpeciesId = NPC->RewardPartner; Gift.Variant = NPC->RewardPartnerVariant;
                Gift.Level = FMath::Clamp(NPC->RewardPartnerLevel, 1, FMath::Min(99, MaxLevel));
                Gift.ABI = FMath::Min(60, Gift.Level / 2); Gift.CAM = 30;
                Gift.Experience = DigimonVenomNXTProgressionCore::ExperienceFloor(Gift.Level);
                Gift.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
                Gift.CurrentHP = MAX_int32; Gift.CurrentSP = MAX_int32;
                const FDigimonBattleUnit Unit = DigimonVenomNXTAutoBattle::BuildUnit(Gift, Data);
                Gift.CurrentHP = Unit.Stats.MaxHP; Gift.CurrentSP = Unit.Stats.MaxSP; Gift.Moves = Unit.Moves;
                const bool bPartySpace = Candidate.Party.Num() < FMath::Clamp(Settings->MaxPartySize, 1, 6);
                if (bPartySpace || Candidate.Collection.Num() - Candidate.Party.Num() < 100)
                {
                    Candidate.Collection.Add(Gift);
                    if (bPartySpace) Candidate.Party.Add(Gift.InstanceId);
                    Summary += FString::Printf(TEXT(" %s joined your %s."), *Definition.DisplayName.ToString(), bPartySpace ? TEXT("party") : TEXT("DigiFarm"));
                }
                else
                {
                    AddBattleScan(Candidate, Unit, 200, 200);
                    Summary += FString::Printf(TEXT(" Your roster is full: %s's 200%% scan data is saved for later."), *Definition.DisplayName.ToString());
                }
            }
        }
        if (bFirstClear && !NPC->BadgeId.IsNone()) Summary += TEXT("\n") + NPC->BadgeName + TEXT(" earned. Your campaign journal has been updated.");
        Summary += LevelUps;
    }
    else if (bVictory) Summary += TEXT("\nFinale replay complete. Completion rewards were already claimed; no XP, items or credits awarded.");
    Summary += TEXT("\nYour party has been fully restored to full HP and SP.");
    DigimonVenomNXTCampaign::Reconcile(Candidate);
    if (Candidate.Relay.bFirewallScanMastery && !Before.Relay.bFirewallScanMastery)
        Summary += TEXT("\nFIREWALL SCAN MASTERY unlocked permanently: +20% scan on FireWall wild victories (5% to 6%).");
    if (Candidate.Chronicles.bParadoxScanMastery && !Before.Chronicles.bParadoxScanMastery)
        Summary += TEXT("\nPARADOX SCAN MASTERY unlocked permanently: +20% scan on Paradox wild victories (5% to 6%).");
    if (Candidate.GhostLine.bShinyScanMastery && !Before.GhostLine.bShinyScanMastery)
        Summary += TEXT("\nSHINY SCAN MASTERY unlocked permanently: +20% scan on Shiny wild victories (5% to 6%).");
    PlayerA->Profile = MoveTemp(Candidate);
    State.bFinished = true; State.WinningTeam = WinningTeam; State.LastEvent = Summary;
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    if (!bSeasonCommandTransaction)
    {
        if (!SaveSeasonCheckpoint())
        {
            PlayerA->Profile = Before; State = BeforeState; StartBattleSafetyChecks();
            return false;
        }
        PlayerA->MarkProfileChanged();
    }
    return true;
}

bool ADigimonVenomNXTBattleActor::FinishPrivateWildMatch(int32 WinningTeam, const FString& Reason, bool bGrantRewards)
{
    const ADigimonVenomNXTPlayerController* Controller = PlayerA ? Cast<ADigimonVenomNXTPlayerController>(PlayerA->GetOwner()) : nullptr;
    if (!HasAuthority() || State.Kind != EDigimonBattleKind::Wild || !IsRelayBattle() || !PlayerA || !Controller ||
        !Controller->IsAccountAuthenticated() || Controller->CurrentBattle != this || !Controller->IsInRelay()) return false;
    const EDigimonPrivateCampaign Campaign = BattleCampaign();
    if (Controller->GetStoryCampaign() != Campaign || PlayerA->Profile.ActiveStoryCampaign != Campaign) return false;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    if (!Data || State.TeamB.Active.Num() < 1 || State.TeamB.Active.Num() > 3 || !State.TeamB.Bench.IsEmpty()) return false;
    const FDigimonPlayerProfile Before = PlayerA->Profile;
    const FDigimonBattleState BeforeState = State;
    FDigimonPlayerProfile Candidate = Before;
    FDigimonRelayProgress& Progress = DigimonVenomNXTCampaign::Progress(Candidate, Campaign);
    if (!Progress.bInside || BattleNPCId() != FName(*FString::Printf(TEXT("wild:%d"), Progress.MapId)) ||
        Progress.PendingBattleId != State.BattleId || Progress.PendingNPCId != BattleNPCId() ||
        Progress.LastSettledBattleId == State.BattleId) return false;
    const bool bVictory = bGrantRewards && WinningTeam == 0;
    if (bVictory && !IsTeamDefeated(State.TeamB)) return false;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const FDigimonRelayMap* Map = DigimonVenomNXTCampaign::GetMap(Campaign, Progress.MapId);
    if (!Map) return false;
    int64 VictoryXP = 0;
    if (bVictory)
        for (const FDigimonBattleUnit& Wild : State.TeamB.Active) VictoryXP += DigimonVenomNXTRewardCore::StoryXP(Wild.Level);
    VictoryXP = DigimonVenomNXTRewardCore::Scale(VictoryXP, Settings->ExperienceRate);
    FString Summary = Reason;
    int32 WeakestLevel = FMath::Clamp(Settings->MaxPartnerLevel, 1, 200);
    for (const FGuid& Id : Candidate.Party)
    {
        FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&Id](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; });
        if (!Partner) return false;
        if (bVictory) Partner->CAM = FMath::Clamp(Partner->CAM + 2, 0, 100);
        DigimonVenomNXTProgressionCore::Apply(*Partner, VictoryXP, Settings->MaxPartnerLevel,
            [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        WeakestLevel = FMath::Min(WeakestLevel, Partner->Level);
    }
    const int32 TrainingFloor = FMath::Min(FMath::Clamp(Map->MinLevel, 1, 99), WeakestLevel + 4);
    for (const FGuid& Id : Candidate.Party)
    {
        FDigimonOwnedPartner* Partner = Candidate.Collection.FindByPredicate([&Id](const FDigimonOwnedPartner& P) { return P.InstanceId == Id; });
        if (bVictory && Campaign != EDigimonPrivateCampaign::GhostLine)
        {
            const int64 FloorXP = FMath::Max<int64>(0, DigimonVenomNXTProgressionCore::ExperienceFloor(TrainingFloor) - Partner->Experience);
            DigimonVenomNXTProgressionCore::Apply(*Partner, FloorXP, Settings->MaxPartnerLevel,
                [Data](const FDigimonOwnedPartner& Value) { return DigimonVenomNXTAutoBattle::BuildUnit(Value, Data).Stats; });
        }
        const FDigimonBattleUnit Rested = DigimonVenomNXTAutoBattle::BuildUnit(*Partner, Data);
        if (State.bFled)
        {
            const FDigimonBattleUnit* Saved = State.TeamA.Active.FindByPredicate([&Id](const FDigimonBattleUnit& U) { return U.InstanceId == Id; });
            if (!Saved) Saved = State.TeamA.Bench.FindByPredicate([&Id](const FDigimonBattleUnit& U) { return U.InstanceId == Id; });
            if (!Saved) return false;
            Partner->CurrentHP = Saved->HP; Partner->CurrentSP = Saved->SP;
        }
        else { Partner->CurrentHP = Rested.Stats.MaxHP; Partner->CurrentSP = Rested.Stats.MaxSP; }
        Partner->CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    }
    if (bVictory)
    {
        Summary += AwardWildMastery(Candidate);
        const int64 Credits = DigimonVenomNXTRewardCore::Scale(DigimonVenomNXTRewardCore::FieldCredits(Map->RegionIndex), Settings->MoneyRewardRate);
        Candidate.Credits = DigimonVenomNXTRewardCore::CreditTotal(Candidate.Credits, Credits);
        AddBattleSupply(Candidate, TEXT("hp_s"), 1);
        Summary += FString::Printf(TEXT("\n+%lld credits; +%lld battle XP per uncapped party member. Small HP Capsule ×1."), Credits, VictoryXP);
    }
    Summary += State.bFled ? TEXT("\nYou withdrew safely. Defeated enemies’ scan data is retained.") : TEXT("\nYour party has been fully restored to full HP and SP. Earned scan data is safe.");
    if (!State.bFled) Progress.LastSettledBattleId = State.BattleId;
    Progress.PendingBattleId.Invalidate(); Progress.PendingNPCId = NAME_None; Progress.BattleCheckpointJson.Reset();
    PlayerA->Profile = MoveTemp(Candidate);
    State.bFinished = true; State.WinningTeam = WinningTeam; State.LastEvent = Summary;
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(BattleSafetyTimer);
    if (!bSeasonCommandTransaction)
    {
        if (!SaveSeasonCheckpoint())
        { PlayerA->Profile = Before; State = BeforeState; StartBattleSafetyChecks(); return false; }
        PlayerA->MarkProfileChanged();
    }
    return true;
}
