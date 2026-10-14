// Portable check: c++ -std=c++17 Tools/test_field_presentation.cpp -o field_test
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTFieldSizingCore.h"
#include <cassert>
#include <iostream>
#include <limits>

int main()
{
    using namespace DigimonVenomNXTFieldSizingCore;
    const auto Near = [](double A, double B) { return std::abs(A - B) < 1.e-8; };
    // A tamer occupies 32x64 authored pixels at the source's 2x display scale,
    // independent of the source map width or a transition into the private farm.
    for (const double NativeMapWidth : {1024., 1536., 2048.})
    {
        const double WorldPixel = 10000. / NativeMapWidth;
        assert(Near(Tamer(16., 32., 2., WorldPixel) * 32., 64. * WorldPixel));
        assert(Near(Partner(400., 400., WorldPixel) * 400., 58. * WorldPixel));
    }
    const double FarmPixel = 6400. / 1672.;
    assert(Near(Tamer(16., 32., 2., FarmPixel), 2. * FarmPixel));
    // Aura padding is not part of bodySize. Fit the unpadded body, preserve the
    // entire canvas around it, and refit each unusually wide/tall action pose.
    assert(Near(Partner(400., 400., FarmPixel) * 640., 58. * FarmPixel * 1.6));
    assert(Near(Partner(800., 400., 1.) * 800., 58.));
    assert(Near(Partner(200., 800., 1.) * 800., 64.));
    assert(Near(Partner(8., 8., 1.), 7.));
    assert(Near(Partner(400., 400., 1., 2.9), Partner(400., 400., 1.) * 2.));
    assert(Near(Tamer(16., 32., 2., 1., 10.8), 4.));
    // Fit-relative zoom survives map changes and viewport aspect changes.
    assert(Near(CameraWidth(10000., 5000., 16./9., 1.), 10000.));
    assert(Near(CameraWidth(10000., 11250., 16./9., 1.), 20000.));
    assert(Near(CameraWidth(10000., 11250., 16./9., 2.), 10000.));
    assert(Near(CameraWidth(10000., 5000., 16./9., 8.), 1250.));
    assert(Near(CameraWidth(10000., 5000., 1., 2.), 5000.));
    assert(Near(CameraWidth(10000., 5000., 16./9., 100.), 1250.));
    assert(Near(CameraWidth(10000., 5000., 16./9., std::numeric_limits<double>::quiet_NaN()), 10000.));
    // At fit zoom the map is centered, not centered on an off-center spawn.
    assert(Near(CameraCenter(3000., 0., 10000., 10000.), 0.));
    assert(Near(CameraCenter(-4000., 0., 10000., 12000.), 0.));
    assert(Near(CameraCenter(9000., 0., 10000., 2500.), 3750.));
    assert(Near(CameraCenter(-9000., 0., 10000., 2500.), -3750.));
    assert(Near(CameraCenter(0., 500., 1000., 250.), 125.));
    std::cout << "Field presentation: source body fit, map/farm scaling, zoom and bounded camera checks passed.\n";
}
