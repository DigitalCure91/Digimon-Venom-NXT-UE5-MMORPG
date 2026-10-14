#pragma once

#include "CoreMinimal.h"

class UMaterial;
class UWorld;

namespace DigimonVenomNXTEditorCustomDepth
{
    /** Only materials assigned to world visuals are considered. Caller saves changed assets. */
    void PrepareWorldMaterials(UWorld* World, TArray<UMaterial*>& OutChanged, TArray<FString>& OutWarnings);
}
