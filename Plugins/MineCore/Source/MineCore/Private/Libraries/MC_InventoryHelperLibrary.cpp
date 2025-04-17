#include "Libraries/MC_InventoryHelperLibrary.h"
#include "Components/MC_InventoryComponent.h"
#include "GameFramework/PlayerController.h"
#include "Items/MC_Item.h"
#include "Player/MC_PlayerCharacter.h"

bool UMC_InventoryHelperLibrary::CanItemsStack(const UMC_Item* ItemA, const UMC_Item* ItemB)
{
	// Retrieve item config data for both items
	const UMC_DT_ItemConfig* ItemConfigA = ItemA->GetItemConfig();
	const UMC_DT_ItemConfig* ItemConfigB = ItemB->GetItemConfig();

	// Validate that both item configs exist
	checkf(ItemConfigA && ItemConfigB, TEXT("CanItemsStack: Missing item configuration for one or both items"));

	// Verify stack compatibility:
	// 1. Items must have the same maximum stack size
	// 2. Combined stacks must not exceed max stack size
	const bool bCanStackBySize = (ItemConfigA->MaxStackSize == ItemConfigB->MaxStackSize) && 
							     (ItemA->GetCurrentStack() + ItemB->GetCurrentStack() <= ItemConfigA->MaxStackSize);

	// Verify item type compatibility:
	// Items must share the same class, rarity and tier to be stackable
	const bool bCanStackByType = (ItemConfigA->ItemClass == ItemConfigB->ItemClass)   && 
								 (ItemConfigA->ItemRarity == ItemConfigB->ItemRarity) &&
	   							 (ItemConfigA->ItemTier == ItemConfigB->ItemTier);
	
	return bCanStackBySize && bCanStackByType;
}

int32 UMC_InventoryHelperLibrary::GetRemainingStackSpace(const UMC_Item* ItemA)
{
	return ItemA->GetItemConfig()->MaxStackSize - ItemA->GetCurrentStack();
}

void UMC_InventoryHelperLibrary::FindItemsByDefinition(const UMC_InventoryComponent* InventoryComponent, const FItemDefinition& ItemDefinition, TArray<FInventorySlot>& OutItems)
{
	// Clear output array to ensure we don't return stale data
	OutItems.Empty();

	// Validate input inventory component
	if (!InventoryComponent)
	{
		UE_LOG(LogInventory, Warning, TEXT("FindItemsByDefinition: Invalid InventoryComponent"));
		return;
	}

	// Search through all inventory slots
	for (const FInventorySlot& InventorySlot : InventoryComponent->GetItemsArray())
	{
		// Compare slot's item definition with the target definition
		if (InventorySlot.Item && InventorySlot == ItemDefinition)
		{
			// Add matching item to results
			OutItems.Add(InventorySlot);
		}
	}
}

bool UMC_InventoryHelperLibrary::IsInventoryFull(const UMC_InventoryComponent* InventoryComponent)
{
	if (!InventoryComponent)
	{
		UE_LOG(LogInventory, Warning, TEXT("IsInventoryFull: Invalid InventoryComponent"));
		return false;
	}

	const int32 CurrentItemCount = InventoryComponent->GetItemsArray().Num();
	const int32 MaxSlots = InventoryComponent->GetMaxSlots();
    
	return CurrentItemCount >= MaxSlots;
}

