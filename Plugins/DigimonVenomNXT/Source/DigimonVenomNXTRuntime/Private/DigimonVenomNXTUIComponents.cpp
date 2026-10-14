#include "DigimonVenomNXTUIComponents.h"
#include "DigimonVenomNXTAnimatedPortrait.h"
#include "DigimonVenomNXTAudioSubsystem.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

void UDigimonVenomNXTActionButton::InitializeAction(const FString& InAction, int32 InPayload)
{
    Action = InAction;
    Payload = InPayload;
    if (!bBound)
    {
        OnClicked.AddDynamic(this, &UDigimonVenomNXTActionButton::HandleClicked);
        OnHovered.AddDynamic(this, &UDigimonVenomNXTActionButton::HandleHovered);
        bBound = true;
    }
}

void UDigimonVenomNXTActionButton::HandleClicked()
{
    if (!GetIsEnabled()) return;
    const bool bBack = Action == TEXT("back") || Action == TEXT("close") || Action == TEXT("leave") || Action == TEXT("returnfield") || Action == TEXT("closemenu") || Action == TEXT("digilab:return");
    UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, bBack ? EDigimonAudioCue::UIBack : EDigimonAudioCue::UIClick);
    OnAction.Broadcast(Action, Payload);
}

void UDigimonVenomNXTActionButton::HandleHovered()
{
    if (GetIsEnabled()) UDigimonVenomNXTAudioSubsystem::PlayForWidget(this, EDigimonAudioCue::UIHover);
}

namespace DigimonVenomNXTUI
{
    FString VarietyLabel(EDigimonVariant Variety)
    {
        switch (Variety)
        {
        case EDigimonVariant::Normal: return TEXT("NORMAL");
        case EDigimonVariant::Paradox: return TEXT("PARADOX");
        case EDigimonVariant::Shiny: return TEXT("SHINY");
        case EDigimonVariant::Firewall: return TEXT("FIREWALL");
        default: return TEXT("UNKNOWN VARIETY");
        }
    }

    FLinearColor VarietyAccent(EDigimonVariant Variety)
    {
        switch (Variety)
        {
        case EDigimonVariant::Normal: return FLinearColor(0.28f, 0.82f, 1.0f, 1.0f);
        case EDigimonVariant::Paradox: return FLinearColor(0.76f, 0.57f, 1.0f, 1.0f);
        case EDigimonVariant::Shiny: return FLinearColor(1.0f, 0.74f, 0.25f, 1.0f);
        case EDigimonVariant::Firewall: return FLinearColor(1.0f, 0.43f, 0.20f, 1.0f);
        default: return FLinearColor(0.61f, 0.74f, 0.83f, 1.0f);
        }
    }

    void StyleButton(UButton* Button, FLinearColor Accent, bool bSelected)
    {
        if (!Button) return;
        const FLinearColor Ink(0.018f, 0.042f, 0.070f, 1.0f);
        FButtonStyle Style = Button->GetStyle();
        Style.SetNormal(FSlateRoundedBoxBrush(bSelected ? FLinearColor::LerpUsingHSV(Ink, Accent, 0.24f) : Ink, 6.0f, Accent.CopyWithNewOpacity(bSelected ? 1.0f : 0.45f), bSelected ? 2.0f : 1.0f));
        Style.SetHovered(FSlateRoundedBoxBrush(FLinearColor::LerpUsingHSV(Ink, Accent, 0.25f), 6.0f, Accent, 2.0f));
        Style.SetPressed(FSlateRoundedBoxBrush(FLinearColor::LerpUsingHSV(Ink, Accent, 0.38f), 6.0f, FLinearColor::White, 2.0f));
        Style.SetDisabled(FSlateRoundedBoxBrush(FLinearColor(0.025f,0.038f,0.053f,1.0f), 6.0f, FLinearColor(0.11f,0.15f,0.20f,1.0f), 1.0f));
        Style.SetNormalPadding(FMargin(14.0f, 10.0f));
        Style.SetPressedPadding(FMargin(14.0f, 11.0f, 14.0f, 9.0f));
        Button->SetStyle(Style);
        Button->SetBackgroundColor(FLinearColor::White);
    }

    void StylePanel(UBorder* Border, FLinearColor Fill)
    {
        if (!Border) return;
        Border->SetBrush(FSlateRoundedBoxBrush(Fill, 10.0f, FLinearColor(0.09f,0.22f,0.30f,0.80f), 1.0f));
        Border->SetBrushColor(FLinearColor::White);
        Border->SetPadding(FMargin(16.0f));
    }

