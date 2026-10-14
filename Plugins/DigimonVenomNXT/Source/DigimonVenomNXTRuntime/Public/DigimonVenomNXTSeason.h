#pragma once
#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
class UDigimonVenomNXTDataSubsystem;

/** Private career transactions. Call on a copy, persist it, then publish the committed profile. */
namespace DigimonVenomNXTSeason
{
    /** Repairs player style IDs and upgrades bot appearances only; never alters career or battle progress. */
    DIGIMONVENOMNXTRUNTIME_API bool ReconcileTamerStyles(FDigimonPlayerProfile& Profile);
    /** Returns true only when initialization/migration changed persistent career state. Never rebooks an existing card. */
    DIGIMONVENOMNXTRUNTIME_API bool EnsureCareer(FDigimonPlayerProfile& Profile, const UDigimonVenomNXTDataSubsystem* Data);
    DIGIMONVENOMNXTRUNTIME_API TArray<FDigimonOwnedPartner> BuildScheduledOpponent(const FDigimonPlayerProfile& Profile, const UDigimonVenomNXTDataSubsystem* Data);
    DIGIMONVENOMNXTRUNTIME_API bool BeginMatch(FDigimonPlayerProfile& Profile, FString& OutContextId, FString& OutError);
    DIGIMONVENOMNXTRUNTIME_API bool SettleMatch(FDigimonPlayerProfile& Profile, const FString& ContextId, bool bWon, bool bDraw,
        const UDigimonVenomNXTDataSubsystem* Data, FString& OutMessage);
    DIGIMONVENOMNXTRUNTIME_API bool AdvanceWeek(FDigimonPlayerProfile& Profile, const UDigimonVenomNXTDataSubsystem* Data, FString& OutMessage);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonSeasonTamer* FindTamer(const FDigimonSeasonCareer& Career, const FString& Id);
    DIGIMONVENOMNXTRUNTIME_API const FDigimonSeasonMatch* GetPlayerMatch(const FDigimonSeasonCareer& Career);
    DIGIMONVENOMNXTRUNTIME_API FString GetScheduledOpponentName(const FDigimonPlayerProfile& Profile);
    DIGIMONVENOMNXTRUNTIME_API FString CalendarLabel(const FDigimonSeasonCareer& Career, int32 DayOffset = INDEX_NONE);
    DIGIMONVENOMNXTRUNTIME_API int32 GetRank(const FDigimonSeasonCareer& Career);
    DIGIMONVENOMNXTRUNTIME_API int32 NextOpponentLevel(const FDigimonSeasonCareer& Career);
    DIGIMONVENOMNXTRUNTIME_API int64 MonthRewardPreview(const FDigimonSeasonCareer& Career);
    DIGIMONVENOMNXTRUNTIME_API int64 YearRewardPreview(const FDigimonSeasonCareer& Career);
}
