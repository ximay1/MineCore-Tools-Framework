#include "Player/MC_PlayerController.h"

void AMC_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Enable cheats
	AddCheats(true);
}
