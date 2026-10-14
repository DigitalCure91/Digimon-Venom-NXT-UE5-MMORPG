#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTWorldChatWidget.generated.h"

class UButton;
class UEditableTextBox;
class UScrollBox;
class USizeBox;
class UTextBlock;
class UVerticalBox;

/** Retained native WORLD channel, shared by the habitat HUD and the field menu. */
UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTWorldChatWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

    void SetFieldPresentation(bool bField);
    void SetHistory(const TArray<FDigimonChatMessage>& History);
    void AppendMessage(const FDigimonChatMessage& Message);
    void FocusComposer();
    void ReleaseComposer();
    bool IsComposing() const;
    FString GetDraft() const;
    void SetDraft(const FString& Draft);
    void TakeComposerStateFrom(const UDigimonVenomNXTWorldChatWidget* Other);

private:
    UPROPERTY(Transient) TObjectPtr<UScrollBox> HistoryScroll;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> MessageRows;
    UPROPERTY(Transient) TObjectPtr<USizeBox> HistorySize;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> MessageInput;
    UPROPERTY(Transient) TObjectPtr<UButton> SendButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SendLabel;
    UPROPERTY(Transient) TObjectPtr<UButton> UnreadButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> UnreadLabel;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Counter;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Help;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> EmptyLabel;

    bool bBuilt = false;
    bool bFieldPresentation = true;
    bool bChangingText = false;
    bool bFollowTail = true;
    bool bPendingTail = false;
    bool bLastCanSend = false;
    bool bWasFocused = false;
    int32 UnreadCount = 0;
    uint64 LastFocusReleaseFrame = MAX_uint64;
    double LastSendTime = -1000.0;

    void BuildNativeUI();
    void RefreshComposer();
    void RefreshUnread();
    bool CanSend() const;
    int32 GetCharacterLimit() const;
    UFUNCTION() void HandleSend();
    UFUNCTION() void HandleTextChanged(const FText& Text);
    UFUNCTION() void HandleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
    UFUNCTION() void HandleScrolled(float Offset);
    UFUNCTION() void HandleUnread();
};
