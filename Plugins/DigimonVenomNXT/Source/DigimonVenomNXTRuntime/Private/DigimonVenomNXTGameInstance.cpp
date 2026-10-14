#include "DigimonVenomNXTGameInstance.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTServerConsoleSubsystem.h"
#include "DigimonVenomNXTRuntime.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Misc/PackageName.h"

bool UDigimonVenomNXTGameInstance::ValidateReadyToEnterWorldForGameInstance(const UGameInstance* GameInstance, FString& OutError)
{
    OutError.Reset();
    if (!GameInstance)
    {
        OutError = TEXT("The Unreal GameInstance is unavailable.");
        return false;
    }

    const UDigimonVenomNXTAuthSubsystem* Auth = GameInstance->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    if (!Auth || !Auth->HasPendingCredentials())
    {
        OutError = TEXT("Enter a username/password and choose Create Account or Log In before entering the public world.");
        return false;
    }
    return true;
}

FString UDigimonVenomNXTGameInstance::GetPublicConnectionAddressForSettings()
{
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    FString Host = S->PublicGameAddress;
    Host.TrimStartAndEndInline();
    Host.RemoveFromStart(TEXT("http://"), ESearchCase::IgnoreCase);
    Host.RemoveFromStart(TEXT("https://"), ESearchCase::IgnoreCase);
    Host.RemoveFromEnd(TEXT("/"));

    if (Host.IsEmpty())
    {
        Host = TEXT("127.0.0.1");
    }

    // Keep IPv6 literals intact. For normal IPv4/DNS hosts, append the configured gameplay port.
    const bool bBracketedIPv6 = Host.StartsWith(TEXT("[")) && Host.Contains(TEXT("]"));
    const bool bAlreadyHasPort = bBracketedIPv6
        ? Host.Mid(Host.Find(TEXT("]")) + 1).StartsWith(TEXT(":"))
        : Host.Contains(TEXT(":"));
    if (!bAlreadyHasPort)
    {
        Host += FString::Printf(TEXT(":%d"), S->GameplayPort);
    }
    return Host;
}

