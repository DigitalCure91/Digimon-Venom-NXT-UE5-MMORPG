#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDigimonVenomNXTEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    FDelegateHandle EngineInitHandle;
    FDelegateHandle MenuStartupHandle;
    bool bInteractiveStarted = false;
    void InitializeEditor();
    void RegisterMenus();
};
