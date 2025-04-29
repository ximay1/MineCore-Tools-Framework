#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNodeSpawner.generated.h"

/** Determines spawner behaviour */
UENUM(BlueprintType)
enum class EResourceSpawnerMode : uint8
{
	SingleSpawnAndDestroy	 UMETA(DisplayName = "Single Spawn"),
	RespawnWithCooldown		 UMETA(DisplayName = "Continuous Respawn")
};

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
	
	/** Determines spawner behavior after completing spawn cycle */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner")
	EResourceSpawnerMode SpawnerMode = EResourceSpawnerMode::RespawnWithCooldown;
	
	/** Initiates spawning of all registered resource nodes */
	UFUNCTION(BlueprintCallable, Category = "Resource Node Spawner")
	void Server_BeginResourceNodeSpawning();
};
