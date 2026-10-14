#include "DigimonVenomNXTVideoSettingsSubsystem.h"
#include "DigimonVenomNXTCustomDepth.h"
#include "DynamicResolutionState.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "GameFramework/GameUserSettings.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformTime.h"
#include "JsonObjectConverter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/App.h"
#include "Misc/ConfigCacheIni.h"
#include "UnrealClient.h"

namespace DigimonVideoRuntime
{
    static const TCHAR* ConfigSection = TEXT("DigimonVenomNXT.LocalVideo");
    static int32 ReadInt(const TCHAR* Name, int32 Fallback)
    {
        const IConsoleVariable* Variable = IConsoleManager::Get().FindConsoleVariable(Name);
        return Variable ? Variable->GetInt() : Fallback;
    }
    static float ReadFloat(const TCHAR* Name, float Fallback)
    {
        const IConsoleVariable* Variable = IConsoleManager::Get().FindConsoleVariable(Name);
        return Variable ? Variable->GetFloat() : Fallback;
    }
    static bool WriteInt(const TCHAR* Name, int32 Value)
    {
        IConsoleVariable* Variable = IConsoleManager::Get().FindConsoleVariable(Name);
        if (!Variable || (Variable->GetFlags() & ECVF_ReadOnly) != 0) return false;
        // A deliberate game preference may override scalability/device defaults,
        // but never a higher-priority developer console or command-line override.
        if ((Variable->GetFlags() & ECVF_SetByMask) > ECVF_SetByGameOverride) return Variable->GetInt() == Value;
        Variable->Set(Value, ECVF_SetByGameOverride);
        return Variable->GetInt() == Value;
    }
    static bool WriteFloat(const TCHAR* Name, float Value)
    {
        IConsoleVariable* Variable = IConsoleManager::Get().FindConsoleVariable(Name);
        if (!Variable || (Variable->GetFlags() & ECVF_ReadOnly) != 0) return false;
        if ((Variable->GetFlags() & ECVF_SetByMask) > ECVF_SetByGameOverride) return FMath::IsNearlyEqual(Variable->GetFloat(), Value);
        Variable->Set(Value, ECVF_SetByGameOverride);
        return FMath::IsNearlyEqual(Variable->GetFloat(), Value);
    }
    static bool IsUsableResolution(const FIntPoint& Resolution)
    {
        return Resolution.X >= 640 && Resolution.Y >= 480 && Resolution.X <= 16384 && Resolution.Y <= 16384;
    }
    static EWindowMode::Type EngineMode(EDigimonDisplayMode Mode)
    {
        switch (Mode)
        {
        case EDigimonDisplayMode::Fullscreen: return EWindowMode::Fullscreen;
        case EDigimonDisplayMode::Windowed: return EWindowMode::Windowed;
        default: return EWindowMode::WindowedFullscreen;
        }
    }
    static EDigimonDisplayMode GameMode(EWindowMode::Type Mode)
    {
        if (Mode == EWindowMode::Fullscreen) return EDigimonDisplayMode::Fullscreen;
        if (Mode == EWindowMode::Windowed) return EDigimonDisplayMode::Windowed;
        return EDigimonDisplayMode::Borderless;
    }
    static void SortResolutions(TArray<FIntPoint>& Values, const FIntPoint& Current, const FIntPoint& Desktop, bool bIncludeCurrent)
    {
        Values.RemoveAll([](const FIntPoint& Item) { return !IsUsableResolution(Item); });
        if (bIncludeCurrent && IsUsableResolution(Current)) Values.AddUnique(Current);
        if (IsUsableResolution(Desktop)) Values.AddUnique(Desktop);
        Values.Sort([](const FIntPoint& A, const FIntPoint& B)
        {
            return A.X == B.X ? A.Y < B.Y : A.X < B.X;
        });
        for (int32 Index = Values.Num() - 1; Index > 0; --Index)
            if (Values[Index] == Values[Index - 1]) Values.RemoveAt(Index);
    }
}

void UDigimonVenomNXTVideoSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    bHadSettingsFileAtStartup = IFileManager::Get().FileSize(*GGameUserSettingsIni) > 0;
    // The core ticker survives widget removal, paused worlds and level travel.
    // No timer manager or replicated actor owns the 15-second safety window.
    if (!IsRunningDedicatedServer())
    {
        TickHandle = FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateUObject(this, &UDigimonVenomNXTVideoSettingsSubsystem::TickVideoSettings), 0.1f);
        TryInitialize();
    }
}

