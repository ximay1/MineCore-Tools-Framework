#pragma once

#include "CoreMinimal.h"
#include "Data/Items/MC_ItemConfig.h"
#include "MC_UsableItemConfig.generated.h"

/** Base class for usable items. These items can have durability, but it is not required. Examples: weapons, tools, armor, potions. */
UCLASS()
class MINECORE_API UMC_UsableItemConfig : public UMC_ItemConfig
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("UsableItemConfig", GetFName()); }

	/** The maximum durability the item can have. Must be greater than 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Usable Item", meta = (ClampMin = "0.01", InlineEditConditionToggle))
	float MaxDurability = 1.0f;
};
