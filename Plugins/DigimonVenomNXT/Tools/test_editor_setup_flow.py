#!/usr/bin/env python3
"""Compile the live full-setup orchestration against stage-failure substitutes.

This tests actual control flow, including the asset-only import regression. It
does not substitute for loading/saving UWorld assets in an Unreal editor.
"""
import os
import re
import shlex
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LIBRARY = ROOT / 'Source/DigimonVenomNXTEditor/Private/DigimonVenomNXTEditorLibrary.cpp'


def function(source, declaration):
    start = source.index(declaration + '(')
    masked = re.sub(r'"(?:\\.|[^"\\])*"|//[^\n]*|/\*.*?\*/',
                    lambda match: ' ' * len(match[0]), source, flags=re.DOTALL)
    opening = masked.index('{', start)
    depth = 0
    for pos in range(opening, len(masked)):
        if masked[pos] == '{':
            depth += 1
        elif masked[pos] == '}':
            depth -= 1
            if depth == 0:
                return source[start:pos + 1]
    raise AssertionError('Unbalanced function: ' + declaration)


def method(source, name):
    return function(source, 'bool UDigimonVenomNXTEditorLibrary::' + name)


STUBS = r'''
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#define TEXT(x) x
#define UE_LOG(...) ((void)0)
struct FString {
    std::string S;
    FString()=default;
    FString(const char* Value):S(Value) {}
    FString(std::string Value):S(std::move(Value)) {}
    void Reset() { S.clear(); }
    FString& operator+=(const FString& Other) { S+=Other.S;return *this; }
    friend FString operator+(const FString& A,const FString& B) { return A.S+B.S; }
};
std::vector<std::string> Calls;
std::string Failure;
bool WorldsSaved=false,Certified=false,RequestedReplace=false;
void Check(bool Test,const char* Message) { if(!Test)throw std::runtime_error(Message); }
bool Stage(const char* Name,FString& Report) {
    Calls.emplace_back(Name);Report=Name;
    if(Failure==Name || (Failure=="cancel" && std::string(Name)=="import")) {
        Report=Failure=="cancel"?"Cancelled during asset import":"Injected stage failure";
        return false;
    }
    return true;
}
namespace DigimonVenomNXTEditorInternal {
    enum class EImportScope { All };
    bool PrepareWorldsInternal(bool Refresh,FString& Report) {
        Check(!Refresh,"Full import must not certify old assets during bootstrap");
        bool Result=Stage("bootstrap",Report);WorldsSaved=Result;return Result;
    }
    bool ImportManifest(EImportScope,bool Replace,FString& Report) {
        Check(Replace==RequestedReplace,"Replace/resume intent was lost");
        return Stage("import",Report);
    }
    bool WriteCompleteReceipt(FString& Report) {
        bool Result=Stage("receipt",Report);Certified=Result;return Result;
    }
}
struct UDigimonVenomNXTEditorLibrary {
    static bool BuildCompleteGameContent(bool,FString&);
    static bool ImportCoreAssets(bool,FString&);
    static bool ImportAllBundledAssets(bool,FString&);
    static bool BuildStarterLevels(bool Replace,FString& Report) {
        Check(!Replace,"Completion must preserve unrelated authored level content");
        return Stage("world-refresh",Report);
    }
    static bool ValidateGameWorlds(FString& Report) { return Stage("validate",Report); }
};
'''

