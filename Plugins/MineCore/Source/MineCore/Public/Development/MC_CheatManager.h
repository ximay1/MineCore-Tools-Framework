#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "MC_CheatManager.generated.h"

UCLASS()
class MINECORE_API UMC_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	/**
	 * Adds an item to the player's inventory by creating an instance of the specified class and associating it with a data asset.
	 * 
	 * InputString_ClassName The class name in the format "StaticClass=ClassName".
	 * InputString_DataAssetType The type of the data asset in the format "DT_Type=TypeName".
	 * InputString_DataAssetName The name of the data asset in the format "DT_Name=AssetName".
	 *
	 * Example usage:
	 *			AddItemToInventory StaticClass=MC_Pickaxe DT_Type=DT_MiningToolConfig DT_Name=DT_PickaxeItemConfig
	 */
	UFUNCTION(Exec)
	void AddItemToInventory(FString InputString_ClassName, FString InputString_DataAssetType, FString InputString_DataAssetName);

	/** This function serializes the inventory to the json file, which is saved in the Saved Folder which is locatd in the project files */
	UFUNCTION(Exec)
	void SerializeInventoryToJSON();
	
protected:
	/**
	 * Searches for a class by name from the given input string and returns a pointer to the UClass if found.
	 * The expected input format is: "StaticClass=ClassName"
	*/
	UClass* FindClass(FString InputString);
};
