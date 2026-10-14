#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTServerConsoleCore.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTProfileSubsystem.h"
#include "DigimonVenomNXTTradeSubsystem.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTAutoBattle.h"
#include "DigimonVenomNXTProgressionCore.h"
#include "DigimonVenomNXTStarterCore.h"
#include "DigimonVenomNXTEvolution.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "DigimonVenomNXTBattleActor.h"
#include "DigimonVenomNXTAIRivalSubsystem.h"
#include "DigimonVenomNXTRankedSubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Engine/NetConnection.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/Pawn.h"
#include "HAL/PlatformMemory.h"
#include "JsonObjectConverter.h"
#include "Misc/SecureHash.h"
#include "Misc/PackageName.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

namespace DigimonServerCommandsPrivate
{
FString Canonical(FString Value)
{
    Value.RemoveFromStart(TEXT("/")); Value = Value.ToLower();
    const TMap<FString, FString> Aliases = {
        {TEXT("digimon"),TEXT("digimon")},{TEXT("digimoninfo"),TEXT("digimoninfo")},{TEXT("givedigimon"),TEXT("givedigimon")},
        {TEXT("removedigimon"),TEXT("removedigimon")},{TEXT("clonedigimon"),TEXT("clonedigimon")},{TEXT("addmoney"),TEXT("givemoney")},
        {TEXT("balance"),TEXT("money")},{TEXT("setfriendshiplevel"),TEXT("setcam")},
        {TEXT("setparadoxdigimon"),TEXT("setparadox")},{TEXT("setshinydigimon"),TEXT("setshiny")},{TEXT("setfirewalldigimon"),TEXT("setfirewall")}};
    if (const FString* Alias = Aliases.Find(Value)) return *Alias; return Value;
}
bool Number(const FString& Text, int64 Minimum, int64 Maximum, int64& Out)
{
    std::int64_t Value = 0;
    if (!DigimonVenomNXTServerConsoleCore::UnsignedDecimal(TCHAR_TO_UTF8(*Text), Maximum, Value) || Value < Minimum) return false;
    Out = Value; return true;
}
bool Parse(const FString& Input, TArray<FString>& Args, FString& Error)
{
    std::vector<std::string> Values; std::string Failure;
    if (!DigimonVenomNXTServerConsoleCore::Tokenize(TCHAR_TO_UTF8(*Input), Values, Failure)) { Error = UTF8_TO_TCHAR(Failure.c_str()); return false; }
    for (const std::string& Value : Values) Args.Add(UTF8_TO_TCHAR(Value.c_str()));
    if (Args[0].Equals(TEXT("/set"), ESearchCase::IgnoreCase) || Args[0].Equals(TEXT("set"), ESearchCase::IgnoreCase))
    {
        if (Args.Num() < 2) { Error = TEXT("Use /set paradoxdigimon|shinydigimon|firewalldigimon <player> <partner> [true|false]."); return false; }
        Args[0] = TEXT("set") + Args[1]; Args.RemoveAt(1);
    }
    Args[0] = Canonical(Args[0]); return true;
}
FString Quoted(const TArray<FString>& Args)
{
    TArray<FString> Result;
    for (FString Part : Args) { Part.ReplaceInline(TEXT("\\"), TEXT("\\\\")); Part.ReplaceInline(TEXT("\""), TEXT("\\\"")); Result.Add(TEXT("\"") + Part + TEXT("\"")); }
    return FString::Join(Result, TEXT(" "));
}
FString VariantName(EDigimonVariant Variant)
{
    switch (Variant) { case EDigimonVariant::Paradox:return TEXT("Paradox"); case EDigimonVariant::Shiny:return TEXT("Shiny"); case EDigimonVariant::Firewall:return TEXT("Firewall"); default:return TEXT("Normal"); }
}
bool Variant(const FString& Text, EDigimonVariant& Out)
{
    if (Text.Equals(TEXT("normal"),ESearchCase::IgnoreCase)) Out=EDigimonVariant::Normal;
    else if (Text.Equals(TEXT("paradox"),ESearchCase::IgnoreCase)) Out=EDigimonVariant::Paradox;
    else if (Text.Equals(TEXT("shiny"),ESearchCase::IgnoreCase)) Out=EDigimonVariant::Shiny;
    else if (Text.Equals(TEXT("firewall"),ESearchCase::IgnoreCase)) Out=EDigimonVariant::Firewall;
    else return false; return true;
}
bool Species(const UDigimonVenomNXTDataSubsystem* Data, const FString& Query, FDigimonSpeciesDefinition& Out, FString& Error)
{
    if (!Data) { Error=TEXT("Species data is unavailable."); return false; }
    int32 Matches = 0;
    for (const FDigimonSpeciesDefinition& Entry : Data->GetAllSpecies())
        if (!Entry.bPlaceholder && (Entry.SpeciesId.ToString().Equals(Query, ESearchCase::IgnoreCase) || Entry.DisplayName.ToString().Equals(Query, ESearchCase::IgnoreCase))) { Out=Entry; ++Matches; }
    if (Matches != 1) { Error=Matches ? TEXT("Ambiguous species name. Use its exact species ID.") : TEXT("Unknown playable species. Use an exact species ID or a quoted full name."); return false; }
    return true;
}
int32 PartnerIndex(const FDigimonPlayerProfile& Profile, const FString& Query, const UDigimonVenomNXTDataSubsystem* Data, FString& Error)
{
    FString Prefix, Suffix; int64 Slot=0;
    if (Query.Split(TEXT(":"), &Prefix, &Suffix) && (Prefix.Equals(TEXT("party"),ESearchCase::IgnoreCase) || Prefix.Equals(TEXT("storage"),ESearchCase::IgnoreCase)))
    {
        if (!Number(Suffix,1,10000,Slot)) { Error=TEXT("Partner slots start at 1. Use party:1 or storage:1."); return INDEX_NONE; }
        TArray<FGuid> IDs;
        if (Prefix.Equals(TEXT("party"),ESearchCase::IgnoreCase)) IDs=Profile.Party;
        else for (const FDigimonOwnedPartner& Entry : Profile.Collection) if (!Profile.Party.Contains(Entry.InstanceId)) IDs.Add(Entry.InstanceId);
        if (Slot > IDs.Num()) { Error=TEXT("That partner slot is empty."); return INDEX_NONE; }
        const FGuid Id=IDs[static_cast<int32>(Slot)-1];
        return Profile.Collection.IndexOfByPredicate([&](const FDigimonOwnedPartner& Entry){return Entry.InstanceId==Id;});
    }
    FGuid Id;
    if (FGuid::Parse(Query,Id))
    {
        const int32 Index=Profile.Collection.IndexOfByPredicate([&](const FDigimonOwnedPartner& Entry){return Entry.InstanceId==Id;});
        if (Index==INDEX_NONE) Error=TEXT("That partner ID is not owned by this account."); return Index;
    }
    int32 Found=INDEX_NONE;
    for (int32 Index=0;Index<Profile.Collection.Num();++Index)
    {
        const FDigimonOwnedPartner& Entry=Profile.Collection[Index]; FDigimonSpeciesDefinition Definition;
        if (Entry.SpeciesId.ToString().Equals(Query,ESearchCase::IgnoreCase) || (!Entry.Nickname.IsEmpty() && Entry.Nickname.Equals(Query,ESearchCase::IgnoreCase)) || (Data && Data->GetSpecies(Entry.SpeciesId,Definition) && Definition.DisplayName.ToString().Equals(Query,ESearchCase::IgnoreCase)))
        { if (Found!=INDEX_NONE) {Error=TEXT("More than one partner matches. Use /digimon then its GUID, party:N or storage:N.");return INDEX_NONE;} Found=Index; }
    }
    if (Found==INDEX_NONE) Error=TEXT("Partner not found. Use /digimon <player> for exact selectors."); return Found;
}
void RefreshVitals(FDigimonOwnedPartner& Partner, const FDigimonBattleUnit& Before, const UDigimonVenomNXTDataSubsystem* Data)
{
    const FDigimonBattleUnit After=DigimonVenomNXTAutoBattle::BuildUnit(Partner,Data);
    Partner.CurrentHP=Before.HP<=0 ? 0 : FMath::Clamp(After.Stats.MaxHP-FMath::Max(0,Before.Stats.MaxHP-Before.HP),1,After.Stats.MaxHP);
    Partner.CurrentSP=FMath::Clamp(After.Stats.MaxSP-FMath::Max(0,Before.Stats.MaxSP-Before.SP),0,After.Stats.MaxSP);
    Partner.Moves=After.Moves; Partner.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
}
void Observe(FDigimonPlayerProfile& Profile, const FDigimonOwnedPartner& Partner)
{
    FDigimonScanRecord* Record=Profile.Scans.FindByPredicate([&](const FDigimonScanRecord& Value){return Value.SpeciesId==Partner.SpeciesId&&Value.Variant==Partner.Variant;});
    if (!Record) {FDigimonScanRecord New;New.SpeciesId=Partner.SpeciesId;New.Variant=Partner.Variant;Profile.Scans.Add(New);Record=&Profile.Scans.Last();}
    DigimonVenomNXTScanCore::Observe(*Record,GetDefault<UDigimonVenomNXTSettings>()->ScanCapPercent,true);
}
bool Duration(const FString& Text,int64& Until)
{
    if (Text.Equals(TEXT("permanent"),ESearchCase::IgnoreCase)) {Until=-1;return true;}
    FString Digits=Text;int64 Multiplier=60;
    if (Digits.EndsWith(TEXT("m"))) Digits.LeftChopInline(1);
    else if (Digits.EndsWith(TEXT("h"))) {Digits.LeftChopInline(1);Multiplier=3600;}
    else if (Digits.EndsWith(TEXT("d"))) {Digits.LeftChopInline(1);Multiplier=86400;}
    int64 Value=0;if(!Number(Digits,1,315360000/Multiplier,Value))return false;
    Until=FDateTime::UtcNow().ToUnixTimestamp()+Value*Multiplier;return true;
}
}

