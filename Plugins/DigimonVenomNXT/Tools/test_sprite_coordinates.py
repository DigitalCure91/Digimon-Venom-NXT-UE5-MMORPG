#!/usr/bin/env python3
"""Compile and exercise the real cooked-sprite coordinate implementation.

This is a portable API contract/numerical regression test, not an Unreal build.
The PaperSprite stub deliberately has no editor-only coordinate/source methods.
Known pixel positions generate fixture vertices; all conversions under test come
from the actual production header, not a reimplementation in this harness.
"""
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest


PLUGIN_ROOT = Path(__file__).resolve().parents[1]
PUBLIC = PLUGIN_ROOT / "Source/DigimonVenomNXTRuntime/Public"
CORE_STUB = r"""
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
using int32 = std::int32_t;
using uint32 = std::uint32_t;
constexpr int32 INDEX_NONE=-1;
#define FORCEINLINE inline
#define SMALL_NUMBER (1.e-8)
#define KINDA_SMALL_NUMBER (1.e-4)
#define UE_SMALL_NUMBER (1.e-8)
#define UE_DOUBLE_SMALL_NUMBER (1.e-8)
#define UE_KINDA_SMALL_NUMBER (1.e-4)
struct FVector2D {
    double X = 0, Y = 0;
    FVector2D() = default;
    FVector2D(double InX, double InY) : X(InX), Y(InY) {}
    FVector2D operator+(const FVector2D& V) const { return {X+V.X,Y+V.Y}; }
    FVector2D operator-(const FVector2D& V) const { return {X-V.X,Y-V.Y}; }
    FVector2D operator*(double S) const { return {X*S,Y*S}; }
    FVector2D operator/(double S) const { return {X/S,Y/S}; }
    double SizeSquared() const { return X*X+Y*Y; }
    bool Equals(const FVector2D& V, double T=1.e-4) const {
        return std::abs(X-V.X)<=T && std::abs(Y-V.Y)<=T;
    }
    static const FVector2D ZeroVector;
};
inline const FVector2D FVector2D::ZeroVector{0,0};
inline FVector2D operator*(double S,const FVector2D& V) { return V*S; }
struct FVector {
    double X=0,Y=0,Z=0;
    FVector()=default;
    FVector(double InX,double InY,double InZ):X(InX),Y(InY),Z(InZ) {}
    FVector operator+(const FVector& V) const { return {X+V.X,Y+V.Y,Z+V.Z}; }
    FVector operator-(const FVector& V) const { return {X-V.X,Y-V.Y,Z-V.Z}; }
    FVector operator*(double S) const { return {X*S,Y*S,Z*S}; }
    FVector operator/(double S) const { return {X/S,Y/S,Z/S}; }
    double SizeSquared() const { return X*X+Y*Y+Z*Z; }
    double Size() const { return std::sqrt(SizeSquared()); }
    bool ContainsNaN() const { return !std::isfinite(X)||!std::isfinite(Y)||!std::isfinite(Z); }
    static double DotProduct(const FVector& A,const FVector& B) {
        return A.X*B.X+A.Y*B.Y+A.Z*B.Z;
    }
    static FVector CrossProduct(const FVector& A,const FVector& B) {
        return {A.Y*B.Z-A.Z*B.Y,A.Z*B.X-A.X*B.Z,A.X*B.Y-A.Y*B.X};
    }
    static const FVector ZeroVector;
};
inline const FVector FVector::ZeroVector{0,0,0};
inline FVector operator*(double S,const FVector& V) { return V*S; }
struct FVector4f {
    float X=0,Y=0,Z=0,W=0;
    FVector4f()=default;
    FVector4f(float A,float B,float C,float D):X(A),Y(B),Z(C),W(D) {}
};
struct FMath {
    template<class T> static T Abs(T V) { return std::abs(V); }
    template<class T> static T Min(T A,T B) { return std::min(A,B); }
    template<class T> static T Max(T A,T B) { return std::max(A,B); }
    template<class T> static T Clamp(T V,T A,T B) { return std::clamp(V,A,B); }
    static bool IsFinite(double V) { return std::isfinite(V); }
    static bool IsNearlyZero(double V,double T=1.e-8) { return std::abs(V)<=T; }
    static bool IsNearlyEqual(double A,double B,double T=1.e-8) { return std::abs(A-B)<=T; }
    static double Sqrt(double V) { return std::sqrt(V); }
    static double RoundToDouble(double V) { return std::round(V); }
    static int32 RoundToInt(double V) { return int32(std::lround(V)); }
};
template<class T> struct TArray:std::vector<T> {
    using std::vector<T>::vector;
    int32 Num() const { return int32(this->size()); }
    bool IsEmpty() const { return this->empty(); }
    void Add(const T& V) { this->push_back(V); }
    void Reset() { this->clear(); }
};
"""

