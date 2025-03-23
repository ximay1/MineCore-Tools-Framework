#include "Items/MC_Item.h"

void UMC_Item::PostInitProperties()
{
	UObject::PostInitProperties();

	// Check if the object exists in a valid world context
	if (GetWorld())
	{
		// Call BeginPlay to simulate the actor's BeginPlay behavior
		BeginPlay();
	} 
}

void UMC_Item::BeginPlay()
{
	
}
