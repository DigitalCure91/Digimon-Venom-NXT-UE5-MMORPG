#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTGameState.h"
#include "DigimonVenomNXTSettings.h"
#include "Engine/World.h"
#include "DigimonVenomNXTRuntime.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/Base64.h"
#include "Misc/SecureHash.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace
{
EDigimonAffinity ParseCombatAffinity(const FString& Value)
{
    if (Value == TEXT("Vaccine")) return EDigimonAffinity::Vaccine;
    if (Value == TEXT("Virus")) return EDigimonAffinity::Virus;
    if (Value == TEXT("Data")) return EDigimonAffinity::Data;
    return EDigimonAffinity::Free;
}
EDigimonElement ParseCombatElement(const FString& Value)
{
    if (Value == TEXT("Fire")) return EDigimonElement::Fire;
    if (Value == TEXT("Water")) return EDigimonElement::Water;
    if (Value == TEXT("Plant")) return EDigimonElement::Plant;
    if (Value == TEXT("Electric")) return EDigimonElement::Electric;
    if (Value == TEXT("Wind")) return EDigimonElement::Wind;
    if (Value == TEXT("Earth")) return EDigimonElement::Earth;
    if (Value == TEXT("Light")) return EDigimonElement::Light;
    if (Value == TEXT("Dark")) return EDigimonElement::Dark;
    return EDigimonElement::Neutral;
}
}

void UDigimonVenomNXTDataSubsystem::LoadCombatRegistry()
{
    MovesById.Reset();
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
    if (!Plugin.IsValid()) return;
    const FString Path = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources"), TEXT("DigimonCombat.json"));
    FString Text;
    TSharedPtr<FJsonObject> Root;
    if (!FFileHelper::LoadFileToString(Text, *Path) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root) || !Root.IsValid())
    {
        UE_LOG(LogDigimonVenomNXT, Error, TEXT("Could not load canonical combat registry: %s"), *Path);
        return;
    }
    const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
    if (!Root->TryGetArrayField(TEXT("moves"), Rows) || !Rows) return;
    for (const TSharedPtr<FJsonValue>& Value : *Rows)
    {
        const TSharedPtr<FJsonObject>* Obj = nullptr;
        if (!Value.IsValid() || !Value->TryGetObject(Obj) || !Obj) continue;
        FString Id, Name, Kind, Element;
        if (!(*Obj)->TryGetStringField(TEXT("moveId"), Id) || Id.IsEmpty()) continue;
        FDigimonMoveSlot Move;
        Move.MoveId = FName(*Id);
        (*Obj)->TryGetStringField(TEXT("displayName"), Name);
        Move.DisplayName = FText::FromString(Name.IsEmpty() ? Id : Name);
        (*Obj)->TryGetStringField(TEXT("description"), Move.Description);
        Move.Power = FMath::Clamp((*Obj)->GetIntegerField(TEXT("power")), 1, 300);
        Move.SPCost = FMath::Clamp((*Obj)->GetIntegerField(TEXT("spCost")), 0, 100);
        if ((*Obj)->HasField(TEXT("spCostPerRank")))
            Move.SPCostPerRank = FMath::Clamp((*Obj)->GetIntegerField(TEXT("spCostPerRank")), 0, 10);
        (*Obj)->TryGetBoolField(TEXT("usesSpeciesElement"), Move.bUsesSpeciesElement);
        (*Obj)->TryGetStringField(TEXT("damageClass"), Kind);
        (*Obj)->TryGetStringField(TEXT("element"), Element);
        Move.DamageClass = Kind == TEXT("Special") ? EDigimonDamageClass::Special : EDigimonDamageClass::Physical;
        Move.Element = ParseCombatElement(Element);
        MovesById.Add(Move.MoveId, Move);
    }
    UE_LOG(LogDigimonVenomNXT, Log, TEXT("Loaded %d canonical combat techniques."), MovesById.Num());
}

