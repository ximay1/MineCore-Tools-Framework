#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MC_InventoryHelperLibrary.generated.h"

/** Forward Declarations */
class UMC_Item;

UCLASS()
class MINECORE_API UMC_InventoryHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Checks if two items can be stacked (same type and stackable). */
	UFUNCTION(BlueprintGetter, Category = "Inventory Helper Library")
	static bool CanItemsStack(const UMC_Item* ItemA, const UMC_Item* ItemB);
	
	/** Returns remaining stack capacity of an item (MaxStack - CurrentStack). */
	UFUNCTION(BlueprintGetter, Category = "Inventory Helper Library")
	static int32 GetRemainingStackSpace(const UMC_Item* ItemA);

	/** Finds all items matching a given ItemDefinition in the inventory. */
	UFUNCTION(BlueprintGetter, Category = "Inventory Helper Library")
	static void FindItemsByDefinition(const UMC_InventoryComponent* InventoryComponent, const FItemDefinition& ItemDefinition, TArray<FInventorySlot>& OutItems);

	/** Returns true if all inventory slots are occupied. */
	UFUNCTION(BlueprintGetter, Category = "Inventory Helper Library")
	static bool IsInventoryFull(const UMC_InventoryComponent* InventoryComponent);

	/** Serializes inventory data into a JSON. */
	UFUNCTION(Blueprintcallable, Category = "Inventory Helper Library")
	static void ConvertInventoryToJSON(const APlayerController* const PlayerController);
	
	/** Calculates the total weight of all items (if they have weight). */
	UFUNCTION(Blueprintcallable, Category = "Inventory Helper Library")
	static float CalculateTotalWeight(const UMC_InventoryComponent* const InventoryComponent);
};
