#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNodeSpawner.generated.h"

/** Determines spawner behaviour */
UENUM(BlueprintType)
enum class EResourceSpawnerMode : uint8
{
	SingleSpawnAndDestroy	 UMETA(DisplayName = "Single Spawn", ToolTip = "Spawns resource nodes once and destroys this spawner immediately after completion"),
	RespawnWithCooldown		 UMETA(DisplayName = "Continuous Respawn", ToolTip = "Periodically respawns resource nodes (destroying old ones) at configured intervals. Spawner persists indefinitely.")
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
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner", meta = (AllowedClasses = "MC_DT_ResourceNodeConfig"))
	TSet<FPrimaryAssetId> ResourceNodeAssetIDs;
	
	/** Determines spawner behavior after completing spawn cycle */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner")
	EResourceSpawnerMode SpawnerMode = EResourceSpawnerMode::RespawnWithCooldown;

	/** Delay between node spawns in RespawnWithCooldown mode (seconds) */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner", meta=(EditCondition="SpawnerMode == EResourceSpawnerMode::RespawnWithCooldown", Units = "Seconds", ClampMin = "0.1"))
	float NodeSpawnInterval = 5.0f;
	
	/** Delay between node destruction in RespawnWithCooldown mode (seconds) */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner", meta=(EditCondition="SpawnerMode == EResourceSpawnerMode::RespawnWithCooldown", Units = "Seconds", ClampMin = "0.1"))
	float NodeDestructionInterval  = 5.0f;

	/** Number of resource nodes to spawn in a single batch */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Resource Node Spawner", meta = (ClampMin = "1"))
	int32 SingleSpawnBatchSize = 1;	

	/** Initiates spawning of all registered resource nodes */
	UFUNCTION(BlueprintCallable, Category = "Resource Node Spawner")
	void Server_BeginResourceNodeSpawning();
};