ATLAS_STUB = r"""
#pragma once
#include "CoreMinimal.h"
// SizeX/SizeY intentionally represent a streamed resident LOD. Production
// mapping must not depend on them to recover source image pixels.
struct UTexture { int32 SizeX=256, SizeY=256; };
struct FSlateAtlasData {
    UTexture* AtlasTexture=nullptr;
    FVector2D StartUV=FVector2D::ZeroVector;
    FVector2D SizeUV=FVector2D::ZeroVector;
};
"""

PAPER_STUB = r"""
#pragma once
#include "CoreMinimal.h"
#include "Slate/SlateTextureAtlasInterface.h"
#if WITH_EDITOR || WITH_EDITORONLY_DATA || !UE_BUILD_SHIPPING
#error This fixture must compile with cooked Shipping preprocessor definitions
#endif
struct UPaperSprite {
    TArray<FVector4f> BakedRenderData;
    FSlateAtlasData Atlas;
    float PixelsPerUnit=1;
    FSlateAtlasData GetSlateAtlasData() const { return Atlas; }
    float GetPixelsPerUnrealUnit() const { return PixelsPerUnit; }
};
"""

FIXTURE = r"""
#include "DigimonVenomNXTSpriteCoordinates.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
using namespace DigimonVenomNXTSpriteCoordinates;

void Check(bool Result,const std::string& Label) {
    if (!Result) throw std::runtime_error(Label);
}
void Near(double Actual,double Expected,const std::string& Label,double T=0.025) {
    Check(std::isfinite(Actual)&&std::abs(Actual-Expected)<=T,
          Label+": got "+std::to_string(Actual)+", expected "+std::to_string(Expected));
}
void Near2(const FVector2D& A,const FVector2D& E,const std::string& Label,double T=0.025) {
    Near(A.X,E.X,Label+" X",T); Near(A.Y,E.Y,Label+" Y",T);
}
void Near3(const FVector& A,const FVector& E,const std::string& Label,double T=0.025) {
    Near(A.X,E.X,Label+" X",T); Near(A.Y,E.Y,Label+" Y",T); Near(A.Z,E.Z,Label+" Z",T);
}
// Independent authored-sprite oracle. Source frame coordinates start at its
// upper-left, whereas Paper2D's local Z axis points upwards.
FVector ExpectedLocal(FVector2D P,FVector2D Pivot,double PPU) {
    return {(P.X-Pivot.X)/PPU,0,(Pivot.Y-P.Y)/PPU};
}
UPaperSprite Sprite(UTexture& Texture,FVector2D Size,FVector2D Pivot,double PPU,
                    FVector2D TextureSize,FVector2D FrameOrigin,bool Tight=false) {
    UPaperSprite S;
    S.PixelsPerUnit=float(PPU);
    S.Atlas.AtlasTexture=&Texture;
    S.Atlas.StartUV={FrameOrigin.X/TextureSize.X,FrameOrigin.Y/TextureSize.Y};
    S.Atlas.SizeUV={Size.X/TextureSize.X,Size.Y/TextureSize.Y};
    const FVector2D Quad[]={{0,0},{Size.X,0},{Size.X,Size.Y},
                           {0,0},{Size.X,Size.Y},{0,Size.Y}};
    // A trimmed interior triangle deliberately touches none of the frame's
    // edges. Vertex extrema must not be mistaken for full image dimensions.
    const FVector2D Interior[]={{Size.X*.17,Size.Y*.13},
                               {Size.X*.81,Size.Y*.27},{Size.X*.36,Size.Y*.89}};
    for (int I=0;I<(Tight?3:6);++I) {
        const auto P=Tight?Interior[I]:Quad[I];
        const auto L=ExpectedLocal(P,Pivot,PPU);
        S.BakedRenderData.Add(FVector4f(float(L.X),float(L.Z),
            float((P.X+FrameOrigin.X)/TextureSize.X),
            float((P.Y+FrameOrigin.Y)/TextureSize.Y)));
    }
    return S;
}
void MappingCase(FVector2D Size,FVector2D Pivot,double PPU,FVector2D TextureSize,
                 FVector2D FrameOrigin,bool Tight,const std::string& Label) {
    UTexture Texture;
    auto S=Sprite(Texture,Size,Pivot,PPU,TextureSize,FrameOrigin,Tight);
    FMapping M;
    Check(TryGetMapping(&S,M),Label+" mapping");
    Near2(M.ImageSize,Size,Label+" dimensions");
    Near2(GetImageSize(&S),Size,Label+" public dimensions");
    const FVector2D Points[]={{0,0},Size,Pivot,{Size.X*.5,Size.Y*.5},
                              {Size.X*.143,Size.Y*.879},{-11,Size.Y+19}};
    for (const auto& P:Points) {
        const auto L=ExpectedLocal(P,Pivot,PPU);
        Near3(M.ImageToLocal(P),L,Label+" mapping local");
        Near2(M.LocalToImage(L),P,Label+" mapping image");
        Near3(ImageToLocal(&S,P),L,Label+" public local");
        Near2(LocalToImage(&S,L),P,Label+" public image");
        Near2(M.LocalToImage(M.ImageToLocal(P)),P,Label+" round trip");
    }
    // Changing the resident texture dimensions cannot change coordinates.
    Texture.SizeX=32; Texture.SizeY=16;
    FMapping LowLOD;
    Check(TryGetMapping(&S,LowLOD),Label+" LOD mapping");
    Near2(LowLOD.ImageSize,Size,Label+" LOD dimensions");
    Near3(LowLOD.ImageToLocal({11,29}),M.ImageToLocal({11,29}),Label+" LOD local");
    const bool Full=FrameOrigin.X==0 && FrameOrigin.Y==0 &&
                    Size.X==TextureSize.X && Size.Y==TextureSize.Y;
    Check(IsFullTexture(&S)==Full,Label+" full texture detection");
}
int main() {
    try {
        int Cases=0;
        for (double PPU:{1.,2.,10.}) {
            for (FVector2D Pivot:{FVector2D(836,470.5),FVector2D(113.25,799.75),FVector2D(0,0)}) {
                MappingCase({1672,941},Pivot,PPU,{1672,941},{0,0},false,"farm quad"); ++Cases;
                MappingCase({1672,941},Pivot,PPU,{1672,941},{0,0},true,"farm tight"); ++Cases;
                const FVector2D GuardianPivot(Pivot.X*.17,Pivot.Y*.31);
                MappingCase({400,400},GuardianPivot,PPU,{1600,800},{400,0},false,"guardian frame 2"); ++Cases;
                MappingCase({400,400},GuardianPivot,PPU,{1600,800},{800,400},true,"guardian tight atlas"); ++Cases;
            }
        }
        FMapping M;
        Check(!TryGetMapping(nullptr,M),"null sprite rejection");
        UTexture Texture;
        auto S=Sprite(Texture,{400,400},{200,200},2,{800,800},{400,400});
        auto Invalid=S; Invalid.BakedRenderData.Reset();
        Check(!TryGetMapping(&Invalid,M),"missing baked data rejection");
        Invalid=S; Invalid.Atlas.AtlasTexture=nullptr;
        Check(!TryGetMapping(&Invalid,M),"missing texture rejection");
        Invalid=S; Invalid.Atlas.SizeUV={0,0};
        Check(!TryGetMapping(&Invalid,M),"zero atlas size rejection");
        for (float PPU:{0.f,-1.f,std::numeric_limits<float>::infinity(),
                        std::numeric_limits<float>::quiet_NaN()}) {
            Invalid=S; Invalid.PixelsPerUnit=PPU;
            Check(!TryGetMapping(&Invalid,M),"invalid PPU rejection");
        }
        Invalid=S;
        for (auto& V:Invalid.BakedRenderData) { V.Z=.5f; V.W=.5f; }
        Check(!TryGetMapping(&Invalid,M),"degenerate UV rejection");
        Invalid=S;
        for (auto& V:Invalid.BakedRenderData) { V.X=0; V.Y=0; }
        Check(!TryGetMapping(&Invalid,M),"degenerate local geometry rejection");
        Invalid=S;
        for (auto& V:Invalid.BakedRenderData) V.X=std::numeric_limits<float>::quiet_NaN();
        Check(!TryGetMapping(&Invalid,M),"nonfinite baked data rejection");
        Invalid=S; Invalid.Atlas.StartUV.X=std::numeric_limits<double>::quiet_NaN();
        Check(!TryGetMapping(&Invalid,M),"nonfinite atlas rejection");
        std::cout << Cases << " geometry cases, six sample points each, LOD checks, and malformed-data checks passed\n";
        return 0;
    } catch (const std::exception& E) {
        std::cerr << E.what() << '\n';
        return 1;
    }
}
"""


