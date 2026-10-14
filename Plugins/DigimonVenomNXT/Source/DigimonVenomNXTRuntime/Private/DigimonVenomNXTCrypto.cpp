#include "DigimonVenomNXTCrypto.h"

namespace DigimonVenomNXTCryptoInternal
{
    static FORCEINLINE uint32 RotR(uint32 Value, uint32 Bits)
    {
        return (Value >> Bits) | (Value << (32u - Bits));
    }

    static FORCEINLINE uint32 Choose(uint32 X, uint32 Y, uint32 Z)
    {
        return (X & Y) ^ (~X & Z);
    }

    static FORCEINLINE uint32 Majority(uint32 X, uint32 Y, uint32 Z)
    {
        return (X & Y) ^ (X & Z) ^ (Y & Z);
    }

    static FORCEINLINE uint32 BigSigma0(uint32 X)
    {
        return RotR(X, 2) ^ RotR(X, 13) ^ RotR(X, 22);
    }

    static FORCEINLINE uint32 BigSigma1(uint32 X)
    {
        return RotR(X, 6) ^ RotR(X, 11) ^ RotR(X, 25);
    }

    static FORCEINLINE uint32 SmallSigma0(uint32 X)
    {
        return RotR(X, 7) ^ RotR(X, 18) ^ (X >> 3);
    }

    static FORCEINLINE uint32 SmallSigma1(uint32 X)
    {
        return RotR(X, 17) ^ RotR(X, 19) ^ (X >> 10);
    }

    static constexpr uint32 K[64] =
    {
        0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u,
        0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
        0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u,
        0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
        0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu,
        0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
        0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u,
        0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
        0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u,
        0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
        0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u,
        0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
        0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u,
        0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
        0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u,
        0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
    };

    struct FSHA256Context
    {
        uint32 State[8] =
        {
            0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au,
            0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u
        };
        uint64 TotalBytes = 0;
        uint8 Buffer[64] = {};
        int32 BufferSize = 0;
    };

    static void Transform(FSHA256Context& Ctx, const uint8 Block[64])
    {
        uint32 W[64];
        for (int32 I = 0; I < 16; ++I)
        {
            const int32 O = I * 4;
            W[I] = (static_cast<uint32>(Block[O]) << 24)
                | (static_cast<uint32>(Block[O + 1]) << 16)
                | (static_cast<uint32>(Block[O + 2]) << 8)
                | static_cast<uint32>(Block[O + 3]);
        }
        for (int32 I = 16; I < 64; ++I)
        {
            W[I] = SmallSigma1(W[I - 2]) + W[I - 7] + SmallSigma0(W[I - 15]) + W[I - 16];
        }

        uint32 A = Ctx.State[0];
        uint32 B = Ctx.State[1];
        uint32 C = Ctx.State[2];
        uint32 D = Ctx.State[3];
        uint32 E = Ctx.State[4];
        uint32 F = Ctx.State[5];
        uint32 G = Ctx.State[6];
        uint32 H = Ctx.State[7];

        for (int32 I = 0; I < 64; ++I)
        {
            const uint32 T1 = H + BigSigma1(E) + Choose(E, F, G) + K[I] + W[I];
            const uint32 T2 = BigSigma0(A) + Majority(A, B, C);
            H = G;
            G = F;
            F = E;
            E = D + T1;
            D = C;
            C = B;
            B = A;
            A = T1 + T2;
        }

        Ctx.State[0] += A;
        Ctx.State[1] += B;
        Ctx.State[2] += C;
        Ctx.State[3] += D;
        Ctx.State[4] += E;
        Ctx.State[5] += F;
        Ctx.State[6] += G;
        Ctx.State[7] += H;
    }

    static void Update(FSHA256Context& Ctx, const uint8* Data, int32 Length)
    {
        if (!Data || Length <= 0)
        {
            return;
        }

        Ctx.TotalBytes += static_cast<uint64>(Length);
        int32 Offset = 0;

        if (Ctx.BufferSize > 0)
        {
            const int32 ToCopy = FMath::Min(64 - Ctx.BufferSize, Length);
            FMemory::Memcpy(Ctx.Buffer + Ctx.BufferSize, Data, ToCopy);
            Ctx.BufferSize += ToCopy;
            Offset += ToCopy;
            if (Ctx.BufferSize == 64)
            {
                Transform(Ctx, Ctx.Buffer);
                Ctx.BufferSize = 0;
            }
        }

        while (Offset + 64 <= Length)
        {
            Transform(Ctx, Data + Offset);
            Offset += 64;
        }

        const int32 Remaining = Length - Offset;
        if (Remaining > 0)
        {
            FMemory::Memcpy(Ctx.Buffer, Data + Offset, Remaining);
            Ctx.BufferSize = Remaining;
        }
    }

