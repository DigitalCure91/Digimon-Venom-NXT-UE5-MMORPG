#!/usr/bin/env python3
"""Compile the actual settings translation unit against the UE 5.8 void Read contract.

The API contract comes from the supplied UE 5.8/MSVC C2451 diagnostic. This test
does not execute Unreal's config parser or read any real hosting credentials.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTSettings.cpp"

API = r'''
#pragma once
#include <stdexcept>
#include <string>
#define TEXT(Value) Value
struct FString : std::string {
    using std::string::string;
    FString() = default;
    FString(const std::string& Value) : std::string(Value) {}
    bool IsEmpty() const { return empty(); }
};
using FSoftObjectPath = FString;
inline FString EnvironmentValue, FileValue, ReadPath;
inline bool FileExists = false, HasPasswordKey = false;
inline int ConfigReads = 0;
struct FPlatformMisc {
    static FString GetEnvironmentVariable(const char* Name) {
        if (std::string(Name) != "DIGIMONVENOMNXT_HOST_PASSWORD") throw std::runtime_error("Unexpected environment key");
        return EnvironmentValue;
    }
};
struct FConfigFile {
    bool HasValue = false;
    FString Value;
    // Deliberately void: using this API in an if-condition must fail compilation.
    void Read(const FString& Path) {
        ++ConfigReads; ReadPath = Path;
        HasValue = FileExists && HasPasswordKey;
        if (HasValue) Value = FileValue;
    }
    bool GetString(const char* Section, const char* Key, FString& Out) const {
        if (std::string(Section) != "Hosting" || std::string(Key) != "Password") throw std::runtime_error("Unexpected config key");
        if (HasValue) Out = Value;
        return HasValue;
    }
};
namespace FPaths {
inline FString ProjectSavedDir() { return "/project/Saved/"; }
inline FString Combine(const FString& First, const char* Second) { return First + Second; }
}
class UDigimonVenomNXTSettings {
public:
    FSoftObjectPath MainMenuMap, PublicWorldMap;
    FString AdminHostPassword;
    UDigimonVenomNXTSettings();
    FString ResolveAdminHostPassword() const;
};
'''

HARNESS = r'''
#include "UE58SettingsAPI.h"
#include <iostream>
int Checks = 0;
void Check(bool Result, const char* Reason) { ++Checks; if (!Result) throw std::runtime_error(Reason); }
int main() {
    UDigimonVenomNXTSettings Settings;
    Settings.AdminHostPassword = "editor-fixture";
    EnvironmentValue = "environment-fixture"; FileExists = HasPasswordKey = true; FileValue = "file-fixture";
    Check(Settings.ResolveAdminHostPassword() == EnvironmentValue, "Environment must override file and editor values");
    Check(ConfigReads == 0, "Environment resolution should not read the local file");
    EnvironmentValue.clear();
    Check(Settings.ResolveAdminHostPassword() == FileValue, "Host file must override editor setting");
    Check(ConfigReads == 1 && ReadPath == "/project/Saved/DigimonVenomNXT/Host.ini", "Read only the designated server-local file");
    FileExists = false;
    Check(Settings.ResolveAdminHostPassword() == Settings.AdminHostPassword, "Missing file falls back to editor setting");
    FileExists = true; HasPasswordKey = false;
    Check(Settings.ResolveAdminHostPassword() == Settings.AdminHostPassword, "Missing key falls back to editor setting");
    HasPasswordKey = true; FileValue.clear();
    Check(Settings.ResolveAdminHostPassword() == Settings.AdminHostPassword, "Empty file value falls back to editor setting");
    Settings.AdminHostPassword.clear();
    Check(Settings.ResolveAdminHostPassword().IsEmpty(), "No configured credential stays empty");
    FileValue = "replacement-file-fixture";
    Check(Settings.ResolveAdminHostPassword() == FileValue, "A later request reads the current file value");
    EnvironmentValue = "replacement-environment-fixture";
    Check(Settings.ResolveAdminHostPassword() == EnvironmentValue, "A later environment override takes precedence");
    Check(Settings.AdminHostPassword.IsEmpty(), "Resolution never writes credentials into default settings");
    Check(Settings.MainMenuMap == "/DigimonVenomNXT/Generated/Levels/MainMenu.MainMenu" &&
          Settings.PublicWorldMap == "/DigimonVenomNXT/Generated/Levels/PublicWorld.PublicWorld", "Startup asset paths remain valid");
    std::cout << Checks << " actual settings API and credential-precedence checks passed\n";
}
'''


class SettingsConfigAPI(unittest.TestCase):
    def build(self, directory: Path, source: Path):
        (directory / "UE58SettingsAPI.h").write_text(API)
        for name in ("DigimonVenomNXTSettings.h", "HAL/PlatformMisc.h", "Misc/ConfigCacheIni.h", "Misc/Paths.h"):
            header = directory / name
            header.parent.mkdir(parents=True, exist_ok=True)
            header.write_text('#include "UE58SettingsAPI.h"\n')
        harness = directory / "main.cpp"
        harness.write_text(HARNESS)
        executable = directory / "check.exe"
        result = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                                 "-I" + str(directory), str(source), str(harness), "-o", str(executable)],
                                capture_output=True, text=True, timeout=60)
        return result, executable

    def test_actual_settings_translation_unit_and_resolution(self):
        with tempfile.TemporaryDirectory(prefix="digimon-settings-api-") as temporary:
            compiled, executable = self.build(Path(temporary), SOURCE)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(executable)], capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout.strip())

    def test_negative_control_rejects_boolean_use_of_void_read(self):
        current = SOURCE.read_text()
        read_call = 'LocalHost.Read(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT/Host.ini")));'
        self.assertIn(read_call, current)
        mutated = current.replace(read_call, 'if (' + read_call[:-1] + ') {}', 1)
        with tempfile.TemporaryDirectory(prefix="digimon-settings-api-negative-") as temporary:
            directory = Path(temporary)
            source = directory / "BrokenSettings.cpp"
            source.write_text(mutated)
            compiled, _ = self.build(directory, source)
            self.assertNotEqual(compiled.returncode, 0, "Fixture failed to detect the original void-to-bool compile error")
            self.assertIn("void", compiled.stderr)


if __name__ == "__main__":
    unittest.main()
