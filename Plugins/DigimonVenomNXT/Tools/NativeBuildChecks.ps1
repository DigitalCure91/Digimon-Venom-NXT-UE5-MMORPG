# PowerShell 5.1 compatible helpers. No Unreal process is started when dot-sourced.
function Resolve-DigimonChildPath {
    param([Parameter(Mandatory = $true)][string]$Root,
          [Parameter(Mandatory = $true)][string]$Relative)
    if ([IO.Path]::IsPathRooted($Relative)) { throw 'A content manifest path must be relative.' }
    $Prefix = [IO.Path]::GetFullPath($Root).TrimEnd([char[]]'\/') + [IO.Path]::DirectorySeparatorChar
    $Result = [IO.Path]::GetFullPath((Join-Path $Root $Relative))
    if (!$Result.StartsWith($Prefix, [StringComparison]::OrdinalIgnoreCase)) { throw 'A content manifest path escapes its source directory.' }
    return $Result
}

function Convert-DigimonPackageToFile {
    param([string]$PluginRoot, [string]$Package, [switch]$Map)
    if ($Package -cnotmatch '^/DigimonVenomNXT/[A-Za-z0-9_/]+$' -or $Package.Contains('//')) {
        throw "Invalid generated package path '$Package'."
    }
    $Suffix = '.uasset'
    if ($Map) { $Suffix = '.umap' }
    return Resolve-DigimonChildPath -Root (Join-Path $PluginRoot 'Content') -Relative ($Package.Substring('/DigimonVenomNXT/'.Length) + $Suffix)
}

function Get-DigimonContentReceiptPath {
    param([Parameter(Mandatory = $true)][string]$ProjectFolder,
          [Parameter(Mandatory = $true)][string]$PluginRoot)
    $Expected = [IO.Path]::GetFullPath((Join-Path $ProjectFolder 'Plugins/DigimonVenomNXT')).TrimEnd([char[]]'\/')
    $Installed = [IO.Path]::GetFullPath($PluginRoot).TrimEnd([char[]]'\/')
    if ($Installed -ine $Expected) { throw 'The content receipt must belong to the host project containing this installed DigimonVenomNXT plugin.' }
    # Matches FPaths::ProjectIntermediateDir() in the Unreal importer. Never accept
    # a stale receipt in the plugin folder or another project's Intermediate tree.
    return Join-Path $ProjectFolder 'Intermediate/DigimonVenomNXT/ContentImportReceipt.json'
}

function Assert-DigimonEngineVersion {
    param([Parameter(Mandatory = $true)][string]$EngineRoot)
    $VersionFile = Join-Path $EngineRoot 'Engine/Build/Build.version'
    if (!(Test-Path -LiteralPath $VersionFile -PathType Leaf)) { throw "Engine version metadata is missing: $VersionFile. Pass -EngineRoot with the complete UE 5.8 installation." }
    $Version = Get-Content -LiteralPath $VersionFile -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
    if (!$Version.PSObject.Properties['MajorVersion'] -or !$Version.PSObject.Properties['MinorVersion'] -or
        $Version.MajorVersion -ne 5 -or $Version.MinorVersion -ne 8) {
        throw "The selected engine is not Unreal Engine 5.8. Choose the correct -EngineRoot before importing or building."
    }
}

