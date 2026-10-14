#pragma once

#include "CoreMinimal.h"

/** Atomic replacement for a closed temporary file created in the same directory as its destination. */
namespace DigimonVenomNXTAtomicFile
{
    /**
     * Replaces Path with TemporaryPath without a delete-then-move gap on Windows/POSIX.
     * Call only after the temporary write succeeded. On failure, retain the original and retry later.
     * Flushes the closed source before rename and the POSIX parent directory afterward.
     * A post-rename directory-flush failure is logged but still returns true: replacement
     * has already occurred and callers must not roll back a published transaction.
     * This is process/crash consistency on supported local filesystems, not a hardware-power-loss
     * durability guarantee or a guarantee about third-party network filesystems.
     */
    DIGIMONVENOMNXTRUNTIME_API bool ReplaceFromTemporary(const FString& Path, const FString& TemporaryPath);
}
