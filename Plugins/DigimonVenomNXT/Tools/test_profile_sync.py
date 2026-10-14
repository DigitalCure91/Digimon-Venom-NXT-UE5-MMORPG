#!/usr/bin/env python3
"""Exercise the production C++ framing, plus source/lifecycle regression guards.

Synthetic JSON tests do not emulate Unreal serialization or launch network clients.
Native codec/persistence tests are in DigimonVenomNXTAccountSyncTests.cpp.
"""
from pathlib import Path
import copy
import json
import os
import random
import shlex
import subprocess
import tempfile
import unittest
import zlib

ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / 'Source/DigimonVenomNXTRuntime/Public'
PRIVATE = ROOT / 'Source/DigimonVenomNXTRuntime/Private'


def fixture(grade: str) -> dict:
    rng = random.Random(420)
    def partner(i):
        return {'instanceId': f'{i:032x}', 'speciesId': f'species_{i % 300}', 'variant': 'Normal',
                'nickname': f'Partner {i}', 'level': 75, 'experience': 123456, 'cAM': 80, 'aBI': 90,
                'currentHP': 900, 'currentSP': 140,
                'moves': [{'moveId': f'move_{j}', 'mastery': 4} for j in range(6)]}
    partners = [partner(i) for i in range(1, 7)]
    roster = [{'tamerId': f'tamer_{i}', 'name': f'Career Rival {i}',
               'team': [partner(100 + i * 6 + j) for j in range(6)], 'rating': 2100 + i}
              for i in range(16)]
    standings = [{k: v for k, v in row.items() if k != 'team'} for row in roster]
    archive = [{'week': week, 'standings': copy.deepcopy(standings),
                'matches': [{'matchId': f'{week}_{m}', 'bResolved': True, 'result': 'Won after 120 turns'} for m in range(8)]}
               for week in range(1, 9)]
    # Substantial unique log text prevents compression from hiding window/boundary defects.
    log = ['Turn %03d: ' % i + ''.join(rng.choice('abcdefghijklmnopqrstuvwxyz0123456789 ') for _ in range(512)) for i in range(160)]
    return {'accountId': 'synthetic_account', 'username': 'Fixture Tamer', 'collection': partners,
            'party': [p['instanceId'] for p in partners], 'credits': 123456789, 'digiRubies': 731,
            'inventory': [{'itemId': 'digimeat_cam', 'quantity': 12}],
            'season': {'week': 9, 'roster': roster, 'archive': archive, 'battleCheckpointJson': json.dumps({'decision': 'unchanged', 'turn': 32, 'team': partners})},
            'ranked': {'grade': grade, 'rating': 2100 if grade == 'A' else 1800,
                       'defenderTeam': partners, 'lastBattleLog': log, 'careerWins': 87, 'energy': 7},
            'commerceRevision': 12, 'neoLabRecoveryRevision': 5}


class ProfileSyncTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix='digimon-profile-sync-')
        cls.work = Path(cls.temp.name)
        cls.binary = cls.work / 'profile_sync_core'
        cmd = shlex.split(os.environ.get('CXX', 'g++')) + ['-std=c++17', '-Wall', '-Wextra', '-Werror',
               '-Wshadow', '-O2', '-I', str(PUBLIC), str(ROOT / 'Tools/test_profile_sync_core.cpp'), '-o', str(cls.binary)]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=45)
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    @classmethod
    def tearDownClass(cls):
        cls.temp.cleanup()

    def test_production_core_boundaries_and_adverse_delivery(self):
        result = subprocess.run([str(self.binary)], capture_output=True, text=True, timeout=45)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        print(result.stdout.strip())

    def test_six_party_season_ranked_a_b_repeated_reconnections(self):
        for grade in ('A', 'B'):
            original = fixture(grade)
            for reconnect in range(2):
                with self.subTest(grade=grade, reconnect=reconnect):
                    raw = json.dumps(original, ensure_ascii=False, separators=(',', ':')).encode('utf-8')
                    self.assertGreater(len(raw), 65536)
                    compressed = zlib.compress(raw)
                    self.assertGreater(len(compressed), 4 * 1024)
                    source, target = self.work / 'source.bin', self.work / 'target.bin'
                    source.write_bytes(compressed)
                    result = subprocess.run([str(self.binary), str(source), str(target)], capture_output=True, text=True, timeout=45)
                    self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                    received = zlib.decompress(target.read_bytes())
                    self.assertEqual(received, raw)
                    decoded = json.loads(received)
                    self.assertEqual(decoded, original)
                    self.assertEqual(len(decoded['party']), 6)
                    self.assertEqual(decoded['ranked']['grade'], grade)
                    print(f'PASS: synthetic grade {grade}, reconnect {reconnect+1}: {len(raw):,} JSON bytes -> {len(compressed):,} compressed bytes; exact restoration')
                    original = decoded

    def test_profile_is_no_longer_one_replicated_property(self):
        header = (PUBLIC / 'DigimonVenomNXTPlayerState.h').read_text()
        source = (PRIVATE / 'DigimonVenomNXTPlayerState.cpp').read_text()
        self.assertNotIn('DOREPLIFETIME_CONDITION(ADigimonVenomNXTPlayerState, Profile,', source)
        self.assertNotIn('ReplicatedUsing=OnRep_Profile, BlueprintReadOnly, Category="Digimon Venom NXT|Profile"', header)
        self.assertIn('DOREPLIFETIME(ADigimonVenomNXTPlayerState, PublicSnapshot)', source)
        self.assertIn('ScanPolicy, COND_OwnerOnly', source)

    def test_login_hud_and_gameplay_have_readiness_barriers(self):
        controller = (PRIVATE / 'DigimonVenomNXTPlayerController.cpp').read_text()
        mode = (PRIVATE / 'DigimonVenomNXTGameMode.cpp').read_text()
        sync = (PRIVATE / 'DigimonVenomNXTPlayerControllerProfileSync.cpp').read_text()
        self.assertIn('TickProfileSynchronization();\n    if (!IsLocalController() || !IsOwnerProfileReady()) return;', controller)
        self.assertIn('if (GameHUDWidget || !IsLocalController() || !IsOwnerProfileReady()) return;', controller)
        self.assertIn('!DigimonController->IsOwnerProfileReady()', mode)
        auth = mode.split('bool ADigimonVenomNXTGameMode::AuthenticatePlayer', 1)[1].split('void ADigimonVenomNXTGameMode::FinishAuthenticatedPlayerLogin', 1)[0]
        self.assertNotIn('HandleStartingNewPlayer(Controller)', auth)
        self.assertIn('if (!PS) return;', sync)
        self.assertIn('AccountId != ExpectedProfileAccountId', sync)
        self.assertIn('ProfileSendWindow.Complete()', sync)
        self.assertIn('ServerCompleteProfileSnapshot(IncomingProfileTransferId, IncomingProfileRevision, true);', sync)

    def test_staging_is_atomic_and_revision_fenced(self):
        codec = (PRIVATE / 'DigimonVenomNXTProfileSnapshot.cpp').read_text()
        sync = (PRIVATE / 'DigimonVenomNXTPlayerControllerProfileSync.cpp').read_text()
        self.assertLess(codec.index('Checksum(JsonData.GetData(), JsonBytes) != Checksum'), codec.index('OutProfile = MoveTemp(Candidate)'))
        self.assertIn('PendingOwnerProfile.CommerceRevision, PS->Profile.CommerceRevision', sync)
        self.assertIn('PendingOwnerProfile.DigiLabRecoveryRevision, PS->Profile.DigiLabRecoveryRevision', sync)
        self.assertIn('TransferId != IncomingProfileTransferId', sync)
        self.assertNotIn('SaveProfile(', sync)
        self.assertNotIn('SavePlayer(', sync)

    def test_save_targets_initialized_authoritative_owner(self):
        source = (PRIVATE / 'DigimonVenomNXTGameMode.cpp').read_text()
        save = source.split('bool ADigimonVenomNXTGameMode::SavePlayer', 1)[1].split('void ADigimonVenomNXTGameMode::', 1)[0]
        self.assertIn('!HasAuthority()', save)
        self.assertIn('!PlayerState->HasInitializedServerProfile()', save)
        self.assertIn('Controller->GetPlayerState<ADigimonVenomNXTPlayerState>() != PlayerState', save)
        self.assertIn('Controller->HasCommittedLogout()', save)
        self.assertIn('bAlreadySaved', source)
        session = (PRIVATE / 'DigimonVenomNXTPlayerControllerSession.cpp').read_text()
        self.assertLess(session.index('if (!Mode->SavePlayer(Profile, false))'), session.index('SessionController->bLogoutServerCommitted = true'))

    def test_invalid_storage_fails_closed(self):
        source = (PRIVATE / 'DigimonVenomNXTProfileSubsystem.cpp').read_text()
        self.assertIn('DigimonVenomNXTProfileValidation::HasRequiredJsonFields(Json)', source)
        self.assertIn('Profile round-trip verification failed; previous saved profile retained.', source)
        self.assertIn('DigimonVenomNXTProfileValidation::Validate(Candidate, Candidate.AccountId, Error)', source)
        self.assertIn('Existing profile could not be read. File retained; no replacement profile created.', source)

    def test_authentication_diagnostics_are_not_inferred_from_an_empty_name(self):
        mode = (PRIVATE / 'DigimonVenomNXTGameMode.cpp').read_text()
        activity = (PRIVATE / 'DigimonVenomNXTServerActivity.h').read_text()
        self.assertNotIn('TEXT("Unauthenticated connection")', activity)
        self.assertIn('TEXT("Pending account authentication")', activity)
        self.assertIn('TEXT("Credentials accepted")', mode)
        self.assertIn('TEXT("Login profile load failed")', mode)
        self.assertIn('TEXT("Authentication rejected")', mode)
        self.assertIn('ExistingController->IsAccountAuthenticated() && !ExistingController->HasCommittedLogout()', mode)

    def test_saving_policy_is_explicit_and_not_a_backup_workaround(self):
        mode = (PRIVATE / 'DigimonVenomNXTGameMode.cpp').read_text()
        self.assertIn('bEnableGlobalAutosaves', mode)
        self.assertIn('SavePlayer(NPS, false)', mode)
        self.assertIn('Profiles->RetainProfile(PlayerState->Profile)', mode)
        self.assertIn('Console->SaveAll(Error)', (PRIVATE / 'DigimonVenomNXTPlayerControllerSession.cpp').read_text())
        self.assertIn('bool bEnableGlobalAutosaves = false;', (PUBLIC / 'DigimonVenomNXTSettings.h').read_text())
        self.assertNotIn('RestoreBackup', (PRIVATE / 'DigimonVenomNXTPlayerControllerProfileSync.cpp').read_text())


    def test_loading_widget_exists_before_slate_construction(self):
        widget = (PRIVATE / 'DigimonVenomNXTProfileSyncWidget.cpp').read_text()
        initialized = widget.split('::NativeOnInitialized()', 1)[1].split('::NativeConstruct()', 1)[0]
        self.assertIn('BuildNativeUI();', initialized)
        self.assertIn('if (StatusText) return;', widget)
        self.assertIn('RETURN TO LOGIN', widget)
        self.assertNotIn('SAVE AND RETURN TO LOGIN', widget)
        self.assertIn('confirm your session handoff', widget)


if __name__ == '__main__':
    unittest.main(verbosity=2)
