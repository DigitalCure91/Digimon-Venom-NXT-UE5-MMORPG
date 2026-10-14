#include "DigimonVenomNXTEditorCustomDepth.h"
#include "DigimonVenomNXTCustomDepth.h"
#include "Components/PrimitiveComponent.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "HAL/FileManager.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "MaterialShared.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "UObject/Package.h"

void DigimonVenomNXTEditorCustomDepth::PrepareWorldMaterials(UWorld* World,
    TArray<UMaterial*>& OutChanged, TArray<FString>& OutWarnings)
{
    OutChanged.Reset();
    OutWarnings.Reset();
    if (!World) return;
    TSet<UMaterial*> Visited;
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        if (It->IsEditorOnly()) continue;
        TInlineComponentArray<UPrimitiveComponent*> Components;
        It->GetComponents(Components);
        for (UPrimitiveComponent* Component : Components)
        {
            if (!DigimonVenomNXTCustomDepth::IsWorldVisual(Component)) continue;
            TArray<UMaterialInterface*> Materials;
            Component->GetUsedMaterials(Materials, false);
            for (UMaterialInterface* Assigned : Materials)
            {
                if (!Assigned || !IsTranslucentBlendMode(Assigned->GetBlendMode())) continue;
                UMaterial* Base = Assigned->GetBaseMaterial();
                if (!Base || Visited.Contains(Base) || Base->AllowTranslucentCustomDepthWrites) continue;
                Visited.Add(Base);
                const FString PackageName = Base->GetOutermost()->GetName();
                FString Filename;
                if (Base->HasAnyFlags(RF_Transient) || !FPackageName::TryConvertLongPackageNameToFilename(
                    PackageName, Filename, FPackageName::GetAssetPackageExtension()))
                {
                    OutWarnings.Add(FString::Printf(TEXT("Transient material %s on %s needs a saved base with Allow Custom Depth Writes enabled."),
                        *Base->GetPathName(), *Component->GetPathName()));
                    continue;
                }
                Filename = FPaths::ConvertRelativePathToFull(Filename);
                const FString EngineDirectory = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
                if (PackageName.StartsWith(TEXT("/Engine/")) || FPaths::IsUnderDirectory(Filename, EngineDirectory) ||
                    IFileManager::Get().IsReadOnly(*Filename))
                {
                    OutWarnings.Add(FString::Printf(TEXT("Material %s on %s is engine-owned or read-only. Use an editable project copy with Allow Custom Depth Writes enabled."),
                        *Base->GetPathName(), *Component->GetPathName()));
                    continue;
                }
                // Compile the depth permutation on the actual assigned base. No material
                // graph, blend mode, instance parameters or unrelated assets are changed.
                Base->Modify();
                Base->AllowTranslucentCustomDepthWrites = true;
                Base->PostEditChange();
                Base->MarkPackageDirty();
                OutChanged.Add(Base);
            }
        }
    }
}
