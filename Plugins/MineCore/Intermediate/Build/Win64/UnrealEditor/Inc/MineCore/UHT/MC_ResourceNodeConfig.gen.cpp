// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MineCore/Public/Data/ResourceNode/MC_ResourceNodeConfig.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMC_ResourceNodeConfig() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
MINECORE_API UClass* Z_Construct_UClass_UMC_ResourceNodeConfig();
MINECORE_API UClass* Z_Construct_UClass_UMC_ResourceNodeConfig_NoRegister();
MINECORE_API UEnum* Z_Construct_UEnum_MineCore_EResourceNodeState();
MINECORE_API UEnum* Z_Construct_UEnum_MineCore_EResourceNodeType();
UPackage* Z_Construct_UPackage__Script_MineCore();
// End Cross Module References

// Begin Class UMC_ResourceNodeConfig
void UMC_ResourceNodeConfig::StaticRegisterNativesUMC_ResourceNodeConfig()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMC_ResourceNodeConfig);
UClass* Z_Construct_UClass_UMC_ResourceNodeConfig_NoRegister()
{
	return UMC_ResourceNodeConfig::StaticClass();
}
struct Z_Construct_UClass_UMC_ResourceNodeConfig_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Data/ResourceNode/MC_ResourceNodeConfig.h" },
		{ "ModuleRelativePath", "Public/Data/ResourceNode/MC_ResourceNodeConfig.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResourceNodeMaterials_MetaData[] = {
		{ "Category", "Resource Node | Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A TMap that associates each resource node state (EResourceNodeState) with a material (UMaterial*).  \n// Used to dynamically assign the appropriate material based on the resource node's current state.  \n" },
#endif
		{ "ModuleRelativePath", "Public/Data/ResourceNode/MC_ResourceNodeConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A TMap that associates each resource node state (EResourceNodeState) with a material (UMaterial*).\nUsed to dynamically assign the appropriate material based on the resource node's current state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeToIncreaseState_MetaData[] = {
		{ "Category", "Resource Node | Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Time interval (in seconds) to increase the state by 1.\n" },
#endif
		{ "ModuleRelativePath", "Public/Data/ResourceNode/MC_ResourceNodeConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time interval (in seconds) to increase the state by 1." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResourceNodeType_MetaData[] = {
		{ "Category", "Resource Node | Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Type of the resource node\n" },
#endif
		{ "ModuleRelativePath", "Public/Data/ResourceNode/MC_ResourceNodeConfig.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of the resource node" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResourceNodeMaterials_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ResourceNodeMaterials_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ResourceNodeMaterials_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ResourceNodeMaterials;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeToIncreaseState;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ResourceNodeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ResourceNodeType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMC_ResourceNodeConfig>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_ValueProp = { "ResourceNodeMaterials", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_Key_KeyProp = { "ResourceNodeMaterials_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_MineCore_EResourceNodeState, METADATA_PARAMS(0, nullptr) }; // 4175797872
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials = { "ResourceNodeMaterials", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMC_ResourceNodeConfig, ResourceNodeMaterials), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResourceNodeMaterials_MetaData), NewProp_ResourceNodeMaterials_MetaData) }; // 4175797872
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_TimeToIncreaseState = { "TimeToIncreaseState", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMC_ResourceNodeConfig, TimeToIncreaseState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeToIncreaseState_MetaData), NewProp_TimeToIncreaseState_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeType = { "ResourceNodeType", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMC_ResourceNodeConfig, ResourceNodeType), Z_Construct_UEnum_MineCore_EResourceNodeType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResourceNodeType_MetaData), NewProp_ResourceNodeType_MetaData) }; // 1870924318
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeMaterials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_TimeToIncreaseState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::NewProp_ResourceNodeType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_MineCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::ClassParams = {
	&UMC_ResourceNodeConfig::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::Class_MetaDataParams), Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMC_ResourceNodeConfig()
{
	if (!Z_Registration_Info_UClass_UMC_ResourceNodeConfig.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMC_ResourceNodeConfig.OuterSingleton, Z_Construct_UClass_UMC_ResourceNodeConfig_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMC_ResourceNodeConfig.OuterSingleton;
}
template<> MINECORE_API UClass* StaticClass<UMC_ResourceNodeConfig>()
{
	return UMC_ResourceNodeConfig::StaticClass();
}
UMC_ResourceNodeConfig::UMC_ResourceNodeConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMC_ResourceNodeConfig);
UMC_ResourceNodeConfig::~UMC_ResourceNodeConfig() {}
// End Class UMC_ResourceNodeConfig

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Data_ResourceNode_MC_ResourceNodeConfig_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMC_ResourceNodeConfig, UMC_ResourceNodeConfig::StaticClass, TEXT("UMC_ResourceNodeConfig"), &Z_Registration_Info_UClass_UMC_ResourceNodeConfig, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMC_ResourceNodeConfig), 4284811515U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Data_ResourceNode_MC_ResourceNodeConfig_h_1790441868(TEXT("/Script/MineCore"),
	Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Data_ResourceNode_MC_ResourceNodeConfig_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_5_Projects_Projects_MCTF_Plugins_MineCore_Source_MineCore_Public_Data_ResourceNode_MC_ResourceNodeConfig_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
