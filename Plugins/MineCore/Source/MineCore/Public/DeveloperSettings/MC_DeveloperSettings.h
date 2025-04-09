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
	
	//~ Begin UDeveloperSettings interface
	virtual FName GetCategoryName() const;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	//~ End UDeveloperSettings interface
};
