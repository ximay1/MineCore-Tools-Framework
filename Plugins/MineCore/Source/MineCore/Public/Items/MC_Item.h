#pragma once

#include "CoreMinimal.h"
#include "MineCore/Public/Data/Items/MC_ItemConfig.h"
#include "UObject/NoExportTypes.h"
#include "MC_LogChannels.h"
#include "MC_Item.generated.h"

class UMC_ItemConfig;

/** Base class for an item object. */
UCLASS()
class MINECORE_API UMC_Item : public UObject
{
	GENERATED_BODY()

public:

	/** Get Item Config */
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE UMC_ItemConfig* GetItemConfig() const { return ItemConfig; }
	
	/** Attempts to cast the ItemConfig to the specified type */
	template<typename ItemConfigClass = UMC_ItemConfig>
	ItemConfigClass* GetItemConfig() const;

protected:
	/** Data Item Config */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UMC_ItemConfig> ItemConfig; 
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
			UE_LOGFMT(LogItem, Error, "Invalid cast for ItemConfig. Expected: {0}, Actual: {1}. File - {2}, Line - {3}", 
					  *ItemConfigClass::StaticClass()->GetName(), *ItemConfig->GetClass()->GetName(), 
					  __FILE__, __LINE__);
			
			return nullptr;
		}
	#endif
}