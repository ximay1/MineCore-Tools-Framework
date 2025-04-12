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
};
