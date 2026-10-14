#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTGameHUDWidget.generated.h"

class UBorder;
class UEditableTextBox;
class UDigimonVenomNXTAnimatedPortrait;
class UDigimonVenomNXTEvolutionWidget;
class UDigimonVenomNXTDigiDexWidget;
class UDigimonVenomNXTPartyWidget;
class UDigimonVenomNXTFieldPartyWidget;
class UDigimonVenomNXTWorldChatWidget;
class UDigimonVenomNXTDigiLabWidget;
class UDigimonVenomNXTVideoSettingsWidget;
class UDigimonVenomNXTServerConsoleWidget;
class UDigimonVenomNXTFarmWidget;
class UDigimonVenomNXTSeasonWidget;
class UDigimonVenomNXTRelayWidget;
class UDigimonVenomNXTChroniclesWidget;
class UDigimonVenomNXTGhostLineWidget;
class UDigimonVenomNXTCommunityWidget;
class UDigimonVenomNXTTamerStudioWidget;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;
class UScrollBox;
class USlider;
class UUniformGridPanel;
class USizeBox;
class UDigimonVenomNXTActionButton;
class ADigimonVenomNXTGameState;
class ADigimonVenomNXTPlayerState;

/**
 * Native in-world UI shell. Provides usable pages for Atlas, party/collection, DigiLab,
 * DigiFarm, shop, Season, Ranked, AI rival stats and WORLD chat. Blueprint subclasses can restyle/extend it.
 */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTGameHUDWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void ShowPage(const FString& PageName);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void ShowToast(const FString& Title, const FString& Message);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Chat") void AppendChat(const FDigimonChatMessage& Message);
    bool IsWorldChatTyping() const;
    bool IsWorldChatHovered() const;
    void FocusWorldChat();
    void ReleaseWorldChatFocus();
    void RefreshChatHistory();
    /** Opens a stable, account-targeted community action from a field nameplate. */
    void OpenCommunityTarget(const FString& TargetId, const FString& Name, bool bRival, const FString& PageName = TEXT("Social"));
    bool HandleCommunityBack();
    bool IsCommunityOpen() const { return bMenuOpen && (ActivePage == TEXT("Social") || ActivePage == TEXT("Unranked") || ActivePage == TEXT("Clans") || ActivePage == TEXT("Trading Center")); }

    /** Owner-only, bounded server response; clients never read the authority's rival save. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void ApplyRivalActivityPage(const FDigimonAIRivalActivityPage& Page);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void RefreshLivePages();
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void ApplySeasonArchivePage(const FDigimonSeasonArchivePage& Page);

    /** Opened only by a proximity-checked server interaction with a campaign NPC. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Relay") void ShowRelayDialogue(FName NPCId, const FString& Dialogue, const FDigimonRelayProgress& ConfirmedProgress);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Relay") void CloseRelayDialogue();
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Relay") bool IsRelayDialogueOpen() const { return !RelayDialogueNPC.IsNone(); }

    /** Field exploration owns the screen by default. M/Tab opens this menu; Escape closes it. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void SetMenuOpen(bool bOpen);
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void ToggleMenu();
    /** In-place recovery overlay; leaves the current map, pawn position and private instance intact. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void OpenDigiLab();
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|HUD") bool IsMenuOpen() const { return bMenuOpen; }
    bool IsTamerStudioOpen() const { return bMenuOpen && ActivePage == TEXT("Tamer Studio"); }
    bool IsVideoSettingsOpen() const { return bMenuOpen && ActivePage == TEXT("Video"); }
    /** Consume Back while confirming a display change; a second Back closes the menu. */
    bool HandleVideoSettingsBack();
    bool IsServerConsoleOpen() const { return bMenuOpen && ActivePage == TEXT("Server Console"); }
    bool HandleServerConsoleBack();
    bool IsLogoutConfirmationOpen() const { return bLogoutConfirmationOpen; }
    bool HandleLogoutConfirmationBack();
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|HUD") void SetCompactHUDVisible(bool bVisible);
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|HUD") bool IsCompactHUDVisible() const { return bCompactHUDVisible; }

protected:
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleProfileChanged();
    UFUNCTION() void HandleMasterVolume(float Value);
    UFUNCTION() void HandleMusicVolume(float Value);
    UFUNCTION() void HandleEffectsVolume(float Value);
    UFUNCTION() void HandleUIVolume(float Value);
    UFUNCTION() void CommitAudioVolumes();

