#include "Components/MC_MiningSystemComponent.h"
#include "Data/Item/MC_UsableItemConfig.h"
#include "Items/MiningTools/MC_Pickaxe.h"
#include "Items/MiningTools/MC_MiningTool.h"
#include "MC_LogChannels.h"

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
	CachedPickaxe = InventoryComponent->FindBestItemInInventory<UMC_Pickaxe>();
}

bool UMC_MiningSystemComponent::CanPlayerMine(UMC_MiningTool* MiningTool)
{
	if (MiningTool->GetDurability() > 0.0f && MiningTool->GetDurability() <= MiningTool->GetItemConfig<UMC_UsableItemConfig>()->MaxDurability)
		return true;
	
	return false;
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
