#!/usr/bin/env python3
"""Compile actual WORLD routing, ingress, receiver and lifecycle methods.

The UE containers, controller iterator, clock, RPC transport and HUD are small
observable doubles. No chat/presence policy is reimplemented here. Bulk close
tests execute the unmodified post-save tails from the real session handlers;
source checks verify that all save/checkpoint rejection paths precede those
tails. This does not execute UE networking, GC, UHT or Slate.
"""
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"


def method(source, qualified_name):
    """Extract one complete real C++ method; braces in literals/comments ignored."""
    name = source.index(qualified_name)
    start = source.rfind("\n", 0, name) + 1
    brace = source.index("{", name)
    masked = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                    lambda match: " " * len(match.group()), source, flags=re.S)
    depth = 0
    for index in range(brace, len(source)):
        depth += (masked[index] == "{") - (masked[index] == "}")
        if depth == 0:
            return source[start:index + 1] + "\n"
    raise AssertionError("Unclosed method: " + qualified_name)


STUBS = r'''
#include "DigimonVenomNXTWorldChatCore.h"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
using int32 = int;
using int64 = long long;
using FGuid = int;
#define TEXT(Value) Value
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    FString(const std::string& Value) : std::string(Value) {}
    FString() = default;
    bool IsEmpty() const { return empty(); }
    int32 Len() const { return static_cast<int32>(size()); }
    const char* operator*() const { return c_str(); }
    template<class... Args> static FString Printf(const char* Format, Args... Values) {
        char Buffer[1024]; std::snprintf(Buffer, sizeof(Buffer), Format, Values...); return Buffer;
    }
};
template<class T> struct TArray : std::vector<T> {
    using std::vector<T>::vector;
    void Add(const T& Value) { this->push_back(Value); }
    int32 Num() const { return static_cast<int32>(this->size()); }
    void RemoveAt(int32 Index, int32 Count) { this->erase(this->begin()+Index,this->begin()+Index+Count); }
    template<class F> bool ContainsByPredicate(F Predicate) const {
        return std::any_of(this->begin(),this->end(),Predicate);
    }
};
template<class T> struct TWeakObjectPtr {
    T* Value;
    explicit TWeakObjectPtr(T* In) : Value(In) {}
    bool operator<(const TWeakObjectPtr& Other) const { return std::less<T*>{}(Value,Other.Value); }
};
template<class K, class V> struct TMap : std::map<K,V> {
    bool Contains(const K& Key) const { return this->find(Key)!=this->end(); }
    void Add(const K& Key,const V& Value) { (*this)[Key]=Value; }
    bool RemoveAndCopyValue(const K& Key,V& Out) {
        auto Found=this->find(Key); if(Found==this->end())return false;
        Out=Found->second; this->erase(Found); return true;
    }
};
namespace FMath { template<class T> T Clamp(T Value,T Low,T High) { return std::clamp(Value,Low,High); } }
struct FPlatformTime { static inline double Now=100.0; static double Seconds() { return Now; } };
struct FDateTime { static FDateTime UtcNow() { return {}; } int64 ToUnixTimestamp() const { return 1000; } };
enum class EDigimonChatMessageKind { Player, PlayerJoined, PlayerLeft };
struct FDigimonChatMessage {
    FString Sender,Message,SenderAccountId;
    EDigimonChatMessageKind Kind=EDigimonChatMessageKind::Player;
    int64 UnixTime=0;
};
struct ADigimonVenomNXTPlayerState { struct { FString Username,AccountId; int CurrentMapId=1; } Profile; };
struct APlayerController { virtual ~APlayerController()=default; };
template<class T,class U> T* Cast(U* Value) { return dynamic_cast<T*>(Value); }
struct ADigimonVenomNXTPlayerController;
struct ADigimonVenomNXTGameMode;
struct ControllerEntry { APlayerController* Value; APlayerController* Get() const { return Value; } };
struct FConstPlayerControllerIterator {
    const std::vector<ControllerEntry>* Entries; std::size_t Index=0;
    explicit operator bool() const { return Index<Entries->size(); }
    void operator++() { ++Index; }
    const ControllerEntry* operator->() const { return &(*Entries)[Index]; }
};
struct MockWorld {
    std::vector<ControllerEntry> Controllers;
    ADigimonVenomNXTGameMode* Mode=nullptr;
    FConstPlayerControllerIterator GetPlayerControllerIterator() const { return {&Controllers}; }
    template<class T> T* GetAuthGameMode() const { return static_cast<T*>(Mode); }
};
struct MockHUD { int Appended=0; void AppendChat(const FDigimonChatMessage&) { ++Appended; } };
struct MockDelegate { int Broadcasts=0; void Broadcast(const FDigimonChatMessage&) { ++Broadcasts; } };
struct FTimerDelegate {
    template<class T,class F> static std::function<void()> CreateWeakLambda(T*,F Callback) { return Callback; }
};
struct MockTimerManager {
    std::vector<std::function<void()>> Pending;
    void SetTimer(int&,std::function<void()> Callback,float,bool) { Pending.push_back(Callback); }
    void Flush() { auto Copy=Pending; Pending.clear(); for(auto& Callback:Copy)Callback(); }
};
struct UDigimonVenomNXTSettings { int32 MaxChatCharacters=256; };
template<class T> T* GetDefault() { static T Settings; return &Settings; }
struct UDigimonVenomNXTServerConsoleSubsystem {
    bool Muted=false;
    bool IsAccountMuted(const FString&,FString& Reason) { Reason="muted"; return Muted; }
};
struct UDigimonVenomNXTSocialSubsystem {
    std::map<FString,FString> Ignored;
    bool IsIgnoring(const FString& Viewer,const FString& Sender) const {
        auto Found=Ignored.find(Viewer);
        return Found!=Ignored.end() && !Sender.IsEmpty() && Found->second==Sender;
    }
};
struct UDigimonVenomNXTAuthSubsystem {
    bool GetAccountIdentity(const FString& Name,FString& CanonicalName,FString& Id) const {
        CanonicalName=Name; Id=FString("account-")+Name; return true;
    }
};
struct MockGameInstance {
    UDigimonVenomNXTSocialSubsystem Social;
    UDigimonVenomNXTAuthSubsystem Auth;
    template<class T>T* GetSubsystem() {
        if constexpr(std::is_same_v<T,UDigimonVenomNXTSocialSubsystem>)return &Social;
        else return &Auth;
    }
};
struct FDigimonSocialContact { FString AccountId; };
struct UDigimonVenomNXTSocialComponent {struct {TArray<FDigimonSocialContact> Ignored;} State;};
struct ADigimonVenomNXTPlayerController : APlayerController {
    bool Authority=true,bAccountAuthenticated=true,bLogoutServerCommitted=false,bLogoutPending=false;
    // Distinct spaces exist in the fixture, but delivery must not inspect these or require a pawn.
    bool InPrivateSpace=false,HasPawn=false;
    int Map=1,ForceUpdates=0,CloseCalls=0,LastClosedHistorySize=-1;
    FGuid CommittedLogoutRequestId=0;
    int HostLogoutTravelTimer=0;
    double LastWorldChatSendTime=-1000.0,LastWorldChatFeedbackTime=-1000.0;
    ADigimonVenomNXTPlayerState* State=nullptr;
    MockWorld* World=nullptr;
    MockHUD* GameHUDWidget=nullptr;
    MockDelegate OnChatReceived;
    MockTimerManager TimerManager;
    UDigimonVenomNXTServerConsoleSubsystem* Console=nullptr;
    UDigimonVenomNXTSocialComponent* SocialComponent=nullptr;
    TArray<FDigimonChatMessage> WorldChatHistory;
    std::vector<FString> Feedback,Audit;
    bool HasAuthority() const { return Authority; }
    bool IsAccountAuthenticated() const { return bAccountAuthenticated; }
    MockWorld* GetWorld() const { return World; }
    template<class T> T* GetPlayerState() const { return State; }
    void ForceNetUpdate() { ++ForceUpdates; }
    MockTimerManager& GetWorldTimerManager() { return TimerManager; }
    void ClientShowMessage(const FString&,const FString& Text) { Feedback.push_back(Text); }
    void ClientReceiveLocalChat(const FDigimonChatMessage& Message) { ClientReceiveLocalChat_Implementation(Message); }
    void ClientHostSessionClosed(const FString&) { ++CloseCalls; LastClosedHistorySize=WorldChatHistory.Num(); }
    void ClientLogoutResult(FGuid,bool,const FString&) { ++CloseCalls; LastClosedHistorySize=WorldChatHistory.Num(); }
    void SetAccountAuthenticatedServer(bool);
    void ServerSendWorldChat_Implementation(const FString&);
    void ServerSendLocalChat_Implementation(const FString&);
    void ClientReceiveLocalChat_Implementation(const FDigimonChatMessage&);
    void RunActualCloseTail(TArray<ADigimonVenomNXTPlayerController*> Players,bool bHost,FGuid RequestId);
    bool RunActualRestartTail(TArray<ADigimonVenomNXTPlayerController*> Players);
};
struct ADigimonVenomNXTGameMode {
    bool Authority=true; MockWorld* World=nullptr;
    MockGameInstance Game;
    TMap<TWeakObjectPtr<ADigimonVenomNXTPlayerController>,FString> WorldChatMembers;
    bool HasAuthority() const { return Authority; }
    MockWorld* GetWorld() const { return World; }
    MockGameInstance* GetGameInstance() { return &Game; }
    int32 BroadcastWorldChat(const FDigimonChatMessage&,const ADigimonVenomNXTPlayerController* Excluded=nullptr);
    void JoinWorldChat(ADigimonVenomNXTPlayerController*);
    void LeaveWorldChat(ADigimonVenomNXTPlayerController*);
};
namespace DigimonVenomNXTServerActivity {
    UDigimonVenomNXTServerConsoleSubsystem* Console(ADigimonVenomNXTPlayerController* PC) { return PC->Console; }
    void Record(ADigimonVenomNXTPlayerController* PC,const FString&,const FString&,const FString& Details,const FString& = "") {
        PC->Audit.push_back(Details);
    }
}
namespace DigimonVenomNXTSessionPrivate { void SuspendDurableBattle(ADigimonVenomNXTPlayerController*) {} }
'''


