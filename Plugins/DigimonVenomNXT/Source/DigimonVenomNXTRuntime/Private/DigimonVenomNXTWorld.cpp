#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTVariantCore.h"
#include "DigimonVenomNXTCollisionCore.h"
#include "DigimonVenomNXTSpriteCoordinates.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTTamerCharacter.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/PostProcessComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/Texture.h"
#include "EngineUtils.h"
#include "UObject/UObjectGlobals.h"

namespace DigimonMapRuntime
{
    static int32 ParseGeneratedMapId(const AActor* Actor)
    {
        if (!Actor) return INDEX_NONE;
        const FString Name = Actor->GetName();
        const FString Marker = TEXT("DVNXT_MapZone_");
        const int32 MarkerIndex = Name.Find(Marker, ESearchCase::IgnoreCase, ESearchDir::FromStart);
        if (MarkerIndex != INDEX_NONE)
        {
            const int32 Start = MarkerIndex + Marker.Len();
            int32 End = Start;
            while (End < Name.Len() && FChar::IsDigit(Name[End])) ++End;
            if (End > Start)
            {
                const int32 Parsed = FCString::Atoi(*Name.Mid(Start, End - Start));
                if (Parsed >= 1 && Parsed <= 500) return Parsed;
            }
        }

        // Final legacy fallback: the original auto-builder used a deterministic
        // 10-column grid at 14k x 11k spacing. This recovers map identity even
        // if an old level lost both its serialized MapId and original object name.
        const FVector L = Actor->GetActorLocation();
        const int32 Col = FMath::RoundToInt(L.X / 14000.0f);
        const int32 Row = FMath::RoundToInt(L.Y / 11000.0f);
        const int32 GridId = Row * 10 + Col + 1;
        const FVector Expected(Col * 14000.0f, Row * 11000.0f, L.Z);
        if (GridId >= 1 && GridId <= 500 && FVector::DistSquared2D(L, Expected) < FMath::Square(500.0f)) return GridId;
        return INDEX_NONE;
    }
    static void ConfigureCustomDepth(UPrimitiveComponent* Component)
    {
        if (!Component) return;
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        // Level artwork always participates in cel shading, including old saved
        // projects that still contain bRenderCustomDepthByDefault=False.
        Component->SetRenderCustomDepth(true);
        if (Settings && Component->CustomDepthStencilValue == 0)
            Component->SetCustomDepthStencilValue(FMath::Clamp(Settings->CustomDepthStencilValue, 0, 255));
    }

    // BEGIN PUBLIC MAP GEOMETRY
    // Public zones store movement metadata only. The local renderer displays one
    // selected texture; collision must never pull every habitat image into memory.
    static bool WorldPointToTextureUV(const ADigimonVenomNXTMapZone* Zone, const DigimonVenomNXTCollisionCore::Grid& Grid,
        const FVector& WorldPoint, FVector2D& OutUV)
    {
        if (!Zone || !DigimonVenomNXTCollisionCore::Valid(Grid) ||
            !DigimonVenomNXTSpriteCoordinates::IsFinitePoint(WorldPoint)) return false;
        const FVector Local = WorldPoint - Zone->GetActorLocation();
        // Same authored +90 roll / mirrored X registration as MakeMapSpriteTransform.
        OutUV = FVector2D(.5 - Local.X / Grid.WorldWidth, .5 - Local.Y / Grid.WorldHeight);
        return FMath::IsFinite(OutUV.X) && FMath::IsFinite(OutUV.Y);
    }

    static bool MakeCollisionGrid(const ADigimonVenomNXTMapZone* Zone, const FDigimonMapRow& Row, DigimonVenomNXTCollisionCore::Grid& Out)
    {
        if (!Zone || Row.SourceWidth <= 0 || Row.SourceHeight <= 0 ||
            !UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent()) return false;
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        const double Width = Settings ? Settings->MapWorldWidth : 10000.0;
        const double Height = Width * static_cast<double>(Row.SourceHeight) / Row.SourceWidth;
        Out = {Row.WalkGridWidth, Row.WalkGridHeight, Row.WalkGridBits.GetData(), static_cast<std::size_t>(Row.WalkGridBits.Num()), Width, Height};
        return DigimonVenomNXTCollisionCore::Valid(Out);
    }

    static bool ImagePoint(const ADigimonVenomNXTMapZone* Zone, const DigimonVenomNXTCollisionCore::Grid& Grid,
        const FVector& WorldPoint, DigimonVenomNXTCollisionCore::Point& Out)
    {
        FVector2D UV;
        if (!WorldPointToTextureUV(Zone, Grid, WorldPoint, UV)) return false;
        Out = {UV.X * Grid.WorldWidth, UV.Y * Grid.WorldHeight};
        return true;
    }
    // END PUBLIC MAP GEOMETRY

    static bool IsWorldSegmentWalkable(const ADigimonVenomNXTMapZone* Zone, const DigimonVenomNXTCollisionCore::Grid& Grid,
        const FVector& From, const FVector& To, double Radius)
    {
        DigimonVenomNXTCollisionCore::Point A, B;
        return ImagePoint(Zone, Grid, From, A) && ImagePoint(Zone, Grid, To, B) &&
            DigimonVenomNXTCollisionCore::IsSegmentWalkable(Grid, A, B, Radius);
    }

