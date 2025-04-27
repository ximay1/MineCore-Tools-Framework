#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MC_InventorySlot.generated.h"

/** Forward Declarations */
class UMC_Item;
class UCommonButtonBase;
class UMC_InventorySlotButton;

/** Inventory Slot Widget that displays and manages a single item. */
UCLASS()
class MINECORE_API UMC_InventorySlot : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this Inventory Slot Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Widget")
	virtual void InitializeInventorySlotWidget(UMC_Item* Item);

protected:
	/** ~ Begin UUserWidget Interface */
	virtual void NativeOnInitialized() override;
	/** ~ End UUserWidget Interface */

	/** Item Context Menu Class */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Slot Widget", meta = (AllowedClasses = "MC_ItemContextMenu"))
	TSubclassOf<UCommonActivatableWidget> ItemContextMenu_Class;
	
	/** The item currently represented by this inventory slot */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget")
	TObjectPtr<UMC_Item> CachedItem;

	/** UI Elements - Bound in Blueprint */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget))
	TObjectPtr<UMC_InventorySlotButton> W_InventorySlotButton;

private:
	/** Called when W_InventorySlotButton is clicked */
	UFUNCTION()
	void HandleInventorySlotButtonClicked();
};
