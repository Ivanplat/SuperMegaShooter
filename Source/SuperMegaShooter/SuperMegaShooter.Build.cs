// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SuperMegaShooter : ModuleRules
{
	public SuperMegaShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"Slate",
			"SlateCore",
			"OnlineSubsystem" 
		});

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
