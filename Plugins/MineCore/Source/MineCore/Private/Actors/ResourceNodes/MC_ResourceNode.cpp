#include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "Components/MC_MiningSystemComponent.h"
#include "Engine/AssetManager.h"
#include "Items/MiningTools/MC_Pickaxe.h"
#include "MineCore/Public/Data/ResourceNodes/MC_DT_ResourceNodeConfig.h"
#include "Player/MC_PlayerCharacter.h"

AMC_ResourceNode::AMC_ResourceNode() : ResourceNodeState(static_cast<EResourceNodeState>(0))
{
    //Set Parameters
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    
    // Create the static mesh component and set it as the root
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetIsReplicated(true);
    RootComponent = StaticMeshComponent;
}

void AMC_ResourceNode::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
#if !UE_BUILD_SHIPPING
        // Valid if the ResourceNodeConfigId is set
        if (!ResourceNodeConfigID.IsValid())
        {
            //Log Error
            UE_LOGFMT(LogResourceNode, Error, "ResourceNodeConfigID is not valid. File - {0}, Line - {1}", __FILE__, __LINE__);
        
            // If the config is invalid, destroy this actor to prevent issues
            Destroy(true);
            return;
        }
#endif
    
        //Create delegate
        FStreamableDelegate PrimaryDataAssetDelegate = FStreamableDelegate::CreateLambda([this]()
        {
            ResourceNodeConfig = Cast<UMC_DT_ResourceNodeConfig>(UAssetManager::Get().GetPrimaryAssetObject(ResourceNodeConfigID));
            if (ResourceNodeConfig)
            {
                //"Start" Node
                Server_ApplyResourceNodeConfig();
            }
        });
    
        //Load Primary Data Asset
        UAssetManager::Get().LoadPrimaryAsset(ResourceNodeConfigID, {}, PrimaryDataAssetDelegate);
    }
}

void AMC_ResourceNode::Client_DisplayMiningProgressWidget_Implementation()
{
    //TODO:Create Progress bar Widget and show widget
    UE_LOGFMT(LogResourceNode, Error, "Displaying progress bar widget on the client");
}

void AMC_ResourceNode::Client_DisplayMiningDeniedWidget_Implementation()
{
    //TODO:Create Denied Widget and show widget
    UE_LOGFMT(LogResourceNode, Error, "Displaying mining denied widget on the client");
}

void AMC_ResourceNode::Server_StartMining_Implementation(APlayerController* PlayerController)
{
    //Get MiningSystemComponent
    UMC_MiningSystemComponent* MiningSystemComponent = Cast<AMC_PlayerCharacter>(PlayerController->GetPawn())->GetMiningSystemComponent();
    
    //Check if the player is able to mine
    if (Server_CanBeMined(PlayerController))
    {
        //Find timer
        const FTimerHandle& TimerHandle = MiningTimers.FindRef(PlayerController);
        
        //Check if the timer handle is invalid
        if (!TimerHandle.IsValid())
        {
            //Create Delegate
            FTimerDelegate MineResourceNodeDelegate = FTimerDelegate::CreateUObject(this, &AMC_ResourceNode::Server_PlayerMineResource, PlayerController);
        
            //Set timer
            GetWorldTimerManager().SetTimer(const_cast<FTimerHandle&>(TimerHandle), MineResourceNodeDelegate, ResourceNodeConfig->MiningTime, true);

            //Add Timer Handle to the MiningTimers
            MiningTimers.Add(PlayerController, TimerHandle);
            
            //Start Mining
            MiningSystemComponent->StartMining();
        
            //Show progress bar
            Client_DisplayMiningProgressWidget();
        }
    }
    else
    {
        //If the player can't mine, we have to show a error widget
        Client_DisplayMiningDeniedWidget();

        //Stop Mining. Timer won't be set here.
        MiningSystemComponent->StopMining();
    }
}

void AMC_ResourceNode::Server_StopMining(APlayerController* PlayerController)
{
    //Check if the player controller is valid
    if (IsValid(PlayerController))
    {
        //Stop Mining
        Cast<AMC_PlayerCharacter>(PlayerController->GetPawn())->GetMiningSystemComponent()->StopMining();

        //Try to clear timer
        Server_TryToClearTimerHandle(PlayerController);

        //Log
        UE_LOGFMT(LogResourceNode, Log, "Player stopped mining");
    }
    else
    {
        // Log Error
        UE_LOGFMT(LogResourceNode, Error, "Player Controlelr is nullptr. File - {0}, Line - {1}", __FILE__, __LINE__);
    }
}