void UDigimonVenomNXTVideoSettingsSubsystem::TryInitialize()
{
    UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings();
    const UWorld* CurrentWorld = GetWorld();
    if (bReady || !EngineSettings || !CurrentWorld || CurrentWorld->GetNetMode() == NM_DedicatedServer) return;
    if (!GIsEditor && (!GEngine || !GEngine->GameViewport || !GEngine->GameViewport->Viewport)) return;
    RefreshCapabilities();
    Applied = ReadEngineSettings();
    Pending = Applied;
    Confirmed = Applied;
    bReady = true;
    if (!Capabilities.bRuntimeAvailable)
    {
        StatusMessage = Capabilities.RuntimeReason;
        return;
    }

    FString SavedJSON;
    bool bRecoveryPending = false;
    int32 SavedSchema = 0;
    if (GConfig)
    {
        GConfig->GetString(DigimonVideoRuntime::ConfigSection, TEXT("ConfirmedSettings"), SavedJSON, GGameUserSettingsIni);
        GConfig->GetBool(DigimonVideoRuntime::ConfigSection, TEXT("UnconfirmedPreview"), bRecoveryPending, GGameUserSettingsIni);
        GConfig->GetInt(DigimonVideoRuntime::ConfigSection, TEXT("Schema"), SavedSchema, GGameUserSettingsIni);
    }
    FDigimonVideoSettings Saved;
    const bool bHaveSaved = SavedSchema == 1 && !SavedJSON.IsEmpty() &&
        FJsonObjectConverter::JsonObjectStringToUStruct(SavedJSON, &Saved, 0, 0);
    if (bHaveSaved)
    {
        // Stock GameUserSettings is authoritative for standard fields; our JSON
        // stores the additional controls and a durable complete rollback point.
        FDigimonVideoSettings Restored = bRecoveryPending ? Saved : Applied;
        Restored.AntiAliasingMethod = Saved.AntiAliasingMethod;
        Restored.Gamma = Saved.Gamma;
        Restored.bMotionBlur = Saved.bMotionBlur;
        Restored.bDepthOfField = Saved.bDepthOfField;
        Restored.bBloom = Saved.bBloom;
        Restored.bLensFlare = Saved.bLensFlare;
        Restored.bChromaticAberration = Saved.bChromaticAberration;
        Restored.bAmbientOcclusion = Saved.bAmbientOcclusion;
        Restored = Sanitize(Restored);
        // Monitor changes must never replay an unavailable exclusive resolution.
        bool bNeedsDisplayRecovery = bRecoveryPending;
        if (Restored.DisplayMode == EDigimonDisplayMode::Fullscreen &&
            !Capabilities.FullscreenResolutions.Contains(Restored.Resolution))
        {
            Restored.DisplayMode = EDigimonDisplayMode::Borderless;
            Restored.Resolution = Capabilities.DesktopResolution;
            bNeedsDisplayRecovery = true;
        }
        // Startup honors a user's -windowed/-ResX recovery arguments. Explicit
        // Apply from the menu is the later deliberate display-mode change.
        ApplyToEngine(Restored, bNeedsDisplayRecovery, true);
        Applied = ReadAppliedResult(Restored);
        Confirmed = Applied;
        Pending = Applied;
        PersistConfirmed();
        StatusMessage = bRecoveryPending ? TEXT("Recovered your last confirmed video settings after an interrupted display preview.") :
            TEXT("Your video settings are saved on this device.");
    }
    else if (!bHadSettingsFileAtStartup)
    {
        DigimonVenomNXTVideoPolicy::ApplyPreset(Pending, static_cast<int32>(EDigimonVideoPreset::Optimized));
        Pending.FrameRateLimit = 0.0f;
        Pending.bVSync = false;
        Pending = Sanitize(Pending);
        // First use never silently changes the window mode or display resolution.
        ApplyToEngine(Pending, false);
        Applied = ReadAppliedResult(Pending);
        Pending = Applied;
        Confirmed = Applied;
        PersistConfirmed();
        StatusMessage = TEXT("Digimon Optimized is ready: shadows off, crisp sprite textures and no motion blur. Choose a frame limit for your device.");
    }
    else
    {
        // A pre-menu installation may already have an auto-generated engine ini.
        // Migrate only the explicitly requested 2D defaults; retain its other
        // quality choices, display mode, resolution, frame target and VSync.
        Pending.ShadowQuality = 0;
        Pending.bMotionBlur = false;
        Pending.bDepthOfField = false;
        Pending = Sanitize(Pending);
        ApplyToEngine(Pending, false);
        Applied = ReadAppliedResult(Pending);
        Pending = Applied;
        Confirmed = Applied;
        PersistConfirmed();
        StatusMessage = TEXT("Video settings added: shadows, motion blur and depth of field are off for clear 2D play. Your other existing settings were preserved.");
    }
}

