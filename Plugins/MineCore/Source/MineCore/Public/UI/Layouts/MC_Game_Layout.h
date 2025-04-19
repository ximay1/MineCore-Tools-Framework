#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MC_Game_Layout.generated.h"

/** Forward Declarations */
class UCommonActivatableWidgetStack;
class UMC_ItemContextMenu;
class UMC_Inventory;

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
	
protected:
	/** Bind Widgets */
	/** UCommonActivatableWidgetStack */
	UPROPERTY(BlueprintReadOnly, Category = "Game Layout", meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CAWS_Inventory;

	UPROPERTY(BlueprintReadOnly, Category = "Game Layout", meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CAWS_ItemContextInfo;
};