function Assert-DigimonImportCommandlet {
    param([Parameter(Mandatory = $true)][string]$PluginRoot)
    $DescriptorPath = Join-Path $PluginRoot 'DigimonVenomNXT.uplugin'
    $Repair = 'Install the corrected DigimonVenomNXT.uplugin before building. The editor module must be Type=Editor and LoadingPhase=Default so Unreal can discover DigimonVenomNXTImportCommandlet.'
    if (!(Test-Path -LiteralPath $DescriptorPath -PathType Leaf)) { throw "Plugin descriptor is missing: $DescriptorPath. $Repair" }
    try { $Descriptor = Get-Content -LiteralPath $DescriptorPath -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop }
    catch { throw "Plugin descriptor cannot be read: $DescriptorPath. $Repair" }
    if ($null -eq $Descriptor -or !$Descriptor.PSObject.Properties['Modules']) { throw "Plugin descriptor has no module declarations. $Repair" }
    $EditorModules = @($Descriptor.Modules | Where-Object { $null -ne $_ -and $_.PSObject.Properties['Name'] -and $_.Name -ceq 'DigimonVenomNXTEditor' })
    if ($EditorModules.Count -ne 1) { throw "Expected exactly one DigimonVenomNXTEditor module; found $($EditorModules.Count). $Repair" }
    $EditorModule = $EditorModules[0]
    if (!$EditorModule.PSObject.Properties['Type'] -or $EditorModule.Type -cne 'Editor') {
        throw "DigimonVenomNXTEditor is not declared as Type=Editor. EditorNoCommandlet and other module types are not supported for this import commandlet. $Repair"
    }
    if (!$EditorModule.PSObject.Properties['LoadingPhase'] -or $EditorModule.LoadingPhase -cne 'Default') {
        throw "DigimonVenomNXTEditor must use LoadingPhase=Default. PostEngineInit is too late for import commandlet class discovery, even after a successful editor build. $Repair"
    }
}

function Assert-DigimonCampaignSources {
    param([Parameter(Mandatory = $true)][string]$PluginRoot,
          [Parameter(Mandatory = $true)][string]$ProjectFolder, [switch]$SourceOnly)
    [void](Get-DigimonContentReceiptPath -ProjectFolder $ProjectFolder -PluginRoot $PluginRoot)
    $Resources = Join-Path $PluginRoot 'Resources'
    $RegistryPath = Join-Path $Resources 'DigimonMaps.json'
    $Registry = Get-Content -LiteralPath $RegistryPath -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
    if (!$Registry.PSObject.Properties['maps'] -or @($Registry.maps).Count -eq 0) { throw 'The installed Digimon map registry is empty.' }
    $ManifestPath = Join-Path $Resources 'GameData/import_manifest.json'
    $Manifest = Get-Content -LiteralPath $ManifestPath -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
    if (!$Manifest.PSObject.Properties['schemaVersion'] -or $Manifest.schemaVersion -ne 1) { throw 'Unsupported Digimon content import manifest schema.' }
    $ExpectedPackages = @{}
    $Seen = @{}
    foreach ($Row in $Registry.maps) {
        $Id = [int]$Row.mapId
        if ($Id -lt 1 -or $Seen.ContainsKey($Id)) { throw "Invalid or duplicate source map ID $Id in the installed registry." }
        $Seen[$Id] = $true
        foreach ($Kind in @('groundSource', 'collisionSource')) {
            if (!$Row.PSObject.Properties[$Kind]) { throw "Map $Id has no $Kind path." }
            $Source = Resolve-DigimonChildPath -Root $Resources -Relative ([string]$Row.PSObject.Properties[$Kind].Value)
            if (!(Test-Path -LiteralPath $Source -PathType Leaf) -or (Get-Item -LiteralPath $Source).Length -eq 0) { throw "Map $Id $Kind source is missing or empty." }
            $HashField = $Kind + 'Sha256'
            if (!$Row.PSObject.Properties[$HashField] -or $Row.PSObject.Properties[$HashField].Value -notmatch '^[0-9a-fA-F]{64}$') { throw "Map $Id $Kind has no valid registered SHA256." }
            if ((Get-FileHash -LiteralPath $Source -Algorithm SHA256).Hash -ine $Row.PSObject.Properties[$HashField].Value) {
                throw "Map $Id $Kind source differs from its registered hash."
            }
        }
        if (!$Row.PSObject.Properties['importedTexture']) { throw "Map $Id has no importedTexture package." }
        $Package = [string]$Row.importedTexture
        $ExpectedPackages[$Package] = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package
    }
    # Validate every manifest source before starting a potentially long editor/build job.
    foreach ($Group in @('textures', 'audio')) {
        if (!$Manifest.PSObject.Properties[$Group]) { throw "Import manifest is missing $Group." }
        foreach ($Entry in @($Manifest.PSObject.Properties[$Group].Value)) {
            $Source = Resolve-DigimonChildPath -Root $Resources -Relative ([string]$Entry.source)
            if (!(Test-Path -LiteralPath $Source -PathType Leaf) -or (Get-Item -LiteralPath $Source).Length -eq 0) { throw "Missing content source '$($Entry.source)'." }
            if (!$Entry.PSObject.Properties['sha1'] -or $Entry.sha1 -notmatch '^[0-9a-fA-F]{40}$' -or (Get-FileHash -LiteralPath $Source -Algorithm SHA1).Hash -ine $Entry.sha1) { throw "Content source hash differs for '$($Entry.source)'." }
        }
    }
    $ManifestPackages = @{}
    foreach ($Group in @('textures', 'sprites', 'animations', 'audio', 'partnerSets', 'tamerSets')) {
        if (!$Manifest.PSObject.Properties[$Group]) { throw "Import manifest is missing $Group." }
        foreach ($Entry in @($Manifest.PSObject.Properties[$Group].Value)) {
            $Package = [string]$Entry.asset
            if ($ManifestPackages.ContainsKey($Package)) { throw "Duplicate import destination '$Package'." }
            $ManifestPackages[$Package] = $true
            $ExpectedPackages[$Package] = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package
        }
    }
    foreach ($Package in @('/DigimonVenomNXT/Generated/Materials/MI_DVNXT_FieldSprite', '/DigimonVenomNXT/Generated/Maps/DA_PlayableMapRevision')) {
        $ExpectedPackages[$Package] = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package
    }
    foreach ($Level in @('MainMenu', 'PublicWorld')) {
        $Package = '/DigimonVenomNXT/Generated/Levels/' + $Level
        $ExpectedPackages[$Package] = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package -Map
    }
    if (!$SourceOnly) { Assert-DigimonContentImport -PluginRoot $PluginRoot -ProjectFolder $ProjectFolder -Registry $Registry -ExpectedPackages $ExpectedPackages }
    $Directories = @([IO.Path]::GetFullPath((Join-Path $PluginRoot 'Content/Generated')))
    $UI = Join-Path $PluginRoot 'Content/UI'
    if (Test-Path -LiteralPath $UI -PathType Container) { $Directories += [IO.Path]::GetFullPath($UI) }
    foreach ($Directory in $Directories) { if ($Directory.Contains('+')) { throw "UAT cook directories cannot contain '+': $Directory" } }
    return [pscustomobject]@{ MapCount = $Seen.Count; CookDirectories = $Directories; AssetRevision = 'digimon-venom-nxt-native-1'; ExpectedPackageCount = $ExpectedPackages.Count }
}