bool UDigimonVenomNXTDataSubsystem::GetMove(FName MoveId, FDigimonMoveSlot& OutMove) const
{
    if (const FDigimonMoveSlot* Move = MovesById.Find(MoveId)) { OutMove = *Move; return true; }
    return false;
}

void UDigimonVenomNXTDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LoadCombatRegistry();
    LoadBuiltInRegistry();
    LoadMapRegistry();
    LoadShopRegistry();
}

EDigimonStage UDigimonVenomNXTDataSubsystem::ParseStage(const FString& Stage)
{
    if (Stage.Equals(TEXT("Fresh"), ESearchCase::IgnoreCase)) return EDigimonStage::Fresh;
    if (Stage.Equals(TEXT("In-Training"), ESearchCase::IgnoreCase)) return EDigimonStage::InTraining;
    if (Stage.Equals(TEXT("Rookie"), ESearchCase::IgnoreCase)) return EDigimonStage::Rookie;
    if (Stage.Equals(TEXT("Champion"), ESearchCase::IgnoreCase)) return EDigimonStage::Champion;
    if (Stage.Equals(TEXT("Ultimate"), ESearchCase::IgnoreCase)) return EDigimonStage::Ultimate;
    if (Stage.Equals(TEXT("Mega"), ESearchCase::IgnoreCase)) return EDigimonStage::Mega;
    if (Stage.Equals(TEXT("Ultra"), ESearchCase::IgnoreCase)) return EDigimonStage::Ultra;
    if (Stage.Equals(TEXT("Armor"), ESearchCase::IgnoreCase)) return EDigimonStage::Armor;
    if (Stage.Equals(TEXT("Hybrid"), ESearchCase::IgnoreCase)) return EDigimonStage::Hybrid;
    return EDigimonStage::Unknown;
}

