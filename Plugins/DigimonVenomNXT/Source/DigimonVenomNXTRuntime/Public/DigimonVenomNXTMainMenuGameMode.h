#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DigimonVenomNXTMainMenuGameMode.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTMainMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTMainMenuGameMode();
};

UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTMainMenuPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;

private:
    UPROPERTY(Transient) TObjectPtr<class UDigimonVenomNXTMainMenuWidget> MainMenuWidget;
};
