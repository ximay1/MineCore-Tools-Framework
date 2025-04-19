#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"
#include "UI/Game/Inventory/MC_Inventory.h"
#include "UI/Game/Inventory/MC_ItemContextMenu.h"
#include "UI/Layouts/MC_Game_Layout.h"

UMC_Inventory* UMC_Game_Layout::PushInventory(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	return Cast<UMC_Inventory>(CAWS_Inventory->AddWidget(WidgetClass));
}

UMC_ItemContextMenu* UMC_Game_Layout::PushItemContextMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	return Cast<UMC_ItemContextMenu>(CAWS_ItemContextInfo->AddWidget(WidgetClass));
}