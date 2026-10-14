#!/usr/bin/env python3
"""Compile the supplied Venom NXT campaigns into native Unreal authored content.

Usage: python Tools/generate_digimon_campaigns.py --source /path/to/DigimonVenomNXT
The source GameEngine remains authoritative for scripts, placement and rewards.
No engine, image processing, synthetic encounters or internet access is involved.
"""
import argparse
import json
import re
import sys
from pathlib import Path


# Generated construction code must remain small enough for MSVC's optimizer in
# every configuration. Bound each authored record and every dispatcher; never
# silence C4883 or turn optimization off for an oversized campaign function.
MAX_FUNCTION_STATEMENTS = 192
MAX_FUNCTION_BYTES = 32768
MAX_BATCH_RECORDS = 24


def emit_function(out, name, body, returns_content=False):
    statements = re.sub(r'"(?:\\.|[^"\\])*"', '""', '\n'.join(body)).count(';')
    byte_count = len('\n'.join(body).encode('utf-8'))
    if statements > MAX_FUNCTION_STATEMENTS or byte_count > MAX_FUNCTION_BYTES:
        raise ValueError(f'{name} exceeds the generated function size contract '
                         f'({statements} statements, {byte_count} bytes). Split this record into smaller helpers.')
    signature = f'FContent {name}()' if returns_content else f'void {name}(FContent& C)'
    # Prevent link-time or normal inlining from reconstructing the monolithic
    # builder. Each helper is still compiled with the project's optimizations.
    out.extend([f'static FORCENOINLINE {signature}', '{', *body, '}', ''])


def literal(value):
    return 'TEXT(' + json.dumps(str(value), ensure_ascii=True) + ')'


