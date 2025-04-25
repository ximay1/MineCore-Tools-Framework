#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MC_Inventory.generated.h"

/** Forward Declarations */
class UMC_InventorySlot;
class UMC_InventoryComponent;
class UProgressBar;
class UCommonTextBlock;
class UCommonButtonBase;

/** Base class for Inventory Widget */
UCLASS()
class MINECORE_API UMC_Inventory : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	/** Events */
	UFUNCTION(BlueprintCallable, Category = "Inventory Widget")
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
	FString InventorySlotName = "W_InventorySlot";
	
	/** Cached Inventory Slots */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget")
	TArray<UMC_InventorySlot*> InventorySlots;

	/** Bind Widgets */
	/** Progress Bars */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget", meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Weight;

	/** Text Blocks */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_WeightPercent;

	/** Buttons */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget", meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> Button_Close;
};
