#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/MC_InventoryComponent.h"
#include "Data/Item/MC_ItemConfig.h"
#include "MC_LogChannels.h"
#include "MC_MiningSystemComponent.generated.h"

class UMC_Pickaxe;
enum class EItemTier : uint8;

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
	
	/** This function attempts to find the best item in the Inventory. */
	template<typename ItemClass>
	ItemClass* FindBestItemInInventory() const;

	/** This function checks if the player is able to mine the resource node */
	//UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Mining System Component")
	//bool CanPlayerMine()

protected:
	/** Cached pointer to pickaxe (the best pickaxe in the inventory). It can be nullptr when player doesn't have any pickaxe in the inventory */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TWeakObjectPtr<UMC_Pickaxe> CachedPickaxe;
	
	/** Cached pointer to the inventory component. It should never be nullptr. */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;
};

template <typename ItemClass>
ItemClass* UMC_MiningSystemComponent::FindBestItemInInventory() const
{
	// Inventory should never be nullptr!
	TArray<ItemClass*> Items;

	// Retrieve all Items of given class from the inventory
	InventoryComponent->FindItemsByClass<ItemClass>(Items);

	// If no items are found, return nullptr
	if (Items.Num() == 0)
	{
		UE_LOGFMT(LogMiningSystem, Warning, "Inventory doesn't contain the requested item. File: {0}, Line: {1}", __FILE__, __LINE__);
		return nullptr;
	}

	// Assuming Tier1 is the lowest tier
	ItemClass* BestItem = nullptr;
	EItemTier HighestTier = EItemTier::Tier1;
	
	// Iterate through all items to find the one with the highest tier
	for (ItemClass* Item : Items)
	{
		if (Item->GetItemConfig()->ItemTier > HighestTier)
		{
			BestItem = Item;
			HighestTier = BestItem->GetItemConfig()->ItemTier;
		}
	}
	
	return BestItem;
}
