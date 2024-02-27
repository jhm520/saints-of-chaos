using UnrealBuildTool;

public class GASUtility : ModuleRules
{
	public GASUtility(ReadOnlyTargetRules Target) : base(Target)
	{

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		/*
		* Engine Modules
		*/
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
            "CoreUObject",
            "Engine",
            "Json",
            "JsonUtilities",
            "HTTP",
            "Slate",
            "SlateCore",
            "PlatformCrypto",
            "DeveloperSettings",
            "UMG",
            "AudioExtensions",
            "InputCore",
            "EnhancedInput"

            // This module should have no other dependencies other than the engine itself!
        });
		
		/*
		* Gameplay Ability System
		*/
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities",
			"GameplayTags", 
			"GameplayTasks"
		});
		
		PublicIncludePaths.Add("GASUtility");
		
		/*
		* Additional Project Dependencies
		*/
		PublicDependencyModuleNames.AddRange(new[]
		{
			// Utilities
			"CoreUtility"
		});
	}
}
