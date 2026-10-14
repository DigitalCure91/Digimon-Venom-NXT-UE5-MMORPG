#include "DigimonVenomNXTImportCommandlet.h"
#include "DigimonVenomNXTEditorLibrary.h"
#include "Misc/Parse.h"

UDigimonVenomNXTImportCommandlet::UDigimonVenomNXTImportCommandlet()
{
    IsClient = false;
    IsServer = false;
    IsEditor = true;
    LogToConsole = true;
    ShowErrorCount = true;
}
int32 UDigimonVenomNXTImportCommandlet::Main(const FString& Params)
{
    FString Report;
    const bool bValidateOnly = FParse::Param(*Params, TEXT("ValidateOnly"));
    const bool bValidateStartup = FParse::Param(*Params, TEXT("ValidateStartup"));
    const bool bRepairStartup = FParse::Param(*Params, TEXT("RepairStartup"));
    if (static_cast<int32>(bValidateOnly) + static_cast<int32>(bValidateStartup) + static_cast<int32>(bRepairStartup) > 1)
    {
        UE_LOG(LogTemp, Error, TEXT("Choose only one commandlet mode: ValidateOnly, ValidateStartup, RepairStartup, or a full import."));
        return 2;
    }
    const bool bSuccess = bValidateOnly ? UDigimonVenomNXTEditorLibrary::ValidateBundledContent(Report)
        : bValidateStartup ? UDigimonVenomNXTEditorLibrary::ValidateGameWorlds(Report)
        : bRepairStartup ? UDigimonVenomNXTEditorLibrary::PrepareGameWorlds(Report)
        : UDigimonVenomNXTEditorLibrary::BuildCompleteGameContent(!FParse::Param(*Params, TEXT("NoReplace")), Report);
    if (!bSuccess)
    {
        UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT content setup failed:\n%s"), *Report);
        return 1;
    }
    UE_LOG(LogTemp, Display, TEXT("Digimon Venom NXT content setup completed:\n%s"), *Report);
    return 0;
}
