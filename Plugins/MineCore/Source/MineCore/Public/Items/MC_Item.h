#pragma once

#include "CoreMinimal.h"
#include "MC_LogChannels.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "MC_Item.generated.h"

/** Base class for an item object. */
UCLASS()
class MINECORE_API UMC_Item : public UObject
{
	GENERATED_BODY()

public:

	/** Events */
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Get Item Config */
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE UMC_DT_ItemConfig* GetItemConfig() const { return ItemConfig; }

	/** Set Item Config. Server-only*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE void Server_SetItemConfig(UMC_DT_ItemConfig* NewItemConfig) { ItemConfig = NewItemConfig; }
	
	/** Attempts to cast the ItemConfig to the specified type */
	template<typename ItemConfigClass = UMC_DT_ItemConfig>
	ItemConfigClass* GetItemConfig() const;

	UFUNCTION(BlueprintGetter, Category = "Item")
	FORCEINLINE int32 GetCurrentStack() const { return CurrentStackCount; }
	
	/** Checks if the current item has a higher or equal tier than the given item. */
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE bool IsBetterThan(const UMC_Item* const Item) const { return (this->ItemConfig->ItemTier >= Item->ItemConfig->ItemTier); }

	/** Checks if the item is stackable */
	UFUNCTION(BlueprintGetter, Category = "Item")
	FORCEINLINE bool IsStackable() { return ItemConfig->MaxStackSize > 1; }

	/** Increases item stack count by specified amount. Server-only */
	UFUNCTION(BlueprintCallable, Category = "Item")
    int32 Server_AddToStack(int32 Amount = 1);

	/** Decreases item stack count by specified amount */
	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 Server_RemoveFromStack(int32 Amount = 1);
	
protected:
	/** Data Item Config */
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UMC_DT_ItemConfig> ItemConfig;

	/** Current quantity of items in this slot. For non-stackable items, value will always be 1 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentStackCount, Category = "Item")
	int32 CurrentStackCount = 1;

	UFUNCTION()
	virtual void OnRep_CurrentStackCount() {};
};

template <typename ItemConfigClass>
ItemConfigClass* UMC_Item::GetItemConfig() const
{
	#if UE_BUILD_SHIPPING
		// In shipping build, we perform the cast without checking.
		return Cast<ItemConfigClass>(ItemConfig);
	#else
		// In non-shipping builds, we perform a safe cast and log an error if it fails.
		if (ItemConfigClass* CastedItemConfig = Cast<ItemConfigClass>(ItemConfig))
		{
			return CastedItemConfig;
		}
		else
		{
			// Log an error message if the cast fails
			UE_LOGFMT(LogItem, Error, "Invalid cast for ItemConfig. Expected: {0}, Actual: {1}. File - {2}, Line - {3}", *ItemConfigClass::StaticClass()->GetName(), *ItemConfig->GetClass()->GetName(), __FILE__, __LINE__);
			
			return nullptr;
		}
	#endif
}