void UDigimonVenomNXTServerConsoleSubsystem::BuildRegistry()
{
    const auto Add=[&](const TCHAR* Name,const TCHAR* Usage,const TCHAR* Description,bool Confirm=false){FDigimonServerCommandInfo Item;Item.Name=Name;Item.Usage=Usage;Item.Description=Description;Item.bRequiresConfirmation=Confirm;Registry.Add(Item);};
    Add(TEXT("help"),TEXT("/help [command]"),TEXT("Read command syntax and aliases. Quoted names and text are supported."));
    Add(TEXT("permissions"),TEXT("/permissions"),TEXT("Show the local host-only access policy."));
    Add(TEXT("players"),TEXT("/players"),TEXT("List authenticated online players and account IDs."));
    Add(TEXT("broadcast"),TEXT("/broadcast \"message\""),TEXT("Send a host notice to all authenticated players."));
    Add(TEXT("digimon"),TEXT("/digimon <player>"),TEXT("Inspect collection GUIDs and party/storage selectors. Alias: /digimon."));
    Add(TEXT("team"),TEXT("/team <player>"),TEXT("Inspect the current party."));
    Add(TEXT("bag"),TEXT("/bag <player>"),TEXT("Inspect inventory item IDs and quantities."));
    Add(TEXT("digimoninfo"),TEXT("/digimoninfo <species>"),TEXT("Inspect a real species, stats and linked evolution routes."));
    Add(TEXT("givedigimon"),TEXT("/givedigimon <player> <species> [level] [normal|paradox|shiny|firewall]"),TEXT("Grant a valid partner to party space, then storage. Alias: /givedigimon."));
    Add(TEXT("removedigimon"),TEXT("/removedigimon <player> <partner>"),TEXT("Remove one exact partner; never remove the final party member."),true);
    Add(TEXT("heal"),TEXT("/heal <player>"),TEXT("Restore party HP and SP outside live or saved battles."));
    Add(TEXT("healall"),TEXT("/healall"),TEXT("Heal eligible online parties; busy/save-failed accounts are reported."));
    Add(TEXT("evolve"),TEXT("/evolve <player> <partner> [target]"),TEXT("Force a real forward route, reset level to 1 and apply route ABI gain."));
    Add(TEXT("devolve"),TEXT("/devolve <player> <partner> [target]"),TEXT("Force a real reverse route, reset level to 1 and apply route ABI gain."));
    Add(TEXT("setlevel"),TEXT("/setlevel <player> <partner> <level>"),TEXT("Set level within the project limit and reset progress within that level."));
    Add(TEXT("setexp"),TEXT("/setexp <player> <partner> <within-level XP>"),TEXT("Set XP within the current level, below its next-level threshold."));
    Add(TEXT("setabi"),TEXT("/setabi <player> <partner> <0-200>"),TEXT("Set ABI without replacing partner identity or training."));
    Add(TEXT("setcam"),TEXT("/setcam <player> <partner> <0-100>"),TEXT("Set friendship. Alias: /setfriendshiplevel."));
    Add(TEXT("setparadox"),TEXT("/setparadox <player> <partner> [true|false]"),TEXT("Set Paradox/Normal. Also /setparadoxdigimon or /set paradoxdigimon."));
    Add(TEXT("setshiny"),TEXT("/setshiny <player> <partner> [true|false]"),TEXT("Set Shiny/Normal. Also /setshinydigimon or /set shinydigimon."));
    Add(TEXT("setfirewall"),TEXT("/setfirewall <player> <partner> [true|false]"),TEXT("Set Firewall/Normal. Also /setfirewalldigimon or /set firewalldigimon."));
    Add(TEXT("clonedigimon"),TEXT("/clonedigimon <player> <partner>"),TEXT("Copy a partner with a new identity. Alias: /clonedigimon."));
    Add(TEXT("giveitem"),TEXT("/giveitem <player> <item> <amount>"),TEXT("Add a real shop item, capped at 999 per item."));
    Add(TEXT("removeitem"),TEXT("/removeitem <player> <item> <amount>"),TEXT("Remove an owned item quantity; never go negative."));
    Add(TEXT("setitem"),TEXT("/setitem <player> <item> <0-999>"),TEXT("Set a real shop item quantity."));
    Add(TEXT("clearinventory"),TEXT("/clearinventory <player>"),TEXT("Clear a bag after a profile-bound confirmation."),true);
    Add(TEXT("money"),TEXT("/money <player>"),TEXT("Inspect Credits and DigiRubies. Alias: /balance."));
    Add(TEXT("givemoney"),TEXT("/givemoney <player> <amount>"),TEXT("Add Credits with overflow protection. Alias: /addmoney."));
    Add(TEXT("removemoney"),TEXT("/removemoney <player> <amount>"),TEXT("Remove Credits without a negative balance."));
    Add(TEXT("setmoney"),TEXT("/setmoney <player> <amount>"),TEXT("Set Credits exactly, with a 9 trillion safety cap."));
    Add(TEXT("teleportplayer"),TEXT("/teleportplayer <player> <public-map-id>"),TEXT("Move an online public-world player to a validated safe map spawn."));
    Add(TEXT("spawn"),TEXT("/spawn <player> <species> [level] [variety]"),TEXT("Start a real targeted wild battle in the public field."));
    Add(TEXT("warn"),TEXT("/warn <player> \"reason\""),TEXT("Persist a warning and notify the player."));
    Add(TEXT("warnings"),TEXT("/warnings <player>"),TEXT("Show the latest 20 persisted warnings."));
    Add(TEXT("kick"),TEXT("/kick <player> [\"reason\"]"),TEXT("Save and disconnect an online non-host player."));
    Add(TEXT("ban"),TEXT("/ban <player> <10m|2h|7d|permanent> \"reason\""),TEXT("Confirm a durable account ban; save and disconnect the player."),true);
    Add(TEXT("unban"),TEXT("/unban <player>"),TEXT("Remove an account ban."));
    Add(TEXT("jail"),TEXT("/jail <player> <10m|2h|7d|permanent> \"reason\""),TEXT("Suspend gameplay in place; retains private sessions and progress. Finish battles first."));
    Add(TEXT("unjail"),TEXT("/unjail <player>"),TEXT("Release gameplay suspension at the retained location."));
    Add(TEXT("mute"),TEXT("/mute <player> <10m|2h|7d|permanent> \"reason\""),TEXT("Temporarily or permanently mute local chat."));
    Add(TEXT("unmute"),TEXT("/unmute <player>"),TEXT("Restore local chat."));
    Add(TEXT("ipinfo"),TEXT("/ipinfo <player>"),TEXT("Inspect an online player's endpoint locally; not added to activity logs."));
    Add(TEXT("createaccount"),TEXT("/createaccount <username>"),TEXT("Open the masked password form to create a host-owned account."));
    Add(TEXT("deleteaccount"),TEXT("/deleteaccount <username>"),TEXT("Permanently delete an offline non-host account and profile after confirmation."),true);
    Add(TEXT("resetpassword"),TEXT("/resetpassword <username>"),TEXT("Open the masked password form for an offline non-host account."));
    Add(TEXT("confirm"),TEXT("/confirm <token>"),TEXT("Confirm one unchanged pending action within 30 seconds; token is single use."));
    Add(TEXT("cancel"),TEXT("/cancel"),TEXT("Discard the pending destructive action."));
    Add(TEXT("memory"),TEXT("/memory"),TEXT("Show process memory usage."));
    Add(TEXT("saveall"),TEXT("/saveall"),TEXT("Checkpoint online/disconnected profiles, commerce, ranked, social and AI rivals; report failures."));
    Add(TEXT("shutdown"),TEXT("/shutdown [0-300 seconds|cancel]"),TEXT("Confirm a saved server closure and return the host to login."),true);
    Add(TEXT("restart"),TEXT("/restart [0-300 seconds|cancel]"),TEXT("Confirm a saved world reload; remote players reconnect."),true);
    Add(TEXT("addtitle"),TEXT("/addtitle \"title\""),TEXT("Create a reusable server title of 1-32 printable characters."));
    Add(TEXT("titles"),TEXT("/titles [player]"),TEXT("List the server catalog or an account's unlocked and equipped titles."));
    Add(TEXT("settitle"),TEXT("/settitle <player> \"title|none\""),TEXT("Grant and equip a catalog title, or clear the displayed title."));
}

