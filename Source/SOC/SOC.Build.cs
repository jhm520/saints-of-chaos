// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SOC : ModuleRules
{
	public SOC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"Sockets", 
			"WhatsMyPublicIP", 
			"SOCAI", 
			"GameplayAbilities", 
			"GameplayTasks",
			"GameplayTags",
			"AIModule",
			"UMG",
			"CommonUI"
		});

		//Plugins
        PublicDependencyModuleNames.AddRange(new string[] { });
        
        //Extra Modules
        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "CoreUtility", 
	        "GASUtility",
	        "AggroSystem",
			"RTSUtility",
			"SelectionSystem"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
