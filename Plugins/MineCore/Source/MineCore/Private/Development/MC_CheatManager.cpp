#include "Development/MC_CheatManager.h"

#include "Components/MC_InventoryComponent.h"
#include "Player/MC_PlayerCharacter.h"

void UMC_CheatManager::AddItemToInventory(FString InputString)
{
	// Check if the class was found and is valid
	if (UClass* ItemClass = FindAndPrintClass(InputString))
	{
		// Ensure the class is a child of UMC_Item (the base item class)
		checkf(ItemClass->IsChildOf(UMC_Item::StaticClass()), TEXT("We can't create an item from the given class: %s"), *ItemClass->GetName());

		// Create a new instance of the item using the found class
		UMC_Item* Item = NewObject<UMC_Item>(GetPlayerController(), ItemClass);

		// Get the player character to interact with its inventory
		AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(GetPlayerController()->GetPawn());

		// Add the created item to the player's inventory in the first available slot
		PlayerCharacter->GetInventoryComponent()->AddItemToFirstAvailableSlot(Item);
	}
}

UClass* UMC_CheatManager::FindAndPrintClass(FString InputString)
{
	FString ClassName;
    
	// Extract the class name from the input string using the "StaticClass=" prefix
	if (FParse::Value(*InputString, TEXT("StaticClass="), ClassName))
	{
		// Try to find the class by its name in the engine's object registry
		if (UClass* FoundClass = FindFirstObject<UClass>(*ClassName))
		{
			UE_LOGFMT(LogTemp, Log, "Class Name: {0}", FoundClass->GetName());
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
