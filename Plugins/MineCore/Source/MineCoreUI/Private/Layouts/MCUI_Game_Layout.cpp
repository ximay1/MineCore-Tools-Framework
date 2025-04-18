#include "Layouts/MCUI_Game_Layout.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"

void UMCUI_Game_Layout::PushInventory(TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	CAWS_Inventory->AddWidget(WidgetClass);
}

void UMCUI_Game_Layout::PushItemContextMenu(TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	CAWS_ItemContextInfo->AddWidget(WidgetClass);
}
