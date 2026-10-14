#!/usr/bin/env python3
"""Exercise the actual native collision core against every shipped public-map spawn."""
import base64
import json
from pathlib import Path
import re
import struct
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / "Source" / "DigimonVenomNXTRuntime" / "Public"


class ImportedMapCollision(unittest.TestCase):
    def test_every_registered_spawn_uses_walkable_native_footprint(self):
        maps = json.loads((ROOT / "Resources" / "DigimonMaps.json").read_text())["maps"]
        self.assertTrue(maps)
        settings = (PUBLIC / "DigimonVenomNXTSettings.h").read_text()
        width = float(re.search(r"float MapWorldWidth = ([\d.]+)f;", settings).group(1))
        radius = float(re.search(r"float TamerCollisionProbeRadius = ([\d.]+)f;", settings).group(1))
        with tempfile.TemporaryDirectory(prefix="digimon-native-spawns-") as directory:
            temp = Path(directory)
            fixture = temp / "masks.bin"
            with fixture.open("wb") as stream:
                stream.write(struct.pack("<I", len(maps)))
                for row in maps:
                    bits = base64.b64decode(row["walkGridBits"], validate=True)
                    stream.write(struct.pack("<IIIIdd", row["mapId"], row["walkGridWidth"],
                                             row["walkGridHeight"], len(bits), row["safeSpawnU"], row["safeSpawnV"]))
                    stream.write(bits)
            source = temp / "check.cpp"
            source.write_text(r'''
#include "DigimonVenomNXTCollisionCore.h"
#include <fstream>
#include <iostream>
#include <vector>
template<class T> void Read(std::ifstream& file, T& value) { file.read(reinterpret_cast<char*>(&value), sizeof(value)); }
int main(int argc, char** argv) {
    if (argc != 2) return 2;
    std::ifstream file(argv[1], std::ios::binary);
    unsigned count = 0, failures = 0; Read(file, count);
    for (unsigned index = 0; index < count; ++index) {
        unsigned id, width, height, length; double u, v;
        Read(file, id); Read(file, width); Read(file, height); Read(file, length); Read(file, u); Read(file, v);
        std::vector<std::uint8_t> bits(length);
        file.read(reinterpret_cast<char*>(bits.data()), length);
        if (!file.good() || !width || !height) return 2;
        DigimonVenomNXTCollisionCore::Grid grid{int(width), int(height), bits.data(), length,
            MAP_WORLD_WIDTH, MAP_WORLD_WIDTH * height / width};
        if (!DigimonVenomNXTCollisionCore::IsWalkable(grid, {u * grid.WorldWidth, v * grid.WorldHeight}, FOOTPRINT_RADIUS)) {
            std::cerr << "Blocked native spawn for map " << id << "\n"; ++failures;
        }
    }
    std::cout << count << " imported native CollisionCore spawn checks, radius " << FOOTPRINT_RADIUS
              << ": " << failures << " failures\n";
    return !file.good() || !count || failures ? 1 : 0;
}
'''.replace("MAP_WORLD_WIDTH", repr(width)).replace("FOOTPRINT_RADIUS", repr(radius)), encoding="utf-8")
            executable = temp / "check.exe"
            compiled = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                                       "-I" + str(PUBLIC), str(source), "-o", str(executable)], capture_output=True, text=True)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(executable), str(fixture)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            print(result.stdout.strip())


if __name__ == "__main__":
    unittest.main()
