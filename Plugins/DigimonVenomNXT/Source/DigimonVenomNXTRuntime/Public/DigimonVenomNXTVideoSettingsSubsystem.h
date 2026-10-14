#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTVideoPolicyCore.h"
#include "DigimonVenomNXTVideoSettingsSubsystem.generated.h"

UENUM(BlueprintType)
enum class EDigimonDisplayMode : uint8 { Fullscreen, Borderless, Windowed };

UENUM(BlueprintType)
enum class EDigimonVideoPreset : uint8 { Optimized, Low, Balanced, High, Epic };

/** Device-local settings. Not part of a tamer profile, replicated state or account save. */
USTRUCT(BlueprintType)
struct DIGIMONVENOMNXTRUNTIME_API FDigimonVideoSettings
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") FIntPoint Resolution = FIntPoint(1280, 720);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") EDigimonDisplayMode DisplayMode = EDigimonDisplayMode::Borderless;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") float ResolutionScale = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") float FrameRateLimit = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") float Gamma = 2.2f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bVSync = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bDynamicResolution = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bHDR = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 HDRNits = 1000;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 ViewDistanceQuality = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 AntiAliasingQuality = 1;
    /** Zero explicitly disables dynamic/contact shadows; 1..4 are medium..cinematic. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 ShadowQuality = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 GlobalIlluminationQuality = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 ReflectionQuality = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 PostProcessQuality = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 TextureQuality = 3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 EffectsQuality = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 FoliageQuality = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 ShadingQuality = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 LandscapeQuality = 1;
    /** Engine enum values: 0 off, 1 FXAA, 2 TAA, 3 MSAA (forward only), 4 TSR. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") int32 AntiAliasingMethod = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bMotionBlur = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bDepthOfField = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bBloom = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bLensFlare = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bChromaticAberration = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Video") bool bAmbientOcclusion = false;
};

struct DIGIMONVENOMNXTRUNTIME_API FDigimonVideoCapabilities
{
    bool bRuntimeAvailable = false;
    bool bCanChangeDisplay = false;
    bool bSupportsHDR = false;
    bool bSupportsDynamicResolution = false;
    bool bSupportsTSR = false;
    bool bSupportsMSAA = false;
    float MinResolutionScale = 50.0f;
    float MaxResolutionScale = 100.0f;
    FIntPoint DesktopResolution = FIntPoint(1280, 720);
    FString RuntimeReason;
    FString DisplayReason;
    FString HDRReason;
    FString DynamicResolutionReason;
    TArray<FIntPoint> FullscreenResolutions;
    TArray<FIntPoint> WindowedResolutions;
    TArray<int32> AntiAliasingMethods;
};

/** A game-instance lifetime owns the confirmation countdown, including hidden/destroyed menus. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTVideoSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    bool IsReady() const { return bReady; }
    const FDigimonVideoSettings& GetPendingSettings() const { return Pending; }
    const FDigimonVideoSettings& GetAppliedSettings() const { return Applied; }
    void SetPendingSettings(const FDigimonVideoSettings& Settings);
    void SetPreset(EDigimonVideoPreset Preset);
    void DiscardPending();
    bool HasPendingChanges() const;
    bool ApplyPending(FString& OutError);
    bool IsAwaitingConfirmation() const { return Confirmation.IsPending(); }
    int32 GetConfirmationSecondsRemaining() const;
    bool ConfirmVideoMode();
    void RevertVideoMode();
    FDigimonVideoCapabilities GetCapabilities() const;
    FString GetStatusMessage() const { return StatusMessage; }
    /** Actual engine-side limiter, not the configured target. VSync/driver can cap further. */
    float GetEffectiveFrameRateLimit() const;

private:
    UPROPERTY(Transient) FDigimonVideoSettings Pending;
    UPROPERTY(Transient) FDigimonVideoSettings Applied;
    UPROPERTY(Transient) FDigimonVideoSettings Confirmed;
    FTSTicker::FDelegateHandle TickHandle;
    DigimonVenomNXTVideoPolicy::Confirmation Confirmation;
    FDigimonVideoCapabilities Capabilities;
    FString StatusMessage;
    bool bReady = false;
    bool bHadSettingsFileAtStartup = false;
    bool bCapturedFramePolicy = false;
    bool bOriginalSmoothFrameRate = false;
    bool bOriginalFixedFrameRate = false;
    bool bOriginalUseFixedTimeStep = false;
    bool TickVideoSettings(float DeltaSeconds);
    void TryInitialize();
    void RefreshCapabilities();
    FDigimonVideoSettings ReadEngineSettings() const;
    FDigimonVideoSettings Sanitize(const FDigimonVideoSettings& Settings) const;
    void ApplyToEngine(const FDigimonVideoSettings& Settings, bool bApplyDisplay, bool bRespectCommandLine = false);
    FDigimonVideoSettings ReadAppliedResult(const FDigimonVideoSettings& Requested) const;
    void PersistConfirmed();
    void SetRecoveryPending(bool bPending);
    void ConfigureFramePolicy();
};
