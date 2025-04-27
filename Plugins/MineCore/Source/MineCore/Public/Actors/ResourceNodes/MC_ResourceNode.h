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
    
    /** Initialize resource node */
    UFUNCTION(BlueprintCallable, Category = "Resource Node")
    virtual void Server_Initialize(const FPrimaryAssetId& NewResourceNodeConfigID);
    
    /** Initiates the mining process on the node. */
    UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Resource Node")
    virtual void Server_StartMining(APlayerController* PlayerController);

protected:
    /** Stops the mining process. */
    UFUNCTION(BlueprintCallable, Category = "Resource Node")
    virtual void Server_StopMining(APlayerController* PlayerController);

    /** Checks if the resource node is in a state that allows mining. */
    UFUNCTION(BlueprintCallable, Category = "Resource Node")
    virtual bool Server_CanBeMined(APlayerController* PlayerController);

    /** Called when the player mines a resource. */
    virtual void Server_PlayerMineResource(APlayerController* PlayerController);

    /** Refreshes the resource node's state (e.g. for resource regeneration). */
    virtual void Server_ResourceNode_Refresh();

    /** Updates the static mesh's material based on the current resource node state. */
    void Server_SetStaticMeshForCurrentState() const;

    /** Applies resource node config. Sets up timers for state refresh and initializes the material. */
    void Server_ApplyResourceNodeConfig();
    
    /** Validates the PlayerController. */
    bool Server_EnsureValidPlayerController(const APlayerController* PlayerController);

    /** Clears and removes the mining timer associated with a player. */
    void Server_TryToClearTimerHandle(const APlayerController* PlayerController);

    /** Cleans up the MiningTimers map by removing invalid PlayerController keys. */
    void Server_RemoveInvalidMiningTimers();
    
    /** Resource Node config primary asset id */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    FPrimaryAssetId ResourceNodeConfigID;    

    /** Pointer to the resource node config asset. */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UMC_DT_ResourceNodeConfig> ResourceNodeConfig;
    
    /** Static mesh component representing the resource node. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
    
    /** Current state of the resource node. */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    EResourceNodeState ResourceNodeState;

private:
    /** Timer handle for refreshing the resource node state. Server-only*/
    FTimerHandle ResourceNodeSpawnTimerHandle;

    /** Stores active mining timer handles for each player controller. Server-only */
    UPROPERTY()
    TMap<APlayerController*, FTimerHandle> MiningTimers;
};