    // BEGIN PRIVATE MAP GEOMETRY
    // Private scenes are placed far from the public world's streaming cells.
    // Their render transform and collision frame therefore come from content,
    // never from an ADigimonVenomNXTMapZone that may not exist on this client.
    static bool MakeMapSpriteTransform(const UPaperSprite* Sprite, const DigimonVenomNXTSpriteCoordinates::FMapping& Mapping,
        double DesiredWidth, FTransform& OutTransform)
    {
        if (!Sprite || !FMath::IsFinite(DesiredWidth) || DesiredWidth <= 0.0 ||
            !FMath::IsFinite(Mapping.ImageSize.X) || !FMath::IsFinite(Mapping.ImageSize.Y) ||
            Mapping.ImageSize.X <= 0.0 || Mapping.ImageSize.Y <= 0.0) return false;
        const float UnitsPerPixel = FMath::Max(0.001f, Sprite->GetUnrealUnitsPerPixel());
        const float NativeWidth = FMath::Max(1.0f, Mapping.ImageSize.X * UnitsPerPixel);
        const float UniformScale = DesiredWidth / NativeWidth;
        if (!FMath::IsFinite(UniformScale) || UniformScale <= 0.0f) return false;
        FTransform Transform(FRotator(0.0f, 0.0f, 90.0f), FVector(0, 0, -6),
            FVector(-UniformScale, UniformScale, UniformScale));
        const FVector ImageCenter = Mapping.ImageToLocal(Mapping.ImageSize * .5);
        Transform.SetTranslation(FVector(0, 0, -6) - Transform.TransformVector(ImageCenter));
        if (Transform.ContainsNaN()) return false;
        OutTransform = Transform;
        return true;
    }

    struct FPrivateMapGeometry
    {
        DigimonVenomNXTSpriteCoordinates::FMapping Mapping;
        FTransform SpriteTransform;
        DigimonVenomNXTCollisionCore::Grid Grid;
        double Radius = 0.0;
        FVector Spawn = FVector::ZeroVector;
    };

    static bool PrivateImagePoint(const FPrivateMapGeometry& Geometry, const FVector& Local,
        DigimonVenomNXTCollisionCore::Point& Out)
    {
        if (!DigimonVenomNXTSpriteCoordinates::IsFinitePoint(Local)) return false;
        const FVector SpriteLocal = Geometry.SpriteTransform.InverseTransformPosition(Local);
        if (!DigimonVenomNXTSpriteCoordinates::IsFinitePoint(SpriteLocal)) return false;
        const FVector2D Pixels = Geometry.Mapping.LocalToImage(SpriteLocal);
        Out = {Pixels.X / Geometry.Mapping.ImageSize.X * Geometry.Grid.WorldWidth,
            Pixels.Y / Geometry.Mapping.ImageSize.Y * Geometry.Grid.WorldHeight};
        return FMath::IsFinite(Out.X) && FMath::IsFinite(Out.Y);
    }

    static bool IsPrivateSegmentWalkable(const FPrivateMapGeometry& Geometry, const FVector& From, const FVector& To)
    {
        if (!DigimonVenomNXTSpriteCoordinates::IsFinitePoint(From) || !DigimonVenomNXTSpriteCoordinates::IsFinitePoint(To) ||
            FVector::DistSquared2D(From, To) > FMath::Square(2000.0)) return false;
        DigimonVenomNXTCollisionCore::Point A, B;
        return PrivateImagePoint(Geometry, From, A) && PrivateImagePoint(Geometry, To, B) &&
            DigimonVenomNXTCollisionCore::IsSegmentWalkable(Geometry.Grid, A, B, Geometry.Radius);
    }

