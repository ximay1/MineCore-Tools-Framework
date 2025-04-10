#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MC_ItemManager.generated.h"

/** Forward Declarations */
class UMC_DT_ItemConfig;

UCLASS()
class MINECORE_API UMC_ItemManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Events */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Calculates the total power sum of all items in the storage. */
	UFUNCTION(BlueprintCallable, Category = "Item Manager", meta=(BlueprintThreadSafe))
	virtual int32 CalculateTotalItemsPower() const;
	
protected:

	/** Load Items Definitions */
	void Server_LoadAllItemsFromFolders(const FPrimaryAssetType& PrimaryAssetType = "ItemConfig");
	
	/** Item storage */
	UPROPERTY()
	TMap<FPrimaryAssetId, UMC_DT_ItemConfig*> ItemDataStorage;
};
