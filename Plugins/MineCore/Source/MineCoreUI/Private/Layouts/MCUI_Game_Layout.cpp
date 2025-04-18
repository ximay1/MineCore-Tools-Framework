#include "Layouts/MCUI_Game_Layout.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"
#include "Game/Inventory/MCUI_Inventory.h"
#include "Game/Inventory/MCUI_ItemContextMenu.h"

UMCUI_Inventory*  UMCUI_Game_Layout::PushInventory(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	return Cast<UMCUI_Inventory>(CAWS_Inventory->AddWidget(WidgetClass));
}

UMCUI_ItemContextMenu* UMCUI_Game_Layout::PushItemContextMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	return Cast<UMCUI_ItemContextMenu>(CAWS_ItemContextInfo->AddWidget(WidgetClass));
}