#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

/** Presentation only: authoritative receipt interpolation and replication-order reconciliation. */
namespace DigimonVenomNXTHealingPresentationCore
{
struct Vitals
{
    int HP = 0, SP = 0, MaxHP = 1, MaxSP = 1;
};

inline Vitals Clamp(Vitals Value)
{
    Value.MaxHP = std::max(1, Value.MaxHP);
    Value.MaxSP = std::max(0, Value.MaxSP);
    Value.HP = std::clamp(Value.HP, 0, Value.MaxHP);
    Value.SP = std::clamp(Value.SP, 0, Value.MaxSP);
    return Value;
}

inline bool Same(const Vitals& A, const Vitals& B)
{
    return A.HP == B.HP && A.SP == B.SP && A.MaxHP == B.MaxHP && A.MaxSP == B.MaxSP;
}

struct Track
{
    Vitals From, To;
    double Elapsed = 0.0;
    double StartedAt = 0.0;
    std::int64_t ReceiptRevision = 0;
    bool Initialized = false;
    bool AwaitingProfile = false;
    bool ShowingReceipt = false;
    static constexpr double FillDuration = 1.35;
    static constexpr double EffectDuration = 2.15;

    void Reset(Vitals Value)
    {
        From = To = Clamp(Value);
        Elapsed = EffectDuration;
        Initialized = true;
        AwaitingProfile = ShowingReceipt = false;
    }

    /** Only an actual non-negative server-confirmed increase may produce healing effects. */
    bool Confirm(Vitals Before, Vitals After, std::int64_t Revision = 0, double StartTime = 0.0)
    {
        Before = Clamp(Before); After = Clamp(After);
        if (Before.MaxHP != After.MaxHP || Before.MaxSP != After.MaxSP ||
            After.HP < Before.HP || After.SP < Before.SP ||
            (After.HP == Before.HP && After.SP == Before.SP)) return false;
        From = Before; To = After; Elapsed = 0.0; StartedAt = StartTime;
        ReceiptRevision = std::max<std::int64_t>(0, Revision);
        Initialized = AwaitingProfile = ShowingReceipt = true;
        return true;
    }

    /** The saved revision fences every older profile snapshot, even one preceding the last battle. */
    void Observe(Vitals Snapshot, std::int64_t ProfileRevision = 0)
    {
        Snapshot = Clamp(Snapshot);
        if (!Initialized) { Reset(Snapshot); return; }
        if (ShowingReceipt && ProfileRevision < ReceiptRevision) return;
        if (ShowingReceipt && Same(Snapshot, To)) { AwaitingProfile = false; return; }
        if (ShowingReceipt) AwaitingProfile = false;
        // A different snapshot is new information (battle, item, evolution, etc.).
        if (!Same(Snapshot, To)) Reset(Snapshot);
    }

    void Advance(double Seconds)
    {
        if (Seconds > 0.0 && std::isfinite(Seconds)) Elapsed = std::min(EffectDuration, Elapsed + Seconds);
    }

    /** A hidden widget need not tick: reopening uses the original receipt's monotonic clock. */
    void AdvanceClock(double Now)
    {
        if (ShowingReceipt && std::isfinite(Now) && std::isfinite(StartedAt))
            Elapsed = std::max(Elapsed, std::clamp(Now - StartedAt, 0.0, EffectDuration));
    }

    bool IsAnimating() const { return ShowingReceipt && Elapsed < EffectDuration; }
    double FillAlpha() const
    {
        const double T = std::clamp(Elapsed / FillDuration, 0.0, 1.0);
        return T * T * (3.0 - 2.0 * T);
    }
    Vitals Display() const
    {
        if (!ShowingReceipt) return To;
        const double Alpha = FillAlpha();
        Vitals Out = To;
        Out.HP = static_cast<int>(std::floor(From.HP + (static_cast<double>(To.HP) - From.HP) * Alpha + 0.5));
        Out.SP = static_cast<int>(std::floor(From.SP + (static_cast<double>(To.SP) - From.SP) * Alpha + 0.5));
        return Clamp(Out);
    }
};
}
