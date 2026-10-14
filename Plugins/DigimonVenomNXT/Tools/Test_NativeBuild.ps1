# Maintainer regression checks for the Windows build helpers. No Unreal or Pester required.
# Run in Windows PowerShell 5.1:
#   powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\Tools\Test_NativeBuild.ps1
[CmdletBinding()]
param()

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 2.0
. (Join-Path $PSScriptRoot 'NativeHost.ps1')
. (Join-Path $PSScriptRoot 'NativeBuildChecks.ps1')

$TestRoot = Join-Path ([IO.Path]::GetTempPath()) ('Digimon Native Build Tests ' + [Guid]::NewGuid().ToString('N'))
$script:FixtureNumber = 0
$script:Passed = 0
$script:Failures = @()
$Utf8 = New-Object System.Text.UTF8Encoding($false)

function Write-TestText {
    param([string]$Path, [string]$Text)
    [void][IO.Directory]::CreateDirectory((Split-Path $Path -Parent))
    [IO.File]::WriteAllText($Path, $Text, $Utf8)
}

function Assert-True {
    param([bool]$Condition, [string]$Message)
    if (!$Condition) { throw $Message }
}

function Assert-Throws {
    param([scriptblock]$Action, [string]$MessagePattern)
    $Caught = $false
    try { & $Action | Out-Null }
    catch {
        $Caught = $true
        if ($_.Exception.Message -notmatch $MessagePattern) {
            throw "Wrong failure. Expected /$MessagePattern/; received: $($_.Exception.Message)"
        }
    }
    if (!$Caught) { throw "Expected failure matching /$MessagePattern/, but the helper succeeded." }
}

function Invoke-TestCase {
    param([string]$Name, [scriptblock]$Action)
    try {
        & $Action
        $script:Passed++
        Write-Host "PASS: $Name"
    }
    catch {
        $script:Failures += "$Name -- $($_.Exception.Message)"
        Write-Host "FAIL: $Name -- $($_.Exception.Message)"
    }
}

function Get-TreeSignature {
    param([string]$Root)
    $Entries = @(Get-ChildItem -LiteralPath $Root -Recurse -Force | Sort-Object FullName | ForEach-Object {
        $Relative = $_.FullName.Substring($Root.Length)
        if ($_.PSIsContainer) { 'D|' + $Relative }
        else { 'F|' + $Relative + '|' + (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash }
    })
    return ($Entries -join "`n")
}

function New-ProjectFixture {
    param([string]$Name = 'DigimonVenomNXT')
    $script:FixtureNumber++
    $Root = Join-Path $TestRoot ('Project Copy With Spaces ' + $script:FixtureNumber)
    $Project = Join-Path $Root ($Name + '.uproject')
    $Descriptor = [pscustomobject]@{
        FileVersion = 3
        EngineAssociation = '5.8'
        Category = 'Test category retained'
        Description = 'Existing project description'
        CustomData = [pscustomobject]@{ Value = 27; Flags = @('one', 'two') }
        Plugins = @(
            [pscustomobject]@{ Name = 'DigimonVenomNXT'; Enabled = $false; MarketplaceURL = 'retained-value'; TargetAllowList = @('Game', 'Editor') },
            [pscustomobject]@{ Name = 'UnrelatedPlugin'; Enabled = $false }
        )
    }
    Write-TestText $Project ($Descriptor | ConvertTo-Json -Depth 100)
    return [pscustomobject]@{ Root = $Root; Project = $Project; Source = (Join-Path $Root 'Source'); Name = $Name }
}

function New-NativeFixture {
    $Fixture = New-ProjectFixture -Name 'ProjectDescriptorName'
    $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
    $Descriptor | Add-Member -MemberType NoteProperty -Name Modules -Value @(
        [pscustomobject]@{ Name = 'ExistingGame'; Type = 'Runtime'; LoadingPhase = 'Default' }
    )
    Write-TestText $Fixture.Project ($Descriptor | ConvertTo-Json -Depth 100)
    Write-TestText (Join-Path $Fixture.Source 'ActualGame.Target.cs') @'
using UnrealBuildTool;
public class ActualGameTarget : TargetRules {
    public ActualGameTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game;
        ExtraModuleNames.Add("ExistingGame");
    }
}
'@
    Write-TestText (Join-Path $Fixture.Source 'ActualEditor.Target.cs') @'
using UnrealBuildTool;
public class ActualEditorTarget : TargetRules {
    public ActualEditorTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Editor;
        ExtraModuleNames.Add("ExistingGame");
    }
}
'@
    Write-TestText (Join-Path $Fixture.Source 'ExistingGame/ExistingGame.Build.cs') @'
using UnrealBuildTool;
public class ExistingGame : ModuleRules {
    public ExistingGame(ReadOnlyTargetRules Target) : base(Target) {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "Engine" });
    }
}
'@
    Write-TestText (Join-Path $Fixture.Source 'ExistingGame/ExistingGame.cpp') @'
#include "Modules/ModuleManager.h"
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ExistingGame, "ExistingGame");
'@
    return $Fixture
}

function Copy-GeneratedSource {
    param($From, $To, [string[]]$RelativeFiles)
    foreach ($Relative in $RelativeFiles) {
        $Destination = Join-Path $To.Source $Relative
        [void][IO.Directory]::CreateDirectory((Split-Path $Destination -Parent))
        [IO.File]::Copy((Join-Path $From.Source $Relative), $Destination, $false)
    }
}

