// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MineCore : ModuleRules
{
	public MineCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"Json",
				"JsonUtilities",
				"AssetRegistry",
				"DeveloperSettings",
				"CommonUI"
			}
			);
	}
}
