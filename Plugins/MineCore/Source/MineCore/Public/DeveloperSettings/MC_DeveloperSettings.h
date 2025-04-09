#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MC_DeveloperSettings.generated.h"

UCLASS(Config = game, DefaultConfig)
class MINECORE_API UMC_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Constructor */
	UMC_DeveloperSettings();
};
