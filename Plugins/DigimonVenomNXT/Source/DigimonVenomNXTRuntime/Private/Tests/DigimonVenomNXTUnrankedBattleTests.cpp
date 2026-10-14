#if WITH_DEV_AUTOMATION_TESTS
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonUnrankedBattleTest,
    "DigimonVenomNXT.Community.Unranked.OwnershipSnapshotsSettlementAndForfeit",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonUnrankedBattleTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    if (!TestNotNull(TEXT("Isolated game world"), World)) return false;
    ON_SCOPE_EXIT { World->DestroyWorld(false); };
    ADigimonVenomNXTBattleActor* Battle = World->SpawnActor<ADigimonVenomNXTBattleActor>();
    ADigimonVenomNXTPlayerState* A = World->SpawnActor<ADigimonVenomNXTPlayerState>();
    ADigimonVenomNXTPlayerState* B = World->SpawnActor<ADigimonVenomNXTPlayerState>();
    APlayerController* ControllerA = World->SpawnActor<APlayerController>();
    APlayerController* ControllerB = World->SpawnActor<APlayerController>();
    APlayerController* Stranger = World->SpawnActor<APlayerController>();
    if (!Battle || !A || !B || !ControllerA || !ControllerB || !Stranger) return false;
    ControllerA->PlayerState = A; ControllerB->PlayerState = B;
    auto Seed = [](ADigimonVenomNXTPlayerState* Player, const TCHAR* Name)
    {
        Player->Profile.Username = Name;
        Player->Profile.Credits = 971;
        Player->Profile.DigiRubies = 19;
        FDigimonOwnedPartner Partner;
        Partner.InstanceId = FGuid::NewGuid();
        Partner.SpeciesId = TEXT("Fixture"); Partner.Level = 20;
        Partner.CurrentHP = 0; Partner.CurrentSP = 3; Partner.Experience = 888;
        Partner.CombatBalanceVersion = DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        Player->Profile.Collection.Add(Partner); Player->Profile.Party.Add(Partner.InstanceId);
    };
    Seed(A, TEXT("Alpha")); Seed(B, TEXT("Beta"));
    const FDigimonPlayerProfile BeforeA = A->Profile, BeforeB = B->Profile;
    if (!TestTrue(TEXT("Both injured parties can enter snapshot sparring"), Battle->InitializeTamerBattle(A, B, EDigimonBattleKind::Friendly))) return false;
    TestEqual(TEXT("Snapshot A fully restored"), Battle->State.TeamA.Active[0].HP, Battle->State.TeamA.Active[0].Stats.MaxHP);
    TestEqual(TEXT("Snapshot B fully restored"), Battle->State.TeamB.Active[0].HP, Battle->State.TeamB.Active[0].Stats.MaxHP);
    TestEqual(TEXT("Starting never heals saved party"), A->Profile.Collection[0].CurrentHP, 0);
    TestEqual(TEXT("Starting preserves saved SP"), B->Profile.Collection[0].CurrentSP, 3);
    TestTrue(TEXT("Decision deadline established"), Battle->UnrankedDecisionDeadline > 0.0);
    FDigimonBattleCommand Item;
    Item.Action = EDigimonBattleAction::Item; Item.ActingSlot = Battle->State.ActingSlot; Item.ItemId = TEXT("hp_s");
    FString Error;
    TestFalse(TEXT("Inventory cannot be spent in unranked"), Battle->ValidateCommand(Battle->State.ActingTeam, Item, Error));
    TestFalse(TEXT("Nonparticipant cannot surrender someone else's match"), Battle->ForfeitUnranked(Stranger, TEXT("forged")));
    TestFalse(TEXT("Nonparticipant cannot submit commands"), Battle->SubmitCommand(Stranger, Item, Error));
    const int32 Acting = Battle->State.ActingTeam;
    FDigimonBattleCommand Guard;
    Guard.ExpectedBattleId = Battle->State.BattleId; Guard.ExpectedTurnNumber = Battle->State.TurnNumber;
    Guard.Action = EDigimonBattleAction::Guard; Guard.ActingSlot = Battle->State.ActingSlot;
    TestFalse(TEXT("Opponent cannot command the other side's active turn"), Battle->SubmitCommand(Acting == 0 ? ControllerB : ControllerA, Guard, Error));
    TestTrue(TEXT("Surrender works even outside your turn"), Battle->ForfeitUnranked(ControllerB, TEXT("Beta surrendered.")));
    TestFalse(TEXT("A result is not published without durable profile storage"), Battle->State.bFinished);
    TestTrue(TEXT("The accepted outcome is queued for safe retry"), Battle->bUnrankedSettlementPending);
    TestEqual(TEXT("Surrender outcome is frozen to the other side"), Battle->PendingUnrankedWinner, 0);
    TestEqual(TEXT("No premature winner counter"), A->Profile.UnrankedWins, 0);
    TestEqual(TEXT("No premature loser counter"), B->Profile.UnrankedLosses, 0);
    TestFalse(TEXT("A repeated surrender cannot settle twice"), Battle->ForfeitUnranked(ControllerB, TEXT("retry")));
    TestFalse(TEXT("A saving match cannot accept another turn"), Battle->ValidateCommand(Acting, Guard, Error));
    TestFalse(TEXT("Failed retry remains unpublished"), Battle->FinishUnrankedMatch(1, TEXT("wrong later outcome"), true));
    TestEqual(TEXT("Later calls cannot reverse the accepted outcome"), Battle->PendingUnrankedWinner, 0);
    TestTrue(TEXT("Every saved profile field remains unchanged when storage is unavailable"),
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&A->Profile, &BeforeA, 0) &&
        FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&B->Profile, &BeforeB, 0));
    FDigimonPlayerProfile Record = BeforeA;
    Record.UnrankedWins = 19; Record.UnrankedLosses = 6; Record.UnrankedDraws = 2;
    FString Json; FDigimonPlayerProfile Restored;
    TestTrue(TEXT("Unranked profile serializes"), FJsonObjectConverter::UStructToJsonObjectString(Record, Json));
    TestTrue(TEXT("Unranked profile reloads"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Restored, 0, 0));
    TestEqual(TEXT("Wins survive profile round trip"), Restored.UnrankedWins, 19);
    TestEqual(TEXT("Losses survive profile round trip"), Restored.UnrankedLosses, 6);
    TestEqual(TEXT("Draws survive profile round trip"), Restored.UnrankedDraws, 2);

    ADigimonVenomNXTBattleActor* Abort = World->SpawnActor<ADigimonVenomNXTBattleActor>();
    if (!TestNotNull(TEXT("Safety-cancellation fixture"), Abort) || !TestTrue(TEXT("Another isolated fixture can initialize"), Abort->InitializeTamerBattle(A, B, EDigimonBattleKind::Friendly))) return false;
    Abort->FinishBattle(INDEX_NONE, TEXT("Invalid formation safety cancellation."), false);
    TestTrue(TEXT("A safety cancellation can end without inventing a played result"), Abort->State.bFinished);
    TestEqual(TEXT("Cancelled matches do not grant draws"), A->Profile.UnrankedDraws, 0);
    TestTrue(TEXT("Safety cancellation never modifies profile"), FDigimonPlayerProfile::StaticStruct()->CompareScriptStruct(&A->Profile, &BeforeA, 0));
    return true;
}
#endif
