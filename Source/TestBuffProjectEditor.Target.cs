// Test Buff Project. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TestBuffProjectEditorTarget : TargetRules
{
	public TestBuffProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("TestBuffProject");
	}
}