    void StyleInput(UEditableTextBox* Input)
    {
        if (!Input) return;
        FEditableTextBoxStyle Style = Input->GetWidgetStyle();
        Style.SetBackgroundImageNormal(FSlateRoundedBoxBrush(FLinearColor(0.013f,0.032f,0.059f,1.0f), 6.0f, FLinearColor(0.14f,0.29f,0.38f,1.0f), 1.0f));
        Style.SetBackgroundImageHovered(FSlateRoundedBoxBrush(FLinearColor(0.021f,0.052f,0.085f,1.0f), 6.0f, FLinearColor(0.1f,0.67f,0.77f,1.0f), 1.0f));
        Style.SetBackgroundImageFocused(FSlateRoundedBoxBrush(FLinearColor(0.016f,0.043f,0.075f,1.0f), 6.0f, FLinearColor(0.08f,0.87f,0.94f,1.0f), 2.0f));
        Style.SetPadding(FMargin(14.0f, 11.0f));
        Style.SetForegroundColor(FSlateColor(FLinearColor(0.94f,0.98f,1.0f,1.0f)));
        Input->SetWidgetStyle(Style);
    }

    USizeBox* Texture(UWidgetTree* Tree, UTexture2D* Image, float Width, float Height)
    {
        USizeBox* Box = Tree->ConstructWidget<USizeBox>();
        Box->SetWidthOverride(Width);
        Box->SetHeightOverride(Height);
        Box->SetClipping(EWidgetClipping::ClipToBounds);
        UScaleBox* Scale = Tree->ConstructWidget<UScaleBox>();
        Scale->SetStretch(EStretch::ScaleToFit);
        Scale->SetStretchDirection(EStretchDirection::Both);
        Box->AddChild(Scale);
        if (Image)
        {
            UImage* Portrait = Tree->ConstructWidget<UImage>();
            Portrait->SetBrushFromTexture(Image, true);
            Portrait->SetVisibility(ESlateVisibility::HitTestInvisible);
            Scale->AddChild(Portrait);
        }
        else
        {
            UTextBlock* Placeholder = Tree->ConstructWidget<UTextBlock>();
            Placeholder->SetText(FText::FromString(TEXT("—")));
            Placeholder->SetColorAndOpacity(FSlateColor(FLinearColor(0.20f,0.40f,0.50f,1.0f)));
            Scale->AddChild(Placeholder);
        }
        return Box;
    }

    USizeBox* CurrencyIcon(UWidgetTree* Tree, bool bDigiRubies, float Width, float Height)
    {
        USizeBox* Box = Tree->ConstructWidget<USizeBox>();
        Box->SetWidthOverride(Width); Box->SetHeightOverride(Height);
        UBorder* Face = Tree->ConstructWidget<UBorder>();
        const FLinearColor Color = bDigiRubies ? FLinearColor(0.83f, 0.56f, 1.0f) : FLinearColor(1.0f, 0.76f, 0.30f);
        Face->SetBrush(FSlateRoundedBoxBrush(Color.CopyWithNewOpacity(0.12f), 5.0f, Color.CopyWithNewOpacity(0.55f), 1.0f));
        Face->SetPadding(FMargin(0)); Face->SetHorizontalAlignment(HAlign_Center); Face->SetVerticalAlignment(VAlign_Center);
        UTextBlock* Glyph = Tree->ConstructWidget<UTextBlock>();
        Glyph->SetText(FText::FromString(bDigiRubies ? TEXT("◆") : TEXT("¥")));
        Glyph->SetColorAndOpacity(Color);
        FSlateFontInfo Font = Glyph->GetFont(); Font.Size = FMath::Max(10, FMath::RoundToInt(Height * 0.57f)); Font.TypefaceFontName = TEXT("Bold"); Glyph->SetFont(Font);
        Glyph->SetJustification(ETextJustify::Center); Glyph->SetVisibility(ESlateVisibility::HitTestInvisible);
        Face->SetContent(Glyph); Box->AddChild(Face);
        Box->SetToolTipText(FText::FromString(bDigiRubies ? TEXT("DigiRubies") : TEXT("Credits")));
        return Box;
    }

    USizeBox* AnimatedPortrait(UWidgetTree* Tree, FName SpeciesId, EDigimonVariant Variant, float Width, float Height)
    {
        USizeBox* Box = Tree->ConstructWidget<USizeBox>();
        Box->SetWidthOverride(Width);
        Box->SetHeightOverride(Height);
        UDigimonVenomNXTAnimatedPortrait* Portrait = Tree->ConstructWidget<UDigimonVenomNXTAnimatedPortrait>();
        Portrait->SetDigimon(SpeciesId, Variant);
        Box->AddChild(Portrait);
        return Box;
    }

