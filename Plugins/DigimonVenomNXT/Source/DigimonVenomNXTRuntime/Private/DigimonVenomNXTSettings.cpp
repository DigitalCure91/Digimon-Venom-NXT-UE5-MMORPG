#include "DigimonVenomNXTSettings.h"
#include "HAL/PlatformMisc.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Paths.h"

UDigimonVenomNXTSettings::UDigimonVenomNXTSettings()
{
    MainMenuMap = FSoftObjectPath(TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu.MainMenu"));
    PublicWorldMap = FSoftObjectPath(TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld.PublicWorld"));
}

FString UDigimonVenomNXTSettings::ResolveAdminHostPassword() const
{
    // Credentials stay on the machine hosting the world, outside shared game content.
    FString Secret = FPlatformMisc::GetEnvironmentVariable(TEXT("DIGIMONVENOMNXT_HOST_PASSWORD"));
    if (!Secret.IsEmpty()) return Secret;
    FConfigFile LocalHost;
    // FConfigFile::Read returns void in UE 5.8. Missing files/keys leave Secret empty.
    LocalHost.Read(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DigimonVenomNXT/Host.ini")));
    LocalHost.GetString(TEXT("Hosting"), TEXT("Password"), Secret);
    if (!Secret.IsEmpty()) return Secret;
    return AdminHostPassword;
}