void UDigimonVenomNXTVideoSettingsSubsystem::RefreshCapabilities()
{
    using namespace DigimonVideoRuntime;
    Capabilities = FDigimonVideoCapabilities();
    UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings();
    const UWorld* CurrentWorld = GetWorld();
    const bool bHasViewport = GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport;
    Capabilities.bRuntimeAvailable = EngineSettings && CurrentWorld && bHasViewport && !GIsEditor &&
        !IsRunningDedicatedServer() && CurrentWorld->GetNetMode() != NM_DedicatedServer;
    if (GIsEditor) Capabilities.RuntimeReason = TEXT("Video settings can be viewed here. To change them, launch Standalone Game or a packaged game; Play In Editor shares the editor renderer.");
    else if (!Capabilities.bRuntimeAvailable) Capabilities.RuntimeReason = TEXT("Video settings become available when a local game window is ready.");
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
    Capabilities.bCanChangeDisplay = Capabilities.bRuntimeAvailable;
#endif
    Capabilities.DisplayReason = Capabilities.bCanChangeDisplay ? FString() :
        (GIsEditor ? Capabilities.RuntimeReason : TEXT("This platform manages the display mode and output resolution."));
    if (EngineSettings)
    {
        Capabilities.DesktopResolution = EngineSettings->GetDesktopResolution();
        if (!IsUsableResolution(Capabilities.DesktopResolution)) Capabilities.DesktopResolution = FIntPoint(1280, 720);
        float Normalized = 1.0f, CurrentScale = 100.0f, Minimum = 50.0f, Maximum = 100.0f;
        EngineSettings->GetResolutionScaleInformationEx(Normalized, CurrentScale, Minimum, Maximum);
        Capabilities.MinResolutionScale = FMath::Clamp(Minimum, 25.0f, 100.0f);
        Capabilities.MaxResolutionScale = FMath::Clamp(Maximum, Capabilities.MinResolutionScale, 100.0f);
        Capabilities.bSupportsHDR = Capabilities.bRuntimeAvailable && EngineSettings->SupportsHDRDisplayOutput() && ReadInt(TEXT("r.AllowHDR"), 0) != 0;
        TArray<FIntPoint> Fullscreen, Windowed;
        const bool bEnumeratedFullscreen = UKismetSystemLibrary::GetSupportedFullscreenResolutions(Fullscreen);
        UKismetSystemLibrary::GetConvenientWindowedResolutions(Windowed);
        // Do not add a stale saved exclusive mode to a successful device query:
        // that would incorrectly "validate" a resolution from a removed monitor.
        SortResolutions(Fullscreen, EngineSettings->GetScreenResolution(), Capabilities.DesktopResolution,
            !bEnumeratedFullscreen || Fullscreen.IsEmpty());
        SortResolutions(Windowed, EngineSettings->GetScreenResolution(), Capabilities.DesktopResolution, true);
        Capabilities.FullscreenResolutions = MoveTemp(Fullscreen);
        Capabilities.WindowedResolutions = MoveTemp(Windowed);
    }
    IDynamicResolutionState* DynamicState = GEngine ? GEngine->GetDynamicResolutionState() : nullptr;
    Capabilities.bSupportsDynamicResolution = Capabilities.bRuntimeAvailable && DynamicState && DynamicState->IsSupported();
    Capabilities.HDRReason = Capabilities.bSupportsHDR ? FString() :
        TEXT("HDR requires an HDR-capable display, enabled OS HDR and HDR output allowed by the project renderer.");
    Capabilities.DynamicResolutionReason = Capabilities.bSupportsDynamicResolution ? FString() :
        TEXT("Dynamic resolution is unavailable on this platform or renderer. Use render scale instead.");
    const bool bDesktopRenderer = CurrentWorld && CurrentWorld->GetFeatureLevel() >= ERHIFeatureLevel::SM5;
    const bool bForwardRenderer = ReadInt(TEXT("r.ForwardShading"), 0) != 0;
    Capabilities.bSupportsTSR = bDesktopRenderer && !bForwardRenderer;
    Capabilities.bSupportsMSAA = bDesktopRenderer && bForwardRenderer;
    Capabilities.AntiAliasingMethods = { 0, 1, 2 };
    if (Capabilities.bSupportsMSAA) Capabilities.AntiAliasingMethods.Add(3);
    if (Capabilities.bSupportsTSR) Capabilities.AntiAliasingMethods.Add(4);
}

