#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystems/WorldSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTWorld.generated.h"

class UPaperSprite;
class UTexture2D;
class UPaperSpriteComponent;
class UBoxComponent;
class USceneComponent;
class UPostProcessComponent;
class UCurveFloat;
class AController;

/**
 * One walkable handheld-RPG-style habitat inside the shared PublicWorld.
 * The imported 2D map artwork is laid flat on XY, normalized to a consistent
 * world size. The registered source-resolution mask is the sole movement
 * boundary; old rectangular wall components are retained with collision disabled.
 */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTMapZone : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTMapZone();
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") TObjectPtr<USceneComponent> Root;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") TObjectPtr<UPaperSpriteComponent> GroundSprite;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") TObjectPtr<UBoxComponent> PlayBounds;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") TObjectPtr<USceneComponent> PlayerSpawn;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map|Collision") TObjectPtr<UBoxComponent> NorthWall;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map|Collision") TObjectPtr<UBoxComponent> SouthWall;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map|Collision") TObjectPtr<UBoxComponent> EastWall;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map|Collision") TObjectPtr<UBoxComponent> WestWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map", meta=(ClampMin="1", ClampMax="500")) int32 MapId = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map") FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map") EDigimonRegion Region = EDigimonRegion::RegionOne;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map", meta=(ClampMin="1", ClampMax="99")) int32 MinLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map", meta=(ClampMin="1", ClampMax="99")) int32 MaxLevel = 3;
    /** Compatibility-only transient reference; public zones never retain map textures. */
    UPROPERTY(Transient, BlueprintReadOnly, Category="Digimon Venom NXT|Map") TObjectPtr<UPaperSprite> MapSprite;
    /** Native image geometry retained for editor bounds without loading artwork. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") FIntPoint SourceImageSize = FIntPoint::ZeroValue;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Digimon Venom NXT|Map") FVector2D SafeSpawnUV = FVector2D(.5, .5);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Venom NXT|Map") TArray<FName> WildSpecies;

    /** Canonical map id recovered from the generated actor name/location when legacy serialized data is stale. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Map") int32 GetRuntimeMapId() const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Map") FVector GetPlayerSpawnLocation() const;
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Map") FVector2D GetPlayableHalfExtents() const;
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Map") void ApplyMapPresentation();

    /** Client-local visual isolation: only the local player's current habitat should render. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Map") void SetLocalPresentationActive(bool bActive);

#if WITH_EDITOR
    /** Transient artwork for the editor's nearby/selected zones; never saved or cooked into PublicWorld. */
    void SetEditorPreviewActive(bool bActive);
#endif

private:
#if WITH_EDITORONLY_DATA
    UPROPERTY(Transient, DuplicateTransient) TObjectPtr<UPaperSpriteComponent> EditorGroundPreview;
    UPROPERTY(Transient, DuplicateTransient) TObjectPtr<UPaperSpriteComponent> EditorForegroundPreview;
    int32 EditorPreviewMapId = INDEX_NONE;
#endif

};


/**
 * Client-local map renderer. PublicWorld keeps its server-side zone actors for
 * travel/bounds only; each local player renders exactly one selected habitat here.
 * This deliberately avoids relying on serialized per-zone GroundSprite state.
 */
UCLASS(NotBlueprintable, Transient)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTLocalMapRenderer : public AActor
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTLocalMapRenderer();

    /** Shows one current canonical habitat at the supplied zone center; rejects missing or incomplete content. */
    bool ShowMap(int32 InMapId, const FVector& ZoneCenter, UPaperSprite* LegacyFallbackSprite = nullptr);

    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Map") TObjectPtr<USceneComponent> Root;
    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Map") TObjectPtr<UPaperSpriteComponent> GroundSprite;

    UPROPERTY(VisibleAnywhere, Category="Digimon Venom NXT|Map") TObjectPtr<UPaperSpriteComponent> ForegroundSprite;

private:
    UPROPERTY(Transient) TObjectPtr<UPaperSprite> RuntimeFallbackSprite;
};

UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|World")
    bool TravelPlayerToMap(AController* Controller, int32 MapId, FString& OutError);

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|World")
    ADigimonVenomNXTMapZone* FindMapZone(int32 MapId) const;


    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|World")
    TArray<ADigimonVenomNXTMapZone*> GetAllMapZones() const;

    /** Collision-mask driven walkability query. Hidden collision data only; masks are never rendered. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|World|Collision")
    bool IsWorldLocationWalkable(int32 MapId, const FVector& WorldLocation) const;

    /** Continuous swept footprint; cannot skip thin walls between valid endpoints. */
    bool IsWorldSegmentWalkable(int32 MapId, const FVector& From, const FVector& To) const;

    /** Uses canonical sprite/collision content at a private origin, independent of public world streaming. */
    bool IsPrivateMapLocationWalkable(int32 SourceMapId, const FVector& Origin, const FVector& Location) const;
    bool IsPrivateMapSegmentWalkable(int32 SourceMapId, const FVector& Origin, const FVector& From, const FVector& To) const;
    /** Checks installed map content and reports the exact campaign entry failure. */
    bool ValidatePrivateMapContent(int32 SourceMapId, FString& OutError) const;
    /** All placement candidates belong to the registered safe spawn's connected walkable component. */
    bool ResolvePrivateMapPoint(int32 SourceMapId, const FVector2D& DesiredUV, FVector& OutLocal,
        const TArray<FVector>& AvoidPoints = TArray<FVector>()) const;
    bool GetPrivateMapSpawn(int32 SourceMapId, FVector& OutLocal) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Wild")
    EDigimonVariant RollWildVariant() const;
private:
    mutable TMap<int32, TArray<FVector>> PrivateReachablePoints;
    mutable double CachedPlacementRadius = -1.0;
    mutable double CachedPlacementWidth = -1.0;
    const TArray<FVector>& GetPrivateReachablePoints(int32 SourceMapId) const;
};
