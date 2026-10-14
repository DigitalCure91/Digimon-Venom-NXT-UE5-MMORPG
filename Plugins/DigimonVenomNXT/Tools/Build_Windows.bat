@echo off
setlocal EnableExtensions DisableDelayedExpansion
title Digimon Venom NXT - Build Windows Game
echo Digimon Venom NXT - Build Windows Game
echo This window stays open when the build finishes or stops with an error.
echo.
powershell.exe -NoLogo -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "%~dp0Build_Launcher.ps1" Windows %*
set "DigimonBuildExitCode=%ERRORLEVEL%"
echo.
if "%DigimonBuildExitCode%"=="0" (
    echo Build command finished successfully. Read the result and output folder above.
) else (
    echo BUILD STOPPED - exit code %DigimonBuildExitCode%. Read the error above.
    echo If no log was created, copy or photograph this window before closing it.
)
if not "%DIGIMONVENOMNXT_NO_PAUSE%"=="1" pause
exit /b %DigimonBuildExitCode%
