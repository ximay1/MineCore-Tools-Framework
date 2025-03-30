#include "Components/MC_ServerCheatsComponent.h"

#include "Components/MC_InventoryComponent.h"

UMC_ServerCheatsComponent::UMC_ServerCheatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsEditorOnly = true;
	
	SetIsReplicatedByDefault(true);
}

void UMC_ServerCheatsComponent::AddItemToFirstAvailableSlot_Cheat_Implementation(UMC_Item* Item)
{
	Cast<APlayerController>(GetOwner())->GetPawn()->FindComponentByClass<UMC_InventoryComponent>()->AddItemToFirstAvailableSlot(Item);
}

