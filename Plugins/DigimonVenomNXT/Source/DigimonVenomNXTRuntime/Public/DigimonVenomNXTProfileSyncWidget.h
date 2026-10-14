#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonVenomNXTProfileSyncWidget.generated.h"

class UTextBlock;
class UButton;

/** Login barrier: never renders an empty account as a new character. */
UCLASS()
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTProfileSyncWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetStatus(const FString& Message, bool bCanRetry);
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
private:
    void BuildNativeUI();
    UPROPERTY(Transient) TObjectPtr<UTextBlock> StatusText;
    UPROPERTY(Transient) TObjectPtr<UButton> RetryButton;
    UPROPERTY(Transient) TObjectPtr<UButton> LeaveButton;
    UFUNCTION() void HandleRetry();
    UFUNCTION() void HandleLeave();
};
