#include "Components/MC_MiningSystemComponent.h"
#include "MC_LogChannels.h"
#include "Components/MC_InventoryComponent.h"

UMC_MiningSystemComponent::UMC_MiningSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMC_MiningSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	//Find Inventory
	FindInventory();

	//Find the best Pickaxe in the inventory
	FindPickaxeInInventory();
}

bool UMC_MiningSystemComponent::FindInventory()
{
	//Get Owner
	if (APawn* Owner = Cast<APawn>(GetOwner()))
	{
		//Find Inventory
		InventoryComponent = Owner->FindComponentByClass<UMC_InventoryComponent>();

		//Return value
		return (InventoryComponent ? true : false);
	}
	else
	{
		//Log Error
		UE_LOGFMT(LogMiningSystem, Error, "You attempted to use MC_MiningSystemComponent on an actor that is not a Pawn or a class derived from it.");

		//Return value
		return false;
	}
}

bool UMC_MiningSystemComponent::FindPickaxeInInventory()
{
	//Inventory shouldn't be nullptr!!!
	
	return true;
}
