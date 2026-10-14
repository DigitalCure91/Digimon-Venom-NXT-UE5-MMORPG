#include "DigimonVenomNXTVideoSettingsWidget.h"
#include "DigimonVenomNXTVideoSettingsSubsystem.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "HAL/PlatformTime.h"
#include "InputCoreTypes.h"
#include "Styling/CoreStyle.h"

namespace DigimonVideoUI
{
const FLinearColor Ink(0.010f, 0.025f, 0.043f, 1.0f);
const FLinearColor Panel(0.020f, 0.062f, 0.085f, 1.0f);
const FLinearColor White(0.95f, 0.99f, 1.0f, 1.0f);
const FLinearColor Muted(0.65f, 0.79f, 0.83f, 1.0f);
const FLinearColor Green(0.30f, 1.0f, 0.61f, 1.0f);
const FLinearColor Cyan(0.22f, 0.87f, 1.0f, 1.0f);
const FLinearColor Gold(1.0f, 0.80f, 0.35f, 1.0f);

UTextBlock* Text(UWidgetTree* Tree, const FString& Value, int32 Size = 12, FLinearColor Color = White, bool bBold = false)
{
    UTextBlock* Result = Tree->ConstructWidget<UTextBlock>();
    Result->SetText(FText::FromString(Value)); Result->SetColorAndOpacity(Color); Result->SetAutoWrapText(true);
    FSlateFontInfo Font = Result->GetFont(); Font.Size = Size; Font.TypefaceFontName = bBold ? FName(TEXT("Bold")) : FName(TEXT("Regular")); Result->SetFont(Font);
    return Result;
}
void Set(UTextBlock* Widget, const FString& Value) { if (Widget) Widget->SetText(FText::FromString(Value)); }
void Add(UVerticalBox* Box, UWidget* Child, float Padding = 3.0f, bool bFill = false)
{
    if (UVerticalBoxSlot* ChildSlot = Box->AddChildToVerticalBox(Child))
    {
        ChildSlot->SetPadding(FMargin(0, Padding)); ChildSlot->SetHorizontalAlignment(HAlign_Fill);
        if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
}
void Row(UHorizontalBox* Box, UWidget* Child, bool bFill = true, float Padding = 3.0f)
{
    if (UHorizontalBoxSlot* ChildSlot = Box->AddChildToHorizontalBox(Child))
    {
        ChildSlot->SetPadding(FMargin(Padding, 0)); ChildSlot->SetVerticalAlignment(VAlign_Center);
        if (bFill) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
}
UBorder* Card(UWidgetTree* Tree, FLinearColor Accent = Cyan)
{
    UBorder* Result = Tree->ConstructWidget<UBorder>();
    Result->SetBrush(FSlateRoundedBoxBrush(Panel, 8.0f, Accent.CopyWithNewOpacity(0.28f), 1.0f));
    Result->SetPadding(FMargin(12, 9)); return Result;
}
FString ResolutionLabel(const FIntPoint& Value) { return FString::Printf(TEXT("%d x %d"), Value.X, Value.Y); }

float ReadValue(const FDigimonVideoSettings& S, FName Key)
{
    if (Key == TEXT("DisplayMode")) return static_cast<float>(S.DisplayMode);
#define DVN_VIDEO_READ(Field) if (Key == TEXT(#Field)) return static_cast<float>(S.Field)
    DVN_VIDEO_READ(ResolutionScale); DVN_VIDEO_READ(FrameRateLimit); DVN_VIDEO_READ(bVSync);
    DVN_VIDEO_READ(Gamma);
    DVN_VIDEO_READ(bDynamicResolution); DVN_VIDEO_READ(bHDR); DVN_VIDEO_READ(HDRNits);
    DVN_VIDEO_READ(ViewDistanceQuality); DVN_VIDEO_READ(AntiAliasingMethod); DVN_VIDEO_READ(AntiAliasingQuality);
    DVN_VIDEO_READ(ShadowQuality); DVN_VIDEO_READ(GlobalIlluminationQuality); DVN_VIDEO_READ(ReflectionQuality);
    DVN_VIDEO_READ(PostProcessQuality); DVN_VIDEO_READ(TextureQuality); DVN_VIDEO_READ(EffectsQuality);
    DVN_VIDEO_READ(FoliageQuality); DVN_VIDEO_READ(ShadingQuality); DVN_VIDEO_READ(LandscapeQuality);
    DVN_VIDEO_READ(bMotionBlur); DVN_VIDEO_READ(bDepthOfField); DVN_VIDEO_READ(bBloom);
    DVN_VIDEO_READ(bLensFlare); DVN_VIDEO_READ(bChromaticAberration); DVN_VIDEO_READ(bAmbientOcclusion);
#undef DVN_VIDEO_READ
    return 0.0f;
}
void WriteValue(FDigimonVideoSettings& S, FName Key, float Value)
{
    if (Key == TEXT("DisplayMode")) S.DisplayMode = static_cast<EDigimonDisplayMode>(FMath::RoundToInt(Value));
#define DVN_VIDEO_WRITE_FLOAT(Field) if (Key == TEXT(#Field)) S.Field = Value
#define DVN_VIDEO_WRITE_INT(Field) if (Key == TEXT(#Field)) S.Field = FMath::RoundToInt(Value)
#define DVN_VIDEO_WRITE_BOOL(Field) if (Key == TEXT(#Field)) S.Field = Value > 0.5f
    DVN_VIDEO_WRITE_FLOAT(ResolutionScale); DVN_VIDEO_WRITE_FLOAT(FrameRateLimit);
    DVN_VIDEO_WRITE_FLOAT(Gamma);
    DVN_VIDEO_WRITE_BOOL(bVSync); DVN_VIDEO_WRITE_BOOL(bDynamicResolution); DVN_VIDEO_WRITE_BOOL(bHDR);
    DVN_VIDEO_WRITE_INT(HDRNits); DVN_VIDEO_WRITE_INT(ViewDistanceQuality); DVN_VIDEO_WRITE_INT(AntiAliasingMethod);
    DVN_VIDEO_WRITE_INT(AntiAliasingQuality); DVN_VIDEO_WRITE_INT(ShadowQuality); DVN_VIDEO_WRITE_INT(GlobalIlluminationQuality);
    DVN_VIDEO_WRITE_INT(ReflectionQuality); DVN_VIDEO_WRITE_INT(PostProcessQuality); DVN_VIDEO_WRITE_INT(TextureQuality);
    DVN_VIDEO_WRITE_INT(EffectsQuality); DVN_VIDEO_WRITE_INT(FoliageQuality); DVN_VIDEO_WRITE_INT(ShadingQuality);
    DVN_VIDEO_WRITE_INT(LandscapeQuality); DVN_VIDEO_WRITE_BOOL(bMotionBlur); DVN_VIDEO_WRITE_BOOL(bDepthOfField);
    DVN_VIDEO_WRITE_BOOL(bBloom); DVN_VIDEO_WRITE_BOOL(bLensFlare); DVN_VIDEO_WRITE_BOOL(bChromaticAberration);
    DVN_VIDEO_WRITE_BOOL(bAmbientOcclusion);
#undef DVN_VIDEO_WRITE_FLOAT
#undef DVN_VIDEO_WRITE_INT
#undef DVN_VIDEO_WRITE_BOOL
}
}

UDigimonVenomNXTVideoOptionPicker::UDigimonVenomNXTVideoOptionPicker(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InitFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 12));
    InitForegroundColor(FSlateColor(DigimonVideoUI::White));
    InitIsFocusable(true);
}

