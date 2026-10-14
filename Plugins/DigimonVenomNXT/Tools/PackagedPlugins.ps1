# PowerShell 5.1. Dot-sourcing this file performs no writes or Unreal operations.
# UE FPluginManifest: Contents[] entries contain File and the embedded Descriptor.
# https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Projects/FPluginManifest
# https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Projects/FPluginManifestEntry
# https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Projects/FPluginReferenceDescriptor
$script:DigimonPackagedPluginsToolsDirectory = $PSScriptRoot

function Get-DigimonManifestField {
    param($Object, [string]$Name, [string]$LegacyName = '')
    if ($null -ne $Object -and $Object.PSObject.Properties[$Name]) { return $Object.$Name }
    if ($LegacyName -and $null -ne $Object -and $Object.PSObject.Properties[$LegacyName]) { return $Object.$LegacyName }
    return
}

function Test-DigimonManifestPlatform {
    param($Descriptor)
    $Platforms = @(Get-DigimonManifestField $Descriptor 'SupportedTargetPlatforms')
    $Explicit = (Get-DigimonManifestField $Descriptor 'HasExplicitPlatforms') -eq $true
    return (($Platforms.Count -eq 0 -and !$Explicit) -or $Platforms -contains 'Win64')
}

function Test-DigimonManifestReference {
    param($Reference, [string]$Configuration)
    if ((Get-DigimonManifestField $Reference 'Enabled') -ne $true) { return $false }
    $PlatformAllow = @(Get-DigimonManifestField $Reference 'PlatformAllowList' 'WhitelistPlatforms')
    $PlatformDeny = @(Get-DigimonManifestField $Reference 'PlatformDenyList' 'BlacklistPlatforms')
    $Explicit = (Get-DigimonManifestField $Reference 'HasExplicitPlatforms') -eq $true
    if (($PlatformAllow.Count -gt 0 -or $Explicit) -and $PlatformAllow -notcontains 'Win64') { return $false }
    if ($PlatformDeny -contains 'Win64') { return $false }
    if (!(Test-DigimonManifestPlatform $Reference)) { return $false }
    $TargetAllow = @(Get-DigimonManifestField $Reference 'TargetAllowList' 'WhitelistTargets')
    $TargetDeny = @(Get-DigimonManifestField $Reference 'TargetDenyList' 'BlacklistTargets')
    if ($TargetAllow.Count -gt 0 -and $TargetAllow -notcontains 'Game') { return $false }
    if ($TargetDeny -contains 'Game') { return $false }
    $ConfigAllow = @(Get-DigimonManifestField $Reference 'TargetConfigurationAllowList' 'WhitelistTargetConfigurations')
    $ConfigDeny = @(Get-DigimonManifestField $Reference 'TargetConfigurationDenyList' 'BlacklistTargetConfigurations')
    if ($ConfigAllow.Count -gt 0 -and $ConfigAllow -notcontains $Configuration) { return $false }
    if ($ConfigDeny -contains $Configuration) { return $false }
    return $true
}

