#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "Components/MC_ServerCheatsComponent.h"
#include "MC_CheatManager.generated.h"

UCLASS()
class MINECORE_API UMC_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	/**
	 * Adds an item to the player's inventory by creating an instance of the specified class and associating it with a data asset.
	 * Example: AddItemToInventory StaticClass=MC_Pickaxe DT_Type=DT_MiningToolConfig DT_Name=DT_PickaxeItemConfig
	 */
	UFUNCTION(Exec)
	void AddItemToInventory(FString InputString_ClassName, FString InputString_DataAssetType, FString InputString_DataAssetName);

	/** Serializes the inventory to a JSON file in the Saved folder. */
	UFUNCTION(Exec)
	void SerializeInventoryToJSON();
	
protected:
	/**
	 * Searches for a class by name and returns a pointer to UClass.
	 * Format: "StaticClass=ClassName"
	 */
	UClass* FindClass(FString InputString);

	/** Get the Server Cheat Component */
	FORCEINLINE UMC_ServerCheatsComponent* GetServerCheatsComponent() const { return Cast<UMC_ServerCheatsComponent>(GetPlayerController()->FindComponentByClass<UMC_ServerCheatsComponent>()); }
};

