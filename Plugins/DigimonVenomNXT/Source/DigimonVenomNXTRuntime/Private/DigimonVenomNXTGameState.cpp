#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "Engine/GameInstance.h"
#include "Net/UnrealNetwork.h"

ADigimonVenomNXTGameState::ADigimonVenomNXTGameState()
{
    SetNetUpdateFrequency(2.0f);
}

void ADigimonVenomNXTGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADigimonVenomNXTGameState, ServerDisplayName);
    DOREPLIFETIME(ADigimonVenomNXTGameState, MaxPlayers);
    DOREPLIFETIME(ADigimonVenomNXTGameState, AtlasMapCount);
    DOREPLIFETIME(ADigimonVenomNXTGameState, PersistentAIRivalCount);
    DOREPLIFETIME(ADigimonVenomNXTGameState, RankedSeasonId);
    DOREPLIFETIME(ADigimonVenomNXTGameState, RankedTop100);
    DOREPLIFETIME(ADigimonVenomNXTGameState, ShopCatalog);
    DOREPLIFETIME(ADigimonVenomNXTGameState, CreditsPerDigiRuby);
}

void ADigimonVenomNXTGameState::InitializeFromSettings()
{
    if (!HasAuthority()) return;
    const UDigimonVenomNXTSettings* S = GetDefault<UDigimonVenomNXTSettings>();
    ServerDisplayName = S->ServerDisplayName;
    MaxPlayers = S->MaxPlayers;
    const UDigimonVenomNXTDataSubsystem* Data = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTDataSubsystem>() : nullptr;
    AtlasMapCount = Data ? Data->GetPublicMapCount() : S->PublicAtlasMapCount;
    ShopCatalog = Data ? Data->GetShopItems() : TArray<FDigimonShopItemDefinition>();
    CreditsPerDigiRuby = FMath::Clamp(S->CreditsPerDigiRuby, 1, 100000);
    ForceNetUpdate();
}

void ADigimonVenomNXTGameState::SetPersistentAIRivalCount(int32 Count)
{
    if (!HasAuthority()) return;
    PersistentAIRivalCount = FMath::Max(0, Count);
    ForceNetUpdate();
}

void ADigimonVenomNXTGameState::SetRankedSeasonId(const FString& InSeasonId)
{
    if (!HasAuthority()) return;
    RankedSeasonId = InSeasonId;
    ForceNetUpdate();
    OnServerStateChanged.Broadcast();
}

void ADigimonVenomNXTGameState::SetRankedTop100(const TArray<FDigimonRankedPublicEntry>& InEntries)
{
    if (!HasAuthority()) return;
    RankedTop100 = InEntries;
    ForceNetUpdate();
    OnServerStateChanged.Broadcast();
}

void ADigimonVenomNXTGameState::OnRep_ServerState()
{
    OnServerStateChanged.Broadcast();
}
