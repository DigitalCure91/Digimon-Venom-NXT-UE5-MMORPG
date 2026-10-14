#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTPartyWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UProgressBar;
class UTextBlock;
class UVerticalBox;

/** Retained cards keep idle animation and keyboard focus intact during profile replication. */
USTRUCT()
struct FDigimonPartyCardView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Role;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Identity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Affinity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Element;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Health;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SkillPoints;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Stats;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Growth;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Experience;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> NextLevel;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HPBar;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> SPBar;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> XPBar;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Leader;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> MoveEarlier;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> MoveLater;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Inspect;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Remove;
};

/** Live, owner-profile presentation. All party changes still use the guarded server RPC. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTPartyWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    void BuildLayout();
    void AddPartnerCard();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Color);
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Cards;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Summary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Formation;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyMessage;
    UPROPERTY(Transient) TArray<FDigimonPartyCardView> PartnerCards;
};
