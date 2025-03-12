// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MineCore/Public/Actors/ResourceNodes/MC_ResourceNode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMC_ResourceNode() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FPrimaryAssetId();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
MINECORE_API UClass* Z_Construct_UClass_AMC_ResourceNode();
MINECORE_API UClass* Z_Construct_UClass_AMC_ResourceNode_NoRegister();
MINECORE_API UClass* Z_Construct_UClass_UMC_ResourceNodeConfig_NoRegister();
MINECORE_API UEnum* Z_Construct_UEnum_MineCore_EResourceNodeState();
MINECORE_API UEnum* Z_Construct_UEnum_MineCore_EResourceNodeType();
UPackage* Z_Construct_UPackage__Script_MineCore();
// End Cross Module References

// Begin Enum EResourceNodeState
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EResourceNodeState;
static UEnum* EResourceNodeState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EResourceNodeState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EResourceNodeState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MineCore_EResourceNodeState, (UObject*)Z_Construct_UPackage__Script_MineCore(), TEXT("EResourceNodeState"));
	}
	return Z_Registration_Info_UEnum_EResourceNodeState.OuterSingleton;
}
template<> MINECORE_API UEnum* StaticEnum<EResourceNodeState>()
{
	return EResourceNodeState_StaticEnum();
}
struct Z_Construct_UEnum_MineCore_EResourceNodeState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
		{ "NONE.DisplayName", "No Resources" },
		{ "NONE.Name", "EResourceNodeState::NONE" },
		{ "STATE_1.Comment", "// No resources available\n" },
		{ "STATE_1.DisplayName", "State 1" },
		{ "STATE_1.Name", "EResourceNodeState::STATE_1" },
		{ "STATE_1.ToolTip", "No resources available" },
		{ "STATE_2.DisplayName", "State 2" },
		{ "STATE_2.Name", "EResourceNodeState::STATE_2" },
		{ "STATE_3.DisplayName", "State 3" },
		{ "STATE_3.Name", "EResourceNodeState::STATE_3" },
		{ "STATE_4.DisplayName", "State 4" },
		{ "STATE_4.Name", "EResourceNodeState::STATE_4" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EResourceNodeState::NONE", (int64)EResourceNodeState::NONE },
		{ "EResourceNodeState::STATE_1", (int64)EResourceNodeState::STATE_1 },
		{ "EResourceNodeState::STATE_2", (int64)EResourceNodeState::STATE_2 },
		{ "EResourceNodeState::STATE_3", (int64)EResourceNodeState::STATE_3 },
		{ "EResourceNodeState::STATE_4", (int64)EResourceNodeState::STATE_4 },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MineCore,
	nullptr,
	"EResourceNodeState",
	"EResourceNodeState",
	Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MineCore_EResourceNodeState()
{
	if (!Z_Registration_Info_UEnum_EResourceNodeState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EResourceNodeState.InnerSingleton, Z_Construct_UEnum_MineCore_EResourceNodeState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EResourceNodeState.InnerSingleton;
}
// End Enum EResourceNodeState

// Begin Enum EResourceNodeType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EResourceNodeType;
static UEnum* EResourceNodeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EResourceNodeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EResourceNodeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MineCore_EResourceNodeType, (UObject*)Z_Construct_UPackage__Script_MineCore(), TEXT("EResourceNodeType"));
	}
	return Z_Registration_Info_UEnum_EResourceNodeType.OuterSingleton;
}
template<> MINECORE_API UEnum* StaticEnum<EResourceNodeType>()
{
	return EResourceNodeType_StaticEnum();
}
struct Z_Construct_UEnum_MineCore_EResourceNodeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "COAL.DisplayName", "Coal" },
		{ "COAL.Name", "EResourceNodeType::COAL" },
		{ "CRYSTALS.DisplayName", "Crystals" },
		{ "CRYSTALS.Name", "EResourceNodeType::CRYSTALS" },
		{ "DEFAULT.DisplayName", "Default" },
		{ "DEFAULT.Name", "EResourceNodeType::DEFAULT" },
		{ "GEMSTONE.DisplayName", "Gemstone" },
		{ "GEMSTONE.Name", "EResourceNodeType::GEMSTONE" },
		{ "GOLD.DisplayName", "Gold" },
		{ "GOLD.Name", "EResourceNodeType::GOLD" },
		{ "GRANITE.DisplayName", "Granite" },
		{ "GRANITE.Name", "EResourceNodeType::GRANITE" },
		{ "IRON.DisplayName", "Iron" },
		{ "IRON.Name", "EResourceNodeType::IRON" },
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
		{ "SILVER.DisplayName", "Silver" },
		{ "SILVER.Name", "EResourceNodeType::SILVER" },
		{ "STONE.DisplayName", "Stone" },
		{ "STONE.Name", "EResourceNodeType::STONE" },
		{ "TITANIUM.DisplayName", "Titanium" },
		{ "TITANIUM.Name", "EResourceNodeType::TITANIUM" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EResourceNodeType::DEFAULT", (int64)EResourceNodeType::DEFAULT },
		{ "EResourceNodeType::STONE", (int64)EResourceNodeType::STONE },
		{ "EResourceNodeType::GRANITE", (int64)EResourceNodeType::GRANITE },
		{ "EResourceNodeType::COAL", (int64)EResourceNodeType::COAL },
		{ "EResourceNodeType::IRON", (int64)EResourceNodeType::IRON },
		{ "EResourceNodeType::SILVER", (int64)EResourceNodeType::SILVER },
		{ "EResourceNodeType::GOLD", (int64)EResourceNodeType::GOLD },
		{ "EResourceNodeType::GEMSTONE", (int64)EResourceNodeType::GEMSTONE },
		{ "EResourceNodeType::CRYSTALS", (int64)EResourceNodeType::CRYSTALS },
		{ "EResourceNodeType::TITANIUM", (int64)EResourceNodeType::TITANIUM },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MineCore,
	nullptr,
	"EResourceNodeType",
	"EResourceNodeType",
	Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MineCore_EResourceNodeType()
{
	if (!Z_Registration_Info_UEnum_EResourceNodeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EResourceNodeType.InnerSingleton, Z_Construct_UEnum_MineCore_EResourceNodeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EResourceNodeType.InnerSingleton;
}
// End Enum EResourceNodeType

// Begin Class AMC_ResourceNode Function ResourceNode_Refresh
struct Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Function called by the timer to refresh the resource node and increment its state. */" },
#endif
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Function called by the timer to refresh the resource node and increment its state." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMC_ResourceNode, nullptr, "ResourceNode_Refresh", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMC_ResourceNode::execResourceNode_Refresh)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResourceNode_Refresh();
	P_NATIVE_END;
}
// End Class AMC_ResourceNode Function ResourceNode_Refresh

// Begin Class AMC_ResourceNode
void AMC_ResourceNode::StaticRegisterNativesAMC_ResourceNode()
{
	UClass* Class = AMC_ResourceNode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ResourceNode_Refresh", &AMC_ResourceNode::execResourceNode_Refresh },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMC_ResourceNode);
UClass* Z_Construct_UClass_AMC_ResourceNode_NoRegister()
{
	return AMC_ResourceNode::StaticClass();
}
struct Z_Construct_UClass_AMC_ResourceNode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Actors/ResourceNodes/MC_ResourceNode.h" },
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResourceNodeState_MetaData[] = {
		{ "Category", "Resource Node" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current state of the resource node */" },
#endif
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current state of the resource node" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResourceNodeConfigId_MetaData[] = {
		{ "Category", "PrimaryAssetLoaderComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Asset Id for the resource node configuration */" },
#endif
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Asset Id for the resource node configuration" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResourceNodeConfigPtr_MetaData[] = {
		{ "Category", "Resource Node | Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pointer to the resource node configuration */" },
#endif
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pointer to the resource node configuration" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMesh_MetaData[] = {
		{ "Category", "Resource Node" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Static mesh component representing the resource node */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Actors/ResourceNodes/MC_ResourceNode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Static mesh component representing the resource node" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ResourceNodeState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ResourceNodeState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ResourceNodeConfigId;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResourceNodeConfigPtr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StaticMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMC_ResourceNode_ResourceNode_Refresh, "ResourceNode_Refresh" }, // 3423567233
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMC_ResourceNode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeState = { "ResourceNodeState", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMC_ResourceNode, ResourceNodeState), Z_Construct_UEnum_MineCore_EResourceNodeState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResourceNodeState_MetaData), NewProp_ResourceNodeState_MetaData) }; // 4175797872
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeConfigId = { "ResourceNodeConfigId", nullptr, (EPropertyFlags)0x0020080000010005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMC_ResourceNode, ResourceNodeConfigId), Z_Construct_UScriptStruct_FPrimaryAssetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResourceNodeConfigId_MetaData), NewProp_ResourceNodeConfigId_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeConfigPtr = { "ResourceNodeConfigPtr", nullptr, (EPropertyFlags)0x0124080000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMC_ResourceNode, ResourceNodeConfigPtr), Z_Construct_UClass_UMC_ResourceNodeConfig_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResourceNodeConfigPtr_MetaData), NewProp_ResourceNodeConfigPtr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_StaticMesh = { "StaticMesh", nullptr, (EPropertyFlags)0x012408000009001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMC_ResourceNode, StaticMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMesh_MetaData), NewProp_StaticMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMC_ResourceNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeConfigId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_ResourceNodeConfigPtr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMC_ResourceNode_Statics::NewProp_StaticMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMC_ResourceNode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMC_ResourceNode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MineCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMC_ResourceNode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMC_ResourceNode_Statics::ClassParams = {
	&AMC_ResourceNode::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMC_ResourceNode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMC_ResourceNode_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMC_ResourceNode_Statics::Class_MetaDataParams), Z_Construct_UClass_AMC_ResourceNode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMC_ResourceNode()
{
	if (!Z_Registration_Info_UClass_AMC_ResourceNode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMC_ResourceNode.OuterSingleton, Z_Construct_UClass_AMC_ResourceNode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMC_ResourceNode.OuterSingleton;
}
template<> MINECORE_API UClass* StaticClass<AMC_ResourceNode>()
{
	return AMC_ResourceNode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMC_ResourceNode);
AMC_ResourceNode::~AMC_ResourceNode() {}
// End Class AMC_ResourceNode

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EResourceNodeState_StaticEnum, TEXT("EResourceNodeState"), &Z_Registration_Info_UEnum_EResourceNodeState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4175797872U) },
		{ EResourceNodeType_StaticEnum, TEXT("EResourceNodeType"), &Z_Registration_Info_UEnum_EResourceNodeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1870924318U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMC_ResourceNode, AMC_ResourceNode::StaticClass, TEXT("AMC_ResourceNode"), &Z_Registration_Info_UClass_AMC_ResourceNode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMC_ResourceNode), 3906639381U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_3054366284(TEXT("/Script/MineCore"),
	Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Actors_ResourceNodes_MC_ResourceNode_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
