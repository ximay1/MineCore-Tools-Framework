#include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "Data/ResourceNode/MC_ResourceNodeConfig.h"
#include "Engine/AssetManager.h"

AMC_ResourceNode::AMC_ResourceNode() : ResourceNodeState(static_cast<EResourceNodeState>(FMath::RandRange(1,4)))
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    
    // Create the static mesh component and set it as the root
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;
}

void AMC_ResourceNode::Server_StartMining_Implementation(APlayerController* PlayerController)
{
    //Check if the player is able to mine
    if (!Server_CanBeMined())
    {
        //Create Delegate
        FTimerDelegate MineResourceNodeDelegate = FTimerDelegate::CreateUObject(this, AMC_ResourceNode::PlayerMineResource, PlayerController);
        
        //Set timer
        GetWorldTimerManager().SetTimer(MineResourceNodeTimerHandle, MineResourceNodeDelegate, ResourceNodeConfigPtr->MiningTime, true);
        
        //TODO: Create progress bar widget
    }
    else
    {
        //If the player can't mine, we have to show a error widget
        Client_DisplayMiningDeniedWidget(PlayerController);
    }
}

void AMC_ResourceNode::Server_StopMining_Implementation(APlayerController* PlayerController)
{
    
}

void AMC_ResourceNode::Client_DisplayMiningDeniedWidget_Implementation(APlayerController* PlayerController)
{
    //Get Player Controller
    if (PlayerController)
    {
        //TODO:Create Widget and show widget
        UE_LOG(LogTemp, Error, TEXT("Displaying mining denied widget from server"));
    }
}

//#if WITH_SERVER_CODE
bool AMC_ResourceNode::Server_CanBeMined() const
{
    return true;
}

void AMC_ResourceNode::PlayerMineResource(APlayerController* PlayerController)
{
    //Check
    checkf(PlayerController, TEXT("Player Controller is nullptr, AMC_ResourceNode::PlayerMineResource"))

    //Clear Timer
    GetWorldTimerManager().ClearTimer(MineResourceNodeTimerHandle);

    //Check if ResourceNodeState isn't STATE_1
    if (ResourceNodeState != EResourceNodeState::STATE_1)
    {
        //Decrease State of this Node
        ResourceNodeState = static_cast<EResourceNodeState>(static_cast<uint8>(ResourceNodeState) - 1);

        //Start again mining
        Server_StartMining(PlayerController);
    }
    else
    {
        //Stop Mining
        Server_StopMining(PlayerController);
    }
}
//#endif

EResourceNodeType AMC_ResourceNode::GetMiningResourceType() const
{
    return ResourceNodeConfigPtr->ResourceNodeType;
}

void AMC_ResourceNode::BeginPlay()
{
    Super::BeginPlay();

    #if !UE_BUILD_SHIPPING
        // Valid if the ResourceNodeConfigId is set
        if (!ResourceNodeConfigId.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("ResourceNodeConfigId is not valid"));
            
            // If the config ID is invalid, destroy this actor to prevent issues
            Destroy(true);
            return;
        }
    #endif

    // Get a reference to the global Asset Manager
    UAssetManager& AssetManager = UAssetManager::Get();

    // Check if the configuration asset is already loaded
    if (UObject* AlreadyLoadedAsset = AssetManager.GetPrimaryAssetObject(ResourceNodeConfigId))
    {
        // Try to cast the loaded asset to the expected UMC_ResourceNodeConfig class
        if (UMC_ResourceNodeConfig* LoadedConfig = Cast<UMC_ResourceNodeConfig>(AlreadyLoadedAsset))
        {
            // If the asset is valid and successfully cast, apply its configuration
            ApplyResourceNodeConfig(LoadedConfig);
        }
        else
        {
            // Log a warning if the asset exists but isn't of the expected type
            UE_LOG(LogTemp, Warning, TEXT("Failed to cast already loaded asset to UMC_ResourceNodeConfig"));
        }
    }
    else // If the asset is not yet loaded, request it asynchronously
    {
        // Define a delegate that will be called once the asset is loaded
        FStreamableDelegate LoadConfigDelegate = FStreamableDelegate::CreateWeakLambda(this, [this]()
        {
            #if !UE_BUILD_SHIPPING
                // Check if the asset loading handle is valid
                if (!ResourceNodeConfigHandle)
                {
                    UE_LOG(LogTemp, Error, TEXT("ResourceNodeConfigHandle is null after async load!"));
                    return;
                }
            #endif

            // Attempt to retrieve the loaded asset from the handle
            UMC_ResourceNodeConfig* LoadedConfig = Cast<UMC_ResourceNodeConfig>(ResourceNodeConfigHandle->GetLoadedAsset());

            // Ensure that the asset was successfully loaded and cast
            ensureAlwaysMsgf(LoadedConfig, TEXT("Failed to load ResourceNodeConfig asset."));

            // Apply the configuration once it's successfully loaded
            ApplyResourceNodeConfig(LoadedConfig);
        });

        // Request the asset to be loaded asynchronously
        ResourceNodeConfigHandle = AssetManager.LoadPrimaryAsset(ResourceNodeConfigId,{}, MoveTemp(LoadConfigDelegate));
    }
}

void AMC_ResourceNode::ResourceNode_Refresh()
{
    // If the node is already in the final state, exit the function
    if (ResourceNodeState == EResourceNodeState::STATE_4) { return; }

    // Increment the resource node state by 1
    ResourceNodeState = static_cast<EResourceNodeState>(static_cast<uint8>(ResourceNodeState) + 1);

    //Set material 
    SetMaterialForCurrentState();
}
void AMC_ResourceNode::SetMaterialForCurrentState()
{
    // Apply the material to the static mesh
    if (UMaterial* Material = *ResourceNodeConfigPtr->ResourceNodeMaterials.Find(ResourceNodeState))
    {
        //Set Material
        StaticMesh->SetMaterial(0, Material);
    }
    else
    {
        //Log Error
        UE_LOG(LogTemp, Error, TEXT("Material not found for ResourceNodeState: %d in AMC_ResourceNode::SetMaterialForCurrentState"), static_cast<uint8>(ResourceNodeState));
    }
}

void AMC_ResourceNode::ApplyResourceNodeConfig(UMC_ResourceNodeConfig* LoadedConfig)
{
    if (!ensureAlways(LoadedConfig)) { return; }

    ResourceNodeConfigPtr = LoadedConfig;

    // Set the timer to refresh the resource node
    GetWorldTimerManager().SetTimer(
        ResourceNodeSpawnTimerHandle,
        this,
        &AMC_ResourceNode::ResourceNode_Refresh,
        ResourceNodeConfigPtr->TimeToIncreaseState,
        true
    );

    // Set the initial material
    SetMaterialForCurrentState();
}