function Assert-DigimonContentImport {
    param([Parameter(Mandatory = $true)][string]$PluginRoot,
          [Parameter(Mandatory = $true)][string]$ProjectFolder,
          [Parameter(Mandatory = $true)]$Registry,
          [Parameter(Mandatory = $true)][hashtable]$ExpectedPackages)
    $Repair = 'For missing startup worlds/config only, run Build_Windows.bat -RepairStartup. If the receipt is absent, incomplete or stale, complete Build_Windows.bat -ImportContent; world repair alone cannot certify imported assets.'
    $ReceiptPath = Get-DigimonContentReceiptPath -ProjectFolder $ProjectFolder -PluginRoot $PluginRoot
    if (!(Test-Path -LiteralPath $ReceiptPath -PathType Leaf)) { throw "The completed content import receipt is missing. $Repair" }
    try { $Receipt = Get-Content -LiteralPath $ReceiptPath -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop }
    catch { throw "The content import receipt cannot be read. $Repair" }
    foreach ($Field in @('schema', 'revision', 'manifestSha1', 'registrySha1', 'mapCount', 'expectedPackageCount', 'packages')) {
        if (!$Receipt.PSObject.Properties[$Field]) { throw "Incomplete content import receipt ($Field missing). $Repair" }
    }
    if ($Receipt.schema -ne 1 -or $Receipt.revision -cne 'digimon-venom-nxt-native-1' -or $Receipt.mapCount -ne @($Registry.maps).Count) { throw "Content import receipt has a different revision or map count. $Repair" }
    foreach ($Check in @(@{ Field = 'registrySha1'; File = 'Resources/DigimonMaps.json' }, @{ Field = 'manifestSha1'; File = 'Resources/GameData/import_manifest.json' })) {
        $Hash = (Get-FileHash -LiteralPath (Join-Path $PluginRoot $Check.File) -Algorithm SHA1).Hash
        if ($Receipt.PSObject.Properties[$Check.Field].Value -ine $Hash) { throw "Content registry/manifest changed after import. $Repair" }
    }
    if ([int]$Receipt.expectedPackageCount -ne @($Receipt.packages).Count) { throw "Incomplete content import receipt package count. $Repair" }
    $SeenPackages = @{}
    foreach ($Asset in @($Receipt.packages)) {
        if ($null -eq $Asset -or !$Asset.PSObject.Properties['packagePath'] -or !$Asset.PSObject.Properties['sha1']) { throw "Malformed package in content import receipt. $Repair" }
        $Package = [string]$Asset.packagePath
        if ($SeenPackages.ContainsKey($Package)) { throw "Duplicate saved package '$Package'. $Repair" }
        $SeenPackages[$Package] = $true
        if ($ExpectedPackages.ContainsKey($Package)) { $File = $ExpectedPackages[$Package] }
        else {
            # Import-generated materials, revision data and supplemental sprites are also hashed.
            $File = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package
            if (!(Test-Path -LiteralPath $File -PathType Leaf)) { $File = Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package -Map }
        }
        if ($Asset.sha1 -notmatch '^[0-9a-fA-F]{40}$' -or !(Test-Path -LiteralPath $File -PathType Leaf) -or
            (Get-Item -LiteralPath $File).Length -eq 0 -or (Get-FileHash -LiteralPath $File -Algorithm SHA1).Hash -ine $Asset.sha1) {
            throw "Saved content '$Package' changed or is missing after import. $Repair"
        }
    }
    foreach ($Package in $ExpectedPackages.Keys) {
        if (!$SeenPackages.ContainsKey($Package)) { throw "Incomplete content import receipt: required package '$Package' is absent. $Repair" }
    }
}

