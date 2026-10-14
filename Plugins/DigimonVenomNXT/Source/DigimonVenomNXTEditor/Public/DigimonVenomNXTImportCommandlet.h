#pragma once
#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "DigimonVenomNXTImportCommandlet.generated.h"

/** Headless native-content authoring for Tools/Build_Windows.bat -ImportContent. */
UCLASS()
class DIGIMONVENOMNXTEDITOR_API UDigimonVenomNXTImportCommandlet : public UCommandlet
{
    GENERATED_BODY()
public:
    UDigimonVenomNXTImportCommandlet();
    virtual int32 Main(const FString& Params) override;
};
