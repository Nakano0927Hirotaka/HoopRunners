// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryItemDefinition.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInventoryItemDefinition() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister();
HOOPRUNNERS_API UEnum* Z_Construct_UEnum_HoopRunners_EInventoryItemUseType();
HOOPRUNNERS_API UScriptStruct* Z_Construct_UScriptStruct_FInventoryStack();
UPackage* Z_Construct_UPackage__Script_HoopRunners();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EInventoryItemUseType *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EInventoryItemUseType;
static UEnum* EInventoryItemUseType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EInventoryItemUseType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EInventoryItemUseType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HoopRunners_EInventoryItemUseType, (UObject*)Z_Construct_UPackage__Script_HoopRunners(), TEXT("EInventoryItemUseType"));
	}
	return Z_Registration_Info_UEnum_EInventoryItemUseType.OuterSingleton;
}
template<> HOOPRUNNERS_API UEnum* StaticEnum<EInventoryItemUseType>()
{
	return EInventoryItemUseType_StaticEnum();
}
struct Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\x92\xe4\xbd\xbf\xe3\x81\xa3\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x99\xe3\x82\x8b\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x81\xae\xe7\xa8\xae\xe9\xa1\x9e\xe3\x80\x82\n" },
#endif
		{ "EMP.Comment", "// \xe7\x9b\xb4\xe6\x8e\xa5\xe4\xbd\xbf\xe7\x94\xa8\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x82\x92\xe6\x8c\x81\xe3\x81\x9f\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\n" },
		{ "EMP.Name", "EInventoryItemUseType::EMP" },
		{ "EMP.ToolTip", "\xe7\x9b\xb4\xe6\x8e\xa5\xe4\xbd\xbf\xe7\x94\xa8\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x82\x92\xe6\x8c\x81\xe3\x81\x9f\xe3\x81\xaa\xe3\x81\x84\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0" },
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
		{ "None.Name", "EInventoryItemUseType::None" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\x92\xe4\xbd\xbf\xe3\x81\xa3\xe3\x81\x9f\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xab\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x99\xe3\x82\x8b\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x81\xae\xe7\xa8\xae\xe9\xa1\x9e\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EInventoryItemUseType::None", (int64)EInventoryItemUseType::None },
		{ "EInventoryItemUseType::EMP", (int64)EInventoryItemUseType::EMP },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_HoopRunners,
	nullptr,
	"EInventoryItemUseType",
	"EInventoryItemUseType",
	Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_HoopRunners_EInventoryItemUseType()
{
	if (!Z_Registration_Info_UEnum_EInventoryItemUseType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EInventoryItemUseType.InnerSingleton, Z_Construct_UEnum_HoopRunners_EInventoryItemUseType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EInventoryItemUseType.InnerSingleton;
}
// ********** End Enum EInventoryItemUseType *******************************************************

// ********** Begin Class UInventoryItemDefinition *************************************************
void UInventoryItemDefinition::StaticRegisterNativesUInventoryItemDefinition()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UInventoryItemDefinition;
UClass* UInventoryItemDefinition::GetPrivateStaticClass()
{
	using TClass = UInventoryItemDefinition;
	if (!Z_Registration_Info_UClass_UInventoryItemDefinition.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InventoryItemDefinition"),
			Z_Registration_Info_UClass_UInventoryItemDefinition.InnerSingleton,
			StaticRegisterNativesUInventoryItemDefinition,
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
	return Z_Registration_Info_UClass_UInventoryItemDefinition.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister()
{
	return UInventoryItemDefinition::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventoryItemDefinition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa1\xa8\xe7\xa4\xba\xe5\x90\x8d\xe3\x80\x81\xe3\x82\xa2\xe3\x82\xa4\xe3\x82\xb3\xe3\x83\xb3\xe3\x80\x81\xe4\xbd\xbf\xe7\x94\xa8\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x82\x92\xe3\x81\xbe\xe3\x81\xa8\xe3\x82\x81\xe3\x81\x9f\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe5\xae\x9a\xe7\xbe\xa9\xe3\x80\x82\n" },
#endif
		{ "IncludePath", "InventoryItemDefinition.h" },
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\xa8\xe7\xa4\xba\xe5\x90\x8d\xe3\x80\x81\xe3\x82\xa2\xe3\x82\xa4\xe3\x82\xb3\xe3\x83\xb3\xe3\x80\x81\xe4\xbd\xbf\xe7\x94\xa8\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x82\x92\xe3\x81\xbe\xe3\x81\xa8\xe3\x82\x81\xe3\x81\x9f\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe5\xae\x9a\xe7\xbe\xa9\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UI\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe5\x90\x8d\xe5\x89\x8d\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UI\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe5\x90\x8d\xe5\x89\x8d\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Icon_MetaData[] = {
		{ "Category", "Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe6\x9e\xa0\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe7\x94\xbb\xe5\x83\x8f\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe6\x9e\xa0\xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8b\xe7\x94\xbb\xe5\x83\x8f\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UseType_MetaData[] = {
		{ "Category", "Item|Use" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xbd\xbf\xe7\x94\xa8\xe6\x99\x82\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbd\xbf\xe7\x94\xa8\xe6\x99\x82\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe5\x8a\xb9\xe6\x9e\x9c\xe3\x80\x82" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Icon;
	static const UECodeGen_Private::FBytePropertyParams NewProp_UseType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_UseType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryItemDefinition>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryItemDefinition, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_Icon = { "Icon", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryItemDefinition, Icon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Icon_MetaData), NewProp_Icon_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_UseType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_UseType = { "UseType", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryItemDefinition, UseType), Z_Construct_UEnum_HoopRunners_EInventoryItemUseType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UseType_MetaData), NewProp_UseType_MetaData) }; // 1135634947
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventoryItemDefinition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_Icon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_UseType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemDefinition_Statics::NewProp_UseType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryItemDefinition_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInventoryItemDefinition_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryItemDefinition_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryItemDefinition_Statics::ClassParams = {
	&UInventoryItemDefinition::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInventoryItemDefinition_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryItemDefinition_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryItemDefinition_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryItemDefinition_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventoryItemDefinition()
{
	if (!Z_Registration_Info_UClass_UInventoryItemDefinition.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryItemDefinition.OuterSingleton, Z_Construct_UClass_UInventoryItemDefinition_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryItemDefinition.OuterSingleton;
}
UInventoryItemDefinition::UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryItemDefinition);
UInventoryItemDefinition::~UInventoryItemDefinition() {}
// ********** End Class UInventoryItemDefinition ***************************************************

// ********** Begin ScriptStruct FInventoryStack ***************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FInventoryStack;
class UScriptStruct* FInventoryStack::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FInventoryStack.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FInventoryStack.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FInventoryStack, (UObject*)Z_Construct_UPackage__Script_HoopRunners(), TEXT("InventoryStack"));
	}
	return Z_Registration_Info_UScriptStruct_FInventoryStack.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FInventoryStack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe5\x86\x85\xe3\x81\xae\xe4\xb8\x80\xe6\x9e\xa0\xe3\x81\xab\xe6\xa0\xbc\xe7\xb4\x8d\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xa8\xe5\x80\x8b\xe6\x95\xb0\xe3\x80\x82\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe5\x86\x85\xe3\x81\xae\xe4\xb8\x80\xe6\x9e\xa0\xe3\x81\xab\xe6\xa0\xbc\xe7\xb4\x8d\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x81\xa8\xe5\x80\x8b\xe6\x95\xb0\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Item_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x81\x93\xe3\x81\xae\xe6\x9e\xa0\xe3\x81\xab\xe6\xa0\xbc\xe7\xb4\x8d\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x81\x93\xe3\x81\xae\xe6\x9e\xa0\xe3\x81\xab\xe6\xa0\xbc\xe7\xb4\x8d\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Materials_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe6\x99\x82\xe3\x81\xab\xe5\x85\x83\xe3\x81\xae\xe8\xa6\x8b\xe3\x81\x9f\xe7\x9b\xae\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe6\x99\x82\xe3\x81\xab\xe5\x85\x83\xe3\x81\xae\xe8\xa6\x8b\xe3\x81\x9f\xe7\x9b\xae\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe3\x83\xa1\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldScale_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xbb\x96\xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe3\x82\x82\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe4\xbf\x9d\xe5\xad\x98\xe6\xb8\x88\xe3\x81\xbf\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbb\x96\xe3\x82\xaf\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe3\x82\x82\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\xe4\xbf\x9d\xe5\xad\x98\xe6\xb8\x88\xe3\x81\xbf\xe3\x83\x9e\xe3\x83\x86\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionRadius_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8f\x96\xe5\xbe\x97\xe3\x81\x97\xe3\x81\x9f\xe6\x99\x82\xe7\x82\xb9\xe3\x81\xae\xe8\xa1\xa8\xe7\xa4\xba\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\x96\xe5\xbe\x97\xe3\x81\x97\xe3\x81\x9f\xe6\x99\x82\xe7\x82\xb9\xe3\x81\xae\xe8\xa1\xa8\xe7\xa4\xba\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstanceId_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe5\xbe\x8c\xe3\x82\x82\xe5\x90\x8c\xe3\x81\x98\xe5\x8f\x96\xe5\xbe\x97\xe7\xaf\x84\xe5\x9b\xb2\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x89\xe3\x83\xad\xe3\x83\x83\xe3\x83\x97\xe5\xbe\x8c\xe3\x82\x82\xe5\x90\x8c\xe3\x81\x98\xe5\x8f\x96\xe5\xbe\x97\xe7\xaf\x84\xe5\x9b\xb2\xe3\x82\x92\xe5\xbe\xa9\xe5\x85\x83\xe3\x81\x99\xe3\x82\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Quantity_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x81\x85\xe5\xbb\xb6\xe3\x81\x97\xe3\x81\x9f\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\xa7\xe5\x88\xa5\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\x92\xe6\xb6\x88\xe8\xb2\xbb\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\x9f\xe3\x82\x81\xe3\x81\xae\xe8\xad\x98\xe5\x88\xa5\xe5\xad\x90\n" },
#endif
		{ "ModuleRelativePath", "Public/InventoryItemDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x81\x85\xe5\xbb\xb6\xe3\x81\x97\xe3\x81\x9f\xe6\x93\x8d\xe4\xbd\x9c\xe3\x81\xa7\xe5\x88\xa5\xe3\x81\xae\xe3\x82\xa2\xe3\x82\xa4\xe3\x83\x86\xe3\x83\xa0\xe3\x82\x92\xe6\xb6\x88\xe8\xb2\xbb\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\x9f\xe3\x82\x81\xe3\x81\xae\xe8\xad\x98\xe5\x88\xa5\xe5\xad\x90" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Item;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Materials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Materials;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InteractionRadius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Quantity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInventoryStack>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, Item), Z_Construct_UClass_UInventoryItemDefinition_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Item_MetaData), NewProp_Item_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, Mesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Materials_Inner = { "Materials", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Materials = { "Materials", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, Materials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Materials_MetaData), NewProp_Materials_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_WorldScale = { "WorldScale", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, WorldScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldScale_MetaData), NewProp_WorldScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_InteractionRadius = { "InteractionRadius", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, InteractionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionRadius_MetaData), NewProp_InteractionRadius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, InstanceId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstanceId_MetaData), NewProp_InstanceId_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Quantity = { "Quantity", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryStack, Quantity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Quantity_MetaData), NewProp_Quantity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FInventoryStack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Item,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Materials_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Materials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_WorldScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_InteractionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_InstanceId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryStack_Statics::NewProp_Quantity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryStack_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInventoryStack_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
	nullptr,
	&NewStructOps,
	"InventoryStack",
	Z_Construct_UScriptStruct_FInventoryStack_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryStack_Statics::PropPointers),
	sizeof(FInventoryStack),
	alignof(FInventoryStack),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryStack_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FInventoryStack_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FInventoryStack()
{
	if (!Z_Registration_Info_UScriptStruct_FInventoryStack.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FInventoryStack.InnerSingleton, Z_Construct_UScriptStruct_FInventoryStack_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FInventoryStack.InnerSingleton;
}
// ********** End ScriptStruct FInventoryStack *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EInventoryItemUseType_StaticEnum, TEXT("EInventoryItemUseType"), &Z_Registration_Info_UEnum_EInventoryItemUseType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1135634947U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FInventoryStack::StaticStruct, Z_Construct_UScriptStruct_FInventoryStack_Statics::NewStructOps, TEXT("InventoryStack"), &Z_Registration_Info_UScriptStruct_FInventoryStack, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FInventoryStack), 4242720339U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryItemDefinition, UInventoryItemDefinition::StaticClass, TEXT("UInventoryItemDefinition"), &Z_Registration_Info_UClass_UInventoryItemDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryItemDefinition), 1853557894U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_1721448615(TEXT("/Script/HoopRunners"),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h__Script_HoopRunners_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
