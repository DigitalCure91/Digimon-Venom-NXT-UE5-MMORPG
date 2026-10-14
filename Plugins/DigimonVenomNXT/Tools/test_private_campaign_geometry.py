#!/usr/bin/env python3
"""Compile actual private campaign geometry without any public map-zone actors.

This portable regression test extracts the current production helper and methods,
uses the real cooked-sprite mapping and exact collision core, and substitutes only
Unreal container/asset APIs. It is not an Unreal build or a multiplayer play test.
"""
from pathlib import Path
import importlib.util
import os
import shlex
import subprocess
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parent
PUBLIC = TOOLS.parent / 'Source/DigimonVenomNXTRuntime/Public'
SOURCE = TOOLS.parent / 'Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTWorld.cpp'


def fixture_module():
    spec = importlib.util.spec_from_file_location('digimon_sprite_stubs', TOOLS / 'test_sprite_coordinates.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def core_stub(module):
    core = module.CORE_STUB.replace('#include <vector>', '#include <vector>\n#include <limits>\n#include <map>\n#include <set>\n#include <string>\n#include <cstdio>\n#include <stdexcept>')
    core = core.replace('using int32 =', 'using uint8 = std::uint8_t;\nusing TCHAR = char;\nusing int32 =')
    core = core.replace('    static double DotProduct(', '''    static double DistSquared2D(const FVector& A, const FVector& B) { return (A.X-B.X)*(A.X-B.X)+(A.Y-B.Y)*(A.Y-B.Y); }
    static double Dist2D(const FVector& A, const FVector& B) { return std::sqrt(DistSquared2D(A,B)); }
    static double Distance(const FVector& A, const FVector& B) { return (A-B).Size(); }
    std::string ToString() const { return std::to_string(X)+","+std::to_string(Y)+","+std::to_string(Z); }
    static double DotProduct(''')
    core = core.replace('    template<class T> static T Max(T A,T B) { return std::max(A,B); }', '    template<class A,class B> static auto Max(A X,B Y) { using T=decltype(X+Y); return std::max(static_cast<T>(X),static_cast<T>(Y)); }')
    core = core.replace('    template<class T> static T Abs(', '    template<class T> static T Square(T V) { return V*V; }\n    template<class T> static T Abs(')
    core = core.replace('    void Reset() { this->clear(); }', '''    void Reset() { this->clear(); }
    void Empty() { this->clear(); }
    const T* GetData() const { return this->data(); }
    T* GetData() { return this->data(); }''')
    return core + r'''
#define TEXT(x) x
template<class... T> void IgnoreLog(const char*,T...) {}
#define UE_LOG(Category,Verbosity,...) IgnoreLog(__VA_ARGS__)
struct FString : std::string {
    using std::string::string;
    using std::string::operator=;
    void Reset() { clear(); }
    const char* operator*() const { return c_str(); }
    template<class... T> static FString Printf(const char* Format, T... Args) {
        int Size = std::snprintf(nullptr, 0, Format, Args...);
        if (Size < 0) throw std::runtime_error("printf failed");
        std::vector<char> Buffer(static_cast<std::size_t>(Size)+1);
        std::snprintf(Buffer.data(), Buffer.size(), Format, Args...);
        return FString(Buffer.data());
    }
};
inline const char* operator*(const std::string& S) { return S.c_str(); }
template<class K, class V> struct TMap : std::map<K,V> {
    V* Find(const K& Key) { auto It=this->find(Key); return It==this->end()?nullptr:&It->second; }
    const V* Find(const K& Key) const { auto It=this->find(Key); return It==this->end()?nullptr:&It->second; }
    V& Add(const K& Key) { return (*this)[Key]; }
    void Empty() { this->clear(); }
};
template<class T> struct TSet : std::set<T> {
    bool Contains(const T& Value) const { return this->count(Value)>0; }
    void Add(const T& Value) { this->insert(Value); }
};
struct FIntPoint {
    int32 X=0,Y=0;
    FIntPoint()=default;
    FIntPoint(int32 A,int32 B):X(A),Y(B) {}
    FIntPoint operator+(const FIntPoint& B) const { return {X+B.X,Y+B.Y}; }
    bool operator<(const FIntPoint& B) const { return X<B.X || (X==B.X && Y<B.Y); }
    static const FIntPoint ZeroValue;
};
inline const FIntPoint FIntPoint::ZeroValue{0,0};
template<class T> struct TNumericLimits { static T Max() { return std::numeric_limits<T>::max(); } };
struct FRotator {
    double Pitch,Yaw,Roll;
    FRotator(double P,double Y,double R):Pitch(P),Yaw(Y),Roll(R) {}
};
// UE's +90 degree roll maps local Z to world +Y and local Y to -Z.
// Only the authored ground plane's fixed rotation is needed by this fixture.
struct FTransform {
    FVector Translation{0,0,0}, Scale{1,1,1};
    FTransform()=default;
    FTransform(FRotator R,FVector T,FVector S):Translation(T),Scale(S) {
        if (R.Pitch!=0 || R.Yaw!=0 || R.Roll!=90) throw std::runtime_error("unexpected ground rotation");
    }
    FVector TransformVector(const FVector& V) const { return {V.X*Scale.X,V.Z*Scale.Z,-V.Y*Scale.Y}; }
    FVector TransformPosition(const FVector& V) const { return TransformVector(V)+Translation; }
    FVector InverseTransformPosition(const FVector& V) const {
        auto D=V-Translation; return {D.X/Scale.X,-D.Z/Scale.Y,D.Y/Scale.Z};
    }
    void SetTranslation(const FVector& V) { Translation=V; }
    void AddToTranslation(const FVector& V) { Translation=Translation+V; }
    FVector GetScale3D() const { return Scale; }
    bool ContainsNaN() const { return Translation.ContainsNaN() || Scale.ContainsNaN(); }
};
'''


API_STUBS = r'''
#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "DigimonVenomNXTCollisionCore.h"
#include "DigimonVenomNXTSpriteCoordinates.h"
#include <iostream>
struct FDigimonMapRow {
    int32 SourceWidth=1000,SourceHeight=600,WalkGridWidth=100,WalkGridHeight=60;
    TArray<uint8> WalkGridBits;
    FVector2D SafeSpawnUV{.15,.5};
};
struct UDigimonVenomNXTSettings { double MapWorldWidth=1000,TamerCollisionProbeRadius=4; };
struct UDigimonVenomNXTMapAssetRevision {
    inline static bool Current=true;
    static bool IsInstalledCurrent() { return Current; }
};
UDigimonVenomNXTSettings Settings;
template<class T> const T* GetDefault() { return &Settings; }
struct UDigimonVenomNXTDataSubsystem {
    FDigimonMapRow Row;
    bool Present=true;
    const FDigimonMapRow* FindMap(int32 Id) const { return Present && Id==113 ? &Row : nullptr; }
};
struct UGameInstance {
    UDigimonVenomNXTDataSubsystem Data;
    template<class T> const T* GetSubsystem() const { return &Data; }
};
struct UWorld {
    UGameInstance GI;
    const UGameInstance* GetGameInstance() const { return &GI; }
};
UWorld* RenderWorld=nullptr;
UPaperSprite* LoadedSprite=nullptr;
int AssetLoads=0;
constexpr int LOAD_NoWarn=1, LOAD_Quiet=2;
template<class T> T* LoadObject(void*, const char*, void* = nullptr, int = 0) { ++AssetLoads; return LoadedSprite; }
struct ADigimonVenomNXTMapZone {
    FVector Location;
    FVector GetActorLocation() const { return Location; }
};
ADigimonVenomNXTMapZone PublicZone;
bool PublicZonePresent=false;
struct UPaperSpriteComponent {
    UPaperSprite* Sprite=nullptr;
    FTransform Relative;
    bool Hidden=true,Visible=false,CustomDepth=false;
    void SetSprite(UPaperSprite* S) { Sprite=S; }
    void SetRelativeTransform(const FTransform& T) { Relative=T; }
    void SetHiddenInGame(bool H,bool) { Hidden=H; }
    void SetVisibility(bool V,bool=false) { Visible=V; }
};
struct ADigimonVenomNXTLocalMapRenderer {
    UPaperSpriteComponent Component, ForegroundComponent;
    UPaperSpriteComponent* GroundSprite=&Component;
    UPaperSpriteComponent* ForegroundSprite=&ForegroundComponent;
    FVector Location;
    bool Hidden=true;
    void SetActorLocation(const FVector& L) { Location=L; }
    void SetActorHiddenInGame(bool H) { Hidden=H; }
    const UGameInstance* GetGameInstance() const { return RenderWorld ? RenderWorld->GetGameInstance() : nullptr; }
    bool ShowMap(int32,const FVector&,UPaperSprite* = nullptr);
};
namespace DigimonMapRuntime {
    void ConfigureCustomDepth(UPaperSpriteComponent* Component) { Component->CustomDepth=true; }
}
struct UDigimonVenomNXTWorldSubsystem {
    UWorld* World=nullptr;
    mutable int ZoneQueries=0;
    mutable TMap<int32,TArray<FVector>> PrivateReachablePoints;
    mutable double CachedPlacementRadius=-1,CachedPlacementWidth=-1;
    UWorld* GetWorld() const { return World; }
    // There are deliberately no public actor transforms, sprites or collision APIs.
    // Every public map zone has been unloaded, as can occur for a remote client.
    ADigimonVenomNXTMapZone* FindMapZone(int32) const { ++ZoneQueries; return PublicZonePresent ? &PublicZone : nullptr; }
    bool IsPrivateMapLocationWalkable(int32,const FVector&,const FVector&) const;
    bool IsPrivateMapSegmentWalkable(int32,const FVector&,const FVector&,const FVector&) const;
    bool ValidatePrivateMapContent(int32,FString&) const;
    bool GetPrivateMapSpawn(int32,FVector&) const;
    const TArray<FVector>& GetPrivateReachablePoints(int32) const;
    bool ResolvePrivateMapPoint(int32,const FVector2D&,FVector&,const TArray<FVector>& = {}) const;
};
'''


CASES = r'''
void Check(bool Condition, const std::string& Message) { if (!Condition) throw std::runtime_error(Message); }
void Near(double A,double B,const std::string& Message,double T=.03) {
    Check(std::isfinite(A)&&std::abs(A-B)<=T,Message+": got "+std::to_string(A)+" expected "+std::to_string(B));
}
void Near3(const FVector& A,const FVector& B,const std::string& Message) {
    Near(A.X,B.X,Message+" X");Near(A.Y,B.Y,Message+" Y");Near(A.Z,B.Z,Message+" Z");
}
UPaperSprite Sprite(UTexture& Texture, FVector2D Pivot, double PPU) {
    UPaperSprite S;
    S.PixelsPerUnit=static_cast<float>(PPU);
    S.Atlas.AtlasTexture=&Texture;
    S.Atlas.StartUV={0,0};S.Atlas.SizeUV={1,1};
    for (FVector2D P : {FVector2D(0,0),FVector2D(1000,0),FVector2D(1000,600),
                        FVector2D(0,0),FVector2D(1000,600),FVector2D(0,600)})
        S.BakedRenderData.Add(FVector4f(static_cast<float>((P.X-Pivot.X)/PPU),
            static_cast<float>((Pivot.Y-P.Y)/PPU),static_cast<float>(P.X/1000),static_cast<float>(P.Y/600)));
    return S;
}
void SetBlocked(FDigimonMapRow& Row,int X,int Y) {
    const int Index=Y*Row.WalkGridWidth+X;
    Row.WalkGridBits[Index/8]&=static_cast<uint8>(~(1u<<(7-Index%8)));
}
FVector ExpectedPoint(FVector2D UV,double Z=100) {
    return {(.5-UV.X)*Settings.MapWorldWidth,(.5-UV.Y)*Settings.MapWorldWidth*.6,Z};
}
void Reset(UDigimonVenomNXTWorldSubsystem& System,UWorld& World,UPaperSprite& S) {
    System=UDigimonVenomNXTWorldSubsystem();System.World=&World;
    RenderWorld=&World;
    Settings=UDigimonVenomNXTSettings();World=UWorld();
    UDigimonVenomNXTMapAssetRevision::Current=true;
    World.GI.Data.Row.WalkGridBits.assign(750,255);LoadedSprite=&S;PublicZonePresent=false;
}
void Reject(UDigimonVenomNXTWorldSubsystem& System,const char* Code) {
    FString Error;
    Check(!System.ValidatePrivateMapContent(113,Error),std::string(Code)+" accepted");
    Check(Error.find(Code)!=std::string::npos,std::string(Code)+" lost diagnostic: "+Error);
    Check(System.ZoneQueries==0,"invalid content consulted public map actors");
}
int main() {
    try {
        UTexture Texture;UWorld World;UDigimonVenomNXTWorldSubsystem System;FString Error;
        int TransformCases=0;
        for (double PPU:{.5,1.,2.,10.}) for (FVector2D Pivot:{FVector2D(500,300),FVector2D(113.25,487.75),FVector2D(0,0)}) {
            auto S=Sprite(Texture,Pivot,PPU);Reset(System,World,S);
            Check(System.ValidatePrivateMapContent(113,Error),"no-zone preflight: "+Error);
            Check(Error.empty(),"success retained error");
            DigimonMapRuntime::FPrivateMapGeometry Geometry;
            Check(DigimonMapRuntime::MakePrivateMapGeometry(&World,113,Geometry,&Error),"geometry");
            ADigimonVenomNXTLocalMapRenderer Renderer;
            const FVector RenderOrigin(900000,-800000,400);
            Check(Renderer.ShowMap(113,RenderOrigin),"no-zone local rendering");
            Check(Renderer.Component.Sprite==&S && !Renderer.Hidden && !Renderer.Component.Hidden &&
                  Renderer.Component.Visible && Renderer.Component.CustomDepth,"renderer presentation flags");
            Near3(Renderer.Location,RenderOrigin,"renderer origin");
            FVector Spawn;
            Check(System.GetPrivateMapSpawn(113,Spawn),"no-zone spawn");
            Near3(Spawn,ExpectedPoint({.15,.5}),"registered spawn");
            for (FVector2D UV:{FVector2D(.15,.5),FVector2D(.27,.18),FVector2D(.73,.81)}) {
                auto Rendered=Renderer.Component.Relative.TransformPosition(Geometry.Mapping.ImageToLocal({UV.X*1000,UV.Y*600}));
                Near3(Rendered,ExpectedPoint(UV,-6),"rendered image oracle");
                DigimonVenomNXTCollisionCore::Point Collision;
                Check(DigimonMapRuntime::PrivateImagePoint(Geometry,Rendered,Collision),"collision coordinate conversion");
                Near(Collision.X,UV.X*1000,"render/collision X");Near(Collision.Y,UV.Y*600,"render/collision Y");
                ADigimonVenomNXTMapZone MetadataZone;
                MetadataZone.Location=RenderOrigin;
                DigimonVenomNXTCollisionCore::Grid PublicGrid;
                const int LoadsBefore=AssetLoads;
                Check(DigimonMapRuntime::MakeCollisionGrid(&MetadataZone,World.GI.Data.Row,PublicGrid),"metadata-only public grid");
                DigimonVenomNXTCollisionCore::Point PublicPoint;
                Check(DigimonMapRuntime::ImagePoint(&MetadataZone,PublicGrid,Rendered+RenderOrigin,PublicPoint),"metadata-only public point");
                Near(PublicPoint.X,Collision.X,"public/private rendered collision X");
                Near(PublicPoint.Y,Collision.Y,"public/private rendered collision Y");
                Check(AssetLoads==LoadsBefore,"public collision loaded artwork");
            }
            const auto& Reachable=System.GetPrivateReachablePoints(113);
            Check(Reachable.Num()>500,"no-zone reachability returned empty/truncated map");
            FVector NPC,Other;
            Check(System.ResolvePrivateMapPoint(113,{.8,.7},NPC),"no-zone NPC placement");
            Check(System.ResolvePrivateMapPoint(113,{.8,.7},Other,TArray<FVector>{NPC}),"no-zone spaced NPC placement");
            Check(FVector::Dist2D(NPC,Other)>350,"NPC avoidance not preserved");
            for (FVector Origin:{FVector(0,0,0),FVector(900000,-800000,400),FVector(-720000,1100000,-80)}) {
                Check(System.IsPrivateMapLocationWalkable(113,Origin,Origin+Spawn),"translated spawn");
                Check(System.IsPrivateMapLocationWalkable(113,Origin,Origin+NPC),"translated NPC");
                Check(System.IsPrivateMapSegmentWalkable(113,Origin,Origin+Spawn,Origin+Spawn+FVector(24,0,0)),"translated movement");
            }
            Check(System.ZoneQueries==0,"private geometry consulted public map actors");
            ++TransformCases;
        }
        auto S=Sprite(Texture,{113.25,487.75},2);Reset(System,World,S);
        // A previously present public habitat may unload after a private session starts.
        // Both the existing candidate cache and a forced rebuild must survive this.
        PublicZonePresent=true;
        Check(System.ValidatePrivateMapContent(113,Error),"present-zone preflight");
        FVector BeforeUnload,AfterUnload;
        Check(System.ResolvePrivateMapPoint(113,{.8,.7},BeforeUnload),"present-zone placement");
        const auto WarmCount=System.GetPrivateReachablePoints(113).Num();
        PublicZonePresent=false;
        Check(System.ValidatePrivateMapContent(113,Error),"post-unload preflight");
        Check(System.ResolvePrivateMapPoint(113,{.8,.7},AfterUnload),"post-unload cached placement");
        Near3(AfterUnload,BeforeUnload,"unload cache stability");
        System.PrivateReachablePoints.Empty();
        Check(System.GetPrivateReachablePoints(113).Num()==WarmCount,"post-unload rebuilt reachability");
        Check(System.IsPrivateMapSegmentWalkable(113,{},BeforeUnload,BeforeUnload+FVector(24,0,0)),"post-unload movement");
        Check(System.ZoneQueries==0,"private path consulted public actors during unload");
        Reset(System,World,S);
        // Solid one-cell wall: both endpoints are valid but the sweep must fail.
        auto& Row=World.GI.Data.Row;
        for (int Y=0;Y<Row.WalkGridHeight;++Y) SetBlocked(Row,50,Y);
        auto A=ExpectedPoint({.45,.5}),B=ExpectedPoint({.55,.5});
        Check(System.IsPrivateMapLocationWalkable(113,{},A)&&System.IsPrivateMapLocationWalkable(113,{},B),"wall endpoints");
        Check(!System.IsPrivateMapSegmentWalkable(113,{},A,B),"segment tunneled through one-cell wall");
        const auto& LeftOnly=System.GetPrivateReachablePoints(113);
        Check(LeftOnly.Num()>100,"wall component unexpectedly empty");
        for (const auto& P:LeftOnly) Check(P.X>0,"BFS tunneled through wall");
        FVector Snapped;
        Check(System.ResolvePrivateMapPoint(113,{.9,.5},Snapped)&&Snapped.X>0,"NPC entered unreachable component");
        // Finite coordinates and the per-update maximum displacement remain enforced.
        const double NaN=std::numeric_limits<double>::quiet_NaN();
        Check(!System.IsPrivateMapSegmentWalkable(113,{NaN,0,0},A,A),"NaN origin accepted");
        Check(!System.IsPrivateMapSegmentWalkable(113,{},A,{NaN,0,0}),"NaN destination accepted");
        Check(!System.ResolvePrivateMapPoint(113,{NaN,.5},Snapped),"NaN placement accepted");
        Check(!System.ResolvePrivateMapPoint(113,{.2,.5},Snapped,TArray<FVector>{FVector(NaN,0,0)}),"NaN avoidance accepted");
        Reset(System,World,S);Settings.MapWorldWidth=10000;
        Check(!System.IsPrivateMapSegmentWalkable(113,{},ExpectedPoint({.1,.5}),ExpectedPoint({.4,.5})),"oversize step accepted");
        // Fail-closed source and collision guards, independent of public zone presence.
        Reset(System,World,S);World.GI.Data.Present=false;Reject(System,"MAP_REGISTRY_MISSING");
        Reset(System,World,S);UDigimonVenomNXTMapAssetRevision::Current=false;Reject(System,"MAP_CONTENT_UPGRADE_REQUIRED");
        ADigimonVenomNXTLocalMapRenderer StaleRenderer;
        StaleRenderer.Component.Sprite=&S;StaleRenderer.Hidden=false;
        Check(!StaleRenderer.ShowMap(113,{},&S),"stale content rendered through legacy fallback");
        Check(StaleRenderer.Hidden && !StaleRenderer.Component.Sprite,"stale content was not cleared/hidden");
        // Public rendering must clear both layers on any rejected transition.
        // The controller can unhide this actor later, so actor hiding alone is not sufficient.
        for (int Failure=0;Failure<9;++Failure) {
            Reset(System,World,S);
            ADigimonVenomNXTLocalMapRenderer Renderer;
            Check(Renderer.ShowMap(113,{}),"valid renderer before failed transition");
            Check(Renderer.ForegroundComponent.Sprite==&S&&Renderer.ForegroundComponent.Visible,"authored foreground not loaded");
            Near(Renderer.ForegroundComponent.Relative.Translation.Z,140.,"masked foreground must occlude avatar depth planes Z20..120");
            int Map=113;FVector Center;
            if(Failure==0)Map=0;
            if(Failure==1)Map=501;
            if(Failure==2)Center.X=NaN;
            if(Failure==3)UDigimonVenomNXTMapAssetRevision::Current=false;
            if(Failure==4)LoadedSprite=nullptr;
            if(Failure==5)World.GI.Data.Row.SourceWidth=999;
            if(Failure==6)World.GI.Data.Present=false;
            if(Failure==7)RenderWorld=nullptr;
            if(Failure==8)Settings.MapWorldWidth=0;
            Check(!Renderer.ShowMap(Map,Center),"invalid public map was rendered");
            Check(!Renderer.Component.Sprite&&!Renderer.ForegroundComponent.Sprite,"failed transition retained old map artwork");
            Check(!Renderer.Component.Visible&&!Renderer.ForegroundComponent.Visible,"failed transition retained layer visibility");
            Renderer.SetActorHiddenInGame(false);
            Check(!Renderer.Component.Sprite&&!Renderer.ForegroundComponent.Sprite,"controller unhide resurrected previous map");
        }
        Reset(System,World,S);LoadedSprite=nullptr;Reject(System,"MAP_ASSET_MISSING");
        auto Broken=S;Broken.BakedRenderData.clear();Reset(System,World,Broken);Reject(System,"MAP_COOKED_MAPPING");
        Broken=S;Broken.Atlas.SizeUV={.5,1};Reset(System,World,Broken);Reject(System,"MAP_TEXTURE_REGION");
        Reset(System,World,S);World.GI.Data.Row.SourceWidth=999;Reject(System,"MAP_SIZE_MISMATCH");
        Reset(System,World,S);World.GI.Data.Row.WalkGridBits.pop_back();Reject(System,"MAP_COLLISION_GRID");
        Reset(System,World,S);Settings.TamerCollisionProbeRadius=-1;Reject(System,"MAP_COLLISION_RADIUS");
        Reset(System,World,S);Settings.TamerCollisionProbeRadius=NaN;Reject(System,"MAP_COLLISION_RADIUS");
        Reset(System,World,S);World.GI.Data.Row.SafeSpawnUV={.505,.505};SetBlocked(World.GI.Data.Row,50,30);Reject(System,"MAP_SPAWN_BLOCKED");
        Reset(System,World,S);Settings.MapWorldWidth=0;Reject(System,"MAP_COLLISION_GRID");
        Reset(System,World,S);Settings.MapWorldWidth=NaN;Reject(System,"MAP_COLLISION_GRID");
        Reset(System,World,S);World.GI.Data.Row.SafeSpawnUV={NaN,.5};Reject(System,"MAP_SPAWN_BLOCKED");
        std::cout<<TransformCases<<" pivot/PPU cases with no public map actors; render/collision agreement, spawn, BFS, NPC spacing, origin invariance, wall sweep and invalid-data checks passed\n";
    } catch (const std::exception& E) { std::cerr<<E.what()<<'\n';return 1; }
    return 0;
}
'''


class PrivateCampaignGeometryTests(unittest.TestCase):
    def production(self):
        source=SOURCE.read_text(encoding='utf-8')
        start='// BEGIN PRIVATE MAP GEOMETRY'
        end='// END PRIVATE MAP GEOMETRY'
        self.assertEqual(source.count(start),1)
        self.assertEqual(source.count(end),1)
        helper=source.split(start,1)[1].split(end,1)[0]
        public_helper=source.split('// BEGIN PUBLIC MAP GEOMETRY',1)[1].split('// END PUBLIC MAP GEOMETRY',1)[0]
        methods=source[source.index('bool UDigimonVenomNXTWorldSubsystem::IsPrivateMapLocationWalkable'):]
        renderer=source[source.index('bool ADigimonVenomNXTLocalMapRenderer::ShowMap'):source.index('ADigimonVenomNXTMapZone::ADigimonVenomNXTMapZone()')]
        return 'namespace DigimonMapRuntime {\n'+public_helper+helper+'\n}\n'+renderer+methods

    def run_cpp(self, production):
        module=fixture_module()
        with tempfile.TemporaryDirectory(prefix='digimon-private-geometry-') as directory:
            root=Path(directory)
            (root/'Slate').mkdir()
            (root/'CoreMinimal.h').write_text(core_stub(module),encoding='utf-8')
            atlas=module.ATLAS_STUB.replace('int32 SizeX=256, SizeY=256;', 'int32 SizeX=256, SizeY=256; FString GetPathName() const { return "fixture texture"; }')
            (root/'Slate/SlateTextureAtlasInterface.h').write_text(atlas,encoding='utf-8')
            paper=module.PAPER_STUB.replace('float GetPixelsPerUnrealUnit()', 'float GetUnrealUnitsPerPixel() const { return 1.f/PixelsPerUnit; }\n    float GetPixelsPerUnrealUnit()')
            (root/'PaperSprite.h').write_text(paper,encoding='utf-8')
            unit=root/'private_geometry.cpp'
            unit.write_text(API_STUBS+production+CASES,encoding='utf-8')
            binary=root/'private_geometry'
            command=shlex.split(os.environ.get('CXX','g++'))+['-std=c++17','-Wall','-Wextra','-Werror','-pedantic',
                '-DWITH_EDITOR=0','-DWITH_EDITORONLY_DATA=0','-DUE_BUILD_SHIPPING=1','-I'+str(root),'-I'+str(PUBLIC),str(unit),'-o',str(binary)]
            built=subprocess.run(command,capture_output=True,text=True,timeout=40,check=False)
            self.assertEqual(built.returncode,0,built.stdout+built.stderr)
            return subprocess.run([str(binary)],capture_output=True,text=True,timeout=30,check=False)

    def test_production_private_geometry_without_public_actors(self):
        result=self.run_cpp(self.production())
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        print(result.stdout.strip())

    def test_public_zone_dependency_regression_is_detected(self):
        production=self.production()
        signature='bool UDigimonVenomNXTWorldSubsystem::ValidatePrivateMapContent(int32 SourceMapId, FString& OutError) const\n{'
        self.assertEqual(production.count(signature),1)
        mutant=production.replace(signature,signature+'\n    if (!FindMapZone(SourceMapId)) return false;',1)
        result=self.run_cpp(mutant)
        self.assertNotEqual(result.returncode,0,'public-zone dependency was not detected')
        self.assertIn('no-zone preflight',result.stderr)


if __name__=='__main__':
    unittest.main()