function New-ReceiptFixture {
    $Fixture = New-ProjectFixture
    $Binaries = Join-Path $Fixture.Root 'Binaries/Win64'
    $Executable = Join-Path $Binaries 'DigimonVenomNXT.exe'
    Write-TestText $Executable 'Fixture native executable bytes, not a runnable PE.'
    $ResourcePaths = @()
    $Dependencies = @()
    foreach ($Resource in @('DigimonSpecies.json', 'DigimonMaps.json', 'DigimonCombat.json')) {
        $RelativePath = 'Plugins/DigimonVenomNXT/Resources/' + $Resource
        $ResourcePath = Join-Path $Fixture.Root $RelativePath
        Write-TestText $ResourcePath '{}'
        $ResourcePaths += $ResourcePath
        $Dependencies += [pscustomobject]@{ Path = ('$(ProjectDir)/' + $RelativePath); Type = 'NonUFS' }
    }
    $Receipt = [pscustomobject]@{
        TargetName = 'DigimonVenomNXT'
        Platform = 'Win64'
        Configuration = 'Development'
        BuildProducts = @([pscustomobject]@{ Path = '$(ProjectDir)/Binaries/Win64/DigimonVenomNXT.exe'; Type = 'Executable' })
        RuntimeDependencies = $Dependencies
    }
    $Result = [pscustomobject]@{
        Root = $Fixture.Root
        EngineRoot = (Join-Path $Fixture.Root 'Fake Engine')
        Executable = $Executable
        ReceiptFile = (Join-Path $Binaries 'DigimonVenomNXT.target')
        ResourcePaths = $ResourcePaths
        Receipt = $Receipt
        StartedUtc = [DateTime]::UtcNow.AddMinutes(-2)
    }
    Save-FixtureReceipt $Result
    [IO.File]::SetLastWriteTimeUtc($Executable, $Result.StartedUtc.AddSeconds(30))
    return $Result
}

function Save-FixtureReceipt {
    param($Fixture)
    Write-TestText $Fixture.ReceiptFile ($Fixture.Receipt | ConvertTo-Json -Depth 100)
    [IO.File]::SetLastWriteTimeUtc($Fixture.ReceiptFile, $Fixture.StartedUtc.AddSeconds(30))
}

function New-EnginePluginFixture {
    $Fixture = New-ProjectFixture
    $EngineRoot = Join-Path $Fixture.Root 'UE Test Install'
    Write-TestText (Join-Path $EngineRoot 'Engine/Build/Build.version') '{"MajorVersion":5,"MinorVersion":8,"PatchVersion":0}'
    foreach ($Name in @('CommonUI', 'Paper2D', 'EnhancedInput')) {
        $Modules = @([pscustomobject]@{ Name = $Name; Type = 'Runtime' })
        if ($Name -eq 'CommonUI') { $Modules += [pscustomobject]@{ Name = 'CommonInput'; Type = 'Runtime' } }
        Write-TestText (Join-Path $EngineRoot ("Engine/Plugins/$Name/$Name.uplugin")) (@{ FileVersion = 3; Modules = $Modules } | ConvertTo-Json -Depth 10)
    }
    return $EngineRoot
}

function New-ImportModuleFixture {
    param([string]$Type = 'Editor', [string]$LoadingPhase = 'Default')
    $Fixture = New-ProjectFixture
    $PluginRoot = Join-Path $Fixture.Root 'Plugins/DigimonVenomNXT'
    $Descriptor = @{ FileVersion = 3; Modules = @(
        @{ Name = 'DigimonVenomNXTRuntime'; Type = 'Runtime'; LoadingPhase = 'Default' },
        @{ Name = 'DigimonVenomNXTEditor'; Type = $Type; LoadingPhase = $LoadingPhase }
    ) }
    Write-TestText (Join-Path $PluginRoot 'DigimonVenomNXT.uplugin') ($Descriptor | ConvertTo-Json -Depth 10)
    return $PluginRoot
}

function Get-CampaignProjectFolder {
    param([string]$PluginRoot)
    return Split-Path (Split-Path $PluginRoot -Parent) -Parent
}

function New-CampaignContentFixture {
    $Fixture = New-ProjectFixture
    $PluginRoot = Join-Path $Fixture.Root 'Plugins/DigimonVenomNXT'
    $Rows = @(); $Textures = @(); $Sprites = @()
    for ($Id = 1; $Id -le 3; $Id++) {
        $Ground = 'RawAssets/assets/maps/map_{0:D3}_a.png' -f $Id
        $Mask = 'RawAssets/assets/maps/map_{0:D3}_b.png' -f $Id
        $GroundFile = Join-Path $PluginRoot ('Resources/' + $Ground)
        $MaskFile = Join-Path $PluginRoot ('Resources/' + $Mask)
        Write-TestText $GroundFile "Fixture artwork $Id"
        Write-TestText $MaskFile "Fixture collision $Id"
        $Texture = '/DigimonVenomNXT/Generated/Maps/T_PlayMap_{0:D3}' -f $Id
        $Sprite = '/DigimonVenomNXT/Generated/Maps/SP_PlayMap_{0:D3}' -f $Id
        $Rows += [pscustomobject]@{
            mapId = $Id; groundSource = $Ground; collisionSource = $Mask; importedTexture = $Texture
            groundSourceSha256 = (Get-FileHash -LiteralPath $GroundFile -Algorithm SHA256).Hash
            collisionSourceSha256 = (Get-FileHash -LiteralPath $MaskFile -Algorithm SHA256).Hash
        }
        $Textures += [pscustomobject]@{ source = $Ground; asset = $Texture; sha1 = (Get-FileHash -LiteralPath $GroundFile -Algorithm SHA1).Hash }
        $Sprites += [pscustomobject]@{ asset = $Sprite; texture = $Texture }
        foreach ($Prefix in @('SP_PlayMap', 'T_PlayMap')) {
            Write-TestText (Join-Path $PluginRoot ('Content/Generated/Maps/{0}_{1:D3}.uasset' -f $Prefix, $Id)) 'Fixture bytes, not an Unreal asset.'
        }
    }
    Write-TestText (Join-Path $PluginRoot 'Content/Generated/Maps/DA_PlayableMapRevision.uasset') 'Fixture marker bytes.'
    Write-TestText (Join-Path $PluginRoot 'Content/Generated/Materials/MI_DVNXT_FieldSprite.uasset') 'Fixture material bytes.'
    foreach ($Level in @('MainMenu', 'PublicWorld')) {
        Write-TestText (Join-Path $PluginRoot "Content/Generated/Levels/$Level.umap") 'Fixture level bytes.'
    }
    Write-TestText (Join-Path $PluginRoot 'Resources/DigimonMaps.json') (@{ maps = $Rows } | ConvertTo-Json -Depth 10)
    Write-TestText (Join-Path $PluginRoot 'Resources/GameData/import_manifest.json') (@{
        schemaVersion = 1; textures = $Textures; sprites = $Sprites
        animations = @(); audio = @(); partnerSets = @(); tamerSets = @()
    } | ConvertTo-Json -Depth 10)
    Save-CampaignImportReceipt $PluginRoot
    return $PluginRoot
}

