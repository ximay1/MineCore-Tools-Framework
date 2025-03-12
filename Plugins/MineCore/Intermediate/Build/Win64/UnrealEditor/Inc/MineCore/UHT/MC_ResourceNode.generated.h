// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MINECORE_MC_ResourceNode_generated_h
#error "MC_ResourceNode.generated.h already included, missing '#pragma once' in MC_ResourceNode.h"
#endif
#define MINECORE_MC_ResourceNode_generated_h

#define FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execResourceNode_Refresh);


#define FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMC_ResourceNode(); \
	friend struct Z_Construct_UClass_AMC_ResourceNode_Statics; \
public: \
	DECLARE_CLASS(AMC_ResourceNode, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MineCore"), NO_API) \
	DECLARE_SERIALIZER(AMC_ResourceNode)


#define FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMC_ResourceNode(AMC_ResourceNode&&); \
	AMC_ResourceNode(const AMC_ResourceNode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMC_ResourceNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMC_ResourceNode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMC_ResourceNode) \
	NO_API virtual ~AMC_ResourceNode();


#define FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_35_PROLOG
#define FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_INCLASS_NO_PURE_DECLS \
	FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_38_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MINECORE_API UClass* StaticClass<class AMC_ResourceNode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h


#define FOREACH_ENUM_ERESOURCENODESTATE(op) \
	op(EResourceNodeState::NONE) \
	op(EResourceNodeState::STATE_1) \
	op(EResourceNodeState::STATE_2) \
	op(EResourceNodeState::STATE_3) \
	op(EResourceNodeState::STATE_4) 

enum class EResourceNodeState : uint8;
template<> struct TIsUEnumClass<EResourceNodeState> { enum { Value = true }; };
template<> MINECORE_API UEnum* StaticEnum<EResourceNodeState>();

#define FOREACH_ENUM_ERESOURCENODETYPE(op) \
	op(EResourceNodeType::DEFAULT) \
	op(EResourceNodeType::STONE) \
	op(EResourceNodeType::GRANITE) \
	op(EResourceNodeType::COAL) \
	op(EResourceNodeType::IRON) \
	op(EResourceNodeType::SILVER) \
	op(EResourceNodeType::GOLD) \
	op(EResourceNodeType::GEMSTONE) \
	op(EResourceNodeType::CRYSTALS) \
	op(EResourceNodeType::TITANIUM) 

enum class EResourceNodeType : uint8;
template<> struct TIsUEnumClass<EResourceNodeType> { enum { Value = true }; };
template<> MINECORE_API UEnum* StaticEnum<EResourceNodeType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