function Assert-DigimonNoSharedHostSecret {
    param([string]$ProjectFolder, [string]$PluginRoot)
    foreach ($Root in @((Join-Path $ProjectFolder 'Config'), (Join-Path $PluginRoot 'Config'))) {
        if (!(Test-Path -LiteralPath $Root -PathType Container)) { continue }
        foreach ($File in @(Get-ChildItem -LiteralPath $Root -Filter '*.ini' -File -Recurse)) {
            foreach ($Line in [IO.File]::ReadAllLines($File.FullName)) {
                if ($Line -match '^\s*AdminHostPassword\s*=\s*(.*)$' -and ![string]::IsNullOrWhiteSpace($Matches[1].Trim('"'))) {
                    throw "A hosting credential is stored in distributable config '$($File.FullName)'. Clear AdminHostPassword there and set DIGIMONVENOMNXT_HOST_PASSWORD or server-local Saved/DigimonVenomNXT/Host.ini instead. The credential was not printed."
                }
            }
        }
    }
}

function Assert-DigimonEnginePlugins {
    param([Parameter(Mandatory = $true)][string]$EngineRoot)
    $PluginsRoot = Join-Path $EngineRoot 'Engine/Plugins'
    if (!(Test-Path -LiteralPath $PluginsRoot -PathType Container)) { throw "Engine plugins folder is missing: $PluginsRoot" }
    $Descriptors = @(Get-ChildItem -LiteralPath $PluginsRoot -Filter '*.uplugin' -File -Recurse -ErrorAction Stop)
    $Requirements = @(
        @{ Name = 'CommonUI'; Modules = @('CommonUI', 'CommonInput') },
        @{ Name = 'Paper2D'; Modules = @('Paper2D') },
        @{ Name = 'EnhancedInput'; Modules = @('EnhancedInput') }
    )
    foreach ($Requirement in $Requirements) {
        $Matches = @($Descriptors | Where-Object { $_.BaseName -ieq $Requirement.Name })
        if ($Matches.Count -ne 1) {
            throw "Expected one installed engine $($Requirement.Name).uplugin; found $($Matches.Count) in '$PluginsRoot'. Repair/verify this UE installation before rebuilding. No plugin descriptors were fabricated or copied into the package."
        }
        $Descriptor = Get-Content -LiteralPath $Matches[0].FullName -Raw -Encoding UTF8 -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
        if (!$Descriptor.PSObject.Properties['Modules']) { throw "Engine plugin has no module declarations: $($Matches[0].FullName)" }
        $Modules = @($Descriptor.Modules | ForEach-Object { $_.Name })
        foreach ($Module in $Requirement.Modules) {
            if ($Modules -notcontains $Module) { throw "Engine plugin '$($Matches[0].FullName)' is missing its required $Module module declaration. Repair/verify this UE installation before rebuilding." }
        }
    }
}