void UDigimonVenomNXTDataSubsystem::LoadBuiltInRegistry()
{
    SpeciesById.Reset();
    DeEvolutionSourcesById.Reset();
    ProvidedSpeciesCount = 0;
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
    if (!Plugin.IsValid())
    {
        UE_LOG(LogDigimonVenomNXT, Error, TEXT("Unable to locate DigimonVenomNXT plugin base directory."));
        return;
    }
    const FString Path = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources"), TEXT("DigimonSpecies.json"));
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *Path))
    {
        UE_LOG(LogDigimonVenomNXT, Error, TEXT("Could not load species registry: %s"), *Path);
        return;
    }
    TSharedPtr<FJsonObject> Root;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) return;
    ProvidedSpeciesCount = Root->GetIntegerField(TEXT("providedSpecies"));
    const TArray<TSharedPtr<FJsonValue>>* SpeciesArray = nullptr;
    if (!Root->TryGetArrayField(TEXT("species"), SpeciesArray) || !SpeciesArray) return;

    for (const TSharedPtr<FJsonValue>& Value : *SpeciesArray)
    {
        const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
        if (!Value->TryGetObject(ObjPtr) || !ObjPtr) continue;
        const TSharedPtr<FJsonObject>& Obj = *ObjPtr;
        FDigimonSpeciesDefinition Def;
        Def.SpeciesId = FName(*Obj->GetStringField(TEXT("speciesId")));
        Def.DisplayName = FText::FromString(Obj->GetStringField(TEXT("displayName")));
        Def.Stage = ParseStage(Obj->GetStringField(TEXT("stage")));
        FString Affinity, Element;
        Obj->TryGetStringField(TEXT("affinity"), Affinity);
        Obj->TryGetStringField(TEXT("element"), Element);
        Obj->TryGetStringField(TEXT("combatRole"), Def.CombatRole);
        Def.Affinity = ParseCombatAffinity(Affinity);
        Def.Element = ParseCombatElement(Element);
        Def.bHasNormalArtwork = Obj->GetBoolField(TEXT("hasNormalArtwork"));
        Def.bHasParadoxArtwork = Obj->GetBoolField(TEXT("hasParadoxArtwork"));
        Def.bHasShinyArtwork = Obj->GetBoolField(TEXT("hasShinyArtwork"));
        // Optional for older/custom registries; only supplied forms are advertised.
        Obj->TryGetBoolField(TEXT("hasFirewallArtwork"), Def.bHasFirewallArtwork);
        Def.bPlaceholder = Obj->GetBoolField(TEXT("placeholder"));
        const TSharedPtr<FJsonObject>* Stats = nullptr;
        if (Obj->TryGetObjectField(TEXT("baseStats"), Stats) && Stats)
        {
            Def.BaseStats.MaxHP = (*Stats)->GetIntegerField(TEXT("maxHP"));
            Def.BaseStats.MaxSP = (*Stats)->GetIntegerField(TEXT("maxSP"));
            Def.BaseStats.Attack = (*Stats)->GetIntegerField(TEXT("attack"));
            Def.BaseStats.Defense = (*Stats)->GetIntegerField(TEXT("defense"));
            Def.BaseStats.Spirit = (*Stats)->GetIntegerField(TEXT("spirit"));
            Def.BaseStats.Speed = (*Stats)->GetIntegerField(TEXT("speed"));
        }

        const TArray<TSharedPtr<FJsonValue>>* Moves = nullptr;
        if (Obj->TryGetArrayField(TEXT("learnableMoves"), Moves) && Moves)
        {
            for (const TSharedPtr<FJsonValue>& MoveValue : *Moves)
            {
                FString Move;
                if (MoveValue.IsValid() && MoveValue->TryGetString(Move)) Def.LearnableMoves.Add(FName(*Move));
            }
        }

        const TArray<TSharedPtr<FJsonValue>>* Evolutions = nullptr;
        if (Obj->TryGetArrayField(TEXT("evolutions"), Evolutions) && Evolutions)
        {
            for (const TSharedPtr<FJsonValue>& EvoValue : *Evolutions)
            {
                const TSharedPtr<FJsonObject>* EvoObjPtr = nullptr;
                if (!EvoValue->TryGetObject(EvoObjPtr) || !EvoObjPtr) continue;
                const TSharedPtr<FJsonObject>& EvoObj = *EvoObjPtr;
                FDigimonEvolutionRequirement R;
                R.TargetSpeciesId = FName(*EvoObj->GetStringField(TEXT("targetSpeciesId")));
                R.RequiredLevel = EvoObj->GetIntegerField(TEXT("requiredLevel"));
                R.RequiredCAM = EvoObj->GetIntegerField(TEXT("requiredCAM"));
                R.RequiredABI = EvoObj->GetIntegerField(TEXT("requiredABI"));
                R.RequiredAttack = EvoObj->GetIntegerField(TEXT("requiredAttack"));
                R.RequiredDefense = EvoObj->GetIntegerField(TEXT("requiredDefense"));
                R.RequiredSpirit = EvoObj->GetIntegerField(TEXT("requiredSpirit"));
                R.RequiredSpeed = EvoObj->GetIntegerField(TEXT("requiredSpeed"));
                Def.Evolutions.Add(R);
            }
        }
        SpeciesById.Add(Def.SpeciesId, Def);
    }
    // Build once per registry load; bot and UI previews must not copy/sort the
    // entire species database every time a single partner considers devolving.
    for (const TPair<FName, FDigimonSpeciesDefinition>& Pair : SpeciesById)
    {
        const FDigimonSpeciesDefinition& From = Pair.Value;
        if (From.bPlaceholder) continue;
        for (const FDigimonEvolutionRequirement& Route : From.Evolutions)
        {
            const FDigimonSpeciesDefinition* To = SpeciesById.Find(Route.TargetSpeciesId);
            if (!To || To->bPlaceholder || To->SpeciesId == From.SpeciesId) continue;
            DeEvolutionSourcesById.FindOrAdd(To->SpeciesId).AddUnique(From.SpeciesId);
        }
    }
    for (TPair<FName, TArray<FName>>& Pair : DeEvolutionSourcesById)
        Pair.Value.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
    UE_LOG(LogDigimonVenomNXT, Log, TEXT("Loaded %d species slots (%d supplied art/name manifests)."), SpeciesById.Num(), ProvidedSpeciesCount);
}

