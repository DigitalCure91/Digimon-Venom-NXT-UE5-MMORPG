#include "DigimonVenomNXTProfileValidation.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool DigimonVenomNXTProfileValidation::Validate(const FDigimonPlayerProfile& Profile, const FString& ExpectedAccountId, FString& Error)
{
    Error.Reset();
    if (ExpectedAccountId.IsEmpty() || Profile.AccountId != ExpectedAccountId || Profile.Username.IsEmpty())
    {
        Error = TEXT("Profile identity is missing or does not match the authenticated account.");
        return false;
    }
    if (Profile.WorldBattleCheckpointJson.Len() > 1024 * 1024)
    {
        Error = TEXT("The saved wild battle checkpoint exceeds its supported size. Existing progress is preserved.");
        return false;
    }
    TSet<FGuid> Owned;
    for (const FDigimonOwnedPartner& Partner : Profile.Collection)
    {
        if (!Partner.IsValid() || Owned.Contains(Partner.InstanceId))
        {
            Error = TEXT("The collection contains a missing or duplicate partner identity.");
            return false;
        }
        Owned.Add(Partner.InstanceId);
    }
    TSet<FGuid> Party;
    for (const FGuid& Id : Profile.Party)
    {
        if (!Owned.Contains(Id) || Party.Contains(Id))
        {
            Error = TEXT("A party member is missing from the collection or appears more than once.");
            return false;
        }
        Party.Add(Id);
    }
    if (Profile.CommerceRevision < 0 || Profile.DigiLabRecoveryRevision < 0)
    {
        Error = TEXT("Profile transaction revisions are invalid.");
        return false;
    }
    return true;
}

bool DigimonVenomNXTProfileValidation::HasRequiredJsonFields(const FString& Json)
{
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json), Root) || !Root.IsValid()) return false;
    // These four fields predate Season/Ranked. Newer optional fields may still
    // migrate normally, but a truncated/default object must not pass as an account.
    FString Account, Username;
    const TArray<TSharedPtr<FJsonValue>>* Collection = nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Party = nullptr;
    return (Root->TryGetStringField(TEXT("accountId"), Account) || Root->TryGetStringField(TEXT("AccountId"), Account)) &&
        !Account.IsEmpty() &&
        (Root->TryGetStringField(TEXT("username"), Username) || Root->TryGetStringField(TEXT("Username"), Username)) &&
        !Username.IsEmpty() &&
        (Root->TryGetArrayField(TEXT("collection"), Collection) || Root->TryGetArrayField(TEXT("Collection"), Collection)) &&
        (Root->TryGetArrayField(TEXT("party"), Party) || Root->TryGetArrayField(TEXT("Party"), Party));
}
