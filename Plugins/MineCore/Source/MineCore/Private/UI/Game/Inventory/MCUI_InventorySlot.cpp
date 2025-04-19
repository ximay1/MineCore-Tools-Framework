#include "Items/MC_Item.h"
#include "UI/Common/Buttons/MC_InventorySlotButton.h"
#include "UI/Game/Inventory/MC_InventorySlot.h"

void UMC_InventorySlot::InitializeInventorySlotWidget(UMC_Item* Item)
{
	//Check if the Item is valid
	if (IsValid(Item))
	{
		//Cache item
		CachedItem = Item;

		//Initialize Inventory Slot Button
		InventorySlotButton->InitializeInventorySlotButtonWidget(Item);
	}
}