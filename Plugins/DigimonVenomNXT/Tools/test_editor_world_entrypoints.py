#!/usr/bin/env python3
"""Exercise the actual open-world callback's save/cancel/load boundary.

Small FileHelpers stand-ins verify ordering and failure handling, not Unreal
level loading. The separate Unreal startup validator inspects generated worlds.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'Source/DigimonVenomNXTEditor/Private/DigimonVenomNXTEditor.cpp'

FAKES = r'''
#include <string>
#include <stdexcept>
#include <iostream>
#define TEXT(x) x
struct FString : std::string {
    using std::string::string;
    FString(const std::string& value) : std::string(value) {}
    FString() = default;
    bool EndsWith(const char* suffix) const {
        std::string s(suffix); return size() >= s.size() && compare(size()-s.size(),s.size(),s)==0;
    }
};
struct Editor { void* PlayWorld = nullptr; } Instance;
Editor* GEditor = &Instance;
bool Exists = true, CanSave = true, CanLoad = true;
int Saves = 0, Loads = 0;
std::string LoadedFile;
struct FPackageName {
    static bool DoesPackageExist(const FString&) { return Exists; }
    static FString GetMapPackageExtension() { return ".umap"; }
    static FString LongPackageNameToFilename(const FString& name, const FString& ext) { return name+ext; }
};
struct FEditorFileUtils {
    static bool SaveDirtyPackages(bool prompt, bool maps, bool content, bool fast, bool notify, bool decline) {
        if (!prompt || !maps || content || fast || notify || decline) throw std::runtime_error("unsafe save policy");
        ++Saves; return CanSave;
    }
    static bool LoadMap(const FString& path, bool asTemplate, bool progress) {
        if (asTemplate || !progress || Saves != 1) throw std::runtime_error("incorrect map load ordering");
        ++Loads; LoadedFile = path; return CanLoad;
    }
};
int Focused = 0;
namespace DigimonVenomNXTEditorMapPreview { void FocusFirstMap() { ++Focused; } }
'''

SCENARIOS = r'''
int main(int argc, char** argv) {
    std::string scenario = argc > 1 ? argv[1] : "";
    FString report;
    if (scenario == "no_editor") GEditor = nullptr;
    if (scenario == "pie") Instance.PlayWorld = &Instance;
    if (scenario == "missing") Exists = false;
    if (scenario == "cancel") CanSave = false;
    if (scenario == "load_failure") CanLoad = false;
    const FString path = scenario == "public" ? "/DigimonVenomNXT/Generated/Levels/PublicWorld" : "/DigimonVenomNXT/Generated/Levels/MainMenu";
    bool success = OpenGeneratedWorld(path, report);
    bool expected = scenario == "menu" || scenario == "public";
    if (success != expected || report.empty()) return 1;
    if ((scenario == "no_editor" || scenario == "pie" || scenario == "missing") && (Saves || Loads)) return 2;
    if (scenario == "cancel" && (Saves != 1 || Loads)) return 3;
    if ((expected || scenario == "load_failure") && (Loads != 1 || LoadedFile != path+".umap")) return 4;
    if (expected && report.find("Play") == std::string::npos) return 5;
    if (Focused != (scenario == "public" ? 1 : 0)) return 6;
    return 0;
}
'''


class EditorWorldEntryPoints(unittest.TestCase):
    def test_actual_callback_handles_missing_world_cancel_and_load_failure(self):
        source = SOURCE.read_text(encoding='utf-8')
        start = source.index('bool OpenGeneratedWorld(')
        opening = source.index('{', start)
        depth, end = 1, opening + 1
        while depth:
            depth += (source[end] == '{') - (source[end] == '}')
            end += 1
        with tempfile.TemporaryDirectory(prefix='digimon-world-entry-') as temporary:
            directory = Path(temporary)
            cpp, exe = directory / 'entry.cpp', directory / 'entry'
            cpp.write_text(FAKES + source[start:end] + SCENARIOS, encoding='utf-8')
            compiled = subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Werror', '-pedantic', str(cpp), '-o', str(exe)], capture_output=True, text=True, timeout=30)
            self.assertEqual(compiled.returncode, 0, compiled.stderr)
            for scenario in ('no_editor', 'pie', 'missing', 'cancel', 'load_failure', 'menu', 'public'):
                with self.subTest(scenario=scenario):
                    result = subprocess.run([str(exe), scenario], capture_output=True, text=True, timeout=5)
                    self.assertEqual(result.returncode, 0, result.stderr)

    def test_menu_exposes_both_levels_and_non_destructive_complete_import(self):
        source = SOURCE.read_text(encoding='utf-8')
        for name in ('MainMenu', 'PublicWorld'):
            self.assertIn(f'OpenGeneratedWorld(TEXT("/DigimonVenomNXT/Generated/Levels/{name}")', source)
        self.assertIn('::BuildCompleteGameContent(false, R)', source)
        self.assertIn('::ImportAllBundledAssets(false, R)', source)
        self.assertIn('::PrepareGameWorlds(R)', source)


if __name__ == '__main__':
    unittest.main()
