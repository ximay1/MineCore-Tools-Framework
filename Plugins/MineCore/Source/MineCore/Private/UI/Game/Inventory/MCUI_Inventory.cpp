#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "MC_LogChannels.h"
#include "Blueprint/WidgetTree.h"
#include "Components/MC_InventoryComponent.h"
#include "Components/ProgressBar.h"
#include "Player/MC_HUD.h"
#include "Player/MC_PlayerCharacter.h"
#include "Player/MC_PlayerController.h"
#include "UI/Game/Inventory/MC_Inventory.h"
#include "UI/Game/Inventory/MC_InventorySlot.h"
#include "UI/Layouts/MC_Game_Layout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UMC_Inventory::InitializeInventoryWidget(UMC_InventoryComponent* InventoryComponent)
{
	//Cache Inventory Slots
    CacheInventorySlots(InventoryComponent);
}

void UMC_Inventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Bind Events
	Button_Close->OnClicked().AddUObject(this, &UMC_Inventory::ButtonClose_OnClicked_Delegate);
}

void UMC_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	//Initialize weight UI elements
	UpdateInventoryWeightUI();
}

void UMC_Inventory::CacheInventorySlots(UMC_InventoryComponent* InventoryComponent)
{
	// Tracks the current expected slot index during search
	uint8 FoundInventorySlots = 0;
	const uint8 MaxItemInventorySlots = InventoryComponent->GetMaxSlots();
	
	// Iterate through all widgets in this widget's hierarchy
	WidgetTree->ForEachWidget([this, &FoundInventorySlots, InventoryComponent](UWidget* Widget)
	{
		// Match widgets following the naming pattern: [InventorySlotName]_[Index]
		if (Widget->GetName() == FString::Printf(TEXT("%s_%d"), *InventorySlotName, FoundInventorySlots))
		{
			// Verify the widget is of the correct inventory slot type
			if (UMC_InventorySlot* InventorySlot = Cast<UMC_InventorySlot>(Widget))
			{
				//Add Inventory Slot to the array
				InventorySlots.Add(InventorySlot);

				//Get Item amd Initialize Inventory Slot
				InventorySlot->InitializeInventorySlotWidget(InventoryComponent->GetAt(FoundInventorySlots));

				//Add InventorySlot to InventorySlots
				InventorySlots.Add(InventorySlot);

				// Increment only after successful validation
				FoundInventorySlots++;
			}
			else
			{
				// Log Error
				UE_LOGFMT(LogWidget, Error, 
					"Inventory slot naming conflict! Widget '{0}' (Path: {1}) "
					"matches slot naming pattern but isn't MC_InventorySlot type. ",
					Widget->GetName(),
					Widget->GetPathName());
			}
		}
	});

	// Validate if all expected inventory slots were successfully cached
	if (InventorySlots.Num() == MaxItemInventorySlots)
	{
		//Log
		UE_LOGFMT(LogWidget, Log, 
			"Successfully cached all {0} inventory slots (Expected: {1})", 
			InventorySlots.Num(), 
			MaxItemInventorySlots);
	}
	else
	{
		//Log Error
		UE_LOGFMT(LogWidget, Error, 
			"Inventory slot cache incomplete! Found {0} slots (Expected: {1}). "
			"Possible causes:\n"
			"- Missing slot widgets in hierarchy\n"
			"- Incorrect naming convention (should be: {Name}_{Index})\n"
			"- Slot widgets not derived from MC_InventorySlot",
			InventorySlots.Num(), 
			MaxItemInventorySlots);
	}
}

void UMC_Inventory::UpdateInventoryWeightUI()
{
	//Get Player Character
	AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(GetOwningPlayer()->GetCharacter()); 
	
	//Get Weight as the percent value
	float MaxWeight = PlayerCharacter->GetMaxWeight();
	float CurrentWeight = PlayerCharacter->GetInventoryComponent()->GetCurrentItemsWeight();
	float WeightPercent = MaxWeight != 0.0f ? (CurrentWeight / MaxWeight) : 0.0f;
	
	//Set Text
	CommonTextBlock_WeightPercent->SetText(FText::FromString(FString::Printf(TEXT("%.0f%%"), WeightPercent * 100.0f)));

	//Set percent in the progress bar
	ProgressBar_Weight->SetPercent(FMath::Max(1.0f, WeightPercent));
}

void UMC_Inventory::ButtonClose_OnClicked_Delegate()
{
	Cast<AMC_PlayerController>(GetOwningPlayer())->GetHUD<AMC_HUD>()->GetGameLayout()->GetCAWS_Inventory()->RemoveWidget(*this);
}
