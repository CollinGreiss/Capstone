// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class Capstone : ModuleRules
{
	public Capstone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange( new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Http", "Json", "JsonUtilities" } );


        PrivateDependencyModuleNames.AddRange(new string[] {  });


        string VcpkgPath = "C:/tools/vcpkg/installed/x64-windows";

        PublicSystemIncludePaths.Add( Path.Combine( VcpkgPath, "include" ) );
        PublicAdditionalLibraries.Add( Path.Combine( VcpkgPath, "lib", "libcrypto.lib" ) );

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

    }
}
