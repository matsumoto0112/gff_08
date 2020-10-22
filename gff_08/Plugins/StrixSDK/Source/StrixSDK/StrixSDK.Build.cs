using System;
using System.Collections.Generic;
using UnrealBuildTool;
using System.IO;
using System.Text;

public class StrixSDK : ModuleRules
{
	public StrixSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string[] dependencyNames = Directory.GetDirectories(Path.Combine(ModuleDirectory, "Dependencies"));
		foreach (string dependency in dependencyNames)
		{
			PublicIncludePaths.Add(dependency);
		}

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

		PublicDependencyModuleNames.Add("Core");
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"OpenSSL",
				"CoreUObject",
				"Engine",
				"Http",
			}
		);

		var targetPlatform = Target.Platform;
		if (targetPlatform == UnrealTargetPlatform.Win32)
        {
			AddDependencyLibraries(new List<String>() { "win", GetCompilerVersion(Target), "x86"});
        }
		else if (targetPlatform == UnrealTargetPlatform.Win64)
        {
			AddDependencyLibraries(new List<String>() { "win", GetCompilerVersion(Target), "x64" });
        }
		else if (targetPlatform == UnrealTargetPlatform.Mac)
        {
			AddDependencyLibraries(new List<String>() { "mac" });
        }
		else if (targetPlatform == UnrealTargetPlatform.IOS)
        {
			AddDependencyLibraries(new List<String>() { "ios" });
        }
		else if (targetPlatform == UnrealTargetPlatform.Android)
        {
			AddDependencyLibraries(new List<String>() { "android", "arm64-v8a" });
			AddDependencyLibraries(new List<String>() { "android", "armeabi-v7a" });
			AddDependencyLibraries(new List<String>() { "android", "x86" });
			AddDependencyLibraries(new List<String>() { "android", "x86_64" });
        }
		else if (targetPlatform == UnrealTargetPlatform.Switch)
        {
			AddDependencyLibraries(new List<String>() { "switch", "nx64" });
		}
	}

	private void AddDependencyLibraries(List<String> pathParts)
	{
		String path = Path.Combine(ModuleDirectory, "Lib");
		foreach (String pathPart in pathParts)
		{
			path = Path.Combine(path, pathPart);
		}

		PublicLibraryPaths.Add(path);
        
		AddOpenSSLDependencyLibraries(path);
		AddPublicAdditionalLibraries(path, "strix-net");
		AddPublicAdditionalLibraries(path, "strix-client-core");
		AddPublicAdditionalLibraries(path, "strix-client-ingame");
		AddPublicAdditionalLibraries(path, "strix-client-match");
		AddPublicAdditionalLibraries(path, "strix-client-node");
		AddPublicAdditionalLibraries(path, "strix-client-replica");
		AddPublicAdditionalLibraries(path, "strix-client-room");
	}
    
	private void AddOpenSSLDependencyLibraries(string path)
    {
		var targetPlatform = Target.Platform;
		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
#if !UE_4_22_OR_LATER
	    AddPublicAdditionalLibraries(path, "openssl-1.0.2-compat");
#endif
        }
		else if (targetPlatform == UnrealTargetPlatform.Android)
        {
            AddPublicAdditionalLibraries(path, "openssl-1.0.2-compat");
		}
		else if (targetPlatform == UnrealTargetPlatform.Switch)
		{
		}
        else
        {
#if !UE_4_24_OR_LATER
            AddPublicAdditionalLibraries(path, "openssl-1.0.2-compat");
#endif
        }
    }

	private void AddPublicAdditionalLibraries(string path, string libraryName)
    {
	var targetPlatform = Target.Platform;
        bool isWindows = (targetPlatform == UnrealTargetPlatform.Win32 || targetPlatform == UnrealTargetPlatform.Win64);

        string prefix = (isWindows ? null : "lib");
        string fileExtension = (isWindows ? "lib" : "a");

        string libraryFilename = Path.Combine(path, CreateLibraryFilename(libraryName, prefix, fileExtension));
        
		if (isWindows)
        {
            PublicAdditionalLibraries.Add(libraryFilename);
        }
		else if (targetPlatform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(libraryFilename);
        }
		else if (targetPlatform == UnrealTargetPlatform.IOS)
        {
            PublicAdditionalLibraries.Add(libraryName);
	    PublicAdditionalShadowFiles.Add(libraryFilename);
        }
        else
        {
            PublicAdditionalLibraries.Add(libraryName);
        }
    }

	private String CreateLibraryFilename(String name, String prefix, String fileExtension)
	{
		StringBuilder builder = new StringBuilder();

		if (!String.IsNullOrEmpty(prefix))
		{
			builder.Append(prefix);
		}

		builder.Append(name);

		if (!String.IsNullOrEmpty(fileExtension))
		{
			builder.Append(".");
			builder.Append(fileExtension);
		}

		

		return builder.ToString();
	}

	private string GetCompilerVersion(ReadOnlyTargetRules Target)
	{
		string compilerString = "";
		var compiler = Target.WindowsPlatform.Compiler;

		switch (compiler)
		{
			case WindowsCompiler.VisualStudio2017:
				compilerString = "vc15";
				break;
#if UE_4_22_OR_LATER
			case WindowsCompiler.VisualStudio2019:
				compilerString = "vc16";
				break;
#else
			case WindowsCompiler.VisualStudio2015:
				compilerString = "vc14";
				break;
#endif
#if UE_4_21_OR_LATER
            case WindowsCompiler.Clang:
				compilerString = "clang";
				break;
#endif
			default:
				break;
		}

		return compilerString;
	}
}