#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DigimonVenomNXTGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDigimonTravelResultEvent, bool, bSuccess, const FString&, Message);

/**
 * Optional Digimon Venom NXT GameInstance wrapper.
 *
 * Digimon Venom NXT no longer requires the project to use this exact GameInstance class.
 * The static helpers below operate on any valid UGameInstance so projects with an
 * existing custom GameInstance can still host/join/return to menu correctly.
 */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Network")
    FDigimonTravelResultEvent OnTravelResult;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Network")
    bool JoinPublicWorld(FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Network")
    bool HostPublicWorld(const FString& AdminPassword, FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Network")
    void ReturnToMainMenu();

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Network")
    FString GetPublicConnectionAddress() const;

    /** C++ helpers used by native plugin UI/controllers. They work with any UGameInstance. */
    static bool JoinPublicWorldForGameInstance(UGameInstance* GameInstance, FString& OutError);
    static bool HostPublicWorldForGameInstance(UGameInstance* GameInstance, const FString& AdminPassword, FString& OutError);
    static void ReturnToMainMenuForGameInstance(UGameInstance* GameInstance);
    /** Preflight the configured local menu before a save-acknowledged logout. */
    static bool ValidateMainMenuForGameInstance(const UGameInstance* GameInstance, FString& OutError);
    static bool TryReturnToMainMenuForGameInstance(UGameInstance* GameInstance, FString& OutError);
    static FString GetPublicConnectionAddressForSettings();

private:
    static bool ValidateReadyToEnterWorldForGameInstance(const UGameInstance* GameInstance, FString& OutError);
};
