#!/usr/bin/env python3
"""Regression for Log(20261009-061115).txt C2039.

Compiles the actual source call against a minimal documented UScrollBox API
surface, not Unreal headers. A negative control must reject the reported spelling.
Epic UE5.8 reference:
https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/UMG/UScrollBox
"""
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTWorldChatWidget.cpp'


class WorldChatScrollbarAPI(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        source = SOURCE.read_text(encoding='utf-8')
        calls = re.findall(r'HistoryScroll\s*->\s*SetScroll[Bb]arThickness\([^;]*;', source)
        if len(calls) != 1:
            raise AssertionError('Expected exactly one real WORLD chat thickness call')
        cls.call = calls[0]

    def compile_call(self, call):
        with tempfile.TemporaryDirectory(prefix='digimon-scrollbar-api-') as directory:
            folder = Path(directory)
            fixture = folder / 'scrollbar.cpp'
            fixture.write_text('''
#include <cassert>
struct FVector2D { double X,Y; FVector2D(double XIn,double YIn):X(XIn),Y(YIn) {} };
struct UScrollBox {
    FVector2D Thickness{0,0};
    void SetScrollbarThickness(const FVector2D& Value) { Thickness=Value; }
};
int main() { UScrollBox Scroll; UScrollBox* HistoryScroll=&Scroll;
''' + call + '\nassert(Scroll.Thickness.X==4 && Scroll.Thickness.Y==4); }\n')
            executable = folder / 'scrollbar'
            result = subprocess.run(shlex.split(os.environ.get('CXX', 'g++')) +
                ['-std=c++17', '-Wall', '-Wextra', '-Werror', '-pedantic', str(fixture), '-o', str(executable)],
                capture_output=True, text=True)
            if result.returncode == 0:
                subprocess.run([str(executable)], check=True)
            return result

    def test_actual_production_call_compiles_and_preserves_thickness(self):
        result = self.compile_call(self.call)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_reported_spelling_is_rejected(self):
        original = self.call.replace('SetScrollbarThickness', 'SetScrollBarThickness')
        result = self.compile_call(original)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('SetScrollBarThickness', result.stderr)


if __name__ == '__main__':
    unittest.main()
