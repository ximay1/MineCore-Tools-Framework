#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNode.generated.h"

class UMC_ResourceNodeConfig;
struct FStreamableHandle;

UENUM(BlueprintType)
enum class EResourceNodeState : uint8
{
    STATE_1     UMETA(DisplayName = "State 1"), // No resources available
    STATE_2     UMETA(DisplayName = "State 2"),
    STATE_3     UMETA(DisplayName = "State 3"),
    STATE_4     UMETA(DisplayName = "State 4")
};

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

UCLASS(NotPlaceable)
class MINECORE_API AMC_ResourceNode : public AActor
{
    GENERATED_BODY()
    
public:
    // Constructor
    AMC_ResourceNode();

    /** Starts the mining process on the node. */
    UFUNCTION(Server, Reliable)
    virtual void Server_StartMining(APlayerController* PlayerController);

    /** Stops the mining process on the node. */
    UFUNCTION(Server, Reliable)
    virtual void Server_StopMining(APlayerController* PlayerController);

    /** Shows the widget if the player is unable to mine */
    UFUNCTION(Client, Reliable)
    virtual void Client_DisplayMiningDeniedWidget(APlayerController* PlayerController);

//#if WITH_SERVER_CODE
    /** Checks if the node can be mined. */
    virtual bool Server_CanBeMined() const;

    /** Called when the player mines a resource */
    void PlayerMineResource(APlayerController* PlayerController);
//#endif
    
    /** Returns the type of resource the node yields. */
    virtual EResourceNodeType GetMiningResourceType() const;
    
protected:
    /** Called when the game starts or when spawned */
    virtual void BeginPlay() override;

    /** Function called by the timer to refresh the resource node and increment its state. */
    UFUNCTION(BlueprintCallable)
    virtual void ResourceNode_Refresh();

protected:
    /** Current state of the resource node */
    UPROPERTY(BlueprintReadOnly, Category = "Resource Node")
    EResourceNodeState ResourceNodeState;

    /** Asset Id for the resource node configuration */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PrimaryAssetLoaderComponent")
    FPrimaryAssetId ResourceNodeConfigId;
    
    /** Pointer to the resource node configuration */
    UPROPERTY(BlueprintReadWrite, Category = "Resource Node | Config")
    TObjectPtr<UMC_ResourceNodeConfig> ResourceNodeConfigPtr;
    
    /** Static mesh component representing the resource node */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node")
    TObjectPtr<UStaticMeshComponent> StaticMesh;
    
private:
    
    /**
    * Set the material for the current resource node state. 
    * This function should be called whenever the resource node state changes.
    */
    void SetMaterialForCurrentState();

    /**
    * Applies the loaded resource node configuration.
    * Sets the refresh timer and set the material for the current state.
    */
    void ApplyResourceNodeConfig(UMC_ResourceNodeConfig* LoadedConfig);
    
    /** Timer handle for managing resource node updates */
    FTimerHandle ResourceNodeSpawnTimerHandle;
    
    /** Handle for asynchronously loading the resource node configuration */
    TSharedPtr<FStreamableHandle> ResourceNodeConfigHandle;

    /** Timer handle for managing the mining node */
    FTimerHandle MineResourceNodeTimerHandle;
};