#!/usr/bin/env python3
"""Portable regression test for the packaged-startup sprite loading boundary.

Compiles the actual ConfigureDefaults/Configure definitions with small component
and loader fakes. This verifies when the code requests assets, its material
fallback, and actor call-site wiring. It is NOT an Unreal build, Windows launch,
or verification of the in-engine async loader.
"""
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"


def definition(source, signature):
    start = source.index(signature)
    end = source.index("{", start) + 1
    depth = 1
    while depth:
        depth += (source[end] == "{") - (source[end] == "}")
        end += 1
    return source[start:end]


FAKES = r'''
#include <iostream>
#include <string>
enum EBlendMode { BLEND_Opaque, BLEND_Masked };
namespace ECollisionEnabled { enum Type { QueryAndPhysics, NoCollision }; }
constexpr int LOAD_NoWarn = 1, LOAD_Quiet = 2;
#define TEXT(x) x
static int Loads = 0, Errors = 0;
static bool GameThread = true;
#define UE_LOG(...) (++Errors)
bool IsInGameThread() { return GameThread; }
struct UMaterialInterface {
    EBlendMode Blend;
    EBlendMode GetBlendMode() const { return Blend; }
};
UMaterialInterface Masked{BLEND_Masked}, Opaque{BLEND_Opaque};
static UMaterialInterface* Generated = &Masked;
static UMaterialInterface* Fallback = &Masked;
template<typename T> T* LoadObject(void*, const char* path, void* = nullptr, int = 0) {
    ++Loads;
    return std::string(path).find("/DigimonVenomNXT/") == 0 ? Generated : Fallback;
}
struct AActor {
    bool Template = false;
    bool IsTemplate() const { return Template; }
};
struct UPaperFlipbookComponent {
    bool Template = false, Registered = true, Visible = true;
    bool Shadow = true, Decals = true, CustomDepth = false;
    int SortPriority = 9, Stencil = 73, Writes = 0;
    ECollisionEnabled::Type Collision = ECollisionEnabled::QueryAndPhysics;
    AActor* Owner = nullptr;
    UMaterialInterface* Materials[2] = {&Opaque, &Opaque};
    bool IsTemplate() const { return Template; }
    bool IsRegistered() const { return Registered; }
    AActor* GetOwner() const { return Owner; }
    void SetCollisionEnabled(ECollisionEnabled::Type value) { ++Writes; Collision = value; }
    void SetCastShadow(bool value) { ++Writes; Shadow = value; }
    void SetReceivesDecals(bool value) { ++Writes; Decals = value; }
    void SetRenderCustomDepth(bool value) { ++Writes; CustomDepth = value; }
    void SetTranslucentSortPriority(int value) { ++Writes; SortPriority = value; }
    void SetVisibility(bool value) { ++Writes; Visible = value; }
    void SetMaterial(int slot, UMaterialInterface* value) { ++Writes; Materials[slot] = value; }
};
namespace DigimonVenomNXTFieldSprite {
    void ConfigureDefaults(UPaperFlipbookComponent*);
    void Configure(UPaperFlipbookComponent*);
}
'''

SCENARIOS = r'''
int main(int argc, char** argv) {
    const std::string scenario = argc > 1 ? argv[1] : "";
    AActor owner;
    UPaperFlipbookComponent sprite;
    sprite.Owner = &owner;
    auto fail = [&](const char* message) {
        std::cerr << scenario << ": " << message << '\n';
        return 1;
    };
    if (scenario == "defaults") {
        sprite.Registered = false;
        sprite.Template = true;
        owner.Template = true;
        GameThread = false;
        DigimonVenomNXTFieldSprite::ConfigureDefaults(nullptr);
        DigimonVenomNXTFieldSprite::ConfigureDefaults(&sprite);
        if (Loads || Errors) return fail("constructor defaults requested an asset");
        if (sprite.Materials[0] != &Opaque || sprite.Materials[1] != &Opaque)
            return fail("constructor defaults assigned a material");
    } else if (scenario == "null") {
        DigimonVenomNXTFieldSprite::Configure(nullptr);
        return Loads || Errors ? fail("null component requested assets") : 0;
    } else if (scenario == "template" || scenario == "owner-template" ||
               scenario == "off-thread" || scenario == "unregistered") {
        sprite.Template = scenario == "template";
        owner.Template = scenario == "owner-template";
        GameThread = scenario != "off-thread";
        sprite.Registered = scenario != "unregistered";
        DigimonVenomNXTFieldSprite::Configure(&sprite);
        return Loads || Errors || sprite.Writes ? fail("unsafe context loaded or mutated") : 0;
    } else {
        if (scenario == "fallback-missing" || scenario == "missing") Generated = nullptr;
        if (scenario == "fallback-opaque") Generated = &Opaque;
        if (scenario == "missing") Fallback = nullptr;
        if (scenario == "ownerless") sprite.Owner = nullptr;
        DigimonVenomNXTFieldSprite::Configure(&sprite);
        if (scenario == "missing") {
            if (Loads != 2 || Errors != 1 || sprite.Visible)
                return fail("missing materials did not hide and report the sprite");
            if (sprite.Materials[0] != &Opaque || sprite.Materials[1] != &Opaque)
                return fail("missing materials assigned an invalid override");
        } else {
            const int expectedLoads = scenario.find("fallback-") == 0 ? 2 : 1;
            if (Loads != expectedLoads || Errors || !sprite.Visible ||
                sprite.Materials[0] != &Masked || sprite.Materials[1] != &Masked)
                return fail("live sprite did not receive masked material in both slots");
        }
    }
    if (sprite.Collision != ECollisionEnabled::NoCollision || sprite.Shadow ||
        sprite.Decals || !sprite.CustomDepth || sprite.SortPriority != 0 || sprite.Stencil != 73)
        return fail("render defaults or authored stencil were lost");
    return 0;
}
'''


class PackagedStartupTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="digimon-startup-")
        cls.addClassCleanup(cls.temp.cleanup)
        source = (PRIVATE / "DigimonVenomNXTFieldSprite.cpp").read_text(encoding="utf-8")
        defaults = definition(source, "void DigimonVenomNXTFieldSprite::ConfigureDefaults(")
        configure = definition(source, "void DigimonVenomNXTFieldSprite::Configure(")
        cls.current = cls.compile_fixture("current", defaults + "\n" + configure)

        # Negative control reproduces the old loading boundary: Configure had
        # only a null check and actor constructors called it directly. Keep the
        # actual material-loading body so this checks behavior, not grep alone.
        material_body = configure[configure.index("    UMaterialInterface* Material ="):]
        legacy = ("void DigimonVenomNXTFieldSprite::Configure(UPaperFlipbookComponent* Sprite)\n"
                  "{\n    if (!Sprite) return;\n" + material_body)
        legacy += ("\nvoid DigimonVenomNXTFieldSprite::ConfigureDefaults(UPaperFlipbookComponent* Sprite)"
                   " { Configure(Sprite); }\n")
        cls.legacy = cls.compile_fixture("legacy", legacy)

    @classmethod
    def compile_fixture(cls, name, definitions):
        compiler = shlex.split(os.environ.get("CXX", "g++"))
        if not compiler:
            raise AssertionError("CXX must name a C++ compiler")
        cpp = Path(cls.temp.name) / (name + ".cpp")
        executable = Path(cls.temp.name) / name
        cpp.write_text(FAKES + definitions + SCENARIOS, encoding="utf-8")
        result = subprocess.run(compiler + ["-std=c++17", "-Wall", "-Wextra", "-Werror",
                                "-pedantic", str(cpp), "-o", str(executable)],
                                capture_output=True, text=True, timeout=30, check=False)
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)
        return executable

    def run_scenario(self, executable, scenario):
        return subprocess.run([str(executable), scenario], capture_output=True,
                              text=True, timeout=5, check=False)

    def test_actual_functions_preserve_asset_loading_boundary_and_rendering(self):
        for scenario in ("defaults", "null", "template", "owner-template", "off-thread",
                         "unregistered", "live", "ownerless", "fallback-missing",
                         "fallback-opaque", "missing"):
            with self.subTest(scenario=scenario):
                result = self.run_scenario(self.current, scenario)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_old_unguarded_constructor_loading_is_detected(self):
        for scenario in ("defaults", "template", "owner-template", "off-thread", "unregistered"):
            with self.subTest(scenario=scenario):
                result = self.run_scenario(self.legacy, scenario)
                self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                self.assertRegex(result.stderr, "requested an asset|unsafe context loaded")

    def test_native_actor_constructors_and_beginplay_use_correct_entrypoints(self):
        for name in ("DigimonVenomNXTTamerCharacter", "DigimonVenomNXTPartnerFollower",
                     "DigimonVenomNXTAIRivalAvatar", "DigimonVenomNXTFarmResident"):
            with self.subTest(actor=name):
                source = (PRIVATE / (name + ".cpp")).read_text(encoding="utf-8")
                constructor = definition(source, f"A{name}::A{name}(")
                begin_play = definition(source, f"void A{name}::BeginPlay(")
                self.assertEqual(constructor.count("DigimonVenomNXTFieldSprite::ConfigureDefaults("), 1)
                self.assertNotIn("DigimonVenomNXTFieldSprite::Configure(", constructor)
                self.assertNotRegex(constructor, r"\b(?:LoadObject|StaticLoadObject|LoadSynchronous)\b")
                self.assertIn("DigimonVenomNXTFieldSprite::Configure(", begin_play)
                self.assertLess(begin_play.index("Super::BeginPlay()"),
                                begin_play.index("DigimonVenomNXTFieldSprite::Configure("))
        header = (PUBLIC / "DigimonVenomNXTFarmResident.h").read_text(encoding="utf-8")
        actor_header = header[header.index("class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTFarmResident") :]
        self.assertRegex(actor_header, r"virtual\s+void\s+BeginPlay\s*\(\s*\)\s+override\s*;")


if __name__ == "__main__":
    unittest.main()
