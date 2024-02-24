using UnrealBuildTool;

public class CoreUtility : ModuleRules
{
	public CoreUtility(ReadOnlyTargetRules Target) : base(Target)
	{

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		/*
		* Engine Modules
		*/
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"NetCore",
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
            "EnhancedInput",
            "InputCore",
            
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
		
		//PublicIncludePaths.Add("CoreUtility");
	}
}
