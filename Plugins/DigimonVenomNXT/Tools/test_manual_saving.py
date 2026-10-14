#!/usr/bin/env python3
"""Compile actual retention methods against portable doubles; audit every save gate.

This does not execute Unreal serialization, auth RPCs, disk journals or networking.
Those engine tests are provided in DigimonVenomNXTManualPersistenceTests.cpp.
"""
from pathlib import Path
import os
import shlex
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[1]
PUBLIC=ROOT/'Source/DigimonVenomNXTRuntime/Public'
PRIVATE=ROOT/'Source/DigimonVenomNXTRuntime/Private'

def method(source, name):
    at=source.index(name)
    start=source.rfind('\n',0,at)+1
    opening=source.index('{',at)
    depth=1; i=opening+1
    # Source bodies under test contain balanced braces in comments/strings too.
    while depth:
        depth+=(source[i]=='{')-(source[i]=='}'); i+=1
    return source[start:i]

class ManualSavingTests(unittest.TestCase):
    def program(self):
        source=(PRIVATE/'DigimonVenomNXTProfileSubsystem.cpp').read_text()
        names=('AutomaticSavingEnabled','RetainProfileLocked','RetainProfile','CheckCommerceFenceLocked','SaveProfile','LoadProfile')
        methods='\n\n'.join(method(source,'UDigimonVenomNXTProfileSubsystem::'+name+'(') for name in names)
        return (ROOT/'Tools/test_manual_save_retention.cpp.in').read_text().replace('// PRODUCTION_METHODS',methods)
    def compile_run(self,code):
        with tempfile.TemporaryDirectory(prefix='digimon-retention-') as temp:
            src=Path(temp)/'test.cpp'; exe=Path(temp)/'test';src.write_text(code)
            cmd=shlex.split(os.environ.get('CXX','g++'))+['-std=c++17','-Wall','-Wextra','-Werror','-O2','-I'+str(PUBLIC),str(src),'-o',str(exe)]
            result=subprocess.run(cmd,capture_output=True,text=True,timeout=45)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            return subprocess.run([str(exe)],capture_output=True,text=True,timeout=10)
    def test_actual_retention_save_load_and_revision_methods(self):
        result=self.compile_run(self.program())
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        print(result.stdout.strip())
    def test_negative_control_detects_unconditional_automatic_writes(self):
        code=self.program().replace('if (!AutomaticSavingEnabled())','if (false)',1)
        result=self.compile_run(code)
        self.assertNotEqual(result.returncode,0)
        self.assertIn('manual mode must not serialize or write',result.stderr)
    def test_negative_control_detects_missing_session_handoff(self):
        result=self.compile_run(self.program().replace('SessionProfiles.Add(Profile.AccountId, Profile);','',1))
        self.assertNotEqual(result.returncode,0)
    def test_default_and_config_are_disabled(self):
        self.assertIn('bool bEnableGlobalAutosaves = false;', (PUBLIC/'DigimonVenomNXTSettings.h').read_text())
        self.assertIn('bEnableGlobalAutosaves=False', (ROOT/'Config/DefaultGame.ini').read_text())
    def test_rival_and_ranked_gates_precede_serialization(self):
        for filename,cls in [('DigimonVenomNXTAIRivalSubsystem.cpp','UDigimonVenomNXTAIRivalSubsystem'),('DigimonVenomNXTRankedSubsystem.cpp','UDigimonVenomNXTRankedSubsystem')]:
            source=(PRIVATE/filename).read_text();save=method(source,cls+'::Save(')
            self.assertIn('!bExplicitAdminSave && !GetDefault<UDigimonVenomNXTSettings>()->bEnableGlobalAutosaves',save)
            writer=save.index('FString Text;') if 'Rival' in filename else save.index('FDigimonRankedSaveData Persisted')
            self.assertLess(save.index('!bExplicitAdminSave'),writer)
            host=method(source,cls+'::SaveForHostConsole(')
            self.assertLess(host.index('CanAccess('),host.index('Save(true)'))
    def test_ordinary_logout_has_no_force_save(self):
        mode=(PRIVATE/'DigimonVenomNXTGameMode.cpp').read_text();logout=method(mode,'ADigimonVenomNXTGameMode::Logout(')
        self.assertIn('SavePlayer(NPS, false)',logout)
        self.assertNotIn('SaveForHostConsole',logout)
        session=(PRIVATE/'DigimonVenomNXTPlayerControllerSession.cpp').read_text()
        logout=method(session,'ADigimonVenomNXTPlayerController::ServerRequestLogout_Implementation(')
        self.assertIn('Mode->SavePlayer(Profile, false)',logout)
        self.assertRegex(logout,r'if \(bHost\)\s*\{\s*if \(!Console->SaveAll\(Error\)\)')
        self.assertLess(logout.index('Console->SaveAll(Error)'),logout.index('SessionController->bLogoutServerCommitted = true'))
        rpc=method((PRIVATE/'DigimonVenomNXTPlayerController.cpp').read_text(),'ADigimonVenomNXTPlayerController::ServerRequestSave_Implementation(')
        self.assertIn('SavePlayer(GetPlayerState<ADigimonVenomNXTPlayerState>(), false)',rpc)
    def test_admin_checkpoint_includes_offline_profiles_and_ledgers(self):
        source=(PRIVATE/'DigimonVenomNXTProfileSubsystem.cpp').read_text()
        flush=method(source,'UDigimonVenomNXTProfileSubsystem::FlushDeferredLocked(')
        self.assertIn('for (const FString& AccountId : DirtySessionProfiles)',flush)
        self.assertIn('SetNumberField(TEXT("version"), 2)',flush)
        self.assertLess(flush.index('ApplyCommerceJournalLocked(Journal)'),flush.index('DirtySessionProfiles.Reset()'))
        saveall=method((PRIVATE/'DigimonVenomNXTServerConsoleCommands.cpp').read_text(),'UDigimonVenomNXTServerConsoleSubsystem::SaveAll(')
        for expr in ('Profiles->SaveForHostConsole','Ranked->SaveForHostConsole','Rivals->SaveForHostConsole','Social->SaveForHostConsole'):
            self.assertIn(expr,saveall)
        self.assertLess(saveall.index('!CanAccess('),saveall.index('Profiles->SaveForHostConsole'))
    def test_commerce_stages_every_participant_before_any_manual_disk_write(self):
        body=method((PRIVATE/'DigimonVenomNXTProfileSubsystem.cpp').read_text(),'UDigimonVenomNXTProfileSubsystem::CommitCommerce(')
        start=body.index('if (!AutomaticSavingEnabled())')
        end=body.index('Accounts.Reset();',start)
        branch=body[start:end]
        self.assertIn('for (const FDigimonPlayerProfile& Candidate : Candidates) RetainProfileLocked(Candidate);',branch)
        self.assertIn('SessionMarketJson = MarketJson;',branch)
        self.assertNotIn('WriteSeasonArchive',branch)
        self.assertNotIn('WriteCommerceAtomic',branch)
    def test_unsaved_season_history_outlives_bounded_profile_window(self):
        source=(PRIVATE/'DigimonVenomNXTProfileSubsystem.cpp').read_text()
        self.assertIn('DeferredSeasonRecords.Add(Key, Record)',source)
        archive=method(source,'UDigimonVenomNXTProfileSubsystem::LoadSeasonArchive(')
        self.assertIn('DeferredSeasonRecords.Find(Key)',archive)
        flush=method(source,'UDigimonVenomNXTProfileSubsystem::FlushDeferredLocked(')
        self.assertIn('WriteSeasonArchive(WithHistory)',flush)
        self.assertIn('UStructToJsonObjectString(Candidate, Json)',flush)

if __name__=='__main__': unittest.main(verbosity=2)
