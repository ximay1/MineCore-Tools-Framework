#include "Components/MC_InventoryComponent.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "MineCore/Public/Data/Items/MC_ItemConfig.h"
#include "MineCoreMacros.h"

FInventoryItemFilter::FInventoryItemFilter()
	: ItemClass(nullptr)
	, MinTier((EItemTier)0)
	, MaxTier((EItemTier)0)
	, ItemCategory((EItemCategory)0)
	, ItemRarity((EItemRarity)0)
	, bUseItemClass(false)
	, bUseMinTier(false)
	, bUseMaxTier(false)
	, bUseCategoryFilter(false)
	, bUseRarityFilter(false)
{
}

FInventoryItemFilter::FInventoryItemFilter(TSubclassOf<UMC_Item> InItemClass, EItemTier InMinTier, EItemTier InMaxTier, EItemCategory InItemCategory, EItemRarity InItemRarity)
	: ItemClass(InItemClass)
	, MinTier(InMinTier)
	, MaxTier(InMaxTier)
	, ItemCategory(InItemCategory)
	, ItemRarity(InItemRarity)
	, bUseItemClass(true)
	, bUseMinTier(true)
	, bUseMaxTier(true)
	, bUseCategoryFilter(true)
	, bUseRarityFilter(true)
{
}

UMC_InventoryComponent::UMC_InventoryComponent() : MaxSlots(40)
{
	//Set Parameters
	PrimaryComponentTick.bCanEverTick = false;
}

void UMC_InventoryComponent::CreateInventory()
{
	//TODO: Create Inventory
}

void UMC_InventoryComponent::RefreshInventoryWidget()
{
	/*if (InventoryWidget)
	{
		TODO: InventoryWidget->RefreshWidget()
	}*/
}

void UMC_InventoryComponent::AddItemToSlot_Implementation(uint8 Slot, UMC_Item* Item)
{
#if WITH_EDITOR
	// Declare a flag to track the validity of the slot and item
	bool bIsValid = true;

	// Validate both the slot and the item using the macro. If invalid, it will set bIsValid to false and log errors.
	VALIDATE_ITEM_AND_SLOT_RETURN(Slot, MaxSlots, Item, bIsValid)

	// If both slot and item aren't valid, exit the function early.
	if (!bIsValid)
		return;
#endif
	
	//Check if there is something on that slot
	if (GetItemFromInventory(Slot) != nullptr)
	{
		//Find next valid slot
		if (FindValidSlot(Slot))
		{
			//Add to the inventory
			Items.Add(Slot, Item);

			//Call delegate
			OnItemAddedToInventory.Broadcast(Slot, Item);
		}
		else
		{
			// Drop the item from the inventory using the given item
			DropItemInstance(Item);
			
			UE_LOGFMT(LogInventory, Log, "We need to create a bag of items at the player's location when attempting to add an item to the inventory");
		}
	}
	else
	{
		//Add to the inventory
		Items.Add(Slot, Item);

		//Call delegate
		OnItemAddedToInventory.Broadcast(Slot, Item);
	}
	
	// Refresh the inventory widget to reflect the changes
	RefreshInventoryWidget();
}

void UMC_InventoryComponent::AddItemToFirstAvailableSlot_Implementation(UMC_Item* Item)
{
	
}

void UMC_InventoryComponent::RemoveItemFromInventory_Implementation(uint8 Slot, EItemAction ItemAction)
{
#if WITH_EDITOR
	// Declare a flag to track the validity of the slot
	bool bIsValid = true;

	// Validate the slot number using the macro; if invalid, it will log an error and set bIsValid to false
	VALIDATE_SLOT_AND_RETURN(Slot, MaxSlots, bIsValid)

	// If the slot is not valid, exit the function early
	if (!bIsValid)
		return;
#endif


	// Perform the assigned action based on the ItemAction enum
	switch (ItemAction)
	{
		case EItemAction::Destroy:
			{
				// Find the item in the inventory map using the given slot
				if (UMC_Item* ItemToDestroy = Items.FindRef(Slot))
				{
					// Start destroying the item by calling BeginDestroy()
					ItemToDestroy->BeginDestroy();

					// Remove the item from the inventory map
					Items.Remove(Slot);

					// Refresh the inventory widget to reflect the changes
					RefreshInventoryWidget();
				}
				else
				{
					// Log Error
					UE_LOGFMT(LogInventory, Error, "We wanted to destroy the item which doesn't exist in the inventory, we passed an invalid slot. File - {0}, Line - {1}", __FILE__, __LINE__);
				}

				break;
			}
		case EItemAction::Drop:
			{
				// Drop the item from the inventory using the given slot
				DropItemBySlot(Slot);
				
				break;
			}
	};

	// Refresh the inventory widget to reflect the changes
	RefreshInventoryWidget();
}

