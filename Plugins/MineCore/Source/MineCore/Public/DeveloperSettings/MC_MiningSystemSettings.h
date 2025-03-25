#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Items/MC_Item.h"
#include "MC_MiningSystemSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Mining System Settings"))
class MINECORE_API UMC_MiningSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	/** List of classes that should be searched in the inventory during BeginPlay in MC_MiningSystemComponent, for example, to cache mining tools. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Mining System Settings")
	TArray<TSoftClassPtr<UMC_Item>> ItemClassesToCache;
};
