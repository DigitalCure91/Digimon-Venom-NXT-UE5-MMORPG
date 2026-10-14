// Executes the same arithmetic functions used by authoritative trade settlement.
// Durable journal, consent and RPC integration are tested separately.
#include "../Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTTradeCore.h"
#include <cstdlib>
#include <iostream>
#include <limits>

namespace T = DigimonVenomNXTTradeCore;
namespace
{
int Checks = 0;
void Check(bool Value, const char* Message)
{
    ++Checks;
    if (!Value) { std::cerr << Message << '\n'; std::exit(1); }
}
void Rejected(std::int64_t A, std::int64_t B, std::int64_t OfferA,
    std::int64_t OfferB, std::int64_t Cap)
{
    std::int64_t OutA = 4321, OutB = 1234;
    Check(!T::Exchange(A, B, OfferA, OfferB, Cap, OutA, OutB), "invalid exchange accepted");
    Check(OutA == 4321 && OutB == 1234, "failed exchange changed output balances");
}
}

int main()
{
    std::int64_t A = 0, B = 0;
    Check(T::Exchange(1000, 100, 250, 50, T::MaxCredits, A, B) && A == 800 && B == 300,
        "two-way money trade did not net both contributions");
    Check(T::Exchange(20, 100, 5, 40, T::MaxRubies, A, B) && A == 55 && B == 65,
        "two-way ruby trade did not net both contributions");
    Check(T::Exchange(100, 0, 100, 0, T::MaxCredits, A, B) && A == 0 && B == 100,
        "exact-balance purchase failed");
    Check(T::Exchange(T::MaxCredits, T::MaxCredits, T::MaxCredits, T::MaxCredits,
        T::MaxCredits, A, B) && A == T::MaxCredits && B == T::MaxCredits,
        "full-cap simultaneous swap overflowed");
    Check(T::Exchange(0, 0, 0, 0, 0, A, B) && A == 0 && B == 0,
        "zero-currency partner-only swap failed");
    Check(T::Exchange(0, T::MaxRubies, 0, T::MaxRubies, T::MaxRubies, A, B) &&
        A == T::MaxRubies && B == 0, "maximum ruby gift failed");
    for (const std::int64_t Cap : {T::MaxCredits, T::MaxRubies})
    {
        Rejected(-1, 0, 0, 0, Cap);
        Rejected(0, -1, 0, 0, Cap);
        Rejected(1, 1, -1, 0, Cap);
        Rejected(1, 1, 0, -1, Cap);
        Rejected(10, 10, 11, 0, Cap);
        Rejected(10, 10, 0, 11, Cap);
        Rejected(Cap, 1, 0, 1, Cap);
        Rejected(1, Cap, 1, 0, Cap);
        Rejected(Cap + 1, 0, 0, 0, Cap);
        Rejected(0, Cap + 1, 0, 0, Cap);
        Rejected(std::numeric_limits<std::int64_t>::min(), Cap, 0, 0, Cap);
        Rejected(Cap, 0, std::numeric_limits<std::int64_t>::max(), 0, Cap);
    }
    Rejected(0, 0, 0, 0, -1);
    // Exhaust every balance/offer combination for a small independent economy.
    // This covers conservation, recipient cap failure and symmetry together.
    for (int BalanceA = 0; BalanceA <= 12; ++BalanceA)
        for (int BalanceB = 0; BalanceB <= 12; ++BalanceB)
            for (int OfferA = 0; OfferA <= BalanceA; ++OfferA)
                for (int OfferB = 0; OfferB <= BalanceB; ++OfferB)
                {
                    A = -99; B = -98;
                    const int ExpectedA = BalanceA - OfferA + OfferB;
                    const int ExpectedB = BalanceB - OfferB + OfferA;
                    const bool Valid = ExpectedA <= 12 && ExpectedB <= 12;
                    Check(T::Exchange(BalanceA, BalanceB, OfferA, OfferB, 12, A, B) == Valid,
                        "exchange acceptance differs from finite exhaustive economy");
                    if (Valid)
                    {
                        Check(A == ExpectedA && B == ExpectedB && A + B == BalanceA + BalanceB,
                            "accepted exchange created or lost currency");
                        std::int64_t ReverseA, ReverseB;
                        Check(T::Exchange(BalanceB, BalanceA, OfferB, OfferA, 12, ReverseB, ReverseA) &&
                            ReverseA == A && ReverseB == B, "participant order changed settlement");
                    }
                    else Check(A == -99 && B == -98, "rejected exchange overwrote outputs");
                }
    Check(T::ValidPrice(1, 0) && T::ValidPrice(0, 1) && T::ValidPrice(1000, 30),
        "money-only, ruby-only or mixed listing price rejected");
    Check(T::ValidPrice(T::MaxCredits, T::MaxRubies), "maximum valid price rejected");
    Check(!T::ValidPrice(0, 0) && !T::ValidPrice(-1, 0) && !T::ValidPrice(0, -1),
        "free or negative listing price accepted");
    Check(!T::ValidPrice(T::MaxCredits + 1, 0) && !T::ValidPrice(0, T::MaxRubies + 1),
        "price beyond exact/persistent currency cap accepted");
    Check(T::ReceiveFits(1000, 6, 6) && T::ReceiveFits(994, 0, 6) && T::ReceiveFits(1000, 1, 1),
        "full collection swap or exact capacity arrival rejected");
    Check(!T::ReceiveFits(1000, 0, 1) && !T::ReceiveFits(999, 0, 2), "collection overflow accepted");
    Check(!T::ReceiveFits(-1, 0, 1) && !T::ReceiveFits(5, -1, 0) &&
        !T::ReceiveFits(5, 6, 0) && !T::ReceiveFits(5, 0, -1), "invalid collection counts accepted");
    std::cout << "Trade settlement core: " << Checks << " conservation, capacity and currency boundary checks passed.\n";
}
