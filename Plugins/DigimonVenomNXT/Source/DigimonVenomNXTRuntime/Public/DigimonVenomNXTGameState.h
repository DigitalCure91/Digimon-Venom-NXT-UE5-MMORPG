#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigimonServerStateChanged);

/** Small, public server summary. Private player profiles live on PlayerState with owner-only replication. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTGameState : public AGameStateBase
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTGameState();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Server")
    FString ServerDisplayName = TEXT("Digimon Venom NXT Public World");

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Server")
    int32 MaxPlayers = 100;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Server")
    int32 AtlasMapCount = 500;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Server")
    int32 PersistentAIRivalCount = 0;

    /** Public effective economy; hosting secrets never enter replicated state. */
    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Economy")
    TArray<FDigimonShopItemDefinition> ShopCatalog;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Economy")
    int32 CreditsPerDigiRuby = 100;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Ranked")
    FString RankedSeasonId;

    UPROPERTY(ReplicatedUsing=OnRep_ServerState, BlueprintReadOnly, Category="Digimon Venom NXT|Ranked")
    TArray<FDigimonRankedPublicEntry> RankedTop100;

    UPROPERTY(BlueprintAssignable, Category="Digimon Venom NXT|Server")
    FDigimonServerStateChanged OnServerStateChanged;

    UFUNCTION(BlueprintPure, Category="Digimon Venom NXT|Server")
    int32 GetOnlinePlayerCount() const { return PlayerArray.Num(); }

    void InitializeFromSettings();
    void SetPersistentAIRivalCount(int32 Count);
    void SetRankedSeasonId(const FString& InSeasonId);
    void SetRankedTop100(const TArray<FDigimonRankedPublicEntry>& InEntries);

protected:
    UFUNCTION() void OnRep_ServerState();
};
