# Unreal 5.8 acceptance procedure

This is the remaining engine-dependent verification work. It has not been executed in the source preparation environment.

## Build and import

1. Use a clean UE5.8 Windows project and install `Plugins/DigimonVenomNXT`. Preserve this directory structure; do not merge it over another plugin's generated content.
2. Run `Tools/Build_Windows.bat -EngineRoot "<UE5.8>" -ImportContent`. Check the first error at each failed stage. A generated receipt only exists after a complete import; do not bypass it.
3. Confirm both modules pass Unreal Header Tool and C++ compilation. Inspect import logs for failed PNG/WAV loads, invalid sprite rectangles, missing references, unsupported durations and package save errors.
4. Confirm the import receipt includes all registered packages and the generated MainMenu/PublicWorld worlds. Reimport and verify that the operation is repeatable.
   On a fresh project, also run the **Import All Bundled Assets** menu entry: it must create both worlds and configure startup. Interrupt the large import after the worlds are saved, then resume it; incomplete artwork must never produce a successful full-build receipt.
5. Build Development, then Shipping. Launch the packaged executable from its archived directory on a machine without the editor. Confirm required plugins and runtime registry staging.

There are over 69,000 generated packages. The source delivery is about 1.9 GiB (including about 1.8 GiB of raw assets); generated packages, derived data, cooking and builds need additional disk space. Source textures expand considerably during import. Import in the commandlet with the editor closed; importer batches release saved objects to control memory. No measured Windows import time or peak memory is claimed.

## First-session checks

- From an unrelated editor template level, use **Open Main Menu**, save/cancel when prompted, and confirm Play runs the login screen. Use **Open Public World** and confirm it frames map 1 with actual artwork; select/focus maps in all three regions and verify their ground/foreground previews. Save/reopen the world and confirm those temporary previews are not serialized into the map or duplicated into PIE.
- The main menu displays source artwork at 1280×720, 1920×1080, ultrawide and windowed sizes. Check font clarity, clipping, focus, scrolling and controller/back navigation.
- Host with a private password, create an account, connect a second client by IP, choose among all 78 starters and verify the chosen sprite/variant.
- Visit representatives of Dawn, World DS and Xros, including very tall/wide maps and foreground maps. Check spawn collision, eight-direction movement, foreground occlusion, camera bounds, zoom, partner following and tamer nameplates. Test all 64 tamer styles.
- Sample ordinary, padded and Fanglongmon animation frames. Confirm feet remain grounded, sprite bodies retain source proportions, and left-facing partial mappings never double-flip.
- Check map music, split Xros introductions/continuations, mute/pause, menu and battle overrides. Travel during an introduction; the old track must never resume over the new map.

## Gameplay and saves

- Exercise one-, two- and three-opponent public wild battles with one and three living active partners. Verify source levels, at most one rolled rare opponent, damage, SP costs, six recovery items, retreat and loss.
- Defeat one enemy, disconnect before victory, reconnect, then retreat. Earned base scan must remain once; victory mastery must not be paid. Repeat with an eventual victory and custom 1% base scan to check fractional mastery.
- Buy each of the 20 shop items with both currencies. Check quantity limits, the 999-item cap, insufficient funds, credit exchange and failed-save rollback.
- Verify evolution/de-evolution identity, variant, ABI, CAM, training and level reset. Test all six +1/+5 training foods against the per-stat and combined caps.
- Materialize at the configured scan requirement, with party and farm full, and verify permanent collection ownership. Check fractional scan reset when scan consumption is enabled.
- Complete each campaign through legitimate progression. Check quest acceptance/reporting, healer/shop/lab/farm access, portals, authored teams and rewards, training, mastery, Dawn defense/reclaim, World DS 17-crest finale and Ghostline reveal/30-proof finale.
- Disconnect during campaign and season decisions, reconnect and verify exact state without duplicate rewards. Attempt travel, trade, evolution, feeding and new battles while any checkpoint is pending.
- Verify normal memory retention and explicit `/saveall`, then repeat with **Enable Global Autosaves** turned on and a full server restart. Test invalid/corrupt save handling with disposable test accounts.

## Multiplayer and production performance

Use a separate host process and a separate client process for the first network acceptance run. On the host, create an account, enter the hosting password and start the world. On the client, configure the host address, create a different account and Join. Confirm both are authenticated by the host, both receive their own starter/profile, both see movement and followers on the same public map, and neither can view the other's private farm/campaign. Exercise one wild battle and one player interaction, save, reconnect and restart the host. Also check wrong account credentials, duplicate account login and a wrong hosting password. This procedure verifies the complete frontend-to-server workflow; source inspection alone cannot certify it.

Check two real clients plus configured AI rivals: movement/follower replication, private-world isolation, profile visibility, chat, friend/community operations, trade cancellation and settlement, live rival occupancy, friendly matches, ranked attacker/defender outcomes and season rollover. Repeat after disconnects and under latency.

Profile map travel, crowded rival scenes, battle effects, collection paging and large rosters. Inspect cooked size, texture residency, load stalls, shader compilation, memory and network traffic on target hardware. Test the entire acceptance list against the final Shipping archive. Record the actual engine version, platform, logs and any remaining defects before removing the beta designation.
