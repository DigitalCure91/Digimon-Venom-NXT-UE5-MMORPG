param(
    [Parameter(Mandatory=$true)][string]$EngineRoot,
    [string]$PackageDirectory = ""
)
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 2.0
$PluginRoot = [IO.Path]::GetFullPath((Split-Path $PSScriptRoot -Parent))
$PluginFile = Join-Path $PluginRoot "DigimonVenomNXT.uplugin"
$RunUAT = Join-Path $EngineRoot "Engine\Build\BatchFiles\RunUAT.bat"
if (!(Test-Path -LiteralPath $RunUAT -PathType Leaf)) { throw "RunUAT.bat was not found. Pass the Unreal Engine installation root, e.g. C:\Program Files\Epic Games\UE_5.8." }
. (Join-Path $PSScriptRoot 'NativeBuildChecks.ps1')
Assert-DigimonEngineVersion -EngineRoot $EngineRoot
Assert-DigimonImportCommandlet -PluginRoot $PluginRoot
if ([string]::IsNullOrWhiteSpace($PackageDirectory)) { $PackageDirectory = Join-Path (Split-Path $PluginRoot -Parent) ("DigimonVenomNXT_UE58_Build_" + (Get-Date -Format "yyyyMMdd-HHmmss") + "_" + [Guid]::NewGuid().ToString("N").Substring(0, 8)) }
$PackageDirectory = [IO.Path]::GetFullPath($PackageDirectory)
if ($PackageDirectory.StartsWith($PluginRoot + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase) -or $PackageDirectory -eq $PluginRoot) {
    throw "Choose an output directory outside the plugin source folder."
}
# UAT owns this output tree. Never let BuildPlugin erase an existing source or unrelated folder.
if (Test-Path -LiteralPath $PackageDirectory) {
    if (!(Test-Path -LiteralPath $PackageDirectory -PathType Container) -or @(Get-ChildItem -LiteralPath $PackageDirectory -Force).Count -gt 0) {
        throw "Choose a new or empty package directory; the existing output will not be erased."
    }
}
Write-Host 'Plugin-only compilation: this does not create MainMenu/PublicWorld or package a playable game.'
& $RunUAT BuildPlugin "-Plugin=$PluginFile" "-Package=$PackageDirectory" -TargetPlatforms=Win64 -Rocket
if ($LASTEXITCODE -ne 0) { throw "Unreal BuildPlugin failed with exit code $LASTEXITCODE. Review the UAT compiler log." }
Write-Host "Unreal source build completed: $PackageDirectory"
Write-Host "This builds the plugin only. To import and package a game, install the plugin in your project and run Tools/Build_Windows.bat -ImportContent. See INSTALL_AND_BUILD.md."
