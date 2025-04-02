#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MC_CheatManager.generated.h"

UCLASS()
class MINECORE_API UMC_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	
	/** Serializes the inventory to a JSON file in the Saved folder. */
	UFUNCTION(Exec)
	void SerializeInventoryToJSON();
};

