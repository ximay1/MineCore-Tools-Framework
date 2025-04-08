#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ItemBag.generated.h"

/** Forward Declarations */
class UMC_InventoryComponent;

UCLASS()
class MINECORE_API AMC_ItemBag : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	AMC_ItemBag();

	/** Get InventoryComponent */
	UFUNCTION(BlueprintGetter, Category = "Item Bag")
	FORCEINLINE UMC_InventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	/** Get BagMeshComponent */
	UFUNCTION(BlueprintGetter, Category = "Item Bag")
	FORCEINLINE UStaticMeshComponent* GetBagMeshComponent() { return BagMeshComponent; }
	
protected:
	/** Primary inventory system attached to this bag item. Handles all item storage and transfer operations */
	UPROPERTY(BlueprintReadOnly, Category = "Item Bag")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;

	/** Visual representation of the bag in the game world. */
	UPROPERTY(BlueprintReadOnly, Category = "Item Bag")
	TObjectPtr<UStaticMeshComponent> BagMeshComponent;
};
