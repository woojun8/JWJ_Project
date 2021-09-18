// Copyright Epic Games, Inc. All Rights Reserved.

// using �� c#���� #include��� ���� �˴ϴ�.
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

		// �𸮾��� ���̺귯���� ����� �������ִ� c#���α׷���
		// �ڽ��� �ڵ带 �ļ� ���̺귯���� ����� �߰��ϴ� ����Դϴ�.
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
