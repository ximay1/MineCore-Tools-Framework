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

UCLASS()
class MINECOREUI_API UMCUI_ItemContextMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this ItemConfig Context Menu Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Widget")
	virtual void InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig);

	/** Common Text Block Description Style */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot Widget")
	TSubclassOf<UCommonTextStyle> CommonTextDescriptonStyle_Class;

protected:
	/** Bind Widgets */
	/** Vertical Boxes */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Stats;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Description;

	/** Create Description for this widget */
	void CreateDescription(const FText& Description);

	/** Create Stats for this widget */
	void CreateStats(UMC_DT_ItemConfig* ItemConfig);
};
