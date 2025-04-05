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
}

void UMC_MiningSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_MiningSystemComponent, IsPlayerMining, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UMC_MiningSystemComponent, CachedMiningTools, COND_OwnerOnly);
}

void UMC_MiningSystemComponent::InitializeMiningSystemComponent()
{
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

void UMC_MiningSystemComponent::Server_CacheMiningToolsFromInventory_Implementation()
{
	//Try to find Inventory Component
	if (!IsValid(InventoryComponent))
		InventoryComponent = FindInventory();
	
	if (InventoryComponent)
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

		// Update cached mining tools
		CachedMiningTools.CachedPickaxe = Cast<UMC_Pickaxe>(BestToolsMap.FindRef(UMC_Pickaxe::StaticClass()));
		CachedMiningTools.CachedAxe = Cast<UMC_Axe>(BestToolsMap.FindRef(UMC_Axe::StaticClass()));
		CachedMiningTools.CachedHammer = Cast<UMC_Hammer>(BestToolsMap.FindRef(UMC_Hammer::StaticClass()));
		CachedMiningTools.CachedKnife = Cast<UMC_Knife>(BestToolsMap.FindRef(UMC_Knife::StaticClass()));
		CachedMiningTools.CachedSickle = Cast<UMC_Sickle>(BestToolsMap.FindRef(UMC_Sickle::StaticClass()));
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

UMC_MiningTool* UMC_MiningSystemComponent::GetMiningTool(TSubclassOf<UMC_MiningTool> ToolClass) const
{
	 if (!ToolClass) return nullptr;
    
    if (ToolClass == UMC_Pickaxe::StaticClass())
        return CachedMiningTools.CachedPickaxe;
	
    if (ToolClass == UMC_Axe::StaticClass())
        return CachedMiningTools.CachedAxe;
	
    if (ToolClass == UMC_Hammer::StaticClass())
        return CachedMiningTools.CachedHammer;
	
    if (ToolClass == UMC_Knife::StaticClass())
        return CachedMiningTools.CachedKnife;
	
    if (ToolClass == UMC_Sickle::StaticClass())
        return CachedMiningTools.CachedSickle;

    return nullptr;
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
