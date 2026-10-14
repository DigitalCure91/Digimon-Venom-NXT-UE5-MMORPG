using UnrealBuildTool;
using System.IO;

public class DigimonVenomNXTRuntime : ModuleRules
{
    public DigimonVenomNXTRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        // JSON registries are read through Unreal's platform filesystem in packaged games.
        // RawAssets remains editor import input; imported assets are cooked separately.
        foreach (string Resource in Directory.GetFiles(Path.Combine(PluginDirectory, "Resources"), "*.json", SearchOption.TopDirectoryOnly))
        {
            RuntimeDependencies.Add(Resource, StagedFileType.UFS);
        }
        string GameData = Path.Combine(PluginDirectory, "Resources", "GameData");
        if (Directory.Exists(GameData))
        {
            foreach (string Resource in Directory.GetFiles(GameData, "*.json", SearchOption.AllDirectories))
            {
                if (Path.GetFileName(Resource) != "import_manifest.json")
                    RuntimeDependencies.Add(Resource, StagedFileType.UFS);
            }
        }
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
            "UMG", "Slate", "SlateCore", "CommonUI", "CommonInput", "Paper2D",
            "DeveloperSettings", "Json", "JsonUtilities", "Projects"
        });
    }
}
