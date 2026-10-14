#include "DigimonVenomNXTEditorLibrary.h"

#include "AssetImportTask.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/AssetData.h"
#include "Settings/ProjectPackagingSettings.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/Base64.h"
#include "Misc/SecureHash.h"
#include "Misc/ScopedSlowTask.h"
#include "Misc/PackageName.h"
#include "HAL/FileManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/GarbageCollection.h"
#include "UObject/UObjectIterator.h"
#include "Engine/Texture2D.h"
#include "ImageCore.h"
#include "ImageUtils.h"
#include "TextureCompiler.h"
#include "Materials/MaterialInstanceConstant.h"
#include "SpriteEditorOnlyTypes.h"
#include "UObject/UnrealType.h"
#include "UObject/EnumProperty.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundWave.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "PaperSpriteFactory.h"
#include "PaperFlipbookFactory.h"
#include "DigimonVenomNXTAnimationAssets.h"
#include "DigimonVenomNXTTamers.h"
#include "DigimonVenomNXTWorld.h"
#include "DigimonVenomNXTMapAssetRevision.h"
#include "DigimonVenomNXTSpriteCoordinates.h"
#include "DigimonVenomNXTCollisionCore.h"
#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTMainMenuGameMode.h"
#include "DigimonVenomNXTGameInstance.h"
#include "GameMapsSettings.h"
#include "DigimonVenomNXTSettings.h"
#include "DigimonVenomNXTCustomDepth.h"
#include "DigimonVenomNXTEditorCustomDepth.h"
#include "Materials/Material.h"
#include "Misc/ConfigCacheIni.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/Level.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/PlayerStart.h"
#include "EditorFramework/AssetImportData.h"

#include "Misc/DateTime.h"
#include "Misc/App.h"
#include "Misc/EngineVersion.h"