FDigimonVideoCapabilities UDigimonVenomNXTVideoSettingsSubsystem::GetCapabilities() const
{
    return Capabilities;
}

FDigimonVideoSettings UDigimonVenomNXTVideoSettingsSubsystem::ReadEngineSettings() const
{
    using namespace DigimonVideoRuntime;
    FDigimonVideoSettings Result;
    UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings();
    if (!EngineSettings) return Result;
    Result.Resolution = EngineSettings->GetScreenResolution();
    if (!IsUsableResolution(Result.Resolution)) Result.Resolution = Capabilities.DesktopResolution;
    Result.DisplayMode = GameMode(EngineSettings->GetFullscreenMode());
    float Normalized = 1.0f, Minimum = 50.0f, Maximum = 100.0f;
    EngineSettings->GetResolutionScaleInformationEx(Normalized, Result.ResolutionScale, Minimum, Maximum);
    Result.FrameRateLimit = EngineSettings->GetFrameRateLimit();
    Result.bVSync = EngineSettings->IsVSyncEnabled();
    Result.bDynamicResolution = EngineSettings->IsDynamicResolutionEnabled();
    Result.bHDR = EngineSettings->IsHDREnabled();
    Result.HDRNits = EngineSettings->GetCurrentHDRDisplayNits() < 1500 ? 1000 : 2000;
    if (!Result.bHDR) Result.HDRNits = 1000;
    Result.ViewDistanceQuality = EngineSettings->GetViewDistanceQuality();
    Result.AntiAliasingQuality = EngineSettings->GetAntiAliasingQuality();
    Result.ShadowQuality = EngineSettings->GetShadowQuality();
    Result.GlobalIlluminationQuality = EngineSettings->GetGlobalIlluminationQuality();
    Result.ReflectionQuality = EngineSettings->GetReflectionQuality();
    Result.PostProcessQuality = EngineSettings->GetPostProcessingQuality();
    Result.TextureQuality = EngineSettings->GetTextureQuality();
    Result.EffectsQuality = EngineSettings->GetVisualEffectQuality();
    Result.FoliageQuality = EngineSettings->GetFoliageQuality();
    Result.ShadingQuality = EngineSettings->GetShadingQuality();
    Result.LandscapeQuality = EngineSettings->GetLandscapeQuality();
    Result.AntiAliasingMethod = ReadInt(TEXT("r.AntiAliasingMethod"), 1);
    Result.bMotionBlur = ReadInt(TEXT("r.MotionBlurQuality"), 0) > 0;
    Result.bDepthOfField = ReadInt(TEXT("r.DepthOfFieldQuality"), 0) > 0;
    Result.bBloom = ReadInt(TEXT("r.BloomQuality"), 5) > 0;
    Result.bLensFlare = ReadInt(TEXT("r.LensFlareQuality"), 0) > 0;
    Result.bChromaticAberration = ReadInt(TEXT("r.SceneColorFringeQuality"), 0) > 0;
    Result.bAmbientOcclusion = ReadInt(TEXT("r.AmbientOcclusionLevels"), -1) != 0;
    const float GammaValue = ReadFloat(TEXT("r.TonemapperGamma"), 0.0f);
    Result.Gamma = GammaValue > 0.0f ? GammaValue : 2.2f;
    return Result;
}

