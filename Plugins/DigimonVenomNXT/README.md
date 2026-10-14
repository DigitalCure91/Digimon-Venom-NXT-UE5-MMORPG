# DigimonVenomNXT

Native Unreal Engine 5.8 source plugin for the supplied **Digimon Venom NXT v1.5.0** game, with editor content import, server-owned gameplay, persistent AI rivals, private story campaigns and Windows packaging tools.

**1.0.6 import configuration fix:** the renderer default is written directly to project `DefaultEngine.ini` and verified from disk, preserving unrelated settings. This corrects the commandlet stop after MainMenu and PublicWorld were saved. See [INSTALL_CONFIG_FIX_1.0.6.txt](INSTALL_CONFIG_FIX_1.0.6.txt), apply the cumulative update and run **Tools/Build_Windows.cmd** again.

**1.0.5 commandlet startup fix:** the Editor module now loads at `Default`, making the content-import commandlet available during Unreal's class lookup. Interactive menus/previews initialize after the engine is ready and never initialize for commandlets. Both external build scripts reject the former late-loading descriptor before compiling. Replace the `.uplugin` as well as Source/Tools; see [INSTALL_COMMANDLET_FIX_1.0.5.txt](INSTALL_COMMANDLET_FIX_1.0.5.txt).

**1.0.4 build preparation fix:** the build now automatically preserves your Project Settings hosting password in the server-local settings before preparing distributable configuration, then continues into compilation/import/package. It also creates a private `Saved/DigimonVenomNXT/PlayPackagedHost.cmd` launcher for hosting the packaged game on the build machine with the same password. See [INSTALL_BUILD_FIX_1.0.4.txt](INSTALL_BUILD_FIX_1.0.4.txt). Existing native-build/package PowerShell fixtures and the full shipped-content source preflight were executed successfully under Linux PowerShell; Windows/Unreal execution remains required.

**1.0.3 Windows launcher fix:** double-click **Tools/Build_Windows.cmd** for a complete import-and-package build. The window stays open with its result; a separate launcher saves the build output under **Tools/Logs** (with a temporary-folder fallback), including build-script parse/parameter errors. See [INSTALL_LAUNCHER_FIX_1.0.3.txt](INSTALL_LAUNCHER_FIX_1.0.3.txt). This cumulative update includes the earlier compile and startup/world fixes.

**1.0.2 startup/world repair:** full import now creates MainMenu and PublicWorld before importing artwork, configures the native game modes and startup, restores visible editor map previews and exposes direct open-level actions. This update includes the 1.0.1 compile fixes. Follow [INSTALL_STARTUP_WORLD_FIX_1.0.2.txt](INSTALL_STARTUP_WORLD_FIX_1.0.2.txt) when updating an existing installation.

**Start with [INSTALL_AND_BUILD.md](INSTALL_AND_BUILD.md).** Install the plugin at `<Project>/Plugins/DigimonVenomNXT`. Full distributions include the raw content in `Resources`; cumulative source updates retain that folder from the existing installation. Generated Unreal assets and the Windows executable are built with Unreal Engine.

```bat
cd <Project>\Plugins\DigimonVenomNXT\Tools
Build_Windows.bat -EngineRoot "C:\Program Files\Epic Games\UE_5.8" -ImportContent
```

The command builds native Editor and Game targets, imports the registered content, verifies the import receipt, cooks the startup worlds and creates a separate Windows package. `Build_Windows.cmd` is equivalent. The editor also exposes **Tools → Digimon Venom NXT: Build Complete Game Content**. See the installation guide for explicit project paths, Shipping builds and troubleshooting.

After editor setup, use **Tools → Digimon Venom NXT: Open Main Menu**, then **Play** for account creation/login, Host and Join. PublicWorld has its own native game mode for authenticated, replicated gameplay. **Open Public World** frames the first map and enables inspection of nearby or selected map artwork; it is separate from starting through the account menu.

## Included content

| Area | Native content |
|---|---|
| Collection | 502 supplied species; Normal, Paradox, Shiny and Firewall varieties; 2,008 visual identities |
| Starters | All 78 source Rookie choices, searchable and paginated |
| Public world | 500 maps: 254 Dawn, 150 World DS and 96 Xros; source collision masks, authored foregrounds and spawn positions |
| Dawn Relay Chronicle | 18 private maps, eight DigiBadges, championship, title defense and reclaim |
| World DS: Paradox Chronicle | 18 private maps, 17 Paradox Crests, the authored level-100 Paradox Mega finale |
| Super Xros: Ghostline | 31 private maps, 30 Access Proofs, witness/report progression, reveal and level-99 finale |
| Campaign writing | 293 authored NPC records and 2,068 dialogue branches generated from the supplied game |
| Presentation | 64 source tamers, 96 source effects, 319 imported audio assets, source maps and interface art |
| Shop and growth | All 20 source items, six recovery capsules, 12 stat-specific training foods, CAM and ABI foods |

