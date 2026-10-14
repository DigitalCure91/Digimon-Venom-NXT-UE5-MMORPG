#!/usr/bin/env python3
"""Source-only regression fixtures for reported UE5.8 compiler/UHT failures."""
import unittest
from pathlib import Path
from validate_compile_surface import actor_role_shadows, class_metadata_errors, controller_member_shadows, mask_cpp, network_container_errors, settings_include_errors


class SettingsIncludeTests(unittest.TestCase):
    def failures(self, source):
        code, errors = mask_cpp(source)
        self.assertEqual(errors, [])
        return settings_include_errors(source, code)

    def test_actual_data_subsystem_without_settings_header_is_rejected(self):
        path = Path(__file__).resolve().parents[1] / "Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTDataSubsystem.cpp"
        source = path.read_text(encoding="utf-8")
        self.assertEqual(self.failures(source), [])
        broken = source.replace('#include "DigimonVenomNXTSettings.h"', '')
        self.assertEqual(len(self.failures(broken)), 1)

    def test_commented_include_does_not_satisfy_dependency(self):
        source = '// #include "DigimonVenomNXTSettings.h"\n/*\n#include "DigimonVenomNXTSettings.h"\n*/\nvoid Use() { GetDefault<UDigimonVenomNXTSettings>(); }'
        self.assertEqual(len(self.failures(source)), 1)

    def test_angle_bracket_include_is_allowed(self):
        self.assertEqual(self.failures('#include <DigimonVenomNXTSettings.h>\nvoid Use() { GetDefault<UDigimonVenomNXTSettings>(); }'), [])

    def test_class_name_only_in_comments_or_strings_is_ignored(self):
        self.assertEqual(self.failures('// UDigimonVenomNXTSettings\nconst char* Example = "UDigimonVenomNXTSettings";'), [])


