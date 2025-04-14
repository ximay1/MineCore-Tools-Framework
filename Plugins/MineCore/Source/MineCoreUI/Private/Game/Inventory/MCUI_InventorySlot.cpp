#include "Game/Inventory/MCUI_InventorySlot.h"
#include "CommonButtonBase.h"
#include "Common/Buttons/MCUI_InventorySlotButton.h"
#include "Items/MC_Item.h"

void UMCUI_InventorySlot::InitializeInventorySlotWidget(UMC_Item* Item)
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