void UDigimonVenomNXTVideoOptionPicker::InitializeOption(FName InSettingKey)
{
    SettingKey = InSettingKey;
    OnSelectionChanged.AddUniqueDynamic(this, &UDigimonVenomNXTVideoOptionPicker::HandleOptionSelected);
    OnOpening.AddUniqueDynamic(this, &UDigimonVenomNXTVideoOptionPicker::HandleOptionOpened);
    SetEnableGamepadNavigationMode(true); SetMaxListHeight(300.0f); SetContentPadding(FMargin(12, 8));
    using namespace DigimonVideoUI;
    FComboBoxStyle Style = GetWidgetStyle();
    FButtonStyle ButtonStyle = Style.ComboButtonStyle.ButtonStyle;
    ButtonStyle.SetNormal(FSlateRoundedBoxBrush(Ink, 6.0f, Cyan.CopyWithNewOpacity(0.4f), 1.0f));
    ButtonStyle.SetHovered(FSlateRoundedBoxBrush(Panel, 6.0f, Cyan, 2.0f));
    ButtonStyle.SetPressed(FSlateRoundedBoxBrush(Panel, 6.0f, White, 2.0f));
    ButtonStyle.SetDisabled(FSlateRoundedBoxBrush(Ink, 6.0f));
    Style.ComboButtonStyle.SetButtonStyle(ButtonStyle);
    Style.ComboButtonStyle.SetMenuBorderBrush(FSlateRoundedBoxBrush(Ink, 6.0f, Cyan, 1.0f));
    SetWidgetStyle(Style);
    FTableRowStyle ItemStyleCopy = GetItemStyle();
    ItemStyleCopy.SetTextColor(FSlateColor(White)); ItemStyleCopy.SetSelectedTextColor(FSlateColor(White));
    ItemStyleCopy.SetEvenRowBackgroundBrush(FSlateRoundedBoxBrush(Ink, 0.0f));
    ItemStyleCopy.SetOddRowBackgroundBrush(FSlateRoundedBoxBrush(Ink, 0.0f));
    ItemStyleCopy.SetEvenRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(Panel, 0.0f));
    ItemStyleCopy.SetOddRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(Panel, 0.0f));
    ItemStyleCopy.SetActiveBrush(FSlateRoundedBoxBrush(FLinearColor(0.025f, 0.23f, 0.28f, 1.0f), 3.0f));
    ItemStyleCopy.SetActiveHoveredBrush(FSlateRoundedBoxBrush(FLinearColor(0.035f, 0.30f, 0.36f, 1.0f), 3.0f));
    ItemStyleCopy.SetInactiveBrush(ItemStyleCopy.ActiveBrush); ItemStyleCopy.SetInactiveHoveredBrush(ItemStyleCopy.ActiveHoveredBrush);
    SetItemStyle(ItemStyleCopy);
}

void UDigimonVenomNXTVideoOptionPicker::HandleOptionSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (SelectionType == ESelectInfo::Direct || !GetIsEnabled()) return;
    const int32 Index = FindOptionIndex(SelectedItem);
    if (Index == INDEX_NONE) return;
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UINavigate);
    OnOptionChanged.Broadcast(SettingKey, Index);
}

void UDigimonVenomNXTVideoOptionPicker::HandleOptionOpened()
{
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UIClick);
}

TSharedRef<SWidget> UDigimonVenomNXTVideoSettingsWidget::RebuildWidget()
{
    BuildLayout(); return Super::RebuildWidget();
}

void UDigimonVenomNXTVideoSettingsWidget::NativeConstruct()
{
    Super::NativeConstruct(); BuildLayout(); RefreshControls();
}

void UDigimonVenomNXTVideoSettingsWidget::NativeDestruct()
{
    CloseSettings(); Super::NativeDestruct();
}

UDigimonVenomNXTVideoSettingsSubsystem* UDigimonVenomNXTVideoSettingsWidget::Backend() const
{
    return GetGameInstance() ? GetGameInstance()->GetSubsystem<UDigimonVenomNXTVideoSettingsSubsystem>() : nullptr;
}

void UDigimonVenomNXTVideoSettingsWidget::OpenSettings()
{
    BuildLayout();
    const bool bWasOpen = bPageOpen; bPageOpen = true;
    if (!bWasOpen) { PerformanceSampleStarted = FPlatformTime::Seconds(); PerformanceSampleFrames = 0; }
    RefreshControls(); RefreshConfirmation();
    if (!bWasOpen && !bShowingConfirmation && CategoryButtons.IsValidIndex(ActiveCategory) && GetOwningPlayer())
        CategoryButtons[ActiveCategory]->SetUserFocus(GetOwningPlayer());
}

void UDigimonVenomNXTVideoSettingsWidget::CloseSettings()
{
    if (bPageOpen) HandleBack();
    bPageOpen = false;
}

bool UDigimonVenomNXTVideoSettingsWidget::HandleBack()
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend();
    if (!Video || !Video->IsAwaitingConfirmation()) return false;
    Video->RevertVideoMode(); Feedback = TEXT("Previous display settings restored.");
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UIBack);
    RefreshControls(); RefreshConfirmation(); return true;
}

UDigimonVenomNXTActionButton* UDigimonVenomNXTVideoSettingsWidget::Button(const FString& Label, const FString& Action, FLinearColor Accent, int32 Payload)
{
    UDigimonVenomNXTActionButton* Result = WidgetTree->ConstructWidget<UDigimonVenomNXTActionButton>();
    Result->InitializeAction(Action, Payload); DigimonVenomNXTUI::StyleButton(Result, Accent);
    Result->OnAction.AddDynamic(this, &UDigimonVenomNXTVideoSettingsWidget::HandleAction);
    UTextBlock* Caption = DigimonVideoUI::Text(WidgetTree, Label, 11, DigimonVideoUI::White, true);
    Caption->SetJustification(ETextJustify::Center); Result->SetContent(Caption); return Result;
}

