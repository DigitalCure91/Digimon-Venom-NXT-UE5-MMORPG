# Shared console/logging boundary for the .cmd/.bat entry points.
# Intentionally no param block: unknown parameters must reach the child script,
# where their binding errors are captured in this launcher's transcript.
# The first argument is the fixed build kind supplied by the batch launcher.
Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
$BuildExitCode = 1
$BuildLogPath = ''
$TranscriptStarted = $false

try {
    if ($args.Count -lt 1 -or @('Windows', 'Plugin') -notcontains [string]$args[0]) {
        throw 'Use Build_Windows.cmd for the playable game or Build_UE58.bat for the plugin.'
    }
    $BuildKind = [string]$args[0]
    $BuildLogName = '{0}-{1}-{2}.log' -f $BuildKind, (Get-Date -Format 'yyyyMMdd-HHmmss'), ([Guid]::NewGuid().ToString('N').Substring(0, 8))
    $LogDirectories = @(
        (Join-Path $PSScriptRoot 'Logs'),
        (Join-Path ([IO.Path]::GetTempPath()) 'DigimonVenomNXT-BuildLogs')
    )
    foreach ($LogDirectory in $LogDirectories) {
        try {
            New-Item -ItemType Directory -Path $LogDirectory -Force -ErrorAction Stop | Out-Null
            $CandidateLog = Join-Path $LogDirectory $BuildLogName
            Start-Transcript -Path $CandidateLog -ErrorAction Stop | Out-Null
            $BuildLogPath = $CandidateLog
            $TranscriptStarted = $true
            break
        }
        catch {
            # The project/plugin can be read-only; try the per-user temp folder.
        }
    }
    if ($TranscriptStarted) {
        Write-Host "Build log: $BuildLogPath" -ForegroundColor Cyan
    }
    else {
        Write-Warning 'A build log could not be opened. Keep this window open and copy any error shown here.'
    }

    $BuildScriptName = if ($BuildKind -eq 'Windows') { 'Build_Windows.ps1' } else { 'Build_UE58.ps1' }
    $BuildScript = Join-Path $PSScriptRoot $BuildScriptName
    if (!(Test-Path -LiteralPath $BuildScript -PathType Leaf)) {
        throw "Build script is missing: $BuildScript. Extract the update into the existing plugin folder and keep all Tools files together."
    }
    $PowerShell = Join-Path $PSHOME 'powershell.exe'
    if (!(Test-Path -LiteralPath $PowerShell -PathType Leaf)) {
        throw "Windows PowerShell was not found at '$PowerShell'. Run the .cmd/.bat launcher on Windows."
    }
    $NativeArguments = @('-NoLogo', '-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-File', $BuildScript)
    if ($args.Count -eq 1 -and $BuildKind -eq 'Windows') {
        Write-Host 'Default build: compile, import/resume all content, validate MainMenu/PublicWorld, and package Windows.'
        $NativeArguments += '-ImportContent'
    }
    elseif ($args.Count -eq 1) {
        throw 'Plugin-only compilation needs an engine path. Example: Build_UE58.bat -EngineRoot "C:\Program Files\Epic Games\UE_5.8". For the playable game, run Build_Windows.cmd.'
    }
    else {
        for ($ArgumentIndex = 1; $ArgumentIndex -lt $args.Count; $ArgumentIndex++) {
            $NativeArguments += [string]$args[$ArgumentIndex]
        }
    }

    # A separate process lets the log capture syntax and parameter-binding errors
    # in the build script, as well as all native compiler/commandlet/cook output.
    # Windows PowerShell wraps native stderr in error records: those must not
    # terminate the stream before we can preserve the process exit code.
    $ErrorActionPreference = 'Continue'
    & $PowerShell @NativeArguments 2>&1 | ForEach-Object { Write-Host $_ }
    $BuildExitCode = $LASTEXITCODE
    $ErrorActionPreference = 'Stop'
    if ($null -eq $BuildExitCode) { $BuildExitCode = 1 }

    if ($BuildExitCode -eq 0) {
        Write-Host 'Build command completed successfully. See the build result above.' -ForegroundColor Green
    }
    else {
        Write-Host "BUILD STOPPED (exit code $BuildExitCode). The error above explains which stage failed." -ForegroundColor Red
    }
}
catch {
    $BuildExitCode = 1
    Write-Host "Build launcher failed: $($_.Exception.Message)" -ForegroundColor Red
}
finally {
    if ($TranscriptStarted) {
        Write-Host "Build log: $BuildLogPath" -ForegroundColor Cyan
        try { Stop-Transcript -ErrorAction Stop | Out-Null } catch { }
    }
}
exit $BuildExitCode
