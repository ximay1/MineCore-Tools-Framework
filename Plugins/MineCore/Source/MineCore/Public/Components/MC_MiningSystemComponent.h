#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/MC_InventoryComponent.h"
#include "MC_MiningSystemComponent.generated.h"

class UMC_Pickaxe;
class UMC_MiningTool;
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
	
	/** This function checks if the player is able to mine the resource node. Always called on the server! */
	bool CanPlayerMine(UMC_MiningTool* MiningTool);

	/** Get Pickaxe */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Pickaxe* GetPickaxe() { return CachedPickaxe.Get(); }

protected:
	/** Cached pointer to pickaxe (the best pickaxe in the inventory). It can be nullptr when player doesn't have any pickaxe in the inventory */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TWeakObjectPtr<UMC_Pickaxe> CachedPickaxe;
	
	/** Cached pointer to the inventory component. It should never be nullptr. */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;
	
	/** This function attempts to find the inventory component. */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	UMC_InventoryComponent* FindInventory() const;
};