    static void Final(FSHA256Context& Ctx, uint8 Out[32])
    {
        const uint64 BitLength = Ctx.TotalBytes * 8ull;

        Ctx.Buffer[Ctx.BufferSize++] = 0x80u;
        if (Ctx.BufferSize > 56)
        {
            while (Ctx.BufferSize < 64)
            {
                Ctx.Buffer[Ctx.BufferSize++] = 0;
            }
            Transform(Ctx, Ctx.Buffer);
            Ctx.BufferSize = 0;
        }

        while (Ctx.BufferSize < 56)
        {
            Ctx.Buffer[Ctx.BufferSize++] = 0;
        }

        for (int32 I = 7; I >= 0; --I)
        {
            Ctx.Buffer[Ctx.BufferSize++] = static_cast<uint8>((BitLength >> (I * 8)) & 0xffu);
        }
        Transform(Ctx, Ctx.Buffer);

        for (int32 I = 0; I < 8; ++I)
        {
            Out[I * 4] = static_cast<uint8>((Ctx.State[I] >> 24) & 0xffu);
            Out[I * 4 + 1] = static_cast<uint8>((Ctx.State[I] >> 16) & 0xffu);
            Out[I * 4 + 2] = static_cast<uint8>((Ctx.State[I] >> 8) & 0xffu);
            Out[I * 4 + 3] = static_cast<uint8>(Ctx.State[I] & 0xffu);
        }
    }

    static void Hash(const uint8* Data, int32 Length, uint8 Out[32])
    {
        FSHA256Context Context;
        Update(Context, Data, Length);
        Final(Context, Out);
    }
}

TArray<uint8> FDigimonVenomNXTCrypto::Utf8(const FString& S)
{
    FTCHARToUTF8 Conv(*S);
    TArray<uint8> Out;
    Out.Append(reinterpret_cast<const uint8*>(Conv.Get()), Conv.Length());
    return Out;
}

TArray<uint8> FDigimonVenomNXTCrypto::SHA256(const TArray<uint8>& Data)
{
    uint8 Digest[32] = {};
    DigimonVenomNXTCryptoInternal::Hash(Data.Num() > 0 ? Data.GetData() : nullptr, Data.Num(), Digest);

    TArray<uint8> Out;
    Out.Append(Digest, UE_ARRAY_COUNT(Digest));
    return Out;
}

TArray<uint8> FDigimonVenomNXTCrypto::HMACSHA256(const TArray<uint8>& InKey, const TArray<uint8>& Data)
{
    constexpr int32 BlockSize = 64;
    TArray<uint8> Key = InKey;
    if (Key.Num() > BlockSize)
    {
        Key = SHA256(Key);
    }
    Key.SetNumZeroed(BlockSize);

    uint8 InnerPad[BlockSize];
    uint8 OuterPad[BlockSize];
    for (int32 I = 0; I < BlockSize; ++I)
    {
        InnerPad[I] = Key[I] ^ 0x36u;
        OuterPad[I] = Key[I] ^ 0x5cu;
    }

    TArray<uint8> Inner;
    Inner.Reserve(BlockSize + Data.Num());
    Inner.Append(InnerPad, BlockSize);
    Inner.Append(Data);
    const TArray<uint8> InnerHash = SHA256(Inner);

    TArray<uint8> Outer;
    Outer.Reserve(BlockSize + InnerHash.Num());
    Outer.Append(OuterPad, BlockSize);
    Outer.Append(InnerHash);
    return SHA256(Outer);
}

FString FDigimonVenomNXTCrypto::Hex(const TArray<uint8>& Bytes)
{
    FString Out;
    Out.Reserve(Bytes.Num() * 2);
    static const TCHAR* Digits = TEXT("0123456789abcdef");
    for (uint8 B : Bytes)
    {
        Out.AppendChar(Digits[(B >> 4) & 0xF]);
        Out.AppendChar(Digits[B & 0xF]);
    }
    return Out;
}

FString FDigimonVenomNXTCrypto::NewSalt()
{
    // A password salt needs uniqueness, not secrecy. Two GUIDs provide 256 bits
    // of per-account salt material without depending on the removed platform
    // SHA/HTTP/token infrastructure.
    return FGuid::NewGuid().ToString(EGuidFormats::Digits) + FGuid::NewGuid().ToString(EGuidFormats::Digits);
}

FString FDigimonVenomNXTCrypto::PBKDF2(const FString& Password, const FString& Salt, int32 Iterations)
{
    const TArray<uint8> Key = Utf8(Password);
    TArray<uint8> SaltBytes = Utf8(Salt);
    SaltBytes.Add(0);
    SaltBytes.Add(0);
    SaltBytes.Add(0);
    SaltBytes.Add(1); // PBKDF2 block index 1, big endian.

    TArray<uint8> U = HMACSHA256(Key, SaltBytes);
    TArray<uint8> Result = U;
    const int32 SafeIterations = FMath::Max(1, Iterations);
    for (int32 I = 1; I < SafeIterations; ++I)
    {
        U = HMACSHA256(Key, U);
        for (int32 J = 0; J < Result.Num(); ++J)
        {
            Result[J] ^= U[J];
        }
    }
    return Hex(Result);
}

bool FDigimonVenomNXTCrypto::ConstantTimeEquals(const FString& A, const FString& B)
{
    if (A.Len() != B.Len())
    {
        return false;
    }

    uint32 Diff = 0;
    for (int32 I = 0; I < A.Len(); ++I)
    {
        Diff |= static_cast<uint32>(A[I] ^ B[I]);
    }
    return Diff == 0;
}