    static bool MakePrivateMapGeometry(const UWorld* World, int32 SourceMapId, FPrivateMapGeometry& Out, FString* OutError = nullptr)
    {
        if (OutError) OutError->Reset();
        const auto Fail = [&](const TCHAR* Code, const TCHAR* Message, const FString& Detail) -> bool
        {
            if (OutError)
            {
                *OutError = FString::Printf(TEXT("Campaign habitat %03d: %s [%s]. Your saved progress is safe."), SourceMapId, Message, Code);
                UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT campaign preflight [%s] source map %03d: %s"), Code, SourceMapId, *Detail);
            }
            return false;
        };
        const UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
        const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        const FDigimonMapRow* Row = Data ? Data->FindMap(SourceMapId) : nullptr;
        if (!Row)
            return Fail(TEXT("MAP_REGISTRY_MISSING"), TEXT("the habitat's collision record is unavailable"), TEXT("DigimonMaps.json was not loaded or does not contain this map id."));
        if (!UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent())
            return Fail(TEXT("MAP_CONTENT_UPGRADE_REQUIRED"), TEXT("the polished maps need to be prepared; run Tools > Digimon Venom NXT: Build Complete Game Content, then save and rebuild the game"),
                TEXT("The complete playable-map import receipt is missing, incomplete, or belongs to another artwork/collision revision."));
        const FString SpritePath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d.SP_PlayMap_%03d"), SourceMapId, SourceMapId);
        UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, *SpritePath);
        if (!Sprite)
            return Fail(TEXT("MAP_ASSET_MISSING"), TEXT("this build is missing the habitat artwork"), SpritePath);
        FPrivateMapGeometry Candidate;
        if (!DigimonVenomNXTSpriteCoordinates::TryGetMapping(Sprite, Candidate.Mapping))
            return Fail(TEXT("MAP_COOKED_MAPPING"), TEXT("the packaged sprite has invalid coordinate data"),
                FString::Printf(TEXT("%s: baked vertices=%d, pixels per unit=%g; the runtime sprite mapping could not be reconstructed."),
                    *SpritePath, Sprite->BakedRenderData.Num(), static_cast<double>(Sprite->GetPixelsPerUnrealUnit())));
        if (!DigimonVenomNXTSpriteCoordinates::IsFullTexture(Sprite))
            return Fail(TEXT("MAP_TEXTURE_REGION"), TEXT("the sprite's image region does not match its collision mask"),
                FString::Printf(TEXT("%s: the registered map must cover its full texture."), *SpritePath));
        if (!FMath::IsNearlyEqual(Candidate.Mapping.ImageSize.X, static_cast<double>(Row->SourceWidth), .01) ||
            !FMath::IsNearlyEqual(Candidate.Mapping.ImageSize.Y, static_cast<double>(Row->SourceHeight), .01))
            return Fail(TEXT("MAP_SIZE_MISMATCH"), TEXT("the artwork and collision mask have different dimensions"),
                FString::Printf(TEXT("%s: runtime image %.6f x %.6f; registered source %d x %d."),
                    *SpritePath, Candidate.Mapping.ImageSize.X, Candidate.Mapping.ImageSize.Y, Row->SourceWidth, Row->SourceHeight));
        const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
        const double Width = Settings ? Settings->MapWorldWidth : 10000.0;
        if (!MakeMapSpriteTransform(Sprite, Candidate.Mapping, Width, Candidate.SpriteTransform))
            return Fail(TEXT("MAP_COLLISION_GRID"), TEXT("the collision grid or map scale is invalid"),
                FString::Printf(TEXT("MapWorldWidth=%g."), Width));
        const FVector ImageEdgeX = Candidate.SpriteTransform.TransformVector(Candidate.Mapping.ImageAxisX * Candidate.Mapping.ImageSize.X);
        const FVector ImageEdgeY = Candidate.SpriteTransform.TransformVector(Candidate.Mapping.ImageAxisY * Candidate.Mapping.ImageSize.Y);
        Candidate.Grid = {Row->WalkGridWidth, Row->WalkGridHeight, Row->WalkGridBits.GetData(), static_cast<std::size_t>(Row->WalkGridBits.Num()),
            ImageEdgeX.Size(), ImageEdgeY.Size()};
        if (!DigimonVenomNXTCollisionCore::Valid(Candidate.Grid))
            return Fail(TEXT("MAP_COLLISION_GRID"), TEXT("the collision grid or map scale is invalid"),
                FString::Printf(TEXT("Grid %d x %d, bytes=%d; map world size %.6f x %.6f."), Row->WalkGridWidth, Row->WalkGridHeight,
                    Row->WalkGridBits.Num(), Candidate.Grid.WorldWidth, Candidate.Grid.WorldHeight));
        Candidate.Radius = Settings ? Settings->TamerCollisionProbeRadius : 34.0;
        if (!FMath::IsFinite(Candidate.Radius) || Candidate.Radius < 0.0)
            return Fail(TEXT("MAP_COLLISION_RADIUS"), TEXT("the movement collision radius is invalid"),
                FString::Printf(TEXT("TamerCollisionProbeRadius=%g."), Candidate.Radius));
        if (!FMath::IsFinite(Row->SafeSpawnUV.X) || !FMath::IsFinite(Row->SafeSpawnUV.Y))
            return Fail(TEXT("MAP_SPAWN_BLOCKED"), TEXT("the registered arrival point is invalid"), TEXT("SafeSpawnUV contains a non-finite coordinate."));
        const FVector2D SpawnPixels(FMath::Clamp(static_cast<double>(Row->SafeSpawnUV.X), 0.0, 1.0) * Candidate.Mapping.ImageSize.X,
            FMath::Clamp(static_cast<double>(Row->SafeSpawnUV.Y), 0.0, 1.0) * Candidate.Mapping.ImageSize.Y);
        Candidate.Spawn = Candidate.SpriteTransform.TransformPosition(Candidate.Mapping.ImageToLocal(SpawnPixels));
        Candidate.Spawn.Z = 100.0;
        if (!IsPrivateSegmentWalkable(Candidate, Candidate.Spawn, Candidate.Spawn))
            return Fail(TEXT("MAP_SPAWN_BLOCKED"), TEXT("the registered arrival point is blocked"),
                FString::Printf(TEXT("Spawn %s, safe UV %.9f / %.9f, radius=%g, map world size %.6f x %.6f."),
                    *Candidate.Spawn.ToString(), Row->SafeSpawnUV.X, Row->SafeSpawnUV.Y, Candidate.Radius,
                    Candidate.Grid.WorldWidth, Candidate.Grid.WorldHeight));
        Out = Candidate;
        return true;
    }
    // END PRIVATE MAP GEOMETRY

    static void DisableLegacyBoundaryWall(UBoxComponent* Wall)
    {
        if (!Wall) return;
        Wall->SetHiddenInGame(true);
        Wall->SetVisibility(false);
        // The exact mask owns collision. Retain serialized components for old maps,
        // but never let their arbitrary rectangular inset clip real paths.
        Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Wall->SetCollisionResponseToAllChannels(ECR_Ignore);
        Wall->SetGenerateOverlapEvents(false);
    }

}


