// Tests production evolution arithmetic and identity-preserving transforms directly.
// UE widgets, replication, profile persistence and runtime registry loading still
// require an Unreal engine smoke test; these are not simulated here.
#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTEvolutionCore.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace
{
int Checks = 0;
void Require(bool Condition, const char* Message)
{
    ++Checks;
    if (!Condition) { std::cerr << "FAIL: " << Message << '\n'; std::exit(1); }
}
namespace Rules = DigimonVenomNXTEvolutionCore;

void TestEvolutionGates()
{
    Require(!Rules::MeetsRequirements(1, 100, 200, 1, 0, 0), "level one can never transform immediately again");
    Require(!Rules::MeetsRequirements(100, 9, 200, 5, 10, 0), "early-stage friendship is a real gate even at maximum level");
    Require(Rules::MeetsRequirements(5, 10, 0, 5, 10, 0), "early-stage exact level and CAM requirement can evolve with zero ABI");
    Require(!Rules::MeetsRequirements(100, 100, 9, 20, 20, 10), "Champion evolution cannot bypass ABI by overlevelling");
    Require(!Rules::MeetsRequirements(19, 100, 200, 20, 20, 10), "extra ABI cannot bypass level requirement");
    Require(!Rules::MeetsRequirements(20, 19, 200, 20, 20, 10), "extra ABI cannot bypass friendship requirement");
    Require(Rules::MeetsRequirements(20, 20, 10, 20, 20, 10), "exact Champion boundaries are accepted");
    Require(!Rules::MeetsRequirements(100, 100, 59, 55, 60, 60), "Mega evolution needs developed ABI");
    Require(Rules::MeetsRequirements(55, 60, 60, 55, 60, 60), "exact Mega boundaries are accepted");
    Require(Rules::MeetsRequirements(2, 0, 0, -10, -10, -10), "bad negative authored minima cannot demand negative stats");
}

void TestABIGrowth()
{
    for (int Tier = 0; Tier <= 7; ++Tier)
    {
        Require(Rules::ABIGain(Tier, 1, false) == 0 && Rules::ABIGain(Tier, 1, true) == 0,
            "freshly transformed partners cannot earn free ABI from form cycling");
        Require(Rules::ABIGain(Tier, 4, true) == 0 && Rules::ABIGain(Tier, 5, true) > 0,
            "de-evolution requires the configured amount of retraining");
        Require(Rules::ABIGain(Tier, 20, true) > Rules::ABIGain(Tier, 20, false),
            "default de-evolution awards more ABI than evolution at equal stage and level");
        Require(Rules::ABIGain(Tier, 100, true) >= Rules::ABIGain(Tier, 20, true),
            "training to higher level never reduces de-evolution ABI");
    }
    Require(Rules::ABIGain(2, 20, false) == 4, "Rookie level twenty forward ABI uses pre-change level");
    Require(Rules::ABIGain(3, 20, true) == 9, "Champion level twenty reverse ABI uses pre-change level");
    Require(Rules::ResultABI(199, 9) == 200, "ABI gains stop at the permanent cap");
    Require(Rules::ResultABI(200, 9) == 200, "already-capped ABI cannot increase");
    Require(Rules::ResultABI(-1, 2) == 2, "legacy negative ABI is safely repaired");
    Require(Rules::ResultABI(10, -1) == 10, "negative gain cannot take away earned ABI");
    Require(Rules::ResultABI(INT_MAX, INT_MAX) == INT_MAX, "above-cap saved ABI remains intact without addition overflow");
    Require(Rules::ResultABI(90, 20, 100) == 100, "a lower configured ABI cap is respected");
    Require(Rules::ResultABI(150, 20, 100) == 150, "lowering configured cap cannot erase permanent ABI already earned");
    Require(Rules::ResultABI(999, 20, 200) == 999, "legacy ABI above the new supported earning cap is preserved");
    Rules::Rules Config;
    Config.MinimumDeEvolutionLevel = 1;
    Config.EvolutionBaseABI = INT_MAX;
    Config.DeEvolutionBaseABI = INT_MAX;
    Config.EvolutionLevelsPerABI = 0;
    Config.DeEvolutionLevelsPerABI = -1;
    Require(Rules::MinimumChangeLevel(true, Config) == 2 && Rules::ABIGain(7, 1, true, Config) == 0,
        "unsafe custom settings cannot enable level-one farming");
    Require(Rules::ABIGain(INT_MAX, INT_MAX, true, Config) == 200,
        "custom gain, stage and level inputs remain bounded without division by zero");
    Config.MinimumDeEvolutionLevel = 20;
    Require(Rules::ABIGain(3, 19, true, Config) == 0 && Rules::ABIGain(3, 20, true, Config) > 0,
        "custom de-evolution minimum is honored exactly");
}

void TestABITrainingCapacity()
{
    Require(Rules::TrainingCapacity(0) == 300 && Rules::TrainingCapacity(200) == 300,
        "Venom training budget is 300 regardless of ABI");
    Require(Rules::TrainingUsedTenths(5, 0, 0, 0, 0, 0) == 50, "HP uses the same training budget as every stat");
    Require(Rules::TrainingUsedTenths(0, 2, 1, 1, 1, 1) == 60, "all six bonuses count toward the budget");
    Require(Rules::TrainingUsedTenths(-10, -1, -1, -1, -1, -1) == 0, "negative bonuses cannot create credit");
    Require(Rules::TrainingUsedTenths(INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX) ==
        static_cast<std::int64_t>(INT_MAX) * 60, "training sum uses wide arithmetic");
    Require(Rules::CanTrain(0, 2990, 10) && !Rules::CanTrain(200, 2991, 10), "shared 300-point boundary applies exactly");
    Require(Rules::CanTrain(0, 2950, 50) && !Rules::CanTrain(0, 2960, 50), "rare +5 meat cannot overshoot shared cap");
    Require(Rules::CanTrainStat(99,1) && !Rules::CanTrainStat(100,1), "per-stat limit is 100");
    Require(Rules::CanTrainStat(95,5) && !Rules::CanTrainStat(96,5), "rare meat is not partially consumed near stat cap");
    Require(!Rules::CanTrainStat(-1,1) && !Rules::CanTrainStat(0,0) && !Rules::CanTrainStat(INT_MAX,1), "invalid stat training fails");
    Require(!Rules::CanTrain(200, INT64_MAX, INT_MAX), "overflow-sized additions are rejected");
    Require(!Rules::CanTrain(0, -1, 1) && !Rules::CanTrain(0, 0, 0) && !Rules::CanTrain(0, 0, -1), "invalid budget requests fail");
}

struct Partner
{
    std::string SpeciesId = "rookie";
    int Level = 20;
    std::int64_t Experience = 9999;
    int ABI = 10;
    std::string InstanceId = "stable-instance";
    int Variant = 2;
    std::string Nickname = "Spark";
    int CAM = 42;
    std::vector<int> PermanentTraining{5, 2, 1, 3, 4, 7};
    std::vector<std::string> Moves{"spark", "guard"};
};

void TestTransformationRetention()
{
    Partner Value;
    const Partner Before = Value;
    const int Gain = Rules::ABIGain(2, Value.Level, false);
    Rules::ApplyIdentityPreservingTransform(Value, std::string("champion"), Rules::ResultABI(Value.ABI, Gain));
    Require(Value.SpeciesId == "champion" && Value.Level == 1 && Value.Experience == 0,
        "evolution changes form and resets both level and XP");
    Require(Value.ABI == 14, "ABI growth is applied before pre-change level is reset");
    Require(Value.InstanceId == Before.InstanceId && Value.Variant == Before.Variant && Value.Nickname == Before.Nickname,
        "ownership identity, rare variant and player nickname survive evolution");
    Require(Value.CAM == Before.CAM && Value.PermanentTraining == Before.PermanentTraining && Value.Moves == Before.Moves,
        "friendship, all permanent training and equipped moves survive evolution");
    Require(Rules::ABIGain(3, Value.Level, true) == 0,
        "newly evolved Champion cannot immediately reverse for ABI");
    Value.Level = 5; Value.Experience = 1234;
    Rules::ApplyIdentityPreservingTransform(Value, std::string("rookie"),
        Rules::ResultABI(Value.ABI, Rules::ABIGain(3, Value.Level, true)));
    Require(Value.SpeciesId == "rookie" && Value.Level == 1 && Value.Experience == 0 && Value.ABI == 20,
        "trained de-evolution resets progression while accumulating permanent ABI");
    Require(Value.InstanceId == Before.InstanceId && Value.CAM == Before.CAM &&
        Value.PermanentTraining == Before.PermanentTraining && Value.Moves == Before.Moves,
        "reverse evolution preserves identity and development for the next cycle");
    Value.ABI = 999;
    Rules::ApplyIdentityPreservingTransform(Value, std::string("champion"), Rules::ResultABI(Value.ABI, 5, 100));
    Require(Value.ABI == 999 && Value.Level == 1 && Value.Experience == 0,
        "transforming with a lowered earning cap retains every saved permanent ABI point");
}
}

int main()
{
    TestEvolutionGates(); TestABIGrowth(); TestABITrainingCapacity(); TestTransformationRetention();
    std::cout << "Evolution core: " << Checks << " checks passed.\n";
}
