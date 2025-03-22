#include "Components/MC_InventoryComponent.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"

UMC_InventoryComponent::UMC_InventoryComponent() : MaxSlots(40)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
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

void UMC_InventoryComponent::DropItem(uint8 Slot)
{
	//TODO: Create a bag at player's location
}

void UMC_InventoryComponent::DropItem(UMC_Item* Item)
{
	//TODO: Create a bag at player's location
}

bool UMC_InventoryComponent::FindValidSlot(uint8& OutSlot)
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

void UMC_InventoryComponent::AddItemToInventory_Implementation(uint8 Slot, UMC_Item* Item)
{
#if !UE_BUILD_SHIPPING
	// Check if the slot number is valid (Slot should be less than or equal to MaxSlots)
	if (Slot > MaxSlots)
	{
		UE_LOGFMT(LogInventory, Error, "Invalid slot number. Slot exceeds MaxSlots. File - {0}, Line - {1}.", __FILE__, __LINE__);
	}
	if (Item == nullptr)
	{
		UE_LOGFMT(LogInventory, Error, "Item is nullptr. File - {0}, Line - {1}.", __FILE__, __LINE__);
	}
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
			DropItem(Item);
			
			UE_LOGFMT(LogInventory, Log, "We need to create a bag of items at the player's location when attempting to add an item to the inventory");
		}
		
		// Refresh the inventory widget to reflect the changes
		RefreshInventoryWidget();
	}
}


void UMC_InventoryComponent::RemoveItemFromInventory_Implementation(uint8 Slot, EItemAction ItemAction)
{
#if !UE_BUILD_SHIPPING
	// Check if the slot number is valid (Slot should be less than or equal to MaxSlots)
	if (Slot > MaxSlots)
	{
		UE_LOGFMT(LogInventory, Error, "Invalid slot number. Slot exceeds MaxSlots. File - {0}, Line - {1}.", __FILE__, __LINE__);
	}
#endif

	// Perform the assigned action based on the ItemAction enum
	switch (ItemAction)
	{
		case EItemAction::IA_Destroy:
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
					// Log an error if the item is nullptr (doesn't exist) in the inventory
					UE_LOGFMT(LogInventory, Error, "We wanted to destroy the item which doesn't exist in the inventory, we passed an invalid slot. File - {0}, Line - {1}", __FILE__, __LINE__);
				}

				break;
			}
		case EItemAction::IA_Drop:
			{
				// Drop the item from the inventory using the given slot
				DropItem(Slot);
				
				break;
			}
	};

	// Refresh the inventory widget to reflect the changes
	RefreshInventoryWidget();
}