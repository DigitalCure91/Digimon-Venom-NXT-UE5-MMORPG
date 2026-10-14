# DigimonVenomNXT validation

## 1.0.6 import configuration correction

The supplied `Windows-20261014-073128-3cc6f4a0.log` records a successful **1.0.5 Editor build (114 actions)** on UE 5.8.3. The import commandlet was discovered and executed; it saved MainMenu and PublicWorld with all 500 zones. Setup then stopped at the disk check for `r.CustomDepth=3`. Artwork import, the Game-target build and cooking had not begun. The log does not establish a filesystem permissions problem.

`SaveRenderDefaults` now uses an absolute normalized project-default path and Unreal's single-property disk update API. It checks the write result and independently rereads the value before updating the active config cache. Already-correct defaults skip the write. It preserves other renderer keys and unrelated sections, and reports actual write or readback failures instead of assuming the file is read-only. The UE 5.8 [FConfigFile API](https://dev.epicgames.com/documentation/unreal-engine/API/Runtime/Core/FConfigFile) documents the signatures used, including `void Read` and the boolean single-property writer.

The fresh PowerShell 7.6.6 Linux checks pass **58 native-build, 30 packaged-plugin and 23 credential fixtures**. The Python Windows-boundary suite passes 9 tests with its Windows-only launcher process test skipped; the host-credential suite passes all 3 tests. Existing editor setup, lifecycle, world-entry, settings and packaged-startup checks also pass. Focused config regression details and exact logs are in [config_verification_1.0.6.json](config_verification_1.0.6.json).

The new render-persistence suite passes **3 tests with 49 checks** against the extracted production function, using real temporary files and separate disk/cache test doubles. It exercises preserved unrelated settings, repeated runs, already-correct read-only defaults, missing keys/files, write failure, false write success, invalid/unreadable readback, missing global config and DefaultGame save failure. Both compiled negative controls are rejected: the original cache-flush implementation and one that assumes its write reached disk.

These checks use portable C++ test doubles and Linux PowerShell. They do not execute Unreal's config writer or Windows packaging. **The corrected 1.0.6 import/cook and Windows Game build remain unexecuted here.** The prior Editor build and world-save results above are evidence from the user's log, not a claim that this update has produced a playable package. Unchanged raw assets were not downloaded or revalidated during this narrow code repair; their manifest hashes are retained from the cumulative update.


## 1.0.5 commandlet discovery correction

The supplied `Windows-20261014-063834-a32ee0d0.log` proves that the 1.0.4 native **Editor target compiled and linked successfully (114 actions)** on UE 5.8 with MSVC 14.44. The next process failed before commandlet Main: Unreal could not find `DigimonVenomNXTImportCommandlet`. The runtime module was loaded, but the Editor module containing the reflected commandlet was still configured for `PostEngineInit` and had not loaded. No content import, Game-target compilation or cooking began.

The descriptor now declares the Editor module at `Default`. Editor-only presentation work is deferred through the UE5.8 `FCoreDelegates::GetOnPostEngineInit()` accessor, with a commandlet guard and paired delegate cleanup. The C++ lifecycle fixture compiles the actual module header and lifecycle methods against small stand-ins and executes **8 scenarios**. Existing open-level callbacks and setup orchestration also pass. These stand-ins test behavior, not Unreal ABI or class registration.

Actual Linux PowerShell runs pass **58 build-helper fixtures**, including rejection of the old descriptor and acceptance of the corrected installed descriptor. The focused Windows boundary suite passes with its Windows-only process fixture skipped. The complete source/content validator passes **21 checks**, including module loading phase and the C++ source checks. [commandlet_verification_1.0.5.json](commandlet_verification_1.0.5.json) records the supplied-log evidence, checks and changed source hashes.

The corrected 1.0.5 C++/descriptor has not been run in Unreal here. Commandlet discovery, import, Game-target build, cook and packaged gameplay still require the next Windows run. The 1.0.4 Editor-build success above applies to the supplied log, not to a claimed local rebuild of this update.

## 1.0.4 build preparation verification

The supplied Windows transcript reached engine/plugin validation, then stopped before Unreal execution because the Project Settings hosting credential was in DefaultGame.ini. The build now migrates that credential to the supported server-local Host.ini, verifies it before clearing distributable values, and applies the existing postcondition check. It creates a private packaged-host launcher outside the game archive so the same credential remains usable from the packaged main menu.

Actual **PowerShell 7.6.6 on Linux** executed **103 fixture cases successfully**: 50 native-build/receipt cases, 30 packaged-plugin cases and 23 credential-migration cases. All **11 PowerShell scripts parse**. The focused credential workflow's **3 Python tests pass**, including actual child-process environment handling; the Windows build-boundary suite passes **9 tests with 1 Windows-only launcher fixture skipped**. Source-only preflight ran against the real supplied content: **500 maps, 16,164 texture sources, 319 audio sources and 69,189 expected generated packages** passed in 19.7 seconds. The expected package count is a registry result, not evidence those packages were created in Unreal.

