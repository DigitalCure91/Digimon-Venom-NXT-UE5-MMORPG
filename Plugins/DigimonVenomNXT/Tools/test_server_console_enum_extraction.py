#!/usr/bin/env python3
"""Regressions for enum source extraction; does not compile Unreal code."""
from pathlib import Path
import unittest

from validate_server_console_integration import enum_members


class ConsoleEnumExtractionTests(unittest.TestCase):
    def test_forward_declaration_cannot_capture_unrelated_class(self):
        definition = 'enum class EDigimonAudioCue : uint8 { UIHover, Confirm, Error };'
        forward = '''
            enum class EDigimonAudioCue : uint8;
            UCLASS() class APlayerState {
                GENERATED_BODY()
                int AccountId;
            };
        '''
        for sources in ((definition, forward), (forward, definition)):
            known = {}
            for source in sources:
                known.update(enum_members(source))
            self.assertEqual(known, {'EDigimonAudioCue': {'UIHover', 'Confirm', 'Error'}})
        self.assertEqual(enum_members(forward), {})

    def test_inline_members_assignments_metadata_and_comments(self):
        source = '''
            // enum class EDigimonFake { Bad };
            const char* Text = "enum class EDigimonFake { Bad };";
            enum class EDigimonCue : uint8 {
                First = 0, Confirm UMETA(DisplayName = "Confirm, action", Hidden),
                /* Error, Fake, */ Error = (1 << 2),
                Nested = Expression(1, (2 + 3)), Last,
            };
        '''
        self.assertEqual(enum_members(source), {'EDigimonCue': {
            'First', 'Confirm', 'Error', 'Nested', 'Last'}})

    def test_shipped_audio_definition_survives_player_state_forward_declaration(self):
        root = Path(__file__).resolve().parents[1] / 'Source/DigimonVenomNXTRuntime/Public'
        known = enum_members((root / 'DigimonVenomNXTAudioSubsystem.h').read_text(encoding='utf-8'))
        known.update(enum_members((root / 'DigimonVenomNXTPlayerState.h').read_text(encoding='utf-8')))
        self.assertIn('Confirm', known['EDigimonAudioCue'])
        self.assertIn('Error', known['EDigimonAudioCue'])
        self.assertNotIn('UnshippedCue', known['EDigimonAudioCue'])


if __name__ == '__main__':
    unittest.main()