CASES = r'''
int main() {
    try {
        const std::vector<std::string> Expected={"bootstrap","import","world-refresh","validate","receipt"};
        int Cases=0;
        for(bool Replace:{false,true})for(int Entry=0;Entry<3;++Entry)
            for(const char* Fail:{"","bootstrap","import","cancel","world-refresh","validate","receipt"}) {
                Calls.clear();Failure=Fail;WorldsSaved=false;Certified=false;RequestedReplace=Replace;
                FString Report;
                const bool Result=Entry==0?UDigimonVenomNXTEditorLibrary::BuildCompleteGameContent(Replace,Report):
                    Entry==1?UDigimonVenomNXTEditorLibrary::ImportCoreAssets(Replace,Report):
                    UDigimonVenomNXTEditorLibrary::ImportAllBundledAssets(Replace,Report);
                Check(Result==Failure.empty(),"Setup returned success for an incomplete stage");
                const std::string FailedStage=Failure=="cancel"?"import":Failure;
                std::vector<std::string> ExpectedCalls;
                for(const auto& Name:Expected) {
                    ExpectedCalls.push_back(Name);
                    if(Name==FailedStage)break;
                }
                Check(Calls==ExpectedCalls,"Wrong setup stage order: worlds must precede import and receipt must be last");
                Check(Certified==Failure.empty(),"Completion receipt state disagrees with setup success");
                Check(WorldsSaved==(Failure!="bootstrap"),"Import failure discarded bootstrap worlds");
                Check(!Report.S.empty(),"Setup did not explain its result");
                if(Failure=="import" || Failure=="cancel") {
                    Check(Report.S.find("INCOMPLETE")!=std::string::npos,"Partial import was not identified");
                    Check(Report.S.find("MainMenu and PublicWorld have been saved")!=std::string::npos,"Partial import lost recovery guidance");
                }
                ++Cases;
            }
        std::cout<<Cases<<" production setup paths passed: all aliases, resume/replace, early worlds, each failure, cancellation and receipt gating\n";
    }catch(const std::exception& Error){std::cerr<<Error.what()<<'\n';return 1;}
}
'''


class EditorSetupFlowTests(unittest.TestCase):
    def production(self):
        source = LIBRARY.read_text(encoding='utf-8')
        return '\n'.join(method(source, name) for name in
                         ('ImportCoreAssets', 'ImportAllBundledAssets', 'BuildCompleteGameContent'))

    def run_cpp(self, production):
        with tempfile.TemporaryDirectory(prefix='dvnxt-setup-flow-') as directory:
            root = Path(directory)
            source = root / 'setup.cpp'
            binary = root / ('setup.exe' if os.name == 'nt' else 'setup')
            source.write_text(STUBS + production + CASES, encoding='utf-8')
            compiler = shlex.split(os.environ.get('CXX', 'g++'))
            compiled = subprocess.run(compiler + ['-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
                                                  str(source), '-o', str(binary)], capture_output=True, text=True, timeout=40)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            return subprocess.run([str(binary)], capture_output=True, text=True, timeout=15)

    def test_live_setup_stages_and_failure_boundaries(self):
        result = self.run_cpp(self.production())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_original_asset_only_import_regression_is_detected(self):
        production = self.production()
        original = method(production, 'ImportCoreAssets')
        mutant = 'bool UDigimonVenomNXTEditorLibrary::ImportCoreAssets(bool R,FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::All,R,Out); }'
        result = self.run_cpp(production.replace(original, mutant, 1))
        self.assertNotEqual(result.returncode, 0, 'The original asset-only import regression escaped detection')
        self.assertIn('Wrong setup stage order', result.stderr)

    def test_complete_setup_does_not_repair_the_unrelated_open_level(self):
        source = LIBRARY.read_text(encoding='utf-8')
        configure = method(source, 'ConfigureProjectForDigimonVenomNXT')
        defaults = function(source, 'static bool SaveRenderDefaults')
        optional_repair = method(source, 'ConfigureLevelCustomDepth')
        self.assertIn('SaveRenderDefaults(DepthReport)', configure)
        for prohibited in ('ConfigureLevelCustomDepth(', 'PrepareWorldMaterials(',
                           'ConfigureWorld(', 'GetEditorWorldContext('):
            self.assertNotIn(prohibited, configure + defaults,
                             'Normal project setup must not mutate the unrelated open world')
        self.assertIn('PrepareWorldMaterials(', optional_repair,
                      'Explicit current-level repair must remain available')
        self.assertIn('SavedEngine.GetInt(', defaults,
                      'Render defaults must be verified from the saved configuration')


if __name__ == '__main__':
    unittest.main()
