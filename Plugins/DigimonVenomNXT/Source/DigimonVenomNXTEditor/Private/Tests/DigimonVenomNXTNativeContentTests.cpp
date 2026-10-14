#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "DigimonVenomNXTEditorLibrary.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTNativeSourceTest,
    "DigimonVenomNXT.Content.NativeSourceIntegrity", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTNativeSourceTest::RunTest(const FString& Parameters)
{
    FString Report;
    const bool bValid = UDigimonVenomNXTEditorLibrary::ValidateBundledContent(Report);
    AddInfo(Report);
    TestTrue(TEXT("Complete source catalog, checksums, map grids and native animation references are valid"), bValid);
    return bValid;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTImportedTamerTest,
    "DigimonVenomNXT.Content.ImportedTamerRoster", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTImportedTamerTest::RunTest(const FString& Parameters)
{
    bool bAllReady = true;
    for (const DigimonVenomNXTTamers::FStyle& Style : DigimonVenomNXTTamers::GetRoster())
    {
        UDigimonVenomNXTTamerAnimationSet* Set = LoadObject<UDigimonVenomNXTTamerAnimationSet>(nullptr, *DigimonVenomNXTTamers::AnimationPath(Style.Id));
        if (!Set)
        {
            AddError(TEXT("Run Build Complete Game Content first. Missing tamer: ") + Style.Id.ToString());
            bAllReady = false; continue;
        }
        for (EDigimonFacing Facing : {EDigimonFacing::Down, EDigimonFacing::DownLeft, EDigimonFacing::Left, EDigimonFacing::UpLeft,
            EDigimonFacing::Up, EDigimonFacing::UpRight, EDigimonFacing::Right, EDigimonFacing::DownRight})
        {
            UPaperFlipbook* Book = Set->GetForFacing(Facing);
            if (!Book || Book->GetNumKeyFrames() == 0 || Book->GetTotalDuration() <= 0.f || !Book->GetSpriteAtTime(0.f, false))
            {
                AddError(TEXT("Incomplete directional tamer animation: ") + Style.Id.ToString());
                bAllReady = false;
            }
        }
        bAllReady &= TestTrue(TEXT("Native tamer display multiplier is positive"), Set->DisplayScale > 0.f);
    }
    bAllReady &= TestTrue(TEXT("All registered map sprites were imported successfully"), UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent());
    return bAllReady;
}
#endif
