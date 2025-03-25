#pragma once

#include "CoreMinimal.h"
#include "Items/MC_Item.h"
#include "MC_MiningTool.generated.h"

/** Base class for mining tools such as pickaxes, axes, and knives. */
UCLASS()
class MINECORE_API UMC_MiningTool : public UMC_Item
{
	GENERATED_BODY()

public:
	/** Get Durablity */
	UFUNCTION(BlueprintCallable,Category = "Mining Tool")
	FORCEINLINE float GetDurability() const { return Durability; }
	
protected:
	/** The durability of the item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mining Tool", meta = (ClampMin = "0.01"))
	float Durability = 1.0f;
};
