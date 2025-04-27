#include "Items/MC_Item.h"
#include "Player/MC_HUD.h"
#include "Player/MC_PlayerController.h"
#include "UI/Common/Buttons/MC_InventorySlotButton.h"
#include "UI/Game/Inventory/MC_InventorySlot.h"
#include "UI/Game/Inventory/MC_ItemContextMenu.h"
#include "UI/Layouts/MC_Game_Layout.h"

void UMC_InventorySlot::InitializeInventorySlotWidget(UMC_Item* Item)
{
	//Check if the Item is valid
	if (IsValid(Item))
	{
		//Cache item
		CachedItem = Item;

		//Initialize Inventory Slot Button
		W_InventorySlotButton->InitializeInventorySlotButtonWidget(Item);
	}
}

void UMC_InventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Bind Events
	W_InventorySlotButton->OnClicked().AddUObject(this, &UMC_InventorySlot::HandleInventorySlotButtonClicked);
}

void UMC_InventorySlot::HandleInventorySlotButtonClicked()
{
	//Check if Cached item is valid
	if (IsValid(CachedItem))
	{
		//Create ItemContextMenu and initialize it
		UMC_ItemContextMenu* ItemContextMenu = Cast<AMC_PlayerController>(GetOwningPlayer())->GetHUD<AMC_HUD>()->GetGameLayout()->PushItemContextMenu(ItemContextMenu_Class);
		ItemContextMenu->InitializeItemContextMenu(CachedItem->GetItemConfig());
	}
}
