#!/usr/bin/env python3
"""Focused source contracts, not an Unreal build or live multiplayer security test."""
from __future__ import annotations
import argparse
import re
from functools import lru_cache
from pathlib import Path
from validate_compile_surface import mask_cpp, closing_brace
ROOT = Path(__file__).resolve().parents[1]


@lru_cache(maxsize=32)
def masked(source: str):
    return mask_cpp(source)


def function_body(source: str, name: str) -> tuple[str, str]:
    code, errors = masked(source)
    if errors:
        raise ValueError(f'Malformed source: {errors[:3]}')
    match = re.search(r'\b' + re.escape(name) + r'\s*\([^;{}]*\)\s*(?:const\s*)?\{', code)
    if not match:
        raise ValueError(f'Missing function definition: {name}')
    begin = code.index('{', match.start())
    end = closing_brace(code, begin)
    return source[begin + 1:end], code[begin + 1:end]


def enum_members(source: str) -> dict[str, set[str]]:
    """Read enum definitions, excluding declarations and nested metadata commas."""
    code, errors = mask_cpp(source)
    if errors:
        raise ValueError(f'Malformed source: {errors[:3]}')
    result = {}
    # A forward declaration ends at ';'; it must never capture the next class
    # body and replace enumerators read from the actual defining header.
    for match in re.finditer(r'\benum\s+class\s+(EDigimon\w+)\s*(?::[^;{}]+)?\s*\{', code):
        opening = match.end() - 1
        values = code[opening + 1:closing_brace(code, opening)]
        members, begin, depth = set(), 0, 0
        for index, char in enumerate(values + ','):
            if char in '([{':
                depth += 1
            elif char in ')]}':
                depth -= 1
            elif char == ',' and depth == 0:
                member = re.match(r'\s*([A-Za-z_]\w*)\b', values[begin:index])
                if member:
                    members.add(member.group(1))
                begin = index + 1
        result[match.group(1)] = members
    return result


