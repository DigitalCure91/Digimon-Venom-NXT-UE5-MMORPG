#include "DigimonVenomNXTPresentationAssets.h"

#include "Engine/Texture2D.h"

namespace DigimonVenomNXTPresentationAssets
{
    namespace
    {
        const FRegistration CommunityRegistrations[] = {
            { TEXT("CommunityHero"), TEXT("assets/ui/extracted/dawn_tamer_boy.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_TamerBoy.T_DVN_TamerBoy") },
            { TEXT("ClansHero"), TEXT("assets/ui/extracted/dawn_tamer_girl.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_TamerGirl.T_DVN_TamerGirl") },
            { TEXT("TradingHero"), TEXT("assets/ui/extracted/shopkeeper.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_Shopkeeper.T_DVN_Shopkeeper") }
        };
        const FRegistration Registrations[] = {
            { TEXT("DigiLabHero"), TEXT("assets/ui/dawn/m_labo_bg.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_DigiLab.T_DVN_DigiLab") },
            { TEXT("hp_s"), TEXT("assets/ui/extracted/hp_max_capsule.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_HPCapsule.T_DVN_HPCapsule") },
            { TEXT("sp_s"), TEXT("assets/ui/extracted/mp_max_capsule.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_SPCapsule.T_DVN_SPCapsule") },
            { TEXT("DigiMeat"), TEXT("assets/ui/digifarm/digimeat.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_DigiMeat.T_DVN_DigiMeat") },
            { TEXT("TitleCoronamon"), TEXT("assets/ui/extracted/coronamon_title.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_TitleCoronamon.T_DVN_TitleCoronamon") },
            { TEXT("TitleLunamon"), TEXT("assets/ui/extracted/lunamon_title.png"), TEXT("/DigimonVenomNXT/Generated/UI/Presentation/T_DVN_TitleLunamon.T_DVN_TitleLunamon") }
        };
    }

    TConstArrayView<FRegistration> AllAssets()
    {
        return MakeArrayView(Registrations);
    }

    TConstArrayView<FRegistration> CommunityAssets()
    {
        return MakeArrayView(CommunityRegistrations);
    }

    const TCHAR* ObjectPath(FName Key)
    {
        for (const FRegistration& Entry : CommunityRegistrations)
            if (Key == FName(Entry.Key)) return Entry.TexturePath;
        for (const FRegistration& Entry : Registrations)
            if (Key == FName(Entry.Key)) return Entry.TexturePath;
        return nullptr;
    }

    UTexture2D* LoadTexture(FName Key)
    {
        if (IsRunningDedicatedServer()) return nullptr;
        const TCHAR* Path = ObjectPath(Key);
        if (!Path) return nullptr;
        static TMap<FName, TWeakObjectPtr<UTexture2D>> Cache;
        if (const TWeakObjectPtr<UTexture2D>* Existing = Cache.Find(Key))
            if (Existing->IsValid()) return Existing->Get();
        UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, Path, nullptr, LOAD_NoWarn | LOAD_Quiet);
        if (Texture) Cache.Add(Key, Texture);
        return Texture;
    }

    UTexture2D* ItemTexture(FName ItemId)
    {
        const FString Id = ItemId.ToString();
        if (Id.StartsWith(TEXT("hp_"))) return LoadTexture(TEXT("hp_s"));
        if (Id.StartsWith(TEXT("sp_"))) return LoadTexture(TEXT("sp_s"));
        if (Id.StartsWith(TEXT("digimeat_"))) return LoadTexture(TEXT("DigiMeat"));
        return nullptr;
    }

}
