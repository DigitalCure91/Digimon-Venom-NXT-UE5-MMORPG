#include "DigimonVenomNXTRelayScene.h"
#include "DigimonVenomNXTRelay.h"
#include "DigimonVenomNXTCampaign.h"
#include "DigimonVenomNXTGhostLine.h"
#include "DigimonVenomNXTSpriteCoordinates.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "Engine/GameInstance.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTFieldSprite.h"
#include "DigimonVenomNXTFieldSizingCore.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/World.h"

namespace DigimonCampaignVisuals
{
    static bool FailScene(int32 SourceMapId, const TCHAR* Code, const FString& Detail, FString* OutError)
    {
        if (OutError) *OutError = FString::Printf(TEXT("Campaign habitat %03d: %s [%s]. Your saved progress is safe."), SourceMapId, *Detail, Code);
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT campaign scene [%s] source map %03d: %s"), Code, SourceMapId, *Detail);
        return false;
    }

    static bool GroundGuardian(UPaperFlipbookComponent* Visual, FName Species, const FVector& Contact, FString* OutError = nullptr)
    {
        if (OutError) OutError->Reset();
        if (!Visual || !Visual->GetFlipbook())
        {
            if (OutError) *OutError = FString::Printf(TEXT("Guardian %s has no animation flipbook"), *Species.ToString());
            return false;
        }
        UPaperSprite* Frame = Visual->GetFlipbook()->GetSpriteAtTime(Visual->GetPlaybackPosition(), true);
        if (!Frame)
        {
            if (OutError) *OutError = FString::Printf(TEXT("Guardian %s has no sprite at time %.3f in %s"),
                *Species.ToString(), static_cast<double>(Visual->GetPlaybackPosition()), *Visual->GetFlipbook()->GetPathName());
            return false;
        }
        const FVector2D FrameSize = DigimonVenomNXTSpriteCoordinates::GetImageSize(Frame);
        if (FrameSize.X <= 0.0 || FrameSize.Y <= 0.0)
        {
            if (OutError) *OutError = FString::Printf(TEXT("Guardian %s has invalid cooked sprite coordinates in %s"),
                *Species.ToString(), *Frame->GetPathName());
            return false;
        }
        // The importer places each source frame's actual foot at its local
        // origin, including padded rare forms. Canvas bottom is not the foot
        // when the original frame contains an aura below the character.
        FVector Location = Contact;
        Location.Z = Visual->GetComponentLocation().Z; // Depth sorting owns only the visual plane height.
        Visual->SetWorldLocation(Location);
        return true;
    }
}

