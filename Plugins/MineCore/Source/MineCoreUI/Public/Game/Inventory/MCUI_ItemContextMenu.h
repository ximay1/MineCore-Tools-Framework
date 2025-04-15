#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MCUI_ItemContextMenu.generated.h"

/** Forward Declarations */
class UMC_DT_ItemConfig;

UCLASS()
class MINECOREUI_API UMCUI_ItemContextMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** Initializes this Item Context Menu Widget with the specified item */
	UFUNCTION(BlueprintCallable, Category = "Inventory Slot Widget")
	virtual void InitializeItemContextMenu(UMC_DT_ItemConfig* Item);
};
