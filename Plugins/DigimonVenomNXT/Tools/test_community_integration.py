#!/usr/bin/env python3
"""Execute real live-challenge authority methods with portable UE doubles.

Exercises consent, authority, replay, ignore, expiry and disconnect races. These
checks do not execute UE replication, UHT, widgets or the full battle engine.
"""
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile
import unittest
from test_world_chat_integration import method

ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ROOT / "Source/DigimonVenomNXTRuntime/Private"
PUBLIC = ROOT / "Source/DigimonVenomNXTRuntime/Public"

STUBS = r'''
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using int64=long long;
#define TEXT(Value) Value
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    FString()=default;
    FString(const std::string& S):std::string(S){}
    bool IsEmpty() const { return empty(); }
};
struct FGuid {
    int Value=0;
    static FGuid NewGuid(){static int Next=100;return {++Next};}
    bool IsValid() const {return Value!=0;}
    bool operator==(const FGuid& B) const {return Value==B.Value;}
    bool operator!=(const FGuid& B) const {return !(*this==B);}
};
template<class T> struct TArray : std::vector<T> {
    using std::vector<T>::vector;
    bool IsEmpty() const {return this->empty();}
};
template<class T> struct TWeakObjectPtr {
    T* Value=nullptr;
    TWeakObjectPtr& operator=(T* In) {Value=In;return *this;}
    T* Get() const {return Value;}
    T* operator->() const {return Value;}
    bool IsValid() const {return Value!=nullptr;}
    void Reset() {Value=nullptr;}
};
struct FPlatformTime {static inline double Now=100;static double Seconds(){return Now;}};
struct FDateTime {
    static inline int64 Now=1000;
    static FDateTime UtcNow(){return {};}
    int64 ToUnixTimestamp()const{return Now;}
};
struct ADigimonVenomNXTPlayerState {
    struct {
        FString AccountId="account";
        FString Username="Tamer";
        TArray<int> Party={1};
        int CurrentMapId=1;
        struct {bool bInside=false;} Farm;
        bool Campaign=false;
    } Profile;
    bool Active=false;
    bool HasActiveBattle()const{return Active;}
};
namespace DigimonVenomNXTCampaign {
    template<class T>bool IsActive(const T& Profile){return Profile.Campaign;}
}
struct UDigimonVenomNXTSocialSubsystem {
    bool Blocked=false;
    bool IsInteractionBlocked(const FString&,const FString&)const{return Blocked;}
};
struct MockGameInstance {
    UDigimonVenomNXTSocialSubsystem* Social=nullptr;
    template<class T>T* GetSubsystem()const{return Social;}
};
enum class EDigimonBattleKind {Friendly};
struct ADigimonVenomNXTBattleActor {
    bool InitializeOK=true,Destroyed=false;
    static int StaticClass(){return 1;}
    bool InitializeTamerBattle(ADigimonVenomNXTPlayerState*,ADigimonVenomNXTPlayerState*,EDigimonBattleKind){return InitializeOK;}
    void Destroy(){Destroyed=true;}
};
struct MockClass {
    int Value=0;
    explicit operator bool()const{return Value!=0;}
    int Get()const{return Value;}
};
struct ADigimonVenomNXTGameMode {
    int GetBattleActorClass() const;
protected:
    MockClass BattleActorClass;
};
struct ConfigurableGameMode : ADigimonVenomNXTGameMode {
    void Configure(int Value){BattleActorClass.Value=Value;}
};
struct MockWorld {
    ConfigurableGameMode Mode;
    ADigimonVenomNXTBattleActor Battle;
    int Spawns=0, SpawnedClass=0;
    bool SpawnOK=true, HasMode=true;
    template<class T>T* GetAuthGameMode(){return HasMode?&Mode:nullptr;}
    template<class T>T* SpawnActor(int Class){++Spawns;SpawnedClass=Class;return SpawnOK?&Battle:nullptr;}
};
struct UDigimonVenomNXTUnrankedComponent;
struct ADigimonVenomNXTPlayerController {
    bool Authority=true,Authenticated=true,Logout=false,Pawn=true,Farm=false,Relay=false,Gameplay=true;
    ADigimonVenomNXTPlayerState State;
    UDigimonVenomNXTUnrankedComponent* Unranked=nullptr;
    int Messages=0;
    MockGameInstance* Game=nullptr;
    MockWorld* World=nullptr;
    ADigimonVenomNXTBattleActor* CurrentBattle=nullptr;
    bool HasAuthority()const{return Authority;}
    bool IsAccountAuthenticated()const{return Authenticated;}
    bool IsLogoutPending()const{return Logout;}
    void* GetPawn()const{return Pawn?(void*)this:nullptr;}
    bool IsInDigiFarm()const{return Farm;}
    bool IsInRelay()const{return Relay;}
    MockGameInstance* GetGameInstance()const{return Game;}
    template<class T>T* GetPlayerState()const{return const_cast<ADigimonVenomNXTPlayerState*>(&State);}
    template<class T>T* FindComponentByClass()const{return Unranked;}
    void SetCurrentBattleServer(ADigimonVenomNXTBattleActor* Battle){CurrentBattle=Battle;}
    void ClientShowMessage(const FString&,const FString&){++Messages;}
};
namespace DigimonVenomNXTServerActivity {
    bool AllowGameplay(ADigimonVenomNXTPlayerController* Player,FString*){return Player->Gameplay;}
}
struct FDigimonUnrankedChallenge {
    FGuid ChallengeId;
    FString OtherAccountId,OtherName;
    int64 ExpiresUnix=0;
};
struct UDigimonVenomNXTUnrankedComponent {
    ADigimonVenomNXTPlayerController* Owner=nullptr;
    ADigimonVenomNXTPlayerController* Lookup=nullptr;
    TWeakObjectPtr<UDigimonVenomNXTUnrankedComponent> OtherComponent;
    FDigimonUnrankedChallenge IncomingChallenge,OutgoingChallenge;
    FString StatusMessage;
    double LastAction=-1000,LastChallenge=-1000;
    ADigimonVenomNXTPlayerController* GetOwner()const{return Owner;}
    ADigimonVenomNXTPlayerController* Controller()const{return Owner;}
    MockWorld* GetWorld()const{return Owner->World;}
    void Notify(const FString& Message){StatusMessage=Message;}
    bool RateLimit(double& Previous,double Interval);
    bool Ready(ADigimonVenomNXTPlayerController* Player,FString& Error)const;
    bool Compatible(ADigimonVenomNXTPlayerController* First,ADigimonVenomNXTPlayerController* Second,FString& Error)const;
    ADigimonVenomNXTPlayerController* FindOnline(const FString& Id)const{return Lookup&&Lookup->State.Profile.AccountId==Id?Lookup:nullptr;}
    void ClearInvitation(const FString& Message);
    void CheckInvitation();
    void ServerRespond_Implementation(FGuid Id,bool Accept);
    void ServerCancel_Implementation(FGuid Id);
    void ServerChallengePlayer_Implementation(const FString& Id);
};
'''

