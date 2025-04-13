#include "Game/Inventory/MCUI_Inventory.h"
#include "Blueprint/WidgetTree.h"

void UMCUI_Inventory::NativeConstruct()
{
	Super::NativePreConstruct();

	//Cache Inventory Slots
	CacheInventorySlots(InventorySlotName);
}

void UMCUI_Inventory::CacheInventorySlots(const FString& InventorySlotName)
{
	TArray<UWidget*> Results;
	int32 FoundInventorySlots = 0;
    
	// Iterate through all widgets in the WidgetTree
	WidgetTree->ForEachWidget([&Results, &InventorySlotName, &FoundInventorySlots](UWidget* Widget)
	{
		// Check if widget name matches the pattern: [InventorySlotName]_[CurrentCount]
		if (Widget->GetName() == FString::Printf(TEXT("%s_%d"), *InventorySlotName, FoundInventorySlots))
		{
			Results.Add(Widget);
			FoundInventorySlots++; // Only increment if we found a match
		}
	});
}