#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MC_ItemManager.generated.h"

/** Forward Declarations */
class UMC_DT_ItemConfig;

/** 
 * Manages item data and generation systems. Handles item loading, 
 * power calculations, and weighted random item generation.
 */
UCLASS()
class MINECORE_API UMC_ItemManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Initializes subsystem and loads required assets */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Calculates total power sum + returns individual item powers */
	UFUNCTION(BlueprintCallable, Category = "Item Manager") 
	virtual int32 CalculateTotalPower(TArray<int32>& ItemsPowerArray) const;

	/** Generates ItemsNum random items using power values as weights */
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	virtual void GenerateWeightedRandomItems(const int32 NumItemsToGenerate, TArray<UMC_DT_ItemConfig*>& OutSelectedItems) const;
    
protected:
	/** Loads all item definitions from folders */
	void Server_LoadAllItemsFromFolders(const FPrimaryAssetType& PrimaryAssetType = "ItemConfig");
    
	/** All loaded item configs */
	UPROPERTY()
	TMap<FPrimaryAssetId, UMC_DT_ItemConfig*> ItemDataStorage;
};