FDigimonVideoSettings UDigimonVenomNXTVideoSettingsSubsystem::Sanitize(const FDigimonVideoSettings& Settings) const
{
    FDigimonVideoSettings Result = Settings;
    DigimonVenomNXTVideoPolicy::Sanitize(Result, Capabilities.MinResolutionScale, Capabilities.MaxResolutionScale);
    if (static_cast<uint8>(Result.DisplayMode) > static_cast<uint8>(EDigimonDisplayMode::Windowed)) Result.DisplayMode = EDigimonDisplayMode::Borderless;
    if (!DigimonVideoRuntime::IsUsableResolution(Result.Resolution)) Result.Resolution = Capabilities.DesktopResolution;
    if (Result.DisplayMode == EDigimonDisplayMode::Borderless) Result.Resolution = Capabilities.DesktopResolution;
    if (!Capabilities.AntiAliasingMethods.Contains(Result.AntiAliasingMethod)) Result.AntiAliasingMethod = 1;
    if (!Capabilities.bSupportsHDR) Result.bHDR = false;
    if (!Capabilities.bSupportsDynamicResolution) Result.bDynamicResolution = false;
    return Result;
}

void UDigimonVenomNXTVideoSettingsSubsystem::SetPendingSettings(const FDigimonVideoSettings& Settings)
{
    if (!Confirmation.IsPending()) Pending = Sanitize(Settings);
}

void UDigimonVenomNXTVideoSettingsSubsystem::SetPreset(EDigimonVideoPreset Preset)
{
    if (Confirmation.IsPending()) return;
    DigimonVenomNXTVideoPolicy::ApplyPreset(Pending, static_cast<int32>(Preset));
    Pending = Sanitize(Pending);
    StatusMessage = TEXT("Preset staged. Apply to use it; display mode, frame limit, VSync and HDR are unchanged.");
}

void UDigimonVenomNXTVideoSettingsSubsystem::DiscardPending()
{
    if (Confirmation.IsPending()) RevertVideoMode();
    Pending = Applied;
    StatusMessage = TEXT("Unapplied changes discarded.");
}

bool UDigimonVenomNXTVideoSettingsSubsystem::HasPendingChanges() const
{
    return !DigimonVenomNXTVideoPolicy::Equal(Pending, Applied);
}

void UDigimonVenomNXTVideoSettingsSubsystem::ConfigureFramePolicy()
{
    if (!Capabilities.bRuntimeAvailable || GIsEditor || IsRunningDedicatedServer() || !GEngine) return;
    if (!bCapturedFramePolicy)
    {
        bOriginalSmoothFrameRate = GEngine->bSmoothFrameRate;
        bOriginalFixedFrameRate = GEngine->bUseFixedFrameRate;
        bOriginalUseFixedTimeStep = FApp::UseFixedTimeStep();
        bCapturedFramePolicy = true;
    }
    // The selected cap is the one game-side limiter. A hidden project 60 FPS
    // smoothing/fixed-rate ceiling must not contradict Unlimited or 144 FPS.
    GEngine->bSmoothFrameRate = false;
    GEngine->bUseFixedFrameRate = false;
    FApp::SetUseFixedTimeStep(false);
}

