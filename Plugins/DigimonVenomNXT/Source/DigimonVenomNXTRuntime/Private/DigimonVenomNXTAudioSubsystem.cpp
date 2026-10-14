#include "DigimonVenomNXTAudioSubsystem.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTSettings.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundWave.h"
#include "HAL/PlatformTime.h"
#include "Misc/ConfigCacheIni.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY_STATIC(LogDigimonMusic, Log, All);

namespace
{
    FString MusicObjectPath(const FString& Path)
    {
        if (Path.IsEmpty() || Path.Contains(TEXT("."))) return Path;
        return Path + TEXT(".") + FPaths::GetBaseFilename(Path);
    }

    DigimonVenomNXTAudioRouting::Owner MusicOwner(const UObject* Object)
    {
        return reinterpret_cast<DigimonVenomNXTAudioRouting::Owner>(Object);
    }
}

static_assert(static_cast<uint8>(EDigimonAudioCue::EffectiveHit) == static_cast<uint8>(DigimonVenomNXTAudioCueCore::Cue::EffectiveHit), "Cue enum and portable policy must match");

FString UDigimonVenomNXTAudioSubsystem::AudioConfigSection() const
{
    const UGameInstance* GI = GetLocalPlayer() ? GetLocalPlayer()->GetGameInstance() : nullptr;
    const int32 Index = GI ? GI->GetLocalPlayers().IndexOfByKey(GetLocalPlayer()) : 0;
    return FString::Printf(TEXT("DigimonVenomNXT.LocalAudio.%d"), FMath::Max(0, Index));
}

void UDigimonVenomNXTAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LoadMusicMetadata();
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    MasterVolume = Settings->DefaultMasterVolume;
    MusicVolume = Settings->DefaultMusicVolume;
    EffectsVolume = Settings->DefaultEffectsVolume;
    UIVolume = Settings->DefaultUIVolume;
    if (GConfig)
    {
        const FString Section = AudioConfigSection();
        GConfig->GetFloat(*Section, TEXT("Master"), MasterVolume, GGameUserSettingsIni);
        GConfig->GetFloat(*Section, TEXT("Music"), MusicVolume, GGameUserSettingsIni);
        GConfig->GetFloat(*Section, TEXT("Effects"), EffectsVolume, GGameUserSettingsIni);
        GConfig->GetFloat(*Section, TEXT("UI"), UIVolume, GGameUserSettingsIni);
    }
    SetAudioVolumes(MasterVolume, MusicVolume, EffectsVolume, UIVolume, false);
}

void UDigimonVenomNXTAudioSubsystem::SetAudioVolumes(float Master, float Music, float Effects, float UI, bool bSave)
{
    MasterVolume = DigimonVenomNXTAudioCueCore::Volume(Master);
    MusicVolume = DigimonVenomNXTAudioCueCore::Volume(Music);
    EffectsVolume = DigimonVenomNXTAudioCueCore::Volume(Effects);
    UIVolume = DigimonVenomNXTAudioCueCore::Volume(UI);
    ApplyVolumes();
    if (bSave && GConfig)
    {
        const FString Section = AudioConfigSection();
        GConfig->SetFloat(*Section, TEXT("Master"), MasterVolume, GGameUserSettingsIni);
        GConfig->SetFloat(*Section, TEXT("Music"), MusicVolume, GGameUserSettingsIni);
        GConfig->SetFloat(*Section, TEXT("Effects"), EffectsVolume, GGameUserSettingsIni);
        GConfig->SetFloat(*Section, TEXT("UI"), UIVolume, GGameUserSettingsIni);
        GConfig->Flush(false, GGameUserSettingsIni);
    }
}

