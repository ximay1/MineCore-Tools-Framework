#include "Components/MC_InventoryComponent.h"
#include "MC_LogChannels.h"
#include "MineCoreMacros.h"
#include "Components/MC_MiningSystemComponent.h"
#include "Development/Data/MC_DT_DefaultInventoryData.h"
#include "Items/MC_Item.h"
#include "MineCore/Public/Data/Items/MC_DT_ItemConfig.h"
#include "Net/UnrealNetwork.h"


FInventoryItemFilter::FInventoryItemFilter()
	: ItemClass(nullptr)
	, MinTier((EItemTier)0)
	, MaxTier((EItemTier)0)
	, ItemCategory((EItemCategory)0)
	, ItemRarity((EItemRarity)0)
	, bUseItemClass(false)
	, bUseMinTier(false)
	, bUseMaxTier(false)
	, bUseCategoryFilter(false)
	, bUseRarityFilter(false)
{
}

FInventoryItemFilter::FInventoryItemFilter(TSubclassOf<UMC_Item> InItemClass, EItemTier InMinTier, EItemTier InMaxTier, EItemCategory InItemCategory, EItemRarity InItemRarity)
	: ItemClass(InItemClass)
	, MinTier(InMinTier)
	, MaxTier(InMaxTier)
	, ItemCategory(InItemCategory)
	, ItemRarity(InItemRarity)
	, bUseItemClass(true)
	, bUseMinTier(true)
	, bUseMaxTier(true)
	, bUseCategoryFilter(true)
	, bUseRarityFilter(true)
{
}

FItemDefinition::FItemDefinition(UMC_DT_ItemConfig* NewItemConfig) : ItemConfig(NewItemConfig)
{
}

UMC_InventoryComponent::UMC_InventoryComponent() : MaxSlots(40)
{
	//Set Parameters
	PrimaryComponentTick.bCanEverTick = false;
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
}

void UMC_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_InventoryComponent, Items_Array, COND_OwnerOnly);
}

void UMC_InventoryComponent::Client_CreateInventory()
{
	//TODO: Create Inventory
}

void UMC_InventoryComponent::Client_RefreshInventoryWidget()
{
	/*if (InventoryWidget)
	{
		TODO: InventoryWidget->RefreshWidget()
	}*/
}

bool UMC_InventoryComponent::FindValidSlot(uint8& OutSlot) const
{
	// Iterate through all the slots in the inventory
	for (uint8 CurrentSlot = 0; CurrentSlot < MaxSlots; CurrentSlot++)
	{
		// Check if the current slot is empty (does not contain an item)
		if (!Items.Contains(CurrentSlot))
		{
			OutSlot = CurrentSlot; 	// Assign the found empty slot to OutSlot
			return true;			// Return true since a valid (empty) slot was found
		}
	}

	// Return false if no empty slot was found
	return false;
}

bool UMC_InventoryComponent::IsValidInventorySlot(const FInventorySlot& InventorySlot)
{
	return IsValid(InventorySlot.Item) && IsValidSlot(InventorySlot.Slot);
}

void UMC_InventoryComponent::Server_AddItemDefinitionToSlot_Implementation(uint8 Slot, const FItemDefinition& ItemDefinition)
{
	Server_AddItemToSlot(FInventorySlot(Slot, Server_ConstructItem(ItemDefinition)));
}

void UMC_InventoryComponent::Server_AddItemToSlot_Implementation(const FInventorySlot& InventorySlot)
{
	//Get Slot
	uint8 Slot = InventorySlot.Slot;

	//Get Item
	UMC_Item* Item = InventorySlot.Item;
	
#if !UE_BUILD_SHIPPING
	// Declare a flag to track the validity of the slot and item
	bool bIsValid = true;

	// Validate both the slot and the item using the macro. If invalid, it will set bIsValid to false and log errors.
	VALIDATE_ITEM_AND_SLOT_RETURN(Slot, MaxSlots, Item, bIsValid)

	// If both slot and item aren't valid, exit the function early.
	if (!bIsValid)
		return;
#endif
	
	//Check if there is something on that slot
	if (GetItemFromInventory(Slot) != nullptr)
	{
		//Find next valid slot
		if (!FindValidSlot(Slot))
		{
			// Drop the item from the inventory using the given item
			Server_DropItemInstance(Item);

			//Log
			UE_LOGFMT(LogInventory, Log, "We need to create a bag of items at the player's location when attempting to add an item to the inventory");
			return;
		}
	}
	
	//Add to the inventory
	Items_Array.Add(FInventorySlot(Slot, Item));
}

