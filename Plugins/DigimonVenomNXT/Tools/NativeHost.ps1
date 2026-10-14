# Dot-source this file, then call Ensure-DigimonNativeHost -Project <file.uproject>.
# Compatible with Windows PowerShell 5.1. This file does not start Unreal.
function Ensure-DigimonNativeHost {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [string]$Project,
        [switch]$DryRun
    )

    $ErrorActionPreference = 'Stop'
    Set-StrictMode -Version 2.0

    function Get-DigimonTargetDeclarations {
        param([string]$SourceRoot)
        if (!(Test-Path -LiteralPath $SourceRoot -PathType Container)) { return }
        foreach ($TargetFile in @(Get-ChildItem -LiteralPath $SourceRoot -Filter '*.Target.cs' -File -Recurse)) {
            $TargetText = [IO.File]::ReadAllText($TargetFile.FullName)
            # Remove comments and string literals before inspecting declarations.
            # Custom C# is never executed or rewritten by this installer.
            $LexicalPattern = '(?s)/\*.*?\*/|//[^\r\n]*|@"(?:""|[^"])*"|"(?:\\.|[^"\\])*"|''(?:\\.|[^''\\])*'''
            $Code = [regex]::Replace($TargetText, $LexicalPattern, ' ')
            $Classes = @([regex]::Matches($Code, '\bclass\s+([A-Za-z_][A-Za-z0-9_]*)\s*:\s*(?:UnrealBuildTool\.)?TargetRules\b'))
            $Kinds = @([regex]::Matches($Code, '\bType\s*=\s*(?:UnrealBuildTool\.)?TargetType\.(Game|Editor|Client|Server|Program)\s*;') | ForEach-Object { $_.Groups[1].Value } | Select-Object -Unique)
            if ($Classes.Count -ne 1 -or $Kinds.Count -ne 1) {
                throw "Cannot safely determine the target declared in '$($TargetFile.FullName)'. Keep your custom target files; give each Game/Editor target one explicit Type = TargetType.Game/Editor assignment before using this helper."
            }
            $FileTargetName = $TargetFile.Name.Substring(0, $TargetFile.Name.Length - '.Target.cs'.Length)
            if ($Classes[0].Groups[1].Value -cne ($FileTargetName + 'Target')) {
                throw "Target class and filename disagree in '$($TargetFile.FullName)'. Unreal requires a class named '$($FileTargetName)Target' for '$($TargetFile.Name)'."
            }
            [pscustomobject]@{ Name = $FileTargetName; Kind = $Kinds[0]; Path = $TargetFile.FullName }
        }
    }

    function Set-DigimonProperty {
        param($Object, [string]$Name, $Value)
        if ($null -ne $Object.PSObject.Properties[$Name]) {
            $Object.PSObject.Properties[$Name].Value = $Value
        }
        else {
            $Object | Add-Member -MemberType NoteProperty -Name $Name -Value $Value
        }
    }

    function Get-DigimonNormalizedText {
        param([string]$Text)
        return $Text.Replace("`r`n", "`n").TrimEnd([char[]]"`r`n")
    }

    function Enable-DigimonRequiredPlugin {
        param($Reference)
        Set-DigimonProperty -Object $Reference -Name 'Enabled' -Value $true
        if ($null -ne $Reference.PSObject.Properties['Optional']) {
            Set-DigimonProperty -Object $Reference -Name 'Optional' -Value $false
        }
        # Repair only exclusions affecting the two targets/configurations built
        # by this Windows helper. Preserve unrelated platforms and custom fields.
        $ExplicitPlatforms = $null -ne $Reference.PSObject.Properties['HasExplicitPlatforms'] -and $Reference.HasExplicitPlatforms -eq $true
        $Filters = @(
            @{ Allow = 'PlatformAllowList'; Deny = 'PlatformDenyList'; Required = @('Win64'); Explicit = $ExplicitPlatforms },
            @{ Allow = 'WhitelistPlatforms'; Deny = 'BlacklistPlatforms'; Required = @('Win64'); Explicit = $false },
            @{ Allow = 'SupportedTargetPlatforms'; Deny = ''; Required = @('Win64'); Explicit = $ExplicitPlatforms },
            @{ Allow = 'TargetAllowList'; Deny = 'TargetDenyList'; Required = @('Game', 'Editor'); Explicit = $false },
            @{ Allow = 'WhitelistTargets'; Deny = 'BlacklistTargets'; Required = @('Game', 'Editor'); Explicit = $false },
            @{ Allow = 'TargetConfigurationAllowList'; Deny = 'TargetConfigurationDenyList'; Required = @('Development', 'Shipping'); Explicit = $false },
            @{ Allow = 'WhitelistTargetConfigurations'; Deny = 'BlacklistTargetConfigurations'; Required = @('Development', 'Shipping'); Explicit = $false }
        )
        foreach ($Filter in $Filters) {
            $Allowed = @()
            if ($null -ne $Reference.PSObject.Properties[$Filter.Allow]) { $Allowed = @($Reference.PSObject.Properties[$Filter.Allow].Value | Where-Object { $null -ne $_ }) }
            if ($Allowed.Count -gt 0 -or $Filter.Explicit) {
                foreach ($RequiredValue in $Filter.Required) {
                    if ($Allowed -notcontains $RequiredValue) { $Allowed += $RequiredValue }
                }
                Set-DigimonProperty -Object $Reference -Name $Filter.Allow -Value $Allowed
            }
            if ($Filter.Deny -ne '' -and $null -ne $Reference.PSObject.Properties[$Filter.Deny]) {
                $Denied = @($Reference.PSObject.Properties[$Filter.Deny].Value | Where-Object { $null -ne $_ -and $Filter.Required -notcontains $_ })
                Set-DigimonProperty -Object $Reference -Name $Filter.Deny -Value $Denied
            }
        }
        if ($null -ne $Reference.PSObject.Properties['TargetsToExplicitlyLoad']) {
            $ExplicitTargets = @($Reference.TargetsToExplicitlyLoad | Where-Object { $_ -ine 'Game' -and $_ -ine 'Editor' })
            Set-DigimonProperty -Object $Reference -Name 'TargetsToExplicitlyLoad' -Value $ExplicitTargets
        }
    }

    if (!(Test-Path -LiteralPath $Project -PathType Leaf) -or [IO.Path]::GetExtension($Project) -ine '.uproject') {
        throw "Project file not found or not a .uproject: $Project"
    }
    $Project = (Resolve-Path -LiteralPath $Project).ProviderPath
    $ProjectRoot = Split-Path $Project -Parent
    $ProjectName = [IO.Path]::GetFileNameWithoutExtension($Project)
    $SourceRoot = Join-Path $ProjectRoot 'Source'
    if ((Test-Path -LiteralPath $SourceRoot) -and !(Test-Path -LiteralPath $SourceRoot -PathType Container)) {
        throw "The project Source path is a file, not a directory: $SourceRoot. It was not overwritten."
    }
    $OriginalDescriptor = [IO.File]::ReadAllText($Project)
    $Descriptor = $OriginalDescriptor | ConvertFrom-Json
    if ($null -eq $Descriptor -or $Descriptor -isnot [pscustomobject]) {
        throw "The project descriptor must be a JSON object: $Project"
    }

    $Modules = @()
    if ($null -ne $Descriptor.PSObject.Properties['Modules']) {
        $Modules = @($Descriptor.Modules | Where-Object { $null -ne $_ })
    }
    foreach ($Module in $Modules) {
        if ($null -eq $Module.PSObject.Properties['Name'] -or [string]::IsNullOrWhiteSpace([string]$Module.Name)) {
            throw 'The project Modules array contains an entry without a valid Name. Correct that descriptor entry before building.'
        }
    }

    $HostModule = 'DigimonVenomNXTHost'
    $OtherModules = @($Modules | Where-Object { $_.Name -ine $HostModule })
    $HostModules = @($Modules | Where-Object { $_.Name -ieq $HostModule })
    if ($HostModules.Count -gt 1) {
        throw 'The project descriptor contains duplicate DigimonVenomNXTHost modules. Keep one valid entry before building.'
    }
    $TargetDeclarations = @(Get-DigimonTargetDeclarations -SourceRoot $SourceRoot)
    $ExpectedFiles = @{}
    $MissingFiles = @()
    $CreateHost = $OtherModules.Count -eq 0
    if ($CreateHost) {
        if ($ProjectName -cnotmatch '^[A-Za-z_][A-Za-z0-9_]*$') {
            throw "The project filename '$ProjectName.uproject' cannot form an Unreal C# target name. Use a project filename containing letters, digits and underscores, starting with a letter or underscore, or supply your existing native Game/Editor targets. Folder names may contain spaces."
        }
        $GameTarget = $ProjectName
        $EditorTarget = $ProjectName + 'Editor'
        $TargetTemplate = @'
// Digimon Venom NXT native host target. Generated by Tools/NativeHost.ps1.
using UnrealBuildTool;

public class __TARGET__Target : TargetRules
{
    public __TARGET__Target(TargetInfo Target) : base(Target)
    {
        Type = TargetType.__KIND__;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("DigimonVenomNXTHost");
    }
}
'@
        $ExpectedFiles[(Join-Path $SourceRoot ($GameTarget + '.Target.cs'))] = $TargetTemplate.Replace('__TARGET__', $GameTarget).Replace('__KIND__', 'Game')
        $ExpectedFiles[(Join-Path $SourceRoot ($EditorTarget + '.Target.cs'))] = $TargetTemplate.Replace('__TARGET__', $EditorTarget).Replace('__KIND__', 'Editor')
        $HostRoot = Join-Path $SourceRoot $HostModule
        $ExpectedFiles[(Join-Path $HostRoot ($HostModule + '.Build.cs'))] = @'
// Digimon Venom NXT primary game module. Generated by Tools/NativeHost.ps1.
using UnrealBuildTool;

public class DigimonVenomNXTHost : ModuleRules
{
    public DigimonVenomNXTHost(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "DigimonVenomNXTRuntime"
        });
    }
}
'@
        $PrimaryModuleTemplate = @'
