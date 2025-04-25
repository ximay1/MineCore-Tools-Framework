#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MC_Game_Layout.generated.h"

/** Forward Declarations */
class UCommonActivatableWidgetStack;
class UMC_ItemContextMenu;
class UMC_Inventory;
class UCommonButtonBase;

/** Main Game Layout Widget managing core UI stacks and navigation. */
UCLASS()
class MINECORE_API UMC_Game_Layout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Push Inventory */
	UFUNCTION(BlueprintCallable, Category = "Game Layout")
	UMC_Inventory* PushInventory(UPARAM(meta = (AllowedClasses = "MCUI_Inventory")) TSubclassOf<UCommonActivatableWidget> WidgetClass) const;

	/** Push Items Info */
	UFUNCTION(BlueprintCallable, Category = "Game Layout")
	UMC_ItemContextMenu* PushItemContextMenu(UPARAM(meta = (AllowedClasses = "MCUI_ItemContextMenu")) TSubclassOf<UCommonActivatableWidget> WidgetClass) const;

	/** Get CAWS_Inventory */
	UFUNCTION(BlueprintGetter, Category = "Game Layout")
	UCommonActivatableWidgetStack* GetCAWS_Inventory() const { return CAWS_Inventory; }
	
	/** Get CAWS_ItemContextInfo */
	UFUNCTION(BlueprintGetter, Category = "Game Layout")
	UCommonActivatableWidgetStack* GetCAWS_ItemContextInfo() const { return CAWS_ItemContextInfo; }

protected:
	/** Events */
	virtual void NativeOnInitialized() override;

	/** MC_Inventory Widget class */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Game Layout", meta = (AllowedClasses = "MC_Inventory"))
	TSubclassOf<UCommonActivatableWidget> Inventory_Class;
	
	/** Bind Widgets */
	/** UCommonActivatableWidgetStack */
	UPROPERTY(BlueprintReadOnly, Category = "Game Layout", meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CAWS_Inventory;

	UPROPERTY(BlueprintReadOnly, Category = "Game Layout", meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CAWS_ItemContextInfo;

	/** Buttons */
	UPROPERTY(BlueprintReadOnly, Category = "Game Layout", meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> Button_Bag;

private:
	/** Delegates */
	UFUNCTION()
	void ButtonBag_OnClicked_Delegate();
};
