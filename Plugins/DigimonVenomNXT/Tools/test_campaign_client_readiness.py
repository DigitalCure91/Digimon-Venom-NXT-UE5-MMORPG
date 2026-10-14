#!/usr/bin/env python3
"""Compile the actual client presentation gate and session handlers with mocks.

Exercises replication arrival order without loading Unreal. The production gate,
RPC handler, OnRep handler, revision policy and input-blocking method are used;
asset construction after the gate is replaced by an observable test seam.
"""
from itertools import permutations
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile
import unittest
from test_world_chat_integration import method


ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"
SOURCE = ROOT / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTPlayerController.cpp"


STUBS = r"""
#include "DigimonVenomNXTRelaySessionCore.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdint>
using int32 = std::int32_t;
using uint64 = std::uint64_t;
constexpr int INDEX_NONE = -1;
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    bool IsEmpty() const { return empty(); }
};
struct FVector {
    double X=0,Y=0,Z=0;
    bool ContainsNaN() const { return !std::isfinite(X)||!std::isfinite(Y)||!std::isfinite(Z); }
};
enum class EDigimonPrivateCampaign { Relay, ParadoxChronicles, GhostLine };
struct FDigimonRelaySession {
    EDigimonPrivateCampaign Campaign = EDigimonPrivateCampaign::Relay;
    bool bActive = false;
    int32 MapId = 1;
    FVector Origin;
    uint64 Revision = 0;
};
namespace DigimonVenomNXTCampaign {
    bool IsValid(EDigimonPrivateCampaign Campaign) {
        return DigimonVenomNXTRelaySessionCore::ValidCampaign(static_cast<int>(Campaign));
    }
    const int* GetMap(EDigimonPrivateCampaign Campaign, int32 MapId) {
        static const int Definition=1;
        return IsValid(Campaign) && MapId>=1 && MapId<=31 ? &Definition : nullptr;
    }
}
struct ADigimonVenomNXTPlayerState { struct { FString AccountId; } Profile; };
struct MockActor {
    bool Destroyed=false;
    int HideCalls=0;
    void Destroy() { Destroyed=true; }
    void SetActorHiddenInGame(bool) { ++HideCalls; }
};
bool IsValid(MockActor* Actor) { return Actor && !Actor->Destroyed; }
struct MockHUD {
    bool Typing=false;
    void CloseRelayDialogue() {}
    bool IsWorldChatTyping() const { return Typing; }
};
struct ADigimonVenomNXTPlayerController {
    bool Local=true, WorldReady=true, PawnReady=false, LocalPlayerReady=false, Farm=false;
    ADigimonVenomNXTPlayerState ProfileOwner;
    ADigimonVenomNXTPlayerState* PlayerState=nullptr;
    MockActor Renderer;
    MockActor* RelayScene=nullptr;
    MockActor* LocalMapRenderer=&Renderer;
    MockHUD* GameHUDWidget=nullptr;
    FDigimonRelaySession RelaySession, AppliedLocalRelaySession;
    int32 PresentedRelayMapId=INDEX_NONE;
    bool bRelayPresentationWaiting=false, bRelayPresentationFailurePending=false;
    bool bLogoutPending=false, bFieldMenuOpen=false, bRelayDialogueOpen=false;
    bool bFarmPresentationFailurePending=false, PendingWorldBattle=false;
    void* CurrentBattle=nullptr;
    int Attempts=0;
    bool ContentFailure=false;
    bool IsLocalController() const { return Local; }
    bool IsOwnerProfileReady() const { return PlayerState && !PlayerState->Profile.AccountId.empty(); }
    void* GetWorld() const { return WorldReady ? (void*)this : nullptr; }
    template<class T> T* GetPlayerState() const { return PlayerState; }
    void* GetPawn() const { return PawnReady ? (void*)this : nullptr; }
    void* GetLocalPlayer() const { return LocalPlayerReady ? (void*)this : nullptr; }
    bool IsInRelay() const { return RelaySession.bActive && !Farm; }
    bool IsInDigiFarm() const { return Farm; }
    bool HasPendingStoryBattle() const { return false; }
    bool HasPendingWorldBattle() const { return PendingWorldBattle; }
    void RefreshLocalActorPrivacy() {}
    void SetFieldMenuOpen(bool Open) { bFieldMenuOpen=Open; }
    void ApplyFieldInputMode() {}
    void RefreshRelayPresentation();
    void ClientSetRelayPresentation_Implementation(EDigimonPrivateCampaign Campaign,
        bool bInside,int32 MapId,FVector Origin,uint64 Revision);
    void OnRep_RelaySession();
    // INPUT_METHOD
};
"""


