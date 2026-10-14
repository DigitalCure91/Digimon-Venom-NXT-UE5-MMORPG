#pragma once
#include <algorithm>
#include <cstdint>

/** Engine-independent progression rules. All gains use the level BEFORE changing form. */
namespace DigimonVenomNXTEvolutionCore
{
    struct Rules
    {
        int MaxABI = 200;
        int MinimumDeEvolutionLevel = 5;
        int EvolutionBaseABI = 2;
        int EvolutionLevelsPerABI = 10;
        int DeEvolutionBaseABI = 5;
        int DeEvolutionLevelsPerABI = 5;
    };

    inline int Clamp(int Value, int Low, int High) { return std::max(Low, std::min(Value, High)); }
    inline int MaximumABI(int Configured) { return Clamp(Configured, 1, 200); }
    inline int MinimumChangeLevel(bool DeEvolution, const Rules& R = {})
    {
        return DeEvolution ? Clamp(R.MinimumDeEvolutionLevel, 2, 200) : 2;
    }
    inline int ABIGain(int SourceTier, int Level, bool DeEvolution, const Rules& R = {})
    {
        if (Level < MinimumChangeLevel(DeEvolution, R)) return 0;
        (void)SourceTier; // Source species stage never changes the earned ABI amount.
        const int SafeLevel = Clamp(Level, 1, 200);
        const int Base = Clamp(DeEvolution ? R.DeEvolutionBaseABI : R.EvolutionBaseABI, 1, 200);
        const int Divisor = Clamp(DeEvolution ? R.DeEvolutionLevelsPerABI : R.EvolutionLevelsPerABI, 1, 200);
        return Clamp(Base + SafeLevel / Divisor, 1, MaximumABI(R.MaxABI));
    }
    inline int ResultABI(int Current, int Gain, int MaxABI = 200)
    {
        const int Cap = MaximumABI(MaxABI);
        // A lowered setting must never erase permanent ABI earned by an existing partner.
        if (Current >= Cap) return Current;
        return std::min(Cap, Clamp(Current, 0, Cap) + Clamp(Gain, 0, Cap));
    }
    inline bool MeetsRequirements(int Level, int CAM, int ABI, int RequiredLevel, int RequiredCAM, int RequiredABI)
    {
        return Level >= std::max(2, RequiredLevel) && CAM >= std::max(0, RequiredCAM) && ABI >= std::max(0, RequiredABI);
    }
    inline int TrainingCapacity(int ABI, int Base = 300)
    {
        (void)ABI;
        return Clamp(Base, 0, 1000);
    }
    /** Source training: one point in any stat uses one point of the shared budget. */
    inline std::int64_t TrainingUsedTenths(int HP, int SP, int Attack, int Defense, int Spirit, int Speed)
    {
        return 10LL * (static_cast<std::int64_t>(std::max(0, HP)) + std::max(0, SP) + std::max(0, Attack) +
                std::max(0, Defense) + std::max(0, Spirit) + std::max(0, Speed));
    }
    inline bool CanTrain(int ABI, std::int64_t UsedTenths, int AddedTenths, int Base = 300)
    {
        const std::int64_t Capacity = static_cast<std::int64_t>(TrainingCapacity(ABI, Base)) * 10;
        return UsedTenths >= 0 && AddedTenths > 0 && AddedTenths <= Capacity && UsedTenths <= Capacity - AddedTenths;
    }
    inline bool CanTrainStat(int Current, int Amount, int PerStatMaximum = 100)
    {
        return Current >= 0 && Amount > 0 && Amount <= PerStatMaximum && Current <= PerStatMaximum - Amount;
    }
    /** No reconstruction: ownership, variant, nickname, CAM and permanent training survive. */
    template<class TPartner, class TSpeciesId>
    void ApplyIdentityPreservingTransform(TPartner& Partner, const TSpeciesId& TargetSpeciesId, int NewABI)
    {
        Partner.SpeciesId = TargetSpeciesId;
        Partner.Level = 1;
        Partner.Experience = 0;
        Partner.ABI = std::max(0, NewABI);
    }
}
