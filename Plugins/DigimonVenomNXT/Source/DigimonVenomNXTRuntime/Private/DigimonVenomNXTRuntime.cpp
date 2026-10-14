#include "DigimonVenomNXTRuntime.h"
#include "Modules/ModuleManager.h"
#include "DigimonVenomNXTCustomDepth.h"

DEFINE_LOG_CATEGORY(LogDigimonVenomNXT);

void FDigimonVenomNXTRuntimeModule::StartupModule()
{
    DigimonVenomNXTCustomDepth::EnsureRendererEnabled();
    UE_LOG(LogDigimonVenomNXT, Log, TEXT("Digimon Venom NXT runtime loaded (Custom Depth enabled with stencil support)."));
}

void FDigimonVenomNXTRuntimeModule::ShutdownModule() {}
IMPLEMENT_MODULE(FDigimonVenomNXTRuntimeModule, DigimonVenomNXTRuntime)
