#pragma once

#include "CoreMinimal.h"
#include "Data/Items/UsableItems/MC_DT_UsableItemConfig.h"
#include "MC_DT_MiningToolItemConfig.generated.h"

/** This class contains information about mining tools such as pickaxes, axes, knives, etc. */
UCLASS()
class MINECORE_API UMC_DT_MiningToolItemConfig : public UMC_DT_UsableItemConfig
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual FPrimaryAssetId GetPrimaryAssetId() const override { return Super::GetPrimaryAssetId(); }
};
