#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MC_ItemContextMenu.generated.h"

class UCommonButtonBase;
/** Forward Declarations */
class UMC_DT_ItemConfig;
class UVerticalBox;
class UCommonTextBlock;
class UCommonTextStyle;
class UCommonTextScrollStyle;
class UImage;
class UMC_DT_RarityIconSet;

/** Context Menu Widget for displaying detailed item information and actions. */
UCLASS()
class MINECORE_API UMC_ItemContextMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this ItemConfig Context Menu Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Item Context Menu Widget")
	virtual void InitializeItemContextMenu(UMC_DT_ItemConfig* ItemConfig);

protected:
	/** Events */
	virtual void NativeOnInitialized() override;
	
	/** Bind Widgets */
	/** Vertical Boxes */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Stats;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Description;

	/** Images */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UImage> Image_ItemIcon_Background;
	
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UImage> Image_ItemIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UImage> Image_ItemRarity;

	/** Common Text Blocks */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemCategory;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemPower;

	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemWeight;
	
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ItemDescription;

	/** Buttons */
	UPROPERTY(BlueprintReadOnly, Category = "Item Context Menu Widget", meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> W_GenericButton_Close;
	
	/** Data asset containing icons for item rarity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Context Menu Widget")
	TObjectPtr<UMC_DT_RarityIconSet> DT_RarityIconSet;

	/** Create Stats for this widget */
	void CreateStats(UMC_DT_ItemConfig* ItemConfig) const;

private:
	/** Delegates */
	UFUNCTION()
	void CloseButton_OnClicked_Delegate();
};