function Save-CampaignImportReceipt {
    param([string]$PluginRoot)
    $ContentRoot = (Join-Path $PluginRoot 'Content').TrimEnd([char[]]'\/') + [IO.Path]::DirectorySeparatorChar
    $Packages = @(Get-ChildItem -LiteralPath $ContentRoot -File -Recurse | ForEach-Object {
        $Relative = $_.FullName.Substring($ContentRoot.Length).Replace('\', '/')
        [pscustomobject]@{
            packagePath = '/DigimonVenomNXT/' + $Relative.Substring(0, $Relative.LastIndexOf('.'))
            sha1 = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA1).Hash
        }
    })
    $Receipt = [pscustomobject]@{
        schema = 1; revision = 'digimon-venom-nxt-native-1'; mapCount = 3; expectedPackageCount = $Packages.Count
        registrySha1 = (Get-FileHash -LiteralPath (Join-Path $PluginRoot 'Resources/DigimonMaps.json') -Algorithm SHA1).Hash
        manifestSha1 = (Get-FileHash -LiteralPath (Join-Path $PluginRoot 'Resources/GameData/import_manifest.json') -Algorithm SHA1).Hash
        packages = $Packages
    }
    Write-TestText (Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot) ($Receipt | ConvertTo-Json -Depth 10)
}

function Invoke-FixtureBuildCheck {
    param($Fixture)
    return Assert-DigimonGameBuild -ProjectFolder $Fixture.Root -EngineRoot $Fixture.EngineRoot -GameTarget 'DigimonVenomNXT' -Configuration 'Development' -BuildStartedUtc $Fixture.StartedUtc
}