ADigimonVenomNXTLocalMapRenderer::ADigimonVenomNXTLocalMapRenderer()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = false;
    SetActorEnableCollision(false);

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    GroundSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GroundSprite"));
    GroundSprite->SetupAttachment(Root);
    GroundSprite->SetMobility(EComponentMobility::Movable);
    GroundSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GroundSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    GroundSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -6.0f));
    GroundSprite->SetTranslucentSortPriority(-100);
    DigimonMapRuntime::ConfigureCustomDepth(GroundSprite);
    ForegroundSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ForegroundSprite"));
    ForegroundSprite->SetupAttachment(Root);
    ForegroundSprite->SetMobility(EComponentMobility::Movable);
    ForegroundSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ForegroundSprite->SetTranslucentSortPriority(200);
    DigimonMapRuntime::ConfigureCustomDepth(ForegroundSprite);

}

bool ADigimonVenomNXTLocalMapRenderer::ShowMap(int32 InMapId, const FVector& ZoneCenter, UPaperSprite* LegacyFallbackSprite)
{
    // A failed transition must not leave the previous habitat's occlusion layer
    // visible when the controller next restores this renderer's visibility.
    if (GroundSprite)
    {
        GroundSprite->SetSprite(nullptr);
        GroundSprite->SetVisibility(false, true);
    }
    if (ForegroundSprite)
    {
        ForegroundSprite->SetSprite(nullptr);
        ForegroundSprite->SetVisibility(false, true);
    }
    SetActorHiddenInGame(true);
    if (!GroundSprite || InMapId < 1 || InMapId > 500 || !DigimonVenomNXTSpriteCoordinates::IsFinitePoint(ZoneCenter)) return false;

    if (!UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent())
    {
        GroundSprite->SetSprite(nullptr);
        SetActorHiddenInGame(true);
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT polished map content is not ready. Run Tools > Digimon Venom NXT: Build Complete Game Content, then save and rebuild the game. Legacy artwork will not be displayed."));
        return false;
    }

    UPaperSprite* Sprite = nullptr;
    const FString SpritePath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d.SP_PlayMap_%03d"), InMapId, InMapId);
    Sprite = LoadObject<UPaperSprite>(nullptr, *SpritePath);

    // Never fall back to legacy SP_Map assets: older imports mixed collision masks into those slots.
    // SP_PlayMap assets are generated by the dedicated playable-map repair tool and
    // are safe for packaged runtime use. Keeping sprite creation editor-only avoids
    // relying on Paper2D editor initialization APIs in shipping builds.
    (void)LegacyFallbackSprite;

    if (!Sprite)
    {
        GroundSprite->SetSprite(nullptr);
        SetActorHiddenInGame(true);
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT map %d is missing SP_PlayMap_%03d. Run Tools -> Digimon Venom NXT: Build Complete Game Content once."), InMapId, InMapId);
        return false;
    }

    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const double DesiredWidth = Settings ? Settings->MapWorldWidth : 10000.0;
    DigimonVenomNXTSpriteCoordinates::FMapping Mapping;
    FTransform SpriteTransform;
    const UGameInstance* GI = GetGameInstance();
    const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    const FDigimonMapRow* Row = Data ? Data->FindMap(InMapId) : nullptr;
    if (!Row || !DigimonVenomNXTSpriteCoordinates::IsFullTexture(Sprite) ||
        !DigimonVenomNXTSpriteCoordinates::TryGetMapping(Sprite, Mapping) ||
        !FMath::IsNearlyEqual(Mapping.ImageSize.X, static_cast<double>(Row->SourceWidth), .01) ||
        !FMath::IsNearlyEqual(Mapping.ImageSize.Y, static_cast<double>(Row->SourceHeight), .01) ||
        !DigimonMapRuntime::MakeMapSpriteTransform(Sprite, Mapping, DesiredWidth, SpriteTransform))
    {
        GroundSprite->SetSprite(nullptr);
        SetActorHiddenInGame(true);
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT map %d artwork does not match its registered full-image collision geometry, or has an invalid map scale."), InMapId);
        return false;
    }

    GroundSprite->SetSprite(Sprite);
    GroundSprite->SetRelativeTransform(SpriteTransform);

    // Source-authored occlusion layers are separate from the collision mask.
    // Their canvas registration is identical to the ground image.
    if (ForegroundSprite)
    {
        ForegroundSprite->SetSprite(nullptr);
        ForegroundSprite->SetVisibility(false);
        const FString ForegroundPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d_Foreground.SP_PlayMap_%03d_Foreground"), InMapId, InMapId);
        if (UPaperSprite* Foreground = LoadObject<UPaperSprite>(nullptr, *ForegroundPath, nullptr, LOAD_NoWarn | LOAD_Quiet))
        {
            DigimonVenomNXTSpriteCoordinates::FMapping ForegroundMapping;
            FTransform ForegroundTransform;
            if (DigimonVenomNXTSpriteCoordinates::IsFullTexture(Foreground) &&
                DigimonVenomNXTSpriteCoordinates::TryGetMapping(Foreground, ForegroundMapping) &&
                ForegroundMapping.ImageSize.Equals(Mapping.ImageSize, .01) &&
                DigimonMapRuntime::MakeMapSpriteTransform(Foreground, ForegroundMapping, DesiredWidth, ForegroundTransform))
            {
                // Foreground is masked and writes depth. Sort priority cannot
                // place it over field avatars, whose visual planes span Z20..120.
                ForegroundTransform.AddToTranslation(FVector(0, 0, 146));
                ForegroundSprite->SetSprite(Foreground);
                ForegroundSprite->SetRelativeTransform(ForegroundTransform);
                ForegroundSprite->SetVisibility(true);
            }
        }
    }

    SetActorLocation(FVector(ZoneCenter.X, ZoneCenter.Y, ZoneCenter.Z));
    SetActorHiddenInGame(false);
    GroundSprite->SetHiddenInGame(false, true);
    GroundSprite->SetVisibility(true, true);
    DigimonMapRuntime::ConfigureCustomDepth(GroundSprite);
    return true;
}