bool UDigimonVenomNXTDataSubsystem::GetSpecies(FName SpeciesId, FDigimonSpeciesDefinition& OutSpecies) const
{
    if (const FDigimonSpeciesDefinition* Found = SpeciesById.Find(SpeciesId)) { OutSpecies = *Found; return true; }
    return false;
}

TArray<FDigimonSpeciesDefinition> UDigimonVenomNXTDataSubsystem::GetAllSpecies() const
{
    TArray<FDigimonSpeciesDefinition> Out;
    SpeciesById.GenerateValueArray(Out);
    Out.Sort([](const FDigimonSpeciesDefinition& A, const FDigimonSpeciesDefinition& B){ return A.SpeciesId.LexicalLess(B.SpeciesId); });
    return Out;
}

TArray<FDigimonSpeciesDefinition> UDigimonVenomNXTDataSubsystem::GetDeEvolutionSources(FName SpeciesId) const
{
    TArray<FDigimonSpeciesDefinition> Out;
    if (const TArray<FName>* Sources = DeEvolutionSourcesById.Find(SpeciesId))
    {
        Out.Reserve(Sources->Num());
        for (const FName& Source : *Sources)
            if (const FDigimonSpeciesDefinition* Definition = SpeciesById.Find(Source)) Out.Add(*Definition);
    }
    return Out;
}

TArray<FDigimonSpeciesDefinition> UDigimonVenomNXTDataSubsystem::GetStarterCandidates(int32 MaxResults) const
{
    TArray<FDigimonSpeciesDefinition> All = GetAllSpecies();
    TArray<FDigimonSpeciesDefinition> Out;
    for (const FDigimonSpeciesDefinition& Def : All)
    {
        if (Def.Stage == EDigimonStage::Rookie && !Def.bPlaceholder)
        {
            Out.Add(Def);
            if (Out.Num() >= FMath::Max(1, MaxResults)) break;
        }
    }
    return Out;
}


