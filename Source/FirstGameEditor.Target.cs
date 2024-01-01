// First Game

using UnrealBuildTool;
using System.Collections.Generic;

public class FirstGameEditorTarget : TargetRules
{
	public FirstGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "FirstGame" } );
	}
}
