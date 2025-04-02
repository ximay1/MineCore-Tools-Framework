#include "Components/MC_CheatsComponent.h"

#include "Components/MC_InventoryComponent.h"

UMC_CheatsComponent::UMC_CheatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsEditorOnly = true;
	
	SetIsReplicatedByDefault(true);
}

void UMC_CheatsComponent::AddItemToFirstAvailableSlot_Cheat_Implementation(UMC_Item* Item)
{
	Cast<APlayerController>(GetOwner())->GetPawn()->FindComponentByClass<UMC_InventoryComponent>()->Server_AddItemToFirstAvailableSlot(Item);
}

