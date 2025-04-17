#include "Game/Inventory/MCUI_ItemContextMenu.h"
#include "Components/VerticalBox.h"
#include "CommonTextBlock.h"
#include "Components/ScaleBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "MCUI_LogChannels.h"
#include "Components/Image.h"

#define LOCTEXT_NAMESPACE "ItemContextMenu"

void UMCUI_ItemContextMenu::InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig)
{
#if WITH_EDITOR
	// Validate enum size at runtime
	int64 FoundEnumElements = StaticEnum<EItemCategory>()->GetMaxEnumValue();
	int64 ExpectedEnumElements = 2;
	if (FoundEnumElements != ExpectedEnumElements)
	{
		UE_LOGFMT(LogWidget, Error, "EItemCategory contains {0} elements but expected {1}. We won't initialize Item Context Menu.", FoundEnumElements, ExpectedEnumElements);
		return;
	}
	
#endif
	
	// Map of category types to their display names (localized)
	const TMap<EItemCategory, FText> ItemCategoryNames =
	{
		{EItemCategory::Resource, LOCTEXT("ItemCategory::Resource", "Resource")},
		{EItemCategory::Tool,      LOCTEXT("ItemCategory::Tool", "Tool")}
	};
    
	// Initialize UI components
	CreateDescription(ItemConfig->ItemDescription);  // Item description text
	CreateStats(ItemConfig);                         // Additional stat widgets

	// Set visual assets
	Image_ItemIcon_Background->SetBrushResourceObject(ItemConfig->ItemIconBackground.LoadSynchronous());
	Image_ItemIcon->SetBrushResourceObject(ItemConfig->ItemIcon.LoadSynchronous());

	// Set dynamic text content
	CommonTextBlock_ItemName->SetText(ItemConfig->ItemName);
	CommonTextBlock_ItemCategory->SetText(ItemCategoryNames.FindRef(ItemConfig->ItemCategory));
	CommonTextBlock_ItemPower->SetText(FText::Format(LOCTEXT("ItemPower", "Item Power: {0}"), ItemConfig->PowerStats.Power));  
	CommonTextBlock_ItemWeight->SetText(FText::Format(LOCTEXT("ItemWeight", "Item Weight: {0}"), ItemConfig->Weight));
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
	int Counter = 0;
	for (const auto& [StatName, StatValue] : StatsProperties)
	{
		// Create Common Text Block widget
		UCommonTextBlock* StatText = NewObject<UCommonTextBlock>(VerticalBox_Stats, FName(FString::Printf(TEXT("Stat_TextBlock_%s"), *StatName)));

		// Format as "StatName - StatValue"
		StatText->SetText(FText::Format(LOCTEXT("Stats", "{0} - {1}"), FText::FromString(StatName), FText::FromString(StatValue)));

		// Add to vertical box with top margin
		UVerticalBoxSlot* StatSlot = VerticalBox_Stats->AddChildToVerticalBox(StatText);
		StatSlot->SetPadding(FMargin(0.0, Counter * 15.0, 0.0, 0.0));

		//Increase Counter
		Counter++;
	}
}

#undef LOCTEXT_NAMESPACE