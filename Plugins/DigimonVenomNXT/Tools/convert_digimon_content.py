#!/usr/bin/env python3
"""Convert the supplied Digimon Venom NXT source into native Unreal import data.

Usage: python convert_digimon_content.py --source /path/to/DigimonVenomNXT
Requires Pillow, numpy and ffmpeg. PNG files are copied byte-for-byte. Audio
streams are decoded to PCM16 WAV without changing sample rate or channel count.
GameEngine preparation is deliberately executed before exporting balance/routes.
"""
from __future__ import annotations

import argparse
import base64
import hashlib
import json
import re
import shutil
import subprocess
import sys
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import numpy as np
from PIL import Image


MOUNT = '/DigimonVenomNXT/Generated'
FAMILIES = {'normal': 'Normal', 'paradox': 'Paradox', 'shiny': 'Shiny', 'firewall': 'Firewall'}
DIRECTIONS = {'down': 'Down', 'down_left': 'DownLeft', 'left': 'Left', 'up_left': 'UpLeft',
              'up': 'Up', 'up_right': 'UpRight', 'right': 'Right', 'down_right': 'DownRight'}
UI_ALIASES = {
    'T_DVN_Shopkeeper': 'assets/ui/extracted/shopkeeper.png',
    'T_DVN_DigiLab': 'assets/ui/dawn/m_labo_bg.png',
    'T_DVN_DigiFarmLevel': 'assets/ui/digifarm/level.png',
    'T_DVN_HPCapsule': 'assets/ui/extracted/hp_max_capsule.png',
    'T_DVN_SPCapsule': 'assets/ui/extracted/mp_max_capsule.png',
    'T_DVN_DigiMeat': 'assets/ui/digifarm/digimeat.png',
    'T_DVN_TitleCoronamon': 'assets/ui/extracted/coronamon_title.png',
    'T_DVN_TitleLunamon': 'assets/ui/extracted/lunamon_title.png',
    'T_DVN_TamerBoy': 'assets/ui/extracted/dawn_tamer_boy.png',
    'T_DVN_TamerGirl': 'assets/ui/extracted/dawn_tamer_girl.png',
}
UI_ALIASES.update({f'T_DVN_BattleImpact_{index:02d}': f'assets/effects/dawn_002/{index:03d}.png'
                   for index in range(15)})


def digest(path: Path, algorithm: str = 'sha256') -> str:
    h = hashlib.new(algorithm)
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def safe(value: str) -> str:
    return re.sub('[^A-Za-z0-9_]', '_', value)


def object_path(package: str) -> str:
    return package + '.' + package.rsplit('/', 1)[-1]


def dump(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, separators=(',', ':')) + '\n', encoding='utf-8')


def load(path: Path):
    return json.loads(path.read_text(encoding='utf-8'))


def stats(source: dict) -> dict:
    return dict(zip(('maxHP', 'maxSP', 'attack', 'defense', 'spirit', 'speed'),
                    (int(source[k]) for k in ('hp', 'sp', 'atk', 'def', 'int', 'spd'))))


