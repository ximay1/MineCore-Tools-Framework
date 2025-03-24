#include "Components/MC_MiningSystemComponent.h"
#include "Data/Item/MC_UsableItemConfig.h"
#include "Items/MiningTools/MC_Pickaxe.h"
#include "Items/MiningTools/MC_MiningTool.h"
#include "MC_LogChannels.h"
#include "Net/UnrealNetwork.h"

UMC_MiningSystemComponent::UMC_MiningSystemComponent() : IsPlayerMining(false)
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

void UMC_MiningSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_MiningSystemComponent, IsPlayerMining, COND_OwnerOnly);
}

bool UMC_MiningSystemComponent::CanPlayerMine(UMC_MiningTool* MiningTool)
{
	if (MiningTool->GetDurability() > 0.0f && MiningTool->GetDurability() <= MiningTool->GetItemConfig<UMC_UsableItemConfig>()->MaxDurability)
		return true;
	
	return false;
}

void UMC_MiningSystemComponent::StartMining_Implementation()
{
	//TODO: Start animation or something else idk

	//Set Is Player Mining to true
	IsPlayerMining = true;
}

void UMC_MiningSystemComponent::StopMining_Implementation()
{
	if (IsPlayerMining)
	{
		//TODO:Stop animation or something else idk
	}
	
	//Set Is Player Mining to false
	IsPlayerMining = false;
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
