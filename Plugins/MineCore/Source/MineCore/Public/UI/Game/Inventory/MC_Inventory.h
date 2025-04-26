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

/** Base class for inventory widget that displays player's items. */
UCLASS()
class MINECORE_API UMC_Inventory : public UCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    /** ~ Begin UCommonActivatableWidget Interface */
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    /** ~ End UCommonActivatableWidget Interface */

    /** Cached Inventory Component */
    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    TWeakObjectPtr<UMC_InventoryComponent> InventoryComponent;

    /** 
     * Base name for inventory slot widgets (without numeric suffix).
     * Example: If slots are named "W_InventorySlot_0", "W_InventorySlot_1",
     * enter "W_InventorySlot" here.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory UI")
    FString InventorySlotName = "W_InventorySlot";

    /** Cached inventory slot widgets */
    UPROPERTY(BlueprintReadOnly, Category = "Inventory UI")
    TArray<UMC_InventorySlot*> InventorySlots;

    /** UI Elements - Bound in Blueprint */
    UPROPERTY(BlueprintReadOnly, Category = "Inventory UI", meta = (BindWidget))
    TObjectPtr<UProgressBar> ProgressBar_Weight;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory UI", meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> CommonTextBlock_WeightPercent;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory UI", meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> Button_Close;

    /** Initializes the widget with inventory component reference. */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual void InitializeInventoryWidget();

    /** Caches all inventory slot widgets matching the naming pattern [InventorySlotName]_[Index]. */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual void CacheInventorySlots();

    /** Updates the weight display including progress bar and text */
    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void UpdateInventoryWeightUI();

private:
    /** Called when close button is clicked */
    UFUNCTION()
    void HandleCloseButtonClicked();

    /** Called when inventory content changes */
    UFUNCTION()
    void HandleInventoryUpdated();
};