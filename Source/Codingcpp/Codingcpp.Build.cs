// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Codingcpp : ModuleRules
{
    public Codingcpp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Codingcpp.h";

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput", 
            "AnimationCore",      // for AnimInstance
            "AnimGraphRuntime",    // if you ever use graph‐driven nodes
            "Niagara",
            "UMG"
        });

        // If you use any BlueprintLibrary math calls:
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Kismet",
            "Niagara"
        });
    }
}