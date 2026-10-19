// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InventoryComponent.h"

#ifdef HOOPRUNNERS_InventoryComponent_generated_h
#error "InventoryComponent.generated.h already included, missing '#pragma once' in InventoryComponent.h"
#endif
#define HOOPRUNNERS_InventoryComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AInventoryPickup;
class UInventoryItemDefinition;
enum class EInventoryNetworkAction : uint8;
struct FGuid;
struct FInventoryStack;

// ********** Begin Delegate FInventoryChanged *****************************************************
#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_12_DELEGATE \
HOOPRUNNERS_API void FInventoryChanged_DelegateWrapper(const FMulticastScriptDelegate& InventoryChanged, TArray<FInventoryStack> const& Items);


// ********** End Delegate FInventoryChanged *******************************************************

// ********** Begin Class UInventoryComponent ******************************************************
#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerPerformAction_Implementation(EInventoryNetworkAction Action, AInventoryPickup* Pickup, FGuid InstanceId, int32 ExpectedQuantity); \
	DECLARE_FUNCTION(execOnRep_Items); \
	DECLARE_FUNCTION(execServerPerformAction); \
	DECLARE_FUNCTION(execGetItems); \
	DECLARE_FUNCTION(execAddItem); \
	DECLARE_FUNCTION(execGetSelectedSlotIndex); \
	DECLARE_FUNCTION(execDropSelectedItem); \
	DECLARE_FUNCTION(execCycleSelection); \
	DECLARE_FUNCTION(execTryInteract);


#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_CALLBACK_WRAPPERS
HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister();

#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct Z_Construct_UClass_UInventoryComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend HOOPRUNNERS_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HoopRunners"), Z_Construct_UClass_UInventoryComponent_NoRegister) \
	DECLARE_SERIALIZER(UInventoryComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		Items=NETFIELD_REP_START, \
		NETFIELD_REP_END=Items	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryComponent(UInventoryComponent&&) = delete; \
	UInventoryComponent(const UInventoryComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventoryComponent) \
	NO_API virtual ~UInventoryComponent();


#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_25_PROLOG
#define FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_CALLBACK_WRAPPERS \
	FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryComponent;

// ********** End Class UInventoryComponent ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_ydauser01_Documents__git_HoopRunner_HoopRunners_Source_HoopRunners_Public_InventoryComponent_h

// ********** Begin Enum EInventoryNetworkAction ***************************************************
#define FOREACH_ENUM_EINVENTORYNETWORKACTION(op) \
	op(EInventoryNetworkAction::Pickup) \
	op(EInventoryNetworkAction::Consume) \
	op(EInventoryNetworkAction::EMP) \
	op(EInventoryNetworkAction::Drop) 

enum class EInventoryNetworkAction : uint8;
template<> struct TIsUEnumClass<EInventoryNetworkAction> { enum { Value = true }; };
template<> HOOPRUNNERS_API UEnum* StaticEnum<EInventoryNetworkAction>();
// ********** End Enum EInventoryNetworkAction *****************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
