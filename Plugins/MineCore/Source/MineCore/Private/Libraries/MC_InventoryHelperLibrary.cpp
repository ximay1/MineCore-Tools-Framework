#include "Libraries/MC_InventoryHelperLibrary.h"

#include "Items/MC_Item.h"

bool UMC_InventoryHelperLibrary::CanItemsStack(const UMC_Item* ItemA, const UMC_Item* ItemB)
{
	// Retrieve item config data for both items
	UMC_DT_ItemConfig* ItemConfigA = ItemA->GetItemConfig();
	UMC_DT_ItemConfig* ItemConfigB = ItemB->GetItemConfig();

	// Validate that both item configs exist
	checkf(ItemConfigA && ItemConfigB, TEXT("CanItemsStack: Missing item configuration for one or both items"));

	// Verify stack compatibility:
	// 1. Items must have the same maximum stack size
	// 2. Combined stacks must not exceed max stack size
	const bool bCanStackBySize = (ItemConfigA->MaxStackSize == ItemConfigB->MaxStackSize) && 
							     (ItemA->GetCurrentStack() + ItemB->GetCurrentStack() <= ItemConfigA->MaxStackSize);

	// Verify item type compatibility:
	// Items must share the same class, rarity and tier to be stackable
	const bool bCanStackByType = (ItemConfigA->ItemClass == ItemConfigB->ItemClass)   && 
								 (ItemConfigA->ItemRarity == ItemConfigB->ItemRarity) &&
	   							 (ItemConfigA->ItemTier == ItemConfigB->ItemTier);
	
	return bCanStackBySize && bCanStackByType;
}

int32 UMC_InventoryHelperLibrary::GetRemainingStackSpace(const UMC_Item* ItemA)
{
	return ItemA->GetItemConfig()->MaxStackSize - ItemA->GetCurrentStack();
}