void UMC_InventoryComponent::Server_AddItemDefinitionToFirstAvailableSlot_Implementation(const FItemDefinition& ItemDefinition)
{
	Server_AddItemToFirstAvailableSlot_Implementation(Server_ConstructItem(ItemDefinition));
}

void UMC_InventoryComponent::Server_AddItemToFirstAvailableSlot_Implementation(UMC_Item* Item)
{
#if !UE_BUILD_SHIPPING
	// Declare a flag to track the validity of the item
	bool bIsValid = true;

	// Validate the item using the macro. If invalid, it will set bIsValid to false and log errors.
	VALIDATE_ITEM_AND_RETURN(Item, bIsValid)

	// If item isn't valid, exit the function early.
	if (!bIsValid)
		return;
#endif

	uint8 Slot = 0;
	
	//Find next valid slot
	if (!FindValidSlot(Slot))
	{
		// Drop the item from the inventory using the given item
		Server_DropItemInstance(Item);

		//Log 
		UE_LOGFMT(LogInventory, Log, "We need to create a bag of items at the player's location when attempting to add an item to the inventory");
		return;
	}

	//Add to the inventory
	Items_Array.Add(FInventorySlot(Slot, Item));
}

void UMC_InventoryComponent::Server_AddItemDefinitionStacksToSlot_Implementation(uint8 SlotIndex, const FItemDefinition& ItemDefinition, int32 StacksToAdd)
{
	Server_AddItemStacksToSlot(FInventorySlot(SlotIndex, Server_ConstructItem(ItemDefinition)), StacksToAdd);
}

void UMC_InventoryComponent::Server_AddItemStacksToSlot_Implementation(const FInventorySlot& TargetInventorySlot, int32 StacksToAdd)
{
	// Validate input parameters
	if (!IsValidSlot(TargetInventorySlot.Slot)|| StacksToAdd <= 0)
	{
		UE_LOGFMT(LogInventory, Error, "Invalid slot index ({0})", TargetInventorySlot.Slot);
		return;
	}
	
	// Check if slot already contains matching item
	if (int32 FoundIndex = Items_Array.Find(TargetInventorySlot))
	{
		// Add stacks to existing item
		FInventorySlot& ExistingSlot = Items_Array[FoundIndex];
		ExistingSlot.Item->Server_AddToStack(StacksToAdd);
	}
	else
	{
		// Initialize new item with proper stack count
		TargetInventorySlot.Item->Server_AddToStack(StacksToAdd);
		Items_Array.Add(TargetInventorySlot);
	}
}

