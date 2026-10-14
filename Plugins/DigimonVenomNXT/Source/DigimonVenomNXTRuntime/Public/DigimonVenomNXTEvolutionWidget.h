#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTEvolutionWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UProgressBar;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;

/** Retained widgets are updated in place: a profile replication never restarts a portrait. */
USTRUCT()
struct FDigimonEvolutionPartnerTile
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Button;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Detail;
};

USTRUCT()
struct FDigimonEvolutionRouteView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Stage;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> RequirementLabels;
    UPROPERTY(Transient) TArray<TObjectPtr<UProgressBar>> RequirementBars;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> AdditionalRequirements;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Outcome;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Transform;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TransformLabel;
};

/** Collection, evolution planning and scan browsing, all keyed by stable partner GUIDs. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTEvolutionWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* PlayerState, UDigimonVenomNXTDataSubsystem* Data);
    void SelectPartner(const FGuid& PartnerId);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    void BuildLayout();
    void RefreshRoster();
    void RefreshPartner();
    void RefreshRoutes();
    void RefreshScans();
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Color);
    FGuid SelectedPartnerId;
    int32 RosterPage = 0;
    int32 ScanPage = 0;
    int32 ActiveTab = 0;
    TArray<FName> VisibleRouteIds;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> PlayerState;
    TWeakObjectPtr<UDigimonVenomNXTDataSubsystem> Data;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> PartnerSection;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> ScanSection;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Summary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RosterPageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RosterPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RosterNext;
    UPROPERTY(Transient) TArray<FDigimonEvolutionPartnerTile> RosterTiles;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    UPROPERTY(Transient) TObjectPtr<UBorder> Hero;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> HeroPortrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroStage;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroAffinity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroElement;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroStats;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroExperience;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroNextLevel;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HeroXP;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroTraining;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HeroCAM;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> HeroABI;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroCAMText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeroABIText;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PartyButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> LeaderButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> CAMButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ABIButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CAMButtonLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ABIButtonLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RouteIntro;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RouteEmpty;
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> RouteGrid;
    UPROPERTY(Transient) TArray<FDigimonEvolutionRouteView> RouteViews;
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> ScanGrid;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ScanPageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ScanPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ScanNext;
    uint32 ScanSignature = 0;
    bool bHasScanSignature = false;
};
