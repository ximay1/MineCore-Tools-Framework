#include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "Components/MC_MiningSystemComponent.h"
#include "Engine/AssetManager.h"
#include "Player/MC_PlayerCharacter.h"
#include "Items/MiningTools/MC_Pickaxe.h"

AMC_ResourceNode::AMC_ResourceNode() : ResourceNodeState(static_cast<EResourceNodeState>(FMath::RandRange(0,3)))
{
    //Set Parameters
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    
    // Create the static mesh component and set it as the root
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetIsReplicated(true);
    RootComponent = StaticMeshComponent;
}

void AMC_ResourceNode::Server_StartMining_Implementation(APlayerController* PlayerController)
{
    //Get MiningSystemComponent
    UMC_MiningSystemComponent* MiningSystemComponent = Cast<AMC_PlayerCharacter>(PlayerController->GetPawn())->GetMiningSystemComponent();
    
    //Check if the player is able to mine
    if (CanBeMined(PlayerController))
    {
        //Check if the timer handle is invalid
        if (!MineResourceNodeTimerHandle.IsValid())
        {
            //Create Delegate
            FTimerDelegate MineResourceNodeDelegate = FTimerDelegate::CreateUObject(this, &AMC_ResourceNode::PlayerMineResource, PlayerController);
        
            //Set timer
            GetWorldTimerManager().SetTimer(MineResourceNodeTimerHandle, MineResourceNodeDelegate, ResourceNodeConfig->MiningTime, true);
            
            //Start Mining
            MiningSystemComponent->StartMining();
        
            //Show progress bar
            Client_DisplayMiningProgressWidget(PlayerController);
        }
    }
    else
    {
        //If the player can't mine, we have to show a error widget
        Client_DisplayMiningDeniedWidget(PlayerController);

        //Stop Mining. Timer won't be set here.
        MiningSystemComponent->StopMining();
    }
}

void AMC_ResourceNode::Client_DisplayMiningProgressWidget_Implementation(APlayerController* PlayerController)
{
    //Get Player Controller
    if (PlayerController)
    {
        //TODO:Create Progress bar Widget and show widget
        UE_LOGFMT(LogResourceNode, Error, "Displaying progress bar widget on the client - Player Controller - {0}", PlayerController->GetName());
    }
}

void AMC_ResourceNode::Client_DisplayMiningDeniedWidget_Implementation(APlayerController* PlayerController)
{
    //Get Player Controller
    if (PlayerController)
    {
        //TODO:Create Denied Widget and show widget
        UE_LOGFMT(LogResourceNode, Error, "Displaying mining denied widget on the client - Player Controller - {0}", PlayerController->GetName());
    }
}

void AMC_ResourceNode::StopMining(APlayerController* PlayerController)
{
    //Check if the player controller is valid
    if (IsValid(PlayerController))
    {
        //Stop Mining
        Cast<AMC_PlayerCharacter>(PlayerController->GetPawn())->GetMiningSystemComponent()->StopMining();
    }
    
    //Try to clear timer
    TryToClearTimerHandle(MineResourceNodeTimerHandle);
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
            ResourceNodeConfig = Cast<UMC_ResourceNodeConfig>(UAssetManager::Get().GetPrimaryAssetObject(ResourceNodeConfigID));
            if (ResourceNodeConfig)
            {
                //"Start" Node
                ApplyResourceNodeConfig();
            }
        });
    
        //Load Primary Data Asset
        UAssetManager::Get().LoadPrimaryAsset(ResourceNodeConfigID, {}, PrimaryDataAssetDelegate);
    }
}

void AMC_ResourceNode::ResourceNode_Refresh()
{
    // If the node is already in the final state, exit the function
    if (ResourceNodeState == EResourceNodeState::STATE_4) { return; }

    // Increment the resource node state by 1
    ResourceNodeState = ResourceNodeState + 1;

    //Set StaticMesh 
    SetStaticMeshForCurrentState();
}

bool AMC_ResourceNode::CanBeMined(APlayerController* PlayerController)
{
    // Validate the player controller
    if (EnsureValidPlayerController(PlayerController))
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

void AMC_ResourceNode::PlayerMineResource(APlayerController* PlayerController)
{
    //Check if ResourceNodeState can be mined
    if (CanBeMined(PlayerController))
    {
        //Decrease State of this Node
        ResourceNodeState = ResourceNodeState - 1;

        //Set StaticMesh
        SetStaticMeshForCurrentState();

        //Check if ResourceNodeState is STATE_1 now
        if (ResourceNodeState == EResourceNodeState::STATE_1)
        {
            //Stop Mining
            StopMining(PlayerController);
        }
    }
}

bool AMC_ResourceNode::EnsureValidPlayerController(APlayerController* PlayerController)
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

        //Clear timer
        TryToClearTimerHandle(MineResourceNodeTimerHandle);

        //Set Player Controller to nullptr
        PlayerController = nullptr;
        
        // PlayerController is null, return false.
        return false;
    }
}

void AMC_ResourceNode::TryToClearTimerHandle(FTimerHandle TimerHandle)
{
    //Try to clear timer
    if (TimerHandle.IsValid())
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }
}

void AMC_ResourceNode::SetStaticMeshForCurrentState()
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

void AMC_ResourceNode::ApplyResourceNodeConfig()
{
    // Set the timer to refresh the resource node
    GetWorldTimerManager().SetTimer(
        ResourceNodeSpawnTimerHandle,
        this,
        &AMC_ResourceNode::ResourceNode_Refresh,
        ResourceNodeConfig->TimeToIncreaseState,
        true
    );
    
    // Set the initial StaticMesh
    SetStaticMeshForCurrentState();
}