void UMC_InventoryComponent::Server_RemoveItemFromInventory_Implementation(uint8 Slot, EItemAction ItemAction)
{
#if !UE_BUILD_SHIPPING
	// Declare a flag to track the validity of the slot
	bool bIsValid = true;

	// Validate the slot number using the macro; if invalid, it will log an error and set bIsValid to false
	VALIDATE_SLOT_AND_RETURN(Slot, MaxSlots, bIsValid)

	// If the slot is not valid, exit the function early
	if (!bIsValid)
		return;
#endif

	
	// Find the item in the inventory that matches the given slot
	FInventorySlot* ItemToDestroy = Items_Array.FindByPredicate([Slot](const FInventorySlot& Item)
	{
		return Item.Slot == Slot;
	});

	// Validate if the item exists and is not null
	if (!ItemToDestroy || !ItemToDestroy->Item)
	{
		UE_LOGFMT(LogInventory, Error, "Failed to perform item action: No valid item found in slot {0}. File: {1}, Line: {2}", Slot, __FILE__, __LINE__);
		return; // Early return to avoid further execution
	}

	switch (ItemAction)
	{
		case EItemAction::Destroy:
			{
				// Destroy item 
				Server_DestroyItem(*ItemToDestroy);

				//Log
				UE_LOGFMT(LogInventory, Log, "Item destroyed from slot {0}.", Slot);
				
				break;
			}
		case EItemAction::Drop:
			{
				// Spawn the item in the world and remove it from inventory
				Server_DropItemInstance(ItemToDestroy->Item);

				//Log
				UE_LOGFMT(LogInventory, Log, "Item dropped from slot {0}.", Slot);
				
				break;
			}
		default:
			{
				//Log
				UE_LOGFMT(LogInventory, Warning, "Unhandled item action type for slot {0}.", Slot);
				break;
			}
	};
}

void UMC_InventoryComponent::Server_SplitItemStack_Implementation(uint8 SourceSlot, int32 StacksToSplit)
{
	// Validate input parameter
	if (!IsValidSlot(SourceSlot))
	{
		UE_LOGFMT(LogInventory, Error, "Invalid slot indexes ({0})", SourceSlot);
		//return;
	}
	
	//Get Source InventorySlot
	FInventorySlot* SourceInventorySlot = Items_Array.FindByPredicate([&SourceSlot](const FInventorySlot& InventorySlot)
	{
		return InventorySlot.Slot == SourceSlot;
	});

	
	//Construct Item
	//TODO Check if the adresses are the same of Data Asset
	Server_ConstructItem(FItemDefinition(SourceInventorySlot.Item->GetItemConfig()));
	
	//Server_AddItemDefinitionToFirstAvailableSlot();
}

void UMC_InventoryComponent::FindItemsByFilter(const FInventoryItemFilter& InventoryItemFilter, TArray<UMC_Item*>& OutItems) const
{
#if !UE_BUILD_SHIPPING

	CHECK_NUM_FIELDS(FInventoryItemFilter::StaticStruct(), 5)
	
    // Warn if no filter criteria are enabled
    if (!(InventoryItemFilter.bUseCategoryFilter || 
          InventoryItemFilter.bUseItemClass		 || 
          InventoryItemFilter.bUseMaxTier		 || 
          InventoryItemFilter.bUseMinTier		 || 
          InventoryItemFilter.bUseRarityFilter))
    {
        UE_LOGFMT(LogInventory, Error, "All inclusive filters are disabled");

    	//Clear OutItems and return
    	OutItems.Empty();
    	return;
    }
#endif
	
    // Get all items from inventory
    TArray<UMC_Item*> TempItems;
    GetInventoryItems(TempItems);

    // Process each item in the inventory
    for (UMC_Item* Item : TempItems)
    {
        // Basic validity checks
        if (!IsValid(Item)) continue;
    	
        UMC_DT_ItemConfig* ItemConfig = Item->GetItemConfig();
        if (!IsValid(ItemConfig)) continue;

        // Inclusive filters
        if (InventoryItemFilter.bUseItemClass && InventoryItemFilter.ItemClass && Item->GetClass() != InventoryItemFilter.ItemClass) continue;

        if ((InventoryItemFilter.bUseMinTier && (ItemConfig->ItemTier < InventoryItemFilter.MinTier)) ||
			(InventoryItemFilter.bUseMaxTier && (ItemConfig->ItemTier > InventoryItemFilter.MaxTier))) continue;

        if (InventoryItemFilter.bUseRarityFilter && ItemConfig->ItemRarity > InventoryItemFilter.ItemRarity) continue;

        if (InventoryItemFilter.bUseCategoryFilter && InventoryItemFilter.ItemCategory != ItemConfig->ItemCategory) continue;

        // Passed all filters
        OutItems.Add(Item);
    }

	//Log Warning
	if (OutItems.Num() == 0)
	{
		UE_LOGFMT(LogMiningSystem, Warning, "Inventory doesn't contain the requested item. File: {0}, Line: {1}", __FILE__, __LINE__);
	}
}

