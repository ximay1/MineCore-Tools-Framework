#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MCUI_ItemContextMenu.generated.h"

/** Forward Declarations */
class UMC_DT_ItemConfig;
class UVerticalBox;
class UCommonTextBlock;
class UCommonTextStyle;
class UCommonTextScrollStyle;
class UImage;
class UMCUI_DT_RarityIconSet;

UCLASS()
class MINECOREUI_API UMCUI_ItemContextMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this ItemConfig Context Menu Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Item Context Menu Widget")
	virtual void InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig);

	/** Common Text Block Description Style */
	UPROPERTY(EditDefaultsOnly, Category = "Item Context Menu Widget")
	TSubclassOf<UCommonTextStyle> CommonTextDescriptonStyle_Class;

protected:
	/** Bind Widgets */
	/** Vertical Boxes */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Stats;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Description;

	/** Images */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UImage> Image_ItemIcon_Background;
	
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UImage> Image_ItemIcon;

	/** Common Text Blocks */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemCategory;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemPower;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemWeight;
	
	/** This data asset contains information about icons for given rarity */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UMCUI_DT_RarityIconSet> DT_RarityIconSet;
	
	/** Create Description for this widget */
	void CreateDescription(const FText& Description);

	/** Create Stats for this widget */
	void CreateStats(UMC_DT_ItemConfig* ItemConfig);
};
