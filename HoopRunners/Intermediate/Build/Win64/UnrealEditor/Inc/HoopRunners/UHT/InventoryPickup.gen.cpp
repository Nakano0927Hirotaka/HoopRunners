// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryPickup.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInventoryPickup() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
HOOPRUNNERS_API UClass* Z_Construct_UClass_AInventoryPickup();
HOOPRUNNERS_API UClass* Z_Construct_UClass_AInventoryPickup_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister();
UPackage* Z_Construct_UPackage__Script_HoopRunners();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInventoryPickup Function Interact ***************************************
struct Z_Construct_UFunction_AInventoryPickup_Interact_Statics
{
	struct InventoryPickup_eventInteract_Parms
	{
		UInventoryComponent* Inventory;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8f\x96\xe5\xbe\x97\xe5\x87\xa6\xe7\x90\x86\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x84\xe3\x80\x81\xe6\x88\x90\xe5\x8a\x9f\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x82\x92\xe7\xa0\xb4\xe6\xa3\x84\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\x96\xe5\xbe\x97\xe5\x87\xa6\xe7\x90\x86\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x84\xe3\x80\x81\xe6\x88\x90\xe5\x8a\x9f\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x82\x92\xe7\xa0\xb4\xe6\xa3\x84\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Inventory_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Inventory;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_Inventory = { "Inventory", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventInteract_Parms, Inventory), Z_Construct_UClass_UInventoryComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Inventory_MetaData), NewProp_Inventory_MetaData) };
void Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((InventoryPickup_eventInteract_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(InventoryPickup_eventInteract_Parms), &Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInventoryPickup_Interact_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_Inventory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_Interact_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_Interact_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInventoryPickup_Interact_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInventoryPickup, nullptr, "Interact", Z_Construct_UFunction_AInventoryPickup_Interact_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_Interact_Statics::PropPointers), sizeof(Z_Construct_UFunction_AInventoryPickup_Interact_Statics::InventoryPickup_eventInteract_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_Interact_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInventoryPickup_Interact_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInventoryPickup_Interact_Statics::InventoryPickup_eventInteract_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInventoryPickup_Interact()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInventoryPickup_Interact_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInventoryPickup::execInteract)
{
	P_GET_OBJECT(UInventoryComponent,Z_Param_Inventory);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Interact(Z_Param_Inventory);
	P_NATIVE_END;
}
// ********** End Class AInventoryPickup Function Interact *****************************************

// ********** Begin Class AInventoryPickup Function OnRep_Appearance *******************************
struct Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x88\x9d\xe6\x9c\x9f\xe9\x85\x8d\xe7\xbd\xae\xe3\x83\xbb\xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe3\x83\xbb\xe9\x80\x94\xe4\xb8\xad\xe5\x8f\x82\xe5\x8a\xa0\xe3\x81\xae\xe3\x81\x84\xe3\x81\x9a\xe3\x82\x8c\xe3\x81\xa7\xe3\x82\x82\xe3\x80\x81\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe5\x81\xb4\xe3\x81\xae\xe5\xa4\x96\xe8\xa6\xb3\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\x9d\xe6\x9c\x9f\xe9\x85\x8d\xe7\xbd\xae\xe3\x83\xbb\xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe3\x83\xbb\xe9\x80\x94\xe4\xb8\xad\xe5\x8f\x82\xe5\x8a\xa0\xe3\x81\xae\xe3\x81\x84\xe3\x81\x9a\xe3\x82\x8c\xe3\x81\xa7\xe3\x82\x82\xe3\x80\x81\xe3\x82\xb5\xe3\x83\xbc\xe3\x83\x90\xe3\x83\xbc\xe5\x81\xb4\xe3\x81\xae\xe5\xa4\x96\xe8\xa6\xb3\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInventoryPickup, nullptr, "OnRep_Appearance", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInventoryPickup::execOnRep_Appearance)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_Appearance();
	P_NATIVE_END;
}
// ********** End Class AInventoryPickup Function OnRep_Appearance *********************************