ADigimonVenomNXTMapZone::ADigimonVenomNXTMapZone()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    GroundSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GroundSprite"));
    GroundSprite->SetupAttachment(Root);
    GroundSprite->SetMobility(EComponentMobility::Movable);
    GroundSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    // Paper sprites are authored in X/Z. +90 roll keeps the FRONT face toward the overhead camera. The local-X mirror plus +90 camera yaw preserves both source up/down and source left/right on screen.
    GroundSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    GroundSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -6.0f));
    GroundSprite->SetTranslucentSortPriority(-100);
    DigimonMapRuntime::ConfigureCustomDepth(GroundSprite);

    PlayBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayBounds"));
    PlayBounds->SetupAttachment(Root);
    PlayBounds->SetBoxExtent(FVector(4800.0f, 2300.0f, 300.0f));
    PlayBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PlayBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    PlayBounds->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    PlayBounds->SetGenerateOverlapEvents(false);

    PlayerSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerSpawn"));
    PlayerSpawn->SetupAttachment(Root);
    PlayerSpawn->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    NorthWall = CreateDefaultSubobject<UBoxComponent>(TEXT("NorthWall"));
    SouthWall = CreateDefaultSubobject<UBoxComponent>(TEXT("SouthWall"));
    EastWall = CreateDefaultSubobject<UBoxComponent>(TEXT("EastWall"));
    WestWall = CreateDefaultSubobject<UBoxComponent>(TEXT("WestWall"));
    for (UBoxComponent* Wall : {NorthWall.Get(), SouthWall.Get(), EastWall.Get(), WestWall.Get()})
    {
        Wall->SetupAttachment(Root);
        DigimonMapRuntime::DisableLegacyBoundaryWall(Wall);
    }
}

void ADigimonVenomNXTMapZone::BeginPlay()
{
    Super::BeginPlay();
    ApplyMapPresentation();
    // Runtime rendering is owned by the local per-player map renderer. Keep all
    // legacy placed zone sprites hidden so they can never z-fight or leak across maps.
    SetLocalPresentationActive(false);
}

void ADigimonVenomNXTMapZone::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    ApplyMapPresentation();
}

void ADigimonVenomNXTMapZone::ApplyMapPresentation()
{
    if (!GroundSprite || !PlayBounds) return;
    MapId = GetRuntimeMapId();
    // Do not serialize or retain an image on any public zone. This also repairs
    // a previously generated world that eagerly referenced the entire map catalog.
    MapSprite = nullptr;
    GroundSprite->SetSprite(nullptr);
    GroundSprite->SetHiddenInGame(true, true);
    GroundSprite->SetVisibility(false, true);

    if (const UGameInstance* GI = GetGameInstance())
        if (const UDigimonVenomNXTDataSubsystem* Data = GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>())
            if (const FDigimonMapRow* Row = Data->FindMap(MapId))
            {
                SourceImageSize = FIntPoint(Row->SourceWidth, Row->SourceHeight);
                SafeSpawnUV = Row->SafeSpawnUV;
                DisplayName = Row->DisplayName;
                Region = Row->Region;
                MinLevel = Row->RecommendedMinLevel;
                MaxLevel = Row->RecommendedMaxLevel;
                WildSpecies = Row->WildSpecies;
            }

    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const double Width = Settings ? Settings->MapWorldWidth : 10000.0;
    const bool bValidGeometry = SourceImageSize.X > 0 && SourceImageSize.Y > 0 && FMath::IsFinite(Width) && Width > 0.0;
    const double WorldWidth = bValidGeometry ? Width : 0.0;
    const double WorldHeight = bValidGeometry ? Width * static_cast<double>(SourceImageSize.Y) / SourceImageSize.X : 0.0;
    PlayBounds->SetBoxExtent(FVector(WorldWidth * .5, WorldHeight * .5, 300.0), false);
    for (UBoxComponent* Wall : {NorthWall.Get(), SouthWall.Get(), EastWall.Get(), WestWall.Get()})
        DigimonMapRuntime::DisableLegacyBoundaryWall(Wall);
    if (PlayerSpawn)
    {
        const double U = FMath::IsFinite(SafeSpawnUV.X) ? FMath::Clamp(SafeSpawnUV.X, 0.0, 1.0) : .5;
        const double V = FMath::IsFinite(SafeSpawnUV.Y) ? FMath::Clamp(SafeSpawnUV.Y, 0.0, 1.0) : .5;
        PlayerSpawn->SetRelativeLocation(FVector((.5 - U) * WorldWidth, (.5 - V) * WorldHeight, 100.0));
    }
}


int32 ADigimonVenomNXTMapZone::GetRuntimeMapId() const
{
    if (const int32 Parsed = DigimonMapRuntime::ParseGeneratedMapId(this); Parsed != INDEX_NONE) return Parsed;
    return (MapId >= 1 && MapId <= 500) ? MapId : 1;
}

void ADigimonVenomNXTMapZone::SetLocalPresentationActive(bool bActive)
{
    if (!GroundSprite) return;
    GroundSprite->SetHiddenInGame(!bActive, true);
    GroundSprite->SetVisibility(bActive, true);
}

