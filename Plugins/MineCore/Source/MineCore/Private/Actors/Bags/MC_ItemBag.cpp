#include "Actors/Bags/MC_ItemBag.h"
#include "Components/MC_InventoryComponent.h"

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

void AMC_ItemBag::BeginPlay()
{
	Super::BeginPlay();

	//Execute this code only on the server
	if (HasAuthority())
	{
		//Initialize Inventory Compnent
		InventoryComponent->Server_InitializeInventory();
	}
}
