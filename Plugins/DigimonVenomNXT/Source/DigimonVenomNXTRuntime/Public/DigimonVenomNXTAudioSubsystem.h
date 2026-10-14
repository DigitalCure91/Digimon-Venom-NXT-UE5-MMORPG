#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "DigimonVenomNXTAudioRoutingCore.h"
#include "DigimonVenomNXTAudioCueCore.h"
#include "DigimonVenomNXTAudioSubsystem.generated.h"

class UAudioComponent;
class USoundBase;
class UWidget;

UENUM(BlueprintType)
enum class EDigimonAudioCue : uint8
{
    UIHover, UIClick, UIBack, UINavigate, Confirm, Error, Heal, Item, Purchase,
    PhysicalAttack, SpecialAttack, Hit, Guard, Knockout, Victory, Defeat, Flee,
    Travel, Interaction, Encounter, EffectiveHit
};

USTRUCT()
struct FDigimonEffectVoice
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UAudioComponent> Component;
    bool bUI = false;
    float Gain = 1.0f;
};

/** A retained logical track can start on a different, non-looping intro wave. */
USTRUCT()
struct FDigimonMusicVoice
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UAudioComponent> Component;
    UPROPERTY(Transient) TObjectPtr<USoundBase> Track;
    UPROPERTY(Transient) TObjectPtr<USoundBase> Continuation;
    DigimonVenomNXTAudioRouting::SequenceState Playback;
};

struct FDigimonMusicTrackInfo
{
    FString IntroPath;
    FString ContinuationPath;
    bool bLooping = true;
};

/** Client-local music controller. Keeps replicated gameplay free of audio state while exposing Blueprint hooks. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTAudioSubsystem : public ULocalPlayerSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Local sound feedback. Never sends network traffic or changes BGM routing. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayCue(EDigimonAudioCue Cue);

    /** Stable receipt key suppresses repeated replicated events, including widget recreation. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayCueOnce(EDigimonAudioCue Cue, const FString& EventKey);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void SetAudioVolumes(float Master, float Music, float Effects, float UI, bool bSave = true);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Audio") float GetMasterVolume() const { return MasterVolume; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Audio") float GetMusicVolume() const { return MusicVolume; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Audio") float GetEffectsVolume() const { return EffectsVolume; }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Audio") float GetUIVolume() const { return UIVolume; }

    static void PlayForWidget(const UWidget* Widget, EDigimonAudioCue Cue);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayExplorationForMap(int32 MapId);

    /** The private farm is a field context, so nonmodal care cannot stop its music. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void SetDigiFarmActive(bool bActive);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayBattleForMap(int32 MapId);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayMainMenuMusic();

    /** Visible UI owners update in place; nested owners restore when closed. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void SetUIScreenMusic(UObject* Owner, const FString& PageName);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void ClearUIScreenMusic(UObject* Owner);

    /** Battle/result presentation overrides UI until that battle is dismissed. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void SetBattleMusicState(UObject* BattleOwner, int32 MapId, bool bVictory, bool bSeasonMatch);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void ClearBattleMusicState(UObject* BattleOwner);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void PlayMusic(USoundBase* Sound, float FadeSeconds = 0.35f);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Audio")
    void StopMusic(float FadeSeconds = 0.35f);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Audio")
    USoundBase* GetCurrentMusic() const { return CurrentSound; }

private:
    UPROPERTY(Transient) TArray<FDigimonEffectVoice> EffectVoices;
    UPROPERTY(Transient) TMap<FName, TObjectPtr<USoundBase>> LoadedEffects;
    TSet<FName> MissingEffects;
    DigimonVenomNXTAudioCueCore::Gate CueGate;
    float MasterVolume = 1.0f;
    float MusicVolume = 1.0f;
    float EffectsVolume = 0.85f;
    float UIVolume = 0.75f;
    void PlayCueInternal(EDigimonAudioCue Cue, const FString& EventKey);
    void ApplyVolumes();
    FString AudioConfigSection() const;
    UPROPERTY(Transient) TObjectPtr<UAudioComponent> MusicComponent;
    UPROPERTY(Transient) TObjectPtr<USoundBase> CurrentSound;
    UPROPERTY(Transient) TArray<FDigimonMusicVoice> MusicLayers;
    UPROPERTY(Transient) TMap<FName, TObjectPtr<USoundBase>> LoadedTracks;
    TSet<FName> MissingTracks;
    TMap<FName, FDigimonMusicTrackInfo> MusicTrackInfo;
    uint64 MusicGeneration = 0;
    void LoadMusicMetadata();
    void HandleMusicFinished(UAudioComponent* Component, uint64 Generation);
    void StartOrResumeMusic(FDigimonMusicVoice& Voice, float FadeSeconds);
    void CancelMusicVoice(FDigimonMusicVoice& Voice);
    TMap<DigimonVenomNXTAudioRouting::Owner, TWeakObjectPtr<UObject>> ScreenOwners;
    TWeakObjectPtr<UObject> ActiveBattleOwner;
    DigimonVenomNXTAudioRouting::State Routing;
    void ApplyRouting();
    void ApplySound(USoundBase* Sound, const TArray<USoundBase*>& RetainedSounds, float FadeSeconds);
    USoundBase* ResolveSound(DigimonVenomNXTAudioRouting::Track Track);
    USoundBase* LoadBGM(const FString& ObjectPath);
    USoundBase* LoadNamedBGM(DigimonVenomNXTAudioRouting::Track Track);
    USoundBase* LoadMapBGM(int32 MapId, bool bBattle);
    void ReleaseLayers(float FadeSeconds);
};
