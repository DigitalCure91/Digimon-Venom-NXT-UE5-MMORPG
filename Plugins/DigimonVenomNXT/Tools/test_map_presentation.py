#!/usr/bin/env python3
"""Check registered public art and the production editor preview selection policy."""
import json
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
EDITOR = ROOT / "Source/DigimonVenomNXTEditor/Private"


class MapPresentationTests(unittest.TestCase):
    def test_every_registered_map_has_full_background_and_foreground_assets(self):
        registry = json.loads((ROOT / "Resources/DigimonMaps.json").read_text())
        manifest = json.loads((ROOT / "Resources/GameData/import_manifest.json").read_text())
        sprites = {item["asset"]: item for item in manifest["sprites"]}
        textures = {item["asset"]: item for item in manifest["textures"]}
        self.assertEqual(len(registry["maps"]), registry["mapCount"])
        for row in registry["maps"]:
            prefix = f'/DigimonVenomNXT/Generated/Maps/SP_PlayMap_{row["mapId"]:03d}'
            layers = [(prefix, row["importedTexture"], row["groundSource"], True)]
            if row.get("foregroundTexture"):
                layers.append((prefix + "_Foreground", row["foregroundTexture"], row["foregroundSource"], False))
            for path, texture, source, ground in layers:
                with self.subTest(map=row["mapId"], layer=path):
                    sprite, image = sprites[path], textures[texture]
                    self.assertEqual(sprite["texture"], texture)
                    self.assertEqual(sprite["rect"], [0, 0, row["sourceWidth"], row["sourceHeight"]])
                    self.assertEqual(sprite["pivot"], [row["sourceWidth"] / 2, row["sourceHeight"] / 2])
                    self.assertEqual(bool(sprite.get("ground")), ground)
                    self.assertEqual([image["width"], image["height"]], [row["sourceWidth"], row["sourceHeight"]])
                    self.assertEqual(image["source"], source)
                    self.assertNotEqual(source, row["collisionSource"], "Collision mask must never be visible artwork")

    def test_actual_editor_preview_selection_is_bounded_and_selection_aware(self):
        cpp = r'''
#include "DigimonVenomNXTEditorMapPreviewCore.h"
#include <cassert>
#include <limits>
#include <iostream>
using namespace DigimonVenomNXTEditorMapPreviewCore;
int main() {
    assert(DistanceToMap(0,0,0,0,5000,2500)==0);
    assert(DistanceToMap(5000,2500,0,0,5000,2500)==0);
    assert(DistanceToMap(5003,2504,0,0,5000,2500)==25);
    std::vector<Candidate> maps;
    for(int i=0;i<500;++i)
        maps.push_back({i,DistanceToMap(0,0,(i%10)*14000.,(i/10)*11000.,5000,2500),false});
    auto initial=Choose(maps);
    assert(initial.size()==4 && initial[0]==0); // Map1 is visible on first opening.
    maps[499].Selected=true;
    auto selected=Choose(maps);
    assert(selected.size()==4 && selected[0]==499); // Outliner selection wins at any distance.
    maps[499].Selected=false;
    for(auto& map:maps)
        map.DistanceSquared=DistanceToMap(126000,539000,(map.Index%10)*14000.,(map.Index/10)*11000.,5000,2500);
    auto focused=Choose(maps);
    assert(focused.size()==4 && focused[0]==499); // Focusing a distant map moves the preview set.
    for(auto& map:maps)map.Selected=true;
    assert(Choose(maps).size()==4); // Selecting all never retains 500 textures.
    maps[499].DistanceSquared=std::numeric_limits<double>::quiet_NaN();
    for(int index:Choose(maps))assert(index!=499);
    assert(Choose(maps,0).empty());assert(Choose({}).empty());
    assert(Choose({{5,1,false},{3,1,false},{4,1,false}},2)==std::vector<int>({3,4}));
    std::cout<<"Editor map previews: initial map, selection, distant focus, bounded residency and invalid coordinates passed\n";
}
'''
        with tempfile.TemporaryDirectory(prefix="digimon-map-preview-") as directory:
            source, executable = Path(directory) / "preview.cpp", Path(directory) / "preview"
            source.write_text(cpp)
            built = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic", "-I", str(EDITOR), str(source), "-o", str(executable)], capture_output=True, text=True, timeout=30)
            self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
            ran = subprocess.run([str(executable)], capture_output=True, text=True, timeout=30)
            self.assertEqual(ran.returncode, 0, ran.stdout + ran.stderr)
            print(ran.stdout.strip())


if __name__ == "__main__":
    unittest.main()
