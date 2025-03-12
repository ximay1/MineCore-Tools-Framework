// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMineCore_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MineCore;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MineCore()
	{
		if (!Z_Registration_Info_UPackage__Script_MineCore.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/MineCore",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x4889B6C3,
				0xAAB3F953,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MineCore.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_MineCore.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MineCore(Z_Construct_UPackage__Script_MineCore, TEXT("/Script/MineCore"), Z_Registration_Info_UPackage__Script_MineCore, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x4889B6C3, 0xAAB3F953));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
