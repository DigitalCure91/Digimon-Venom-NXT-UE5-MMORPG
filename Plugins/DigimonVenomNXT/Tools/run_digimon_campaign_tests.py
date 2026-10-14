#!/usr/bin/env python3
"""Exercise actual authored C++ campaigns with small Unreal-container substitutes.

This checks state-machine behavior and generated C++ syntax. It is explicitly
NOT UnrealHeaderTool, an Unreal build, an editor import, or a play test.
Requires Python 3 and clang++ or g++; runs without the original browser source.
"""
import argparse
import os
import re
from pathlib import Path
import shutil
import subprocess
import tempfile


def live_profile_declarations(public):
    """Use the shipped schema verbatim; unrelated nested value types stay opaque.

    No hand-written Profile or Progress fields can hide a stale runtime member.
    These substitutes do not implement Unreal reflection or serialization.
    """
    source = (public / 'DigimonVenomNXTTypes.h').read_text()
    def extract(kind, name):
        pattern = (r'enum class ' if kind == 'enum' else r'struct DIGIMONVENOMNXTRUNTIME_API ') + name + r'\b.*?\n\};'
        match = re.search(pattern, source, re.S)
        if not match:
            raise AssertionError('Cannot extract live declaration: ' + name)
        return match.group()
    enums = [extract('enum', name) for name in ('EDigimonVariant', 'EDigimonPrivateCampaign')]
    schema = [extract('struct', name) for name in ('FDigimonStoryProgress', 'FDigimonRelayProgress', 'FDigimonPlayerProfile')]
    opaque = ('FDigimonOwnedPartner', 'FDigimonFarmState', 'FDigimonScanRecord', 'FDigimonInventoryEntry', 'FDigimonRankedCareer', 'FDigimonSeasonCareer')
    return '#pragma once\n#include "CoreMinimal.h"\n' + '\n'.join(enums) + '\n' + '\n'.join('struct ' + name + ' {};' for name in opaque) + '\n' + '\n'.join(schema) + '\n'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--optimization", choices=("0", "2"), default="0", help="Portable compiler optimization level (default: 0).")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    public = root / 'Source/DigimonVenomNXTRuntime/Public'
    private = root / 'Source/DigimonVenomNXTRuntime/Private'
    fixtures = root / 'Tools/tests/campaign'
    compiler = os.environ.get('CXX') or shutil.which('clang++') or shutil.which('g++')
    if not compiler:
        raise SystemExit('Install clang++ or g++, or set CXX to a compatible compiler.')
    with tempfile.TemporaryDirectory(prefix='digimon_campaign_tests_') as temp:
        temp = Path(temp)
        for name in ('CoreMinimal.h', 'test_campaigns.cpp'):
            shutil.copy2(fixtures / name, temp / name)
        (temp / "DigimonVenomNXTTypes.h").write_text(live_profile_declarations(public))
        # Copy live non-reflected declarations so generated content is checked
        # against the current plugin's actual API, not stale duplicate fixtures.
        for name in ('DigimonVenomNXTCampaignAuthored.h', 'DigimonVenomNXTRelay.h', 'DigimonVenomNXTRelayCore.h', 'DigimonVenomNXTGhostLine.h', 'DigimonVenomNXTChronicles.h', 'DigimonVenomNXTCampaign.h', 'DigimonVenomNXTCampaignCore.h', 'DigimonVenomNXTVariantCore.h', 'DigimonVenomNXTRelaySessionCore.h'):
            shutil.copy2(public / name, temp / name)
        executable = temp / ('test_campaigns.exe' if os.name == 'nt' else 'test_campaigns')
        subprocess.run([compiler, '-std=c++17', '-O' + args.optimization, '-I' + str(temp),
                        str(private / 'DigimonVenomNXTCampaignAuthored.cpp'),
                        str(private / 'DigimonVenomNXTGhostLine.cpp'),
                        str(private / 'DigimonVenomNXTChronicles.cpp'),
                        str(private / 'DigimonVenomNXTRelay.cpp'),
                        str(private / 'DigimonVenomNXTCampaign.cpp'),
                        str(temp / 'test_campaigns.cpp'), '-o', str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
    print('Native campaign state-machine checks passed. Unreal compilation and play testing remain separate gates.')


if __name__ == '__main__':
    main()
