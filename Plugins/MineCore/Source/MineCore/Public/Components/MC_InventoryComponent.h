#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/MC_Item.h"
#include "MC_LogChannels.h"
#include "MineCore/Public/Data/Items/MC_ItemConfig.h"
#include "MC_InventoryComponent.generated.h"

class UMC_Item;

/** Enum representing possible actions that can be performed on an item. */
UENUM(BlueprintType)
enum class EItemAction : uint8
{
	Destroy UMETA(DisplayName = "Destroy"),  // Player wants to destroy the item
	Drop    UMETA(DisplayName = "Drop"),     // Player wants to drop the item
};

/** Triggered when an item is added (Slot number, Item). */  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedToInventory, uint8, Slot, UMC_Item*, Item);

/** Base class for the inventory system used in MineCore. */
UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// TODO: Change UUserWidget class to the base InventoryWidget class
	
public:	
	// Sets default values for this component's properties
	UMC_InventoryComponent();
	
	/** Creates the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void CreateInventory();

	/** Refresh Widget Inventory */
	void RefreshInventoryWidget();
	
	/** Adds an item to the inventory */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory Component")
	void AddItemToInventory(uint8 Slot, UMC_Item* Item);

	/** Removes an item from the inventory */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory Component")
	void RemoveItemFromInventory(uint8 Slot, EItemAction ItemAction);

	/** Get Items */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void GetItems(TArray<UMC_Item*>& ValuesArray) const { Items.GenerateValueArray(ValuesArray); }
	
	/** Checks if an item exists in the inventory. Returns UMC_Item if found, otherwise nullptr */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	FORCEINLINE UMC_Item* GetItemFromInventory(uint8 Slot) const { return Items.FindRef(Slot); }

	/** This function finds the items of given class in the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Componenet")
	void FindItemsByClass(const TSubclassOf<UMC_Item>& ItemClass, TArray<UMC_Item*>& OutItems) const;

	/** This function finds the items of given class in the inventory */
	template<typename ItemClass>
	void FindItemsByClass(TArray<ItemClass*>& OutItems) const;
	
	/** This function attempts to find the best item in the Inventory. */
	UMC_Item* FindBestItemInInventory(const TSubclassOf<UMC_Item>& ItemClass) const;

	/** This function attempts to find the best item in the Inventory. */
	template<typename ItemClass>
	ItemClass* FindBestItemInInventory() const;
	
	/** Drops the item as a bag at the player's location */
	void DropItem(uint8 Slot);
	void DropItem(UMC_Item* Item);
	
	/** Finds the first available (empty) slot in the inventory. Returns true if a valid slot is found, otherwise false. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	bool FindValidSlot(uint8& OutSlot) const;
	
	/** Get Max Slots */
	UFUNCTION(BlueprintGetter, Category = "Inventory Component")
	FORCEINLINE uint8 GetMaxSlots() const { return MaxSlots; }

public:
	//Delegates
	FOnItemAddedToInventory OnItemAddedToInventory;
	
protected:
	/** Widget class representing the Inventory */ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Component")
	TSubclassOf<UUserWidget> InventoryClass;

	/** Cached Pointer to the Inventory widget */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TObjectPtr<UUserWidget> InventoryWidget;

	/** Map of items in the inventory. uint8 represents a number of slot. */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TMap<uint8, UMC_Item*> Items;
	
	/** Maximum number of slots in the inventory */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", meta = (AllowPrivateAccess))
	uint8 MaxSlots;
};

template <typename ItemClass>
void UMC_InventoryComponent::FindItemsByClass(TArray<ItemClass*>& OutItems) const
{
	// Ensure that ItemClass is derived from UMC_Item
	static_assert(TPointerIsConvertibleFromTo<ItemClass, const UMC_Item>::Value, "'T' template parameter to FindItemsByClass must be derived from UMC_Item");

	// Clear the result array to avoid adding to any old data
	OutItems.Empty();

	// Iterate through all items in the inventory
	for (const auto& Pair : Items)
	{
		// Check if the item is of the specified class or derived class
		if (Pair.Value)
		{
			if (ItemClass* Item = Cast<ItemClass>(Pair.Value))
			{
				// If true, add the item to the result array
				OutItems.Add(Item);
			}
		}
	}
}

template <typename ItemClass>
ItemClass* UMC_InventoryComponent::FindBestItemInInventory() const
{
	// Inventory should never be nullptr!
    TArray<ItemClass*> OutItems;

    // Retrieve all Items of given class from the inventory
    FindItemsByClass<ItemClass>(OutItems);

    // If no items are found, return nullptr
    if (OutItems.Num() == 0)
    {
    	UE_LOGFMT(LogMiningSystem, Warning, "Inventory doesn't contain the requested item. File: {0}, Line: {1}", __FILE__, __LINE__);
    	return nullptr;
    }

    // Assuming Tier1 is the lowest tier
    ItemClass* BestItem = nullptr;
    EItemTier HighestTier = EItemTier::Tier1;
    
    // Iterate through all items to find the one with the highest tier
    for (ItemClass* Item : OutItems)
    {
    	if (Item->GetItemConfig()->ItemTier > HighestTier)
    	{
    		BestItem = Item;
    		HighestTier = BestItem->GetItemConfig()->ItemTier;
    	}
    }
    
    return BestItem;
}
