#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ItemBag.generated.h"

/** Forward Declarations */
class UMC_InventoryComponent;

/** Contains all initialization data for an ItemBag actor */
USTRUCT(BlueprintType)
struct FItemBagDefinition
{
	GENERATED_BODY()
	
	/** Physical mesh representing the bag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> BagMesh;
};

UCLASS()
class MINECORE_API AMC_ItemBag : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	AMC_ItemBag();

	/** Initializes bag with random items based on weight parameters */
	UFUNCTION(BlueprintCallable, Category = "Item Bag")
	virtual void Server_InitializeRandomizedBag(const FItemBagDefinition& Params);

	/** Initializes bag with predefined items (no randomization) */ 
	UFUNCTION(BlueprintCallable, Category = "Item Bag")
	virtual void Server_InitializeBagWithItems(const FItemBagDefinition& Params, const TArray<UMC_DT_ItemConfig*>& SpecificItems);
	
	/** Initializes item bag using either random items or predefined list based on bShouldRandomize */
	UFUNCTION(BlueprintCallable, Category = "Item Bag")
	virtual void Server_InitializeItemBag(const FItemBagDefinition& Params, const bool bShouldRandomize, const TArray<UMC_DT_ItemConfig*>& SpecificItems);
	
	/** Get InventoryComponent */
	UFUNCTION(BlueprintGetter, Category = "Item Bag")
	FORCEINLINE UMC_InventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	/** Get BagMeshComponent */
	UFUNCTION(BlueprintGetter, Category = "Item Bag")
	FORCEINLINE UStaticMeshComponent* GetBagMeshComponent() { return BagMeshComponent; }

protected:
	/** Events */
	virtual void BeginPlay() override;

	/** Primary inventory system attached to this bag item. Handles all item storage and transfer operations */
	UPROPERTY(BlueprintReadOnly, Category = "Item Bag")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;

	/** Visual representation of the bag in the game world. */
	UPROPERTY(BlueprintReadOnly, Category = "Item Bag")
	TObjectPtr<UStaticMeshComponent> BagMeshComponent;
};