function Assert-DigimonPluginManifestContents {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $true)][string]$ArchiveDirectory,
        [ValidateSet('Development', 'Shipping')][string]$Configuration = 'Development',
        [string]$ManifestPath = '',
        [string[]]$AdditionalManifestPaths = @()
    )
    if (!(Test-Path -LiteralPath $ArchiveDirectory -PathType Container)) {
        throw "Cannot validate plugin dependencies: archive directory is missing: $ArchiveDirectory"
    }
    $ArchivePrefix = (Get-Item -LiteralPath $ArchiveDirectory).FullName.TrimEnd([char[]]'\/') + [IO.Path]::DirectorySeparatorChar
    $ManifestMatches = @()
    if ($ManifestPath) {
        if (!(Test-Path -LiteralPath $ManifestPath -PathType Leaf)) { throw "Extracted plugin manifest is missing: $ManifestPath" }
        $Candidates = @(Get-Item -LiteralPath $ManifestPath)
    } else {
        $Candidates = @(Get-ChildItem -LiteralPath $ArchiveDirectory -Filter '*.upluginmanifest' -File -Recurse | Where-Object {
            $RelativePath = $_.FullName.Substring($ArchivePrefix.Length)
            $_.Directory.Name -eq 'Plugins' -and $RelativePath -notmatch '(^|[\\/])Engine[\\/]'
        })
    }
    foreach ($AdditionalPath in $AdditionalManifestPaths) { $Candidates += Get-Item -LiteralPath $AdditionalPath -ErrorAction Stop }
    foreach ($File in $Candidates) {
        try { $Manifest = Get-Content -LiteralPath $File.FullName -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop }
        catch { throw "Invalid packaged plugin manifest '$($File.FullName)': $($_.Exception.Message)" }
        if (!$Manifest.PSObject.Properties['Contents'] -or $Manifest.Contents -isnot [System.Array]) { throw "Packaged plugin manifest has no Contents array: $($File.FullName)" }
        $Entries = @($Manifest.Contents)
        $ContainsDigimon = @($Entries | Where-Object {
            $EntryFile = [string](Get-DigimonManifestField $_ 'File')
            ($EntryFile -replace '\\', '/') -match '(^|/)DigimonVenomNXT\.uplugin$'
        }).Count -gt 0
        if ($ContainsDigimon) { $ManifestMatches += [pscustomobject]@{ File = $File.FullName; Entries = $Entries } }
    }
    if ($ManifestMatches.Count -ne 1) {
        throw "Expected one packaged project plugin manifest containing DigimonVenomNXT; found $($ManifestMatches.Count) under '$ArchiveDirectory'. Plugin dependencies have not been verified. If the manifest is inside a pak, extract that build's .upluginmanifest with UnrealPak and pass -ManifestPath."
    }
    $Match = $ManifestMatches[0]
    $ByName = @{}
    foreach ($Entry in $Match.Entries) {
        $EntryFile = [string](Get-DigimonManifestField $Entry 'File')
        $Normalized = $EntryFile -replace '\\', '/'
        $FileMatch = [regex]::Match($Normalized, '(^|/)([^/]+)\.uplugin$', [Text.RegularExpressions.RegexOptions]::IgnoreCase)
        if (!$FileMatch.Success) { throw "Invalid plugin File in '$($Match.File)': $EntryFile" }
        $Name = $FileMatch.Groups[2].Value
        if ($ByName.ContainsKey($Name)) { throw "Duplicate plugin '$Name' in '$($Match.File)'." }
        $Descriptor = Get-DigimonManifestField $Entry 'Descriptor'
        if ($null -eq $Descriptor -or $Descriptor -isnot [pscustomobject]) {
            throw "Plugin '$Name' has no embedded Descriptor in '$($Match.File)'."
        }
        # File is a logical path. UAT embeds descriptors here; a loose .uplugin
        # is not required in a pak/IoStore archive.
        $ByName[$Name] = $Descriptor
    }
    $SourcePath = Join-Path (Split-Path $script:DigimonPackagedPluginsToolsDirectory -Parent) 'DigimonVenomNXT.uplugin'
    $Source = Get-Content -LiteralPath $SourcePath -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
    $Queue = New-Object 'System.Collections.Generic.Queue[object]'
    $Queue.Enqueue([pscustomobject]@{ Name = 'DigimonVenomNXT'; Chain = 'DigimonVenomNXT'; Required = $true; Optional = $false })
    foreach ($Dependency in @(Get-DigimonManifestField $Source 'Plugins')) {
        if (Test-DigimonManifestReference $Dependency $Configuration) {
            $Name = [string](Get-DigimonManifestField $Dependency 'Name')
            $Optional = (Get-DigimonManifestField $Dependency 'Optional') -eq $true
            $Queue.Enqueue([pscustomobject]@{ Name = $Name; Chain = "DigimonVenomNXT -> $Name"; Required = !$Optional; Optional = $Optional })
        }
    }
    # These are runtime requirements, even if a stale embedded Digimon descriptor
    # accidentally omits its dependency references.
    foreach ($Name in @('Paper2D', 'CommonUI', 'EnhancedInput')) {
        $Queue.Enqueue([pscustomobject]@{ Name = $Name; Chain = "DigimonVenomNXT -> $Name"; Required = $true; Optional = $false })
    }
    $Visited = @{}
    while ($Queue.Count -gt 0) {
        $Next = $Queue.Dequeue()
        if (!$ByName.ContainsKey($Next.Name)) {
            if ($Next.Optional) { continue }
            throw "Packaged plugin dependency is missing: $($Next.Chain). Manifest: $($Match.File). Do not distribute this build; rebuild and stage with the required plugins enabled."
        }
        $Descriptor = $ByName[$Next.Name]
        if (!(Test-DigimonManifestPlatform $Descriptor)) {
            if ($Next.Required) { throw "Required plugin does not support Win64: $($Next.Chain). Manifest: $($Match.File)" }
            continue
        }
        if ($Visited.ContainsKey($Next.Name)) { continue }
        $Visited[$Next.Name] = $true
        foreach ($Dependency in @(Get-DigimonManifestField $Descriptor 'Plugins')) {
            if (!(Test-DigimonManifestReference $Dependency $Configuration)) { continue }
            $Name = [string](Get-DigimonManifestField $Dependency 'Name')
            if ([string]::IsNullOrWhiteSpace($Name)) { throw "Unnamed required plugin reference in '$($Next.Name)'." }
            $Optional = (Get-DigimonManifestField $Dependency 'Optional') -eq $true
            $Queue.Enqueue([pscustomobject]@{ Name = $Name; Chain = "$($Next.Chain) -> $Name"; Required = $false; Optional = $Optional })
        }
    }
    return [pscustomobject]@{ Manifest = $Match.File; Configuration = $Configuration; Plugins = @($Visited.Keys | Sort-Object) }
}