function Resolve-DigimonReceiptPath {
    param([Parameter(Mandatory = $true)][string]$Path,
          [Parameter(Mandatory = $true)][string]$ProjectFolder,
          [Parameter(Mandatory = $true)][string]$EngineRoot)
    $Resolved = $Path.Replace('$(ProjectDir)', $ProjectFolder).Replace('$(EngineDir)', (Join-Path $EngineRoot 'Engine'))
    if ($Resolved.Contains('$(')) { throw "Unresolved variable in Unreal receipt path: $Path" }
    if (![IO.Path]::IsPathRooted($Resolved)) { $Resolved = Join-Path $ProjectFolder $Resolved }
    return [IO.Path]::GetFullPath($Resolved)
}

function Assert-DigimonGameBuild {
    param([Parameter(Mandatory = $true)][string]$ProjectFolder,
          [Parameter(Mandatory = $true)][string]$EngineRoot,
          [Parameter(Mandatory = $true)][string]$GameTarget,
          [Parameter(Mandatory = $true)][string]$Configuration,
          [Parameter(Mandatory = $true)][datetime]$BuildStartedUtc)
    $Binaries = Join-Path $ProjectFolder 'Binaries/Win64'
    if (!(Test-Path -LiteralPath $Binaries -PathType Container)) {
        throw "The native build produced no project Binaries/Win64 folder. Packaging has been stopped."
    }
    $MatchingReceipts = @()
    foreach ($File in @(Get-ChildItem -LiteralPath $Binaries -Filter '*.target' -File)) {
        try { $Receipt = Get-Content -LiteralPath $File.FullName -Raw -Encoding UTF8 | ConvertFrom-Json }
        catch { continue }
        if ($Receipt.PSObject.Properties['TargetName'] -and $Receipt.PSObject.Properties['Platform'] -and $Receipt.PSObject.Properties['Configuration'] -and
            $Receipt.TargetName -ceq $GameTarget -and $Receipt.Platform -ceq 'Win64' -and $Receipt.Configuration -ceq $Configuration) {
            $MatchingReceipts += [pscustomobject]@{ File = $File; Receipt = $Receipt }
        }
    }
    if ($MatchingReceipts.Count -ne 1) {
        throw "Expected one $GameTarget Win64 $Configuration game receipt; found $($MatchingReceipts.Count). Packaging has been stopped."
    }
    $Match = $MatchingReceipts[0]
    if ($Match.File.LastWriteTimeUtc -lt $BuildStartedUtc.AddSeconds(-2)) {
        throw "The game receipt predates this clean C++ build: $($Match.File.FullName). Packaging has been stopped."
    }
    if (!$Match.Receipt.PSObject.Properties['BuildProducts']) { throw 'The game receipt has no build products.' }
    $Products = @($Match.Receipt.BuildProducts | Where-Object { $_.Type -eq 'Executable' })
    $Executables = @()
    $ProjectPrefix = [IO.Path]::GetFullPath($ProjectFolder).TrimEnd([char[]]@([IO.Path]::DirectorySeparatorChar, [IO.Path]::AltDirectorySeparatorChar)) + [IO.Path]::DirectorySeparatorChar
    foreach ($Product in $Products) {
        $Executable = Resolve-DigimonReceiptPath -Path $Product.Path -ProjectFolder $ProjectFolder -EngineRoot $EngineRoot
        if ([IO.Path]::GetExtension($Executable) -ine '.exe') { continue }
        if (!$Executable.StartsWith($ProjectPrefix, [StringComparison]::OrdinalIgnoreCase)) {
            throw "The game receipt points outside this project: $Executable. Packaging has been stopped."
        }
        if (!(Test-Path -LiteralPath $Executable -PathType Leaf)) { throw "Missing native game executable: $Executable" }
        $ExecutableInfo = Get-Item -LiteralPath $Executable
        if ($ExecutableInfo.Length -eq 0 -or $ExecutableInfo.LastWriteTimeUtc -lt $BuildStartedUtc.AddSeconds(-2)) {
            throw "The game executable is empty or predates this clean C++ build: $Executable"
        }
        $Executables += $Executable
    }
    if ($Executables.Count -eq 0) { throw 'The game receipt contains no project Windows executable.' }

    # These unique staged dependencies are added by DigimonVenomNXTRuntime.Build.cs.
    # Their presence proves the plugin participated in this target's build graph.
    if (!$Match.Receipt.PSObject.Properties['RuntimeDependencies']) { throw 'The game receipt contains no runtime dependencies for DigimonVenomNXT.' }
    foreach ($Resource in @('DigimonSpecies.json', 'DigimonMaps.json', 'DigimonCombat.json')) {
        $Found = @($Match.Receipt.RuntimeDependencies | Where-Object { ($_.Path -replace '\\', '/') -like "*/Resources/$Resource" })
        if ($Found.Count -eq 0) {
            throw "DigimonVenomNXTRuntime is missing from the game build receipt ($Resource not staged). Packaging has been stopped."
        }
        foreach ($Dependency in $Found) {
            $DependencyPath = Resolve-DigimonReceiptPath -Path $Dependency.Path -ProjectFolder $ProjectFolder -EngineRoot $EngineRoot
            if (!(Test-Path -LiteralPath $DependencyPath -PathType Leaf)) { throw "Missing Digimon runtime resource: $DependencyPath" }
        }
    }
    return [pscustomobject]@{ Receipt = $Match.File.FullName; Executables = $Executables }
}

