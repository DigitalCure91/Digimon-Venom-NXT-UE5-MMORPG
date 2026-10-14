#include "DigimonVenomNXTCustomDepth.h"
#include "Components/PrimitiveComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/BrushComponent.h"
#include "Components/LineBatchComponent.h"
#include "GameFramework/Volume.h"
#include "Components/WidgetComponent.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "HAL/IConsoleManager.h"

bool DigimonVenomNXTCustomDepth::IsWorldVisual(const UPrimitiveComponent* Component)
{
    // World-space widgets are level surfaces too. Screen-space UMG has no scene
    // depth surface; collision/debug shapes must not become depth-only silhouettes.
    // Do not filter temporarily hidden visuals: prepare them before they are shown.
    if (!IsValid(Component) || Component->IsEditorOnly() || !Component->bRenderInMainPass ||
        Component->IsA<UShapeComponent>() || Component->IsA<ULineBatchComponent>()) return false;
    if (const UWidgetComponent* Widget = Cast<UWidgetComponent>(Component))
        if (Widget->GetWidgetSpace() == EWidgetSpace::Screen) return false;
    return !(Component->IsA<UBrushComponent>() && Component->GetOwner() && Component->GetOwner()->IsA<AVolume>());
}

bool DigimonVenomNXTCustomDepth::ConfigurePrimitive(UPrimitiveComponent* Component)
{
    if (!IsWorldVisual(Component) || Component->bRenderCustomDepth) return false;
    // Preserve authored stencil IDs, opacity, collision, shadows, sort order and visibility.
    Component->SetRenderCustomDepth(true);
    return true;
}

int32 DigimonVenomNXTCustomDepth::ConfigureActor(AActor* Actor)
{
    if (!IsValid(Actor) || Actor->IsEditorOnly()) return 0;
    TInlineComponentArray<UPrimitiveComponent*> Components;
    Actor->GetComponents(Components);
    int32 Changed = 0;
    for (UPrimitiveComponent* Component : Components)
        Changed += ConfigurePrimitive(Component) ? 1 : 0;
    return Changed;
}

int32 DigimonVenomNXTCustomDepth::ConfigureWorld(UWorld* World)
{
    if (!World) return 0;
    EnsureRendererEnabled();
    int32 Changed = 0;
    for (TActorIterator<AActor> It(World); It; ++It) Changed += ConfigureActor(*It);
    return Changed;
}

void DigimonVenomNXTCustomDepth::EnsureRendererEnabled()
{
    if (IConsoleVariable* CustomDepth = IConsoleManager::Get().FindConsoleVariable(TEXT("r.CustomDepth")))
    {
        if (CustomDepth->GetInt() != 3)
        {
            // Respect the existing CVar priority while changing its value. In particular,
            // old project .ini/console settings must not silently defeat the world policy.
            const EConsoleVariableFlags Priority = static_cast<EConsoleVariableFlags>(
                static_cast<uint32>(CustomDepth->GetFlags()) & static_cast<uint32>(ECVF_SetByMask));
            CustomDepth->Set(3, Priority);
        }
    }
}