TSharedRef<SWidget> UDigimonVenomNXTRelayWorldLabel::RebuildWidget()
{
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("RelayLabelTree"));
    LabelText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Label"));
    WidgetTree->RootWidget = LabelText;
    LabelText->SetJustification(ETextJustify::Center);
    FSlateFontInfo Font = LabelText->GetFont();
    Font.Size = 14;
    LabelText->SetFont(Font);
    LabelText->SetShadowColorAndOpacity(FLinearColor(0,0,0,1));
    LabelText->SetShadowOffset(FVector2D(1,2));
    SetLabel(PendingLabel, PendingColor);
    return Super::RebuildWidget();
}
void UDigimonVenomNXTRelayWorldLabel::SetLabel(const FString& Label, const FLinearColor& Color)
{
    PendingLabel = Label;
    PendingColor = Color;
    if (LabelText) { LabelText->SetText(FText::FromString(Label)); LabelText->SetColorAndOpacity(Color); }
}
ADigimonVenomNXTRelayScene::ADigimonVenomNXTRelayScene()
{
    bReplicates = false;
    PrimaryActorTick.bCanEverTick = true;
    SetActorEnableCollision(false);
    SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
}
void ADigimonVenomNXTRelayScene::AddLabel(const FVector& WorldLocation, const FString& Text, const FLinearColor& Color)
{
    UWidgetComponent* Component = NewObject<UWidgetComponent>(this);
    Component->SetupAttachment(GetRootComponent());
    Component->SetWidgetSpace(EWidgetSpace::Screen);
    Component->SetDrawAtDesiredSize(true);
    Component->SetPivot(FVector2D(.5f, 1.8f));
    Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Component->SetRenderCustomDepth(true);
    Component->SetOwnerPlayer(CampaignOwner->GetLocalPlayer());
    Component->RegisterComponent();
    Component->SetWorldLocation(WorldLocation + FVector(0,0,160));
    UDigimonVenomNXTRelayWorldLabel* Widget = CreateWidget<UDigimonVenomNXTRelayWorldLabel>(CampaignOwner.Get(), UDigimonVenomNXTRelayWorldLabel::StaticClass());
    Widget->SetLabel(Text, Color);
    Component->SetWidget(Widget);
    Labels.Add(Component);
}
bool ADigimonVenomNXTRelayScene::InitializeFor(ADigimonVenomNXTPlayerController* Controller, FString* OutError)
{
    if (OutError) OutError->Reset();
    CampaignOwner = Controller;
    const FDigimonRelayMap* Map = Controller ? DigimonVenomNXTCampaign::GetMap(Controller->GetStoryCampaign(), Controller->GetRelayMapId()) : nullptr;
    if (!Map || !Controller || !Controller->IsLocalController() || !GetWorld())
        return DigimonCampaignVisuals::FailScene(Map ? Map->SourceMapId : INDEX_NONE, TEXT("SCENE_CONTEXT"),
            TEXT("The local campaign controller, map definition or world is unavailable"), OutError);
    if (!Controller->GetPlayerState<ADigimonVenomNXTPlayerState>())
        return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_PLAYER_STATE"),
            TEXT("The owning player's state has not arrived on this client"), OutError);
    SetActorLocation(Controller->GetRelayOrigin());
    FActorSpawnParameters Params;
    Params.Owner = Controller;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    Ground = GetWorld()->SpawnActor<ADigimonVenomNXTLocalMapRenderer>(ADigimonVenomNXTLocalMapRenderer::StaticClass(), GetActorLocation(), FRotator::ZeroRotator, Params);
    if (!Ground)
        return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GROUND_SPAWN"),
            TEXT("The local ground renderer could not be created"), OutError);
    if (!Ground->ShowMap(Map->SourceMapId, GetActorLocation()))
        return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GROUND_CONTENT"),
            FString::Printf(TEXT("The ground sprite could not be rendered: /DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d.SP_PlayMap_%03d"),
                Map->SourceMapId, Map->SourceMapId), OutError);
    return RebuildCast(OutError);
}

FString ADigimonVenomNXTRelayScene::CastSignature() const
{
    const ADigimonVenomNXTPlayerState* PS = CampaignOwner ? CampaignOwner->GetPlayerState<ADigimonVenomNXTPlayerState>() : nullptr;
    if (!PS) return FString();
    const auto Campaign = CampaignOwner->GetStoryCampaign();
    const auto& Progress = DigimonVenomNXTCampaign::Progress(PS->Profile, Campaign);
    FString Signature = FString::Printf(TEXT("%d:%d:%d:%d:%d:%d:%d:%d"), static_cast<int32>(Campaign), CampaignOwner->GetRelayMapId(),
        Progress.bComplete, Progress.bEverChampion, Progress.bIsChampion, Progress.ChallengerIndex, Progress.AcceptedQuests.Num(), Progress.CompletedObjectives.Num());
    for (const auto& NPC : DigimonVenomNXTCampaign::NPCsForMap(Campaign, CampaignOwner->GetRelayMapId()))
        Signature += FString::Printf(TEXT("|%s:%d:%d"), *NPC.Id.ToString(), DigimonVenomNXTCampaign::IsNPCVisible(Campaign, Progress, NPC), Progress.DefeatedTamers.Contains(NPC.Id));
    Signature += FString::Printf(TEXT("|portals:%d:%d"), CampaignOwner->GetRelayPortalTarget(false), CampaignOwner->GetRelayPortalTarget(true));
    return Signature;
}