function Assert-DigimonPackagedGame {
    param([Parameter(Mandatory = $true)][string]$ArchiveDirectory,
          [Parameter(Mandatory = $true)][string[]]$Executables)
    if (!(Test-Path -LiteralPath $ArchiveDirectory -PathType Container)) { throw 'Unreal returned success but the new archive folder is missing.' }
    $ArchivePrefix = (Get-Item -LiteralPath $ArchiveDirectory).FullName.TrimEnd([char[]]'\/') + [IO.Path]::DirectorySeparatorChar
    $Verified = @()
    foreach ($Executable in $Executables) {
        $Leaf = Split-Path $Executable -Leaf
        $Candidates = @(Get-ChildItem -LiteralPath $ArchiveDirectory -Filter $Leaf -File -Recurse | Where-Object {
            $RelativePath = $_.FullName.Substring($ArchivePrefix.Length)
            $RelativePath -match '[\\/]Binaries[\\/]Win64[\\/]' -and $RelativePath -notmatch '(^|[\\/])Engine[\\/]'
        })
        $ExpectedHash = (Get-FileHash -LiteralPath $Executable -Algorithm SHA256).Hash
        $Matching = @($Candidates | Where-Object { (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash -eq $ExpectedHash })
        if ($Matching.Count -eq 0) { throw "The new archive does not contain the verified native game binary '$Leaf'." }
        $Verified += $Matching[0].FullName
    }
    return $Verified
}
