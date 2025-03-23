#include "Components/MC_MiningSystemComponent.h"
#include "Data/Item/MC_ItemConfig.h"
#include "Items/MiningTools/MC_Pickaxe.h"

UMC_MiningSystemComponent::UMC_MiningSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMC_MiningSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	//Find Inventory
	InventoryComponent = FindInventory();

	//Find the best Pickaxe in the inventory
	CachedPickaxe = Cast<UMC_Pickaxe>(InventoryComponent->FindBestItemInInventory(UMC_Pickaxe::StaticClass()));
}

UMC_InventoryComponent* UMC_MiningSystemComponent::FindInventory() const
{
	//Get Owner
	if (APawn* Owner = Cast<APawn>(GetOwner()))
	{
		//Return Inventory
		return Owner->FindComponentByClass<UMC_InventoryComponent>();
	}
	else
	{
		//Log Error
		UE_LOGFMT(LogMiningSystem, Error, "You attempted to use MC_MiningSystemComponent on an actor that is not a Pawn or a class derived from it.");

		//Return value
		return nullptr;
	}
}