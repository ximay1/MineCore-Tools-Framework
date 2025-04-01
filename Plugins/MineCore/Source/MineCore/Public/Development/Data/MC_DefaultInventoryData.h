#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/Items/MC_ItemConfig.h"
#include "MC_DefaultInventoryData.generated.h"

/**
 * Represents a single item in the default inventory configuration
 * Used only for editor-time inventory setup
 */
USTRUCT()
struct FDefaultInventoryItem
{
	GENERATED_BODY()

public:

	/** The item's data asset reference containing all item properties */
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Tooltip = "Reference to the item's data asset"))
	TObjectPtr<UMC_ItemConfig> ItemData;

	/** The inventory slot where this item should be placed */
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Tooltip = "Default slot index for this item"))
	uint8 Slot;
};

/**
 * Data asset containing the default inventory configuration
 * Used to set up starting inventory for characters/players
 */
UCLASS()
class MINECORE_API UMC_DefaultInventoryData : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Array of items that should be included in the default inventory */
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Tooltip = "List of items in default inventory"))
	TArray<FDefaultInventoryItem> DefaultItems;
};