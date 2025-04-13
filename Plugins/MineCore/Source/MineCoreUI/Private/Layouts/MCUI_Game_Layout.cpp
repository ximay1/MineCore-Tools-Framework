#include "Layouts/MCUI_Game_Layout.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"

void UMCUI_Game_Layout::PushInventory(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	CAWS_Inventory->AddWidget(WidgetClass);
}

void UMCUI_Game_Layout::PushItemsInfo(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	CAWS_ItemsInfo->AddWidget(WidgetClass);
}
