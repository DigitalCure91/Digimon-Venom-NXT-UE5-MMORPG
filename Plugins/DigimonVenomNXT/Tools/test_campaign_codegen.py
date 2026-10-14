#!/usr/bin/env python3
"""Guard MSVC-sized campaign construction and preserve the reviewed source data.

This checks the emitted call graph and every ordered authored assignment, including
dialogue, gates, teams and rewards. Runtime progression is exercised separately by
run_digimon_campaign_tests.py. No Unreal or original browser source is required.
"""
import hashlib
import importlib.util
import re
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
GENERATED = TOOLS.parent / 'Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTCampaignContent.inl'
FUNCTION = re.compile(
    r'^static (?P<noinline>FORCENOINLINE )?(?:void|FContent) (?P<name>\w+)\([^\n]*\)\n\{\n(?P<body>.*?)^}',
    re.MULTILINE | re.DOTALL)
CALL = re.compile(r'(PopulateCampaign\d+\w+)\(C\);')
STRING = re.compile(r'"(?:\\.|[^"\\])*"')
# Captured from the original, unsplit generated builders. These cover all data,
# not helper names or formatting. Intentional source revisions must review and
# update the corresponding snapshot, rather than accepting a structural rewrite.
AUTHORED = (
    (18, 60, 282, '359f6b025f07c487c80e4fea6127ca3b64e78606fea740d4df019f884745740f'),
    (18, 92, 638, '2bde9df868bd635449a4e07e721ccdb0d354c20dcf4c966b14041cd1e1d18237'),
    (31, 141, 1148, 'fc65b7f1d7f96372ed562f9b38025576416f5d9ad6892b7411d2eaa7640575a3'),
)


class CampaignCodeGenerationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        spec = importlib.util.spec_from_file_location('campaign_generator', TOOLS / 'generate_digimon_campaigns.py')
        cls.generator = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(cls.generator)
        cls.functions = {m['name']: m for m in FUNCTION.finditer(GENERATED.read_text(encoding='utf-8'))}

    def expanded(self, name, visited):
        self.assertNotIn(name, visited, f'Helper is duplicated or recursive: {name}')
        visited.add(name)
        self.assertIn(name, self.functions, f'Missing campaign helper: {name}')
        operations = []
        for line in self.functions[name]['body'].splitlines():
            line = line.strip()
            call = CALL.fullmatch(line)
            if call:
                operations.extend(self.expanded(call[1], visited))
            elif line and line not in ('FContent C;', 'return C;'):
                operations.append(line)
        return operations

    def test_all_functions_are_bounded_and_keep_their_boundaries(self):
        self.assertEqual(sum(name.startswith('BuildCampaign') for name in self.functions), 3)
        for name, function in self.functions.items():
            with self.subTest(function=name):
                self.assertTrue(function['noinline'], 'Inlining can recreate the C4883-sized builder')
                body = function['body']
                self.assertLessEqual(STRING.sub('""', body).count(';'), self.generator.MAX_FUNCTION_STATEMENTS)
                self.assertLessEqual(len(body.encode('utf-8')), self.generator.MAX_FUNCTION_BYTES)
                calls = [line.strip() for line in body.splitlines() if CALL.fullmatch(line.strip())]
                self.assertLessEqual(len(calls), self.generator.MAX_BATCH_RECORDS)

    def test_every_authored_value_and_read_order_is_preserved(self):
        visited = set()
        for campaign, (maps, npcs, branches, digest) in enumerate(AUTHORED):
            with self.subTest(campaign=campaign):
                operations = '\n'.join(self.expanded(f'BuildCampaign{campaign}', visited))
                self.assertEqual(operations.count('C.Maps.Add(M);'), maps)
                self.assertEqual(operations.count('C.NPCs.Add(MoveTemp(N));'), npcs)
                self.assertEqual(operations.count('N.DialogueBranches.Add('), branches)
                self.assertEqual(hashlib.sha256(operations.encode('utf-8')).hexdigest(), digest)
        self.assertEqual(visited, set(self.functions), 'Unreachable authored helpers would silently lose content')

    def test_generator_rejects_an_oversized_future_record(self):
        emitted = []
        with self.assertRaisesRegex(ValueError, 'function size contract'):
            self.generator.emit_function(emitted, 'OversizedStatements', ['    C.Name = TEXT("x");'] *
                                         (self.generator.MAX_FUNCTION_STATEMENTS + 1))
        self.assertEqual(emitted, [], 'Rejected functions must not be partially emitted')
        with self.assertRaisesRegex(ValueError, 'function size contract'):
            self.generator.emit_function(emitted, 'OversizedText',
                                         ['    C.Name = TEXT("' + 'x' * self.generator.MAX_FUNCTION_BYTES + '");'])
        self.assertEqual(emitted, [])


if __name__ == '__main__':
    unittest.main()