CASES = r"""
void Check(bool Condition,const char* Message) {
    if (!Condition) throw std::runtime_error(Message);
}
void Receive(ADigimonVenomNXTPlayerController& Controller,int Part) {
    if (Part==0) Controller.PlayerState=&Controller.ProfileOwner;
    if (Part==1) Controller.ProfileOwner.Profile.AccountId="signed-in-account";
    if (Part==2) Controller.PawnReady=true;
    if (Part==3) Controller.LocalPlayerReady=true;
}
void Ready(ADigimonVenomNXTPlayerController& Controller) {
    for (int Part=0;Part<4;++Part) Receive(Controller,Part);
}
int main() {
    try {
        const int Orders[][4]={/* ORDERS */};
        for (const auto& Order:Orders) {
            ADigimonVenomNXTPlayerController Controller;
            // An early content attempt would fail and permanently latch the old implementation.
            Controller.ContentFailure=true;
            Controller.ClientSetRelayPresentation_Implementation(
                EDigimonPrivateCampaign::GhostLine,true,1,{1000000,1000000,0},1);
            Check(Controller.Attempts==0,"presentation attempted before replicated state arrived");
            Check(Controller.bRelayPresentationWaiting && !Controller.bRelayPresentationFailurePending,
                  "replication delay was latched as an asset failure");
            Check(Controller.IsFieldInputBlocked(),"input allowed while waiting for campaign state");
            Check(Controller.Renderer.HideCalls==0,"public renderer hidden before state arrived");
            for (int Index=0;Index<4;++Index) {
                Receive(Controller,Order[Index]);
                if (Index==3) Controller.ContentFailure=false;
                // The existing local Tick retries RefreshRelayPresentation each frame.
                Controller.RefreshRelayPresentation();
                if (Index<3) {
                    Check(Controller.Attempts==0 && Controller.bRelayPresentationWaiting,
                          "partial state arrival incorrectly passed readiness gate");
                    Check(!Controller.bRelayPresentationFailurePending,"partial arrival latched failure");
                }
            }
            Check(Controller.Attempts==1 && !Controller.bRelayPresentationWaiting &&
                  !Controller.bRelayPresentationFailurePending,"late replicated state did not recover");
            Check(!Controller.IsFieldInputBlocked(),"input remained blocked after successful readiness");
        }
        ADigimonVenomNXTPlayerController Host;
        Ready(Host);
        Host.ClientSetRelayPresentation_Implementation(
            EDigimonPrivateCampaign::Relay,true,2,{1000000,1000000,0},7);
        Check(Host.Attempts==1 && !Host.bRelayPresentationWaiting,"ready listen host did not present immediately");
        Host.ClientSetRelayPresentation_Implementation(
            EDigimonPrivateCampaign::GhostLine,true,3,{1100000,1000000,0},6);
        Check(Host.Attempts==1 && Host.RelaySession.MapId==2 && Host.RelaySession.Revision==7,
              "stale RPC overwrote accepted session");
        Host.RelaySession.MapId=3;
        Host.RelaySession.Revision=6;
        Host.OnRep_RelaySession();
        Check(Host.Attempts==1 && Host.RelaySession.MapId==2 && Host.RelaySession.Revision==7,
              "stale property overwrote accepted session");
        Host.ClientSetRelayPresentation_Implementation(
            EDigimonPrivateCampaign::Relay,true,2,{1000000,1000000,0},7);
        Check(Host.Attempts==2 && !Host.bRelayPresentationWaiting && !Host.bRelayPresentationFailurePending,
              "duplicate accepted RPC introduced a failure");

        // Real content failures retain the existing stop-and-report behavior.
        Host.ContentFailure=true;
        Host.RefreshRelayPresentation();
        Check(Host.bRelayPresentationFailurePending && !Host.bRelayPresentationWaiting,
              "actual content failure was confused with replication wait");
        const int AttemptsBeforeFailureRetry=Host.Attempts;
        Host.RefreshRelayPresentation();
        Check(Host.Attempts==AttemptsBeforeFailureRetry,"actual content failure was retried every frame");
        Host.bRelayPresentationWaiting=true;
        Host.ClientSetRelayPresentation_Implementation(
            EDigimonPrivateCampaign::Relay,false,2,{1000000,1000000,0},8);
        Check(!Host.bRelayPresentationWaiting && !Host.bRelayPresentationFailurePending,
              "leaving campaign retained presentation blocker");
        MockHUD ChatHUD;
        Host.GameHUDWidget=&ChatHUD;
        Check(!Host.IsFieldInputBlocked(),"idle chat blocked field input");
        ChatHUD.Typing=true;
        Check(Host.IsFieldInputBlocked(),"chat typing did not block field input");
        Check(!Host.IsFieldPresentationBlocked(),"chat typing hid public field presentation");
        ChatHUD.Typing=false;
        Host.PendingWorldBattle=true;
        Check(Host.CurrentBattle==nullptr && Host.IsFieldInputBlocked() && Host.IsFieldPresentationBlocked(),
              "saved public wild battle allowed movement before resume");
        Host.PendingWorldBattle=false;
        Host.bFieldMenuOpen=true;
        Check(Host.IsFieldInputBlocked() && Host.IsFieldPresentationBlocked(),
              "open menu must independently block field input and presentation");
        Host.bFieldMenuOpen=false;
        Check(!Host.IsFieldInputBlocked() && !Host.IsFieldPresentationBlocked(),
              "field input failed to resume after dismissing menu");
        std::cout << "24 arrival orders, late-state retry, input gate, host, stale/duplicate sessions "
                     "and content-failure/menu separation passed\n";
        return 0;
    } catch (const std::exception& Error) {
        std::cerr << Error.what() << '\n';
        return 1;
    }
}
"""


