#include "Player/MC_PlayerController.h"

AMC_HUD* AMC_PlayerController::GetMCHUD()
{
	return GetHUD<AMC_HUD>(); 
}
