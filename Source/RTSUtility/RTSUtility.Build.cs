using UnrealBuildTool;

public class RTSUtility : ModuleRules
{
	public RTSUtility(ReadOnlyTargetRules Target) : base(Target)
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
            "CoreUtility",
            "GASUtility"
		});
				
		
		/*
		* Gameplay Ability System
		*/
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities",
			"GameplayTags", 
			"GameplayTasks",
			"EnhancedInput"
		});
		
		//PublicIncludePaths.Add("CoreUtility");
	}
}
