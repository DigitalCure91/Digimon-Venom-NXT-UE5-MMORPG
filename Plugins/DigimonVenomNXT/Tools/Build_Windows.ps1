# Run Build_Windows.cmd after saving the project and closing Unreal Editor.
# Optional: Build_Windows.cmd -Project "D:\Game\DigimonVenomNXT.uproject" -EngineRoot "D:\UE_5.8"
# Creates native host targets when absent, builds Editor + Game explicitly, then packages.
# -ImportContent resumes verified packages; add -ForceReimport to rebuild every asset.
# -RepairStartup repairs missing worlds/config while preserving a verified asset import.
# -DryRun validates paths and prints the build sequence without changing files.
[CmdletBinding()]
param(
    [string]$Project = '',
    [string]$EngineRoot = '',
    [ValidateSet('Development', 'Shipping')]
    [string]$Configuration = 'Development',
    [switch]$ImportContent,
    [switch]$ForceReimport,
    [switch]$RepairStartup,
    [switch]$DryRun
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 2.0

try {
    if ($ImportContent -and $RepairStartup) { throw 'Choose either -ImportContent (full content setup) or -RepairStartup (existing content startup repair), not both.' }
    if ($ForceReimport -and !$ImportContent) { throw '-ForceReimport requires -ImportContent.' }
    if ([string]::IsNullOrWhiteSpace($Project)) {
        $Folder = Get-Item -LiteralPath (Split-Path $PSScriptRoot -Parent)
        $ProjectFolder = $null
        while ($null -ne $Folder.Parent) {
            if ($Folder.Name -ieq 'Plugins') {
                $ProjectFolder = $Folder.Parent.FullName
                break
            }
            $Folder = $Folder.Parent
        }
        if ($null -eq $ProjectFolder) {
            throw 'Install DigimonVenomNXT inside your project Plugins folder, or pass -Project with the full .uproject path.'
        }
        $Projects = @(Get-ChildItem -LiteralPath $ProjectFolder -Filter '*.uproject' -File)
        if ($Projects.Count -ne 1) {
            throw "Expected one .uproject in '$ProjectFolder'; found $($Projects.Count). Pass -Project with the intended .uproject path."
        }
        $Project = $Projects[0].FullName
    }
    if (!(Test-Path -LiteralPath $Project -PathType Leaf) -or [IO.Path]::GetExtension($Project) -ine '.uproject') {
        throw "Project file not found or not a .uproject: $Project"
    }
    $Project = (Resolve-Path -LiteralPath $Project).ProviderPath
    $ProjectFolder = Split-Path $Project -Parent
    $Descriptor = Get-Content -LiteralPath $Project -Raw -Encoding UTF8 | ConvertFrom-Json

    if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
        $Association = ''
        if ($Descriptor.PSObject.Properties['EngineAssociation']) {
            $Association = [string]$Descriptor.EngineAssociation
        }
        if (![string]::IsNullOrWhiteSpace($Association)) {
            $SourceBuilds = Get-ItemProperty -LiteralPath 'HKCU:\Software\Epic Games\Unreal Engine\Builds' -ErrorAction SilentlyContinue
            if ($null -ne $SourceBuilds -and $SourceBuilds.PSObject.Properties[$Association]) {
                $EngineRoot = [string]$SourceBuilds.PSObject.Properties[$Association].Value
            }
            if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
                foreach ($RegistryRoot in @('HKLM:\SOFTWARE\EpicGames\Unreal Engine', 'HKLM:\SOFTWARE\WOW6432Node\EpicGames\Unreal Engine')) {
                    $Install = Get-ItemProperty -LiteralPath (Join-Path $RegistryRoot $Association) -ErrorAction SilentlyContinue
                    if ($null -ne $Install -and $Install.PSObject.Properties['InstalledDirectory']) {
                        $EngineRoot = [string]$Install.InstalledDirectory
                        break
                    }
                }
            }
        }
        if ([string]::IsNullOrWhiteSpace($EngineRoot) -and ($Association -eq '' -or $Association -eq '5.8')) {
            if (![string]::IsNullOrWhiteSpace($env:ProgramFiles)) {
                $ConventionalEngine = Join-Path $env:ProgramFiles 'Epic Games\UE_5.8'
                if (Test-Path -LiteralPath $ConventionalEngine -PathType Container) {
                    $EngineRoot = $ConventionalEngine
                }
            }
        }
        if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
            throw "Could not locate the engine associated with '$Association'. Run Build_Windows.cmd -EngineRoot with your UE 5.8 installation folder."
        }
    }
    $RunUAT = Join-Path $EngineRoot 'Engine\Build\BatchFiles\RunUAT.bat'
    if (!(Test-Path -LiteralPath $RunUAT -PathType Leaf)) {
        throw "RunUAT.bat was not found at '$RunUAT'. Pass -EngineRoot with the Unreal installation root, for example 'C:\Program Files\Epic Games\UE_5.8'."
    }
    $RunUAT = (Resolve-Path -LiteralPath $RunUAT).ProviderPath

    $EditorCmd = Join-Path $EngineRoot 'Engine\Binaries\Win64\UnrealEditor-Cmd.exe'
    if (!(Test-Path -LiteralPath $EditorCmd -PathType Leaf)) { throw "Startup-world validation requires '$EditorCmd'." }
    $BuildTool = Join-Path $EngineRoot 'Engine\Build\BatchFiles\Build.bat'
    $CleanTool = Join-Path $EngineRoot 'Engine\Build\BatchFiles\Clean.bat'
    foreach ($Tool in @($BuildTool, $CleanTool)) {
        if (!(Test-Path -LiteralPath $Tool -PathType Leaf)) { throw "Required Unreal build tool was not found: $Tool" }
    }
    $LocalPlugin = Join-Path $ProjectFolder 'Plugins\DigimonVenomNXT\DigimonVenomNXT.uplugin'
    if (!(Test-Path -LiteralPath $LocalPlugin -PathType Leaf)) {
        throw 'Install this update as <project>/Plugins/DigimonVenomNXT before running the build.'
    }
    $ExpectedTools = [IO.Path]::GetFullPath((Join-Path $ProjectFolder 'Plugins\DigimonVenomNXT\Tools')).TrimEnd([char[]]'\/')
    if ([IO.Path]::GetFullPath($PSScriptRoot).TrimEnd([char[]]'\/') -ine $ExpectedTools) {
        throw "Run the installed script in '$ExpectedTools', so the plugin being built is the plugin you just updated."
    }
    if (!$DryRun -and @(Get-Process -Name @('UnrealEditor', 'UnrealEditor-Cmd') -ErrorAction SilentlyContinue).Count -gt 0) {
        throw 'Save your work and close Unreal Editor before running this build. An open editor locks the DLLs being rebuilt.'
    }
    . (Join-Path $PSScriptRoot 'NativeHost.ps1')
    . (Join-Path $PSScriptRoot 'NativeBuildChecks.ps1')
    . (Join-Path $PSScriptRoot 'PackagedPlugins.ps1')
    . (Join-Path $PSScriptRoot 'HostCredentials.ps1')
    Write-Host 'Checking Unreal version and required engine plugins...'
    Assert-DigimonEngineVersion -EngineRoot $EngineRoot
    Assert-DigimonEnginePlugins -EngineRoot $EngineRoot
    Assert-DigimonImportCommandlet -PluginRoot (Split-Path $LocalPlugin -Parent)
    Write-Host 'Preparing local hosting settings for packaging...'
    $HostPreparation = Move-DigimonHostCredential -ProjectFolder $ProjectFolder -PluginRoot (Split-Path $LocalPlugin -Parent) -DryRun:$DryRun
    if (!$DryRun -or !$HostPreparation.Planned) {
        Assert-DigimonNoSharedHostSecret -ProjectFolder $ProjectFolder -PluginRoot (Split-Path $LocalPlugin -Parent)
    }
    Write-Host 'Checking all registered source files and hashes. This can take several minutes...'
    $CampaignContent = Assert-DigimonCampaignSources -PluginRoot (Split-Path $LocalPlugin -Parent) -ProjectFolder $ProjectFolder -SourceOnly:($ImportContent -or $RepairStartup)
    Write-Host 'Preparing native project Game and Editor targets...'
    $NativeHost = Ensure-DigimonNativeHost -Project $Project -DryRun:$DryRun

    function Invoke-DigimonBuildStep {
        param([string]$Label, [string]$Tool, [string[]]$ToolArguments)
        Write-Host ''
        Write-Host $Label -ForegroundColor Cyan
        Write-Host ('"{0}" {1}' -f $Tool, (($ToolArguments | ForEach-Object { '"{0}"' -f $_ }) -join ' '))
        if ($DryRun) { return }
        & $Tool @ToolArguments
        if ($LASTEXITCODE -ne 0) { throw "$Label failed (exit code $LASTEXITCODE). Packaging stopped. Read this stage's error above." }
    }

    # A named project Game target is required; a content-only cook or a successful
    # Turnkey SDK check is not accepted as a native game build.
    $EditorArguments = @($NativeHost.EditorTarget, 'Win64', 'Development', "-Project=$Project", '-WaitMutex', '-NoHotReloadFromIDE')
    $GameArguments = @($NativeHost.GameTarget, 'Win64', $Configuration, "-Project=$Project", '-WaitMutex', '-NoHotReloadFromIDE')
    $BuildName = 'Windows-{0}-{1}-{2}' -f $Configuration, (Get-Date -Format 'yyyyMMdd-HHmmss'), ([Guid]::NewGuid().ToString('N').Substring(0, 8))
    $ArchiveDirectory = Join-Path (Join-Path $ProjectFolder 'Builds') $BuildName
    $UatArguments = @(
        'BuildCookRun',
        "-project=$Project",
        "-target=$($NativeHost.GameTarget)",
        '-noP4',
        '-utf8output',
        '-build',
        '-cook',
        '-map=/DigimonVenomNXT/Generated/Levels/MainMenu+/DigimonVenomNXT/Generated/Levels/PublicWorld',
        ('-CookDir=' + ($CampaignContent.CookDirectories -join '+')),
        '-stage',
        '-pak',
        '-iostore',
        '-package',
        '-archive',
        '-platform=Win64',
        "-clientconfig=$Configuration",
        '-prereqs',
        "-archivedirectory=$ArchiveDirectory"
    )
    Write-Host "Project: $Project"
    Write-Host "Native Game target: $($NativeHost.GameTarget)"
    Write-Host "Native Editor target: $($NativeHost.EditorTarget)"
    Write-Host 'Required project plugins: DigimonVenomNXT, CommonUI, Paper2D, EnhancedInput (Win64 Game + Editor).'
    Write-Host "Digimon map registry: $($CampaignContent.MapCount) maps; import revision $($CampaignContent.AssetRevision)."
    if ($ImportContent) { Write-Host "Content import will generate and verify $($CampaignContent.ExpectedPackageCount) required asset packages before the game build." }
    Write-Host ('Explicit additional cook directories: ' + ($CampaignContent.CookDirectories -join ', '))
    Write-Host "New packaged build: $ArchiveDirectory"
    Invoke-DigimonBuildStep -Label '1/5 Clean native Editor target' -Tool $CleanTool -ToolArguments $EditorArguments
    Invoke-DigimonBuildStep -Label '2/5 Compile native Editor target' -Tool $BuildTool -ToolArguments $EditorArguments
    if ($ImportContent) {
        $ImportArguments = @($Project, '-run=DigimonVenomNXTImport', '-unattended', '-nop4', '-nosplash', '-NullRHI', '-utf8output', '-stdout', '-FullStdOutLogOutput')
        if (!$ForceReimport) { $ImportArguments += '-NoReplace' }
        Invoke-DigimonBuildStep -Label 'Import all registered Digimon content and save generated levels' -Tool $EditorCmd -ToolArguments $ImportArguments
        if (!$DryRun) {
            $CampaignContent = Assert-DigimonCampaignSources -PluginRoot (Split-Path $LocalPlugin -Parent) -ProjectFolder $ProjectFolder
            Write-Host 'Generated content and import hashes verified.' -ForegroundColor Green
        }
    }
    if ($RepairStartup) {
        $RepairArguments = @($Project, '-run=DigimonVenomNXTImport', '-RepairStartup', '-unattended', '-nop4', '-nosplash', '-NullRHI', '-utf8output', '-stdout', '-FullStdOutLogOutput')
        Invoke-DigimonBuildStep -Label 'Repair missing startup worlds and project startup defaults' -Tool $EditorCmd -ToolArguments $RepairArguments
        if (!$DryRun) {
            $CampaignContent = Assert-DigimonCampaignSources -PluginRoot (Split-Path $LocalPlugin -Parent) -ProjectFolder $ProjectFolder
            Write-Host 'Startup repair and complete imported-content receipt verified.' -ForegroundColor Green
        }
    }
    # Hashes prove saved bytes; the editor validates actual UWorld objects, map
    # zones, game modes and effective project settings before we cook anything.
    $ValidationArguments = @($Project, '-run=DigimonVenomNXTImport', '-ValidateStartup', '-unattended', '-nop4', '-nosplash', '-NullRHI', '-utf8output', '-stdout', '-FullStdOutLogOutput')
    Invoke-DigimonBuildStep -Label 'Validate saved startup worlds and effective game configuration' -Tool $EditorCmd -ToolArguments $ValidationArguments
    Invoke-DigimonBuildStep -Label '3/5 Clean native Game target' -Tool $CleanTool -ToolArguments $GameArguments
    $GameBuildStartedUtc = [DateTime]::UtcNow
    Invoke-DigimonBuildStep -Label '4/5 Compile native Game target (C++ and link)' -Tool $BuildTool -ToolArguments $GameArguments
    if (!$DryRun) {
        $BuiltGame = Assert-DigimonGameBuild -ProjectFolder $ProjectFolder -EngineRoot $EngineRoot -GameTarget $NativeHost.GameTarget -Configuration $Configuration -BuildStartedUtc $GameBuildStartedUtc
        Write-Host "Verified native game receipt: $($BuiltGame.Receipt)" -ForegroundColor Green
        Write-Host 'Digimon runtime resources are present in the game build graph.'
        # Detect edits or an interrupted repair while the native build ran.
        $CampaignContent = Assert-DigimonCampaignSources -PluginRoot (Split-Path $LocalPlugin -Parent) -ProjectFolder $ProjectFolder
    }
    Invoke-DigimonBuildStep -Label '5/5 Cook and package the verified Game target' -Tool $RunUAT -ToolArguments $UatArguments
    if ($DryRun) {
        Write-Host 'Dry run only: no files were changed and Unreal was not started.'
        exit 0
    }
    $PackagedExecutables = @(Assert-DigimonPackagedGame -ArchiveDirectory $ArchiveDirectory -Executables $BuiltGame.Executables)
    $ManifestArguments = @{ ArchiveDirectory = $ArchiveDirectory; EngineRoot = $EngineRoot; Configuration = $Configuration }
    $ProjectName = [IO.Path]::GetFileNameWithoutExtension($Project)
    $CookKeys = Join-Path $ProjectFolder ("Saved/Cooked/Windows/$ProjectName/Metadata/Crypto.json")
    if (Test-Path -LiteralPath $CookKeys -PathType Leaf) { $ManifestArguments.CryptoKeys = $CookKeys }
    $PluginCheck = Assert-DigimonPluginManifest @ManifestArguments
    # A host-only convenience launcher stays outside the distributed archive.
    # It reads the project-local settings at launch time; no secret is embedded.
    $HostLauncher = Join-Path $ProjectFolder 'Saved/DigimonVenomNXT/PlayPackagedHost.cmd'
    $HostScript = Join-Path $PSScriptRoot 'Start_LocalHost.ps1'
    $HostCommand = 'powershell.exe -NoLogo -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "{0}" -ProjectFolder "{1}" -GameExecutable "{2}"' -f $HostScript.Replace('%', '%%'), $ProjectFolder.Replace('%', '%%'), $PackagedExecutables[0].Replace('%', '%%')
    $HostLauncherText = "@echo off`r`nsetlocal EnableExtensions DisableDelayedExpansion`r`n$HostCommand`r`nset ""DigimonHostExitCode=%ERRORLEVEL%""`r`nif not ""%DigimonHostExitCode%""==""0"" pause`r`nexit /b %DigimonHostExitCode%`r`n"
    [void][IO.Directory]::CreateDirectory((Split-Path $HostLauncher -Parent))
    [IO.File]::WriteAllText($HostLauncher, $HostLauncherText, [Text.Encoding]::Default)
    Write-Host "Windows packaging completed: $ArchiveDirectory" -ForegroundColor Green
    Write-Host 'Verified that the archived game binary matches this native build.'
    Write-Host ('Verified packaged plugin dependencies: ' + ($PluginCheck.Plugins -join ', '))
    foreach ($Executable in $PackagedExecutables) { Write-Host "Game binary: $Executable" }
    Write-Host "Play with this machine's hosting password: $HostLauncher" -ForegroundColor Cyan
    Write-Host 'Launch the game from this NEW archive folder. Build verification is not a Windows launch test.'
    exit 0
}
catch {
    Write-Host "Digimon Windows packaging failed: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}
