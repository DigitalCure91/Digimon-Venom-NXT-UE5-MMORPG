@echo off
setlocal EnableExtensions DisableDelayedExpansion
call "%~dp0Build_Windows.bat" %*
exit /b %ERRORLEVEL%
