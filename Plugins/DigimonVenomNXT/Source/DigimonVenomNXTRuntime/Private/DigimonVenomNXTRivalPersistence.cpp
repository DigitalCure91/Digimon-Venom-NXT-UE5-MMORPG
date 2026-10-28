#include "DigimonVenomNXTRivalPersistence.h"
#include "DigimonVenomNXTRivalJsonStreamCore.h"
#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Serialization/Archive.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Containers/StringConv.h"

namespace DigimonVenomNXTRivalPersistence
{
namespace
{
    class FBufferedBytes
    {
    public:
        explicit FBufferedBytes(FArchive& InArchive) : Archive(InArchive), Size(InArchive.TotalSize()) {}
        int Peek()
        {
            if (Cursor == Count && !Refill()) return -1;
            return Buffer[Cursor];
        }
        int Get() { const int Byte = Peek(); if (Byte >= 0) { ++Cursor; ++Consumed; } return Byte; }
        std::int64_t Position() const { return Consumed; }
        bool Failed() const { return bFailed || Archive.IsError(); }
    private:
        FArchive& Archive;
        int64 Size = 0;
        int64 Loaded = 0;
        int64 Consumed = 0;
        int32 Cursor = 0;
        int32 Count = 0;
        uint8 Buffer[64 * 1024];
        bool bFailed = false;
        bool Refill()
        {
            if (Loaded >= Size || bFailed) return false;
            Count = static_cast<int32>(FMath::Min<int64>(sizeof(Buffer), Size - Loaded));
            Cursor = 0;
            Archive.Serialize(Buffer, Count);
            if (Archive.IsError()) { Count = 0; bFailed = true; return false; }
            Loaded += Count;
            return Count > 0;
        }
    };

    // A move's catalog metadata is not ownership/progression. BuildUnit resolves
    // each equipped slot from MoveId, including inherited moves, on every battle.
    // Persisting descriptions and stat templates thousands of times wastes space.
    void CompactMoves(const TSharedRef<FJsonObject>& Record, const FString& ArrayName)
    {
        const TArray<TSharedPtr<FJsonValue>>* Partners = nullptr;
        if (!Record->TryGetArrayField(ArrayName, Partners)) return;
        for (const TSharedPtr<FJsonValue>& Value : *Partners)
        {
            if (!Value.IsValid() || Value->Type != EJson::Object) continue;
            const TSharedPtr<FJsonObject> Partner = Value->AsObject();
            const TArray<TSharedPtr<FJsonValue>>* Moves = nullptr;
            if (!Partner.IsValid() || !Partner->TryGetArrayField(TEXT("moves"), Moves)) continue;
            TArray<TSharedPtr<FJsonValue>> Slots;
            Slots.Reserve(Moves->Num());
            for (const TSharedPtr<FJsonValue>& Move : *Moves)
            {
                FString MoveId;
                if (!Move.IsValid() || Move->Type != EJson::Object || !Move->AsObject()->TryGetStringField(TEXT("moveId"), MoveId)) continue;
                TSharedRef<FJsonObject> Slot = MakeShared<FJsonObject>();
                Slot->SetStringField(TEXT("moveId"), MoveId);
                Slots.Add(MakeShared<FJsonValueObject>(Slot));
            }
            Partner->SetArrayField(TEXT("moves"), Slots);
        }
    }
}

bool Read(const FString& Path, FDigimonAIRivalSaveData& OutData,
    TFunctionRef<void(FDigimonAIRivalRecord&, int32 TotalRivals)> CompactRecord, FString& OutError, bool& bUnsupportedSchema)
{
    OutError.Reset();
    bUnsupportedSchema = false;
    TUniquePtr<FArchive> File(IFileManager::Get().CreateFileReader(*Path));
    if (!File) { OutError = TEXT("Could not open rival checkpoint."); return false; }
    const int64 Size = File->TotalSize();
    if (Size <= 0 || Size > DigimonVenomNXTRivalJsonStreamCore::MaxLegacyFileBytes)
    {
        OutError = TEXT("Rival checkpoint is empty or exceeds the 8 GiB legacy-import safety limit.");
        return false;
    }
    DigimonVenomNXTRivalJsonStreamCore::Index Index;
    {
        FBufferedBytes Bytes(*File);
        DigimonVenomNXTRivalJsonStreamCore::Scanner<FBufferedBytes> Scanner(Bytes, Index);
        if (!Scanner.Run())
        {
            OutError = UTF8_TO_TCHAR(Index.Error.c_str());
            bUnsupportedSchema = Index.UnsupportedSchema;
            return false;
        }
    }
    FDigimonAIRivalSaveData Candidate;
    Candidate.SchemaVersion = Index.SchemaVersion;
    Candidate.ActivityWindowStartUnix = Index.ActivityWindowStartUnix;
    Candidate.LastSavedUnix = Index.LastSavedUnix;
    const int32 TotalRivals = static_cast<int32>(Index.Records.size());
    Candidate.Rivals.Reserve(TotalRivals);
    TSet<FString> Ids;
    for (const DigimonVenomNXTRivalJsonStreamCore::RecordRange& Range : Index.Records)
    {
        FDigimonAIRivalRecord Rival;
        // This scope releases the legacy JSON/DOM before the compacted record is
        // added to the candidate database or the next rival is decoded.
        {
            TArray<ANSICHAR> Raw;
            Raw.SetNumUninitialized(static_cast<int32>(Range.Length) + 1);
            File->Seek(Range.Offset);
            File->Serialize(Raw.GetData(), Range.Length);
            if (File->IsError()) { OutError = TEXT("Could not read a complete rival record."); return false; }
            Raw[static_cast<int32>(Range.Length)] = 0;
            const FUTF8ToTCHAR Converted(Raw.GetData(), static_cast<int32>(Range.Length));
            const FString Text(Converted.Length(), Converted.Get());
            TSharedPtr<FJsonObject> Object;
            if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Object) || !Object.IsValid() ||
                !FJsonObjectConverter::JsonObjectToUStruct(Object.ToSharedRef(), &Rival, 0, 0))
            {
                OutError = TEXT("A rival record could not be decoded; checkpoint was not loaded.");
                return false;
            }
        }
        if (Rival.RivalId.IsEmpty() || Rival.RivalId.Len() > 128 || Ids.Contains(Rival.RivalId))
        {
            OutError = TEXT("Checkpoint contains a missing, duplicate, or invalid rival ID.");
            return false;
        }
        Ids.Add(Rival.RivalId);
        CompactRecord(Rival, TotalRivals);
        Candidate.Rivals.Add(MoveTemp(Rival));
    }
    if (!File->Close() || File->IsError()) { OutError = TEXT("Could not finish reading rival checkpoint."); return false; }
    OutData = MoveTemp(Candidate);
    return true;
}

