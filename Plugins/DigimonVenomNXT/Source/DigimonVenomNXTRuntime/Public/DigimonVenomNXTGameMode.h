#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTGameMode.generated.h"

class ADigimonVenomNXTPlayerController;
class ADigimonVenomNXTBattleActor;
class ADigimonVenomNXTPlayerState;

/** Authoritative public-world rules, authentication gate, autosave and battle factory. */
UCLASS(BlueprintType, Blueprintable)
class DIGIMONVENOMNXTRUNTIME_API ADigimonVenomNXTGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ADigimonVenomNXTGameMode();
    virtual void BeginPlay() override;
    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;


    /** Called only by the connected player's server RPC. Validates/creates the account from the host UE SaveGame and spawns gameplay only after success. */
    bool AuthenticatePlayer(ADigimonVenomNXTPlayerController* Controller, bool bCreateAccount, const FString& Username, const FString& Password,
        FString& OutUsername, FString& OutAccountId, FString& OutError);
    /** Authenticated server-world channel; independent of habitat, pawn and private instance. */
    int32 BroadcastWorldChat(const FDigimonChatMessage& Message, const ADigimonVenomNXTPlayerController* Excluded = nullptr);
    void JoinWorldChat(ADigimonVenomNXTPlayerController* Controller);
    void LeaveWorldChat(ADigimonVenomNXTPlayerController* Controller);

    /** Read-only native battle factory configuration, with the standard actor as a safe fallback. */
    UClass* GetBattleActorClass() const;

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    ADigimonVenomNXTBattleActor* StartWildBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError);


    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Battle")
    ADigimonVenomNXTBattleActor* StartAIRivalBattleFor(ADigimonVenomNXTPlayerController* Controller, const FString& RivalId, FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Season")
    ADigimonVenomNXTBattleActor* StartSeasonBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Story")
    ADigimonVenomNXTBattleActor* StartStoryBossBattleFor(ADigimonVenomNXTPlayerController* Controller, int32 Chapter, FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Story")
    ADigimonVenomNXTBattleActor* StartFinalStoryBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError);

    /** All private campaign factories validate the authenticated owner's current private scene. */
    bool InteractRelayNPCFor(ADigimonVenomNXTPlayerController* Controller, FName NPCId, FString& OutError, bool bAdvanceQuest = false);
    ADigimonVenomNXTBattleActor* StartRelayBattleFor(ADigimonVenomNXTPlayerController* Controller, FName NPCId, FString& OutError);
    ADigimonVenomNXTBattleActor* StartRelayFieldTrainingFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError);
    ADigimonVenomNXTBattleActor* ResumeRelayBattleFor(ADigimonVenomNXTPlayerController* Controller, FString& OutError);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    bool SavePlayer(ADigimonVenomNXTPlayerState* PlayerState, bool bAllowAutomaticWrite = true);

    /** Called once after the owner acknowledges a complete profile (directly for the listen host). */
    void FinishAuthenticatedPlayerLogin(ADigimonVenomNXTPlayerController* Controller);

    UFUNCTION(BlueprintCallable, Category="Digimon Venom NXT|Persistence")
    void SaveAllPlayers();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Digimon Venom NXT|Battle")
    TSubclassOf<ADigimonVenomNXTBattleActor> BattleActorClass;

private:
    TMap<TWeakObjectPtr<ADigimonVenomNXTPlayerController>, FString> WorldChatMembers;
    FTimerHandle AutosaveTimer;
    FTimerHandle RankedRefreshTimer;
    void RefreshRankedSeason();
};
