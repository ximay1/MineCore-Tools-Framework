#include "Actors/ResourceNodes/MC_ResourceNodeSpawner.h"

// Sets default values
AMC_ResourceNodeSpawner::AMC_ResourceNodeSpawner()
{
 	//Set Parameters
	PrimaryActorTick.bCanEverTick = false;

}

void AMC_ResourceNodeSpawner::BeginPlay()
{
	Super::BeginPlay();

	//Check if the machine has the authority
	if (HasAuthority())
	{
		//Begin spawning the resource nodes
		Server_BeginResourceNodeSpawning();
	}
}

void AMC_ResourceNodeSpawner::Server_BeginResourceNodeSpawning()
{
	
}
