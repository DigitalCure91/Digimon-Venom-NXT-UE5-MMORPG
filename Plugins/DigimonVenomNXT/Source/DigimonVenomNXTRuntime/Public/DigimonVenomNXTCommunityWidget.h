#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "DigimonVenomNXTCommunityWidget.generated.h"

class UBorder;
class UComboBoxString;
class UEditableTextBox;
class UHorizontalBox;
class UScrollBox;
class UTextBlock;
class UVerticalBox;
class UDigimonVenomNXTActionButton;
class UDigimonVenomNXTSocialComponent;
class UDigimonVenomNXTTradeComponent;
class UDigimonVenomNXTUnrankedComponent;
class ADigimonVenomNXTPlayerState;

/** Account-owned social, clan, friendly battle and trading pages. Forms survive live refreshes. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTCommunityWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void Configure(FName InSection);
    void SetPageActive(bool bInActive);
    void OpenTarget(const FString& TargetId, const FString& Name, bool bRival);
    void ReviewIgnoreTarget(const FString& TargetId, const FString& Name);
    void RequestRefresh();
    bool HandleBack();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
    virtual FReply NativeOnPreviewKeyDown(const FGeometry& Geometry, const FKeyEvent& Event) override;

private:
    struct FAction
    {
        FString Kind;
        FString Target;
        FString Text;
        FString Extra;
        FGuid Id;
        int32 Revision = 0;
        int32 Number = 0;
        int64 Credits = 0;
        int32 Rubies = 0;
        TArray<FGuid> Partners;
    };
    FName Section = TEXT("Social");
    FString Mode = TEXT("Friends");
    bool bBuilt = false;
    bool bActive = false;
    bool bDirty = true;
    float RefreshTime = 0;
    int32 NextAction = 1;
    TMap<int32, FAction> Actions;
    TArray<int32> DynamicActionIds;
    FAction PendingAction;
    FGuid DisplayedSession;
    FGuid SeenPurchaseToken;
    int32 DisplayedRevision = 0;
    FString LoadedClanId;
    FString ExpectedConfirmationName;
    FString TargetAccount;
    bool bTargetRival = false;
    int32 BrowsePage = 0;
    FString SubmittedSearch;
    TMap<FString, FGuid> PartnerOptions;
    TSet<FString> VisibleForms;

    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Body;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> FormHost;
    UPROPERTY(Transient) TObjectPtr<UHorizontalBox> TabRow;
    UPROPERTY(Transient) TObjectPtr<UScrollBox> Scroll;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> Live;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Summary;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<UBorder> Confirmation;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ConfirmationText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ConfirmationTitle;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> ConfirmationName;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTActionButton> ConfirmationButton;
    UPROPERTY(Transient) TMap<FString, TObjectPtr<UWidget>> Forms;
    UPROPERTY(Transient) TMap<FString, TObjectPtr<UEditableTextBox>> Inputs;
    UPROPERTY(Transient) TMap<FString, TObjectPtr<UDigimonVenomNXTActionButton>> Tabs;
    UPROPERTY(Transient) TObjectPtr<UComboBoxString> ListingPartner;
    UPROPERTY(Transient) TArray<TObjectPtr<UComboBoxString>> OfferPartners;
    TWeakObjectPtr<UDigimonVenomNXTSocialComponent> Social;
    TWeakObjectPtr<UDigimonVenomNXTTradeComponent> Trade;
    TWeakObjectPtr<UDigimonVenomNXTUnrankedComponent> Unranked;
    TWeakObjectPtr<ADigimonVenomNXTPlayerState> Player;

    UFUNCTION() void HandleAction(const FString& Action, int32 Payload);
    UFUNCTION() void HandleChanged();
    UFUNCTION() void HandleProfileChanged();
    UFUNCTION() void HandleSocialResult(bool bSuccess, const FString& Message);
    UFUNCTION() void HandleChatCommitted(const FText& Text, ETextCommit::Type Commit);
    void Build();
    void Bind();
    void SetMode(const FString& NewMode);
    void Refresh();
    void RefreshSocial();
    void RefreshClans();
    void RefreshUnranked();
    void RefreshTrading();
    void RefreshPartnerOptions();
    void Execute(const FAction& Action);
    void Ask(const FAction& Action, const FString& Title, const FString& Message);
    void ShowStatus(const FString& Message, bool bSuccess = true);
    UDigimonVenomNXTActionButton* Button(const FString& Label, const FAction& Action, bool bDynamic = false, bool bEnabled = true);
    UVerticalBox* Form(const FString& Key);
    UEditableTextBox* Input(UVerticalBox* Parent, const FString& Key, const FString& Label, const FString& Hint, int32 MaxLength = 100);
    UVerticalBox* Card(const FString& Title, const FString& Detail = FString());
    void AddAction(UVerticalBox* Parent, const FString& Label, const FAction& Action, bool bEnabled = true);
    FString Value(const FString& Key) const;
    bool ReadPrice(const FString& Prefix, int64& Credits, int32& Rubies);
    FAction Make(const FString& Kind, const FString& Target = FString()) const;
};
