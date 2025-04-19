#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "MC_InventorySlotButton.generated.h"

/** Forward Declarations */
class UImage;
class UMC_Item;

/** Button Widget representing a single inventory slot. */
UCLASS()
class MINECORE_API UMC_InventorySlotButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	/** Initializes this inventory slot button widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Button Widget")
	virtual void InitializeInventorySlotButtonWidget(UMC_Item* Item);

protected:
	/** Bind Widgets */
	/** Images */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Button Widget", meta = (BindWidget))
	TObjectPtr<UImage> Image_Background;
};