FString UDigimonVenomNXTServerConsoleSubsystem::ConfirmationFingerprint(const TArray<FString>& Args) const
{
    FString Value=DigimonServerCommandsPrivate::Quoted(Args);
    if (Args.Num()>1)
    {
        FDigimonPlayerProfile Profile;ADigimonVenomNXTPlayerState* Live=nullptr;FString Error;
        if (ResolveTarget(Args[1],Profile,Live,Error)) {FString Json;FJsonObjectConverter::UStructToJsonObjectString(Profile,Json);Value+=Json;}
    }
    uint8 Hash[20];const FTCHARToUTF8 UTF8(*Value);FSHA1::HashBuffer(UTF8.Get(),UTF8.Length(),Hash);return BytesToHex(Hash,20);
}
bool UDigimonVenomNXTServerConsoleSubsystem::PrepareConfirmation(const TArray<FString>& Args,const FString& Fingerprint,FString& OutResponse)
{
    PendingCommand=DigimonServerCommandsPrivate::Quoted(Args);PendingFingerprint=Fingerprint;
    PendingToken=FGuid::NewGuid().ToString(EGuidFormats::Digits).Left(8);PendingUntil=FPlatformTime::Seconds()+30.0;
    OutResponse=TEXT("Review: ")+PendingCommand+TEXT(". Type /confirm ")+PendingToken+TEXT(" within 30 seconds, or /cancel. Any changed target requires a new confirmation.");return true;
}
bool UDigimonVenomNXTServerConsoleSubsystem::ExecuteCommand(APlayerController* Requester,const FString& Command,FString& OutResponse)
{
    OutResponse.Reset();if(!CanAccess(Requester)){OutResponse=TEXT("Only the authenticated local host can use the world console.");return false;}
    TArray<FString> Args;if(!DigimonServerCommandsPrivate::Parse(Command,Args,OutResponse))return false;
    bool Success=false;
    if(Args[0]==TEXT("confirm"))
    {
        const bool HadPending=!PendingToken.IsEmpty();
        const bool TokenMatched=Args.Num()==2&&Args[1]==PendingToken;
        const double Expiry=PendingUntil;
        TArray<FString> Confirmed;FString Error;const FString SavedCommand=PendingCommand,SavedFingerprint=PendingFingerprint;
        PendingCommand.Reset();PendingToken.Reset();PendingFingerprint.Reset();PendingUntil=0;
        const bool Parsed=HadPending&&TokenMatched&&DigimonServerCommandsPrivate::Parse(SavedCommand,Confirmed,Error);
        const bool SameTarget=Parsed&&ConfirmationFingerprint(Confirmed)==SavedFingerprint;
        if(!DigimonVenomNXTServerConsoleCore::ConfirmationAllowed(HadPending,TokenMatched,FPlatformTime::Seconds(),Expiry,SameTarget))
        {OutResponse=TEXT("Confirmation is invalid, expired, or the target changed. Nothing was changed. Enter the original command to review it again.");return false;}
        Success=RunCommand(Requester,Confirmed,OutResponse,true);Args=MoveTemp(Confirmed);
    }
    else if(Args[0]==TEXT("cancel")) {PendingCommand.Reset();PendingToken.Reset();PendingFingerprint.Reset();OutResponse=TEXT("Pending confirmation cancelled.");return true;}
    else Success=RunCommand(Requester,Args,OutResponse,false);
    // Never echo raw arguments: endpoints, passwords, quoted messages and confirmation tokens stay out of the activity stream.
    RecordActivity(TEXT("Admin"),HostAccountId,TEXT("/")+Args[0],Success?TEXT("Command completed; result shown only in host console."):TEXT("Command rejected; details shown only in host console."),Success?TEXT("Info"):TEXT("Warning"));
    return Success;
}
bool UDigimonVenomNXTServerConsoleSubsystem::ExecuteSensitiveCommand(APlayerController* Requester,const FString& Verb,const FString& Username,const FString& Password,FString& OutResponse)
{
    if(!CanAccess(Requester)){OutResponse=TEXT("Host console access is required.");return false;}
    const FString Command=DigimonServerCommandsPrivate::Canonical(Verb);
    UDigimonVenomNXTAuthSubsystem* Auth=GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    bool Success=false;
    if(!Auth){OutResponse=TEXT("Account service is unavailable.");return false;}
    if(Command==TEXT("createaccount")) Success=Auth->AdminCreateAccount(Username,Password,OutResponse);
    else if(Command==TEXT("resetpassword")) Success=Auth->AdminResetPassword(Username,Password,OutResponse);
    else{OutResponse=TEXT("This form only accepts account creation or password reset.");return false;}
    if(Success)OutResponse=Command==TEXT("createaccount")?TEXT("Account created. The player may now sign in."):TEXT("Password changed. The player may sign in with the new password.");
    RecordActivity(TEXT("Accounts"),Username,Command,Success?TEXT("Secure account operation saved."):TEXT("Secure account operation rejected."),Success?TEXT("Info"):TEXT("Warning"));
    return Success;
}

