#pragma once

#include "CoreMinimal.h"
#include "Data/Items/MC_ItemConfig.h"
#include "MC_UsableItemConfig.generated.h"

/** Base class for usable items that have durability, such as weapons, tools, and armors. */
UCLASS()
class MINECORE_API UMC_UsableItemConfig : public UMC_ItemConfig
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("UsableItemConfig", GetFName()); }

	/** The maximum durability the item can have. Must be greater than 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Usable Item", meta = (ClampMin = "0.01"))
	float MaxDurability = 1.0f;
};