void UDigimonVenomNXTVideoSettingsWidget::AddControl(UVerticalBox* Body, FName Key, const FString& Label, const FString& Help, const TArray<FString>& Labels, const TArray<float>& Values)
{
    using namespace DigimonVideoUI;
    FDigimonVideoControlView View; View.SettingKey = Key; View.Description = Help; View.Values = Values;
    UBorder* Entry = Card(WidgetTree); Add(Body, Entry, 3);
    UVerticalBox* Content = WidgetTree->ConstructWidget<UVerticalBox>(); Entry->SetContent(Content);
    UHorizontalBox* Main = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(Content, Main, 1);
    Row(Main, Text(WidgetTree, Label, 13, White, true), true, 0);
    View.Picker = WidgetTree->ConstructWidget<UDigimonVenomNXTVideoOptionPicker>(); View.Picker->InitializeOption(Key);
    View.Picker->SetToolTipText(FText::FromString(Label + TEXT("\n") + Help));
    for (const FString& Option : Labels) View.Picker->AddOption(Option);
    View.Picker->OnOptionChanged.AddDynamic(this, &UDigimonVenomNXTVideoSettingsWidget::HandleOptionChanged);
    Row(Main, View.Picker, true, 0);
    View.Help = Text(WidgetTree, Help, 10, Muted); Add(Content, View.Help, 3);
    Controls.Add(View);
}

