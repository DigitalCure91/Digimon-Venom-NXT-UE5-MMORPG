#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DigimonVenomNXTEditorLibrary.generated.h"

/** Native Digimon setup. Worlds are prepared first; authored assets require verified source checksums. */
UCLASS()
class DIGIMONVENOMNXTEDITOR_API UDigimonVenomNXTEditorLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    /** Read-only verification of the complete source manifest and every dependency. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ValidateBundledContent(FString& OutReport);

    /** Complete setup: create worlds, import content and configure startup. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportCoreAssets(bool bReplaceExisting, FString& OutReport);

    /** Complete setup, including MainMenu/PublicWorld and startup configuration. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportAllBundledAssets(bool bReplaceExisting, FString& OutReport);

    /** Import every Firewall variety with original frame dimensions and timing. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportFirewallRosterAssets(bool bReplaceExisting, FString& OutReport);

    /** Import all supplied tamer appearances and eight-direction animations. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportFullTamerRosterAssets(bool bReplaceExisting, FString& OutReport);

    /** Import every registered map and save the matching collision completion marker. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportPlayableMapAssets(bool bReplaceExisting, FString& OutReport);

    /** Import all source Digimon interface imagery, effects and background music. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ImportPresentationPolishAssets(bool bReplaceExisting, FString& OutReport);

    /** Import missing source sound effects and repair non-looping playback. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool RepairSoundEffects(FString& OutReport);

    /** Import missing source background music and repair looping playback. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool RepairBackgroundMusic(FString& OutReport);

    /** Prepare the source private farm island and farm presentation. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool PreparePrivateDigiFarm(FString& OutReport);

    /** Repair every Digimon sprite, flipbook and animation set in place. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool RepairFieldSpriteRendering(FString& OutReport);

    /** Enable Custom Depth with Stencil and configure rendered level components. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ConfigureLevelCustomDepth(FString& OutReport);

    /** Create MainMenu and PublicWorld without switching the open editor level. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool BuildStarterLevels(bool bOverwriteExisting, FString& OutReport);

    /** Create or repair both worlds and startup settings without waiting for artwork import. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool PrepareGameWorlds(FString& OutReport);

    /** Read-only validation of saved worlds, native modes, map identities, start and imported map revision. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ValidateGameWorlds(FString& OutReport);

    /** Repair missing worlds, zone metadata, startup, travel and cooking. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool RepairPackagedStartup(FString& OutReport);

    /** Save native project startup and render configuration. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool ConfigureProjectForDigimonVenomNXT(FString& OutReport);

    /** Import all content, build worlds, configure the project and save a verified packaging receipt. */
    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Editor")
    static bool BuildCompleteGameContent(bool bReplaceExisting, FString& OutReport);

};
