// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MonsterSlave : ModuleRules
{
	public MonsterSlave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Paper2D",
			"InputCore",
			"HeadMountedDisplay",
			"UMG",
			"OnlineSubSystem",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"Niagara",
		});



	}
}
