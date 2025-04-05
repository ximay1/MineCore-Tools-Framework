#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNode.generated.h"

/** Forward Declarations */
class UMC_DT_ResourceNodeConfig;
struct FStreamableHandle;
enum class EResourceNodeState : uint8;

/** AMC_ResourceNode represents a resource node in the game world. */
UCLASS()
class MINECORE_API AMC_ResourceNode : public AActor
{
    GENERATED_BODY()
    
public:
    /** Constructor */
    AMC_ResourceNode();

    /** Displays the mining progress widget on the client-side. */
    UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Resource Node")
    virtual void Client_DisplayMiningProgressWidget();

    /** Displays a widget informing the player that mining is denied on the client-side. */
    UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Resource Node")
    virtual void Client_DisplayMiningDeniedWidget();

    /** Initiates the mining process on the node. */
    UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Resource Node")
    virtual void Server_StartMining(APlayerController* PlayerController);

    /** Stops the mining process. */
    virtual void Server_StopMining(APlayerController* PlayerController);

protected:
    /** Current state of the resource node. */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    EResourceNodeState ResourceNodeState;

    /** Resource Node config primary asset id */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Resource Node | Config")
    FPrimaryAssetId ResourceNodeConfigID;    

    /** Pointer to the resource node config asset. */
    UPROPERTY(BlueprintReadWrite, Category = "Resource Node | Config")
    TObjectPtr<UMC_DT_ResourceNodeConfig> ResourceNodeConfig;
    
    /** Static mesh component representing the resource node. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    /** Called when the game starts or when spawned. */
    virtual void BeginPlay() override;

    /** Refreshes the resource node's state (e.g. for resource regeneration). This function is invoked periodically via a timer. */
    UFUNCTION(BlueprintCallable)
    virtual void ResourceNode_Refresh();

    /** Checks if the resource node is in a state that allows mining. */
    virtual bool CanBeMined(APlayerController* PlayerController);

    /** Called when the player mines a resource. */
    virtual void PlayerMineResource(APlayerController* PlayerController);
    
    /** Validates the PlayerController. */
    virtual bool EnsureValidPlayerController(APlayerController* PlayerController);

    /** Try to clear MineResourceNodeTimerHandle */
    void TryToClearTimerHandle(FTimerHandle TimerHandle);

    /** Updates the static mesh's material based on the current resource node state. */
    virtual void SetStaticMeshForCurrentState();

    /** Applies resource node config. Sets up timers for state refresh and initializes the material. */
    virtual void ApplyResourceNodeConfig();

    /** Cleans up the MiningTimers map by removing all entries with invalid (nullptr) PlayerController keys. */
    UFUNCTION(BlueprintCallable, Category = "Resource Node")
    void Server_RemoveInvalidMiningTimers();
    
private:
    /** Timer handle for refreshing the resource node state. */
    FTimerHandle ResourceNodeSpawnTimerHandle;

    /** Stores active mining timer handles for each player controller. Server-only */
    UPROPERTY()
    TMap<APlayerController*, FTimerHandle> MiningTimers;
};
