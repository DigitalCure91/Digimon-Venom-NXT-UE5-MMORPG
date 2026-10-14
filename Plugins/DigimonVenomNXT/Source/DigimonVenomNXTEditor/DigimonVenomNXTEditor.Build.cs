using UnrealBuildTool;

public class DigimonVenomNXTEditor : ModuleRules
{
    public DigimonVenomNXTEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "DigimonVenomNXTRuntime" });
        // Editor automation constructs UWidgetComponent directly; link its owning module here.
        PrivateDependencyModuleNames.AddRange(new string[] {
            "UnrealEd", "AssetTools", "AssetRegistry", "ContentBrowser", "ToolMenus", "LevelEditor", "Paper2D", "Paper2DEditor",
            "UMG", "Slate", "SlateCore", "Json", "JsonUtilities", "EngineSettings", "Projects", "DeveloperToolSettings", "ImageCore"
        });
    }
}
