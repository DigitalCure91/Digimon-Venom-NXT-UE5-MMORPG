// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DigimonVenomNXTMainMenuWidget.h"
#include "DigimonVenomNXTTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDigimonVenomNXTMainMenuWidget() {}

// ********** Begin Cross Module References ********************************************************
COMMONUI_API UClass* Z_Construct_UClass_UCommonActivatableWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UButton(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UEditableTextBox(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UTextBlock(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidget(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DigimonVenomNXTRuntime(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FDigimonAuthResult(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget(ETypeConstructPhase);
DIGIMONVENOMNXTRUNTIME_API UClass* Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleAuthResult *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleAuthResult_Statics
struct UHT_STATICS
{
	struct DigimonVenomNXTMainMenuWidget_eventHandleAuthResult_Parms
	{
		FDigimonAuthResult Result;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleAuthResult constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Result;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleAuthResult constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleAuthResult Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DigimonVenomNXTMainMenuWidget_eventHandleAuthResult_Parms, Result), Z_Construct_UScriptStruct_FDigimonAuthResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Result_MetaData), NewProp_Result_MetaData) }; // f3e13be835c9c5fbfe44ef4e4e4b443b7b7ec2b6
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Result,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAuthResult Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleAuthResult", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DigimonVenomNXTMainMenuWidget_eventHandleAuthResult_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DigimonVenomNXTMainMenuWidget_eventHandleAuthResult_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleAuthResult(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleAuthResult)
{
	P_GET_STRUCT_REF(FDigimonAuthResult,Z_Param_Out_Result);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAuthResult(Z_Param_Out_Result);
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleAuthResult *******************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleCloseVideo *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCloseVideo_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCloseVideo constinit property declarations **********************
// ********** End Function HandleCloseVideo constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleCloseVideo", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCloseVideo(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleCloseVideo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCloseVideo();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleCloseVideo *******************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleCreateAccount **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCreateAccount_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleCreateAccount constinit property declarations *******************
// ********** End Function HandleCreateAccount constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleCreateAccount", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCreateAccount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleCreateAccount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCreateAccount();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleCreateAccount ****************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleExitGame *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleExitGame_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleExitGame constinit property declarations ************************
// ********** End Function HandleExitGame constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleExitGame", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleExitGame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleExitGame)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleExitGame();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleExitGame *********************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleHost ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleHost_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleHost constinit property declarations ****************************
// ********** End Function HandleHost constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleHost", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleHost(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleHost)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleHost();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleHost *************************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleJoin ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleJoin_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleJoin constinit property declarations ****************************
// ********** End Function HandleJoin constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleJoin", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleJoin(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleJoin)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleJoin();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleJoin *************************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleLogin **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogin_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleLogin constinit property declarations ***************************
// ********** End Function HandleLogin constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleLogin", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogin(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleLogin)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleLogin();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleLogin ************************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleLogout *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogout_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleLogout constinit property declarations **************************
// ********** End Function HandleLogout constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleLogout", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogout(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleLogout)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleLogout();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleLogout ***********************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function HandleOpenVideo ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleOpenVideo_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleOpenVideo constinit property declarations ***********************
// ********** End Function HandleOpenVideo constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "HandleOpenVideo", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleOpenVideo(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execHandleOpenVideo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleOpenVideo();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function HandleOpenVideo ********************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function ShowAuthentication ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowAuthentication_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Main Menu" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowAuthentication constinit property declarations ********************
// ********** End Function ShowAuthentication constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "ShowAuthentication", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowAuthentication(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execShowAuthentication)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowAuthentication();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function ShowAuthentication *****************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Function ShowServerPage *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowServerPage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Digimon Venom NXT|Main Menu" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowServerPage constinit property declarations ************************
// ********** End Function ShowServerPage constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, nullptr, "ShowServerPage", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowServerPage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDigimonVenomNXTMainMenuWidget::execShowServerPage)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowServerPage();
	P_NATIVE_END;
}
// ********** End Class UDigimonVenomNXTMainMenuWidget Function ShowServerPage *********************

// ********** Begin Class UDigimonVenomNXTMainMenuWidget *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fully native login/create-account and public join/admin-host menu. No join password exists. */" },
#endif
		{ "IncludePath", "DigimonVenomNXTMainMenuWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fully native login/create-account and public join/admin-host menu. No join password exists." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PageSwitcher_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UsernameInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PasswordInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdminPasswordInput_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AuthStatusText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerStatusText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WelcomeText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConnectionText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HostInfoText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JoinWorldButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoginSurface_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VideoSurface_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VideoMenuButton_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VideoSettings_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DigimonVenomNXTMainMenuWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDigimonVenomNXTMainMenuWidget constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PageSwitcher;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UsernameInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PasswordInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AdminPasswordInput;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AuthStatusText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ServerStatusText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WelcomeText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ConnectionText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HostInfoText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JoinWorldButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoginSurface;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VideoSurface;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VideoMenuButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VideoSettings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDigimonVenomNXTMainMenuWidget constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleAuthResult"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleAuthResult },
		{ .NameUTF8 = UTF8TEXT("HandleCloseVideo"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleCloseVideo },
		{ .NameUTF8 = UTF8TEXT("HandleCreateAccount"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleCreateAccount },
		{ .NameUTF8 = UTF8TEXT("HandleExitGame"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleExitGame },
		{ .NameUTF8 = UTF8TEXT("HandleHost"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleHost },
		{ .NameUTF8 = UTF8TEXT("HandleJoin"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleJoin },
		{ .NameUTF8 = UTF8TEXT("HandleLogin"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleLogin },
		{ .NameUTF8 = UTF8TEXT("HandleLogout"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleLogout },
		{ .NameUTF8 = UTF8TEXT("HandleOpenVideo"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execHandleOpenVideo },
		{ .NameUTF8 = UTF8TEXT("ShowAuthentication"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execShowAuthentication },
		{ .NameUTF8 = UTF8TEXT("ShowServerPage"), .Pointer = &UDigimonVenomNXTMainMenuWidget::execShowServerPage },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleAuthResult, "HandleAuthResult" }, // 30396f8402843bd681eea912bf1bf460cba9cb13
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCloseVideo, "HandleCloseVideo" }, // 0014d74c878fced60fd5b4b5d15c18ce8ca2ed96
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleCreateAccount, "HandleCreateAccount" }, // 81942cae66899c62726d363485f45f0a4786f1f4
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleExitGame, "HandleExitGame" }, // 666b9f8fa82b7432f579746a94f32bfb4e512533
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleHost, "HandleHost" }, // 30ed3d583e151cf53d5788dced3ad107304740c0
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleJoin, "HandleJoin" }, // 5268cd79f0fd90c784416e31795778d0e2cdeea5
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogin, "HandleLogin" }, // 9ea5efe89da6d695d447442d261aa20809f2ae22
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleLogout, "HandleLogout" }, // e68152db4e4b0a3d6bafc26485fb3896ef1de463
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_HandleOpenVideo, "HandleOpenVideo" }, // a44e6f95ffd68024a81c1c7a8c3d78faacf1a903
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowAuthentication, "ShowAuthentication" }, // 158b6489c93ebee8bb097180272f8a25e1190d22
		{ &Z_Construct_UFunction_UDigimonVenomNXTMainMenuWidget_ShowServerPage, "ShowServerPage" }, // af4ea93730649acdb4aa92aa267ebd4a6fca15e7
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDigimonVenomNXTMainMenuWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDigimonVenomNXTMainMenuWidget Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PageSwitcher = { "PageSwitcher", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, PageSwitcher), Z_Construct_UClass_UWidgetSwitcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PageSwitcher_MetaData), NewProp_PageSwitcher_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UsernameInput = { "UsernameInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, UsernameInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UsernameInput_MetaData), NewProp_UsernameInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PasswordInput = { "PasswordInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, PasswordInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PasswordInput_MetaData), NewProp_PasswordInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AdminPasswordInput = { "AdminPasswordInput", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, AdminPasswordInput), Z_Construct_UClass_UEditableTextBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdminPasswordInput_MetaData), NewProp_AdminPasswordInput_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AuthStatusText = { "AuthStatusText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, AuthStatusText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AuthStatusText_MetaData), NewProp_AuthStatusText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ServerStatusText = { "ServerStatusText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, ServerStatusText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerStatusText_MetaData), NewProp_ServerStatusText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_WelcomeText = { "WelcomeText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, WelcomeText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WelcomeText_MetaData), NewProp_WelcomeText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ConnectionText = { "ConnectionText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, ConnectionText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConnectionText_MetaData), NewProp_ConnectionText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HostInfoText = { "HostInfoText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, HostInfoText), Z_Construct_UClass_UTextBlock, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HostInfoText_MetaData), NewProp_HostInfoText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_JoinWorldButton = { "JoinWorldButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, JoinWorldButton), Z_Construct_UClass_UButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JoinWorldButton_MetaData), NewProp_JoinWorldButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LoginSurface = { "LoginSurface", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, LoginSurface), Z_Construct_UClass_UWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoginSurface_MetaData), NewProp_LoginSurface_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_VideoSurface = { "VideoSurface", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, VideoSurface), Z_Construct_UClass_UWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VideoSurface_MetaData), NewProp_VideoSurface_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_VideoMenuButton = { "VideoMenuButton", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, VideoMenuButton), Z_Construct_UClass_UButton, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VideoMenuButton_MetaData), NewProp_VideoMenuButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_VideoSettings = { "VideoSettings", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UDigimonVenomNXTMainMenuWidget, VideoSettings), Z_Construct_UClass_UDigimonVenomNXTVideoSettingsWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VideoSettings_MetaData), NewProp_VideoSettings_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PageSwitcher,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UsernameInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PasswordInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdminPasswordInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AuthStatusText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ServerStatusText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WelcomeText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ConnectionText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HostInfoText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JoinWorldButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LoginSurface,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VideoSurface,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VideoMenuButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VideoSettings,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDigimonVenomNXTMainMenuWidget Property Definitions ************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UCommonActivatableWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DigimonVenomNXTRuntime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UDigimonVenomNXTMainMenuWidget_StaticRegisterNativesUDigimonVenomNXTMainMenuWidget()
{
	UClass* Class = UDigimonVenomNXTMainMenuWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget;
UClass* Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDigimonVenomNXTMainMenuWidget;
		if (!Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DigimonVenomNXTMainMenuWidget"),
				Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.InnerSingleton,
				UDigimonVenomNXTMainMenuWidget_StaticRegisterNativesUDigimonVenomNXTMainMenuWidget,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget.OuterSingleton;
}
#undef UHT_STATICS
UDigimonVenomNXTMainMenuWidget::UDigimonVenomNXTMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDigimonVenomNXTMainMenuWidget);
UDigimonVenomNXTMainMenuWidget::~UDigimonVenomNXTMainMenuWidget() {}
// ********** End Class UDigimonVenomNXTMainMenuWidget *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTMainMenuWidget_h__Script_DigimonVenomNXTRuntime_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDigimonVenomNXTMainMenuWidget, TEXT("UDigimonVenomNXTMainMenuWidget"), &Z_Registration_Info_UClass_UDigimonVenomNXTMainMenuWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDigimonVenomNXTMainMenuWidget), 2966135447U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Leen_Documents_Unreal_Projects_DigimonVenomNXT_Plugins_DigimonVenomNXT_Source_DigimonVenomNXTRuntime_Public_DigimonVenomNXTMainMenuWidget_h__Script_DigimonVenomNXTRuntime_5edff6816b964ef8dc0e53249761d28c444b9d58{
	TEXT("/Script/DigimonVenomNXTRuntime"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
