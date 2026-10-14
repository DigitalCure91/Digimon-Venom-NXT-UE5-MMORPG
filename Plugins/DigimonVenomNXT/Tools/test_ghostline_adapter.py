#!/usr/bin/env python3
"""Compile and execute the actual source-campaign adapter and authored content.

Uses minimal Unreal-container substitutes; this is not UHT, a real Unreal build,
reflected-save serialization, rendering, or an editor play test. The shared runner
covers all campaigns plus focused Super Xros Wars acceptance, report, reveal,
return-visit, loss/retry and finale receipt behavior.
"""
from run_digimon_campaign_tests import main

if __name__ == '__main__':
    main()
