#include "Actors/ResourceNodes/MC_ResourceNode.h"
#include "Data/ResourceNode/MC_ResourceNodeConfig.h"
#include "Net/UnrealNetwork.h"

AMC_ResourceNode::AMC_ResourceNode() : ResourceNodeState(static_cast<EResourceNodeState>(FMath::RandRange(0,3)))
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    
    // Create the static mesh component and set it as the root
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;
}

void AMC_ResourceNode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(AMC_ResourceNode, StaticMeshComponent);
    DOREPLIFETIME(AMC_ResourceNode, CurrentStaticMesh);
}

void AMC_ResourceNode::Server_StartMining_Implementation(APlayerController* PlayerController)
{
    //Check if the player is able to mine
    if (CanBeMined())
    {
        //Create Delegate
        FTimerDelegate MineResourceNodeDelegate = FTimerDelegate::CreateUObject(this, &AMC_ResourceNode::PlayerMineResource, PlayerController);
        
        //Set timer
        GetWorldTimerManager().SetTimer(MineResourceNodeTimerHandle, MineResourceNodeDelegate, ResourceNodeConfig->MiningTime, true);

        //Show progress bar
        Client_DisplayMiningProgressWidget(PlayerController);
    }
    else
    {
        //If the player can't mine, we have to show a error widget
        Client_DisplayMiningDeniedWidget(PlayerController);
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

bool AMC_ResourceNode::CanBeMined() const
{
    /** TODO:Create Logic here */
    return true;
}

void AMC_ResourceNode::StopMining(bool IsPlayerControllerValid)
{
    /** TODO: Create logic, IsPlayerControlerValid can be true */
    //Check if the player controller is valid
    if (IsPlayerControllerValid)
    {
        
    }
    else
    {
        
    }
}

void AMC_ResourceNode::PlayerMineResource(APlayerController* PlayerController)
{
    //Check if the player controller is valid
    bool IsPlayerControlerValid = EnsureValidPlayerController(PlayerController);
    
    //Check if ResourceNodeState isn't STATE_1
    if (ResourceNodeState != EResourceNodeState::STATE_1 && IsPlayerControlerValid)
    {
        //Decrease State of this Node
        ResourceNodeState = ResourceNodeState - 1;

        //Set StaticMesh
        SetStaticMeshForCurrentState();

        //Check if ResourceNodeState is STATE_1 now
        if (ResourceNodeState != EResourceNodeState::STATE_1)
        {
            //Start again mining
            Server_StartMining(PlayerController);
        }

        return;
    }

    //Stop mining
    StopMining(IsPlayerControlerValid);
}

void AMC_ResourceNode::BeginPlay()
{
    Super::BeginPlay();
    
    if (HasAuthority())
    {
#if !UE_BUILD_SHIPPING
        // Valid if the ResourceNodeConfigId is set
        if (!IsValid(ResourceNodeConfig))
        {
            UE_LOGFMT(LogResourceNode, Warning, "ResourceNodeConfigId is not valid");
            
            // If the config is invalid, destroy this actor to prevent issues
            Destroy(true);
            return;
        }
#endif

        //"Start" Node
        ApplyResourceNodeConfig();
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
        UE_LOGFMT(LogResourceNode, Warning, "Player Controller isn't valid. File: {0}, Line: {1}", __FILE__, __LINE__);

        //Clear timer
        GetWorldTimerManager().ClearTimer(MineResourceNodeTimerHandle);

        //Set Player Controller to nullptr
        PlayerController = nullptr;
        
        // PlayerController is null, return false.
        return false;
    }
}

void AMC_ResourceNode::OnRep_CurrentStaticMesh()
{
    //Set StaticMesh
    StaticMeshComponent->SetStaticMesh(CurrentStaticMesh);
}

void AMC_ResourceNode::SetStaticMeshForCurrentState()
{
    //Find and check
    if (UStaticMesh* StaticMesh = ResourceNodeConfig->ResourceNodeMaterials.FindChecked(ResourceNodeState))
    {
        // Set the current static mesh
        CurrentStaticMesh = StaticMesh;
    }
    else
    {
        //Log Error
        UE_LOGFMT(LogResourceNode, Error, "Material not found for ResourceNodeState: {0}. File: {1}, Line: {2}",  UEnum::GetValueAsString(ResourceNodeState), __FILE__, __LINE__);
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