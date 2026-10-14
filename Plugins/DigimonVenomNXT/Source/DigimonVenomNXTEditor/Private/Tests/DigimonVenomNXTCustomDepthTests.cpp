#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTCustomDepth.h"
#include "DigimonVenomNXTCustomDepthSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "HAL/IConsoleManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Particles/ParticleSystemComponent.h"

namespace DigimonVenomNXTCustomDepthTests
{
    template<typename T> T* AddPrimitive(AActor* Owner)
    {
        T* Component = NewObject<T>(Owner);
        Owner->AddInstanceComponent(Component);
        Component->RegisterComponent();
        return Component;
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTCustomDepthWorldTest,
    "DigimonVenomNXT.Editor.Rendering.CustomDepthWorldCoverage",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTCustomDepthWorldTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    using namespace DigimonVenomNXTCustomDepthTests;
    // An isolated transient world never replaces or modifies the user's open map.
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    if (!TestNotNull(TEXT("Isolated test world"), World)) return false;
    ON_SCOPE_EXIT { World->DestroyWorld(false); };
    UDigimonVenomNXTCustomDepthSubsystem* System = World->GetSubsystem<UDigimonVenomNXTCustomDepthSubsystem>();
    if (!TestNotNull(TEXT("Automatic world rendering subsystem"), System)) return false;
    AActor* Owner = World->SpawnActor<AActor>();
    if (!TestNotNull(TEXT("World fixture actor"), Owner)) return false;
    UStaticMeshComponent* Mesh = AddPrimitive<UStaticMeshComponent>(Owner);
    USkeletalMeshComponent* Skeletal = AddPrimitive<USkeletalMeshComponent>(Owner);
    UInstancedStaticMeshComponent* Instances = AddPrimitive<UInstancedStaticMeshComponent>(Owner);
    UPaperSpriteComponent* Ground = AddPrimitive<UPaperSpriteComponent>(Owner);
    UPaperFlipbookComponent* Creature = AddPrimitive<UPaperFlipbookComponent>(Owner);
    UTextRenderComponent* WorldText = AddPrimitive<UTextRenderComponent>(Owner);
    UParticleSystemComponent* Effect = AddPrimitive<UParticleSystemComponent>(Owner);
    UBoxComponent* Collision = AddPrimitive<UBoxComponent>(Owner);
    UWidgetComponent* Nameplate = AddPrimitive<UWidgetComponent>(Owner);
    Nameplate->SetWidgetSpace(EWidgetSpace::Screen);
    UWidgetComponent* WorldWidget = AddPrimitive<UWidgetComponent>(Owner);
    WorldWidget->SetWidgetSpace(EWidgetSpace::World);
    TArray<UPrimitiveComponent*> Visuals{Mesh, Skeletal, Instances, Ground, Creature, WorldText, Effect, WorldWidget};
    for (UPrimitiveComponent* Visual : Visuals)
    {
        // Emulate a serialized old Blueprint override without notifying the renderer.
        Visual->bRenderCustomDepth = false;
        Visual->SetCustomDepthStencilValue(77);
    }
    Collision->bRenderCustomDepth = false;
    Nameplate->bRenderCustomDepth = false;
    Creature->SetVisibility(false);
    UDigimonVenomNXTSettings* Settings = GetMutableDefault<UDigimonVenomNXTSettings>();
    TGuardValue<bool> LegacySetting(Settings->bRenderCustomDepthByDefault, false);
    System->RefreshWorld();
    bool Passed = true;
    for (UPrimitiveComponent* Visual : Visuals)
    {
        Passed &= TestTrue(Visual->GetClass()->GetName() + TEXT(" participates despite legacy false setting"), Visual->bRenderCustomDepth != 0);
        Passed &= TestEqual(TEXT("Authored stencil preserved"), Visual->CustomDepthStencilValue, 77);
    }
    Passed &= TestFalse(TEXT("Hidden creature stays hidden"), Creature->IsVisible());
    Passed &= TestFalse(TEXT("Collision shapes are not drawn into depth"), Collision->bRenderCustomDepth != 0);
    Passed &= TestFalse(TEXT("Screen-space UMG nameplates remain UI"), Nameplate->bRenderCustomDepth != 0);

    AStaticMeshActor* Spawned = World->SpawnActor<AStaticMeshActor>();
    Passed &= TestNotNull(TEXT("Actor spawned after initial world scan"), Spawned);
    if (Spawned) Passed &= TestTrue(TEXT("Spawn event configures actor immediately"), Spawned->GetStaticMeshComponent()->bRenderCustomDepth != 0);

    // A component appended after spawning is picked up by the construction revisit,
    // and later additions by the bounded sweep, even with no material/visibility event.
    System->Tick(1.0f / 60.0f);
    UPaperSpriteComponent* LateSprite = AddPrimitive<UPaperSpriteComponent>(Owner);
    LateSprite->bRenderCustomDepth = false;
    for (int32 Tick = 0; Tick < 120; ++Tick) System->Tick(1.0f / 60.0f);
    Passed &= TestTrue(TEXT("Late registered component joins depth pass"), LateSprite->bRenderCustomDepth != 0);

    // Material/visibility/render-state changes cannot restore an old false flag.
    // Broadcasting the engine event also tests fixtures without an actual mesh proxy.
    Mesh->bRenderCustomDepth = false;
    UActorComponent::MarkRenderStateDirtyEvent.Broadcast(*Mesh);
    Passed &= TestTrue(TEXT("Render-state event repairs an old override before proxy rebuild"), Mesh->bRenderCustomDepth != 0);
    Passed &= TestEqual(TEXT("Render-state repair preserves stencil"), Mesh->CustomDepthStencilValue, 77);

    LateSprite->DestroyComponent();
    if (Spawned) Spawned->Destroy();
    for (int32 Tick = 0; Tick < 120; ++Tick) System->Tick(1.0f / 60.0f);
    IConsoleVariable* CustomDepth = IConsoleManager::Get().FindConsoleVariable(TEXT("r.CustomDepth"));
    Passed &= TestTrue(TEXT("Custom Depth with stencil support enabled"), CustomDepth && CustomDepth->GetInt() == 3);
    return Passed;
}

#endif // WITH_DEV_AUTOMATION_TESTS

#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTEditorCustomDepth.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Misc/Guid.h"
#include "UObject/Package.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTCustomDepthMaterialTest,
    "DigimonVenomNXT.Editor.Rendering.AssignedTranslucentDepthMaterials",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDigimonVenomNXTCustomDepthMaterialTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    if (!TestNotNull(TEXT("Isolated material fixture world"), World)) return false;
    ON_SCOPE_EXIT { World->DestroyWorld(false); };
    UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (!TestNotNull(TEXT("Engine cube for actual material-slot enumeration"), Cube)) return false;
    // Use an unsaved, uniquely named project package so the helper's real writable
    // asset path is exercised. Cleanup removes all save/standalone flags afterward.
    const FString PackagePath = TEXT("/Game/__DigimonVenomNXT_Automation__/Depth_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    UPackage* Package = CreatePackage(*PackagePath);
    UMaterial* Assigned = NewObject<UMaterial>(Package, TEXT("AssignedTranslucent"), RF_Public | RF_Standalone);
    UMaterial* Unrelated = NewObject<UMaterial>(Package, TEXT("UnrelatedTranslucent"), RF_Public | RF_Standalone);
    UMaterial* Opaque = NewObject<UMaterial>(Package, TEXT("AssignedOpaque"), RF_Public | RF_Standalone);
    ON_SCOPE_EXIT
    {
        for (UMaterial* Material : {Assigned, Unrelated, Opaque})
            Material->ClearFlags(RF_Public | RF_Standalone);
        Package->SetDirtyFlag(false);
    };
    Assigned->BlendMode = BLEND_Translucent;
    Unrelated->BlendMode = BLEND_Translucent;
    Opaque->BlendMode = BLEND_Opaque;
    Assigned->AllowTranslucentCustomDepthWrites = false;
    Unrelated->AllowTranslucentCustomDepthWrites = false;
    Opaque->AllowTranslucentCustomDepthWrites = false;
    AStaticMeshActor* TranslucentActor = World->SpawnActor<AStaticMeshActor>();
    AStaticMeshActor* OpaqueActor = World->SpawnActor<AStaticMeshActor>();
    if (!TestNotNull(TEXT("Translucent world actor"), TranslucentActor) ||
        !TestNotNull(TEXT("Opaque world actor"), OpaqueActor)) return false;
    TranslucentActor->GetStaticMeshComponent()->SetStaticMesh(Cube);
    TranslucentActor->GetStaticMeshComponent()->SetMaterial(0, Assigned);
    OpaqueActor->GetStaticMeshComponent()->SetStaticMesh(Cube);
    OpaqueActor->GetStaticMeshComponent()->SetMaterial(0, Opaque);
    TArray<UMaterial*> Changed;
    TArray<FString> Warnings;
    DigimonVenomNXTEditorCustomDepth::PrepareWorldMaterials(World, Changed, Warnings);
    bool Passed = TestTrue(TEXT("Assigned translucent base compiles Custom Depth permutation"), Assigned->AllowTranslucentCustomDepthWrites != 0);
    Passed &= TestFalse(TEXT("Unassigned material remains unchanged"), Unrelated->AllowTranslucentCustomDepthWrites != 0);
    Passed &= TestFalse(TEXT("Opaque base does not need a translucent permutation"), Opaque->AllowTranslucentCustomDepthWrites != 0);
    Passed &= TestTrue(TEXT("Only the actual assigned translucent base is returned for saving"), Changed.Num() == 1 && Changed.Contains(Assigned));
    Passed &= TestTrue(TEXT("Writable fixture has no material warnings"), Warnings.IsEmpty());
    Passed &= TestTrue(TEXT("Blend modes are preserved"), Assigned->BlendMode == BLEND_Translucent && Opaque->BlendMode == BLEND_Opaque);
    DigimonVenomNXTEditorCustomDepth::PrepareWorldMaterials(World, Changed, Warnings);
    Passed &= TestTrue(TEXT("Repeated repair is idempotent"), Changed.IsEmpty() && Warnings.IsEmpty());
    // The test does not call SaveAsset: it leaves no generated fixture files on disk.
    return Passed;
}

#endif // WITH_DEV_AUTOMATION_TESTS
