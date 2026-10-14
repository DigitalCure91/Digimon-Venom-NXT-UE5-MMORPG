# Opens the packaged game's normal login/main menu using this machine's host
# credential. The password is passed only in the child process environment.
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)][string]$ProjectFolder,
    [Parameter(Mandatory = $true)][string]$GameExecutable
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 2.0
try {
    if (!(Test-Path -LiteralPath $GameExecutable -PathType Leaf)) {
        throw 'The packaged game was moved or removed. Build again to refresh PlayPackagedHost.cmd.'
    }
    . (Join-Path $PSScriptRoot 'HostCredentials.ps1')
    $HostPassword = [Environment]::GetEnvironmentVariable('DIGIMONVENOMNXT_HOST_PASSWORD', 'Process')
    if ([string]::IsNullOrEmpty($HostPassword)) {
        $HostPassword = Get-DigimonLocalHostPassword -ProjectFolder $ProjectFolder
    }
    if ([string]::IsNullOrEmpty($HostPassword)) {
        throw 'No local hosting password is configured. Set it in Digimon Venom NXT Project Settings and run the build, or configure Saved/DigimonVenomNXT/Host.ini. To join another host, launch the packaged game normally.'
    }
    $LaunchInfo = New-Object System.Diagnostics.ProcessStartInfo
    $LaunchInfo.FileName = (Resolve-Path -LiteralPath $GameExecutable).ProviderPath
    $LaunchInfo.WorkingDirectory = Split-Path $LaunchInfo.FileName -Parent
    $LaunchInfo.UseShellExecute = $false
    $LaunchInfo.EnvironmentVariables['DIGIMONVENOMNXT_HOST_PASSWORD'] = $HostPassword
    $GameProcess = [Diagnostics.Process]::Start($LaunchInfo)
    if ($null -eq $GameProcess) { throw 'The packaged game could not be started.' }
    $GameProcess.Dispose()
    Write-Host 'Opened the game. Log in, choose Host, and enter your existing hosting password.'
    exit 0
}
catch {
    Write-Host "Local host launch failed: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}
