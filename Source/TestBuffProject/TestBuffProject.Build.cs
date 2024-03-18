// Test Buff Project. All Rights Reserved.

using UnrealBuildTool;

public class TestBuffProject : ModuleRules
{
	public TestBuffProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "HeadMountedDisplay", "UMG", "Niagara", "GameplayTags" });
		PublicIncludePaths.AddRange(new string[] { "TestBuffProject"});
	}
}
