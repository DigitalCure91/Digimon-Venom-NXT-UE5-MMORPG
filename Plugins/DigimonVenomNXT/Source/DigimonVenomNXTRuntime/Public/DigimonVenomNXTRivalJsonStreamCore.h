#pragma once

// Intentionally independent of Unreal: the legacy-file scanner is exercised by
// the standalone regression suite as well as the engine adapter.
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

namespace DigimonVenomNXTRivalJsonStreamCore
{
    constexpr std::int64_t MaxCheckpointBytes = 256LL * 1024 * 1024;
    constexpr std::int64_t MaxLegacyRecordBytes = 64LL * 1024 * 1024;
    constexpr std::int64_t MaxLegacyFileBytes = 8LL * 1024 * 1024 * 1024;
    constexpr std::size_t MaxRivals = 5000;
    constexpr int CurrentSchema = 3;
    inline bool AdvanceCheckpointBudget(std::int64_t Bytes, std::int64_t& Written)
    {
        if (Written < 0 || Written > MaxCheckpointBytes || Bytes < 0 || Bytes > MaxCheckpointBytes - Written) return false;
        Written += Bytes;
        return true;
    }
    struct RecordRange { std::int64_t Offset = 0; std::int64_t Length = 0; };
    struct Index
    {
        int SchemaVersion = CurrentSchema;
        std::int64_t ActivityWindowStartUnix = 0;
        std::int64_t LastSavedUnix = 0;
        std::vector<RecordRange> Records;
        std::string Error;
        bool UnsupportedSchema = false;
    };

