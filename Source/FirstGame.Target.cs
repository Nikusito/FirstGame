// First Game

using UnrealBuildTool;
using System.Collections.Generic;

public class FirstGameTarget : TargetRules
{
	public FirstGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "FirstGame" } );
	}
}
