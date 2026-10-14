#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTHealingPresentationCore.h"
#include "DigimonVenomNXTHealingTypes.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTDigiLabWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UProgressBar;
class UTextBlock;
class UVerticalBox;

USTRUCT()
struct FDigimonDigiLabCardView
{
    GENERATED_BODY()
    FGuid InstanceId;
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Slot;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Identity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Health;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SkillPoints;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Restored;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HPBar;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> SPBar;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> Pluses;
};

/** Retained recovery dashboard. Animation follows confirmed receipts, never predicted healing. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTDigiLabWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|DigiLab") void RefreshFromProfile();
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleHealResult(const FDigimonHealReceipt& Receipt);
private:
    void BuildLayout();
    void BindPlayerState();
    void UpdatePresentation(FDigimonDigiLabCardView& Card);
    void UpdateControls();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Accent);
    ADigimonVenomNXTPlayerState* PlayerState() const;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> BoundPlayerState;
    TMap<FGuid, DigimonVenomNXTHealingPresentationCore::Track> HealingTracks;
    FGuid PendingRequest;
    FGuid LastReceipt;
    bool bPendingHeal = false;
    double PendingStartedAt = 0.0;
    float ProfilePollSeconds = 0.0f;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PartySummary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CollectionSummary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RecoveryStatus;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HealCaption;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResearchSummary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ResearchDetails;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> HealButton;
    UPROPERTY(Transient) TArray<FDigimonDigiLabCardView> PartyCards;
};