void UDigimonVenomNXTVideoSettingsSubsystem::ApplyToEngine(const FDigimonVideoSettings& Settings, bool bApplyDisplay, bool bRespectCommandLine)
{
    using namespace DigimonVideoRuntime;
    UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings();
    if (!EngineSettings || !Capabilities.bRuntimeAvailable || GIsEditor || IsRunningDedicatedServer()) return;
    ConfigureFramePolicy();
    EngineSettings->SetScreenResolution(Settings.Resolution);
    EngineSettings->SetFullscreenMode(EngineMode(Settings.DisplayMode));
    EngineSettings->SetVSyncEnabled(Settings.bVSync);
    EngineSettings->SetFrameRateLimit(Settings.FrameRateLimit);
    EngineSettings->SetDynamicResolutionEnabled(Settings.bDynamicResolution);
    EngineSettings->SetViewDistanceQuality(Settings.ViewDistanceQuality);
    EngineSettings->SetAntiAliasingQuality(Settings.AntiAliasingQuality);
    EngineSettings->SetShadowQuality(Settings.ShadowQuality);
    EngineSettings->SetGlobalIlluminationQuality(Settings.GlobalIlluminationQuality);
    EngineSettings->SetReflectionQuality(Settings.ReflectionQuality);
    EngineSettings->SetPostProcessingQuality(Settings.PostProcessQuality);
    EngineSettings->SetTextureQuality(Settings.TextureQuality);
    EngineSettings->SetVisualEffectQuality(Settings.EffectsQuality);
    EngineSettings->SetFoliageQuality(Settings.FoliageQuality);
    EngineSettings->SetShadingQuality(Settings.ShadingQuality);
    EngineSettings->SetLandscapeQuality(Settings.LandscapeQuality);
    EngineSettings->SetResolutionScaleValueEx(Settings.ResolutionScale);
    // ApplySettings() auto-saves. Never use it for an unconfirmed display preview.
    if (bApplyDisplay && Capabilities.bCanChangeDisplay) EngineSettings->ApplyResolutionSettings(bRespectCommandLine);
    EngineSettings->ApplyNonResolutionSettings();
    if (Capabilities.bSupportsHDR) EngineSettings->EnableHDRDisplayOutput(Settings.bHDR, Settings.HDRNits);

    bool bAllOverridesApplied = true;
    bAllOverridesApplied &= WriteFloat(TEXT("t.MaxFPS"), Settings.FrameRateLimit);
    bAllOverridesApplied &= WriteInt(TEXT("r.VSync"), Settings.bVSync ? 1 : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.AntiAliasingMethod"), Settings.AntiAliasingMethod);
    bAllOverridesApplied &= WriteInt(TEXT("r.ShadowQuality"), Settings.ShadowQuality == 0 ? 0 : (Settings.ShadowQuality == 1 ? 2 : 5));
    bAllOverridesApplied &= WriteInt(TEXT("r.ContactShadows"), Settings.ShadowQuality == 0 ? 0 : 1);
    bAllOverridesApplied &= WriteInt(TEXT("r.MotionBlurQuality"), Settings.bMotionBlur ? FMath::Clamp(Settings.PostProcessQuality + 1, 1, 4) : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.DepthOfFieldQuality"), Settings.bDepthOfField ? FMath::Clamp(Settings.PostProcessQuality, 1, 4) : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.BloomQuality"), Settings.bBloom ? 5 : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.LensFlareQuality"), Settings.bLensFlare ? 2 : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.SceneColorFringeQuality"), Settings.bChromaticAberration ? 1 : 0);
    bAllOverridesApplied &= WriteInt(TEXT("r.AmbientOcclusionLevels"), Settings.bAmbientOcclusion ? -1 : 0);
    // SDR gamma must not leak into the HDR transfer function; retain the choice
    // in the snapshot so switching back to SDR restores the selected brightness.
    bAllOverridesApplied &= WriteFloat(TEXT("r.TonemapperGamma"), Settings.bHDR || FMath::IsNearlyEqual(Settings.Gamma, 2.2f) ? 0.0f : Settings.Gamma);
    if (Capabilities.bSupportsDynamicResolution)
    {
        // OperationMode=1 honors the user setting; 0 would silently disable it.
        bAllOverridesApplied &= WriteInt(TEXT("r.DynamicRes.OperationMode"), 1);
        const float TargetFPS = Settings.FrameRateLimit > 0.0f ? Settings.FrameRateLimit : 60.0f;
        bAllOverridesApplied &= WriteFloat(TEXT("r.DynamicRes.FrameTimeBudget"), 1000.0f / TargetFPS);
    }
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    bAllOverridesApplied &= WriteInt(TEXT("r.PostProcessing.DisableMaterials"), 0);
    // Scalability adjusts optional passes; the cel-shading blendable and stencil
    // infrastructure remain enabled even at Low. Never set ShowFlag.PostProcessing.
    StatusMessage = bAllOverridesApplied ? TEXT("Video settings applied.") :
        TEXT("Settings applied. Some renderer values are controlled by a developer console or command-line override; remove that override to change them here.");
}

