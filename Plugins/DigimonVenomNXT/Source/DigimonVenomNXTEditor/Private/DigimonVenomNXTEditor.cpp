#include "DigimonVenomNXTEditor.h"
#include "DigimonVenomNXTEditorLibrary.h"
#include "DigimonVenomNXTEditorMapPreview.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
#include "IToolMenusModule.h"
#include "Misc/MessageDialog.h"
#include "Framework/Commands/UIAction.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "Misc/PackageName.h"
#include "CoreGlobals.h"
#include "Misc/CoreDelegates.h"

namespace
{
bool OpenGeneratedWorld(const FString& PackageName, FString& Report)
{
    if (!GEditor || GEditor->PlayWorld)
    {
        Report = TEXT("Stop Play in Editor before opening a game level.");
        return false;
    }
    if (!FPackageName::DoesPackageExist(PackageName))
    {
        Report = TEXT("This game level has not been generated. Run Tools > Digimon Venom NXT: Build Complete Game Content first, then open the level again.");
        return false;
    }
    // The filename overload does not prompt before replacing the open level.
    // Keep the normal save/cancel boundary before requesting a map switch.
    if (!FEditorFileUtils::SaveDirtyPackages(true, true, false, false, false, false))
    {
        Report = TEXT("Opening the game level was cancelled. Your current level remains open.");
        return false;
    }
    const FString Filename = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetMapPackageExtension());
    if (!FEditorFileUtils::LoadMap(Filename, false, true))
    {
        Report = TEXT("The generated level could not be opened: ") + PackageName;
        return false;
    }
    if (PackageName.EndsWith(TEXT("/PublicWorld"))) DigimonVenomNXTEditorMapPreview::FocusFirstMap();
    Report = PackageName.EndsWith(TEXT("/MainMenu"))
        ? TEXT("MainMenu is open. Press Play to create or sign in to an account, then Host or Join the public world. Hosting settings are in Project Settings > Game > Digimon Venom NXT.")
        : TEXT("PublicWorld is open with the registered public map zones. Nearby and selected maps show their ground and foreground artwork. To start through account login and hosting, use Tools > Digimon Venom NXT: Open Main Menu, then press Play.");
    return true;
}
}

#define LOCTEXT_NAMESPACE "DigimonVenomNXTEditor"

