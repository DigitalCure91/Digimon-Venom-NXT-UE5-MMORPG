#!/usr/bin/env python3
"""Execute the production POSIX atomic-replace function on real temporary files.

UE path/string adapters are doubled; open/fsync/rename/close are real syscalls.
The Windows branch still requires the documented native build/run gate.
"""
from pathlib import Path
import os
import shlex
import subprocess
import tempfile
import unittest
from test_world_chat_integration import method

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTAtomicFile.cpp"

STUBS = r'''
#include <cstdio>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#define PLATFORM_WINDOWS 0
#define TEXT(Value) Value
#define UE_LOG(...) ((void)0)
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    FString()=default;
    FString(const std::string& Value):std::string(Value){}
    bool IsEmpty()const{return empty();}
    const char* operator*()const{return c_str();}
};
struct FTCHARToUTF8 {
    std::string Value;
    explicit FTCHARToUTF8(const char* Input):Value(Input){}
    const char* Get()const{return Value.c_str();}
};
struct IFileManager {
    static IFileManager& Get(){static IFileManager Value;return Value;}
    FString ConvertToAbsolutePathForExternalAppForWrite(const char* Input){return std::filesystem::absolute(Input).string();}
};
struct FPaths {
    static void NormalizeFilename(FString& Value){Value=std::filesystem::path(Value.c_str()).lexically_normal().string();}
    static FString GetPath(const FString& Value){return std::filesystem::path(Value.c_str()).parent_path().string();}
};
namespace DigimonVenomNXTAtomicFile {bool ReplaceFromTemporary(const FString&,const FString&);}
'''

CASES = r'''
int Checks=0;
void Check(bool OK,const char* Message){++Checks;if(!OK)throw std::runtime_error(Message);}
void Write(const FString& Path,const std::string& Data){std::ofstream Out(Path);Out<<Data;Out.close();Check(Out.good(),"fixture write failed");}
std::string Read(const FString& Path){std::ifstream In(Path);return {std::istreambuf_iterator<char>(In),std::istreambuf_iterator<char>()};}
int main(int Argc,char** Argv){try{
    Check(Argc==2,"scratch directory missing");
    const FString Root=Argv[1];
    const FString Destination=Root+"/accounts.json",Temporary=Root+"/accounts.tmp";
    Write(Destination,"original");
    Check(!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Destination,Temporary),"missing source was accepted");
    Check(Read(Destination)=="original","missing source destroyed destination");
    Check(!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Destination,Destination),"identical source/destination was accepted");
    Check(Read(Destination)=="original","identical source destroyed destination");
    Check(!DigimonVenomNXTAtomicFile::ReplaceFromTemporary("",Temporary),"empty destination accepted");
    Write(Temporary,"new durable state");
    Check(DigimonVenomNXTAtomicFile::ReplaceFromTemporary(Destination,Temporary),"valid replacement failed");
    Check(Read(Destination)=="new durable state","replacement has incorrect contents");
    Check(!std::filesystem::exists(Temporary.c_str()),"successful replacement retained temporary source");
    Write(Temporary,"next state");
    const FString OtherDirectory=Root+"/other";
    std::filesystem::create_directory(OtherDirectory.c_str());
    Check(!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(OtherDirectory+"/new.json",Temporary),"cross-directory replacement accepted");
    Check(Read(Temporary)=="next state","rejected cross-directory replacement discarded source");
    const FString DirectoryDestination=Root+"/directory";
    std::filesystem::create_directory(DirectoryDestination.c_str());
    Check(!DigimonVenomNXTAtomicFile::ReplaceFromTemporary(DirectoryDestination,Temporary),"rename over a directory succeeded");
    Check(Read(Temporary)=="next state","failed rename discarded source");
    Check(std::filesystem::is_directory(DirectoryDestination.c_str()),"failed rename damaged existing directory");
    const FString NewFile=Root+"/new.json";
    Check(DigimonVenomNXTAtomicFile::ReplaceFromTemporary(NewFile,Temporary),"first save failed");
    Check(Read(NewFile)=="next state","first save contents wrong");
    std::cout<<"Actual POSIX atomic replacement: "<<Checks<<" real-file integrity checks passed.\n";
    return 0;
}catch(const std::exception& Error){std::cerr<<Error.what()<<'\n';return 1;}}
'''


class AtomicFileIntegrationTests(unittest.TestCase):
    @unittest.skipIf(os.name == "nt", "POSIX harness; native Windows build runs the Win32 branch")
    def test_actual_posix_atomic_replacement_preserves_failed_and_committed_state(self):
        source = SOURCE.read_text(encoding="utf-8")
        program = STUBS + method(source, "DigimonVenomNXTAtomicFile::ReplaceFromTemporary(") + CASES
        with tempfile.TemporaryDirectory(prefix="digimon-atomic-") as directory:
            cpp = Path(directory) / "atomic.cpp"
            binary = Path(directory) / "atomic"
            cpp.write_text(program, encoding="utf-8")
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", str(cpp), "-o", str(binary)]
            compiled = subprocess.run(command, capture_output=True, text=True, timeout=45)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(binary), directory], capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout.strip())


if __name__ == "__main__":
    unittest.main()