#if WITH_EDITOR
void ADigimonVenomNXTMapZone::SetEditorPreviewActive(bool bActive)
{
    const bool bEditorWorld = GetWorld() && GetWorld()->WorldType == EWorldType::Editor;
    if (!bActive || !bEditorWorld || EditorPreviewMapId != GetRuntimeMapId())
    {
        for (UPaperSpriteComponent* Preview : {EditorGroundPreview.Get(), EditorForegroundPreview.Get()})
            if (Preview) { Preview->SetSprite(nullptr); Preview->DestroyComponent(); }
        EditorGroundPreview = nullptr;
        EditorForegroundPreview = nullptr;
        EditorPreviewMapId = INDEX_NONE;
        if (!bActive || !bEditorWorld) return;
    }
    if (EditorGroundPreview && EditorGroundPreview->GetSprite()) return;

    const int32 PreviewMapId = GetRuntimeMapId();
    const FString Path = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d.SP_PlayMap_%03d"), PreviewMapId, PreviewMapId);
    UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, *Path, nullptr, LOAD_NoWarn | LOAD_Quiet);
    DigimonVenomNXTSpriteCoordinates::FMapping Mapping;
    FTransform Transform;
    const double Width = GetDefault<UDigimonVenomNXTSettings>()->MapWorldWidth;
    if (!Sprite || !DigimonVenomNXTSpriteCoordinates::TryGetMapping(Sprite, Mapping) ||
        !DigimonMapRuntime::MakeMapSpriteTransform(Sprite, Mapping, Width, Transform)) return;

    const auto MakePreview = [&](const TCHAR* Name, UPaperSprite* Art, const FTransform& Placement, int32 Sort) -> UPaperSpriteComponent*
    {
        // Dynamic transient components keep these temporary asset references out
        // of the saved level and every PIE/cooked copy of the zone actor.
        const FName ComponentName = MakeUniqueObjectName(this, UPaperSpriteComponent::StaticClass(), FName(Name));
        UPaperSpriteComponent* Preview = NewObject<UPaperSpriteComponent>(this, ComponentName, RF_Transient | RF_DuplicateTransient | RF_TextExportTransient);
        Preview->bIsEditorOnly = true;
        Preview->SetMobility(EComponentMobility::Movable);
        Preview->SetupAttachment(Root);
        Preview->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        // Keep artwork visible when the editor viewport's Game View is enabled.
        // Editor-world gating and duplicate-transient flags exclude gameplay copies.
        Preview->SetHiddenInGame(false);
        Preview->SetTranslucentSortPriority(Sort);
        Preview->SetSprite(Art);
        Preview->SetRelativeTransform(Placement);
        Preview->RegisterComponent();
        return Preview;
    };
    EditorGroundPreview = MakePreview(TEXT("EditorGroundPreview"), Sprite, Transform, -100);
    EditorPreviewMapId = PreviewMapId;
    const FString ForegroundPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d_Foreground.SP_PlayMap_%03d_Foreground"), PreviewMapId, PreviewMapId);
    if (UPaperSprite* Foreground = LoadObject<UPaperSprite>(nullptr, *ForegroundPath, nullptr, LOAD_NoWarn | LOAD_Quiet))
    {
        DigimonVenomNXTSpriteCoordinates::FMapping ForegroundMapping;
        FTransform ForegroundTransform;
        if (DigimonVenomNXTSpriteCoordinates::TryGetMapping(Foreground, ForegroundMapping) &&
            ForegroundMapping.ImageSize.Equals(Mapping.ImageSize, .01) &&
            DigimonMapRuntime::MakeMapSpriteTransform(Foreground, ForegroundMapping, Width, ForegroundTransform))
        {
            ForegroundTransform.AddToTranslation(FVector(0, 0, 146));
            EditorForegroundPreview = MakePreview(TEXT("EditorForegroundPreview"), Foreground, ForegroundTransform, 200);
        }
    }
}
#endif

FVector ADigimonVenomNXTMapZone::GetPlayerSpawnLocation() const
{
    return PlayerSpawn ? PlayerSpawn->GetComponentLocation() : GetActorLocation();
}

FVector2D ADigimonVenomNXTMapZone::GetPlayableHalfExtents() const
{
    const FVector Extent = PlayBounds ? PlayBounds->GetScaledBoxExtent() : FVector(5000.0f, 2500.0f, 300.0f);
    return FVector2D(Extent.X, Extent.Y);
}

ADigimonVenomNXTMapZone* UDigimonVenomNXTWorldSubsystem::FindMapZone(int32 MapId) const
{
    if (!GetWorld()) return nullptr;
    for (TActorIterator<ADigimonVenomNXTMapZone> It(GetWorld()); It; ++It)
    {
        if (It->GetRuntimeMapId() == MapId) return *It;
    }
    return nullptr;
}





TArray<ADigimonVenomNXTMapZone*> UDigimonVenomNXTWorldSubsystem::GetAllMapZones() const
{
    TArray<ADigimonVenomNXTMapZone*> Out;
    if (!GetWorld()) return Out;
    for (TActorIterator<ADigimonVenomNXTMapZone> It(GetWorld()); It; ++It) Out.Add(*It);
    Out.Sort([](const ADigimonVenomNXTMapZone& A, const ADigimonVenomNXTMapZone& B){ return A.GetRuntimeMapId() < B.GetRuntimeMapId(); });
    return Out;
}