void UMC_InventoryHelperLibrary::ConvertInventoryToJSON(const APlayerController* const PlayerController)
{
	// Set the path to the "Saved" folder where the JSON file will be stored
	FString SavedFolderDir = FPaths::ProjectSavedDir() / TEXT("Mine Core") / FString::Printf(TEXT("Inventory_%s.json"), *FGuid::NewGuid().ToString(EGuidFormats::Digits).Left(8));

	// Create a JSON root object
	TSharedPtr<FJsonObject> RootJsonObject = MakeShareable(new FJsonObject());

	// Create an array to store inventory item data
	TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;

	// Get the player character
	AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOGFMT(LogJson, Error, "Failed to get MC Player Character.");
		return;
	}

	// Get inventory items from the player's inventory component
	TMap<uint8, UMC_Item*> Items;
	PlayerCharacter->GetInventoryComponent()->GetInventoryItemsMap(Items);

	// Retrieve references to enum classes used for item properties
	UEnum* EnumTier = FindFirstObject<UEnum>(TEXT("EItemTier"));
	UEnum* EnumRarity = FindFirstObject<UEnum>(TEXT("EItemRarity"));
	UEnum* EnumCategory = FindFirstObject<UEnum>(TEXT("EItemCategory"));

	// Validate enum references
	if (!EnumTier || !EnumRarity || !EnumCategory)
	{
		UE_LOGFMT(LogJson, Error, "Failed to find item enum references.");
		return;
	}

	// Iterate through the inventory slots and serialize item data
	for (const auto& ItemPair : Items)
	{
		// Extract slot number and item pointer
		uint8 Slot = ItemPair.Key;
		UMC_Item* ItemPtr = ItemPair.Value;
		
		// Create a JSON object to store item properties
		TSharedPtr<FJsonObject> ItemJsonObject = MakeShareable(new FJsonObject());

		// Set item properties
		ItemJsonObject->SetNumberField(TEXT("Slot"), Slot);
		ItemJsonObject->SetStringField(TEXT("Class Name"), ItemPtr->GetItemConfig()->ItemClass->GetName());
		ItemJsonObject->SetStringField(TEXT("Name"), ItemPtr->GetItemConfig()->ItemName.ToString());
		ItemJsonObject->SetStringField(TEXT("Tier"), EnumTier->GetNameStringByIndex(static_cast<uint8>(ItemPtr->GetItemConfig()->ItemTier)));
		ItemJsonObject->SetStringField(TEXT("Rarity"), EnumRarity->GetNameStringByIndex(static_cast<uint8>(ItemPtr->GetItemConfig()->ItemRarity)));
		ItemJsonObject->SetStringField(TEXT("Category"), EnumCategory->GetNameStringByIndex(static_cast<uint8>(ItemPtr->GetItemConfig()->ItemCategory)));
		ItemJsonObject->SetNumberField(TEXT("Weight"), ItemPtr->GetItemConfig()->Weight);
		ItemJsonObject->SetNumberField(TEXT("MaxStackSize"), ItemPtr->GetItemConfig()->MaxStackSize);

		// Add item JSON object to the array
		ItemsJsonArray.Add(MakeShareable(new FJsonValueObject(ItemJsonObject)));
	}

	// Store the items array in the root JSON object
	RootJsonObject->SetArrayField(TEXT("Inventory"), ItemsJsonArray);

	// Create a string to store the serialized JSON data
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

	// Serialize the root JSON object into the output string
	if (FJsonSerializer::Serialize(RootJsonObject.ToSharedRef(), Writer))
	{
		// Attempt to save the JSON string to a file
		if (FFileHelper::SaveStringToFile(OutputString, *SavedFolderDir))
		{
			UE_LOGFMT(LogJson, Log, "Inventory successfully saved to JSON file: {0}", *SavedFolderDir);
		}
		else
		{
			UE_LOGFMT(LogJson, Error, "Failed to save inventory JSON file.");
		}
	}
	else
	{
		UE_LOGFMT(LogJson, Error, "Failed to serialize inventory to JSON.");
	}
}
float UMC_InventoryHelperLibrary::CalculateTotalWeight(const UMC_InventoryComponent* const InventoryComponent)
{
	float TotalWeight = 0.0f;

	// Safety check - return 0 weight for invalid inventory
	if (!InventoryComponent)
	{
		UE_LOG(LogInventory, Warning, TEXT("CalculateTotalWeight: Invalid InventoryComponent"));
		return 0.0f;
	}

	// Sum weights of all valid items in inventory
	for (const FInventorySlot& InventorySlot : InventoryComponent->GetItemsArray())
	{
		TotalWeight += InventorySlot.Item->GetItemConfig()->Weight;
	}

	return TotalWeight;
}