CASES = r'''
int Checks=0;
void Check(bool OK,const char* Message){++Checks;if(!OK)throw std::runtime_error(Message);}
struct Fixture {
    UDigimonVenomNXTSocialSubsystem Social;
    MockGameInstance Game;
    MockWorld World;
    ADigimonVenomNXTPlayerController A,B;
    UDigimonVenomNXTUnrankedComponent First,Second;
    Fixture(){
        FPlatformTime::Now+=100;FDateTime::Now+=100;
        Game.Social=&Social; A.Game=&Game;B.Game=&Game;A.World=&World;B.World=&World;
        A.State.Profile.AccountId="first";B.State.Profile.AccountId="second";
        First.Owner=&A;Second.Owner=&B;First.Lookup=&B;Second.Lookup=&A;A.Unranked=&First;B.Unranked=&Second;
        First.OutgoingChallenge.ChallengeId={42};First.OutgoingChallenge.ExpiresUnix=FDateTime::Now+45;
        Second.IncomingChallenge=First.OutgoingChallenge;
        First.OtherComponent=&Second;Second.OtherComponent=&First;
    }
    void Accept(){Second.ServerRespond_Implementation({42},true);}
    void Empty(){Check(!First.OutgoingChallenge.ChallengeId.IsValid()&&!Second.IncomingChallenge.ChallengeId.IsValid(),"both invitations must be consumed");}
};
int main(){try{
    {Fixture F;F.First.ClearInvitation("ready");F.First.ServerChallengePlayer_Implementation("second");
     Check(F.First.OutgoingChallenge.ChallengeId.IsValid()&&F.First.OutgoingChallenge.ChallengeId==F.Second.IncomingChallenge.ChallengeId,
        "available tamers did not receive matching newly issued invitations");
     Check(F.B.Messages==1&&F.World.Spawns==0,"issuing invitation must notify the recipient without starting combat");}
    {Fixture F;F.Accept();Check(F.World.SpawnedClass==ADigimonVenomNXTBattleActor::StaticClass(),"unset configured class must select native fallback");}
    {Fixture F;F.World.Mode.Configure(27);F.Accept();Check(F.World.SpawnedClass==27,"configured battle subclass was discarded");}
    {Fixture F;F.World.HasMode=false;F.Accept();Check(F.World.SpawnedClass==ADigimonVenomNXTBattleActor::StaticClass(),"missing mode must select native fallback");}
    {Fixture F;F.Accept();F.Empty();Check(F.World.Spawns==1,"valid consent must start one match");
     Check(F.A.CurrentBattle==&F.World.Battle&&F.B.CurrentBattle==&F.World.Battle,"both participants must own same match");
     FPlatformTime::Now+=1;F.Accept();Check(F.World.Spawns==1,"replayed consent spawned another match");}
    {Fixture F;F.Second.ServerRespond_Implementation({41},true);Check(F.World.Spawns==0,"foreign challenge accepted");
     Check(F.Second.IncomingChallenge.ChallengeId.IsValid(),"foreign challenge cleared real invitation");}
    {Fixture F;F.First.ServerRespond_Implementation({42},true);Check(F.World.Spawns==0,"sender accepted own invitation");}
    {Fixture F;F.Second.ServerRespond_Implementation({42},false);F.Empty();Check(F.World.Spawns==0,"declined challenge spawned battle");}
    {Fixture F;F.First.ServerCancel_Implementation({42});F.Empty();Check(F.World.Spawns==0,"cancelled challenge spawned battle");}
    {Fixture F;F.Second.ServerCancel_Implementation({42});Check(F.Second.IncomingChallenge.ChallengeId.IsValid(),"receiver cancelled outgoing-only route");}
    {Fixture F;F.Social.Blocked=true;F.Accept();F.Empty();Check(F.World.Spawns==0,"ignore added after invite did not block acceptance");}
    {Fixture F;F.Game.Social=nullptr;F.Accept();F.Empty();Check(F.World.Spawns==0,"missing ignore service did not fail closed");}
    {Fixture F;FDateTime::Now=F.Second.IncomingChallenge.ExpiresUnix;F.Accept();F.Empty();Check(F.World.Spawns==0,"expiry boundary accepted");}
    {Fixture F;FDateTime::Now=F.Second.IncomingChallenge.ExpiresUnix;F.Second.CheckInvitation();F.Empty();}
    {Fixture F;F.A.State.Profile.CurrentMapId=2;F.Second.CheckInvitation();F.Empty();Check(F.World.Spawns==0,"cross-map challenge continued");}
    {Fixture F;F.Second.OtherComponent.Reset();F.Second.CheckInvitation();Check(!F.Second.IncomingChallenge.ChallengeId.IsValid(),"disconnected peer remained pending");}
    {Fixture F;F.Second.IncomingChallenge.ChallengeId={43};F.First.ClearInvitation("old cancelled");
     Check(F.Second.IncomingChallenge.ChallengeId.Value==43,"old cancellation cleared newer peer invite");}
    {Fixture F;F.B.Authenticated=false;F.Accept();Check(F.World.Spawns==0,"unauthenticated consent accepted");}
    {Fixture F;F.B.Authority=false;F.Accept();Check(F.World.Spawns==0,"client local consent created battle");}
    {Fixture F;F.B.Logout=true;F.Accept();F.Empty();Check(F.World.Spawns==0,"logout-pending consent accepted");}
    {Fixture F;F.B.Gameplay=false;F.Accept();F.Empty();Check(F.World.Spawns==0,"maintenance blocked consent accepted");}
    {Fixture F;F.B.State.Profile.Party.clear();F.Accept();F.Empty();Check(F.World.Spawns==0,"empty party consent accepted");}
    {Fixture F;F.A.State.Active=true;F.Accept();F.Empty();Check(F.World.Spawns==0,"battle already active accepted");}
    {Fixture F;F.A.Farm=true;F.Accept();F.Empty();Check(F.World.Spawns==0,"private farm consent accepted");}
    {Fixture F;F.A.State.Profile.Campaign=true;F.Accept();F.Empty();Check(F.World.Spawns==0,"private campaign consent accepted");}
    {Fixture F;F.World.SpawnOK=false;F.Accept();F.Empty();Check(!F.A.CurrentBattle&&!F.B.CurrentBattle,"failed spawn attached invalid battle");}
    {Fixture F;F.World.Battle.InitializeOK=false;F.Accept();F.Empty();Check(F.World.Battle.Destroyed,"failed initialization leaked battle");
     Check(!F.A.CurrentBattle&&!F.B.CurrentBattle,"failed initialization attached battle");}
    {Fixture F;double Last=-1000;Check(F.First.RateLimit(Last,3),"first request was throttled");
     Check(!F.First.RateLimit(Last,3),"duplicate request not throttled");FPlatformTime::Now+=3;
     Check(F.First.RateLimit(Last,3),"rate boundary request incorrectly throttled");}
    std::cout<<"Actual unranked authority methods: "<<Checks<<" consent, ignore, ownership, replay and race checks passed.\n";
    return 0;
}catch(const std::exception& Error){std::cerr<<Error.what()<<'\n';return 1;}}
'''


