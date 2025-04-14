#include "Common/Buttons/MCUI_InventorySlotButton.h"
#include "Components/Image.h"
#include "Items/MC_Item.h"

void UMCUI_InventorySlotButton::InitializeInventorySlotButtonWidget(UMC_Item* Item)
{
	//Set Icon for this button
	Image_Background->SetBrushResourceObject(Item->GetItemConfig()->ItemIcon.LoadSynchronous());
}