class ClassMetadataPathTests(unittest.TestCase):
    def failures(self, source):
        code, errors = mask_cpp(source)
        self.assertEqual(errors, [])
        return class_metadata_errors(source, code)

    def test_reported_sound_override_short_name_is_rejected_on_its_line(self):
        source = '\n' * 23 + 'UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(AllowedClasses="SoundBase"))\nTMap<FName, FSoftObjectPath> SoundEffectOverrides;'
        failures = self.failures(source)
        self.assertEqual(len(failures), 1)
        self.assertEqual(failures[0][0], 24)
        self.assertIn("AllowedClasses class metadata value 'SoundBase'", failures[0][1])
        self.assertIn("/Script/Engine.SoundBase", failures[0][1])

    def test_repaired_sound_override_long_path_is_allowed(self):
        self.assertEqual(self.failures('UPROPERTY(Config, meta=(AllowedClasses="/Script/Engine.SoundBase")) TMap<FName, FSoftObjectPath> SoundEffectOverrides;'), [])

    def test_each_class_metadata_key_requires_a_long_path(self):
        for key in ("AllowedClasses", "DisallowedClasses", "MetaClass", "MustImplement"):
            with self.subTest(key=key):
                failures = self.failures(f'UPROPERTY(meta=({key}="Actor")) FSoftObjectPath Value;')
                self.assertEqual(len(failures), 1)
                self.assertIn(key, failures[0][1])

    def test_native_blueprint_and_plugin_long_class_paths_are_allowed(self):
        for path in ("/Script/Engine.SoundBase", "/Game/Audio/BP_Sound.BP_Sound_C", "/DigimonVenomNXT/Care/BP_Care.BP_Care_C"):
            for key in ("AllowedClasses", "DisallowedClasses", "MetaClass", "MustImplement"):
                with self.subTest(key=key, path=path):
                    self.assertEqual(self.failures(f'UPROPERTY(meta=({key}="{path}")) FSoftObjectPath Value;'), [])

    def test_class_lists_check_each_entry_and_trim_spaces(self):
        for key in ("AllowedClasses", "DisallowedClasses"):
            with self.subTest(key=key):
                self.assertEqual(self.failures(f'UPROPERTY(meta=({key}=" /Script/Engine.SoundBase , /Game/Audio/BP_Sound.BP_Sound_C ")) FSoftObjectPath Value;'), [])
                failures = self.failures(f'UPROPERTY(meta=({key}="/Script/Engine.SoundBase, SoundWave, /Script/Engine.SoundCue")) FSoftObjectPath Value;')
                self.assertEqual(len(failures), 1)
                self.assertIn("'SoundWave'", failures[0][1])

    def test_missing_package_or_object_path_is_rejected(self):
        for path in ("SoundBase", "Engine.SoundBase", "/Script/Engine", "/SoundBase", ""):
            with self.subTest(path=path):
                self.assertEqual(len(self.failures(f'UPROPERTY(meta=(AllowedClasses="{path}")) FSoftObjectPath Value;')), 1)

    def test_multiline_metadata_reports_key_line(self):
        failures = self.failures('UPROPERTY(EditAnywhere,\n  meta=(\n    ToolTip="Comma, parentheses (here)",\n    AllowedClasses =\n      "SoundBase",\n    DisallowedClasses="SoundWave"\n  )) FSoftObjectPath Value;')
        self.assertEqual([line for line, _ in failures], [4, 6])

    def test_comments_around_literal_and_key_do_not_hide_failure(self):
        source = 'UPROPERTY(meta=(/* before key */ AllowedClasses /* equals */ =\n/* before value */ "SoundBase" /* after value */)) FSoftObjectPath Value;'
        failures = self.failures(source)
        self.assertEqual(len(failures), 1)
        self.assertEqual(failures[0][0], 1)

    def test_metadata_in_comments_and_ordinary_or_raw_strings_is_ignored(self):
        source = r'''
            // UPROPERTY(meta=(AllowedClasses="SoundBase")) FSoftObjectPath Example;
            /* UPROPERTY(meta=(MetaClass="Actor")) FSoftObjectPath Example; */
            const char* Example = "UPROPERTY(meta=(AllowedClasses=\"SoundBase\"))";
            const char* Raw = R"sample(UPROPERTY(meta=(MustImplement="Interface")))sample";
            UPROPERTY(EditAnywhere) FSoftObjectPath RealValue;
        '''
        self.assertEqual(self.failures(source), [])

    def test_dynamic_class_callbacks_and_other_metadata_are_ignored(self):
        source = 'UPROPERTY(meta=(GetAllowedClasses="GetSupportedSounds", GetDisallowedClasses="GetBannedSounds", DisplayName="SoundBase", AllowedTypes="SoundBase", ToolTip="AllowedClasses=\\\"SoundBase\\\"")) FSoftObjectPath Value;'
        self.assertEqual(self.failures(source), [])

    def test_non_reflected_metadata_and_nested_tooltip_tokens_are_ignored(self):
        self.assertEqual(self.failures('void Example() { Metadata(meta=(AllowedClasses="SoundBase")); }\nUPROPERTY(Category="SoundBase", meta=(ToolTip=(AllowedClasses="SoundBase"))) FSoftObjectPath Value;'), [])

    def test_nonliteral_class_value_is_not_guessed(self):
        self.assertEqual(self.failures('UPROPERTY(meta=(AllowedClasses=AllowedClassName)) FSoftObjectPath Value;'), [])

    def test_reflected_class_and_function_metadata_are_checked(self):
        failures = self.failures('UCLASS(meta=(MustImplement="Interface")) class UExample {};\nUFUNCTION(meta=(MetaClass="Actor")) void Use();')
        self.assertEqual([line for line, _ in failures], [1, 2])


