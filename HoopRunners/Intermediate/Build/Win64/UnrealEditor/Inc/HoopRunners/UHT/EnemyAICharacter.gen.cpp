// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EnemyAICharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEnemyAICharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
HOOPRUNNERS_API UClass* Z_Construct_UClass_AEnemyAICharacter();
HOOPRUNNERS_API UClass* Z_Construct_UClass_AEnemyAICharacter_NoRegister();
HOOPRUNNERS_API UEnum* Z_Construct_UEnum_HoopRunners_EEnemyAIState();
UPackage* Z_Construct_UPackage__Script_HoopRunners();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EEnemyAIState *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyAIState;
static UEnum* EEnemyAIState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEnemyAIState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEnemyAIState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HoopRunners_EEnemyAIState, (UObject*)Z_Construct_UPackage__Script_HoopRunners(), TEXT("EEnemyAIState"));
	}
	return Z_Registration_Info_UEnum_EEnemyAIState.OuterSingleton;
}
template<> HOOPRUNNERS_API UEnum* StaticEnum<EEnemyAIState>()
{
	return EEnemyAIState_StaticEnum();
}
struct Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Chasing.Comment", "// NavMesh\xe4\xb8\x8a\xe3\x82\x92\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b\n" },
		{ "Chasing.Name", "EEnemyAIState::Chasing" },
		{ "Chasing.ToolTip", "NavMesh\xe4\xb8\x8a\xe3\x82\x92\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\xb5\xe3\x82\xad\xe3\x83\xa3\xe3\x83\xa9\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe8\xa1\x8c\xe5\x8b\x95\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92\xe8\xa1\xa8\xe3\x81\x99\xe5\x88\x97\xe6\x8c\x99\xe5\x9e\x8b\xe3\x80\x82\n" },
