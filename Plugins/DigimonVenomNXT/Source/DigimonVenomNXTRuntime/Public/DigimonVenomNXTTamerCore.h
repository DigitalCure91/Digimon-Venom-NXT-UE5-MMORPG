#pragma once

#include <cstdint>
#include <string_view>

// Immutable source-slot IDs: holes are intentional and must never become styles.
namespace DigimonVenomNXTTamerCore
{
inline constexpr int StyleNumbers[] = { 2, 3, 4, 5, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 82, 83, 84, 85, 86, 87, 88, 89 };
inline constexpr int StyleCount = sizeof(StyleNumbers) / sizeof(StyleNumbers[0]);
inline constexpr int DefaultStyleNumber = 2;
inline bool IsStyleNumber(int Number)
{
    for (int Value : StyleNumbers) if (Value == Number) return true;
    return false;
}
inline int StyleNumberAt(int Index)
{
    return Index >= 0 && Index < StyleCount ? StyleNumbers[Index] : DefaultStyleNumber;
}
inline std::uint32_t StableStyleHash(std::string_view Key)
{
    std::uint32_t Hash = 2166136261u;
    for (unsigned char Byte : Key)
    {
        if (Byte >= 'A' && Byte <= 'Z') Byte = static_cast<unsigned char>(Byte + ('a' - 'A'));
        Hash = (Hash ^ Byte) * 16777619u;
    }
    // Mix high bits into low bits before selecting one of the 64 appearances.
    Hash ^= Hash >> 16; Hash *= 0x7feb352du;
    Hash ^= Hash >> 15; Hash *= 0x846ca68bu;
    return Hash ^ (Hash >> 16);
}
inline int StyleIndexForKey(std::string_view Key)
{
    return Key.empty() ? 0 : static_cast<int>(StableStyleHash(Key) % StyleCount);
}
}