// ********** Begin Class AInventoryPickup Function OnVolumeBeginOverlap ***************************
struct Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics
{
	struct InventoryPickup_eventOnVolumeBeginOverlap_Parms
	{
		UPrimitiveComponent* Overlapped;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComponent;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe7\xaf\x84\xe5\x9b\xb2\xe3\x81\xab\xe5\x85\xa5\xe3\x81\xa3\xe3\x81\x9f\xef\xbc\x8f\xe5\x87\xba\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x80\x81\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe5\x81\xb4\xe3\x81\xae\xe5\x80\x99\xe8\xa3\x9c\xe4\xb8\x80\xe8\xa6\xa7\xe3\x82\x92\xe6\x9b\xb4\xe6\x96\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe7\xaf\x84\xe5\x9b\xb2\xe3\x81\xab\xe5\x85\xa5\xe3\x81\xa3\xe3\x81\x9f\xef\xbc\x8f\xe5\x87\xba\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x80\x81\xe6\x89\x80\xe6\x8c\x81\xe5\x93\x81\xe5\x81\xb4\xe3\x81\xae\xe5\x80\x99\xe8\xa3\x9c\xe4\xb8\x80\xe8\xa6\xa7\xe3\x82\x92\xe6\x9b\xb4\xe6\x96\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Overlapped_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Overlapped;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComponent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_Overlapped = { "Overlapped", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeBeginOverlap_Parms, Overlapped), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Overlapped_MetaData), NewProp_Overlapped_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherComponent = { "OtherComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeBeginOverlap_Parms, OtherComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComponent_MetaData), NewProp_OtherComponent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeBeginOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_bFromSweep_SetBit(void* Obj)
{
	((InventoryPickup_eventOnVolumeBeginOverlap_Parms*)Obj)->bFromSweep = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(InventoryPickup_eventOnVolumeBeginOverlap_Parms), &Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeBeginOverlap_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // 267591329
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_Overlapped,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInventoryPickup, nullptr, "OnVolumeBeginOverlap", Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::PropPointers), sizeof(Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::InventoryPickup_eventOnVolumeBeginOverlap_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::InventoryPickup_eventOnVolumeBeginOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInventoryPickup::execOnVolumeBeginOverlap)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_Overlapped);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnVolumeBeginOverlap(Z_Param_Overlapped,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// ********** End Class AInventoryPickup Function OnVolumeBeginOverlap *****************************

// ********** Begin Class AInventoryPickup Function OnVolumeEndOverlap *****************************
struct Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics
{
	struct InventoryPickup_eventOnVolumeEndOverlap_Parms
	{
		UPrimitiveComponent* Overlapped;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComponent;
		int32 OtherBodyIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Overlapped_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Overlapped;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComponent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_Overlapped = { "Overlapped", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeEndOverlap_Parms, Overlapped), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Overlapped_MetaData), NewProp_Overlapped_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeEndOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherComponent = { "OtherComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeEndOverlap_Parms, OtherComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComponent_MetaData), NewProp_OtherComponent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventoryPickup_eventOnVolumeEndOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_Overlapped,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::NewProp_OtherBodyIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInventoryPickup, nullptr, "OnVolumeEndOverlap", Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::PropPointers), sizeof(Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::InventoryPickup_eventOnVolumeEndOverlap_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::InventoryPickup_eventOnVolumeEndOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInventoryPickup::execOnVolumeEndOverlap)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_Overlapped);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnVolumeEndOverlap(Z_Param_Overlapped,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex);
	P_NATIVE_END;
}
// ********** End Class AInventoryPickup Function OnVolumeEndOverlap *******************************

// ********** Begin Class AInventoryPickup *********************************************************
void AInventoryPickup::StaticRegisterNativesAInventoryPickup()
{
	UClass* Class = AInventoryPickup::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Interact", &AInventoryPickup::execInteract },
		{ "OnRep_Appearance", &AInventoryPickup::execOnRep_Appearance },
		{ "OnVolumeBeginOverlap", &AInventoryPickup::execOnVolumeBeginOverlap },
		{ "OnVolumeEndOverlap", &AInventoryPickup::execOnVolumeEndOverlap },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInventoryPickup;
UClass* AInventoryPickup::GetPrivateStaticClass()
{
	using TClass = AInventoryPickup;
	if (!Z_Registration_Info_UClass_AInventoryPickup.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InventoryPickup"),
			Z_Registration_Info_UClass_AInventoryPickup.InnerSingleton,
			StaticRegisterNativesAInventoryPickup,
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
	return Z_Registration_Info_UClass_AInventoryPickup.InnerSingleton;
}
UClass* Z_Construct_UClass_AInventoryPickup_NoRegister()
{
	return AInventoryPickup::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInventoryPickup_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe8\xbf\x91\xe3\x81\xa5\xe3\x81\x84\xe3\x81\xa6\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe3\x81\xb8\xe5\x85\xa5\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x80\x82\n" },
#endif
		{ "IncludePath", "InventoryPickup.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe8\xbf\x91\xe3\x81\xa5\xe3\x81\x84\xe3\x81\xa6\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe3\x81\xb8\xe5\x85\xa5\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemMesh_MetaData[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x80\x82\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionVolume_MetaData[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe5\x8f\x96\xe5\xbe\x97\xe5\x8f\xaf\xe8\x83\xbd\xe3\x81\xab\xe3\x81\xaa\xe3\x82\x8b\xe7\xaf\x84\xe5\x9b\xb2\xe3\x80\x82\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x97\xe3\x83\xac\xe3\x82\xa4\xe3\x83\xa4\xe3\x83\xbc\xe3\x81\x8c\xe5\x8f\x96\xe5\xbe\x97\xe5\x8f\xaf\xe8\x83\xbd\xe3\x81\xab\xe3\x81\xaa\xe3\x82\x8b\xe7\xaf\x84\xe5\x9b\xb2\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemDefinition_MetaData[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x81\x93\xe3\x81\xae\xe5\x8f\x96\xe5\xbe\x97\xe7\x89\xa9\xe3\x81\x8c\xe8\xa1\xa8\xe3\x81\x99\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe5\xae\x9a\xe7\xbe\xa9\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x81\x93\xe3\x81\xae\xe5\x8f\x96\xe5\xbe\x97\xe7\x89\xa9\xe3\x81\x8c\xe8\xa1\xa8\xe3\x81\x99\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xae\xe5\xae\x9a\xe7\xbe\xa9\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupMesh_MetaData[] = {
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupMaterials_MetaData[] = {
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupScale_MetaData[] = {
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupInteractionRadius_MetaData[] = {
		{ "ModuleRelativePath", "Public/InventoryPickup.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionVolume;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemDefinition;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PickupMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PickupMaterials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PickupMaterials;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PickupScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PickupInteractionRadius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AInventoryPickup_Interact, "Interact" }, // 4038852054
		{ &Z_Construct_UFunction_AInventoryPickup_OnRep_Appearance, "OnRep_Appearance" }, // 1130880783
		{ &Z_Construct_UFunction_AInventoryPickup_OnVolumeBeginOverlap, "OnVolumeBeginOverlap" }, // 293437679
		{ &Z_Construct_UFunction_AInventoryPickup_OnVolumeEndOverlap, "OnVolumeEndOverlap" }, // 2266790615
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInventoryPickup>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_ItemMesh = { "ItemMesh", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, ItemMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemMesh_MetaData), NewProp_ItemMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_InteractionVolume = { "InteractionVolume", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, InteractionVolume), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionVolume_MetaData), NewProp_InteractionVolume_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_ItemDefinition = { "ItemDefinition", nullptr, (EPropertyFlags)0x0114000000000025, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, ItemDefinition), Z_Construct_UClass_UInventoryItemDefinition_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemDefinition_MetaData), NewProp_ItemDefinition_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMesh = { "PickupMesh", "OnRep_Appearance", (EPropertyFlags)0x0144000100000020, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, PickupMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupMesh_MetaData), NewProp_PickupMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMaterials_Inner = { "PickupMaterials", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMaterials = { "PickupMaterials", "OnRep_Appearance", (EPropertyFlags)0x0144000100000020, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, PickupMaterials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupMaterials_MetaData), NewProp_PickupMaterials_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupScale = { "PickupScale", "OnRep_Appearance", (EPropertyFlags)0x0040000100000020, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, PickupScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupScale_MetaData), NewProp_PickupScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupInteractionRadius = { "PickupInteractionRadius", nullptr, (EPropertyFlags)0x0040000000000020, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInventoryPickup, PickupInteractionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupInteractionRadius_MetaData), NewProp_PickupInteractionRadius_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInventoryPickup_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_ItemMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_InteractionVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_ItemDefinition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMaterials_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupMaterials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryPickup_Statics::NewProp_PickupInteractionRadius,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInventoryPickup_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AInventoryPickup_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInventoryPickup_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInventoryPickup_Statics::ClassParams = {
	&AInventoryPickup::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AInventoryPickup_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AInventoryPickup_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInventoryPickup_Statics::Class_MetaDataParams), Z_Construct_UClass_AInventoryPickup_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInventoryPickup()
{
	if (!Z_Registration_Info_UClass_AInventoryPickup.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInventoryPickup.OuterSingleton, Z_Construct_UClass_AInventoryPickup_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInventoryPickup.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void AInventoryPickup::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_ItemDefinition(TEXT("ItemDefinition"));
	static FName Name_PickupMesh(TEXT("PickupMesh"));
	static FName Name_PickupMaterials(TEXT("PickupMaterials"));
	static FName Name_PickupScale(TEXT("PickupScale"));
	static FName Name_PickupInteractionRadius(TEXT("PickupInteractionRadius"));
	const bool bIsValid = true
		&& Name_ItemDefinition == ClassReps[(int32)ENetFields_Private::ItemDefinition].Property->GetFName()
		&& Name_PickupMesh == ClassReps[(int32)ENetFields_Private::PickupMesh].Property->GetFName()
		&& Name_PickupMaterials == ClassReps[(int32)ENetFields_Private::PickupMaterials].Property->GetFName()
		&& Name_PickupScale == ClassReps[(int32)ENetFields_Private::PickupScale].Property->GetFName()
		&& Name_PickupInteractionRadius == ClassReps[(int32)ENetFields_Private::PickupInteractionRadius].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AInventoryPickup"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR(AInventoryPickup);
AInventoryPickup::~AInventoryPickup() {}
// ********** End Class AInventoryPickup ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h__Script_HoopRunners_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInventoryPickup, AInventoryPickup::StaticClass, TEXT("AInventoryPickup"), &Z_Registration_Info_UClass_AInventoryPickup, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInventoryPickup), 3190088864U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h__Script_HoopRunners_2407453234(TEXT("/Script/HoopRunners"),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h__Script_HoopRunners_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h__Script_HoopRunners_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
