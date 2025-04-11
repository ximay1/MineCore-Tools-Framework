#include "Actors/Bags/MC_ItemBag.h"
#include "Components/MC_InventoryComponent.h"
#include "Subsystems/MC_ItemManager.h"

AMC_ItemBag::AMC_ItemBag()
{
	PrimaryActorTick.bCanEverTick = false;

	//Create Bag Mesh Component
	BagMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Bag Mesh"));

	//Set as root component
	RootComponent = BagMeshComponent;
	
	//Create Inventory Component
	InventoryComponent = CreateDefaultSubobject<UMC_InventoryComponent>(FName("Inventory"));
}

void AMC_ItemBag::Server_InitializeRandomizedBag(const FItemBagDefinition& Params)
{
	//Get Item Manager
	UMC_ItemManager* ItemManager = GetWorld()->GetSubsystem<UMC_ItemManager>();

	//Generate Items
	TArray<UMC_DT_ItemConfig*> ItemConfigs;
	ItemManager->Server_GenerateWeightedRandomItems(6, ItemConfigs);

	//Add these Item Configs to the inventory
	for (UMC_DT_ItemConfig* ItemConfig : ItemConfigs)
	{
		InventoryComponent->Server_AddItemDefinitionToFirstAvailableSlot(FItemDefinition(ItemConfig));
	}
}

void AMC_ItemBag::Server_InitializeBagWithItems(const FItemBagDefinition& Params, const TArray<UMC_DT_ItemConfig*>& SpecificItems)
{
	//Add these Item Configs to the inventory
    for (UMC_DT_ItemConfig* ItemConfig : SpecificItems)
    {
    	InventoryComponent->Server_AddItemDefinitionToFirstAvailableSlot(FItemDefinition(ItemConfig));
    }
}

void AMC_ItemBag::Server_InitializeItemBag(const FItemBagDefinition& Params, const bool bShouldRandomize, const TArray<UMC_DT_ItemConfig*>& SpecificItems)
{
	//Set Static Mesh
	BagMeshComponent->SetStaticMesh(Params.BagMesh);

	//Initialize Item Bag
	if (bShouldRandomize)
		Server_InitializeRandomizedBag(Params);
	else
		Server_InitializeBagWithItems(Params, SpecificItems);
}

void AMC_ItemBag::BeginPlay()
{
	Super::BeginPlay();

	//Execute this code only on the server
	if (HasAuthority())
	{
		//Initialize Inventory Compnent
		InventoryComponent->Server_InitializeInventory(10);
	}
}
