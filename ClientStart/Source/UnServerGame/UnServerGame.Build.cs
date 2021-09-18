// Copyright Epic Games, Inc. All Rights Reserved.

// using 은 c#에서 #include라고 보면 됩니다.
using System.IO;
using UnrealBuildTool;

public class UnServerGame : ModuleRules
{
	public UnServerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Sockets", "Networking", "Slate", "SlateCore" });

		PublicDefinitions.Add("UNREALDEFINE=1");

		// 언리얼의 라이브러리와 헤더를 지정해주는 c#프로그램에
		// 자신의 코드를 쳐서 라이브러리나 헤더를 추가하는 방식입니다.
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
			string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../ServerStart/"));
            {
                string InclduePath = ThirdPartyPath + "GameEngineBase/";
                PublicIncludePaths.Add(InclduePath);
            }

			{
				string InclduePath = ThirdPartyPath + "GameEngineNet/";
				PublicIncludePaths.Add(InclduePath);
			}

			{
				string InclduePath = ThirdPartyPath + "GameEngineObject/";
				PublicIncludePaths.Add(InclduePath);
			}

			{
				string InclduePath = ThirdPartyPath + "LogicContent/";
				PublicIncludePaths.Add(InclduePath);
			}

			// string LibraryName = "GameEngineBase.lib";
			string LibraryPath = ThirdPartyPath + "Build/Unrelease/";

			PublicSystemLibraryPaths.Add(LibraryPath);
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineBase.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineNet.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineObject.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "LogicContent.lib"));
		}

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
