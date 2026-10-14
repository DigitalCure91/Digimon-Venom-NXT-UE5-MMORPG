#pragma once

#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTFarmCore.h"
#include "DigimonVenomNXTFieldSizingCore.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSettings.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "HAL/PlatformTime.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"

namespace DigimonVenomNXTFieldSizing
{
    inline double FarmWorldPerPixel() { return DigimonVenomNXTFarmCore::WorldWidth / 1672.; }

    inline double MapWorldPerPixel(const UObject* Context, int32 MapId)
    {
        const UWorld* World = Context ? Context->GetWorld() : nullptr;
        const UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
        const UDigimonVenomNXTDataSubsystem* Data = GI ? GI->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
        const FDigimonMapRow* Row = Data ? Data->FindMap(MapId) : nullptr;
        return Row && Row->SourceWidth > 0
            ? GetDefault<UDigimonVenomNXTSettings>()->MapWorldWidth / Row->SourceWidth : 1.;
    }

    inline double PawnWorldPerPixel(const APawn* Pawn)
    {
        if (!Pawn) return 1.;
        if (const ADigimonVenomNXTPlayerController* PC = Cast<ADigimonVenomNXTPlayerController>(Pawn->GetController()))
        {
            if (PC->IsInDigiFarm()) return FarmWorldPerPixel();
            // This resolves private campaign source maps as well as the currently
            // presented public map, including transitions before profile sync.
            return MapWorldPerPixel(Pawn, PC->GetLocalMusicMapId());
        }
        const ADigimonVenomNXTPlayerState* State = Pawn->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!State) return MapWorldPerPixel(Pawn, 1);
        if (Pawn->HasAuthority() ? State->Profile.Farm.bInside : State->PublicSnapshot.bInDigiFarm)
            return FarmWorldPerPixel();
        return MapWorldPerPixel(Pawn, Pawn->HasAuthority() ? State->Profile.CurrentMapId : State->PublicSnapshot.MapId);
    }

    inline UPaperSprite* CurrentFrame(UPaperFlipbookComponent* Sprite)
    {
        return Sprite && Sprite->GetFlipbook()
            ? Sprite->GetFlipbook()->GetSpriteAtTime(Sprite->GetPlaybackPosition(), true) : nullptr;
    }

    inline void SetSourceClock(UPaperFlipbookComponent* Sprite, bool bAnimate = true)
    {
        if (!Sprite || !Sprite->GetFlipbook()) return;
        // Advance before fitting/mirroring so a later component tick cannot
        // present next frame's artwork with the previous frame's registration.
        Sprite->Stop();
        const double Duration = Sprite->GetFlipbook()->GetTotalDuration();
        const float Time = bAnimate && Duration > 0.
            ? static_cast<float>(FMath::Fmod(FPlatformTime::Seconds(), Duration)) : 0.f;
        Sprite->SetPlaybackPosition(Time, false);
    }

    inline void SetScale(UPaperFlipbookComponent* Sprite, double Scale, bool bMirror = false)
    {
        if (!Sprite || !FMath::IsFinite(Scale) || Scale <= 0.) return;
        // Negative X compensates the field camera/Paper2D handedness; positive
        // X is used only when the source client explicitly mirrors this frame.
        const FVector Desired(bMirror ? Scale : -Scale, Scale, Scale);
        if (!Sprite->GetRelativeScale3D().Equals(Desired, .00001)) Sprite->SetRelativeScale3D(Desired);
    }

    inline void ApplyTamer(UPaperFlipbookComponent* Sprite, const UDigimonVenomNXTTamerAnimationSet* Set, double WorldPerPixel)
    {
        if (!Sprite || !Set) return;
        SetScale(Sprite, DigimonVenomNXTFieldSizingCore::Tamer(Set->NativeBodySize.X, Set->NativeBodySize.Y,
            Set->DisplayScale, WorldPerPixel, GetDefault<UDigimonVenomNXTSettings>()->TamerFieldSpriteScale));
    }

    inline void ApplyPartner(UPaperFlipbookComponent* Sprite, const UDigimonVenomNXTPartnerAnimationSet* Set,
        double WorldPerPixel, bool bFacingLeft)
    {
        if (!Sprite || !Set) return;
        UPaperSprite* Frame = CurrentFrame(Sprite);
        const FVector2D Body = Set->GetBodySizeForFrame(Frame);
        const bool bMirror = bFacingLeft && Set->bHasAuthoredLeftFrames && Set->ShouldMirrorLeftFrame(Frame);
        SetScale(Sprite, DigimonVenomNXTFieldSizingCore::Partner(Body.X, Body.Y, WorldPerPixel,
            GetDefault<UDigimonVenomNXTSettings>()->FollowerFieldSpriteScale), bMirror);
    }
}
