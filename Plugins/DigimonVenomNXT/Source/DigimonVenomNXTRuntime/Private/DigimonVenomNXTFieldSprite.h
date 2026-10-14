#pragma once

#include "CoreMinimal.h"

class UPaperFlipbookComponent;

/** Shared rendering rules for flat tamer/partner/rival sprites. */
namespace DigimonVenomNXTFieldSprite
{
    /** Asset-free properties only; safe for native constructors and class defaults. */
    void ConfigureDefaults(UPaperFlipbookComponent* Sprite);

    /** Resolve masked materials on registered game-thread instances, after construction. */
    void Configure(UPaperFlipbookComponent* Sprite);
    void UpdateDepth(UPaperFlipbookComponent* Sprite);
}
