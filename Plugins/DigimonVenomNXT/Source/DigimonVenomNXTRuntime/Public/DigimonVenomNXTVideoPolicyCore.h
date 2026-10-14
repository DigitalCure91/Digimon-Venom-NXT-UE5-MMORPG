#pragma once

// Engine-independent policy shared by the runtime and executable regression tests.
#include <algorithm>
#include <cmath>

namespace DigimonVenomNXTVideoPolicy
{
    inline int Quality(int Value) { return std::max(0, std::min(4, Value)); }
    inline float FiniteClamp(float Value, float Minimum, float Maximum, float Fallback)
    {
        return std::isfinite(Value) ? std::max(Minimum, std::min(Maximum, Value)) : Fallback;
    }
    inline float FrameLimit(float Value)
    {
        if (!std::isfinite(Value) || Value <= 0.0f) return 0.0f;
        return FiniteClamp(Value, 15.0f, 1000.0f, 0.0f);
    }

    template<class Settings> void Sanitize(Settings& Value, float MinimumScale, float MaximumScale)
    {
        Value.ViewDistanceQuality = Quality(Value.ViewDistanceQuality);
        Value.AntiAliasingQuality = Quality(Value.AntiAliasingQuality);
        Value.ShadowQuality = Quality(Value.ShadowQuality);
        Value.GlobalIlluminationQuality = Quality(Value.GlobalIlluminationQuality);
        Value.ReflectionQuality = Quality(Value.ReflectionQuality);
        Value.PostProcessQuality = Quality(Value.PostProcessQuality);
        Value.TextureQuality = Quality(Value.TextureQuality);
        Value.EffectsQuality = Quality(Value.EffectsQuality);
        Value.FoliageQuality = Quality(Value.FoliageQuality);
        Value.ShadingQuality = Quality(Value.ShadingQuality);
        Value.LandscapeQuality = Quality(Value.LandscapeQuality);
        Value.ResolutionScale = FiniteClamp(Value.ResolutionScale, MinimumScale, MaximumScale, MaximumScale);
        Value.FrameRateLimit = FrameLimit(Value.FrameRateLimit);
        Value.Gamma = FiniteClamp(Value.Gamma, 1.8f, 2.6f, 2.2f);
        // UE's HDR output transform has two supported curves, not arbitrary nits.
        Value.HDRNits = Value.HDRNits < 1500 ? 1000 : 2000;
        if (Value.AntiAliasingMethod < 0 || Value.AntiAliasingMethod > 4) Value.AntiAliasingMethod = 1;
    }

    // Presets intentionally preserve display, refresh limit, VSync, HDR and gamma.
    // They never turn off the post-process material pass or custom depth.
    template<class Settings> void ApplyPreset(Settings& Value, int Preset)
    {
        const int Tier = Preset == 0 ? 1 : std::max(0, std::min(3, Preset - 1));
        Value.ViewDistanceQuality = Tier;
        Value.AntiAliasingQuality = Tier;
        Value.ShadowQuality = 0;
        Value.GlobalIlluminationQuality = Preset == 0 ? 0 : Tier;
        Value.ReflectionQuality = Preset == 0 ? 0 : Tier;
        Value.PostProcessQuality = Tier;
        Value.TextureQuality = Preset == 0 ? 3 : std::max(1, Tier);
        Value.EffectsQuality = Tier;
        Value.FoliageQuality = Preset == 0 ? 0 : Tier;
        Value.ShadingQuality = Tier;
        Value.LandscapeQuality = Tier;
        Value.AntiAliasingMethod = 1; // FXAA avoids temporal trails on moving sprites.
        Value.ResolutionScale = Preset == 1 ? 75.0f : 100.0f;
        Value.bDynamicResolution = false;
        Value.bMotionBlur = false;
        Value.bDepthOfField = false;
        Value.bBloom = Preset != 1;
        Value.bLensFlare = false;
        Value.bChromaticAberration = false;
        Value.bAmbientOcclusion = Preset >= 3;
    }

    template<class Settings> bool Equal(const Settings& A, const Settings& B)
    {
        return A.Resolution == B.Resolution && A.DisplayMode == B.DisplayMode &&
            A.ResolutionScale == B.ResolutionScale && A.FrameRateLimit == B.FrameRateLimit &&
            A.Gamma == B.Gamma && A.bVSync == B.bVSync && A.bDynamicResolution == B.bDynamicResolution &&
            A.bHDR == B.bHDR && A.HDRNits == B.HDRNits &&
            A.ViewDistanceQuality == B.ViewDistanceQuality && A.AntiAliasingQuality == B.AntiAliasingQuality &&
            A.ShadowQuality == B.ShadowQuality && A.GlobalIlluminationQuality == B.GlobalIlluminationQuality &&
            A.ReflectionQuality == B.ReflectionQuality && A.PostProcessQuality == B.PostProcessQuality &&
            A.TextureQuality == B.TextureQuality && A.EffectsQuality == B.EffectsQuality &&
            A.FoliageQuality == B.FoliageQuality && A.ShadingQuality == B.ShadingQuality &&
            A.LandscapeQuality == B.LandscapeQuality && A.AntiAliasingMethod == B.AntiAliasingMethod &&
            A.bMotionBlur == B.bMotionBlur && A.bDepthOfField == B.bDepthOfField && A.bBloom == B.bBloom &&
            A.bLensFlare == B.bLensFlare && A.bChromaticAberration == B.bChromaticAberration &&
            A.bAmbientOcclusion == B.bAmbientOcclusion;
    }
    template<class Settings> bool NeedsConfirmation(const Settings& A, const Settings& B)
    {
        return A.Resolution != B.Resolution || A.DisplayMode != B.DisplayMode ||
            A.bHDR != B.bHDR || (B.bHDR && A.HDRNits != B.HDRNits);
    }

    class Confirmation
    {
        bool Pending = false;
        bool RevertRequested = false;
        double Deadline = 0.0;
    public:
        bool Begin(double Now)
        {
            if (Pending || !std::isfinite(Now)) return false;
            Pending = true;
            RevertRequested = false;
            Deadline = Now + 15.0;
            return true;
        }
        bool IsPending() const { return Pending; }
        bool Expired(double Now) const { return Pending && (!std::isfinite(Now) || Now >= Deadline); }
        void RequestRevert() { if (Pending) RevertRequested = true; }
        bool ShouldRevert(double Now) const { return Pending && (RevertRequested || Expired(Now)); }
        int Remaining(double Now) const
        {
            if (!Pending || RevertRequested || !std::isfinite(Now)) return 0;
            return static_cast<int>(std::ceil(std::max(0.0, std::min(15.0, Deadline - Now))));
        }
        // Calling Keep at/after the deadline can never rescue an expired preview.
        bool Confirm(double Now)
        {
            if (!Pending || RevertRequested || Expired(Now)) return false;
            Pending = false;
            return true;
        }
        void Cancel() { Pending = false; RevertRequested = false; Deadline = 0.0; }
    };
}
