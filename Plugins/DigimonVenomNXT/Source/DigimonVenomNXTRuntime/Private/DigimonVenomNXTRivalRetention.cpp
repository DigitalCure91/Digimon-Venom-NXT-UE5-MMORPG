#include "DigimonVenomNXTRivalRetention.h"
#include "DigimonVenomNXTDataSubsystem.h"
#include "DigimonVenomNXTScanCore.h"
#include "DigimonVenomNXTSettings.h"
#include "UObject/Class.h"

namespace
{
    struct FScanKey
    {
        FName SpeciesId;
        EDigimonVariant Variant = EDigimonVariant::Normal;
        bool operator==(const FScanKey& Other) const { return SpeciesId == Other.SpeciesId && Variant == Other.Variant; }
        friend uint32 GetTypeHash(const FScanKey& Key) { return HashCombine(GetTypeHash(Key.SpeciesId), static_cast<uint32>(Key.Variant)); }
    };

    bool ValidName(FName Name) { return !Name.IsNone() && Name.ToString().Len() <= 128; }
    bool ValidVariant(EDigimonVariant Variant) { return static_cast<uint8>(Variant) <= static_cast<uint8>(EDigimonVariant::Firewall); }

    bool TrimText(FString& Text, int32 Limit)
    {
        if (Text.Len() <= Limit) return false;
        Text.LeftInline(Limit);
        Text.Shrink();
        return true;
    }

    bool PruneMoves(FDigimonOwnedPartner& Partner)
    {
        bool bChanged = TrimText(Partner.Nickname, 64);
        // Combat has always used at most four IDs and resolves all metadata from the catalog.
        // Do not keep copies of localized descriptions inside every persistent AI creature.
        if (Partner.Moves.Num() > 4) { Partner.Moves.SetNum(4); bChanged = true; }
        // Repeated equipped IDs are legal slots. Preserve their order and multiplicity.
        const int32 Removed = Partner.Moves.RemoveAll([](const FDigimonMoveSlot& Move)
        {
            return !ValidName(Move.MoveId);
        });
        bChanged |= Removed > 0;
        for (FDigimonMoveSlot& Move : Partner.Moves)
        {
            if (!Move.DisplayName.IsEmpty()) { Move.DisplayName = FText::GetEmpty(); bChanged = true; }
            if (!Move.Description.IsEmpty()) { Move.Description.Empty(); bChanged = true; }
        }
        if (bChanged) Partner.Moves.Shrink();
        return bChanged;
    }

    int64 TrainingValue(const FDigimonOwnedPartner& Partner)
    {
        const FDigimonStats& Stats = Partner.PermanentTraining;
        return static_cast<int64>(Stats.MaxHP) + Stats.MaxSP + Stats.Attack + Stats.Defense + Stats.Spirit + Stats.Speed;
    }
}

namespace DigimonVenomNXTRivalRetention
{
    int32 CollectionLimit(int32 Configured, int32 ConfiguredPartySize, int32 Population)
    {
        return DigimonVenomNXTRivalRetentionCore::CollectionLimit(Configured, ConfiguredPartySize, Population);
    }

    int32 ScanLimit(int32 Configured, int32 Population)
    {
        return DigimonVenomNXTRivalRetentionCore::ScanLimit(Configured, Population);
    }