bool UDigimonVenomNXTWorldSubsystem::IsWorldLocationWalkable(int32 MapId, const FVector& WorldLocation) const
{
    return IsWorldSegmentWalkable(MapId, WorldLocation, WorldLocation);
}

bool UDigimonVenomNXTWorldSubsystem::IsWorldSegmentWalkable(int32 MapId, const FVector& From, const FVector& To) const
{
    if (!GetWorld() || From.ContainsNaN() || To.ContainsNaN() || FVector::DistSquared2D(From, To) > FMath::Square(2000.0)) return false;
    const UGameInstance* GI = GetWorld()->GetGameInstance();
    const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    ADigimonVenomNXTMapZone* Zone = FindMapZone(MapId);
    const FDigimonMapRow* Row = Data ? Data->FindMap(MapId) : nullptr;
    DigimonVenomNXTCollisionCore::Grid Grid;
    if (!Row || !DigimonMapRuntime::MakeCollisionGrid(Zone, *Row, Grid)) return false;
    const double Radius = GetDefault<UDigimonVenomNXTSettings>()->TamerCollisionProbeRadius;
    return DigimonMapRuntime::IsWorldSegmentWalkable(Zone, Grid, From, To, Radius);
}

bool UDigimonVenomNXTWorldSubsystem::TravelPlayerToMap(AController* Controller, int32 MapId, FString& OutError)
{
    if (!Controller || !Controller->HasAuthority()) { OutError = TEXT("Map travel must be authorized by the server."); return false; }

    if (!UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent())
    {
        OutError = TEXT("The polished map update has not been prepared. Run Tools > Digimon Venom NXT: Build Complete Game Content, then save and rebuild the game. Your saved progress is safe.");
        return false;
    }
    if (const ADigimonVenomNXTPlayerController* DigimonController = Cast<ADigimonVenomNXTPlayerController>(Controller))
        if (DigimonController->IsInDigiFarm() || DigimonController->IsInRelay()) { OutError = TEXT("Leave your private campaign or DigiFarm before travelling to a public habitat."); return false; }
    const UGameInstance* GI = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
    const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonMapRow RealMapRow;
    if (!Data || !Data->GetMap(MapId, RealMapRow)) { OutError = FString::Printf(TEXT("Map %d is not a real playable habitat in the current content pack."), MapId); return false; }
    ADigimonVenomNXTMapZone* Zone = FindMapZone(MapId);
    if (!Zone)
    {
        OutError = FString::Printf(TEXT("Map %d is not placed in the public world."), MapId);
        return false;
    }
    APawn* Pawn = Controller->GetPawn();
    if (!Pawn) { OutError = TEXT("Player pawn is not available."); return false; }

    Zone->ApplyMapPresentation();
    if (!IsWorldLocationWalkable(MapId, Zone->GetPlayerSpawnLocation()))
    {
        OutError = TEXT("This habitat has no valid collision-safe arrival point. Repair the map collision before travelling.");
        return false;
    }
    if (!Pawn->TeleportTo(Zone->GetPlayerSpawnLocation(), Pawn->GetActorRotation(), false, true))
    {
        OutError = TEXT("Could not move the player to the selected map."); return false;
    }

    if (ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>()) PS->SetCurrentMap(MapId);
    if (ADigimonVenomNXTTamerCharacter* Tamer = Cast<ADigimonVenomNXTTamerCharacter>(Pawn))
    {
        Tamer->ResetEncounterTracker();
        Tamer->SnapFollowerToTamer();
    }
    return true;
}

EDigimonVariant UDigimonVenomNXTWorldSubsystem::RollWildVariant() const
{
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    return static_cast<EDigimonVariant>(DigimonVenomNXTVariantCore::RollWildVariant(
        FMath::FRand(), S->ShinyChance, S->ParadoxChance, S->FirewallChance));
}


bool UDigimonVenomNXTWorldSubsystem::IsPrivateMapLocationWalkable(int32 SourceMapId, const FVector& Origin, const FVector& Location) const
{
    return IsPrivateMapSegmentWalkable(SourceMapId, Origin, Location, Location);
}

bool UDigimonVenomNXTWorldSubsystem::IsPrivateMapSegmentWalkable(int32 SourceMapId, const FVector& Origin, const FVector& From, const FVector& To) const
{
    if (!DigimonVenomNXTSpriteCoordinates::IsFinitePoint(Origin) || !DigimonVenomNXTSpriteCoordinates::IsFinitePoint(From) ||
        !DigimonVenomNXTSpriteCoordinates::IsFinitePoint(To)) return false;
    DigimonMapRuntime::FPrivateMapGeometry Geometry;
    return DigimonMapRuntime::MakePrivateMapGeometry(GetWorld(), SourceMapId, Geometry) &&
        DigimonMapRuntime::IsPrivateSegmentWalkable(Geometry, From - Origin, To - Origin);
}

bool UDigimonVenomNXTWorldSubsystem::ValidatePrivateMapContent(int32 SourceMapId, FString& OutError) const
{
    DigimonMapRuntime::FPrivateMapGeometry Geometry;
    return DigimonMapRuntime::MakePrivateMapGeometry(GetWorld(), SourceMapId, Geometry, &OutError);
}

bool UDigimonVenomNXTWorldSubsystem::GetPrivateMapSpawn(int32 SourceMapId, FVector& OutLocal) const
{
    DigimonMapRuntime::FPrivateMapGeometry Geometry;
    if (!DigimonMapRuntime::MakePrivateMapGeometry(GetWorld(), SourceMapId, Geometry)) return false;
    OutLocal = Geometry.Spawn;
    return true;
}

