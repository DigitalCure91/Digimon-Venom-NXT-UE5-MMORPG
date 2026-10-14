#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTBattleWidget.generated.h"

class ADigimonVenomNXTBattleActor;
class UBorder;
class UCanvasPanel;
class UHorizontalBox;
class UImage;
class UDigimonVenomNXTActionButton;
class UDigimonVenomNXTAnimatedPortrait;
class UOverlay;
class UProgressBar;
class UScrollBox;
class UTextBlock;
class UTexture2D;
class UVerticalBox;

/** Stable widget references: changing HP must never restart the partner's idle animation. */
USTRUCT()
struct FDigimonBattleSlotVisual
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Selection;
    UPROPERTY(Transient) TObjectPtr<UBorder> SpriteHost;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Detail;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Affinity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Element;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Marker;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HP;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> SP;
    FName SpeciesId;
    EDigimonVariant Variant = EDigimonVariant::Normal;
};

/** Shared battlefield for wild, story, tamer and automatic ranked matches.
 * Replicated combat remains authoritative; local snapshots only pace its presentation.
 */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTBattleWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    void SetBattle(ADigimonVenomNXTBattleActor* InBattle);
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Battle")
    ADigimonVenomNXTBattleActor* GetBattle() const { return Battle.Get(); }
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Battle")
    bool IsPresentationBusy() const { return bPresentationAnimating || PendingPresentationEvents.Num() > 0; }

protected:
    UFUNCTION() void HandleBattleStateChanged(const FDigimonBattleState& NewState);
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION(BlueprintImplementableEvent, Category="Digimon Venom NXT|Battle")
    void BP_OnBattleRefreshed(const FDigimonBattleState& NewState);

private:
    TWeakObjectPtr<ADigimonVenomNXTBattleActor> Battle;
    bool bBuilt = false;
    bool bHasDisplayState = false;
    bool bVisualOursAreOriginalB = false;
    bool bPresentationAnimating = false;
    bool bImpactApplied = false;
    bool bActionPositionsCached = false;
    int32 ActiveHPRecovery = 0;
    int32 ActiveSPRecovery = 0;
    FVector2D ActionStartCenter = FVector2D::ZeroVector;
    FVector2D ActionTargetCenter = FVector2D::ZeroVector;
    float PresentationAnimTime = 0.0f;
    int32 SeenPresentationSerial = 0;
    int32 SelectedTarget = 0;
    int32 SelectedActor = 0;
    int32 CommandTab = 0;
    bool bConfirmUnrankedSurrender = false;
    TSet<int32> SubmittedSlots;
    TArray<FString> BattleLog;

    UPROPERTY(Transient) FDigimonBattleState DisplayState;
    UPROPERTY(Transient) FDigimonBattleState LatestState;
    UPROPERTY(Transient) TArray<FDigimonBattlePresentationEvent> PendingPresentationEvents;
    UPROPERTY(Transient) FDigimonBattlePresentationEvent ActivePresentationEvent;
    UPROPERTY(Transient) TObjectPtr<UOverlay> PresentationOverlay;
    UPROPERTY(Transient) TObjectPtr<UCanvasPanel> ArenaCanvas;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> BattleTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> BattleSubtitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TurnText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EventText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> LogText;
    UPROPERTY(Transient) TObjectPtr<UScrollBox> LogScroll;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PartyCount;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> MatchupPreview;
    UPROPERTY(Transient) TObjectPtr<UHorizontalBox> CommandsBox;
    UPROPERTY(Transient) TObjectPtr<UBorder> ResultPanel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResultHeading;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResultSummary;
    UPROPERTY(Transient) TObjectPtr<UScrollBox> ResultScroll;
    UPROPERTY(Transient) TObjectPtr<UBorder> ActionTray;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> ActionTrayContent;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> PartyBox;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ImpactText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ImpactDetail;
    UPROPERTY(Transient) TObjectPtr<UImage> ImpactImage;
    UPROPERTY(Transient) TArray<TObjectPtr<UTexture2D>> ImpactFrames;
    UPROPERTY(Transient) TArray<FDigimonBattleSlotVisual> TeamAVisuals;
    UPROPERTY(Transient) TArray<FDigimonBattleSlotVisual> TeamBVisuals;
    UPROPERTY(Transient) TArray<FDigimonBattleSlotVisual> PartyVisuals;

    void BuildNativeUI();
    void Refresh();
    void RebuildTeam(const FDigimonBattleTeam& Team, bool bPlayerTeam, TArray<FDigimonBattleSlotVisual>& Visuals);
    void RefreshTeam(const FDigimonBattleTeam& Team, bool bPlayerTeam, TArray<FDigimonBattleSlotVisual>& Visuals);
    void RefreshParty(const FDigimonBattleTeam& Team);
    void RefreshCommands(const FDigimonBattleTeam& Ours);
    void QueuePresentationEvents(const FDigimonBattleState& NewState);
    void StartNextPresentationEvent();
    void ApplyPresentationImpact();
    void PlayPresentationCue(bool bImpact);
    void ResetPresentationTransforms();
    void AppendBattleLog(const FString& Text);
    void AdvanceSelectedActor();
    void SyncSubmittedSlots();
    bool IsAutomaticBattle() const;
    UBorder* ResolveVisualCard(int32 OriginalTeamIndex, int32 SlotIndex) const;
    int32 FindFirstLivingTarget(const FDigimonBattleTeam& Team) const;
    FString VariantLabel(EDigimonVariant Variant) const;
};
