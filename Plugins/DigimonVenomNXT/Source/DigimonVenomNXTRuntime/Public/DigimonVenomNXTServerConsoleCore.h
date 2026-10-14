#pragma once
// Exact native parser and numeric policies; independent of Unreal for adversarial tests.
#include <string>
#include <vector>
#include <cstdint>
#include <limits>
namespace DigimonVenomNXTServerConsoleCore
{
inline bool Authorized(bool Armed, bool Listen, bool SameWorld, bool SameInstance, bool Authority,
    bool Local, bool FirstLocal, bool Authenticated, bool AccountMatches)
{
    return Armed && Listen && SameWorld && SameInstance && Authority && Local && FirstLocal && Authenticated && AccountMatches;
}
inline bool UnsignedDecimal(const std::string& Text, std::int64_t Maximum, std::int64_t& Out)
{
    if (Text.empty() || Maximum < 0) return false;
    std::int64_t Value = 0;
    for (unsigned char C : Text)
    {
        if (C < '0' || C > '9') return false;
        const int Digit = C - '0';
        if (Digit > Maximum || Value > (Maximum - Digit) / 10) return false;
        Value = Value * 10 + Digit;
    }
    Out = Value; return true;
}
inline bool Tokenize(const std::string& Input, std::vector<std::string>& Out, std::string& Error)
{
    Out.clear(); Error.clear();
    if (Input.empty() || Input.size() > 1024) { Error = "Enter a command of 1 to 1024 bytes."; return false; }
    std::string Token; bool Quoted = false, Escaped = false, Started = false;
    for (unsigned char C : Input)
    {
        if (C < 32 || C == 127) { Error = "Commands must be a single printable line."; return false; }
        if (Escaped) { if (C != '"' && C != '\\') { Error = "Only quote and backslash escapes are supported."; return false; } Token += static_cast<char>(C); Escaped = false; Started = true; }
        else if (C == '\\' && Quoted) { Escaped = true; }
        else if (C == '"') { Quoted = !Quoted; Started = true; }
        else if (C == ' ' && !Quoted)
        {
            if (Started) { Out.push_back(Token); Token.clear(); Started = false; }
        }
        else { Token += static_cast<char>(C); Started = true; }
        if (Out.size() > 12 || Token.size() > 512) { Error = "Too many arguments or an argument is too long."; return false; }
    }
    if (Quoted || Escaped) { Error = "Close the quoted text before sending the command."; return false; }
    if (Started) Out.push_back(Token);
    if (Out.empty() || Out.size() > 12) { Error = "Enter one supported command."; return false; }
    return true;
}
template <typename Candidate, typename Save, typename Publish>
bool Commit(Candidate& Value, Save SaveValue, Publish PublishValue)
{
    if (!SaveValue(Value)) return false;
    PublishValue(Value);
    return true;
}
inline bool ConfirmationAllowed(bool Pending, bool TokenMatches, double Now, double Expiry, bool SameTarget)
{
    return Pending && TokenMatches && Now <= Expiry && SameTarget;
}
inline bool ActiveUntil(std::int64_t Until, std::int64_t Now) { return Until == -1 || Until > Now; }
inline bool AddWithin(std::int64_t Current, std::int64_t Amount, std::int64_t Maximum, std::int64_t& Out)
{
    if (Current < 0 || Amount < 0 || Current > Maximum || Amount > Maximum - Current) return false;
    Out = Current + Amount; return true;
}
}
