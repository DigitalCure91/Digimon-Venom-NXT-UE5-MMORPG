// Compile: c++ -std=c++17 -Wall -Wextra -Werror -pedantic Tools/test_video_policy_core.cpp -o /tmp/digimon-video-policy
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTVideoPolicyCore.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>

struct Settings
{
    std::pair<int, int> Resolution{1920, 1080};
    int DisplayMode = 1;
    float ResolutionScale = 100, FrameRateLimit = 144, Gamma = 2.4f;
    bool bVSync = true, bDynamicResolution = true, bHDR = true;
    int HDRNits = 1000;
    int ViewDistanceQuality = 3, AntiAliasingQuality = 3, ShadowQuality = 3;
    int GlobalIlluminationQuality = 3, ReflectionQuality = 3, PostProcessQuality = 3;
    int TextureQuality = 3, EffectsQuality = 3, FoliageQuality = 3, ShadingQuality = 3, LandscapeQuality = 3;
    int AntiAliasingMethod = 4;
    bool bMotionBlur = true, bDepthOfField = true, bBloom = true, bLensFlare = true;
    bool bChromaticAberration = true, bAmbientOcclusion = true;
};

int main()
{
    using namespace DigimonVenomNXTVideoPolicy;
    int Checks = 0;
    const auto Check = [&Checks](bool Result) { assert(Result); ++Checks; };
    Check(FrameLimit(0) == 0);
    Check(FrameLimit(-60) == 0);
    Check(FrameLimit(144) == 144);
    Check(FrameLimit(360) == 360);
    Check(FrameLimit(5) == 15);
    Check(FrameLimit(9999) == 1000);
    Check(FrameLimit(std::numeric_limits<float>::quiet_NaN()) == 0);
    Check(FrameLimit(std::numeric_limits<float>::infinity()) == 0);
    Check(Quality(-1) == 0 && Quality(7) == 4);
    Settings Original;
    for (int Preset = 0; Preset <= 4; ++Preset)
    {
        Settings Value = Original;
        ApplyPreset(Value, Preset);
        Check(Value.Resolution == Original.Resolution && Value.DisplayMode == Original.DisplayMode);
        Check(Value.FrameRateLimit == 144 && Value.bVSync && Value.bHDR && Value.HDRNits == 1000 && Value.Gamma == 2.4f);
        Check(Value.ShadowQuality == 0 && !Value.bMotionBlur && !Value.bDepthOfField);
        Check(!Value.bDynamicResolution && Value.AntiAliasingMethod == 1 && !Value.bChromaticAberration && !Value.bLensFlare);
        Check(Value.ResolutionScale == (Preset == 1 ? 75.0f : 100.0f));
        Check(Value.TextureQuality >= 1 && Value.TextureQuality <= 3);
        if (Preset == 0) Check(Value.TextureQuality == 3 && Value.GlobalIlluminationQuality == 0 && Value.FoliageQuality == 0);
    }
    Settings Invalid;
    Invalid.TextureQuality = -200;
    Invalid.LandscapeQuality = 50;
    Invalid.ShadowQuality = -1;
    Invalid.ResolutionScale = std::numeric_limits<float>::quiet_NaN();
    Invalid.Gamma = -7;
    Invalid.FrameRateLimit = std::numeric_limits<float>::infinity();
    Invalid.HDRNits = 100000;
    Invalid.AntiAliasingMethod = 255;
    Sanitize(Invalid, 50, 100);
    Check(Invalid.TextureQuality == 0 && Invalid.LandscapeQuality == 4 && Invalid.ShadowQuality == 0);
    Check(Invalid.ResolutionScale == 100 && Invalid.Gamma == 1.8f && Invalid.FrameRateLimit == 0);
    Check(Invalid.HDRNits == 2000 && Invalid.AntiAliasingMethod == 1);
    Invalid.HDRNits = 400; Sanitize(Invalid, 50, 100); Check(Invalid.HDRNits == 1000);
    Invalid.HDRNits = 1499; Sanitize(Invalid, 50, 100); Check(Invalid.HDRNits == 1000);
    Invalid.HDRNits = 1500; Sanitize(Invalid, 50, 100); Check(Invalid.HDRNits == 2000);
    Invalid.ResolutionScale = 10;
    Invalid.Gamma = std::numeric_limits<float>::quiet_NaN();
    Sanitize(Invalid, 66, 100);
    Check(Invalid.ResolutionScale == 66 && Invalid.Gamma == 2.2f);
    Check(Equal(Original, Original));
    Settings Changed = Original;
    Changed.LandscapeQuality = 0;
    Check(!Equal(Original, Changed) && !NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.FrameRateLimit = 0;
    Check(!Equal(Original, Changed) && !NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.bVSync = false;
    Check(!Equal(Original, Changed) && !NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.bBloom = false;
    Check(!Equal(Original, Changed) && !NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.Gamma = 2.2f;
    Check(!Equal(Original, Changed) && !NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.Resolution = {1280, 720};
    Check(NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.DisplayMode = 2;
    Check(NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.bHDR = false;
    Check(NeedsConfirmation(Original, Changed));
    Changed = Original; Changed.HDRNits = 600;
    Check(NeedsConfirmation(Original, Changed));
    Original.bHDR = false; Changed.bHDR = false;
    Check(!NeedsConfirmation(Original, Changed));

    Confirmation Preview;
    Check(!Preview.IsPending() && Preview.Remaining(100) == 0 && !Preview.Confirm(100));
    Check(!Preview.Begin(std::numeric_limits<double>::quiet_NaN()));
    Check(Preview.Begin(100) && Preview.IsPending());
    Check(!Preview.Begin(102)); // Clicking Apply twice cannot prolong a risky preview.
    Check(Preview.Remaining(100) == 15 && Preview.Remaining(100.1) == 15);
    Check(Preview.Remaining(114.9) == 1 && !Preview.Expired(114.9));
    Check(Preview.Expired(115) && Preview.Remaining(115) == 0);
    Check(!Preview.Confirm(115) && Preview.IsPending()); // Caller must restore the saved snapshot.
    Preview.Cancel();
    Check(!Preview.IsPending());
    Check(Preview.Begin(200));
    Check(Preview.Confirm(214.99) && !Preview.IsPending());
    Check(!Preview.Confirm(214.99)); // No duplicate Keep/save.
    Check(Preview.Begin(300));
    Check(Preview.Expired(1000)); // Paused/hidden UI and a long process stall still time out.
    Preview.Cancel();
    Check(Preview.Begin(1000));
    Check(Preview.Expired(std::numeric_limits<double>::infinity()));
    Preview.Cancel();
    Check(Preview.Begin(1100));
    Preview.Cancel(); // Close/destroy path.
    Check(!Preview.Expired(99999) && Preview.Remaining(99999) == 0);
    Check(Preview.Begin(1200));
    Preview.RequestRevert(); // Close during travel, before the 15-second deadline.
    Check(!Preview.Expired(1201) && Preview.ShouldRevert(1201));
    Check(Preview.IsPending() && Preview.Remaining(1201) == 0);
    Check(!Preview.Confirm(1201)); // Keep cannot undo the requested rollback.
    Check(Preview.ShouldRevert(1202)); // Retry immediately once the viewport returns.
    Preview.Cancel();
    Check(!Preview.ShouldRevert(1202));
    Check(Preview.Begin(1300) && !Preview.ShouldRevert(1301) && Preview.Confirm(1301));
    std::cout << "PASS: " << Checks << " video policy, preset, finite-input and confirmation lifecycle checks\n";
}
