#!/usr/bin/env python3
"""Compile the real editor-module lifecycle against observable engine stand-ins.

This verifies callback ownership and headless ordering. Class discovery itself
still requires running the UE editor commandlet binary.
"""
import json
import os
import re
import shlex
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'Source/DigimonVenomNXTEditor/Private/DigimonVenomNXTEditor.cpp'
HEADER = ROOT / 'Source/DigimonVenomNXTEditor/Public/DigimonVenomNXTEditor.h'


def method(source, name):
    start = source.index('void FDigimonVenomNXTEditorModule::' + name + '(')
    masked = re.sub(r'"(?:\\.|[^"\\])*"|//[^\n]*|/\*.*?\*/',
                    lambda match: ' ' * len(match[0]), source, flags=re.DOTALL)
    opening, depth = masked.index('{', start), 0
    for pos in range(opening, len(masked)):
        depth += (masked[pos] == '{') - (masked[pos] == '}')
        if depth == 0:
            return source[start:pos + 1]
    raise AssertionError('Unbalanced lifecycle method: ' + name)


STUBS = r'''
#include <functional>
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
void Check(bool Value,const char* Message) { if(!Value)throw std::runtime_error(Message); }
struct FDelegateHandle {
    int Id=0;
    bool IsValid() const { return Id!=0; }
    void Reset() { Id=0; }
};
struct FSimpleMulticastDelegate {
    struct FDelegate {
        std::function<void()> Call;
        template<class T> static FDelegate CreateRaw(T* Owner,void(T::*Method)()) {
            return {[Owner,Method](){(Owner->*Method)();}};
        }
    };
    int Next=1;
    std::map<int,FDelegate> Callbacks;
    template<class T> FDelegateHandle AddRaw(T* Owner,void(T::*Method)()) {
        const int Id=Next++;Callbacks.emplace(Id,FDelegate::CreateRaw(Owner,Method));return {Id};
    }
    void Remove(FDelegateHandle Handle) { Callbacks.erase(Handle.Id); }
    void Broadcast() {
        const auto Snapshot=Callbacks;
        for(const auto& Entry:Snapshot)if(Callbacks.count(Entry.first))Entry.second.Call();
    }
};
struct FCoreDelegates {
    static FSimpleMulticastDelegate& GetOnPostEngineInit() {
        static FSimpleMulticastDelegate Event;return Event;
    }
};
bool Commandlet=false,GIsRunning=false,MenuModuleAvailable=true;
struct Editor {} EditorInstance;
Editor* GEditor=nullptr;
bool IsRunningCommandlet() { return Commandlet; }
struct IModuleInterface {
    virtual ~IModuleInterface()=default;
    virtual void StartupModule() {}
    virtual void ShutdownModule() {}
};
int PreviewsStarted=0,PreviewsStopped=0,MenuCallbacks=0,MenusRemoved=0,OwnersRemoved=0,MenusBuilt=0;
namespace DigimonVenomNXTEditorMapPreview {
    void Startup() { Check(!Commandlet && GEditor,"Preview started before interactive engine readiness");++PreviewsStarted; }
    void Shutdown() { ++PreviewsStopped; }
}
struct IToolMenusModule { static bool IsAvailable() { return MenuModuleAvailable; } };
struct UToolMenus {
    static FDelegateHandle RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate Delegate) {
        Check(!Commandlet && GEditor,"Menu callback registered during headless/early startup");
        ++MenuCallbacks;Delegate.Call();return {1};
    }
    static void UnRegisterStartupCallback(FDelegateHandle Handle) {
        Check(Handle.IsValid() && MenuModuleAvailable,"Invalid menu callback removal");++MenusRemoved;
    }
    static void UnregisterOwner(void*) { Check(MenuModuleAvailable,"Menus accessed after unload");++OwnersRemoved; }
};
'''