namespace DigimonVenomNXTEditorInternal
{
    static bool ValidateWorldSetup(bool bRequireImportedContent, FString& Report);
    static FString ResourceFile(const TCHAR* Name)
    {
        const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DigimonVenomNXT"));
        return Plugin.IsValid() ? FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources"), Name) : FString();
    }
    static FString ObjectPath(const FString& Package) { return Package + TEXT(".") + FPackageName::GetLongPackageAssetName(Package); }
    static FString ReceiptPath() { return FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("DigimonVenomNXT/ContentImportReceipt.json")); }
    static bool FileSha1(const FString& File, FString& Hash)
    {
        TArray<uint8> Bytes;
        if (!FFileHelper::LoadFileToArray(Bytes, *File)) return false;
        uint8 Digest[FSHA1::DigestSize];
        FSHA1::HashBuffer(Bytes.GetData(), Bytes.Num(), Digest);
        Hash = BytesToHex(Digest, FSHA1::DigestSize).ToLower();
        return true;
    }
    static FString String(const TSharedPtr<FJsonObject>& Row, const TCHAR* Key)
    {
        FString Value;
        if (Row) Row->TryGetStringField(Key, Value);
        return Value;
    }
    static bool Boolean(const TSharedPtr<FJsonObject>& Row, const TCHAR* Key, bool Default = false)
    {
        bool Value = Default;
        if (Row) Row->TryGetBoolField(Key, Value);
        return Value;
    }
    static double Number(const TSharedPtr<FJsonObject>& Row, const TCHAR* Key, double Default = 0.)
    {
        double Value = Default;
        if (Row) Row->TryGetNumberField(Key, Value);
        return Value;
    }
    static bool SaveAsset(UObject* Asset);

    static UMaterialInterface* FieldSpriteMaterial()
    {
        static TWeakObjectPtr<UMaterialInstanceConstant> Cached;
        if (Cached.IsValid()) return Cached.Get();
        // Use Paper2D's SpriteTexture sampler, never the similarly named Niagara material.
        UMaterialInterface* Parent = LoadObject<UMaterialInterface>(nullptr,
            TEXT("/Paper2D/MaskedUnlitSpriteMaterial.MaskedUnlitSpriteMaterial"));
        if (!Parent)
        {
            UE_LOG(LogTemp, Error, TEXT("Digimon Venom NXT: Paper2D masked sprite material is missing. Enable Paper2D before importing."));
            return nullptr;
        }
        const FString PackageName = TEXT("/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite");
        UObject* ExistingMaterial = LoadObject<UObject>(nullptr, *(PackageName + TEXT(".MI_DVNXT_FieldSprite")), nullptr, LOAD_NoWarn | LOAD_Quiet);
        UMaterialInstanceConstant* Material = Cast<UMaterialInstanceConstant>(ExistingMaterial);
        if (ExistingMaterial && !Material) return nullptr;
        if (!Material)
        {
            UPackage* Package = CreatePackage(*PackageName);
            Material = NewObject<UMaterialInstanceConstant>(Package, TEXT("MI_DVNXT_FieldSprite"), RF_Public | RF_Standalone | RF_Transactional);
            FAssetRegistryModule::AssetCreated(Material);
        }
        Material->Modify();
        Material->SetParentEditorOnly(Parent, false);
        Material->BasePropertyOverrides.bOverride_BlendMode = true;
        Material->BasePropertyOverrides.BlendMode = BLEND_Masked;
        Material->BasePropertyOverrides.bOverride_OpacityMaskClipValue = true;
        // Keep the soft artwork's silhouette, but discard empty/near-empty pixels before depth writes.
        Material->BasePropertyOverrides.OpacityMaskClipValue = 0.1f;
        Material->BasePropertyOverrides.bOverride_TwoSided = true;
        Material->BasePropertyOverrides.TwoSided = true;
        Material->PostEditChange();
        if (!SaveAsset(Material)) return nullptr;
        Cached = Material;
        return Material;
    }

    static void ConfigureTexture(UTexture2D* Texture, bool bUI, bool bNearest = true)
    {
        Texture->Modify();
        Texture->PreEditChange(nullptr);
        Texture->CompressionSettings = TC_EditorIcon;
        Texture->CompressionNoAlpha = false;
        Texture->SRGB = true;
        Texture->Filter = bNearest ? TF_Nearest : TF_Bilinear;
        Texture->AddressX = TA_Clamp;
        Texture->AddressY = TA_Clamp;
        Texture->MipGenSettings = TMGS_NoMipmaps;
        Texture->LODGroup = bUI ? TEXTUREGROUP_UI : TEXTUREGROUP_Pixels2D;
        Texture->LODBias = 0;
        Texture->MaxTextureSize = 0;
        Texture->PowerOfTwoMode = ETexturePowerOfTwoSetting::None;
        Texture->Downscale = FPerPlatformFloat(1.0f);
        Texture->VirtualTextureStreaming = false;
        Texture->NeverStream = bUI;
        Texture->PostEditChange();
    }

    static UPaperSprite* CreateSprite(IAssetTools& AssetTools, UTexture2D* Texture, const FString& PackagePath, const FString& AssetName, FIntPoint UV, FIntPoint Dimension, bool bReplace, bool bCenteredUnitScale = false, const FVector2D* FrameOrigin = nullptr, bool bGround = false, float PixelsPerUnit = 1.0f)
    {
        if (!Texture) return nullptr;
        UMaterialInterface* Material = bGround
            ? LoadObject<UMaterialInterface>(nullptr, TEXT("/Paper2D/OpaqueUnlitSpriteMaterial.OpaqueUnlitSpriteMaterial"))
            : FieldSpriteMaterial();
        // A missing alpha material must never silently become an opaque sprite.
        if (!Material) return nullptr;
        const FString ObjectPath = PackagePath / AssetName + TEXT(".") + AssetName;
        UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, *ObjectPath);
        if (!Sprite)
        {
            UPaperSpriteFactory* Factory = NewObject<UPaperSpriteFactory>();
            Factory->InitialTexture = Texture;
            Factory->bUseSourceRegion = true;
            Factory->InitialSourceUV = UV;
            Factory->InitialSourceDimension = Dimension;
            Sprite = Cast<UPaperSprite>(AssetTools.CreateAsset(AssetName, PackagePath, UPaperSprite::StaticClass(), Factory, FName(TEXT("DigimonVenomNXT")), false));
        }
        if (Sprite)
        {
            // Repair in place, retaining the object identity used by maps and flipbooks.
            Sprite->Modify();
            FSpriteAssetInitParameters Init;
            Init.Texture = Texture;
            Init.Offset = UV;
            Init.Dimension = Dimension;
            // Farm coordinates are native source pixels around the island centre.
            // Do not inherit a project's custom importer scale or a previously edited pivot.
            const bool bRegisteredCanvas = true;
            Init.SetPixelsPerUnrealUnit(FMath::Max(.01f, PixelsPerUnit));
            Init.DefaultMaterialOverride = Material;
            Init.AlternateMaterialOverride = Material;
            if (bRegisteredCanvas)
            {
                Sprite->SetRotated(false, false);
                Sprite->SetTrim(false, FVector2D::ZeroVector, FVector2D(Dimension.X, Dimension.Y), false);
                if (FBoolProperty* Snap = FindFProperty<FBoolProperty>(UPaperSprite::StaticClass(), TEXT("bSnapPivotToPixelGrid")))
                    Snap->SetPropertyValue_InContainer(Sprite, false);
            }
            if (bGround || bCenteredUnitScale) Sprite->SetPivotMode(ESpritePivotMode::Center_Center, FVector2D::ZeroVector, false);
            Sprite->InitializeSprite(Init, true);
            {
                // Maps are registered whole images. An earlier manual polygon,
                // sprite atlas, or physics hull must not survive a map upgrade.
                // Movement uses the separately verified native collision mask.
                FStructProperty* RenderProperty = FindFProperty<FStructProperty>(UPaperSprite::StaticClass(), TEXT("RenderGeometry"));
                FProperty* CollisionProperty = FindFProperty<FProperty>(UPaperSprite::StaticClass(), TEXT("SpriteCollisionDomain"));
                FObjectPropertyBase* AtlasProperty = FindFProperty<FObjectPropertyBase>(UPaperSprite::StaticClass(), TEXT("AtlasGroup"));
                if (!RenderProperty || !CollisionProperty) return nullptr;
                FSpriteGeometryCollection* Geometry = RenderProperty->ContainerPtrToValuePtr<FSpriteGeometryCollection>(Sprite);
                Geometry->Reset();
                Geometry->GeometryType = ESpritePolygonMode::SourceBoundingBox;
                // Support both TEnumAsByte and scoped-enum reflection without
                // depending on Paper2D's private property's representation.
                if (FByteProperty* ByteProperty = CastField<FByteProperty>(CollisionProperty))
                    ByteProperty->SetPropertyValue_InContainer(Sprite, static_cast<uint8>(ESpriteCollisionMode::None));
                else if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(CollisionProperty))
                    EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(
                        EnumProperty->ContainerPtrToValuePtr<void>(Sprite), static_cast<uint64>(ESpriteCollisionMode::None));
                else return nullptr;
                if (AtlasProperty) AtlasProperty->SetObjectPropertyValue_InContainer(Sprite, nullptr);
                else if (Sprite->GetAtlasGroup() != nullptr) return nullptr;
            }
            if (bGround || bCenteredUnitScale)
                Sprite->SetPivotMode(ESpritePivotMode::Custom, FVector2D(UV.X + Dimension.X * 0.5, UV.Y + Dimension.Y * 0.5), true);
            if (FrameOrigin)
            {
                // The supplied registration is relative to this frame; Paper2D's
                // setter accepts texture coordinates, including the atlas offset.
                if (FBoolProperty* Snap = FindFProperty<FBoolProperty>(UPaperSprite::StaticClass(), TEXT("bSnapPivotToPixelGrid")))
                    Snap->SetPropertyValue_InContainer(Sprite, false);
                Sprite->SetPivotMode(ESpritePivotMode::Custom, FVector2D(UV.X, UV.Y) + *FrameOrigin, true);
            }
            Sprite->PostEditChange();
            Sprite->MarkPackageDirty();
        }
        (void)bReplace; // Existing generated assets always receive rendering repairs.
        return Sprite;
    }

    static UPaperFlipbook* CreateFlipbook(IAssetTools& AssetTools, const FString& PackagePath, const FString& AssetName, const TArray<UPaperSprite*>& Sprites, float FPS, bool bReplace, const TArray<double>* FrameDurationsSeconds = nullptr)
    {
        if (Sprites.Num() == 0) return nullptr;
        TArray<FPaperFlipbookKeyFrame> Frames;
        for (int32 FrameIndex = 0; FrameIndex < Sprites.Num(); ++FrameIndex)
        {
            UPaperSprite* Sprite = Sprites[FrameIndex];
            if (!Sprite) continue;
            FPaperFlipbookKeyFrame Frame;
            Frame.Sprite = Sprite;
            Frame.FrameRun = FrameDurationsSeconds && FrameDurationsSeconds->IsValidIndex(FrameIndex)
                ? FMath::Max(1, FMath::RoundToInt((*FrameDurationsSeconds)[FrameIndex] * FPS)) : 1;
            Frames.Add(Frame);
        }
        if (Frames.IsEmpty()) return nullptr;
        const FString ObjectPath = PackagePath / AssetName + TEXT(".") + AssetName;
        UPaperFlipbook* Flipbook = LoadObject<UPaperFlipbook>(nullptr, *ObjectPath);
        if (!Flipbook)
        {
            UPaperFlipbookFactory* Factory = NewObject<UPaperFlipbookFactory>();
            Factory->KeyFrames = Frames;
            Flipbook = Cast<UPaperFlipbook>(AssetTools.CreateAsset(AssetName, PackagePath, UPaperFlipbook::StaticClass(), Factory, FName(TEXT("DigimonVenomNXT")), false));
        }
        if (Flipbook)
        {
            Flipbook->Modify();
            {
                FScopedFlipbookMutator Mutator(Flipbook);
                Mutator.KeyFrames = Frames;
                Mutator.FramesPerSecond = FMath::Max(1.0f, FPS);
            }
            // Paper2D exposes no public setter for this editable asset property.
            UMaterialInterface* Material = FieldSpriteMaterial();
            if (!Material) return nullptr;
            FObjectPropertyBase* Property = FindFProperty<FObjectPropertyBase>(UPaperFlipbook::StaticClass(), TEXT("DefaultMaterial"));
            if (!Property) return nullptr;
            Property->SetObjectPropertyValue_InContainer(Flipbook, Material);
            Flipbook->PostEditChange();
            Flipbook->MarkPackageDirty();
        }
        (void)bReplace;
        return Flipbook;
    }

    template<typename T>
    static T* CreateDataAsset(const FString& LongPackagePath, const FString& AssetName, bool bReplace)
    {
        const FString FullObjectPath = LongPackagePath / AssetName + TEXT(".") + AssetName;
        if (UObject* Object = LoadObject<UObject>(nullptr, *FullObjectPath, nullptr, LOAD_NoWarn | LOAD_Quiet))
        {
            T* Existing = Cast<T>(Object);
            if (!Existing) return nullptr;
            if (bReplace) Existing->Modify();
            return Existing;
        }
        UPackage* Package = CreatePackage(*(LongPackagePath / AssetName));
        T* Asset = NewObject<T>(Package, *AssetName, RF_Public | RF_Standalone | RF_Transactional);
        FAssetRegistryModule::AssetCreated(Asset);
        Package->MarkPackageDirty();
        return Asset;
    }

    static bool SaveAsset(UObject* Asset)
    {
        if (!Asset) return false;
        Asset->MarkPackageDirty();
        UPackage* Package = Asset->GetOutermost();
        const FString Filename = FPackageName::LongPackageNameToFilename(Package->GetName(), FPackageName::GetAssetPackageExtension());
        IFileManager::Get().MakeDirectory(*FPaths::GetPath(Filename), true);
        FSavePackageArgs Args;
        Args.TopLevelFlags = RF_Public | RF_Standalone;
        Args.SaveFlags = SAVE_NoError;
        return UPackage::SavePackage(Package, Asset, *Filename, Args);
    }

    static bool EnsureDynamicContentIsCooked()
    {
        UProjectPackagingSettings* Packaging = GetMutableDefault<UProjectPackagingSettings>();
        if (!Packaging) return false;
        for (const FString& Path : { FString(TEXT("/DigimonVenomNXT/Generated")) })
        {
            if (!Packaging->DirectoriesToAlwaysCook.ContainsByPredicate([&](const FDirectoryPath& Existing) { return Existing.Path == Path; }))
            {
                FDirectoryPath Directory;
                Directory.Path = Path;
                Packaging->DirectoriesToAlwaysCook.Add(Directory);
            }
        }
        // Always persist the project defaults, including when the in-memory values
        // already matched after an earlier failed write or a session-only change.
        Packaging->SaveConfig();
        return Packaging->TryUpdateDefaultConfigFile(FString(), true);
    }

    static bool LoadJson(const FString& File, TSharedPtr<FJsonObject>& Out)
    {
        FString Text;
        if (!FFileHelper::LoadFileToString(Text, *File)) return false;
        const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
        return FJsonSerializer::Deserialize(Reader, Out) && Out.IsValid();
    }


    enum class EImportScope { All, Partners, Firewall, Tamers, Maps, Presentation, Music, Effects, Farm };
    enum class EAssetKind { Texture, Sprite, Animation, Audio, PartnerSet, TamerSet };
    struct FManifestAsset
    {
        EAssetKind Kind;
        TSharedPtr<FJsonObject> Row;
        FString Package;
    };
    struct FImportPlan
    {
        TSharedPtr<FJsonObject> Manifest;
        TSharedPtr<FJsonObject> MapRegistry;
        TArray<FManifestAsset> Assets;
        TSet<FString> Selected;
        FString ManifestHash;
        FString RegistryHash;
        int32 MapCount = 0;
        bool bMaps = false;
    };
    static const TCHAR* Directions[] = { TEXT("Down"), TEXT("DownLeft"), TEXT("Left"), TEXT("UpLeft"), TEXT("Up"), TEXT("UpRight"), TEXT("Right"), TEXT("DownRight") };

    static bool ValidAssetPath(const FString& Path)
    {
        return Path.StartsWith(TEXT("/DigimonVenomNXT/Generated/")) &&
            !Path.Contains(TEXT("..")) && FPackageName::IsValidLongPackageName(Path);
    }
    static bool SourcePath(const FString& Relative, FString& Full)
    {
        if (!Relative.StartsWith(TEXT("RawAssets/")) || Relative.Contains(TEXT("..")) || Relative.Contains(TEXT("\\"))) return false;
        Full = ResourceFile(*Relative);
        return !Full.IsEmpty() && FPaths::FileExists(Full);
    }
    static TArray<FString> Dependencies(const FManifestAsset& Asset)
    {
        TArray<FString> Result;
        if (Asset.Kind == EAssetKind::Sprite) Result.Add(String(Asset.Row, TEXT("texture")));
        if (Asset.Kind == EAssetKind::Animation)
        {
            const TArray<TSharedPtr<FJsonValue>>* Frames = nullptr;
            if (Asset.Row->TryGetArrayField(TEXT("frames"), Frames))
                for (const TSharedPtr<FJsonValue>& Value : *Frames)
                    if (Value.IsValid() && Value->Type == EJson::Object) Result.Add(String(Value->AsObject(), TEXT("sprite")));
        }
        if (Asset.Kind == EAssetKind::PartnerSet)
        {
            for (const TCHAR* Key : { TEXT("idle"), TEXT("walkLeft"), TEXT("walkRight"), TEXT("attack") }) Result.Add(String(Asset.Row, Key));
            if (Boolean(Asset.Row, TEXT("hasAuthoredLeftFrames")))
                for (const TCHAR* Key : {TEXT("idleLeft"), TEXT("attackLeft")}) Result.Add(String(Asset.Row, Key));
            const TArray<TSharedPtr<FJsonValue>>* Authored = nullptr;
            if (Asset.Row->TryGetArrayField(TEXT("authoredLeftSprites"), Authored))
                for (const TSharedPtr<FJsonValue>& Value : *Authored)
                { FString Path; if (Value.IsValid()) Value->TryGetString(Path); Result.Add(Path); }
            const TArray<TSharedPtr<FJsonValue>>* Bodies = nullptr;
            if (Asset.Row->TryGetArrayField(TEXT("frameBodies"), Bodies))
                for (const TSharedPtr<FJsonValue>& Value : *Bodies)
                    Result.Add(Value.IsValid() && Value->Type == EJson::Object ? String(Value->AsObject(), TEXT("sprite")) : FString());
        }
        if (Asset.Kind == EAssetKind::TamerSet)
        {
            const TSharedPtr<FJsonObject>* Facing = nullptr;
            if (Asset.Row->TryGetObjectField(TEXT("directions"), Facing))
                for (const TCHAR* Direction : Directions) Result.Add(String(*Facing, Direction));
            const FString Thumbnail = String(Asset.Row, TEXT("thumbnail"));
            if (!Thumbnail.IsEmpty()) Result.Add(Thumbnail);
        }
        return Result;
    }
    static bool MatchesScope(const FManifestAsset& Asset, EImportScope Scope)
    {
        const FString& P = Asset.Package;
        switch (Scope)
        {
            case EImportScope::All: return true;
            case EImportScope::Partners: return P.Contains(TEXT("/Digimon/"));
            case EImportScope::Firewall: return P.Contains(TEXT("/Digimon/Firewall/"));
            case EImportScope::Tamers: return P.Contains(TEXT("/Tamers/"));
            case EImportScope::Maps: return P.Contains(TEXT("/Maps/"));
            case EImportScope::Presentation: return P.Contains(TEXT("/UI/")) || P.Contains(TEXT("/Audio/"));
            case EImportScope::Music: return Asset.Kind == EAssetKind::Audio && P.Contains(TEXT("/Audio/BGM/"));
            case EImportScope::Effects: return Asset.Kind == EAssetKind::Audio && P.Contains(TEXT("/Audio/SFX/"));
            case EImportScope::Farm: return P.Contains(TEXT("farm"), ESearchCase::IgnoreCase);
        }
        return false;
    }
    static bool ReadNumberArray(const TSharedPtr<FJsonObject>& Row, const TCHAR* Key, int32 Count, TArray<double>& Out)
    {
        const TArray<TSharedPtr<FJsonValue>>* Values = nullptr;
        if (!Row->TryGetArrayField(Key, Values) || Values->Num() != Count) return false;
        Out.Reset();
        for (const TSharedPtr<FJsonValue>& V : *Values)
        {
            double N;
            if (!V.IsValid() || !V->TryGetNumber(N) || !FMath::IsFinite(N)) return false;
            Out.Add(N);
        }
        return true;
    }
    static bool BuildPlan(EImportScope Scope, FImportPlan& Plan, FString& Problem)
    {
        if (GEditor && GEditor->PlayWorld) { Problem = TEXT("Stop Play in Editor before importing content."); return false; }
        if (!LoadJson(ResourceFile(TEXT("GameData/import_manifest.json")), Plan.Manifest) ||
            Number(Plan.Manifest, TEXT("schemaVersion")) != 1 ||
            !FileSha1(ResourceFile(TEXT("GameData/import_manifest.json")), Plan.ManifestHash))
        { Problem = TEXT("Missing or invalid Resources/GameData/import_manifest.json (schemaVersion 1 is required)."); return false; }
        TMap<FString, int32> Index;
        const auto AddArray = [&](const TCHAR* Key, EAssetKind Kind) -> bool
        {
            const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
            if (!Plan.Manifest->TryGetArrayField(Key, Rows)) { Problem = FString(TEXT("Manifest array missing: ")) + Key; return false; }
            for (const TSharedPtr<FJsonValue>& Value : *Rows)
            {
                if (!Value.IsValid() || Value->Type != EJson::Object) { Problem = FString(TEXT("Invalid manifest record in ")) + Key; return false; }
                const TSharedPtr<FJsonObject> Row = Value->AsObject();
                const FString Package = String(Row, TEXT("asset"));
                if (!ValidAssetPath(Package) || Index.Contains(Package))
                { Problem = TEXT("Invalid or duplicated package path: ") + Package; return false; }
                Index.Add(Package, Plan.Assets.Num());
                Plan.Assets.Add({Kind, Row, Package});
            }
            return true;
        };
        if (!AddArray(TEXT("textures"), EAssetKind::Texture) || !AddArray(TEXT("sprites"), EAssetKind::Sprite) ||
            !AddArray(TEXT("animations"), EAssetKind::Animation) || !AddArray(TEXT("audio"), EAssetKind::Audio) ||
            !AddArray(TEXT("partnerSets"), EAssetKind::PartnerSet) || !AddArray(TEXT("tamerSets"), EAssetKind::TamerSet)) return false;
        // A valid manifest must cover the complete source catalog, not only the
        // subset selected by an incremental repair menu action.
        TSharedPtr<FJsonObject> SpeciesRegistry;
        const TArray<TSharedPtr<FJsonValue>>* Species = nullptr;
        if (!LoadJson(ResourceFile(TEXT("DigimonSpecies.json")), SpeciesRegistry) ||
            !SpeciesRegistry->TryGetArrayField(TEXT("species"), Species) || Species->IsEmpty())
        { Problem = TEXT("The canonical Digimon species registry is missing."); return false; }
        for (const TSharedPtr<FJsonValue>& Value : *Species)
        {
            if (!Value.IsValid() || Value->Type != EJson::Object) { Problem = TEXT("Invalid species registry record."); return false; }
            const FString Id = String(Value->AsObject(), TEXT("speciesId"));
            for (const TCHAR* Variant : {TEXT("Normal"), TEXT("Paradox"), TEXT("Shiny"), TEXT("Firewall")})
            {
                const FString SetPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Digimon/%s/%s/DA_%s_%s_Animation"), Variant, *Id, *Id, Variant);
                const int32* SetIndex = Index.Find(SetPath);
                if (!SetIndex || Plan.Assets[*SetIndex].Kind != EAssetKind::PartnerSet)
                { Problem = TEXT("Source roster has a missing animation set: ") + SetPath; return false; }
            }
        }
        for (const DigimonVenomNXTTamers::FStyle& Style : DigimonVenomNXTTamers::GetRoster())
        {
            const FString Id = Style.Id.ToString();
            const FString SetPath = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Tamers/%s/DA_%s_Animation"), *Id, *Id);
            const int32* SetIndex = Index.Find(SetPath);
            if (!SetIndex || Plan.Assets[*SetIndex].Kind != EAssetKind::TamerSet)
            { Problem = TEXT("Tamer roster has a missing animation set: ") + SetPath; return false; }
        }
        TArray<FString> Pending;
        for (const FManifestAsset& A : Plan.Assets) if (MatchesScope(A, Scope)) Pending.Add(A.Package);
        while (!Pending.IsEmpty())
        {
            const FString Path = Pending.Pop(EAllowShrinking::No);
            if (Plan.Selected.Contains(Path)) continue;
            const int32* Found = Index.Find(Path);
            if (!Found) { Problem = TEXT("Manifest dependency is missing: ") + Path; return false; }
            Plan.Selected.Add(Path);
            Pending.Append(Dependencies(Plan.Assets[*Found]));
        }
        if (Plan.Selected.IsEmpty()) { Problem = TEXT("This import selection contains no source assets."); return false; }
        FScopedSlowTask Progress(static_cast<float>(Plan.Selected.Num()), FText::FromString(TEXT("Verifying Digimon source files and native frame registration")));
        if (!IsRunningCommandlet()) Progress.MakeDialog(true);
        TMap<FString, FString> SourceHashes;
        for (const FManifestAsset& A : Plan.Assets)
        {
            if (!Plan.Selected.Contains(A.Package)) continue;
            if (Progress.ShouldCancel()) { Problem = TEXT("Verification cancelled. Generated assets were not changed."); return false; }
            Progress.EnterProgressFrame(1, FText::FromString(TEXT("Checking ") + FPackageName::GetLongPackageAssetName(A.Package)));
            if (A.Kind == EAssetKind::Texture || A.Kind == EAssetKind::Audio)
            {
                FString Source;
                if (!SourcePath(String(A.Row, TEXT("source")), Source))
                { Problem = TEXT("Source file missing or unsafe: ") + String(A.Row, TEXT("source")); return false; }
                const FString Expected = String(A.Row, TEXT("sha1"));
                FString* Actual = SourceHashes.Find(Source);
                if (!Actual)
                {
                    FString Hash;
                    if (!FileSha1(Source, Hash)) { Problem = TEXT("Could not read source: ") + Source; return false; }
                    Actual = &SourceHashes.Add(Source, Hash);
                }
                if (Expected.Len() != 40 || !Expected.Equals(*Actual, ESearchCase::IgnoreCase))
                { Problem = TEXT("Source checksum mismatch: ") + Source; return false; }
                if (A.Kind == EAssetKind::Texture && (Number(A.Row, TEXT("width")) < 1 || Number(A.Row, TEXT("height")) < 1 ||
                    Number(A.Row, TEXT("width")) > 16384 || Number(A.Row, TEXT("height")) > 16384))
                { Problem = TEXT("Invalid native image dimensions: ") + A.Package; return false; }
            }
            else if (A.Kind == EAssetKind::Sprite)
            {
                TArray<double> Rect, Pivot;
                const FManifestAsset& Texture = Plan.Assets[Index.FindChecked(String(A.Row, TEXT("texture")))];
                if (Texture.Kind != EAssetKind::Texture || !ReadNumberArray(A.Row, TEXT("rect"), 4, Rect) ||
                    !ReadNumberArray(A.Row, TEXT("pivot"), 2, Pivot) || Rect[0] < 0 || Rect[1] < 0 || Rect[2] <= 0 || Rect[3] <= 0 ||
                    Rect[0] + Rect[2] > Number(Texture.Row, TEXT("width")) || Rect[1] + Rect[3] > Number(Texture.Row, TEXT("height")))
                { Problem = TEXT("Invalid sprite rectangle or pivot: ") + A.Package; return false; }
                // Authored pivots can lie outside a cropped rectangle (flying frames).
                if (A.Package.Contains(TEXT("/Maps/SP_PlayMap_"))) Plan.bMaps = true;
            }
            else if (A.Kind == EAssetKind::Animation)
            {
                const TArray<TSharedPtr<FJsonValue>>* Frames = nullptr;
                if (!A.Row->TryGetArrayField(TEXT("frames"), Frames) || Frames->IsEmpty() || Number(A.Row, TEXT("fps")) < 1 || Number(A.Row, TEXT("fps")) > 1000)
                { Problem = TEXT("Empty animation: ") + A.Package; return false; }
                for (const TSharedPtr<FJsonValue>& Frame : *Frames)
                {
                    if (!Frame.IsValid() || Frame->Type != EJson::Object || Number(Frame->AsObject(), TEXT("seconds")) <= 0 ||
                        Number(Frame->AsObject(), TEXT("seconds")) > 60 ||
                        !FMath::IsFinite(Number(Frame->AsObject(), TEXT("seconds"))) ||
                        !FMath::IsNearlyEqual(static_cast<double>(FMath::RoundToInt(Number(Frame->AsObject(), TEXT("seconds")) * Number(A.Row, TEXT("fps")))),
                            Number(Frame->AsObject(), TEXT("seconds")) * Number(A.Row, TEXT("fps")), .0001) ||
                        Plan.Assets[Index.FindChecked(String(Frame->AsObject(), TEXT("sprite")))].Kind != EAssetKind::Sprite)
                    { Problem = TEXT("Invalid animation frame or timing: ") + A.Package; return false; }
                }
            }
            else if (A.Kind == EAssetKind::PartnerSet || A.Kind == EAssetKind::TamerSet)
            {
                const int32 Expected = A.Kind == EAssetKind::PartnerSet ? (Boolean(A.Row, TEXT("hasAuthoredLeftFrames")) ? 6 : 4) : 8;
                const TArray<FString> Refs = Dependencies(A);
                if (Refs.Num() < Expected) { Problem = TEXT("Incomplete animation set: ") + A.Package; return false; }
                for (int32 N = 0; N < Expected; ++N)
                    if (Plan.Assets[Index.FindChecked(Refs[N])].Kind != EAssetKind::Animation)
                    { Problem = TEXT("Animation set references a different asset class: ") + A.Package; return false; }
                if (A.Kind == EAssetKind::PartnerSet)
                {
                    const TArray<TSharedPtr<FJsonValue>>* Authored = nullptr;
                    const bool bHasAuthoredSprites = A.Row->TryGetArrayField(TEXT("authoredLeftSprites"), Authored) && !Authored->IsEmpty();
                    if (bHasAuthoredSprites != Boolean(A.Row, TEXT("hasAuthoredLeftFrames")))
                    { Problem = TEXT("Authored-left flag and source-frame mapping disagree: ") + A.Package; return false; }
                    for (int32 N = Expected; N < Refs.Num(); ++N)
                        if (Plan.Assets[Index.FindChecked(Refs[N])].Kind != EAssetKind::Sprite)
                        { Problem = TEXT("Native frame metadata references a non-sprite asset: ") + A.Package; return false; }
                    const TArray<TSharedPtr<FJsonValue>>* Bodies = nullptr;
                    if (A.Row->TryGetArrayField(TEXT("frameBodies"), Bodies))
                        for (const TSharedPtr<FJsonValue>& Value : *Bodies)
                        {
                            TArray<double> Body;
                            if (!Value.IsValid() || Value->Type != EJson::Object || !ReadNumberArray(Value->AsObject(), TEXT("bodySize"), 2, Body) || Body[0] <= 0 || Body[1] <= 0)
                            { Problem = TEXT("Invalid native frame body dimensions: ") + A.Package; return false; }
                        }
                }
            }
        }
        if (Plan.bMaps)
        {
            const TArray<TSharedPtr<FJsonValue>>* Maps = nullptr;
            if (!LoadJson(ResourceFile(TEXT("DigimonMaps.json")), Plan.MapRegistry) ||
                !Plan.MapRegistry->TryGetArrayField(TEXT("maps"), Maps) || Maps->IsEmpty() ||
                !FileSha1(ResourceFile(TEXT("DigimonMaps.json")), Plan.RegistryHash))
            { Problem = TEXT("DigimonMaps.json is missing or invalid."); return false; }
            Plan.MapCount = Maps->Num();
            if (Plan.MapCount != UDigimonVenomNXTMapAssetRevision::ExpectedMapCount ||
                String(Plan.MapRegistry, TEXT("playableMapContentRevision")) != UDigimonVenomNXTMapAssetRevision::ExpectedRevision ||
                String(Plan.MapRegistry, TEXT("playableMapContentFingerprint")) != UDigimonVenomNXTMapAssetRevision::ExpectedContentFingerprint)
            { Problem = TEXT("Map registry revision differs from this runtime module. Restore the complete matching plugin release."); return false; }
            TSet<int32> Seen;
            FScopedSlowTask CollisionProgress(static_cast<float>(Maps->Num()), FText::FromString(TEXT("Comparing native collision masks with registered movement grids")));
            if (!IsRunningCommandlet()) CollisionProgress.MakeDialog(true);
            for (const TSharedPtr<FJsonValue>& V : *Maps)
            {
                if (!V.IsValid() || V->Type != EJson::Object) { Problem = TEXT("Invalid map registry record."); return false; }
                const TSharedPtr<FJsonObject> Map = V->AsObject();
                const int32 Id = static_cast<int32>(Number(Map, TEXT("mapId")));
                if (CollisionProgress.ShouldCancel()) { Problem = TEXT("Collision verification cancelled. Generated assets were not changed."); return false; }
                CollisionProgress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("Verifying map %d collision pixels"), Id)));
                const int32 W = static_cast<int32>(Number(Map, TEXT("walkGridWidth")));
                const int32 H = static_cast<int32>(Number(Map, TEXT("walkGridHeight")));
                TArray<uint8> Bits;
                const FString MapAsset = FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/SP_PlayMap_%03d"), Id);
                if (Id < 1 || Seen.Contains(Id) || !Plan.Selected.Contains(MapAsset) || W < 1 || H < 1 || W > 16384 || H > 16384 ||
                    !FBase64::Decode(String(Map, TEXT("walkGridBits")), Bits) || Bits.Num() != (static_cast<int64>(W) * H + 7) / 8)
                { Problem = FString::Printf(TEXT("Map %d has no registered artwork or has invalid collision data."), Id); return false; }
                uint8 Digest[FSHA1::DigestSize]; FSHA1::HashBuffer(Bits.GetData(), Bits.Num(), Digest);
                if (!BytesToHex(Digest, FSHA1::DigestSize).Equals(String(Map, TEXT("walkGridSha1")), ESearchCase::IgnoreCase))
                { Problem = FString::Printf(TEXT("Map %d collision-grid checksum differs from its registration."), Id); return false; }
                FString MaskSource;
                FImage Mask;
                if (!SourcePath(String(Map, TEXT("collisionSource")), MaskSource) || !FImageUtils::LoadImage(*MaskSource, Mask) ||
                    Mask.SizeX != W || Mask.SizeY != H || Mask.NumSlices != 1)
                { Problem = FString::Printf(TEXT("Map %d collision image is missing or has mismatched dimensions."), Id); return false; }
                Mask.ChangeFormat(ERawImageFormat::BGRA8, EGammaSpace::sRGB);
                for (int64 PixelIndex = 0; PixelIndex < static_cast<int64>(W) * H; ++PixelIndex)
                {
                    const uint8* Pixel = Mask.RawData.GetData() + PixelIndex * 4;
                    // Match the source converter's greyscale threshold exactly.
                    const int32 Luminance = (19595 * Pixel[2] + 38470 * Pixel[1] + 7471 * Pixel[0] + 32768) >> 16;
                    const bool bMaskWalkable = Luminance >= 128;
                    const bool bRegistered = (Bits[PixelIndex / 8] & (1u << (7 - PixelIndex % 8))) != 0;
                    if (bMaskWalkable != bRegistered)
                    { Problem = FString::Printf(TEXT("Map %d mask differs from the native collision grid at pixel %lld."), Id, PixelIndex); return false; }
                }
                Seen.Add(Id);
            }
        }
        return true;
    }

    static bool ImportedSourceMatches(const UAssetImportData* ImportData, const FString& Source)
    {
        return ImportData && ImportData->GetSourceData().SourceFiles.Num() == 1 &&
            ImportData->GetSourceData().SourceFiles[0].FileHash == FMD5Hash::HashFile(*Source);
    }

    static void ReleaseSavedImportBatch(const FImportPlan& Plan)
    {
        // Limit residency without touching unrelated or unsaved editor content. Assets
        // referenced by an open world/editor stay alive, with their original flags restored.
        TArray<TWeakObjectPtr<UObject>> Released;
        for (TObjectIterator<UObject> It; It; ++It)
        {
            UObject* Object = *It;
            UPackage* Package = Object->GetOutermost();
            if (Object->HasAnyFlags(RF_Standalone) && Package && !Package->IsDirty() && Plan.Selected.Contains(Package->GetName()))
            {
                Released.Add(Object);
                Object->ClearFlags(RF_Standalone);
            }
        }
        CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS, true);
        for (const TWeakObjectPtr<UObject>& Object : Released)
            if (Object.IsValid()) Object->SetFlags(RF_Standalone);
    }

    static UTexture2D* ImportTexture(const FManifestAsset& A, bool bReplace, FString& Problem)
    {
        const FString Path = ObjectPath(A.Package);
        UObject* Existing = LoadObject<UObject>(nullptr, *Path, nullptr, LOAD_NoWarn | LOAD_Quiet);
        UTexture2D* Texture = Cast<UTexture2D>(Existing);
        if (Existing && !Texture) { Problem = TEXT("Package is occupied by a non-texture: ") + Path; return nullptr; }
        const bool bCreate = !Texture;
        const int32 Width = static_cast<int32>(Number(A.Row, TEXT("width")));
        const int32 Height = static_cast<int32>(Number(A.Row, TEXT("height")));
        FString Source;
        SourcePath(String(A.Row, TEXT("source")), Source);
        const bool bSourceMatches = Texture && ImportedSourceMatches(Texture->AssetImportData, Source);
        if (bCreate || bReplace || !bSourceMatches || Texture->Source.GetSizeX() != Width || Texture->Source.GetSizeY() != Height)
        {
            FImage Image;
            if (!FImageUtils::LoadImage(*Source, Image) || Image.SizeX != Width || Image.SizeY != Height || Image.NumSlices != 1)
            { Problem = TEXT("Source image dimensions differ from the manifest: ") + Source; return nullptr; }
            if (!Texture)
            {
                UPackage* Package = CreatePackage(*A.Package);
                Texture = NewObject<UTexture2D>(Package, *FPackageName::GetLongPackageAssetName(A.Package), RF_Public | RF_Standalone | RF_Transactional);
            }
            Texture->Modify();
            Texture->PreEditChange(nullptr);
            Image.ChangeFormat(ERawImageFormat::BGRA8, EGammaSpace::sRGB);
            Texture->Source.Init(Image);
            if (!Texture->AssetImportData) Texture->AssetImportData = NewObject<UAssetImportData>(Texture);
            Texture->AssetImportData->Update(Source);
            Texture->PostEditChange();
            if (bCreate) FAssetRegistryModule::AssetCreated(Texture);
        }
        ConfigureTexture(Texture, String(A.Row, TEXT("group")) == TEXT("ui"), String(A.Row, TEXT("filter")) != TEXT("bilinear"));
        TArray<UTexture*> Textures; Textures.Add(Texture);
        FTextureCompilingManager::Get().FinishCompilation(Textures);
        return Texture;
    }

    static bool ImportManifest(EImportScope Scope, bool bReplace, FString& Report)
    {
        FImportPlan Plan;
        if (!BuildPlan(Scope, Plan, Report)) return false;
        for (const FString& PackageName : Plan.Selected)
            if (UPackage* LoadedPackage = FindPackage(nullptr, *PackageName))
                if (LoadedPackage->IsDirty())
                { Report = TEXT("Save or discard unsaved changes to this generated package before importing: ") + PackageName; return false; }
        if (Plan.bMaps)
            if (UPackage* LoadedMarker = FindPackage(nullptr, TEXT("/DigimonVenomNXT/Generated/Maps/DA_PlayableMapRevision")))
                if (LoadedMarker->IsDirty())
                { Report = TEXT("Save or discard unsaved changes to the map revision marker before importing."); return false; }
        if (UPackage* MaterialPackage = FindPackage(nullptr, TEXT("/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite")))
            if (MaterialPackage->IsDirty())
            { Report = TEXT("Save or discard unsaved changes to MI_DVNXT_FieldSprite before importing."); return false; }
        // A partial update must never retain a success receipt from a previous build.
        if (FPaths::FileExists(ReceiptPath()) && !IFileManager::Get().Delete(*ReceiptPath(), false, true))
        { Report = TEXT("Could not invalidate the previous build receipt. Check project Intermediate permissions."); return false; }
        if (!EnsureDynamicContentIsCooked()) { Report = TEXT("Could not save generated-content cooking settings."); return false; }
        // Resume only packages whose saved bytes match a successful earlier
        // import by this importer and engine for this exact source manifest.
        // An interrupted run never writes the complete-content receipt.
        const FString ProgressPath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("DigimonVenomNXT/ContentImportProgress.json"));
        const FString EngineVersion = FEngineVersion::Current().ToString();
        TMap<FString, FString> CompletedPackages;
        TSharedPtr<FJsonObject> PreviousProgress;
        if (!bReplace && LoadJson(ProgressPath, PreviousProgress) && Number(PreviousProgress, TEXT("schema")) == 1 &&
            String(PreviousProgress, TEXT("importer")) == TEXT("native-frames-v2") &&
            String(PreviousProgress, TEXT("engine")) == EngineVersion && String(PreviousProgress, TEXT("manifestSha1")) == Plan.ManifestHash)
        {
            const TSharedPtr<FJsonObject>* Completed = nullptr;
            if (PreviousProgress->TryGetObjectField(TEXT("completedPackages"), Completed))
                for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*Completed)->Values)
                {
                    FString Hash;
                    if (ValidAssetPath(Pair.Key) && Pair.Value->TryGetString(Hash) && Hash.Len() == 40) CompletedPackages.Add(Pair.Key, Hash);
                }
        }
        const auto SaveProgress = [&]()
        {
            TSharedRef<FJsonObject> ProgressRoot = MakeShared<FJsonObject>();
            ProgressRoot->SetNumberField(TEXT("schema"), 1);
            ProgressRoot->SetStringField(TEXT("importer"), TEXT("native-frames-v2"));
            ProgressRoot->SetStringField(TEXT("engine"), EngineVersion);
            ProgressRoot->SetStringField(TEXT("manifestSha1"), Plan.ManifestHash);
            TSharedRef<FJsonObject> Completed = MakeShared<FJsonObject>();
            for (const TPair<FString, FString>& Pair : CompletedPackages) Completed->SetStringField(Pair.Key, Pair.Value);
            ProgressRoot->SetObjectField(TEXT("completedPackages"), Completed);
            FString JSON; FJsonSerializer::Serialize(ProgressRoot, TJsonWriterFactory<>::Create(&JSON));
            IFileManager::Get().MakeDirectory(*FPaths::GetPath(ProgressPath), true);
            const FString Temp = ProgressPath + TEXT(".tmp");
            if (!FFileHelper::SaveStringToFile(JSON, *Temp, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM) ||
                !IFileManager::Get().Move(*ProgressPath, *Temp, true, true))
                UE_LOG(LogTemp, Warning, TEXT("Could not save the optional Digimon import resume cache: %s. Full-content validation still applies."), *ProgressPath);
        };
        if (!FieldSpriteMaterial()) { Report = TEXT("Could not prepare the native Paper2D field material. Check the Output Log."); return false; }
        TStrongObjectPtr<UDigimonVenomNXTMapAssetRevision> Marker;
        if (Plan.bMaps)
        {
            Marker.Reset(CreateDataAsset<UDigimonVenomNXTMapAssetRevision>(TEXT("/DigimonVenomNXT/Generated/Maps"), TEXT("DA_PlayableMapRevision"), true));
            if (!Marker.IsValid()) { Report = TEXT("Could not create the map completion marker."); return false; }
            Marker->Revision.Reset(); Marker->ContentFingerprint.Reset(); Marker->MapCount = 0;
            if (!SaveAsset(Marker.Get())) { Report = TEXT("Could not invalidate the map completion marker."); return false; }
        }
        FScopedSlowTask Progress(static_cast<float>(Plan.Selected.Num()), FText::FromString(TEXT("Building native Digimon Venom NXT content")));
        if (!IsRunningCommandlet()) Progress.MakeDialog(true);
        int32 Saved = 0;
        int32 Reused = 0;
        FString Problem;
        // Dependencies are imported in explicit order; generated assets retain object identity.
        for (EAssetKind Pass : { EAssetKind::Texture, EAssetKind::Audio, EAssetKind::Sprite, EAssetKind::Animation, EAssetKind::PartnerSet, EAssetKind::TamerSet })
        for (const FManifestAsset& A : Plan.Assets)
        {
            if (A.Kind != Pass || !Plan.Selected.Contains(A.Package)) continue;
            if (Progress.ShouldCancel())
            { SaveProgress(); Report = FString::Printf(TEXT("Cancelled after preparing %d/%d assets. Saved packages are retained; rerun Build Complete Game Content to resume. Full-build receipt remains invalid."), Saved, Plan.Selected.Num()); return false; }
            Progress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("%d/%d  %s"), Saved + 1, Plan.Selected.Num(), *FPackageName::GetLongPackageAssetName(A.Package))));
            const FString SavedFile = FPackageName::LongPackageNameToFilename(A.Package, FPackageName::GetAssetPackageExtension());
            if (!bReplace)
                if (const FString* ExpectedHash = CompletedPackages.Find(A.Package))
                {
                    FString ActualHash;
                    if (FileSha1(SavedFile, ActualHash) && ActualHash == *ExpectedHash)
                    {
                        ++Saved; ++Reused;
                        if (Saved % 128 == 0) ReleaseSavedImportBatch(Plan);
                        continue;
                    }
                    CompletedPackages.Remove(A.Package);
                }
            UObject* Asset = nullptr;
            const FString Folder = FPackageName::GetLongPackagePath(A.Package);
            const FString Name = FPackageName::GetLongPackageAssetName(A.Package);
            if (Pass == EAssetKind::Texture) Asset = ImportTexture(A, bReplace, Problem);
            else if (Pass == EAssetKind::Audio)
            {
                UObject* Existing = LoadObject<UObject>(nullptr, *ObjectPath(A.Package), nullptr, LOAD_NoWarn | LOAD_Quiet);
                USoundWave* Sound = Cast<USoundWave>(Existing);
                if (Existing && !Sound)
                { Report = TEXT("Package is occupied by a non-audio asset: ") + A.Package; return false; }
                FString Source;
                SourcePath(String(A.Row, TEXT("source")), Source);
                if (!Sound || bReplace || !ImportedSourceMatches(Sound->AssetImportData, Source))
                {
                    TStrongObjectPtr<UAssetImportTask> Task(NewObject<UAssetImportTask>());
                    Task->Filename = Source;
                    Task->DestinationPath = Folder; Task->DestinationName = Name;
                    Task->bAutomated = true; Task->bReplaceExisting = true; Task->bReplaceExistingSettings = false;
                    Task->bSave = false; Task->bAsync = false;
                    TArray<UAssetImportTask*> Tasks; Tasks.Add(Task.Get());
                    FAssetToolsModule::GetModule().Get().ImportAssetTasks(Tasks);
                    Sound = LoadObject<USoundWave>(nullptr, *ObjectPath(A.Package), nullptr, LOAD_NoWarn | LOAD_Quiet);
                }
                if (Sound && !ImportedSourceMatches(Sound->AssetImportData, Source))
                { Problem = TEXT("Audio import did not register the current source WAV: ") + Source; Sound = nullptr; }
                if (Sound) { Sound->Modify(); Sound->bLooping = Boolean(A.Row, TEXT("loop")); Sound->PostEditChange(); }
                Asset = Sound;
            }
            else if (Pass == EAssetKind::Sprite)
            {
                TArray<double> R, P; ReadNumberArray(A.Row, TEXT("rect"), 4, R); ReadNumberArray(A.Row, TEXT("pivot"), 2, P);
                UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *ObjectPath(String(A.Row, TEXT("texture"))));
                const FVector2D Pivot(P[0], P[1]);
                Asset = CreateSprite(FAssetToolsModule::GetModule().Get(), Texture, Folder, Name, {static_cast<int32>(R[0]), static_cast<int32>(R[1])},
                    {static_cast<int32>(R[2]), static_cast<int32>(R[3])}, true, false, &Pivot, Boolean(A.Row, TEXT("ground")), static_cast<float>(Number(A.Row, TEXT("pixelsPerUnit"), 1.)));
                UPaperSprite* Sprite = Cast<UPaperSprite>(Asset);
                if (!Sprite || Sprite->GetSourceTexture() != Texture ||
                    !Sprite->GetPivotPosition().Equals(FVector2D(R[0], R[1]) + Pivot, .01) ||
                    !Sprite->GetSourceSize().Equals(FVector2D(R[2], R[3]), .01))
                {
                    Problem = Sprite ? FString::Printf(TEXT("Sprite registration differs: pivot=%s expected=%s, size=%s expected=(%g,%g)."),
                        *Sprite->GetPivotPosition().ToString(), *(FVector2D(R[0], R[1]) + Pivot).ToString(), *Sprite->GetSourceSize().ToString(), R[2], R[3])
                        : TEXT("Paper2D could not create or repair this sprite. Check the source texture and field material errors in the Output Log.");
                    Asset = nullptr;
                }
            }
            else if (Pass == EAssetKind::Animation)
            {
                TArray<UPaperSprite*> Sprites;
                TArray<double> Durations;
                const TArray<TSharedPtr<FJsonValue>>& Frames = A.Row->GetArrayField(TEXT("frames"));
                for (const TSharedPtr<FJsonValue>& Frame : Frames)
                {
                    Sprites.Add(LoadObject<UPaperSprite>(nullptr, *ObjectPath(String(Frame->AsObject(), TEXT("sprite")))));
                    Durations.Add(Number(Frame->AsObject(), TEXT("seconds")));
                }
                // Manifest timebase is chosen to represent the native frame durations exactly.
                Asset = CreateFlipbook(FAssetToolsModule::GetModule().Get(), Folder, Name, Sprites, static_cast<float>(Number(A.Row, TEXT("fps"), 1000.)), true, &Durations);
                if (Sprites.Contains(nullptr)) Asset = nullptr;
            }
            else if (Pass == EAssetKind::PartnerSet)
            {
                UDigimonVenomNXTPartnerAnimationSet* Set = CreateDataAsset<UDigimonVenomNXTPartnerAnimationSet>(Folder, Name, true);
                if (Set)
                {
                    Set->Idle = LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("idle"))));
                    Set->WalkLeft = LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("walkLeft"))));
                    Set->WalkRight = LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("walkRight"))));
                    Set->Attack = LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("attack"))));
                    Set->bHasAuthoredLeftFrames = Boolean(A.Row, TEXT("hasAuthoredLeftFrames"));
                    Set->IdleLeft = Set->bHasAuthoredLeftFrames ? LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("idleLeft")))) : nullptr;
                    Set->AttackLeft = Set->bHasAuthoredLeftFrames ? LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(A.Row, TEXT("attackLeft")))) : nullptr;
                    bool bFrameMetadataReady = true;
                    Set->AuthoredLeftSprites.Reset();
                    const TArray<TSharedPtr<FJsonValue>>* Authored = nullptr;
                    if (A.Row->TryGetArrayField(TEXT("authoredLeftSprites"), Authored))
                        for (const TSharedPtr<FJsonValue>& Value : *Authored)
                        {
                            UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, *ObjectPath(Value->AsString()));
                            if (Sprite) Set->AuthoredLeftSprites.AddUnique(Sprite); else bFrameMetadataReady = false;
                        }
                    Set->NativeFrameBodies.Reset();
                    const TArray<TSharedPtr<FJsonValue>>* Bodies = nullptr;
                    if (A.Row->TryGetArrayField(TEXT("frameBodies"), Bodies))
                        for (const TSharedPtr<FJsonValue>& Value : *Bodies)
                        {
                            const TSharedPtr<FJsonObject> Body = Value->AsObject();
                            UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, *ObjectPath(String(Body, TEXT("sprite"))));
                            TArray<double> Size; ReadNumberArray(Body, TEXT("bodySize"), 2, Size);
                            if (Sprite) Set->NativeFrameBodies.Add(Sprite, FVector2D(Size[0], Size[1])); else bFrameMetadataReady = false;
                        }
                    TArray<double> NativeBody;
                    if (ReadNumberArray(A.Row, TEXT("bodySize"), 2, NativeBody)) Set->NativeBodySize = FVector2D(NativeBody[0], NativeBody[1]);
                    Set->FootOrigins.Reset();
                    const TArray<TSharedPtr<FJsonValue>>* Origins = nullptr;
                    if (A.Row->TryGetArrayField(TEXT("footOrigins"), Origins))
                    {
                        for (const TSharedPtr<FJsonValue>& Origin : *Origins)
                        {
                            const TArray<TSharedPtr<FJsonValue>>* XY = nullptr;
                            if (Origin->TryGetArray(XY) && XY->Num() == 2)
                                Set->FootOrigins.Add(FVector2D((*XY)[0]->AsNumber(), (*XY)[1]->AsNumber()));
                        }
                    }
                    if (bFrameMetadataReady && Set->Idle && Set->WalkLeft && Set->WalkRight && Set->Attack &&
                        (!Set->bHasAuthoredLeftFrames || (Set->IdleLeft && Set->AttackLeft))) Asset = Set;
                }
            }
            else if (Pass == EAssetKind::TamerSet)
            {
                UDigimonVenomNXTTamerAnimationSet* Set = CreateDataAsset<UDigimonVenomNXTTamerAnimationSet>(Folder, Name, true);
                const TSharedPtr<FJsonObject> Facing = A.Row->GetObjectField(TEXT("directions"));
                if (Set)
                {
                    Set->DisplayScale = static_cast<float>(Number(A.Row, TEXT("displayScale"), 2.));
                    TArray<double> NativeBody;
                    if (ReadNumberArray(A.Row, TEXT("nativeSize"), 2, NativeBody)) Set->NativeBodySize = FVector2D(NativeBody[0], NativeBody[1]);
                    auto Load = [&](const TCHAR* Key) { return LoadObject<UPaperFlipbook>(nullptr, *ObjectPath(String(Facing, Key))); };
                    Set->Down = Load(TEXT("Down")); Set->DownLeft = Load(TEXT("DownLeft")); Set->Left = Load(TEXT("Left")); Set->UpLeft = Load(TEXT("UpLeft"));
                    Set->Up = Load(TEXT("Up")); Set->UpRight = Load(TEXT("UpRight")); Set->Right = Load(TEXT("Right")); Set->DownRight = Load(TEXT("DownRight"));
                    if (Set->Down && Set->DownLeft && Set->Left && Set->UpLeft && Set->Up && Set->UpRight && Set->Right && Set->DownRight) Asset = Set;
                }
            }
            if (!Asset || !SaveAsset(Asset))
            {
                SaveProgress();
                Report = FString::Printf(TEXT("Import stopped at %s after %d saved assets. %s Check the Output Log and available disk space; rerun after fixing the issue."), *A.Package, Saved, *Problem);
                return false;
            }
            FString PackageHash;
            if (FileSha1(SavedFile, PackageHash)) CompletedPackages.Add(A.Package, PackageHash);
            ++Saved;
            if (Saved % 512 == 0) SaveProgress();
            if (Saved % 128 == 0)
            {
                UE_LOG(LogTemp, Display, TEXT("Digimon content import: %d/%d assets saved."), Saved, Plan.Selected.Num());
                ReleaseSavedImportBatch(Plan);
            }
        }
        SaveProgress();
        FString CurrentHash;
        if (!FileSha1(ResourceFile(TEXT("GameData/import_manifest.json")), CurrentHash) || CurrentHash != Plan.ManifestHash ||
            (Plan.bMaps && (!FileSha1(ResourceFile(TEXT("DigimonMaps.json")), CurrentHash) || CurrentHash != Plan.RegistryHash)))
        { Report = TEXT("Source registries changed during import. Rerun with a consistent source package; completion has not been recorded."); return false; }
        if (Marker.IsValid())
        {
            Marker->Revision = UDigimonVenomNXTMapAssetRevision::ExpectedRevision;
            Marker->MapCount = Plan.MapCount;
            Marker->ContentFingerprint = String(Plan.MapRegistry, TEXT("playableMapContentFingerprint"));
            if (!SaveAsset(Marker.Get())) { Report = TEXT("Assets saved, but map completion marker could not be saved."); return false; }
        }
        Report = FString::Printf(TEXT("Prepared and verified %d native Digimon assets (%d reused from matching saved packages). Original image dimensions, alpha, animation timing and frame pivots are retained. Generated content is registered for cooking."), Saved, Reused);
        return true;
    }

    static bool WriteCompleteReceipt(FString& Problem)
    {
        FImportPlan Plan;
        // Includes a final source verification before recording a complete build.
        if (!BuildPlan(EImportScope::All, Plan, Problem)) return false;
        TSet<FString> Packages = Plan.Selected;
        for (const TCHAR* P : {TEXT("/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite"),
            TEXT("/DigimonVenomNXT/Generated/Maps/DA_PlayableMapRevision"), TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu"),
            TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld")}) Packages.Add(P);
        TArray<FString> Ordered = Packages.Array(); Ordered.Sort();
        TArray<TSharedPtr<FJsonValue>> Rows;
        for (const FString& Package : Ordered)
        {
            const bool bWorld = Package.Contains(TEXT("/Levels/"));
            const FString Filename = FPackageName::LongPackageNameToFilename(Package, bWorld ? FPackageName::GetMapPackageExtension() : FPackageName::GetAssetPackageExtension());
            FString Hash;
            if (!FileSha1(Filename, Hash)) { Problem = TEXT("Could not verify saved package: ") + Filename; return false; }
            TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
            Row->SetStringField(TEXT("packagePath"), Package); Row->SetStringField(TEXT("sha1"), Hash);
            Rows.Add(MakeShared<FJsonValueObject>(Row));
        }
        TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
        Root->SetNumberField(TEXT("schema"), 1);
        Root->SetStringField(TEXT("revision"), TEXT("digimon-venom-nxt-native-1"));
        Root->SetStringField(TEXT("manifestSha1"), Plan.ManifestHash);
        Root->SetStringField(TEXT("registrySha1"), Plan.RegistryHash);
        Root->SetNumberField(TEXT("mapCount"), Plan.MapCount);
        Root->SetNumberField(TEXT("expectedPackageCount"), Ordered.Num());
        Root->SetStringField(TEXT("generatedUtc"), FDateTime::UtcNow().ToIso8601());
        Root->SetArrayField(TEXT("packages"), Rows);
        FString JSON; FJsonSerializer::Serialize(Root, TJsonWriterFactory<>::Create(&JSON));
        IFileManager::Get().MakeDirectory(*FPaths::GetPath(ReceiptPath()), true);
        const FString Temp = ReceiptPath() + TEXT(".tmp");
        if (!FFileHelper::SaveStringToFile(JSON, *Temp, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM) ||
            !IFileManager::Get().Move(*ReceiptPath(), *Temp, true, true))
        { Problem = TEXT("Could not save the complete-content build receipt."); return false; }
        return true;
    }
}

bool UDigimonVenomNXTEditorLibrary::ValidateBundledContent(FString& OutReport)
{
    DigimonVenomNXTEditorInternal::FImportPlan Plan;
    if (!DigimonVenomNXTEditorInternal::BuildPlan(DigimonVenomNXTEditorInternal::EImportScope::All, Plan, OutReport)) return false;
    OutReport = FString::Printf(TEXT("Verified %d manifest assets and %d maps, including source checksums, dependency paths, frame registration and collision grid sizes. No generated assets were changed."), Plan.Selected.Num(), Plan.MapCount);
    return true;
}
bool UDigimonVenomNXTEditorLibrary::ImportCoreAssets(bool R, FString& Out) { return BuildCompleteGameContent(R, Out); }
bool UDigimonVenomNXTEditorLibrary::ImportAllBundledAssets(bool R, FString& Out) { return ImportCoreAssets(R, Out); }
bool UDigimonVenomNXTEditorLibrary::ImportFirewallRosterAssets(bool R, FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Firewall, R, Out); }
bool UDigimonVenomNXTEditorLibrary::ImportFullTamerRosterAssets(bool R, FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Tamers, R, Out); }
bool UDigimonVenomNXTEditorLibrary::ImportPlayableMapAssets(bool R, FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Maps, R, Out); }
bool UDigimonVenomNXTEditorLibrary::ImportPresentationPolishAssets(bool R, FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Presentation, R, Out); }
bool UDigimonVenomNXTEditorLibrary::RepairSoundEffects(FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Effects, false, Out); }
bool UDigimonVenomNXTEditorLibrary::RepairBackgroundMusic(FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Music, false, Out); }
bool UDigimonVenomNXTEditorLibrary::PreparePrivateDigiFarm(FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Farm, false, Out); }
bool UDigimonVenomNXTEditorLibrary::RepairFieldSpriteRendering(FString& Out) { return DigimonVenomNXTEditorInternal::ImportManifest(DigimonVenomNXTEditorInternal::EImportScope::Partners, false, Out); }

