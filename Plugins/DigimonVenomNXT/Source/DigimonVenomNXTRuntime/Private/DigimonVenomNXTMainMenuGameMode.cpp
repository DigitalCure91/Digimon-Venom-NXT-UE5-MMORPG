#include "DigimonVenomNXTMainMenuGameMode.h"
#include "DigimonVenomNXTMainMenuWidget.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"

ADigimonVenomNXTMainMenuGameMode::ADigimonVenomNXTMainMenuGameMode()
{
    DefaultPawnClass = nullptr;
    PlayerControllerClass = ADigimonVenomNXTMainMenuPlayerController::StaticClass();
}

void ADigimonVenomNXTMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (!IsLocalController()) return;
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly());
    if (UDigimonVenomNXTAudioSubsystem* Audio = GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<UDigimonVenomNXTAudioSubsystem>() : nullptr) Audio->PlayMainMenuMusic();
    MainMenuWidget = CreateWidget<UDigimonVenomNXTMainMenuWidget>(this, UDigimonVenomNXTMainMenuWidget::StaticClass());
    if (MainMenuWidget)
    {
        MainMenuWidget->AddToViewport(100);
        MainMenuWidget->ActivateWidget();
    }
}
