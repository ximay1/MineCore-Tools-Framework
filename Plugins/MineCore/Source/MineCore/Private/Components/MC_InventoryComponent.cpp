#include "Components/MC_InventoryComponent.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "MineCore/Public/Data/Items/MC_DT_ItemConfig.h"
#include "MineCoreMacros.h"
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

void UMC_InventoryComponent::CreateInventory()
{
	//TODO: Create Inventory
}

void UMC_InventoryComponent::RefreshInventoryWidget()
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

void UMC_InventoryComponent::AddItemToSlot_Implementation(uint8 Slot, UMC_Item* Item)
{
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
			DropItemInstance(Item);
			
			UE_LOGFMT(LogInventory, Log, "We need to create a bag of items at the player's location when attempting to add an item to the inventory");
			return;
		}
	}
	
	//Add to the inventory
	Items_Array.Add(FInventoryItemsMap(Slot, Item));

	//Call delegate
	OnItemAddedToInventory.Broadcast(Slot, Item);
}

void UMC_InventoryComponent::AddItemToFirstAvailableSlot_Implementation(UMC_Item* Item)
{
	//TODO: Create logic
}

void UMC_InventoryComponent::RemoveItemFromInventory_Implementation(uint8 Slot, EItemAction ItemAction)
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
	FInventoryItemsMap* ItemToDestroy = Items_Array.FindByPredicate([Slot](const FInventoryItemsMap& Item)
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
				// Remove the item from the inventory array
				Items_Array.RemoveSingle(*ItemToDestroy);
				RemoveReplicatedSubObject
				UE_LOGFMT(LogInventory, Log, "Item destroyed from slot {0}.", Slot);
				
				break;
			}
		case EItemAction::Drop:
			{
				// Spawn the item in the world and remove it from inventory
				DropItemInstance(ItemToDestroy->Item);
				UE_LOGFMT(LogInventory, Log, "Item dropped from slot {0}.", Slot);
				
				break;
			}
		default:
			{
				UE_LOGFMT(LogInventory, Warning, "Unhandled item action type for slot {0}.", Slot);
				break;
			}
	};
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

void UMC_InventoryComponent::DropItemBySlot(uint8 Slot)
{
	//TODO: Create a bag at player's location
}

void UMC_InventoryComponent::DropItemInstance(UMC_Item* Item)
{
	//TODO: Create a bag at player's location
}

UMC_Item* UMC_InventoryComponent::ConstructItem(const FItemDefinition& ItemDefinition)
{
	//Create Item
	UMC_Item* Item = NewObject<UMC_Item>(GetOwner());

	//Set replication
	AddReplicatedSubObject(Item);

	//Set values from Item Definition
	Item->SetItemConfig(ItemDefinition.ItemConfig);
	
	return Item;
}

void UMC_InventoryComponent::DestroyItem(FInventoryItemsMap* ItemToDestroy)
{
	if (!ItemToDestroy || !ItemToDestroy->Item)
	{
		UE_LOG(LogInventory, Warning, TEXT("Attempted to destroy invalid item"));
		return;
	}
	
	//1. Call delegate
	OnItemRemovedFromInventory.Broadcast(ItemToDestroy->Slot);
	
	// 2. Remove from inventory array
	Items_Array.RemoveSingle(*ItemToDestroy);
}

void UMC_InventoryComponent::InitializeInventory_Implementation()
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
			Items_Array.Add(FInventoryItemsMap(Element.Slot, ConstructItem(ItemDefinition)));
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
	RefreshInventoryWidget();
}
