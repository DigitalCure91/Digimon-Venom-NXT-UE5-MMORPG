// Compiles the same state/routing policy used by UDigimonVenomNXTAudioSubsystem.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTAudioRoutingCore.h"
#include <cstdlib>
#include <iostream>
using namespace DigimonVenomNXTAudioRouting;
namespace
{
int Checks = 0;
void Require(bool Condition, const char* Description)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Description << '\n'; std::exit(1); }
}

// A mixer can reclaim an active voice at zero volume. Model that boundary so
// the same activation routine used with UAudioComponent must preserve paused
// voices without assuming two separate audio-thread commands are atomic.
struct TestVoice
{
    bool Stopped = true;
    bool Paused = false;
    float Cursor = 0.0f;
    float Gain = 1.0f;
    float LastFadeSeconds = 0.0f;
    int Starts = 0;
    int ZeroVolumeCommands = 0;

    void SetPaused(bool Value) { Paused = Value; }
    void FadeIn(float Duration, float Target, float StartTime)
    {
        Stopped = false;
        Cursor = StartTime;
        Gain = Target;
        LastFadeSeconds = Duration;
        ++Starts;
    }
    void AdjustVolume(float Duration, float Target)
    {
        if (Target <= 0.0f) { ++ZeroVolumeCommands; Stopped = true; }
        if (Stopped) return; // Changing gain does not start a retired voice.
        LastFadeSeconds = Duration;
        Gain = Target;
    }
    void Advance(float Seconds) { if (!Stopped && !Paused) Cursor += Seconds; }
};
}
int main()
{
    // Exercise the exact lifecycle policy used by the audio-finished delegate,
    // including callbacks already queued when a page/map replaces an intro.
    SequenceState Intro;
    Intro.Generation = 1;
    Require(Intro.CanPlay(true, true), "selected audible intro can begin");
    Require(!Intro.CanPlay(false, true), "a retained exploration intro stays silent under UI or battle");
    Require(!Intro.CanPlay(true, false), "muting cannot start an intro");
    Require(Intro.Finish(1, 2, true) && Intro.NeedsStart && !Intro.Completed, "natural intro completion prepares its loop");
    Require(!Intro.Finish(1, 3, true) && Intro.Generation == 2, "duplicate intro completion cannot advance the loop");
    Require(!Intro.CanPlay(false, true), "intro finishing during an override cannot restart background music");
    Intro.Cancel(4);
    Require(!Intro.Finish(2, 5, true) && !Intro.CanPlay(true, true), "map change or Stop invalidates pending completion");
    SequenceState Arrival;
    Arrival.Generation = 6;
    Require(Arrival.Finish(6, 7, true), "one-shot arrival can queue its catalog continuation");
    SequenceState OneShot;
    OneShot.Generation = 8;
    Require(OneShot.Finish(8, 9, false) && OneShot.Completed, "unsequenced one-shot stays completed");
    Require(!OneShot.CanPlay(true, true), "repeated routing or unmute cannot restart a completed one-shot");

    const std::vector<std::pair<std::string_view, Track>> Pages = {
        {"overview", Track::GenericUI}, {"atlas", Track::Atlas}, {"party", Track::Party},
        {"digidex", Track::DigiDex}, {"collection", Track::Evolution}, {"digilab", Track::Lab}, {"digifarm", Track::Farm},
        {"shop", Track::Shop}, {"story", Track::Story}, {"season", Track::Season},
        {"ranked", Track::Ranked}, {"rivals", Track::Rivals}, {"botactivity", Track::BotActivity},
        {"login", Track::MainMenu}, {"createaccount", Track::MainMenu}, {"settings", Track::Settings}
    };
    State S;
    Require(S.Current() == Track::None, "an uninitialized player has no music");
    S.EnterMainMenu();
    Require(S.Current() == Track::MainMenu, "authentication pages use the main menu theme");
    S.SetExploration(17);
    Require(S.Current() == Track::Exploration && S.MapId == 17, "entering the world leaves main menu");
    for (const auto& Page : Pages)
    {
        S.SetScreen(100, ScreenTrack(Page.first));
        Require(S.Current() == Page.second, "each authored UI route overrides exploration");
        Require(std::string_view(AssetStem(S.Current())).size() > 0, "every UI route has a concrete named asset");
        S.SetScreen(100, ScreenTrack(Page.first));
        S.ClearScreen(100);
        Require(S.Current() == Track::Exploration, "idempotent repeated opens do not stack duplicate owners");
    }
    S.SetScreen(100, Track::Ranked);
    S.SetScreen(200, Track::GenericUI);
    S.SetScreen(100, Track::Season);
    Require(S.Current() == Track::GenericUI, "updating an obscured page does not steal the overlay soundtrack");
    S.ClearScreen(999);
    Require(S.Current() == Track::GenericUI, "stale unrelated widget cleanup cannot pop an active overlay");
    S.ClearScreen(200);
    Require(S.Current() == Track::Season, "closing a nested overlay restores the underlying updated page");
    S.SetExploration(42);
    Require(S.Current() == Track::Season && S.MapId == 42, "delayed map updates never replace visible UI music");
    S.SetBattle(300, 42, false, true);
    Require(S.Current() == Track::Battle && S.UI() == Track::Season, "battle overrides but preserves its underlying UI");
    S.SetExploration(43);
    Require(S.Current() == Track::Battle && S.MapId == 43 && S.BattleMapId == 42, "world replication cannot steal battle music or alter battle fallback map");
    S.SetScreen(100, Track::Ranked);
    Require(S.Current() == Track::Battle, "UI updates under battle do not steal its music");
    S.SetBattle(300, 42, true, true);
    Require(S.Current() == Track::SeasonVictory, "visible season victory uses the season match win theme");
    S.SetBattle(300, 42, true, false);
    Require(S.Current() == Track::Victory, "wild/ranked/story victory uses the after-battle win theme");
    S.SetBattle(300, 42, false, false);
    Require(S.Current() == Track::Victory, "refreshing the same completed battle cannot restart its fight/result tracks");
    S.SetBattle(400, 43, false, false);
    S.ClearBattle(300);
    Require(S.Current() == Track::Battle && S.GetBattleOwner() == 400, "old battle teardown cannot clear a newer battle");
    S.ClearBattle(400);
    Require(S.Current() == Track::Ranked, "dismissing battle restores the actual current UI");
    S.ClearScreen(100);
    Require(S.Current() == Track::Exploration && S.MapId == 43, "closing UI returns to the latest map rather than the pre-battle map");
    S.SetScreen(100, Track::Lab);
    S.SetBattle(400, 43, false, false);
    S.ClearScreen(100);
    Require(S.Current() == Track::Battle, "removing HUD while battle is visible leaves battle music intact");
    S.ClearBattle(400);
    Require(S.Current() == Track::Exploration, "no hidden UI music remains after HUD removal");
    S.SetScreen(100, Track::Farm);
    S.SetBattle(500, 43, true, false);
    S.EnterMainMenu();
    Require(S.Current() == Track::MainMenu && S.UI() == Track::None && S.Battle() == Track::None && S.MapId == 0, "returning to login discards all previous-world audio contexts");
    S.ClearScreen(100);
    S.ClearBattle(500);
    Require(S.Current() == Track::MainMenu, "late old-world cleanup cannot interrupt login music");
    S.SetExploration(8);
    Require(S.Current() == Track::Exploration && S.MapId == 8, "re-login has no stale menu/battle music");
    S.SetScreen(0, Track::Lab);
    S.SetBattle(0, 8, false, false);
    Require(S.Current() == Track::Exploration, "invalid owner cannot install an unremovable music override");
    S.Reset();
    Require(S.Current() == Track::None, "shutdown clears all routing contexts");

    S.SetExploration(17);
    S.SetFarm(true);
    Require(S.Current() == Track::Farm && S.Field() == Track::Farm, "a walkable private farm is a persistent field music context");
    Require(std::string_view(AssetStem(S.Field())) == "digifarm_home", "farm field uses the exact supplied case-sensitive filename");
    S.SetExploration(17);
    Require(S.Current() == Track::Farm, "late saved-map music RPC cannot replace the active farm theme");
    S.SetFarm(true);
    Require(S.Current() == Track::Farm, "repeated private-scene updates are idempotent");
    for (const Track Page : {Track::GenericUI, Track::Atlas, Track::Farm, Track::Lab, Track::Ranked, Track::Season})
    {
        S.SetScreen(100, Page);
        Require(S.Current() == Page && S.Field() == Track::Farm, "full-screen farm menus override but retain the farm field context");
        S.ClearScreen(100);
        Require(S.Current() == Track::Farm, "return to farm from any menu restores the farm theme");
    }
    S.SetBattle(600, 17, false, false);
    Require(S.Current() == Track::Battle, "battle music still takes precedence over every field context");
    S.ClearBattle(600);
    Require(S.Current() == Track::Farm, "battle owner cleanup preserves the home soundtrack");
    S.SetFarm(false);
    Require(S.Current() == Track::Exploration && S.MapId == 17, "leaving home restores the real saved habitat music");
    S.SetFarm(true);
    S.EnterMainMenu();
    Require(S.Current() == Track::MainMenu && S.Field() == Track::None, "disconnect clears private farm music along with other world state");
    S.SetExploration(3);
    Require(S.Current() == Track::Exploration, "a later field login cannot inherit a stale farm soundtrack");
    S.Reset();

    TestVoice FieldVoice;
    ResumeOrStartVoice(FieldVoice, FieldVoice.Stopped, 0.2f);
    Require(!FieldVoice.Stopped && !FieldVoice.Paused && FieldVoice.Starts == 1 && FieldVoice.Gain == 1.0f,
        "new field music starts once at audible gain");
    FieldVoice.Advance(30.0f);
    S.SetExploration(17);
    for (const Track Page : {Track::GenericUI, Track::Atlas, Track::Ranked, Track::Season})
    {
        TestVoice MenuVoice;
        S.SetScreen(100, Page);
        FieldVoice.SetPaused(true);
        ResumeOrStartVoice(MenuVoice, MenuVoice.Stopped, 0.2f);
        FieldVoice.Advance(5.0f);
        MenuVoice.Advance(5.0f);
        Require(FieldVoice.Cursor == 30.0f && MenuVoice.Cursor == 5.0f,
            "visible menus pause the field cursor while their own music advances");
        S.ClearScreen(100); // The live Return to Level button clears this owner.
        MenuVoice.SetPaused(true);
        ResumeOrStartVoice(FieldVoice, FieldVoice.Stopped, 0.2f);
        Require(S.Current() == Track::Exploration && S.MapId == 17 && !FieldVoice.Paused &&
            !FieldVoice.Stopped && FieldVoice.Starts == 1 && FieldVoice.Cursor == 30.0f && FieldVoice.Gain == 1.0f,
            "Return to Level resumes the same audible field voice without atlas travel or restarting it");
        Require(FieldVoice.ZeroVolumeCommands == 0,
            "resuming field music never exposes its voice to zero-volume reclamation");
    }
    FieldVoice.Advance(2.0f);
    Require(FieldVoice.Cursor == 32.0f, "field playback advances after repeated menu returns");
    FieldVoice.SetPaused(true);
    FieldVoice.Stopped = true; // Voice eviction while covered by UI/battle.
    ResumeOrStartVoice(FieldVoice, FieldVoice.Stopped, 0.2f);
    Require(!FieldVoice.Stopped && !FieldVoice.Paused && FieldVoice.Starts == 2 && FieldVoice.Cursor == 0.0f,
        "a retained but stopped voice restarts instead of attempting a silent resume");
    FieldVoice.SetPaused(true);
    ResumeOrStartVoice(FieldVoice, FieldVoice.Stopped, -1.0f);
    Require(FieldVoice.LastFadeSeconds == 0.0f && FieldVoice.Starts == 2,
        "negative requested fades become immediate gain restoration without restarting a paused voice");
    FieldVoice.SetPaused(true);
    const float PreviousCursor = FieldVoice.Cursor;
    ResumeOrStartVoice(FieldVoice, FieldVoice.Stopped, 0.05f, 0.32f);
    Require(FieldVoice.Gain == 0.32f && FieldVoice.Cursor == PreviousCursor && FieldVoice.Starts == 2,
        "custom master/music gain resumes the same voice without resetting its cursor");
    TestVoice QuietVoice;
    ResumeOrStartVoice(QuietVoice, true, 0.05f, 0.18f);
    Require(QuietVoice.Gain == 0.18f && QuietVoice.Starts == 1,
        "new music respects the mixer gain from its very first playback frame");

    // Prove that the test double exercises the old failure, rather than allowing
    // a gain update to magically resurrect a stopped component.
    TestVoice OldResume;
    OldResume.FadeIn(0.2f, 1.0f, 0.0f);
    OldResume.SetPaused(true);
    OldResume.SetPaused(false);
    OldResume.AdjustVolume(0.0f, 0.0f);
    OldResume.AdjustVolume(0.2f, 1.0f);
    Require(OldResume.Stopped, "the regression mixer rejects the previous mute-then-resume sequence");
    std::cout << "Audio routing core: " << Checks << " checks passed\n";
}
