#!/usr/bin/env python3
"""Exercise the production campaign placement transaction with fault injection.

The current C++ function is extracted on every run and compiled with lightweight
Unreal API substitutes. This verifies cache ownership and failure handling, not
Unreal compilation, sprite loading, or the actual collision algorithm.
"""
from pathlib import Path
import importlib.util
import os
import shlex
import subprocess
import tempfile
import unittest


TOOLS = Path(__file__).resolve().parent
SOURCE = TOOLS.parent / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTPlayerController.cpp"
SIGNATURE = "bool ADigimonVenomNXTPlayerController::PrepareRelayPlacements(FString* OutError) const"


def core_stub():
    specification = importlib.util.spec_from_file_location(
        "digimon_sprite_test_stubs", TOOLS / "test_sprite_coordinates.py")
    module = importlib.util.module_from_spec(specification)
    specification.loader.exec_module(module)
    return module.CORE_STUB.replace("#pragma once", "")


STUBS = r"""
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#define TEXT(x) x
#define UE_LOG(...) ((void)0)
#define MoveTemp(x) std::move(x)
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    void Reset() { clear(); }
    const char* operator*() const { return c_str(); }
    template<class... T> static FString Printf(const char*, T...) { return "placement failure"; }
};
struct FName : FString {
    using FString::FString;
    FString ToString() const { return *this; }
};
template<class K, class V> struct TMap : std::map<K,V> {
    bool IsEmpty() const { return this->empty(); }
    bool Contains(const K& Key) const { return this->count(Key) != 0; }
    const V* Find(const K& Key) const {
        const auto It = this->find(Key);
        return It == this->end() ? nullptr : &It->second;
    }
    void Add(const K& Key, const V& Value) { (*this)[Key] = Value; }
};
enum class EDigimonRelayRole { Other, Champion, Challenger };
struct FDigimonRelayMap {
    int MapId = 2, SourceMapId = 113;
    FVector2D EntryPosition, ExitPosition, ArrivalPosition;
};
struct FDigimonRelayNPC {
    FName Id;
    FVector2D Position;
    EDigimonRelayRole Role = EDigimonRelayRole::Other;
};
namespace DigimonVenomNXTCampaign {
    FDigimonRelayMap Map;
    TArray<FDigimonRelayNPC> NPCs;
    const FDigimonRelayMap* GetMap(int, int) { return &Map; }
    const TArray<FDigimonRelayNPC>& NPCsForMap(int, int) { return NPCs; }
}
struct UDigimonVenomNXTWorldSubsystem {
    int Calls = 0, FailAt = 0;
    bool Valid = true;
    bool ValidatePrivateMapContent(int, FString& Error) {
        if (!Valid) Error = "preflight failure";
        return Valid;
    }
    bool ResolvePrivateMapPoint(int, const FVector2D&, FVector& Point, const TArray<FVector>& = {}) {
        ++Calls;
        if (Calls == FailAt) return false;
        Point = {double(Calls), 0, 0};
        return true;
    }
};
struct MockWorld {
    UDigimonVenomNXTWorldSubsystem Subsystem;
    template<class T> T* GetSubsystem() { return &Subsystem; }
};
struct ADigimonVenomNXTPlayerController {
    mutable int PlacementCampaign = 1, PlacementMapId = 1;
    int Campaign = 1, MapId = 2;
    mutable FVector RelayEntryLocal{11,0,0}, RelayExitLocal{22,0,0}, RelayArrivalLocal{44,0,0};
    mutable TMap<FName,FVector> RelayNPCLocalLocations;
    mutable MockWorld World;
    int GetStoryCampaign() const { return Campaign; }
    int GetRelayMapId() const { return MapId; }
    MockWorld* GetWorld() const { return &World; }
    bool PrepareRelayPlacements(FString* OutError = nullptr) const;
};
"""

