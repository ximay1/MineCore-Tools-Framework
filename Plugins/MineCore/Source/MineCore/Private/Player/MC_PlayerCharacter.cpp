#include "Player/MC_PlayerCharacter.h"
#include "Components/MC_InventoryComponent.h"
#include "Components/MC_MiningSystemComponent.h"

AMC_PlayerCharacter::AMC_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Inventory Component
	InventoryComponent = CreateDefaultSubobject<UMC_InventoryComponent>(FName("Inventory Component"));

	//Create Mining System Component
	MiningSystemComponent = CreateDefaultSubobject<UMC_MiningSystemComponent>(FName("Mining System Component"));
}

void AMC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

