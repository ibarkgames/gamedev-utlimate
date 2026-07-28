// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamedevUltimate : ModuleRules
{
	public GamedevUltimate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });

		PublicIncludePaths.AddRange(new string[] {
			"GamedevUltimate",
			"GamedevUltimate/Variant_Horror",
			"GamedevUltimate/Variant_Horror/UI",
			"GamedevUltimate/Variant_Shooter",
			"GamedevUltimate/Variant_Shooter/AI",
			"GamedevUltimate/Variant_Shooter/UI",
			"GamedevUltimate/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