    FResult Prune(FDigimonAIRivalRecord& Rival, const UDigimonVenomNXTSettings& Settings,
        const UDigimonVenomNXTDataSubsystem* Data, int32 Population)
    {
        FResult Result;
        const int32 Capacity = CollectionLimit(Settings.AIRivalMaxCollectionSize, Settings.MaxPartySize, Population);
        const int32 PartyCapacity = FMath::Clamp(Settings.MaxPartySize, 1, 12);
        TMap<FName, bool> ValidSpecies;
        auto SpeciesExists = [Data, &ValidSpecies](FName SpeciesId)
        {
            if (!ValidName(SpeciesId)) return false;
            if (!Data) return true;
            if (const bool* Cached = ValidSpecies.Find(SpeciesId)) return *Cached;
            FDigimonSpeciesDefinition Def;
            const bool bValid = Data->GetSpecies(SpeciesId, Def) && !Def.bPlaceholder;
            ValidSpecies.Add(SpeciesId, bValid);
            return bValid;
        };
        auto PartnerValid = [&SpeciesExists](const FDigimonOwnedPartner& Partner)
        {
            return Partner.InstanceId.IsValid() && ValidVariant(Partner.Variant) && SpeciesExists(Partner.SpeciesId);
        };

        // Current selected copies own the most recent XP, evolution and vitality. Merge first.
        TSet<FGuid> PartyIds;
        Result.bChanged |= Rival.Partners.RemoveAll([&](const FDigimonOwnedPartner& Partner)
        {
            if (!PartnerValid(Partner) || PartyIds.Contains(Partner.InstanceId) || PartyIds.Num() >= PartyCapacity) return true;
            PartyIds.Add(Partner.InstanceId);
            return false;
        }) > 0;
        for (FDigimonOwnedPartner& Partner : Rival.Partners) Result.bChanged |= PruneMoves(Partner);
        const FGuid StarterId = Rival.Collection.IsEmpty() ? FGuid() : Rival.Collection[0].InstanceId;
        TMap<FGuid, int32> FirstOwnedIndex;
        // A single pass over legacy collections avoids a party-size scan of the entire payload.
        for (int32 Index = 0; Index < Rival.Collection.Num(); ++Index)
            if (!FirstOwnedIndex.Contains(Rival.Collection[Index].InstanceId)) FirstOwnedIndex.Add(Rival.Collection[Index].InstanceId, Index);
        for (const FDigimonOwnedPartner& Partner : Rival.Partners)
        {
            if (const int32* Index = FirstOwnedIndex.Find(Partner.InstanceId))
            {
                FDigimonOwnedPartner& Existing = Rival.Collection[*Index];
                if (!FDigimonOwnedPartner::StaticStruct()->CompareScriptStruct(&Existing, &Partner, 0))
                {
                    Existing = Partner;
                    Result.bChanged = true;
                }
            }
            else { Rival.Collection.Add(Partner); Result.bChanged = true; }
        }

        TSet<FGuid> OwnedIds;
        Result.ReleasedPartners += Rival.Collection.RemoveAll([&](const FDigimonOwnedPartner& Partner)
        {
            if (!PartnerValid(Partner) || OwnedIds.Contains(Partner.InstanceId)) return true;
            OwnedIds.Add(Partner.InstanceId);
            return false;
        });
        if (Rival.Collection.Num() > Capacity)
        {
            TArray<int32> Preferred;
            Preferred.Reserve(Rival.Collection.Num());
            for (int32 Index = 0; Index < Rival.Collection.Num(); ++Index) Preferred.Add(Index);
            auto Priority = [&PartyIds, &Rival, StarterId](const FDigimonOwnedPartner& Partner)
            {
                return PartyIds.Contains(Partner.InstanceId) ? 0 : Partner.InstanceId == Rival.TrainingLeaderId ? 1 :
                    Partner.InstanceId == StarterId ? 2 : 3;
            };
            Preferred.Sort([&](int32 A, int32 B)
            {
                const FDigimonOwnedPartner& Left = Rival.Collection[A];
                const FDigimonOwnedPartner& Right = Rival.Collection[B];
                const int32 LP = Priority(Left), RP = Priority(Right);
                if (LP != RP) return LP < RP;
                if (LP == 0) return A < B;
                if (Left.ABI != Right.ABI) return Left.ABI > Right.ABI;
                if (TrainingValue(Left) != TrainingValue(Right)) return TrainingValue(Left) > TrainingValue(Right);
                if (Left.Level != Right.Level) return Left.Level > Right.Level;
                if (Left.Experience != Right.Experience) return Left.Experience > Right.Experience;
                if (Left.CAM != Right.CAM) return Left.CAM > Right.CAM;
                if (Left.Variant != Right.Variant) return static_cast<uint8>(Left.Variant) > static_cast<uint8>(Right.Variant);
                return A < B;
            });
            OwnedIds.Reset();
            for (int32 Index = 0; Index < Capacity; ++Index) OwnedIds.Add(Rival.Collection[Preferred[Index]].InstanceId);
            Result.ReleasedPartners += Rival.Collection.RemoveAll([&OwnedIds](const FDigimonOwnedPartner& Partner)
                { return !OwnedIds.Contains(Partner.InstanceId); });
        }
        for (FDigimonOwnedPartner& Partner : Rival.Collection) Result.bChanged |= PruneMoves(Partner);
        if (Rival.TrainingLeaderId.IsValid() && !OwnedIds.Contains(Rival.TrainingLeaderId))
        {
            Rival.TrainingLeaderId.Invalidate();
            Result.bChanged = true;
        }

        TMap<FGuid, int32> HistoryIndices;
        TArray<FDigimonAIRivalTrainingHistory> History;
        History.Reserve(FMath::Min(Capacity, Rival.TrainingHistory.Num()));
        for (const FDigimonAIRivalTrainingHistory& Entry : Rival.TrainingHistory)
        {
            if (!OwnedIds.Contains(Entry.InstanceId)) continue;
            const int64 Session = FMath::Clamp<int64>(Entry.LastLedSession, 0, FMath::Max<int64>(0, Rival.TrainingSessionSerial));
            Result.bChanged |= Session != Entry.LastLedSession;
            if (int32* Index = HistoryIndices.Find(Entry.InstanceId))
                History[*Index].LastLedSession = FMath::Max(History[*Index].LastLedSession, Session);
            else
            {
                FDigimonAIRivalTrainingHistory Normalized = Entry;
                Normalized.LastLedSession = Session;
                HistoryIndices.Add(Entry.InstanceId, History.Add(Normalized));
            }
        }
        Result.RemovedHistory = Rival.TrainingHistory.Num() - History.Num();
        Rival.TrainingHistory = MoveTemp(History);

        TArray<FDigimonScanRecord> Scans;
        TMap<FScanKey, int32> ScanIndices;
        Scans.Reserve(FMath::Min(Rival.Scans.Num(), ScanLimit(Settings.AIRivalMaxScanRecords, Population)));
        for (FDigimonScanRecord Scan : Rival.Scans)
        {
            if (!ValidVariant(Scan.Variant) || !SpeciesExists(Scan.SpeciesId)) continue;
            if (Data)
            {
                FDigimonSpeciesDefinition Def;
                if (!Data->GetSpecies(Scan.SpeciesId, Def) || !DigimonVenomNXTScanCore::IsVariantAvailable(static_cast<int32>(Scan.Variant),
                    Def.bHasNormalArtwork, Def.bHasParadoxArtwork, Def.bHasShinyArtwork, Def.bHasFirewallArtwork)) continue;
            }
            Result.bChanged |= DigimonVenomNXTScanCore::Observe(Scan, Settings.ScanCapPercent);
            // Spent scans are no longer an AI discovery archive. Lifetime activity totals remain.
            if (Scan.Percent == 0 && Scan.FractionalHundredths == 0) continue;
            const FScanKey Key{Scan.SpeciesId, Scan.Variant};
            if (int32* Index = ScanIndices.Find(Key))
            {
                FDigimonScanRecord& Existing = Scans[*Index];
                if (Scan.Percent > Existing.Percent || (Scan.Percent == Existing.Percent && Scan.FractionalHundredths > Existing.FractionalHundredths))
                { Existing.Percent = Scan.Percent; Existing.FractionalHundredths = Scan.FractionalHundredths; }
                Existing.PeakPercent = FMath::Max(Existing.PeakPercent, Scan.PeakPercent);
                Existing.Materializations = FMath::Max(Existing.Materializations, Scan.Materializations);
                Existing.bEverOwned |= Scan.bEverOwned;
            }
            else ScanIndices.Add(Key, Scans.Add(Scan));
        }
        const int32 ScanCapacity = ScanLimit(Settings.AIRivalMaxScanRecords, Population);
        if (Scans.Num() > ScanCapacity)
        {
            // Keep immediately spendable/near-complete progress first. Stable ties prevent churn.
            Scans.StableSort([](const FDigimonScanRecord& A, const FDigimonScanRecord& B)
            {
                if (A.Percent != B.Percent) return A.Percent > B.Percent;
                return A.FractionalHundredths > B.FractionalHundredths;
            });
            Scans.SetNum(ScanCapacity);
        }
        Result.RemovedScans = Rival.Scans.Num() - Scans.Num();
        Rival.Scans = MoveTemp(Scans);

        TArray<FDigimonInventoryEntry> Inventory;
        TMap<FName, int32> ItemIndices;
        Inventory.Reserve(FMath::Min(64, Rival.Inventory.Num()));
        for (const FDigimonInventoryEntry& Entry : Rival.Inventory)
        {
            if (!ValidName(Entry.ItemId) || Entry.Quantity <= 0) continue;
            if (int32* Index = ItemIndices.Find(Entry.ItemId)) Inventory[*Index].Quantity = FMath::Max(Inventory[*Index].Quantity, Entry.Quantity);
            else if (Inventory.Num() < 64) ItemIndices.Add(Entry.ItemId, Inventory.Add(Entry));
        }
        Result.RemovedInventory = Rival.Inventory.Num() - Inventory.Num();
        Rival.Inventory = MoveTemp(Inventory);
        Result.bChanged |= TrimText(Rival.DisplayName, 96);
        Result.bChanged |= TrimText(Rival.CurrentActivity, 160);
        Result.bChanged |= Result.ReleasedPartners > 0 || Result.RemovedScans > 0 || Result.RemovedHistory > 0 || Result.RemovedInventory > 0;
        if (Result.bChanged)
        {
            Rival.Collection.Shrink(); Rival.Partners.Shrink(); Rival.Scans.Shrink();
            Rival.TrainingHistory.Shrink(); Rival.Inventory.Shrink();
        }
        return Result;
    }

    bool Release(FDigimonAIRivalRecord& Rival, const FGuid& InstanceId, const UDigimonVenomNXTSettings& Settings,
        const UDigimonVenomNXTDataSubsystem* Data, int32 Population)
    {
        if (!InstanceId.IsValid() || Rival.TrainingLeaderId == InstanceId ||
            Rival.Partners.ContainsByPredicate([&InstanceId](const FDigimonOwnedPartner& Partner) { return Partner.InstanceId == InstanceId; })) return false;
        const int32 Removed = Rival.Collection.RemoveAll([&InstanceId](const FDigimonOwnedPartner& Partner) { return Partner.InstanceId == InstanceId; });
        if (Removed == 0) return false;
        Rival.TrainingHistory.RemoveAll([&InstanceId](const FDigimonAIRivalTrainingHistory& Entry) { return Entry.InstanceId == InstanceId; });
        // No full creature tombstone or retired archive is retained after release.
        Prune(Rival, Settings, Data, Population);
        return true;
    }
}
