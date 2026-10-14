#include "DigimonVenomNXTEditorMapPreview.h"
#include "DigimonVenomNXTEditorMapPreviewCore.h"
#include "DigimonVenomNXTWorld.h"
#include "Containers/Ticker.h"
#include "Editor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "LevelEditorViewport.h"
#include "UnrealClient.h"

namespace DigimonVenomNXTEditorMapPreview
{
    static FTSTicker::FDelegateHandle TickHandle;

    static bool Refresh(float)
    {
        if (!GEditor || IsRunningCommandlet() || GEditor->PlayWorld) return true;
        UWorld* World = GEditor->GetEditorWorldContext().World();
        if (!World || World->WorldType != EWorldType::Editor) return true;
        TArray<ADigimonVenomNXTMapZone*> Zones;
        for (TActorIterator<ADigimonVenomNXTMapZone> It(World); It; ++It) Zones.Add(*It);
        if (Zones.IsEmpty()) return true;

        TArray<FVector> Views;
        for (FLevelEditorViewportClient* Viewport : GEditor->GetLevelViewportClients())
            if (Viewport && Viewport->GetWorld() == World && Viewport->IsVisible())
                Views.Add(Viewport->GetViewLocation());
        // A newly opened level still gets its first habitat before a viewport
        // has rendered. Focus/select in the Outliner immediately changes this set.
        if (Views.IsEmpty()) Views.Add(FVector::ZeroVector);
        std::vector<DigimonVenomNXTEditorMapPreviewCore::Candidate> Candidates;
        Candidates.reserve(Zones.Num());
        for (int32 Index = 0; Index < Zones.Num(); ++Index)
        {
            const FVector Center = Zones[Index]->GetActorLocation();
            const FVector2D Half = Zones[Index]->GetPlayableHalfExtents();
            double Distance = TNumericLimits<double>::Max();
            for (const FVector& View : Views)
                Distance = FMath::Min(Distance, DigimonVenomNXTEditorMapPreviewCore::DistanceToMap(View.X, View.Y, Center.X, Center.Y, Half.X, Half.Y));
            Candidates.push_back({Index, Distance, Zones[Index]->IsSelected()});
        }
        const std::vector<int> Active = DigimonVenomNXTEditorMapPreviewCore::Choose(MoveTemp(Candidates));
        for (int32 Index = 0; Index < Zones.Num(); ++Index)
            Zones[Index]->SetEditorPreviewActive(std::find(Active.begin(), Active.end(), Index) != Active.end());
        return true;
    }

    void Startup()
    {
        if (!IsRunningCommandlet() && !TickHandle.IsValid())
            TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateStatic(&Refresh), .5f);
    }

    void FocusFirstMap()
    {
        if (!GEditor || IsRunningCommandlet() || GEditor->PlayWorld) return;
        UWorld* World = GEditor->GetEditorWorldContext().World();
        if (!World || World->WorldType != EWorldType::Editor) return;
        ADigimonVenomNXTMapZone* First = nullptr;
        for (TActorIterator<ADigimonVenomNXTMapZone> It(World); It; ++It)
            if (It->GetRuntimeMapId() == 1) { First = *It; break; }
        if (!First) return;
        FLevelEditorViewportClient* Target = nullptr;
        for (FLevelEditorViewportClient* Viewport : GEditor->GetLevelViewportClients())
            if (Viewport && Viewport->GetWorld() == World && Viewport->IsVisible())
            {
                if (!Target) Target = Viewport;
                if (Viewport->Viewport == GEditor->GetActiveViewport()) { Target = Viewport; break; }
            }
        if (!Target) return;
        First->SetEditorPreviewActive(true);
        const FVector2D Half = First->GetPlayableHalfExtents();
        const FIntPoint Size = Target->Viewport ? Target->Viewport->GetSizeXY() : FIntPoint(16, 9);
        const double Aspect = Size.X > 0 && Size.Y > 0 ? static_cast<double>(Size.X) / Size.Y : 16. / 9.;
        const double HalfFOV = FMath::DegreesToRadians(FMath::Clamp(static_cast<double>(Target->ViewFOV), 10., 170.)) * .5;
        const double Distance = FMath::Max(Half.X, Half.Y * Aspect) * 1.12 / FMath::Tan(HalfFOV);
        const FVector Center = First->GetActorLocation();
        Target->SetViewportType(LVT_Perspective);
        Target->SetGameView(false);
        Target->SetViewLocation(Center + FVector(0, 0, Distance + 140.));
        Target->SetViewRotation(FRotator(-90., 90., 0.));
        Target->SetLookAtLocation(Center, false);
        Target->Invalidate();
        Refresh(0.f);
    }

    void Shutdown()
    {
        if (TickHandle.IsValid()) FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
        TickHandle.Reset();
        if (GEditor)
            if (UWorld* World = GEditor->GetEditorWorldContext().World())
                for (TActorIterator<ADigimonVenomNXTMapZone> It(World); It; ++It) It->SetEditorPreviewActive(false);
    }
}
