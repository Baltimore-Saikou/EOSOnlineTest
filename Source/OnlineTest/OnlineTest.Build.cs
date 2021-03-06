// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnlineTest : ModuleRules
{
	public OnlineTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"HeadMountedDisplay", 
				"NavigationSystem", 
				"AIModule", 
				"Niagara", 
				"GameplayAbilities" 
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"EnhancedInput",
			}
		);
    }
}