SCENARIOS = r'''
void FDigimonVenomNXTEditorModule::RegisterMenus() { ++MenusBuilt; }
int main(int argc,char** argv) {
    try {
        const std::string Scenario=argc>1?argv[1]:"";
        FDigimonVenomNXTEditorModule Module;
        auto& Event=FCoreDelegates::GetOnPostEngineInit();
        if(Scenario=="commandlet" || Scenario=="commandlet_initialized") {
            Commandlet=true;
            if(Scenario=="commandlet_initialized") { GEditor=&EditorInstance;GIsRunning=true; }
            Module.StartupModule();Event.Broadcast();Module.ShutdownModule();
            Check(Event.Callbacks.empty(),"Commandlet retained an editor callback");
            Check(PreviewsStarted+PreviewsStopped+MenuCallbacks+MenusRemoved+OwnersRemoved+MenusBuilt==0,
                "Commandlet touched preview or UI lifecycle");
        } else if(Scenario=="unload_before_init") {
            Module.StartupModule();Check(Event.Callbacks.size()==1,"Early startup must defer");
            Module.ShutdownModule();GEditor=&EditorInstance;Event.Broadcast();
            Check(Event.Callbacks.empty() && PreviewsStarted==0 && PreviewsStopped==0 && MenuCallbacks==0,
                "Unloaded module left a live engine-init callback");
        } else if(Scenario=="no_editor") {
            Module.StartupModule();Event.Broadcast();Module.ShutdownModule();
            Check(Event.Callbacks.empty() && PreviewsStarted==0 && PreviewsStopped==0 && MenuCallbacks==0,
                "Missing editor instance started UI work");
        } else {
            const bool Late=Scenario=="late_load" || Scenario=="menu_module_unloaded" || Scenario=="reload";
            if(Late) { GIsRunning=true;GEditor=&EditorInstance; }
            Module.StartupModule();
            if(!Late) {
                Check(Event.Callbacks.size()==1 && PreviewsStarted==0 && MenuCallbacks==0,
                    "Default-phase load performed interactive work before engine init");
                GEditor=&EditorInstance;Event.Broadcast();
            }
            Check(Event.Callbacks.empty(),"Completed initialization retained its raw callback");
            Event.Broadcast();
            Check(PreviewsStarted==1 && MenuCallbacks==1 && MenusBuilt==1,"Interactive initialization did not run exactly once");
            if(Scenario=="menu_module_unloaded")MenuModuleAvailable=false;
            Module.ShutdownModule();Module.ShutdownModule();
            Check(PreviewsStopped==1,"Preview shutdown was missing or duplicated");
            const int ExpectedRemoval=MenuModuleAvailable?1:0;
            Check(MenusRemoved==ExpectedRemoval && OwnersRemoved==ExpectedRemoval,"Menu shutdown ownership was incorrect");
            if(Scenario=="reload") {
                Module.StartupModule();Module.ShutdownModule();
                Check(PreviewsStarted==2 && PreviewsStopped==2 && MenuCallbacks==2 && MenusRemoved==2 && OwnersRemoved==2,
                    "Reload did not reset module lifecycle state");
            }
        }
        std::cout<<Scenario<<" passed\n";
    } catch(const std::exception& Error) { std::cerr<<Error.what()<<'\n';return 1; }
}
'''


class EditorModuleLifecycle(unittest.TestCase):
    def test_reflected_commandlet_module_loads_before_engine_initialization(self):
        descriptor = json.loads((ROOT / 'DigimonVenomNXT.uplugin').read_text(encoding='utf-8'))
        editor = next(module for module in descriptor['Modules'] if module['Name'] == 'DigimonVenomNXTEditor')
        self.assertEqual(editor['Type'], 'Editor', 'EditorNoCommandlet would exclude the import class')
        self.assertEqual(editor['LoadingPhase'], 'Default', 'PostEngineInit is too late for commandlet class resolution')

    def test_actual_lifecycle_headless_deferred_late_and_shutdown_paths(self):
        source = SOURCE.read_text(encoding='utf-8')
        header = re.sub(r'^\s*#.*$', '', HEADER.read_text(encoding='utf-8'), flags=re.MULTILINE)
        production = '\n'.join(method(source, name) for name in ('StartupModule', 'InitializeEditor', 'ShutdownModule'))
        with tempfile.TemporaryDirectory(prefix='digimon-module-lifecycle-') as temporary:
            directory = Path(temporary)
            cpp, exe = directory / 'lifecycle.cpp', directory / ('lifecycle.exe' if os.name == 'nt' else 'lifecycle')
            cpp.write_text(STUBS + header + production + SCENARIOS, encoding='utf-8')
            compiler = shlex.split(os.environ.get('CXX', 'g++'))
            compiled = subprocess.run(compiler + ['-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror', '-pedantic',
                                                  str(cpp), '-o', str(exe)], capture_output=True, text=True, timeout=40)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            scenarios = ('commandlet', 'commandlet_initialized', 'early_load', 'late_load',
                         'unload_before_init', 'no_editor', 'menu_module_unloaded', 'reload')
            for scenario in scenarios:
                with self.subTest(scenario=scenario):
                    result = subprocess.run([str(exe), scenario], capture_output=True, text=True, timeout=5)
                    self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(f'{len(scenarios)} production editor module lifecycle paths passed')


if __name__ == '__main__':
    unittest.main()
