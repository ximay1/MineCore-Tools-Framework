#include "Development/MC_CheatManager.h"
#include "Libraries/MC_InventoryHelperLibrary.h"

void UMC_CheatManager::SerializeInventoryToJSON() const
{
	UMC_InventoryHelperLibrary::ConvertInventoryToJSON(GetPlayerController());
}