bool UDigimonVenomNXTServerConsoleSubsystem::RunCommand(APlayerController* Requester,const TArray<FString>& A,FString& Out,bool bConfirmed)
{
    using namespace DigimonServerCommandsPrivate;
    if(!CanAccess(Requester)||A.IsEmpty()){Out=TEXT("Host access was revoked.");return false;}
    const FString& C=A[0];
    const FDigimonServerCommandInfo* Info=Registry.FindByPredicate([&](const FDigimonServerCommandInfo& Value){return Value.Name==C;});
    if(!Info){Out=TEXT("Unknown command. Use /help for the supported host commands.");return false;}
    const auto Usage=[&](){Out=TEXT("Usage: ")+Info->Usage;return false;};
    UDigimonVenomNXTDataSubsystem* Data=GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>();
    UDigimonVenomNXTProfileSubsystem* Profiles=GetGameInstance()->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    const int32 MaxLevel=DigimonVenomNXTProgressionCore::MaximumLevel(GetDefault<UDigimonVenomNXTSettings>()->MaxPartnerLevel);
    if(C==TEXT("help"))
    {
        if(A.Num()>2)return Usage();
        if(A.Num()==2){const FString Name=Canonical(A[1]);for(const FDigimonServerCommandInfo& Entry:Registry)if(Entry.Name==Name){Out=Entry.Usage+TEXT("\n")+Entry.Description;return true;}Out=TEXT("Unknown command. Use /help.");return false;}
        TArray<FString> Lines;for(const FDigimonServerCommandInfo& Entry:Registry)Lines.Add(Entry.Usage+TEXT(" — ")+Entry.Description);
        Out=TEXT("Host commands · exact usernames/account IDs; quote names with spaces. Partners: GUID, party:N, storage:N or unique full name.\n")+FString::Join(Lines,TEXT("\n"));return true;
    }
    if(C==TEXT("permissions")){if(A.Num()!=1)return Usage();Out=TEXT("Local listen-server host: full native host console access. Remote players, chat messages, clients and split-screen guests cannot read or execute console commands.");return true;}
    if(C==TEXT("players"))
    {
        if(A.Num()!=1)return Usage();TArray<FString> Lines;
        for(FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator();It;++It){const ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(It->Get());const ADigimonVenomNXTPlayerState* PS=PC?PC->GetPlayerState<ADigimonVenomNXTPlayerState>():nullptr;if(PS&&PC->IsAccountAuthenticated())Lines.Add(FString::Printf(TEXT("%s | %s | map %d%s%s"),*PS->Profile.Username,*PS->Profile.AccountId,PS->Profile.CurrentMapId,PC->IsInDigiFarm()?TEXT(" | DigiFarm"):PC->IsInRelay()?TEXT(" | private campaign"):TEXT(""),PC->CurrentBattle?TEXT(" | battle"):TEXT("")));}
        Out=FString::Printf(TEXT("%d authenticated player(s)\n"),Lines.Num())+FString::Join(Lines,TEXT("\n"));return true;
    }
    if(C==TEXT("broadcast"))
    {
        if(A.Num()!=2||A[1].IsEmpty()||A[1].Len()>256)return Usage();int32 Count=0;
        for(FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator();It;++It)if(ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(It->Get()))if(PC->IsAccountAuthenticated()){PC->ClientShowMessage(TEXT("Host announcement"),A[1]);++Count;}
        Out=FString::Printf(TEXT("Announcement delivered to %d player(s)."),Count);return true;
    }
    if(C==TEXT("memory")){if(A.Num()!=1)return Usage();const FPlatformMemoryStats Stats=FPlatformMemory::GetStats();Out=FString::Printf(TEXT("Process physical memory %.1f MiB | peak %.1f MiB | system available %.1f MiB"),Stats.UsedPhysical/1048576.0,Stats.PeakUsedPhysical/1048576.0,Stats.AvailablePhysical/1048576.0);return true;}
    if(C==TEXT("saveall")){if(A.Num()!=1)return Usage();return SaveAll(Out);}
    if(C==TEXT("shutdown")||C==TEXT("restart"))
    {
        if(A.Num()>2)return Usage();
        if(A.Num()==2&&A[1].Equals(TEXT("cancel"),ESearchCase::IgnoreCase)){GetWorld()->GetTimerManager().ClearTimer(LifecycleTimer);PendingCommand.Reset();PendingToken.Reset();Out=TEXT("Scheduled server action cancelled.");return true;}
        int64 Delay=0;if(A.Num()==2&&!Number(A[1],0,300,Delay))return Usage();
        if(!bConfirmed)return PrepareConfirmation(A,ConfirmationFingerprint(A),Out);
        bRestartScheduled=C==TEXT("restart");
        GetWorld()->GetTimerManager().SetTimer(LifecycleTimer,this,&UDigimonVenomNXTServerConsoleSubsystem::FinishLifecycle,FMath::Max(0.25f,static_cast<float>(Delay)),false);
        for(FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator();It;++It)if(ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(It->Get()))if(PC->IsAccountAuthenticated())PC->ClientShowMessage(TEXT("Server notice"),FString::Printf(TEXT("The host scheduled a server %s in %lld second(s). Progress will be saved. Finish your battle; unsafe closure will be cancelled."),bRestartScheduled?TEXT("restart"):TEXT("closure"),Delay));
        Out=TEXT("Scheduled. Use /")+C+TEXT(" cancel to cancel. The operation aborts if saving or battle checkpointing fails.");return true;
    }
    if(C==TEXT("createaccount")||C==TEXT("resetpassword")){if(A.Num()!=2)return Usage();Out=TEXT("Use the secure password form in this native console. Passwords are never accepted in the command line.");return false;}
    if(C==TEXT("addtitle"))
    {
        if(A.Num()!=2||A[1].TrimStartAndEnd().IsEmpty()||A[1].Len()>32)return Usage();if(!Moderation){Out=TEXT("Moderation data is unavailable.");return false;}
        if(A[1].Equals(TEXT("none"),ESearchCase::IgnoreCase)){Out=TEXT("The title 'none' is reserved for clearing a title.");return false;}
        if(Moderation->Titles.ContainsByPredicate([&](const FString& Value){return Value.Equals(A[1],ESearchCase::IgnoreCase);})){Out=TEXT("That title is already in the server catalog.");return false;}
        if(Moderation->Titles.Num()>=512){Out=TEXT("The server title catalog is full (512 titles).");return false;}
        UDigimonVenomNXTServerModerationSaveGame* Candidate=DuplicateObject<UDigimonVenomNXTServerModerationSaveGame>(Moderation,this);Candidate->Titles.Add(A[1].TrimStartAndEnd());if(!SaveModeration(Candidate,Out))return false;Out=TEXT("Title added: ")+A[1]+TEXT(". Equip it with /settitle <player> \"")+A[1]+TEXT("\".");return true;
    }
    if(C==TEXT("titles")&&A.Num()==1){Out=Moderation?FString::Join(Moderation->Titles,TEXT("\n")):TEXT("");if(Out.IsEmpty())Out=TEXT("No catalog titles yet. Use /addtitle \"title\".");return true;}
    if(C==TEXT("digimoninfo"))
    {
        if(A.Num()!=2)return Usage();FDigimonSpeciesDefinition S;if(!Species(Data,A[1],S,Out))return false;
        TArray<FString> Routes;for(const FDigimonEvolutionRequirement& R:S.Evolutions)Routes.Add(R.TargetSpeciesId.ToString());
        Out=FString::Printf(TEXT("%s [%s]\nBase HP %d | SP %d | ATK %d | DEF %d | INT %d | SPD %d\nEvolution routes: %s"),*S.DisplayName.ToString(),*S.SpeciesId.ToString(),S.BaseStats.MaxHP,S.BaseStats.MaxSP,S.BaseStats.Attack,S.BaseStats.Defense,S.BaseStats.Spirit,S.BaseStats.Speed,*FString::Join(Routes,TEXT(", ")));return true;
    }
    if(C==TEXT("healall"))
    {
        if(A.Num()!=1)return Usage();int32 Saved=0,Skipped=0;TArray<FString> Lines;
        for(FConstPlayerControllerIterator It=GetWorld()->GetPlayerControllerIterator();It;++It)
        {
            ADigimonVenomNXTPlayerController* PC=Cast<ADigimonVenomNXTPlayerController>(It->Get());ADigimonVenomNXTPlayerState* PS=PC?PC->GetPlayerState<ADigimonVenomNXTPlayerState>():nullptr;if(!PS||!PC->IsAccountAuthenticated())continue;
            FDigimonPlayerProfile Candidate=PS->Profile;FString Error;if(!RequireMutable(Candidate,PS,Error)){++Skipped;Lines.Add(PS->Profile.Username+TEXT(": ")+Error);continue;}
            for(FDigimonOwnedPartner& P:Candidate.Collection)if(Candidate.Party.Contains(P.InstanceId)){const FDigimonBattleUnit Unit=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);P.CurrentHP=Unit.Stats.MaxHP;P.CurrentSP=Unit.Stats.MaxSP;}
            if(CommitProfile(Candidate,PS,Error)){++Saved;RecordActivity(TEXT("Admin"),PS->Profile.Username,TEXT("/healall"),TEXT("Party healed and saved."));}else{++Skipped;Lines.Add(PS->Profile.Username+TEXT(": ")+Error);}
        }
        Out=FString::Printf(TEXT("Healed and saved %d account(s); skipped %d.\n"),Saved,Skipped)+FString::Join(Lines,TEXT("\n"));return Skipped==0;
    }
    if(A.Num()<2)return Usage();
    FDigimonPlayerProfile Candidate;ADigimonVenomNXTPlayerState* Live=nullptr;if(!ResolveTarget(A[1],Candidate,Live,Out))return false;
    ADigimonVenomNXTPlayerController* PC=Live?Cast<ADigimonVenomNXTPlayerController>(Live->GetOwner()):nullptr;
    const FString TargetName=Candidate.Username;
    if(C==TEXT("money")){if(A.Num()!=2)return Usage();Out=FString::Printf(TEXT("%s: %lld Credits | %d DigiRubies"),*TargetName,Candidate.Credits,Candidate.DigiRubies);return true;}
    if(C==TEXT("bag")){if(A.Num()!=2)return Usage();TArray<FString> Lines;for(const FDigimonInventoryEntry& E:Candidate.Inventory)Lines.Add(FString::Printf(TEXT("%s x%d"),*E.ItemId.ToString(),E.Quantity));Out=TargetName+TEXT(" · inventory\n")+(Lines.IsEmpty()?TEXT("Empty."):FString::Join(Lines,TEXT("\n")));return true;}
    if(C==TEXT("titles")){if(A.Num()!=2)return Usage();Out=TargetName+TEXT(" · equipped: ")+(Candidate.EquippedTitle.IsEmpty()?TEXT("none"):Candidate.EquippedTitle)+TEXT("\nOwned: ")+FString::Join(Candidate.OwnedTitles,TEXT(", "));return true;}
    if(C==TEXT("team")||C==TEXT("digimon"))
    {
        if(A.Num()!=2)return Usage();TArray<FString> Lines;int32 Storage=0;
        for(const FDigimonOwnedPartner& P:Candidate.Collection){const int32 Party=Candidate.Party.IndexOfByKey(P.InstanceId);if(Party==INDEX_NONE)++Storage;if(C==TEXT("team")&&Party==INDEX_NONE)continue;const FDigimonBattleUnit Unit=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);Lines.Add(FString::Printf(TEXT("%s:%d | %s | %s %s Lv.%d | HP %d/%d SP %d/%d | ABI %d CAM %d"),Party==INDEX_NONE?TEXT("storage"):TEXT("party"),Party==INDEX_NONE?Storage:Party+1,*P.InstanceId.ToString(EGuidFormats::DigitsWithHyphens),*VariantName(P.Variant),*P.SpeciesId.ToString(),P.Level,P.CurrentHP,Unit.Stats.MaxHP,P.CurrentSP,Unit.Stats.MaxSP,P.ABI,P.CAM));}
        Out=TargetName+TEXT(" · ")+FString::FromInt(Lines.Num())+TEXT(" partner(s)\n")+FString::Join(Lines,TEXT("\n"));return true;
    }
    if(C==TEXT("ipinfo")){if(A.Num()!=2)return Usage();if(!PC){Out=TEXT("That account is offline.");return false;}UNetConnection* Connection=PC->GetNetConnection();Out=TargetName+TEXT(" · ")+(PC->IsLocalController()?TEXT("local host (no remote endpoint)"):Connection?Connection->LowLevelGetRemoteAddress(true):TEXT("Endpoint unavailable."));return true;}
    if(C==TEXT("warnings"))
    {
        if(A.Num()!=2)return Usage();const FDigimonServerModerationRecord* R=Moderation?Moderation->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& E){return E.AccountId==Candidate.AccountId;}):nullptr;Out=R&&!R->Warnings.IsEmpty()?FString::Join(R->Warnings,TEXT("\n")):TEXT("No recorded warnings.");return true;
    }
    if(C==TEXT("deleteaccount"))
    {
        if(A.Num()!=2)return Usage();if(Live||Candidate.AccountId==HostAccountId){Out=TEXT("Only offline non-host accounts can be deleted.");return false;}
        UDigimonVenomNXTTradeSubsystem* Trading=GetGameInstance()->GetSubsystem<UDigimonVenomNXTTradeSubsystem>();
        if(!Trading||Trading->HasAccountAssets(Candidate.AccountId)){Out=TEXT("Cancel this account's trading listings and resolve pending transfers before deleting the account.");return false;}
        UDigimonVenomNXTSocialSubsystem* Social=GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
        if(!Social||Social->HasClanMembership(Candidate.AccountId)){Out=TEXT("This account must leave or disband its clan before it can be deleted.");return false;}
        if(!RequireMutable(Candidate,Live,Out))return false;if(!bConfirmed)return PrepareConfirmation(A,ConfirmationFingerprint(A),Out);
        UDigimonVenomNXTAuthSubsystem* Auth=GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();if(!Auth||!Auth->AdminDeleteAccount(A[1],Out))return false;
        if(!Profiles||!Profiles->DeleteProfile(Candidate.AccountId)){Out=TEXT("The account login was deleted, but its inactive profile files could not be removed. Check save permissions before manually removing the orphaned profile.");return false;}
        Out=TEXT("Offline account and profile deleted: ")+TargetName;return true;
    }
    if(C==TEXT("kick"))
    {
        if(A.Num()<2||A.Num()>3)return Usage();if(!PC||Candidate.AccountId==HostAccountId){Out=TEXT("Choose an online non-host player.");return false;}
        ADigimonVenomNXTGameMode* GM=GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();if(!GM||!GM->GameSession||!GM->SavePlayer(Live)){Out=TEXT("Save failed; player was not disconnected.");return false;}
        const FString Reason=A.Num()==3?A[2]:TEXT("Disconnected by the host.");if(!GM->GameSession->KickPlayer(PC,FText::FromString(Reason))){Out=TEXT("The player could not be disconnected.");return false;}Out=TEXT("Saved and disconnected ")+TargetName;return true;
    }
    if(C==TEXT("warn")||C==TEXT("ban")||C==TEXT("unban")||C==TEXT("jail")||C==TEXT("unjail")||C==TEXT("mute")||C==TEXT("unmute"))
    {
        if(!Moderation){Out=TEXT("The moderation database is unavailable.");return false;}
        const bool Remove=C==TEXT("unban")||C==TEXT("unjail")||C==TEXT("unmute");
        if((Remove&&A.Num()!=2)||(C==TEXT("warn")&&A.Num()!=3)||(!Remove&&C!=TEXT("warn")&&A.Num()!=4))return Usage();
        if(Candidate.AccountId==HostAccountId){Out=TEXT("The active host account cannot be moderated by its own console.");return false;}
        int64 Until=0;FString Reason;
        if(!Remove){Reason=A.Last().TrimStartAndEnd();if(Reason.IsEmpty()||Reason.Len()>256){Out=TEXT("Enter a reason of 1-256 characters.");return false;}if(C!=TEXT("warn")&&!Duration(A[2],Until)){Out=TEXT("Duration must be 1-5256000 minutes, 10m, 2h, 7d, or permanent (at most ten years).");return false;}}
        if(C==TEXT("jail")&&!RequireMutable(Candidate,Live,Out))return false;
        if(C==TEXT("ban")&&!bConfirmed)return PrepareConfirmation(A,ConfirmationFingerprint(A),Out);
        if(C==TEXT("ban")&&Live){ADigimonVenomNXTGameMode* GM=GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();if(!GM||!GM->GameSession||!GM->SavePlayer(Live)){Out=TEXT("Save or disconnect service unavailable; ban was not applied.");return false;}}
        UDigimonVenomNXTServerModerationSaveGame* Next=DuplicateObject<UDigimonVenomNXTServerModerationSaveGame>(Moderation,this);
        FDigimonServerModerationRecord* R=Next->Accounts.FindByPredicate([&](const FDigimonServerModerationRecord& E){return E.AccountId==Candidate.AccountId;});
        if(!R){FDigimonServerModerationRecord New;New.AccountId=Candidate.AccountId;New.Username=TargetName;Next->Accounts.Add(New);R=&Next->Accounts.Last();}
        if(C==TEXT("warn")){R->Warnings.Add(FDateTime::UtcNow().ToIso8601()+TEXT(" · ")+Reason);if(R->Warnings.Num()>20)R->Warnings.RemoveAt(0,R->Warnings.Num()-20);}
        else if(C==TEXT("ban")||C==TEXT("unban")){R->BannedUntil=Remove?0:Until;R->BanReason=Reason;}
        else if(C==TEXT("jail")||C==TEXT("unjail")){R->JailedUntil=Remove?0:Until;R->JailReason=Reason;}
        else{R->MutedUntil=Remove?0:Until;R->MuteReason=Reason;}
        if(!SaveModeration(Next,Out))return false;
        RecordActivity(TEXT("Moderation"),TargetName,TEXT("/")+C,Remove?TEXT("Restriction removed and saved."):TEXT("Moderation record saved."));
        if(PC){if(C==TEXT("ban")){ADigimonVenomNXTGameMode* GM=GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>();PC->SetAccountAuthenticatedServer(false);
            if(!GM||!GM->GameSession||!GM->GameSession->KickPlayer(PC,FText::FromString(TEXT("Account banned: ")+Reason)))
            {Out=TEXT("The ban was saved and gameplay access revoked, but the network disconnect failed. The account cannot reauthenticate while banned.");return false;}}else{ApplyModerationToPlayer(PC);PC->ClientShowMessage(TEXT("Host moderation"),C+TEXT(": ")+(Remove?TEXT("Restriction removed."):Reason));}}
        Out=C+TEXT(" saved for ")+TargetName;return true;
    }
    if(!RequireMutable(Candidate,Live,Out))return false;
    if(C==TEXT("heal"))
    {
        if(A.Num()!=2)return Usage();for(FDigimonOwnedPartner& P:Candidate.Collection)if(Candidate.Party.Contains(P.InstanceId)){const FDigimonBattleUnit Unit=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);P.CurrentHP=Unit.Stats.MaxHP;P.CurrentSP=Unit.Stats.MaxSP;}
    }
    else if(C==TEXT("givemoney")||C==TEXT("removemoney")||C==TEXT("setmoney"))
    {
        int64 Amount=0;if(A.Num()!=3||!Number(A[2],C==TEXT("setmoney")?0:1,9000000000000LL,Amount))return Usage();
        if(C==TEXT("setmoney"))Candidate.Credits=Amount;
        else if(C==TEXT("removemoney")){if(Candidate.Credits<Amount){Out=TEXT("The account does not have that many Credits.");return false;}Candidate.Credits-=Amount;}
        else{std::int64_t Total=0;if(!DigimonVenomNXTServerConsoleCore::AddWithin(Candidate.Credits,Amount,9000000000000LL,Total)){Out=TEXT("That grant would exceed the 9 trillion Credit safety cap.");return false;}Candidate.Credits=Total;}
    }
    else if(C==TEXT("giveitem")||C==TEXT("removeitem")||C==TEXT("setitem"))
    {
        int64 Quantity=0;if(A.Num()!=4||!Number(A[3],C==TEXT("setitem")?0:1,999,Quantity))return Usage();
        const FString Item=A[2].Equals(TEXT("CAMDigiMeat"),ESearchCase::IgnoreCase)?TEXT("digimeat_cam"):A[2];
        const TArray<FName> Allowed={TEXT("hp_s"),TEXT("sp_s"),TEXT("DigiMeat"),TEXT("digimeat_cam"),TEXT("digimeat_abi")};const FName ID(*Item);
        if(!Allowed.Contains(ID)){Out=TEXT("Item must be HPCapsuleSmall, SPCapsuleSmall, DigiMeat, CAMTreat or ABIMeat.");return false;}
        FDigimonInventoryEntry* E=Candidate.Inventory.FindByPredicate([&](const FDigimonInventoryEntry& Value){return Value.ItemId==ID;});
        const int64 Before=E?E->Quantity:0;const int64 After=C==TEXT("setitem")?Quantity:C==TEXT("giveitem")?Before+Quantity:Before-Quantity;
        if(After<0||After>999){Out=TEXT("The resulting quantity must be between 0 and 999. Nothing changed.");return false;}
        if(E)E->Quantity=static_cast<int32>(After);else if(After>0){FDigimonInventoryEntry New;New.ItemId=ID;New.Quantity=static_cast<int32>(After);Candidate.Inventory.Add(New);}
        Candidate.Inventory.RemoveAll([](const FDigimonInventoryEntry& Value){return Value.Quantity<=0;});
    }
    else if(C==TEXT("clearinventory")){if(A.Num()!=2)return Usage();if(!bConfirmed)return PrepareConfirmation(A,ConfirmationFingerprint(A),Out);Candidate.Inventory.Reset();}
    else if(C==TEXT("settitle"))
    {
        if(A.Num()!=3)return Usage();if(A[2].Equals(TEXT("none"),ESearchCase::IgnoreCase))Candidate.EquippedTitle.Reset();
        else{const FString* Title=Moderation?Moderation->Titles.FindByPredicate([&](const FString& Value){return Value.Equals(A[2],ESearchCase::IgnoreCase);}):nullptr;if(!Title){Out=TEXT("That title is not in the catalog. Create it with /addtitle first.");return false;}Candidate.OwnedTitles.AddUnique(*Title);Candidate.EquippedTitle=*Title;}
    }
    else if(C==TEXT("givedigimon")||C==TEXT("spawn"))
    {
        if(A.Num()<3||A.Num()>5)return Usage();FDigimonSpeciesDefinition S;if(!Species(Data,A[2],S,Out))return false;int64 Level=1;if(A.Num()>=4&&!Number(A[3],1,MaxLevel,Level))return Usage();EDigimonVariant V=EDigimonVariant::Normal;if(A.Num()==5&&!Variant(A[4],V))return Usage();
        const bool Artwork=V==EDigimonVariant::Paradox?S.bHasParadoxArtwork:V==EDigimonVariant::Shiny?S.bHasShinyArtwork:V==EDigimonVariant::Firewall?S.bHasFirewallArtwork:S.bHasNormalArtwork;
        if(!Artwork){Out=TEXT("This species does not provide artwork for that variety.");return false;}
        if(C==TEXT("spawn"))
        {
            FString Reason;if(!PC||PC->IsInDigiFarm()||PC->IsInRelay()||IsAccountJailed(Candidate.AccountId,Reason)){Out=TEXT("Target must be online, outside private maps, undetained and free of battles.");return false;}
            if(Candidate.Party.IsEmpty()){Out=TEXT("Target needs a party before starting a wild battle.");return false;}
            ADigimonVenomNXTBattleActor* Battle=GetWorld()->SpawnActor<ADigimonVenomNXTBattleActor>();if(!Battle||!Battle->InitializeWildBattle(Live,S.SpeciesId,V,static_cast<int32>(Level))){if(Battle)Battle->Destroy();Out=TEXT("The wild battle could not be initialized.");return false;}PC->SetCurrentBattleServer(Battle);Out=TEXT("Wild battle started for ")+TargetName;return true;
        }
        if(Candidate.Collection.Num()>=1000){Out=TEXT("Collection storage is full (1000 partners).");return false;}
        FDigimonOwnedPartner P;P.InstanceId=FGuid::NewGuid();P.SpeciesId=S.SpeciesId;P.Variant=V;P.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;
        DigimonVenomNXTStarterCore::InitializeLevel(P,static_cast<int32>(Level),MaxLevel,[Data](const FDigimonOwnedPartner& Value){return DigimonVenomNXTAutoBattle::BuildUnit(Value,Data).Stats;});P.Moves=DigimonVenomNXTAutoBattle::BuildUnit(P,Data).Moves;
        if(Candidate.Collection.IsEmpty())Candidate.StarterBalanceVersion=DigimonVenomNXTStarterCore::BalanceVersion;
        Candidate.Collection.Add(P);if(Candidate.Party.Num()<FMath::Min(6,GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize))Candidate.Party.Add(P.InstanceId);Observe(Candidate,P);
    }
    else if(C==TEXT("teleportplayer"))
    {
        int64 MapId=0;if(A.Num()!=3||!Number(A[2],1,10000,MapId))return Usage();FString Reason;
        if(!PC||PC->IsInDigiFarm()||PC->IsInRelay()||!PC->GetPawn()||IsAccountJailed(Candidate.AccountId,Reason)){Out=TEXT("Target must be online in the public world, undetained and free of battles.");return false;}
        UDigimonVenomNXTWorldSubsystem* World=GetWorld()->GetSubsystem<UDigimonVenomNXTWorldSubsystem>();FDigimonMapRow Row;ADigimonVenomNXTMapZone* Zone=World?World->FindMapZone(static_cast<int32>(MapId)):nullptr;
        if(!Data||!Data->GetMap(static_cast<int32>(MapId),Row)||!Zone){Out=TEXT("That real public map is not available in this world.");return false;}Zone->ApplyMapPresentation();const FVector Spawn=Zone->GetPlayerSpawnLocation();
        if(!World->IsWorldLocationWalkable(static_cast<int32>(MapId),Spawn)){Out=TEXT("The map has no collision-safe arrival point.");return false;}
        Candidate.CurrentMapId=static_cast<int32>(MapId);if(!CommitProfile(Candidate,Live,Out))return false;
        PC->GetPawn()->SetActorLocation(Spawn,false,nullptr,ETeleportType::TeleportPhysics);PC->ClientSetActiveMapPresentation(static_cast<int32>(MapId));PC->ClientPlayExplorationMusic(static_cast<int32>(MapId));
        if(ADigimonVenomNXTTamerCharacter* Tamer=Cast<ADigimonVenomNXTTamerCharacter>(PC->GetPawn())){Tamer->ResetEncounterTracker();Tamer->SnapFollowerToTamer();}
        RecordActivity(TEXT("Travel"),TargetName,TEXT("Host teleport"),TEXT("Saved and moved to public map ")+A[2]);
        Out=TEXT("Saved and moved ")+TargetName+TEXT(" to map ")+A[2];return true;
    }
    else
    {
        if(A.Num()<3)return Usage();const int32 Index=PartnerIndex(Candidate,A[2],Data,Out);if(Index==INDEX_NONE)return false;
        FDigimonOwnedPartner& P=Candidate.Collection[Index];const FDigimonBattleUnit Before=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);
        if(C==TEXT("removedigimon"))
        {
            if(A.Num()!=3)return Usage();if(Candidate.Party.Contains(P.InstanceId)&&Candidate.Party.Num()<=1){Out=TEXT("The final party member cannot be removed.");return false;}
            if(!bConfirmed)return PrepareConfirmation(A,ConfirmationFingerprint(A),Out);const FGuid Id=P.InstanceId;Candidate.Party.Remove(Id);Candidate.DigiFarmResidents.Remove(Id);Candidate.Collection.RemoveAt(Index);
        }
        else if(C==TEXT("clonedigimon"))
        {
            if(A.Num()!=3)return Usage();if(Candidate.Collection.Num()>=1000){Out=TEXT("Collection storage is full (1000 partners).");return false;}
            FDigimonOwnedPartner Copy=P;Copy.InstanceId=FGuid::NewGuid();Candidate.Collection.Add(Copy);if(Candidate.Party.Num()<FMath::Min(6,GetDefault<UDigimonVenomNXTSettings>()->MaxPartySize))Candidate.Party.Add(Copy.InstanceId);Observe(Candidate,Copy);
        }
        else if(C==TEXT("setlevel")||C==TEXT("setexp")||C==TEXT("setabi")||C==TEXT("setcam"))
        {
            int64 Value=0;const int64 Maximum=C==TEXT("setlevel")?MaxLevel:C==TEXT("setabi")?200:C==TEXT("setcam")?100:P.Level>=MaxLevel?0:DigimonVenomNXTProgressionCore::NextLevelXP(P.Level)-DigimonVenomNXTProgressionCore::ExperienceFloor(P.Level)-1;
            if(A.Num()!=4||!Number(A[3],C==TEXT("setlevel")?1:0,Maximum,Value)){Out=Info->Usage+FString::Printf(TEXT("\nAllowed value: %d to %lld."),C==TEXT("setlevel")?1:0,Maximum);return false;}
            if(C==TEXT("setlevel")){P.Level=static_cast<int32>(Value);P.Experience=DigimonVenomNXTProgressionCore::ExperienceFloor(P.Level);if(Index==0)Candidate.StarterBalanceVersion=DigimonVenomNXTStarterCore::BalanceVersion;}
            else if(C==TEXT("setexp"))P.Experience=DigimonVenomNXTProgressionCore::ExperienceFloor(P.Level)+Value;
            else if(C==TEXT("setabi"))P.ABI=static_cast<int32>(Value);else P.CAM=static_cast<int32>(Value);RefreshVitals(P,Before,Data);
        }
        else if(C==TEXT("setparadox")||C==TEXT("setshiny")||C==TEXT("setfirewall"))
        {
            if(A.Num()<3||A.Num()>4)return Usage();bool Enable=true;if(A.Num()==4){if(A[3].Equals(TEXT("false"),ESearchCase::IgnoreCase)||A[3]==TEXT("0"))Enable=false;else if(!A[3].Equals(TEXT("true"),ESearchCase::IgnoreCase)&&A[3]!=TEXT("1"))return Usage();}
            FDigimonSpeciesDefinition S;if(!Data||!Data->GetSpecies(P.SpeciesId,S))return false;
            const EDigimonVariant V=!Enable?EDigimonVariant::Normal:C==TEXT("setparadox")?EDigimonVariant::Paradox:C==TEXT("setshiny")?EDigimonVariant::Shiny:EDigimonVariant::Firewall;
            if((V==EDigimonVariant::Paradox&&!S.bHasParadoxArtwork)||(V==EDigimonVariant::Shiny&&!S.bHasShinyArtwork)||(V==EDigimonVariant::Firewall&&!S.bHasFirewallArtwork)){Out=TEXT("No artwork exists for this species variety.");return false;}
            P.Variant=V;RefreshVitals(P,Before,Data);Observe(Candidate,P);
        }
        else if(C==TEXT("evolve")||C==TEXT("devolve"))
        {
            if(A.Num()<3||A.Num()>4)return Usage();const bool Reverse=C==TEXT("devolve");const TArray<FDigimonEvolutionOption> All=DigimonVenomNXTEvolution::GetOptions(P,Data,true);TArray<FDigimonEvolutionOption> Options;for(const FDigimonEvolutionOption& Option:All)if(Option.bDeEvolution==Reverse)Options.Add(Option);
            FName Target=NAME_None;if(A.Num()==4){FDigimonSpeciesDefinition S;if(!Species(Data,A[3],S,Out))return false;Target=S.SpeciesId;}else if(Options.Num()==1)Target=Options[0].TargetSpeciesId;
            const FDigimonEvolutionOption* Route=Options.FindByPredicate([&](const FDigimonEvolutionOption& Option){return Option.TargetSpeciesId==Target;});
            if(!Route){TArray<FString> Names;for(const FDigimonEvolutionOption& Option:Options)Names.Add(Option.TargetSpeciesId.ToString());Out=TEXT("Choose one of the valid routes: ")+FString::Join(Names,TEXT(", "));return false;}
            FDigimonSpeciesDefinition Form;
            if(!Data->GetSpecies(Route->TargetSpeciesId,Form)||!DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(P.Variant),Form.bHasNormalArtwork,Form.bHasParadoxArtwork,Form.bHasShinyArtwork,Form.bHasFirewallArtwork))
            {Out=TEXT("The target form does not provide this partner's variety.");return false;}
            P.SpeciesId=Route->TargetSpeciesId;P.Level=1;P.Experience=0;P.ABI=FMath::Clamp(P.ABI+Route->ABIGain,0,200);P.Moves.Reset();const FDigimonBattleUnit Unit=DigimonVenomNXTAutoBattle::BuildUnit(P,Data);P.Moves=Unit.Moves;P.CurrentHP=Unit.Stats.MaxHP;P.CurrentSP=Unit.Stats.MaxSP;P.CombatBalanceVersion=DigimonVenomNXTAutoBattle::CurrentBalanceVersion;Observe(Candidate,P);
        }
        else return Usage();
    }
    if(!CommitProfile(Candidate,Live,Out))return false;
    RecordActivity(TEXT("Admin"),TargetName,TEXT("/")+C,TEXT("Authoritative profile update saved and published."));
    if(PC)PC->ClientShowMessage(TEXT("Host update"),TEXT("The host applied /")+C+TEXT(" to your account. Your progress was saved."));
    Out=TEXT("Saved /")+C+TEXT(" for ")+TargetName+TEXT(".");return true;
}