const TArray<FVector>& UDigimonVenomNXTWorldSubsystem::GetPrivateReachablePoints(int32 SourceMapId) const
{
    const double RadiusSetting = GetDefault<UDigimonVenomNXTSettings>()->TamerCollisionProbeRadius;
    const double WidthSetting = GetDefault<UDigimonVenomNXTSettings>()->MapWorldWidth;
    if (RadiusSetting != CachedPlacementRadius || WidthSetting != CachedPlacementWidth)
    {
        PrivateReachablePoints.Empty();
        CachedPlacementRadius = RadiusSetting;
        CachedPlacementWidth = WidthSetting;
    }
    if (const TArray<FVector>* Cached = PrivateReachablePoints.Find(SourceMapId))
        if (!Cached->IsEmpty()) return *Cached;
    TArray<FVector>& Points = PrivateReachablePoints.Add(SourceMapId);
    DigimonMapRuntime::FPrivateMapGeometry Geometry;
    if (!DigimonMapRuntime::MakePrivateMapGeometry(GetWorld(), SourceMapId, Geometry)) return Points;
    const FVector Spawn = Geometry.Spawn;
    // Every accepted edge is checked as a complete swept disk. A midpoint test
    // could jump a one-pixel obstruction and publish an unreachable NPC anchor.
    constexpr float Step = 24.0f;
    TArray<FIntPoint> Queue;
    TSet<FIntPoint> Visited;
    Queue.Add(FIntPoint::ZeroValue);
    Visited.Add(FIntPoint::ZeroValue);
    const FIntPoint Neighbours[] = {FIntPoint(1,0),FIntPoint(-1,0),FIntPoint(0,1),FIntPoint(0,-1)};
    const FVector2D Half(Geometry.Grid.WorldWidth * .5, Geometry.Grid.WorldHeight * .5);
    for (int32 Head = 0; Head < Queue.Num(); ++Head)
    {
        const FIntPoint Cell = Queue[Head];
        const FVector P = Spawn + FVector(Cell.X * Step, Cell.Y * Step, 0);
        Points.Add(P);
        for (const FIntPoint& Offset : Neighbours)
        {
            const FIntPoint Next = Cell + Offset;
            if (Visited.Contains(Next)) continue;
            const FVector Candidate = Spawn + FVector(Next.X * Step, Next.Y * Step, 0);
            if (FMath::Abs(Candidate.X) > Half.X || FMath::Abs(Candidate.Y) > Half.Y) continue;
            if (DigimonMapRuntime::IsPrivateSegmentWalkable(Geometry, P, Candidate))
            {
                // An edge may graze an obstacle even when another incoming edge
                // reaches this cell. Only mark a successfully reached cell visited.
                Visited.Add(Next);
                Queue.Add(Next);
            }
        }
    }
    return Points;
}

bool UDigimonVenomNXTWorldSubsystem::ResolvePrivateMapPoint(int32 SourceMapId, const FVector2D& DesiredUV, FVector& OutLocal, const TArray<FVector>& AvoidPoints) const
{
    if (!FMath::IsFinite(DesiredUV.X) || !FMath::IsFinite(DesiredUV.Y)) return false;
    for (const FVector& Avoid : AvoidPoints)
        if (!DigimonVenomNXTSpriteCoordinates::IsFinitePoint(Avoid)) return false;
    const TArray<FVector>& Points = GetPrivateReachablePoints(SourceMapId);
    if (Points.IsEmpty()) return false;
    DigimonMapRuntime::FPrivateMapGeometry Geometry;
    if (!DigimonMapRuntime::MakePrivateMapGeometry(GetWorld(), SourceMapId, Geometry)) return false;
    const FVector SpriteLocal = Geometry.Mapping.ImageToLocal(FVector2D(
        FMath::Clamp(DesiredUV.X, 0.0, 1.0) * Geometry.Mapping.ImageSize.X,
        FMath::Clamp(DesiredUV.Y, 0.0, 1.0) * Geometry.Mapping.ImageSize.Y));
    const FVector Target = Geometry.SpriteTransform.TransformPosition(SpriteLocal);
    // Keep the author's exact feet/portal coordinate when it connects to the
    // spawn component. The sampled lattice is a fallback, not a visual grid.
    bool bSeparated = true;
    for (const FVector& Avoid : AvoidPoints)
        if (FVector::DistSquared2D(Target, Avoid) < FMath::Square(80.0)) { bSeparated = false; break; }
    if (bSeparated && DigimonMapRuntime::IsPrivateSegmentWalkable(Geometry, Target, Target))
        for (const FVector& Point : Points)
            if (FVector::DistSquared2D(Point, Target) <= FMath::Square(300.0) &&
                DigimonMapRuntime::IsPrivateSegmentWalkable(Geometry, Point, Target))
            { OutLocal = Target; OutLocal.Z = 100; return true; }
    double Best = TNumericLimits<double>::Max();
    for (const FVector& Point : Points)
    {
        double Score = FVector::DistSquared2D(Point, Target);
        for (const FVector& Avoid : AvoidPoints)
        {
            const double Separation = FVector::Dist2D(Point, Avoid);
            if (Separation < 400.0) Score += FMath::Square(400.0 - Separation) * 1000.0;
        }
        if (Score < Best) { Best = Score; OutLocal = Point; }
    }
    return true;
}
