#!/usr/bin/env python3
"""Verify Digimon native source/content contracts. Does not compile or run Unreal.

Requires Python 3.10+, Pillow and NumPy. Run from any directory:
    python Tools/validate_plugin.py
Content import, cooking and Windows launch are separate Unreal acceptance steps.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
from convert_digimon_content import verify_export
from validate_compile_surface import validate as validate_compile


def validate(root: Path) -> tuple[list[str], list[str]]:
    checks, errors = [], []
    descriptor = json.loads((root / 'DigimonVenomNXT.uplugin').read_text(encoding='utf-8'))
    modules = {row['Name']: row['Type'] for row in descriptor['Modules']}
    expected_modules = {'DigimonVenomNXTRuntime': 'Runtime', 'DigimonVenomNXTEditor': 'Editor'}
    if modules != expected_modules or not descriptor.get('CanContainContent'):
        errors.append('Plugin descriptor module names/types or content flag are incorrect.')
    else:
        checks.append('DigimonVenomNXT descriptor has its Runtime/Editor modules and content mount.')
    editor_modules = [row for row in descriptor['Modules'] if row.get('Name') == 'DigimonVenomNXTEditor']
    if len(editor_modules) != 1 or editor_modules[0].get('LoadingPhase') != 'Default':
        errors.append('DigimonVenomNXTEditor must load at Default so Unreal can find the import commandlet before engine initialization completes.')
    else:
        checks.append('Editor module loads at Default for import/repair/validation commandlet discovery.')
    dependencies = {row['Name'] for row in descriptor.get('Plugins', []) if row.get('Enabled')}
    if not {'Paper2D', 'CommonUI', 'EnhancedInput'}.issubset(dependencies):
        errors.append('A required engine plugin dependency is not enabled.')
    else:
        checks.append('Paper2D, CommonUI and EnhancedInput dependencies are declared.')
    try:
        report = verify_export(root)
        checks.append('Native content payload: ' + json.dumps(report, sort_keys=True))
    except (ValueError, AssertionError, OSError, KeyError) as exc:
        errors.append('Content payload: ' + str(exc))
    compile_errors, compile_checks = validate_compile(root)
    errors.extend(compile_errors)
    checks.extend(compile_checks)
    required_tools = ['Build_Windows.bat', 'Build_Windows.cmd', 'Build_Windows.ps1', 'Build_Launcher.ps1', 'NativeBuildChecks.ps1', 'NativeHost.ps1', 'PackagedPlugins.ps1', 'HostCredentials.ps1', 'Start_LocalHost.ps1']
    missing = [name for name in required_tools if not (root / 'Tools' / name).is_file()]
    if missing:
        errors.append('Missing Windows packaging tools: ' + ', '.join(missing))
    else:
        checks.append('Windows packaging entry points and native validation helpers are present.')
    for path in (root / 'Config').glob('*.ini'):
        for line in path.read_text(encoding='utf-8').splitlines():
            key, sep, value = line.partition('=')
            if sep and key.strip() == 'AdminHostPassword' and value.strip().strip('"'):
                errors.append(f'{path.name}: shared config contains a hosting password; value was not printed.')
    return errors, checks


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    errors, checks = validate(args.root.resolve())
    for check in checks:
        print('PASS:', check)
    for error in errors:
        print('FAIL:', error)
    print(f'{len(checks)} source/content checks passed; {len(errors)} failures. Unreal compilation/play testing was not performed.')
    return int(bool(errors))


if __name__ == '__main__':
    raise SystemExit(main())
