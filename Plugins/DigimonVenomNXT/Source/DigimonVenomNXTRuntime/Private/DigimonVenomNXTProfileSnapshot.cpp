#include "DigimonVenomNXTProfileSnapshot.h"
#include "DigimonVenomNXTProfileSyncCore.h"
#include "DigimonVenomNXTProfileValidation.h"
#include "Containers/StringConv.h"
#include "JsonObjectConverter.h"
#include "Misc/Compression.h"

bool DigimonVenomNXTProfileSnapshot::Encode(const FDigimonPlayerProfile& Profile, TArray<uint8>& Bytes,
    int32& JsonBytes, uint32& Checksum, FString& Error)
{
    Bytes.Reset(); JsonBytes = 0; Checksum = 0;
    if (!DigimonVenomNXTProfileValidation::Validate(Profile, Profile.AccountId, Error)) return false;
    FString Json;
    if (!FJsonObjectConverter::UStructToJsonObjectString(Profile, Json))
    {
        Error = TEXT("The server could not serialize this profile. Saved progress has not been changed.");
        return false;
    }
    const FTCHARToUTF8 Utf8(*Json);
    if (!DigimonVenomNXTProfileSyncCore::ValidSize(Utf8.Length()))
    {
        Error = TEXT("This profile exceeds the 32 MiB synchronization safety limit. Contact the host; the saved account has not been replaced.");
        return false;
    }
    int64 Capacity = 0;
    if (!FCompression::CompressMemoryBound(NAME_Zlib, Capacity, static_cast<int64>(Utf8.Length()), 0) ||
        Capacity <= 0 || Capacity > static_cast<int64>(DigimonVenomNXTProfileSyncCore::MaxSnapshotBytes) + 65536)
    {
        Error = TEXT("Profile compression is unavailable. Saved progress has not been changed.");
        return false;
    }
    Bytes.SetNumUninitialized(static_cast<int32>(Capacity));
    if (!FCompression::CompressMemory(NAME_Zlib, Bytes.GetData(), Capacity, Utf8.Get(),
        static_cast<int64>(Utf8.Length()), COMPRESS_None, 0) ||
        Capacity <= 0 || Capacity > DigimonVenomNXTProfileSyncCore::MaxSnapshotBytes)
    {
        Bytes.Reset();
        Error = TEXT("The server could not prepare the account snapshot. Saved progress has not been changed.");
        return false;
    }
    Bytes.SetNum(static_cast<int32>(Capacity));
    JsonBytes = Utf8.Length();
    Checksum = DigimonVenomNXTProfileSyncCore::Checksum(reinterpret_cast<const uint8*>(Utf8.Get()), JsonBytes);
    return true;
}

bool DigimonVenomNXTProfileSnapshot::Decode(const uint8* Bytes, int32 ByteCount, int32 JsonBytes, uint32 Checksum,
    const FString& ExpectedAccountId, FDigimonPlayerProfile& OutProfile, FString& Error)
{
    Error.Reset();
    if (!Bytes || !DigimonVenomNXTProfileSyncCore::ValidSize(ByteCount) || !DigimonVenomNXTProfileSyncCore::ValidSize(JsonBytes))
    {
        Error = TEXT("The account snapshot has an invalid length.");
        return false;
    }
    TArray<uint8> JsonData;
    JsonData.SetNumUninitialized(JsonBytes);
    if (!FCompression::UncompressMemory(NAME_Zlib, JsonData.GetData(), static_cast<int64>(JsonBytes), Bytes,
        static_cast<int64>(ByteCount), COMPRESS_None, 0) ||
        DigimonVenomNXTProfileSyncCore::Checksum(JsonData.GetData(), JsonBytes) != Checksum)
    {
        Error = TEXT("The account snapshot failed its integrity check. The previous profile remains unchanged.");
        return false;
    }
    const FUTF8ToTCHAR Converted(reinterpret_cast<const ANSICHAR*>(JsonData.GetData()), JsonData.Num());
    const FString Json(Converted.Length(), Converted.Get());
    FDigimonPlayerProfile Candidate;
    if (!DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json) ||
        !FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Candidate, 0, 0) ||
        !DigimonVenomNXTProfileValidation::Validate(Candidate, ExpectedAccountId, Error))
    {
        if (Error.IsEmpty()) Error = TEXT("The received account data is incomplete. Saved progress has not been changed.");
        return false;
    }
    // Nothing is published until the entire payload, identity and party references pass.
    OutProfile = MoveTemp(Candidate);
    return true;
}
