#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <deque>
#include <string>
#include <unordered_set>

/** Client-only cue policy. Asset stems refer to the source game interaction and combat cues, never BGM. */
namespace DigimonVenomNXTAudioCueCore
{
enum class Cue : unsigned char
{
    UIHover, UIClick, UIBack, UINavigate, Confirm, Error, Heal, Item, Purchase,
    PhysicalAttack, SpecialAttack, Hit, Guard, Knockout, Victory, Defeat, Flee,
    Travel, Interaction, Encounter, EffectiveHit, Count
};
struct Descriptor
{
    const char* Name;
    const char* Stem;
    bool UI;
    float Gain;
    double Cooldown;
    float Pitch = 1.0f;
};
inline const Descriptor* Describe(Cue Value)
{
    static constexpr Descriptor Cues[] = {
        {"UIHover", "ui_se000", true, .24f, .12, 1.18f},
        {"UIClick", "ui_se001", true, .48f, .065},
        {"UIBack", "ui_se002", true, .42f, .12, .84f},
        {"UINavigate", "ui_se000", true, .40f, .12, 1.07f},
        {"Confirm", "ui_se001", true, .38f, .20},
        {"Error", "ui_se004", true, .26f, .30, .84f},
        {"Heal", "se011", false, .54f, .20},
        {"Item", "se009", false, .38f, .15},
        {"Purchase", "ui_se009", true, .45f, .20, 1.10f},
        {"PhysicalAttack", "se014", false, .36f, .065},
        {"SpecialAttack", "se014", false, .42f, .065},
        {"Hit", "se014", false, .42f, .065},
        {"Guard", "se014", false, .36f, .10},
        {"Knockout", "se014", false, .32f, .15},
        {"Victory", "ui_se030", false, .62f, .40},
        {"Defeat", "ui_se004", false, .38f, .40, .90f},
        {"Flee", "ui_se002", false, .80f, .25},
        {"Travel", "ui_se003", false, .36f, .35},
        {"Interaction", "ui_se001", true, .44f, .20, .95f},
        {"Encounter", "ui_se003", false, .30f, .30},
        {"EffectiveHit", "se014", false, .42f, .065}
    };
    const auto Index = static_cast<std::size_t>(Value);
    return Index < static_cast<std::size_t>(Cue::Count) ? &Cues[Index] : nullptr;
}
inline float Volume(float Value)
{
    return std::isfinite(Value) ? std::max(0.0f, std::min(1.0f, Value)) : 0.0f;
}
inline float Mix(float Master, float Channel, float Gain)
{
    return Volume(Master) * Volume(Channel) * Volume(Gain);
}
/** Bounded event receipts survive widget rebuilds; hover storms cannot drown gameplay. */
class Gate
{
public:
    bool Accept(Cue Value, double Now, const std::string& EventKey = {})
    {
        const Descriptor* D = Describe(Value);
        if (!D || !std::isfinite(Now)) return false;
        if (!EventKey.empty())
        {
            if (Receipts.count(EventKey) != 0) return false;
            Receipts.insert(EventKey);
            ReceiptOrder.push_back(EventKey);
            while (ReceiptOrder.size() > 4096)
            {
                Receipts.erase(ReceiptOrder.front());
                ReceiptOrder.pop_front();
            }
        }
        const auto Index = static_cast<std::size_t>(Value);
        if (Played[Index] && Now >= Last[Index] && Now - Last[Index] < D->Cooldown) return false;
        Played[Index] = true;
        Last[Index] = Now;
        return true;
    }
    std::size_t ReceiptCount() const { return Receipts.size(); }
private:
    std::array<double, static_cast<std::size_t>(Cue::Count)> Last{};
    std::array<bool, static_cast<std::size_t>(Cue::Count)> Played{};
    std::deque<std::string> ReceiptOrder;
    std::unordered_set<std::string> Receipts;
};
}
