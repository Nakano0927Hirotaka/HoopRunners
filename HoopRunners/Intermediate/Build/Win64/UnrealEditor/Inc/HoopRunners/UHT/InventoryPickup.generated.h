// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InventoryPickup.h"

#ifdef HOOPRUNNERS_InventoryPickup_generated_h
#error "InventoryPickup.generated.h already included, missing '#pragma once' in InventoryPickup.h"
#endif
#define HOOPRUNNERS_InventoryPickup_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;
class UInventoryComponent;
class UPrimitiveComponent;
struct FHitResult;

// ********** Begin Class AInventoryPickup *********************************************************
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnVolumeEndOverlap); \
	DECLARE_FUNCTION(execOnVolumeBeginOverlap); \
	DECLARE_FUNCTION(execOnRep_Appearance); \
	DECLARE_FUNCTION(execInteract);


HOOPRUNNERS_API UClass* Z_Construct_UClass_AInventoryPickup_NoRegister();

#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInventoryPickup(); \
	friend struct Z_Construct_UClass_AInventoryPickup_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend HOOPRUNNERS_API UClass* Z_Construct_UClass_AInventoryPickup_NoRegister(); \
public: \
	DECLARE_CLASS2(AInventoryPickup, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HoopRunners"), Z_Construct_UClass_AInventoryPickup_NoRegister) \
	DECLARE_SERIALIZER(AInventoryPickup) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ItemDefinition=NETFIELD_REP_START, \
		PickupMesh, \
		PickupMaterials, \
		PickupScale, \
		PickupInteractionRadius, \
		NETFIELD_REP_END=PickupInteractionRadius	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInventoryPickup(AInventoryPickup&&) = delete; \
	AInventoryPickup(const AInventoryPickup&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInventoryPickup); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInventoryPickup); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInventoryPickup) \
	NO_API virtual ~AInventoryPickup();


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_14_PROLOG
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_INCLASS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInventoryPickup;

// ********** End Class AInventoryPickup ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_InventoryPickup_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
