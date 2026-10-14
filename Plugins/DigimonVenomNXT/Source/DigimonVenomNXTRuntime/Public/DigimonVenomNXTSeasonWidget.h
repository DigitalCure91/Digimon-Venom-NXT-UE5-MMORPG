#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTSeasonWidget.generated.h"

class ADigimonVenomNXTPlayerState;
class UDigimonVenomNXTDataSubsystem;
class UDigimonVenomNXTAnimatedPortrait;
class UBorder;
class UImage;
class UProgressBar;
class USizeBox;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;

USTRUCT()
struct FDigimonSeasonPartnerView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<USizeBox> Bounds;
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Stats;
};

USTRUCT()
struct FDigimonSeasonMatchView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Day;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Home;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Away;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Result;
};

USTRUCT()
struct FDigimonSeasonRosterView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> Button;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> Portrait;
    UPROPERTY(Transient) TObjectPtr<UImage> Tamer;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Rank;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Name;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Record;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Progress;
};

USTRUCT()
struct FDigimonSeasonRivalryView
{
    GENERATED_BODY()
    UPROPERTY(Transient) TObjectPtr<UBorder> Card;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Names;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Record;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> Heat;
};

/** Pure presentation of the owner's private, persisted season. Never resolves a booking or awards currency. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTSeasonWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    void ApplyArchivePage(const FDigimonSeasonArchivePage& Page);
    void RefreshFromProfile(ADigimonVenomNXTPlayerState* InPlayerState, UDigimonVenomNXTDataSubsystem* InData);
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
private:
    void BuildLayout();
    void RefreshWeek();
    void RefreshRoster();
    void RefreshRivalries();
    void RefreshChampionship();
    void RefreshArchive();
    void RefreshTeams(TArray<FDigimonSeasonPartnerView>& Views, const TArray<FDigimonOwnedPartner>& Team, bool bDetailed);
    void RefreshMatches(TArray<FDigimonSeasonMatchView>& Views, const TArray<FDigimonSeasonMatch>& Fixtures, const TArray<FDigimonSeasonTamer>* SavedStandings = nullptr);
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Accent);
    UVerticalBox* BuildTeam(UVerticalBox* Parent, TArray<FDigimonSeasonPartnerView>& Views, bool bDetailed);
    void BuildMatchCard(UVerticalBox* Parent, TArray<FDigimonSeasonMatchView>& Views);
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> PlayerState;
    TWeakObjectPtr<UDigimonVenomNXTDataSubsystem> Data;
    int32 ActiveTab = 0;
    int32 RosterPage = 0;
    int32 RivalryPage = 0;
    int32 ArchivePage = 0;
    int32 PayoutPage = 0;
    int32 HistoricalRosterPage = 0;
    bool bShowHistoricalStandings = false;
    int32 SelectedArchiveWeek = 0;
    bool bHasArchivePage = false;
    bool bArchivePending = false;
    double ArchiveRequestTime = 0.0;
    UPROPERTY(Transient) FDigimonSeasonArchivePage ArchiveSnapshot;
    FString SelectedTamerId;
    FString BoundCareerId;
    bool bCommandPending = false;
    double CommandSentAt = 0.0;
    int32 PendingWeek = 0;
    bool bPendingComplete = false;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Root;
    UPROPERTY(Transient) TObjectPtr<UWidgetSwitcher> Pages;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Calendar;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SaveStatus;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> MatchKicker;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> MatchTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> MatchDetail;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> MatchOutcome;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> MatchAction;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PlayerName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> OpponentName;
    UPROPERTY(Transient) TObjectPtr<UImage> PlayerTamer;
    UPROPERTY(Transient) TObjectPtr<UImage> OpponentTamer;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PlayerTeamSummary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> OpponentTeamSummary;
    UPROPERTY(Transient) TArray<FDigimonSeasonPartnerView> PlayerTeam;
    UPROPERTY(Transient) TArray<FDigimonSeasonPartnerView> OpponentTeam;
    UPROPERTY(Transient) TArray<FDigimonSeasonMatchView> WeekMatches;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> ChampionPortrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ChampionName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ChampionDetails;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CareerRecord;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CareerRank;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CareerTitles;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CareerIncome;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> LeagueNews;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RosterPager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RosterPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RosterNext;
    UPROPERTY(Transient) TArray<FDigimonSeasonRosterView> RosterRows;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedTamerName;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SelectedTamerRecord;
    UPROPERTY(Transient) TArray<FDigimonSeasonPartnerView> SelectedTeam;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalryPager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RivalryPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RivalryNext;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalryEmpty;
    UPROPERTY(Transient) TArray<FDigimonSeasonRivalryView> RivalryCards;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> TitlePortrait;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TitleHolder;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TitleDetails;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> TitleMilestone;
    UPROPERTY(Transient) TObjectPtr<UProgressBar> DefenseProgress;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ReignHistory;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ArchivePager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ArchivePrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ArchiveNext;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> ArchiveRows;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ArchiveSelection;
    UPROPERTY(Transient) TArray<FDigimonSeasonMatchView> ArchiveMatches;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ArchivedPayouts;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> HistoricalStandings;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> HistoricalToggle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HistoricalPager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> HistoricalPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> HistoricalNext;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> HistoricalRows;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RewardSummary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RewardForecast;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PayoutPager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PayoutPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PayoutNext;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> PayoutRows;
};
