# Run with Windows PowerShell 5.1 or newer. No Unreal installation is needed.
# Creates synthetic package manifests in a unique temporary directory only.
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
. (Join-Path $PSScriptRoot 'PackagedPlugins.ps1')

$TestRoot = Join-Path ([IO.Path]::GetTempPath()) ('DigimonManifestTests-' + [guid]::NewGuid().ToString('N'))
$script:DigimonManifestTestCount = 0

function New-TestPlugin {
    param([string]$Name, [object[]]$Dependencies = @())
    return [ordered]@{
        File = '../../../Engine/Plugins/' + $Name + '/' + $Name + '.uplugin'
        Descriptor = [ordered]@{ FileVersion = 3; Version = 1; Plugins = @($Dependencies) }
    }
}
function New-TestReference {
    param([string]$Name)
    return [ordered]@{ Name = $Name; Enabled = $true }
}
function Write-TestManifest {
    param([string]$Path, $Data)
    New-Item -ItemType Directory -Path (Split-Path $Path -Parent) -Force | Out-Null
    [IO.File]::WriteAllText($Path, ($Data | ConvertTo-Json -Depth 30), (New-Object Text.UTF8Encoding($false)))
}
function Test-ManifestCase {
    param([string]$Name, [scriptblock]$Mutate, [string]$ExpectedError = '',
          [string]$Configuration = 'Development', [switch]$ExplicitPath)
    $CaseDirectory = Join-Path $TestRoot $Name
    $ManifestFile = Join-Path $CaseDirectory 'Windows/DigimonVenomNXT/Plugins/DigimonVenomNXT.upluginmanifest'
    $Data = [ordered]@{ Contents = @(
        (New-TestPlugin 'DigimonVenomNXT' @((New-TestReference 'Paper2D'), (New-TestReference 'CommonUI'), (New-TestReference 'EnhancedInput'))),
        (New-TestPlugin 'Paper2D'),
        (New-TestPlugin 'CommonUI' @((New-TestReference 'FixtureInputSupport'))),
        (New-TestPlugin 'EnhancedInput'),
        (New-TestPlugin 'FixtureInputSupport')
    ) }
    New-Item -ItemType Directory -Path $CaseDirectory -Force | Out-Null
    & $Mutate $Data $CaseDirectory
    Write-TestManifest $ManifestFile $Data
    $Caught = ''
    try {
        $Arguments = @{ ArchiveDirectory = $CaseDirectory; Configuration = $Configuration }
        if ($ExplicitPath) { $Arguments['ManifestPath'] = $ManifestFile }
        $Result = Assert-DigimonPluginManifest @Arguments
        if ($Result.Plugins -notcontains 'CommonUI') { throw 'Successful result omitted CommonUI.' }
    } catch { $Caught = $_.Exception.Message }
    if ($ExpectedError) {
        if ($Caught -notlike "*$ExpectedError*") { throw "FAIL ${Name}: expected '$ExpectedError', got '$Caught'." }
    } elseif ($Caught) { throw "FAIL ${Name}: $Caught" }
    $script:DigimonManifestTestCount++
    Write-Host "PASS $Name"
}