UMC_Item* UMC_InventoryComponent::FindBestItemInInventory(const TSubclassOf<UMC_Item>& ItemClass) const
{
	// Inventory should never be nullptr!
	TArray<UMC_Item*> OutItems;

	//Create Filter
	FInventoryItemFilter InventoryItemFilter;

	//Set Filters
	InventoryItemFilter.ItemClass = ItemClass;
	InventoryItemFilter.bUseItemClass = true;

	// Get all Items of given class from the inventory
	FindItemsByFilter(InventoryItemFilter, OutItems);
	
	// Assuming Tier1 is the lowest tier
	UMC_Item* BestItem = nullptr;
	EItemTier HighestTier = EItemTier::Tier1;
	
	// Iterate through all items to find the one with the highest tier
	for (UMC_Item* Item : OutItems)
	{
		if (Item->GetItemConfig()->ItemTier > HighestTier)
		{
			BestItem = Item;
			HighestTier = BestItem->GetItemConfig()->ItemTier;
		}
	}
	
	return BestItem;
}

void UMC_InventoryComponent::Server_DropItemBySlot(uint8 Slot)
{
	//TODO: Create a bag at player's location
}

void UMC_InventoryComponent::Server_DropItemInstance(UMC_Item* Item)
{
	//TODO: Create a bag at player's location
}

UMC_Item* UMC_InventoryComponent::Server_ConstructItem(const FItemDefinition& ItemDefinition)
{
	//Create Item
	UMC_Item* Item = NewObject<UMC_Item>(GetOwner(), ItemDefinition.ItemConfig->ItemClass);

	//Set replication
	AddReplicatedSubObject(Item);

	//Set values from Item Definition
	Item->Server_SetItemConfig(ItemDefinition.ItemConfig);
	
	return Item;
}

void UMC_InventoryComponent::Server_DestroyItem_Implementation(const FInventorySlot& ItemToDestroy)
{
	if (!ItemToDestroy.Item)
	{
		UE_LOG(LogInventory, Warning, TEXT("Attempted to destroy invalid item"));
		return;
	}
	
	// Remove from replication
	RemoveReplicatedSubObject(ItemToDestroy.Item);
	
	// Remove from inventory array
	Items_Array.RemoveSingle(ItemToDestroy);
}

void UMC_InventoryComponent::Server_InitializeInventory_Implementation()
{
#if WITH_EDITOR

	// Validate the default inventory data asset reference
	if (IsValid(DefaultInventory))
	{
		// Initialize inventory with items from the data asset
		for (const auto& Element : DefaultInventory->DefaultItems)
		{
			//Create Item Definition
			FItemDefinition ItemDefinition(Element.ItemConfig);
			
			// Add to inventory array with specified slot
			Items_Array.Add(FInventorySlot(Element.Slot, Server_ConstructItem(ItemDefinition)));
		}
	}
	else
	{
		// Log warning if data asset is missing
		UE_LOGFMT(LogInventory, Warning, "Default Inventory not initialized - DataAsset is null. File: {0}, Line: {1}", __FILE__, __LINE__);
	}
#endif
}

void UMC_InventoryComponent::OnRep_Items_Array()
{
	//Reset Map
	Items.Reset();
	
	// Iterate through the replicated array and update the map.
	for (auto& Element : Items_Array)
	{
		// Add the item into the TMap using the slot as the key.
		Items.Add(Element.Slot, Element.Item);
	}
	
	// Refresh the inventory widget to reflect the changes
	Client_RefreshInventoryWidget();

	//Get Mining System Component
	UMC_MiningSystemComponent* MiningSystemComponent = GetOwner()->FindComponentByClass<UMC_MiningSystemComponent>();
	
	//Try to cache the inventory items
	MiningSystemComponent->Server_CacheMiningToolsFromInventory();
}