class ActorRoleShadowTests(unittest.TestCase):
    def shadows(self, source):
        code, errors = mask_cpp(source)
        self.assertEqual(errors, [])
        return actor_role_shadows(code)

    def test_reported_actor_local_is_rejected(self):
        source = 'bool ADigimonVenomNXTRelayScene::InitializeFor(AController* Controller) { const FString Role = NPC.Role == EDigimonRelayRole::Gym ? TEXT("DIGIGYM") : TEXT("STORY"); AddLabel(Location, Role); return true; }'
        self.assertEqual(len(self.shadows(source)), 1)

    def test_descriptive_local_keeps_data_role_valid(self):
        source = 'bool ADigimonVenomNXTRelayScene::InitializeFor(AController* Controller) { const FString NPCRoleLabel = NPC.Role == EDigimonRelayRole::Gym ? TEXT("DIGIGYM") : TEXT("STORY"); AddLabel(Location, NPCRoleLabel); return true; }'
        self.assertEqual(self.shadows(source), [])

    def test_namespace_helper_is_not_an_actor_member(self):
        self.assertEqual(self.shadows('namespace UI { FString Label(EDigimonRelayRole Role) { return FString(); } }'), [])

    def test_comments_and_strings_do_not_create_declarations(self):
        self.assertEqual(self.shadows('void ADigimonVenomNXTRelayScene::Tick(float DeltaSeconds) { /* FString Role = X; */ SetLabel(TEXT("FString Role = X;")); }'), [])


class ControllerMemberShadowTests(unittest.TestCase):
    def shadows(self, source):
        code, errors = mask_cpp(source)
        self.assertEqual(errors, [])
        return controller_member_shadows(code)

    def test_reported_range_loop_and_local_are_rejected(self):
        source = 'void ADigimonVenomNXTPlayerController::PrepareHostWorldRestart() { for (ADigimonVenomNXTPlayerController* Player : Players) { Player->Save(); } ADigimonVenomNXTPlayerController* Player = Entry; }'
        self.assertEqual([name for _, name in self.shadows(source)], ['Player', 'Player'])

    def test_pawn_parameter_and_nested_if_initializer_are_rejected(self):
        source = 'void ADigimonVenomNXTPlayerController::Test(APawn* Pawn) { if (const auto* Player = Find()) { Consume(Player); } }'
        self.assertEqual([name for _, name in self.shadows(source)], ['Pawn', 'Player'])

    def test_renamed_session_controller_is_allowed(self):
        source = 'void ADigimonVenomNXTPlayerController::PrepareHostWorldRestart() { for (ADigimonVenomNXTPlayerController* SessionController : Players) { SessionController->Save(); } }'
        self.assertEqual(self.shadows(source), [])

    def test_namespace_helper_and_other_class_are_allowed(self):
        source = 'namespace Session { bool Preserve(AController* Player) { return Player; } } void UOther::Test() { AController* Player = Get(); }'
        self.assertEqual(self.shadows(source), [])

    def test_existing_inherited_member_access_is_allowed(self):
        source = 'UPlayer* ADigimonVenomNXTPlayerController::Test() { Consume(Player); this->Player = Other->Player; return Player; }'
        self.assertEqual(self.shadows(source), [])

    def test_comments_and_strings_are_ignored(self):
        source = 'void ADigimonVenomNXTPlayerController::Test() { /* APawn* Pawn = Get(); */ Log(TEXT("AController* Player = X;")); }'
        self.assertEqual(self.shadows(source), [])