bool UDigimonVenomNXTGameInstance::JoinPublicWorldForGameInstance(UGameInstance* GameInstance, FString& OutError)
{
    if (GameInstance)
        if (UDigimonVenomNXTServerConsoleSubsystem* Console = GameInstance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
    if (!ValidateReadyToEnterWorldForGameInstance(GameInstance, OutError)) return false;

    APlayerController* PC = GameInstance->GetFirstLocalPlayerController();
    if (!PC)
    {
        OutError = TEXT("No local player controller exists.");
        return false;
    }

    const FString Address = GetPublicConnectionAddressForSettings();
    UE_LOG(LogDigimonVenomNXT, Log, TEXT("Joining Digimon Venom NXT public world at %s using GameInstance %s."), *Address, *GetNameSafe(GameInstance->GetClass()));

    // No account token or password is placed in the travel URL. The gameplay
    // PlayerController authenticates over the existing UE connection after travel.
    PC->ClientTravel(Address, TRAVEL_Absolute);
    return true;
}

bool UDigimonVenomNXTGameInstance::HostPublicWorldForGameInstance(UGameInstance* GameInstance, const FString& AdminPassword, FString& OutError)
{
    if (GameInstance)
        if (UDigimonVenomNXTServerConsoleSubsystem* Console = GameInstance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
    if (!ValidateReadyToEnterWorldForGameInstance(GameInstance, OutError)) return false;

    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    if (!S)
    {
        OutError = TEXT("Digimon Venom NXT settings are unavailable.");
        return false;
    }
    const FString HostPassword = S->ResolveAdminHostPassword();
    if (HostPassword.IsEmpty() || HostPassword == TEXT("CHANGE_ME"))
    {
        OutError = TEXT("Configure a non-default Admin Host Password in Project Settings > Game > Digimon Venom NXT.");
        return false;
    }
    if (AdminPassword != HostPassword)
    {
        OutError = TEXT("Admin host password is incorrect.");
        return false;
    }

    const FString Package = S->PublicWorldMap.GetLongPackageName();
    if (Package.IsEmpty())
    {
        OutError = TEXT("Public World Map is not configured in Project Settings > Game > Digimon Venom NXT.");
        return false;
    }

    if (!FPackageName::IsValidLongPackageName(Package) || !FPackageName::DoesPackageExist(Package))
    {
        OutError = FString::Printf(TEXT("The configured Public World Map does not exist: %s"), *Package);
        return false;
    }

    UWorld* World = GameInstance->GetWorld();
    APlayerController* LocalController = GameInstance->GetFirstLocalPlayerController();
    if (!World || !LocalController || !LocalController->IsLocalController() || !LocalController->GetLocalPlayer())
    {
        OutError = TEXT("The local player or Unreal world is unavailable. Return to the main menu and try again.");
        return false;
    }
    UDigimonVenomNXTServerConsoleSubsystem* Console = GameInstance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>();
    if (!Console)
    {
        OutError = TEXT("The Digimon Venom NXT host session subsystem is unavailable.");
        return false;
    }

    UDigimonVenomNXTAuthSubsystem* Auth = GameInstance->GetSubsystem<UDigimonVenomNXTAuthSubsystem>();
    if (!Auth)
    {
        OutError = TEXT("The Digimon Venom NXT account subsystem is unavailable.");
        return false;
    }
    if (!Auth->AuthenticateLocalHost(OutError))
    {
        if (OutError.IsEmpty()) OutError = TEXT("The host account could not be authenticated.");
        return false;
    }

    // This capability is local provenance, never a replicated account role or username.
    // The subsystem also requires the resulting listen controller to authenticate normally.
    Console->ArmHostSession(Auth->GetAccountId());

    UE_LOG(LogDigimonVenomNXT, Log,
        TEXT("Starting Digimon Venom NXT public listen world. GameInstance=%s World=%s Map=%s UDP=%d"),
        *GetNameSafe(GameInstance->GetClass()), *GetNameSafe(World), *Package, S->GameplayPort);

    // A single canonical Unreal listen-travel path is used here. Passing the
    // listen option on OpenLevel creates the listen NetDriver for the destination
    // world; no separate pre-travel EnableListenServer call is required. Keeping
    // hosting to one mechanism also avoids editor/standalone state mismatches.
    const FString Options = FString::Printf(TEXT("listen?port=%d"), S->GameplayPort);
    UGameplayStatics::OpenLevel(GameInstance, FName(*Package), true, Options);
    return true;
}

void UDigimonVenomNXTGameInstance::ReturnToMainMenuForGameInstance(UGameInstance* GameInstance)
{
    FString Error;
    if (!TryReturnToMainMenuForGameInstance(GameInstance, Error))
        UE_LOG(LogDigimonVenomNXT, Error, TEXT("Cannot return to Digimon Venom NXT MainMenu: %s"), *Error);
}

bool UDigimonVenomNXTGameInstance::ValidateMainMenuForGameInstance(const UGameInstance* GameInstance, FString& OutError)
{
    OutError.Reset();
    if (!GameInstance || !GameInstance->GetWorld())
    {
        OutError = TEXT("The current Unreal world is unavailable.");
        return false;
    }
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const FString Package = Settings ? Settings->MainMenuMap.GetLongPackageName() : FString();
    if (Package.IsEmpty() || !FPackageName::IsValidLongPackageName(Package) || !FPackageName::DoesPackageExist(Package))
    {
        OutError = TEXT("The configured Main Menu Map is unavailable. Check Project Settings > Game > Digimon Venom NXT and include that map in the packaged game.");
        return false;
    }
    if (Settings && Package == Settings->PublicWorldMap.GetLongPackageName())
    {
        OutError = TEXT("Main Menu Map must be different from Public World Map. Your session has not been closed.");
        return false;
    }
    return true;
}

bool UDigimonVenomNXTGameInstance::TryReturnToMainMenuForGameInstance(UGameInstance* GameInstance, FString& OutError)
{
    if (!ValidateMainMenuForGameInstance(GameInstance, OutError)) return false;
    if (UDigimonVenomNXTServerConsoleSubsystem* Console = GameInstance->GetSubsystem<UDigimonVenomNXTServerConsoleSubsystem>()) Console->DisarmHostSession();
    // Absolute travel removes listen options and tears down the current connection.
    UGameplayStatics::OpenLevel(GameInstance, FName(*GetDefault<UDigimonVenomNXTSettings>()->MainMenuMap.GetLongPackageName()), true);
    return true;
}

bool UDigimonVenomNXTGameInstance::JoinPublicWorld(FString& OutError)
{
    const bool bSuccess = JoinPublicWorldForGameInstance(this, OutError);
    OnTravelResult.Broadcast(bSuccess, bSuccess ? TEXT("Connecting to the public world...") : OutError);
    return bSuccess;
}

bool UDigimonVenomNXTGameInstance::HostPublicWorld(const FString& AdminPassword, FString& OutError)
{
    const bool bSuccess = HostPublicWorldForGameInstance(this, AdminPassword, OutError);
    OnTravelResult.Broadcast(bSuccess, bSuccess ? TEXT("Hosting the public world.") : OutError);
    return bSuccess;
}

void UDigimonVenomNXTGameInstance::ReturnToMainMenu()
{
    ReturnToMainMenuForGameInstance(this);
}

FString UDigimonVenomNXTGameInstance::GetPublicConnectionAddress() const
{
    return GetPublicConnectionAddressForSettings();
}
