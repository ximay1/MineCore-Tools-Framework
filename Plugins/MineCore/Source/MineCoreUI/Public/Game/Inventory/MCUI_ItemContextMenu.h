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
	/** Initializes this Item Context Menu Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Widget")
	virtual void InitializeItemContextMenu(UMC_DT_ItemConfig* Item);

	/** Common Text Block Description Style */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot Widget")
	TSubclassOf<UCommonTextStyle> CommonTextDescriptonStyle_Class;

	/** Common Text Block Description Scroll Style */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot Widget")
	TSubclassOf<UCommonTextScrollStyle> CommonTextDescriptonScrollStyle_Class; 
	
protected:
	/** Bind Widgets */
	/** Vertical Boxes */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Stats;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Description;

	/** Create Description for this widget */
	void CreateDescription(const FText& Description);
};
