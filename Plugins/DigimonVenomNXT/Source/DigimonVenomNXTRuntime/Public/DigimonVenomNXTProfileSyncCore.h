#pragma once

// Engine-independent framing used by the production owner-profile transport and tests.
#include <algorithm>
#include <cstdint>
#include <vector>

namespace DigimonVenomNXTProfileSyncCore
{
constexpr std::int32_t ProtocolVersion = 1;
// Deliberately below both the default dynamic-array element limit and
// normal reliable-bunch size. Never raise engine limits to fit a profile.
constexpr std::int32_t ChunkBytes = 1024;
constexpr std::int32_t WindowChunks = 4;
constexpr std::int32_t MaxSnapshotBytes = 32 * 1024 * 1024;
constexpr double IdleTimeoutSeconds = 30.0;
constexpr double MinimumSnapshotIntervalSeconds = 0.5;

inline bool ValidSize(std::int32_t Size) { return Size > 0 && Size <= MaxSnapshotBytes; }
inline std::int32_t ChunkCount(std::int32_t Size)
{
    return ValidSize(Size) ? (Size + ChunkBytes - 1) / ChunkBytes : 0;
}
inline std::int32_t ExpectedChunkBytes(std::int32_t Total, std::int32_t Offset)
{
    if (!ValidSize(Total) || Offset < 0 || Offset >= Total || Offset % ChunkBytes != 0) return 0;
    return std::min(ChunkBytes, Total - Offset);
}
inline std::uint32_t Checksum(const std::uint8_t* Data, std::int32_t Size)
{
    std::uint32_t Result = 0xffffffffu;
    for (std::int32_t Index = 0; Index < Size; ++Index)
    {
        Result ^= Data[Index];
        for (int Bit = 0; Bit < 8; ++Bit)
            Result = (Result >> 1) ^ (0xedb88320u & (0u - (Result & 1u)));
    }
    return ~Result;
}
inline bool CanApplyRevision(std::int64_t Incoming, std::int64_t Applied,
    std::int64_t IncomingCommerce, std::int64_t LocalCommerce,
    std::int64_t IncomingRecovery, std::int64_t LocalRecovery)
{
    return Incoming > Applied && Incoming > 0 && IncomingCommerce >= LocalCommerce && IncomingRecovery >= LocalRecovery;
}

enum class AddResult { Rejected, Duplicate, Accepted, Complete };
class Receiver
{
public:
    bool Begin(std::int32_t Size)
    {
        Reset();
        if (!ValidSize(Size)) return false;
        Data.resize(static_cast<std::size_t>(Size));
        Present.resize(static_cast<std::size_t>(ChunkCount(Size)), 0);
        return true;
    }
    void Reset() { Data.clear(); Present.clear(); Received = 0; }
    AddResult Add(std::int32_t Offset, const std::uint8_t* Bytes, std::int32_t Size)
    {
        const std::int32_t Expected = ExpectedChunkBytes(TotalBytes(), Offset);
        if (!Bytes || Expected == 0 || Size != Expected) return AddResult::Rejected;
        const auto Index = static_cast<std::size_t>(Offset / ChunkBytes);
        auto Target = Data.begin() + Offset;
        if (Present[Index])
            return std::equal(Bytes, Bytes + Size, Target) ? AddResult::Duplicate : AddResult::Rejected;
        std::copy(Bytes, Bytes + Size, Target);
        Present[Index] = 1;
        Received += Size;
        return Complete() ? AddResult::Complete : AddResult::Accepted;
    }
    bool Complete() const { return !Data.empty() && Received == TotalBytes(); }
    std::int32_t TotalBytes() const { return static_cast<std::int32_t>(Data.size()); }
    std::int32_t ReceivedBytes() const { return Received; }
    const std::uint8_t* Bytes() const { return Data.data(); }
private:
    std::vector<std::uint8_t> Data;
    std::vector<std::uint8_t> Present;
    std::int32_t Received = 0;
};

// There can never be more than four unacknowledged data RPCs. No loop queues a
// whole account into Unreal's reliable buffer, even for a multi-megabyte profile.
class SendWindow
{
public:
    bool Begin(std::int32_t Size)
    {
        Reset();
        if (!ValidSize(Size)) return false;
        Total = Size;
        Acknowledged.resize(static_cast<std::size_t>(ChunkCount(Size)), 0);
        return true;
    }
    void Reset() { Total = 0; NextIndex = 0; Outstanding = 0; CountAcknowledged = 0; Acknowledged.clear(); }
    std::int32_t NextOffset()
    {
        if (Outstanding >= WindowChunks || NextIndex >= ChunkCount(Total)) return -1;
        ++Outstanding;
        return NextIndex++ * ChunkBytes;
    }
    bool Acknowledge(std::int32_t Offset)
    {
        if (!ExpectedChunkBytes(Total, Offset)) return false;
        const std::int32_t Index = Offset / ChunkBytes;
        if (Index >= NextIndex) return false; // Never acknowledge unsent bytes.
        if (Acknowledged[static_cast<std::size_t>(Index)]) return false;
        Acknowledged[static_cast<std::size_t>(Index)] = 1;
        --Outstanding;
        ++CountAcknowledged;
        return true;
    }
    bool Complete() const { return Total > 0 && CountAcknowledged == ChunkCount(Total); }
    std::int32_t InFlight() const { return Outstanding; }
private:
    std::vector<std::uint8_t> Acknowledged;
    std::int32_t Total = 0;
    std::int32_t NextIndex = 0;
    std::int32_t Outstanding = 0;
    std::int32_t CountAcknowledged = 0;
};
}