bool AMC_ResourceNode::Server_CanBeMined(APlayerController* PlayerController)
{
    // Validate the player controller
    if (Server_EnsureValidPlayerController(PlayerController))
    {
        // Check if the MineResourceNodeTimerHandle isn't cleared for the given player controller
        // Check if the resource node is in a minable state
        if (ResourceNodeState != EResourceNodeState::STATE_1)
        {
            // Get the player character associated with the controller
            if (AMC_PlayerCharacter* PlayerCharacter = PlayerController->GetPawn<AMC_PlayerCharacter>())
            {
                // Get the player's pickaxe from the mining system component
                if (UMC_Pickaxe* Pickaxe = PlayerCharacter->GetMiningSystemComponent()->GetMiningTool<UMC_Pickaxe>())
                {
                    // Check if the player can mine using the retrieved pickaxe
                    return PlayerCharacter->GetMiningSystemComponent()->CanPlayerMine(Pickaxe);
                }
            }
        }
    }
    
    // Return false if any condition fails
    return false; 
}

void AMC_ResourceNode::Server_PlayerMineResource(APlayerController* PlayerController)
{
    //Check if ResourceNodeState can be mined
    if (Server_CanBeMined(PlayerController))
    {
        //Decrease State of this Node
        ResourceNodeState = ResourceNodeState - 1;

        //Set StaticMesh
        Server_SetStaticMeshForCurrentState();

        //Check if ResourceNodeState is STATE_1 now
        if (ResourceNodeState == EResourceNodeState::STATE_1)
        {
            // Stop all active mining operations
            TArray<APlayerController*> PlayerControllers;
            MiningTimers.GenerateKeyArray(PlayerControllers);

            for (APlayerController* PC : PlayerControllers)
            {
                Server_StopMining(PC);
            }
        }
    }
}

void AMC_ResourceNode::Server_ResourceNode_Refresh()
{
    // If the node is already in the final state, exit the function
    if (ResourceNodeState == EResourceNodeState::STATE_4) { return; }

    // Increment the resource node state by 1
    ResourceNodeState = ResourceNodeState + 1;

    //Set StaticMesh 
    Server_SetStaticMeshForCurrentState();
}

void AMC_ResourceNode::Server_SetStaticMeshForCurrentState()
{
    //Find and check
    if (UStaticMesh* StaticMesh = ResourceNodeConfig->ResourceNodeMaterials.FindChecked(ResourceNodeState))
    {
        // Set the current static mesh
        StaticMeshComponent->SetStaticMesh(StaticMesh);
    }
    else
    {
        //Log Error
        UE_LOGFMT(LogResourceNode, Error, "Static Mesh not found for ResourceNodeState: {0}. File: {1}, Line: {2}",  UEnum::GetValueAsString(ResourceNodeState), __FILE__, __LINE__);
    }
}

void AMC_ResourceNode::Server_ApplyResourceNodeConfig()
{
    // Set the timer to refresh the resource node
    GetWorldTimerManager().SetTimer(
        ResourceNodeSpawnTimerHandle,
        this,
        &AMC_ResourceNode::Server_ResourceNode_Refresh,
        ResourceNodeConfig->TimeToIncreaseState,
        true
    );
    
    // Set the initial StaticMesh
    Server_SetStaticMeshForCurrentState();
}

bool AMC_ResourceNode::Server_EnsureValidPlayerController(APlayerController* PlayerController)
{
    //Check if the player controller is valid
    if (IsValid(PlayerController))
    {
        // PlayerController is valid, return true.
        return true;
    }
    else
    {
        //Log Warning
        UE_LOGFMT(LogResourceNode, Error, "Player Controller isn't valid. File: {0}, Line: {1}", __FILE__, __LINE__);

        //Find and remove the invalid timers
        Server_RemoveInvalidMiningTimers();
        
        // PlayerController is null, return false.
        return false;
    }
}

void AMC_ResourceNode::Server_TryToClearTimerHandle(APlayerController* PlayerController)
{
    //Clear Timer
    GetWorld()->GetTimerManager().ClearTimer(*MiningTimers.Find(PlayerController));

    // Remove the player's entry from the MiningTimers
    MiningTimers.Remove(PlayerController);
}

void AMC_ResourceNode::Server_RemoveInvalidMiningTimers()
{
    // Get the World's TimerManager to handle timer cleanup
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();

    // Temporary array to store keys for removal (can't modify map during iteration)
    TArray<APlayerController*> KeysToRemove;
    
    // Iterate through all MiningTimers entries
    for (auto& Pair : MiningTimers)
    {
        if (!IsValid(Pair.Key))
        {
            // Clear and invalidate the timer before removal
            TimerManager.ClearTimer(Pair.Value);
            KeysToRemove.Add(Pair.Key);
        }
    }

    // Remove all invalid entries from the MiningTimers map
    for (auto& Element : KeysToRemove)
    {
        MiningTimers.Remove(Element);
    }
}
