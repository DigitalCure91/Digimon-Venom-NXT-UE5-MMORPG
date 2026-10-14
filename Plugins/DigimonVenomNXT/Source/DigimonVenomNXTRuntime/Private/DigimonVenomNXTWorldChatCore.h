#pragma once

#include <cmath>
#include <cstdint>
#include <string>

// Engine-independent policy used by the actual server ingress, not a test-only model.
namespace DigimonVenomNXTWorldChatCore
{
    constexpr int HistoryLimit = 200;
    constexpr double SendIntervalSeconds = 1.0;

    inline bool CanSend(double Now, double Previous)
    {
        return std::isfinite(Now) && std::isfinite(Previous) && Now - Previous >= SendIntervalSeconds;
    }

    template<typename Character>
    std::basic_string<Character> Normalize(const Character* Input, int Length, int RequestedLimit)
    {
        const int Limit = RequestedLimit < 1 ? 1 : RequestedLimit > 512 ? 512 : RequestedLimit;
        std::basic_string<Character> Out;
        if (!Input || Length <= 0) return Out;
        Out.reserve(static_cast<std::size_t>(Limit));
        bool PendingSpace = false;
        // Hard bound scanning as well as output; a whitespace-only malicious RPC cannot monopolize a frame.
        for (int Index = 0; Index < Length && Index < 4096 && static_cast<int>(Out.size()) < Limit; ++Index)
        {
            const std::uint32_t C = static_cast<std::uint32_t>(Input[Index]);
            if (C <= 0x20 || (C >= 0x7f && C <= 0x9f) || C == 0x2028 || C == 0x2029 || C == 0xa0)
            {
                PendingSpace = !Out.empty();
                continue;
            }
            // Prevent invisible direction overrides/line spoofing; actual international text is kept.
            if ((C >= 0x202a && C <= 0x202e) || (C >= 0x2066 && C <= 0x2069) || C == 0x200b || C == 0xfeff) continue;
            if (PendingSpace)
            {
                if (static_cast<int>(Out.size()) + 1 >= Limit) break;
                Out.push_back(static_cast<Character>(' '));
                PendingSpace = false;
            }
            // Never split a UTF-16 surrogate pair at the configured character boundary.
            if (C >= 0xd800 && C <= 0xdbff)
            {
                if (Index + 1 >= Length || Index + 1 >= 4096 || static_cast<int>(Out.size()) + 2 > Limit) break;
                const std::uint32_t Low = static_cast<std::uint32_t>(Input[Index + 1]);
                if (Low < 0xdc00 || Low > 0xdfff) continue;
                Out.push_back(Input[Index++]);
                Out.push_back(Input[Index]);
                continue;
            }
            if (C >= 0xdc00 && C <= 0xdfff) continue;
            Out.push_back(Input[Index]);
        }
        while (!Out.empty() && Out.back() == static_cast<Character>(' ')) Out.pop_back();
        return Out;
    }
}