    void AddBackdrop(UWidgetTree* Tree, UOverlay* Overlay, const TCHAR* AssetPath, FLinearColor Shade)
    {
        if (!Tree || !Overlay) return;
        UTexture2D* Art = AssetPath && *AssetPath ? LoadObject<UTexture2D>(nullptr, AssetPath, nullptr, LOAD_NoWarn | LOAD_Quiet) : nullptr;
        if (Art)
        {
            UScaleBox* Crop = Tree->ConstructWidget<UScaleBox>();
            Crop->SetStretch(EStretch::ScaleToFill);
            Crop->SetClipping(EWidgetClipping::ClipToBoundsAlways);
            Crop->SetVisibility(ESlateVisibility::HitTestInvisible);
            UImage* Image = Tree->ConstructWidget<UImage>();
            Image->SetBrushFromTexture(Art, true);
            Crop->AddChild(Image);
            // Decorative art must not impose its native resolution on auto-sized hero cards.
            USizeBox* ArtBounds = Tree->ConstructWidget<USizeBox>();
            ArtBounds->SetWidthOverride(0.0f); ArtBounds->SetHeightOverride(0.0f);
            ArtBounds->AddChild(Crop);
            if (UOverlaySlot* Slot = Overlay->AddChildToOverlay(ArtBounds))
            {
                Slot->SetHorizontalAlignment(HAlign_Fill);
                Slot->SetVerticalAlignment(VAlign_Fill);
            }
        }
        UBorder* Veil = Tree->ConstructWidget<UBorder>();
        Veil->SetBrushColor(Art ? Shade : FLinearColor(0.005f,0.015f,0.034f,1.0f));
        Veil->SetVisibility(ESlateVisibility::HitTestInvisible);
        if (UOverlaySlot* Slot = Overlay->AddChildToOverlay(Veil))
        {
            Slot->SetHorizontalAlignment(HAlign_Fill);
            Slot->SetVerticalAlignment(VAlign_Fill);
        }
        if (!Art)
        {
            // Native-resolution, quiet circuit work follows the supplied game's
            // presentation.py palette. It cannot blur or cover player controls.
            UCanvasPanel* Circuits = Tree->ConstructWidget<UCanvasPanel>();
            Circuits->SetVisibility(ESlateVisibility::HitTestInvisible);
            if (UOverlaySlot* Slot = Overlay->AddChildToOverlay(Circuits))
            { Slot->SetHorizontalAlignment(HAlign_Fill); Slot->SetVerticalAlignment(VAlign_Fill); }
            const auto Trace = [Tree, Circuits](float X0, float Y0, float X1, float Y1, bool bVertical)
            {
                UBorder* Line = Tree->ConstructWidget<UBorder>();
                Line->SetBrushColor(FLinearColor(0.018f, 0.075f, 0.105f, 0.60f));
                if (UCanvasPanelSlot* Slot = Circuits->AddChildToCanvas(Line))
                {
                    Slot->SetAnchors(FAnchors(X0, Y0, X1, Y1));
                    Slot->SetOffsets(bVertical ? FMargin(0, 0, 1.0f, 0) : FMargin(0, 0, 0, 1.0f));
                }
            };
            for (int32 I = 0; I < 10; ++I)
            {
                const float X = (I + 0.3f) / 10.0f;
                const float Bend = 0.20f + (I % 4) * 0.11f;
                Trace(X, 0.0f, X, Bend, true);
                Trace(X, Bend, X + 0.035f, Bend, false);
                Trace(X + 0.035f, Bend, X + 0.035f, FMath::Min(0.94f, Bend + 0.25f), true);
            }
        }
    }

    FString ScanValue(int32 Whole, int32 Hundredths)
    {
        Whole = FMath::Max(0, Whole);
        Hundredths = FMath::Clamp(Hundredths, 0, 99);
        return Hundredths > 0 ? FString::Printf(TEXT("%d.%02d"), Whole, Hundredths) : FString::FromInt(Whole);
    }

    FString Countdown(int64 Seconds)
    {
        Seconds = FMath::Max<int64>(0, Seconds);
        const int64 Days = Seconds / 86400;
        const int64 Hours = (Seconds / 3600) % 24;
        const int64 Minutes = (Seconds / 60) % 60;
        const int64 Remainder = Seconds % 60;
        return Days > 0
            ? FString::Printf(TEXT("%lldd %02lldh %02lldm"), Days, Hours, Minutes)
            : FString::Printf(TEXT("%02lld:%02lld:%02lld"), Hours, Minutes, Remainder);
    }
}
