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
	
protected:

	/** Load Items Definitions */
	void LoadAllItemsFromFolder(const FPrimaryAssetType& PrimaryAssetType = "ItemConfig");
	
	/** Item storage */
	UPROPERTY()
	TMap<FPrimaryAssetId, UMC_DT_ItemConfig*> ItemDataStorage;
};
