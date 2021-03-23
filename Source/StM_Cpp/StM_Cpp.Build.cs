// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StM_Cpp : ModuleRules
{
	public StM_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

