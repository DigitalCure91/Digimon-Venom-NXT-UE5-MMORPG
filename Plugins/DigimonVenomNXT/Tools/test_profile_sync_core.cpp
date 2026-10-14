#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTProfileSyncCore.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace DigimonVenomNXTProfileSyncCore;

static std::vector<std::uint8_t> Transfer(const std::vector<std::uint8_t>& Source)
{
    Receiver Receive;
    SendWindow Send;
    assert(Receive.Begin(static_cast<std::int32_t>(Source.size())));
    assert(Send.Begin(static_cast<std::int32_t>(Source.size())));
    std::vector<std::int32_t> Delayed;
    std::mt19937 Random(7331);
    std::size_t Loops = 0;
    while (!Send.Complete())
    {
        assert(++Loops < Source.size() + 100);
        for (auto Offset = Send.NextOffset(); Offset >= 0; Offset = Send.NextOffset()) Delayed.push_back(Offset);
        assert(Send.InFlight() <= WindowChunks);
        assert(!Delayed.empty());
        // Model reliable delivery after delay and reordering, without acknowledging
        // unsent or missing chunks. The sender must stop when all four slots fill.
        if (Loops % 5 == 1)
        {
            assert(Send.NextOffset() == -1);
            continue;
        }
        std::shuffle(Delayed.begin(), Delayed.end(), Random);
        const auto Offset = Delayed.back(); Delayed.pop_back();
        const auto Length = ExpectedChunkBytes(static_cast<std::int32_t>(Source.size()), Offset);
        const auto Added = Receive.Add(Offset, Source.data() + Offset, Length);
        assert(Added == AddResult::Accepted || Added == AddResult::Complete);
        const auto Progress = Receive.ReceivedBytes();
        assert(Receive.Add(Offset, Source.data() + Offset, Length) == AddResult::Duplicate);
        assert(Receive.ReceivedBytes() == Progress);
        assert(Send.Acknowledge(Offset));
        assert(!Send.Acknowledge(Offset)); // Duplicate ACK never opens an extra slot or refreshes an idle timeout.
    }
    assert(Receive.Complete());
    assert(Receive.ReceivedBytes() == static_cast<std::int32_t>(Source.size()));
    assert(Send.InFlight() == 0);
    assert(std::equal(Source.begin(), Source.end(), Receive.Bytes()));
    return {Receive.Bytes(), Receive.Bytes() + Receive.TotalBytes()};
}

static void SelfTest()
{
    assert(Checksum(reinterpret_cast<const std::uint8_t*>("123456789"), 9) == 0xcbf43926u);
    Receiver Receive;
    for (const std::int32_t Bad : {0, -1, std::numeric_limits<std::int32_t>::min(), MaxSnapshotBytes + 1,
        std::numeric_limits<std::int32_t>::max()}) assert(!Receive.Begin(Bad));
    assert(Receive.Begin(ChunkBytes + 1));
    std::vector<std::uint8_t> Chunk(ChunkBytes, 17);
    assert(Receive.Add(-1, Chunk.data(), ChunkBytes) == AddResult::Rejected);
    assert(Receive.Add(1, Chunk.data(), ChunkBytes) == AddResult::Rejected);
    assert(Receive.Add(0, nullptr, ChunkBytes) == AddResult::Rejected);
    assert(Receive.Add(0, Chunk.data(), ChunkBytes - 1) == AddResult::Rejected);
    assert(Receive.Add(0, Chunk.data(), ChunkBytes + 1) == AddResult::Rejected);
    assert(Receive.Add(std::numeric_limits<std::int32_t>::max(), Chunk.data(), ChunkBytes) == AddResult::Rejected);
    assert(Receive.Add(0, Chunk.data(), ChunkBytes) == AddResult::Accepted);
    assert(!Receive.Complete());
    Chunk[0] ^= 1;
    assert(Receive.Add(0, Chunk.data(), ChunkBytes) == AddResult::Rejected);
    assert(Receive.ReceivedBytes() == ChunkBytes);
    assert(Receive.Add(ChunkBytes, Chunk.data(), 1) == AddResult::Complete);
    assert(Receive.Begin(1)); // Reconnect discards partial bytes from the old stream.
    assert(Receive.ReceivedBytes() == 0 && !Receive.Complete());
    assert(Receive.Add(0, Chunk.data(), 1) == AddResult::Complete);
    SendWindow Send;
    assert(Send.Begin(ChunkBytes * 5));
    assert(!Send.Acknowledge(0));
    for (int I = 0; I < WindowChunks; ++I) assert(Send.NextOffset() == I * ChunkBytes);
    assert(Send.NextOffset() == -1);
    assert(!Send.Acknowledge(ChunkBytes * 4));
    assert(!Send.Acknowledge(1));
    assert(Send.InFlight() == WindowChunks);
    assert(Send.Acknowledge(0));
    assert(!Send.Acknowledge(0));
    assert(Send.NextOffset() == ChunkBytes * 4);
    assert(Send.NextOffset() == -1);
    assert(Send.InFlight() == WindowChunks);
    assert(CanApplyRevision(2, 1, 7, 7, 9, 9));
    assert(!CanApplyRevision(1, 1, 7, 7, 9, 9));
    assert(!CanApplyRevision(0, 0, 7, 7, 9, 9));
    assert(!CanApplyRevision(2, 1, 6, 7, 9, 9));
    assert(!CanApplyRevision(2, 1, 7, 7, 8, 9));
    for (const std::int32_t Size : {1, ChunkBytes - 1, ChunkBytes, ChunkBytes + 1, 65535, 65536, 65537, 1024 * 1024, MaxSnapshotBytes})
    {
        std::vector<std::uint8_t> Bytes(static_cast<std::size_t>(Size));
        for (std::int32_t I = 0; I < Size; ++I) Bytes[static_cast<std::size_t>(I)] = static_cast<std::uint8_t>((I * 31) % 251);
        Transfer(Bytes);
    }
}
int main(int Argc, char** Argv)
{
    if (Argc == 1) { SelfTest(); std::cout << "PASS: production framing, window, CRC, replay, corruption, generation and boundary tests (1 byte through 32 MiB)\n"; return 0; }
    if (Argc != 3) return 2;
    std::ifstream Input(Argv[1], std::ios::binary);
    if (!Input) return 3;
    const std::vector<std::uint8_t> Source((std::istreambuf_iterator<char>(Input)), std::istreambuf_iterator<char>());
    if (!ValidSize(static_cast<std::int32_t>(Source.size()))) return 4;
    const auto Result = Transfer(Source);
    std::ofstream Output(Argv[2], std::ios::binary);
    Output.write(reinterpret_cast<const char*>(Result.data()), static_cast<std::streamsize>(Result.size()));
    return Output ? 0 : 5;
}
