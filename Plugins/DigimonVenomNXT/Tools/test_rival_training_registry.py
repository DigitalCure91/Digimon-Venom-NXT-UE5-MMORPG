#!/usr/bin/env python3
"""Exercise the production C++ planner against the shipped public habitat registry."""
import json
import os
from pathlib import Path
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    maps = json.loads((ROOT / "Resources/DigimonMaps.json").read_text(encoding="utf-8"))["maps"]
    with tempfile.TemporaryDirectory(prefix="digimon-rival-training-") as directory:
        work = Path(directory)
        fixture = work / "habitats.txt"
        fixture.write_text("".join(f"{row['mapId']} {row['recommendedMinLevel']} {row['recommendedMaxLevel']}\n" for row in maps), encoding="utf-8")
        executable = work / "training"
        compiler = shlex.split(os.environ.get("CXX", "g++"))
        subprocess.run(compiler + ["-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
            str(ROOT / "Tools/test_rival_training_core.cpp"), "-o", str(executable)], check=True)
        subprocess.run([str(executable), str(fixture)], check=True)


if __name__ == "__main__":
    main()
