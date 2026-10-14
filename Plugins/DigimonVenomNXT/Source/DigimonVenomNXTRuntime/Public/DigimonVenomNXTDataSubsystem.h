#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTDataSubsystem.generated.h"

UCLASS(BlueprintType)
class DIGIMONVENOMNXTRUNTIME_API UDigimonVenomNXTDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    bool GetSpecies(FName SpeciesId, FDigimonSpeciesDefinition& OutSpecies) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    TArray<FDigimonSpeciesDefinition> GetAllSpecies() const;

    /** Canonical moves override old serialized power/cost values without changing equipped IDs. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    bool GetMove(FName MoveId, FDigimonMoveSlot& OutMove) const;

    /** Indexed reverse routes: only linked, supplied species are returned. */
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    TArray<FDigimonSpeciesDefinition> GetDeEvolutionSources(FName SpeciesId) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    TArray<FDigimonSpeciesDefinition> GetStarterCandidates(int32 MaxResults = 12) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    int32 GetProvidedSpeciesCount() const { return ProvidedSpeciesCount; }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    bool GetMap(int32 MapId, FDigimonMapRow& OutMap) const;

    /** Immutable registry view for collision hot paths; valid for this subsystem's lifetime. */
    const FDigimonMapRow* FindMap(int32 MapId) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    TArray<FDigimonMapRow> GetAllMaps() const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    int32 GetPublicMapCount() const { return MapsById.Num(); }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    int32 GetConfiguredSpeciesCapacity() const { return SpeciesById.Num(); }

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    TArray<FDigimonShopItemDefinition> GetShopItems() const;
    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    bool GetShopItem(FName ItemId, FDigimonShopItemDefinition& OutItem) const;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Data")
    int32 GetCreditsPerDigiRuby() const;

private:
    TArray<FDigimonShopItemDefinition> ShopItems;
    void LoadShopRegistry();
    TMap<FName, FDigimonSpeciesDefinition> SpeciesById;
    TMap<FName, FDigimonMoveSlot> MovesById;
    TMap<FName, TArray<FName>> DeEvolutionSourcesById;
    TMap<int32, FDigimonMapRow> MapsById;
    int32 ProvidedSpeciesCount = 0;
    void LoadBuiltInRegistry();
    void LoadMapRegistry();
    void LoadCombatRegistry();
    static EDigimonStage ParseStage(const FString& Stage);
};
