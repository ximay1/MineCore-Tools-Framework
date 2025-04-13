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
	virtual void NativePreConstruct() override;
	
	/** Cache inventory slot widgets. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Widget")
	void CacheInventorySlots();

	/** Bind Widgets */
	/** Cached Inventory Slots */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget")
	TArray<UMCUI_InventorySlot*> InventorySlots;
};