bool WriteTemporary(const FString& Path, const FDigimonAIRivalSaveData& Data, FString& OutError)
{
    OutError.Reset();
    if (Data.SchemaVersion > DigimonVenomNXTRivalJsonStreamCore::CurrentSchema || Data.SchemaVersion < 0 ||
        Data.Rivals.Num() > static_cast<int32>(DigimonVenomNXTRivalJsonStreamCore::MaxRivals))
    {
        OutError = TEXT("Rival checkpoint schema or population exceeds the supported safety limits.");
        return false;
    }
    TUniquePtr<FArchive> File(IFileManager::Get().CreateFileWriter(*Path));
    if (!File) { OutError = TEXT("Could not open temporary rival checkpoint."); return false; }
    static_assert(MaxCheckpointBytes == DigimonVenomNXTRivalJsonStreamCore::MaxCheckpointBytes, "Checkpoint limits must agree");
    std::int64_t Written = 0;
    auto Write = [&File, &Written, &OutError](const FString& Text)
    {
        const FTCHARToUTF8 Bytes(*Text);
        const int64 Count = Bytes.Length();
        if (!DigimonVenomNXTRivalJsonStreamCore::AdvanceCheckpointBudget(Count, Written))
        {
            OutError = TEXT("Rival checkpoint would exceed the 256 MiB safety limit; previous save is retained.");
            return false;
        }
        File->Serialize(const_cast<ANSICHAR*>(Bytes.Get()), Count);
        if (File->IsError()) { OutError = TEXT("Could not write temporary rival checkpoint; previous save is retained."); return false; }
        return true;
    };
    auto Abort = [&File, &Path]()
    {
        File->Close(); File.Reset();
        IFileManager::Get().Delete(*Path, false, true);
        return false;
    };
    const FString Header = FString::Printf(TEXT("{\"schemaVersion\":%d,\"activityWindowStartUnix\":%lld,\"lastSavedUnix\":%lld,\"rivals\":["),
        Data.SchemaVersion, static_cast<long long>(Data.ActivityWindowStartUnix), static_cast<long long>(Data.LastSavedUnix));
    if (!Write(Header)) return Abort();
    TSet<FString> Ids;
    for (int32 I = 0; I < Data.Rivals.Num(); ++I)
    {
        const FDigimonAIRivalRecord& Rival = Data.Rivals[I];
        if (Rival.RivalId.IsEmpty() || Rival.RivalId.Len() > 128 || Ids.Contains(Rival.RivalId))
        {
            OutError = TEXT("Cannot checkpoint missing, duplicate, or invalid rival IDs.");
            return Abort();
        }
        Ids.Add(Rival.RivalId);
        TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
        if (!FJsonObjectConverter::UStructToJsonObject(FDigimonAIRivalRecord::StaticStruct(), &Rival, Object, 0, 0))
        {
            OutError = TEXT("Could not serialize a rival record; previous save is retained.");
            return Abort();
        }
        CompactMoves(Object, TEXT("partners"));
        CompactMoves(Object, TEXT("collection"));
        FString Text;
        const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
            TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Text);
        if (!FJsonSerializer::Serialize(Object, Writer))
        {
            OutError = TEXT("Could not encode a rival record; previous save is retained.");
            return Abort();
        }
        if ((I > 0 && !Write(TEXT(","))) || !Write(Text)) return Abort();
    }
    if (!Write(TEXT("]}"))) return Abort();
    File->Flush();
    const bool bClosed = File->Close();
    if (!bClosed || File->IsError())
    {
        OutError = TEXT("Could not close temporary rival checkpoint; previous save is retained.");
        return Abort();
    }
    return true;
}
}
