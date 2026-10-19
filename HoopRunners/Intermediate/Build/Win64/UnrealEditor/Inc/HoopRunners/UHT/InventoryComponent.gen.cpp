// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryComponent.h"
#include "InventoryItemDefinition.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInventoryComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
HOOPRUNNERS_API UClass* Z_Construct_UClass_AInventoryPickup_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryComponent();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryWidget_NoRegister();
HOOPRUNNERS_API UEnum* Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction();
HOOPRUNNERS_API UFunction* Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature();
HOOPRUNNERS_API UScriptStruct* Z_Construct_UScriptStruct_FInventoryStack();
UPackage* Z_Construct_UPackage__Script_HoopRunners();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FInventoryChanged *****************************************************
struct Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics
{
	struct _Script_HoopRunners_eventInventoryChanged_Parms
	{
		TArray<FInventoryStack> Items;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Items_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Items_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Items;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::NewProp_Items_Inner = { "Items", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryStack, METADATA_PARAMS(0, nullptr) }; // 4242720339
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::NewProp_Items = { "Items", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_HoopRunners_eventInventoryChanged_Parms, Items), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Items_MetaData), NewProp_Items_MetaData) }; // 4242720339
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::NewProp_Items_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::NewProp_Items,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_HoopRunners, nullptr, "InventoryChanged__DelegateSignature", Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::_Script_HoopRunners_eventInventoryChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::_Script_HoopRunners_eventInventoryChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FInventoryChanged_DelegateWrapper(const FMulticastScriptDelegate& InventoryChanged, TArray<FInventoryStack> const& Items)
{
	struct _Script_HoopRunners_eventInventoryChanged_Parms
	{
		TArray<FInventoryStack> Items;
	};
	_Script_HoopRunners_eventInventoryChanged_Parms Parms;
	Parms.Items=Items;
	InventoryChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FInventoryChanged *******************************************************

// ********** Begin Enum EInventoryNetworkAction ***************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EInventoryNetworkAction;
static UEnum* EInventoryNetworkAction_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EInventoryNetworkAction.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EInventoryNetworkAction.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction, (UObject*)Z_Construct_UPackage__Script_HoopRunners(), TEXT("EInventoryNetworkAction"));
	}
	return Z_Registration_Info_UEnum_EInventoryNetworkAction.OuterSingleton;
}
template<> HOOPRUNNERS_API UEnum* StaticEnum<EInventoryNetworkAction>()
{
	return EInventoryNetworkAction_StaticEnum();
}
struct Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8f\x96\xe5\xbe\x97\xe8\xa6\x81\xe6\xb1\x82\xe3\x81\x8c\xe5\xa4\xb1\xe6\x95\x97\xe3\x81\x97\xe3\x81\xa6\xe3\x82\x82\xe3\x80\x81\xe5\x90\x8c\xe3\x81\x98\xe8\xa6\x81\xe6\xb1\x82\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\xb8\xe5\x88\x87\xe3\x82\x8a\xe6\x9b\xbf\xe3\x81\x88\xe3\x81\xaa\xe3\x81\x84\xe3\x80\x82\n" },
#endif
		{ "Consume.Name", "EInventoryNetworkAction::Consume" },
		{ "Drop.Name", "EInventoryNetworkAction::Drop" },
		{ "EMP.Name", "EInventoryNetworkAction::EMP" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
		{ "Pickup.Name", "EInventoryNetworkAction::Pickup" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\x96\xe5\xbe\x97\xe8\xa6\x81\xe6\xb1\x82\xe3\x81\x8c\xe5\xa4\xb1\xe6\x95\x97\xe3\x81\x97\xe3\x81\xa6\xe3\x82\x82\xe3\x80\x81\xe5\x90\x8c\xe3\x81\x98\xe8\xa6\x81\xe6\xb1\x82\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\xb8\xe5\x88\x87\xe3\x82\x8a\xe6\x9b\xbf\xe3\x81\x88\xe3\x81\xaa\xe3\x81\x84\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EInventoryNetworkAction::Pickup", (int64)EInventoryNetworkAction::Pickup },
		{ "EInventoryNetworkAction::Consume", (int64)EInventoryNetworkAction::Consume },
		{ "EInventoryNetworkAction::EMP", (int64)EInventoryNetworkAction::EMP },
		{ "EInventoryNetworkAction::Drop", (int64)EInventoryNetworkAction::Drop },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_HoopRunners,
	nullptr,
	"EInventoryNetworkAction",
	"EInventoryNetworkAction",
	Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::Enum_MetaDataParams), Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction()
{
	if (!Z_Registration_Info_UEnum_EInventoryNetworkAction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EInventoryNetworkAction.InnerSingleton, Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EInventoryNetworkAction.InnerSingleton;
}
// ********** End Enum EInventoryNetworkAction *****************************************************

// ********** Begin Class UInventoryComponent Function AddItem *************************************
struct Z_Construct_UFunction_UInventoryComponent_AddItem_Statics
{
	struct InventoryComponent_eventAddItem_Parms
	{
		UInventoryItemDefinition* ItemDefinition;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xbb\xbb\xe6\x84\x8f\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x81\xaf\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xae\xe5\xa0\xb1\xe9\x85\xac\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xaa\xe3\x81\xa9\xe3\x81\x8b\xe3\x82\x89\xe3\x81\xa0\xe3\x81\x91\xe5\x91\xbc\xe3\x81\xb6\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbb\xbb\xe6\x84\x8f\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x81\xaf\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xae\xe5\xa0\xb1\xe9\x85\xac\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xaa\xe3\x81\xa9\xe3\x81\x8b\xe3\x82\x89\xe3\x81\xa0\xe3\x81\x91\xe5\x91\xbc\xe3\x81\xb6\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemDefinition;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ItemDefinition = { "ItemDefinition", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventAddItem_Parms, ItemDefinition), Z_Construct_UClass_UInventoryItemDefinition_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((InventoryComponent_eventAddItem_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(InventoryComponent_eventAddItem_Parms), &Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ItemDefinition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "AddItem", Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::InventoryComponent_eventAddItem_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020405, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::InventoryComponent_eventAddItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_AddItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_AddItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execAddItem)
{
	P_GET_OBJECT(UInventoryItemDefinition,Z_Param_ItemDefinition);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->AddItem(Z_Param_ItemDefinition);
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function AddItem ***************************************

// ********** Begin Class UInventoryComponent Function CycleSelection ******************************
struct Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics
{
	struct InventoryComponent_eventCycleSelection_Parms
	{
		int32 Direction;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventCycleSelection_Parms, Direction), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::NewProp_Direction,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "CycleSelection", Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::InventoryComponent_eventCycleSelection_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::InventoryComponent_eventCycleSelection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_CycleSelection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_CycleSelection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execCycleSelection)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Direction);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CycleSelection(Z_Param_Direction);
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function CycleSelection ********************************

// ********** Begin Class UInventoryComponent Function DropSelectedItem ****************************
struct Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics
{
	struct InventoryComponent_eventDropSelectedItem_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((InventoryComponent_eventDropSelectedItem_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(InventoryComponent_eventDropSelectedItem_Parms), &Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "DropSelectedItem", Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::InventoryComponent_eventDropSelectedItem_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::InventoryComponent_eventDropSelectedItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_DropSelectedItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_DropSelectedItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execDropSelectedItem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DropSelectedItem();
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function DropSelectedItem ******************************

// ********** Begin Class UInventoryComponent Function GetItems ************************************
struct Z_Construct_UFunction_UInventoryComponent_GetItems_Statics
{
	struct InventoryComponent_eventGetItems_Parms
	{
		TArray<FInventoryStack> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryStack, METADATA_PARAMS(0, nullptr) }; // 4242720339
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventGetItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 4242720339
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "GetItems", Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::InventoryComponent_eventGetItems_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::InventoryComponent_eventGetItems_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_GetItems()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_GetItems_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execGetItems)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FInventoryStack>*)Z_Param__Result=P_THIS->GetItems();
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function GetItems **************************************

// ********** Begin Class UInventoryComponent Function GetSelectedSlotIndex ************************
struct Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics
{
	struct InventoryComponent_eventGetSelectedSlotIndex_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventGetSelectedSlotIndex_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "GetSelectedSlotIndex", Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::InventoryComponent_eventGetSelectedSlotIndex_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::InventoryComponent_eventGetSelectedSlotIndex_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execGetSelectedSlotIndex)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetSelectedSlotIndex();
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function GetSelectedSlotIndex **************************

// ********** Begin Class UInventoryComponent Function OnRep_Items *********************************
struct Z_Construct_UFunction_UInventoryComponent_OnRep_Items_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_OnRep_Items_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "OnRep_Items", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_OnRep_Items_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_OnRep_Items_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UInventoryComponent_OnRep_Items()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_OnRep_Items_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execOnRep_Items)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Items();
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function OnRep_Items ***********************************

// ********** Begin Class UInventoryComponent Function ServerPerformAction *************************
struct InventoryComponent_eventServerPerformAction_Parms
{
	EInventoryNetworkAction Action;
	AInventoryPickup* Pickup;
	FGuid InstanceId;
	int32 ExpectedQuantity;
};
static FName NAME_UInventoryComponent_ServerPerformAction = FName(TEXT("ServerPerformAction"));
void UInventoryComponent::ServerPerformAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup, FGuid InstanceId, int32 ExpectedQuantity)
{
	InventoryComponent_eventServerPerformAction_Parms Parms;
	Parms.Action=Action;
	Parms.Pickup=Pickup;
	Parms.InstanceId=InstanceId;
	Parms.ExpectedQuantity=ExpectedQuantity;
	UFunction* Func = FindFunctionChecked(NAME_UInventoryComponent_ServerPerformAction);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8b\xe3\x82\x89\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe5\xae\x9a\xe7\xbe\xa9\xe3\x82\x92\xe5\x8f\x97\xe3\x81\x91\xe5\x8f\x96\xe3\x82\x89\xe3\x81\x9a\xe3\x80\x81\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xae\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x81\xa8ID\xe3\x82\x92\xe7\x85\xa7\xe5\x90\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\x8b\xe3\x82\x89\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe5\xae\x9a\xe7\xbe\xa9\xe3\x82\x92\xe5\x8f\x97\xe3\x81\x91\xe5\x8f\x96\xe3\x82\x89\xe3\x81\x9a\xe3\x80\x81\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xae\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x81\xa8ID\xe3\x82\x92\xe7\x85\xa7\xe5\x90\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Action_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Action;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Pickup;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ExpectedQuantity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Action_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Action = { "Action", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventServerPerformAction_Parms, Action), Z_Construct_UEnum_HoopRunners_EInventoryNetworkAction, METADATA_PARAMS(0, nullptr) }; // 4052412824
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Pickup = { "Pickup", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventServerPerformAction_Parms, Pickup), Z_Construct_UClass_AInventoryPickup_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventServerPerformAction_Parms, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_ExpectedQuantity = { "ExpectedQuantity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryComponent_eventServerPerformAction_Parms, ExpectedQuantity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Action_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Action,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_Pickup,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::NewProp_ExpectedQuantity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "ServerPerformAction", Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::PropPointers), sizeof(InventoryComponent_eventServerPerformAction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00A40CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(InventoryComponent_eventServerPerformAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_ServerPerformAction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_ServerPerformAction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execServerPerformAction)
{
	P_GET_ENUM(EInventoryNetworkAction,Z_Param_Action);
	P_GET_OBJECT(AInventoryPickup,Z_Param_Pickup);
	P_GET_STRUCT(FGuid,Z_Param_InstanceId);
	P_GET_PROPERTY(FIntProperty,Z_Param_ExpectedQuantity);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerPerformAction_Implementation(EInventoryNetworkAction(Z_Param_Action),Z_Param_Pickup,Z_Param_InstanceId,Z_Param_ExpectedQuantity);
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function ServerPerformAction ***************************

// ********** Begin Class UInventoryComponent Function TryInteract *********************************
struct Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics
{
	struct InventoryComponent_eventTryInteract_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// E\xe3\x81\xaf\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f\xe9\x80\x9a\xe5\xb8\xb8\xe4\xbd\xbf\xe7\x94\xa8\xe3\x80\x81Space\xe3\x81\xaf\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f""EMP\xe4\xbd\xbf\xe7\x94\xa8\xe3\x80\x82\n// \xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xaetrue\xe3\x81\xaf\xe8\xa6\x81\xe6\xb1\x82\xe9\x80\x81\xe4\xbf\xa1\xe3\x82\x92\xe8\xa1\xa8\xe3\x81\x99\xe3\x80\x82\xe7\xa2\xba\xe5\xae\x9a\xe7\xb5\x90\xe6\x9e\x9c\xe3\x81\xafOnInventoryChanged\xe3\x81\xa7\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "E\xe3\x81\xaf\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f\xe9\x80\x9a\xe5\xb8\xb8\xe4\xbd\xbf\xe7\x94\xa8\xe3\x80\x81Space\xe3\x81\xaf\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f""EMP\xe4\xbd\xbf\xe7\x94\xa8\xe3\x80\x82\n\xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xaetrue\xe3\x81\xaf\xe8\xa6\x81\xe6\xb1\x82\xe9\x80\x81\xe4\xbf\xa1\xe3\x82\x92\xe8\xa1\xa8\xe3\x81\x99\xe3\x80\x82\xe7\xa2\xba\xe5\xae\x9a\xe7\xb5\x90\xe6\x9e\x9c\xe3\x81\xafOnInventoryChanged\xe3\x81\xa7\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((InventoryComponent_eventTryInteract_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(InventoryComponent_eventTryInteract_Parms), &Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventoryComponent, nullptr, "TryInteract", Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::InventoryComponent_eventTryInteract_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::InventoryComponent_eventTryInteract_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInventoryComponent_TryInteract()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryComponent_TryInteract_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryComponent::execTryInteract)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->TryInteract();
	P_NATIVE_END;
}
// ********** End Class UInventoryComponent Function TryInteract ***********************************

// ********** Begin Class UInventoryComponent ******************************************************
void UInventoryComponent::StaticRegisterNativesUInventoryComponent()
{
	UClass* Class = UInventoryComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddItem", &UInventoryComponent::execAddItem },
		{ "CycleSelection", &UInventoryComponent::execCycleSelection },
		{ "DropSelectedItem", &UInventoryComponent::execDropSelectedItem },
		{ "GetItems", &UInventoryComponent::execGetItems },
		{ "GetSelectedSlotIndex", &UInventoryComponent::execGetSelectedSlotIndex },
		{ "OnRep_Items", &UInventoryComponent::execOnRep_Items },
		{ "ServerPerformAction", &UInventoryComponent::execServerPerformAction },
		{ "TryInteract", &UInventoryComponent::execTryInteract },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UInventoryComponent;
UClass* UInventoryComponent::GetPrivateStaticClass()
{
	using TClass = UInventoryComponent;
	if (!Z_Registration_Info_UClass_UInventoryComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InventoryComponent"),
			Z_Registration_Info_UClass_UInventoryComponent.InnerSingleton,
			StaticRegisterNativesUInventoryComponent,
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
	return Z_Registration_Info_UClass_UInventoryComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventoryComponent_NoRegister()
{
	return UInventoryComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventoryComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Gameplay" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x82\x92\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xa7\xe7\xae\xa1\xe7\x90\x86\xe3\x81\x97\xe3\x80\x81\xe6\x89\x80\xe6\x9c\x89\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\xa0\xe3\x81\x91\xe3\x81\xab\xe5\x86\x85\xe5\xae\xb9\xe3\x81\xa8HUD\xe3\x82\x92\xe5\x90\x8c\xe6\x9c\x9f\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "IncludePath", "InventoryComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x82\x92\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\xa7\xe7\xae\xa1\xe7\x90\x86\xe3\x81\x97\xe3\x80\x81\xe6\x89\x80\xe6\x9c\x89\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\xa0\xe3\x81\x91\xe3\x81\xab\xe5\x86\x85\xe5\xae\xb9\xe3\x81\xa8HUD\xe3\x82\x92\xe5\x90\x8c\xe6\x9c\x9f\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventoryWidgetClass_MetaData[] = {
		{ "Category", "Inventory|UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\x99\xe3\x82\x8b\xe6\x9c\xac\xe4\xba\xba\xe3\x81\xaeHUD\xe3\x80\x82\xe6\x9c\xaa\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xae\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe6\x97\xa2\xe5\xad\x98WBP\xe3\x82\x92\xe5\xae\x9f\xe8\xa1\x8c\xe6\x99\x82\xe3\x81\xab\xe8\xaa\xad\xe3\x81\xbf\xe8\xbe\xbc\xe3\x82\x80\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\x99\xe3\x82\x8b\xe6\x9c\xac\xe4\xba\xba\xe3\x81\xaeHUD\xe3\x80\x82\xe6\x9c\xaa\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xae\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe6\x97\xa2\xe5\xad\x98WBP\xe3\x82\x92\xe5\xae\x9f\xe8\xa1\x8c\xe6\x99\x82\xe3\x81\xab\xe8\xaa\xad\xe3\x81\xbf\xe8\xbe\xbc\xe3\x82\x80\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnInventoryChanged_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\x8c\xe7\xa2\xba\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x82\x92\xe5\x8f\x97\xe4\xbf\xa1\xe3\x81\x97\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab\xe3\x82\x82\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe3\x81\x8c\xe7\xa2\xba\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe3\x82\x92\xe5\x8f\x97\xe4\xbf\xa1\xe3\x81\x97\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab\xe3\x82\x82\xe9\x80\x9a\xe7\x9f\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Items_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventoryWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_InventoryWidgetClass;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnInventoryChanged;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Items_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Items;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InventoryWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInventoryComponent_AddItem, "AddItem" }, // 467827768
		{ &Z_Construct_UFunction_UInventoryComponent_CycleSelection, "CycleSelection" }, // 4000286553
		{ &Z_Construct_UFunction_UInventoryComponent_DropSelectedItem, "DropSelectedItem" }, // 2288102925
		{ &Z_Construct_UFunction_UInventoryComponent_GetItems, "GetItems" }, // 3588056642
		{ &Z_Construct_UFunction_UInventoryComponent_GetSelectedSlotIndex, "GetSelectedSlotIndex" }, // 3998252049
		{ &Z_Construct_UFunction_UInventoryComponent_OnRep_Items, "OnRep_Items" }, // 224766609
		{ &Z_Construct_UFunction_UInventoryComponent_ServerPerformAction, "ServerPerformAction" }, // 2659516747
		{ &Z_Construct_UFunction_UInventoryComponent_TryInteract, "TryInteract" }, // 587635805
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UInventoryComponent_Statics::NewProp_InventoryWidgetClass = { "InventoryWidgetClass", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryComponent, InventoryWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UInventoryWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventoryWidgetClass_MetaData), NewProp_InventoryWidgetClass_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UInventoryComponent_Statics::NewProp_OnInventoryChanged = { "OnInventoryChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryComponent, OnInventoryChanged), Z_Construct_UDelegateFunction_HoopRunners_InventoryChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnInventoryChanged_MetaData), NewProp_OnInventoryChanged_MetaData) }; // 1902262962
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UInventoryComponent_Statics::NewProp_Items_Inner = { "Items", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryStack, METADATA_PARAMS(0, nullptr) }; // 4242720339
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UInventoryComponent_Statics::NewProp_Items = { "Items", "OnRep_Items", (EPropertyFlags)0x0040000100020035, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryComponent, Items), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Items_MetaData), NewProp_Items_MetaData) }; // 4242720339
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventoryComponent_Statics::NewProp_InventoryWidget = { "InventoryWidget", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryComponent, InventoryWidget), Z_Construct_UClass_UInventoryWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventoryWidget_MetaData), NewProp_InventoryWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventoryComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryComponent_Statics::NewProp_InventoryWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryComponent_Statics::NewProp_OnInventoryChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryComponent_Statics::NewProp_Items_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryComponent_Statics::NewProp_Items,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryComponent_Statics::NewProp_InventoryWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInventoryComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryComponent_Statics::ClassParams = {
	&UInventoryComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UInventoryComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventoryComponent()
{
	if (!Z_Registration_Info_UClass_UInventoryComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryComponent.OuterSingleton, Z_Construct_UClass_UInventoryComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryComponent.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void UInventoryComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_Items(TEXT("Items"));
	const bool bIsValid = true
		&& Name_Items == ClassReps[(int32)ENetFields_Private::Items].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UInventoryComponent"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryComponent);
UInventoryComponent::~UInventoryComponent() {}
// ********** End Class UInventoryComponent ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EInventoryNetworkAction_StaticEnum, TEXT("EInventoryNetworkAction"), &Z_Registration_Info_UEnum_EInventoryNetworkAction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4052412824U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryComponent, UInventoryComponent::StaticClass, TEXT("UInventoryComponent"), &Z_Registration_Info_UClass_UInventoryComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryComponent), 2990838576U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_1760064969(TEXT("/Script/HoopRunners"),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h__Script_HoopRunners_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
