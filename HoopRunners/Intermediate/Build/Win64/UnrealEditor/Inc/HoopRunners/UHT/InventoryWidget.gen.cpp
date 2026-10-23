// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInventoryWidget() {}

// ********** Begin Cross Module References ********************************************************
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryWidget();
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UBorder_NoRegister();
UMG_API UClass* Z_Construct_UClass_UHorizontalBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_HoopRunners();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInventoryWidget *********************************************************
void UInventoryWidget::StaticRegisterNativesUInventoryWidget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UInventoryWidget;
UClass* UInventoryWidget::GetPrivateStaticClass()
{
	using TClass = UInventoryWidget;
	if (!Z_Registration_Info_UClass_UInventoryWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InventoryWidget"),
			Z_Registration_Info_UClass_UInventoryWidget.InnerSingleton,
			StaticRegisterNativesUInventoryWidget,
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
	return Z_Registration_Info_UClass_UInventoryWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventoryWidget_NoRegister()
{
	return UInventoryWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventoryWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 3\xe6\x9e\xa0\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe3\x81\xa8\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f""EMP\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\xae\xe6\x93\x8d\xe4\xbd\x9c\xe6\xa1\x88\xe5\x86\x85\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8bHUD\xe3\x80\x82\n" },
#endif
		{ "IncludePath", "InventoryWidget.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/InventoryWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "3\xe6\x9e\xa0\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x99\xe3\x83\xb3\xe3\x83\x88\xe3\x83\xaa\xe3\x81\xa8\xe5\x8f\x96\xe5\xbe\x97\xef\xbc\x8f""EMP\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\xae\xe6\x93\x8d\xe4\xbd\x9c\xe6\xa1\x88\xe5\x86\x85\xe3\x82\x92\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x99\xe3\x82\x8bHUD\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventorySlots_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupPromptBackground_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActionPromptText_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InventorySlots;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PickupPromptBackground;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActionPromptText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventoryWidget_Statics::NewProp_InventorySlots = { "InventorySlots", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryWidget, InventorySlots), Z_Construct_UClass_UHorizontalBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventorySlots_MetaData), NewProp_InventorySlots_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventoryWidget_Statics::NewProp_PickupPromptBackground = { "PickupPromptBackground", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryWidget, PickupPromptBackground), Z_Construct_UClass_UBorder_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupPromptBackground_MetaData), NewProp_PickupPromptBackground_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventoryWidget_Statics::NewProp_ActionPromptText = { "ActionPromptText", nullptr, (EPropertyFlags)0x0144000000082008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryWidget, ActionPromptText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActionPromptText_MetaData), NewProp_ActionPromptText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventoryWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryWidget_Statics::NewProp_InventorySlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryWidget_Statics::NewProp_PickupPromptBackground,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryWidget_Statics::NewProp_ActionPromptText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInventoryWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_HoopRunners,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryWidget_Statics::ClassParams = {
	&UInventoryWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInventoryWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventoryWidget()
{
	if (!Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton, Z_Construct_UClass_UInventoryWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton;
}
UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryWidget);
UInventoryWidget::~UInventoryWidget() {}
// ********** End Class UInventoryWidget ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryWidget_h__Script_HoopRunners_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryWidget, UInventoryWidget::StaticClass, TEXT("UInventoryWidget"), &Z_Registration_Info_UClass_UInventoryWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryWidget), 2459377541U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryWidget_h__Script_HoopRunners_2200440437(TEXT("/Script/HoopRunners"),
	Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryWidget_h__Script_HoopRunners_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryWidget_h__Script_HoopRunners_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
