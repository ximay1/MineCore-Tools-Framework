#include "Game/Inventory/MCUI_Inventory.h"

void UMCUI_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Create Inventory Slots
	CacheInventorySlots();
}

void UMCUI_Inventory::CacheInventorySlots()
{
}