#include "Development/MC_CheatManager.h"
#include "Components/MC_InventoryComponent.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "Player/MC_PlayerCharacter.h"

void UMC_CheatManager::SerializeInventoryToJSON()
{
	// Set the path to the "Saved" folder where the JSON file will be stored
	FString SavedFolderDir = FPaths::ProjectSavedDir() / TEXT("Mine Core") / FString::Printf(TEXT("Inventory_%s.json"), *FGuid::NewGuid().ToString(EGuidFormats::Digits).Left(8));

	// Create a JSON root object
	TSharedPtr<FJsonObject> RootJsonObject = MakeShareable(new FJsonObject());

	// Create an array to store inventory item data
	TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;

	// Get the player character
	AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(GetPlayerController()->GetPawn());
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
