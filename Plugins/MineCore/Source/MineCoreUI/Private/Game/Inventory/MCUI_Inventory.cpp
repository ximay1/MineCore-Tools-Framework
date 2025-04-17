#include "Game/Inventory/MCUI_Inventory.h"
#include "MCUI_LogChannels.h"
#include "Blueprint/WidgetTree.h"
#include "Components/MC_InventoryComponent.h"
#include "Game/Inventory/MCUI_InventorySlot.h"

void UMCUI_Inventory::InitializeInventoryWidget(UMC_InventoryComponent* InventoryComponent)
{
	//Cache Inventory Slots
    CacheInventorySlots(InventoryComponent);
}

void UMCUI_Inventory::CacheInventorySlots(UMC_InventoryComponent* InventoryComponent)
{
	// Tracks the current expected slot index during search
	uint8 FoundInventorySlots = 0;
	const uint8 MaxItemInventorySlots = InventoryComponent->GetMaxSlots();
	
	// Iterate through all widgets in this widget's hierarchy
	WidgetTree->ForEachWidget([this, &FoundInventorySlots, InventoryComponent](UWidget* Widget)
	{
		// Match widgets following the naming pattern: [InventorySlotName]_[Index]
		if (Widget->GetName() == FString::Printf(TEXT("%s_%d"), *InventorySlotName, FoundInventorySlots))
		{
			// Verify the widget is of the correct inventory slot type
			if (UMCUI_InventorySlot* InventorySlot = Cast<UMCUI_InventorySlot>(Widget))
			{
				//Add Inventory Slot to the array
				InventorySlots.Add(InventorySlot);

				//Get Item amd Initialize Inventory Slot
				InventorySlot->InitializeInventorySlotWidget(InventoryComponent->GetAt(FoundInventorySlots));
					
				InventorySlots.Add(InventorySlot);
				FoundInventorySlots++; // Increment only after successful validation
				
				// DEV NOTE: We increment index only when finding EXACT sequence (0,1,2...)
			}
			else
			{
				// Log Error
				UE_LOGFMT(LogWidget, Error, 
					"Inventory slot naming conflict! Widget '{0}' (Path: {1}) "
					"matches slot naming pattern but isn't MCUI_InventorySlot type. ",
					Widget->GetName(),
					Widget->GetPathName());
			}
		}
	});

	// Validate if all expected inventory slots were successfully cached
	if (InventorySlots.Num() == MaxItemInventorySlots)
	{
		//Log
		UE_LOGFMT(LogWidget, Log, 
			"Successfully cached all {0} inventory slots (Expected: {1})", 
			InventorySlots.Num(), 
			MaxItemInventorySlots);
	}
	else
	{
		//Log Error
		UE_LOGFMT(LogWidget, Error, 
			"Inventory slot cache incomplete! Found {0} slots (Expected: {1}). "
			"Possible causes:\n"
			"- Missing slot widgets in hierarchy\n"
			"- Incorrect naming convention (should be: {Name}_{Index})\n"
			"- Slot widgets not derived from MCUI_InventorySlot",
			InventorySlots.Num(), 
			MaxItemInventorySlots);
	}
}
