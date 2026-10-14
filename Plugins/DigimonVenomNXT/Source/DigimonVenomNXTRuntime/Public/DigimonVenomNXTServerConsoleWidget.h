#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTServerConsoleWidget.generated.h"

class UBorder;
class UEditableTextBox;
class UHorizontalBox;
class UMultiLineEditableText;
class UScrollBox;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;

/** Uses the engine's initializer API rather than deprecated direct UMG fields. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTConsoleFilter : public UComboBoxString
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTConsoleFilter(const FObjectInitializer& ObjectInitializer);
};

/** Local listen-host console. It neither replicates output nor forwards commands through chat/RPCs. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTServerConsoleWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Server") void OpenConsole();
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Server") void CloseConsole();
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Server") bool HandleBack();
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Server") bool IsOpen() const { return bPageOpen; }
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
private:
    void BuildLayout();
    bool CheckAccess();
    void ClearPrivateState();
    void PollEntries();
    void RefreshReadout();
    void RebuildLog();
    void AppendLogRow(const FDigimonServerConsoleEntry& Entry);
    void RebuildHelp();
    void SelectPage(int32 PageIndex);
    void SetFeedback(const FString& Message, bool bSuccess);
    void SubmitCommand();
    void NavigateHistory(int32 Direction);
    void CompleteCommand();
    void FillCommand(const FString& Command);
    void OpenCredentialPrompt(const FString& Verb, const FString& Username);
    void CloseCredentialPrompt();
    void SubmitCredentialPrompt();
    bool EntryMatches(const FDigimonServerConsoleEntry& Entry) const;
    bool CommandHasFocus() const;
    UDigimonVenomNXTActionButton* MakeButton(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload = 0);
    UDigimonVenomNXTServerConsoleSubsystem* Backend() const;

    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleCategoryChanged(FString Selection, ESelectInfo::Type SelectionType);
    UFUNCTION() void HandleSeverityChanged(FString Selection, ESelectInfo::Type SelectionType);
    UFUNCTION() void HandleLogSearchChanged(const FText& Text);
    UFUNCTION() void HandleHelpSearchChanged(const FText& Text);
    UFUNCTION() void HandleCommandChanged(const FText& Text);
    UFUNCTION() void HandleCommandCommitted(const FText& Text, ETextCommit::Type CommitType);
    UFUNCTION() void HandleCredentialCommitted(const FText& Text, ETextCommit::Type CommitType);
    UFUNCTION() void HandleUserScrolled(float Offset);

    bool bPageOpen = false;
    bool bPaused = false;
    bool bFollowLive = true;
    bool bLogFilterDirty = false;
    bool bHelpFilterDirty = false;
    bool bUpdatingInput = false;
    bool bSynchronizingScroll = false;
    bool bSensitiveDraft = false;
    bool bCredentialPromptOpen = false;
    int32 ActivePage = 0;
    int32 HistoryIndex = INDEX_NONE;
    int32 PendingEntries = 0;
    int32 OnlinePlayers = 0;
    int32 RetainedEntries = 0;
    int64 LastSequence = 0;
    float PollElapsed = 0.0f;
    FString DraftCommand;
    FString CategoryFilter;
    FString SeverityFilter;
    FString LogSearch;
    FString HelpSearch;
    FString StatusNotice;
    FString CredentialVerb;
    FString CredentialUsername;
    TArray<FString> CommandHistory;
    TArray<FDigimonServerConsoleEntry> Entries;
    TArray<FDigimonServerCommandInfo> CommandHelp;
    TArray<int64> RenderedSequences;

    UPROPERTY(Transient) TObjectPtr<UBorder> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Content;
    UPROPERTY(Transient) TObjectPtr<UWidgetSwitcher> Pages;
    UPROPERTY(Transient) TObjectPtr<UScrollBox> LogScroll;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> LogRows;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> HelpRows;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SessionReadout;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ViewReadout;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyMessage;
    UPROPERTY(Transient) TObjectPtr<UMultiLineEditableText> FeedbackText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> InputHint;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HelpReadout;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PauseCaption;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> FollowCaption;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTConsoleFilter> CategoryPicker;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTConsoleFilter> SeverityPicker;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> LogSearchInput;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> HelpSearchInput;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> CommandInput;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ExecuteButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> PauseButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> FollowButton;
    UPROPERTY(Transient) TObjectPtr<UBorder> CredentialOverlay;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CredentialTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CredentialAccount;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CredentialFeedback;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> CredentialPassword;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> CredentialConfirmation;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> PageButtons;
    UPROPERTY(Transient) TArray<TObjectPtr<UBorder>> RenderedRows;
};
