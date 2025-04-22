#include "Player/MC_PlayerController.h"
#include "Player/MC_HUD.h"

AMC_HUD* AMC_PlayerController::GetMCHUD()
{
	return GetHUD<AMC_HUD>(); 
}
