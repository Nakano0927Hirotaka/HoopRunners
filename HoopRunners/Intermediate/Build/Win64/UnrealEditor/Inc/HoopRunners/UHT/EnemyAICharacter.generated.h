// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EnemyAICharacter.h"

#ifdef HOOPRUNNERS_EnemyAICharacter_generated_h
#error "EnemyAICharacter.generated.h already included, missing '#pragma once' in EnemyAICharacter.h"
#endif
#define HOOPRUNNERS_EnemyAICharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

enum class EEnemyAIState : uint8;

// ********** Begin Class AEnemyAICharacter ********************************************************
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_CurrentState); \
	DECLARE_FUNCTION(execApplyEMPStun); \
	DECLARE_FUNCTION(execGetAIState);


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_CALLBACK_WRAPPERS
HOOPRUNNERS_API UClass* Z_Construct_UClass_AEnemyAICharacter_NoRegister();

#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyAICharacter(); \
	friend struct Z_Construct_UClass_AEnemyAICharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend HOOPRUNNERS_API UClass* Z_Construct_UClass_AEnemyAICharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AEnemyAICharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HoopRunners"), Z_Construct_UClass_AEnemyAICharacter_NoRegister) \
	DECLARE_SERIALIZER(AEnemyAICharacter) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentState=NETFIELD_REP_START, \
		NETFIELD_REP_END=CurrentState	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEnemyAICharacter(AEnemyAICharacter&&) = delete; \
	AEnemyAICharacter(const AEnemyAICharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyAICharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyAICharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyAICharacter) \
	NO_API virtual ~AEnemyAICharacter();


#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_18_PROLOG
#define FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_CALLBACK_WRAPPERS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEnemyAICharacter;

// ********** End Class AEnemyAICharacter **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_ydauser01_Documents__git_HoopRun_HoopRunners_Source_HoopRunners_Public_EnemyAICharacter_h

// ********** Begin Enum EEnemyAIState *************************************************************
#define FOREACH_ENUM_EENEMYAISTATE(op) \
	op(EEnemyAIState::Patrolling) \
	op(EEnemyAIState::Chasing) \
	op(EEnemyAIState::FinalChase) \
	op(EEnemyAIState::Stunned) 

enum class EEnemyAIState : uint8;
template<> struct TIsUEnumClass<EEnemyAIState> { enum { Value = true }; };
template<> HOOPRUNNERS_API UEnum* StaticEnum<EEnemyAIState>();
// ********** End Enum EEnemyAIState ***************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
