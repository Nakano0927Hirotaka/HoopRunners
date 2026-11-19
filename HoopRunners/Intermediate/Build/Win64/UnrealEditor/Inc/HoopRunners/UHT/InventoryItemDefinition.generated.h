// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InventoryItemDefinition.h"

#ifdef HOOPRUNNERS_InventoryItemDefinition_generated_h
#error "InventoryItemDefinition.generated.h already included, missing '#pragma once' in InventoryItemDefinition.h"
#endif
#define HOOPRUNNERS_InventoryItemDefinition_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UInventoryItemDefinition *************************************************
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister();

#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryItemDefinition(); \
	friend struct Z_Construct_UClass_UInventoryItemDefinition_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryItemDefinition_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryItemDefinition, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HoopRunners"), Z_Construct_UClass_UInventoryItemDefinition_NoRegister) \
	DECLARE_SERIALIZER(UInventoryItemDefinition)


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_22_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryItemDefinition(UInventoryItemDefinition&&) = delete; \
	UInventoryItemDefinition(const UInventoryItemDefinition&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryItemDefinition); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryItemDefinition); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryItemDefinition) \
	NO_API virtual ~UInventoryItemDefinition();


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_19_PROLOG
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryItemDefinition;

// ********** End Class UInventoryItemDefinition ***************************************************

// ********** Begin ScriptStruct FInventoryStack ***************************************************
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h_45_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInventoryStack_Statics; \
	HOOPRUNNERS_API static class UScriptStruct* StaticStruct();


struct FInventoryStack;
// ********** End ScriptStruct FInventoryStack *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryItemDefinition_h

// ********** Begin Enum EInventoryItemUseType *****************************************************
#define FOREACH_ENUM_EINVENTORYITEMUSETYPE(op) \
	op(EInventoryItemUseType::None) \
	op(EInventoryItemUseType::EMP) 

enum class EInventoryItemUseType : uint8;
template<> struct TIsUEnumClass<EInventoryItemUseType> { enum { Value = true }; };
template<> HOOPRUNNERS_API UEnum* StaticEnum<EInventoryItemUseType>();
// ********** End Enum EInventoryItemUseType *******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
