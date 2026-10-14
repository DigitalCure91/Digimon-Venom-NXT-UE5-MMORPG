// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTSocialTypes.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTSocialTypes() {}

// ********** Begin Cross Module References ********************************************************
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonChatMessage(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanInvitationRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanInviteView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanMemberRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanMemberView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanView(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialAccountRecord(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialContact(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialDatabase(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialState(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EDigimonClanRole **********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole_Statics
template<> DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonClanRole>()
{
	return Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Leader.Name", "EDigimonClanRole::Leader" },
		{ "Member.Name", "EDigimonClanRole::Member" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
		{ "None.Name", "EDigimonClanRole::None" },
		{ "Officer.Name", "EDigimonClanRole::Officer" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDigimonClanRole::None", (int64)EDigimonClanRole::None },
		{ "EDigimonClanRole::Member", (int64)EDigimonClanRole::Member },
		{ "EDigimonClanRole::Officer", (int64)EDigimonClanRole::Officer },
		{ "EDigimonClanRole::Leader", (int64)EDigimonClanRole::Leader },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	"EDigimonClanRole",
	"EDigimonClanRole",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EDigimonClanRole;
UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EDigimonClanRole.OuterSingleton)
		{
			ZRIE_EDigimonClanRole.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("EDigimonClanRole"));
		}
		return ZRIE_EDigimonClanRole.OuterSingleton;
	}
	if (!ZRIE_EDigimonClanRole.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EDigimonClanRole.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EDigimonClanRole.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EDigimonClanRole ************************************************************

// ********** Begin Enum EDigimonSocialAction ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction_Statics
template<> DIGIMONVENOMNXTRUNTIME_NON_ATTRIBUTED_API UEnum* StaticEnum<EDigimonSocialAction>()
{
	return Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ClanAccept.Name", "EDigimonSocialAction::ClanAccept" },
		{ "ClanCreate.Name", "EDigimonSocialAction::ClanCreate" },
		{ "ClanDecline.Name", "EDigimonSocialAction::ClanDecline" },
		{ "ClanDemote.Name", "EDigimonSocialAction::ClanDemote" },
		{ "ClanDisband.Name", "EDigimonSocialAction::ClanDisband" },
		{ "ClanInvite.Name", "EDigimonSocialAction::ClanInvite" },
		{ "ClanKick.Name", "EDigimonSocialAction::ClanKick" },
		{ "ClanLeave.Name", "EDigimonSocialAction::ClanLeave" },
		{ "ClanPromote.Name", "EDigimonSocialAction::ClanPromote" },
		{ "ClanTransfer.Name", "EDigimonSocialAction::ClanTransfer" },
		{ "ClanUpdate.Name", "EDigimonSocialAction::ClanUpdate" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target is an account username/ID unless documented otherwise in SocialComponent. */" },
#endif
		{ "FriendAccept.Name", "EDigimonSocialAction::FriendAccept" },
		{ "FriendCancel.Name", "EDigimonSocialAction::FriendCancel" },
		{ "FriendDecline.Name", "EDigimonSocialAction::FriendDecline" },
		{ "FriendRemove.Name", "EDigimonSocialAction::FriendRemove" },
		{ "FriendRequest.Name", "EDigimonSocialAction::FriendRequest" },
		{ "IgnoreAdd.Name", "EDigimonSocialAction::IgnoreAdd" },
		{ "IgnoreRemove.Name", "EDigimonSocialAction::IgnoreRemove" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target is an account username/ID unless documented otherwise in SocialComponent." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDigimonSocialAction::FriendRequest", (int64)EDigimonSocialAction::FriendRequest },
		{ "EDigimonSocialAction::FriendAccept", (int64)EDigimonSocialAction::FriendAccept },
		{ "EDigimonSocialAction::FriendDecline", (int64)EDigimonSocialAction::FriendDecline },
		{ "EDigimonSocialAction::FriendRemove", (int64)EDigimonSocialAction::FriendRemove },
		{ "EDigimonSocialAction::FriendCancel", (int64)EDigimonSocialAction::FriendCancel },
		{ "EDigimonSocialAction::IgnoreAdd", (int64)EDigimonSocialAction::IgnoreAdd },
		{ "EDigimonSocialAction::IgnoreRemove", (int64)EDigimonSocialAction::IgnoreRemove },
		{ "EDigimonSocialAction::ClanCreate", (int64)EDigimonSocialAction::ClanCreate },
		{ "EDigimonSocialAction::ClanDisband", (int64)EDigimonSocialAction::ClanDisband },
		{ "EDigimonSocialAction::ClanInvite", (int64)EDigimonSocialAction::ClanInvite },
		{ "EDigimonSocialAction::ClanAccept", (int64)EDigimonSocialAction::ClanAccept },
		{ "EDigimonSocialAction::ClanDecline", (int64)EDigimonSocialAction::ClanDecline },
		{ "EDigimonSocialAction::ClanLeave", (int64)EDigimonSocialAction::ClanLeave },
		{ "EDigimonSocialAction::ClanKick", (int64)EDigimonSocialAction::ClanKick },
		{ "EDigimonSocialAction::ClanPromote", (int64)EDigimonSocialAction::ClanPromote },
		{ "EDigimonSocialAction::ClanDemote", (int64)EDigimonSocialAction::ClanDemote },
		{ "EDigimonSocialAction::ClanTransfer", (int64)EDigimonSocialAction::ClanTransfer },
		{ "EDigimonSocialAction::ClanUpdate", (int64)EDigimonSocialAction::ClanUpdate },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	"EDigimonSocialAction",
	"EDigimonSocialAction",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EDigimonSocialAction;
UEnum* Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EDigimonSocialAction.OuterSingleton)
		{
			ZRIE_EDigimonSocialAction.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("EDigimonSocialAction"));
		}
		return ZRIE_EDigimonSocialAction.OuterSingleton;
	}
	if (!ZRIE_EDigimonSocialAction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EDigimonSocialAction.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EDigimonSocialAction.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EDigimonSocialAction ********************************************************

// ********** Begin ScriptStruct FDigimonSocialContact *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSocialContact_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSocialContact>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSocialContact); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOnline_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeadLevel_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeadSpeciesId_MetaData[] = {
		{ "Category", "DigimonSocialContact" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSocialContact constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static void NewProp_bOnline_SetBit(void* Obj)
	{
		((FDigimonSocialContact*)Obj)->bOnline = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOnline;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Location;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LeadLevel;
	static const UECodeGen_Private::FNamePropertyParams NewProp_LeadSpeciesId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSocialContact constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSocialContact>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSocialContact Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialContact, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialContact, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOnline = { "bOnline", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialContact), &UHT_STATICS::NewProp_bOnline_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOnline_MetaData), NewProp_bOnline_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialContact, Location), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_LeadLevel = { "LeadLevel", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialContact, LeadLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeadLevel_MetaData), NewProp_LeadLevel_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LeadSpeciesId = { "LeadSpeciesId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialContact, LeadSpeciesId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeadSpeciesId_MetaData), NewProp_LeadSpeciesId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOnline,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LeadLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LeadSpeciesId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSocialContact Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSocialContact",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSocialContact>(),
	alignof(FDigimonSocialContact),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSocialContact;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialContact(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSocialContact.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSocialContact.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSocialContact, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSocialContact"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSocialContact.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSocialContact.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSocialContact.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSocialContact.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSocialContact ***********************************************

// ********** Begin ScriptStruct FDigimonClanMemberView ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanMemberView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanMemberView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanMemberView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Player_MetaData[] = {
		{ "Category", "DigimonClanMemberView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "DigimonClanMemberView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JoinedUnix_MetaData[] = {
		{ "Category", "DigimonClanMemberView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanMemberView constinit property declarations ************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Player;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_JoinedUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanMemberView constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanMemberView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanMemberView Property Definitions ***********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberView, Player), Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Player_MetaData), NewProp_Player_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberView, Role), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // 7f8b13eb99d5631eabd59c702d03f61e42ad8c3f
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_JoinedUnix = { "JoinedUnix", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberView, JoinedUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JoinedUnix_MetaData), NewProp_JoinedUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JoinedUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanMemberView Property Definitions *************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanMemberView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanMemberView>(),
	alignof(FDigimonClanMemberView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanMemberView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanMemberView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanMemberView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanMemberView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanMemberView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanMemberView **********************************************

// ********** Begin ScriptStruct FDigimonClanInviteView ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanInviteView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanInviteView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanInviteView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanId_MetaData[] = {
		{ "Category", "DigimonClanInviteView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanName_MetaData[] = {
		{ "Category", "DigimonClanInviteView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InviterName_MetaData[] = {
		{ "Category", "DigimonClanInviteView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpiresUnix_MetaData[] = {
		{ "Category", "DigimonClanInviteView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanInviteView constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InviterName;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_ExpiresUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanInviteView constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanInviteView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanInviteView Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanId = { "ClanId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInviteView, ClanId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanId_MetaData), NewProp_ClanId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanName = { "ClanName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInviteView, ClanName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanName_MetaData), NewProp_ClanName_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_InviterName = { "InviterName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInviteView, InviterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InviterName_MetaData), NewProp_InviterName_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_ExpiresUnix = { "ExpiresUnix", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInviteView, ExpiresUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpiresUnix_MetaData), NewProp_ExpiresUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InviterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExpiresUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanInviteView Property Definitions *************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanInviteView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanInviteView>(),
	alignof(FDigimonClanInviteView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanInviteView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanInviteView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanInviteView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanInviteView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanInviteView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanInviteView **********************************************

// ********** Begin ScriptStruct FDigimonClanView **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanView_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanView>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanView); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanId_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tag_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageOfTheDay_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_YourRole_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Members_MetaData[] = {
		{ "Category", "DigimonClanView" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanView constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Tag;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MessageOfTheDay;
	static const UECodeGen_Private::FBytePropertyParams NewProp_YourRole_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_YourRole;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Members_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Members;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanView constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanView>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanView Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanId = { "ClanId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, ClanId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanId_MetaData), NewProp_ClanId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, Tag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tag_MetaData), NewProp_Tag_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_MessageOfTheDay = { "MessageOfTheDay", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, MessageOfTheDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageOfTheDay_MetaData), NewProp_MessageOfTheDay_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_YourRole_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_YourRole = { "YourRole", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, YourRole), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_YourRole_MetaData), NewProp_YourRole_MetaData) }; // 7f8b13eb99d5631eabd59c702d03f61e42ad8c3f
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Members_Inner = { "Members", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonClanMemberView, METADATA_PARAMS(0, nullptr) }; // 85ee8de9344f820db23d1b9d3e8d4b8dc1a9d568
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Members = { "Members", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanView, Members), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Members_MetaData), NewProp_Members_MetaData) }; // 85ee8de9344f820db23d1b9d3e8d4b8dc1a9d568
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MessageOfTheDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_YourRole_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_YourRole,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Members_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Members,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanView Property Definitions *******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanView",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanView>(),
	alignof(FDigimonClanView),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanView;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanView(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanView.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanView.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanView, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanView"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanView.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanView.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanView.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanView.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanView ****************************************************

// ********** Begin ScriptStruct FDigimonSocialPlayerInfo ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSocialPlayerInfo>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSocialPlayerInfo); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Explicitly public information; never a copy of another account's private profile. */" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Explicitly public information; never a copy of another account's private profile." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bValid_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Player_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EquippedTitle_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUnrankedStatsAvailable_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnrankedWins_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnrankedLosses_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnrankedDraws_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanName_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanTag_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanRole_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFriend_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIgnored_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIncomingRequest_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOutgoingRequest_MetaData[] = {
		{ "Category", "DigimonSocialPlayerInfo" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSocialPlayerInfo constinit property declarations **********
	static void NewProp_bValid_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bValid = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bValid;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Player;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EquippedTitle;
	static void NewProp_bUnrankedStatsAvailable_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bUnrankedStatsAvailable = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUnrankedStatsAvailable;
	static const UECodeGen_Private::FIntPropertyParams NewProp_UnrankedWins;
	static const UECodeGen_Private::FIntPropertyParams NewProp_UnrankedLosses;
	static const UECodeGen_Private::FIntPropertyParams NewProp_UnrankedDraws;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanTag;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ClanRole_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ClanRole;
	static void NewProp_bFriend_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bFriend = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFriend;
	static void NewProp_bIgnored_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bIgnored = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIgnored;
	static void NewProp_bIncomingRequest_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bIncomingRequest = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncomingRequest;
	static void NewProp_bOutgoingRequest_SetBit(void* Obj)
	{
		((FDigimonSocialPlayerInfo*)Obj)->bOutgoingRequest = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOutgoingRequest;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSocialPlayerInfo constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSocialPlayerInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSocialPlayerInfo Property Definitions *********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bValid = { "bValid", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bValid_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bValid_MetaData), NewProp_bValid_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, Player), Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Player_MetaData), NewProp_Player_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_EquippedTitle = { "EquippedTitle", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, EquippedTitle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EquippedTitle_MetaData), NewProp_EquippedTitle_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bUnrankedStatsAvailable = { "bUnrankedStatsAvailable", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bUnrankedStatsAvailable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUnrankedStatsAvailable_MetaData), NewProp_bUnrankedStatsAvailable_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_UnrankedWins = { "UnrankedWins", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, UnrankedWins), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnrankedWins_MetaData), NewProp_UnrankedWins_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_UnrankedLosses = { "UnrankedLosses", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, UnrankedLosses), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnrankedLosses_MetaData), NewProp_UnrankedLosses_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_UnrankedDraws = { "UnrankedDraws", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, UnrankedDraws), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnrankedDraws_MetaData), NewProp_UnrankedDraws_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanName = { "ClanName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, ClanName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanName_MetaData), NewProp_ClanName_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanTag = { "ClanTag", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, ClanTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanTag_MetaData), NewProp_ClanTag_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ClanRole_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ClanRole = { "ClanRole", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialPlayerInfo, ClanRole), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanRole_MetaData), NewProp_ClanRole_MetaData) }; // 7f8b13eb99d5631eabd59c702d03f61e42ad8c3f
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bFriend = { "bFriend", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bFriend_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFriend_MetaData), NewProp_bFriend_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIgnored = { "bIgnored", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bIgnored_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIgnored_MetaData), NewProp_bIgnored_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIncomingRequest = { "bIncomingRequest", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bIncomingRequest_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIncomingRequest_MetaData), NewProp_bIncomingRequest_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOutgoingRequest = { "bOutgoingRequest", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialPlayerInfo), &UHT_STATICS::NewProp_bOutgoingRequest_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOutgoingRequest_MetaData), NewProp_bOutgoingRequest_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bValid,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EquippedTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bUnrankedStatsAvailable,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnrankedWins,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnrankedLosses,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UnrankedDraws,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanRole_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanRole,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bFriend,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIgnored,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIncomingRequest,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOutgoingRequest,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSocialPlayerInfo Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSocialPlayerInfo",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSocialPlayerInfo>(),
	alignof(FDigimonSocialPlayerInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSocialPlayerInfo"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSocialPlayerInfo ********************************************

// ********** Begin ScriptStruct FDigimonSocialState ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSocialState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSocialState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSocialState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bReady_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Friends_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Ignored_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingFriends_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutgoingFriends_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Clan_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanInvites_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanChat_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerInfo_MetaData[] = {
		{ "Category", "DigimonSocialState" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSocialState constinit property declarations ***************
	static void NewProp_bReady_SetBit(void* Obj)
	{
		((FDigimonSocialState*)Obj)->bReady = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReady;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Friends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Friends;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Ignored_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Ignored;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IncomingFriends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_IncomingFriends;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutgoingFriends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutgoingFriends;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Clan;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClanInvites_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ClanInvites;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClanChat_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ClanChat;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlayerInfo;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSocialState constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSocialState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSocialState Property Definitions **************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bReady = { "bReady", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FDigimonSocialState), &UHT_STATICS::NewProp_bReady_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bReady_MetaData), NewProp_bReady_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Friends_Inner = { "Friends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(0, nullptr) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Friends = { "Friends", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, Friends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Friends_MetaData), NewProp_Friends_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Ignored_Inner = { "Ignored", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(0, nullptr) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Ignored = { "Ignored", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, Ignored), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Ignored_MetaData), NewProp_Ignored_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_IncomingFriends_Inner = { "IncomingFriends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(0, nullptr) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_IncomingFriends = { "IncomingFriends", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, IncomingFriends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingFriends_MetaData), NewProp_IncomingFriends_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutgoingFriends_Inner = { "OutgoingFriends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSocialContact, METADATA_PARAMS(0, nullptr) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutgoingFriends = { "OutgoingFriends", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, OutgoingFriends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutgoingFriends_MetaData), NewProp_OutgoingFriends_MetaData) }; // b753d686038f32bb7cad0f016c975ad3b07cec93
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Clan = { "Clan", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, Clan), Z_Construct_UScriptStruct_FDigimonClanView, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Clan_MetaData), NewProp_Clan_MetaData) }; // 171288c7cbfd54a825acef14c65f68499658729e
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ClanInvites_Inner = { "ClanInvites", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonClanInviteView, METADATA_PARAMS(0, nullptr) }; // 5bd58ae7a768a0c605ef9b7e0b885542dc35586e
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ClanInvites = { "ClanInvites", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, ClanInvites), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanInvites_MetaData), NewProp_ClanInvites_MetaData) }; // 5bd58ae7a768a0c605ef9b7e0b885542dc35586e
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ClanChat_Inner = { "ClanChat", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonChatMessage, METADATA_PARAMS(0, nullptr) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ClanChat = { "ClanChat", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, ClanChat), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanChat_MetaData), NewProp_ClanChat_MetaData) }; // 1d3d456acbdf556a1bcde05103f2bb92764853b4
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PlayerInfo = { "PlayerInfo", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialState, PlayerInfo), Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerInfo_MetaData), NewProp_PlayerInfo_MetaData) }; // 7f415071d0c62585e4c1669fae4df784ee845f10
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Friends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Friends,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Ignored_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Ignored,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IncomingFriends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IncomingFriends,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutgoingFriends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutgoingFriends,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Clan,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanInvites_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanInvites,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanChat_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanChat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerInfo,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSocialState Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSocialState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSocialState>(),
	alignof(FDigimonSocialState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSocialState;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSocialState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSocialState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSocialState, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSocialState"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSocialState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSocialState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSocialState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSocialState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSocialState *************************************************

// ********** Begin ScriptStruct FDigimonSocialAccountRecord ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSocialAccountRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSocialAccountRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSocialAccountRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Durable server records. These are never replicated directly to clients.\n" },
#endif
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Durable server records. These are never replicated directly to clients." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Friends_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Ignored_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingFriends_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutgoingFriends_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSocialAccountRecord constinit property declarations *******
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Friends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Friends;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Ignored_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Ignored;
	static const UECodeGen_Private::FStrPropertyParams NewProp_IncomingFriends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_IncomingFriends;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutgoingFriends_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutgoingFriends;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSocialAccountRecord constinit property declarations *********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSocialAccountRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSocialAccountRecord Property Definitions ******************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, Username), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Username_MetaData), NewProp_Username_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Friends_Inner = { "Friends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Friends = { "Friends", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, Friends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Friends_MetaData), NewProp_Friends_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Ignored_Inner = { "Ignored", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Ignored = { "Ignored", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, Ignored), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Ignored_MetaData), NewProp_Ignored_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_IncomingFriends_Inner = { "IncomingFriends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_IncomingFriends = { "IncomingFriends", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, IncomingFriends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingFriends_MetaData), NewProp_IncomingFriends_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_OutgoingFriends_Inner = { "OutgoingFriends", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutgoingFriends = { "OutgoingFriends", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialAccountRecord, OutgoingFriends), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutgoingFriends_MetaData), NewProp_OutgoingFriends_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Username,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Friends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Friends,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Ignored_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Ignored,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IncomingFriends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IncomingFriends,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutgoingFriends_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutgoingFriends,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSocialAccountRecord Property Definitions ********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSocialAccountRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSocialAccountRecord>(),
	alignof(FDigimonSocialAccountRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialAccountRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSocialAccountRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSocialAccountRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSocialAccountRecord *****************************************

// ********** Begin ScriptStruct FDigimonClanMemberRecord ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanMemberRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanMemberRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanMemberRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JoinedUnix_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanMemberRecord constinit property declarations **********
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_JoinedUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanMemberRecord constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanMemberRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanMemberRecord Property Definitions *********************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberRecord, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberRecord, Role), Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // 7f8b13eb99d5631eabd59c702d03f61e42ad8c3f
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_JoinedUnix = { "JoinedUnix", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanMemberRecord, JoinedUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JoinedUnix_MetaData), NewProp_JoinedUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JoinedUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanMemberRecord Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanMemberRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanMemberRecord>(),
	alignof(FDigimonClanMemberRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanMemberRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanMemberRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanMemberRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanMemberRecord ********************************************

// ********** Begin ScriptStruct FDigimonClanInvitationRecord **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanInvitationRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanInvitationRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanInvitationRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccountId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InviterAccountId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpiresUnix_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanInvitationRecord constinit property declarations ******
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccountId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InviterAccountId;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_ExpiresUnix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanInvitationRecord constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanInvitationRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanInvitationRecord Property Definitions *****************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_AccountId = { "AccountId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInvitationRecord, AccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccountId_MetaData), NewProp_AccountId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_InviterAccountId = { "InviterAccountId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInvitationRecord, InviterAccountId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InviterAccountId_MetaData), NewProp_InviterAccountId_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_ExpiresUnix = { "ExpiresUnix", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanInvitationRecord, ExpiresUnix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpiresUnix_MetaData), NewProp_ExpiresUnix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InviterAccountId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExpiresUnix,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanInvitationRecord Property Definitions *******************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanInvitationRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanInvitationRecord>(),
	alignof(FDigimonClanInvitationRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanInvitationRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanInvitationRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanInvitationRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanInvitationRecord ****************************************

// ********** Begin ScriptStruct FDigimonClanRecord ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonClanRecord_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonClanRecord>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonClanRecord); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClanId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tag_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageOfTheDay_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Members_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Invitations_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonClanRecord constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClanId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Tag;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MessageOfTheDay;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Members_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Members;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Invitations_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Invitations;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonClanRecord constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonClanRecord>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonClanRecord Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ClanId = { "ClanId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, ClanId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClanId_MetaData), NewProp_ClanId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, Tag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tag_MetaData), NewProp_Tag_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_MessageOfTheDay = { "MessageOfTheDay", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, MessageOfTheDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageOfTheDay_MetaData), NewProp_MessageOfTheDay_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Members_Inner = { "Members", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonClanMemberRecord, METADATA_PARAMS(0, nullptr) }; // 89e1d92ba81813d79f006a2284e91bafcaadb1d7
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Members = { "Members", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, Members), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Members_MetaData), NewProp_Members_MetaData) }; // 89e1d92ba81813d79f006a2284e91bafcaadb1d7
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Invitations_Inner = { "Invitations", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonClanInvitationRecord, METADATA_PARAMS(0, nullptr) }; // 7bd415faafa264f6c114dc56ebbc8bc38cccf2cb
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Invitations = { "Invitations", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonClanRecord, Invitations), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Invitations_MetaData), NewProp_Invitations_MetaData) }; // 7bd415faafa264f6c114dc56ebbc8bc38cccf2cb
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClanId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MessageOfTheDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Members_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Members,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Invitations_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Invitations,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonClanRecord Property Definitions *****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonClanRecord",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonClanRecord>(),
	alignof(FDigimonClanRecord),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonClanRecord;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonClanRecord(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonClanRecord.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonClanRecord.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonClanRecord, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonClanRecord"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonClanRecord.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonClanRecord.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonClanRecord.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonClanRecord.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonClanRecord **************************************************

// ********** Begin ScriptStruct FDigimonSocialDatabase ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FDigimonSocialDatabase_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FDigimonSocialDatabase>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDigimonSocialDatabase); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SchemaVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Revision_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Accounts_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Clans_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTSocialTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDigimonSocialDatabase constinit property declarations ************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SchemaVersion;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Revision;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Accounts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Accounts;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Clans_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Clans;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDigimonSocialDatabase constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDigimonSocialDatabase>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FDigimonSocialDatabase Property Definitions ***********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SchemaVersion = { "SchemaVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialDatabase, SchemaVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SchemaVersion_MetaData), NewProp_SchemaVersion_MetaData) };
const UECodeGen_Private::FInt64PropertyParams UHT_STATICS::NewProp_Revision = { "Revision", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int64, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialDatabase, Revision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Revision_MetaData), NewProp_Revision_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Accounts_Inner = { "Accounts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonSocialAccountRecord, METADATA_PARAMS(0, nullptr) }; // 4f4823bd09cb8d83824d4c42ba4f125869376fc8
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Accounts = { "Accounts", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialDatabase, Accounts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Accounts_MetaData), NewProp_Accounts_MetaData) }; // 4f4823bd09cb8d83824d4c42ba4f125869376fc8
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Clans_Inner = { "Clans", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDigimonClanRecord, METADATA_PARAMS(0, nullptr) }; // be06f5825ad44ea414330bca8446f04494e2211a
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Clans = { "Clans", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FDigimonSocialDatabase, Clans), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Clans_MetaData), NewProp_Clans_MetaData) }; // be06f5825ad44ea414330bca8446f04494e2211a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SchemaVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Revision,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accounts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Clans_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Clans,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FDigimonSocialDatabase Property Definitions *************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
	nullptr,
	&NewStructOps,
	"DigimonSocialDatabase",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FDigimonSocialDatabase>(),
	alignof(FDigimonSocialDatabase),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase;