class CampaignClientReadinessTests(unittest.TestCase):
    def production_functions(self):
        source = SOURCE.read_text(encoding="utf-8")
        rpc = source.split("void ADigimonVenomNXTPlayerController::ClientSetRelayPresentation_Implementation", 1)[1]
        rpc = "void ADigimonVenomNXTPlayerController::ClientSetRelayPresentation_Implementation" + rpc.split(
            "void ADigimonVenomNXTPlayerController::OnRep_RelaySession", 1)[0]
        on_rep = source.split("void ADigimonVenomNXTPlayerController::OnRep_RelaySession", 1)[1]
        on_rep = "void ADigimonVenomNXTPlayerController::OnRep_RelaySession" + on_rep.split(
            "void ADigimonVenomNXTPlayerController::RefreshRelayPresentation", 1)[0]
        presentation = source.split("void ADigimonVenomNXTPlayerController::RefreshRelayPresentation", 1)[1]
        gate = "void ADigimonVenomNXTPlayerController::RefreshRelayPresentation" + presentation.split("    FString CastKey;", 1)[0]
        self.assertIn("if (bRelayPresentationWaiting) return;", gate)
        self.assertLess(gate.index("if (bRelayPresentationWaiting) return;"),
                        gate.index("LocalMapRenderer->SetActorHiddenInGame(true)"))
        gate += "    ++Attempts;\n    bRelayPresentationFailurePending = ContentFailure;\n}\n"
        header = (PUBLIC / "DigimonVenomNXTPlayerController.h").read_text(encoding="utf-8")
        presentation_method = re.search(r"bool IsFieldPresentationBlocked\(\) const \{[^\n]+\}", header).group(0)
        input_method = (presentation_method + "\n" +
                        method(source, "ADigimonVenomNXTPlayerController::IsFieldInputBlocked").replace(
                            "ADigimonVenomNXTPlayerController::", "", 1))
        self.assertIn("bRelayPresentationWaiting", input_method)
        return rpc + on_rep + gate, input_method

    def compile_and_run(self, functions, input_method):
        orders = ",".join("{" + ",".join(map(str, order)) + "}" for order in permutations(range(4)))
        program = STUBS.replace("// INPUT_METHOD", input_method) + functions + CASES.replace("/* ORDERS */", orders)
        with tempfile.TemporaryDirectory(prefix="digimon-client-readiness-") as directory:
            source = Path(directory) / "readiness.cpp"
            source.write_text(program, encoding="utf-8")
            executable = Path(directory) / "readiness"
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                "-I", str(PUBLIC), str(source), "-o", str(executable),
            ]
            result = subprocess.run(command, capture_output=True, text=True, timeout=30, check=False)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            return subprocess.run([str(executable)], capture_output=True, text=True, timeout=10, check=False)

    def test_actual_gate_retries_for_all_replication_orders(self):
        result = self.compile_and_run(*self.production_functions())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_missing_readiness_gate_regression_is_detected(self):
        functions, input_method = self.production_functions()
        functions = functions.replace("if (bRelayPresentationWaiting) return;", "", 1)
        result = self.compile_and_run(functions, input_method)
        self.assertNotEqual(result.returncode, 0, "Missing readiness gate was not detected")
        self.assertIn("presentation attempted before replicated state arrived", result.stderr)

    def test_scene_diagnostics_reach_the_client_without_generic_overwrite(self):
        source = SOURCE.read_text(encoding="utf-8")
        scene = (SOURCE.parent / "DigimonVenomNXTRelayScene.cpp").read_text(encoding="utf-8")
        header = (PUBLIC / "DigimonVenomNXTRelayScene.h").read_text(encoding="utf-8")
        self.assertIn("InitializeFor(ADigimonVenomNXTPlayerController* Controller, FString* OutError = nullptr)", header)
        self.assertIn("bool RebuildCast(FString* OutError = nullptr)", header)
        self.assertIn("return RebuildCast(OutError);", scene)
        self.assertIn("!RelayScene->InitializeFor(this, &PresentationError) && PresentationError.IsEmpty()", source)
        for code in ("SCENE_CONTEXT", "SCENE_PLAYER_STATE", "SCENE_GROUND_SPAWN", "SCENE_GROUND_CONTENT",
                     "SCENE_GUARDIAN_TEAM", "SCENE_GUARDIAN_ASSET", "SCENE_GUARDIAN_POSE",
                     "SCENE_GUARDIAN_ANCHOR", "SCENE_TAMER_STYLE", "SCENE_TAMER_ASSET", "SCENE_TAMER_POSE"):
            self.assertIn('TEXT("' + code + '")', scene, code)
        self.assertIn('TEXT("Contact %s is missing tamer animation asset %s"), *NPC.Id.ToString(), *Path', scene)
        self.assertIn('TEXT("Guardian %s is missing animation asset %s"), *NPC.Id.ToString(), *Path', scene)


if __name__ == "__main__":
    unittest.main()