private:
    bool bBuilt = false;
    bool bAudioMixDirty = false;
    bool bMenuOpen = false;
    bool bLogoutConfirmationOpen = false;
    bool bCompactHUDVisible = true;
    float RefreshAccumulator = 0.0f;
    float LiveRefreshAccumulator = 0.0f;
    float ToastSecondsRemaining = 0.0f;
    FString ActivePage = TEXT("Overview");
    int32 RivalPageIndex = 0;
    EDigimonPrivateCampaign SelectedCampaign = EDigimonPrivateCampaign::Relay;
    FName RelayDialogueNPC = NAME_None;
    bool bHasRivalSnapshot = false;
    bool bRivalsLayoutBuilt = false;
    bool bRivalWindowExpired = false;
    double RivalSnapshotReceivedAt = 0.0;
    double RankedSnapshotReceivedAt = 0.0;
    int64 RankedSnapshotUnix = 0;
    TArray<FString> RivalVisibleIds;
    TWeakObjectPtr<ADigimonVenomNXTGameState> BoundGameState;
    UPROPERTY(Transient) FDigimonAIRivalActivityPage RivalSnapshot;
    UPROPERTY(Transient) TMap<FString, TObjectPtr<UScrollBox>> PageScrolls;
    UPROPERTY(Transient) TMap<FString, TObjectPtr<UDigimonVenomNXTActionButton>> NavButtons;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalSummaryText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalCountdownText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalTotalsText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RivalPageText;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RivalPreviousButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RivalNextButton;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> RivalRowsBox;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> RivalMetricValues;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> RivalRowTexts;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> RivalChallengeButtons;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RankedCountdownText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RankedEnergyText;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> BoundPlayerState;

    UPROPERTY(Transient) TObjectPtr<UBorder> CompactHUDRoot;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTAnimatedPortrait> CompactLeadImage;
    UPROPERTY(Transient) TArray<TObjectPtr<UTextBlock>> AudioVolumeLabels;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeaderIdentity;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeaderEconomy;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeaderRubies;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTFieldPartyWidget> FieldParty;
    UPROPERTY(Transient) TObjectPtr<UWidget> FieldPartyFrame;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTWorldChatWidget> FieldWorldChat;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTWorldChatWidget> MenuWorldChat;
    UPROPERTY(Transient) TObjectPtr<USizeBox> FieldWorldChatFrame;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HeaderWorld;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> FieldHintText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ToastText;
    UPROPERTY(Transient) TObjectPtr<UBorder> RelayObjectiveRoot;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RelayCampaignLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RelayObjectiveTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RelayObjectiveText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RelayInteractionText;
    UPROPERTY(Transient) TObjectPtr<UBorder> RelayDialogueRoot;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> RelayDialogueContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTRelayWidget> RelayJournal;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTChroniclesWidget> ChroniclesJournal;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTGhostLineWidget> GhostLineJournal;
    UPROPERTY(Transient) TObjectPtr<UBorder> MenuRoot;
    UPROPERTY(Transient) TObjectPtr<UWidgetSwitcher> PageSwitcher;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> OverviewContent;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> TamerContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTTamerStudioWidget> TamerStudio;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> PartyContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTPartyWidget> PartyPanel;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> CollectionContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTEvolutionWidget> EvolutionLab;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> DigiDexContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTDigiDexWidget> DigiDex;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> LabContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTDigiLabWidget> DigiLab;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTVideoSettingsWidget> VideoSettings;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTServerConsoleWidget> ServerConsole;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> HostConsoleButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> LogoutButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> LogoutCancelButton;
    UPROPERTY(Transient) TObjectPtr<UBorder> LogoutOverlay;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> LogoutMessage;
    UPROPERTY(Transient) TObjectPtr<UWidget> MenuBodyFrame;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> FarmContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTFarmWidget> FarmManager;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTFarmWidget> FarmWorldHUD;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> ShopContent;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> StoryContent;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> SeasonContent;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTSeasonWidget> SeasonCareer;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> RankedContent;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> RivalsContent;

    UPROPERTY(Transient) TMap<FString, TObjectPtr<UDigimonVenomNXTCommunityWidget>> CommunityPages;
    TMap<FString, int32> PageIndices;

    void BuildNativeUI();
    void RefreshSessionControls();
    void SetLogoutConfirmation(bool bShow);
    void SyncMenuMusic();
    void BindPlayerState();
    void RefreshAll();
    void RefreshHeader();
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> StarterSearchInput;
    FString StarterSearchTerm;
    int32 StarterPage = 0;
    void RefreshOverview();
    void BuildAudioControls();
    void SetAudioMixValue(int32 Channel, float Value);
    void RefreshTamerStudio();
    void RefreshParty();
    void RefreshCollection();
    void RefreshDigiDex();
    void RefreshLab();
    void RefreshFarm();
    void RefreshFarmPresentation(bool bRefreshData = false);
    void RefreshFieldPartyPresentation(bool bRefreshData = false);
    void RefreshWorldChatPresentation();
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> AtlasGrid;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> AtlasPageLabel;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> AtlasPrevious;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> AtlasNext;
    int32 AtlasRegion = -1;
    int32 AtlasPage = 0;
    void RefreshAtlas();
    int32 ShopFilter = 0;
    int32 ShopQuantity = 1;
    void RefreshShop();
    void RefreshStory();
    void RefreshParadoxStory();
    void RefreshGhostLineStory();
    void RefreshRelayFieldHUD();
    void RefreshSeason();
    void RefreshRanked();
    void RefreshRivals();
    void RefreshLiveTimers();
    void RequestLivePage();
    ADigimonVenomNXTPlayerState* GetDigimonPlayerState() const;
};