void UDigimonVenomNXTDataSubsystem::LoadMapRegistry()
{
    MapsById.Reset();
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
    if (!Plugin.IsValid()) return;

    const FString Path = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources"), TEXT("DigimonMaps.json"));
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *Path))
    {
        UE_LOG(LogDigimonVenomNXT, Error, TEXT("Could not load map registry: %s"), *Path);
        return;
    }

    TSharedPtr<FJsonObject> Root;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) return;
    const TArray<TSharedPtr<FJsonValue>>* MapArray = nullptr;
    if (!Root->TryGetArrayField(TEXT("maps"), MapArray) || !MapArray) return;

    for (const TSharedPtr<FJsonValue>& Value : *MapArray)
    {
        const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
        if (!Value->TryGetObject(ObjPtr) || !ObjPtr) continue;
        const TSharedPtr<FJsonObject>& Obj = *ObjPtr;
        FDigimonMapRow Row;
        Row.MapId = Obj->GetIntegerField(TEXT("mapId"));
        Row.DisplayName = FText::FromString(Obj->GetStringField(TEXT("displayName")));
        const int32 Region = Obj->GetIntegerField(TEXT("region"));
        Row.Region = Region == 2 ? EDigimonRegion::RegionTwo : Region == 3 ? EDigimonRegion::RegionThree : EDigimonRegion::RegionOne;
        Row.RecommendedMinLevel = Obj->GetIntegerField(TEXT("recommendedMinLevel"));
        Row.RecommendedMaxLevel = Obj->GetIntegerField(TEXT("recommendedMaxLevel"));
        if (!Obj->TryGetStringField(TEXT("groundSource"), Row.SourceImageRelativePath))
        {
            Obj->TryGetStringField(TEXT("sourceImage"), Row.SourceImageRelativePath);
        }
        Obj->TryGetStringField(TEXT("collisionSource"), Row.CollisionSourceImageRelativePath);
        Obj->TryGetBoolField(TEXT("collisionDerivedFromGround"), Row.bCollisionDerivedFromGround);
        Row.SourceWidth = Obj->HasField(TEXT("sourceWidth")) ? Obj->GetIntegerField(TEXT("sourceWidth")) : 0;
        Row.SourceHeight = Obj->HasField(TEXT("sourceHeight")) ? Obj->GetIntegerField(TEXT("sourceHeight")) : 0;
        Row.WalkGridWidth = Obj->HasField(TEXT("walkGridWidth")) ? Obj->GetIntegerField(TEXT("walkGridWidth")) : 0;
        Row.WalkGridHeight = Obj->HasField(TEXT("walkGridHeight")) ? Obj->GetIntegerField(TEXT("walkGridHeight")) : 0;
        FString WalkBits;
        if (Obj->TryGetStringField(TEXT("walkGridBits"), WalkBits) && !WalkBits.IsEmpty())
        {
            FBase64::Decode(WalkBits, Row.WalkGridBits);
        }
        double SafeSpawnU = 0.5;
        double SafeSpawnV = 0.5;
        Obj->TryGetNumberField(TEXT("safeSpawnU"), SafeSpawnU);
        Obj->TryGetNumberField(TEXT("safeSpawnV"), SafeSpawnV);
        Row.SafeSpawnUV = FVector2D(
            FMath::Clamp(static_cast<float>(SafeSpawnU), 0.0f, 1.0f),
            FMath::Clamp(static_cast<float>(SafeSpawnV), 0.0f, 1.0f));
        FString ImportedTexture;
        if (Obj->TryGetStringField(TEXT("importedTexture"), ImportedTexture) && !ImportedTexture.IsEmpty())
        {
            const FString AssetName = FPaths::GetBaseFilename(ImportedTexture);
            Row.GroundTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(ImportedTexture + TEXT(".") + AssetName));
        }
        FString ExplorationAsset;
        if (Obj->TryGetStringField(TEXT("explorationBgmAsset"), ExplorationAsset) && !ExplorationAsset.IsEmpty())
            Row.ExplorationMusic = TSoftObjectPtr<USoundBase>(FSoftObjectPath(ExplorationAsset));
        FString BattleAsset;
        if (Obj->TryGetStringField(TEXT("battleBgmAsset"), BattleAsset) && !BattleAsset.IsEmpty())
            Row.BattleMusic = TSoftObjectPtr<USoundBase>(FSoftObjectPath(BattleAsset));
        const auto ReadSpeciesPool = [&Obj](const TCHAR* Key, TArray<FName>& Pool)
        {
            const TArray<TSharedPtr<FJsonValue>>* Values = nullptr;
            if (!Obj->TryGetArrayField(Key, Values) || !Values) return;
            for (const TSharedPtr<FJsonValue>& SpeciesValue : *Values)
            {
                FString Species;
                if (SpeciesValue.IsValid() && SpeciesValue->TryGetString(Species) && !Species.IsEmpty()) Pool.Add(FName(*Species));
            }
        };
        ReadSpeciesPool(TEXT("wildSpecies"), Row.WildSpecies);
        ReadSpeciesPool(TEXT("paradoxSpecies"), Row.ParadoxSpecies);
        ReadSpeciesPool(TEXT("shinySpecies"), Row.ShinySpecies);
        ReadSpeciesPool(TEXT("firewallSpecies"), Row.FirewallSpecies);
        MapsById.Add(Row.MapId, Row);
    }
    UE_LOG(LogDigimonVenomNXT, Log, TEXT("Loaded %d public atlas map rows."), MapsById.Num());
}