bool UDigimonVenomNXTEditorLibrary::BuildStarterLevels(bool bOverwriteExisting, FString& OutReport)
{
    using namespace DigimonVenomNXTEditorInternal;
    if (GEditor && GEditor->PlayWorld) { OutReport = TEXT("Stop Play in Editor before generating starter worlds."); return false; }
    TSharedPtr<FJsonObject> Registry;
    const TArray<TSharedPtr<FJsonValue>>* Maps = nullptr;
    if (!LoadJson(ResourceFile(TEXT("DigimonMaps.json")), Registry) || !Registry->TryGetArrayField(TEXT("maps"), Maps) ||
        Maps->Num() != UDigimonVenomNXTMapAssetRevision::ExpectedMapCount ||
        String(Registry, TEXT("playableMapContentRevision")) != UDigimonVenomNXTMapAssetRevision::ExpectedRevision ||
        String(Registry, TEXT("playableMapContentFingerprint")) != UDigimonVenomNXTMapAssetRevision::ExpectedContentFingerprint)
    { OutReport = TEXT("The native map registry is missing or belongs to a different plugin release. No world was changed."); return false; }
    TMap<int32, TSharedPtr<FJsonObject>> RegisteredMaps;
    for (const TSharedPtr<FJsonValue>& Value : *Maps)
    {
        if (!Value.IsValid() || Value->Type != EJson::Object) { OutReport = TEXT("Invalid native map record."); return false; }
        const TSharedPtr<FJsonObject> Row = Value->AsObject();
        const double RawId = Number(Row, TEXT("mapId"));
        const int32 Id = static_cast<int32>(RawId);
        const double U = Number(Row, TEXT("safeSpawnU"), -1), V = Number(Row, TEXT("safeSpawnV"), -1);
        if (RawId != Id || Id < 1 || Id > Maps->Num() || RegisteredMaps.Contains(Id) ||
            Number(Row, TEXT("sourceWidth")) < 1 || Number(Row, TEXT("sourceHeight")) < 1 ||
            !FMath::IsFinite(U) || !FMath::IsFinite(V) || U < 0 || U > 1 || V < 0 || V > 1)
        { OutReport = FString::Printf(TEXT("Map %d has invalid identity, dimensions or arrival coordinates. No world was changed."), Id); return false; }
        RegisteredMaps.Add(Id, Row);
    }
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    if (!Settings || !FMath::IsFinite(Settings->MapWorldWidth) || Settings->MapWorldWidth <= 0)
    { OutReport = TEXT("Map World Width must be positive in Project Settings > Digimon Venom NXT."); return false; }
    const FString MenuPath = TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu");
    const FString WorldPath = TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld");
    // Worlds depend on source metadata, not imported artwork. Save them before
    // the large asset import so a failed/cancelled import cannot omit both maps.
    for (const FString& Path : {MenuPath, WorldPath})
        if (UPackage* Existing = FindPackage(nullptr, *Path))
            if (Existing->IsDirty())
            { OutReport = TEXT("Save or discard pending edits to ") + Path + TEXT(" before setup. Unsaved work was preserved."); return false; }
    auto LoadOrCreate = [&](const FString& Path, TStrongObjectPtr<UWorld>& Result, bool& bCreated) -> bool
    {
        bCreated = !FPackageName::DoesPackageExist(Path);
        if (!bCreated)
        {
            Result.Reset(LoadObject<UWorld>(nullptr, *ObjectPath(Path), nullptr, LOAD_NoWarn | LOAD_Quiet));
            if (!Result.IsValid() || !Result->GetWorldSettings())
            { OutReport = TEXT("The saved package is not a valid world: ") + Path; return false; }
            if (Result->GetOutermost()->IsDirty())
            { OutReport = TEXT("Save pending edits to ") + Path + TEXT(" before setup."); return false; }
            return true;
        }
        if (FindPackage(nullptr, *Path))
        { OutReport = TEXT("An unsaved package occupies ") + Path + TEXT(". Save or close it before continuing."); return false; }
        UPackage* Package = CreatePackage(*Path);
        if (!Package) { OutReport = TEXT("Could not create package: ") + Path; return false; }
        Package->SetPackageFlags(PKG_ContainsMap);
        Result.Reset(UWorld::CreateWorld(EWorldType::Editor, false, FName(*FPackageName::GetLongPackageAssetName(Path)), Package, false));
        if (!Result.IsValid() || !Result->GetWorldSettings())
        { OutReport = TEXT("Could not initialize world: ") + Path; return false; }
        Result->SetFlags(RF_Public | RF_Standalone);
        FAssetRegistryModule::AssetCreated(Result.Get());
        return true;
    };
    auto SaveWorld = [&](UWorld* W, const FString& Path) -> bool
    {
        FString File;
        if (!FPackageName::TryConvertLongPackageNameToFilename(Path, File, FPackageName::GetMapPackageExtension()) ||
            !IFileManager::Get().MakeDirectory(*FPaths::GetPath(File), true))
        { OutReport = TEXT("The plugin Content folder is not mounted or writable for ") + Path; return false; }
        W->GetOutermost()->SetPackageFlags(PKG_ContainsMap);
        W->MarkPackageDirty();
        FSavePackageArgs Args; Args.TopLevelFlags = RF_Public | RF_Standalone; Args.SaveFlags = SAVE_NoError;
        if (!UPackage::SavePackage(W->GetOutermost(), W, *File, Args) || !FPaths::FileExists(File))
        { OutReport = TEXT("Could not save starter world: ") + FPaths::ConvertRelativePathToFull(File) + TEXT(". Check folder permissions and disk space."); return false; }
        UE_LOG(LogTemp, Display, TEXT("Digimon setup saved world: %s"), *FPaths::ConvertRelativePathToFull(File));
        return true;
    };
    TStrongObjectPtr<UWorld> Menu, World;
    bool bMenuCreated = false, bWorldCreated = false;
    if (!LoadOrCreate(MenuPath, Menu, bMenuCreated)) return false;
    Menu->GetWorldSettings()->DefaultGameMode = ADigimonVenomNXTMainMenuGameMode::StaticClass();
    if (!SaveWorld(Menu.Get(), MenuPath)) return false;
    if (!LoadOrCreate(WorldPath, World, bWorldCreated)) return false;
    World->GetWorldSettings()->DefaultGameMode = ADigimonVenomNXTGameMode::StaticClass();
    // Persist the valid empty shell immediately. A later retry fills missing
    // zones instead of being blocked by an entirely absent PublicWorld package.
    if (bWorldCreated && !SaveWorld(World.Get(), WorldPath)) return false;
    TMap<int32, ADigimonVenomNXTMapZone*> ExistingZones;
    TArray<AActor*> Remove;
    APlayerStart* GeneratedStart = nullptr;
    const FName StartTag(TEXT("DigimonVenomNXT.GeneratedPlayerStart"));
    for (ULevel* Level : World->GetLevels())
        if (Level) for (AActor* Actor : Level->Actors)
        {
            if (!IsValid(Actor) || Actor->IsActorBeingDestroyed()) continue;
            if (ADigimonVenomNXTMapZone* Zone = Cast<ADigimonVenomNXTMapZone>(Actor))
            {
                const int32 Id = Zone->GetRuntimeMapId();
                if (bOverwriteExisting || !RegisteredMaps.Contains(Id) || ExistingZones.Contains(Id)) Remove.Add(Zone);
                else ExistingZones.Add(Id, Zone);
            }
            else if (APlayerStart* Start = Cast<APlayerStart>(Actor))
            {
                if (Start->ActorHasTag(StartTag) || Start->GetActorLabel() == TEXT("Digimon Venom NXT Player Start"))
                {
                    if (GeneratedStart) Remove.Add(Start); else GeneratedStart = Start;
                }
            }
        }
    for (AActor* Actor : Remove)
        if (!World->DestroyActor(Actor))
        { OutReport = TEXT("Could not remove a duplicate generated zone/start: ") + Actor->GetName(); return false; }
    FScopedSlowTask Progress(static_cast<float>(Maps->Num()), FText::FromString(TEXT("Creating Digimon MainMenu and PublicWorld map zones")));
    if (!IsRunningCommandlet()) Progress.MakeDialog(false);
    int32 Created = 0;
    for (const TSharedPtr<FJsonValue>& Value : *Maps)
    {
        const TSharedPtr<FJsonObject> Row = Value->AsObject();
        const int32 Id = static_cast<int32>(Number(Row, TEXT("mapId")));
        Progress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("Preparing habitat %d/%d"), Id, Maps->Num())));
        const FVector Location(((Id - 1) % 10) * 14000.f, ((Id - 1) / 10) * 11000.f, 0.f);
        ADigimonVenomNXTMapZone* Zone = ExistingZones.FindRef(Id);
        if (!Zone)
        {
            FActorSpawnParameters Params;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            Zone = World->SpawnActor<ADigimonVenomNXTMapZone>(ADigimonVenomNXTMapZone::StaticClass(), Location, FRotator::ZeroRotator, Params);
            if (!Zone) { OutReport = FString::Printf(TEXT("Could not create map zone %d. Saved level shells remain available; rerun Create / Repair Main Menu + Public World."), Id); return false; }
            ++Created;
        }
        Zone->Modify();
        Zone->SetActorLocation(Location);
        Zone->SetActorRotation(FRotator::ZeroRotator);
        Zone->SetActorScale3D(FVector::OneVector);
        Zone->SetActorLabel(FString::Printf(TEXT("DVNXT Map %03d - %s"), Id, *String(Row, TEXT("displayName"))));
        Zone->MapId = Id;
        Zone->DisplayName = FText::FromString(String(Row, TEXT("displayName")));
        FString RegionId = String(Row, TEXT("regionId"));
        if (RegionId.IsEmpty()) RegionId = String(Row, TEXT("region"));
        const int32 Region = static_cast<int32>(Number(Row, TEXT("region"), 1));
        Zone->Region = RegionId == TEXT("world_ds") || Region == 2 ? EDigimonRegion::RegionTwo :
            RegionId == TEXT("xros_wars") || Region == 3 ? EDigimonRegion::RegionThree : EDigimonRegion::RegionOne;
        Zone->MinLevel = static_cast<int32>(Number(Row, TEXT("recommendedMinLevel"), 1));
        Zone->MaxLevel = static_cast<int32>(Number(Row, TEXT("recommendedMaxLevel"), 1));
        Zone->WildSpecies.Reset();
        const TArray<TSharedPtr<FJsonValue>>* Wild = nullptr;
        if (Row->TryGetArrayField(TEXT("wildSpecies"), Wild))
            for (const TSharedPtr<FJsonValue>& V : *Wild) { FString Species; if (V->TryGetString(Species)) Zone->WildSpecies.Add(FName(*Species)); }
        Zone->SourceImageSize = FIntPoint(static_cast<int32>(Number(Row, TEXT("sourceWidth"))), static_cast<int32>(Number(Row, TEXT("sourceHeight"))));
        Zone->SafeSpawnUV = FVector2D(Number(Row, TEXT("safeSpawnU")), Number(Row, TEXT("safeSpawnV")));
        Zone->ApplyMapPresentation();
        ExistingZones.Add(Id, Zone);
    }
    ADigimonVenomNXTMapZone* FirstZone = ExistingZones.FindRef(1);
    if (!FirstZone) { OutReport = TEXT("The registered starting habitat is missing."); return false; }
    const FVector StartLocation = FirstZone->GetPlayerSpawnLocation();
    if (!GeneratedStart)
    {
        FActorSpawnParameters Params; Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        GeneratedStart = World->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), StartLocation, FRotator::ZeroRotator, Params);
    }
    if (!GeneratedStart) { OutReport = TEXT("Could not create the player start. Rerun Create / Repair Main Menu + Public World."); return false; }
    GeneratedStart->SetActorLocation(StartLocation);
    GeneratedStart->Tags.AddUnique(StartTag);
    GeneratedStart->SetActorLabel(TEXT("Digimon Venom NXT Player Start"));
    if (!SaveWorld(World.Get(), WorldPath)) return false;
    OutReport = FString::Printf(TEXT("Saved MainMenu and PublicWorld with all %d native map zones (%d created) and a registered player start.\n%s\n%s\nThese levels are available before artwork import; complete content setup is required before playing habitats."),
        Maps->Num(), Created, *MenuPath, *WorldPath);
    return true;
}
namespace DigimonVenomNXTEditorInternal
{
static bool SaveRenderDefaults(FString& OutReport)
{
    if (!GConfig) { OutReport = TEXT("Project configuration is unavailable."); return false; }
    FString DefaultEngine = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultEngine.ini")));
    FPaths::NormalizeFilename(DefaultEngine);
    const TCHAR* RendererSection = TEXT("/Script/Engine.RendererSettings");
    const TCHAR* DepthKey = TEXT("r.CustomDepth");
    FConfigFile SavedEngine;
    SavedEngine.Read(DefaultEngine);
    int32 SavedDepth = 0;
    if (!SavedEngine.GetInt(RendererSection, DepthKey, SavedDepth) || SavedDepth != 3)
    {
        // Source defaults are not the generated Engine config-cache branch.
        // Write only this disk property, retaining other renderer keys and all
        // unrelated sections instead of saving commandlet renderer settings.
        FConfigFile DepthUpdate;
        DepthUpdate.SetString(RendererSection, DepthKey, TEXT("3"));
        if (!DepthUpdate.UpdateSinglePropertyInSection(*DefaultEngine, DepthKey, RendererSection))
        {
            OutReport = FString::Printf(TEXT("Unreal's single-property config writer could not save r.CustomDepth=3 to '%s' (file exists: %s; read-only: %s). See LogConfig for the underlying write error."),
                *DefaultEngine, FPaths::FileExists(DefaultEngine) ? TEXT("yes") : TEXT("no"),
                IFileManager::Get().IsReadOnly(*DefaultEngine) ? TEXT("yes") : TEXT("no"));
            return false;
        }
        SavedEngine.Reset();
        SavedEngine.Read(DefaultEngine);
    }
    if (!SavedEngine.GetInt(RendererSection, DepthKey, SavedDepth) || SavedDepth != 3)
    {
        OutReport = FString::Printf(TEXT("Renderer config verification failed for '%s': expected [%s] %s=3, but that value was not present when the file was reread. Content setup remains incomplete."),
            *DefaultEngine, RendererSection, DepthKey);
        return false;
    }
    GConfig->SetInt(RendererSection, DepthKey, 3, GEngineIni);
    UDigimonVenomNXTSettings* Settings = GetMutableDefault<UDigimonVenomNXTSettings>();
    Settings->bRenderCustomDepthByDefault = true;
    Settings->SaveConfig();
    if (!Settings->TryUpdateDefaultConfigFile(FString(), true))
    {
        OutReport = FString::Printf(TEXT("Unreal could not update Digimon render defaults in '%s'. See LogConfig for the underlying config-update error."),
            *FPaths::ConvertRelativePathToFull(Settings->GetDefaultConfigFilename()));
        return false;
    }
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    OutReport = TEXT("Custom Depth with Stencil and Digimon render defaults saved to project settings.");
    return true;
}
}

