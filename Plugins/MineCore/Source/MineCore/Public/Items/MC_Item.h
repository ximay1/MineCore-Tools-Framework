#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/Item/MC_ItemConfig.h"
#include "MC_Item.generated.h"

UCLASS()
class MINECORE_API UMC_Item : public UObject
{
	GENERATED_BODY()

protected:
	/** Data Item Config */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UMC_ItemConfig> ItemConfig; 
};