bool UDigimonVenomNXTServerConsoleSubsystem::SaveAll(FString& OutResponse)
{
    UGameInstance* Instance = GetGameInstance();
    if (!Instance || !CanAccess(Instance->GetFirstLocalPlayerController()))
    { OutResponse = TEXT("Only the authenticated local admin may save all server progress."); return false; }
    ADigimonVenomNXTGameMode* Mode = GetWorld() ? GetWorld()->GetAuthGameMode<ADigimonVenomNXTGameMode>() : nullptr;
    UDigimonVenomNXTProfileSubsystem* Profiles = Instance->GetSubsystem<UDigimonVenomNXTProfileSubsystem>();
    if (!Mode || !Profiles) { OutResponse = TEXT("Authoritative profile service is unavailable."); return false; }
    TArray<FString> Failed;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        ADigimonVenomNXTPlayerController* Controller = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        ADigimonVenomNXTPlayerState* Player = Controller ? Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
        if (Player && Controller->IsAccountAuthenticated() && !Controller->HasCommittedLogout() && !Mode->SavePlayer(Player, false))
            Failed.Add(Player->Profile.Username);
    }
    if (!Failed.IsEmpty())
    { OutResponse = TEXT("Could not capture authoritative accounts: ") + FString::Join(Failed, TEXT(", ")); return false; }
    int32 Saved = 0;
    if (!Profiles->SaveForHostConsole(Saved, OutResponse)) return false;
    UDigimonVenomNXTRankedSubsystem* Ranked = Instance->GetSubsystem<UDigimonVenomNXTRankedSubsystem>();
    UDigimonVenomNXTAIRivalSubsystem* Rivals = GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>();
    UDigimonVenomNXTSocialSubsystem* Social = Instance->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
    const bool bRankedSaved = Ranked && Ranked->SaveForHostConsole();
    const bool bRivalsSaved = Rivals && Rivals->SaveForHostConsole();
    const bool bSocialSaved = Social && Social->SaveForHostConsole();
    OutResponse = FString::Printf(TEXT("Checkpointed %d online/disconnected profile(s) and commerce. Ranked: %s. AI rivals: %s. Social: %s."),
        Saved, bRankedSaved ? TEXT("saved") : TEXT("FAILED"), bRivalsSaved ? TEXT("saved") : TEXT("FAILED"), bSocialSaved ? TEXT("saved") : TEXT("FAILED"));
    return bRankedSaved && bRivalsSaved && bSocialSaved;
}
void UDigimonVenomNXTServerConsoleSubsystem::FinishLifecycle()
{
    ADigimonVenomNXTPlayerController* Host=Cast<ADigimonVenomNXTPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
    if(!CanAccess(Host))return;FString Message;
    if(bRestartScheduled)
    {
        const UDigimonVenomNXTSettings* Settings=GetDefault<UDigimonVenomNXTSettings>();
        const FString Package=Settings->PublicWorldMap.GetLongPackageName();
        if(!FPackageName::IsValidLongPackageName(Package)||!FPackageName::DoesPackageExist(Package))
        {Host->ClientShowMessage(TEXT("Restart cancelled"),TEXT("The configured public world map is unavailable."));return;}
        if(!Host->PrepareHostWorldRestart(Message)){RecordActivity(TEXT("Server"),TEXT("Host"),TEXT("Restart aborted"),Message,TEXT("Error"));Host->ClientShowMessage(TEXT("Server remains open"),Message);return;}
        const FString Options=FString::Printf(TEXT("listen?port=%d"),FMath::Clamp(Settings->GameplayPort,1,65535));
        const TWeakObjectPtr<UGameInstance> Instance=GetGameInstance();
        GetWorld()->GetTimerManager().SetTimer(LifecycleTimer,FTimerDelegate::CreateLambda([Instance,Package,Options]()
        {if(Instance.IsValid())UGameplayStatics::OpenLevel(Instance.Get(),FName(*Package),true,Options);}),0.5f,false);
    }
    else if(!Host->RequestLogout(Message)){RecordActivity(TEXT("Server"),TEXT("Host"),TEXT("Closure aborted"),Message,TEXT("Error"));Host->ClientShowMessage(TEXT("Server remains open"),Message);}
}