bool UDigimonVenomNXTEditorLibrary::ConfigureLevelCustomDepth(FString& OutReport)
{
    if (!DigimonVenomNXTEditorInternal::SaveRenderDefaults(OutReport)) return false;
    UWorld* World = !IsRunningCommandlet() && GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
    const int32 Changed = DigimonVenomNXTCustomDepth::ConfigureWorld(World);
    TArray<UMaterial*> ChangedMaterials;
    TArray<FString> Warnings;
    DigimonVenomNXTEditorCustomDepth::PrepareWorldMaterials(World, ChangedMaterials, Warnings);
    int32 SavedMaterials = 0;
    for (UMaterial* Material : ChangedMaterials)
    {
        if (DigimonVenomNXTEditorInternal::SaveAsset(Material)) ++SavedMaterials;
        else Warnings.Add(TEXT("Could not save Custom Depth material: ") + Material->GetPathName());
    }
    OutReport = FString::Printf(TEXT("Custom Depth with Stencil enabled in project settings. %d rendered level components enabled immediately; %d/%d assigned translucent materials repaired and saved. The world subsystem maintains coverage for existing, spawned and streamed level assets in the editor and packaged game; authored stencil IDs and visibility are preserved."), Changed, SavedMaterials, ChangedMaterials.Num());
    for (const FString& Warning : Warnings) OutReport += TEXT("\n") + Warning;
    return SavedMaterials == ChangedMaterials.Num() && Warnings.IsEmpty();
}