void UDigimonVenomNXTAudioSubsystem::ApplyVolumes()
{
    for (FDigimonMusicVoice& Voice : MusicLayers)
    {
        UAudioComponent* Layer = Voice.Component;
        if (!IsValid(Layer)) continue;
        const float Gain = MasterVolume * MusicVolume;
        // Preserve the exact intro/loop cursor while muted or behind another UI.
        if (Gain <= 0.0f) Layer->SetPaused(true);
        else if (Layer == MusicComponent) StartOrResumeMusic(Voice, 0.05f);
        else Layer->AdjustVolume(0.05f, Gain);
    }
    for (const FDigimonEffectVoice& Voice : EffectVoices)
        if (IsValid(Voice.Component)) Voice.Component->SetVolumeMultiplier(
            DigimonVenomNXTAudioCueCore::Mix(MasterVolume, Voice.bUI ? UIVolume : EffectsVolume, Voice.Gain));
}

void UDigimonVenomNXTAudioSubsystem::PlayForWidget(const UWidget* Widget, EDigimonAudioCue Cue)
{
    const UUserWidget* Owner = Widget ? Widget->GetTypedOuter<UUserWidget>() : nullptr;
    if (!Owner) Owner = Cast<UUserWidget>(Widget);
    ULocalPlayer* Local = Owner ? Owner->GetOwningLocalPlayer() : nullptr;
    if (UDigimonVenomNXTAudioSubsystem* Audio = Local ? Local->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr)
        Audio->PlayCue(Cue);
}

void UDigimonVenomNXTAudioSubsystem::PlayCue(EDigimonAudioCue Cue)
{
    PlayCueInternal(Cue, FString());
}

void UDigimonVenomNXTAudioSubsystem::PlayCueOnce(EDigimonAudioCue Cue, const FString& EventKey)
{
    PlayCueInternal(Cue, EventKey);
}

void UDigimonVenomNXTAudioSubsystem::PlayCueInternal(EDigimonAudioCue Cue, const FString& EventKey)
{
    using namespace DigimonVenomNXTAudioCueCore;
    const Descriptor* D = Describe(static_cast<DigimonVenomNXTAudioCueCore::Cue>(Cue));
    UWorld* World = GetLocalPlayer() ? GetLocalPlayer()->GetWorld() : nullptr;
    if (!D || !World || World->GetNetMode() == NM_DedicatedServer) return;
    if (!CueGate.Accept(static_cast<DigimonVenomNXTAudioCueCore::Cue>(Cue), FPlatformTime::Seconds(), TCHAR_TO_UTF8(*EventKey))) return;
    const float Gain = Mix(MasterVolume, D->UI ? UIVolume : EffectsVolume, D->Gain);
    if (Gain <= 0.0f) return;
    const FName Name(UTF8_TO_TCHAR(D->Name));
    USoundBase* Sound = nullptr;
    if (const TObjectPtr<USoundBase>* Loaded = LoadedEffects.Find(Name)) Sound = Loaded->Get();
    else if (!MissingEffects.Contains(Name))
    {
        const FString Asset = TEXT("SW_") + FString(UTF8_TO_TCHAR(D->Stem));
        FString Path = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Audio/SFX/%s.%s"), *Asset, *Asset);
        bool bOverride = false;
        if (const FSoftObjectPath* Override = GetDefault<UDigimonVenomNXTSettings>()->SoundEffectOverrides.Find(Name))
            if (Override->IsValid() && !Override->ToString().StartsWith(TEXT("/DigimonVenomNXT/Generated/Audio/BGM/")))
            { Path = Override->ToString(); bOverride = true; }
        Sound = LoadObject<USoundBase>(nullptr, *Path, nullptr, LOAD_NoWarn);
        if (Sound && bOverride)
        {
            // A project override is not permission to mutate a shared music wave.
            if (const USoundWave* Wave = Cast<USoundWave>(Sound))
                if (Wave->bLooping) Sound = nullptr;
        }
        if (Sound)
        {
            // One-shot SFX never enter the music cache or alter BGM looping flags.
            if (!bOverride) if (USoundWave* Wave = Cast<USoundWave>(Sound)) Wave->bLooping = false;
            LoadedEffects.Add(Name, Sound);
        }
        else
        {
            MissingEffects.Add(Name);
            UE_LOG(LogDigimonMusic, Warning, TEXT("SFX %s unavailable or looping: %s. Use a one-shot override or run Tools > Digimon Venom NXT: Import Interface + Audio."), *Name.ToString(), *Path);
        }
    }
    if (!Sound) return;
    for (int32 I = EffectVoices.Num() - 1; I >= 0; --I)
        if (!IsValid(EffectVoices[I].Component) || !EffectVoices[I].Component->IsPlaying())
        {
            if (IsValid(EffectVoices[I].Component)) EffectVoices[I].Component->DestroyComponent();
            EffectVoices.RemoveAt(I);
        }
    const int32 Limit = D->UI ? 2 : 6;
    int32 InChannel = 0;
    for (const FDigimonEffectVoice& Voice : EffectVoices) if (Voice.bUI == D->UI) ++InChannel;
    if (InChannel >= Limit)
        for (int32 I = 0; I < EffectVoices.Num(); ++I)
            if (EffectVoices[I].bUI == D->UI)
            {
                EffectVoices[I].Component->Stop();
                EffectVoices[I].Component->DestroyComponent();
                EffectVoices.RemoveAt(I);
                break;
            }
    UAudioComponent* Voice = UGameplayStatics::CreateSound2D(World, Sound, Gain, D->Pitch, 0.0f, nullptr, false, false);
    if (!Voice) return;
    Voice->bIsUISound = true; // Local feedback remains responsive while a modal UI owns input.
    FDigimonEffectVoice Entry;
    Entry.Component = Voice;
    Entry.bUI = D->UI;
    Entry.Gain = D->Gain;
    EffectVoices.Add(Entry);
    Voice->Play();
}

