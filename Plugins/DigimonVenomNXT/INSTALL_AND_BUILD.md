# DigimonVenomNXT — install, import and package

This is a native Unreal Engine source plugin. Unreal Editor must compile its C++ modules and import the supplied Digimon source assets before you can play or package the game. Your Unreal installation creates the generated `.uasset` and `.umap` packages.

## Install into an Unreal 5.8 project

1. Create or use a Windows Unreal 5.8 project with a filename that is a valid C++ identifier, such as `DigimonVenomNXT.uproject`. Paths may contain spaces. Close Unreal Editor.
2. Put this whole folder at `<Project>/Plugins/DigimonVenomNXT`. The descriptor must be `<Project>/Plugins/DigimonVenomNXT/DigimonVenomNXT.uplugin`.
3. Install the Windows C++ toolchain and Windows SDK required by your Unreal installation. Ensure the engine's Paper2D, CommonUI and EnhancedInput plugins are installed. They are enabled by the build helper.
4. Keep `Resources/RawAssets` and `Resources/GameData/import_manifest.json` with the source plugin. The importer needs them. Do not reuse generated packages from another plugin namespace.

The build helper preserves existing native project source. If a project is content-only, it adds a small `DigimonVenomNXTHost` module and project-named Game and Editor targets. It backs up the `.uproject` before changing it. Ambiguous existing targets or modified generated source stop the helper with an explanation; they are not overwritten.

## One command: compile, import, cook and package

Double-click **Tools/Build_Windows.cmd** for a complete build. With no arguments it imports/resumes content automatically. It locates the host project and its associated UE 5.8 installation, then runs the sequence below. Save and close Unreal Editor first.

The window now stays open after success or failure. The build log is printed at the beginning and end, normally under **Tools/Logs**; a user temporary folder is used if that location is not writable. Send the newest log if a build stops. The log also captures build-script syntax and parameter errors.

Open Command Prompt in the plugin's `Tools` folder:

```bat
Build_Windows.bat -EngineRoot "C:\Program Files\Epic Games\UE_5.8" -ImportContent
```

To specify the host project explicitly:

```bat
Build_Windows.bat -Project "D:\Games\DigimonVenomNXT\DigimonVenomNXT.uproject" -EngineRoot "D:\UE_5.8" -ImportContent -Configuration Shipping
```

The helper checks source hashes and required plugins, builds the native Editor target, runs `UnrealEditor-Cmd.exe -run=DigimonVenomNXTImport`, verifies the completed asset receipt and loads the generated worlds through the startup validator, builds the native Game target, cooks both startup worlds and generated asset directories, then packages to a new `<Project>/Builds/Windows-<configuration>-<timestamp>-<id>` directory. A nonzero exit code stops the sequence. Source imports can take substantial time and disk space.

For later builds with current, saved imported assets, omit `-ImportContent`. Use it again after source asset or manifest changes. Imports resume packages verified against their source, engine/importer version and saved file hashes. Add `-ForceReimport` alongside `-ImportContent` only when you intentionally want to rebuild all registered generated content. Keep custom authoring outside `Content/Generated`.

```bat
Build_Windows.bat -EngineRoot "D:\UE_5.8" -Configuration Shipping
Build_Windows.bat -EngineRoot "D:\UE_5.8" -ImportContent -DryRun
```

`-DryRun` validates and prints the intended sequence without modifying the project or starting Unreal; the launcher still saves its diagnostic log. With `-ImportContent`, it validates import sources instead of requiring generated assets to exist already. `.cmd` and `.bat` run the same build and pause once at the end. For automation, set `DIGIMONVENOMNXT_NO_PAUSE=1` before invoking either wrapper; the original build exit code is preserved. Direct `.ps1` invocation remains noninteractive and does not use the outer launcher log.

The final checks compare the packaged executable with the native build and inspect the staged plugin manifest. They do not launch or play-test the Windows executable.

## Editor import and project settings

After compilation, use **Tools → Digimon Venom NXT: Build Complete Game Content** for the full content import. Use the full import after source updates, allow it to finish, then save and close the editor before external packaging. Partial or failed imports do not count as a completed import. The commandlet uses the same content builder as the editor menu.

In version 1.0.2, **Import All Bundled Assets also performs complete setup**, including MainMenu, PublicWorld and project configuration. The worlds are saved before the large artwork import starts, so an interruption no longer leaves both levels absent. A visible level is not evidence that the asset import has finished; wait for a successful complete-content report.