namespace DigimonVenomNXTEditorInternal
{
static bool SaveStartupConfiguration(FString& OutReport)
{
    if (GEditor && GEditor->PlayWorld)
    { OutReport = TEXT("Stop Play in Editor, then run Repair Packaged Startup from the editor Tools menu."); return false; }

    const FString MainMenu = TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu");
    const FString PublicWorld = TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld");
    // Inspect assets directly. Loading/rebuilding an editor level would discard or
    // save unrelated work, and recreating PublicWorld would replace custom edits.
    if (!FPackageName::DoesPackageExist(PublicWorld))
    {
        OutReport = TEXT("The saved /DigimonVenomNXT/Generated/Levels/PublicWorld map is missing. Restore the existing map from your working project, or use Build Complete Game Content for a new project. No world has been rebuilt.");
        return false;
    }
    TStrongObjectPtr<UWorld> PublicWorldAsset(LoadObject<UWorld>(nullptr, *(PublicWorld + TEXT(".PublicWorld"))));
    if (!PublicWorldAsset.IsValid() || !PublicWorldAsset->GetWorldSettings())
    { OutReport = TEXT("PublicWorld exists but could not be loaded as a valid world. Restore that map from your working project; this repair will not overwrite it."); return false; }
    if (PublicWorldAsset->GetOutermost()->IsDirty())
    { OutReport = TEXT("PublicWorld has unsaved changes. Save that map, then run Repair Packaged Startup again so packaging uses your latest work."); return false; }

    const bool bCreateMainMenu = !FPackageName::DoesPackageExist(MainMenu);
    TStrongObjectPtr<UWorld> MainMenuAsset;
    if (bCreateMainMenu)
    {
        // Do not reuse an unsaved package under the canonical name. In particular,
        // never overwrite a map currently being edited in an unsaved state.
        if (FindPackage(nullptr, *MainMenu))
        { OutReport = TEXT("MainMenu is loaded but has not been saved. Save or close that map, then run Repair Packaged Startup again."); return false; }
        UPackage* MenuPackage = CreatePackage(*MainMenu);
        if (!MenuPackage)
        { OutReport = TEXT("Could not create the missing MainMenu package."); return false; }
        MenuPackage->SetPackageFlags(PKG_ContainsMap);
        MainMenuAsset.Reset(UWorld::CreateWorld(EWorldType::Editor, false, FName(TEXT("MainMenu")), MenuPackage, false));
        if (MainMenuAsset.IsValid())
        {
            MainMenuAsset->SetFlags(RF_Public | RF_Standalone);
            FAssetRegistryModule::AssetCreated(MainMenuAsset.Get());
        }
    }
    else
    {
        MainMenuAsset.Reset(LoadObject<UWorld>(nullptr, *(MainMenu + TEXT(".MainMenu"))));
    }
    if (!MainMenuAsset.IsValid() || !MainMenuAsset->GetWorldSettings())
    { OutReport = TEXT("MainMenu could not be loaded or created with valid World Settings. Existing maps have not been replaced."); return false; }
    if (!bCreateMainMenu && MainMenuAsset->GetOutermost()->IsDirty())
    { OutReport = TEXT("MainMenu has unsaved changes. Save that map, then run Repair Packaged Startup again."); return false; }

    AWorldSettings* MenuWorldSettings = MainMenuAsset->GetWorldSettings();
    if (bCreateMainMenu || MenuWorldSettings->DefaultGameMode != ADigimonVenomNXTMainMenuGameMode::StaticClass())
    {
        MenuWorldSettings->Modify();
        MenuWorldSettings->DefaultGameMode = ADigimonVenomNXTMainMenuGameMode::StaticClass();
        MainMenuAsset->MarkPackageDirty();
        const FString MenuFile = FPackageName::LongPackageNameToFilename(MainMenu, FPackageName::GetMapPackageExtension());
        IFileManager::Get().MakeDirectory(*FPaths::GetPath(MenuFile), true);
        FSavePackageArgs Args; Args.TopLevelFlags = RF_Public | RF_Standalone; Args.SaveFlags = SAVE_NoError;
        if (!UPackage::SavePackage(MainMenuAsset->GetOutermost(), MainMenuAsset.Get(), *MenuFile, Args))
        { OutReport = TEXT("MainMenu could not be saved. Make the plugin Content/Generated/Levels folder writable and retry. Project startup defaults were not changed."); return false; }
    }

    UGameMapsSettings* Maps = UGameMapsSettings::GetGameMapsSettings();
    UDigimonVenomNXTSettings* Settings = GetMutableDefault<UDigimonVenomNXTSettings>();
    UProjectPackagingSettings* Packaging = GetMutableDefault<UProjectPackagingSettings>();
    if (!Maps || !Settings || !Packaging)
    {
        OutReport = TEXT("Project startup or packaging settings are unavailable.");
        return false;
    }
    UGameMapsSettings::SetGameDefaultMap(MainMenu);
    Maps->EditorStartupMap = FSoftObjectPath(MainMenu + TEXT(".MainMenu"));
    Maps->GameInstanceClass = FSoftClassPath(UDigimonVenomNXTGameInstance::StaticClass()->GetPathName());
    Maps->SaveConfig();
    if (!Maps->TryUpdateDefaultConfigFile(FString(), true))
    { OutReport = TEXT("Could not write the startup map and GameInstance to project Config/DefaultEngine.ini. Make that file writable and rerun this repair before packaging."); return false; }

    Settings->MainMenuMap = FSoftObjectPath(MainMenu + TEXT(".MainMenu"));
    Settings->PublicWorldMap = FSoftObjectPath(PublicWorld + TEXT(".PublicWorld"));
    Settings->SaveConfig();
    if (!Settings->TryUpdateDefaultConfigFile(FString(), true))
    { OutReport = TEXT("Could not write Digimon map travel targets to project Config/DefaultGame.ini. Make that file writable and rerun this repair before packaging."); return false; }

    for (const FString& MapPath : { MainMenu, PublicWorld })
    {
        if (!Packaging->MapsToCook.ContainsByPredicate([&](const FFilePath& Entry) { return Entry.FilePath == MapPath; }))
        {
            FFilePath Entry;
            Entry.FilePath = MapPath;
            Packaging->MapsToCook.Add(Entry);
        }
    }
    // A source plugin needs a game executable build, even when the host project
    // began as Blueprint-only. Do not rely on the conditional packaging default.
    Packaging->Build = EProjectPackagingBuild::Always;
    Packaging->FullRebuild = true;
    if (!DigimonVenomNXTEditorInternal::EnsureDynamicContentIsCooked())
    { OutReport = TEXT("Could not save Build Always, Full Rebuild, the map cook list and dynamic asset directories to project Config/DefaultGame.ini. Make that file writable and rerun this repair before packaging."); return false; }

    OutReport = TEXT("Packaged startup configuration saved. MainMenu and PublicWorld are valid saved worlds; MainMenu uses the native menu game mode. DigimonVenomNXTGameInstance, the default startup map, both Maps to Cook entries and dynamic asset cook directories are written to project defaults. Packaging is set to Build Always with Full Rebuild so it requests a new game executable. PublicWorld and the open editor level were preserved. Package a fresh Windows build to apply these changes.");
    return true;
}

}