bool UDigimonVenomNXTVideoSettingsSubsystem::ApplyPending(FString& OutError)
{
    OutError.Reset();
    TryInitialize();
    RefreshCapabilities();
    if (!bReady || !Capabilities.bRuntimeAvailable)
    {
        OutError = Capabilities.RuntimeReason;
        return false;
    }
    if (Confirmation.IsPending())
    {
        OutError = TEXT("Keep or revert the current display preview first.");
        return false;
    }
    if (!GConfig || IFileManager::Get().IsReadOnly(*GGameUserSettingsIni))
    {
        OutError = TEXT("The local video settings file is read-only. Make GameUserSettings.ini writable and try again.");
        return false;
    }
    FDigimonVideoSettings Candidate = Sanitize(Pending);
    if (!Capabilities.bCanChangeDisplay)
    {
        Candidate.DisplayMode = Applied.DisplayMode;
        Candidate.Resolution = Applied.Resolution;
    }
    const TArray<FIntPoint>& Available = Candidate.DisplayMode == EDigimonDisplayMode::Windowed ?
        Capabilities.WindowedResolutions : Capabilities.FullscreenResolutions;
    if (Candidate.DisplayMode != EDigimonDisplayMode::Borderless && !Available.Contains(Candidate.Resolution))
    {
        OutError = TEXT("That resolution is no longer available on this display. Choose a listed resolution or Borderless.");
        return false;
    }
    Pending = Candidate;
    if (DigimonVenomNXTVideoPolicy::Equal(Pending, Applied))
    {
        StatusMessage = TEXT("Your video settings are already up to date.");
        return true;
    }
    const bool bNeedsPreview = DigimonVenomNXTVideoPolicy::NeedsConfirmation(Applied, Candidate);
    if (bNeedsPreview)
    {
        Confirmed = Applied;
        // Write rollback data BEFORE a display change or HDR call. An unrelated
        // engine SaveSettings during preview cannot replace this recovery point.
        PersistConfirmed();
        SetRecoveryPending(true);
        Confirmation.Begin(FPlatformTime::Seconds());
    }
    ApplyToEngine(Candidate, bNeedsPreview);
    Applied = ReadAppliedResult(Candidate);
    Pending = Applied;
    if (!bNeedsPreview)
    {
        Confirmed = Applied;
        PersistConfirmed();
    }
    return true;
}

FDigimonVideoSettings UDigimonVenomNXTVideoSettingsSubsystem::ReadAppliedResult(const FDigimonVideoSettings& Requested) const
{
    FDigimonVideoSettings Result = Requested;
    if (UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings())
    {
        // HDR backends may force exclusive fullscreen or reject HDR. Report the
        // engine's accepted state rather than presenting the request as success.
        Result.DisplayMode = DigimonVideoRuntime::GameMode(EngineSettings->GetFullscreenMode());
        Result.Resolution = EngineSettings->GetScreenResolution();
        Result.bHDR = EngineSettings->IsHDREnabled();
        if (Result.bHDR) Result.HDRNits = EngineSettings->GetCurrentHDRDisplayNits() < 1500 ? 1000 : 2000;
        float Normalized = 1.0f, Minimum = 50.0f, Maximum = 100.0f;
        EngineSettings->GetResolutionScaleInformationEx(Normalized, Result.ResolutionScale, Minimum, Maximum);
    }
    // Keep the saved SDR gamma while HDR uses its separate transfer function.
    return Result;
}

void UDigimonVenomNXTVideoSettingsSubsystem::PersistConfirmed()
{
    UGameUserSettings* EngineSettings = UGameUserSettings::GetGameUserSettings();
    if (!GConfig || !EngineSettings || !Capabilities.bRuntimeAvailable) return;
    EngineSettings->ConfirmVideoMode();
    EngineSettings->SaveSettings();
    FString Serialized;
    if (FJsonObjectConverter::UStructToJsonObjectString(Confirmed, Serialized))
    {
        GConfig->SetString(DigimonVideoRuntime::ConfigSection, TEXT("ConfirmedSettings"), *Serialized, GGameUserSettingsIni);
        GConfig->SetInt(DigimonVideoRuntime::ConfigSection, TEXT("Schema"), 1, GGameUserSettingsIni);
        GConfig->SetBool(DigimonVideoRuntime::ConfigSection, TEXT("UnconfirmedPreview"), false, GGameUserSettingsIni);
        GConfig->Flush(false, GGameUserSettingsIni);
    }
}

