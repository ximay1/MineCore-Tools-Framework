#include "Game/Inventory/MCUI_Inventory.h"
#include "Blueprint/WidgetTree.h"
#include "Game/Inventory/MCUI_InventorySlot.h"
#include "MCUI_LogChannels.h"

void UMCUI_Inventory::NativeConstruct()
{
	Super::NativePreConstruct();

	//Cache Inventory Slots
	CacheInventorySlots();
}

void UMCUI_Inventory::CacheInventorySlots()
{
	int32 FoundInventorySlots = 0; // Tracks the current expected slot index during search
    
	// Iterate through all widgets in this widget's hierarchy
	WidgetTree->ForEachWidget([this, &FoundInventorySlots](UWidget* Widget)
	{
		// Match widgets following the naming pattern: [InventorySlotName]_[Index]
		if (Widget->GetName() == FString::Printf(TEXT("%s_%d"), *InventorySlotName, FoundInventorySlots))
		{
			// Verify the widget is of the correct inventory slot type
			if (UMCUI_InventorySlot* InventorySlot = Cast<UMCUI_InventorySlot>(Widget))
			{
				InventorySlots.Add(InventorySlot);
				FoundInventorySlots++; // Increment only after successful validation
            
				// DEV NOTE: We increment index only when finding EXACT sequence (0,1,2...)
			}
			else
			{
				// Log Error
				UE_LOGFMT(LogWidget, Error, 
					"Inventory slot naming conflict! Widget '{0}' (Path: {1}) "
					"matches slot naming pattern but isn't UMCUI_InventorySlot type. ",
					Widget->GetName(),
					Widget->GetPathName());
			}
		}
	});
}