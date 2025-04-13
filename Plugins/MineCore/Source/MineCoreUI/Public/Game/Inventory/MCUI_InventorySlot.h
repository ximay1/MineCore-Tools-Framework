#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MCUI_InventorySlot.generated.h"

/** Forward Declarations */
class UMC_Item;

UCLASS()
class MINECOREUI_API UMCUI_InventorySlot : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this inventory slot widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Widget")
	virtual void InitializeInventorySlotWidget(UMC_Item* Item);

protected:
	/** The item currently represented by this inventory slot */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget")
	TObjectPtr<UMC_Item> CachedItem;
};
