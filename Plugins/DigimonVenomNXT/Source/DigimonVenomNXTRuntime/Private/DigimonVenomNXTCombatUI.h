#pragma once

#include "CoreMinimal.h"
#include "DigimonVenomNXTTypes.h"
#include "DigimonVenomNXTCombatCore.h"
#include "Blueprint/WidgetTree.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"

/** Presentation names only. Matchup values always come from the shared battle rules. */
namespace DigimonVenomNXTCombatUI
{
inline FString Affinity(EDigimonAffinity Value)
{
    switch (Value)
    {
    case EDigimonAffinity::Vaccine: return TEXT("Vaccine");
    case EDigimonAffinity::Virus: return TEXT("Virus");
    case EDigimonAffinity::Data: return TEXT("Data");
    default: return TEXT("Free");
    }
}
inline FString Element(EDigimonElement Value)
{
    switch (Value)
    {
    case EDigimonElement::Fire: return TEXT("Fire");
    case EDigimonElement::Water: return TEXT("Water");
    case EDigimonElement::Plant: return TEXT("Plant");
    case EDigimonElement::Electric: return TEXT("Electric");
    case EDigimonElement::Wind: return TEXT("Wind");
    case EDigimonElement::Earth: return TEXT("Earth");
    case EDigimonElement::Light: return TEXT("Light");
    case EDigimonElement::Dark: return TEXT("Dark");
    default: return TEXT("Neutral");
    }
}
inline FLinearColor AffinityColor(EDigimonAffinity Value)
{
    return Value == EDigimonAffinity::Vaccine ? FLinearColor(FColor(90,220,242)) :
        Value == EDigimonAffinity::Virus ? FLinearColor(FColor(255,141,119)) :
        Value == EDigimonAffinity::Data ? FLinearColor(FColor(190,157,255)) : FLinearColor(FColor(190,207,220));
}
inline FLinearColor ElementColor(EDigimonElement Value)
{
    switch (Value)
    {
    case EDigimonElement::Fire: return FLinearColor(FColor(255,163,113));
    case EDigimonElement::Water: return FLinearColor(FColor(119,193,255));
    case EDigimonElement::Plant: return FLinearColor(FColor(160,228,132));
    case EDigimonElement::Electric: return FLinearColor(FColor(255,219,110));
    case EDigimonElement::Wind: return FLinearColor(FColor(144,237,205));
    case EDigimonElement::Earth: return FLinearColor(FColor(223,184,137));
    case EDigimonElement::Light: return FLinearColor(FColor(255,241,182));
    case EDigimonElement::Dark: return FLinearColor(FColor(201,172,241));
    default: return FLinearColor(FColor(190,207,220));
    }
}
inline FString Class(EDigimonDamageClass Value)
{
    return Value == EDigimonDamageClass::Special ? TEXT("Special") : TEXT("Physical");
}
inline FString StatHelp()
{
    return TEXT("HP: health. SP: energy spent on skills. ATK attacks DEF for physical moves. INT is both special attack and special defense. SPD sets how often a partner acts. Basic Attack costs 0 SP.");
}
inline FString MatchupHelp()
{
    return TEXT("TYPE: Vaccine > Virus > Data > Vaccine. Advantage ×2; reverse ×0.5; same type or Free ×1.\nELEMENT: Fire > Plant > Water > Fire; Electric > Wind > Earth > Electric; Light and Dark hit each other for ×1.5. All other element matchups ×1.\nType and element multiply (up to ×3). A move uses its own element, not necessarily its user's. Stats and levels still determine damage.");
}
inline FString MatchupLabel(float Multiplier)
{
    return FString::Printf(TEXT("%s ×%s"), Multiplier > 1.001f ? TEXT("Super effective") : Multiplier < 0.999f ? TEXT("Not very effective") : TEXT("Normal"), *FString::SanitizeFloat(Multiplier, 0));
}
inline float Effectiveness(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, EDigimonElement MoveElement)
{
    return DigimonVenomNXTCombatCore::Effectiveness(static_cast<int32>(Attacker.Affinity), static_cast<int32>(Defender.Affinity), static_cast<int32>(MoveElement), static_cast<int32>(Defender.Element));
}
inline FString MatchupDetail(const FDigimonBattleUnit& Attacker, const FDigimonBattleUnit& Defender, EDigimonElement MoveElement)
{
    const float Type = DigimonVenomNXTCombatCore::TypeMultiplier(static_cast<int32>(Attacker.Affinity), static_cast<int32>(Defender.Affinity));
    const float Attribute = DigimonVenomNXTCombatCore::ElementMultiplier(static_cast<int32>(MoveElement), static_cast<int32>(Defender.Element));
    return FString::Printf(TEXT("Target: %s\n%s\n%s → %s type ×%s; %s → %s element ×%s."), *Defender.DisplayName,
        *MatchupLabel(Effectiveness(Attacker, Defender, MoveElement)), *Affinity(Attacker.Affinity), *Affinity(Defender.Affinity), *FString::SanitizeFloat(Type, 0),
        *Element(MoveElement), *Element(Defender.Element), *FString::SanitizeFloat(Attribute, 0));
}
inline FString MoveName(const FDigimonMoveSlot& Move)
{
    return Move.DisplayName.IsEmpty() ? Move.MoveId.ToString() : Move.DisplayName.ToString();
}
inline FString UnitDetails(const FDigimonBattleUnit& Unit)
{
    return FString::Printf(TEXT("%s  /  %s type  /  %s element\nHP %d/%d   SP %d/%d\nATK %d   DEF %d   INT %d   SPD %d\n%s"), *Unit.DisplayName,
        *Affinity(Unit.Affinity), *Element(Unit.Element), Unit.HP, Unit.Stats.MaxHP, Unit.SP, Unit.Stats.MaxSP,
        Unit.Stats.Attack, Unit.Stats.Defense, Unit.Stats.Spirit, Unit.Stats.Speed, *StatHelp());
}
inline UHorizontalBox* TypeChips(UWidgetTree* Tree, UTextBlock*& TypeText, UTextBlock*& ElementText, int32 FontSize = 10)
{
    UHorizontalBox* Row = Tree->ConstructWidget<UHorizontalBox>();
    for (UTextBlock** Label : {&TypeText, &ElementText})
    {
        UBorder* Chip = Tree->ConstructWidget<UBorder>();
        Chip->SetBrush(FSlateRoundedBoxBrush(FLinearColor(FColor(18,41,59)), 4.0f));
        Chip->SetPadding(FMargin(6, 2));
        *Label = Tree->ConstructWidget<UTextBlock>();
        FSlateFontInfo Font = (*Label)->GetFont(); Font.Size = FontSize; Font.TypefaceFontName = TEXT("Bold"); (*Label)->SetFont(Font);
        (*Label)->SetJustification(ETextJustify::Center);
        Chip->SetContent(*Label);
        if (UHorizontalBoxSlot* Slot = Row->AddChildToHorizontalBox(Chip))
        { Slot->SetPadding(FMargin(2, 0)); Slot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); }
    }
    Row->SetToolTipText(FText::FromString(MatchupHelp()));
    return Row;
}
inline void UpdateChips(UTextBlock* TypeText, UTextBlock* ElementText, EDigimonAffinity Type, EDigimonElement Attribute)
{
    if (TypeText) { TypeText->SetText(FText::FromString(Affinity(Type))); TypeText->SetColorAndOpacity(AffinityColor(Type)); }
    if (ElementText) { ElementText->SetText(FText::FromString(Element(Attribute))); ElementText->SetColorAndOpacity(ElementColor(Attribute)); }
}
}
