#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_MiningSystemComponent.generated.h"

class UMC_Pickaxe;
class UMC_InventoryComponent;

UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_MiningSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Constructor
	UMC_MiningSystemComponent();

	/** Events */
	virtual void BeginPlay() override;
	
	/** This function attempts to find the inventory component. */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	UMC_InventoryComponent* FindInventory() const;
	
	/** This function attempts to find a Pickaxe in the Inventory. */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	UMC_Pickaxe* FindPickaxeInInventory() const;

protected:
	/** Cached pointer to pickaxe (the best pickaxe in the inventory). It can be nullptr when player doesn't have any pickaxe in the inventory */
	TWeakObjectPtr<UMC_Pickaxe> CachedPickaxe;
	
	/** Cached pointer to the inventory component. It should never be nullptr. */
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;
};
