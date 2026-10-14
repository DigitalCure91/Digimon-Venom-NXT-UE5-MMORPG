#!/usr/bin/env python3
"""Regression fixtures for the twelve errors in Log(20261009-171649).txt.

Source guards recognize the exact reported C4459/C2248 patterns. The compiler
fixtures use actual palette/role declarations with small native C++ stand-ins;
they do not compile Unreal code, execute UHT, or claim MSVC validation.
"""
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile
import unittest
from validate_compile_surface import (
    external_battle_class_accesses, hud_panel_shadows, mask_cpp, social_policy_imports,
)

ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"


class ReportedCommunitySourceGuards(unittest.TestCase):
    def masked(self, source):
        code, failures = mask_cpp(source)
        self.assertEqual(failures, [])
        return code

    def test_all_three_social_import_forms_are_rejected(self):
        for source in ("namespace { using namespace DigimonVenomNXTSocialCore; }",
                       "using DigimonVenomNXTSocialCore::Member;", "using DigimonVenomNXTSocialCore::Leader;"):
            with self.subTest(source=source):
                self.assertEqual(len(social_policy_imports(self.masked(source))), 1)

    def test_qualified_social_calls_and_comment_examples_are_allowed(self):
        source = '''
        // using namespace DigimonVenomNXTSocialCore;
        const char* Example="using DigimonVenomNXTSocialCore::Leader;";
        void F() { int Member=1; DigimonVenomNXTSocialCore::CanInvite(Member); }
        '''
        self.assertEqual(social_policy_imports(self.masked(source)), [])

    def test_reported_hud_pointer_and_related_lookup_declarations_are_rejected(self):
        source = '''void UDigimonVenomNXTGameHUDWidget::Build() {
            UDigimonVenomNXTCommunityWidget* Panel = Create();
            if (const TObjectPtr<UDigimonVenomNXTCommunityWidget>* Panel = Find()) Use(Panel);
        }'''
        self.assertEqual(len(hud_panel_shadows(self.masked(source))), 2)

    def test_palette_uses_and_descriptive_hud_locals_are_allowed(self):
        source = '''namespace DigimonHUDUI { static const FLinearColor Panel(0,0,0,1); }
        void UDigimonVenomNXTGameHUDWidget::Build() {
            UDigimonVenomNXTCommunityWidget* CommunityPage = Create(); SetColor(Panel);
            // UDigimonVenomNXTCommunityWidget* Panel = Create();
        }'''
        self.assertEqual(hud_panel_shadows(self.masked(source)), [])

    def test_each_reported_protected_read_is_rejected(self):
        source = "Mode && Mode->BattleActorClass ? Mode->BattleActorClass.Get() : Fallback();"
        self.assertEqual(len(external_battle_class_accesses(self.masked(source))), 2)

    def test_read_only_accessor_and_literals_are_allowed(self):
        source = '''auto* Class = Mode ? Mode->GetBattleActorClass() : Fallback();
        // Mode->BattleActorClass.Get();
        const char* Note="Mode.BattleActorClass";'''
        self.assertEqual(external_battle_class_accesses(self.masked(source)), [])

    def test_current_production_files_have_no_reported_regressions(self):
        social = (PRIVATE / "DigimonVenomNXTSocialSubsystem.cpp").read_text(encoding="utf-8")
        hud = (PRIVATE / "DigimonVenomNXTGameHUDWidget.cpp").read_text(encoding="utf-8")
        unranked = (PRIVATE / "DigimonVenomNXTUnrankedComponent.cpp").read_text(encoding="utf-8")
        self.assertEqual(social_policy_imports(self.masked(social)), [])
        self.assertEqual(hud_panel_shadows(self.masked(hud)), [])
        self.assertEqual(external_battle_class_accesses(self.masked(unranked)), [])
        self.assertEqual(unranked.count("Mode->GetBattleActorClass()"), 2)


class CommunityDeclarationCompilerTests(unittest.TestCase):
    def compile(self, program):
        with tempfile.TemporaryDirectory(prefix="digimon-community-compile-") as directory:
            source = Path(directory) / "declarations.cpp"
            source.write_text(program, encoding="utf-8")
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wshadow", "-Werror=shadow", "-fsyntax-only", str(source)]
            return subprocess.run(command, capture_output=True, text=True, timeout=30)

    def hud_fixture(self):
        source = (PRIVATE / "DigimonVenomNXTGameHUDWidget.cpp").read_text(encoding="utf-8")
        palette = re.search(r"static const FLinearColor Panel\([^;]+;", source).group(0)
        local = re.search(r"UDigimonVenomNXTCommunityWidget\*\s+(\w+)\s*=\s*CreateWidget<UDigimonVenomNXTCommunityWidget>", source)
        self.assertIsNotNone(local)
        variable = local.group(1)
        # GCC does not warn through a using-directive as MSVC C4459 does.
        # Replay the real declarations in the palette namespace so GCC sees
        # the same global-versus-local name collision under -Werror=shadow.
        program = ("struct FLinearColor {FLinearColor(float,float,float,float){}};\n"
                   "struct UDigimonVenomNXTCommunityWidget {};\nnamespace DigimonHUDUI {\n" + palette +
                   "\nvoid Build() { UDigimonVenomNXTCommunityWidget* " + variable + " = nullptr; (void)" + variable + "; }\n}\n")
        return program, variable

    def test_actual_hud_declarations_compile_without_shadow(self):
        program, _ = self.hud_fixture()
        result = self.compile(program)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_original_panel_shadow_is_rejected_by_compiler(self):
        program, variable = self.hud_fixture()
        result = self.compile(re.sub(r"\b" + re.escape(variable) + r"\b", "Panel", program))
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("shadow", result.stderr)
        self.assertIn("Panel", result.stderr)

    def test_actual_role_constants_keep_locals_safe_when_qualified(self):
        core = (PUBLIC / "DigimonVenomNXTSocialCore.h").read_text(encoding="utf-8").replace("#pragma once", "")
        result = self.compile(core + "\nvoid Probe(){int Member=1,Leader=3; (void)DigimonVenomNXTSocialCore::CanKick(Leader,Member,false);}\n")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_exposing_actual_role_constants_detects_both_collisions(self):
        core = (PUBLIC / "DigimonVenomNXTSocialCore.h").read_text(encoding="utf-8").replace("#pragma once", "")
        for name in ("Member", "Leader"):
            with self.subTest(name=name):
                # Direct using-declaration makes the symbol visible to GCC's
                # shadow diagnostic; the source guard separately tests the
                # exact anonymous-namespace using-directive reported by MSVC.
                result = self.compile(core + "\nusing DigimonVenomNXTSocialCore::" + name + ";\nvoid Probe(){int " + name + "=0; (void)" + name + ";}\n")
                self.assertNotEqual(result.returncode, 0)
                self.assertIn("shadow", result.stderr)
                self.assertIn(name, result.stderr)


if __name__ == "__main__":
    unittest.main()
