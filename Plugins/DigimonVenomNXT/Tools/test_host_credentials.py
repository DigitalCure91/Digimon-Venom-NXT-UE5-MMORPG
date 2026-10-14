#!/usr/bin/env python3
"""Run real PowerShell credential migration and local host process fixtures."""
from pathlib import Path
import json
import os
import shutil
import subprocess
import tempfile
import time
import unittest

TOOLS = Path(__file__).resolve().parent
SHELL = shutil.which('pwsh') or shutil.which('powershell.exe')


class HostCredentialWorkflow(unittest.TestCase):
    def test_build_prepares_credentials_before_distributable_check(self):
        script = (TOOLS / 'Build_Windows.ps1').read_text()
        prepare = script.index('$HostPreparation = Move-DigimonHostCredential')
        check = script.index('Assert-DigimonNoSharedHostSecret -ProjectFolder')
        compile_step = script.index("Invoke-DigimonBuildStep -Label '2/5 Compile native Editor target'")
        self.assertTrue(prepare < check < compile_step)
        self.assertIn('if (!$DryRun -or !$HostPreparation.Planned)', script)
        self.assertIn("'Saved/DigimonVenomNXT/PlayPackagedHost.cmd'", script)
        self.assertNotIn('HostPassword', script)

    @unittest.skipUnless(SHELL, 'PowerShell runtime required for filesystem migration tests')
    def test_real_powershell_migration(self):
        result = subprocess.run([SHELL, '-NoLogo', '-NoProfile', '-NonInteractive', '-ExecutionPolicy',
                                 'Bypass', '-File', str(TOOLS / 'Test_HostCredentials.ps1')],
                                text=True, capture_output=True, timeout=180)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    @unittest.skipUnless(SHELL and os.name == 'posix', 'Linux PowerShell/native process fixture; Windows launch remains an acceptance check')
    def test_local_host_launch_transfers_password_only_to_child_environment(self):
        # This verifies ProcessStartInfo with a real native child process. It is
        # not a Windows executable, Unreal launch, or CMD shell test.
        with tempfile.TemporaryDirectory(prefix='Digimon local host spaces ') as temp:
            root = Path(temp)
            host = root / 'Saved/DigimonVenomNXT/Host.ini'
            host.parent.mkdir(parents=True)
            host.write_text('[Hosting]\nPassword="fixture-local-value"\n')
            result_file = root / 'child-result.json'
            game = root / 'fixture-game'
            game.write_text('#!/usr/bin/env python3\nimport os,json,pathlib\n' +
                            'pathlib.Path(' + repr(str(result_file)) + ').write_text(json.dumps({' +
                            '"password":os.environ.get("DIGIMONVENOMNXT_HOST_PASSWORD"),' +
                            '"cwd":os.getcwd()}))\n')
            game.chmod(0o700)
            command = [SHELL, '-NoLogo', '-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass',
                       '-File', str(TOOLS / 'Start_LocalHost.ps1'), '-ProjectFolder', str(root),
                       '-GameExecutable', str(game)]
            for inherited in ('', 'fixture-environment-value'):
                with self.subTest(environment_override=bool(inherited)):
                    result_file.unlink(missing_ok=True)
                    env = dict(os.environ)
                    env.pop('DIGIMONVENOMNXT_HOST_PASSWORD', None)
                    if inherited:
                        env['DIGIMONVENOMNXT_HOST_PASSWORD'] = inherited
                    run = subprocess.run(command, capture_output=True, text=True, timeout=20, env=env)
                    self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                    for _ in range(100):
                        if result_file.exists():
                            break
                        time.sleep(0.02)
                    child = json.loads(result_file.read_text())
                    expected = inherited or 'fixture-local-value'
                    self.assertEqual(child['password'], expected)
                    self.assertEqual(Path(child['cwd']), root)
                    self.assertNotIn(expected, run.stdout + run.stderr)
            host.unlink()
            env = dict(os.environ)
            env.pop('DIGIMONVENOMNXT_HOST_PASSWORD', None)
            run = subprocess.run(command, capture_output=True, text=True, timeout=20, env=env)
            self.assertEqual(run.returncode, 1)
            self.assertIn('No local hosting password', run.stdout + run.stderr)


if __name__ == '__main__':
    unittest.main()
