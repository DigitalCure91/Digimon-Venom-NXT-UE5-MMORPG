#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTVideoSettingsWidget.generated.h"

class UBorder;
class UHorizontalBox;
class UEditableTextBox;
class UOverlay;
class UScrollBox;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;
class UDigimonVenomNXTVideoSettingsSubsystem;
struct FDigimonVideoSettings;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDigimonVideoOptionChanged, FName, SettingKey, int32, OptionIndex);

/** Native, keyboard/gamepad accessible dropdown with a stable setting identity. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTVideoOptionPicker : public UComboBoxString
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTVideoOptionPicker(const FObjectInitializer& ObjectInitializer);
    void InitializeOption(FName InSettingKey);
    UPROPERTY(Transient) FDigimonVideoOptionChanged OnOptionChanged;
private:
    FName SettingKey;
    UFUNCTION() void HandleOptionSelected(FString SelectedItem, ESelectInfo::Type SelectionType);
    UFUNCTION() void HandleOptionOpened();
};

USTRUCT()
struct FDigimonVideoControlView
{
    GENERATED_BODY()
    FName SettingKey;
    FString Description;
    TArray<float> Values;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTVideoOptionPicker> Picker;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Help;
};

/** Retained local video controls. Gameplay/profile refreshes never reset an edit. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTVideoSettingsWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    /** Idempotent: call when the parent menu shows this page. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Video") void OpenSettings();
    /** Keep staged edits, but immediately undo an unconfirmed display preview. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Video") void CloseSettings();
    /** Consume Back only when it reverts an active display preview. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Video") bool HandleBack();
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|UI") FDigimonUIButtonAction OnAction;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
private:
    void BuildLayout();
    void RefreshControls();
    void RefreshStatus();
    void RefreshConfirmation();
    void SelectCategory(int32 CategoryIndex);
    void PopulateResolutions(const FDigimonVideoSettings& Settings);
    void StageCustomFrameRate();
    void AddControl(UVerticalBox* Body, FName Key, const FString& Label, const FString& Help, const TArray<FString>& Labels, const TArray<float>& Values);
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload = 0);
    UDigimonVenomNXTVideoSettingsSubsystem* Backend() const;
    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleOptionChanged(FName SettingKey, int32 OptionIndex);
    UFUNCTION() void HandleCustomFrameRateCommitted(const FText& Text, ETextCommit::Type CommitType);

    bool bPageOpen = false;
    bool bRefreshing = false;
    bool bShowingConfirmation = false;
    bool bBackendWasReady = false;
    int32 LastConfirmationSeconds = INDEX_NONE;
    int32 ActiveCategory = 0;
    int32 SelectedPreset = INDEX_NONE;
    TArray<FIntPoint> DisplayResolutions;
    FString Feedback;
    double PerformanceSampleStarted = 0.0;
    int32 PerformanceSampleFrames = 0;
    UPROPERTY(Transient) TObjectPtr<UOverlay> Root;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> EditableContent;
    UPROPERTY(Transient) TObjectPtr<UWidgetSwitcher> Categories;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> RuntimeNotice;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PresetDescription;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> PerformanceReadout;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> CustomFrameRateStatus;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> CustomFrameRateInput;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> CustomFrameRateButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ConfirmationText;
    UPROPERTY(Transient) TObjectPtr<UBorder> ConfirmationOverlay;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ApplyButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> RevertButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ResetButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> KeepDisplayButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> UndoDisplayButton;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> CategoryButtons;
    UPROPERTY(Transient) TArray<TObjectPtr<UDigimonVenomNXTActionButton>> PresetButtons;
    UPROPERTY(Transient) TArray<FDigimonVideoControlView> Controls;
};
