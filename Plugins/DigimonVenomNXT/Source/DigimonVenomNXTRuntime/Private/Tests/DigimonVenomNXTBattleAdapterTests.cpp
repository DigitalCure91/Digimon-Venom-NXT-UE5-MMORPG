#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTTimelineCore.h"
#include "Engine/World.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonBattleAdapterTest,
    "DigimonVenomNXT.Combat.RuntimeAdapter.DamageTimelineGuardAndWildEscape",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonBattleAdapterTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    if (!TestNotNull(TEXT("Isolated combat test world"), World)) return false;
    ON_SCOPE_EXIT { World->DestroyWorld(false); };
    ADigimonVenomNXTBattleActor* Battle = World->SpawnActor<ADigimonVenomNXTBattleActor>();
    ADigimonVenomNXTPlayerState* Player = World->SpawnActor<ADigimonVenomNXTPlayerState>();
    if (!TestNotNull(TEXT("Actual runtime battle actor"), Battle) || !TestNotNull(TEXT("Fixture player state"), Player)) return false;
    auto MakeUnit = [](int32 Speed)
    {
        FDigimonBattleUnit Unit;
        Unit.InstanceId = FGuid::NewGuid(); Unit.SpeciesId = TEXT("Fixture"); Unit.DisplayName = TEXT("Fixture");
        Unit.Level = 50; Unit.HP = Unit.Stats.MaxHP = 1500; Unit.SP = Unit.Stats.MaxSP = 100;
        Unit.Stats.Attack = 200; Unit.Stats.Defense = 175; Unit.Stats.Spirit = 200; Unit.Stats.Speed = Speed;
        Unit.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        return Unit;
    };
    FDigimonBattleUnit A = MakeUnit(100), B = MakeUnit(50);
    Battle->PlayerA = Player;
    Battle->State.BattleId = FGuid::NewGuid();
    Battle->State.Kind = EDigimonBattleKind::Wild;
    Battle->State.TeamA.Active.Add(A); Battle->State.TeamB.Active.Add(B);
    FDigimonMoveSlot Physical;
    FDigimonMoveSlot Special;
    Special.Power = 155; Special.DamageClass = EDigimonDamageClass::Special; Special.Element = EDigimonElement::Fire;
    A.Affinity = EDigimonAffinity::Vaccine; B.Affinity = EDigimonAffinity::Virus; B.Element = EDigimonElement::Plant;
    A.Stats.Attack = 20; A.Stats.Spirit = 200; B.Stats.Defense = 200; B.Stats.Spirit = 20;
    TestEqual(TEXT("Runtime physical attack uses DEF and cannot erase the level gap"), Battle->ComputeMoveDamage_Implementation(A, B, Physical), 1);
    auto CoreA = DigimonVenomNXTAutoBattle::ToCoreUnit(A), CoreB = DigimonVenomNXTAutoBattle::ToCoreUnit(B);
    const auto CoreMove = DigimonVenomNXTAutoBattle::ToCoreMove(Special);
    const int32 MinSpecial = DigimonVenomNXTCombatCore::CalculateDamage(CoreA, CoreB, CoreMove, 0.92f);
    const int32 MaxSpecial = DigimonVenomNXTCombatCore::CalculateDamage(CoreA, CoreB, CoreMove, 1.08f);
    const int32 ActualSpecial = Battle->ComputeMoveDamage_Implementation(A, B, Special);
    TestTrue(TEXT("Actual runtime wrapper uses INT and combined type/element metadata"), ActualSpecial >= MinSpecial && ActualSpecial <= MaxSpecial);
    B.bGuarding = true;
    const int32 Guarded = Battle->ComputeMoveDamage_Implementation(A, B, Special);
    TestTrue(TEXT("Runtime Guard halves the resulting hit and meaningfully reduces damage"), Guarded < MinSpecial);
    A = MakeUnit(100); B = MakeUnit(50);
    TestTrue(TEXT("Neutral equal-level runtime attacks take more than two hits"), Battle->ComputeMoveDamage_Implementation(A, B, Physical) < B.HP / 3);

    Battle->InitializeTimeline();
    TestEqual(TEXT("Faster unit receives initial action"), Battle->State.ActingTeam, 0);
    TestEqual(TEXT("Initial time is 500 / SPD"), Battle->State.BattleClock, 5.0);
    FDigimonBattleCommand Guard; Guard.Action = EDigimonBattleAction::Guard; Guard.ActingSlot = 0;
    FString Error;
    TestTrue(TEXT("Guard requires no enemy target"), Battle->ValidateCommand(0, Guard, Error));
    Battle->PendingA.Add(0, Guard);
    Battle->ResolveRound();
    TestEqual(TEXT("AI acts then yields to next faster-unit opportunity"), Battle->State.ActingTeam, 0);
    TestEqual(TEXT("Continuous clock advances to 15, not a team round"), Battle->State.BattleClock, 15.0);
    TestFalse(TEXT("Guard expires precisely at owner's next input opportunity"), Battle->State.TeamA.Active[0].bGuarding);
    TestTrue(TEXT("Actual enemy action records guard reduction"), Battle->State.PresentationEvents.ContainsByPredicate(
        [](const FDigimonBattlePresentationEvent& Event) { return Event.ActingTeam == 1 && Event.bGuarded; }));
    TestFalse(TEXT("Earlier action ID cannot be replayed"), DigimonVenomNXTCombatCore::IsCurrentDecision(Battle->State.BattleId,
        Battle->State.TurnNumber, Battle->State.BattleId, Battle->State.TurnNumber - 1));
    FDigimonBattleCommand Forged = Guard; Forged.Action = static_cast<EDigimonBattleAction>(255);
    TestFalse(TEXT("Unknown network action is rejected"), Battle->ValidateCommand(0, Forged, Error));
    Forged = Guard; Forged.ActingSlot = 1;
    TestFalse(TEXT("Nonexistent / ineligible actor cannot spend an action"), Battle->ValidateCommand(0, Forged, Error));

    FDigimonSeasonBattleCheckpoint Checkpoint;
    Checkpoint.State = Battle->State;
    FString Json;
    FDigimonSeasonBattleCheckpoint Restored;
    TestTrue(TEXT("Version-2 checkpoint serializes"), FJsonObjectConverter::UStructToJsonObjectString(Checkpoint, Json));
    TestTrue(TEXT("Version-2 checkpoint deserializes"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Restored, 0, 0));
    TestTrue(TEXT("Exact clock, stable identities, Guard and current input survive reconnect"),
        FDigimonBattleState::StaticStruct()->CompareScriptStruct(&Checkpoint.State, &Restored.State, 0));

    // Exercise the real adapter with every supported wild formation size. Duplicate
    // species intentionally verify that targeting and CTB use individual identities.
    for (int32 EnemyCount = 1; EnemyCount <= 3; ++EnemyCount)
    {
        ADigimonVenomNXTBattleActor* GroupBattle = World->SpawnActor<ADigimonVenomNXTBattleActor>();
        if (!TestNotNull(TEXT("Wild group fixture battle"), GroupBattle)) return false;
        GroupBattle->PlayerA = Player;
        GroupBattle->State.BattleId = FGuid(1, 2, 3, EnemyCount);
        GroupBattle->State.Kind = EDigimonBattleKind::Wild;
        GroupBattle->State.TeamA.Active.Add(MakeUnit(100));
        for (int32 Slot = 0; Slot < EnemyCount; ++Slot)
        {
            FDigimonBattleUnit Wild = MakeUnit(50);
            Wild.SP = 90 - Slot * 10;
            GroupBattle->State.TeamB.Active.Add(Wild);
        }
        GroupBattle->InitializeTimeline();
        TestEqual(FString::Printf(TEXT("%d-enemy opening records every combatant"), EnemyCount),
            GroupBattle->State.InitialActiveCount, EnemyCount + 1);

        FDigimonBattleCommand Attack;
        Attack.Action = EDigimonBattleAction::Attack;
        Attack.ActingSlot = 0;
        for (int32 Slot = 0; Slot < EnemyCount; ++Slot)
        {
            Attack.TargetSlot = Slot;
            TestTrue(FString::Printf(TEXT("%d-enemy formation accepts target slot %d"), EnemyCount, Slot),
                GroupBattle->ValidateCommand(0, Attack, Error));
            const FDigimonBattleTeam BeforeAttack = GroupBattle->State.TeamB;
            GroupBattle->ResolveOne(0, Attack);
            const FDigimonBattleUnit& Target = GroupBattle->State.TeamB.Active[Slot];
            TestTrue(TEXT("Attack damages the selected wild unit without defeating the healthy fixture"),
                Target.HP > 0 && Target.HP < BeforeAttack.Active[Slot].HP);
            for (int32 OtherSlot = 0; OtherSlot < EnemyCount; ++OtherSlot)
                if (OtherSlot != Slot)
                    TestEqual(TEXT("Targeted attack preserves every other wild unit's HP"),
                        GroupBattle->State.TeamB.Active[OtherSlot].HP, BeforeAttack.Active[OtherSlot].HP);
            TestTrue(TEXT("Attack presentation identifies the selected instance"),
                GroupBattle->State.PresentationEvents.ContainsByPredicate(
                    [&Target, Slot](const FDigimonBattlePresentationEvent& Event)
                    { return Event.TargetTeam == 1 && Event.TargetSlot == Slot && Event.TargetInstanceId == Target.InstanceId; }));
        }
        Attack.TargetSlot = EnemyCount;
        TestFalse(TEXT("First nonexistent wild target slot is rejected"), GroupBattle->ValidateCommand(0, Attack, Error));

        // All same-speed enemies must act once at time 10 before the player returns
        // at time 15; a single shared enemy identity would lose one of these actions.
        GroupBattle->PendingA.Add(0, Guard);
        GroupBattle->ResolveRound();
        TestEqual(TEXT("Wild group AI returns input to the player"), GroupBattle->State.ActingTeam, 0);
        TestEqual(TEXT("Wild group AI retains the continuous action clock"), GroupBattle->State.BattleClock, 15.0);
        TestFalse(TEXT("The opening AI sequence leaves the wild group battle active"), GroupBattle->State.bFinished);
        TSet<FGuid> ActingWildIds;
        for (const FDigimonBattlePresentationEvent& Event : GroupBattle->State.PresentationEvents)
        {
            if (Event.ActingTeam != 1) continue;
            TestTrue(TEXT("AI event uses a valid wild actor slot"), GroupBattle->State.TeamB.Active.IsValidIndex(Event.ActingSlot));
            if (GroupBattle->State.TeamB.Active.IsValidIndex(Event.ActingSlot))
                TestTrue(TEXT("AI event retains that slot's distinct instance identity"),
                    Event.ActingInstanceId == GroupBattle->State.TeamB.Active[Event.ActingSlot].InstanceId);
            TestFalse(TEXT("Each wild instance acts only once in the opening AI sequence"), ActingWildIds.Contains(Event.ActingInstanceId));
            ActingWildIds.Add(Event.ActingInstanceId);
        }
        TestEqual(FString::Printf(TEXT("All %d wild instances receive their own AI action"), EnemyCount), ActingWildIds.Num(), EnemyCount);
        for (int32 Slot = 0; Slot < EnemyCount; ++Slot)
        {
            const FDigimonBattleUnit& Wild = GroupBattle->State.TeamB.Active[Slot];
            TestEqual(TEXT("Every wild instance has a distinct stable timeline order"), Wild.TimelineOrder, Slot);
            TestEqual(TEXT("Every wild instance is rescheduled independently after acting"), Wild.NextActionTime, 30.0);
        }

        auto CheckGroupRoundTrip = [this, GroupBattle, EnemyCount]()
        {
            FDigimonSeasonBattleCheckpoint GroupCheckpoint;
            GroupCheckpoint.State = GroupBattle->State;
            FDigimonSeasonBattleCheckpoint RestoredGroup;
            FString GroupJson;
            if (!TestTrue(TEXT("Wild group checkpoint serializes"), FJsonObjectConverter::UStructToJsonObjectString(GroupCheckpoint, GroupJson))) return;
            if (!TestTrue(TEXT("Wild group checkpoint deserializes"), FJsonObjectConverter::JsonObjectStringToUStruct(GroupJson, &RestoredGroup, 0, 0))) return;
            TestEqual(TEXT("Checkpoint keeps the complete wild formation"), RestoredGroup.State.TeamB.Active.Num(), EnemyCount);
            TestTrue(TEXT("Checkpoint preserves all wild identities, partial HP/SP, defeat flags, events and exact timeline"),
                FDigimonBattleState::StaticStruct()->CompareScriptStruct(&GroupCheckpoint.State, &RestoredGroup.State, 0));
        };
        CheckGroupRoundTrip();

        GroupBattle->State.TeamB.Active[0].HP = 1;
        Attack.TargetSlot = 0;
        if (EnemyCount > 1)
        {
            GroupBattle->PendingA.Add(0, Attack);
            GroupBattle->ResolveRound();
            TestTrue(TEXT("First wild unit is defeated by the actual round resolver"), GroupBattle->State.TeamB.Active[0].bDefeated);
            TestFalse(TEXT("Defeating the first enemy does not finish a multi-enemy wild encounter"), GroupBattle->State.bFinished);
            TestFalse(TEXT("A surviving wild unit prevents team defeat"), GroupBattle->IsTeamDefeated(GroupBattle->State.TeamB));
            TestFalse(TEXT("A defeated wild target is rejected on the next player decision"), GroupBattle->ValidateCommand(0, Attack, Error));
            Attack.TargetSlot = EnemyCount - 1;
            TestTrue(TEXT("The remaining final slot stays targetable after the first knockout"), GroupBattle->ValidateCommand(0, Attack, Error));
            CheckGroupRoundTrip();
        }
        else
        {
            // Resolve individual final hits without reward settlement: this isolated
            // fixture deliberately has no GameInstance or account-save subsystem.
            GroupBattle->ResolveOne(0, Attack);
        }
        for (int32 Slot = 1; Slot < EnemyCount; ++Slot)
        {
            TestFalse(TEXT("Wild team is not defeated while another target remains"), GroupBattle->IsTeamDefeated(GroupBattle->State.TeamB));
            GroupBattle->State.TeamB.Active[Slot].HP = 1;
            Attack.TargetSlot = Slot;
            GroupBattle->ResolveOne(0, Attack);
        }
        TestTrue(TEXT("Wild team is defeated only after every member falls"), GroupBattle->IsTeamDefeated(GroupBattle->State.TeamB));
    }

    FDigimonBattleCommand Flee; Flee.Action = EDigimonBattleAction::Retreat; Flee.ActingSlot = 0;
    for (EDigimonBattleKind Kind : {EDigimonBattleKind::AITamer, EDigimonBattleKind::Season, EDigimonBattleKind::Ranked,
        EDigimonBattleKind::Story, EDigimonBattleKind::Friendly})
    {
        Battle->State.Kind = Kind;
        TestFalse(TEXT("Trainer/ranked/season/story/friendly escape rejected at validation"), Battle->ValidateCommand(0, Flee, Error));
        Battle->ResolveOne(0, Flee);
        TestFalse(TEXT("Forged non-wild escape rejected again at execution"), Battle->State.bFinished || Battle->State.bFled);
    }
    Battle->State.Kind = EDigimonBattleKind::Wild;
    Battle->State.TeamA.Active[0].HP = 333; Battle->State.TeamA.Active[0].SP = 7;
    FDigimonOwnedPartner Owned;
    Owned.InstanceId = Battle->State.TeamA.Active[0].InstanceId; Owned.SpeciesId = TEXT("Fixture");
    Owned.CurrentHP = 333; Owned.CurrentSP = 7; Owned.Experience = 12345;
    Owned.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
    Player->Profile.Collection.Add(Owned); Player->Profile.Party.Add(Owned.InstanceId);
    Player->Profile.Credits = 8123;
    const int32 BeforeScans = Player->Profile.Scans.Num();
    TestTrue(TEXT("Only a genuine wild encounter permits escape"), Battle->ValidateCommand(0, Flee, Error));
    Battle->ResolveOne(0, Flee);
    TestTrue(TEXT("Escape finishes immediately without a winner"), Battle->State.bFinished && Battle->State.bFled && Battle->State.WinningTeam == INDEX_NONE);
    TestEqual(TEXT("Escape preserves exact current HP"), Player->Profile.Collection[0].CurrentHP, 333);
    TestEqual(TEXT("Escape preserves exact current SP"), Player->Profile.Collection[0].CurrentSP, 7);
    TestEqual(TEXT("Escape awards no XP"), Player->Profile.Collection[0].Experience, static_cast<int64>(12345));
    TestEqual(TEXT("Escape awards no credits"), Player->Profile.Credits, static_cast<int64>(8123));
    TestEqual(TEXT("Escape awards no scan data"), Player->Profile.Scans.Num(), BeforeScans);
    return true;
}
#endif