def verify_export(plugin: Path) -> dict:
    """Verify the shipped payload independently of the original source tree."""
    resources = plugin / 'Resources'
    manifest = load(resources / 'GameData/import_manifest.json')
    destinations = {}
    for group in ('textures', 'sprites', 'animations', 'audio', 'partnerSets', 'tamerSets'):
        for row in manifest[group]:
            asset = row['asset']
            if asset in destinations:
                raise ValueError('Duplicate import destination: ' + asset)
            if not asset.startswith(MOUNT + '/') or '.' in asset:
                raise ValueError('Invalid native asset package: ' + asset)
            destinations[asset] = group
    for row in manifest['textures'] + manifest['audio']:
        path = (resources / row['source']).resolve()
        if not path.is_relative_to(resources.resolve()) or not path.is_file():
            raise ValueError('Missing or unsafe source path: ' + row['source'])
        if digest(path, 'sha1') != row['sha1']:
            raise ValueError('Import source hash mismatch: ' + row['source'])
    for row in manifest['sprites']:
        if destinations.get(row['texture']) != 'textures':
            raise ValueError('Unresolved sprite texture: ' + row['asset'])
        if min(row['rect'][2:]) <= 0:
            raise ValueError('Empty sprite geometry: ' + row['asset'])
    for row in manifest['animations']:
        if not row['frames']:
            raise ValueError('Empty animation: ' + row['asset'])
        for frame in row['frames']:
            if destinations.get(frame['sprite']) != 'sprites' or frame['seconds'] <= 0:
                raise ValueError('Invalid animation frame: ' + row['asset'])
    for row in manifest['partnerSets']:
        if any(destinations.get(row[key]) != 'animations' for key in ('idle', 'walkLeft', 'walkRight', 'attack')):
            raise ValueError('Invalid partner animation set: ' + row['asset'])
        for key in ('idleLeft', 'attackLeft'):
            if row.get(key) and destinations.get(row[key]) != 'animations':
                raise ValueError('Invalid left-facing animation: ' + row['asset'])
        if bool(row.get('hasAuthoredLeftFrames')) != bool(row.get('authoredLeftSprites')):
            raise ValueError('Authored-left metadata mismatch: ' + row['asset'])
        if any(destinations.get(path) != 'sprites' for path in row.get('authoredLeftSprites', [])):
            raise ValueError('Unknown authored-left sprite: ' + row['asset'])
        for body in row.get('frameBodies', []):
            if destinations.get(body['sprite']) != 'sprites' or min(body['bodySize']) <= 0:
                raise ValueError('Invalid native frame body: ' + row['asset'])
    for row in manifest['tamerSets']:
        if set(row['directions']) != set(DIRECTIONS.values()):
            raise ValueError('Incomplete tamer facings: ' + row['id'])
        if any(destinations.get(path) != 'animations' for path in row['directions'].values()):
            raise ValueError('Invalid tamer animation set: ' + row['id'])
    species = {row['speciesId']: row for row in load(resources / 'DigimonSpecies.json')['species']}
    for row in species.values():
        if any(route['targetSpeciesId'] not in species for route in row['evolutions']):
            raise ValueError('Unknown evolution target: ' + row['speciesId'])
    maps = load(resources / 'DigimonMaps.json')['maps']
    if [row['mapId'] for row in maps] != list(range(1, len(maps) + 1)):
        raise ValueError('Public map IDs are not stable contiguous catalog order.')
    for row in maps:
        for kind in ('ground', 'collision'):
            source = resources / row[kind + 'Source']
            if digest(source) != row[kind + 'SourceSha256']:
                raise ValueError('Map source hash mismatch: ' + str(row['mapId']))
        width, height = row['sourceWidth'], row['sourceHeight']
        bits = base64.b64decode(row['walkGridBits'], validate=True)
        if len(bits) != (width * height + 7) // 8:
            raise ValueError('Incomplete map bitmask: ' + str(row['mapId']))
        with Image.open(resources / row['collisionSource']) as image:
            source_mask = np.asarray(image.convert('L')) >= 128
        # CollisionCore::CellWalkable reads 1 << (7 - Index % 8): MSB first.
        decoded = np.unpackbits(np.frombuffer(bits, dtype=np.uint8), bitorder='big')[:width*height].reshape(height, width)
        if not np.array_equal(decoded, source_mask):
            raise ValueError('Map bitmask differs from source: ' + str(row['mapId']))
        x = round(row['safeSpawnU'] * width)
        y = round(row['safeSpawnV'] * height)
        if not source_mask[y, x]:
            raise ValueError('Map spawn is not on source walkable floor: ' + str(row['mapId']))
        if destinations.get(row['importedTexture']) != 'textures':
            raise ValueError('Map ground texture is not imported: ' + str(row['mapId']))
        for family in ('wildSpecies', 'paradoxSpecies', 'shinySpecies', 'firewallSpecies'):
            if any(identity not in species for identity in row[family]):
                raise ValueError('Unknown encounter species: ' + str(row['mapId']))
    # Independently cover every asset path, including fallback/front poses that
    # are not used by the source client's normal idle/walk/attack state machine.
    catalog = load(resources / 'GameData/prepared_catalog.json')
    required_paths = set()
    def collect_paths(value):
        if isinstance(value, dict):
            for key, child in value.items():
                collect_paths(key)
                collect_paths(child)
        elif isinstance(value, list):
            for child in value:
                collect_paths(child)
        elif isinstance(value, str) and value.startswith('assets/'):
            required_paths.add(value)
    collect_paths(catalog)
    collect_paths(load(resources / 'GameData/ui.json'))
    collect_paths(load(resources / 'GameData/audio.json'))
    imported_sources = {row['source'].removeprefix('RawAssets/') for row in manifest['textures']}
    imported_sources.update(row['originalSource'] for row in manifest['audio'])
    collision_sources = {row['collisionSource'].removeprefix('RawAssets/') for row in maps}
    for source in required_paths:
        if not (resources / 'RawAssets' / source).is_file():
            raise ValueError('Missing required catalog asset: ' + source)
        if Path(source).suffix.lower() in ('.png', '.ogg', '.wav') and source not in imported_sources | collision_sources:
            raise ValueError('Catalog media has no native import registration: ' + source)
    result = {'schemaVersion': 1, 'passed': True, 'checks': [
        'All native import destinations are unique and confined to the plugin mount.',
        'Every imported texture/audio source exists and matches its recorded SHA1.',
        'All sprite, flipbook, partner and tamer references resolve.',
        'All 8 directions are present for every tamer.',
        'Every evolution and encounter species exists in the canonical registry.',
        'Every source map/clip mask SHA256 matches.',
        'All packed masks exactly reproduce native source pixels, with verified safe spawns.'
    ], 'counts': dict(Counter(destinations.values())), 'maps': len(maps), 'baseSpecies': len(species),
        'requiredCatalogAssets': len(required_paths), 'unregisteredCatalogMedia': [],
        'unrealBuildExecuted': False}
    dump(resources / 'GameData/validation_report.json', result)
    return result


