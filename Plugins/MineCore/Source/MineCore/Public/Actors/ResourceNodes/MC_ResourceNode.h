#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNode.generated.h"

// Forward declarations
class UMC_ResourceNodeConfig;
struct FStreamableHandle;

/**
 * Enum representing the different states of a resource node.
 */
UENUM(BlueprintType)
enum class EResourceNodeState : uint8
{
    STATE_1 UMETA(DisplayName = "State 1"), // No resources available
    STATE_2 UMETA(DisplayName = "State 2"),
    STATE_3 UMETA(DisplayName = "State 3"),
    STATE_4 UMETA(DisplayName = "State 4")
};

#include "Logging/LogMacros.h"

// Define a log category for resource nodes
DEFINE_LOG_CATEGORY_STATIC(LogResourceNode, Log, All);

// Overloaded subtraction operator for EResourceNodeState
inline EResourceNodeState operator-(const EResourceNodeState NodeState, uint8 Number)
{
    // Cast the enum to uint8 to perform arithmetic operations
    uint8 NewValue = static_cast<uint8>(NodeState);

    // Check if subtraction would cause an underflow (result below 0)
    if (NewValue < Number) 
    {
        // Log a warning about underflow
        UE_LOG(LogResourceNode, Warning, TEXT("Underflow detected in EResourceNodeState subtraction! NodeState: %d, Number: %d"), NewValue, Number);
        
        // Return a fallback value (e.g., the first enum state)
        return EResourceNodeState::STATE_1; 
    }

    // Return the new enum value after subtraction
    return static_cast<EResourceNodeState>(NewValue - Number);
}

// Overloaded addition operator for EResourceNodeState
inline EResourceNodeState operator+(const EResourceNodeState NodeState, uint8 Number)
{
    // Cast the enum to uint8 to perform arithmetic operations
    uint8 NewValue = static_cast<uint8>(NodeState);

    // Check if the addition would exceed the maximum valid value for EResourceNodeState
    const uint8 MaxValue = static_cast<uint8>(EResourceNodeState::STATE_4);

    if (NewValue + Number > MaxValue)
    {
        // Log a warning about overflow
        UE_LOG(LogResourceNode, Warning, TEXT("Overflow detected in EResourceNodeState addition! NodeState: %d, Number: %d"), NewValue, Number);
        
        // Return a fallback value (e.g., the maximum enum state)
        return EResourceNodeState::STATE_4; 
    }

    // Return the new enum value after addition
    return static_cast<EResourceNodeState>(NewValue + Number);
}

/**
 * Enum representing various types of resource nodes.
 */
UENUM(BlueprintType)
enum class EResourceNodeType : uint8
{
    DEFAULT    UMETA(DisplayName = "Default"),
    STONE      UMETA(DisplayName = "Stone"),
    GRANITE    UMETA(DisplayName = "Granite"),
    COAL       UMETA(DisplayName = "Coal"),
    IRON       UMETA(DisplayName = "Iron"),
    SILVER     UMETA(DisplayName = "Silver"),
    GOLD       UMETA(DisplayName = "Gold"),
    GEMSTONE   UMETA(DisplayName = "Gemstone"),
    CRYSTALS   UMETA(DisplayName = "Crystals"),
    TITANIUM   UMETA(DisplayName = "Titanium")
};

/**
 * AMC_ResourceNode represents a resource node in the game world.
 * It manages mining logic, UI feedback, state changes, and resource regeneration.
 */
UCLASS()
class MINECORE_API AMC_ResourceNode : public AActor
{
    GENERATED_BODY()
    
public:
    /** Constructor */
    AMC_ResourceNode();

    /** Events */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    /**
     * Initiates the mining process on the node.
     * Called on the server.
     *
     * @param PlayerController The controller of the player initiating mining.
     */
    UFUNCTION(Server, Reliable, BlueprintCallable)
    virtual void Server_StartMining(APlayerController* PlayerController);

//#if UE_SERVER
    /**
     * Displays the mining progress widget on the client.
     *
     * @param PlayerController The controller of the player.
     */
    UFUNCTION(Client, Reliable)
    virtual void Client_DisplayMiningProgressWidget(APlayerController* PlayerController);
    
    /**
     * Displays a widget informing the player that mining is denied.
     *
     * @param PlayerController The controller of the player.
     */
    UFUNCTION(Client, Reliable)
    virtual void Client_DisplayMiningDeniedWidget(APlayerController* PlayerController);

    /**
     * Checks if the resource node is in a state that allows mining.
     *
     * @return true if mining is allowed, false otherwise.
     */
    virtual bool CanBeMined() const;

    /**
     * Stops the mining process.
     *
     * @param IsPlayerControllerValid Indicates whether the PlayerController is valid.
     */
    virtual void StopMining(bool IsPlayerControllerValid);
    
    /**
     * Called when the player mines a resource.
     *
     * @param PlayerController The controller of the player.
     */
    virtual void PlayerMineResource(APlayerController* PlayerController);
    
protected:
    /** Called when the game starts or when spawned. */
    virtual void BeginPlay() override;

    /**
     * Refreshes the resource node's state (e.g. for resource regeneration).
     * This function is invoked periodically via a timer.
     */
    UFUNCTION(BlueprintCallable)
    virtual void ResourceNode_Refresh();

    /**
     * Validates the PlayerController.
     *
     * @param PlayerController The controller to validate.
     * @return true if valid, false otherwise.
     */
    bool EnsureValidPlayerController(APlayerController* PlayerController);
    
    /** Current state of the resource node. */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    EResourceNodeState ResourceNodeState;

    /** Primary asset ID for the resource node configuration. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PrimaryAssetLoaderComponent")
    FPrimaryAssetId ResourceNodeConfigId;
    
    /** Pointer to the resource node configuration asset. */
    UPROPERTY(BlueprintReadWrite, Category = "Resource Node | Config")
    TObjectPtr<UMC_ResourceNodeConfig> ResourceNodeConfigPtr;
    
//#endif
    
    /** Static mesh component representing the resource node. */
    UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMeshComponent> StaticMesh;

//#if UE_SERVER
private:
    /**
     * Updates the static mesh's material based on the current resource node state.
     */
    void SetMaterialForCurrentState();

    /**
     * Applies the loaded resource node configuration.
     * Sets up timers for state refresh and initializes the material.
     *
     * @param LoadedConfig The loaded configuration asset.
     */
    void ApplyResourceNodeConfig(UMC_ResourceNodeConfig* LoadedConfig);

private:
    /** Timer handle for refreshing the resource node state. */
    FTimerHandle ResourceNodeSpawnTimerHandle;
    
    /** Handle for asynchronously loading the resource node configuration. */
    TSharedPtr<FStreamableHandle> ResourceNodeConfigHandle;

    /** Timer handle for managing the mining process. */
    FTimerHandle MineResourceNodeTimerHandle;
//#endif
};
