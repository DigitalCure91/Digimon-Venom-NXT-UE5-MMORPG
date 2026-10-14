#pragma once

// Engine-independent routing policy used by the live local-player audio subsystem.
#include <algorithm>
#include <cstdint>
#include <string_view>
#include <vector>

namespace DigimonVenomNXTAudioRouting
{
// Shared by the runtime audio component and the native voice regression tests.
// A retained voice already has a valid playback cursor and gain. Sending it an
// intermediate zero-volume command can retire the voice before the following
// fade-up is processed; resume it directly at its existing cursor instead.
template <typename Voice>
void ResumeOrStartVoice(Voice& Component, bool WasStopped, float FadeSeconds, float TargetVolume = 1.0f)
{
    Component.SetPaused(false);
    if (WasStopped)
        Component.FadeIn(std::max(0.0f, FadeSeconds), TargetVolume, 0.0f);
    else
        Component.AdjustVolume(std::max(0.0f, FadeSeconds), TargetVolume);
}

// A completion belongs to one musical segment, even when its component is
// reused for the next segment. Retiring a voice also invalidates queued events.
struct SequenceState
{
    std::uint64_t Generation = 0;
    bool NeedsStart = true;
    bool Completed = false;

    void Cancel(std::uint64_t NextGeneration)
    {
        Generation = NextGeneration;
        Completed = true;
    }
    bool Finish(std::uint64_t ExpectedGeneration, std::uint64_t NextGeneration, bool HasContinuation)
    {
        if (Completed || Generation != ExpectedGeneration) return false;
        Generation = NextGeneration;
        Completed = !HasContinuation;
        NeedsStart = HasContinuation;
        return true;
    }
    bool CanPlay(bool IsCurrent, bool IsAudible) const
    {
        return !Completed && IsCurrent && IsAudible;
    }
};

enum class Track
{
    None, Exploration, MainMenu, GenericUI, Atlas, Lab, Farm, Ranked,
    Season, Rivals, BotActivity, Battle, Victory, SeasonVictory,
    Shop, Party, DigiDex, Evolution, Storage, Scan, Skills, Settings, Story, TamerStudio
};

inline Track ScreenTrack(std::string_view Page)
{
    if (Page == "mainmenu" || Page == "login" || Page == "createaccount") return Track::MainMenu;
    if (Page == "atlas" || Page == "levelselect") return Track::Atlas;
    if (Page == "digilab") return Track::Lab;
    if (Page == "digifarm") return Track::Farm;
    if (Page == "ranked") return Track::Ranked;
    if (Page == "season") return Track::Season;
    if (Page == "rivals" || Page == "rivaltamers") return Track::Rivals;
    if (Page == "botactivity") return Track::BotActivity;
    if (Page == "story") return Track::Story;
    if (Page == "tamerstudio") return Track::TamerStudio;
    if (Page == "shop") return Track::Shop;
    if (Page == "party") return Track::Party;
    if (Page == "digidex" || Page == "dex") return Track::DigiDex;
    if (Page == "collection" || Page == "evolution") return Track::Evolution;
    if (Page == "storage") return Track::Storage;
    if (Page == "scan") return Track::Scan;
    if (Page == "skills") return Track::Skills;
    if (Page == "video" || Page == "settings") return Track::Settings;
    return Track::GenericUI;
}

// These IDs come directly from data/ui_audio.json and data/audio_catalog.json.
// The ui_ prefix separates supplied interface renders from the world score.
inline const char* AssetStem(Track Value)
{
    switch (Value)
    {
    case Track::MainMenu: return "ui_bgm00";
    case Track::Farm: return "digifarm_home";
    case Track::Atlas: return "ui_bgm18";
    case Track::Lab: return "ui_bgm11";
    case Track::GenericUI: return "ui_bgm14";
    case Track::Ranked: return "ui_bgm30";
    case Track::BotActivity: return "ui_bgm14";
    case Track::Rivals: return "ui_bgm20";
    case Track::Battle: return "bgm40";
    case Track::SeasonVictory: return "bgm51";
    case Track::Season: return "bgm50";
    case Track::Victory: return "bgm60";
    case Track::Shop: return "ui_bgm12";
    case Track::Party: return "ui_bgm13";
    case Track::DigiDex: return "ui_bgm15";
    case Track::Evolution: return "ui_bgm19";
    case Track::Storage: return "ui_bgm17";
    case Track::Scan: return "ui_bgm16";
    case Track::Skills: return "ui_bgm32";
    case Track::Settings: return "ui_bgm43";
    case Track::Story: return "bgm30";
    case Track::TamerStudio: return "ui_bgm01";
    default: return "";
    }
}

using Owner = std::uintptr_t;
struct Screen { Owner Id; Track Music; };

class State
{
public:
    int MapId = 0;
    int BattleMapId = 0;

    void SetExploration(int NewMapId)
    {
        MapId = NewMapId;
        MainMenu = false;
    }
    void EnterMainMenu()
    {
        Reset();
        MainMenu = true;
    }
    void SetFarm(bool Active)
    {
        Farm = Active;
        if (Active) MainMenu = false;
    }
    void SetScreen(Owner Id, Track Music)
    {
        if (Id == 0) return;
        const auto Found = std::find_if(Screens.begin(), Screens.end(), [Id](const Screen& S) { return S.Id == Id; });
        if (Found != Screens.end()) Found->Music = Music;
        else Screens.push_back({Id, Music});
    }
    void ClearScreen(Owner Id)
    {
        Screens.erase(std::remove_if(Screens.begin(), Screens.end(), [Id](const Screen& S) { return S.Id == Id; }), Screens.end());
    }
    void SetBattle(Owner Id, int NewMapId, bool Won, bool SeasonMatch)
    {
        if (Id == 0) return;
        // A controller refresh may announce the same battle before its widget
        // reasserts the displayed result. Never restart the fight track in between.
        const bool KeepResult = Id == BattleOwner && !Won &&
            (BattleMusic == Track::Victory || BattleMusic == Track::SeasonVictory);
        BattleOwner = Id;
        BattleMapId = NewMapId;
        if (!KeepResult) BattleMusic = Won ? (SeasonMatch ? Track::SeasonVictory : Track::Victory) : Track::Battle;
        MainMenu = false;
    }
    void ClearBattle(Owner Id)
    {
        if (BattleOwner != Id) return;
        BattleOwner = 0;
        BattleMapId = 0;
        BattleMusic = Track::None;
    }
    Track Current() const
    {
        if (BattleOwner != 0) return BattleMusic;
        if (MainMenu) return Track::MainMenu;
        if (!Screens.empty()) return Screens.back().Music;
        return Field();
    }
    Track Field() const { return Farm ? Track::Farm : (MapId > 0 ? Track::Exploration : Track::None); }
    Track UI() const { return Screens.empty() ? Track::None : Screens.back().Music; }
    Track Battle() const { return BattleMusic; }
    Owner GetBattleOwner() const { return BattleOwner; }
    void Reset()
    {
        MapId = BattleMapId = 0;
        BattleOwner = 0;
        MainMenu = false;
        Farm = false;
        BattleMusic = Track::None;
        Screens.clear();
    }

private:
    bool MainMenu = false;
    bool Farm = false;
    Owner BattleOwner = 0;
    Track BattleMusic = Track::None;
    std::vector<Screen> Screens;
};
}
