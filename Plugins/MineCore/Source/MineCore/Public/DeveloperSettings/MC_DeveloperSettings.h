#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MC_DeveloperSettings.generated.h"

UCLASS(Config = Game, DefaultConfig)
class MINECORE_API UMC_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Constructor */
	UMC_DeveloperSettings();
	
	//~ Begin UDeveloperSettings interface
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	//~ End UDeveloperSettings interface

	/** Path to the directory containing all Primary Data Assets that inherit from UMC_DT_ItemConfig class. */
	UPROPERTY(Config, EditAnywhere, Category = "Mine Core Settings")
	FString PathToItemsPrimaryDataAssets;

	/** Defines a custom PrimaryAssetType for item classification. When empty (default), uses the PrimaryAssetType defined in UMC_DT_ItemConfig class. */
	UPROPERTY(Config, EditAnywhere, Category = "Mine Core Settings")
	FPrimaryAssetType PrimaryAssetType;
};
