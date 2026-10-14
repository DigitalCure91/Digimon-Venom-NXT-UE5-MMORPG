#!/usr/bin/env python3
"""Guard the Windows packaging/startup boundary and run its PowerShell fixtures when available.

Text-contract checks are not a PowerShell interpreter or an Unreal world loader.
The behavioral receipt fixtures live in Test_NativeBuild.ps1; the editor commandlet
performs actual world/configuration validation on the target Unreal installation.
"""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "Tools"
EDITOR = ROOT / "Source/DigimonVenomNXTEditor/Private"


def function(script: str, name: str) -> str:
    start = script.index("function " + name + " {")
    end = re.search(r"(?m)^function ", script[start + 1:])
    return script[start:start + 1 + end.start()] if end else script[start:]


def assert_receipt_contract(check: unittest.TestCase, helpers: str) -> None:
    resolver = function(helpers, "Get-DigimonContentReceiptPath")
    check.assertIn("return Join-Path $ProjectFolder 'Intermediate/DigimonVenomNXT/ContentImportReceipt.json'", resolver)
    check.assertIn("$Installed -ine $Expected", resolver)
    receipt = function(helpers, "Assert-DigimonContentImport")
    check.assertIn("Get-DigimonContentReceiptPath -ProjectFolder $ProjectFolder -PluginRoot $PluginRoot", receipt)
    check.assertNotIn("Join-Path $PluginRoot 'Intermediate", receipt)


def assert_validation_before_game(check: unittest.TestCase, script: str) -> None:
    editor = script.index("Invoke-DigimonBuildStep -Label '2/5 Compile native Editor target'")
    validation_args = script.index("'-ValidateStartup'")
    validation = script.index("Invoke-DigimonBuildStep -Label 'Validate saved startup worlds and effective game configuration'")
    game = script.index("Invoke-DigimonBuildStep -Label '3/5 Clean native Game target'")
    cook = script.index("Invoke-DigimonBuildStep -Label '5/5 Cook and package the verified Game target'")
    check.assertTrue(editor < validation_args < validation < game < cook)
    check.assertRegex(script, r"(?m)^    Invoke-DigimonBuildStep -Label 'Validate saved startup worlds and effective game configuration' -Tool \$EditorCmd -ToolArguments \$ValidationArguments$")
    invoke = function(script, "Invoke-DigimonBuildStep")
    check.assertIn("if ($LASTEXITCODE -ne 0) { throw", invoke)