The import manifest registers **69,185 generated assets**: 16,164 textures, 41,982 sprites, 8,648 flipbooks, 319 sounds, 2,008 partner animation sets and 64 tamer sets. Original raw assets are included; compressed source audio also has native-rate PCM import copies. Imported textures retain source pixels, animation timing, alpha and native frame-body metadata. The four Fanglongmon varieties' partial opposite-facing frames are handled individually.

## Gameplay and presentation

The runtime uses Digimon's source species, evolution links, stats, moves, Vaccine/Virus/Data/Free affinities, wild group distributions, growth, training limits, rare varieties and rewards. Public encounters and private field practice have separate source rules. Base scan is retained after an enemy defeat; the appropriate campaign mastery adds 20% only after a wild victory, including fractional progress when custom scan settings require it.

The server-owned rival simulation, visible roaming bots, real rival parties, trade/community systems, season competition and ranked structure remain integrated. Ranked uses Bronze through Master grades. Private campaigns have independent progression and saved decisions. Battle checkpoints preserve accepted choices, scans and queued actions across reconnects under the configured persistence policy.

Native menus provide the full starter selection, collection filters, party management, DigiLab recovery/evolution, DigiFarm feeding, paginated regional map atlas, all shop items and currencies, campaign dialogue and battle controls. Source-size sprites, padded-frame correction, ground anchors, foreground layers and a fit-relative camera replace assumptions tied to unrelated artwork. Zoom begins at the full map and retains the player's zoom across map changes.

## Global settings

Open **Project Settings → Game → Digimon Venom NXT**. Settings cover the public host address, gameplay port, hosting password, player limits, scans and encounter probabilities, XP/credit rates, progression, source item prices, rival simulation, seasons/ranked, audio, camera, movement and persistence. `ShopCreditPriceOverrides` and `ShopDigiRubyPriceOverrides` accept canonical source item IDs for individual overrides.

The shipped host password is blank. For a packaged host, use `DIGIMONVENOMNXT_HOST_PASSWORD` or the hosting machine's Saved `DigimonVenomNXT/Host.ini`; details and precedence are in the installation guide. Shared configuration must not contain a production secret.

The inherited default save policy retains normal progress in server memory until administrator `/saveall` or administrator logout. Turn on **Enable Global Autosaves** for periodic disk checkpoints. A successful in-session transaction is not a guarantee against process or machine failure while disk saving is disabled.

## Source layout

- `Source/DigimonVenomNXTRuntime`: gameplay, profiles, rivals, campaigns, world rendering and native UI.
- `Source/DigimonVenomNXTEditor`: manifest-driven import, generated levels and commandlet.
- `Resources/RawAssets`: supplied source assets and native import audio.
- `Resources/GameData`: source catalogues, import manifest and conversion metadata.
- `Resources/Digimon*.json`: native runtime registries.
- `Config`: plugin configuration and content staging.
- `Tools`: Windows build helpers, deterministic source converters and regression checks.
- `Docs`: validation evidence and the remaining Unreal acceptance procedure.

`Tools/convert_digimon_content.py` reproduces content registries from the supplied source tree. `Tools/generate_digimon_campaigns.py` reproduces authored campaign data. Run either script with `--help` for its input contract. Installed assets can be checked independently of that source tree with `python Tools/validate_plugin.py`.

## Validation status

Portable C++ rule tests, extracted runtime adapter tests, campaign progression tests and source/asset consistency checks are supplied and executed as documented in [Docs/VALIDATION.md](Docs/VALIDATION.md). These checks cover real production source where possible; lightweight Unreal mocks are identified in the adapter runners.

The latest supplied **UE 5.8.3 Windows log successfully compiled the 1.0.5 Editor target**, ran the import commandlet and saved MainMenu/PublicWorld with all 500 zones. Setup then stopped at the renderer config write corrected in 1.0.6, before artwork import and Game-target compilation. **The corrected 1.0.6 source has not been compiled with Unreal/MSVC here.** Import, cooking, Windows launch, visual inspection and multiplayer playtesting remain required. This archive is a source beta; it is not a compiled or production-certified game. Follow [Docs/UNREAL_ACCEPTANCE.md](Docs/UNREAL_ACCEPTANCE.md) after the first successful Windows build.