CASES = r"""
void Check(bool Condition, const char* Message) {
    if (!Condition) throw std::runtime_error(Message);
}
int main() {
    try {
        DigimonVenomNXTCampaign::NPCs.Add({"first", {.1,.2}, EDigimonRelayRole::Other});
        DigimonVenomNXTCampaign::NPCs.Add({"second", {.5,.6}, EDigimonRelayRole::Other});
        ADigimonVenomNXTPlayerController Controller;
        Controller.RelayNPCLocalLocations.Add("old", {33,0,0});
        auto& World = Controller.World.Subsystem;
        FString Error;

        // Entrance, exit, first NPC, then a later NPC fail in separate attempts.
        // A later failure must not expose earlier successful candidate writes.
        for (int Failure : {1,2,3,4,5}) {
            World.Calls = 0;
            World.FailAt = Failure;
            Check(!Controller.PrepareRelayPlacements(&Error), "injected failure was accepted");
            Check(!Error.empty(), "failure did not return its diagnostic");
            Check(Controller.PlacementMapId == 1 && Controller.PlacementCampaign == 1,
                  "previous cache key changed on failure");
            Check(Controller.RelayEntryLocal.X == 11 && Controller.RelayExitLocal.X == 22 && Controller.RelayArrivalLocal.X == 44,
                  "previous portals changed on failure");
            Check(Controller.RelayNPCLocalLocations.size() == 1 &&
                  Controller.RelayNPCLocalLocations.Contains("old") &&
                  Controller.RelayNPCLocalLocations.Find("old")->X == 33,
                  "previous NPC cache changed on failure");
        }

        // Returning to the previous journey after failure must reuse its intact cache.
        Controller.MapId = 1;
        const int BeforeRetry = World.Calls;
        Check(Controller.PrepareRelayPlacements(&Error), "previous-map retry failed");
        Check(World.Calls == BeforeRetry && Error.empty(), "cache hit rebuilt or retained stale error");

        Controller.MapId = 2;
        World.Calls = 0;
        World.FailAt = 0;
        Check(Controller.PrepareRelayPlacements(&Error), "successful placement failed");
        Check(Controller.PlacementMapId == 2 && Controller.PlacementCampaign == 1,
              "successful placement did not commit its key");
        Check(Controller.RelayEntryLocal.X == 2 && Controller.RelayExitLocal.X == 3 && Controller.RelayArrivalLocal.X == 1,
              "successful placement did not commit its portals");
        Check(Controller.RelayNPCLocalLocations.size() == 2 &&
              Controller.RelayNPCLocalLocations.Contains("first") &&
              Controller.RelayNPCLocalLocations.Contains("second") &&
              !Controller.RelayNPCLocalLocations.Contains("old"),
              "successful placement did not replace the whole NPC cache");

        Controller.MapId = 3;
        World.Valid = false;
        const int BeforePreflight = World.Calls;
        Check(!Controller.PrepareRelayPlacements(&Error), "invalid preflight was accepted");
        Check(Error == "preflight failure" && World.Calls == BeforePreflight,
              "preflight failure was lost or placement continued");
        Check(Controller.PlacementMapId == 2 && Controller.RelayNPCLocalLocations.size() == 2 &&
              Controller.RelayEntryLocal.X == 2 && Controller.RelayExitLocal.X == 3 && Controller.RelayArrivalLocal.X == 1,
              "preflight failure damaged the prior cache");

        // Champion and title challenger share one stage but retain separate IDs.
        Controller.MapId = 4;
        DigimonVenomNXTCampaign::Map.MapId = 4;
        DigimonVenomNXTCampaign::NPCs.Reset();
        DigimonVenomNXTCampaign::NPCs.Add({"champion", {.5,.5}, EDigimonRelayRole::Champion});
        DigimonVenomNXTCampaign::NPCs.Add({"challenger", {.7,.7}, EDigimonRelayRole::Challenger});
        World.Valid = true;
        World.Calls = 0;
        World.FailAt = 5;
        Check(Controller.PrepareRelayPlacements(&Error), "shared champion stage failed");
        Check(World.Calls == 4 && Controller.RelayNPCLocalLocations.size() == 2 &&
              Controller.RelayNPCLocalLocations.Find("champion")->X ==
              Controller.RelayNPCLocalLocations.Find("challenger")->X,
              "challenger did not reuse champion stage");

        // Same map number in another campaign must not reuse a different story's cache.
        Controller.Campaign = 2;
        World.Calls = 0;
        Check(Controller.PrepareRelayPlacements(), "campaign switch failed without error output");
        Check(World.Calls == 4 && Controller.PlacementCampaign == 2,
              "cache ignored campaign identity");
        std::cout << "Five placement failures, rollback retry, successful commit, preflight, "
                     "champion stage and campaign identity checks passed\n";
        return 0;
    } catch (const std::exception& Error) {
        std::cerr << Error.what() << '\n';
        return 1;
    }
}
"""


class CampaignPlacementCacheTests(unittest.TestCase):
    def production_function(self):
        source = SOURCE.read_text(encoding="utf-8")
        self.assertEqual(source.count(SIGNATURE), 1, "Production placement function signature changed")
        body = source.split(SIGNATURE, 1)[1].split(
            "FVector ADigimonVenomNXTPlayerController::GetRelayNPCLocation", 1)[0]
        return SIGNATURE + body

    def run_function(self, function):
        with tempfile.TemporaryDirectory(prefix="digimon-campaign-cache-") as directory:
            root = Path(directory)
            source = root / "cache.cpp"
            source.write_text(core_stub() + STUBS + function + CASES, encoding="utf-8")
            binary = root / "cache"
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                str(source), "-o", str(binary),
            ]
            compiled = subprocess.run(command, capture_output=True, text=True, timeout=30, check=False)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            return subprocess.run([str(binary)], capture_output=True, text=True, timeout=10, check=False)

    def test_actual_function_preserves_cache_until_success(self):
        result = self.run_function(self.production_function())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_partial_cache_publication_regression_is_detected(self):
        function = self.production_function()
        publication = "CandidateLocations.Add(NPC.Id, Local);"
        self.assertEqual(function.count(publication), 1)
        mutant = function.replace(publication,
            publication + "\n        RelayNPCLocalLocations = CandidateLocations;", 1)
        result = self.run_function(mutant)
        self.assertNotEqual(result.returncode, 0, "Partial cache publication was not detected")
        self.assertIn("previous NPC cache changed on failure", result.stderr)


if __name__ == "__main__":
    unittest.main()