CASES = r'''
int Checks=0;
void Check(bool Condition,const char* Message) { ++Checks; if(!Condition)throw std::runtime_error(Message); }
struct Fixture {
    MockWorld World; ADigimonVenomNXTGameMode Mode;
    ADigimonVenomNXTPlayerController Host,Far,Private,Unauth;
    ADigimonVenomNXTPlayerState HostState,FarState,PrivateState,UnauthState;
    APlayerController OtherType;
    Fixture() {
        World.Mode=&Mode; Mode.World=&World;
        Set(Host,HostState,"Host",1); Set(Far,FarState,"Far",145);
        Set(Private,PrivateState,"Private",-1); Set(Unauth,UnauthState,"Unauth",1);
        Private.InPrivateSpace=true; Unauth.bAccountAuthenticated=false;
        World.Controllers={{&Host},{&Far},{&Private},{&Unauth},{&OtherType},{nullptr}};
    }
    void Set(ADigimonVenomNXTPlayerController& PC,ADigimonVenomNXTPlayerState& PS,const char* Name,int Map) {
        PC.World=&World; PC.State=&PS; PC.Map=Map;
        PS.Profile.Username=Name; PS.Profile.AccountId=std::string("account-")+Name; PS.Profile.CurrentMapId=Map;
    }
    TArray<ADigimonVenomNXTPlayerController*> Players() { return {&Host,&Far,&Private}; }
    void Admit() { for(auto* PC:Players())Mode.JoinWorldChat(PC); Clear(); }
    void Clear() { for(auto* PC:Players())PC->WorldChatHistory.clear(); }
};
int main() {
 try {
    {
        Fixture F; FDigimonChatMessage M; M.Message="cross-map";
        Check(F.Mode.BroadcastWorldChat(M)==3,"WORLD failed to route across maps/private spaces without pawns");
        Check(F.Host.WorldChatHistory.Num()==1&&F.Far.WorldChatHistory.Num()==1&&F.Private.WorldChatHistory.Num()==1,
              "authenticated cross-map recipient missed WORLD message");
        Check(F.Unauth.WorldChatHistory.empty(),"unauthenticated transport received WORLD message");
        Check(F.Mode.BroadcastWorldChat(M,&F.Far)==2&&F.Far.WorldChatHistory.Num()==1,"explicit exclusion ignored");
        F.Mode.Authority=false; Check(F.Mode.BroadcastWorldChat(M)==0,"non-authority broadcast accepted");
        F.Mode.JoinWorldChat(&F.Host); Check(F.Mode.WorldChatMembers.empty(),"non-authority admission accepted");
        F.Mode.Authority=true; F.Mode.World=nullptr; Check(F.Mode.BroadcastWorldChat(M)==0,"missing-world broadcast unsafe");
    }
    {
        Fixture F; F.Admit();
        F.Mode.Game.Social.Ignored["account-Far"]="account-Host";
        FDigimonChatMessage Message;
        Message.Sender="display-name-is-not-the-identity";
        Message.SenderAccountId="account-Host"; Message.Message="blocked";
        Check(F.Mode.BroadcastWorldChat(Message)==2,"ignore did not filter exact account recipient");
        Check(F.Far.WorldChatHistory.empty()&&F.Private.WorldChatHistory.Num()==1,
              "ignore either leaked to blocked recipient or hid unrelated recipient");
        F.Clear(); F.Host.State=nullptr;
        F.Mode.LeaveWorldChat(&F.Host);
        Check(F.Far.WorldChatHistory.empty(),"ignored departure leaked after player state teardown");
        Check(F.Private.WorldChatHistory.Num()==1&&F.Private.WorldChatHistory.back().SenderAccountId=="account-Host",
              "departure did not preserve immutable identity through auth fallback");
        F.Mode.Game.Social.Ignored.clear(); F.Clear();
        Check(F.Mode.BroadcastWorldChat(Message)==3&&F.Far.WorldChatHistory.Num()==1,
              "removing ignore did not restore delivery");
        UDigimonVenomNXTSocialComponent ClientSocial;
        ClientSocial.State.Ignored.Add({"account-Host"}); F.Far.SocialComponent=&ClientSocial; F.Clear();
        F.Far.ClientReceiveLocalChat_Implementation(Message);
        Check(F.Far.WorldChatHistory.empty(),"queued ignored message entered client chat history");
        ClientSocial.State.Ignored.clear();F.Far.ClientReceiveLocalChat_Implementation(Message);
        Check(F.Far.WorldChatHistory.Num()==1,"client-side unignore did not restore queued chat delivery");
    }
    {
        Fixture F;
        F.Mode.JoinWorldChat(nullptr); F.Mode.JoinWorldChat(&F.Unauth); F.Mode.LeaveWorldChat(&F.Unauth);
        F.FarState.Profile.AccountId=""; F.Mode.JoinWorldChat(&F.Far);
        F.Private.State=nullptr; F.Mode.JoinWorldChat(&F.Private);
        Check(F.Mode.WorldChatMembers.empty()&&F.Host.WorldChatHistory.empty(),"failed admission emitted presence");
        F.Mode.JoinWorldChat(&F.Host); F.Mode.JoinWorldChat(&F.Host);
        Check(F.Host.WorldChatHistory.Num()==1&&F.Mode.WorldChatMembers.size()==1,"repeated admission emitted duplicate join");
        const auto& Joined=F.Host.WorldChatHistory.back();
        Check(Joined.Kind==EDigimonChatMessageKind::PlayerJoined&&Joined.Sender=="Host"&&Joined.Message=="Host has joined the game.",
              "join did not use trusted profile identity and correct event type/text");
        F.HostState.Profile.Username="changed-after-admission"; F.Host.State=nullptr;
        F.Host.SetAccountAuthenticatedServer(false); F.Mode.LeaveWorldChat(&F.Host);
        Check(F.Far.WorldChatHistory.Num()==2&&F.Mode.WorldChatMembers.empty(),"deauth plus engine logout duplicated leave");
        const auto& Left=F.Far.WorldChatHistory.back();
        Check(Left.Kind==EDigimonChatMessageKind::PlayerLeft&&Left.Sender=="Host"&&Left.Message=="Host has left the game.",
              "teardown lost admitted identity when PlayerState disappeared");
        Check(F.Host.WorldChatHistory.Num()==2&&!F.Host.bAccountAuthenticated,"leave was not queued before deauthentication");
        F.Host.State=&F.HostState; F.HostState.Profile.Username="Host"; F.Host.SetAccountAuthenticatedServer(true);
        F.Mode.JoinWorldChat(&F.Host); Check(F.Mode.WorldChatMembers.size()==1,"reconnection remained falsely admitted");
        F.Clear(); F.Host.bAccountAuthenticated=false; F.Host.State=nullptr; F.Mode.LeaveWorldChat(&F.Host);
        Check(F.Far.WorldChatHistory.Num()==1,"already-deauthenticated abrupt teardown lost leave");
    }
    for(bool Restart:{false,true}) {
        Fixture F; F.Admit();
        if(Restart)Check(F.Host.RunActualRestartTail(F.Players()),"actual restart tail failed");
        else F.Host.RunActualCloseTail(F.Players(),true,42);
        for(auto* PC:F.Players()) {
            Check(PC->WorldChatHistory.Num()==3,"bulk close deauthenticated recipient before all leaves arrived");
            for(const auto& Entry:PC->WorldChatHistory)Check(Entry.Kind==EDigimonChatMessageKind::PlayerLeft,"bulk close emitted non-leave event");
            Check(!PC->bAccountAuthenticated,"closing session retained gameplay authentication");
            F.Mode.LeaveWorldChat(PC);
            Check(PC->WorldChatHistory.Num()==3,"later engine Logout duplicated bulk-close presence");
        }
        Check(F.Far.CloseCalls==1&&F.Far.LastClosedHistorySize==3&&F.Private.LastClosedHistorySize==3,
              "client close RPC was queued before all presence notices");
        Check(F.Host.CloseCalls==0,"host travel delay disappeared");
        if(!Restart) { F.Host.TimerManager.Flush(); Check(F.Host.LastClosedHistorySize==3,"host closed without complete leave history"); }
        Check(F.Mode.WorldChatMembers.empty(),"bulk closure leaked admission entries");
    }
    {
        Fixture F; F.Admit(); F.Far.RunActualCloseTail({&F.Far},false,7);
        Check(F.Host.WorldChatHistory.Num()==1&&F.Private.WorldChatHistory.Num()==1&&F.Host.bAccountAuthenticated,
              "ordinary player logout closed or skipped other sessions");
        Check(F.Far.CloseCalls==1&&F.Far.LastClosedHistorySize==1,"ordinary logout acknowledged before leave");
    }
    {
        Fixture F; F.Admit(); FPlatformTime::Now=100;
        F.Host.ServerSendWorldChat_Implementation("  /kick Fake\nhello\tworld  ");
        Check(F.Far.WorldChatHistory.Num()==1&&F.Private.WorldChatHistory.Num()==1,"canonical ingress did not reach WORLD recipients");
        const auto& M=F.Far.WorldChatHistory.back();
        Check(M.Kind==EDigimonChatMessageKind::Player&&M.Sender=="Host"&&M.Message=="/kick Fake hello world",
              "ingress did not preserve server identity/type or normalize text");
        Check(F.Host.Audit.size()==1&&F.Host.Audit.back().find("Fake")==std::string::npos,"audit leaked chat body");
        F.Host.ServerSendWorldChat_Implementation("flood"); Check(F.Far.WorldChatHistory.Num()==1,"ingress rate limit bypassed");
        Check(F.Host.Feedback.size()==1,"rate limit failed to report feedback");
        FPlatformTime::Now+=2; F.Host.ServerSendLocalChat_Implementation("legacy WORLD");
        Check(F.Far.WorldChatHistory.Num()==2,"legacy local entry point did not route WORLD");
        UDigimonVenomNXTServerConsoleSubsystem Console; Console.Muted=true; F.Host.Console=&Console;
        FPlatformTime::Now+=2; F.Host.ServerSendWorldChat_Implementation("muted");
        Check(F.Far.WorldChatHistory.Num()==2,"muted account delivered chat");
        Console.Muted=false; F.Host.bLogoutServerCommitted=true; FPlatformTime::Now+=2;
        F.Host.ServerSendWorldChat_Implementation("after logout"); Check(F.Far.WorldChatHistory.Num()==2,"committed logout sent chat");
        F.Unauth.ServerSendWorldChat_Implementation("unauth"); Check(F.Far.WorldChatHistory.Num()==2,"unauthenticated sender sent chat");
        F.Host.bLogoutServerCommitted=false; F.Host.State=nullptr; F.Host.ServerSendWorldChat_Implementation("missing profile");
        Check(F.Far.WorldChatHistory.Num()==2,"missing profile sent chat");
    }
    {
        ADigimonVenomNXTPlayerController Early; Early.bAccountAuthenticated=false; Early.State=nullptr; Early.World=nullptr;
        FDigimonChatMessage Join; Join.Kind=EDigimonChatMessageKind::PlayerJoined; Join.Message="before HUD";
        Early.ClientReceiveLocalChat_Implementation(Join);
        Check(Early.WorldChatHistory.Num()==1&&Early.OnChatReceived.Broadcasts==1,"early authentication/HUD readiness dropped join");
        MockHUD HUD; Early.GameHUDWidget=&HUD;
        for(int I=0;I<DigimonVenomNXTWorldChatCore::HistoryLimit+5;++I) {
            FDigimonChatMessage M; M.UnixTime=I; Early.ClientReceiveLocalChat_Implementation(M);
        }
        Check(Early.WorldChatHistory.Num()==DigimonVenomNXTWorldChatCore::HistoryLimit&&Early.WorldChatHistory.front().UnixTime==5,
              "retained history did not discard oldest entries at the configured bound");
        Check(HUD.Appended==DigimonVenomNXTWorldChatCore::HistoryLimit+5,"live HUD append lost messages");
    }
    std::cout<<"Actual WORLD methods: "<<Checks<<" checks passed (portable UE doubles, not engine networking).\n";
    return 0;
 } catch(const std::exception& Error) { std::cerr<<Error.what()<<'\n'; return 1; }
}
'''


