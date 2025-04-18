#include "Layouts/MCUI_Game_Layout.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"

void UMCUI_Game_Layout::PushInventory(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	CAWS_Inventory->AddWidget(WidgetClass);
}

void UMCUI_Game_Layout::PushItemContextMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	CAWS_ItemContextInfo->AddWidget(WidgetClass);
}