[build_verification_1.0.4.json](build_verification_1.0.4.json) records the runtime, results, script hashes and test logs. No Windows PowerShell 5.1/cmd.exe execution, Windows C++ compilation, Unreal import/cook or game launch was available in this environment. Gameplay/editor C++ and content registries are unchanged since 1.0.2. The following older verification is retained as historical evidence.

## Earlier validation

**1.0.3 launcher verification:** the focused Windows build-boundary suite passes 8 portable contract tests. Two behavioral tests are explicitly skipped because Windows/PowerShell are unavailable: the existing native-build fixtures and the new launcher process fixtures. The new fixtures exercise default import, spaced paths, stderr/log capture, nonzero exit propagation, bad parameters, parse errors, missing scripts and the temporary log fallback using build stubs. No Unreal build or actual Windows launcher execution was performed here. Gameplay/editor C++ and all asset registries are unchanged from 1.0.2; the full-suite result below is retained as historical evidence, not a fresh 1.0.3 run.

All **69 portable regression suites passed** for version **1.0.2-native-source**: 39 standalone C++ executables and 30 Python suites. One PowerShell behavioral test is explicitly skipped because PowerShell is unavailable. The unchanged campaign sources retain the separate successful `-O0` and `-O2` runs from 1.0.1. Per-suite output, environment, registry hashes and the current source-tree fingerprint are recorded in [portable_test_results.json](portable_test_results.json).

This verification ran in Linux with Python and a C++17 compiler. Unreal Engine 5.8 and Windows PowerShell were unavailable. The results establish portable gameplay behavior, source integration checks and source-content integrity; they do not establish a successful Unreal build or a production-ready Windows executable.

| Executed check | Result |
| --- | --- |
| Portable core and real-source adapter suites | 69 passed, 0 failed; one unavailable PowerShell behavioral test skipped |
| Actual campaign translation units with live profile declarations | O0 and O2 builds and progression checks passed in 1.0.1; those sources are unchanged |
| Plugin and imported-source validator | 20 checks passed, 0 failures |
| Final reflected C++ source validator | 16 checks passed across 226 C++ files |
| Server-console integration validator (unchanged; 1.0.1 run) | 48 checks passed, 0 failures |
| Python syntax | 37 top-level tool files parsed |
| Native collision core against shipped maps | All 500 registered spawns walkable at the configured footprint radius of 8 |
| Campaign generation compared with original source | 67 maps, 293 NPCs and 2,068 dialogue branches matched |
| Original GameEngine encounter-pool audit | All 2,000 ordered map/variety pool arrays matched |

The source validator verifies every texture/audio input hash, unique import destination, sprite/animation/partner/tamer reference, eight-direction tamer set, canonical species reference and map-source hash. For all 500 maps it independently verifies that the packed collision masks reproduce the source image pixels and that the recorded spawn is safe. The native collision suite additionally executes the actual C++ collision implementation against those same shipped masks.

The separate encounter-pool audit compared the registry with the original GameEngine source for all 500 maps and four varieties. It ran during the 1.0.0 source conversion and requires the original source tree; the content registries are unchanged through 1.0.2. This audit is additional to the portable suites.

## Startup and world repairs in 1.0.2

Source comparison with the supplied working baseline identified these gaps: asset-only import omitted startup worlds, world generation waited for the whole asset catalog, the editor had no way to open the generated levels, placed zones had no artwork preview, and startup repair accepted a saved world without verifying its native game mode or zone coverage.

The update creates and saves MainMenu/PublicWorld first, repairs their native game modes and all 500 zones, persists startup/cooking defaults, then imports and verifies assets. All full-import aliases use this sequence. Missing worlds can be repaired independently; only a verified complete asset set can receive a packaging receipt. Import resumption verifies the engine/importer version, manifest and saved package hashes. Preview components are transient and editor-only; nearby/selected maps show their real ground and foreground art without serializing all map textures into PublicWorld. The explicit open-world action respects save/cancel and frames map 1. Runtime foreground occlusion and failed-map-transition clearing were also repaired.

New executed coverage:

- The actual setup orchestration compiles and passes **42 paths** spanning all full-import aliases, replace/resume, early world creation, every failed stage, cancellation and receipt ordering. A negative mutation restoring the original asset-only entry point is detected.
- The actual open-level callback passes missing-editor, PIE, missing-level, cancelled-save, failed-load and successful MainMenu/PublicWorld scenarios.
- All **500 ground maps and 295 foreground layers** match their import registrations; editor preview selection and bounded residency are exercised in the production helper.
- The extracted runtime renderer rejects nine invalid transitions, clears both old layers and preserves source geometry/foreground depth. All 500 registered collision-safe spawns remain valid.
- Six portable Windows build-contract checks pass. Expanded PowerShell behavior fixtures are supplied but were **not executed** here.