try {
    [void][IO.Directory]::CreateDirectory($TestRoot)

    Invoke-TestCase 'Dynamic map registry and complete import produce a cook directory' {
        $PluginRoot = New-CampaignContentFixture
        $Result = Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot)
        Assert-True ($Result.MapCount -eq 3 -and @($Result.CookDirectories).Count -eq 1 -and $Result.ExpectedPackageCount -eq 10) 'Incorrect dynamic package/map count.'
        Assert-True ($Result.AssetRevision -ceq 'digimon-venom-nxt-native-1') 'Incorrect import revision.'
    }
    Invoke-TestCase 'First-import source-only preflight does not require saved assets' {
        $PluginRoot = New-CampaignContentFixture
        Remove-Item -LiteralPath (Join-Path $PluginRoot 'Content') -Recurse -Force
        Remove-Item -LiteralPath (Join-Path (Get-CampaignProjectFolder $PluginRoot) 'Intermediate') -Recurse -Force
        $Result = Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -SourceOnly
        Assert-True ($Result.MapCount -eq 3) 'Source-only preflight failed.'
    }
    Invoke-TestCase 'Content receipt is project-local and wrong project is rejected' {
        $PluginRoot = New-CampaignContentFixture
        $ProjectFolder = Get-CampaignProjectFolder $PluginRoot
        $Receipt = Get-DigimonContentReceiptPath -PluginRoot $PluginRoot -ProjectFolder $ProjectFolder
        Assert-True ($Receipt -eq (Join-Path $ProjectFolder 'Intermediate/DigimonVenomNXT/ContentImportReceipt.json')) 'Receipt location differs from Unreal ProjectIntermediateDir.'
        Assert-Throws { Get-DigimonContentReceiptPath -PluginRoot $PluginRoot -ProjectFolder (Join-Path $ProjectFolder 'OtherProject') } 'host project containing'
    }
    Invoke-TestCase 'A stale plugin-local receipt never substitutes for the host receipt' {
        $PluginRoot = New-CampaignContentFixture
        $Receipt = Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot
        Write-TestText (Join-Path $PluginRoot 'Intermediate/DigimonVenomNXT/ContentImportReceipt.json') ([IO.File]::ReadAllText($Receipt))
        Remove-Item -LiteralPath $Receipt
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'import receipt is missing'
    }
    Invoke-TestCase 'Imported assets without a completed world receipt cannot package' {
        $PluginRoot = New-CampaignContentFixture
        $Receipt = Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot
        Remove-Item -LiteralPath $Receipt
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'world repair alone cannot certify'
    }
    Invoke-TestCase 'Missing public world stops packaging even when all textures exist' {
        $PluginRoot = New-CampaignContentFixture
        Remove-Item -LiteralPath (Join-Path $PluginRoot 'Content/Generated/Levels/PublicWorld.umap')
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'PublicWorld.*changed or is missing'
    }
    Invoke-TestCase 'Receipt cannot drop the required map revision marker' {
        $PluginRoot = New-CampaignContentFixture
        $ReceiptPath = Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot
        $Receipt = Get-Content -LiteralPath $ReceiptPath -Raw | ConvertFrom-Json
        $Receipt.packages = @($Receipt.packages | Where-Object { $_.packagePath -notlike '*/DA_PlayableMapRevision' })
        $Receipt.expectedPackageCount = $Receipt.packages.Count
        Write-TestText $ReceiptPath ($Receipt | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'required package.*DA_PlayableMapRevision.*absent'
    }
    Invoke-TestCase 'Missing imported sprite stops packaging' {
        $PluginRoot = New-CampaignContentFixture
        Remove-Item -LiteralPath (Join-Path $PluginRoot 'Content/Generated/Maps/SP_PlayMap_003.uasset')
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'SP_PlayMap_003.*changed or is missing'
    }
    Invoke-TestCase 'Empty imported map stops packaging' {
        $PluginRoot = New-CampaignContentFixture
        Write-TestText (Join-Path $PluginRoot 'Content/Generated/Maps/T_PlayMap_002.uasset') ''
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'T_PlayMap_002.*changed or is missing'
    }
    Invoke-TestCase 'Duplicate map IDs stop before building' {
        $PluginRoot = New-CampaignContentFixture
        $Path = Join-Path $PluginRoot 'Resources/DigimonMaps.json'
        $Registry = Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
        $Registry.maps[2].mapId = 1
        Write-TestText $Path ($Registry | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'Invalid or duplicate source map ID'
    }
    Invoke-TestCase 'Missing completed import receipt blocks packaging' {
        $PluginRoot = New-CampaignContentFixture
        Remove-Item -LiteralPath (Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'import receipt is missing'
    }
    Invoke-TestCase 'Changed registry invalidates receipt' {
        $PluginRoot = New-CampaignContentFixture
        Add-Content -LiteralPath (Join-Path $PluginRoot 'Resources/DigimonMaps.json') -Value ' '
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'registry/manifest changed'
    }
    Invoke-TestCase 'Changed manifest invalidates receipt' {
        $PluginRoot = New-CampaignContentFixture
        Add-Content -LiteralPath (Join-Path $PluginRoot 'Resources/GameData/import_manifest.json') -Value ' '
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'registry/manifest changed'
    }
    Invoke-TestCase 'Changed map source fails hash verification' {
        $PluginRoot = New-CampaignContentFixture
        Write-TestText (Join-Path $PluginRoot 'Resources/RawAssets/assets/maps/map_001_a.png') 'Different artwork'
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'Map 1 groundSource source differs'
    }
    Invoke-TestCase 'Missing registered source hash stops before import' {
        $PluginRoot = New-CampaignContentFixture
        $Path = Join-Path $PluginRoot 'Resources/DigimonMaps.json'
        $Registry = Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
        $Registry.maps[0].PSObject.Properties.Remove('groundSourceSha256')
        Write-TestText $Path ($Registry | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -SourceOnly } 'has no valid registered SHA256'
    }
    Invoke-TestCase 'Duplicate imported package destination stops before import' {
        $PluginRoot = New-CampaignContentFixture
        $Path = Join-Path $PluginRoot 'Resources/GameData/import_manifest.json'
        $Manifest = Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
        $Manifest.sprites[0].asset = $Manifest.textures[0].asset
        Write-TestText $Path ($Manifest | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -SourceOnly } 'Duplicate import destination'
    }
    Invoke-TestCase 'Source path traversal is rejected' {
        Assert-Throws { Resolve-DigimonChildPath -Root $TestRoot -Relative '../outside.png' } 'escapes its source directory'
    }
    Invoke-TestCase 'Missing generated main menu blocks packaging' {
        $PluginRoot = New-CampaignContentFixture
        Remove-Item -LiteralPath (Join-Path $PluginRoot 'Content/Generated/Levels/MainMenu.umap')
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'MainMenu.*changed or is missing'
    }
    Invoke-TestCase 'Partial receipt cannot omit required generated packages' {
        $PluginRoot = New-CampaignContentFixture
        $Path = Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot
        $Receipt = Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
        $Receipt.packages = @($Receipt.packages | Select-Object -First 7)
        $Receipt.expectedPackageCount = 7
        Write-TestText $Path ($Receipt | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'required package.*absent'
    }
    Invoke-TestCase 'Duplicate receipt entry is rejected' {
        $PluginRoot = New-CampaignContentFixture
        $Path = Get-DigimonContentReceiptPath -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) -PluginRoot $PluginRoot
        $Receipt = Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
        $Receipt.packages += $Receipt.packages[0]
        $Receipt.expectedPackageCount = $Receipt.packages.Count
        Write-TestText $Path ($Receipt | ConvertTo-Json -Depth 10)
        Assert-Throws { Assert-DigimonCampaignSources -PluginRoot $PluginRoot -ProjectFolder (Get-CampaignProjectFolder $PluginRoot) } 'Duplicate saved package'
    }
    Invoke-TestCase 'Shared hosting credential blocks build without printing its value' {
        $PluginRoot = New-CampaignContentFixture
        Write-TestText (Join-Path $PluginRoot 'Config/DefaultGame.ini') "[Settings]`nAdminHostPassword=fixture-secret"
        Assert-Throws { Assert-DigimonNoSharedHostSecret -PluginRoot $PluginRoot -ProjectFolder $TestRoot } 'credential was not printed'
    }

    Invoke-TestCase 'Default Editor module supports early import commandlet discovery' {
        $PluginRoot = New-ImportModuleFixture
        Assert-DigimonImportCommandlet -PluginRoot $PluginRoot
    }
    Invoke-TestCase 'Old PostEngineInit module fails with the commandlet discovery cause' {
        $PluginRoot = New-ImportModuleFixture -LoadingPhase 'PostEngineInit'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'PostEngineInit is too late for import commandlet class discovery'
    }
    Invoke-TestCase 'EditorNoCommandlet module is rejected before compiling' {
        $PluginRoot = New-ImportModuleFixture -Type 'EditorNoCommandlet'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'EditorNoCommandlet.*not supported'
    }
    Invoke-TestCase 'Wrong module host type cannot pass the import preflight' {
        $PluginRoot = New-ImportModuleFixture -Type 'Runtime'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'not declared as Type=Editor'
    }
    Invoke-TestCase 'Disabled module loading cannot pass the import preflight' {
        $PluginRoot = New-ImportModuleFixture -LoadingPhase 'None'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'must use LoadingPhase=Default'
    }
    Invoke-TestCase 'Missing and duplicate editor module declarations fail closed' {
        $PluginRoot = New-ImportModuleFixture
        $Path = Join-Path $PluginRoot 'DigimonVenomNXT.uplugin'
        Write-TestText $Path '{"Modules":[{"Name":"DigimonVenomNXTRuntime","Type":"Runtime"}]}'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'found 0'
        Write-TestText $Path '{"Modules":[{"Name":"DigimonVenomNXTEditor","Type":"Editor","LoadingPhase":"Default"},{"Name":"DigimonVenomNXTEditor","Type":"Editor","LoadingPhase":"Default"}]}'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'found 2'
    }
    Invoke-TestCase 'Incomplete editor module properties fail with import guidance' {
        $PluginRoot = New-ImportModuleFixture
        $Path = Join-Path $PluginRoot 'DigimonVenomNXT.uplugin'
        Write-TestText $Path '{"Modules":[{"Name":"DigimonVenomNXTEditor","Type":"Editor"}]}'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'LoadingPhase=Default'
        Write-TestText $Path '{"Modules":[{"Name":"DigimonVenomNXTEditor","LoadingPhase":"Default"}]}'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'Type=Editor'
    }
    Invoke-TestCase 'Missing and malformed plugin descriptors give actionable failures' {
        $PluginRoot = New-ImportModuleFixture
        $Path = Join-Path $PluginRoot 'DigimonVenomNXT.uplugin'
        Write-TestText $Path '{invalid'
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'descriptor cannot be read'
        Remove-Item -LiteralPath $Path
        Assert-Throws { Assert-DigimonImportCommandlet -PluginRoot $PluginRoot } 'descriptor is missing'
    }

    Invoke-TestCase 'UE 5.8 engine metadata passes the version gate' {
        $EngineRoot = New-EnginePluginFixture
        Assert-DigimonEngineVersion -EngineRoot $EngineRoot
    }
    Invoke-TestCase 'Wrong engine installation stops before project changes' {
        $EngineRoot = New-EnginePluginFixture
        Write-TestText (Join-Path $EngineRoot 'Engine/Build/Build.version') '{"MajorVersion":5,"MinorVersion":7,"PatchVersion":4}'
        Assert-Throws { Assert-DigimonEngineVersion -EngineRoot $EngineRoot } 'not Unreal Engine 5.8'
    }
    Invoke-TestCase 'Missing engine metadata fails closed' {
        $EngineRoot = New-EnginePluginFixture
        Remove-Item -LiteralPath (Join-Path $EngineRoot 'Engine/Build/Build.version')
        Assert-Throws { Assert-DigimonEngineVersion -EngineRoot $EngineRoot } 'version metadata is missing'
    }
    Invoke-TestCase 'Required installed engine plugins and CommonInput module pass preflight' {
        $EngineRoot = New-EnginePluginFixture
        Assert-DigimonEnginePlugins -EngineRoot $EngineRoot
    }

    Invoke-TestCase 'Missing engine CommonUI stops before project mutation or build' {
        $EngineRoot = New-EnginePluginFixture
        Remove-Item -LiteralPath (Join-Path $EngineRoot 'Engine/Plugins/CommonUI/CommonUI.uplugin')
        Assert-Throws { Assert-DigimonEnginePlugins -EngineRoot $EngineRoot } 'CommonUI.uplugin; found 0'
    }

    Invoke-TestCase 'Incomplete engine CommonUI missing CommonInput stops preflight' {
        $EngineRoot = New-EnginePluginFixture
        Write-TestText (Join-Path $EngineRoot 'Engine/Plugins/CommonUI/CommonUI.uplugin') '{"FileVersion":3,"Modules":[{"Name":"CommonUI","Type":"Runtime"}]}'
        Assert-Throws { Assert-DigimonEnginePlugins -EngineRoot $EngineRoot } 'required CommonInput module'
    }

    Invoke-TestCase 'Duplicate engine CommonUI descriptors stop preflight' {
        $EngineRoot = New-EnginePluginFixture
        Write-TestText (Join-Path $EngineRoot 'Engine/Plugins/Other/CommonUI.uplugin') '{"FileVersion":3}'
        Assert-Throws { Assert-DigimonEnginePlugins -EngineRoot $EngineRoot } 'CommonUI.uplugin; found 2'
    }

    Invoke-TestCase 'Content-only project gains native targets, runtime dependency and descriptor backup' {
        $Fixture = New-ProjectFixture
        $OriginalText = [IO.File]::ReadAllText($Fixture.Project)
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        Assert-True ($Result.GameTarget -ceq 'DigimonVenomNXT' -and $Result.EditorTarget -ceq 'DigimonVenomNXTEditor' -and $Result.Created) 'Incorrect generated target selection.'
        Assert-True ($Descriptor.EngineAssociation -ceq '5.8' -and $Descriptor.Category -ceq 'Test category retained' -and $Descriptor.Description -ceq 'Existing project description') 'Existing descriptor fields changed.'
        Assert-True ($Descriptor.CustomData.Value -eq 27 -and ($Descriptor.CustomData.Flags -join ',') -ceq 'one,two') 'Nested descriptor fields changed.'
        $Plugin = @($Descriptor.Plugins | Where-Object { $_.Name -ceq 'DigimonVenomNXT' })[0]
        Assert-True ($Plugin.Enabled -and $Plugin.MarketplaceURL -ceq 'retained-value' -and ($Plugin.TargetAllowList -join ',') -ceq 'Game,Editor') 'Plugin settings were lost or plugin was not enabled.'
        Assert-True (!(@($Descriptor.Plugins | Where-Object { $_.Name -ceq 'UnrelatedPlugin' })[0].Enabled)) 'Unrelated plugin setting changed.'
        foreach ($RequiredPlugin in @('Paper2D', 'CommonUI', 'EnhancedInput')) {
            $References = @($Descriptor.Plugins | Where-Object { $_.Name -ceq $RequiredPlugin })
            Assert-True ($References.Count -eq 1 -and $References[0].Enabled) "Required project plugin $RequiredPlugin was not enabled exactly once."
        }
        Assert-True (@($Descriptor.Plugins | Where-Object { $_.Name -ceq 'CommonInput' }).Count -eq 0) 'CommonInput is a CommonUI module, not a separate plugin reference.'
        Assert-True (@($Descriptor.Modules).Count -eq 1 -and $Descriptor.Modules[0].Name -ceq 'DigimonVenomNXTHost') 'Primary host module not registered exactly once.'
        $GameText = Get-Content -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXT.Target.cs') -Raw
        $EditorText = Get-Content -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXTEditor.Target.cs') -Raw
        $RulesText = Get-Content -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXTHost/DigimonVenomNXTHost.Build.cs') -Raw
        $PrimaryText = Get-Content -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXTHost/DigimonVenomNXTHost.cpp') -Raw
        Assert-True ($GameText -match 'class DigimonVenomNXTTarget\s*:\s*TargetRules' -and $GameText -match 'Type\s*=\s*TargetType\.Game' -and $GameText -match 'ExtraModuleNames.Add\("DigimonVenomNXTHost"\)') 'Game target is not wired to the host.'
        Assert-True ($EditorText -match 'class DigimonVenomNXTEditorTarget\s*:\s*TargetRules' -and $EditorText -match 'Type\s*=\s*TargetType\.Editor' -and $EditorText -match 'ExtraModuleNames.Add\("DigimonVenomNXTHost"\)') 'Editor target is not wired to the host.'
        Assert-True ($RulesText -match '"DigimonVenomNXTRuntime"' -and $PrimaryText -match 'IMPLEMENT_PRIMARY_GAME_MODULE\(FDefaultGameModuleImpl, DigimonVenomNXTHost, "DigimonVenomNXT"\)') 'Primary module or runtime link dependency missing.'
        $Backups = @(Get-ChildItem -LiteralPath $Fixture.Root -Filter '*.bak' -File)
        Assert-True ($Backups.Count -eq 2) 'Expected the initial safety copy and the atomic-replacement backup.'
        foreach ($BackupFile in $Backups) {
            Assert-True ([IO.File]::ReadAllText($BackupFile.FullName) -ceq $OriginalText) 'A descriptor backup is not the exact original.'
        }
    }

    Invoke-TestCase 'Disabled CommonUI and Windows target exclusions are repaired without removing other settings' {
        $Fixture = New-ProjectFixture
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        $Descriptor.Plugins += [pscustomobject]@{
            Name = 'CommonUI'; Enabled = $false; Optional = $true; MarketplaceURL = 'preserved'
            HasExplicitPlatforms = $true; SupportedTargetPlatforms = @()
            PlatformAllowList = @('Linux'); PlatformDenyList = @('Win64', 'Android')
            TargetAllowList = @('Server'); TargetDenyList = @('Game', 'Editor', 'Program')
            TargetConfigurationAllowList = @('Debug'); TargetConfigurationDenyList = @('Development', 'Shipping', 'Test')
            WhitelistPlatforms = @('Linux'); BlacklistPlatforms = @('Win64', 'Android')
            WhitelistTargets = @('Server'); BlacklistTargets = @('Game', 'Editor', 'Program')
            WhitelistTargetConfigurations = @('Debug'); BlacklistTargetConfigurations = @('Development', 'Shipping', 'Test')
            TargetsToExplicitlyLoad = @('Game', 'Editor', 'Server')
        }
        Write-TestText $Fixture.Project ($Descriptor | ConvertTo-Json -Depth 100)
        Ensure-DigimonNativeHost -Project $Fixture.Project | Out-Null
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        $Common = @($Descriptor.Plugins | Where-Object { $_.Name -ceq 'CommonUI' })[0]
        Assert-True ($Common.Enabled -and !$Common.Optional -and $Common.MarketplaceURL -ceq 'preserved') 'CommonUI enablement/metadata mismatch.'
        Assert-True (($Common.SupportedTargetPlatforms -join ',') -ceq 'Win64') 'Explicit empty platform list still excludes Win64.'
        foreach ($Field in @('PlatformAllowList', 'WhitelistPlatforms')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Linux,Win64') "Incorrect $Field repair."
        }
        foreach ($Field in @('PlatformDenyList', 'BlacklistPlatforms')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Android') "Incorrect $Field repair."
        }
        foreach ($Field in @('TargetAllowList', 'WhitelistTargets')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Server,Game,Editor') "Incorrect $Field repair."
        }
        foreach ($Field in @('TargetDenyList', 'BlacklistTargets')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Program') "Incorrect $Field repair."
        }
        foreach ($Field in @('TargetConfigurationAllowList', 'WhitelistTargetConfigurations')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Debug,Development,Shipping') "Incorrect $Field repair."
        }
        foreach ($Field in @('TargetConfigurationDenyList', 'BlacklistTargetConfigurations')) {
            Assert-True (($Common.PSObject.Properties[$Field].Value -join ',') -ceq 'Test') "Incorrect $Field repair."
        }
        Assert-True (($Common.TargetsToExplicitlyLoad -join ',') -ceq 'Server') 'Required startup plugins remain explicitly unloaded for Game/Editor.'
        $Before = Get-TreeSignature $Fixture.Root
        Ensure-DigimonNativeHost -Project $Fixture.Project | Out-Null
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Repeated dependency repair changed the project.'
    }

    Invoke-TestCase 'Duplicate required engine plugin entries fail without changing any project files' {
        $Fixture = New-ProjectFixture
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        $Descriptor.Plugins += [pscustomobject]@{ Name = 'CommonUI'; Enabled = $true }
        $Descriptor.Plugins += [pscustomobject]@{ Name = 'CommonUI'; Enabled = $false }
        Write-TestText $Fixture.Project ($Descriptor | ConvertTo-Json -Depth 100)
        $Before = Get-TreeSignature $Fixture.Root
        Assert-Throws { Ensure-DigimonNativeHost -Project $Fixture.Project } 'duplicate CommonUI'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Duplicate rejection wrote files.'
    }

    Invoke-TestCase 'Repeating native setup makes no file or descriptor changes' {
        $Fixture = New-ProjectFixture
        Ensure-DigimonNativeHost -Project $Fixture.Project | Out-Null
        $Before = Get-TreeSignature $Fixture.Root
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project
        Assert-True (!$Result.Created -and !$Result.DescriptorChanged) 'Repeated setup reported changes.'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Repeated setup changed files or created another backup.'
    }

    Invoke-TestCase 'Dry run reports intended targets without modifying the project' {
        $Fixture = New-ProjectFixture
        $Before = Get-TreeSignature $Fixture.Root
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project -DryRun
        Assert-True ($Result.Created -and $Result.DescriptorChanged -and $Result.GameTarget -ceq 'DigimonVenomNXT') 'Dry run did not report the intended setup.'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Dry run mutated the project.'
    }

    Invoke-TestCase 'Modified generated source is rejected without overwriting any file' {
        $Fixture = New-ProjectFixture
        Ensure-DigimonNativeHost -Project $Fixture.Project | Out-Null
        $CustomFile = Join-Path $Fixture.Source 'DigimonVenomNXTHost/DigimonVenomNXTHost.cpp'
        Write-TestText $CustomFile (([IO.File]::ReadAllText($CustomFile)) + "`r`n// Custom code must survive.`r`n")
        $Before = Get-TreeSignature $Fixture.Root
        Assert-Throws { Ensure-DigimonNativeHost -Project $Fixture.Project } 'custom or modified file'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Rejected setup wrote project files.'
    }

    Invoke-TestCase 'Undeclared existing native source is preserved and rejected' {
        $Fixture = New-ProjectFixture
        Write-TestText (Join-Path $Fixture.Source 'MyExistingGame.cpp') '// Existing source, module descriptor missing.'
        $Before = Get-TreeSignature $Fixture.Root
        Assert-Throws { Ensure-DigimonNativeHost -Project $Fixture.Project } 'Existing project source'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Undeclared source rejection changed the project.'
    }

    Invoke-TestCase 'Interrupted setup with a subset of exact generated files resumes safely' {
        $Seed = New-ProjectFixture
        Ensure-DigimonNativeHost -Project $Seed.Project | Out-Null
        $Fixture = New-ProjectFixture
        Copy-GeneratedSource $Seed $Fixture @('DigimonVenomNXT.Target.cs', 'DigimonVenomNXTHost/DigimonVenomNXTHost.cpp')
        $BeforeHash = (Get-FileHash -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXT.Target.cs') -Algorithm SHA256).Hash
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project
        Assert-True ($Result.Created -and @(Get-ChildItem -LiteralPath $Fixture.Source -Recurse -File).Count -eq 4) 'Interrupted setup did not finish the four generated source files.'
        Assert-True ((Get-FileHash -LiteralPath (Join-Path $Fixture.Source 'DigimonVenomNXT.Target.cs') -Algorithm SHA256).Hash -ceq $BeforeHash) 'Existing exact target was rewritten.'
    }

    Invoke-TestCase 'Interrupted setup after all source files but before descriptor update resumes' {
        $Seed = New-ProjectFixture
        Ensure-DigimonNativeHost -Project $Seed.Project | Out-Null
        $Fixture = New-ProjectFixture
        Copy-GeneratedSource $Seed $Fixture @('DigimonVenomNXT.Target.cs', 'DigimonVenomNXTEditor.Target.cs', 'DigimonVenomNXTHost/DigimonVenomNXTHost.Build.cs', 'DigimonVenomNXTHost/DigimonVenomNXTHost.cpp')
        # Match the screenshot's failure state: generated source and an initial
        # backup exist, but the original descriptor has not been replaced.
        $PriorBackup = $Fixture.Project + '.previous-attempt.bak'
        [IO.File]::Copy($Fixture.Project, $PriorBackup, $false)
        $PriorBackupHash = (Get-FileHash -LiteralPath $PriorBackup -Algorithm SHA256).Hash
        $Before = Get-TreeSignature $Fixture.Source
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        Assert-True ($Result.Created -and $Descriptor.Modules[0].Name -ceq 'DigimonVenomNXTHost') 'Descriptor recovery did not register the host module.'
        Assert-True ((Get-TreeSignature $Fixture.Source) -ceq $Before) 'Descriptor recovery changed exact generated source.'
        Assert-True ((Get-FileHash -LiteralPath $PriorBackup -Algorithm SHA256).Hash -ceq $PriorBackupHash) 'Recovery changed the failed-attempt backup.'
    }

    Invoke-TestCase 'Existing native project uses actual target names and keeps its primary module' {
        $Fixture = New-NativeFixture
        $Before = Get-TreeSignature $Fixture.Source
        $Result = Ensure-DigimonNativeHost -Project $Fixture.Project
        $Descriptor = Get-Content -LiteralPath $Fixture.Project -Raw | ConvertFrom-Json
        Assert-True ($Result.GameTarget -ceq 'ActualGame' -and $Result.EditorTarget -ceq 'ActualEditor' -and $null -eq $Result.HostModule -and !$Result.Created) 'Existing native target names were not retained.'
        Assert-True (@($Descriptor.Modules).Count -eq 1 -and $Descriptor.Modules[0].Name -ceq 'ExistingGame') 'A second primary host module was added.'
        Assert-True ((Get-TreeSignature $Fixture.Source) -ceq $Before) 'Existing native source was changed.'
        Assert-True (@($Descriptor.Plugins | Where-Object { $_.Name -ceq 'DigimonVenomNXT' })[0].Enabled) 'Digimon plugin was not enabled in existing native project.'
    }

    Invoke-TestCase 'Ambiguous native Game targets fail without changing source or descriptor' {
        $Fixture = New-NativeFixture
        $OtherTarget = ([IO.File]::ReadAllText((Join-Path $Fixture.Source 'ActualGame.Target.cs'))).Replace('ActualGameTarget', 'OtherGameTarget')
        Write-TestText (Join-Path $Fixture.Source 'OtherGame.Target.cs') $OtherTarget
        $Before = Get-TreeSignature $Fixture.Root
        Assert-Throws { Ensure-DigimonNativeHost -Project $Fixture.Project } '2 identifiable Game targets'
        Assert-True ((Get-TreeSignature $Fixture.Root) -ceq $Before) 'Ambiguous-target rejection changed files.'
    }

    Invoke-TestCase 'Matching fresh receipt and executable with all three runtime resources pass' {
        $Fixture = New-ReceiptFixture
        $Result = Invoke-FixtureBuildCheck $Fixture
        Assert-True ($Result.Receipt -ceq $Fixture.ReceiptFile -and @($Result.Executables).Count -eq 1 -and $Result.Executables[0] -ceq $Fixture.Executable) 'Receipt check returned the wrong native executable.'
    }

    Invoke-TestCase 'Missing game receipt stops packaging' {
        $Fixture = New-ReceiptFixture
        [IO.File]::Delete($Fixture.ReceiptFile)
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'Expected one .* game receipt; found 0'
    }

    Invoke-TestCase 'Stale game receipt stops packaging' {
        $Fixture = New-ReceiptFixture
        [IO.File]::SetLastWriteTimeUtc($Fixture.ReceiptFile, $Fixture.StartedUtc.AddMinutes(-5))
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'receipt predates'
    }

    Invoke-TestCase 'Stale native executable stops packaging even with a fresh receipt' {
        $Fixture = New-ReceiptFixture
        [IO.File]::SetLastWriteTimeUtc($Fixture.Executable, $Fixture.StartedUtc.AddMinutes(-5))
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'executable is empty or predates'
    }

    Invoke-TestCase 'Wrong Game target receipt is rejected' {
        $Fixture = New-ReceiptFixture
        $Fixture.Receipt.TargetName = 'WrongGame'
        Save-FixtureReceipt $Fixture
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'Expected one .* game receipt; found 0'
    }

    Invoke-TestCase 'Wrong build configuration receipt is rejected' {
        $Fixture = New-ReceiptFixture
        $Fixture.Receipt.Configuration = 'Shipping'
        Save-FixtureReceipt $Fixture
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'Expected one .* game receipt; found 0'
    }

    Invoke-TestCase 'Receipt missing one required Digimon runtime dependency is rejected' {
        $Fixture = New-ReceiptFixture
        $Fixture.Receipt.RuntimeDependencies = @($Fixture.Receipt.RuntimeDependencies | Where-Object { $_.Path -notlike '*DigimonCombat.json' })
        Save-FixtureReceipt $Fixture
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'DigimonVenomNXTRuntime is missing.*DigimonCombat.json'
    }

    Invoke-TestCase 'Receipt referring to an absent Digimon runtime resource is rejected' {
        $Fixture = New-ReceiptFixture
        [IO.File]::Delete($Fixture.ResourcePaths[1])
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'Missing Digimon runtime resource'
    }

    Invoke-TestCase 'Receipt referring to an absent native executable is rejected' {
        $Fixture = New-ReceiptFixture
        [IO.File]::Delete($Fixture.Executable)
        Assert-Throws { Invoke-FixtureBuildCheck $Fixture } 'Missing native game executable'
    }

    Invoke-TestCase 'Archive containing the verified native binary passes its SHA256 check' {
        $Fixture = New-ReceiptFixture
        $Build = Invoke-FixtureBuildCheck $Fixture
        $Archive = Join-Path $Fixture.Root 'Packaged Output'
        $ArchivedExecutable = Join-Path $Archive 'Windows/DigimonVenomNXT/Binaries/Win64/DigimonVenomNXT.exe'
        [void][IO.Directory]::CreateDirectory((Split-Path $ArchivedExecutable -Parent))
        [IO.File]::Copy($Fixture.Executable, $ArchivedExecutable, $false)
        $Result = @(Assert-DigimonPackagedGame -ArchiveDirectory $Archive -Executables $Build.Executables)
        Assert-True ($Result.Count -eq 1 -and $Result[0] -ceq $ArchivedExecutable) 'Archive verification returned the wrong native binary.'
    }

    Invoke-TestCase 'Archive with a different same-name executable is rejected' {
        $Fixture = New-ReceiptFixture
        $Build = Invoke-FixtureBuildCheck $Fixture
        $Archive = Join-Path $Fixture.Root 'Packaged Output'
        Write-TestText (Join-Path $Archive 'Windows/DigimonVenomNXT/Binaries/Win64/DigimonVenomNXT.exe') 'Different stale executable bytes.'
        Assert-Throws { Assert-DigimonPackagedGame -ArchiveDirectory $Archive -Executables $Build.Executables } 'does not contain the verified native game binary'
    }

    Write-Host "`nNative build helper checks: $script:Passed passed, $($script:Failures.Count) failed."
    if ($script:Failures.Count -gt 0) {
        throw ("Native build helper regression failures:`n" + ($script:Failures -join "`n"))
    }
}
finally {
    # Only this invocation's GUID-named temporary fixture directory is removed.
    if (Test-Path -LiteralPath $TestRoot -PathType Container) {
        Remove-Item -LiteralPath $TestRoot -Recurse -Force
    }
}