To recover already imported artwork with missing levels, use **Tools → Digimon Venom NXT: Create / Repair Main Menu + Public World**. If any registered artwork is missing, finish **Build Complete Game Content**. These operations preserve the currently open editor level.

### Start the game from the editor

1. Finish **Build Complete Game Content**.
2. Use **Tools → Digimon Venom NXT: Open Main Menu**, then press **Play**. This opens the generated level explicitly; pressing Play in an unrelated template level does not run the game's login menu.
3. Enter your account credentials and choose **Create Account** or **Login**. The menu stages the credentials for the hosting server to verify.
4. Choose **Host** and enter the hosting password, or choose **Join** to connect to the configured address. Hosting uses the local machine as the authoritative server.
5. After the server verifies the account and synchronizes the profile, the native PublicWorld game mode spawns the tamer. New accounts begin in their private DigiFarm and choose a starter through the Overview screen; the map atlas opens the public habitats.

**Tools → Digimon Venom NXT: Open Public World** opens the generated 500-zone level for inspection and frames its first map. Nearby and selected zones display the actual ground and foreground artwork. Editor previews load a bounded set of maps; each game client loads its active habitat. Use **Open Main Menu** for the login/hosting play flow.

MainMenu uses `ADigimonVenomNXTMainMenuGameMode`; PublicWorld uses `ADigimonVenomNXTGameMode`. The latter configures the native player controller, player state, game state, tamer character and battle actor. Player movement and public state replicate; private profiles synchronize to their owner, and the server authorizes profile changes, battles and rewards. Accounts and saves belong to the hosting machine, matching the inherited direct-IP multiplayer architecture.

Project Settings → Game → Digimon Venom NXT exposes host address/port, player limits, party rules, levels and progression, encounter/scan rates, money rates, AI rival simulation, ranked rewards, farm/evolution, cameras, movement, audio and persistence. Camera zoom starts at a fit of the full source map to the viewport (`FieldCameraInitialZoom=1`); the zoom step is `FieldCameraZoomIncrement=0.25`. Shop prices can be adjusted per item through `ShopCreditPriceOverrides` and `ShopDigiRubyPriceOverrides`; use the canonical item IDs in `Resources/DigimonShop.json`. The AI rival architecture remains server-owned. Important starting values use the supplied source data; the catalog and map import registries remain authoritative for available content.

`PublicGameAddress` is the IP or DNS name clients connect to; `GameplayPort` defaults to 7777. The startup map is `/DigimonVenomNXT/Generated/Levels/MainMenu`; the public world is `/DigimonVenomNXT/Generated/Levels/PublicWorld`. The importer configures the host project for these maps and the plugin game instance. Make intentional overrides in the host project's settings.

The default persistence policy keeps progress in server memory until administrator `/saveall` or administrator logout. Turn on **Enable Global Autosaves** in Project Settings if you want automatic checkpoints. Ordinary player logout does not force a disk checkpoint under the default policy.

## Host administrator password

Set `AdminHostPassword` through the masked Project Settings field as usual. Since 1.0.4, the Windows build automatically preserves this credential in `<Project>/Saved/DigimonVenomNXT/Host.ini`, verifies the local copy, then clears the distributable configuration value and continues. It never prints the password. No manual INI edit is needed for the normal setup. A conflicting existing local credential or differing passwords in multiple config files stops before changes, with an explanation; existing credentials are not silently overwritten. `-DryRun` reports the intended migration without changing files.

After packaging, the build creates **`<Project>/Saved/DigimonVenomNXT/PlayPackagedHost.cmd`**. Double-click it on the build machine to open the packaged game's normal main menu with your local hosting credential available. Log in and choose **Host** using the same password. This launcher and its settings stay outside the distributed game folder; the launcher passes the credential only to the game process. Players joining the world can launch the packaged executable normally.

For the machine hosting the packaged world, set one of these server-local overrides:

- Environment variable `DIGIMONVENOMNXT_HOST_PASSWORD` in the environment that launches the game.
- `<ProjectSavedDir>/DigimonVenomNXT/Host.ini`, containing `[Hosting]` and `Password=<your private value>`.

