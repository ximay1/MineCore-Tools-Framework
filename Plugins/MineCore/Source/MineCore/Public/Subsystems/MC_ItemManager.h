#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MC_ItemManager.generated.h"

/** Forward Declarations */
class UMC_DT_ItemConfig;
enum class EItemTier : uint8;
enum class EItemRarity : uint8;

/** 
 * Manages item data and generation systems. Handles item loading, 
 * power calculations, and weighted random item generation.
 */
UCLASS()
class MINECORE_API UMC_ItemManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Returns this subsystem */
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	static FORCEINLINE UMC_ItemManager* Get(UWorld* World) { return World->GetSubsystem<UMC_ItemManager>(); }
	
	/** Initializes subsystem and loads required assets */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Calculates total power sum + returns individual item powers */
	UFUNCTION(BlueprintCallable, Category = "Item Manager") 
	virtual int32 Server_CalculateTotalPower(TArray<int32>& ItemsPowerArray) const;

	/** Generates ItemsNum random items using power values as weights */
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	virtual void Server_GenerateWeightedRandomItems(const int32 NumItemsToGenerate, TArray<UMC_DT_ItemConfig*>& OutSelectedItems) const;
	
	/** Generates unique item identifier from components (Name_Tier_Rarity) */
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void GenerateItemIdentifier(const FString& ItemName, EItemTier Tier, EItemRarity Rarity, FString& OutName) const;
protected:

	/** Return Primary Asset Type for primary data assets which contain information about items */
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FPrimaryAssetType GetPrimaryDataAssetType() const;
	
	/** Called when item assets finish asynchronous loading. Populates the item database with loaded configs. */
	void ItemsLoaded_Delegate();
	
	/** Loads all item definitions from folders */
	void Server_LoadAllItemsFromFolders(const FPrimaryAssetType& PrimaryAssetType = "ItemConfig");
    
	/** All loaded item configs
	 * Key is FString which is built from [ItemName]_[Tier]_[Rarity]
	 * Example : Sword_4_2
	 */
	UPROPERTY()
	TMap<FString, UMC_DT_ItemConfig*> ItemDataStorage;
};