UScriptStruct* Z_Construct_UScriptStruct_FDigimonSocialDatabase(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDigimonSocialDatabase, (UObject*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase::Outer), TEXT("DigimonSocialDatabase"));
		}
		return Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FDigimonSocialDatabase **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialTypes_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonClanRole, TEXT("EDigimonClanRole"), &ZRIE_EDigimonClanRole, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2139821035U) },
		{ Z_Construct_UEnum_DigimonVenomNXTRuntime_EDigimonSocialAction, TEXT("EDigimonSocialAction"), &ZRIE_EDigimonSocialAction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1624482475U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FDigimonSocialContact, Z_Construct_UScriptStruct_FDigimonSocialContact_Statics::NewStructOps, TEXT("DigimonSocialContact"),&Z_Registration_Info_UScriptStruct_FDigimonSocialContact, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSocialContact), 3075724934U) },
		{ Z_Construct_UScriptStruct_FDigimonClanMemberView, Z_Construct_UScriptStruct_FDigimonClanMemberView_Statics::NewStructOps, TEXT("DigimonClanMemberView"),&Z_Registration_Info_UScriptStruct_FDigimonClanMemberView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanMemberView), 2247003625U) },
		{ Z_Construct_UScriptStruct_FDigimonClanInviteView, Z_Construct_UScriptStruct_FDigimonClanInviteView_Statics::NewStructOps, TEXT("DigimonClanInviteView"),&Z_Registration_Info_UScriptStruct_FDigimonClanInviteView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanInviteView), 1540721383U) },
		{ Z_Construct_UScriptStruct_FDigimonClanView, Z_Construct_UScriptStruct_FDigimonClanView_Statics::NewStructOps, TEXT("DigimonClanView"),&Z_Registration_Info_UScriptStruct_FDigimonClanView, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanView), 387090631U) },
		{ Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo, Z_Construct_UScriptStruct_FDigimonSocialPlayerInfo_Statics::NewStructOps, TEXT("DigimonSocialPlayerInfo"),&Z_Registration_Info_UScriptStruct_FDigimonSocialPlayerInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSocialPlayerInfo), 2134986865U) },
		{ Z_Construct_UScriptStruct_FDigimonSocialState, Z_Construct_UScriptStruct_FDigimonSocialState_Statics::NewStructOps, TEXT("DigimonSocialState"),&Z_Registration_Info_UScriptStruct_FDigimonSocialState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSocialState), 1509421825U) },
		{ Z_Construct_UScriptStruct_FDigimonSocialAccountRecord, Z_Construct_UScriptStruct_FDigimonSocialAccountRecord_Statics::NewStructOps, TEXT("DigimonSocialAccountRecord"),&Z_Registration_Info_UScriptStruct_FDigimonSocialAccountRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSocialAccountRecord), 1330127805U) },
		{ Z_Construct_UScriptStruct_FDigimonClanMemberRecord, Z_Construct_UScriptStruct_FDigimonClanMemberRecord_Statics::NewStructOps, TEXT("DigimonClanMemberRecord"),&Z_Registration_Info_UScriptStruct_FDigimonClanMemberRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanMemberRecord), 2313279787U) },
		{ Z_Construct_UScriptStruct_FDigimonClanInvitationRecord, Z_Construct_UScriptStruct_FDigimonClanInvitationRecord_Statics::NewStructOps, TEXT("DigimonClanInvitationRecord"),&Z_Registration_Info_UScriptStruct_FDigimonClanInvitationRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanInvitationRecord), 2077496826U) },
		{ Z_Construct_UScriptStruct_FDigimonClanRecord, Z_Construct_UScriptStruct_FDigimonClanRecord_Statics::NewStructOps, TEXT("DigimonClanRecord"),&Z_Registration_Info_UScriptStruct_FDigimonClanRecord, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonClanRecord), 3188127106U) },
		{ Z_Construct_UScriptStruct_FDigimonSocialDatabase, Z_Construct_UScriptStruct_FDigimonSocialDatabase_Statics::NewStructOps, TEXT("DigimonSocialDatabase"),&Z_Registration_Info_UScriptStruct_FDigimonSocialDatabase, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDigimonSocialDatabase), 1428781511U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTSocialTypes_h__Script_DigimonVenomNXTRuntime_637967cbad4bbbf78bde07f818802daeffcaadb5{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
