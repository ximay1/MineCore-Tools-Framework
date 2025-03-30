#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_ServerCheatsComponent.generated.h"


UCLASS( ClassGroup=(MineCore), meta=(BlueprintSpawnableComponent))
class MINECORE_API UMC_ServerCheatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Constructor */
	UMC_ServerCheatsComponent();

	/** Adds an item to the first available slot in the inventory */
	UFUNCTION(Server, Reliable, Category = "Server Cheats Component")
	void AddItemToFirstAvailableSlot_Cheat(UMC_Item* Item);
};