class SpriteCoordinateContractTests(unittest.TestCase):
    def compile_fixture(self, fixture, run=False):
        with tempfile.TemporaryDirectory(prefix="digimon-sprite-coordinates-") as directory:
            root = Path(directory)
            (root / "Slate").mkdir()
            (root / "CoreMinimal.h").write_text(CORE_STUB, encoding="utf-8")
            (root / "Slate/SlateTextureAtlasInterface.h").write_text(ATLAS_STUB, encoding="utf-8")
            (root / "PaperSprite.h").write_text(PAPER_STUB, encoding="utf-8")
            source = root / "contract.cpp"
            source.write_text(fixture, encoding="utf-8")
            binary = root / "contract"
            command = shlex.split(os.environ.get("CXX", "g++")) + [
                "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                "-DWITH_EDITOR=0", "-DWITH_EDITORONLY_DATA=0", "-DUE_BUILD_SHIPPING=1",
                "-I", str(root), "-I", str(PUBLIC), str(source), "-o", str(binary),
            ]
            result = subprocess.run(command, capture_output=True, text=True,
                                    timeout=30, check=False)
            if run and result.returncode == 0:
                result = subprocess.run([str(binary)], capture_output=True,
                                        text=True, timeout=10, check=False)
            return result

    def test_production_header_compiles_without_editor_apis_and_preserves_coordinates(self):
        result = self.compile_fixture(FIXTURE, run=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_original_editor_only_api_regressions_are_rejected(self):
        calls = (
            "S.GetSourceSize()", "S.GetSourceUV()", "S.GetPivotPosition()",
            "S.ConvertTextureSpaceToPivotSpace(FVector2D())",
            "S.ConvertPivotSpaceToTextureSpace(FVector2D())",
        )
        for call in calls:
            with self.subTest(call=call):
                fixture = '#include "PaperSprite.h"\nint main() { UPaperSprite S; (void)' + call + '; }\n'
                result = self.compile_fixture(fixture)
                self.assertNotEqual(result.returncode, 0,
                                    "Editor-only call unexpectedly available: " + call)
                self.assertIn("has no member", result.stderr)


if __name__ == "__main__":
    unittest.main()
