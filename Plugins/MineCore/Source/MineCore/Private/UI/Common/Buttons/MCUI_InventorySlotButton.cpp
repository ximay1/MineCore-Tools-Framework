#include "Components/Image.h"
#include "Items/MC_Item.h"
#include "UI/Common/Buttons/MC_InventorySlotButton.h"

void UMC_InventorySlotButton::InitializeInventorySlotButtonWidget(UMC_Item* Item)
{
	//Set Icon for this button
	Image_Background->SetBrushResourceObject(Item->GetItemConfig()->ItemIcon.LoadSynchronous());
}