class Converter:
    def __init__(self, source: Path, plugin: Path):
        self.source, self.plugin = source, plugin
        self.resources = plugin / 'Resources'
        self.raw = self.resources / 'RawAssets'
        self.data = self.resources / 'GameData'
        self.manifest = {'schemaVersion': 1, 'game': 'DigimonVenomNXT', 'textures': [], 'sprites': [],
                         'animations': [], 'audio': [], 'partnerSets': [], 'tamerSets': []}
        self.image_info = {}
        self.texture_assets = {}
        self.sprite_assets = {}
        self.audio_by_source = {}
        self.audio_by_id = {}
        self.references = set()
        self.raw.mkdir(parents=True, exist_ok=True)
        self.data.mkdir(parents=True, exist_ok=True)
        sys.path.insert(0, str(source))
        from venom.common.game import GameEngine
        self.engine = GameEngine(source, seed=0)

    def image(self, source: str):
        if source not in self.image_info:
            path = self.source / source
            if not path.is_file():
                raise FileNotFoundError(f'Catalog image is missing: {source}')
            with Image.open(path) as image:
                width, height = image.size
            self.image_info[source] = (width, height, digest(path, 'sha1'))
        self.references.add(source)
        return self.image_info[source]

    def texture(self, source: str, asset: str | None = None, group: str = 'character') -> str:
        width, height, sha = self.image(source)
        if asset is None:
            key = hashlib.sha1(source.encode()).hexdigest()[:12]
            asset = f'{MOUNT}/SourceTextures/T_{safe(Path(source).stem)[:70]}_{key}'
        previous = self.texture_assets.get(asset)
        if previous and previous != source:
            raise ValueError(f'Conflicting destination texture {asset}')
        if not previous:
            self.manifest['textures'].append({'source': 'RawAssets/' + source, 'asset': asset,
                'width': width, 'height': height, 'filter': 'nearest', 'group': group, 'sha1': sha})
            self.texture_assets[asset] = source
        return asset

    def sprite(self, source: str, asset: str, pivot=None, texture=None, ground=False,
               pixels_per_unit=1.) -> str:
        width, height, _ = self.image(source)
        texture = texture or self.texture(source)
        row = {'asset': asset, 'texture': texture, 'rect': [0, 0, width, height],
               'pivot': list(pivot or [width / 2, height]), 'ground': ground,
               'pixelsPerUnit': pixels_per_unit}
        if asset in self.sprite_assets:
            if self.sprite_assets[asset] != row:
                raise ValueError(f'Conflicting sprite {asset}')
        else:
            self.manifest['sprites'].append(row)
            self.sprite_assets[asset] = row
        return asset

    def partner_anchor(self, species, source):
        width, height, _ = self.image(source)
        geometry = species.get('sprite_geometry', {}).get(source, {})
        body = geometry.get('source_size', [width, height])
        padding = geometry.get('padding', {})
        return [padding.get('left', 0) + body[0] / 2, padding.get('top', 0) + body[1]], body

    def partners(self):
        records = []
        for species in self.engine.species.values():
            base = species['base_id']
            variety = species['variety']
            family = FAMILIES[variety]
            folder = f'{MOUNT}/Digimon/{family}/{base}'
            stem = f'{base}_{family}'
            animations = species['animations']
            for source in species.get('sprites', {}).values():
                for path in source if isinstance(source, list) else [source]:
                    self.texture(path)
            idle = animations.get('idle') or [species['sprites']['idle']]
            walk = animations.get('walk') or idle
            attack = animations.get('attack') or idle
            pose_paths = [idle[0], idle[min(1, len(idle)-1)],
                          species['sprites'].get('walk_right', walk[-1]),
                          species['sprites'].get('walk_left', walk[0]),
                          attack[0], attack[min(1, len(attack)-1)]]
            foot_origins = []
            frame_bodies = []
            for name, source in zip(('IdleA', 'IdleB', 'WalkR', 'WalkL', 'AttackA', 'AttackB'), pose_paths):
                anchor, body = self.partner_anchor(species, source)
                width, height, _ = self.image(source)
                foot_origins.append([anchor[0] / width, anchor[1] / height])
                sprite = self.sprite(source, f'{folder}/SP_{stem}_{name}', anchor)
                frame_bodies.append({'sprite': sprite, 'bodySize': body})
            # A native portrait is the exact idle PNG, not a newly resampled atlas.
            self.texture(idle[0], f'{folder}/T_{stem}_Portrait')
            sets = {'asset': f'{folder}/DA_{stem}_Animation', 'speciesId': base,
                    'sourceSpeciesId': species['id'], 'variant': family,
                    'footOrigins': foot_origins, 'bodySize': self.partner_anchor(species, idle[0])[1],
                    'frameBodies': frame_bodies, 'authoredLeftSprites': []}
            mirrors = species.get('mirrored_frames', {})
            actions = [('Idle', idle), ('WalkLeft', walk), ('WalkRight', walk), ('Attack', attack)]
            if mirrors:
                actions += [('IdleLeft', idle), ('AttackLeft', attack)]
            for action, paths in actions:
                frames = []
                for index, source in enumerate(paths):
                    authored = action.endswith('Left') and source in mirrors
                    if authored:
                        source = mirrors[source]
                    anchor, body = self.partner_anchor(species, source)
                    sp = self.sprite(source, f'{folder}/SP_{stem}_{action}_{index:03d}', anchor)
                    frame_bodies.append({'sprite': sp, 'bodySize': body})
                    if authored:
                        sets['authoredLeftSprites'].append(sp)
                    # venom/client/assets.py::sprite_path uses int(now * 8)
                    # for every source species/motion (no per-species timing).
                    frames.append({'sprite': sp, 'seconds': 0.125})
                asset = f'{folder}/FB_{stem}_{action}'
                self.manifest['animations'].append({'asset': asset, 'frames': frames, 'fps': 120})
                sets[{'Idle': 'idle', 'WalkLeft': 'walkLeft', 'WalkRight': 'walkRight', 'Attack': 'attack',
                      'IdleLeft': 'idleLeft', 'AttackLeft': 'attackLeft'}[action]] = asset
            sets['hasAuthoredLeftFrames'] = bool(sets['authoredLeftSprites'])
            self.manifest['partnerSets'].append(sets)
            # Preserve opposite-facing source art and geometry even where the
            # current runtime uses component mirroring for left/right facing.
            for source in species.get('mirrored_frames', {}).values():
                self.texture(source)
            if variety != 'normal':
                continue
            evolutions = []
            for route in species.get('evolutions', []):
                target = self.engine.species[route['to']]['base_id']
                req = route.get('stats', {})
                evolutions.append({'targetSpeciesId': target, 'requiredLevel': route.get('level', 1),
                    'requiredCAM': route.get('cam', 0), 'requiredABI': route.get('abi', 0),
                    'requiredAttack': req.get('atk', 0), 'requiredDefense': req.get('def', 0),
                    'requiredSpirit': req.get('int', 0), 'requiredSpeed': req.get('spd', 0),
                    'provenance': route.get('provenance', '')})
            record = {'speciesId': base, 'displayName': species['name'],
                'stage': {'in_training': 'In-Training'}.get(species['stage'], species['stage'].title()),
                'affinity': species['type'].title(), 'element': species['attribute'].title(),
                'combatRole': '', 'hasNormalArtwork': True,
                'hasParadoxArtwork': base in self.engine._variants['paradox'],
                'hasShinyArtwork': base in self.engine._variants['shiny'],
                'hasFirewallArtwork': base in self.engine._variants['firewall'],
                'placeholder': False, 'baseStats': stats(species['base_stats']),
                'learnableMoves': ['burst', 'strike'], 'evolutions': evolutions,
                'sourceProvenance': species.get('mechanics_provenance', species.get('provenance', ''))}
            records.append(record)
        dump(self.resources / 'DigimonSpecies.json', {'schemaVersion': 1, 'providedSpecies': len(records),
            'varietyCount': len(self.engine.species), 'species': records})
        dump(self.resources / 'DigimonCombat.json', {'schemaVersion': 1, 'moves': [
            {'moveId': 'burst', 'displayName': 'Data Burst', 'description': 'An elemental special technique.',
             'power': 155, 'spCost': 5, 'spCostPerRank': 1, 'damageClass': 'Special',
             'element': 'Neutral', 'usesSpeciesElement': True},
            {'moveId': 'strike', 'displayName': 'Power Strike', 'description': 'A strong physical attack.',
             'power': 145, 'spCost': 4, 'spCostPerRank': 1, 'damageClass': 'Physical',
             'element': 'Neutral', 'usesSpeciesElement': False}]})

    def tamers(self):
        for tamer in self.engine.tamers.values():
            tid = tamer['id']
            folder = f'{MOUNT}/Tamers/{tid}'
            row = {'id': tid, 'name': tamer['name'], 'description': tamer.get('provenance', ''),
                   'asset': f'{folder}/DA_{tid}_Animation', 'directions': {},
                   'displayScale': tamer.get('display_scale', 2), 'nativeSize': tamer.get('native_size')}
            for direction, title in DIRECTIONS.items():
                paths = tamer['frames'][direction]
                durations = tamer['frame_seconds'][direction]
                frames = []
                for index, (source, seconds) in enumerate(zip(paths, durations)):
                    texture = self.texture(source, f'{folder}/{direction}/T_{tid}_{direction}_{index:02d}')
                    sprite = self.sprite(source, f'{folder}/{direction}/SP_{tid}_{direction}_{index:02d}',
                        tamer.get('anchors', {}).get(direction), texture)
                    frames.append({'sprite': sprite, 'seconds': seconds})
                    if direction == 'down' and index == 0:
                        row['thumbnail'] = texture
                asset = f'{folder}/FB_{tid}_{title}'
                self.manifest['animations'].append({'asset': asset, 'frames': frames, 'fps': 120})
                row['directions'][title] = asset
            self.manifest['tamerSets'].append(row)
        dump(self.data / 'tamers.json', {'schemaVersion': 1, 'tamers': list(self.engine.tamers.values()),
             'sets': self.manifest['tamerSets']})

    def audio(self):
        info = self.engine.catalog['audio']
        ui = load(self.source / 'data/ui_audio.json')
        cache_path = self.raw / 'UnrealAudio/source_hashes.json'
        previous_hashes = load(cache_path) if cache_path.exists() else {}
        tracks = []
        for kind, rows in (('BGM', info['music']), ('SFX', info['effects'])):
            tracks.extend((row['id'], row['path'], kind, bool(row.get('looped', kind == 'BGM')), row)
                          for row in rows)
        for source in sorted(set(ui['screen_tracks'].values()) | set(ui['cues'].values())):
            if any(t[1] == source for t in tracks):
                continue
            kind = 'SFX' if source in ui['cues'].values() else 'BGM'
            tid = ('ui_' if '/interface/' in source else '') + Path(source).stem
            tracks.append((tid, source, kind, kind == 'BGM', {}))
        # Include intro streams separately; they are queued before the catalog loop.
        for tid, source, kind, loop, metadata in list(tracks):
            intro = metadata.get('intro_path') or metadata.get('intro')
            if isinstance(intro, str) and (self.source / intro).exists():
                tracks.append((tid + '_intro', intro, kind, False, {}))

        def convert(track):
            tid, source, kind, loop, metadata = track
            original = self.source / source
            if not original.is_file():
                raise FileNotFoundError(f'Catalog audio missing: {source}')
            output = self.raw / 'UnrealAudio' / kind / (safe(tid) + '.wav')
            output.parent.mkdir(parents=True, exist_ok=True)
            source_hash = digest(original)
            if not output.exists() or previous_hashes.get(tid) != source_hash:
                if original.suffix.lower() == '.wav':
                    shutil.copy2(original, output)
                else:
                    subprocess.run(['ffmpeg', '-nostdin', '-v', 'error', '-i', str(original),
                                    '-c:a', 'pcm_s16le', '-y', str(output)], check=True)
            return {'id': tid, 'originalSource': source, 'source': output.relative_to(self.resources).as_posix(),
                    'asset': f'{MOUNT}/Audio/{kind}/SW_{safe(tid)}', 'loop': loop,
                    'sha1': digest(output, 'sha1'), 'sourceSha256': source_hash,
                    'metadata': metadata}

        with ThreadPoolExecutor(max_workers=6) as pool:
            rows = list(pool.map(convert, tracks))
        dump(cache_path, {row['id']: row['sourceSha256'] for row in rows})
        for row in rows:
            if row['asset'] in self.audio_by_id.values():
                raise ValueError(f'Duplicate audio asset {row["asset"]}')
            self.audio_by_id[row['id']] = row['asset']
            self.audio_by_source[row['originalSource']] = row['asset']
            self.references.add(row['originalSource'])
        self.manifest['audio'] = rows
        scenes = {scene: object_path(self.audio_by_source[source]) for scene, source in ui['screen_tracks'].items()}
        events = {cue: object_path(self.audio_by_source[source]) for cue, source in ui['cues'].items()}
        for scene, tid in info['scene_tracks'].items():
            scenes.setdefault(scene, object_path(self.audio_by_id[tid]))
        for cue, tid in info['event_sounds'].items():
            events.setdefault(cue, object_path(self.audio_by_id[tid]))
        dump(self.data / 'audio.json', {'schemaVersion': 1, 'screenTracks': scenes, 'eventSounds': events,
             'regionTracks': info['region_tracks'], 'tracks': rows})

    def maps(self):
        rows, mapping = [], []
        music = [t for t in self.engine.catalog['audio']['music']
                 if t.get('region_id') not in ('world_ds', 'xros_wars') and not t['id'].startswith(('ds_', 'xros_'))]
        for index, area in enumerate(self.engine.maps.values(), 1):
            region = area.get('region_id', 'dawn')
            width, height, _ = self.image(area['path'])
            if [width, height] != [area['width'], area['height']]:
                raise ValueError(f'Map catalog geometry mismatch: {area["id"]}')
            self.references.add(area['walkable'])
            with Image.open(self.source / area['walkable']) as im:
                if im.size != (width, height):
                    raise ValueError(f'Mask geometry mismatch: {area["id"]}')
                walk = np.asarray(im.convert('L')) >= 128
            x, y = area['spawn']
            if not walk[int(y), int(x)]:
                raise ValueError(f'Unsafe catalog spawn: {area["id"]}')
            bits = np.packbits(walk.reshape(-1), bitorder='big').tobytes()
            source_texture = self.texture(area['path'], f'{MOUNT}/Maps/T_PlayMap_{index:03d}', 'map')
            self.sprite(area['path'], f'{MOUNT}/Maps/SP_PlayMap_{index:03d}',
                        [width / 2, height / 2], source_texture, ground=True)
            low, high = self.engine.wild_level_range(area)
            field_id = area.get('music_id', music[(index-1) % len(music)]['id'])
            battle_id = area.get('battle_music_id', 'bgm40')
            row = {'mapId': index, 'sourceMapId': area['id'], 'displayName': area['name'],
                'region': {'dawn': 1, 'world_ds': 2, 'xros_wars': 3}[region], 'regionId': region,
                'recommendedMinLevel': low, 'recommendedMaxLevel': high,
                'groundSource': 'RawAssets/' + area['path'], 'collisionSource': 'RawAssets/' + area['walkable'],
                'groundSourceSha256': digest(self.source / area['path']),
                'collisionSourceSha256': digest(self.source / area['walkable']),
                'collisionDerivedFromGround': False, 'sourceWidth': width, 'sourceHeight': height,
                'walkGridWidth': width, 'walkGridHeight': height,
                'walkGridBits': base64.b64encode(bits).decode(), 'walkGridSha1': hashlib.sha1(bits).hexdigest(),
                'walkablePixelCount': int(walk.sum()), 'safeSpawnU': x / width, 'safeSpawnV': y / height,
                'importedTexture': source_texture, 'explorationBgmAsset': object_path(self.audio_by_id[field_id]),
                'battleBgmAsset': object_path(self.audio_by_id[battle_id]),
                'wildSpecies': area['encounters'], 'paradoxSpecies': [self.engine.species[s]['base_id'] for s in area['paradox_encounters']],
                'shinySpecies': [self.engine.species[s]['base_id'] for s in area['shiny_encounters']],
                'firewallSpecies': [self.engine.species[s]['base_id'] for s in area['firewall_encounters']],
                'geometry': area.get('geometry', {}), 'sourceProvenance': area.get('provenance', ''),
                'collisionProvenance': area.get('collision_provenance', '')}
            if area.get('foreground'):
                foreground = self.texture(area['foreground'], f'{MOUNT}/Maps/T_PlayMap_{index:03d}_Foreground', 'map')
                self.sprite(area['foreground'], f'{MOUNT}/Maps/SP_PlayMap_{index:03d}_Foreground',
                            [width/2, height/2], foreground)
                row['foregroundTexture'] = foreground
                row['foregroundSource'] = 'RawAssets/' + area['foreground']
            rows.append(row)
            mapping.append({'sourceId': area['id'], 'mapId': index, 'displayName': area['name'], 'regionId': region})
        fingerprint = hashlib.sha256(json.dumps(rows, ensure_ascii=False, separators=(',', ':')).encode()).hexdigest()
        dump(self.resources / 'DigimonMaps.json', {'schemaVersion': 1, 'mapCount': len(rows),
            'playableMapContentRevision': 'DVNXT-' + fingerprint[:16],
            'playableMapContentFingerprint': fingerprint, 'maps': rows})
        dump(self.resources / 'MapIdMap.json', {'schemaVersion': 1, 'maps': mapping})

    def ui_and_effects(self):
        ui = []
        for path in sorted((self.source / 'assets/ui').rglob('*.png')):
            source = path.relative_to(self.source).as_posix()
            suffix = hashlib.sha1(source.encode()).hexdigest()[:8]
            asset = self.texture(source, f'{MOUNT}/UI/T_{safe(path.stem)}_{suffix}', 'ui')
            ui.append({'source': source, 'asset': asset})
        for name, source in UI_ALIASES.items():
            ui.append({'source': source, 'asset': self.texture(source, f'{MOUNT}/UI/Presentation/{name}', 'ui')})
        for effect in self.engine.catalog['battle_effects']:
            frames = []
            eid = effect['id']
            for index, source in enumerate(effect['frames']):
                width, height, _ = self.image(source)
                asset = self.sprite(source, f'{MOUNT}/Effects/{eid}/SP_{eid}_{index:03d}', [width/2, height/2])
                frames.append({'sprite': asset, 'seconds': effect.get('frame_seconds', 0.08)})
            self.manifest['animations'].append({'asset': f'{MOUNT}/Effects/{eid}/FB_{eid}', 'frames': frames, 'fps': 600})
        dump(self.data / 'ui.json', {'schemaVersion': 1, 'textures': ui, 'source': load(self.source / 'data/ui_assets.json')})
        dump(self.data / 'effects.json', {'schemaVersion': 1, 'effects': self.engine.catalog['battle_effects']})

    def farm_and_rules(self):
        from venom.common import farm, economy
        from venom.common.game import SHOP
        source = 'assets/ui/digifarm/level.png'
        width, height, _ = self.image(source)
        texture = self.texture(source, f'{MOUNT}/Maps/T_DigiFarmIsland', 'map')
        self.sprite(source, f'{MOUNT}/Maps/SP_DigiFarmIsland', [width/2, height/2], texture, ground=True)
        dump(self.data / 'farm.json', {'schemaVersion': 1, 'source': 'RawAssets/' + source,
            'width': farm.FARM_WIDTH, 'height': farm.FARM_HEIGHT, 'spawn': farm.FARM_SPAWN,
            'shore': farm.FARM_SHORE, 'texture': texture, 'sprite': f'{MOUNT}/Maps/SP_DigiFarmIsland'})
        shop = [{'itemId': iid, 'displayName': item['name'], 'description': item.get('description', ''),
                 'creditCost': item['price'], 'digiRubyCost': economy.ruby_price(item['price']),
                 'resource': item['resource'], 'amount': item['amount'], 'category': item.get('category', 'capsule'),
                 'rarity': item.get('rarity', 'common'), 'icon': item.get('icon', '')} for iid, item in SHOP.items()]
        dump(self.resources / 'DigimonShop.json', {'schemaVersion': 1, 'items': shop})
        dump(self.data / 'economy.json', {'schemaVersion': 1, 'creditsPerRuby': economy.CREDITS_PER_RUBY,
            'rubyShopCreditUnit': economy.RUBY_SHOP_CREDIT_UNIT, 'maxExchangeRubies': economy.MAX_EXCHANGE_RUBIES,
            'maxCredits': economy.MAX_CREDITS, 'shop': shop})
        dump(self.data / 'mechanics.json', {'schemaVersion': 1, 'source': self.engine.rules,
            'preparedRules': self.engine.catalog['rules'], 'statGrowth': {'hp': [18, 2], 'sp': [2, 0],
            'atk': [3, 0.3], 'def': [2.5, 0.3], 'int': [3, 0.3], 'spd': [2, 0.2]},
            'xpFormula': '35 + floor(12 * level ** 1.45)', 'abiMultiplier': '1 + clamp(abi, 0, 200) / 1000'})

    def finish(self):
        print('Copying authoritative asset bytes...', flush=True)
        shutil.copytree(self.source / 'assets', self.raw / 'assets', dirs_exist_ok=True)
        dump(self.data / 'prepared_catalog.json', self.engine.catalog)
        dump(self.data / 'import_manifest.json', self.manifest)
        source_files = []
        for folder in ('data', 'venom/common'):
            for path in sorted((self.source / folder).glob('*')):
                if path.is_file() and path.suffix in ('.json', '.py'):
                    source_files.append({'path': path.relative_to(self.source).as_posix(), 'sha256': digest(path)})
        dump(self.data / 'source_provenance.json', {'schemaVersion': 1, 'sourceVersion': self.engine.catalog.get('version'),
            'sourceFiles': source_files, 'pngPolicy': 'Original PNG bytes preserved; no resampling or artwork synthesis.',
            'audioPolicy': 'Original compressed streams retained; Unreal PCM16 decoding retains native sample rate and channels.'})
        report = {'schemaVersion': 1, 'baseSpecies': sum(s['variety']=='normal' for s in self.engine.species.values()),
            'varietySpecies': len(self.engine.species), 'varieties': dict(Counter(s['variety'] for s in self.engine.species.values())),
            'publicMaps': len(self.engine.maps), 'regions': dict(Counter(m.get('region_id') for m in self.engine.maps.values())),
            'tamers': len(self.engine.tamers), 'effects': len(self.engine.catalog['battle_effects']),
            'counts': {key: len(value) for key, value in self.manifest.items() if isinstance(value, list)},
            'referencedSourceFiles': len(self.references), 'missingReferences': [],
            'mapRegistrySha256': digest(self.resources / 'DigimonMaps.json'),
            'speciesRegistrySha256': digest(self.resources / 'DigimonSpecies.json'),
            'importManifestSha256': digest(self.data / 'import_manifest.json'),
            'unrealBuildExecuted': False}
        map_registry = load(self.resources / 'DigimonMaps.json')
        report.update({key: map_registry[key] for key in ('playableMapContentFingerprint', 'playableMapContentRevision')})
        dump(self.data / 'conversion_report.json', report)
        verify_export(self.plugin)
        print(json.dumps(report, indent=2), flush=True)

    def run(self):
        for label, action in [('partners', self.partners), ('tamers', self.tamers), ('audio', self.audio),
                              ('maps', self.maps), ('UI and effects', self.ui_and_effects),
                              ('farm and rules', self.farm_and_rules), ('verification', self.finish)]:
            print('Converting ' + label + '...', flush=True)
            action()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path)
    parser.add_argument('--plugin', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--verify-only', action='store_true', help='Validate the shipped native payload without the original source.')
    args = parser.parse_args()
    if args.verify_only:
        print(json.dumps(verify_export(args.plugin.resolve()), indent=2))
        return
    if args.source is None:
        parser.error('--source is required unless --verify-only is used')
    Converter(args.source.resolve(), args.plugin.resolve()).run()


if __name__ == '__main__':
    main()