bool ADigimonVenomNXTRelayScene::RebuildCast(FString* OutError)
{
    if (OutError) OutError->Reset();
    ADigimonVenomNXTPlayerController* Controller = CampaignOwner.Get();
    const FDigimonRelayMap* Map = Controller ? DigimonVenomNXTCampaign::GetMap(Controller->GetStoryCampaign(), Controller->GetRelayMapId()) : nullptr;
    if (!Map || !Controller)
        return DigimonCampaignVisuals::FailScene(INDEX_NONE, TEXT("SCENE_CONTEXT"),
            TEXT("The campaign controller or map definition is unavailable"), OutError);
    if (!Controller->GetPlayerState<ADigimonVenomNXTPlayerState>())
        return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_PLAYER_STATE"),
            TEXT("The owning player's state has not arrived on this client"), OutError);
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    FDigimonMapRow SourceMap;
    const double WorldPerPixel = Data && Data->GetMap(Map->SourceMapId, SourceMap) && SourceMap.SourceWidth > 0
        ? GetDefault<UDigimonVenomNXTSettings>()->MapWorldWidth / SourceMap.SourceWidth : 1.;
    // Destroy retired contacts and their labels together. The ground and collision remain intact.
    for (UPaperFlipbookComponent* Sprite : Tamers) if (Sprite) Sprite->DestroyComponent();
    for (UWidgetComponent* Label : Labels) if (Label) Label->DestroyComponent();
    Tamers.Reset(); Labels.Reset(); GuardianVisuals.Reset();
    for (const FDigimonRelayNPC& NPC : DigimonVenomNXTCampaign::NPCsForMap(Controller->GetStoryCampaign(), Map->MapId))
    {
        const ADigimonVenomNXTPlayerState* PS = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (!PS || !DigimonVenomNXTCampaign::IsNPCVisible(Controller->GetStoryCampaign(), DigimonVenomNXTCampaign::Progress(PS->Profile, Controller->GetStoryCampaign()), NPC)) continue;
        const FVector Location = Controller->GetRelayNPCLocation(NPC.Id);
        if (Location.IsNearlyZero()) continue;
        const bool bParadoxBoss = Controller->IsInChronicles() && (NPC.Role == EDigimonRelayRole::ParadoxBoss || NPC.Role == EDigimonRelayRole::FinalBoss);
        const int32 VisualCount = bParadoxBoss ? NPC.TeamSpecies.Num() : 1;
        if (VisualCount < 1)
            return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GUARDIAN_TEAM"),
                FString::Printf(TEXT("Guardian encounter %s has no team species"), *NPC.Id.ToString()), OutError);
        for (int32 VisualIndex = 0; VisualIndex < VisualCount; ++VisualIndex)
        {
            UPaperFlipbookComponent* Sprite = NewObject<UPaperFlipbookComponent>(this);
            Sprite->SetupAttachment(GetRootComponent());
            Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Sprite->SetRenderCustomDepth(true);
            Sprite->RegisterComponent();
            Tamers.Add(Sprite);
            // A final trio shares one authoritative interaction point; its flanking art is local only.
            const float OffsetX = (VisualIndex - (VisualCount - 1) * .5f) * 68.0f * WorldPerPixel;
            Sprite->SetWorldLocation(Location + FVector(OffsetX, 0, -80));
            Sprite->SetWorldRotation(FRotator(0,0,90));
            if (bParadoxBoss)
            {
                const FString Species = NPC.TeamSpecies[VisualIndex].ToString();
                const FString AssetName = FString::Printf(TEXT("DA_%s_Paradox_Animation"), *Species);
                const FString Path = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Digimon/Paradox/%s/%s.%s"), *Species, *AssetName, *AssetName);
                UDigimonVenomNXTPartnerAnimationSet* Animation = LoadObject<UDigimonVenomNXTPartnerAnimationSet>(nullptr, *Path);
                if (!Animation)
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GUARDIAN_ASSET"),
                        FString::Printf(TEXT("Guardian %s is missing animation asset %s"), *NPC.Id.ToString(), *Path), OutError);
                if (!Animation->Idle)
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GUARDIAN_POSE"),
                        FString::Printf(TEXT("Guardian %s has no Idle flipbook in %s"), *NPC.Id.ToString(), *Path), OutError);
                Sprite->SetFlipbook(Animation->Idle.Get());
                const FVector2D Body = Animation->NativeBodySize;
                const double Scale = DigimonVenomNXTFieldSizingCore::Partner(Body.X, Body.Y, WorldPerPixel,
                    GetDefault<UDigimonVenomNXTSettings>()->FollowerFieldSpriteScale);
                Sprite->SetWorldScale3D(FVector(-Scale, Scale, Scale));
                // The scene advances the pose and its foot registration together;
                // component tick order must not leave one frame at the old origin.
                Sprite->Stop();
                Sprite->SetPlaybackPosition(0.0f, false);
                const FVector GroundContact = Location + FVector(OffsetX, 0, 0);
                FString AnchorError;
                if (!DigimonCampaignVisuals::GroundGuardian(Sprite, NPC.TeamSpecies[VisualIndex], GroundContact, &AnchorError))
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_GUARDIAN_ANCHOR"), AnchorError, OutError);
                FGuardianVisual Registration;
                Registration.Sprite = Sprite;
                Registration.Animation = Animation;
                Registration.WorldPerPixel = WorldPerPixel;
                Registration.Species = NPC.TeamSpecies[VisualIndex];
                Registration.GroundContact = GroundContact;
                GuardianVisuals.Add(Registration);
            }
            else
            {
                const FString Path = DigimonVenomNXTTamers::AnimationPath(NPC.TamerStyleId);
                if (Path.IsEmpty())
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_TAMER_STYLE"),
                        FString::Printf(TEXT("Contact %s has an unknown tamer style %s"), *NPC.Id.ToString(), *NPC.TamerStyleId.ToString()), OutError);
                UDigimonVenomNXTTamerAnimationSet* Animation = LoadObject<UDigimonVenomNXTTamerAnimationSet>(nullptr, *Path);
                if (!Animation)
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_TAMER_ASSET"),
                        FString::Printf(TEXT("Contact %s is missing tamer animation asset %s"), *NPC.Id.ToString(), *Path), OutError);
                if (!Animation->Down)
                    return DigimonCampaignVisuals::FailScene(Map->SourceMapId, TEXT("SCENE_TAMER_POSE"),
                        FString::Printf(TEXT("Contact %s has no Down flipbook in %s"), *NPC.Id.ToString(), *Path), OutError);
                const FVector2D Body = Animation->NativeBodySize;
                const double Scale = DigimonVenomNXTFieldSizingCore::Tamer(Body.X, Body.Y, Animation->DisplayScale, WorldPerPixel,
                    GetDefault<UDigimonVenomNXTSettings>()->TamerFieldSpriteScale);
                Sprite->SetWorldScale3D(FVector(-Scale, Scale, Scale));
                Sprite->SetFlipbook(Animation->GetForFacing(EDigimonFacing::Down));
                Sprite->Stop();
                Sprite->SetPlaybackPositionInFrames(0, false);
            }
            DigimonVenomNXTFieldSprite::Configure(Sprite);
        }
        const bool bBattle = DigimonVenomNXTCampaign::IsBattleRole(NPC.Role);
        const auto& Progress = DigimonVenomNXTCampaign::Progress(PS->Profile, Controller->GetStoryCampaign());
        const bool bCleared = NPC.Role == EDigimonRelayRole::Quest ? Progress.CompletedObjectives.Contains(NPC.QuestId) : Progress.DefeatedTamers.Contains(NPC.Id);
        const FString NPCRoleLabel = !NPC.RoleLabel.IsEmpty() ? NPC.RoleLabel : Controller->IsInGhostLine() ? DigimonVenomNXTGhostLine::RoleLabel(NPC) : NPC.Role == EDigimonRelayRole::FinalBoss ? TEXT("FINAL CONVERGENCE | 3 x LV 100") :
            NPC.Role == EDigimonRelayRole::ParadoxBoss ? FString::Printf(TEXT("PARADOX GUARDIAN | LV %d"), NPC.Level) :
            NPC.Role == EDigimonRelayRole::Quest ? TEXT("CHRONICLES ASSIGNMENT") :
            NPC.Role == EDigimonRelayRole::Gym ? TEXT("DIGIBADGE WARDEN") : NPC.Role == EDigimonRelayRole::Champion ? TEXT("CHAMPION") :
            NPC.Role == EDigimonRelayRole::Challenger ? TEXT("CHALLENGER") : NPC.Role == EDigimonRelayRole::Healer ? TEXT("DIGILAB CARE") :
            NPC.Role == EDigimonRelayRole::Shop ? TEXT("SHOP") : bBattle ? TEXT("TAMER") : TEXT("STORY");
        const FString StateLabel = bCleared ? TEXT("\nCleared | Approach + E") : TEXT("\nApproach + E");
        const FLinearColor LabelColor = bCleared ? FLinearColor(.5f,.95f,.7f,1) : bParadoxBoss ? FLinearColor(.85f,.65f,1,1) : bBattle ? FLinearColor(1,.76f,.28f,1) : FLinearColor(.45f,.95f,1,1);
        AddLabel(Location, NPCRoleLabel + TEXT("\n") + NPC.Name + StateLabel, LabelColor);
    }
    if (Controller->GetRelayPortalTarget(false) != INDEX_NONE) AddLabel(Controller->GetRelayPortalLocation(false), TEXT("PREVIOUS MAP\nApproach + E"), FLinearColor(.55f,.8f,1,1));
    const int32 Forward = Controller->GetRelayPortalTarget(true);
    if (Forward != INDEX_NONE) AddLabel(Controller->GetRelayPortalLocation(true), Forward == 1 ? TEXT("BACKCHANNEL UPLINK\nApproach + E") : TEXT("NEXT MAP\nApproach + E"), FLinearColor(.4f,1,.76f,1));
    PresentedCastSignature = CastSignature();
    return true;
}
void ADigimonVenomNXTRelayScene::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CastRefreshAccumulator += FMath::Max(0.0f, DeltaSeconds);
    if (CastRefreshAccumulator >= .2f)
    {
        CastRefreshAccumulator = 0.0f;
        if (PresentedCastSignature != CastSignature()) RebuildCast();
    }
    // Both idle poses retain their original registration. Correcting each pose
    // prevents visible feet drifting away from the interaction point as it animates.
    for (FGuardianVisual& Guardian : GuardianVisuals)
    {
        UPaperFlipbookComponent* Visual = Guardian.Sprite.Get();
        if (!Visual || !Visual->GetFlipbook()) continue;
        const float Duration = Visual->GetFlipbook()->GetTotalDuration();
        if (Duration > SMALL_NUMBER)
        {
            Guardian.PlaybackTime = FMath::Fmod(Guardian.PlaybackTime + FMath::Max(0.0f, DeltaSeconds), Duration);
            Visual->SetPlaybackPosition(Guardian.PlaybackTime, false);
        }
        if (UDigimonVenomNXTPartnerAnimationSet* Animation = Guardian.Animation.Get())
        {
            const FVector2D Body = Animation->GetBodySizeForFrame(Visual->GetFlipbook()->GetSpriteAtTime(Visual->GetPlaybackPosition(), true));
            const double Scale = DigimonVenomNXTFieldSizingCore::Partner(Body.X, Body.Y, Guardian.WorldPerPixel,
                GetDefault<UDigimonVenomNXTSettings>()->FollowerFieldSpriteScale);
            Visual->SetWorldScale3D(FVector(-Scale, Scale, Scale));
        }
        DigimonCampaignVisuals::GroundGuardian(Visual, Guardian.Species, Guardian.GroundContact);
    }
    for (UPaperFlipbookComponent* Tamer : Tamers) DigimonVenomNXTFieldSprite::UpdateDepth(Tamer);
    const bool bLabelsVisible = CampaignOwner && !CampaignOwner->CurrentBattle && !CampaignOwner->IsFieldMenuOpen();
    for (UWidgetComponent* Label : Labels) if (Label) Label->SetVisibility(bLabelsVisible);
}
void ADigimonVenomNXTRelayScene::EndPlay(const EEndPlayReason::Type Reason)
{
    if (IsValid(Ground)) Ground->Destroy();
    Super::EndPlay(Reason);
}