def names(values):
    return '{' + ', '.join(literal(v) for v in values) + '}'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--plugin', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--check', action='store_true', help='Validate reproducibility without changing generated content')
    args = parser.parse_args()
    sys.path.insert(0, str(args.source.resolve()))
    from venom.common.game import GameEngine, variety_of
    from venom.common import story
    engine = GameEngine(args.source, seed=1)
    map_ids = {row['id']: i for i, row in enumerate(engine.catalog['maps'], 1)}
    variant_names = {'normal': 'Normal', 'paradox': 'Paradox', 'shiny': 'Shiny', 'firewall': 'Firewall'}
    def identity(sid):
        species = engine.species[sid]
        return species.get('base_id', sid), variant_names[variety_of(species)]
    out = ['// Generated from supplied venom.common.story content. Do not hand edit.', '']
    summary = []
    for ci, campaign_id in enumerate(story.CAMPAIGN_IDS):
        data = story.content(engine, campaign_id)
        campaign_maps = list(data['maps'])
        local_ids = {mid: i for i, mid in enumerate(campaign_maps, 1)}
        regions = {r['id']: r for r in data['regions']}
        builder = ['    FContent C;',
                f'    C.Name = {literal(data["name"])};',
                f'    C.Introduction = {literal(data.get("introduction", ""))};',
                f'    C.Epilogue = {literal(chr(10).join(data.get("epilogue", {}).get("lines", [])))};',
                f'    C.FinalId = {literal(data["champion_id"])};',
                f'    C.Challengers = {names(n["id"] for n in data.get("challengers", []))};']
        record_helpers = []
        for mid, m in data['maps'].items():
            src = engine.maps[mid]
            r = regions[m['region_id']]
            idx = r['index']
            required = [x['badge']['id'] for x in data['regions'][:idx] if x.get('badge')]
            # The hub and first linear field are open from the start.
            def uv(point):
                return f'FVector2D({point[0] / src["width"]:.12g}, {point[1] / src["height"]:.12g})'
            arrival = m.get('arrival', src['spawn'])
            back = next((e for e in m['exits'] if local_ids[e['to_map']] < local_ids[mid]), None)
            forward = next((e for e in m['exits'] if local_ids[e['to_map']] > local_ids[mid]), None)
            if ci == 2 and local_ids[mid] == 31:
                forward = next((e for e in m['exits'] if e['to_map'] == data['start_map']), forward)
            body = ['    { FDigimonRelayMap M;',
                    f'      M.MapId = {local_ids[mid]}; M.SourceMapId = {map_ids[mid]}; M.RegionIndex = {idx};',
                    f'      M.Name = {literal(m["name"])}; M.Subtitle = {literal(r["subtitle"])};',
                    f'      M.Intro = {literal(r["synopsis"])}; M.Objective = {literal(r.get("objective", ""))};',
                    f'      M.MinLevel = {r["level_min"]}; M.MaxLevel = {r["level_max"]};',
                    f'      M.ArrivalPosition = {uv(arrival)};',
                    f'      M.EntryPosition = {uv([back["x"], back["y"]] if back else arrival)};',
                    f'      M.ExitPosition = {uv([forward["x"], forward["y"]] if forward else arrival)};',
                    f'      M.RequiredBadges = {names(required)};',
                    f'      M.BadgeId = {literal(r["badge"]["id"]) if r.get("badge") else "NAME_None"};',
                    f'      M.bPeaceful = {str(bool(m.get("peaceful", r.get("peaceful", False)))).lower()};',
                    '      C.Maps.Add(M); }']
            helper = f'PopulateCampaign{ci}Map{local_ids[mid]:03d}'
            emit_function(out, helper, body)
            record_helpers.append(helper)
        npcs = list(data['npcs'].values()) + data.get('challengers', [])
        counts = {'maps': len(campaign_maps), 'npcs': len(npcs), 'dialogueBranches': 0, 'battles': 0}
        for ni, n in enumerate(npcs):
            role = {'mentor': 'Guide', 'intel': 'Guide', 'healer': 'Healer', 'shop': 'Shop',
                    'lab': 'Lab', 'farm': 'Farm', 'trainer': 'Tamer', 'warden': 'ParadoxBoss' if ci == 1 else 'Gym',
                    'champion': 'Champion', 'challenger': 'Challenger', 'quest': 'Quest', 'final': 'FinalBoss'}[n['role']]
            if any(n['id'] == challenger['id'] for challenger in data.get('challengers', [])):
                role = 'Challenger'
            src = engine.maps[n['map_id']]
            reward = n.get('reward', {})
            dialogue = n.get('dialogue', {})
            team = n.get('team', [])
            badge = next((r['badge'] for r in data['regions'] if r.get('badge') and r['badge']['id'] == n.get('badge')), None)
            join = lambda key: '\n\n'.join(dialogue.get(key, dialogue.get('intro', [])))
            quest_requires = n.get('quest_requires', [])
            accepted = n.get('requires_accepted', [])
            quest_id = n['id'] if role == 'Quest' else (accepted[0] if accepted else '')
            if not quest_id and ci == 1 and n['role'] == 'warden':
                quest_id = next((i for i in n.get('requires', []) if data['npcs'].get(i, {}).get('role') == 'quest'), '')
            body = ['    { FDigimonRelayNPC N;', f'      N.Id = {literal(n["id"])}; N.MapId = {local_ids[n["map_id"]]};',
                    f'      N.Name = {literal(n["name"])}; N.TamerStyleId = {literal(n["tamer_id"])}; N.Role = EDigimonRelayRole::{role};',
                    f'      N.Position = FVector2D({n["x"] / src["width"]:.12g}, {n["y"] / src["height"]:.12g});',
                    f'      N.Dialogue = {literal(join("intro"))};', f'      N.AfterDialogue = {literal(join("won"))};', f'      N.LostDialogue = {literal(join("lost"))};',
                    f'      N.Level = {max((t["level"] for t in team), default=1)}; N.TeamSize = {len(team)};',
                    f'      N.TeamSpecies = {names(identity(t["species"])[0] for t in team)};',
                    '      N.TeamVariants = {' + ', '.join('EDigimonVariant::' + identity(t['species'])[1] for t in team) + '};',
                    '      N.TeamLevels = {' + ', '.join(str(t['level']) for t in team) + '};',
                    f'      N.Credits = {reward.get("credits", 0)}; N.TrainingLevel = {reward.get("training_level", 1)};',
                    f'      N.QuestId = {literal(quest_id) if quest_id else "NAME_None"}; N.QuestTarget = {max(1, len(quest_requires))};',
                    f'      N.Prerequisite = {literal(quest_requires[0] if quest_requires else n.get("requires", [""])[-1]) if quest_requires or n.get("requires") else "NAME_None"};',
                    f'      N.BadgeId = {literal(n["badge"]) if n.get("badge") else "NAME_None"}; N.BadgeName = {literal(badge["name"] if badge else "")};',
                    f'      N.QuestTitle = {literal(n.get("quest_title", ""))}; N.RoleLabel = {literal(n.get("role_label", n["role"].upper()))}; N.CharacterId = {literal(n.get("character_id", ""))};']
            body.append(f'      N.bMentor = {str(n["role"] == "mentor").lower()};')
            for cpp, key in [('RequiresCompleted','requires'),('RequiresAccepted','requires_accepted'),('RequiresHacked','requires_hacked'),('QuestRequires','quest_requires')]:
                body.append(f'      N.{cpp} = {names(n.get(key, []))};')
            body.append(f'      N.RequiresBadges = {names(n.get("requires_badges", n.get("required_badges", [])))};')
            for cpp,key in [('bRepeatable','repeatable'),('bHideOnReveal','hide_on_reveal'),('bShowRequiresReveal','show_requires_reveal'),('bHideOnComplete','hide_on_campaign_complete'),('bRevealOnComplete','reveal_on_complete'),('bHackedAfterVictory','hacked_after_victory')]:
                body.append(f'      N.{cpp} = {str(bool(n.get(key, False))).lower()};')
            body.append(f'      N.RequiresReveal = {int(n["requires_reveal"]) if "requires_reveal" in n else -1};')
            for key, lines in dialogue.items():
                body.append(f'      N.DialogueBranches.Add({literal(key)}, {literal(chr(10).join(lines))});')
                counts['dialogueBranches'] += 1
            for v in n.get('dialogue_variants', []):
                branches = v.get('branch', [])
                if isinstance(branches,str): branches = [branches]
                body += ['      { FDigimonCampaignDialogueVariant V;', f'        V.Branches = {names(branches)}; V.RequiresCompleted = {names(v.get("requires_completed",[]))}; V.RequiresHacked = {names(v.get("requires_hacked",[]))};',
                        f'        V.RequiresReveal = {int(v["requires_reveal"]) if "requires_reveal" in v else -1}; V.RequiresComplete = {int(v["campaign_complete"]) if "campaign_complete" in v else -1};',
                        f'        V.Text = {literal(chr(10).join(v.get("lines",[])))}; N.DialogueVariants.Add(V); }}']
            for item, qty in reward.get('items', {}).items(): body.append(f'      N.RewardItems.Add({literal(item)}, {qty});')
            if reward.get('partner'):
                base,variant = identity(reward['partner'])
                body += [f'      N.RewardPartner = {literal(base)}; N.RewardPartnerVariant = EDigimonVariant::{variant}; N.RewardPartnerLevel = {min(99,max(1,reward.get("training_level",5)))};']
            body.append('      C.NPCs.Add(MoveTemp(N)); }')
            helper = f'PopulateCampaign{ci}NPC{ni:03d}'
            emit_function(out, helper, body)
            record_helpers.append(helper)
            if team: counts['battles'] += 1
        # The call order is exactly the source map order followed by the source
        # NPC order, including challengers and ordered dialogue variants.
        for start in range(0, len(record_helpers), MAX_BATCH_RECORDS):
            batch = f'PopulateCampaign{ci}Batch{start // MAX_BATCH_RECORDS:03d}'
            emit_function(out, batch, [f'    {helper}(C);' for helper in record_helpers[start:start + MAX_BATCH_RECORDS]])
            builder.append(f'    {batch}(C);')
        emit_function(out, f'BuildCampaign{ci}', builder + ['    return C;'], returns_content=True)
        summary.append(dict(id=campaign_id, **counts))
    out += ['const FContent& Content(int32 Campaign)', '{', '    static const FContent Campaigns[] = { BuildCampaign0(), BuildCampaign1(), BuildCampaign2() };', '    check(Campaign >= 0 && Campaign < 3);', '    return Campaigns[FMath::Clamp(Campaign, 0, 2)];', '}']
    dest = args.plugin / 'Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTCampaignContent.inl'
    rendered = '\n'.join(out)+'\n'
    if args.check:
        if not dest.exists() or dest.read_text(encoding='utf-8') != rendered:
            raise SystemExit('Generated campaign content differs from the supplied source. Regenerate before packaging.')
    else:
        dest.write_text(rendered,encoding='utf-8')
    print(json.dumps(summary,indent=2))


if __name__ == '__main__':
    main()