void UDigimonVenomNXTVideoSettingsWidget::BuildLayout()
{
    if (Root) return;
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("VideoSettingsWidgetTree"));
    using namespace DigimonVideoUI;
    Root = WidgetTree->ConstructWidget<UOverlay>(); WidgetTree->RootWidget = Root;
    EditableContent = WidgetTree->ConstructWidget<UVerticalBox>();
    if (UOverlaySlot* ChildSlot = Root->AddChildToOverlay(EditableContent)) { ChildSlot->SetHorizontalAlignment(HAlign_Fill); ChildSlot->SetVerticalAlignment(VAlign_Fill); }

    UBorder* Hero = Card(WidgetTree); Hero->SetPadding(FMargin(0)); Hero->SetClipping(EWidgetClipping::ClipToBounds); Add(EditableContent, Hero, 0);
    USizeBox* HeroBounds = WidgetTree->ConstructWidget<USizeBox>(); HeroBounds->SetHeightOverride(91.0f); Hero->SetContent(HeroBounds);
    UOverlay* HeroLayers = WidgetTree->ConstructWidget<UOverlay>(); HeroBounds->AddChild(HeroLayers);
    DigimonVenomNXTUI::AddBackdrop(WidgetTree, HeroLayers, nullptr, FLinearColor(0.005f, 0.019f, 0.030f, 0.62f));
    UBorder* HeroCaption = WidgetTree->ConstructWidget<UBorder>(); HeroCaption->SetBrushColor(FLinearColor::Transparent); HeroCaption->SetPadding(FMargin(18, 10));
    HeroLayers->AddChildToOverlay(HeroCaption);
    UHorizontalBox* HeroColumns = WidgetTree->ConstructWidget<UHorizontalBox>(); HeroCaption->SetContent(HeroColumns);
    UVerticalBox* HeroText = WidgetTree->ConstructWidget<UVerticalBox>(); Row(HeroColumns, HeroText, true, 0);
    Add(HeroText, Text(WidgetTree, TEXT("VIDEO & GRAPHICS"), 23, White, true), 0);
    Add(HeroText, Text(WidgetTree, TEXT("YOUR WORLD. YOUR PERFORMANCE."), 10, Cyan, true), 1);
    Add(HeroText, Text(WidgetTree, TEXT("Keep partners clear, reduce effects and choose your own frame limit."), 11, Muted), 2);
    USizeBox* PerformanceBounds = WidgetTree->ConstructWidget<USizeBox>(); PerformanceBounds->SetWidthOverride(225);
    PerformanceReadout = Text(WidgetTree, TEXT("Measuring frame rate..."), 11, Green, true);
    PerformanceReadout->SetJustification(ETextJustify::Right);
    PerformanceReadout->SetToolTipText(FText::FromString(TEXT("Live average over half a second. FPS and frame time measure this menu's render cadence, not a benchmark. The driver, VSync and monitor may impose additional limits.")));
    PerformanceBounds->AddChild(PerformanceReadout); Row(HeroColumns, PerformanceBounds, false, 0);

    UHorizontalBox* Presets = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(EditableContent, Presets, 5);
    const TCHAR* PresetLabels[] = { TEXT("OPTIMIZED"), TEXT("LOW"), TEXT("BALANCED"), TEXT("HIGH"), TEXT("EPIC") };
    for (int32 Index = 0; Index < UE_ARRAY_COUNT(PresetLabels); ++Index)
    {
        UDigimonVenomNXTActionButton* Preset = Button(PresetLabels[Index], TEXT("video:preset"), Index == 0 ? Green : Cyan, Index);
        Preset->SetToolTipText(FText::FromString(Index == 0 ? TEXT("Recommended for Digimon: shadows off and fewer distracting effects. Does not change your display, frame limit or VSync.") : TEXT("Stage a graphics-quality preset. Display, frame limit and VSync stay as you chose them. Apply when ready.")));
        Row(Presets, Preset); PresetButtons.Add(Preset);
    }
    PresetDescription = Text(WidgetTree, TEXT("Recommended: Optimized keeps shadows off and partners easy to read. Presets are staged until Apply."), 10, Muted);
    Add(EditableContent, PresetDescription, 1);
    RuntimeNotice = Text(WidgetTree, TEXT(""), 11, Gold); Add(EditableContent, RuntimeNotice, 3); RuntimeNotice->SetVisibility(ESlateVisibility::Collapsed);
    UHorizontalBox* Tabs = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(EditableContent, Tabs, 4);
    const TCHAR* CategoryLabels[] = { TEXT("DISPLAY"), TEXT("QUALITY"), TEXT("EFFECTS") };
    for (int32 Index = 0; Index < UE_ARRAY_COUNT(CategoryLabels); ++Index)
    {
        UDigimonVenomNXTActionButton* Tab = Button(CategoryLabels[Index], TEXT("video:category"), Cyan, Index);
        Row(Tabs, Tab); CategoryButtons.Add(Tab);
    }
    Categories = WidgetTree->ConstructWidget<UWidgetSwitcher>(); Add(EditableContent, Categories, 1, true);
    TArray<UVerticalBox*> Bodies;
    for (int32 Index = 0; Index < UE_ARRAY_COUNT(CategoryLabels); ++Index)
    {
        UScrollBox* Scroll = WidgetTree->ConstructWidget<UScrollBox>();
        Scroll->SetAnimateWheelScrolling(true); Scroll->SetScrollWhenFocusChanges(EScrollWhenFocusChanges::AnimatedScroll);
        Scroll->SetNavigationDestination(EDescendantScrollDestination::IntoView);
        Categories->AddChild(Scroll);
        UVerticalBox* Body = WidgetTree->ConstructWidget<UVerticalBox>(); Scroll->AddChild(Body); Bodies.Add(Body);
    }
    const TArray<FString> ToggleLabels = { TEXT("Off"), TEXT("On") }; const TArray<float> ToggleValues = { 0, 1 };
    const TArray<FString> QualityLabels = { TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic"), TEXT("Cinematic") };
    const TArray<float> QualityValues = { 0, 1, 2, 3, 4 };
    UVerticalBox* Display = Bodies[0];
    Add(Display, Text(WidgetTree, TEXT("Changes to your screen mode or HDR need confirmation. If the picture disappears, the previous display returns automatically."), 11, Muted), 5);
    AddControl(Display, TEXT("DisplayMode"), TEXT("Window mode"), TEXT("Borderless uses your desktop resolution. Windowed lets you choose a smaller game window."), { TEXT("Fullscreen"), TEXT("Borderless"), TEXT("Windowed") }, { 0, 1, 2 });
    AddControl(Display, TEXT("Resolution"), TEXT("Output resolution"), TEXT("Sets the screen or window size. Lower resolutions can improve performance."), {}, {});
    AddControl(Display, TEXT("ResolutionScale"), TEXT("3D render scale"), TEXT("Lower the world's render resolution while menu text stays at full resolution. 100% gives the sharpest partners."), { TEXT("50%"), TEXT("58%"), TEXT("67%"), TEXT("75%"), TEXT("83%"), TEXT("90%"), TEXT("100%") }, { 50, 58, 67, 75, 83, 90, 100 });
    AddControl(Display, TEXT("FrameRateLimit"), TEXT("Frame rate limit"), TEXT("Unlimited removes the game's frame cap. VSync, your monitor and driver can still limit the visible frame rate."), { TEXT("Unlimited"), TEXT("30 FPS"), TEXT("45 FPS"), TEXT("60 FPS"), TEXT("75 FPS"), TEXT("90 FPS"), TEXT("120 FPS"), TEXT("144 FPS"), TEXT("165 FPS"), TEXT("180 FPS"), TEXT("240 FPS"), TEXT("360 FPS") }, { 0, 30, 45, 60, 75, 90, 120, 144, 165, 180, 240, 360 });
    UBorder* CustomFrameRateCard = Card(WidgetTree); Add(Display, CustomFrameRateCard, 3);
    UVerticalBox* CustomFrameRateBody = WidgetTree->ConstructWidget<UVerticalBox>(); CustomFrameRateCard->SetContent(CustomFrameRateBody);
    UHorizontalBox* CustomFrameRateRow = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(CustomFrameRateBody, CustomFrameRateRow, 1);
    Row(CustomFrameRateRow, Text(WidgetTree, TEXT("Custom frame rate"), 13, White, true), true, 0);
    CustomFrameRateInput = WidgetTree->ConstructWidget<UEditableTextBox>(); DigimonVenomNXTUI::StyleInput(CustomFrameRateInput);
    CustomFrameRateInput->SetHintText(FText::FromString(TEXT("0 or 15-1000")));
    CustomFrameRateInput->SetToolTipText(FText::FromString(TEXT("Enter a whole-number frame cap from 15 to 1000, or 0 for unlimited. Press Enter or Set Custom to stage it; Apply saves it.")));
    CustomFrameRateInput->OnTextCommitted.AddDynamic(this, &UDigimonVenomNXTVideoSettingsWidget::HandleCustomFrameRateCommitted);
    Row(CustomFrameRateRow, CustomFrameRateInput, true, 5);
    CustomFrameRateButton = Button(TEXT("SET CUSTOM"), TEXT("video:customfps"), Cyan); Row(CustomFrameRateRow, CustomFrameRateButton, false, 0);
    CustomFrameRateStatus = Text(WidgetTree, TEXT("Enter a whole number: 15-1000 FPS, or 0 for unlimited. This is staged until Apply."), 10, Muted); Add(CustomFrameRateBody, CustomFrameRateStatus, 3);
    AddControl(Display, TEXT("bVSync"), TEXT("VSync"), TEXT("On reduces screen tearing by synchronizing with your monitor. Off allows uncapped rendering and may reduce input latency."), ToggleLabels, ToggleValues);
    AddControl(Display, TEXT("Gamma"), TEXT("SDR brightness"), TEXT("Adjust the SDR image's midtone brightness. 2.2 is the standard setting; higher values brighten dark areas."), { TEXT("1.8  /  darker"), TEXT("1.9"), TEXT("2.0"), TEXT("2.1"), TEXT("2.2  /  standard"), TEXT("2.3"), TEXT("2.4"), TEXT("2.5"), TEXT("2.6  /  brighter") }, { 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f, 2.6f });
    AddControl(Display, TEXT("bDynamicResolution"), TEXT("Dynamic resolution"), TEXT("Automatically adjusts the 3D render resolution on supported devices. Menus stay sharp."), ToggleLabels, ToggleValues);
    AddControl(Display, TEXT("bHDR"), TEXT("HDR output"), TEXT("Use HDR on a supported display and rendering platform. The previous output returns if you do not confirm."), ToggleLabels, ToggleValues);
    AddControl(Display, TEXT("HDRNits"), TEXT("HDR peak brightness"), TEXT("Match the peak brightness your HDR display supports. This does not alter SDR brightness."), { TEXT("1,000 nits"), TEXT("2,000 nits") }, { 1000, 2000 });
    UVerticalBox* Quality = Bodies[1];
    Add(Quality, Text(WidgetTree, TEXT("Shadows are optional for Digimon's 2D presentation. Turn them off first when you want more performance. Cinematic is demanding."), 11, Muted), 5);
    AddControl(Quality, TEXT("ShadowQuality"), TEXT("Shadows"), TEXT("Off disables dynamic and contact shadows. This is the recommended choice for the sprite-based world."), { TEXT("Off  (recommended)"), TEXT("Medium"), TEXT("High"), TEXT("Epic"), TEXT("Cinematic") }, QualityValues);
    AddControl(Quality, TEXT("ViewDistanceQuality"), TEXT("View distance"), TEXT("Controls the distance at which eligible scenery is drawn. Lower values reduce distant scenery work."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("TextureQuality"), TEXT("Texture quality"), TEXT("Controls streaming 3D textures and video-memory use. Digimon's imported sprite and interface artwork stays sharp. Streaming changes may take a moment."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("AntiAliasingMethod"), TEXT("Anti-aliasing method"), TEXT("FXAA is inexpensive. Temporal methods smooth edges over time but may soften moving sprites. Only supported methods are offered."), {}, {});
    AddControl(Quality, TEXT("AntiAliasingQuality"), TEXT("Anti-aliasing quality"), TEXT("Controls edge-smoothing quality for the selected method. Not used when anti-aliasing is off."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("GlobalIlluminationQuality"), TEXT("Global illumination"), TEXT("Controls indirect lighting quality where the project's renderer supports it. Higher settings can be expensive."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("ReflectionQuality"), TEXT("Reflections"), TEXT("Controls reflection quality where the material and renderer use reflections."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("PostProcessQuality"), TEXT("Post-processing quality"), TEXT("Controls the quality of screen effects. Cel-shading depth tagging remains active at every preset."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("EffectsQuality"), TEXT("Effects quality"), TEXT("Controls the complexity of supported particle and material effects."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("FoliageQuality"), TEXT("Foliage quality"), TEXT("Controls density and detail for scenery that uses Unreal's foliage system."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("ShadingQuality"), TEXT("Material shading"), TEXT("Controls material shading quality. Higher levels can increase GPU cost."), QualityLabels, QualityValues);
    AddControl(Quality, TEXT("LandscapeQuality"), TEXT("Landscape quality"), TEXT("Controls detail for maps that use Unreal landscapes. Painted map artwork is unaffected."), QualityLabels, QualityValues);
    UVerticalBox* Effects = Bodies[2];
    Add(Effects, Text(WidgetTree, TEXT("Fine-tune readability. Optimized turns off motion blur, depth of field, lens flare and chromatic aberration to keep the action clear."), 11, Muted), 5);
    AddControl(Effects, TEXT("bMotionBlur"), TEXT("Motion blur"), TEXT("Blurs moving scenery. Off is recommended for clear sprites and camera movement."), ToggleLabels, ToggleValues);
    AddControl(Effects, TEXT("bDepthOfField"), TEXT("Depth of field"), TEXT("Allows the camera to blur areas outside its focus. Off keeps the whole play area readable."), ToggleLabels, ToggleValues);
    AddControl(Effects, TEXT("bBloom"), TEXT("Bloom"), TEXT("Allows a soft glow around bright materials and effects. Off gives a cleaner image."), ToggleLabels, ToggleValues);
    AddControl(Effects, TEXT("bLensFlare"), TEXT("Lens flare"), TEXT("Allows camera flare from bright light sources. Off reduces visual clutter."), ToggleLabels, ToggleValues);
    AddControl(Effects, TEXT("bChromaticAberration"), TEXT("Chromatic aberration"), TEXT("Allows colored fringes at the edge of the image. Off keeps edges clean."), ToggleLabels, ToggleValues);
    AddControl(Effects, TEXT("bAmbientOcclusion"), TEXT("Ambient occlusion"), TEXT("Adds contact shading where supported. Off can reduce GPU work in the 3D world."), ToggleLabels, ToggleValues);
    Add(Effects, Text(WidgetTree, TEXT("An effect only appears when the current camera or material uses it. These controls do not remove gameplay effects, partner animations or interface feedback."), 11, Muted), 7);

    UBorder* Footer = Card(WidgetTree, Green); Add(EditableContent, Footer, 4);
    UVerticalBox* FooterBody = WidgetTree->ConstructWidget<UVerticalBox>(); Footer->SetContent(FooterBody);
    Status = Text(WidgetTree, TEXT("Loading your local graphics settings..."), 11, Muted); Add(FooterBody, Status, 2);
    UHorizontalBox* Actions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(FooterBody, Actions, 3);
    ApplyButton = Button(TEXT("APPLY CHANGES"), TEXT("video:apply"), Green);
    RevertButton = Button(TEXT("REVERT EDITS"), TEXT("video:discard"), Cyan);
    ResetButton = Button(TEXT("RESET TO OPTIMIZED"), TEXT("video:reset"), Gold);
    ApplyButton->SetToolTipText(FText::FromString(TEXT("Apply and save these local graphics settings. Screen-mode and HDR changes need confirmation.")));
    RevertButton->SetToolTipText(FText::FromString(TEXT("Discard unapplied edits and restore the settings currently in use.")));
    ResetButton->SetToolTipText(FText::FromString(TEXT("Stage the recommended Optimized graphics preset. Your display mode, resolution, VSync and frame cap remain unchanged.")));
    Row(Actions, ApplyButton); Row(Actions, RevertButton); Row(Actions, ResetButton);

    ConfirmationOverlay = WidgetTree->ConstructWidget<UBorder>(); ConfirmationOverlay->SetBrushColor(FLinearColor(0.003f, 0.012f, 0.02f, 0.97f)); ConfirmationOverlay->SetPadding(FMargin(22));
    ConfirmationOverlay->SetHorizontalAlignment(HAlign_Center); ConfirmationOverlay->SetVerticalAlignment(VAlign_Center);
    if (UOverlaySlot* ChildSlot = Root->AddChildToOverlay(ConfirmationOverlay)) { ChildSlot->SetHorizontalAlignment(HAlign_Fill); ChildSlot->SetVerticalAlignment(VAlign_Fill); }
    USizeBox* ConfirmationBounds = WidgetTree->ConstructWidget<USizeBox>(); ConfirmationBounds->SetMaxDesiredWidth(560); ConfirmationOverlay->SetContent(ConfirmationBounds);
    UBorder* ConfirmationCard = Card(WidgetTree, Gold); ConfirmationCard->SetPadding(FMargin(24)); ConfirmationBounds->AddChild(ConfirmationCard);
    UVerticalBox* ConfirmationBody = WidgetTree->ConstructWidget<UVerticalBox>(); ConfirmationCard->SetContent(ConfirmationBody);
    Add(ConfirmationBody, Text(WidgetTree, TEXT("KEEP THESE DISPLAY SETTINGS?"), 20, White, true), 6);
    ConfirmationText = Text(WidgetTree, TEXT(""), 15, Gold, true); Add(ConfirmationBody, ConfirmationText, 9);
    Add(ConfirmationBody, Text(WidgetTree, TEXT("Check that the image is clear and fits your screen. If anything looks wrong, revert now. Closing this page also restores the previous display."), 12, Muted), 8);
    UHorizontalBox* ConfirmationActions = WidgetTree->ConstructWidget<UHorizontalBox>(); Add(ConfirmationBody, ConfirmationActions, 10);
    KeepDisplayButton = Button(TEXT("KEEP SETTINGS"), TEXT("video:keep"), Green);
    UndoDisplayButton = Button(TEXT("REVERT NOW"), TEXT("video:undo"), Gold);
    Row(ConfirmationActions, KeepDisplayButton); Row(ConfirmationActions, UndoDisplayButton);
    Add(ConfirmationBody, Text(WidgetTree, TEXT("Escape / controller Back: revert"), 10, Muted), 2);
    ConfirmationOverlay->SetVisibility(ESlateVisibility::Collapsed);
    SelectCategory(0);
}

void UDigimonVenomNXTVideoSettingsWidget::SelectCategory(int32 CategoryIndex)
{
    if (!Categories) return;
    ActiveCategory = FMath::Clamp(CategoryIndex, 0, 2); Categories->SetActiveWidgetIndex(ActiveCategory);
    for (int32 Index = 0; Index < CategoryButtons.Num(); ++Index) DigimonVenomNXTUI::StyleButton(CategoryButtons[Index], DigimonVideoUI::Cyan, Index == ActiveCategory);
}

void UDigimonVenomNXTVideoSettingsWidget::PopulateResolutions(const FDigimonVideoSettings& Settings)
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend(); if (!Video) return;
    const FDigimonVideoCapabilities Cap = Video->GetCapabilities();
    TArray<FIntPoint> Options = Settings.DisplayMode == EDigimonDisplayMode::Windowed ? Cap.WindowedResolutions : Cap.FullscreenResolutions;
    if (Settings.DisplayMode == EDigimonDisplayMode::Borderless) { Options.Reset(); Options.Add(Cap.DesktopResolution); }
    else if (Settings.DisplayMode == EDigimonDisplayMode::Windowed && Settings.Resolution.X > 0 && Settings.Resolution.Y > 0) Options.AddUnique(Settings.Resolution);
    Options.RemoveAll([](const FIntPoint& Value) { return Value.X <= 0 || Value.Y <= 0; });
    Options.Sort([](const FIntPoint& A, const FIntPoint& B) { return A.X == B.X ? A.Y < B.Y : A.X < B.X; });
    if (Options == DisplayResolutions) return;
    DisplayResolutions = MoveTemp(Options);
    for (FDigimonVideoControlView& View : Controls)
    {
        if (View.SettingKey != TEXT("Resolution")) continue;
        View.Picker->ClearOptions();
        for (const FIntPoint& Resolution : DisplayResolutions) View.Picker->AddOption(DigimonVideoUI::ResolutionLabel(Resolution));
    }
}

void UDigimonVenomNXTVideoSettingsWidget::RefreshControls()
{
    if (!Root) return;
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend();
    if (!Video) { DigimonVideoUI::Set(Status, TEXT("Graphics settings are not available until a local game session is ready.")); EditableContent->SetIsEnabled(false); return; }
    EditableContent->SetIsEnabled(!Video->IsAwaitingConfirmation());
    bBackendWasReady = Video->IsReady();
    TGuardValue<bool> Guard(bRefreshing, true);
    const FDigimonVideoSettings& Settings = Video->GetPendingSettings(); const FDigimonVideoCapabilities Cap = Video->GetCapabilities();
    PopulateResolutions(Settings);
    for (FDigimonVideoControlView& View : Controls)
    {
        const FName Key = View.SettingKey;
        FString DisabledReason;
        if (!Cap.bRuntimeAvailable) DisabledReason = Cap.RuntimeReason;
        else if ((Key == TEXT("DisplayMode") || Key == TEXT("Resolution")) && !Cap.bCanChangeDisplay) DisabledReason = Cap.DisplayReason;
        else if (Key == TEXT("Resolution") && Settings.DisplayMode == EDigimonDisplayMode::Borderless) DisabledReason = TEXT("Borderless follows your desktop. Choose Fullscreen or Windowed to select a resolution.");
        else if (Key == TEXT("ResolutionScale") && Settings.bDynamicResolution) DisabledReason = TEXT("Dynamic resolution controls this automatically. Turn it off to choose a fixed render scale.");
        else if (Key == TEXT("bDynamicResolution") && !Cap.bSupportsDynamicResolution) DisabledReason = Cap.DynamicResolutionReason;
        else if ((Key == TEXT("bHDR") || Key == TEXT("HDRNits")) && !Cap.bSupportsHDR) DisabledReason = Cap.HDRReason;
        else if (Key == TEXT("HDRNits") && !Settings.bHDR) DisabledReason = TEXT("Enable HDR output to set HDR peak brightness.");
        else if (Key == TEXT("Gamma") && Settings.bHDR) DisabledReason = TEXT("SDR brightness is not used in HDR. Set HDR peak brightness for your display instead.");
        else if (Key == TEXT("AntiAliasingQuality") && Settings.AntiAliasingMethod == 0) DisabledReason = TEXT("Choose an anti-aliasing method to use this quality setting.");
        bool bControlSupported = Cap.bRuntimeAvailable;
        if ((Key == TEXT("DisplayMode") || Key == TEXT("Resolution")) && !Cap.bCanChangeDisplay) bControlSupported = false;
        if (Key == TEXT("Resolution") && (Settings.DisplayMode == EDigimonDisplayMode::Borderless || DisplayResolutions.Num() == 0)) bControlSupported = false;
        if (Key == TEXT("ResolutionScale") && Settings.bDynamicResolution) bControlSupported = false;
        if (Key == TEXT("bDynamicResolution") && !Cap.bSupportsDynamicResolution) bControlSupported = false;
        if ((Key == TEXT("bHDR") || Key == TEXT("HDRNits")) && !Cap.bSupportsHDR) bControlSupported = false;
        if (Key == TEXT("HDRNits") && !Settings.bHDR) bControlSupported = false;
        if (Key == TEXT("Gamma") && Settings.bHDR) bControlSupported = false;
        if (Key == TEXT("AntiAliasingQuality") && Settings.AntiAliasingMethod == 0) bControlSupported = false;
        if (Key == TEXT("AntiAliasingMethod"))
        {
            TArray<float> SupportedValues;
            for (int32 Method : Cap.AntiAliasingMethods) SupportedValues.Add(static_cast<float>(Method));
            if (SupportedValues != View.Values)
            {
                View.Picker->ClearOptions(); View.Values = MoveTemp(SupportedValues);
                for (float Method : View.Values)
                {
                    const int32 MethodIndex = FMath::RoundToInt(Method);
                    const TCHAR* Name = MethodIndex == 0 ? TEXT("Off") : MethodIndex == 1 ? TEXT("FXAA") : MethodIndex == 2 ? TEXT("TAA") : MethodIndex == 3 ? TEXT("MSAA") : TEXT("TSR");
                    View.Picker->AddOption(Name);
                }
            }
        }
        int32 SelectedIndex = INDEX_NONE;
        if (Key == TEXT("Resolution")) SelectedIndex = DisplayResolutions.IndexOfByKey(Settings.DisplayMode == EDigimonDisplayMode::Borderless ? Cap.DesktopResolution : Settings.Resolution);
        else
        {
            const float Current = DigimonVideoUI::ReadValue(Settings, Key);
            SelectedIndex = View.Values.IndexOfByPredicate([Current](float Value) { return FMath::IsNearlyEqual(Current, Value, 0.01f); });
            // Preserve a valid custom cap/scale loaded from configuration instead of silently replacing it.
            if (SelectedIndex == INDEX_NONE && (Key == TEXT("ResolutionScale") || Key == TEXT("FrameRateLimit") || Key == TEXT("Gamma")))
            {
                SelectedIndex = View.Values.Add(Current);
                const FString CustomLabel = Key == TEXT("FrameRateLimit") ? FString::Printf(TEXT("%.0f FPS (custom)"), Current)
                    : Key == TEXT("Gamma") ? FString::Printf(TEXT("%.2f (custom)"), Current) : FString::Printf(TEXT("%.0f%% (custom)"), Current);
                View.Picker->AddOption(CustomLabel);
            }
        }
        if (SelectedIndex != INDEX_NONE) View.Picker->SetSelectedIndex(SelectedIndex);
        else View.Picker->ClearSelection();
        View.Picker->SetIsEnabled(bControlSupported && !Video->IsAwaitingConfirmation());
        DigimonVideoUI::Set(View.Help, DisabledReason.IsEmpty() ? View.Description : DisabledReason);
        View.Help->SetColorAndOpacity(DisabledReason.IsEmpty() ? DigimonVideoUI::Muted : DigimonVideoUI::Gold);
        View.Picker->SetToolTipText(FText::FromString(DisabledReason.IsEmpty() ? View.Description : DisabledReason));
    }
    RuntimeNotice->SetVisibility(Cap.bRuntimeAvailable ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
    DigimonVideoUI::Set(RuntimeNotice, Cap.RuntimeReason.IsEmpty() ? TEXT("Run a Standalone Game or a packaged build to apply graphics settings.") : Cap.RuntimeReason);
    for (int32 Index = 0; Index < PresetButtons.Num(); ++Index)
    {
        PresetButtons[Index]->SetIsEnabled(Cap.bRuntimeAvailable);
        DigimonVenomNXTUI::StyleButton(PresetButtons[Index], Index == 0 ? DigimonVideoUI::Green : DigimonVideoUI::Cyan, SelectedPreset == Index);
    }
    ResetButton->SetIsEnabled(Cap.bRuntimeAvailable); RefreshStatus();
    CustomFrameRateInput->SetIsEnabled(Cap.bRuntimeAvailable && !Video->IsAwaitingConfirmation());
    CustomFrameRateButton->SetIsEnabled(Cap.bRuntimeAvailable && !Video->IsAwaitingConfirmation());
}

void UDigimonVenomNXTVideoSettingsWidget::RefreshStatus()
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend(); if (!Video || !Status) return;
    const bool bDirty = Video->HasPendingChanges(); const bool bConfirming = Video->IsAwaitingConfirmation();
    const bool bRuntime = Video->GetCapabilities().bRuntimeAvailable;
    ApplyButton->SetIsEnabled(bRuntime && bDirty && !bConfirming); RevertButton->SetIsEnabled(bDirty && !bConfirming);
    Status->SetColorAndOpacity(!bRuntime ? DigimonVideoUI::Muted : bDirty ? DigimonVideoUI::Gold : DigimonVideoUI::Green);
    FString Message = bDirty ? TEXT("UNSAVED CHANGES  /  Apply when ready. Your edits stay here when you switch tabs.") : TEXT("SETTINGS SAVED  /  These graphics settings apply only to this device.");
    if (!Feedback.IsEmpty()) Message = Feedback + (bDirty ? TEXT("  Apply to save your changes.") : TEXT(""));
    else if (!Video->GetStatusMessage().IsEmpty() && !bDirty) Message = Video->GetStatusMessage();
    DigimonVideoUI::Set(Status, Message);
}

void UDigimonVenomNXTVideoSettingsWidget::RefreshConfirmation()
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend(); if (!Video || !ConfirmationOverlay) return;
    const bool bConfirming = Video->IsAwaitingConfirmation();
    if (bConfirming != bShowingConfirmation)
    {
        bShowingConfirmation = bConfirming; LastConfirmationSeconds = INDEX_NONE;
        ConfirmationOverlay->SetVisibility(bConfirming ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        EditableContent->SetIsEnabled(!bConfirming);
        if (bConfirming && GetOwningPlayer()) UndoDisplayButton->SetUserFocus(GetOwningPlayer());
        if (!bConfirming)
        {
            Feedback = Video->GetStatusMessage(); RefreshControls();
            if (bPageOpen && GetOwningPlayer() && CategoryButtons.IsValidIndex(ActiveCategory)) CategoryButtons[ActiveCategory]->SetUserFocus(GetOwningPlayer());
        }
    }
    if (bConfirming)
    {
        const int32 Seconds = Video->GetConfirmationSecondsRemaining();
        if (Seconds != LastConfirmationSeconds)
        {
            LastConfirmationSeconds = Seconds;
            DigimonVideoUI::Set(ConfirmationText, FString::Printf(TEXT("Reverting automatically in %d second%s"), Seconds, Seconds == 1 ? TEXT("") : TEXT("s")));
        }
    }
}

void UDigimonVenomNXTVideoSettingsWidget::HandleOptionChanged(FName SettingKey, int32 OptionIndex)
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend(); if (bRefreshing || !Video || Video->IsAwaitingConfirmation()) return;
    FDigimonVideoSettings Updated = Video->GetPendingSettings();
    if (SettingKey == TEXT("Resolution"))
    {
        if (!DisplayResolutions.IsValidIndex(OptionIndex)) return;
        Updated.Resolution = DisplayResolutions[OptionIndex];
    }
    else
    {
        const FDigimonVideoControlView* View = Controls.FindByPredicate([SettingKey](const FDigimonVideoControlView& Candidate) { return Candidate.SettingKey == SettingKey; });
        if (!View || !View->Values.IsValidIndex(OptionIndex)) return;
        DigimonVideoUI::WriteValue(Updated, SettingKey, View->Values[OptionIndex]);
        if (SettingKey == TEXT("DisplayMode"))
        {
            const FDigimonVideoCapabilities Cap = Video->GetCapabilities();
            if (Updated.DisplayMode == EDigimonDisplayMode::Borderless) Updated.Resolution = Cap.DesktopResolution;
            else if (Updated.DisplayMode == EDigimonDisplayMode::Fullscreen && !Cap.FullscreenResolutions.Contains(Updated.Resolution))
            {
                if (Cap.FullscreenResolutions.Contains(Cap.DesktopResolution)) Updated.Resolution = Cap.DesktopResolution;
                else if (Cap.FullscreenResolutions.Num() > 0) Updated.Resolution = Cap.FullscreenResolutions.Last();
            }
        }
    }
    Video->SetPendingSettings(Updated); SelectedPreset = INDEX_NONE; Feedback.Empty();
    DigimonVideoUI::Set(PresetDescription, TEXT("CUSTOM  /  Fine-tune any option below. Nothing changes until you choose Apply.")); RefreshControls();
}

void UDigimonVenomNXTVideoSettingsWidget::HandleAction(const FString& Action, int32 Payload)
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend(); if (!Video) return;
    if (Action == TEXT("video:keep"))
    {
        const bool bConfirmed = Video->ConfirmVideoMode(); Feedback = Video->GetStatusMessage();
        if (bConfirmed) UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Confirm);
    }
    else if (Action == TEXT("video:undo")) { HandleBack(); return; }
    else if (Video->IsAwaitingConfirmation()) return;
    else if (Action == TEXT("video:customfps")) { StageCustomFrameRate(); return; }
    else if (Action == TEXT("video:category")) { SelectCategory(Payload); return; }
    else if (Action == TEXT("video:preset") || Action == TEXT("video:reset"))
    {
        SelectedPreset = Action == TEXT("video:reset") ? 0 : FMath::Clamp(Payload, 0, 4);
        Video->SetPreset(static_cast<EDigimonVideoPreset>(SelectedPreset));
        Feedback = TEXT("Graphics preset staged. Display settings and frame pacing are unchanged.");
        DigimonVideoUI::Set(PresetDescription, SelectedPreset == 0 ? TEXT("OPTIMIZED  /  Shadows off, clear sprites and fewer screen effects. Recommended for Digimon.") : TEXT("PRESET STAGED  /  Review Quality and Effects, then Apply. Individual options can still be changed."));
    }
    else if (Action == TEXT("video:discard"))
    {
        Video->DiscardPending(); SelectedPreset = INDEX_NONE; Feedback = TEXT("Unapplied edits discarded. Your saved settings are in use.");
        DigimonVideoUI::Set(PresetDescription, TEXT("Recommended: Optimized keeps shadows off and partners easy to read. Presets are staged until Apply."));
    }
    else if (Action == TEXT("video:apply"))
    {
        FString Error;
        if (!Video->ApplyPending(Error))
        {
            Feedback = Error.IsEmpty() ? TEXT("Unable to apply these settings. Review the available display options and try again.") : Error;
            UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Error);
        }
        else
        {
            Feedback = Video->IsAwaitingConfirmation() ? TEXT("Check your display and confirm the new settings.") : Video->GetStatusMessage();
            if (Feedback.IsEmpty()) Feedback = TEXT("Graphics settings applied and saved on this device.");
            if (!Video->IsAwaitingConfirmation()) UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Confirm);
        }
    }
    else { OnAction.Broadcast(Action, Payload); return; }
    RefreshControls(); RefreshConfirmation();
}

void UDigimonVenomNXTVideoSettingsWidget::StageCustomFrameRate()
{
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend();
    if (!Video || !CustomFrameRateInput || Video->IsAwaitingConfirmation() || !Video->GetCapabilities().bRuntimeAvailable) return;
    const FString Input = CustomFrameRateInput->GetText().ToString().TrimStartAndEnd();
    bool bValid = !Input.IsEmpty() && Input.Len() <= 4;
    for (TCHAR Character : Input) if (Character < '0' || Character > '9') bValid = false;
    const int32 FrameCap = bValid ? FCString::Atoi(*Input) : -1;
    bValid = bValid && (FrameCap == 0 || (FrameCap >= 15 && FrameCap <= 1000));
    if (!bValid)
    {
        DigimonVideoUI::Set(CustomFrameRateStatus, TEXT("Use a whole number from 15 to 1000, or 0 for unlimited. Your current frame cap has not changed."));
        CustomFrameRateStatus->SetColorAndOpacity(DigimonVideoUI::Gold);
        UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::Error); return;
    }
    FDigimonVideoSettings Updated = Video->GetPendingSettings(); Updated.FrameRateLimit = static_cast<float>(FrameCap);
    Video->SetPendingSettings(Updated); Feedback.Empty();
    DigimonVideoUI::Set(CustomFrameRateStatus, FrameCap == 0 ? TEXT("Unlimited staged. Choose Apply to save it.") : FString::Printf(TEXT("%d FPS staged. Choose Apply to save it."), FrameCap));
    if (!Video->HasPendingChanges()) DigimonVideoUI::Set(CustomFrameRateStatus, TEXT("Your saved frame cap already uses this value."));
    CustomFrameRateStatus->SetColorAndOpacity(DigimonVideoUI::Green);
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UINavigate);
    // Refresh dropdowns only; the editable text is deliberately retained, including focus.
    RefreshControls();
}