function Assert-DigimonPluginManifest {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $true)][string]$ArchiveDirectory,
        [ValidateSet('Development', 'Shipping')][string]$Configuration = 'Development',
        [string]$ManifestPath = '',
        [string]$EngineRoot = '',
        [string]$CryptoKeys = ''
    )
    if (!(Test-Path -LiteralPath $ArchiveDirectory -PathType Container)) {
        throw "Cannot validate plugin dependencies: archive directory is missing: $ArchiveDirectory"
    }
    $ArchivePrefix = (Get-Item -LiteralPath $ArchiveDirectory).FullName.TrimEnd([char[]]'\/') + [IO.Path]::DirectorySeparatorChar
    if ($ManifestPath) {
        return Assert-DigimonPluginManifestContents -ArchiveDirectory $ArchiveDirectory -Configuration $Configuration -ManifestPath $ManifestPath
    }
    $LooseManifests = @(Get-ChildItem -LiteralPath $ArchiveDirectory -Filter '*.upluginmanifest' -File -Recurse | Where-Object {
        $RelativePath = $_.FullName.Substring($ArchivePrefix.Length)
        $_.Directory.Name -eq 'Plugins' -and $RelativePath -notmatch '(^|[\\/])Engine[\\/]'
    })
    $Paks = @(Get-ChildItem -LiteralPath $ArchiveDirectory -Filter '*.pak' -File -Recurse | Where-Object {
        $RelativePath = $_.FullName.Substring($ArchivePrefix.Length)
        $RelativePath -match '[\\/]Content[\\/]Paks[\\/][^\\/]+\.pak$' -and
        $RelativePath -notmatch '(^|[\\/])(Engine|Plugins)[\\/]'
    } | Sort-Object FullName)
    if ($Paks.Count -eq 0 -and $LooseManifests.Count -gt 0) {
        return Assert-DigimonPluginManifestContents -ArchiveDirectory $ArchiveDirectory -Configuration $Configuration
    }
    # CreatePluginManifest stages this JSON as UFS. With -pak/-iostore it is
    # normally embedded in the accompanying .pak, so inspect that real payload.
    if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
        throw 'Pass -EngineRoot to inspect the packaged .pak with UnrealPak, or -ManifestPath for a manifest extracted from this build. Dependencies have not been verified.'
    }
    $UnrealPak = Join-Path $EngineRoot 'Engine/Binaries/Win64/UnrealPak.exe'
    if (!(Test-Path -LiteralPath $UnrealPak -PathType Leaf)) {
        throw "Cannot inspect packaged plugin dependencies: UnrealPak is missing: $UnrealPak"
    }
    if ($Paks.Count -eq 0) { throw "No project plugin manifest or .pak was found in '$ArchiveDirectory'. Dependencies have not been verified." }
    if ($CryptoKeys -and !(Test-Path -LiteralPath $CryptoKeys -PathType Leaf)) { throw "The supplied UnrealPak crypto-key file is missing: $CryptoKeys" }
    $ExtractionRoot = Join-Path ([IO.Path]::GetTempPath()) ('DigimonPluginManifest-' + [guid]::NewGuid().ToString('N'))
    try {
        New-Item -ItemType Directory -Path $ExtractionRoot -ErrorAction Stop | Out-Null
        for ($Index = 0; $Index -lt $Paks.Count; $Index++) {
            $Destination = Join-Path $ExtractionRoot ('pak-' + $Index.ToString('D4'))
            New-Item -ItemType Directory -Path $Destination -ErrorAction Stop | Out-Null
            Write-Host "Inspecting packaged plugin manifest: $($Paks[$Index].FullName)"
            # Separate destinations preserve evidence of ambiguous duplicate manifests.
            # Extract only manifest JSON; never edit the archive or copy engine plugins.
            $PakArguments = @($Paks[$Index].FullName, '-Extract', $Destination, '-Filter=*.upluginmanifest', '-ExtractToMountPoint')
            if ($CryptoKeys) { $PakArguments += '-cryptokeys=' + [IO.Path]::GetFullPath($CryptoKeys) }
            & $UnrealPak @PakArguments | Out-Host
            if ($LASTEXITCODE -ne 0) {
                throw "UnrealPak could not inspect '$($Paks[$Index].FullName)' (exit $LASTEXITCODE). Dependencies have not been verified."
            }
        }
        $Result = Assert-DigimonPluginManifestContents -ArchiveDirectory $ExtractionRoot -Configuration $Configuration -AdditionalManifestPaths @($LooseManifests | ForEach-Object { $_.FullName })
        $ExtractedPath = $Result.Manifest
        $Result.Manifest = 'Verified packaged plugin manifest in ' + [IO.Path]::GetFullPath($ArchiveDirectory)
        $Result | Add-Member -NotePropertyName ExtractedManifest -NotePropertyValue $ExtractedPath
        return $Result
    } finally {
        # This directory is created uniquely by this invocation; no user data is removed.
        if (Test-Path -LiteralPath $ExtractionRoot) { Remove-Item -LiteralPath $ExtractionRoot -Recurse -Force -ErrorAction Stop }
    }
}
