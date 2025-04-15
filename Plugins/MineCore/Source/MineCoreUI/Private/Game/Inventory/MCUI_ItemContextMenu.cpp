#include "Game/Inventory/MCUI_ItemContextMenu.h"
#include "Components/VerticalBox.h"
#include "CommonTextBlock.h"
#include "Components/ScaleBox.h"
#include "Data/Items/MC_DT_ItemConfig.h"

void UMCUI_ItemContextMenu::InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig)
{	
	///Create description
	CreateDescription(ItemConfig->ItemDescription);
}

void UMCUI_ItemContextMenu::CreateDescription(const FText& Description)
{
	//Create Common Text Block
	UCommonTextBlock* CommonTextBlock_Description = NewObject<UCommonTextBlock>(VerticalBox_Description, FName("Common Text Block Description"));
	
	// Set default valeus for CommonTextBlock_Description
	CommonTextBlock_Description->SetText(Description);
	CommonTextBlock_Description->SetStyle(CommonTextDescriptonStyle_Class);
	CommonTextBlock_Description->SetAutoWrapText(true);

	//Add CommonTextBlock_Description to the VerticalBox_Description 
	VerticalBox_Description->AddChild(CommonTextBlock_Description);
}
