#!/usr/bin/env python3
"""Exercise the live render-default persistence helper with separate disk/cache APIs.

The extracted production C++ executes against a small file-backed config double.
It models the reported UE 5.8 commandlet failure: updating a GConfig cache entry
and flushing a standalone DefaultEngine filename need not write that source file.
This is a control-flow/API regression test, not Unreal's parser or config cache.
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


def production_function():
    source = LIBRARY.read_text(encoding='utf-8')
    start = source.index('static bool SaveRenderDefaults(')
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
    raise AssertionError('Unbalanced SaveRenderDefaults function')


API = r'''
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#define TEXT(Value) Value
using int32=int;
using TCHAR=char;
struct FString {
    std::string S;
    FString()=default;
    FString(const char* Value):S(Value){}
    FString(std::string Value):S(std::move(Value)){}
    const char* operator*() const { return S.c_str(); }
    template<class... Args>static FString Printf(const char* Format,Args... Values) {
        const int Size=std::snprintf(nullptr,0,Format,Values...);
        std::vector<char> Buffer(static_cast<std::size_t>(Size)+1);
        std::snprintf(Buffer.data(),Buffer.size(),Format,Values...);
        return Buffer.data();
    }
};
using Fields=std::map<std::string,std::map<std::string,std::string>>;
std::filesystem::path ConfigRoot;
int Checks=0,PropertyWrites=0,ConfigReads=0,CacheFlushes=0,RendererEnables=0;
bool RejectWrite=false,SkipWrite=false,CorruptWrite=false,RejectReadback=false;
bool ReadOnly=false;
bool GameWriteSucceeds=true;
void Check(bool Test,const char* Message) {
    ++Checks;
    if(!Test)throw std::runtime_error(Message);
}
std::string ReadBytes(const std::string& Path) {
    std::ifstream File(Path,std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(File),{});
}
void WriteBytes(const std::string& Path,const std::string& Value) {
    std::filesystem::create_directories(std::filesystem::path(Path).parent_path());
    std::ofstream File(Path,std::ios::binary|std::ios::trunc);
    File<<Value;
    if(!File)throw std::runtime_error("Fixture disk write failed");
}
Fields Parse(const std::string& Text) {
    Fields Result;std::string Section,Line;std::istringstream Lines(Text);
    while(std::getline(Lines,Line)) {
        if(!Line.empty() && Line.back()=='\r')Line.pop_back();
        if(Line.empty() || Line.front()==';')continue;
        if(Line.front()=='[' && Line.back()==']') { Section=Line.substr(1,Line.size()-2);continue; }
        const auto Equal=Line.find('=');
        if(Equal!=std::string::npos)Result[Section][Line.substr(0,Equal)]=Line.substr(Equal+1);
    }
    return Result;
}
// This deliberately narrow writer keeps unrelated lines byte-for-byte. It models
// the production API's single-property boundary, not Unreal INI parsing rules.
void WriteOneProperty(const std::string& Path,const std::string& Section,
                      const std::string& Key,const std::string& Value) {
    std::istringstream Input(ReadBytes(Path));std::vector<std::string> Lines;
    std::string Line;bool InSection=false,FoundSection=false,Written=false;
    while(std::getline(Input,Line)) {
        if(!Line.empty() && Line.front()=='[' && Line.back()==']') {
            if(InSection && !Written) { Lines.push_back(Key+"="+Value);Written=true; }
            InSection=Line=="["+Section+"]";
            FoundSection|=InSection;
        }
        if(InSection && Line.rfind(Key+"=",0)==0) {
            if(!Written)Lines.push_back(Key+"="+Value);
            Written=true;
        }else Lines.push_back(Line);
    }
    if(!Written) {
        if(!FoundSection)Lines.push_back("["+Section+"]");
        Lines.push_back(Key+"="+Value);
    }
    std::string Output;for(const auto& Entry:Lines)Output+=Entry+"\n";
    WriteBytes(Path,Output);
}
namespace FPaths {
FString ProjectConfigDir() { return ConfigRoot.string()+"/"; }
FString Combine(const FString& Root,const char* Leaf) { return Root.S+Leaf; }
FString ConvertRelativePathToFull(const FString& Path) { return std::filesystem::absolute(Path.S).string(); }
void NormalizeFilename(FString& Path) { Path.S=std::filesystem::path(Path.S).lexically_normal().generic_string(); }
bool FileExists(const FString& Path) { return std::filesystem::is_regular_file(Path.S); }
}
struct IFileManager {
    static IFileManager& Get() { static IFileManager Files;return Files; }
    bool IsReadOnly(const char*) const { return ReadOnly; }
};
struct FConfigFile {
    Fields Values;
    void Reset() { Values.clear(); }
    // UE 5.8 Read is void; putting it in an if-condition must not compile.
    void Read(const FString& Path) {
        ++ConfigReads;
        Values=RejectReadback?Fields{}:Parse(ReadBytes(Path.S));
    }
    void SetString(const char* Section,const char* Key,const char* Value) { Values[Section][Key]=Value; }
    void SetInt(const char* Section,const char* Key,int Value) { Values[Section][Key]=std::to_string(Value); }
    bool UpdateSinglePropertyInSection(const char* Path,const char* Key,const char* Section) {
        ++PropertyWrites;
        if(RejectWrite || ReadOnly)return false;
        const auto SectionIt=Values.find(Section);
        if(SectionIt==Values.end() || !SectionIt->second.count(Key))return false;
        if(!SkipWrite)WriteOneProperty(Path,Section,Key,CorruptWrite?"2":SectionIt->second.at(Key));
        return true;
    }
    bool GetInt(const char* Section,const char* Key,int& Value) const {
        auto FoundSection=Values.find(Section);
        if(FoundSection==Values.end())return false;
        auto FoundValue=FoundSection->second.find(Key);
        if(FoundValue==FoundSection->second.end())return false;
        try { Value=std::stoi(FoundValue->second);return true; }catch(...) { return false; }
    }
};
struct FConfigCacheIni {
    std::map<std::string,Fields> Cache;
    void SetInt(const char* Section,const char* Key,int Value,const FString& Path) {
        Cache[Path.S][Section][Key]=std::to_string(Value);
    }
    // Intentional separation: a source filename is not a writable generated
    // branch in this failure model. Readback must use the actual disk file.
    void Flush(bool,const FString&) { ++CacheFlushes; }
};
FConfigCacheIni Cache;
FConfigCacheIni* GConfig=&Cache;
FString GEngineIni="/generated/Engine.ini";
struct UDigimonVenomNXTSettings {
    bool bRenderCustomDepthByDefault=false;
    int SaveCalls=0,DefaultCalls=0;
    FString GetDefaultConfigFilename() const { return (ConfigRoot/"DefaultGame.ini").string(); }
    void SaveConfig() { ++SaveCalls; }
    bool TryUpdateDefaultConfigFile(const FString&,bool) {
        ++DefaultCalls;
        if(!GameWriteSucceeds)return false;
        WriteOneProperty((ConfigRoot/"DefaultGame.ini").string(),
            "/Script/DigimonVenomNXTRuntime.DigimonVenomNXTSettings",
            "bRenderCustomDepthByDefault",bRenderCustomDepthByDefault?"True":"False");
        return true;
    }
} Settings;
template<class T>T* GetMutableDefault() { return &Settings; }
namespace DigimonVenomNXTCustomDepth { void EnsureRendererEnabled() { ++RendererEnables; } }
const std::string EngineSeed=
    "; unrelated project configuration must survive\n"
    "[/Script/Engine.RendererSettings]\n"
    "r.CustomDepth=1\n"
    "r.DefaultFeature.MotionBlur=False\n"
    "r.Shadow.Virtual.Enable=1\n"
    "[/Script/EngineSettings.GameMapsSettings]\n"
    "GameDefaultMap=/Game/KeepThisMap\n"
    "+EditorTemplateMapOverrides=First\n"
    "+EditorTemplateMapOverrides=Second\n";
const std::string GameSeed=
    "[/Script/UnrealEd.ProjectPackagingSettings]\n"
    "+MapsToCook=/Game/KeepMapA\n"
    "+MapsToCook=/Game/KeepMapB\n"
    "[/Script/DigimonVenomNXTRuntime.DigimonVenomNXTSettings]\n"
    "ServerDisplayName=Fixture server\n"
    "bRenderCustomDepthByDefault=False\n";
void Reset() {
    std::filesystem::remove_all(ConfigRoot);
    WriteBytes((ConfigRoot/"DefaultEngine.ini").string(),EngineSeed);
    WriteBytes((ConfigRoot/"DefaultGame.ini").string(),GameSeed);
    Cache=FConfigCacheIni();GConfig=&Cache;Settings=UDigimonVenomNXTSettings();
    PropertyWrites=ConfigReads=CacheFlushes=RendererEnables=0;
    RejectWrite=SkipWrite=CorruptWrite=RejectReadback=ReadOnly=false;GameWriteSucceeds=true;
}
std::string EnginePath() { return (ConfigRoot/"DefaultEngine.ini").string(); }
void CheckFailure(const FString& Report) {
    Check(!Report.S.empty(),"Persistence failure must produce a diagnostic");
    Check(RendererEnables==0,"Failed persistence must not report renderer setup complete");
}
'''

CASES = r'''
int main(int argc,char** argv) {
    try {
        Check(argc==2,"Expected fixture directory");ConfigRoot=argv[1];
        FString Report;
        Reset();
        Check(SaveRenderDefaults(Report),"Expected successful disk persistence despite an unwritable cache branch");
        std::string ExpectedEngine=EngineSeed;
        ExpectedEngine.replace(ExpectedEngine.find("r.CustomDepth=1"),15,"r.CustomDepth=3");
        Check(ReadBytes(EnginePath())==ExpectedEngine,"Render edit changed unrelated DefaultEngine settings");
        Check(Cache.Cache[GEngineIni.S]["/Script/Engine.RendererSettings"]["r.CustomDepth"]=="3",
            "Successful disk commit must update the effective engine cache");
        Check(RendererEnables==1 && Settings.bRenderCustomDepthByDefault,
            "Successful save did not activate Digimon render defaults");
        std::string ExpectedGame=GameSeed;
        const std::string OldGameValue="bRenderCustomDepthByDefault=False";
        ExpectedGame.replace(ExpectedGame.find(OldGameValue),OldGameValue.size(),"bRenderCustomDepthByDefault=True");
        Check(ReadBytes((ConfigRoot/"DefaultGame.ini").string())==ExpectedGame,
            "DefaultGame update changed unrelated packaging settings");
        Check(!Report.S.empty(),"Successful persistence must explain its result");
        const int WrittenBeforeRepeat=PropertyWrites;
        Check(SaveRenderDefaults(Report),"Repeated setup must succeed");
        Check(PropertyWrites==WrittenBeforeRepeat,"Already-correct DefaultEngine must not be rewritten");
        Check(ReadBytes(EnginePath())==ExpectedEngine,"Repeated setup changed DefaultEngine contents");
        Check(ReadBytes((ConfigRoot/"DefaultGame.ini").string())==ExpectedGame,
            "Repeated setup duplicated or changed DefaultGame settings");
        ReadOnly=true;
        Check(SaveRenderDefaults(Report),"Already-correct read-only DefaultEngine must not block setup");
        Check(PropertyWrites==WrittenBeforeRepeat && ReadBytes(EnginePath())==ExpectedEngine,
            "Read-only already-correct file must remain untouched");

        Reset();Cache.SetInt("/Script/Engine.RendererSettings","r.CustomDepth",3,FString(EnginePath()));
        Check(SaveRenderDefaults(Report),"A pre-existing cache value must not hide stale disk defaults");
        Check(ReadBytes(EnginePath())==ExpectedEngine,"Stale disk value survived because the cache already held 3");

        Reset();std::string WithoutKey=EngineSeed;WithoutKey.erase(WithoutKey.find("r.CustomDepth=1\n"),16);
        WriteBytes(EnginePath(),WithoutKey);
        Check(SaveRenderDefaults(Report),"Missing renderer property must be added");
        const auto Added=Parse(ReadBytes(EnginePath()));
        Check(Added.at("/Script/Engine.RendererSettings").at("r.CustomDepth")=="3","New depth property was not saved");
        Check(Added.at("/Script/EngineSettings.GameMapsSettings").at("GameDefaultMap")=="/Game/KeepThisMap",
            "Adding the renderer property discarded another section");

        Reset();std::filesystem::remove(EnginePath());
        Check(SaveRenderDefaults(Report),"Missing DefaultEngine should be created by the property writer");
        Check(Parse(ReadBytes(EnginePath())).at("/Script/Engine.RendererSettings").at("r.CustomDepth")=="3",
            "New DefaultEngine was not verified from disk");

        Reset();GConfig=nullptr;
        Check(!SaveRenderDefaults(Report),"Null global config must fail without crashing");CheckFailure(Report);
        Check(ReadBytes(EnginePath())==EngineSeed && PropertyWrites==0 && Settings.DefaultCalls==0,
            "Null global config must not modify files");

        Reset();RejectWrite=true;
        Check(!SaveRenderDefaults(Report),"A rejected disk write must fail setup");CheckFailure(Report);
        Check(Report.S.find(EnginePath())!=std::string::npos && Report.S.find("read-only: no")!=std::string::npos,
            "A writer failure must identify its file without incorrectly diagnosing permissions");
        Check(ReadBytes(EnginePath())==EngineSeed,"Rejected write damaged existing defaults");
        Check(Settings.DefaultCalls==0,"Failed engine persistence must stop before writing Digimon defaults");

        Reset();ReadOnly=true;
        Check(!SaveRenderDefaults(Report),"Incorrect read-only defaults must report the failed write");CheckFailure(Report);
        Check(ReadBytes(EnginePath())==EngineSeed && Report.S.find("read-only: yes")!=std::string::npos,
            "Read-only failure must preserve content and report actual file state");

        Reset();SkipWrite=true;
        Check(!SaveRenderDefaults(Report),"A successful API result without a disk change must fail readback");CheckFailure(Report);
        Check(ReadBytes(EnginePath())==EngineSeed,"No-op write unexpectedly changed disk");

        Reset();CorruptWrite=true;
        Check(!SaveRenderDefaults(Report),"A wrong saved depth value must fail readback");CheckFailure(Report);

        Reset();RejectReadback=true;
        Check(!SaveRenderDefaults(Report),"Unreadable saved defaults must not claim success");CheckFailure(Report);

        Reset();GameWriteSucceeds=false;
        Check(!SaveRenderDefaults(Report),"Rejected DefaultGame persistence must fail setup");CheckFailure(Report);
        Check(Report.S.find("DefaultGame.ini")!=std::string::npos,"DefaultGame failure must identify the failed file");
        Check(ReadBytes((ConfigRoot/"DefaultGame.ini").string())==GameSeed,"Failed DefaultGame write damaged unrelated settings");
        std::cout<<Checks<<" extracted render-default checks passed with separate file/cache state\n";
    }catch(const std::exception& Error) { std::cerr<<Error.what()<<'\n';return 1; }
}
'''

# Retain the actual broken method as a negative control. It must compile against
# the same API and fail persistence at runtime, rather than a textual assertion.
BROKEN_CACHE_FLUSH = r'''
static bool SaveRenderDefaults(FString& OutReport)
{
    if (!GConfig) { OutReport = TEXT("Project configuration is unavailable."); return false; }
    const FString DefaultEngine = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultEngine.ini"));
    GConfig->SetInt(TEXT("/Script/Engine.RendererSettings"), TEXT("r.CustomDepth"), 3, DefaultEngine);
    GConfig->Flush(false, DefaultEngine);
    FConfigFile SavedEngine;
    SavedEngine.Read(DefaultEngine);
    int32 SavedDepth = 0;
    if (!SavedEngine.GetInt(TEXT("/Script/Engine.RendererSettings"), TEXT("r.CustomDepth"), SavedDepth) || SavedDepth != 3)
    { OutReport = TEXT("Could not persist Custom Depth with Stencil to project Config/DefaultEngine.ini. Make that file writable and retry setup."); return false; }
    GConfig->SetInt(TEXT("/Script/Engine.RendererSettings"), TEXT("r.CustomDepth"), 3, GEngineIni);
    UDigimonVenomNXTSettings* Settings = GetMutableDefault<UDigimonVenomNXTSettings>();
    Settings->bRenderCustomDepthByDefault = true;
    Settings->SaveConfig();
    if (!Settings->TryUpdateDefaultConfigFile(FString(), true))
    { OutReport = TEXT("Could not save Digimon render defaults to project Config/DefaultGame.ini. Make that file writable and retry setup."); return false; }
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    OutReport = TEXT("Custom Depth with Stencil and Digimon render defaults saved to project settings.");
    return true;
}
'''


class RenderDefaultsTests(unittest.TestCase):
    def run_cpp(self, production):
        with tempfile.TemporaryDirectory(prefix='dvnxt-render-defaults-') as directory:
            root = Path(directory)
            source = root / 'render.cpp'
            binary = root / ('render.exe' if os.name == 'nt' else 'render')
            source.write_text(API + production + CASES, encoding='utf-8')
            compiler = shlex.split(os.environ.get('CXX', 'g++'))
            compiled = subprocess.run(compiler + ['-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
                                                  str(source), '-o', str(binary)], capture_output=True,
                                      text=True, timeout=45)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            return subprocess.run([str(binary), str(root / 'Config')], capture_output=True,
                                  text=True, timeout=15)

    def test_extracted_render_defaults_persist_and_verify_disk(self):
        result = self.run_cpp(production_function())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_original_cache_flush_regression_is_detected(self):
        result = self.run_cpp(BROKEN_CACHE_FLUSH)
        self.assertNotEqual(result.returncode, 0, 'Original cache-only persistence bug escaped detection')
        self.assertIn('Expected successful disk persistence', result.stderr)

    def test_readback_cannot_be_replaced_with_an_assumed_value(self):
        production = production_function()
        read = 'SavedEngine.Read(DefaultEngine);'
        self.assertEqual(production.count(read), 2)
        before, after = production.rsplit(read, 1)
        mutant = before + 'SavedEngine.SetInt(RendererSection, DepthKey, 3);' + after
        result = self.run_cpp(mutant)
        self.assertNotEqual(result.returncode, 0, 'A pretend readback escaped disk verification tests')
        self.assertIn('successful API result without a disk change must fail readback', result.stderr)


if __name__ == '__main__':
    unittest.main()