class WindowsBuildBoundary(unittest.TestCase):
    def test_launchers_retain_errors_and_preserve_the_process_exit_code(self):
        cmd = (TOOLS / 'Build_Windows.cmd').read_text()
        self.assertIn('call "%~dp0Build_Windows.bat" %*', cmd)
        self.assertNotRegex(cmd, r'(?im)^pause\b')
        for filename, kind in [('Build_Windows.bat', 'Windows'), ('Build_UE58.bat', 'Plugin')]:
            with self.subTest(filename=filename):
                script = (TOOLS / filename).read_text()
                self.assertIn('DisableDelayedExpansion', script)
                call = script.index('Build_Launcher.ps1" ' + kind + ' %*')
                capture = script.index('set "DigimonBuildExitCode=%ERRORLEVEL%"')
                pause = script.index('if not "%DIGIMONVENOMNXT_NO_PAUSE%"=="1" pause')
                result = script.index('exit /b %DigimonBuildExitCode%')
                self.assertTrue(call < capture < pause < result)
                self.assertNotIn('-Command', script)

    def test_outer_launcher_logs_before_child_binding_and_defaults_to_full_import(self):
        script = (TOOLS / 'Build_Launcher.ps1').read_text()
        self.assertNotRegex(script, r'(?im)^\s*(param\s*\(|\[CmdletBinding)')
        self.assertLess(script.index('Start-Transcript -Path'), script.index('& $PowerShell @NativeArguments'))
        self.assertIn("[IO.Path]::GetTempPath()", script)
        self.assertIn("$args.Count -eq 1 -and $BuildKind -eq 'Windows'", script)
        self.assertIn("$NativeArguments += '-ImportContent'", script)
        self.assertIn("$NativeArguments += [string]$args[$ArgumentIndex]", script)
        self.assertIn("$ErrorActionPreference = 'Continue'\n    & $PowerShell @NativeArguments 2>&1 | ForEach-Object { Write-Host $_ }\n    $BuildExitCode = $LASTEXITCODE", script)
        self.assertIn('Stop-Transcript -ErrorAction Stop | Out-Null } catch { }', script)
        self.assertNotIn('Invoke-Expression', script)

    @unittest.skipUnless(os.name == 'nt', 'Windows cmd.exe/PowerShell required for actual launcher process fixtures')
    def test_actual_windows_launcher_processes(self):
        shell = shutil.which('powershell.exe')
        self.assertIsNotNone(shell, 'Windows PowerShell must be installed')
        stub = '''[CmdletBinding()]
param([string]$Project = '', [switch]$ImportContent, [int]$ExitCode = 0)
Write-Host ('PROJECT=' + $Project)
Write-Host ('IMPORT=' + [bool]$ImportContent)
Write-Error 'STDERR_SENTINEL' -ErrorAction Continue
exit $ExitCode
'''
        with tempfile.TemporaryDirectory(prefix='Digimon launcher spaces ! ') as folder:
            root = Path(folder)
            for name in ('Build_Launcher.ps1', 'Build_Windows.bat', 'Build_Windows.cmd', 'Build_UE58.bat'):
                shutil.copy2(TOOLS / name, root / name)
            child = root / 'Build_Windows.ps1'
            child.write_text(stub)

            def run(arguments, code, needle, batch=False):
                env = dict(os.environ, DIGIMONVENOMNXT_NO_PAUSE='1', TEMP=folder, TMP=folder)
                if batch:
                    command = [os.environ.get('COMSPEC', 'cmd.exe'), '/d', '/c', str(root / 'Build_Windows.cmd'), *arguments]
                else:
                    command = [shell, '-NoLogo', '-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass',
                               '-File', str(root / 'Build_Launcher.ps1'), 'Windows', *arguments]
                completed = subprocess.run(command, text=True, capture_output=True, timeout=45, env=env)
                output = completed.stdout + completed.stderr
                self.assertEqual(completed.returncode, code, output)
                self.assertIn(needle, output)
                match = re.search(r'Build log: (.+)', output)
                self.assertIsNotNone(match, output)
                log = Path(match.group(1).strip()).read_bytes()
                # Windows PowerShell transcripts may be UTF-8 or UTF-16.
                text = log.decode('utf-16') if log[:2] in (b'\xff\xfe', b'\xfe\xff') else log.decode('utf-8-sig')
                self.assertIn(needle, text)
                return output

            run([], 0, 'IMPORT=True')
            run(['-Project', r'C:\Game With Spaces!\Game.uproject'], 0, r'PROJECT=C:\Game With Spaces!\Game.uproject')
            run(['-ExitCode', '7'], 7, 'STDERR_SENTINEL')
            run(['-ThisParameterDoesNotExist'], 1, 'ThisParameterDoesNotExist')
            run(['-ExitCode', '7'], 7, 'STDERR_SENTINEL', batch=True)
            child.write_text('param(\n')
            run([], 1, 'Build_Windows.ps1')
            child.unlink()
            run([], 1, 'Build script is missing')
            child.write_text(stub)
            shutil.rmtree(root / 'Logs')
            (root / 'Logs').write_text('Force temporary log fallback')
            self.assertIn('DigimonVenomNXT-BuildLogs', run([], 0, 'IMPORT=True'))

    def test_editor_and_windows_use_the_same_host_receipt_location(self):
        helpers = (TOOLS / "NativeBuildChecks.ps1").read_text()
        assert_receipt_contract(self, helpers)
        importer = (EDITOR / "DigimonVenomNXTEditorLibrary.cpp").read_text()
        self.assertRegex(importer, r"ReceiptPath\(\).*FPaths::ProjectIntermediateDir\(\).*DigimonVenomNXT/ContentImportReceipt.json")
        with self.assertRaises(AssertionError):
            assert_receipt_contract(self, helpers.replace("return Join-Path $ProjectFolder 'Intermediate/", "return Join-Path $PluginRoot 'Intermediate/", 1))

    def test_receipt_requires_worlds_and_runtime_marker_material(self):
        helpers = (TOOLS / "NativeBuildChecks.ps1").read_text()
        sources = function(helpers, "Assert-DigimonCampaignSources")
        self.assertIn("foreach ($Level in @('MainMenu', 'PublicWorld'))", sources)
        self.assertIn("Convert-DigimonPackageToFile -PluginRoot $PluginRoot -Package $Package -Map", sources)
        for package in ("MI_DVNXT_FieldSprite", "DA_PlayableMapRevision"):
            self.assertIn(package, sources)
        receipt = function(helpers, "Assert-DigimonContentImport")
        self.assertIn("foreach ($Package in $ExpectedPackages.Keys)", receipt)
        self.assertIn("Get-FileHash -LiteralPath $File -Algorithm SHA1", receipt)
        self.assertIn("world repair alone cannot certify imported assets", receipt)

    def test_every_build_runs_unreal_startup_validation_before_game_and_cook(self):
        script = (TOOLS / "Build_Windows.ps1").read_text()
        assert_validation_before_game(self, script)
        with self.assertRaises((AssertionError, ValueError)):
            assert_validation_before_game(self, script.replace("Invoke-DigimonBuildStep -Label 'Validate saved startup worlds and effective game configuration'", "# validation omitted", 1))

    def test_repair_and_import_cannot_bypass_complete_receipt(self):
        script = (TOOLS / "Build_Windows.ps1").read_text()
        self.assertIn("if ($ImportContent -and $RepairStartup) { throw", script)
        self.assertIn("-SourceOnly:($ImportContent -or $RepairStartup)", script)
        calls = [line.strip() for line in script.splitlines() if "$CampaignContent = Assert-DigimonCampaignSources" in line]
        self.assertEqual(len(calls), 4)
        self.assertTrue(all("-ProjectFolder $ProjectFolder" in call for call in calls))
        self.assertTrue(all("-SourceOnly" not in call for call in calls[1:]))
        repair = script[script.index("    if ($RepairStartup) {"):script.index("    # Hashes prove saved bytes")]
        self.assertIn("'-RepairStartup'", repair)
        self.assertIn("Assert-DigimonCampaignSources", repair)
        commandlet = (EDITOR / "DigimonVenomNXTImportCommandlet.cpp").read_text()
        self.assertIn('TEXT("RepairStartup")', commandlet)
        self.assertIn('TEXT("ValidateStartup")', commandlet)

    def test_engine_version_gate_precedes_native_host_or_plugin_build(self):
        script = (TOOLS / "Build_Windows.ps1").read_text()
        self.assertLess(script.index("Assert-DigimonEngineVersion -EngineRoot $EngineRoot"), script.index("Ensure-DigimonNativeHost -Project"))
        plugin = (TOOLS / "Build_UE58.ps1").read_text()
        self.assertLess(plugin.index("Assert-DigimonEngineVersion -EngineRoot $EngineRoot"), plugin.index("& $RunUAT BuildPlugin"))
        self.assertIn("does not create MainMenu/PublicWorld", plugin)
        version = function((TOOLS / "NativeBuildChecks.ps1").read_text(), "Assert-DigimonEngineVersion")
        self.assertIn("$Version.MajorVersion -ne 5 -or $Version.MinorVersion -ne 8", version)

    def test_verified_resume_is_default_and_progress_is_never_a_receipt(self):
        script = (TOOLS / "Build_Windows.ps1").read_text()
        self.assertIn("[switch]$ForceReimport", script)
        self.assertIn("if ($ForceReimport -and !$ImportContent) { throw", script)
        resume = script.index("if (!$ForceReimport) { $ImportArguments += '-NoReplace' }")
        run = script.index("Invoke-DigimonBuildStep -Label 'Import all registered Digimon content and save generated levels'")
        self.assertLess(resume, run)
        helpers = (TOOLS / "NativeBuildChecks.ps1").read_text()
        self.assertNotIn("ContentImportProgress.json", helpers)
        self.assertNotIn("ContentImportProgress.json", script)
        assert_receipt_contract(self, helpers)

    def test_powershell_receipt_and_native_build_behaviors(self):
        shell = shutil.which("pwsh") or shutil.which("powershell.exe")
        if not shell:
            self.skipTest("PowerShell unavailable; behavioral Windows fixtures must run on the Windows build host")
        result = subprocess.run([shell, "-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File",
                                 str(TOOLS / "Test_NativeBuild.ps1")], capture_output=True, text=True, timeout=180)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())


if __name__ == "__main__":
    unittest.main()
