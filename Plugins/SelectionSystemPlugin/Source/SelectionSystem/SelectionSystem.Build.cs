using UnrealBuildTool;

public class SelectionSystem : ModuleRules
{
	public SelectionSystem(ReadOnlyTargetRules Target) : base(Target)
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
			"GameplayTags"
		});
		
		//PublicIncludePaths.Add("CoreUtility");
	}
}
