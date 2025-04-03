#include "Components/MC_MiningSystemComponent.h"
#include "MC_LogChannels.h"
#include "Components/MC_InventoryComponent.h"
#include "Items/MiningTools/MC_Axe.h"
#include "Items/MiningTools/MC_Hammer.h"
#include "Items/MiningTools/MC_Knife.h"
#include "Items/MiningTools/MC_MiningTool.h"
#include "Items/MiningTools/MC_Pickaxe.h"
#include "Items/MiningTools/MC_Sickle.h"
#include "MineCore/Public/Data/Items//UsableItems/MC_DT_UsableItemConfig.h"
#include "Net/UnrealNetwork.h"

UMC_MiningSystemComponent::UMC_MiningSystemComponent() : IsPlayerMining(false)
{
	//Set Parameters
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UMC_MiningSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	//Find Inventory
	InventoryComponent = FindInventory();

	//Update cache
	CacheMiningToolsFromInventory();
}

void UMC_MiningSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_MiningSystemComponent, IsPlayerMining, COND_OwnerOnly);
}

void UMC_MiningSystemComponent::Client_InitializeMiningSystemComponent_Implementation()
{
	//Cache mining tools
	CacheMiningToolsFromInventory();
	
	//Call Server Initialize Mining System Component
	Server_InitializeMiningSystemComponent();
}

void UMC_MiningSystemComponent::Server_InitializeMiningSystemComponent_Implementation()
{
}

bool UMC_MiningSystemComponent::CanPlayerMine(UMC_MiningTool* MiningTool)
{
	if (MiningTool->GetDurability() > 0.0f && MiningTool->GetDurability() <= MiningTool->GetItemConfig<UMC_DT_UsableItemConfig>()->MaxDurability)
		return true;
	
	return false;
}

void UMC_MiningSystemComponent::CacheMiningToolsFromInventory()
{
	// List of tool classes we're interested in
	const TSet<TSubclassOf<UMC_MiningTool>> ToolClasses = {
		UMC_Pickaxe::StaticClass(),
		UMC_Hammer::StaticClass(),
		UMC_Axe::StaticClass(),
		UMC_Knife::StaticClass(),
		UMC_Sickle::StaticClass()
	};

	TMap<TSubclassOf<UMC_MiningTool>, UMC_MiningTool*> BestToolsMap;

	// Process each inventory item only once
	TArray<UMC_Item*> Items;
	InventoryComponent->GetInventoryItems(Items);
	for (UMC_Item* const& Item : Items)
	{
		// Check if the item is a mining tool
		if (UMC_MiningTool* Tool = Cast<UMC_MiningTool>(Item))
		{
			TSubclassOf<UMC_MiningTool> ToolClass = Tool->GetClass();
            
			// Check if this is one of the tool types we're looking for
			if (ToolClasses.Contains(ToolClass))
			{
				// Compare tiers with current best tool of this type
				UMC_MiningTool*& CurrentBestTool = BestToolsMap.FindOrAdd(ToolClass);
				if (!CurrentBestTool || Tool->IsBetterThan(CurrentBestTool))
				{
					CurrentBestTool = Tool;
				}
			}
		}
	}

	// Update cache: clear old entries and add new ones
	CachedMiningTools.Empty();
	for (const auto& ToolPair : BestToolsMap)
	{
		CachedMiningTools.Add(ToolPair.Key, ToolPair.Value);
	}
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