class WorldChatIntegrationTests(unittest.TestCase):
    def sources(self):
        return {name: (PRIVATE / name).read_text(encoding="utf-8") for name in (
            "DigimonVenomNXTGameModeWorldChat.cpp", "DigimonVenomNXTGameMode.cpp",
            "DigimonVenomNXTPlayerController.cpp", "DigimonVenomNXTPlayerControllerSession.cpp")}

    def production_program(self):
        source = self.sources()
        functions = re.sub(r'^#include[^\n]*\n', '', source["DigimonVenomNXTGameModeWorldChat.cpp"], flags=re.M)
        controller = source["DigimonVenomNXTPlayerController.cpp"]
        for name in ("SetAccountAuthenticatedServer", "ServerSendWorldChat_Implementation",
                     "ServerSendLocalChat_Implementation", "ClientReceiveLocalChat_Implementation"):
            functions += method(controller, "ADigimonVenomNXTPlayerController::" + name)
        sessions = source["DigimonVenomNXTPlayerControllerSession.cpp"]
        marker = "for (ADigimonVenomNXTPlayerController* SessionController : Players) Mode->LeaveWorldChat(SessionController);"
        close = method(sessions, "ADigimonVenomNXTPlayerController::ServerRequestLogout_Implementation")
        restart = method(sessions, "ADigimonVenomNXTPlayerController::PrepareHostWorldRestart")
        self.assertIn(marker, close)
        self.assertIn(marker, restart)
        functions += ("void ADigimonVenomNXTPlayerController::RunActualCloseTail(TArray<ADigimonVenomNXTPlayerController*> Players,bool bHost,FGuid RequestId)\n"
                      "{ ADigimonVenomNXTGameMode* Mode=GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();\n" + close[close.index(marker):])
        functions += ("bool ADigimonVenomNXTPlayerController::RunActualRestartTail(TArray<ADigimonVenomNXTPlayerController*> Players)\n"
                      "{ ADigimonVenomNXTGameMode* Mode=GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();\n" + restart[restart.index(marker):])
        return STUBS + functions + CASES

    def compile_and_run(self, program):
        with tempfile.TemporaryDirectory(prefix="digimon-world-chat-") as directory:
            source = Path(directory) / "world_chat.cpp"
            executable = Path(directory) / "world_chat"
            source.write_text(program, encoding="utf-8")
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                "-I", str(PRIVATE), str(source), "-o", str(executable)]
            compiled = subprocess.run(command, capture_output=True, text=True, timeout=45, check=False)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            return subprocess.run([str(executable)], capture_output=True, text=True, timeout=10, check=False)

    def test_actual_routing_ingress_presence_and_post_save_close_sequences(self):
        result = self.compile_and_run(self.production_program())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_missing_authentication_gate_is_detected(self):
        program = self.production_program().replace(
            "Recipient == Excluded || !Recipient->IsAccountAuthenticated()", "Recipient == Excluded", 1)
        result = self.compile_and_run(program)
        self.assertNotEqual(result.returncode, 0, "Negative control failed to detect unauthorized delivery")
        self.assertIn("WORLD failed to route", result.stderr)

    def test_admission_logout_save_and_rpc_wiring(self):
        sources = self.sources()
        mode = sources["DigimonVenomNXTGameMode.cpp"]
        auth = method(mode, "ADigimonVenomNXTGameMode::AuthenticatePlayer")
        # Membership is now gated by the verified owner snapshot, not just credentials.
        self.assertNotIn("JoinWorldChat(Controller);", auth)
        self.assertLess(auth.index("NPS->InitializeServerProfile(Profile);"), auth.index("Controller->SetAccountAuthenticatedServer(true);"))
        finish = method(mode, "ADigimonVenomNXTGameMode::FinishAuthenticatedPlayerLogin")
        self.assertEqual(finish.count("JoinWorldChat(Controller);"), 1)
        self.assertLess(finish.index("!Controller->IsOwnerProfileReady()"), finish.index("JoinWorldChat(Controller);"))
        sync = (PRIVATE / "DigimonVenomNXTPlayerControllerProfileSync.cpp").read_text()
        self.assertIn("Mode->FinishAuthenticatedPlayerLogin(this)", sync)
        self.assertNotIn("JoinWorldChat", method(mode, "ADigimonVenomNXTGameMode::PostLogin"))
        logout = method(mode, "ADigimonVenomNXTGameMode::Logout")
        self.assertLess(logout.index("LeaveWorldChat("), logout.index("GetPlayerState<"))
        self.assertLess(logout.index("LeaveWorldChat("), logout.index("Super::Logout("))
        sessions = sources["DigimonVenomNXTPlayerControllerSession.cpp"]
        for name in ("ServerRequestLogout_Implementation", "PrepareHostWorldRestart"):
            body = method(sessions, "ADigimonVenomNXTPlayerController::" + name)
            leave = body.index("Mode->LeaveWorldChat(SessionController)")
            self.assertLess(body.index("CanPreserveBattle("), leave)
            self.assertLess(body.index("!Mode->SavePlayer("), leave)
            self.assertLess(body.index("!Console->SaveAll("), leave)
            # Every failed persistence/checkpoint path exits before presence changes.
            self.assertLess(body.rfind("return false;" if name == "PrepareHostWorldRestart" else "return;"), leave)
            self.assertLess(leave, body.index("SetAccountAuthenticatedServer(false)"))
            self.assertLess(leave, body.index("ClientHostSessionClosed("))
        header = (PUBLIC / "DigimonVenomNXTPlayerController.h").read_text(encoding="utf-8")
        for name in ("ServerSendLocalChat", "ServerSendWorldChat"):
            self.assertRegex(header, r'UFUNCTION\([^\n]*Server, Reliable[^\n]*\)\s*void ' + name + r'\(const FString& Message\)')
        self.assertRegex(header, r'UFUNCTION\(Client, Reliable[^\n]*\)\s*void ClientReceiveLocalChat\(')
        send = method(sources["DigimonVenomNXTPlayerController.cpp"], "ADigimonVenomNXTPlayerController::ServerSendLocalChat_Implementation")
        self.assertNotRegex(send, r'Execute(?:Sensitive)?Command|RunCommand|ConsoleCommand')
        self.assertNotIn("LocalChatRadius", send)
        self.assertNotIn("GetPawn()", send)
        hud = (PRIVATE / "DigimonVenomNXTGameHUDWidget.cpp").read_text(encoding="utf-8")
        initialized = method(hud, "UDigimonVenomNXTGameHUDWidget::NativeConstruct")
        append = method(hud, "UDigimonVenomNXTGameHUDWidget::AppendChat")
        for panel in ("FieldWorldChat", "MenuWorldChat"):
            replay = panel + "->SetHistory(PC->WorldChatHistory)"
            self.assertIn(replay, initialized, "Early messages must replay into both native chat views")
            self.assertLess(initialized.index("BuildNativeUI();"), initialized.index(replay))
            self.assertIn(panel + "->AppendMessage(Message)", append)


if __name__ == "__main__":
    unittest.main()
