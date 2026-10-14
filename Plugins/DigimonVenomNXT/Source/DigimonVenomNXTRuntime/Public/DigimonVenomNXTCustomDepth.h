#pragma once

#include "CoreMinimal.h"

class AActor;
class UPrimitiveComponent;
class UWorld;

/** Cel-shading participation for rendered level assets. Does not change stencil IDs or visibility. */
namespace DigimonVenomNXTCustomDepth
{
    DIGIMONVENOMNXTRUNTIME_API bool IsWorldVisual(const UPrimitiveComponent* Component);
    DIGIMONVENOMNXTRUNTIME_API bool ConfigurePrimitive(UPrimitiveComponent* Component);
    DIGIMONVENOMNXTRUNTIME_API int32 ConfigureActor(AActor* Actor);
    DIGIMONVENOMNXTRUNTIME_API int32 ConfigureWorld(UWorld* World);
    DIGIMONVENOMNXTRUNTIME_API void EnsureRendererEnabled();
}