def validate(root: Path = ROOT) -> tuple[list[tuple[str, str]], list[tuple[str, str]]]:
    passed, failed = [], []
    src = root / 'Source/DigimonVenomNXTRuntime'
    def read(path): return (src / path).read_text(encoding='utf-8')
    def check(name, valid, detail): (passed if valid else failed).append((name, detail))
    def body(source, name): return function_body(source, name)[1]
    try:
        backend = read('Private/DigimonVenomNXTServerConsoleSubsystem.cpp')
        header = read('Public/DigimonVenomNXTServerConsoleSubsystem.h')
        controller = read('Private/DigimonVenomNXTPlayerController.cpp')
        instance = read('Private/DigimonVenomNXTGameInstance.cpp')
        activity = read('Private/DigimonVenomNXTServerActivity.h')
        player = read('Private/DigimonVenomNXTPlayerState.cpp')
        session = read('Private/DigimonVenomNXTPlayerControllerSession.cpp')
        widget = read('Private/DigimonVenomNXTServerConsoleWidget.cpp')
        hcode, _ = mask_cpp(header)
        check('No reflected command transport', 'UFUNCTION' not in hcode and not re.search(r'UPROPERTY\s*\([^)]*Replicated', hcode), 'Console commands/output have no Blueprint, RPC or replicated entry point.')
        callers, armers = [], []
        for path in src.rglob('*.cpp'):
            code, _ = mask_cpp(path.read_text(encoding='utf-8'))
            if re.search(r'(?:->|\.)\s*Execute(?:Sensitive)?Command\s*\(', code): callers.append(path.name)
            if re.search(r'(?:->|\.)\s*ArmHostSession\s*\(', code): armers.append(path.name)
        check('Local UI is the only command caller', set(callers) == {'DigimonVenomNXTServerConsoleWidget.cpp'}, str(sorted(callers)))
        check('One host capability arming path', set(armers) == {'DigimonVenomNXTGameInstance.cpp'}, str(sorted(armers)))
        gate = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::CanAccess')
        names = ['Authorized', 'IsHostWorld', 'GetWorld', 'GetGameInstance', 'HasAuthority', 'IsLocalController', 'GetLocalPlayer', 'HostLocalPlayer', 'GetFirstGamePlayer', 'IsAccountAuthenticated', 'IsLoggedIn', 'AccountId', 'HostAccountId']
        check('Host gate checks provenance and identity', all(x in gate for x in names), 'Authority alone does not grant console access.')
        for name in ['ReadEntries', 'GetStatus', 'GetCommandHelp']:
            code = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::' + name)
            check('Gated console ' + name, bool(re.search(r'if\s*\(\s*!CanAccess\(Requester\)\s*\)\s*return false', code)), 'Each read rechecks the requesting controller.')
        commit = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::CommitProfile')
        ordered = [commit.find(x) for x in ['RequireMutable(', 'DigimonVenomNXTServerConsoleCore::Commit(', 'SaveProfile(Value)', 'Live->Profile =', 'Live->MarkProfileChanged()']]
        check('Save before profile publication', all(x >= 0 for x in ordered) and ordered == sorted(ordered), 'Actual portable commit policy receives durable-write and live-publication callbacks after the battle guard.')
        mutable = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::RequireMutable')
        check('Live and saved battles lock edits', all(x in mutable for x in ['HasActiveBattle', 'CurrentBattle', 'BattleCheckpointJson', 'HasPendingBattle']), 'Finished battle views and suspended campaign/Season checkpoints stay protected.')
        resolving = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::ResolveTarget')
        guard = re.search(r'if\s*\(\s*!PC->IsAccountAuthenticated\(\)\s*\|\|\s*PC->IsLogoutPending\(\)\s*\)\s*\{[^{}]*return false;', resolving)
        identity = resolving.find('PS->Profile.Username.Equals(Query')
        check('Disconnecting identities cannot fall back to offline edits', bool(guard) and 0 <= identity < guard.start() < resolving.find('Profiles->LoadProfile('), 'A connected account signing out is rejected before loading its older saved profile.')
        check('Profile publication rejects closing sessions', '!PC->IsAccountAuthenticated() || PC->IsLogoutPending()' in mutable, 'The final commit gate also blocks a live target whose session is closing.')
        record = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::RecordActivity')
        check('Bounded sanitized activity buffer', all(x in record for x in ['IsHostWorld', 'Clean', 'Entries.Num()', 'Entries.RemoveAt']), 'Records are sanitized and retained within a fixed bound on the host.')
        revoke = body(backend, 'UDigimonVenomNXTServerConsoleSubsystem::DisarmHostSession')
        check('Revocation erases private output', all(x in revoke for x in ['HostAccountId.Reset', 'HostLocalPlayer.Reset', 'Entries.Reset', 'PendingToken.Reset']), 'Sessions cannot inherit capability, output or confirmations.')
        host = body(instance, 'UDigimonVenomNXTGameInstance::HostPublicWorldForGameInstance')
        ordered = [host.find(x) for x in ['AdminPassword !=', 'AuthenticateLocalHost', 'ArmHostSession', 'UGameplayStatics::OpenLevel']]
        check('Local authentication precedes arming', all(x >= 0 for x in ordered) and ordered == sorted(ordered), 'Local account/password checks run before listen travel.')
        chat = body(controller, 'ADigimonVenomNXTPlayerController::ServerSendLocalChat_Implementation')
        check('Chat cannot dispatch commands', not re.search(r'Execute(?:Sensitive)?Command|RunCommand|ConsoleCommand', chat), 'Player slash text remains ordinary chat.')
        gameplay = body(activity, 'AllowGameplay')
        check('Gameplay gate closes logout race', all(x in gameplay for x in ['HasAuthority', 'NM_Client', 'IsAccountAuthenticated', 'IsLogoutPending', 'IsAccountJailed']), 'Queued player RPCs cannot change a profile after final save approval.')
        logout = body(session, 'ADigimonVenomNXTPlayerController::ServerRequestLogout_Implementation')
        check('Logout saves before disconnect', logout.find('SavePlayer(') >= 0 and logout.find('SavePlayer(') < logout.find('SetAccountAuthenticatedServer(false)') < logout.find('ClientHostSessionClosed('), 'Save failures do not disconnect players.')
        ack = body(session, 'ADigimonVenomNXTPlayerController::ClientLogoutResult_Implementation')
        check('Logout acknowledgement is request bound', 'RequestId != PendingLogoutRequestId' in ack and 'CompleteAcknowledgedLogout' in ack, 'Only a matching successful save acknowledgement initiates travel.')
        access = body(widget, 'UDigimonVenomNXTServerConsoleWidget::CheckAccess')
        check('Denied UI purges cached output', all(x in access for x in ['CanAccess(GetOwningPlayer())', 'ClearPrivateState', 'Collapsed']), 'Revoked host access collapses and clears the private widget.')
        snapshot = body(player, 'ADigimonVenomNXTPlayerState::RefreshPublicSnapshot')
        check('Equipped titles publish in public identity', 'PublicSnapshot.EquippedTitle' in snapshot and 'Profile.EquippedTitle' in snapshot, 'Host-assigned titles reach the nameplate snapshot.')
        plate = body(read('Private/DigimonVenomNXTNameplateWidget.cpp'), 'UDigimonVenomNXTNameplateWidget::SetIdentity')
        check('Title rendering is bounded', 'Title.Left(32)' in plate and 'CleanTitle' in plate, 'Native plain-text titles are limited to 32 characters.')
        command_source = read('Private/DigimonVenomNXTServerConsoleCommands.cpp')
        for name in ['ExecuteCommand', 'ExecuteSensitiveCommand', 'RunCommand']:
            code = body(command_source, 'UDigimonVenomNXTServerConsoleSubsystem::' + name)
            check('Gated native ' + name, 'CanAccess(Requester)' in code and code.find('CanAccess(Requester)') < code.find('return false;'), 'Each execution path checks the live host capability before dispatch.')
        publish = body(read('Private/DigimonVenomNXTBattleActor.cpp'), 'ADigimonVenomNXTBattleActor::PublishState')
        check('Battle activity follows transaction fence', 0 <= publish.find('bSeasonCommandTransaction') < publish.find('return;') < publish.find('DigimonVenomNXTServerActivity::RecordFor'), 'Uncommitted or rolled-back decisions never enter the activity stream.')
        check('Battle result activity is deduplicated', 'LastConsolePresentationSerial' in publish and 'bConsoleResultLogged' in publish, 'Repeated publication does not emit duplicate resolved actions/results.')
        mode = read('Private/DigimonVenomNXTGameMode.cpp')
        auth_raw, auth = function_body(mode, 'ADigimonVenomNXTGameMode::AuthenticatePlayer')
        check('Ban lookup follows account verification', 0 <= auth.find('AuthenticateServerCredentials') < auth.find('IsAccountBanned'), 'Arbitrary attempted usernames cannot impersonate account moderation identity.')
        auth_records = re.findall(r'DigimonVenomNXTServerActivity::Record(?:For)?\s*\([^;]*;', mask_cpp(auth_raw)[0])
        check('Authentication activity excludes credentials', bool(auth_records) and all(not re.search(r'\b(?:Password|AdminPassword|PendingPassword|Username|Error|OutError)\b', entry) for entry in auth_records), 'Account activity records do not contain credential input or raw authentication errors.')
        for match in re.finditer(r'ADigimonVenomNXTPlayerState::(Server\w+_Implementation)\s*\(', mask_cpp(player)[0]):
            name = match.group(1)
            rpc = body(player, 'ADigimonVenomNXTPlayerState::' + name)
            guarded_farm_delegate = (name == 'ServerUseDigiMeat_Implementation' and 'ServerFeedFarmResident_Implementation(' in rpc and 'AllowGameplay(this' in body(player, 'ADigimonVenomNXTPlayerState::ServerFeedFarmResident_Implementation'))
            check('Player-state moderation gate ' + name, 'AllowGameplay(this' in rpc or 'ProcessDigiLabHeal(' in rpc or guarded_farm_delegate, 'Player mutations use the shared authority/authentication/detention gate, directly or through the checked recovery/farm handler.')
        known_enums = {}
        for path in src.glob('Public/*.h'):
            known_enums.update(enum_members(path.read_text(encoding='utf-8')))
        unresolved = []
        for path in list(src.glob('Private/DigimonVenomNXTServerConsole*.cpp')) + [src / 'Private/DigimonVenomNXTPlayerControllerSession.cpp']:
            code, _ = mask_cpp(path.read_text(encoding='utf-8'))
            for enum, member in re.findall(r'\b(EDigimon\w+)::(\w+)', code):
                if enum not in known_enums or member not in known_enums[enum]: unresolved.append(path.name + ':' + enum + '::' + member)
        check('New console enum members resolve', not unresolved, ', '.join(sorted(set(unresolved))) or 'All referenced Digimon enumerators exist in the shipped headers.')
        check('Rival saves use world subsystem lifetime', 'GetGameInstance()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>' not in command_source + session and 'GetWorld()->GetSubsystem<UDigimonVenomNXTAIRivalSubsystem>' in command_source + session, 'World subsystem lookup prevents the GameInstance template static assertion.')
        all_native = '\n'.join(mask_cpp(p.read_text(encoding='utf-8'))[0] for p in src.glob('Private/DigimonVenomNXTServerConsole*.cpp'))
        check('No generic command evaluator', not re.search(r'\b(?:ProcessConsoleExec|ExecuteConsoleCommand|system|popen|CreateProc)\s*\(', all_native), 'Console actions cannot escape to a shell or generic engine evaluator.')
    except (OSError, ValueError) as error:
        failed.append(('Console integration source available', str(error)))
    return passed, failed


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args()
    passed, failed = validate(args.root)
    for name, detail in passed: print(f'PASS {name}: {detail}')
    for name, detail in failed: print(f'FAIL {name}: {detail}')
    print(f'Console integration source checks: {len(passed)} passed, {len(failed)} failed. Unreal build/live multiplayer not run.')
    return bool(failed)


if __name__ == '__main__':
    raise SystemExit(main())
