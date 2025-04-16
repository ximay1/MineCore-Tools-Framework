#include "Game/Inventory/MCUI_ItemContextMenu.h"
#include "Components/VerticalBox.h"
#include "CommonTextBlock.h"
#include "Components/ScaleBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "MCUI_LogChannels.h"

void UMCUI_ItemContextMenu::InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig)
{	
	///Create description
	CreateDescription(ItemConfig->ItemDescription);

	//Create Stats
	CreateStats(ItemConfig);
}

void UMCUI_ItemContextMenu::CreateDescription(const FText& Description)
{
	//Create Common Text Block
	UCommonTextBlock* CommonTextBlock_Description = NewObject<UCommonTextBlock>(VerticalBox_Description, FName("Common_Text_Block_Description"));
	
	// Configure CommonTextBlock_Description properties
	CommonTextBlock_Description->SetText(Description);
	CommonTextBlock_Description->SetStyle(CommonTextDescriptonStyle_Class);
	CommonTextBlock_Description->SetAutoWrapText(true);

	//Add CommonTextBlock_Description to the VerticalBox_Description 
	UVerticalBoxSlot* CommonTextBlock_Description_VerticalBoxSlot = VerticalBox_Description->AddChildToVerticalBox(CommonTextBlock_Description);
	CommonTextBlock_Description_VerticalBoxSlot->SetSize(FSlateChildSize());
}

void UMCUI_ItemContextMenu::CreateStats(UMC_DT_ItemConfig* ItemConfig)
{
	//Checks if the ItemConfig isn't nullptr
	if (!ItemConfig)
	{
		//Log Warning
		UE_LOGFMT(LogTemp, Warning, "Null ItemConfig provided to CreateStats");
		return;
	}

	// Get stat properties in name-value pairs
	TMap<FString, FString> StatsProperties;
	ItemConfig->GetStatsProperties(StatsProperties);

	//Checks if the StatsProperties isn't nullptr
	if (StatsProperties.IsEmpty())
	{
		//Log Warning
		UE_LOGFMT(LogTemp, Warning, "No stats properties found for item");
		return;
	}

	// Create a widget for each stat
	for (const auto& [StatName, StatValue] : StatsProperties)
	{
		// Create Common Text Block widget
		UCommonTextBlock* StatText = NewObject<UCommonTextBlock>(VerticalBox_Stats, FName(FString::Printf(TEXT("Stat_TextBlock_%s"), *StatName)));

		// Format as "StatName - StatValue"
		StatText->SetText(FText::Format(NSLOCTEXT("ItemContextMenu", "StatFormat", "{0} - {1}"), FText::FromString(StatName), FText::FromString(StatValue)));

		// Add to vertical box with top margin
		UVerticalBoxSlot* StatSlot = VerticalBox_Stats->AddChildToVerticalBox(StatText);
		StatSlot->SetPadding(FMargin(0.0f, 15.0f, 0.0f, 0.0f));
	}
}