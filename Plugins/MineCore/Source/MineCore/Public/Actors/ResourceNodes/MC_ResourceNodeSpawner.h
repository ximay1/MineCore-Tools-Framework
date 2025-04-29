#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNodeSpawner.generated.h"

UCLASS()
class MINECORE_API AMC_ResourceNodeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	AMC_ResourceNodeSpawner();

protected:
	/** ~ Begin AActor Interface */
	virtual void BeginPlay() override;
	/** ~ End AActor Interface */

	/** Collection of Primary Asset IDs (Resource Nodes) which will be spawned by this spawner */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner")
	TSet<FPrimaryAssetId> ResourceNodeAssetIDs;
	
	/** Initiates spawning of all registered resource nodes */
	UFUNCTION(BlueprintCallable, Category = "Resource Node Spawner")
	void Server_BeginResourceNodeSpawning();
};