void FDigimonVenomNXTEditorModule::StartupModule()
{
    // This module loads in Default so its reflected commandlet class is available
    // before Unreal resolves -run=. Commandlets must never start editor UI work.
    if (IsRunningCommandlet()) return;
    if (GIsRunning)
        InitializeEditor(); // A late module load after the one-shot engine event.
    else
        EngineInitHandle = FCoreDelegates::GetOnPostEngineInit().AddRaw(this, &FDigimonVenomNXTEditorModule::InitializeEditor);
}
void FDigimonVenomNXTEditorModule::InitializeEditor()
{
    FCoreDelegates::GetOnPostEngineInit().Remove(EngineInitHandle);
    EngineInitHandle.Reset();
    if (bInteractiveStarted || IsRunningCommandlet() || !GEditor) return;
    bInteractiveStarted = true;
    DigimonVenomNXTEditorMapPreview::Startup();
    MenuStartupHandle = UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDigimonVenomNXTEditorModule::RegisterMenus));
}
void FDigimonVenomNXTEditorModule::ShutdownModule()
{
    FCoreDelegates::GetOnPostEngineInit().Remove(EngineInitHandle);
    EngineInitHandle.Reset();
    if (bInteractiveStarted && IToolMenusModule::IsAvailable())
    {
        if (MenuStartupHandle.IsValid()) UToolMenus::UnRegisterStartupCallback(MenuStartupHandle);
        UToolMenus::UnregisterOwner(this);
    }
    MenuStartupHandle.Reset();
    if (bInteractiveStarted) DigimonVenomNXTEditorMapPreview::Shutdown();
    bInteractiveStarted = false;
}
void FDigimonVenomNXTEditorModule::RegisterMenus()
{
    FToolMenuOwnerScoped OwnerScoped(this);
    UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.MainMenu.Tools"));
    FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("DigimonVenomNXT"), LOCTEXT("Section", "Digimon Venom NXT"));
    auto Add = [&](const TCHAR* Id, const TCHAR* Label, const TCHAR* Tip, TFunction<bool(FString&)> Run)
    {
        Section.AddMenuEntry(FName(Id), FText::FromString(Label), FText::FromString(Tip), FSlateIcon(),
            FUIAction(FExecuteAction::CreateLambda([Run]()
            {
                FString Report;
                const bool bSuccess = Run(Report);
                UE_LOG(LogTemp, Display, TEXT("Digimon Venom NXT setup: %s"), *Report);
                FMessageDialog::Open(EAppMsgType::Ok, FText::FromString((bSuccess ? TEXT("COMPLETE\n\n") : TEXT("INCOMPLETE\n\n")) + Report));
            }), FCanExecuteAction::CreateLambda([]() { return GEditor && !GEditor->PlayWorld; })));
    };
    Add(TEXT("DVNXT_Complete"), TEXT("Digimon Venom NXT: Build Complete Game Content"),
        TEXT("Create MainMenu and PublicWorld, import or repair all game artwork and audio, configure login/hosting startup and verify packaging readiness. Saved assets are reused when their source is current; interrupted imports can be resumed."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::BuildCompleteGameContent(false, R); });
    Add(TEXT("DVNXT_OpenMainMenu"), TEXT("Digimon Venom NXT: Open Main Menu"),
        TEXT("Open the generated MainMenu level, then press Play for account creation, login, Host and Join. Prompts to save the open level first."),
        [](FString& R) { return OpenGeneratedWorld(TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu"), R); });
    Add(TEXT("DVNXT_OpenPublicWorld"), TEXT("Digimon Venom NXT: Open Public World"),
        TEXT("Open PublicWorld to inspect all registered map zones and their nearby/selected artwork. Start gameplay through MainMenu for the account and hosting flow."),
        [](FString& R) { return OpenGeneratedWorld(TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld"), R); });
    Add(TEXT("DVNXT_PrepareWorlds"), TEXT("Digimon Venom NXT: Create / Repair Main Menu + Public World"),
        TEXT("Create missing startup worlds and repair their native game modes, map-zone metadata and project startup settings. Full artwork import is still required before playing."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::PrepareGameWorlds(R); });
    Add(TEXT("DVNXT_Validate"), TEXT("Digimon Venom NXT: Validate Source Content"),
        TEXT("Check source files, hashes, map collision grids, frame pivots and animation dependencies without changing generated assets."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::ValidateBundledContent(R); });
    Add(TEXT("DVNXT_Import"), TEXT("Digimon Venom NXT: Import All Bundled Assets"),
        TEXT("Complete game setup: create startup levels, import every supplied Digimon variety, map, tamer, interface image and sound, then verify the playable-world configuration."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::ImportAllBundledAssets(false, R); });
    Add(TEXT("DVNXT_Tamers"), TEXT("Digimon Venom NXT: Import Tamer Roster"), TEXT("Repair all supplied tamer styles and their eight directional animations."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::ImportFullTamerRosterAssets(true, R); });
    Add(TEXT("DVNXT_Farm"), TEXT("Digimon Venom NXT: Prepare Private DigiFarm"),
        TEXT("Repair the private starting island and its presentation assets used after account login."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::PreparePrivateDigiFarm(R); });
    Add(TEXT("DVNXT_Maps"), TEXT("Digimon Venom NXT: Import Maps + Collision"), TEXT("Import all native maps, preserving exact source pixels and collision registration."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::ImportPlayableMapAssets(true, R); });
    Add(TEXT("DVNXT_UI"), TEXT("Digimon Venom NXT: Import Interface + Audio"), TEXT("Import all supplied Digimon interface artwork, battle effects, background music and sound effects."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::ImportPresentationPolishAssets(true, R); });
    Add(TEXT("DVNXT_Sprites"), TEXT("Digimon Venom NXT: Repair Digimon Animations"), TEXT("Repair native sprite alpha, pivots, flipbooks and animation sets for all varieties."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::RepairFieldSpriteRendering(R); });
    Add(TEXT("DVNXT_Startup"), TEXT("Digimon Venom NXT: Repair Packaged Startup"), TEXT("Repair startup, travel and cooking settings while preserving generated world content."),
        [](FString& R) { return UDigimonVenomNXTEditorLibrary::RepairPackagedStartup(R); });
}
IMPLEMENT_MODULE(FDigimonVenomNXTEditorModule, DigimonVenomNXTEditor)
#undef LOCTEXT_NAMESPACE
