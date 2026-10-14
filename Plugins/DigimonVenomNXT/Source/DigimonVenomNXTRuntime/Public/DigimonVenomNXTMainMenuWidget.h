#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTMainMenuWidget.generated.h"

class UBorder;
class UButton;
class UEditableTextBox;
class UTextBlock;
class UWidgetSwitcher;
class UDigimonVenomNXTVideoSettingsWidget;

/** Fully native login/create-account and public join/admin-host menu. No join password exists. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTMainMenuWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Main Menu") void ShowAuthentication();
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Main Menu") void ShowServerPage();

protected:
    UFUNCTION() void HandleCreateAccount();
    UFUNCTION() void HandleLogin();
    UFUNCTION() void HandleLogout();
    UFUNCTION() void HandleJoin();
    UFUNCTION() void HandleHost();
    UFUNCTION() void HandleAuthResult(const FDigimonAuthResult& Result);
    UFUNCTION() void HandleOpenVideo();
    UFUNCTION() void HandleCloseVideo();
    UFUNCTION() void HandleExitGame();

private:
    bool bBuilt = false;
    UPROPERTY(Transient) TObjectPtr<UWidgetSwitcher> PageSwitcher;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> UsernameInput;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> PasswordInput;
    UPROPERTY(Transient) TObjectPtr<UEditableTextBox> AdminPasswordInput;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> AuthStatusText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ServerStatusText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> WelcomeText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> ConnectionText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> HostInfoText;
    UPROPERTY(Transient) TObjectPtr<UButton> JoinWorldButton;
    UPROPERTY(Transient) TObjectPtr<UWidget> LoginSurface;
    UPROPERTY(Transient) TObjectPtr<UWidget> VideoSurface;
    UPROPERTY(Transient) TObjectPtr<UButton> VideoMenuButton;
    UPROPERTY(Transient) TObjectPtr<UDigimonVenomNXTVideoSettingsWidget> VideoSettings;

    void BuildNativeUI();
    void RefreshServerPage();
    void SetAuthStatus(const FString& Text, bool bError = false);
    void SetServerStatus(const FString& Text, bool bError = false);
};
