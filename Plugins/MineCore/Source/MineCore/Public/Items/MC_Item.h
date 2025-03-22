#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MC_Item.generated.h"

class UMC_ItemConfig;

UCLASS()
class MINECORE_API UMC_Item : public UObject
{
	GENERATED_BODY()

public:
	/** Get ItemConfig */
	FORCEINLINE UMC_ItemConfig* GetItemConfig() const { return ItemConfig; }
	
protected:
	/** Data Item Config */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UMC_ItemConfig> ItemConfig; 
};
