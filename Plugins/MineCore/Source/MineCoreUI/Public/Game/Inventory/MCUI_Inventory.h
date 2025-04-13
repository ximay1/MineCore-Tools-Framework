#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MCUI_Inventory.generated.h"

/** Forward Declarations */
class UMCUI_InventorySlot;
UCLASS()
class MINECOREUI_API UMCUI_Inventory : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	/** Events */
	virtual void InitializeInventoryWidget(UMC_InventoryComponent* InventoryComponent);
	
	/** Caches all inventory slot widgets matching the naming pattern: [InventorySlotName]_[Index]. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Widget")
	virtual void CacheInventorySlots(UMC_InventoryComponent* InventoryComponent);
	
	/**
	 * Base name for inventory slot widgets (without the numeric suffix).
	 * 
	 * Example: 
	 * - If your slots are named "W_InventorySlot_0", "W_InventorySlot_1" etc.
	 * - Enter here: "W_InventorySlot"
	 * 
	 * The system will automatically look for widgets following the pattern [InventorySlotName]_[Index]
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget")
	FString InventorySlotName;
	
	/** Bind Widgets */
	/** Cached Inventory Slots */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget")
	TArray<UMCUI_InventorySlot*> InventorySlots;
};
