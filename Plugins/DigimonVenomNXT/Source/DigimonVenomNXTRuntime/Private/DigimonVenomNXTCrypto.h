#pragma once
#include "CoreMinimal.h"

/** Password hashing helpers only. Digimon Venom NXT does not use signed account/session tokens. */
class FDigimonVenomNXTCrypto
{
public:
    static FString NewSalt();
    static FString PBKDF2(const FString& Password, const FString& Salt, int32 Iterations);
    static bool ConstantTimeEquals(const FString& A, const FString& B);

private:
    static TArray<uint8> SHA256(const TArray<uint8>& Data);
    static TArray<uint8> HMACSHA256(const TArray<uint8>& Key, const TArray<uint8>& Data);
    static TArray<uint8> Utf8(const FString& S);
    static FString Hex(const TArray<uint8>& Bytes);
};