class CommunityIntegrationTests(unittest.TestCase):
    def production_program(self):
        source = (PRIVATE / "DigimonVenomNXTUnrankedComponent.cpp").read_text(encoding="utf-8")
        methods = ("RateLimit", "Ready", "Compatible", "ClearInvitation", "CheckInvitation", "ServerChallengePlayer_Implementation",
                   "ServerRespond_Implementation", "ServerCancel_Implementation")
        mode_source = (PRIVATE / "DigimonVenomNXTGameMode.cpp").read_text(encoding="utf-8")
        # The pointer/class token is represented by int in this portable fixture;
        # the production accessor body and C++ protected access rules are unchanged.
        accessor = method(mode_source, "ADigimonVenomNXTGameMode::GetBattleActorClass(").replace(
            "UClass* ADigimonVenomNXTGameMode::", "int ADigimonVenomNXTGameMode::", 1)
        return STUBS + accessor + "\n".join(method(source, "UDigimonVenomNXTUnrankedComponent::" + name + "(")
                                 for name in methods) + CASES

    def compile_and_run(self, program, expect_compile_success=True):
        with tempfile.TemporaryDirectory(prefix="digimon-community-") as directory:
            source = Path(directory) / "community.cpp"
            binary = Path(directory) / "community"
            source.write_text(program, encoding="utf-8")
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                str(source), "-o", str(binary)]
            compile_result = subprocess.run(command, capture_output=True, text=True, timeout=45)
            if not expect_compile_success:
                self.assertNotEqual(compile_result.returncode, 0, "protected-field regression unexpectedly compiled")
                return compile_result
            self.assertEqual(compile_result.returncode, 0, compile_result.stdout + compile_result.stderr)
            return subprocess.run([str(binary)], capture_output=True, text=True, timeout=10)

    def test_actual_invitation_lifecycle_and_authority_guards(self):
        result = self.compile_and_run(self.production_program())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_direct_protected_field_access_is_rejected_by_compiler(self):
        program = self.production_program().replace(
            "Mode->GetBattleActorClass()", "Mode->BattleActorClass.Get()", 1)
        result = self.compile_and_run(program, expect_compile_success=False)
        self.assertIn("protected", result.stderr)

    def test_both_unranked_spawns_use_read_only_public_accessor(self):
        header = (PUBLIC / "DigimonVenomNXTGameMode.h").read_text(encoding="utf-8")
        public, protected = header.split("protected:", 1)
        self.assertIn("UClass* GetBattleActorClass() const;", public)
        self.assertIn("TSubclassOf<ADigimonVenomNXTBattleActor> BattleActorClass;", protected.split("private:", 1)[0])
        source = (PRIVATE / "DigimonVenomNXTUnrankedComponent.cpp").read_text(encoding="utf-8")
        for name in ("ServerRespond_Implementation", "ServerChallengeRival_Implementation"):
            body = method(source, "UDigimonVenomNXTUnrankedComponent::" + name + "(")
            self.assertIn("Mode ? Mode->GetBattleActorClass() : ADigimonVenomNXTBattleActor::StaticClass()", body)
            self.assertNotIn("Mode->BattleActorClass", body)

    def test_missing_expiry_guard_is_detected(self):
        program = self.production_program().replace(
            "FDateTime::UtcNow().ToUnixTimestamp() >= IncomingChallenge.ExpiresUnix || ", "", 1)
        result = self.compile_and_run(program)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("expiry boundary accepted", result.stderr)

    def test_owned_components_and_rpc_implementations_are_registered(self):
        controller = (PRIVATE / "DigimonVenomNXTPlayerController.cpp").read_text(encoding="utf-8")
        for family in ("Social", "Trade", "Unranked"):
            name = "UDigimonVenomNXT" + family + "Component"
            self.assertIn("CreateDefaultSubobject<" + name + ">", controller)
            header = (PUBLIC / ("DigimonVenomNXT" + family + "Component.h")).read_text(encoding="utf-8")
            source = (PRIVATE / ("DigimonVenomNXT" + family + "Component.cpp")).read_text(encoding="utf-8")
            self.assertIn("SetIsReplicatedByDefault(true)", source)
            for rpc in re.findall(r"UFUNCTION\([^)]*(?:Server|Client)[^)]*\)\s*void\s+(\w+)\s*\(", header):
                self.assertEqual(source.count(name + "::" + rpc + "_Implementation("), 1, rpc)
            for line in source.splitlines():
                if "DOREPLIFETIME" in line:
                    self.assertIn("COND_OwnerOnly", line)

    def test_text_navigation_and_confirmation_capture_source_contracts(self):
        controller = (PRIVATE / "DigimonVenomNXTPlayerController.cpp").read_text(encoding="utf-8")
        tick = method(controller, "ADigimonVenomNXTPlayerController::Tick(")
        shortcut_gate = re.search(r"const bool bMenuOwnsShortcuts = ([^;]+);", tick).group(1)
        self.assertIn("GameHUDWidget->IsCommunityOpen()", shortcut_gate)
        self.assertIn("if (!bMenuOwnsShortcuts && (WasInputKeyJustPressed(EKeys::M) || WasInputKeyJustPressed(EKeys::Tab)))", tick)
        self.assertLess(tick.index("GameHUDWidget->HandleCommunityBack()"), tick.index("SetFieldMenuOpen(false)"))
        ui = (PRIVATE / "DigimonVenomNXTCommunityWidget.cpp").read_text(encoding="utf-8")
        action = method(ui, "UDigimonVenomNXTCommunityWidget::HandleAction(")
        self.assertIn("FAction Confirmed=PendingAction", action)
        self.assertIn("Confirmed.Text!=ExpectedConfirmationName", action)
        execute = method(ui, "UDigimonVenomNXTCommunityWidget::Execute(")
        self.assertIn("ServerConfirmPurchase(A.Id)", execute)
        self.assertIn("ServerConfirmTrade(A.Id,A.Revision)", execute)
        self.assertIn("S.SessionId!=A.Id||S.Revision!=A.Revision", execute)
        ask = method(ui, "UDigimonVenomNXTCommunityWidget::Ask(")
        self.assertIn("PendingAction=A", ask)

    def test_identity_lookup_returns_only_unique_authority_owned_identity(self):
        auth = (PRIVATE / "DigimonVenomNXTAuthSubsystem.cpp").read_text(encoding="utf-8")
        body = method(auth, "UDigimonVenomNXTAuthSubsystem::GetAccountIdentity(")
        self.assertIn("GetWorld()->GetNetMode() == NM_Client", body)
        self.assertIn("Query.Len() > 128", body)
        self.assertIn("Matches == 1", body)
        self.assertIn("OutUsername.Reset(); OutAccountId.Reset();", body)
        self.assertNotIn("RequireLocalHostConsole", body)
        self.assertNotIn("Password", body)
        self.assertNotIn("PasswordHash", body)


if __name__ == "__main__":
    unittest.main()
