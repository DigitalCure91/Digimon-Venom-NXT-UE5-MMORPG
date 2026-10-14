#include "DigimonVenomNXTAtomicFile.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#else
#include <cstdio>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#endif

bool DigimonVenomNXTAtomicFile::ReplaceFromTemporary(const FString& Path, const FString& TemporaryPath)
{
    if (Path.IsEmpty() || TemporaryPath.IsEmpty() || Path == TemporaryPath) return false;
    // Respect the platform file's physical write directory, including UE sandbox redirection.
    FString Destination = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*Path);
    FString Source = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*TemporaryPath);
    FPaths::NormalizeFilename(Destination);
    FPaths::NormalizeFilename(Source);
    if (FPaths::GetPath(Destination) != FPaths::GetPath(Source)) return false;
#if PLATFORM_WINDOWS
    FPaths::MakePlatformFilename(Destination);
    FPaths::MakePlatformFilename(Source);
    HANDLE TemporaryHandle = ::CreateFileW(*Source, GENERIC_WRITE, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (TemporaryHandle == INVALID_HANDLE_VALUE) return false;
    const bool bFlushed = ::FlushFileBuffers(TemporaryHandle) != 0;
    ::CloseHandle(TemporaryHandle);
    if (!bFlushed) return false;
    return ::MoveFileExW(*Source, *Destination, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    const FTCHARToUTF8 SourceUtf8(*Source);
    const FTCHARToUTF8 DestinationUtf8(*Destination);
    const int TemporaryDescriptor = ::open(SourceUtf8.Get(), O_WRONLY);
    if (TemporaryDescriptor < 0) return false;
    int FlushResult;
    do { FlushResult = ::fsync(TemporaryDescriptor); } while (FlushResult < 0 && errno == EINTR);
    ::close(TemporaryDescriptor);
    if (FlushResult != 0) return false;
    const FTCHARToUTF8 DirectoryUtf8(*FPaths::GetPath(Destination));
    const int DirectoryDescriptor = ::open(DirectoryUtf8.Get(), O_RDONLY | O_DIRECTORY);
    if (DirectoryDescriptor < 0) return false;
    const bool bReplaced = std::rename(SourceUtf8.Get(), DestinationUtf8.Get()) == 0;
    if (bReplaced)
    {
        do { FlushResult = ::fsync(DirectoryDescriptor); } while (FlushResult < 0 && errno == EINTR);
        // The rename already committed. Never report "not applied" and let callers
        // roll back memory while the authoritative intent is present on disk.
        if (FlushResult != 0)
            UE_LOG(LogTemp, Error, TEXT("Digimon save replaced, but directory durability could not be confirmed: %s"), *Destination);
    }
    ::close(DirectoryDescriptor);
    return bReplaced;
#endif
}