#endif
		{ "FinalChase.Comment", "// \xe8\xa6\x96\xe8\xaa\x8d\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b\n" },
		{ "FinalChase.Name", "EEnemyAIState::FinalChase" },
		{ "FinalChase.ToolTip", "\xe8\xa6\x96\xe8\xaa\x8d\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
		{ "Patrolling.Name", "EEnemyAIState::Patrolling" },
		{ "Stunned.Comment", "// \xe7\xb5\x82\xe7\x9b\xa4\xe3\x81\xab\xe6\x9c\x80\xe5\xaf\x84\xe3\x82\x8a\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe3\x81\x84\xe7\xb6\x9a\xe3\x81\x91\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b\n" },
		{ "Stunned.Name", "EEnemyAIState::Stunned" },
		{ "Stunned.ToolTip", "\xe7\xb5\x82\xe7\x9b\xa4\xe3\x81\xab\xe6\x9c\x80\xe5\xaf\x84\xe3\x82\x8a\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe3\x81\x84\xe7\xb6\x9a\xe3\x81\x91\xe3\x82\x8b\xe7\x8a\xb6\xe6\x85\x8b" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\xb5\xe3\x82\xad\xe3\x83\xa3\xe3\x83\xa9\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x81\xae\xe8\xa1\x8c\xe5\x8b\x95\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92\xe8\xa1\xa8\xe3\x81\x99\xe5\x88\x97\xe6\x8c\x99\xe5\x9e\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEnemyAIState::Patrolling", (int64)EEnemyAIState::Patrolling },
		{ "EEnemyAIState::Chasing", (int64)EEnemyAIState::Chasing },
		{ "EEnemyAIState::FinalChase", (int64)EEnemyAIState::FinalChase },
		{ "EEnemyAIState::Stunned", (int64)EEnemyAIState::Stunned },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_HoopRunners,
	nullptr,
	"EEnemyAIState",
	"EEnemyAIState",
	Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_HoopRunners_EEnemyAIState()
{
	if (!Z_Registration_Info_UEnum_EEnemyAIState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyAIState.InnerSingleton, Z_Construct_UEnum_HoopRunners_EEnemyAIState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEnemyAIState.InnerSingleton;
}
// ********** End Enum EEnemyAIState ***************************************************************

// ********** Begin Class AEnemyAICharacter Function ApplyEMPStun **********************************
struct Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics
{
	struct EnemyAICharacter_eventApplyEMPStun_Parms
	{
		float DurationSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Stun" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// EMP\xe3\x81\xae\xe5\x8a\xb9\xe6\x9e\x9c\xe6\x99\x82\xe9\x96\x93\xe3\x81\xa0\xe3\x81\x91\xe6\x95\xb5\xe3\x82\x92\xe5\x81\x9c\xe6\xad\xa2\xe3\x81\x95\xe3\x81\x9b\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "EMP\xe3\x81\xae\xe5\x8a\xb9\xe6\x9e\x9c\xe6\x99\x82\xe9\x96\x93\xe3\x81\xa0\xe3\x81\x91\xe6\x95\xb5\xe3\x82\x92\xe5\x81\x9c\xe6\xad\xa2\xe3\x81\x95\xe3\x81\x9b\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DurationSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::NewProp_DurationSeconds = { "DurationSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAICharacter_eventApplyEMPStun_Parms, DurationSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::NewProp_DurationSeconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAICharacter, nullptr, "ApplyEMPStun", Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::EnemyAICharacter_eventApplyEMPStun_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::EnemyAICharacter_eventApplyEMPStun_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAICharacter::execApplyEMPStun)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DurationSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyEMPStun(Z_Param_DurationSeconds);
	P_NATIVE_END;
}
// ********** End Class AEnemyAICharacter Function ApplyEMPStun ************************************

// ********** Begin Class AEnemyAICharacter Function GetAIState ************************************
struct Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics
{
	struct EnemyAICharacter_eventGetAIState_Parms
	{
		EEnemyAIState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x8f\xbe\xe5\x9c\xa8\xe3\x81\xae""AI\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92""Blueprint\xe3\x81\x8b\xe3\x82\x89\xe8\xaa\xad\xe3\x81\xbf\xe5\x8f\x96\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x8f\xbe\xe5\x9c\xa8\xe3\x81\xae""AI\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92""Blueprint\xe3\x81\x8b\xe3\x82\x89\xe8\xaa\xad\xe3\x81\xbf\xe5\x8f\x96\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAICharacter_eventGetAIState_Parms, ReturnValue), Z_Construct_UEnum_HoopRunners_EEnemyAIState, METADATA_PARAMS(0, nullptr) }; // 3194246220
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAICharacter, nullptr, "GetAIState", Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::EnemyAICharacter_eventGetAIState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::EnemyAICharacter_eventGetAIState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAICharacter_GetAIState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAICharacter_GetAIState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAICharacter::execGetAIState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EEnemyAIState*)Z_Param__Result=P_THIS->GetAIState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAICharacter Function GetAIState **************************************

// ********** Begin Class AEnemyAICharacter Function OnAIStateChanged ******************************
struct EnemyAICharacter_eventOnAIStateChanged_Parms
{
	EEnemyAIState NewState;
};
static FName NAME_AEnemyAICharacter_OnAIStateChanged = FName(TEXT("OnAIStateChanged"));
void AEnemyAICharacter::OnAIStateChanged(EEnemyAIState NewState)
{
	EnemyAICharacter_eventOnAIStateChanged_Parms Parms;
	Parms.NewState=NewState;
	UFunction* Func = FindFunctionChecked(NAME_AEnemyAICharacter_OnAIStateChanged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x8a\xb6\xe6\x85\x8b\xe3\x81\x8c\xe5\x88\x87\xe3\x82\x8a\xe6\x9b\xbf\xe3\x82\x8f\xe3\x81\xa3\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab""Blueprint\xe5\x81\xb4\xe3\x81\xb8\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa4\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x8a\xb6\xe6\x85\x8b\xe3\x81\x8c\xe5\x88\x87\xe3\x82\x8a\xe6\x9b\xbf\xe3\x82\x8f\xe3\x81\xa3\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab""Blueprint\xe5\x81\xb4\xe3\x81\xb8\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa4\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::NewProp_NewState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAICharacter_eventOnAIStateChanged_Parms, NewState), Z_Construct_UEnum_HoopRunners_EEnemyAIState, METADATA_PARAMS(0, nullptr) }; // 3194246220
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::NewProp_NewState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAICharacter, nullptr, "OnAIStateChanged", Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::PropPointers), sizeof(EnemyAICharacter_eventOnAIStateChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(EnemyAICharacter_eventOnAIStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AEnemyAICharacter Function OnAIStateChanged ********************************

// ********** Begin Class AEnemyAICharacter Function OnRep_CurrentState ****************************
struct Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x83\xbb\xe8\xbf\xbd\xe8\xb7\xa1\xe8\xa7\xa3\xe9\x99\xa4\xe3\x82\x92\xe5\x8f\x97\xe4\xbf\xa1\xe3\x81\x97\xe3\x81\x9f\xe7\xab\xaf\xe6\x9c\xab\xe3\x81\xa7\xe3\x82\x82""Blueprint\xe3\x81\xae\xe8\xa1\xa8\xe7\xa4\xba\xe3\x82\xa4\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x82\x92\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x83\xbb\xe8\xbf\xbd\xe8\xb7\xa1\xe8\xa7\xa3\xe9\x99\xa4\xe3\x82\x92\xe5\x8f\x97\xe4\xbf\xa1\xe3\x81\x97\xe3\x81\x9f\xe7\xab\xaf\xe6\x9c\xab\xe3\x81\xa7\xe3\x82\x82""Blueprint\xe3\x81\xae\xe8\xa1\xa8\xe7\xa4\xba\xe3\x82\xa4\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x82\x92\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAICharacter, nullptr, "OnRep_CurrentState", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAICharacter::execOnRep_CurrentState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAICharacter Function OnRep_CurrentState ******************************

// ********** Begin Class AEnemyAICharacter ********************************************************
void AEnemyAICharacter::StaticRegisterNativesAEnemyAICharacter()
{
	UClass* Class = AEnemyAICharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ApplyEMPStun", &AEnemyAICharacter::execApplyEMPStun },
		{ "GetAIState", &AEnemyAICharacter::execGetAIState },
		{ "OnRep_CurrentState", &AEnemyAICharacter::execOnRep_CurrentState },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AEnemyAICharacter;
UClass* AEnemyAICharacter::GetPrivateStaticClass()
{
	using TClass = AEnemyAICharacter;
	if (!Z_Registration_Info_UClass_AEnemyAICharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("EnemyAICharacter"),
			Z_Registration_Info_UClass_AEnemyAICharacter.InnerSingleton,
			StaticRegisterNativesAEnemyAICharacter,
			sizeof(TClass),
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
	return Z_Registration_Info_UClass_AEnemyAICharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_AEnemyAICharacter_NoRegister()
{
	return AEnemyAICharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEnemyAICharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa6\x96\xe7\x95\x8c\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x80\x81\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81""EMP\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x82\x92\xe7\xae\xa1\xe7\x90\x86\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb5\xe3\x82\xad\xe3\x83\xa3\xe3\x83\xa9\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x80\x82\n" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "EnemyAICharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa6\x96\xe7\x95\x8c\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x80\x81\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81""EMP\xe3\x82\xb9\xe3\x82\xbf\xe3\x83\xb3\xe3\x82\x92\xe7\xae\xa1\xe7\x90\x86\xe3\x81\x99\xe3\x82\x8b\xe6\x95\xb5\xe3\x82\xad\xe3\x83\xa3\xe3\x83\xa9\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SightRange_MetaData[] = {
		{ "Category", "AI|Vision" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa6\x96\xe7\x95\x8c\xe5\x88\xa4\xe5\xae\x9a\xe3\x81\xab\xe4\xbd\xbf\xe3\x81\x86\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x80\x81\xe8\xa7\x92\xe5\xba\xa6\xe3\x80\x81\xe6\x9b\xb4\xe6\x96\xb0\xe9\x96\x93\xe9\x9a\x94\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa6\x96\xe7\x95\x8c\xe5\x88\xa4\xe5\xae\x9a\xe3\x81\xab\xe4\xbd\xbf\xe3\x81\x86\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x80\x81\xe8\xa7\x92\xe5\xba\xa6\xe3\x80\x81\xe6\x9b\xb4\xe6\x96\xb0\xe9\x96\x93\xe9\x9a\x94\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SightHalfAngleDegrees_MetaData[] = {
		{ "Category", "AI|Vision" },
		{ "ClampMax", "89.0" },
		{ "ClampMin", "1.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SenseUpdateInterval_MetaData[] = {
		{ "Category", "AI|Vision" },
		{ "ClampMin", "0.05" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolRadius_MetaData[] = {
		{ "Category", "AI|Patrol" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe5\x9b\x9e\xe7\xaf\x84\xe5\x9b\xb2\xe3\x81\xa8\xe5\xb7\xa1\xe5\x9b\x9e\xe5\x9c\xb0\xe7\x82\xb9\xe3\x81\xa7\xe5\xbe\x85\xe3\x81\xa4\xe6\x99\x82\xe9\x96\x93\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe5\x9b\x9e\xe7\xaf\x84\xe5\x9b\xb2\xe3\x81\xa8\xe5\xb7\xa1\xe5\x9b\x9e\xe5\x9c\xb0\xe7\x82\xb9\xe3\x81\xa7\xe5\xbe\x85\xe3\x81\xa4\xe6\x99\x82\xe9\x96\x93\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolPauseSeconds_MetaData[] = {
		{ "Category", "AI|Patrol" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolSpeed_MetaData[] = {
		{ "Category", "AI|Movement" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x80\x9a\xe5\xb8\xb8\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x80\x81\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\x9d\xe3\x82\x8c\xe3\x81\x9e\xe3\x82\x8c\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x80\x9f\xe5\xba\xa6\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x80\x9a\xe5\xb8\xb8\xe5\xb7\xa1\xe5\x9b\x9e\xe3\x80\x81\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x80\x81\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\x9d\xe3\x82\x8c\xe3\x81\x9e\xe3\x82\x8c\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x80\x9f\xe5\xba\xa6\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChaseSpeed_MetaData[] = {
		{ "Category", "AI|Movement" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FinalChaseSpeed_MetaData[] = {
		{ "Category", "AI|Movement" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChaseForgetSeconds_MetaData[] = {
		{ "Category", "AI|Chase" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbf\xbd\xe8\xb7\xa1\xe3\x82\x92\xe8\xab\xa6\xe3\x82\x81\xe3\x82\x8b\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe6\x99\x82\xe9\x96\x93\xe3\x81\xa8\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\xae\xe9\x96\x8b\xe5\xa7\x8b\xe6\x99\x82\xe5\x88\xbb\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x82\x92\xe8\xab\xa6\xe3\x82\x81\xe3\x82\x8b\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe6\x99\x82\xe9\x96\x93\xe3\x81\xa8\xe7\xb5\x82\xe7\x9b\xa4\xe8\xbf\xbd\xe8\xb7\xa1\xe3\x81\xae\xe9\x96\x8b\xe5\xa7\x8b\xe6\x99\x82\xe5\x88\xbb\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FinalChaseStartSeconds_MetaData[] = {
		{ "Category", "AI|Final Chase" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FinalTargetRefreshInterval_MetaData[] = {
		{ "Category", "AI|Final Chase" },
		{ "ClampMin", "0.05" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAcceptanceRadius_MetaData[] = {
		{ "Category", "AI|Movement" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Blueprint\xe3\x81\x8b\xe3\x82\x89\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92\xe7\xa2\xba\xe8\xaa\x8d\xe3\x81\xa7\xe3\x81\x8d\xe3\x82\x8b\xe3\x82\x88\xe3\x81\x86\xe7\x8f\xbe\xe5\x9c\xa8\xe5\x80\xa4\xe3\x82\x92\xe5\x85\xac\xe9\x96\x8b\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/EnemyAICharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint\xe3\x81\x8b\xe3\x82\x89\xe7\x8a\xb6\xe6\x85\x8b\xe3\x82\x92\xe7\xa2\xba\xe8\xaa\x8d\xe3\x81\xa7\xe3\x81\x8d\xe3\x82\x8b\xe3\x82\x88\xe3\x81\x86\xe7\x8f\xbe\xe5\x9c\xa8\xe5\x80\xa4\xe3\x82\x92\xe5\x85\xac\xe9\x96\x8b\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SightRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SightHalfAngleDegrees;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SenseUpdateInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolPauseSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChaseSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FinalChaseSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChaseForgetSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FinalChaseStartSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FinalTargetRefreshInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveAcceptanceRadius;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyAICharacter_ApplyEMPStun, "ApplyEMPStun" }, // 1737820473
		{ &Z_Construct_UFunction_AEnemyAICharacter_GetAIState, "GetAIState" }, // 799152605
		{ &Z_Construct_UFunction_AEnemyAICharacter_OnAIStateChanged, "OnAIStateChanged" }, // 857204558
		{ &Z_Construct_UFunction_AEnemyAICharacter_OnRep_CurrentState, "OnRep_CurrentState" }, // 3424581160
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyAICharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SightRange = { "SightRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, SightRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SightRange_MetaData), NewProp_SightRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SightHalfAngleDegrees = { "SightHalfAngleDegrees", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, SightHalfAngleDegrees), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SightHalfAngleDegrees_MetaData), NewProp_SightHalfAngleDegrees_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SenseUpdateInterval = { "SenseUpdateInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, SenseUpdateInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SenseUpdateInterval_MetaData), NewProp_SenseUpdateInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolRadius = { "PatrolRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, PatrolRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolRadius_MetaData), NewProp_PatrolRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolPauseSeconds = { "PatrolPauseSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, PatrolPauseSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolPauseSeconds_MetaData), NewProp_PatrolPauseSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolSpeed = { "PatrolSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, PatrolSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolSpeed_MetaData), NewProp_PatrolSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_ChaseSpeed = { "ChaseSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, ChaseSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChaseSpeed_MetaData), NewProp_ChaseSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalChaseSpeed = { "FinalChaseSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, FinalChaseSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FinalChaseSpeed_MetaData), NewProp_FinalChaseSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_ChaseForgetSeconds = { "ChaseForgetSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, ChaseForgetSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChaseForgetSeconds_MetaData), NewProp_ChaseForgetSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalChaseStartSeconds = { "FinalChaseStartSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, FinalChaseStartSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FinalChaseStartSeconds_MetaData), NewProp_FinalChaseStartSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalTargetRefreshInterval = { "FinalTargetRefreshInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, FinalTargetRefreshInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FinalTargetRefreshInterval_MetaData), NewProp_FinalTargetRefreshInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_MoveAcceptanceRadius = { "MoveAcceptanceRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, MoveAcceptanceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAcceptanceRadius_MetaData), NewProp_MoveAcceptanceRadius_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_CurrentState = { "CurrentState", "OnRep_CurrentState", (EPropertyFlags)0x0040000100020035, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAICharacter, CurrentState), Z_Construct_UEnum_HoopRunners_EEnemyAIState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 3194246220
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyAICharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SightRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SightHalfAngleDegrees,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_SenseUpdateInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolPauseSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_PatrolSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_ChaseSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalChaseSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_ChaseForgetSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalChaseStartSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_FinalTargetRefreshInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_MoveAcceptanceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_CurrentState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAICharacter_Statics::NewProp_CurrentState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAICharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AEnemyAICharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAICharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyAICharacter_Statics::ClassParams = {
	&AEnemyAICharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AEnemyAICharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAICharacter_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAICharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyAICharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyAICharacter()
{
	if (!Z_Registration_Info_UClass_AEnemyAICharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyAICharacter.OuterSingleton, Z_Construct_UClass_AEnemyAICharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyAICharacter.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void AEnemyAICharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_CurrentState(TEXT("CurrentState"));
	const bool bIsValid = true
		&& Name_CurrentState == ClassReps[(int32)ENetFields_Private::CurrentState].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AEnemyAICharacter"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyAICharacter);
AEnemyAICharacter::~AEnemyAICharacter() {}
// ********** End Class AEnemyAICharacter **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EEnemyAIState_StaticEnum, TEXT("EEnemyAIState"), &Z_Registration_Info_UEnum_EEnemyAIState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3194246220U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyAICharacter, AEnemyAICharacter::StaticClass, TEXT("AEnemyAICharacter"), &Z_Registration_Info_UClass_AEnemyAICharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyAICharacter), 660687742U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_1317224339(TEXT("/Script/HoopRunners"),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h__Script_HoopRunners_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
