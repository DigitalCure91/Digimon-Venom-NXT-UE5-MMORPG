#pragma once
#include <algorithm>
#include <cmath>

/** Source-pixel fitting shared by the native field presenters. */
namespace DigimonVenomNXTFieldSizingCore
{
    inline double Fit(double Width, double Height, double BoxWidth, double BoxHeight)
    {
        if (!std::isfinite(Width) || !std::isfinite(Height) || Width <= 0. || Height <= 0.) return 1.;
        const double Scale = std::min(BoxWidth / Width, BoxHeight / Height);
        return Scale >= 1. ? std::max(1., std::floor(Scale)) : Scale;
    }
    inline double Partner(double Width, double Height, double WorldPerPixel, double UserScale = 1.45)
    {
        const double Multiplier = std::isfinite(UserScale) ? std::max(.01, std::abs(UserScale) / 1.45) : 1.;
        return Fit(Width, Height, 58., 64.) * WorldPerPixel * Multiplier;
    }
    inline double Tamer(double Width, double Height, double DisplayScale, double WorldPerPixel, double UserScale = 5.4)
    {
        const double Display = std::isfinite(DisplayScale) ? std::max(.01, DisplayScale) : 2.;
        const double NativeScale = Fit(Width, Height, std::min(64., Width * Display), std::min(80., Height * Display));
        const double Multiplier = std::isfinite(UserScale) ? std::max(.01, std::abs(UserScale) / 5.4) : 1.;
        return NativeScale * WorldPerPixel * Multiplier;
    }
    inline double CameraWidth(double MapWidth, double MapHeight, double Aspect, double Zoom)
    {
        if (!std::isfinite(Aspect) || Aspect <= 0.) Aspect = 16. / 9.;
        if (!std::isfinite(Zoom)) Zoom = 1.;
        return std::max(MapWidth, MapHeight * Aspect) / std::clamp(Zoom, 1., 8.);
    }
    inline double CameraCenter(double Target, double MapCenter, double MapSpan, double ViewSpan)
    {
        const double Travel = std::max(0., (MapSpan - ViewSpan) * .5);
        return std::clamp(Target, MapCenter - Travel, MapCenter + Travel);
    }
}