void UDigimonVenomNXTAudioSubsystem::Deinitialize()
{
    for (const FDigimonEffectVoice& Voice : EffectVoices)
        if (IsValid(Voice.Component)) { Voice.Component->Stop(); Voice.Component->DestroyComponent(); }
    EffectVoices.Reset();
    LoadedEffects.Reset();
    MissingEffects.Reset();
    StopMusic(0.0f);
    LoadedTracks.Reset();
    MissingTracks.Reset();
    MusicTrackInfo.Reset();
    Super::Deinitialize();
}

void UDigimonVenomNXTAudioSubsystem::LoadMusicMetadata()
{
    // The importer and runtime read the same source catalog. Never infer a split
    // intro from a filename: the supplied metadata also has one-shot arrivals.
    MusicTrackInfo.Reset();
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
    FString JSON;
    TSharedPtr<FJsonObject> Root;
    const TArray<TSharedPtr<FJsonValue>>* Tracks = nullptr;
    if (!Plugin.IsValid() || !FFileHelper::LoadFileToString(JSON,
        *FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources/GameData/audio.json"))) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JSON), Root) ||
        !Root.IsValid() || !Root->TryGetArrayField(TEXT("tracks"), Tracks))
    {
        UE_LOG(LogDigimonMusic, Warning, TEXT("Music catalog unavailable. Imported wave looping remains active, but split intros cannot be queued."));
        return;
    }
    TMap<FString, FString> ById;
    TMap<FString, FString> BySource;
    for (const TSharedPtr<FJsonValue>& Value : *Tracks)
    {
        const TSharedPtr<FJsonObject> Row = Value.IsValid() ? Value->AsObject() : nullptr;
        FString Id, Source, Asset;
        if (!Row.IsValid() || !Row->TryGetStringField(TEXT("asset"), Asset)) continue;
        Asset = MusicObjectPath(Asset);
        if (Row->TryGetStringField(TEXT("id"), Id)) ById.Add(Id, Asset);
        if (Row->TryGetStringField(TEXT("originalSource"), Source)) BySource.Add(Source, Asset);
    }
    for (const TSharedPtr<FJsonValue>& Value : *Tracks)
    {
        const TSharedPtr<FJsonObject> Row = Value.IsValid() ? Value->AsObject() : nullptr;
        FString Asset;
        if (!Row.IsValid() || !Row->TryGetStringField(TEXT("asset"), Asset)) continue;
        FDigimonMusicTrackInfo Info;
        Row->TryGetBoolField(TEXT("loop"), Info.bLooping);
        const TSharedPtr<FJsonObject>* Metadata = nullptr;
        if (Row->TryGetObjectField(TEXT("metadata"), Metadata) && Metadata && Metadata->IsValid())
        {
            FString IntroSource, ContinuationId;
            if ((*Metadata)->TryGetStringField(TEXT("intro_path"), IntroSource))
                if (const FString* Path = BySource.Find(IntroSource)) Info.IntroPath = *Path;
            if ((*Metadata)->TryGetStringField(TEXT("continuation_id"), ContinuationId))
                if (const FString* Path = ById.Find(ContinuationId)) Info.ContinuationPath = *Path;
        }
        MusicTrackInfo.Add(FName(*MusicObjectPath(Asset)), MoveTemp(Info));
    }
}

USoundBase* UDigimonVenomNXTAudioSubsystem::LoadBGM(const FString& ObjectPath)
{
    if (ObjectPath.IsEmpty()) return nullptr;
    const FString CanonicalPath = MusicObjectPath(ObjectPath);
    const FName Key(*CanonicalPath);
    if (const TObjectPtr<USoundBase>* Existing = LoadedTracks.Find(Key)) return Existing->Get();
    if (MissingTracks.Contains(Key)) return nullptr;
    USoundBase* Sound = LoadObject<USoundBase>(nullptr, *CanonicalPath, nullptr, LOAD_NoWarn);
    if (!Sound)
    {
        MissingTracks.Add(Key);
        UE_LOG(LogDigimonMusic, Warning, TEXT("BGM asset missing: %s. Using the next available music context. Run Tools > Digimon Venom NXT: Import Interface + Audio."), *ObjectPath);
        return nullptr;
    }
    // Intro and one-shot arrival waves must finish naturally. Only apply the
    // catalog's explicit flag, leaving project-provided waves untouched.
    if (const FDigimonMusicTrackInfo* Info = MusicTrackInfo.Find(Key))
        if (USoundWave* Wave = Cast<USoundWave>(Sound)) Wave->bLooping = Info->bLooping;
    LoadedTracks.Add(Key, Sound);
    return Sound;
}

USoundBase* UDigimonVenomNXTAudioSubsystem::LoadNamedBGM(DigimonVenomNXTAudioRouting::Track Track)
{
    const FString Stem = UTF8_TO_TCHAR(DigimonVenomNXTAudioRouting::AssetStem(Track));
    if (Stem.IsEmpty()) return nullptr;
    const FString Asset = TEXT("SW_") + Stem;
    return LoadBGM(FString::Printf(TEXT("/DigimonVenomNXT/Generated/Audio/BGM/%s.%s"), *Asset, *Asset));
}

USoundBase* UDigimonVenomNXTAudioSubsystem::LoadMapBGM(int32 MapId, bool bBattle)
{
    UGameInstance* GI = GetLocalPlayer() ? GetLocalPlayer()->GetGameInstance() : nullptr;
    UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonMapRow Row;
    if (!Data || !Data->GetMap(MapId, Row)) return nullptr;
    return LoadBGM((bBattle ? Row.BattleMusic : Row.ExplorationMusic).ToSoftObjectPath().ToString());
}

USoundBase* UDigimonVenomNXTAudioSubsystem::ResolveSound(DigimonVenomNXTAudioRouting::Track Track)
{
    using TrackType = DigimonVenomNXTAudioRouting::Track;
    if (Track == TrackType::None) return nullptr;
    if (Track == TrackType::Exploration) return LoadMapBGM(Routing.MapId, false);
    // Region-specific music is part of the source map, including World DS and
    // Super Xros Wars battles; do not mask it with the Dawn fallback theme.
    if (Track == TrackType::Battle)
        if (USoundBase* RegionBattle = LoadMapBGM(Routing.BattleMapId, true)) return RegionBattle;
    if (Track == TrackType::Victory)
    {
        UGameInstance* GI = GetLocalPlayer() ? GetLocalPlayer()->GetGameInstance() : nullptr;
        UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        FDigimonMapRow Row;
        if (Data && Data->GetMap(Routing.BattleMapId, Row) && Row.Region == EDigimonRegion::RegionTwo)
            if (USoundBase* Victory = LoadBGM(TEXT("/DigimonVenomNXT/Generated/Audio/BGM/SW_ds_bgm30.SW_ds_bgm30"))) return Victory;
    }
    if (USoundBase* Named = LoadNamedBGM(Track)) return Named;
    if (Track == TrackType::Battle || Track == TrackType::Victory || Track == TrackType::SeasonVictory)
    {
        if (Track != TrackType::Battle)
            if (USoundBase* Battle = LoadNamedBGM(TrackType::Battle)) return Battle;
        if (USoundBase* MapBattle = LoadMapBGM(Routing.BattleMapId, true)) return MapBattle;
    }
    else if (Track != TrackType::GenericUI)
    {
        if (USoundBase* Generic = LoadNamedBGM(TrackType::GenericUI)) return Generic;
    }
    return LoadMapBGM(Routing.MapId, false);
}

void UDigimonVenomNXTAudioSubsystem::PlayExplorationForMap(int32 MapId)
{
    const bool bChangedMap = Routing.MapId > 0 && Routing.MapId != MapId;
    // Compatibility for old Blueprint callers; real battle owners are only cleared
    // explicitly by presentation teardown, never by a delayed map update.
    if (ActiveBattleOwner.Get() == this)
    {
        Routing.ClearBattle(MusicOwner(this));
        ActiveBattleOwner.Reset();
    }
    Routing.SetExploration(MapId);
    ApplyRouting();
    if (bChangedMap) PlayCue(EDigimonAudioCue::Travel);
}

void UDigimonVenomNXTAudioSubsystem::PlayBattleForMap(int32 MapId)
{
    SetBattleMusicState(this, MapId, false, false);
}

void UDigimonVenomNXTAudioSubsystem::SetDigiFarmActive(bool bActive)
{
    const bool bWasFarm = Routing.Field() == DigimonVenomNXTAudioRouting::Track::Farm;
    Routing.SetFarm(bActive);
    ApplyRouting();
    if (bWasFarm != bActive && Routing.MapId > 0) PlayCue(EDigimonAudioCue::Travel);
}

void UDigimonVenomNXTAudioSubsystem::PlayMainMenuMusic()
{
    ScreenOwners.Reset();
    ActiveBattleOwner.Reset();
    Routing.EnterMainMenu();
    ApplyRouting();
}

void UDigimonVenomNXTAudioSubsystem::SetUIScreenMusic(UObject* Owner, const FString& PageName)
{
    if (!IsValid(Owner)) return;
    const auto Id = MusicOwner(Owner);
    ScreenOwners.Add(Id, Owner);
    const FString Normalized = PageName.ToLower().Replace(TEXT(" "), TEXT(""));
    Routing.SetScreen(Id, DigimonVenomNXTAudioRouting::ScreenTrack(TCHAR_TO_UTF8(*Normalized)));
    ApplyRouting();
}

void UDigimonVenomNXTAudioSubsystem::ClearUIScreenMusic(UObject* Owner)
{
    const auto Id = MusicOwner(Owner);
    ScreenOwners.Remove(Id);
    Routing.ClearScreen(Id);
    ApplyRouting();
}

void UDigimonVenomNXTAudioSubsystem::SetBattleMusicState(UObject* BattleOwner, int32 MapId, bool bVictory, bool bSeasonMatch)
{
    if (!IsValid(BattleOwner)) return;
    ActiveBattleOwner = BattleOwner;
    Routing.SetBattle(MusicOwner(BattleOwner), MapId, bVictory, bSeasonMatch);
    ApplyRouting();
}

void UDigimonVenomNXTAudioSubsystem::ClearBattleMusicState(UObject* BattleOwner)
{
    if (BattleOwner) Routing.ClearBattle(MusicOwner(BattleOwner));
    else if (!ActiveBattleOwner.IsValid()) Routing.ClearBattle(Routing.GetBattleOwner());
    if (Routing.GetBattleOwner() == 0) ActiveBattleOwner.Reset();
    ApplyRouting();
}

void UDigimonVenomNXTAudioSubsystem::ApplyRouting()
{
    for (auto It = ScreenOwners.CreateIterator(); It; ++It)
    {
        if (!It.Value().IsValid())
        {
            Routing.ClearScreen(It.Key());
            It.RemoveCurrent();
        }
    }
    if (!ActiveBattleOwner.IsValid()) Routing.ClearBattle(Routing.GetBattleOwner());

    TArray<USoundBase*> Retained;
    const auto Retain = [&Retained](USoundBase* Sound) { if (Sound) Retained.AddUnique(Sound); };
    Retain(ResolveSound(Routing.Field()));
    Retain(ResolveSound(Routing.UI()));
    Retain(ResolveSound(Routing.Battle()));
    USoundBase* Desired = ResolveSound(Routing.Current());
    Retain(Desired);
    ApplySound(Desired, Retained, 0.20f);
}

void UDigimonVenomNXTAudioSubsystem::CancelMusicVoice(FDigimonMusicVoice& Voice)
{
    // Stop() also broadcasts completion. Invalidate ownership and remove our
    // delegate first, so teardown can never launch a retired track's next part.
    Voice.Playback.Cancel(++MusicGeneration);
    Voice.Continuation = nullptr;
    if (IsValid(Voice.Component)) Voice.Component->OnAudioFinishedNative.RemoveAll(this);
}

void UDigimonVenomNXTAudioSubsystem::StartOrResumeMusic(FDigimonMusicVoice& Voice, float FadeSeconds)
{
    UAudioComponent* Component = Voice.Component;
    if (!IsValid(Component) || Voice.Playback.Completed || Component != MusicComponent) return;
    const float Gain = MasterVolume * MusicVolume;
    if (!Voice.Playback.CanPlay(Component == MusicComponent, Gain > 0.0f)) { Component->SetPaused(true); return; }
    const bool bStopped = Voice.Playback.NeedsStart || Component->GetPlayState() == EAudioComponentPlayState::Stopped;
    Voice.Playback.NeedsStart = false;
    DigimonVenomNXTAudioRouting::ResumeOrStartVoice(*Component, bStopped, FadeSeconds, Gain);
}

void UDigimonVenomNXTAudioSubsystem::HandleMusicFinished(UAudioComponent* Component, uint64 Generation)
{
    FDigimonMusicVoice* Voice = MusicLayers.FindByPredicate([Component, Generation](const FDigimonMusicVoice& Entry)
    { return Entry.Component == Component && Entry.Playback.Generation == Generation; });
    if (!Voice || !IsValid(Component)) return;
    USoundBase* Next = Voice->Continuation;
    if (!Voice->Playback.Finish(Generation, ++MusicGeneration, Next != nullptr)) return;
    Voice->Continuation = nullptr;
    Component->OnAudioFinishedNative.RemoveAll(this);
    if (!Next) return;
    Component->SetSound(Next);
    Component->OnAudioFinishedNative.AddUObject(this, &UDigimonVenomNXTAudioSubsystem::HandleMusicFinished, Voice->Playback.Generation);
    // If a UI/battle override or mute arrived as the intro finished, retain the
    // loop at its start. Only the currently selected audible layer may play.
    StartOrResumeMusic(*Voice, 0.0f);
}

void UDigimonVenomNXTAudioSubsystem::ApplySound(USoundBase* Sound, const TArray<USoundBase*>& RetainedSounds, float FadeSeconds)
{
    // Retain by logical track, not the component's currently playing intro.
    // At most field, UI and battle/result voices remain, one audible at a time.
    for (int32 Index = MusicLayers.Num() - 1; Index >= 0; --Index)
    {
        FDigimonMusicVoice& Voice = MusicLayers[Index];
        if (!IsValid(Voice.Component) || !RetainedSounds.Contains(Voice.Track.Get()))
        {
            CancelMusicVoice(Voice);
            if (IsValid(Voice.Component)) { Voice.Component->Stop(); Voice.Component->DestroyComponent(); }
            MusicLayers.RemoveAt(Index);
        }
    }
    FDigimonMusicVoice* NextVoice = nullptr;
    for (FDigimonMusicVoice& Voice : MusicLayers)
    {
        if (Voice.Track == Sound) NextVoice = &Voice;
        else if (IsValid(Voice.Component)) Voice.Component->SetPaused(true);
    }
    CurrentSound = nullptr;
    MusicComponent = nullptr;
    if (!Sound) return;
    if (!NextVoice)
    {
        UWorld* World = GetLocalPlayer() ? GetLocalPlayer()->GetWorld() : nullptr;
        if (!World || World->GetNetMode() == NM_DedicatedServer) return;
        USoundBase* FirstSegment = Sound;
        USoundBase* Continuation = nullptr;
        if (const FDigimonMusicTrackInfo* Info = MusicTrackInfo.Find(FName(*Sound->GetPathName())))
        {
            if (!Info->IntroPath.IsEmpty())
            {
                if (USoundBase* Intro = LoadBGM(Info->IntroPath))
                { FirstSegment = Intro; Continuation = Sound; }
            }
            else if (!Info->ContinuationPath.IsEmpty()) Continuation = LoadBGM(Info->ContinuationPath);
        }
        UAudioComponent* Component = UGameplayStatics::CreateSound2D(World, FirstSegment, 1.0f, 1.0f, 0.0f, nullptr, true, false);
        if (!Component) return;
        FDigimonMusicVoice Voice;
        Voice.Component = Component;
        Voice.Track = Sound;
        Voice.Continuation = Continuation;
        Voice.Playback.Generation = ++MusicGeneration;
        Component->OnAudioFinishedNative.AddUObject(this, &UDigimonVenomNXTAudioSubsystem::HandleMusicFinished, Voice.Playback.Generation);
        NextVoice = &MusicLayers.Add_GetRef(Voice);
    }
    CurrentSound = Sound;
    MusicComponent = NextVoice->Component;
    StartOrResumeMusic(*NextVoice, FadeSeconds);
}

void UDigimonVenomNXTAudioSubsystem::PlayMusic(USoundBase* Sound, float FadeSeconds)
{
    if (!Sound) return;
    Routing.Reset();
    ScreenOwners.Reset();
    ActiveBattleOwner.Reset();
    TArray<USoundBase*> Retained;
    Retained.Add(Sound);
    ApplySound(Sound, Retained, FadeSeconds);
}

void UDigimonVenomNXTAudioSubsystem::ReleaseLayers(float FadeSeconds)
{
    for (FDigimonMusicVoice& Voice : MusicLayers)
    {
        UAudioComponent* Layer = Voice.Component;
        CancelMusicVoice(Voice);
        if (!IsValid(Layer)) continue;
        if (Layer == MusicComponent && FadeSeconds > 0.0f)
        {
            Layer->bAutoDestroy = true;
            Layer->FadeOut(FadeSeconds, 0.0f);
        }
        else { Layer->Stop(); Layer->DestroyComponent(); }
    }
    MusicLayers.Reset();
    MusicComponent = nullptr;
    CurrentSound = nullptr;
}

void UDigimonVenomNXTAudioSubsystem::StopMusic(float FadeSeconds)
{
    Routing.Reset();
    ScreenOwners.Reset();
    ActiveBattleOwner.Reset();
    ReleaseLayers(FMath::Max(0.0f, FadeSeconds));
}