bool UDigimonVenomNXTDataSubsystem::GetMap(int32 MapId, FDigimonMapRow& OutMap) const
{
    if (const FDigimonMapRow* Found = FindMap(MapId)) { OutMap = *Found; return true; }
    return false;
}

const FDigimonMapRow* UDigimonVenomNXTDataSubsystem::FindMap(int32 MapId) const
{
    return MapsById.Find(MapId);
}



TArray<FDigimonMapRow> UDigimonVenomNXTDataSubsystem::GetAllMaps() const
{
    TArray<FDigimonMapRow> Out;
    MapsById.GenerateValueArray(Out);
    Out.Sort([](const FDigimonMapRow& A, const FDigimonMapRow& B){ return A.MapId < B.MapId; });
    return Out;
}

void UDigimonVenomNXTDataSubsystem::LoadShopRegistry()
{
    ShopItems.Reset();
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
    FString Text;
    TSharedPtr<FJsonObject> Root;
    const TArray<TSharedPtr<FJsonValue>>* Items = nullptr;
    if (!Plugin.IsValid() || !FFileHelper::LoadFileToString(Text, *FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources/DigimonShop.json"))) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root) || !Root.IsValid() ||
        !Root->TryGetArrayField(TEXT("items"), Items) || !Items)
    { UE_LOG(LogDigimonVenomNXT, Error, TEXT("Digimon shop registry could not be loaded.")); return; }
    TSet<FName> Seen;
    for (const TSharedPtr<FJsonValue>& Value : *Items)
    {
        const TSharedPtr<FJsonObject>* Obj = nullptr;
        if (!Value.IsValid() || !Value->TryGetObject(Obj) || !Obj) continue;
        FString Id, Name, Description, Resource, Category;
        double Credits = 0, Rubies = 0, Amount = 0;
        if (!(*Obj)->TryGetStringField(TEXT("itemId"), Id) || Id.IsEmpty() || Seen.Contains(FName(*Id)) ||
            !(*Obj)->TryGetNumberField(TEXT("creditCost"), Credits) || !FMath::IsFinite(Credits) || Credits < 1 || Credits > MAX_int32 ||
            !(*Obj)->TryGetNumberField(TEXT("digiRubyCost"), Rubies) || !FMath::IsFinite(Rubies) || Rubies < 1 || Rubies > MAX_int32 ||
            !(*Obj)->TryGetNumberField(TEXT("amount"), Amount) || Amount < 1 || Amount > MAX_int32) continue;
        (*Obj)->TryGetStringField(TEXT("displayName"), Name);
        (*Obj)->TryGetStringField(TEXT("description"), Description);
        (*Obj)->TryGetStringField(TEXT("resource"), Resource);
        (*Obj)->TryGetStringField(TEXT("category"), Category);
        FDigimonShopItemDefinition Item;
        Item.ItemId = FName(*Id); Item.DisplayName = FText::FromString(Name); Item.Description = FText::FromString(Description);
        Item.CreditCost = static_cast<int64>(Credits); Item.DigiRubyCost = static_cast<int32>(Rubies);
        Item.Resource = FName(*Resource); Item.Category = FName(*Category); Item.Amount = static_cast<int32>(Amount);
        Item.HPHeal = Resource == TEXT("hp") && Category != TEXT("digimeat") ? Item.Amount : 0;
        Item.SPHeal = Resource == TEXT("sp") && Category != TEXT("digimeat") ? Item.Amount : 0;
        Item.CAMGain = Resource == TEXT("cam") ? Item.Amount : 0;
        Item.bABIMeat = Resource == TEXT("abi");
        Item.TrainingGain = Category == TEXT("digimeat") && !Item.bABIMeat && !Item.CAMGain ? Item.Amount : 0;
        Seen.Add(Item.ItemId); ShopItems.Add(Item);
    }
}

TArray<FDigimonShopItemDefinition> UDigimonVenomNXTDataSubsystem::GetShopItems() const
{
    TArray<FDigimonShopItemDefinition> Result;
    Result.Reserve(ShopItems.Num());
    for (const FDigimonShopItemDefinition& Base : ShopItems)
    {
        FDigimonShopItemDefinition Item;
        if (GetShopItem(Base.ItemId, Item)) Result.Add(Item);
    }
    return Result;
}
bool UDigimonVenomNXTDataSubsystem::GetShopItem(FName ItemId, FDigimonShopItemDefinition& OutItem) const
{
    if (const UWorld* World = GetWorld(); World && World->GetNetMode() == NM_Client)
    {
        const ADigimonVenomNXTGameState* State = World->GetGameState<ADigimonVenomNXTGameState>();
        const FDigimonShopItemDefinition* Effective = State ? State->ShopCatalog.FindByPredicate(
            [ItemId](const FDigimonShopItemDefinition& Row) { return Row.ItemId == ItemId; }) : nullptr;
        if (!Effective) return false; // Wait for the host's prices; never display a client override.
        OutItem = *Effective;
        return true;
    }
    const FDigimonShopItemDefinition* Item = ShopItems.FindByPredicate([ItemId](const FDigimonShopItemDefinition& Row) { return Row.ItemId == ItemId; });
    if (!Item) return false;
    OutItem = *Item;
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    if (ItemId == FName(TEXT("hp_s")))
    { OutItem.CreditCost = Settings->SmallHPCapsuleCreditCost; OutItem.DigiRubyCost = Settings->SmallHPCapsuleRubyCost; }
    else if (ItemId == FName(TEXT("sp_s")))
    { OutItem.CreditCost = Settings->SmallSPCapsuleCreditCost; OutItem.DigiRubyCost = Settings->SmallSPCapsuleRubyCost; }
    else if (ItemId == FName(TEXT("digimeat_cam")))
    { OutItem.CreditCost = Settings->CAMMeatCreditCost; OutItem.DigiRubyCost = Settings->CAMMeatRubyCost; OutItem.CAMGain = FMath::Clamp(Settings->CAMMeatGain, 1, 100); OutItem.Amount = OutItem.CAMGain; }
    else if (ItemId == FName(TEXT("digimeat_abi")))
    { OutItem.CreditCost = Settings->ABIMeatCreditCost; OutItem.DigiRubyCost = Settings->ABIMeatRubyCost; OutItem.Amount = FMath::Clamp(Settings->ABIMeatGain, 1, 200); }
    else if (Item->TrainingGain == 1)
    { OutItem.CreditCost = Settings->DigiMeatCreditCost; OutItem.DigiRubyCost = Settings->DigiMeatRubyCost; }
    if (const int32* Override = Settings->ShopCreditPriceOverrides.Find(ItemId)) OutItem.CreditCost = *Override;
    if (const int32* Override = Settings->ShopDigiRubyPriceOverrides.Find(ItemId)) OutItem.DigiRubyCost = *Override;
    OutItem.CreditCost = FMath::Clamp<int64>(OutItem.CreditCost, 1, MAX_int32);
    OutItem.DigiRubyCost = FMath::Clamp(OutItem.DigiRubyCost, 0, MAX_int32);
    return true;
}

int32 UDigimonVenomNXTDataSubsystem::GetCreditsPerDigiRuby() const
{
    if (const UWorld* World = GetWorld(); World && World->GetNetMode() == NM_Client)
        if (const ADigimonVenomNXTGameState* State = World->GetGameState<ADigimonVenomNXTGameState>()) return FMath::Clamp(State->CreditsPerDigiRuby, 1, 100000);
    return FMath::Clamp(GetDefault<UDigimonVenomNXTSettings>()->CreditsPerDigiRuby, 1, 100000);
}