bool UDigimonVenomNXTEditorLibrary::ConfigureProjectForDigimonVenomNXT(FString& OutReport)
{
    if (!DigimonVenomNXTEditorInternal::SaveStartupConfiguration(OutReport)) return false;

    FString DepthReport;
    // Complete game setup may run while an unrelated authored level is open.
    // Material edits belong exclusively to the explicit current-level repair.
    const bool bDepthReady = DigimonVenomNXTEditorInternal::SaveRenderDefaults(DepthReport);
    OutReport += TEXT("\n") + DepthReport;
    if (!bDepthReady) return false;
    FString ValidationReport;
    if (!DigimonVenomNXTEditorInternal::ValidateWorldSetup(false, ValidationReport))
    { OutReport += TEXT("\n") + ValidationReport; return false; }
    return true;
}

namespace DigimonVenomNXTEditorInternal
{
static bool ValidateWorldSetup(bool bRequireImportedContent, FString& Report)
{
    const FString MenuPath = TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu");
    const FString WorldPath = TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld");
    for (const FString& Path : {MenuPath, WorldPath})
        if (!FPackageName::DoesPackageExist(Path))
        { Report = TEXT("Missing saved world: ") + Path + TEXT(". Run Create / Repair Main Menu + Public World."); return false; }
    TStrongObjectPtr<UWorld> Menu(LoadObject<UWorld>(nullptr, *ObjectPath(MenuPath), nullptr, LOAD_NoWarn | LOAD_Quiet));
    TStrongObjectPtr<UWorld> World(LoadObject<UWorld>(nullptr, *ObjectPath(WorldPath), nullptr, LOAD_NoWarn | LOAD_Quiet));
    if (!Menu.IsValid() || !World.IsValid() || !Menu->GetWorldSettings() || !World->GetWorldSettings())
    { Report = TEXT("A startup package could not be loaded as a valid UWorld. Run Create / Repair Main Menu + Public World."); return false; }
    if (Menu->GetOutermost()->IsDirty() || World->GetOutermost()->IsDirty())
    { Report = TEXT("A startup world has unsaved changes. Save both generated worlds before validation or packaging."); return false; }
    if (Menu->GetWorldSettings()->DefaultGameMode != ADigimonVenomNXTMainMenuGameMode::StaticClass() ||
        World->GetWorldSettings()->DefaultGameMode != ADigimonVenomNXTGameMode::StaticClass())
    { Report = TEXT("MainMenu or PublicWorld uses the wrong game mode. Run Create / Repair Main Menu + Public World."); return false; }
    TSharedPtr<FJsonObject> Registry;
    const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
    if (!LoadJson(ResourceFile(TEXT("DigimonMaps.json")), Registry) || !Registry->TryGetArrayField(TEXT("maps"), Rows) ||
        Rows->Num() != UDigimonVenomNXTMapAssetRevision::ExpectedMapCount ||
        String(Registry, TEXT("playableMapContentRevision")) != UDigimonVenomNXTMapAssetRevision::ExpectedRevision ||
        String(Registry, TEXT("playableMapContentFingerprint")) != UDigimonVenomNXTMapAssetRevision::ExpectedContentFingerprint)
    { Report = TEXT("The native map registry does not match this runtime release."); return false; }
    TMap<int32, TSharedPtr<FJsonObject>> Registered;
    for (const TSharedPtr<FJsonValue>& V : *Rows)
    {
        if (!V.IsValid() || V->Type != EJson::Object) { Report = TEXT("Invalid native map record."); return false; }
        const int32 Id = static_cast<int32>(Number(V->AsObject(), TEXT("mapId")));
        if (Id < 1 || Id > Rows->Num() || Registered.Contains(Id)) { Report = TEXT("Invalid or duplicate source map identity."); return false; }
        Registered.Add(Id, V->AsObject());
    }
    TSet<int32> Seen;
    bool bPlayerStart = false;
    for (ULevel* Level : World->GetLevels())
        if (Level) for (AActor* Actor : Level->Actors)
        {
            if (!IsValid(Actor) || Actor->IsActorBeingDestroyed()) continue;
            if (const ADigimonVenomNXTMapZone* Zone = Cast<ADigimonVenomNXTMapZone>(Actor))
            {
                const TSharedPtr<FJsonObject>* Row = Registered.Find(Zone->MapId);
                if (!Row || Seen.Contains(Zone->MapId) || Zone->GetRuntimeMapId() != Zone->MapId ||
                    Zone->SourceImageSize != FIntPoint(static_cast<int32>(Number(*Row, TEXT("sourceWidth"))), static_cast<int32>(Number(*Row, TEXT("sourceHeight")))) ||
                    !Zone->SafeSpawnUV.Equals(FVector2D(Number(*Row, TEXT("safeSpawnU")), Number(*Row, TEXT("safeSpawnV"))), .000001))
                { Report = TEXT("PublicWorld has duplicate, missing or stale habitat metadata. Run Create / Repair Main Menu + Public World."); return false; }
                Seen.Add(Zone->MapId);
            }
            else if (const APlayerStart* Start = Cast<APlayerStart>(Actor))
                bPlayerStart |= Start->ActorHasTag(FName(TEXT("DigimonVenomNXT.GeneratedPlayerStart")));
        }
    if (Seen.Num() != Registered.Num() || !bPlayerStart)
    { Report = TEXT("PublicWorld is missing registered map zones or its player start. Run Create / Repair Main Menu + Public World."); return false; }
    const UGameMapsSettings* Maps = GetDefault<UGameMapsSettings>();
    const UDigimonVenomNXTSettings* Settings = GetDefault<UDigimonVenomNXTSettings>();
    const UProjectPackagingSettings* Packaging = GetDefault<UProjectPackagingSettings>();
    if (!Maps || !Settings || !Packaging ||
        FSoftObjectPath(UGameMapsSettings::GetGameDefaultMap()).GetLongPackageName() != MenuPath ||
        Maps->EditorStartupMap.GetLongPackageName() != MenuPath ||
        Maps->GameInstanceClass.ToString() != UDigimonVenomNXTGameInstance::StaticClass()->GetPathName() ||
        Settings->MainMenuMap.GetLongPackageName() != MenuPath || Settings->PublicWorldMap.GetLongPackageName() != WorldPath)
    { Report = TEXT("Effective project startup or travel settings differ from the native worlds. Run Create / Repair Main Menu + Public World."); return false; }
    for (const FString& Path : {MenuPath, WorldPath})
        if (!Packaging->MapsToCook.ContainsByPredicate([&](const FFilePath& P) { return P.FilePath == Path; }))
        { Report = TEXT("A startup world is missing from Maps to Cook. Run Create / Repair Main Menu + Public World."); return false; }
    if (!Packaging->DirectoriesToAlwaysCook.ContainsByPredicate([](const FDirectoryPath& P) { return P.Path == TEXT("/DigimonVenomNXT/Generated"); }))
    { Report = TEXT("Generated content is missing from the cook directories. Run Create / Repair Main Menu + Public World."); return false; }
    if (bRequireImportedContent)
    {
        if (!UDigimonVenomNXTMapAssetRevision::IsInstalledCurrent())
        { Report = TEXT("The startup worlds are prepared, but map content import is incomplete. Run Build Complete Game Content and let all asset stages finish."); return false; }
        for (const TPair<int32, TSharedPtr<FJsonObject>>& Pair : Registered)
            for (const TCHAR* Prefix : {TEXT("SP"), TEXT("T")})
                if (!FPackageName::DoesPackageExist(FString::Printf(TEXT("/DigimonVenomNXT/Generated/Maps/%s_PlayMap_%03d"), Prefix, Pair.Key)))
                { Report = FString::Printf(TEXT("Map %d artwork is missing despite the import marker. Run Build Complete Game Content."), Pair.Key); return false; }
    }
    Report = FString::Printf(TEXT("Verified saved MainMenu/PublicWorld, native game modes, all %d map identities, player start, startup targets and cooking settings.%s"),
        Seen.Num(), bRequireImportedContent ? TEXT(" Current map content is installed.") : TEXT(" Artwork completion is a separate required step."));
    return true;
}

static bool CanRefreshWorldReceipt(FString& Reason)
{
    TSharedPtr<FJsonObject> Receipt, Manifest;
    const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
    FString ManifestHash, RegistryHash;
    if (!LoadJson(ReceiptPath(), Receipt) || Number(Receipt, TEXT("schema")) != 1 ||
        String(Receipt, TEXT("revision")) != TEXT("digimon-venom-nxt-native-1") ||
        !FileSha1(ResourceFile(TEXT("GameData/import_manifest.json")), ManifestHash) ||
        !FileSha1(ResourceFile(TEXT("DigimonMaps.json")), RegistryHash) ||
        String(Receipt, TEXT("manifestSha1")) != ManifestHash || String(Receipt, TEXT("registrySha1")) != RegistryHash ||
        Number(Receipt, TEXT("mapCount")) != UDigimonVenomNXTMapAssetRevision::ExpectedMapCount ||
        !Receipt->TryGetArrayField(TEXT("packages"), Rows) || Number(Receipt, TEXT("expectedPackageCount")) != Rows->Num() ||
        !LoadJson(ResourceFile(TEXT("GameData/import_manifest.json")), Manifest))
    { Reason = TEXT("There is no complete receipt for the current source catalog."); return false; }
    TMap<FString, FString> Recorded;
    for (const TSharedPtr<FJsonValue>& V : *Rows)
    {
        if (!V.IsValid() || V->Type != EJson::Object) { Reason = TEXT("Invalid receipt package record."); return false; }
        const FString Path = String(V->AsObject(), TEXT("packagePath"));
        if (!ValidAssetPath(Path) || Recorded.Contains(Path)) { Reason = TEXT("Invalid or duplicate receipt package path."); return false; }
        Recorded.Add(Path, String(V->AsObject(), TEXT("sha1")));
    }
    TSet<FString> Required;
    for (const TCHAR* Key : {TEXT("textures"), TEXT("sprites"), TEXT("animations"), TEXT("audio"), TEXT("partnerSets"), TEXT("tamerSets")})
    {
        const TArray<TSharedPtr<FJsonValue>>* Assets = nullptr;
        if (!Manifest->TryGetArrayField(Key, Assets)) { Reason = TEXT("Manifest asset group is missing."); return false; }
        for (const TSharedPtr<FJsonValue>& V : *Assets)
        {
            if (!V.IsValid() || V->Type != EJson::Object) { Reason = TEXT("Invalid manifest record."); return false; }
            Required.Add(String(V->AsObject(), TEXT("asset")));
        }
    }
    for (const TCHAR* Path : {TEXT("/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite"), TEXT("/DigimonVenomNXT/Generated/Maps/DA_PlayableMapRevision"),
        TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu"), TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld")}) Required.Add(Path);
    for (const FString& Path : Required)
        if (!Recorded.Contains(Path)) { Reason = TEXT("The previous receipt omits required content: ") + Path; return false; }
    FScopedSlowTask Progress(static_cast<float>(Recorded.Num()), FText::FromString(TEXT("Checking imported packages before repairing the world receipt")));
    if (!IsRunningCommandlet()) Progress.MakeDialog(false);
    for (const TPair<FString, FString>& Pair : Recorded)
    {
        Progress.EnterProgressFrame(1);
        if (Pair.Key == TEXT("/DigimonVenomNXT/Generated/Levels/MainMenu") || Pair.Key == TEXT("/DigimonVenomNXT/Generated/Levels/PublicWorld")) continue;
        FString Hash;
        const FString File = FPackageName::LongPackageNameToFilename(Pair.Key, FPackageName::GetAssetPackageExtension());
        if (!FileSha1(File, Hash) || Hash != Pair.Value)
        { Reason = TEXT("An imported package is missing or changed: ") + Pair.Key; return false; }
    }
    return true;
}

