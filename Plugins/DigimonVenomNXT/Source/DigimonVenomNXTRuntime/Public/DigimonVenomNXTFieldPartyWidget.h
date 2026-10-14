#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTFieldPartyWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UProgressBar;
class UTextBlock;
class UVerticalBox;

/** Field buttons never consume movement focus after a click. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFieldActionButton : public UDigimonVenomNXTActionButton
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTFieldActionButton(const FObjectInitializer& ObjectInitializer);
};

/** A fixed slot, retained across owner-profile replication and party reordering. */
USTRUCT()
struct FDigimonFieldPartyCard
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Frame;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HP;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SP;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HPBar;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> SPBar;
    FName DisplayedSpecies;
    EDigimonVariant DisplayedVariant = EDigimonVariant::Normal;
};

/** Six lightweight field cards. The parent owns visibility; no travel or gameplay writes. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTFieldPartyWidget : public UUserWidget
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
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Summary;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> LabShortcut;
    UPROPERTY(Transient) TArray<FDigimonFieldPartyCard> Cards;
};
