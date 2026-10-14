#!/usr/bin/env python3
"""Compile the declaration scopes behind Log(8)'s three unity-build collisions.

This deliberately compiles extracted source snippets, not Unreal Engine code.
Run with CXX=g++ (the default) or a compatible C++ compiler. An optional
--baseline-root /path/to/old/DigimonVenomNXT uses untouched source for the negative
control; otherwise the historical global names are restored in the extracted
declarations. No fixture changes production source or compiler warning policy.
"""
import argparse
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import unittest


PLUGIN_ROOT = Path(__file__).resolve().parents[1]
PRIVATE = Path("Source/DigimonVenomNXTRuntime/Private")
GLOBAL_RENAMES = {
    "PlayerId": "SeasonPlayerId",
    "Names": "SeasonTamerNames",
    "Months": "SeasonMonthNames",
    "Days": "SeasonWeekdayNames",
}
BASELINE_ROOT = None


def season_declarations(root):
    source = (root / PRIVATE / "DigimonVenomNXTSeason.cpp").read_text(encoding="utf-8")
    declarations = re.findall(
        r"^\s*const\s+TCHAR\s*\*\s*\w+\s*(?:\[\s*\])?\s*=[^;]+;",
        source,
        re.MULTILINE,
    )
    if len(declarations) != 4:
        raise AssertionError("Expected the four Season.cpp namespace data declarations")
    return "\n".join(declaration.strip() for declaration in declarations)


def one_declaration(source, pattern, label):
    matches = re.findall(pattern, source)
    if len(matches) != 1:
        raise AssertionError(f"Expected one actual declaration for {label}; got {len(matches)}")
    return matches[0]


def local_declarations(root):
    widget = (root / PRIVATE / "DigimonVenomNXTSeasonWidget.cpp").read_text(encoding="utf-8")
    components = (root / PRIVATE / "DigimonVenomNXTUIComponents.cpp").read_text(encoding="utf-8")
    return (
        ("SeasonTabLabels", "Names", one_declaration(
            widget, r"const\s+TCHAR\s*\*\s*Names\s*\[\s*\]\s*=\s*\{[^;]+;",
            "SeasonWidget tab Names")),
        ("SeasonMatchWeekdays", "Days", one_declaration(
            widget, r"const\s+TCHAR\s*\*\s*Days\s*\[\s*\]\s*=\s*\{[^;]+;",
            "SeasonWidget weekday Days")),
        ("DurationWholeDays", "Days", one_declaration(
            components, r"const\s+int64\s+Days\s*=\s*Seconds\s*/\s*86400\s*;",
            "UIComponents duration Days")),
    )


def unity_fixture(globals_source, locals_source):
    # GCC does not warn for a global found only through the anonymous namespace's
    # implicit using-directive; MSVC C4459 does. Keep the wrapper functions in
    # that namespace so GCC checks the same global/local identifier collisions.
    code = [
        "using TCHAR = char;",
        "using int64 = long long;",
        "#define TEXT(Value) Value",
        "namespace {",
        globals_source,
    ]
    for function_name, variable_name, declaration in locals_source:
        code.extend((
            f"void {function_name}() {{",
            "    const int64 Seconds = 90061;",
            "    (void)Seconds;",
            declaration,
            f"    (void){variable_name};",
            "}",
        ))
    code.append("}")
    return "\n".join(code) + "\n"


class UnityDeclarationCompileTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compiler = shlex.split(os.environ.get("CXX", "g++"))
        if not cls.compiler:
            raise AssertionError("CXX must name a C++ compiler")
        cls.current_globals = season_declarations(PLUGIN_ROOT)
        cls.locals_source = local_declarations(PLUGIN_ROOT)
        if BASELINE_ROOT is not None:
            cls.original_globals = season_declarations(BASELINE_ROOT)
        else:
            cls.original_globals = cls.current_globals
            for old_name, new_name in GLOBAL_RENAMES.items():
                cls.original_globals = re.sub(
                    rf"\b{re.escape(new_name)}\b", old_name, cls.original_globals)

    def compile_fixture(self, globals_source, locals_source):
        with tempfile.TemporaryDirectory(prefix="digimon-unity-shadow-") as directory:
            source = Path(directory) / "unity_declarations.cpp"
            source.write_text(unity_fixture(globals_source, locals_source), encoding="utf-8")
            return subprocess.run(
                self.compiler + ["-std=c++17", "-Wshadow", "-Werror=shadow", "-fsyntax-only", str(source)],
                capture_output=True, text=True, timeout=30,
                env={**os.environ, "LC_ALL": "C"}, check=False,
            )

    def test_current_source_declarations_compile_together(self):
        result = self.compile_fixture(self.current_globals, self.locals_source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_each_reported_original_collision_is_rejected(self):
        for case in self.locals_source:
            with self.subTest(source_case=case[0]):
                result = self.compile_fixture(self.original_globals, (case,))
                self.assertNotEqual(result.returncode, 0, "Original shadowing unexpectedly compiled")
                self.assertIn("shadow", result.stderr.lower(), result.stderr)
                self.assertIn(case[1], result.stderr, result.stderr)

    def test_season_constant_values_are_preserved(self):
        if BASELINE_ROOT is None:
            self.skipTest("An untouched --baseline-root is required to compare constant values")
        restored = self.current_globals
        for old_name, new_name in GLOBAL_RENAMES.items():
            restored = re.sub(rf"\b{re.escape(new_name)}\b", old_name, restored)
        self.assertEqual(restored, self.original_globals)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("--baseline-root", type=Path)
    options, unittest_args = parser.parse_known_args()
    BASELINE_ROOT = options.baseline_root.resolve() if options.baseline_root else None
    unittest.main(argv=[__file__, *unittest_args])