The native account/login, Host/Join, profile synchronization, gameplay authority and replication paths were compared with the baseline source. They remain connected. This is the existing host-authoritative direct-IP architecture with per-host accounts and saves; configured player counts are not load-test results. A real host plus a separate joined client still needs the engine acceptance procedure.

## Compiler-log corrections in 1.0.1

The supplied Windows log used UE 5.8.3 and MSVC 14.44. UnrealHeaderTool succeeded; compilation reported 36 error diagnostics and no compiler warnings. The diagnostics reduce to four causes, including cascading messages:

- Absent profile members in campaign reconciliation, an unused migration function and automation tests. Runtime progression now uses only the native per-campaign achievements and mastery fields. The portable campaign runner extracts the current profile and progress declarations from `DigimonVenomNXTTypes.h`, preventing a stale hand-written schema from concealing absent fields.
- A missing direct Settings include in the data subsystem. The source guard checks all settings class users; a negative fixture removes the real include to reproduce the dependency failure.
- `FConfigFile::Read` used as a boolean despite returning `void`. The actual Settings translation unit compiles against the observed API contract and passes 12 startup/password-precedence checks; its negative control rejects the original conditional call.
- MSVC C4883 for a generated campaign function large enough to suppress optimization. Generation now emits 360 record helpers, 17 bounded batches and three builders with explicit non-inlining. The largest function contains 165 statements and 13,945 bytes; authored assignment hashes and order match the original unsplit content. No warning suppression or optimization-disable setting was added.

These checks establish the corrections against the reported causes. A successful corrected Unreal/MSVC build has **not** been executed in this environment.

The current import manifest registers 16,164 textures, 41,982 sprites, 8,648 animations, 319 audio assets, 2,008 partner sets and 64 tamer sets. These are source/import registrations; Unreal has not generated or cooked their `.uasset` packages in this environment.

Selected integration coverage includes:

- **392 economy checks:** actual purchase, currency exchange, direct ABI food and healing handlers; authoritative costs, capacity and overflow boundaries, failed persistence rollback and replay protection. The transaction fixture also uses undefined-behavior sanitization.
- **715 retention checks:** actual profile save/load/retention methods, deferred manual saving, commerce revisions, disconnected sessions and fractional scan migration. Two negative controls demonstrate that missing session retention and unconditional writes are detected.
- **260 wild-battle adapter checks:** source encounter pools and probabilities, private practice selection, source rewards, fractional scan mastery, saved encounters, living first-three formation, no implicit healing or reserve promotion for human source battles, and preserved automatic rival behavior.
- **Field and campaign presentation:** source-body sizing, aura padding, map/farm scale, camera fit and bounds, 12 arbitrary sprite pivot/PPU mappings, source arrival coordinates, and public map metadata roundtrips without map texture loads.
- **Battle and campaign behavior:** production combat adapters, progression, evolution, scan, training, ranked/season policy, all authored campaign routes and finales, dialogue/quest gates, loss/retry/return paths, independent mastery rewards, checkpoint recovery, private map geometry, and client arrival ordering.
- **Server systems:** manual persistence, profile transfer framing, atomic file policy, trade settlement, social rules, unranked settlement, AI rival training/habitats, chat, console permissions, and package-startup integration checks.

The portable adapter suites compile extracted production functions with small Unreal stand-ins. They do not emulate Unreal reflection, serialization, RPC delivery, rendering, the audio device or the engine asset pipeline.

## Reproduce the available checks

From the plugin directory, with Python 3 and `g++` on PATH:

```sh
python Tools/run_portable_tests.py
python Tools/validate_plugin.py
python Tools/validate_compile_surface.py
python Tools/validate_server_console_integration.py
python Tools/run_digimon_campaign_tests.py --optimization 0
python Tools/run_digimon_campaign_tests.py --optimization 2
```

The runner discovers the shipped standalone C++ and Python suites and writes logs plus `results.json` under `Intermediate/PortableTests`. To repeat the campaign source comparison, provide the original source tree:

```sh
python Tools/generate_digimon_campaigns.py --source <OriginalDigimonSource> --check
```

## Required Unreal and Windows acceptance

The following remain **unexecuted**:

- A fresh UnrealHeaderTool run and UE 5.8 Editor/Game module compilation of this corrected 1.0.2 source. The supplied failing 1.0.0 build did pass UnrealHeaderTool.
- Editor and commandlet import, asset saves, completed import receipt generation and interruption/retry behavior in Unreal.
- The supplied PowerShell regression fixtures and Windows build helpers.
- Win64 cooking, packaging, packaged-plugin inspection and executable launch.
- Live multiplayer, durable engine serialization, audio playback, controller/input, memory/performance, and visual/UI play testing.

Use [INSTALL_AND_BUILD.md](../INSTALL_AND_BUILD.md) for the external `Build_Windows.bat -ImportContent` workflow. The helper requires native compilation, current content hashes and a completed import receipt before packaging. Follow [UNREAL_ACCEPTANCE.md](UNREAL_ACCEPTANCE.md) for engine and play-test acceptance before calling a build production-ready.