static bool PrepareWorldsInternal(bool bRefreshReceipt, FString& Report)
{
    FString ReceiptReason;
    const bool bHadVerifiedAssets = bRefreshReceipt && CanRefreshWorldReceipt(ReceiptReason);
    if (FPaths::FileExists(ReceiptPath()) && !IFileManager::Get().Delete(*ReceiptPath(), false, true))
    { Report = TEXT("Could not invalidate the previous completion receipt. Check project Intermediate permissions."); return false; }
    FString Step;
    if (!UDigimonVenomNXTEditorLibrary::BuildStarterLevels(false, Report)) return false;
    if (!UDigimonVenomNXTEditorLibrary::ConfigureProjectForDigimonVenomNXT(Step))
    { Report += TEXT("\nStartup configuration incomplete: ") + Step; return false; }
    Report += TEXT("\n") + Step;
    if (!ValidateWorldSetup(false, Step)) { Report += TEXT("\n") + Step; return false; }
    if (bHadVerifiedAssets)
    {
        if (!ValidateWorldSetup(true, Step) || !WriteCompleteReceipt(Step))
        { Report += TEXT("\nWorlds repaired, but content verification failed: ") + Step; return false; }
        Report += TEXT("\nVerified imported content was preserved and its world package hashes were refreshed.");
    }
    else if (bRefreshReceipt)
        Report += TEXT("\nWorld setup succeeded. Full game content is not certified yet: ") + ReceiptReason +
            TEXT(" Run Tools > Digimon Venom NXT: Build Complete Game Content before playing or packaging.");
    return true;
}
}

