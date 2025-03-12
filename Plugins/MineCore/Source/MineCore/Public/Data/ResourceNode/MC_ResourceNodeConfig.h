#pragma once

#include "CoreMinimal.h"
#include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "Engine/DataAsset.h"
#include "MC_ResourceNodeConfig.generated.h"

UCLASS()
class MINECORE_API UMC_ResourceNodeConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("ResourceNodeConfig", GetFName()); }

	// A TMap that associates each resource node state (EResourceNodeState) with a material (UMaterial*).  
	// Used to dynamically assign the appropriate material based on the resource node's current state.  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	TMap<EResourceNodeState, UMaterial*> ResourceNodeMaterials;

	// Time interval (in seconds) to increase the state by 1.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	float TimeToIncreaseState = 5.0f;

	//Type of the resource node
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	EResourceNodeType ResourceNodeType;
};
