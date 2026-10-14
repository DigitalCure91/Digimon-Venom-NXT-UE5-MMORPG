@echo off
setlocal EnableExtensions DisableDelayedExpansion
title Digimon Venom NXT - Build Plugin Only
echo Digimon Venom NXT - Build Plugin Only
echo To package the playable game, use Build_Windows.cmd instead.
echo.
powershell.exe -NoLogo -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "%~dp0Build_Launcher.ps1" Plugin %*
set "DigimonBuildExitCode=%ERRORLEVEL%"
echo.
if "%DigimonBuildExitCode%"=="0" (
    echo Plugin build finished successfully. Read the output folder above.
) else (
    echo PLUGIN BUILD STOPPED - exit code %DigimonBuildExitCode%. Read the error above.
    echo If no log was created, copy or photograph this window before closing it.
)
if not "%DIGIMONVENOMNXT_NO_PAUSE%"=="1" pause
exit /b %DigimonBuildExitCode%