bool UDigimonVenomNXTEditorLibrary::PrepareGameWorlds(FString& OutReport)
{
    return DigimonVenomNXTEditorInternal::PrepareWorldsInternal(true, OutReport);
}

bool UDigimonVenomNXTEditorLibrary::RepairPackagedStartup(FString& OutReport)
{
    return PrepareGameWorlds(OutReport);
}

bool UDigimonVenomNXTEditorLibrary::ValidateGameWorlds(FString& OutReport)
{
    return DigimonVenomNXTEditorInternal::ValidateWorldSetup(true, OutReport);
}

bool UDigimonVenomNXTEditorLibrary::BuildCompleteGameContent(bool bReplaceExisting, FString& OutReport)
{
    using namespace DigimonVenomNXTEditorInternal;
    FString Step;
    OutReport.Reset();
    UE_LOG(LogTemp, Display, TEXT("Digimon setup 1/4: saving MainMenu, PublicWorld and startup settings."));
    if (!PrepareWorldsInternal(false, OutReport)) return false;
    UE_LOG(LogTemp, Display, TEXT("Digimon setup 2/4: verifying and importing the complete source catalog. Worlds are already saved."));
    if (!ImportManifest(EImportScope::All, bReplaceExisting, Step))
    {
        OutReport += TEXT("\nASSET IMPORT INCOMPLETE\n") + Step +
            TEXT("\nMainMenu and PublicWorld have been saved. Do not package yet. Fix the reported asset issue, then rerun Build Complete Game Content to continue.");
        return false;
    }
    OutReport += TEXT("\n") + Step;
    UE_LOG(LogTemp, Display, TEXT("Digimon setup 3/4: refreshing and validating native world metadata."));
    if (!BuildStarterLevels(false, Step) || !ValidateGameWorlds(Step)) { OutReport += TEXT("\n") + Step; return false; }
    OutReport += TEXT("\n") + Step;
    UE_LOG(LogTemp, Display, TEXT("Digimon setup 4/4: verifying every saved package and recording completion."));
    if (!WriteCompleteReceipt(Step)) { OutReport += TEXT("\n") + Step; return false; }
    OutReport += TEXT("\nComplete-content receipt saved.\nNext: Tools > Digimon Venom NXT: Open Main Menu, then press Play. Create or sign in to an account and choose Host or Join.");
    return true;
}