class NetworkContainerTests(unittest.TestCase):
    def failures(self, **sources):
        masked_files = {}
        for name, source in sources.items():
            code, errors = mask_cpp(source)
            self.assertEqual(errors, [])
            masked_files[Path(name + ".h")] = code
        return network_container_errors(masked_files)

    BAD_PROGRESS = '''
        USTRUCT(BlueprintType)
        struct DIGIMONVENOMNXTRUNTIME_API FDigimonRelayProgress {
            GENERATED_BODY()
            UPROPERTY() TMap<FName, int32> QuestCounters;
        };
    '''

    def test_reported_nested_map_in_replicated_profile_is_rejected(self):
        failures = self.failures(Types=self.BAD_PROGRESS + '''
            USTRUCT(BlueprintType) struct FDigimonProfile {
                GENERATED_BODY()
                UPROPERTY() FDigimonRelayProgress Chronicles;
            };
        ''', PlayerState='''
            UCLASS() class APlayerState {
                GENERATED_BODY()
                UPROPERTY(ReplicatedUsing=OnRep_Profile, Category="Accounts")
                FDigimonProfile Profile;
            };
        ''')
        self.assertEqual(len(failures), 1)
        self.assertIn("replicated property Profile -> FDigimonProfile.Chronicles -> FDigimonRelayProgress.QuestCounters", failures[0])
        self.assertIn("unsupported TMap", failures[0])

    def test_reported_map_in_client_rpc_is_rejected(self):
        failures = self.failures(Types=self.BAD_PROGRESS, Controller='''
            UCLASS() class AController {
                GENERATED_BODY()
                UFUNCTION(Client, Reliable, Category="Relay")
                void ClientShowRelayDialogue(FName NPCId, const FString& Dialogue,
                    EDigimonPrivateCampaign Campaign, const FDigimonRelayProgress& ConfirmedProgress);
            };
        ''')
        self.assertEqual(len(failures), 1)
        self.assertIn("RPC ClientShowRelayDialogue parameter ConfirmedProgress -> FDigimonRelayProgress.QuestCounters", failures[0])

    def test_nested_array_struct_map_is_rejected(self):
        failures = self.failures(Types='''
            USTRUCT() struct FQuest { GENERATED_BODY() UPROPERTY() TMap<FName, int32> Values; };
            USTRUCT() struct FChapter { GENERATED_BODY() UPROPERTY() TArray<FQuest> Quests; };
            USTRUCT() struct FProgress { GENERATED_BODY() UPROPERTY() TArray<FChapter> Chapters; };
            UCLASS() class AState { GENERATED_BODY() UPROPERTY(Replicated) FProgress Progress; };
        ''')
        self.assertEqual(len(failures), 1)
        self.assertIn("Progress -> FProgress.Chapters -> FChapter.Quests -> FQuest.Values", failures[0])

    def test_array_of_counter_structs_is_safe(self):
        self.assertEqual(self.failures(Types='''
            USTRUCT() struct FQuestCounter {
                GENERATED_BODY()
                UPROPERTY() FName QuestId;
                UPROPERTY() int32 Count = 0;
            };
            USTRUCT() struct FProgress {
                GENERATED_BODY()
                UPROPERTY() TArray<FQuestCounter> QuestCounters;
            };
            UCLASS() class AState {
                GENERATED_BODY()
                UPROPERTY(Replicated) FProgress Progress;
                UFUNCTION(Client, Reliable) void ClientConfirm(const FProgress& ConfirmedProgress);
            };
        '''), [])

    def test_server_only_reflected_map_is_allowed(self):
        self.assertEqual(self.failures(Types=self.BAD_PROGRESS + '''
            USTRUCT() struct FDigimonRankedSave {
                GENERATED_BODY()
                UPROPERTY() TMap<FString, int32> PendingRubyRewards;
            };
            UCLASS() class UServerStore {
                GENERATED_BODY()
                UPROPERTY() FDigimonRankedSave Save;
                UPROPERTY(Replicated) int32 Count = 0;
                UFUNCTION(BlueprintCallable) void LocalUse(const FDigimonRelayProgress& Progress);
            };
        '''), [])

    def test_server_and_multicast_set_parameters_are_rejected(self):
        failures = self.failures(Controller='''
            USTRUCT() struct FRequest { GENERATED_BODY() UPROPERTY() TSet<FName> Ids; };
            UCLASS() class AController {
                GENERATED_BODY()
                UFUNCTION(Server, Reliable) void ServerRequest(const FRequest& Request);
                UFUNCTION(NetMulticast, Reliable) void Broadcast(const TSet<FName>& Ids);
            };
        ''')
        self.assertEqual(len(failures), 2)
        self.assertTrue(all("unsupported TSet" in failure for failure in failures))

    def test_template_comma_does_not_split_direct_map_rpc_parameter(self):
        failures = self.failures(Controller='''
            UCLASS() class AController {
                GENERATED_BODY()
                UFUNCTION(Server, Reliable) void ServerUpdate(const TMap<FName, int32>& Counters, bool bReset);
            };
        ''')
        self.assertEqual(len(failures), 1)
        self.assertIn("RPC ServerUpdate parameter Counters contains unsupported TMap", failures[0])

if __name__ == '__main__':
    unittest.main()