void UMC_InventoryComponent::FindItemsByFilter(const FInventoryItemFilter& InventoryItemFilter, TArray<UMC_Item*>& OutItems) const
{
#if !UE_BUILD_SHIPPING

	CHECK_NUM_FIELDS(4, FInventoryItemFilter)
	
    // Warn if no filter criteria are enabled
    if (!(InventoryItemFilter.bUseCategoryFilter || 
          InventoryItemFilter.bUseItemClass		 || 
          InventoryItemFilter.bUseMaxTier		 || 
          InventoryItemFilter.bUseMinTier		 || 
          InventoryItemFilter.bUseRarityFilter))
    {
        UE_LOGFMT(LogInventory, Error, "All inclusive filters are disabled");

    	//Clear OutItems and return
    	OutItems.Empty();
    	return;
    }
#endif
	
    // Get all items from inventory
    TArray<UMC_Item*> TempItems;
    GetInventoryItems(TempItems);

    // Process each item in the inventory
    for (UMC_Item* Item : TempItems)
    {
        // Basic validity checks
        if (!IsValid(Item)) continue;
    	
        UMC_ItemConfig* ItemConfig = Item->GetItemConfig();
        if (!IsValid(ItemConfig)) continue;

        // Inclusive filters
        if (InventoryItemFilter.bUseItemClass && InventoryItemFilter.ItemClass && Item->GetClass() != InventoryItemFilter.ItemClass) continue;

        if ((InventoryItemFilter.bUseMinTier && (ItemConfig->ItemTier < InventoryItemFilter.MinTier)) ||
			(InventoryItemFilter.bUseMaxTier && (ItemConfig->ItemTier > InventoryItemFilter.MaxTier))) continue;

        if (InventoryItemFilter.bUseRarityFilter && ItemConfig->ItemRarity > InventoryItemFilter.ItemRarity) continue;

        if (InventoryItemFilter.bUseCategoryFilter && InventoryItemFilter.ItemCategory != ItemConfig->ItemCategory) continue;

        // Passed all filters
        OutItems.Add(Item);
    }
}

UMC_Item* UMC_InventoryComponent::FindBestItemInInventory(const TSubclassOf<UMC_Item>& ItemClass) const
{
	// Inventory should never be nullptr!
	TArray<UMC_Item*> OutItems;

	//Create Filter
	FInventoryItemFilter InventoryItemFilter;

	//Set Filters
	InventoryItemFilter.ItemClass = ItemClass;
	InventoryItemFilter.bUseItemClass = true;

	// Get all Items of given class from the inventory
	FindItemsByFilter(InventoryItemFilter, OutItems);

	// If no items are found, return nullptr
	if (OutItems.Num() == 0)
	{
		//Log Warning
		UE_LOGFMT(LogMiningSystem, Warning, "Inventory doesn't contain the requested item. File: {0}, Line: {1}", __FILE__, __LINE__);
		return nullptr;
	}

	// Assuming Tier1 is the lowest tier
	UMC_Item* BestItem = nullptr;
	EItemTier HighestTier = EItemTier::Tier1;
	
	// Iterate through all items to find the one with the highest tier
	for (UMC_Item* Item : OutItems)
	{
		if (Item->GetItemConfig()->ItemTier > HighestTier)
		{
			BestItem = Item;
			HighestTier = BestItem->GetItemConfig()->ItemTier;
		}
	}
	
	return BestItem;
}

void UMC_InventoryComponent::DropItemBySlot(uint8 Slot)
{
	//TODO: Create a bag at player's location
}

void UMC_InventoryComponent::DropItemInstance(UMC_Item* Item)
{
	//TODO: Create a bag at player's location
}

bool UMC_InventoryComponent::FindValidSlot(uint8& OutSlot) const
{
	// Iterate through all the slots in the inventory
	for (uint8 CurrentSlot = 0; CurrentSlot < MaxSlots; CurrentSlot++)
	{
		// Check if the current slot is empty (does not contain an item)
		if (!Items.Contains(CurrentSlot))
		{
			OutSlot = CurrentSlot; 	// Assign the found empty slot to OutSlot
			return true;			// Return true since a valid (empty) slot was found
		}
	}

	// Return false if no empty slot was found
	return false;
}