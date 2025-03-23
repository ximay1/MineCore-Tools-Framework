#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ResourceNode/MC_ResourceNodeConfig.h"
#include "MC_ResourceNode.generated.h"

class UMC_ResourceNodeConfig;
struct FStreamableHandle;

/** AMC_ResourceNode represents a resource node in the game world. */
UCLASS()
class MINECORE_API AMC_ResourceNode : public AActor
{
    GENERATED_BODY()
    
public:
    /** Constructor */
    AMC_ResourceNode();

    /** Events */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    /** Displays the mining progress widget on the client. */
    UFUNCTION(Client, Reliable)
    virtual void Client_DisplayMiningProgressWidget(APlayerController* PlayerController);
    
    /** Displays a widget informing the player that mining is denied. */
    UFUNCTION(Client, Reliable)
    virtual void Client_DisplayMiningDeniedWidget(APlayerController* PlayerController);
    
    /**
     * Initiates the mining process on the node. */
    UFUNCTION(Server, Reliable, BlueprintCallable)
    virtual void Server_StartMining(APlayerController* PlayerController);
    
    /** Checks if the resource node is in a state that allows mining. */
    virtual bool CanBeMined() const;

    /** Stops the mining process. */
    virtual void StopMining(bool IsPlayerControllerValid);
    
    /** Called when the player mines a resource. */
    virtual void PlayerMineResource(APlayerController* PlayerController);
    
protected:
    /** Called when the game starts or when spawned. */
    virtual void BeginPlay() override;

    /** Refreshes the resource node's state (e.g. for resource regeneration). This function is invoked periodically via a timer. */
    UFUNCTION(BlueprintCallable)
    virtual void ResourceNode_Refresh();

    /** Validates the PlayerController. */
    bool EnsureValidPlayerController(APlayerController* PlayerController);
    
    /** Current state of the resource node. */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    EResourceNodeState ResourceNodeState;
    
    /** Pointer to the resource node config asset. */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Resource Node | Config")
    TObjectPtr<UMC_ResourceNodeConfig> ResourceNodeConfig;
    
    /** Static mesh component representing the resource node. */
    UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    /** The StaticMesh currently applied to the Static Mesh Component */
    UPROPERTY(ReplicatedUsing = OnRep_CurrentStaticMesh, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMesh> CurrentStaticMesh;

    /** Called when the CurrentStaticMesh property is replicated */
    UFUNCTION()
    void OnRep_CurrentStaticMesh();
   
    /** Updates the static mesh's material based on the current resource node state. */
    void SetStaticMeshForCurrentState();

    /** Applies resource node config. Sets up timers for state refresh and initializes the material. */
    void ApplyResourceNodeConfig();

private:
    /** Timer handle for refreshing the resource node state. */
    FTimerHandle ResourceNodeSpawnTimerHandle;
    
    /** Timer handle for managing the mining process. */
    FTimerHandle MineResourceNodeTimerHandle;
};