The environment variable takes priority, then the local file, then the editor setting. `ProjectSavedDir` is Unreal's Saved directory for that executable; packaged installations may place it in the user's local application-data directory. Keep this file on the hosting machine. This password unlocks hosting; it is not a public-world join password. Account registration and login use the existing server-owned account system.

## Plugin-only compilation

```bat
Build_UE58.bat -EngineRoot "D:\UE_5.8" -PackageDirectory "D:\PluginBuilds\DigimonVenomNXT"
```

This runs Unreal Automation Tool `BuildPlugin` and packages the plugin. It does not import art, cook worlds or produce a playable game. Use `Build_Windows.bat` for the game.

## Verification and troubleshooting

- **Could not persist Custom Depth with Stencil:** apply the complete 1.0.6 update and run `Build_Windows.cmd` again. Earlier setup used a cache flush to persist the source renderer setting; the correction updates the property directly and verifies the saved file. The previous message did not establish that your file was read-only. Genuine write failures still stop with the exact config path. Existing worlds and source assets can be retained.
- **ImportCommandlet looked like a commandlet, but Unreal could not find the class:** install the complete 1.0.5 update, including `DigimonVenomNXT.uplugin`. The old `PostEngineInit` Editor-module loading phase prevented the reflected class from being discovered. The corrected module loads at `Default`, while interactive menus/previews remain deferred. Run `Build_Windows.cmd` again; it rebuilds the Editor module and resumes content setup.
- **Window closes immediately:** apply the launcher fix and run `Build_Windows.cmd` again. It should stay open with the actual build result. Without the fix, open Command Prompt in Tools first and run `Build_Windows.cmd -ImportContent` to retain the error output.
- **Hosting credential in distributable config:** apply 1.0.4 and run `Build_Windows.cmd` again. The build migrates the Project Settings password automatically while preserving local hosting. No need to delete your password.
- **No MainMenu/PublicWorld after an older import:** install 1.0.2, rebuild the Editor module, then run **Create / Repair Main Menu + Public World**. Finish **Build Complete Game Content** if artwork is incomplete. For the external workflow with already imported artwork, use `Build_Windows.bat -EngineRoot "<UE5.8>" -RepairStartup`; use `-ImportContent` instead if assets are missing.
- **Pressing Play shows a template scene:** explicitly use **Open Main Menu**, then Play. Startup defaults do not switch the currently open editor level.
- **PublicWorld looks empty in the editor:** use **Open Public World** to frame map 1, or focus/select another map zone in the Outliner. Only nearby/selected artwork is loaded into editor previews. An interrupted asset import still needs to finish.
- **Missing content import receipt:** run with `-ImportContent`. Do not hand-author a receipt. It binds the registries and generated asset hashes to a successful import.
- **Registry/manifest or asset hash changed:** import the current source again. A stale receipt cannot certify newly changed content.
- **Editor open:** save and close all Unreal Editor processes before running the external build.
- **Missing engine plugin or toolchain:** repair the corresponding Unreal/Visual Studio installation. The scripts do not fabricate plugin descriptors or skip native compilation.
- **Custom targets/source conflict:** preserve your existing C++ source and resolve the stated target ambiguity; do not delete it simply to satisfy the helper.
- **Compiler/commandlet/cook error:** start with the first error from that failed stage. The helper returns failure and does not report the package as verified.

Portable C++17 and Python regression suites can run with Python 3 and `g++` on PATH (for example, Linux or WSL):

```sh
python Tools/run_portable_tests.py
python Tools/validate_plugin.py
python Tools/validate_server_console_integration.py
```

The runner writes an individual log for every suite and a JSON result report under `Intermediate/PortableTests`. The source validator checks import sources, references, collision data and reflected C++ patterns; it is not an Unreal compiler.

Maintainer PowerShell regression fixtures can run without Unreal:

```bat
powershell.exe -NoProfile -ExecutionPolicy Bypass -File Tools\Test_NativeBuild.ps1
powershell.exe -NoProfile -ExecutionPolicy Bypass -File Tools\Test_PackagedPlugins.ps1
powershell.exe -NoProfile -ExecutionPolicy Bypass -File Tools\Test_HostCredentials.ps1
```

This source delivery was prepared in a Linux workspace without the Windows Unreal 5.8 editor or toolchain. Actual UE compilation, content import, cook, executable launch and multiplayer play testing must be performed in the Windows project; they are not represented as completed by this delivery.