// Digimon Venom NXT primary game module. Generated by Tools/NativeHost.ps1.
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, DigimonVenomNXTHost, "__PROJECT__");
'@
        $ExpectedFiles[(Join-Path $HostRoot ($HostModule + '.cpp'))] = $PrimaryModuleTemplate.Replace('__PROJECT__', $ProjectName)

        # Recognize only our exact files when resuming an interrupted setup.
        # Any other source may already implement a primary game module.
        if (Test-Path -LiteralPath $SourceRoot -PathType Container) {
            foreach ($SourceFile in @(Get-ChildItem -LiteralPath $SourceRoot -File -Recurse)) {
                if (!$ExpectedFiles.ContainsKey($SourceFile.FullName)) {
                    # A terminated process may leave its same-directory temporary
                    # file. Its .tmp suffix is not C++/C# source; retain it safely.
                    $TemporaryMatch = [regex]::Match($SourceFile.FullName, '^(.+)\.[0-9a-f]{32}\.tmp$', [Text.RegularExpressions.RegexOptions]::IgnoreCase)
                    if ($TemporaryMatch.Success -and $ExpectedFiles.ContainsKey($TemporaryMatch.Groups[1].Value)) { continue }
                    throw "Existing project source was found at '$($SourceFile.FullName)', but there is no separate native module declared in the .uproject. No source was overwritten. Restore that project's native Modules/targets first; this helper will then use them."
                }
            }
        }
        foreach ($Path in @($ExpectedFiles.Keys | Sort-Object)) {
            if (Test-Path -LiteralPath $Path) {
                if (!(Test-Path -LiteralPath $Path -PathType Leaf) -or
                    (Get-DigimonNormalizedText ([IO.File]::ReadAllText($Path))) -cne (Get-DigimonNormalizedText $ExpectedFiles[$Path])) {
                    throw "A custom or modified file already exists at '$Path'. It was not overwritten. Preserve your custom source and configure its native module/targets explicitly before building."
                }
            }
            else {
                $MissingFiles += $Path
            }
        }
        if ($HostModules.Count -eq 1) {
            if ($null -eq $HostModules[0].PSObject.Properties['Type'] -or $HostModules[0].Type -cne 'Runtime' -or
                $null -eq $HostModules[0].PSObject.Properties['LoadingPhase'] -or $HostModules[0].LoadingPhase -cne 'Default') {
                throw 'Existing DigimonVenomNXTHost module settings differ from the generated Runtime/Default module. No descriptor settings were overwritten.'
            }
        }
        else {
            $Modules += [pscustomobject]@{ Name = $HostModule; Type = 'Runtime'; LoadingPhase = 'Default' }
            Set-DigimonProperty -Object $Descriptor -Name 'Modules' -Value $Modules
        }
    }
    else {
        # Existing projects retain their primary module and all native source.
        $Games = @($TargetDeclarations | Where-Object { $_.Kind -ceq 'Game' })
        $Editors = @($TargetDeclarations | Where-Object { $_.Kind -ceq 'Editor' })
        if ($Games.Count -ne 1 -or $Editors.Count -ne 1) {
            throw "This native project has $($Games.Count) identifiable Game targets and $($Editors.Count) Editor targets. This helper requires one of each to avoid building the wrong executable. Keep your source and build the intended targets explicitly with Unreal Build.bat, or resolve the missing/ambiguous target declarations."
        }
        $GameTarget = $Games[0].Name
        $EditorTarget = $Editors[0].Name
        $HostModule = $null
    }

    $Plugins = @()
    if ($null -ne $Descriptor.PSObject.Properties['Plugins']) {
        $Plugins = @($Descriptor.Plugins | Where-Object { $null -ne $_ })
    }
    foreach ($Plugin in $Plugins) {
        if ($null -eq $Plugin.PSObject.Properties['Name']) {
            throw 'The project Plugins array contains an entry without a Name. Correct that descriptor entry before building.'
        }
    }
    # Build.cs module dependencies are not a replacement for enabling plugins
    # in the host project. CommonUI must be included in UBT's plugin set so UAT
    # stages its descriptor as well as linking CommonUI/CommonInput modules.
    foreach ($RequiredPlugin in @('DigimonVenomNXT', 'Paper2D', 'CommonUI', 'EnhancedInput')) {
        $Matches = @($Plugins | Where-Object { $_.Name -ieq $RequiredPlugin })
        if ($Matches.Count -gt 1) {
            throw "The project descriptor contains duplicate $RequiredPlugin plugin entries. Keep one valid entry before building."
        }
        if ($Matches.Count -eq 0) {
            $Plugins += [pscustomobject]@{ Name = $RequiredPlugin; Enabled = $true }
        }
        else {
            Enable-DigimonRequiredPlugin -Reference $Matches[0]
        }
    }
    Set-DigimonProperty -Object $Descriptor -Name 'Plugins' -Value $Plugins

    # Compare JSON values, not whitespace, so repeating setup is a no-op.
    $OriginalCanonical = ($OriginalDescriptor | ConvertFrom-Json | ConvertTo-Json -Depth 100 -Compress)
    $UpdatedCanonical = ($Descriptor | ConvertTo-Json -Depth 100 -Compress)
    $DescriptorChanged = $OriginalCanonical -cne $UpdatedCanonical
    $Created = $CreateHost -and ($MissingFiles.Count -gt 0 -or $HostModules.Count -eq 0)
    if ($DryRun) {
        if ($Created) { Write-Host "Dry run: would install native Game target '$GameTarget' and Editor target '$EditorTarget'." }
        if ($DescriptorChanged) { Write-Host 'Dry run: would enable DigimonVenomNXT, Paper2D, CommonUI and EnhancedInput for Win64 Game/Editor in the project descriptor.' }
        return [pscustomobject]@{ GameTarget = $GameTarget; EditorTarget = $EditorTarget; HostModule = $HostModule; Created = $Created; DescriptorChanged = $DescriptorChanged }
    }

    if ($MissingFiles.Count -gt 0 -or $DescriptorChanged) {
        if ([IO.File]::ReadAllText($Project) -cne $OriginalDescriptor) {
            throw 'The project descriptor changed during validation. Save and close Unreal Editor, then run the build again.'
        }
        $Backup = $Project + '.digimon-native-host.' + [DateTime]::UtcNow.ToString('yyyyMMdd-HHmmss') + '.' + [Guid]::NewGuid().ToString('N') + '.bak'
        [IO.File]::Copy($Project, $Backup, $false)
        Write-Host "Project descriptor backup: $Backup"
        $Utf8 = New-Object System.Text.UTF8Encoding($false)
        foreach ($Path in $MissingFiles) {
            $ParentDirectory = Split-Path $Path -Parent
            [void][IO.Directory]::CreateDirectory($ParentDirectory)
            $TemporaryPath = $Path + '.' + [Guid]::NewGuid().ToString('N') + '.tmp'
            try {
                [IO.File]::WriteAllText($TemporaryPath, ($ExpectedFiles[$Path].Replace("`r`n", "`n").Replace("`n", "`r`n") + "`r`n"), $Utf8)
                # Move fails if another process created the destination. Never overwrite.
                [IO.File]::Move($TemporaryPath, $Path)
            }
            finally {
                if ([IO.File]::Exists($TemporaryPath)) { [IO.File]::Delete($TemporaryPath) }
            }
        }
        if ($DescriptorChanged) {
            if ([IO.File]::ReadAllText($Project) -cne $OriginalDescriptor) {
                throw 'The project descriptor changed during native target creation and was not overwritten. Close the editor and rerun; already created target files can be safely reused.'
            }
            $TemporaryDescriptor = $Project + '.' + [Guid]::NewGuid().ToString('N') + '.tmp'
            try {
                $DescriptorJson = ($Descriptor | ConvertTo-Json -Depth 100) + "`r`n"
                [IO.File]::WriteAllText($TemporaryDescriptor, $DescriptorJson, $Utf8)
                # Windows PowerShell converts a bare $null to an empty string for
                # this string parameter. .NET Framework rejects that backup path.
                # Use a unique same-directory backup and keep the earlier copy.
                $ReplacementBackup = [IO.Path]::ChangeExtension($TemporaryDescriptor, 'bak')
                [IO.File]::Replace($TemporaryDescriptor, $Project, $ReplacementBackup)
            }
            finally {
                if ([IO.File]::Exists($TemporaryDescriptor)) { [IO.File]::Delete($TemporaryDescriptor) }
            }
        }
    }
    return [pscustomobject]@{ GameTarget = $GameTarget; EditorTarget = $EditorTarget; HostModule = $HostModule; Created = $Created; DescriptorChanged = $DescriptorChanged }
}