    // Input supplies Peek()/Get() (unsigned byte, or -1 at EOF), Position(), Failed().
    // No array/object tree or complete JSON string is ever retained.
    template<class Input> class Scanner
    {
    public:
        Scanner(Input& InInput, Index& InResult) : In(InInput), Result(InResult) {}
        bool Run()
        {
            if (In.Peek() == 0xef)
                if (In.Get() != 0xef || In.Get() != 0xbb || In.Get() != 0xbf) return Fail("Invalid UTF-8 BOM");
            Space();
            if (!Take('{')) return Fail("Rival checkpoint root must be an object");
            Space();
            bool HaveRivals = false, HaveSchema = false, HaveWindow = false, HaveSaved = false;
            if (!Take('}'))
            {
                while (true)
                {
                    std::string Key;
                    if (!String(&Key)) return false;
                    Space();
                    if (!Take(':')) return Fail("Missing colon in checkpoint root");
                    Space();
                    if (Key == "rivals" || Key == "Rivals")
                    {
                        if (HaveRivals) return Fail("Duplicate rivals field");
                        HaveRivals = true;
                        if (!Rivals()) return false;
                    }
                    else if (Key == "schemaVersion" || Key == "SchemaVersion")
                    {
                        if (HaveSchema) return Fail("Duplicate schemaVersion field");
                        HaveSchema = true;
                        std::int64_t Value = 0;
                        if (!Integer(Value)) return false;
                        if (Value > CurrentSchema)
                        {
                            Result.UnsupportedSchema = true;
                            return Fail("Rival checkpoint uses a newer schema");
                        }
                        if (Value < 0) return Fail("Invalid rival checkpoint schema");
                        Result.SchemaVersion = static_cast<int>(Value);
                    }
                    else if (Key == "activityWindowStartUnix" || Key == "ActivityWindowStartUnix")
                    {
                        if (HaveWindow) return Fail("Duplicate activityWindowStartUnix field");
                        HaveWindow = true;
                        if (!Integer(Result.ActivityWindowStartUnix)) return false;
                    }
                    else if (Key == "lastSavedUnix" || Key == "LastSavedUnix")
                    {
                        if (HaveSaved) return Fail("Duplicate lastSavedUnix field");
                        HaveSaved = true;
                        if (!Integer(Result.LastSavedUnix)) return false;
                    }
                    else if (!Value(1)) return false;
                    Space();
                    if (Take('}')) break;
                    if (!Take(',')) return Fail("Missing comma in checkpoint root");
                    Space();
                }
            }
            Space();
            if (In.Failed()) return Fail("Could not read rival checkpoint");
            if (In.Peek() != -1) return Fail("Trailing bytes after rival checkpoint");
            if (!HaveRivals) return Fail("Rival checkpoint has no rivals array");
            return true;
        }
    private:
        Input& In;
        Index& Result;
        bool Fail(const char* Message) { if (Result.Error.empty()) Result.Error = Message; return false; }
        bool Take(int Byte) { if (In.Peek() != Byte) return false; In.Get(); return true; }
        void Space() { while (In.Peek() == ' ' || In.Peek() == '\t' || In.Peek() == '\r' || In.Peek() == '\n') In.Get(); }
        static bool Digit(int C) { return C >= '0' && C <= '9'; }
        static int Hex(int C)
        {
            if (C >= '0' && C <= '9') return C - '0';
            if (C >= 'a' && C <= 'f') return C - 'a' + 10;
            if (C >= 'A' && C <= 'F') return C - 'A' + 10;
            return -1;
        }
        bool FourHex(std::uint32_t& Out)
        {
            Out = 0;
            for (int I = 0; I < 4; ++I)
            {
                const int H = Hex(In.Get());
                if (H < 0) return Fail("Invalid Unicode escape");
                Out = (Out << 4) | static_cast<std::uint32_t>(H);
            }
            return true;
        }
        bool Append(std::string* Out, std::uint32_t Code)
        {
            if (!Out) return true;
            if (Code <= 0x7f) Out->push_back(static_cast<char>(Code));
            else if (Code <= 0x7ff)
            {
                Out->push_back(static_cast<char>(0xc0 | (Code >> 6)));
                Out->push_back(static_cast<char>(0x80 | (Code & 0x3f)));
            }
            else if (Code <= 0xffff)
            {
                Out->push_back(static_cast<char>(0xe0 | (Code >> 12)));
                Out->push_back(static_cast<char>(0x80 | ((Code >> 6) & 0x3f)));
                Out->push_back(static_cast<char>(0x80 | (Code & 0x3f)));
            }
            else
            {
                Out->push_back(static_cast<char>(0xf0 | (Code >> 18)));
                Out->push_back(static_cast<char>(0x80 | ((Code >> 12) & 0x3f)));
                Out->push_back(static_cast<char>(0x80 | ((Code >> 6) & 0x3f)));
                Out->push_back(static_cast<char>(0x80 | (Code & 0x3f)));
            }
            return Out->size() <= 256 || Fail("Checkpoint root field name is too long");
        }
        bool String(std::string* Out = nullptr)
        {
            if (!Take('"')) return Fail("Expected JSON string");
            while (true)
            {
                int C = In.Get();
                if (C == '"') return true;
                if (C < 0x20) return Fail("Unterminated string or unescaped control byte");
                std::uint32_t Code = static_cast<std::uint32_t>(C);
                if (C == '\\')
                {
                    C = In.Get();
                    switch (C)
                    {
                    case '"': case '\\': case '/': Code = static_cast<std::uint32_t>(C); break;
                    case 'b': Code = 8; break;
                    case 'f': Code = 12; break;
                    case 'n': Code = 10; break;
                    case 'r': Code = 13; break;
                    case 't': Code = 9; break;
                    case 'u':
                        if (!FourHex(Code)) return false;
                        if (Code >= 0xd800 && Code <= 0xdbff)
                        {
                            std::uint32_t Low = 0;
                            if (!Take('\\') || !Take('u') || !FourHex(Low) || Low < 0xdc00 || Low > 0xdfff)
                                return Fail("Invalid Unicode surrogate pair");
                            Code = 0x10000 + ((Code - 0xd800) << 10) + (Low - 0xdc00);
                        }
                        else if (Code >= 0xdc00 && Code <= 0xdfff) return Fail("Unpaired Unicode surrogate");
                        break;
                    default: return Fail("Invalid JSON escape");
                    }
                }
                else if (C >= 0x80)
                {
                    int Remaining = 0;
                    std::uint32_t Minimum = 0;
                    if (C >= 0xc2 && C <= 0xdf) { Remaining = 1; Code = C & 0x1f; Minimum = 0x80; }
                    else if (C >= 0xe0 && C <= 0xef) { Remaining = 2; Code = C & 0x0f; Minimum = 0x800; }
                    else if (C >= 0xf0 && C <= 0xf4) { Remaining = 3; Code = C & 0x07; Minimum = 0x10000; }
                    else return Fail("Invalid UTF-8 in checkpoint");
                    for (int I = 0; I < Remaining; ++I)
                    {
                        C = In.Get();
                        if (C < 0x80 || C > 0xbf) return Fail("Invalid UTF-8 continuation");
                        Code = (Code << 6) | (C & 0x3f);
                    }
                    if (Code < Minimum || Code > 0x10ffff || (Code >= 0xd800 && Code <= 0xdfff)) return Fail("Invalid UTF-8 code point");
                }
                if (!Append(Out, Code)) return false;
            }
        }
        bool Number()
        {
            Take('-');
            if (!Digit(In.Peek())) return Fail("Invalid JSON number");
            if (!Take('0')) while (Digit(In.Peek())) In.Get();
            if (Take('.'))
            {
                if (!Digit(In.Peek())) return Fail("Invalid JSON fraction");
                while (Digit(In.Peek())) In.Get();
            }
            if (Take('e') || Take('E'))
            {
                if (!Take('+')) Take('-');
                if (!Digit(In.Peek())) return Fail("Invalid JSON exponent");
                while (Digit(In.Peek())) In.Get();
            }
            return true;
        }
        bool Integer(std::int64_t& Out)
        {
            const bool Negative = Take('-');
            if (!Digit(In.Peek())) return Fail("Expected integer checkpoint metadata");
            const std::uint64_t Limit = static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()) + (Negative ? 1ULL : 0ULL);
            std::uint64_t Magnitude = 0;
            const bool Zero = In.Peek() == '0';
            do
            {
                const auto D = static_cast<std::uint64_t>(In.Get() - '0');
                if (Magnitude > (Limit - D) / 10) return Fail("Checkpoint metadata integer overflow");
                Magnitude = Magnitude * 10 + D;
                if (Zero) break;
            } while (Digit(In.Peek()));
            if (In.Peek() == '.' || In.Peek() == 'e' || In.Peek() == 'E' || Digit(In.Peek())) return Fail("Expected canonical integer checkpoint metadata");
            Out = Negative ? (Magnitude == Limit ? std::numeric_limits<std::int64_t>::min() : -static_cast<std::int64_t>(Magnitude)) : static_cast<std::int64_t>(Magnitude);
            return true;
        }
        bool Literal(const char* Text)
        {
            while (*Text) if (In.Get() != *Text++) return Fail("Invalid JSON literal");
            return true;
        }
        bool Value(int Depth)
        {
            if (Depth > 64) return Fail("Checkpoint JSON nesting exceeds 64 levels");
            Space();
            switch (In.Peek())
            {
            case '"': return String();
            case '{':
                In.Get(); Space();
                if (Take('}')) return true;
                while (true)
                {
                    if (!String()) return false;
                    Space(); if (!Take(':')) return Fail("Missing colon in JSON object");
                    if (!Value(Depth + 1)) return false;
                    Space(); if (Take('}')) return true;
                    if (!Take(',')) return Fail("Missing comma in JSON object");
                    Space();
                }
            case '[':
                In.Get(); Space();
                if (Take(']')) return true;
                while (true)
                {
                    if (!Value(Depth + 1)) return false;
                    Space(); if (Take(']')) return true;
                    if (!Take(',')) return Fail("Missing comma in JSON array");
                    Space();
                }
            case 't': return Literal("true");
            case 'f': return Literal("false");
            case 'n': return Literal("null");
            default: return Number();
            }
        }
        bool Rivals()
        {
            if (!Take('[')) return Fail("Rivals must be an array");
            Space();
            if (Take(']')) return true;
            while (true)
            {
                if (Result.Records.size() >= MaxRivals) return Fail("Checkpoint exceeds the 5000-rival safety limit");
                if (In.Peek() != '{') return Fail("Each rival record must be an object");
                RecordRange Range; Range.Offset = In.Position();
                if (!Value(1)) return false;
                Range.Length = In.Position() - Range.Offset;
                if (Range.Length > MaxLegacyRecordBytes) return Fail("One legacy rival record exceeds 64 MiB; offline repair is required");
                Result.Records.push_back(Range);
                Space(); if (Take(']')) return true;
                if (!Take(',')) return Fail("Missing comma in rivals array");
                Space();
            }
        }
    };
}
