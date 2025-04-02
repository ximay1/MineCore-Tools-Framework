#include "Development/MC_CheatManager.h"
#include "Components/MC_InventoryComponent.h"
#include "Engine/AssetManager.h"
#include "Player/MC_PlayerCharacter.h"

void UMC_CheatManager::AddItemToInventory(FString InputString_ClassName, FString InputString_DataAssetType, FString InputString_DataAssetName)
{
	// Check if the class was found and is valid
	if (UClass* ItemClass = FindClass(InputString_ClassName))
	{
		// Ensure the class is a child of UMC_Item (the base item class)
		checkf(ItemClass->IsChildOf(UMC_Item::StaticClass()), TEXT("We can't create an item from the given class: %s"), *ItemClass->GetName());

		FName DataAssetType;
		FName DataAsetName;
		
		// Extract the ID of the primary data asset using the "DT_Type=" prefix 
		if (!FParse::Value(*InputString_DataAssetType, TEXT("DT_Type="), DataAssetType))
		{
			// Log a warning if the input string does not contain "DT_Type="
			UE_LOGFMT(LogTemp, Warning, "Invalid input format. Expected format: DT_Type=DataAssetType");
			return;
		}

		// Extract the Name of the primary data asset using the "DT_Name=" prefix
		if (!FParse::Value(*InputString_DataAssetName, TEXT("DT_Name="), DataAsetName))
		{
			// Log a warning if the input string does not contain "DT_Name="
			UE_LOGFMT(LogTemp, Warning, "Invalid input format. Expected format: DT_Name=DataAssetName");
			return;
		}

		//Combine Data Asset Type and Name
		FPrimaryAssetId PrimaryAssetID(DataAssetType, DataAsetName);

		//Try to load this primary data asset
		UAssetManager::Get().LoadPrimaryAsset(PrimaryAssetID, {}, FStreamableDelegate::CreateLambda([this, ItemClass, PrimaryAssetID]()
		{
			//Get Primary Data Asset Object
			UMC_DT_ItemConfig* ItemConfig = Cast<UMC_DT_ItemConfig>(UAssetManager::Get().GetPrimaryAssetObject(PrimaryAssetID));

			// Create a new instance of the item using the found class
			UMC_Item* Item = NewObject<UMC_Item>(GetPlayerController(), ItemClass);

			//Set Item Config
			Item->SetItemConfig(ItemConfig);
			
			// Get the player character to interact with its inventory
			AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(GetPlayerController()->GetPawn());

			// Add the created item to the player's inventory in the first available slot
			GetCheatsComponent()->AddItemToFirstAvailableSlot_Cheat(Item);
		}));
	}
}

void UMC_CheatManager::SerializeInventoryToJSON()
{
	// Set the path to the "Saved" folder where the JSON file will be stored
	FString SavedFolderDir = FPaths::ProjectSavedDir() / TEXT("Mine Core") / TEXT("Inventory.json");

	// Create a JSON root object
	TSharedPtr<FJsonObject> RootJsonObject = MakeShareable(new FJsonObject());

	// Create an array to store inventory item data
	TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;

	// Get the player character
	AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(GetPlayerController()->GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOGFMT(LogJson, Error, "Failed to get player character.");
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

UClass* UMC_CheatManager::FindClass(FString InputString)
{
	FString ClassName;

	// Extract the class name from the input string using the "StaticClass=" prefix
	if (FParse::Value(*InputString, TEXT("StaticClass="), ClassName))
	{
		// Try to find the class
		if (UClass* FoundClass = FindFirstObject<UClass>(*ClassName))
		{
			return FoundClass; // Return the found class
		}
		else
		{
			// Log a warning if the class was not found
			UE_LOGFMT(LogTemp, Warning, "Class not found: {0}", ClassName);
		}
	}
	else
	{
		// Log a warning if the input string does not contain "StaticClass="
		UE_LOGFMT(LogTemp, Warning, "Invalid input format. Expected format: StaticClass=ClassName");
	}

	// Return nullptr if class was not found or input was invalid
	return nullptr; 
}