void UDigimonVenomNXTVideoSettingsWidget::HandleCustomFrameRateCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    if (CommitType == ETextCommit::OnEnter) StageCustomFrameRate();
}

void UDigimonVenomNXTVideoSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    // Only the countdown label changes during a preview. The backend owns rollback,
    // so collapsing this widget, pausing or changing maps cannot suspend recovery.
    if (!bPageOpen) return;
    RefreshConfirmation();
    UDigimonVenomNXTVideoSettingsSubsystem* Video = Backend();
    if (Video && Video->IsReady() != bBackendWasReady) RefreshControls();
    const double Now = FPlatformTime::Seconds();
    if (PerformanceSampleStarted <= 0.0) PerformanceSampleStarted = Now;
    ++PerformanceSampleFrames;
    const double Elapsed = Now - PerformanceSampleStarted;
    if (Elapsed >= 0.5 && PerformanceReadout)
    {
        const double FPS = static_cast<double>(PerformanceSampleFrames) / Elapsed;
        const double FrameMS = Elapsed * 1000.0 / static_cast<double>(PerformanceSampleFrames);
        const float EffectiveCap = Video ? Video->GetEffectiveFrameRateLimit() : 0.0f;
        const float TargetCap = Video ? Video->GetAppliedSettings().FrameRateLimit : 0.0f;
        const FString Target = TargetCap <= 0.0f ? TEXT("Unlimited") : FString::Printf(TEXT("%.0f"), TargetCap);
        const FString Effective = EffectiveCap <= 0.0f ? TEXT("Unlimited") : FString::Printf(TEXT("%.0f"), EffectiveCap);
        DigimonVideoUI::Set(PerformanceReadout, FString::Printf(TEXT("%.0f FPS  /  %.1f ms\nTarget: %s  /  Engine: %s\nVSync %s"), FPS, FrameMS, *Target, *Effective, Video && Video->GetAppliedSettings().bVSync ? TEXT("on") : TEXT("off")));
        PerformanceSampleStarted = Now; PerformanceSampleFrames = 0;
    }
}

FReply UDigimonVenomNXTVideoSettingsWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    const FKey Key = InKeyEvent.GetKey();
    if ((Key == EKeys::Escape || Key == EKeys::Gamepad_FaceButton_Right) && HandleBack()) return FReply::Handled();
    if (!bShowingConfirmation && (Key == EKeys::PageUp || Key == EKeys::Gamepad_LeftShoulder))
    {
        SelectCategory((ActiveCategory + 2) % 3); return FReply::Handled();
    }
    if (!bShowingConfirmation && (Key == EKeys::PageDown || Key == EKeys::Gamepad_RightShoulder))
    {
        SelectCategory((ActiveCategory + 1) % 3); return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