void UDigimonVenomNXTVideoSettingsSubsystem::SetRecoveryPending(bool bPending)
{
    if (!GConfig) return;
    GConfig->SetBool(DigimonVideoRuntime::ConfigSection, TEXT("UnconfirmedPreview"), bPending, GGameUserSettingsIni);
    GConfig->Flush(false, GGameUserSettingsIni);
}

int32 UDigimonVenomNXTVideoSettingsSubsystem::GetConfirmationSecondsRemaining() const
{
    return Confirmation.Remaining(FPlatformTime::Seconds());
}

bool UDigimonVenomNXTVideoSettingsSubsystem::ConfirmVideoMode()
{
    if (!Confirmation.IsPending()) return false;
    if (!Confirmation.Confirm(FPlatformTime::Seconds()))
    {
        RevertVideoMode();
        return false;
    }
    const bool bHadOverrideWarning = StatusMessage.Contains(TEXT("override"));
    Confirmed = Applied;
    Pending = Applied;
    PersistConfirmed();
    StatusMessage = bHadOverrideWarning ?
        TEXT("Display confirmed and saved. Some renderer values remain controlled by a developer console or command-line override.") :
        TEXT("Display confirmed. Your video settings are saved on this device.");
    return true;
}

void UDigimonVenomNXTVideoSettingsSubsystem::RevertVideoMode()
{
    if (!Confirmation.IsPending()) return;
    // Once closing/reverting has requested rollback, Keep cannot cancel that
    // decision and the ticker retries immediately when a viewport returns.
    Confirmation.RequestRevert();
    RefreshCapabilities();
    if (!Capabilities.bRuntimeAvailable)
    {
        // Level travel can temporarily remove the viewport. Keep the expired
        // token alive so the core ticker retries once it returns. On shutdown,
        // the durable recovery marker remains for the next launch instead.
        StatusMessage = TEXT("Restoring the last confirmed display as soon as the game window is ready.");
        return;
    }
    FDigimonVideoSettings SafeSettings = Sanitize(Confirmed);
    if (SafeSettings.DisplayMode == EDigimonDisplayMode::Fullscreen &&
        !Capabilities.FullscreenResolutions.Contains(SafeSettings.Resolution))
    {
        SafeSettings.DisplayMode = EDigimonDisplayMode::Borderless;
        SafeSettings.Resolution = Capabilities.DesktopResolution;
    }
    const bool bDisplayChanged = DigimonVenomNXTVideoPolicy::NeedsConfirmation(Confirmed, SafeSettings);
    Confirmation.Cancel();
    ApplyToEngine(SafeSettings, true);
    Applied = ReadAppliedResult(SafeSettings);
    Confirmed = Applied;
    Pending = Applied;
    PersistConfirmed();
    StatusMessage = bDisplayChanged ?
        TEXT("Display preview reverted. Your previous display is no longer available, so compatible display settings were restored.") :
        TEXT("Display preview reverted. Your previous video settings have been restored.");
}

float UDigimonVenomNXTVideoSettingsSubsystem::GetEffectiveFrameRateLimit() const
{
    return FMath::Max(0.0f, DigimonVideoRuntime::ReadFloat(TEXT("t.MaxFPS"), 0.0f));
}

bool UDigimonVenomNXTVideoSettingsSubsystem::TickVideoSettings(float DeltaSeconds)
{
    TryInitialize();
    if (Confirmation.ShouldRevert(FPlatformTime::Seconds())) RevertVideoMode();
    return true;
}

void UDigimonVenomNXTVideoSettingsSubsystem::Deinitialize()
{
    // A graceful quit during preview also reverts; a crash uses the on-disk marker.
    RevertVideoMode();
    if (TickHandle.IsValid()) FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
    if (bCapturedFramePolicy && GEngine && !GIsEditor)
    {
        GEngine->bSmoothFrameRate = bOriginalSmoothFrameRate;
        GEngine->bUseFixedFrameRate = bOriginalFixedFrameRate;
        FApp::SetUseFixedTimeStep(bOriginalUseFixedTimeStep);
    }
    Super::Deinitialize();
}