try {
    Test-ManifestCase 'embedded-descriptors-no-loose-uplugins' { param($D, $P) }
    Test-ManifestCase 'Engine/Plugins/archive-parent-names' { param($D, $P) }
    Test-ManifestCase 'shipping' { param($D, $P) } -Configuration Shipping
    Test-ManifestCase 'commonui-missing' { param($D, $P) $D.Contents = @($D.Contents | Where-Object { $_.File -notmatch '/CommonUI/' }) } 'DigimonVenomNXT -> CommonUI'
    Test-ManifestCase 'transitive-required-plugin-missing' { param($D, $P) $D.Contents = @($D.Contents | Where-Object { $_.File -notmatch '/FixtureInputSupport/' }) } 'CommonUI -> FixtureInputSupport'
    Test-ManifestCase 'stale-root-descriptor' { param($D, $P) $D.Contents[0].Descriptor.Plugins = @(); $D.Contents = @($D.Contents | Where-Object { $_.File -notmatch '/CommonUI/' }) } 'DigimonVenomNXT -> CommonUI'
    Test-ManifestCase 'optional-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'OptionalMissing'; Enabled = $true; Optional = $true }) }
    Test-ManifestCase 'present-optional-transitive-required' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'FixtureInputSupport'; Enabled = $true; Optional = $true }); $D.Contents[4].Descriptor.Plugins = @((New-TestReference 'RequiredBelowOptional')) } 'FixtureInputSupport -> RequiredBelowOptional'
    Test-ManifestCase 'disabled-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'DisabledMissing'; Enabled = $false }) }
    Test-ManifestCase 'editor-only-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'EditorMissing'; Enabled = $true; TargetAllowList = @('Editor') }) }
    Test-ManifestCase 'game-denied-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'GameDenied'; Enabled = $true; TargetDenyList = @('Game') }) }
    Test-ManifestCase 'linux-only-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'LinuxMissing'; Enabled = $true; PlatformAllowList = @('Linux') }) }
    Test-ManifestCase 'win64-denied-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'Win64Denied'; Enabled = $true; PlatformDenyList = @('Win64') }) }
    Test-ManifestCase 'reference-unsupported-missing' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'UnsupportedMissing'; Enabled = $true; SupportedTargetPlatforms = @('Linux') }) }
    Test-ManifestCase 'explicit-empty-platforms' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'ExtensionOnly'; Enabled = $true; HasExplicitPlatforms = $true; PlatformAllowList = @(); SupportedTargetPlatforms = @() }) }
    Test-ManifestCase 'legacy-platform-filter' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'LegacyMissing'; Enabled = $true; WhitelistPlatforms = @('Linux') }) }
    Test-ManifestCase 'shipping-only-ignored-in-development' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'ShippingDependency'; Enabled = $true; TargetConfigurationAllowList = @('Shipping') }) }
    Test-ManifestCase 'shipping-only-required-in-shipping' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'ShippingDependency'; Enabled = $true; TargetConfigurationAllowList = @('Shipping') }) } 'CommonUI -> ShippingDependency' -Configuration Shipping
    Test-ManifestCase 'shipping-denied' { param($D, $P) $D.Contents[2].Descriptor.Plugins = @([ordered]@{ Name = 'ShippingDenied'; Enabled = $true; TargetConfigurationDenyList = @('Shipping') }) } -Configuration Shipping
    Test-ManifestCase 'mandatory-plugin-platform-incompatible' { param($D, $P) $D.Contents[2].Descriptor['SupportedTargetPlatforms'] = @('Linux') } 'Required plugin does not support Win64'
    Test-ManifestCase 'cycles-terminate' { param($D, $P) $D.Contents[4].Descriptor.Plugins = @((New-TestReference 'CommonUI')) }
    Test-ManifestCase 'engine-manifest-ignored' { param($D, $P) Write-TestManifest (Join-Path $P 'Windows/Engine/Plugins/Engine.upluginmanifest') $D }
    Test-ManifestCase 'unrelated-project-ignored' { param($D, $P) Write-TestManifest (Join-Path $P 'Windows/Other/Plugins/Other.upluginmanifest') ([ordered]@{ Contents = @((New-TestPlugin 'Other')) }) }
    Test-ManifestCase 'two-project-manifests-fail' { param($D, $P) Write-TestManifest (Join-Path $P 'Copy/DigimonVenomNXT/Plugins/DigimonVenomNXT.upluginmanifest') $D } 'found 2'
    Test-ManifestCase 'explicit-extracted-manifest' { param($D, $P) Write-TestManifest (Join-Path $P 'Copy/DigimonVenomNXT/Plugins/DigimonVenomNXT.upluginmanifest') $D } -ExplicitPath
    Test-ManifestCase 'duplicate-plugin-entry' { param($D, $P) $D.Contents += (New-TestPlugin 'CommonUI') } "Duplicate plugin 'CommonUI'"
    Test-ManifestCase 'missing-descriptor' { param($D, $P) $D.Contents[2].Remove('Descriptor') } 'no embedded Descriptor'
    Test-ManifestCase 'missing-contents-array' { param($D, $P) $D.Contents = [ordered]@{ File = 'DigimonVenomNXT.uplugin'; Descriptor = [ordered]@{ FileVersion = 3 } } } 'no Contents array'
    Test-ManifestCase 'no-digimon-manifest' { param($D, $P) $D.Contents = @((New-TestPlugin 'Other')) } 'found 0'
    Test-ManifestCase 'loose-does-not-hide-uninspected-pak' { param($D, $P) $Pak = Join-Path $P 'Windows/DigimonVenomNXT/Content/Paks/DigimonVenomNXT-Windows.pak'; New-Item -ItemType Directory -Path (Split-Path $Pak -Parent) -Force | Out-Null; [IO.File]::WriteAllText($Pak, 'fixture only') } 'Pass -EngineRoot'
    Write-Host "$script:DigimonManifestTestCount manifest fixture checks passed. This is not an Unreal build or launch test."
} finally {
    if (Test-Path -LiteralPath $TestRoot) { Remove-Item -LiteralPath $TestRoot -Recurse -Force }
}
