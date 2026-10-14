#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTTamerCore.h"

namespace DigimonVenomNXTTamers
{
const TArray<FStyle>& GetRoster()
{
    static const TArray<FStyle> Styles = {
        { FName(TEXT("tamer_002")), TEXT("Dawn Tamer \u00b7 male"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_003")), TEXT("Dawn Tamer \u00b7 female"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_004")), TEXT("Dusk Tamer \u00b7 male"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_005")), TEXT("Dusk Tamer \u00b7 female"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_014")), TEXT("Digital World Tamer 014"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_015")), TEXT("Digital World Tamer 015"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_016")), TEXT("Digital World Tamer 016"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_017")), TEXT("Digital World Tamer 017"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_018")), TEXT("Digital World Tamer 018"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_019")), TEXT("Digital World Tamer 019"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_020")), TEXT("Digital World Tamer 020"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_021")), TEXT("Digital World Tamer 021"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_022")), TEXT("Digital World Tamer 022"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_023")), TEXT("Digital World Tamer 023"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_024")), TEXT("Digital World Tamer 024"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_025")), TEXT("Digital World Tamer 025"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_026")), TEXT("Digital World Tamer 026"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_027")), TEXT("Digital World Tamer 027"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_028")), TEXT("Digital World Tamer 028"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_029")), TEXT("Digital World Tamer 029"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_030")), TEXT("Digital World Tamer 030"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_031")), TEXT("Digital World Tamer 031"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_032")), TEXT("Digital World Tamer 032"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_033")), TEXT("Digital World Tamer 033"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_034")), TEXT("Digital World Tamer 034"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_035")), TEXT("Digital World Tamer 035"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_036")), TEXT("Digital World Tamer 036"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_037")), TEXT("Digital World Tamer 037"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_038")), TEXT("Digital World Tamer 038"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_039")), TEXT("Digital World Tamer 039"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_044")), TEXT("Digital World Tamer 044"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_045")), TEXT("Digital World Tamer 045"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_046")), TEXT("Digital World Tamer 046"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_047")), TEXT("Digital World Tamer 047"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_048")), TEXT("Digital World Tamer 048"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_049")), TEXT("Digital World Tamer 049"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_050")), TEXT("Digital World Tamer 050"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_051")), TEXT("Digital World Tamer 051"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_052")), TEXT("Digital World Tamer 052"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_053")), TEXT("Digital World Tamer 053"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_054")), TEXT("Digital World Tamer 054"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_055")), TEXT("Digital World Tamer 055"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_056")), TEXT("Digital World Tamer 056"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_057")), TEXT("Digital World Tamer 057"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_058")), TEXT("Digital World Tamer 058"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_059")), TEXT("Digital World Tamer 059"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_060")), TEXT("Digital World Tamer 060"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_061")), TEXT("Digital World Tamer 061"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_062")), TEXT("Digital World Tamer 062"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_063")), TEXT("Digital World Tamer 063"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_064")), TEXT("Digital World Tamer 064"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_065")), TEXT("Digital World Tamer 065"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_066")), TEXT("Digital World Tamer 066"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_067")), TEXT("Digital World Tamer 067"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_068")), TEXT("Digital World Tamer 068"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_069")), TEXT("Digital World Tamer 069"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_082")), TEXT("Digital World Tamer 082"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_083")), TEXT("Digital World Tamer 083"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_084")), TEXT("Digital World Tamer 084"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_085")), TEXT("Digital World Tamer 085"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_086")), TEXT("Digital World Tamer 086"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_087")), TEXT("Digital World Tamer 087"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_088")), TEXT("Digital World Tamer 088"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
        { FName(TEXT("tamer_089")), TEXT("Digital World Tamer 089"), TEXT("Dawn ROM MCHR_CHR/PAL/ANM; tile decoding, RLE decompression and per-direction animation-table flips; no redrawing") },
    };
    return Styles;
}
bool IsValidStyle(FName StyleId)
{
    return GetRoster().ContainsByPredicate([StyleId](const FStyle& Entry) { return Entry.Id == StyleId; });
}
FName StyleForIndex(int32 Index)
{
    const TArray<FStyle>& Styles = GetRoster();
    return Styles.IsValidIndex(Index) ? Styles[Index].Id : Styles[0].Id;
}
FName StyleForStableId(const FString& StableId)
{
    const FTCHARToUTF8 Bytes(*StableId);
    return StyleForIndex(DigimonVenomNXTTamerCore::StyleIndexForKey(std::string_view(Bytes.Get(), Bytes.Length())));
}
FString DisplayName(FName StyleId)
{
    if (const FStyle* Found = GetRoster().FindByPredicate([StyleId](const FStyle& Entry) { return Entry.Id == StyleId; })) return Found->Name;
    return TEXT("Unknown tamer style");
}
FString ThumbnailPath(FName StyleId)
{
    if (!IsValidStyle(StyleId)) return FString();
    const FString Id = StyleId.ToString().ToLower();
    return FString::Printf(TEXT("/DigimonVenomNXT/Generated/Tamers/%s/down/T_%s_down_00.T_%s_down_00"), *Id, *Id, *Id);
}
FString AnimationPath(FName StyleId)
{
    if (!IsValidStyle(StyleId)) return FString();
    const FString Id = StyleId.ToString().ToLower();
    return FString::Printf(TEXT("/DigimonVenomNXT/Generated/Tamers/%s/DA_%s_Animation.DA_%s_Animation"), *Id, *Id, *Id);
}
}
